/*

    UNstructure - Physical Structures
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#ifndef _UN_Structure_
#define _UN_Structure_

#include "../Utility/datatypes.h"
#include "../Geometry/unTrr.h"

#include <vector>
#include <string>

#include "paralelo3d.h"

extern int RESULTS_WINDOW_WIDTH;
extern int RESULTS_WINDOW_HEIGHT;

using namespace std;

namespace UN
{

/*typedef struct
{
} unArgument;*/

#define EQAL_LAY0_XSKIPFACTOR RESULTS_WINDOW_WIDTH / 8
#define EQAL_LAY0_YSKIPFACTOR RESULTS_WINDOW_HEIGHT / 6
#define EQAL_LAY1_XSKIPFACTOR 3
#define EQAL_LAY1_YSKIPFACTOR 3

#define EQAL_2DTHRESH_RED 180
#define EQAL_2DTHRESH_GREEN 180
#define EQAL_2DTHRESH_BLUE 180

class unPinSheet;

class unVertex2
{
public:
	unVertex2() {};
	unVertex2(int i_X, int i_Y) { m_X = i_X; m_Y = i_Y; };
	~unVertex2() {};

	float acLength(void) { return sqrt((float)(m_X * m_X + m_Y * m_Y)); };
	float acDist(unVertex2 i_Vert) { return sqrt((float)(i_Vert.m_X * m_X + i_Vert.m_Y * m_Y)); };

	int m_X;
	int m_Y;
};

class unStructure
{
public:
	unStructure() {};
	~unStructure() {};

	int m_Width;
	int m_Height;

	unsigned int m_PinIdx;
	unPinSheet* m_PinSheet;

	std::vector<int> m_PinVertsIdx;
	std::vector<unVertex2> m_PinVerts;
	std::vector<unVertex2> m_Verts;
};

class unTemplate
{
public:
	unTemplate(int i_Width, int i_Height);
	~unTemplate() {};

	void acClear(void);

	unStructure* m_Structure;

	int m_Width;
	int m_Height;

	GLfloat* m_FBuffer;
	unsigned int *m_Buffer;
	unsigned int m_Texture;
};

class unPinSheet
{
public:
	unPinSheet() {};
	unPinSheet(int i_Width, int i_Height, int i_GridWidth, int i_GridHeight);
	~unPinSheet() {};

	int m_Width;
	int m_Height;
	int m_GridWidth;
	int m_GridHeight;

	std::vector<std::vector<unVertex2>> m_RedVerts;
	std::vector<std::vector<unVertex2>> m_GreenVerts;
	std::vector<std::vector<unVertex2>> m_BlueVerts;
};

class unStructureBank
{
public:
	unStructureBank(HWND hWnd);
	~unStructureBank() {};

	bool acAnalyse(unsigned int* i_Screen, unsigned int i_Pitch);
	int acGenerateStructures(int i_StartX, int i_StartY);
	int acResizeStructures(void);
	int acGenerateTemplates(void);

	void acPrintStructure(int i_StructureCount);

	std::vector<unPinSheet*> m_PinSheet;

	std::vector<unStructure*> m_Structure;
	std::vector<unTemplate*> m_Template;

	int m_PinCount;

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
	//*CGparameter m_terrainrotationMatrices;
	//*CGparameter m_terraincolormap;

	// fragment program for normal_mesh
	//*CGprogram m_frag_mesh;
	//*CGparameter m_meshAmbient;
	//*CGparameter m_meshDiffuse;
	//*CGparameter m_meshSpecular;
	//*CGparameter m_meshAlpha;
	//*CGparameter m_meshLightVec;
	//*CGparameter m_meshEyeVec;

	// fragment program for normal_terrain
	//*CGprogram m_frag_terrain;
	//*CGparameter m_terrainAmbient;
	//*CGparameter m_terrainDiffuse;
	//*CGparameter m_terrainSpecular;
	//*CGparameter m_terrainAlpha;
	//*CGparameter m_terrainLightVec;
	//*CGparameter m_terrainEyeVec;

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

	pPBuffer *m_pbuffer;
	unsigned int m_tex[1];
	unsigned int gl_buffers[1];		// gl id for mrt buffers
	unsigned int wgl_buffers[1];	// wgl id for mrt buffers

	int m_sizex,m_sizey;	// current buffers resolution

	int m_null_color;	// null color texture (all white)
	int m_null_normal;	// null normal map (128,128,255)

	// mrt binding
	void buffer_bind_render();
	void buffer_unbind_render();
	void buffer_bind_texture(int target);
	void buffer_unbind_texture(int target);

	// set cg program parameters
	void set_normal_params(const pVector& diffuse,const pVector& specular,float tile,int texcolor,int texnormal);
	void set_normal_params_mesh(const float& diffuse,const float& specular,float tile,GLuint texcolor,GLuint texnormal);
	void set_relief_params(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal);
	void set_relief_params_mesh(const float& diffuse,const float& specular,float tile,float depth,GLuint texcolor,GLuint texnormal);
	void set_light_params(const pVector& lightpos,const pVector& lightcolor);
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

	// light scissor
	int set_light_scissor(const pVector& lightpos,int sx,int sy);

	// cg program methods
	void set_program_params(bool depth_bias,bool nv_render_depth_texture);
	bool load_programs();
	void free_programs();
	
	// mrt methods
	void create_buffer(int sx,int sy);
	void destroy_buffer();

	// draw methods
	void draw_geometry(pMesh *m,bool relief);	// draw mrt
	void draw_lights(pMesh *m,bool scissor);	// draw lighting 
	void draw_bloom();							// draw bloom
	void draw_antialias();						// draw antialias
	void draw_final(int sx,int sy);				// draw final image to screen
	void draw_debug(void);				// draw debug mrt textures
	void draw_debug_plate(void);
	void draw_rect(int x,int y,int sx,int sy,bool vpos,bool flipy);

	void checkError(const char *name, const char *situation);

	bool m_Activate;
	GLint m_meshArray;
	GLint m_VertexMaxUniforms;

	inline void testfunction(void);
	GLuint CreateEmptyTexture(int i_x, int i_y);
};

};

#endif