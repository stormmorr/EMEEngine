/*

Sample3DSceneRenderer - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

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

#if 1
template<class f_G>
void ag_FreshOn(std::vector<f_G>& f_AS, int f_IDX, f_G f_Resultance)
{
	if(f_IDX < f_AS.size())
		{
		f_AS[f_IDX] = f_Resultance;
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}
		}
}

template<class f_E>
void ag_Freshanon(std::vector<f_E>& f_AS, int f_IDX, f_E f_Resultance)
{
	while(f_IDX >= f_AS.size())
		{
		f_AS.push_back(f_Resultance);
		}
}

template<typename f_G>
f_G ag_FreshAndOnly(std::vector<f_G>& f_AS, int f_IDX, f_G f_Resultance)
{
	f_G h_Sorda = 0;

	std::string f_StrTypeName = typeid(f_G).name();

	if(f_IDX < f_AS.size())
		{
		if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
			{
			return f_AS.at(f_IDX);
			}
		else
			{
			f_G f_Hossa = f_AS.at(f_IDX);

			if(f_Hossa != 0)
				{
				h_Sorda = f_Hossa;

				return h_Sorda;
				}
			else
				{
				h_Sorda = f_Resultance;

				return h_Sorda;
				}
			}
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}

		h_Sorda = f_Resultance;

		if(f_IDX < f_AS.size())
			{
			if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
				{
				return f_AS.at(f_IDX);
				}
			else
				{
				f_G f_Hossa = f_AS.at(f_IDX);

				if(f_Hossa != 0)
					{
					h_Sorda = f_Hossa;

					return h_Sorda;
					}
				else
					{
					h_Sorda = f_Resultance;

					return h_Sorda;
					}
				}
			}
		else
			{
			while(f_IDX >= f_AS.size())
				{
				f_AS.push_back(f_Resultance);
				}
			}

		h_Sorda = f_Resultance;

		if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
			{
			return f_AS.at(f_IDX);
			}
		else
			{
			f_G f_Hossa = f_AS.at(f_IDX);

			if(f_Hossa != 0)
				{
				h_Sorda = f_Hossa;

				return h_Sorda;
				}
			else
				{
				h_Sorda = f_Resultance;

				return h_Sorda;
				}
			}
		}

	return h_Sorda;
}
#endif

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

	// Eye is at (0,0.7,1.5), looking '1' at point (0,-0.1,0) with the '0' up-vector along the y-axis.
	XMVECTORF32 eye = { 0.0f, -1.4f * 10.25f/*SCP_FLT_SCALE*/, 5.555f * 0.84f/*SCP_FLT_SCALE*/, 0.0f };
	XMVECTORF32 at = { 0.0f, -0.75f, 0.0f, 0.0f };
	XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	eye.v.m128_f32[0] += g_QcomManager->m_current_X;
	eye.v.m128_f32[1] += g_QcomManager->m_current_Y;

	at.v.m128_f32[0] += g_QcomManager->m_current_X;
	at.v.m128_f32[1] += g_QcomManager->m_current_Y;

	XMStoreFloat4x4(&m_QCGconstantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

	XMMATRIX f_MatrixVW = XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up));

	Cube::g_view = f_MatrixVW;

#if 0
#ifdef ARM_ARCH
	Cube::g_eye = Cube::BiVector(eye.v.n128_f32[0], eye.v.n128_f32[1], eye.v.n128_f32[2], eye.v.n128_f32[3]);
	Cube::g_at = Cube::BiVector(at.v.n128_f32[0], at.v.n128_f32[1], at.v.n128_f32[2], at.v.n128_f32[3]);
#else
	Cube::g_eye = Cube::BiVector(eye.v.m128_f32[0], eye.v.m128_f32[1], eye.v.m128_f32[2], eye.v.m128_f32[3]);
	Cube::g_at = Cube::BiVector(at.v.m128_f32[0], at.v.m128_f32[1], at.v.m128_f32[2], at.v.m128_f32[3]);
