/*

Sample3DSceneRenderer - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#pragma once

#include <dxgi1_4.h>
#include <d3d11_3.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>

#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"
#include "ShaderStructures.h"

#include "Include\Cube.h"

extern DirectX::XMMATRIX g_MatrixTP;

namespace ecoin
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample3DSceneRenderer
		{
		public:
			Sample3DSceneRenderer(std::shared_ptr<DX::DeviceResources> deviceResources);
			~Sample3DSceneRenderer();

			std::future<void> CreateDeviceDependentResources(void);
			
			void RestoreTargetedBuffers(void);
			void CreateWindowSizeDependentResources();
			void ReleaseDeviceDependentResources();

			void Update(void);

			void Render(int f_Index);
			void Render_Qcom(void);
			void Render_COM(float f_X, float f_Y, time_t f_Trial_Length);
			void Render_Curve(void);

			void StartTracking();
			void TrackingUpdate(float positionX);
			void StopTracking();
			bool IsTracking() { return m_tracking; }

			void acGen_GenHesh(void);
			void acSaveCompletePublish_GenHesh_Upper(void);
			void acSaveCompletePublish_GenHesh_Upper_Reflection(void);

			void acCreateAdmaxDependentResources(void);

			int m_cnt_SCP_Thread;
			int m_cnt_DIV_Thread;

			int m_LowtonTicket;

			std::shared_mutex m_DB_AccessLock;

			int m_IDX;

			int LOWTON_STORAGE;

		private:
			void Rotate(float radians);

			// Cached pointer to device resources.
			std::shared_ptr<DX::DeviceResources> m_deviceResources;

			// Direct3D resources for cube geometry.
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_QCGinputLayout;
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_COMinputLayout;
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_curveinputLayout;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_COMvertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_COMindexBuffer;
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_QCGvertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_QCGpixelShader;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_QCGconstantBuffer;
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_COMvertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_COMpixelShader;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_COMconstantBuffer;
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_curvevertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_curvepixelShader;
			Microsoft::WRL::ComPtr<ID3D11Buffer>		m_curveconstantBuffer;

			// System resources for cube geometry.
			ModelViewProjectionConstantBuffer	m_constantBufferData;
			ModelViewProjectionConstantBuffer	m_QCGconstantBufferData;
			ModelViewProjectionConstantBuffer	m_COMconstantBufferData;
			ModelViewProjectionConstantBuffer	m_curveconstantBufferData;

			// Variables used with the rendering loop.
			bool	m_loadingComplete;
			bool	m_COMloadingComplete;
			bool	m_curveloadingComplete;
			bool	m_tracking;
			float	m_degreesPerSecond;

			unsigned int	m_indexCount;
		};
}

