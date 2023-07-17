#ifndef P_PARALELO3D_H
#define P_PARALELO3D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(WIN32)
#pragma warning(disable:4786)
#include <windows.h>
#endif

#define GLEW_STATIC
#include "Holding/glew.h"

#if defined(WIN32)
#include "Holding/wglew.h"
#endif

#ifdef UNIFICATION
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#endif

#include "pDefines.h"

#if defined(WIN32)
#include "SDL_keycode.h"
#endif

#ifdef P_NETWORK
//#include "../sdl/sdl_net.h"
#endif

#ifdef P_SOUND
#include "../openal/al.h"
#include "../openal/alut.h"
#endif

#if defined(WIN32)
#if 0 // P_SUPPORT_CG
//#include <Cg/cg.h>
//#include <Cg///*cgGL.h>
P3D_API int CgCheckError(void);
#endif
#endif

P3D_API char *LoadTextFile(const char *file);

#define P3D_FILEID				0x9171
#define P3D_FILEVER				0x0002

#define P_MAX_THREADS 2

#define P_RENDERMODE_TRANSP				(1<<0)
#define P_RENDERMODE_AMBIENT			(1<<1)
#define P_RENDERMODE_SHADOWS			(1<<2)
#define P_RENDERMODE_GLOW				(1<<3)
#define P_RENDERMODE_PASS				(1<<4)

#define P_RENDERFLAG_NORMAL					(1<<0)
#define P_RENDERFLAG_TEXTURE				(1<<1)
#define P_RENDERFLAG_TEXTURE2				(1<<2)
#define P_RENDERFLAG_TANGENT				(1<<3)
#define P_RENDERFLAG_CURVATURE				(1<<4)

#define P_RENDERCAPS_MULTI_PASS			(1<<0)
#define P_RENDERCAPS_SHADOWS			(1<<1)
#define P_RENDERCAPS_VERTEX_LIGHTING	(1<<2)
#define P_RENDERCAPS_PIXEL_LIGHTING		(1<<3)

#define P_LOG_ELAPSED_TIME_STEP	(1<<0)
#define P_LOG_LAST_UPDATED_OBJ	(1<<1)
#define P_LOG_VISIBLE_OBJS		(1<<2)
#define P_LOG_LAST_DRAWN_OBJ	(1<<3)
#define P_LOG_SET_OBJ_FLAGS		(1<<4)
#define P_LOG_SET_OBJ_TRANSFORM	(1<<5)
#define P_LOG_SET_OBJ_PARAM		(1<<6)
#define P_LOG_ATTACH_OBJECT		(1<<7)
#define P_LOG_PROJECTILES		(1<<8)
#define P_LOG_SET_WORLD_ORIGIN	(1<<9)
#define P_LOG_RENDER_UPDATE		(1<<10)

#define P_FACEFLAGS_EDGE_A		(1<<0)
#define P_FACEFLAGS_EDGE_B		(1<<1)
#define P_FACEFLAGS_EDGE_C		(1<<2)
#define P_FACEFLAGS_EDGE_ALL	(P_FACEFLAGS_EDGE_A|P_FACEFLAGS_EDGE_B|P_FACEFLAGS_EDGE_C)
#define P_FACEFLAGS_TWOSIDE		(1<<3)
#define P_FACEFLAGS_NOSHADOW	(1<<4)

#define P_MATFLAGS_TWOSIDE		(1<<3)
#define P_MATFLAGS_NOSHADOW		(1<<4)
#define P_MATFLAGS_TEXCLAMP		(1<<5)
#define P_MATFLAGS_NOLIGHT		(1<<8)
#define P_MATFLAGS_NOCOLLIDE	(1<<9)
#define P_MATFLAGS_NOFOG		(1<<10)
#define P_MATFLAGS_NOMIPMAP		(1<<11)
#define P_MATFLAGS_NOGLOW		(1<<12)
#define P_MATFLAGS_NOENVMAP		(1<<13)

#define P_PICFLAGS_NORMALMAP	(1<<0)
#define P_PICFLAGS_NOMIPMAP		(1<<1)
#define P_PICFLAGS_TEX3D		(1<<2)
#define P_PICFLAGS_RELIEFMAP	(1<<3)

#define P_LIGHTFLAGS_ENABLED	(1<<0)
#define P_LIGHTFLAGS_NOSHADOW	(1<<1)
#define P_LIGHTFLAGS_SELECTED	(1<<2)
#define P_LIGHTFLAGS_GLOBAL		(1<<3)

#define P_LIGHTMODE_SELECTFACES	(1<<0)
#define P_LIGHTMODE_SCISSORS	(1<<1)