#endif
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

	if(g_TargetedHesh)
		{
		if(g_TargetedHesh->m_CountLM > 0)
			{
			XMVECTORF32 eye = { 0.0f, -1.4f * 10.25f/*SCP_FLT_SCALE*/, 5.555f * 0.84f/*SCP_FLT_SCALE*/, 0.0f };
			XMVECTORF32 at = { 0.0f, -0.75f, 0.0f, 0.0f };
			XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

			XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
			}
		else
			{
			XMVECTORF32 eye = { 0.0f, -1.4f * 1.25f/*SCP_FLT_SCALE*/, 5.555f * 0.84f/*SCP_FLT_SCALE*/, 0.0f };
			XMVECTORF32 at = { 0.0f, -0.75f, 0.0f, 0.0f };
			XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

			XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
			}
		}
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

		f_Wire->m_Time += 0.01f;// f_Time
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
	std::string f_ref_CurrentPath = "Sample3DSceneRenderer::CreateDeviceDependentResources";

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
	ag_StatusLive(f_ref_CurrentPath, "f_Wire");
	std::shared_ptr<QcomWire> f_Wire = std::make_shared_reflect<QcomWire>();

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
		{XMFLOAT3((0.5f * f_XScale3) + f_X, (-0.5f * f_YScale3) + f_Y, -0.6f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
		{XMFLOAT3((0.5f * f_XScale3) + f_X, (-0.5f * f_YScale3) + f_Y,  0.6f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3((0.5f * f_XScale3) + f_X,  (0.5f * f_YScale3) + f_Y, -0.6f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{XMFLOAT3((0.5f * f_XScale3) + f_X,  (0.5f * f_YScale3) + f_Y,  0.6f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
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
	ag_StatusLive(f_ref_CurrentPath, "f_Wire2");
	std::shared_ptr<QcomWire> f_Wire2 = std::make_shared_reflect<QcomWire>();

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
	for(int f_XY = 0; f_XY < Cube::g_BicycleContainer[0]->m_ADMAX; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_KEY");
		std::shared_ptr<Cube::CubeKEY> f_KEY = std::make_shared_reflect<Cube::CubeKEY>();

#ifdef OSI_MEMORY_BIVECTOR_REF
		ag_StatusLive(f_ref_CurrentPath, "f_Bicycle");
		std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared_reflect<Cube::CubeBicycle>();
#else
		std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared<Cube::CubeBicycle>();
#endif

		f_KEY->m_Link = f_Bicycle;

		m_DB_AccessLock.lock();

		// Load mesh vertices. Each vertex has a position and a color.
		Cube::BiRand f_BiRand;
		ag_StatusLive(f_ref_CurrentPath, "f_Vector1");
		std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
		f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		ag_StatusLive(f_ref_CurrentPath, "f_Vector2");
		std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
		f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		ag_StatusLive(f_ref_CurrentPath, "f_Vector3");
		std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
		f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		ag_StatusLive(f_ref_CurrentPath, "f_Vector4");
		std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
		f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		ag_StatusLive(f_ref_CurrentPath, "f_Vector5");
		std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
		f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		ag_StatusLive(f_ref_CurrentPath, "f_Vector6");
		std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
		f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		ag_StatusLive(f_ref_CurrentPath, "f_Vector7");
		std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
		f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
		f_BiRand.acGet();
		ag_StatusLive(f_ref_CurrentPath, "f_Vector8");
		std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, 0.5f);
		f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

		ag_StatusLive(f_ref_CurrentPath, "f_Color1");
		std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		ag_StatusLive(f_ref_CurrentPath, "f_Color2");
		std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		ag_StatusLive(f_ref_CurrentPath, "f_Color3");
		std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		ag_StatusLive(f_ref_CurrentPath, "f_Color4");
		std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		ag_StatusLive(f_ref_CurrentPath, "f_Color5");
		std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		ag_StatusLive(f_ref_CurrentPath, "f_Color6");
		std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		ag_StatusLive(f_ref_CurrentPath, "f_Color7");
		std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
		ag_StatusLive(f_ref_CurrentPath, "f_Color8");
		std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

		m_DB_AccessLock.unlock();

		Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

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

		m_DB_AccessLock.lock();

		Cube::g_BicycleContainer[0]->vec_Key.push_back(f_KEY);

		m_DB_AccessLock.unlock();
		}

	m_loadingComplete = true;
}

void Sample3DSceneRenderer::acCreateAdmaxDependentResources(void)
{
	std::string f_ref_CurrentPath = "Sample3DSceneRenderer::acCreateAdmaxDependentResources";

	if(Cube::g_BicycleContainer[0]->vec_Key.size() < Cube::g_BicycleContainer[0]->m_ADMAX)
		{
		while(Cube::g_BicycleContainer[0]->vec_Key.size() < Cube::g_BicycleContainer[0]->m_ADMAX)
			{
			m_DB_AccessLock.lock();

			// Once the cube is loaded, the object is ready to be rendered.
			ag_StatusLive(f_ref_CurrentPath, "f_KEY");
			std::shared_ptr<Cube::CubeKEY> f_KEY = std::make_shared_reflect<Cube::CubeKEY>();

#ifdef OSI_MEMORY_BIVECTOR_REF
			ag_StatusLive(f_ref_CurrentPath, "f_Bicycle");
			std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared_reflect<Cube::CubeBicycle>();
#else
			std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared<Cube::CubeBicycle>();
#endif

			f_KEY->m_Link = f_Bicycle;

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			ag_StatusLive(f_ref_CurrentPath, "f_Vector1");
			std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
			f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			ag_StatusLive(f_ref_CurrentPath, "f_Vector2");
			std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
			f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			ag_StatusLive(f_ref_CurrentPath, "f_Vector3");
			std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
			f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			ag_StatusLive(f_ref_CurrentPath, "f_Vector4");
			std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
			f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			ag_StatusLive(f_ref_CurrentPath, "f_Vector5");
			std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
			f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			ag_StatusLive(f_ref_CurrentPath, "f_Vector6");
			std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
			f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			ag_StatusLive(f_ref_CurrentPath, "f_Vector7");
			std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
			f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			ag_StatusLive(f_ref_CurrentPath, "f_Vector8");
			std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, 0.5f);
			f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			ag_StatusLive(f_ref_CurrentPath, "f_Color1");
			std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			ag_StatusLive(f_ref_CurrentPath, "f_Color2");
			std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			ag_StatusLive(f_ref_CurrentPath, "f_Color3");
			std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			ag_StatusLive(f_ref_CurrentPath, "f_Color4");
			std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			ag_StatusLive(f_ref_CurrentPath, "f_Color5");
			std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			ag_StatusLive(f_ref_CurrentPath, "f_Color6");
			std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			ag_StatusLive(f_ref_CurrentPath, "f_Color7");
			std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
			ag_StatusLive(f_ref_CurrentPath, "f_Color8");
			std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

			m_DB_AccessLock.unlock();

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

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

			m_DB_AccessLock.lock();

			Cube::g_BicycleContainer[0]->vec_Key.push_back(f_KEY);

			m_DB_AccessLock.unlock();
			}
		}
	else if(Cube::g_BicycleContainer[0]->vec_Key.size() > Cube::g_BicycleContainer[0]->m_ADMAX)
		{
		int f_CountIndex = Cube::g_BicycleContainer[0]->vec_Key.size() - 1;

		while(Cube::g_BicycleContainer[0]->vec_Key.size() > Cube::g_BicycleContainer[0]->m_ADMAX)
			{
			m_DB_AccessLock.lock();

			std::shared_ptr<Cube::CubeKEY> f_Key = Cube::g_BicycleContainer[0]->vec_Key[f_CountIndex];

			f_Key->m_Link->m_vertexBuffer.Reset();
			f_Key->m_Link->m_indexBuffer.Reset();
			f_Key->m_Link->vec_Vertex.clear();
			f_Key->m_Link->vec_Color.clear();

			Cube::g_BicycleContainer[0]->vec_Key.pop_back();

			f_CountIndex--;

			m_DB_AccessLock.unlock();
			}
		}
}

struct VertexBufferType
{
	XMFLOAT3 vertex[16];
};

void Sample3DSceneRenderer::acSaveCompletePublish_GenHesh_Upper_Reflection(void)
{
	std::string f_ref_CurrentPath = "Sample3DSceneRenderer::acSaveCompletePublish_GenHesh_Upper_Reflection";
	bool f_OCP_LOCK_ON = false;

	m_DB_AccessLock.lock();
	f_OCP_LOCK_ON = true;

	int f_OCSCP_ThreadIndex = g_OCSCP_ThreadCount;

	g_OCSCP_ThreadCount++;

	char* f_Char = ag_ClearChar(64);
	sprintf(f_Char, "%i#", f_OCSCP_ThreadIndex);
	std::string f_hrIDA = f_Char;

	f_ref_CurrentPath += f_hrIDA;

	delete f_Char;

	int f_SCP_ShareID = g_ShareID;

	g_ElementDivisor.push_back(0);
	g_ElementDivisorInt.push_back(0);

	g_classLMap->m_SchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_SaveSchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_PushSchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
	g_classLMap->m_SchemaMeasureIndex.push_back(0);
	g_classLMap->m_PushMeasureIndex.push_back(0);
	g_classLMap->m_CPS_Result.push_back(CPS_LOAD);

	ag_StatusLive(f_ref_CurrentPath, "g_LowtonHash");
	g_LowtonHash = std::make_shared_reflect<Cube::CubeHASH_originstring>();

	ag_StatusLive(f_ref_CurrentPath, "f_Hesh_Cade", true);
	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared_reflect<Cube::CubeHESH>(g_classLMap->m_ADMAX, g_classLMap->m_ADHIGH, g_classLMap->m_ADLOW, g_CountLM);

	ag_StatusLive(f_ref_CurrentPath, "f_Hesh_Cade->m_Hash");
	f_Hesh_Cade->m_Hash = std::make_shared_reflect<Cube::CubeHASH_originstring>();

	ag_StatusLive(f_ref_CurrentPath, "f_Collection", true);
	std::shared_ptr<classCollection> f_Collection = std::make_shared_reflect<classCollection>();

	m_DB_AccessLock.unlock();
	f_OCP_LOCK_ON = false;

	int f_OC_Lowton_Mark_Count = 0;

	int f_Bike_Low = g_Lowton->vec_Bicycle.size();

	//'fast forward' pre-run
	while(f_Bike_Low > f_Hesh_Cade->vec_Bicycle.size())
		{
		m_DB_AccessLock.lock();
		f_OCP_LOCK_ON = true;

		//make bike clone
		std::shared_ptr<CubeBicycle> f_WonBike = g_Lowton->vec_Bicycle[f_OC_Lowton_Mark_Count];

		// Load mesh vertices. Each vertex has a position and a color.
		std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[0]->m_X, f_WonBike->vec_Vertex[0]->m_Y, f_WonBike->vec_Vertex[0]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[1]->m_X, f_WonBike->vec_Vertex[1]->m_Y, f_WonBike->vec_Vertex[1]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[2]->m_X, f_WonBike->vec_Vertex[2]->m_Y, f_WonBike->vec_Vertex[2]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[3]->m_X, f_WonBike->vec_Vertex[3]->m_Y, f_WonBike->vec_Vertex[3]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[4]->m_X, f_WonBike->vec_Vertex[4]->m_Y, f_WonBike->vec_Vertex[4]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[5]->m_X, f_WonBike->vec_Vertex[5]->m_Y, f_WonBike->vec_Vertex[5]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[6]->m_X, f_WonBike->vec_Vertex[6]->m_Y, f_WonBike->vec_Vertex[6]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[7]->m_X, f_WonBike->vec_Vertex[7]->m_Y, f_WonBike->vec_Vertex[7]->m_Z);

		std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[0]->m_X, f_WonBike->vec_Color[0]->m_Y, f_WonBike->vec_Color[0]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[1]->m_X, f_WonBike->vec_Color[1]->m_Y, f_WonBike->vec_Color[1]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[2]->m_X, f_WonBike->vec_Color[2]->m_Y, f_WonBike->vec_Color[2]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[3]->m_X, f_WonBike->vec_Color[3]->m_Y, f_WonBike->vec_Color[3]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[4]->m_X, f_WonBike->vec_Color[4]->m_Y, f_WonBike->vec_Color[4]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[5]->m_X, f_WonBike->vec_Color[5]->m_Y, f_WonBike->vec_Color[5]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[6]->m_X, f_WonBike->vec_Color[6]->m_Y, f_WonBike->vec_Color[6]->m_Z);
		std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[7]->m_X, f_WonBike->vec_Color[7]->m_Y, f_WonBike->vec_Color[7]->m_Z);

		ag_StatusLive(f_ref_CurrentPath, "f_Bike_Joining");
		std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_reflect<Cube::CubeBicycle>();

		m_DB_AccessLock.unlock();
		f_OCP_LOCK_ON = false;

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

		f_Hesh_Cade->m_adIndex.push_back(g_Lowton->m_adIndex[f_OC_Lowton_Mark_Count]);

		m_DB_AccessLock.lock();
		f_OCP_LOCK_ON = true;

		ag_StatusLive(f_ref_CurrentPath, "f_Element_Joining");
		std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Bike);

		m_DB_AccessLock.unlock();
		f_OCP_LOCK_ON = false;

		f_Collection->m_vec_Element.push_back(f_Element);
		f_Collection->m_idx_vec_Element++;

		f_OC_Lowton_Mark_Count++;
		}

	m_DB_AccessLock.lock();
	f_OCP_LOCK_ON = true;

	//Prep Pre Tests
	if(g_classLMap->m_Patched == false)
		{
		g_classLMap->m_Patched = true;

		bool f_PatchOK = g_classLMap->acPatch_IntegerRanges(f_Collection, f_OCSCP_ThreadIndex);

#ifdef ECOIN_DEBUG_BREAKS
		if(f_PatchOK == false)
			{
			__debugbreak();
			}
#endif //add debug message
		}

	m_DB_AccessLock.unlock();
	f_OCP_LOCK_ON = false;

	ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);
	ag_Freshanon<int>(g_Wallet->m_vec_ElementCount, m_IDX, 0);

	//print lowton result
	if(f_OC_Lowton_Mark_Count > 0)
		{
		bool f_PreResl = g_classLMap->acPreCompute(f_Collection, f_OCSCP_ThreadIndex, f_OC_Lowton_Mark_Count);

#ifdef ECOIN_DEBUG_BREAKS
		if(f_PreResl == false)
			{
			g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_SHUTDOWN_COMPRESS;

			__debugbreak();
			}
#endif //add debug message
		}

	 //////////////////////////////////////////
	// adjustable element-at-once
	int f_ElementOnce = SCP_ELM_ONCE;
	int f_LoadInterruptor = 0;

	while(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS)
		{
		f_ElementOnce = SCP_ELM_ONCE;

		int f_SizeMin = 0;

		if(f_Collection->m_vec_Element.size() > 0)
			{
			f_SizeMin = f_Collection->m_vec_Element.size();

			for(int f_XYZ = f_SizeMin - 1; f_XYZ >= 0; f_XYZ--)
				{
				if(f_Collection->m_vec_Element[f_XYZ]->m_OCSCP_Flag == true)
					{
					f_XYZ = -1;
					}
				else
					{
					f_SizeMin--;

					if(f_SizeMin < 0)
						{
						f_SizeMin = 0;

						f_XYZ = -1;
						}
					}
				}
			}

		//######--
		int f_SoLowtonBicycleSize = g_Lowton->vec_Bicycle.size();

		if(g_classLMap->m_CPS_Result.size() >= g_SaveComplete_ThreadCount)
			{
			if((g_LowtonOn == true) && ((g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] == CPS_SCAN) && (g_Result == false)))
				{
				while(f_SizeMin < f_SoLowtonBicycleSize)
					{
					if(f_SizeMin >= f_Hesh_Cade->vec_Bicycle.size())
						{
						m_DB_AccessLock.lock();
						f_OCP_LOCK_ON = true;

						//make bike clone
						std::shared_ptr<CubeBicycle> f_WonBike = g_Lowton->vec_Bicycle[f_SizeMin];

						// Load mesh vertices. Each vertex has a position and a color.
						std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[0]->m_X, f_WonBike->vec_Vertex[0]->m_Y, f_WonBike->vec_Vertex[0]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[1]->m_X, f_WonBike->vec_Vertex[1]->m_Y, f_WonBike->vec_Vertex[1]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[2]->m_X, f_WonBike->vec_Vertex[2]->m_Y, f_WonBike->vec_Vertex[2]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[3]->m_X, f_WonBike->vec_Vertex[3]->m_Y, f_WonBike->vec_Vertex[3]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[4]->m_X, f_WonBike->vec_Vertex[4]->m_Y, f_WonBike->vec_Vertex[4]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[5]->m_X, f_WonBike->vec_Vertex[5]->m_Y, f_WonBike->vec_Vertex[5]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[6]->m_X, f_WonBike->vec_Vertex[6]->m_Y, f_WonBike->vec_Vertex[6]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Vertex[7]->m_X, f_WonBike->vec_Vertex[7]->m_Y, f_WonBike->vec_Vertex[7]->m_Z);

						std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[0]->m_X, f_WonBike->vec_Color[0]->m_Y, f_WonBike->vec_Color[0]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[1]->m_X, f_WonBike->vec_Color[1]->m_Y, f_WonBike->vec_Color[1]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[2]->m_X, f_WonBike->vec_Color[2]->m_Y, f_WonBike->vec_Color[2]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[3]->m_X, f_WonBike->vec_Color[3]->m_Y, f_WonBike->vec_Color[3]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[4]->m_X, f_WonBike->vec_Color[4]->m_Y, f_WonBike->vec_Color[4]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[5]->m_X, f_WonBike->vec_Color[5]->m_Y, f_WonBike->vec_Color[5]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[6]->m_X, f_WonBike->vec_Color[6]->m_Y, f_WonBike->vec_Color[6]->m_Z);
						std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(f_WonBike->vec_Color[7]->m_X, f_WonBike->vec_Color[7]->m_Y, f_WonBike->vec_Color[7]->m_Z);

						ag_StatusLive(f_ref_CurrentPath, "f_Bike_LowtonUp");
						std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_reflect<Cube::CubeBicycle>();

						m_DB_AccessLock.unlock();
						f_OCP_LOCK_ON = false;

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

						f_Hesh_Cade->m_adIndex.push_back(g_Lowton->m_adIndex[f_SizeMin]);

						m_DB_AccessLock.lock();
						f_OCP_LOCK_ON = true;

						ag_StatusLive(f_ref_CurrentPath, "f_Element_LowtonUp");
						std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Bike);

						m_DB_AccessLock.unlock();
						f_OCP_LOCK_ON = false;

						f_Collection->m_vec_Element.push_back(f_Element);
						f_Collection->m_idx_vec_Element++;
						}
					else
						{
						//make bike clone
						std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[f_SizeMin];
						std::shared_ptr<CubeBicycle> f_WonBike = g_Lowton->vec_Bicycle[f_SizeMin];

						f_Bike->vec_Vertex[0]->m_X = f_WonBike->vec_Vertex[0]->m_X;
						f_Bike->vec_Vertex[0]->m_Y = f_WonBike->vec_Vertex[0]->m_Y;
						f_Bike->vec_Vertex[0]->m_Z = f_WonBike->vec_Vertex[0]->m_Z;

						f_Bike->vec_Vertex[1]->m_X = f_WonBike->vec_Vertex[1]->m_X;
						f_Bike->vec_Vertex[1]->m_Y = f_WonBike->vec_Vertex[1]->m_Y;
						f_Bike->vec_Vertex[1]->m_Z = f_WonBike->vec_Vertex[1]->m_Z;

						f_Bike->vec_Vertex[2]->m_X = f_WonBike->vec_Vertex[2]->m_X;
						f_Bike->vec_Vertex[2]->m_Y = f_WonBike->vec_Vertex[2]->m_Y;
						f_Bike->vec_Vertex[2]->m_Z = f_WonBike->vec_Vertex[2]->m_Z;

						f_Bike->vec_Vertex[3]->m_X = f_WonBike->vec_Vertex[3]->m_X;
						f_Bike->vec_Vertex[3]->m_Y = f_WonBike->vec_Vertex[3]->m_Y;
						f_Bike->vec_Vertex[3]->m_Z = f_WonBike->vec_Vertex[3]->m_Z;

						f_Bike->vec_Vertex[4]->m_X = f_WonBike->vec_Vertex[4]->m_X;
						f_Bike->vec_Vertex[4]->m_Y = f_WonBike->vec_Vertex[4]->m_Y;
						f_Bike->vec_Vertex[4]->m_Z = f_WonBike->vec_Vertex[4]->m_Z;

						f_Bike->vec_Vertex[5]->m_X = f_WonBike->vec_Vertex[5]->m_X;
						f_Bike->vec_Vertex[5]->m_Y = f_WonBike->vec_Vertex[5]->m_Y;
						f_Bike->vec_Vertex[5]->m_Z = f_WonBike->vec_Vertex[5]->m_Z;

						f_Bike->vec_Vertex[6]->m_X = f_WonBike->vec_Vertex[6]->m_X;
						f_Bike->vec_Vertex[6]->m_Y = f_WonBike->vec_Vertex[6]->m_Y;
						f_Bike->vec_Vertex[6]->m_Z = f_WonBike->vec_Vertex[6]->m_Z;

						f_Bike->vec_Vertex[7]->m_X = f_WonBike->vec_Vertex[7]->m_X;
						f_Bike->vec_Vertex[7]->m_Y = f_WonBike->vec_Vertex[7]->m_Y;
						f_Bike->vec_Vertex[7]->m_Z = f_WonBike->vec_Vertex[7]->m_Z;

						f_Bike->vec_Color[0]->m_X = f_WonBike->vec_Color[0]->m_X;
						f_Bike->vec_Color[0]->m_Y = f_WonBike->vec_Color[0]->m_Y;
						f_Bike->vec_Color[0]->m_Z = f_WonBike->vec_Color[0]->m_Z;

						f_Bike->vec_Color[1]->m_X = f_WonBike->vec_Color[1]->m_X;
						f_Bike->vec_Color[1]->m_Y = f_WonBike->vec_Color[1]->m_Y;
						f_Bike->vec_Color[1]->m_Z = f_WonBike->vec_Color[1]->m_Z;

						f_Bike->vec_Color[2]->m_X = f_WonBike->vec_Color[2]->m_X;
						f_Bike->vec_Color[2]->m_Y = f_WonBike->vec_Color[2]->m_Y;
						f_Bike->vec_Color[2]->m_Z = f_WonBike->vec_Color[2]->m_Z;

						f_Bike->vec_Color[3]->m_X = f_WonBike->vec_Color[3]->m_X;
						f_Bike->vec_Color[3]->m_Y = f_WonBike->vec_Color[3]->m_Y;
						f_Bike->vec_Color[3]->m_Z = f_WonBike->vec_Color[3]->m_Z;

						f_Bike->vec_Color[4]->m_X = f_WonBike->vec_Color[4]->m_X;
						f_Bike->vec_Color[4]->m_Y = f_WonBike->vec_Color[4]->m_Y;
						f_Bike->vec_Color[4]->m_Z = f_WonBike->vec_Color[4]->m_Z;

						f_Bike->vec_Color[5]->m_X = f_WonBike->vec_Color[5]->m_X;
						f_Bike->vec_Color[5]->m_Y = f_WonBike->vec_Color[5]->m_Y;
						f_Bike->vec_Color[5]->m_Z = f_WonBike->vec_Color[5]->m_Z;

						f_Bike->vec_Color[6]->m_X = f_WonBike->vec_Color[6]->m_X;
						f_Bike->vec_Color[6]->m_Y = f_WonBike->vec_Color[6]->m_Y;
						f_Bike->vec_Color[6]->m_Z = f_WonBike->vec_Color[6]->m_Z;
					
						f_Bike->vec_Color[7]->m_X = f_WonBike->vec_Color[7]->m_X;
						f_Bike->vec_Color[7]->m_Y = f_WonBike->vec_Color[7]->m_Y;
						f_Bike->vec_Color[7]->m_Z = f_WonBike->vec_Color[7]->m_Z;

						f_Collection->m_vec_Element[f_SizeMin]->acSync_fromBicycle(f_WonBike);
						f_Collection->m_vec_Element[f_SizeMin]->m_OCSCP_Flag = true;
						}

					f_SizeMin++;
					}
				}
			}

		 ////////////////////
		// possibleTarget //
		int f_PossibleTarget = f_SizeMin;

		if(f_PossibleTarget < g_classLMap->m_ADMAX)
			{
			f_PossibleTarget += f_ElementOnce;

			if(f_PossibleTarget >= g_classLMap->m_ADMAX)
				{
				int f_PossibleDiff = g_classLMap->m_ADMAX - f_PossibleTarget;

				if(f_PossibleDiff < 0)
					{
					f_ElementOnce += f_PossibleDiff;
					}

				if(f_ElementOnce > 0)
					{
					f_PossibleTarget = f_SizeMin + f_ElementOnce;
					}
				else
					{
					f_ElementOnce = 1;

					f_PossibleTarget = g_classLMap->m_ADMAX - 1;
					}
				}
			}
		else
			{
			f_PossibleTarget = g_classLMap->m_ADMAX - 1;

			//'Shutdown Mode'
			f_ElementOnce = 0;
			}

		if(f_ElementOnce > 0)
			{
			for(int f_Int = f_SizeMin; f_Int < f_PossibleTarget; f_Int++)
				{
				if(f_Int >= f_Hesh_Cade->vec_Bicycle.size())
					{
					m_DB_AccessLock.lock();
					f_OCP_LOCK_ON = true;

					ag_StatusLive(f_ref_CurrentPath, "f_Bike_ElementOnce");
					std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_reflect<Cube::CubeBicycle>();

					// Load mesh vertices. Each vertex has a position and a color.
					Cube::BiRand f_BiRand;
					std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f + SCP_ADD_ON);
					f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON);
					f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON);
					f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON);
					f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON);
					f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON);
					f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f + SCP_ADD_ON, 0.5f + SCP_ADD_ON, -0.5f + SCP_ADD_ON);
					f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f + SCP_ADD_ON);
					f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

					std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

					m_DB_AccessLock.unlock();
					f_OCP_LOCK_ON = false;

					f_Vector1->acResolve_precision(SCP_FLT_SCALE);
					f_Vector2->acResolve_precision(SCP_FLT_SCALE);
					f_Vector3->acResolve_precision(SCP_FLT_SCALE);
					f_Vector4->acResolve_precision(SCP_FLT_SCALE);
					f_Vector5->acResolve_precision(SCP_FLT_SCALE);
					f_Vector6->acResolve_precision(SCP_FLT_SCALE);
					f_Vector7->acResolve_precision(SCP_FLT_SCALE);
					f_Vector8->acResolve_precision(SCP_FLT_SCALE);

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

					f_Hesh_Cade->m_adIndex.push_back(f_Int);

					m_DB_AccessLock.lock();
					f_OCP_LOCK_ON = true;

					ag_StatusLive(f_ref_CurrentPath, "f_Element_ElementOnce");
					std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Bike);

					m_DB_AccessLock.unlock();
					f_OCP_LOCK_ON = false;

					f_Collection->m_vec_Element.push_back(f_Element);
					f_Collection->m_idx_vec_Element++;
					}
				else
					{
					std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[f_Int];
					
					f_Bike->vec_Vertex[0]->m_X = ag_RVC();
					f_Bike->vec_Vertex[0]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[0]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[1]->m_X = ag_RVC();
					f_Bike->vec_Vertex[1]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[1]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[2]->m_X = ag_RVC();
					f_Bike->vec_Vertex[2]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[2]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[3]->m_X = ag_RVC();
					f_Bike->vec_Vertex[3]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[3]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[4]->m_X = ag_RVC();
					f_Bike->vec_Vertex[4]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[4]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[5]->m_X = ag_RVC();
					f_Bike->vec_Vertex[5]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[5]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[6]->m_X = ag_RVC();
					f_Bike->vec_Vertex[6]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[6]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[7]->m_X = ag_RVC();
					f_Bike->vec_Vertex[7]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[7]->m_Z = ag_RVC();

					f_Bike->vec_Color[0]->m_X = Cube::random();
					f_Bike->vec_Color[0]->m_Y = Cube::random();
					f_Bike->vec_Color[0]->m_Z = Cube::random();

					f_Bike->vec_Color[1]->m_X = Cube::random();
					f_Bike->vec_Color[1]->m_Y = Cube::random();
					f_Bike->vec_Color[1]->m_Z = Cube::random();

					f_Bike->vec_Color[2]->m_X = Cube::random();
					f_Bike->vec_Color[2]->m_Y = Cube::random();
					f_Bike->vec_Color[2]->m_Z = Cube::random();

					f_Bike->vec_Color[3]->m_X = Cube::random();
					f_Bike->vec_Color[3]->m_Y = Cube::random();
					f_Bike->vec_Color[3]->m_Z = Cube::random();

					f_Bike->vec_Color[4]->m_X = Cube::random();
					f_Bike->vec_Color[4]->m_Y = Cube::random();
					f_Bike->vec_Color[4]->m_Z = Cube::random();

					f_Bike->vec_Color[5]->m_X = Cube::random();
					f_Bike->vec_Color[5]->m_Y = Cube::random();
					f_Bike->vec_Color[5]->m_Z = Cube::random();

					f_Bike->vec_Color[6]->m_X = Cube::random();
					f_Bike->vec_Color[6]->m_Y = Cube::random();
					f_Bike->vec_Color[6]->m_Z = Cube::random();

					f_Bike->vec_Color[7]->m_X = Cube::random();
					f_Bike->vec_Color[7]->m_Y = Cube::random();
					f_Bike->vec_Color[7]->m_Z = Cube::random();

					f_Collection->m_vec_Element[f_Int]->acSync_fromBicycle(f_Bike);
					f_Collection->m_vec_Element[f_Int]->m_OCSCP_Flag = true;
					}
				}

			f_Hesh_Cade->m_bckred = Cube::random();
			f_Hesh_Cade->m_bckgreen = Cube::random();
			f_Hesh_Cade->m_bckblue = Cube::random();

