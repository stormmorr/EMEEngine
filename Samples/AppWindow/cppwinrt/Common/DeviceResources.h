//
// DeviceResources.h - A wrapper for the Direct3D 11 device and swapchain
//

#pragma once

#include <wrl.h>
#include <wrl/client.h>
#include <shcore.h>
#include <memory>
#include <iostream>
#include <mutex>

#include <d3d11_1.h>
#include <d2d1_1.h>
#include <d3d11_3.h>
#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif

#include <wincodec.h>

#include "d2d1_3.h"
#include "dwrite.h"
#include "dwrite_3.h"

#include "DirectXHelper.h"

extern std::shared_mutex mutex_swap;

namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) noexcept : result(hr) {}

        const char* what() const override
            {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
            return s_str;
            }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
        {
        if (FAILED(hr))
            {
            throw com_exception(hr);
            }
        }

    extern std::future<std::vector<unsigned char>> ReadDataAsync(const std::wstring_view& filename);

    // Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
    interface IDeviceNotify
    {
        virtual void OnDeviceLost() = 0;
        virtual void OnDeviceRestored() = 0;

    protected:
        ~IDeviceNotify() = default;
    };

    // Controls all the DirectX device resources.
    class DeviceResources : public ecom_base
    {
    public:
        static const unsigned int c_AllowTearing    = 0x1;
        static const unsigned int c_EnableHDR       = 0x2;

        DeviceResources(DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM,
                        DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT,
                        UINT backBufferCount = 2,
                        D3D_FEATURE_LEVEL minFeatureLevel = D3D_FEATURE_LEVEL_9_3,
                        unsigned int flags = 0) noexcept;
        ~DeviceResources() = default;

        DeviceResources(DeviceResources&&) = default;
        DeviceResources& operator= (DeviceResources&&) = default;

        DeviceResources(DeviceResources const&) = delete;
        DeviceResources& operator= (DeviceResources const&) = delete;

        void CreateDeviceResources();
        void CreateWindowSizeDependentResources();
        void CreateDeviceIndependentResources();
        void SetSwapChainPanel(winrt::Windows::UI::Xaml::Controls::SwapChainPanel panel);
        void SetLogicalSize(winrt::Windows::Foundation::Size logicalSize);
        void SetCurrentOrientation(winrt::Windows::Graphics::Display::DisplayOrientations currentOrientation);
        void SetCompositionScale(float compositionScaleX, float compositionScaleY);
        void SetDpi(float dpi);
        void ValidateDevice();
        void HandleDeviceLost();
        void RegisterDeviceNotify(IDeviceNotify* deviceNotify) noexcept { m_deviceNotify = deviceNotify; }
        void Trim() noexcept;
        void Present();

        // Device Accessors.
        winrt::Windows::Foundation::Size GetOutputSize() const noexcept             { return m_logicalSize; }
        DXGI_MODE_ROTATION GetRotation() const noexcept { return m_rotation; }

        // Direct3D Accessors.
        auto                    GetD3DDevice() const noexcept              { return m_d3dDevice.Get(); }
        auto                    GetD3DDeviceContext() const noexcept       { return m_d3dContext.Get(); }
        auto                    GetSwapChain() const noexcept              { return m_swapChain.Get(); }
        auto                    GetDXGIFactory() const noexcept            { return m_dxgiFactory.Get(); }
        D3D_FEATURE_LEVEL       GetDeviceFeatureLevel() const noexcept     { return m_d3dFeatureLevel; }
        ID3D11Texture2D*        GetRenderTarget() const noexcept           { return m_renderTarget.Get(); }
        ID3D11Texture2D*        GetDepthStencil() const noexcept           { return m_depthStencil.Get(); }
        ID3D11RenderTargetView* GetRenderTargetView() const noexcept       { return m_d3dRenderTargetView.Get(); }
        ID3D11DepthStencilView* GetDepthStencilView() const noexcept       { return m_d3dDepthStencilView.Get(); }
        DXGI_FORMAT             GetBackBufferFormat() const noexcept       { return m_backBufferFormat; }
        DXGI_FORMAT             GetDepthBufferFormat() const noexcept      { return m_depthBufferFormat; }
        D3D11_VIEWPORT          GetScreenViewport() const noexcept         { return m_screenViewport; }
        UINT                    GetBackBufferCount() const noexcept        { return m_backBufferCount; }
        DirectX::XMFLOAT4X4     GetOrientationTransform3D() const noexcept { return m_orientationTransform3D; }
        DXGI_COLOR_SPACE_TYPE   GetColorSpace() const noexcept             { return m_colorSpace; }
        unsigned int            GetDeviceOptions() const noexcept          { return m_options; }
        D2D1::Matrix3x2F		GetOrientationTransform2D() const          { return m_orientationTransform2D; }

        void UpdateRenderTargetSize(void);

        Microsoft::WRL::ComPtr<ID2D1Factory3>		m_d2dFactory;
        Microsoft::WRL::ComPtr<ID2D1DeviceContext2>	m_d2dContext;

        winrt::Windows::Foundation::Size            m_d3dRenderTargetSize;

    private:
        void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);
        void UpdateColorSpace();
        DXGI_MODE_ROTATION ComputeDisplayRotation();

        // Direct3D objects.
        Microsoft::WRL::ComPtr<IDXGIFactory2>           m_dxgiFactory;
        Microsoft::WRL::ComPtr<ID3D11Device3>           m_d3dDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext2>    m_d3dContext;
        Microsoft::WRL::ComPtr<IDXGISwapChain1>          m_swapChain;

        // Direct3D rendering objects. Required for 3D.
        Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_renderTarget;
        Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_depthStencil;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView1>	m_d3dRenderTargetView;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_d3dDepthStencilView;
        D3D11_VIEWPORT                                  m_screenViewport;               

        // Direct3D properties.
        DXGI_FORMAT                                     m_backBufferFormat;
        DXGI_FORMAT                                     m_depthBufferFormat;
        UINT                                            m_backBufferCount;
        D3D_FEATURE_LEVEL                               m_d3dMinFeatureLevel;

        // Cached device properties.
        D3D_FEATURE_LEVEL                               m_d3dFeatureLevel;
        DXGI_MODE_ROTATION                              m_rotation;
        DWORD                                           m_dxgiFactoryFlags;

        winrt::Windows::Foundation::Size                       m_logicalSize;
        winrt::Windows::Graphics::Display::DisplayOrientations m_nativeOrientation;
        winrt::Windows::Graphics::Display::DisplayOrientations m_currentOrientation;
        float                                           m_compositionScaleX;
        float                                           m_compositionScaleY;
        float                                           m_dpi;

        // Direct2D drawing components.
        Microsoft::WRL::ComPtr<ID2D1Device2>		m_d2dDevice;
        Microsoft::WRL::ComPtr<ID2D1Bitmap1>		m_d2dTargetBitmap;

        // DirectWrite drawing components.
        Microsoft::WRL::ComPtr<IDWriteFactory3>		m_dwriteFactory;
        Microsoft::WRL::ComPtr<IWICImagingFactory2>	m_wicFactory;

        // Transforms used for display orientation.
        DirectX::XMFLOAT4X4                             m_orientationTransform3D;

        // HDR Support
        DXGI_COLOR_SPACE_TYPE                           m_colorSpace;

        // DeviceResources options (see flags above)
        unsigned int                                    m_options;

        // Variables that take into account whether the app supports high resolution screens or not.
        float											m_effectiveDpi;
        float											m_effectiveCompositionScaleX;
        float											m_effectiveCompositionScaleY;

        // Transforms used for display orientation.
        D2D1::Matrix3x2F	m_orientationTransform2D;

        // The IDeviceNotify can be held directly as it owns the DeviceResources.
        IDeviceNotify*                                  m_deviceNotify;

        winrt::Windows::UI::Xaml::Controls::SwapChainPanel m_swapChainPanel;
    };
}