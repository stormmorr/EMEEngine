/*

ecoinMain.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include <iostream>

#include "SecondaryAppWindowPageDX.h"

#include "Include/Cube.h"

#include "Code/Work/Contract.h"
#include "Code/Work/Schedular.h"

#include "Code/Cube/qcom.h"
#include "Code/CLS/Target.h"
#include "ecoinMain.h"
#include "Common\DirectXHelper.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>

int g_Timer = 1;
extern int g_EventID;

using namespace Cube;
using namespace ecoin;

winrt::Windows::UI::Xaml::Controls::Button g_PrevButton({ nullptr });

namespace ecoin
{

// Loads and initializes application assets when the application is loaded.
ecoinMain::ecoinMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_pointerLocationX(0.0f), m_Rendering(false)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "ecoinMain::ecoinMain";

	m_deviceResources = deviceResources;

	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	// TODO: Replace this with your app's content initialization.
	m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer(m_deviceResources));

	m_fpsTextRenderer = std::unique_ptr<SampleFpsTextRenderer>(new SampleFpsTextRenderer(m_deviceResources));

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:

	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);

	//###==- Seed the random number generator -==###//
	g_TimeStamp = GetTickCount64();
	srand(15378687);

	Cube::g_RandomSeed.x = 1245.3454; //(250.0f * sin((double)g_TimeStamp / 55000)) - 125.0f;
	Cube::g_RandomSeed.y = 245.3454; //sin((double)g_TimeStamp) * cos((double)g_TimeStamp);
	Cube::g_RandomSeed.z = 45.3454; //1433.567 * tan((double)g_TimeStamp);

	m_sceneRenderer->m_cnt_SCP_Thread = 0;
	m_sceneRenderer->m_cnt_DIV_Thread = 0;

#ifndef OSI_MEM_APP
	ag_Push(g_KeepShare, f_ref_CurrentPath + g_ref_global_Div + "g_KeepShare");
	ag_Push(g_Found_Share, f_ref_CurrentPath + g_ref_global_Div + "g_Found_Share");
	ag_Push(g_Found_Block, f_ref_CurrentPath + g_ref_global_Div + "g_Found_Block");
	ag_Push(g_Found_Msg, f_ref_CurrentPath + g_ref_global_Div + "g_Found_Msg");
	ag_Push(g_CoolDown, f_ref_CurrentPath + g_ref_global_Div + "g_CoolDown");
	ag_Push(g_CoolBoost, f_ref_CurrentPath + g_ref_global_Div + "g_CoolBoost");
	ag_Push(g_PEERCNT, f_ref_CurrentPath + g_ref_global_Div + "g_PEERCNT");
	ag_Push(g_SHARECNT, f_ref_CurrentPath + g_ref_global_Div + "g_SHARECNT");
	ag_Push(g_GameOpen, f_ref_CurrentPath + g_ref_global_Div + "g_GameOpen");
	ag_Push(g_Editor_ON, f_ref_CurrentPath + g_ref_global_Div + "g_Editor_ON");
	ag_Push(g_CopyStackPageN, f_ref_CurrentPath + g_ref_global_Div + "g_CopyStackPageN");
	ag_Push(g_BoardPushHeightAdjust, f_ref_CurrentPath + g_ref_global_Div + "g_BoardPushHeightAdjust");
	ag_Push(g_ComPositionToPoint2fFactor, f_ref_CurrentPath + g_ref_global_Div + "g_ComPositionToPoint2fFactor");
	ag_Push(g_ComICOPositionToComPositionX, f_ref_CurrentPath + g_ref_global_Div + "g_ComICOPositionToComPositionX");
	ag_Push(g_ComICOPositionToComPositionY, f_ref_CurrentPath + g_ref_global_Div + "g_ComICOPositionToComPositionY");
	ag_Push(g_CarriageReturnX, f_ref_CurrentPath + g_ref_global_Div + "g_CarriageReturnX");
	ag_Push(g_TXD_Scan, f_ref_CurrentPath + g_ref_global_Div + "g_TXD_Scan");
	ag_Push(g_OCSCP_ThreadCount, f_ref_CurrentPath + g_ref_global_Div + "g_OCSCP_ThreadCount");
	ag_Push(g_ConnectedECD, f_ref_CurrentPath + g_ref_global_Div + "g_ConnectedECD");
	ag_Push(g_LowtonMark, f_ref_CurrentPath + g_ref_global_Div + "g_LowtonMark");
	ag_Push(g_OCSCP_LowtonMark, f_ref_CurrentPath + g_ref_global_Div + "g_OCSCP_LowtonMark");
	ag_Push(g_RenderHesh, f_ref_CurrentPath + g_ref_global_Div + "g_RenderHesh");
	ag_Push(g_LowtonOn, f_ref_CurrentPath + g_ref_global_Div + "g_LowtonOn");
	ag_Push(g_espo_ShareOffset, g_Found_Text + g_ref_global_Div + "g_espo_ShareOffset");
	ag_Push(g_espo_Peer, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Peer");
	ag_Push(g_espo_Score, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Score");
	ag_Push(g_espo_Amount, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Amount");
	ag_Push(g_espo_ECN_Amount, f_ref_CurrentPath + g_ref_global_Div + "g_espo_ECN_Amount");
	ag_Push(g_espo_Owner, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Owner");
	ag_Push(g_espo_Date, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Date");
	ag_Push(g_CurrentComID, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentComID");
	ag_Push(g_CurrentSharePrice, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentSharePrice");
	ag_Push(g_CurrentShareID, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentShareID");
	ag_Push(g_Once, f_ref_CurrentPath + g_ref_global_Div + "g_Once");
	ag_Push(g_JobID, f_ref_CurrentPath + g_ref_global_Div + "g_JobID");
	ag_Push(g_ShareCount, f_ref_CurrentPath + g_ref_global_Div + "g_ShareCount");
	ag_Push(g_CurrentShareOffset, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentShareOffset");
	ag_Push(g_PEER, f_ref_CurrentPath + g_ref_global_Div + "g_PEER");
	ag_Push(g_EventOffset, f_ref_CurrentPath + g_ref_global_Div + "g_EventOffset");
	ag_Push(g_GUItimer, f_ref_CurrentPath + g_ref_global_Div + "g_GUItimer");
	ag_Push(g_SaveComplete_ThreadCount, f_ref_CurrentPath + g_ref_global_Div + "g_SaveComplete_ThreadCount");
	ag_Push(g_Diviner_ThreadCount, f_ref_CurrentPath + g_ref_global_Div + "g_Diviner_ThreadCount");
	ag_Push(g_BoughtCom, f_ref_CurrentPath + g_ref_global_Div + "g_BoughtCom");
	ag_Push(g_MyOwnCom, f_ref_CurrentPath + g_ref_global_Div + "g_MyOwnCom");
	ag_Push(g_CountLM, f_ref_CurrentPath + g_ref_global_Div + "g_CountLM");
#endif
	
	//only obstainers
	//extern std::vector<std::vector<std::string>> g_CopyStack;
	//extern std::vector<std::shared_ptr<Ackent>> g_Ackent;
}

ecoinMain::~ecoinMain()
{
	// Deregister device notification
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void ecoinMain::CreateWindowSizeDependentResources()
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

void ecoinMain::StartRenderLoop()
{
	std::string f_ref_CurrentPath = "ecoinMain::StartRenderLoop";

	// If the animation render loop is already running then do not start another thread.
	if(m_Rendering == false)
		{
#if 1
#if 0
		ag_StatusLive(f_ref_CurrentPath, "m_vec_threadObj");

		m_vec_threadObj = std::make_shared_reflect<std::thread>(&ecoinMain::RenderLoop, this);
#else

		std::thread f_Thread(&ecoinMain::RenderLoop, this);

		f_Thread.detach();

		m_vec_threadObj = &f_Thread;
#endif
#else
		g_QcomManager->acDisplayOn();
#endif
		}
}

void ecoinMain::RenderLoop(void)
{
	g_Schedular[0]->m_MainMutex.lock();

	m_Rendering = true;

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
		g_EventID = ::atoi(g_Schedular[0]->acEntry(0)[0].c_str());
		}

	g_JobID = g_Wallet->acGet_JobID(m_IDX, 0, true);

	char* f_idquery2 = ag_ClearChar(150);
	sprintf(f_idquery2, "SELECT id, owner, score FROM share WHERE jobid = %i", g_JobID);
	std::shared_ptr<Cube::ShareContainerExt> f_ShareContainer = Cag->ag_SelectPeerGraphExt(g_JobID, 0, 0, g_CurrentShareOffset, g_PEER, true);

	int f_ShareCounting = f_ShareContainer->m_espo_TotalShares;
	g_ShareCount = f_ShareCounting;

	g_Schedular[0]->m_MainMutex.unlock();

	ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

	// Calculate the updated frame and render once per vertical blanking interval.
	m_Scan = true;
	while(m_Scan == true)
		{
		if(g_WalletOpen == true)
			{
			if(g_Wallet->m_vec_MainMode[m_IDX] <= ECOIN_MODE_VIEWING)
				{
				mutex_swap.lock();

				if(g_Wallet->m_vec_MainMode[m_IDX] <= ECOIN_MODE_NONVIEW)
					{
					while(m_sceneRenderer->m_cnt_DIV_Thread < g_Diviner_ThreadCount)
						{
						std::thread f_Thread(&Sample3DSceneRenderer::acGen_GenHesh, m_sceneRenderer.get());

						f_Thread.detach();

						m_sceneRenderer->m_cnt_DIV_Thread++;
						}
					}

				if(g_QcomManager->m_Open == true)
					{
					if(g_RenderHesh == true)
						{
						m_sceneRenderer->acCreateAdmaxDependentResources();

						m_sceneRenderer->RestoreTargetedBuffers();

						g_RenderHesh = false;
						}

					Update();

					try
						{
						if(Render())
							{
							m_deviceResources->Present();
							}
						}

					catch(...)
						{
						int i = 1;
						}
					}
				else
					{
					if(::g_TargetedHesh)
						{
						if(g_RenderHesh == true)
							{
							m_sceneRenderer->acCreateAdmaxDependentResources();

							m_sceneRenderer->RestoreTargetedBuffers();

							Update();

							try
								{
								if(Render())
									{
									m_deviceResources->Present();
									}
								}

							catch(...)
								{
								int i = 1;
								}

							g_RenderHesh = false;
							}
						}
					}

				mutex_swap.unlock();
				}
			else
				{
				std::string f_ref_CurrentPath = g_ref_flow_reset + "ecoinMain::StartRenderLoop";

				m_sceneRenderer->m_IDX = m_IDX;

				while(m_sceneRenderer->m_cnt_SCP_Thread < g_SaveComplete_ThreadCount)
					{
					if(g_LowtonOn == false)
						{
						g_BlockType = ecoin_BlockType::ecoin_Block_Target_SCP;

						g_LowtonOn = true;

						int f_ComID = ::g_QcomManager->m_Qcom->m_ID;
						float f_Cost = ::g_QcomManager->m_Qcom->m_Cost;
						int f_ShareID = ::g_QcomManager->m_Qcom->m_PackageShareID;

						std::shared_ptr<Qcom> f_com = nullptr;

						//if one com selected save only this one as main shall insert
						if(g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size() == 1)
							{
							f_com = g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com[0];

							f_ComID = f_com->m_ID;

							if(f_com->m_Cost > 0.0f)
								{
								f_Cost = f_com->m_Cost;
								}
							}

						g_classLMap->m_Patched = false;

						ag_StatusLive(f_ref_CurrentPath, "g_Lowton");
						g_Lowton = std::make_shared_reflect<Cube::CubeHESH>(g_classLMap->m_ADMAX, g_classLMap->m_ADMAX, g_classLMap->m_ADMAX, g_CountLM);
						ag_StatusLive(f_ref_CurrentPath, "g_Lowton_Collection");
						g_Lowton_Collection = std::make_shared_reflect<classCollection>();
						ag_StatusLive(f_ref_CurrentPath, "g_LowtonHash");
						g_LowtonHash = std::make_shared_reflect<Cube::CubeHASH_originstring>();

						m_sceneRenderer->m_DB_AccessLock.lock();

						g_JobID = g_Wallet->acGet_JobID(m_IDX);

						float f_Difficulty = 0.0f;

						std::string f_ShareLedgerPrimer = g_classLMap->acLenseMapHash();

						//ECN::Hesh...Check Reaquire Sending BlockHesh Elements
						char* query = ag_ClearChar(512); // AND comid = %i , f_ComID when QamLoadAll implemented
						::sprintf(query, "SELECT id, bckred, bckgreen, bckblue FROM share WHERE shareledger = '%s' ORDER BY score DESC", f_ShareLedgerPrimer.c_str());
						g_SafeL[0]->acSelectCommand(query, 2, false);
						delete query;

						if(g_Schedular[0]->acEntry(0)[0].at(0) != '0')
							{
							g_ShareID = ::atoi(g_Schedular[0]->acEntry(0)[0].c_str());

							Cube::BiVector f_BCK(atof(g_Schedular[0]->acEntry(0)[1].c_str()), atof(g_Schedular[0]->acEntry(0)[2].c_str()), atof(g_Schedular[0]->acEntry(0)[3].c_str()));

							char* cubequery = ag_ClearChar(3000);
							::sprintf(cubequery, "SELECT id, vert1x, vert1y, vert1z, vert2x, vert2y, vert2z, vert3x, vert3y, vert3z, vert4x, vert4y, vert4z, vert5x, vert5y, vert5z, vert6x, vert6y, vert6z, vert7x, vert7y, vert7z, vert8x, vert8y, vert8z, vert1r, vert1g, vert1b, vert2r, vert2g, vert2b, vert3r, vert3g, vert3b, vert4r, vert4g, vert4b, vert5r, vert5g, vert5b, vert6r, vert6g, vert6b, vert7r, vert7g, vert7b, vert8r, vert8g, vert8b, shareid, jobid, eslid, targetid, eslcode, difficulty FROM cube WHERE shareid = %i ORDER BY eslid ASC#", g_ShareID);
							g_SafeL[0]->acSelectCommand(cubequery, false, false);
							delete cubequery;

							int f_adCount = 0;

							int f_CountLM = g_CountLM;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_adCount = 0;
								}
							else
								{
								f_adCount = g_Schedular[0]->acEntrySize();

								f_CountLM = ::atoi(g_Schedular[0]->acEntry(0)[52].c_str());
								}

							//CountLM Measurement Count Value
							g_CountLM = f_CountLM;

							//ECN::f_adCount
							g_BicycleContainer[0]->m_ADMAX = f_adCount;
							g_BicycleContainer[0]->m_ADHIGH = f_adCount;
							g_BicycleContainer[0]->m_ADLOW = f_adCount;

							//convert ADMAX to scoreand maxvote
							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)((g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX) * ECOIN_REWARD_ON) /*ECN_OPER_REWARD*/ + ECOIN_SCP_INSTANT_BONUS);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, ECOIN_REWARD_ON /*ECN_OPER_REWARD*/ + ECOIN_SCP_INSTANT_BONUS);

							f_Difficulty = (((float)g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX)) * ECOIN_SCP_DEFAULT_BASEDIFF;

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
									std::shared_ptr<Cube::BiVector> f_Vector = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[0]->acEntry(f_Int)[1 + (f_Int2 * 3)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 1)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 2)].c_str()));

									f_Bike->vec_Vertex.push_back(f_Vector);
									}

								f_Bike->vec_Color.clear();

								for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
									{
									ag_StatusLive(f_ref_CurrentPath, "f_Color");
									std::shared_ptr<Cube::BiVector> f_Color = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[0]->acEntry(f_Int)[25 + (f_Int3 * 3)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 1)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 2)].c_str()));

									f_Bike->vec_Color.push_back(f_Color);
									}

								ag_StatusLive(f_ref_CurrentPath, "f_Element");
								std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Bike);

								g_Lowton_Collection->m_vec_Element.push_back(f_Element);
								g_Lowton_Collection->m_idx_vec_Element++;

								f_Heshr->vec_Bicycle.push_back(f_Bike);
								}

							  ////////////
							 // HESH   //
							//        //
							int f_PortCNTR = 0;
							f_Heshr->m_adIndex.clear();

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

							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)f_Difficulty + 100.0f);
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, f_CountLM);
							ag_FreshOn<float>(g_Wallet->m_vec_difficulty, m_IDX, (float)ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, ecoin_BlockType::ecoin_Block_Target_SCP);
							ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_ShareLedgerPrimer);
							ag_FreshOn<float>(g_Wallet->m_vec_price, m_IDX, f_Cost);
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);

							ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, -1);

							f_Heshr->ac_IsOK();

							g_Once = true;
							g_Lowton = f_Heshr;
							g_TargetedHesh = f_Heshr;
							g_RenderHesh = true;

							//JOB Mainly
							char* jobquery = ag_ClearChar(512);
							::sprintf(jobquery, "SELECT id, blocktype, eslcode, pledgetype, pledgemax, targetbreach, owner, scoremax, markmax, markmin, reward, rewardid, startbreach, blockid, dated FROM job WHERE blockid = (SELECT id FROM block WHERE ((shareid = %i) AND (jobid = %i))) ORDER BY dated DESC LIMIT 1", g_ShareID, g_JobID);
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
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, atof(g_Schedular[0]->acEntry(0)[7].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, atof(g_Schedular[0]->acEntry(0)[8].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, atof(g_Schedular[0]->acEntry(0)[9].c_str()));
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, ::atoi(g_Schedular[0]->acEntry(0)[3].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, ::atoi(g_Schedular[0]->acEntry(0)[4].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, ::atoi(g_Schedular[0]->acEntry(0)[5].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, ::atoi(g_Schedular[0]->acEntry(0)[12].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, ::atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, ::atoi(g_Schedular[0]->acEntry(0)[13].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_eslcode, m_IDX, g_TypeName);
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);

								g_Found_Msg = 15;

								char* f_Chr = ag_ClearChar(2500);
								::sprintf(f_Chr, "Group Founder onSHR#(...%i) Job#(...%i)!", g_ShareID, g_Wallet->m_vec_jobboardid[m_IDX]);
								std::string f_ChrString = f_Chr;
								delete f_Chr;

								g_Found_Text = f_ChrString;

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

								char* jobvarquery = ag_ClearChar(512);
								::sprintf(jobvarquery, "SELECT id, name, groupname, value, dated FROM jobvar WHERE jobid = %i ORDER BY dated DESC", ::atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
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
											f_vec_jobvarid.push_back(::atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
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
											g_Wallet->m_vec_jobvarid[m_IDX].push_back(::atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
											g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
											g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
											}
										}
									}
								}
							else
								{
								g_Wallet->acSet_IDX(m_IDX);
								g_Wallet->acSave_currentJob();

								g_Found_Msg = 15;

								char* f_Chr = ag_ClearChar(2500);
								::sprintf(f_Chr, "Group Founder onSHR#(...%i) Job#(...%i)!", g_ShareID, g_Wallet->m_vec_jobboardid[m_IDX]);
								std::string f_ChrString = f_Chr;
								delete f_Chr;

								g_Found_Text = f_ChrString;
								}
							}
						else
							{
							//CountLM Measurement Count Value
							int f_CountLM = g_CountLM;

							//ECN::f_adCount
							g_BicycleContainer[0]->m_ADMAX = 0;
							g_BicycleContainer[0]->m_ADHIGH = 0;
							g_BicycleContainer[0]->m_ADLOW = 0;

							//convert ADMAX to score and maxvote
							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)ECOIN_SCP_INSTANT_BONUS);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, ECOIN_REWARD_ON /*ECN_OPER_REWARD*/ + ECOIN_SCP_INSTANT_BONUS);
							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)ECOIN_SCP_INSTANT_BONUS);
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, f_CountLM);
							ag_FreshOn<float>(g_Wallet->m_vec_difficulty, m_IDX, (float)ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, ecoin_BlockType::ecoin_Block_Target_SCP);
							ag_Freshanon<std::string>(g_Wallet->m_vec_blockledger, m_IDX, "EMPTY");
							ag_FreshOn<float>(g_Wallet->m_vec_price, m_IDX, f_Cost);
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);
							ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, -1);

							char* g_sharevalue[25];

							for(int f_Count = 0; f_Count < 25; f_Count++)
								{
								g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
								}

							::sprintf(g_sharevalue[0], "%i", (int)g_Wallet->m_vec_mark[m_IDX]);
							::sprintf(g_sharevalue[1], "%f", (float)g_Wallet->m_vec_mark[m_IDX]);
							::sprintf(g_sharevalue[2], "%i", 1);
							::sprintf(g_sharevalue[3], "%i", 3);
							::sprintf(g_sharevalue[4], "%i", g_JobID);
							::sprintf(g_sharevalue[5], "%i", g_Wallet->m_vec_jobboardid[m_IDX]);
							::sprintf(g_sharevalue[6], "%i", g_Wallet->m_vec_eslid[m_IDX]);
							::sprintf(g_sharevalue[7], "%i", g_Wallet->m_vec_targetid[m_IDX]);
							::sprintf(g_sharevalue[8], "%s", g_TypeName.c_str());
							::sprintf(g_sharevalue[9], "%f", g_Wallet->m_vec_difficulty[m_IDX]);
							::sprintf(g_sharevalue[10], "%f", g_Wallet->m_vec_score[m_IDX]);
							::sprintf(g_sharevalue[11], "%f", g_Wallet->m_vec_maxvote[m_IDX]);
							::sprintf(g_sharevalue[12], "%s", f_ShareLedgerPrimer.c_str());
							::sprintf(g_sharevalue[13], "%s", g_Wallet->m_vec_blockledger[m_IDX].c_str());
							::sprintf(g_sharevalue[14], "%s", g_Wallet->GetAdr().c_str());
							::sprintf(g_sharevalue[15], "%f", 0.5f);
							::sprintf(g_sharevalue[16], "%f", 0.4f);
							::sprintf(g_sharevalue[17], "%f", 0.97f);
							::sprintf(g_sharevalue[18], "%i", f_ComID);
							::sprintf(g_sharevalue[19], "%f", g_Wallet->m_Reward);
							::sprintf(g_sharevalue[20], "%f", 0.0f);
							::sprintf(g_sharevalue[21], "%f", 0.0f);
							::sprintf(g_sharevalue[22], "%f", ECN_TX_FEE);
							::sprintf(g_sharevalue[23], "%f", g_Wallet->m_vec_price[m_IDX]);
							::sprintf(g_sharevalue[24], "%i", g_BlockType);

							g_ShareID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 25, 2, false);

							for(int f_Count = 0; f_Count < 25; f_Count++)
								{
								free(g_sharevalue[f_Count]);
								}

							  ///////////////
							 // Add Share //
							///////////////
							char* balancequery = ag_ClearChar(1000);
							::sprintf(balancequery, "Call acTopUpPeerBalanceAdvance(%i, %i)", g_ShareID, g_JobID);
							g_SafeL[0]->acSelectCommand(balancequery, 2, false);
							delete balancequery;

							std::shared_ptr<ShareContainerExt> f_PG = Cag->ag_SelectPeerGraphExt(g_JobID, 0, g_ShareID, g_CurrentShareOffset, g_PEER);

							g_CurrentShareOffset = f_PG->m_espo_ShareOffset;
							g_CurrentShareOffsetMAX = f_PG->m_espo_SharesOnPeerCount;
							g_PEER = f_PG->m_espo_Peer;
							g_PEERCNT = f_PG->m_espo_PeerCount;
							g_PEERMAX = f_PG->m_espo_PeerCount;

							g_JobID = g_Wallet->acGet_JobID(m_IDX);

							g_Wallet->acSet_IDX(m_IDX);
							g_Wallet->acSave_currentJob();

							g_Found_Msg = 15;

							char* f_Chr = ag_ClearChar(2500);
							::sprintf(f_Chr, "Group Founder onSHR#(...%i) Job#(...%i)!", g_ShareID, g_Wallet->m_vec_jobboardid[m_IDX]);
							std::string f_ChrString = f_Chr;
							delete f_Chr;

							g_Found_Text = f_ChrString;

							 ///////////////////////////////////////////////////////////////////////
							// Toss share calculation transaction onto next block/jobid as yield //
							Cag->ag_addGenesisTracking(g_ShareID, ecoin_BlockType::ecoin_Block_Target_SCP, 0);

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

							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)100 * (int)((float)g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX));
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, g_CountLM);
							ag_Freshanon<float>(g_Wallet->m_vec_difficulty, m_IDX, ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_Freshanon<int>(g_Wallet->m_vec_blocktype, m_IDX, ecoin_BlockType::ecoin_Block_Target_SCP);
							ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_TXJob_OutputHash);
							
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);
							}

						m_sceneRenderer->m_DB_AccessLock.unlock();
						}

					std::thread f_Thread(&Sample3DSceneRenderer::acSaveCompletePublish_GenHesh_Upper_Reflection, m_sceneRenderer.get());

					f_Thread.detach();

					m_sceneRenderer->m_cnt_SCP_Thread++;
					}

				mutex_swap.lock();

				if(g_TargetedHesh)
					{
					if(g_RenderHesh == true)
						{
						m_sceneRenderer->acCreateAdmaxDependentResources();

						m_sceneRenderer->RestoreTargetedBuffers();

						Update();

						try
							{
							if(Render() == true)
								{
								m_deviceResources->Present();
								}
							}

						catch(...)
							{
							int i = 1;
							}

						g_RenderHesh = false;
						}
					}

				mutex_swap.unlock();
				}
			}
		}

	m_Rendering = false;
}

