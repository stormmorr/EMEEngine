#include "paralelo3d.h"
#include "unRenderer.h"
#include "resource.h"

#include "../tgaload.h"
#include "../../Lighting/unPhosectNucleus.h"
#include "../../Lighting/RSM.h"
#include "../../QActiveFramewrk.h"

char *appname = "Unification Renderer";
char app_path[256];

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")

extern HWND hWndMain;
extern HINSTANCE hInstance;

void draw_scene();
void draw_info();
void key_pressed(int key,int flags);
void animate();
void appInit();
void appClose();
void update_menu();
void command(UINT msg, WPARAM wParam, LPARAM lParam);

pString meshfile("data\\p3dscene.p3d");	// geometry file
//pString meshfile("data\\scene.p3d");	// geometry file
//pString meshfile("data\\p3dmesh.p3d");	// geometry file

namespace GVARS
{
pMesh *mesh=0;	// geometry object
}

unRenderer *unRender=0;	// relief object
unPhosectNucleus *phosectNucleus;
RSM *m_RSM;

bool info=true;
bool bloom=false;
bool debug=false;
bool scissor=true;
bool depthtex=true;
bool depthbias=false;
bool antialias=false;

int resolutions[5][2]={ {256,256} , {400,300}, {512,512} , {640,480} , {800,600} };
int res=2;
int mode=1;
int camera=0;
float time=0;

int active=0;
int mouse=0,mousex,mousey;

HWND hWndMain;
HINSTANCE hInstance;

