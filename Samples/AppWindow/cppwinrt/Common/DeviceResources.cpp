//
// DeviceResources.cpp - A wrapper for the Direct3D 11 device and swapchain
//                       (requires DirectX 11.3 Runtime)
//


#include "pch.h"

#include "DeviceResources.h"
#include "d2d1helper.h"

std::shared_mutex mutex_swap;

using namespace DirectX;
using namespace DX;

using Microsoft::WRL::ComPtr;

using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::Graphics::Display;

#ifdef __clang__
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#pragma warning(disable : 4061)

namespace
{
#if defined(_DEBUG)
    // Check for SDK Layer support.
    inline bool SdkLayersAvailable() noexcept
    {
        HRESULT hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
            nullptr,
            D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
            nullptr,                    // Any feature level will do.
            0,
            D3D11_SDK_VERSION,
            nullptr,                    // No need to keep the D3D device reference.
            nullptr,                    // No need to know the feature level.
            nullptr                     // No need to keep the D3D device context reference.
            );

        return SUCCEEDED(hr);
    }
#endif

    inline DXGI_FORMAT NoSRGB(DXGI_FORMAT fmt) noexcept
    {
        switch (fmt)
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:   return DXGI_FORMAT_R8G8B8A8_UNORM;
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:   return DXGI_FORMAT_B8G8R8A8_UNORM;
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:   return DXGI_FORMAT_B8G8R8X8_UNORM;
        default:                                return fmt;
        }
    }
}

namespace DisplayMetrics
{
    // High resolution displays can require a lot of GPU and battery power to render.
    // High resolution phones, for example, may suffer from poor battery life if
    // games attempt to render at 60 frames per second at full fidelity.
    // The decision to render at full fidelity across all platforms and form factors
    // should be deliberate.
    static const bool SupportHighResolutions = false;

    // The default thresholds that define a "high resolution" display. If the thresholds
    // are exceeded and SupportHighResolutions is false, the dimensions will be scaled
    // by 50%.
    static const float DpiThreshold = 192.0f;		// 200% of standard desktop display.
    static const float WidthThreshold = 1920.0f;	// 1080p width.
    static const float HeightThreshold = 1080.0f;	// 1080p height.
};

// Constants used to calculate screen rotations
namespace ScreenRotation
{
    // 0-degree Z-rotation
    static const XMFLOAT4X4 Rotation0(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );

    // 90-degree Z-rotation
    static const XMFLOAT4X4 Rotation90(
        0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );

    // 180-degree Z-rotation
    static const XMFLOAT4X4 Rotation180(
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );

    // 270-degree Z-rotation
    static const XMFLOAT4X4 Rotation270(
        0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );
}

namespace DX
{

// Constructor for DeviceResources.
DeviceResources::DeviceResources(
    DXGI_FORMAT backBufferFormat,
    DXGI_FORMAT depthBufferFormat,
    UINT backBufferCount,
    D3D_FEATURE_LEVEL minFeatureLevel,
    unsigned int flags) noexcept :
        m_screenViewport{},
        m_backBufferFormat(backBufferFormat),
        m_depthBufferFormat(depthBufferFormat),
        m_backBufferCount(backBufferCount),
        m_d3dMinFeatureLevel(minFeatureLevel),
        m_d3dFeatureLevel(D3D_FEATURE_LEVEL_9_1),
        m_rotation(DXGI_MODE_ROTATION_IDENTITY),
        m_dxgiFactoryFlags(0),
        m_orientationTransform3D(ScreenRotation::Rotation0),
        m_colorSpace(DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709),
        m_options(flags),
        m_deviceNotify(nullptr)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "DeviceResources::DeviceResources";

