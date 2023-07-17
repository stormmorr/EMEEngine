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

#include "SecondaryAppWindowPageDX.g.h"
#include "ecoinMain.h"
#include "Code/Cube/qcom.h"

extern int g_IDX;

class qtx_Transaction
{
public:
	qtx_Transaction()
		{
		acClear();
		}

	qtx_Transaction(int f_Index);

	~qtx_Transaction()
		{
		acClear();
		}

	void acClear(void)
		{
		m_status = 0;
		m_txid = 0;
		m_amt = 0.0f;
		m_confirmation = 0;
		}

	int m_status;
	int m_txid;
	float m_amt;
	int m_confirmation;
};

extern winrt::Windows::UI::Xaml::Controls::Button g_insertinsertbutton;

extern winrt::Windows::UI::Xaml::Controls::SwapChainPanel g_swapChainPanel;
extern winrt::Windows::Foundation::IAsyncAction g_inputLoopWorker;

namespace winrt::SDKTemplate::implementation
{
    struct SecondaryAppWindowPageDX : SecondaryAppWindowPageDXT<SecondaryAppWindowPageDX>
    {
	public:
        SecondaryAppWindowPageDX();

		void acClick(std::string f_ButtonName);

        void OnVisibilityChanged(winrt::CoreWindow sender, winrt::VisibilityChangedEventArgs args);

		// DisplayInformation event handlers.
		void OnDpiChanged(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args);
		void OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args);
		void OnDisplayContentsInvalidated(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args);

		void OnSCP_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e);
		void OnSCP_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e);
		void OnSCP_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e);

		void OnSwap_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void OnSwap_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void OnSwap_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);

		// Other event handlers.
		void OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel sender, IInspectable args);
		void OnSwapChainPanelSizeChanged(IInspectable sender, Windows::UI::Xaml::SizeChangedEventArgs e);

		void OnSaveOBJ(std::string f_Filename);
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
		void OnWalletClick(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnHeshtextClick(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickWithDraw(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickVoteUp(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickNextShare(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPrevShare(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPeer(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPeerMinus(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickMilliPeer(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickMilliPeerMinus(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickLookAt(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void acLoadShare(int f_LShare = 0, int f_ServLay = 0);
		void acProcessAckMessage(std::shared_ptr<Ackent> f_Ack);
		void OnFillTargets(void);
		void OnClickShowTransaction(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBack(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickNext(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickSend(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickNewAddress(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickNextos(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickPreviousBlock(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickWinningShare(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void onClickOwnPeer(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickInsertInsert(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnKeyDownInsertSearch(IInspectable sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs e);
		void OnSelectInsertTypeCombo(IInspectable sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs e);

		fire_and_forget OnClickBuyComponent(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		fire_and_forget OnClickOpenPredator(void);

		void OnPredatorWindowClosed(Windows::UI::WindowManagement::AppWindow const& sender, IInspectable const&);
		void OnClosed(winrt::CoreWindow sender, winrt::Windows::UI::Core::CoreWindowEventArgs e);

		void DisplayInterfaceCom(std::shared_ptr<Cube::Qcom> f_Com);

		void OnRightClickWindow(IInspectable sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs e);

		void OnClickIncludeComponent(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickQcom(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);

		void StartFrameLoop(void);
		void StopFrameLoop();

		float m_DPI;
		float m_logicalWidth;
		float m_logicalHeight;

		bool m_Frame_ThreadON;

		winrt::Windows::UI::Xaml::DispatcherTimer m_FrameTimer;

		bool m_FirstAll;

		winrt::Windows::UI::Xaml::Controls::Frame appWindowFrame{};

		  ////////////////////////////////
		 // qtx
		//...
		bool qtx_Send(std::string f_A, std::string f_B, float f_Amt);

		  ////////////////////////////////
		 // qtx display control
		//...
		void OpenTXD(std::string f_Recipient = "", float f_Amt = -1.0);

		void StartTXD(void);
		void clearTXDisplay(void);
		void qtx_Update(void);
		bool qtx_Results(void);
		void CloseTXD(void);
		void acTXReal(void);
		void acRefreshJob(void);
		void acRefreshJobVar(void);

		void OnClickFloatTXD(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickSuccessClose(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickCloseTXD(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickTXDpreview(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenWalletPrint(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickRefreshWalletPrint(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void acRefreshWalletPrint(void);
		void OnClickCloseWalletPrint(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenTXD(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShowWithdraw(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShowDeposit(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy5GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy10GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy20GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy50GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickBuy100GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);

		std::future<bool> OnBuyGBP(std::string f_ProductID, int f_IntAmt);
		std::future<bool> acFullfill(::winrt::hstring f_ProdId, ::winrt::guid f_TransactionId, bool f_QuickFullFill = false);

		void OnClickWithDrawCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA1PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickeslcodeClose(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickeslcodeCheck(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickeslcodeStart(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShareShop(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickShopSearch(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopsearchprev(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopsearchnext(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopownproducts(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnHover(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnRefreshShop(void);
		void OnClickOpenProductA1(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA2(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA3(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA4(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA5(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductA6(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB1(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB2(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB3(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB4(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB5(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickOpenProductB6(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickCurrentSkip(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickCurrentKeep(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA2PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA3PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA4PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA5PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopA6PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB1PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB2PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB3PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB4PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB5PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickshopB6PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisions(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionUp(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionRight(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionLeft(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionDown(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionIn(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void OnClickDecisionOut(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void acBuild_ExcomPackaging(void);
		void OnClickComFunction(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void Frame_OnCount(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable e);
		void OnClickSaveComplete(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnValueChangedSaveCompletePublishSlider(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
		void OnClickCloseSaveComplete(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e);
		void acRefreshDecisionsPanel(void);
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
		void acRefreshSelectionInfo(void);
		void OnRefreshEslCodeStack(void);
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
		void OnLoadPledgeStack(void);
		void OnClickPledgeClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPledgesOn(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickPreviousJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnClickNextJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnJobVarInvalidateSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		void OnClickTypePrefixHelp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnGotFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void OnLostFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

		std::shared_ptr<eshop> m_ShareShop;

		bool m_Frame_OnCount;
};

}

namespace winrt::SDKTemplate::factory_implementation
{
    struct SecondaryAppWindowPageDX : SecondaryAppWindowPageDXT<SecondaryAppWindowPageDX, implementation::SecondaryAppWindowPageDX>
    {
    };
}

extern int g_EventID;
extern int g_ShareCount;