/*

Sample3DSceneRenderer - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Sample3DSceneRenderer.h"
#include "Code/CLS/Target.h"

#include "Common/DirectXHelper.h"

#include <Generated Files\winrt\Windows.UI.Composition.h>

using namespace ecoin;
using namespace Cube;
using namespace DirectX;
using namespace Windows::Foundation;

float g_StampProvider = 0.0f;
float g_StampSize = 1.0f;

DirectX::XMMATRIX g_MatrixTP;
std::vector<std::shared_ptr<Ackent>> g_Ackent;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(std::shared_ptr<DX::DeviceResources> deviceResources) :
	m_loadingComplete(false),
	m_COMloadingComplete(false),
	m_degreesPerSecond(45),
	m_indexCount(0),
	m_tracking(false)
{
	m_deviceResources = deviceResources;

	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	g_Target_1 = NULL;
	g_Target_2 = NULL;
	g_Target_3 = NULL;
	g_Target_4 = NULL;
	g_Target_5 = NULL;
	g_Target_6 = NULL;
	g_Target_7 = NULL;
	g_Target_8 = NULL;
	g_Target_9 = NULL;
	g_Target_10 = NULL;

#if 0
	std::shared_ptr<classTarget> g_Target_1 = new classTarget();
	g_Target_1->acGen_Humanoid();
	g_Target_1->acSaveCloud("Human Factor1");
#endif

#if 0
	std::shared_ptr<classTarget> g_Target_2 = new classTarget();
	g_Target_2->acGen_Vehicle_Ground();
	g_Target_2->acSaveCloud("Vehicle Ground1");
#endif
}

Sample3DSceneRenderer::~Sample3DSceneRenderer()
{
	m_deviceResources = nullptr;

	g_Target_1 = NULL;
	g_Target_2 = NULL;
	g_Target_3 = NULL;
	g_Target_4 = NULL;
	g_Target_5 = NULL;
	g_Target_6 = NULL;
	g_Target_7 = NULL;
	g_Target_8 = NULL;
	g_Target_9 = NULL;
	g_Target_10 = NULL;
}

// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	winrt::Windows::Foundation::Size outputSize = m_deviceResources->GetOutputSize();

	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if(aspectRatio < 1.0f)
		{
		fovAngleY *= 2.0f;
		}

	// Note that the OrientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	Cube::g_projection = perspectiveMatrix * orientationMatrix;

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	XMStoreFloat4x4(
		&m_QCGconstantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	XMStoreFloat4x4(
		&m_COMconstantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	XMStoreFloat4x4(
		&m_curveconstantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
	XMVECTORF32 eye = { 0.0f, -1.4f * 1.5f/*SCP_FLT_SCALE*/, 5.555f * 1.0f/*SCP_FLT_SCALE*/, 0.0f };
	XMVECTORF32 at = { 0.0f, -1.4f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	eye.v.m128_f32[0] += g_QcomManager->m_current_X;
	eye.v.m128_f32[1] += g_QcomManager->m_current_Y;

	at.v.m128_f32[0] += g_QcomManager->m_current_X;
	at.v.m128_f32[1] += g_QcomManager->m_current_Y;

	XMStoreFloat4x4(&m_QCGconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	XMMATRIX f_MatrixVW = XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up));

	Cube::g_view = f_MatrixVW;

#ifdef ARM_ARCH
	Cube::g_eye = Cube::BiVector(eye.v.n128_f32[0], eye.v.n128_f32[1], eye.v.n128_f32[2], eye.v.n128_f32[3]);
	Cube::g_at = Cube::BiVector(at.v.n128_f32[0], at.v.n128_f32[1], at.v.n128_f32[2], at.v.n128_f32[3]);
#else
	Cube::g_eye = Cube::BiVector(eye.v.m128_f32[0], eye.v.m128_f32[1], eye.v.m128_f32[2], eye.v.m128_f32[3]);
	Cube::g_at = Cube::BiVector(at.v.m128_f32[0], at.v.m128_f32[1], at.v.m128_f32[2], at.v.m128_f32[3]);
#endif
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(void)
{
	// Convert degrees to radians, then convert seconds to rotation angle
	float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
	float f_O = 0.15f;
	double totalRotation = f_O * radiansPerSecond;
	float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

	Rotate(radians);
}

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
	// Prepare to pass the updated model matrix to the shader
	g_RADX = 0;
	g_RADY = 0;
	g_RADZ = 0;

	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));

	//XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
	//XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));

	XMStoreFloat4x4(&m_QCGconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(0.0f)));
	XMStoreFloat4x4(&m_COMconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(0.0f)));
	XMStoreFloat4x4(&m_curveconstantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(0.0f)));
}

