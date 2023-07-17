/*

	unGUI - Progressive User Interface
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include <iostream>
#include <string>
#include "unGUI.h"

#include "../QActiveFramewrk.h"

#include <iterator>

using namespace GUI;

//----------------------------------------------------------------------------//
// Instance                                                                   //
//----------------------------------------------------------------------------//

unGUI* unGUI::s_instance = 0;
unGUI* unGUI::instance()
{
  return s_instance;
}

//----------------------------------------------------------------------------//
// Constructors                                                               //
//----------------------------------------------------------------------------//

unGUI::unGUI(unsigned int i_width, unsigned int i_height)
{ 
	m_texturebank = unTextureBank::instance();
	m_DocumentBank = new unDocumentBank();

	m_VidWidth = i_width;
	m_VidHeight = i_height;

	matrix2D = new float[16];
	matrix3D = new float[16];

	m_incnt = 0;
	m_outcnt = 0;
	m_mode = 0;

	defaultResponse = new GUI::unGuiResponse(-1, 0);

	unConsoleAttribute(CONSOLE_MSG);

#if 0
	initFont();
#endif

	m_vert_prog=0;
	m_vtile=0;
	m_vdepth=0;

	m_vert_mesh=0;
	m_meshtile=0;
	m_meshdepth=0;
	m_meshrotationMatrices = 0;
	m_meshcolormap = 0;

	m_vert_terrain=0;
	m_terraintile=0;
	m_terraindepth=0;
	m_terrainrotationMatrices = 0;
	m_terraincolormap = 0;

	m_frag_mesh=0;
	m_frag_prog_normal=0;
	m_ndiffuse=0;
	m_nspecular=0;
	m_nplanes=0;

	m_frag_prog_relief=0;
	m_rdiffuse=0;
	m_rspecular=0;
	m_rplanes=0;

	m_frag_prog_light=0;
	m_lplanes=0;
	m_lpos=0;
	m_lcolor=0;

	m_frag_prog_blur=0;
	m_bdisp=0;

	m_frag_prog_antialias=0;
	m_apixelsize=0;
	m_aweight=0;

	m_pbuffer=0;
	m_tex[0]=0;

	m_sizex=m_sizey=0;

	m_nv_render_depth_texture=false;
	m_depth_bias=false;

	/////// Create Buffer Rendering Context ///////
	//set_program_params(false, true);
	//create_buffer(GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY);
	//load_programs();

	unConsoleAttribute(CONSOLE_INIT);

#if 0
	/////// Tumble Document
	TumDocument* TDocument = new TumDocument("EmptyDocument", "Data/QoreResource/TestDocument.qore");

#if 0
	TDocument->hwnd = hwnd;
#endif

	TDocument->addBlocker("[FLASH]", 40);
	TDocument->addExtractor(".swf", 40, 0);

#if 0
	TDocument->Tumble();
	TDocument->PrintResults();
#endif

	m_DocumentBank->m_Document.push_back(new TumDocument("EmptyDocument", "Data/QoreResource/TestDocument.qore"));

#if 0
	printf("LINE 0: %s\n", m_DocumentBank->getDocument(0)->m_Content[0].c_str());
	printf("LINE 1: %s\n", m_DocumentBank->getDocument(0)->m_Content[1].c_str());
	printf("LINE 2: %s\n", m_DocumentBank->getDocument(0)->m_Content[2].c_str());
#endif
#endif
}

//----------------------------------------------------------------------------//
// Destructor                                                                 //
//----------------------------------------------------------------------------//

unGUI::~unGUI()
{
	destroy_buffer();
	free_programs();

	size_t ident = 0, iter = 0;

	for(ident = 0; ident < m_outcnt; ident++)
		{
		vecpane[ident]->vectext.clear();
		vecpane[ident]->vecvertex.clear();

		for(iter = 0; iter < vecpane[ident]->vecbutton.size(); iter++)
			{
			vecpane[ident]->vecbutton[iter]->vecvertex.clear();
			vecpane[ident]->vecbutton[iter]->vecgizmot.clear();
			vecpane[ident]->vecbutton[iter]->vecbounds.clear();
			vecpane[ident]->vecbutton[iter]->vectext.clear();
			}

		for(iter = 0; iter < vecpane[ident]->veceditbox.size(); iter++)
			{
			vecpane[ident]->veceditbox[iter]->vecvertex.clear();
			vecpane[ident]->veceditbox[iter]->vecgizmot.clear();
			vecpane[ident]->veceditbox[iter]->vecbounds.clear();
			vecpane[ident]->veceditbox[iter]->vectext.clear();

			if(vecpane[ident]->veceditbox[iter]->m_Document >= 0)
				{
				glDeleteTextures(1, &vecpane[ident]->veceditbox[iter]->m_TexPlate.m_TexID);
				vecpane[ident]->veceditbox[iter]->m_TexPlate.m_TexID = 0;
				}
			}
		}

	vecpane.clear();

	m_incnt = 0;
	m_outcnt = 0;
}

//----------------------------------------------------------------------------//
// Render Modes                                                               //
//----------------------------------------------------------------------------//

void unGUI::Perspective3D(float p_fov, float p_near, float p_far, float width, float height)
{
	renderMode = RENDER_3D;
	float lw = (float)width, lh = (float)height;
	if(height == 0) height = 1;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(p_fov,lw/lh,p_near,p_far);
	glMatrixMode(GL_MODELVIEW);
	//glGetDoublev(GL_PROJECTION_MATRIX , matrix3D);
	glLoadIdentity();
}

void unGUI::Perspective2D(RECT size)
{
	renderMode = RENDER_2D;
	glViewport(size.left, size.bottom, size.right, size.top);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(size.left, size.right, size.bottom, size.top);
	glMatrixMode(GL_MODELVIEW);
	//glGetDoublev(GL_PROJECTION_MATRIX, matrix2D);
	glLoadIdentity();
}

void unGUI::setRender2D(void)
{
	if(renderMode==RENDER_2D) return;
	renderMode = RENDER_2D;
	glMatrixMode(GL_PROJECTION);
	//glLoadMatrixd(matrix2D);
	glMatrixMode(GL_MODELVIEW);
}

void unGUI::setRender3D(void)
{
	if(renderMode==RENDER_3D) return;
	renderMode = RENDER_3D;
	glMatrixMode(GL_PROJECTION);
	//glLoadMatrixd(matrix3D);
	glMatrixMode(GL_MODELVIEW);
}

void unGUI::GLEnable2D(void)
{
   int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
}

void unGUI::GLDisable2D(void)
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

bool unGUI::PntIntersect(std::vector<unGL::GLvecf2> vec, float x, float y)
{
	int i, j, c = 0;
	for (i = 0, j = vec.size() - 1; i < vec.size(); j = i++)
		{
		if ((((vec[i].m_y<=y) && (y < vec[j].m_y)) || 
			((vec[j].m_y<=y) && (y < vec[i].m_y))) &&
			(x < (vec[j].m_x - vec[i].m_x) * (y - vec[i].m_y) / (vec[j].m_y - vec[i].m_y) + vec[i].m_x))
		   c = !c;
		}
	return c;
}

void unGUI::acRefresh(void)
{
	m_texturebank = unTextureBank::instance();
}

void unGUI::acFrame(void)
{
	GLEnable2D();
	glEnable( GL_TEXTURE_2D );

	glDisable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

#if 0 //SUSPENDED (FRAPS)
	if(KEY_DOWN(QIN_F3)) draw_debug();
	if(KEY_DOWN(QIN_F4)) draw_debug_plate();
#endif

	/// Conditional Crunch Time
	if(m_incnt > 0)
		if(!acCrunch()) unPrintError("ERROR Crunch Bite 'Out of Bounds'");

	for(size_t ident=0; ident < m_outcnt; ident++)
		{
		if(vecpane[ident]->m_visible)
			{
			if(m_mode > 0)
				{
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);
				glEnable(GL_BLEND);

				/// Render Button Effects
				for(size_t k=0; k < vecpane[ident]->vecbutton.size(); k++)
					{
					if(vecpane[ident]->vecbutton[k]->m_ButtonType == 0)
						{
						/// Set GL States
						if(vecpane[ident]->vecbutton[k]->m_hover && vecpane[ident]->m_hover)
							{
							vecpane[ident]->vecbutton[k]->vectext[0].m_alpha = 1.0;
							}
						else
							{
							if(vecpane[ident]->vecbutton[k]->vectext[0].m_alpha - 0.085 >= 0) vecpane[ident]->vecbutton[k]->vectext[0].m_alpha -= 0.085;
							else vecpane[ident]->vecbutton[k]->vectext[0].m_alpha = 0;
							}

						// Bind the texture to which subsequent calls refer to
						//glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->vectext[0].m_texlist].m_TexID );

						//glColor3ub(185, 185, 255);
						//glColor4f(0.8f, 0.8f, 1.0f, vecpane[ident]->vecbutton[k]->vectext[0].m_alpha);
						//glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[3].m_TexID );

						if(vecpane[ident]->vecbutton[k]->m_click)
							{
							vecpane[ident]->vecbutton[k]->m_click = false;
							glColor4f(0.1f, 0.8f, 1.0f, vecpane[ident]->vecbutton[k]->vectext[0].m_alpha);
							glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[5].m_TexID );
							}
						else
							{
							glColor4f(0.8f, 0.8f, 1.0f, vecpane[ident]->vecbutton[k]->vectext[0].m_alpha);
							glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[2].m_TexID );
							}

						glBegin( GL_QUADS );

						for(size_t id=0; id < vecpane[ident]->vecbutton[k]->vecvertex.size(); id++)
							{
							glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
							glVertex2d(vecpane[ident]->vecbutton[k]->vecvertex[id].m_x, vecpane[ident]->vecbutton[k]->vecvertex[id].m_y);
							}

						glEnd();
						}

					if(vecpane[ident]->vecbutton[k]->m_ButtonType == 1)
						{
						/// Set GL States
						if(vecpane[ident]->vecbutton[k]->m_click)
							{
							vecpane[ident]->vecbutton[k]->m_click = false;
							glColor4f(0.1f, 0.5f, 1.0f, 1.0f);
							}
						else
							{
							if(vecpane[ident]->vecbutton[k]->m_select) glColor4f(0.1f, 0.5f, 1.0f, 1.0f);
							else
								{
								if(vecpane[ident]->vecbutton[k]->m_hover && vecpane[ident]->m_hover) vecpane[ident]->vecbutton[k]->vectext[0].m_alpha = 0.9f;
								else
									{
									if(vecpane[ident]->vecbutton[k]->vectext[0].m_alpha - 0.1 >= 0.3) vecpane[ident]->vecbutton[k]->vectext[0].m_alpha -= 0.1;
									else vecpane[ident]->vecbutton[k]->vectext[0].m_alpha = 0.3;
									}
								glColor4f(1.0f, 1.0f, 1.0f, vecpane[ident]->vecbutton[k]->vectext[0].m_alpha);
								}
							}

						glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->vecbutton[k]->m_TextureID].m_TexID );

						glBegin( GL_QUADS );

						for(size_t id=0; id < vecpane[ident]->vecbutton[k]->vecvertex.size(); id++)
							{
							glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
							glVertex2d(vecpane[ident]->vecbutton[k]->vecvertex[id].m_x, vecpane[ident]->vecbutton[k]->vecvertex[id].m_y);
							}

						glEnd();
						}

					if(vecpane[ident]->vecbutton[k]->m_ButtonType == 2)
						{
						/// Set GL States
						if(vecpane[ident]->m_hover)
							{
							if(vecpane[ident]->vecbutton[k]->m_hover)
								{
								vecpane[ident]->vecbutton[k]->vectext[0].m_alpha = 1.0;
								}
							else
								{
								if(vecpane[ident]->vecbutton[k]->vectext[0].m_alpha - 0.03 > 0.3) vecpane[ident]->vecbutton[k]->vectext[0].m_alpha -= 0.03;
								else vecpane[ident]->vecbutton[k]->vectext[0].m_alpha = 0.3;
								}
							}
						else
							{
							if(vecpane[ident]->vecbutton[k]->vectext[0].m_alpha - 0.045 > 0.15) vecpane[ident]->vecbutton[k]->vectext[0].m_alpha -= 0.045;
							else vecpane[ident]->vecbutton[k]->vectext[0].m_alpha = 0.15;
							}

						if(vecpane[ident]->vecbutton[k]->m_click)
							{
							vecpane[ident]->vecbutton[k]->m_click = false;
							glColor4f(0.1f, 0.8f, 1.0f, vecpane[ident]->vecbutton[k]->vectext[0].m_alpha);
							glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->vecbutton[k]->m_TextureID].m_TexID );
							}
						else
							{
							glColor4f(0.8f, 0.8f, 1.0f, vecpane[ident]->vecbutton[k]->vectext[0].m_alpha);
							glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->vecbutton[k]->m_TextureID].m_TexID );
							}

						glBegin( GL_QUADS );

						for(size_t id=0; id < vecpane[ident]->vecbutton[k]->vecvertex.size(); id++)
							{
							glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
							glVertex2d(vecpane[ident]->vecbutton[k]->vecvertex[id].m_x, vecpane[ident]->vecbutton[k]->vecvertex[id].m_y);
							}

						glEnd();
						}
					}

				/// Set GL States
				if(vecpane[ident]->m_PaneType == 5)
					{
					if(vecpane[ident]->m_hover)
						{
						if(vecpane[ident]->vectext[0].m_alpha + 0.25 <= 1.0) vecpane[ident]->vectext[0].m_alpha += 0.25;
						else vecpane[ident]->vectext[0].m_alpha = 1.0;
						}
					else
						{
						if(vecpane[ident]->vectext[0].m_alpha - 0.1 >= 0) vecpane[ident]->vectext[0].m_alpha -= 0.1;
						else vecpane[ident]->vectext[0].m_alpha = 0.085f;
						}
					}
				else if(vecpane[ident]->m_PaneType == 2 || (vecpane[ident]->m_PaneType > 100 && vecpane[ident]->m_PaneType < 200))
					{
#if 0
					if(vecpane[ident]->m_hover)
						{
						if(vecpane[ident]->vectext[0].m_alpha + 0.25 <= 0.375) vecpane[ident]->vectext[0].m_alpha += 0.25;
						else vecpane[ident]->vectext[0].m_alpha = 0.3;
						}
					else
						{
						if(vecpane[ident]->vectext[0].m_alpha - 0.1 >= 0.085f) vecpane[ident]->vectext[0].m_alpha -= 0.1;
						else vecpane[ident]->vectext[0].m_alpha = 0.085f;
						}
#endif
					if(vecpane[ident]->m_hover)
						{
						if(vecpane[ident]->vectext[0].m_alpha + 0.15 <= 0.75f) vecpane[ident]->vectext[0].m_alpha += 0.15;
						else vecpane[ident]->vectext[0].m_alpha = 0.75;
						}
					else
						{
						if(vecpane[ident]->vectext[0].m_alpha - 0.05 >= 0.085f) vecpane[ident]->vectext[0].m_alpha -= 0.05;
						else vecpane[ident]->vectext[0].m_alpha = 0.085f;
						}
					}
				else vecpane[ident]->vectext[0].m_alpha = 1;
				}
			else vecpane[ident]->vectext[0].m_alpha = 1;

			glColor4f(1.0f,1.0f,1.0f, vecpane[ident]->vectext[0].m_alpha);

			if(vecpane[ident]->m_PaneType == 1)
				{
				// Bind the texture to which subsequent calls refer to
				glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->vectext[0].m_texlist].m_TexID );

				glBegin( GL_QUADS );

				for(size_t id=0; id < 4; id++)
					{
					//Bottom-right vertex (corner)
					glTexCoord2i(texxreversed[id*2], texxreversed[(id*2)+1]);
					glVertex2d(vecpane[ident]->vecvertex[id].m_x, vecpane[ident]->vecvertex[id].m_y);
					}

				glEnd();
				}

			if(m_mode > 0)
				{
				if(vecpane[ident]->m_PaneType == 2 || (vecpane[ident]->m_PaneType > 100 && vecpane[ident]->m_PaneType < 200))
					{
					// Bind the texture to which subsequent calls refer to
					glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->vectext[0].m_texlist].m_TexID );

					glBegin( GL_QUADS );

					for(size_t id=0; id < 4; id++)
						{
						//Bottom-right vertex (corner)
						glTexCoord2i(texxreversed[id*2], texxcoords[(id*2)+1]);
						glVertex2d(vecpane[ident]->vecvertex[id].m_x, vecpane[ident]->vecvertex[id].m_y);
						}

					glEnd();
					}

				if(vecpane[ident]->m_PaneType == 5)
					{
					// Bind the texture to which subsequent calls refer to
					glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->vectext[0].m_texlist].m_TexID );

					glBegin( GL_QUADS );

					for(size_t id=0; id < 4; id++)
						{
						//Bottom-right vertex (corner)
						glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
						glVertex2d(vecpane[ident]->vecvertex[id].m_x, vecpane[ident]->vecvertex[id].m_y);
						}

					glEnd();
					}

				for(size_t k=0; k < vecpane[ident]->veceditbox.size(); k++)
					{
					if(vecpane[ident]->veceditbox[k]->m_EditType == 1)
						{
						/// Set GL States
						if(vecpane[ident]->veceditbox[k]->m_click)
							{
							vecpane[ident]->veceditbox[k]->m_click = false;
							glColor4f(0.1f, 0.5f, 1.0f, 1.0f);
							}
						else
							{
							if(vecpane[ident]->veceditbox[k]->m_select) glColor4f(0.1f, 0.5f, 1.0f, 1.0f); //glColor4f(1.0f, 0.5f, 1.0f, 1.0f);
							else
								{
								if(vecpane[ident]->m_hover)
									{
									if(vecpane[ident]->veceditbox[k]->m_hover) vecpane[ident]->veceditbox[k]->vectext[0].m_alpha = 0.9f;
									else
										{
										if(vecpane[ident]->veceditbox[k]->vectext[0].m_alpha - 0.06 >= 0.35) vecpane[ident]->veceditbox[k]->vectext[0].m_alpha -= 0.06;
										else vecpane[ident]->veceditbox[k]->vectext[0].m_alpha = 0.35;
										}
									}
								else
									{
									if(vecpane[ident]->veceditbox[k]->vectext[0].m_alpha - 0.1 >= 0.2) vecpane[ident]->veceditbox[k]->vectext[0].m_alpha -= 0.1;
									else vecpane[ident]->veceditbox[k]->vectext[0].m_alpha = 0.2;
									}
								glColor4f(1.0f, 1.0f, 1.0f, vecpane[ident]->veceditbox[k]->vectext[0].m_alpha);
								}
							}

#pragma message("OPT:::Add a width generator to crunch")
						glEnable(GL_SCISSOR_TEST);
						glScissor(vecpane[ident]->veceditbox[k]->vecvertex[1].m_x, vecpane[ident]->veceditbox[k]->vecvertex[2].m_y, vecpane[ident]->veceditbox[k]->vecvertex[0].m_x - vecpane[ident]->veceditbox[k]->vecvertex[1].m_x, vecpane[ident]->veceditbox[k]->vecvertex[0].m_y - vecpane[ident]->veceditbox[k]->vecvertex[2].m_y);
						//glScissor(100, 100, 375, 375);

						glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

						if(vecpane[ident]->veceditbox[k]->m_Document == -1)	glBindTexture( GL_TEXTURE_2D, m_texturebank->vecGLtextures[vecpane[ident]->veceditbox[k]->m_TextureID].m_TexID );
						else glBindTexture( GL_TEXTURE_2D, vecpane[ident]->veceditbox[k]->m_TexPlate.m_TexID );

						glBegin( GL_QUADS );

#if 0
						for(size_t id=0; id < vecpane[ident]->veceditbox[k]->vecvertex.size(); id++)
							{
							glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
							glVertex2d(vecpane[ident]->veceditbox[k]->vecvertex[id].m_x, vecpane[ident]->veceditbox[k]->vecvertex[id].m_y);
							}
#endif

						glTexCoord2i(texxcoords[0*2], texxreversed[(0*2)+1]);
						glVertex2d(vecpane[ident]->veceditbox[k]->vecvertex[1].m_x + GUI_DEFAULT_EDITDX, vecpane[ident]->veceditbox[k]->vecvertex[0].m_y);

						glTexCoord2i(texxcoords[1*2], texxreversed[(1*2)+1]);
						glVertex2d(vecpane[ident]->veceditbox[k]->vecvertex[1].m_x, vecpane[ident]->veceditbox[k]->vecvertex[1].m_y);

						glTexCoord2i(texxcoords[2*2], texxreversed[(2*2)+1]);
						glVertex2d(vecpane[ident]->veceditbox[k]->vecvertex[2].m_x, vecpane[ident]->veceditbox[k]->vecvertex[2].m_y);

						glTexCoord2i(texxcoords[3*2], texxreversed[(3*2)+1]);
						glVertex2d(vecpane[ident]->veceditbox[k]->vecvertex[2].m_x + GUI_DEFAULT_EDITDX, vecpane[ident]->veceditbox[k]->vecvertex[3].m_y);

						glEnd();

						glDisable(GL_SCISSOR_TEST);
						}
					}
				}
			}/// END Pane Visible
		}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	/////// Render Text
	if(m_mode > 0)
		{
		for (int x = 0; x < vecstatictext.size(); ++x)
			{
			if(vecstatictext[x]->m_TextType == 0) commands_face->draw( vecstatictext[x]->m_posx, vecstatictext[x]->m_posy, vecstatictext[x]->m_Content );
			if(vecstatictext[x]->m_TextType == 1) login_face->draw( vecstatictext[x]->m_posx, vecstatictext[x]->m_posy, vecstatictext[x]->m_Content );
			}

		for (int x = 0; x < vecpane.size(); ++x)
			{
			if(vecpane[x]->m_visible)
				{
				for (int l = 0; l < vecpane[x]->vecstatictext.size(); ++l)
					{
					if(vecpane[x]->vecstatictext[l]->m_TextType == 0) commands_face->draw( vecpane[x]->m_posx + vecpane[x]->vecstatictext[l]->m_posx, vecpane[x]->m_posy - vecpane[x]->vecstatictext[l]->m_posy, vecpane[x]->vecstatictext[l]->m_Content );
					if(vecpane[x]->vecstatictext[l]->m_TextType == 1) login_face->draw( vecpane[x]->m_posx + vecpane[x]->vecstatictext[l]->m_posx, vecpane[x]->m_posy - vecpane[x]->vecstatictext[l]->m_posy, vecpane[x]->vecstatictext[l]->m_Content );

					OGLFT::BBox i_Box = commands_face->measure(vecpane[x]->vecstatictext[l]->m_Content);
					
					//if((i_Box.x_min_ + i_Box.x_max_) > (vecpane[x]->m_posx + vecpane[x]->ScaleX))
					//	{

						

					//	}
					}
				for (int k = 0; k < vecpane[x]->veceditbox.size(); ++k)
					{
					std::string StrCombine = vecpane[x]->veceditbox[k]->m_Static + vecpane[x]->veceditbox[k]->m_Content;
					
					//glEnable(GL_SCISSOR_TEST);
					//glScissor(vecpane[x]->veceditbox[k]->vecvertex[1].m_x, vecpane[x]->veceditbox[k]->vecvertex[2].m_y, vecpane[x]->veceditbox[k]->vecvertex[0].m_x, vecpane[x]->veceditbox[k]->vecvertex[0].m_y);
					//glScissor(100, 100, 375, 375);

					//if(vecpane[x]->veceditbox[k]->m_EditType == 0) commands_face->draw( vecpane[x]->veceditbox[k]->vecvertex[1].m_x + 2, vecpane[x]->veceditbox[k]->vecvertex[1].m_y - point_size, StrCombine.c_str() );
					//if(vecpane[x]->veceditbox[k]->m_EditType == 1) commands_face->draw( vecpane[x]->veceditbox[k]->vecvertex[1].m_x + 2, vecpane[x]->veceditbox[k]->vecvertex[1].m_y - point_size, StrCombine.c_str() );

					//printf("Trace %s\n", StrCombine.c_str());

					if(vecpane[x]->veceditbox[k]->m_EditType == 0)
						{
						//for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(0)->m_Content.size(); ++lineiter)
						//	{ commands_face->draw( vecpane[x]->veceditbox[k]->vecvertex[1].m_x + 2, (vecpane[x]->veceditbox[k]->vecvertex[1].m_y - point_size) - (lineiter * point_size), m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str() ); }

						commands_face->draw( vecpane[x]->veceditbox[k]->vecvertex[1].m_x + 2, (vecpane[x]->veceditbox[k]->vecvertex[1].m_y - point_size)/* - (8 * point_size)*/, StrCombine.c_str() );
						}

					if(vecpane[x]->veceditbox[k]->m_EditType == 1)
						{
						//for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(0)->m_Content.size(); ++lineiter)
						//	{ commands_face->draw( vecpane[x]->veceditbox[k]->vecvertex[1].m_x + 2, (vecpane[x]->veceditbox[k]->vecvertex[1].m_y - point_size) - (lineiter * point_size), m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str() ); }

						commands_face->draw( vecpane[x]->veceditbox[k]->vecvertex[1].m_x + 2, (vecpane[x]->veceditbox[k]->vecvertex[1].m_y - point_size)/* - (8 * point_size)*/, StrCombine.c_str() );
						}

					//glDisable(GL_SCISSOR_TEST);
					}
				for (int k = 0; k < vecpane[x]->vecbutton.size(); ++k)
					{
					for (int i = 0; i < vecpane[x]->vecbutton[k]->vecstatictext.size(); ++i)
						{
						if(vecpane[x]->vecbutton[k]->vecstatictext[i]->m_TextType == 0) commands_face->draw( vecpane[x]->vecbutton[k]->vecvertex[1].m_x + vecpane[x]->vecbutton[k]->vecstatictext[i]->m_posx, vecpane[x]->vecbutton[k]->vecvertex[1].m_y + vecpane[x]->vecbutton[k]->vecstatictext[i]->m_posy - point_size, vecpane[x]->vecbutton[k]->vecstatictext[i]->m_Content );
						if(vecpane[x]->vecbutton[k]->vecstatictext[i]->m_TextType == 1) commands_face->draw( vecpane[x]->vecbutton[k]->vecvertex[1].m_x + vecpane[x]->vecbutton[k]->vecstatictext[i]->m_posx, vecpane[x]->vecbutton[k]->vecvertex[1].m_y + vecpane[x]->vecbutton[k]->vecstatictext[i]->m_posy - point_size, vecpane[x]->vecbutton[k]->vecstatictext[i]->m_Content );
						}
					}
				}
			}
		}

	GLDisable2D();
}