#define P_MESHFLAGS_DIRTY		(1<<0)
#define P_MESHFLAGS_SKELETON	(1<<1)
#define P_MESHFLAGS_REF			(1<<2)

#define P_COMPUTE_FACENORM	(1<<0)
#define P_COMPUTE_VERTNORM	(1<<1)
#define P_COMPUTE_TANGENTS	(1<<2)
#define P_COMPUTE_BBOX		(1<<3)
#define P_COMPUTE_CURVATURE (1<<4)
#define P_COMPUTE_ALL		(P_COMPUTE_FACENORM|P_COMPUTE_VERTNORM|P_COMPUTE_TANGENTS|P_COMPUTE_CURVATURE|P_COMPUTE_BBOX)

#define P_RONUMDEFAULTPARAM			3
#define P_ROFLAGS_ENABLED			(1<<0)
#define P_ROFLAGS_VISIBLE			(1<<1)
#define P_ROFLAGS_TRANSP			(1<<2)
#define P_ROFLAGS_HASMESH			(1<<3)
#define P_ROFLAGS_CONTAINER			(1<<4)
#define P_ROFLAGS_ENABLED_VISIBLE	(3)

#define P_GUINUMDEFAULTPARAM		23
#define P_GUIFLAGS_ENABLED			(1<<0)
#define P_GUIFLAGS_VISIBLE			(1<<1)
#define P_GUIFLAGS_ENABLED_VISIBLE	(3)

#define P_GUI_MOUSESTATE_LEFTDOWN		(1<<0)
#define P_GUI_MOUSESTATE_RIGHTDOWN		(1<<1)
#define P_GUI_MOUSESTATE_MIDDLEDOWN		(1<<2)
#define P_GUI_MOUSESTATE_LEFTCLICK		(1<<3)
#define P_GUI_MOUSESTATE_RIGHTCLICK		(1<<4)
#define P_GUI_MOUSESTATE_MIDDLECLICK	(1<<5)
#define P_GUI_MOUSESTATE_LEFTUNCLICK	(1<<6)
#define P_GUI_MOUSESTATE_RIGHTUNCLICK	(1<<7)
#define P_GUI_MOUSESTATE_MIDDLEUNCLICK	(1<<8)
#define P_GUI_MOUSESTATE_LEFTDCLICK		(1<<9)
#define P_GUI_MOUSESTATE_RIGHTDCLICK	(1<<10)
#define P_GUI_MOUSESTATE_MIDDLEDCLICK	(1<<11)

enum
{
	P_ENVMODE_NONE=0,
	P_ENVMODE_CUBE_MAPPING,
	P_ENVMODE_SPHERE_MAPPING,
};

enum
{
	P_GUI_MSG_BEGINDRAG=1024,
	P_GUI_MSG_BUTTONCLICK,
	P_GUI_MSG_CHECKBOXCLICK,
	P_GUI_MSG_DRAGOVER,
	P_GUI_MSG_DROP,
	P_GUI_MSG_ENDDRAG,
	P_GUI_MSG_ONCHANGE,
	P_GUI_MSG_SELCHANGE,
	P_GUI_MSG_POPUP,
	P_GUI_MSG_POPUPACTION,
	P_GUI_MSG_LEFTMOUSEDOWN,
	P_GUI_MSG_LEFTMOUSEUP,
	P_GUI_MSG_RIGHTMOUSEDOWN,
	P_GUI_MSG_RIGHTMOUSEUP,
	P_GUI_MSG_MOUSEIN,
	P_GUI_MSG_MOUSEOUT,
};

#define P_FONTS_NUM			16
#define P_FONTS_FACTOR		0.0625f

#define P_PACK_FLOAT_TO_BYTE(in) ((unsigned char)(((in)+1.0f)*127.5f));

#define P_HASH_SIZE 9
#define P_LIST_SIZE 8

enum
{
	P_PERIODICFUNC_NONE = 0,
	P_PERIODICFUNC_SIN,
	P_PERIODICFUNC_TRIANGLE,
	P_PERIODICFUNC_SQUARE,
	P_PERIODICFUNC_SAWTOOTH,
	P_PERIODICFUNC_INVERSESAWTOOTH
};

enum 
{ 
	P_ANIMTYPE_VALUE_LINEAR=0,
	P_ANIMTYPE_VALUE_SMOOTH,
	P_ANIMTYPE_POINT_LINEAR,
	P_ANIMTYPE_POINT_SMOOTH,
	P_ANIMTYPE_QUAT_LINEAR,
	P_ANIMTYPE_QUAT_SMOOTH
};

