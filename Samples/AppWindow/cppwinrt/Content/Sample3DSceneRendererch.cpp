#include "pch.h"
#include "Sample3DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"
#include "Include\Cube.h"

using namespace ecoin;

using namespace DirectX;
using namespace Windows::Foundation;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_degreesPerSecond(45),
	m_indexCount(0),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	//###==- Seed the random number generator -==###//
	ULONGLONG f_ULongLong = GetTickCount64();
	srand(f_ULongLong);
}

// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
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

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
	static const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		Rotate(radians);
	}
}

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
	// Prepare to pass the updated model matrix to the shader
	float f_RAD = (((float)rand() / 32767) * (float)10);
	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationX(f_RAD)));
	f_RAD = (((float)rand() / 32767) * (float)10);
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
	//f_RAD = (((float)rand() / 32767) * (float)10);
	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationZ(radians)));
}

void Sample3DSceneRenderer::StartTracking()
{
	m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
	}
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render()
{
	Cube::CubeBicycle* f_Bistream = new Cube::CubeBicycle();
	Cube::CubeKEY* f_KEY = new Cube::CubeKEY();

	if(Cube::g_BicycleContainer[0].vec_Bicycle.size() > 0)
		{
		int f_Finger = rand() % Cube::g_BicycleContainer[0].vec_Bicycle.size();
		f_Bistream = Cube::g_BicycleContainer[0].vec_Bicycle[f_Finger];
		f_KEY->m_Link = f_Bistream;
		}
	else
		{
		return;
		}

	// Loading is asynchronous. Only draw geometry after it's loaded.
	if(!m_loadingComplete)
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

#if 1
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
#else
	// Each vertex is one instance of the VertexPositionColor struct.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	context->IASetVertexBuffers(
		0,
		1,
		f_Bistream->m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
	);

	context->IASetIndexBuffer(
		f_Bistream->m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
	);
#endif

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

