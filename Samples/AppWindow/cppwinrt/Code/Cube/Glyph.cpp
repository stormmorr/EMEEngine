/*

VoxelGrid.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Glyph.h"
#include "MathHelper.h"

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"

#include "q-keydefinitions.h"

#if 0
#include "Render/FrustumG.h"
#endif

using namespace GVARS;
using namespace Cube;
using namespace std;

namespace Cube
{

GlyphManager* g_GlyphManager;

#define STRING(s) #s

GLuint glyphCompileShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *sourceArray[1] = { source.c_str() };
    glShaderSource(shader, 1, sourceArray, NULL);
    glCompileShader(shader);

    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if(compileResult == 0)
		{
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Shader compilation failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 
		std::string f_errorMessage = to_string(errorMessage);

		printf("SHADER ERROR:::VX:::%s\n", f_errorMessage.c_str());

#if 0
		throw;
#endif
#if 1
		__debugbreak();
#endif
    }

    return shader;
}

GLuint glyphCompileProgram(const std::string &vsSource, const std::string &fsSource)
{
    GLuint program = glCreateProgram();

    if(program == 0)
		{
        throw;
		}

    GLuint vs = glyphCompileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = glyphCompileShader(GL_FRAGMENT_SHADER, fsSource);

    if(vs == 0 || fs == 0)
		{
        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(program);
        return 0;
		}

    glAttachShader(program, vs);
    glDeleteShader(vs);

    glAttachShader(program, fs);
    glDeleteShader(fs);

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if(linkStatus == 0)
		{
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Program link failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end());

        throw;
		}

    return program;
}

Glyph::Glyph()
{
	Initialize();
}

Glyph::~Glyph()
{
#if 1
	Unload();
#endif
}

// Initialize
void Glyph::Initialize()
{
	m_rebuild = true;
}

void Glyph::Unload(void)
{
	glDeleteBuffers(1, &mVertexPositionBuffer);
	glDeleteBuffers(1, &mVertexNormalBuffer);
	glDeleteBuffers(1, &mVertexColorBuffer);
	glDeleteBuffers(1, &mVertexTexCoordBuffer);
}

void Glyph::GenerateBuffers(void)
{
	const unsigned int f_VertNom = m_vec_Vertex.size() * 3;
	const unsigned int f_ColorNom = m_vec_Color.size() * 4;
	const unsigned int f_UVNom = m_vec_Tex.size() * 2;
	const unsigned int f_IndexNom = m_vec_Index.size() * 3;

	GLfloat* f_Position = new GLfloat[f_VertNom];
	GLfloat* f_Normal = new GLfloat[f_VertNom];
	GLfloat* f_Color = new GLfloat[f_ColorNom];
	GLfloat* f_Tex = new GLfloat[f_UVNom];
	short* f_Index = new short[f_IndexNom];

	for (unsigned int f_VertexCount = 0; f_VertexCount < m_vec_Vertex.size(); f_VertexCount++)
		{
		f_Position[(f_VertexCount * 3)] = m_vec_Vertex[f_VertexCount]->m_X;
		f_Position[(f_VertexCount * 3) + 1] = m_vec_Vertex[f_VertexCount]->m_Y;
		f_Position[(f_VertexCount * 3) + 2] = m_vec_Vertex[f_VertexCount]->m_Z;
		}

	for (unsigned int f_NormalCount = 0; f_NormalCount < m_vec_Normal.size(); f_NormalCount++)
		{
		f_Normal[(f_NormalCount * 3)] = m_vec_Normal[f_NormalCount]->m_X;
		f_Normal[(f_NormalCount * 3) + 1] = m_vec_Normal[f_NormalCount]->m_Y;
		f_Normal[(f_NormalCount * 3) + 2] = m_vec_Normal[f_NormalCount]->m_Z;
		}

	for (unsigned int f_ColorCount = 0; f_ColorCount < m_vec_Color.size(); f_ColorCount++)
		{
		f_Color[(f_ColorCount * 4)] = m_vec_Color[f_ColorCount]->m_R;
		f_Color[(f_ColorCount * 4) + 1] = m_vec_Color[f_ColorCount]->m_G;
		f_Color[(f_ColorCount * 4) + 2] = m_vec_Color[f_ColorCount]->m_B;
		f_Color[(f_ColorCount * 4) + 3] = m_vec_Color[f_ColorCount]->m_A;
		}

	for (unsigned int f_TexCount = 0; f_TexCount < m_vec_Tex.size(); f_TexCount++)
		{
		f_Tex[(f_TexCount * 2)] = m_vec_Tex[f_TexCount]->m_U;
		f_Tex[(f_TexCount * 2) + 1] = m_vec_Tex[f_TexCount]->m_V;
		}

	for (unsigned int f_IndexCount = 0; f_IndexCount < m_vec_Index.size(); f_IndexCount++)
		{
		f_Index[(f_IndexCount * 3)] = m_vec_Index[f_IndexCount]->m_A;
		f_Index[(f_IndexCount * 3) + 1] = m_vec_Index[f_IndexCount]->m_B;
		f_Index[(f_IndexCount * 3) + 2] = m_vec_Index[f_IndexCount]->m_C;
		}

	glGenBuffers(1, &mVertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Position, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_IndexNom, f_Index, GL_STATIC_DRAW);
}

GlyphManager::GlyphManager() :
    mWindowWidth(0),
    mWindowHeight(0),
    mDrawCount(0)
{
	// Vertex Shader source
    const std::string vs = STRING
		(
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec3 uPos;
		uniform vec4 cameraTrans;
        attribute vec3 aPosition;
		attribute vec3 aNormal;
        attribute vec4 aColor;
		attribute vec2 aUV;
		varying vec3 vPosition;
		varying vec3 vNormal;
        varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			vec4 f_Position = vec4(aPosition, 1.0);

			f_Position = uProjMatrix * uViewMatrix * f_Position;

			vPosition = f_Position.xyz;
			vNormal = aNormal;
			vColor = aColor;
			vUV = aUV;
			
			gl_Position = f_Position;
			}
		);

	// Fragment Shader source
	const std::string fs = STRING
		(
		precision mediump float;
		uniform sampler2D f_texture;
		varying vec3 vPosition;
		varying vec3 vNormal;
		varying vec4 vColor;
		varying vec2 vUV;
		void main()
			{
			//vec4 f_Color = texture2D(f_texture, gl_PointCoord);
			vec4 f_Color = vColor;
			gl_FragColor = f_Color;
			}
		);

    // Set up the shader and its uniform/attribute locations.
    mProgram = glyphCompileProgram(vs, fs);
    mPositionAttribLocation = glGetAttribLocation(mProgram, "aPosition");
	mNormalAttribLocation = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocation = glGetAttribLocation(mProgram, "aColor");
	mTexCoordAttribLocation = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
    mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
    mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");
	mCameraTranslationUniformLocation = glGetUniformLocation(mProgram, "cameraTrans");
}

GlyphManager::~GlyphManager()
{
    if(mProgram != 0)
		{
        glDeleteProgram(mProgram);
        mProgram = 0;
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Spawn[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Event[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Function[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Variable[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Trigger[f_XY]->Unload();
		}

	g_RefList.clear();
}

void GlyphManager::acResetList(void)
{
	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Spawn[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Event[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Function[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Variable[f_XY]->Unload();
		}

	for(int f_XY = 0; f_XY < m_vec_Glyph_Spawn.size(); f_XY++)
		{
		m_vec_Glyph_Trigger[f_XY]->Unload();
		}

	g_RefList.clear();
}

bool GlyphManager::UpdateGlyphs(void)
{
#if 0
	std::vector< QamRefList*> f_GlyphList;

	f_GlyphList.clear();

	//TEST Triggers
	for(int f_Int = 0; f_Int < g_QAM->m_vec_Trigger.size(); f_Int++)
		{
		int f_QtkID = g_QAM->m_vec_Trigger[f_Int]->m_ID;

		QamRefList* f_List = new QamRefList(qamTYPE_Trigger, f_QtkID);

		f_GlyphList.push_back(f_List);
		}

	bool f_RebuildList = false;

	for(int f_TJet = 0; f_TJet < f_GlyphList.size(); f_TJet++)
		{
		for(int f_BJet = 0; f_BJet < f_GlyphList[f_TJet]->m_vec_Spawn.size(); f_BJet++)
			{
			if(f_BJet < m_vec_Glyph_Spawn.size())
				{
				if (f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_X != g_RefList[f_TJet]->m_vec_Spawn[f_BJet]->m_X ||
					f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y != g_RefList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y ||
					f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z != g_RefList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z ||
					f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Xrot != g_RefList[f_TJet]->m_vec_Spawn[f_BJet]->m_Xrot ||
					f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Yrot != g_RefList[f_TJet]->m_vec_Spawn[f_BJet]->m_Yrot ||
					f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Zrot != g_RefList[f_TJet]->m_vec_Spawn[f_BJet]->m_Zrot ||
					f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Updated == false)
					{
					f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Updated = true;

					   /////////////
					  //
					 //
					// Triggers
					Cube::Glyph* f_Glyph = new Cube::Glyph();

					Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z);
					Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z + 5.0f);
					Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z + 5.0f);

					f_Glyph->m_pos = f_VecO;

					Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

					Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
					Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
					Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

					Cube::Index* f_Index = new Cube::Index();

					Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

					f_VecN->acNormalize();

					f_Index->m_A = 0;
					f_Index->m_B = 1;
					f_Index->m_C = 2;

					f_Glyph->m_vec_Vertex.push_back(f_VecO);
					f_Glyph->m_vec_Vertex.push_back(f_VecA);
					f_Glyph->m_vec_Vertex.push_back(f_VecB);

					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);

					f_Glyph->m_vec_Index.push_back(f_Index);

					f_Glyph->m_vec_Tex.push_back(f_TexO);
					f_Glyph->m_vec_Tex.push_back(f_TexA);
					f_Glyph->m_vec_Tex.push_back(f_TexB);

					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);

					f_Glyph->GenerateBuffers();

					m_vec_Glyph_Spawn[f_BJet] = f_Glyph;

					f_RebuildList = true;
					}
				}
			else
				{
				f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Updated = true;

				   /////////////
				  //
				 //
				// Triggers
				Cube::Glyph* f_Glyph = new Cube::Glyph();

				Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z);
				Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z + 5.0f);
				Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Spawn[f_BJet]->m_Z + 5.0f);

				f_Glyph->m_pos = f_VecO;

				Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

				Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
				Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
				Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

				Cube::Index* f_Index = new Cube::Index();

				Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

				f_VecN->acNormalize();

				f_Index->m_A = 0;
				f_Index->m_B = 1;
				f_Index->m_C = 2;

				f_Glyph->m_vec_Vertex.push_back(f_VecO);
				f_Glyph->m_vec_Vertex.push_back(f_VecA);
				f_Glyph->m_vec_Vertex.push_back(f_VecB);

				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);

				f_Glyph->m_vec_Index.push_back(f_Index);

				f_Glyph->m_vec_Tex.push_back(f_TexO);
				f_Glyph->m_vec_Tex.push_back(f_TexA);
				f_Glyph->m_vec_Tex.push_back(f_TexB);

				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);

				f_Glyph->GenerateBuffers();

				m_vec_Glyph_Spawn.push_back(f_Glyph);

				f_RebuildList = true;
				}
			}

		for(int f_BJet = 0; f_BJet < f_GlyphList[f_TJet]->m_vec_Event.size(); f_BJet++)
			{
			if(f_BJet < m_vec_Glyph_Event.size())
				{
				if (f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_X != g_RefList[f_TJet]->m_vec_Event[f_BJet]->m_X ||
					f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Y != g_RefList[f_TJet]->m_vec_Event[f_BJet]->m_Y ||
					f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Z != g_RefList[f_TJet]->m_vec_Event[f_BJet]->m_Z ||
					f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Xrot != g_RefList[f_TJet]->m_vec_Event[f_BJet]->m_Xrot ||
					f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Yrot != g_RefList[f_TJet]->m_vec_Event[f_BJet]->m_Yrot ||
					f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Zrot != g_RefList[f_TJet]->m_vec_Event[f_BJet]->m_Zrot ||
					f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Updated == false)
					{
					f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Updated = true;

					   /////////////
					  //
					 //
					// Triggers
					Cube::Glyph* f_Glyph = new Cube::Glyph();

					Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Z);
					Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Z + 5.0f);
					Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Z + 5.0f);

					f_Glyph->m_pos = f_VecO;

					Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

					Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
					Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
					Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

					Cube::Index* f_Index = new Cube::Index();

					Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

					f_VecN->acNormalize();

					f_Index->m_A = 0;
					f_Index->m_B = 1;
					f_Index->m_C = 2;

					f_Glyph->m_vec_Vertex.push_back(f_VecO);
					f_Glyph->m_vec_Vertex.push_back(f_VecA);
					f_Glyph->m_vec_Vertex.push_back(f_VecB);

					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);

					f_Glyph->m_vec_Index.push_back(f_Index);

					f_Glyph->m_vec_Tex.push_back(f_TexO);
					f_Glyph->m_vec_Tex.push_back(f_TexA);
					f_Glyph->m_vec_Tex.push_back(f_TexB);

					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);

					f_Glyph->GenerateBuffers();

					m_vec_Glyph_Event[f_BJet] = f_Glyph;

					f_RebuildList = true;
					}
				}
			else
				{
				f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Updated = true;

				   /////////////
				  //
				 //
				// Triggers
				Cube::Glyph* f_Glyph = new Cube::Glyph();

				Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Z);
				Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Z + 5.0f);
				Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Event[f_BJet]->m_Z + 5.0f);

				f_Glyph->m_pos = f_VecO;

				Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

				Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
				Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
				Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

				Cube::Index* f_Index = new Cube::Index();

				Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

				f_VecN->acNormalize();

				f_Index->m_A = 0;
				f_Index->m_B = 1;
				f_Index->m_C = 2;

				f_Glyph->m_vec_Vertex.push_back(f_VecO);
				f_Glyph->m_vec_Vertex.push_back(f_VecA);
				f_Glyph->m_vec_Vertex.push_back(f_VecB);

				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);

				f_Glyph->m_vec_Index.push_back(f_Index);

				f_Glyph->m_vec_Tex.push_back(f_TexO);
				f_Glyph->m_vec_Tex.push_back(f_TexA);
				f_Glyph->m_vec_Tex.push_back(f_TexB);

				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);

				f_Glyph->GenerateBuffers();

				m_vec_Glyph_Event.push_back(f_Glyph);

				f_RebuildList = true;
				}
			}

		for(int f_BJet = 0; f_BJet < f_GlyphList[f_TJet]->m_vec_Function.size(); f_BJet++)
			{
			if(f_BJet < m_vec_Glyph_Function.size())
				{
				if (f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_X != g_RefList[f_TJet]->m_vec_Function[f_BJet]->m_X ||
					f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Y != g_RefList[f_TJet]->m_vec_Function[f_BJet]->m_Y ||
					f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Z != g_RefList[f_TJet]->m_vec_Function[f_BJet]->m_Z ||
					f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Xrot != g_RefList[f_TJet]->m_vec_Function[f_BJet]->m_Xrot ||
					f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Yrot != g_RefList[f_TJet]->m_vec_Function[f_BJet]->m_Yrot ||
					f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Zrot != g_RefList[f_TJet]->m_vec_Function[f_BJet]->m_Zrot ||
					f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Updated == false)
					{
					f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Updated = true;

					   /////////////
					  //
					 //
					// Triggers
					Cube::Glyph* f_Glyph = new Cube::Glyph();

					Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Z);
					Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Z + 5.0f);
					Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Z + 5.0f);

					f_Glyph->m_pos = f_VecO;

					Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

					Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
					Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
					Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

					Cube::Index* f_Index = new Cube::Index();

					Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

					f_VecN->acNormalize();

					f_Index->m_A = 0;
					f_Index->m_B = 1;
					f_Index->m_C = 2;

					f_Glyph->m_vec_Vertex.push_back(f_VecO);
					f_Glyph->m_vec_Vertex.push_back(f_VecA);
					f_Glyph->m_vec_Vertex.push_back(f_VecB);

					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);

					f_Glyph->m_vec_Index.push_back(f_Index);

					f_Glyph->m_vec_Tex.push_back(f_TexO);
					f_Glyph->m_vec_Tex.push_back(f_TexA);
					f_Glyph->m_vec_Tex.push_back(f_TexB);

					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);

					f_Glyph->GenerateBuffers();

					m_vec_Glyph_Function[f_BJet] = f_Glyph;

					f_RebuildList = true;
					}
				}
			else
				{
				f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Updated = true;

				   /////////////
				  //
				 //
				// Triggers
				Cube::Glyph* f_Glyph = new Cube::Glyph();

				Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Z);
				Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Z + 5.0f);
				Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Function[f_BJet]->m_Z + 5.0f);

				f_Glyph->m_pos = f_VecO;

				Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

				Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
				Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
				Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

				Cube::Index* f_Index = new Cube::Index();

				Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

				f_VecN->acNormalize();

				f_Index->m_A = 0;
				f_Index->m_B = 1;
				f_Index->m_C = 2;

				f_Glyph->m_vec_Vertex.push_back(f_VecO);
				f_Glyph->m_vec_Vertex.push_back(f_VecA);
				f_Glyph->m_vec_Vertex.push_back(f_VecB);

				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);

				f_Glyph->m_vec_Index.push_back(f_Index);

				f_Glyph->m_vec_Tex.push_back(f_TexO);
				f_Glyph->m_vec_Tex.push_back(f_TexA);
				f_Glyph->m_vec_Tex.push_back(f_TexB);

				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);

				f_Glyph->GenerateBuffers();

				m_vec_Glyph_Function.push_back(f_Glyph);

				f_RebuildList = true;
				}
			}

		for(int f_BJet = 0; f_BJet < f_GlyphList[f_TJet]->m_vec_Variable.size(); f_BJet++)
			{
			if(f_BJet < m_vec_Glyph_Variable.size())
				{
				if (f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_X != g_RefList[f_TJet]->m_vec_Variable[f_BJet]->m_X ||
					f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Y != g_RefList[f_TJet]->m_vec_Variable[f_BJet]->m_Y ||
					f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Z != g_RefList[f_TJet]->m_vec_Variable[f_BJet]->m_Z ||
					f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Xrot != g_RefList[f_TJet]->m_vec_Variable[f_BJet]->m_Xrot ||
					f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Yrot != g_RefList[f_TJet]->m_vec_Variable[f_BJet]->m_Yrot ||
					f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Zrot != g_RefList[f_TJet]->m_vec_Variable[f_BJet]->m_Zrot ||
					f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Updated == false)
					{
					f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Updated = true;

					   /////////////
					  //
					 //
					// Triggers
					Cube::Glyph* f_Glyph = new Cube::Glyph();

					Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Z);
					Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Z + 5.0f);
					Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Z + 5.0f);

					f_Glyph->m_pos = f_VecO;

					Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

					Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
					Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
					Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

					Cube::Index* f_Index = new Cube::Index();

					Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

					f_VecN->acNormalize();

					f_Index->m_A = 0;
					f_Index->m_B = 1;
					f_Index->m_C = 2;

					f_Glyph->m_vec_Vertex.push_back(f_VecO);
					f_Glyph->m_vec_Vertex.push_back(f_VecA);
					f_Glyph->m_vec_Vertex.push_back(f_VecB);

					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);

					f_Glyph->m_vec_Index.push_back(f_Index);

					f_Glyph->m_vec_Tex.push_back(f_TexO);
					f_Glyph->m_vec_Tex.push_back(f_TexA);
					f_Glyph->m_vec_Tex.push_back(f_TexB);

					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);

					f_Glyph->GenerateBuffers();

					m_vec_Glyph_Variable[f_BJet] = f_Glyph;

					f_RebuildList = true;
					}
				}
			else
				{
				f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Updated = true;

				   /////////////
				  //
				 //
				// Triggers
				Cube::Glyph* f_Glyph = new Cube::Glyph();

				Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Z);
				Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Z + 5.0f);
				Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Variable[f_BJet]->m_Z + 5.0f);

				f_Glyph->m_pos = f_VecO;

				Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

				Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
				Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
				Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

				Cube::Index* f_Index = new Cube::Index();

				Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

				f_VecN->acNormalize();

				f_Index->m_A = 0;
				f_Index->m_B = 1;
				f_Index->m_C = 2;

				f_Glyph->m_vec_Vertex.push_back(f_VecO);
				f_Glyph->m_vec_Vertex.push_back(f_VecA);
				f_Glyph->m_vec_Vertex.push_back(f_VecB);

				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);

				f_Glyph->m_vec_Index.push_back(f_Index);

				f_Glyph->m_vec_Tex.push_back(f_TexO);
				f_Glyph->m_vec_Tex.push_back(f_TexA);
				f_Glyph->m_vec_Tex.push_back(f_TexB);

				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);

				f_Glyph->GenerateBuffers();

				m_vec_Glyph_Variable.push_back(f_Glyph);

				f_RebuildList = true;
				}
			}

		for(int f_BJet = 0; f_BJet < f_GlyphList[f_TJet]->m_vec_Trigger.size(); f_BJet++)
			{
			if(f_BJet < m_vec_Glyph_Trigger.size())
				{
				if (f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_X != g_RefList[f_TJet]->m_vec_Trigger[f_BJet]->m_X ||
					f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y != g_RefList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y ||
					f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z != g_RefList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z ||
					f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Xrot != g_RefList[f_TJet]->m_vec_Trigger[f_BJet]->m_Xrot ||
					f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Yrot != g_RefList[f_TJet]->m_vec_Trigger[f_BJet]->m_Yrot ||
					f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Zrot != g_RefList[f_TJet]->m_vec_Trigger[f_BJet]->m_Zrot ||
					f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Updated == false)
					{
					f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Updated = true;

					   /////////////
					  //
					 //
					// Triggers
					Cube::Glyph* f_Glyph = new Cube::Glyph();

					Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z);
					Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z + 5.0f);
					Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z + 5.0f);

					f_Glyph->m_pos = f_VecO;

					Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

					Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
					Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
					Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

					Cube::Index* f_Index = new Cube::Index();

					Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

					f_VecN->acNormalize();

					f_Index->m_A = 0;
					f_Index->m_B = 1;
					f_Index->m_C = 2;

					f_Glyph->m_vec_Vertex.push_back(f_VecO);
					f_Glyph->m_vec_Vertex.push_back(f_VecA);
					f_Glyph->m_vec_Vertex.push_back(f_VecB);

					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);
					f_Glyph->m_vec_Color.push_back(f_GreenColour);

					f_Glyph->m_vec_Index.push_back(f_Index);

					f_Glyph->m_vec_Tex.push_back(f_TexO);
					f_Glyph->m_vec_Tex.push_back(f_TexA);
					f_Glyph->m_vec_Tex.push_back(f_TexB);

					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);
					f_Glyph->m_vec_Normal.push_back(f_VecN);

					f_Glyph->GenerateBuffers();

					m_vec_Glyph_Trigger[f_BJet] = f_Glyph;

					f_RebuildList = true;
					}
				}
			else
				{
				f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Updated = true;

				   /////////////
				  //
				 //
				// Triggers
				Cube::Glyph* f_Glyph = new Cube::Glyph();

				Cube::BiVector* f_VecO = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_X, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z);
				Cube::BiVector* f_VecA = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_X - 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z + 5.0f);
				Cube::BiVector* f_VecB = new Cube::BiVector(f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_X + 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Y + 10.0f, f_GlyphList[f_TJet]->m_vec_Trigger[f_BJet]->m_Z + 5.0f);

				f_Glyph->m_pos = f_VecO;

				Cube::BiColor* f_GreenColour = new Cube::BiColor(0.0f, 1.0f, 0.0f, 1.0f);

				Cube::BiTex* f_TexO = new Cube::BiTex(0.5f, 0.0f);
				Cube::BiTex* f_TexA = new Cube::BiTex(0.0f, 1.0f);
				Cube::BiTex* f_TexB = new Cube::BiTex(1.0f, 1.0f);

				Cube::Index* f_Index = new Cube::Index();

				Cube::BiVector* f_VecN = new Cube::BiVector(0.0f, 1.0f, 0.5f);

				f_VecN->acNormalize();

				f_Index->m_A = 0;
				f_Index->m_B = 1;
				f_Index->m_C = 2;

				f_Glyph->m_vec_Vertex.push_back(f_VecO);
				f_Glyph->m_vec_Vertex.push_back(f_VecA);
				f_Glyph->m_vec_Vertex.push_back(f_VecB);

				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);
				f_Glyph->m_vec_Color.push_back(f_GreenColour);

				f_Glyph->m_vec_Index.push_back(f_Index);

				f_Glyph->m_vec_Tex.push_back(f_TexO);
				f_Glyph->m_vec_Tex.push_back(f_TexA);
				f_Glyph->m_vec_Tex.push_back(f_TexB);

				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);
				f_Glyph->m_vec_Normal.push_back(f_VecN);

				f_Glyph->GenerateBuffers();

				m_vec_Glyph_Trigger.push_back(f_Glyph);

				f_RebuildList = true;
				}
			}
		}

	if(f_RebuildList == true)
		{
		g_RefList.clear();

		for(int f_Jet = 0; f_Jet < f_GlyphList.size(); f_Jet++)
			{
			g_RefList.push_back(f_GlyphList[f_Jet]);
			}
		}

#if 0
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
#else
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);
#endif

#if 0
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
#endif

	glLineWidth(3.0f);

	if(mProgram == 0)
		{
		return false;
		}

	glUseProgram(mProgram);

	for(int f_Ral = 0; f_Ral < m_vec_Glyph_Spawn.size(); f_Ral++)
		{
		Glyph* f_Glyph = m_vec_Glyph_Spawn[f_Ral];

		BiVector f_Pos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);
		BiVector f_VecTo(f_Glyph->m_pos->m_X - f_Pos.m_X, f_Glyph->m_pos->m_Y - f_Pos.m_Y, f_Glyph->m_pos->m_Z - f_Pos.m_Z);

		float f_Dist = f_VecTo.acLength();
		if(f_Dist < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexPositionBuffer);
			glEnableVertexAttribArray(mPositionAttribLocation);
			glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexNormalBuffer);
			glEnableVertexAttribArray(mNormalAttribLocation);
			glVertexAttribPointer(mNormalAttribLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexColorBuffer);
			glEnableVertexAttribArray(mColorAttribLocation);
			glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexTexCoordBuffer);
			glEnableVertexAttribArray(mTexCoordAttribLocation);
			glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Glyph->mIndexBuffer);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
			glDrawElements(GL_LINES, f_Glyph->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
			}
		}

	for(int f_Ral = 0; f_Ral < m_vec_Glyph_Event.size(); f_Ral++)
		{
		Glyph* f_Glyph = m_vec_Glyph_Event[f_Ral];

		BiVector f_Pos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);
		BiVector f_VecTo(f_Glyph->m_pos->m_X - f_Pos.m_X, f_Glyph->m_pos->m_Y - f_Pos.m_Y, f_Glyph->m_pos->m_Z - f_Pos.m_Z);

		float f_Dist = f_VecTo.acLength();
		if(f_Dist < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexPositionBuffer);
			glEnableVertexAttribArray(mPositionAttribLocation);
			glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexNormalBuffer);
			glEnableVertexAttribArray(mNormalAttribLocation);
			glVertexAttribPointer(mNormalAttribLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexColorBuffer);
			glEnableVertexAttribArray(mColorAttribLocation);
			glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexTexCoordBuffer);
			glEnableVertexAttribArray(mTexCoordAttribLocation);
			glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Glyph->mIndexBuffer);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
			glDrawElements(GL_LINES, f_Glyph->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
			}
		}

	for(int f_Ral = 0; f_Ral < m_vec_Glyph_Function.size(); f_Ral++)
		{
		Glyph* f_Glyph = m_vec_Glyph_Function[f_Ral];

		BiVector f_Pos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);
		BiVector f_VecTo(f_Glyph->m_pos->m_X - f_Pos.m_X, f_Glyph->m_pos->m_Y - f_Pos.m_Y, f_Glyph->m_pos->m_Z - f_Pos.m_Z);

		float f_Dist = f_VecTo.acLength();
		if(f_Dist < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexPositionBuffer);
			glEnableVertexAttribArray(mPositionAttribLocation);
			glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexNormalBuffer);
			glEnableVertexAttribArray(mNormalAttribLocation);
			glVertexAttribPointer(mNormalAttribLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexColorBuffer);
			glEnableVertexAttribArray(mColorAttribLocation);
			glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexTexCoordBuffer);
			glEnableVertexAttribArray(mTexCoordAttribLocation);
			glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Glyph->mIndexBuffer);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
			glDrawElements(GL_LINES, f_Glyph->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
			}
		}

	for(int f_Ral = 0; f_Ral < m_vec_Glyph_Variable.size(); f_Ral++)
		{
		Glyph* f_Glyph = m_vec_Glyph_Variable[f_Ral];

		BiVector f_Pos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);
		BiVector f_VecTo(f_Glyph->m_pos->m_X - f_Pos.m_X, f_Glyph->m_pos->m_Y - f_Pos.m_Y, f_Glyph->m_pos->m_Z - f_Pos.m_Z);

		float f_Dist = f_VecTo.acLength();
		if(f_Dist < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexPositionBuffer);
			glEnableVertexAttribArray(mPositionAttribLocation);
			glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexNormalBuffer);
			glEnableVertexAttribArray(mNormalAttribLocation);
			glVertexAttribPointer(mNormalAttribLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexColorBuffer);
			glEnableVertexAttribArray(mColorAttribLocation);
			glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexTexCoordBuffer);
			glEnableVertexAttribArray(mTexCoordAttribLocation);
			glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Glyph->mIndexBuffer);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
			glDrawElements(GL_LINES, f_Glyph->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
			}
		}

	for(int f_Ral = 0; f_Ral < m_vec_Glyph_Trigger.size(); f_Ral++)
		{
		Glyph* f_Glyph = m_vec_Glyph_Trigger[f_Ral];

		BiVector f_Pos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);
		BiVector f_VecTo(f_Glyph->m_pos->m_X - f_Pos.m_X, f_Glyph->m_pos->m_Y - f_Pos.m_Y, f_Glyph->m_pos->m_Z - f_Pos.m_Z);

		float f_Dist = f_VecTo.acLength();
		if(f_Dist < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexPositionBuffer);
			glEnableVertexAttribArray(mPositionAttribLocation);
			glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexNormalBuffer);
			glEnableVertexAttribArray(mNormalAttribLocation);
			glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexColorBuffer);
			glEnableVertexAttribArray(mColorAttribLocation);
			glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, f_Glyph->mVertexTexCoordBuffer);
			glEnableVertexAttribArray(mTexCoordAttribLocation);
			glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Glyph->mIndexBuffer);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
			glDrawElements(GL_LINES, f_Glyph->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
			}
		}
#endif

	return true;
}

};

#if 0
	// Create mesh
void VoxelGrid::CreateMesh(void)
{
    if(mVertexPositionBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexPositionBuffer);
        mVertexPositionBuffer = 0;
		}

    if(mVertexColorBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexColorBuffer);
        mVertexColorBuffer = 0;
		}

	if(mVertexTexCoordBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexTexCoordBuffer);
		mVertexTexCoordBuffer = 0;
		}

    if(mIndexBuffer != 0)
		{
        glDeleteBuffers(1, &mIndexBuffer);
        mIndexBuffer = 0;
		}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	int *l_merged;
	l_merged = new int[VOXEL_GRID_SIZE_CUBED];

	for (unsigned int j = 0; j < VOXEL_GRID_SIZE_CUBED; j++)
		{
		l_merged[j] = MergedSide_None;
		}

	for (int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for (int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for (int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				if (GetActive(x, y, z) == false)
					{
					continue;
					}
				else
					{
					GetColour(x, y, z, &r, &g, &b, &a);

					a = 1.0f;

					BiVector p1(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p2(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p3(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p4(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p5(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					BiVector p6(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					BiVector p7(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					BiVector p8(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					BiVector n1;
					unsigned int v1, v2, v3, v4;
					unsigned int t1, t2, t3, t4;

					bool doXPositive = (IsMergedXPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doXNegative = (IsMergedXNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doYPositive = (IsMergedYPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doYNegative = (IsMergedYNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doZPositive = (IsMergedZPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doZNegative = (IsMergedZNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);

					// Front
					if (doZPositive && ((z == VOXEL_GRID_SIZE - 1) || z < VOXEL_GRID_SIZE - 1 && GetActive(x, y, z + 1) == false))
						{
						bool addSide = true;

						if ((z == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);
							if (pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, y, 0) == false);
								}
							}

						if (addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p1, &p2, &p3, &p4, x, y, endX, endY, true, true, false, false);

							n1 = BiVector(0.0f, 0.0f, 1.0f);
							v1 = AddVertexToMesh(p1, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p2, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p3, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p4, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Back
					if(doZNegative && ((z == 0) || (z > 0 && GetActive(x, y, z - 1) == false)))
						{
						bool addSide = true;

						if((z == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, y, VOXEL_GRID_SIZE - 1) == false);
								}
							}

						if (addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p5, &p8, &p7, x, y, endX, endY, false, true, false, false);

							n1 = BiVector(0.0f, 0.0f, -1.0f);
							v1 = AddVertexToMesh(p5, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p6, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p7, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p8, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Right
					if(doXPositive && ((x == VOXEL_GRID_SIZE - 1) || (x < VOXEL_GRID_SIZE - 1 && GetActive(x + 1, y, z) == false)))
						{
						bool addSide = true;

						if ((x == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(0, y, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p5, &p2, &p3, &p8, z, y, endX, endY, true, false, true, false);

							n1 = BiVector(1.0f, 0.0f, 0.0f);
							v1 = AddVertexToMesh(p2, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p3, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Left
					if(doXNegative && ((x == 0) || (x > 0 && GetActive(x - 1, y, z) == false)))
						{
						bool addSide = true;

						if((x == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(VOXEL_GRID_SIZE - 1, y, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p1, &p4, &p7, z, y, endX, endY, false, false, true, false);

							n1 = BiVector(-1.0f, 0.0f, 0.0f);
							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p1, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p4, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Top
					if(doYPositive && ((y == VOXEL_GRID_SIZE - 1) || (y < VOXEL_GRID_SIZE - 1 && GetActive(x, y + 1, z) == false)))
						{
						bool addSide = true;

						if((y == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, 0, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p7, &p8, &p3, &p4, x, z, endX, endY, true, false, false, true);

							n1 = BiVector(0.0f, 1.0f, 0.0f);
							v1 = AddVertexToMesh(p4, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p3, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Bottom
					if(doYNegative && ((y == 0) || (y > 0 && GetActive(x, y - 1, z) == false)))
						{
						bool addSide = true;

						if((y == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, VOXEL_GRID_SIZE - 1, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p5, &p2, &p1, x, z, endX, endY, false, false, false, true);

							n1 = BiVector(0.0f, -1.0f, 0.0f);
							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p2, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p1, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}
					}
				}
			}
		}

	// Delete the merged array
	delete l_merged;
}
#endif