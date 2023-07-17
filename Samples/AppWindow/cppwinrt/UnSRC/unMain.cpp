/*

unMain.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Render\unRenderer\resource.h"
#include "Render\unRenderer\unRenderer.h"

#include "QActiveFramewrk.h"
#include "Texture/tgaload.h"

#include "Q-NET-ProtoMap.h"

#ifdef OSIRUS_CORE
#include "Speech/SpeechDlg.h"
#endif

#include "Utility/unConsole.h"

//¬¬¬ Application specific window name ¬¬¬//
char *appname = "Quantum Angel Arena";
char app_path[256];

void draw_scene();
void draw_info();
void key_pressed(int key,int flags);
void animate();
void appInit();
void acClose();
void update_menu();
void command(UINT msg, WPARAM wParam, LPARAM lParam);

std::string meshfile;

unRenderer *unRender=0;	// engine object

#ifdef OSIRUS_CORE
CSpeechDlg *i_CSpeechDlg;
#endif

extern GLuint BlurTexture;

#if 0
extern QSharedStruct<QAGE::QActiveFramewrk> QActiveFrameWork;
#else
extern QAGE::QActiveFramewrk *QActiveFrameWork;
#endif

//##### Unification Console #####//
int g_unC_RowON = 0;
int g_unCStrSize = 0;
std::vector<std::string> g_unConsole_vec_str;
std::vector<int> g_unC_vec_ind;
std::string g_unConsoleText[10];
int g_unCoutcnt = 0;
int g_unCoutcntSTR = 0;
//##### Unification Console #####//

std::vector<char> m_vec_EnergyGlyphsAv[QNOMAI + 10];
char g_EnergyCntlCharAv[QNOMAI + 10];
std::vector<char> m_vec_EnergyGlyphsPl;
char g_EnergyCntlCharPl = 1;
int g_EnergyControlSWIT = 1;

bool bloom=false;
bool debug=false;
bool scissor=true;
bool depthtex=true;
bool depthbias=false;
bool antialias=false;
bool m_Running = true;

//AST
bool around=false;

int resolutions[5][2]={ {256,256} , {400,300}, {512,512} , {640,480} , {800,600} };
int screenres[7][2]={ {640,480} , {800,600}, {960,600} , {1024,768} , {1152,864}, {1280,1024}, {1366,768} };
int res=2;
int scrres=1;
int mode=1;
int camera=0;
float i_time=0;

int active=0;
int mouse=0,mousex,mousey;

bool vecDpress[5];

HWND hWndMain;
HINSTANCE hInstance;

int g_Index = 0;
bool g_IndexLock = false;

char qkey;

#if 0
int WinFunc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
		{
		case WM_KEYDOWN:
			{
			qkey = (char)wParam;

			switch (qkey)
				{
				//##### Keylogger for Left To Forward Jink
				case 'A':
					{
					player[g_Player]->KL_LeftToFor = 1;

					if(player[g_Player]->KL_ForToLeft == 1)
						{
						player[g_Player]->KL_ForToLeft = 2;
						player[g_Player]->KL_LeftToFor = 0;
						}
					} break;

				//##### Keylogger for Right To Forward Jink
				case 'D':
					{
					player[g_Player]->KL_RightToFor = 1;

					if(player[g_Player]->KL_ForToRight == 1)
						{
						player[g_Player]->KL_ForToRight = 2;
						player[g_Player]->KL_RightToFor = 0;
						}
					} break;

				//##### Keylogger for Forward Jinks
				case 'W':
					{
					player[g_Player]->KL_ForToLeft = 1;
					player[g_Player]->KL_ForToRight = 1;

					if(player[g_Player]->KL_LeftToFor == 1)
						{
						player[g_Player]->KL_LeftToFor = 2;
						player[g_Player]->KL_ForToLeft = 0;
						}

					if(player[g_Player]->KL_RightToFor == 1)
						{
						player[g_Player]->KL_RightToFor = 2;
						player[g_Player]->KL_ForToRight = 0;
						}

					if(player[g_Player]->KL_BlockToFor == 1)
						{
						player[g_Player]->KL_BlockToFor = 2;
						}
					} break;

				//##### Keylogger for Block Jinks
				case 'S':
					{
					player[g_Player]->KL_BlockToFor = 1;
					} break;

				//##### Escape Fullscreen mode
				case 27:
					{
					g_render->set_fullscreen(0, true);
					} break;
				}

			//*QActiveFrameWork->m_GUI->acKeyDown(key);
			}break;

		case WM_KEYUP:
			{
			qkey = (char)wParam;

			switch (qkey)
				{
				//##### Keylogger for Left To Forward Jink - Stage Three
				case 'A':
					{
					if(player[g_Player]->KL_LeftToFor == 2)
						{
						player[g_Player]->KL_LTFSpecLevel++;

						player[g_Player]->KL_Timer = TIME;

						
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->ViewXForm.Translation);
						}

					player[g_Player]->KL_LeftToFor = 0;
					player[g_Player]->KL_ForToLeft = 0;
					player[g_Player]->KL_ForToRight = 0;
					player[g_Player]->KL_RightToFor = 0;
					} break;

				//##### Keylogger for Right To Forward Jink - Stage Three
				case 'D':
					{
					if(player[g_Player]->KL_RightToFor == 2)
						{
						player[g_Player]->KL_RTFSpecLevel++;

						player[g_Player]->KL_Timer = TIME;

						
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->ViewXForm.Translation);
						}

					player[g_Player]->KL_LeftToFor = 0;
					player[g_Player]->KL_ForToLeft = 0;
					player[g_Player]->KL_ForToRight = 0;
					player[g_Player]->KL_RightToFor = 0;
					} break;

				//##### Keylogger for Forward To Left OR Right Jink - Stage Three
				case 'W':
					{
					if(player[g_Player]->KL_ForToLeft == 2)
						{
						player[g_Player]->KL_FTLSpecLevel++;

						player[g_Player]->KL_Timer = TIME;

						
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->ViewXForm.Translation);
						}

					if(player[g_Player]->KL_ForToRight == 2)
						{
						player[g_Player]->KL_FTRSpecLevel++;

						player[g_Player]->KL_Timer = TIME;

						
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->ViewXForm.Translation);
						}

					player[g_Player]->KL_LeftToFor = 0;
					player[g_Player]->KL_ForToLeft = 0;
					player[g_Player]->KL_ForToRight = 0;
					player[g_Player]->KL_RightToFor = 0;
					} break;

				//##### Keylogger for Right To Forward Jink - Stage Three
				case 'S':
					{
					if(player[g_Player]->KL_BlockToFor == 2)
						{
						player[g_Player]->KL_BTFSpecLevel++;

						player[g_Player]->KL_LTFSpecLevel = 0;
						player[g_Player]->KL_RTFSpecLevel = 0;
						player[g_Player]->KL_FTLSpecLevel = 0;
						player[g_Player]->KL_FTRSpecLevel = 0;

						player[g_Player]->KL_BTimer = TIME;

						
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->ViewXForm.Translation);
						}
					} break;

				} break;

			case WM_LBUTTONDOWN:
				{
#if 1
				//*if(!QActiveFrameWork->acGuiEvents(QActiveFrameWork->m_GUI->acMouseClick()))
				//*	{
				//*	_->lbutton[g_Player]=1;
				//*	_->lbuttonhold[g_Player]=1;
				//*	player[g_Player]->WeaponFire = 1;
				//*	}
#endif
				} break;

			case WM_LBUTTONUP:
				{
				_->lbutton[g_Player]=0;
				_->lbuttonhold[g_Player]=0;
				} break;

			case WM_RBUTTONDOWN:
				{
				_->rbutton[g_Player]=1;
				} break;

			case WM_MBUTTONDOWN:
				{
				_->mbutton[g_Player]=1;
				} break;

			case 0x020A:	//### Mouse Wheel Scroll
				{
				_->mbutton[g_Player]=1;
				_->mwheelroll[g_Player]=1;
				} break;

			case WM_CREATE:
				{
				hWndMain=hWnd;

				g_NetConnect = false;
				g_QUITM = false;

				render_init(app_path,"unRenderer.ini",hWnd,0);

				if (g_render->load_font("data\\fonts.tga")!=-1) g_render->sel_font(0);
				appInit();

				if(!g_render)
					{
					printf("ERROR:::OpenGL initialization failed...\n");
					throw;
					}*/
				} break;

			case WM_SIZE:
				if (g_render) g_render->resize(LOWORD(lParam),HIWORD(lParam));
				break;

			case WM_DESTROY:
