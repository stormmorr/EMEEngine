/*

OGL.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include <thread>

#include "SecondaryAppWindowPageDX.h"
#include "SecondaryAppWindowPageOGL.h"
#include "SecondaryAppWindowPageOGL.g.cpp"
#include "SecondaryAppWindowPagePredator.h"

#include <Code/CLS/Target.h>

#include "SimpleRenderer.h"

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

#include "q-keydefinitions.h"

#include "SDL_main.h"

extern int Q_EntryMain(void);
extern int Q_Frame(void);
extern int Q_Clear(void);

using namespace Cube;
using namespace Quantum_Angel;
using namespace ecoin;
using namespace std;

extern std::vector<qtx_Transaction*> g_vec_qtx_Transaction;
extern std::vector<qtx_Transaction*> g_vec_qtx_TransactionNew;

CoreWindow g_CoreWindow{( nullptr )};

QpoVec3d g_PositionLock;

bool g_LOCK_on = false;
int g_LOCK_key = -5;

bool g_EnterPress = false;
bool g_Startup = true;

bool g_PosLockFire = false;

winrt::Windows::Foundation::IAsyncAction m_globalLoopWorker;

bool klmem_a_dwn[QNOMPLAYER];
bool klmem_d_dwn[QNOMPLAYER];
bool klmem_w_dwn[QNOMPLAYER];
bool klmem_s_dwn[QNOMPLAYER];

bool klpress_a_dwn[QNOMPLAYER];
bool klpress_d_dwn[QNOMPLAYER];
bool klpress_w_dwn[QNOMPLAYER];
bool klpress_s_dwn[QNOMPLAYER];

bool klpress_a_pul[QNOMPLAYER];
bool klpress_d_pul[QNOMPLAYER];
bool klpress_w_pul[QNOMPLAYER];
bool klpress_s_pul[QNOMPLAYER];

winrt::Windows::UI::WindowManagement::AppWindow appWindowOgl{ nullptr };

bool txd_on_ogl = false;
int g_TXD_Position_ogl = 0;
bool g_TXD_Preview_ogl = false;

winrt::Windows::System::VirtualKey ag_GetPlayerKey(int f_QIN)
{
	switch(g_Player)
		{
		case 0:
			{
			return (winrt::Windows::System::VirtualKey)f_QIN;
			}break;

		case 1:
			{
			switch(f_QIN)
				{
				case QIN_w:
					{
					return (winrt::Windows::System::VirtualKey)QIN_i;
					}break;

				case QIN_s:
					{
					return (winrt::Windows::System::VirtualKey)QIN_k;
					}break;

				case QIN_a:
					{
					return (winrt::Windows::System::VirtualKey)QIN_j;
					}break;

				case QIN_d:
					{
					return (winrt::Windows::System::VirtualKey)QIN_l;
					}break;

				case QIN_q:
					{
					return (winrt::Windows::System::VirtualKey)QIN_u;
					}break;

				case QIN_e:
					{
					return (winrt::Windows::System::VirtualKey)QIN_o;
					}break;

				case QIN_z:
					{
					return (winrt::Windows::System::VirtualKey)QIN_n;
					}break;

				case QIN_SPACE:
					{
					return (winrt::Windows::System::VirtualKey)QIN_m;
					}break;

				case QIN_SHIFT:
					{
					return (winrt::Windows::System::VirtualKey)QIN_CONTROL;
					}break;

				case QIN_1:
					{
					return (winrt::Windows::System::VirtualKey)QIN_8;
					}break;

				case QIN_2:
					{
					return (winrt::Windows::System::VirtualKey)QIN_9;
					}break;

				case QIN_3:
					{
					return (winrt::Windows::System::VirtualKey)QIN_0;
					}break;
				}
			}break;
		}

	return (winrt::Windows::System::VirtualKey)f_QIN;
}

namespace GVARS
{
	int KEY_PRESS_DOWN(int QIN_code)
	{
		bool keystate = ag_GetKey((int)ag_GetPlayerKey(QIN_code));

		if(keystate) return true;
		else return false;
	}

	int KEY_DOWN_LOCK(int QIN_code)
	{
		bool keystate = ag_GetKey((int)ag_GetPlayerKey(QIN_code));

		if(g_LOCK_on == false)
			{
			if(keystate)
				{
				g_LOCK_key = QIN_code;
				g_LOCK_on = true;
				return true;
				}
			else
				{
				g_LOCK_key = QIN_code;
				g_LOCK_on = false;
				return false;
				}
			}
		else
			{
			if(keystate == true)
				{
				if(g_LOCK_key == QIN_code)
					{
					g_LOCK_key = QIN_code;
					g_LOCK_on = true;
					return false;
					}
				else
					{
					g_LOCK_key = QIN_code;
					g_LOCK_on = true;
					return true;
					}
				}
			else
				{
				g_LOCK_on = false;
				return false;
				}
			}
	}

	int KEY_UP(int QIN_code)
	{
		bool keystate = ag_GetKey((int)ag_GetPlayerKey(QIN_code));

		if (keystate) return false;
		else return true;
	}

	int KEY_DOWN_w(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_w));

		if (keystateA) return true;
		return false;
	}

	int KEY_DOWN_s(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_s));

		if (keystateA) return true;
		return false;
	}

	int KEY_DOWN_a(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_a));

		if (keystateA) return true;
		return false;
	}

	int KEY_DOWN_d(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_d));

		if (keystateA) return true;
		return false;
	}

	int KEY_DOWN_PK(int QIN_code)
	{
		bool keystate = ag_GetKey((int)ag_GetPlayerKey(QIN_code));

		if(keystate) return true;
		else return false;
	}

	int KEY_UP_PK(int QIN_code)
	{
		bool keystate = ag_GetKey((int)ag_GetPlayerKey(QIN_code));

		if (keystate) return false;
		else return true;
	}

	int KEY_DOWN_PK_w(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_w));
		bool keystateC = ag_GetKey((int)ag_GetPlayerKey(QIN_s));
		bool keystateE = ag_GetKey((int)ag_GetPlayerKey(QIN_a));
		bool keystateG = ag_GetKey((int)ag_GetPlayerKey(QIN_d));

		if(keystateA && keystateC)
			{
			return false;
			}

		if(keystateE && keystateG)
			{
			return false;
			}

		if(keystateA) return true;
		if(keystateC) return true;
		if(keystateE) return true;
		if(keystateG) return true;

		return false;
	}

	int KEY_DOWN_PK_s(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_w));
		bool keystateC = ag_GetKey((int)ag_GetPlayerKey(QIN_s));
		bool keystateE = ag_GetKey((int)ag_GetPlayerKey(QIN_a));
		bool keystateG = ag_GetKey((int)ag_GetPlayerKey(QIN_d));

		if(KEY_DOWN_PC_w())
			{
			return false;
			}

		switch(kldirection[g_Player])
			{
			case UN_MOUSE_OUT:
				{
				if((keystateA) && (keystateC)) return true;
				}break;

			case UN_MOUSE_IN:
				{
				if ((keystateA) && (keystateC)) return true;
				}break;

			case UN_MOUSE_IN_RIGHT:
				{
				if((keystateA) && (keystateG) && (keystateC)) return true;
				}break;

			case UN_MOUSE_IN_LEFT:
				{
				if((keystateA) && (keystateE) && (keystateC)) return true;
				}break;

			case UN_MOUSE_RIGHT:
				{
				if((keystateG) && (keystateC)) return true;
				}break;

			case UN_MOUSE_LEFT:
				{
				if((keystateE) && (keystateC)) return true;
				}break;

			case UN_MOUSE_OUT_RIGHT:
				{
				if((keystateC) && (keystateG) && (keystateA)) return true;
				}break;

			case UN_MOUSE_OUT_LEFT:
				{
				if ((keystateC) && (keystateE) && (keystateA)) return true;
				}break;
			}

		return false;
	}

	int KEY_DOWN_PK_a(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_w));
		bool keystateC = ag_GetKey((int)ag_GetPlayerKey(QIN_s));
		bool keystateE = ag_GetKey((int)ag_GetPlayerKey(QIN_a));
		bool keystateG = ag_GetKey((int)ag_GetPlayerKey(QIN_d));

		if(KEY_DOWN_PC_d())
			{
			return false;
			}

		switch(kldirection[g_Player])
			{
			case UN_MOUSE_OUT:
				{
				if ((keystateC) && (keystateG)) return true;
				}break;

			case UN_MOUSE_IN:
				{
				if((keystateE) && (keystateA)) return true;
				}break;

			case UN_MOUSE_IN_RIGHT:
				{
				if((keystateA) && (keystateE)) return true;
				}break;

			case UN_MOUSE_IN_LEFT:
				{
				if((keystateC) && (keystateE)) return true;
				}break;

			case UN_MOUSE_RIGHT:
				{
				if((keystateA)) return true;
				}break;

			case UN_MOUSE_LEFT:
				{
				if((keystateC)) return true;
				}break;

			case UN_MOUSE_OUT_RIGHT:
				{
				if((keystateA) && (keystateG)) return true;
				}break;

			case UN_MOUSE_OUT_LEFT:
				{
				if((keystateC) && (keystateG)) return true;
				}break;
			}

		return false;
	}

	int KEY_DOWN_PK_d(void)
	{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_w));
		bool keystateC = ag_GetKey((int)ag_GetPlayerKey(QIN_s));
		bool keystateE = ag_GetKey((int)ag_GetPlayerKey(QIN_a));
		bool keystateG = ag_GetKey((int)ag_GetPlayerKey(QIN_d));

		if(KEY_DOWN_PC_a())
			{
			return false;
			}

		switch(kldirection[g_Player])
			{
			case UN_MOUSE_OUT:
				{
				if ((keystateC) && (keystateE)) return true;
				}break;

			case UN_MOUSE_IN:
				{
				if((keystateG) && (keystateA)) return true;
				}break;

			case UN_MOUSE_IN_RIGHT:
				{
				if((keystateA) && (keystateG)) return true;
				}break;

			case UN_MOUSE_IN_LEFT:
				{
				if((keystateC) && (keystateG)) return true;
				}break;

			case UN_MOUSE_RIGHT:
				{
				if((keystateC)) return true;
				}break;

			case UN_MOUSE_LEFT:
				{
				if ((keystateA)) return true;
				}break;

			case UN_MOUSE_OUT_RIGHT:
				{
				if((keystateA) && (keystateE)) return true;
				}break;

			case UN_MOUSE_OUT_LEFT:
				{
				if ((keystateC) && (keystateE)) return true;
				}break;
			}

		return false;
		}

	int KEY_DOWN_PC_w(void)
		{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_w));

		if(keystateA) return true;
		else return false;
		}

	int KEY_DOWN_PC_s(void)
		{
		bool keystateC = ag_GetKey((int)ag_GetPlayerKey(QIN_s));

		if(keystateC) return true;
		else return false;
		}

	int KEY_DOWN_PC_a(void)
		{
		bool keystateE = ag_GetKey((int)ag_GetPlayerKey(QIN_a));

		if(keystateE) return true;
		else return false;
		}

	int KEY_DOWN_PC_d(void)
		{
		bool keystateG = ag_GetKey((int)ag_GetPlayerKey(QIN_d));

		if(keystateG) return true;
		else return false;
		}

	int KEY_DOWN_PCX_w(void)
		{
		bool keystateA = ag_GetKey((int)ag_GetPlayerKey(QIN_w));
		bool keystateX = ag_GetKey((int)ag_GetPlayerKey(QIN_s));

		if(keystateA && !keystateX) return true;
		else return false;
		}

	int KEY_DOWN_PCX_s(void)
		{
		bool keystateC = ag_GetKey((int)ag_GetPlayerKey(QIN_s));
		bool keystateX = ag_GetKey((int)ag_GetPlayerKey(QIN_w));

		if(keystateC && !keystateX) return true;
		else return false;
		}

	int KEY_DOWN_PCX_a(void)
		{
		bool keystateE = ag_GetKey((int)ag_GetPlayerKey(QIN_a));
		bool keystateX = ag_GetKey((int)ag_GetPlayerKey(QIN_d));

		if(keystateE && !keystateX) return true;
		else return false;
		}

	int KEY_DOWN_PCX_d(void)
		{
		bool keystateG = ag_GetKey((int)ag_GetPlayerKey(QIN_d));
		bool keystateX = ag_GetKey((int)ag_GetPlayerKey(QIN_a));

		if(keystateG && !keystateX) return true;
		else return false;
		}

};

winrt::Windows::UI::Xaml::Controls::SwapChainPanel g_swapChainPanel_ogl({ nullptr });
winrt::Windows::Foundation::IAsyncAction m_inputLoopWorker_ogl;
winrt::Windows::UI::Core::CoreIndependentInputSource m_coreInput_ogl({ nullptr });
winrt::Windows::UI::Xaml::Controls::Button g_insertinsertbutton_ogl({ nullptr });
winrt::Windows::UI::Xaml::Controls::TextBox g_ConsoleTextBox({ nullptr });

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

namespace winrt::SDKTemplate::implementation
{

SecondaryAppWindowPageOGL::SecondaryAppWindowPageOGL() : m_FirstAll(true)
{
	InitializeComponent();

	std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPageOGL::SecondaryAppWindowPageOGL";

	m_IDX = g_IDX;

	m_Frame_OnCount = false;

	g_IDX++;

	if(g_EngineMode == QEngineMode::QEngine_World)
		{
		loadingtextpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		}

	m_PlayerTeamsInvalid = true;

	m_InterfaceTimer = nullptr;
	m_InputUpTimer = nullptr;

	m_Name = StrUsingStr("...EQGL");

	m_Render_ThreadON = false;
	m_Engine_ThreadON = false;
	m_Interface_ThreadON = false;

	m_Render_ThreadON_Still = false;
	m_Engine_ThreadON_Still = false;

	g_CoreWindow = winrt::Windows::UI::Xaml::Window::Current().CoreWindow();

	g_CoreWindow.KeyDown({ this, &SecondaryAppWindowPageOGL::OnSwapKeyDown });
	g_CoreWindow.KeyUp({ this, &SecondaryAppWindowPageOGL::OnSwapKeyUp });

	LOWTON_STORAGE = 0;
	m_FirstAll = false;
	m_ComboSelectedCom = false;
	m_ComPackageShareID = 0;

	g_insertinsertbutton_ogl = insertinsertbutton();
	g_ConsoleTextBox = messagetextBox();

	g_CoreWindow.VisibilityChanged({ this, &SecondaryAppWindowPageOGL::OnVisibilityChanged });

	winrt::Windows::Graphics::Display::DisplayInformation currentDisplayInformation{ winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView() };

	swapChainPanel().CompositionScaleChanged({ this, &SecondaryAppWindowPageOGL::OnCompositionScaleChanged });
	swapChainPanel().SizeChanged({ this, &SecondaryAppWindowPageOGL::OnSwapChainPanelSizeChanged });

	m_DPI = currentDisplayInformation.LogicalDpi();

	m_logicalWidth = g_CoreWindow.Bounds().Width;
	m_logicalHeight = g_CoreWindow.Bounds().Height;

	m_nativeOrientation = currentDisplayInformation.NativeOrientation();
	m_currentOrientation = currentDisplayInformation.CurrentOrientation();

	DXGI_MODE_ROTATION rotation = ComputeDisplayRotation();

	g_swapChainPanel_ogl = swapChainPanel();

	m_EngineScan = true;

	//###==- Seed the random number generator -==###//
	g_TimeStamp = GetTickCount64();
	srand(g_TimeStamp);

	Cube::g_RandomSeed.x = 1245.3454;
	Cube::g_RandomSeed.y = 245.3454;
	Cube::g_RandomSeed.z = 45.3454;

	//###- Initialisation -###//
	g_Current_ThreadID = -5;

	g_UpdatingMuti.lock();

	// The SwapChainPanel has been created and arranged in the page layout, so EGL can be initialized.
	//CreateRenderSurface();

	g_OpenGLES.MakeCurrent(g_RenderSurface);

	g_UpdatingMuti.unlock();

	g_SimpleRenderer = new SimpleRenderer();

	for(int f_QyCount = 0; f_QyCount < 1024; f_QyCount++)
		{
		g_Qy[f_QyCount] = false;
		}

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		m_ButtonDown[g_Player][0] = false;
		m_ButtonDown[g_Player][1] = false;
		m_ButtonDown[g_Player][2] = false;
		m_ButtonDown[g_Player][3] = false;
		m_ButtonDown[g_Player][4] = false;

		klmem_a_dwn[g_Player] = false;
		klmem_d_dwn[g_Player] = false;
		klmem_w_dwn[g_Player] = false;
		klmem_s_dwn[g_Player] = false;

		klpress_a_dwn[g_Player] = false;
		klpress_d_dwn[g_Player] = false;
		klpress_w_dwn[g_Player] = false;
		klpress_s_dwn[g_Player] = false;

		klpress_a_pul[g_Player] = false;
		klpress_d_pul[g_Player] = false;
		klpress_w_pul[g_Player] = false;
		klpress_s_pul[g_Player] = false;

		kldirection[g_Player] = 0;

		g_MouseMode[g_Player] = UN_MOUSE_PUSH_KEY;

		g_FirstStack[g_Player] = false;
		}

	 //////////////////////
	// QAGE
	g_Player = 0;

	//VX
	ag_StatusLive(f_ref_CurrentPath, "g_VoxelGridManager");
	Cube::g_VoxelGridManager = std::make_shared_reflect<Cube::VoxelGridManager>();

	//WZ
	Cube::g_WarZoneManager = std::make_shared<Cube::WarZone_Manager>();

	//WZ
	Cube::g_WarZoneManager->acPushGridOrigin(BiVector(0.0f));

	 /////////////
	//ShareShop
	ag_StatusLive(f_ref_CurrentPath, "m_ShareShop");
	m_ShareShop = ::std::make_shared_reflect<eshop>(m_IDX);

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

			f_ShareCounting = f_ShareContainer->m_espo_TotalShares;

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

			f_ShareCounting = 0;

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

#if 0
	std::thread f_Thread(&SecondaryAppWindowPageOGL::Frame_OnCount, this);

	f_Thread.detach();

	m_thread = &f_Thread;
#endif

#ifdef ECOIN_STORE_SIM
	bool f_Hok = ConfigureSimulatorAsync(false);

	if(f_Hok == false)
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
		}
#endif

	g_Wallet->m_my_Active_pledge = false;
	g_Wallet->m_my_pledge_shareID = 0;
	g_Wallet->m_pledge_Total = 0.0f;

	  /////////////////
	 //	TAPE RECORD //
	/////////////////
	Cube::seedrand(2);

#if 0
	Cube::TapeOn();

	Cube::TapeOff();
#endif

	  ///////////
	 // ecoin
	//--hesh
#if 0
	for(uint f_Count = 0; f_Count < 10; f_Count++)
		{
		Cube::CubeHESH* f_Hesh = Cube::agGenerateHesh();

		Cube::g_HESH.push_back(f_Hesh);
		}
#endif

	ReadyKeys_Away = 0;

	ac_ReadyPlayerKeys();

	 ///////
	// Q //
	Q_EntryMain();

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
	{
	g_Player = f_CountPlayer;

	playerAV[g_Player]->Xform.Translation.x = AV_START_X + (40.0f * f_CountPlayer);
	playerAV[g_Player]->Xform.Translation.y = AV_START_Y;
	playerAV[g_Player]->Xform.Translation.z = AV_START_Z;
	}

	g_GameOpen = true;

	 /////////////////
	// Load-render //
   //             //
#ifndef QRENDERER_EDITOR
	StartRenderLoop();
#else
	StartEditorRenderLoop();
#endif

	  /////////////////
	 // Load-engine //
	//             //
	if(g_EngineMode == QEngineMode::QEngine_World)
		{
		StartEngineLoop();
		}
	else
		{
		g_QamStatus = QAM_STATUS_LOADED;
		}

	StartInterfaceLoop();

	StartInputUpLoop();

	StartFrameLoop();

	OnRefreshCharSelectListBox();
}

std::byte HexToByteUsingByteManipulation_ogl(std::string s)
{
	std::byte byte_result;

	int hi = s[0] - 65;
	hi = hi + 10 + ((hi >> 31) & 7);

	int lo = s[1] - 65;
	lo = lo + 10 + ((lo >> 31) & 7) & 0x0f;

	byte_result = (std::byte)(lo | hi << 4);

	return byte_result;
}

void SecondaryAppWindowPageOGL::ac_ReadyPlayerKeys(void)
{
	if(ReadyKeys_Away <= 0)
		{
		g_vec_Qy_ok.clear();

#if 1
		g_vec_Qy_ok.push_back(QIN_w);

		g_vec_Qy_ok.push_back(QIN_s);

		g_vec_Qy_ok.push_back(QIN_a);

		g_vec_Qy_ok.push_back(QIN_d);

		g_vec_Qy_ok.push_back(QIN_q);

		g_vec_Qy_ok.push_back(QIN_e);

		g_vec_Qy_ok.push_back(QIN_SPACE);

		g_vec_Qy_ok.push_back(QIN_SHIFT);

		g_vec_Qy_ok.push_back(QIN_1);

		g_vec_Qy_ok.push_back(QIN_2);

		g_vec_Qy_ok.push_back(QIN_3);

		g_vec_Qy_ok.push_back(QIN_z);
#endif

#if 1
		g_vec_Qy_ok.push_back(QIN_i);

		g_vec_Qy_ok.push_back(QIN_k);

		g_vec_Qy_ok.push_back(QIN_j);

		g_vec_Qy_ok.push_back(QIN_l);

		g_vec_Qy_ok.push_back(QIN_u);

		g_vec_Qy_ok.push_back(QIN_o);

		g_vec_Qy_ok.push_back(QIN_m);

		g_vec_Qy_ok.push_back(QIN_CONTROL);

		g_vec_Qy_ok.push_back(QIN_8);

		g_vec_Qy_ok.push_back(QIN_9);

		g_vec_Qy_ok.push_back(QIN_0);

		g_vec_Qy_ok.push_back(QIN_n);

		ReadyKeys_Away = 400;
#endif

#if 1 // utility keys
		g_vec_Qy_ok.push_back(QIN_v);

		g_vec_Qy_ok.push_back(QIN_b);
#endif
		}
	else
		{
		ReadyKeys_Away--;
		}
}

void SecondaryAppWindowPageOGL::acClose_Mouse(void)
{
	mpos = temppos;

	TURN_SPEED = 0;
	UPDOWN_SPEED = 0;
}

void SecondaryAppWindowPageOGL::acPrep_Mouse(void)
{
	if(g_MouseMode[g_Player] <= UN_MOUSE_PUSH_MOUSE)
		{
		bool f_LeftButton = (int)g_CoreWindow.GetAsyncKeyState(Windows::System::VirtualKey::LeftButton) & (int)Windows::UI::Core::CoreVirtualKeyStates::Down;
		bool f_RightButton = (int)g_CoreWindow.GetAsyncKeyState(Windows::System::VirtualKey::RightButton) & (int)Windows::UI::Core::CoreVirtualKeyStates::Down;
		bool f_MidButton = (int)g_CoreWindow.GetAsyncKeyState(Windows::System::VirtualKey::MiddleButton) & (int)Windows::UI::Core::CoreVirtualKeyStates::Down;
		bool f_ScrollButton = (int)g_CoreWindow.GetAsyncKeyState(Windows::System::VirtualKey::Scroll) & (int)Windows::UI::Core::CoreVirtualKeyStates::Down;

		g_CoreWindow.PointerCursor(nullptr);

		if(f_LeftButton)
			{
			if(!m_ButtonDown[g_Player][0] || player[g_Player]->WeaponStatus > 0)
				{
				_->lbutton[g_Player] = 1;

				m_ButtonDown[g_Player][0] = true;
				}
			else
				{
				_->lbutton[g_Player] = 0;
				}
			}
		else
			{
			m_ButtonDown[g_Player][0] = false;

			_->lbutton[g_Player] = 0;
			}

		if(f_RightButton)
			{
			if(!m_ButtonDown[g_Player][1] || player[g_Player]->WeaponStatus > 0)
				{
				_->rbutton[g_Player] = 1;

				m_ButtonDown[g_Player][1] = true;
				}
			else
				{
				_->rbutton[g_Player] = 0;
				}
			}
		else
			{
			m_ButtonDown[g_Player][1] = false;

			_->rbutton[g_Player] = 0;
			}

		if(f_MidButton)
			{
			if(!m_ButtonDown[g_Player][2] || player[g_Player]->WeaponStatus > 0)
				{
				_->mbutton[g_Player] = 1;

				m_ButtonDown[g_Player][2] = true;
				}
			else
				{
				_->mbutton[g_Player] = 0;
				}
			}
		else
			{
			m_ButtonDown[g_Player][2] = false;

			_->mbutton[g_Player] = 0;
			}

		if(f_ScrollButton)
			{
			if(!m_ButtonDown[g_Player][3] || player[g_Player]->WeaponStatus > 0)
				{
				_->mwheelroll[g_Player] = 1;

				m_ButtonDown[g_Player][3] = true;
				}
			else
				{
				_->mwheelroll[g_Player] = 0;
				}
			}
		else
			{
			m_ButtonDown[g_Player][3] = false;

			_->mwheelroll[g_Player] = 0;
			}

		if(g_MouseMode[g_Player] == 0)
			{
			temppos.x = g_CoreWindow.PointerPosition().X;
			temppos.y = g_CoreWindow.PointerPosition().Y;
			}
		else
			{
			mpos.x = g_CoreWindow.PointerPosition().X;
			mpos.y = g_CoreWindow.PointerPosition().Y;
			}

		acKeyLog();
		}
	else if(g_MouseMode[g_Player] == UN_MOUSE_PUSH_KEY)
		{
		bool f_LeftButton = (bool)KEY_DOWN_PK(QIN_1);
		bool f_RightButton = (bool)KEY_DOWN_PK(QIN_2);
		bool f_MidButton = (bool)KEY_DOWN_PK(QIN_3);
		bool f_ScrollButton = (bool)KEY_DOWN_PK(QIN_y);

#if 0
		g_CoreWindow.PointerCursor(nullptr);
#endif

		if(f_LeftButton)
			{
			if(!m_ButtonDown[g_Player][0] || player[g_Player]->WeaponStatus > 0)
				{
				_->lbutton[g_Player] = 1;

				m_ButtonDown[g_Player][0] = true;
				}
			else
				{
				_->lbutton[g_Player] = 0;
				}
			}
		else
			{
			m_ButtonDown[g_Player][0] = false;

			_->lbutton[g_Player] = 0;
			}

		if(f_RightButton)
			{
			if(!m_ButtonDown[g_Player][1] || player[g_Player]->WeaponStatus > 0)
				{
				_->rbutton[g_Player] = 1;

				m_ButtonDown[g_Player][1] = true;
				}
			else
				{
				_->rbutton[g_Player] = 0;
				}
			}
		else
			{
			m_ButtonDown[g_Player][1] = false;

			_->rbutton[g_Player] = 0;
			}

		if(f_MidButton)
			{
			_->mbutton[g_Player] = 1;
			}
		else
			{
			_->mbutton[g_Player] = 0;
			}

		if(f_ScrollButton)
			{
			if(!m_ButtonDown[g_Player][3] || player[g_Player]->WeaponStatus > 0)
				{
				_->mwheelroll[g_Player] = 1;

				m_ButtonDown[g_Player][3] = true;
				}
			else
				{
				_->mwheelroll[g_Player] = 0;
				}
			}
		else
			{
			m_ButtonDown[g_Player][3] = false;

			_->mwheelroll[g_Player] = 0;
			}

		acKeyLogPK();
		}
}

void SecondaryAppWindowPageOGL::acKeyLog(void)
{
	//##### Keylogger for Left To Forward Jink
	if(KEY_DOWN_a())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_a_dwn[g_Player] = true;
		}

	//##### Keylogger for Right To Forward Jink
	if(KEY_DOWN_d())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_d_dwn[g_Player] = true;
		}

	//##### Keylogger for Forward Jinks
	if(KEY_DOWN_w())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_w_dwn[g_Player] = true;
		}	

	//##### Keylogger for Block Jinks
	if(KEY_DOWN_s())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_s_dwn[g_Player] = true;
		}

	//##### Keylogger for Left To Forward Jink - Stage Three
	if(!KEY_DOWN_a() && klmem_a_dwn[g_Player] == true && klmem_w_dwn[g_Player] == true)
		{
		klmem_a_dwn[g_Player] = false;

		player[g_Player]->KL_LTFSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[0]->Xform.Translation); //campos
		}

	//##### Keylogger for Right To Forward Jink - Stage Three
	if(!KEY_DOWN_d() && klmem_d_dwn[g_Player] == true && klmem_w_dwn[g_Player] == true)
		{
		klmem_d_dwn[g_Player] = false;

		player[g_Player]->KL_RTFSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[0]->Xform.Translation); //campos
		}

	//##### Keylogger for Forward To Left OR Right Jink - Stage Three
	if(!KEY_DOWN_w() && klmem_w_dwn[g_Player] == true && klmem_a_dwn[g_Player] == true)
		{
		klmem_w_dwn[g_Player] = false;

		player[g_Player]->KL_FTLSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[0]->Xform.Translation); //campos
		}

	if(!KEY_DOWN_w() && klmem_w_dwn[g_Player] == true && klmem_d_dwn[g_Player] == true)
		{
		klmem_w_dwn[g_Player] = false;

		player[g_Player]->KL_FTRSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[0]->Xform.Translation); //campos
		}

	//##### Keylogger for Right To Forward Jink - Stage Three
	if(!KEY_DOWN_s() && klmem_s_dwn[g_Player] == true && klmem_w_dwn[g_Player] == true)
		{
		klmem_s_dwn[g_Player] = false;

		player[g_Player]->KL_BTFSpecLevel++;

		player[g_Player]->KL_LTFSpecLevel = 0;
		player[g_Player]->KL_RTFSpecLevel = 0;
		player[g_Player]->KL_FTLSpecLevel = 0;
		player[g_Player]->KL_FTRSpecLevel = 0;

		player[g_Player]->KL_BTimer = TIME;

				//'Jink Ready'
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[0]->Xform.Translation); //campos
		}

	if(!KEY_DOWN_w() && klmem_w_dwn[g_Player] == true)
		{
		klmem_w_dwn[g_Player] = false;
		}

	if(!KEY_DOWN_a() && klmem_a_dwn[g_Player] == true)
		{
		klmem_a_dwn[g_Player] = false;
		}

	if(!KEY_DOWN_d() && klmem_d_dwn[g_Player] == true)
		{
		klmem_d_dwn[g_Player] = false;
		}

	if(!KEY_DOWN_s() && klmem_s_dwn[g_Player] == true)
		{
		klmem_s_dwn[g_Player] = false;
		}
}

void SecondaryAppWindowPageOGL::acKeyLogPK(void)
{
	//##### Keylogger for Left To Forward Jink
	if(KEY_DOWN_PC_a())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_a_dwn[g_Player] = true;
		}

	//##### Keylogger for Right To Forward Jink
	if(KEY_DOWN_PC_d())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_d_dwn[g_Player] = true;
		}

	//##### Keylogger for Forward Jinks
	if(KEY_DOWN_PC_w())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_w_dwn[g_Player] = true;
		}	

	//##### Keylogger for Block Jinks
	if(KEY_DOWN_PC_s())
		{
		player[g_Player]->KL_Timer = TIME;
		klmem_s_dwn[g_Player] = true;
		}

	//##### Keylogger for Left To Forward Jink - Stage Three
	if(!KEY_DOWN_PC_a() && klmem_a_dwn[g_Player] == true && klmem_w_dwn[g_Player] == true)
		{
		klmem_a_dwn[g_Player] = false;

		player[g_Player]->KL_LTFSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		if(player[g_Player]->KL_LTFSpecLevel == 1)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_LTFSpecLevel == 2)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_LTFSpecLevel == 3)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		}

	//##### Keylogger for Right To Forward Jink - Stage Three
	if(!KEY_DOWN_PC_d() && klmem_d_dwn[g_Player] == true && klmem_w_dwn[g_Player] == true)
		{
		klmem_d_dwn[g_Player] = false;

		player[g_Player]->KL_RTFSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		if(player[g_Player]->KL_RTFSpecLevel == 1)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_RTFSpecLevel == 2)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_RTFSpecLevel == 3)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		}

	//##### Keylogger for Forward To Left OR Right Jink - Stage Three
	if(!KEY_DOWN_PC_w() && klmem_w_dwn[g_Player] == true && klmem_a_dwn[g_Player] == true)
		{
		klmem_w_dwn[g_Player] = false;

		player[g_Player]->KL_FTLSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		if(player[g_Player]->KL_FTLSpecLevel == 1)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_FTLSpecLevel == 2)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_FTLSpecLevel == 3)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		}

	if(!KEY_DOWN_PC_w() && klmem_w_dwn[g_Player] == true && klmem_d_dwn[g_Player] == true)
		{
		klmem_w_dwn[g_Player] = false;

		player[g_Player]->KL_FTRSpecLevel++;

		player[g_Player]->KL_Timer = TIME;

				//'Jink Ready'
		if(player[g_Player]->KL_FTRSpecLevel == 1)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_FTRSpecLevel == 2)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_FTRSpecLevel == 3)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		}

	//##### Keylogger for Back To Forward Jink - Stage Three
	if(!KEY_DOWN_PC_s() && klmem_s_dwn[g_Player] == true && klmem_w_dwn[g_Player] == true)
		{
		klmem_s_dwn[g_Player] = false;

		player[g_Player]->KL_BTFSpecLevel++;

		player[g_Player]->KL_LTFSpecLevel = 0;
		player[g_Player]->KL_RTFSpecLevel = 0;
		player[g_Player]->KL_FTLSpecLevel = 0;
		player[g_Player]->KL_FTRSpecLevel = 0;

		player[g_Player]->KL_BTimer = TIME;

				//'Jink Ready'
		if(player[g_Player]->KL_BTFSpecLevel == 1)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_BTFSpecLevel == 2)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		else if(player[g_Player]->KL_BTFSpecLevel == 3)
			{
			Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, 1.0f, 1.0f, false, &playerAV[0]->Xform.Translation); //campos
			}
		}

	if(!KEY_DOWN_PC_w() && klmem_w_dwn[g_Player] == true)
		{
		klmem_w_dwn[g_Player] = false;
		}

	if(!KEY_DOWN_PC_a() && klmem_a_dwn[g_Player] == true)
		{
		klmem_a_dwn[g_Player] = false;
		}

	if(!KEY_DOWN_PC_d() && klmem_d_dwn[g_Player] == true)
		{
		klmem_d_dwn[g_Player] = false;
		}

	if(!KEY_DOWN_PC_s() && klmem_s_dwn[g_Player] == true)
		{
		klmem_s_dwn[g_Player] = false;
		}
}

bool SecondaryAppWindowPageOGL::acLowLatentencyInput(void)
{
	// Create a task to register for independent input and begin processing input messages.
	Windows::System::Threading::WorkItemHandler workItemHandler([this](Windows::Foundation::IAsyncAction const& /* action */)
		{
		// The CoreIndependentInputSource will raise pointer events for the specified device types on whichever thread it's created on.
			m_coreInput_ogl = swapChainPanel().CreateCoreIndependentInputSource(
				Windows::UI::Core::CoreInputDeviceTypes::Mouse/* |
				Windows::UI::Core::CoreInputDeviceTypes::Touch |
				Windows::UI::Core::CoreInputDeviceTypes::Pen*/);

		// Register for pointer events, which will be raised on the background thread.
		m_coreInput_ogl.PointerPressed({ this, &SecondaryAppWindowPageOGL::OnSCP_PointerPressed });
		m_coreInput_ogl.PointerMoved({ this, &SecondaryAppWindowPageOGL::OnSCP_PointerMoved });
		m_coreInput_ogl.PointerReleased({ this, &SecondaryAppWindowPageOGL::OnSCP_PointerReleased });

		// Begin processing input messages as they're delivered.
		m_coreInput_ogl.Dispatcher().ProcessEvents(winrt::Windows::UI::Core::CoreProcessEventsOption::ProcessUntilQuit);
		});

	// Run task on a dedicated high priority background thread.
	m_inputLoopWorker_ogl = Windows::System::Threading::ThreadPool::RunAsync(workItemHandler, winrt::Windows::System::Threading::WorkItemPriority::High, winrt::Windows::System::Threading::WorkItemOptions::TimeSliced);

	return true;
}

