/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -QAGE Port Shell-
	*/#include "pch.h"/*- Minor Component -Function Definitions-

*/

#include <iterator>
#include <iostream>
#include <math.h>

// OpenGL ES includes
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <angle_windowsstore.h>

//*** INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include "Q-PortSHELL-Sound.h"

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"

//***== Include Engine Specific Headers ===##
#pragma message("Server engine excludes")
#if defined(WIN32)
#include "../Texture/tgaload.h"
#endif

#include "unConsole.h"
#include "../Avatar/unAvatar.h"
#include "../QActiveFramewrk.h"
#include "../Element/unElement.h"

using namespace Cube;
using namespace GVARS;
using namespace QAGE;
using namespace Quantum_Angel;
using namespace std;

//*#include "../../DigitalMass/Source/Mesh/digiMesh.h"

extern QAGE::QActiveFramewrk* QActiveFrameWork;

#define CCX_MODE_NULL 0
#define CCX_MODE_POLY 1
#define CCX_MODE_BLIT 2
#define CCX_MODE_DRAW 3
#define CCX_MODE_MESH 4

#define SCALE_IMP 1.75

extern float WeaponvalueX;
extern float WeaponvalueY;
extern float WeaponvalueZ;

#if defined(WIN32)
int m_ChannelPNT;
#endif

#if 0
#define QAGEMODE_SURGERY 1
#define PORTSHELL_ASSERT_DEBUG 1
#endif

namespace QAGE
{
bool g_PlayerForgeBoxxed = false;
}

namespace GVARS
{

///// PortSHELL Class Cache /////
float Q_PORTShell::CC::Cos, Q_PORTShell::CC::Sin, Q_PORTShell::CC::ScaleFT;
pVector Q_PORTShell::CC::pVector1, Q_PORTShell::CC::pResult;
unsigned int Q_PORTShell::CC::m_ExecMode = 55;
int Q_PORTShell::CC::vPort[4];

QpoVec3d Q_PORTShell::CC::campos;
QpoVec3d Q_PORTShell::CC::destpos;
QpoVec3d Q_PORTShell::CC::InVec;
QpoVec3d Q_PORTShell::CC::UpVec;
QpoVec3d Q_PORTShell::CC::LeftVec;
QpoVec3d Q_PORTShell::CC::transvert;

float Q_PORTShell::CC::m_Red;
float Q_PORTShell::CC::m_Green;
float Q_PORTShell::CC::m_Blue;
float Q_PORTShell::CC::m_Alpha;

int vectrans[32];
int vecvar[5];
bool vecvarDpress[5];
float vecvalue[4];

int keyvecvar[5];
int storelockvar[5];

Q_PORTShell::Q_PORTShell()
{
	m_CC.m_ExecMode = CCX_MODE_NULL;

	vecvar[0] = 0;
	vecvar[1] = 0;
	vecvar[2] = 0;
	vecvar[3] = 0;
	vecvar[4] = 0;

	vecvarDpress[0] = false;
	vecvarDpress[1] = false;
	vecvarDpress[2] = false;
	vecvarDpress[3] = false;
	vecvarDpress[4] = false;

	vectrans[0] = 0;
	vectrans[1] = 0;
	vectrans[2] = 0;
	vectrans[3] = 1;
	vectrans[4] = 0;
	vectrans[5] = 2;
	vectrans[6] = 1;
	vectrans[7] = 0;
	vectrans[8] = 1;
	vectrans[9] = 1;
	vectrans[10] = 1;
	vectrans[11] = 2;
	vectrans[12] = 2;
	vectrans[13] = 0;
	vectrans[14] = 2;
	vectrans[15] = 1;
	vectrans[16] = 2;
	vectrans[17] = 2;

	vectrans[18] = 0;
	vectrans[19] = 0;
	vectrans[20] = 0;
	vectrans[21] = 0;
	vectrans[22] = 0;
	vectrans[23] = 0;
	vectrans[24] = 0;
	vectrans[25] = 0;
	vectrans[26] = 0;
	vectrans[27] = 0;
	vectrans[28] = 0;
	vectrans[29] = 0;
	vectrans[30] = 0;
	vectrans[31] = 0;

	vecvalue[0] = 0;
	vecvalue[1] = 0;
	vecvalue[2] = 0;
	vecvalue[3] = 0;

	keyvecvar[0] = 0;
	keyvecvar[1] = 0;
	keyvecvar[2] = 0;
	keyvecvar[3] = 0;
	keyvecvar[4] = 0;
	storelockvar[0] = 0;
	storelockvar[1] = 0;
	storelockvar[2] = 0;
	storelockvar[3] = 0;
	storelockvar[4] = 0;

	m_ChannelPNT = 0;
}

#ifndef PS_ASM
void Q_PORTShell::Vec3d_AddScaled(QpoVec3d * vec1, float scale, QpoVec3d * dir, QpoVec3d * result)
	{
	assert( Qpo->Vec3d_IsValid(vec1) != false );
	assert( Qpo->Vec3d_IsValid(dir) != false );
	assert ( result != NULL );

	result->x = vec1->x + dir->x*scale;
	result->y = vec1->y + dir->y*scale;
	result->z = vec1->z + dir->z*scale;
	}
#else
void Q_PORTShell::Vec3d_AddScaled(QpoVec3d * vec1, float scale, QpoVec3d * dir, QpoVec3d * result)
{
	QpoVec3d					scale_vector;
	QpoVec3d					*s = &scale_vector;

	//s->Pad = 0.0f;
	s->x = scale;
	s->y = scale;
	s->z = scale;

	_asm {
		mov					esi, vec1
		mov					edi, dir
		mov					ecx, s

		movups				xmm0, [esi]
		movups				xmm1, [edi]
		movups				xmm2, [ecx]

		addps				xmm0, xmm1
		movaps				xmm3, xmm0

		mulps				xmm3, xmm2

		mov					edx, result
		movups				[edx], xmm3
	}
}
#endif

#ifndef PS_ASM
void Q_PORTShell::Vec3d_Subtract(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result)
	{
	result->x = vec1->x - vec2->x;
	result->y = vec1->y - vec2->y;
	result->z = vec1->z - vec2->z;
	}
#else
void Q_PORTShell::Vec3d_Subtract(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result)
{
	_asm {
		mov					esi, vec1
		mov					edi, vec2

		movups				xmm0, [esi]
		movups				xmm1, [edi]

		subps				xmm0, xmm1

		mov					ecx, result
		movups				[ecx], xmm0
	}
}
#endif

#ifndef PS_ASM
float Q_PORTShell::Vec3d_Length(QpoVec3d * vec1)
	{
	return (float)sqrt(Qpo->Vec3d_DotProduct(vec1, vec1));
	}
#else
float Q_PORTShell::Vec3d_Length(QpoVec3d * vec1)
{
	float					result;
	float					*r = &result;

	_asm {
		mov					esi, vec1
		mov					ecx, r

		movups				xmm0, [esi]
		mulps				xmm0, xmm0
		movaps				xmm1, xmm0

		shufps				xmm1, xmm1, 4Eh

		addps				xmm0, xmm1
		movaps				xmm1, xmm0

		shufps				xmm1, xmm1, 11h
		
		addps				xmm0, xmm1
		sqrtss				xmm0, xmm0
		movss				[ecx], xmm0
	}

	return result;
}
#endif

#if 1
#ifndef PS_ASM
float Q_PORTShell::Vec3d_Normalize(QpoVec3d * V1)
	{
	float *fPtr;
	float Dist,OneOverDist;
		
	fPtr = (float *)V1;
	Dist =  (*fPtr) * (*fPtr); fPtr++;
	Dist += (*fPtr) * (*fPtr); fPtr++;
	Dist += (*fPtr) * (*fPtr);

	// Vtune shows the float <-> double conversions
	// required for the clib sqrt() are taking a lot of time.
	// hence we use asm to access the float fsqrt() directly

#if 0
	__asm 
	{
		FLD Dist
		FSQRT
		FSTP Dist
	}
#endif

	Dist = sqrt(Dist);

	if ( Dist == 0.0f )
		return 0.0f;

	OneOverDist = 1.0f/Dist;
			
	fPtr = (float *)V1;
	*fPtr *= OneOverDist; fPtr++;
	*fPtr *= OneOverDist; fPtr++;
	*fPtr *= OneOverDist;

	return (float)Dist;
	}
#else
void Q_PORTShell::Vec3d_Normalize(QpoVec3d * V1)
{
	//V1->Pad = 0.0f;

	_asm {
		mov					esi, V1
		movups				xmm0, [esi]
		movaps				xmm2, xmm0
		mulps				xmm0, xmm0
		movaps				xmm1, xmm0
		shufps				xmm1, xmm1, 4Eh
		addps				xmm0, xmm1
		movaps				xmm1, xmm0
		shufps				xmm1, xmm1, 11h
		addps				xmm0, xmm1

		rsqrtps				xmm0, xmm0		;reciprocal square root
		mulps				xmm2, xmm0
		movups				[esi], xmm2
	}
}
#endif
#else
float Q_PORTShell::Vec3d_Normalize(QpoVec3d * V1)
{
	float len = V1->x * V1->x + V1->y * V1->y + V1->z * V1->z;
	if(len > 0)
		{
		len = 1.0f / sqrtf(len);
		V1->x *= len; V1->y *= len; V1->z *= len;
		}
	return len;
}
#endif

#ifndef PS_ASM
float Q_PORTShell::Vec3d_DotProduct(QpoVec3d *vec1, QpoVec3d *vec2)
	{
	return(vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z);
	}
#else
float Q_PORTShell::Vec3d_DotProduct(QpoVec3d *vec1, QpoVec3d *vec2)
{
	float					res;
	float					*r = &res;

	_asm 
	{
		mov					ecx, r
		mov					esi, vec1
		mov					edi, vec2

		movups				xmm0, [esi]
		movups				xmm1, [edi]
	
		mulps				xmm0, xmm1

		movaps				xmm2, xmm0
		shufps				xmm2, xmm2, 4Eh
		addps				xmm0, xmm2
		movaps				xmm2, xmm0
		shufps				xmm2, xmm2, 11h
		addps				xmm0, xmm2

		movss				[ecx], xmm0
	}

	return res;
}
#endif

#ifndef PS_ASM
void Q_PORTShell::Vec3d_CrossProduct(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result)
	{
	result->x = vec1->y*vec2->z - vec1->z*vec2->y;
    result->y = vec1->z*vec2->x - vec1->x*vec2->z;
    result->z = vec1->x*vec2->y - vec1->y*vec2->x;
	}
#else
void Q_PORTShell::Vec3d_CrossProduct(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result)
{
	_asm {
		mov					esi, vec1
		mov					edi, vec2

		movups				xmm0, [esi]
		movups				xmm1, [edi]
		movaps				xmm2, xmm0
		movaps				xmm3, xmm1

		shufps				xmm0, xmm0, 0xc9
		shufps				xmm1, xmm1, 0xd2
		mulps				xmm0, xmm1

		shufps				xmm2, xmm2, 0xd2
		shufps				xmm3, xmm3, 0xc9
		mulps				xmm2, xmm3

		subps				xmm0, xmm2

		mov					esi, result
		movups				[esi], xmm0
	}
}
#endif

void Q_PORTShell::Vec3d_Inverse(QpoVec3d * vec1)
	{
	vec1->x *= -1.0f;
	vec1->y *= -1.0f;
	vec1->z *= -1.0f;
	}

#ifndef PS_ASM
float Q_PORTShell::Vec3d_DistanceBetween(QpoVec3d * vec1, QpoVec3d * vec2)
	{
	QpoVec3d result;

	result.x = vec1->x - vec2->x;
	result.y = vec1->y - vec2->y;
	result.z = vec1->z - vec2->z;

	return Qpo->Vec3d_Length(&result);
	}
#else
float Q_PORTShell::Vec3d_DistanceBetween(QpoVec3d * vec1, QpoVec3d * vec2)
{
	float					result;
	float					*r = &result;

	_asm {
		mov					esi, vec1
		mov					edi, vec2
		mov					ecx, r

		movups				xmm0, [esi]
		movups				xmm1, [edi]
		
		subps				xmm0, xmm1
		movaps				xmm3, xmm0

		mulps				xmm3, xmm3
		movaps				xmm4, xmm3

		shufps				xmm4, xmm4, 4Eh

		addps				xmm3, xmm4
		movaps				xmm4, xmm3

		shufps				xmm4, xmm4, 11h
		
		addps				xmm3, xmm4
		sqrtss				xmm3, xmm3
		movss				[ecx], xmm3
	}

	return result;
}
#endif

void Q_PORTShell::Vec3d_New(QpoVec3d * vec1)
	{
	vec1->x = 0;
	vec1->y = 0;
	vec1->z = 0;
	}

void Q_PORTShell::Vec3d_Set(QpoVec3d * vec1, float x, float y, float z)
	{
	vec1->x = x;
	vec1->y = y;
	vec1->z = z;
	}

void Q_PORTShell::Vec3d_Copy(QpoVec3d * vec1, QpoVec3d * vec2)
	{
	*vec2 = *vec1;
	}

#ifndef PS_ASM
void Q_PORTShell::Vec3d_Scale(QpoVec3d * vec1, float scale, QpoVec3d * result)
	{
	result->x = vec1->x * scale;
	result->y = vec1->y * scale;
	result->z = vec1->z * scale;
	}
#else
void Q_PORTShell::Vec3d_Scale(QpoVec3d * vec1, float scale, QpoVec3d * result)
{
	QpoVec3d					scale_vector;
	QpoVec3d					*s = &scale_vector;

	s->x = scale;
	s->y = scale;
	s->z = scale;
	//s->Pad = 0.0f;

	_asm {
		mov					esi, vec1
		mov					edi, s

		movups				xmm0, [esi]
		movups				xmm1, [edi]

		mulps				xmm0, xmm1

		mov					ecx, result
		movups				[ecx], xmm0
	}
}
#endif

#ifndef PS_ASM
void Q_PORTShell::Vec3d_Add(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result)
	{
	result->x = vec1->x + vec2->x;
	result->y = vec1->y + vec2->y;
	result->z = vec1->z + vec2->z;
	}
#else
void Q_PORTShell::Vec3d_Add(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result)
{
	_asm {
		mov					esi, vec1
		mov					edi, vec2

		movups				xmm0, [esi]
		movups				xmm1, [edi]

		addps				xmm0, xmm1

		mov					ecx, result
		movups				[ecx], xmm0
	}
}
#endif

bool Q_PORTShell::Vec3d_Compare(QpoVec3d *V1, QpoVec3d *V2, float Tolerance)
	{
	assert( V1 != NULL );
	assert( V2 != NULL );
	assert( Tolerance >= 0.0 );
	assert( Qpo->Vec3d_IsValid(V1) != false );
	assert( Qpo->Vec3d_IsValid(V2) != false );

	if(fabs(V2->x - V1->x) > Tolerance) //VCOMPARE_EPSILON)
		return false;
	if(fabs(V2->y - V1->y) > Tolerance) //VCOMPARE_EPSILON)
		return false;
	if(fabs(V2->z - V1->z) > Tolerance) //VCOMPARE_EPSILON)
		return false;

	return true;
	}

bool Q_PORTShell::Vec3d_IsValid(QpoVec3d *V)
	{
	if(V == NULL)
		return false;
	if((V->x * V->x) < 0.0f) 
		return false;
	if((V->y * V->y) < 0.0f) 
		return false;
	if((V->z * V->z) < 0.0f) 
		return false;

	return true;
	}

void Q_PORTShell::Transform_New(QpoTransform * transform)
	{
	transform->Matrix.load_identity();

	transform->Translation.x = transform->Translation.y = transform->Translation.z = 0.0f;
	}

void Q_PORTShell::Transform_Copy(const QpoTransform *Src, QpoTransform *Dst)
	{
#ifdef PORTSHELL_ASSERT_DEBUG
	geXForm3d_Assert ( geXForm3d_IsOrthogonal(Src) == GE_true );
#endif

	*Dst = *Src;
	}

void Q_PORTShell::Transform_Print(QpoTransform * transform)
	{
	printf("Transform Row 1 [0][0] %f [0][1] %f [0][2] %f [0][3] %f\n", transform->Matrix.m[0][0], transform->Matrix.m[0][1], transform->Matrix.m[0][2], transform->Matrix.m[0][3]);
	printf("Transform Row 2 [1][0] %f [1][1] %f [1][2] %f [1][3] %f\n", transform->Matrix.m[1][0], transform->Matrix.m[1][1], transform->Matrix.m[1][2], transform->Matrix.m[1][3]);
	printf("Transform Row 3 [2][0] %f [2][1] %f [2][2] %f [2][3] %f\n", transform->Matrix.m[2][0], transform->Matrix.m[2][1], transform->Matrix.m[2][2], transform->Matrix.m[2][3]);
	printf("Transform Row 4 [3][0] %f [3][1] %f [3][2] %f [3][3] %f\n", transform->Matrix.m[3][0], transform->Matrix.m[3][1], transform->Matrix.m[3][2], transform->Matrix.m[3][3]);
	printf("Transform Translation x %f y %f z %f\n", transform->Translation.x, transform->Translation.y, transform->Translation.z);
	}

bool Q_PORTShell::Transform_TestIdentity(QpoTransform & transform)
	{
	double Epsilon1_a = 1-Q_EPSILON;
	double Epsilon1_b = 1+Q_EPSILON;

	if(transform.Matrix.m[0][0] < Epsilon1_a || transform.Matrix.m[0][0] > Epsilon1_b || 
		transform.Matrix.m[1][0] < -Q_EPSILON || transform.Matrix.m[1][0] > Q_EPSILON || 
		transform.Matrix.m[2][0] < -Q_EPSILON || transform.Matrix.m[2][0] > Q_EPSILON)
		return false;
	if(transform.Matrix.m[0][1] < -Q_EPSILON || transform.Matrix.m[0][1] > Q_EPSILON ||
		transform.Matrix.m[1][1] < Epsilon1_a || transform.Matrix.m[1][1] > Epsilon1_b ||
		transform.Matrix.m[2][1] < -Q_EPSILON || transform.Matrix.m[2][1] > Q_EPSILON)
		return false;
	if(-transform.Matrix.m[0][2] < -Q_EPSILON || -transform.Matrix.m[0][2] > Q_EPSILON ||
		-transform.Matrix.m[1][2] < -Q_EPSILON || -transform.Matrix.m[1][2] > Q_EPSILON ||
		-transform.Matrix.m[2][2] < Epsilon1_a || -transform.Matrix.m[2][2] > Epsilon1_b)
		return false;

	// reset them a little

	transform.Matrix.m[0][0] = 1;
	transform.Matrix.m[1][0] = 0;
	transform.Matrix.m[2][0] = 0;

	transform.Matrix.m[0][1] = 0;
	transform.Matrix.m[1][1] = 1;
	transform.Matrix.m[2][1] = 0;

	transform.Matrix.m[0][2] = 0;
	transform.Matrix.m[1][2] = 0;
	transform.Matrix.m[2][2] = -1;

	return true;
	}

#if 0
inline void Q_PORTShell::Transform_New_XRotation(QpoTransform * transform, float RadianAngle)
	{
	transform->Matrix.setOrientation( nvmath::Quatf(nvmath::Vec3f(1.0f, 0.0f, 0.0f ), RadianAngle) );
	//transform->setTrafo(trafo);
	}

inline void Q_PORTShell::Transform_New_YRotation(QpoTransform * transform, float RadianAngle)
	{
	transform->Matrix.setOrientation( nvmath::Quatf(nvmath::Vec3f(0.0f, 1.0f, 0.0f ), RadianAngle) );
	//transform->setTrafo(trafo);
	}

inline void Q_PORTShell::Transform_New_ZRotation(QpoTransform * transform, float RadianAngle)
	{
	transform->Matrix.setOrientation( nvmath::Quatf(nvmath::Vec3f(0.0f, 0.0f, 1.0f ), RadianAngle) );
	//transform->setTrafo(trafo);
	}
#endif

void Q_PORTShell::Transform_New_XRotation(QpoTransform * transform, float RadianAngle)
	// sets up a transform that rotates RadianAngle about X axis
{
#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform->Matrix != NULL );
	assert( RadianAngle * RadianAngle >= 0.0f );
#endif

	m_CC.Cos = (float)cos(RadianAngle);
	m_CC.Sin = (float)sin(RadianAngle);

#if 0
	transform->Matrix.m[1][1] =  m_CC.Cos;
	transform->Matrix.m[1][2] = -m_CC.Sin;
	transform->Matrix.m[2][1] =  m_CC.Sin;
	transform->Matrix.m[2][2] =  m_CC.Cos;
	transform->Matrix.m[0][0] = 1.0f;
	transform->Matrix.m[0][1] = transform->Matrix.m[0][2] = transform->Matrix.m[1][0] = transform->Matrix.m[2][0] = 0.0f;
	transform->Translation.x = transform->Translation.y = transform->Translation.z = 0.0f;
#endif

	transform->Matrix.m[1][1] = m_CC.Cos;
	transform->Matrix.m[1][2] = -m_CC.Sin;
	transform->Matrix.m[2][1] = m_CC.Sin;
	transform->Matrix.m[2][2] = m_CC.Cos;
	transform->Matrix.m[0][0] = 1.0f;
	transform->Matrix.m[0][1] = transform->Matrix.m[0][2] = transform->Matrix.m[1][0] = transform->Matrix.m[2][0] = 0.0f;
	transform->Translation.x = transform->Translation.y = transform->Translation.z = 0.0f;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Transform_IsOrthogonal(transform) == true );
#endif
}