void Sample3DSceneRenderer::StartTracking()
{
	m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
	float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
	Rotate(radians);
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render(int f_Index)
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(!m_loadingComplete)
		{
		return;
		}

	if(f_Index >= g_TargetedHesh->vec_Bicycle.size())
		{
		return;
		}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0,
		0
		);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	context->IASetVertexBuffers(
		0,
		1,
		g_TargetedHesh->vec_Bicycle[f_Index]->m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		g_TargetedHesh->vec_Bicycle[f_Index]->m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_inputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	// Draw the objects.
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render_Qcom(void)
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(!m_loadingComplete)
		{
		return;
		}

	XMVECTORF32 eye = { 0.0f, -1.4f, 5.555f, 0.0f };
	XMVECTORF32 at = { 0.0f, -1.4f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	//XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	float f_Div = 5.0f;

	eye.v.m128_f32[0] += g_QcomManager->m_current_X / f_Div;
	eye.v.m128_f32[1] += g_QcomManager->m_current_Y / f_Div;

	at.v.m128_f32[0] += g_QcomManager->m_current_X / f_Div;
	at.v.m128_f32[1] += g_QcomManager->m_current_Y / f_Div;

	XMStoreFloat4x4(&m_QCGconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_QCGconstantBuffer.Get(),
		0,
		NULL,
		&m_QCGconstantBufferData,
		0,
		0,
		0
		);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	context->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_QCGinputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(
		m_QCGvertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_QCGconstantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_QCGpixelShader.Get(),
		nullptr,
		0
		);

	// Draw the objects.
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render_Curve(void)
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(m_curveloadingComplete == false)
		{
		return;
		}

	auto context = m_deviceResources->GetD3DDeviceContext();

	D3D11_BLEND_DESC blendDesc;
	ID3D11BlendState* blendState;

	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; //0x0f;

	// set blending
	m_deviceResources->GetD3DDevice()->CreateBlendState(&blendDesc, &blendState);

	float blendFactor[4] = { 1,1,1, 1 };
	context->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	XMVECTORF32 eye = { 0.0f, -1.4f, 5.555f, 0.0f };
	XMVECTORF32 at = { 0.0f, -1.4f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	float f_Div = 5.0f;

	eye.v.m128_f32[0] += (g_QcomManager->m_current_X / f_Div);
	eye.v.m128_f32[1] += (g_QcomManager->m_current_Y / f_Div);

	at.v.m128_f32[0] += (g_QcomManager->m_current_X / f_Div);
	at.v.m128_f32[1] += (g_QcomManager->m_current_Y / f_Div);

	XMStoreFloat4x4(&m_curveconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)) * XMMatrixTranspose(XMMatrixRotationY(g_RADZ)));

	for(int f_XY = 0; f_XY < g_QcomManager->m_vec_ComWire.size(); f_XY++)
		{
		if(f_XY == 0 || true)
		{
		std::shared_ptr<QcomWire> f_Wire = g_QcomManager->m_vec_ComWire[f_XY];

		XMVECTOR f_Min;
		f_Min.m128_f32[0] = f_Wire->m_Xmin;
		f_Min.m128_f32[1] = f_Wire->m_Ymin;
		f_Min.m128_f32[2] = f_Wire->m_Length;
		f_Min.m128_f32[3] = f_Wire->m_Height;

		XMVECTOR f_Max;
		f_Max.m128_f32[0] = f_Wire->m_Xmax;
		f_Max.m128_f32[1] = f_Wire->m_Ymax;
		f_Max.m128_f32[2] = f_Wire->m_Length;
		f_Max.m128_f32[3] = f_Wire->m_Height;

		time_t f_Time;
		time(&f_Time);

		f_Wire->m_Time += 0.01;// f_Time
		if(f_Wire->m_Time > 2.0f)
			{
			f_Wire->m_Time = 1.0f;
			}

		XMVECTOR f_TimeVec;
		f_TimeVec.m128_f32[0] = (float)f_Wire->m_Time;
		f_TimeVec.m128_f32[1] = (float)f_Wire->m_Time;
		f_TimeVec.m128_f32[2] = (float)f_Wire->m_Time;
		f_TimeVec.m128_f32[3] = (float)f_Wire->m_Time;

		XMMATRIX f_Matrix;
		f_Matrix.r[0] = f_Min;
		f_Matrix.r[1] = f_Max;
		f_Matrix.r[2] = f_TimeVec;
		f_Matrix.r[3] = f_TimeVec;

		XMStoreFloat4x4(&m_curveconstantBufferData.model, f_Matrix);

		// Prepare the constant buffer to send it to the graphics device.
		context->UpdateSubresource1(
			m_curveconstantBuffer.Get(),
			0,
			NULL,
			&m_curveconstantBufferData,
			0,
			0,
			0
			);

		// Each vertex is one instance of the VertexPositionColor struct.
		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;

		context->IASetVertexBuffers(
			0,
			1,
			f_Wire->m_curvevertexBuffer.GetAddressOf(),
			&stride,
			&offset
			);

		context->IASetIndexBuffer(
			f_Wire->m_curveindexBuffer.Get(),
			DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
			0
			);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		context->IASetInputLayout(m_curveinputLayout.Get());

		// Attach our vertex shader.
		context->VSSetShader(
			m_curvevertexShader.Get(),
			nullptr,
			0
			);

		// Send the constant buffer to the graphics device.
		context->VSSetConstantBuffers1(
			0,
			1,
			m_curveconstantBuffer.GetAddressOf(),
			nullptr,
			nullptr
			);

		// Attach our pixel shader.
		context->PSSetShader(
			m_curvepixelShader.Get(),
			nullptr,
			0
			);

		// Draw the objects.
		context->DrawIndexed(
			f_Wire->m_indexCount,
			0,
			0
			);
		}
		}
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render_COM(float f_X, float f_Y, time_t f_Trial_Length)
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(m_COMloadingComplete == false)
		{
		return;
		}

	time_t f_Time;
	time(&f_Time);

	if(f_Trial_Length != -1)
		{
		if(f_Time > f_Trial_Length)
			{
			return;
			}
		}

	XMVECTORF32 eye = { 0.0f, -1.4f, 5.555f, 0.0f };
	XMVECTORF32 at = { 0.0f, -1.4f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	float f_Div = 5.0f;

	eye.v.m128_f32[0] += ((g_QcomManager->m_current_X + (f_X * -1.0f)) / f_Div);
	eye.v.m128_f32[1] += ((g_QcomManager->m_current_Y + (f_Y * -1.0f)) / f_Div) + g_BoardPushHeightAdjust;

	at.v.m128_f32[0] += ((g_QcomManager->m_current_X + (f_X * -1.0f)) / f_Div);
	at.v.m128_f32[1] += ((g_QcomManager->m_current_Y + (f_Y * -1.0f)) / f_Div) + g_BoardPushHeightAdjust;

	XMStoreFloat4x4(&m_COMconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	auto context = m_deviceResources->GetD3DDeviceContext();

#if 1
	D3D11_BLEND_DESC blendDesc;
	ID3D11BlendState* blendState;

	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; //0x0f;

	// set blending
	m_deviceResources->GetD3DDevice()->CreateBlendState(&blendDesc, &blendState);

	float blendFactor[4] = { 1,1,1, 1 };
	context->OMSetBlendState(blendState, blendFactor, 0xffffffff);
#endif

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_COMconstantBuffer.Get(),
		0,
		NULL,
		&m_COMconstantBufferData,
		0,
		0,
		0
		);

	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;

	context->IASetVertexBuffers(
		0,
		1,
		m_COMvertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_COMindexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
		);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_COMinputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(
		m_COMvertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_COMconstantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_COMpixelShader.Get(),
		nullptr,
		0
		);

#pragma message("m_indexcount is the same temporarily most likely")

	// Draw the objects.
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;

std::future<void> Sample3DSceneRenderer::CreateDeviceDependentResources(void)
{
	g_ref_CurrentPath = "Sample3DSceneRenderer::CreateDeviceDependentResources";

	// Load shaders asynchronously.
	// After the vertex shader file is loaded, create the shader and input layout.

	std::vector<unsigned char> fileDataOL = await DX::ReadDataAsync(L"ms-appx:///SampleVertexShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateVertexShader(
			&fileDataOL[0],
			fileDataOL.size(),
			nullptr,
			&m_vertexShader)
			);

	static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			&fileDataOL[0],
			fileDataOL.size(),
			&m_inputLayout)
			);

	// After the pixel shader file is loaded, create the shader and constant buffer.
	std::vector<unsigned char> fileDataP = await DX::ReadDataAsync(L"ms-appx:///SamplePixelShader.cso");
		
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreatePixelShader(
			&fileDataP[0],
			fileDataP.size(),
			nullptr,
			&m_pixelShader)
			);

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&constantBufferDesc,
			nullptr,
			&m_constantBuffer)
			);

	// After the vertex shader file is loaded, create the shader and input layout.
	std::vector<unsigned char> fileDataL = await DX::ReadDataAsync(L"ms-appx:///QcomGridVertexShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateVertexShader(
			&fileDataL[0],
			fileDataL.size(),
			nullptr,
			&m_QCGvertexShader
			)
		);

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			&fileDataL[0],
			fileDataL.size(),
			&m_QCGinputLayout
			)
		);

	// After the pixel shader file is loaded, create the shader and constant buffer.
	std::vector<unsigned char> fileDataPL = await DX::ReadDataAsync(L"ms-appx:///QcomGridPixelShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreatePixelShader(
			&fileDataPL[0],
			fileDataPL.size(),
			nullptr,
			&m_QCGpixelShader
			)
		);

	CD3D11_BUFFER_DESC constantBufferDescPL(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&constantBufferDescPL,
			nullptr,
			&m_QCGconstantBuffer
			)
		);

	// After the vertex shader file is loaded, create the shader and input layout.
	std::vector<unsigned char> fileDataM = await DX::ReadDataAsync(L"ms-appx:///comVertexShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateVertexShader(
			&fileDataM[0],
			fileDataM.size(),
			nullptr,
			&m_COMvertexShader
			)
		);

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			&fileDataM[0],
			fileDataM.size(),
			&m_COMinputLayout
			)
		);

	// After the pixel shader file is loaded, create the shader and constant buffer.
	std::vector<unsigned char> fileDataPB = await DX::ReadDataAsync(L"ms-appx:///comPixelShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreatePixelShader(
			&fileDataPB[0],
			fileDataPB.size(),
			nullptr,
			&m_COMpixelShader
			)
		);

	CD3D11_BUFFER_DESC constantBufferDescPB(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&constantBufferDescPB,
			nullptr,
			&m_COMconstantBuffer
			)
		);

	// After the vertex shader file is loaded, create the shader and input layout.
	std::vector<unsigned char> fileDataFG = await DX::ReadDataAsync(L"ms-appx:///CurveVertexShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateVertexShader(
			&fileDataFG[0],
			fileDataFG.size(),
			nullptr,
			&m_curvevertexShader
			)
		);

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			&fileDataFG[0],
			fileDataFG.size(),
			&m_curveinputLayout
			)
		);

	// After the pixel shader file is loaded, create the shader and constant buffer.
	std::vector<unsigned char> fileDataPG = await DX::ReadDataAsync(L"ms-appx:///CurvePixelShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreatePixelShader(
			&fileDataPG[0],
			fileDataPG.size(),
			nullptr,
			&m_curvepixelShader
			)
		);

	CD3D11_BUFFER_DESC constantBufferDescPG(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&constantBufferDescPG,
			nullptr,
			&m_curveconstantBuffer
			)
		);

	// Once both shaders are loaded, create the mesh.
	float f_XScale = 25.0f;
	float f_YScale = 25.0f;

	// Load mesh vertices. Each vertex has a position and a color.
	static const VertexPositionColor cubeVertices[] = 
		{
		{XMFLOAT3(-0.5f * f_XScale, -0.5f * f_YScale, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
		{XMFLOAT3(-0.5f * f_XScale, -0.5f * f_YScale,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-0.5f * f_XScale,  0.5f * f_YScale, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{XMFLOAT3(-0.5f * f_XScale,  0.5f * f_YScale,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
		{XMFLOAT3( 0.5f * f_XScale, -0.5f * f_YScale, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3( 0.5f * f_XScale, -0.5f * f_YScale,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 0.5f * f_XScale,  0.5f * f_YScale, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
		{XMFLOAT3( 0.5f * f_XScale,  0.5f * f_YScale,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		};

	D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDescCV(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDescCV,
			&vertexBufferData,
			&m_vertexBuffer
			)
		);

	// Load mesh indices. Each trio of indices represents
	// a triangle to be rendered on the screen.
	// For example: 0,2,1 means that the vertices with indexes
	// 0, 2 and 1 from the vertex buffer compose the 
	// first triangle of this mesh.
	static const unsigned short cubeIndices [] =
		{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
		};

	m_indexCount = ARRAYSIZE(cubeIndices);

	D3D11_SUBRESOURCE_DATA indexBufferData = {0};
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDescGI(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDescGI,
			&indexBufferData,
			&m_indexBuffer
			)
		);

	// Once both shaders are loaded, create the mesh.
	float f_XScale2 = 1.0f / 1.0f;
	float f_YScale2 = 1.0f / 1.0f;

	// Load mesh vertices. Each vertex has a position and a color.
	static const VertexPositionColor cubeVertices2[] = 
		{
		{XMFLOAT3(-0.5f * f_XScale2, -0.5f * f_YScale2, -0.6f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-0.5f * f_XScale2, -0.5f * f_YScale2,  0.6f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
		{XMFLOAT3(-0.5f * f_XScale2,  0.5f * f_YScale2, -0.6f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-0.5f * f_XScale2,  0.5f * f_YScale2,  0.6f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{XMFLOAT3( 0.5f * f_XScale2, -0.5f * f_YScale2, -0.6f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 0.5f * f_XScale2, -0.5f * f_YScale2,  0.6f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3( 0.5f * f_XScale2,  0.5f * f_YScale2, -0.6f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{XMFLOAT3( 0.5f * f_XScale2,  0.5f * f_YScale2,  0.6f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
		};

	D3D11_SUBRESOURCE_DATA vertexBufferData2 = {0};
	vertexBufferData2.pSysMem = cubeVertices2;
	vertexBufferData2.SysMemPitch = 0;
	vertexBufferData2.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDescSW(sizeof(cubeVertices2), D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDescSW,
			&vertexBufferData2,
			&m_COMvertexBuffer
			)
		);

	// Load mesh indices. Each trio of indices represents
	// a triangle to be rendered on the screen.
	// For example: 0,2,1 means that the vertices with indexes
	// 0, 2 and 1 from the vertex buffer compose the 
	// first triangle of this mesh.
	static const unsigned short cubeIndices2 [] =
		{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
		};

	m_indexCount = ARRAYSIZE(cubeIndices2);

	D3D11_SUBRESOURCE_DATA indexBufferData2 = {0};
	indexBufferData2.pSysMem = cubeIndices2;
	indexBufferData2.SysMemPitch = 0;
	indexBufferData2.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDescIB(sizeof(cubeIndices2), D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDescIB,
			&indexBufferData2,
			&m_COMindexBuffer
			)
		);

	// Once both shaders are loaded, create the mesh.
	float f_XScale3 = 3.0f;
	float f_YScale3 = 0.5f;
	float f_X = 0.0;
	float f_Y = 2.0;

	 //////////////////////
	// Add One Wire
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Wire");
	std::shared_ptr<QcomWire> f_Wire = std::make_shared<QcomWire>();

	f_Wire->m_Xmin = 0.0f;
	f_Wire->m_Ymin = 0.0f;
	f_Wire->m_Xmax = 1.0f;
	f_Wire->m_Ymax = 1.0f;

	f_Wire->m_Length = f_XScale3;
	f_Wire->m_Height = f_YScale3;

	// Load mesh vertices. Each vertex has a position and a color.
	static const VertexPositionColor cubeVertices3[] = 
		{
		{XMFLOAT3((-0.5f * f_XScale3) + f_X, (-0.5f * f_YScale3) + f_Y, -0.6f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{XMFLOAT3((-0.5f * f_XScale3) + f_X, (-0.5f * f_YScale3) + f_Y,  0.6f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
		{XMFLOAT3((-0.5f * f_XScale3) + f_X,  (0.5f * f_YScale3) + f_Y, -0.6f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
		{XMFLOAT3((-0.5f * f_XScale3) + f_X,  (0.5f * f_YScale3) + f_Y,  0.6f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{XMFLOAT3( (0.5f * f_XScale3) + f_X, (-0.5f * f_YScale3) + f_Y, -0.6f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( (0.5f * f_XScale3) + f_X, (-0.5f * f_YScale3) + f_Y,  0.6f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3( (0.5f * f_XScale3) + f_X,  (0.5f * f_YScale3) + f_Y, -0.6f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{XMFLOAT3( (0.5f * f_XScale3) + f_X,  (0.5f * f_YScale3) + f_Y,  0.6f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
		};

	for(int f_Helly = 0; f_Helly < 16; f_Helly+=2)
		{
		f_Wire->m_vec_Vertice.push_back(BiVector(cubeVertices[f_Helly].pos.x, cubeVertices[f_Helly].pos.y, cubeVertices[f_Helly].pos.z));
		f_Wire->m_vec_Color.push_back(BiVector(cubeVertices[f_Helly + 1].color.x, cubeVertices[f_Helly + 1].color.y, cubeVertices[f_Helly + 1].color.z));
		}

	D3D11_SUBRESOURCE_DATA vertexBufferData3 = {0};
	vertexBufferData3.pSysMem = cubeVertices3;
	vertexBufferData3.SysMemPitch = 0;
	vertexBufferData3.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDescFG(sizeof(cubeVertices3), D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDescFG,
			&vertexBufferData3,
			&f_Wire->m_curvevertexBuffer
			)
		);

	// Load mesh indices. Each trio of indices represents
	// a triangle to be rendered on the screen.
	// For example: 0,2,1 means that the vertices with indexes
	// 0, 2 and 1 from the vertex buffer compose the 
	// first triangle of this mesh.
	static const unsigned short cubeIndices3 [] =
		{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
		};

	f_Wire->m_indexCount = ARRAYSIZE(cubeIndices3);

	D3D11_SUBRESOURCE_DATA indexBufferData4 = {0};
	indexBufferData4.pSysMem = cubeIndices3;
	indexBufferData4.SysMemPitch = 0;
	indexBufferData4.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDescFR(sizeof(cubeIndices3), D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDescFR,
			&indexBufferData4,
			&f_Wire->m_curveindexBuffer
			)
		);

	g_QcomManager->m_vec_ComWire.push_back(f_Wire);

	float f_XScale4 = 10.0f;
	float f_YScale4 = 0.3f;
	float f_X4 = -4.0;
	float f_Y4 = 2.0;

	 //////////////////////
	// Add One Wire
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Wire2");
	std::shared_ptr<QcomWire> f_Wire2 = std::make_shared<QcomWire>();

	f_Wire2->m_Xmin = 0.0f;
	f_Wire2->m_Ymin = 0.0f;
	f_Wire2->m_Xmax = 1.0f;
	f_Wire2->m_Ymax = 1.0f;

	f_Wire2->m_Length = f_XScale4;
	f_Wire2->m_Height = f_YScale4;

	// Load mesh vertices. Each vertex has a position and a color.
	static const VertexPositionColor cubeVertices21[] = 
		{
		{XMFLOAT3((-0.5f * f_XScale4) + f_X4, (-0.5f * f_YScale4) + f_Y4, -0.6f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{XMFLOAT3((-0.5f * f_XScale4) + f_X4, (-0.5f * f_YScale4) + f_Y4,  0.6f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
		{XMFLOAT3((-0.5f * f_XScale4) + f_X4,  (0.5f * f_YScale4) + f_Y4, -0.6f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
		{XMFLOAT3((-0.5f * f_XScale4) + f_X4,  (0.5f * f_YScale4) + f_Y4,  0.6f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{XMFLOAT3( (0.5f * f_XScale4) + f_X4, (-0.5f * f_YScale4) + f_Y4, -0.6f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( (0.5f * f_XScale4) + f_X4, (-0.5f * f_YScale4) + f_Y4,  0.6f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3( (0.5f * f_XScale4) + f_X4,  (0.5f * f_YScale4) + f_Y4, -0.6f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{XMFLOAT3( (0.5f * f_XScale4) + f_X4,  (0.5f * f_YScale4) + f_Y4,  0.6f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
		};

	for(int f_Helly = 0; f_Helly < 16; f_Helly+=2)
		{
		f_Wire2->m_vec_Vertice.push_back(BiVector(cubeVertices21[f_Helly].pos.x, cubeVertices21[f_Helly].pos.y, cubeVertices21[f_Helly].pos.z));
		f_Wire2->m_vec_Color.push_back(BiVector(cubeVertices21[f_Helly + 1].color.x, cubeVertices21[f_Helly + 1].color.y, cubeVertices21[f_Helly + 1].color.z));
		}

	D3D11_SUBRESOURCE_DATA vertexBufferData21 = {0};
	vertexBufferData21.pSysMem = cubeVertices21;
	vertexBufferData21.SysMemPitch = 0;
	vertexBufferData21.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc21(sizeof(cubeVertices21), D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc21,
			&vertexBufferData21,
			&f_Wire2->m_curvevertexBuffer
			)
		);

	// Load mesh indices. Each trio of indices represents
	// a triangle to be rendered on the screen.
	// For example: 0,2,1 means that the vertices with indexes
	// 0, 2 and 1 from the vertex buffer compose the 
	// first triangle of this mesh.
	static const unsigned short cubeIndices24 [] =
		{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
		};

	f_Wire2->m_indexCount = ARRAYSIZE(cubeIndices24);

	D3D11_SUBRESOURCE_DATA indexBufferData24 = {0};
	indexBufferData24.pSysMem = cubeIndices24;
	indexBufferData24.SysMemPitch = 0;
	indexBufferData24.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc24(sizeof(cubeIndices24), D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDesc24,
			&indexBufferData24,
			&f_Wire2->m_curveindexBuffer
			)
		);

	g_QcomManager->m_vec_ComWire.push_back(f_Wire2);

	m_COMloadingComplete = true;
	m_curveloadingComplete = true;

	// Once the cube is loaded, the object is ready to be rendered.
	for(int f_XY = 0; f_XY < g_ADMAX; f_XY++)
		{
		Cube::CubeKEY* f_KEY = new Cube::CubeKEY();

		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bicycle");
		std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared<Cube::CubeBicycle>();

		f_KEY->m_Link = f_Bicycle;

		// Load mesh vertices. Each vertex has a position and a color.
		Cube::BiRand f_BiRand;
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
		std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
		f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
		std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
		f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
		std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
		f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
		std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
		f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
		std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
		f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
		std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
		f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
		std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
		f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
		std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, 0.5f);
		f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
		std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
		std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
		std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
		std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
		std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
		std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
		std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
		std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

		Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

		f_Vector1->acRun_visualminer();
		f_Vector2->acRun_visualminer();
		f_Vector3->acRun_visualminer();
		f_Vector4->acRun_visualminer();
		f_Vector5->acRun_visualminer();
		f_Vector6->acRun_visualminer();
		f_Vector7->acRun_visualminer();
		f_Vector8->acRun_visualminer();

#if 1
		f_Vector1->acResolve_precision(SCP_FLT_SCALE);
		f_Vector2->acResolve_precision(SCP_FLT_SCALE);
		f_Vector3->acResolve_precision(SCP_FLT_SCALE);
		f_Vector4->acResolve_precision(SCP_FLT_SCALE);
		f_Vector5->acResolve_precision(SCP_FLT_SCALE);
		f_Vector6->acResolve_precision(SCP_FLT_SCALE);
		f_Vector7->acResolve_precision(SCP_FLT_SCALE);
		f_Vector8->acResolve_precision(SCP_FLT_SCALE);
#endif

		f_KEY->m_Link->vec_Vertex.push_back(f_Vector1);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector2);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector3);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector4);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector5);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector6);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector7);
		f_KEY->m_Link->vec_Vertex.push_back(f_Vector8);

		f_KEY->m_Link->vec_Color.push_back(f_Color1);
		f_KEY->m_Link->vec_Color.push_back(f_Color2);
		f_KEY->m_Link->vec_Color.push_back(f_Color3);
		f_KEY->m_Link->vec_Color.push_back(f_Color4);
		f_KEY->m_Link->vec_Color.push_back(f_Color5);
		f_KEY->m_Link->vec_Color.push_back(f_Color6);
		f_KEY->m_Link->vec_Color.push_back(f_Color7);
		f_KEY->m_Link->vec_Color.push_back(f_Color8);

		static const VertexPositionColor cubeVertices6[] =
			{
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			};

		D3D11_SUBRESOURCE_DATA vertexBufferData6 = { 0 };
		vertexBufferData6.pSysMem = cubeVertices6;
		vertexBufferData6.SysMemPitch = 0;
		vertexBufferData6.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDescSA(sizeof(cubeVertices6), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&vertexBufferDescSA,
				&vertexBufferData6,
				&f_KEY->m_Link->m_vertexBuffer
				)
			);

		static const unsigned short cubeIndices6[] =
			{
			0,2,1, // -x
			1,2,3,

			4,5,6, // +x
			5,7,6,

			0,1,5, // -y
			0,5,4,

			2,6,7, // +y
			2,7,3,

			0,4,6, // -z
			0,6,2,

			1,3,7, // +z
			1,7,5,
			};

		f_KEY->m_Link->m_indexCount = ARRAYSIZE(cubeIndices6);

		D3D11_SUBRESOURCE_DATA indexBufferData7 = { 0 };
		indexBufferData7.pSysMem = cubeIndices6;
		indexBufferData7.SysMemPitch = 0;
		indexBufferData7.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDescAS(sizeof(cubeIndices6), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&indexBufferDescAS,
				&indexBufferData7,
				&f_KEY->m_Link->m_indexBuffer
				)
			);

		Cube::g_BicycleContainer[0].vec_Key.push_back(f_KEY);
		}

	m_loadingComplete = true;
}

void Sample3DSceneRenderer::acCreateAdmaxDependentResources(void)
{
	g_ref_CurrentPath = "Sample3DSceneRenderer::acCreateAdmaxDependentResources";

	if(Cube::g_BicycleContainer[0].vec_Key.size() < g_ADMAX)
		{
		while(Cube::g_BicycleContainer[0].vec_Key.size() < g_ADMAX)
			{
			// Once the cube is loaded, the object is ready to be rendered.
			Cube::CubeKEY* f_KEY = new Cube::CubeKEY();

			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bicycle");
			std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared<Cube::CubeBicycle>();

			f_KEY->m_Link = f_Bicycle;

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
			std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
			f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
			std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
			f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
			std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
			f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
			std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
			f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
			std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
			f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
			std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
			f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
			std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
			f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
			std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, 0.5f);
			f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
			std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
			std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
			std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
			std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
			std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
			std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
			std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
			std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1->acRun_visualminer();
			f_Vector2->acRun_visualminer();
			f_Vector3->acRun_visualminer();
			f_Vector4->acRun_visualminer();
			f_Vector5->acRun_visualminer();
			f_Vector6->acRun_visualminer();
			f_Vector7->acRun_visualminer();
			f_Vector8->acRun_visualminer();

#if 1
			f_Vector1->acResolve_precision(SCP_FLT_SCALE);
			f_Vector2->acResolve_precision(SCP_FLT_SCALE);
			f_Vector3->acResolve_precision(SCP_FLT_SCALE);
			f_Vector4->acResolve_precision(SCP_FLT_SCALE);
			f_Vector5->acResolve_precision(SCP_FLT_SCALE);
			f_Vector6->acResolve_precision(SCP_FLT_SCALE);
			f_Vector7->acResolve_precision(SCP_FLT_SCALE);
			f_Vector8->acResolve_precision(SCP_FLT_SCALE);
#endif

			f_KEY->m_Link->vec_Vertex.push_back(f_Vector1);
			f_KEY->m_Link->vec_Vertex.push_back(f_Vector2);
			f_KEY->m_Link->vec_Vertex.push_back(f_Vector3);
			f_KEY->m_Link->vec_Vertex.push_back(f_Vector4);
			f_KEY->m_Link->vec_Vertex.push_back(f_Vector5);
			f_KEY->m_Link->vec_Vertex.push_back(f_Vector6);
			f_KEY->m_Link->vec_Vertex.push_back(f_Vector7);
			f_KEY->m_Link->vec_Vertex.push_back(f_Vector8);

			f_KEY->m_Link->vec_Color.push_back(f_Color1);
			f_KEY->m_Link->vec_Color.push_back(f_Color2);
			f_KEY->m_Link->vec_Color.push_back(f_Color3);
			f_KEY->m_Link->vec_Color.push_back(f_Color4);
			f_KEY->m_Link->vec_Color.push_back(f_Color5);
			f_KEY->m_Link->vec_Color.push_back(f_Color6);
			f_KEY->m_Link->vec_Color.push_back(f_Color7);
			f_KEY->m_Link->vec_Color.push_back(f_Color8);

			static const VertexPositionColor cubeVertices6[] =
				{
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
				};

			D3D11_SUBRESOURCE_DATA vertexBufferData6 = { 0 };
			vertexBufferData6.pSysMem = cubeVertices6;
			vertexBufferData6.SysMemPitch = 0;
			vertexBufferData6.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDescSA(sizeof(cubeVertices6), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&vertexBufferDescSA,
					&vertexBufferData6,
					&f_KEY->m_Link->m_vertexBuffer
					)
				);

			static const unsigned short cubeIndices6[] =
				{
				0,2,1, // -x
				1,2,3,

				4,5,6, // +x
				5,7,6,

				0,1,5, // -y
				0,5,4,

				2,6,7, // +y
				2,7,3,

				0,4,6, // -z
				0,6,2,

				1,3,7, // +z
				1,7,5,
				};

			f_KEY->m_Link->m_indexCount = ARRAYSIZE(cubeIndices6);

			D3D11_SUBRESOURCE_DATA indexBufferData7 = { 0 };
			indexBufferData7.pSysMem = cubeIndices6;
			indexBufferData7.SysMemPitch = 0;
			indexBufferData7.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDescAS(sizeof(cubeIndices6), D3D11_BIND_INDEX_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&indexBufferDescAS,
					&indexBufferData7,
					&f_KEY->m_Link->m_indexBuffer
					)
				);

			Cube::g_BicycleContainer[0].vec_Key.push_back(f_KEY);
			}
		}
	else if(Cube::g_BicycleContainer[0].vec_Key.size() > g_ADMAX)
		{
		int f_CountIndex = Cube::g_BicycleContainer[0].vec_Key.size() - 1;

		while(Cube::g_BicycleContainer[0].vec_Key.size() > g_ADMAX)
			{
			Cube::CubeKEY* f_Key = Cube::g_BicycleContainer[0].vec_Key[f_CountIndex];

			f_Key->m_Link->m_vertexBuffer.Reset();
			f_Key->m_Link->m_indexBuffer.Reset();
			f_Key->m_Link->vec_Vertex.clear();
			f_Key->m_Link->vec_Color.clear();

			delete Cube::g_BicycleContainer[0].vec_Key[f_CountIndex];
			Cube::g_BicycleContainer[0].vec_Key.pop_back();

			f_CountIndex--;
			}
		}
}

struct VertexBufferType
{
	XMFLOAT3 vertex[16];
};

#ifdef SCP_REFLECT
void Sample3DSceneRenderer::acSaveCompletePublish_GenHesh(void)
{
	g_ref_CurrentPath = "Sample3DSceneRenderer::acSaveCompletePublish_GenHesh";
	bool f_OCP_LOCK_ON = false;

	m_DB_AccessLock.lock();
	f_OCP_LOCK_ON = true;

	int f_OCSCP_ThreadIndex = g_OCSCP_ThreadCount;

	g_OCSCP_ThreadCount++;

	g_ElementDivisor.push_back(0);
	g_ElementDivisorInt.push_back(0);

	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "g_classLMap->m_SchemaRef");
	g_classLMap->m_SchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "g_classLMap->m_SaveSchemaRef");
	g_classLMap->m_SaveSchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_SchemaMeasureIndex.push_back(0);
	g_classLMap->m_CPS_Result.push_back(CPS_SCAN);

	m_DB_AccessLock.unlock();
	f_OCP_LOCK_ON = false;

	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "g_classLMap->m_SaveSchemaRef");
	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared<Cube::CubeHESH>(g_classLMap->m_ADMAX, g_classLMap->m_ADHIGH, g_classLMap->m_ADLOW);
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "g_classLMap->m_SaveSchemaRef");
	std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared<Cube::CubeHASH_originstring>();
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "g_classLMap->m_SaveSchemaRef");
	std::shared_ptr<classCollection> f_Collection = std::make_shared<classCollection>();

	while(g_Compressing == 1)
		{
		int f_SizeMin = f_Collection->m_vec_Element.size();

		for(int f_XYZ = f_Collection->m_vec_Element.size() - 1; f_XYZ >= 0; f_XYZ--)
			{
			if(f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag == false)
				{
				f_SizeMin = f_XYZ;
				}
			}

		if(f_SizeMin < 0)
			{
			f_SizeMin = 0;
			}

		while(f_Hesh_Cade->vec_Bicycle.size() > f_SizeMin)
			{
			f_Hesh_Cade->vec_Bicycle.pop_back();
			f_Hesh_Cade->m_adIndex.pop_back();
			f_Collection->m_vec_Element.pop_back();
			f_Collection->m_idx_vec_Element--;
			}

		if(g_LowtonOn == true)
			{
			int f_FingerBike = f_SizeMin;

			while(f_Hesh_Cade->vec_Bicycle.size() < g_Lowton->vec_Bicycle.size())
				{
				//make bike clone
				std::shared_ptr<CubeBicycle> f_WonBike = g_Lowton->vec_Bicycle[f_FingerBike];

				// Load mesh vertices. Each vertex has a position and a color.
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
				std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[0]->m_X, f_WonBike->vec_Vertex[0]->m_Y, f_WonBike->vec_Vertex[0]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
				std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[1]->m_X, f_WonBike->vec_Vertex[1]->m_Y, f_WonBike->vec_Vertex[1]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
				std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[2]->m_X, f_WonBike->vec_Vertex[2]->m_Y, f_WonBike->vec_Vertex[2]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
				std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[3]->m_X, f_WonBike->vec_Vertex[3]->m_Y, f_WonBike->vec_Vertex[3]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
				std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[4]->m_X, f_WonBike->vec_Vertex[4]->m_Y, f_WonBike->vec_Vertex[4]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
				std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[5]->m_X, f_WonBike->vec_Vertex[5]->m_Y, f_WonBike->vec_Vertex[5]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
				std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[6]->m_X, f_WonBike->vec_Vertex[6]->m_Y, f_WonBike->vec_Vertex[6]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
				std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[7]->m_X, f_WonBike->vec_Vertex[7]->m_Y, f_WonBike->vec_Vertex[7]->m_Z);

				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
				std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[0]->m_X, f_WonBike->vec_Color[0]->m_Y, f_WonBike->vec_Color[0]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
				std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[1]->m_X, f_WonBike->vec_Color[1]->m_Y, f_WonBike->vec_Color[1]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
				std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[2]->m_X, f_WonBike->vec_Color[2]->m_Y, f_WonBike->vec_Color[2]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
				std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[3]->m_X, f_WonBike->vec_Color[3]->m_Y, f_WonBike->vec_Color[3]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
				std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[4]->m_X, f_WonBike->vec_Color[4]->m_Y, f_WonBike->vec_Color[4]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
				std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[5]->m_X, f_WonBike->vec_Color[5]->m_Y, f_WonBike->vec_Color[5]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
				std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[6]->m_X, f_WonBike->vec_Color[6]->m_Y, f_WonBike->vec_Color[6]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
				std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[7]->m_X, f_WonBike->vec_Color[7]->m_Y, f_WonBike->vec_Color[7]->m_Z);

				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bike");
				std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>();

				f_Bike->vec_Vertex.push_back(f_Vector1);
				f_Bike->vec_Vertex.push_back(f_Vector2);
				f_Bike->vec_Vertex.push_back(f_Vector3);
				f_Bike->vec_Vertex.push_back(f_Vector4);
				f_Bike->vec_Vertex.push_back(f_Vector5);
				f_Bike->vec_Vertex.push_back(f_Vector6);
				f_Bike->vec_Vertex.push_back(f_Vector7);
				f_Bike->vec_Vertex.push_back(f_Vector8);

				f_Bike->vec_Color.clear();

				f_Bike->vec_Color.push_back(f_Color1);
				f_Bike->vec_Color.push_back(f_Color2);
				f_Bike->vec_Color.push_back(f_Color3);
				f_Bike->vec_Color.push_back(f_Color4);
				f_Bike->vec_Color.push_back(f_Color5);
				f_Bike->vec_Color.push_back(f_Color6);
				f_Bike->vec_Color.push_back(f_Color7);
				f_Bike->vec_Color.push_back(f_Color8);

				f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

				f_Hesh_Cade->m_adIndex.push_back(g_Lowton->m_adIndex[f_FingerBike]);

				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Element");
				std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Bike);

				f_Collection->m_vec_Element.push_back(f_Element);
				f_Collection->m_idx_vec_Element++;

				f_FingerBike++;
				}
			}

		for(int f_Int = f_Hesh_Cade->vec_Bicycle.size(); f_Int < g_classLMap->m_ADMAX; f_Int++)
			{
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bike");
			std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>();

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
			std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
			f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
			std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
			f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
			std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
			f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
			std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
			f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
			std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
			f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
			std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
			f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
			std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
			f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
			std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f);
			f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
			std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
			std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
			std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
			std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
			std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
			std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
			std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
			std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1->acRun_visualminer();
			f_Vector2->acRun_visualminer();
			f_Vector3->acRun_visualminer();
			f_Vector4->acRun_visualminer();
			f_Vector5->acRun_visualminer();
			f_Vector6->acRun_visualminer();
			f_Vector7->acRun_visualminer();
			f_Vector8->acRun_visualminer();

#if 1
			f_Vector1->acResolve_precision();
			f_Vector2->acResolve_precision();
			f_Vector3->acResolve_precision();
			f_Vector4->acResolve_precision();
			f_Vector5->acResolve_precision();
			f_Vector6->acResolve_precision();
			f_Vector7->acResolve_precision();
			f_Vector8->acResolve_precision();
#endif

			f_Bike->vec_Vertex.push_back(f_Vector1);
			f_Bike->vec_Vertex.push_back(f_Vector2);
			f_Bike->vec_Vertex.push_back(f_Vector3);
			f_Bike->vec_Vertex.push_back(f_Vector4);
			f_Bike->vec_Vertex.push_back(f_Vector5);
			f_Bike->vec_Vertex.push_back(f_Vector6);
			f_Bike->vec_Vertex.push_back(f_Vector7);
			f_Bike->vec_Vertex.push_back(f_Vector8);

			f_Bike->vec_Color.clear();

			f_Bike->vec_Color.push_back(f_Color1);
			f_Bike->vec_Color.push_back(f_Color2);
			f_Bike->vec_Color.push_back(f_Color3);
			f_Bike->vec_Color.push_back(f_Color4);
			f_Bike->vec_Color.push_back(f_Color5);
			f_Bike->vec_Color.push_back(f_Color6);
			f_Bike->vec_Color.push_back(f_Color7);
			f_Bike->vec_Color.push_back(f_Color8);

			f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Element");
			std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Bike);

			f_Collection->m_vec_Element.push_back(f_Element);
			f_Collection->m_idx_vec_Element++;
			}

		//hesh admax limiter
#ifndef ECOIN_ADMAX_MAX
		float f_Finger = Cube::random();
		float f_LimitSenseFLT = (((float)f_Hesh_Cade->m_ADMAX - ECOIN_HESH_MINIMUM) * f_Finger) + ECOIN_HESH_MINIMUM;
		int f_LimitSense = (int)f_LimitSenseFLT;
#else
		int f_LimitSense = g_classLMap->m_ADMAX;
#endif

		int f_PORTcntr = f_Hesh_Cade->m_adIndex.size();

		while(f_Hesh_Cade->m_adIndex.size() < f_LimitSense)
			{
			f_Hesh_Cade->m_adIndex.push_back(f_PORTcntr);
			f_PORTcntr++;
			}

		Cube::BiVector f_ColorBCK(Cube::random(), Cube::random(), Cube::random());

		f_Hesh_Cade->m_bckred = f_ColorBCK.m_X;
		f_Hesh_Cade->m_bckgreen = f_ColorBCK.m_Y;
		f_Hesh_Cade->m_bckblue = f_ColorBCK.m_Z;

		f_Hesh_Cade->ac_IsOK();

		g_ElementCount += f_Hesh_Cade->m_adIndex.size();

		  ////////////
		 // HESH   //
		// Target //
		if(g_Result == false)
			{
			g_Result = g_classLMap->acCompute(f_Collection, f_OCSCP_ThreadIndex);

			   ////////////
			  // Save
			 // Hash
			// Result
			if((g_Result == true) && 0)
				{
				int f_ShareID = 1;
				int f_BlockID = 1;
				int f_JobID = 1;
				int f_EslID = 1;
				int f_TargetID = 1;
				float f_Difficulty = ECOIN_TARGET_COMPARE_THRESH; //Target Mark Threshold

				m_DB_AccessLock.lock();
				f_OCP_LOCK_ON = true;

#if 0
				for(int f_XY = 0; f_XY < g_classLMap->m_vec_Ecom.size(); f_XY++)
					{
					gf_Target_3->m_vec_Ecom.push_back(g_classLMap->m_vec_Ecom[f_XY]);
					}
#endif

				f_Hesh_Cade->m_Hash = f_Hash;

				char* g_sharevalue[60];

				for(int f_Count = 0; f_Count < 60; f_Count++)
					{
					g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
					}

				std::sprintf(g_sharevalue[0], "%f", 1.0f * (float)g_OCSCP_LowtonMark);
				std::sprintf(g_sharevalue[1], "%i", 1);
				std::sprintf(g_sharevalue[2], "%s", "3");
				std::sprintf(g_sharevalue[4], "%i", f_EslID);
				std::sprintf(g_sharevalue[5], "%i", f_TargetID);
				std::sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
				std::sprintf(g_sharevalue[7], "%f", f_Difficulty);

				f_Hash->acClear();

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					for(int f_Helly = 0; f_Helly < 8; f_Helly++)
						{
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					for(int f_Helly = 0; f_Helly < 8; f_Helly++)
						{
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					f_Hash->acPushInt(f_Hesh_Cade->m_adIndex[f_Jet]);
					}

				   ////////////
				  // Hash
				 //
				//
				std::string f_InputHash = f_Hash->acGetInput();

				// check GenesisBlock (assume)
				std::string f_previousblock = "00000000000000000000000000000001";
				//ECN::Hesh...Checking Previous BlockHesh.

				char blokquery[1000];
				::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

				g_SafeL[0]->acSelectCommand(blokquery, 2, false);

				int f_blokLCount = 0;

				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
					{
					f_blokLCount = 0;
					}
				else
					{
					f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
					}

				//ECN::Stat::: f_TrxLCount f_blokLCount
				g_JobID = 0;

				if(f_blokLCount > 0)
					{
					g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
					g_JobID++;
					f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
					}

				f_JobID = g_JobID;

				::sprintf(g_sharevalue[3], "%i", f_JobID);

				//ECN::Stat::: f_tx - f_JobID
				std::string f_tx = ag_GatherTransactions(g_JobID);

				std::string f_job = f_tx + f_previousblock;

				f_InputHash += f_job;

#if 1
				g_hasha.init(); //reset hasher state
				g_hasha.process(f_InputHash.begin(), f_InputHash.end());
				g_hasha.finish();
				picosha2::get_hash_hex_string(g_hasha, f_Hash->m_OutputHash);
#else
				f_Hash->m_OutputHash = "00000000000000000000000000000000";
#endif

				f_Hesh_Cade->m_Hash = f_Hash;

				//ShareHash-f_Hash->m_OutputHash
				::sprintf(g_sharevalue[8], "%i", 0);
				::sprintf(g_sharevalue[9], "%i", 10);
				::sprintf(g_sharevalue[10], "%s", f_Hash->m_OutputHash.c_str());
				::sprintf(g_sharevalue[11], "%s", f_Hash->m_OutputHash.c_str());
				::sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
				::sprintf(g_sharevalue[13], "%f", f_Hesh_Cade->m_bckred);
				::sprintf(g_sharevalue[14], "%f", f_Hesh_Cade->m_bckgreen);
				::sprintf(g_sharevalue[15], "%f", f_Hesh_Cade->m_bckblue);
				::sprintf(g_sharevalue[16], "%f", 0.0f);

				//ECN::Hesh...Sending BlockHesh
				char shlquery[1000];
				::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Hash->m_OutputHash.c_str());

				g_SafeL[0]->acSelectCommand(shlquery, 2, false);

				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
					{
					int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

					f_ShareID = f_ShareUniqueID;
					g_ShareID = f_ShareID;

					//ECN::Stat::: f_ShareID f_shareuniqueID
					ag_addGenesisTracking(f_ShareUniqueID);
				
					char* f_idquery2 = new char[150];
					::sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

					g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
					delete[] f_idquery2;

					int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
					int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

					g_PEERCNT = f_PEERCNT;
					g_SHARECNT = f_SHARECNT;

					for(int f_Int = 0; f_Int < f_Hesh_Cade->m_adIndex.size(); f_Int++)
						{
						std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[/*f_Hesh_Cade->m_adIndex[*/f_Int/*]*/];

						char* g_cubevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
							}

						for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
							{
							::sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
							::sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
							::sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
							}

						for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
							{
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
							}
				
						::sprintf(g_cubevalue[48], "%i", f_BlockID);
						::sprintf(g_cubevalue[49], "%i", f_ShareID);
						::sprintf(g_cubevalue[50], "%i", f_JobID);
						::sprintf(g_cubevalue[51], "%i", f_Int);
						::sprintf(g_cubevalue[52], "%i", f_TargetID);
						::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
						::sprintf(g_cubevalue[54], "%f", f_Difficulty);

						g_CubeFieldCount = 55;

						int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
						}

					//ECN::Complete Share Submitted
					g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
					f_Ack->m_ECN = 0.0f;
					f_Ack->m_Reward = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = g_Wallet->GetAdr();
					g_Ackent.push_back(f_Ack);

					g_Compressing = 0;
					}
				else //Duplicate Block Found.
					{
					g_Result = false;
					}
				}
			else
				{
				int f_OC_Mark_Count = g_Lowton->vec_Bicycle.size();

				bool f_Scan = true;

				while(f_Scan == true)
					{
					if(f_OC_Mark_Count >= f_Collection->m_vec_Element.size())
						{
						f_Scan = false;
						}
					else
						{
						if(f_Collection->m_vec_Element[f_OC_Mark_Count]->m_OCSCP_Flag == false)
							{
							f_Scan = false;
							}
						else
							{
							f_OC_Mark_Count++;
							}
						}
					}

				if(f_OC_Mark_Count > g_Lowton->vec_Bicycle.size())
					{
					m_DB_AccessLock.lock();
					f_OCP_LOCK_ON = true;

					for(int f_Jet = g_Lowton->vec_Bicycle.size(); f_Jet < f_OC_Mark_Count; f_Jet++)
						{
						//make bike clone
						std::shared_ptr<CubeBicycle> f_WinningBike = f_Hesh_Cade->vec_Bicycle[f_Jet];

						// Load mesh vertices. Each vertex has a position and a color.
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
						std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[0]->m_X, f_WinningBike->vec_Vertex[0]->m_Y, f_WinningBike->vec_Vertex[0]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
						std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[1]->m_X, f_WinningBike->vec_Vertex[1]->m_Y, f_WinningBike->vec_Vertex[1]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
						std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[2]->m_X, f_WinningBike->vec_Vertex[2]->m_Y, f_WinningBike->vec_Vertex[2]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
						std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[3]->m_X, f_WinningBike->vec_Vertex[3]->m_Y, f_WinningBike->vec_Vertex[3]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
						std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[4]->m_X, f_WinningBike->vec_Vertex[4]->m_Y, f_WinningBike->vec_Vertex[4]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
						std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[5]->m_X, f_WinningBike->vec_Vertex[5]->m_Y, f_WinningBike->vec_Vertex[5]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
						std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[6]->m_X, f_WinningBike->vec_Vertex[6]->m_Y, f_WinningBike->vec_Vertex[6]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
						std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[7]->m_X, f_WinningBike->vec_Vertex[7]->m_Y, f_WinningBike->vec_Vertex[7]->m_Z);

						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
						std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[0]->m_X, f_WinningBike->vec_Color[0]->m_Y, f_WinningBike->vec_Color[0]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
						std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[1]->m_X, f_WinningBike->vec_Color[1]->m_Y, f_WinningBike->vec_Color[1]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
						std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[2]->m_X, f_WinningBike->vec_Color[2]->m_Y, f_WinningBike->vec_Color[2]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
						std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[3]->m_X, f_WinningBike->vec_Color[3]->m_Y, f_WinningBike->vec_Color[3]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
						std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[4]->m_X, f_WinningBike->vec_Color[4]->m_Y, f_WinningBike->vec_Color[4]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
						std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[5]->m_X, f_WinningBike->vec_Color[5]->m_Y, f_WinningBike->vec_Color[5]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
						std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[6]->m_X, f_WinningBike->vec_Color[6]->m_Y, f_WinningBike->vec_Color[6]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
						std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[7]->m_X, f_WinningBike->vec_Color[7]->m_Y, f_WinningBike->vec_Color[7]->m_Z);

						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bike");
						std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>();

						f_Bike->vec_Vertex.push_back(f_Vector1);
						f_Bike->vec_Vertex.push_back(f_Vector2);
						f_Bike->vec_Vertex.push_back(f_Vector3);
						f_Bike->vec_Vertex.push_back(f_Vector4);
						f_Bike->vec_Vertex.push_back(f_Vector5);
						f_Bike->vec_Vertex.push_back(f_Vector6);
						f_Bike->vec_Vertex.push_back(f_Vector7);
						f_Bike->vec_Vertex.push_back(f_Vector8);

						f_Bike->vec_Color.clear();

						f_Bike->vec_Color.push_back(f_Color1);
						f_Bike->vec_Color.push_back(f_Color2);
						f_Bike->vec_Color.push_back(f_Color3);
						f_Bike->vec_Color.push_back(f_Color4);
						f_Bike->vec_Color.push_back(f_Color5);
						f_Bike->vec_Color.push_back(f_Color6);
						f_Bike->vec_Color.push_back(f_Color7);
						f_Bike->vec_Color.push_back(f_Color8);

						g_Lowton->vec_Bicycle.push_back(f_Bike);

						g_Lowton->m_adIndex.push_back(/*f_Hesh_Cade->m_adIndex[*/f_Jet/*]*/);

						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Element");
						std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Bike);

						g_Lowton_Collection->m_vec_Element.push_back(f_Element);
						g_Lowton_Collection->m_idx_vec_Element++;

						//?require?g_LowtonTarget_3 = gf_Target_3; < hmm
						}

					g_Lowton->m_bckblue = f_Hesh_Cade->m_bckblue;
					g_Lowton->m_bckred = f_Hesh_Cade->m_bckred;
					g_Lowton->m_bckgreen = f_Hesh_Cade->m_bckgreen;

					g_TargetedHesh = g_Lowton;

					g_TargetedHesh->ac_IsOK();

					g_RenderHesh = true;

#if 0
					bool f_Result = g_classLMap->acCompute(g_Lowton_Collection, f_OCSCP_ThreadIndex, true);

					int f_OC_Lowton_Mark_Count = 0;

					bool f_ScanX = true;

					while(f_ScanX == true)
						{
						if(f_OC_Lowton_Mark_Count >= g_Lowton_Collection->m_vec_Element.size())
							{
							f_ScanX = false;
							}
						else
							{
							if(g_Lowton_Collection->m_vec_Element[f_OC_Lowton_Mark_Count]->m_OCSCP_Flag == false)
								{
								f_ScanX = false;
								}
							else
								{
								f_OC_Lowton_Mark_Count++;
								}
							}
						}
#endif

					if(f_OC_Mark_Count >= g_classLMap->m_ADMAX)
						{
						g_Result = true;

						int f_ShareID = 1;
						int f_BlockID = 1;
						int f_JobID = 1;
						int f_EslID = 1;
						int f_TargetID = 1;
						float f_Difficulty = ECOIN_TARGET_SCP_COMPARE_THRESH; //Target Mark Threshold

						char* g_sharevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
							}

						::sprintf(g_sharevalue[0], "%f", (float)g_Lowton->vec_Bicycle.size());
						::sprintf(g_sharevalue[1], "%i", 1);
						::sprintf(g_sharevalue[2], "%s", "3");
						::sprintf(g_sharevalue[4], "%i", 15);
						::sprintf(g_sharevalue[5], "%i", 15);
						::sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
						::sprintf(g_sharevalue[7], "%f", f_Difficulty);

						g_LowtonHash = f_Hash;

						g_LowtonHash->acClear();

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							g_LowtonHash->acPushInt(g_Lowton->m_adIndex[f_Jet]);
							}

							////////////
						   //
						  // Hash
						 //
						std::string f_InputHash = g_LowtonHash->acGetInput();

						// check GenesisBlock (assume)
						std::string f_previousblock = "00000000000000000000000000000001";
						//ECN::Hesh...Checking Previous BlockHesh

						char blokquery[1000];

						::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

						if(f_OCP_LOCK_ON == false)
							{
							m_DB_AccessLock.lock();
							f_OCP_LOCK_ON = true;
							}

						g_SafeL[0]->acSelectCommand(blokquery, 2, false);

						int f_blokLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_blokLCount = 0;
							}
						else
							{
							f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						g_JobID = 0;

						if(f_blokLCount > 0)
							{
							g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
							g_JobID++;
							f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
							}

						f_JobID = g_JobID;

						::sprintf(g_sharevalue[3], "%i", f_JobID);

						std::string f_tx = ag_GatherTransactions(g_JobID);

						std::string f_job = f_tx + f_previousblock;

						f_InputHash += f_job;

#if 1
						g_hasha.init(); //reset hasher state
						g_hasha.process(f_InputHash.begin(), f_InputHash.end());
						g_hasha.finish();
						picosha2::get_hash_hex_string(g_hasha, g_LowtonHash->m_OutputHash);
#else
						g_LowtonHash->m_OutputHash = "00000000000000000000000000000000";
#endif

						g_Lowton->m_Hash = g_LowtonHash;

						g_LowtonMark = 0;

						::sprintf(g_sharevalue[8], "%i", 0);
						::sprintf(g_sharevalue[9], "%i", 10);
						::sprintf(g_sharevalue[10], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[11], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
						::sprintf(g_sharevalue[13], "%f", g_Lowton->m_bckred);
						::sprintf(g_sharevalue[14], "%f", g_Lowton->m_bckgreen);
						::sprintf(g_sharevalue[15], "%f", g_Lowton->m_bckblue);
						::sprintf(g_sharevalue[16], "%f", 0.0f);

						//ECN::Hesh...Sending BlockHesh
						char shlquery[1000];
						::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", g_LowtonHash->m_OutputHash.c_str());

						g_SafeL[0]->acSelectCommand(shlquery, 2, false);

						int f_ShareLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_ShareLCount = 0;
							}
						else
							{
							f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						if(f_ShareLCount == 0)
							{
							int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

							f_ShareID = f_ShareUniqueID;
							g_ShareID = f_ShareID;

							ag_addGenesisTracking(f_ShareUniqueID);
				
							char* f_idquery2 = new char[150];
							::sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

							g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
							delete[] f_idquery2;

							int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
							int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

							g_PEERCNT = f_PEERCNT;
							g_SHARECNT = f_SHARECNT;

							for(int f_Int = 0; f_Int < g_Lowton->m_adIndex.size(); f_Int++)
								{
								shared_ptr<CubeBicycle> f_Bike = g_Lowton->vec_Bicycle[/*g_Lowton->m_adIndex[*/f_Int/*]*/];

								char* g_cubevalue[60];

								for(int f_Count = 0; f_Count < 60; f_Count++)
									{
									g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
									}

								for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
									{
									::sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
									::sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
									::sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
									}

								for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
									{
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
									}
				
								::sprintf(g_cubevalue[48], "%i", f_BlockID);
								::sprintf(g_cubevalue[49], "%i", f_ShareID);
								::sprintf(g_cubevalue[50], "%i", f_JobID);
								::sprintf(g_cubevalue[51], "%i", f_Int);
								::sprintf(g_cubevalue[52], "%i", 1);	// FIXME ADD L-TARGETID
								::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
								::sprintf(g_cubevalue[54], "%f", f_Difficulty);

								g_CubeFieldCount = 55;

								int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
								}

							// ECN::Lowton Share Submitted
							g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Ack");
							std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
							f_Ack->m_ECN = 0.0f;
							f_Ack->m_Reward = 50.0f;
							f_Ack->m_Origin = 1;
							f_Ack->m_Owner = g_Wallet->GetAdr();
							g_Ackent.push_back(f_Ack);

							g_Compressing = 0;
							}
						else // Duplicate Block Found.
							{
							g_Result = false;
							}
						}
					}
				}
			}

		if(f_OCP_LOCK_ON == true)
			{
			m_DB_AccessLock.unlock();
			f_OCP_LOCK_ON = false;
			}
		}

	 ///////////////////////////////////////////////////
	// not safe for multiple miner windows open on
	g_ElementDivisor.pop_back();
	g_ElementDivisorInt.pop_back();

	g_classLMap->m_SchemaRef.pop_back();
	g_classLMap->m_SaveSchemaRef.pop_back();
	g_classLMap->m_SchemaMeasureIndex.pop_back();
	g_classLMap->m_CPS_Result.pop_back();
}

void Sample3DSceneRenderer::acSaveCompletePublish_GenHesh_Upper(void)
{
	g_ref_CurrentPath = "Sample3DSceneRenderer::acSaveCompletePublish_GenHesh_Upper";
	bool f_OCP_LOCK_ON = false;

	m_DB_AccessLock.lock();
	f_OCP_LOCK_ON = true;

	int f_OCSCP_ThreadIndex = g_OCSCP_ThreadCount;

	g_OCSCP_ThreadCount++;

	g_ElementDivisor.push_back(0);
	g_ElementDivisorInt.push_back(0);

	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "g_classLMap->m_SchemaRef");
	g_classLMap->m_SchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));

	m_DB_AccessLock.unlock();
	f_OCP_LOCK_ON = false;

	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Hesh_Cade");
	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared<Cube::CubeHESH>(g_classLMap->m_ADMAX, g_classLMap->m_ADHIGH, g_classLMap->m_ADLOW);
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Hash");
	std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared<Cube::CubeHASH_originstring>();
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Collection");
	std::shared_ptr<classCollection> f_Collection = std::make_shared<classCollection>();

	while(g_Compressing == 1)
		{
		int f_SizeMin = f_Collection->m_vec_Element.size();

		for(int f_XYZ = f_Collection->m_vec_Element.size() - 1; f_XYZ >= 0; f_XYZ--)
			{
			if(f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag == false)
				{
				f_SizeMin = f_XYZ;
				}
			}

		if(f_SizeMin < 0)
			{
			f_SizeMin = 0;
			}

		while(f_Hesh_Cade->vec_Bicycle.size() > f_SizeMin)
			{
			f_Hesh_Cade->vec_Bicycle.pop_back();
			f_Hesh_Cade->m_adIndex.pop_back();
			f_Collection->m_vec_Element.pop_back();
			f_Collection->m_idx_vec_Element--;
			}

		if(g_LowtonOn == true)
			{
			int f_FingerBike = f_SizeMin;

			while(f_Hesh_Cade->vec_Bicycle.size() < g_Lowton->vec_Bicycle.size())
				{
				//make bike clone
				std::shared_ptr<CubeBicycle> f_WonBike = g_Lowton->vec_Bicycle[f_FingerBike];

				// Load mesh vertices. Each vertex has a position and a color.
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
				std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[0]->m_X, f_WonBike->vec_Vertex[0]->m_Y, f_WonBike->vec_Vertex[0]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
				std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[1]->m_X, f_WonBike->vec_Vertex[1]->m_Y, f_WonBike->vec_Vertex[1]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
				std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[2]->m_X, f_WonBike->vec_Vertex[2]->m_Y, f_WonBike->vec_Vertex[2]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
				std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[3]->m_X, f_WonBike->vec_Vertex[3]->m_Y, f_WonBike->vec_Vertex[3]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
				std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[4]->m_X, f_WonBike->vec_Vertex[4]->m_Y, f_WonBike->vec_Vertex[4]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
				std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[5]->m_X, f_WonBike->vec_Vertex[5]->m_Y, f_WonBike->vec_Vertex[5]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
				std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[6]->m_X, f_WonBike->vec_Vertex[6]->m_Y, f_WonBike->vec_Vertex[6]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
				std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[7]->m_X, f_WonBike->vec_Vertex[7]->m_Y, f_WonBike->vec_Vertex[7]->m_Z);

				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
				std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[0]->m_X, f_WonBike->vec_Color[0]->m_Y, f_WonBike->vec_Color[0]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
				std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[1]->m_X, f_WonBike->vec_Color[1]->m_Y, f_WonBike->vec_Color[1]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
				std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[2]->m_X, f_WonBike->vec_Color[2]->m_Y, f_WonBike->vec_Color[2]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
				std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[3]->m_X, f_WonBike->vec_Color[3]->m_Y, f_WonBike->vec_Color[3]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
				std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[4]->m_X, f_WonBike->vec_Color[4]->m_Y, f_WonBike->vec_Color[4]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
				std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[5]->m_X, f_WonBike->vec_Color[5]->m_Y, f_WonBike->vec_Color[5]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
				std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[6]->m_X, f_WonBike->vec_Color[6]->m_Y, f_WonBike->vec_Color[6]->m_Z);
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
				std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[7]->m_X, f_WonBike->vec_Color[7]->m_Y, f_WonBike->vec_Color[7]->m_Z);
				
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bike");
				std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>();

				f_Bike->vec_Vertex.push_back(f_Vector1);
				f_Bike->vec_Vertex.push_back(f_Vector2);
				f_Bike->vec_Vertex.push_back(f_Vector3);
				f_Bike->vec_Vertex.push_back(f_Vector4);
				f_Bike->vec_Vertex.push_back(f_Vector5);
				f_Bike->vec_Vertex.push_back(f_Vector6);
				f_Bike->vec_Vertex.push_back(f_Vector7);
				f_Bike->vec_Vertex.push_back(f_Vector8);

				f_Bike->vec_Color.clear();

				f_Bike->vec_Color.push_back(f_Color1);
				f_Bike->vec_Color.push_back(f_Color2);
				f_Bike->vec_Color.push_back(f_Color3);
				f_Bike->vec_Color.push_back(f_Color4);
				f_Bike->vec_Color.push_back(f_Color5);
				f_Bike->vec_Color.push_back(f_Color6);
				f_Bike->vec_Color.push_back(f_Color7);
				f_Bike->vec_Color.push_back(f_Color8);

				f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

				f_Hesh_Cade->m_adIndex.push_back(g_Lowton->m_adIndex[f_FingerBike]);

				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Element");
				std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Bike);

				f_Collection->m_vec_Element.push_back(f_Element);
				f_Collection->m_idx_vec_Element++;

				f_FingerBike++;
				}
			}

		for(int f_Int = f_Hesh_Cade->vec_Bicycle.size(); f_Int < f_Hesh_Cade->vec_Bicycle.size() + 1; f_Int++)
			{
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bike");
			std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>();

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
			std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
			f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
			std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
			f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
			std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
			f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
			std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
			f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
			std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
			f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
			std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
			f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
			std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
			f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
			std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f);
			f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
			std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
			std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
			std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
			std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
			std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
			std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
			std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
			std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1->acRun_visualminer();
			f_Vector2->acRun_visualminer();
			f_Vector3->acRun_visualminer();
			f_Vector4->acRun_visualminer();
			f_Vector5->acRun_visualminer();
			f_Vector6->acRun_visualminer();
			f_Vector7->acRun_visualminer();
			f_Vector8->acRun_visualminer();

#if 1
			f_Vector1->acResolve_precision();
			f_Vector2->acResolve_precision();
			f_Vector3->acResolve_precision();
			f_Vector4->acResolve_precision();
			f_Vector5->acResolve_precision();
			f_Vector6->acResolve_precision();
			f_Vector7->acResolve_precision();
			f_Vector8->acResolve_precision();
#endif

			f_Bike->vec_Vertex.push_back(f_Vector1);
			f_Bike->vec_Vertex.push_back(f_Vector2);
			f_Bike->vec_Vertex.push_back(f_Vector3);
			f_Bike->vec_Vertex.push_back(f_Vector4);
			f_Bike->vec_Vertex.push_back(f_Vector5);
			f_Bike->vec_Vertex.push_back(f_Vector6);
			f_Bike->vec_Vertex.push_back(f_Vector7);
			f_Bike->vec_Vertex.push_back(f_Vector8);

			f_Bike->vec_Color.clear();

			f_Bike->vec_Color.push_back(f_Color1);
			f_Bike->vec_Color.push_back(f_Color2);
			f_Bike->vec_Color.push_back(f_Color3);
			f_Bike->vec_Color.push_back(f_Color4);
			f_Bike->vec_Color.push_back(f_Color5);
			f_Bike->vec_Color.push_back(f_Color6);
			f_Bike->vec_Color.push_back(f_Color7);
			f_Bike->vec_Color.push_back(f_Color8);

			f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Element");
			std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Bike);

			f_Collection->m_vec_Element.push_back(f_Element);
			f_Collection->m_idx_vec_Element++;
			}

		//hesh admax limiter
#ifndef ECOIN_ADMAX_MAX
		float f_Finger = Cube::random();
		float f_LimitSenseFLT = (((float)f_Hesh_Cade->m_ADMAX - ECOIN_HESH_MINIMUM) * f_Finger) + ECOIN_HESH_MINIMUM;
		int f_LimitSense = (int)f_LimitSenseFLT;
#else
		int f_LimitSense = g_classLMap->m_ADMAX;
#endif

		int f_PORTcntr = f_Hesh_Cade->m_adIndex.size();

		while(f_Hesh_Cade->m_adIndex.size() < f_LimitSense)
			{
			f_Hesh_Cade->m_adIndex.push_back(f_PORTcntr);
			f_PORTcntr++;
			}

		Cube::BiVector f_ColorBCK(Cube::random(), Cube::random(), Cube::random());

		f_Hesh_Cade->m_bckred = f_ColorBCK.m_X;
		f_Hesh_Cade->m_bckgreen = f_ColorBCK.m_Y;
		f_Hesh_Cade->m_bckblue = f_ColorBCK.m_Z;

		f_Hesh_Cade->ac_IsOK();

		g_ElementCount += f_Hesh_Cade->m_adIndex.size();

		  ////////////
		 // HESH   //
		// Target //
		if(g_Result == false || true)
			{
			g_Result = g_classLMap->acCompute(f_Collection, f_OCSCP_ThreadIndex);

			   ////////////
			  // Save
			 // Hash
			// Result
			if((g_Result == true) && 0)
				{
				int f_ShareID = 1;
				int f_BlockID = 1;
				int f_JobID = 1;
				int f_EslID = 1;
				int f_TargetID = 1;
				float f_Difficulty = ECOIN_TARGET_COMPARE_THRESH; //Target Mark Threshold

				m_DB_AccessLock.lock();
				f_OCP_LOCK_ON = true;

#if 0
				for(int f_XY = 0; f_XY < g_classLMap->m_vec_Ecom.size(); f_XY++)
					{
					gf_Target_3->m_vec_Ecom.push_back(g_classLMap->m_vec_Ecom[f_XY]);
					}
#endif

				f_Hesh_Cade->m_Hash = f_Hash;

				char* g_sharevalue[60];

				for(int f_Count = 0; f_Count < 60; f_Count++)
					{
					g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
					}

				std::sprintf(g_sharevalue[0], "%f", 1.0f * (float)g_OCSCP_LowtonMark);
				std::sprintf(g_sharevalue[1], "%i", 1);
				std::sprintf(g_sharevalue[2], "%s", "3");
				std::sprintf(g_sharevalue[4], "%i", f_EslID);
				std::sprintf(g_sharevalue[5], "%i", f_TargetID);
				std::sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
				std::sprintf(g_sharevalue[7], "%f", f_Difficulty);

				f_Hash->acClear();

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					for(int f_Helly = 0; f_Helly < 8; f_Helly++)
						{
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					for(int f_Helly = 0; f_Helly < 8; f_Helly++)
						{
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					f_Hash->acPushInt(f_Hesh_Cade->m_adIndex[f_Jet]);
					}

				   ////////////
				  // Hash
				 //
				//
				std::string f_InputHash = f_Hash->acGetInput();

				// check GenesisBlock (assume)
				std::string f_previousblock = "00000000000000000000000000000001";
				//ECN::Hesh...Checking Previous BlockHesh.

				char blokquery[1000];
				::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

				g_SafeL[0]->acSelectCommand(blokquery, 2, false);

				int f_blokLCount = 0;

				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
					{
					f_blokLCount = 0;
					}
				else
					{
					f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
					}

				//ECN::Stat::: f_TrxLCount f_blokLCount
				g_JobID = 0;

				if(f_blokLCount > 0)
					{
					g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
					g_JobID++;
					f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
					}

				f_JobID = g_JobID;

				::sprintf(g_sharevalue[3], "%i", f_JobID);

				//ECN::Stat::: f_tx - f_JobID
				std::string f_tx = ag_GatherTransactions(g_JobID);

				std::string f_job = f_tx + f_previousblock;

				f_InputHash += f_job;

#if 1
				g_hasha.init(); //reset hasher state
				g_hasha.process(f_InputHash.begin(), f_InputHash.end());
				g_hasha.finish();
				picosha2::get_hash_hex_string(g_hasha, f_Hash->m_OutputHash);
#else
				f_Hash->m_OutputHash = "00000000000000000000000000000000";
#endif

				f_Hesh_Cade->m_Hash = f_Hash;

				//ShareHash-f_Hash->m_OutputHash
				::sprintf(g_sharevalue[8], "%i", 0);
				::sprintf(g_sharevalue[9], "%i", 10);
				::sprintf(g_sharevalue[10], "%s", f_Hash->m_OutputHash.c_str());
				::sprintf(g_sharevalue[11], "%s", f_Hash->m_OutputHash.c_str());
				::sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
				::sprintf(g_sharevalue[13], "%f", f_Hesh_Cade->m_bckred);
				::sprintf(g_sharevalue[14], "%f", f_Hesh_Cade->m_bckgreen);
				::sprintf(g_sharevalue[15], "%f", f_Hesh_Cade->m_bckblue);
				::sprintf(g_sharevalue[16], "%f", 0.0f);

				//ECN::Hesh...Sending BlockHesh
				char shlquery[1000];
				::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Hash->m_OutputHash.c_str());

				g_SafeL[0]->acSelectCommand(shlquery, 2, false);

				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
					{
					int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

					f_ShareID = f_ShareUniqueID;
					g_ShareID = f_ShareID;

					//ECN::Stat::: f_ShareID f_shareuniqueID
					ag_addGenesisTracking(f_ShareUniqueID);
				
					char* f_idquery2 = new char[150];
					::sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

					g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
					delete[] f_idquery2;

					int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
					int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

					g_PEERCNT = f_PEERCNT;
					g_SHARECNT = f_SHARECNT;

					for(int f_Int = 0; f_Int < f_Hesh_Cade->m_adIndex.size(); f_Int++)
						{
						std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[/*f_Hesh_Cade->m_adIndex[*/f_Int/*]*/];

						char* g_cubevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
							}

						for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
							{
							::sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
							::sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
							::sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
							}

						for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
							{
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
							}
				
						::sprintf(g_cubevalue[48], "%i", f_BlockID);
						::sprintf(g_cubevalue[49], "%i", f_ShareID);
						::sprintf(g_cubevalue[50], "%i", f_JobID);
						::sprintf(g_cubevalue[51], "%i", f_Int);
						::sprintf(g_cubevalue[52], "%i", f_TargetID);
						::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
						::sprintf(g_cubevalue[54], "%f", f_Difficulty);

						g_CubeFieldCount = 55;

						int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
						}

					//ECN::Complete Share Submitted
					g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
					f_Ack->m_ECN = 0.0f;
					f_Ack->m_Reward = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = g_Wallet->GetAdr();
					g_Ackent.push_back(f_Ack);

					g_Compressing = 0;
					}
				else //Duplicate Block Found.
					{
					g_Result = false;
					}
				}
			else
				{
				int f_OC_Mark_Count = g_Lowton->vec_Bicycle.size();

				bool f_Scan = true;

				while(f_Scan == true)
					{
					if(f_OC_Mark_Count >= f_Collection->m_vec_Element.size())
						{
						f_Scan = false;
						}
					else
						{
						if(f_Collection->m_vec_Element[f_OC_Mark_Count]->m_OCSCP_Flag == false)
							{
							f_Scan = false;
							}
						else
							{
							f_OC_Mark_Count++;
							}
						}
					}

				if(f_OC_Mark_Count > g_Lowton->vec_Bicycle.size())
					{
					m_DB_AccessLock.lock();
					f_OCP_LOCK_ON = true;

					for(int f_Jet = g_Lowton->vec_Bicycle.size(); f_Jet < f_OC_Mark_Count; f_Jet++)
						{
						//make bike clone
						std::shared_ptr<CubeBicycle> f_WinningBike = f_Hesh_Cade->vec_Bicycle[f_Jet];

						// Load mesh vertices. Each vertex has a position and a color.
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
						std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[0]->m_X, f_WinningBike->vec_Vertex[0]->m_Y, f_WinningBike->vec_Vertex[0]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
						std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[1]->m_X, f_WinningBike->vec_Vertex[1]->m_Y, f_WinningBike->vec_Vertex[1]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
						std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[2]->m_X, f_WinningBike->vec_Vertex[2]->m_Y, f_WinningBike->vec_Vertex[2]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
						std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[3]->m_X, f_WinningBike->vec_Vertex[3]->m_Y, f_WinningBike->vec_Vertex[3]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
						std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[4]->m_X, f_WinningBike->vec_Vertex[4]->m_Y, f_WinningBike->vec_Vertex[4]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
						std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[5]->m_X, f_WinningBike->vec_Vertex[5]->m_Y, f_WinningBike->vec_Vertex[5]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
						std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[6]->m_X, f_WinningBike->vec_Vertex[6]->m_Y, f_WinningBike->vec_Vertex[6]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
						std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[7]->m_X, f_WinningBike->vec_Vertex[7]->m_Y, f_WinningBike->vec_Vertex[7]->m_Z);

						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
						std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[0]->m_X, f_WinningBike->vec_Color[0]->m_Y, f_WinningBike->vec_Color[0]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
						std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[1]->m_X, f_WinningBike->vec_Color[1]->m_Y, f_WinningBike->vec_Color[1]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
						std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[2]->m_X, f_WinningBike->vec_Color[2]->m_Y, f_WinningBike->vec_Color[2]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
						std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[3]->m_X, f_WinningBike->vec_Color[3]->m_Y, f_WinningBike->vec_Color[3]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
						std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[4]->m_X, f_WinningBike->vec_Color[4]->m_Y, f_WinningBike->vec_Color[4]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
						std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[5]->m_X, f_WinningBike->vec_Color[5]->m_Y, f_WinningBike->vec_Color[5]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
						std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[6]->m_X, f_WinningBike->vec_Color[6]->m_Y, f_WinningBike->vec_Color[6]->m_Z);
						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
						std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[7]->m_X, f_WinningBike->vec_Color[7]->m_Y, f_WinningBike->vec_Color[7]->m_Z);

						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bike");
						std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>();

						f_Bike->vec_Vertex.push_back(f_Vector1);
						f_Bike->vec_Vertex.push_back(f_Vector2);
						f_Bike->vec_Vertex.push_back(f_Vector3);
						f_Bike->vec_Vertex.push_back(f_Vector4);
						f_Bike->vec_Vertex.push_back(f_Vector5);
						f_Bike->vec_Vertex.push_back(f_Vector6);
						f_Bike->vec_Vertex.push_back(f_Vector7);
						f_Bike->vec_Vertex.push_back(f_Vector8);

						f_Bike->vec_Color.clear();

						f_Bike->vec_Color.push_back(f_Color1);
						f_Bike->vec_Color.push_back(f_Color2);
						f_Bike->vec_Color.push_back(f_Color3);
						f_Bike->vec_Color.push_back(f_Color4);
						f_Bike->vec_Color.push_back(f_Color5);
						f_Bike->vec_Color.push_back(f_Color6);
						f_Bike->vec_Color.push_back(f_Color7);
						f_Bike->vec_Color.push_back(f_Color8);

						g_Lowton->vec_Bicycle.push_back(f_Bike);

						g_Lowton->m_adIndex.push_back(/*f_Hesh_Cade->m_adIndex[*/f_Jet/*]*/);

						g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Element");
						std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Bike);

						g_Lowton_Collection->m_vec_Element.push_back(f_Element);
						g_Lowton_Collection->m_idx_vec_Element++;

						//?require?g_LowtonTarget_3 = gf_Target_3; < hmm
						}

					g_Lowton->m_bckblue = f_Hesh_Cade->m_bckblue;
					g_Lowton->m_bckred = f_Hesh_Cade->m_bckred;
					g_Lowton->m_bckgreen = f_Hesh_Cade->m_bckgreen;

					g_TargetedHesh = g_Lowton;

					g_TargetedHesh->ac_IsOK();

					g_RenderHesh = true;

					bool f_Result = g_classLMap->acCompute(g_Lowton_Collection, f_OCSCP_ThreadIndex, true);

					int f_OC_Lowton_Mark_Count = 0;

					bool f_ScanX = true;

					while(f_ScanX == true)
						{
						if(f_OC_Lowton_Mark_Count >= g_Lowton_Collection->m_vec_Element.size())
							{
							f_ScanX = false;
							}
						else
							{
							if(g_Lowton_Collection->m_vec_Element[f_OC_Lowton_Mark_Count]->m_OCSCP_Flag == false)
								{
								f_ScanX = false;
								}
							else
								{
								f_OC_Lowton_Mark_Count++;
								}
							}
						}

					if(f_OC_Lowton_Mark_Count >= g_classLMap->m_ADMAX)
						{
						g_Result = true;

						int f_ShareID = 1;
						int f_BlockID = 1;
						int f_JobID = 1;
						int f_EslID = 1;
						int f_TargetID = 1;
						float f_Difficulty = ECOIN_TARGET_SCP_COMPARE_THRESH; //Target Mark Threshold

						char* g_sharevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
							}

						::sprintf(g_sharevalue[0], "%f", (float)g_Lowton->vec_Bicycle.size());
						::sprintf(g_sharevalue[1], "%i", 1);
						::sprintf(g_sharevalue[2], "%s", "3");
						::sprintf(g_sharevalue[4], "%i", 15);
						::sprintf(g_sharevalue[5], "%i", 15);
						::sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
						::sprintf(g_sharevalue[7], "%f", f_Difficulty);

						g_LowtonHash = f_Hash;

						g_LowtonHash->acClear();

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							g_LowtonHash->acPushInt(g_Lowton->m_adIndex[f_Jet]);
							}

							////////////
						   //
						  // Hash
						 //
						std::string f_InputHash = g_LowtonHash->acGetInput();

						// check GenesisBlock (assume)
						std::string f_previousblock = "00000000000000000000000000000001";
						//ECN::Hesh...Checking Previous BlockHesh

						char blokquery[1000];

						::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

						if(f_OCP_LOCK_ON == false)
							{
							m_DB_AccessLock.lock();
							f_OCP_LOCK_ON = true;
							}

						g_SafeL[0]->acSelectCommand(blokquery, 2, false);

						int f_blokLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_blokLCount = 0;
							}
						else
							{
							f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						g_JobID = 0;

						if(f_blokLCount > 0)
							{
							g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
							g_JobID++;
							f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
							}

						f_JobID = g_JobID;

						::sprintf(g_sharevalue[3], "%i", f_JobID);

						std::string f_tx = ag_GatherTransactions(g_JobID);

						std::string f_job = f_tx + f_previousblock;

						f_InputHash += f_job;

#if 1
						g_hasha.init(); //reset hasher state
						g_hasha.process(f_InputHash.begin(), f_InputHash.end());
						g_hasha.finish();
						picosha2::get_hash_hex_string(g_hasha, g_LowtonHash->m_OutputHash);
#else
						g_LowtonHash->m_OutputHash = "00000000000000000000000000000000";
#endif

						g_Lowton->m_Hash = g_LowtonHash;

						g_LowtonMark = 0;

						::sprintf(g_sharevalue[8], "%i", 0);
						::sprintf(g_sharevalue[9], "%i", 10);
						::sprintf(g_sharevalue[10], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[11], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
						::sprintf(g_sharevalue[13], "%f", g_Lowton->m_bckred);
						::sprintf(g_sharevalue[14], "%f", g_Lowton->m_bckgreen);
						::sprintf(g_sharevalue[15], "%f", g_Lowton->m_bckblue);
						::sprintf(g_sharevalue[16], "%f", 0.0f);

						//ECN::Hesh...Sending BlockHesh
						char shlquery[1000];
						::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", g_LowtonHash->m_OutputHash.c_str());

						g_SafeL[0]->acSelectCommand(shlquery, 2, false);

						int f_ShareLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_ShareLCount = 0;
							}
						else
							{
							f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						if(f_ShareLCount == 0)
							{
							int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

							f_ShareID = f_ShareUniqueID;
							g_ShareID = f_ShareID;

							ag_addGenesisTracking(f_ShareUniqueID);
				
							char* f_idquery2 = new char[150];
							::sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

							g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
							delete[] f_idquery2;

							int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
							int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

							g_PEERCNT = f_PEERCNT;
							g_SHARECNT = f_SHARECNT;

							for(int f_Int = 0; f_Int < g_Lowton->m_adIndex.size(); f_Int++)
								{
								shared_ptr<CubeBicycle> f_Bike = g_Lowton->vec_Bicycle[/*g_Lowton->m_adIndex[*/f_Int/*]*/];

								char* g_cubevalue[60];

								for(int f_Count = 0; f_Count < 60; f_Count++)
									{
									g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
									}

								for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
									{
									::sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
									::sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
									::sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
									}

								for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
									{
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
									}
				
								::sprintf(g_cubevalue[48], "%i", f_BlockID);
								::sprintf(g_cubevalue[49], "%i", f_ShareID);
								::sprintf(g_cubevalue[50], "%i", f_JobID);
								::sprintf(g_cubevalue[51], "%i", f_Int);
								::sprintf(g_cubevalue[52], "%i", 1);	// FIXME ADD L-TARGETID
								::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
								::sprintf(g_cubevalue[54], "%f", f_Difficulty);

								g_CubeFieldCount = 55;

								int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
								}

							// ECN::Lowton Share Submitted
							g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Ack");
							std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
							f_Ack->m_ECN = 0.0f;
							f_Ack->m_Reward = 50.0f;
							f_Ack->m_Origin = 1;
							f_Ack->m_Owner = g_Wallet->GetAdr();
							g_Ackent.push_back(f_Ack);

							g_Compressing = 0;
							}
						else // Duplicate Block Found.
							{
							g_Result = false;
							}
						}
					}
				}
			}

		if(f_OCP_LOCK_ON == true)
			{
			m_DB_AccessLock.unlock();
			f_OCP_LOCK_ON = false;
			}
		}

	 ///////////////////////////////////////////////////
	// not safe for multiple miner windows open on
	g_ElementDivisor.pop_back();
	g_ElementDivisorInt.pop_back();
	g_classLMap->m_SchemaRef.pop_back();
}

