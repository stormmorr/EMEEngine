/*

	unRenderer.h - osirem.com
	Copyright OSIREM LTD (C) 2016
	www.osirem.com www.qage.org www.geopomp.com

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __UNRENDERER__
#define __UNRENDERER__

#if 0
#include "../../../DigitalMass/Source/Digi/DigiMass.h"
#include "../../../DigitalMass/Source/Geometry/unTerrainCell.h"
#include "../../../DigitalMass/Source/Geometry/unTrrCellSettings.h"
#endif

#include "../../QActiveFramewrk.h"
#include "../../Avatar/unMesh.h"
#include "../../Avatar/unPointLocator.h"

#if 0
#include "../../Process/unMessageCore.h"
#endif

#include "../../Texture/textureDef.h"
#include "../../Avatar/unShape.h"

#ifdef OSIRUS_CORE
#include "../../Osirus/OsirusCore.h"
#endif

 /////////////////////////////////
////// UNRENDERER SETTINGS //////

#define UNREND_BLOOM_SCALE 10
#define UNREND_FRAMEMEMSIZE 8
#define AOGI_AROUND 4

#if 1
#define UNRENDER_FRAMEMEMORY 1
#endif

extern float g_LightPos[40];
extern float g_LightColor[40];
extern float g_LightNom;

extern float g_LightonX;
extern float g_LightonY;
extern float g_LightonZ;

extern int g_LightonXDir;
extern int g_LightonZDir;

extern float g_LightonR;
extern float g_LightonG;
extern float g_LightonB;

class unRenderer
{
protected:
	// vertex program and parameters
	//*CGprogram m_vert_prog;
	//*CGparameter m_vtile;
	//*CGparameter m_vdepth;

	// vertex program for view_mesh
	//*CGprogram m_vert_mesh;
	//*CGprofile vertexProfile;
	//*CGparameter m_meshtile;
	//*CGparameter m_meshdepth;
	//*CGparameter m_meshrotationMatrices;
	//*CGparameter m_meshcolormap;

	// vertex program for view_terrain
	//*CGprogram m_vert_terrain;
	//*CGprofile vertterrainProfile;
	//*CGparameter m_terraintile;
	//*CGparameter m_terraindepth;
	//*CGparameter m_terrainsampler;
	//*CGparameter m_terrainwidth;
	//*CGparameter m_terraincolormap;
	//*CGparameter m_alphadepthmap;
	//*CGparameter m_alphacolormap;

	// fragment program for normal_mesh
	//*CGprogram m_frag_mesh;
	//*CGprogram m_frag_shadow;
	//*CGparameter m_meshAmbient;
	//*CGparameter m_meshDiffuse;
	//*CGparameter m_meshSpecular;
	//*CGparameter m_meshAlpha;
	//*CGparameter m_meshLightVec;
	//*CGparameter m_meshEyeVec;
	//*CGparameter m_shadowAmbient;
	//*CGparameter m_shadowDiffuse;
	//*CGparameter m_shadowSpecular;
	//*CGparameter m_shadowAlpha;
	//*CGparameter m_shadowLightVec;
	//*CGparameter m_shadowEyeVec;
	//*CGparameter m_shadowcolormap;

	// fragment program for normal_terrain
	//*CGprogram m_frag_terrain;
	//*CGparameter m_terrainAmbient;
	//*CGparameter m_terrainDiffuse;
	//*CGparameter m_terrainSpecular;
	//*CGparameter m_terrainAlpha;
	//*CGparameter m_terrainLightVec;
	//*CGparameter m_terrainEyeVec;

	//*CGprogram m_frag_alpha;
	//*CGparameter m_alphaAmbient;
	//*CGparameter m_alphaDiffuse;
	//*CGparameter m_alphaSpecular;
	//*CGparameter m_alphaAlpha;
	//*CGparameter m_alphaLightVec;
	//*CGparameter m_alphaEyeVec;
	//*CGparameter m_alphaPlanes;
	//*CGparameter m_alphaView;

	// normal mapping fragment program and parameters
	//*CGprogram m_frag_prog_normal;	
	//*CGparameter m_ndiffuse;
	//*CGparameter m_nspecular;
	//*CGparameter m_nplanes;

	// relief mapping fragment program and parameters
	//*CGprogram m_frag_prog_relief;
	//*CGparameter m_rdiffuse;
	//*CGparameter m_rspecular;
	//*CGparameter m_rplanes;
	//*CGparameter m_stepmap;
	//*CGparameter m_rtdepth;

	// lighting fragment program and parameters
	//*CGprogram m_frag_prog_light;
	//*CGparameter m_lplanes;
	//*CGparameter m_lpos;
	//*CGparameter m_lcolor;

	// blur fragment program and parameters
	//*CGprogram m_frag_prog_blur;
	//*CGparameter m_bdisp;

	// anti-alias fragment program and parameters
	//*CGprogram m_frag_prog_antialias;
	//*CGparameter m_apixelsize;
	//*CGparameter m_aweight;

	void replication(void) {};

	// render options
	bool m_nv_render_depth_texture; // use depth buffer
	bool m_depth_bias;	// use perspective depth bias

	//pPBuffer *m_mrt;		// multiple render targets
	unsigned m_mrttex[4];	// mrt texture ids

	//pPBuffer *m_fb[4];		// frame buffers used for bloom
	unsigned m_fbtex[4];	// bloom textures for each frame buffer

	unsigned gl_buffers[4];		// gl id for mrt buffers
	unsigned wgl_buffers[4];	// wgl id for mrt buffers

	int m_null_color;	// null color texture (all white)
	int m_null_normal;	// null normal map (128,128,255)

	GLuint acShader(GLenum type, const std::string& source);
	GLuint acProgram(const std::string& vsSource, const std::string& fsSource);

	// mrt binding
	void mrt_bind_render();
	void mrt_unbind_render();
	void mrt_bind_texture(int target);
	void mrt_unbind_texture(int target);

	// mrt unbinding
	void fb_bind_render(int buffer);
	void fb_unbind_render(int buffer);
	void fb_bind_texture(int buffer,int texunit);
	void fb_unbind_texture(int buffer,int texunit);

	// set cg program parameters
	void set_normal_params(const pVector& diffuse,const pVector& specular,float tile,int texcolor,int texnormal);
	void set_normal_params_mesh(const float& diffuse,const float& specular,float tile,GLuint texcolor,GLuint texnormal);
	void set_normal_params_static(const pVector& diffuse,const pVector& specular,float tile,GLuint texcolor,GLuint texnormal);
	void set_relief_params(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal);
	void set_relief_params_terrain(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal);
	void set_relief_params_mesh(const float& diffuse,const float& specular,float tile,float depth,GLuint texcolor,GLuint texnormal);
	void set_relief_params_static(const pVector& diffuse,const pVector& specular,float tile,float depth,GLuint texcolor,GLuint texnormal);
	void set_light_params(const pVector& lightpos,const pVector& lightcolor);
	void set_blur_params(bool horiz_vert_flag);
	void set_antialias_params(int texcolor,int texnormal);

	// bind cg programs
	void bind_vertex();
	void bind_normal();
	void bind_mesh_vertex();
	void bind_terrain_vertex();
	void bind_mesh_normal();
	void bind_relief();
	void bind_mesh_relief();
	void bind_light();
	void bind_blur();
	void bind_antialias();

	// unbind cg programs
	void unbind_vertex();
	void unbind_normal();
	void unbind_mesh_vertex();
	void unbind_terrain_vertex();
	void unbind_mesh_normal();
	void unbind_relief();
	void unbind_mesh_relief();
	void unbind_light();
	void unbind_blur();
	void unbind_antialias();

	//AST- Copy BLOCK
	void bind_around();
	void unbind_around();

	// light scissor
	int set_light_scissor(const pVector& lightpos,int sx,int sy);

	// draw depth only pass
	void draw_depth(pMesh *m);
	void draw_depth_meshes(void);
	void draw_depth_avatars(void);
	void draw_depth_avatars_shell(void);
	void draw_depth_terrain(pMesh *m);
	void draw_depth_terrain_old(void);
	void draw_depth_shapes(void);
	void draw_depth_shape_instances(void);
	void draw_depth_shape_energy(void);

	// draw geometry sorted by material
	void draw_material(pMesh *m,bool relief);
	void draw_material_terrain(pMesh *m, bool relief);
	void draw_material_mesh(pMesh *m,bool relief);
	void draw_material_meshes(void);
	void draw_material_avatars_shell(bool relief);
	void draw_material_terrain_old(bool relief);
	void draw_material_shapes(bool relief);
	void draw_material_shape_instances(bool relief);
	void draw_material_shape_energy(bool relief);
	void draw_alpha_shadows(void);
	void draw_alpha_energy(void);

	// draw screen aliged 2D rectangle
	void draw_rect(int x,int y,int sx,int sy,bool vpos,bool flipy);

	void ViewOrtho(void);
	void ViewPerspective(void);

	void RenderToTexture_Prep(void);
	void RenderToTexture_Tex(void);
	
	// project/unproject glu funcions in float
	void project(const pVector& p_obj,pVector& p_win);
	void unproject(const pVector& p_win,pVector& p_obj);

	GLint getVertexUniformIndex(void);//*CGparameter parameter);

public:
	int m_sizex, m_sizey;	// current buffers resolution
	int m_num_lights_drawn;	// num of lights rendered
	int m_percent_pixel_drawn;	// % of screen pixels not saved by scissor

	unRenderer();
	~unRenderer();

	void Shutdown();

	GLuint EmptyTexture(void);

	void ClearBlur(void);
	void DrawBlur(int times, float inc);

	// cg program methods
	void set_program_params(bool depth_bias,bool nv_render_depth_texture);
	bool load_programs();
	void free_programs();

	void acInit(void);

	void sync_PhysicsMemory(void);
	
	// mrt methods
	void mrt_create(int sx,int sy);
	void mrt_destroy();

	// draw methods
	void draw_geometry(pMesh *m,bool relief);	// draw mrt
	void draw_lights(pMesh *m, bool scissor, int f_AOGI = 0, int f_whiteout = 0, int f_FAAB_Camera = -1);	// draw lighting 
	void draw_bloom();							// draw bloom
	void draw_antialias();						// draw antialias
	void draw_final(int sx,int sy);				// draw final image to screen
	void draw_debug(int sx,int sy);				// draw debug mrt textures

	void draw_material_avatars(bool relief);

	void draw_avatars(void);

	void checkError(const char *name, const char *situation);

	void GLEnable2D(void);
	void GLDisable2D(void);

	void DrawPane(unsigned int f_texture, int f_x, int f_y, int f_scalex, int f_scaley);

	unGL::GLtexture stepmap;
	bool m_Activate;
	GLint m_meshArray;
	GLint m_VertexMaxUniforms;

	inline void testfunction(void);
	GLuint CreateEmptyTexture(int f_x, int f_y);
	GLuint m_FrameMemory[UNREND_FRAMEMEMSIZE];
	int m_FcurCounter;
	unsigned int m_Fcursor;

	pMaterial *terrainMaterial;

	GLuint CompileShader(GLenum type, const std::string &source);
	GLuint CompileProgram(const std::string &vsSource, const std::string &fsSource);

	QpoVec3d ClothLocator;
	unPointLocator *m_PointLocator;
	int m_SurgeryMode;
	int m_keyPress;

	GLuint mProgram;

	GLint m0AttribLocation;
	GLint m1AttribLocation;
	GLint m2AttribLocation;
	GLint m3AttribLocation;
	GLint m4AttribLocation;

	GLint mModelUniformLocation;
	GLint mViewUniformLocation;
	GLint mProjUniformLocation;
	GLint mMatricesUniformLocation;
	GLint mTextureUniformLocation;
	GLint mLightPosUniformLocation;
	GLint mLightColorUniformLocation;
	GLint mLightNomUniformLocation;
	GLint mTimeUniformLocation;
	GLint mFrameUniformLocation;
	GLint mTeamUniformLocation;
	GLint mAvatarTranslationUniformLocation;
	GLint mCamUniformLocation;

	GLint mPositionAttribLocation;
	GLint mColorAttribLocation;

	GLuint mVertexPositionBuffer;
	GLuint mVertexColorBuffer;
	GLuint mIndexBuffer;
};

#endif