void Q_PORTShell::Transform_New_YRotation(QpoTransform * transform, float RadianAngle)
	// sets up a transform that rotates RadianAngle about Y axis
{
#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform->Matrix != NULL );
	assert( RadianAngle * RadianAngle >= 0.0f );
#endif

	m_CC.Cos = (float)cos(RadianAngle);
	m_CC.Sin = (float)sin(RadianAngle);

	transform->Matrix.m[0][0] =  m_CC.Cos;
	transform->Matrix.m[0][2] =  m_CC.Sin;
	transform->Matrix.m[2][0] = -m_CC.Sin;
	transform->Matrix.m[2][2] =  m_CC.Cos;
	transform->Matrix.m[1][1] = 1.0f;
	transform->Matrix.m[0][1] = transform->Matrix.m[1][0] = transform->Matrix.m[1][2] = transform->Matrix.m[2][1] = 0.0f;
	transform->Matrix.m[0][3] = transform->Matrix.m[1][3] = transform->Matrix.m[2][3] = transform->Matrix.m[3][3] = transform->Matrix.m[3][2] = transform->Matrix.m[3][1] = transform->Matrix.m[3][0] = 0.0f;
	transform->Translation.x = transform->Translation.y = transform->Translation.z = 0.0f;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Transform_IsOrthogonal(transform) == true );
#endif
}

void Q_PORTShell::Transform_New_ZRotation(QpoTransform * transform, float RadianAngle)
	// sets up a transform that rotates RadianAngle about Z axis
{
#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform->Matrix != NULL );
	assert( RadianAngle * RadianAngle >= 0.0f );
#endif

	m_CC.Cos = (float)cos(RadianAngle);
	m_CC.Sin = (float)sin(RadianAngle);

	transform->Matrix.m[0][0] =  m_CC.Cos;
	transform->Matrix.m[0][1] = -m_CC.Sin;
	transform->Matrix.m[1][0] =  m_CC.Sin;
	transform->Matrix.m[1][1] =  m_CC.Cos;
	transform->Matrix.m[2][2] = 1.0f;
	transform->Matrix.m[0][2] = transform->Matrix.m[1][2] = transform->Matrix.m[2][0] = transform->Matrix.m[2][1] = 0.0f;
	transform->Translation.x = transform->Translation.y = transform->Translation.z = 0.0f;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Transform_IsOrthogonal(transform) == true );
#endif
}

void Q_PORTShell::Transform_New_LeftUpIn(QpoTransform  *transform, QpoVec3d * left, QpoVec3d * up, QpoVec3d * in)
	{
	transform->Matrix.load_identity();

	transform->Matrix.m[0][2] = -left->x;
	transform->Matrix.m[2][2] = -left->y;
	transform->Matrix.m[1][2] = -left->z;
	transform->Matrix.m[0][1] =  up->x;
	transform->Matrix.m[2][1] =  up->y;
	transform->Matrix.m[1][1] =  up->z;
	transform->Matrix.m[0][0] = -in->x;
	transform->Matrix.m[2][0] = -in->y;
	transform->Matrix.m[1][0] = -in->z;

	transform->Translation.x = 0;
	transform->Translation.y = 0;
	transform->Translation.z = 0;
	}

/// ~~~ IMPORTANT SPEED LOSS HERE ~~~~~~~~ LOSE EXTRA TRANSFORMS
void Q_PORTShell::Transform_Multiply(QpoTransform * transform1, QpoTransform * transform2, QpoTransform * result)
	{
	result->Matrix = transform1->Matrix * transform2->Matrix;
	}

void Q_PORTShell::Transform_Translate(QpoTransform * transform, float x, float y, float z)
	{
	transform->Translation.x += x;
	transform->Translation.y += y;
	transform->Translation.z += z;
	}

void Q_PORTShell::Transform_GetIn(QpoTransform * transform, QpoVec3d * result)
	// Gets a vector that is 'in' in the frame of reference of transform->Matrix.getMatrix() (facing -Z)
	{
	result->x = -transform->Matrix.m[1][1];
	result->y = -transform->Matrix.m[2][1];
	result->z = -transform->Matrix.m[0][1];
	}

void Q_PORTShell::Transform_GetLeft(QpoTransform * transform, QpoVec3d * result)
	// Gets a vector that is 'left' in the frame of reference of transform->Matrix.getMatrix() (facing -Z)
	{
	result->x = -transform->Matrix.m[1][2];
	result->y = -transform->Matrix.m[2][2];
	result->z = -transform->Matrix.m[0][2];
	}

void Q_PORTShell::Transform_GetRight(QpoTransform * transform, QpoVec3d * result)
	// Gets a vector that is 'left' in the frame of reference of transform->Matrix.getMatrix() (facing -Z)
	{
	result->x = transform->Matrix.m[0][2];
	result->y = transform->Matrix.m[2][2];
	result->z = transform->Matrix.m[1][2];
	}

void Q_PORTShell::Transform_GetUp(QpoTransform * transform, QpoVec3d * result)
	// Gets a vector that is 'up' in the frame of reference of transform->Matrix.getMatrix() (facing -Z)
	{
	result->x = transform->Matrix.m[1][0];
	result->y = transform->Matrix.m[2][0];
	result->z = transform->Matrix.m[0][0];
	}

void Q_PORTShell::Transform_GetIn(pMatrix * transform, QpoVec3d * result)
	// Gets a vector that is 'in' in the frame of reference of Matrix.getMatrix() (facing -Z)
	{
	result->x = -transform->m[1][1];
	result->y = -transform->m[2][1];
	result->z = -transform->m[0][1];
	}

void Q_PORTShell::Transform_GetLeft(pMatrix * transform, QpoVec3d * result)
	// Gets a vector that is 'left' in the frame of reference of Matrix.getMatrix() (facing -Z)
	{
	result->x = transform->m[0][2] * -1;
	result->z = transform->m[2][2] * -1;
	result->y = transform->m[1][2] * -1;
	}

void Q_PORTShell::Transform_GetUp(pMatrix * transform, QpoVec3d * result)
	// Gets a vector that is 'up' in the frame of reference of Matrix.getMatrix() (facing -Z)
	{
	result->x = transform->m[1][0];
	result->y = transform->m[2][0];
	result->z = transform->m[0][0];
	}

void Q_PORTShell::Transform_Orthonormalize(QpoTransform * transform)
	{
#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform != NULL );
	assert ( Qpo->Transform_IsValid(transform) == true );
#endif

	transform->Matrix.orthonormalize();

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Qpo->Transform_IsOrthonormal(transform) == true );
#endif
	}

void Q_PORTShell::Transform_SetTranslation(QpoTransform * transform, float x, float y, float z)
	{
	transform->Translation.x = x;
	transform->Translation.y = y;
	transform->Translation.z = z;
	}

void Q_PORTShell::Transform_RotateX(QpoTransform * transform, float RadianAngle)
	{
	QpoTransform R;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform != NULL );
	assert( RadianAngle * RadianAngle >= 0.0f );
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );
#endif

	Qpo->Transform_New_XRotation(&R,RadianAngle);
	Qpo->Transform_Multiply(&R, transform, transform);

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );
#endif
	}

void Q_PORTShell::Transform_RotateY(QpoTransform * transform, float RadianAngle)
	{
	QpoTransform R;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform != NULL );
	assert( RadianAngle * RadianAngle >= 0.0f );
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );
#endif

	Qpo->Transform_New_YRotation(&R,RadianAngle);
	Qpo->Transform_Multiply(&R, transform, transform);

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );
#endif
	}

void Q_PORTShell::Transform_RotateZ(QpoTransform * transform, float RadianAngle)
	{
	QpoTransform R;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform != NULL );
	assert( RadianAngle * RadianAngle >= 0.0f );
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );
#endif

	Qpo->Transform_New_ZRotation(&R,RadianAngle);
	Qpo->Transform_Multiply(&R, transform, transform);

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );
#endif
	}

void Q_PORTShell::Transform_RotateVector(QpoTransform * transform, QpoVec3d * vec, QpoVec3d * result)
	{
#ifdef PORTSHELL_ASSERT_DEBUG
	assert( transform != NULL );
	assert( result != NULL );
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );
	assert( Qpo->Vec3d_IsValid(vec)!=false);
#endif

	m_CC.pVector1.x = vec->x;
	m_CC.pVector1.y = vec->y;
	m_CC.pVector1.z = vec->z;

	m_CC.pResult = m_CC.pVector1 * transform->Matrix;

	result->x = m_CC.pResult.x;
	result->y = m_CC.pResult.y;
	result->z = m_CC.pResult.z;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert( Qpo->Vec3d_IsValid(result)!=false);
#endif
	}

void Q_PORTShell::Transform_Mirror(QpoTransform * source, QpoVec3d * planenormal, float planedist, QpoTransform * result)
	{
	//...
	}

void Q_PORTShell::Transform_Transpose(const QpoTransform *M, QpoTransform *MInv)
{
	QpoTransform M1;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert(Transform_IsOrthogonal(M) == true);
#endif

	M1 = *M;

	MInv->Matrix.m[0][0] = M1.Matrix.m[0][0];
	MInv->Matrix.m[0][1] = M1.Matrix.m[1][0];
	MInv->Matrix.m[0][2] = M1.Matrix.m[2][0];

	MInv->Matrix.m[1][0] = M1.Matrix.m[0][1];
	MInv->Matrix.m[1][1] = M1.Matrix.m[1][1];
	MInv->Matrix.m[1][2] = M1.Matrix.m[2][1];

	MInv->Matrix.m[2][0] = M1.Matrix.m[0][2];
	MInv->Matrix.m[2][1] = M1.Matrix.m[1][2];
	MInv->Matrix.m[2][2] = M1.Matrix.m[2][2];

	MInv->Translation.x = 0.0f;
	MInv->Translation.y = 0.0f;
	MInv->Translation.z = 0.0f;

	QpoTransform T;
	Transform_SetTranslation(&T,-M1.Translation.x,-M1.Translation.y,-M1.Translation.z);
	Transform_Multiply(MInv,&T,MInv);

#ifdef PORTSHELL_ASSERT_DEBUG
	assert(Transform_IsOrthogonal(MInv) == true);
#endif
}