concurrency::task<void> AVD(void)
{
	concurrency::task<void> f_Task;
	return f_Task;
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
{
	// Load shaders asynchronously.
	auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");

	// After the vertex shader file is loaded, create the shader and input layout.
	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_vertexShader
				)
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
				&fileData[0],
				fileData.size(),
				&m_inputLayout
				)
			);
	});

	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pixelShader
				)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&constantBufferDesc,
				nullptr,
				&m_constantBuffer
				)
			);
	});

	// Once both shaders are loaded, create the mesh.
	auto createCubeTask = (createPSTask && createVSTask).then([this] () {

		float f_FingerA[8];
		float f_FingerB[8];
		float f_FingerC[8];
		int f_Top = rand() % 5;

		f_FingerA[0] = (rand() % ((rand() % 5) + f_Top - f_Top - 13)) - (((rand() + f_Top % 5) + (rand() % 5)) - f_Top - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[1] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5 + f_Top - f_Top)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[2] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5 + f_Top) + (rand() % 5)) - 6.5 + f_Top);
		f_FingerA[3] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[4] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[5] = (rand() % ((rand() % 5 + f_Top - f_Top) - 13)) - (((rand() + f_Top - f_Top % 5) + (rand() % 5)) - f_Top - 6.5);
		f_FingerA[6] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - f_Top - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[7] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - f_Top - 6.5);

		f_FingerB[0] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() - f_Top % 5) + (rand() % 5)) - 6.5 - f_Top);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[1] = (rand() + f_Top % ((rand() % 5 - f_Top) - 13)) - (((rand() % 5 + f_Top) + (rand() % 5)) - 6.5 - f_Top);
		f_FingerB[2] = (rand() % ((rand() % 5 + f_Top) - 13 - f_Top - f_Top)) - (((rand() % 5 - f_Top + f_Top) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[3] = (rand() + f_Top % ((rand() % 5 + f_Top) - 13)) - (((rand() % 5 - f_Top) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[4] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[5] = (rand() + f_Top % ((rand() % 5) - 13 - f_Top + f_Top)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_FingerB[6] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5 - f_Top);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[7] = (rand() % ((rand() + f_Top % 5 - f_Top) - 13 - f_Top)) - (((rand() % 5 - f_Top) + (rand() % 5)) - 6.5);

		f_FingerC[0] = (rand() % ((rand() % 5 + f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 / f_Top)) - 6.5 - f_Top);
		f_FingerC[1] = (rand() / f_Top - f_Top % ((rand() % 5 + f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - f_Top - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerC[2] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - 6.5);
		f_FingerC[3] = (rand() + f_Top - f_Top % ((rand() - f_Top % 5 + f_Top) - 13 / f_Top)) - (((rand() % 5) + (rand() % 5 - f_Top)) - 6.5 - f_Top);
		f_FingerC[4] = (rand() % ((rand() % 5) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - 6.5);
		f_FingerC[5] = (rand() + f_Top % ((rand() - f_Top % 5) - 13)) - (((rand() % 5 - f_Top) + (rand() % 5 - f_Top / f_Top)) - 6.5 - f_Top);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerC[6] = (rand() % ((rand() % 5 + f_Top) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerC[7] = (rand() % ((rand() % 5 - f_Top) - f_Top - 13)) - (((rand() / f_Top % 5 - f_Top) + (rand() / f_Top % 5)) - 6.5);

		f_FingerA[0] = 1;
		f_FingerB[0] = 1;
		f_FingerC[0] = 1;
		f_FingerA[1] = 1;
		f_FingerB[1] = 1;
		f_FingerC[1] = 1;
		f_FingerA[2] = 1;
		f_FingerB[2] = 1;
		f_FingerC[2] = 1;
		f_FingerA[3] = 1;
		f_FingerB[3] = 1;
		

#if 0
		// Load mesh vertices. Each vertex has a position and a color.
		static const VertexPositionColor cubeVertices[] = 
		{
			{XMFLOAT3(-0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8])},
			{XMFLOAT3(-0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8])},
			{XMFLOAT3(-0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8])},
			{XMFLOAT3(-0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8])},
			{XMFLOAT3( 0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8])},
			{XMFLOAT3( 0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8])},
			{XMFLOAT3( 0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8])},
			{XMFLOAT3( 0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8])},
		};
#else
// Load mesh vertices. Each vertex has a position and a color.
static const VertexPositionColor cubeVertices[] =
{
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
	{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
	{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
	{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
	{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
};
#endif



		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&vertexBufferDesc,
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
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&m_indexBuffer
				)
			);
	});

	// Once the cube is loaded, the object is ready to be rendered.
	createCubeTask.then([this] () {
		m_loadingComplete = true;
	});

	for (int f_Count = 0; f_Count < 150; f_Count++)
		{
		Cube::CubeBicycle* f_Bicycle = new Cube::CubeBicycle();

		Cube::CubeKEY* f_KEY = new Cube::CubeKEY();

		f_KEY->m_Link = f_Bicycle;

		//AVD().then([this, f_KEY](){
		CreateResources(f_KEY, m_deviceResources);
		//});

		Cube::g_BicycleContainer[0].vec_Bicycle.push_back(f_Bicycle);
		}
}