#if 0
void unGUI::TextDraw(float i_x, float i_y, std::string i_Text)
{

	//Boundaries snap

}
#endif

void unGUI::acVidResize(unsigned int i_width, unsigned int i_height)
{
	m_VidWidth = i_width;
	m_VidHeight = i_height;

	//set_program_params(false, true);
	//create_buffer(GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY);

#if 0
	acReset();
#endif
}

void unGUI::acReset(void)
{
	size_t ident = 0, iter = 0;

	for(ident = 0; ident < m_outcnt; ident++)
		{
		vecpane[ident]->vectext.clear();
		vecpane[ident]->vecvertex.clear();

		for(iter = 0; iter < vecpane[ident]->vecbutton.size(); iter++)
			{
			vecpane[ident]->vecbutton[iter]->vecvertex.clear();
			vecpane[ident]->vecbutton[iter]->vecgizmot.clear();
			vecpane[ident]->vecbutton[iter]->vecbounds.clear();
			vecpane[ident]->vecbutton[iter]->vectext.clear();
			}

		for(iter = 0; iter < vecpane[ident]->veceditbox.size(); iter++)
			{
			vecpane[ident]->veceditbox[iter]->vecvertex.clear();
			vecpane[ident]->veceditbox[iter]->vecgizmot.clear();
			vecpane[ident]->veceditbox[iter]->vecbounds.clear();
			vecpane[ident]->veceditbox[iter]->vectext.clear();
			}
		}

	m_incnt = m_outcnt;
	m_outcnt = 0;
}