#else

void Sample3DSceneRenderer::acSaveCompletePublish_GenHesh(void)
{
	bool f_OCP_LOCK_ON = false;

	m_DB_AccessLock.lock();
	f_OCP_LOCK_ON = true;

	int f_OCSCP_ThreadIndex = g_OCSCP_ThreadCount;

	g_OCSCP_ThreadCount++;

	g_ElementDivisor.push_back(0);
	g_ElementDivisorInt.push_back(0);

	g_classLMap->m_SchemaRef.push_back(std::make_shared_oage<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_SaveSchemaRef.push_back(std::make_shared_oage<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_SchemaMeasureIndex.push_back(0);
	g_classLMap->m_CPS_Result.push_back(CPS_SCAN);

	m_DB_AccessLock.unlock();
	f_OCP_LOCK_ON = false;

	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared_oage<Cube::CubeHESH>(g_classLMap->m_ADMAX, g_classLMap->m_ADHIGH, g_classLMap->m_ADLOW);
	std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared_oage<Cube::CubeHASH_originstring>();
	std::shared_ptr<classCollection> f_Collection = std::make_shared_oage<classCollection>();

	while(g_Compressing == 1)
		{
		int f_SizeMin = f_Collection->m_vec_Element.size();

		for(int f_XYZ = f_Collection->m_vec_Element.size() - 1; f_XYZ >= 0; f_XYZ--)
			{
			if(f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag == false)
				{
				f_SizeMin = f_XYZ;
				}
			}

		if(f_SizeMin < 0)
			{
			f_SizeMin = 0;
			}

		while(f_Hesh_Cade->vec_Bicycle.size() > f_SizeMin)
			{
			f_Hesh_Cade->vec_Bicycle.pop_back();
			f_Hesh_Cade->m_adIndex.pop_back();
			f_Collection->m_vec_Element.pop_back();
			f_Collection->m_idx_vec_Element--;
			}

		if(g_LowtonOn == true)
			{
			int f_FingerBike = f_SizeMin;

			while(f_Hesh_Cade->vec_Bicycle.size() < g_Lowton->vec_Bicycle.size())
				{
				//make bike clone
				std::shared_ptr<CubeBicycle> f_WonBike = g_Lowton->vec_Bicycle[f_FingerBike];

				// Load mesh vertices. Each vertex has a position and a color.
				std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[0]->m_X, f_WonBike->vec_Vertex[0]->m_Y, f_WonBike->vec_Vertex[0]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[1]->m_X, f_WonBike->vec_Vertex[1]->m_Y, f_WonBike->vec_Vertex[1]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[2]->m_X, f_WonBike->vec_Vertex[2]->m_Y, f_WonBike->vec_Vertex[2]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[3]->m_X, f_WonBike->vec_Vertex[3]->m_Y, f_WonBike->vec_Vertex[3]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[4]->m_X, f_WonBike->vec_Vertex[4]->m_Y, f_WonBike->vec_Vertex[4]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[5]->m_X, f_WonBike->vec_Vertex[5]->m_Y, f_WonBike->vec_Vertex[5]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[6]->m_X, f_WonBike->vec_Vertex[6]->m_Y, f_WonBike->vec_Vertex[6]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[7]->m_X, f_WonBike->vec_Vertex[7]->m_Y, f_WonBike->vec_Vertex[7]->m_Z);

				std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[0]->m_X, f_WonBike->vec_Color[0]->m_Y, f_WonBike->vec_Color[0]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[1]->m_X, f_WonBike->vec_Color[1]->m_Y, f_WonBike->vec_Color[1]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[2]->m_X, f_WonBike->vec_Color[2]->m_Y, f_WonBike->vec_Color[2]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[3]->m_X, f_WonBike->vec_Color[3]->m_Y, f_WonBike->vec_Color[3]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[4]->m_X, f_WonBike->vec_Color[4]->m_Y, f_WonBike->vec_Color[4]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[5]->m_X, f_WonBike->vec_Color[5]->m_Y, f_WonBike->vec_Color[5]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[6]->m_X, f_WonBike->vec_Color[6]->m_Y, f_WonBike->vec_Color[6]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[7]->m_X, f_WonBike->vec_Color[7]->m_Y, f_WonBike->vec_Color[7]->m_Z);

				std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_oage<Cube::CubeBicycle>();

				f_Bike->vec_Vertex.push_back(f_Vector1);
				f_Bike->vec_Vertex.push_back(f_Vector2);
				f_Bike->vec_Vertex.push_back(f_Vector3);
				f_Bike->vec_Vertex.push_back(f_Vector4);
				f_Bike->vec_Vertex.push_back(f_Vector5);
				f_Bike->vec_Vertex.push_back(f_Vector6);
				f_Bike->vec_Vertex.push_back(f_Vector7);
				f_Bike->vec_Vertex.push_back(f_Vector8);

				f_Bike->vec_Color.clear();

				f_Bike->vec_Color.push_back(f_Color1);
				f_Bike->vec_Color.push_back(f_Color2);
				f_Bike->vec_Color.push_back(f_Color3);
				f_Bike->vec_Color.push_back(f_Color4);
				f_Bike->vec_Color.push_back(f_Color5);
				f_Bike->vec_Color.push_back(f_Color6);
				f_Bike->vec_Color.push_back(f_Color7);
				f_Bike->vec_Color.push_back(f_Color8);

				f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

				f_Hesh_Cade->m_adIndex.push_back(g_Lowton->m_adIndex[f_FingerBike]);

				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Element");
				std::shared_ptr<classElement> f_Element = std::make_shared_oage<classElement>(f_Bike);

				f_Collection->m_vec_Element.push_back(f_Element);
				f_Collection->m_idx_vec_Element++;

				f_FingerBike++;
				}
			}

		for(int f_Int = f_Hesh_Cade->vec_Bicycle.size(); f_Int < g_classLMap->m_ADMAX; f_Int++)
			{
			std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_oage<Cube::CubeBicycle>();

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared_oage<Cube::BiVector>(-0.5f);
			f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared_oage<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
			f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared_oage<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
			f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared_oage<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
			f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared_oage<Cube::BiVector>(0.5f, -0.5f, -0.5f);
			f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared_oage<Cube::BiVector>(0.5f, -0.5f, 0.5f);
			f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared_oage<Cube::BiVector>(0.5f, 0.5f, -0.5f);
			f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared_oage<Cube::BiVector>(0.5f);
			f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1->acRun_visualminer();
			f_Vector2->acRun_visualminer();
			f_Vector3->acRun_visualminer();
			f_Vector4->acRun_visualminer();
			f_Vector5->acRun_visualminer();
			f_Vector6->acRun_visualminer();
			f_Vector7->acRun_visualminer();
			f_Vector8->acRun_visualminer();

#if 1
			f_Vector1->acResolve_precision(SCP_FLT_SCALE);
			f_Vector2->acResolve_precision(SCP_FLT_SCALE);
			f_Vector3->acResolve_precision(SCP_FLT_SCALE);
			f_Vector4->acResolve_precision(SCP_FLT_SCALE);
			f_Vector5->acResolve_precision(SCP_FLT_SCALE);
			f_Vector6->acResolve_precision(SCP_FLT_SCALE);
			f_Vector7->acResolve_precision(SCP_FLT_SCALE);
			f_Vector8->acResolve_precision(SCP_FLT_SCALE);
#endif

			f_Bike->vec_Vertex.push_back(f_Vector1);
			f_Bike->vec_Vertex.push_back(f_Vector2);
			f_Bike->vec_Vertex.push_back(f_Vector3);
			f_Bike->vec_Vertex.push_back(f_Vector4);
			f_Bike->vec_Vertex.push_back(f_Vector5);
			f_Bike->vec_Vertex.push_back(f_Vector6);
			f_Bike->vec_Vertex.push_back(f_Vector7);
			f_Bike->vec_Vertex.push_back(f_Vector8);

			f_Bike->vec_Color.clear();

			f_Bike->vec_Color.push_back(f_Color1);
			f_Bike->vec_Color.push_back(f_Color2);
			f_Bike->vec_Color.push_back(f_Color3);
			f_Bike->vec_Color.push_back(f_Color4);
			f_Bike->vec_Color.push_back(f_Color5);
			f_Bike->vec_Color.push_back(f_Color6);
			f_Bike->vec_Color.push_back(f_Color7);
			f_Bike->vec_Color.push_back(f_Color8);

			f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

			std::shared_ptr<classElement> f_Element = std::make_shared_oage<classElement>(f_Bike);

			f_Collection->m_vec_Element.push_back(f_Element);
			f_Collection->m_idx_vec_Element++;
			}

		//hesh admax limiter
#ifndef ECOIN_ADMAX_MAX
		float f_Finger = Cube::random();
		float f_LimitSenseFLT = (((float)f_Hesh_Cade->m_ADMAX - ECOIN_HESH_MINIMUM) * f_Finger) + ECOIN_HESH_MINIMUM;
		int f_LimitSense = (int)f_LimitSenseFLT;
#else
		int f_LimitSense = g_classLMap->m_ADMAX;
#endif

		int f_PORTcntr = f_Hesh_Cade->m_adIndex.size();

		while(f_Hesh_Cade->m_adIndex.size() < f_LimitSense)
			{
			f_Hesh_Cade->m_adIndex.push_back(f_PORTcntr);
			f_PORTcntr++;
			}

		Cube::BiVector f_ColorBCK(Cube::random(), Cube::random(), Cube::random());

		f_Hesh_Cade->m_bckred = f_ColorBCK.m_X;
		f_Hesh_Cade->m_bckgreen = f_ColorBCK.m_Y;
		f_Hesh_Cade->m_bckblue = f_ColorBCK.m_Z;

		f_Hesh_Cade->ac_IsOK();

		g_ElementCount += f_Hesh_Cade->m_adIndex.size();

		  ////////////
		 // HESH   //
		// Target //
		if(g_Result == false)
			{
			g_Result = g_classLMap->acTestCompute(f_Collection, f_OCSCP_ThreadIndex, false);

			   ////////////
			  // Save
			 // Hash
			// Result
			if((g_Result == true) && 0)
				{
				int f_ShareID = 1;
				int f_BlockID = 1;
				int f_JobID = 1;
				int f_EslID = 1;
				int f_TargetID = 1;
				float f_Difficulty = ECOIN_TARGET_COMPARE_THRESH; //Target Mark Threshold

				m_DB_AccessLock.lock();
				f_OCP_LOCK_ON = true;

#if 0
				for(int f_XY = 0; f_XY < g_classLMap->m_vec_Ecom.size(); f_XY++)
					{
					gf_Target_3->m_vec_Ecom.push_back(g_classLMap->m_vec_Ecom[f_XY]);
					}
#endif

				f_Hesh_Cade->m_Hash = f_Hash;

				char* g_sharevalue[60];

				for(int f_Count = 0; f_Count < 60; f_Count++)
					{
					g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
					}

				std::sprintf(g_sharevalue[0], "%f", 1.0f * (float)g_OCSCP_LowtonMark);
				std::sprintf(g_sharevalue[1], "%i", 1);
				std::sprintf(g_sharevalue[2], "%s", "3");
				std::sprintf(g_sharevalue[4], "%i", f_EslID);
				std::sprintf(g_sharevalue[5], "%i", f_TargetID);
				std::sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
				std::sprintf(g_sharevalue[7], "%f", f_Difficulty);

				f_Hash->acClear();

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					for(int f_Helly = 0; f_Helly < 8; f_Helly++)
						{
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					for(int f_Helly = 0; f_Helly < 8; f_Helly++)
						{
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
						f_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
					{
					f_Hash->acPushInt(f_Hesh_Cade->m_adIndex[f_Jet]);
					}

				   ////////////
				  // Hash
				 //
				//
				std::string f_InputHash = f_Hash->acGetInput();

				// check GenesisBlock (assume)
				std::string f_previousblock = "00000000000000000000000000000001";
				//ECN::Hesh...Checking Previous BlockHesh.

				char blokquery[1000];
				::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

				g_SafeL[0]->acSelectCommand(blokquery, 2, false);

				int f_blokLCount = 0;

				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
					{
					f_blokLCount = 0;
					}
				else
					{
					f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
					}

				//ECN::Stat::: f_TrxLCount f_blokLCount
				g_JobID = 0;

				if(f_blokLCount > 0)
					{
					g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
					g_JobID++;
					f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
					}

				f_JobID = g_JobID;

				::sprintf(g_sharevalue[3], "%i", f_JobID);

				//ECN::Stat::: f_tx - f_JobID
				std::string f_tx = ag_GatherTransactions(g_JobID);

				std::string f_job = f_tx + f_previousblock;

				f_InputHash += f_job;

#if 1
				g_hasha.init(); //reset hasher state
				g_hasha.process(f_InputHash.begin(), f_InputHash.end());
				g_hasha.finish();
				picosha2::get_hash_hex_string(g_hasha, f_Hash->m_OutputHash);
#else
				f_Hash->m_OutputHash = "00000000000000000000000000000000";
#endif

				f_Hesh_Cade->m_Hash = f_Hash;

				//ShareHash-f_Hash->m_OutputHash
				::sprintf(g_sharevalue[8], "%i", 0);
				::sprintf(g_sharevalue[9], "%i", 10);
				::sprintf(g_sharevalue[10], "%s", f_Hash->m_OutputHash.c_str());
				::sprintf(g_sharevalue[11], "%s", f_Hash->m_OutputHash.c_str());
				::sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
				::sprintf(g_sharevalue[13], "%f", f_Hesh_Cade->m_bckred);
				::sprintf(g_sharevalue[14], "%f", f_Hesh_Cade->m_bckgreen);
				::sprintf(g_sharevalue[15], "%f", f_Hesh_Cade->m_bckblue);
				::sprintf(g_sharevalue[16], "%f", 0.0f);

				//ECN::Hesh...Sending BlockHesh
				char shlquery[1000];
				::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Hash->m_OutputHash.c_str());

				g_SafeL[0]->acSelectCommand(shlquery, 2, false);

				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
					{
					int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

					f_ShareID = f_ShareUniqueID;
					g_ShareID = f_ShareID;

					//ECN::Stat::: f_ShareID f_shareuniqueID
					ag_addGenesisTracking(f_ShareUniqueID);
				
					char* f_idquery2 = new char[150];
					::sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

					g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
					delete[] f_idquery2;

					int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
					int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

					g_PEERCNT = f_PEERCNT;
					g_SHARECNT = f_SHARECNT;

					for(int f_Int = 0; f_Int < f_Hesh_Cade->m_adIndex.size(); f_Int++)
						{
						std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[/*f_Hesh_Cade->m_adIndex[*/f_Int/*]*/];

						char* g_cubevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
							}

						for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
							{
							::sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
							::sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
							::sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
							}

						for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
							{
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
							::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
							}
				
						::sprintf(g_cubevalue[48], "%i", f_BlockID);
						::sprintf(g_cubevalue[49], "%i", f_ShareID);
						::sprintf(g_cubevalue[50], "%i", f_JobID);
						::sprintf(g_cubevalue[51], "%i", f_Int);
						::sprintf(g_cubevalue[52], "%i", f_TargetID);
						::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
						::sprintf(g_cubevalue[54], "%f", f_Difficulty);

						g_CubeFieldCount = 55;

						int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
						}

					//ECN::Complete Share Submitted
					std::shared_ptr<Ackent> f_Ack = std::make_shared_oage<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
					f_Ack->m_ECN = 0.0f;
					f_Ack->m_Reward = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = g_Wallet->GetAdr();
					g_Ackent.push_back(f_Ack);

					g_Compressing = 0;
					}
				else //Duplicate Block Found.
					{
					g_Result = false;
					}
				}
			else
				{
				int f_OC_Mark_Count = g_Lowton->vec_Bicycle.size();

				bool f_Scan = true;

				while(f_Scan == true)
					{
					if(f_OC_Mark_Count >= f_Collection->m_vec_Element.size())
						{
						f_Scan = false;
						}
					else
						{
						if(f_Collection->m_vec_Element[f_OC_Mark_Count]->m_OCSCP_Flag == false)
							{
							f_Scan = false;
							}
						else
							{
							f_OC_Mark_Count++;
							}
						}
					}

				if(f_OC_Mark_Count > g_Lowton->vec_Bicycle.size())
					{
					m_DB_AccessLock.lock();
					f_OCP_LOCK_ON = true;

					for(int f_Jet = g_Lowton->vec_Bicycle.size(); f_Jet < f_OC_Mark_Count; f_Jet++)
						{
						//make bike clone
						std::shared_ptr<CubeBicycle> f_WinningBike = f_Hesh_Cade->vec_Bicycle[f_Jet];

						// Load mesh vertices. Each vertex has a position and a color.
						std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[0]->m_X, f_WinningBike->vec_Vertex[0]->m_Y, f_WinningBike->vec_Vertex[0]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[1]->m_X, f_WinningBike->vec_Vertex[1]->m_Y, f_WinningBike->vec_Vertex[1]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[2]->m_X, f_WinningBike->vec_Vertex[2]->m_Y, f_WinningBike->vec_Vertex[2]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[3]->m_X, f_WinningBike->vec_Vertex[3]->m_Y, f_WinningBike->vec_Vertex[3]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[4]->m_X, f_WinningBike->vec_Vertex[4]->m_Y, f_WinningBike->vec_Vertex[4]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[5]->m_X, f_WinningBike->vec_Vertex[5]->m_Y, f_WinningBike->vec_Vertex[5]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[6]->m_X, f_WinningBike->vec_Vertex[6]->m_Y, f_WinningBike->vec_Vertex[6]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[7]->m_X, f_WinningBike->vec_Vertex[7]->m_Y, f_WinningBike->vec_Vertex[7]->m_Z);

						std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[0]->m_X, f_WinningBike->vec_Color[0]->m_Y, f_WinningBike->vec_Color[0]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[1]->m_X, f_WinningBike->vec_Color[1]->m_Y, f_WinningBike->vec_Color[1]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[2]->m_X, f_WinningBike->vec_Color[2]->m_Y, f_WinningBike->vec_Color[2]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[3]->m_X, f_WinningBike->vec_Color[3]->m_Y, f_WinningBike->vec_Color[3]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[4]->m_X, f_WinningBike->vec_Color[4]->m_Y, f_WinningBike->vec_Color[4]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[5]->m_X, f_WinningBike->vec_Color[5]->m_Y, f_WinningBike->vec_Color[5]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[6]->m_X, f_WinningBike->vec_Color[6]->m_Y, f_WinningBike->vec_Color[6]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[7]->m_X, f_WinningBike->vec_Color[7]->m_Y, f_WinningBike->vec_Color[7]->m_Z);

						std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_oage<Cube::CubeBicycle>();

						f_Bike->vec_Vertex.push_back(f_Vector1);
						f_Bike->vec_Vertex.push_back(f_Vector2);
						f_Bike->vec_Vertex.push_back(f_Vector3);
						f_Bike->vec_Vertex.push_back(f_Vector4);
						f_Bike->vec_Vertex.push_back(f_Vector5);
						f_Bike->vec_Vertex.push_back(f_Vector6);
						f_Bike->vec_Vertex.push_back(f_Vector7);
						f_Bike->vec_Vertex.push_back(f_Vector8);

						f_Bike->vec_Color.clear();

						f_Bike->vec_Color.push_back(f_Color1);
						f_Bike->vec_Color.push_back(f_Color2);
						f_Bike->vec_Color.push_back(f_Color3);
						f_Bike->vec_Color.push_back(f_Color4);
						f_Bike->vec_Color.push_back(f_Color5);
						f_Bike->vec_Color.push_back(f_Color6);
						f_Bike->vec_Color.push_back(f_Color7);
						f_Bike->vec_Color.push_back(f_Color8);

						g_Lowton->vec_Bicycle.push_back(f_Bike);

						g_Lowton->m_adIndex.push_back(/*f_Hesh_Cade->m_adIndex[*/f_Jet/*]*/);

						std::shared_ptr<classElement> f_Element = std::make_shared_oage<classElement>(f_Bike);

						g_Lowton_Collection->m_vec_Element.push_back(f_Element);
						g_Lowton_Collection->m_idx_vec_Element++;

						//?require?g_LowtonTarget_3 = gf_Target_3; < hmm
						}

					g_Lowton->m_bckblue = f_Hesh_Cade->m_bckblue;
					g_Lowton->m_bckred = f_Hesh_Cade->m_bckred;
					g_Lowton->m_bckgreen = f_Hesh_Cade->m_bckgreen;

					g_TargetedHesh = g_Lowton;

					g_TargetedHesh->ac_IsOK();

					g_RenderHesh = true;

#if 0
					bool f_Result = g_classLMap->acCompute(g_Lowton_Collection, f_OCSCP_ThreadIndex, true);

					int f_OC_Lowton_Mark_Count = 0;

					bool f_ScanX = true;

					while(f_ScanX == true)
						{
						if(f_OC_Lowton_Mark_Count >= g_Lowton_Collection->m_vec_Element.size())
							{
							f_ScanX = false;
							}
						else
							{
							if(g_Lowton_Collection->m_vec_Element[f_OC_Lowton_Mark_Count]->m_OCSCP_Flag == false)
								{
								f_ScanX = false;
								}
							else
								{
								f_OC_Lowton_Mark_Count++;
								}
							}
						}
#endif

					if(f_OC_Mark_Count >= g_classLMap->m_ADMAX)
						{
						int f_ShareID = 1;
						int f_BlockID = 1;
						int f_JobID = 1;
						int f_EslID = 1;
						int f_TargetID = 1;
						float f_Difficulty = ECOIN_TARGET_SCP_COMPARE_THRESH; //Target Mark Threshold

						char* g_sharevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
							}

						::sprintf(g_sharevalue[0], "%f", (float)g_Lowton->vec_Bicycle.size());
						::sprintf(g_sharevalue[1], "%i", 1);
						::sprintf(g_sharevalue[2], "%s", "3");
						::sprintf(g_sharevalue[4], "%i", 15);
						::sprintf(g_sharevalue[5], "%i", 15);
						::sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
						::sprintf(g_sharevalue[7], "%f", f_Difficulty);

						g_LowtonHash = f_Hash;

						g_LowtonHash->acClear();

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							g_LowtonHash->acPushInt(g_Lowton->m_adIndex[f_Jet]);
							}

							////////////
						   //
						  // Hash
						 //
						std::string f_InputHash = g_LowtonHash->acGetInput();

						// check GenesisBlock (assume)
						std::string f_previousblock = "00000000000000000000000000000001";
						//ECN::Hesh...Checking Previous BlockHesh

						char blokquery[1000];

						::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

						if(f_OCP_LOCK_ON == false)
							{
							m_DB_AccessLock.lock();
							f_OCP_LOCK_ON = true;
							}

						g_SafeL[0]->acSelectCommand(blokquery, 2, false);

						int f_blokLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_blokLCount = 0;
							}
						else
							{
							f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						g_JobID = 0;

						if(f_blokLCount > 0)
							{
							g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
							g_JobID++;
							f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
							}

						f_JobID = g_JobID;

						::sprintf(g_sharevalue[3], "%i", f_JobID);

						std::string f_tx = ag_GatherTransactions(g_JobID);

						std::string f_job = f_tx + f_previousblock;

						f_InputHash += f_job;

#if 1
						g_hasha.init(); //reset hasher state
						g_hasha.process(f_InputHash.begin(), f_InputHash.end());
						g_hasha.finish();
						picosha2::get_hash_hex_string(g_hasha, g_LowtonHash->m_OutputHash);
#else
						g_LowtonHash->m_OutputHash = "00000000000000000000000000000000";
#endif

						g_Lowton->m_Hash = g_LowtonHash;

						g_LowtonMark = 0;

						::sprintf(g_sharevalue[8], "%i", 0);
						::sprintf(g_sharevalue[9], "%i", 10);
						::sprintf(g_sharevalue[10], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[11], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
						::sprintf(g_sharevalue[13], "%f", g_Lowton->m_bckred);
						::sprintf(g_sharevalue[14], "%f", g_Lowton->m_bckgreen);
						::sprintf(g_sharevalue[15], "%f", g_Lowton->m_bckblue);
						::sprintf(g_sharevalue[16], "%f", 0.0f);

						//ECN::Hesh...Sending BlockHesh
						char shlquery[1000];
						::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", g_LowtonHash->m_OutputHash.c_str());

						g_SafeL[0]->acSelectCommand(shlquery, 2, false);

						int f_ShareLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_ShareLCount = 0;
							}
						else
							{
							f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						if(f_ShareLCount == 0)
							{
							int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

							f_ShareID = f_ShareUniqueID;
							g_ShareID = f_ShareID;

							ag_addGenesisTracking(f_ShareUniqueID);
				
							char* f_idquery2 = new char[150];
							::sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

							g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
							delete[] f_idquery2;

							int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
							int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

							g_PEERCNT = f_PEERCNT;
							g_SHARECNT = f_SHARECNT;

							for(int f_Int = 0; f_Int < g_Lowton->m_adIndex.size(); f_Int++)
								{
								shared_ptr<CubeBicycle> f_Bike = g_Lowton->vec_Bicycle[/*g_Lowton->m_adIndex[*/f_Int/*]*/];

								char* g_cubevalue[60];

								for(int f_Count = 0; f_Count < 60; f_Count++)
									{
									g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
									}

								for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
									{
									::sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
									::sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
									::sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
									}

								for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
									{
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
									::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
									}
				
								::sprintf(g_cubevalue[48], "%i", f_BlockID);
								::sprintf(g_cubevalue[49], "%i", f_ShareID);
								::sprintf(g_cubevalue[50], "%i", f_JobID);
								::sprintf(g_cubevalue[51], "%i", f_Int);
								::sprintf(g_cubevalue[52], "%i", 1);	// FIXME ADD L-TARGETID
								::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
								::sprintf(g_cubevalue[54], "%f", f_Difficulty);

								g_CubeFieldCount = 55;

								int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
								}

							// ECN::Lowton Share Submitted
							std::shared_ptr<Ackent> f_Ack = std::make_shared_oage<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
							f_Ack->m_ECN = 0.0f;
							f_Ack->m_Reward = 50.0f;
							f_Ack->m_Origin = 1;
							f_Ack->m_Owner = g_Wallet->GetAdr();
							g_Ackent.push_back(f_Ack);

							g_Compressing = 0;
							}
						else // Duplicate Block Found.
							{
							g_Result = false;
							}
						}
					}
				}
			}

		if(f_OCP_LOCK_ON == true)
			{
			m_DB_AccessLock.unlock();
			f_OCP_LOCK_ON = false;
			}
		}

	 ///////////////////////////////////////////////////
	// not safe for multiple miner windows open on
	g_ElementDivisor.pop_back();
	g_ElementDivisorInt.pop_back();

	g_classLMap->m_SchemaRef.pop_back();
	g_classLMap->m_SaveSchemaRef.pop_back();
	g_classLMap->m_SchemaMeasureIndex.pop_back();
	g_classLMap->m_CPS_Result.pop_back();
}

