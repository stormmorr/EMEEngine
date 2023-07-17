#include "p3d\paralelo3d.h"
#include "resource.h"

extern HWND hWndMain;
extern HINSTANCE hInstance;

char *appname="Curved Relief Mapping";

void draw_scene();
void key_pressed(int key,int flags);
void animate();
void init();
void destroy();
void command(UINT msg,WPARAM wParam,LPARAM lParam);
void update_menu();
void load_scene();

pString rmfile("data\\stone.tga");
pString colorfile("data\\stone.jpg");
pString meshfile("data\\cylinder.p3d");

pRM rm;			// relief object
pMesh *mesh=0;	// geometry object

int prog_mode=2;		// 0:normal, 1:parallax, 2:relief
int color_tex=-1;		// color tex id
int color_tex_null=-1;	// null (white) color tex id
int relief_tex=-1;		// relief tex id

bool draw_wire=0;	// draw wireframe on/off flag
bool anim_light=0;	// animate light on/off flag
bool anim_model=1;	// animate model on/off flag
bool shadows=0;		// shadows on/off flag
bool doubledepth=0;	// double depth on/off flag
bool doubleprec=0;	// double search precision (10 or 20 steps)
bool depthcorrect=0;// depth correct (z write in shader)

// tile factor:
//   0    for one tile with texclamp
//   1..n for tile without text clamp)
unsigned tile=1;
// depth factor
float depth=1.0f;
// model rotation
float rot=0.0f;
float rotspeed=20.0f;

// light position
pVector lightpos(100,-150,200,1000);
pLight light;

// material colors
pVector amb(0.25f,0.25f,0.25f);
pVector diff(1,1,1,1);
pVector spec(0.75f,0.75f,0.75f,64);

// initialize demo
void init()
{	
	g_render->camera.pos.vec(0,-40,15);
	g_render->camera.rotate(-90,pVector(1,0,0));

	light.pos=lightpos;

	rm.load(prog_mode,shadows,doubleprec,depthcorrect,false,false,false);

	relief_tex=g_render->load_tex(rmfile,0,1);
	color_tex=g_render->load_tex(colorfile,0,1);
	color_tex_null=g_render->build_onepixelmap(255,255,255);
	mesh=g_render->load_mesh(meshfile);
	if (mesh)
		g_render->target_pos=mesh->bbox.get_center();

#ifndef P_SUPPORT_CG13
	HMENU menu=GetMenu(hWndMain);
	EnableMenuItem(menu,ID_VIEW_RM_FP40,MF_GRAYED);
#endif

	update_menu();
}

// free demo
void destroy()
{
	g_render->reset();
}

// draws main scene (single quad polygon)
void draw_scene()
{
	glPushMatrix();
	glRotatef(rot,0,0,1);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// draw relief object
	rm.draw(mesh,color_tex,relief_tex,-1,tile,depth,amb,diff,spec,&light);

	//draw(m_mesh,texturecolor,texturerelief,-1,m_tile,m_depth,g_render->lightambient,diff,spec,&l);
	
	if (depthcorrect)
	{
		float size=mesh->bbox.get_diagonal().length()*0.5;
		float scale=(size-depth)/size;

		glColor3f(0,0,1);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glScalef(scale,scale,scale);
		mesh->array_lock(0,0);
		mesh->array_draw(0);
		mesh->array_unlock();
		glPopMatrix();
	}

	if (draw_wire)
	{
		glDepthMask(0);
		glColor3f(1,0,0);
		glPolygonMode(GL_FRONT,GL_LINE);
		glPolygonOffset(-1,-1);
		glEnable(GL_POLYGON_OFFSET_LINE);
		mesh->array_lock(0,0);
		mesh->array_draw(0);
		mesh->array_unlock();
		glDisable(GL_POLYGON_OFFSET_LINE);
		glPolygonMode(GL_FRONT,GL_FILL);
		glDepthMask(1);
	}

	glPopMatrix();
}