void unGUI::acResetPositions(void)
{
	size_t ident = 0, iter = 0;

	for(ident = 0; ident < m_outcnt; ident++)
		{
		vecpane[ident]->vecvertex.clear();

		for(iter = 0; iter < vecpane[ident]->vecbutton.size(); iter++)
			{
			vecpane[ident]->vecbutton[iter]->vecvertex.clear();
			vecpane[ident]->vecbutton[iter]->vecgizmot.clear();
			vecpane[ident]->vecbutton[iter]->vecbounds.clear();
			}

		for(iter = 0; iter < vecpane[ident]->veceditbox.size(); iter++)
			{
			vecpane[ident]->veceditbox[iter]->vecvertex.clear();
			vecpane[ident]->veceditbox[iter]->vecgizmot.clear();
			vecpane[ident]->veceditbox[iter]->vecbounds.clear();
			}
		}

	m_incnt = m_outcnt;
	m_outcnt = 0;
}

bool unGUI::acCrunch(void)
{
	unConsoleAttribute(CONSOLE_MSG);
	printf("unGUI Crunch\n");
	unConsoleAttribute(CONSOLE_INIT);
#if 1
	int pointer = m_outcnt;
	for(size_t ident=0; ident < m_incnt; ident++)
		{
		if(vecpane[pointer]->m_PaneType == 5)
			{
			unGL::GLvecf2 vertex(0,0);
			unGL::GLvecf2 gizmot(0,0);
			unGL::GLmaterial text(0,vecpane[pointer]->m_TextureID);

			int strendX = vecpane[pointer]->m_posx + vecpane[pointer]->ScaleX;
			int strendY = m_VidHeight - (vecpane[pointer]->m_posy + vecpane[pointer]->ScaleY);

			if(strendX > m_VidWidth || strendY > m_VidHeight) return false;

			vecpane[pointer]->vectext.push_back(text);
			vertex.set(strendX, m_VidHeight - vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, m_VidHeight - vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, strendY);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(strendX, strendY);
			vecpane[pointer]->vecvertex.push_back(vertex);

			/// Crunch Buttons
			for(size_t k=0; k < vecpane[pointer]->vecbutton.size(); k++)
				{
				text.m_texlist = 3;
				vecpane[pointer]->vecbutton[k]->vectext.push_back(text);
				for(size_t i=0; i < vecpane[pointer]->vecbutton[k]->vecgizmot.size(); ++i)
					{ vecpane[pointer]->vecbutton[k]->vecvertex.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), m_VidHeight - (vecpane[pointer]->m_posy + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)))); }
				}
			}

		if(vecpane[pointer]->m_PaneType == 4)
			{
			unGL::GLvecf2 vertex(0,0);
			unGL::GLvecf2 gizmot(0,0);
			unGL::GLmaterial text(0,vecpane[pointer]->m_TextureID);

			int strendX = vecpane[pointer]->m_posx + vecpane[pointer]->ScaleX;
			int strendY = m_VidHeight - (vecpane[pointer]->m_posy + vecpane[pointer]->ScaleY);

			if(strendX > m_VidWidth || strendY > m_VidHeight) return false;

			vecpane[pointer]->vectext.push_back(text);
			vertex.set(strendX, m_VidHeight - vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, m_VidHeight - vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, strendY);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(strendX, strendY);
			vecpane[pointer]->vecvertex.push_back(vertex);

			/// Crunch Buttons
			for(size_t k=0; k < vecpane[pointer]->vecbutton.size(); k++)
				{
				vecpane[pointer]->vecbutton[k]->vectext.push_back(text);
				for(size_t i=0; i < vecpane[pointer]->vecbutton[k]->vecgizmot.size(); ++i)
					vecpane[pointer]->vecbutton[k]->vecvertex.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), vecpane[pointer]->m_posy + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)));
				}
			}

		if(vecpane[pointer]->m_PaneType == 1 || vecpane[pointer]->m_PaneType == 2)
			{
			unGL::GLvecf2 vertex(0,0);
			unGL::GLvecf2 gizmot(0,0);
			unGL::GLmaterial text(0,vecpane[pointer]->m_TextureID);

			int strendX = vecpane[pointer]->m_posx + vecpane[pointer]->ScaleX;
			int strendY = m_VidHeight - (vecpane[pointer]->m_posy + vecpane[pointer]->ScaleY);

			if(strendX > m_VidWidth || strendY > m_VidHeight) return false;

			vecpane[pointer]->vectext.push_back(text);
			vertex.set(strendX, m_VidHeight - vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, m_VidHeight - vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, strendY);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(strendX, strendY);
			vecpane[pointer]->vecvertex.push_back(vertex);

			/// Crunch Buttons
			for(size_t k=0; k < vecpane[pointer]->vecbutton.size(); k++)
				{
				vecpane[pointer]->vecbutton[k]->vectext.push_back(unGL::GLmaterial(0,vecpane[pointer]->vecbutton[k]->m_TextureID));
				for(size_t i=0; i < vecpane[pointer]->vecbutton[k]->vecgizmot.size(); ++i)
					vecpane[pointer]->vecbutton[k]->vecvertex.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), m_VidHeight - (vecpane[pointer]->m_posy + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY))));
				}

			/// Crunch EditBoxes
			for(size_t k=0; k < vecpane[pointer]->veceditbox.size(); k++)
				{
				vecpane[pointer]->veceditbox[k]->vectext.push_back(text);
				for(size_t i=0; i < vecpane[pointer]->veceditbox[k]->vecgizmot.size(); ++i)
					{ vecpane[pointer]->veceditbox[k]->vecvertex.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->veceditbox[k]->vecgizmot[i].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), m_VidHeight - (vecpane[pointer]->m_posy + ((vecpane[pointer]->veceditbox[k]->vecgizmot[i].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)))); }
					//printf("Trace vecvertex %i x %f y %f\n", i, vecpane[pointer]->m_posx + ((vecpane[pointer]->veceditbox[k]->vecgizmot[i].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), m_VidHeight - (vecpane[pointer]->m_posy + ((vecpane[pointer]->veceditbox[k]->vecgizmot[i].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)) ); Sleep(15000); }

				if(vecpane[pointer]->veceditbox[k]->m_Document >= 0) acDocumentPlate(vecpane[pointer]->veceditbox[k], 0);
				}
			}

		if(vecpane[pointer]->m_PaneType == 10)
			{
			unGL::GLvecf2 vertex(0,0);
			unGL::GLvecf2 gizmot(0,0);
			unGL::GLmaterial text(0,vecpane[pointer]->m_TextureID);

			vecpane[pointer]->vectext.push_back(text);
			vertex.set(vecpane[pointer]->m_posx + vecpane[pointer]->ScaleX, vecpane[pointer]->m_posy - vecpane[pointer]->ScaleY);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, vecpane[pointer]->m_posy - vecpane[pointer]->ScaleY);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx, vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);
			vertex.set(vecpane[pointer]->m_posx + vecpane[pointer]->ScaleX, vecpane[pointer]->m_posy);
			vecpane[pointer]->vecvertex.push_back(vertex);

			/// Crunch Buttons
			for(size_t k=0; k < vecpane[pointer]->vecbutton.size(); k++)
				{
				vecpane[pointer]->vecbutton[k]->vectext.push_back(text);
				for(size_t i=0; i < vecpane[pointer]->vecbutton[k]->vecgizmot.size(); ++i)
					vecpane[pointer]->vecbutton[k]->vecvertex.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), vecpane[pointer]->m_posy + ((vecpane[pointer]->vecbutton[k]->vecgizmot[i].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)));
				}
			}

		/// Crunch Bounds
		if(vecpane[pointer]->m_PaneType == 2)
			{
			for(size_t i=0; i < vecpane[pointer]->vecgizmot.size(); ++i)
				vecpane[pointer]->vecbounds.push_back(vecpane[pointer]->vecgizmot[i]);

			/// Button Bounds
			for(size_t k=0; k < vecpane[pointer]->vecbutton.size(); ++k)
				for(size_t l=0; l < vecpane[pointer]->vecbutton[k]->vecgizmot.size(); ++l)
					vecpane[pointer]->vecbutton[k]->vecbounds.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->vecbutton[k]->vecgizmot[l].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), vecpane[pointer]->m_posy + ((vecpane[pointer]->vecbutton[k]->vecgizmot[l].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vecbutton[k]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)));
			}

		if(vecpane[pointer]->m_PaneType == 5)
			{
			for(size_t i=0; i < vecpane[pointer]->vecgizmot.size(); ++i)
				vecpane[pointer]->vecbounds.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->vecgizmot[i].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), vecpane[pointer]->m_posy + ((vecpane[pointer]->vecgizmot[i].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)));

			/// Button Bounds
			for(size_t k=0; k < vecpane[pointer]->vecbutton.size(); ++k)
				for(size_t l=0; l < vecpane[pointer]->vecbutton[k]->vecgizmot.size(); ++l)
					vecpane[pointer]->vecbutton[k]->vecbounds.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->vecbutton[k]->vecgizmot[l].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), vecpane[pointer]->m_posy + ((vecpane[pointer]->vecbutton[k]->vecgizmot[l].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)));
			}

		/// EditBox Bounds
		for(size_t k=0; k < vecpane[pointer]->veceditbox.size(); ++k)
			for(size_t l=0; l < vecpane[pointer]->veceditbox[k]->vecgizmot.size(); ++l)
				vecpane[pointer]->veceditbox[k]->vecbounds.push_back(unGL::GLvecf2(vecpane[pointer]->m_posx + ((vecpane[pointer]->veceditbox[k]->vecgizmot[l].m_x / m_texturebank->vecGLtextures[vecpane[pointer]->veceditbox[k]->vectext[0].m_texlist].m_width) * vecpane[pointer]->ScaleX), vecpane[pointer]->m_posy + ((vecpane[pointer]->veceditbox[k]->vecgizmot[l].m_y / m_texturebank->vecGLtextures[vecpane[pointer]->veceditbox[k]->vectext[0].m_texlist].m_height) * vecpane[pointer]->ScaleY)));

		m_outcnt++;
		pointer++;
		}

	/// Reset In Tray
	m_incnt = 0;