void Q_PORTShell::Transform_TransposeVector(QpoTransform  *transform, QpoVec3d * V, QpoVec3d *Result)
{
	QpoVec3d V1;

	assert( transform != NULL );
	assert( Qpo->Vec3d_IsValid(V)!=false);

	assert( Result != NULL );
	assert ( Qpo->Transform_IsOrthogonal(transform) == true );

	V1.x = V->x - transform->Translation.x;
	V1.y = V->y - transform->Translation.y;
	V1.z = V->z - transform->Translation.z;

	Result->x = (V1.x * transform->Matrix.m[0][0]) + (V1.y * transform->Matrix.m[1][0]) + (V1.z * transform->Matrix.m[2][0]);
	Result->y = (V1.x * transform->Matrix.m[0][1]) + (V1.y * transform->Matrix.m[1][1]) + (V1.z * transform->Matrix.m[2][1]);
	Result->z = (V1.x * transform->Matrix.m[0][2]) + (V1.y * transform->Matrix.m[1][2]) + (V1.z * transform->Matrix.m[2][2]);

	assert( Qpo->Vec3d_IsValid(Result)!=false);
}

bool Q_PORTShell::Transform_IsOrthonormal(QpoTransform * transform)
{
	QpoVec3d Col1,Col2,Col3;
	QpoVec3d Col1CrossCol2;
	bool IsOrthonormal;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Qpo->Transform_IsValid(transform) == true );
#endif

	Col1.x = transform->Matrix.m[0][0];
	Col1.y = transform->Matrix.m[1][0];
	Col1.z = transform->Matrix.m[2][0];
	
	Col2.x = transform->Matrix.m[0][1];
	Col2.y = transform->Matrix.m[1][1];
	Col2.z = transform->Matrix.m[2][1];

	Col3.x = transform->Matrix.m[0][2];
	Col3.y = transform->Matrix.m[1][2];
	Col3.z = transform->Matrix.m[2][2];

	Qpo->Vec3d_CrossProduct(&Col1,&Col2,&Col1CrossCol2);

	IsOrthonormal = Qpo->Vec3d_Compare(&Col1CrossCol2, &Col3, ORTHONORMAL_TOLERANCE);

	if(IsOrthonormal == false)
		{
		Qpo->Vec3d_Inverse(&Col3);
		IsOrthonormal = Qpo->Vec3d_Compare(&Col1CrossCol2, &Col3, ORTHONORMAL_TOLERANCE);
		}

	if(Qpo->Vec3d_IsValid(&(transform->Translation)) == false)
		{
		return false;
		}

	return IsOrthonormal;
}

bool Q_PORTShell::Transform_IsOrthogonal(QpoTransform * transform)
{
	QpoVec3d Col1,Col2,Col3;
	QpoVec3d Col1CrossCol2;
	bool IsOrthogonal;

	assert(Qpo->Transform_IsValid(transform) == true);

	Col1.x = transform->Matrix.m[0][0];
	Col1.y = transform->Matrix.m[1][0];
	Col1.z = transform->Matrix.m[2][0];
	
	Col2.x = transform->Matrix.m[0][1];
	Col2.y = transform->Matrix.m[1][1];
	Col2.z = transform->Matrix.m[2][1];
	
	Col3.x = transform->Matrix.m[0][2];
	Col3.y = transform->Matrix.m[1][2];
	Col3.z = transform->Matrix.m[2][2];

	Qpo->Vec3d_Normalize(&Col3);

	Qpo->Vec3d_CrossProduct(&Col1,&Col2,&Col1CrossCol2);

	Qpo->Vec3d_Normalize(&Col1CrossCol2);

	IsOrthogonal = Qpo->Vec3d_Compare(&Col1CrossCol2,&Col3,ORTHOGONAL_TOLERANCE);

	if(IsOrthogonal == false)
		{
		Qpo->Vec3d_Inverse(&Col3);
		IsOrthogonal = Qpo->Vec3d_Compare(&Col1CrossCol2,&Col3,ORTHOGONAL_TOLERANCE);
		}

	if(Qpo->Vec3d_IsValid(&(transform->Translation)) == false)
		return false;

	return IsOrthogonal;
}

bool Q_PORTShell::Transform_IsValid(QpoTransform * transform)
{
	if (transform == NULL)
		return false;
	if (Qpo->Vec3d_IsValid(&(transform->Translation)) == false)
		return false;

	if ((transform->Matrix.m[0][0] * transform->Matrix.m[0][0]) < 0.0f)
		return false;
	if ((transform->Matrix.m[0][1] * transform->Matrix.m[0][1]) < 0.0f)
		return false;
	if ((transform->Matrix.m[0][2] * transform->Matrix.m[0][2]) < 0.0f)
		return false;

	if ((transform->Matrix.m[1][0] * transform->Matrix.m[1][0]) < 0.0f)
		return false;
	if ((transform->Matrix.m[1][1] * transform->Matrix.m[1][1]) < 0.0f)
		return false;
	if ((transform->Matrix.m[1][2] * transform->Matrix.m[1][2]) < 0.0f)
		return false;
	
	if ((transform->Matrix.m[2][0] * transform->Matrix.m[2][0]) < 0.0f)
		return false;
	if ((transform->Matrix.m[2][1] * transform->Matrix.m[2][1]) < 0.0f)
		return false;
	if ((transform->Matrix.m[2][2] * transform->Matrix.m[2][2]) < 0.0f)
		return false;

	return true;
}

// Poly_Once addonce polyonce addpoly add_poly poly once add poly
bool Q_PORTShell::Poly_AddOnce(QpoVertex * Verts, int NumVerts, unsigned int Bitmap, UInt8 TypeFLAGS, UInt8 RendFLAGS, float Scale)
{
#if 0
	return false;
#endif

	 // Poly
	//
	QpoVec3d f_Here;
	QpoVec3d f_VecTo;

	f_Here.x = Verts[0].x;
	f_Here.y = Verts[0].y;
	f_Here.z = Verts[0].z;

	float f_Length;

	Qpo->Vec3d_Subtract(&f_Here, &playerAV[0]->Xform.Translation, &f_VecTo);

	f_Length = Qpo->Vec3d_Length(&f_VecTo);

	if(f_Length <= 900)
		{
		if(TypeFLAGS == QPOLY_TYPE_PNT)
			{
			Quantum_Angel::mCubeRenderer->DrawPoint(Verts[0].x, Verts[0].y, Verts[0].z, Verts[0].r / 255.0f, Verts[0].g / 255.0f, Verts[0].b / 255.0f, Verts[0].a / 255.0f, Bitmap, Scale);
			}
		}

	return true;
}

QpoPolygon * Q_PORTShell::Poly_Add(QpoVertex *Verts, int NumVerts, unsigned int Bitmap, QInt TypeFLAGS, QInt RendFLAGS, float Scale)
{
#if 0
	//##==-- POLY
	QCH.PolySTAY[QCH.NomPOLY].POLY = QPOLY_POLY_STAY;

	//##==-- TYPE
	if(NumVerts == 1 || TypeFLAGS == 0) { QCH.PolySTAY[QCH.NomPOLY].TYPE = QPOLY_TYPE_PNT; }
	if(TypeFLAGS == 1)					{ QCH.PolySTAY[QCH.NomPOLY].TYPE = QPOLY_TYPE_TRI; }
	if(TypeFLAGS == 2)					{ QCH.PolySTAY[QCH.NomPOLY].TYPE = QPOLY_TYPE_GOR; }

	//##==-- REND
	QCH.PolySTAY[QCH.NomPOLY].REND = RendFLAGS;

	//##==-- VERTS
	QCH.PolySTAY[QCH.NomPOLY].VERT = Verts;

	//##==-- TEX
	//QCH.PolySTAY[QCH.NomPOLY].TEXID = Engine->GetMaterialList()->Find(Bitmap);
	QCH.PolySTAY[QCH.NomPOLY].TEX = Bitmap;

	//##==-- SCALE
	QCH.PolySTAY[QCH.NomPOLY].SCALE = Scale;

	QCH.NomPOLY++;

#pragma message ("FIXME::: return exit function on poly reference in QCH engine to prevent replication-")
#endif

	bool h_OK = Poly_AddOnce(Verts, NumVerts, Bitmap, TypeFLAGS, RendFLAGS, Scale);

	QpoPolygon* FROZENFIX = new QpoPolygon();

	return FROZENFIX;
}

void Q_PORTShell::Draw_FillRect(const QpoRect *Rect, const QpoColor *Color)
{
	m_CC.setExecMode(CCX_MODE_DRAW);
}

void Q_PORTShell::Body_GetBone(QpoBody * Body, int BoneIndex, const char **BoneName, QpoTransform * Attachment, int * ParBone)
{
	//FROZEN
}

void Q_PORTShell::Light_Remove(QpoLight light)
{
	g_Light[(int)light].m_ON = false;
	Q_Nom_Light--;
}

QpoLight Q_PORTShell::Light_AddtoWorld(QpoVec3d pos)
{
	int f_Count = 0;
	int f_Return = -1;
	int f_QLightNom = 0;
	int f_QLightProgNom = 0;
	bool f_Scan = true;
	while(f_Scan)
		{
		if(f_Return < 0)
			{
			if(!(g_Light[f_Count].m_ON) || (g_Light[f_Count].m_Radius <= 0.0f))
				{
				g_Light[f_Count].m_ON = true;
				g_Light[f_Count].m_Pos = pos;
				g_Light[f_Count].m_Radius = 150.0f;
				f_Return = f_Count;
				}
			else
				{
				if(f_Count >= Q_Nom_Light)
					{
					f_Return = Q_Nom_Light;
					g_Light[Q_Nom_Light].m_ON = true;
					g_Light[Q_Nom_Light].m_Pos = pos;
					g_Light[Q_Nom_Light].m_Radius = 150.0f;
					Q_Nom_Light++;
					}
				}

			f_QLightNom++;
			f_QLightProgNom = f_Count + 1;
			}
		else
			{
			if(f_Count >= Q_Nom_Light)
				{
				f_Scan = false;
				Q_Nom_Light = f_QLightProgNom;
				Q_Nom_Light_Orig = f_QLightNom;
				}
			else
				{
				if(g_Light[f_Count].m_ON && (g_Light[f_Count].m_Radius > 0.0f))
					{
					f_QLightNom++;
					f_QLightProgNom = f_Count + 1;
					}
				}
			}

		f_Count++;
		}

#if 0
	printf("Q_PORTShell::Light_AddtoWorld-:%i\n", f_Return);
#endif

	return f_Return;
}

void Q_PORTShell::Light_SetAttr(QpoLight Light, QpoVec3d *Pos, QpoColor *RGBA, float Radius, bool CastShadow)
	{
	g_Light[Light].m_Pos = *(Pos);
	g_Light[Light].m_Color = *(RGBA);
	g_Light[Light].m_Radius = Radius;
	}

#pragma message("Server engine excludes")
bool Q_PORTShell::Sound_Init(void)
	{
	std::string f_ref_CurrentPath = g_ref_global_start + "Q_COREFunctions::InitSounds";

	ag_StatusLive(f_ref_CurrentPath, "g_MediaReader");
	g_MediaReader = std::make_shared_reflect<MediaReader>();

	ag_StatusLive(f_ref_CurrentPath, "g_Audio");
	g_Audio = std::make_shared_reflect<Audio>();

	g_Audio->Initialize();

    return 0;
}

void Q_PORTShell::Sound_Capture_Start(void)
{

}

bool Q_PORTShell::Sound_Capture_Progress(void)
{

	return true;
}

float *Q_PORTShell::Sound_Capture_Get(void)
{
	/// Convert sample to float ///
	float *i_FloatSample = new float[QPO_CAPTURE_RATE];

	return i_FloatSample;
}

winrt::Windows::Storage::StorageFile g_StorageFile({ nullptr });

void Q_PORTShell::Sound_Load(QpoSoundDef* f_Stream, const char * Name, const char * File)
{
	g_Complete = false;

	 //////////////////////
	// Position Control
	*(f_Stream) = g_StreamIndex;
	g_StreamIndex++;

	std::string root = to_string(winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path());
	std::string f_path = root + "\\Assets\\WavFiles";
	winrt::hstring path = StrUsingStr(f_path);

	std::string f_str = f_path + File;

	Concurrency::create_task(winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path)).then([f_Stream, File, f_str](Concurrency::task<winrt::Windows::Storage::StorageFolder> folderTk)
		{
		try
			{
			winrt::Windows::Storage::StorageFolder folder = folderTk.get();

#if 0
			printf("folder Assets::Searching for %s\n", f_str.c_str());
#endif

			Concurrency::create_task(folder.GetFileAsync(StrUsingStr(File))).then([f_Stream, File, f_str](Concurrency::task<winrt::Windows::Storage::StorageFile> f_StorageFileTk)
				{
				try
					{
					winrt::Windows::Storage::StorageFile f_file = f_StorageFileTk.get();

					if(f_file != nullptr)
						{
						g_Stream[*(f_Stream)] = g_MediaReader->LoadMedia(StrUsingStr(f_str));

#if 0
						printf("QLOADED SOUND %s\n", File);
#endif
						}
					}
				catch (...)
					{
					int i = 1;
					}
				});
			}
		catch (...)
			{
			int i = 1;
			}
		});
}

void Q_PORTShell::Sound_Load_Play(QpoSoundDef* f_Stream, const char * Name, const char * File, float f_Volume)
{
	g_Complete = false;

	bool f_Play = false;
	for(int f_Helly = 0; f_Helly < g_StreamGuide.size(); f_Helly++)
		{
		if(*(f_Stream) == g_StreamGuide[f_Helly])
			{
			f_Helly = g_StreamGuide.size();

			Qpo->Sound_Play_Default(*(f_Stream), f_Volume);

			f_Play = true;
			}
		}

	if(f_Play == false)
		{
		 //////////////////////
		// Position Control
		*(f_Stream) = g_StreamIndex;
		g_StreamIndex++;

		std::string root = to_string(winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path());
		std::string f_path = root + "\\Assets\\WavFiles";
		winrt::hstring path = StrUsingStr(f_path);

		std::string f_str = f_path + File;

		Concurrency::create_task(winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path)).then([f_Stream, File, f_Volume, f_str](Concurrency::task<winrt::Windows::Storage::StorageFolder> folderTk)
			{
			try
				{
				winrt::Windows::Storage::StorageFolder folder = folderTk.get();

#if 0
				printf("folder Assets::Searching for %s\n", f_str.c_str());
#endif
		
				Concurrency::create_task(folder.GetFileAsync(StrUsingStr(File))).then([f_Stream, File, f_Volume, f_str](Concurrency::task<winrt::Windows::Storage::StorageFile> f_StorageFileTk)
					{
					try
						{
						winrt::Windows::Storage::StorageFile f_file = f_StorageFileTk.get();

						if(f_file != nullptr)
							{
							g_Stream[*(f_Stream)] = g_MediaReader->LoadMedia(StrUsingStr(f_str));

#if 0
							printf("QLOADED SOUND AND PLAYING %s\n", File);
#endif

							g_StreamGuide.push_back(*(f_Stream));

							Qpo->Sound_Play_Default(*(f_Stream), f_Volume);
							}
						}
					catch (...)
						{
						int i = 1;
						}
					});
				}
			catch (...)
				{
				int i = 1;
				}
			});
		}
}

void Q_PORTShell::Sound_Process(void)
	{
	//...
	}

int Q_PORTShell::Sound_FindSource(void)
	{
	for(int i_Iter = 0; i_Iter < 32; i_Iter++)
		{
		if(_->SoundQueue[i_Iter] == 0) return i_Iter;
		}

	return -1;
	}