#if 0
				render_free();
#endif
				break;

			case WM_ERASEBKGND:
				if (g_render) return 1;
				else return 0;

			case WM_CHAR:
				//if (g_render) key_pressed(wParam,GetAsyncKeyState(VK_SHIFT)&0x80000000);
 				return 0;

			case WM_PAINT:
				{
				if(ApplicationFocus)
					{
					g_render->begin_draw();
					draw_scene();
					g_render->set_draw2d();
					draw_info();
					g_render->end_draw();
					}
				} break;

			case WM_COMMAND:
				command(msg,wParam,lParam);
				break;

			case WM_ACTIVATE:
				active=LOWORD(wParam)==WA_INACTIVE?0:1;
				update_menu();
				break;

			case WM_MOUSEMOVE:
				{
#if 0
#if 0
				float rotspeed=0.05f;
				float panspeed=0.2f;
				int dx=(short)LOWORD(lParam)-mousex;
				int dy=(short)HIWORD(lParam)-mousey;
#endif

				mousex=(short)LOWORD(lParam);
				mousey=(short)HIWORD(lParam);

				if(g_render->fullscreen) QActiveFrameWork->m_GUI->acMouseMotion(mousex, (mousey + 55) + (g_render->sizey - 544));
				else QActiveFrameWork->m_GUI->acMouseMotion(mousex, (mousey + 55) - (g_render->sizey - 544));

				QActiveFrameWork->acGameEventsFrame();
#endif
				} break;

#ifdef OSIRUS_CORE
			case WM_CSPEECHEVENT:
				{
				if(unRender->QActiveFrameWork->m_re
				if(!QNetwork.m_Recording && !QNetwork.m_Playing)
					{
					i_CSpeechDlg->acSpeechEvent();

					char *i_message = i_CSpeechDlg->acSpeechEvent();

					//Qxl->randSwitch();
					//QActiveFrameWork->i_OsirusCore->acCreateCommand(i_message);
					//Qxl->randSwitch(i_OsirusCore->acCreateCommand());
					//unRender->QA
					}
				} break;
#endif

			case WM_ACTIVATEAPP:
				{
				if((int)wParam != 0)
					{
					ApplicationFocus = 1;
					}
				else
					{
					ApplicationFocus = 0;
					}
				}break;
			}
		}

	/*if(g_render)
		{
		if(g_render->fullscreen == 0)
			{
			while(ShowCursor(true)<=0);
			}
		if(g_render->fullscreen == 1) ShowCursor(false);
		}
	else ShowCursor(true);*/

	return 1; //DefWindowProc (hWnd, msg, wParam, lParam);
}
#endif