void SecondaryAppWindowPageOGL::acClick(std::string f_CurrentFunction)
{
	if(m_FirstAll == false)
		{
		ag_Click(f_CurrentFunction);

		Qpo->Sound_Play_Default(Medias->S_Click, 0.6f);
		}
}

void SecondaryAppWindowPageOGL::OnHover(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if(m_FirstAll == false)
		{
		Qpo->Sound_Play_Default(Medias->S_Hover, 0.6f);
		}
}

double atodie(std::string f_String)
{
	return 0.0 + (double)atoi(f_String.c_str());
}

int SecondaryAppWindowPageOGL::ConvertDipsToPixels(float dips)
{
    return int(dips * m_DPI / 96.f + 0.5f);
}

float SecondaryAppWindowPageOGL::ConvertPixelsToDips(int pixels)
{
    return (float(pixels) * 96.f / m_DPI);
}

DXGI_MODE_ROTATION SecondaryAppWindowPageOGL::ComputeDisplayRotation()
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
			switch(m_currentOrientation)
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

void SecondaryAppWindowPageOGL::OnVisibilityChanged(winrt::CoreWindow sender, winrt::VisibilityChangedEventArgs args)
{
	if((args.Visible() == true) && (g_RenderSurface != EGL_NO_SURFACE))
		{
		StartEngineLoop();

#ifndef QRENDERER_EDITOR
		StartRenderLoop();
#else
		StartEditorRenderLoop();
#endif

		StartInterfaceLoop();

		StartInputUpLoop();

		StartFrameLoop();
		}
	else
		{
		StopEngineLoop(); 

		StopRenderLoop();

		StopInterfaceLoop();

		StopInputUpLoop();

		StopFrameLoop();
		}

	EGLint panelWidth = 0;
	EGLint panelHeight = 0;

	//g_OpenGLES.GetSurfaceDimensions(g_RenderSurface, &panelWidth, &panelHeight);

	// Logic to update the scene could go here
	g_SimpleRenderer->UpdateWindowSize(panelWidth, panelHeight);

	g_Width = panelWidth;
	g_Height = panelHeight;
}

#if 0
void SecondaryAppWindowPageOGL::CreateRenderSurface()
{
	if(g_RenderSurface == EGL_NO_SURFACE)
		{
		// The app can configure the the SwapChainPanel which may boost performance.
		// By default, this template uses the default configuration.
		g_RenderSurface = g_OpenGLES.CreateSurface(swapChainPanel(), nullptr, nullptr);
        
		// You can configure the SwapChainPanel to render at a lower resolution and be scaled up to
		// the swapchain panel size. This scaling is often free on mobile hardware.
		//
		// One way to configure the SwapChainPanel is to specify precisely which resolution it should render at.
		// Size custog_RenderSurfaceSize = Size(800, 600);
		// g_RenderSurface = g_OpenGLES.CreateSurface(swapChainPanel, &custog_RenderSurfaceSize, nullptr);
		//
		// Another way is to tell the SwapChainPanel to render at a certain scale factor compared to its size.
		// e.g. if the SwapChainPanel is 1920x1280 then setting a factor of 0.5f will make the app render at 960x640
		// float customResolutionScale = 0.5f;
		// g_RenderSurface = g_OpenGLES.CreateSurface(swapChainPanel, nullptr, &customResolutionScale);
		// 
		}
}
#endif

void SecondaryAppWindowPageOGL::DestroyRenderSurface()
{
	//g_OpenGLES.DestroySurface(g_RenderSurface);

	//g_RenderSurface = EGL_NO_SURFACE;
}

void SecondaryAppWindowPageOGL::RecoverFromLostDevice()
{
	// Stop the render loop, reset OpenGLES, recreate the render surface
	// and start the render loop again to recover from a lost device
	StopEngineLoop();
	StopRenderLoop();
	StopInterfaceLoop();
	StopInputUpLoop();
	StopFrameLoop();

	DestroyRenderSurface();

	g_OpenGLES.Reset();

	//CreateRenderSurface();

	StartEngineLoop();

	//Render loop switch
#ifndef QRENDERER_EDITOR
	StartRenderLoop();
#else
	StartEditorRenderLoop();
#endif

	StartInterfaceLoop();

	StartInputUpLoop();

	StartFrameLoop();
}

void SecondaryAppWindowPageOGL::StartRenderLoop(void)
{
	// If the render loop is already running then do not start another thread.
	if(m_Render_ThreadON_Still == false)
		{
		if(m_Render_ThreadON == false)
			{
			m_Render_ThreadON = true;

			std::thread f_Thread(&SecondaryAppWindowPageOGL::RenderLoop, this);

			f_Thread.detach();
			}
		}
	else
		{
		m_Render_ThreadON = true;
		}
}

void SecondaryAppWindowPageOGL::RenderLoop(void)
{
	m_Render_ThreadON_Still = true;

	while(m_Render_ThreadON == true)
		{
		if(g_WalletOpen)
			{
			ag_Lock_OpenGL(MAIN_RENDER_THREAD_ID);

			EGLint panelWidth = 1920;
			EGLint panelHeight = 1080;
			//g_OpenGLES.GetSurfaceDimensions(g_RenderSurface, &panelWidth, &panelHeight);

			// Logic to update the scene could go here
			g_SimpleRenderer->UpdateWindowSize(panelWidth, panelHeight);

			g_Width = panelWidth;
			g_Height = panelHeight;

			glClearColor(0.5, 0.5, 0.3, 1);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if(g_QamStatus >= QAM_STATUS_LOADED)
				{
				if(g_QcomManager->m_Open == false)
					{
					if(g_GameOpen == true)
						{
						try
							{
							g_VoxelGridManager->Draw(BiVector(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z));
							}
						catch (...)
							{
							int i = 1;
							}

						  /////////
						 // Q
						//
						if(g_QamStatus == QAM_STATUS_STARTED)
							{
							g_QAM->ac_Frame();
							}

						Q_Frame();

						acClose_Mouse();
						}
					}

				   ////////////
				  //
				 // ecoin
				//--HESH
#if 0
				g_SimpleRenderer->DrawHesh(Cube::g_HESH[0]);

				g_SimpleRenderer->DrawPoint(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 100, 3.0f);

				g_VoxelGridManager->Draw(BiVector(0, 0, 0));

				g_VoxelGridManager->DrawCube();
#endif

				g_PosLockFire = false;

				if(playerAV[0]->Xform.Translation.x < g_PositionLock.x - 35.5f ||
					playerAV[0]->Xform.Translation.x > g_PositionLock.x + 35.5f ||
					playerAV[0]->Xform.Translation.y < g_PositionLock.y - 35.5f ||
					playerAV[0]->Xform.Translation.y > g_PositionLock.y + 35.5f ||
					playerAV[0]->Xform.Translation.z < g_PositionLock.z - 35.5f ||
					playerAV[0]->Xform.Translation.z > g_PositionLock.z + 35.5f)
					{
					g_PosLockFire = true;

					g_PositionLock = playerAV[0]->Xform.Translation;
					}

				for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
					{
					if(player[f_CountPlayer]->MoveReactSpeed > 10.0f)
						{
						player[f_CountPlayer]->MoveReactSpeed = 10.0f;
						}
					}

				if(g_EnterPress == false)
					{
					if(KEY_PRESS_DOWN(QIN_v))
						{
						acSpawnAvatar(0, rand() % player[g_Player]->BFO.NomCharacters, rand() % 5, 0, playerAV[0]->Xform.Translation, -1, 0, false);
						g_EnterPress = true;
						}
					else
						{
						g_EnterPress = false;
						}
					}
				else
					{
					if(KEY_PRESS_DOWN(QIN_v))
						{
#if 0
						acSpawnAvatar(0, rand() % player[g_Player]->BFO.NomCharacters, rand() % 5, 0, playerAV[0]->Xform.Translation, -1, 0, false);
#endif

						g_EnterPress = true;
						}
					else
						{
						g_EnterPress = false;
						}
					}

#if 0
				if (_->TimeHole != 0)
					{
					g_Zoom = (_->TimeFactor + 1.0);
					}
				else
					{
					g_Zoom = 1;
					}
#endif

#if 0
				if(KEY_PRESS_DOWN(QIN_m))
					{
					_->TimeHole = 0;
					_->TimeHoleDir = 0;
					_->TimeHole = 0;
					_->TimeInit = 0;
					_->TimeReset = 0;
					_->TimeRotate = 0;
					_->TimePlayerLock = 0;
					_->TimeWaitReset = 0;
					_->JumpTimeInit = 0;
					_->JinkTime = 0;

					_->NomNetEffectControl = 0;
					_->NomPlasma = 0;
					_->NomCharacterDATA = 0;
					_->NomPntSprite = 0;
					_->NomPEFMesh = 0;
					_->NomHSpark = 0;
					_->NomHeal = 0;
					_->NomWorldEntities = 0;
					_->NomMelHit = 0;
					_->NomMelHitPRPR = 0;
					_->NomSEnergy = 0;
					_->NomLEnergy = 0;
					_->NomSEnergyPRPR = 0;
					_->NomLEnergyPRPR = 0;
					_->NomJinks = 0;
					_->NomCart = 0;
					_->NomBullet = 0;
					_->NomBulletPRPR = 0;
					_->NomBulHit = 0;
					_->NomBulHitPRPR = 0;
					_->NomSpikes = 0;
					_->NomPowerFlash = 0;
					_->NomSparks = 0;
					_->NomBlood = 0;
					_->NomExplosions = 0;
					_->NomExplosionsPRPR = 0;
					_->NomCloud = 0;
					_->NomAI = 0;
					_->NomStartP = 0;
					_->NomSpell = 0;
					_->NomDecal = 0;
					_->NomVaporTrails = 0;
					_->NomEnMatBlocks = 0;
					_->NomQObject = 0;
					_->NomBMSentry = 0;
					_->NomBuilding = 0;
					_->NomNetZoneENTITY = 0;
					_->NomNNBots = 0;
					_->NomRealisation = 0;
					_->NomPowerBlade = 0;
					}
#endif

				  /////////
				 // hesh
				//
#if 0
				Cube::CubeHESH* f_Hesh = Cube::agGenerateHesh();

				Cube::g_HESH[0] = f_Hesh;
#endif

				  //////////
				 // Heal //
				//////////
				if(KEY_PRESS_DOWN(QIN_h))
					{
					player[1]->HB_Dead = 0;
					player[1]->HB_Health = player[1]->HB_MaxHealth;
					playerAV[1]->Xform.Translation = playerAV[0]->Xform.Translation;
					}

				// The call to eglSwapBuffers might not be successful (i.e. due to Device Lost)
				// If the call fails, then we must reinitialize EGL and the GL resources.
				g_OpenGLES.SwapBuffers();
				}
			}
		}

	m_Render_ThreadON_Still = false;
}