QpoSound Q_PORTShell::Sound_Play(QpoSoundDef SoundDef, float Volume, float Pan, float Pitch, bool Loop, QpoVec3d * Position)
	{
	std::vector<::byte> f_inputvector = g_Stream[SoundDef];

	std::shared_ptr<SoundEffect> f_SoundEffect = std::make_shared_reflect<SoundEffect>();

	QpoVec3d f_Aerials = playerAV[g_Player]->Xform.Translation;
	QpoVec3d f_VecTo;
	float f_LengthVecTo;
	int f_LengthFINT1, f_LengthFINTMIX;
	Uint8 f_LengthInt, f_LengthMix;

	f_Aerials.y += (75 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));

	Qpo->Vec3d_Subtract(Position, &f_Aerials, &f_VecTo);
	f_LengthVecTo = Qpo->Vec3d_Length(&f_VecTo);

	float f_SetVolume = (1 - (f_LengthVecTo / 500));

	f_SoundEffect->Initialize(g_Audio->MusicEngine(), g_MediaReader->GetOutputWaveFormatEx(), f_inputvector);

	f_SoundEffect->PlaySound(f_SetVolume);

	return m_ChannelPNT;
	}

QpoSound Q_PORTShell::Sound_Play_Default(QpoSoundDef SoundDef, float Volume)
	{
	std::vector<::byte> f_inputvector = g_Stream[SoundDef];

	std::shared_ptr<SoundEffect> f_SoundEffect = std::make_shared_reflect<SoundEffect>();

	f_SoundEffect->Initialize(g_Audio->MusicEngine(), g_MediaReader->GetOutputWaveFormatEx(), f_inputvector);

	f_SoundEffect->PlaySound(Volume);

	return m_ChannelPNT;
	}

QpoSound Q_PORTShell::Sound_Play_Effect(QpoSoundDef SoundDef, float Volume, float Pan, float Pitch, bool Loop, QpoVec3d * Position, bool i_RefreshEFX)
	{
	return 0;
	}

bool Q_PORTShell::Sound_SetEffect(unsigned int i_Source, bool i_Refresh)
	{
	return true;
	}

void Q_PORTShell::Sound_ClearEffect(void)
	{
	//...
	}

void Q_PORTShell::Sound_Stop(QpoSound Sound)
	{
	//...
	}

void Q_PORTShell::Sound_Modify(QpoSound Sound, float Volume, float Pan, float Pitch, QpoVec3d * Position, QpoVec3d * Velocity)
	{
	//...
	}

void Q_PORTShell::Sound_Close(QpoSoundDef SoundDef)
	{
	//...
	}

void Q_PORTShell::Sound_Shutdown(void)
	{
	//...
	}

unsigned int Q_PORTShell::Tex_LoadTexture(unsigned short Flags, const char * File)
	{
	switch(Flags)
		{
		case 0:			// LOAD - TGA image
			{
			unsigned int f_Int = QActiveFrameWork->m_texturebank->GLloadTGA(File);

#if 0
			printf("Loaded %i Texture %s\n", f_Int, File);
#endif

			return f_Int;

			} break;

		case 1:			// LOAD - PNG image
			{

			return 0;

			} break;
		}

	return 0;
	}

unsigned int Q_PORTShell::Tex_LoadAlphaTexture(const char * File, const char * Name, int color_key)
	{
	return 1;
	}

void Q_PORTShell::Tex_Blit(unsigned int i_texture, QpoRect *Brushrect, int x, int y)
	{
	//FROZEN
	}

void Q_PORTShell::Tex_BlitAlpha(unsigned int lpBitmap, int nX, int nY, DWORD dwWidth, DWORD dwHeight, float fAlpha, float fU, float fV, int RED, int GREEN, int BLUE )
	{
	//FROZEN
	}

void Q_PORTShell::Tex_RemoveE(unsigned int Texture)
	{
	//FROZEN
	}

void Q_PORTShell::Tex_RemoveW(unsigned int Texture)
	{
	//FROZEN
	}

void Q_PORTShell::Tex_Delete(unsigned int Texture)
	{
	glDeleteTextures(1, &Texture);
	}

bool Q_PORTShell::Collision_Make_DMGSphere(QpoVec3d *Center, float f_Radius, float f_Power)
{
	Cube::BiVector f_Center(Center->x, Center->y, Center->z);

	bool f_Collide = false;

	g_VoxMuti.lock();
	g_VoxelGridManager->m_Voxel_Muti.lock();

	for(int i = 0; i < g_VoxelGridManager->m_VoxelGridsVector.size(); i++)
		{
		VoxelGrid* f_Grid = g_VoxelGridManager->m_VoxelGridsVector[i];

		int* f_IntX = new int();
		int* f_IntY = new int();
		int* f_IntZ = new int();
		*(f_IntX) = 0;
		*(f_IntY) = 0;
		*(f_IntZ) = 0;

		f_Collide = f_Grid->Make_ApplyDamageSphere(f_Center, f_Radius * 5.0f, (f_Power * 0.5f) + 10.0f, f_Grid->m_gridX, 0, f_Grid->m_gridZ, f_IntX, f_IntY, f_IntZ);
		}

	g_VoxMuti.unlock();
	g_VoxelGridManager->m_Voxel_Muti.unlock();

	return f_Collide;
}

bool Q_PORTShell::Collision_RayTest(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Back, QpoVec3d *Front, int UserFlags, bool Collision, bool *Context, QpoCollision *Col)
{
	Cube::BiVector front(Front->x, Front->y, Front->z);
	Cube::BiVector back(Back->x, Back->y, Back->z);

	bool f_Collide = false;

	g_VoxMuti.lock();

	VoxelGrid* f_backGrid = nullptr;
	int f_backint = -1;

	for(int i = 0; i < g_VoxelGridManager->m_VoxelGridsVector.size(); i++)
		{
		VoxelGrid* f_Grid = g_VoxelGridManager->m_VoxelGridsVector[i];

		if((back.m_X >= ((float)f_Grid->m_gridX * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_X < (((float)f_Grid->m_gridX + 1) * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Y >= ((float)f_Grid->m_gridY * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Y < (((float)f_Grid->m_gridY + 1) * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Z >= ((float)f_Grid->m_gridZ * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Z < (((float)f_Grid->m_gridZ + 1) * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))))
			{
			f_backGrid = f_Grid;
			f_backint = i;
			}
		}

	VoxelGrid* f_frontGrid = nullptr;
	int f_frontint = -1;

	for(int i = 0; i < g_VoxelGridManager->m_VoxelGridsVector.size(); i++)
		{
		VoxelGrid* f_Grid = g_VoxelGridManager->m_VoxelGridsVector[i];

		if((back.m_X >= ((float)f_Grid->m_gridX * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_X < (((float)f_Grid->m_gridX + 1) * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Y >= ((float)f_Grid->m_gridY * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Y < (((float)f_Grid->m_gridY + 1) * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Z >= ((float)f_Grid->m_gridZ * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(back.m_Z < (((float)f_Grid->m_gridZ + 1) * (Cube::VoxelGrid::VOXEL_GRID_SIZE * (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))))
			{
			f_frontGrid = f_Grid;
			f_frontint = i;
			}
		}

	if((f_backint >= 0) && (f_frontint >= 0))
		{ //both in a grid
		if(f_backint == f_frontint)
			{ //both the same
			BiVector* f_ImpactPoint = new BiVector(0.0f, 0.0f, 0.0f);

			f_Collide = f_frontGrid->CollideMarchPoint(front, back, f_frontGrid->m_gridX, f_frontGrid->m_gridY, f_frontGrid->m_gridZ, f_ImpactPoint);

			if(f_Collide)
				{	
				Col->Impact.x = f_ImpactPoint->m_X;
				Col->Impact.y = f_ImpactPoint->m_Y;
				Col->Impact.z = f_ImpactPoint->m_Z;

#if 0
				Col->Avatar = 0;
#endif

				Col->Plane.Dist = 0;
				Col->Plane.Normal.x = 0;
				Col->Plane.Normal.y = 1;
				Col->Plane.Normal.z = 0;

				g_VoxMuti.unlock();

				return true;
				}
			}
		else
			{ //both in different grid run both combine results
			BiVector* f_ImpactPointback = new BiVector(0.0f, 0.0f, 0.0f);

			f_Collide = f_backGrid->CollideMarchPoint(front, back, f_backGrid->m_gridX, f_backGrid->m_gridY, f_backGrid->m_gridZ, f_ImpactPointback);

			if(f_Collide)
				{	
				Col->Impact.x = f_ImpactPointback->m_X;
				Col->Impact.y = f_ImpactPointback->m_Y;
				Col->Impact.z = f_ImpactPointback->m_Z;

#if 0
				Col->Avatar = 0;
#endif

				Col->Plane.Dist = 0;
				Col->Plane.Normal.x = 0;
				Col->Plane.Normal.y = 1;
				Col->Plane.Normal.z = 0;

				g_VoxMuti.unlock();

				return true;
				}

			BiVector* f_ImpactPointfront = new BiVector(0.0f, 0.0f, 0.0f);

			f_Collide = f_frontGrid->CollideMarchPoint(front, back, f_frontGrid->m_gridX, f_frontGrid->m_gridY, f_frontGrid->m_gridZ, f_ImpactPointfront);

			if(f_Collide)
				{	
				Col->Impact.x = f_ImpactPointfront->m_X;
				Col->Impact.y = f_ImpactPointfront->m_Y;
				Col->Impact.z = f_ImpactPointfront->m_Z;

#if 0
				Col->Avatar = 0;
#endif

				Col->Plane.Dist = 0;
				Col->Plane.Normal.x = 0;
				Col->Plane.Normal.y = 1;
				Col->Plane.Normal.z = 0;

				g_VoxMuti.unlock();

				return true;
				}
			}
		}
	else
		{
		if((f_backint == -1) && (f_frontint == -1))
			{
			g_VoxMuti.unlock();

			return false;
			}
		else
			{
			if(f_backint >= 0)
				{
				BiVector* f_ImpactPoint = new BiVector(0.0f, 0.0f, 0.0f);

				f_Collide = f_backGrid->CollideMarchPoint(front, back, f_backGrid->m_gridX, f_backGrid->m_gridY, f_backGrid->m_gridZ, f_ImpactPoint);

				if(f_Collide)
					{	
					Col->Impact.x = f_ImpactPoint->m_X;
					Col->Impact.y = f_ImpactPoint->m_Y;
					Col->Impact.z = f_ImpactPoint->m_Z;

#if 0
					Col->Avatar = 0;
#endif

					Col->Plane.Dist = 0;
					Col->Plane.Normal.x = 0;
					Col->Plane.Normal.y = 1;
					Col->Plane.Normal.z = 0;

					g_VoxMuti.unlock();

					return true;
					}
				}
			else
				{
				BiVector* f_ImpactPoint = new BiVector(0.0f, 0.0f, 0.0f);

				f_Collide = f_frontGrid->CollideMarchPoint(front, back, f_frontGrid->m_gridX, f_frontGrid->m_gridY, f_frontGrid->m_gridZ, f_ImpactPoint);

				if(f_Collide)
					{	
					Col->Impact.x = f_ImpactPoint->m_X;
					Col->Impact.y = f_ImpactPoint->m_Y;
					Col->Impact.z = f_ImpactPoint->m_Z;

#if 0
					Col->Avatar = 0;
#endif

					Col->Plane.Dist = 0;
					Col->Plane.Normal.x = 0;
					Col->Plane.Normal.y = 1;
					Col->Plane.Normal.z = 0;

					g_VoxMuti.unlock();

					return true;
					}
				}
			}
		}

	g_VoxMuti.unlock();

	return false;
}

bool Q_PORTShell::CheckLineBox(QpoVec3d B1, QpoVec3d B2, QpoVec3d L1, QpoVec3d L2, QpoVec3d* Hit)
{
    if (L2.x < B1.x && L1.x < B1.x) return false;
    if (L2.x > B2.x && L1.x > B2.x) return false;
    if (L2.y < B1.y && L1.y < B1.y) return false;
    if (L2.y > B2.y && L1.y > B2.y) return false;
    if (L2.z < B1.z && L1.z < B1.z) return false;
    if (L2.z > B2.z && L1.z > B2.z) return false;
    if (L1.x > B1.x && L1.x < B2.x &&
        L1.y > B1.y && L1.y < B2.y &&
        L1.z > B1.z && L1.z < B2.z)
		{
        *Hit = L1;
        return true;
		}

    if ((GetIntersection(L1.x - B1.x, L2.x - B1.x, L1, L2, Hit) && InBox(Hit, B1, B2, 1))
      || (GetIntersection(L1.y - B1.y, L2.y - B1.y, L1, L2, Hit) && InBox(Hit, B1, B2, 2))
      || (GetIntersection(L1.z - B1.z, L2.z - B1.z, L1, L2, Hit) && InBox(Hit, B1, B2, 3))
      || (GetIntersection(L1.x - B2.x, L2.x - B2.x, L1, L2, Hit) && InBox(Hit, B1, B2, 1))
      || (GetIntersection(L1.y - B2.y, L2.y - B2.y, L1, L2, Hit) && InBox(Hit, B1, B2, 2))
      || (GetIntersection(L1.z - B2.z, L2.z - B2.z, L1, L2, Hit) && InBox(Hit, B1, B2, 3)))
        return true;

    return false;
}

bool Q_PORTShell::GetIntersection(float fDst1, float fDst2, QpoVec3d P1, QpoVec3d P2, QpoVec3d* Hit)
{
    if ((fDst1 * fDst2) >= 0.0f) return false;
    if (fDst1 == fDst2) return false;
	QpoVec3d f_P2MinusP1;
	Qpo->Vec3d_Subtract(&P2, &P1, &f_P2MinusP1);
	float f_Dist = (-fDst1 / (fDst2 - fDst1));
    Hit->x = P1.x + f_P2MinusP1.x * f_Dist;
	Hit->y = P1.y + f_P2MinusP1.y * f_Dist;
	Hit->z = P1.z + f_P2MinusP1.z * f_Dist;
    return true;
}

bool Q_PORTShell::InBox(QpoVec3d* Hit, QpoVec3d B1, QpoVec3d B2, int Axis)
{
    if (Axis == 1 && Hit->z > B1.z && Hit->z < B2.z && Hit->y > B1.y && Hit->y < B2.y) return true;
    if (Axis == 2 && Hit->z > B1.z && Hit->z < B2.z && Hit->x > B1.x && Hit->x < B2.x) return true;
    if (Axis == 3 && Hit->x > B1.x && Hit->x < B2.x && Hit->y > B1.y && Hit->y < B2.y) return true;
    return false;
}

bool Q_PORTShell::Collision_RayTest_Avatar(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Front, QpoVec3d *Rear, int UserFlags, bool Collision, bool *Context, QpoCollision *Col, int f_AvID, bool f_Impactor)
{
	return false;
}

bool Q_PORTShell::Collision_RayTest_Projectile(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Front, QpoVec3d *Rear, int UserFlags, bool Collision, bool *Context, QpoCollision *Col)
{
#if defined(ENABLE_PX_PHYSICS)
#if 1
#if 1
	float distance;
	PxVec3 i_impact;
	bool f_result = QActiveFrameWork->DigiMass->acRayCollider(Col, PxVec3(Front->x,Front->y,Front->z), PxVec3(Rear->x,Rear->y,Rear->z), i_impact, distance);
#else
	bool f_result;
	float distance;
	pVector i_impact;
	pFace* i_Face = _->mesh->octree.ray_intersect(pVector(Front->x, Front->y, Front->z), pVector(Rear->x,Rear->y,Rear->z), i_impact, distance);
	if(i_Face == 0) f_result = false;
	else f_result = true;
#endif

	Col->Impact.x = i_impact.x;
	Col->Impact.y = i_impact.y;
	Col->Impact.z = i_impact.z;
	//Col->Avatar = 0;

	Col->Plane.Dist = 0;
	Col->Plane.Normal.x = 0;//i_Face->face_normal.x;
	Col->Plane.Normal.y = 1;//i_Face->face_normal.y;
	Col->Plane.Normal.z = 0;//i_Face->face_normal.z;

	//Col->Plane.Dist = 0;
	//Col->Plane.Normal.x = 0;
	//Col->Plane.Normal.y = 1;
	//Col->Plane.Normal.z = 0;
#endif
#pragma message("FIXME optimise ray picker for try concave selection")
#if 1
	/*Col->m_HitAvatar = false;
	if(!(((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x) > (Front->x + 25)) || ((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x) < (Front->x - 25))) &&
	!(((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y) > (Front->y + 25)) || ((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y) < (Front->y - 25))) &&
	!(((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z) > (Front->z + 25)) || ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z) < (Front->z - 25))))
		{
		//Col->Avatar = playerAV[g_Player]->Avatar;
		Col->m_AvatarID = -1;
		Col->m_HitAvatar = true;
		return true;
		}*/

	Col->m_AvatarID = 0;
	Col->m_HitAvatar = false;
#endif

#if 0
	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[SCRAM].AV.Xform.Translation, &Front->x) < 2)
			if(!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Mins.x) > (Front->x + 25)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Maxs.x) < (Front->x - 25))) &&
			!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Mins.y) > (Front->y + 25)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Maxs.y) < (Front->y - 25))) &&
			!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Mins.z) > (Front->z + 25)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Maxs.z) < (Front->z - 25))))
				{
				Col->m_AvatarID = SCRAM;
				Col->m_HitAvatar = true;
				return true;
				}
			}
		SCRAM++;
		}