void Sample3DSceneRenderer::acSaveCompletePublish_GenHesh_Upper(void)
{
	bool f_OCP_LOCK_ON = false;

	m_DB_AccessLock.lock();
	f_OCP_LOCK_ON = true;

	int f_OCSCP_ThreadIndex = g_OCSCP_ThreadCount;

	g_OCSCP_ThreadCount++;

	g_ElementDivisor.push_back(0);
	g_ElementDivisorInt.push_back(0);

	g_classLMap->m_SchemaRef.push_back(std::make_shared_oage<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_SaveSchemaRef.push_back(std::make_shared_oage<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_SchemaMeasureIndex.push_back(0);
	g_classLMap->m_CPS_Result.push_back(CPS_SCAN);

	m_DB_AccessLock.unlock();
	f_OCP_LOCK_ON = false;

	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared_oage<Cube::CubeHESH>(g_classLMap->m_ADMAX, g_classLMap->m_ADHIGH, g_classLMap->m_ADLOW);
	std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared_oage<Cube::CubeHASH_originstring>();
	std::shared_ptr<classCollection> f_Collection = std::make_shared_oage<classCollection>();

	int f_OC_Lowton_Mark_Count = 0;

	 //////////////////////////////////////////
	// adjustable element at once count max
	int f_ElementOnce = SCP_ELM_ONCE;
	int f_ElementsOnceMax = SCP_ELM_ONCE;

	while(g_Compressing == 1)
		{
		int f_SizeMin = f_Collection->m_vec_Element.size();

		for(int f_XYZ = f_Collection->m_vec_Element.size() - 1; f_XYZ >= 0; f_XYZ--)
			{
			if(f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag == false)
				{
				f_SizeMin = f_XYZ;
				}
			}

		if(f_SizeMin < 0)
			{
			f_SizeMin = 0;
			}

		while(f_Hesh_Cade->vec_Bicycle.size() > f_SizeMin)
			{
			f_Hesh_Cade->vec_Bicycle.pop_back();
			f_Hesh_Cade->m_adIndex.pop_back();
			f_Collection->m_vec_Element.pop_back();
			f_Collection->m_idx_vec_Element--;
			}

		//######--
		int f_SoLowtonBicycleSize = g_Lowton->vec_Bicycle.size();

#ifdef SCP_DEBUG
		if(f_Hesh_Cade->vec_Bicycle.size() > f_SoLowtonBicycleSize)
			{
			throw;
			}
#endif

		if(g_LowtonOn == true)
			{
			int f_FingerBike = f_SizeMin;

			while(f_Hesh_Cade->vec_Bicycle.size() < f_SoLowtonBicycleSize)
				{
				//make bike clone
				std::shared_ptr<CubeBicycle> f_WonBike = g_Lowton->vec_Bicycle[f_FingerBike];

				// Load mesh vertices. Each vertex has a position and a color.
				std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[0]->m_X, f_WonBike->vec_Vertex[0]->m_Y, f_WonBike->vec_Vertex[0]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[1]->m_X, f_WonBike->vec_Vertex[1]->m_Y, f_WonBike->vec_Vertex[1]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[2]->m_X, f_WonBike->vec_Vertex[2]->m_Y, f_WonBike->vec_Vertex[2]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[3]->m_X, f_WonBike->vec_Vertex[3]->m_Y, f_WonBike->vec_Vertex[3]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[4]->m_X, f_WonBike->vec_Vertex[4]->m_Y, f_WonBike->vec_Vertex[4]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[5]->m_X, f_WonBike->vec_Vertex[5]->m_Y, f_WonBike->vec_Vertex[5]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[6]->m_X, f_WonBike->vec_Vertex[6]->m_Y, f_WonBike->vec_Vertex[6]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Vertex[7]->m_X, f_WonBike->vec_Vertex[7]->m_Y, f_WonBike->vec_Vertex[7]->m_Z);

				std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[0]->m_X, f_WonBike->vec_Color[0]->m_Y, f_WonBike->vec_Color[0]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[1]->m_X, f_WonBike->vec_Color[1]->m_Y, f_WonBike->vec_Color[1]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[2]->m_X, f_WonBike->vec_Color[2]->m_Y, f_WonBike->vec_Color[2]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[3]->m_X, f_WonBike->vec_Color[3]->m_Y, f_WonBike->vec_Color[3]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[4]->m_X, f_WonBike->vec_Color[4]->m_Y, f_WonBike->vec_Color[4]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[5]->m_X, f_WonBike->vec_Color[5]->m_Y, f_WonBike->vec_Color[5]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[6]->m_X, f_WonBike->vec_Color[6]->m_Y, f_WonBike->vec_Color[6]->m_Z);
				std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared_oage<Cube::BiVector>(f_WonBike->vec_Color[7]->m_X, f_WonBike->vec_Color[7]->m_Y, f_WonBike->vec_Color[7]->m_Z);

				std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_oage<Cube::CubeBicycle>();

				f_Bike->vec_Vertex.push_back(f_Vector1);
				f_Bike->vec_Vertex.push_back(f_Vector2);
				f_Bike->vec_Vertex.push_back(f_Vector3);
				f_Bike->vec_Vertex.push_back(f_Vector4);
				f_Bike->vec_Vertex.push_back(f_Vector5);
				f_Bike->vec_Vertex.push_back(f_Vector6);
				f_Bike->vec_Vertex.push_back(f_Vector7);
				f_Bike->vec_Vertex.push_back(f_Vector8);

				f_Bike->vec_Color.clear();

				f_Bike->vec_Color.push_back(f_Color1);
				f_Bike->vec_Color.push_back(f_Color2);
				f_Bike->vec_Color.push_back(f_Color3);
				f_Bike->vec_Color.push_back(f_Color4);
				f_Bike->vec_Color.push_back(f_Color5);
				f_Bike->vec_Color.push_back(f_Color6);
				f_Bike->vec_Color.push_back(f_Color7);
				f_Bike->vec_Color.push_back(f_Color8);

				f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

				f_Hesh_Cade->m_adIndex.push_back(g_Lowton->m_adIndex[f_FingerBike]);

				std::shared_ptr<classElement> f_Element = std::make_shared_oage<classElement>(f_Bike);

				f_Collection->m_vec_Element.push_back(f_Element);
				f_Collection->m_idx_vec_Element++;

				f_FingerBike++;
				}
			}

		//ADD ONE BIKE on for compution checks
		int f_BicyclePosition = f_Hesh_Cade->vec_Bicycle.size();

		int f_ElementsRemaining = g_classLMap->m_ADMAX - f_BicyclePosition;

		if(f_ElementsRemaining < f_ElementsOnceMax)
			{
			f_ElementOnce = f_ElementsRemaining;
			}

		if(f_ElementOnce > 0)
			{
			for(int f_Int = f_BicyclePosition; f_Int < f_BicyclePosition + f_ElementOnce; f_Int++)
				{
				std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_oage<Cube::CubeBicycle>();

				// Load mesh vertices. Each vertex has a position and a color.
				Cube::BiRand f_BiRand;
				std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared_oage<Cube::BiVector>(-0.5f + SCP_ADD_ON);
				f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared_oage<Cube::BiVector>(-0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON);
				f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared_oage<Cube::BiVector>(-0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON);
				f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared_oage<Cube::BiVector>(-0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON);
				f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared_oage<Cube::BiVector>(0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON);
				f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared_oage<Cube::BiVector>(0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON);
				f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared_oage<Cube::BiVector>(0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON);
				f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
				f_BiRand.acGet();
				std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared_oage<Cube::BiVector>(0.5f + SCP_ADD_ON);
				f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

				std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
				std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
				std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
				std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
				std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
				std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
				std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
				std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared_oage<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

#if 0
				Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));
#endif
#if 1
				Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * SCP_ELM_PUSH), ((Cube::random() - 0.5) * SCP_ELM_PUSH), ((Cube::random() - 0.5) * SCP_ELM_PUSH)));
