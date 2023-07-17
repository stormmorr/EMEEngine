#include "..\..\p3d\include\p3d\paralelo3d.h"
#include "resource.h"

extern HWND hWndMain;
extern HINSTANCE hInstance;

char *appname="Relief Mapping";

void draw_scene();
void key_pressed(int key,int flags);
void animate();
void init();
void destroy();
void command(UINT msg,WPARAM wParam,LPARAM lParam);
void update_menu();
void load_scene();

pString colorfile("data//tile1.jpg");
pString relieffile("data//tile1.tga");
pString meshfile("data//cube.P3D");

pRM rm;			// relief object
pMesh *mesh=0;	// geometry object

int prog_mode=2;		// 0:normal, 1:parallax, 2:relief, 3:relief_nv
int color_tex=-1;		// color tex id
int relief_tex=-1;		// relief tex id

int color_tex_null=-1;	// null (white) color tex id
int draw_status=2;

bool draw_wire=0;	// draw wireframe on/off flag
bool anim_light=0;	// animate light on/off flag
bool anim_model=1;	// animate model on/off flag
bool shadows=0;		// shadows on/off flag
bool doubleprec=0;	// double search precision (10 or 20 steps)
bool depthcorrect=0;// depth correct (z write in shader)
bool depthbias=1;	// depth bias
bool borderclamp=1;	// border clamp
bool viewdepth=0;	// view depth values
bool viewnormal=0;	// view depth values

// tile factor:
//   0    for one tile with texclamp
//   1..n for tile without text clamp)
unsigned tile=1;
// depth factor
float depth=4.0f;
// model rotation
float rot=0.0f;
float rotspeed=20.0f;

// light position
pVector lightpos(100,-150,200,1000);
pLight light;

// material colors
pVector amb(0.35f,0.35f,0.35f);
pVector diff(1,1,1,1);
pVector spec(0.75f,0.75f,0.75f,64);

// initialize demo
void init()
{	
	g_render->camera.pos.vec(0,-100,0);
	g_render->camera.rotate(-90,pVector(1,0,0));

	light.pos=lightpos;
	rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);

	color_tex=g_render->load_tex(colorfile,0,1);
	relief_tex=g_render->load_tex(relieffile,0,1);
	color_tex_null=g_render->build_onepixelmap(255,255,255);
	mesh=g_render->load_mesh("data//cube.P3D");
	if (mesh)
		g_render->target_pos=mesh->bbox.get_center();
	//else exit(-1);

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
	rm.draw(mesh,color_tex,relief_tex,relief_tex,tile,depth,amb,diff,spec,&light);

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
	if (draw_status==0)
		return;

	glColor4f(1,1,0,1);

	pString str;
	int y=0;
	
	switch(prog_mode)
	{
		case 0:
			str="Normal Mapping";
			break;
		case 1:
			str="Parallax Mapping";
			break;
		case 2:
			str="Relief Mapping";
			break;
	}
	g_render->draw_text(0,y,str,16);
	y+=16;

	if (doubleprec)
	{
		g_render->draw_text(0,y,"Double Precision",16);
		y+=16;
	}
	
	if (borderclamp)
	{
		g_render->draw_text(0,y,"Border Clamp",16);
		y+=16;
	}

	if (depthbias)
	{
		g_render->draw_text(0,y,"Depth Bias",16);
		y+=16;
	}

	if (depthcorrect)
	{
		g_render->draw_text(0,y,"Depth Correct",16);
		y+=16;
	}

	if (shadows)
	{
		g_render->draw_text(0,y,"Self-Shadows",16);
		y+=16;
	}

	if (viewdepth)
	{
		g_render->draw_text(0,y,"View Depth",16);
		y+=16;
	}
	else
	if (viewnormal)
	{
		g_render->draw_text(0,y,"View Normal",16);
		y+=16;
	}

	if (draw_status==1)
		return;

	str.format("FPS: %i",g_render->curfps);
	g_render->draw_text(0,g_render->sizey-16,str,16);
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
	if (key==9)
		draw_status=(draw_status+1)%3;
	else
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
		if (depth>1.1f) 
			depth-=1.0f;
		update_menu();
	}
	else
	if (key==']' || key=='}')
	{
		if (depth<7.9f) 
			depth+=1.0f;
		update_menu();
	}
}