class P3D_API pFile;
class P3D_API pVector;
class P3D_API pPlane;
class P3D_API pVertex;
class P3D_API pMatrix;
class P3D_API pQuaternion;
class P3D_API pString;
class P3D_API pBoundBox;
class P3D_API pFrustum;
class P3D_API pOrientedBoundBox;
class P3D_API pCapsule;
class P3D_API pLineSegment;
class P3D_API pFace;
class P3D_API pMesh;

#include "pMath.h"

#if defined(WIN32)
#include "pString.h"
#include "pArray.h"
#include "pFile.h"
#include "pBoundBox.h"
#include "pFrustum.h"
#include "pOrientedBoundBox.h"
#include "pLineSegment.h"
#include "pCapsule.h"

class P3D_API pAmination;
class P3D_API pBezier;
class P3D_API pDummy;
class P3D_API pOcTreeNode;
class P3D_API pOcTree;
class P3D_API pCamera;
class P3D_API pLight;
class P3D_API pMSPhy;
class P3D_API pMSAni;
class P3D_API pMSMtg;
class P3D_API pMSMtgAni;
class P3D_API pMeshSkeleton;
class P3D_API pMaterial;
class P3D_API pPicture;
class P3D_API pRender;
class P3D_API pRenderPass;
class P3D_API pRenderProfile;
class P3D_API pRenderObject;

#include "pHashTable.h"
#include "pHashTableStr.h"
#include "pCircularList.h"
#include "pLogReport.h"
#include "pPeriodicFunc.h"
#include "pAnimation.h"
#include "pBezier.h"
#include "pCamera.h"
#include "pLight.h"
#include "pOcTreeNode.h"
#include "pOcTree.h"
#include "pMaterial.h"
#include "pFace.h"
#include "pDummy.h"
#include "pMesh.h"
#include "pMeshSkeleton.h"
#include "pDesc.h"
#include "pPicture.h"
#include "pPBuffer.h"
#include "pRM.h"
#include "pTeapot.h"
#include "pRenderProfile.h"
#include "pRenderProfileVert.h"
#include "pRenderProfileFrag.h"
#include "pRenderGlow.h"
#include "pRenderRipple.h"
#include "pRenderPass.h"
#include "pRenderShadowMap.h"
#include "pRenderVertexBuffer.h"
#include "pRender.h"
#include "pRenderObject.h"

#ifdef P_MANAGER_OBJ
class P3D_API pRenderObjectManager;
#endif

#ifdef P_MANAGER_GUI
class P3D_API pGUIObjectManager;
class P3D_API pGUIEventHandler;
class P3D_API pGUIObject;
class P3D_API pGUIButton;
class P3D_API pGUIGroup;
class P3D_API pGUIWindow;
#endif

#ifdef P_MANAGER_OBJ
#include "pRenderObjectManager.h"
#include "pROBillboard.h"
#include "pROCamera.h"
#include "pROExplosion.h"
#include "pROExplodeObject.h"
#include "pROGroup.h"
#include "pROLensFlare.h"
#include "pROLight.h"
#include "pROMesh.h"
#include "pROMeshHuge.h"
#include "pROMeshLOD.h"
#include "pROMeshRelief.h"
#include "pROMeshSkeleton.h"
#include "pROMeshTeapot.h"
#include "pROPanorama.h"
#include "pROObfuscatingPoint.h"
#include "pROParticleSystem.h"
#include "pROParticleSystemGPU.h"
#include "pROProjectile.h"
#include "pRORotor.h"
#include "pROSpaceDust.h"
#include "pROTrail.h"
#endif

#ifdef P_MANAGER_GUI
#include "pRect.h"
#include "pIconGridInfo.h"
#include "pGUIObjectManager.h"
#include "pGUIObject.h"
#include "pGUIButton.h"
#include "pGUICheckBox.h"
#include "pGUIEditBox.h"
#include "pGUIGroup.h"
#include "pGUIImage.h"
#include "pGUIRadialCursor.h"
#include "pGUIModelViewer.h"
#include "pGUIMultilineText.h"
#include "pGUIPopUpMenu.h"
#include "pGUIProgressBar.h"
#include "pGUIProgressDisk.h"
#include "pGUIWindow.h"
#include "pGUIListControl.h"
#include "pGUITreeControl.h"
#endif

#ifdef P_NETWORK
#include "pNetwork.h"
#endif

#ifdef P_SOUND
#include "pSound.h"
#include "pSoundManager.h"
#include "pROSound.h"
#endif

#if 0
#include "../../UnSRC/QActiveFramewrk.h"
#endif

#endif //WIN32

#endif