#endif

#if 0
				f_Vector1->acRun_visualminer();
				f_Vector2->acRun_visualminer();
				f_Vector3->acRun_visualminer();
				f_Vector4->acRun_visualminer();
				f_Vector5->acRun_visualminer();
				f_Vector6->acRun_visualminer();
				f_Vector7->acRun_visualminer();
				f_Vector8->acRun_visualminer();
#endif

#if 1
				f_Vector1->acResolve_precision(SCP_FLT_SCALE);
				f_Vector2->acResolve_precision(SCP_FLT_SCALE);
				f_Vector3->acResolve_precision(SCP_FLT_SCALE);
				f_Vector4->acResolve_precision(SCP_FLT_SCALE);
				f_Vector5->acResolve_precision(SCP_FLT_SCALE);
				f_Vector6->acResolve_precision(SCP_FLT_SCALE);
				f_Vector7->acResolve_precision(SCP_FLT_SCALE);
				f_Vector8->acResolve_precision(SCP_FLT_SCALE);
#endif

				f_Bike->vec_Vertex.push_back(f_Vector1);
				f_Bike->vec_Vertex.push_back(f_Vector2);
				f_Bike->vec_Vertex.push_back(f_Vector3);
				f_Bike->vec_Vertex.push_back(f_Vector4);
				f_Bike->vec_Vertex.push_back(f_Vector5);
				f_Bike->vec_Vertex.push_back(f_Vector6);
				f_Bike->vec_Vertex.push_back(f_Vector7);
				f_Bike->vec_Vertex.push_back(f_Vector8);

				f_Bike->vec_Color.clear();

				f_Bike->vec_Color.push_back(f_Color1);
				f_Bike->vec_Color.push_back(f_Color2);
				f_Bike->vec_Color.push_back(f_Color3);
				f_Bike->vec_Color.push_back(f_Color4);
				f_Bike->vec_Color.push_back(f_Color5);
				f_Bike->vec_Color.push_back(f_Color6);
				f_Bike->vec_Color.push_back(f_Color7);
				f_Bike->vec_Color.push_back(f_Color8);

				f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

				std::shared_ptr<classElement> f_Element = std::make_shared_oage<classElement>(f_Bike);

				f_Collection->m_vec_Element.push_back(f_Element);
				f_Collection->m_idx_vec_Element++;
				}