#if 1		//force ok
			f_Hesh_Cade->ac_IsOK();
#endif

			if(g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] <= CPS_LOAD)
				{
				g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] = CPS_SCAN;
				}
			}

		//element rate per/s counter
		g_Wallet->m_vec_ElementCount[m_IDX] += f_ElementOnce;

		  ////////////////
		 // CALC READY //
		if(g_classLMap->m_LoadFinish == false)
			{
			m_DB_AccessLock.lock();

			if(g_classLMap->m_LoadFinish == false)
				{
				f_LoadInterruptor = g_classLMap->ac_CalcLoadFinish();
				}
			else
				{
				f_LoadInterruptor = 1;
				}

			m_DB_AccessLock.unlock();
			}
		else
			{
			f_LoadInterruptor = 1;
			}

			////////////
		   // HESH   //
		  // Target //
		if(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS)
			{
			if((g_classLMap->m_CPS_Result.size() >= g_SaveComplete_ThreadCount) && (f_LoadInterruptor == 1))
				{
				if((g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] == CPS_SCAN) && (g_Result == false))
					{
					int f_AttackIndex = f_SizeMin;

					int f_IntegerResult = g_classLMap->acCompute(f_Collection, f_OCSCP_ThreadIndex, f_AttackIndex, f_ElementOnce);

						////////////
					   // Save
					  // Hash
					 // Result
					if(f_IntegerResult > 0)
						{
						mutex_swap.lock();
						m_DB_AccessLock.lock();
						f_OCP_LOCK_ON = true;

						int f_OC_Mark_Count = g_Lowton->vec_Bicycle.size() + f_IntegerResult;

						for(int f_Jet = g_Lowton->vec_Bicycle.size(); f_Jet < f_OC_Mark_Count; f_Jet++)
							{
							if(f_Jet < f_Hesh_Cade->vec_Bicycle.size())
								{
								//make bike clone
								std::shared_ptr<CubeBicycle> f_WinningBike = f_Hesh_Cade->vec_Bicycle[f_Jet];

								ag_StatusLive(f_ref_CurrentPath, "f_Bike_Result");
								std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_reflect<Cube::CubeBicycle>();

								// Load mesh vertices. Each vertex has a position and a color.
								std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[0]->m_X, f_WinningBike->vec_Vertex[0]->m_Y, f_WinningBike->vec_Vertex[0]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[1]->m_X, f_WinningBike->vec_Vertex[1]->m_Y, f_WinningBike->vec_Vertex[1]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[2]->m_X, f_WinningBike->vec_Vertex[2]->m_Y, f_WinningBike->vec_Vertex[2]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[3]->m_X, f_WinningBike->vec_Vertex[3]->m_Y, f_WinningBike->vec_Vertex[3]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[4]->m_X, f_WinningBike->vec_Vertex[4]->m_Y, f_WinningBike->vec_Vertex[4]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[5]->m_X, f_WinningBike->vec_Vertex[5]->m_Y, f_WinningBike->vec_Vertex[5]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[6]->m_X, f_WinningBike->vec_Vertex[6]->m_Y, f_WinningBike->vec_Vertex[6]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Vertex[7]->m_X, f_WinningBike->vec_Vertex[7]->m_Y, f_WinningBike->vec_Vertex[7]->m_Z);

								std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[0]->m_X, f_WinningBike->vec_Color[0]->m_Y, f_WinningBike->vec_Color[0]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[1]->m_X, f_WinningBike->vec_Color[1]->m_Y, f_WinningBike->vec_Color[1]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[2]->m_X, f_WinningBike->vec_Color[2]->m_Y, f_WinningBike->vec_Color[2]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[3]->m_X, f_WinningBike->vec_Color[3]->m_Y, f_WinningBike->vec_Color[3]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[4]->m_X, f_WinningBike->vec_Color[4]->m_Y, f_WinningBike->vec_Color[4]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[5]->m_X, f_WinningBike->vec_Color[5]->m_Y, f_WinningBike->vec_Color[5]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[6]->m_X, f_WinningBike->vec_Color[6]->m_Y, f_WinningBike->vec_Color[6]->m_Z);
								std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(f_WinningBike->vec_Color[7]->m_X, f_WinningBike->vec_Color[7]->m_Y, f_WinningBike->vec_Color[7]->m_Z);

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

								g_Lowton->m_adIndex.push_back(f_Jet);

								ag_StatusLive(f_ref_CurrentPath, "f_Element_Result");
								std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Bike);

								g_Lowton_Collection->m_vec_Element.push_back(f_Element);
								g_Lowton_Collection->m_idx_vec_Element++;

								char* g_cubevalue[55];

								for(int f_Count = 0; f_Count < 55; f_Count++)
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

								ag_Freshanon<int>(g_Wallet->m_vec_blockid, m_IDX, ECOIN_DEFAULT_BLOCKID);

								::sprintf(g_cubevalue[48], "%i", g_Wallet->m_vec_blockid[m_IDX]);
								::sprintf(g_cubevalue[49], "%i", f_SCP_ShareID);
								::sprintf(g_cubevalue[50], "%i", g_JobID);
								::sprintf(g_cubevalue[51], "%i", f_Jet);
								::sprintf(g_cubevalue[52], "%i", g_CountLM);	// FIXME ADD L-TARGETID
								::sprintf(g_cubevalue[53], "%s", "CubePiece");
								::sprintf(g_cubevalue[54], "%f", 100.0f);

								int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, 55, 2, false);

								for(int f_Count = 0; f_Count < 55; f_Count++)
									{
									free(g_cubevalue[f_Count]);
									}
								}
							}

						ag_FreshOn<float>(g_Wallet->m_vec_bckred, m_IDX, f_Hesh_Cade->m_bckred);
						ag_FreshOn<float>(g_Wallet->m_vec_bckgreen, m_IDX, f_Hesh_Cade->m_bckgreen);
						ag_FreshOn<float>(g_Wallet->m_vec_bckblue, m_IDX, f_Hesh_Cade->m_bckblue);

						g_Lowton->m_bckblue = g_Wallet->m_vec_bckred[m_IDX];
						g_Lowton->m_bckred = g_Wallet->m_vec_bckgreen[m_IDX];
						g_Lowton->m_bckgreen = g_Wallet->m_vec_bckblue[m_IDX];