#endif
	return true;
}

bool unGUI::acMouseMotion(const Uint16 mx, const Uint16 my)
{
#if 1
	/// Convert Mouse Position
	float mousex = mx, mousey = my;

	int xyz = m_outcnt;

	for(int ident=0; ident < m_outcnt; ident++)
		{
		if(vecpane[ident]->m_PaneType == 5 || vecpane[ident]->m_PaneType == 4 || vecpane[ident]->m_PaneType == 2)	//Entrance
			{
			if(PntIntersect(vecpane[ident]->vecbounds, mousex, mousey))
				{
				vecpane[ident]->m_hover = true;

				for(int i=0; i < vecpane[ident]->vecbutton.size(); i++)
					{
					if(PntIntersect(vecpane[ident]->vecbutton[i]->vecbounds, mousex, mousey))
						{
						vecpane[ident]->vecbutton[i]->m_hover = true;
						}
					else vecpane[ident]->vecbutton[i]->m_hover = false;
					}
				}
			else if(m_mode != 2) vecpane[ident]->m_hover = false;
			}
		for(int i=0; i < vecpane[ident]->veceditbox.size(); i++)
			{
			if(PntIntersect(vecpane[ident]->veceditbox[i]->vecbounds, mousex, mousey))
				{
				vecpane[ident]->veceditbox[i]->m_hover = true;
				}
			else vecpane[ident]->veceditbox[i]->m_hover = false;
			}
		}
#endif
	return true;
}

unGuiResponse* unGUI::acMouseClick(void)
{
#if 1
	/// Boolean Scan
	for(int ident=0; ident < m_outcnt; ident++)
		{
		if(vecpane[ident]->m_hover)
			{
			for(int i=0; i < vecpane[ident]->vecbutton.size(); i++)
				{
				if(vecpane[ident]->vecbutton[i]->m_hover)
					{
					vecpane[ident]->vecbutton[i]->m_click = true;

					if(vecpane[ident]->vecbutton[i]->m_select) vecpane[ident]->vecbutton[i]->m_select = false;
					else vecpane[ident]->vecbutton[i]->m_select = true;

					vecpane[ident]->vecbutton[i]->m_response->m_hover = true;
					vecpane[ident]->vecbutton[i]->m_response->m_click = true;
					vecpane[ident]->vecbutton[i]->m_response->m_select = vecpane[ident]->vecbutton[i]->m_select;
					return vecpane[ident]->vecbutton[i]->m_response;
					}
				}
			for(int k=0; k < vecpane[ident]->veceditbox.size(); k++)
				{
				if(vecpane[ident]->veceditbox[k]->m_hover)
					{
					vecpane[ident]->veceditbox[k]->m_click = true;

					if(vecpane[ident]->veceditbox[k]->m_select) vecpane[ident]->veceditbox[k]->m_select = false;
					else vecpane[ident]->veceditbox[k]->m_select = true;

					acClickCancel(0, ident, k);
					}
				}
			}
		}
#endif

	return defaultResponse;
}

