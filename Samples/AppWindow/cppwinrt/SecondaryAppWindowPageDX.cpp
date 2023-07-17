/*

DX.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "SecondaryAppWindowPageDX.h"
#include "SecondaryAppWindowPageDX.g.cpp"
#include "SecondaryAppWindowPagePredator.h"

#include <Code\CLS\Target.h>

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"

using namespace std;

int g_EventID = 0;
int g_ShareCount = 0;

std::vector<qtx_Transaction*> g_vec_qtx_Transaction;
std::vector<qtx_Transaction*> g_vec_qtx_TransactionNew;

bool txd_on = false;
int g_TXD_Position = 0;
bool g_TXD_Preview = false;
int g_IDX = 0;

winrt::Windows::UI::Xaml::Controls::SwapChainPanel g_swapChainPanel({ nullptr });
winrt::Windows::Foundation::IAsyncAction g_inputLoopWorker;
winrt::Windows::Foundation::IAsyncAction m_inputLoopWorker;
winrt::Windows::UI::Core::CoreIndependentInputSource m_coreInput({ nullptr });
winrt::Windows::UI::Xaml::Controls::Button g_insertinsertbutton({ nullptr });

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
}

qtx_Transaction::qtx_Transaction(int f_Index)
{
	m_txid = atoi(g_Schedular[0]->acEntry(f_Index)[0].c_str());
	m_status = atoi(g_Schedular[0]->acEntry(f_Index)[1].c_str());
	m_confirmation = atoi(g_Schedular[0]->acEntry(f_Index)[2].c_str());
	m_amt = atof(g_Schedular[0]->acEntry(f_Index)[3].c_str());
}

namespace winrt::SDKTemplate::implementation
{
	SecondaryAppWindowPageDX::SecondaryAppWindowPageDX() :
		m_windowVisible(true),
		m_DPI(96.f),
		m_logicalWidth(800.f),
		m_logicalHeight(600.f),
		m_nativeOrientation(winrt::Windows::Graphics::Display::DisplayOrientations::None),
		m_currentOrientation(winrt::Windows::Graphics::Display::DisplayOrientations::None),
		m_FirstAll(true)
	{
		InitializeComponent();

		m_IDX = g_IDX;

		g_IDX++;

		LOWTON_STORAGE = 0;

		m_Frame_OnCount = false;

		m_FirstAll = false;
		m_ComboSelectedCom = false;

		m_ComPackageShareID = 0;

		g_insertinsertbutton = insertinsertbutton();

		std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPageDX::SecondaryAppWindowPageDX";

		// Register event handlers for page lifecycle.
		CoreWindow window = CoreWindow::GetForCurrentThread();

		window.Closed({ this, &SecondaryAppWindowPageDX::OnClosed });
		window.VisibilityChanged({ this, &SecondaryAppWindowPageDX::OnVisibilityChanged });

		winrt::Windows::Graphics::Display::DisplayInformation currentDisplayInformation{ winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView() };

		currentDisplayInformation.DpiChanged({ this, &SecondaryAppWindowPageDX::OnDpiChanged });
		currentDisplayInformation.OrientationChanged({ this, &SecondaryAppWindowPageDX::OnOrientationChanged });

		winrt::Windows::Graphics::Display::DisplayInformation::DisplayContentsInvalidated({ this, &SecondaryAppWindowPageDX::OnDisplayContentsInvalidated });

		swapChainPanel().CompositionScaleChanged({ this, &SecondaryAppWindowPageDX::OnCompositionScaleChanged });
		swapChainPanel().SizeChanged({ this, &SecondaryAppWindowPageDX::OnSwapChainPanelSizeChanged });

		m_DPI = currentDisplayInformation.LogicalDpi();

		m_logicalWidth = window.Bounds().Width;
		m_logicalHeight = window.Bounds().Height;

		m_nativeOrientation = currentDisplayInformation.NativeOrientation();
		m_currentOrientation = currentDisplayInformation.CurrentOrientation();

		DXGI_MODE_ROTATION rotation = ComputeDisplayRotation();

		ag_StatusLive(f_ref_CurrentPath, "g_BicycleContainer");
		g_BicycleContainer.push_back(std::make_shared_reflect<BicycleContainer>());

		ag_StatusLive(f_ref_CurrentPath, "m_DeviceResources");
		m_DeviceResources = ::std::make_shared_reflect<DX::DeviceResources>();
		m_DeviceResources->SetSwapChainPanel(swapChainPanel());

		g_swapChainPanel = swapChainPanel();

 		m_main = ::std::unique_ptr<ecoinMain>(new ecoinMain(m_DeviceResources));
		m_main->StartRenderLoop();

		m_main->m_IDX = m_IDX;
		m_main->m_sceneRenderer->m_IDX = m_IDX;

		ag_StatusLive(f_ref_CurrentPath, "m_ShareShop");
		m_ShareShop = ::std::make_shared_reflect<eshop>(m_IDX);

#if 0
		bool h_OK = acLowLatentencyInput();
#endif

#if 0
		//make main protocol extension node for extending switch statements
		ag_StatusLive(f_ref_CurrentPath, "g_MainNode");
		g_MainNode = std::make_shared_reflect<BiProtocolExNode>();
		g_MainNode->m_PEXMAPIDX = -5;

		ag_StatusLive(f_ref_CurrentPath, "g_ExcomPexMain");
		g_ExcomPexMain = std::make_shared_reflect<BiProtocolExNode>();
		g_ExcomPexMain->m_PEXMAPIDX = -3;
		g_ExcomPexMain->m_NodeParent = g_MainNode;

		g_MainNode->m_vec_NodeChildren.push_back(g_ExcomPexMain);

		ag_StatusLive(f_ref_CurrentPath, "g_InstallMain");
		g_InstallMain = std::make_shared_reflect<BiProtocolExNode>();
		g_ExcomPexMain->m_PEXMAPIDX = -3;
		g_ExcomPexMain->m_NodeParent = g_MainNode;

		g_MainNode->m_vec_NodeChildren.push_back(g_ExcomPexMain);
#endif

		g_Tab[0] = "";

#if 0
		OnFillTargets();
#endif

#ifdef ECOIN_STORE_SIM
		bool f_Hok = ConfigureSimulatorAsync(false);

		if(f_Hok == false)
			{
#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif
			}
#endif

		 //////////////////////////////
		// ecoinMain Initialisation //
		g_Schedular[0]->m_MainMutex.lock();

		char* f_eventquery = ag_ClearChar(150);
		sprintf(f_eventquery, "SELECT id, dated FROM event ORDER BY dated DESC LIMIT 1");
		g_SafeL[0]->acSelectCommand(f_eventquery, false, false, true);
		delete f_eventquery;

		int f_eventLCount = 0;

		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_eventLCount = 0;
			}
		else
			{
			f_eventLCount = g_Schedular[0]->acEntrySize();
			}

		if(f_eventLCount > 0)
			{
			g_EventID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
			}

		g_JobID = g_Wallet->acGet_JobID(m_IDX, 0, true);

		char* f_idquery2 = ag_ClearChar(150);
		sprintf(f_idquery2, "SELECT id, owner, score FROM share WHERE jobid = %i", g_JobID);
		std::shared_ptr<Cube::ShareContainerExt> f_ShareContainer = Cag->ag_SelectPeerGraphExt(g_JobID, 0, 0, g_CurrentShareOffset, g_PEER, true);

		int f_ShareCounting = f_ShareContainer->m_espo_TotalShares;
		g_ShareCount = f_ShareCounting;

		g_Schedular[0]->m_MainMutex.unlock();

		  //////////////////////
		 // Initial
		// Balance Check
		if(g_WalletOpen == true)
			{
			double f_BalanceIndollars = g_Wallet->GetBalance(true, 1);
			double f_Balance = f_BalanceIndollars / (double)g_Wallet->m_Price;

			double f_CPSBalanceInpounds = g_Wallet->GetBalanceCPS(true, 1);

			 //////////////////
			// Init Timers	//
			time(&g_Storetime);
			time(&g_StoretimeSEC);

			char* rewardquery = ag_ClearChar(1000);
			sprintf(rewardquery, "SELECT id, reward FROM reward ORDER BY id DESC LIMIT 1");
			g_SafeL[1]->acSelectCommand(rewardquery, 2, false);
			delete rewardquery;

			int f_RewardCount = 0;

			if(g_Schedular[1]->acEntry(0)[0].at(0) == '0')
				{
				f_RewardCount = 0;
				}
			else
				{
				f_RewardCount = g_Schedular[1]->acEntrySize();
				}

			if(f_RewardCount == 1)
				{
				g_Wallet->m_Reward = atof(g_Schedular[1]->acEntry(0)[1].c_str());
				g_Wallet->m_RewardID = atoi(g_Schedular[1]->acEntry(0)[0].c_str());
				}

			g_JobID = g_Wallet->acGet_JobID(m_IDX, 1);

			  //////////////////////
			 // Share
			// balance
			char* f_Char1 = ag_ClearChar(255);

			::sprintf(f_Char1, "%.5f ECN", (float)f_Balance);
			std::string f_String2 = f_Char1;
			ecoinpersecondBlock().Text(StrUsingStr(f_String2));

			delete f_Char1;

			char* f_Char2 = ag_ClearChar(255);

			::sprintf(f_Char2, "%.8f", (float)f_BalanceIndollars);
			std::string f_String4 = f_Char2;

			walletindollarstextBlock().Text(StrUsingStr(f_String4));

			delete f_Char2;

			char* f_Char3 = ag_ClearChar(255);

			::sprintf(f_Char3, "%.4f", (float)g_Wallet->m_Price);
			std::string f_String9 = f_Char3;

			ecoinvalueBlock().Text(StrUsingStr(f_String9));

			delete f_Char3;

			char* f_Char4 = ag_ClearChar(255);

			::sprintf(f_Char4, "%.4f", (float)f_CPSBalanceInpounds);
			std::string f_String10 = f_Char4;

			walletindollarstextBlock_CPS().Text(StrUsingStr(f_String10));

			myaddressTextBlock().Text(StrUsingStr("Wallet Address " + g_Wallet->GetAdr()));

			if(f_ShareContainer->m_espo_PeerCount > 0)
				{
				int f_OwnPeerCount = f_ShareContainer->m_espo_TotalSharesOwnPeer;
				int f_OnPeerCount = f_ShareContainer->m_espo_SharesOnPeerCount;

				char numbuf2[100];

				_itoa(f_ShareContainer->m_espo_PeerCount, numbuf2, 10);
				std::string f_interim = numbuf2;
								
				allpeertextBlock().Text(StrUsingStr(f_interim + " peers"));

				char numbuf3[100];
				_itoa(f_OwnPeerCount, numbuf3, 10);
				std::string f_interim2 = numbuf3;
								
				ownsharestextBlock().Text(StrUsingStr(f_interim2 + " own"));

				int f_ShareCountingEL = f_ShareContainer->m_espo_TotalShares;

				char numbuf4[100];
				_itoa(f_ShareCountingEL, numbuf4, 10);
				std::string f_interim3 = numbuf4;
								
				alltotaltextBlock().Text(StrUsingStr(f_interim3 + " on block"));
							
				char numbuf9[100];
				_itoa(f_OnPeerCount, numbuf9, 10);
				std::string f_interim8 = numbuf9;
								
				owntotaltextBlock().Text(StrUsingStr("share count " + f_interim8));

				g_ShareCount = f_ShareCountingEL;
				}
			else
				{
				int f_OwnPeerIndex = 0;
				int f_OnPeerIndex = 0;
				int f_OwnTotal = 0;
				int f_OwnPeerCount = 0;
				int f_OnPeerCount = 0;

				char numbuf2[100];

				_itoa(f_ShareContainer->m_espo_PeerCount, numbuf2, 10);
				std::string f_interim = numbuf2;
								
				allpeertextBlock().Text(StrUsingStr(f_interim + " peers"));

				char numbuf3[100];
				_itoa(f_OwnPeerCount, numbuf3, 10);
				std::string f_interim2 = numbuf3;
								
				ownsharestextBlock().Text(StrUsingStr(f_interim2 + " own"));

				char numbuf4[100];
				_itoa(f_ShareCounting, numbuf4, 10);
				std::string f_interim3 = numbuf4;
								
				alltotaltextBlock().Text(StrUsingStr(f_interim3 + " on block"));
					
				char numbuf9[100];
				_itoa(f_OnPeerCount, numbuf9, 10);
				std::string f_interim8 = numbuf9;
								
				owntotaltextBlock().Text(StrUsingStr("share count " + f_interim8));

				g_ShareCount = f_ShareCounting;
				}
			}

		  /////////////////
		 //	TAPE RECORD //
		/////////////////
		Cube::seedrand(2);

#if 0
		Cube::TapeOn();

		Cube::TapeOff();
#endif

		g_Wallet->m_my_Active_pledge = false;
		g_Wallet->m_my_pledge_shareID = 0;
		g_Wallet->m_pledge_Total = 0.0f;

		//Start Frame_OnCount Dispatcher Timer Thread Every [1000]ms
		StartFrameLoop();
	}

	bool SecondaryAppWindowPageDX::acLowLatentencyInput(void)
	{
		// Create a task to register for independent input and begin processing input messages.
		Windows::System::Threading::WorkItemHandler workItemHandler([this](Windows::Foundation::IAsyncAction const& /* action */)
			{
			// The CoreIndependentInputSource will raise pointer events for the specified device types on whichever thread it's created on.
			m_coreInput = swapChainPanel().CreateCoreIndependentInputSource(
					Windows::UI::Core::CoreInputDeviceTypes::Mouse/* |
					Windows::UI::Core::CoreInputDeviceTypes::Touch |
					Windows::UI::Core::CoreInputDeviceTypes::Pen*/);

			// Register for pointer events, which will be raised on the background thread.
			m_coreInput.PointerPressed({ this, &SecondaryAppWindowPageDX::OnSCP_PointerPressed });
			m_coreInput.PointerMoved({ this, &SecondaryAppWindowPageDX::OnSCP_PointerMoved });
			m_coreInput.PointerReleased({ this, &SecondaryAppWindowPageDX::OnSCP_PointerReleased });

			// Begin processing input messages as they're delivered.
			m_coreInput.Dispatcher().ProcessEvents(winrt::Windows::UI::Core::CoreProcessEventsOption::ProcessUntilQuit);
			});

		// Run task on a dedicated high priority background thread.
		m_inputLoopWorker = Windows::System::Threading::ThreadPool::RunAsync(workItemHandler, Windows::System::Threading::WorkItemPriority::High, Windows::System::Threading::WorkItemOptions::TimeSliced);

		return true;
	}

	void SecondaryAppWindowPageDX::acClick(std::string f_CurrentFunction)
	{
		if(m_FirstAll == false)
			{
			ag_Click(f_CurrentFunction);

			Qpo->Sound_Play_Default(Medias->S_Click, 0.6f);
			}
	}

	void SecondaryAppWindowPageDX::OnHover(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		if(m_FirstAll == false)
			{
			Qpo->Sound_Play_Default(Medias->S_Hover, 0.6f);
			}
	}

	double atodi(std::string f_String)
	{
		return 0.0 + (double)atoi(f_String.c_str());
	}

    int SecondaryAppWindowPageDX::ConvertDipsToPixels(float dips)
    {
        return int(dips * m_DPI / 96.f + 0.5f);
    }

    float SecondaryAppWindowPageDX::ConvertPixelsToDips(int pixels)
    {
        return (float(pixels) * 96.f / m_DPI);
    }

    DXGI_MODE_ROTATION SecondaryAppWindowPageDX::ComputeDisplayRotation()
		{
        DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

        switch (m_nativeOrientation)
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

	void SecondaryAppWindowPageDX::OnDpiChanged(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args)
	{
		// Note: The value for LogicalDpi retrieved here may not match the effective DPI of the app
		// if it is being scaled for high resolution devices. Once the DPI is set on DeviceResources,
		// you should always retrieve it using the GetDpi method.
		// See DeviceResources.cpp for more details.

		m_DeviceResources->SetDpi(sender.LogicalDpi());

		m_main->CreateWindowSizeDependentResources();
	}

	void SecondaryAppWindowPageDX::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args)
	{
		m_DeviceResources->SetCurrentOrientation(sender.CurrentOrientation());

		m_main->CreateWindowSizeDependentResources();
	}

	void SecondaryAppWindowPageDX::OnDisplayContentsInvalidated(winrt::Windows::Graphics::Display::DisplayInformation sender, IInspectable args)
	{
		m_DeviceResources->ValidateDevice();

		m_main->CreateWindowSizeDependentResources();
	}

	void SecondaryAppWindowPageDX::OnVisibilityChanged(winrt::CoreWindow sender, winrt::VisibilityChangedEventArgs args)
	{
		m_DeviceResources->CreateWindowSizeDependentResources();

		m_main->CreateWindowSizeDependentResources();

		g_RenderHesh = true;
	}

	void SecondaryAppWindowPageDX::OnClickOpenAppBar(void)
	{
		if(qcomappBar().IsOpen() == true)
			{
			qcomappBar().IsOpen(false);
			}
		else
			{
			qcomappBar().IsOpen(true);

			::g_QcomManager->m_Open = true;
			}
	}

	void SecondaryAppWindowPageDX::OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel sender, IInspectable args)
	{
		m_DeviceResources->SetCompositionScale(sender.CompositionScaleX(), sender.CompositionScaleY());

		m_main->CreateWindowSizeDependentResources();

		g_RenderHesh = true;
	}

	void SecondaryAppWindowPageDX::OnSwapChainPanelSizeChanged(IInspectable sender, Windows::UI::Xaml::SizeChangedEventArgs e)
	{
		m_DeviceResources->SetLogicalSize(e.NewSize());

		m_main->CreateWindowSizeDependentResources();

		g_RenderHesh = true;
	}

	auto CreateComboBoxItem = [](hstring const& name, IInspectable const& tag = nullptr)
	{
		Windows::UI::Xaml::Controls::ComboBoxItem item;
		item.Content(box_value(name));
		item.Tag(tag);
		return item;
	};

	void SecondaryAppWindowPageDX::OnKeyDownInsertSearch(IInspectable sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs e)
	{
		std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::TextBox>().Name());

		acClick(f_KeyName);

		if(e.Key() == Windows::System::VirtualKey::Enter)
			{
			inserttypecomboBox().Items().Clear();

			std::string f_StringText = to_string(insertsearchtextBox().Text());

			  ////////////////
			 // targets
			//
			char* targetquery;

			targetquery = (char*)malloc(sizeof(char) * 1024);

			std::string f_NameStringText = "%" + f_StringText + "%";

			::sprintf(targetquery, "SELECT name, id, dated FROM com WHERE birthcomid <= 0 AND name LIKE '%s' ORDER BY dated DESC LIMIT %i", f_NameStringText.c_str(), ECOIN_SEARCH_ROW_MAX);

			mutex_qcomdb.lock();

			g_SafeL[2]->acSelectCommand(targetquery, false, false);

			if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
				{
				int f_targetCount = g_Schedular[2]->acEntrySize();

				inserttypecomboBox().Items().Append(CreateComboBoxItem(L"NEW Own COM"));

				m_inserttypecombo.clear();
				m_inserttypecombo.push_back(-1);

				for(int f_TGTID = 0; f_TGTID < f_targetCount; f_TGTID++)
					{
					inserttypecomboBox().Items().Append(CreateComboBoxItem(StrUsingStr(g_Schedular[2]->acEntry(f_TGTID)[0])));
					m_inserttypecombo.push_back(atoi(g_Schedular[2]->acEntry(f_TGTID)[1].c_str()));
					}

				if(f_targetCount >= 1)
					{
					inserttypecomboBox().SelectedIndex(1);
					}
				}

			mutex_qcomdb.unlock();
			}
	}

	void SecondaryAppWindowPageDX::OnSelectInsertTypeCombo(IInspectable sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs e)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::OnSelectInsertTypeCombo";

		std::string f_ComboName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::ComboBox>().Name());

		acClick(f_ComboName);

		winrt::Windows::UI::Xaml::Controls::ComboBoxItem f_Item = inserttypecomboBox().SelectedItem().as< winrt::Windows::UI::Xaml::Controls::ComboBoxItem>();

		int f_Selected = inserttypecomboBox().SelectedIndex();

		int f_SelectedID = m_inserttypecombo[f_Selected];

		m_ComboSelectedCom = true;

		  ///////////////////
	     // combo reload
	    //
		if(f_SelectedID != -1)
			{
			ag_StatusLive(f_ref_CurrentPath, "g_PreCom");
			g_PreCom = ::std::make_shared_reflect<Qcom>(f_SelectedID, false);

			g_PreComBool = true;
			g_PreComLock = false;
			g_PreComInclude = false;
			g_PreComBoughtIN = 0;

			char* checksinglecomquery = ag_ClearChar(1024);

			::sprintf(checksinglecomquery, "SELECT id, price, dated FROM share WHERE comid = %i ORDER BY dated DESC LIMIT 1", f_SelectedID);

			g_SafeL[0]->acSelectCommand(checksinglecomquery, false, false);

			delete checksinglecomquery;

			if(g_Schedular[0]->acEntry(0)[0].at(0) != '0')
				{
				int f_SingleComPackageCount = g_Schedular[0]->acEntrySize();

				if(f_SingleComPackageCount > 0)
					{
					m_ComPackageShareID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
					m_ComPackagePrice = atof(g_Schedular[0]->acEntry(0)[1].c_str());
					g_PreCom->m_PackageShareID = m_ComPackageShareID;
					}
				else
					{
					char* checkcontainercomquery = ag_ClearChar(1024);

					::sprintf(checkcontainercomquery, "SELECT id, price, dated FROM share WHERE comid = %i ORDER BY dated DESC LIMIT 1", g_PreCom->m_parentcomid);

					g_SafeL[0]->acSelectCommand(checkcontainercomquery, false, false);

					delete checkcontainercomquery;

					int f_ComPackageCount = g_Schedular[0]->acEntrySize();

					if(f_ComPackageCount > 0)
						{
						m_ComPackageShareID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
						m_ComPackagePrice = atof(g_Schedular[0]->acEntry(0)[1].c_str());
						g_PreCom->m_PackageShareID = m_ComPackageShareID;
						}
					else
						{
						m_ComPackageShareID = 0;
						m_ComPackagePrice = 0.0f;
						g_PreCom->m_PackageShareID = 0;
						}
					}
				}
			else
				{
				char* checkcontainercomquery = ag_ClearChar(1024);

				::sprintf(checkcontainercomquery, "SELECT id, price, dated FROM share WHERE comid = %i ORDER BY dated DESC LIMIT 1", g_PreCom->m_parentcomid);

				g_SafeL[0]->acSelectCommand(checkcontainercomquery, false, false);

				delete checkcontainercomquery;

				int f_ComPackageCount = g_Schedular[0]->acEntrySize();

				if(f_ComPackageCount > 0)
					{
					m_ComPackageShareID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
					m_ComPackagePrice = atof(g_Schedular[0]->acEntry(0)[1].c_str());
					g_PreCom->m_PackageShareID = m_ComPackageShareID;
					}
				else
					{
					m_ComPackageShareID = 0;
					m_ComPackagePrice = 0.0f;
					g_PreCom->m_PackageShareID = 0;
					}
				}

			insertnametextBox().Text(StrUsingStr(g_PreCom->m_name));

			char* f_Char = ag_ClearChar(255);

			::sprintf(f_Char, "%.2f", g_PreCom->m_Cost);

			insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

			delete f_Char;

			g_PreComBoughtIN = 1;
			g_PreComInclude = false;

			if(m_ComPackageShareID > 0)
				{
				if(m_ComPackagePrice > 0.0f) //win conditions price available so lock main textbox
					{
					g_PreCom->m_genScript = gqcom_INLfromComID(g_PreCom->m_ID);

					DisplayInterfaceCom(g_PreCom);

					if(g_Wallet->acGet_assetContractbyID(m_ComPackageShareID, g_PreCom->m_Cost) == true)
						{
						g_PreComLock = true;	//win
						g_PreComBoughtIN = 1;
						g_PreComInclude = false;

						Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

						insertinsertbutton().BorderBrush(myBrush);

						insertscripttextBox().IsReadOnly(false);
						}
					else
						{
						g_PreComInclude = false;  //reset win
						g_PreComLock = false;
						g_PreComBool = false;
						g_PreComBoughtIN = 0;

						Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0));

						insertinsertbutton().BorderBrush(myBrush);

						insertscripttextBox().IsReadOnly(true);
						}
					}
				else
					{
					g_PreCom->m_genScript = gqcom_INLfromComID(g_PreCom->m_ID);

					DisplayInterfaceCom(g_PreCom);

					g_PreComLock = true;	//win
					g_PreComBoughtIN = 1;
					g_PreComInclude = false;

					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);

					insertscripttextBox().IsReadOnly(false);
					}
				}
			else
				{
				g_PreComInclude = false;  //false
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0));

				insertinsertbutton().BorderBrush(myBrush);

				g_PreCom->m_genScript = gqcom_INLfromComID(g_PreCom->m_ID);

				DisplayInterfaceCom(g_PreCom);

				insertscripttextBox().IsReadOnly(true);
				}
			}
		else
			{
			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0));

			insertinsertbutton().BorderBrush(myBrush);
			}
	}

	void SecondaryAppWindowPageDX::DisplayInterfaceCom(std::shared_ptr<Cube::Qcom> f_Com)
	{
		std::string f_INL;

		f_INL.clear();

		for(int f_XY = 0; f_XY < f_Com->m_genScript->m_vec_InitLineOrdered.size(); f_XY++)
			{
			f_INL += f_Com->m_genScript->m_vec_InitLineOrdered[f_XY] + ::std::string("\n");
			}

		insertscripttextBox().Text(StrUsingStr(f_INL));
	}

	fire_and_forget SecondaryAppWindowPageDX::OnClickOpenPredator(void)
	{
		auto lifetime = get_strong();

		// Create a new window
		appWindowPredator = co_await AppWindow::TryCreateAsync();

		// Clean up when the window is closed
		appWindowPredator.Closed({ get_weak(), &SecondaryAppWindowPageDX::OnPredatorWindowClosed });

		// Navigate the frame to the page we want to show in the new window
		appWindowFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPagePredator>());

		// Attach the XAML content to our window
		ElementCompositionPreview::SetAppWindowContent(appWindowPredator, appWindowFrame);

		co_await appWindowPredator.TryShowAsync();
	}

	void SecondaryAppWindowPageDX::OnPredatorWindowClosed(winrt::Windows::UI::WindowManagement::AppWindow const&, winrt::Windows::Foundation::IInspectable const&)
	{
		//...
	}

	void SecondaryAppWindowPageDX::OnClosed(winrt::CoreWindow sender, winrt::Windows::UI::Core::CoreWindowEventArgs e)
	{
		//...
	}

	fire_and_forget SecondaryAppWindowPageDX::OnClickBuyComponent(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		std::string f_Adr = g_Wallet->GetAdr();

		winrt::fire_and_forget f_FF;

		if(g_PreComBool == false)
			{
#if 0
			printf("ECN:::Please Select a Component\n");
#endif
			return f_FF;
			}
		else if(f_Adr.length() < 20)
			{
			throw;
			}
		else if(g_PreCom->m_owner.length() < 20)
			{
			throw;
			}
		else if(f_Adr.compare(g_PreCom->m_owner) == 0)
			{
#if 0
			printf("ECN:::Cannot buy your own component\n");
#endif
			return f_FF;
			}
		else
			{
			bool f_Bought = g_Wallet->acBuy_ShareComID(g_PreCom->m_ID, g_PreCom->m_Cost, g_PreCom->m_Cost, g_PreCom->m_PackageShareID);

			if(f_Bought == true)
				{					//unlock
				g_PreComLock = true; //win
				g_PreComBoughtIN = 1;
				g_PreComInclude = false;

				Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

				insertinsertbutton().BorderBrush(myBrush);
				}
			else
				{
				float f_percBought = g_Wallet->acGet_assetContractbyID(-1, g_PreCom->m_ID);

				if(f_percBought == -5.0)
					{
#if 0
					printf("ECN:::Cannot buy your own component\n");
#endif
					return f_FF;
					}
				else if(f_percBought == -1.0)
					{
#if 0
					printf("ECN:::Component does not exist\n");
#endif
					return f_FF;
					}
				else
					{
					if(f_percBought >= g_PreCom->m_Cost)
						{
						g_PreComLock = true; //win
						g_PreComBoughtIN = 1;
						g_PreComInclude = false;

						Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

						insertinsertbutton().BorderBrush(myBrush);

						return f_FF;
						}
					else 
						{
						float f_PayAmt = g_PreCom->m_Cost - f_percBought;

						transactionStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
						transactionExplorerStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

						OpenTXD(g_PreCom->m_owner, f_PayAmt);

						return f_FF;
						}
					}
				}
			}

#if 0
		g_PreComBoughtIN = 0;
		g_PreComInclude = false;

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

		insertinsertbutton().BorderBrush(myBrush);
#endif

		return f_FF;
	}

	void SecondaryAppWindowPageDX::OnClickInsertInsert(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::OnClickInsertInsert";

		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(g_QamID <= 0)
			{
			g_QAccountID = -3;

			QAM* f_QAM = new QAM;

			f_QAM->acClear();

			f_QAM->m_qaccountid = -3;
			f_QAM->m_Name = "New ecom Grid";
			f_QAM->m_Author = g_Wallet->GetAdr();
			f_QAM->m_Description = "Insert Grid of ecom Native Qcom Pin Board";
			f_QAM->m_Keywords = "App ecoin";
			f_QAM->m_Features = "Com Loading";
			f_QAM->m_evalue = atof(to_string(insertpricetextBox().Text()).c_str());
			f_QAM->m_LevelCurrent = 0;
			f_QAM->m_LevelCount = 1;

			g_QAM = f_QAM;

			g_QAM->ac_Save();

			g_Editor_ON = true;

			g_QamStatus = QAM_STATUS_REFRESHED;

			g_QamID = g_QAM->m_qamid;
			}

		bool f_Fail_Trigger = false;

		ag_StatusLive(f_ref_CurrentPath, "f_com");
		std::shared_ptr<Qcom> f_com = ::std::make_shared_reflect<Qcom>();

		f_com->m_QamID = g_QamID;
		f_com->m_QamLevel = 0;
		f_com->m_ParentCom = ::g_QcomManager->m_Qcom;

		if(m_ComboSelectedCom == true)
			{
			f_com->m_name = to_string(insertnametextBox().Text());

			f_com->m_Cost = atof(to_string(insertpricetextBox().Text()).c_str());

			std::string f_Text = to_string(insertscripttextBox().Text());

			f_com->m_genScript = gqcom_INLfromString(f_Text);

			if(g_ShuttleCom == nullptr)
				{
				f_com->m_birthcomid = g_PreCom->m_ID;

				f_com->m_owner = g_PreCom->m_owner;

				f_com->m_vec_ESLFunction.clear();

				for(int f_Jet = 0; f_Jet < g_PreCom->m_vec_ESLFunction.size(); f_Jet++)
					{
					f_com->m_vec_ESLFunction.push_back(g_PreCom->m_vec_ESLFunction[f_Jet]);
					}

				if(f_com->m_vec_ESLFunction.size() <= 0)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_functionesl");
					f_com->m_vec_ESLFunction.push_back(std::make_shared_reflect<Cube::Qcom_eslfunction>());
					}

				if(g_PreCom->m_Frame_ESLFunction != nullptr)
					{
					f_com->m_Frame_ESLFunction = g_PreCom->m_Frame_ESLFunction;
					}
				else
					{
					ag_StatusLive(f_ref_CurrentPath, "f_functionesl2");
					f_com->m_Frame_ESLFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();
					}
				}
			else
				{
				f_com->m_birthcomid = g_ShuttleCom->m_ID;

				f_com->m_owner = g_ShuttleCom->m_owner;

				f_com->m_vec_ESLFunction.clear();

				for(int f_Jet = 0; f_Jet < g_ShuttleCom->m_vec_ESLFunction.size(); f_Jet++)
					{
					f_com->m_vec_ESLFunction.push_back(g_PreCom->m_vec_ESLFunction[f_Jet]);
					}

				if(f_com->m_vec_ESLFunction.size() <= 0)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_functionesl3");
					f_com->m_vec_ESLFunction.push_back(std::make_shared_reflect<Cube::Qcom_eslfunction>());
					}

				if(g_ShuttleCom->m_Frame_ESLFunction != nullptr)
					{
					f_com->m_Frame_ESLFunction = g_ShuttleCom->m_Frame_ESLFunction;
					}
				else
					{
					ag_StatusLive(f_ref_CurrentPath, "f_functionesl4");
					f_com->m_Frame_ESLFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();
					}

				for(int f_Jet = 0; f_Jet < g_ShuttleCom->m_vec_Input.size(); f_Jet++)
					{
					f_com->m_vec_Input.push_back(g_PreCom->m_vec_Input[f_Jet]);
					}

				for(int f_Jet = 0; f_Jet < g_ShuttleCom->m_vec_Output.size(); f_Jet++)
					{
					f_com->m_vec_Output.push_back(g_PreCom->m_vec_Output[f_Jet]);
					}
				}

			if((g_PreComBoughtIN <= 0) && (g_PreComInclude == true))
				{
				if(g_ShuttleCom == nullptr)
					{
					if((g_PreCom->m_description.length() > 0) && (f_com->m_description.length() == 0))
						{
						f_com->m_description = g_PreCom->m_description;
						}

					if(f_com->m_BossLVLMin < g_PreCom->m_BossLVLMin)
						{
						f_com->m_BossLVLMin = g_PreCom->m_BossLVLMin;
						}
					}
				else
					{
					if((g_ShuttleCom->m_description.length() > 0) && (f_com->m_description.length() == 0))
						{
						f_com->m_description = g_ShuttleCom->m_description;
						}

					if(f_com->m_BossLVLMin < g_ShuttleCom->m_BossLVLMin)
						{
						f_com->m_BossLVLMin = g_ShuttleCom->m_BossLVLMin;
						}
					}

				auto f_Info = winrt::Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();

				char* f_CharX = ag_ClearChar(256);

				::sprintf(f_CharX, "%u%u", f_Info.Id().Data1, f_Info.Id().Data2);

				std::string Id = f_CharX;

				delete f_CharX;

				char* rfpquery = ag_ClearChar(512);

				::sprintf(rfpquery, "SELECT id FROM reference WHERE hdid = '%s' AND comid = %i AND jobid = %i AND owner = '%s'", Id.c_str(), f_com->m_birthcomid, g_JobID, g_Wallet->GetAdr().c_str());

				g_SafeL[0]->acSelectCommand(rfpquery, false, false);

				delete rfpquery;

				int f_refCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_refCount = 0;
					}
				else
					{
					f_refCount = g_Schedular[0]->acEntrySize();
					}

				if(f_refCount == 0)
					{
					char* g_refvalue[17];

					for(int f_Count = 0; f_Count < 17; f_Count++)
						{
						g_refvalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
						}

					//update share integer voting score
					float f_ScoreResultFloat = 0.0f;

					if(g_ShuttleCom == nullptr)
						{
						f_ScoreResultFloat = g_PreCom->m_Cost + (g_PreCom->m_Cost * g_Wallet->m_Price);
						}
					else
						{
						f_ScoreResultFloat = g_ShuttleCom->m_Cost + (g_ShuttleCom->m_Cost * g_Wallet->m_Price);
						}

					::sprintf(g_refvalue[0], "%i", 0);
					::sprintf(g_refvalue[1], "%i", 3);
					::sprintf(g_refvalue[2], "%s", "ECN_Full_Include_ComID");
					::sprintf(g_refvalue[3], "%s", Id.c_str());
					::sprintf(g_refvalue[4], "%i", 0);
					::sprintf(g_refvalue[5], "%i", 4);
					::sprintf(g_refvalue[6], "%i", -1);	//g_CurrentShareID
					::sprintf(g_refvalue[7], "%i", 1);
					::sprintf(g_refvalue[8], "%i", g_JobID);
					::sprintf(g_refvalue[9], "%i", 0);
					::sprintf(g_refvalue[10], "%i", f_com->m_birthcomid);
					::sprintf(g_refvalue[11], "%s", "none");
					::sprintf(g_refvalue[12], "%f", f_ScoreResultFloat);
					::sprintf(g_refvalue[13], "%i", 0);
					::sprintf(g_refvalue[14], "%s", g_Wallet->GetAdr().c_str());
					::sprintf(g_refvalue[15], "%f", f_com->m_Cost);
					::sprintf(g_refvalue[16], "%f", f_com->m_Cost * g_Wallet->m_Price);

					g_SafeL[0]->Insert("reference", (const char **)g_reffield, (const char **)g_refvalue, 17, false, false);

					for(int f_Count = 0; f_Count < 15; f_Count++)
						{
						free(g_refvalue[f_Count]);
						}
					}
				}
			else if(::g_PreComBoughtIN > 0)
				{
				if(g_ShuttleCom == nullptr)
					{
					if((g_PreCom->m_description.length() > 0) && (f_com->m_description.length() == 0))
						{
						f_com->m_description = g_PreCom->m_description;
						}

					if(f_com->m_BossLVLMin < g_PreCom->m_BossLVLMin)
						{
						f_com->m_BossLVLMin = g_PreCom->m_BossLVLMin;
						}
					}
				else
					{
					if((g_ShuttleCom->m_description.length() > 0) && (f_com->m_description.length() == 0))
						{
						f_com->m_description = g_ShuttleCom->m_description;
						}

					if(f_com->m_BossLVLMin < g_ShuttleCom->m_BossLVLMin)
						{
						f_com->m_BossLVLMin = g_ShuttleCom->m_BossLVLMin;
						}
					}
				}
			else
				{
				f_com->m_description = "none";

				f_com->m_BossLVLMin = ecoin::g_BossLVLMin;

				f_Fail_Trigger = true;
				}
			}
		else
			{
			if(::g_PreComLock == false)
				{
				f_com->m_name = to_string(insertnametextBox().Text());

				f_com->m_Cost = atof(to_string(insertpricetextBox().Text()).c_str());

				std::string f_Text = to_string(insertscripttextBox().Text());

				f_com->m_owner = g_Wallet->GetAdr();

				f_com->m_birthcomid = -1;

				f_com->m_genScript = gqcom_INLfromString(f_Text);

				f_com->m_description = "none";

				f_com->m_BossLVLMin = ecoin::g_BossLVLMin;

				f_com->m_vec_ESLFunction.clear();

				ag_StatusLive(f_ref_CurrentPath, "f_functionesl5");
				f_com->m_vec_ESLFunction.push_back(std::make_shared_reflect<Cube::Qcom_eslfunction>());

				ag_StatusLive(f_ref_CurrentPath, "f_functionesl6");
				f_com->m_Frame_ESLFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();
				}
			else
				{
				f_com->m_name = to_string(insertnametextBox().Text());

				if(g_ShuttleCom == nullptr)
					{
					f_com->m_Cost = g_PreCom->m_Cost;

					f_com->m_genScript = g_PreCom->m_genScript;

					f_com->m_birthcomid = g_PreCom->m_ID;

					f_com->m_description = g_PreCom->m_description;

					f_com->m_BossLVLMin = g_PreCom->m_BossLVLMin;

					f_com->m_owner = g_PreCom->m_owner;
					}
				else
					{
					f_com->m_Cost = g_ShuttleCom->m_Cost;

					f_com->m_genScript = g_ShuttleCom->m_genScript;

					f_com->m_birthcomid = g_ShuttleCom->m_ID;

					f_com->m_description = g_ShuttleCom->m_description;

					f_com->m_BossLVLMin = g_ShuttleCom->m_BossLVLMin;

					f_com->m_owner = g_ShuttleCom->m_owner;
					}

				if(g_ShuttleCom == nullptr)
					{
					f_com->m_birthcomid = g_PreCom->m_ID;

					f_com->m_owner = g_PreCom->m_owner;

					f_com->m_vec_ESLFunction.clear();

					for(int f_Jet = 0; f_Jet < g_PreCom->m_vec_ESLFunction.size(); f_Jet++)
						{
						f_com->m_vec_ESLFunction.push_back(g_PreCom->m_vec_ESLFunction[f_Jet]);
						}

					if(f_com->m_vec_ESLFunction.size() <= 0)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_functionesl7");
						f_com->m_vec_ESLFunction.push_back(std::make_shared_reflect<Cube::Qcom_eslfunction>());
						}

					if(g_PreCom->m_Frame_ESLFunction != nullptr)
						{
						f_com->m_Frame_ESLFunction = g_PreCom->m_Frame_ESLFunction;
						}
					else
						{
						ag_StatusLive(f_ref_CurrentPath, "f_functionesl8");
						f_com->m_Frame_ESLFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();
						}
					}
				else
					{
					f_com->m_vec_ESLFunction.clear();

					for(int f_Jet = 0; f_Jet < g_ShuttleCom->m_vec_ESLFunction.size(); f_Jet++)
						{
						f_com->m_vec_ESLFunction.push_back(g_PreCom->m_vec_ESLFunction[f_Jet]);
						}

					if(f_com->m_vec_ESLFunction.size() <= 0)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_functionesl9");
						f_com->m_vec_ESLFunction.push_back(std::make_shared_reflect<Cube::Qcom_eslfunction>());
						}

					if(g_ShuttleCom->m_Frame_ESLFunction != nullptr)
						{
						f_com->m_Frame_ESLFunction = g_ShuttleCom->m_Frame_ESLFunction;
						}
					else
						{
						ag_StatusLive(f_ref_CurrentPath, "f_functionesl10");
						f_com->m_Frame_ESLFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();
						}

					for(int f_Jet = 0; f_Jet < g_ShuttleCom->m_vec_Input.size(); f_Jet++)
						{
						f_com->m_vec_Input.push_back(g_PreCom->m_vec_Input[f_Jet]);
						}

					for(int f_Jet = 0; f_Jet < g_ShuttleCom->m_vec_Output.size(); f_Jet++)
						{
						f_com->m_vec_Output.push_back(g_PreCom->m_vec_Output[f_Jet]);
						}
					}

				if((::g_PreComBoughtIN <= 0) && (::g_PreComInclude == true))
					{
					auto f_Info = winrt::Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();

					char* f_CharX = ag_ClearChar(256);

					::sprintf(f_CharX, "%u%u", f_Info.Id().Data1, f_Info.Id().Data2);

					std::string Id = f_CharX;

					delete f_CharX;

					char* rfpquery = ag_ClearChar(512);
					::sprintf(rfpquery, "SELECT id FROM reference WHERE hdid = '%s' AND comid = %i AND jobid = %i AND owner = '%s'", Id.c_str(), f_com->m_birthcomid, g_JobID, g_Wallet->GetAdr().c_str());
					g_SafeL[0]->acSelectCommand(rfpquery, false, false);
					delete rfpquery;

					int f_refCount = 0;
		
					if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
						{
						f_refCount = 0;
						}
					else
						{
						f_refCount = g_Schedular[0]->acEntrySize();
						}

					if(f_refCount == 0)
						{
						char* g_refvalue[17];

						for(int f_Count = 0; f_Count < 17; f_Count++)
							{
							g_refvalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
							}

						//update share integer voting score
						float f_ScoreResultFloat = 0.0f;

						if(g_ShuttleCom == nullptr)
							{
							f_ScoreResultFloat = g_PreCom->m_Cost + (g_PreCom->m_Cost * g_Wallet->m_Price);
							}
						else
							{
							f_ScoreResultFloat = g_ShuttleCom->m_Cost + (g_ShuttleCom->m_Cost * g_Wallet->m_Price);
							}

						::sprintf(g_refvalue[0], "%i", 0);
						::sprintf(g_refvalue[1], "%i", 3);
						::sprintf(g_refvalue[2], "%s", "ECN_Full_Include_ComID");
						::sprintf(g_refvalue[3], "%s", Id.c_str());
						::sprintf(g_refvalue[4], "%i", 0);
						::sprintf(g_refvalue[5], "%i", 4);
						::sprintf(g_refvalue[6], "%i", -1);
						::sprintf(g_refvalue[7], "%i", 1);
						::sprintf(g_refvalue[8], "%i", g_JobID);
						::sprintf(g_refvalue[9], "%i", 0);
						::sprintf(g_refvalue[10], "%i", f_com->m_birthcomid);
						::sprintf(g_refvalue[11], "%s", "none");
						::sprintf(g_refvalue[12], "%f", f_ScoreResultFloat);
						::sprintf(g_refvalue[13], "%i", 0);
						::sprintf(g_refvalue[14], "%s", g_Wallet->GetAdr().c_str());
						::sprintf(g_refvalue[15], "%f", f_com->m_Cost);
						::sprintf(g_refvalue[16], "%f", f_com->m_Cost * g_Wallet->m_Price);

						g_SafeL[0]->Insert("reference", (const char **)g_reffield, (const char **)g_refvalue, 17, false, false);

						for(int f_Count = 0; f_Count < 17; f_Count++)
							{
							free(g_refvalue[f_Count]);
							}

#if 0
						char* f_sharequery = ag_ClearChar(512);
						::sprintf(f_sharequery, "UPDATE SET score = %f FROM share WHERE id = %i", f_ScoreResultFloat, g_Wallet->m_my_pledge_shareID);
						g_SafeL[0]->UpdateQuery(f_sharequery);
						delete f_sharequery;
#endif
						}
					}
				else
					{
					f_Fail_Trigger = true;
					}
				}
			}

		if(f_Fail_Trigger == false)
			{
			f_com->m_position->m_X = Cube::g_QcomManager->m_current_X;
			f_com->m_position->m_Y = Cube::g_QcomManager->m_current_Y;
			f_com->m_position->m_Z = 0.0;

			::g_QcomManager->m_Qcom->m_vec_Qcom.push_back(f_com);
			::g_QcomManager->m_vec_Qcom.push_back(f_com);

			//parse
			::g_QcomManager->acParse_GenScript(f_com);

			//build
			acBuild_ExcomPackaging();

			//save
			f_com->ac_Save();

			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			winrt::Windows::UI::Xaml::Media::SolidColorBrush myBrush(winrt::Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

			insertinsertbutton().BorderBrush(myBrush);
			}
	}

	void SecondaryAppWindowPageDX::OnClickIncludeComponent(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(g_PreComInclude == true)
			{	
			g_PreComInclude = false;
			}
		else
			{
			g_PreComInclude = true;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90) });

			insertinsertbutton().BorderBrush(myBrush);
			}
	}

	void SecondaryAppWindowPageDX::Frame_OnCount(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable e)
	{
		std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPageDX::Frame_OnCount";

		if(g_WalletOpen == true)
			{
			if(g_Schedular[1]->acPopulusIsFull() == true)
				{
				if(m_Frame_OnCount == false)
					{
					m_Frame_OnCount = true;

					time(&g_Currtime);

					int f_Double = g_Currtime - g_Storetime;

					 ///////////
					// ecoin //
					g_EcoinDifficulty = 100;
					g_AverageSaleValue = 300;

					g_EVALUE = g_AverageSaleValue;

					if(g_Wallet->m_vec_MainMode[m_IDX] != ECOIN_MODE_VIEWING)
						{
						//Element Rate per Second
						char* f_Char = ag_ClearChar(255);

						g_Wallet->m_vec_ElementCount_Muti[m_IDX]->lock();

						int f_ElementCount = g_Wallet->m_vec_ElementCount[m_IDX];

						::sprintf(f_Char, "%i elements/s", f_ElementCount);

						g_Wallet->m_vec_ElementCount[m_IDX] = 0;

						g_Wallet->m_vec_ElementCount_Muti[m_IDX]->unlock();

						std::string f_String5 = f_Char;

						delete f_Char;

						khashBlock().Text(StrUsingStr(f_String5));

						//Current Lowest Mark
						if(g_LowtonMark < FLT_MAX)
							{
							char* f_CharX = ag_ClearChar(255);

							::sprintf(f_CharX, "Current Lowest Mark (%.3f)", g_LowtonMark);

							currentlowtontextBlock().Text(StrUsingStr(std::string(f_CharX)));

							delete f_CharX;

							currentStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
							}

						if(g_Found_Block > 0)
							{
							rewardStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
							foundStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
							foundText().Text(L"ecoin Block Found!");

							char* f_PledgeTotal = ag_ClearChar(255);
							::sprintf(f_PledgeTotal, "%f ECN plus %f eGBP Token complete pledge for block", g_espo_ECN_Amount, g_espo_Amount);
							std::string f_Str = f_PledgeTotal;
							winrt::hstring f_HStr = StrUsingStr(f_Str);
							delete f_PledgeTotal;

							rewardtextblock().Text(f_HStr);

							g_Found_Block--;
							}
						else
							{
							if(g_Found_Msg > 0)
								{
								rewardStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
								foundStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
								foundText().Text(StrUsingStr(g_Found_Text));
								g_Found_Msg--;
								}
							else
								{
								if(g_Found_Share > 0)
									{
									rewardStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
									foundStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
									foundText().Text(L"Share Divined!");
									g_Found_Share--;
									}
								else
									{
									rewardStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
									foundStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
									}
								}
							}

						g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

						if(((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS) || ((g_Type == 3) && (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW)) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_SHUTDOWN_COMPRESS)) && (g_Wallet->m_vec_ComputeText_PrintMode_Lowton[m_IDX] == ECOIN_MUTEX_MODE_PRINT))
							{
							computeoutputlowtontextBox().Text(StrUsingStr(g_Wallet->m_vec_ComputeText_Lowton[m_IDX]));

							g_Wallet->m_vec_ComputeText_PrintMode_Lowton[m_IDX] = ECOIN_MUTEX_MODE_OFF;
							}
					
						if(((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS) || ((g_Type == 3) && (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW)) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_SHUTDOWN_COMPRESS)) && (g_Wallet->m_vec_ComputeText_PrintMode[m_IDX] == ECOIN_MUTEX_MODE_PRINT))
							{
							computeoutputtextBox().Text(StrUsingStr(g_Wallet->m_vec_ComputeText[m_IDX]));

							g_Wallet->m_vec_ComputeText_PrintMode[m_IDX] = ECOIN_MUTEX_MODE_OFF;
							}

						if(((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_SHUTDOWN_COMPRESS) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_SHUTDOWN_NONVIEW)) && (f_ElementCount <= 0))
							{
							g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_VIEWING;
							}

						g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();
						}
					
					 ///////////////////////////
					// medium to long update //
					if(f_Double >= ECOIN_ASYNC_REFRESH_SECONDS)
						{
						time(&g_Storetime);
			
						if((g_GUItimer <= 0) && ((g_Wallet->m_vec_MainMode[m_IDX] != ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] != ECOIN_MODE_COMPRESS)))
							{
							g_GUItimer = 5;

							  //////////////
							 // JobID
							//
							g_JobID = g_Wallet->acGet_JobID(m_IDX, 1);

							if((g_ShareID > 0) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_VIEWING))
								{
								std::shared_ptr<ShareContainerExt> f_ShareContainer = Cag->ag_SelectPeerGraphExt(g_JobID, 1, 0, g_CurrentShareOffset, g_PEER);

								if(f_ShareContainer->m_espo_PeerCount > 0)
									{
									int f_OwnPeerCount = f_ShareContainer->m_espo_TotalSharesOwnPeer;
									int f_OnPeerCount = f_ShareContainer->m_espo_SharesOnPeerCount;

									char numbuf2[100];

									_itoa(f_ShareContainer->m_espo_PeerCount, numbuf2, 10);
									std::string f_interim = numbuf2;
								
									allpeertextBlock().Text(StrUsingStr(f_interim + " peers"));

									char numbuf3[100];
									_itoa(f_OwnPeerCount, numbuf3, 10);
									std::string f_interim2 = numbuf3;
								
									ownsharestextBlock().Text(StrUsingStr(f_interim2 + " own"));

									int f_ShareCounting = f_ShareContainer->m_espo_TotalShares;

									char numbuf4[100];
									_itoa(f_ShareCounting, numbuf4, 10);
									std::string f_interim3 = numbuf4;
								
									alltotaltextBlock().Text(StrUsingStr(f_interim3 + " on block"));
							
									char numbuf9[100];
									_itoa(f_OnPeerCount, numbuf9, 10);
									std::string f_interim8 = numbuf9;
								
									owntotaltextBlock().Text(StrUsingStr("share count " + f_interim8));

									g_ShareCount = f_ShareCounting;
									}
								else
									{
									int f_OwnPeerIndex = 0;
									int f_OnPeerIndex = 0;
									int f_OwnTotal = 0;
									int f_OwnPeerCount = 0;
									int f_OnPeerCount = 0;

									char numbuf2[100];

									_itoa(f_ShareContainer->m_espo_PeerCount, numbuf2, 10);
									std::string f_interim = numbuf2;

									allpeertextBlock().Text(StrUsingStr(f_interim + " peers"));

									char numbuf3[100];
									_itoa(f_OwnPeerCount, numbuf3, 10);
									std::string f_interim2 = numbuf3;

									ownsharestextBlock().Text(StrUsingStr(f_interim2 + " own"));

									int f_ShareCounting = 0;

									char numbuf4[100];
									_itoa(f_ShareCounting, numbuf4, 10);
									std::string f_interim3 = numbuf4;

									alltotaltextBlock().Text(StrUsingStr(f_interim3 + " on block"));

									char numbuf9[100];
									_itoa(f_OnPeerCount, numbuf9, 10);
									std::string f_interim8 = numbuf9;

									owntotaltextBlock().Text(StrUsingStr("share count " + f_interim8));

									g_ShareCount = f_ShareCounting;
									}
								}

							char* rewardquery = ag_ClearChar(1000);
							sprintf(rewardquery, "SELECT id, reward FROM reward ORDER BY id DESC LIMIT 1");
							g_SafeL[1]->acSelectCommand(rewardquery, 2, false);
							delete rewardquery;

							int f_RewardCount = 0;

							if(g_Schedular[1]->acEntry(0)[0].at(0) == '0')
								{
								f_RewardCount = 0;
								}
							else
								{
								f_RewardCount = g_Schedular[1]->acEntrySize();
								}

							if(f_RewardCount == 1)
								{
								g_Wallet->m_Reward = atof(g_Schedular[1]->acEntry(0)[1].c_str());
								g_Wallet->m_RewardID = atoi(g_Schedular[1]->acEntry(0)[0].c_str());
								}

							 ////////////////////
							// Wallet Balance //
							double f_BalanceIndollars = g_Wallet->GetBalance(true, 1);

							double f_Balance = 0.0f;

							if(f_BalanceIndollars != 0.0f)
								{
								f_Balance = f_BalanceIndollars / (double)g_Wallet->m_Price;
								}

							double f_CPSBalanceInpounds = g_Wallet->GetBalanceCPS(true, 1);

							char* numbuf5 = ag_ClearChar(100);
							sprintf(numbuf5, "on #%i", g_espo_ShareOffset);
							std::string f_interim5 = numbuf5;
							delete numbuf5;
						
							owninfotextBlock().Text(StrUsingStr(f_interim5));

							char* numbuf6 = ag_ClearChar(100);
							sprintf(numbuf6, "peer #%i", g_espo_Peer);
							std::string f_interim6 = numbuf6;
							delete numbuf6;
						
							ownpeertextBlockf().Text(StrUsingStr(f_interim6));

							char* numbuf10 = ag_ClearChar(100);
							sprintf(numbuf10, "on share #%i", g_espo_ShareOffset);
							std::string f_interim4 = numbuf10;
							delete numbuf10;
						
							ownsharetextBlock().Text(StrUsingStr(f_interim4));

							char* numbuf7 = ag_ClearChar(100);
							sprintf(numbuf7, "on peer #%i", g_espo_Peer);
							std::string f_interim7 = numbuf7;
							delete numbuf7;
						
							ownpeertextBlock().Text(StrUsingStr(f_interim7));

							ownerinfoBlock().Text(StrUsingStr(g_espo_Owner));

							char* numbuf88 = ag_ClearChar(100);
							sprintf(numbuf88, "%f", g_espo_Score);
							std::string f_interim88 = numbuf88;
							delete numbuf88;
						
							voteinfoBlock().Text(StrUsingStr(f_interim88));

							char* f_Char = ag_ClearChar(255);

							sprintf(f_Char, "%.4f eGBP", (float)g_espo_Amount);
							std::string f_String13 = f_Char;

							pledgeinfoBlock().Text(StrUsingStr(f_String13));

							FillChar(f_Char, 255);

							sprintf(f_Char, "%.8f ECN", (float)g_espo_ECN_Amount);
							std::string f_String14 = f_Char;

							ecnpledgeinfoBlock().Text(StrUsingStr(f_String14));

							dateinfoBlock().Text(StrUsingStr(g_espo_Date));

							  //////////////////////
							 //
							// balance
							FillChar(f_Char, 255);

							sprintf(f_Char, "%.5f ECN", (float)f_Balance);
							std::string f_String2 = f_Char;
							ecoinpersecondBlock().Text(StrUsingStr(f_String2));

							FillChar(f_Char, 255);

							sprintf(f_Char, "%.8f", (float)f_BalanceIndollars);
							std::string f_String4 = f_Char;

							walletindollarstextBlock().Text(StrUsingStr(f_String4));

							FillChar(f_Char, 255);

							sprintf(f_Char, "%.4f", (float)g_Wallet->m_Price);
							std::string f_String9 = f_Char;

							ecoinvalueBlock().Text(StrUsingStr(f_String9));

							FillChar(f_Char, 255);

							sprintf(f_Char, "%.4f", (float)f_CPSBalanceInpounds);
							std::string f_String10 = f_Char;
							delete f_Char;

							walletindollarstextBlock_CPS().Text(StrUsingStr(f_String10));

							myaddressTextBlock().Text(StrUsingStr("Wallet Address " + g_Wallet->GetAdr()));

							//Send Keep Alive Message to all other Servers
							g_SafeL[0]->acKeepAliveCommand("UploadServerConnectionKeepAlive", false);
							g_SafeL[1]->acKeepAliveCommand("ReceiveServerConnectionKeepAlive", false);
							g_SafeL[2]->acKeepAliveCommand("QuantumServerConnectionKeepAlive", false);
							}
						else
							{
							if((g_Wallet->m_vec_MainMode[m_IDX] != ECOIN_MODE_NONVIEW) && (g_Wallet->m_vec_MainMode[m_IDX] != ECOIN_MODE_COMPRESS))
								{
								g_GUItimer--;
								}

							if(g_TXD_Scan == true)
								{
								qtx_Update();
								}
							}

						  ////////////
						 // Ackent //
						// events //
						char* f_eventquery = ag_ClearChar(512);
						sprintf(f_eventquery, "SELECT id, appid, type, shareid, blockid, score, category, owner, reward, pledge, fee, pathowner FROM event WHERE id > %i", g_EventID);
						g_SafeL[1]->acSelectCommand(f_eventquery, true, false);
						delete f_eventquery;

						int f_EventIDSupport = 1;

						if(g_Schedular[1]->acEntry(0)[0].at(0) != '0')
							{
							for(int f_Jet = 0; f_Jet < g_Schedular[1]->acEntrySize(); f_Jet++)
								{
								ag_StatusLive(f_ref_CurrentPath, "f_Ack");
								std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(atoi(g_Schedular[1]->acEntry(f_Jet)[2].c_str())), atoi(g_Schedular[1]->acEntry(f_Jet)[3].c_str()), 1);

								f_Ack->m_ECN = atof(g_Schedular[1]->acEntry(f_Jet)[8].c_str()) + atof(g_Schedular[1]->acEntry(f_Jet)[9].c_str());
								f_Ack->m_Origin = 0;

								f_Ack->m_AppID = atoi(g_Schedular[1]->acEntry(f_Jet)[1].c_str());
								f_Ack->m_ShareID = atoi(g_Schedular[1]->acEntry(f_Jet)[4].c_str());
								f_Ack->m_BlockID = atoi(g_Schedular[1]->acEntry(f_Jet)[5].c_str());
								f_Ack->m_Score = atoi(g_Schedular[1]->acEntry(f_Jet)[5].c_str());
								f_Ack->m_Category = atoi(g_Schedular[1]->acEntry(f_Jet)[6].c_str());
								f_Ack->m_Owner = g_Schedular[1]->acEntry(f_Jet)[7];
								f_Ack->m_Reward = atof(g_Schedular[1]->acEntry(f_Jet)[8].c_str());
								f_Ack->m_Pledge = atof(g_Schedular[1]->acEntry(f_Jet)[9].c_str());
								f_Ack->m_Fee = atof(g_Schedular[1]->acEntry(f_Jet)[10].c_str());
								f_Ack->m_PathOwner = g_Schedular[1]->acEntry(f_Jet)[11];

								f_EventIDSupport = atoi(g_Schedular[1]->acEntry(f_Jet)[0].c_str());

								g_Ackent.push_back(f_Ack);
								g_EventID = f_EventIDSupport;
								}
							}

						bool f_Scan = true;
						for(int f_Helly = 0; f_Helly < g_Ackent.size(); f_Helly++)
							{
							if(f_Scan)
								{
								std::shared_ptr<Ackent> f_Ack = g_Ackent[f_Helly];

								if(f_Ack->m_State < 1)
									{
									f_Ack->m_State = 1;

									f_Helly = g_Ackent.size();
									f_Scan = false;

									if(f_Ack->m_Origin == 1)
										{
										char* g_eventvalue[11];

										for(int f_Count = 0; f_Count < 11; f_Count++)
											{
											g_eventvalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
											}

										sprintf(g_eventvalue[0], "%i", 1);
										sprintf(g_eventvalue[1], "%i", f_Ack->m_Type);
										sprintf(g_eventvalue[2], "%i", f_Ack->m_ShareID);
										sprintf(g_eventvalue[3], "%i", f_Ack->m_BlockID);
										sprintf(g_eventvalue[4], "%i", f_Ack->m_Score);
										sprintf(g_eventvalue[5], "%i", f_Ack->m_Category);
										sprintf(g_eventvalue[6], "%s", f_Ack->m_Owner.c_str());
										sprintf(g_eventvalue[7], "%s", f_Ack->m_PathOwner.c_str());
										sprintf(g_eventvalue[8], "%f", f_Ack->m_Reward);
										sprintf(g_eventvalue[9], "%f", f_Ack->m_Pledge);
										sprintf(g_eventvalue[10], "%f", f_Ack->m_Fee);

										g_SafeL[1]->Insert("event", (const char **)g_eventfield, (const char **)g_eventvalue, 11, true, false);

										for(int f_Count = 0; f_Count < 11; f_Count++)
											{
											free(g_eventvalue[f_Count]);
											}
										}

									acProcessAckMessage(f_Ack);
									}
								}
							}
						}

					m_Frame_OnCount = false;
					}
				}
			else
				{
				g_Schedular[1]->acScheduleUpdator();
				}
			}
	}

	bool SecondaryAppWindowPageDX::ConfigureSimulatorAsync(bool f_Bool)
	{
		auto f_BoolResult = ConfigSim(f_Bool);

		return true;
	}

	std::future<bool> SecondaryAppWindowPageDX::ConfigSim(bool f_Bool)
	{
		auto lifetime = get_strong();

		std::string f_String = "in-app-purchase-consumables.xml";

		winrt::hstring f_hstring = StrUsingStr(f_String);

		//C:\Users\storm\AppData\Local\Packages\48521OSIREMLTD.ecoin_rtgm85ssf2asy\RoamingState

		Windows::Storage::StorageFile f_File(nullptr);

		f_File = co_await winrt::Windows::Storage::ApplicationData::Current().RoamingFolder().GetFileAsync(f_hstring);

		if(f_File != nullptr)
			{
			if(f_File.IsAvailable() == true)
				{
				co_await Windows::ApplicationModel::Store::CurrentAppSimulator::ReloadSimulatorAsync(f_File);
				}
			}

		co_return true;
	}

	void SecondaryAppWindowPageDX::OnSaveOBJ(std::string f_Filename)
	{
		std::string f_String;
		f_String.clear();

		const char* f_Char = "# osirem.com ecn.world bitcoin-office.com\n";
		f_String += f_Char;

		const char* f_Char1 = "mtllib ";
		f_String += f_Char1;

		f_String += f_Filename + ".mtl\n";

		std::string f_Stringify = "o " + f_Filename + "_" + f_Filename + "\n";
		f_String += f_Stringify;
	
		  //////////////////////
		 /// Cube vertices  ///
		//////////////////////

		const char* f_Press_v = "v ";
		const char* f_Press_return = "\n";

		for(int BiVectorCount = 0; BiVectorCount < g_CubeHeshExport->BiVectorCount; BiVectorCount++)
			{
			f_String += f_Press_v;

			acBufwriteValueFloat(&f_String, g_CubeHeshExport->m_vec_Result[BiVectorCount].pos.x);
			acBufwriteValueFloat(&f_String, g_CubeHeshExport->m_vec_Result[BiVectorCount].pos.y);
			acBufwriteValueFloat(&f_String, g_CubeHeshExport->m_vec_Result[BiVectorCount].pos.z);

			f_String += f_Press_return;
			}

		const char* f_Pressvt = "vt ";
		const char* f_Press0 = "0 ";
		const char* f_Press1 = "1 ";
		const char* f_Press0return = "0\n";
		const char* f_Press1return = "1\n";

		for(int f_TextureCube = 0; f_TextureCube < g_CubeHeshExport->BiCount; f_TextureCube++)
			{
			f_String += f_Pressvt;
			f_String += f_Press0;
			f_String += f_Press0return;

			f_String += f_Pressvt;
			f_String += f_Press0;
			f_String += f_Press1return;

			f_String += f_Pressvt;
			f_String += f_Press1;
			f_String += f_Press1return;

			f_String += f_Pressvt;
			f_String += f_Press1;
			f_String += f_Press0return;
			}

		const char* f_Pressvn = "vn ";
		const char* f_Pressm1 = "-1 ";
		const char* f_Pressm1return = "-1\n";

		for(int f_NormCube = 0; f_NormCube < g_CubeHeshExport->BiCount; f_NormCube++)
			{
			f_String += f_Pressvn;
			f_String += f_Press0;
			f_String += f_Press0;
			f_String += f_Pressm1return;

			f_String += f_Pressvn;
			f_String += f_Press0;
			f_String += f_Press0;
			f_String += f_Press1return;

			f_String += f_Pressvn;
			f_String += f_Press1;
			f_String += f_Press0;
			f_String += f_Press0return;

			f_String += f_Pressvn;
			f_String += f_Press0;
			f_String += f_Pressm1;
			f_String += f_Press0return;

			f_String += f_Pressvn;
			f_String += f_Pressm1;
			f_String += f_Press0;
			f_String += f_Press0return;

			f_String += f_Pressvn;
			f_String += f_Press0;
			f_String += f_Press1;
			f_String += f_Press0return;
			}

		  ///////////////////
		 /// MATERIALS ..///
		///////////////////

		const char* f_Material = "usemtl ";
		std::string f_MatEnd = f_Filename + "Mtl\n";
		const char* f_MaterialEnd = f_MatEnd.c_str();

		f_String += f_Material;
		f_String += f_MaterialEnd;

		  ///////////////
		 /// FACES ..///
		///////////////

		const char* f_Pressf = "f ";
		const char* f_Pressslash = "/";
		const char* f_Pressspace = " ";
		const char* f_Pressreturn = "\n";

		for(int f_FaceCube = 0; f_FaceCube < g_CubeHeshExport->BiCount * 8; f_FaceCube += 8)
			{
			//1
			f_String += f_Pressf;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);

			f_String += f_Pressreturn;

			//2

			f_String += f_Pressf;
			acBufwriteValueInt(&f_String, f_FaceCube + 8);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 4);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 2);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 6);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 2);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);

			f_String += f_Pressreturn;

			//3

			f_String += f_Pressf;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 8);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 6);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);

			f_String += f_Pressreturn;

			//4

			f_String += f_Pressf;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 6);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 2);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);

			f_String += f_Pressreturn;

			//5

			f_String += f_Pressf;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 8);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 2);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 8);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 4);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 8);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 8);

			f_String += f_Pressreturn;

			//6

			f_String += f_Pressf;
			acBufwriteValueInt(&f_String, f_FaceCube + 8);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 5);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 6);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 1);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 6);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 3);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 6);

			f_String += f_Pressspace;

			acBufwriteValueInt(&f_String, f_FaceCube + 4);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 7);
			f_String += f_Pressslash;
			acBufwriteValueInt(&f_String, f_FaceCube + 6);

			f_String += f_Pressreturn;
			}

		acSaveFileBuffer(f_String);
	}

	std::future<bool> SecondaryAppWindowPageDX::acSaveFileBuffer(std::string f_Buffer)
	{
		winrt::hstring f_StringBuf = StrUsingStr(f_Buffer);

		::winrt::Windows::Storage::Pickers::FileSavePicker savePicker;
		savePicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
		
		savePicker.FileTypeChoices().Insert(L"OBJ Mesh", winrt::single_threaded_vector<winrt::hstring>({ L".obj" }));
		
		savePicker.SuggestedFileName(L"New Mesh");

		::winrt::Windows::Storage::StorageFile file = co_await savePicker.PickSaveFileAsync();

		if(file != nullptr)
			{
			::winrt::Windows::Storage::CachedFileManager::DeferUpdates(file);

			await winrt::Windows::Storage::FileIO::WriteTextAsync(file, f_StringBuf);
            
			::winrt::Windows::Storage::Provider::FileUpdateStatus status = co_await ::winrt::Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file);
            if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::Complete)
				{
#if 0
				VarResBox().Text(StrUsingStr("OBJ Mesh File " + to_string(file.Name()) + " Save Successfull!!!"));
#endif
				}
            else if (status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::CompleteAndRenamed)
				{
#if 0
				VarResBox().Text(StrUsingStr("OBJ Mesh File " + to_string(file.Name()) + " Couldn't Be Saved..."));
#endif
				}
            else
				{
				throw;
				}
			}
        else
			{
#if 0
			VarResBox().Text(StrUsingStr("OBJ Mesh File " + to_string(file.Name()) + "Cancelled Save"));
#endif
			}

		co_return true;
	}

	void SecondaryAppWindowPageDX::OnWalletClick(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
#if 0
		if(walletBar().IsOpen() == true)
			{
			walletBar().IsOpen(false);
			}
		else
			{
			walletBar().IsOpen(true);
			}
#endif

		if(appWindowPredator == nullptr)
			{
			OnClickOpenPredator();
			}

		OnClickOpenAppBar();
	}

	void SecondaryAppWindowPageDX::OnHeshtextClick(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		heshText().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
		heshButton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	}

	void SecondaryAppWindowPageDX::OnClickWithDraw(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(withdrawStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			withdrawStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			withdrawStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
			withdrawconfirmtextBlock().Text(L"Please enter your Pay-Pal email for payment contain \"ecoincps\"");
			}

#if 0
		// Create the URI from a string
		std::string f_URL1 = "http://ecn.world?owner=";
		std::string f_URL2 = g_Wallet->GetAdr();
		std::string f_URL = f_URL1 + f_URL2;
		Uri uri({ StrUsingStr(f_URL) });

		// Launch the URI
		Windows::System::Launcher::LaunchUriAsync(uri);
#endif
	}

	void SecondaryAppWindowPageDX::OnClickBuy(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);
	}

	void SecondaryAppWindowPageDX::onClickVoteUp(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		//make visible the pledge system
		if(pledgeStack().Visibility() == winrt::Windows::UI::Xaml::Visibility::Visible)
			{
			pledgeStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			pledgeStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);

			OnLoadPledgeStack();

			pledgeresultstextBlock().Text(L"...Enter amount(s) above and click synchronize...");
			}
	}

	void SecondaryAppWindowPageDX::acProcessAckMessage(std::shared_ptr<Ackent> f_Ack)
	{
		switch(f_Ack->m_Type)
			{
			case ACK_TYPE::ACK_TYPE_VOTE_PLEDGE:
				{
				char* f_Chr = ag_ClearChar(2500);
				sprintf(f_Chr, "VotePledge on SHR#(%i)!..ECN %f EGBP %f", f_Ack->m_ShareID, f_Ack->m_ECN, f_Ack->m_Pledge);
				std::string f_ChrString = f_Chr;
				delete f_Chr;

				g_Found_Msg = 19;
				g_Found_Text = f_ChrString;

#ifdef ECOIN_LOAD_ACKS
				if(f_Ack->m_ShareID > 0)
					{
					swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this]()
						{
						acLoadShare(f_Ack->m_ShareID, 0);
						});
					}
#endif
				}break;

			case ACK_TYPE::ACK_TYPE_REF:
				{
				ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);
				
				if(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_VIEWING)
					{
					if(f_Ack->m_PathOwner.compare(::g_Wallet->GetAdr()) == 0)
						{
						char* f_Chr = ag_ClearChar(2500);
						sprintf(f_Chr, "Receieved. Reference Made. SHR#(%i) ECN %f, EGBP %f. FROM %s", f_Ack->m_ShareID, f_Ack->m_ECN, f_Ack->m_Pledge, f_Ack->m_PathOwner.c_str());
						std::string f_ChrString = f_Chr;
						delete f_Chr;

						g_Found_Msg = 39;
						g_Found_Text = f_ChrString;

#ifdef ECOIN_LOAD_ACKS
						if(f_Ack->m_ShareID > 0)
							{
							swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this]()
								{
								acLoadShare(f_Ack->m_ShareID, 0);
								});
							}
#endif
						}
					}
				}break;

			case ACK_TYPE::ACK_TYPE_SHARE:
				{
				if(f_Ack->m_Owner.compare(::g_Wallet->GetAdr()) == 0)
					{
					g_Found_Share = 35;

					char* f_Chr = ag_ClearChar(2500);
					::sprintf(f_Chr, "ShareFall4U on SHR#(%i)!..ECN... %f EGBP %f", f_Ack->m_ShareID, f_Ack->m_ECN, f_Ack->m_Pledge);
					std::string f_ChrString = f_Chr;
					delete f_Chr;

					g_Found_Text = f_ChrString;

#ifdef ECOIN_LOAD_ACKS
					if(f_Ack->m_ShareID > 0)
						{
						swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this]()
							{
							acLoadShare(f_Ack->m_ShareID, 0);
							});
						}
#endif
					}
				}break;

			case ACK_TYPE::ACK_TYPE_BOND_ELEMENT:
				{
				if(f_Ack->m_Owner.compare(::g_Wallet->GetAdr()) == 0)
					{
					g_Found_Share = 29;

					char* f_Chr = ag_ClearChar(2500);
					::sprintf(f_Chr, "Elements4U on SHR#(%i)!..ECN %f", f_Ack->m_ShareID, f_Ack->m_ECN);
					std::string f_ChrString = f_Chr;
					delete f_Chr;

					g_Found_Text = f_ChrString;

#ifdef ECOIN_LOAD_ACKS
					if(f_Ack->m_ShareID > 0)
						{
						swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this]()
							{
							acLoadShare(f_Ack->m_ShareID, 0);
							});
						}
#endif
					}
				}break;

			case ACK_TYPE::ACK_TYPE_BLOCK:
				{
				char* f_Chr = ag_ClearChar(2500);

				if(f_Ack->m_Owner.compare(::g_Wallet->GetAdr()) == 0)
					{
					::sprintf(f_Chr, "YOU FOUND BLOCK... on BLK#(%i)!..ECN %f EGBP %f", f_Ack->m_BlockID, f_Ack->m_ECN, f_Ack->m_Pledge);
					}
				else
					{
					::sprintf(f_Chr, "BlockFall on BLK#(%i)!..ECN %f EGBP %f", f_Ack->m_BlockID, f_Ack->m_ECN, f_Ack->m_Pledge);
					}

				std::string f_ChrString = f_Chr;
				delete f_Chr;

				g_Found_Text = f_ChrString;
				g_Found_Block = 49;

#ifdef ECOIN_LOAD_ACKS
				if(f_Ack->m_ShareID > 0)
					{
					swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this]()
						{
						acLoadShare(f_Ack->m_ShareID, 0);
						});
					}
#endif
				}break;
			}
	}

	   ////////////////////////////////////////////////////////
	  // acLoadShare(ShareID, ServerIndex)
	 //  singular ecoin share hesh loading point function
	//
	void SecondaryAppWindowPageDX::acLoadShare(int f_LShare, int f_ServLay)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::acLoadShare";

#if 0	//reflection continuation//
		acClick(f_ref_CurrentPath);
#endif

#ifdef TEST_VERIFY_SCP_BUILD_ECOM
		ag_StatusLive(f_ref_CurrentPath, "f_Collection");
		std::shared_ptr<classCollection> f_Collection = std::make_shared_reflect<classCollection>();
#endif

		int f_ShareID = 0; //forward instantiation

		bool f_L = false;

		std::shared_ptr<ShareContainerExt> f_ShareContainer = Cag->ag_SelectPeerGraphExt(g_JobID, f_ServLay, f_LShare, g_CurrentShareOffset, g_PEER);

		if(f_ShareContainer->m_espo_PeerCount)
			{
			if(f_LShare <= 0) //INPUT offset and peer
				{
				if(g_CurrentShareOffset < f_ShareContainer->m_espo_SharesOnPeerCount)
					{
					f_ShareID = f_ShareContainer->m_espo_ID;
					g_espo_ShareOffset = g_CurrentShareOffset;
					g_espo_Peer = g_PEER;
					g_espo_Owner = f_ShareContainer->m_espo_Owner;
					g_espo_Date = f_ShareContainer->m_espo_Date;
					g_espo_Score = f_ShareContainer->m_espo_Score;
					g_espo_Amount = f_ShareContainer->m_espo_Amount;
					g_espo_ECN_Amount = f_ShareContainer->m_espo_ECN_Amount;

					f_L = true;
					}
				else
					{
					if(g_PEER >= f_ShareContainer->m_espo_PeerCount)
						{
						g_PEER = f_ShareContainer->m_espo_PeerCount - 1;
						}

					if(g_CurrentShareOffset >= f_ShareContainer->m_espo_SharesOnPeerCount)
						{
						g_CurrentShareOffset = f_ShareContainer->m_espo_SharesOnPeerCount - 1;
						g_CurrentShareOffsetMAX = f_ShareContainer->m_espo_SharesOnPeerCount;

						if(g_CurrentShareOffset < 0)
							{
							g_CurrentShareOffset = 0;
							}
						}

					f_ShareContainer = Cag->ag_SelectPeerGraphExt(g_JobID, f_ServLay, f_LShare, g_CurrentShareOffset, g_PEER);

					int f_PeerCountB = f_ShareContainer->m_espo_PeerCount;

					if(f_PeerCountB > 0)
						{
						f_ShareID = f_ShareContainer->m_espo_ID;
						g_espo_ShareOffset = g_CurrentShareOffset;
						g_espo_Peer = g_PEER;
						g_espo_Owner = f_ShareContainer->m_espo_Owner;
						g_espo_Date = f_ShareContainer->m_espo_Date;
						g_espo_Score = f_ShareContainer->m_espo_Score;
						g_espo_Amount = f_ShareContainer->m_espo_Amount;
						g_espo_ECN_Amount = f_ShareContainer->m_espo_ECN_Amount;

						f_L = true;
						}
					else
						{
						f_ShareID = 0;
						g_espo_ShareOffset = 0;
						g_CurrentShareOffset = 0;
						g_espo_Peer = 0;
						g_PEER = 0;
						g_espo_Owner = "New Empty Block";
						g_espo_Date = "Empty";
						g_espo_Score = 0;
						g_espo_Amount = 0.0f;
						g_espo_ECN_Amount = 0.0f;

						f_L = false;
						}
					}
				}
			else  //RECEIVE espo info INPUT ShareID (f_LShare)
				{
				f_ShareID = f_LShare;
				g_espo_ShareOffset = f_ShareContainer->m_espo_ShareOffset;
				g_CurrentShareOffset = f_ShareContainer->m_espo_ShareOffset;
				g_espo_Peer = f_ShareContainer->m_espo_Peer;
				g_PEER = f_ShareContainer->m_espo_Peer;
				g_espo_Owner = f_ShareContainer->m_espo_Owner;
				g_espo_Date = f_ShareContainer->m_espo_Date;
				g_espo_Score = f_ShareContainer->m_espo_Score;
				g_espo_Amount = f_ShareContainer->m_espo_Amount;
				g_espo_ECN_Amount = f_ShareContainer->m_espo_ECN_Amount;

				f_L = true;
				}

			g_PEERMAX = f_ShareContainer->m_espo_PeerCount;
			g_CurrentShareOffsetMAX = f_ShareContainer->m_espo_SharesOnPeerCount;
			}
		else
			{
			f_ShareID = 0;
			g_espo_ShareOffset = 0;
			g_CurrentShareOffset = 0;
			g_espo_Peer = 0;
			g_PEER = 0;
			g_espo_Owner = "New Empty Block";
			g_espo_Date = "Empty";
			g_espo_Score = 0;
			g_espo_Amount = 0.0f;
			g_espo_ECN_Amount = 0.0f;

			f_L = false;
			}

		swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this, f_ShareContainer]()
			{
			int f_OwnPeerCount = f_ShareContainer->m_espo_TotalSharesOwnPeer;
			int f_OnPeerCount = f_ShareContainer->m_espo_SharesOnPeerCount;

			char* numbuf18 = ag_ClearChar(100);
			sprintf(numbuf18, "%i peers", f_ShareContainer->m_espo_PeerCount);
			std::string f_interim37 = numbuf18;
			delete numbuf18;

			allpeertextBlock().Text(StrUsingStr(f_interim37));

			char* numbuf15 = ag_ClearChar(100);
			sprintf(numbuf15, "%i own", f_OwnPeerCount);
			std::string f_interim27 = numbuf15;
			delete numbuf15;

			ownsharestextBlock().Text(StrUsingStr(f_interim27));

			int f_ShareCounting = f_ShareContainer->m_espo_TotalShares;

			char* numbuf25 = ag_ClearChar(100);
			sprintf(numbuf25, "%i on block", f_ShareCounting);
			std::string f_interim33 = numbuf25;
			delete numbuf25;

			alltotaltextBlock().Text(StrUsingStr(f_interim33));

			char* numbuf22 = ag_ClearChar(100);
			sprintf(numbuf22, "share count %i", f_ShareCounting);
			std::string f_interim32 = numbuf22;
			delete numbuf22;

			owntotaltextBlock().Text(StrUsingStr(f_interim32));

			g_ShareCount = f_ShareCounting;

			char* numbuf12 = ag_ClearChar(100);
			sprintf(numbuf12, "on #%i", g_espo_ShareOffset);
			std::string f_interim31 = numbuf12;
			delete numbuf12;

			owninfotextBlock().Text(StrUsingStr(f_interim31));

			char* numbuf7 = ag_ClearChar(100);
			sprintf(numbuf7, "on peer #%i", g_espo_Peer);
			std::string f_interim7 = numbuf7;
			delete numbuf7;

			ownpeertextBlock().Text(StrUsingStr(f_interim7));

			char* numbuf10 = ag_ClearChar(100);
			sprintf(numbuf10, "on share #%i", g_espo_ShareOffset);
			std::string f_interim47 = numbuf10;
			delete numbuf10;

			ownsharetextBlock().Text(StrUsingStr(f_interim47));

			ownerinfoBlock().Text(StrUsingStr(g_espo_Owner));

			char* numbuf57 = ag_ClearChar(100);
			sprintf(numbuf57, "%f", g_espo_Score);
			std::string f_interim58 = numbuf57;
			delete numbuf57;

			voteinfoBlock().Text(StrUsingStr(f_interim58));

			char* numbuf51 = ag_ClearChar(100);
			sprintf(numbuf51, "%.4f ECN", g_espo_Amount);
			std::string f_interim51 = numbuf51;
			delete numbuf51;

			pledgeinfoBlock().Text(StrUsingStr(f_interim51));

			char* numbuf59 = ag_ClearChar(100);
			sprintf(numbuf59, "%.8f ECN", g_espo_ECN_Amount);
			std::string f_interim59 = numbuf59;
			delete numbuf59;

			ecnpledgeinfoBlock().Text(StrUsingStr(f_interim59));

			dateinfoBlock().Text(StrUsingStr(g_espo_Date));
			});

		if(f_L == true)
			{
			g_ShareID = f_ShareID;

			char* query = ag_ClearChar(1024);
			::sprintf(query, "SELECT id, mark, assetid, assetofficeid, jobid, eslid, targetid, eslcode, difficulty, shareledger, jobledger, owner, bckred, bckgreen, bckblue, comid, price, jobboardid FROM share WHERE id = %i", f_ShareID);
			g_SafeL[f_ServLay]->acSelectCommand(query, false, false);
			delete query;

			int f_ShareEXCNT = 0;

			if(g_Schedular[f_ServLay]->acEntry(0)[0].at(0) == '0')
				{
				f_ShareEXCNT = 0;
				}
			else
				{
				f_ShareEXCNT = g_Schedular[f_ServLay]->acEntrySize();
				}

			if(f_ShareEXCNT >= 1)
				{
				g_CurrentShareID = atoi(g_Schedular[f_ServLay]->acEntry(0)[0].c_str());

				g_CurrentComID = atoi(g_Schedular[f_ServLay]->acEntry(0)[15].c_str());

				ag_FreshOn<int>(g_Wallet->m_vec_comid, m_IDX, g_CurrentComID);

				g_CurrentSharePrice = atof(g_Schedular[f_ServLay]->acEntry(0)[16].c_str());

				ag_FreshOn<float>(g_Wallet->m_vec_price, m_IDX, g_CurrentSharePrice);

				Cube::BiVector f_BCK(atof(g_Schedular[f_ServLay]->acEntry(0)[12].c_str()), atof(g_Schedular[f_ServLay]->acEntry(0)[13].c_str()), atof(g_Schedular[f_ServLay]->acEntry(0)[14].c_str()));

				std::string f_ESL_Code = g_Schedular[f_ServLay]->acEntry(0)[7];

				ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, atoi(g_Schedular[f_ServLay]->acEntry(0)[17].c_str()));

				char* cubequery = ag_ClearChar(3000);
				::sprintf(cubequery, "SELECT id, vert1x, vert1y, vert1z, vert2x, vert2y, vert2z, vert3x, vert3y, vert3z, vert4x, vert4y, vert4z, vert5x, vert5y, vert5z, vert6x, vert6y, vert6z, vert7x, vert7y, vert7z, vert8x, vert8y, vert8z, vert1r, vert1g, vert1b, vert2r, vert2g, vert2b, vert3r, vert3g, vert3b, vert4r, vert4g, vert4b, vert5r, vert5g, vert5b, vert6r, vert6g, vert6b, vert7r, vert7g, vert7b, vert8r, vert8g, vert8b, shareid, jobid, eslid, targetid, eslcode, difficulty FROM cube WHERE shareid = %i ORDER BY eslid ASC#", f_ShareID);
				g_SafeL[f_ServLay]->acSelectCommand(cubequery, false, false);
				delete cubequery;

				int f_adCount = 0;

				if(g_Schedular[f_ServLay]->acEntry(0)[0].at(0) == '0')
					{
					f_adCount = 0;
					}
				else
					{
					f_adCount = g_Schedular[f_ServLay]->acEntrySize();
					}

				//ECN::f_adCount
				//...
				//ECN::Form Hesh

				g_BicycleContainer[0]->m_ADMAX = f_adCount;
				g_BicycleContainer[0]->m_ADHIGH = f_adCount;
				g_BicycleContainer[0]->m_ADLOW = f_adCount;

				//ECN::g_CountLM
				//...
				//ECN::FRECOM

				int f_CountLM = atoi(g_Schedular[f_ServLay]->acEntry(0)[52].c_str());

				g_CountLM = f_CountLM;

				ag_StatusLive(f_ref_CurrentPath, "f_Heshr");
				std::shared_ptr<Cube::CubeHESH> f_Heshr = ::std::make_shared_reflect<Cube::CubeHESH>(f_adCount, f_adCount, f_adCount, f_CountLM);

				for(int f_Int = 0; f_Int < f_adCount; f_Int++)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_Bike");
					std::shared_ptr<Cube::CubeBicycle> f_Bike = ::std::make_shared_reflect<Cube::CubeBicycle>();

					f_Bike->acClear();

					for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_Vector");
						std::shared_ptr<Cube::BiVector> f_Vector = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[1 + (f_Int2 * 3)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 1)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 2)].c_str()));

						f_Bike->vec_Vertex.push_back(f_Vector);
						}

					f_Bike->vec_Color.clear();

					for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_Color");
						std::shared_ptr<Cube::BiVector> f_Color = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[25 + (f_Int3 * 3)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 1)].c_str()), (float)atof(g_Schedular[f_ServLay]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 2)].c_str()));

						f_Bike->vec_Color.push_back(f_Color);
						}

#ifdef TEST_VERIFY_SCP_BUILD_ECOM
					ag_StatusLive(f_ref_CurrentPath, "f_Element");
					std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Bike);

					f_Collection->m_vec_Element.push_back(f_Element);
					f_Collection->m_idx_vec_Element++;
#endif

					f_Heshr->vec_Bicycle.push_back(f_Bike);

#ifdef CHK_ELEMENT_INDEX
					int f_CH = atoi(g_Schedular[f_ServLay]->acEntry(f_Int][51].c_str());

					if(f_CH != f_Int)
						{
						throw;
						}
#endif
					}

				  ////////////
				 // HESH   //
				//        //
				int f_PortCNTR = f_Heshr->m_adIndex.size();

				while(f_Heshr->m_adIndex.size() < f_adCount)
					{
					f_Heshr->m_adIndex.push_back(f_PortCNTR);
					f_PortCNTR++;
					}

				f_Heshr->m_bckred = f_BCK.m_X;
				f_Heshr->m_bckgreen = f_BCK.m_Y;
				f_Heshr->m_bckblue = f_BCK.m_Z;

				ag_FreshOn<float>(g_Wallet->m_vec_bckred, m_IDX, f_Heshr->m_bckred);
				ag_FreshOn<float>(g_Wallet->m_vec_bckgreen, m_IDX, f_Heshr->m_bckgreen);
				ag_FreshOn<float>(g_Wallet->m_vec_bckblue, m_IDX, f_Heshr->m_bckblue);

				f_Heshr->ac_IsOK();

				g_currentLaunchTypeName = f_ESL_Code;

				int f_Type = ag_FindTypefromCode(f_ESL_Code);

				g_currentLaunchType = f_Type;

				g_currentLaunchPrefix = ag_FindPrefixfromCode(f_ESL_Code);

				g_currentLaunch = true;

				//g_Type Switch
				switch(f_Type)
					{
					case 0:
						{
						g_Found_Msg = 15;
						g_Found_Text = "[" + g_currentLaunchPrefix + "]";

						ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, ecoin_PledgeType::ecoin_Pledge_Off);
						}break;

					case 1:
						{
						g_Found_Msg = 15;
						g_Found_Text = "[" + g_currentLaunchPrefix + "]";

						ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, ecoin_PledgeType::ecoin_Pledge_Off);
						}break;

					case 2:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_1");
						g_Target_1 = ::std::make_shared_reflect<classTarget>(f_Heshr);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_2");
						g_Target_2 = ::std::make_shared_reflect<classTarget>(f_Heshr);

						if((g_Type == 0) || (g_Type == 1))
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(2)[" + g_currentLaunchPrefix + "]";
							
							//JOB Mainly
							char* jobquery = ag_ClearChar(512);
							::sprintf(jobquery, "SELECT id, blocktype, eslcode, pledgetype, pledgemax, targetbreach, owner, scoremax, markmax, markmin, reward, rewardid, startbreach, blockid, dated FROM job WHERE id = %i ORDER BY dated DESC LIMIT 1", g_Wallet->m_vec_jobboardid[m_IDX]);
							g_SafeL[0]->acSelectCommand(jobquery, 2, false);
							delete jobquery;
						
							int f_jobLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobLCount = 0;
								}
							else
								{
								f_jobLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobLCount
							if(f_jobLCount == 1)
								{
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, atof(g_Schedular[0]->acEntry(0)[7].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, atof(g_Schedular[0]->acEntry(0)[8].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, atof(g_Schedular[0]->acEntry(0)[9].c_str()));
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, atoi(g_Schedular[0]->acEntry(0)[3].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, atoi(g_Schedular[0]->acEntry(0)[4].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[5].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[12].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[13].c_str()));
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);

								if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
									{
									std::vector<float> f_vec_jobvar_value;
									std::vector<std::string> f_vec_jobvar_groupname;
									std::vector<std::string> f_vec_jobvar_name;
									std::vector<int> f_vec_jobvar_index;
									std::vector<int> f_vec_jobvarid;
									std::vector<bool> f_vec_jobvar_save;
									std::vector<bool> f_vec_jobvar_textupdate;

									f_vec_jobvar_value.push_back(18.57f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("MATCH_MIXIN");
									f_vec_jobvar_index.push_back(0);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(0.0143f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("MATCH_THRESH");
									f_vec_jobvar_index.push_back(1);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(1.341f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("MATCH_THRESH_UP");
									f_vec_jobvar_index.push_back(2);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(12.55f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("COMPARE_QUALITY");
									f_vec_jobvar_index.push_back(3);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(33.7357f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("COMPARE_THRESH");
									f_vec_jobvar_index.push_back(4);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(98.0f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("LOWTON_STORAGE");
									f_vec_jobvar_index.push_back(5);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
									g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
									g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
									g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
									g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
									g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
									g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

									g_Wallet->m_vec_jobvar_current_index.push_back(0);
									}
								else
									{
									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(18.57f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("MATCH_MIXIN");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(0.0143f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("MATCH_THRESH");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(1);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(1.341f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("MATCH_THRESH_UP");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(2);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(12.55f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("COMPARE_QUALITY");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(3);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(33.7357f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("COMPARE_THRESH");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(4);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(98.0f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("LOWTON_STORAGE");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(5);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
									}
								}

							char* jobvarquery = ag_ClearChar(512);
							::sprintf(jobvarquery, "SELECT id, name, groupname, value, dated FROM jobvar WHERE jobid = %i ORDER BY dated DESC", atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
							g_SafeL[0]->acSelectCommand(jobvarquery, 2, false);
							delete jobvarquery;
						
							int f_jobvarLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobvarLCount = 0;
								}
							else
								{
								f_jobvarLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobvarLCount
							if(f_jobvarLCount > 0)
								{
								if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
									{
									std::vector<float> f_vec_jobvar_value;
									std::vector<std::string> f_vec_jobvar_groupname;
									std::vector<std::string> f_vec_jobvar_name;
									std::vector<int> f_vec_jobvar_index;
									std::vector<int> f_vec_jobvarid;
									std::vector<bool> f_vec_jobvar_save;
									std::vector<bool> f_vec_jobvar_textupdate;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										f_vec_jobvar_value.push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										f_vec_jobvar_groupname.push_back(g_Schedular[0]->acEntry(0)[2]);
										f_vec_jobvar_name.push_back(g_Schedular[0]->acEntry(0)[1]);
										f_vec_jobvar_index.push_back(f_Jet);
										f_vec_jobvarid.push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										f_vec_jobvar_save.push_back(false);
										f_vec_jobvar_textupdate.push_back(false);
										}

									g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
									g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
									g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
									g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
									g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
									g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
									g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

									g_Wallet->m_vec_jobvar_current_index.push_back(0);
									}
								else
									{
									g_Wallet->m_vec_jobvar_value[m_IDX].clear();
									g_Wallet->m_vec_jobvar_groupname[m_IDX].clear();
									g_Wallet->m_vec_jobvar_name[m_IDX].clear();
									g_Wallet->m_vec_jobvar_index[m_IDX].clear();
									g_Wallet->m_vec_jobvarid[m_IDX].clear();
									g_Wallet->m_vec_jobvar_save[m_IDX].clear();
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].clear();

									g_Wallet->m_vec_jobvar_current_index[m_IDX] = 0;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										g_Wallet->m_vec_jobvar_value[m_IDX].push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back(g_Schedular[0]->acEntry(0)[2]);
										g_Wallet->m_vec_jobvar_name[m_IDX].push_back(g_Schedular[0]->acEntry(0)[1]);
										g_Wallet->m_vec_jobvar_index[m_IDX].push_back(f_Jet);
										g_Wallet->m_vec_jobvarid[m_IDX].push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
										g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
										}
									}

								acRefreshJob();
								}
							}
						else
							{
							g_Type = f_Type;
							}
						}break;

					case 3:
						{	////////////
						   // Load...
						  // [FRECOM]
						 // Result
						ag_StatusLive(f_ref_CurrentPath, "f_classTarget_Ecom");
						std::shared_ptr<classTarget_Ecom> f_classTarget_Ecom = std::make_shared_reflect<classTarget_Ecom>();

						ag_StatusLive(f_ref_CurrentPath, "f_classTarget_Ecom_B");
						std::shared_ptr<classTarget_Ecom> f_classTarget_Ecom_B = std::make_shared_reflect<classTarget_Ecom>();

#ifdef TEST_VERIFY_SCP_BUILD_ECOM
						ag_StatusLive(f_ref_CurrentPath, "g_classLMap");
						g_classLMap = std::make_shared_reflect<classLMap>(m_IDX);

						g_ElementDivisor.push_back(0);
						g_ElementDivisorInt.push_back(0);

						ag_StatusLive(f_ref_CurrentPath, "g_classLMap->m_SchemaRef");
						g_classLMap->m_SchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
						ag_StatusLive(f_ref_CurrentPath, "g_classLMap->m_SaveSchemaRef");
						g_classLMap->m_SaveSchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
						ag_StatusLive(f_ref_CurrentPath, "g_classLMap->m_PushSchemaRef");
						g_classLMap->m_PushSchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
						g_classLMap->m_SchemaMeasureIndex.push_back(0);
						g_classLMap->m_PushMeasureIndex.push_back(0);
						g_classLMap->m_CPS_Result.push_back(CPS_SCAN);

						std::shared_ptr<Qcom> f_com = g_classLMap->acGen_com_FromEcom(::g_QcomManager->m_Qcom, 0, g_BicycleContainer[0]->m_ADMAX, g_BicycleContainer[0]->m_ADMAX, 1, f_classTarget_Ecom);

						g_classLMap->acRangeAD();

						g_Result = g_classLMap->acFinalCompute(f_Collection, g_ElementDivisor.size() - 1, false);

						g_classLMap->m_SchemaRef.pop_back();
						g_classLMap->m_SaveSchemaRef.pop_back();
						g_classLMap->m_PushSchemaRef.pop_back();
						g_classLMap->m_SchemaMeasureIndex.pop_back();
						g_classLMap->m_PushMeasureIndex.pop_back();
						g_classLMap->m_CPS_Result.pop_back();

						g_ElementDivisor.pop_back();
						g_ElementDivisorInt.pop_back();

						g_Found_Msg = 20;

						char* f_Char = ag_ClearChar(256);

						::sprintf(f_Char, "[%s] Load-com = %i", g_currentLaunchPrefix.c_str(), (int)g_Result);

						g_Found_Text = std::string(f_Char);

						delete f_Char;
#else

						g_ElementDivisor.push_back(0);
						g_ElementDivisorInt.push_back(0);

						ag_StatusLive(f_ref_CurrentPath, "f_classTarget_Ecom->m_SchemaRef");
						f_classTarget_Ecom->m_SchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));

						f_classTarget_Ecom->acPrepare_Lense();

						std::shared_ptr<Qcom> f_com = f_classTarget_Ecom->acGen_com_FromHesh(f_Heshr, 0, f_Heshr->m_ADMAX, f_Heshr->m_ADMAX, 1, f_classTarget_Ecom_B);

						f_classTarget_Ecom->m_SchemaRef.pop_back();

						g_ElementDivisor.pop_back();
						g_ElementDivisorInt.pop_back();

#if 0
						f_com->m_owner = g_Wallet->GetAdr();

						f_com->m_position->m_X = Cube::g_QcomManager->m_current_X;
						f_com->m_position->m_Y = Cube::g_QcomManager->m_current_Y;
						f_com->m_position->m_Z = 0.0;

						::g_QcomManager->m_Qcom->m_vec_Qcom.push_back(f_com);
						::g_QcomManager->m_vec_Qcom.push_back(f_com);
#endif

						g_Found_Msg = 20;

						g_Type = f_Type;

						char* f_Char = ag_ClearChar(256);

						::sprintf(f_Char, "[%s]LoadCom-(%i)", g_currentLaunchPrefix.c_str(), (int)f_Heshr->m_ADMAX);

						g_Found_Text = std::string(f_Char);

						delete f_Char;

						g_ShuttleCom = f_com;

						swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this, f_com]()
							{
							eventsubjectBlock().Text(StrUsingStr(f_com->m_name));

							eventsourcetextBlock().Text(StrUsingStr(std::string("ShareShop")));

							eventtypetextBlock().Text(StrUsingStr(std::string("FRECOM: EXCom")));

							char* f_CharP = ag_ClearChar(256);

							sprintf(f_CharP, "%.2f", f_com->m_Cost);

							std::string f_CostString = "Com Price ";

							f_CostString += f_CharP;

							delete f_CharP;

							eventCollectiveComDeclaretextBlock().Text(StrUsingStr(f_CostString));

							//FIXME:: Add amount paid textblock

							char* f_Char1 = ag_ClearChar(256);

							sprintf(f_Char1, "%i Count Inputs %i Count Outputs", (int)f_com->m_vec_Input.size(), (int)f_com->m_vec_Output.size());

							std::string f_INOUTString = f_Char1;

							delete f_Char1;

							eventCollectivePowerFactorTextAtextBlock().Text(StrUsingStr(f_INOUTString));

							char* f_Char2 = ag_ClearChar(256);

							if(f_com->m_genScript != nullptr)
								{
								sprintf(f_Char2, "%i Count ESL Functions %i Line Count GenScript", (int)f_com->m_vec_ESLFunction.size(), (int)f_com->m_genScript->m_vec_InitLineOrdered.size());
								}
							else
								{
								sprintf(f_Char2, "%i Count ESL Functions No GenScript", (int)f_com->m_vec_ESLFunction.size());
								}

							std::string f_FunctionString = f_Char2;

							delete f_Char2;

							eventCollectivePowerFactorTextBtextBlock().Text(StrUsingStr(f_FunctionString));

							eventsourcetextBlock().Text(StrUsingStr(std::string("Share")));
							eventtypetextBlock().Text(StrUsingStr(g_currentLaunchPrefix));

							eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);

							//close shop temporarily
							shopStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
							});
#endif
						}break;

					case 4:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_3");
						g_Target_3 = ::std::make_shared_reflect<classTarget_Ecom>();

						g_Target_3->acFromHesh(f_Heshr, g_Target_3);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_4");
						g_Target_4 = ::std::make_shared_reflect<classTarget_Ecom>();

						g_Target_4->acFromHesh(f_Heshr, g_Target_4);

						if(g_Type == 3)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(4)[" + g_currentLaunchPrefix + "]";

							//JOB Mainly
							char* jobquery = ag_ClearChar(512);
							::sprintf(jobquery, "SELECT id, blocktype, eslcode, pledgetype, pledgemax, targetbreach, owner, scoremax, markmax, markmin, reward, rewardid, startbreach, blockid, dated FROM job WHERE id = %i ORDER BY dated DESC LIMIT 1", g_Wallet->m_vec_jobboardid[m_IDX]);
							g_SafeL[0]->acSelectCommand(jobquery, 2, false);
							delete jobquery;
						
							int f_jobLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobLCount = 0;
								}
							else
								{
								f_jobLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobLCount
							if(f_jobLCount > 0)
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, atof(g_Schedular[0]->acEntry(0)[7].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, atof(g_Schedular[0]->acEntry(0)[8].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, atof(g_Schedular[0]->acEntry(0)[9].c_str()));
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, atoi(g_Schedular[0]->acEntry(0)[3].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, atoi(g_Schedular[0]->acEntry(0)[4].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[5].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[12].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[13].c_str()));
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}
							else
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, 0);
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, 0);
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, 0);
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}

							char* jobvarquery = ag_ClearChar(512);
							::sprintf(jobvarquery, "SELECT id, name, groupname, value, dated FROM jobvar WHERE jobid = %i ORDER BY dated DESC", atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
							g_SafeL[0]->acSelectCommand(jobvarquery, 2, false);
							delete jobvarquery;
						
							int f_jobvarLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobvarLCount = 0;
								}
							else
								{
								f_jobvarLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobvarLCount
							if(f_jobvarLCount > 0)
								{
								if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
									{
									std::vector<float> f_vec_jobvar_value;
									std::vector<std::string> f_vec_jobvar_groupname;
									std::vector<std::string> f_vec_jobvar_name;
									std::vector<int> f_vec_jobvar_index;
									std::vector<int> f_vec_jobvarid;
									std::vector<bool> f_vec_jobvar_save;
									std::vector<bool> f_vec_jobvar_textupdate;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										f_vec_jobvar_value.push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										f_vec_jobvar_groupname.push_back(g_Schedular[0]->acEntry(0)[2]);
										f_vec_jobvar_name.push_back(g_Schedular[0]->acEntry(0)[1]);
										f_vec_jobvar_index.push_back(f_Jet);
										f_vec_jobvarid.push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										f_vec_jobvar_save.push_back(false);
										f_vec_jobvar_textupdate.push_back(false);
										}

									g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
									g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
									g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
									g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
									g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
									g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
									g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

									g_Wallet->m_vec_jobvar_current_index.push_back(0);
									}
								else
									{
									g_Wallet->m_vec_jobvar_value[m_IDX].clear();
									g_Wallet->m_vec_jobvar_groupname[m_IDX].clear();
									g_Wallet->m_vec_jobvar_name[m_IDX].clear();
									g_Wallet->m_vec_jobvar_index[m_IDX].clear();
									g_Wallet->m_vec_jobvarid[m_IDX].clear();
									g_Wallet->m_vec_jobvar_save[m_IDX].clear();
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].clear();

									g_Wallet->m_vec_jobvar_current_index[m_IDX] = 0;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										g_Wallet->m_vec_jobvar_value[m_IDX].push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back(g_Schedular[0]->acEntry(0)[2]);
										g_Wallet->m_vec_jobvar_name[m_IDX].push_back(g_Schedular[0]->acEntry(0)[1]);
										g_Wallet->m_vec_jobvar_index[m_IDX].push_back(f_Jet);
										g_Wallet->m_vec_jobvarid[m_IDX].push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
										g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
										}
									}

								acRefreshJob();
								}
							}
						else
							{
							g_Type = f_Type;
							}
						}break;

					case 6:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_5");
						g_Target_5 = ::std::make_shared_reflect<classTarget_ESL_Script>();

						g_Target_5->acFromHesh(f_Heshr, g_Target_5);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_6");
						g_Target_6 = ::std::make_shared_reflect<classTarget_ESL_Script>();

						g_Target_6->acFromHesh(f_Heshr, g_Target_6);

						if(g_Type == 5)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(6)[" + g_currentLaunchPrefix + "]";

							//JOB Mainly
							char* jobquery = ag_ClearChar(512);
							::sprintf(jobquery, "SELECT id, blocktype, eslcode, pledgetype, pledgemax, targetbreach, owner, scoremax, markmax, markmin, reward, rewardid, startbreach, blockid, dated FROM job WHERE id = %i ORDER BY dated DESC LIMIT 1", g_Wallet->m_vec_jobboardid[m_IDX]);
							g_SafeL[0]->acSelectCommand(jobquery, 2, false);
							delete jobquery;
						
							int f_jobLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobLCount = 0;
								}
							else
								{
								f_jobLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobLCount
							if(f_jobLCount > 0)
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, atof(g_Schedular[0]->acEntry(0)[7].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, atof(g_Schedular[0]->acEntry(0)[8].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, atof(g_Schedular[0]->acEntry(0)[9].c_str()));
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, atoi(g_Schedular[0]->acEntry(0)[3].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, atoi(g_Schedular[0]->acEntry(0)[4].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[5].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[12].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[13].c_str()));
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}
							else
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, 0);
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, 0);
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, 0);
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}

							char* jobvarquery = ag_ClearChar(512);
							::sprintf(jobvarquery, "SELECT id, name, groupname, value, dated FROM jobvar WHERE jobid = %i ORDER BY dated DESC", atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
							g_SafeL[0]->acSelectCommand(jobvarquery, 2, false);
							delete jobvarquery;
						
							int f_jobvarLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobvarLCount = 0;
								}
							else
								{
								f_jobvarLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobvarLCount
							if(f_jobvarLCount > 0)
								{
								if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
									{
									std::vector<float> f_vec_jobvar_value;
									std::vector<std::string> f_vec_jobvar_groupname;
									std::vector<std::string> f_vec_jobvar_name;
									std::vector<int> f_vec_jobvar_index;
									std::vector<int> f_vec_jobvarid;
									std::vector<bool> f_vec_jobvar_save;
									std::vector<bool> f_vec_jobvar_textupdate;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										f_vec_jobvar_value.push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										f_vec_jobvar_groupname.push_back(g_Schedular[0]->acEntry(0)[2]);
										f_vec_jobvar_name.push_back(g_Schedular[0]->acEntry(0)[1]);
										f_vec_jobvar_index.push_back(f_Jet);
										f_vec_jobvarid.push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										f_vec_jobvar_save.push_back(false);
										f_vec_jobvar_textupdate.push_back(false);
										}

									g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
									g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
									g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
									g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
									g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
									g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
									g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

									g_Wallet->m_vec_jobvar_current_index.push_back(0);
									}
								else
									{
									g_Wallet->m_vec_jobvar_value[m_IDX].clear();
									g_Wallet->m_vec_jobvar_groupname[m_IDX].clear();
									g_Wallet->m_vec_jobvar_name[m_IDX].clear();
									g_Wallet->m_vec_jobvar_index[m_IDX].clear();
									g_Wallet->m_vec_jobvarid[m_IDX].clear();
									g_Wallet->m_vec_jobvar_save[m_IDX].clear();
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].clear();

									g_Wallet->m_vec_jobvar_current_index[m_IDX] = 0;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										g_Wallet->m_vec_jobvar_value[m_IDX].push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back(g_Schedular[0]->acEntry(0)[2]);
										g_Wallet->m_vec_jobvar_name[m_IDX].push_back(g_Schedular[0]->acEntry(0)[1]);
										g_Wallet->m_vec_jobvar_index[m_IDX].push_back(f_Jet);
										g_Wallet->m_vec_jobvarid[m_IDX].push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
										g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
										}
									}

								acRefreshJob();
								}
							}
						else
							{
							g_Type = f_Type;
							}
						}break;

					case 8:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_7");
						g_Target_7 = ::std::make_shared_reflect<classTarget_Generation_Script>();

						g_Target_7->acFromHesh(f_Heshr, g_Target_7);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_8");
						g_Target_8 = ::std::make_shared_reflect<classTarget_Generation_Script>();

						g_Target_8->acFromHesh(f_Heshr, g_Target_8);

						if(g_Type == 7)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(8)[" + g_currentLaunchPrefix + "]";

							//JOB Mainly
							char* jobquery = ag_ClearChar(512);
							::sprintf(jobquery, "SELECT id, blocktype, eslcode, pledgetype, pledgemax, targetbreach, owner, scoremax, markmax, markmin, reward, rewardid, startbreach, blockid, dated FROM job WHERE id = %i ORDER BY dated DESC LIMIT 1", g_Wallet->m_vec_jobboardid[m_IDX]);
							g_SafeL[0]->acSelectCommand(jobquery, 2, false);
							delete jobquery;
						
							int f_jobLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobLCount = 0;
								}
							else
								{
								f_jobLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobLCount
							if(f_jobLCount > 0)
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, atof(g_Schedular[0]->acEntry(0)[7].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, atof(g_Schedular[0]->acEntry(0)[8].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, atof(g_Schedular[0]->acEntry(0)[9].c_str()));
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, atoi(g_Schedular[0]->acEntry(0)[3].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, atoi(g_Schedular[0]->acEntry(0)[4].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[5].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[12].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[13].c_str()));
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}
							else
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, 0);
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, 0);
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, 0);
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}

							char* jobvarquery = ag_ClearChar(512);
							::sprintf(jobvarquery, "SELECT id, name, groupname, value, dated FROM jobvar WHERE jobid = %i ORDER BY dated DESC", atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
							g_SafeL[0]->acSelectCommand(jobvarquery, 2, false);
							delete jobvarquery;
						
							int f_jobvarLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobvarLCount = 0;
								}
							else
								{
								f_jobvarLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobvarLCount
							if(f_jobvarLCount > 0)
								{
								if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
									{
									std::vector<float> f_vec_jobvar_value;
									std::vector<std::string> f_vec_jobvar_groupname;
									std::vector<std::string> f_vec_jobvar_name;
									std::vector<int> f_vec_jobvar_index;
									std::vector<int> f_vec_jobvarid;
									std::vector<bool> f_vec_jobvar_save;
									std::vector<bool> f_vec_jobvar_textupdate;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										f_vec_jobvar_value.push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										f_vec_jobvar_groupname.push_back(g_Schedular[0]->acEntry(0)[2]);
										f_vec_jobvar_name.push_back(g_Schedular[0]->acEntry(0)[1]);
										f_vec_jobvar_index.push_back(f_Jet);
										f_vec_jobvarid.push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										f_vec_jobvar_save.push_back(false);
										f_vec_jobvar_textupdate.push_back(false);
										}

									g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
									g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
									g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
									g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
									g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
									g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
									g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

									g_Wallet->m_vec_jobvar_current_index.push_back(0);
									}
								else
									{
									g_Wallet->m_vec_jobvar_value[m_IDX].clear();
									g_Wallet->m_vec_jobvar_groupname[m_IDX].clear();
									g_Wallet->m_vec_jobvar_name[m_IDX].clear();
									g_Wallet->m_vec_jobvar_index[m_IDX].clear();
									g_Wallet->m_vec_jobvarid[m_IDX].clear();
									g_Wallet->m_vec_jobvar_save[m_IDX].clear();
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].clear();

									g_Wallet->m_vec_jobvar_current_index[m_IDX] = 0;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										g_Wallet->m_vec_jobvar_value[m_IDX].push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back(g_Schedular[0]->acEntry(0)[2]);
										g_Wallet->m_vec_jobvar_name[m_IDX].push_back(g_Schedular[0]->acEntry(0)[1]);
										g_Wallet->m_vec_jobvar_index[m_IDX].push_back(f_Jet);
										g_Wallet->m_vec_jobvarid[m_IDX].push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
										g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
										}
									}

								acRefreshJob();
								}
							}
						else
							{
							g_Type = f_Type;
							}
						}break;

					case 10:
						{
						ag_StatusLive(f_ref_CurrentPath, "g_Target_9");
						g_Target_9 = ::std::make_shared_reflect<classTarget_JScript>();

						g_Target_9->acFromHesh(f_Heshr, g_Target_9);

						ag_StatusLive(f_ref_CurrentPath, "g_Target_10");
						g_Target_10 = ::std::make_shared_reflect<classTarget_JScript>();

						g_Target_10->acFromHesh(f_Heshr, g_Target_10);

						if(g_Type == 9)
							{
							g_Found_Msg = 10;
							g_Found_Text = "Correct Target Loaded!(10)[" + g_currentLaunchPrefix + "]";

							//JOB Mainly
							char* jobquery = ag_ClearChar(512);
							::sprintf(jobquery, "SELECT id, blocktype, eslcode, pledgetype, pledgemax, targetbreach, owner, scoremax, markmax, markmin, reward, rewardid, startbreach, blockid, dated FROM job WHERE id = %i ORDER BY dated DESC LIMIT 1", g_Wallet->m_vec_jobboardid[m_IDX]);
							g_SafeL[0]->acSelectCommand(jobquery, 2, false);
							delete jobquery;
						
							int f_jobLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobLCount = 0;
								}
							else
								{
								f_jobLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobLCount
							if(f_jobLCount > 0)
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, atof(g_Schedular[0]->acEntry(0)[7].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, atof(g_Schedular[0]->acEntry(0)[8].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, atof(g_Schedular[0]->acEntry(0)[9].c_str()));
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, atoi(g_Schedular[0]->acEntry(0)[3].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, atoi(g_Schedular[0]->acEntry(0)[4].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[5].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[12].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[13].c_str()));
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}
							else
								{
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, 0);
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, 0);
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, 0);
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, 0);
								ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_ESL_Code);
								}

							char* jobvarquery = ag_ClearChar(512);
							::sprintf(jobvarquery, "SELECT id, name, groupname, value, dated FROM jobvar WHERE jobid = %i ORDER BY dated DESC", atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
							g_SafeL[0]->acSelectCommand(jobvarquery, 2, false);
							delete jobvarquery;
						
							int f_jobvarLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobvarLCount = 0;
								}
							else
								{
								f_jobvarLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobvarLCount
							if(f_jobvarLCount > 0)
								{
								if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
									{
									std::vector<float> f_vec_jobvar_value;
									std::vector<std::string> f_vec_jobvar_groupname;
									std::vector<std::string> f_vec_jobvar_name;
									std::vector<int> f_vec_jobvar_index;
									std::vector<int> f_vec_jobvarid;
									std::vector<bool> f_vec_jobvar_save;
									std::vector<bool> f_vec_jobvar_textupdate;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										f_vec_jobvar_value.push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										f_vec_jobvar_groupname.push_back(g_Schedular[0]->acEntry(0)[2]);
										f_vec_jobvar_name.push_back(g_Schedular[0]->acEntry(0)[1]);
										f_vec_jobvar_index.push_back(f_Jet);
										f_vec_jobvarid.push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										f_vec_jobvar_save.push_back(false);
										f_vec_jobvar_textupdate.push_back(false);
										}

									g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
									g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
									g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
									g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
									g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
									g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
									g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

									g_Wallet->m_vec_jobvar_current_index.push_back(0);
									}
								else
									{
									g_Wallet->m_vec_jobvar_value[m_IDX].clear();
									g_Wallet->m_vec_jobvar_groupname[m_IDX].clear();
									g_Wallet->m_vec_jobvar_name[m_IDX].clear();
									g_Wallet->m_vec_jobvar_index[m_IDX].clear();
									g_Wallet->m_vec_jobvarid[m_IDX].clear();
									g_Wallet->m_vec_jobvar_save[m_IDX].clear();
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].clear();

									g_Wallet->m_vec_jobvar_current_index[m_IDX] = 0;

									for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
										{
										g_Wallet->m_vec_jobvar_value[m_IDX].push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
										g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back(g_Schedular[0]->acEntry(0)[2]);
										g_Wallet->m_vec_jobvar_name[m_IDX].push_back(g_Schedular[0]->acEntry(0)[1]);
										g_Wallet->m_vec_jobvar_index[m_IDX].push_back(f_Jet);
										g_Wallet->m_vec_jobvarid[m_IDX].push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
										g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
										g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
										}
									}

								acRefreshJob();
								}
							}
						else
							{
							g_Type = f_Type;
							}
						}break;
					}

				if(g_currentLaunch == true)
					{
					g_Once = true;
					g_TargetedHesh = f_Heshr;
					g_RenderHesh = true;

					OnLoadPledgeStack();

					if(pledgeStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
						{
						pledgeresultstextBlock().Text(L"...Enter amount(s) above and click synchronize...");
						}
					}
				}
			else
				{
				//ECN::requested share doesnt exist shareid g_ShareID
				}
			}
		else
			{
			//ECN::Zero shares on job 
			}
	}

	void SecondaryAppWindowPageDX::onClickPrevShare(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		  /////////////
		 //
		// Increment
		g_CurrentShareOffset--;

		if(g_CurrentShareOffset < 0)
			{
			g_CurrentShareOffset = 0;
			}

		  /////////////
		 //
		// LoadShare
		acLoadShare();
	}

	void SecondaryAppWindowPageDX::onClickNextShare(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		  /////////////
		 //
		// Increment
		g_CurrentShareOffset++;

		if(g_CurrentShareOffset >= g_CurrentShareOffsetMAX)
			{
			g_CurrentShareOffset = g_CurrentShareOffsetMAX - 1;
			}

		if(g_CurrentShareOffset < 0)
			{
			g_CurrentShareOffset = 0;
			}

		  /////////////
		 //
		// LoadShare
		acLoadShare();
	}

	void SecondaryAppWindowPageDX::onClickPeer(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_PEER++;

		if(g_PEER >= g_PEERMAX)
			{
			g_PEER = g_PEERMAX - 1;
			}

		g_CurrentShareOffset = 0;

		  /////////////
		 //
		// LoadShare
		acLoadShare();
	}

	void SecondaryAppWindowPageDX::onClickPeerMinus(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_PEER--;

		if(g_PEER < 0)
			{
			g_PEER = 0;
			}

		g_CurrentShareOffset = 0;
	 
		  /////////////
		 //
		// LoadShare
		acLoadShare();
	}

	void SecondaryAppWindowPageDX::onClickMilliPeer(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_CurrentShareOffset += 500;

		if(g_CurrentShareOffset >= g_CurrentShareOffsetMAX)
			{
			g_CurrentShareOffset = g_CurrentShareOffsetMAX - (g_CurrentShareOffset - g_CurrentShareOffsetMAX);
			}

		while(g_CurrentShareOffset < 0)
			{
			g_CurrentShareOffset *= -1;
			}

		  /////////////
		 //
		// LoadShare
		acLoadShare();
	}

	void SecondaryAppWindowPageDX::onClickMilliPeerMinus(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_CurrentShareOffset -= 500;

		while(g_CurrentShareOffset < 0)
			{
			g_CurrentShareOffset *= -1;
			}

		  /////////////
		 //
		// LoadShare
		acLoadShare();
	}

	void SecondaryAppWindowPageDX::onClickLookAt(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_VIEWING;

			lookatButton().Content(box_value(L"CLICK\n4 shares"));

			eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			currentStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_VIEWING;

			eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

			lookatButton().Content(box_value(L"CLICK\n4 viewing"));

			OnRefreshEslCodeStack();
			}
	}

	void SecondaryAppWindowPageDX::OnRefreshEslCodeStack(void)
	{
		eslcoderesulttextBlock().Text(L"Please enter Tag, Name and description. Limit total characters 3000.");

		ag_Freshanon(g_Wallet->m_vec_targetbreach, m_IDX, 0);
		ag_Freshanon(g_Wallet->m_vec_maxpledge, m_IDX, 0);
		ag_Freshanon(g_Wallet->m_vec_scoremax, m_IDX, 0);
		ag_Freshanon(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
		ag_Freshanon(g_Wallet->m_vec_markmin, m_IDX, 0.0f);

		if(m_IDX < g_Wallet->m_vec_targetbreach.size())
			{
			char* f_Char = ag_ClearChar(256);

			::sprintf(f_Char, "%i", g_Wallet->m_vec_maxpledge[m_IDX]);

			eslmaxpledgetextBox().Text(StrUsingStr(f_Char));

			delete f_Char;

			char* f_Char1 = ag_ClearChar(256);

			::sprintf(f_Char1, "%i", g_Wallet->m_vec_targetbreach[m_IDX]);

			esltimedpledgetextBox().Text(StrUsingStr(f_Char1));

			delete f_Char1;

			char* f_Char2 = ag_ClearChar(256);

			::sprintf(f_Char2, "%i", g_Wallet->m_vec_scoremax[m_IDX]);

			eslscoremaxtextBox().Text(StrUsingStr(f_Char2));

			delete f_Char2;

			char* f_Char3 = ag_ClearChar(256);

			::sprintf(f_Char3, "%f", g_Wallet->m_vec_markmax[m_IDX]);

			eslmarkmaxtextBox().Text(StrUsingStr(f_Char3));

			delete f_Char3;

			char* f_Char4 = ag_ClearChar(256);

			::sprintf(f_Char4, "%f", g_Wallet->m_vec_markmin[m_IDX]);

			eslmarkmintextBox().Text(StrUsingStr(f_Char4));

			delete f_Char4;
			}
		else
			{
			eslmaxpledgetextBox().Text(L"");
			esltimedpledgetextBox().Text(L"");
			eslscoremaxtextBox().Text(L"0");
			eslmarkmaxtextBox().Text(L"0.0");
			eslmarkmintextBox().Text(L"0.0");
			}

		acRefreshJobVar();
	}

	void SecondaryAppWindowPageDX::OnClickShowTransaction(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(transactionStack().Visibility() == Windows::UI::Xaml::Visibility::Collapsed)
			{
			transactionStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
			transactionExplorerStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

			if(g_PreCom != nullptr)
				{
				OpenTXD(g_PreCom->m_owner, g_PreCom->m_Cost);
				}
			else
				{
				OpenTXD("", 1.0f);
				}
			}
		else if(transactionStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			transactionStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			transactionExplorerStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);

			CloseTXD();
			}
	}

	void SecondaryAppWindowPageDX::OnClickBack(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(g_Once == true)
			{
			if(g_Ackent[g_EventOffset]->m_ShareID == g_ShareID)
				{
				g_EventOffset--;
				}

			if(g_EventOffset < 0)
				{
				g_EventOffset = 0;
				}

			g_Ackent[g_EventOffset]->m_State = 0;
			}
	}

	void SecondaryAppWindowPageDX::OnClickNext(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(g_Once == true)
			{
			if(g_Ackent[g_EventOffset]->m_ShareID == g_ShareID)
				{
				g_EventOffset++;
				}

			if(g_EventOffset > g_Ackent.size())
				{
				g_EventOffset = g_Ackent.size() - 1;
				}

			g_Ackent[g_EventOffset]->m_State = 0;
			}
	}

	void SecondaryAppWindowPageDX::OnFillTargets(void)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::OnFillTargets";

		int f_Int = 1;

		targetcomboBox().Items().Clear();

		  ////////////////
		 // targets
		//
		g_SafeL[0]->acSelectCommand("SELECT id, name FROM target", false, false);

		int f_targetCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_targetCount = 0;
			}
		else
			{
			f_targetCount = g_Schedular[0]->acEntrySize();
			}

		for(int f_TGTID = 0; f_TGTID < f_targetCount; f_TGTID++)
			{
			targetcomboBox().Items().Append(CreateComboBoxItem(StrUsingStr(g_Schedular[0]->acEntry(f_TGTID)[1])));
			}
	}

	void SecondaryAppWindowPageDX::OnClickSend(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		std::string f_A = to_string(transactionA().Text());
		std::string f_B = to_string(transactionB().Text());
		std::string f_Stramt = to_string(transactionamt().Text());

		float f_amt = (float)atof(f_Stramt.c_str());

		int f_Flag = Cag->ag_GenerateTransaction(f_A, f_B, f_amt);

		switch(f_Flag)
			{
			case 0:
				{
				txnerrortextBlock().Text(L"Transaction Failed - unknown error code");
				}break;

			case 1:
				{
				txnerrortextBlock().Text(L"Transaction SUCCESS");
				transactionA().Text(L"");
				transactionB().Text(L"");
				transactionamt().Text(L"0.0");
				}break;

			case 2:
				{
				txnerrortextBlock().Text(L"Transaction Failed - Permission to access coins denied");
				transactionA().Text(L"");
				transactionB().Text(L"");
				transactionamt().Text(L"0.0");
				}break;

			case 3:
				{
				txnerrortextBlock().Text(L"Transaction Failed : Not enough ecoin in sending address");
				transactionA().Text(L"");
				transactionB().Text(L"");
				transactionamt().Text(L"0.0");
				}break;
			}
	}


	void SecondaryAppWindowPageDX::OnClickNewAddress(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(newaddresstextBox().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			newaddresstextBox().Text(L"");
			newaddresstextBox().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			std::shared_ptr<CKey> f_key = ecoin::ag_GenerateAddress(1, false);

			g_Wallet->acPushKey(f_key);

			newaddresstextBox().Text(StrUsingStr(f_key->m_owner));
			newaddresstextBox().Visibility(Windows::UI::Xaml::Visibility::Visible);
			}
	}

	void SecondaryAppWindowPageDX::onClickNextos(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(g_Once == true)
			{
			if(g_Ackent[g_EventOffset]->m_ShareID == g_ShareID)
				{
				g_EventOffset++;
				}

			if(g_EventOffset > g_Ackent.size())
				{
				g_EventOffset = g_Ackent.size() - 1;
				}

			g_Ackent[g_EventOffset]->m_State = 0;
			}
	}

	void SecondaryAppWindowPageDX::onClickPreviousBlock(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		char* blokquery = ag_ClearChar(1000);
		::sprintf(blokquery, "SELECT shareid, dated FROM block ORDER BY dated DESC LIMIT 1");
		g_SafeL[0]->acSelectCommand(blokquery, false, false);
		delete blokquery;

		int f_blokLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_blokLCount = 0;
			}
		else
			{
			f_blokLCount = g_Schedular[0]->acEntrySize();
			}

		//ECN::Stat::: f_blokLCount
		if(f_blokLCount == 1)
			{
			int f_PrevJobShareID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());

			  /////////////
			 //
			// LoadShare
			g_ShareID = f_PrevJobShareID;
			g_Found_Msg = 15;
			g_Found_Text = "Previous Block!";

			acLoadShare(g_ShareID);
			}
	}

	void SecondaryAppWindowPageDX::onClickWinningShare(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		char* blokquery = ag_ClearChar(1000);
		::sprintf(blokquery, "SELECT id, score FROM share WHERE ((jobid = %i) AND (score > 0)) ORDER BY score DESC LIMIT 1", g_JobID);
		g_SafeL[0]->acSelectCommand(blokquery, false, false);
		delete blokquery;

		int f_winnerLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_winnerLCount = 0;
			}
		else
			{
			f_winnerLCount = g_Schedular[0]->acEntrySize();
			}

		//ECN::Stat::: f_winnerLCount
		if(f_winnerLCount == 1)
			{
			int f_WinningShareID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());

			  /////////////
			 // LoadShare
			//
			g_ShareID = f_WinningShareID;
			g_Found_Msg = 15;
			g_Found_Text = "Winning Share!";

			acLoadShare(g_ShareID);
			}
	}

	void SecondaryAppWindowPageDX::onClickOwnPeer(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		std::shared_ptr<ShareContainerExt> f_ShareContainer = Cag->ag_SelectPeerGraphExt(g_JobID, 0, 0, g_CurrentShareOffset, g_PEER);

		g_PEER = f_ShareContainer->m_espo_OwnPeerIndex;
		g_CurrentShareOffset = 0;

		g_PEERMAX = f_ShareContainer->m_espo_PeerCount;

		if(g_PEERMAX > 0)
			{
			g_CurrentShareOffsetMAX = f_ShareContainer->m_espo_TotalSharesOwnPeer;
			}
		else
			{
			g_CurrentShareOffsetMAX = 0;
			}

		  /////////////
		 //
		// LoadShare
		acLoadShare();
	}

	void SecondaryAppWindowPageDX::OnClickQcom(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(::g_QcomManager->m_Open == true)
			{
			::g_QcomManager->m_Open = false;

			g_RenderHesh = true;
			}
		else
			{
			::g_QcomManager->m_Open = true;
			::g_QcomManager->m_current_X = 0.0f;
			::g_QcomManager->m_current_Y = 0.0f;
			::g_QcomManager->m_current_Zoom = 0.0f;
			}
	}

	void SecondaryAppWindowPageDX::OnRightClickWindow(IInspectable sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs e)
	{
		if(::g_QcomManager)
			{
			if(::g_QcomManager->m_Open == true)
				{
				::g_QcomManager->ac_FireRTClick();
				}
			}

		if(qcomappBar().IsOpen() == true)
			{
			qcomappBar().IsOpen(false);
			}
		else
			{
			qcomappBar().IsOpen(true);

			::g_QcomManager->m_Open = true;
			}
	}

	void SecondaryAppWindowPageDX::OnClickShowWithdraw(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(withdrawStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			withdrawStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			withdrawStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
			withdrawconfirmtextBlock().Text(L"Please enter your Pay-Pal email for payment contain \"ecoincps\"");
			}
	}

	void SecondaryAppWindowPageDX::OnClickShowDeposit(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(depositStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			depositStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			depositStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
			depositresulttextBlock().Text(L"Please proceed.");
			}
	}

	void SecondaryAppWindowPageDX::OnClickBuy5GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY5", 5);
	}

	void SecondaryAppWindowPageDX::OnClickBuy10GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY10", 10);
	}

	void SecondaryAppWindowPageDX::OnClickBuy20GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY20", 20);
	}

	void SecondaryAppWindowPageDX::OnClickBuy50GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY50", 50);
	}

	void SecondaryAppWindowPageDX::OnClickBuy100GBP(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY100", 100);
	}

	std::future<bool> SecondaryAppWindowPageDX::OnBuyGBP(std::string f_ProductID, int f_IntAmt)
	{
		depositresulttextBlock().Text(L"Please Proceed...");

#ifdef ECOIN_STORE_SIM
		::winrt::hstring f_ProductIDX = StrUsingStr(f_ProductID);

		try
			{
			::winrt::Windows::ApplicationModel::Store::PurchaseResults results = await ::winrt::Windows::ApplicationModel::Store::CurrentAppSimulator::RequestProductPurchaseAsync(f_ProductIDX);

			switch(results.Status())
				{
				case ::winrt::Windows::ApplicationModel::Store::ProductPurchaseStatus::Succeeded:
					{
					char* f_CChar = ag_ClearChar(512);

					::sprintf(f_CChar, "%i", f_IntAmt);

					std::string f_String = "Succcess ";
					f_String += f_CChar;
					f_String += " eGBP Credited to wallet! ";

					delete f_CChar;

					depositresulttextBlock().Text(StrUsingStr(f_String));

					g_Wallet->GetBalanceCPS(true, 0);

					float f_Before = g_Wallet->m_Bank_ecoin_constant;

					f_Before += (float)f_IntAmt;

					char* f_Char = ag_ClearChar(512);

					::sprintf(f_Char, "%.4f", f_Before);

					walletindollarstextBlock_CPS().Text(StrUsingStr(std::string(f_Char)));

					delete f_Char;

					g_Wallet->SetBalanceCPS(f_Before);

					char* g_constantdepositvalue[4];
					char* g_constantdepositfield[4];

					for(int f_Count = 0; f_Count < 4; f_Count++)
						{
						g_constantdepositvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
						g_constantdepositfield[f_Count] = (char*)malloc(sizeof(char) * 512);
						}

					::sprintf(g_constantdepositfield[0], "employeeid");
					::sprintf(g_constantdepositfield[1], "owner");
					::sprintf(g_constantdepositfield[2], "buyamt");
					::sprintf(g_constantdepositfield[3], "bosslvlmin");

					::sprintf(g_constantdepositvalue[0], "%i", g_EmployeeID);
					::sprintf(g_constantdepositvalue[1], "%s", g_Wallet->GetAdr().c_str());
					::sprintf(g_constantdepositvalue[2], "%f", (float)f_IntAmt);
					::sprintf(g_constantdepositvalue[3], "%f", 0.0100f);

					int f_UniqueID = g_SafeL[0]->Insert("constantdeposit", (const char **)g_constantdepositfield, (const char **)g_constantdepositvalue, 4, false, false);

					acFullfill(f_ProductIDX, results.TransactionId());
					}break;

				case ::winrt::Windows::ApplicationModel::Store::ProductPurchaseStatus::NotFulfilled:
					{
					depositresulttextBlock().Text(L"Failure Product not Fullfilled.");

					acFullfill(f_ProductIDX, results.TransactionId(), true);
					}break;

				case ::winrt::Windows::ApplicationModel::Store::ProductPurchaseStatus::NotPurchased: //fail lose not found
					{
					depositresulttextBlock().Text(L"[FAILURE] Product Not Found.");
					}break;
				}
			}

		catch(...)
			{
			depositresulttextBlock().Text(L"[FAILURE] Quit or retry.");
			}
					
#else
		::winrt::hstring f_ProductIDX = StrUsingStr(f_ProductID);

		try
			{
			::winrt::Windows::ApplicationModel::Store::PurchaseResults results = await ::winrt::Windows::ApplicationModel::Store::CurrentAppSimulator::RequestProductPurchaseAsync(f_ProductIDX);

			switch(results.Status())
				{
				case ::winrt::Windows::ApplicationModel::Store::ProductPurchaseStatus::Succeeded:
					{
					char* f_CChar = ag_ClearChar(512);

					::sprintf(f_CChar, "%i", f_IntAmt);

					std::string f_String = "Succcess ";
					f_String += f_CChar;
					f_String += " eGBP Credited to wallet! ";

					delete f_CChar;

					depositresulttextBlock().Text(StrUsingStr(f_String));

					g_Wallet->GetBalanceCPS(true, 0);

					float f_Before = g_Wallet->m_Bank_ecoin_constant;

					f_Before += (float)f_IntAmt;

					char* f_Char = ag_ClearChar(512);

					::sprintf(f_Char, "%.4f", f_Before);

					walletindollarstextBlock_CPS().Text(StrUsingStr(std::string(f_Char)));

					delete f_Char;

					g_Wallet->SetBalanceCPS(f_Before);

					char* g_constantdepositvalue[4];
					char* g_constantdepositfield[4];

					for(int f_Count = 0; f_Count < 4; f_Count++)
						{
						g_constantdepositvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
						g_constantdepositfield[f_Count] = (char*)malloc(sizeof(char) * 512);
						}

					::sprintf(g_constantdepositfield[0], "employeeid");
					::sprintf(g_constantdepositfield[1], "owner");
					::sprintf(g_constantdepositfield[2], "buyamt");
					::sprintf(g_constantdepositfield[3], "bosslvlmin");

					::sprintf(g_constantdepositvalue[0], "%i", g_EmployeeID);
					::sprintf(g_constantdepositvalue[1], "%s", g_Wallet->GetAdr().c_str());
					::sprintf(g_constantdepositvalue[2], "%f", (float)f_IntAmt);
					::sprintf(g_constantdepositvalue[3], "%f", 0.0100f);

					int f_UniqueID = g_SafeL[0]->Insert("constantdeposit", (const char **)g_constantdepositfield, (const char **)g_constantdepositvalue, 4, false, false);

					acFullfill(f_ProductIDX, results.TransactionId());
					}break;

				case ::winrt::Windows::ApplicationModel::Store::ProductPurchaseStatus::NotFulfilled:
					{
					depositresulttextBlock().Text(L"Failure Product not Fullfilled.");

					acFullfill(f_ProductIDX, results.TransactionId(), true);
					}break;

				case ::winrt::Windows::ApplicationModel::Store::ProductPurchaseStatus::NotPurchased: //fail lose not found
					{
					depositresulttextBlock().Text(L"[FAILURE] Product Not Found.");
					}break;
				}
			}

		catch(...)
			{
			depositresulttextBlock().Text(L"[FAILURE] Quit or retry.");
			}
#endif

		co_return true;
	}

	std::future<bool> SecondaryAppWindowPageDX::acFullfill(winrt::hstring f_ProdId, winrt::guid f_TransactionId, bool f_QuickFullFill)
	{
#ifdef ECOIN_STORE_SIM
		::winrt::Windows::ApplicationModel::Store::FulfillmentResult result = await ::winrt::Windows::ApplicationModel::Store::CurrentAppSimulator::ReportConsumableFulfillmentAsync(f_ProdId, f_TransactionId);

		switch(result)
			{
			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::Succeeded:
				{
				if(f_QuickFullFill == false)
					{
					depositresulttextBlock().Text(L"[SUCCESS] Payment Processed and fulfilled.");
					}
				}break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::NothingToFulfill:
				{
				if(f_QuickFullFill == false)
					{
					depositresulttextBlock().Text(L"Nothing to Fulfill.");
					}
				}break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchasePending:
				{
				depositresulttextBlock().Text(L"The purchase is pending so we cannot fulfill the product.");
				}break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchaseReverted:
				{
				depositresulttextBlock().Text(L"But your purchase has been reverted.");
				}break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::ServerError:
				{
				depositresulttextBlock().Text(L"There was an error when fulfilling.");
				}break;
			}

		winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::ApplicationModel::Store::UnfulfilledConsumable> f_vec_chkresult = await ::winrt::Windows::ApplicationModel::Store::CurrentAppSimulator::GetUnfulfilledConsumablesAsync();

		if(f_vec_chkresult.Size() > 0)
			{
			depositresulttextBlock().Text(L"[IMPORTANT] Error one or more transactions unfullfilled.");

			std::vector<int> f_vecResult;

			f_vecResult.clear();

			for(int f_Jet = 0; f_Jet < f_vec_chkresult.Size(); f_Jet++)
				{
				winrt::Windows::ApplicationModel::Store::UnfulfilledConsumable f_unfullfilled = f_vec_chkresult.GetAt(f_Jet);

				::winrt::Windows::ApplicationModel::Store::FulfillmentResult unfresult = await ::winrt::Windows::ApplicationModel::Store::CurrentAppSimulator::ReportConsumableFulfillmentAsync(f_unfullfilled.ProductId(), f_unfullfilled.TransactionId());

				switch(unfresult)
					{
					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::Succeeded:
						depositresulttextBlock().Text(L"[SUCCESS] Payment Processed and fulfilled.");

						f_vecResult.push_back(1);
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::NothingToFulfill:
						depositresulttextBlock().Text(L"Nothing to Fulfill.");
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchasePending:
						depositresulttextBlock().Text(L"The purchase is pending so we cannot fulfill the product.");

						f_vecResult.push_back(2);
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchaseReverted:
						depositresulttextBlock().Text(L"But your purchase has been reverted.");
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::ServerError:
						depositresulttextBlock().Text(L"There was an error when fulfilling.");

						f_vecResult.push_back(3);
						break;
					}
				}

			bool f_ShowBool = false;

			for(int f_Helly = 0; f_Helly < f_vecResult.size(); f_Helly++)
				{
				if(f_vecResult[f_Helly] != 1)
					{
					f_ShowBool = true;
					}
				}

			f_vecResult.clear();
			
			if(f_ShowBool == true)
				{
				std::string f_ErrorMsg = "ErrorCode[";

				for(int f_Jet2 = 0; f_Jet2 < f_vecResult.size(); f_Jet2++)
					{
					char* f_Char = ag_ClearChar(64);

					sprintf(f_Char, "%i", f_vecResult[f_Jet2]);

					f_ErrorMsg += f_Char;
					}

				f_ErrorMsg += "]";

				winrt::hstring f_hstring = depositresulttextBlock().Text();

				std::string f_StringVal = to_string(f_hstring);

				f_StringVal += f_ErrorMsg;

				depositresulttextBlock().Text(StrUsingStr(f_StringVal));
				}
			}
#else
		::winrt::Windows::ApplicationModel::Store::FulfillmentResult result = await ::winrt::Windows::ApplicationModel::Store::CurrentApp::ReportConsumableFulfillmentAsync(f_ProdId, f_TransactionId);

		switch(result)
			{
			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::Succeeded:
				{
				if(f_QuickFullFill == false)
					{
					depositresulttextBlock().Text(L"Payment Processed and fulfilled.");
					}
				}break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::NothingToFulfill:
				{
				if(f_QuickFullFill == false)
					{
					depositresulttextBlock().Text(L"nofulfill.");
					}
				} break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchasePending:
				{
				depositresulttextBlock().Text(L"The purchase is pending so we cannot fulfill the product.");
				}break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchaseReverted:
				{
				depositresulttextBlock().Text(L"But your purchase has been reverted.");
				}break;

			case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::ServerError:
				{
				depositresulttextBlock().Text(L"There was an error when fulfilling.");
				}break;
			}

		winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::ApplicationModel::Store::UnfulfilledConsumable> f_vec_chkresult = await ::winrt::Windows::ApplicationModel::Store::CurrentApp::GetUnfulfilledConsumablesAsync();

		if(f_vec_chkresult.Size() > 0)
			{
			depositresulttextBlock().Text(L"[IMPORTANT] Error one or more transactions unfullfilled.");

			std::vector<int> f_vecResult;

			f_vecResult.clear();

			for(int f_Jet = 0; f_Jet < f_vec_chkresult.Size(); f_Jet++)
				{
				winrt::Windows::ApplicationModel::Store::UnfulfilledConsumable f_unfullfilled = f_vec_chkresult.GetAt(f_Jet);

				::winrt::Windows::ApplicationModel::Store::FulfillmentResult unfresult = await ::winrt::Windows::ApplicationModel::Store::CurrentApp::ReportConsumableFulfillmentAsync(f_unfullfilled.ProductId(), f_unfullfilled.TransactionId());

				switch(unfresult)
					{
					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::Succeeded:
						depositresulttextBlock().Text(L"[SUCCESS] Payment Processed and fulfilled.");

						f_vecResult.push_back(1);
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::NothingToFulfill:
						depositresulttextBlock().Text(L"Nothing to Fulfill.");
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchasePending:
						depositresulttextBlock().Text(L"The purchase is pending so we cannot fulfill the product.");

						f_vecResult.push_back(2);
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::PurchaseReverted:
						depositresulttextBlock().Text(L"But your purchase has been reverted.");
						break;

					case ::winrt::Windows::ApplicationModel::Store::FulfillmentResult::ServerError:
						depositresulttextBlock().Text(L"There was an error when fulfilling.");

						f_vecResult.push_back(3);
						break;
					}
				}

			bool f_ShowBool = false;

			for(int f_Helly = 0; f_Helly < f_vecResult.size(); f_Helly++)
				{
				if(f_vecResult[f_Helly] != 1)
					{
					f_ShowBool = true;
					}
				}

			f_vecResult.clear();
			
			if(f_ShowBool == true)
				{
				std::string f_ErrorMsg = "ErrorCode[";

				for(int f_Jet2 = 0; f_Jet2 < f_vecResult.size(); f_Jet2++)
					{
					char* f_Char = ag_ClearChar(64);

					sprintf(f_Char, "%i", f_vecResult[f_Jet2]);

					f_ErrorMsg += f_Char;
					}

				f_ErrorMsg += "]";

				winrt::hstring f_hstring = depositresulttextBlock().Text();

				std::string f_StringVal = to_string(f_hstring);

				f_StringVal += f_ErrorMsg;

				depositresulttextBlock().Text(StrUsingStr(f_StringVal));
				}
			}
#endif

		co_return true;
	}

	void SecondaryAppWindowPageDX::OnClickWithDrawCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		std::string f_WithdrawAmountTXT = to_string(withdrawamounttextBox().Text());

		float f_WithdrawalAmount = atof(f_WithdrawAmountTXT.c_str());

		if(f_WithdrawalAmount >= 50.0f && f_BalanceCPS >= 50.0f)
			{
			if(f_BalanceCPS >= f_WithdrawalAmount)
				{
				std::string f_PayPalEmail = to_string(withdrawpaypalemailtextBox().Text());

				char* g_syncWithdrawvalue[5];
				char* g_syncWithdrawfield[5];

				for(int f_s = 0; f_s < 5; f_s++)
					{
					g_syncWithdrawvalue[f_s] = (char*)malloc(sizeof(char) * 256);
					g_syncWithdrawfield[f_s] = (char*)malloc(sizeof(char) * 256);
					}

				::sprintf(g_syncWithdrawfield[0], "employeeid");
				::sprintf(g_syncWithdrawfield[1], "owner");
				::sprintf(g_syncWithdrawfield[2], "withdrawamt");
				::sprintf(g_syncWithdrawfield[3], "paypalemail");
				::sprintf(g_syncWithdrawfield[4], "status");

				::sprintf(g_syncWithdrawvalue[0], "%i", g_EmployeeID);
				::sprintf(g_syncWithdrawvalue[1], "%s", g_Wallet->GetAdr().c_str());
				::sprintf(g_syncWithdrawvalue[2], "%f", f_WithdrawalAmount);
				::sprintf(g_syncWithdrawvalue[3], "%s", f_PayPalEmail.c_str());
				::sprintf(g_syncWithdrawvalue[4], "%i", 1);

				int f_SyncUniqueID = g_SafeL[1]->Insert("constantwithdraw", (const char **)g_syncWithdrawfield, (const char **)g_syncWithdrawvalue, 5, true, false);

				for(int f_s = 0; f_s < 5; f_s++)
					{
					delete g_syncWithdrawvalue[f_s];
					delete g_syncWithdrawfield[f_s];
					}

				g_Wallet->SetBalanceCPS(f_BalanceCPS - f_WithdrawalAmount);
			
				withdrawconfirmtextBlock().Text(L"Well Done! Successfull Withdraw!");
				}
			else
				{
				withdrawconfirmtextBlock().Text(L"Failure not enough eGBP");
				}
			}
		else
			{
			withdrawconfirmtextBlock().Text(L"Sorry Minimum Withdrawal is £50");
			}
	}

	void SecondaryAppWindowPageDX::OnClickeslcodeClose(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(eslcodeStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
	}

	void SecondaryAppWindowPageDX::OnClickeslcodeCheck(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		string f_PrefixString = to_string(eslcodeprefixtextBox().Text());

		int f_Length = f_PrefixString.length();

		f_Length++;

		f_Length += to_string(eslcodenametextBox().Text()).length();

		f_Length++;

		f_Length += to_string(eslcodedescriptiontextBox().Text()).length();

		g_Type = ag_FindTypefromText(f_PrefixString);

		if(g_Type > 0)
			{
			char* f_Char = new char(255);
			std::sprintf(f_Char, "%i/%i", f_Length, ECOIN_SHARE_PROTOCOL_LENGTH);
			string f_LengthString = f_Char;

			if(f_Length <= ECOIN_SHARE_PROTOCOL_LENGTH)
				{
				if(g_currentLaunch == true)
					{
					eslcoderesulttextBlock().Text(StrUsingStr("All Good! Start Diving Shares->>>(" + f_LengthString + ")"));

					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0));
					myBrush.Color();
					eslcodestartbutton().BorderBrush(myBrush);
					}
				else
					{
					if((g_currentLaunchType == 0) && ((g_Type == 0) || (g_Type == 1) || (g_Type == 2)))
						{
						if(g_Type <= 1)
							{
							eslcoderesulttextBlock().Text(StrUsingStr("All Good! Start Diving Shares->>>(" + f_LengthString + ")"));

							Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0));
							eslcodestartbutton().BorderBrush(myBrush);
							}
						else if (g_Type == 2)
							{
							eslcoderesulttextBlock().Text(StrUsingStr("All Good! Start Diving Shares->>>(" + f_LengthString + ")"));

							Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0));
							eslcodestartbutton().BorderBrush(myBrush);
							}
						}
					else if(g_Type == 3)
						{
						eslcoderesulttextBlock().Text(StrUsingStr("All Good!(" + f_LengthString + "). Genesis target loaded(" + g_currentLaunchPrefix + ")"));

						Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0));
						eslcodestartbutton().BorderBrush(myBrush);
						}
					else
						{
						eslcoderesulttextBlock().Text(StrUsingStr("code len Good!(" + f_LengthString + "). Incorrect target loaded(" + g_currentLaunchPrefix + ")"));

						Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0));
						eslcodestartbutton().BorderBrush(myBrush);
						}
					}
				}
			else
				{
				eslcoderesulttextBlock().Text(StrUsingStr("FAIL Maximum Length Exceeded. Length = " + f_LengthString));

				Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0));
				eslcodestartbutton().BorderBrush(myBrush);
				}
			}
		else
			{
			eslcoderesulttextBlock().Text(StrUsingStr("FAIL Tag not recognised. TAG = " + f_PrefixString));

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0));
			eslcodestartbutton().BorderBrush(myBrush);
			}
	}

	void SecondaryAppWindowPageDX::OnClickeslcodeStart(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ref_CurrentPath = "SecondaryAppWindowPageDX::OnClickeslcodeStart";

		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		//instantiate special variables
		LOWTON_STORAGE = (int)g_Wallet->acSelect_JobVar(m_IDX, "LOWTON_STORAGE");

		if(LOWTON_STORAGE <= 0.0f)
			{
			LOWTON_STORAGE = ECOIN_TARGET_LOWTON_STORAGE;
			}

		std::string f_MaxPledgeStr = "";
		std::string f_TimedPledgeStr = "";

		int f_PledgesON = ecoin_PledgeType::ecoin_Pledge_Off;
		g_BlockType = ecoin_BlockType::ecoin_Block_Target_TypeName;

		bool f_Cover_TimeLimit = false;
		bool f_Cover_MaxPledge = false;
		bool f_Cover_TargetSCP = false;

		if(eslmaxpledgetextBox().IsReadOnly() == false)
			{
			f_MaxPledgeStr = to_string(eslmaxpledgetextBox().Text());
			f_TimedPledgeStr = to_string(esltimedpledgetextBox().Text());

			int f_MaxPledgeINT = ag_CheckInteger(f_MaxPledgeStr);
			int f_TimedPledgeINT = ag_CheckInteger(f_TimedPledgeStr);

			std::time_t f_CurrentTime;
			std::time(&f_CurrentTime);

			if(f_MaxPledgeINT > -1)
				{
				if(f_TimedPledgeINT > -1)
					{
					f_PledgesON = ecoin_PledgeType::ecoin_Pledge_MaxTimed;
					g_BlockType = ecoin_BlockType::ecoin_Block_MaxTimedPledge;

					f_Cover_TimeLimit = true;
					f_Cover_MaxPledge = true;
					f_Cover_TargetSCP = false;

					f_TimedPledgeINT += f_CurrentTime;

					ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, f_MaxPledgeINT);
					ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, f_TimedPledgeINT);
					ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
					}
				else
					{
					f_PledgesON = ecoin_PledgeType::ecoin_Pledge_Max;
					g_BlockType = ecoin_BlockType::ecoin_Block_MaxPledge;

					f_Cover_TimeLimit = false;
					f_Cover_MaxPledge = true;
					f_Cover_TargetSCP = false;

					ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, f_MaxPledgeINT);
					ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, f_TimedPledgeINT);
					ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
					}
				}
			else
				{
				if(f_TimedPledgeINT > -1)
					{
					f_PledgesON = ecoin_PledgeType::ecoin_Pledge_Timed;
					g_BlockType = ecoin_BlockType::ecoin_Block_TimedPledge;

					f_Cover_TimeLimit = true;
					f_Cover_MaxPledge = false;
					f_Cover_TargetSCP = false;

					f_TimedPledgeINT += f_CurrentTime;

					ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, f_MaxPledgeINT);
					ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, f_TimedPledgeINT);
					ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
					}
				else
					{
					f_PledgesON = ecoin_PledgeType::ecoin_Pledge_Off;
					g_BlockType = ecoin_BlockType::ecoin_Block_Target_TypeName;

					f_Cover_TimeLimit = false;
					f_Cover_MaxPledge = false;
					f_Cover_TargetSCP = false;

					ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, 0);
					ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, 0);
					ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
					}
				}
			}
		else
			{
			f_PledgesON = ecoin_PledgeType::ecoin_Pledge_Off;

			f_TimedPledgeStr = to_string(esltimedpledgetextBox().Text());

			int f_TimedPledgeINT = ag_CheckInteger(f_TimedPledgeStr);

			time_t f_CurrentTime;
			time(&f_CurrentTime);

			if(f_TimedPledgeINT > -1)
				{
				g_BlockType = ecoin_BlockType::ecoin_Block_Target_TimedType; //win conditions Target Driven Timed TypeName

				f_Cover_TimeLimit = true;
				f_Cover_MaxPledge = false;
				f_Cover_TargetSCP = false;

				f_TimedPledgeINT += f_CurrentTime;

				ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, 0);
				ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, f_TimedPledgeINT);
				ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
				}
			else
				{
				g_BlockType = ecoin_BlockType::ecoin_Block_Target_TypeName; //win conditions Target Driven Timed TypeName

				f_Cover_TimeLimit = false;
				f_Cover_MaxPledge = false;
				f_Cover_TargetSCP = false;

				ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, 0);
				ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, 0);
				ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
				}
			}

		ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, f_PledgesON);

		std::string f_MaxVotingScoreString = to_string(eslscoremaxtextBox().Text());
		std::string f_MarkMaxString = to_string(eslmarkmaxtextBox().Text());
		std::string f_MarkMinString = to_string(eslmarkmintextBox().Text());

		int f_MaxVotingScore = ag_CheckInteger(f_MaxVotingScoreString);
		float f_MarkMax = ag_CheckFloat(f_MarkMaxString);
		float f_MarkMin = ag_CheckFloat(f_MarkMinString);

		if(f_MaxVotingScore > 0.0f)
			{
			if((f_PledgesON != ecoin_PledgeType::ecoin_Pledge_Timed) && (f_PledgesON != ecoin_PledgeType::ecoin_Pledge_MaxTimed))
				{
				ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, f_MaxVotingScore);
				}
			}

		if(f_MarkMax > 0.0f)
			{
			ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, f_MarkMax);
			}

		if(f_MarkMin > 0.0f)
			{
			ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, f_MarkMin);
			}

		string f_PrefixString = to_string(eslcodeprefixtextBox().Text());

		int f_Length = f_PrefixString.length();

		f_Length++;

		string f_NameString = to_string(eslcodenametextBox().Text());

		f_Length += f_NameString.length();

		f_Length++;

		string f_DescriptionString = to_string(eslcodedescriptiontextBox().Text());

		f_Length += to_string(eslcodedescriptiontextBox().Text()).length();

		g_Type = ag_FindTypefromText(f_PrefixString);

		if(g_Type > 0)
			{
			char* f_Char = new char(255);
			std::sprintf(f_Char, "%i/%i", f_Length, ECOIN_SHARE_PROTOCOL_LENGTH);
			string f_LengthString = f_Char;

			if(f_Length <= ECOIN_SHARE_PROTOCOL_LENGTH)
				{
				g_TypeName.clear();
				g_TypeName = f_PrefixString + ECOIN_SHOP_PROTOCOL_SEPARATOR + f_NameString + ECOIN_SHOP_PROTOCOL_SEPARATOR + f_DescriptionString;

				if(g_currentLaunch == true)
					{
					if((m_IDX < g_Wallet->m_vec_jobvar_textupdate.size()) && (m_IDX < g_Wallet->m_vec_jobvar_current_index.size()))
						{
						if(g_Wallet->m_vec_jobvar_current_index[m_IDX] < g_Wallet->m_vec_jobvar_textupdate[m_IDX].size())
							{
							if(g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] == true)
								{
								g_Wallet->m_vec_jobvar_groupname[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = to_string(esljobvargrouptextBox().Text());
								g_Wallet->m_vec_jobvar_name[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = to_string(esljobvarnametextBox().Text());
								g_Wallet->m_vec_jobvar_value[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = atof(to_string(esljobvarvaluetextBox().Text()).c_str());

								g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = false;
								}
							}
						}

					if(g_Type != 3)
						{
						ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_NONVIEW);

						g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_NONVIEW;

						if(f_PledgesON == 0)
							{
							g_BlockType = ecoin_BlockType::ecoin_Block_Target_TypeName;
							}

						ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
						ag_FreshOn<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
						ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_PrefixString);

						ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, 0);
						ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, 0);

						ag_Freshanon<float>(::g_Wallet->m_vec_markmax, m_IDX, 0.0f);
						ag_Freshanon<float>(::g_Wallet->m_vec_markmin, m_IDX, 0.0f);

						m_main->m_sceneRenderer->m_LowtonTicket = -1;

						g_Result = false;

						time(&g_storagetime);
						g_storagetime += LOWTON_STORAGE;

						eslcoderesulttextBlock().Text(L"Launching!");
						
						Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0) });
						eslcodestartbutton().BorderBrush(myBrush);

						currentStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
						eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
						}
					else //Save...Complete...Publish...Mode
						{
						ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_COMPRESS);

						g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_COMPRESS;

						g_Result = false;
						g_LowtonOn = false;

						if(f_PledgesON == 0)
							{
							g_BlockType = ecoin_BlockType::ecoin_Block_Target_SCP;
							}

						ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
						ag_FreshOn<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
						ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_PrefixString);

						ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, 0);
						ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, 0);

						ag_Freshanon<float>(::g_Wallet->m_vec_markmax, m_IDX, 0.0f);
						ag_Freshanon<float>(::g_Wallet->m_vec_markmin, m_IDX, 0.0f);
						
						eslcoderesulttextBlock().Text(L"Launching!");

						Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0) });
						eslcodestartbutton().BorderBrush(myBrush);

						eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
						}
					}
				else
					{
					if((g_currentLaunchType == 0) && ((g_Type == 0) || (g_Type == 1) || (g_Type == 2)))
						{
						if(g_Type <= 2)
							{
#if 0
							g_Target_1 = ::std::make_shared_reflect<classTarget>();
							g_Target_1->acLoad_from_TargetID(2);

							g_Target_2 = ::std::make_shared_reflect<classTarget>();
							g_Target_2->acLoad_from_TargetID(2);

							time(&g_storagetime);
							g_storagetime += LOWTON_STORAGE;

							ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_NONVIEW);

							g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_NONVIEW;

							m_main->m_sceneRenderer->m_LowtonTicket = -1;

							g_Result = false;

							eslcoderesulttextBlock().Text(L"Launching!");

							Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0) });

							eslcodestartbutton().BorderBrush(myBrush);

							currentStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
							eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
#endif

							eslcoderesulttextBlock().Text(StrUsingStr(".code length Good!(" + f_LengthString + "). Incorrect target loaded, Buy or use Free from ShareShop.(" + f_PrefixString + ")"));

							Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0) });

							eslcodestartbutton().BorderBrush(myBrush);
							}
						}
					else if(g_Type == 3)
						{
						int f_Type = g_Type;

						g_currentLaunchType = f_Type;

						g_currentLaunchPrefix = f_PrefixString;

						g_currentLaunch = false;

						ag_StatusLive(f_ref_CurrentPath, "g_Target_3");
						g_Target_3 = ::std::make_shared_reflect<classTarget_Ecom>();

						g_Found_Msg = 10;
						g_currentLaunch = true;

						if(f_PledgesON == 0)
							{
							g_BlockType = ecoin_BlockType::ecoin_Block_Target_SCP;
							}

						ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);

						ag_FreshOn<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
						ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, f_PrefixString);

						ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, 0);
						ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, 0);
						ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);

						ag_Freshanon<float>(::g_Wallet->m_vec_markmax, m_IDX, 0.0f);
						ag_Freshanon<float>(::g_Wallet->m_vec_markmin, m_IDX, 0.0f);

						eslcoderesulttextBlock().Text(L"Launching!");

						Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0) });
						eslcodestartbutton().BorderBrush(myBrush);

						eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);

						ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_COMPRESS);

						g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_COMPRESS;

						g_Result = false;
						g_LowtonOn = false;
						}
					else
						{
						eslcoderesulttextBlock().Text(StrUsingStr("code length Good!(" + f_LengthString + "). Incorrect target loaded(" + g_currentLaunchPrefix + ")"));

						Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 0, 255, 0) });

						eslcodestartbutton().BorderBrush(myBrush);
						}
					}
				}
			else
				{
				eslcoderesulttextBlock().Text(StrUsingStr("FAIL Maximum Length Exceeded. Length = " + f_LengthString));

				Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0) });

				eslcodestartbutton().BorderBrush(myBrush);
				}
			}
		else
			{
			eslcoderesulttextBlock().Text(StrUsingStr("FAIL Tag not recognised. TAG = " + f_PrefixString));

			Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 255, 0, 0) });

			eslcodestartbutton().BorderBrush(myBrush);
			}
	}

	void SecondaryAppWindowPageDX::OnClickShareShop(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(shopStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			shopStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			shopStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
			}
	}

	void SecondaryAppWindowPageDX::OnClickShopSearch(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		m_ShareShop->m_ShopPage = 1;

		std::string f_searchReturn = m_ShareShop->acSearch_Shop(to_string(shopsearchnametextBox().Text()), to_string(shopsearchdescriptiontextBox().Text()), to_string(shopsearchprefixtextBox().Text()));

		shopresultstextBlock().Text(StrUsingStr(f_searchReturn));

		if((f_searchReturn.at(0) != 'O') || (f_searchReturn.at(1) != 'O'))
			{
			int f_productCount = m_ShareShop->acPopulate();

			OnRefreshShop();
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopsearchprev(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(m_ShareShop->m_ShopPage > 1)
			{
			m_ShareShop->m_ShopPage -= 1;

			std::string f_searchReturn = m_ShareShop->acSearch_Shop(to_string(shopsearchnametextBox().Text()), to_string(shopsearchdescriptiontextBox().Text()), to_string(shopsearchprefixtextBox().Text()));

			shopresultstextBlock().Text(StrUsingStr(f_searchReturn));

			if((f_searchReturn.at(0) != 'O') || (f_searchReturn.at(1) != 'O'))
				{
				int f_productCount = m_ShareShop->acPopulate();

				OnRefreshShop();
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopsearchnext(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		m_ShareShop->m_ShopPage += 1;

		std::string f_searchReturn = m_ShareShop->acSearch_Shop(to_string(shopsearchnametextBox().Text()), to_string(shopsearchdescriptiontextBox().Text()), to_string(shopsearchprefixtextBox().Text()));

		shopresultstextBlock().Text(StrUsingStr(f_searchReturn));

		if((f_searchReturn.at(0) != 'O') || (f_searchReturn.at(1) != 'O'))
			{
			int f_productCount = m_ShareShop->acPopulate();

			OnRefreshShop();
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopownproducts(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(g_MyOwnCom == false)
			{
			g_MyOwnCom = true;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 115, 55, 55));

			shopproductsownbutton().Foreground(myBrush);
			}
		else
			{
			g_MyOwnCom = false;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 255, 255));

			shopproductsownbutton().Foreground(myBrush);
			}

		m_ShareShop->m_ShopPage = 1;

		std::string f_searchReturn = m_ShareShop->acSearch_Shop(to_string(shopsearchnametextBox().Text()), to_string(shopsearchdescriptiontextBox().Text()), to_string(shopsearchprefixtextBox().Text()));

		shopresultstextBlock().Text(StrUsingStr(f_searchReturn));

		if((f_searchReturn.at(0) != 'O') || (f_searchReturn.at(1) != 'O'))
			{
			int f_productCount = m_ShareShop->acPopulate();

			OnRefreshShop();
			}
	}

	void SecondaryAppWindowPageDX::OnClickProductsBought(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(g_BoughtCom == false)
			{
			g_BoughtCom = true;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 115, 55, 55));

			shopproductsboughtbutton().Foreground(myBrush);
			}
		else
			{
			g_BoughtCom = false;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 255, 255));

			shopproductsboughtbutton().Foreground(myBrush);
			}

		m_ShareShop->m_ShopPage = 1;

		std::string f_searchReturn = m_ShareShop->acSearch_Shop(to_string(shopsearchnametextBox().Text()), to_string(shopsearchdescriptiontextBox().Text()), to_string(shopsearchprefixtextBox().Text()));

		shopresultstextBlock().Text(StrUsingStr(f_searchReturn));

		if((f_searchReturn.at(0) != 'O') || (f_searchReturn.at(1) != 'O'))
			{
			int f_productCount = m_ShareShop->acPopulate();

			OnRefreshShop();
			}
	}

	void SecondaryAppWindowPageDX::OnRefreshShop(void)
	{
		int f_Page = m_ShareShop->m_ShopPage - 1;

		for(int f_AX = f_Page * 12; f_AX < ((f_Page * 12) + 6); f_AX++)
			{
			if(f_AX < m_ShareShop->m_vec_Product.size())
				{
				std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[f_AX];

				if(f_AX == (f_Page * 12))
					{
					shopslotA1nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotA1descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotA1panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotA1paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.4fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotA1payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotA1nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA1rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if(f_AX == ((f_Page * 12) + 1))
					{
					shopslotA2nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotA2descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotA2panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotA2paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.4fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotA2payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotA2nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA2rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if(f_AX == ((f_Page * 12) + 2))
					{
					shopslotA3nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotA3descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotA3panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotA3paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.4fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotA3payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotA3nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA3rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if(f_AX == ((f_Page * 12) + 3))
					{
					shopslotA4nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotA4descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotA4panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotA4paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.4fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotA4payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotA4nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA4rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if (f_AX == ((f_Page * 12) + 4))
					{
					shopslotA5nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotA5descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotA5panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotA5paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.4fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotA5payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotA5nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA5rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if (f_AX == ((f_Page * 12) + 5))
					{
					shopslotA6nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotA6descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotA6panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotA6paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.4fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotA6payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotA6nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotA6rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				}
			else
				{
				if(f_AX == (f_Page * 12))
					{
					shopslotA1nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA1rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if(f_AX == (f_Page * 12) + 1)
					{
					shopslotA2nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA2rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if(f_AX == (f_Page * 12) + 2)
					{
					shopslotA3nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA3rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if (f_AX == (f_Page * 12) + 3)
					{
					shopslotA4nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA4rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if (f_AX == (f_Page * 12) + 4)
					{
					shopslotA5nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA5rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if (f_AX == (f_Page * 12) + 5)
					{
					shopslotA6nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotA6rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				}
			}

		for(int f_BX = ((f_Page * 12) + 6); f_BX < ((f_Page * 12) + 12); f_BX++)
			{
			if(f_BX < m_ShareShop->m_vec_Product.size())
				{
				std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[f_BX];

				if(f_BX == ((f_Page * 12) + 6))
					{
					shopslotB1nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotB1descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotB1panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotB1paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.2fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotB1payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotB1nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB1rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if(f_BX == ((f_Page * 12) + 7))
					{
					shopslotB2nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotB2descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotB2panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotB2paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.2fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotB2payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotB2nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB2rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if(f_BX == ((f_Page * 12) + 8))
					{
					shopslotB3nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotB3descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotB3panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotB3paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.2fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotB3payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotB3nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB3rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if(f_BX == ((f_Page * 12) + 9))
					{
					shopslotB4nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotB4descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotB4panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotB4paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.2fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotB4payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotB4nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB4rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if (f_BX == ((f_Page * 12) + 10))
					{
					shopslotB5nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotB5descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotB5panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotB5paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.2fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotB5payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotB5nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB5rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				else if (f_BX == ((f_Page * 12) + 11))
					{
					shopslotB6nametextBlock().Text(StrUsingStr(f_Product->m_Name));
					shopslotB6descriptiontextBlock().Text(StrUsingStr(f_Product->m_Description));
					shopslotB6panelbutton().Content(box_value(StrUsingStr(f_Product->m_TypeText)));
				
					float f_CostCPS = f_Product->m_CostCPS;

					char* prodquery = ag_ClearChar(1000);
					std::sprintf(prodquery, "Pay £%.2f", f_CostCPS);
					std::string f_ProductPriceText = prodquery;
					delete prodquery;

					shopslotB6paycpsbutton().Content(box_value(StrUsingStr(f_ProductPriceText)));

					float f_CostECN = f_CostCPS / g_Wallet->m_Price;

					char* prodecnquery = ag_ClearChar(1000);
					std::sprintf(prodecnquery, "Pay %.2fecn", f_CostECN);
					std::string f_ProductECNPriceText = prodecnquery;
					delete prodecnquery;

					shopslotB6payecnbutton().Content(box_value(StrUsingStr(f_ProductECNPriceText)));

					shopslotB6nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6panelbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6combutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6previewbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					shopslotB6rectangle().Visibility(Windows::UI::Xaml::Visibility::Visible);
					}
				}
			else
				{
				if(f_BX == ((f_Page * 12) + 6))
					{
					shopslotB1nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB1rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if(f_BX == ((f_Page * 12) + 7))
					{
					shopslotB2nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB2rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if(f_BX == ((f_Page * 12) + 8))
					{
					shopslotB3nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB3rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if (f_BX == ((f_Page * 12) + 9))
					{
					shopslotB4nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB4rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if (f_BX == ((f_Page * 12) + 10))
					{
					shopslotB5nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB5rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				else if (f_BX == ((f_Page * 12) + 11))
					{
					shopslotB6nametextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6descriptiontextBlock().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6panelbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6paycpsbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6payecnbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6combutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6previewbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6panelRectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					shopslotB6rectangle().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
					}
				}
			}

		int f_StartValue = f_Page * 12;
		int f_EndValue = (f_Page + 1) * 12;

		char pagequery[1000];
		std::sprintf(pagequery, "%i-%i", f_StartValue, f_EndValue);
		std::string f_PageText = pagequery;

		shopsearchpagetextBlock().Text(StrUsingStr(f_PageText));
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductA1(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12)];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductA2(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 1];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductA3(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 2];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));
				
					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductA4(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 3];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductA5(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 4];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductA6(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 5];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductB1(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 6];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductB2(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 7];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductB3(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 8];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductB4(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 9];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductB5(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 10];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickOpenProductB6(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop open,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 11];

			int f_ShareID = f_Product->m_ShareID;

			if((g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_CostCPS, f_Product->m_ComID) == true) /*FREE|| (f_Product->m_Score == 0)*/)
				{
				g_ShareID = f_ShareID;
				acLoadShare(f_ShareID, 0);

				//reset win
				g_PreComInclude = false;
				g_PreComLock = false;
				g_PreComBool = false;
				g_PreComBoughtIN = 0;

				g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickCurrentSkip(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_LowtonMark = 10000000.0f;

		time(&g_storagetime);
		g_storagetime += LOWTON_STORAGE;
	}

	void SecondaryAppWindowPageDX::OnClickCurrentKeep(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(currentskipbutton().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			currentskipbutton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			currentkeepbutton().Content(box_value(L"Keeping Share"));

			g_KeepShare = true;
			}
		else
			{
			currentskipbutton().Visibility(Windows::UI::Xaml::Visibility::Visible);
			currentkeepbutton().Content(box_value(L"Keep Current Share"));

			g_KeepShare = false;

			time(&g_storagetime);
			g_storagetime += LOWTON_STORAGE;
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopA1PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12)];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopA2PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 1];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopA3PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 2];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopA4PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 3];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopA5PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 4];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopA6PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 5];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopB1PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 6];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopB2PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 7];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopB3PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 8];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopB4PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 9];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopB5PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 10];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickshopB6PayCPS(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		double f_BalanceCPS = g_Wallet->GetBalanceCPS(true, 0);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
			{
			shopresultstextBlock().Text(L"Oops please pause divining or compression for shop buy product,...");
			}
		else
			{
			std::shared_ptr<eshop_Product> f_Product = m_ShareShop->m_vec_Product[((m_ShareShop->m_ShopPage - 1) * 12) + 11];

			float f_PaidAmt = g_Wallet->acGet_assetContractbyID(f_Product->m_ShareID, f_Product->m_ComID);

			if(f_PaidAmt == -5.0)
				{
				shopresultstextBlock().Text(L"Oops...Cannot buy your own component...");
				}
			else if(f_PaidAmt == -1.0)
				{
				shopresultstextBlock().Text(L"Sorry...Component does not exist...");
				}
			else
				{
				if(f_PaidAmt < f_Product->m_CostCPS)
					{
					if(f_Product->m_CostCPS <= f_BalanceCPS)
						{
						float f_BillAmt = f_Product->m_CostCPS - f_PaidAmt;

						bool f_buyresult = g_Wallet->acBuy_ShareComID(f_Product->m_ComID, f_BillAmt, f_Product->m_CostCPS, f_Product->m_ShareID);

						if(f_buyresult == true)
							{
							shopresultstextBlock().Text(L"Awesome Job! Successfull Purchase!");
							}
						else
							{
							shopresultstextBlock().Text(L"Sorry! unsuccessfull Purchase...");
							}
						}
					else
						{
						shopresultstextBlock().Text(L"Sorry! Deposit More eGBP Purchase Too Expensive...");
						}
					}
				else
					{
					shopresultstextBlock().Text(L"...Already paid...or cost zero...");
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickDecisions(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(decisionsStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			decisionsStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			decisionsStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

			::g_QcomManager->m_Open = true;
			}
	}

	void SecondaryAppWindowPageDX::OnClickDecisionUp(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(0.0f, 1.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageDX::OnClickDecisionRight(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(1.0f, 0.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageDX::OnClickDecisionLeft(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(-1.0f, 0.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageDX::OnClickDecisionDown(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(0.0f, -1.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageDX::OnClickDecisionIn(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acPressIn();

		int f_CurrentLayer = g_vec_DecisionsManager[0]->m_Wheel->m_Layer;
		int f_CurrentPosition = g_vec_DecisionsManager[0]->m_Wheel->m_LayerPos;

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i-%i)", f_CurrentLayer, f_CurrentPosition);

		std::string f_Str(f_Char);

		delete f_Char;

		char* f_Charo = ag_ClearChar(255);

		sprintf(f_Charo, "%i)", f_CurrentLayer - 1);

		std::string f_Stro(f_Charo);

		delete f_Charo;

		decisionsinbutton().Content(box_value(StrUsingStr("IN One Layer (" + f_Str)));
		decisionsoutbutton().Content(box_value(StrUsingStr("Out One Layer (" + f_Stro)));
	}

	void SecondaryAppWindowPageDX::OnClickDecisionOut(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acPressOut();

		int f_CurrentLayer = g_vec_DecisionsManager[0]->m_Wheel->m_Layer;
		int f_CurrentPosition = g_vec_DecisionsManager[0]->m_Wheel->m_LayerPos;

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i-%i)", f_CurrentLayer, f_CurrentPosition);

		std::string f_Str(f_Char);

		delete f_Char;

		char* f_Charo = ag_ClearChar(255);

		sprintf(f_Charo, "%i)", f_CurrentLayer - 1);

		std::string f_Stro(f_Charo);

		delete f_Charo;

		decisionsinbutton().Content(box_value(StrUsingStr("IN One Layer (" + f_Str)));
		decisionsoutbutton().Content(box_value(StrUsingStr("Out One Layer (" + f_Stro)));
	}

	void SecondaryAppWindowPageDX::OnClickComFunction(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
	{
		winrt::hstring buttonName = sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name();

		std::vector<std::shared_ptr<BiPacket>> f_Packet = ::g_QcomManager->acSearch_PacketbyName(to_string(buttonName));

		for(int f_XY = 0; f_XY < f_Packet.size(); f_XY++)
			{
			if(f_Packet[f_XY]->m_Name.length() > 0)
				{
				std::shared_ptr<Qcom> f_com = f_Packet[f_XY]->m_Operator_Com;

				f_com->ac_Execute();
				}
			}
	}

	std::byte HexToByteUsingByteManipulation(std::string s)
	{
		std::byte byte_result;

		int hi = s[0] - 65;
		hi = hi + 10 + ((hi >> 31) & 7);

		int lo = s[1] - 65;
		lo = lo + 10 + ((lo >> 31) & 7) & 0x0f;

		byte_result = (std::byte) (lo | hi << 4);

		return byte_result;
	}

#if 1
		///////////////////////////////////////////
	   // Ecom Building Generation Script
	  //
	void SecondaryAppWindowPageDX::acBuild_ExcomPackaging(void)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::acBuild_ExcomPackaging";

		for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Packet.size(); f_XY++)
			{
			winrt::Windows::UI::Xaml::Controls::Button g_ecomButton({ nullptr });
			winrt::Windows::UI::Xaml::Controls::Grid g_ecomGrid({ nullptr });
			winrt::Windows::UI::Xaml::Controls::StackPanel g_ecomStackPanel({ nullptr });
			winrt::Windows::UI::Xaml::Controls::TextBlock g_TextBlock({ nullptr });
			winrt::Windows::UI::Xaml::Controls::TextBox g_TextBox({ nullptr });
			winrt::Windows::UI::Xaml::Media::LinearGradientBrush g_ecomLinearGradientBrush({ nullptr });
			winrt::Windows::UI::Xaml::Media::GradientStop g_ecomGradientStop({ nullptr });

			std::shared_ptr<BiPacket> f_Packet = g_QcomManager->m_vec_Packet[f_XY];

			if(f_Packet->m_Activate_Status == COM_PAK_UNACTIVATED)
				{
				bool f_Fail_PacketIncomplete = false;

				switch(f_Packet->m_InsertElementType)
					{
					case COM_PAK_TYPE_INSERT:
						{
						switch(f_Packet->m_ClassType)
							{
							case ctVariable:
								{
								}break;

							case ctCClass:
								{
								}break;

							case ctQcom:
								{
								}break;

							case ctQcomInput:
								{
								std::string f_DefaultPacket = f_Packet->m_DefaultValue;

								f_Packet->m_vec_Package_XElement_Title.clear();
								f_Packet->m_vecvec_Package_Arg_Title.clear();
								f_Packet->m_vecvec_Package_Arg_Data.clear();

								std::string f_Packets = "";
								bool f_Some = false;
								int f_InputStage = 0;

								for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
									{
									if(f_Fail_PacketIncomplete == false)
										{
										char f_c = f_DefaultPacket.at(f_CCount);

										switch(f_InputStage)
											{
											case COM_PAKX_STAGE_TITLE:
												{
												if(f_c == '_')
													{
													f_Packet->m_vec_Package_XElement_Title.push_back(f_Packets);

													std::vector<std::string> f_vec_String;
													f_vec_String.clear();

													f_Packet->m_vecvec_Package_Arg_Title.push_back(f_vec_String);
													f_Packet->m_vecvec_Package_Arg_Data.push_back(f_vec_String);

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '-')
													{
													f_Packet->m_vecvec_Package_Arg_Title[f_Packet->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
													f_Packet->m_vecvec_Package_Arg_Data[f_Packet->m_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=') //win
													{
													if(f_Packet->m_vec_Package_XElement_Title.size() >= 1)
														{
														if(f_Packet->m_vecvec_Package_Arg_Title.size() >= 1)
															{
															f_Packet->m_vecvec_Package_Arg_Title[f_Packet->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															}
														else
															{
#ifdef ECOIN_SECURE
															throw;
#endif
															}
														}

													f_InputStage = COM_PAKX_STAGE_EQUAL;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;

											case COM_PAKX_STAGE_EQUAL:
												{
												if(f_c == '_')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_InputStage = COM_PAKX_STAGE_QUOTE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												}break;

											case COM_PAKX_STAGE_QUOTE:
												{
												if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_Packet->m_vecvec_Package_Arg_Data[f_Packet->m_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

#if 0
												if(f_CCount >= f_DefaultPacket.length() - 1)
													{
													f_Packet->m_vecvec_Package_Arg_Data[f_Packet->m_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
#endif
												}break;
											}
										}
									}

								if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_Packet->m_vec_Package_XElement_Title.size() <= 0))
									{
									f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
									throw;
#endif
									}

								if(f_Fail_PacketIncomplete == false)
									{
									for(int f_IDX = 0; f_IDX < f_Packet->m_vec_Package_XElement_Title.size(); f_IDX++)
										{
										if(f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("QcomInput") == 0 ||
											f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("ecomInput") == 0 ||
											f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("Input") == 0)
											{
											ag_StatusLive(f_ref_CurrentPath, "f_Input");
											std::shared_ptr<QcomInput> f_Input = ::std::make_shared_reflect<QcomInput>();

											f_Input->m_name = f_Packet->m_Name;

											f_Packet->m_Operator_Com->m_vec_Input.push_back(f_Input);
											g_QcomManager->m_vec_Input.push_back(f_Input);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positionx") == 0)
													{
													float f_Float = atof(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Input->m_position->m_X = f_Float;
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positiony") == 0)
													{
													float f_Float = atof(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Input->m_position->m_Y = f_Float;
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("float") == 0)
													{
													float f_Float = atof(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													std::string f_GatheredNameGroup_String = f_Packet->m_Operator_Com->m_name + g_ref_InOut_Var + f_Input->m_name + g_ref_InOut_Var + "float" + g_ref_InOut_Var;

													if(f_Input->m_vec_InputVar.size() >= 1)
														{
														char* f_char = ag_ClearChar(256);
														sprintf(f_char, "%i/", f_Input->m_vec_InputVar.size());

														f_GatheredNameGroup_String += f_char;
														delete f_char;
														}

													////ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
													std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

													f_MxVar->m_Var = f_Float;

													f_Input->m_vec_InputVar.push_back(f_MxVar);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("int") == 0)
													{
													int f_Int = atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													std::string f_GatheredNameGroup_String = f_Packet->m_Operator_Com->m_name + g_ref_InOut_Var + f_Input->m_name + g_ref_InOut_Var + "int" + g_ref_InOut_Var;

													if(f_Input->m_vec_InputVar.size() >= 1)
														{
														char* f_char = ag_ClearChar(256);
														sprintf(f_char, "%i/", f_Input->m_vec_InputVar.size());

														f_GatheredNameGroup_String += f_char;
														delete f_char;
														}

													//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
													std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

													f_MxVar->m_Var = f_Int;

													f_Input->m_vec_InputVar.push_back(f_MxVar);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("string") == 0)
													{
													std::string f_String = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_GatheredNameGroup_String = f_Packet->m_Operator_Com->m_name + g_ref_InOut_Var + f_Input->m_name + g_ref_InOut_Var + "string" + g_ref_InOut_Var;

													if(f_Input->m_vec_InputVar.size() >= 1)
														{
														char* f_char = ag_ClearChar(256);
														sprintf(f_char, "%i/", f_Input->m_vec_InputVar.size());

														f_GatheredNameGroup_String += f_char;
														delete f_char;
														}

													//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
													std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

													f_MxVar->m_Var = f_String;

													f_Input->m_vec_InputVar.push_back(f_MxVar);
													}
												}
											}
										}
									}
								}break;

							case ctQcomOutput:
								{
								std::string f_DefaultPacket = f_Packet->m_DefaultValue;

								f_Packet->m_vec_Package_XElement_Title.clear();
								f_Packet->m_vecvec_Package_Arg_Title.clear();
								f_Packet->m_vecvec_Package_Arg_Data.clear();

								std::string f_Packets = "";
								bool f_Some = false;
								int f_InputStage = 0;

								for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
									{
									if(f_Fail_PacketIncomplete == false)
										{
										char f_c = f_DefaultPacket.at(f_CCount);

										switch(f_InputStage)
											{
											case COM_PAKX_STAGE_TITLE:
												{
												if(f_c == '_')
													{
													f_Packet->m_vec_Package_XElement_Title.push_back(f_Packets);

													std::vector<std::string> f_vec_String;
													f_vec_String.clear();

													f_Packet->m_vecvec_Package_Arg_Title.push_back(f_vec_String);
													f_Packet->m_vecvec_Package_Arg_Data.push_back(f_vec_String);

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '-')
													{
													f_Packet->m_vecvec_Package_Arg_Title[f_Packet->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
													f_Packet->m_vecvec_Package_Arg_Data[f_Packet->m_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=') //win
													{
													if(f_Packet->m_vec_Package_XElement_Title.size() >= 1)
														{
														if(f_Packet->m_vecvec_Package_Arg_Title.size() >= 1)
															{
															f_Packet->m_vecvec_Package_Arg_Title[f_Packet->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															}
														else
															{
#ifdef ECOIN_SECURE
															throw;
#endif
															}
														}

													f_InputStage = COM_PAKX_STAGE_EQUAL;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;

											case COM_PAKX_STAGE_EQUAL:
												{
												if(f_c == '_')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_InputStage = COM_PAKX_STAGE_QUOTE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												}break;

											case COM_PAKX_STAGE_QUOTE:
												{
												if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_Packet->m_vecvec_Package_Arg_Data[f_Packet->m_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;
											}
										}
									}

								if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_Packet->m_vec_Package_XElement_Title.size() <= 0))
									{
									f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
									throw;
#endif
									}

								if(f_Fail_PacketIncomplete == false)
									{
									for(int f_IDX = 0; f_IDX < f_Packet->m_vec_Package_XElement_Title.size(); f_IDX++)
										{
										if(f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("QcomOutput") == 0 ||
											f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("ecomOutput") == 0 ||
											f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("Output") == 0)
											{
											ag_StatusLive(f_ref_CurrentPath, "f_Output");
											std::shared_ptr<QcomOutput> f_Output = ::std::make_shared_reflect<QcomOutput>();

											f_Output->m_name = f_Packet->m_Name;

											f_Packet->m_Operator_Com->m_vec_Output.push_back(f_Output);
											g_QcomManager->m_vec_Output.push_back(f_Output);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positionx") == 0)
													{
													float f_Float = atof(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Output->m_position->m_X = f_Float;
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("positiony") == 0)
													{
													float f_Float = atof(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													f_Output->m_position->m_Y = f_Float;
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("float") == 0)
													{
													float f_Float = atof(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													std::string f_GatheredNameGroup_String = f_Packet->m_Operator_Com->m_name + g_ref_InOut_Var + f_Output->m_name + g_ref_InOut_Var + "float" + g_ref_InOut_Var;

													if(f_Output->m_vec_OutputVar.size() >= 1)
														{
														char* f_char = ag_ClearChar(256);
														sprintf(f_char, "%i/", f_Output->m_vec_OutputVar.size());

														f_GatheredNameGroup_String += f_char;
														delete f_char;
														}

													//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
													std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

													f_MxVar->m_Var = f_Float;

													f_Output->m_vec_OutputVar.push_back(f_MxVar);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("int") == 0)
													{
													int f_Int = atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str());

													std::string f_GatheredNameGroup_String = f_Packet->m_Operator_Com->m_name + g_ref_InOut_Var + f_Output->m_name + g_ref_InOut_Var + "int" + g_ref_InOut_Var;

													if(f_Output->m_vec_OutputVar.size() >= 1)
														{
														char* f_char = ag_ClearChar(256);
														sprintf(f_char, "%i/", f_Output->m_vec_OutputVar.size());

														f_GatheredNameGroup_String += f_char;
														delete f_char;
														}

													//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
													std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

													f_MxVar->m_Var = f_Int;

													f_Output->m_vec_OutputVar.push_back(f_MxVar);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("string") == 0)
													{
													std::string f_String = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_GatheredNameGroup_String = f_Packet->m_Operator_Com->m_name + g_ref_InOut_Var + f_Output->m_name + g_ref_InOut_Var + "string" + g_ref_InOut_Var;

													if(f_Output->m_vec_OutputVar.size() >= 1)
														{
														char* f_char = ag_ClearChar(256);
														sprintf(f_char, "%i/", f_Output->m_vec_OutputVar.size());

														f_GatheredNameGroup_String += f_char;
														delete f_char;
														}

													//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
													std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

													f_MxVar->m_Var = f_String;

													f_Output->m_vec_OutputVar.push_back(f_MxVar);
													}
												}
											}
										}
									}
								}break;

							case ctComFunctionX:
								{
								std::string f_DefaultPacket = f_Packet->m_DefaultValue;

								f_Packet->m_vec_Package_XElement_Title.clear();
								f_Packet->m_vecvec_Package_Arg_Title.clear();
								f_Packet->m_vecvec_Package_Arg_Data.clear();

								std::string f_Packets = "";
								bool f_Some = false;
								int f_InputStage = 0;

								for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
									{
									if(f_Fail_PacketIncomplete == false)
										{
										char f_c = f_DefaultPacket.at(f_CCount);

										switch(f_InputStage)
											{
											case COM_PAKX_STAGE_TITLE:
												{
												if(f_c == '_')
													{
													f_Packet->m_vec_Package_XElement_Title.push_back(f_Packets);

													std::vector<std::string> f_vec_String;
													f_vec_String.clear();

													f_Packet->m_vecvec_Package_Arg_Title.push_back(f_vec_String);
													f_Packet->m_vecvec_Package_Arg_Data.push_back(f_vec_String);

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '-')
													{
													f_Packet->m_vecvec_Package_Arg_Title[f_Packet->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
													f_Packet->m_vecvec_Package_Arg_Data[f_Packet->m_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=') //win
													{
													if(f_Packet->m_vec_Package_XElement_Title.size() >= 1)
														{
														if(f_Packet->m_vecvec_Package_Arg_Title.size() >= 1)
															{
															f_Packet->m_vecvec_Package_Arg_Title[f_Packet->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															}
														else
															{
#ifdef ECOIN_SECURE
															throw;
#endif
															}
														}

													f_InputStage = COM_PAKX_STAGE_EQUAL;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;

											case COM_PAKX_STAGE_EQUAL:
												{
												if(f_c == '_')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_InputStage = COM_PAKX_STAGE_QUOTE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}

												}break;

											case COM_PAKX_STAGE_QUOTE:
												{
												if(f_c == '=')
													{
													f_Fail_PacketIncomplete = true;
													f_CCount = f_DefaultPacket.length();
													f_InputStage = COM_PAKX_STAGE_OFF;

													f_Packets.clear();
													f_Some = false;
													}
												else if(f_c == '"') //win
													{
													f_Packet->m_vecvec_Package_Arg_Data[f_Packet->m_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

													f_InputStage = COM_PAKX_STAGE_TITLE;

													f_Packets.clear();
													f_Some = false;
													}
												else //record
													{
													f_Packets.push_back(f_c);

													f_Some = true;
													}
												}break;
											}
										}
									}

								if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_Packet->m_vec_Package_XElement_Title.size() <= 0))
									{
									f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
									throw;
#endif
									}

								if(f_Fail_PacketIncomplete == false)
									{
									for(int f_IDX = 0; f_IDX < f_Packet->m_vec_Package_XElement_Title.size(); f_IDX++)
										{
										if(f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("Button") == 0)
											{
											//set knowns
											winrt::Windows::UI::Xaml::Controls::Button f_ecomButton({});
											
											g_ecomButton = f_ecomButton;

											f_ecomButton.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" });

											f_ecomButton.FontFamily(myFont);

											f_ecomButton.Click({ this, &SecondaryAppWindowPageDX::OnClickComFunction });

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Title[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Content") == 0)
													{
													f_ecomButton.Content(box_value(StrUsingStr(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet])));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Foreground") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.Foreground(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Background") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.Background(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("BorderBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.BorderBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FontFamily") == 0)
													{
													Windows::UI::Xaml::Media::FontFamily myFontB({ StrUsingStr(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet]) });

													f_ecomButton.FontFamily(myFontB);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Height") == 0)
													{
													f_ecomButton.Height(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Width") == 0)
													{
													f_ecomButton.Width(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("VerticalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														f_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														f_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("HorizontalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														f_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														f_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													f_ecomButton.Margin(myThickness);
													}
												}

											swapChainPanel().Children().Append(f_ecomButton);
											}
										else if(f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("StackPanel") == 0)
											{
											//set knowns
											winrt::Windows::UI::Xaml::Controls::StackPanel f_ecomStackPanel({});
											
											g_ecomStackPanel = f_ecomStackPanel;

											f_ecomStackPanel.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											//f_ecomStackPanel.Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Background") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomStackPanel.Background(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("BorderBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomStackPanel.BorderBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomStackPanel.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomStackPanel.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Height") == 0)
													{
													f_ecomStackPanel.Height(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Width") == 0)
													{
													f_ecomStackPanel.Width(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("VerticalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														f_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														f_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_ecomStackPanel.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("HorizontalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														f_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														f_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_ecomStackPanel.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													f_ecomStackPanel.Margin(myThickness);
													}
												}

											swapChainPanel().Children().Append(f_ecomStackPanel);
											}
										else if(f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("Grid") == 0)
											{
											//set knowns
											Windows::UI::Xaml::Controls::Grid f_ecomGrid({});
											
											g_ecomGrid = f_ecomGrid;

											f_ecomGrid.Name(StrUsingStr(f_Packet->m_Name));

											Windows::UI::Xaml::Controls::ColumnDefinition myCollumn({});
											Windows::UI::Xaml::Controls::RowDefinition myRow({});

											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.ColumnDefinitions().Append(myCollumn);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);
											f_ecomGrid.RowDefinitions().Append(myRow);

											//set defaults
											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Background") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomGrid.Background(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("BorderBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomGrid.BorderBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomGrid.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomGrid.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Height") == 0)
													{
													f_ecomGrid.Height(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Width") == 0)
													{
													f_ecomGrid.Width(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("VerticalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														f_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														f_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_ecomGrid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("HorizontalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														f_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														f_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_ecomGrid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													f_ecomGrid.Margin(myThickness);
													}
												}

											swapChainPanel().Children().Append(f_ecomGrid);
											}
										else if(f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("TextBlock") == 0)
											{
											Windows::UI::Xaml::Controls::TextBlock f_TextBlock({});
											
											g_TextBlock = f_TextBlock;

											//set knowns
											f_TextBlock.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" }); 

											f_TextBlock.FontFamily(myFont);

											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Text") == 0)
													{
													f_TextBlock.Text(StrUsingStr(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet]));
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Foreground") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.Foreground(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("SelectionHighlightColor") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.SelectionHighlightColor(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FontFamily") == 0)
													{
													Windows::UI::Xaml::Media::FontFamily myFontB({ StrUsingStr(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet]) });

													f_TextBlock.FontFamily(myFontB);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Height") == 0)
													{
													f_TextBlock.Height(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Width") == 0)
													{
													f_TextBlock.Width(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("VerticalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("HorizontalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													f_TextBlock.Margin(myThickness);
													}
												}

											swapChainPanel().Children().Append(f_TextBlock);
											}
										else if(f_Packet->m_vec_Package_XElement_Title[f_IDX].compare("TextBox") == 0)
											{
											Windows::UI::Xaml::Controls::TextBox f_TextBox;

											g_TextBox = f_TextBox;

											//set knowns
											f_TextBox.Name(StrUsingStr(f_Packet->m_Name));

											//set defaults
											Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" });

											f_TextBox.FontFamily(myFont);

											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Text") == 0)
													{
													f_TextBox.Text(StrUsingStr(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet]));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Foreground") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.Foreground(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("SelectionHighlightColor") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.SelectionHighlightColor(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.FocusVisualSecondaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FontFamily") == 0)
													{
													Windows::UI::Xaml::Media::FontFamily myFontB(StrUsingStr(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet]));

													f_TextBox.FontFamily(myFontB);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Height") == 0)
													{
													f_TextBox.Height(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Width") == 0)
													{
													f_TextBox.Width(atoi(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].c_str()));
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("VerticalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Top") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Bottom") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
														}
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("HorizontalAlignment") == 0)
													{
													if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Left") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Right") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Stretch") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
														}
													else if(f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet].compare("Center") == 0)
														{
														f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
														}
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Margin") == 0)
													{
													std::string f_DataPacket = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];

													std::string f_vec_Pack_A1;
													std::string f_vec_Pack_A2;
													std::string f_vec_Pack_A3;
													std::string f_vec_Pack_A4;

													f_vec_Pack_A1.clear();
													f_vec_Pack_A2.clear();
													f_vec_Pack_A3.clear();
													f_vec_Pack_A4.clear();

													std::string f_Packetss = "";
													
													int f_InputStages = 0;

													for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
														{
														if(f_Fail_PacketIncomplete == false)
															{
															char f_c = f_DataPacket.at(f_CCount);

															if(f_c == ',')
																{
																f_InputStages++;
																}
															else
																{
																switch(f_InputStages)
																	{
																	case 0:
																		{
																		f_vec_Pack_A1.push_back(f_c);
																		}break;

																	case 1:
																		{
																		f_vec_Pack_A2.push_back(f_c);
																		}break;

																	case 2:
																		{
																		f_vec_Pack_A3.push_back(f_c);
																		}break;

																	case 3:
																		{
																		f_vec_Pack_A4.push_back(f_c);
																		}break;
																	}
																}
															}
														}

													Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

													f_TextBox.Margin(myThickness);
													}
												}

											swapChainPanel().Children().Append(f_TextBox);
											}
										}
									}
								}break;

							case ctEClass:
								{
								}break;

							case ctShare:
								{
								}break;

							case ctElement:
								{
								}break;

							default:
								{
								//g_ExcomPexMain->acExecute(EXCOM_MAIN_INSERT_IDX, 0, f_Packet->m_ClassType);
								}break;
							}

						for(int f_LP = 0; f_LP < f_Packet->m_vec_Packet.size(); f_LP++)
							{
							std::shared_ptr<BiPacket> f_PacketLP = f_Packet->m_vec_Packet[f_LP];

							if(f_PacketLP->m_InsertElementType == COM_PAK_TYPE_COMPLETE)
								{
								switch(f_PacketLP->m_ClassType)
									{
									case ctVariable:
										{
										}break;

									case ctCClass:
										{
										}break;

									case ctQcom:
										{
										}break;

									case ctQcomInput:
										{
										std::string f_DefaultPacket = f_PacketLP->m_DefaultValue;

										f_PacketLP->m_vec_Package_XElement_Title.clear();
										f_PacketLP->m_vecvec_Package_Arg_Title.clear();
										f_PacketLP->m_vecvec_Package_Arg_Data.clear();

										std::string f_Packets = "";
										bool f_Some = false;
										int f_InputStage = 0;

										for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
											{
											if(f_Fail_PacketIncomplete == false)
												{
												char f_c = f_DefaultPacket.at(f_CCount);

												switch(f_InputStage)
													{
													case COM_PAKX_STAGE_TITLE:
														{
														if(f_c == '_')
															{
															f_PacketLP->m_vec_Package_XElement_Title.push_back(f_Packets);

															std::vector<std::string> f_vec_String;
															f_vec_String.clear();

															f_PacketLP->m_vecvec_Package_Arg_Title.push_back(f_vec_String);
															f_PacketLP->m_vecvec_Package_Arg_Data.push_back(f_vec_String);

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '-')
															{
															f_PacketLP->m_vecvec_Package_Arg_Title[f_PacketLP->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															f_PacketLP->m_vecvec_Package_Arg_Data[f_PacketLP->m_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=') //win
															{
															if(f_PacketLP->m_vec_Package_XElement_Title.size() >= 1)
																{
																if(f_PacketLP->m_vecvec_Package_Arg_Title.size() >= 1)
																	{
																	f_PacketLP->m_vecvec_Package_Arg_Title[f_PacketLP->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
																	}
																else
																	{
#ifdef ECOIN_SECURE
																	throw;
#endif
																	}
																}

															f_InputStage = COM_PAKX_STAGE_EQUAL;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}
														}break;

													case COM_PAKX_STAGE_EQUAL:
														{
														if(f_c == '_')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_InputStage = COM_PAKX_STAGE_QUOTE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}

														}break;

													case COM_PAKX_STAGE_QUOTE:
														{
														if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_PacketLP->m_vecvec_Package_Arg_Data[f_PacketLP->m_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

															f_InputStage = COM_PAKX_STAGE_TITLE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}
														}break;
													}
												}
											}

										if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_PacketLP->m_vec_Package_XElement_Title.size() <= 0))
											{
											f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
											throw;
#endif
											}

										if(f_Fail_PacketIncomplete == false)
											{
											for(int f_IDY = 0; f_IDY < f_PacketLP->m_vec_Package_XElement_Title.size(); f_IDY++)
												{
												if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("QcomInput") == 0 ||
													f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("ecomInput") == 0 ||
													f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Input") == 0)
													{
													ag_StatusLive(f_ref_CurrentPath, "f_Input");
													std::shared_ptr<QcomInput> f_Input = ::std::make_shared_reflect<QcomInput>();

													f_Input->m_name = f_PacketLP->m_Name;

													f_PacketLP->m_Operator_Com->m_vec_Input.push_back(f_Input);
													g_QcomManager->m_vec_Input.push_back(f_Input);

													//xeff

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("positionx") == 0)
															{
															float f_Float = atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															f_Input->m_position->m_X = f_Float;
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("positiony") == 0)
															{
															float f_Float = atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															f_Input->m_position->m_Y = f_Float;
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("float") == 0)
															{
															float f_Float = atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															std::string f_GatheredNameGroup_String = f_PacketLP->m_Operator_Com->m_name + g_ref_InOut_Var + f_Input->m_name + g_ref_InOut_Var + "float" + g_ref_InOut_Var;

															if(f_Input->m_vec_InputVar.size() >= 1)
																{
																char* f_char = ag_ClearChar(256);
																sprintf(f_char, "%i/", f_Input->m_vec_InputVar.size());

																f_GatheredNameGroup_String += f_char;
																delete f_char;
																}

															//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
															std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

															f_MxVar->m_Var = f_Float;

															f_Input->m_vec_InputVar.push_back(f_MxVar);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("int") == 0)
															{
															int f_Int = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															std::string f_GatheredNameGroup_String = f_PacketLP->m_Operator_Com->m_name + g_ref_InOut_Var + f_Input->m_name + g_ref_InOut_Var + "int" + g_ref_InOut_Var;

															if(f_Input->m_vec_InputVar.size() >= 1)
																{
																char* f_char = ag_ClearChar(256);
																sprintf(f_char, "%i/", f_Input->m_vec_InputVar.size());

																f_GatheredNameGroup_String += f_char;
																delete f_char;
																}

															//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
															std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

															f_MxVar->m_Var = f_Int;

															f_Input->m_vec_InputVar.push_back(f_MxVar);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("string") == 0)
															{
															std::string f_String = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															std::string f_GatheredNameGroup_String = f_PacketLP->m_Operator_Com->m_name + g_ref_InOut_Var + f_Input->m_name + g_ref_InOut_Var + "string" + g_ref_InOut_Var;

															if(f_Input->m_vec_InputVar.size() >= 1)
																{
																char* f_char = ag_ClearChar(256);
																sprintf(f_char, "%i/", f_Input->m_vec_InputVar.size());

																f_GatheredNameGroup_String += f_char;
																delete f_char;
																}

															//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
															std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

															f_MxVar->m_Var = f_String;

															f_Input->m_vec_InputVar.push_back(f_MxVar);
															}
														}
													}
												}
											}
										}break;

									case ctQcomOutput:
										{
										std::string f_DefaultPacket = f_PacketLP->m_DefaultValue;

										f_PacketLP->m_vec_Package_XElement_Title.clear();
										f_PacketLP->m_vecvec_Package_Arg_Title.clear();
										f_PacketLP->m_vecvec_Package_Arg_Data.clear();

										std::string f_Packets = "";
										bool f_Some = false;
										int f_InputStage = 0;

										for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
											{
											if(f_Fail_PacketIncomplete == false)
												{
												char f_c = f_DefaultPacket.at(f_CCount);

												switch(f_InputStage)
													{
													case COM_PAKX_STAGE_TITLE:
														{
														if(f_c == '_')
															{
															f_PacketLP->m_vec_Package_XElement_Title.push_back(f_Packets);

															std::vector<std::string> f_vec_String;
															f_vec_String.clear();

															f_PacketLP->m_vecvec_Package_Arg_Title.push_back(f_vec_String);
															f_PacketLP->m_vecvec_Package_Arg_Data.push_back(f_vec_String);

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '-')
															{
															f_PacketLP->m_vecvec_Package_Arg_Title[f_PacketLP->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															f_PacketLP->m_vecvec_Package_Arg_Data[f_PacketLP->m_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=') //win
															{
															if(f_PacketLP->m_vec_Package_XElement_Title.size() >= 1)
																{
																if(f_PacketLP->m_vecvec_Package_Arg_Title.size() >= 1)
																	{
																	f_PacketLP->m_vecvec_Package_Arg_Title[f_PacketLP->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
																	}
																else
																	{
#ifdef ECOIN_SECURE
																	throw;
#endif
																	}
																}

															f_InputStage = COM_PAKX_STAGE_EQUAL;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}
														}break;

													case COM_PAKX_STAGE_EQUAL:
														{
														if(f_c == '_')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_InputStage = COM_PAKX_STAGE_QUOTE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}

														}break;

													case COM_PAKX_STAGE_QUOTE:
														{
														if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_PacketLP->m_vecvec_Package_Arg_Data[f_PacketLP->m_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

															f_InputStage = COM_PAKX_STAGE_TITLE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}
														}break;
													}
												}
											}

										if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_PacketLP->m_vec_Package_XElement_Title.size() <= 0))
											{
											f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
											throw;
#endif
											}

										if(f_Fail_PacketIncomplete == false)
											{
											for(int f_IDY = 0; f_IDY < f_PacketLP->m_vec_Package_XElement_Title.size(); f_IDY++)
												{
												if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("QcomOutput") == 0 ||
													f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("ecomOutput") == 0 ||
													f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Output") == 0)
													{
													ag_StatusLive(f_ref_CurrentPath, "f_Output");
													std::shared_ptr<QcomOutput> f_Output = ::std::make_shared_reflect<QcomOutput>();

													f_Output->m_name = f_PacketLP->m_Name;

													f_PacketLP->m_Operator_Com->m_vec_Output.push_back(f_Output);
													g_QcomManager->m_vec_Output.push_back(f_Output);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("positionx") == 0)
															{
															float f_Float = atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															f_Output->m_position->m_X = f_Float;
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("positiony") == 0)
															{
															float f_Float = atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															f_Output->m_position->m_Y = f_Float;
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("float") == 0)
															{
															float f_Float = atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															std::string f_GatheredNameGroup_String = f_PacketLP->m_Operator_Com->m_name + g_ref_InOut_Var + f_Output->m_name + g_ref_InOut_Var + "float" + g_ref_InOut_Var;

															if(f_Output->m_vec_OutputVar.size() >= 1)
																{
																char* f_char = ag_ClearChar(256);
																sprintf(f_char, "%i/", f_Output->m_vec_OutputVar.size());

																f_GatheredNameGroup_String += f_char;
																delete f_char;
																}

															//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
															std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

															f_MxVar->m_Var = f_Float;

															f_Output->m_vec_OutputVar.push_back(f_MxVar);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("int") == 0)
															{
															int f_Int = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															std::string f_GatheredNameGroup_String = f_PacketLP->m_Operator_Com->m_name + g_ref_InOut_Var + f_Output->m_name + g_ref_InOut_Var + "int" + g_ref_InOut_Var;

															if(f_Output->m_vec_OutputVar.size() >= 1)
																{
																char* f_char = ag_ClearChar(256);
																sprintf(f_char, "%i/", f_Output->m_vec_OutputVar.size());

																f_GatheredNameGroup_String += f_char;
																delete f_char;
																}

															//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
															std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

															f_MxVar->m_Var = f_Int;

															f_Output->m_vec_OutputVar.push_back(f_MxVar);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("string") == 0)
															{
															std::string f_String = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															std::string f_GatheredNameGroup_String = f_PacketLP->m_Operator_Com->m_name + g_ref_InOut_Var + f_Output->m_name + g_ref_InOut_Var + "string" + g_ref_InOut_Var;

															if(f_Output->m_vec_OutputVar.size() >= 1)
																{
																char* f_char = ag_ClearChar(256);
																sprintf(f_char, "%i/", f_Output->m_vec_OutputVar.size());

																f_GatheredNameGroup_String += f_char;
																delete f_char;
																}

															//ag_StatusLive(f_ref_CurrentPath, "f_MxVar");
															std::shared_ptr<Variable> f_MxVar = std::make_shared<Variable>(f_GatheredNameGroup_String, MuCode_Var);

															f_MxVar->m_Var = f_String;

															f_Output->m_vec_OutputVar.push_back(f_MxVar);
															}
														}
													}
												}
											}
										}break;

									case ctComFunctionX:
										{
										std::string f_DefaultPacket = f_PacketLP->m_DefaultValue;

										f_PacketLP->m_vec_Package_XElement_Title.clear();
										f_PacketLP->m_vecvec_Package_Arg_Title.clear();
										f_PacketLP->m_vecvec_Package_Arg_Data.clear();

										std::string f_Packets = "";
										bool f_Some = false;
										int f_InputStage = 0;

										for(int f_CCount = 0; f_CCount < f_DefaultPacket.length(); f_CCount++)
											{
											if(f_Fail_PacketIncomplete == false)
												{
												char f_c = f_DefaultPacket.at(f_CCount);

												switch(f_InputStage)
													{
													case COM_PAKX_STAGE_TITLE:
														{
														if(f_c == '_')
															{
															f_PacketLP->m_vec_Package_XElement_Title.push_back(f_Packets);

															std::vector<std::string> f_vec_String;
															f_vec_String.clear();

															f_PacketLP->m_vecvec_Package_Arg_Title.push_back(f_vec_String);
															f_PacketLP->m_vecvec_Package_Arg_Data.push_back(f_vec_String);

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '-')
															{
															f_PacketLP->m_vecvec_Package_Arg_Title[f_PacketLP->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
															f_PacketLP->m_vecvec_Package_Arg_Data[f_PacketLP->m_vecvec_Package_Arg_Data.size() - 1].push_back(std::string("X"));

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=') //win
															{
															if(f_PacketLP->m_vec_Package_XElement_Title.size() >= 1)
																{
																if(f_PacketLP->m_vecvec_Package_Arg_Title.size() >= 1)
																	{
																	f_PacketLP->m_vecvec_Package_Arg_Title[f_PacketLP->m_vecvec_Package_Arg_Title.size() - 1].push_back(f_Packets);
																	}
																else
																	{
#ifdef ECOIN_SECURE
																	throw;
#endif
																	}
																}

															f_InputStage = COM_PAKX_STAGE_EQUAL;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}
														}break;

													case COM_PAKX_STAGE_EQUAL:
														{
														if(f_c == '_')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_InputStage = COM_PAKX_STAGE_QUOTE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}

														}break;

													case COM_PAKX_STAGE_QUOTE:
														{
														if(f_c == '=')
															{
															f_Fail_PacketIncomplete = true;
															f_CCount = f_DefaultPacket.length();
															f_InputStage = COM_PAKX_STAGE_OFF;

															f_Packets.clear();
															f_Some = false;
															}
														else if(f_c == '"') //win
															{
															f_PacketLP->m_vecvec_Package_Arg_Data[f_PacketLP->m_vecvec_Package_Arg_Data.size() - 1].push_back(f_Packets);

															f_InputStage = COM_PAKX_STAGE_TITLE;

															f_Packets.clear();
															f_Some = false;
															}
														else //record
															{
															f_Packets.push_back(f_c);

															f_Some = true;
															}
														}break;
													}
												}
											}

										if((f_InputStage != COM_PAKX_STAGE_TITLE) || (f_PacketLP->m_vec_Package_XElement_Title.size() <= 0))
											{
											f_Fail_PacketIncomplete = true;

#ifdef ECOIN_SECURE
											throw;
#endif
											}

										if(f_Fail_PacketIncomplete == false)
											{
											winrt::Windows::UI::Xaml::Media::GradientStopCollection f_GradientStopsCollection({ nullptr });

											for(int f_IDY = 0; f_IDY < f_PacketLP->m_vec_Package_XElement_Title.size(); f_IDY++)
												{
												if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("LinearGradientBrush") == 0)
													{
													//set knowns
													winrt::Windows::UI::Xaml::Media::LinearGradientBrush f_ecomLinearGradientBrush({});

													g_ecomLinearGradientBrush = f_ecomLinearGradientBrush;

													//set defaults
													//g_ecomStackPanel.Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("EndPoint") == 0)
															{
															f_ecomLinearGradientBrush.EndPoint(Point(atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][0].c_str()), atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][1].c_str())));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("StartPoint") == 0)
															{
															f_ecomLinearGradientBrush.StartPoint(Point(atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][0].c_str()), atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][1].c_str())));
															}
														}

													//receiver
													if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("TextBlock") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Foreground") == 0)
															{
															g_TextBlock.Foreground(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_TextBlock.FocusVisualPrimaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_TextBlock.FocusVisualSecondaryBrush(f_ecomLinearGradientBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("TextBox") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Foreground") == 0)
															{
															g_TextBox.Foreground(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_TextBox.FocusVisualPrimaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_TextBox.FocusVisualSecondaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_TextBox.Background(f_ecomLinearGradientBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("Button") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Foreground") == 0)
															{
															g_ecomButton.Foreground(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_ecomButton.FocusVisualPrimaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_ecomButton.FocusVisualSecondaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_ecomButton.Background(f_ecomLinearGradientBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_ecomGrid.FocusVisualPrimaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_ecomGrid.FocusVisualSecondaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_ecomGrid.Background(f_ecomLinearGradientBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("StackPanel") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_ecomStackPanel.FocusVisualPrimaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_ecomStackPanel.FocusVisualSecondaryBrush(f_ecomLinearGradientBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_ecomStackPanel.Background(f_ecomLinearGradientBrush);
															}
														}
													}
												else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("GradientStop") == 0)
													{
													//set knowns
													winrt::Windows::UI::Xaml::Media::GradientStop f_ecomGradientStop({});

													g_ecomGradientStop = f_ecomGradientStop;

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Color") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Color myColor({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_ecomGradientStop.Color(myColor);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Offset") == 0)
															{
															float f_OffSetFLT = atof(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][0].c_str());

															f_ecomGradientStop.Offset(f_OffSetFLT);
															}

														f_GradientStopsCollection.Append(f_ecomGradientStop);
														}

													g_ecomLinearGradientBrush.GradientStops(f_GradientStopsCollection);
													}
												else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("ImageBrush") == 0)
													{
													winrt::Windows::UI::Xaml::Media::ImageBrush f_ecomImageBrush({});

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("ImageSource") == 0)
															{
															std::string f_FilePath = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															winrt::hstring pictureUrl = StrUsingStr(f_FilePath);

															winrt::Windows::Foundation::Uri f_Uri({ pictureUrl });

															winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage f_BitmapImage({});

															f_BitmapImage.UriSource(f_Uri);

															f_ecomImageBrush.ImageSource(f_BitmapImage);
															}
														}

													//receiver
													if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("TextBlock") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Foreground") == 0)
															{
															g_TextBlock.Foreground(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_TextBlock.FocusVisualPrimaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_TextBlock.FocusVisualSecondaryBrush(f_ecomImageBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("TextBox") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Foreground") == 0)
															{
															g_TextBox.Foreground(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_TextBox.FocusVisualPrimaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_TextBox.FocusVisualSecondaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_TextBox.Background(f_ecomImageBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("Button") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Foreground") == 0)
															{
															g_ecomButton.Foreground(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_ecomButton.FocusVisualPrimaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_ecomButton.FocusVisualSecondaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_ecomButton.Background(f_ecomImageBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_ecomGrid.FocusVisualPrimaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_ecomGrid.FocusVisualSecondaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_ecomGrid.Background(f_ecomImageBrush);
															}
														}
													else if(f_Packet->m_vec_Package_XElement_Title[f_IDY].compare("StackPanel") == 0)
														{
														if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualPrimaryBrush") == 0)
															{
															g_ecomStackPanel.FocusVisualPrimaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("FocusVisualSecondaryBrush") == 0)
															{
															g_ecomStackPanel.FocusVisualSecondaryBrush(f_ecomImageBrush);
															}
														else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Background") == 0)
															{
															g_ecomStackPanel.Background(f_ecomImageBrush);
															}
														}

													g_ecomLinearGradientBrush.GradientStops(f_GradientStopsCollection);
													}
												else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Button") == 0)
													{
													//set knowns
													Windows::UI::Xaml::Controls::Button f_new_ecomButton({});

													f_new_ecomButton.Name(StrUsingStr(f_PacketLP->m_Name));

													//set defaults
													Windows::UI::Xaml::Media::FontFamily myFont({ L"Audiowide" });

													f_new_ecomButton.FontFamily(myFont);

													f_new_ecomButton.Click({ this, &SecondaryAppWindowPageDX::OnClickComFunction });

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Content") == 0)
															{
															f_new_ecomButton.Content(box_value(StrUsingStr(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet])));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Foreground") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.Foreground(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Background") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.Background(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("BorderBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.BorderBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FontFamily") == 0)
															{
															Windows::UI::Xaml::Media::FontFamily myFontB(StrUsingStr(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet]));

															f_new_ecomButton.FontFamily(myFontB);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Height") == 0)
															{
															f_new_ecomButton.Height(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Width") == 0)
															{
															f_new_ecomButton.Width(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("VerticalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Top") == 0)
																{
																f_new_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Bottom") == 0)
																{
																f_new_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_new_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_new_ecomButton.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("HorizontalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Left") == 0)
																{
																f_new_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Right") == 0)
																{
																f_new_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_new_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_new_ecomButton.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });
															
															g_ecomButton.Margin(myThickness);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRow(g_ecomButton, f_Data);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumn(g_ecomButton, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(g_ecomButton, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(g_ecomButton, f_Data);
															}
														}

													if(f_PacketLP->m_ClassType)
														{
														g_ecomStackPanel.Children().Append(g_ecomButton);
														}
													else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(g_ecomButton);
														}
													}
												else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("StackPanel") == 0)
													{
													//set knowns
													winrt::Windows::UI::Xaml::Controls::StackPanel f_Stack;
													f_Stack.Name(StrUsingStr(f_PacketLP->m_Name));

													//set defaults
													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Background") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.Background(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("BorderBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.BorderBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Height") == 0)
															{
															f_Stack.Height(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Width") == 0)
															{
															f_Stack.Width(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("VerticalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Top") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Bottom") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_Stack.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("HorizontalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Left") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Right") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_Stack.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_Stack.Margin(myThickness);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRow(f_Stack, f_Data);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_Stack, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_Stack, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_Stack, f_Data);
															}
														}

													if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_Stack);
														}
													else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_Stack);
														}

													g_ecomStackPanel = f_Stack;
													}
												else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
													{
													//set knowns
													winrt::Windows::UI::Xaml::Controls::Grid f_Grid({});

													f_Grid.Name(StrUsingStr(f_PacketLP->m_Name));

													Windows::UI::Xaml::Controls::ColumnDefinition myCollumn({});
													Windows::UI::Xaml::Controls::RowDefinition myRow({});

													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.ColumnDefinitions().Append(myCollumn);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);
													f_Grid.RowDefinitions().Append(myRow);

													//set defaults
													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Background") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.Background(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("BorderBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.BorderBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Height") == 0)
															{
															f_Grid.Height(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Width") == 0)
															{
															f_Grid.Width(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("VerticalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Top") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Bottom") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_Grid.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("HorizontalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Left") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Right") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_Grid.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();

															std::string f_Packetss = "";
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_Grid.Margin(myThickness);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRow(f_Grid, f_Data);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_Grid, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_Grid, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_Grid, f_Data);
															}
														}

													if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_Grid);
														}
													else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_Grid);
														}

													g_ecomGrid = f_Grid;
													}
												else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("TextBlock") == 0)
													{
													winrt::Windows::UI::Xaml::Controls::TextBlock f_TextBlock({});

													//set knowns
													f_TextBlock.Name(StrUsingStr(f_PacketLP->m_Name));

													//set defaults
													Windows::UI::Xaml::Media::FontFamily myFont(L"Audiowide");

													f_TextBlock.FontFamily(myFont);

													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Text") == 0)
															{
															f_TextBlock.Text(StrUsingStr(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet]));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Foreground") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.Foreground(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("SelectionHighlightColor") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.SelectionHighlightColor(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FontFamily") == 0)
															{
															Windows::UI::Xaml::Media::FontFamily myFontB({ StrUsingStr(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet]) });

															f_TextBlock.FontFamily(myFontB);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Height") == 0)
															{
															f_TextBlock.Height(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Width") == 0)
															{
															f_TextBlock.Width(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("VerticalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Top") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Bottom") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_TextBlock.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("HorizontalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Left") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Right") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_TextBlock.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_TextBlock.Margin(myThickness);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRow(f_TextBlock, f_Data);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_TextBlock, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_TextBlock, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_TextBlock, f_Data);
															}
														}

													if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_TextBlock);
														}
													else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_TextBlock);
														}
													}
												else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("TextBox") == 0)
													{
													winrt::Windows::UI::Xaml::Controls::TextBox f_TextBox({});

													//set knowns
													f_TextBox.Name(StrUsingStr(f_PacketLP->m_Name));

													//set defaults
													Windows::UI::Xaml::Media::FontFamily myFont(L"Audiowide");

													f_TextBox.FontFamily(myFont);

													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageDX::OnClickComFunction);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Text") == 0)
															{
															f_TextBox.Text(StrUsingStr(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet]));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Foreground") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.Foreground(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("SelectionHighlightColor") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.SelectionHighlightColor(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.FocusVisualSecondaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FontFamily") == 0)
															{
															Windows::UI::Xaml::Media::FontFamily myFontB({ StrUsingStr(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet]) });

															f_TextBox.FontFamily(myFontB);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Height") == 0)
															{
															f_TextBox.Height(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Width") == 0)
															{
															f_TextBox.Width(atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str()));
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("VerticalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Top") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Bottom") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Bottom);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_TextBox.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("HorizontalAlignment") == 0)
															{
															if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Left") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Right") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Stretch") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
																}
															else if(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].compare("Center") == 0)
																{
																f_TextBox.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
																}
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Margin") == 0)
															{
															std::string f_DataPacket = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];

															std::string f_vec_Pack_A1;
															std::string f_vec_Pack_A2;
															std::string f_vec_Pack_A3;
															std::string f_vec_Pack_A4;

															f_vec_Pack_A1.clear();
															f_vec_Pack_A2.clear();
															f_vec_Pack_A3.clear();
															f_vec_Pack_A4.clear();
															
															int f_InputStages = 0;

															for(int f_CCount = 0; f_CCount < f_DataPacket.length(); f_CCount++)
																{
																if(f_Fail_PacketIncomplete == false)
																	{
																	char f_c = f_DataPacket.at(f_CCount);

																	if(f_c == ',')
																		{
																		f_InputStages++;
																		}
																	else
																		{
																		switch(f_InputStages)
																			{
																			case 0:
																				{
																				f_vec_Pack_A1.push_back(f_c);
																				}break;

																			case 1:
																				{
																				f_vec_Pack_A2.push_back(f_c);
																				}break;

																			case 2:
																				{
																				f_vec_Pack_A3.push_back(f_c);
																				}break;

																			case 3:
																				{
																				f_vec_Pack_A4.push_back(f_c);
																				}break;
																			}
																		}
																	}
																}

															Thickness myThickness({ atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()), atodi(f_vec_Pack_A1.c_str()) });

															f_TextBox.Margin(myThickness);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Row") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRow(f_TextBox, f_Data);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.Column") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumn(f_TextBox, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.RowSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetRowSpan(f_TextBox, f_Data);
															}
														else if (f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Grid.ColumnSpan") == 0)
															{
															int f_Data = atoi(f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet].c_str());

															g_ecomGrid.SetColumnSpan(f_TextBox, f_Data);
															}
														}

													if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("StackPanel") == 0)
														{
														g_ecomStackPanel.Children().Append(f_TextBox);
														}
													else if(f_PacketLP->m_vec_Package_XElement_Title[f_IDY].compare("Grid") == 0)
														{
														g_ecomGrid.Children().Append(f_TextBox);
														}
													}
												}
											}
										}break;

									case ctEClass:
										{
										}break;

									case ctShare:
										{
										}break;

									case ctElement:
										{
										}break;

									default:
										{
										//g_ExcomPexMain->acExecute(EXCOM_MAIN_COMPLETE_IDX, 0, f_PacketLP->m_ClassType);
										}break;
									}
								}

							if(f_Fail_PacketIncomplete == false)
								{
								f_PacketLP->m_Activate_Status = COM_PAK_ACTIVATED;
								}
							}
						}break;

					case COM_PAK_TYPE_DELETE:
						{
						//not yet implemented
						}break;
					}

				if(f_Fail_PacketIncomplete == false)
					{
					f_Packet->m_Activate_Status = COM_PAK_ACTIVATED;
					}
				}
			}
	}

	void SecondaryAppWindowPageDX::OnClickSaveComplete(IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::OnClickSaveComplete";

		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		//switch off qcom panel
		g_QcomManager->m_Open = false;

		int f_ComID = ::g_QcomManager->m_Qcom->m_ID;
		float f_Cost = ::g_QcomManager->m_Qcom->m_Cost;

		std::shared_ptr<Qcom> f_Save_com = nullptr;

		//if one com selected save only this one as main shall insert
		if(g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size() == 1)
			{
			f_Save_com = g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com[0];

			f_ComID = f_Save_com->m_ID;

			if(f_Save_com->m_Cost > 0.0f)
				{
				f_Cost = f_Save_com->m_Cost;
				}
			}

#ifdef ECOIN_PREVIOUS_METHOD
		ag_StatusLive(f_ref_CurrentPath, "f_classTarget_Ecom");
		std::shared_ptr<classTarget_Ecom> f_classTarget_Ecom = std::make_shared_reflect<classTarget_Ecom>();

		ag_StatusLive(f_ref_CurrentPath, "g_classLMap");
		g_classLMap = std::make_shared_reflect<classLMap>(m_IDX);

		g_ElementDivisor.push_back(0);
		g_ElementDivisorInt.push_back(0);

		ag_StatusLive(f_ref_CurrentPath, "g_classLMap->m_SchemaRef");
		g_classLMap->m_SchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
		ag_StatusLive(f_ref_CurrentPath, "g_classLMap->m_SaveSchemaRef");
		g_classLMap->m_SaveSchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
		ag_StatusLive(f_ref_CurrentPath, "g_classLMap->m_SaveSchemaRef");
		g_classLMap->m_PushSchemaRef.push_back(std::make_shared<BiVector>(float(3.121113539F), float(3.773584266F), float(3.952468634F)));
		g_classLMap->m_SchemaMeasureIndex.push_back(0);
		g_classLMap->m_PushMeasureIndex.push_back(0);
		g_classLMap->m_CPS_Result.push_back(CPS_SCAN);

		std::shared_ptr<Qcom> f_com = g_classLMap->acGen_com_FromEcom(f_Save_com, 0, g_BicycleContainer[0]->m_ADMAX, g_BicycleContainer[0]->m_ADMAX, 1, f_classTarget_Ecom);

		g_classLMap->acRangeAD();

#if 0
		for(int f_Jet = 0; f_Jet < f_com->m_vec_Qcom.size(); f_Jet++)
			{
			std::shared_ptr<Qcom> f_Component = f_com->m_vec_Qcom[f_Jet];

			for(int f_XYZ = 0; f_XYZ < f_Component->m_vec_ESLFunction.size(); f_XYZ++)
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = f_Component->m_vec_ESLFunction[f_XYZ];

				f_Function->acCompile();
				}
			}
#endif

		g_classLMap->m_SchemaRef.pop_back();
		g_classLMap->m_SaveSchemaRef.pop_back();
		g_classLMap->m_PushSchemaRef.pop_back();
		g_classLMap->m_SchemaMeasureIndex.pop_back();
		g_classLMap->m_PushMeasureIndex.pop_back();
		g_classLMap->m_CPS_Result.pop_back();

		g_ElementDivisor.pop_back();
		g_ElementDivisorInt.pop_back();
#endif

#if 0
		::g_QcomManager->m_Qcom = f_com;
#endif

		Compressor(f_Save_com);

		lookatButton().Content(box_value(StrUsingStr("CLICK\n4 viewing")));

		char* f_Char = ag_ClearChar(32);

		sprintf(f_Char, "%i\n", ECOIN_SHARE_PROTOCOL_LENGTH);

		std::string f_CharString = "Save Complete Publish...Ready, Enter Name, Description Limit total characters " + std::string(f_Char);

		eslcoderesulttextBlock().Text(StrUsingStr(f_CharString));
		eslcodeprefixtextBox().Text(StrUsingStr("FRECOM"));

		eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
		computeoutputlowtontextBox().Visibility(Windows::UI::Xaml::Visibility::Visible);
		computeoutputtextBox().Visibility(Windows::UI::Xaml::Visibility::Visible);

		SavecompleteStackPanel().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	}

  //////////////////////////////////
 // qtx
//
bool SecondaryAppWindowPageDX::qtx_Send(std::string f_A, std::string f_B, float f_Amt)
{
	transactionA().Text(StrUsingStr(f_A));

	transactionB().Text(StrUsingStr(f_B));

	float f_amt = f_Amt;

	char* f_char = new char[250];
	sprintf(f_char, "%f", f_amt);

	transactionamt().Text(StrUsingStr(std::string(f_char)));

	delete[] f_char;

	std::shared_ptr<CubeTransaction> f_SendTX = nullptr;

	int f_Flag = Cag->ag_GenerateTransaction(f_A, f_B, f_amt, f_SendTX);

	bool f_Success = false;

	switch(f_Flag)
		{
		case 0:
			{
			Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 255, 100, 100) });

			txnerrortextBlock().Foreground(myBrush);
			txnerrortextBlock().Text(L"Transaction Failed - unknown error code");
			}break;

		case 1:
			{
			Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 100, 255, 100) });

			txnerrortextBlock().Foreground(myBrush);
			txnerrortextBlock().Text(L"Transaction SUCCESS");
			transactionA().Text(L"");
			transactionB().Text(L"");
			transactionamt().Text(L"0.0");
			f_Success = true;
			g_vec_Successfull_TX.push_back(f_SendTX);
			}break;

		case 2:
			{
			Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 255, 100, 100) });

			txnerrortextBlock().Foreground(myBrush);
			txnerrortextBlock().Text(L"Transaction Failed - Permission to access coins denied");
			transactionA().Text(L"");
			transactionB().Text(L"");
			transactionamt().Text(L"0.0");
			}break;

		case 3:
			{
			Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 255, 100, 100) });

			txnerrortextBlock().Foreground(myBrush);
			txnerrortextBlock().Text(L"Transaction Failed : Not enough ecoin in sending address");
			transactionA().Text(L"");
			transactionB().Text(L"");
			transactionamt().Text(L"0.0");
			}break;
		}

	return f_Success;
}

void SecondaryAppWindowPageDX::clearTXDisplay(void)
{
	std::string f_Null = "";

	txdisplay1txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay1txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay1txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay2txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay2txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay2txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay3txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay3txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay3txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay4txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay4txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay4txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay5txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay5txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay5txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay6txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay6txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay6txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay7txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay7txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay7txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay8txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay8txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay8txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay9txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay9txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay9txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay10txidtextBlock().Text(StrUsingStr(f_Null));
	txdisplay10txstatustextBlock().Text(StrUsingStr(f_Null));
	txdisplay10txconfirmationstextBlock().Text(StrUsingStr(f_Null));
	txdisplay1txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay2txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay3txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay4txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay5txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay6txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay7txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay8txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay9txamounttextBlock().Text(StrUsingStr(f_Null));
	txdisplay10txamounttextBlock().Text(StrUsingStr(f_Null));
}

void SecondaryAppWindowPageDX::StartTXD(void)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::StartTXD";

	if(!txd_on)
		{
		txd_on = true;

		g_TXD_Scan = true;

#if 0
		qtx_Update();
#endif
		}
	else
		{
		txd_on = false;

		g_TXD_Scan = false;
		}
}

void SecondaryAppWindowPageDX::qtx_Update(void)
{
	char* txquery = ag_ClearChar(3000);
	sprintf(txquery, "SELECT id, status, confirmation, amt, dated FROM transactions WHERE owner = '%s' ORDER BY dated DESC LIMIT 9", g_Wallet->GetAdr().c_str());
	g_SafeL[0]->acSelectCommand(txquery, false, false);
	delete txquery;

	int f_TxLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_TxLCount = 0;
		}
	else
		{
		f_TxLCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat::: f_TxLCount

	g_vec_qtx_TransactionNew.clear();

	if(f_TxLCount > 0)
		{
#if 0
		for(int f_XY = 0; f_XY < f_TxLCount; f_XY++)
			{
			qtx_Transaction* f_qtx_tx = new qtx_Transaction(f_XY);

			g_vec_qtx_TransactionNew.push_back(f_qtx_tx);
			}
#endif

		int f_Index = 0;

		txdisplay1txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
		txdisplay1txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
		txdisplay1txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
		txdisplay1txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));

		if(f_TxLCount > 1)
			{
			f_Index = 1;

			txdisplay2txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay2txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay2txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay2txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 2)
			{
			f_Index = 2;

			txdisplay3txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay3txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay3txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay3txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 3)
			{
			f_Index = 3;

			txdisplay4txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay4txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay4txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay4txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 4)
			{
			f_Index = 4;

			txdisplay5txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay5txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay5txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay5txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 5)
			{
			f_Index = 5;

			txdisplay6txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay6txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay6txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay6txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 6)
			{
			f_Index = 6;

			txdisplay7txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay7txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay7txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay7txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 7)
			{
			f_Index = 7;

			txdisplay8txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay8txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay8txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay8txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 8)
			{
			f_Index = 8;

			txdisplay9txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay9txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay9txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay9txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

		if(f_TxLCount > 9)
			{
			f_Index = 9;

			txdisplay10txidtextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[0]));
			txdisplay10txstatustextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[1]));
			txdisplay10txconfirmationstextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[2]));
			txdisplay10txamounttextBlock().Text(StrUsingStr(g_Schedular[0]->acEntry(f_Index)[3]));
			}

#if 0
		bool f_bool = qtx_Results();
#endif

		//QTX::Results f_bool
		}
}

bool SecondaryAppWindowPageDX::qtx_Results(void)
{
	if(g_vec_qtx_Transaction.size() <= 0)
		{
		if(g_vec_qtx_TransactionNew.size() <= 0)
			{
			return false;
			}
		else
			{ //first run and full,. push away
			for(int f_Helly = 0; f_Helly < g_vec_qtx_TransactionNew.size(); f_Helly++)
				{
				g_vec_qtx_Transaction.push_back(g_vec_qtx_TransactionNew[f_Helly]);
				}

			return false;
			}
		}
	else
		{
		//Legacy Rack Update
		for(int f_Helly = 0; f_Helly < g_vec_qtx_Transaction.size(); f_Helly++)
			{
			qtx_Transaction* f_LegacyTX = g_vec_qtx_Transaction[f_Helly];
			qtx_Transaction* f_NewTX = nullptr;

			//Find new copy
			bool f_Found = false;
			int f_Index = 0;
			for(int f_Aero = 0; f_Aero < g_vec_qtx_TransactionNew.size(); f_Aero++)
				{
				if(g_vec_qtx_TransactionNew[f_Aero]->m_txid == f_LegacyTX->m_txid)
					{
					f_Index = f_Aero;
					f_Found = true;
					f_Aero = g_vec_qtx_TransactionNew.size();
					f_NewTX = g_vec_qtx_TransactionNew[f_Aero];
					}
				}

			if(f_Found)
				{//Legacy TX found New Version
				if(f_NewTX->m_status == -5)
					{
					//Qpo->Sound_Load_Play(&Medias->S_Click, "QpoSound", "txfail.wav", 0.6f);
					}
				else if(f_NewTX->m_confirmation >= 6)
					{
					//Qpo->Sound_Load_Play(&Medias->S_Click, "QpoSound", "txsuccess.wav", 0.6f);

					successStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

					char* f_char = new char[250];
					sprintf(f_char, "%f", f_NewTX->m_amt);

					successecoinchangestextBlock().Text(StrUsingStr(f_char));

					delete[] f_char;
					}
				}
			}
		}

	return true;
}
#endif

void SecondaryAppWindowPageDX::OnClickFloatTXD(winrt::Windows::Foundation::IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_TXD_Position++;
	if(g_TXD_Position >= 4)
		{
		g_TXD_Position = 0;
		}

	if(g_TXD_Position == 0)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Left);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Top);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 386, 593, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		}
	else if(g_TXD_Position == 1)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Right);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Top);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 0, 90, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
	else if(g_TXD_Position == 2)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Right);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Bottom);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 0, 0, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
	else if (g_TXD_Position == 3)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Left);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Bottom);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 0, 0, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageDX::OnClickSuccessClose(winrt::Windows::Foundation::IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	successStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
}

	/////////////////////
   // Open and receive
  // qtx
 // pass on owner
//
void SecondaryAppWindowPageDX::OpenTXD(std::string f_Recipient, float f_Amt)
{
	std::string f_A = g_Wallet->GetAdr();

	transactionA().Text(StrUsingStr(f_A));

	std::string f_B = f_Recipient;

	transactionB().Text(StrUsingStr(f_B));

	float f_amt = f_Amt;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", f_amt);

	transactionamt().Text(StrUsingStr(std::string(f_char)));

	delete f_char;

	Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(255, 255, 100, 100) });

	txnerrortextBlock().Foreground(myBrush);
	txnerrortextBlock().Text(L"Transaction Prepared... Fulfillment Ready... Press Send");

	StartTXD();
}

void SecondaryAppWindowPageDX::CloseTXD(void)
{
	g_TXD_Scan = false;
}

void SecondaryAppWindowPageDX::OnClickCloseTXD(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	transactionStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	transactionExplorerStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);

	txnerrortextBlock().Text(L"Transaction Failed Closed TXD... Enter Again Please");
	transactionA().Text(L"");
	transactionB().Text(L"");
	transactionamt().Text(L"0.0");

	CloseTXD();
}

void SecondaryAppWindowPageDX::OnClickTXDpreview(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_TXD_Preview = true;
}

void SecondaryAppWindowPageDX::acTXReal(void)
{
	//g_TXD_Scan = true

	float f_TX_Amount = atof(to_string(transactionamt().Text()).c_str());

	float f_TX_Result = f_TX_Amount * 1.01f;

}

void SecondaryAppWindowPageDX::OnClickOpenWalletPrint(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
		{
		ecoinwalletStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

		acRefreshWalletPrint();
		});
}

void SecondaryAppWindowPageDX::OnClickRefreshWalletPrint(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	acRefreshWalletPrint();
}

void SecondaryAppWindowPageDX::acRefreshWalletPrint(void)
{
	std::string f_String = "";
	f_String.clear();
	f_String += "ecoinWallet v2.0 Print Address Stats.\n\n";

	float f_TotalWalletAmount = 0.0;

	for(int f_Helly = 0; f_Helly < g_Wallet->m_vec_Key.size(); f_Helly++)
		{
		std::shared_ptr<CKey> f_Key = g_Wallet->m_vec_Key[f_Helly];

		char txquery[1000];

		::sprintf(txquery, "SELECT amt FROM address WHERE owner = '%s'", f_Key->m_owner.c_str());

		g_SafeL[0]->acSelectCommand(txquery, false, false);

		int f_ADRCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_ADRCount = 0;
			}
		else
			{
			f_ADRCount = g_Schedular[0]->acEntrySize();
			}

		//ECN:Stat::ADRCount f_ADRCount
		if(f_ADRCount == 0)
			{
			char* f_char = ag_ClearChar(512);

			::sprintf(f_char, "UNK(%i): ", f_Key->m_prefix);

			f_String += f_char;

			delete f_char;

			f_String += f_Key->m_owner + " ";
			f_String += "0.00000000 ECN\n";
			}
		else
			{
			char* f_char = ag_ClearChar(512);

			::sprintf(f_char, "%i: ", f_Key->m_prefix);

			f_String += f_char;

			delete f_char;

			f_String += f_Key->m_owner + " ";
			f_String += g_Schedular[0]->acEntry(0)[0] + " ECN\n";

			f_TotalWalletAmount += atof(g_Schedular[0]->acEntry(0)[0].c_str());
			}
		}

	char* f_charf = ag_ClearChar(512);

	sprintf(f_charf, "\n    Wallet Total Balance %f ECN\n", f_TotalWalletAmount);

	f_String += f_charf;

	delete f_charf;

	ecoinwallettextBox().Text(StrUsingStr(f_String));
}

void SecondaryAppWindowPageDX::OnClickCloseWalletPrint(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	ecoinwalletStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::OnClickCloseSaveComplete(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	lookatButton().Content(box_value(L"CLICK\n4 shares"));

	eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	currentStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::OnClickOpenTXD(IInspectable sender, Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	transactionStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
	transactionExplorerStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

	if(g_PreCom != nullptr)
		{
		OpenTXD(g_PreCom->m_owner, g_PreCom->m_Cost);
		}
	else
		{
		OpenTXD("", 1.0f);
		}
}

void SecondaryAppWindowPageDX::OnValueChangedSaveCompletePublishSlider(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
	std::string f_SliderName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Slider>().Name());

	acClick(f_SliderName);

	int f_IntValue = e.NewValue();

	g_SaveComplete_ThreadCount = f_IntValue;

	char* f_Char = ag_ClearChar(255);

	sprintf(f_Char, "%i", f_IntValue);

	std::string f_AmtValueStr = f_Char;

	delete f_Char;

	if(m_FirstAll == false)
		{
		SavecompleteresulttextBlock().Text(StrUsingStr(f_AmtValueStr));
		}
}

void SecondaryAppWindowPageDX::OnClickSelectStack(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(selectdecisionsStack().Visibility() == Windows::UI::Xaml::Visibility::Collapsed)
		{
		selectdecisionsStack().Visibility(Windows::UI::Xaml::Visibility::Visible);
		}
	else if(selectdecisionsStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
		{
		selectdecisionsStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageDX::OnClickSelectSelect(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	if(f_WHL->m_LayerPos == 0)
		{
		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_HighLighted_com.size(); f_Jet++)
			{
			std::shared_ptr<Qcom> f_com = f_WHL->m_vec_HighLighted_com[f_Jet];

			if(f_com->m_Selected == true)
				{
				f_com->acSelect(false);

				for(int f_L = 0; f_L < f_WHL->m_vec_HighLighted_com.size(); f_L++)
					{
					if(f_com->m_ID == f_WHL->m_vec_HighLighted_com[f_L]->m_ID)
						{
						for(int f_Helly = f_L; f_Helly < f_WHL->m_vec_HighLighted_com.size() - 1; f_Helly++)
							{
							f_WHL->m_vec_HighLighted_com[f_Helly] = f_WHL->m_vec_HighLighted_com[f_Helly + 1];
							}

						f_WHL->m_vec_HighLighted_com.pop_back();
						}
					}
				}
			else
				{
				f_com->acSelect(true);

				f_WHL->m_vec_Selection_com.push_back(f_com);
				}
			}
		}

	for(int f_Jet = 0; f_Jet < f_WHL->m_vec_HighLighted_input.size(); f_Jet++)
		{
		std::shared_ptr<QcomInput> f_input = f_WHL->m_vec_HighLighted_input[f_Jet];

		if(f_input->m_Selected == true)
			{
			f_input->acSelect(false);

			for(int f_L = 0; f_L < f_WHL->m_vec_HighLighted_input.size(); f_L++)
				{
				if(f_input->m_ID == f_WHL->m_vec_HighLighted_input[f_L]->m_ID)
					{
					for(int f_Helly = f_L; f_Helly < f_WHL->m_vec_HighLighted_input.size() - 1; f_Helly++)
						{
						f_WHL->m_vec_HighLighted_input[f_Helly] = f_WHL->m_vec_HighLighted_input[f_Helly + 1];
						}

					f_WHL->m_vec_HighLighted_input.pop_back();
					}
				}
			}
		else
			{
			f_input->acSelect(true);

			f_WHL->m_vec_Selection_input.push_back(f_input);
			}
		}

	for(int f_Jet = 0; f_Jet < f_WHL->m_vec_HighLighted_output.size(); f_Jet++)
		{
		std::shared_ptr<QcomOutput> f_output = f_WHL->m_vec_HighLighted_output[f_Jet];

		if(f_output->m_Selected == true)
			{
			f_output->acSelect(false);

			for(int f_L = 0; f_L < f_WHL->m_vec_HighLighted_output.size(); f_L++)
				{
				if(f_output->m_ID == f_WHL->m_vec_HighLighted_output[f_L]->m_ID)
					{
					for(int f_Helly = f_L; f_Helly < f_WHL->m_vec_HighLighted_output.size() - 1; f_Helly++)
						{
						f_WHL->m_vec_HighLighted_output[f_Helly] = f_WHL->m_vec_HighLighted_output[f_Helly + 1];
						}

					f_WHL->m_vec_HighLighted_output.pop_back();
					}
				}
			}
		else
			{
			f_output->acSelect(true);

			f_WHL->m_vec_Selection_output.push_back(f_output);
			}
		}

	for(int f_Jet = 0; f_Jet < f_WHL->m_vec_HighLighted_wire.size(); f_Jet++)
		{
		std::shared_ptr<QcomWire> f_wire = f_WHL->m_vec_HighLighted_wire[f_Jet];

		if(f_wire->m_Selected == true)
			{
			f_wire->acSelect(false);

			for(int f_L = 0; f_L < f_WHL->m_vec_HighLighted_wire.size(); f_L++)
				{
				if(f_wire->m_ID == f_WHL->m_vec_HighLighted_wire[f_L]->m_ID)
					{
					for(int f_Helly = f_L; f_Helly < f_WHL->m_vec_HighLighted_wire.size() - 1; f_Helly++)
						{
						f_WHL->m_vec_HighLighted_wire[f_Helly] = f_WHL->m_vec_HighLighted_wire[f_Helly + 1];
						}

					f_WHL->m_vec_HighLighted_wire.pop_back();
					}
				}
			}
		else
			{
			f_wire->acSelect(true);

			f_WHL->m_vec_Selection_wire.push_back(f_wire);
			}
		}

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickAction(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageDX::acRefreshDecisionsPanel(void)
{
	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	g_vec_DecisionsManager[0]->acClear();
	g_vec_DecisionsManager[0]->acLoad_ApplicationSpecificLegacy();

	for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_vec_DecisionCom.size(); f_XY++)
		{
		std::shared_ptr<BiDecisionQ> f_DecisionQ = g_vec_DecisionsManager[0]->m_vec_DecisionCom[f_XY]->acGen_DecisionQ_fromDecisionCom();

		if(f_DecisionQ->acCheck_Show() == true)
			{
			g_vec_DecisionsManager[0]->m_vec_DecisionQ.push_back(f_DecisionQ);
			}
		}

	if((f_WHL->m_SelectionIndex < g_vec_DecisionsManager[0]->m_vec_DecisionQ.size()) && (f_WHL->m_DecisionIndex < g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA.size()))
		{
		if(g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA[f_WHL->m_DecisionIndex]->m_Applied == false)
			{
			decisionsButton().Content(box_value(StrUsingStr("Apply")));
			}
		else
			{
			decisionsButton().Content(box_value(StrUsingStr("UnApply")));
			}

		char* f_charf = ag_ClearChar(1024);

		sprintf(f_charf, "Q-%i-%i A-%i-%i ", (int)g_vec_DecisionsManager[0]->m_Wheel->m_SelectionIndex, (int)g_vec_DecisionsManager[0]->m_vec_DecisionQ.size(), (int)g_vec_DecisionsManager[0]->m_Wheel->m_DecisionIndex, (int)g_vec_DecisionsManager[0]->m_vec_DecisionQ[g_vec_DecisionsManager[0]->m_Wheel->m_SelectionIndex]->m_vec_DecisionA.size());

		std::string f_string = f_charf;

		f_string += g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA[f_WHL->m_DecisionIndex]->m_TitleText;

		delete f_charf;

		decisionsTitle().Text(StrUsingStr(f_string));
		decisionB1textBox().Text(StrUsingStr(g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA[f_WHL->m_DecisionIndex]->m_ObjectNameOverride));
		}
}

void SecondaryAppWindowPageDX::acRefreshSelectionInfo(void)
{
	char* f_Char = ag_ClearChar(256);

	sprintf(f_Char, "%i Com Selected\n%i Inputs Selected\n%i Outputs Selected\n%i Wires Selected", (int)g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size(), (int)g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_input.size(), (int)g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_output.size(), (int)g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_wire.size());

	selectcomtextBlock().Text(StrUsingStr(std::string(f_Char)));

	delete f_Char;

	acRefreshDecisionsPanel();

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	if(f_WHL->m_vec_Selection_com.size() == 1)
		{
		if(f_WHL->m_vec_Selection_input.size() == 0)
			{
			if(f_WHL->m_Selection_base == nullptr)
				{
				f_WHL->m_Selection_base = f_WHL->m_vec_Selection_com[0];

				appWindowPredatorTextBox.Text(g_vec_PredatorManager[0]->ac_Open_Com(f_WHL->m_Selection_base));
				}
			else
				{
				if(f_WHL->m_vec_Selection_com[0]->m_ID != f_WHL->m_Selection_base->m_ID)
					{
					f_WHL->m_Selection_base = f_WHL->m_vec_Selection_com[0];

					appWindowPredatorTextBox.Text(g_vec_PredatorManager[0]->ac_Open_Com(f_WHL->m_Selection_base));
					}
				}
			}
		else
			{
			//.
			}
		}
}

void SecondaryAppWindowPageDX::OnClickSelectUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acSelectionGrow(BiVector(0.0f, 5.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickSelectRight(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acSelectionGrow(BiVector(5.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickSelectLeft(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acSelectionGrow(BiVector(-5.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickSelectDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->acSelectionGrow(BiVector(0.0f, -5.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickSelectIn(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->acPressIn();

	f_WHL->acSelectionGrow(BiVector(0.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}


void SecondaryAppWindowPageDX::OnClickSelectOut(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->acPressOut();

	f_WHL->acSelectionGrow(BiVector(0.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}


void SecondaryAppWindowPageDX::OnClickSelectMode(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}


void SecondaryAppWindowPageDX::OnClickSelectAdditive(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageDX::OnClickSelectPrevious(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	m_SelectionSaveIndex--;

	if(m_SelectionSaveIndex < 0)
		{
		m_SelectionSaveIndex = 0;
		}

	char* f_Char = ag_ClearChar(256);

	sprintf(f_Char, "%i-%i", (int)m_SelectionSaveIndex, (int)g_vec_DecisionsManager[0]->m_Wheel->m_Selection_Bank.size());

	selectindextextBlock().Text(StrUsingStr(std::string(f_Char)));

	delete f_Char;
}

void SecondaryAppWindowPageDX::OnClickSelectNext(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	m_SelectionSaveIndex++;

	if(m_SelectionSaveIndex >= g_vec_DecisionsManager[0]->m_Wheel->m_Selection_Bank.size())
		{
		if(g_vec_DecisionsManager[0]->m_Wheel->m_Selection_Bank.size() > 0)
			{
			m_SelectionSaveIndex = g_vec_DecisionsManager[0]->m_Wheel->m_Selection_Bank.size() - 1;
			}
		else
			{
			m_SelectionSaveIndex = 0;
			}
		}

	char* f_Char = ag_ClearChar(256);

	sprintf(f_Char, "%i-%i", (int)m_SelectionSaveIndex, (int)g_vec_DecisionsManager[0]->m_Wheel->m_Selection_Bank.size());

	selectindextextBlock().Text(StrUsingStr(std::string(f_Char)));

	delete f_Char;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickSelectRecall(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->acClear();

	::g_QcomManager->acSelectNone();

	std::shared_ptr<SelectionSave> f_Save = f_WHL->m_Selection_Bank[m_SelectionSaveIndex];

	for(int f_XYZ = 0; f_XYZ < f_Save->m_vec_Selection_com.size(); f_XYZ++)
		{
		std::shared_ptr<Qcom> f_com = f_Save->m_vec_Selection_com[f_XYZ];

		f_com->m_Selected = true;

		f_WHL->m_vec_Selection_com.push_back(f_com);
		}

	for(int f_XYZ = 0; f_XYZ < f_Save->m_vec_Selection_input.size(); f_XYZ++)
		{
		std::shared_ptr<QcomInput> f_com = f_Save->m_vec_Selection_input[f_XYZ];

		f_com->m_Selected = true;

		f_WHL->m_vec_Selection_input.push_back(f_com);
		}

	for(int f_XYZ = 0; f_XYZ < f_Save->m_vec_Selection_output.size(); f_XYZ++)
		{
		std::shared_ptr<QcomOutput> f_com = f_Save->m_vec_Selection_output[f_XYZ];

		f_com->m_Selected = true;

		f_WHL->m_vec_Selection_output.push_back(f_com);
		}

	for(int f_XYZ = 0; f_XYZ < f_Save->m_vec_Selection_wire.size(); f_XYZ++)
		{
		std::shared_ptr<QcomWire> f_com = f_Save->m_vec_Selection_wire[f_XYZ];

		f_com->m_Selected = true;

		f_WHL->m_vec_Selection_wire.push_back(f_com);
		}

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickDecisionsTop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acClear();

	g_vec_DecisionsManager[0]->m_Wheel->m_LayerPos = 0;
	g_vec_DecisionsManager[0]->m_Wheel->m_Layer = -1;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickdecisionsLayerZero(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acClear();

	::g_QcomManager->m_Qcom = ::g_QcomManager->mam_Qcom;

	g_vec_DecisionsManager[0]->m_Wheel->m_LayerPos = 0;
	g_vec_DecisionsManager[0]->m_Wheel->m_Layer = 0;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickdecisionsLastDecisionCom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	if(g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA.size() > 0)
		{
		f_WHL->m_DecisionIndex = g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA.size() - 1;
		}

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickPreviousDecision(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->m_DecisionIndex--;

	if(f_WHL->m_DecisionIndex < 0)
		{
		f_WHL->m_SelectionIndex--;

		if(f_WHL->m_SelectionIndex < 0)
			{
			f_WHL->m_SelectionIndex = 0;
			}

		f_WHL->m_DecisionIndex = g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA.size() - 1;
		}

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickNextDecision(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->m_DecisionIndex++;

	if(f_WHL->m_DecisionIndex >= g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA.size())
		{
		f_WHL->m_DecisionIndex = 0;

		f_WHL->m_SelectionIndex++;

		if(f_WHL->m_SelectionIndex >= g_vec_DecisionsManager[0]->m_vec_DecisionQ.size())
			{
			f_WHL->m_SelectionIndex = 0;
			}
		}

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickDecision1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->m_DecisionIndex = 0;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickDecisionCom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageDX::OnClickDecisionClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_Visible = false;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickDecisionsUndo(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<BiDecisionA> f_UndoAnswer = g_vec_DecisionsManager[0]->m_UnDo[g_vec_DecisionsManager[0]->m_UnDo.size() - 1];

	g_vec_DecisionsManager[0]->m_vec_DecisionQ[g_vec_DecisionsManager[0]->m_Wheel->m_SelectionIndex]->m_vec_DecisionA.push_back(f_UndoAnswer);
	g_vec_DecisionsManager[0]->m_Wheel->m_DecisionIndex = g_vec_DecisionsManager[0]->m_vec_DecisionQ[g_vec_DecisionsManager[0]->m_Wheel->m_SelectionIndex]->m_vec_DecisionA.size() - 1;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageDX::OnClickdecisionsApply(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	std::shared_ptr<BiDecisionA> f_Answer = g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA[f_WHL->m_DecisionIndex];

	if(f_Answer->m_Applied == false)
		{
		f_Answer->acApply();

		f_Answer->m_Applied = true;

		g_vec_DecisionsManager[0]->m_UnDo.push_back(f_Answer);
		}
	else
		{
		f_Answer->acApply();

		f_Answer->m_Applied = false;

		g_vec_DecisionsManager[0]->m_UnDo.push_back(f_Answer);
		}

	decisionsButton().Content(box_value(StrUsingStr(std::string("Cancel"))));
}

void SecondaryAppWindowPageDX::OnClickSelectSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::OnClickSelectSave";

	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

#if 0
	ag_StatusLive(f_ref_CurrentPath, "f_SelectionSave");
	std::shared_ptr<SelectionSave> f_SelectionSave = std::make_shared_reflect<SelectionSave>();
#else
	std::shared_ptr<SelectionSave> f_SelectionSave = std::make_shared<SelectionSave>();
#endif

	g_vec_DecisionsManager[0]->m_Wheel->m_Selection_Bank.push_back(f_SelectionSave);

	char* f_Char = ag_ClearChar(256);

	sprintf(f_Char, "%i-%i", (int)m_SelectionSaveIndex, (int)g_vec_DecisionsManager[0]->m_Wheel->m_Selection_Bank.size());

	selectindextextBlock().Text(StrUsingStr(std::string(f_Char)));

	delete f_Char;
}

void SecondaryAppWindowPageDX::OnSCP_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e)
{
	// When the pointer is pressed begin tracking the pointer movement.
	//m_main->StartTracking();

	if(::g_QcomManager)
		{
		if(::g_QcomManager->m_Open == true)
			{
			::g_QcomManager->m_PointerCharge = true;
			}
		}
}

void SecondaryAppWindowPageDX::OnSCP_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e)
{
	// Stop tracking pointer movement when the pointer is released.
	//m_main->StopTracking();

	if(::g_QcomManager)
		{
		if(::g_QcomManager->m_Open == true)
			{
			if(::g_QcomManager->m_PointerCharge)
				{
				::g_QcomManager->ac_FireLTClick();
				::g_QcomManager->m_PointerCharge = false;
				}

			::g_QcomManager->m_drag_on = false;
			}
		}
}

void SecondaryAppWindowPageDX::OnSCP_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e)
{
	Windows::UI::Input::PointerPoint f_PointerPoint = e.CurrentPoint();

	if(::g_QcomManager)
		{
		if(::g_QcomManager->m_Open == true)
			{
			if(::g_QcomManager->m_PointerCharge == true)
				{
				::g_QcomManager->ac_DragGrid(f_PointerPoint.Position().X, f_PointerPoint.Position().Y * -1);
				}
			}
		else
			{
			// Update the pointer tracking code.
			if(m_main->IsTracking())
				{
				m_main->TrackingUpdate(f_PointerPoint.Position().X);
				}
			}
		}

	//m_main->StartTracking();
}

void SecondaryAppWindowPageDX::OnSwap_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	// When the pointer is pressed begin tracking the pointer movement.
	//m_main->StartTracking();

	if(::g_QcomManager)
		{
		if(::g_QcomManager->m_Open == true)
			{
			::g_QcomManager->m_PointerCharge = true;
			}
		}
}

void SecondaryAppWindowPageDX::OnSwap_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	// Stop tracking pointer movement when the pointer is released.
	//m_main->StopTracking();

	if(::g_QcomManager)
		{
		if(::g_QcomManager->m_Open == true)
			{
			if(::g_QcomManager->m_PointerCharge)
				{
				::g_QcomManager->ac_FireLTClick();
				::g_QcomManager->m_PointerCharge = false;
				}

			::g_QcomManager->m_drag_on = false;
			}
		}
}

void SecondaryAppWindowPageDX::OnSwap_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	Windows::UI::Input::PointerPoint f_PointerPoint = e.GetCurrentPoint(swapChainPanel());

	if(::g_QcomManager)
		{
		if(::g_QcomManager->m_Open == true)
			{
			if(::g_QcomManager->m_PointerCharge == true)
				{
				::g_QcomManager->ac_DragGrid(f_PointerPoint.Position().X, f_PointerPoint.Position().Y * -1);
				}
			}
		else
			{
			// Update the pointer tracking code.
			if(m_main->IsTracking())
				{
				m_main->TrackingUpdate(f_PointerPoint.Position().X);
				}
			}
		}

	//m_main->StartTracking();
}

void SecondaryAppWindowPageDX::OnClickApplyNumber(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::string f_ApplyNumberString = to_string(ApplyNumbertextBox().Text());

	std::string f_ADMAX;
	std::string f_ADPTLr;
	std::vector<std::string> f_vec_AD_PROTCOL_IDX;

	f_vec_AD_PROTCOL_IDX.clear();

	int f_HeadMode = 0;

	for(int f_Jet = 0; f_Jet < f_ApplyNumberString.length(); f_Jet++)
		{
		char f_Char = f_ApplyNumberString.at(f_Jet);

		if(((f_Char >= '0') && (f_Char <= '9')))
			{
			if(f_HeadMode == 0)
				{
				f_ADMAX.push_back(f_Char);
				}
			else
				{
				f_ADPTLr.push_back(f_Char);
				}
			}
		else
			{
			f_HeadMode++;

			if(f_HeadMode > 1)
				{
				f_vec_AD_PROTCOL_IDX.push_back(f_ADPTLr);
				}
			}
		}

	int f_INTMAX = 5;

	if(f_ADMAX.length() > 0)
		{
		f_INTMAX = atoi(f_ADMAX.c_str());
		}

	if(f_INTMAX > 0)
		{
		g_BicycleContainer[0]->m_ADMAX = f_INTMAX;
		g_BicycleContainer[0]->m_ADHIGH = f_INTMAX;
		g_BicycleContainer[0]->m_ADLOW = f_INTMAX;
		}
	else
		{
		ApplyNumbertextBox().Text(L"15-");

		g_BicycleContainer[0]->m_ADMAX = 15;
		g_BicycleContainer[0]->m_ADHIGH = 15;
		g_BicycleContainer[0]->m_ADLOW = 15;
		}
}

void SecondaryAppWindowPageDX::OnClickIncreaseCompressionHigh(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if(Savecompletelmslider().Maximum() == 15)
		{
		Savecompletelmslider().Maximum(100);
		}
	else if(Savecompletelmslider().Maximum() == 100)
		{
		Savecompletelmslider().Maximum(1000);
		}
	else if(Savecompletelmslider().Maximum() == 1000)
		{
		Savecompletelmslider().Maximum(15);
		}
}

void SecondaryAppWindowPageDX::OnValueChangedSaveCompressionSlider(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
	int f_IntValue = e.NewValue();

	g_CountLM = f_IntValue;

	char* f_Char = ag_ClearChar(255);

	sprintf(f_Char, "%i", f_IntValue);

	std::string f_AmtValueStr = f_Char;

	delete f_Char;

	if(m_FirstAll == false)
		{
#if 0
		g_classLMap->acRangeAD();
#endif

		SavecompleteresultlmtextBlock().Text(StrUsingStr(f_AmtValueStr));
		}
}

void SecondaryAppWindowPageDX::OnClickPlaceVector(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(g_PreComInclude == false)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(g_ShuttleCom->m_Cost, g_ShuttleCom->m_ID);

		if(f_hasBought == true) //win 1
			{
			::g_QcomManager->m_SaveCom.push_back(g_ShuttleCom);

			g_ShuttleCom = nullptr;

			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

			insertinsertbutton().BorderBrush(myBrush);

			eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 55, 50));

			insertinsertbutton().BorderBrush(myBrush);
			}
		}
	else
		{	//win 2
		::g_QcomManager->m_SaveCom.push_back(g_ShuttleCom);

		g_ShuttleCom = nullptr;

		//reset win
		g_PreComInclude = false;
		g_PreComLock = false;
		g_PreComBool = false;
		g_PreComBoughtIN = 0;

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 200, 255, 90));

		insertinsertbutton().BorderBrush(myBrush);

		eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageDX::OnClickPlaceInNewGrid(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(g_PreComInclude == false)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(g_ShuttleCom->m_Cost, g_ShuttleCom->m_ID);

		if(f_hasBought == true) //win 1
			{
			::g_QcomManager->acClearGridNew(g_ShuttleCom);

#if 0
			::g_QcomManager->acParse_GenScript(g_ShuttleCom);

			acBuild_ExcomPackaging();

			g_ShuttleCom = nullptr;
#endif

			qcomappBar().IsOpen(true);

			::g_QcomManager->m_Open = true;

			insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

			char* f_Char = new char[255];

			sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

			insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

			delete[] f_Char;

			DisplayInterfaceCom(g_ShuttleCom);

			g_PreComBoughtIN = 1;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

			insertinsertbutton().BorderBrush(myBrush);

			//win conditions.!
			g_PreComBoughtIN = 1;

			eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 55, 50));

			insertinsertbutton().BorderBrush(myBrush);
			}
		}
	else
		{ //win 2
		::g_QcomManager->acClearGridNew(g_ShuttleCom);

#if 0
		::g_QcomManager->acParse_GenScript(g_ShuttleCom);

		acBuild_ExcomPackaging();

		g_ShuttleCom = nullptr;
#endif

		qcomappBar().IsOpen(true);

		::g_QcomManager->m_Open = true;

		insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

		char* f_Char = new char[255];

		sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

		insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

		delete[] f_Char;

		DisplayInterfaceCom(g_ShuttleCom);

		g_PreComBoughtIN = 1;

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 200, 255, 90));

		insertinsertbutton().BorderBrush(myBrush);

		//win conditions.!
		g_PreComBoughtIN = 1;

		eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageDX::OnClickExecuteNew(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(g_PreComInclude == false)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(g_ShuttleCom->m_Cost, g_ShuttleCom->m_ID);

		if(f_hasBought == true) //win 1
			{
			::g_QcomManager->acClearGridNew(g_ShuttleCom);

			::g_QcomManager->acParse_GenScript(g_ShuttleCom);

			acBuild_ExcomPackaging();

			insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

			char* f_Char = new char[255];

			sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

			insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

			delete[] f_Char;

			DisplayInterfaceCom(g_ShuttleCom);

			g_PreComBoughtIN = 1;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

			insertinsertbutton().BorderBrush(myBrush);

			::g_QcomManager->m_Qcom->m_vec_Qcom.push_back(g_ShuttleCom);

			g_ShuttleCom = nullptr;

			::g_QcomManager->m_Qcom->ac_Execute();
			}
		else
			{
			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 55, 50));

			insertinsertbutton().BorderBrush(myBrush);
			}
		}
	else
		{
		::g_QcomManager->acClearGridNew(g_ShuttleCom);

		::g_QcomManager->acParse_GenScript(g_ShuttleCom);

		acBuild_ExcomPackaging();

		insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

		char* f_Char = new char[255];

		sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

		insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

		delete[] f_Char;

		DisplayInterfaceCom(g_ShuttleCom);

		g_PreComBoughtIN = 0;

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 200, 255, 90));

		insertinsertbutton().BorderBrush(myBrush);

		g_ShuttleCom = nullptr;

		::g_QcomManager->m_Qcom->ac_Execute();
		}
}

void SecondaryAppWindowPageDX::OnClickClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

#if 0
	for(int f_XY = 0; f_XY < 3; f_XY++)
		{
		g_Schedular[f_XY]->acShutdown();
		}
#endif
}

void SecondaryAppWindowPageDX::OnClickIncreaseSCPThreadsHigh(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if(Savecompleteslider().Maximum() == 10)
		{
		Savecompleteslider().Maximum(100);
		}
	else if(Savecompleteslider().Maximum() == 100)
		{
		Savecompleteslider().Maximum(1000);
		}
	else if(Savecompleteslider().Maximum() == 1000)
		{
		Savecompleteslider().Maximum(10000);
		}
	else if(Savecompleteslider().Maximum() == 10000)
		{
		Savecompleteslider().Maximum(100000);
		}
	else if(Savecompleteslider().Maximum() == 100000)
		{
		Savecompleteslider().Maximum(1000000);
		}
	else if(Savecompleteslider().Maximum() == 1000000)
		{
		Savecompleteslider().Maximum(10);
		}
}

void SecondaryAppWindowPageDX::OnEventExecuteImmediatly(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(g_PreComInclude == false)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(g_ShuttleCom->m_Cost, g_ShuttleCom->m_ID);

		if(f_hasBought == true) //win 1
			{
			::g_QcomManager->acClearGridNew(g_ShuttleCom);

			::g_QcomManager->acParse_GenScript(g_ShuttleCom);

			acBuild_ExcomPackaging();

			insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

			char* f_Char = new char[255];

			sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

			insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

			delete[] f_Char;

			DisplayInterfaceCom(g_ShuttleCom);

			g_PreComBoughtIN = 1;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

			insertinsertbutton().BorderBrush(myBrush);

			eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

			//Receiver ~Compile Execute
			g_ShuttleCom->m_vec_ESLFunction[0]->ac_Execute();
			}
		else
			{
			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 55, 50));

			insertinsertbutton().BorderBrush(myBrush);
			}
		}
	else
		{
		insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

		char* f_Char = new char[255];

		sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

		insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

		delete[] f_Char;

		DisplayInterfaceCom(g_ShuttleCom);

		g_PreComBoughtIN = 0;

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 55, 50));

		insertinsertbutton().BorderBrush(myBrush);

		eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

		//Receiver ~Compile Execute
		g_ShuttleCom->ac_Execute();
		}
}

void SecondaryAppWindowPageDX::OnClickPlaceInCurrentGrid(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

#if 0
	g_ShuttleCom->m_position.m_X = Cube::g_QcomManager->m_current_X;
	g_ShuttleCom->m_position.m_Y = Cube::g_QcomManager->m_current_Y;
	g_ShuttleCom->m_position.m_Z = 0.0;
#endif

	if(g_PreComInclude == false)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(g_ShuttleCom->m_Cost, g_ShuttleCom->m_ID);

		if(f_hasBought == true) //win 1
			{
#if 0
			for(int f_XY = 0; f_XY < g_ShuttleCom->m_vec_Qcom.size(); f_XY++)
				{
				::g_QcomManager->m_Qcom->m_vec_Qcom.push_back(g_ShuttleCom->m_vec_Qcom[f_XY]);
				}

			::g_QcomManager->acParse_GenScript(g_ShuttleCom);

			acBuild_ExcomPackaging();

			g_ShuttleCom = nullptr;
#endif

			qcomappBar().IsOpen(true);

			::g_QcomManager->m_Open = true;

			insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

			char* f_Char = new char[255];

			sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

			insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

			delete[] f_Char;

			DisplayInterfaceCom(g_ShuttleCom);

			g_PreComBoughtIN = 1;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

			insertinsertbutton().BorderBrush(myBrush);
			}
		else
			{
			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 55, 50));

			insertinsertbutton().BorderBrush(myBrush);
			}
		}
	else
		{
#if 0
		for(int f_XY = 0; f_XY < g_ShuttleCom->m_vec_Qcom.size(); f_XY++)
			{
			::g_QcomManager->m_Qcom->m_vec_Qcom.push_back(g_ShuttleCom->m_vec_Qcom[f_XY]);
			}

		::g_QcomManager->acParse_GenScript(g_ShuttleCom);

		acBuild_ExcomPackaging();

		g_ShuttleCom = nullptr;
#endif

		qcomappBar().IsOpen(true);

		::g_QcomManager->m_Open = true;

		insertnametextBox().Text(StrUsingStr(g_ShuttleCom->m_name));

		char* f_Char = new char[255];

		sprintf(f_Char, "%.2f", g_ShuttleCom->m_Cost);

		insertpricetextBox().Text(StrUsingStr(std::string(f_Char)));

		delete[] f_Char;

		DisplayInterfaceCom(g_ShuttleCom);

		g_PreComBoughtIN = 0;

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 200, 255, 90));

		insertinsertbutton().BorderBrush(myBrush);
		}
}

void SecondaryAppWindowPageDX::OnClickPlaceInstall(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

#if 0
	if(g_PreComInclude == false)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(g_ShuttleCom->m_Cost, g_ShuttleCom->m_ID);

		if(f_hasBought == true) //win 1
			{
			if(g_ShuttleCom->m_vec_Input.size() > 0)
				{
				std::shared_ptr<QcomInput> f_Input = g_ShuttleCom->m_vec_Input[0];

				if(f_Input->m_name.compare("OnInstall") == 0)
					{
					int f_PEXMAPIDX = g_ShuttleCom->m_typed;
					int f_SwitchFinger = f_Input->m_typed;

					switch(f_PEXMAPIDX)
						{
						case PEX_MAIN_NODE_IDX:
							{
							switch(f_SwitchFinger)
								{
								case 0: //simple install default com runtime
									{
									//...com A type install
									}break;

								case 1: //install PEX in main node
									{
#if 0
									if(g_MainNode->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
										{
										g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}
#endif
									}break;

								default:
									{
#if 0
									if(g_MainNode->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
										{
										g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}
#endif
									}break;
								}
							}break;

						case PEX_EXCOM_MAIN_IDX:
							{
							switch(f_SwitchFinger)
								{
								case 0: //simple install default com runtime
									{
									//...com A type install
									}break;

								case 1: //install PEX in main node
									{
									if(//g_ExcomPexMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
										{
										g_ExcomPexMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}
									}break;

								default:
									{
									if(//g_ExcomPexMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
										{
										g_ExcomPexMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}
									}break;
								}
							}break;

						case PEX_INSTALL_MAIN_IDX:
							{
							switch(f_SwitchFinger)
								{
								case 0: //simple install default com runtime
									{
									//...com A type install
									}break;

								case 1: //install PEX in main node
									{
									if(g_InstallMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
										{
										g_InstallMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}
									}break;

								default:
									{
									if(g_InstallMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
										{
										g_InstallMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}
									}break;
								}
							}break;

						case EXCOM_MAIN_INSERT_IDX:
						case EXCOM_MAIN_COMPLETE_IDX:
						case EXCOM_MAIN_REMOVE_IDX:
							{
							for(int f_XY = 0; f_XY < g_MainNode->m_vec_NodeChildren.size(); f_XY++)
								{
								std::shared_ptr<BiProtocolExNode> f_Node = g_ExcomPexMain->m_vec_NodeChildren[f_XY];

								if(f_Node->m_PEXMAPIDX == f_PEXMAPIDX)
									{
									switch(f_SwitchFinger)
										{
										case 0: //simple install default com runtime
											{
											//...com A type install
											}break;

										case 1: //install PEX in main node
											{
											if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
												{
												f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
												}
											}break;

										default:
											{
											if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
												{
												f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
												}
											}break;
										}
									}
								}
							}break;

						default:
							{
							bool f_Change = false;

							if(g_MainNode->m_vec_NodeChildren.size() > PEX_INSTALL_MAIN_IDX)
								{
								for(int f_XY = PEX_IDX_MAX; f_XY < g_MainNode->m_vec_NodeChildren.size(); f_XY++)
									{
									std::shared_ptr<BiProtocolExNode> f_Node = g_MainNode->m_vec_NodeChildren[f_XY];

									if(f_Node->m_PEXMAPIDX == f_PEXMAPIDX)
										{
										switch(f_SwitchFinger)
											{
											case 0: //0 simple install default com runtime
												{
												//...com A type install
												f_Change = true;
												}break;

											case 1: //1 install PEX in main node
												{
												if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
													{
													f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
													}

												f_Change = true;
												}break;

											default:
												{
												if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
													{
													f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
													}

												f_Change = true;
												}break;
											}
										}
									}
								}
					
							if(f_Change == false)
								{
								switch(f_SwitchFinger)
									{
									case 0: //simple install default com runtime
										{
										//...com A type install
										}break;

									case 1: //install PEX in main node
										{
										g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}break;

									default:
										{
										g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
										}break;
									}
								}
							}break;
						}
					}
				}

			g_ShuttleCom = nullptr;

			//reset win
			g_PreComInclude = false;
			g_PreComLock = false;
			g_PreComBool = false;
			g_PreComBoughtIN = 0;

			Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

			insertinsertbutton().BorderBrush(myBrush);

			eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			}
		}
	else
		{
		if(g_ShuttleCom->m_vec_Input.size() > 0)
			{
			std::shared_ptr<QcomInput> f_Input = g_ShuttleCom->m_vec_Input[0];

			if(f_Input->m_name.compare("OnInstall") == 0)
				{
				int f_PEXMAPIDX = g_ShuttleCom->m_typed;
				int f_SwitchFinger = f_Input->m_typed;

				switch(f_PEXMAPIDX)
					{
					case PEX_MAIN_NODE_IDX:
						{
						switch(f_SwitchFinger)
							{
							case 0: //simple install default com runtime
								{
								//...com A type install
								}break;

							case 1: //install PEX in main node
								{
								if(g_MainNode->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
									{
									g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}
								}break;

							default:
								{
								if(g_MainNode->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
									{
									g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}
								}break;
							}
						}break;

					case PEX_EXCOM_MAIN_IDX:
						{
						switch(f_SwitchFinger)
							{
							case 0: //simple install default com runtime
								{
								//...com A type install
								}break;

							case 1: //install PEX in main node
								{
								if(//g_ExcomPexMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
									{
									g_ExcomPexMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}
								}break;

							default:
								{
								if(//g_ExcomPexMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
									{
									g_ExcomPexMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}
								}break;
							}
						}break;

					case PEX_INSTALL_MAIN_IDX:
						{
						switch(f_SwitchFinger)
							{
							case 0: //simple install default com runtime
								{
								//...com A type install
								}break;

							case 1: //install PEX in main node
								{
								if(g_InstallMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
									{
									g_InstallMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}
								}break;

							default:
								{
								if(g_InstallMain->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
									{
									g_InstallMain->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}
								}break;
							}
						}break;

					case EXCOM_MAIN_INSERT_IDX:
					case EXCOM_MAIN_COMPLETE_IDX:
					case EXCOM_MAIN_REMOVE_IDX:
						{
						for(int f_XY = 0; f_XY < g_MainNode->m_vec_NodeChildren.size(); f_XY++)
							{
							std::shared_ptr<BiProtocolExNode> f_Node = g_ExcomPexMain->m_vec_NodeChildren[f_XY];

							if(f_Node->m_PEXMAPIDX == f_PEXMAPIDX)
								{
								switch(f_SwitchFinger)
									{
									case 0: //simple install default com runtime
										{
										//...com A type install
										}break;

									case 1: //install PEX in main node
										{
										if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
											{
											f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
											}
										}break;

									default:
										{
										if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
											{
											f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
											}
										}break;
									}
								}
							}
						}break;

					default:
						{
						bool f_Change = false;

						if(g_MainNode->m_vec_NodeChildren.size() > PEX_INSTALL_MAIN_IDX)
							{
							for(int f_XY = PEX_IDX_MAX; f_XY < g_MainNode->m_vec_NodeChildren.size(); f_XY++)
								{
								std::shared_ptr<BiProtocolExNode> f_Node = g_MainNode->m_vec_NodeChildren[f_XY];

								if(f_Node->m_PEXMAPIDX == f_PEXMAPIDX)
									{
									switch(f_SwitchFinger)
										{
										case 0: //0 simple install default com runtime
											{
											//...com A type install
											f_Change = true;
											}break;

										case 1: //1 install PEX in main node
											{
											if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
												{
												f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
												}

											f_Change = true;
											}break;

										default:
											{
											if(f_Node->acExecute(f_PEXMAPIDX, 0, f_SwitchFinger) == false)
												{
												f_Node->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
												}

											f_Change = true;
											}break;
										}
									}
								}
							}
					
						if(f_Change == false)
							{
							switch(f_SwitchFinger)
								{
								case 0: //simple install default com runtime
									{
									//...com A type install
									}break;

								case 1: //install PEX in main node
									{
									g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}break;

								default:
									{
									g_MainNode->acInstallPEX(g_ShuttleCom, f_PEXMAPIDX, 0, f_SwitchFinger);
									}break;
								}
							}
						}break;
					}
				}
			}
#endif
#if 0
		g_ShuttleCom = nullptr;

		//reset win
		g_PreComInclude = false;
		g_PreComLock = false;
		g_PreComBool = false;
		g_PreComBoughtIN = 0;

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

		insertinsertbutton().BorderBrush(myBrush);

		eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
#endif
}

void SecondaryAppWindowPageDX::OnClickPayBuyOnce(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	bool f_hasBought = g_Wallet->acBuy_ShareComID(g_ShuttleCom->m_ID, g_ShuttleCom->m_Cost, g_ShuttleCom->m_Cost, g_ShuttleCom->m_PackageShareID);

	if(f_hasBought == true)
		{
		//...win conditions
		}
}

void SecondaryAppWindowPageDX::OnClickPayBuyAmount(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	//adjeust pay amount
	bool f_hasBought = g_Wallet->acBuy_ShareComID(g_ShuttleCom->m_ID, g_ShuttleCom->m_Cost, g_ShuttleCom->m_Cost, g_ShuttleCom->m_PackageShareID);

	if(f_hasBought == true)
		{
		//...win conditions playsound message ack even
		}
}

void SecondaryAppWindowPageDX::OnClickPayJoinMembership(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	//adjeust pay amount
	bool f_hasBought = g_Wallet->acBuy_ShareComID(g_ShuttleCom->m_ID, g_ShuttleCom->m_Cost, g_ShuttleCom->m_Cost, g_ShuttleCom->m_PackageShareID);

	if(f_hasBought == true)
		{
		//...win conditions
		}
}

void SecondaryAppWindowPageDX::OnClickPayBuyBundle(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	//adjeust pay amount
	bool f_hasBought = g_Wallet->acBuy_ShareComID(g_ShuttleCom->m_ID, g_ShuttleCom->m_Cost, g_ShuttleCom->m_Cost, g_ShuttleCom->m_PackageShareID);

	if(f_hasBought == true)
		{
		//...win conditions
		}
}

void SecondaryAppWindowPageDX::OnClickPayZeroNow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

#pragma message("FIXME::Add payment modules")
#if 0
	//adjust pay amount
	bool f_hasBought = g_Wallet->acBuy_ShareComID(g_ShuttleCom->m_ID, g_ShuttleCom->m_Cost, g_ShuttleCom->m_Cost, g_ShuttleCom->m_PackageShareID);

	if(f_hasBought == true)
		{
		//...win conditions
		}
#endif
}

void SecondaryAppWindowPageDX::OnClickIncludeProfitEngRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageDX::ONClickIncludeLimitedRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageDX::OnClickIncludeMembershipRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageDX::OnClickIncludeGroupRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageDX::OnClickClosePauseMinimizebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	//reset win
	g_PreComInclude = false;
	g_PreComLock = false;
	g_PreComBool = false;
	g_PreComBoughtIN = 0;

	Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

	insertinsertbutton().BorderBrush(myBrush);

	eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::StartFrameLoop(void)
{
	ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);
	ag_Freshanon<int>(g_Wallet->m_vec_ElementCount, m_IDX, 0);
	ag_Freshanon<int>(g_Wallet->m_vec_StorageCounter, m_IDX, 0);

	while(m_IDX >= g_Wallet->m_vec_Async_Gui_Muti.size())
		{
		g_Wallet->m_vec_Async_Gui_Muti.push_back(std::make_shared<std::shared_mutex>());
		}

	while(m_IDX >= g_Wallet->m_vec_ElementCount_Muti.size())
		{
		g_Wallet->m_vec_ElementCount_Muti.push_back(std::make_shared<std::shared_mutex>());
		}

	ag_Freshanon<std::string>(g_Wallet->m_vec_ComputeText, m_IDX, "");
	ag_Freshanon<std::string>(g_Wallet->m_vec_ComputeText_Lowton, m_IDX, "");
	ag_Freshanon<int>(g_Wallet->m_vec_ComputeText_PrintMode, m_IDX, ECOIN_MUTEX_MODE_OFF);
	ag_Freshanon<int>(g_Wallet->m_vec_ComputeText_PrintMode_Lowton, m_IDX, ECOIN_MUTEX_MODE_OFF);

#if 0
	if(m_FrameTimer != nullptr)
		{
		if(m_FrameTimer.IsEnabled() == false)
			{
			m_FrameTimer = winrt::Windows::UI::Xaml::DispatcherTimer();

			TimeSpan ts(ECOIN_ASYNC_REFRESH_MILLISECONDS);
			m_FrameTimer.Interval(ts);
			m_FrameTimer.Start();
			auto registrationtoken = m_FrameTimer.Tick({ this, &SecondaryAppWindowPageDX::Frame_OnCount });
			}
		else
			{
			m_FrameTimer.Start();
			}
		}
	else
		{
		m_FrameTimer = winrt::Windows::UI::Xaml::DispatcherTimer();

		TimeSpan ts(ECOIN_ASYNC_REFRESH_MILLISECONDS);
		m_FrameTimer.Interval(ts);
		m_FrameTimer.Start();
		auto registrationtoken = m_FrameTimer.Tick({ this, &SecondaryAppWindowPageDX::Frame_OnCount });
		}
#endif

	m_Frame_ThreadON = true;
}

void SecondaryAppWindowPageDX::StopFrameLoop(void)
{
	if(m_FrameTimer.IsEnabled())
		{
		m_FrameTimer.Stop();
		}

	m_Frame_ThreadON = false;
}

void SecondaryAppWindowPageDX::OnClickPutToBackbutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(g_ShuttleCom != nullptr)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(-1, 0.0f, g_ShuttleCom->m_ID);

		if(f_hasBought == true)
			{
			::g_QcomManager->m_SaveCom.push_back(g_ShuttleCom);

			g_ShuttleCom = nullptr;
			}
		}

	//reset win
	g_PreComInclude = false;
	g_PreComLock = false;
	g_PreComBool = false;
	g_PreComBoughtIN = 0;

	Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

	insertinsertbutton().BorderBrush(myBrush);

	eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::OnClickIgnoreClosebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	//reset win
	g_PreComInclude = false;
	g_PreComLock = false;
	g_PreComBool = false;
	g_PreComBoughtIN = 0;

	Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

	insertinsertbutton().BorderBrush(myBrush);

	eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::OnClickCancelClosebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

	g_ShuttleCom = nullptr;

	//reset win
	g_PreComInclude = false;
	g_PreComLock = false;
	g_PreComBool = false;
	g_PreComBoughtIN = 0;

	Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

	insertinsertbutton().BorderBrush(myBrush);

	eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::OnClickLogOut(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::OnClickLogOut";

	if(g_ConnectedECD == true)
		{
		g_ConnectedECD = false;

		for(int f_XY = 0; f_XY < 3; f_XY++)
			{
			g_Schedular[f_XY]->acShutdown();
			}

		logoutbutton().Content(box_value(StrUsingStr("Close App or Click Connect")));
		}
}

void SecondaryAppWindowPageDX::OnClickStorePolicy(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	// Create the URI from a string
	std::string f_URL = "http://www.osirem.com/affiliate/osi_privacy_policy_orig.html";

	Uri uri({ StrUsingStr(f_URL) });

	// Launch the URI
	Windows::System::Launcher::LaunchUriAsync(uri);
}

void SecondaryAppWindowPageDX::OnClicktandc(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	// Create the URI from a string
	std::string f_URL = "http://www.osirem.com/affiliate/t&c.html";

	Uri uri({ StrUsingStr(f_URL) });

	// Launch the URI
	Windows::System::Launcher::LaunchUriAsync(uri);
}

void SecondaryAppWindowPageDX::OnClickStopAll(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

	if(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW)
		{
		g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_SHUTDOWN_NONVIEW;
		}
	else if(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS)
		{
		g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_SHUTDOWN_COMPRESS;
		}

	computeoutputlowtontextBox().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	computeoutputtextBox().Visibility(Windows::UI::Xaml::Visibility::Collapsed);

	currentStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::OnLoadPledgeStack(void)
{
	//reset input
	pledgeegbpaddtextBox().Text(L"0.0000");
	pledgeecnaddtextBox().Text(L"0.00000000");

	ag_Freshanon<int>(g_Wallet->m_vec_pledgetype, m_IDX, 0);

	switch(g_Wallet->m_vec_pledgetype[m_IDX])
		{
		case ecoin_PledgeType::ecoin_Pledge_MaxTimed:
			{
			char* f_CharXYZ1 = ag_ClearChar(64);
			printf(f_CharXYZ1, "%i", ag_FreshAndOnly<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0));

			time_t f_CurrentTime;
			time(&f_CurrentTime);

			int f_TimeRemaining = ag_FreshAndOnly<int>(g_Wallet->m_vec_targetbreach, m_IDX, f_CurrentTime);

			char* f_CharXYZ2 = ag_ClearChar(64);
			printf(f_CharXYZ2, "%i", f_TimeRemaining);

			std::string f_MaxTimedPledge = " Culmulative And Timed Pledge for Block\r Max Pledge " + std::string(f_CharXYZ1) + "\r Time Remaining (secs) " + std::string(f_CharXYZ2);

			maximumpledgetextBlock().Text(StrUsingStr(f_MaxTimedPledge));

#if 0
			pledgeegbpaddtextBox().IsReadOnly(false);
			pledgeecnaddtextBox().IsReadOnly(false);
#endif
			}break;

		case ecoin_PledgeType::ecoin_Pledge_Max:
			{
			char* f_CharXYZ = ag_ClearChar(64);

			ag_Freshanon<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0);

			printf(f_CharXYZ, "%i", g_Wallet->m_vec_maxpledge[m_IDX]);

			std::string f_MaxPledge = " Culmulative Pledge for Block\r Current Maximum Pledge\r " + std::string(f_CharXYZ);

			maximumpledgetextBlock().Text(StrUsingStr(f_MaxPledge));

#if 0
			pledgeegbpaddtextBox().IsReadOnly(false);
			pledgeecnaddtextBox().IsReadOnly(false);
#endif
			}break;

		case ecoin_PledgeType::ecoin_Pledge_Timed:
			{
			time_t f_CurrentTime;
			time(&f_CurrentTime);

			ag_Freshanon<int>(g_Wallet->m_vec_targetbreach, m_IDX, 0);

			int f_TimeRemaining = g_Wallet->m_vec_targetbreach[m_IDX] - f_CurrentTime;

			char* f_CharXYZ2 = ag_ClearChar(64);
			printf(f_CharXYZ2, "%i", f_TimeRemaining);

			std::string f_TimedPledge = " Timed Pledge for Block\r Time Remaining (secs) " + std::string(f_CharXYZ2);

			maximumpledgetextBlock().Text(StrUsingStr(f_TimedPledge));

#if 0
			pledgeegbpaddtextBox().IsReadOnly(false);
			pledgeecnaddtextBox().IsReadOnly(false);
#endif
			}break;

		case ecoin_PledgeType::ecoin_Pledge_Off:
			{
			maximumpledgetextBlock().Text(L" Pledges for this Share OFF");

#if 0
			pledgeegbpaddtextBox().IsReadOnly(true);
			pledgeecnaddtextBox().IsReadOnly(true);
#endif
			}break;
		}

	if((g_ShareID > 0) && (g_Wallet->m_vec_pledgetype[m_IDX] != ecoin_PledgeType::ecoin_Pledge_Off))
		{
		auto f_Info = winrt::Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();

		char* f_CharX = ag_ClearChar(256);
		::sprintf(f_CharX, "%u%u", f_Info.Id().Data1, f_Info.Id().Data2);
		std::string Id = f_CharX;
		delete f_CharX;

		char* rfpquery = ag_ClearChar(512);
		::sprintf(rfpquery, "SELECT IFNULL(SUM(pledge), 0), IFNULL(SUM(ecnpledge), 0) FROM reference WHERE ((shareid = %i) AND (jobid = %i))", g_ShareID, g_JobID/*, g_Wallet->m_vec_blockid[m_IDX]*/);
		g_SafeL[0]->acSelectCommand(rfpquery, false, false);
		delete rfpquery;

		int f_allrefCount = 0;

		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_allrefCount = 0;
			}
		else
			{
			f_allrefCount = g_Schedular[0]->acEntrySize();
			}

		//gather current entire pledge
		ag_Freshanon<float>(g_Wallet->m_vec_current_pledge, m_IDX, 0.0f);
		ag_Freshanon<float>(g_Wallet->m_vec_current_ecnpledge, m_IDX, 0.0f);

		if(f_allrefCount == 1)
			{
			g_Wallet->m_vec_current_pledge[m_IDX] = atof(g_Schedular[0]->acEntry(0)[0].c_str());
			g_Wallet->m_vec_current_ecnpledge[m_IDX] = atof(g_Schedular[0]->acEntry(0)[1].c_str());

			//update share integer voting score
			float f_ScoreResultFloat = g_Wallet->m_vec_current_pledge[m_IDX] + (g_Wallet->m_vec_current_ecnpledge[m_IDX] * g_Wallet->m_Price);

			g_Wallet->m_pledge_Total = f_ScoreResultFloat;

			//set pledge count level
			char* f_Char = ag_ClearChar(128);
			::sprintf(f_Char, "%f", f_ScoreResultFloat);

			winrt::hstring f_CountLevelString = StrUsingStr(f_Char);

			delete f_Char;

			pledgeinfocounttextBlock().Text(f_CountLevelString);

			//set pledge count level
			char* f_CharA = ag_ClearChar(512);
			::sprintf(f_CharA, "%f", g_Wallet->m_vec_current_pledge[m_IDX]);

			winrt::hstring f_EGBP_String = StrUsingStr(f_CharA);

			delete f_CharA;

			char* f_CharB = ag_ClearChar(512);
			::sprintf(f_CharB, "%f", g_Wallet->m_vec_current_ecnpledge[m_IDX]);

			winrt::hstring f_ECN_String = StrUsingStr(f_CharB);

			delete f_CharB;

			pledgeegbpamttextBlock().Text(f_EGBP_String);
			pledgeecnamttextBlock().Text(f_ECN_String);

			g_espo_Score = g_Wallet->m_pledge_Total;

			char* numbuf88 = ag_ClearChar(512);
			_itoa(g_espo_Score, numbuf88, 10);

			std::string f_interim88 = numbuf88;

			delete numbuf88;

			voteinfoBlock().Text(StrUsingStr(f_interim88));

			g_espo_Amount = g_Wallet->m_vec_current_pledge[m_IDX];

			char* f_CharX3 = ag_ClearChar(512);

			::sprintf(f_CharX3, "%.4f eGBP", (float)g_espo_Amount);
			std::string f_String13 = f_CharX3;

			pledgeinfoBlock().Text(StrUsingStr(f_String13));

			delete f_CharX3;

			g_espo_ECN_Amount = g_Wallet->m_vec_current_ecnpledge[m_IDX];

			char* f_Char1 = ag_ClearChar(512);

			::sprintf(f_Char1, "%.8f ECN", (float)g_espo_ECN_Amount);
			std::string f_String14 = f_Char1;

			delete f_Char1;

			ecnpledgeinfoBlock().Text(StrUsingStr(f_String14));

			char* rfpaquery = ag_ClearChar(512);
			::sprintf(rfpaquery, "SELECT id, pledge, ecnpledge FROM reference WHERE ((hdid = '%s') AND (shareid = %i) AND (blockid = %i) AND (owner = '%s'))", Id.c_str(), g_ShareID, g_Wallet->m_vec_blockid[m_IDX], g_Wallet->GetAdr().c_str());
			g_SafeL[0]->acSelectCommand(rfpaquery, false, false);
			delete rfpaquery;

			int f_refCount = 0;
		
			if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
				{
				f_refCount = 0;
				}
			else
				{
				f_refCount = g_Schedular[0]->acEntrySize();
				}

			if(f_refCount == 1)
				{
				//gather my current pledge
				g_Wallet->m_my_pledge_shareID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
				g_Wallet->m_my_EGBP_pledge = atof(g_Schedular[0]->acEntry(0)[1].c_str());
				g_Wallet->m_my_ECN_pledge = atof(g_Schedular[0]->acEntry(0)[2].c_str());

				//set pledge count level
				char* f_CharC = ag_ClearChar(512);
				::sprintf(f_CharC, "%f", g_Wallet->m_my_EGBP_pledge);

				winrt::hstring f_my_EGBP_String = StrUsingStr(f_CharC);

				delete f_CharC;

				char* f_CharD = ag_ClearChar(512);
				::sprintf(f_CharD, "%f", g_Wallet->m_my_ECN_pledge);

				winrt::hstring f_my_ECN_String = StrUsingStr(f_CharD);

				delete f_CharD;

				pledgeegbpmyamttextBlock().Text(f_my_EGBP_String);
				pledgeecnmyamttextBlock().Text(f_my_ECN_String);

				g_Wallet->m_my_Active_pledge = true;
				}
			else
				{
				g_Wallet->m_my_Active_pledge = false;
				g_Wallet->m_my_pledge_shareID = 0;
				g_Wallet->m_my_EGBP_pledge = 0.0f;
				g_Wallet->m_my_ECN_pledge = 0.0f;
				}
			}
		else
			{
			g_Wallet->m_pledge_Total = 0.0f;
			g_Wallet->m_my_Active_pledge = false;
			g_Wallet->m_my_pledge_shareID = 0;
			g_Wallet->m_my_EGBP_pledge = 0.0f;
			g_Wallet->m_my_ECN_pledge = 0.0f;

			pledgeinfocounttextBlock().Text(L"0");

			pledgeegbpamttextBlock().Text(L"0.0000");
			pledgeegbpamttextBlock().Text(L"0.00000000");

			pledgeegbpaddtextBox().Text(L"0.0000");
			pledgeecnaddtextBox().Text(L"0.00000000");

			pledgeegbpmyamttextBlock().Text(L"0.0000");
			pledgeecnmyamttextBlock().Text(L"0.00000000");
			}
		}
}

void SecondaryAppWindowPageDX::OnClickPledgeSynchronize(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::acLoadShare";

	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	bool f_LaunchSync = true;

	std::string f_eGBP_Pledge = "";

	float f_eGBP_Pledge_amt = 0.0f;

	std::string f_ECN_Pledge = "";

	float f_ECN_Pledge_amt = 0.0f;

	if(pledgeegbpaddtextBox().IsReadOnly() == true)
		{
		if(pledgeecnaddtextBox().IsReadOnly() == true)
			{
			f_LaunchSync = false;
			}
		else
			{
			f_eGBP_Pledge = to_string(pledgeegbpaddtextBox().Text());

			f_eGBP_Pledge_amt = ag_CheckFloat(f_eGBP_Pledge);
			}
		}
	else
		{
		f_eGBP_Pledge = to_string(pledgeegbpaddtextBox().Text());

		f_eGBP_Pledge_amt = ag_CheckFloat(f_eGBP_Pledge);

		if(pledgeecnaddtextBox().IsReadOnly() == false)
			{
			f_ECN_Pledge = to_string(pledgeecnaddtextBox().Text());

			f_ECN_Pledge_amt = ag_CheckFloat(f_ECN_Pledge);
			}
		}

	if((g_ShareID > 0) && (f_LaunchSync == true))
		{
		int f_Result = 1;

		if(f_eGBP_Pledge_amt > 0.0f)
			{
			f_Result = g_Wallet->acSet_ConstantBalance(g_Wallet->GetAdr(), (f_eGBP_Pledge_amt * -1));
			}
	
		int f_ECN_Result = f_Result;

		if(f_ECN_Pledge_amt > 0.0f)
			{
			f_ECN_Result = Cag->ag_GenerateTransaction(g_Wallet->GetAdr(), g_espo_Owner, f_ECN_Pledge_amt);
			}

		if(f_ECN_Result != 1)
			{
			pledgeresultstextBlock().Text(L"[FAILURE] Not enough value available in wallet. Token Spend or ECN Transaction failed.");
			}
		else
			{
			if((f_eGBP_Pledge_amt > 0.0f) || (f_ECN_Pledge_amt > 0.0f))
				{
				ag_Freshanon<int>(g_Wallet->m_vec_pledgetype, m_IDX, ecoin_PledgeType::ecoin_Pledge_Off);

				if(g_Wallet->m_vec_pledgetype[m_IDX] == ecoin_PledgeType::ecoin_Pledge_Off)
					{
					g_Wallet->m_vec_pledgetype[m_IDX] = ecoin_PledgeType::ecoin_Pledge_Max;

					g_BlockType = ecoin_BlockType::ecoin_Block_MaxPledge;
		
					ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);

					ag_FreshOn<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
					ag_FreshOn<std::string>(g_Wallet->m_vec_eslcode, m_IDX, "MaxPledge");

					ag_FreshOn<int>(::g_Wallet->m_vec_maxpledge, m_IDX, 0);
					ag_FreshOn<int>(::g_Wallet->m_vec_targetbreach, m_IDX, 0);
					ag_FreshOn<int>(::g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);

					ag_Freshanon<float>(::g_Wallet->m_vec_markmax, m_IDX, 0.0f);
					ag_Freshanon<float>(::g_Wallet->m_vec_markmin, m_IDX, 0.0f);

					g_Wallet->acSet_IDX(m_IDX);
					//...
					g_Wallet->acSave_currentJob();
					}

				if(g_Wallet->m_my_Active_pledge == false) //new reference
					{
					//update my share integer pledge strength score
					float f_ScoreResultFloat = f_eGBP_Pledge_amt + (f_ECN_Pledge_amt * g_Wallet->m_Price);

					auto f_Info = winrt::Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();

					char* f_CharX = ag_ClearChar(256);
					::sprintf(f_CharX, "%u%u", f_Info.Id().Data1, f_Info.Id().Data2);
					std::string Id = f_CharX;
					delete f_CharX;

					ag_FreshAndOnly<int>(g_Wallet->m_vec_blockid, m_IDX, -1551);
					ag_FreshAndOnly<int>(g_Wallet->m_vec_comid, m_IDX, -1);
					ag_FreshOn<int>(g_Wallet->m_vec_access, m_IDX, 2);

					char* g_refvalue[17];

					for(int f_Count = 0; f_Count < 17; f_Count++)
						{
						g_refvalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
						}

					::sprintf(g_refvalue[0], "%i", 0);
					::sprintf(g_refvalue[1], "%i", 3);
					::sprintf(g_refvalue[2], "%s", "Ecoin_Share_Pledge_Reference");
					::sprintf(g_refvalue[3], "%s", Id.c_str());
					::sprintf(g_refvalue[4], "%i", 0);
					::sprintf(g_refvalue[5], "%i", g_Wallet->m_vec_access[m_IDX]);
					::sprintf(g_refvalue[6], "%i", g_ShareID);
					::sprintf(g_refvalue[7], "%i", 1);
					::sprintf(g_refvalue[8], "%i", g_JobID);
					::sprintf(g_refvalue[9], "%i", g_Wallet->m_vec_blockid[m_IDX]);
					::sprintf(g_refvalue[10], "%i", g_Wallet->m_vec_comid[m_IDX]);
					::sprintf(g_refvalue[11], "%s", "none");
					::sprintf(g_refvalue[12], "%f", f_ScoreResultFloat);
					::sprintf(g_refvalue[13], "%i", 0);
					::sprintf(g_refvalue[14], "%s", g_Wallet->GetAdr().c_str());
					::sprintf(g_refvalue[15], "%f", f_eGBP_Pledge_amt);
					::sprintf(g_refvalue[16], "%f", f_ECN_Pledge_amt);

					g_SafeL[0]->Insert("reference", (const char **)g_reffield, (const char **)g_refvalue, 17, false, false);

					for(int f_Count = 0; f_Count < 17; f_Count++)
						{
						free(g_refvalue[f_Count]);
						}
					
					char* RAFquery = ag_ClearChar(1000);
					::sprintf(RAFquery, "SELECT id, owner FROM share WHERE id = %i", g_Wallet->m_my_pledge_shareID);
					g_SafeL[0]->acSelectCommand(RAFquery, false, false);
					delete RAFquery;

					int f_RAFLCount = 0;

					//ECN::Stat::: f_RAFLCount
					if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
						{
						f_RAFLCount = 0;
						}
					else
						{
						f_RAFLCount = g_Schedular[2]->acEntrySize();
						}

					std::string f_PathOwner = "unknown";

					//checks
					if(f_RAFLCount > 0)
						{
						f_PathOwner = g_Schedular[2]->acEntry(0)[1];
						}

					//ECN::Reference Submitted.
					ag_StatusLive(f_ref_CurrentPath, "f_AckReference");
					std::shared_ptr<Ackent> f_AckReference = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_REF), g_ShareID, 1);
					f_AckReference->m_ECN = 0.0f;
					f_AckReference->m_Reward = g_Wallet->m_Reward;
					f_AckReference->m_Origin = 1;
					f_AckReference->m_Owner = g_Wallet->GetAdr();
					f_AckReference->m_PathOwner = f_PathOwner;
					g_Ackent.push_back(f_AckReference);

					OnLoadPledgeStack();

					if(f_eGBP_Pledge_amt > 0.0f)
						{
						if(f_ECN_Pledge_amt > 0.0f)
							{
							pledgeresultstextBlock().Text(L"[SUCCESS] eGBP Toke and ECN Pledge Synchronize");
							}
						else
							{
							pledgeresultstextBlock().Text(L"[SUCCESS] eGBP Toke Synchronize");
							}
						}
					else
						{
						if(f_ECN_Pledge_amt > 0.0f)
							{
							pledgeresultstextBlock().Text(L"[SUCCESS] ECN Pledge Synchronize");
							}
						}
					}
				else
					{
					f_eGBP_Pledge_amt += g_Wallet->m_my_EGBP_pledge;
					f_ECN_Pledge_amt += g_Wallet->m_my_ECN_pledge;

					char* f_reffield[5];
					char* f_refvalue[5];
					char* f_refwhere[1];

					for(int f_Count = 0; f_Count < 5; f_Count++)
						{
						f_reffield[f_Count] = (char*)malloc(sizeof(char) * 1024);
						f_refvalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
						}

					f_refwhere[0] = (char*)malloc(sizeof(char) * 1024);

					::sprintf(f_reffield[0], "level");
					::sprintf(f_reffield[1], "access");
					::sprintf(f_reffield[2], "score");
					::sprintf(f_reffield[3], "pledge");
					::sprintf(f_reffield[4], "ecnpledge");

					::sprintf(f_refvalue[0], "%i", 2);
					::sprintf(f_refvalue[1], "%i", 2);
					::sprintf(f_refvalue[2], "%f", g_Wallet->m_pledge_Total);
					::sprintf(f_refvalue[3], "%f", f_eGBP_Pledge_amt);
					::sprintf(f_refvalue[4], "%f", f_ECN_Pledge_amt);

					::sprintf(f_refwhere[0], "id = %i", g_Wallet->m_my_pledge_shareID);

					g_SafeL[0]->Update("reference", (const char**)f_reffield, (const char**)f_refvalue, 5, f_refwhere[0], true, false);

					for(int f_Count = 0; f_Count < 5; f_Count++)
						{
						free(f_reffield[f_Count]);
						free(f_refvalue[f_Count]);
						}

					free(f_refwhere[0]);

					char* RAFquery = ag_ClearChar(1000);
					::sprintf(RAFquery, "SELECT id, owner FROM share WHERE id = %i", g_Wallet->m_my_pledge_shareID);
					g_SafeL[0]->acSelectCommand(RAFquery, false, false);
					delete RAFquery;

					int f_RAFLCount = 0;

					//ECN::Stat::: f_RAFLCount
					if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
						{
						f_RAFLCount = 0;
						}
					else
						{
						f_RAFLCount = g_Schedular[2]->acEntrySize();
						}

					std::string f_PathOwner = "unknown";

					//checks
					if(f_RAFLCount > 0)
						{
						f_PathOwner = g_Schedular[2]->acEntry(0)[1];
						}

					//ECN::Reference Submitted.
					ag_StatusLive(f_ref_CurrentPath, "f_AckReference");
					std::shared_ptr<Ackent> f_AckReference = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_REF), g_ShareID, 1);
					f_AckReference->m_ECN = 0.0f;
					f_AckReference->m_Reward = g_Wallet->m_Reward;
					f_AckReference->m_Origin = 1;
					f_AckReference->m_Owner = g_Wallet->GetAdr();
					f_AckReference->m_PathOwner = f_PathOwner;
					g_Ackent.push_back(f_AckReference);

					OnLoadPledgeStack();

					if(f_eGBP_Pledge_amt > 0.0f)
						{
						if(f_ECN_Pledge_amt > 0.0f)
							{
							pledgeresultstextBlock().Text(L"[SUCCESS] eGBP Toke and ECN Pledge Synchronize");
							}
						else
							{
							pledgeresultstextBlock().Text(L"[SUCCESS] eGBP Toke Synchronize");
							}
						}
					else
						{
						if(f_ECN_Pledge_amt > 0.0f)
							{
							pledgeresultstextBlock().Text(L"[SUCCESS] ECN Pledge Synchronize");
							}
						}
					}

				if(ag_FreshAndOnly<int>(g_Wallet->m_vec_blocktype, m_IDX, ecoin_BlockType::ecoin_Block_Target_SCP) >= 2) //ecoin_Pledge
					{ ///////////
					 // JobID //
					///////////
					g_JobID = g_Wallet->acGet_JobID(m_IDX);

					  /////////////
					 // Hash //
					// check GenesisBlock (assume)
					std::string f_StrBlock = "GENESISBLOCK";

					ag_Freshanon<std::string>(g_Wallet->m_vec_prevblock, m_IDX, f_StrBlock);

					std::string f_previousblock = g_Wallet->m_vec_prevblock[m_IDX];
					//ECN::Hesh...Checking Previous BlockHesh

					 //////////////////
					// Hash Results //
					std::shared_ptr<Cube::CubeResults> f_Res = Cag->ag_GatherTransactions(g_JobID, m_IDX);

					 ///////////////
					// TXHash //
					std::string f_tx = f_Res->m_Result;

					 //////////////
					// JOBHash //
					std::string f_job = f_tx + f_previousblock;

					ag_Freshanon<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_StrBlock);

					g_hasha.init(); //reset hasher state
					g_hasha.process(f_job.begin(), f_job.end());
					g_hasha.finish();
					picosha2::get_hash_hex_string(g_hasha, g_Wallet->m_vec_blockledger[m_IDX]);

					ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, 0);
					ag_Freshanon<int>(g_Wallet->m_vec_scoremax, m_IDX, 0);
					ag_Freshanon<float>(g_Wallet->m_vec_markmax, m_IDX, 0.0f);
					ag_Freshanon<float>(g_Wallet->m_vec_markmin, m_IDX, 0.0f);
					ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
					ag_Freshanon<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0.0f);

					switch(g_BlockType)
						{
						case ecoin_BlockType::ecoin_Block_Target_TypeName:
							{
							g_Wallet->m_vec_score[m_IDX] = ag_Get_current_Target_Mark(g_Type);

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
										}
									else
										{
										g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmax[m_IDX];
										}
									}
								else
									{
									if(g_Wallet->m_vec_markmin[m_IDX] > 0.0f)
										{
										g_Wallet->m_vec_maxvote[m_IDX] = g_Wallet->m_vec_markmin[m_IDX];
										}
									else
										{
										g_Wallet->m_vec_maxvote[m_IDX] = 0; //lean towards COMPARE_THRESH minimum mark
										}
									}
								}
							}break;

						case ecoin_BlockType::ecoin_Block_Target_TimedType:
							{
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
							g_Wallet->m_vec_score[m_IDX] = (float)g_BicycleContainer[0]->m_ADMAX;
							g_Wallet->m_vec_maxvote[m_IDX] = (float)g_BicycleContainer[0]->m_ADMAX;
							//...mebbe add debug message
							}break;

						case ecoin_BlockType::ecoin_Block_TimedPledge:
							{
							//convert scoremax to maxvote
							if(g_Wallet->m_vec_scoremax[m_IDX] > 0.0f)
								{
								if(g_Wallet->m_vec_targetbreach[m_IDX] > 0)
									{
									time_t f_CurrentTime;
									time(&f_CurrentTime);

									if(f_CurrentTime > g_Wallet->m_vec_startbreach[m_IDX])
										{
										if(f_CurrentTime > g_Wallet->m_vec_targetbreach[m_IDX]) 
											{
											g_Wallet->m_vec_score[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX];

											g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX];
											}
										else
											{
											g_Wallet->m_vec_score[m_IDX] = ((float)g_Wallet->m_vec_targetbreach[m_IDX] - (float)g_Wallet->m_vec_startbreach[m_IDX]) * ((float)f_CurrentTime - (float)g_Wallet->m_vec_startbreach[m_IDX]);

											g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX];
											}
										}
									else
										{
										g_Wallet->m_vec_score[m_IDX] = (float)g_Wallet->m_vec_startbreach[m_IDX] - (float)f_CurrentTime;

										g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_startbreach[m_IDX];
										}
									}
								else
									{
									g_Wallet->m_vec_score[m_IDX] = f_eGBP_Pledge_amt + (f_ECN_Pledge_amt * g_Wallet->m_Price);

									//convert scoremax to maxvote
									if(g_Wallet->m_vec_maxpledge[m_IDX] > 0)
										{
										g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_maxpledge[m_IDX];
										}
									else
										{
										g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_startbreach[m_IDX];
										}
									}
								}
							else
								{
								if(g_Wallet->m_vec_targetbreach[m_IDX] > 0)
									{
									time_t f_CurrentTime;
									time(&f_CurrentTime);

									if(f_CurrentTime > g_Wallet->m_vec_startbreach[m_IDX])
										{
										if(f_CurrentTime > g_Wallet->m_vec_targetbreach[m_IDX]) 
											{
											g_Wallet->m_vec_score[m_IDX] = (float)ECOIN_REWARD_ON + ((float)g_Wallet->m_vec_targetbreach[m_IDX] - (float)f_CurrentTime);

											g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_scoremax[m_IDX];
											}
										else
											{
											g_Wallet->m_vec_score[m_IDX] = ((float)g_Wallet->m_vec_targetbreach[m_IDX] - (float)g_Wallet->m_vec_startbreach[m_IDX]) * (((float)f_CurrentTime - (float)g_Wallet->m_vec_startbreach[m_IDX]) / ((float)g_Wallet->m_vec_targetbreach[m_IDX] - (float)g_Wallet->m_vec_startbreach[m_IDX]));

											g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_targetbreach[m_IDX] - (float)g_Wallet->m_vec_startbreach[m_IDX];
											}
										}
									else
										{
										g_Wallet->m_vec_score[m_IDX] = ((float)g_Wallet->m_vec_startbreach[m_IDX] - (float)f_CurrentTime) / ECOIN_SCP_REWARD_FACT5000;

										g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_startbreach[m_IDX];
										}
									}
								else
									{
									g_Wallet->m_vec_score[m_IDX] = f_eGBP_Pledge_amt + (f_ECN_Pledge_amt * g_Wallet->m_Price);

									//convert scoremax to maxvote
									if(g_Wallet->m_vec_maxpledge[m_IDX] > 0)
										{
										g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_maxpledge[m_IDX];
										}
									else
										{
										g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_startbreach[m_IDX];
										}
									}
								}
							}break;

						case ecoin_BlockType::ecoin_Block_MaxPledge:
							{
							//update share integer voting score
							g_Wallet->m_vec_score[m_IDX] = f_eGBP_Pledge_amt + (f_ECN_Pledge_amt * g_Wallet->m_Price);

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
							g_Wallet->m_vec_score[m_IDX] = f_eGBP_Pledge_amt + (f_ECN_Pledge_amt * g_Wallet->m_Price);

							//convert scoremax to maxvote
							if(g_Wallet->m_vec_maxpledge[m_IDX] > 0)
								{
								g_Wallet->m_vec_maxvote[m_IDX] = (float)g_Wallet->m_vec_maxpledge[m_IDX];
								}

#ifdef ECOIN_DEBUG_BREAKS
							else
								{

								__debugbreak();
								}
#endif //add debug message
							}break;
						}

					char* g_sharefield_update[6];
					char* g_sharevalueup[6];
					char* f_sharewhere[1];

					for(int f_Count = 0; f_Count < 6; f_Count++)
						{
						g_sharefield_update[f_Count] = (char*)malloc(sizeof(char) * 1024);
						g_sharevalueup[f_Count] = (char*)malloc(sizeof(char) * 1024);
						}

					f_sharewhere[0] = (char*)malloc(sizeof(char) * 1024);

					float f_LargeScoreFLT = g_Wallet->m_vec_score[m_IDX];
					int f_LargeScoreINT = 0;

					if(f_LargeScoreFLT < (float)INT_MAX)
						{
						f_LargeScoreINT = (int)f_LargeScoreFLT;
						}
					else
						{
						f_LargeScoreINT = INT_MAX;
						}

					//convert ADMAX to scoreand maxvote
					ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, f_LargeScoreINT);
					ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, f_LargeScoreFLT);
					ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, ECOIN_REWARD_ON /*ECN_OPER_REWARD*/ + ECOIN_SCP_INSTANT_BONUS);

					ag_Freshanon<int>(g_Wallet->m_vec_eslid, m_IDX, g_CountLM);
					ag_Freshanon<float>(g_Wallet->m_vec_difficulty, m_IDX, ECOIN_SCP_DEFAULT_BASEDIFF);
					ag_Freshanon<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
					ag_Freshanon<float>(g_Wallet->m_vec_price, m_IDX, g_CurrentSharePrice);
					ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, ECOIN_DEFAULT_JOBBOARDID);
					ag_Freshanon<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);

					::sprintf(g_sharefield_update[0], "jobledger");
					::sprintf(g_sharefield_update[1], "score");
					::sprintf(g_sharefield_update[2], "maxvote");
					::sprintf(g_sharefield_update[3], "mark");
					::sprintf(g_sharefield_update[4], "markfloat");
					::sprintf(g_sharefield_update[5], "jobboardid");
					::sprintf(g_sharevalueup[0], "%s", g_Wallet->m_vec_blockledger[m_IDX].c_str());
					::sprintf(g_sharevalueup[1], "%f", g_Wallet->m_vec_score[m_IDX]);
					::sprintf(g_sharevalueup[2], "%f", g_Wallet->m_vec_maxvote[m_IDX]);
					::sprintf(g_sharevalueup[3], "%i", g_Wallet->m_vec_mark[m_IDX]);
					::sprintf(g_sharevalueup[4], "%f", g_Wallet->m_vec_score[m_IDX]);
					::sprintf(g_sharevalueup[5], "%i", g_Wallet->m_vec_jobboardid[m_IDX]);

					::sprintf(f_sharewhere[0], "id = %i", g_Wallet->m_my_pledge_shareID);

					g_SafeL[0]->Update("share", (const char **)g_sharefield_update, (const char **)g_sharevalueup, 6, f_sharewhere[0], false, false);

					for(int f_Count = 0; f_Count < 6; f_Count++)
						{
						free(g_sharefield_update[f_Count]);
						free(g_sharevalueup[f_Count]);
						}

					free(f_sharewhere[0]);

					char* balancequery = ag_ClearChar(1000);
					::sprintf(balancequery, "Call acTopUpPeerBalanceAdvance(%i, %i)", g_Wallet->m_my_pledge_shareID, g_JobID);
					g_SafeL[0]->acSelectCommand(balancequery, 2, false);
					delete balancequery;

					std::shared_ptr<ShareContainerExt> f_PG = Cag->ag_SelectPeerGraphExt(g_JobID, 0, g_ShareID, g_CurrentShareOffset, g_PEER);

					g_CurrentShareOffset = f_PG->m_espo_ShareOffset;
					g_CurrentShareOffsetMAX = f_PG->m_espo_SharesOnPeerCount;
					g_PEER = f_PG->m_espo_Peer;
					g_PEERCNT = f_PG->m_espo_PeerCount;
					g_PEERMAX = f_PG->m_espo_PeerCount;

					//ECN::VotePledge Submitted.
					ag_StatusLive(f_ref_CurrentPath, "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_VOTE_PLEDGE), g_ShareID, g_PEERCNT);
					f_Ack->m_ECN = 0.0f;
					f_Ack->m_Reward = g_Wallet->m_Reward;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = g_Wallet->GetAdr();
					f_Ack->m_PathOwner = g_Wallet->GetAdr();
					g_Ackent.push_back(f_Ack);

					g_Wallet->acSet_IDX(m_IDX);
					//...
					g_Wallet->acTestForBlock(g_Wallet->m_vec_blocktype[m_IDX], f_Res);
					}
				}
			}
		}
}

void SecondaryAppWindowPageDX::OnClickPledgeClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	//make visible the pledge system
	pledgeStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageDX::OnClickPledgesOn(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(eslmaxpledgetextBox().IsReadOnly() == false)
		{
		eslmaxpledgetextBox().IsReadOnly(true);

		eslpledgeonbutton().Content(box_value(L"Pledges OFF"));

		eslcoderesulttextBlock().Text(L"Stopped Share Pledges...");
		}
	else
		{
		eslmaxpledgetextBox().IsReadOnly(false);

		eslpledgeonbutton().Content(box_value(L"Pledges ON"));

		eslcoderesulttextBlock().Text(L"Block Pledges Initialized");
		}
}

void SecondaryAppWindowPageDX::acRefreshJob(void)
{
	if(m_IDX < g_Wallet->m_vec_scoremax.size())
		{
		char* f_CharJob = ag_ClearChar(256);
		sprintf(f_CharJob, "%f", g_Wallet->m_vec_scoremax[m_IDX]);

		eslscoremaxtextBox().Text(StrUsingStr(f_CharJob));

		delete f_CharJob;

		f_CharJob = ag_ClearChar(256);
		sprintf(f_CharJob, "%.8f", g_Wallet->m_vec_markmax[m_IDX]);

		eslmarkmaxtextBox().Text(StrUsingStr(f_CharJob));

		delete f_CharJob;

		f_CharJob = ag_ClearChar(256);
		sprintf(f_CharJob, "%.8f", g_Wallet->m_vec_markmin[m_IDX]);

		eslmarkmintextBox().Text(StrUsingStr(f_CharJob));

		delete f_CharJob;
		}

	acRefreshJobVar();
}

void SecondaryAppWindowPageDX::acRefreshJobVar(void)
{
	if(m_IDX < g_Wallet->m_vec_jobvar_index.size())
		{
		if(g_Wallet->m_vec_jobvar_current_index[m_IDX] < g_Wallet->m_vec_jobvar_index[m_IDX].size())
			{
			esljobvargrouptextBox().Text(StrUsingStr(g_Wallet->m_vec_jobvar_groupname[m_IDX][g_Wallet->m_vec_jobvar_index[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]]]));
			esljobvarnametextBox().Text(StrUsingStr(g_Wallet->m_vec_jobvar_name[m_IDX][g_Wallet->m_vec_jobvar_index[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]]]));

			char* f_CharVar = ag_ClearChar(256);
			sprintf(f_CharVar, "%.6f", g_Wallet->m_vec_jobvar_value[m_IDX][g_Wallet->m_vec_jobvar_index[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]]]);

			esljobvarvaluetextBox().Text(StrUsingStr(f_CharVar));

			delete f_CharVar;
			}
		else if(g_Wallet->m_vec_jobvar_current_index[m_IDX] == g_Wallet->m_vec_jobvar_index[m_IDX].size())
			{
			std::vector<float> f_vec_jobvar_value;
			std::vector<std::string> f_vec_jobvar_groupname;
			std::vector<std::string> f_vec_jobvar_name;
			std::vector<int> f_vec_jobvar_index;

			int f_Jet = g_Wallet->m_vec_jobvar_current_index[m_IDX];

			g_Wallet->m_vec_jobvar_value[m_IDX].push_back(0.0f);
			g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("DefaultGroup");
			g_Wallet->m_vec_jobvar_name[m_IDX].push_back("DefaultName");
			g_Wallet->m_vec_jobvar_index[m_IDX].push_back(g_Wallet->m_vec_jobvar_index[m_IDX].size());

			esljobvargrouptextBox().Text(StrUsingStr(g_Wallet->m_vec_jobvar_groupname[m_IDX][g_Wallet->m_vec_jobvar_index[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]]]));
			esljobvarnametextBox().Text(StrUsingStr(g_Wallet->m_vec_jobvar_name[m_IDX][g_Wallet->m_vec_jobvar_index[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]]]));

			char* f_CharVar = ag_ClearChar(256);
			sprintf(f_CharVar, "%.6f", g_Wallet->m_vec_jobvar_value[m_IDX][g_Wallet->m_vec_jobvar_index[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]]]);

			esljobvarvaluetextBox().Text(StrUsingStr(f_CharVar));

			delete f_CharVar;
			}
		}
}

void SecondaryAppWindowPageDX::OnClickPreviousJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(m_IDX >= g_Wallet->m_vec_jobvar_index.size())
		{
		std::vector<int> f_vec_index;

		f_vec_index.clear();
		f_vec_index.push_back(0);

		g_Wallet->m_vec_jobvar_index.push_back(f_vec_index);
		g_Wallet->m_vec_jobvar_current_index.push_back(0);
		}
	else
		{
		g_Wallet->m_vec_jobvar_current_index[m_IDX]--;

		if(g_Wallet->m_vec_jobvar_current_index[m_IDX] < 0)
			{
			g_Wallet->m_vec_jobvar_current_index[m_IDX] = 0;
			}
		else
			{
			if(g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] == true)
				{
				g_Wallet->m_vec_jobvar_groupname[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = to_string(esljobvargrouptextBox().Text());
				g_Wallet->m_vec_jobvar_name[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = to_string(esljobvarnametextBox().Text());
				g_Wallet->m_vec_jobvar_value[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = atof(to_string(esljobvarvaluetextBox().Text()).c_str());

				g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = false;
				}
			}
		}

	acRefreshJobVar();
}

void SecondaryAppWindowPageDX::OnClickNextJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(m_IDX >= g_Wallet->m_vec_jobvar_index.size())
		{
		std::vector<int> f_vec_index;

		f_vec_index.clear();
		f_vec_index.push_back(0);

		g_Wallet->m_vec_jobvar_index.push_back(f_vec_index);
		g_Wallet->m_vec_jobvar_current_index.push_back(0);
		}
	else
		{
		g_Wallet->m_vec_jobvar_current_index[m_IDX]++;

		if(g_Wallet->m_vec_jobvar_current_index[m_IDX] > g_Wallet->m_vec_jobvar_index[m_IDX].size())
			{
			g_Wallet->m_vec_jobvar_current_index[m_IDX] = g_Wallet->m_vec_jobvar_index[m_IDX].size();
			}

		if(g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] == true)
			{
			g_Wallet->m_vec_jobvar_groupname[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = to_string(esljobvargrouptextBox().Text());
			g_Wallet->m_vec_jobvar_name[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = to_string(esljobvarnametextBox().Text());
			g_Wallet->m_vec_jobvar_value[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = atof(to_string(esljobvarvaluetextBox().Text()).c_str());

			g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = false;
			}
		}

	acRefreshJobVar();
}

void SecondaryAppWindowPageDX::OnJobVarInvalidateSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
	if(m_IDX < g_Wallet->m_vec_jobvar_index[m_IDX].size())
		{
		g_Wallet->m_vec_jobvar_save[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = true;
		g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = true;
		}
}

void SecondaryAppWindowPageDX::OnClickTypePrefixHelp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageDX::OnGotFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	g_GameFocusOn = false;
}

void SecondaryAppWindowPageDX::OnLostFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	g_GameFocusOn = true;
}

};