int Q_EntryMain(void)
{
	//Start
	if(m_OpenReturn == true)
		{
		return -1;
		}

	m_OpenReturn = true;

#if 0
#if 0
	Q.CoreAcquire();
#else
	Q.CoreAllocate();
#endif
#endif

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

	_->TimeHoleDir = 0;
	_->TimeHole = 0;
	_->TimeInit = 0;
	_->TimeReset = 0;
	_->TimeRotate = 0;
	_->TimePlayerLock = 0;
	_->TimeWaitReset = 0;
	_->JumpTimeInit = 0;
	_->JinkTime = 0;

	// Porting Template
#if 0
	ag_PortShell_Initialisation();
#endif
	
	/*_->screenx = g_render->sizex;
    _->screeny = g_render->sizex;

	unRender->mrt_destroy();
	res = 4;
	unRender->mrt_create(resolutions[res][0],resolutions[res][1]);

	int j = -1;
	for( i=0;i<g_render->videomode.num;i++ )
	if (g_render->videomode[i].dmPelsWidth==(unsigned int)g_render->sizex &&
		g_render->videomode[i].dmPelsHeight==(unsigned int)g_render->sizey)
		{
		if ((int)g_render->videomode[i].dmDisplayFrequency>j && g_render->videomode[i].dmDisplayFrequency<=120)
			{
			j=g_render->videomode[i].dmDisplayFrequency;
			g_render->selvideomode=i;
			}
		}

	QActiveFrameWork->m_GUI->acVidResize((unsigned int)g_render->sizex, (unsigned int)g_render->sizey);
	ChangeDisplaySettings(&g_render->videomode[g_render->selvideomode], NULL);
	update_menu();

	//g_render->set_fullscreen(!g_render->fullscreen);
	//mfullscreen = g_render->fullscreen;
	//ShowCursor(false);*/

	g_NetConnect = false;
	g_QUITM = false;

	g_render = new pRender(app_path, "unRenderer.ini");
	g_render->create();

	//render_init(app_path,"unRenderer.ini",hWnd,0);

	//printf("g_render->sizey %i\n", g_render->sizey);

	//if (g_render->load_font("data\\fonts.tga")!=-1) g_render->sel_font(0);

	appInit();

	g_startcommand = 2;

	//g_QUITM = true;
#if 0
	//while(!g_QUITM)
	//	{
#ifndef QAR_EXT
		if(g_startcommand == 2 || 1)
			{
			if(g_optionsresult == 3)
				{
				if(QActiveFrameWork->m_NetStart)
					{
					//.lock()??
					QActiveFrameWork->m_PacketPump.m_PP_STATE_I = QActiveFrameWork->m_PacketPump.m_PP_STATE;

					if(QActiveFrameWork->m_PacketPump.m_PP_STATE_I >= 4) g_startcommand = 1;
					}
				}
			else g_startcommand = 1;

			if(g_startcommand == 1 || 1)
				{
				g_startcommand = 5;

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(0);

				f_SpawnPoint->m_CellCenter.x = 0;//* _->mesh->cam[0].pos.x;
				f_SpawnPoint->m_CellCenter.y = 0;//*_->mesh->cam[0].pos.y;
				f_SpawnPoint->m_CellCenter.z = 0;//*_->mesh->cam[0].pos.z;

				f_SpawnPoint->m_RotationVec.x = 0;//*_->mesh->cam[0].Z.x * -1;
				f_SpawnPoint->m_RotationVec.y = 0;
				f_SpawnPoint->m_RotationVec.z = 0;//*_->mesh->cam[0].Z.z * -1;

				Qpo->Vec3d_Normalize(&f_SpawnPoint->m_RotationVec);

				QpoVec3d f_YRotationVec;

				f_YRotationVec.x = 0;
				f_YRotationVec.y = 1;
				f_YRotationVec.z = 0;

				Qpo->Vec3d_CrossProduct(&f_SpawnPoint->m_RotationVec, &f_YRotationVec, &f_SpawnPoint->m_StRotationVec);

				f_SpawnPoint->m_StRotationVec.y = 0;

				Qpo->Vec3d_Normalize(&f_SpawnPoint->m_StRotationVec);
				Qpo->Vec3d_Normalize(&f_SpawnPoint->m_RotationVec);

				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);

#if 0
				for(int f_counter = 1; f_counter < _->mesh->ncam; f_counter++)
					{
					QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);

					f_SpawnPoint->m_CellCenter.x = _->mesh->cam[f_counter].pos.x;
					f_SpawnPoint->m_CellCenter.y = _->mesh->cam[f_counter].pos.y;
					f_SpawnPoint->m_CellCenter.z = _->mesh->cam[f_counter].pos.z;

					f_SpawnPoint->m_RotationVec.x = _->mesh->cam[f_counter].Z.x * -1;
					f_SpawnPoint->m_RotationVec.y = 0;
					f_SpawnPoint->m_RotationVec.z = _->mesh->cam[f_counter].Z.z * -1;

					Qpo->Vec3d_Normalize(&f_SpawnPoint->m_RotationVec);

					QpoVec3d f_YRotationVec;

					f_YRotationVec.x = 0;
					f_YRotationVec.y = 1;
					f_YRotationVec.z = 0;

					Qpo->Vec3d_CrossProduct(&f_SpawnPoint->m_RotationVec, &f_YRotationVec, &f_SpawnPoint->m_StRotationVec);

					f_SpawnPoint->m_StRotationVec.y = 0;

					Qpo->Vec3d_Normalize(&f_SpawnPoint->m_StRotationVec);
					Qpo->Vec3d_Normalize(&f_SpawnPoint->m_RotationVec);

					QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
					}
#endif

				if(player[g_Player]->Team >= QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.size())
					player[g_Player]->Team = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.size() - 1;

				playerAV[g_Player]->Xform.Translation.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.x;
				playerAV[g_Player]->Xform.Translation.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.y;
				playerAV[g_Player]->Xform.Translation.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.z;

				player[g_Player]->finalcolldet_oldpos.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.x;
				player[g_Player]->finalcolldet_oldpos.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.y;
				player[g_Player]->finalcolldet_oldpos.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.z;

				player[g_Player]->HB_LastAvatarHitID = 0;
	
				//Begin Transforming for Camera
				Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &playerAV[g_Player]->Up);

				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec.y = 0;

				Qpo->Vec3d_Subtract(&playerAV[g_Player]->Up, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec, &ScanTurnVec);
				Ange.y = Qpo->Vec3d_Length(&ScanTurnVec);

				//### Check Distance between Pure Left and Right to work out direction of Turn
				Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &playerAV[g_Player]->Left);

				Qpo->Vec3d_Copy(&playerAV[g_Player]->Left, &playerAV[g_Player]->Right);
				Qpo->Vec3d_Inverse(&playerAV[g_Player]->Right);

				ScanDistL = Qpo->Vec3d_DistanceBetween(&QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec, &playerAV[g_Player]->Left);
				ScanDistR = Qpo->Vec3d_DistanceBetween(&QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec, &playerAV[g_Player]->Right);

				if(ScanDistL < ScanDistR) Ange.y *= -1;

				player[g_Player]->trueAngles.y = Ange.y + PI;

				player[g_Player]->Angles.y = Ange.y + PI;
				if(player[g_Player]->Angles.y > (PI*2)) player[g_Player]->Angles.y = 0;
				if(player[g_Player]->Angles.y < 0) player[g_Player]->Angles.y = (PI*2);

				if(_->NetworkOption != 1 || 1)
					{
					helly = 0;
					while(helly < _->NomAI)
						{
						if(player[g_Player]->BFO.AVATARDATA[helly].LIVE == 1 || 1)
							{
							int f_Team = 0;
							f_Team = Q_Forge->Forge[helly].Team;
							while(Q_Forge->Forge[helly].Team >= QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.size())
								{
								f_Team = rand() % QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.size();
								Q_Forge->Forge[helly].Team = f_Team;
								}
							
							QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec.y = 0;

							//Begin Transforming for Camera
							Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[helly].AV.Xform, &Q_Forge->Forge[helly].AV.Up);

							Qpo->Vec3d_Subtract(&Q_Forge->Forge[helly].AV.Up, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &ScanTurnVec);
							Q_Forge->Forge[helly].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);

							//### Check Distance between Pure Left and Right to work out direction of Turn
							Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[helly].AV.Xform, &Q_Forge->Forge[helly].AV.Left);

							Qpo->Vec3d_Copy(&Q_Forge->Forge[helly].AV.Left, &Q_Forge->Forge[helly].AV.Right);
							Qpo->Vec3d_Inverse(&Q_Forge->Forge[helly].AV.Right);

							ScanDistL = Qpo->Vec3d_DistanceBetween(&QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].AV.Left);
							ScanDistR = Qpo->Vec3d_DistanceBetween(&QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].AV.Right);

							if(ScanDistL < ScanDistR) Q_Forge->Forge[helly].ScanTurnAng *= -1;

							Q_Forge->Forge[helly].trueAngles.y = Q_Forge->Forge[helly].ScanTurnAng;

							Q_Forge->Forge[helly].Angles.y = Q_Forge->Forge[helly].ScanTurnAng;
							if(Q_Forge->Forge[helly].Angles.y > (PI*2)) Q_Forge->Forge[helly].Angles.y = 0;
							if(Q_Forge->Forge[helly].Angles.y < 0) Q_Forge->Forge[helly].Angles.y = (PI*2);

							Q_Forge->Forge[helly].STOREAngles.y = Q_Forge->Forge[helly].ScanTurnAng;

							Q_Forge->Forge[helly].QNetAngles.y = Q_Forge->Forge[helly].ScanTurnAng;
							if(Q_Forge->Forge[helly].QNetAngles.y > (PI*2)) Q_Forge->Forge[helly].QNetAngles.y -= (PI*2);
							if(Q_Forge->Forge[helly].QNetAngles.y < 0) Q_Forge->Forge[helly].QNetAngles.y = (PI*2) - Q_Forge->Forge[helly].QNetAngles.y;

							//Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[helly].ScanTurnAng);
							//Qpo->Transform_Multiply(&Q_Forge->Forge[helly].AV.Xform, &AIfriendly, &Q_Forge->Forge[helly].AV.Xform);

							//Q_Forge->Forge[helly].Xform.Matrix.load_identity();
							Q_Forge->Forge[helly].Xform.Translation.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.x;
							Q_Forge->Forge[helly].Xform.Translation.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.y;
							Q_Forge->Forge[helly].Xform.Translation.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.z;
							Q_Forge->Forge[helly].Xform.GhostTranslation.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.x;
							Q_Forge->Forge[helly].Xform.GhostTranslation.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.y;
							Q_Forge->Forge[helly].Xform.GhostTranslation.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.z;

							//Q_Forge->Forge[helly].AV.Xform.Matrix.load_identity();
							Q_Forge->Forge[helly].AV.Xform.Translation.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.x;
							Q_Forge->Forge[helly].AV.Xform.Translation.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.y;
							Q_Forge->Forge[helly].AV.Xform.Translation.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.z;
							Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.x;
							Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.y;
							Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_CellCenter.z;

							Q_Forge->Forge[helly].AnglesChg.y = 0;
							//if(Q_Forge->Forge[helly].AnglesChg.y > (PI*2)) Q_Forge->Forge[helly].AnglesChg.y -= (PI*2);
							//if(Q_Forge->Forge[helly].AnglesChg.y < 0) Q_Forge->Forge[helly].AnglesChg.y += (PI*2);

							Q_Forge->Forge[helly].AV.STR_Xform.Matrix = Q_Forge->Forge[helly].AV.Xform.Matrix;