#endif

	//Col->Plane.Normal.x = 0;
	//Col->Plane.Normal.y = 1;
	//Col->Plane.Normal.z = 0;

	if(f_result)
		{
		QpoVec3d i_ray, i_dest;

		Vec3d_Subtract(Rear, Front, &i_ray);
		Vec3d_Subtract(&Col->Impact, Front, &i_dest);

		if((Vec3d_Length(&i_dest) <= Vec3d_Length(&i_ray))) return true;
		else return false;
		}
#endif

	return false;
	}

void Q_PORTShell::Avatar_BlendPose(QpoAvatar Avatar, int Motion, float Time, QpoTransform * Transform, float BlendAmount)
{
#ifndef QAGEMODE_SURGERY
	if(Avatar.Mesh->m_BoneStructure == 0)
		{
		if(storelockvar[2])
			{
			Avatar.Mesh->acSetPose();
			}
		else
			{
			if(storelockvar[0])
				{
				Avatar.Mesh->BlendAnimPhysicsSurgery(Motion, Time, BlendAmount);

#if 0
				Avatar.Mesh->BlendAnimPhysics(Motion, Time, BlendAmount);
#endif

				Avatar.Mesh->acSetPoseSurgery();
				}
			else
				{
				if(storelockvar[1])
					{
					Avatar.Mesh->BlendAnimPhysicsProp(Motion, Time, BlendAmount);
					Avatar.Mesh->acSetPose();
					}
				else
					{
					Avatar.Mesh->BlendAnim(Motion, Time, BlendAmount);
					Avatar.Mesh->BlendAnimPhysics(Motion, Time, BlendAmount);
					}
				}
			}

#if 0
		if(Avatar.Mesh->m_digiBodyMesh)
			{
			Avatar.Mesh->m_digiBodyMesh->acUpdate(0);

			//Avatar.Mesh->m_digiBodyMesh->acCollide(m_trrCell->vec_Model[1]);
			//printf("collision results size() %i\n", m_trrCell->vec_Model[0]->_tree->m_rets.size());

			Camera_Set();

			Avatar.Mesh->m_digiBodyMesh->acRenderBody(0, 1);
			}
#endif
		}
	else
		{
		if(Avatar.Mesh->m_BoneStructure == -1)
			{
			Avatar.Mesh->BlendAnim(Motion, Time, BlendAmount);
			}
		else
			{
			if(Q_Forge->Forge[Avatar.Mesh->m_BoneStructure - 1].HB_Dead == 0)
				{
#if 0
				Avatar.Mesh->BlendAnimMin(Motion, Time, BlendAmount);
#endif
				Avatar.Mesh->BlendAnim(Motion, Time, BlendAmount);
				Avatar.Mesh->BlendAnimPhysics(Motion, Time, BlendAmount);
				}
			else Avatar.Mesh->acSetPose();
			}
		}

#if 0
	if(KEY_DOWN(QIN_b))
		{
		Avatar.Mesh->acPrintBoneAbsPos(47);
		Avatar.Mesh->acPrintBoneAbsPos(51);
		}

	if(KEY_DOWN(QIN_v))
		{
		Avatar.Mesh->acPrintBonePos(47);
		Avatar.Mesh->acPrintBonePos(51);
		}
#endif

#else
	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();
	Avatar.Mesh->ClearAnimPhysics();
#endif
}

void Q_PORTShell::Avatar_SetPosePM(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown)
	{
#if 1	//SURGERY
	Avatar.Mesh->ApplyAnim(Motion, Count, 1);
#endif
	}

void Q_PORTShell::Avatar_SetPose_LeftLeg(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown)
	{
#if 1	//SURGERY
	Avatar.Mesh->Animate_LeftLeg(Motion, Count, 1);
#endif
	}

void Q_PORTShell::Avatar_SetPose_RightLeg(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown)
	{
#if 1	//SURGERY
	Avatar.Mesh->Animate_RightLeg(Motion, Count, 1);
#endif
	}

void Q_PORTShell::Avatar_SetPose_LeftArm(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown)
	{
#if 1	//SURGERY
	Avatar.Mesh->Animate_LeftArm(Motion, Count, 1);
#endif
	}

void Q_PORTShell::Avatar_SetPose_RightArm(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown)
	{
#if 1	//SURGERY
	Avatar.Mesh->Animate_RightArm(Motion, Count, 1);
#endif
	}

void Q_PORTShell::Avatar_SetPoseAP(QpoAvatar * Avatar, QpoMotion Motion, float Count, QpoTransform * transform)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_SetPivot(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown)
	{
	Avatar.Mesh->Animate_Pivot(Motion, Count, 1);
	}

void Q_PORTShell::Avatar_AddtoWorld(QpoAvatar * Avatar, Uint32 UserFlags)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_Attach(QpoAvatar * Slave, const char *SlaveBoneName, QpoAvatar * Master, const char *MasterBoneName, QpoTransform * attachment)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_SetBoneAttach(QpoAvatar * Avatar, const char *BoneName, QpoTransform * Transform)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_Detach(QpoAvatar * Slave)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_Remove(QpoAvatar * Avatar)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_SetExtBox(QpoAvatar * Avatar, QpoExtBox * ExtBox, const char *BoneAnchor)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_SetScale(QpoAvatar * Avatar, float newScaleX, float newScaleY, float newScaleZ)
	{
	Avatar->Scale.x = newScaleX;
	Avatar->Scale.y = newScaleY;
	Avatar->Scale.z = newScaleZ;
	}

void Q_PORTShell::Avatar_SetAlpha(QpoAvatar * Avatar, float Alpha)
	{
	#pragma message("Set Inline as and when")
	Avatar->m_Alpha = Alpha;
	}

void Q_PORTShell::Avatar_GetTex(QpoAvatar * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_SetTex(QpoAvatar * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue)
	{
	//FROZEN
	}

void Q_PORTShell::Mesh_GetTex(QpoInstanceFlags * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue)
	{
	//FROZEN
	}

void Q_PORTShell::Mesh_SetTex(QpoInstanceFlags * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_ClearPose(QpoAvatar Avatar, QpoTransform * ShieldActorXform)
	{
	#pragma message("So far unused")
	}

void Q_PORTShell::Avatar_SetLighting(QpoAvatar * Avatar, bool, QpoVec3d * Vec1, float, float, float, float, float, float, bool, int, bool, bool)
	{
	//FROZEN
	}

void Q_PORTShell::Avatar_GetBoneTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	QunBone *i_bone;
	int boneID = Q.StructureA(String);

	if(i_AV->Avatar.Mesh)
		{
		std::vector<QunBone *>& vec_Bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

		//if(boneID < vec_Bone.size());
		i_bone = vec_Bone[boneID];

		//QunBone *i_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
		QunQuaternion boneort = i_bone->getRotationAbsolute();
		QunVector bonetrans = i_bone->getTranslationAbsolute();

		QpoVec3d bonevector;
		bonevector.x = bonetrans.x;
		bonevector.y = bonetrans.y;
		bonevector.z = bonetrans.z;

		QunMatrix rotationMatrix = boneort;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
		Bone->Matrix.m[0][0]=rotationMatrix.dxdx;Bone->Matrix.m[0][1]=rotationMatrix.dxdy;Bone->Matrix.m[0][2]=rotationMatrix.dxdz;
		Bone->Matrix.m[1][0]=rotationMatrix.dydx;Bone->Matrix.m[1][1]=rotationMatrix.dydy;Bone->Matrix.m[1][2]=rotationMatrix.dydz;
		Bone->Matrix.m[2][0]=rotationMatrix.dzdx;Bone->Matrix.m[2][1]=rotationMatrix.dzdy;Bone->Matrix.m[2][2]=rotationMatrix.dzdz;

		Bone->Matrix = i_AV->Xform.Matrix * Bone->Matrix;

		Qpo->Transform_RotateVector(&i_AV->Xform, &bonevector, &bonevector);

		bonevector.x *= i_AV->Avatar.Scale.x;
		bonevector.y *= i_AV->Avatar.Scale.y;
		bonevector.z *= i_AV->Avatar.Scale.z;

		Bone->Translation.x = bonevector.x + i_AV->Xform.Translation.x;
		Bone->Translation.y = bonevector.y + i_AV->Xform.Translation.y;
		Bone->Translation.z = bonevector.z + i_AV->Xform.Translation.z;
		}
	}

void Q_PORTShell::Avatar_GetBoneTransformMP(QpoAvatarFlags f_AV, const char * String, QpoTransform * Bone)
	{
	QunBone *f_bone = f_AV.Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = f_bone->getRotationAbsolute();
	QunVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0] = rotationMatrix.dxdy;
	Bone->Matrix.m[0][1] = rotationMatrix.dydy;
	Bone->Matrix.m[0][2] = rotationMatrix.dzdy;
	Bone->Matrix.m[1][0] = rotationMatrix.dxdx;
	Bone->Matrix.m[1][1] = rotationMatrix.dydx;
	Bone->Matrix.m[1][2] = rotationMatrix.dzdx;
	Bone->Matrix.m[2][0] = rotationMatrix.dxdz;
	Bone->Matrix.m[2][1] = rotationMatrix.dydz;
	Bone->Matrix.m[2][2] = rotationMatrix.dzdz;

	pMatrix f_Matrix;
	pQuaternion f_Quat;
	f_Quat.w = -0.09;
	f_Quat.x = 0.82;
	f_Quat.y = 2.039;
	f_Quat.z = -19.240345;
	f_Quat.normalize();
	f_Quat.get_mat(f_Matrix);

	Bone->Matrix = f_Matrix * Bone->Matrix;

	Bone->Matrix = Bone->Matrix * f_AV.Xform.Matrix;

	m_CC.pVector1.x = bonetrans.x;
	m_CC.pVector1.y = bonetrans.y;
	m_CC.pVector1.z = bonetrans.z;
	m_CC.pResult = m_CC.pVector1 * f_AV.Xform.Matrix;

	m_CC.pResult.x *= f_AV.Avatar.Scale.x;
	m_CC.pResult.y *= f_AV.Avatar.Scale.y;
	m_CC.pResult.z *= f_AV.Avatar.Scale.z;

	Bone->Translation.x = m_CC.pResult.x + f_AV.Xform.Translation.x;
	Bone->Translation.y = m_CC.pResult.y + f_AV.Xform.Translation.y;
	Bone->Translation.z = m_CC.pResult.z + f_AV.Xform.Translation.z;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
	}

void Q_PORTShell::Avatar_GetTransformAvatar(QpoAvatarFlags * f_AV, const char * String, QpoTransform * Bone, int AIcounters, bool f_IsPlayer)
	{
	QunBone *f_bone = f_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = f_bone->getRotationAbsolute();
	QunVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0]=-rotationMatrix.dxdx;
	Bone->Matrix.m[0][1]=-rotationMatrix.dxdy;
	Bone->Matrix.m[0][2]=-rotationMatrix.dxdz;
	Bone->Matrix.m[1][0]=rotationMatrix.dydx;
	Bone->Matrix.m[1][1]=rotationMatrix.dydy;
	Bone->Matrix.m[1][2]=rotationMatrix.dydz;
	Bone->Matrix.m[2][0]=-rotationMatrix.dzdx;
	Bone->Matrix.m[2][1]=-rotationMatrix.dzdy;
	Bone->Matrix.m[2][2]=-rotationMatrix.dzdz;

	//###-- - Quaternion - --###//
	pMatrix f_Matrix;
	pQuaternion f_Quat;
	f_Quat.w = 2.37;
	f_Quat.x = -0.97;
	f_Quat.y = -0.49;
	f_Quat.z = 2.2;
	f_Quat.normalize();
	f_Quat.get_mat(f_Matrix);

#if 0 // IMMEDIATE MODE
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&f_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

	glRotatef(radToDeg(-Q_Forge->Forge[AIcounters].Angles.y + PI), 0.0f, 0.0f, 1.0f);

	glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);
#endif

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	Qpo->Transform_RotateVector(&f_AV->Xform, &bonevector, &bonevector);

	bonevector.y *= f_AV->Avatar.Scale.y;

	Bone->Translation.x = bonevector.x + f_AV->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + f_AV->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + f_AV->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_GetWeaponTransform_s(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone, bool f_IsPlayer)
	{
	QunBone *i_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = i_bone->getRotationAbsolute();
	QunVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	QunQuaternion i_quat(1,0,1,0);

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0]=-rotationMatrix.dxdx;Bone->Matrix.m[0][1]=-rotationMatrix.dxdy;Bone->Matrix.m[0][2]=-rotationMatrix.dxdz;
	Bone->Matrix.m[1][0]=rotationMatrix.dydx;Bone->Matrix.m[1][1]=rotationMatrix.dydy;Bone->Matrix.m[1][2]=rotationMatrix.dydz;
	Bone->Matrix.m[2][0]=-rotationMatrix.dzdx;Bone->Matrix.m[2][1]=-rotationMatrix.dzdy;Bone->Matrix.m[2][2]=-rotationMatrix.dzdz;

	//***-- - Sense Quaternion - --***//
	pMatrix f_Matrix;
	pQuaternion f_Quat;
	f_Quat.w = 2.37;
	f_Quat.x = -0.97;
	f_Quat.y = -0.49;
	f_Quat.z = 2.2;
	f_Quat.normalize();
	f_Quat.get_mat(f_Matrix);

#if 1
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		//*glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		//*glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		//*glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		//*glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

#if 0
	//*glRotatef(radToDeg(-player[g_Player]->AvatarRotation + PI), 0.0f, 0.0f, 1.0f);
#endif

	//*glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);

	Qpo->Transform_RotateVector(&playerAV[g_Player]->Xform, &bonevector, &bonevector);

	bonevector.y *= playerAV[g_Player]->Avatar.Scale.y;

	//if(!f_IsPlayer) bonevector.y -= 17;

	Bone->Translation.x = bonevector.x + playerAV[g_Player]->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + playerAV[g_Player]->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + playerAV[g_Player]->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_GetWeaponTransform_old(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	QunBone *i_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = i_bone->getRotationAbsolute();
	QunVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	QunQuaternion i_quat(1,0,1,0);

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0]=-rotationMatrix.dxdx;Bone->Matrix.m[0][1]=-rotationMatrix.dxdy;Bone->Matrix.m[0][2]=-rotationMatrix.dxdz;
	Bone->Matrix.m[1][0]=rotationMatrix.dydx;Bone->Matrix.m[1][1]=rotationMatrix.dydy;Bone->Matrix.m[1][2]=rotationMatrix.dydz;
	Bone->Matrix.m[2][0]=-rotationMatrix.dzdx;Bone->Matrix.m[2][1]=-rotationMatrix.dzdy;Bone->Matrix.m[2][2]=-rotationMatrix.dzdz;

	//***-- - Sense Quaternion - --***//
	pMatrix i_Matrix;
	pQuaternion i_Quat;
	i_Quat.w = 2.37;
	i_Quat.x = -0.97;
	i_Quat.y = -0.49;
	i_Quat.z = 2.2;
	i_Quat.normalize();
	i_Quat.get_mat(i_Matrix);

