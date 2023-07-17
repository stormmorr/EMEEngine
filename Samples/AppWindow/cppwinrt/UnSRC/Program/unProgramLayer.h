/*

	unProgramLayer
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef PROGRAMLAYER_H
#define PROGRAMLAYER_H 

#include <Cg\cg.h>
#include <Cg\cggl.h>
#include <vector>

/* OpenGL tokens for cube maps missing from Windows version of <GL/gl.h> */
#define GL_TEXTURE_CUBE_MAP                 0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X      0x8515

namespace unPRG
{

class unProgram
{
public:
	unProgram();
	unProgram(const char *i_name);
	~unProgram();

	void pushParameter(const char *i_name);
	void push//*CGparameter(//*CGparameter i_parameter, const char *i_name);
	CGtechnique pushTechnique(CGtechnique i_technique);

	bool ValidateTechniques(void);
	bool m_techValid;

	//*CGprogram	m_Program;
	CGeffect    m_Effect;
	//*CGprofile	m_Profile;
	CGcontext   m_cgContext;

	const char *m_name;

	std::vector<CGtechnique> vecTechnique;
	std::vector<//*CGparameter> vecParameter;
	std::vector<std::string> decParameter;
};

class unProgramLayer
{
public:
	unProgramLayer();
	~unProgramLayer();

	/// Manage Program Creation
	unProgram *pushProgramVert(const char * i_name, const char * i_entrypoint, const char *i_filename);
	unProgram *pushProgramFrag(const char * i_name, const char * i_entrypoint, const char *i_filename);
	unProgram *pushFXProgram(const char * i_name, const char *i_filename);
	unProgram *getLast(void) { if(vecProgram.size() > 0) return vecProgram[vecProgram.size() - 1]; else printf("ERROR Program Layer vecProgram empty\n"); return NULL; }
	int getLastID(void) { return vecProgram.size() - 1; };

	void BindProgram(void);

	/// Texture Manipulation ///
	void useSamplerParameter(CGeffect effect, const char *paramName, GLuint texobj);

	/// Error Checking ///
	void checkError(const char *name, const char *situation);

	/// One and Only Context ///
	CGcontext m_cgContext;

	std::vector<unProgram*> vecProgram;

	/// singleton instance access
	static unProgramLayer* instance();

private:
	static unProgramLayer* s_instance;
};

};// End PRG namespace

#endif