void SecondaryAppWindowPageOGL::StartEditorRenderLoop(void)
{
	// If the render loop is already running then do not start another thread.
	if(m_Render_ThreadON_Still == false)
		{
		if(m_Render_ThreadON == false)
			{
			m_Render_ThreadON = true;

			std::thread f_Thread(&SecondaryAppWindowPageOGL::EditorRenderLoop, this);

			f_Thread.detach();
			}
		}
	else
		{
		m_Render_ThreadON = true;
		}
}

void SecondaryAppWindowPageOGL::EditorRenderLoop(void)
{
	m_Render_ThreadON_Still = true;

#if 1
	QpoVec3d f_TorchPos(0.0f, 0.0f, 0.0f);
	QpoLight f_PlayerTorch = Qpo->Light_AddtoWorld(f_TorchPos);
	QpoColor f_RGBATorch;

	f_RGBATorch.alpha = 255.0f;
	f_RGBATorch.red = 0.69f * 255.0f;
	f_RGBATorch.green = 0.15f * 255.0f;
	f_RGBATorch.blue = 0.71f * 255.0f;
#endif

	while(m_Render_ThreadON == true)
		{
		if(g_WalletOpen)
			{
			if(g_QamStatus >= QAM_STATUS_LOADED)
				{
				ag_Lock_OpenGL(MAIN_RENDER_THREAD_ID);

				glClearColor(0.5, 0.5, 0.3, 1);
				glEnable(GL_DEPTH_TEST);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				ag_UnLock_OpenGL(MAIN_RENDER_THREAD_ID);

#if 1
				f_TorchPos = playerAV[1]->Xform.Translation;
				f_TorchPos.y += 60.0f;

				Qpo->Light_SetAttr(f_PlayerTorch, &f_TorchPos, &f_RGBATorch, 1500.0f, true);
#endif
			
				if(g_GameOpen == true)
					{
					if(g_QcomManager->m_Open == false)
						{
						ag_Lock_OpenGL(MAIN_RENDER_THREAD_ID);

						g_VoxelGridManager->Draw(BiVector(playerAV[0]->Xform.Translation.x, -playerAV[0]->Xform.Translation.y, -playerAV[0]->Xform.Translation.z));
				
						if(g_QamStatus == QAM_STATUS_STARTED)
							{
							g_QAM->ac_Frame();
							}

						Q_Frame();

						ag_UnLock_OpenGL(MAIN_RENDER_THREAD_ID);

						acClose_Mouse();
						}

#if 0
					if(playerU[0]->m_UpdateDisplay)
						{
						pendingStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);

						if(playerU[0]->m_CharUpdate)
							{	
							pendcharStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
							}
						else
							{
							pendcharStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
							}

						if(playerU[0]->m_ItemUpdate)
							{
							penditemStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
							}
						else
							{
							penditemStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
							}

						if(playerU[0]->m_TXUpdate)
							{
							pendecoinStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
							}
						else
							{
							pendecoinStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
							}

						playerU[0]->m_UpdateDisplay = false;
						}
					else
						{
						pendingStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
						}
#endif
					}

				   ////////////
				  //
				 // ecoin
				//--HESH
#if 0
				g_SimpleRenderer->DrawHesh(Cube::g_HESH[0]);

				g_SimpleRenderer->DrawPoint(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 100, 3.0f);

				g_VoxelGridManager->Draw(BiVector(0, 0, 0));

				g_VoxelGridManager->DrawCube();
#endif

#if 0
				g_PosLockFire = false;

				if (playerAV[0]->Xform.Translation.x < g_PositionLock.x - 35.5f ||
					playerAV[0]->Xform.Translation.x > g_PositionLock.x + 35.5f ||
					playerAV[0]->Xform.Translation.y < g_PositionLock.y - 35.5f ||
					playerAV[0]->Xform.Translation.y > g_PositionLock.y + 35.5f ||
					playerAV[0]->Xform.Translation.z < g_PositionLock.z - 35.5f ||
					playerAV[0]->Xform.Translation.z > g_PositionLock.z + 35.5f)
					{
					g_PosLockFire = true;

					g_PositionLock = playerAV[0]->Xform.Translation;
					}
#endif

				if(g_EnterPress == false)
					{
					if(KEY_PRESS_DOWN(QIN_v))
						{
						ag_Lock_OpenGL(MAIN_RENDER_THREAD_ID);

						int f_Team = player[0]->Team;
						acSpawnAvatar(0, rand() % player[g_Player]->BFO.NomCharacters, rand() % 5, f_Team, playerAV[0]->Xform.Translation, -1, 0, false);
						g_EnterPress = true;

						ag_UnLock_OpenGL(MAIN_RENDER_THREAD_ID);
						}
					else
						{
						if(KEY_PRESS_DOWN(QIN_b))
							{
							ag_Lock_OpenGL(MAIN_RENDER_THREAD_ID);

							int f_Team = player[1]->Team;
							acSpawnAvatar(0, rand() % player[g_Player]->BFO.NomCharacters, rand() % 5, f_Team, playerAV[0]->Xform.Translation, -1, 0, false);
							g_EnterPress = true;

							ag_UnLock_OpenGL(MAIN_RENDER_THREAD_ID);
							}
						}
					}
				else
					{
					if(KEY_PRESS_DOWN(QIN_v))
						{
						g_EnterPress = true;
						}
					else
						{
						if(KEY_PRESS_DOWN(QIN_b))
							{
							g_EnterPress = true;
							}
						else
							{
							g_EnterPress = false;
							}
						}
					}

				if(g_GameOpen)
					{
					for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
						{
						g_Player = f_CountPlayer;

						acPrep_Mouse();
						}

					g_Player = 0;
					}

#if 0
				  /////////
				 // hesh
				//
				if(KEY_PRESS_DOWN(QIN_m))
					{
					Cube::CubeHESH* f_Hesh = Cube::agGenerateHesh();

					Cube::g_HESH[0] = f_Hesh;
					}
#endif

				 ////////
				// Heal
#if 1
				if(KEY_PRESS_DOWN(QIN_h))
					{
					player[1]->HB_Dead = 0;
					player[1]->HB_Health = player[1]->HB_MaxHealth;
					playerAV[1]->Xform.Translation = playerAV[0]->Xform.Translation;
					}
#endif

#if 0
				if(KEY_PRESS_DOWN(QIN_h))
					{
					Q_ItemRef f_ItemREF = Q.CreatePlayerItem(150, 0, 17.25);
					playerU[0]->m_UpdateReady = true;
					playerU[0]->m_ItemUpdate = true;
					}
#endif

				if((g_WalletOpen == true) && (g_GameOpen == true)/* && (g_QamStatus >= QAM_STATUS_LOADED)*/)
					{
					g_QcomManager->acQcom_Frame();
					}

				ag_Lock_OpenGL(MAIN_RENDER_THREAD_ID);

				// The call to eglSwapBuffers might not be successful (i.e. due to Device Lost)
				// If the call fails, then we must reinitialize EGL and the GL resources.
				g_OpenGLES.SwapBuffers();

				ag_UnLock_OpenGL(MAIN_RENDER_THREAD_ID);
				}
			}
		}

	m_Render_ThreadON_Still = false;
}

void SecondaryAppWindowPageOGL::StopRenderLoop()
{
    m_Render_ThreadON = false;
}

void SecondaryAppWindowPageOGL::StartEngineLoop(void)
{
	// If the render loop is already running then do not start another thread.
	if(m_Engine_ThreadON_Still == false)
		{
		if(m_Engine_ThreadON == false)
			{
			m_Engine_ThreadON = true;

#ifndef VOXEL_BUILD_PROGGRESSIVE
			std::thread f_Thread(&SecondaryAppWindowPageOGL::EngineLoop, this);
#else
			std::thread f_Thread(&SecondaryAppWindowPageOGL::EngineLoopManager, this);
#endif

			f_Thread.detach();
			}
		}
	else
		{
		m_Engine_ThreadON = true;
		}
}

fire_and_forget SecondaryAppWindowPageOGL::OnClickOpenGrid(void)
{
	auto lifetime = get_strong();

	// Create a new window
	winrt::Windows::UI::WindowManagement::AppWindow f_appWindowQcom = co_await AppWindow::TryCreateAsync();

#if 0
	// Clean up when the window is closed
	f_appWindowQcom.Closed({ get_weak(), &SecondaryAppWindowPageDX::OnPredatorWindowClosed });
#endif
		
	appWindowFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageDX>());

	// Attach the XAML content to our window
	ElementCompositionPreview::SetAppWindowContent(f_appWindowQcom, appWindowFrame);

	co_await f_appWindowQcom.TryShowAsync();
}

		// Create a background thread.
void SecondaryAppWindowPageOGL::EngineLoop(void)
{
	m_Engine_ThreadON_Still = true;

	if((g_TerrainUpdate == true) || 1)
		{
		g_TerrainUpdate = false;

		if(g_GameOpen)
			{
			Cube::g_VoxelGridManager->Position_Player(BiVector(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z));
			}
		else
			{
			Cube::g_VoxelGridManager->Position_Player(BiVector(0.0f, 0.0f, 0.0f));
			}
		}

	int f_Nom = 0;

	for(int f_Count = 0; f_Count < Cube::g_VoxelGridManager->m_VoxelGridsVector.size(); f_Count++)
		{
		std::shared_ptr<VoxelGrid> f_Grid = Cube::g_VoxelGridManager->m_VoxelGridsVector[f_Count];

		if(f_Grid->m_rebuild == 1)
			{
			if(f_Grid->m_build_count == 0)
				{
				f_Grid->Setup();

				if(g_QAM)
					{
					for(int f_terrCnt = 0; f_terrCnt < g_QAM->m_vec_Terrain.size(); f_terrCnt++)
						{
						qamTerrain* f_Terrain = g_QAM->m_vec_Terrain[f_terrCnt];

						if(f_Terrain->m_QamLevel == g_QAM->m_LevelCurrent)
							{
							f_Terrain->acVoxprint(f_Grid);
							}
						}
					}

				for(int f_Cnt = 0; f_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size(); f_Cnt++)
					{
					std::shared_ptr<Building> f_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_Cnt];

					Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Building(f_Building, f_Grid);

					if(f_Building->acPush_Grid(f_Grid) == false)
						{
						// Array re-order
						for(int f_XY = f_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size() - 1; f_XY++)
							{
							Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY + 1];
							}

						Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.pop_back();
						}
					}

				for(int f_Cnt = 0; f_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.size(); f_Cnt++)
					{
					std::shared_ptr<LightStr> f_LightStr = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_Cnt];
					std::shared_ptr<Building> f_Light_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_Cnt];

					Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Lighting(f_LightStr, f_Light_Building, f_Grid);

					if(f_Light_Building->acPush_Grid(f_Grid) == false)
						{
						// Add Light
						QpoVec3d f_Pos(f_Light_Building->m_Pos.m_X, f_Light_Building->m_Pos.m_Y + ((f_Light_Building->m_Height + 1.5f) * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)), f_Light_Building->m_Pos.m_Z);

						QpoLight f_NewLight = Qpo->Light_AddtoWorld(f_Pos);

						Qpo->Light_SetAttr(f_NewLight, &f_Pos, &f_LightStr->m_RGBA, f_LightStr->m_Radius, true);

						// Array re-order
						for(int f_XY = f_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.size() - 1; f_XY++)
							{
							Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY + 1];
							Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY + 1];
							}

						Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.pop_back();
						Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building.pop_back();
						}
					}
				}

			f_Grid->RebuildMesh(ENGINE_MANAGER_THREAD_ID);
			f_Grid->CompleteMesh(ENGINE_MANAGER_THREAD_ID);

			// Limb Build
			for(int f_Jet = 0; f_Jet < f_Grid->m_vec_VoxelLimb.size(); f_Jet++)
				{
				std::shared_ptr<VoxelLimb> f_Limb = f_Grid->m_vec_VoxelLimb[f_Jet];

				if(f_Limb->m_rebuild == 1)
					{
					f_Limb->RebuildMesh(ENGINE_MANAGER_THREAD_ID);
					f_Limb->CompleteMesh(ENGINE_MANAGER_THREAD_ID);
					f_Limb->SetCreated(ENGINE_MANAGER_THREAD_ID, true);
					}
				}

			f_Grid->SetCreated(ENGINE_MANAGER_THREAD_ID, true);

			f_Nom++;
			}
		}

	while(m_Engine_ThreadON == true)
		{
		if(g_TerrainUpdate || 1)
			{
			g_TerrainUpdate = false;

			if(g_GameOpen)
				{
				g_VoxelGridManager->Position_Player(BiVector(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z));
				}
			else
				{
				g_VoxelGridManager->Position_Player(BiVector(0.0f, 0.0f, 0.0f));
				}
			}

		for(int f_Count = 0; f_Count < g_VoxelGridManager->m_VoxelGridsVector.size(); f_Count++)
			{
			std::shared_ptr<VoxelGrid> f_Grid = Cube::g_VoxelGridManager->m_VoxelGridsVector[f_Count];

			if(f_Grid->m_rebuild == 1)
				{
				if(f_Grid->m_build_count == 0)
					{
					f_Grid->Setup();

					if(g_QAM)
						{
						for(int f_terrCnt = 0; f_terrCnt < g_QAM->m_vec_Terrain.size(); f_terrCnt++)
							{
							qamTerrain* f_Terrain = g_QAM->m_vec_Terrain[f_terrCnt];

							if(f_Terrain->m_QamLevel == g_QAM->m_LevelCurrent)
								{
								f_Terrain->acVoxprint(f_Grid);
								}
							}
						}

					for(int f_Cnt = 0; f_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size(); f_Cnt++)
						{
						std::shared_ptr<Building> f_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_Cnt];

						Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Building(f_Building, f_Grid);

						if(f_Building->acPush_Grid(f_Grid) == false)
							{
							// Array re-order
							for(int f_XY = f_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size() - 1; f_XY++)
								{
								Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY + 1];
								}

							Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.pop_back();
							}
						}

					for(int f_Cnt = 0; f_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.size(); f_Cnt++)
						{
						std::shared_ptr<LightStr> f_LightStr = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_Cnt];
						std::shared_ptr<Building> f_Light_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_Cnt];

						Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Lighting(f_LightStr, f_Light_Building, f_Grid);

						if(f_Light_Building->acPush_Grid(f_Grid) == false)
							{
							// Add Light
							QpoVec3d f_Pos(f_Light_Building->m_Pos.m_X, f_Light_Building->m_Pos.m_Y + ((f_Light_Building->m_Height + 1.5f) * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)), f_Light_Building->m_Pos.m_Z);

							QpoLight f_NewLight = Qpo->Light_AddtoWorld(f_Pos);

							Qpo->Light_SetAttr(f_NewLight, &f_Pos, &f_LightStr->m_RGBA, f_LightStr->m_Radius, true);

							// Array re-order
							for(int f_XY = f_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.size() - 1; f_XY++)
								{
								Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY + 1];
								Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY + 1];
								}

							Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.pop_back();
							Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building.pop_back();
							}
						}
					}

				f_Grid->RebuildMesh(ENGINE_MANAGER_THREAD_ID);
				f_Grid->CompleteMesh(ENGINE_MANAGER_THREAD_ID);

				// Limb Build
				for(int f_Jet = 0; f_Jet < f_Grid->m_vec_VoxelLimb.size(); f_Jet++)
					{
					std::shared_ptr<VoxelLimb> f_Limb = f_Grid->m_vec_VoxelLimb[f_Jet];

					if(f_Limb->m_rebuild == 1)
						{
						f_Limb->RebuildMesh(ENGINE_MANAGER_THREAD_ID);
						f_Limb->CompleteMesh(ENGINE_MANAGER_THREAD_ID);
						f_Limb->SetCreated(ENGINE_MANAGER_THREAD_ID, true);
						}
					}

				f_Grid->SetCreated(ENGINE_MANAGER_THREAD_ID, true);
				}
			else
				{
				// Limb Re-Build
				for(int f_Jet = 0; f_Jet < f_Grid->m_vec_VoxelLimb.size(); f_Jet++)
					{
					std::shared_ptr<VoxelLimb> f_Limb = f_Grid->m_vec_VoxelLimb[f_Jet];

					if(f_Limb->m_rebuild == 1)
						{
						f_Limb->RebuildMesh(ENGINE_MANAGER_THREAD_ID);
						f_Limb->CompleteMesh(ENGINE_MANAGER_THREAD_ID);
						f_Limb->SetCreated(ENGINE_MANAGER_THREAD_ID, true);
						}
					}
				}

			f_Grid->acSimulateCore(1.0f);
			}

		Sleep(5);

		//###- Hold Off Player and AI functions until ground structure built
		if(g_QamStatus < QAM_STATUS_LOADED)
			{
			bool f_Ready = true;

			for(int f_Int = 0; f_Int < g_VoxelGridManager->m_VoxelGridsVector.size(); f_Int++)
				{
				std::shared_ptr<VoxelGrid> f_Grid = Cube::g_VoxelGridManager->m_VoxelGridsVector[f_Int];

				if(f_Grid->m_rebuild != 0)
					{
					f_Ready = false;
					}
				}

			if(f_Ready == true)
				{
				// Register Player Position Placed and Loaded Grids
				g_QamStatus = QAM_STATUS_LOADED;
				}
			}
		}

	m_Engine_ThreadON_Still = false;
}

	// Create a background thread.
void SecondaryAppWindowPageOGL::EngineLoopManager(void)
{
	m_Engine_ThreadON_Still = true;

	// VX Manager Loop
	while(m_Engine_ThreadON == true)
		{
		if(g_TerrainUpdate || 1)
			{
			g_TerrainUpdate = false;

			if(g_GameOpen)
				{
				g_VoxelGridManager->Position_Player(BiVector(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z));
				}
			else
				{
				g_VoxelGridManager->Position_Player(BiVector(0.0f, 0.0f, 0.0f));
				}
			}

		for(int f_Count = 0; f_Count < g_VoxelGridManager->m_VoxelGridsVector.size(); f_Count++)
			{
			std::shared_ptr<VoxelGrid> f_Grid = Cube::g_VoxelGridManager->m_VoxelGridsVector[f_Count];

			if(f_Grid->m_rebuild != 0) //? !Has_Core == false
				{
				bool f_Dupe = false;

				g_VoxelGridManager->m_Muti_EngineWork.lock();

				for(int f_Jet = 0; f_Jet < g_VoxelGridManager->m_vec_EngineWork_Grid.size(); f_Jet++)
					{
					std::shared_ptr<VoxelGrid> f_ChkGrid = Cube::g_VoxelGridManager->m_vec_EngineWork_Grid[f_Jet];

					if(f_ChkGrid->m_UID == f_Grid->m_UID)
						{
						f_Dupe = true;

						f_Jet = g_VoxelGridManager->m_vec_EngineWork_Grid.size();
						}
					}

				if(f_Dupe == false)
					{
					// Secondary Check for already being built
					for(int f_Jet = 0; f_Jet < g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.size(); f_Jet++)
						{
						std::shared_ptr<VoxelGrid> f_ChkGrid = Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid[f_Jet];

						if(f_ChkGrid->m_UID == f_Grid->m_UID)
							{
							f_Dupe = true;

							f_Jet = g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.size();
							}
						}

					if(f_Dupe == false)
						{
						g_VoxelGridManager->m_vec_EngineWork_Grid.push_back(f_Grid);
						g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.push_back(f_Grid);
						}
					}

				g_VoxelGridManager->m_Muti_EngineWork.unlock();
				}
			else
				{
				// Limb Build
				for(int f_Jet = 0; f_Jet < f_Grid->m_vec_VoxelLimb.size(); f_Jet++)
					{
					std::shared_ptr<VoxelLimb> f_Limb = f_Grid->m_vec_VoxelLimb[f_Jet];

					if(f_Limb->m_rebuild == 1)
						{
						bool f_Dupe = false;

						g_VoxelGridManager->m_Muti_EngineWork.lock();

						for(int f_Grf = 0; f_Grf < g_VoxelGridManager->m_vec_EngineWork_Limb.size(); f_Grf++)
							{
							std::shared_ptr<VoxelLimb> f_ChkLimb = Cube::g_VoxelGridManager->m_vec_EngineWork_Limb[f_Grf];

							if(f_ChkLimb->m_UID == f_Limb->m_UID)
								{
								f_Dupe = true;

								f_Grf = g_VoxelGridManager->m_vec_EngineWork_Limb.size();
								}
							}

						if(f_Dupe == false)
							{
							// Secondary Check for already being built
							for(int f_Grf = 0; f_Grf < g_VoxelGridManager->m_vec_EngineWork_WIP_Limb.size(); f_Grf++)
								{
								std::shared_ptr<VoxelLimb> f_ChkLimb = Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Limb[f_Grf];

								if(f_ChkLimb->m_UID == f_Limb->m_UID)
									{
									f_Dupe = true;

									f_Grf = g_VoxelGridManager->m_vec_EngineWork_WIP_Limb.size();
									}
								}

							if(f_Dupe == false)
								{
								// Second test stage 'Grid already under work'
								for(int f_Grf = 0; f_Grf < g_VoxelGridManager->m_vec_EngineWork_Grid.size(); f_Grf++)
									{
									std::shared_ptr<VoxelGrid> f_ChkGrid = Cube::g_VoxelGridManager->m_vec_EngineWork_Grid[f_Grf];

									if(f_ChkGrid->m_UID == f_Limb->m_GridRef->m_UID);
										{
										f_Dupe = true;

										f_Grf = g_VoxelGridManager->m_vec_EngineWork_Grid.size();
										}
									}

								// Still original workload
								if(f_Dupe == false)
									{
									// Secondary Check for already being built
									for(int f_Grf = 0; f_Grf < g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.size(); f_Grf++)
										{
										std::shared_ptr<VoxelGrid> f_ChkGrid = Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid[f_Grf];

										if(f_ChkGrid->m_UID == f_Limb->m_GridRef->m_UID)
											{
											f_Dupe = true;

											f_Grf = g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.size();
											}
										}

									if(f_Dupe == false)
										{
#ifdef VOXEL_LIMB_ON
										g_VoxelGridManager->m_vec_EngineWork_Limb.push_back(f_Limb);
										g_VoxelGridManager->m_vec_EngineWork_WIP_Limb.push_back(f_Limb);
#else
										f_Limb->m_created = true;
										f_Limb->m_build_count = 1;
										f_Limb->m_rebuild = 0;
										f_Limb->m_full = false;
										f_Limb->m_emptyVoxelGrid = true;
#endif
										}
									}
								}
							}

						g_VoxelGridManager->m_Muti_EngineWork.unlock();
						}
					}
				}

			if(f_Grid->m_Has_Core == true)
				{
				f_Grid->acSimulateCore(1.0f);
				}
			}

		//Lock Aquire Work Count
		g_VoxelGridManager->m_Muti_EngineWork.lock();

		int f_NomUpgrades_thread = g_VoxelGridManager->m_vec_EngineWork_Grid.size() + g_VoxelGridManager->m_vec_EngineWork_Limb.size();
		
		int f_ThreadCount = g_VoxelGridManager->m_EngineWork_ThreadCount;

		g_VoxelGridManager->m_Muti_EngineWork.unlock();

		if(f_NomUpgrades_thread > f_ThreadCount)
			{
			f_NomUpgrades_thread = ag_max(f_NomUpgrades_thread, VOXEL_ENGINE_THREAD_COUNT);
			}
		else
			{
			f_NomUpgrades_thread = ag_min(f_NomUpgrades_thread, 0);
			}

		// +++
		while(g_VoxelGridManager->m_EngineWork_ThreadCount < f_NomUpgrades_thread)
			{
			std::thread f_Thread(&SecondaryAppWindowPageOGL::EngineFrame, this);

			f_Thread.detach();

			//inc++//dec--
			g_VoxelGridManager->m_EngineWork_ThreadCount++;
			}

		//###- Hold Off Player and AI functions until ground structure built
		if(g_QamStatus < QAM_STATUS_LOADED)
			{
			bool f_Ready = true;

			for(int f_Int = 0; f_Int < g_VoxelGridManager->m_VoxelGridsVector.size(); f_Int++)
				{
				std::shared_ptr<VoxelGrid> f_Grid = Cube::g_VoxelGridManager->m_VoxelGridsVector[f_Int];

				if(f_Grid->m_rebuild == 1)
					{
					if(f_Grid->m_emptyVoxelGrid == false)
						{
						f_Ready = false;

						f_Int = g_VoxelGridManager->m_VoxelGridsVector.size();
						}
					}
				}

			if(f_Ready == true)
				{
				Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

				//First Worker Thread Tests
				for(int f_Jeh = 0; f_Jeh < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_Jeh++)
					{
					std::shared_ptr<Q_Building_Thread> f_Thread = Cube::g_WarZoneManager->m_vec_WorkThread[f_Jeh];
					
					for(int f_JB = 0; f_JB < f_Thread->m_vec_WorkComp->size(); f_JB++)
						{
						if(f_Thread->m_vec_WorkComp->at(f_JB) == 0)
							{
							f_Ready = false;

							f_JB = f_Thread->m_vec_WorkComp->size();
							f_Jeh = Cube::g_WarZoneManager->m_vec_WorkThread.size();
							}
						}
					}

				if(f_Ready == true)
					{
					for(int f_Jeh = 0; f_Jeh < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_Jeh++)
						{
						std::shared_ptr<Q_Building_Thread> f_Thread = Cube::g_WarZoneManager->m_vec_WorkThread[f_Jeh];

						if(f_Thread->m_vec_WorkComp->size() > 0)
							{
							if(f_Thread->m_vec_WorkComp->at(f_Thread->m_vec_WorkComp->size() - 1) != -5)
								{
								f_Ready = false;

								f_Jeh = Cube::g_WarZoneManager->m_vec_WorkThread.size();
								}
							}
						}

					if(f_Ready == true)
						{
						// Register Player Position Placed and Loaded Grids
						g_QamStatus = QAM_STATUS_LOADED;

						g_VoxelGridManager->acInitialiseReflection();
						}
					}

				Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
				}
			}
		}

	m_Engine_ThreadON_Still = false;
}