#if 1
							float f_LatMove = (((float)rand() / 32767) - 0.5) * 1600;
							float f_LongMove = (((float)rand() / 32767) - 0.5) * 600;

							float f_LatMoveStr = 0;
							float f_LongMoveStr = 0;

							bool f_inTransit = true;
							while(f_inTransit)
								{
								if(f_LatMove >= 0)
									{
									if(f_LatMoveStr < f_LatMove)
										{
										Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].AV.Xform.Translation, 10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_StRotationVec, &Q_Forge->Forge[helly].NewPos);
										f_LatMoveStr += 10;

										if(f_LongMove >= 0)
											{
											if(f_LongMoveStr < f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].NewPos, 10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr += 10;
												}
											}
										else
											{
											if(f_LongMoveStr > f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].NewPos, -10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr -= 10;
												}
											}
										}
									else
										{
										if(f_LongMove >= 0)
											{
											if(f_LongMoveStr < f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].AV.Xform.Translation, 10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr += 10;
												}
											else f_inTransit = false;
											}
										else
											{
											if(f_LongMoveStr > f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].AV.Xform.Translation, -10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr -= 10;
												}
											else f_inTransit = false;
											}
										}
									}
								else
									{
									if(f_LatMoveStr > f_LatMove)
										{
										Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].AV.Xform.Translation, -10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_StRotationVec, &Q_Forge->Forge[helly].NewPos);
										f_LatMoveStr -= 10;

										if(f_LongMove >= 0)
											{
											if(f_LongMoveStr < f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].NewPos, 10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr += 10;
												}
											}
										else
											{
											if(f_LongMoveStr > f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].NewPos, -10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr -= 10;
												}
											}
										}
									else
										{
										if(f_LongMove >= 0)
											{
											if(f_LongMoveStr < f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].AV.Xform.Translation, 10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr += 10;
												}
											else f_inTransit = false;
											}
										else
											{
											if(f_LongMoveStr > f_LongMove)
												{
												Qpo->Vec3d_AddScaled(&Q_Forge->Forge[helly].AV.Xform.Translation, -10, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[f_Team]->m_RotationVec, &Q_Forge->Forge[helly].NewPos);
												f_LongMoveStr -= 10;
												}
											else f_inTransit = false;
											}
										}
									}

								Q_Forge->Forge[helly].AV.OldPos = Q_Forge->Forge[helly].AV.Xform.Translation;
								Q_Forge->Forge[helly].AV.NewPos = Q_Forge->Forge[helly].NewPos;
			
								Q_Forge->Forge[helly].AV.OldPos.y += 60;
								Q_Forge->Forge[helly].AV.NewPos.y += 60;

								// This does collision detection
								if(Qpo->Collision_RayTest(
												NULL, 
												NULL, 
												&Q_Forge->Forge[helly].AV.OldPos, 
												&Q_Forge->Forge[helly].AV.NewPos, 
												// GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
												//GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS,
												0xffffffff, NULL, NULL, 
												&Q_Forge->Forge[helly].AV.Collision))
									{
									Q_Forge->Forge[helly].collide = 1;
									}
								else Q_Forge->Forge[helly].collide = 0;

								Q_Forge->Forge[helly].AV.OldPos.y -= 60;
								Q_Forge->Forge[helly].AV.NewPos.y -= 60;
		
								// Set the player to the new pos
								if(Q_Forge->Forge[helly].collide == 0) Q_Forge->Forge[helly].AV.Xform.Translation = Q_Forge->Forge[helly].AV.NewPos;
								else f_inTransit = false;
								}
#else
							Q_Forge->Forge[helly].AV.Xform.Translation.x += (((float)rand() / 32767) - 0.5) * 600;
							Q_Forge->Forge[helly].AV.Xform.Translation.z += (((float)rand() / 32767) - 0.5) * 600;
#endif

							Q_Forge->Forge[helly].Q_Brain.TargetLOSTcountON = false;

							Q_Forge->Forge[helly].Q_Brain.WeaponDrawPrime = true;
							Q_Forge->Forge[helly].Q_Brain.WeaponDrawCounter = 0;

							Q_Forge->Forge[helly].HitReactionGB = 0;

							CartMins.x = -10;
							CartMins.y = -10;
							CartMins.z = -10;
							CartMaxs.x = 10;
							CartMaxs.y = 10;
							CartMaxs.z = 10;
							}

						helly++;
						}
					}
				}
			}
#endif
#endif

#if 0 
		i_CSpeechDlg->CreateGeneralTape();
#endif

#if 0
		if(KEY_PRESS_DOWN(QIN_g)) i_CSpeechDlg->acButtonSpeak("Access Denied");
#endif

	return 0;
}

int Q_Frame(void)
{
#if 0
	g_render->begin_draw();
#endif
	
	draw_scene();
	
#if 0
	g_render->set_draw2d();
#endif
		
#if 0
	draw_info();
#endif

#if 0
	g_render->end_draw();
#endif

	return 1;
}

int Q_Clear(void)
{
	for(int f_Helly = 0; f_Helly < _->NomAI; f_Helly++)
		{
		if(Q_Forge->Forge[f_Helly].LIVE == 1)
			{
			delete Q_Forge->Forge[f_Helly].AV.Avatar.Mesh;
			Q_Forge->Forge[f_Helly].LIVE = 0;
			}
		}

	return 1;
}

// Main Render Initialization
void appInit()
{
	/*if (GLEW_ATI_draw_buffers==false ||
		GLEW_ARB_vertex_program==false ||
		GLEW_ARB_fragment_program==false ||
		WGLEW_ARB_pbuffer==false)
		{
		printf("ERROR:::unRenderer cannot find extensions needed!\nRequires: GL_ATI_draw_buffers, GL_ARB_vertex_program,\nGL_ARB_fragment_program, WGL_ARB_pbuffer.\n");
		//throw;
		}

	if (WGLEW_NV_render_depth_texture==false)
		{
		HMENU menu=GetMenu(hWndMain);
		EnableMenuItem(menu,ID_VIEW_NVRENDERDEPTHTEX,MF_GRAYED);
		depthtex=false;
		}

	if (GLEW_ARB_texture_non_power_of_two==false)
		{
		HMENU menu=GetMenu(hWndMain);
		EnableMenuItem(menu,ID_RENDER_400X300,MF_GRAYED);
		EnableMenuItem(menu,ID_RENDER_640X480,MF_GRAYED);
		EnableMenuItem(menu,ID_RENDER_800X600,MF_GRAYED);
		}*/

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); // this line indicates the face you cull is the back one

	unRender = new unRenderer;

	unRender->set_program_params(depthbias,depthtex);
	unRender->mrt_create(resolutions[res][0],resolutions[res][1]);
	unRender->load_programs();
	unRender->acInit();

	//*g_render->camera.rotate(-90,pVector(1,0,0));
	//*g_render->camera.pos.vec(0,0,50);

#if 0 //defined(UNIFICATION)
	_->mesh=g_render->load_mesh(meshfile);
	_->mesh->nlight = 0;

	if (_->mesh)
		{
		g_render->target_pos=_->mesh->bbox.get_center();
		if (_->mesh->ncam)
			{
			srand(timeGetTime());
			//camera=rand()%_->mesh->ncam;
			g_render->camera=_->mesh->cam[0];
			}
		}
	else
		{
		printf("ERROR:::unRenderer failed to load scene _->mesh\n");
		throw;
		}
#endif

	//*update_menu();

#if 0
	///// Phosect Nucleus /////
	phosectNucleus = new unPhosectNucleus;
	phosectNucleus->acCreatePhosect(pVertex(g_render->camera.pos[0], g_render->camera.pos[1], g_render->camera.pos[2]));
	phosectNucleus->Initialize();
#endif

#if 0
	///// Reflective Shadow Mapping /////
	m_RSM = new RSM();
#endif

	//*unRender->sync_PhysicsMemory();
}

// shutdown app
void acClose()
{
	Q.CloseSounds();

	Q.CloseTextures();

	Q.CoreRelease();

	unRender->Shutdown();

	delete unRender;
	unRender=0;

	g_render->reset();

#if 0
	exit(-1);
#endif
}