// update menu state
void update_menu()
{
	HMENU menu=GetMenu(hWndMain);
	CheckMenuRadioItem(menu,ID_VIEW_BUMPMAPPING,ID_VIEW_BUMPMAPPING+3,ID_VIEW_BUMPMAPPING+prog_mode,MF_BYCOMMAND);
	CheckMenuItem(menu,ID_VIEW_DOUBLEPRECISION,doubleprec?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_DEPTHCORRECT,depthcorrect?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_DEPTHBIAS,depthbias?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_BORDERCLAMP,borderclamp?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_SHADOWS,shadows?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_WIREFRAME,draw_wire?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_ANIMATELIGHT,anim_light?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_MODELANIMATION,anim_model?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_DEPTH,viewdepth?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_NORMAL,viewnormal?MF_CHECKED:MF_UNCHECKED);
	CheckMenuRadioItem(menu,ID_VIEW_CAMERAORBIT,ID_VIEW_CAMERAOBSERVER,ID_VIEW_CAMERAORBIT+g_render->selcamctrl,MF_BYCOMMAND);
	CheckMenuRadioItem(menu,ID_VIEW_TILEFACTOR_1,ID_VIEW_TILEFACTOR_8,ID_VIEW_TILEFACTOR_0+tile,MF_BYCOMMAND);
	int depthsel=int(depth/1.0f);
	CheckMenuRadioItem(menu,ID_RENDER_DEPTHFACTOR_000,ID_RENDER_DEPTHFACTOR_200,ID_RENDER_DEPTHFACTOR_000+depthsel,MF_BYCOMMAND);
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
						relieffile=str;
						relief_tex=g_render->load_tex(relieffile,0,1);
						
						colorfile=relieffile;
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
				rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
				prog_mode=rm.get_progmode();
				update_menu();
			}
			break;

		case ID_VIEW_PARALLAXMAPPING:
			if (prog_mode!=1)
			{
				prog_mode=1;
				rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
				prog_mode=rm.get_progmode();
				update_menu();
			}
			break;

		case ID_VIEW_RM:
			if (prog_mode!=2)
			{
				prog_mode=2;
				rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
				prog_mode=rm.get_progmode();
				update_menu();
			}
			break;

		case ID_VIEW_RM_NV:
			if (prog_mode!=3)
			{
				prog_mode=3;
				rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
				prog_mode=rm.get_progmode();
				update_menu();
			}
			break;

		case ID_VIEW_DOUBLEPRECISION:
			doubleprec=!doubleprec;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
			update_menu();
			break;

		case ID_VIEW_SHADOWS:
			shadows=!shadows;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
			update_menu();
			break;

		case ID_VIEW_DEPTHCORRECT:
			depthcorrect=!depthcorrect;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
			update_menu();
			break;
		
		case ID_VIEW_DEPTHBIAS:
			depthbias=!depthbias;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
			update_menu();
			break;

		case ID_VIEW_BORDERCLAMP:
			borderclamp=!borderclamp;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
			update_menu();
			break;

		case ID_VIEW_DEPTH:
			viewnormal=0;
			viewdepth=!viewdepth;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
			update_menu();
			break;

		case ID_VIEW_NORMAL:
			viewdepth=0;
			viewnormal=!viewnormal;
			rm.load(prog_mode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,false);
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

		case ID_VIEW_MODELANIMATION:
			anim_model=!anim_model;
			update_menu();
			break;

		case ID_VIEW_TILEFACTOR_1:
		case ID_VIEW_TILEFACTOR_2:
		case ID_VIEW_TILEFACTOR_3:
		case ID_VIEW_TILEFACTOR_4:
		case ID_VIEW_TILEFACTOR_5:
		case ID_VIEW_TILEFACTOR_6:
		case ID_VIEW_TILEFACTOR_7:
		case ID_VIEW_TILEFACTOR_8:
			tile=LOWORD(wParam)-ID_VIEW_TILEFACTOR_0;
			update_menu();
			break;

		case ID_RENDER_DEPTHFACTOR_000:
		case ID_RENDER_DEPTHFACTOR_025:
		case ID_RENDER_DEPTHFACTOR_050:
		case ID_RENDER_DEPTHFACTOR_075:
		case ID_RENDER_DEPTHFACTOR_100:
		case ID_RENDER_DEPTHFACTOR_125:
		case ID_RENDER_DEPTHFACTOR_150:
		case ID_RENDER_DEPTHFACTOR_175:
		case ID_RENDER_DEPTHFACTOR_200:
			depth=1.0f*(LOWORD(wParam)-ID_RENDER_DEPTHFACTOR_000);
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
				"Relief Mapping\n\nFabio Policarpo\nhttp://fabio.policarpo.nom.br/",
				"About",
				MB_ICONINFORMATION|MB_OK);
			break;
	}
}