// Create a background thread.
void SecondaryAppWindowPageOGL::EngineFrame(void)
{
	int f_WorkSig = 0;
	bool f_ScanBuilding = true;
	int f_Engine_ThreadIndex = -1;

	std::shared_ptr<std::vector<int>> f_vec_WorkStatus = nullptr;

	std::shared_ptr<Q_Building_Thread> f_Worker_Thread = nullptr;

	Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

	for(int f_JI = 0; f_JI < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_JI++)
		{
		if(Cube::g_WarZoneManager->m_vec_WorkThread[f_JI]->m_Active == false)
			{
			f_Engine_ThreadIndex = Cube::g_VoxelGridManager->m_vec_running_EngineThread_IDX[f_JI];

			f_Worker_Thread = Cube::g_WarZoneManager->m_vec_WorkThread[f_JI];

			f_Worker_Thread->ac_reset_Clear();
				
			f_vec_WorkStatus = f_Worker_Thread->m_vec_WorkComp;

			f_JI = Cube::g_WarZoneManager->m_vec_WorkThread.size();
			}
		}

	if(f_Engine_ThreadIndex < 0)
		{
		f_Engine_ThreadIndex = g_Engine_ThreadCount;

		g_Engine_ThreadCount++;

		Cube::g_VoxelGridManager->m_vec_running_EngineThread_IDX.push_back(f_Engine_ThreadIndex);

		f_vec_WorkStatus = std::make_shared<std::vector<int>>();

		f_Worker_Thread = std::make_shared<Q_Building_Thread>();

		f_Worker_Thread->ac_EntryKey(f_vec_WorkStatus);

		f_Worker_Thread->ac_reset_Clear();

		Cube::g_WarZoneManager->m_vec_WorkThread.push_back(f_Worker_Thread);
		}

	Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

	bool f_FrameScan = true;

	while((m_EngineScan == true) && (f_FrameScan == true))
		{
		 ///////////////////
		// Checking Work //
		Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

		int f_Grid_WorkSize = Cube::g_VoxelGridManager->m_vec_EngineWork_Grid.size();
		int f_Limb_WorkSize = Cube::g_VoxelGridManager->m_vec_EngineWork_Limb.size();

		Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

		if(f_Grid_WorkSize > 0)
			{
			Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

			std::shared_ptr<VoxelGrid> f_WorkGrid = Cube::g_VoxelGridManager->m_vec_EngineWork_Grid[0];

			for(int f_XY = 0; f_XY < Cube::g_VoxelGridManager->m_vec_EngineWork_Grid.size() - 1; f_XY++)
				{
				Cube::g_VoxelGridManager->m_vec_EngineWork_Grid[f_XY] = Cube::g_VoxelGridManager->m_vec_EngineWork_Grid[f_XY + 1];
				}

			Cube::g_VoxelGridManager->m_vec_EngineWork_Grid.pop_back();

			Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

			if((f_WorkGrid->m_rebuild == 1) && (f_WorkGrid->m_Has_Core == true))
				{
				if(f_WorkGrid->m_build_count == 0)
					{
					Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

					//Generate Proper Count Start Position // size() reentrant????
					f_Worker_Thread->m_Cnt = f_Engine_ThreadIndex * (Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size() / VOXEL_ENGINE_THREAD_COUNT);

					if(f_Worker_Thread->m_Cnt >= Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size())
						{
						f_Worker_Thread->m_Cnt -= Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size();
						}

					Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

					Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

					f_Worker_Thread->ac_reset_Clear();

					while(f_vec_WorkStatus->size() < f_Worker_Thread->m_Cnt)
						{
						f_vec_WorkStatus->push_back(0);
						}

					Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

					f_WorkGrid->Setup();

					if(g_QAM)
						{
						for(int f_terrCnt = 0; f_terrCnt < g_QAM->m_vec_Terrain.size(); f_terrCnt++)
							{
							qamTerrain* f_Terrain = g_QAM->m_vec_Terrain[f_terrCnt];

							if(f_Terrain->m_QamLevel == g_QAM->m_LevelCurrent)
								{
								f_Terrain->acVoxprint(f_WorkGrid);
								}
							}
						}

					if(f_WorkGrid->m_full == false)
						{
						f_Worker_Thread->m_Cnt = 0;
						f_WorkSig = 0;
						f_ScanBuilding = true;

						Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

						if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size() <= 0)
							{
							f_ScanBuilding = false;
							}

						Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

						while(f_ScanBuilding == true)
							{
							Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

							if(f_Worker_Thread->m_Cnt < f_vec_WorkStatus->size())
								{
								if(f_vec_WorkStatus->at(f_Worker_Thread->m_Cnt) == 0)
									{
									Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
							
									Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

									if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Worker_Thread->m_Cnt] == 0)
										{
										Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Worker_Thread->m_Cnt] = 1;

										Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

										std::shared_ptr<Building> f_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_Worker_Thread->m_Cnt];

										Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Building(f_Building, f_WorkGrid);

										if(f_Building->acPush_Grid(f_WorkGrid) == false)
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

											// Array re-order
											for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size() - 1; f_XY++)
												{
												Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY + 1];
												Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_XY + 1];
												}

											Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.pop_back();
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.pop_back();

											Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

											Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

											for(int f_J = 0; f_J < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_J++)
												{
												std::shared_ptr<Q_Building_Thread> f_ResultThread = Cube::g_WarZoneManager->m_vec_WorkThread[f_J];

												if(f_ResultThread->m_Active == true)
													{
													if(f_ResultThread->m_BuildingNM == true)
														{
														if(f_ResultThread->m_Cnt >= f_Worker_Thread->m_Cnt)
															{
															f_ResultThread->m_Cnt--;
															}

														std::shared_ptr<std::vector<int>> f_Vector = f_ResultThread->m_vec_WorkComp;

														//all sizes 1 off
														if(f_Worker_Thread->m_Cnt < f_Vector->size())
															{
															for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < f_Vector->size() - 1; f_XY++)
																{
																f_Vector->at(f_XY) = f_Vector->at(f_XY + 1);
																}

															f_Vector->pop_back();
															}
														}
													}
												}

											Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

											f_WorkSig = 2; //pop
											}
										else
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

											if(f_Worker_Thread->m_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size())
												{
												Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Worker_Thread->m_Cnt] = 0;
												}

											Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

											f_WorkSig = 1;
											}
										}
									else
										{
										Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

										f_WorkSig = 0;
										}
									} //END Skipped previously
								else
									{
									Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

									f_WorkSig = 3; //remaining appeasement
									}
								}
							else //END Work.size() > complete
								{
								Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

								Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

								if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Worker_Thread->m_Cnt] == 0)
									{
									Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Worker_Thread->m_Cnt] = 1;

									Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

									std::shared_ptr<Building> f_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_Worker_Thread->m_Cnt];

									Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Building(f_Building, f_WorkGrid);

									if(f_Building->acPush_Grid(f_WorkGrid) == false)
										{
										Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

										// Array re-order
										for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.size() - 1; f_XY++)
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building[f_XY + 1];
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_XY + 1];
											}

										Cube::g_WarZoneManager->m_current_WarZone->m_vec_Building.pop_back();
										Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.pop_back();

										Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

										Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

										for(int f_J = 0; f_J < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_J++)
											{
											std::shared_ptr<Q_Building_Thread> f_ResultThread = Cube::g_WarZoneManager->m_vec_WorkThread[f_J];

											if(f_ResultThread->m_Active == true)
												{
												if(f_ResultThread->m_BuildingNM == true)
													{
													if(f_ResultThread->m_Cnt >= f_Worker_Thread->m_Cnt)
														{
														f_ResultThread->m_Cnt--;
														}

													std::shared_ptr<std::vector<int>> f_Vector = f_ResultThread->m_vec_WorkComp;

													//all sizes 1 off
													if(f_Worker_Thread->m_Cnt < f_Vector->size())
														{
														for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < f_Vector->size() - 1; f_XY++)
															{
															f_Vector->at(f_XY) = f_Vector->at(f_XY + 1);
															}

														f_Vector->pop_back();
														}
													}
												}
											}

										Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

										f_WorkSig = 2; //pop
										}
									else
										{
										Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

										if(f_Worker_Thread->m_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size())
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Worker_Thread->m_Cnt] = 0;
											}

										Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

										f_WorkSig = 1;
										}
									}
								else
									{
									Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();

									f_WorkSig = 0;
									}
								} //END New Building

							if(f_WorkSig < 2)
								{
								Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

								if(f_Worker_Thread->m_Cnt < f_vec_WorkStatus->size())
									{
									f_vec_WorkStatus->at(f_Worker_Thread->m_Cnt) = f_WorkSig;
									}
								else
									{
									f_vec_WorkStatus->push_back(f_WorkSig);
									}

								Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
								}

							Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();
							Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

							if(f_vec_WorkStatus->size() >= Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size())
								{
								f_ScanBuilding = false;

								for(int f_Flp = 0; f_Flp < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size(); f_Flp++)
									{
									if(f_vec_WorkStatus->at(f_Flp) == 0)
										{
										f_ScanBuilding = true;

										f_Flp = Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size();
										}
									}
								}

							Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();
							Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

							f_Worker_Thread->m_Cnt++;

							Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.lock();

							// Load Next Cycle
							if(f_Worker_Thread->m_Cnt >= Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size())
								{ // Detect No Work
								if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size() <= 0)
									{
									f_ScanBuilding = false;
									}

								f_Worker_Thread->m_Cnt = 0;

								//Work Status Reset
								for(int f_Kl = 0; f_Kl < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building.size(); f_Kl++)
									{
									if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Kl] == 1)
										{
										bool f_On = false;

										for(int f_J = 0; f_J < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_J++)
											{
											if(f_Engine_ThreadIndex != f_J)
												{
												std::shared_ptr<Q_Building_Thread> f_ResultThread = Cube::g_WarZoneManager->m_vec_WorkThread[f_J];

												if(f_ResultThread->m_Active == true)
													{
													if(f_ResultThread->m_BuildingNM == true)
														{
														if(f_ResultThread->m_Cnt == f_Kl)
															{
															f_On = true;
															}
														}
													}
												}
											}

										if(f_On == false)
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Building[f_Kl] = 0;
											}
										}
									}
								}
						
							Cube::g_WarZoneManager->m_current_WarZone->m_BuildingMuti.unlock();
							}

						////RESET
						f_WorkSig = 0;

						Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

						//Generate Proper Count Start Position // size() reentrant????
						f_Worker_Thread->m_Cnt = f_Engine_ThreadIndex * (Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building.size() / VOXEL_ENGINE_THREAD_COUNT);

						if(f_Worker_Thread->m_Cnt >= Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building.size())
							{
							f_Worker_Thread->m_Cnt -= Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building.size();
							}

						Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

						Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

						f_Worker_Thread->ac_light_Clear();

						while(f_vec_WorkStatus->size() < f_Worker_Thread->m_Cnt)
							{
							f_vec_WorkStatus->push_back(0);
							}

						Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

						f_ScanBuilding = true;

						Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

						if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size() <= 0)
							{
							f_ScanBuilding = false;
							}

						Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

						while(f_ScanBuilding == true)
							{
							Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

							if(f_Worker_Thread->m_Cnt < f_vec_WorkStatus->size())
								{
								if(f_vec_WorkStatus->at(f_Worker_Thread->m_Cnt) == 0)
									{
									Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

									Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

									if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Worker_Thread->m_Cnt] == 0)
										{
										Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Worker_Thread->m_Cnt] = 1;

										Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

										std::shared_ptr<LightStr> f_LightStr = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_Worker_Thread->m_Cnt];
										std::shared_ptr<Building> f_Light_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_Worker_Thread->m_Cnt];

										Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Lighting(f_LightStr, f_Light_Building, f_WorkGrid);

										if(f_Light_Building->acPush_Grid(f_WorkGrid) == false)
											{
											// Add Light
											QpoVec3d f_Pos(f_Light_Building->m_Pos.m_X, f_Light_Building->m_Pos.m_Y + ((f_Light_Building->m_Height + 1.5f) * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)), f_Light_Building->m_Pos.m_Z * -1.0f);

											QpoLight f_NewLight = Qpo->Light_AddtoWorld(f_Pos);

											Qpo->Light_SetAttr(f_NewLight, &f_Pos, &f_LightStr->m_RGBA, f_LightStr->m_Radius, true);

											Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

											// Array re-order
											for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.size() - 1; f_XY++)
												{
												Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY + 1];
												Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY + 1];
												Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_XY + 1];
												}

											Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.pop_back();
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building.pop_back();
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.pop_back();

											Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

											Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

											for(int f_J = 0; f_J < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_J++)
												{
												std::shared_ptr<Q_Building_Thread> f_ResultThread = Cube::g_WarZoneManager->m_vec_WorkThread[f_J];

												if(f_ResultThread->m_Active == true)
													{
													if(f_ResultThread->m_BuildingNM == false)
														{
														if(f_ResultThread->m_Cnt >= f_Worker_Thread->m_Cnt)
															{
															f_ResultThread->m_Cnt--;
															}

														std::shared_ptr<std::vector<int>> f_Vector = f_ResultThread->m_vec_WorkComp;

														//all sizes 1 off
														if(f_Worker_Thread->m_Cnt < f_Vector->size())
															{
															for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < f_Vector->size() - 1; f_XY++)
																{
																f_Vector->at(f_XY) = f_Vector->at(f_XY + 1);
																}

															f_Vector->pop_back();
															}
														}
													}
												}

											Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

											f_WorkSig = 2; //pop
											}
										else
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

											if(f_Worker_Thread->m_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size())
												{
												Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Worker_Thread->m_Cnt] = 0;
												}
										
											Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

											f_WorkSig = 1;
											}
										}
									else
										{
										Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

										f_WorkSig = 0;
										}
									}
								else
									{
									Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

									f_WorkSig = 3; //remaining appeasement
									}
								}
							else
								{
								Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

								Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

								if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Worker_Thread->m_Cnt] == 0)
									{
									Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Worker_Thread->m_Cnt] = 1;

									Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

									std::shared_ptr<LightStr> f_LightStr = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_Worker_Thread->m_Cnt];
									std::shared_ptr<Building> f_Light_Building = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_Worker_Thread->m_Cnt];

									Cube::g_VoxelGridManager->Make_Gen_Rand_Small_Lighting(f_LightStr, f_Light_Building, f_WorkGrid);

									if(f_Light_Building->acPush_Grid(f_WorkGrid) == false)
										{
										// Add Light
										QpoVec3d f_Pos(f_Light_Building->m_Pos.m_X, f_Light_Building->m_Pos.m_Y + ((f_Light_Building->m_Height + 1.5f) * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)), f_Light_Building->m_Pos.m_Z * -1.0f);

										QpoLight f_NewLight = Qpo->Light_AddtoWorld(f_Pos);

										Qpo->Light_SetAttr(f_NewLight, &f_Pos, &f_LightStr->m_RGBA, f_LightStr->m_Radius, true);

										Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

										// Array re-order
										for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.size() - 1; f_XY++)
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr[f_XY + 1];
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building[f_XY + 1];
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_XY] = Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_XY + 1];
											}

										Cube::g_WarZoneManager->m_current_WarZone->m_vec_LightStr.pop_back();
										Cube::g_WarZoneManager->m_current_WarZone->m_vec_Light_Building.pop_back();
										Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.pop_back();

										Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

										Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

										for(int f_J = 0; f_J < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_J++)
											{
											std::shared_ptr<Q_Building_Thread> f_ResultThread = Cube::g_WarZoneManager->m_vec_WorkThread[f_J];

											if(f_ResultThread->m_Active == true)
												{
												if(f_ResultThread->m_BuildingNM == false)
													{
													if(f_ResultThread->m_Cnt >= f_Worker_Thread->m_Cnt)
														{
														f_ResultThread->m_Cnt--;
														}

													std::shared_ptr<std::vector<int>> f_Vector = f_ResultThread->m_vec_WorkComp;

													//all sizes 1 off
													if(f_Worker_Thread->m_Cnt < f_Vector->size())
														{
														for(int f_XY = f_Worker_Thread->m_Cnt; f_XY < f_Vector->size() - 1; f_XY++)
															{
															f_Vector->at(f_XY) = f_Vector->at(f_XY + 1);
															}

														f_Vector->pop_back();
														}
													}
												}
											}

										Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

										f_WorkSig = 2; //popped
										}
									else
										{
										Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

										if(f_Worker_Thread->m_Cnt < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size())
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Worker_Thread->m_Cnt] = 0;
											}

										Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

										f_WorkSig = 1;
										}
									}
								else
									{
									Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();

									f_WorkSig = 0;
									}
								}

							if(f_WorkSig < 2)
								{
								Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

								if(f_Worker_Thread->m_Cnt < f_vec_WorkStatus->size())
									{
									f_vec_WorkStatus->at(f_Worker_Thread->m_Cnt) = f_WorkSig;
									}
								else
									{
									f_vec_WorkStatus->push_back(f_WorkSig);
									}

								Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
								}

							Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();
							Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

							if(f_vec_WorkStatus->size() >= Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size())
								{
								f_ScanBuilding = false;

								for(int f_Flp = 0; f_Flp < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size(); f_Flp++)
									{
									if(f_vec_WorkStatus->at(f_Flp) == 0)
										{
										f_ScanBuilding = true;
										}
									}
								}

							Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();
							Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

							f_Worker_Thread->m_Cnt++;

							Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.lock();

							// Load Next Cycle
							if(f_Worker_Thread->m_Cnt >= Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size())
								{ // Detect No Work
								if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size() <= 0)
									{
									f_ScanBuilding = false;
									}

								f_Worker_Thread->m_Cnt = 0;

								//Work Status Reset
								for(int f_Kl = 0; f_Kl < Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building.size(); f_Kl++)
									{
									if(Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Kl] == 1)
										{
										bool f_On = false;

										for(int f_J = 0; f_J < Cube::g_WarZoneManager->m_vec_WorkThread.size(); f_J++)
											{
											if(f_Engine_ThreadIndex != f_J)
												{
												std::shared_ptr<Q_Building_Thread> f_ResultThread = Cube::g_WarZoneManager->m_vec_WorkThread[f_J];

												if(f_ResultThread->m_Active == true)
													{
													if(f_ResultThread->m_BuildingNM == true)
														{
														if(f_ResultThread->m_Cnt == f_Kl)
															{
															f_On = true;
															}
														}
													}
												}
											}

										if(f_On == false)
											{
											Cube::g_WarZoneManager->m_current_WarZone->m_vec_WorkStatus_Light_Building[f_Kl] = 0;
											}
										}
									}
								}

							Cube::g_WarZoneManager->m_current_WarZone->m_LightBuildingMuti.unlock();
							}
						}
					}

				f_WorkGrid->RebuildMesh(f_Engine_ThreadIndex);
				f_WorkGrid->CompleteMesh(f_Engine_ThreadIndex);

				// !Full Limb Build
				if(f_WorkGrid->m_full == false)
					{
					for(int f_Jet = 0; f_Jet < f_WorkGrid->m_vec_VoxelLimb.size(); f_Jet++)
						{
						std::shared_ptr<VoxelLimb> f_Limb = f_WorkGrid->m_vec_VoxelLimb[f_Jet];

						if(f_Limb->m_rebuild == 1)
							{
#ifdef VOXEL_LIMB_ON
							f_Limb->RebuildMesh(f_Engine_ThreadIndex);
							f_Limb->CompleteMesh(f_Engine_ThreadIndex);
							f_Limb->SetCreated(f_Engine_ThreadIndex, true);
#else
							f_Limb->m_created = true;
							f_Limb->m_build_count = 1;
							f_Limb->m_rebuild = 0;
							f_Limb->m_full = false;
							f_Limb->m_emptyVoxelGrid = true;
#endif
							}
						}
					}

				f_WorkGrid->SetCreated(f_Engine_ThreadIndex, true);

				Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

				// Repeat Build Appease
				if(f_vec_WorkStatus->size() <= 0)
					{
					f_vec_WorkStatus->push_back(1);
					}

				if(f_vec_WorkStatus->at(f_vec_WorkStatus->size() - 1) == 1) //?chk?all? for..
					{	//Win Conditions
					f_vec_WorkStatus->at(f_vec_WorkStatus->size() - 1) = -5;
					}

				for(int f_XY = 0; f_XY < Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.size(); f_XY++)
					{
					if(Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid[f_XY]->m_UID == f_WorkGrid->m_UID)
						{
						for(int f_ZS = f_XY; f_ZS < Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.size() - 1; f_ZS++)
							{
							Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid[f_ZS] = Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid[f_ZS + 1];
							}

						Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Grid.pop_back();
						}
					}

				Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
				}
			}
		else
			{
			f_FrameScan = false;
			}

		 ////////////////////////
		// Checking Limb Work //
		Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

		f_Limb_WorkSize = Cube::g_VoxelGridManager->m_vec_EngineWork_Limb.size();

		Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();

		if(f_Limb_WorkSize > 0)
			{
			Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

			if(Cube::g_VoxelGridManager->m_vec_EngineWork_Limb.size() > 0)
				{
				std::shared_ptr<VoxelLimb> f_WorkLimb = Cube::g_VoxelGridManager->m_vec_EngineWork_Limb[0];

				//if(Cube::g_VoxelGridManager->m_vec_EngineWork_Limb.size() >= 2)
				//	{
					for(int f_XY = 0; f_XY < Cube::g_VoxelGridManager->m_vec_EngineWork_Limb.size() - 1; f_XY++)
						{
						Cube::g_VoxelGridManager->m_vec_EngineWork_Limb[f_XY] = Cube::g_VoxelGridManager->m_vec_EngineWork_Limb[f_XY + 1];
						}
				//	}

				Cube::g_VoxelGridManager->m_vec_EngineWork_Limb.pop_back();

				Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
			
				// Limb Re-Build
				if(f_WorkLimb->m_rebuild == 1)
					{
					f_WorkLimb->RebuildMesh(f_Engine_ThreadIndex);
					f_WorkLimb->CompleteMesh(f_Engine_ThreadIndex);
					f_WorkLimb->SetCreated(f_Engine_ThreadIndex, true);
					}

				Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

				for(int f_XY = 0; f_XY < Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Limb.size(); f_XY++)
					{
					if(Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Limb[f_XY]->m_UID == f_WorkLimb->m_UID)
						{
						for(int f_ZS = f_XY; f_ZS < Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Limb.size() - 1; f_ZS++)
							{
							Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Limb[f_ZS] = Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Limb[f_ZS + 1];
							}

						Cube::g_VoxelGridManager->m_vec_EngineWork_WIP_Limb.pop_back();
						}
					}

				Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
				}
			else
				{
				Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
				}
			}
		else
			{
			f_FrameScan = false;
			}
		}

	//- Close Thread -//
	Cube::g_VoxelGridManager->m_Muti_EngineWork.lock();

	f_Worker_Thread->ac_ExitKey();

	g_VoxelGridManager->m_EngineWork_ThreadCount--;

	Cube::g_VoxelGridManager->m_Muti_EngineWork.unlock();
	
	  //                    //
	 //- END ENGINE FRAME -//
	//                    //
}

