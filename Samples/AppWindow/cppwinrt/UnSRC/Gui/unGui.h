/*

    unGUI - Progressive User Interface
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#pragma once

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include <stdio.h>

#include "paralelo3d.h"

#include "../Utility/unConsole.h"
#include "unGUIscheme.h"

#include "TumDocument.h"

#include "../Texture/unTextureBank.h"

#include "SDL.h"
#include "OGLFT.h"

#include "../Utility/datatypes.h"

//----------------------------------------------------------------------------//
// Definitions                                                                //
//----------------------------------------------------------------------------//

#define VID_WIDTH 800
#define VID_HEIGHT 600

#define RENDER_2D 2030
#define RENDER_3D 2031

#define GUI_DEFAULT_EDITDX 1280
#define GUI_DEFAULT_EDITDY 450
#define GUI_MIPMAP 0

//----------------------------------------------------------------------------//
// Class Declarations                                                         //
//----------------------------------------------------------------------------//

namespace GUI
{

///// Gui Click Response
class unGuiResponse
{
public:
	unGuiResponse(int ButID, int PaneID)
		{ EventID = 0; ButtonID = ButID; m_PaneID = PaneID;
		  m_hover = false;
		  m_click = false;
		  m_select = false; };

	bool m_hover;
	bool m_click;
	bool m_select;

	int m_PaneID;

	int EventID;
	int ButtonID;
};

class unTreeLink
{
public:
	unTreeLink(int D1, int D2) { KX.push_back(D1); KX.push_back(D2); };
	virtual ~unTreeLink() {};

	std::vector<int> KX;
};

class EventArgs
{
public:
	/*************************************************************************
		Construction
	*************************************************************************/
	EventArgs(void) : handled(false) {}
	EventArgs(unGuiResponse* response) : handled(false) {m_response = response;}
	virtual ~EventArgs(void) {}


	/*************************************************************************
		Data members
	*************************************************************************/
	unGuiResponse* m_response;
	int m_ID;
	bool handled;		//!< handlers should set this to true if they handled the event, or false otherwise.
};

template<typename T>
struct FunctorReferenceBinder
{
    FunctorReferenceBinder(T& functor) :
        d_functor(functor)
    {}

    T& d_functor;
};

class SlotFunctorBase
{
public:
    virtual ~SlotFunctorBase() {};
    virtual bool operator()(const EventArgs& args) = 0;
};

class FreeFunctionSlot : public SlotFunctorBase
{
public:
    //! Slot function type.
    typedef bool (SlotFunction)(const EventArgs&);

    FreeFunctionSlot(SlotFunction* func) :
        d_function(func)
    {}

    virtual bool operator()(const EventArgs& args)
    {
        return d_function(args);
    }

private:
    SlotFunction* d_function;
};

template<typename T>
class FunctorCopySlot : public SlotFunctorBase
{
public:
    FunctorCopySlot(const T& functor) :
        d_functor(functor)
    {}

	/// Temporary Removed
    virtual bool operator()(const EventArgs& args)
    {
        return d_functor(args);
    }

private:
    T d_functor;
};

template<typename T>
class MemberFunctionSlot : public SlotFunctorBase
{
public:
    //! Member function slot type.
    typedef bool(T::*MemberFunctionType)(const EventArgs&);

    MemberFunctionSlot(MemberFunctionType func, T* obj) :
        d_function(func),
        d_object(obj)
    {}

    virtual bool operator()(const EventArgs& args)
    {
        return (d_object->*d_function)(args);
    }

private:
    MemberFunctionType d_function;
    T* d_object;
};

class SubscriberSlot
{
public:
    SubscriberSlot();
	~SubscriberSlot() {};

	/// Main Constructor
    SubscriberSlot(FreeFunctionSlot::SlotFunction* func);

	bool operator()(const EventArgs& args) const
    {
        return (*d_functor_impl)(args);
    }

	/// templatised constructors
    template<typename T>
    SubscriberSlot(bool (T::*function)(const EventArgs&), T* obj) :
        d_functor_impl(new MemberFunctionSlot<T>(function, obj))
    {}

    template<typename T>
    SubscriberSlot(const FunctorReferenceBinder<T>& binder) :
        d_functor_impl(new FunctorReferenceSlot<T>(binder.d_functor))
    {}

    template<typename T>
    SubscriberSlot(const T& functor) :
        d_functor_impl(new FunctorCopySlot<T>(functor))
    {}

    template<typename T>
    SubscriberSlot(T* functor) :
        d_functor_impl(new FunctorPointerSlot<T>(functor))
    {}

private:
    //Internal functor object to which we are bound
    SlotFunctorBase* d_functor_impl;
};

class unTextBox
{
public:
	unTextBox() {};
	virtual ~unTextBox() {};