// draw 2d text with demo informations
void draw_info()
{
	pString str;
	
	switch(prog_mode)
	{
		case 0:
			str="NORMAL MAP (ARBFP1)";
			break;
		case 1:
			str="PARALLAX MAP (ARBFP1)";
			break;
		case 2:
			str="RELIEF MAP (ARBFP1)";
			break;
	}
	g_render->draw_text(0,0,str,16);

	g_render->draw_text(0,16,prog_mode&&doubleprec?"DOUBLE PREC":"SINGLE PREC",16);
	g_render->draw_text(0,32,prog_mode&&depthcorrect?"DEPTH CORRECT":"NO DEPTH CORRECT",16);
	g_render->draw_text(0,48,prog_mode&&shadows?"SHADOWS":"NO SHADOWS",16);

	str.format("FPS: %i",g_render->curfps);
	g_render->draw_text(0,64,str,16);
}

// animate light position moving it around object
void animate()
{
	if (anim_light)
	{
		static int light_time=0;
		light_time+=g_render->curdt;
		float t=TWOPI*(light_time%6000)/6000.0f;
		float d=lightpos.length();
		light.pos.x=d*cosf(t);
		light.pos.z=d*sinf(t);
	}
	else
		light.pos=lightpos;

	if (anim_model)
	{
		rot+=rotspeed*g_render->curdtf;
		while( rot>360.0f )
			rot-=360.0f;
	}
}

// key processing
void key_pressed(int key,int flags)
{
	if (key=='-' || key=='_')
	{
		if (tile>1) 
			tile--;
		update_menu();
	}
	else
	if (key=='+' || key=='=')
	{
		if (tile<8) 
			tile++;
		update_menu();
	}
	else
	if (key=='[' || key=='{')
	{
		if (depth>0.6f) 
			depth-=0.5f;
		update_menu();
	}
	else
	if (key==']' || key=='}')
	{
		if (depth<4.9f) 
			depth+=0.25f;
		update_menu();
	}
}