void SecondaryAppWindowPageOGL::StopEngineLoop()
{
	m_Engine_ThreadON = false;
}

void SecondaryAppWindowPageOGL::StartInterfaceLoop()
{
	if(m_InterfaceTimer != nullptr)
		{
		if(m_InterfaceTimer.IsEnabled() == false)
			{
			m_InterfaceTimer = winrt::Windows::UI::Xaml::DispatcherTimer();

			TimeSpan ts(250);
			m_InterfaceTimer.Interval(ts);
			m_InterfaceTimer.Start();
			auto registrationtoken = m_InterfaceTimer.Tick({this, &SecondaryAppWindowPageOGL::acInterfaceLoop});
			}
		else
			{
			m_InterfaceTimer.Start();
			}
		}
	else
		{
		m_InterfaceTimer = winrt::Windows::UI::Xaml::DispatcherTimer();

		TimeSpan ts(250);
		m_InterfaceTimer.Interval(ts);
		m_InterfaceTimer.Start();
		auto registrationtoken = m_InterfaceTimer.Tick({ this, &SecondaryAppWindowPageOGL::acInterfaceLoop });
		}

	m_Interface_ThreadON = true;
}

void SecondaryAppWindowPageOGL::StartInputUpLoop()
{
	if(m_InputUpTimer != nullptr)
		{
		if(m_InputUpTimer.IsEnabled() == false)
			{
			m_InputUpTimer = winrt::Windows::UI::Xaml::DispatcherTimer();

			TimeSpan ts(166);
			m_InputUpTimer.Interval(ts);
			m_InputUpTimer.Start();
			auto registrationtoken = m_InputUpTimer.Tick({ this, &SecondaryAppWindowPageOGL::acInputUpLoop });
			}
		else
			{
			m_InputUpTimer.Start();
			}
		}
	else
		{
		m_InputUpTimer = winrt::Windows::UI::Xaml::DispatcherTimer();

		TimeSpan ts(166);
		m_InputUpTimer.Interval(ts);
		m_InputUpTimer.Start();
		auto registrationtoken = m_InputUpTimer.Tick({ this, &SecondaryAppWindowPageOGL::acInputUpLoop });
		}

	m_InputUp_ThreadON = true;
}

void SecondaryAppWindowPageOGL::StartFrameLoop()
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

	if(m_FrameTimer != nullptr)
		{
		if(m_FrameTimer.IsEnabled() == false)
			{
			m_FrameTimer = winrt::Windows::UI::Xaml::DispatcherTimer();

			TimeSpan ts(ECOIN_ASYNC_REFRESH_MILLISECONDS);
			m_FrameTimer.Interval(ts);
			m_FrameTimer.Start();
			auto registrationtoken = m_FrameTimer.Tick({ this, &SecondaryAppWindowPageOGL::Frame_OnCount });
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
		auto registrationtoken = m_FrameTimer.Tick({ this, &SecondaryAppWindowPageOGL::Frame_OnCount });
		}

	m_Frame_ThreadON = true;
}

winrt::Windows::UI::Xaml::Controls::TextBlock SecondaryAppWindowPageOGL::ac_Acquire_QINT(int f_Index)
{
	winrt::Windows::UI::Xaml::Controls::TextBlock f_TextBlock = itemspanel().Children().GetAt(f_Index).as<winrt::Windows::UI::Xaml::Controls::TextBlock>();

	return f_TextBlock;
}

void SecondaryAppWindowPageOGL::acInterfaceLoop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable e)
{
	if(g_GameOpen)
		{
		EGLint panelWidth = 1920;
		EGLint panelHeight = 1080;
		
		//g_OpenGLES.GetSurfaceDimensions(g_RenderSurface, &panelWidth, &panelHeight);

		int f_PlayerHitBy = 0;

		 /////////////////
		// Life Energy
		float f_onebar = 100.0f;

		float f_player1hbar = f_onebar*((float)player[0]->HB_Health / (float)player[0]->HB_MaxHealth);
		float f_player1pbar = f_onebar*((float)player[0]->HB_Energy / (float)player[0]->HB_MaxEnergy);
		float f_player1abar = f_onebar*((float)player[0]->HB_Armour / (float)player[0]->HB_MaxArmour);

		p1HealthBar().Value(f_player1hbar);
		p1EnergyBar().Value(f_player1pbar);
		p1ArmourBar().Value(f_player1abar);

		float f_player2hbar = f_onebar*((float)player[1]->HB_Health / (float)player[1]->HB_MaxHealth);
		float f_player2pbar = f_onebar*((float)player[1]->HB_Energy / (float)player[1]->HB_MaxEnergy);
		float f_player2abar = f_onebar*((float)player[1]->HB_Armour / (float)player[1]->HB_MaxArmour);

		p2HealthBar().Value(f_player2hbar);
		p2EnergyBar().Value(f_player2pbar);
		p2ArmourBar().Value(f_player2abar);

		g_PlayerShowEnemyIdx = 0;

		if(player[0]->HB_LastAvatarHitIDSTORE != player[0]->HB_LastAvatarHitID)
			{
			g_PlayerShowEnemyIdx = 0;
			}
		else
			{
			if(player[1]->HB_LastAvatarHitIDSTORE != player[1]->HB_LastAvatarHitID)
				{
				g_PlayerShowEnemyIdx = 1;
				}
			}

		f_PlayerHitBy = g_PlayerShowEnemyIdx;

		if(g_PlayerShowEnemyIdx == 0)
			{
			if(player[0]->HB_LastAvatarHitID >= 0 && player[0]->HB_LastAvatarHitID < _->NomAI)
				{
				float f_avatarhbar = f_onebar*((float)Q_Forge->Forge[player[0]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[0]->HB_LastAvatarHitID].HB_MaxHealth);
				float f_avatarpbar = f_onebar*((float)Q_Forge->Forge[player[0]->HB_LastAvatarHitID].HB_Energy / (float)Q_Forge->Forge[player[0]->HB_LastAvatarHitID].HB_MaxEnergy);
				float f_avatarabar = f_onebar*((float)Q_Forge->Forge[player[0]->HB_LastAvatarHitID].HB_Armour / (float)Q_Forge->Forge[player[0]->HB_LastAvatarHitID].HB_MaxArmour);

				enemyHealthBar().Value(f_avatarhbar);
				enemyEnergyBar().Value(f_avatarpbar);
				enemyArmourBar().Value(f_avatarabar);

				player[0]->HB_LastAvatarHitIDSTORE = player[0]->HB_LastAvatarHitID;
				}
			}
		else
			{
			if(g_PlayerShowEnemyIdx == 1)
				{
				if(player[1]->HB_LastAvatarHitID >= 0 && player[1]->HB_LastAvatarHitID < _->NomAI)
					{
					float f_avatarhbar = f_onebar*((float)Q_Forge->Forge[player[1]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[1]->HB_LastAvatarHitID].HB_MaxHealth);
					float f_avatarpbar = f_onebar*((float)Q_Forge->Forge[player[1]->HB_LastAvatarHitID].HB_Energy / (float)Q_Forge->Forge[player[1]->HB_LastAvatarHitID].HB_MaxEnergy);
					float f_avatarabar = f_onebar*((float)Q_Forge->Forge[player[1]->HB_LastAvatarHitID].HB_Armour / (float)Q_Forge->Forge[player[1]->HB_LastAvatarHitID].HB_MaxArmour);

					enemyHealthBar().Value(f_avatarhbar);
					enemyEnergyBar().Value(f_avatarpbar);
					enemyArmourBar().Value(f_avatarabar);

					player[1]->HB_LastAvatarHitIDSTORE = player[1]->HB_LastAvatarHitID;
					}
				}
			}

		  ///////////
		 ///////////
		// Input //
		if(g_vec_QINT_Input.size() > 0)
			{
			for(int f_Count = 0; f_Count < g_vec_QINT_Input.size(); f_Count++)
				{
				QINT_InterfaceItem* f_Item = g_vec_QINT_Input[f_Count];

				float f_X = (f_Item->m_X - playerAV[0]->Xform.Translation.x) + ((float)panelWidth / 2.0f);
				float f_Y = ((f_Item->m_Z - playerAV[0]->Xform.Translation.z) - f_Item->m_Y) + ((float)panelHeight / 2.0f);

				if(f_X >= 0 && f_X < panelWidth && f_Y >= 0 && f_Y < panelHeight)
					{
					winrt::Windows::UI::Xaml::Controls::TextBlock myTextBlock;
					myTextBlock.Text(f_Item->m_Text);

					winrt::Windows::UI::Xaml::Thickness myThickness({ f_X + (rand() % 10), f_Y + (rand() % 10), 0, 0 });
					myTextBlock.Margin(myThickness);

					itemspanel().Children().Append(myTextBlock);

					std::string f_ItemTextStr = std::string("Damage ") + to_string(f_Item->m_Text);
					winrt::hstring f_CompText = StrUsingStr(f_ItemTextStr);

					damageBox().Text(f_CompText);

					g_vec_QINT_Control.push_back(f_Item);
					}
				}

			// clear added inputs
			g_vec_QINT_Input.clear();

			  ///////////////////
			 // On Any Inputs //
			//update ally and enemy names and team colours
			if(m_PlayerTeamsInvalid == true)
				{
				m_PlayerTeamsInvalid = false;
				
				int f_Team[4];

				if(player[0]->Team == 0)
					{
					f_Team[0] = 0.0 * 255;
					f_Team[1] = 0.0 * 255;
					f_Team[2] = 0.0 * 255;
					f_Team[3] = 1.0 * 255;
					}
				else if(player[0]->Team == 1)
					{
					f_Team[0] = 0.21 * 255;
					f_Team[1] = 0.0 * 255;
					f_Team[2] = 1.0 * 255;
					f_Team[3] = 1.0 * 255;
					}
				else if(player[0]->Team == 2)
					{
					f_Team[0] = 1.0 * 255;
					f_Team[1] = 0.0 * 255;
					f_Team[2] = 0.0 * 255;
					f_Team[3] = 1.0 * 255;
					}
				else if(player[0]->Team == 3)
					{
					f_Team[0] = 1.0 * 255;
					f_Team[1] = 0.0 * 255;
					f_Team[2] = 0.25 * 255;
					f_Team[3] = 1.0 * 255;
					}
				else if(player[0]->Team == 4)
					{
					f_Team[0] = 0.5 * 255;
					f_Team[1] = 0.5 * 255;
					f_Team[2] = 0.0 * 255;
					f_Team[3] = 1.0 * 255;
					}

				Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(f_Team[3], f_Team[0], f_Team[1], f_Team[2]) });

				p1teamtextBlock().Foreground(myBrush);

				p1titletextBlock().Foreground(myBrush);

				p1titletextBlock().Text(StrUsingStr(player[0]->BFO.CharDATA[player[0]->BFO.CurrCHAR].Name));

				int f_TeamP2[4];

				if(player[1]->Team == 0)
					{
					f_TeamP2[0] = 0.0 * 255;
					f_TeamP2[1] = 0.0 * 255;
					f_TeamP2[2] = 0.0 * 255;
					f_TeamP2[3] = 1.0 * 255;
					}
				else if(player[1]->Team == 1)
					{
					f_TeamP2[0] = 0.21 * 255;
					f_TeamP2[1] = 0.0 * 255;
					f_TeamP2[2] = 1.0 * 255;
					f_TeamP2[3] = 1.0 * 255;
					}
				else if(player[1]->Team == 2)
					{
					f_TeamP2[0] = 1.0 * 255;
					f_TeamP2[1] = 0.0 * 255;
					f_TeamP2[2] = 0.0 * 255;
					f_TeamP2[3] = 1.0 * 255;
					}
				else if(player[1]->Team == 3)
					{
					f_TeamP2[0] = 1.0 * 255;
					f_TeamP2[1] = 0.0 * 255;
					f_TeamP2[2] = 0.25 * 255;
					f_TeamP2[3] = 1.0 * 255;
					}
				else if(player[1]->Team == 4)
					{
					f_TeamP2[0] = 0.5 * 255;
					f_TeamP2[1] = 0.5 * 255;
					f_TeamP2[2] = 0.0 * 255;
					f_TeamP2[3] = 1.0 * 255;
					}

				Windows::UI::Xaml::Media::SolidColorBrush myBrushP2({ Windows::UI::ColorHelper::FromArgb(f_TeamP2[3], f_TeamP2[0], f_TeamP2[1], f_TeamP2[2]) });

				p2teamtextBlock().Foreground(myBrushP2);

				p2titletextBlock().Foreground(myBrushP2);

				p2titletextBlock().Text(StrUsingStr(player[1]->BFO.CharDATA[player[1]->BFO.CurrCHAR].Name));
				}

			int f_Team[4];

			if(Q_Forge->Forge[player[f_PlayerHitBy]->HB_LastAvatarHitID].Team == 0)
				{
				f_Team[0] = 0.0 * 255;
				f_Team[1] = 0.0 * 255;
				f_Team[2] = 0.0 * 255;
				f_Team[3] = 1.0 * 255;
				}
			else if(Q_Forge->Forge[player[f_PlayerHitBy]->HB_LastAvatarHitID].Team == 1)
				{
				f_Team[0] = 0.21 * 255;
				f_Team[1] = 0.0 * 255;
				f_Team[2] = 1.0 * 255;
				f_Team[3] = 1.0 * 255;
				}
			else if(Q_Forge->Forge[player[f_PlayerHitBy]->HB_LastAvatarHitID].Team == 2)
				{
				f_Team[0] = 1.0 * 255;
				f_Team[1] = 0.0 * 255;
				f_Team[2] = 0.0 * 255;
				f_Team[3] = 1.0 * 255;
				}
			else if(Q_Forge->Forge[player[f_PlayerHitBy]->HB_LastAvatarHitID].Team == 3)
				{
				f_Team[0] = 1.0 * 255;
				f_Team[1] = 0.0 * 255;
				f_Team[2] = 0.25 * 255;
				f_Team[3] = 1.0 * 255;
				}
			else if(Q_Forge->Forge[player[f_PlayerHitBy]->HB_LastAvatarHitID].Team == 4)
				{
				f_Team[0] = 0.5 * 255;
				f_Team[1] = 0.5 * 255;
				f_Team[2] = 0.0 * 255;
				f_Team[3] = 1.0 * 255;
				}

			Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(f_Team[3], f_Team[0], f_Team[1], f_Team[2]) });

			lasthitteamtextBlock().Foreground(myBrush);

			char* f_CharVB = ag_ClearChar(64);

			sprintf(f_CharVB, "Team %i", Q_Forge->Forge[player[f_PlayerHitBy]->HB_LastAvatarHitID].Team);

			lasthitteamtextBlock().Text(StrUsingStr(std::string(f_CharVB)));

			lasthitnametextBlock().Foreground(myBrush);

			lasthitnametextBlock().Text(StrUsingStr(Q_Forge->Forge[player[f_PlayerHitBy]->HB_LastAvatarHitID].CharDATA.Name));
			}

		  /////////////
		 /////////////
		// Control //
		if(g_vec_QINT_Control.size() > 0)
			{
			for(int f_Count = 0; f_Count < g_vec_QINT_Control.size(); f_Count++)
				{
				QINT_InterfaceItem* f_Item = g_vec_QINT_Control[f_Count];

				float f_Float = ((float)f_Item->m_TimeLimit / (float)f_Item->m_Time) * 255.0f;
				int f_Int = (int)f_Float;

				Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb(f_Int, 255, 155, 185) });

				winrt::Windows::UI::Xaml::Controls::TextBlock f_TextBlock = ac_Acquire_QINT(f_Count);

				f_TextBlock.Foreground(myBrush);

				f_Item->m_Time += f_Item->m_TimeProgression * _->TimeScale;

				if(f_Item->m_Time > f_Item->m_TimeLimit)
					{
					int v = f_Count;
					for(int i = v; i < (g_vec_QINT_Control.size() - 1); i++)
						{
						g_vec_QINT_Control[i] = g_vec_QINT_Control[i + 1];
						}

					g_vec_QINT_Control.pop_back();
					}
				}
			}
		else
			{
			itemspanel().Children().Clear();
			}
		}//END g_GameOpen END//
}

void SecondaryAppWindowPageOGL::acInputUpLoop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable e)
{
	if(g_GameOpen == true)
		{
		if(g_GameFocusOn == true)
			{
#ifdef KEYOFF_CHECKER_ONLY
			for(int f_Jet = 0; f_Jet < g_vec_Qy.size(); f_Jet++)
				{
				auto f_State = g_CoreWindow.GetAsyncKeyState((winrt::Windows::System::VirtualKey)g_vec_Qy[f_Jet]);

				if((f_State & CoreVirtualKeyStates::Down) != CoreVirtualKeyStates::Down)
					{
					g_Qy[g_vec_Qy[f_Jet]] = false;

					for(int f_Helly = f_Jet; f_Helly < g_vec_Qy.size() - 1; f_Helly++)
						{
						g_vec_Qy[f_Helly] = g_vec_Qy[f_Helly + 1];
						}

					g_vec_Qy.pop_back();
					}
				}
#else
			for(int f_Jet = 0; f_Jet < g_vec_Qy_ok.size(); f_Jet++)
				{
				CoreVirtualKeyStates f_State = g_CoreWindow.GetAsyncKeyState((winrt::Windows::System::VirtualKey)g_vec_Qy_ok[f_Jet]);

				if(((int)f_State & (int)CoreVirtualKeyStates::Down) > (int)0)
					{
					g_Qy[g_vec_Qy_ok[f_Jet]] = true;
					}
				else
					{
					g_Qy[g_vec_Qy_ok[f_Jet]] = false;
					}
				}
#endif
			}
		}//end g_GameOpen
}

void SecondaryAppWindowPageOGL::StopInterfaceLoop()
{
	if(m_InterfaceTimer.IsEnabled())
		{
		m_InterfaceTimer.Stop();
		}

	m_Interface_ThreadON = false;
}

void SecondaryAppWindowPageOGL::StopInputUpLoop()
{
	if(m_InputUpTimer.IsEnabled())
		{
		m_InputUpTimer.Stop();
		}

	m_InputUp_ThreadON = false;
}

void SecondaryAppWindowPageOGL::StopFrameLoop()
{
	if(m_FrameTimer.IsEnabled())
		{
		m_FrameTimer.Stop();
		}

	m_Frame_ThreadON = false;
}

void SecondaryAppWindowPageOGL::OnRefreshCharSelectListBox(void)
{
	if(g_GameOpen)
		{
		charlistBox().Items().Clear();

		for(int f_Count = 0; f_Count < player[g_Player]->BFO.NomCharacters; f_Count++)
			{
			charlistBox().Items().InsertAt((unsigned int)f_Count, box_value(StrUsingStr(player[g_Player]->BFO.CharDATA[f_Count].Name)));
			}
		}
}

void SecondaryAppWindowPageOGL::onClickStartMission1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	////// Temp test spawn
	for(int f_Int = 0; f_Int < 10; f_Int++)
		{
		if(_->NomAI < 406)
			{
			int f_Team = Cube::randomFac() % 3;
			QpoVec3d f_Position;
			f_Position.x = (((Cube::random() - 0.5) * 2) * 900.0f) + playerAV[0]->Xform.Translation.x;
			f_Position.y = 480.75f;
			f_Position.z = (((Cube::random() - 0.5) * 2) * 900.0f) + playerAV[0]->Xform.Translation.z;
			acSpawnAvatar(0, rand() % player[g_Player]->BFO.NomCharacters, rand() % 5, f_Team, f_Position, -1, 0, false);
			}
		}
}

void SecondaryAppWindowPageOGL::onClickMissionButton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(spawnpanel().Visibility() == winrt::Windows::UI::Xaml::Visibility::Collapsed)
		{
		spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		}
	else
		{
		spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageOGL::onClickInsertType(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	gui_InsertType++;

	if(gui_InsertType > 3)
		{
		gui_InsertType = 0;
		}

	Show_MissionPanel();
}

void SecondaryAppWindowPageOGL::Show_MissionPanel(void)
{
	if(gui_InsertType == 0)
		{
		terrainStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		spawnStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		triggerStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		buildingStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}

	if(gui_InsertType == 1)
		{
		terrainStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		spawnStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		triggerStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		buildingStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		}

	if(gui_InsertType == 2)
		{
		terrainStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		spawnStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		triggerStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		buildingStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}

	if(gui_InsertType == 3)
		{
		terrainStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		spawnStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		triggerStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		buildingStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}

	if(gui_InsertType == 4)
		{
		terrainStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		spawnStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		triggerStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		buildingStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageOGL::onClickInsertTypeMin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	gui_InsertType--;

	if(gui_InsertType < 0)
		{
		gui_InsertType = 3;
		}

	Show_MissionPanel();
}

void SecondaryAppWindowPageOGL::onClickLogin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

#if 0
	Qpo->Sound_Load_Play(&Medias->S_QuantumAngelIntro, "QpoSound", "QuantumAngelIntro.wav", 1.0f);
#endif

	std::string f_Username = to_string(logintextBox().Text());
	std::string f_Password = to_string(passwordtextBox().Text());

	g_QA_Username = f_Username;
	g_QA_Password = f_Password;

	g_Schedular[2]->acLogin(f_Username, f_Password);

	qaccounttextBlock().Text(StrUsingStr(f_Username));

	acSaveLogin(f_Username, f_Password);

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_Wallet->GetBalance(false));

	accountbalancetextBlock().Text(StrUsingStr(f_char));

	loginStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
	centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
}

void SecondaryAppWindowPageOGL::onClickRegister(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	std::string f_Username = to_string(logintextBox().Text());
	std::string f_Password = to_string(passwordtextBox().Text());
	std::string f_Email = to_string(emailtextBox().Text());

	g_Schedular[2]->acRegister(f_Username, f_Password, f_Email);

	acSaveLogin(f_Username, f_Password);

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_Wallet->GetBalance(false));

	accountbalancetextBlock().Text(StrUsingStr(f_char));

	loginStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
	centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
}