// animate light and camera
void animate()
{
	// accumulate time
	i_time+=g_render->curdtf;

	// animate lights
	int i,j;

#if 1 //defined(UNIFICATION)
	j=_->mesh->nlight;

	for( i=0;i<j;i++ )
		{
		_->mesh->light[i].animate(i_time);
		//_->mesh->light[i].pos.x = g_render->camera.pos.x;
		//_->mesh->light[i].pos.y = g_render->camera.pos.y;
		//_->mesh->light[i].pos.z = g_render->camera.pos.z;
		//_->mesh->light[i].pos.w = 1;
		//_->mesh->light[i].anim_color.color.x = 0;
		_->mesh->light[i].pos.w = 350;
		}

	//_->mesh->light[0].pos.x = playerAV[g_Player]->Xform.Translation.x;
	//_->mesh->light[0].pos.y = playerAV[g_Player]->Xform.Translation.y;
	//_->mesh->light[0].pos.z = playerAV[g_Player]->Xform.Translation.z;
	//_->mesh->light[0].pos.w = 500;

	//_->mesh->light[1].pos.x = playerAV[g_Player]->Xform.Translation.x;
	//_->mesh->light[1].pos.y = playerAV[g_Player]->Xform.Translation.y + 35;
	//_->mesh->light[1].pos.z = playerAV[g_Player]->Xform.Translation.z;

	//_->mesh->light[2].pos.x = playerAV[g_Player]->Xform.Translation.x;
	//_->mesh->light[2].pos.y = playerAV[g_Player]->Xform.Translation.y + 35;
	//_->mesh->light[2].pos.z = playerAV[g_Player]->Xform.Translation.z;

	//_->mesh->light[0].pos.w = 1;
	//_->mesh->light[0].anim_color.color.x = 0;

	// animate camera
	//g_render->camera.animate(i_time);
	//g_render->set_camera();
#endif
}

#include <math.h>

void ChangeLevel(void)
{
	g_LevelFactor += ((float)rand() / 32767) * 40;

	if(g_LevelFactor >= 1000)
		{
		g_LevelFactor = 1000;
		}

	int f_NomGroup = 3;// ((int)g_LevelFactor / 20;
	int f_NomTeam = 3;// ((int)g_LevelFactor / 10;

	if(QTEAM_CAP)
		{
		f_NomTeam = QTEAM_SIZE;
		}
	else
		{
		if(g_LevelFactor > 150)
			{
			f_NomTeam = 1;
			}
		else
			{
			if(f_NomTeam > 5)
				{
				f_NomTeam = 5;
				}
			}
		}

	for(int f_Skip = 0; f_Skip < f_NomGroup; f_Skip++)
		{
		const int f_Team = (rand() % f_NomTeam) + 1;
		const int f_AvatarCount = 3 + (rand() % (int)(g_LevelFactor / 15));
		QpoVec3d f_GroupPosition;
		QpoVec3d f_AvatarPosition;

		f_GroupPosition.x = (((float)rand() / 32767) - 0.5) * 500;
		f_GroupPosition.y = 0;
		f_GroupPosition.z = (((float)rand() / 32767) - 0.5) * 500;

		for(int f_AVC = 0; f_AVC < f_AvatarCount; f_AVC++)
			{
			if(g_Index >= QNOMAI + 10)
				{
				g_Index = 0;
				g_IndexLock = true;
				}

			f_AvatarPosition.x = f_GroupPosition.x + (((float)rand() / 32767) - 0.5) * 38;
			f_AvatarPosition.y = 0;
			f_AvatarPosition.z = f_GroupPosition.z + (((float)rand() / 32767) - 0.5) * 38;

			if (g_IndexLock)
				{
				QActiveFrameWork->acRespawnAvatar(g_Index);
				::Q_Forge->Forge[g_Index].Team = f_Team;

				::Q_Forge->Forge[g_Index].AV.Xform.Translation = f_AvatarPosition;
				}
			else
				{
				QActiveFrameWork->acSpawnAvatar(g_Index, rand() % player[g_Player]->BFO.NomCharacters, rand() % 5, f_Team, f_AvatarPosition, -1, 0);
				}

			g_Index++;
			}
		}
}

void ChangeLevel(float f_X, float f_Y, float f_Z)
{
	g_LevelFactor += ((float)rand() / 32767) * 4.0f;

	if(g_LevelFactor >= 350.0f)
		{
		g_LevelFactor = 0.0f;
		}

	int f_NomGroup = (int)g_LevelFactor / 20;
	int f_NomTeam = (int)g_LevelFactor / 10;

	if(f_NomGroup <= 0 || f_NomGroup > 4)
		{
		f_NomGroup = 1;
		}

	if(f_NomTeam <= 0 || f_NomTeam > 4)
		{
		f_NomTeam = 1;
		}

	if(QTEAM_CAP)
		{
		f_NomTeam = QTEAM_SIZE;
		}

	for(int f_Skip = 0; f_Skip < f_NomGroup; f_Skip++)
		{
		int f_Team = (rand() % f_NomTeam) + 1;
		int f_AvatarCount = 1 + ((int)g_LevelFactor / 25);
		if(f_AvatarCount > 4) f_AvatarCount = 4;
		QpoVec3d f_GroupPosition;
		QpoVec3d f_AvatarPosition;

		f_GroupPosition.x = f_X + (((float)rand() / 32767) - 0.5) * 300;
		f_GroupPosition.y = 0;
		f_GroupPosition.z = f_Z + (((float)rand() / 32767) - 0.5) * 300;

		for(int f_AVC = 0; f_AVC < f_AvatarCount; f_AVC++)
			{
			f_AvatarPosition.x = f_GroupPosition.x + (((float)rand() / 32767) - 0.5) * 38;
			f_AvatarPosition.y = 0;
			f_AvatarPosition.z = f_GroupPosition.z + (((float)rand() / 32767) - 0.5) * 38;

			QActiveFrameWork->acSpawnAvatar(0, rand() % player[g_Player]->BFO.NomCharacters, rand() % 5, f_Team, f_AvatarPosition, -1, 0);
			}
		}
}

bool acSpawnAvatar(int f_Index, int f_CharID, int f_BDataID, int f_Team, QpoVec3d f_Position, int f_BoneStructure, int f_SpawnPnt, bool level)
{
	return QActiveFrameWork->acSpawnAvatar(0, f_CharID, f_BDataID, f_Team, f_Position, f_BoneStructure, f_SpawnPnt, level);
}

// draws main scene (single quad polygon)
void draw_scene()
{
	ApplicationFocus = 1;

	unRender->draw_avatars();

	QActiveFrameWork->acWorldFrame();

	QActiveFrameWork->acQFrame();
}