    CreateDeviceIndependentResources();
    CreateDeviceResources();

#ifndef OSI_MEM_APP
	ac_Push(m_compositionScaleX, f_ref_CurrentPath + g_ref_Div + "m_compositionScaleX");
	ac_Push(m_compositionScaleY, f_ref_CurrentPath + g_ref_Div + "m_compositionScaleY");
	ac_Push(m_dpi, f_ref_CurrentPath + g_ref_Div + "m_dpi");
	ac_Push((int&)m_options, f_ref_CurrentPath + g_ref_Div + "m_options");
	ac_Push(m_effectiveDpi, f_ref_CurrentPath + g_ref_Div + "m_effectiveDpi");
	ac_Push(m_effectiveCompositionScaleX, f_ref_CurrentPath + g_ref_Div + "m_effectiveCompositionScaleX");
	ac_Push(m_effectiveCompositionScaleY, f_ref_CurrentPath + g_ref_Div + "m_effectiveCompositionScaleY");
#endif
}

// Configures resources that don't depend on the Direct3D device.
void DX::DeviceResources::CreateDeviceIndependentResources()
{
	// Initialize Direct2D resources.
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
	// If the project is in a debug build, enable Direct2D debugging via SDK Layers.
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	// Initialize the Direct2D Factory.
	DX::ThrowIfFailed(
		D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory3),
			&options,
			&m_d2dFactory
			)
		);

	// Initialize the DirectWrite Factory.
	DX::ThrowIfFailed(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory3),
			&m_dwriteFactory
			)
		);

	// Initialize the Windows Imaging Component (WIC) Factory.
	DX::ThrowIfFailed(
		CoCreateInstance(
			CLSID_WICImagingFactory2,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_wicFactory)
			)
		);
}

// Configures the Direct3D device, and stores handles to it and the device context.
void DeviceResources::CreateDeviceResources()
{
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

    ThrowIfFailed(CreateDXGIFactory2(m_dxgiFactoryFlags, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf())));

    // This array defines the set of DirectX hardware feature levels this app will support.
    // Note the ordering should be preserved.
    // Don't forget to declare your application's minimum required feature level in its
    // description.  All applications are assumed to support 9.1 unless otherwise stated.
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };

    // Create the Direct3D 11 API device object and a corresponding context.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	HRESULT hr = D3D11CreateDevice(
		nullptr,					// Specify nullptr to use the default adapter.
		D3D_DRIVER_TYPE_HARDWARE,	// Create a device using the hardware graphics driver.
		0,							// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
		creationFlags,				// Set debug and Direct2D compatibility flags.
		featureLevels,				// List of feature levels this app can support.
		ARRAYSIZE(featureLevels),	// Size of the list above.
		D3D11_SDK_VERSION,			// Always set this to D3D11_SDK_VERSION for Windows Store apps.
		&device,					// Returns the Direct3D device created.
		&m_d3dFeatureLevel,			// Returns feature level of device created.
		&context					// Returns the device immediate context.
		);

	if(FAILED(hr))
	    {
		// If the initialization fails, fall back to the WARP device.
		// For more information on WARP, see: 
		// http://go.microsoft.com/fwlink/?LinkId=286690
		DX::ThrowIfFailed(
			D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
				0,
				creationFlags,
				featureLevels,
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,
				&device,
				&m_d3dFeatureLevel,
				&context
				));
	    }

    // Store pointers to the Direct3D 11.3 API device and immediate context.
	DX::ThrowIfFailed(
		device.As(&m_d3dDevice)
		);

	DX::ThrowIfFailed(
		context.As(&m_d3dContext)
		);

	// Create the Direct2D device object and a corresponding context.
	ComPtr<IDXGIDevice3> dxgiDevice;
	DX::ThrowIfFailed(
		m_d3dDevice.As(&dxgiDevice)
		);

	DX::ThrowIfFailed(
		m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice)
		);

	DX::ThrowIfFailed(
		m_d2dDevice->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_d2dContext
			)
		);
}