void SecondaryAppWindowPageOGL::acUpdateInsert(void)
{
	if(g_TerrainInsertUpdateMode == 0)
		{
#if 0
		acClearVoxels();

		g_VoxelGridManager->Position_Player(BiVector(-g_Position.m_X, g_Position.m_Y, g_Position.m_Z));
#endif

		//Terrain
		acUpdateTerrainInsert();
		}
}

void SecondaryAppWindowPageOGL::acClearVoxels(void)
{
	g_VoxelGridManager->m_VoxelGridsVector.clear();
}

void SecondaryAppWindowPageOGL::acUpdateTerrainInsert(void)
{
	const float BLOCK_RENDER = (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_SIZE = (Cube::VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	if(g_GameOpen)
		{
		BiVector f_Pos;

		for(int f_moveX = 1; f_moveX < (g_TerrainInsertMaxX + 1); f_moveX += g_TerrainInsertMoveX)
			{
			for(int f_moveY = 1; f_moveY < (g_TerrainInsertMaxY + 1); f_moveY += g_TerrainInsertMoveY)
				{
				for(int f_moveZ = 1; f_moveZ < (g_TerrainInsertMaxZ + 1); f_moveZ += g_TerrainInsertMoveZ)
					{
					for(int f_fillX = 1; f_fillX < (g_TerrainInsertFillX + 1); f_fillX++)
						{
						for(int f_fillY = 1; f_fillY < (g_TerrainInsertFillY + 1); f_fillY++)
							{
							for(int f_fillZ = 1; f_fillZ < (g_TerrainInsertFillZ + 1); f_fillZ++)
								{ ///////////////
								 // negated
								bool f_Negate = false;

								if((((g_TerrainInsertNegatedX > 0) && (f_fillX > g_TerrainInsertNegatedX)) || ((g_TerrainInsertNegatedX < 0) && (f_fillX < g_TerrainInsertFillX - (g_TerrainInsertNegatedX * -1)) || (g_TerrainInsertNegatedX == 0))) &&
								   (((g_TerrainInsertNegatedY > 0) && (f_fillY > g_TerrainInsertNegatedY)) || ((g_TerrainInsertNegatedY < 0) && (f_fillY < g_TerrainInsertFillY - (g_TerrainInsertNegatedY * -1)) || (g_TerrainInsertNegatedY == 0))) &&
								   (((g_TerrainInsertNegatedZ > 0) && (f_fillZ > g_TerrainInsertNegatedZ)) || ((g_TerrainInsertNegatedZ < 0) && (f_fillZ < g_TerrainInsertFillZ - (g_TerrainInsertNegatedZ * -1)) || (g_TerrainInsertNegatedZ == 0))))
									{
									f_Negate = false;
									}
								else
									{
									f_Negate = true;
									}

								  ///////////
								 // fpos
								//
								f_Pos.m_X = g_PlaceInsertX + (((f_fillX * BLOCK_RENDER) * f_moveX));
								f_Pos.m_Y = g_PlaceInsertY + (((f_fillY * BLOCK_RENDER) * f_moveY));
								f_Pos.m_Z = (g_PlaceInsertZ * -1.0f) + (((f_fillZ * BLOCK_RENDER) * f_moveZ));

								g_UpdatingMuti.lock();

								int f_i = g_VoxelGridManager->m_VoxelGridsVector.size();

								g_UpdatingMuti.unlock();

								for(int i = 0; i < f_i; i++)
									{
									std::shared_ptr<VoxelGrid> f_Grid = g_VoxelGridManager->m_VoxelGridsVector[i];

									if(f_Grid->m_rebuild == 0)
										{
										if( (f_Pos.m_X >= (f_Grid->m_gridX * GRID_SIZE)) &&
											(f_Pos.m_X < ((f_Grid->m_gridX + 1) * GRID_SIZE)) &&
											(f_Pos.m_Y >= (f_Grid->m_gridY * GRID_SIZE)) &&
											(f_Pos.m_Y < ((f_Grid->m_gridY + 1) * GRID_SIZE)) &&
											(f_Pos.m_Z >= ((f_Grid->m_gridZ * -1) * GRID_SIZE)) &&
											(f_Pos.m_Z < (((f_Grid->m_gridZ * -1) + 1) * GRID_SIZE)))
											{
											BiVector f_Point(f_Pos.m_X, f_Pos.m_Y, f_Pos.m_Z);

											  //////////////////
											 // Inside VX
											//
											f_Grid->m_VX_Core->m_Core_Muti.lock();

											for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
												{
												for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
													{
													for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
														{
														float f_CentralX = (((f_Grid->m_gridX * GRID_SIZE) + ((x * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE)));
														float f_CentralY = (((f_Grid->m_gridY * GRID_SIZE) + ((y * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE)));
														float f_CentralZ = ((((f_Grid->m_gridZ * -1) * GRID_SIZE) + ((z * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE)));
						
														BiVector f_Central(f_CentralX, f_CentralY, f_CentralZ);
														BiVector f_ForceVec = f_Central - f_Point;

														float f_ForceFac = f_ForceVec.acLength();

														  ///////////////////
														 // Sphere Test
														//
														if(f_ForceFac <= 15.5f)
															{
#if 0
															if(f_LockInt == false)
																{
																g_UpdatingMuti.lock();
																f_LockInt = true;
																}
#endif

															f_Grid->SetNeedsRebuild(true, true, true);

															int f_X = x;
															int f_Y = y;
															int f_Z = z;

															if(f_Negate)
																{
																f_Grid->SetColour(f_X, f_Y, f_Z, 0.0f, 0.0f, 0.0f, 0.0f);
																f_Grid->SetStrength(f_X, f_Y, f_Z, 0.0f);
																}
															else
																{
																float red = 0.65f;
																float green = 0.80f;
																float blue = 0.00f;
																float alpha = 1.0f;

																BlockType blockType = BlockType::BlockType_Default;

																f_Grid->SetColour(f_X, f_Y, f_Z, red, green, blue, alpha);
																f_Grid->SetStrength(f_X, f_Y, f_Z, 0.0f);
																f_Grid->SetBlockType(f_X, f_Y, f_Z, blockType);
																}
															}
														}
													}
												}

											f_Grid->m_VX_Core->m_Core_Muti.unlock();
											}
										}

									g_UpdatingMuti.lock();

									f_i = g_VoxelGridManager->m_VoxelGridsVector.size();

									g_UpdatingMuti.unlock();
									}
								}
							}
						}
					}
				}
			}
		}
}

void SecondaryAppWindowPageOGL::onClickMissionCreate(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	QAM* f_QAM = new QAM;

	f_QAM->acClear();

	f_QAM->m_qaccountid = g_QAccountID;
	f_QAM->m_Name = "New Mission";
	f_QAM->m_Author = "Author";
	f_QAM->m_Description = "Description";
	f_QAM->m_Keywords = "Keywords";
	f_QAM->m_Features = "Features";
	f_QAM->m_evalue = 0.0f;
	f_QAM->m_LevelCurrent = 0;
	f_QAM->m_LevelCount = 1;

	g_QAM = f_QAM;

	g_QAM->ac_Save();

	g_Editor_ON = true;

	g_QamStatus = QAM_STATUS_REFRESHED;

	loadmissionpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::onClickViewMission(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_LoggedOn == true)
		{
		centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

		//g_QamID = 1;

		acLoadBrief();

		loadmissionpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		}
}

void SecondaryAppWindowPageOGL::acLoadBrief(void)
{
	  ////////////
	 // Data
	// mission brief
	QAM* f_QAM = ag_LoadBrief(g_QamID);

	if(f_QAM->m_Name.length() > 0)
		{
		missionnametextBlock().Text(StrUsingStr(f_QAM->m_Name));
		}

	if(f_QAM->m_Author.length() > 0)
		{
		missionauthortextBlock().Text(StrUsingStr(f_QAM->m_Author));
		}

	if(f_QAM->m_Features.length() > 0)
		{
		missionfeaturestextBlock().Text(StrUsingStr(f_QAM->m_Features));
		}

	if(f_QAM->m_ECN.length() > 0)
		{
		missioncosttextBlock().Text(StrUsingStr(f_QAM->m_ECN));
		}

	if(f_QAM->m_Description.length() > 0)
		{
		missionbriefingtextBox().Text(StrUsingStr(f_QAM->m_Description));
		}

	g_QAM = f_QAM;
}

void SecondaryAppWindowPageOGL::onClickFillXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillX += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillX);

	terrainfillxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickFillYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillY += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillY);

	terrainfillytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickFillZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillZ += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillZ);

	terrainfillztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveX += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveX);

	terrainmovextextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveY += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveY);

	terrainmoveytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveZ += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveZ);

	terrainmoveztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedX += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedX);

	terrainnegatedxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedY += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedY);

	terrainnegatedytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedZ += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedZ);

	terrainnegatedztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxXplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxX += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxX);

	terrainmaxxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxYplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxY += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxY);

	terrainmaxytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxZplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxZ += g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxZ);

	terrainmaxztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

//RESET

void SecondaryAppWindowPageOGL::onClickFillXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillX = g_TerrainInsertFillXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillX);

	terrainfillxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickFillYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillY = g_TerrainInsertFillYres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillY);

	terrainfillytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickFillZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillZ = g_TerrainInsertFillZres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillZ);

	terrainfillztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveX = g_TerrainInsertMoveXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveX);

	terrainmovextextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveY = g_TerrainInsertMoveXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveY);

	terrainmoveytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveZ = g_TerrainInsertMoveXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveZ);

	terrainmoveztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedX = g_TerrainInsertNegatedXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedX);

	terrainnegatedxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedY = g_TerrainInsertNegatedXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedY);

	terrainnegatedytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedZ = g_TerrainInsertNegatedXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedZ);

	terrainnegatedztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxXreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxX = g_TerrainInsertMaxXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxX);

	terrainmaxxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxYreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxY = g_TerrainInsertMaxXres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxY);

	terrainmaxytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxZreset(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxZ = g_TerrainInsertMaxZres;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxZ);

	terrainmaxztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

//MINUS

void SecondaryAppWindowPageOGL::onClickFillXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillX -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillX);

	terrainfillxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickFillYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillY -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillY);

	terrainfillytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickFillZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertFillZ -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertFillZ);

	terrainfillztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveX -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveX);

	terrainmovextextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveY -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveY);

	terrainmoveytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMoveZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMoveZ -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMoveZ);

	terrainmoveztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedX -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedX);

	terrainnegatedxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedY -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedY);

	terrainnegatedytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickNegatedZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertNegatedZ -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertNegatedZ);

	terrainnegatedztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxXminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxX -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxX);

	terrainmaxxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxYminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxY -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxY);

	terrainmaxytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickMaxZminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertMaxZ -= g_TerrainInsertScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertMaxZ);

	terrainmaxztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

//PLACEMENT

void SecondaryAppWindowPageOGL::onClickPlacePositionIncMinus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if((g_PlaceInsertPosInc > 1.0f) || (g_PlaceInsertPosInc <= -1.0f))
		{
		g_PlaceInsertPosInc -= 0.5f * (float)g_PlaceScale;
		}
	else
		{
		g_PlaceInsertPosInc -= 0.0125f * (float)g_PlaceScale;
		}

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertPosInc);

	placepositioninctextBox().Text(StrUsingStr(f_char));

	delete f_char;
}

void SecondaryAppWindowPageOGL::onClickPlacePositionIncPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if((g_PlaceInsertPosInc >= 1.0f) || (g_PlaceInsertPosInc < -1.0f))
		{
		g_PlaceInsertPosInc += 0.5f * (float)g_PlaceScale;
		}
	else
		{
		g_PlaceInsertPosInc += 0.0125f * (float)g_PlaceScale;
		}

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertPosInc);

	placepositioninctextBox().Text(StrUsingStr(f_char));

	delete f_char;
}

void SecondaryAppWindowPageOGL::onClickPlaceAngleIncMinus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if((g_PlaceInsertAngInc > 1.0f) || (g_PlaceInsertAngInc <= -1.0f))
		{
		g_PlaceInsertAngInc -= 15.0f;
		}
	else
		{
		g_PlaceInsertAngInc -= 0.5f;
		}

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertAngInc);

	placeangleinctextBox().Text(StrUsingStr(f_char));

	delete f_char;
}

void SecondaryAppWindowPageOGL::onClickPlaceAngleIncPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if((g_PlaceInsertAngInc >= 1.0f) || (g_PlaceInsertAngInc < -1.0f))
		{
		g_PlaceInsertAngInc += 15.0f;
		}
	else
		{
		g_PlaceInsertAngInc += 0.5f;
		}

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertAngInc);

	placeangleinctextBox().Text(StrUsingStr(f_char));

	delete f_char;
}

void SecondaryAppWindowPageOGL::onClickPlacePositionMinusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertX -= g_PlaceInsertPosInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertX);

	placepositionxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlacePositionPlusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertX += g_PlaceInsertPosInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertX);

	placepositionxtextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlacePositionMinusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertY -= g_PlaceInsertPosInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertY);

	placepositionytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlacePositionPlusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertY += g_PlaceInsertPosInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertY);

	placepositionytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlacePositionMinusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertZ -= g_PlaceInsertPosInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertZ);

	placepositionztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlacePositionPlusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertZ += g_PlaceInsertPosInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertZ);

	placepositionztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

//PLACE ANGLE

void SecondaryAppWindowPageOGL::onClickPlaceAngleMinusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertXrot -= g_PlaceInsertAngInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertXrot);

	placeanglextextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlaceAnglePlusX(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertXrot += g_PlaceInsertAngInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertXrot);

	placeanglextextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlaceAngleMinusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertYrot -= g_PlaceInsertAngInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertYrot);

	placeangleytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlaceAnglePlusY(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertYrot += g_PlaceInsertAngInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertYrot);

	placeangleytextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlaceAngleMinusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertZrot -= g_PlaceInsertAngInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertZrot);

	placeangleztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlaceAnglePlusZ(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceInsertZrot += g_PlaceInsertAngInc;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%f", g_PlaceInsertZrot);

	placeangleztextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}


void SecondaryAppWindowPageOGL::onClickInsert(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

#if 1
	g_QamID = g_QAM->m_qamid;
#endif

	if(gui_InsertType == 0)
		{
		qamTerrain* f_Terrain = new qamTerrain();
		f_Terrain->m_TerrainInsertFillX = g_TerrainInsertFillX;

		char f_NameGrouptext[256];
		sprintf(f_NameGrouptext, "%i", g_NameGroup[g_current_NameGroup].m_currentOrder);
		f_Terrain->m_NameGroup = f_NameGrouptext;

		f_Terrain->m_X = g_PlaceInsertX;
		f_Terrain->m_Y = g_PlaceInsertY;
		f_Terrain->m_Z = g_PlaceInsertZ;

		f_Terrain->m_Xrot = g_PlaceInsertXrot;
		f_Terrain->m_Yrot = g_PlaceInsertYrot;
		f_Terrain->m_Zrot = g_PlaceInsertZrot;

		f_Terrain->m_TerrainInsertFillX = g_TerrainInsertFillX;
		f_Terrain->m_TerrainInsertFillY = g_TerrainInsertFillY;
		f_Terrain->m_TerrainInsertFillZ = g_TerrainInsertFillZ;
		f_Terrain->m_TerrainInsertMoveX = g_TerrainInsertMoveX;
		f_Terrain->m_TerrainInsertMoveY = g_TerrainInsertMoveY;
		f_Terrain->m_TerrainInsertMoveZ = g_TerrainInsertMoveZ;
		f_Terrain->m_TerrainInsertNegatedX = g_TerrainInsertNegatedX;
		f_Terrain->m_TerrainInsertNegatedY = g_TerrainInsertNegatedY;
		f_Terrain->m_TerrainInsertNegatedZ = g_TerrainInsertNegatedZ;
		f_Terrain->m_TerrainInsertMaxX = g_TerrainInsertMaxX;
		f_Terrain->m_TerrainInsertMaxY = g_TerrainInsertMaxY;
		f_Terrain->m_TerrainInsertMaxZ = g_TerrainInsertMaxZ;
		f_Terrain->m_TerrainInsertFillXres = g_TerrainInsertFillXres;
		f_Terrain->m_TerrainInsertFillYres = g_TerrainInsertFillYres;
		f_Terrain->m_TerrainInsertFillZres = g_TerrainInsertFillZres;
		f_Terrain->m_TerrainInsertMoveXres = g_TerrainInsertMoveXres;
		f_Terrain->m_TerrainInsertMoveYres = g_TerrainInsertMoveYres;
		f_Terrain->m_TerrainInsertMoveZres = g_TerrainInsertMoveZres;
		f_Terrain->m_TerrainInsertNegatedXres = g_TerrainInsertNegatedXres;
		f_Terrain->m_TerrainInsertNegatedYres = g_TerrainInsertNegatedYres;
		f_Terrain->m_TerrainInsertNegatedZres = g_TerrainInsertNegatedZres;
		f_Terrain->m_TerrainInsertMaxXres = g_TerrainInsertMaxXres;
		f_Terrain->m_TerrainInsertMaxYres = g_TerrainInsertMaxYres;
		f_Terrain->m_TerrainInsertMaxZres = g_TerrainInsertMaxZres;
		f_Terrain->m_materialid = 0;
		f_Terrain->m_DefaultShape = 0;

		f_Terrain->m_Order = g_NameGroup[g_current_NameGroup].m_currentOrder;
		f_Terrain->m_Type = 0;
		f_Terrain->m_Repeat = 0;

		f_Terrain->m_QamLevel = g_QAM->m_LevelCurrent;
		f_Terrain->m_QamID = g_QAM->m_qamid;

		f_Terrain->ac_Save();

		//g_VoxMuti.ac_Fire();

		g_QAM->m_vec_Terrain.push_back(f_Terrain);

		//g_VoxMuti.ac_Free();
		}
	else if(gui_InsertType == 2)
		{
		qamSpawn* f_Spawn = new qamSpawn();

		char f_NameGrouptext[256];
		sprintf(f_NameGrouptext, "%i", g_NameGroup[g_current_NameGroup].m_currentOrder);
		f_Spawn->m_NameGroup = f_NameGrouptext;

		f_Spawn->m_X = g_PlaceInsertX;
		f_Spawn->m_Y = g_PlaceInsertY;
		f_Spawn->m_Z = g_PlaceInsertZ;

		f_Spawn->m_Xrot = g_PlaceInsertXrot;
		f_Spawn->m_Yrot = g_PlaceInsertYrot;
		f_Spawn->m_Zrot = g_PlaceInsertZrot;

		f_Spawn->m_Type = g_QamSpawnInsertCharacterDiscovery;
		f_Spawn->m_Repeat = 1;

		f_Spawn->m_QamLevel = g_QAM->m_LevelCurrent;
		f_Spawn->m_QamID = g_QAM->m_qamid;

		f_Spawn->m_CharID = g_PlaceInsertCharID;
		f_Spawn->m_Team = g_QamSpawnInsertCharacterTeam;

		f_Spawn->boosthealth = g_QamSpawnInsertCharacterBoostHealth;
		f_Spawn->boostconstitution = g_QamSpawnInsertCharacterBoostCon;
		f_Spawn->boostdamage = g_QamSpawnInsertCharacterBoostDamage;
		f_Spawn->boostfocus = g_QamSpawnInsertCharacterBoostFocus;
		f_Spawn->boostjink = g_QamSpawnInsertCharacterBoostJink;

		f_Spawn->ac_Save();

		acSpawnAvatar(0, g_PlaceInsertCharID, player[0]->BFO.CharDATA[g_PlaceInsertCharID].BDataID, g_QamSpawnInsertCharacterTeam, QpoVec3d(g_PlaceInsertX, g_PlaceInsertY, g_PlaceInsertZ), -1, 0, false);

		//g_VoxMuti.ac_Fire();

		g_QAM->m_vec_Spawn.push_back(f_Spawn);

		//g_VoxMuti.ac_Free();
		}
}

void SecondaryAppWindowPageOGL::onClickPlay(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_QAM)
		{
		delete g_QAM;

		Q_Clear();
		}

	QAM* f_QAM = new QAM(g_QamID);

	g_QAM = f_QAM;

	g_Editor_ON = false;

	g_QamStatus = QAM_STATUS_STARTED;

	g_AI_ON = true;

	g_VoxelGridManager->acFullRebuild();

	loadmissionpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
	spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
}

void SecondaryAppWindowPageOGL::onClickNextMission(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamID++;

	acLoadBrief();
}

void SecondaryAppWindowPageOGL::onClickPrevMission(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamID--;

	acLoadBrief();
}

void SecondaryAppWindowPageOGL::onClickEdit(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_QAM)
		{
		delete g_QAM;

		Q_Clear();
		}

	QAM* f_QAM = new QAM(g_QamID);

	g_QAM = f_QAM;

	g_Editor_ON = true;

	g_QamStatus = QAM_STATUS_REFRESHED;

	g_AI_ON = false;

	g_VoxelGridManager->acFullRebuild();

	spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
	loadmissionpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::OnClickSpawncharacterInc(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamSpawnInsertCharacterSelect++;

	if(g_QamSpawnInsertCharacterSelect >= player[0]->BFO.NomCharacters)
		{
		g_QamSpawnInsertCharacterSelect = player[0]->BFO.NomCharacters - 1;
		}

	spawncharactertextBlock().Text(StrUsingStr(player[0]->BFO.CharDATA[g_QamSpawnInsertCharacterSelect].Name));
}

void SecondaryAppWindowPageOGL::OnClickSpawncharacterMin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamSpawnInsertCharacterSelect--;

	if(g_QamSpawnInsertCharacterSelect < 0)
		{
		g_QamSpawnInsertCharacterSelect = 0;
		}

	spawncharactertextBlock().Text(StrUsingStr(player[0]->BFO.CharDATA[g_QamSpawnInsertCharacterSelect].Name));
}

void SecondaryAppWindowPageOGL::OnClickDiscovery(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamSpawnInsertCharacterDiscovery++;

	if(g_QamSpawnInsertCharacterDiscovery > 2)
		{
		g_QamSpawnInsertCharacterDiscovery = 0;
		}

	switch(g_QamSpawnInsertCharacterDiscovery)
		{
		case QAM_SPAWN_TYPE_UPON_DISCOVERY:
			spawntypebutton().Content(box_value(StrUsingStr("Upon Discovery")));
			break;

		case QAM_SPAWN_TYPE_TRIGGER:
			spawntypebutton().Content(box_value(StrUsingStr("Trigger")));
			break;

		case QAM_SPAWN_TYPE_START_ACTIVE:
			spawntypebutton().Content(box_value(StrUsingStr("Start Active")));
			break;
		}
}

void ag_ApplyUpdate(float f_Sp)
{
	playerU[0]->m_UpdateReady = true;
	playerU[0]->m_UpdateDisplay = true;
	playerU[0]->m_ItemUpdate = true;
	playerU[0]->m_CharUpdate = true;
	//TX

	if(f_Sp > 0.0f)
		{
		float f_MiniSp = f_Sp / 5000.0f;
		playerU[0]->m_TXUpdate = true;
		playerU[0]->m_TXAmt = f_MiniSp * (50.0f / g_Wallet->m_Reward);
		}
	//f_Sp
}