// draw 2d text with demo informations
void draw_info()
{
	// screen size
	int sx=g_render->sizex;
	int sy=g_render->sizey;
	unRender->m_sizex=g_render->sizex;
	unRender->m_sizey=g_render->sizey;

	// compute lighting
	if(around)
		{
		//*cgGLSetParameter1f(unRender->m_around_seedst, ((float)rand() / 32767));

		//*cgGLSetParameter1f(unRender->m_around_white_out, 0);

		//*cgGLSetParameter1f(unRender->m_around_ScreenWidth, g_render->sizex);
		//*cgGLSetParameter1f(unRender->m_around_ScreenHeight, g_render->sizey);
		//*cgGLSetParameter1f(unRender->m_around_ScreenDepth, 10000);

		//*cgGLSetParameter1f(unRender->m_around_var_Final_Attenuation, 0.38);
		//*cgGLSetParameter1f(unRender->m_around_var_Radius123_Boost, 2.3);
		//*cgGLSetParameter1f(unRender->m_around_var_Cutoff_Threshold, 6.5);

		unRender->draw_lights(_->mesh, scissor, AOGI_AROUND);
		}
	else
		{
		////-= Without AOGI Shaders -=////
		unRender->draw_lights(_->mesh, scissor);
		}

	// draw antialias (blur edges)
	if (antialias) unRender->draw_antialias();

	// compute bloom
	if (bloom) unRender->draw_bloom();

	// draw final image to screen
	unRender->draw_final(sx,sy);

	//*QActiveFrameWork->m_GUI->acFrame();

	QActiveFrameWork->acNetFrame();

	if(player[g_Player]->BFO.GameTypeSelect == 1)
		{
		QActiveFrameWork->m_QSpawnPntController->acSpawnFrame();
		}

	// draw debug mrt textures
	if (debug) unRender->draw_debug(sx,sy);

	if (g_render->info)
		{
		// draw fps
		//glColor4f(1,1,0,1);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		/*pString str;
		switch(mode)
			{
			case 0: str="Normal Mapping"; break;
			case 1: str="Relief Mapping"; break;
			}

		g_render->draw_text(0,0,str,16);
		str.format("FPS: %i",g_render->curfps);
		g_render->draw_text(0,16,str,16);
		str.format("Lights: %i/%i",unRender->m_num_lights_drawn,_->mesh->nlight);
		g_render->draw_text(0,32,str,16);
		str.format("Scissor: %i%%",unRender->m_percent_pixel_drawn);
		g_render->draw_text(0,48,str,16);

		str.format("CamPos[0]: %f", g_render->camera.pos[0]);
		g_render->draw_text(0,66,str,16);

		str.format("CamPos[1]: %f", g_render->camera.pos[1]);
		g_render->draw_text(0,84,str,16);

		str.format("CamPos[2]: %f", g_render->camera.pos[2]);
		g_render->draw_text(0,102,str,16);*/
		}
	else
		{
		//glColor4f(0,0.4,0.4,1);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		int f_counterlimit = 5;

		if(g_unCoutcnt < f_counterlimit) f_counterlimit = g_unCoutcnt;

		//##### Unification Console #####//
		if(g_unCoutcnt == g_unCoutcntSTR)
			{
			for(int f_count = 0; f_count < f_counterlimit; f_count++)
				{
				//pString stringy(g_unConsoleText[f_count].c_str());
				//g_render->draw_text(8, 8 + (f_count * 18), stringy, 16);
				}
			}
		else
			{
			g_unCoutcntSTR = g_unCoutcnt;

			for(int f_count = 0; f_count < f_counterlimit; f_count++)
				{
				g_unConsoleText[f_count] = g_unConsole_vec_str[(g_unCoutcnt - 1) - ((f_counterlimit - 1) - f_count)];
				//pString stringy(g_unConsoleText[f_count].c_str());
				//g_render->draw_text(8, 8 + (f_count * 18), stringy, 16);
				}
			}
		//##### Unification Console #####//
		}

	if(g_render->infoedit)
		{
		// draw fps
		//glColor4f(1,1,0,1);

		//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_BLEND);

		/*pString str;
		str="ANGEL EDIT MODE";
		g_render->draw_text(15,23,str,16);
		str.format("ON/OFF: %d", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.ANGELEDITFLAG);
		g_render->draw_text(15,36,str,16);
		str.format("Map: %s", Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPNAME);
		g_render->draw_text(15,49,str,16);
		str.format("Map Number: %d", _->ANGELeditMAPNUM);
		g_render->draw_text(15,66,str,16);
		str.format("RED: %f", _->ANGELeditBitmapRed);
		g_render->draw_text(50,79,str,16);
		str.format("GREEN: %f", _->ANGELeditBitmapGreen);
		g_render->draw_text(50,92,str,16);
		str.format("BLUE: %f", _->ANGELeditBitmapBlue);
		g_render->draw_text(50,105,str,16);*/
		}

#if 1
		//#######----"" Health and energy bars plus nameplate ""----######//
		//glColor4f(0.7,1,0,1);

		//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_BLEND);

		/*pString strplayername;
		pString strenemyname;
		pString strhealth;
		pString strenergy;
		pString strarmour;
		pString strends;

		// Start input
		int f_xstart = g_render->sizex / 2;
		int f_ystart = 23;

		// Determine spaces
		int f_spaceforname = 125;
		int f_spaceforletter = 12;
		int f_spaceforheight = 18;
		int f_bothbars = (g_render->sizex / 2) - (f_spaceforname * 2);

		// Subtract start and end pieces
		f_bothbars -= 24;

		int f_onebar = f_bothbars / 2;

		if(player[g_Player]->HB_LastAvatarHitID >= 0 && player[g_Player]->HB_LastAvatarHitID < _->NomAI)
			{
			float f_playerhbar = f_onebar*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth);
			float f_avatarhbar = f_onebar*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth);
			float f_playerpbar = f_onebar*((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy);
			float f_avatarpbar = f_onebar*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy);
			float f_playerabar = f_onebar*((float)player[g_Player]->HB_Armour/(float)player[g_Player]->HB_MaxArmour);
			float f_avatarabar = f_onebar*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Armour / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxArmour);

			if(f_avatarabar != f_avatarabar) f_avatarabar = 0;

			if(f_playerhbar < 0) f_playerhbar = 0;
			if(f_avatarhbar < 0) f_avatarhbar = 0;
			if(f_playerpbar < 0) f_playerpbar = 0;
			if(f_avatarpbar < 0) f_avatarpbar = 0;
			if(f_playerabar < 0) f_playerabar = 0;
			if(f_avatarabar < 0) f_avatarabar = 0;

			if(f_playerhbar > f_onebar) f_playerhbar = f_onebar;
			if(f_avatarhbar > f_onebar) f_avatarhbar = f_onebar;
			if(f_playerpbar > f_onebar) f_playerpbar = f_onebar;
			if(f_avatarpbar > f_onebar) f_avatarpbar = f_onebar;
			if(f_playerabar > f_onebar) f_playerabar = f_onebar;
			if(f_avatarabar > f_onebar) f_avatarabar = f_onebar;

			if(player[g_Player]->HB_LastAvatarHitID < 0)
				{
				f_avatarhbar = 0;
				f_avatarpbar = 0;
				f_avatarabar = 0;
				}

			char i_Life = 3;
			strhealth.format("%c", i_Life);
			strenergy.format("-");
			strarmour.format("^");
			strends.format("||");

			strplayername.format("%s", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Name);
			strenemyname.format("%s", Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].CharDATA.Name);

			//######################//
			//#- Draw HEALTH bars -#//
			//######################//

			//glColor4f(1 - (float)((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth), (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth, 0, 1);

			g_render->draw_text(f_xstart + 45, f_ystart, strenemyname, 16);
			g_render->draw_text(f_xstart + f_spaceforname, f_ystart, strends, 16);

			int f_xbarstart = f_xstart + f_spaceforname + f_spaceforletter + (f_onebar - f_avatarhbar);

			for(int f_count = 0; f_count < (int)f_avatarhbar; f_count += f_spaceforletter)
				{
				g_render->draw_text(f_xbarstart + f_count, f_ystart, strhealth, 16);
				}

			g_render->draw_text(f_xstart + f_spaceforname + f_spaceforletter + f_onebar, f_ystart, strends, 16);

			//glColor4f(1 - (float)((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth), (float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth, 0, 1);

			g_render->draw_text(f_xstart + f_spaceforname + f_spaceforletter + f_onebar + f_spaceforletter, f_ystart, strends, 16);

			f_xbarstart = f_xstart + f_spaceforname + f_spaceforletter + f_onebar + f_spaceforletter + f_spaceforletter;

			for(int f_count = 0; f_count < (int)f_playerhbar; f_count += f_spaceforletter)
				{
				g_render->draw_text(f_xbarstart + f_count, f_ystart, strhealth, 16);
				}
		
			g_render->draw_text(f_xbarstart + f_onebar, f_ystart, strends, 16);
			g_render->draw_text(f_xbarstart + f_onebar + f_spaceforletter, f_ystart, strplayername, 16);

			//######################//
			//#- Draw ENERGY bars -#//
			//######################//

			// Increment Height
			f_ystart += f_spaceforheight;
			for(int f_aicount = 0; f_aicount < _->NomAI; f_aicount++)
				{
				//glColor4f(1, 1, 1 - (float)((float)Q_Forge->Forge[f_aicount].HB_Energy / (float)Q_Forge->Forge[f_aicount].HB_MaxEnergy), 1);

				if(f_aicount == player[g_Player]->HB_LastAvatarHitID) g_render->draw_text(f_xstart + f_spaceforname, f_ystart, strends, 16);

				f_xbarstart = f_xstart + f_spaceforname + f_spaceforletter + (f_onebar - f_avatarpbar);

				for(int f_count = (int)f_avatarabar; f_count < (int)f_onebar; f_count += f_spaceforletter)
					{
					pString f_pString;

					if(f_count >= m_vec_EnergyGlyphsAv[f_aicount].size())
						{
						char f_Char = rand() % 255;

						f_pString.format("%c", f_Char);
						m_vec_EnergyGlyphsAv[f_aicount].push_back(f_Char);

						g_EnergyCntlCharAv[f_aicount] = f_Char;
						}
					else
						{
						f_pString.format("%c", m_vec_EnergyGlyphsAv[f_count]);

						g_EnergyCntlCharAv[f_aicount] = m_vec_EnergyGlyphsAv[f_aicount][f_count];
						}

					if(f_aicount == player[g_Player]->HB_LastAvatarHitID) g_render->draw_text(f_xbarstart + f_count, f_ystart, f_pString, 16);
					}
				}

			g_render->draw_text(f_xstart + f_spaceforname + f_spaceforletter + f_onebar, f_ystart, strends, 16);

			//glColor4f(1, 1, 1 - (float)((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy), 1);

			g_render->draw_text(f_xstart + f_spaceforname + f_spaceforletter + f_onebar + f_spaceforletter, f_ystart, strends, 16);

			//glColor4f(0.35, 0.35, 0.35, 1);

			for(int f_count = (int)f_avatarabar; f_count < (int)f_onebar; f_count += f_spaceforletter)
				{
				g_render->draw_text(f_xbarstart + f_count, f_ystart + 18, strarmour, 16);
				}

			//glColor4f(1, 1, 1 - (float)((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy), 1);

			f_xbarstart = f_xstart + f_spaceforname + f_spaceforletter + f_onebar + f_spaceforletter + f_spaceforletter;

			for(int f_count = 0; f_count < (int)f_playerpbar; f_count += f_spaceforletter)
				{
				pString f_pString;

				if(f_count >= m_vec_EnergyGlyphsPl.size())
					{
					char f_Char = rand() % 255;

					f_pString.format("%c", f_Char);
					m_vec_EnergyGlyphsPl.push_back(f_Char);

					g_EnergyCntlCharPl = f_Char;
					}
				else
					{
					f_pString.format("%c", m_vec_EnergyGlyphsPl[f_count]);

					g_EnergyCntlCharPl = m_vec_EnergyGlyphsPl[f_count];
					}

				g_render->draw_text(f_xbarstart + f_count, f_ystart, f_pString, 16);
				}
		
			g_render->draw_text(f_xbarstart + f_onebar, f_ystart, strends, 16);

			f_ystart += f_spaceforheight;

			//glColor4f(0.35, 0.35, 0.35, 1);

			for(int f_count = 0; f_count < (int)f_playerabar; f_count += f_spaceforletter)
				{
				g_render->draw_text(f_xbarstart + f_count, f_ystart, strarmour, 16);
				}
			}*/
#endif

	// draw Shadow Effect
	//unRender->DrawBlur(25, 0.02f);

	//update_menu();
}