void unGUI::acKeyDown(char KeyPressed)
{
	/// Boolean Scan
	for(int x=0; x < vecpane.size(); x++)
		{
		for(int ident=0; ident < vecpane[x]->veceditbox.size(); ident++)
			{
			if(vecpane[x]->veceditbox[ident]->m_select)
				{
				if(KeyPressed == 8 && vecpane[x]->veceditbox[ident]->m_Content.length() > 0) vecpane[x]->veceditbox[ident]->m_Content.resize(vecpane[x]->veceditbox[ident]->m_Content.size() - 1);
				else
					{
#if 1
					//if(KeyPressed == 8)
					if(KEY_DOWN(QIN_SPACE))
						{
						vecpane[x]->veceditbox[ident]->m_Content.push_back(32);
						}
					else
						{
						if(KEY_DOWN(QIN_SHIFT)) vecpane[x]->veceditbox[ident]->m_Content.push_back(KeyPressed);
						else vecpane[x]->veceditbox[ident]->m_Content.push_back(KeyPressed + 32);
						}
#endif
					}
				}
			}
		}
}

void unGUI::acClickCancel(int Range, int PaneID, int GizID)
{
	if(Range == 0)
		{
		for(int x=0; x < vecpane.size(); x++)
			{
			for(int k=0; k < vecpane[x]->veceditbox.size(); k++)
				{
				if(!(x == PaneID && k == GizID)) vecpane[x]->veceditbox[k]->m_select = false;
				}
			}
		}
}

void unGUI::initFont(void)
{
	////// Temporary Strings
	USAGE = " fontfile";
	//commands = "a/A: char rotate X, s/S: char rotate Y, d/D: char rotate Z, f/F: string rotate, r: reset all";
	commands = "FFFF";
	text = "The quick brown fox jumps over a lazy dog.";
	point_size = 16;

	////// Text Rendering Initialisation
	std::cout << glGetString( GL_VENDOR ) << " " << glGetString( GL_RENDERER ) << " "
       << glGetString( GL_VERSION ) << std::endl;

	//commands_face = new OGLFT::Monochrome( "fonts/futena_book.ttf", point_size / 1.65 );
	commands_face = new OGLFT::Monochrome( "fonts/arial.ttf", point_size / 1.65 );
	//commands_face = new OGLFT::Monochrome( "fonts/Wormfont.ttf", point_size / 1.65 );	
	//commands_face = new OGLFT::Monochrome( "fonts/SURSONG.TTF", point_size / 1.65 );	
	commands_face->setHorizontalJustification( OGLFT::Face::LEFT );

	login_face = new OGLFT::Outline( "fonts/arial.ttf", point_size * 1. );
	login_face->setHorizontalJustification( OGLFT::Face::LEFT );

	monochrome_face = new OGLFT::Monochrome( "fonts/arial.ttf", point_size );
	monochrome_face->setHorizontalJustification( OGLFT::Face::LEFT );
	monochrome_face->setForegroundColor( 1., 0., 0., 1. );

	if ( !monochrome_face->isValid() )
		{
		std::cerr << "failed to open face. exiting." << std::endl;
		exit( 1 );
		}

	grayscale_face = new OGLFT::Grayscale( "fonts/arial.ttf", point_size );
	grayscale_face->setHorizontalJustification( OGLFT::Face::CENTER );
	grayscale_face->setForegroundColor( 0., 0., .5, 1. );
	grayscale_face->setBackgroundColor( 0., 1., 1., 1. );

	translucent_face = new OGLFT::Translucent( "fonts/arial.ttf", point_size );
	translucent_face->setHorizontalJustification( OGLFT::Face::CENTER );
	translucent_face->setForegroundColor( 0., .5, 0., 1. );

	outline_face = new OGLFT::Outline( "fonts/arial.ttf", point_size );
	outline_face->setHorizontalJustification( OGLFT::Face::CENTER );
	outline_face->setForegroundColor( 1., 1., 0., 1. );

	filled_face = new OGLFT::Filled( "fonts/arial.ttf", point_size );
	filled_face->setHorizontalJustification( OGLFT::Face::CENTER );
	filled_face->setForegroundColor( .5, 0., 1., 1. );

	#ifndef OGLFT_NO_SOLID
	solid_face = new OGLFT::Solid( "fonts/arial.ttf", point_size );
	solid_face->setDepth( 10. );
	solid_face->setCharacterRotationX( 25. );
	solid_face->setCharacterRotationY( 25. );
	solid_face->setTessellationSteps( 3 );
	#else
	solid_face = new OGLFT::Monochrome( "fonts/arial.ttf", point_size );
	#endif
	solid_face->setHorizontalJustification( OGLFT::Face::CENTER );
	solid_face->setForegroundColor( 1., .5, 0., 1. );

	monochrome_texture_face = new OGLFT::MonochromeTexture( "fonts/arial.ttf", point_size );
	monochrome_texture_face->setHorizontalJustification( OGLFT::Face::CENTER );
	monochrome_texture_face->setForegroundColor( 0., .5, .75, 1. );

	grayscale_texture_face = new OGLFT::GrayscaleTexture( "fonts/arial.ttf", point_size );
	grayscale_texture_face->setHorizontalJustification( OGLFT::Face::CENTER );
	grayscale_texture_face->setForegroundColor( 0.9, .65, .9, 1. );
	grayscale_texture_face->setBackgroundColor( 0.5, .5, .75, 0.3 );

	translucent_texture_face = new OGLFT::TranslucentTexture( "fonts/arial.ttf", point_size );
	translucent_texture_face->setHorizontalJustification( OGLFT::Face::CENTER );
	translucent_texture_face->setForegroundColor( 0.75, 1., .75, 1. );

	// Set various general parameters which don't affect performance (yet).
	glClearColor( .75, .75, .75, 1. );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	#if defined( GL_RASTER_POSITION_UNCLIPPED_IBM )
	glEnable( GL_RASTER_POSITION_UNCLIPPED_IBM );
	#endif
	//glEnable( GL_LIGHT0 );	/// CAUSES CRASH
	glDisable( GL_DITHER );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
}