#if 0
			int f_LimitSense = g_classLMap->m_ADMAX;
#else
			//heshcade admax
			int f_LimitSense = f_Hesh_Cade->vec_Bicycle.size();
#endif

			//counter
			int f_PORTcntr = f_Hesh_Cade->m_adIndex.size();

			while(f_Hesh_Cade->m_adIndex.size() < f_LimitSense)
				{
				f_Hesh_Cade->m_adIndex.push_back(f_PORTcntr);
				f_PORTcntr++;
				}

			Cube::BiVector f_ColorBCK(Cube::random(), Cube::random(), Cube::random());

			f_Hesh_Cade->m_bckred = f_ColorBCK.m_X;
			f_Hesh_Cade->m_bckgreen = f_ColorBCK.m_Y;
			f_Hesh_Cade->m_bckblue = f_ColorBCK.m_Z;

			//force ok
			f_Hesh_Cade->ac_IsOK();

			//element rate p/s counter
			g_ElementCount += f_LimitSense - f_BicyclePosition;
			}
		else
			{
			f_BicyclePosition = f_Hesh_Cade->vec_Bicycle.size() - 1;

			f_ElementOnce = 1;

			g_ElementCount += f_ElementOnce;
			}

		  ////////////
		 // HESH   //
		// Target //
		if((g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] == CPS_SCAN) && (g_Result == false))
			{
			int f_AttackIndex = 0;

			if(g_LowtonOn == true)
				{
				f_AttackIndex = f_BicyclePosition;
				}

			int f_IntegerResult = g_classLMap->acCompute(f_Collection, f_OCSCP_ThreadIndex, false, f_AttackIndex, f_ElementOnce);

				////////////
			   // Save
			  // Hash
			 // Result
			if(f_IntegerResult > 0)
				{
				mutex_swap.lock();
				m_DB_AccessLock.lock();
				f_OCP_LOCK_ON = true;

				if(g_Compressing == 1)
					{
					int f_OC_Mark_Count = g_Lowton->vec_Bicycle.size() + f_IntegerResult;

					for(int f_Jet = g_Lowton->vec_Bicycle.size(); f_Jet < f_OC_Mark_Count; f_Jet++)
						{
						//make bike clone
						std::shared_ptr<CubeBicycle> f_WinningBike = f_Hesh_Cade->vec_Bicycle[f_Jet];

						// Load mesh vertices. Each vertex has a position and a color.
						std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[0]->m_X, f_WinningBike->vec_Vertex[0]->m_Y, f_WinningBike->vec_Vertex[0]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[1]->m_X, f_WinningBike->vec_Vertex[1]->m_Y, f_WinningBike->vec_Vertex[1]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[2]->m_X, f_WinningBike->vec_Vertex[2]->m_Y, f_WinningBike->vec_Vertex[2]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[3]->m_X, f_WinningBike->vec_Vertex[3]->m_Y, f_WinningBike->vec_Vertex[3]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[4]->m_X, f_WinningBike->vec_Vertex[4]->m_Y, f_WinningBike->vec_Vertex[4]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[5]->m_X, f_WinningBike->vec_Vertex[5]->m_Y, f_WinningBike->vec_Vertex[5]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[6]->m_X, f_WinningBike->vec_Vertex[6]->m_Y, f_WinningBike->vec_Vertex[6]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Vertex[7]->m_X, f_WinningBike->vec_Vertex[7]->m_Y, f_WinningBike->vec_Vertex[7]->m_Z);

						std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[0]->m_X, f_WinningBike->vec_Color[0]->m_Y, f_WinningBike->vec_Color[0]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[1]->m_X, f_WinningBike->vec_Color[1]->m_Y, f_WinningBike->vec_Color[1]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[2]->m_X, f_WinningBike->vec_Color[2]->m_Y, f_WinningBike->vec_Color[2]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[3]->m_X, f_WinningBike->vec_Color[3]->m_Y, f_WinningBike->vec_Color[3]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[4]->m_X, f_WinningBike->vec_Color[4]->m_Y, f_WinningBike->vec_Color[4]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[5]->m_X, f_WinningBike->vec_Color[5]->m_Y, f_WinningBike->vec_Color[5]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[6]->m_X, f_WinningBike->vec_Color[6]->m_Y, f_WinningBike->vec_Color[6]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared_oage<Cube::BiVector>(f_WinningBike->vec_Color[7]->m_X, f_WinningBike->vec_Color[7]->m_Y, f_WinningBike->vec_Color[7]->m_Z);

						std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_oage<Cube::CubeBicycle>();

						f_Bike->vec_Vertex.push_back(f_Vector1);
						f_Bike->vec_Vertex.push_back(f_Vector2);
						f_Bike->vec_Vertex.push_back(f_Vector3);
						f_Bike->vec_Vertex.push_back(f_Vector4);
						f_Bike->vec_Vertex.push_back(f_Vector5);
						f_Bike->vec_Vertex.push_back(f_Vector6);
						f_Bike->vec_Vertex.push_back(f_Vector7);
						f_Bike->vec_Vertex.push_back(f_Vector8);

						f_Bike->vec_Color.clear();

						f_Bike->vec_Color.push_back(f_Color1);
						f_Bike->vec_Color.push_back(f_Color2);
						f_Bike->vec_Color.push_back(f_Color3);
						f_Bike->vec_Color.push_back(f_Color4);
						f_Bike->vec_Color.push_back(f_Color5);
						f_Bike->vec_Color.push_back(f_Color6);
						f_Bike->vec_Color.push_back(f_Color7);
						f_Bike->vec_Color.push_back(f_Color8);

						g_Lowton->vec_Bicycle.push_back(f_Bike);

						g_Lowton->m_adIndex.push_back(/*f_Hesh_Cade->m_adIndex[*/f_Jet/*]*/);

						std::shared_ptr<classElement> f_Element = std::make_shared_oage<classElement>(f_Bike);

						g_Lowton_Collection->m_vec_Element.push_back(f_Element);
						g_Lowton_Collection->m_idx_vec_Element++;

						//?require?g_LowtonTarget_3 = gf_Target_3; < hmm
						}

					g_Lowton->m_bckblue = f_Hesh_Cade->m_bckblue;
					g_Lowton->m_bckred = f_Hesh_Cade->m_bckred;
					g_Lowton->m_bckgreen = f_Hesh_Cade->m_bckgreen;

					g_TargetedHesh = g_Lowton;

					g_TargetedHesh->ac_IsOK();

					g_RenderHesh = true;

					//print lowton result
					bool f_Resl = g_classLMap->acTestCompute(g_Lowton_Collection, f_OCSCP_ThreadIndex, true);

	#ifdef SCP_DEBUG
					if(f_Resl == false)
						{
						throw;
						}
	#endif

					bool f_ScanX = true;
					while(f_ScanX == true)
						{
						if(f_OC_Lowton_Mark_Count >= g_Lowton_Collection->m_vec_Element.size())
							{
							f_ScanX = false;
							}
						else
							{
							if(g_Lowton_Collection->m_vec_Element[f_OC_Lowton_Mark_Count]->m_OCSCP_Flag == false)
								{
								f_ScanX = false;
								}
							else
								{
								f_OC_Lowton_Mark_Count++;
								}
							}
						}

					if(f_OC_Lowton_Mark_Count >= g_classLMap->m_ADMAX)
						{
						int f_ShareID = 1;
						int f_BlockID = 1;
						int f_JobID = 1;
						int f_EslID = 1;
						int f_TargetID = 1;
						float f_Difficulty = ECOIN_TARGET_SCP_COMPARE_THRESH; //Target Mark Threshold

						char* g_sharevalue[60];

						for(int f_Count = 0; f_Count < 60; f_Count++)
							{
							g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
							}

						::sprintf(g_sharevalue[0], "%f", (float)g_Lowton->vec_Bicycle.size());
						::sprintf(g_sharevalue[1], "%i", 1);
						::sprintf(g_sharevalue[2], "%s", "3");
						::sprintf(g_sharevalue[4], "%i", 15);
						::sprintf(g_sharevalue[5], "%i", 15);
						::sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
						::sprintf(g_sharevalue[7], "%f", f_Difficulty);

						g_LowtonHash = f_Hash;

						g_LowtonHash->acClear();

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
								g_LowtonHash->acPushFloat(g_Lowton->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < g_Lowton->m_adIndex.size(); f_Jet++)
							{
							g_LowtonHash->acPushInt(g_Lowton->m_adIndex[f_Jet]);
							}

							////////////
							//
							// Hash
							//
						std::string f_InputHash = g_LowtonHash->acGetInput();

						// check GenesisBlock (assume)
						std::string f_previousblock = "00000000000000000000000000000001";
						//ECN::Hesh...Checking Previous BlockHesh

						char blokquery[1000];

						::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

						if(f_OCP_LOCK_ON == false)
							{
							m_DB_AccessLock.lock();
							f_OCP_LOCK_ON = true;
							}

						g_SafeL[0]->acSelectCommand(blokquery, 2, false);

						int f_blokLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_blokLCount = 0;
							}
						else
							{
							f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						g_JobID = 0;

						if(f_blokLCount > 0)
							{
							g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
							g_JobID++;
							f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
							}

						f_JobID = g_JobID;

						::sprintf(g_sharevalue[3], "%i", f_JobID);

						std::string f_tx = ag_GatherTransactions(g_JobID);

						std::string f_job = f_tx + f_previousblock;

						f_InputHash += f_job;

	#if 1
						g_hasha.init(); //reset hasher state
						g_hasha.process(f_InputHash.begin(), f_InputHash.end());
						g_hasha.finish();
						picosha2::get_hash_hex_string(g_hasha, g_LowtonHash->m_OutputHash);
	#else
						g_LowtonHash->m_OutputHash = "00000000000000000000000000000000";
	#endif

						g_Lowton->m_Hash = g_LowtonHash;

						g_LowtonMark = 0;

						::sprintf(g_sharevalue[8], "%i", 0);
						::sprintf(g_sharevalue[9], "%i", 10);
						::sprintf(g_sharevalue[10], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[11], "%s", g_LowtonHash->m_OutputHash.c_str());
						::sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
						::sprintf(g_sharevalue[13], "%f", g_Lowton->m_bckred);
						::sprintf(g_sharevalue[14], "%f", g_Lowton->m_bckgreen);
						::sprintf(g_sharevalue[15], "%f", g_Lowton->m_bckblue);
						::sprintf(g_sharevalue[16], "%f", 0.0f);

						//ECN::Hesh...Sending BlockHesh
						char shlquery[1000];
						::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", g_LowtonHash->m_OutputHash.c_str());

						g_SafeL[0]->acSelectCommand(shlquery, 2, false);

						int f_ShareLCount = 0;

						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
							{
							f_ShareLCount = 0;
							}
						else
							{
							f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
							}

						if(f_ShareLCount == 0)
							{
							int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

							f_ShareID = f_ShareUniqueID;
							g_ShareID = f_ShareID;

							ag_addGenesisTracking(f_ShareUniqueID);
				
#if 0
							char* f_idquery2 = new char[150];
							::sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

							g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
							delete[] f_idquery2;

							int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
							int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

							g_PEERCNT = f_PEERCNT;
							g_SHARECNT = f_SHARECNT;
#endif

							g_CubeFieldCount = 55;

							std::shared_ptr<std::vector<std::string>> f_cubeValue = std::make_shared_oage<std::vector<std::string>>();

							for(int f_Int = 0; f_Int < g_Lowton->m_adIndex.size(); f_Int++)
								{
								shared_ptr<CubeBicycle> f_Bike = g_Lowton->vec_Bicycle[/*g_Lowton->m_adIndex[*/f_Int/*]*/];

								for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
									{
									char* f_cubeval1 = ag_ClearChar(64);
									::sprintf(f_cubeval1, "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
									f_cubeValue->push_back(f_cubeval1);
									delete f_cubeval1;

									char* f_cubeval2 = ag_ClearChar(64);
									::sprintf(f_cubeval2, "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
									f_cubeValue->push_back(f_cubeval2);
									delete f_cubeval2;

									char* f_cubeval3 = ag_ClearChar(64);
									::sprintf(f_cubeval3, "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
									f_cubeValue->push_back(f_cubeval3);
									delete f_cubeval3;
									}

								for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
									{
									char* f_cubeval1 = ag_ClearChar(64);
									::sprintf(f_cubeval1, "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
									f_cubeValue->push_back(f_cubeval1);
									delete f_cubeval1;

									char* f_cubeval2 = ag_ClearChar(64);
									::sprintf(f_cubeval2, "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
									f_cubeValue->push_back(f_cubeval2);
									delete f_cubeval2;

									char* f_cubeval3 = ag_ClearChar(64);
									::sprintf(f_cubeval3, "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
									f_cubeValue->push_back(f_cubeval3);
									delete f_cubeval3;
									}
				
								char* f_cubeval48 = ag_ClearChar(64);
								::sprintf(f_cubeval48, "%i", f_BlockID);
								f_cubeValue->push_back(f_cubeval48);
								delete f_cubeval48;

								char* f_cubeval49 = ag_ClearChar(64);
								::sprintf(f_cubeval49, "%i", f_ShareID);
								f_cubeValue->push_back(f_cubeval49);
								delete f_cubeval49;

								char* f_cubeval50 = ag_ClearChar(64);
								::sprintf(f_cubeval50, "%i", f_JobID);
								f_cubeValue->push_back(f_cubeval50);
								delete f_cubeval50;

								char* f_cubeval51 = ag_ClearChar(64);
								::sprintf(f_cubeval51, "%i", f_Int);
								f_cubeValue->push_back(f_cubeval51);
								delete f_cubeval51;

								char* f_cubeval52 = ag_ClearChar(64);
								::sprintf(f_cubeval52, "%i", 1);
								f_cubeValue->push_back(f_cubeval52);
								delete f_cubeval52;

								char* f_cubeval53 = ag_ClearChar(64);
								::sprintf(f_cubeval53, "%s", "jsd8932o39aeru");
								f_cubeValue->push_back(f_cubeval53);
								delete f_cubeval53;

								char* f_cubeval54 = ag_ClearChar(64);
								::sprintf(f_cubeval54, "%f", f_Difficulty);
								f_cubeValue->push_back(f_cubeval54);
								delete f_cubeval54;
								}

							int f_OK = g_SafeL[0]->InsertM("cube", (const char**)g_cubefield, f_cubeValue, g_CubeFieldCount, g_Lowton->m_adIndex.size(), 2, false);

							// ECN::Lowton Share Submitted
							std::shared_ptr<Ackent> f_Ack = std::make_shared_oage<Ackent>(ACK_TYPE_SHARE, g_ShareID, 1/*f_PEERCNT*/);
							f_Ack->m_ECN = 0.0f;
							f_Ack->m_Reward = 50.0f;
							f_Ack->m_Origin = 1;
							f_Ack->m_Owner = g_Wallet->GetAdr();
							g_Ackent.push_back(f_Ack);

							g_Compressing = 0;
							}
						//else // Duplicate Block Found.
						}

					if(g_Compressing == 1)
						{
						int f_CompletedIndex = f_AttackIndex + f_IntegerResult;
						int f_UpperFalse = f_ElementOnce - f_IntegerResult;

						int f_AllElementIndex = f_CompletedIndex + f_UpperFalse;

						if(f_AllElementIndex > f_Collection->m_vec_Element.size())
							{
							f_AllElementIndex = f_Collection->m_vec_Element.size();
							}

						for(int f_XYZ = f_CompletedIndex; f_XYZ < f_AllElementIndex; f_XYZ++)
							{
							f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag = false;
							}

						g_Result = false;
						}

					mutex_swap.unlock();
					}
				else
					{
					for(int f_XYZ = f_Collection->m_vec_Element.size() - f_ElementOnce; f_XYZ < f_Collection->m_vec_Element.size(); f_XYZ++)
						{
						f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag = false;
						}
					}
				}
			else
				{
				for(int f_XYZ = f_Collection->m_vec_Element.size() - f_ElementOnce; f_XYZ < f_Collection->m_vec_Element.size(); f_XYZ++)
					{
					f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag = false;
					}
				}
			}
		else
			{
			if((g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] == CPS_DRAW) && (g_Result == false))
				{
				g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] = CPS_SCAN;
				}

			for(int f_XYZ = f_Collection->m_vec_Element.size() - f_ElementOnce; f_XYZ < f_Collection->m_vec_Element.size(); f_XYZ++)
				{
				f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag = false;
				}
			}

		if(f_OCP_LOCK_ON == true)
			{
			m_DB_AccessLock.unlock();
			f_OCP_LOCK_ON = false;
			}
		}

	 ///////////////////////////////////////////////////
	// not safe for multiple miner windows open on
	g_ElementDivisor.pop_back();
	g_ElementDivisorInt.pop_back();
	g_classLMap->m_SchemaRef.pop_back();
	g_classLMap->m_SaveSchemaRef.pop_back();
	g_classLMap->m_SchemaMeasureIndex.pop_back();
	g_classLMap->m_CPS_Result.pop_back();
}

#endif
#ifdef SCP_REFLECT

void Sample3DSceneRenderer::acGen_GenHesh(void)
{
	g_ref_CurrentPath = "Sample3DSceneRenderer::acGen_GenHesh";
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Hesh_Cade");
	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared<Cube::CubeHESH>(g_ADMAX, g_ADHIGH, g_ADLOW);
	g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Hash");
	std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared<Cube::CubeHASH_originstring>();

	bool f_Result = false;

	if(g_KeepShare == false)
		{
		for(int f_Int = 0; f_Int < f_Hesh_Cade->m_ADMAX; f_Int++)
			{
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Bike");
			std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>(); // Cube::g_BicycleContainer[0].vec_Key[f_Int];

			f_Bike->vec_Vertex.clear();

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector1");
			std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
			f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector2");
			std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
			f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector3");
			std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
			f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector4");
			std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
			f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector5");
			std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
			f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector6");
			std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
			f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector7");
			std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
			f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Vector8");
			std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, 0.5f);
			f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color1");
			std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color2");
			std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color3");
			std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color4");
			std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color5");
			std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color6");
			std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color7");
			std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Color8");
			std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1->acRun_visualminer();
			f_Vector2->acRun_visualminer();
			f_Vector3->acRun_visualminer();
			f_Vector4->acRun_visualminer();
			f_Vector5->acRun_visualminer();
			f_Vector6->acRun_visualminer();
			f_Vector7->acRun_visualminer();
			f_Vector8->acRun_visualminer();

#if 1
			f_Vector1->acResolve_precision();
			f_Vector2->acResolve_precision();
			f_Vector3->acResolve_precision();
			f_Vector4->acResolve_precision();
			f_Vector5->acResolve_precision();
			f_Vector6->acResolve_precision();
			f_Vector7->acResolve_precision();
			f_Vector8->acResolve_precision();
#endif

			f_Hash->acPushFloat(f_Vector1->m_X);
			f_Hash->acPushFloat(f_Vector1->m_Y);
			f_Hash->acPushFloat(f_Vector1->m_Z);
			f_Hash->acPushFloat(f_Vector2->m_X);
			f_Hash->acPushFloat(f_Vector2->m_Y);
			f_Hash->acPushFloat(f_Vector2->m_Z);
			f_Hash->acPushFloat(f_Vector3->m_X);
			f_Hash->acPushFloat(f_Vector3->m_Y);
			f_Hash->acPushFloat(f_Vector3->m_Z);
			f_Hash->acPushFloat(f_Vector4->m_X);
			f_Hash->acPushFloat(f_Vector4->m_Y);
			f_Hash->acPushFloat(f_Vector4->m_Z);
			f_Hash->acPushFloat(f_Vector5->m_X);
			f_Hash->acPushFloat(f_Vector5->m_Y);
			f_Hash->acPushFloat(f_Vector5->m_Z);
			f_Hash->acPushFloat(f_Vector6->m_X);
			f_Hash->acPushFloat(f_Vector6->m_Y);
			f_Hash->acPushFloat(f_Vector6->m_Z);
			f_Hash->acPushFloat(f_Vector7->m_X);
			f_Hash->acPushFloat(f_Vector7->m_Y);
			f_Hash->acPushFloat(f_Vector7->m_Z);
			f_Hash->acPushFloat(f_Vector8->m_X);
			f_Hash->acPushFloat(f_Vector8->m_Y);
			f_Hash->acPushFloat(f_Vector8->m_Z);

			f_Bike->vec_Vertex.push_back(f_Vector1);
			f_Bike->vec_Vertex.push_back(f_Vector2);
			f_Bike->vec_Vertex.push_back(f_Vector3);
			f_Bike->vec_Vertex.push_back(f_Vector4);
			f_Bike->vec_Vertex.push_back(f_Vector5);
			f_Bike->vec_Vertex.push_back(f_Vector6);
			f_Bike->vec_Vertex.push_back(f_Vector7);
			f_Bike->vec_Vertex.push_back(f_Vector8);

			f_Hash->acPushFloat(f_Color1->m_X);
			f_Hash->acPushFloat(f_Color1->m_Y);
			f_Hash->acPushFloat(f_Color1->m_Z);
			f_Hash->acPushFloat(f_Color2->m_X);
			f_Hash->acPushFloat(f_Color2->m_Y);
			f_Hash->acPushFloat(f_Color2->m_Z);
			f_Hash->acPushFloat(f_Color3->m_X);
			f_Hash->acPushFloat(f_Color3->m_Y);
			f_Hash->acPushFloat(f_Color3->m_Z);
			f_Hash->acPushFloat(f_Color4->m_X);
			f_Hash->acPushFloat(f_Color4->m_Y);
			f_Hash->acPushFloat(f_Color4->m_Z);
			f_Hash->acPushFloat(f_Color5->m_X);
			f_Hash->acPushFloat(f_Color5->m_Y);
			f_Hash->acPushFloat(f_Color5->m_Z);
			f_Hash->acPushFloat(f_Color6->m_X);
			f_Hash->acPushFloat(f_Color6->m_Y);
			f_Hash->acPushFloat(f_Color6->m_Z);
			f_Hash->acPushFloat(f_Color7->m_X);
			f_Hash->acPushFloat(f_Color7->m_Y);
			f_Hash->acPushFloat(f_Color7->m_Z);
			f_Hash->acPushFloat(f_Color8->m_X);
			f_Hash->acPushFloat(f_Color8->m_Y);
			f_Hash->acPushFloat(f_Color8->m_Z);

			f_Bike->vec_Color.clear();

			f_Bike->vec_Color.push_back(f_Color1);
			f_Bike->vec_Color.push_back(f_Color2);
			f_Bike->vec_Color.push_back(f_Color3);
			f_Bike->vec_Color.push_back(f_Color4);
			f_Bike->vec_Color.push_back(f_Color5);
			f_Bike->vec_Color.push_back(f_Color6);
			f_Bike->vec_Color.push_back(f_Color7);
			f_Bike->vec_Color.push_back(f_Color8);

			f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);
			}

		//hesh admax limiter
		float f_Finger = Cube::random();

#ifndef ECOIN_ADMAX
		float f_LimitSenseFLT = (((float)f_Hesh_Cade->m_ADMAX - ECOIN_HESH_MINIMUM) * f_Finger) + ECOIN_HESH_MINIMUM;
		int f_LimitSense = (int)f_LimitSenseFLT;
#else
		int f_LimitSense = f_Hesh_Cade->m_ADMAX;
#endif

		int f_PORTcntr = 0;
		while(f_Hesh_Cade->m_adIndex.size() < f_LimitSense)
			{
			f_Hesh_Cade->m_adIndex.push_back(f_PORTcntr);
			f_Hash->acPushInt((unsigned int)f_PORTcntr);

			f_PORTcntr++;
			}

		Cube::BiVector f_ColorBCK(Cube::random(), Cube::random(), Cube::random());

		f_Hash->acPushFloat(f_ColorBCK.m_X);
		f_Hash->acPushFloat(f_ColorBCK.m_Y);
		f_Hash->acPushFloat(f_ColorBCK.m_Z);

		f_Hesh_Cade->m_bckred = f_ColorBCK.m_X;
		f_Hesh_Cade->m_bckgreen = f_ColorBCK.m_Y;
		f_Hesh_Cade->m_bckblue = f_ColorBCK.m_Z;

		f_Hesh_Cade->ac_IsOK();

		  ////////////
		 // HESH   //
		// Target //
		float f_Difficulty = ECOIN_TARGET_COMPARE_THRESH; //Target Mark Threshold

		//g_Type Switch
		switch(g_Type)
			{
			case 0:
			case 1:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget> f_Target = std::make_shared<classTarget>(f_Hesh_Cade);

				f_Result = g_Target_1->acCompare(f_Target, 80.55f, f_Difficulty, true);

				gf_Target_1 = f_Target;

				 /////////////////
				// Match Check //
				float f_Mark = f_Target->m_Mark;

				float f_MatchMark = g_Target_1->acMatch(f_Target);

				if(f_MatchMark < ECOIN_TARGET_MATCH_THRESH)
					{
					f_Result = true;
					}

				if(f_MatchMark > ECOIN_TARGET_MATCH_THRESH_UP)
					{
					f_Result = false;
					}

				gf_Target_1->m_Mark = (f_MatchMark * ECOIN_TARGET_MATCH_MIXIN) * gf_Target_1->m_Mark;
				}break;

			case 2:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget> f_Target = std::make_shared<classTarget>(f_Hesh_Cade);

				f_Result = g_Target_2->acCompare(f_Target, 80.55f, f_Difficulty, true);

				gf_Target_2 = f_Target;

					/////////////////
				// Match Check //
				float f_Mark = gf_Target_2->m_Mark;

				float f_MatchMark = g_Target_2->acMatch(f_Target);

				if(f_MatchMark < ECOIN_TARGET_MATCH_THRESH)
					{
					f_Result = true;
					}

				if(f_MatchMark > ECOIN_TARGET_MATCH_THRESH_UP)
					{
					f_Result = false;
					}

				gf_Target_2->m_Mark = (f_MatchMark * ECOIN_TARGET_MATCH_MIXIN) * gf_Target_2->m_Mark;
				}break;

			case 3:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared<classTarget_Ecom>();

				g_QcomManager->acClearGrid();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_3);

				//f_Result = g_Target_3->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_3 = f_Target;
				}break;

			case 4:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared<classTarget_Ecom>();

				g_QcomManager->acClearGrid();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_4);

				//f_Result = g_Target_4->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_4 = f_Target;
				}break;

			case 5:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared<classTarget_ESL_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_5);

				//f_Result = g_Target_5->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_5 = f_Target;
				}break;

			case 6:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared<classTarget_ESL_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_6);

				//f_Result = g_Target_6->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_6 = f_Target;
				}break;
			case 7:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared<classTarget_Generation_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_7);

				//f_Result = g_Target_7->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_7 = f_Target;
				}break;

			case 8:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared<classTarget_Generation_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_8);

				//f_Result = g_Target_8->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_8 = f_Target;
				}break;

			case 9:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_JScript> f_Target = std::make_shared<classTarget_JScript>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_9);

				//f_Result = g_Target_9->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_9 = f_Target;
				}break;

			case 10:
				{
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Target");
				std::shared_ptr<classTarget_JScript> f_Target = std::make_shared<classTarget_JScript>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_10);

				//f_Result = g_Target_10->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_10 = f_Target;
				}break;
			}

		g_ElementCount += f_Hesh_Cade->m_adIndex.size();
		}

	   ////////////
	  //
	 // Hash
	//
	int f_ShareID = 1;
	int f_BlockID = 1;
	int f_JobID = 1;	//Fixme pass out jobid
	int f_EslID = 1;
	int f_TargetID = 1;
	float f_Difficulty = ECOIN_TARGET_COMPARE_THRESH; //Target Mark Threshold

	if((f_Result == true) && (g_KeepShare == false))
		{
		f_Hesh_Cade->m_Hash = f_Hash;

		char* g_sharevalue[60];

		for(int f_Count = 0; f_Count < 60; f_Count++)
			{
			g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
			}

		sprintf(g_sharevalue[0], "%f", ag_Get_current_Target_Mark(g_Type));
		sprintf(g_sharevalue[1], "%i", 1);
		sprintf(g_sharevalue[2], "%s", "3");
		sprintf(g_sharevalue[4], "%i", f_EslID);
		sprintf(g_sharevalue[5], "%i", f_TargetID);
		sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
		sprintf(g_sharevalue[7], "%f", f_Difficulty);

		   ////////////
		  //
		 // Hash
		//
		std::string f_InputHash = f_Hash->acGetInput();

		// check GenesisBlock (assume)
		std::string f_previousblock = "00000000000000000000000000000001";
		//ECN::Hesh...Checking Previous BlockHesh\n");

		m_DB_AccessLock.lock();

		char blokquery[1000];
		sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

		g_SafeL[0]->acSelectCommand(blokquery, 2, false);

		int f_blokLCount = 0;

		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
			{
			f_blokLCount = 0;
			}
		else
			{
			f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
			}

		//ECN::Stat::: f_JobID - f_blokLCount);
		g_JobID = 0;

		if(f_blokLCount > 0)
			{
			g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
			g_JobID++;
			f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
			}

		f_JobID = g_JobID;

		sprintf(g_sharevalue[3], "%i", f_JobID);

		//ECN::Stat::: g_JobID

		std::string f_tx = ag_GatherTransactions(g_JobID);

		std::string f_job = f_tx + f_previousblock;

		f_InputHash += f_job;

#if 1
		g_hasha.init(); //reset hasher state
		g_hasha.process(f_InputHash.begin(), f_InputHash.end());
		g_hasha.finish();
		picosha2::get_hash_hex_string(g_hasha, f_Hash->m_OutputHash);
#else
		f_Hash->m_OutputHash = "00000000000000000000000000000000";
#endif

		f_Hesh_Cade->m_Hash = f_Hash;

		//ShareHash-f_Hash->m_OutputHash

		sprintf(g_sharevalue[8], "%i", 0);
		sprintf(g_sharevalue[9], "%i", 10);
		sprintf(g_sharevalue[10], "%s", f_Hash->m_OutputHash.c_str());
		sprintf(g_sharevalue[11], "%s", f_Hash->m_OutputHash.c_str());
		sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
		sprintf(g_sharevalue[13], "%f", f_Hesh_Cade->m_bckred);
		sprintf(g_sharevalue[14], "%f", f_Hesh_Cade->m_bckgreen);
		sprintf(g_sharevalue[15], "%f", f_Hesh_Cade->m_bckblue);
		sprintf(g_sharevalue[16], "%f", 0.0f);

		//ECN::Hesh...Sending BlockHesh.

		char shlquery[1000];
		sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Hash->m_OutputHash.c_str());

		g_SafeL[0]->acSelectCommand(shlquery, 2, false);

		int f_ShareLCount = 0;

		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
			{
			f_ShareLCount = 0;
			}
		else
			{
			f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
			}

		//ECN::Stat::: f_ShareLCount

		if(f_ShareLCount == 0)
			{
			int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

			f_ShareID = f_ShareUniqueID;
			g_ShareID = f_ShareID;

			//ECN::Stat::: f_ShareID f_shareuniqueID

			ag_addGenesisTracking(f_ShareUniqueID);
				
			char* f_idquery2 = new char[150];
			sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

			g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
			delete[] f_idquery2;

			int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
			int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

			g_PEERCNT = f_PEERCNT;
			g_SHARECNT = f_SHARECNT;

			for(int f_Int = 0; f_Int < f_Hesh_Cade->m_adIndex.size(); f_Int++)
				{
				std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[f_Hesh_Cade->m_adIndex[f_Int]];

				char* g_cubevalue[60];

				for(int f_Count = 0; f_Count < 60; f_Count++)
					{
					g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
					}

				for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
					{
					sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
					sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
					sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
					}

				for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
					{
					sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
					sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
					sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
					}
				
				sprintf(g_cubevalue[48], "%i", f_BlockID);
				sprintf(g_cubevalue[49], "%i", f_ShareID);
				sprintf(g_cubevalue[50], "%i", f_JobID);
				sprintf(g_cubevalue[51], "%i", f_Int);
				sprintf(g_cubevalue[52], "%i", f_TargetID);
				sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
				sprintf(g_cubevalue[54], "%f", f_Difficulty);

				g_CubeFieldCount = 55;

				int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
				}

			//ECN::Share Submitted.
			g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Ack");
			std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
			f_Ack->m_ECN = 0.0f;
			f_Ack->m_Reward = 50.0f;
			f_Ack->m_Origin = 1;
			f_Ack->m_Owner = g_Wallet->GetAdr();
			g_Ackent.push_back(f_Ack);
			}
		else
			{
			//Duplicate Block Found.
			f_Result = false;
			}

		m_DB_AccessLock.unlock();
		}
	else
		{
		float f_Mark = ag_Get_current_Target_Mark(g_Type);

		if((f_Mark < g_LowtonMark) && (g_KeepShare == false))
			{
			g_LowtonMark = f_Mark;
			g_Lowton = f_Hesh_Cade;
			g_LowtonHash = f_Hash;

			switch(g_Type)
				{
				case 0:
				case 1:
					{
					g_LowtonTarget_1 = gf_Target_1;
					}break;
				case 2:
					{
					g_LowtonTarget_2 = gf_Target_2;
					}break;
				case 3:
					{
					g_LowtonTarget_3 = gf_Target_3;
					}break;
				case 4:
					{
					g_LowtonTarget_4 = gf_Target_4;
					}break;
				case 5:
					{
					g_LowtonTarget_5 = gf_Target_5;
					}break;
				case 6:
					{
					g_LowtonTarget_6 = gf_Target_6;
					}break;
				case 7:
					{
					g_LowtonTarget_7 = gf_Target_7;
					}break;
				case 8:
					{
					g_LowtonTarget_8 = gf_Target_8;
					}break;
				case 9:
					{
					g_LowtonTarget_9 = gf_Target_9;
					}break;
				case 10:
					{
					g_LowtonTarget_10 = gf_Target_10;
					}break;
				}

			g_TargetedHesh->ac_IsOK();

			g_TargetedHesh = g_Lowton;

			g_RenderHesh = true;

			//New LowTon Holding... g_LowtonMark
			}

		time(&g_currenttime);

		if(g_currenttime > g_storagetime)
			{
			time(&g_storagetime);
			g_storagetime += ECOIN_TARGET_LOWTON_STORAGE;

			char* g_sharevalue[60];

			for(int f_Count = 0; f_Count < 60; f_Count++)
				{
				g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
				}

			sprintf(g_sharevalue[0], "%f", g_LowtonMark);
			sprintf(g_sharevalue[1], "%i", 1);
			sprintf(g_sharevalue[2], "%s", "3");
			sprintf(g_sharevalue[4], "%i", 15);
			sprintf(g_sharevalue[5], "%i", 15);
			sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
			sprintf(g_sharevalue[7], "%f", f_Difficulty);

			   ////////////
			  //
			 // Hash
			//
			std::string f_InputHash = g_LowtonHash->acGetInput();

			// check GenesisBlock (assume)
			std::string f_previousblock = "00000000000000000000000000000001";
			//ECN::Hesh...Checking Previous BlockHesh.

			char blokquery[1000];
			sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

			m_DB_AccessLock.lock();

			g_SafeL[0]->acSelectCommand(blokquery, 2, false);

			int f_blokLCount = 0;
			
			if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
				{
				f_blokLCount = 0;
				}
			else
				{
				f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
				}

			//ECN::Stat::: f_TrxLCount

			g_JobID = 0;

			if(f_blokLCount > 0)
				{
				g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
				g_JobID++;
				f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
				}

			f_JobID = g_JobID;

			sprintf(g_sharevalue[3], "%i", f_JobID);

			//ECN::Stat::: g_JobID

			std::string f_tx = ag_GatherTransactions(g_JobID);

			std::string f_job = f_tx + f_previousblock;

			f_InputHash += f_job;

#if 1
			g_hasha.init(); //reset hasher state
			g_hasha.process(f_InputHash.begin(), f_InputHash.end());
			g_hasha.finish();
			picosha2::get_hash_hex_string(g_hasha, g_LowtonHash->m_OutputHash);
#else
			g_LowtonHash->m_OutputHash = "00000000000000000000000000000000";
#endif

			g_Lowton->m_Hash = g_LowtonHash;

			g_LowtonMark = FLT_MAX;

			//ShareHash-g_LowtonHash->m_OutputHash

			sprintf(g_sharevalue[8], "%i", 0);
			sprintf(g_sharevalue[9], "%i", 10);
			sprintf(g_sharevalue[10], "%s", g_LowtonHash->m_OutputHash.c_str());
			sprintf(g_sharevalue[11], "%s", g_LowtonHash->m_OutputHash.c_str());
			sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
			sprintf(g_sharevalue[13], "%f", g_Lowton->m_bckred);
			sprintf(g_sharevalue[14], "%f", g_Lowton->m_bckgreen);
			sprintf(g_sharevalue[15], "%f", g_Lowton->m_bckblue);
			sprintf(g_sharevalue[16], "%f", 0.0f);

			//ECN::Hesh...Sending BlockHesh.

			char shlquery[1000];
			sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", g_LowtonHash->m_OutputHash.c_str());

			g_SafeL[0]->acSelectCommand(shlquery, 2, false);

			int f_ShareLCount = 0;
		
			if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
				{
				f_ShareLCount = 0;
				}
			else
				{
				f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
				}

			//ECN::Stat::: f_ShareLCount

			if(f_ShareLCount == 0)
				{
				int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

				f_ShareID = f_ShareUniqueID;
				g_ShareID = f_ShareID;

				//ECN::Stat::: f_ShareID f_shareuniqueID

				ag_addGenesisTracking(f_ShareUniqueID);
				
				char* f_idquery2 = new char[150];
				sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

				g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
				delete[] f_idquery2;

				int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
				int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

				g_PEERCNT = f_PEERCNT;
				g_SHARECNT = f_SHARECNT;

				for(int f_Int = 0; f_Int < g_Lowton->m_adIndex.size(); f_Int++)
					{
					shared_ptr<CubeBicycle> f_Bike = g_Lowton->vec_Bicycle[g_Lowton->m_adIndex[f_Int]];
					char* g_cubevalue[60];

					for(int f_Count = 0; f_Count < 60; f_Count++)
						{
						g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
						}

					for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
						{
						sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
						sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
						sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
						}

					for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
						{
						sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
						sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
						sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
						}
				
					sprintf(g_cubevalue[48], "%i", f_BlockID);
					sprintf(g_cubevalue[49], "%i", f_ShareID);
					sprintf(g_cubevalue[50], "%i", f_JobID);
					sprintf(g_cubevalue[51], "%i", f_Int);
					sprintf(g_cubevalue[52], "%i", 1);	//FIXME ADD L-TARGETID
					sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
					sprintf(g_cubevalue[54], "%f", f_Difficulty);

					g_CubeFieldCount = 55;

					int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
					}

				//ECN::Lowton Share Submitted.
				g_vec_ref_ObjectName.push_back(g_ref_CurrentPath + "f_Ack");
				std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
				f_Ack->m_ECN = 0.0f;
				f_Ack->m_Reward = 50.0f;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = g_Wallet->GetAdr();
				g_Ackent.push_back(f_Ack);
				}
			else
				{
				//Duplicate Block Found.
				f_Result = false;
				}

			m_DB_AccessLock.unlock();
			}
		}
}