// These resources need to be recreated every time the window size is changed.
void DeviceResources::CreateWindowSizeDependentResources()
{
	mutex_swap.lock();

    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews[] = {nullptr};
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_d3dRenderTargetView.Reset();
    m_d3dDepthStencilView.Reset();
	m_d2dTargetBitmap.Reset();
	m_d2dContext->SetTarget(nullptr);
    m_renderTarget.Reset();
    m_depthStencil.Reset();
    m_d3dContext->Flush();
	m_d3dContext->ClearState();

#if 0
	m_swapChain = nullptr;
#endif

    m_effectiveDpi = m_dpi;
	m_effectiveCompositionScaleX = m_compositionScaleX;
	m_effectiveCompositionScaleY = m_compositionScaleY;

	// To improve battery life on high resolution devices, render to a smaller render target
	// and allow the GPU to scale the output when it is presented.
	if(!DisplayMetrics::SupportHighResolutions && m_dpi > DisplayMetrics::DpiThreshold)
	    {
		float width = DX::ConvertDipsToPixels(m_logicalSize.Width, m_dpi);
		float height = DX::ConvertDipsToPixels(m_logicalSize.Height, m_dpi);

		// When the device is in portrait orientation, height > width. Compare the
		// larger dimension against the width threshold and the smaller dimension
		// against the height threshold.
        if(std::max(width, height) > DisplayMetrics::WidthThreshold && std::min(width, height) > DisplayMetrics::HeightThreshold)
            {
            // To scale the app we change the effective DPI. Logical size does not change.
            m_effectiveDpi /= 2.0f;
            m_effectiveCompositionScaleX /= 2.0f;
            m_effectiveCompositionScaleY /= 2.0f;
            }
	    }

	// Calculate the necessary render target size in pixels.
	m_logicalSize.Width = DX::ConvertDipsToPixels(m_logicalSize.Width, m_effectiveDpi);
	m_logicalSize.Height = DX::ConvertDipsToPixels(m_logicalSize.Height, m_effectiveDpi);

	// Prevent zero size DirectX content from being created.
	m_logicalSize.Width = std::max(m_logicalSize.Width, 1.0f);
	m_logicalSize.Height = std::max(m_logicalSize.Height, 1.0f);

    DXGI_MODE_ROTATION displayRotation = ComputeDisplayRotation();

    bool swapDimensions = displayRotation == DXGI_MODE_ROTATION_ROTATE90 || displayRotation == DXGI_MODE_ROTATION_ROTATE270;
    m_d3dRenderTargetSize.Width = swapDimensions ? m_logicalSize.Height : m_logicalSize.Width;
    m_d3dRenderTargetSize.Height = swapDimensions ? m_logicalSize.Width : m_logicalSize.Height;

    if(m_swapChain)
        {
        HRESULT hr = m_swapChain->ResizeBuffers(
			2, // Double-buffered swap chain.
			static_cast<UINT>(m_d3dRenderTargetSize.Width),
			static_cast<UINT>(m_d3dRenderTargetSize.Height),
            DXGI_FORMAT_B8G8R8A8_UNORM,
            0
            );

        if(hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
            {
            HandleDeviceLost();

            return;
            }
		else
			{
			if(hr == DXGI_ERROR_INVALID_CALL)
				{
#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); // add debug message
#endif
				}
			else
				{
				if(FAILED(hr))
					{
					wchar_t text_buffer[64] = { 0 }; //temporary buffer
					swprintf(text_buffer, _countof(text_buffer), L"hr result error code 0x%08X\n", hr); // convert
					OutputDebugString(text_buffer);

					winrt::check_hresult(hr);

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); // add debug message
#endif
					}
				}
			}
        }
    else
        {
        // Otherwise, create a new one using the same adapter as the existing Direct3D device.
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

        // Create a descriptor for the swap chain.
        swapChainDesc.Width = static_cast<UINT>(m_d3dRenderTargetSize.Width);
        swapChainDesc.Height = static_cast<UINT>(m_d3dRenderTargetSize.Height);
        swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        swapChainDesc.Flags = 0;

        // This sequence obtains the DXGI factory that was used to create the Direct3D device above.
		ComPtr<IDXGIDevice3> dxgiDevice;
		DX::ThrowIfFailed(
			m_d3dDevice.As(&dxgiDevice)
			);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		DX::ThrowIfFailed(
			dxgiDevice->GetAdapter(&dxgiAdapter)
			);

		ComPtr<IDXGIFactory4> dxgiFactory;
		DX::ThrowIfFailed(
			dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
			);

        DX::ThrowIfFailed(
            m_dxgiFactory->CreateSwapChainForComposition(
                m_d3dDevice.Get(),
                &swapChainDesc,
                nullptr,
                m_swapChain.GetAddressOf()
                ));

        m_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
            {
            // Get backing native interface for SwapChainPanel
            winrt::com_ptr<ISwapChainPanelNative> panelNative;

            panelNative = m_swapChainPanel.as<ISwapChainPanelNative>();

            DX::ThrowIfFailed(
                panelNative->SetSwapChain(m_swapChain.Get())
                );
            });

        // Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
        // ensures that the application will only render after each VSync, minimizing power consumption.
        ThrowIfFailed(dxgiDevice->SetMaximumFrameLatency(1));
        }

    switch (displayRotation)
	    {
	    case DXGI_MODE_ROTATION_IDENTITY:
		    m_orientationTransform2D = D2D1::Matrix3x2F::Identity();
		    m_orientationTransform3D = ScreenRotation::Rotation0;
		    break;

	    case DXGI_MODE_ROTATION_ROTATE90:
		    m_orientationTransform2D = 
                D2D1::Matrix3x2F::Rotation(90.0f) *
                D2D1::Matrix3x2F::Translation(m_logicalSize.Height, 0.0f);
		    m_orientationTransform3D = ScreenRotation::Rotation270;
		    break;

	    case DXGI_MODE_ROTATION_ROTATE180:
		    m_orientationTransform2D = 
                D2D1::Matrix3x2F::Rotation(180.0f) *
                D2D1::Matrix3x2F::Translation(m_logicalSize.Width, m_logicalSize.Height);
		    m_orientationTransform3D = ScreenRotation::Rotation180;
		    break;

	    case DXGI_MODE_ROTATION_ROTATE270:
		    m_orientationTransform2D = 
                D2D1::Matrix3x2F::Rotation(270.0f) *
                D2D1::Matrix3x2F::Translation(0.0f, m_logicalSize.Width);
		    m_orientationTransform3D = ScreenRotation::Rotation90;
		    break;

	    default:
		    throw;
	    }

    ThrowIfFailed(m_swapChain->SetRotation(displayRotation));

    // Setup inverse scale on the swap chain
	DXGI_MATRIX_3X2_F inverseScale = { 0 };
	inverseScale._11 = 1.0f / m_effectiveCompositionScaleX;
	inverseScale._22 = 1.0f / m_effectiveCompositionScaleY;
	ComPtr<IDXGISwapChain2> spSwapChain2;
	DX::ThrowIfFailed(
		m_swapChain.As<IDXGISwapChain2>(&spSwapChain2)
		);

	DX::ThrowIfFailed(
		spSwapChain2->SetMatrixTransform(&inverseScale)
		);

	// Create a render target view of the swap chain back buffer.
	ComPtr<ID3D11Texture2D1> backBuffer;
	DX::ThrowIfFailed(
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
		);

	DX::ThrowIfFailed(
		m_d3dDevice->CreateRenderTargetView1(
			backBuffer.Get(),
			nullptr,
			&m_d3dRenderTargetView
			)
		);

	// Create a depth stencil view for use with 3D rendering if needed.
	CD3D11_TEXTURE2D_DESC1 depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT, 
		static_cast<UINT>(m_d3dRenderTargetSize.Width),
		static_cast<UINT>(m_d3dRenderTargetSize.Height),
		1, // This depth stencil view has only one texture.
		1, // Use a single mipmap level.
		D3D11_BIND_DEPTH_STENCIL
		);

	ComPtr<ID3D11Texture2D1> depthStencil;
	DX::ThrowIfFailed(
		m_d3dDevice->CreateTexture2D1(
			&depthStencilDesc,
			nullptr,
			&depthStencil
			)
		);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	DX::ThrowIfFailed(
		m_d3dDevice->CreateDepthStencilView(
			depthStencil.Get(),
			&depthStencilViewDesc,
			&m_d3dDepthStencilView
			)
		);

	// Set the 3D rendering viewport to target the entire window.
	m_screenViewport = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		m_d3dRenderTargetSize.Width,
		m_d3dRenderTargetSize.Height
		);

	m_d3dContext->RSSetViewports(1, &m_screenViewport);

	// Create a Direct2D target bitmap associated with the
	// swap chain back buffer and set it as the current target.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties = 
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			m_dpi,
			m_dpi
			);

	ComPtr<IDXGISurface2> dxgiBackBuffer;
	DX::ThrowIfFailed(
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
		);

	DX::ThrowIfFailed(
		m_d2dContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&m_d2dTargetBitmap
			)
		);

	m_d2dContext->SetTarget(m_d2dTargetBitmap.Get());
	m_d2dContext->SetDpi(m_effectiveDpi, m_effectiveDpi);

	// Grayscale text anti-aliasing is recommended for all Windows Store apps.
	m_d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

	mutex_swap.unlock();
}