void unGUI::reshape(int width, int height)
{
	viewport_width = width;
	viewport_height = height;

	glViewport( 0, 0, viewport_width, viewport_height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, viewport_width, 0, viewport_height, -100, 100 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	dy = viewport_height / ( 9 + 1 );
}

void unGUI::reset(void)
{
	monochrome_face->setCharacterRotationZ( 0 );
	monochrome_face->setStringRotation( 0 );

	grayscale_face->setCharacterRotationZ( 0 );
	grayscale_face->setStringRotation( 0 );

	translucent_face->setCharacterRotationZ( 0 );
	translucent_face->setStringRotation( 0 );

	outline_face->setCharacterRotationX( 0 );
	outline_face->setCharacterRotationY( 0 );
	outline_face->setCharacterRotationZ( 0 );
	outline_face->setStringRotation( 0 );

	filled_face->setCharacterRotationX( 0 );
	filled_face->setCharacterRotationY( 0 );
	filled_face->setCharacterRotationZ( 0 );
	filled_face->setStringRotation( 0 );

	#ifndef OGLFT_NO_SOLID
	solid_face->setCharacterRotationX( 25. );
	solid_face->setCharacterRotationY( 25. );
	#endif
	solid_face->setCharacterRotationZ( 0 );
	solid_face->setStringRotation( 0 );

	monochrome_texture_face->setCharacterRotationX( 0 );
	monochrome_texture_face->setCharacterRotationY( 0 );
	monochrome_texture_face->setCharacterRotationZ( 0 );
	monochrome_texture_face->setStringRotation( 0 );

	grayscale_texture_face->setCharacterRotationX( 0 );
	grayscale_texture_face->setCharacterRotationY( 0 );
	grayscale_texture_face->setCharacterRotationZ( 0 );
	grayscale_texture_face->setStringRotation( 0 );

	translucent_texture_face->setCharacterRotationX( 0 );
	translucent_texture_face->setCharacterRotationY( 0 );
	translucent_texture_face->setCharacterRotationZ( 0 );
	translucent_texture_face->setStringRotation( 0 );

	glViewport( 0, 0, viewport_width, viewport_height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, viewport_width, 0, viewport_height, -100, 100 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void unGUI::char_rotate_x(float dx)
{
	outline_face->setCharacterRotationX( outline_face->characterRotationX()+dx );
	filled_face->setCharacterRotationX( filled_face->characterRotationX()+dx );
	#ifndef OGLFT_NO_SOLID
	solid_face->setCharacterRotationX( solid_face->characterRotationX()+dx );
	#endif
	monochrome_texture_face->setCharacterRotationX(
					 monochrome_texture_face->characterRotationX()+dx );
	grayscale_texture_face->setCharacterRotationX(
					grayscale_texture_face->characterRotationX()+dx );
	translucent_texture_face->setCharacterRotationX(
				  translucent_texture_face->characterRotationX()+dx );
}

void unGUI::char_rotate_y(float dy)
{
	outline_face->setCharacterRotationY( outline_face->characterRotationY()+dy );
	filled_face->setCharacterRotationY( filled_face->characterRotationY()+dy );
	#ifndef OGLFT_NO_SOLID
	solid_face->setCharacterRotationY( solid_face->characterRotationY()+dy );
	#endif
	monochrome_texture_face->setCharacterRotationY(
					 monochrome_texture_face->characterRotationY()+dy );
	grayscale_texture_face->setCharacterRotationY(
					grayscale_texture_face->characterRotationY()+dy );
	translucent_texture_face->setCharacterRotationY(
				  translucent_texture_face->characterRotationY()+dy );
}

void unGUI::char_rotate_z(float dz)
{
	monochrome_face->setCharacterRotationZ( monochrome_face->characterRotationZ()+dz );
	grayscale_face->setCharacterRotationZ( grayscale_face->characterRotationZ()+dz );
	translucent_face->setCharacterRotationZ( translucent_face->characterRotationZ()+dz );

	outline_face->setCharacterRotationZ( outline_face->characterRotationZ()+dz );
	filled_face->setCharacterRotationZ( filled_face->characterRotationZ()+dz );
	solid_face->setCharacterRotationZ( solid_face->characterRotationZ()+dz );

	monochrome_texture_face->setCharacterRotationZ( monochrome_texture_face->characterRotationZ()+dz );
	grayscale_texture_face->setCharacterRotationZ( grayscale_texture_face->characterRotationZ()+dz );
	translucent_texture_face->setCharacterRotationZ( translucent_texture_face->characterRotationZ()+dz );
}

void unGUI::string_rotate(float dz)
{
	monochrome_face->setStringRotation( monochrome_face->stringRotation()+dz );
	grayscale_face->setStringRotation( grayscale_face->stringRotation()+dz );
	translucent_face->setStringRotation( translucent_face->stringRotation()+dz );

	outline_face->setStringRotation( outline_face->stringRotation()+dz );
	filled_face->setStringRotation( filled_face->stringRotation()+dz );
	solid_face->setStringRotation( solid_face->stringRotation()+dz );

	monochrome_texture_face->setStringRotation( monochrome_texture_face->stringRotation()+dz );
	grayscale_texture_face->setStringRotation( grayscale_texture_face->stringRotation()+dz );
	translucent_texture_face->setStringRotation( translucent_texture_face->stringRotation()+dz );
}

void unGUI::textrender(void)
{
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glPushMatrix();

	// Draw everything centered
	//glTranslatef( 150, 50, 0 );

	//glTranslatef( 0, 0, 0 );

	/*glTranslatef( 0., dy, 0. );
	monochrome_face->draw( 0., 0., text );

	glTranslatef( 0., dy, 0. );
	grayscale_face->draw( 0., 0., text );

	glEnable( GL_BLEND );
	glTranslatef( 0., dy, 0. );
	translucent_face->draw( 0., 0., text );
	glDisable( GL_BLEND );

	glTranslatef( 0., dy, 0. );
	outline_face->draw( 0., 0., text );

	glTranslatef( 0., dy, 0. );
	filled_face->draw( 0., 0., text );

	glTranslatef( 0., dy, 0. );
	#ifndef OGLFT_NO_SOLID
	glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_COLOR_MATERIAL );
	solid_face->draw( 0., 0., text );
	glDisable( GL_COLOR_MATERIAL );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );
	#else
	solid_face->draw( 0., 0., "<Note: Solid face not available in library>" );
	#endif

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );
	glTranslatef( 0., dy, 0. );
	monochrome_texture_face->draw( 0., 0., text );

	glTranslatef( 0., dy, 0. );
	grayscale_texture_face->draw( 0., 0., text );

	glTranslatef( 0., dy, 0. );
	translucent_texture_face->draw( 0., 0., text );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );

	glPopMatrix();*/
	//glutSwapBuffers();
}

void unGUI::acDocumentPlate(unEditBox* i_EditBox, UInt32 i_Address)
{
#if 1
	buffer_bind_render();	// bind diffuse mrt texture

	//glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(i_EditBox->m_Document)->m_Content.size(); ++lineiter)
	//	{ commands_face->draw( i_EditBox->vecvertex[1].m_x + 2, (i_EditBox->vecvertex[1].m_y - point_size) - (lineiter * point_size), m_DocumentBank->getDocument(i_EditBox->m_Document)->m_Content[lineiter].c_str() ); }

	//for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(i_EditBox->m_Document)->m_Content.size(); ++lineiter)
	//	{ commands_face->draw( i_EditBox->vecvertex[1].m_x + 2, (i_EditBox->vecvertex[1].m_y - point_size) - (lineiter * point_size), m_DocumentBank->getDocument(i_EditBox->m_Document)->m_Content[lineiter].c_str() ); }

	//GLEnable2D();
	//glEnable( GL_TEXTURE_2D );
	//glDisable(GL_DEPTH_TEST);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	//glColor4f(1.0f, 1.0f, 1.0f, 0.80f);

	for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(0)->m_Content.size(); ++lineiter)
		{ commands_face->draw( 0, m_sizey - (lineiter * point_size), m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str() ); }

	//commands_face->setForegroundColor ( 1, 0, 0, 1 );
	//commands_face->draw( 0, 0, i_line );
	//commands_face->setForegroundColor ( 0, 0, 0, 1 );

#if 1
	glGenTextures(1, &i_EditBox->m_TexPlate.m_TexID);
	glBindTexture(GL_TEXTURE_2D, i_EditBox->m_TexPlate.m_TexID);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY, 0);
	//glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY);
#endif

#if 0
	Cleanup();
	m_nType = (nHeight == 1) ? GL_TEXTURE_1D : GL_TEXTURE_2D;
	glGenTextures(1, &i_EditBox->m_TexPlate.m_TexID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, bClamp ? GL_CLAMP : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, bClamp ? GL_CLAMP : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if(m_nType == GL_TEXTURE_1D)
		glCopyTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, x, y, nWidth, 0);
	else
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, nWidth, nHeight, 0);
#endif

	buffer_unbind_render();

#if 0
	unsigned int* data;											// Stored Data
	data = (unsigned int*)new GLuint[((GUI_DEFAULT_EDITDX * GUI_DEFAULT_EDITDY)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((GUI_DEFAULT_EDITDX * GUI_DEFAULT_EDITDY)* 4 * sizeof(unsigned int)));	// Clear Storage Memory
	//FillMemory(data,((GUI_DEFAULT_EDITDX * GUI_DEFAULT_EDITDY)* 4 * sizeof(unsigned int)), 0.5);	// Clear Storage Memory
	glGenTextures(1, &i_EditBox->m_TexPlate.m_TexID);
	glBindTexture(GL_TEXTURE_2D, i_EditBox->m_TexPlate.m_TexID);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	delete [] data;
#endif

	if(GUI_MIPMAP)
		{
#if 0
		gluBuild2DMipmaps(GL_TEXTURE_2D, picture->bytespixel, picture->sx, picture->sy, GL_RGBA, GL_UNSIGNED_BYTE, picture->buf);
		glTexParameteri(type,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
#endif
		}
	else
		{	//No MipMap Texture
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}

	int x=0;
	int y=0;

#if 0
#if 0
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.80f);
#endif

	// draw all mrt textures at top of screen
	buffer_bind_texture(0);
	draw_rect(x, g_render->sizey - GUI_DEFAULT_EDITDY, m_sizex, GUI_DEFAULT_EDITDY, false, false);
	buffer_bind_texture(0);
#endif
#endif
}

void unGUI::acPush(const char* i_line)
{
#if 0
	//commands_face->draw( vecpane[x]->m_posx + vecpane[x]->vecstatictext[l]->m_posx, vecpane[x]->m_posy - vecpane[x]->vecstatictext[l]->m_posy, i_line );
	//OGLFT::BBox i_Box = commands_face->measure(vecpane[x]->vecstatictext[l]->m_Content);

	buffer_bind_render();	// bind diffuse mrt texture

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	//glOrtho(0, m_sizex, 0, m_sizey, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(0)->m_Content.size(); ++lineiter)
		{
		commands_face->draw( 0, m_sizey - (lineiter * point_size), m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str() );
		printf("%i ::: %s\n", lineiter, m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str());
		}

	//commands_face->setForegroundColor ( 1, 0, 0, 1 );
	//commands_face->draw( 0, 0, i_line );
	//commands_face->setForegroundColor ( 0, 0, 0, 1 );

	buffer_unbind_render();

	/*GLuint textureplate;
	glGenTextures(1, &textureplate);
	glBindTexture(GL_TEXTURE_2D, textureplate);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY, 0);

	if(GUI_MIPMAP)
		{
#if 0
		gluBuild2DMipmaps(GL_TEXTURE_2D, picture->bytespixel, picture->sx, picture->sy, GL_RGBA, GL_UNSIGNED_BYTE, picture->buf);
		glTexParameteri(type,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
#endif
		}
	else
		{	//No MipMap Texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}*/
#endif

#if 0
	//commands_face->draw( vecpane[x]->m_posx + vecpane[x]->vecstatictext[l]->m_posx, vecpane[x]->m_posy - vecpane[x]->vecstatictext[l]->m_posy, i_line );
	//OGLFT::BBox i_Box = commands_face->measure(vecpane[x]->vecstatictext[l]->m_Content);

	buffer_bind_render();	// bind diffuse mrt texture
	//buffer_bind_texture(0);
	//draw_rect(0,0,m_sizex,m_sizey,false,false);
	//glClearColor( 0.15, 0.25, 0.75, 1.0 );
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glBindTexture(GL_TEXTURE_2D, Media->QAEFF00);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	//glOrtho(0, m_sizex, 0, m_sizey, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(0)->m_Content.size(); ++lineiter)
		{ commands_face->draw( 0, m_sizey - (lineiter * point_size), m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str() );
		printf("%i ::: %s\n", lineiter, m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str()); }

	//commands_face->setForegroundColor ( 1, 0, 0, 1 );
	//commands_face->draw( 0, 0, i_line );
	//commands_face->setForegroundColor ( 0, 0, 0, 1 );

	buffer_unbind_render();
#endif
}

void unGUI::draw_debug(void)
{
	int x=0;
	int y=0;

#if 0
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
#endif

#if 0
	glDepthMask(false);
	glColorMask(true,true,true,true);
#endif

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.80f);

	// draw all mrt textures at top of screen
	buffer_bind_texture(0);
	draw_rect(x, g_render->sizey - GUI_DEFAULT_EDITDY, m_sizex, GUI_DEFAULT_EDITDY, false, false);
	buffer_bind_texture(0);
}

