/*

	unProgramLayer
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "unProgramLayer.h"

namespace unPRG
{

unProgram::unProgram(void)
{

}

unProgram::unProgram(const char *i_name)
{
	/// Set Program Name
	m_name = i_name;
}

void unProgram::pushParameter(const char *i_name)
{
	/// Push Program Parameter ///
	vecParameter.push_back(cgGetNamedParameter(m_Program, i_name));
	decParameter.push_back(i_name);

	if(!vecParameter[vecParameter.size() - 1])
		{
		fprintf(stderr, "%s: must find parameter\n", i_name);
		while(1) { /* Infinite Loop */ }
		exit(1);
		}
}

void unProgram::push//*CGparameter(//*CGparameter i_parameter, const char *i_name)
{
	/// Push Program Parameter ///
	vecParameter.push_back(i_parameter);
	decParameter.push_back("default_cgfx_param");

	if(!vecParameter[vecParameter.size() - 1])
		{
		fprintf(stderr, "%s: must find parameter ::: %s\n", "default_cgfx_param", i_name);
		while(1) { /* Infinite Loop */ }
		exit(1);
		}
}

bool unProgram::ValidateTechniques(void)
{
	m_techValid = true;

	for(size_t i = 0; i < vecTechnique.size(); i++)
		{
		if(vecTechnique[i] && cgValidateTechnique(vecTechnique[i]) == CG_FALSE)
			{
			fprintf(stderr, "%s: Technique %s did not validate.  Skipping.\n", m_name, cgGetTechniqueName(vecTechnique[i]));
			vecTechnique[i] = cgGetNextTechnique(vecTechnique[i]);
			m_techValid = false;
			}
		}

	return m_techValid;
}

void unProgramLayer::BindProgram(void)
{

}

unProgramLayer::unProgramLayer(void)
{
	///// Create CG Context /////
	// Setup Cg
	m_cgContext = cgCreateContext();										// Create A New Context For Our Cg Program(s)

	// Set debugging mode
	////*cgGLSetDebugMode( CG_FALSE );

	// Check for errors mostly driver related
	checkError("m_cgContext", "Create Context");
}

unProgram *unProgramLayer::pushProgramVert(const char * i_name, const char * i_entrypoint, const char *i_filename)
{
	unProgram *program = new unProgram(i_name);

	program->m_Profile = //*cgGLGetLatestProfile(CG_GL_VERTEX);

	// Validate Our Profile Determination Was Successful
	if (program->m_Profile == CG_PROFILE_UNKNOWN) printf("ERROR::: Invalid profile type\n");

	//*cgGLSetOptimalOptions(program->m_Profile);

	program->m_Program = cgCreateProgramFromFile(m_cgContext, CG_SOURCE, i_filename, program->m_Profile, i_entrypoint, 0);

	// Validate Success
	if (program->m_Program == NULL) checkError(program->m_name, "CG::LOAD:::ERROR");

	// Load The Program
	//*cgGLLoadProgram(program->m_Program);

	vecProgram.push_back( program );

	printf("CG::LOADED %s\n", i_name);

	return program;
}

unProgram *unProgramLayer::pushProgramFrag(const char * i_name, const char * i_entrypoint, const char *i_filename)
{
	unProgram *program = new unProgram(i_name);

	program->m_Profile = //*cgGLGetLatestProfile(CG_GL_FRAGMENT);

	// Validate Our Profile Determination Was Successful
	if (program->m_Profile == CG_PROFILE_UNKNOWN) printf("ERROR::: Invalid profile type\n");

	//*cgGLSetOptimalOptions(program->m_Profile);

	//CG_PROFILE_ARBFP1

	program->m_Program = cgCreateProgramFromFile(m_cgContext, CG_SOURCE, i_filename, program->m_Profile, i_entrypoint, 0);

	// Validate Success
	if (program->m_Program == NULL) checkError(program->m_name, "CG::LOAD:::ERROR");

	// Load The Program
	//*cgGLLoadProgram(program->m_Program);

	vecProgram.push_back( program );

	printf("CG::LOADED %s\n", i_name);

	return program;
}

unProgram *unProgramLayer::pushFXProgram(const char * i_name, const char *i_filename)
{
	unProgram *program = new unProgram(i_name);

	////// Load CGFX Effect //////
	//*cgGLRegisterStates(m_cgContext);
	checkError(i_name, "registering standard CgFX states");

	//*cgGLSetManageTextureParameters(m_cgContext, CG_TRUE);
	checkError(i_name, "manage texture parameters");

	program->m_Effect = cgCreateEffectFromFile(m_cgContext, i_filename, NULL);
	checkError(i_name, "creating cgfx effect");

	program->vecTechnique.push_back(cgGetFirstTechnique(program->m_Effect));
	program->ValidateTechniques();

	if(program->m_techValid) fprintf(stderr, "%s: Use technique %s.\n", program->m_name, cgGetTechniqueName(program->vecTechnique[0]));
	else
		{
		fprintf(stderr, "%s: No valid technique\n", program->m_name);
		while(1) { /* Infinite Loop */ }
		exit(1);
		}

	vecProgram.push_back( program );

	return program;
}

void unProgramLayer::useSamplerParameter(CGeffect effect, const char *paramName, GLuint texobj)
{
	//*CGparameter param = cgGetNamedEffectParameter(effect, paramName);

	if(!param)
		{
		fprintf(stderr, "ERROR::: expected effect parameter named %s\n", paramName);
		while(1) { /* Infinite Loop */ }
		exit(1);
		}

	//*cgGLSetTextureParameter(param, texobj);
	cgSetSamplerState(param);
}

void unProgramLayer::checkError(const char *name, const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);
  
	if (error != CG_NO_ERROR)
		{
		if (error == CG_COMPILER_ERROR)
			{
			fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s\n\n"
			"Cg compiler output...\n%s",
			name, situation, string,
			cgGetLastListing(m_cgContext));
			}
		else
			{
			fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s",
			name, situation, string);
			}
		while(1) { /* Infinite Loop */ }
		exit(1);
		}
}

unProgramLayer::~unProgramLayer(void)
{

}

unProgramLayer* unProgramLayer::s_instance = 0;
unProgramLayer* unProgramLayer::instance()
{
  return s_instance;
}

};// End PRG namespace