/*

	unPhosectNucleusNT - No Threads
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef PHOSECTNUCLEUS_NT_H
#define PHOSECTNUCLEUS_NT_H

/// Unification MidIncludes
#include "../ClassUtil/unClarityDef.h"
#include "../../Server/Thread.h"
#include "Phosect/unPhosect.h"

//#include <iostream>
#include <sstream>
//#include <string>
//#include <stdexcept>

/// pEngine Includes
#include "pMath.h"

/// Lighting Includes
//#include "VPL/OmniDirectionalShadowMap.h"

#include <windows.h>		// Header File For Windows

#include "glew.h"

/// OpenGL includes
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <C:\Program Files (x86)\Microsoft Platform SDK for Windows Server 2003 R2\Include\gl\GLAux.h>		// Header File For The Glaux Library
#include <gl\glext.h>       // Header File For OpenGL Extensions


//#include <gl\glh_extensions.h>
//#include <gl\glh_genext.h>
//#include <gl\glh_combiners.h>

// Include DRAT framework

#define MAX_PHOSECT 256
#define MED_PHOSECT 5
#define MIN_PHOSECT 1

const int SHADOW_MAP_RES = 1024;

const unsigned int texxcoordsnew[] =
{
1, 0,
0, 0,
0, 1,
1, 1
};

const unsigned int texxreversednew[] =
{
1, 1,
0, 1,
0, 0,
1, 0
};

class unPhosectNucleusNT : public unClarity
{
public:

	unPhosectNucleusNT(void);
	virtual ~unPhosectNucleusNT();

	bool UpdateCache(void);
	bool UpdateNucleus(void);
	void ServeNucleus(void);
	void DelocPhosect(Uint16 i_element);
	inline void acCreatePhosect(pVertex i_vertex) { m_NewVertexserve.push_back(i_vertex); };

	char *readRegCombinerFile(const char *fileName);

	bool Initialize(void);
	void Run(void);

	bool ValidityCheck(float ClarityLevel);
	bool RemovalUpdate(void);

	static void sysMessage(const char *i_Message);
	static void sysFloat(float i_Float);
	static void sysInt(unsigned int i_Int);

	void GLEnable2D(void);
	void GLDisable2D(void);
	void DrawPane(unsigned int i_texture, int i_x, int i_y, int i_scalex, int i_scaley);

	/// singleton instance access
	static unPhosectNucleusNT* instance();

	/// Phosect Vector POSSIBLY TEMPORARY
	std::vector<unPhosect *> m_Phosect;

	pVertex CameraVertex;

	unsigned int textureone;

protected:

	//// Programs
	GLuint VP_Render, RC_Mux, DL_Scene;           // Shaders
	//GLuint T_Shadow[2] ;										// Shadow map textures

	bool m_Update;

private:
	static unPhosectNucleusNT* s_instance;

	std::vector<pVertex> m_NewVertexserve;
	std::vector<Uint16> m_PhoVectorserver;
	Uint16 m_NomPhosect;
};

class BadConversion : public std::runtime_error
{
	public:
	BadConversion(const std::string& s) : std::runtime_error(s) { }
};
 
inline std::string stringify(double x)
{
	std::ostringstream o;
	if (!(o << x))
	throw BadConversion("stringify(double)");
	return o.str();
}

inline std::string stringint(unsigned int x)
{
	std::ostringstream o;
	if (!(o << x))
	throw BadConversion("stringify(int)");
	return o.str();
}

#endif