void unGUI::draw_debug_plate(void)
{
	int x=0;
	int y=0;

#if 0
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
#endif

#if 0
	glDepthMask(false);
	glColorMask(true,true,true,true);
#endif

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.80f);

	glBindTexture( GL_TEXTURE_2D, vecpane[4]->veceditbox[0]->m_TexPlate.m_TexID );

	// draw all mrt textures at top of screen
	buffer_bind_texture(0);
	draw_rect(x, g_render->sizey - GUI_DEFAULT_EDITDY, m_sizex, GUI_DEFAULT_EDITDY, false, false);
	buffer_bind_texture(0);
}

void unGUI::draw_rect(int x,int y,int sx,int sy,bool vpos,bool flipy)
{
	if (vpos)
	{
		pVector f[4];
		double d[3];
		int pixels[4][2]={ { 0,0 },{0,sy},{sx,sy},{sx,0} };
		int viewport[4]={ 0,0,sx,sy };

		pMatrix view_rot=g_render->view_matrix;
		view_rot.set_translate(0);
		for( int i=0;i<4;i++ )
		{
			gluUnProject(
				pixels[i][0],pixels[i][1],10,
				g_render->cam_model_mat,g_render->cam_proj_mat,
				viewport,&d[0],&d[1],&d[2]);
			f[i].vec((float)d[0],(float)d[1],(float)d[2]);
			f[i]-=g_render->camera.pos;
			f[i].normalize();
			f[i]=f[i]*view_rot;
		}

		glBegin(GL_QUADS);
			glMultiTexCoord2f(GL_TEXTURE0_ARB,0,0);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[0].x);
			glVertex2i(x,y);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,0,1);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[1].x);
			glVertex2i(x,y+sy);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,1,1);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[2].x);
			glVertex2i(x+sx,y+sy);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,1,0);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[3].x);
			glVertex2i(x+sx,y);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,0,0);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[0].x);
			glVertex2i(x,y);
		glEnd();
	}
	else
	if (flipy)
	{
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex2i(x,y);

			glTexCoord2f(0,0);
			glVertex2i(x,y+sy);

			glTexCoord2f(1,0);
			glVertex2i(x+sx,y+sy);

			glTexCoord2f(1,1);
			glVertex2i(x+sx,y);

			glTexCoord2f(0,1);
			glVertex2i(x,y);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex2i(x,y);

			glTexCoord2f(0,1);
			glVertex2i(x,y+sy);

			glTexCoord2f(1,1);
			glVertex2i(x+sx,y+sy);

			glTexCoord2f(1,0);
			glVertex2i(x+sx,y);

			glTexCoord2f(0,0);
			glVertex2i(x,y);
		glEnd();
	}
}

void unGUI::create_buffer(int sx,int sy)
{
	gl_buffers[0]=GL_FRONT_LEFT;

#if 0
	gl_buffers[1]=GL_AUX0;
	gl_buffers[2]=GL_AUX1;
	gl_buffers[3]=GL_AUX2;
#endif
	
    wgl_buffers[0]=WGL_FRONT_LEFT_ARB;

#if 0
    wgl_buffers[1]=WGL_AUX0_ARB;
    wgl_buffers[2]=WGL_AUX1_ARB;
	wgl_buffers[3]=m_nv_render_depth_texture?WGL_DEPTH_COMPONENT_NV:WGL_AUX2_ARB;
#endif

	m_sizex=sx;
	m_sizey=sy;

	m_pbuffer=new pPBuffer(m_sizex, m_sizey, 32, true, true, false, true, true, false, false, true, 1);

	glGenTextures(1,m_tex);

	glBindTexture(GL_TEXTURE_2D,m_tex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_sizex, m_sizey, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D,0);

	buffer_bind_render();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	initFont();

	buffer_unbind_render();
}

void unGUI::destroy_buffer()
{
	glDeleteTextures(1,m_tex);
	m_tex[0]=0;

	delete m_pbuffer;
	m_pbuffer=0;
}

void unGUI::set_program_params(bool depth_bias,bool nv_render_depth_texture)
{
	m_depth_bias=depth_bias;
	m_nv_render_depth_texture=(nv_render_depth_texture&&WGLEW_NV_render_depth_texture);
}

bool unGUI::load_programs()
{
	if (g_render == 0)
		return false;

	free_programs();

	unConsoleAttribute(CONSOLE_ERROR);

	int i=0;
	char *m_vert_options[8];
	m_vert_options[0]="-posinv";
	m_vert_options[1]=0;
	char *m_frag_options[8];
	if (m_nv_render_depth_texture)
		m_frag_options[i++]="-DNV_RENDER_DEPTH_TEXTURE";
	if (m_depth_bias)
		m_frag_options[i++]="-DDEPTH_BIAS";
	m_frag_options[i]=0;

	bool ret=false;
	int count=0;
	pString str;
	str.format("%s%s..\\shaders\\Cg\\cg_relief_map_ds.cg",
		(const char *)g_render->app_path,
		(const char *)g_render->shader_path);
	char *programtext=LoadTextFile(str);

	if(programtext)
		{
		m_vert_prog = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBVP1,
				"view_space",
				(const char **)m_vert_options);
		if(m_vert_prog) count++;

		checkError("view_space", "cgCreateProgram");

		vertexProfile = //*cgGLGetLatestProfile(CG_GL_VERTEX);
		//*cgGLSetOptimalOptions(vertexProfile);
		checkError("Get Profile", "selecting vertex profile");

		vertterrainProfile = //*cgGLGetLatestProfile(CG_GL_VERTEX);
		//*cgGLSetOptimalOptions(vertterrainProfile);
		checkError("Get Profile", "selecting vertex profile");

		m_vert_mesh = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				vertexProfile,
				"view_mesh",
				0);

		checkError("view_mesh", "cgCreateProgram");

		m_vert_terrain = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				vertterrainProfile,
				"view_terrain",
				0);

		checkError("view_terrain", "cgCreateProgram");

		m_frag_prog_normal = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal",
				(const char **)m_frag_options);
		if(m_frag_prog_normal) count++;

		checkError("mrt_normal", "cgCreateProgram");

		m_frag_mesh = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal_mesh",
				(const char **)m_frag_options);

		checkError("mrt_normal_mesh", "cgCreateProgram");

		m_frag_terrain = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal_terrain",
				(const char **)m_frag_options);

		checkError("mrt_normal_terrain", "cgCreateProgram");

		m_frag_prog_relief = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_relief",
				(const char **)m_frag_options);
		if(m_frag_prog_relief) count++;

		checkError("mrt_relief_relaxed", "cgCreateProgram");

		m_frag_prog_light = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_light",
				(const char **)m_frag_options);
		if(m_frag_prog_light) count++;

		checkError("mrt_light", "cgCreateProgram");

		m_frag_prog_blur = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"blur",
				0);
		if (m_frag_prog_blur) count++;

		checkError("blur", "cgCreateProgram");

		m_frag_prog_antialias = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"anti_alias",
				0);
		if(m_frag_prog_antialias) count++;

		checkError("anti_alias", "cgCreateProgram");

		ret=(count==6);

		if(ret)
			{
			//*cgGLLoadProgram(m_vert_prog);
			CgCheckError();

			//*cgGLLoadProgram(m_vert_mesh);
			CgCheckError();

			//*cgGLLoadProgram(m_vert_terrain);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_normal);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_mesh);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_terrain);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_relief);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_light);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_blur);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_antialias);
			CgCheckError();

			m_vtile=cgGetNamedParameter(m_vert_prog,"tile");
			m_vdepth=cgGetNamedParameter(m_vert_prog,"depth");

			m_meshtile=cgGetNamedParameter(m_vert_mesh,"tile");
			m_meshdepth=cgGetNamedParameter(m_vert_mesh,"depth");
			m_meshrotationMatrices=cgGetNamedParameter(m_vert_mesh,"rotationMatrices");

			m_terraintile=cgGetNamedParameter(m_vert_terrain,"tile");
			m_terraindepth=cgGetNamedParameter(m_vert_terrain,"depth");
			m_terrainrotationMatrices=cgGetNamedParameter(m_vert_terrain,"rotationMatrices");

			m_meshcolormap=cgGetNamedParameter(m_frag_mesh,"colortex");
			m_meshAmbient=cgGetNamedParameter(m_frag_mesh,"i_Ambient");
			m_meshDiffuse=cgGetNamedParameter(m_frag_mesh,"i_Diffuse");
			m_meshSpecular=cgGetNamedParameter(m_frag_mesh,"i_Specular");
			m_meshLightVec=cgGetNamedParameter(m_frag_mesh,"i_LightVec");
			m_meshEyeVec=cgGetNamedParameter(m_frag_mesh,"i_EyeVec");
			m_meshAlpha=cgGetNamedParameter(m_frag_mesh,"i_Alpha");

			m_terraincolormap=cgGetNamedParameter(m_frag_terrain,"colortex");
			m_terrainAmbient=cgGetNamedParameter(m_frag_terrain,"i_Ambient");
			m_terrainDiffuse=cgGetNamedParameter(m_frag_terrain,"i_Diffuse");
			m_terrainSpecular=cgGetNamedParameter(m_frag_terrain,"i_Specular");
			m_terrainLightVec=cgGetNamedParameter(m_frag_terrain,"i_LightVec");
			m_terrainEyeVec=cgGetNamedParameter(m_frag_terrain,"i_EyeVec");
			m_terrainAlpha=cgGetNamedParameter(m_frag_terrain,"i_Alpha");

			if(!m_meshtile) printf("ERROR:::LoadPrograms tile parameter not found\n");
			if(!m_meshdepth) printf("ERROR:::LoadPrograms depth parameter not found\n");
			if(!m_meshrotationMatrices) printf("ERROR:::LoadPrograms rotationMatrices parameter not found\n");

			if(!m_meshcolormap) printf("ERROR:::LoadPrograms m_meshcolormap parameter not found\n");
			if(!m_meshAmbient) printf("ERROR:::LoadPrograms m_meshAmbient parameter not found\n");
			if(!m_meshDiffuse) printf("ERROR:::LoadPrograms m_meshDiffuse parameter not found\n");
			if(!m_meshSpecular) printf("ERROR:::LoadPrograms m_meshSpecular parameter not found\n");
			if(!m_meshLightVec) printf("ERROR:::LoadPrograms m_meshLightVec parameter not found\n");
			if(!m_meshEyeVec) printf("ERROR:::LoadPrograms m_meshEyeVec parameter not found\n");
			if(!m_meshAlpha) printf("ERROR:::LoadPrograms m_meshAlpha parameter not found\n");

			if(!m_terraincolormap) printf("ERROR:::LoadPrograms m_terraincolormap parameter not found\n");
			if(!m_terrainAmbient) printf("ERROR:::LoadPrograms m_terrainAmbient parameter not found\n");
			if(!m_terrainDiffuse) printf("ERROR:::LoadPrograms m_terrainDiffuse parameter not found\n");
			if(!m_terrainSpecular) printf("ERROR:::LoadPrograms m_terrainSpecular parameter not found\n");
			if(!m_terrainLightVec) printf("ERROR:::LoadPrograms m_terrainLightVec parameter not found\n");
			if(!m_terrainEyeVec) printf("ERROR:::LoadPrograms m_terrainEyeVec parameter not found\n");
			if(!m_terrainAlpha) printf("ERROR:::LoadPrograms m_terrainAlpha parameter not found\n");

			if(!m_terraintile) printf("ERROR:::LoadPrograms tile parameter not found\n");
			if(!m_terraindepth) printf("ERROR:::LoadPrograms depth parameter not found\n");
			if(!m_terrainrotationMatrices) printf("ERROR:::LoadPrograms rotationMatrices parameter not found\n");

			m_ndiffuse=cgGetNamedParameter(m_frag_prog_normal,"diffuse");
			m_nspecular=cgGetNamedParameter(m_frag_prog_normal,"specular");
			m_nplanes=cgGetNamedParameter(m_frag_prog_normal,"planes");
			m_rdiffuse=cgGetNamedParameter(m_frag_prog_relief,"diffuse");
			m_rspecular=cgGetNamedParameter(m_frag_prog_relief,"specular");
			m_rplanes=cgGetNamedParameter(m_frag_prog_relief,"planes");
			m_stepmap=cgGetNamedParameter(m_frag_prog_relief,"stepmap");
			m_lplanes=cgGetNamedParameter(m_frag_prog_light,"planes");
			m_lpos=cgGetNamedParameter(m_frag_prog_light,"lightpos");
			m_lcolor=cgGetNamedParameter(m_frag_prog_light,"lightcolor");
			m_bdisp=cgGetNamedParameter(m_frag_prog_blur,"disp");
			m_apixelsize=cgGetNamedParameter(m_frag_prog_antialias,"pixel_size");
			m_aweight=cgGetNamedParameter(m_frag_prog_antialias,"weight");

			CgCheckError();
			}

		delete programtext;
		}

	if (ret==false)
		free_programs();

	int tex;
	tex=g_render->build_onepixelmap(255,255,255);
	m_null_color=g_render->picid[tex];
	tex=g_render->build_onepixelmap(128,128,255);
	m_null_normal=g_render->picid[tex];

	unConsoleReset();

	///// Reflective Shadow Mapping /////