void Sample3DSceneRenderer::CreateResources(Cube::CubeKEY* f_KEY, std::shared_ptr<DX::DeviceResources> f_deviceResources)
{
		float f_FingerA[8];
		float f_FingerB[8];
		float f_FingerC[8];
		int f_Top = rand() % 5;

		f_FingerA[0] = (rand() % ((rand() % 5) + f_Top - f_Top - 13)) - (((rand() + f_Top % 5) + (rand() % 5)) - f_Top - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[1] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5 + f_Top - f_Top)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[2] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5 + f_Top) + (rand() % 5)) - 6.5 + f_Top);
		f_FingerA[3] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[4] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[5] = (rand() % ((rand() % 5 + f_Top - f_Top) - 13)) - (((rand() + f_Top - f_Top % 5) + (rand() % 5)) - f_Top - 6.5);
		f_FingerA[6] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - f_Top - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerA[7] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - f_Top - 6.5);

		f_FingerB[0] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() - f_Top % 5) + (rand() % 5)) - 6.5 - f_Top);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[1] = (rand() + f_Top % ((rand() % 5 - f_Top) - 13)) - (((rand() % 5 + f_Top) + (rand() % 5)) - 6.5 - f_Top);
		f_FingerB[2] = (rand() % ((rand() % 5 + f_Top) - 13 - f_Top - f_Top)) - (((rand() % 5 - f_Top + f_Top) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[3] = (rand() + f_Top % ((rand() % 5 + f_Top) - 13)) - (((rand() % 5 - f_Top) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[4] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[5] = (rand() + f_Top % ((rand() % 5) - 13 - f_Top + f_Top)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_FingerB[6] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5 - f_Top);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerB[7] = (rand() % ((rand() + f_Top % 5 - f_Top) - 13 - f_Top)) - (((rand() % 5 - f_Top) + (rand() % 5)) - 6.5);

		f_FingerC[0] = (rand() % ((rand() % 5 + f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 / f_Top)) - 6.5 - f_Top);
		f_FingerC[1] = (rand() / f_Top - f_Top % ((rand() % 5 + f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - f_Top - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerC[2] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - 6.5);
		f_FingerC[3] = (rand() + f_Top - f_Top % ((rand() - f_Top % 5 + f_Top) - 13 / f_Top)) - (((rand() % 5) + (rand() % 5 - f_Top)) - 6.5 - f_Top);
		f_FingerC[4] = (rand() % ((rand() % 5) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - 6.5);
		f_FingerC[5] = (rand() + f_Top % ((rand() - f_Top % 5) - 13)) - (((rand() % 5 - f_Top) + (rand() % 5 - f_Top / f_Top)) - 6.5 - f_Top);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerC[6] = (rand() % ((rand() % 5 + f_Top) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
		f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
		f_FingerC[7] = (rand() % ((rand() % 5 - f_Top) - f_Top - 13)) - (((rand() / f_Top % 5 - f_Top) + (rand() / f_Top % 5)) - 6.5);

#if 1
		f_FingerA[0] = 1;
		f_FingerB[0] = 1;
		f_FingerC[0] = 1;
		f_FingerA[1] = 1;
		f_FingerB[1] = 1;
		f_FingerC[1] = 1;
		f_FingerA[2] = 1;
		f_FingerB[2] = 1;
		f_FingerC[2] = 1;
		f_FingerA[3] = 1;
		f_FingerB[3] = 1;
		f_FingerC[3] = 1;
		f_FingerA[4] = 1;
		f_FingerB[4] = 1;
		f_FingerC[4] = 1;
		f_FingerA[5] = 1;
		f_FingerB[5] = 1;
		f_FingerC[5] = 1;
		f_FingerA[6] = 1;
		f_FingerB[6] = 1;
		f_FingerC[6] = 1;
		f_FingerA[7] = 1;
		f_FingerB[7] = 1;
		f_FingerC[7] = 1;
#endif

#if 1
		// Load mesh vertices. Each vertex has a position and a color.
		static const VertexPositionColor cubeVertices[] =
		{
			{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
			{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
			{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
			{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
			{ XMFLOAT3(0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
			{ XMFLOAT3(0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
			{ XMFLOAT3(0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
			{ XMFLOAT3(0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
		};
#else
		// Load mesh vertices. Each vertex has a position and a color.
		static const VertexPositionColor cubeVertices[] =
		{
			{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
			{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
			{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
			{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
		};
#endif

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			f_deviceResources->GetD3DDevice()->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&f_KEY->m_Link->m_vertexBuffer
			)
		);

		// Load mesh indices. Each trio of indices represents
		// a triangle to be rendered on the screen.
		// For example: 0,2,1 means that the vertices with indexes
		// 0, 2 and 1 from the vertex buffer compose the 
		// first triangle of this mesh.
		static const unsigned short cubeIndices[] =
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

		f_KEY->m_Link->m_indexCount = ARRAYSIZE(cubeIndices);

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			f_deviceResources->GetD3DDevice()->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&f_KEY->m_Link->m_indexBuffer
			)
		);
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
}


void Sample3DSceneRenderer::CreateBufferResources(Cube::CubeKEY* f_KEY)
{
	float f_FingerA[8];
	float f_FingerB[8];
	float f_FingerC[8];
	int f_Top = rand() % 5;

	f_FingerA[0] = (rand() % ((rand() % 5) + f_Top - f_Top - 13)) - (((rand() + f_Top % 5) + (rand() % 5)) - f_Top - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerA[1] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5 + f_Top - f_Top)) - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerA[2] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5 + f_Top) + (rand() % 5)) - 6.5 + f_Top);
	f_FingerA[3] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerA[4] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerA[5] = (rand() % ((rand() % 5 + f_Top - f_Top) - 13)) - (((rand() + f_Top - f_Top % 5) + (rand() % 5)) - f_Top - 6.5);
	f_FingerA[6] = (rand() + f_Top % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - f_Top - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerA[7] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - f_Top - 6.5);

	f_FingerB[0] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() - f_Top % 5) + (rand() % 5)) - 6.5 - f_Top);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerB[1] = (rand() + f_Top % ((rand() % 5 - f_Top) - 13)) - (((rand() % 5 + f_Top) + (rand() % 5)) - 6.5 - f_Top);
	f_FingerB[2] = (rand() % ((rand() % 5 + f_Top) - 13 - f_Top - f_Top)) - (((rand() % 5 - f_Top + f_Top) + (rand() % 5)) - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerB[3] = (rand() + f_Top % ((rand() % 5 + f_Top) - 13)) - (((rand() % 5 - f_Top) + (rand() % 5)) - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerB[4] = (rand() % ((rand() % 5) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerB[5] = (rand() + f_Top % ((rand() % 5) - 13 - f_Top + f_Top)) - (((rand() % 5) + (rand() % 5)) - 6.5);
	f_FingerB[6] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5 - f_Top);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerB[7] = (rand() % ((rand() + f_Top % 5 - f_Top) - 13 - f_Top)) - (((rand() % 5 - f_Top) + (rand() % 5)) - 6.5);

	f_FingerC[0] = (rand() % ((rand() % 5 + f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 / f_Top)) - 6.5 - f_Top);
	f_FingerC[1] = (rand() / f_Top - f_Top % ((rand() % 5 + f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - f_Top - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerC[2] = (rand() % ((rand() % 5 - f_Top) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - 6.5);
	f_FingerC[3] = (rand() + f_Top - f_Top % ((rand() - f_Top % 5 + f_Top) - 13 / f_Top)) - (((rand() % 5) + (rand() % 5 - f_Top)) - 6.5 - f_Top);
	f_FingerC[4] = (rand() % ((rand() % 5) - 13)) - (((rand() + f_Top % 5) + (rand() % 5 + f_Top)) - 6.5);
	f_FingerC[5] = (rand() + f_Top % ((rand() - f_Top % 5) - 13)) - (((rand() % 5 - f_Top) + (rand() % 5 - f_Top / f_Top)) - 6.5 - f_Top);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerC[6] = (rand() % ((rand() % 5 + f_Top) - 13)) - (((rand() % 5) + (rand() % 5)) - 6.5);
	f_Top = (((rand() % 5 - f_Top + f_Top) + (rand() + f_Top % 5 + f_Top)) - f_Top - 6.5);
	f_FingerC[7] = (rand() % ((rand() % 5 - f_Top) - f_Top - 13)) - (((rand() / f_Top % 5 - f_Top) + (rand() / f_Top % 5)) - 6.5);

	f_FingerA[0] = 1;
	f_FingerB[0] = 1;
	f_FingerC[0] = 1;
	f_FingerA[1] = 1;
	f_FingerB[1] = 1;
	f_FingerC[1] = 1;
	f_FingerA[2] = 1;
	f_FingerB[2] = 1;
	f_FingerC[2] = 1;
	f_FingerA[3] = 1;
	f_FingerB[3] = 1;

#if 0
	// Load mesh vertices. Each vertex has a position and a color.
	static const VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
		{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
		{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
		{ XMFLOAT3(-0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(0.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
		{ XMFLOAT3(0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
		{ XMFLOAT3(0.5f * f_FingerA[rand() % 8], -0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 0.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
		{ XMFLOAT3(0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8], -0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 0.0f * f_FingerC[rand() % 8]) },
		{ XMFLOAT3(0.5f * f_FingerA[rand() % 8],  0.5f * f_FingerB[rand() % 8],  0.5f * f_FingerC[rand() % 8]), XMFLOAT3(1.0f * f_FingerA[rand() % 8], 1.0f * f_FingerB[rand() % 8], 1.0f * f_FingerC[rand() % 8]) },
	};
#else
	// Load mesh vertices. Each vertex has a position and a color.
	static const VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
	};
#endif

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&f_KEY->m_Link->m_vertexBuffer
		)
	);

	// Load mesh indices. Each trio of indices represents
	// a triangle to be rendered on the screen.
	// For example: 0,2,1 means that the vertices with indexes
	// 0, 2 and 1 from the vertex buffer compose the 
	// first triangle of this mesh.
#if 0
	static const unsigned short cubeIndices[] =
	{
		f_KEY->m_Link->vec_Indices[0].m_A,f_KEY->m_Link->vec_Indices[0].m_B,f_KEY->m_Link->vec_Indices[0].m_C, // -x
		f_KEY->m_Link->vec_Indices[1].m_A,f_KEY->m_Link->vec_Indices[1].m_B,f_KEY->m_Link->vec_Indices[1].m_C,

		f_KEY->m_Link->vec_Indices[2].m_A,f_KEY->m_Link->vec_Indices[2].m_B,f_KEY->m_Link->vec_Indices[2].m_C, // +x
		f_KEY->m_Link->vec_Indices[3].m_A,f_KEY->m_Link->vec_Indices[3].m_B,f_KEY->m_Link->vec_Indices[3].m_C,

		f_KEY->m_Link->vec_Indices[4].m_A,f_KEY->m_Link->vec_Indices[4].m_B,f_KEY->m_Link->vec_Indices[4].m_C, // -y
		f_KEY->m_Link->vec_Indices[5].m_A,f_KEY->m_Link->vec_Indices[5].m_B,f_KEY->m_Link->vec_Indices[5].m_C,

		f_KEY->m_Link->vec_Indices[6].m_A,f_KEY->m_Link->vec_Indices[6].m_B,f_KEY->m_Link->vec_Indices[6].m_C, // +y
		f_KEY->m_Link->vec_Indices[7].m_A,f_KEY->m_Link->vec_Indices[7].m_B,f_KEY->m_Link->vec_Indices[7].m_C,

		f_KEY->m_Link->vec_Indices[8].m_A,f_KEY->m_Link->vec_Indices[8].m_B,f_KEY->m_Link->vec_Indices[8].m_C, // -z
		f_KEY->m_Link->vec_Indices[9].m_A,f_KEY->m_Link->vec_Indices[9].m_B,f_KEY->m_Link->vec_Indices[9].m_C,

		f_KEY->m_Link->vec_Indices[10].m_A,f_KEY->m_Link->vec_Indices[10].m_B,f_KEY->m_Link->vec_Indices[10].m_C, // +z
		f_KEY->m_Link->vec_Indices[11].m_A,f_KEY->m_Link->vec_Indices[11].m_B,f_KEY->m_Link->vec_Indices[11].m_C,
	};
#endif

	static const unsigned short cubeIndices[] =
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

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&f_KEY->m_Link->m_indexBuffer
		)
	);
}