void DX::DeviceResources::UpdateRenderTargetSize()
{
	m_effectiveDpi = m_dpi;
	m_effectiveCompositionScaleX = m_compositionScaleX;
	m_effectiveCompositionScaleY = m_compositionScaleY;

	// To improve battery life on high resolution devices, render to a smaller render target
	// and allow the GPU to scale the output when it is presented.
	if(!DisplayMetrics::SupportHighResolutions && m_dpi > DisplayMetrics::DpiThreshold)
	    {
		float width = DX::ConvertDipsToPixels(m_logicalSize.Width, m_dpi);
		float height = DX::ConvertDipsToPixels(m_logicalSize.Height, m_dpi);

		// When the device is in portrait orientation, height > width. Compare the
		// larger dimension against the width threshold and the smaller dimension
		// against the height threshold.
        if (max(width, height) > DisplayMetrics::WidthThreshold && min(width, height) > DisplayMetrics::HeightThreshold)
            {
            // To scale the app we change the effective DPI. Logical size does not change.
            m_effectiveDpi /= 2.0f;
            m_effectiveCompositionScaleX /= 2.0f;
            m_effectiveCompositionScaleY /= 2.0f;
            }
	    }

	// Calculate the necessary render target size in pixels.
	m_logicalSize.Width = DX::ConvertDipsToPixels(m_logicalSize.Width, m_effectiveDpi);
	m_logicalSize.Height = DX::ConvertDipsToPixels(m_logicalSize.Height, m_effectiveDpi);

	// Prevent zero size DirectX content from being created.
	m_logicalSize.Width = std::max(m_logicalSize.Width, 1.0f);
	m_logicalSize.Height = std::max(m_logicalSize.Height, 1.0f);
}