#if 0
	m_RSM = new RSM();
#endif

#if 0
	///// Active Framework /////
	QActiveFrameWork = new QAGE::QActiveFramewrk;
	QActiveFrameWork->acActiveInit();

	unSlowDating = new UN::unMessageCore();

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	DigiMass = new Digi::DigiMassCore();
	DigiMass->acInit(DIGI_ERROR_PRINT);

	i_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	i_trrCell->acLoad(0, 0, "Data/Terrain/foundation.trr");

	i_TrrBank = new unTrrBank();
	i_TrrBank->m_TerrainCell.push_back(i_trrCell);
	//i_TrrBank->acAddInstance(0, 0, -340, 0);

	//for(int i = 0; i < 500; i++) Digi::CreateCube(PxVec3(((rand()%50)-25), ((rand()%50)-25), ((rand()%50)-25)),1);
	for(int i = 0; i < 500; i++) DigiMass->acCreateCube(PxVec3(((rand()%50)-25), 75, ((rand()%50)-25)),1);

	// Test Engine Dynamic Shapes
	i_ShapeBank = new UN::unShapeBank();
	i_ShapeBank->acCreateShape(UN_SHAPE_CUBE, 50);
	i_ShapeBank->acAddInstance(0, 0, -340, 0);

	i_shape = new UN::unShape(UN_SHAPE_CUBE, 109, 10);
#endif

	return ret;
}

void unGUI::bind_vertex()
{
	//*cgGLBindProgram(m_vert_prog);
	//*cgGLEnableProfile(CG_PROFILE_ARBVP1);
}

void unGUI::unbind_vertex()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBVP1);
}

void unGUI::bind_mesh_vertex()
{
	//*cgGLBindProgram(m_vert_mesh);
	//*cgGLEnableProfile(vertexProfile);
}

void unGUI::unbind_mesh_vertex()
{
	//*cgGLDisableProfile(vertexProfile);
}

void unGUI::bind_terrain_vertex()
{
	//*cgGLBindProgram(m_vert_terrain);
	//*cgGLEnableProfile(vertterrainProfile);
}

void unGUI::unbind_terrain_vertex()
{
	//*cgGLDisableProfile(vertterrainProfile);
}

void unGUI::bind_normal()
{
	//*cgGLBindProgram(m_frag_prog_normal);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::unbind_normal()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unGUI::bind_mesh_normal()
{
	//*cgGLBindProgram(m_frag_prog_normal);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::unbind_mesh_normal()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unGUI::bind_relief()
{
	//*cgGLBindProgram(m_frag_prog_relief);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::unbind_relief()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unGUI::bind_mesh_relief()
{
	//*cgGLBindProgram(m_frag_prog_relief);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::unbind_mesh_relief()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unGUI::bind_light()
{
	//*cgGLBindProgram(m_frag_prog_light);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::unbind_light()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::unbind_blur()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::bind_antialias()
{
	//*cgGLBindProgram(m_frag_prog_antialias);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::unbind_antialias()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
}

void unGUI::set_normal_params(const pVector& diffuse,const pVector& specular,float tile,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_nspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unGUI::set_normal_params_mesh(const float& diffuse,const float& specular,float tile,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse);
	//*cgGLSetParameter4fv(m_nspecular,&specular);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unGUI::set_relief_params(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_rspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);
	//*cgGLSetParameter1f(m_vdepth,depth);

	////*cgGLSetTextureParameter(m_stepmap, stepmap.m_TexID);
	//cgSetSamplerState(m_stepmap);

	//*cgGLSetParameter2f(m_rplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unGUI::set_relief_params_mesh(const float& diffuse,const float& specular,float tile,float depth,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse,&diffuse);
	//*cgGLSetParameter4fv(m_rspecular,&specular);
	//*cgGLSetParameter1f(m_vtile,tile);
	//*cgGLSetParameter1f(m_vdepth,depth);

	////*cgGLSetTextureParameter(m_stepmap, stepmap.m_TexID);
	//cgSetSamplerState(m_stepmap);

	//*cgGLSetParameter2f(m_rplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unGUI::set_light_params(const pVector& lightpos,const pVector& lightcolor)
{
	//*cgGLSetParameter4fv(m_lpos,&lightpos.x);
	//*cgGLSetParameter3fv(m_lcolor,&lightcolor.x);

	//*cgGLSetParameter2f(m_lplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));
}

void unGUI::buffer_bind_render()
{
	if (m_pbuffer)
		{
		m_pbuffer->Bind();
		glDrawBuffersATI(1, gl_buffers);
		}
}

void unGUI::buffer_unbind_render()
{
	if (m_pbuffer) m_pbuffer->Unbind();
}

void unGUI::buffer_bind_texture(int target)
{
	if (m_pbuffer)
		{
		if (target>=0)
			{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_tex[target]);
			m_pbuffer->BindAsTexture(wgl_buffers[target]);
			glEnable(GL_TEXTURE_2D);
			}
		else
			{
			glActiveTextureARB(GL_TEXTURE3_ARB);
			glBindTexture(GL_TEXTURE_2D,m_tex[0]);
			m_pbuffer->BindAsTexture(wgl_buffers[0]);
			}
		}
}

void unGUI::buffer_unbind_texture(int target)
{
	if (m_pbuffer)
		{
		if (target>=0)
			{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			m_pbuffer->ReleaseTexture(wgl_buffers[target]);
			glBindTexture(GL_TEXTURE_2D,0);
			glDisable(GL_TEXTURE_2D);
			}
		else
			{
			glActiveTextureARB(GL_TEXTURE3_ARB);
			m_pbuffer->ReleaseTexture(wgl_buffers[0]);
			glBindTexture(GL_TEXTURE_2D,0);
			}
		}
}

void unGUI::free_programs()
{
	if (m_vert_prog)
		cgDestroyProgram(m_vert_prog);
	m_vert_prog=0;

	if (m_vert_mesh)
		cgDestroyProgram(m_vert_mesh);
	m_vert_mesh=0;

	if (m_frag_prog_normal)
		cgDestroyProgram(m_frag_prog_normal);
	m_frag_prog_normal=0;

	if (m_frag_mesh)
		cgDestroyProgram(m_frag_mesh);
	m_frag_mesh=0;

	if (m_frag_prog_relief)
		cgDestroyProgram(m_frag_prog_relief);
	m_frag_prog_relief=0;

	if (m_frag_prog_light)
		cgDestroyProgram(m_frag_prog_light);
	m_frag_prog_light=0;

	if (m_frag_prog_antialias)
		cgDestroyProgram(m_frag_prog_antialias);
	m_frag_prog_antialias=0;
}

void unGUI::checkError(const char *name, const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);
  
	if (error != CG_NO_ERROR)
		{
		if (error == CG_COMPILER_ERROR)
			{
			std::string errorstr;
			errorstr += cgGetLastListing(g_render->cgcontext);
#if 0
			MessageBox (0, errorstr.c_str(), "CG Compile ERROR", MB_OK);
#endif
			printf("CG:::Compile Error:::%s:::%s:::\n %s\n", name, situation, errorstr.c_str());
			for(;;) {};
			}
		else
			{
#if 0
			MessageBox (0, "General Fault", "CG ERROR", MB_OK);
#endif
			printf("CG:::General Execution Error\n");
			}
		}
}

GLuint unGUI::CreateEmptyTexture(int i_x, int i_y)
{
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((i_x * i_y)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((i_x * i_y)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, i_x, i_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}