void SecondaryAppWindowPageOGL::onClickSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	printf("Starting Character Data Upload...\n");

	g_Player = 0;

	playerU[g_Player]->m_UpdateReady = true;
	playerU[g_Player]->m_UpdateDisplay = true;
	playerU[g_Player]->m_ItemUpdate = true;
	playerU[g_Player]->m_CharUpdate = true;
	playerU[g_Player]->m_CharAttacksUpdate = true;
	playerU[g_Player]->m_CharEditUpdate = true;
	playerU[g_Player]->m_CharEffectsUpdate = true;
	playerU[g_Player]->m_CharSkillUpdate = true;
}


void SecondaryAppWindowPageOGL::onClickLoad(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	printf("Starting Character Data Download...\n");

	g_Player = 0;

	Q.LoadCharacterData();
}

void SecondaryAppWindowPageOGL::onClickTeamMin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamSpawnInsertCharacterTeam--;

	if(g_QamSpawnInsertCharacterTeam < 0)
		{
		g_QamSpawnInsertCharacterTeam = 0;
		}

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_QamSpawnInsertCharacterTeam);

	angelteamtextBlock().Text(StrUsingStr(f_char));

	delete f_char;
}

void SecondaryAppWindowPageOGL::onClickTeamPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamSpawnInsertCharacterTeam++;

	if(g_QamSpawnInsertCharacterTeam > 9999999)
		{
		g_QamSpawnInsertCharacterTeam = 9999999;
		}

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_QamSpawnInsertCharacterTeam);

	angelteamtextBlock().Text(StrUsingStr(f_char));

	delete f_char;
}


void SecondaryAppWindowPageOGL::acUpdateBoost(void)
{
	switch(g_QamSpawnInsertCharacterBoostIndex)
		{
		case 0:
			{
			spawnboosttextBlock().Text(StrUsingStr("Boost Angel Health"));

			char* f_char = ag_ClearChar(250);
			sprintf(f_char, "%i", g_QamSpawnInsertCharacterBoostHealth);

			spawnboostamounttextBlock().Text(StrUsingStr(f_char));
			delete f_char;
			}break;
		case 1:
			{
			spawnboosttextBlock().Text(StrUsingStr("Boost Cons/Quickness"));

			char* f_char1 = ag_ClearChar(250);
			sprintf(f_char1, "%i", g_QamSpawnInsertCharacterBoostCon);

			spawnboostamounttextBlock().Text(StrUsingStr(f_char1));
			delete f_char1;
			}break;
		case 3:
			{
			spawnboosttextBlock().Text(StrUsingStr("Boost Damage"));

			char* f_char2 = ag_ClearChar(250);
			sprintf(f_char2, "%i", g_QamSpawnInsertCharacterBoostDamage);

			spawnboostamounttextBlock().Text(StrUsingStr(f_char2));
			delete f_char2;
			}break;

		case 4:
			{
			spawnboosttextBlock().Text(StrUsingStr("Boost Angel Focus"));

			char* f_char3 = ag_ClearChar(250);
			sprintf(f_char3, "%i", g_QamSpawnInsertCharacterBoostFocus);

			spawnboostamounttextBlock().Text(StrUsingStr(f_char3));
			delete f_char3;
			}break;

		case 5:
			{
			spawnboosttextBlock().Text(StrUsingStr("Boost Angel Jink"));

			char* f_char4 = ag_ClearChar(250);
			sprintf(f_char4, "%i", g_QamSpawnInsertCharacterBoostJink);

			spawnboostamounttextBlock().Text(StrUsingStr(f_char4));
			delete f_char4;
			}break;
		}
}

void SecondaryAppWindowPageOGL::onClickBoostDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamSpawnInsertCharacterBoostIndex--;

	if(g_QamSpawnInsertCharacterBoostIndex < 0)
		{
		g_QamSpawnInsertCharacterBoostIndex = 5;
		}

	acUpdateBoost();
}

void SecondaryAppWindowPageOGL::onClickBoostUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_QamSpawnInsertCharacterBoostIndex++;

	if(g_QamSpawnInsertCharacterBoostIndex > 5)
		{
		g_QamSpawnInsertCharacterBoostIndex = 0;
		}

	acUpdateBoost();
}

void SecondaryAppWindowPageOGL::onClickBoostLeft(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	switch(g_QamSpawnInsertCharacterBoostIndex)
		{
		case 0:
			g_QamSpawnInsertCharacterBoostHealth -= 50;
			break;

		case 1:
			g_QamSpawnInsertCharacterBoostCon -= 50;
			break;

		case 3:
			g_QamSpawnInsertCharacterBoostDamage -= 50;
			break;

		case 4:
			g_QamSpawnInsertCharacterBoostFocus -= 50;
			break;

		case 5:
			g_QamSpawnInsertCharacterBoostJink -= 50;
			break;
		}

	acUpdateBoost();
}

void SecondaryAppWindowPageOGL::onClickBoostRight(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	switch(g_QamSpawnInsertCharacterBoostIndex)
		{
		case 0:
			g_QamSpawnInsertCharacterBoostHealth += 50;
			break;

		case 1:
			g_QamSpawnInsertCharacterBoostCon += 50;
			break;

		case 3:
			g_QamSpawnInsertCharacterBoostDamage += 50;
			break;

		case 4:
			g_QamSpawnInsertCharacterBoostFocus += 50;
			break;

		case 5:
			g_QamSpawnInsertCharacterBoostJink += 50;
			break;
		}

	acUpdateBoost();
}

void SecondaryAppWindowPageOGL::onClickMenu(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	loadmissionpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

	if(g_Editor_ON)
		{
		if(spawnpanel().Visibility() == winrt::Windows::UI::Xaml::Visibility::Visible)
			{
			spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			if(centralpanel().Visibility() == winrt::Windows::UI::Xaml::Visibility::Visible)
				{
				centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
				spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
				}
			else
				{
				centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
				}
			}
		}
	else
		{
		if(centralpanel().Visibility() == winrt::Windows::UI::Xaml::Visibility::Visible)
			{
			centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
			spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
			}
		}
}

void SecondaryAppWindowPageOGL::onClickStartSim(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_QAM)
		{
		if(g_QamStatus != QAM_STATUS_STARTED)
			{
			centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

			g_QAM->acPrep_Launch();

			g_QamStatus = QAM_STATUS_STARTED;

			g_AI_ON = true;

			playerAV[0]->Xform.Translation.x = 0;
			playerAV[0]->Xform.Translation.y = 0;
			playerAV[0]->Xform.Translation.z = 0;

			g_VoxelGridManager->acFullRebuild();

			StartSimButton().Content(box_value(StrUsingStr("Stop Sim")));
			}
		else
			{
			if(g_Editor_ON)
				{
				spawnpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
				}

			g_QamStatus = QAM_STATUS_REFRESHED;

			g_AI_ON = false;

			StartSimButton().Content(box_value(StrUsingStr("Start Sim")));
			}
		}
}

void SecondaryAppWindowPageOGL::onClickDownLevel(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_QAM)
		{
		g_QAM->m_LevelCurrent--;

		if(g_QAM->m_LevelCurrent < 0)
			{
			g_QAM->m_LevelCurrent = 0;
			}

		g_VoxelGridManager->acFullRebuild();
		}
}

void SecondaryAppWindowPageOGL::onClickUpLevel(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_QAM)
		{
		g_QAM->m_LevelCurrent++;

		if(g_QAM->m_LevelCurrent < 0)
			{
			g_QAM->m_LevelCurrent = 0;
			}

		g_VoxelGridManager->acFullRebuild();
		}
}

void SecondaryAppWindowPageOGL::onClickPauseSim(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_QamStatus == QAM_STATUS_STARTED)
		{
		g_QamStatus = QAM_STATUS_PAUSED;

		g_AI_ON = false;

		PauseSimButton().Content(box_value(StrUsingStr("un-Pause")));
		}
	else if(g_QamStatus == QAM_STATUS_PAUSED)
		{
		g_QamStatus = QAM_STATUS_STARTED;

		g_AI_ON = false;

		PauseSimButton().Content(box_value(StrUsingStr("Pause Sim")));
		}
}

void SecondaryAppWindowPageOGL::OnClickUpdate(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(playerU[0]->m_UpdateReady)
		{
		//playerU[0]->
		Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO, true);

		playerU[0]->m_UpdateReady = false;
		}
}

void SecondaryAppWindowPageOGL::OnClickCloseLoadingText(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	loadingtextpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::onClickPlaceScaleIncPlus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceScale += 1;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_PlaceScale);

	placescaleinctextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickPlaceScaleIncMinus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_PlaceScale -= 1;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_PlaceScale);

	placescaleinctextBox().Text(StrUsingStr(f_char));

	delete f_char; acUpdateInsert();
}

void SecondaryAppWindowPageOGL::onClickIncplus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertScale += 1 * g_PlaceScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertScale);

	terraininctextBox().Text(StrUsingStr(f_char));
}

void SecondaryAppWindowPageOGL::onClickIncminus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	g_TerrainInsertScale -= 1 * g_PlaceScale;

	char* f_char = ag_ClearChar(250);
	sprintf(f_char, "%i", g_TerrainInsertScale);

	terraininctextBox().Text(StrUsingStr(f_char));
}

void SecondaryAppWindowPageOGL::onClickUpdateMode(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_TerrainInsertUpdateMode == 0)
		{
		terrainupdatemodebutton().Content(box_value(StrUsingStr("Update on command")));
		terrainupdatecommandbutton().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		g_TerrainInsertUpdateMode = 1;
		}
	else
		{
		terrainupdatemodebutton().Content(box_value(StrUsingStr("Update on click")));
		g_TerrainInsertUpdateMode = 0;
		terrainupdatecommandbutton().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageOGL::onClickUpdateCommand(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

#if 0
	acClearVoxels();

	g_VoxelGridManager->Position_Player(BiVector(-g_Position.m_X, g_Position.m_Y, g_Position.m_Z));
#endif

	//Terrain
	acUpdateTerrainInsert();
}

void SecondaryAppWindowPageOGL::onClickPlaceonPlayer(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_GameOpen)
		{
		g_PlaceInsertX = playerAV[0]->Xform.Translation.x;
		g_PlaceInsertY = playerAV[0]->Xform.Translation.y;
		g_PlaceInsertZ = playerAV[0]->Xform.Translation.z;

		char* f_char = ag_ClearChar(250);
		sprintf(f_char, "%f", g_PlaceInsertX);

		placepositionxtextBox().Text(StrUsingStr(f_char));

		char* f_char1 = new char[250];
		sprintf(f_char1, "%f", g_PlaceInsertY);

		placepositionxtextBox().Text(StrUsingStr(f_char));

		char* f_char2 = new char[250];
		sprintf(f_char2, "%f", g_PlaceInsertZ);

		placepositionxtextBox().Text(StrUsingStr(f_char));

		delete f_char; acUpdateInsert();
		}
}

void SecondaryAppWindowPageOGL::onClicknameGroupSelect(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_GameOpen)
		{
		if(g_QAM)
			{
			//...
			}
		}
}

void SecondaryAppWindowPageOGL::OnClickQO(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	// Create the URI from a string
	std::string f_URL1 = "http://www.qo.fyi?owner=";
	std::string f_URL2 = g_Wallet->GetAdr();
	std::string f_URL = f_URL1 + f_URL2;
	Uri uri(StrUsingStr(f_URL));

	// Launch the URI
	winrt::Windows::System::Launcher::LaunchUriAsync(uri);
}

void SecondaryAppWindowPageOGL::OnClickQAO(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	// Create the URI from a string
	std::string f_URL1 = "http://www.quantumangel.online";
	Uri uri(StrUsingStr(f_URL1));

	// Launch the URI
	winrt::Windows::System::Launcher::LaunchUriAsync(uri);
}

void SecondaryAppWindowPageOGL::OnClickEnterQcom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	if(g_QcomManager->m_Open == true)
		{
		g_QcomManager->m_Open = false;
		}
	else
		{
		g_QcomManager->m_Open = true;

		g_QcomManager->m_current_X = 0.0f;
		g_QcomManager->m_current_Y = 0.0f;

		g_QcomManager->m_current_Zoom = 0.0f;
		}
}

void SecondaryAppWindowPageOGL::OnClickWindow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	if(g_QcomManager)
		{
		if(g_QcomManager->m_Open == true)
			{
			g_QcomManager->m_PointerCharge = true;
			}
		}
}

void SecondaryAppWindowPageOGL::OnReleaseWindow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	if(g_QcomManager)
		{
		if(g_QcomManager->m_Open)
			{
			if(g_QcomManager->m_PointerCharge)
				{
				g_QcomManager->ac_FireLTClick();
				g_QcomManager->m_PointerCharge = false;
				}

			g_QcomManager->m_drag_on = false;
			}
		}
}

void SecondaryAppWindowPageOGL::OnMovedWindow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	if(g_QcomManager)
		{
		if(g_QcomManager->m_Open)
			{
			if(g_QcomManager->m_PointerCharge)
				{
				winrt::Windows::UI::Input::PointerPoint f_PointerPoint = e.GetCurrentPoint(itemspanel());

				g_QcomManager->ac_DragGrid(f_PointerPoint.Position().X, f_PointerPoint.Position().Y * -1);
				}
			}
		}
}

	/////////////////////
   // Open and pipe
  // qtx
 // pass on owner
//
void SecondaryAppWindowPageOGL::OnClickOpenLogin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	loginStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
}

void SecondaryAppWindowPageOGL::acFillLogin(void)
{
	char* txquery = ag_ClearChar(1000);
	sprintf(txquery, "SELECT username, password, dated FROM qlogin WHERE owner = '%s' ORDER BY dated DESC LIMIT 1", g_Wallet->GetAdr().c_str());

	g_SafeL[2]->acSelectCommand(txquery, false, false);
	delete txquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		std::string f_Username = g_Schedular[2]->acEntry(0)[0];
		std::string f_Password = g_Schedular[2]->acEntry(0)[1];

		logintextBox().Text(StrUsingStr(f_Username));
		passwordtextBox().Text(StrUsingStr(f_Password));
		}
	else
		{
		logintextBox().Text(L"");
		passwordtextBox().Text(L"");
		}
}

void SecondaryAppWindowPageOGL::acSaveLogin(std::string f_Username, std::string f_Password)
{
#ifdef QLOGON_SAVE_EACH
	char* f_loginfield[3];
	char* f_loginvalue[3];

	for(int f_Count = 0; f_Count < 3; f_Count++)
		{
		f_loginfield[f_Count] = (char*)malloc(sizeof(char) * 512);
		f_loginvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
		}

	sprintf(f_loginfield[0], "owner");
	sprintf(f_loginfield[1], "username");
	sprintf(f_loginfield[2], "password");

	sprintf(f_loginvalue[0], "%s", g_Wallet->GetAdr().c_str());
	sprintf(f_loginvalue[1], "%s", f_Username.c_str());
	sprintf(f_loginvalue[2], "%s", f_Password.c_str());

	int f_loginUniqueID = g_SafeL[2]->Insert("qlogin", (const char **)f_loginfield, (const char **)f_loginvalue, 3, false, false);

	for(int f_Count = 0; f_Count < 3; f_Count++)
		{
		free(f_loginfield[f_Count]);
		free(f_loginvalue[f_Count]);
		}
#endif
}

void SecondaryAppWindowPageOGL::OnClickLoadUsualLogin(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	acFillLogin();
}

void SecondaryAppWindowPageOGL::OnClickEXTRA(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	// Create the URI from a string
	std::string f_URL1 = "http://www.ecn.world";
	Uri uri(StrUsingStr(f_URL1));

	// Launch the URI
	winrt::Windows::System::Launcher::LaunchUriAsync(uri);
}

void SecondaryAppWindowPageOGL::OnClickBITOLYL(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_KeyName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_KeyName);

	// Create the URI from a string
	std::string f_URL1 = "http://www.bitolyl.com";
	Uri uri(StrUsingStr(f_URL1));

	// Launch the URI
	winrt::Windows::System::Launcher::LaunchUriAsync(uri);
}

	//QUANTUM PORTION

void SecondaryAppWindowPageOGL::OnClickOpenAppBar(void)
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

void SecondaryAppWindowPageOGL::OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel sender, IInspectable args)
{
	EGLint panelWidth = 1920;
	EGLint panelHeight = 1080;

	//g_OpenGLES.GetSurfaceDimensions(g_RenderSurface, &panelWidth, &panelHeight);

	// Logic to update the scene could go here
	g_SimpleRenderer->UpdateWindowSize(panelWidth, panelHeight);

	g_Width = panelWidth;
	g_Height = panelHeight;
}

void SecondaryAppWindowPageOGL::OnSwapChainPanelSizeChanged(IInspectable sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs e)
{
	EGLint panelWidth = 1920;
	EGLint panelHeight = 1080;

	//g_OpenGLES.GetSurfaceDimensions(g_RenderSurface, &panelWidth, &panelHeight);

	// Logic to update the scene could go here
	g_SimpleRenderer->UpdateWindowSize(panelWidth, panelHeight);

	g_Width = panelWidth;
	g_Height = panelHeight;

}

auto CreateComboBoxItem = [](hstring const& name, IInspectable const& tag = nullptr)
{
	Windows::UI::Xaml::Controls::ComboBoxItem item;

	item.Content(box_value(name));
	item.Tag(tag);

	return item;
};

void SecondaryAppWindowPageOGL::OnKeyDownInsertSearch(IInspectable sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs e)
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

void SecondaryAppWindowPageOGL::OnSelectInsertTypeCombo(IInspectable sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs e)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::OnSelectInsertTypeCombo";

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

