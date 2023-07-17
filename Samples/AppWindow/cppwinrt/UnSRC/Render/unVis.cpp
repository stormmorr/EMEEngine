/*

	unVis
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "unVis.h"
#include <string>
#include <cassert>
#include <iostream>

using std::string;

unVis* unVis::s_instance = 0;
unVis* unVis::instance()
{
  return s_instance;
}

unVis::unVis() :
m_width(0),
m_height(0),
m_redraw(true)
{
  assert(s_instance == 0);
  s_instance = this;
}

unVis::~unVis()
{
  s_instance = 0;
}

void unVis::init(unsigned w, unsigned h, bool fullscreen)
{
#if 0
  std::cout << "Creating SDL OpenGL window" << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw string("Unable to init SDL: ")+SDL_GetError();
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  //*Uint32 flags = SDL_OPENGL;
  //*if (fullscreen)
  //*  flags |= SDL_FULLSCREEN;

  //*screen = SDL_SetVideoMode(w,h,0,flags);
  //*if (screen == 0)
  //*{
  //*  throw string("Unable to set video mode: ")+SDL_GetError();
  //*}

  m_width = screen->w;
  m_height = screen->h;

  std::cout << "  done (width=" << m_width << " height=" << m_height << ")" << std::endl;
#endif
  //*SDL_WM_SetCaption("Unification", 0);
}

#if 0
TextureBufferRA *unVis::addTextureRA (nvsg::unsigned int *&outTex)
{
  TextureBufferRA* texRA = new TextureBufferRA (width (), height ());
  m_renderArea->makeCurrent ();
  texRA->init (m_renderArea);

  outTex = texRA->getTextureAttributeItem ();
  v_texturesRA.push_back (texRA);
  return texRA;
}
#endif

void unVis::close()
{
  std::cout << "Closing SDL OpenGL window" << std::endl;

#if 0
  for (size_t i = 0; i < v_texturesRA.size (); i++)
  {
    v_texturesRA[i]->destroy ();
    delete v_texturesRA[i];
  }
  v_texturesRA.clear ();
#endif

  //SDL_Quit();

  m_width = 0;
  m_height = 0;
}

#if 0
void unVis::setSceneData (nvsg::SceneHandle *sceneHdl, nvsg::ViewStateHandle* viewStateHdl)
{
  m_renderArea->setSceneData (sceneHdl, viewStateHdl);
}
#endif

void unVis::update()
{
	//*SDL_GL_SwapBuffers();

#if 0
  if (m_redraw)
  {
    m_renderArea->renderScene();
    for (size_t i = 0; i < v_texturesRA.size (); i++)
    {
      v_texturesRA[i]->renderScene ();
    }
    m_redraw = false;
  }
#endif
}