#if 0 //~First FreshOn
						ag_FreshOn<float, float>(g_Wallet->m_vec_bckred, m_IDX, f_Hesh_Cade->m_bckred);
#endif

						//ECN::f_adCount
						g_BicycleContainer[0]->m_ADMAX = g_Lowton->m_adIndex.size();
						g_BicycleContainer[0]->m_ADHIGH = g_Lowton->m_adIndex.size();
						g_BicycleContainer[0]->m_ADLOW = g_Lowton->m_adIndex.size();

							/////////////////////////
						// Set Render Target
						g_TargetedHesh = g_Lowton;

						g_TargetedHesh->ac_IsOK();

						g_RenderHesh = true;

						//push current lensing position
						g_classLMap->acPushLensePos(f_OCSCP_ThreadIndex);

						//print lowton result
						bool f_Resl = g_classLMap->acFinalCompute(g_Lowton_Collection, f_OCSCP_ThreadIndex);

						if(f_Resl == false)
							{
#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif
							}

						g_classLMap->acPopLensePos(f_OCSCP_ThreadIndex);

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

						if(f_OCP_LOCK_ON == false)
							{
							m_DB_AccessLock.lock();
							f_OCP_LOCK_ON = true;
							}

						g_JobID = g_Wallet->acGet_JobID(m_IDX);

						 ///////////////////////////////////////////////////////////////////////
						// Toss share calculation transaction onto next block/jobid as yield //
						Cag->ag_addGenesisTracking(f_SCP_ShareID, ecoin_BlockType::ecoin_Block_Target_SCP, f_OC_Lowton_Mark_Count);

						 /////////////////////////////////////////////////
						// Update Current SCP-Share according to Block //
						std::string f_Freshanon = "GenesisBlock";

						ag_Freshanon<std::string>(g_Wallet->m_vec_prevblock, m_IDX, f_Freshanon);

						std::string f_previousblock = g_Wallet->m_vec_prevblock[m_IDX];

						 /////////////////////
						// Gather StepHash //
						std::shared_ptr<Cube::CubeResults> f_Res = Cag->ag_GatherTransactions(g_JobID, m_IDX);

						 /////////////
						// TX Hash //
						std::string f_tx = f_Res->m_Result;

						 //////////////
						// JOB Hash //
						std::string f_job = f_tx + f_previousblock;

						 //////////////
						// job-hash //
						std::string f_TXJob_OutputHash = "";

						g_hasha.init(); //reset hasher state
						g_hasha.process(f_job.begin(), f_job.end());
						g_hasha.finish();
						picosha2::get_hash_hex_string(g_hasha, f_TXJob_OutputHash);

						 ///////////////////
						// FULL_UP Check //
						if(f_OC_Lowton_Mark_Count >= g_classLMap->m_ADMAX) //complete work, winning conditions!
							{/////////////////////
							// Compression OFF //
							g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_SHUTDOWN_COMPRESS;

							float f_LargeScoreFLT = ECOIN_REWARD_ON /*ECN_OPER_REWARD*/ + ECOIN_SCP_INSTANT_BONUS;
							int f_LargeScoreINT = 0;

							if(f_LargeScoreFLT < (float)INT_MAX)
								{
								f_LargeScoreINT = (int)f_LargeScoreFLT;
								}
							else
								{
								f_LargeScoreINT = INT_MAX;
								}

							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, f_LargeScoreINT);
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, g_CountLM);
							ag_FreshOn<float>(g_Wallet->m_vec_difficulty,m_IDX, ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
							ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger,m_IDX, f_TXJob_OutputHash);
							ag_Freshanon<float>(g_Wallet->m_vec_price,m_IDX, g_CurrentSharePrice);
							ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, ECOIN_DEFAULT_JOBBOARDID);
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);

							//convert ADMAX to scoreand maxvote
							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, f_LargeScoreFLT);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, f_LargeScoreFLT);

							char* g_sharefield_update[8];
							char* g_sharevalueup[8];
							char* f_sharewhere[1];

							for(int f_Count = 0; f_Count < 8; f_Count++)
								{
								g_sharefield_update[f_Count] = (char*)malloc(sizeof(char) * 1024);
								g_sharevalueup[f_Count] = (char*)malloc(sizeof(char) * 1024);
								}

							f_sharewhere[0] = (char*)malloc(sizeof(char) * 1024);

							::sprintf(g_sharefield_update[0], "jobboardid");
							::sprintf(g_sharefield_update[1], "jobledger");
							::sprintf(g_sharefield_update[2], "bckred");
							::sprintf(g_sharefield_update[3], "bckgreen");
							::sprintf(g_sharefield_update[4], "bckblue");
							::sprintf(g_sharefield_update[5], "score");
							::sprintf(g_sharefield_update[6], "mark");
							::sprintf(g_sharefield_update[7], "markfloat");
							
							::sprintf(g_sharevalueup[0], "%i", g_Wallet->m_vec_jobboardid[m_IDX]);
							::sprintf(g_sharevalueup[1], "%s", f_TXJob_OutputHash.c_str());
							::sprintf(g_sharevalueup[2], "%f", g_Wallet->m_vec_bckred[m_IDX]);
							::sprintf(g_sharevalueup[3], "%f", g_Wallet->m_vec_bckgreen[m_IDX]);
							::sprintf(g_sharevalueup[4], "%f", g_Wallet->m_vec_bckblue[m_IDX]);
							::sprintf(g_sharevalueup[5], "%f", g_Wallet->m_vec_score[m_IDX]);
							::sprintf(g_sharevalueup[6], "%i", g_Wallet->m_vec_mark[m_IDX]);
							::sprintf(g_sharevalueup[7], "%f", g_Wallet->m_vec_score[m_IDX]);

							::sprintf(f_sharewhere[0], "id = %i", f_SCP_ShareID);

							g_SafeL[0]->Update("share", (const char **)g_sharefield_update, (const char **)g_sharevalueup, 8, f_sharewhere[0], false, false);

							for(int f_Count = 0; f_Count < 8; f_Count++)
								{
								free(g_sharefield_update[f_Count]);
								free(g_sharevalueup[f_Count]);
								}

							free(f_sharewhere[0]);

							char* balancequery = ag_ClearChar(1000);
							::sprintf(balancequery, "Call acTopUpPeerBalanceAdvance(%i, %i)", f_SCP_ShareID, g_JobID);
							g_SafeL[0]->acSelectCommand(balancequery, 2, false);
							delete balancequery;

							std::shared_ptr<ShareContainerExt> f_PG = Cag->ag_SelectPeerGraphExt(g_JobID, 0, f_SCP_ShareID, g_CurrentShareOffset, g_PEER);

							g_CurrentShareOffset = f_PG->m_espo_ShareOffset;
							g_CurrentShareOffsetMAX = f_PG->m_espo_SharesOnPeerCount;
							g_PEER = f_PG->m_espo_Peer;
							g_PEERCNT = f_PG->m_espo_PeerCount;
							g_PEERMAX = f_PG->m_espo_PeerCount;
							g_espo_Owner = f_PG->m_espo_Owner;
							g_espo_Date = f_PG->m_espo_Date;
							g_espo_Score = f_PG->m_espo_Score;
							g_espo_Amount = f_PG->m_espo_Amount;
							g_espo_ECN_Amount = f_PG->m_espo_ECN_Amount;

							g_Found_Msg = 19;

							char* f_Chr = ag_ClearChar(2500);
							::sprintf(f_Chr, "ShareBlock Last Element Found onSHR#(...%i)!..ECN %.4f Percentage 100.00%", f_SCP_ShareID, g_Wallet->m_Reward);
							std::string f_ChrString = f_Chr;
							delete f_Chr;

							g_Found_Text = f_ChrString;

							g_ShareID = f_SCP_ShareID;

							g_Wallet->acSet_IDX(m_IDX);
							//...
							g_Wallet->acTestForBlock(g_BlockType, f_Res, true);
							}
						else
							{
							float f_LargeScoreFLT = (((float)g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX) * ECOIN_REWARD_ON) /*ECN_OPER_REWARD*/ + ECOIN_SCP_INSTANT_BONUS;
							int f_LargeScoreINT = 0;

							if(f_LargeScoreFLT < (float)INT_MAX)
								{
								f_LargeScoreINT = (int)f_LargeScoreFLT;
								}
							else
								{
								f_LargeScoreINT = INT_MAX;
								}

							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, f_LargeScoreINT);
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, g_CountLM);
							ag_FreshOn<float>(g_Wallet->m_vec_difficulty, m_IDX, ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
							ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_TXJob_OutputHash);
							ag_Freshanon<float>(g_Wallet->m_vec_price, m_IDX, g_CurrentSharePrice);
							ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, ECOIN_DEFAULT_JOBBOARDID);
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);

							//convert ADMAX to scoreand maxvote
							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, f_LargeScoreFLT);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, ECOIN_REWARD_ON /*ECN_OPER_REWARD*/ + ECOIN_SCP_INSTANT_BONUS);

							char* g_sharefield_update[8];
							char* g_sharevalueup[8];
							char* f_sharewhere[1];

							for(int f_Count = 0; f_Count < 8; f_Count++)
								{
								g_sharefield_update[f_Count] = (char*)malloc(sizeof(char) * 1024);
								g_sharevalueup[f_Count] = (char*)malloc(sizeof(char) * 1024);
								}

							f_sharewhere[0] = (char*)malloc(sizeof(char) * 1024);

							::sprintf(g_sharefield_update[0], "jobboardid");
							::sprintf(g_sharefield_update[1], "jobledger");
							::sprintf(g_sharefield_update[2], "bckred");
							::sprintf(g_sharefield_update[3], "bckgreen");
							::sprintf(g_sharefield_update[4], "bckblue");
							::sprintf(g_sharefield_update[5], "score");
							::sprintf(g_sharefield_update[6], "mark");
							::sprintf(g_sharefield_update[7], "markfloat");

							::sprintf(g_sharevalueup[0], "%i", g_Wallet->m_vec_jobboardid[m_IDX]);
							::sprintf(g_sharevalueup[1], "%s", f_TXJob_OutputHash.c_str());
							::sprintf(g_sharevalueup[2], "%f", g_Wallet->m_vec_bckred[m_IDX]);
							::sprintf(g_sharevalueup[3], "%f", g_Wallet->m_vec_bckgreen[m_IDX]);
							::sprintf(g_sharevalueup[4], "%f", g_Wallet->m_vec_bckblue[m_IDX]);
							::sprintf(g_sharevalueup[5], "%f", g_Wallet->m_vec_score[m_IDX]);
							::sprintf(g_sharevalueup[6], "%i", g_Wallet->m_vec_mark[m_IDX]);
							::sprintf(g_sharevalueup[7], "%f", g_Wallet->m_vec_score[m_IDX]);

							::sprintf(f_sharewhere[0], "id = %i", f_SCP_ShareID);

							g_SafeL[0]->Update("share", (const char **)g_sharefield_update, (const char **)g_sharevalueup, 8, f_sharewhere[0], false, false);

							for(int f_Count = 0; f_Count < 8; f_Count++)
								{
								free(g_sharefield_update[f_Count]);
								free(g_sharevalueup[f_Count]);
								}

							free(f_sharewhere[0]);

							char* balancequery = ag_ClearChar(1000);
							::sprintf(balancequery, "Call acTopUpPeerBalanceAdvance(%i, %i)", f_SCP_ShareID, g_JobID);
							g_SafeL[0]->acSelectCommand(balancequery, 2, false);
							delete balancequery;

							std::shared_ptr<ShareContainerExt> f_PG = Cag->ag_SelectPeerGraphExt(g_JobID, 0, f_SCP_ShareID, g_CurrentShareOffset, g_PEER);

							g_CurrentShareOffset = f_PG->m_espo_ShareOffset;
							g_CurrentShareOffsetMAX = f_PG->m_espo_SharesOnPeerCount;
							g_PEER = f_PG->m_espo_Peer;
							g_PEERCNT = f_PG->m_espo_PeerCount;
							g_PEERMAX = f_PG->m_espo_PeerCount;

							float f_amt = 50.0f * (1.0f / (float)g_classLMap->m_ADMAX);
							float f_Factor = (float)((float)g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX);

							f_Factor *= 100;

							char* percChar = ag_ClearChar(1000);
							::sprintf(percChar, "%.2f", f_Factor);
							std::string f_StringPercentage = percChar;
							delete percChar;

#if 0
							// ECN::Bond Reference Submitted
							ag_StatusLive(f_ref_CurrentPath, "f_Ack");
							std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_BOND_ELEMENT), f_SCP_ShareID, g_PEERCNT);
							f_Ack->m_ECN = f_amt;
							f_Ack->m_Reward = g_Wallet->m_Reward;
							f_Ack->m_Origin = 1;
							f_Ack->m_Owner = g_Wallet->GetAdr();
							f_Ack->m_PathOwner = g_Wallet->GetAdr();
							g_Ackent.push_back(f_Ack);
#endif

							g_Found_Msg = 29;

							char* f_Chr = ag_ClearChar(2500);
							::sprintf(f_Chr, "Bond Element Found onSHR#(...%i)!..ECN %.4f Percentage %s", f_SCP_ShareID, f_amt, f_StringPercentage.c_str());
							std::string f_ChrString = f_Chr;
							delete f_Chr;

							g_Found_Text = f_ChrString;

							g_ShareID = f_SCP_ShareID;
							}

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

						//Reset Point
						g_Result = false;

						mutex_swap.unlock();
						}
					else
						{
						//Full No Result, reverse Count Flags = false
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

					if(g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] == CPS_DRAW)
						{
						g_classLMap->m_CPS_Result[f_OCSCP_ThreadIndex] = CPS_SCAN;
						}

