#ifndef __UNRENDERER__
#define __UNRENDERER__

#include "../../QActiveFramewrk.h"
#include "../../Avatar/unMesh.h"

#include "../../Process/UNprocessor.h"

#include "../textureDef.h"

class unRenderer
{
	// vectex program and parameters
	//*CGprogram m_vert_prog;
	//*CGparameter m_vtile;
	//*CGparameter m_vdepth;

	// vectex program for view mesh
	//*CGprogram m_vert_mesh;
	//*CGparameter m_meshtile;
	//*CGparameter m_meshdepth;
	//*CGparameter m_meshmatrix;
	//*CGparameter m_meshtranslation;
	//*CGparameter m_meshrotationMatrices;
	//*CGparameter m_meshtranslationVectors;
	//*CGparameter m_meshvertices;
	//*CGparameter m_meshcolormap;
	//*CGparameter m_meshmatcount;

	//*CGprofile vertexProfile;

	//*CGprogram m_frag_mesh;

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

	// render options
	bool m_nv_render_depth_texture; // use depth buffer
	bool m_depth_bias;	// use perspective depth bias

	pPBuffer *m_mrt;		// multiple render targets
	unsigned m_mrttex[4];	// mrt texture ids

	pPBuffer *m_fb[4];		// frame buffers used for bloom
	unsigned m_fbtex[4];	// bloom textures for each frame buffer

	unsigned gl_buffers[4];		// gl id for mrt buffers
	unsigned wgl_buffers[4];	// wgl id for mrt buffers

	int m_sizex,m_sizey;	// current buffers resolution

	int m_null_color;	// null color texture (all white)
	int m_null_normal;	// null normal map (128,128,255)

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
	void set_relief_params(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal);
	void set_relief_params_mesh(const float& diffuse,const float& specular,float tile,float depth,GLuint texcolor,GLuint texnormal);
	void set_light_params(const pVector& lightpos,const pVector& lightcolor);
	void set_blur_params(bool horiz_vert_flag);
	void set_antialias_params(int texcolor,int texnormal);

	// bind cg programs
	void bind_vertex();
	void bind_normal();
	void bind_mesh_vertex();
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
	void unbind_mesh_normal();
	void unbind_relief();
	void unbind_mesh_relief();
	void unbind_light();
	void unbind_blur();
	void unbind_antialias();

	// light scissor
	int set_light_scissor(const pVector& lightpos,int sx,int sy);

	// draw depth only pass
	void draw_depth(pMesh *m);
	void draw_depth_avatars(void);
	void draw_depth_player(void);

	// draw geometry sorted by material
	void draw_material(pMesh *m,bool relief);
	void draw_material_avatars(bool relief);
	void draw_material_player(bool relief);

	// draw screen aliged 2D rectangle
	void draw_rect(int x,int y,int sx,int sy,bool vpos,bool flipy);
	
	// project/unproject glu funcions in float
	void project(const pVector& p_obj,pVector& p_win);
	void unproject(const pVector& p_win,pVector& p_obj);

	GLint getVertexUniformIndex(//*CGparameter parameter);

public:
	int m_num_lights_drawn;	// num of lights rendered
	int m_percent_pixel_drawn;	// % of screen pixels not saved by scissor

	unRenderer();
	~unRenderer();

	// cg program methods
	void set_program_params(bool depth_bias,bool nv_render_depth_texture);
	bool load_programs();
	void free_programs();
	
	// mrt methods
	void mrt_create(int sx,int sy);
	void mrt_destroy();

	// draw methods
	void draw_geometry(pMesh *m,bool relief);	// draw mrt
	void draw_lights(pMesh *m,bool scissor);	// draw lighting 
	void draw_bloom();							// draw bloom
	void draw_antialias();						// draw antialias
	void draw_final(int sx,int sy);				// draw final image to screen
	void draw_debug(int sx,int sy);				// draw debug mrt textures

	void checkError(const char *name, const char *situation);

	void GLEnable2D(void);
	void GLDisable2D(void);
	void DrawPane(unsigned int i_texture, int i_x, int i_y, int i_scalex, int i_scaley);

	unGL::GLtexture stepmap;
	bool m_Activate;
	GLint m_meshArray;
	GLint m_VertexMaxUniforms;

	inline void testfunction(void);
};

#endif