LRESULT CALLBACK WinFunc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
		{
		case WM_KEYDOWN:
		key = (char)wParam;

        switch (key)
			{
			//##### Keylogger for Left To Forward Jink
			case 'A':
				{
				player.KL_LeftToFor = 1;

				if(player.KL_ForToLeft == 1)
					{
					player.KL_ForToLeft = 2;
					player.KL_LeftToFor = 0;
					}
				} break;

			//##### Keylogger for Right To Forward Jink
			case 'D':
				{
				player.KL_RightToFor = 1;

				if(player.KL_ForToRight == 1)
					{
					player.KL_ForToRight = 2;
					player.KL_RightToFor = 0;
					}
				} break;

			//##### Keylogger for Forward Jinks
			case 'W':
				{
				player.KL_ForToLeft = 1;
				player.KL_ForToRight = 1;

				if(player.KL_LeftToFor == 1)
					{
					player.KL_LeftToFor = 2;
					player.KL_ForToLeft = 0;
					}

				if(player.KL_RightToFor == 1)
					{
					player.KL_RightToFor = 2;
					player.KL_ForToRight = 0;
					}

				if(player.KL_BlockToFor == 1)
					{
					player.KL_BlockToFor = 2;
					}
				} break;

			//##### Keylogger for Block Jinks
			case 'S':
				{
				//player.KL_BlockToFor = 1;
				} break;
			}
		break;

		QAGE::QActiveFramewrk::instance()->m_GUI->acKeyDown(key);
        break;

	  case WM_KEYUP:
		key = (char)wParam;

        switch (key)
			{
			//##### Keylogger for Left To Forward Jink - Stage Three
			case 'A':
				{
				if(player.KL_LeftToFor == 2)
					{
					player.KL_LTFSpecLevel++;

					player.KL_Timer = TIME;

					//QpoSound3D_GetConfig(World, &player.ViewXForm, &player.ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					Qpo->Sound_Play(S_KeyLog, Volume, Pan, S_TimeScale, FALSE);
					}

				player.KL_LeftToFor = 0;
				player.KL_ForToLeft = 0;
				player.KL_ForToRight = 0;
				player.KL_RightToFor = 0;
				} break;

			//##### Keylogger for Right To Forward Jink - Stage Three
			case 'D':
				{
				if(player.KL_RightToFor == 2)
					{
					player.KL_RTFSpecLevel++;

					player.KL_Timer = TIME;

					//QpoSound3D_GetConfig(World, &player.ViewXForm, &player.ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					Qpo->Sound_Play(S_KeyLog, Volume, Pan, S_TimeScale, FALSE);
					}

				player.KL_LeftToFor = 0;
				player.KL_ForToLeft = 0;
				player.KL_ForToRight = 0;
				player.KL_RightToFor = 0;
				} break;

			//##### Keylogger for Forward To Left OR Right Jink - Stage Three
			case 'W':
				{
				if(player.KL_ForToLeft == 2)
					{
					player.KL_FTLSpecLevel++;

					player.KL_Timer = TIME;

					//QpoSound3D_GetConfig(World, &player.ViewXForm, &player.ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					Qpo->Sound_Play(S_KeyLog, Volume, Pan, S_TimeScale, FALSE);
					}

				if(player.KL_ForToRight == 2)
					{
					player.KL_FTRSpecLevel++;

					player.KL_Timer = TIME;

					//QpoSound3D_GetConfig(World, &player.ViewXForm, &player.ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					Qpo->Sound_Play(S_KeyLog, Volume, Pan, S_TimeScale, FALSE);
					}

				player.KL_LeftToFor = 0;
				player.KL_ForToLeft = 0;
				player.KL_ForToRight = 0;
				player.KL_RightToFor = 0;
				} break;

			//##### Keylogger for Right To Forward Jink - Stage Three
			case 'S':
				{
				if(player.KL_BlockToFor == 2)
					{
					player.KL_BTFSpecLevel++;

					player.KL_LTFSpecLevel = 0;
					player.KL_RTFSpecLevel = 0;
					player.KL_FTLSpecLevel = 0;
					player.KL_FTRSpecLevel = 0;

					player.KL_BTimer = TIME;

					//QpoSound3D_GetConfig(World, &player.ViewXForm, &player.ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					Qpo->Sound_Play(S_KeyLog, Volume, Pan, S_TimeScale, FALSE);
					}
				} break;

			} break;

		case WM_LBUTTONDOWN:
			{
			lbuttonklik=1;
			player.WeaponFire = 1;
			QAGE::QActiveFramewrk::instance()->acGuiEvents(QAGE::QActiveFramewrk::instance()->m_GUI->acMouseClick());
			} break;

		case WM_RBUTTONDOWN:
			{
			rbuttonklik=1;
			} break;

		case WM_MBUTTONDOWN:
			{
			mbuttonklik=1;
			} break;

		case 0x020A:	//### Mouse Wheel Scroll
			{
			mwheelroll=1;
			} break;

		case WM_CREATE:
			{
			hWndMain=hWnd;

			render_init(app_path,hWnd,0);

			if (g_render->load_font("data\\fonts.tga")!=-1) g_render->sel_font(0);
			appInit();

			if(!g_render)
				{
				printf("ERROR:::OpenGL initialization failed...\n");
				for(;;) {};
				}
			} break;

		case WM_SIZE:
			if (g_render) g_render->resize(LOWORD(lParam),HIWORD(lParam));
			break;

		case WM_DESTROY:
			appClose();
			render_free();
			PostQuitMessage(0);
			break;

		case WM_ERASEBKGND:
			if (g_render) return 1;
			else return 0;

		case WM_CHAR:
			if (g_render) key_pressed(wParam,GetAsyncKeyState(VK_SHIFT)&0x80000000);
 			return 0;

		case WM_PAINT:
			{
			g_render->begin_draw();
			draw_scene();
			g_render->set_draw2d();
			draw_info();
			g_render->end_draw(); 
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
			//float rotspeed=0.05f;
			//float panspeed=0.2f;

			//int dx=(short)LOWORD(lParam)-mousex;
			//int dy=(short)HIWORD(lParam)-mousey;

			mousex=(short)LOWORD(lParam);
			mousey=(short)HIWORD(lParam);

			QAGE::QActiveFramewrk::instance()->m_GUI->acMouseMotion(mousex, mousey);
			//QAGE::QActiveFramewrk::instance()->acGameEventsFrame();
			} break;
		}

	return DefWindowProc (hWnd, msg, wParam, lParam);
}