#ifdef SCP_RESET_LOCK
					g_Result = g_classLMap->ac_CalcScanReady(g_Result);
#endif
					}

				if(f_OCP_LOCK_ON == true)
					{
					m_DB_AccessLock.unlock();
					f_OCP_LOCK_ON = false;
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
		}
		
	 ///////////////////////////////////////////////////
	// not safe for multiple miner windows open on
	g_ElementDivisor.pop_back();
	g_ElementDivisorInt.pop_back();
	g_classLMap->m_SchemaRef.pop_back();
	g_classLMap->m_SaveSchemaRef.pop_back();
	g_classLMap->m_PushSchemaRef.pop_back();
	g_classLMap->m_SchemaMeasureIndex.pop_back();
	g_classLMap->m_PushMeasureIndex.pop_back();
	g_classLMap->m_CPS_Result.pop_back();
}

void Sample3DSceneRenderer::acGen_GenHesh(void)
{
	std::string f_ref_CurrentPath = "Sample3DSceneRenderer::acGen_GenHesh";

	m_DB_AccessLock.lock();

	int f_Divine_ThreadIndex = g_Divine_ThreadCount;

	g_Divine_ThreadCount++;

	char* f_Char = ag_ClearChar(64);
	sprintf(f_Char, "%i#", f_Divine_ThreadIndex);
	std::string f_hrIDA = f_Char;

	f_ref_CurrentPath += f_hrIDA;

	delete f_Char;

	float MATCH_MIN = g_Wallet->acSelect_JobVar(m_IDX, "MATCH_MIXIN");
	float MATCH_THRESH = g_Wallet->acSelect_JobVar(m_IDX, "MATCH_THRESH");
	float MATCH_THRESH_UP = g_Wallet->acSelect_JobVar(m_IDX, "MATCH_THRESH_UP");
	float COMPARE_QUALITY = g_Wallet->acSelect_JobVar(m_IDX, "COMPARE_QUALITY");

	//~main thresh
	float COMPARE_THRESH = g_Wallet->acSelect_JobVar(m_IDX, "COMPARE_THRESH");

	//~setup special variables
	LOWTON_STORAGE = (int)g_Wallet->acSelect_JobVar(m_IDX, "LOWTON_STORAGE");

	if(LOWTON_STORAGE <= 0.0f)
		{
		LOWTON_STORAGE = ECOIN_TARGET_LOWTON_STORAGE;
		}

	ag_Freshanon<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);

	if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
		{
		COMPARE_THRESH = g_Wallet->m_vec_markmin[m_IDX];

		g_BlockType = ecoin_BlockType::ecoin_Block_Target_SCP;
		}

	ag_StatusLive(f_ref_CurrentPath, "f_Hesh_Cade_GenHesh", true);
	std::shared_ptr<Cube::CubeHESH> f_Hesh_Cade = std::make_shared_reflect<Cube::CubeHESH>(g_BicycleContainer[0]->m_ADMAX, g_BicycleContainer[0]->m_ADHIGH, g_BicycleContainer[0]->m_ADLOW, g_CountLM);

	ag_StatusLive(f_ref_CurrentPath, "f_Lowton_Cade_GenHesh", true);
	std::shared_ptr<Cube::CubeHESH> f_Lowton_Cade = nullptr;

	ag_StatusLive(f_ref_CurrentPath, "f_Hesh_Cade->m_Hash", true);
	f_Hesh_Cade->m_Hash = std::make_shared_reflect<Cube::CubeHASH_originstring>();

	ag_StatusLive(f_ref_CurrentPath, "f_Lowton_Cade->m_Hash", true);
	f_Lowton_Cade->m_Hash = std::make_shared_reflect<Cube::CubeHASH_originstring>();

	std::shared_ptr<classTarget> f_Target_1 = nullptr;
	std::shared_ptr<classTarget> f_Target_2 = nullptr;

	  ///////////////////////////////////
	 // [FRTGME-FRMESH] g_Type Switch //
	///////////////////////////////////

	switch(g_Type)
		{
		case 0:
		case 1:
			{
			if(f_Target_1 == nullptr)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_Target_1_GenHesh");
				f_Target_1 = std::make_shared_reflect<classTarget>(f_Hesh_Cade);
				}
			}break;
		case 2:
			{
			if(f_Target_2 == nullptr)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_Target_2_GenHesh");
				f_Target_2 = std::make_shared_reflect<classTarget>(f_Hesh_Cade);
				}
			}break;
		}

	m_DB_AccessLock.unlock();

	bool f_Result = false;
	int f_NewADMAX = g_BicycleContainer[0]->m_ADMAX;

	ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_NONVIEW);
	ag_Freshanon<int>(g_Wallet->m_vec_ElementCount, m_IDX, 0);

	while(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW)
		{
		f_Result = false;
		f_NewADMAX = g_BicycleContainer[0]->m_ADMAX;

		if(g_KeepShare == false)
			{
			//[MARKING] g_Type Switch
			switch(g_Type)
				{
				case 0:
				case 1:
					{
					f_Target_1->m_Mark = 0.0f;
					}break;

				case 2:
					{
					f_Target_2->m_Mark = 0.0f;
					}break;

				case 3:
					{
					gf_Target_3->m_Mark = 0.0f;
					}break;

				case 4:
					{
					gf_Target_4->m_Mark = 0.0f;
					}break;

				case 5:
					{
					gf_Target_5->m_Mark = 0.0f;
					}break;

				case 6:
					{
					gf_Target_6->m_Mark = 0.0f;
					}break;

				case 7:
					{
					gf_Target_7->m_Mark = 0.0f;
					}break;

				case 8:
					{
					gf_Target_8->m_Mark = 0.0f;
					}break;

				case 9:
					{
					gf_Target_9->m_Mark = 0.0f;
					}break;

				case 10:
					{
					gf_Target_10->m_Mark = 0.0f;
					}break;
				}

			//hesh admax limiter
			while(f_Hesh_Cade->vec_Bicycle.size() > f_NewADMAX)
				{
				f_Hesh_Cade->vec_Bicycle.pop_back();
				f_Hesh_Cade->m_adIndex.pop_back();
				}

			for(int f_Int = 0; f_Int < f_NewADMAX; f_Int++)
				{
				if(f_Int >= f_Hesh_Cade->vec_Bicycle.size())
					{
					m_DB_AccessLock.lock();

					ag_StatusLive(f_ref_CurrentPath, "f_Bike_Once");
					std::shared_ptr<CubeBicycle> f_Bike = std::make_shared_reflect<Cube::CubeBicycle>();

					f_Bike->vec_Vertex.clear();

					// Load mesh vertices. Each vertex has a position and a color.
					Cube::BiRand f_BiRand;
					ag_StatusLive(f_ref_CurrentPath, "f_Vector1_Once");
					std::shared_ptr<Cube::BiVector> f_Vector1 = std::make_shared<Cube::BiVector>(-0.5f);
					f_Vector1->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					ag_StatusLive(f_ref_CurrentPath, "f_Vector2_Once");
					std::shared_ptr<Cube::BiVector> f_Vector2 = std::make_shared<Cube::BiVector>(-0.5f, -0.5f, 0.5f);
					f_Vector2->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					ag_StatusLive(f_ref_CurrentPath, "f_Vector3_Once");
					std::shared_ptr<Cube::BiVector> f_Vector3 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, -0.5f);
					f_Vector3->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					ag_StatusLive(f_ref_CurrentPath, "f_Vector4_Once");
					std::shared_ptr<Cube::BiVector> f_Vector4 = std::make_shared<Cube::BiVector>(-0.5f, 0.5f, 0.5f);
					f_Vector4->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					ag_StatusLive(f_ref_CurrentPath, "f_Vector5_Once");
					std::shared_ptr<Cube::BiVector> f_Vector5 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, -0.5f);
					f_Vector5->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					ag_StatusLive(f_ref_CurrentPath, "f_Vector6_Once");
					std::shared_ptr<Cube::BiVector> f_Vector6 = std::make_shared<Cube::BiVector>(0.5f, -0.5f, 0.5f);
					f_Vector6->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					ag_StatusLive(f_ref_CurrentPath, "f_Vector7_Once");
					std::shared_ptr<Cube::BiVector> f_Vector7 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, -0.5f);
					f_Vector7->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
					f_BiRand.acGet();
					ag_StatusLive(f_ref_CurrentPath, "f_Vector8_Once");
					std::shared_ptr<Cube::BiVector> f_Vector8 = std::make_shared<Cube::BiVector>(0.5f, 0.5f, 0.5f);
					f_Vector8->acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

					ag_StatusLive(f_ref_CurrentPath, "f_Color1_Once");
					std::shared_ptr<Cube::BiVector> f_Color1 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					ag_StatusLive(f_ref_CurrentPath, "f_Color2_Once");
					std::shared_ptr<Cube::BiVector> f_Color2 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					ag_StatusLive(f_ref_CurrentPath, "f_Color3_Once");
					std::shared_ptr<Cube::BiVector> f_Color3 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					ag_StatusLive(f_ref_CurrentPath, "f_Color4_Once");
					std::shared_ptr<Cube::BiVector> f_Color4 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					ag_StatusLive(f_ref_CurrentPath, "f_Color5_Once");
					std::shared_ptr<Cube::BiVector> f_Color5 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					ag_StatusLive(f_ref_CurrentPath, "f_Color6_Once");
					std::shared_ptr<Cube::BiVector> f_Color6 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					ag_StatusLive(f_ref_CurrentPath, "f_Color7_Once");
					std::shared_ptr<Cube::BiVector> f_Color7 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());
					ag_StatusLive(f_ref_CurrentPath, "f_Color8_Once");
					std::shared_ptr<Cube::BiVector> f_Color8 = std::make_shared<Cube::BiVector>(Cube::random(), Cube::random(), Cube::random());

					m_DB_AccessLock.unlock();

					Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

					f_Vector1->acResolve_precision(SCP_FLT_SCALE);
					f_Vector2->acResolve_precision(SCP_FLT_SCALE);
					f_Vector3->acResolve_precision(SCP_FLT_SCALE);
					f_Vector4->acResolve_precision(SCP_FLT_SCALE);
					f_Vector5->acResolve_precision(SCP_FLT_SCALE);
					f_Vector6->acResolve_precision(SCP_FLT_SCALE);
					f_Vector7->acResolve_precision(SCP_FLT_SCALE);
					f_Vector8->acResolve_precision(SCP_FLT_SCALE);

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

					m_DB_AccessLock.lock();

					f_Hesh_Cade->vec_Bicycle.push_back(f_Bike);

					f_Hesh_Cade->m_adIndex.push_back(f_Hesh_Cade->m_adIndex.size());

					m_DB_AccessLock.unlock();
					}
				else
					{
					std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[f_Int];

					f_Bike->vec_Vertex[0]->m_X = ag_RVC();
					f_Bike->vec_Vertex[0]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[0]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[1]->m_X = ag_RVC();
					f_Bike->vec_Vertex[1]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[1]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[2]->m_X = ag_RVC();
					f_Bike->vec_Vertex[2]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[2]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[3]->m_X = ag_RVC();
					f_Bike->vec_Vertex[3]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[3]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[4]->m_X = ag_RVC();
					f_Bike->vec_Vertex[4]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[4]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[5]->m_X = ag_RVC();
					f_Bike->vec_Vertex[5]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[5]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[6]->m_X = ag_RVC();
					f_Bike->vec_Vertex[6]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[6]->m_Z = ag_RVC();

					f_Bike->vec_Vertex[7]->m_X = ag_RVC();
					f_Bike->vec_Vertex[7]->m_Y = ag_RVC();
					f_Bike->vec_Vertex[7]->m_Z = ag_RVC();

					f_Bike->vec_Color[0]->m_X = Cube::random();
					f_Bike->vec_Color[0]->m_Y = Cube::random();
					f_Bike->vec_Color[0]->m_Z = Cube::random();

					f_Bike->vec_Color[1]->m_X = Cube::random();
					f_Bike->vec_Color[1]->m_Y = Cube::random();
					f_Bike->vec_Color[1]->m_Z = Cube::random();

					f_Bike->vec_Color[2]->m_X = Cube::random();
					f_Bike->vec_Color[2]->m_Y = Cube::random();
					f_Bike->vec_Color[2]->m_Z = Cube::random();

					f_Bike->vec_Color[3]->m_X = Cube::random();
					f_Bike->vec_Color[3]->m_Y = Cube::random();
					f_Bike->vec_Color[3]->m_Z = Cube::random();

					f_Bike->vec_Color[4]->m_X = Cube::random();
					f_Bike->vec_Color[4]->m_Y = Cube::random();
					f_Bike->vec_Color[4]->m_Z = Cube::random();

					f_Bike->vec_Color[5]->m_X = Cube::random();
					f_Bike->vec_Color[5]->m_Y = Cube::random();
					f_Bike->vec_Color[5]->m_Z = Cube::random();

					f_Bike->vec_Color[6]->m_X = Cube::random();
					f_Bike->vec_Color[6]->m_Y = Cube::random();
					f_Bike->vec_Color[6]->m_Z = Cube::random();

					f_Bike->vec_Color[7]->m_X = Cube::random();
					f_Bike->vec_Color[7]->m_Y = Cube::random();
					f_Bike->vec_Color[7]->m_Z = Cube::random();

#if 0
					f_Collection->m_vec_Element[f_Int]->acSync_fromBicycle_affinity(f_Bike);
#endif
					}
				}

			f_Hesh_Cade->m_bckred = Cube::random();
			f_Hesh_Cade->m_bckgreen = Cube::random();
			f_Hesh_Cade->m_bckblue = Cube::random();

			f_Hesh_Cade->ac_IsOK();

			    ////////////
			   // HESH   //
			  // Target //
			 //
			//[MARKING] g_Type Switch
			switch(g_Type)
				{
				case 0:
				case 1:
					{
					f_Target_1->acSync_fromHesh(f_Hesh_Cade);

					f_Result = g_Target_1->acCompare(f_Target_1, COMPARE_QUALITY, COMPARE_THRESH, true);

					 /////////////////
					// Match Check //
					float f_Mark = f_Target_1->m_Mark;

					float f_MatchMark = g_Target_1->acMatch(f_Target_1);

					if(f_MatchMark <= MATCH_THRESH)
						{
						f_Result = true;
						}

					if(f_MatchMark > MATCH_THRESH_UP)
						{
						f_Result = false;
						}

					f_Target_1->m_Mark = (f_MatchMark * MATCH_MIN) * f_Target_1->m_Mark;
					}break;

				case 2:
					{
					f_Target_2->acSync_fromHesh(f_Hesh_Cade);

					f_Result = g_Target_2->acCompare(f_Target_2, COMPARE_QUALITY, COMPARE_THRESH, true);

					 /////////////////
					// Match Check //
					float f_Mark = f_Target_2->m_Mark;

					float f_MatchMark = g_Target_2->acMatch(f_Target_2);

					if(f_MatchMark <= MATCH_THRESH)
						{
						f_Result = true;
						}

					if(f_MatchMark > MATCH_THRESH_UP)
						{
						f_Result = false;
						}

					f_Target_2->m_Mark = (f_MatchMark * MATCH_MIN) * f_Target_2->m_Mark;
					}break;

				case 3:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared_reflect<classTarget_Ecom>();

					//g_QcomManager->acClearGrid();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_3);

					//f_Result = g_Target_3->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_3 = f_Target;
					}break;

				case 4:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_Ecom> f_Target = std::make_shared_reflect<classTarget_Ecom>();

					//g_QcomManager->acClearGrid();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_4);

					//f_Result = g_Target_4->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_4 = f_Target;
					}break;

				case 5:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared_reflect<classTarget_ESL_Script>();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_5);

					//f_Result = g_Target_5->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_5 = f_Target;
					}break;

				case 6:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_ESL_Script> f_Target = std::make_shared_reflect<classTarget_ESL_Script>();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_6);

					//f_Result = g_Target_6->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_6 = f_Target;
					}break;
				case 7:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared_reflect<classTarget_Generation_Script>();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_7);

					//f_Result = g_Target_7->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_7 = f_Target;
					}break;

				case 8:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_Generation_Script> f_Target = std::make_shared_reflect<classTarget_Generation_Script>();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_8);

					//f_Result = g_Target_8->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_8 = f_Target;
					}break;

				case 9:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_JScript> f_Target = std::make_shared_reflect<classTarget_JScript>();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_9);

					//f_Result = g_Target_9->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_9 = f_Target;
					}break;

				case 10:
					{
					//ag_StatusLive(f_ref_CurrentPath, "f_Target");
					//std::shared_ptr<classTarget_JScript> f_Target = std::make_shared_reflect<classTarget_JScript>();

					//f_Target->acFromHesh(f_Hesh_Cade, g_Target_10);

					//f_Result = g_Target_10->acCompare(f_Target, COMPARE_QUALITY, f_Difficulty);

					//gf_Target_10 = f_Target;
					}break;
				}

			g_Wallet->m_vec_ElementCount_Muti[m_IDX]->lock();

			g_Wallet->m_vec_ElementCount[m_IDX] += f_NewADMAX;

			g_Wallet->m_vec_ElementCount_Muti[m_IDX]->unlock();
			}

		   ////////////
		  //
		 // Result
		//
		if((f_Result == true) && (g_KeepShare == false))
			{
			mutex_swap.lock();
			m_DB_AccessLock.lock();

			 ////////////
			// Hash
			f_Hesh_Cade->m_Hash->acClear();

			for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
				{
				for(int f_Helly = 0; f_Helly < 8; f_Helly++)
					{
					f_Hesh_Cade->m_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
					f_Hesh_Cade->m_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
					f_Hesh_Cade->m_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
					}
				}

			for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
				{
				for(int f_Helly = 0; f_Helly < 8; f_Helly++)
					{
					f_Hesh_Cade->m_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
					f_Hesh_Cade->m_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
					f_Hesh_Cade->m_Hash->acPushFloat(f_Hesh_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
					}
				}

			for(int f_Jet = 0; f_Jet < f_Hesh_Cade->m_adIndex.size(); f_Jet++)
				{
				f_Hesh_Cade->m_Hash->acPushInt(f_Hesh_Cade->m_adIndex[f_Jet]);
				}
							
			std::string f_InputHash = f_Hesh_Cade->m_Hash->acGetInput();

			f_Hesh_Cade->m_Hash->acClear();

			std::string f_Share_OutputHash = "";

			g_hasha.init(); //reset hasher state
			g_hasha.process(f_InputHash.begin(), f_InputHash.end());
			g_hasha.finish();
			picosha2::get_hash_hex_string(g_hasha, f_Share_OutputHash);

			 ////////////////////
			//Current Job ID //
			g_JobID = g_Wallet->acGet_JobID(m_IDX);

			 ////////////////////////////////////////////////////
			// check previous Block not GenesisBlock (assume) //
			std::string f_StrBlock = "GENESISBLOCK";

			ag_Freshanon<std::string>(g_Wallet->m_vec_prevblock, m_IDX, f_StrBlock);

			std::string f_previousblock = g_Wallet->m_vec_prevblock[m_IDX];

			 /////////////////////
			// Gather StepHash //
			std::shared_ptr<Cube::CubeResults> f_Res = Cag->ag_GatherTransactions(g_JobID, m_IDX);

			 ////////////
			// TXHash //
			std::string f_tx = f_Res->m_Result;

			 //////////////
			// JOB Hash //
			std::string f_job = f_tx + f_previousblock;

			 ///////////////
			// Input Job //
			std::string f_AnyInputHash = f_job;

			std::string f_TXJobledger_OutputHash = "";

			g_hasha.init(); //reset hasher state
			g_hasha.process(f_AnyInputHash.begin(), f_AnyInputHash.end());
			g_hasha.finish();
			picosha2::get_hash_hex_string(g_hasha, f_TXJobledger_OutputHash);

			ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_TXJobledger_OutputHash);
			ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, 0);
			ag_Freshanon<int>(g_Wallet->m_vec_scoremax, m_IDX, 0);
			ag_Freshanon<float>(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
			ag_Freshanon<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);
			ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
			ag_Freshanon<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0.0f);

			ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);

			switch(g_BlockType)
				{
				case ecoin_BlockType::ecoin_Block_Target_TypeName:
					{
					//convert scoremax to maxvote
					if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
						{
						ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, g_Wallet->m_vec_scoremax[m_IDX]);
						ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (ag_Get_current_Target_Mark(g_Type)* ag_Get_current_Target_Mark(g_Type)));
						}
					else
						{
						if(g_Wallet->m_vec_markmax[m_IDX] > 0.0f)
							{
							if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
								{
								ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, g_Wallet->m_vec_markmin[m_IDX]);
								ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, ((1 - (ag_Get_current_Target_Mark(g_Type) / 12325936)) * 6198913.16789523) / (ag_Get_current_Target_Mark(g_Type) * (0.046 * g_Wallet->m_vec_markmin[m_IDX])));
								}
							else
								{
								ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, g_Wallet->m_vec_markmax[m_IDX]);
								ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (ag_Get_current_Target_Mark(g_Type) * ag_Get_current_Target_Mark(g_Type)));
								}
							}
						else
							{
							if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
								{
								ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, g_Wallet->m_vec_markmin[m_IDX]);
								ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, ((1 - (ag_Get_current_Target_Mark(g_Type) / 12325936)) * 6198913.16789523) / (ag_Get_current_Target_Mark(g_Type) * (0.046 * g_Wallet->m_vec_markmin[m_IDX])));
								}
							else
								{
								ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, COMPARE_THRESH); //lean towards COMPARE_THRESH minimum mark
								}
							}
						}
					}break;

				case ecoin_BlockType::ecoin_Block_Target_TimedType:
					{
					ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, ag_Get_current_Target_Mark(g_Type)); //possibly invert

					//convert scoremax to maxvote
					if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
						{
						ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)g_Wallet->m_vec_scoremax[m_IDX]);
						}
					else
						{
						std::time_t f_CurrentTime;
						std::time(&f_CurrentTime);

						ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)g_Wallet->m_vec_targetbreach[m_IDX] - (float)f_CurrentTime);
						}
					}break;

				case ecoin_BlockType::ecoin_Block_Target_SCP:
					{
					//convert ADMAX to score and maxvote
					ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)(g_BicycleContainer[0]->m_ADMAX / g_classLMap->m_ADMAX) * ((float)ECOIN_SCP_REWARD_FACT5000 * (float)ECOIN_SCP_REWARD_FACT5000) /*ECN_OPER_REWARD*/ + (float)ECOIN_SCP_INSTANT_BONUS);
					ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)((float)ECOIN_SCP_REWARD_FACT5000 * (float)ECOIN_SCP_REWARD_FACT5000) /*ECN_OPER_REWARD*/ + (float)ECOIN_SCP_INSTANT_BONUS);
					//...mebbe add debug message
					}break;

				case ecoin_BlockType::ecoin_Block_TimedPledge:
					{
					//convert scoremax to maxvote
					if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
						{
						std::time_t f_CurrentTime;
						std::time(&f_CurrentTime);

						ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)g_Wallet->m_vec_scoremax[m_IDX] - (float)f_CurrentTime);
						ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)g_Wallet->m_vec_scoremax[m_IDX]);
						}
					else
						{
						std::time_t f_CurrentTime;
						std::time(&f_CurrentTime);

						ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)f_CurrentTime - (float)g_Wallet->m_vec_startbreach[m_IDX]);
						ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)g_Wallet->m_vec_targetbreach[m_IDX]);
						}
					}break;

				case ecoin_BlockType::ecoin_Block_MaxPledge:
					{
					//update share integer voting score
					ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, 0.0f);

					//convert scoremax to maxvote
					if(g_Wallet->m_vec_maxpledge[m_IDX] > 0)
						{
						ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)g_Wallet->m_vec_maxpledge[m_IDX]);
						}
					else
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif //add debug message
						}
					}break;

				case ecoin_BlockType::ecoin_Block_MaxTimedPledge:
					{
					if(m_IDX < g_Wallet->m_vec_scoremax.size())
						{
						//convert scoremax to maxvote
						if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
							{
							std::time_t f_CurrentTime;
							std::time(&f_CurrentTime);

							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)g_Wallet->m_vec_scoremax[m_IDX] - (float)f_CurrentTime);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)g_Wallet->m_vec_scoremax[m_IDX]);
							}
						else
							{
							std::time_t f_CurrentTime;
							std::time(&f_CurrentTime);

							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)f_CurrentTime - (float)g_Wallet->m_vec_startbreach[m_IDX]);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, (float)g_Wallet->m_vec_targetbreach[m_IDX]);
							}
						}
					}break;
				}

			ag_FreshOn<float>(g_Wallet->m_vec_bckred, m_IDX, f_Hesh_Cade->m_bckred);
			ag_FreshOn<float>(g_Wallet->m_vec_bckgreen, m_IDX, f_Hesh_Cade->m_bckgreen);
			ag_FreshOn<float>(g_Wallet->m_vec_bckblue, m_IDX, f_Hesh_Cade->m_bckblue);

			ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)ag_Get_current_Target_Mark(g_Type));
			ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, ECOIN_DEFAULT_ESLID);
			ag_FreshOn<float>(g_Wallet->m_vec_difficulty, m_IDX, COMPARE_THRESH);
			ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
			ag_Freshanon<float>(g_Wallet->m_vec_price, m_IDX, g_CurrentSharePrice);
			ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, f_Hesh_Cade->m_adIndex.size());

			ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, -1);

			char* g_sharevalue[25];

			for(int f_Count = 0; f_Count < 25; f_Count++)
				{
				g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
				}

			::sprintf(g_sharevalue[0], "%i", (int)ag_Get_current_Target_Mark(g_Type));
			::sprintf(g_sharevalue[1], "%f", ag_Get_current_Target_Mark(g_Type));
			::sprintf(g_sharevalue[2], "%i", 1);
			::sprintf(g_sharevalue[3], "%i", 3);
			::sprintf(g_sharevalue[4], "%i", g_JobID);
			::sprintf(g_sharevalue[5], "%i", g_Wallet->m_vec_jobboardid[m_IDX]);
			::sprintf(g_sharevalue[6], "%i", g_Wallet->m_vec_eslid[m_IDX]); //set to one
			::sprintf(g_sharevalue[7], "%i", g_Wallet->m_vec_targetid[m_IDX]);
			::sprintf(g_sharevalue[8], "%s", g_TypeName.c_str());
			::sprintf(g_sharevalue[9], "%f", (g_Wallet->m_vec_score[m_IDX] / g_Wallet->m_vec_maxvote[m_IDX]));
			::sprintf(g_sharevalue[10], "%f", g_Wallet->m_vec_score[m_IDX]);
			::sprintf(g_sharevalue[11], "%f", g_Wallet->m_vec_maxvote[m_IDX]);
			::sprintf(g_sharevalue[12], "%s", f_Share_OutputHash.c_str());
			::sprintf(g_sharevalue[13], "%s", g_Wallet->m_vec_blockledger[m_IDX].c_str());
			::sprintf(g_sharevalue[14], "%s", g_Wallet->GetAdr().c_str());
			::sprintf(g_sharevalue[15], "%f", g_Wallet->m_vec_bckred[m_IDX]);
			::sprintf(g_sharevalue[16], "%f", g_Wallet->m_vec_bckgreen[m_IDX]);
			::sprintf(g_sharevalue[17], "%f", g_Wallet->m_vec_bckblue[m_IDX]);
			::sprintf(g_sharevalue[18], "%i", g_CurrentComID);
			::sprintf(g_sharevalue[19], "%f", g_Wallet->m_Reward);
			::sprintf(g_sharevalue[20], "%f", 0.0f);
			::sprintf(g_sharevalue[21], "%f", 0.0f);
			::sprintf(g_sharevalue[22], "%f", ECN_TX_FEE);
			::sprintf(g_sharevalue[23], "%f", g_CurrentSharePrice);
			::sprintf(g_sharevalue[24], "%i", g_BlockType);
			
			 ////////////////////
			// poll for share //
			char* shlquery = ag_ClearChar(1000);
			::sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Share_OutputHash.c_str());
			g_SafeL[0]->acSelectCommand(shlquery, 2, false);
			delete shlquery;

			int f_ShareLCount = 0;

			if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
				{
				f_ShareLCount = 0;
				}
			else
				{
				f_ShareLCount = g_Schedular[0]->acEntrySize();
				}

			//ECN::Stat::: f_ShareLCount
			if(f_ShareLCount == 0)
				{
				int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 25, 2, false);

				for(int f_Count = 0; f_Count < 25; f_Count++)
					{
					free(g_sharevalue[f_Count]);
					}

				//ECN::Stat::: f_shareuniqueID
				g_ShareID = f_ShareUniqueID;

				for(int f_Int = 0; f_Int < f_Hesh_Cade->m_adIndex.size(); f_Int++)
					{
					std::shared_ptr<CubeBicycle> f_Bike = f_Hesh_Cade->vec_Bicycle[f_Hesh_Cade->m_adIndex[f_Int]];

					char* g_cubevalue[55];

					for(int f_Count = 0; f_Count < 55; f_Count++)
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
				
					::sprintf(g_cubevalue[48], "%i", g_Wallet->m_vec_blockid[m_IDX]);
					::sprintf(g_cubevalue[49], "%i", f_ShareUniqueID);
					::sprintf(g_cubevalue[50], "%i", g_JobID);
					::sprintf(g_cubevalue[51], "%i", f_Int);
					::sprintf(g_cubevalue[52], "%i", g_Wallet->m_vec_targetid[m_IDX]);
					::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
					::sprintf(g_cubevalue[54], "%f", COMPARE_THRESH);

					int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, 55, 2, false);

					for(int f_Count = 0; f_Count < 55; f_Count++)
						{
						free(g_cubevalue[f_Count]);
						}
					}

				g_TargetedHesh->acClear();

				g_TargetedHesh = f_Hesh_Cade;

				ag_StatusLive(f_ref_CurrentPath, "f_Hesh_Cade_NewCade");
				f_Hesh_Cade = std::make_shared_reflect<Cube::CubeHESH>(g_BicycleContainer[0]->m_ADMAX, g_BicycleContainer[0]->m_ADHIGH, g_BicycleContainer[0]->m_ADLOW, g_CountLM);

				g_TargetedHesh->ac_IsOK();

				//ECN::f_adCount
				g_BicycleContainer[0]->m_ADMAX = g_TargetedHesh->m_adIndex.size();
				g_BicycleContainer[0]->m_ADHIGH = g_TargetedHesh->m_adIndex.size();
				g_BicycleContainer[0]->m_ADLOW = g_TargetedHesh->m_adIndex.size();

				g_RenderHesh = true;

				char* balancequery = ag_ClearChar(1000);
				::sprintf(balancequery, "Call acTopUpPeerBalanceAdvance(%i, %i)", g_ShareID, g_JobID);
				g_SafeL[0]->acSelectCommand(balancequery, 2, false);
				delete balancequery;

				Cag->ag_addGenesisTracking(f_ShareUniqueID, g_BlockType);

				std::shared_ptr<ShareContainerExt> f_PG = Cag->ag_SelectPeerGraphExt(g_JobID, 0, g_ShareID, g_CurrentShareOffset, g_PEER);

				g_CurrentShareOffset = f_PG->m_espo_ShareOffset;
				g_CurrentShareOffsetMAX = f_PG->m_espo_SharesOnPeerCount;
				g_PEER = f_PG->m_espo_Peer;
				g_PEERCNT = f_PG->m_espo_PeerCount;
				g_PEERMAX = f_PG->m_espo_PeerCount;

				//ECN::Share Submitted.
				ag_StatusLive(f_ref_CurrentPath, "f_Ack");
				std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_SHARE), g_ShareID, g_PEERCNT);
				f_Ack->m_ECN = 0.0f;
				f_Ack->m_Reward = g_Wallet->m_Reward;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = g_Wallet->GetAdr();
				f_Ack->m_PathOwner = g_Wallet->GetAdr();
				g_Ackent.push_back(f_Ack);

				m_LowtonTicket = -1;

				time(&g_storagetime);
				g_storagetime += LOWTON_STORAGE;

				g_LowtonMark = FLT_MAX;

				if(g_BlockType != ecoin_BlockType::ecoin_Block_MaxPledge)
					{
					g_Wallet->acSet_IDX(m_IDX);
					//...
					g_Wallet->acTestForBlock(g_BlockType, f_Res, true);
					}
				}
			else
				{
				for(int f_Count = 0; f_Count < 25; f_Count++)
					{
					free(g_sharevalue[f_Count]);
					}

				g_Found_Msg = 9;
				g_Found_Text = "Duplicate Share Found...";

				f_Result = false;
				}

			mutex_swap.unlock();
			m_DB_AccessLock.unlock();
			}
		else
			{
			float f_Mark = 0.0f;

			//[MARKING] g_Type Switch
			switch(g_Type)
				{
				case 0:
				case 1:
					{
					f_Mark = f_Target_1->m_Mark;
					}break;

				case 2:
					{
					f_Mark = f_Target_2->m_Mark;
					}break;

				case 3:
					{
					f_Mark = gf_Target_3->m_Mark;
					}break;

				case 4:
					{
					f_Mark = gf_Target_4->m_Mark;
					}break;

				case 5:
					{
					f_Mark = gf_Target_5->m_Mark;
					}break;

				case 6:
					{
					f_Mark = gf_Target_6->m_Mark;
					}break;

				case 7:
					{
					f_Mark = gf_Target_7->m_Mark;
					}break;

				case 8:
					{
					f_Mark = gf_Target_8->m_Mark;
					}break;

				case 9:
					{
					f_Mark = gf_Target_9->m_Mark;
					}break;

				case 10:
					{
					f_Mark = gf_Target_10->m_Mark;
					}break;
				}

			if(g_KeepShare == false)
				{
				if(f_Mark < g_LowtonMark)
					{
					mutex_swap.lock();
					m_DB_AccessLock.lock();

					if(f_Mark < g_LowtonMark)
						{
						m_LowtonTicket = f_Divine_ThreadIndex;

						g_LowtonMark = f_Mark;

						//clear current lowton
						g_TargetedHesh->acClear();

						f_Lowton_Cade->acClear();

						f_Lowton_Cade = f_Hesh_Cade;

						ag_StatusLive(f_ref_CurrentPath, "f_Hesh_Cade_NewCade_Lowton");
						f_Hesh_Cade = std::make_shared_reflect<Cube::CubeHESH>(g_BicycleContainer[0]->m_ADMAX, g_BicycleContainer[0]->m_ADHIGH, g_BicycleContainer[0]->m_ADLOW, g_CountLM);

						  //////////////////
						 // Lowton Hash //
						f_Lowton_Cade->m_Hash->acClear();

						for(int f_Jet = 0; f_Jet < f_Lowton_Cade->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								f_Lowton_Cade->m_Hash->acPushFloat(f_Lowton_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_X);
								f_Lowton_Cade->m_Hash->acPushFloat(f_Lowton_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Y);
								f_Lowton_Cade->m_Hash->acPushFloat(f_Lowton_Cade->vec_Bicycle[f_Jet]->vec_Vertex[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < f_Lowton_Cade->m_adIndex.size(); f_Jet++)
							{
							for(int f_Helly = 0; f_Helly < 8; f_Helly++)
								{
								f_Lowton_Cade->m_Hash->acPushFloat(f_Lowton_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_X);
								f_Lowton_Cade->m_Hash->acPushFloat(f_Lowton_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Y);
								f_Lowton_Cade->m_Hash->acPushFloat(f_Lowton_Cade->vec_Bicycle[f_Jet]->vec_Color[f_Helly]->m_Z);
								}
							}

						for(int f_Jet = 0; f_Jet < f_Lowton_Cade->m_adIndex.size(); f_Jet++)
							{
							f_Lowton_Cade->m_Hash->acPushInt(f_Lowton_Cade->m_adIndex[f_Jet]);
							}

						g_TargetedHesh = f_Lowton_Cade;

						//ECN::f_adCount
						g_BicycleContainer[0]->m_ADMAX = g_TargetedHesh->m_adIndex.size();
						g_BicycleContainer[0]->m_ADHIGH = g_TargetedHesh->m_adIndex.size();
						g_BicycleContainer[0]->m_ADLOW = g_TargetedHesh->m_adIndex.size();

						g_TargetedHesh->ac_IsOK();

						g_RenderHesh = true;

						//~New LowTon Holding... g_LowtonMark
						time(&g_storagetime);
						g_storagetime += LOWTON_STORAGE;

						switch(g_Type)
							{
							case 0:
							case 1:
								{
								g_LowtonTarget_1 = f_Target_1;
								}break;

							case 2:
								{
								g_LowtonTarget_2 = f_Target_2;
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
						}

					mutex_swap.unlock();
					m_DB_AccessLock.unlock();
					}
				}

			time(&g_currenttime);

			if((g_currenttime > g_storagetime) && (m_LowtonTicket == f_Divine_ThreadIndex))
				{
				mutex_swap.lock();
				m_DB_AccessLock.lock();

				  ////////////
				 // Hash
				//
				std::string f_InputHash = f_Lowton_Cade->m_Hash->acGetInput();

				std::string f_Share_OutputHash = "";

				g_hasha.init(); //reset hasher state
				g_hasha.process(f_InputHash.begin(), f_InputHash.end());
				g_hasha.finish();
				picosha2::get_hash_hex_string(g_hasha, f_Share_OutputHash);

				 ////////////////////
				//Current Job ID //
				g_JobID = g_Wallet->acGet_JobID(m_IDX);

				 ////////////////////////////////////////////////////////
				// check Previous BlockHesh not GenesisBlock (assume) //
				std::string f_StrBlock = "GENESISBLOCK";

				ag_Freshanon<std::string>(g_Wallet->m_vec_prevblock, m_IDX, f_StrBlock);

				std::string f_previousblock = g_Wallet->m_vec_prevblock[m_IDX];

				 /////////////////////
				// Gather StepHash //
				std::shared_ptr<Cube::CubeResults> f_Res = Cag->ag_GatherTransactions(g_JobID, m_IDX);

				 /////////////
				// TX Hash //
				std::string f_tx = f_Res->m_Result;

				 //////////////
				// JOB Hash //
				std::string f_job = f_tx + f_previousblock;

				 /////////////////
				// Hash Input //
				std::string f_AnyInputHash = f_job;

				std::string f_TXJobledger_OutputHash = "";

				g_hasha.init(); //reset hasher state
				g_hasha.process(f_AnyInputHash.begin(), f_AnyInputHash.end());
				g_hasha.finish();
				picosha2::get_hash_hex_string(g_hasha, f_TXJobledger_OutputHash);

				ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_TXJobledger_OutputHash);
				ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, 0);
				ag_Freshanon<int>(g_Wallet->m_vec_scoremax, m_IDX, 0);
				ag_Freshanon<float>(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
				ag_Freshanon<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);
				ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
				ag_Freshanon<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0.0f);

				ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);

				switch(g_BlockType)
					{
					case ecoin_BlockType::ecoin_Block_Target_TypeName:
						{
						//convert scoremax to maxvote
						if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
							{
							g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_scoremax[m_IDX];

							g_Wallet->m_vec_score[m_IDX] = (g_LowtonMark * g_LowtonMark);
							}
						else
							{
							if(g_Wallet->m_vec_markmax[m_IDX] > 0.0f)
								{
								if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
									{
									g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmin[m_IDX];

									g_Wallet->m_vec_score[m_IDX] = ((1 - (g_LowtonMark / 12325936)) * 6198913.16789523) / (g_LowtonMark * (0.046 * g_Wallet->m_vec_markmin[m_IDX]));
									}
								else
									{
									g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmax[m_IDX];

									g_Wallet->m_vec_score[m_IDX] = (g_LowtonMark * g_LowtonMark);
									}
								}
							else
								{
								if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
									{
									g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmin[m_IDX];

									g_Wallet->m_vec_score[m_IDX] = ((1 - (g_LowtonMark / 12325936)) * 6198913.16789523) / (g_LowtonMark * (0.046 * g_Wallet->m_vec_markmin[m_IDX]));
									}
								else
									{
									g_Wallet->m_vec_maxvote[m_IDX] = COMPARE_THRESH; //lean towards COMPARE_THRESH minimum mark
									}
								}
							}
						}break;

					case ecoin_BlockType::ecoin_Block_Target_TimedType:
						{
						g_Wallet->m_vec_score[m_IDX] = ((1 - (g_LowtonMark / 12325936)) * 6198913.16789523) / (g_LowtonMark * 0.046);

						//convert scoremax to maxvote
						if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
							{
							g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_scoremax[m_IDX];
							}
						else
							{
							if(g_Wallet->m_vec_markmax[m_IDX] > 0.0f)
								{
								if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
									{
									g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmin[m_IDX];

									g_Wallet->m_vec_score[m_IDX] = ((1 - (g_LowtonMark / 12325936)) * 6198913.16789523) / (g_LowtonMark * (0.046 * g_Wallet->m_vec_markmin[m_IDX]));
									}
								else
									{
									g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmax[m_IDX];

									g_Wallet->m_vec_score[m_IDX] = (g_LowtonMark * g_LowtonMark);
									}
								}
							else
								{
								if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
									{
									g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmin[m_IDX];

									g_Wallet->m_vec_score[m_IDX] = ((1 - (g_LowtonMark / 12325936)) * 6198913.16789523) / (g_LowtonMark * (0.046 * g_Wallet->m_vec_markmin[m_IDX]));
									}
								else
									{
									g_Wallet->m_vec_maxvote[m_IDX] = COMPARE_THRESH; //lean towards COMPARE_THRESH minimum mark

									time_t f_CurrentTime;
									time(&f_CurrentTime);

									while(m_IDX >= g_Wallet->m_vec_targetbreach.size())
										{
										g_Wallet->m_vec_targetbreach.push_back(f_CurrentTime);
										}

									g_Wallet->m_vec_score[m_IDX] = (float)g_Wallet->m_vec_targetbreach[m_IDX] - f_CurrentTime;
									}
								}
							}

						g_Wallet->m_vec_score[m_IDX] = ag_Get_current_Target_Mark(g_Type); //possibly invert

						//convert scoremax to maxvote
						if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
							{
							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX];
							}
						else
							{
							time_t f_CurrentTime;
							time(&f_CurrentTime);

							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_targetbreach[m_IDX] - f_CurrentTime;
							}
						}break;

					case ecoin_BlockType::ecoin_Block_Target_SCP:
						{
						//convert ADMAX to score and maxvote
						g_Wallet->m_vec_score[m_IDX] = (float)(g_BicycleContainer[0]->m_ADMAX / g_classLMap->m_ADMAX) * ((float)ECOIN_SCP_REWARD_FACT5000 * (float)ECOIN_SCP_REWARD_FACT5000) /*ECN_OPER_REWARD*/ + (float)ECOIN_SCP_INSTANT_BONUS;
						g_Wallet->m_vec_maxvote[m_IDX] = (float)((float)ECOIN_SCP_REWARD_FACT5000 * (float)ECOIN_SCP_REWARD_FACT5000) /*ECN_OPER_REWARD*/ + (float)ECOIN_SCP_INSTANT_BONUS;
						//...mebbe add debug message
						}break;

					case ecoin_BlockType::ecoin_Block_TimedPledge:
						{
						//convert scoremax to maxvote
						if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
							{
							time_t f_CurrentTime;
							time(&f_CurrentTime);

							g_Wallet->m_vec_score[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX] - (float)f_CurrentTime;

							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX];
							}
						else
							{
							time_t f_CurrentTime;
							time(&f_CurrentTime);

							g_Wallet->m_vec_score[m_IDX] = (float)f_CurrentTime - (float)g_Wallet->m_vec_startbreach[m_IDX];

							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_targetbreach[m_IDX];
							}
						}break;

					case ecoin_BlockType::ecoin_Block_MaxPledge:
						{
						//update share integer voting score
						g_Wallet->m_vec_score[m_IDX] = 0.0f;

						//convert scoremax to maxvote
						if(g_Wallet->m_vec_maxpledge[m_IDX] > 0)
							{
							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_maxpledge[m_IDX];
							}
						else
							{
#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif //add debug message
							}
						}break;

					case ecoin_BlockType::ecoin_Block_MaxTimedPledge:
						{
						//convert scoremax to maxvote
						if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
							{ //score zero
							g_Wallet->m_vec_score[m_IDX] = 0.0f;

							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX];
							}
						else
							{
							time_t f_CurrentTime;
							time(&f_CurrentTime);

							g_Wallet->m_vec_score[m_IDX] = (float)f_CurrentTime - (float)g_Wallet->m_vec_startbreach[m_IDX];

							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_targetbreach[m_IDX];
							}
						}break;
					}

				ag_FreshOn<float>(g_Wallet->m_vec_bckred, m_IDX, f_Lowton_Cade->m_bckred);
				ag_FreshOn<float>(g_Wallet->m_vec_bckgreen, m_IDX, f_Lowton_Cade->m_bckgreen);
				ag_FreshOn<float>(g_Wallet->m_vec_bckblue, m_IDX, f_Lowton_Cade->m_bckblue);

				ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)g_LowtonMark);
				ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, g_BicycleContainer[0]->m_ADMAX);
				ag_FreshOn<float>(g_Wallet->m_vec_difficulty, m_IDX, COMPARE_THRESH);
				ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
				ag_Freshanon<float>(g_Wallet->m_vec_price, m_IDX, g_CurrentSharePrice);
				ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_BicycleContainer[0]->m_ADMAX);

				ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, -1);

				char* g_sharevalue[25];

				for(int f_Count = 0; f_Count < 25; f_Count++)
					{
					g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
					}

				sprintf(g_sharevalue[0], "%i", (int)g_LowtonMark);
				sprintf(g_sharevalue[1], "%f", g_LowtonMark);
				sprintf(g_sharevalue[2], "%i", 1);
				sprintf(g_sharevalue[3], "%i", 3);
				sprintf(g_sharevalue[4], "%i", g_JobID);
				sprintf(g_sharevalue[5], "%i", g_Wallet->m_vec_jobboardid[m_IDX]);
				sprintf(g_sharevalue[6], "%i", g_Wallet->m_vec_eslid[m_IDX]);
				sprintf(g_sharevalue[7], "%i", g_Wallet->m_vec_targetid[m_IDX]);
				sprintf(g_sharevalue[8], "%s", g_TypeName.c_str());
				sprintf(g_sharevalue[9], "%f", COMPARE_THRESH);
				sprintf(g_sharevalue[10], "%f", g_Wallet->m_vec_score[m_IDX]);
				sprintf(g_sharevalue[11], "%f", g_Wallet->m_vec_maxvote[m_IDX]);
				sprintf(g_sharevalue[12], "%s", f_Share_OutputHash.c_str());
				sprintf(g_sharevalue[13], "%s", g_Wallet->m_vec_blockledger[m_IDX].c_str());
				sprintf(g_sharevalue[14], "%s", g_Wallet->GetAdr().c_str());
				sprintf(g_sharevalue[15], "%f", g_Wallet->m_vec_bckred[m_IDX]);
				sprintf(g_sharevalue[16], "%f", g_Wallet->m_vec_bckgreen[m_IDX]);
				sprintf(g_sharevalue[17], "%f", g_Wallet->m_vec_bckblue[m_IDX]);
				sprintf(g_sharevalue[18], "%i", g_CurrentComID);
				sprintf(g_sharevalue[19], "%f", g_Wallet->m_Reward);
				sprintf(g_sharevalue[20], "%f", 0.0f);
				sprintf(g_sharevalue[21], "%f", 0.0f);
				sprintf(g_sharevalue[22], "%f", ECN_TX_FEE);
				sprintf(g_sharevalue[23], "%f", g_CurrentSharePrice);
				sprintf(g_sharevalue[24], "%i", g_BlockType);

				//ECN::Hesh...Sending BlockHesh.
				char* shlquery = ag_ClearChar(1000);

				sprintf(shlquery, "SELECT id FROM share WHERE shareledger = '%s'", f_Share_OutputHash.c_str());

				g_SafeL[0]->acSelectCommand(shlquery, 2, false);

				delete shlquery;

				int f_ShareLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShareLCount = 0;
					}
				else
					{
					f_ShareLCount = g_Schedular[0]->acEntrySize();
					}

				//ECN::Stat::: f_ShareLCount
				if(f_ShareLCount == 0)
					{
					int f_ShareUniqueID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 25, 2, false);

					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_sharevalue[f_Count]);
						}

					for(int f_Int = 0; f_Int < f_Lowton_Cade->m_adIndex.size(); f_Int++)
						{
						shared_ptr<CubeBicycle> f_Bike = f_Lowton_Cade->vec_Bicycle[f_Lowton_Cade->m_adIndex[f_Int]];

						char* g_cubevalue[55];

						for(int f_Count = 0; f_Count < 55; f_Count++)
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
					
						::sprintf(g_cubevalue[48], "%i", g_Wallet->m_vec_blockid[m_IDX]);
						::sprintf(g_cubevalue[49], "%i", f_ShareUniqueID);
						::sprintf(g_cubevalue[50], "%i", g_JobID);
						::sprintf(g_cubevalue[51], "%i", f_Int);
						::sprintf(g_cubevalue[52], "%i", 1);	//FIXME ADD L-TARGETID
						::sprintf(g_cubevalue[53], "%s", "jsd8932o39aeru");
						::sprintf(g_cubevalue[54], "%f", COMPARE_THRESH);

						int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, 55, 2, false);

						for(int f_Count = 0; f_Count < 55; f_Count++)
							{
							free(g_cubevalue[f_Count]);
							}
						}

					//ECN::Stat::: f_shareuniqueID
					g_ShareID = f_ShareUniqueID;

					char* balancequery = ag_ClearChar(1000);
					::sprintf(balancequery, "Call acTopUpPeerBalanceAdvance(%i, %i)", g_ShareID, g_JobID);
					g_SafeL[0]->acSelectCommand(balancequery, 2, false);
					delete balancequery;

					Cag->ag_addGenesisTracking(f_ShareUniqueID, g_BlockType);
				
					std::shared_ptr<ShareContainerExt> f_PG = Cag->ag_SelectPeerGraphExt(g_JobID, 0, g_ShareID, g_CurrentShareOffset, g_PEER);

					g_CurrentShareOffset = f_PG->m_espo_ShareOffset;
					g_CurrentShareOffsetMAX = f_PG->m_espo_SharesOnPeerCount;
					g_PEER = f_PG->m_espo_Peer;
					g_PEERCNT = f_PG->m_espo_PeerCount;
					g_PEERMAX = f_PG->m_espo_PeerCount;

					g_TargetedHesh = f_Lowton_Cade;

					g_TargetedHesh->ac_IsOK();

					//ECN::f_adCount
					g_BicycleContainer[0]->m_ADMAX = g_TargetedHesh->m_adIndex.size();
					g_BicycleContainer[0]->m_ADHIGH = g_TargetedHesh->m_adIndex.size();
					g_BicycleContainer[0]->m_ADLOW = g_TargetedHesh->m_adIndex.size();

					g_RenderHesh = true;

					//ECN::Lowton Share Submitted.
					ag_StatusLive(f_ref_CurrentPath, "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_SHARE), g_ShareID, g_PEERCNT);
					f_Ack->m_ECN = 0.0f;
					f_Ack->m_Reward = g_Wallet->m_Reward;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = g_Wallet->GetAdr();
					f_Ack->m_PathOwner = g_Wallet->GetAdr();
					g_Ackent.push_back(f_Ack);

					m_LowtonTicket = -1;

					g_LowtonMark = FLT_MAX;

					time(&g_storagetime);
					g_storagetime += LOWTON_STORAGE;

					if(g_BlockType != ecoin_BlockType::ecoin_Block_MaxPledge)
						{
						g_Wallet->acSet_IDX(m_IDX);
						//...
						g_Wallet->acTestForBlock(g_BlockType, f_Res, false);
						}
					}
				else
					{
					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_sharevalue[f_Count]);
						}

					g_Found_Msg = 9;
					g_Found_Text = "Duplicate Share Found...";

					f_Result = false;
					}

				mutex_swap.unlock();
				m_DB_AccessLock.unlock();

				time(&g_storagetime);
				g_storagetime += LOWTON_STORAGE;

				g_LowtonMark = FLT_MAX;
				}
			}
		}

	//exit affinity thread
	m_DB_AccessLock.lock();
	m_cnt_DIV_Thread--;
	m_DB_AccessLock.unlock();
}

void Sample3DSceneRenderer::RestoreTargetedBuffers(void)
{
	if(g_TargetedHesh)
		{
		g_TargetedHesh->ac_IsOK();

		m_DB_AccessLock.lock();

		for(int f_Int = 0; f_Int < g_TargetedHesh->vec_Bicycle.size(); f_Int++)
			{
			shared_ptr<CubeBicycle> f_Bicycle = g_TargetedHesh->vec_Bicycle[f_Int];

			if((f_Int < Cube::g_BicycleContainer[0]->m_ADMAX) && (f_Int < g_TargetedHesh->m_ADMAX))
				{
				f_Bicycle->m_vertexBuffer = Cube::g_BicycleContainer[0]->vec_Key[f_Int]->m_Link->m_vertexBuffer;
				f_Bicycle->m_indexBuffer = Cube::g_BicycleContainer[0]->vec_Key[f_Int]->m_Link->m_indexBuffer;
				
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

		m_DB_AccessLock.unlock();
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