// key processing
void key_pressed(int key,int flags)
{
	if (_->mesh && _->mesh->ncam>0)
	if (key>='1' && key<='9')
		{
		camera=key-'1';
		if (camera>=_->mesh->ncam) return;
		g_render->camera=_->mesh->cam[camera];
		update_menu();
		i_time=0;
		}

	if (key=='o')
		{
		Qpo->Transform_New_YRotation(&AIfriendly, -0.1);	/// Originaly -
		Qpo->Transform_Multiply(&playerAV[g_Player]->Xform, &AIfriendly, &playerAV[g_Player]->Xform);
		printf("Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, -0.1);\n");
		}

	if(key=='p')
		{
		Qpo->Transform_New_YRotation(&AIfriendly, 0.1);	/// Originaly -
		Qpo->Transform_Multiply(&playerAV[g_Player]->Xform, &AIfriendly, &playerAV[g_Player]->Xform);
		printf("Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, 0.1);\n");
		}
}

// update menu state
void update_menu()
{
	/*HMENU menu=GetMenu(hWndMain);
	CheckMenuItem(menu,ID_VIEW_DEPTHBIAS,depthbias?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_BLOOM,bloom?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_SCISSOR,scissor?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_NVRENDERDEPTHTEX,depthtex?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_DEBUG,debug?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_INFORMATION,g_render->info?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_FRAMEMEMORY,g_render->framememory?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_ANTIALIAS,antialias?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_AROUND,around?MF_CHECKED:MF_UNCHECKED);
	CheckMenuRadioItem(menu,ID_VIEW_FREECAMERA,ID_VIEW_FREECAMERA+2,ID_VIEW_FREECAMERA+camera,0);
	CheckMenuRadioItem(menu,ID_VIEW_NORMAL,ID_VIEW_NORMAL+2,ID_VIEW_NORMAL+mode,0);
	CheckMenuRadioItem(menu,ID_RENDER_256X256,ID_RENDER_256X256+4,ID_RENDER_256X256+res,0);
	CheckMenuRadioItem(menu,ID_SCREEN_640X480,ID_SCREEN_640X480+5,ID_SCREEN_640X480+scrres,0);*/
}

// open a file dialog window
int OpenFileDialog(const char *title,const char *filter,const char *ext,const char *initdir,char *filename,int len)
{
	/*OPENFILENAME ofn;
	memset(&ofn,0,sizeof(OPENFILENAME));
	
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hWndMain;
	ofn.hInstance=hInstance;
	ofn.lpstrFilter=filter;
	ofn.lpstrDefExt=ext;
	ofn.lpstrInitialDir=initdir;
	ofn.lpstrTitle=title;
	ofn.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	ofn.lpstrFile=filename;
	ofn.nMaxFile=len;

	if (GetOpenFileName(&ofn))
		return 1;*/
	return 0;
}