#if 0
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&i_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

	glRotatef(radToDeg(-player[g_Player]->AvatarRotation + PI), 0.0f, 0.0f, 1.0f);

	glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);
#endif

	Qpo->Transform_RotateVector(&i_AV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = /*bonevector.x + */playerAV[g_Player]->Xform.Translation.x;
	Bone->Translation.y = /*bonevector.y + */playerAV[g_Player]->Xform.Translation.y;
	Bone->Translation.z = /*bonevector.z + */playerAV[g_Player]->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_GetWeaponTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	QunBone *i_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = i_bone->getRotationAbsolute();
	QunVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	QunQuaternion i_quat(1,0,1,0);

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0]=-rotationMatrix.dxdx;Bone->Matrix.m[0][1]=-rotationMatrix.dxdy;Bone->Matrix.m[0][2]=-rotationMatrix.dxdz;
	Bone->Matrix.m[1][0]=rotationMatrix.dydx;Bone->Matrix.m[1][1]=rotationMatrix.dydy;Bone->Matrix.m[1][2]=rotationMatrix.dydz;
	Bone->Matrix.m[2][0]=-rotationMatrix.dzdx;Bone->Matrix.m[2][1]=-rotationMatrix.dzdy;Bone->Matrix.m[2][2]=-rotationMatrix.dzdz;

	//###-- - Sense Quaternion - --###//
	pMatrix i_Matrix;
	pQuaternion i_Quat;
	i_Quat.w = 2.37;
	i_Quat.x = -0.97;
	i_Quat.y = -0.49;
	i_Quat.z = 2.2;
	i_Quat.normalize();
	i_Quat.get_mat(i_Matrix);

#if 0
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&i_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

	glRotatef(radToDeg(-player[g_Player]->AvatarRotation + PI), 0.0f, 0.0f, 1.0f);

	glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);
#endif

	Qpo->Transform_RotateVector(&i_AV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = bonevector.x + i_AV->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + i_AV->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + i_AV->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_RenderWeaponTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	QunBone *i_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = i_bone->getRotationAbsolute();
	QunVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	QunQuaternion i_quat(1,0,1,0);

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0]=-rotationMatrix.dxdx;Bone->Matrix.m[0][1]=-rotationMatrix.dxdy;Bone->Matrix.m[0][2]=-rotationMatrix.dxdz;
	Bone->Matrix.m[1][0]=rotationMatrix.dydx;Bone->Matrix.m[1][1]=rotationMatrix.dydy;Bone->Matrix.m[1][2]=rotationMatrix.dydz;
	Bone->Matrix.m[2][0]=-rotationMatrix.dzdx;Bone->Matrix.m[2][1]=-rotationMatrix.dzdy;Bone->Matrix.m[2][2]=-rotationMatrix.dzdz;

	//###-- - Sense Quaternion - --###//
	pMatrix i_Matrix;
	pQuaternion i_Quat;
	i_Quat.w = 2.37;
	i_Quat.x = -0.97;
	i_Quat.y = -0.49;
	i_Quat.z = 2.2;
	i_Quat.normalize();
	i_Quat.get_mat(i_Matrix);

#if 0
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);
#endif

	Qpo->Transform_RotateVector(&i_AV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = bonevector.x + i_AV->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + i_AV->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + i_AV->Xform.Translation.z;

#if 0
	glTranslatef(Bone->Translation.x, Bone->Translation.y, Bone->Translation.z);

	glMultMatrixf((float *)&i_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

	glRotatef(radToDeg(-player[g_Player]->AvatarRotation + PI), 0.0f, 0.0f, 1.0f);
#endif
	}

void Q_PORTShell::AvatarView_GetBoneTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone, bool f_IsPlayer)
	{
	QunBone *f_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = f_bone->getRotationAbsolute();
	QunVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	QunMatrix rotationMatrix = boneort;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
	//pMatrix f_matrix;
	//f_matrix.m[0][0]=rotationMatrix.dxdx;	f_matrix.m[0][1]=rotationMatrix.dxdy;	f_matrix.m[0][2]=rotationMatrix.dxdz;
	//f_matrix.m[1][0]=rotationMatrix.dydx;	f_matrix.m[1][1]=rotationMatrix.dydy;	f_matrix.m[1][2]=rotationMatrix.dydz;
	//f_matrix.m[2][0]=rotationMatrix.dzdx;	f_matrix.m[2][1]=rotationMatrix.dzdy;	f_matrix.m[2][2]=rotationMatrix.dzdz;

#if 1
	Bone->Matrix.m[0][0] = rotationMatrix.dxdy;
	Bone->Matrix.m[0][1] = rotationMatrix.dydy;
	Bone->Matrix.m[0][2] = rotationMatrix.dzdy;
	Bone->Matrix.m[1][0] = rotationMatrix.dxdx;
	Bone->Matrix.m[1][1] = rotationMatrix.dydx;
	Bone->Matrix.m[1][2] = rotationMatrix.dzdx;
	Bone->Matrix.m[2][0] = rotationMatrix.dxdz;
	Bone->Matrix.m[2][1] = rotationMatrix.dydz;
	Bone->Matrix.m[2][2] = rotationMatrix.dzdz;
#endif

	pMatrix f_Matrix;
	pQuaternion f_Quat;

#if 1
	f_Quat.w = -0.09;
	f_Quat.x = 0.82;
	f_Quat.y = 2.039;
	f_Quat.z = -19.240345;
#else
	f_Quat.w = -0.09;
	f_Quat.x = WeaponvalueX;
	f_Quat.y = WeaponvalueY;
	f_Quat.z = WeaponvalueZ;
#endif

	f_Quat.normalize();
	f_Quat.get_mat(f_Matrix);

	Bone->Matrix = f_Matrix * Bone->Matrix;

	Bone->Matrix = Bone->Matrix * i_AV->Viewform;

	m_CC.pVector1.x = bonetrans.x;
	m_CC.pVector1.y = bonetrans.y;
	m_CC.pVector1.z = bonetrans.z;
	m_CC.pResult = m_CC.pVector1 * i_AV->Viewform;
	
	m_CC.pResult.y *= i_AV->Avatar.Scale.y;

	Bone->Translation.x = m_CC.pResult.x + i_AV->Xform.Translation.x;
	Bone->Translation.y = m_CC.pResult.y + i_AV->Xform.Translation.y;
	Bone->Translation.z = m_CC.pResult.z + i_AV->Xform.Translation.z;
	}

void Q_PORTShell::AvatarView_GetBoneTransform_PntSprite(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	QunBone *f_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = f_bone->getRotationAbsolute();
	QunVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	QunMatrix rotationMatrix = boneort;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
	//pMatrix f_matrix;
	//f_matrix.m[0][0]=rotationMatrix.dxdx;	f_matrix.m[0][1]=rotationMatrix.dxdy;	f_matrix.m[0][2]=rotationMatrix.dxdz;
	//f_matrix.m[1][0]=rotationMatrix.dydx;	f_matrix.m[1][1]=rotationMatrix.dydy;	f_matrix.m[1][2]=rotationMatrix.dydz;
	//f_matrix.m[2][0]=rotationMatrix.dzdx;	f_matrix.m[2][1]=rotationMatrix.dzdy;	f_matrix.m[2][2]=rotationMatrix.dzdz;

#if 1
	Bone->Matrix.m[0][0] = rotationMatrix.dxdy;
	Bone->Matrix.m[0][1] = rotationMatrix.dydy;
	Bone->Matrix.m[0][2] = rotationMatrix.dzdy;
	Bone->Matrix.m[1][0] = rotationMatrix.dxdx;
	Bone->Matrix.m[1][1] = rotationMatrix.dydx;
	Bone->Matrix.m[1][2] = rotationMatrix.dzdx;
	Bone->Matrix.m[2][0] = rotationMatrix.dxdz;
	Bone->Matrix.m[2][1] = rotationMatrix.dydz;
	Bone->Matrix.m[2][2] = rotationMatrix.dzdz;
#endif

	pMatrix f_Matrix;
	pQuaternion f_Quat;

#if 1
	f_Quat.w = -0.09;
	f_Quat.x = 0.82;
	f_Quat.y = 2.039;
	f_Quat.z = -19.240345;
#else
	f_Quat.w = -0.09;
	f_Quat.x = WeaponvalueX;
	f_Quat.y = WeaponvalueY;
	f_Quat.z = WeaponvalueZ;
#endif

	f_Quat.normalize();
	f_Quat.get_mat(f_Matrix);

	Bone->Matrix = f_Matrix * Bone->Matrix;

	Bone->Matrix = Bone->Matrix * i_AV->Viewform;

	m_CC.pVector1.x = bonetrans.x;
	m_CC.pVector1.y = bonetrans.y;
	m_CC.pVector1.z = bonetrans.z;
	m_CC.pResult = m_CC.pVector1 * i_AV->Viewform;

	Bone->Translation.x = m_CC.pResult.x + i_AV->Xform.Translation.x;
	Bone->Translation.y = m_CC.pResult.y + i_AV->Xform.Translation.y;
	Bone->Translation.z = m_CC.pResult.z + i_AV->Xform.Translation.z;
	}

void Q_PORTShell::WeaponView_GetBoneTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	QunBone *i_bone = i_AV->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = i_bone->getRotationAbsolute();
	QunVector bonetrans = i_bone->getTranslationAbsolute();

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0] = rotationMatrix.dxdy;
	Bone->Matrix.m[0][1] = rotationMatrix.dydy;
	Bone->Matrix.m[0][2] = rotationMatrix.dzdy;
	Bone->Matrix.m[1][0] = rotationMatrix.dxdx;
	Bone->Matrix.m[1][1] = rotationMatrix.dydx;
	Bone->Matrix.m[1][2] = rotationMatrix.dzdx;
	Bone->Matrix.m[2][0] = rotationMatrix.dxdz;
	Bone->Matrix.m[2][1] = rotationMatrix.dydz;
	Bone->Matrix.m[2][2] = rotationMatrix.dzdz;

	pMatrix i_Matrix;
	pQuaternion i_Quat;
	i_Quat.w = -0.09;
	i_Quat.x = 0.82;
	i_Quat.y = 2.039;
	i_Quat.z = -19.240345;
	i_Quat.normalize();
	i_Quat.get_mat(i_Matrix);

	Bone->Matrix = i_Matrix * Bone->Matrix;
	Bone->Matrix = Bone->Matrix * i_AV->Weaponform;

	m_CC.pVector1.x = bonetrans.x;
	m_CC.pVector1.y = bonetrans.y;
	m_CC.pVector1.z = bonetrans.z;
	m_CC.pResult = m_CC.pVector1 * i_AV->Weaponform;

	Bone->Translation.x = m_CC.pResult.x + i_AV->Xform.Translation.x;
	Bone->Translation.y = m_CC.pResult.y + i_AV->Xform.Translation.y;
	Bone->Translation.z = m_CC.pResult.z + i_AV->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_WeaponView_GetBoneTransform(int i_AvatarIndex, const char * String, QpoTransform * Bone)
	{
	QunBone *i_bone = Q_Forge->Forge[i_AvatarIndex].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(String));
	QunQuaternion boneort = i_bone->getRotationAbsolute();
	QunVector bonetrans = i_bone->getTranslationAbsolute();

	QunMatrix rotationMatrix = boneort;

	Bone->Matrix.m[0][0] = rotationMatrix.dxdy;
	Bone->Matrix.m[0][1] = rotationMatrix.dydy;
	Bone->Matrix.m[0][2] = rotationMatrix.dzdy;
	Bone->Matrix.m[1][0] = rotationMatrix.dxdx;
	Bone->Matrix.m[1][1] = rotationMatrix.dydx;
	Bone->Matrix.m[1][2] = rotationMatrix.dzdx;
	Bone->Matrix.m[2][0] = rotationMatrix.dxdz;
	Bone->Matrix.m[2][1] = rotationMatrix.dydz;
	Bone->Matrix.m[2][2] = rotationMatrix.dzdz;

	pMatrix i_Matrix;
	pQuaternion i_Quat;
	i_Quat.w = -0.09;
	i_Quat.x = 0.82;
	i_Quat.y = 2.039;
	i_Quat.z = -19.240345;
	i_Quat.normalize();
	i_Quat.get_mat(i_Matrix);

	Bone->Matrix = i_Matrix * Bone->Matrix;

#if 0
	Bone->Matrix = Bone->Matrix * Q_Forge->Forge[i_AvatarIndex].AV.Weaponform;
#else
	Bone->Matrix = Bone->Matrix * Q_Forge->Forge[i_AvatarIndex].AV.Viewform;
#endif

	m_CC.pVector1.x = bonetrans.x;
	m_CC.pVector1.y = bonetrans.y;
	m_CC.pVector1.z = bonetrans.z;

#if 0
	m_CC.pResult = m_CC.pVector1 * Q_Forge->Forge[i_AvatarIndex].AV.Weaponform;
#else
	m_CC.pResult = m_CC.pVector1 * Q_Forge->Forge[i_AvatarIndex].AV.Viewform;
#endif

	Bone->Translation.x = m_CC.pResult.x + Q_Forge->Forge[i_AvatarIndex].AV.Xform.Translation.x;
	Bone->Translation.y = m_CC.pResult.y + Q_Forge->Forge[i_AvatarIndex].AV.Xform.Translation.y;
	Bone->Translation.z = m_CC.pResult.z + Q_Forge->Forge[i_AvatarIndex].AV.Xform.Translation.z;
	}

void Q_PORTShell::Avatar_GetJointTransform(QpoPose Pose, int BoneNum, QpoTransform * BoneTransform)
	{
	BoneTransform->Matrix.load_identity();
	BoneTransform->Translation.x = 0;
	BoneTransform->Translation.y = 0;
	BoneTransform->Translation.z = 0;
	}

void Q_PORTShell::Avatar_SetJointTransform(QpoPose Pose, int BoneNum, QpoTransform * BoneTransform)
	{
	//FROZEN
	}

QpoMotion Q_PORTShell::Avatar_GetMotionByName(QpoAvatar_Def * Avatar_Def, const char *Name )
	{
	QpoMotion motionhandle = 0;

	return motionhandle;
	}

void Q_PORTShell::Player_SetMatrix(void)
	{
	//...
	}

QpoFog * Q_PORTShell::Fog_AddtoWorld(void)
	{
	QpoFog * foghandle = 0;
	
	return foghandle;
	}

void Q_PORTShell::Fog_RemovefromWorld(QpoFog * fog)
	{
	//FROZEN
	}

void Q_PORTShell::Fog_SetAttr(QpoFog * fog, QpoVec3d * pos, QpoColor * color, float LightBrightness, float VolumeBrightness, float VolumeRadius)
	{
	//FROZEN
	}

void Q_PORTShell::GUI_Printf(int x,int y, const char *String, ...)
	{
	//FROZEN
	}

void Q_PORTShell::Player_GetBoneBoundingBox(const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ)
	{
	QunBone *i_bone = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(BoneName));
	i_bone->calculateBoundingBox();
	QunBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	QunVector i_Points[8];
	i_BoneBox.computePoints(i_Points);

	Corner->x = i_Points[4].x;
	Corner->y = i_Points[4].y;
	Corner->z = i_Points[4].z;

	DX->x = i_Points[2].x - i_Points[6].x;
	DX->y = i_Points[2].y - i_Points[6].y;
	DX->z = i_Points[2].z - i_Points[6].z;

	DY->x = i_Points[7].x - i_Points[6].x;
	DY->y = i_Points[7].y - i_Points[6].y;
	DY->z = i_Points[7].z - i_Points[6].z;

	DZ->x = i_Points[4].x - i_Points[6].x;
	DZ->y = i_Points[4].y - i_Points[6].y;
	DZ->z = i_Points[4].z - i_Points[6].z;
	}