	/// Functional Constructors Entry
	unTextBox(int TextType, const char *Text)
		{ m_response = new unGuiResponse(TextType, 0);
		  m_Content = Text;
		  m_TextType = TextType;
		  m_hover = false; m_click = false; m_select = false; }

public:
	int m_TextType;

	bool m_hover;
	bool m_click;
	bool m_select;

	unGuiResponse* m_response;

	const char *m_Content;

	int m_posx;
	int m_posy;
};

class unEditBox
{
public:
	unEditBox() {};
	virtual ~unEditBox() {};

	/// Functional Constructors Entry
	unEditBox(int EditType, int TextureID, const char *Text)
		{ m_response = new unGuiResponse(EditType, 0);
		  m_TextureID = TextureID;
		  m_Static = Text;
		  m_EditType = EditType;
		  m_hover = false; m_click = false; m_select = false;
		  m_Document = -1; }

	unEditBox(int EditType, int TextureID, int i_DocumentID)
		{ m_response = new unGuiResponse(EditType, 0);
		  m_TextureID = TextureID;
		  m_EditType = EditType;
		  m_hover = false; m_click = false; m_select = false;
		  m_Document = i_DocumentID; }

public:
	int m_EditType;
	int m_TextureID;
	int m_StaticLength;

	bool m_hover;
	bool m_click;
	bool m_select;

	int m_Document;

#if 0
	std::vector<GLtexmin> m_TexPlate;
#else
	unGL::GLtexmin m_TexPlate;
#endif

	unGuiResponse* m_response;

	std::string m_Content;
	std::string m_Static;

	std::vector<unGL::GLvecf2> vecvertex;
	std::vector<unGL::GLvecf2> vecgizmot;
	std::vector<unGL::GLvecf2> vecbounds;
	std::vector<unGL::GLmaterial> vectext;
};

class unButton
{
public:
	unButton() {};
	virtual ~unButton() {};

	/// Functional Constructors Entry
	unButton(int ButtonType, int TextureID, int PaneID)
		{ m_response = new unGuiResponse(ButtonType, PaneID);
		  m_ButtonType = ButtonType;
		  m_TextureID = TextureID;
		  m_hover = false; m_click = false; m_select = false; }

	/// Create Text
	inline /*unTreeLink*/void addText(int TextType, const char *Text)
		{ /*return*/ addText(TextType, 0, 0, Text); }

	inline /*unTreeLink*/void addText(int TextType, int mX, int mY, const char *Text)
		{
		unTextBox* text = new unTextBox(TextType, Text);
		text->m_posx = mX;
		text->m_posy = mY;
		vecstatictext.push_back(text);
		/*return unTreeLink(m_ID, vecstatictext.size()-1);*/ }

public:
	int m_ButtonType;
	int m_TextureID;

	bool m_hover;
	bool m_click;
	bool m_select;

	unGuiResponse* m_response;

	std::vector<unTextBox*> vecstatictext;

	std::vector<unGL::GLvecf2> vecvertex;
	std::vector<unGL::GLvecf2> vecgizmot;
	std::vector<unGL::GLvecf2> vecbounds;
	std::vector<unGL::GLmaterial> vectext;
};

class unGUIpane
{
public:
	unGUIpane() {};
	virtual ~unGUIpane() {};

	/// Functional Constructors Entry
	unGUIpane(int PaneType, float x, float y) { m_PaneType = PaneType; m_posx = x; m_posy = y; m_visible = true; }

	//void *getVar(int ID);				/// Originator
	//void setVar(void *Var, int ID);

	/// Create Text
	inline /*unTreeLink*/void addText(int TextType, const char *Text)
		{ /*return*/ addText(TextType, 0, 0, Text); }

	inline /*unTreeLink*/void addText(int TextType, int mX, int mY, const char *Text)
		{
		unTextBox* text = new unTextBox(TextType, Text);
		text->m_posx = mX;
		text->m_posy = mY;
		vecstatictext.push_back(text);
		/*return unTreeLink(m_ID, vecstatictext.size()-1);*/ }

		/// Create Pane
	inline unTreeLink addButton(int ButtonType, int TextureID, int PaneID)
		{ return addButton(ButtonType, TextureID, PaneID, 4, unGL::GLvecf2(m_posx, m_posy), unGL::GLvecf2(m_posx + ScaleX, m_posy), unGL::GLvecf2(m_posx + ScaleX, m_posy + ScaleY), unGL::GLvecf2(m_posx, m_posy + ScaleY)); }

	inline unTreeLink addButton(int ButtonType, int TextureID, int PaneID, int nbGizmot, ... )
		{ va_list vl; va_start(vl, nbGizmot);
		unButton* button = new unButton(ButtonType, TextureID, PaneID);

		for(int i=0; i < nbGizmot; ++i)
			button->vecgizmot.push_back(va_arg( vl, unGL::GLvecf2 ));

		vecbutton.push_back(button);
		va_end( vl );
		return unTreeLink(m_ID, vecbutton.size()-1); }

