#ifndef P_DEFINES_H
#define P_DEFINES_H

#define P_P3DVERSIONSTR "1.1.11"
#define P_P3DVERSION	1111

#ifdef P3D_DLL
	#pragma warning(disable:4251)
	#ifdef P3D_EXPORTS
		#define P3D_API __declspec(dllexport)
	#else
		#define P3D_API __declspec(dllimport)
	#endif
#else
	#define P3D_API 
#endif

//#define P_DISABLE_3D			// disables all 3d support (no linking with opengl or cg)
#ifndef P_DISABLE_3D
	#define P_INIT_OGL			// initialize opengl with render (comment for using sdl)
	#define P_SUPPORT_CG		// supports cg
//	#define P_SUPPORT_3DS		// support loading 3ds files
#endif

#define P_MANAGER_OBJ			// render objects manager and objects
#define P_MANAGER_GUI			// gui manager and objects
#define P_TRANSPARENT			// transparent faces support
#define P_EXTRAPASS				// extra render pass
//#define P_NETWORK				// sdl_net support
//#define P_SOUND					// openal sound support
//#define P_MESH_SHORT_FACE		// small face indices (<65535 faces per model)
//#define P_MESH_SHORT_VERT		// small vertex params (no map scale or curvature)

#endif
