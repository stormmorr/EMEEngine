/*

	unVis
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unVis__
#define __unVis__
 
#include "SDL.h"

/**
Video singleton class
Wraps SDL visual interface
*/
class unVis
{
public:
  
  unVis();

  ~unVis();

  /// call to initialize video
  void init(unsigned w, unsigned h, bool fullscreen);
  /// call to shutdown video
  void close();

  /// window width
  unsigned width() const      {return m_width;}
  /// window height
  unsigned height() const     {return m_height;}

  /// is a redraw requested?
  bool needsRedraw() const    {return m_redraw;}
  /// request a redraw!
  void requestRedraw()        {m_redraw = true;}

  //void setSceneData (nvsg::SceneHandle *sceneHdl, nvsg::ViewStateHandle* viewStateHdl);

  /// re-render scene and update display
  void update();

  /// add texture render area
  //TextureBufferRA *addTextureRA (nvsg::unsigned int *&outTex);

  /// singleton Video instance
  static unVis* instance();

  SDL_Surface* screen;

private:

  unsigned m_width;
  unsigned m_height;
  //std::vector<TextureBufferRA *> v_texturesRA;
  bool m_redraw;

  static unVis* s_instance;
};

#endif