void ecoinMain::StopRenderLoop()
{
	m_Scan = false;
}

// Updates the application state once per frame.
void ecoinMain::Update()
{
	ProcessInput();

	// TODO: Replace this with your app's content update functions.
	m_sceneRenderer->Update();
}

// Process all input from the user before updating game state
void ecoinMain::ProcessInput()
{
	// TODO: Add per frame input handling here.
	m_sceneRenderer->TrackingUpdate(m_pointerLocationX);
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool ecoinMain::Render(void)
{
	// Don't try to render anything before the first Update.
#if 0
	if(m_timer.GetFrameCount() == 0)
		{
		return false;
		}
#endif

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Reset the viewport to target the whole screen.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// Reset render targets to the screen.
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	float f_Color[4];

	if(g_TargetedHesh)
		{
		f_Color[0] = g_TargetedHesh->m_bckred;
		f_Color[1] = g_TargetedHesh->m_bckgreen;
		f_Color[2] = g_TargetedHesh->m_bckblue;
		f_Color[3] = 1.0;
		}
	else
		{
		f_Color[0] = 0.8f;
		f_Color[1] = 0.8f;
		f_Color[2] = 1.0f;
		f_Color[3] = 1.0;
		}

	context->ClearRenderTargetView(m_deviceResources->GetRenderTargetView(), f_Color);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render the scene objects.
	if(g_QcomManager->m_Open == true)
		{
		g_QcomManager->acDisplayOn();

		m_sceneRenderer->Render_Qcom();

		for(int f_XL = 0; f_XL < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XL++)
			{
			std::shared_ptr<Qcom> f_com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XL];

			m_sceneRenderer->Render_COM(f_com->m_position->m_X, f_com->m_position->m_Y, f_com->m_Trial_Length);
			}

		m_sceneRenderer->Render_Curve();

		m_fpsTextRenderer->Update();
		}
	else
		{
		if(g_TargetedHesh)
			{
			for(int f_PORTcntr = 0; f_PORTcntr < g_TargetedHesh->m_adIndex.size(); f_PORTcntr++)
				{
				m_sceneRenderer->Render(g_TargetedHesh->m_adIndex[f_PORTcntr]);
				}
			}
		}

	return true;
}

// Notifies renderers that device resources need to be released.
void ecoinMain::OnDeviceLost()
{
	m_sceneRenderer->ReleaseDeviceDependentResources();
	m_fpsTextRenderer->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void ecoinMain::OnDeviceRestored()
{
	m_sceneRenderer->CreateDeviceDependentResources();
	m_fpsTextRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

};