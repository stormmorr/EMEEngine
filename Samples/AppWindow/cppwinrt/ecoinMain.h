/*

ecoinMain.h - osirem.com
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

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace ecoin
{
	class ecoinMain : public DX::IDeviceNotify
	{
	public:
		ecoinMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~ecoinMain();

		void CreateWindowSizeDependentResources();

		void StartTracking() { m_sceneRenderer->StartTracking(); }
		void StopTracking() { m_sceneRenderer->StopTracking(); }
		void TrackingUpdate(float positionX) { m_pointerLocationX = positionX; }

		bool IsTracking() { return m_sceneRenderer->IsTracking(); }

		void StartRenderLoop();
		void StopRenderLoop();

		void RenderLoop(void);

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		int m_IDX;

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Rendering loop timer.
		DX::StepTimer m_timer;

		bool m_Rendering;
		bool m_Scan;
		float m_pointerLocationX;

		std::thread* m_vec_threadObj;
	};
}