void Q_PORTShell::Avatar_GetBoneBoundingBox(unsigned int i_AVIndex, const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ)
	{
	QunBone *i_bone = Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(BoneName));
	i_bone->calculateBoundingBox();
	QunBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	QunVector i_Points[8];
	i_BoneBox.computePoints(i_Points);

	Corner->x = i_Points[4].x;
	Corner->y = i_Points[4].y;
	Corner->z = i_Points[4].z;

	DX->x = i_Points[2].x - i_Points[6].x;
	DX->y = i_Points[2].y - i_Points[6].y;
	DX->z = i_Points[2].z - i_Points[6].z;

	DY->x = i_Points[7].x - i_Points[6].x;
	DY->y = i_Points[7].y - i_Points[6].y;
	DY->z = i_Points[7].z - i_Points[6].z;

	DZ->x = i_Points[4].x - i_Points[6].x;
	DZ->y = i_Points[4].y - i_Points[6].y;
	DZ->z = i_Points[4].z - i_Points[6].z;
	}

void Q_PORTShell::Player_GetBoneBoxes(const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ, QpoVectorBox *i_ExtBox)
	{
	QunBone *i_bone = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(BoneName));
	i_bone->calculateBoundingBox();
	QunBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	QunVector i_Points[8];
	i_BoneBox.computePoints(i_Points);

	Corner->x = i_Points[4].x;
	Corner->y = i_Points[4].y;
	Corner->z = i_Points[4].z;

	DX->x = i_Points[2].x - i_Points[6].x;
	DX->y = i_Points[2].y - i_Points[6].y;
	DX->z = i_Points[2].z - i_Points[6].z;

	DY->x = i_Points[7].x - i_Points[6].x;
	DY->y = i_Points[7].y - i_Points[6].y;
	DY->z = i_Points[7].z - i_Points[6].z;

	DZ->x = i_Points[4].x - i_Points[6].x;
	DZ->y = i_Points[4].y - i_Points[6].y;
	DZ->z = i_Points[4].z - i_Points[6].z;

	i_ExtBox->Min.x = i_Points[0].x;
	i_ExtBox->Min.y = i_Points[0].y;
	i_ExtBox->Min.z = i_Points[0].z;

	i_ExtBox->Max = i_ExtBox->Min;

	for(int i_iter = 0; i_iter < 8; i_iter++)
		{
		if(i_Points[i_iter].x < i_ExtBox->Min.x) i_ExtBox->Min.x = i_Points[i_iter].x;
		if(i_Points[i_iter].y < i_ExtBox->Min.y) i_ExtBox->Min.y = i_Points[i_iter].y;
		if(i_Points[i_iter].z < i_ExtBox->Min.z) i_ExtBox->Min.z = i_Points[i_iter].z;

		if(i_Points[i_iter].x > i_ExtBox->Max.x) i_ExtBox->Max.x = i_Points[i_iter].x;
		if(i_Points[i_iter].y > i_ExtBox->Max.y) i_ExtBox->Max.y = i_Points[i_iter].y;
		if(i_Points[i_iter].z > i_ExtBox->Max.z) i_ExtBox->Max.z = i_Points[i_iter].z;
		}
	}

void Q_PORTShell::Avatar_GetBoneBoxes(unsigned int i_AVIndex, const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ, QpoVectorBox *i_ExtBox)
	{
	QunBone *i_bone = Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(BoneName));
	i_bone->calculateBoundingBox();
	QunBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	QunVector i_Points[8];
	i_BoneBox.computePoints(i_Points);

	Corner->x = i_Points[4].x;
	Corner->y = i_Points[4].y;
	Corner->z = i_Points[4].z;

	DX->x = i_Points[2].x - i_Points[6].x;
	DX->y = i_Points[2].y - i_Points[6].y;
	DX->z = i_Points[2].z - i_Points[6].z;

	DY->x = i_Points[7].x - i_Points[6].x;
	DY->y = i_Points[7].y - i_Points[6].y;
	DY->z = i_Points[7].z - i_Points[6].z;

	DZ->x = i_Points[4].x - i_Points[6].x;
	DZ->y = i_Points[4].y - i_Points[6].y;
	DZ->z = i_Points[4].z - i_Points[6].z;

	i_ExtBox->Min.x = i_Points[0].x;
	i_ExtBox->Min.y = i_Points[0].y;
	i_ExtBox->Min.z = i_Points[0].z;

	i_ExtBox->Max = i_ExtBox->Min;

	for(int i_iter = 0; i_iter < 8; i_iter++)
		{
		if(i_Points[i_iter].x < i_ExtBox->Min.x) i_ExtBox->Min.x = i_Points[i_iter].x;
		if(i_Points[i_iter].y < i_ExtBox->Min.y) i_ExtBox->Min.y = i_Points[i_iter].y;
		if(i_Points[i_iter].z < i_ExtBox->Min.z) i_ExtBox->Min.z = i_Points[i_iter].z;

		if(i_Points[i_iter].x > i_ExtBox->Max.x) i_ExtBox->Max.x = i_Points[i_iter].x;
		if(i_Points[i_iter].y > i_ExtBox->Max.y) i_ExtBox->Max.y = i_Points[i_iter].y;
		if(i_Points[i_iter].z > i_ExtBox->Max.z) i_ExtBox->Max.z = i_Points[i_iter].z;
		}
	}

void Q_PORTShell::Player_RenderBoneBoundingBox(const char *BoneName)
	{
	QunBone *i_bone = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(BoneName));
	i_bone->calculateBoundingBox();
	QunBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	QunVector i_Points[8];
	i_BoneBox.computePoints(i_Points);
	}

void Q_PORTShell::Avatar_RenderBoneBoundingBox(unsigned int i_AVIndex, const char *BoneName)
	{
	QunBone *i_bone = Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getBone(Q.StructureA(BoneName));
	i_bone->calculateBoundingBox();
	QunBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	QunVector i_Points[8];
	i_BoneBox.computePoints(i_Points);
	}

void Q_PORTShell::Box_Render(QpoBox i_Box)
	{
	QpoVec3d i_in, i_up, i_left;
	QpoVec3d i_point[8];

	Transform_GetIn(&i_Box.Transform, &i_in);
	Transform_GetLeft(&i_Box.Transform, &i_left);
	Transform_GetUp(&i_Box.Transform, &i_up);

	i_point[2].x = i_Box.Transform.Translation.x;
	i_point[2].y = i_Box.Transform.Translation.y;
	i_point[2].z = i_Box.Transform.Translation.z;
	Vec3d_AddScaled(&i_point[2], i_Box.xScale, &i_left, &i_point[0]);
	Vec3d_AddScaled(&i_point[0], i_Box.zScale, &i_in, &i_point[1]);
	Vec3d_AddScaled(&i_point[1], -i_Box.xScale, &i_left, &i_point[3]);
	Vec3d_AddScaled(&i_point[0], i_Box.yScale, &i_up, &i_point[4]);
	Vec3d_AddScaled(&i_point[1], i_Box.yScale, &i_up, &i_point[5]);
	Vec3d_AddScaled(&i_point[2], i_Box.yScale, &i_up, &i_point[6]);
	Vec3d_AddScaled(&i_point[3], i_Box.yScale, &i_up, &i_point[7]);

	Camera_Set();
	}

void Q_PORTShell::Player_RenderBoundingBoxes(void)
	{
	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->calculateBoundingBoxes();
	playerAV[g_Player]->Avatar.Mesh->renderBoundingBox();
	}

void Q_PORTShell::Avatar_RenderBoundingBoxes(unsigned int i_AVIndex)
	{
	Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_qunModel->getSkeleton()->calculateBoundingBoxes();
	Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->renderBoundingBox();
	}

void Q_PORTShell::Mesh_SetScale(QpoInstanceFlags * i_Instance, float newScaleX, float newScaleY, float newScaleZ)
	{
	i_Instance->Scale.x = newScaleX;
	i_Instance->Scale.y = newScaleY;
	i_Instance->Scale.z = newScaleZ;
	}

void Q_PORTShell::Mesh_SetAlpha(QpoInstanceFlags * i_Instance, float Alpha)
	{
	#pragma message("Set Inline as and when")
	i_Instance->m_Alpha = Alpha;
	}

void Q_PORTShell::Engine_ScreenShot(const char *FileName)
	{
	//...
	}

void Q_PORTShell::Camera_SetTransform(int/*camera*/camera, QpoTransform * transform, QpoVec3d Position)
	{
	g_render->camera.mat_t.m[0][0]=transform->Matrix.m[1][0];
	g_render->camera.mat_t.m[0][1]=transform->Matrix.m[1][1];
	g_render->camera.mat_t.m[0][2]=transform->Matrix.m[1][2];
	g_render->camera.mat_t.m[1][0]=transform->Matrix.m[2][0];
	g_render->camera.mat_t.m[1][1]=transform->Matrix.m[2][1];
	g_render->camera.mat_t.m[1][2]=transform->Matrix.m[2][2];
	g_render->camera.mat_t.m[2][0]=transform->Matrix.m[0][0];
	g_render->camera.mat_t.m[2][1]=transform->Matrix.m[0][1];
	g_render->camera.mat_t.m[2][2]=transform->Matrix.m[0][2];

	//g_render->camera.mat = playerAV[g_Player]->Xform.Matrix;
	g_render->camera.pos.x = transform->Translation.x;
	g_render->camera.pos.y = transform->Translation.y;
	g_render->camera.pos.z = transform->Translation.z;

	g_render->camera.X.vec(g_render->camera.mat_t.m[0][0],g_render->camera.mat_t.m[1][0],g_render->camera.mat_t.m[2][0]);
	g_render->camera.Y.vec(g_render->camera.mat_t.m[0][1],g_render->camera.mat_t.m[1][1],g_render->camera.mat_t.m[2][1]);
	g_render->camera.Z.vec(g_render->camera.mat_t.m[0][2],g_render->camera.mat_t.m[1][2],g_render->camera.mat_t.m[2][2]);

	g_render->camera.update_mat();

	float fov=(g_render->camerafov>0?g_render->camerafov:g_render->camera.fov);
	g_render->view.build(g_render->camera.pos,g_render->camera.X,g_render->camera.Y,g_render->camera.Z,fov/g_render->aspect,g_render->aspect,g_render->farplane);
	}

void Q_PORTShell::Camera_GetClippingRect(int/*camera*/camera, QpoRect * rect)
	{
#if 0
	Vec2f minvec;
	Vec2f maxvec;

	WritableObject<nvsg::Camera> i_camera (camera);
	i_camera->getWindowRegion(minvec, maxvec);

	rect->xmin = minvec[0];
	rect->ymin = minvec[1];
	rect->xmax = maxvec[0];
	rect->ymax = maxvec[0];
#endif
	}

void Q_PORTShell::Camera_SetAttr(int/*camera*/camera, float FOV, QpoRect * rect)
	{
#if 0
	WritableObject<nvsg::Camera> i_camera (GVARS::Camera);
	i_camera->setWindowRegion(Vec2f(rect->xmin, rect->ymin), Vec2f(rect->xmax, rect->ymax));
	i_camera->zoom(FOV);
#endif
	}

void Q_PORTShell::Camera_SetFOV(int/*camera*/camera, float FOV)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	g_render->camera.fov = FOV;
#endif
	}

void Q_PORTShell::Camera_Set(void)
	{
#pragma message("Server Engine excludes")
#if 0
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);
#endif
	}

void Q_PORTShell::Camera_SetPlayer(void)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	//...
#endif
	}

void Q_PORTShell::Camera_SetAvatar(unsigned int i_AVIndex)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	//...
#endif
	}

void Q_PORTShell::Engine_SetGamma(float gama)
	{
	//FROZEN
	}

///////  QpoBox functions  ///////

void Q_PORTShell::Box_ComputeGlobalFrameAxes(QpoBox* Box)
	{
#ifdef PORTSHELL_ASSERT_DEBUG
	bool isOrthonormal;
	isOrthonormal = Transform_IsOrthonormal(&(Box->Transform));
	assert(Transform_IsOrthonormal);
#endif

	Box->GlobalFrameAxes[0].x = Box->Transform.Matrix.m[0][2] * -Box->xScale;
	Box->GlobalFrameAxes[0].y = Box->Transform.Matrix.m[2][2] * -Box->xScale;
	Box->GlobalFrameAxes[0].z = Box->Transform.Matrix.m[1][2] * -Box->xScale;

	Box->GlobalFrameAxes[1].x = Box->Transform.Matrix.m[0][0] * Box->yScale;
	Box->GlobalFrameAxes[1].y = Box->Transform.Matrix.m[2][0] * Box->yScale;
	Box->GlobalFrameAxes[1].z = Box->Transform.Matrix.m[1][0] * Box->yScale;

	Box->GlobalFrameAxes[2].x = Box->Transform.Matrix.m[0][1] * Box->zScale;
	Box->GlobalFrameAxes[2].y = Box->Transform.Matrix.m[2][1] * Box->zScale;
	Box->GlobalFrameAxes[2].z = Box->Transform.Matrix.m[1][1] * Box->zScale;
	}

void Q_PORTShell::Box_Set(QpoBox* Box, float xScale, float yScale, float zScale, const QpoTransform* Transform)
	{
#ifdef PORTSHELL_ASSERT_DEBUG
	bool isOrthonormal;
	isOrthonormal = Transform_IsOrthonormal(&(Box->Transform));
	assert(isOrthonormal);
#endif

	Box->xScale = xScale;
	Box->yScale = yScale;
	Box->zScale = zScale;

	Box_SetXForm(Box, Transform);	
	}

//////  set a Box's Transform  //////

void Q_PORTShell::Box_SetXForm(QpoBox* Box, const QpoTransform* Transform)
	{
#ifdef PORTSHELL_ASSERT_DEBUG
	bool isOrthonormal;
	isOrthonormal = Transform_IsOrthonormal(Transform);
	assert(isOrthonormal);
#endif

	Transform_Copy(Transform, &(Box->Transform));

#ifdef PORTSHELL_ASSERT_DEBUG
	isOrthonormal = Transform_IsOrthonormal(&(Box->Transform));
	assert(isOrthonormal);
#endif

	Transform_Transpose(Transform, &(Box->TransformInv));

#ifdef PORTSHELL_ASSERT_DEBUG
	isOrthonormal = Transform_IsOrthonormal(&(Box->TransformInv));
	assert(isOrthonormal);
#endif

	Box_ComputeGlobalFrameAxes(Box);
	}

bool Q_PORTShell::Box_DetectCollisionBetween(QpoBox* Box1, QpoBox* Box2)
	{
	int i, c;
	float radius;
	QpoBox* BoxA;
	QpoBox* BoxB;
	static QpoVec3d centerToCenterVector, xformedCenterToCenterVector;
	static QpoVec3d inverseXFormedGlobalFrameAxes[3];

#ifdef PORTSHELL_ASSERT_DEBUG
	isOrthonormal = Transform_IsOrthonormal(&(Box1->Transform));
	assert(isOrthonormal);
#endif

#ifdef PORTSHELL_ASSERT_DEBUG
	isOrthonormal = Transform_IsOrthonormal(&(Box2->Transform));
	assert(isOrthonormal);
#endif

	// test B against A and if necessary A against B
	for(c = 0; c < 2; c ++)
		{
		if(c == 0)
			{
			BoxA = Box1;
			BoxB = Box2;
			}
		else
			{
			BoxA = Box2;
			BoxB = Box1;
			}

		// rotate B's global frame axes by the amount A was rotated to bring it
		// back into its local coord system
		for(i = 0; i < 3; i++)
			{
			Transform_RotateVector(&BoxA->TransformInv, &BoxB->GlobalFrameAxes[i], &inverseXFormedGlobalFrameAxes[i]);
			}

		// get B's translation offset from A in global coord system
		Vec3d_Subtract(&BoxB->Transform.Translation, &BoxA->Transform.Translation, &centerToCenterVector);

		// rotate offset by the amount A was rotated to bring it
		// back into its local coord system
		Transform_RotateVector(&BoxA->TransformInv, &centerToCenterVector, &xformedCenterToCenterVector);

		xformedCenterToCenterVector.x = (float)fabs(xformedCenterToCenterVector.x);
		xformedCenterToCenterVector.y = (float)fabs(xformedCenterToCenterVector.y);
		xformedCenterToCenterVector.z = (float)fabs(xformedCenterToCenterVector.z);

		// test every radius of BoxB
		// for every global frame-axis-aligned axis of BoxA
		// to see if overlap occurred

		// test overlap in X axis

		radius = (float)(fabs(inverseXFormedGlobalFrameAxes[0].x) +
			fabs(inverseXFormedGlobalFrameAxes[1].x) +
			fabs(inverseXFormedGlobalFrameAxes[2].x));

		if((radius + BoxA->xScale) < xformedCenterToCenterVector.x) return false;

		// test overlap in Y axis

		radius = (float)(fabs(inverseXFormedGlobalFrameAxes[0].y) +
			fabs(inverseXFormedGlobalFrameAxes[1].y) +
			fabs(inverseXFormedGlobalFrameAxes[2].y));

		if((radius + BoxA->yScale) < xformedCenterToCenterVector.y) return false;

		// test overlap in Z axis

		radius = (float)(fabs(inverseXFormedGlobalFrameAxes[0].z) +
			fabs(inverseXFormedGlobalFrameAxes[1].z) +
			fabs(inverseXFormedGlobalFrameAxes[2].z));

		if((radius + BoxA->zScale) < xformedCenterToCenterVector.z) return false;
		} // c

	return true; // all tests checked out, overlap occurred
	}