// This method is called when the XAML control is created (or re-created).
void DX::DeviceResources::SetSwapChainPanel(winrt::Windows::UI::Xaml::Controls::SwapChainPanel panel)
{
    winrt::Windows::Graphics::Display::DisplayInformation currentDisplayInformation = winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

	m_swapChainPanel = panel;
	m_logicalSize = winrt::Windows::Foundation::Size(static_cast<float>(panel.ActualWidth()), static_cast<float>(panel.ActualHeight()));
	m_nativeOrientation = currentDisplayInformation.NativeOrientation();
	m_currentOrientation = currentDisplayInformation.CurrentOrientation();
	m_compositionScaleX = panel.CompositionScaleX();
	m_compositionScaleY = panel.CompositionScaleY();
	m_dpi = currentDisplayInformation.LogicalDpi();
	m_d2dContext->SetDpi(m_dpi, m_dpi);
}

// This method is called in the event handler for the DisplayContentsInvalidated event.
void DeviceResources::ValidateDevice()
{
    // The D3D Device is no longer valid if the default adapter changed since the device
    // was created or if the device has been removed.

    DXGI_ADAPTER_DESC previousDesc;
		{
        ComPtr<IDXGIAdapter1> previousDefaultAdapter;
        ThrowIfFailed(m_dxgiFactory->EnumAdapters1(0, previousDefaultAdapter.GetAddressOf()));

        ThrowIfFailed(previousDefaultAdapter->GetDesc(&previousDesc));
		}

    DXGI_ADAPTER_DESC currentDesc;
		{
        ComPtr<IDXGIFactory2> currentFactory;
        ThrowIfFailed(CreateDXGIFactory2(m_dxgiFactoryFlags, IID_PPV_ARGS(currentFactory.GetAddressOf())));

        ComPtr<IDXGIAdapter1> currentDefaultAdapter;
        ThrowIfFailed(currentFactory->EnumAdapters1(0, currentDefaultAdapter.GetAddressOf()));

        ThrowIfFailed(currentDefaultAdapter->GetDesc(&currentDesc));
		}

    // If the adapter LUIDs don't match, or if the device reports that it has been removed,
    // a new D3D device must be created.

    if(previousDesc.AdapterLuid.LowPart != currentDesc.AdapterLuid.LowPart
        || previousDesc.AdapterLuid.HighPart != currentDesc.AdapterLuid.HighPart
        || FAILED(m_d3dDevice->GetDeviceRemovedReason()))
		{
#ifdef _DEBUG
        OutputDebugStringA("Device Lost on ValidateDevice\n");
#endif

        // Create a new device and swap chain.
        HandleDeviceLost();
		}

	CreateWindowSizeDependentResources();
}