	inline void setBounds(int nbGizmot, ... )
		{ va_list vl; va_start(vl, nbGizmot);

		vecgizmot.clear();
		for(int i=0; i < nbGizmot; ++i)
		vecgizmot.push_back(va_arg( vl, unGL::GLvecf2 ));
		va_end( vl ); }

	inline void autoBounds(void)
		{ vecgizmot.push_back(unGL::GLvecf2(m_posx, m_posy));
		  vecgizmot.push_back(unGL::GLvecf2(m_posx + ScaleX, m_posy));
		  vecgizmot.push_back(unGL::GLvecf2(m_posx + ScaleX, m_posy + ScaleY));
		  vecgizmot.push_back(unGL::GLvecf2(m_posx, m_posy + ScaleY)); }

	inline unButton* getLast(void) { if(vecbutton.size() > 0) return vecbutton[vecbutton.size()-1]; else unPrintError("ERROR vecbutton empty"); return NULL; }
	inline int getLastID(void) { return vecbutton.size() - 1; }

	inline /*unTreeLink*/void addEditBox(int EditType, int TextureID, const char *Text, int nbGizmot, ... )
		{ va_list vl; va_start(vl, nbGizmot);
		unEditBox* editbox = new unEditBox(EditType, TextureID, Text);

		for(int i=0; i < nbGizmot; ++i)
			editbox->vecgizmot.push_back(va_arg( vl, unGL::GLvecf2 ));

		veceditbox.push_back(editbox);
		va_end( vl );
		/*return unTreeLink(m_ID, veceditbox.size()-1);*/ }

	inline /*unTreeLink*/void addEditBox(int EditType, int TextureID, int i_DocumentID, int nbGizmot, ... )
		{ va_list vl; va_start(vl, nbGizmot);
		unEditBox* editbox = new unEditBox(EditType, TextureID, i_DocumentID);

		for(int i=0; i < nbGizmot; ++i)
			editbox->vecgizmot.push_back(va_arg( vl, unGL::GLvecf2 ));

		veceditbox.push_back(editbox);
		va_end( vl );
		/*return unTreeLink(m_ID, veceditbox.size()-1);*/ }

public:
	float ScaleX;
	float ScaleY;
	float ScaleZ;

	float m_posx;
	float m_posy;
	unGL::GLvecf2 m_pos;

	int m_PaneType;
	int m_TextureID;
	int m_ID;
	int m_angle;

	bool m_hover;
	bool m_visible;

	float m_scrollx;
	float m_scrolly;

	std::vector<unTextBox*> vecstatictext;
	std::vector<unGL::GLvecf2> vecvertex;
	std::vector<unGL::GLmaterial> vectext;
	std::vector<unGL::GLvecf2> vecgizmot;
	std::vector<unGL::GLvecf2> vecbounds;
	std::vector<unButton*> vecbutton;
	std::vector<unEditBox*> veceditbox;
};

class unGUI
{
public:
	unGUI(unsigned int i_width, unsigned int i_height);
    virtual ~unGUI();

	void acReset(void);
	void acResetPositions(void);
	void acRefresh(void);

	void acVidResize(unsigned int i_width, unsigned int i_height);

	bool PntIntersect(std::vector<unGL::GLvecf2> vec, float x, float y);

	/// Render State Prep
	void GLEnable2D(void);
	void GLDisable2D(void);

	void Perspective2D(RECT size);
	void Perspective3D(float p_fov, float p_near, float p_far, float width, float height);

	void setRender2D(void);
	void setRender3D(void);

	void acClickCancel(int Range, int PaneID, int GizID);

	inline unGUIpane* getLast(void) { if(vecpane.size() > 0) return vecpane[vecpane.size()-1]; else unPrintError("ERROR vecpane empty"); return NULL; }
	inline int getLastID(void) { return vecpane.size() - 1; }

	inline unButton* getLastD2(void) { if(vecpane.size() > 0 && vecpane[vecpane.size()-1]->vecbutton.size() > 0) return vecpane[vecpane.size()-1]->vecbutton[vecpane[vecpane.size()-1]->vecbutton.size()-1]; else unPrintError("ERROR vector empty"); return NULL; }
	inline int getLastIDD2(void) { if(vecpane.size() > 0 && vecpane[vecpane.size()-1]->vecbutton.size() > 0) return vecpane[vecpane.size()-1]->vecbutton.size()-1; else unPrintError("ERROR vector empty"); return NULL; }

	/// Create Text
	inline /*unTreeLink*/void addText(int TextType, const char *Text)
		{ /*return*/ addText(TextType, 0, 0, Text); }