#else

void Sample3DSceneRenderer::acGen_GenHesh(void)
{
	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared<Cube::CubeHESH>(g_ADMAX, g_ADHIGH, g_ADLOW);
	std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared<Cube::CubeHASH_originstring>();

	bool f_Result = false;

	if(g_KeepShare == false)
		{
		for(int f_Int = 0; f_Int < f_Hesh_Cade->m_ADMAX; f_Int++)
			{
			std::shared_ptr<CubeBicycle> f_Bike = std::make_shared<Cube::CubeBicycle>(); // Cube::g_BicycleContainer[0].vec_Key[f_Int];

			f_Bike->vec_Vertex.clear();

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
			f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
			f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
			f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
			f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
			f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
			f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
			f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, 0.5f);
			f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1->acRun_visualminer();
			f_Vector2->acRun_visualminer();
			f_Vector3->acRun_visualminer();
			f_Vector4->acRun_visualminer();
			f_Vector5->acRun_visualminer();
			f_Vector6->acRun_visualminer();
			f_Vector7->acRun_visualminer();
			f_Vector8->acRun_visualminer();

#if 1
			f_Vector1->acResolve_precision(SCP_FLT_SCALE);
			f_Vector2->acResolve_precision(SCP_FLT_SCALE);
			f_Vector3->acResolve_precision(SCP_FLT_SCALE);
			f_Vector4->acResolve_precision(SCP_FLT_SCALE);
			f_Vector5->acResolve_precision(SCP_FLT_SCALE);
			f_Vector6->acResolve_precision(SCP_FLT_SCALE);
			f_Vector7->acResolve_precision(SCP_FLT_SCALE);
			f_Vector8->acResolve_precision(SCP_FLT_SCALE);
#endif

			f_Hash->acPushFloat(f_Vector1->m_X);
			f_Hash->acPushFloat(f_Vector1->m_Y);
			f_Hash->acPushFloat(f_Vector1->m_Z);
			f_Hash->acPushFloat(f_Vector2->m_X);
			f_Hash->acPushFloat(f_Vector2->m_Y);
			f_Hash->acPushFloat(f_Vector2->m_Z);
			f_Hash->acPushFloat(f_Vector3->m_X);
			f_Hash->acPushFloat(f_Vector3->m_Y);
			f_Hash->acPushFloat(f_Vector3->m_Z);
			f_Hash->acPushFloat(f_Vector4->m_X);
			f_Hash->acPushFloat(f_Vector4->m_Y);
			f_Hash->acPushFloat(f_Vector4->m_Z);
			f_Hash->acPushFloat(f_Vector5->m_X);
			f_Hash->acPushFloat(f_Vector5->m_Y);
			f_Hash->acPushFloat(f_Vector5->m_Z);
			f_Hash->acPushFloat(f_Vector6->m_X);
			f_Hash->acPushFloat(f_Vector6->m_Y);
			f_Hash->acPushFloat(f_Vector6->m_Z);
			f_Hash->acPushFloat(f_Vector7->m_X);
			f_Hash->acPushFloat(f_Vector7->m_Y);
			f_Hash->acPushFloat(f_Vector7->m_Z);
			f_Hash->acPushFloat(f_Vector8->m_X);
			f_Hash->acPushFloat(f_Vector8->m_Y);
			f_Hash->acPushFloat(f_Vector8->m_Z);

			f_Bike->vec_Vertex.push_back(f_Vector1);
			f_Bike->vec_Vertex.push_back(f_Vector2);
			f_Bike->vec_Vertex.push_back(f_Vector3);
			f_Bike->vec_Vertex.push_back(f_Vector4);
			f_Bike->vec_Vertex.push_back(f_Vector5);
			f_Bike->vec_Vertex.push_back(f_Vector6);
			f_Bike->vec_Vertex.push_back(f_Vector7);
			f_Bike->vec_Vertex.push_back(f_Vector8);

			f_Hash->acPushFloat(f_Color1->m_X);
			f_Hash->acPushFloat(f_Color1->m_Y);
			f_Hash->acPushFloat(f_Color1->m_Z);
			f_Hash->acPushFloat(f_Color2->m_X);
			f_Hash->acPushFloat(f_Color2->m_Y);
			f_Hash->acPushFloat(f_Color2->m_Z);
			f_Hash->acPushFloat(f_Color3->m_X);
			f_Hash->acPushFloat(f_Color3->m_Y);
			f_Hash->acPushFloat(f_Color3->m_Z);
			f_Hash->acPushFloat(f_Color4->m_X);
			f_Hash->acPushFloat(f_Color4->m_Y);
			f_Hash->acPushFloat(f_Color4->m_Z);
			f_Hash->acPushFloat(f_Color5->m_X);
			f_Hash->acPushFloat(f_Color5->m_Y);
			f_Hash->acPushFloat(f_Color5->m_Z);
			f_Hash->acPushFloat(f_Color6->m_X);
			f_Hash->acPushFloat(f_Color6->m_Y);
			f_Hash->acPushFloat(f_Color6->m_Z);
			f_Hash->acPushFloat(f_Color7->m_X);
			f_Hash->acPushFloat(f_Color7->m_Y);
			f_Hash->acPushFloat(f_Color7->m_Z);
			f_Hash->acPushFloat(f_Color8->m_X);
			f_Hash->acPushFloat(f_Color8->m_Y);
			f_Hash->acPushFloat(f_Color8->m_Z);

			f_Bike->vec_Color.clear();

			f_Bike->vec_Color.push_back(f_Color1);
			f_Bike->vec_Color.push_back(f_Color2);
			f_Bike->vec_Color.push_back(f_Color3);
			f_Bike->vec_Color.push_back(f_Color4);
			f_Bike->vec_Color.push_back(f_Color5);
			f_Bike->vec_Color.push_back(f_Color6);
			f_Bike->vec_Color.push_back(f_Color7);
			f_Bike->vec_Color.push_back(f_Color8);

			f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);
			}

		//hesh admax limiter
		float f_Finger = Cube::random();