// Recreate all device resources and set them back to the current state.
void DeviceResources::HandleDeviceLost()
{
    if(m_deviceNotify)
		{
        m_deviceNotify->OnDeviceLost();
		}

    m_d3dDepthStencilView.Reset();
    m_d3dRenderTargetView.Reset();
    m_renderTarget.Reset();
    m_depthStencil.Reset();
    m_swapChain.Reset();
    m_d3dContext.Reset();
    m_d3dDevice.Reset();
    m_dxgiFactory.Reset();

#ifdef _DEBUG_DX
		{
        ComPtr<IDXGIDebug1> dxgiDebug;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug))))
			{
            dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
			}
		}
#endif

    CreateDeviceResources();
    CreateWindowSizeDependentResources();

    if(m_deviceNotify)
		{
        m_deviceNotify->OnDeviceRestored();
		}
}

// Call this method when the app suspends. It provides a hint to the driver that the app
// is entering an idle state and that temporary buffers can be reclaimed for use by other apps.
void DeviceResources::Trim() noexcept
{
    ComPtr<IDXGIDevice3> dxgiDevice;

    if(SUCCEEDED(m_d3dDevice.As(&dxgiDevice)))
		{
        dxgiDevice->Trim();
		}
}

// Present the contents of the swap chain to the screen.
void DeviceResources::Present()
{
	DXGI_PRESENT_PARAMETERS parameters = { 0 };
	HRESULT hr = m_swapChain->Present1(1, 0, &parameters);

	m_d3dContext->DiscardView1(m_d3dRenderTargetView.Get(), nullptr, 0);
	m_d3dContext->DiscardView1(m_d3dDepthStencilView.Get(), nullptr, 0);

	if(hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
		HandleDeviceLost();
		}
	else
		{
		DX::ThrowIfFailed(hr);
		}
}

// This method acquires the first available hardware adapter.
// If no such adapter can be found, *ppAdapter will be set to nullptr.
void DeviceResources::GetHardwareAdapter(IDXGIAdapter1** ppAdapter)
{
    *ppAdapter = nullptr;

    ComPtr<IDXGIAdapter1> adapter;

#if defined(__dxgi1_6_h__) && defined(NTDDI_WIN10_RS4)
    ComPtr<IDXGIFactory6> factory6;
    HRESULT hr = m_dxgiFactory.As(&factory6);
    if(SUCCEEDED(hr))
		{
        for(UINT adapterIndex = 0;
            SUCCEEDED(factory6->EnumAdapterByGpuPreference(
            adapterIndex,
            DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
            IID_PPV_ARGS(adapter.ReleaseAndGetAddressOf())));
            adapterIndex++)
			{
            DXGI_ADAPTER_DESC1 desc;
            ThrowIfFailed(adapter->GetDesc1(&desc));

            if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				{
                // Don't select the Basic Render Driver adapter.
                continue;
				}

        #ifdef _DEBUG
            wchar_t buff[256] = {};
            swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterIndex, desc.VendorId, desc.DeviceId, desc.Description);
            OutputDebugStringW(buff);
        #endif

            break;
			}
		}
