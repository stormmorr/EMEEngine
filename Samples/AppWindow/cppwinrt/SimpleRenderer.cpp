/*

	unSimpleRenderer - Unification Renderer
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include "SimpleRenderer.h"
#include "MathHelper.h"

#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"

#include "UnSRC\Render\unRenderer\unRenderer.h"

#include "UnSRC\QActiveFramewrk.h"

// These are used by the shader compilation methods.
#include <vector>
#include <iostream>
#include <fstream>

namespace Quantum_Angel
{
	SimpleRenderer* g_SimpleRenderer;
}

using namespace Quantum_Angel;

#define STRING(s) #s

extern QAGE::QActiveFramewrk *QActiveFrameWork;

GLuint CompileShader(GLenum type, const std::string &source)
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

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
#if 0
        throw Exception::CreateException(E_FAIL, ref new Platform::String(errorMessage.c_str()));
#endif
		}

    return shader;
}

GLuint CompileProgram(const std::string &vsSource, const std::string &fsSource)
{
    GLuint program = glCreateProgram();

    if(program == 0)
		{
#if 0
        throw Exception::CreateException(E_FAIL, L"unRenderer Program creation failed");
#endif

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
		}

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

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

#if 0
        throw Exception::CreateException(E_FAIL, ref new Platform::String(errorMessage.c_str()));
#endif
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
		}

    return program;
}

SimpleRenderer::SimpleRenderer()
{
	// Vertex Shader source
    const std::string vs = STRING
		(
		uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform vec4 uColor[4];
		uniform vec3 uPos[4];
		uniform vec2 uUV[4];
		uniform vec3 uCamPos;
		attribute vec2 aVertNom;
		varying vec3 vPosition;
		varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			int f_VNom = int(aVertNom.x);

			vec4 f_ActingPosition = vec4(uPos[f_VNom], 1.0);
			vColor = uColor[f_VNom];
			vUV = uUV[f_VNom];

			vec4 f_CamPos = vec4(uCamPos, 1.0);
			//f_CamPos.z *= -1.0;

			vec4 f_interim = uModelMatrix * f_ActingPosition;

			// interim translation
			
			//f_interim -= f_CamPos;

			vec4 f_WOPlayVec = uProjMatrix * uViewMatrix * f_interim;

			f_WOPlayVec -= f_CamPos;

			//vPosition = f_interim.xyz + uCamPos; //\/wk

			//###f_WOPlayVec.z *= -1.0;

			vPosition = f_WOPlayVec.xyz;

			gl_Position = f_WOPlayVec;

			//vec4 f_interim = vec4(f_ActingPosition, 1.0);

			//vec4 f_Position = uProjMatrix * uViewMatrix * uModelMatrix * f_interim;

			//f_Position -= f_AvatarTransV3; // ? +

			//vPosition = f_Position.xyz;

			//gl_Position = f_Position;
			}
		);

	const std::string vs_point = STRING
		(
		uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform vec4 uColor;
		uniform vec3 uPos[2];
		uniform vec3 uCamPos;
		attribute vec2 aUV;
		varying vec3 vPosition;
		varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			vec4 f_ActingPosition = vec4(uPos[0], 0.0);
			float f_Scale = uPos[1].x;
			vColor = uColor;

			vec4 f_CamPos = vec4(uCamPos, 1.0);
			//f_CamPos *= -1.0;

			vec4 f_interim = uModelMatrix * f_ActingPosition;

			// interim translation
			f_interim -= f_CamPos;

			vec4 f_WOPlayVec = uProjMatrix * uViewMatrix * f_interim;

			//###f_WOPlayVec.z *= -1.0;

			vPosition = f_WOPlayVec.xyz;

			gl_Position = f_WOPlayVec;

			gl_PointSize = f_Scale * 1.0; // 2.0 // 14.5 // 30.5
			}
		);

    // Fragment Shader source
    const std::string fs = STRING
		(
        precision mediump float;
		uniform sampler2D f_texture;
		varying vec3 vPosition;
        varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			vec4 f_Color = texture2D(f_texture, vUV);

			gl_FragColor = f_Color * vColor;
			}
		);

	// Fragment Shader source
    const std::string fs_point = STRING
		(
        precision mediump float;
		uniform sampler2D f_texture;
		varying vec3 vPosition;
        varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			vec4 f_Color = texture2D(f_texture, gl_PointCoord);

			gl_FragColor = f_Color * vColor;
			}
		);

	// Fragment Shader source
    const std::string fs_gor = STRING
		(
        precision mediump float;
		varying vec3 vPosition;
        varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			gl_FragColor = vColor;
			}
		);

    // Set up the shader and its uniform/attribute locations.
    mProgram[0] = CompileProgram(vs, fs);
	mProgram[1] = CompileProgram(vs, fs_gor);
	mProgram[2] = CompileProgram(vs_point, fs_point);

	for(int f_XY = 0; f_XY < 3; f_XY++)
		{
		mCamPosUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "uCamPos");

		mModelUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "uModelMatrix");
		mViewUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "uViewMatrix");
		mProjUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "uProjMatrix");

		mPosUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "uPos");
		mColorUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "uColor");

		if(f_XY <= 1)
			{
			// 4 Verts
			mVertNomAttribLocation[f_XY] = glGetAttribLocation(mProgram[f_XY], "aVertNom");

			// 4 UVs
			mUVUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "uUV");
			}

		if((f_XY == 0) || (f_XY == 2))
			{
			mTextureUniformLocation[f_XY] = glGetUniformLocation(mProgram[f_XY], "f_texture");
			}
		}

	GLfloat vertexVertNomCoords[] =
		{
        0.0f, 0.0f,
        1.0f, 0.0f,
        2.0f, 0.0f,
        3.0f, 0.0f,
		};

	//0.0f, 0.0f,
	//1.0f, 0.0f,
	//2.0f, 0.0f,
	//3.0f, 0.0f,

	//0.0f, 0.0f,
    //2.0f, 0.0f,
    //1.0f, 0.0f,
    //3.0f, 0.0f,

	glGenBuffers(1, &mVertNomBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertNomBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexVertNomCoords), vertexVertNomCoords, GL_STATIC_DRAW);

    short indices[] =
		{
		0, 1, 2,
		1, 2, 3,
		};

	//0, 3, 2,
	//1, 3, 2,

	//0, 2, 1,
	//1, 2, 3,

	//1, 0, 2,
	//2, 1, 3,

	//1, 2, 0,
	//2, 3, 1,

	//1, 0, 2,
	//2, 1, 3,

	//0, 1, 2,
	//1, 2, 3,

	//0, 1, 2,
	//2, 1, 3,

	//0, 2, 1,
	//1, 2, 3,

	//0, 2, 1,
	//2, 0, 3,

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

SimpleRenderer::~SimpleRenderer()
{
    if(mProgram[0] != 0)
		{
        glDeleteProgram(mProgram[0]);

		mProgram[0] = 0;
		}

	if(mProgram[1] != 0)
		{
        glDeleteProgram(mProgram[1]);

		mProgram[1] = 0;
		}

	if(mProgram[2] != 0)
		{
        glDeleteProgram(mProgram[2]);

		mProgram[2] = 0;
		}
}

void SimpleRenderer::acSelect_BlendFunction(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void SimpleRenderer::DrawPoint(float f_X, float f_Y, float f_Z, float f_Red, float f_Green, float f_Blue, float f_Alpha, unsigned int f_Bitmap, float f_Scale)
{
	acSelect_BlendFunction();

	GLfloat vertexPositions[6];
	GLfloat vertexColors[4];

	if(mProgram[2] == 0) return;

	glUseProgram(mProgram[2]);

#if 0
	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
	glUniformMatrix4fv(mModelUniformLocation[2], 1, GL_FALSE, &(modelMatrix.m[0][0]));
#else
	 ////////////////////////////////
	////// Render Player Mesh //////
	glUniformMatrix4fv(mModelUniformLocation[2], 1, GL_FALSE, playerAV[0]->Viewform.mf);
#endif

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
	glUniformMatrix4fv(mViewUniformLocation[2], 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mProjUniformLocation[2], 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	glEnable(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, f_Bitmap);
	glUniform1i(mTextureUniformLocation[2], 0);

	vertexPositions[0] = f_X;
	vertexPositions[1] = f_Y;
	vertexPositions[2] = f_Z * -1.0f;

	vertexPositions[3] = f_Scale;
	vertexPositions[4] = 0.0f;
	vertexPositions[5] = 0.0f;

	vertexColors[0] = f_Red / 255.0f;
	vertexColors[1] = f_Green / 255.0f;
	vertexColors[2] = f_Blue / 255.0f;
	vertexColors[3] = f_Alpha / 255.0f;
	
	glUniform3fv(mPosUniformLocation[2], 2, &(vertexPositions[0]));
	glUniform4fv(mColorUniformLocation[2], 1, &(vertexColors[0]));

	glUniform3f(mCamPosUniformLocation[2], playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	glDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, 0);
}

void SimpleRenderer::DrawTri(QpoVertex* Verts, GLuint f_Bitmap)
{
	acSelect_BlendFunction();

	GLfloat vertexPositions[12];
	GLfloat vertexColors[16];
	GLfloat vertexUV[8];

	if(mProgram[0] == 0) return;

	glUseProgram(mProgram[0]);

	glBindBuffer(GL_ARRAY_BUFFER, mVertNomBuffer);
	glEnableVertexAttribArray(mVertNomAttribLocation[0]);
	glVertexAttribPointer(mVertNomAttribLocation[0], 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

#if 0
	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
	glUniformMatrix4fv(mModelUniformLocation[0], 1, GL_FALSE, &(modelMatrix.m[0][0]));
#else
	 ////////////////////////////////
	////// Render Player Mesh //////
	glUniformMatrix4fv(mModelUniformLocation[0], 1, GL_FALSE, playerAV[0]->Viewform.mf);
#endif

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
	glUniformMatrix4fv(mViewUniformLocation[0], 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mProjUniformLocation[0], 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	glEnable(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, f_Bitmap);
	glUniform1i(mTextureUniformLocation[0], 0);

	int f_IncCount = 0;

	for(int f_XY = 0; f_XY < 4; f_XY++)
		{
		vertexPositions[(f_IncCount * 3)] = Verts[f_IncCount].x;
		vertexPositions[(f_IncCount * 3) + 1] = Verts[f_IncCount].y;
		vertexPositions[(f_IncCount * 3) + 2] = Verts[f_IncCount].z * -1.0f;

		vertexColors[(f_IncCount * 4)] = Verts[f_IncCount].r / 255.0f;
		vertexColors[(f_IncCount * 4) + 1] = Verts[f_IncCount].g / 255.0f;
		vertexColors[(f_IncCount * 4) + 2] = Verts[f_IncCount].b / 255.0f;
		vertexColors[(f_IncCount * 4) + 3] = Verts[f_IncCount].a / 255.0f;

		vertexUV[(f_IncCount * 2)] = Verts[f_IncCount].u;
		vertexUV[(f_IncCount * 2) + 1] = Verts[f_IncCount].v;

		f_IncCount++;
		}

	glUniform3fv(mPosUniformLocation[0], 4, &(vertexPositions[0]));
	glUniform4fv(mColorUniformLocation[0], 4, &(vertexColors[0]));
	glUniform2fv(mUVUniformLocation[0], 4, &(vertexUV[0]));

	glUniform3f(mCamPosUniformLocation[0], playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}

void SimpleRenderer::DrawQuad(QpoVertex* Verts, GLuint f_Bitmap)
{
	acSelect_BlendFunction();

	GLfloat vertexPositions[12];
	GLfloat vertexColors[16];
	GLfloat vertexUV[8];

	if(mProgram[0] == 0) return;

	glUseProgram(mProgram[0]);

	glBindBuffer(GL_ARRAY_BUFFER, mVertNomBuffer);
	glEnableVertexAttribArray(mVertNomAttribLocation[0]);
	glVertexAttribPointer(mVertNomAttribLocation[0], 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

#if 0
	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
	glUniformMatrix4fv(mModelUniformLocation[0], 1, GL_FALSE, &(modelMatrix.m[0][0]));
#else
	////////////////////////////////
   ////// Render Player Mesh //////
	glUniformMatrix4fv(mModelUniformLocation[0], 1, GL_FALSE, playerAV[0]->Viewform.mf);
#endif

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
	glUniformMatrix4fv(mViewUniformLocation[0], 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mProjUniformLocation[0], 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	glEnable(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, f_Bitmap);
	glUniform1i(mTextureUniformLocation[0], 0);

	int f_IncCount = 0;

	for(int f_XY = 0; f_XY < 4; f_XY++)
		{
		vertexPositions[(f_IncCount * 3)] = Verts[f_IncCount].x;
		vertexPositions[(f_IncCount * 3) + 1] = Verts[f_IncCount].y;
		vertexPositions[(f_IncCount * 3) + 2] = Verts[f_IncCount].z * -1.0f;

		vertexColors[(f_IncCount * 4)] = Verts[f_IncCount].r / 255.0f;
		vertexColors[(f_IncCount * 4) + 1] = Verts[f_IncCount].g / 255.0f;
		vertexColors[(f_IncCount * 4) + 2] = Verts[f_IncCount].b / 255.0f;
		vertexColors[(f_IncCount * 4) + 3] = Verts[f_IncCount].a / 255.0f;

		vertexUV[(f_IncCount * 2)] = Verts[f_IncCount].u;
		vertexUV[(f_IncCount * 2) + 1] = Verts[f_IncCount].v;

		f_IncCount++;
		}

	glUniform3fv(mPosUniformLocation[0], 4, &(vertexPositions[0]));
	glUniform4fv(mColorUniformLocation[0], 4, &(vertexColors[0]));
	glUniform2fv(mUVUniformLocation[0], 4, &(vertexUV[0]));

	glUniform3f(mCamPosUniformLocation[0], playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void SimpleRenderer::DrawTriGor(QpoVertex* Verts)
{
	acSelect_BlendFunction();

	GLfloat vertexPositions[12];
	GLfloat vertexColors[16];
	GLfloat vertexUV[8];

	if(mProgram[1] == 0) return;

	glBindBuffer(GL_ARRAY_BUFFER, mVertNomBuffer);
	glEnableVertexAttribArray(mVertNomAttribLocation[1]);
	glVertexAttribPointer(mVertNomAttribLocation[1], 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

#if 0
	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
	glUniformMatrix4fv(mModelUniformLocation[2], 1, GL_FALSE, &(modelMatrix.m[0][0]));
#else
	 ////////////////////////////////
    ////// Render Player Mesh //////
	glUniformMatrix4fv(mModelUniformLocation[1], 1, GL_FALSE, playerAV[0]->Viewform.mf);
#endif

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
	glUniformMatrix4fv(mViewUniformLocation[1], 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mProjUniformLocation[1], 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	int f_IncCount = 0;

	for(int f_XY = 0; f_XY < 4; f_XY++)
		{
		vertexPositions[(f_IncCount * 3)] = Verts[f_IncCount].x;
		vertexPositions[(f_IncCount * 3) + 1] = Verts[f_IncCount].y;
		vertexPositions[(f_IncCount * 3) + 2] = Verts[f_IncCount].z * -1.0f;

		vertexColors[(f_IncCount * 4)] = Verts[f_IncCount].r / 255.0f;
		vertexColors[(f_IncCount * 4) + 1] = Verts[f_IncCount].g / 255.0f;
		vertexColors[(f_IncCount * 4) + 2] = Verts[f_IncCount].b / 255.0f;
		vertexColors[(f_IncCount * 4) + 3] = Verts[f_IncCount].a / 255.0f;

		vertexUV[(f_IncCount * 2)] = Verts[f_IncCount].u;
		vertexUV[(f_IncCount * 2) + 1] = Verts[f_IncCount].v;

		f_IncCount++;
		}

	glUniform3fv(mPosUniformLocation[1], 4, &(vertexPositions[0]));
	glUniform4fv(mColorUniformLocation[1], 4, &(vertexColors[0]));
	glUniform2fv(mUVUniformLocation[1], 4, &(vertexUV[0]));

	glUniform3f(mCamPosUniformLocation[1], playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}

void SimpleRenderer::DrawQuadGor(QpoVertex * Verts)
{
	acSelect_BlendFunction();

	GLfloat vertexPositions[12];
	GLfloat vertexColors[16];
	GLfloat vertexUV[8];

	if(mProgram[1] == 0) return;

	glBindBuffer(GL_ARRAY_BUFFER, mVertNomBuffer);
	glEnableVertexAttribArray(mVertNomAttribLocation[1]);
	glVertexAttribPointer(mVertNomAttribLocation[1], 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

#if 0
	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
	glUniformMatrix4fv(mModelUniformLocation[1], 1, GL_FALSE, &(modelMatrix.m[0][0]));
#else
	////////////////////////////////
   ////// Render Player Mesh //////
	glUniformMatrix4fv(mModelUniformLocation[1], 1, GL_FALSE, playerAV[0]->Viewform.mf);
#endif

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
	glUniformMatrix4fv(mViewUniformLocation[1], 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mProjUniformLocation[1], 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	int f_IncCount = 0;

	for(int f_XY = 0; f_XY < 4; f_XY++)
		{
		vertexPositions[(f_IncCount * 3)] = Verts[f_IncCount].x;
		vertexPositions[(f_IncCount * 3) + 1] = Verts[f_IncCount].y;
		vertexPositions[(f_IncCount * 3) + 2] = Verts[f_IncCount].z * -1.0f;

		vertexColors[(f_IncCount * 4)] = Verts[f_IncCount].r / 255.0f;
		vertexColors[(f_IncCount * 4) + 1] = Verts[f_IncCount].g / 255.0f;
		vertexColors[(f_IncCount * 4) + 2] = Verts[f_IncCount].b / 255.0f;
		vertexColors[(f_IncCount * 4) + 3] = Verts[f_IncCount].a / 255.0f;

		vertexUV[(f_IncCount * 2)] = Verts[f_IncCount].u;
		vertexUV[(f_IncCount * 2) + 1] = Verts[f_IncCount].v;

		f_IncCount++;
		}

	glUniform3fv(mPosUniformLocation[1], 4, &(vertexPositions[0]));
	glUniform4fv(mColorUniformLocation[1], 4, &(vertexColors[0]));
	glUniform2fv(mUVUniformLocation[1], 4, &(vertexUV[0]));

	glUniform3f(mCamPosUniformLocation[1], playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void SimpleRenderer::UpdateWindowSize(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
}