//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lp, int nCmd)
int main (int argc, char* argv[])
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS wcl;
	MSG  msg;

	hInstance=hInst;
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	char *c,*cmdline=GetCommandLine();
	if (cmdline[0]=='"') 
		{
		cmdline++;
		c=strchr(cmdline,'"');
		if (c) *c=0;
		}
	else
		{
		c=strchr(cmdline,' ');
		if (c) *c=0;
		}

	strcpy(app_path,cmdline);
	c=strrchr(app_path,'\\');
	if (c) *(c+1)=0;

	wcl.style			= CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc		= (WNDPROC)WinFunc;
	wcl.cbClsExtra		= 0;
	wcl.cbWndExtra		= 0;
	wcl.hInstance		= hInst;
	wcl.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
	wcl.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground	= 0;
	wcl.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU);
	wcl.lpszClassName	= "glWin32";

	if (!RegisterClass (&wcl))
		{
		printf("ERROR:::main can't register Window\n");
		for(;;) {};
		}

	CreateWindowEx(	0,"glWin32",appname,
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,CW_USEDEFAULT,160,120,
					NULL,NULL,hInst,NULL);

	ShowWindow (hWndMain, SW_NORMAL);

	while (1) 
		{
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE) 
			{
			if (GetMessage(&msg, NULL, 0, 0)) 
				{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
					{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					}
				}
			else return TRUE;
			}

		g_render->update();

		if (active)
			{
			g_render->check_input();
			g_render->update_camera();
			}

		animate();
		g_render->begin_draw();
		draw_scene();
		g_render->set_draw2d();
		draw_info();
		g_render->end_draw();
		}
}

// Main Render Initialization
void appInit()
{	
	if (GLEW_ATI_draw_buffers==false ||
		GLEW_ARB_vertex_program==false ||
		GLEW_ARB_fragment_program==false ||
		WGLEW_ARB_pbuffer==false)
		{
		printf("ERROR:::unRenderer cannot find extensions needed!\nRequires: GL_ATI_draw_buffers, GL_ARB_vertex_program,\nGL_ARB_fragment_program, WGL_ARB_pbuffer.\n");
		for(;;) {};
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
		}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // this line indicates the face you cull is the back one

	unRender = new unRenderer;

	unRender->set_program_params(depthbias,depthtex);
	unRender->mrt_create(resolutions[res][0],resolutions[res][1]);
	unRender->load_programs();

	g_render->camera.rotate(-90,pVector(1,0,0));
	g_render->camera.pos.vec(0,0,50);

	mesh=g_render->load_mesh(meshfile);

	if (mesh)
		{
		g_render->target_pos=mesh->bbox.get_center();
		if (mesh->ncam)
			{
			srand(timeGetTime());
			//camera=rand()%mesh->ncam;
			g_render->camera=mesh->cam[0];
			}
		}
	else
		{
		printf("ERROR:::unRenderer failed to load scene mesh\n");
		for(;;) {};
		}

	update_menu();

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
}

// free demo
void appClose()
{
	delete unRender;
	unRender=0;

	g_render->reset();
}

// animate light and camera
void animate()
{
	// accumulate time
	time+=g_render->curdtf;

	// animate lights
	int i,j=mesh->nlight;
	//for( i=0;i<j;i++ )
	//	mesh->light[i].animate(time);

	mesh->light[0].pos.x = playerAV.Xform.Translation.x;
	mesh->light[0].pos.y = playerAV.Xform.Translation.y + 35;
	mesh->light[0].pos.z = playerAV.Xform.Translation.z;
	mesh->light[0].pos.w = 1;
	//mesh->light[0].anim_color.color.x = 0;
	
	// animate camera
	g_render->camera.animate(time);
	g_render->set_camera();
}

// draws main scene (single quad polygon)
void draw_scene()
{
	playerAV.Avatar.Mesh->onIdleAnim();
	unRender->draw_geometry(mesh,mode>0);

#if 0
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_ONE,GL_ZERO);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glColor4f(1,1,1,1);
	glClearColor(g_render->bgcolor.x,g_render->bgcolor.y,g_render->bgcolor.z,1);
	glClearDepth(1);
	glDisable(GL_TEXTURE_2D);

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
#endif

	//unRender->draw_meshes(true);
}

