/*! \file */

#ifndef PRENDER_H
#define PRENDER_H

P3D_API const char *get_file_name(const char *fullfile);
P3D_API const char *get_path_name(const char *fullfile);

P3D_API bool check_path(const pString& app_path,const pString& file1,pString& file2);

//! Global access to render
P3D_API extern pRender *g_render;

//! Global access to render
P3D_API pRender *get_render();

P3D_API void render_init(const char *app_path,const char *inifilename,HWND hwnd=0,int fullscreen=0,int norender=-1);
P3D_API void render_free();	

typedef struct
{
	int pic;
	int size;
	int charsize;
	int width[256];
} pFontInfo;

class P3D_API pRender
{
	public:
		HWND hwnd;
		HDC hdc;
		HGLRC hrc;

#if 0 // P_SUPPORT_CG
		CGcontext cgcontext;
#endif
		pArray<DEVMODE> videomode;
		int selvideomode;
		int fullscreen;
		HMENU winmenu;

		int norender;
		int debug;
		int sizex,sizey;
		float aspect;
		float nearplane;
		float farplane;
		double hugeplane;
		bool hugeplaneflag;
		float alphatestval;
		int colorbits,depthbits,stencilbits, accumbits;
		bool info;
		bool framememory;
		bool infoedit;

		pArray<pRenderProfile *> profile;
		pRenderProfile *cur_profile;
		int sel_profile;

		pArray<pFontInfo *> font;
		pFontInfo *cur_font;
		int cursorx,cursory;

#ifndef P_DISABLE_3D
#if 0 // QAGE_DESKTOP
		pRenderGlow rg;
		pRenderRipple rr;
		pRenderShadowMap rs;
#endif
		int rg_enabled, rr_enabled, mb_enabled, ac_enabled;
		float ac_factor;
		int env_map_mode; // P_ENVMODE_NONE, P_ENVMODE_CUBE_MAPPING, P_ENVMODE_SPHERE_MAPPING
		unsigned int cube_map_tex,sph_map_tex;
		pString cube_map_tex_name,sph_map_tex_name;
#endif
		int shadowflag;
		int svtype;

		pVector lightambient;
		int texfilter;
		int texmipmap;
		int texload;
		int texresize;
		int vertbuffer;
		int rendermode;
		int renderflag;
		int drawfps;
		int texdetail;
		int loddetail;
		int fog;
		
		int bgclear;
		pVector bgcolor;

		int maxtex2dsize;
		int maxtex3dsize;
		int maxlights;
		int maxoctreedepth;
		int maxtextureunits;

		int curdraw;
		int curfps;
		
		pArray<unsigned int> picid;
		pArray<pPicture *> pic;
		
		pArray<pMesh *> model;
		pArray<pLight *> light;

		float camerafov;
		pCamera camera;
		pFrustum view;
		//FrustumG viewdif;
		pMatrix view_matrix;
		pMatrix proj_matrix;

		pString camkeys;
		pCameraCtrl *camctrl[2];
		int selcamctrl;
		pVector target_pos;
		int target_moving;

		int cam_viewport[4];
		double cam_proj_mat[16];
		double cam_model_mat[16];
		
		pVector hitnormal,hitip;
		float hitdist;

		float curtimef,curdtf;
		unsigned int starttime,curtime,curdt;
		pString app_path;
		pString renderini_path_store;
		pString shader_path;

		// each blink data comprises 2 vectors in the array, as follows:
		// blink color, stored in v1.xyzw
		// blink time, stored in v2.x
		// blink start time, stored in v2.y
		// blink additive blend flag, stored in v2.z
		// blink mode flag, stored in v2.w
		pArray<pVector> blink_data;
		pArray<pVector> blink_data_out;
		// constant blink color was added for constant blinking (like obfuscating effects)
		pVector const_blink_color;

		int logflag;			//!< bitfield for log options (see paralelo3d.h)
		pLogReport logreport;	//!< object for control log

		float tooltip_delay;
		pVector tooltip_bgcolor;
		pVector tooltip_textcolor;
		int tooltip_tex;
		int tooltip_font;
		int tooltip_fontsize;
		int tooltip_border;

	pRender(const char *path="",const char *inifilename="");
	~pRender();

	void pre_create(HWND hWnd);
	int create(int menuflag=1);
	void resize(int sx,int sy);
	void destroy();
	
	void load_ini(const char* inifilename);
	pMesh *load_mesh(const char *modelfile, float f_UVFactor);
	pMeshSkeleton *load_mesh_skeleton(const char *modelfile);
	void clean_resources();
	void reset();

	void save_ini();

	void init();
	void clear();
	void begin_draw();
	void draw3d();
	void set_draw2d();
	void draw2d();
	void end_draw();
	void draw(pArray<pRenderObject *>& objects);

	void shadows_stencil_init();
	void shadows_stencil_test();
	void shadows_stencil_release();
	void draw_shadows(pLight *l,pRenderObject *obj);

	int load_tex(const char *texfile,int flags,int load);
	void tex_add_reference(int tex);
	void tex_remove_reference(int tex);
	void build_mipmaps(pPicture *p,unsigned int type2);
	void set_tex_params(pPicture *p,unsigned int type1,unsigned int type2);
	void sel_tex(int tex);
	void update_texflags();
	void reset_tex_state();
	int create_texture(int sx,int sy,int bytespixel,unsigned int color);
	bool load_cubemap_tex(const char *texfile);
	bool load_spheremap_tex(const char *texfile);
	void set_fullscreen(int fsflag,int menuflag=1);
	void set_camera(bool envmapmode=false);
	void set_camera_mesh(bool envmapmode=false);
	int key_pressed(int key);
	void update();
	void check_input();
	void update_camera();

	void get_ray(float x,float y,pVector& ray);
	
	int load_font(const char *fontfile);
	int sel_font(int fontid);
	void draw_text(int x,int y,const char *text,int size,int n=-1);
	void draw_text_center(int x,int y,const char *text,int size);
	int get_text_size(const char *text, int size);
	int build_onepixelmap(unsigned char r,unsigned char g,unsigned char b);

	void profile_build();
	void profile_select(int p);
	int profile_get_count() const;
	const char *profile_get_name(int p) const;

	int get_global_param_desc(int i,pParamDesc *pd);
	bool set_global_param(const char *param,const char *value);
	bool get_global_param(const char *param,pString& value);
	void on_pre_parameter_change(int i);
	void on_pos_parameter_change(int i);

	void blink(const int time,const pVector& color,const int add_blend);
	void blink_in(const int time,const pVector& color,const int add_blend);
	void blink_out(const int time,const pVector& color,const int add_blend);
	void const_blink(const pVector& color);
	void draw_blink();

	void do_frame(bool process_camera);
	void set_shader_path(const char *path);
	void set_app_path(const char *path);
};

#endif
