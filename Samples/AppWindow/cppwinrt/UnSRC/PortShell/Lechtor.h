/*

NonStaticArray - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef LECHTOR_H
#define LECHTOR_H

#include <vector>
#include <math.h>

#define LTR_PNT_STATUS_INIT 0
#define LTR_TRI_STATUS_INIT 0
#define LTR_QUAD_STATUS_INIT 0
#define LTR_PNT_STATUS_LIVE 1
#define LTR_TRI_STATUS_LIVE 1
#define LTR_QUAD_STATUS_LIVE 1

#define LTR_PNT_TYPE_TEX 1
#define LTR_TRI_TYPE_TEX 1
#define LTR_QUAD_TYPE_TEX 1
#define LTR_PNT_TYPE_GOR 2
#define LTR_TRI_TYPE_GOR 2
#define LTR_QUAD_TYPE_GOR 2

namespace Quantum_Angel
{

	class Point_NonStaticArray_Element
	{
	public:
		Point_NonStaticArray_Element() { acClear(); };
		~Point_NonStaticArray_Element() { acClear(); }

		void acClear(void)
			{
			m_X = 15000000.0f;
			m_Y = 15000000.0f;
			m_Z = 15000000.0f;
			m_R = 1.0f;
			m_G = 1.0f;
			m_B = 1.0f;
			m_A = 1.0f;
			m_Status = LTR_PNT_STATUS_INIT;
			}

		float m_X;
		float m_Y;
		float m_Z;
		float m_R;
		float m_G;
		float m_B;
		float m_A;
		int m_Status;
		int m_TexType;
		float m_Scale;
		GLuint m_TextureID;
	};

	class Tri_NonStaticArray_Element
	{
	public:
		Tri_NonStaticArray_Element() { acClear(); };
		~Tri_NonStaticArray_Element() { acClear(); }

		void acClear(void)
			{
			m_X1 = 15000000.0f;
			m_Y1 = 15000000.0f;
			m_Z1 = 15000000.0f;
			m_R1 = 1.0f;
			m_G1 = 1.0f;
			m_B1 = 1.0f;
			m_A1 = 1.0f;
			m_X2 = 15000000.0f;
			m_Y2 = 15000000.0f;
			m_Z2 = 15000000.0f;
			m_R2 = 1.0f;
			m_G2 = 1.0f;
			m_B2 = 1.0f;
			m_A2 = 1.0f;
			m_X3 = 15000000.0f;
			m_Y3 = 15000000.0f;
			m_Z3 = 15000000.0f;
			m_R3 = 1.0f;
			m_G3 = 1.0f;
			m_B3 = 1.0f;
			m_A3 = 1.0f;
			m_U1 = 0.0f;
			m_V1 = 0.0f;
			m_U2 = 1.0f;
			m_V2 = 1.0f;
			m_U3 = 1.0f;
			m_V3 = 1.0f;
			m_Status = LTR_TRI_STATUS_INIT;
			}

		float m_X1;
		float m_Y1;
		float m_Z1;
		float m_R1;
		float m_G1;
		float m_B1;
		float m_A1;
		float m_X2;
		float m_Y2;
		float m_Z2;
		float m_R2;
		float m_G2;
		float m_B2;
		float m_A2;
		float m_X3;
		float m_Y3;
		float m_Z3;
		float m_R3;
		float m_G3;
		float m_B3;
		float m_A3;
		float m_U1;
		float m_V1;
		float m_U2;
		float m_V2;
		float m_U3;
		float m_V3;
		int m_Status;
		int m_TexType;
		GLuint m_TextureID;
	};

	class Quad_NonStaticArray_Element
	{
	public:
		Quad_NonStaticArray_Element() { acClear(); };
		~Quad_NonStaticArray_Element() { acClear(); }

		void acClear(void)
			{
			m_X1 = 15000000.0f;
			m_Y1 = 15000000.0f;
			m_Z1 = 15000000.0f;
			m_R1 = 1.0f;
			m_G1 = 1.0f;
			m_B1 = 1.0f;
			m_A1 = 1.0f;
			m_X2 = 15000000.0f;
			m_Y2 = 15000000.0f;
			m_Z2 = 15000000.0f;
			m_R2 = 1.0f;
			m_G2 = 1.0f;
			m_B2 = 1.0f;
			m_A2 = 1.0f;
			m_X3 = 15000000.0f;
			m_Y3 = 15000000.0f;
			m_Z3 = 15000000.0f;
			m_R3 = 1.0f;
			m_G3 = 1.0f;
			m_B3 = 1.0f;
			m_A3 = 1.0f;
			m_X4 = 15000000.0f;
			m_Y4 = 15000000.0f;
			m_Z4 = 15000000.0f;
			m_R4 = 1.0f;
			m_G4 = 1.0f;
			m_B4 = 1.0f;
			m_A4 = 1.0f;
			m_U1 = 0.0f;
			m_V1 = 0.0f;
			m_U2 = 1.0f;
			m_V2 = 0.0f;
			m_U3 = 1.0f;
			m_V3 = 1.0f;
			m_U4 = 1.0f;
			m_V4 = 1.0f;
			m_Status = LTR_QUAD_STATUS_INIT;
			}

		float m_X1;
		float m_Y1;
		float m_Z1;
		float m_R1;
		float m_G1;
		float m_B1;
		float m_A1;
		float m_X2;
		float m_Y2;
		float m_Z2;
		float m_R2;
		float m_G2;
		float m_B2;
		float m_A2;
		float m_X3;
		float m_Y3;
		float m_Z3;
		float m_R3;
		float m_G3;
		float m_B3;
		float m_A3;
		float m_X4;
		float m_Y4;
		float m_Z4;
		float m_R4;
		float m_G4;
		float m_B4;
		float m_A4;
		float m_U1;
		float m_V1;
		float m_U2;
		float m_V2;
		float m_U3;
		float m_V3;
		float m_U4;
		float m_V4;
		int m_Status;
		int m_TexType;
		GLuint m_TextureID;
	};

	class PointNonStaticArrayContainer
	{
	public:
		PointNonStaticArrayContainer(int f_Size)
			{
			acResize(f_Size);
			};
		~PointNonStaticArrayContainer() { acClear(); }

		void acClear(void)
			{
			m_vec_NonStaticArray.clear();
			}

		void acResize(int f_Size)
			{
			acClear();

			for(int f_Int = 0; f_Int < f_Size; f_Int++)
				{
				m_vec_NonStaticArray.push_back(new Point_NonStaticArray_Element());
				}

			m_Size = f_Size;
			}

		void acMap(void);
		void acBuild(void);

		GLuint mProgram;
		
		GLfloat *m_VertexPositionBuff;
		GLfloat *m_VertexColorBuff;
		GLuint *m_IndexBuff;

		int m_Size;
		int m_Nom_Element;

		int m_Status;

		GLuint mVertexPositionBuffer;
		GLuint mVertexColorBuffer;
		GLuint mIndexBuffer;

		GLint mPositionAttribLocation;
		GLint mColorAttribLocation;
		GLint mViewUniformLocation;
		GLint mProjUniformLocation;
		GLint mTextureUniformLocation;
		GLint mScaleUniformLocation;

		std::vector<Point_NonStaticArray_Element*> m_vec_NonStaticArray;
	};

	class TriNonStaticArrayContainer
	{
	public:
		TriNonStaticArrayContainer(int f_Size)
			{
			acResize(f_Size);
			};
		~TriNonStaticArrayContainer() { acClear(); }

		void acClear(void)
			{
			m_vec_NonStaticArray.clear();
			}

		void acResize(int f_Size)
			{
			acClear();

			for(int f_Int = 0; f_Int < f_Size; f_Int++)
				{
				m_vec_NonStaticArray.push_back(new Tri_NonStaticArray_Element());
				}

			m_Size = f_Size;
			}

		void acMap(void);
		void acBuild(void);

		GLuint mProgram;
		
		GLfloat *m_VertexPositionBuff;
		GLfloat *m_VertexColorBuff;
		GLuint *m_IndexBuff;
		GLfloat *m_TexCoordBuff;

		int m_Size;
		int m_Nom_Element;

		int m_Status;

		GLuint mVertexPositionBuffer;
		GLuint mVertexColorBuffer;
		GLuint mIndexBuffer;
		GLuint mTexCoordBuffer;

		GLint mPositionAttribLocation;
		GLint mColorAttribLocation;
		GLint mTexCoordAttribLocation;
		GLint mViewUniformLocation;
		GLint mProjUniformLocation;
		GLint mTextureUniformLocation;

		std::vector<Tri_NonStaticArray_Element*> m_vec_NonStaticArray;
	};

	class QuadNonStaticArrayContainer
	{
	public:
		QuadNonStaticArrayContainer(int f_Size)
			{
			acResize(f_Size);
			};
		~QuadNonStaticArrayContainer() { acClear(); }

		void acClear(void)
			{
			m_vec_NonStaticArray.clear();
			}

		void acResize(int f_Size)
			{
			acClear();

			for(int f_Int = 0; f_Int < f_Size; f_Int++)
				{
				m_vec_NonStaticArray.push_back(new Quad_NonStaticArray_Element());
				}

			m_Size = f_Size;
			}

		void acMap(void);
		void acBuild(void);

		GLuint mProgram;
		
		GLfloat *m_VertexPositionBuff;
		GLfloat *m_VertexColorBuff;
		GLuint *m_IndexBuff;
		GLfloat *m_TexCoordBuff;

		int m_Size;
		int m_Nom_Element;

		int m_Status;

		GLuint mVertexPositionBuffer;
		GLuint mVertexColorBuffer;
		GLuint mIndexBuffer;
		GLuint mTexCoordBuffer;

		GLint mPositionAttribLocation;
		GLint mColorAttribLocation;
		GLint mTexCoordAttribLocation;
		GLint mViewUniformLocation;
		GLint mProjUniformLocation;
		GLint mTextureUniformLocation;

		std::vector<Quad_NonStaticArray_Element*> m_vec_NonStaticArray;
	};

};

#endif