// draw 2d text with demo informations
void draw_info()
{
	// screen size
	int sx=g_render->sizex;
	int sy=g_render->sizey;

	// compute lighting
	unRender->draw_lights(mesh,scissor);

	// draw antialias (blur edges)
	if (antialias) unRender->draw_antialias();

	// compute bloom
	if (bloom) unRender->draw_bloom();

	// draw final image to screen
	unRender->draw_final(sx,sy);

	// draw debug mrt textures
	if (debug) unRender->draw_debug(sx,sy);

	if (info)
		{
		// draw fps
		glColor4f(1,1,0,1);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		pString str;
		switch(mode)
			{
			case 0: str="Normal Mapping"; break;
			case 1: str="Relief Mapping"; break;
			}

		g_render->draw_text(0,0,str,16);
		str.format("FPS: %i",g_render->curfps);
		g_render->draw_text(0,16,str,16);
		str.format("Lights: %i/%i",unRender->m_num_lights_drawn,mesh->nlight);
		g_render->draw_text(0,32,str,16);
		str.format("Scissor: %i%%",unRender->m_percent_pixel_drawn);
		g_render->draw_text(0,48,str,16);

		str.format("CamPos[0]: %f", g_render->camera.pos[0]);
		g_render->draw_text(0,66,str,16);

		str.format("CamPos[1]: %f", g_render->camera.pos[1]);
		g_render->draw_text(0,84,str,16);

		str.format("CamPos[2]: %f", g_render->camera.pos[2]);
		g_render->draw_text(0,102,str,16);
		}

	update_menu();
}

// key processing
void key_pressed(int key,int flags)
{
	if (mesh && mesh->ncam>0)
	if (key>='1' && key<='9')
		{
		camera=key-'1';
		if (camera>=mesh->ncam) return;
		g_render->camera=mesh->cam[camera];
		update_menu();
		time=0;
		}

	if (key=='o')
		{
		Qpo->Transform_New_YRotation(&AIfriendly, -0.1);	/// Originaly -
		Qpo->Transform_Multiply(&playerAV.Xform, &AIfriendly, &playerAV.Xform);
		printf("Qpo->Transform_RotateY(&playerAV.Xform, -0.1);\n");
		}

	if (key=='p')
		{
		Qpo->Transform_New_YRotation(&AIfriendly, 0.1);	/// Originaly -
		Qpo->Transform_Multiply(&playerAV.Xform, &AIfriendly, &playerAV.Xform);
		printf("Qpo->Transform_RotateY(&playerAV.Xform, 0.1);\n");
		}
}

// update menu state
void update_menu()
{
	HMENU menu=GetMenu(hWndMain);
	CheckMenuItem(menu,ID_VIEW_DEPTHBIAS,depthbias?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_BLOOM,bloom?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_SCISSOR,scissor?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_NVRENDERDEPTHTEX,depthtex?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_DEBUG,debug?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_INFORMATION,info?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_ANTIALIAS,antialias?MF_CHECKED:MF_UNCHECKED);
	CheckMenuRadioItem(menu,ID_VIEW_FREECAMERA,ID_VIEW_FREECAMERA+2,ID_VIEW_FREECAMERA+camera,0);
	CheckMenuRadioItem(menu,ID_VIEW_NORMAL,ID_VIEW_NORMAL+2,ID_VIEW_NORMAL+mode,0);
	CheckMenuRadioItem(menu,ID_RENDER_256X256,ID_RENDER_256X256+3,ID_RENDER_256X256+res,0);
}

// open a file dialog window
int OpenFileDialog(const char *title,const char *filter,const char *ext,const char *initdir,char *filename,int len)
{
	OPENFILENAME ofn;
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
		return 1;
	return 0;
}

// process window commands
void command(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( LOWORD(wParam) )
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
					mesh=g_render->load_mesh(meshfile);
					if (mesh) g_render->target_pos=mesh->bbox.get_center();
					else meshfile="";
					}
				}
			}
			break;
		case ID_VIEW_FREECAMERA:
		case ID_VIEW_ANIMCAMERA:
		case ID_VIEW_ANIMCAMERA2:
			key_pressed('1'+((LOWORD(wParam)-ID_VIEW_FREECAMERA)),0);
			break;

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
			info=!info;
			update_menu();
			break;

		case ID_EXIT:
			appClose();
			DestroyWindow(hWndMain);
			break;

		case ID_VIEW_FULLSCREEN:
			g_render->set_fullscreen(!g_render->fullscreen);
			break;

		case ID_ABOUT:
			{
			MessageBox(
				hWndMain,
				"Unification OpenGL Renderer www.stsshome.com\n",
				appname,
				MB_ICONINFORMATION|MB_OK);
			break;
			}
		}
}