// update menu state
void update_menu()
{
	printf("menu\n");
	HMENU menu=GetMenu(hWndMain);
	CheckMenuRadioItem(menu,ID_VIEW_BUMPMAPPING,ID_VIEW_BUMPMAPPING+2,ID_VIEW_BUMPMAPPING+prog_mode,MF_BYCOMMAND);
	CheckMenuItem(menu,ID_VIEW_DOUBLEPRECISION,doubleprec?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_DEPTHCORRECT,depthcorrect?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_SHADOWS,shadows?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_WIREFRAME,draw_wire?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_ANIMATELIGHT,anim_light?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_ANIMATEMODEL,anim_model?MF_CHECKED:MF_UNCHECKED);
	CheckMenuRadioItem(menu,ID_VIEW_CAMERAORBIT,ID_VIEW_CAMERAOBSERVER,ID_VIEW_CAMERAORBIT+g_render->selcamctrl,MF_BYCOMMAND);
	CheckMenuRadioItem(menu,ID_VIEW_TILEFACTOR_1,ID_VIEW_TILEFACTOR_8,ID_VIEW_TILEFACTOR_0+tile,MF_BYCOMMAND);
	int depthsel=int(depth/0.5f+0.5f)-1;
	CheckMenuRadioItem(menu,ID_RENDER_DEPTHFACTOR_05,ID_RENDER_DEPTHFACTOR_50,ID_RENDER_DEPTHFACTOR_05+depthsel,MF_BYCOMMAND);
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

		case ID_FILE_OPENTEXTUREMAP:
			{
			char filename[512]="";
			if (OpenFileDialog("Open RM","Relief map files (*.tga)\0*.tga\0\0","*.tga",g_render->app_path+"data\\",filename,255))
				{
					pString str;
					str=filename;
					if (check_path(g_render->app_path,filename,str))
					{
						rmfile=str;
						relief_tex=g_render->load_tex(rmfile,0,1);
						
						colorfile=rmfile;
						int p=colorfile.find_reverse('.');
						if (p!=-1)
						{
							colorfile.set_char(p,0);
							colorfile+=".jpg";
							color_tex=g_render->load_tex(colorfile,0,1);
							if (color_tex==-1)
							{
								color_tex=color_tex_null;
								colorfile="";
							}
						}
					}
				}
			}
			break;

		case ID_FILE_LOADCOLORMAP:
			{
			char filename[512]="";
			if (OpenFileDialog("Open Color Map","All image files (*.tga;*.jpg)\0*.tga;*.jpg\0Targa image files (*.tga)\0*.tga\0Jpeg image files (*.jpg)\0*.jpg\0\0","*.tga;*.jpg",g_render->app_path+"data\\",filename,255))
				{
					pString str;
					str=filename;
					if (check_path(g_render->app_path,filename,str))
					{
						colorfile=str;
						color_tex=g_render->load_tex(colorfile,0,1);
						if (color_tex==-1)
						{
							color_tex=color_tex_null;
							colorfile="";
						}
					}
				}
			else
				color_tex=color_tex_null;
			}
			break;

		case ID_FILE_LOADMESH:
			{
			char filename[512]="";
			if (OpenFileDialog("Open P3D","P3D mesh fils (*.p3d)\0*.p3d\0\0","*.p3d",g_render->app_path+"data\\",filename,255))
				{
					pString str;
					str=filename;
					if (check_path(g_render->app_path,filename,str))
					{
						meshfile=str;
						mesh=g_render->load_mesh(meshfile);
						if (mesh)
							g_render->target_pos=mesh->bbox.get_center();
						else
							meshfile="";
					}
				}
			}
			break;

		case ID_VIEW_BUMPMAPPING:
			if (prog_mode!=0)
			{
				prog_mode=0;
				rm.load(prog_mode,shadows,doubleprec,depthcorrect,false,false,false);
				prog_mode=rm.get_progmode();
				update_menu();
			}
			break;

		case ID_VIEW_PARALLAXMAPPING:
			if (prog_mode!=1)
			{
				prog_mode=1;
				rm.load(prog_mode,shadows,doubleprec,depthcorrect,false,false,false);
				prog_mode=rm.get_progmode();
				update_menu();
			}
			break;

		case ID_VIEW_RM:
			if (prog_mode!=2)
			{
				prog_mode=2;
				rm.load(prog_mode,shadows,doubleprec,depthcorrect,false,false,false);
				prog_mode=rm.get_progmode();
				update_menu();
			}
			break;

		case ID_VIEW_DOUBLEPRECISION:
			doubleprec=!doubleprec;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,false,false,false);
			update_menu();
			break;

		case ID_VIEW_SHADOWS:
			shadows=!shadows;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,false,false,false);
			update_menu();
			break;

		case ID_VIEW_DEPTHCORRECT:
			depthcorrect=!depthcorrect;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,false,false,false);
			update_menu();
			break;

		case ID_VIEW_WIREFRAME:
			draw_wire=!draw_wire;
			update_menu();
			break;

		case ID_VIEW_CAMERAORBIT:
			g_render->selcamctrl=1;
			update_menu();
			break;
		
		case ID_VIEW_CAMERAOBSERVER:
			g_render->selcamctrl=0;
			update_menu();
			break;

		case ID_VIEW_ANIMATELIGHT:
			anim_light=!anim_light;
			update_menu();
			break;

		case ID_VIEW_ANIMATEMODEL:
			anim_model=!anim_model;
			update_menu();
			break;

		case ID_VIEW_TILEFACTOR_1:
		case ID_VIEW_TILEFACTOR_2:
		case ID_VIEW_TILEFACTOR_3:
		case ID_VIEW_TILEFACTOR_4:
			tile=LOWORD(wParam)-ID_VIEW_TILEFACTOR_0;
			update_menu();
			break;

		case ID_RENDER_DEPTHFACTOR_05:
		case ID_RENDER_DEPTHFACTOR_10:
		case ID_RENDER_DEPTHFACTOR_15:
		case ID_RENDER_DEPTHFACTOR_20:
		case ID_RENDER_DEPTHFACTOR_25:
		case ID_RENDER_DEPTHFACTOR_30:
		case ID_RENDER_DEPTHFACTOR_35:
		case ID_RENDER_DEPTHFACTOR_40:
		case ID_RENDER_DEPTHFACTOR_45:
		case ID_RENDER_DEPTHFACTOR_50:
			depth=0.5*(LOWORD(wParam)-ID_RENDER_DEPTHFACTOR_05+1);
			update_menu();
			break;

		case ID_EXIT:
			destroy();
			DestroyWindow(hWndMain);
			break;

		case ID_VIEW_FULLSCREEN:
			g_render->set_fullscreen(!g_render->fullscreen);
			break;

		case ID_ABOUT:
			MessageBox(
				hWndMain,
				"Curved Relief Mapping\n\nFabio Policarpo\nhttp://fabio.policarpo.nom.br/",
				"About",
				MB_ICONINFORMATION|MB_OK);
			break;
	}
}