bool Q_PORTShell::Player_ExtBox_intersect(unsigned int i_AVIndex)
	{
	if (((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Maxs.x)) || ((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Mins.x))) return false;
	if (((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Maxs.y)) || ((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Mins.y))) return false;
	if (((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Maxs.z)) || ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Avatar_Player_ExtBox_intersect(unsigned int i_AVIndex)
	{
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Mins.x) > (playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Maxs.x) < (playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Mins.y) > (playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Maxs.y) < (playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Mins.z) > (playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Maxs.z) < (playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Player_Player_ExtBox_intersect(unsigned int i_PLIndex)
	{
	if (((playerAV[i_PLIndex]->Xform.Translation.x + playerAV[i_PLIndex]->Mins.x) > (playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x)) || ((playerAV[i_PLIndex]->Xform.Translation.x + playerAV[i_PLIndex]->Maxs.x) < (playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x))) return false;
	if (((playerAV[i_PLIndex]->Xform.Translation.y + playerAV[i_PLIndex]->Mins.y) > (playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y)) || ((playerAV[i_PLIndex]->Xform.Translation.y + playerAV[i_PLIndex]->Maxs.y) < (playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y))) return false;
	if (((playerAV[i_PLIndex]->Xform.Translation.z + playerAV[i_PLIndex]->Mins.z) > (playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z)) || ((playerAV[i_PLIndex]->Xform.Translation.z + playerAV[i_PLIndex]->Maxs.z) < (playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Avatar_ExtBox_intersect(unsigned int i_AVIndex1, unsigned int i_AVIndex2)
	{
	if (((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex1].AV.Mins.x) > (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex2].AV.Maxs.x)) || ((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex1].AV.Maxs.x) < (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex2].AV.Mins.x))) return false;
	if (((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex1].AV.Mins.y) > (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex2].AV.Maxs.y)) || ((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex1].AV.Maxs.y) < (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex2].AV.Mins.y))) return false;
	if (((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex1].AV.Mins.z) > (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex2].AV.Maxs.z)) || ((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex1].AV.Maxs.z) < (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex2].AV.Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Collision_Player_Intersect(unsigned int i_AVIndex)
	{
	if (((playerAV[g_Player]->Xform.Translation.x + ColldetBox.Min.x) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Maxs.x)) || ((playerAV[g_Player]->Xform.Translation.x + ColldetBox.Max.x) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Mins.x))) return false;
	if (((playerAV[g_Player]->Xform.Translation.y + ColldetBox.Min.y) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Maxs.y)) || ((playerAV[g_Player]->Xform.Translation.y + ColldetBox.Max.y) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Mins.y))) return false;
	if (((playerAV[g_Player]->Xform.Translation.z + ColldetBox.Min.z) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Maxs.z)) || ((playerAV[g_Player]->Xform.Translation.z + ColldetBox.Max.z) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Collision_Avatar_Player_Intersect(unsigned int i_AVIndex)
	{
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + ColldetBox.Min.x) > (playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + ColldetBox.Max.x) < (playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + ColldetBox.Min.y) > (playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + ColldetBox.Max.y) < (playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + ColldetBox.Min.z) > (playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + ColldetBox.Max.z) < (playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Collision_Avatar_Intersect(unsigned int i_AVIndex1, unsigned int i_AVIndex2)
	{
	if (((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.x + ColldetBox.Min.x) > (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex2].AV.Maxs.x)) || ((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.x + ColldetBox.Max.x) < (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex2].AV.Mins.x))) return false;
	if (((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.y + ColldetBox.Min.y) > (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex2].AV.Maxs.y)) || ((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.y + ColldetBox.Max.y) < (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex2].AV.Mins.y))) return false;
	if (((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.z + ColldetBox.Min.z) > (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex2].AV.Maxs.z)) || ((Q_Forge->Forge[i_AVIndex1].AV.Xform.Translation.z + ColldetBox.Max.z) < (Q_Forge->Forge[i_AVIndex2].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex2].AV.Mins.z))) return false;
	return true;
	}

#if 0
void SenseMatrix()
{
	int vectrans[32];
	int vecvar[5];
	bool vecvarDpress[5];

	vecvar[0] = 0;
	vecvar[1] = 0;
	vecvar[2] = 0;
	vecvar[3] = 0;
	vecvar[4] = 0;

	vecvarDpress[0] = false;
	vecvarDpress[1] = false;
	vecvarDpress[2] = false;
	vecvarDpress[3] = false;
	vecvarDpress[4] = false;

	vectrans[0] = 0;
	vectrans[1] = 0;
	vectrans[2] = 0;
	vectrans[3] = 0;
	vectrans[4] = 0;
	vectrans[5] = 0;
	vectrans[6] = 0;
	vectrans[7] = 0;
	vectrans[8] = 0;
	vectrans[9] = 0;
	vectrans[10] = 0;
	vectrans[11] = 0;
	vectrans[12] = 0;
	vectrans[13] = 0;
	vectrans[14] = 0;
	vectrans[15] = 0;
	vectrans[16] = 0;
	vectrans[17] = 0;
	vectrans[18] = 0;
	vectrans[19] = 0;
	vectrans[20] = 0;
	vectrans[21] = 0;
	vectrans[22] = 0;
	vectrans[23] = 0;
	vectrans[24] = 0;
	vectrans[25] = 0;
	vectrans[26] = 0;
	vectrans[27] = 0;
	vectrans[28] = 0;
	vectrans[29] = 0;
	vectrans[30] = 0;
	vectrans[31] = 0;

	if(KEY_DOWN(QIN_g))
		{
		if(!vecvarDpress[0])
			{
			vecvarDpress[0] = true;
			vectrans[vecvar[1]]++;
			if(vectrans[vecvar[1]] > 2) vectrans[vecvar[1]] = 0;

			printf("Transform Row 0 1 - %i %i\n", vectrans[0], vectrans[1]);
			printf("Transform Row 2 3 - %i %i\n", vectrans[2], vectrans[3]);
			printf("Transform Row 4 5 - %i %i\n", vectrans[4], vectrans[5]);
			printf("Transform Row 6 7 - %i %i\n", vectrans[6], vectrans[7]);
			printf("Transform Row 8 9 - %i %i\n", vectrans[8], vectrans[9]);
			printf("Transform Row1011 - %i %i\n", vectrans[10], vectrans[11]);
			printf("Transform Row1213 - %i %i\n", vectrans[12], vectrans[13]);
			printf("Transform Row1415 - %i %i\n", vectrans[14], vectrans[15]);
			printf("Transform Row1617 - %i %i\n", vectrans[16], vectrans[17]);
			printf("_____________\n");

			printf("Transform Row 0 1 - %f\n", g_render->camera.mat.m[0][0]);
			printf("Transform Row 2 3 - %f\n", g_render->camera.mat.m[0][1]);
			printf("Transform Row 4 5 - %f\n", g_render->camera.mat.m[0][2]);
			printf("Transform Row 6 7 - %f\n", g_render->camera.mat.m[1][0]);
			printf("Transform Row 8 9 - %f\n", g_render->camera.mat.m[1][1]);
			printf("Transform Row1011 - %f\n", g_render->camera.mat.m[1][2]);
			printf("Transform Row1213 - %f\n", g_render->camera.mat.m[2][0]);
			printf("Transform Row1415 - %f\n", g_render->camera.mat.m[2][1]);
			printf("Transform Row1617 - %f\n", g_render->camera.mat.m[2][2]);
			printf("_____________\n");
			}
		}
	else vecvarDpress[0] = false;

	if(KEY_DOWN(QIN_f))
		{
		if(!vecvarDpress[1])
			{
			vecvarDpress[1] = true;

			vecvar[1]--;
			if(vecvar[1] > 31) vecvar[1] = 0;
			printf("vecvar = %i\n", vecvar[1]);
			}
		}
	else vecvarDpress[1] = false;

	if(KEY_DOWN(QIN_h))
		{
		if(!vecvarDpress[2])
			{
			vecvarDpress[2] = true;

			vecvar[1]++;
			if(vecvar[1] < 0) vecvar[1] = 31;
			printf("vecvar = %i\n", vecvar[1]);
			}
		}
	else vecvarDpress[2] = false;

	g_render->camera.mat.m[0][0]=transform->Matrix.m[vectrans[0]][vectrans[1]];
	g_render->camera.mat.m[0][1]=transform->Matrix.m[vectrans[2]][vectrans[3]];
	g_render->camera.mat.m[0][2]=transform->Matrix.m[vectrans[4]][vectrans[5]];

	g_render->camera.mat.m[1][0]=transform->Matrix.m[vectrans[6]][vectrans[7]];
	g_render->camera.mat.m[1][1]=transform->Matrix.m[vectrans[8]][vectrans[9]];
	g_render->camera.mat.m[1][2]=transform->Matrix.m[vectrans[10]][vectrans[11]];

	g_render->camera.mat.m[2][0]=transform->Matrix.m[vectrans[12]][vectrans[13]];
	g_render->camera.mat.m[2][1]=transform->Matrix.m[vectrans[14]][vectrans[15]];
	g_render->camera.mat.m[2][2]=transform->Matrix.m[vectrans[16]][vectrans[17]];
}

void SenseRotation(void)
{
	if(KEY_DOWN(QIN_g))
		{
		if(!vecvarDpress)
			{
			vecvarDpress = true;

			vecvar++;
			if(vecvar > 17) vecvar = 0;
			printf("vecvar = %i\n", vecvar);
			}
		}
	else vecvarDpress = false;

	if(vecvar == 0)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 1)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 2)
		{
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 3)
		{
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 4)
		{
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 5)
		{
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 6)
		{
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 7)
		{
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 8)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 9)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 10)
		{
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 11)
		{
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 12)
		{
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 13)
		{
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateY(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 14)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 15)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}

	if(vecvar == 16)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		}

	if(vecvar == 17)
		{
		Qpo->Transform_RotateX(&player[g_Player]->Camrot, player[g_Player]->Angles.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
		}
}

	//Sense Avatar View
	if(KEY_DOWN(QIN_g))
		{
		if(!vecvarDpress[0])
			{
			vecvarDpress[0] = true;
			vectrans[vecvar[1]]++;
			if(vectrans[vecvar[1]] > 2) vectrans[vecvar[1]] = 0;

			printf("Transform Row 0 1 - %i %i\n", vectrans[0], vectrans[1]);
			printf("Transform Row 2 3 - %i %i\n", vectrans[2], vectrans[3]);
			printf("Transform Row 4 5 - %i %i\n", vectrans[4], vectrans[5]);
			printf("Transform Row 6 7 - %i %i\n", vectrans[6], vectrans[7]);
			printf("Transform Row 8 9 - %i %i\n", vectrans[8], vectrans[9]);
			printf("Transform Row1011 - %i %i\n", vectrans[10], vectrans[11]);
			printf("Transform Row1213 - %i %i\n", vectrans[12], vectrans[13]);
			printf("Transform Row1415 - %i %i\n", vectrans[14], vectrans[15]);
			printf("Transform Row1617 - %i %i\n", vectrans[16], vectrans[17]);
			printf("_____________\n");

			printf("Transform Row 0 1 - %f\n", i_matrix.m[0][0]);
			printf("Transform Row 2 3 - %f\n", i_matrix.m[0][1]);
			printf("Transform Row 4 5 - %f\n", i_matrix.m[0][2]);
			printf("Transform Row 6 7 - %f\n", i_matrix.m[1][0]);
			printf("Transform Row 8 9 - %f\n", i_matrix.m[1][1]);
			printf("Transform Row1011 - %f\n", i_matrix.m[1][2]);
			printf("Transform Row1213 - %f\n", i_matrix.m[2][0]);
			printf("Transform Row1415 - %f\n", i_matrix.m[2][1]);
			printf("Transform Row1617 - %f\n", i_matrix.m[2][2]);
			printf("_____________\n");
			}
		}
	else vecvarDpress[0] = false;

	if(KEY_DOWN(QIN_f))
		{
		if(!vecvarDpress[1])
			{
			vecvarDpress[1] = true;

			vecvar[1]--;
			if(vecvar[1] > 17) vecvar[1] = 0;
			printf("vecvar = %i\n", vecvar[1]);
			}
		}
	else vecvarDpress[1] = false;

	if(KEY_DOWN(QIN_h))
		{
		if(!vecvarDpress[2])
			{
			vecvarDpress[2] = true;

			vecvar[1]++;
			if(vecvar[1] < 0) vecvar[1] = 17;
			printf("vecvar = %i\n", vecvar[1]);
			}
		}
	else vecvarDpress[2] = false;

	Bone->Matrix.m[0][0] = i_matrix.m[vectrans[0]][vectrans[1]];
	Bone->Matrix.m[0][1] = i_matrix.m[vectrans[2]][vectrans[3]];
	Bone->Matrix.m[0][2] = i_matrix.m[vectrans[4]][vectrans[5]];

	Bone->Matrix.m[1][0] = i_matrix.m[vectrans[6]][vectrans[7]];
	Bone->Matrix.m[1][1] = i_matrix.m[vectrans[8]][vectrans[9]];
	Bone->Matrix.m[1][2] = i_matrix.m[vectrans[10]][vectrans[11]];

	Bone->Matrix.m[2][0] = i_matrix.m[vectrans[12]][vectrans[13]];
	Bone->Matrix.m[2][1] = i_matrix.m[vectrans[14]][vectrans[15]];
	Bone->Matrix.m[2][2] = i_matrix.m[vectrans[16]][vectrans[17]];
#endif

///***## Class Cache Shell Execution Mode ***##///
inline bool Q_PORTShell::CC::setExecMode(int i_ExecMode)
	{
	if(i_ExecMode == m_ExecMode) return false;

	switch(i_ExecMode)
		{
		case CCX_MODE_POLY:
			{
			glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
			glEnable(GL_BLEND);									// Enable Blending
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
			glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
			} break;

		case CCX_MODE_BLIT:
			{
			glGetIntegerv(GL_VIEWPORT, vPort);
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
			} break;

		case CCX_MODE_DRAW:
			{
			glGetIntegerv(GL_VIEWPORT, vPort);
			glDisable(GL_DEPTH_TEST);
			} break;
		}

	m_ExecMode = i_ExecMode;

	return true;
	}

///***## Class Cache Shell Execution Mode ***##///
void Q_PORTShell::resetExecMode(void)
{
	m_CC.m_ExecMode = 55;
}

};