#endif
    if(!adapter)
		{
        for(UINT adapterIndex = 0;
            SUCCEEDED(m_dxgiFactory->EnumAdapters1(
            adapterIndex,
            adapter.ReleaseAndGetAddressOf()));
            adapterIndex++)
			{
            DXGI_ADAPTER_DESC1 desc;
            ThrowIfFailed(adapter->GetDesc1(&desc));

            if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				{
                // Don't select the Basic Render Driver adapter.
                continue;
				}

#ifdef _DEBUG
            wchar_t buff[256] = {};
            swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterIndex, desc.VendorId, desc.DeviceId, desc.Description);
            OutputDebugStringW(buff);
#endif

            break;
			}
		}

    *ppAdapter = adapter.Detach();
}

// This method determines the rotation between the display device's native orientation and the
// current display orientation.
DXGI_MODE_ROTATION DeviceResources::ComputeDisplayRotation(void)
{
	DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

	// Note: NativeOrientation can only be Landscape or Portrait even though
	// the DisplayOrientations enum has other values.
	switch(m_nativeOrientation)
	    {
		case winrt::Windows::Graphics::Display::DisplayOrientations::Landscape:
			{
		    switch (m_currentOrientation)
		        {
		        case winrt::Windows::Graphics::Display::DisplayOrientations::Landscape:
			        rotation = DXGI_MODE_ROTATION_IDENTITY;
			        break;

		        case winrt::Windows::Graphics::Display::DisplayOrientations::Portrait:
			        rotation = DXGI_MODE_ROTATION_ROTATE270;
			        break;

		        case winrt::Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped:
			        rotation = DXGI_MODE_ROTATION_ROTATE180;
			        break;

		        case winrt::Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
			        rotation = DXGI_MODE_ROTATION_ROTATE90;
			        break;
		        }
			}break;

	    case winrt::Windows::Graphics::Display::DisplayOrientations::Portrait:
			{
		    switch (m_currentOrientation)
		        {
		        case winrt::Windows::Graphics::Display::DisplayOrientations::Landscape:
			        rotation = DXGI_MODE_ROTATION_ROTATE90;
			        break;

		        case winrt::Windows::Graphics::Display::DisplayOrientations::Portrait:
			        rotation = DXGI_MODE_ROTATION_IDENTITY;
			        break;

		        case winrt::Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped:
			        rotation = DXGI_MODE_ROTATION_ROTATE270;
			        break;

		        case winrt::Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
			        rotation = DXGI_MODE_ROTATION_ROTATE180;
			        break;
		        }
			}break;
	    }

	return rotation;
}

// This method is called in the event handler for the SizeChanged event.
void DeviceResources::SetLogicalSize(winrt::Windows::Foundation::Size logicalSize)
{
	if(m_logicalSize != logicalSize)
	    {
		m_logicalSize = logicalSize;

		CreateWindowSizeDependentResources();

		g_RenderHesh = true;
	    }
}

// This method is called in the event handler for the DpiChanged event.
void DeviceResources::SetDpi(float dpi)
{
	if(dpi != m_dpi)
	    {
		m_dpi = dpi;
		m_d2dContext->SetDpi(m_dpi, m_dpi);

		CreateWindowSizeDependentResources();

		g_RenderHesh = true;
	    }
}

// This method is called in the event handler for the OrientationChanged event.
void DeviceResources::SetCurrentOrientation(winrt::Windows::Graphics::Display::DisplayOrientations currentOrientation)
{
	if(m_currentOrientation != currentOrientation)
	    {
		m_currentOrientation = currentOrientation;

		CreateWindowSizeDependentResources();

		g_RenderHesh = true;
	    }
}

// This method is called in the event handler for the CompositionScaleChanged event.
void DeviceResources::SetCompositionScale(float compositionScaleX, float compositionScaleY)
{
	if(m_compositionScaleX != compositionScaleX ||
		m_compositionScaleY != compositionScaleY)
	    {
		m_compositionScaleX = compositionScaleX;
		m_compositionScaleY = compositionScaleY;

		CreateWindowSizeDependentResources();

		g_RenderHesh = true;
	    }
}

};