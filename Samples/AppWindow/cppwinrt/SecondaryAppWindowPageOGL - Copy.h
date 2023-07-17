//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

#include "OpenGLES.h"
#include "SecondaryAppWindowPageOGL.g.h"

#include "Code/Cube/VoxelGrid.h"
#include "Include/Cube.h"
#include "Code/Cube/qcom.h"

#include "ecoinMain.h"

namespace Quantum_Angel
{

class Q_Terrain_Insert
	{
	public:
		Q_Terrain_Insert()
			{
			m_X = 0.0f;
			m_Y = 0.0f;
			m_Z = 0.0f;
			}

		~Q_Terrain_Insert()
			{
			m_X = 0.0f;
			m_Y = 0.0f;
			m_Z = 0.0f;
			}

		float m_X;
		float m_Y;
		float m_Z;
	};

class Q_TerrainDef
	{
	public:
		Q_TerrainDef()
			{
			m_vec_Insert.clear();
			}

		~Q_TerrainDef()
			{
			m_vec_Insert.clear();
			}

		float m_MaxGroundHeight;
		std::vector<Q_Terrain_Insert*> m_vec_Insert;
	};

class Q_Building_Insert
	{
	public:
		Q_Building_Insert()
			{

			}

		~Q_Building_Insert()
			{

			}

		uint m_Type;
		std::vector<Cube::Building*> m_Building;

		float m_X;
		float m_Y;
		float m_Z;
	};

class Q_BuildingDef
	{
	public:
		Q_BuildingDef()
			{

			}

		~Q_BuildingDef()
			{

			}

		float m_MaxGroundHeight;
		std::vector<Q_Building_Insert*> m_vec_Insert;
	};

class Q_Trigger_Insert
	{
	public:
		Q_Trigger_Insert()
			{

			}

		~Q_Trigger_Insert()
			{

			}

		float m_X;
		float m_Y;
		float m_Z;
	};

class Q_TriggerDef
	{
	public:
		Q_TriggerDef()
			{

			}

		~Q_TriggerDef()
			{

			}

		std::vector<Q_Trigger_Insert*> m_vec_Insert;
	};

class Q_Spawn_Insert
	{
	public:
		Q_Spawn_Insert()
			{

			}

		~Q_Spawn_Insert()
			{

			}

		float m_TimerMax;
		int m_Count;
		int m_CountMax;

		int m_Type;

		int m_BDataID;
		int m_CDataID;

		Cube::BiVector m_Dir;

		float m_X;
		float m_Y;
		float m_Z;

		float m_XRotate;
		float m_YRotate;
		float m_ZRotate;
	};

class Q_SpawnDef
	{
	public:
		Q_SpawnDef()
			{

			}

		~Q_SpawnDef()
			{

			}

		std::vector<Q_Spawn_Insert*> m_vec_Insert;
		std::vector<Q_Trigger_Insert*> m_vec_Trigger;
	};

class Q_Mission
	{
	public:
		Q_Mission()
			{

			}

		~Q_Mission()
			{

			}

		std::vector<Q_TerrainDef*> m_vec_TERRAIN;
		std::vector<Q_BuildingDef*> m_vec_BUILD;
		std::vector<Q_SpawnDef*> m_vec_SPAWN;
		float ecn_Value;
		float egold_Value;
	};

};

extern winrt::Windows::UI::Xaml::Controls::Button g_insertinsertbutton_ogl;
extern winrt::Windows::UI::Xaml::Controls::SwapChainPanel g_swapChainPanel_ogl;
extern winrt::Windows::UI::Xaml::Controls::TextBox g_ConsoleTextBox;

namespace winrt::SDKTemplate::implementation
{
    struct SecondaryAppWindowPageOGL : SecondaryAppWindowPageOGLT<SecondaryAppWindowPageOGL>
    {
	public:
		SecondaryAppWindowPageOGL();

		//QUANTUM PORTION

		void CreateRenderSurface();
		void DestroyRenderSurface();
		void RecoverFromLostDevice();

		void OnHover(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void acClick(std::string f_ButtonName);

		void OnVisibilityChanged(winrt::Windows::UI::Core::CoreWindow sender, winrt::Windows::UI::Core::VisibilityChangedEventArgs args);

		//QUANTUM PORTION

#if 0   // DisplayInformation event handlers.
		void OnDpiChanged(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args);
		void OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args);
		void OnDisplayContentsInvalidated(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args);
#endif