void SecondaryAppWindowPageOGL::DisplayInterfaceCom(std::shared_ptr<Cube::Qcom> f_Com)
{
	std::string f_INL;

	f_INL.clear();

	for(int f_XY = 0; f_XY < f_Com->m_genScript->m_vec_InitLineOrdered.size(); f_XY++)
		{
		f_INL += f_Com->m_genScript->m_vec_InitLineOrdered[f_XY] + ::std::string("\n");
		}

	insertscripttextBox().Text(StrUsingStr(f_INL));
}

	fire_and_forget SecondaryAppWindowPageOGL::OnClickOpenPredator(void)
	{
		auto lifetime = get_strong();

		// Create a new window
		appWindowPredator = co_await AppWindow::TryCreateAsync();
		// Clean up when the window is closed
		appWindowPredator.Closed({ get_weak(), &SecondaryAppWindowPageOGL::OnPredatorWindowClosed });
		// Navigate the frame to the page we want to show in the new window
		appWindowFrame.Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPagePredator>());
		// Attach the XAML content to our window
		ElementCompositionPreview::SetAppWindowContent(appWindowPredator, appWindowFrame);

		co_await appWindowPredator.TryShowAsync();
	}

	void SecondaryAppWindowPageOGL::OnPredatorWindowClosed(winrt::Windows::UI::WindowManagement::AppWindow const&, winrt::Windows::Foundation::IInspectable const&)
	{
		//...
	}

	void SecondaryAppWindowPageOGL::OnClosed(winrt::CoreWindow sender, winrt::Windows::UI::Core::CoreWindowEventArgs e)
	{
		//...
	}

	fire_and_forget SecondaryAppWindowPageOGL::OnClickBuyComponent(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickInsertInsert(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::OnClickInsertInsert";

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

	void SecondaryAppWindowPageOGL::OnClickIncludeComponent(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::Frame_OnCount(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable e)
	{
		std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPageOGL::Frame_OnCount";

		if(g_WalletOpen == true)
			{
			if(g_Schedular[1]->acPopulusIsFull() == true)
				{
				if(m_Frame_OnCount == false)
					{
					m_Frame_OnCount = true;

					time(&g_Currtime);

					int f_Double = g_Currtime - g_Storetime;
		#
					 ///////////
					// ecoin //
					g_EcoinDifficulty = 100;
					g_AverageSaleValue = 300;

					g_EVALUE = g_AverageSaleValue;

					//FrameRate per Second
					char* f_CharFR = ag_ClearChar(255);

					::sprintf(f_CharFR, "FrameRate %i/s", g_curfps);

					std::string f_StringFR = f_CharFR;

					delete f_CharFR;

					framerateTextBlock().Text(StrUsingStr(f_StringFR));
							
					//TimeScale per Second
					char* f_CharJK = ag_ClearChar(255);

					::sprintf(f_CharJK, "TimeScale %.4f 1/Frame/s", _->TimeScale);

					std::string f_StringJK = f_CharJK;

					delete f_CharJK;

					timescaleTextBlock().Text(StrUsingStr(f_StringJK));

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

								/////////////////////
							//  Wallet Balance //
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

							 /////////////
							// balance //
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
					}
				}
			else
				{
				g_Schedular[1]->acScheduleUpdator();
				}
			}
	}

	bool SecondaryAppWindowPageOGL::ConfigureSimulatorAsync(bool f_Bool)
	{
		auto f_BoolResult = ConfigSim(f_Bool);

		return true;
	}

	std::future<bool> SecondaryAppWindowPageOGL::ConfigSim(bool f_Bool)
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

	std::future<bool> SecondaryAppWindowPageOGL::acSaveFileBuffer(std::string f_Buffer)
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

	void SecondaryAppWindowPageOGL::OnWalletClick(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

		OnClickOpenGrid();

#if 0   // in use and usable
		if(appWindowPredator == nullptr)
			{
			OnClickOpenPredator();
			}

		OnClickOpenAppBar();
#endif
	}

	void SecondaryAppWindowPageOGL::OnHeshtextClick(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		heshText().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
		heshButton().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	}

	void SecondaryAppWindowPageOGL::OnClickWithDraw(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickBuy(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);
	}

	void SecondaryAppWindowPageOGL::onClickVoteUp(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::acProcessAckMessage(std::shared_ptr<Ackent> f_Ack)
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
	void SecondaryAppWindowPageOGL::acLoadShare(int f_LShare, int f_ServLay)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::acLoadShare";

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

			swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this, f_ShareContainer]()
				{
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

					char f_Char[255];
					char numbuf5[100];
					_itoa(g_espo_ShareOffset, numbuf5, 10);
					std::string f_interim5 = numbuf5;

					owninfotextBlock().Text(StrUsingStr("on #" + f_interim5));

					char numbuf6[100];
					_itoa(g_espo_Peer, numbuf6, 10);
					std::string f_interim6 = numbuf6;

					ownpeertextBlockf().Text(StrUsingStr("peer #" + f_interim6));

					char numbuf10[100];
					_itoa(g_espo_ShareOffset, numbuf10, 10);
					std::string f_interim4 = numbuf10;

					ownsharetextBlock().Text(StrUsingStr("on share #" + f_interim4));

					char numbuf7[100];
					_itoa(g_espo_Peer, numbuf7, 10);
					std::string f_interim7 = numbuf7;

					ownpeertextBlock().Text(StrUsingStr(f_interim7));

					ownerinfoBlock().Text(StrUsingStr(g_espo_Owner));

					char numbuf88[100];
					_itoa(g_espo_Score, numbuf88, 10);
					std::string f_interim88 = numbuf88;

					voteinfoBlock().Text(StrUsingStr(f_interim88));

					FillChar(f_Char, 255);

					sprintf_s(f_Char, "%.4f ECN", (float)g_espo_Amount);
					std::string f_String13 = f_Char;

					pledgeinfoBlock().Text(StrUsingStr(f_String13));

					FillChar(f_Char, 255);

					sprintf_s(f_Char, "%.8f ECN", (float)g_espo_ECN_Amount);
					std::string f_String14 = f_Char;

					ecnpledgeinfoBlock().Text(StrUsingStr(f_String14));

					dateinfoBlock().Text(StrUsingStr(g_espo_Date));
					}
				});
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

			swapChainPanel().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this, f_ShareContainer]()
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

				char f_Char[255];
				char numbuf5[100];
				_itoa(g_espo_ShareOffset, numbuf5, 10);
				std::string f_interim5 = numbuf5;

				owninfotextBlock().Text(StrUsingStr("on #" + f_interim5));

				char numbuf6[100];
				_itoa(g_espo_Peer, numbuf6, 10);
				std::string f_interim6 = numbuf6;

				ownpeertextBlockf().Text(StrUsingStr("peer #" + f_interim6));

				char numbuf10[100];
				_itoa(g_espo_ShareOffset, numbuf10, 10);
				std::string f_interim4 = numbuf10;

				ownsharetextBlock().Text(StrUsingStr("on share #" + f_interim4));

				char numbuf7[100];
				_itoa(g_espo_Peer, numbuf7, 10);
				std::string f_interim7 = numbuf7;

				ownpeertextBlock().Text(StrUsingStr(f_interim7));

				ownerinfoBlock().Text(StrUsingStr(g_espo_Owner));

				char numbuf88[100];
				_itoa(g_espo_Score, numbuf88, 10);
				std::string f_interim88 = numbuf88;

				voteinfoBlock().Text(StrUsingStr(f_interim88));

				FillChar(f_Char, 255);

				sprintf_s(f_Char, "%.4f ECN", (float)g_espo_Amount);
				std::string f_String13 = f_Char;

				pledgeinfoBlock().Text(StrUsingStr(f_String13));

				FillChar(f_Char, 255);

				sprintf_s(f_Char, "%.8f ECN", (float)g_espo_ECN_Amount);
				std::string f_String14 = f_Char;

				ecnpledgeinfoBlock().Text(StrUsingStr(f_String14));

				dateinfoBlock().Text(StrUsingStr(g_espo_Date));
				});
			}

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

	void SecondaryAppWindowPageOGL::onClickPrevShare(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickNextShare(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickPeer(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickPeerMinus(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickMilliPeer(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickMilliPeerMinus(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickLookAt(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

		if(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW)
			{
			g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_VIEWING;

			lookatButton().Content(box_value(L"CLICK\n4 shares"));

			eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			currentStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
		else
			{
			g_Wallet->m_vec_MainMode[m_IDX] = ECOIN_MODE_NONVIEW;

			eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

			lookatButton().Content(box_value(L"CLICK\n4 viewing"));

			OnRefreshEslCodeStack();
			}
	}

	void SecondaryAppWindowPageOGL::OnRefreshEslCodeStack(void)
	{
		eslcoderesulttextBlock().Text(L"Please enter Tag, Name and description. Limit total characters 3000.");

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

			::sprintf(f_Char2, "%f", g_Wallet->m_vec_scoremax[m_IDX]);

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

	void SecondaryAppWindowPageOGL::OnClickShowTransaction(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickBack(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickNext(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnFillTargets(void)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::OnFillTargets";

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

	void SecondaryAppWindowPageOGL::OnClickSend(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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


	void SecondaryAppWindowPageOGL::OnClickNewAddress(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickNextos(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickPreviousBlock(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickWinningShare(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::onClickOwnPeer(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickQcom(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnRightClickWindow(IInspectable sender, winrt::Windows::UI::Xaml::Input::RightTappedRoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickShowWithdraw(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickShowDeposit(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickBuy5GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY5", 5);
	}

	void SecondaryAppWindowPageOGL::OnClickBuy10GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY10", 10);
	}

	void SecondaryAppWindowPageOGL::OnClickBuy20GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY20", 20);
	}

	void SecondaryAppWindowPageOGL::OnClickBuy50GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY50", 50);
	}

	void SecondaryAppWindowPageOGL::OnClickBuy100GBP(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		OnBuyGBP("ECOIN_CPS_BUY100", 100);
	}

	std::future<bool> SecondaryAppWindowPageOGL::OnBuyGBP(std::string f_ProductID, int f_IntAmt)
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

	std::future<bool> SecondaryAppWindowPageOGL::acFullfill(winrt::hstring f_ProdId, winrt::guid f_TransactionId, bool f_QuickFullFill)
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

	void SecondaryAppWindowPageOGL::OnClickWithDrawCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickeslcodeClose(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		if(eslcodeStack().Visibility() == Windows::UI::Xaml::Visibility::Visible)
			{
			eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
			}
	}

	void SecondaryAppWindowPageOGL::OnClickeslcodeCheck(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickeslcodeStart(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ref_CurrentPath = "SecondaryAppWindowPageOGL::OnClickeslcodeStart";

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
						ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

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
						ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

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

							ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

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

						ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

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

	void SecondaryAppWindowPageOGL::OnClickShareShop(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickShopSearch(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopsearchprev(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopsearchnext(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopownproducts(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickProductsBought(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

	void SecondaryAppWindowPageOGL::OnRefreshShop(void)
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

	void SecondaryAppWindowPageOGL::OnClickOpenProductA1(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductA2(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductA3(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));
				
					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductA4(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductA5(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductA6(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductB1(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductB2(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductB3(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductB4(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductB5(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickOpenProductB6(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

				g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
					{
					Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 100, 255, 90));

					insertinsertbutton().BorderBrush(myBrush);
					});
				}
			}
	}

	void SecondaryAppWindowPageOGL::OnClickCurrentSkip(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_LowtonMark = 10000000.0f;

		time(&g_storagetime);
		g_storagetime += LOWTON_STORAGE;
	}

	void SecondaryAppWindowPageOGL::OnClickCurrentKeep(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopA1PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopA2PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopA3PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopA4PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopA5PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopA6PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopB1PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopB2PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopB3PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopB4PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopB5PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickshopB6PayCPS(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickDecisions(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickDecisionUp(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(0.0f, 1.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageOGL::OnClickDecisionRight(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(1.0f, 0.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageOGL::OnClickDecisionLeft(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(-1.0f, 0.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageOGL::OnClickDecisionDown(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
	{
		std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

		acClick(f_ButtonName);

		g_vec_DecisionsManager[0]->m_Wheel->acReposition(BiVector(0.0f, -1.0f, 0.0f));

		acRefreshSelectionInfo();
	}

	void SecondaryAppWindowPageOGL::OnClickDecisionIn(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickDecisionOut(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

	void SecondaryAppWindowPageOGL::OnClickComFunction(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

#if 1
		///////////////////////////////////////////
	   // Ecom Building Generation Script
	  //
	void SecondaryAppWindowPageOGL::acBuild_ExcomPackaging(void)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::acBuild_ExcomPackaging";

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

											f_ecomButton.Click({ this, &SecondaryAppWindowPageOGL::OnClickComFunction });

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
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.Foreground(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Background") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.Background(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("BorderBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.BorderBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomButton.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

													Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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
											//f_ecomStackPanel.Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("Background") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomStackPanel.Background(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("BorderBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomStackPanel.BorderBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomStackPanel.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

													Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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
											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

											for(int f_Jet = 0; f_Jet < f_Packet->m_vecvec_Package_Arg_Data[f_IDX].size(); f_Jet++)
												{
												if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("Background") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomGrid.Background(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("BorderBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomGrid.BorderBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_ecomGrid.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

													Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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

											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

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
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.Foreground(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("SelectionHighlightColor") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.SelectionHighlightColor(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBlock.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vec_Package_XElement_Title[f_XY].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

													Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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

											//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

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
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.Foreground(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("SelectionHighlightColor") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.SelectionHighlightColor(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

													Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

													f_TextBox.FocusVisualPrimaryBrush(myBrush);
													}
												else if(f_Packet->m_vecvec_Package_Arg_Title[f_IDX][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
													{
													string f_Hex = f_Packet->m_vecvec_Package_Arg_Data[f_IDX][f_Jet];
													string f_A = "";
													f_A.push_back(f_Hex.at(1));
													f_A.push_back(f_Hex.at(2));
													std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
													string f_R = "";
													f_R.push_back(f_Hex.at(1));
													f_R.push_back(f_Hex.at(2));
													std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
													string f_G = "";
													f_G.push_back(f_Hex.at(1));
													f_G.push_back(f_Hex.at(2));
													std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
													string f_B = "";
													f_B.push_back(f_Hex.at(1));
													f_B.push_back(f_Hex.at(2));
													std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

													Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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
													//g_ecomStackPanel.Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

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
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

													f_new_ecomButton.Click({ this, &SecondaryAppWindowPageOGL::OnClickComFunction });

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
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.Foreground(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Background") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.Background(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("BorderBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.BorderBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_new_ecomButton.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

															Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });
															
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
													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Background") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.Background(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("BorderBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.BorderBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Stack.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

															Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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
													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

													for(int f_Jet = 0; f_Jet < f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY].size(); f_Jet++)
														{
														if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("Background") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.Background(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("BorderBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.BorderBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_Grid.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

															Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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

													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

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
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.Foreground(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("SelectionHighlightColor") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.SelectionHighlightColor(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBlock.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

															Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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

													//f_Stack->Click += ref new RoutedEventHandler(this, SecondaryAppWindowPageOGL::OnClickComFunction);

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
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.Foreground(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("SelectionHighlightColor") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.SelectionHighlightColor(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualPrimaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

															Windows::UI::Xaml::Media::SolidColorBrush myBrush({ Windows::UI::ColorHelper::FromArgb((unsigned char)f_A_byte, (unsigned char)f_R_byte, (unsigned char)f_G_byte, (unsigned char)f_B_byte) });

															f_TextBox.FocusVisualPrimaryBrush(myBrush);
															}
														else if(f_PacketLP->m_vecvec_Package_Arg_Title[f_IDY][f_Jet].compare("FocusVisualSecondaryBrush") == 0)
															{
															string f_Hex = f_PacketLP->m_vecvec_Package_Arg_Data[f_IDY][f_Jet];
															string f_A = "";
															f_A.push_back(f_Hex.at(1));
															f_A.push_back(f_Hex.at(2));
															std::byte f_A_byte = HexToByteUsingByteManipulation_ogl(f_A);
															string f_R = "";
															f_R.push_back(f_Hex.at(1));
															f_R.push_back(f_Hex.at(2));
															std::byte f_R_byte = HexToByteUsingByteManipulation_ogl(f_R);
															string f_G = "";
															f_G.push_back(f_Hex.at(1));
															f_G.push_back(f_Hex.at(2));
															std::byte f_G_byte = HexToByteUsingByteManipulation_ogl(f_G);
															string f_B = "";
															f_B.push_back(f_Hex.at(1));
															f_B.push_back(f_Hex.at(2));
															std::byte f_B_byte = HexToByteUsingByteManipulation_ogl(f_B);

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

															Thickness myThickness({ atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()), atodie(f_vec_Pack_A1.c_str()) });

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

	void SecondaryAppWindowPageOGL::OnClickSaveComplete(IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::OnClickSaveComplete";

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

#if 0
		::g_QcomManager->m_Qcom = f_com;
#endif

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
bool SecondaryAppWindowPageOGL::qtx_Send(std::string f_A, std::string f_B, float f_Amt)
{
	transactionA().Text(StrUsingStr(f_A));

	transactionB().Text(StrUsingStr(f_B));

	float f_amt = f_Amt;

	char* f_char = ag_ClearChar(250);
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

void SecondaryAppWindowPageOGL::clearTXDisplay(void)
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

void SecondaryAppWindowPageOGL::StartTXD(void)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::StartTXD";

	if(!txd_on_ogl)
		{
		txd_on_ogl = true;

		g_TXD_Scan = true;

#if 0
		qtx_Update();
#endif
		}
	else
		{
		txd_on_ogl = false;

		g_TXD_Scan = false;
		}
}

void SecondaryAppWindowPageOGL::qtx_Update(void)
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

bool SecondaryAppWindowPageOGL::qtx_Results(void)
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

					char* f_char = ag_ClearChar(250);
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

void SecondaryAppWindowPageOGL::OnClickFloatTXD(winrt::Windows::Foundation::IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_TXD_Position_ogl++;
	if(g_TXD_Position_ogl >= 4)
		{
		g_TXD_Position_ogl = 0;
		}

	if(g_TXD_Position_ogl == 0)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Left);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Top);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 386, 593, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		}
	else if(g_TXD_Position_ogl == 1)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Right);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Top);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 0, 90, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
	else if(g_TXD_Position_ogl == 2)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Right);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Bottom);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 0, 0, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
	else if (g_TXD_Position_ogl == 3)
		{
		transactionExplorerStack().HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Left);
		transactionExplorerStack().VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Bottom);
		transactionExplorerStack().Margin(winrt::Windows::UI::Xaml::Thickness({ 0, 0, 0, 0 }));
		transactionStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
		}
}

void SecondaryAppWindowPageOGL::OnClickSuccessClose(winrt::Windows::Foundation::IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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
void SecondaryAppWindowPageOGL::OpenTXD(std::string f_Recipient, float f_Amt)
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

void SecondaryAppWindowPageOGL::CloseTXD(void)
{
	g_TXD_Scan = false;
}

void SecondaryAppWindowPageOGL::OnClickCloseTXD(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

void SecondaryAppWindowPageOGL::OnClickTXDpreview(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_TXD_Preview_ogl = true;
}

void SecondaryAppWindowPageOGL::acTXReal(void)
{
	//g_TXD_Scan = true

	float f_TX_Amount = atof(to_string(transactionamt().Text()).c_str());

	float f_TX_Result = f_TX_Amount * 1.01f;

}

void SecondaryAppWindowPageOGL::OnClickOpenWalletPrint(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
		{
		ecoinwalletStack().Visibility(Windows::UI::Xaml::Visibility::Visible);

		acRefreshWalletPrint();
		});
}

void SecondaryAppWindowPageOGL::OnClickRefreshWalletPrint(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	acRefreshWalletPrint();
}

void SecondaryAppWindowPageOGL::acRefreshWalletPrint(void)
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

void SecondaryAppWindowPageOGL::OnClickCloseWalletPrint(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	ecoinwalletStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::OnClickCloseSaveComplete(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	lookatButton().Content(box_value(L"CLICK\n4 shares"));

	eslcodeStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	currentStack().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::OnClickOpenTXD(IInspectable sender, winrt::Windows::UI::Xaml::RoutedEventArgs e)
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

void SecondaryAppWindowPageOGL::OnValueChangedSaveCompletePublishSlider(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickSelectStack(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickSelectSelect(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickAction(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::acRefreshDecisionsPanel(void)
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

void SecondaryAppWindowPageOGL::acRefreshSelectionInfo(void)
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

void SecondaryAppWindowPageOGL::OnClickSelectUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acSelectionGrow(BiVector(0.0f, 5.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickSelectRight(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acSelectionGrow(BiVector(5.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickSelectLeft(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acSelectionGrow(BiVector(-5.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickSelectDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->acSelectionGrow(BiVector(0.0f, -5.0f, 0.0f));

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickSelectIn(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->acPressIn();

	f_WHL->acSelectionGrow(BiVector(0.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}


void SecondaryAppWindowPageOGL::OnClickSelectOut(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	f_WHL->acPressOut();

	f_WHL->acSelectionGrow(BiVector(0.0f, 0.0f, 0.0f));

	acRefreshSelectionInfo();
}


void SecondaryAppWindowPageOGL::OnClickSelectMode(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}


void SecondaryAppWindowPageOGL::OnClickSelectAdditive(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnClickSelectPrevious(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickSelectNext(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickSelectRecall(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickDecisionsTop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acClear();

	g_vec_DecisionsManager[0]->m_Wheel->m_LayerPos = 0;
	g_vec_DecisionsManager[0]->m_Wheel->m_Layer = -1;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickdecisionsLayerZero(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->acClear();

	::g_QcomManager->m_Qcom = ::g_QcomManager->mam_Qcom;

	g_vec_DecisionsManager[0]->m_Wheel->m_LayerPos = 0;
	g_vec_DecisionsManager[0]->m_Wheel->m_Layer = 0;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickdecisionsLastDecisionCom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPreviousDecision(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickNextDecision(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickDecision1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_vec_DecisionsManager[0]->m_Wheel->m_DecisionIndex = 0;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickDecisionCom(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnClickDecisionClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

	g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_Visible = false;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickDecisionsUndo(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	std::shared_ptr<BiDecisionA> f_UndoAnswer = g_vec_DecisionsManager[0]->m_UnDo[g_vec_DecisionsManager[0]->m_UnDo.size() - 1];

	g_vec_DecisionsManager[0]->m_vec_DecisionQ[g_vec_DecisionsManager[0]->m_Wheel->m_SelectionIndex]->m_vec_DecisionA.push_back(f_UndoAnswer);
	g_vec_DecisionsManager[0]->m_Wheel->m_DecisionIndex = g_vec_DecisionsManager[0]->m_vec_DecisionQ[g_vec_DecisionsManager[0]->m_Wheel->m_SelectionIndex]->m_vec_DecisionA.size() - 1;

	acRefreshSelectionInfo();
}

void SecondaryAppWindowPageOGL::OnClickdecisionsApply(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickSelectSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::OnClickSelectSave";

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

void SecondaryAppWindowPageOGL::OnSCP_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnSCP_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnSCP_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::PointerEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnSwap_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnSwap_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnSwap_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickApplyNumber(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickIncreaseCompressionHigh(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnValueChangedSaveCompressionSlider(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPlaceVector(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPlaceInNewGrid(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickExecuteNew(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickIncreaseSCPThreadsHigh(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnEventExecuteImmediatly(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	if(g_PreComInclude == false)
		{
		bool f_hasBought = g_Wallet->acGet_assetContractbyID(g_ShuttleCom->m_Cost, g_ShuttleCom->m_ID);

		if(f_hasBought == true) //win 1
			{
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

			g_ShuttleCom->ac_Execute();
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

		Windows::UI::Xaml::Media::SolidColorBrush myBrush(Windows::UI::ColorHelper::FromArgb(255, 200, 255, 90));

		insertinsertbutton().BorderBrush(myBrush);

		eventStackPanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

		g_ShuttleCom->ac_Execute();
		}
}

void SecondaryAppWindowPageOGL::OnClickPlaceInCurrentGrid(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPlaceInstall(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPayBuyOnce(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	bool f_hasBought = g_Wallet->acBuy_ShareComID(g_ShuttleCom->m_ID, g_ShuttleCom->m_Cost, g_ShuttleCom->m_Cost, g_ShuttleCom->m_PackageShareID);

	if(f_hasBought == true)
		{
		//...win conditions
		}
}

void SecondaryAppWindowPageOGL::OnClickPayBuyAmount(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPayJoinMembership(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPayBuyBundle(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPayZeroNow(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickIncludeProfitEngRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageOGL::ONClickIncludeLimitedRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageOGL::OnClickIncludeMembershipRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageOGL::OnClickIncludeGroupRef(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	g_PreComInclude = true;
}

void SecondaryAppWindowPageOGL::OnClickClosePauseMinimizebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickPutToBackbutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickIgnoreClosebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickCancelClosebutton(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickLogOut(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::OnClickLogOut";

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

void SecondaryAppWindowPageOGL::OnClickStorePolicy(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	// Create the URI from a string
	std::string f_URL = "http://www.osirem.com/affiliate/osi_privacy_policy.html";

	Uri uri({ StrUsingStr(f_URL) });

	// Launch the URI
	Windows::System::Launcher::LaunchUriAsync(uri);
}

void SecondaryAppWindowPageOGL::OnClicktandc(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	// Create the URI from a string
	std::string f_URL = "http://www.osirem.com/affiliate/t&c.html";

	Uri uri({ StrUsingStr(f_URL) });

	// Launch the URI
	Windows::System::Launcher::LaunchUriAsync(uri);
}

void SecondaryAppWindowPageOGL::OnClickStopAll(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnLoadPledgeStack(void)
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

void SecondaryAppWindowPageOGL::OnClickPledgeSynchronize(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageOGL::acLoadShare";

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
					ag_Freshanon<int>(g_Wallet->m_vec_maxpledge, m_IDX, 0);

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

void SecondaryAppWindowPageOGL::OnClickPledgeClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	//make visible the pledge system
	pledgeStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::OnClickPledgesOn(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::acRefreshJob(void)
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

void SecondaryAppWindowPageOGL::acRefreshJobVar(void)
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

void SecondaryAppWindowPageOGL::OnClickPreviousJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnClickNextJobVar(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

void SecondaryAppWindowPageOGL::OnJobVarInvalidateSave(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
	if(m_IDX < g_Wallet->m_vec_jobvar_index[m_IDX].size())
		{
		g_Wallet->m_vec_jobvar_save[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = true;
		g_Wallet->m_vec_jobvar_textupdate[m_IDX][g_Wallet->m_vec_jobvar_current_index[m_IDX]] = true;
		}
}

void SecondaryAppWindowPageOGL::OnClickTypePrefixHelp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnSwapKeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::KeyEventArgs const& e)
{
	if(g_GameFocusOn == true)
		{
		int f_KeyCodePressed = (int)e.VirtualKey();

		g_Qy[f_KeyCodePressed] = true;
	
		bool f_Found = false;
		for(int f_Jet = 0; f_Jet < g_vec_Qy_ok.size(); f_Jet++)
			{
			if(g_vec_Qy_ok[f_Jet] == f_KeyCodePressed)
				{
				f_Found = true;
				f_Jet < g_vec_Qy_ok.size();
				}
			}

		if(f_Found == false)
			{
			g_vec_Qy_ok.push_back(f_KeyCodePressed);
			}

#ifdef KEYOFF_CHECKER_ONLY
		bool f_Found = false;
		for(int f_Jet = 0; f_Jet < g_vec_Qy.size(); f_Jet++)
			{
			if(g_vec_Qy[f_Jet] == f_KeyCodePressed)
				{
				f_Found = true;
				f_Jet = g_vec_Qy.size();
				}
			}

		if(f_Found == false)
			{
			g_vec_Qy.push_back(f_KeyCodePressed);
			}
#endif
		}
}

void SecondaryAppWindowPageOGL::OnSwapKeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Core::KeyEventArgs const& e)
{
	if(g_GameFocusOn == true)
		{
		int f_KeyCodePressed = (int)e.VirtualKey();

		g_Qy[f_KeyCodePressed] = false;

#ifdef KEYOFF_CHECKER_ONLY
		int f_Index = -1;
		for(int f_Jet = 0; f_Jet < g_vec_Qy.size(); f_Jet++)
			{
			if(g_vec_Qy[f_Jet] == f_KeyCodePressed)
				{
				f_Index = f_Jet;
				f_Jet = g_vec_Qy.size();
				}
			}

		if(f_Index > 0)
			{
			for(int f_Helly = f_Index; f_Helly < g_vec_Qy.size() - 1; f_Helly++)
				{
				g_vec_Qy[f_Helly] = g_vec_Qy[f_Helly + 1];
				}

			g_vec_Qy.pop_back();
			}
#endif
		}
}

void SecondaryAppWindowPageOGL::OnClickCentralClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	centralpanel().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::OnClickLoginClose(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	loginStack().Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
}

void SecondaryAppWindowPageOGL::OnClickCreateAngel(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);

	Q.CreateAngelData();
}

void SecondaryAppWindowPageOGL::OnClickExploreAngels(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnClickViewStats(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnClickTradableLicenses(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnClickItemBank(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnClickAngelTrade(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	std::string f_ButtonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

	acClick(f_ButtonName);
}

void SecondaryAppWindowPageOGL::OnGotFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	g_GameFocusOn = false;
}

void SecondaryAppWindowPageOGL::OnLostFocusG(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	g_GameFocusOn = true;
}

};