// process window commands
void command(UINT msg, WPARAM wParam, LPARAM lParam)
{
	/*switch( LOWORD(wParam) )
		{
		case ID_FILE_LOADMESH:
			{
			char filename[MAX_PATH]="";
			if (OpenFileDialog("Open P3D","P3D mesh fils (*.p3d)\0*.p3d\0\0","*.p3d",g_render->app_path+"data\\",filename,255))
				{
				pString str;
				str=filename;
				if (check_path(g_render->app_path,filename,str))
					{
					meshfile=str;
					_->mesh=g_render->load_mesh(meshfile, 1);
					if (_->mesh) g_render->target_pos=_->mesh->bbox.get_center();
					else meshfile="";
					_->mesh->nlight = 0;
					}
				}
			}
			break;
		case ID_VIEW_FREECAMERA:
		case ID_VIEW_ANIMCAMERA:
		case ID_VIEW_ANIMCAMERA2:
			key_pressed('1'+((LOWORD(wParam)-ID_VIEW_FREECAMERA)),0);
			break;

		case ID_SCREEN_640X480:
		case ID_SCREEN_800X600:
		case ID_SCREEN_960X600:
		case ID_SCREEN_1024X768:
		case ID_SCREEN_1152X864:
		case ID_SCREEN_1280X1024:
		case ID_SCREEN_1366X768:
			{
			scrres=LOWORD(wParam)-ID_SCREEN_640X480;
			g_render->sizex = screenres[scrres][0];
			g_render->sizey = screenres[scrres][1];
			_->screenx = screenres[scrres][0];
			_->screeny = screenres[scrres][1];

			int j = -1;
			for( i=0;i<g_render->videomode.num;i++ )
			if (g_render->videomode[i].dmPelsWidth==(unsigned int)g_render->sizex &&
				g_render->videomode[i].dmPelsHeight==(unsigned int)g_render->sizey)
				{
				if ((int)g_render->videomode[i].dmDisplayFrequency>j && g_render->videomode[i].dmDisplayFrequency<=120)
					{
					j=g_render->videomode[i].dmDisplayFrequency;
					g_render->selvideomode=i;
					}
				}

			QActiveFrameWork->m_GUI->acVidResize((unsigned int)g_render->sizex, (unsigned int)g_render->sizey);
			ChangeDisplaySettings(&g_render->videomode[g_render->selvideomode], NULL);
			update_menu();
			} break;

		case ID_VIEW_FULLSETTINGS:
			{
			bloom = false;
			antialias= true;
			around = true;

			g_render->set_fullscreen(!g_render->fullscreen);
			mfullscreen = g_render->fullscreen;
			if(g_render->fullscreen) ShowCursor(false);

			unRender->mrt_destroy();
			res = 4;
			unRender->mrt_create(resolutions[res][0],resolutions[res][1]);
			
			scrres = 5;

#pragma message("Default screen highest setting")
#if 0 ///Original
			g_render->sizex = 1280;
			g_render->sizey = 1024;
			_->screenx = 1280;
			_->screeny = 1024;
#endif

#if 0 ///Laptop setting
			g_render->sizex = 1366;
			g_render->sizey = 768;
			_->screenx = 1366;
			_->screeny = 768;
#endif

#if 1 ///Spylon Dialus
			g_render->sizex = 1920;
			g_render->sizey = 1080;
			_->screenx = 1920;
			_->screeny = 1080;
#endif

			int j = -1;
			for( i=0;i<g_render->videomode.num;i++ )
			if (g_render->videomode[i].dmPelsWidth==(unsigned int)g_render->sizex &&
				g_render->videomode[i].dmPelsHeight==(unsigned int)g_render->sizey)
				{
				if ((int)g_render->videomode[i].dmDisplayFrequency>j && g_render->videomode[i].dmDisplayFrequency<=120)
					{
					j=g_render->videomode[i].dmDisplayFrequency;
					g_render->selvideomode=i;
					}
				}

			QActiveFrameWork->m_GUI->acVidResize((unsigned int)g_render->sizex, (unsigned int)g_render->sizey);
			ChangeDisplaySettings(&g_render->videomode[g_render->selvideomode], NULL);
			update_menu();
			} break;

		case ID_RENDER_256X256:
		case ID_RENDER_400X300:
		case ID_RENDER_512X512:
		case ID_RENDER_640X480:
		case ID_RENDER_800X600:
			unRender->mrt_destroy();
			res=LOWORD(wParam)-ID_RENDER_256X256;
			unRender->mrt_create(resolutions[res][0],resolutions[res][1]);
			update_menu();
			break;

		case ID_VIEW_DEPTHBIAS:
			unRender->free_programs();
			depthbias=!depthbias;
			unRender->set_program_params(depthbias,depthtex);
			unRender->load_programs();
			update_menu();
			break;

		case ID_VIEW_BLOOM:
			bloom=!bloom;
			update_menu();
			break;

		case ID_VIEW_DEBUG:
			debug=!debug;
			update_menu();
			break;

		case ID_VIEW_SCISSOR:
			scissor=!scissor;
			update_menu();
			break;

		case ID_VIEW_ANTIALIAS:
			antialias=!antialias;
			update_menu();
			break;

		case ID_VIEW_AROUND:
			around=!around;
			update_menu();
			break;

		case ID_VIEW_FRAMEMEMORY:
			g_render->framememory=!g_render->framememory;
			update_menu();
			break;

		case ID_VIEW_NORMAL:
		case ID_VIEW_RELIEF:
			unRender->free_programs();
			mode=LOWORD(wParam)-ID_VIEW_NORMAL;
			unRender->set_program_params(depthbias,depthtex);
			unRender->load_programs();
			update_menu();
			break;

		case ID_VIEW_NVRENDERDEPTHTEX:
			unRender->mrt_destroy();
			unRender->free_programs();
			depthtex=!depthtex;
			unRender->set_program_params(depthbias,depthtex);
			unRender->mrt_create(resolutions[res][0],resolutions[res][1]);
			unRender->load_programs();
			update_menu();
			break;

		case ID_VIEW_INFORMATION:
			g_render->info=!g_render->info;
			update_menu();
			break;

		case ID_EXIT:
			acClose();
			//DestroyWindow(hWndMain);
			m_Running = false;
			break;

		case ID_VIEW_FULLSCREEN:
			g_render->set_fullscreen(!g_render->fullscreen);
			mfullscreen = g_render->fullscreen;
			ShowCursor(false);
			break;

		case ID_ABOUT:
			{
			MessageBox(
				hWndMain,
				"Unification OpenGL Renderer\nwww.osirem.com\n",
				appname,
				MB_ICONINFORMATION|MB_OK);
			}break;

		case ID_CHARACTERDIALOG:
			{
			if(g_startcommand == 0)
				{
				if(QActiveFrameWork->acStartInit())
					{
					if(g_optionsresult == 3)
						{
						printf("-SUCCESS-:::acStartInit:::AMATCH Starting Online Multiplayer GAME Finished.\n");
						}
					else printf("-SUCCESS-:::acStartInit:::S_Player Starting Single Player GAME Finished.\n");
					}
				else
					{
					unConsoleAttribute(CONSOLE_ERROR);
					if(g_optionsresult == 3)
						{
						printf("|||ERROR|||:::acStartInit:::AMATCH -FAILED- Starting Online Multiplayer GAME.\n");
						printf("|||ERROR|||:::acStartInit:::AMATCH Check connection and try again,\n");
						printf("|||ERROR|||:::acStartInit:::AMATCH if persists contact osirem@ymail.com or");
						printf("|||ERROR|||:::acStartInit:::AMATCH (search) post on the OSIREM forums here osirem.com/forum.\n");
						}
					else
						{
						printf("|||ERROR|||:::acStartInit:::S_Player -FAILED- Starting Single Player GAME.\n");
						printf("|||ERROR|||:::acStartInit:::S_Player Please try again (sometimes delete game folder and re-run patch server to DL again),\n");
						printf("|||ERROR|||:::acStartInit:::S_Player if persists contact osirem@ymail.com or");
						printf("|||ERROR|||:::acStartInit:::S_Player (search) post on the OSIREM forums here osirem.com/forum.\n");
						}
					unConsoleAttribute(CONSOLE_INIT);
					for(;;) { }
					}
				}
			else
				{
#ifdef QAMOD_ARENA
				g_optionsresult = Q.ShowCharacterDialog();
#endif
				}
			}break;
		}

	if(g_render)
		{
		if(g_render->fullscreen == 0)
			{
			while(ShowCursor(true)<=0);
			}
		if(g_render->fullscreen == 1) ShowCursor(false);
		}
	else ShowCursor(true);*/

#if 0
	g_render->save_ini();
#endif
}