		void OnSCP_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e);
		void OnSCP_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e);
		void OnSCP_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e);

		void OnSwap_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void OnSwap_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void OnSwap_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);

		// Other event handlers.
		void OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel sender, IInspectable args);
		void OnSwapChainPanelSizeChanged(IInspectable sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs e);

		std::future<bool> acSaveFileBuffer(std::string f_Buffer);

		bool ConfigureSimulatorAsync(bool f_Bool);
		std::future<bool> ConfigSim(bool f_Bool);

		std::shared_ptr<DX::DeviceResources> m_DeviceResources;
		std::unique_ptr<ecoin::ecoinMain> m_main;

		winrt::Windows::Graphics::Display::DisplayOrientations m_nativeOrientation;
		winrt::Windows::Graphics::Display::DisplayOrientations m_currentOrientation;

		int ConvertDipsToPixels(float dips);
		float ConvertPixelsToDips(int pixels);
		DXGI_MODE_ROTATION ComputeDisplayRotation();

#if 0
		void SaveInternalState(Windows::Foundation::Collections::IPropertySet state);
		void LoadInternalState(Windows::Foundation::Collections::IPropertySet state);
#endif

		bool acLowLatentencyInput(void);

		bool m_windowVisible;
		bool m_ComboSelectedCom;

		int m_ComPackageShareID;
		float m_ComPackagePrice;

		std::vector<int> m_inserttypecombo;
		std::thread* m_thread;

		int m_IDX;
		int m_SelectionSaveIndex;
		int LOWTON_STORAGE;

		void OnClickOpenAppBar(void);
		void OnWalletClick(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnHeshtextClick(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickWithDraw(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickVoteUp(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickNextShare(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPrevShare(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPeer(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPeerMinus(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickMilliPeer(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickMilliPeerMinus(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickLookAt(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShowTransaction(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBack(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickNext(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickSend(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickNewAddress(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickNextos(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPreviousBlock(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickWinningShare(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void onClickOwnPeer(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickInsertInsert(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnKeyDownInsertSearch(IInspectable sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs e);
		void OnSelectInsertTypeCombo(IInspectable sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs e);

		void acLoadShare(int f_LShare = 0, int f_ServLay = 0);
		void acProcessAck(std::shared_ptr<Ackent> f_Ack);
		void OnFillTargets(void);

		fire_and_forget OnClickBuyComponent(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		fire_and_forget OnClickOpenPredator(void);

		void OnPredatorWindowClosed(Windows::UI::WindowManagement::AppWindow const& sender, IInspectable const&);
		void OnClosed(winrt::CoreWindow sender, winrt::Windows::UI::Core::CoreWindowEventArgs e);
		void DisplayInterfaceCom(std::shared_ptr<Cube::Qcom> f_Com);
		void OnRightClickWindow(IInspectable sender, winrt::Windows::UI::Xaml::Input::RightTappedRoutedEventArgs e);
		void OnClickIncludeComponent(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickQcom(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);

		float m_DPI;
		float m_logicalWidth;
		float m_logicalHeight;

		bool m_FirstAll;

		winrt::Windows::UI::Xaml::Controls::Frame appWindowFrame{};

		  ////////////////////////////////
		 // qtx display control
		//...
		bool qtx_Send(std::string f_A, std::string f_B, float f_Amt);
		void OpenTXD(std::string f_Recipient = "", float f_Amt = -1.0);
		void StartTXD(void);
		void clearTXDisplay(void);
		void qtx_Update(void);
		bool qtx_Results(void);
		void CloseTXD(void);
		void acTXReal(void);

		void acRefreshJob(void);
		void acRefreshJobVar(void);

		void Frame_OnCount(void);

		void OnClickFloatTXD(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickSuccessClose(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickCloseTXD(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickTXDpreview(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenWalletPrint(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickRefreshWalletPrint(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void acRefreshWalletPrint(void);
		void OnClickCloseWalletPrint(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenTXD(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShowWithdraw(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShowDeposit(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy5GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy10GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy20GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy50GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy100GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);

		std::future<bool> OnBuyGBP(std::string f_ProductID, int f_IntAmt);
		std::future<bool> acFullfill(::winrt::hstring f_ProdId, ::winrt::guid f_TransactionId, bool f_QuickFullFill = false);

		void OnClickWithDrawCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA1PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickeslcodeClose(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickeslcodeCheck(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickeslcodeStart(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShareShop(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShopSearch(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopsearchprev(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopsearchnext(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopownproducts(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA1(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA2(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA3(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA4(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA5(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA6(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB1(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB2(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB3(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB4(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB5(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB6(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickCurrentSkip(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickCurrentKeep(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA2PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA3PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA4PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA5PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA6PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB1PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB2PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB3PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB4PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB5PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB6PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisions(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionUp(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionRight(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionLeft(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionDown(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionIn(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionOut(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickComFunction(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickSaveComplete(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnValueChangedSaveCompletePublishSlider(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
		void OnClickCloseSaveComplete(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickSelectStack(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectSelect(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickAction(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectRight(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectLeft(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectIn(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectOut(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectMode(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectAdditive(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectPrevious(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectNext(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectRecall(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickDecisionsTop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickdecisionsLayerZero(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickdecisionsLastDecisionCom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPreviousDecision(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickNextDecision(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickDecision1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickDecisionCom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickDecisionClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickDecisionsUndo(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickdecisionsApply(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSelectSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickApplyNumber(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickIncreaseCompressionHigh(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnValueChangedSaveCompressionSlider(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
		void OnClickPlaceVector(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCancelClosebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPlaceInNewGrid(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickExecuteNew(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickIncreaseSCPThreadsHigh(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnEventExecuteImmediatly(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickClosePauseMinimizebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPlaceInCurrentGrid(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPlaceInstall(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPayBuyOnce(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPayBuyAmount(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPayJoinMembership(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPayBuyBundle(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPayZeroNow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickIncludeProfitEngRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ONClickIncludeLimitedRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickIncludeMembershipRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickIncludeGroupRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPutToBackbutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickIgnoreClosebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickLogOut(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickProductsBought(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickStorePolicy(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClicktandc(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickStopAll(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPledgeSynchronize(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPledgeClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPledgesOn(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPreviousJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickNextJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnJobVarInvalidateSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		void OnClickTypePrefixHelp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

		void acInterfaceLoop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable e);

		void acRefreshSelectionInfo(void);
		void OnRefreshEslCodeStack(void);
		void acRefreshDecisionsPanel(void);
		void OnLoadPledgeStack(void);
		void OnRefreshShop(void);

		void acBuild_ExcomPackaging(void);

		void acClose_Mouse(void);
		void acPrep_Mouse(void);
		void acKeyLog(void);
		void acKeyLogPK(void);

		bool GetKeyState(int f_Key);

		void acLoadBrief(void);

        OpenGLES mOpenGLES;

        EGLSurface mRenderSurface;     // This surface is associated with a swapChainPanel on the page

        winrt::Windows::Foundation::IAsyncAction mRenderLoopWorker;
		winrt::Windows::Foundation::IAsyncAction mEngineLoopWorker;
		winrt::Windows::Foundation::IAsyncAction mInterfaceLoopWorker;

		void OnSwapKeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		void OnSwapKeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);

		void OnRefreshCharSelectListBox(void);

		void Show_MissionPanel(void);

		void acUpdateInsert(void);
		void acUpdateTerrainInsert(void);

		void acClearVoxels(void);
		void acUpdateBoost(void);

		winrt::hstring m_Name;
		winrt::Windows::UI::Xaml::DispatcherTimer m_InterfaceTimer;

		void onClickStartMission1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMissionButton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickInsertType(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickInsertTypeMin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickLogin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickRegister(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMissionCreate(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickViewMission(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickFillZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMoveZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNegatedZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMaxZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionIncMinus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionIncPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionMinusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionPlusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionMinusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionPlusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionMinusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlacePositionPlusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAngleIncMinus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAngleIncPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAngleMinusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAnglePlusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAngleMinusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAnglePlusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAngleMinusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceAnglePlusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickInsert(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlay(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickNextMission(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPrevMission(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickEdit(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSpawncharacterInc(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickSpawncharacterMin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickDiscovery(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickLoad(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickTeamMin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickTeamPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickBoostDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickBoostUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickBoostLeft(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickBoostRight(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickMenu(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickStartSim(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickDownLevel(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickUpLevel(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPauseSim(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickUpdate(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickCloseLoadingText(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceScaleIncPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceScaleIncMinus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickIncplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickIncminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickUpdateMode(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickUpdateCommand(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClickPlaceonPlayer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void onClicknameGroupSelect(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickQO(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickQAO(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickEnterQcom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickWindow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void OnReleaseWindow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void OnMovedWindow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);

		void OnClickOpenLogin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void acFillLogin(void);
		void acSaveLogin(std::string f_Username, std::string f_Password);
		void OnClickLoadUsualLogin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

		void OnClickEXTRA(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickBITOLYL(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

		void StartRenderLoop(bool f_Really = false);
		void StartInterfaceLoop();
		void StartEditorRenderLoop(bool f_Really = false);
		void StartEngineLoop(bool f_Really = false);

		void StopRenderLoop();
		void StopInterfaceLoop();
		void StopEngineLoop();
};

}

namespace winrt::SDKTemplate::factory_implementation
{
    struct SecondaryAppWindowPageOGL : SecondaryAppWindowPageOGLT<SecondaryAppWindowPageOGL, implementation::SecondaryAppWindowPageOGL>
    {
    };
}

extern int g_EventID;
extern int g_ShareCount;