#ifndef ECOIN_ADMAX
		float f_LimitSenseFLT = (((float)f_Hesh_Cade->m_ADMAX - ECOIN_HESH_MINIMUM) * f_Finger) + ECOIN_HESH_MINIMUM;
		int f_LimitSense = (int)f_LimitSenseFLT;
#else
		int f_LimitSense = f_Hesh_Cade->m_ADMAX;
#endif

		int f_PORTcntr = 0;
		while(f_Hesh_Cade->m_adIndex.size() < f_LimitSense)
			{
			f_Hesh_Cade->m_adIndex.push_back(f_PORTcntr);
			f_Hash->acPushInt((unsigned int)f_PORTcntr);

			f_PORTcntr++;
			}

		Cube::BiVector f_ColorBCK(Cube::random(), Cube::random(), Cube::random());

		f_Hash->acPushFloat(f_ColorBCK.m_X);
		f_Hash->acPushFloat(f_ColorBCK.m_Y);
		f_Hash->acPushFloat(f_ColorBCK.m_Z);

		f_Hesh_Cade->m_bckred = f_ColorBCK.m_X;
		f_Hesh_Cade->m_bckgreen = f_ColorBCK.m_Y;
		f_Hesh_Cade->m_bckblue = f_ColorBCK.m_Z;

		f_Hesh_Cade->ac_IsOK();

		  ////////////
		 // HESH   //
		// Target //
		float f_Difficulty = ECOIN_TARGET_COMPARE_THRESH; //Target Mark Threshold

		//g_Type Switch
		switch(g_Type)
			{
			case 0:
			case 1:
				{
				std::shared_ptr<classTarget> f_Target = std::make_shared<classTarget>(f_Hesh_Cade);

				f_Result = g_Target_1->acCompare(f_Target, 80.55f, f_Difficulty, true);

				gf_Target_1 = f_Target;

				 /////////////////
				// Match Check //
				float f_MatchMark = g_Target_1->acMatch(f_Target);

				if(f_MatchMark < ECOIN_TARGET_MATCH_THRESH)
					{
					f_Result = true;
					}

				if(f_MatchMark > ECOIN_TARGET_MATCH_THRESH_UP)
					{
					f_Result = false;
					}

				gf_Target_1->m_Mark = (f_MatchMark * ECOIN_TARGET_MATCH_MIXIN) * gf_Target_1->m_Mark;
				}break;

			case 2:
				{
				std::shared_ptr<classTarget> f_Target = std::make_shared<classTarget>(f_Hesh_Cade);

				f_Result = g_Target_2->acCompare(f_Target, 80.55f, f_Difficulty, true);

				gf_Target_2 = f_Target;

				 /////////////////
				// Match Check //
				float f_MatchMark = g_Target_2->acMatch(f_Target);

				if(f_MatchMark < ECOIN_TARGET_MATCH_THRESH)
					{
					f_Result = true;
					}

				if(f_MatchMark > ECOIN_TARGET_MATCH_THRESH_UP)
					{
					f_Result = false;
					}

				gf_Target_2->m_Mark = (f_MatchMark * ECOIN_TARGET_MATCH_MIXIN) * gf_Target_2->m_Mark;
				}break;

			case 3:
				{
				std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared<classTarget_Ecom>();

				g_QcomManager->acClearGrid();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_3);

				//f_Result = g_Target_3->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_3 = f_Target;
				}break;

			case 4:
				{
				std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared<classTarget_Ecom>();

				g_QcomManager->acClearGrid();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_4);

				//f_Result = g_Target_4->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_4 = f_Target;
				}break;

			case 5:
				{
				std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared<classTarget_ESL_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_5);

				//f_Result = g_Target_5->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_5 = f_Target;
				}break;

			case 6:
				{
				std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared<classTarget_ESL_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_6);

				//f_Result = g_Target_6->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_6 = f_Target;
				}break;
			case 7:
				{
				std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared<classTarget_Generation_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_7);

				//f_Result = g_Target_7->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_7 = f_Target;
				}break;

			case 8:
				{
				std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared<classTarget_Generation_Script>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_8);

				//f_Result = g_Target_8->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_8 = f_Target;
				}break;

			case 9:
				{
				std::shared_ptr<classTarget_JScript> f_Target = std::make_shared<classTarget_JScript>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_9);

				//f_Result = g_Target_9->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_9 = f_Target;
				}break;

			case 10:
				{
				std::shared_ptr<classTarget_JScript> f_Target = std::make_shared<classTarget_JScript>();

				f_Target->acFromHesh(f_Hesh_Cade, g_Target_10);

				//f_Result = g_Target_10->acCompare(f_Target, 80.55f, f_Difficulty);

				gf_Target_10 = f_Target;
				}break;
			}

		g_ElementCount += f_Hesh_Cade->m_adIndex.size();
		}

	   ////////////
	  //
	 // Hash
	//
	int f_ShareID = 1;
	int f_BlockID = 1;
	int f_JobID = 1;	//Fixme pass out jobid
	int f_EslID = 1;
	int f_TargetID = 1;
	float f_Difficulty = ECOIN_TARGET_COMPARE_THRESH; //Target Mark Threshold

	if((f_Result == true) && (g_KeepShare == false))
		{
		f_Hesh_Cade->m_Hash = f_Hash;

		char* g_sharevalue[60];

		for(int f_Count = 0; f_Count < 60; f_Count++)
			{
			g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
			}

		sprintf(g_sharevalue[0], "%f", ag_Get_current_Target_Mark(g_Type));
		sprintf(g_sharevalue[1], "%i", 1);
		sprintf(g_sharevalue[2], "%s", "3");
		sprintf(g_sharevalue[4], "%i", f_EslID);
		sprintf(g_sharevalue[5], "%i", f_TargetID);
		sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
		sprintf(g_sharevalue[7], "%f", f_Difficulty);

		   ////////////
		  //
		 // Hash
		//
		std::string f_InputHash = f_Hash->acGetInput();

		// check GenesisBlock (assume)
		std::string f_previousblock = "00000000000000000000000000000001";
		//ECN::Hesh...Checking Previous BlockHesh\n");

		m_DB_AccessLock.lock();

		char blokquery[1000];
		sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

		g_SafeL[0]->acSelectCommand(blokquery, 2, false);

		int f_blokLCount = 0;

		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
			{
			f_blokLCount = 0;
			}
		else
			{
			f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
			}

		//ECN::Stat::: f_JobID - f_blokLCount);
		g_JobID = 0;

		if(f_blokLCount > 0)
			{
			g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
			g_JobID++;
			f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
			}

		f_JobID = g_JobID;

		sprintf(g_sharevalue[3], "%i", f_JobID);

		//ECN::Stat::: g_JobID

		std::string f_tx = ag_GatherTransactions(g_JobID);

		std::string f_job = f_tx + f_previousblock;

		f_InputHash += f_job;

#if 1
		g_hasha.init(); //reset hasher state
		g_hasha.process(f_InputHash.begin(), f_InputHash.end());
		g_hasha.finish();
		picosha2::get_hash_hex_string(g_hasha, f_Hash->m_OutputHash);
#else
		f_Hash->m_OutputHash = "00000000000000000000000000000000";
#endif

		f_Hesh_Cade->m_Hash = f_Hash;

		//ShareHash-f_Hash->m_OutputHash

		sprintf(g_sharevalue[8], "%i", 0);
		sprintf(g_sharevalue[9], "%i", 10);
		sprintf(g_sharevalue[10], "%s", f_Hash->m_OutputHash.c_str());
		sprintf(g_sharevalue[11], "%s", f_Hash->m_OutputHash.c_str());
		sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
		sprintf(g_sharevalue[13], "%f", f_Hesh_Cade->m_bckred);
		sprintf(g_sharevalue[14], "%f", f_Hesh_Cade->m_bckgreen);
		sprintf(g_sharevalue[15], "%f", f_Hesh_Cade->m_bckblue);
		sprintf(g_sharevalue[16], "%f", 0.0f);

		//ECN::Hesh...Sending BlockHesh.

		char shlquery[1000];
		sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Hash->m_OutputHash.c_str());

		g_SafeL[0]->acSelectCommand(shlquery, 2, false);

		int f_ShareLCount = 0;

		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
			{
			f_ShareLCount = 0;
			}
		else
			{
			f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
			}

		//ECN::Stat::: f_ShareLCount

		if(f_ShareLCount == 0)
			{
			int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

			f_ShareID = f_ShareUniqueID;
			g_ShareID = f_ShareID;

			//ECN::Stat::: f_ShareID f_shareuniqueID

			ag_addGenesisTracking(f_ShareUniqueID);
				
			char* f_idquery2 = new char[150];
			sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

			g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
			delete[] f_idquery2;

			int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
			int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

			g_PEERCNT = f_PEERCNT;
			g_SHARECNT = f_SHARECNT;

			for(int f_Int = 0; f_Int < f_Hesh_Cade->m_adIndex.size(); f_Int++)
				{
				std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[f_Hesh_Cade->m_adIndex[f_Int]];

				char* g_cubevalue[60];

				for(int f_Count = 0; f_Count < 60; f_Count++)
					{
					g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
					}

				for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
					{
					sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
					sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
					sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
					}

				for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
					{
					sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
					sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
					sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
					}
				
				sprintf(g_cubevalue[48], "%i", f_BlockID);
				sprintf(g_cubevalue[49], "%i", f_ShareID);
				sprintf(g_cubevalue[50], "%i", f_JobID);
				sprintf(g_cubevalue[51], "%i", f_Int);
				sprintf(g_cubevalue[52], "%i", f_TargetID);
				sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
				sprintf(g_cubevalue[54], "%f", f_Difficulty);

				g_CubeFieldCount = 55;

				int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
				}

			//ECN::Share Submitted.

			std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
			f_Ack->m_ECN = 0.0f;
			f_Ack->m_Reward = 50.0f;
			f_Ack->m_Origin = 1;
			f_Ack->m_Owner = g_Wallet->GetAdr();
			g_Ackent.push_back(f_Ack);
			}
		else
			{
			//Duplicate Block Found.
			f_Result = false;
			}

		m_DB_AccessLock.unlock();
		}
	else
		{
		float f_Mark = ag_Get_current_Target_Mark(g_Type);

		if((f_Mark < g_LowtonMark) && (g_KeepShare == false))
			{
			g_LowtonMark = f_Mark;
			g_Lowton = f_Hesh_Cade;
			g_LowtonHash = f_Hash;

			switch(g_Type)
				{
				case 0:
				case 1:
					{
					g_LowtonTarget_1 = gf_Target_1;
					}break;
				case 2:
					{
					g_LowtonTarget_2 = gf_Target_2;
					}break;
				case 3:
					{
					g_LowtonTarget_3 = gf_Target_3;
					}break;
				case 4:
					{
					g_LowtonTarget_4 = gf_Target_4;
					}break;
				case 5:
					{
					g_LowtonTarget_5 = gf_Target_5;
					}break;
				case 6:
					{
					g_LowtonTarget_6 = gf_Target_6;
					}break;
				case 7:
					{
					g_LowtonTarget_7 = gf_Target_7;
					}break;
				case 8:
					{
					g_LowtonTarget_8 = gf_Target_8;
					}break;
				case 9:
					{
					g_LowtonTarget_9 = gf_Target_9;
					}break;
				case 10:
					{
					g_LowtonTarget_10 = gf_Target_10;
					}break;
				}

			g_TargetedHesh->ac_IsOK();

			g_TargetedHesh = g_Lowton;

			g_RenderHesh = true;

			//New LowTon Holding... g_LowtonMark
			}

		time(&g_currenttime);

		if(g_currenttime > g_storagetime)
			{
			time(&g_storagetime);
			g_storagetime += ECOIN_TARGET_LOWTON_STORAGE;

			char* g_sharevalue[60];

			for(int f_Count = 0; f_Count < 60; f_Count++)
				{
				g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
				}

			sprintf(g_sharevalue[0], "%f", g_LowtonMark);
			sprintf(g_sharevalue[1], "%i", 1);
			sprintf(g_sharevalue[2], "%s", "3");
			sprintf(g_sharevalue[4], "%i", 15);
			sprintf(g_sharevalue[5], "%i", 15);
			sprintf(g_sharevalue[6], "%s", g_TypeName.c_str());
			sprintf(g_sharevalue[7], "%f", f_Difficulty);

			   ////////////
			  //
			 // Hash
			//
			std::string f_InputHash = g_LowtonHash->acGetInput();

			// check GenesisBlock (assume)
			std::string f_previousblock = "00000000000000000000000000000001";
			//ECN::Hesh...Checking Previous BlockHesh.

			char blokquery[1000];
			sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block ORDER BY dated DESC LIMIT 1");

			m_DB_AccessLock.lock();

			g_SafeL[0]->acSelectCommand(blokquery, 2, false);

			int f_blokLCount = 0;
			
			if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
				{
				f_blokLCount = 0;
				}
			else
				{
				f_blokLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
				}

			//ECN::Stat::: f_TrxLCount

			g_JobID = 0;

			if(f_blokLCount > 0)
				{
				g_JobID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
				g_JobID++;
				f_previousblock = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
				}

			f_JobID = g_JobID;

			sprintf(g_sharevalue[3], "%i", f_JobID);

			//ECN::Stat::: g_JobID

			std::string f_tx = ag_GatherTransactions(g_JobID);

			std::string f_job = f_tx + f_previousblock;

			f_InputHash += f_job;

#if 1
			g_hasha.init(); //reset hasher state
			g_hasha.process(f_InputHash.begin(), f_InputHash.end());
			g_hasha.finish();
			picosha2::get_hash_hex_string(g_hasha, g_LowtonHash->m_OutputHash);
#else
			g_LowtonHash->m_OutputHash = "00000000000000000000000000000000";
#endif

			g_Lowton->m_Hash = g_LowtonHash;

			g_LowtonMark = FLT_MAX;

			//ShareHash-g_LowtonHash->m_OutputHash

			sprintf(g_sharevalue[8], "%i", 0);
			sprintf(g_sharevalue[9], "%i", 10);
			sprintf(g_sharevalue[10], "%s", g_LowtonHash->m_OutputHash.c_str());
			sprintf(g_sharevalue[11], "%s", g_LowtonHash->m_OutputHash.c_str());
			sprintf(g_sharevalue[12], "%s", g_Wallet->GetAdr().c_str());
			sprintf(g_sharevalue[13], "%f", g_Lowton->m_bckred);
			sprintf(g_sharevalue[14], "%f", g_Lowton->m_bckgreen);
			sprintf(g_sharevalue[15], "%f", g_Lowton->m_bckblue);
			sprintf(g_sharevalue[16], "%f", 0.0f);

			//ECN::Hesh...Sending BlockHesh.

			char shlquery[1000];
			sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", g_LowtonHash->m_OutputHash.c_str());

			g_SafeL[0]->acSelectCommand(shlquery, 2, false);

			int f_ShareLCount = 0;
		
			if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
				{
				f_ShareLCount = 0;
				}
			else
				{
				f_ShareLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
				}

			//ECN::Stat::: f_ShareLCount

			if(f_ShareLCount == 0)
				{
				int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 17, 2, false);

				f_ShareID = f_ShareUniqueID;
				g_ShareID = f_ShareID;

				//ECN::Stat::: f_ShareID f_shareuniqueID

				ag_addGenesisTracking(f_ShareUniqueID);
				
				char* f_idquery2 = new char[150];
				sprintf(f_idquery2, "SELECT id, owner FROM share WHERE jobid = %i", g_JobID);

				g_SafeL[0]->acSelectCommand_PeerGraph(f_idquery2, 2, false);
				delete[] f_idquery2;

				int f_PEERCNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 2][0].c_str());
				int f_SHARECNT = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size() - 1][0].c_str());

				g_PEERCNT = f_PEERCNT;
				g_SHARECNT = f_SHARECNT;

				for(int f_Int = 0; f_Int < g_Lowton->m_adIndex.size(); f_Int++)
					{
					shared_ptr<CubeBicycle> f_Bike = g_Lowton->vec_Bicycle[g_Lowton->m_adIndex[f_Int]];
					char* g_cubevalue[60];

					for(int f_Count = 0; f_Count < 60; f_Count++)
						{
						g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
						}

					for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
						{
						sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
						sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
						sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
						}

					for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
						{
						sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", f_Bike->vec_Color[f_Int3]->m_X);
						sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int3]->m_Y);
						sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int3]->m_Z);
						}
				
					sprintf(g_cubevalue[48], "%i", f_BlockID);
					sprintf(g_cubevalue[49], "%i", f_ShareID);
					sprintf(g_cubevalue[50], "%i", f_JobID);
					sprintf(g_cubevalue[51], "%i", f_Int);
					sprintf(g_cubevalue[52], "%i", 1);	//FIXME ADD L-TARGETID
					sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
					sprintf(g_cubevalue[54], "%f", f_Difficulty);

					g_CubeFieldCount = 55;

					int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, g_CubeFieldCount, 2, false);
					}

				//ECN::Lowton Share Submitted.

				std::shared_ptr<Ackent> f_Ack = std::make_shared<Ackent>(ACK_TYPE_SHARE, g_ShareID, f_PEERCNT);
				f_Ack->m_ECN = 0.0f;
				f_Ack->m_Reward = 50.0f;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = g_Wallet->GetAdr();
				g_Ackent.push_back(f_Ack);
				}
			else
				{
				//Duplicate Block Found.
				f_Result = false;
				}

			m_DB_AccessLock.unlock();
			}
		}
}

#endif

void Sample3DSceneRenderer::RestoreTargetedBuffers(void)
{
	if(g_TargetedHesh)
		{
		g_TargetedHesh->ac_IsOK();

		for(int f_Int = 0; f_Int < g_TargetedHesh->vec_Bicycle.size(); f_Int++)
			{
			shared_ptr<CubeBicycle> f_Bicycle = g_TargetedHesh->vec_Bicycle[f_Int];

			if((f_Int < g_ADMAX) && (f_Int < g_TargetedHesh->m_ADMAX))
				{
				f_Bicycle->m_vertexBuffer = Cube::g_BicycleContainer[0].vec_Key[f_Int]->m_Link->m_vertexBuffer;
				f_Bicycle->m_indexBuffer = Cube::g_BicycleContainer[0].vec_Key[f_Int]->m_Link->m_indexBuffer;
				
				D3D11_MAPPED_SUBRESOURCE mappedResource;
				VertexBufferType* dataPtr;

				// Lock the constant buffer so it can be written to.
				HRESULT result = m_deviceResources->GetD3DDeviceContext()->Map(f_Bicycle->m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
				if (FAILED(result))
					{
					throw std::exception("GetD3DDeviceContext()->Map buffer map failed");
					}

				// Get a pointer to the data in the constant buffer.
				dataPtr = (VertexBufferType*)mappedResource.pData;

				int f_VertexCount = 0;
				for (int f_Count = 0; f_Count < 16; f_Count+=2)
					{
					if(f_VertexCount < f_Bicycle->vec_Vertex.size())
						{
						dataPtr->vertex[f_Count].x = f_Bicycle->vec_Vertex[f_VertexCount]->m_X;
						dataPtr->vertex[f_Count].y = f_Bicycle->vec_Vertex[f_VertexCount]->m_Y;
						dataPtr->vertex[f_Count].z = f_Bicycle->vec_Vertex[f_VertexCount]->m_Z;

						f_VertexCount++;
						}

					if(f_VertexCount < f_Bicycle->vec_Color.size())
						{
						dataPtr->vertex[f_Count + 1].x = f_Bicycle->vec_Color[f_VertexCount]->m_X;
						dataPtr->vertex[f_Count + 1].y = f_Bicycle->vec_Color[f_VertexCount]->m_Y;
						dataPtr->vertex[f_Count + 1].z = f_Bicycle->vec_Color[f_VertexCount]->m_Z;
						}
					}

				// Unlock the constant buffer.
				m_deviceResources->GetD3DDeviceContext()->Unmap(f_Bicycle->m_vertexBuffer.Get(), 0);
				}
			}
		}
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	
	m_vertexShader.Reset();
	m_QCGvertexShader.Reset();
	m_COMvertexShader.Reset();
	m_curvevertexShader.Reset();
	m_pixelShader.Reset();
	m_QCGpixelShader.Reset();
	m_COMpixelShader.Reset();
	m_curvepixelShader.Reset();
	m_inputLayout.Reset();
	m_QCGinputLayout.Reset();
	m_COMinputLayout.Reset();
	m_curveinputLayout.Reset();
	m_vertexBuffer.Reset();
	m_COMvertexBuffer.Reset();
	m_indexBuffer.Reset();
	m_COMindexBuffer.Reset();
	m_constantBuffer.Reset();
	m_QCGconstantBuffer.Reset();
	m_COMconstantBuffer.Reset();
	m_curveconstantBuffer.Reset();
}