	inline /*unTreeLink*/void addText(int TextType, int mX, int mY, const char *Text)
		{
		unTextBox* text = new unTextBox(TextType, Text);
		text->m_posx = mX;
		text->m_posy = mY;
		vecstatictext.push_back(text);
		/*return unTreeLink(m_ID, vecstatictext.size()-1);*/ }

	bool acCrunch(void);
	void acFrame(void);

	bool acMouseMotion(const Uint16 mousex, const Uint16 mousey);
	unGuiResponse* acMouseClick(void);
	void acKeyDown(char KeyPressed);

	/// Create Pane
	inline void CreatePane(int PaneType, int TextureID, float x, float y)
		{ clone_structPane(PaneType, TextureID, x, y, unGL::GLvecf2(0,0), 320.0f, 240.0f, 1.0f); }

	inline void CreatePane(int PaneType, int TextureID, unGL::GLvecf2 m_pos)
		{ clone_structPane(PaneType, TextureID, 0, 0, m_pos, 320.0f, 240.0f, 1.0f); }

	inline void CreatePane(int PaneType, int TextureID, float x, float y, float ScaleX, float ScaleY, float ScaleZ)
		{ clone_structPane(PaneType, TextureID, x, y, unGL::GLvecf2(0,0), ScaleX, ScaleY, ScaleZ); }

	inline void CreatePane(int PaneType, int TextureID, unGL::GLvecf2 m_pos, float ScaleX, float ScaleY, float ScaleZ)
		{ clone_structPane(PaneType, TextureID, 0, 0, m_pos, ScaleX, ScaleY, ScaleZ); }

	inline void clone_structPane(int PaneType, int TextureID, float m_posx, float m_posy, unGL::GLvecf2 m_pos, float ScaleX, float ScaleY, float ScaleZ)
	{
	unGUIpane* pane;
	pane = new unGUIpane(PaneType, m_posx, m_posy);
	pane->m_TextureID = TextureID;
	pane->ScaleX = ScaleX;
	pane->ScaleY = ScaleY;
	pane->ScaleZ = ScaleZ;
	pane->m_pos = m_pos;
	pane->autoBounds();
	pane->m_ID = vecpane.size();
	vecpane.push_back(pane);
	m_incnt++;
	}

	void acDocumentPlate(unEditBox* i_EditBox, UInt32 i_Address);

	static unGUI* instance();

	/// Dynamic Scheme Fractal pass spike

private:
    static unGUI* s_instance;
	unTextureBank* m_texturebank;

	short renderMode;

	float* matrix2D;
	float* matrix3D;

	/// Render vars and scheme
	float Depth;

	unGuiResponse* defaultResponse;

public:
	std::vector<unGUIpane*> vecpane;
	std::vector<unTextBox*> vecstatictext;

	unDocumentBank *m_DocumentBank;

	/// For Crunching
	std::vector<int> vecClist;

	int m_incnt;
	int m_outcnt;

	unsigned int m_VidWidth;
	unsigned int m_VidHeight;

	void acPush(const char* i_line);

#if 1
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

#if 0 // QAGE_DESKTOP
	pPBuffer *m_pbuffer;
#endif
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

	unGL::GLtexture stepmap;
	bool m_Activate;
	GLint m_meshArray;
	GLint m_VertexMaxUniforms;

	inline void testfunction(void);
	GLuint CreateEmptyTexture(int i_x, int i_y);
#endif

#pragma message("FIXME Set Scheme Modes")
	bool m_mode;
	bool m_reset;

private: //OGLFT
	void initFont(void);
	void reshape(int width, int height);
	void reset(void);
	void char_rotate_x(float dx);
	void char_rotate_y(float dy);
	void char_rotate_z(float dz);
	void string_rotate(float dz);
	void textrender(void);

	char* USAGE;
	char* commands;
	char* text;
	float point_size;

	/*OGLFT::Monochrome* commands_face;
	OGLFT::Outline* login_face;
	OGLFT::Monochrome* monochrome_face;
	OGLFT::Grayscale* grayscale_face;
	OGLFT::Translucent* translucent_face;
	OGLFT::Outline* outline_face;
	OGLFT::Filled* filled_face;
	#ifndef OGLFT_NO_SOLID
	OGLFT::Solid* solid_face;
	#else
	OGLFT::Monochrome* solid_face;
	#endif
	OGLFT::MonochromeTexture* monochrome_texture_face;
	OGLFT::GrayscaleTexture* grayscale_texture_face;
	OGLFT::TranslucentTexture* translucent_texture_face;*/

	float dy;
	int viewport_width;
	int viewport_height;
	int x_rot, y_rot, z_rot;
};

}; //END namespace unGUI