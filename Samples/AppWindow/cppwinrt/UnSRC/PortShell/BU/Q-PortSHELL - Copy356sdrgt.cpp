/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -QAGE Port Shell-
	- Minor Component -Function Definitions-

*/

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

//***## Include Engine Specific Headers ***##

#include "unConsole.h"

#pragma message("Server engine excludes")
#if defined(WIN32)
#include "../Texture/tgaload.h"
#endif

#include "../Avatar/unAvatar.h"

#include <iterator>
#include <iostream>

#pragma message("Server engine excludes")
#if defined(WIN32)
#include "../Sound/Framework.h"
#include "EFX-Util.h"
#endif

#include <math.h>

#include "../../DigitalMass/Source/Mesh/digiMesh.h"

#include "../QActiveFramewrk.h"

extern QAGE::QActiveFramewrk* QActiveFrameWork;

#if 0
#define PORTSHELL_ASSERT_DEBUG
#endif

#define CCX_MODE_NULL 0
#define CCX_MODE_POLY 1
#define CCX_MODE_BLIT 2
#define CCX_MODE_DRAW 3
#define CCX_MODE_MESH 4

#if defined(WIN32)
EAXREVERBPROPERTIES eaxBathroom = REVERB_PRESET_BATHROOM;
EAXREVERBPROPERTIES eaxHangar = REVERB_PRESET_HANGAR;
EFXEAXREVERBPROPERTIES efxReverb;

ALuint uiEffectSlot, uiEffect;
bool uiEffectOn;

ALCdevice		*pDevice;
ALCcontext		*pContext;
ALCdevice		*pCaptureDevice;
const ALCchar	*szDefaultCaptureDevice;
ALint			iSamplesAvailable;
ALint			pCBuffer[QPO_CAPTURE_RATE];
ALint			iDataSize = 0;
ALint			iSize;

int m_ChannelPNT;
#endif

extern float WeaponvalueX;
extern float WeaponvalueY;
extern float WeaponvalueZ;

#if 0
#define QAGEMODE_SURGERY
#endif

using namespace GVARS;

namespace GVARS
{

PxRigidDynamic* g_ForgeCap[QNOMAI];
PxRigidDynamic* g_ForgeCapPlayer;

///// PortSHELL Class Cache /////
#if defined(WIN32)
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
#else
Q_PORTShell::CC m_CC;
#endif

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
	QpoVec3d result;

	//result.x = vec1->x * vec1->x;
	//result.y = vec1->y * vec1->y;
	//result.z = vec1->z * vec1->z;

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

		__asm 
		{
			FLD Dist
			FSQRT
			FSTP Dist
		}

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
	vec1->x = -vec1->x;
	vec1->y = -vec1->y;
	vec1->z = -vec1->z;
	}

#ifndef PS_ASM
float Q_PORTShell::Vec3d_DistanceBetween(QpoVec3d * vec1, QpoVec3d * vec2)
	{
	QpoVec3d result;

	//result = vec1 - vec2;

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
	assert ( V1 != NULL );
	assert ( V2 != NULL );
	assert ( Tolerance >= 0.0 );
	assert( Qpo->Vec3d_IsValid(V1) != false );
	assert( Qpo->Vec3d_IsValid(V2) != false );

	if (fabs(V2->x - V1->x) > Tolerance) //VCOMPARE_EPSILON)
		return false;
	if (fabs(V2->y - V1->y) > Tolerance) //VCOMPARE_EPSILON)
		return false;
	if (fabs(V2->z - V1->z) > Tolerance) //VCOMPARE_EPSILON)
		return false;

	return true;
	}

bool Q_PORTShell::Vec3d_IsValid(QpoVec3d *V)
	{
	if (V == NULL)
		return false;
	if ((V->x * V->x) < 0.0f) 
		return false;
	if ((V->y * V->y) < 0.0f) 
		return false;
	if ((V->z * V->z) < 0.0f) 
		return false;
	return true;
	}

void Q_PORTShell::Transform_New(QpoTransform * transform)
	{
	transform->Matrix.load_identity();

#if 0
	transform->Matrix.m[0][0] =  -1;
	transform->Matrix.m[0][1] =  0;
	transform->Matrix.m[0][2] =  0;
	transform->Matrix.m[0][3] =  0;

	transform->Matrix.m[1][0] =  0;
	transform->Matrix.m[1][1] =  0;
	transform->Matrix.m[1][2] =  1;
	transform->Matrix.m[1][3] =  0;

	transform->Matrix.m[2][0] =  0;
	transform->Matrix.m[2][1] =  1;
	transform->Matrix.m[2][2] =  0;
	transform->Matrix.m[2][3] =  0;

	transform->Matrix.m[3][0] =  0;
	transform->Matrix.m[3][1] =  0;
	transform->Matrix.m[3][2] =  0;
	transform->Matrix.m[3][3] =  1;
#endif

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

	if (transform.Matrix.m[0][0] < Epsilon1_a || transform.Matrix.m[0][0] > Epsilon1_b || 
		transform.Matrix.m[1][0] < -Q_EPSILON || transform.Matrix.m[1][0] > Q_EPSILON || 
		transform.Matrix.m[2][0] < -Q_EPSILON || transform.Matrix.m[2][0] > Q_EPSILON)
		return false;
	if (transform.Matrix.m[0][1] < -Q_EPSILON || transform.Matrix.m[0][1] > Q_EPSILON ||
		transform.Matrix.m[1][1] < Epsilon1_a || transform.Matrix.m[1][1] > Epsilon1_b ||
		transform.Matrix.m[2][1] < -Q_EPSILON || transform.Matrix.m[2][1] > Q_EPSILON)
		return false;
	if (-transform.Matrix.m[0][2] < -Q_EPSILON || -transform.Matrix.m[0][2] > Q_EPSILON ||
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

#if 0
	result->x = -transform->Matrix.m[0][2];
	result->y = -transform->Matrix.m[2][2];
	result->z = -transform->Matrix.m[1][2];

	result->x = transform->Matrix.m[0][0];
	result->y = transform->Matrix.m[2][0];
	result->z = transform->Matrix.m[1][0];

	result->x = transform->Matrix.m[0][2];
	result->y = transform->Matrix.m[2][2];
	result->z = transform->Matrix.m[1][2];
#endif

#if 1
	transform->Matrix.m[0][2] = -left->x;
	transform->Matrix.m[2][2] = -left->y;
	transform->Matrix.m[1][2] = -left->z;
	transform->Matrix.m[0][1] =  up->x;
	transform->Matrix.m[2][1] =  up->y;
	transform->Matrix.m[1][1] =  up->z;
	transform->Matrix.m[0][0] = -in->x;
	transform->Matrix.m[2][0] = -in->y;
	transform->Matrix.m[1][0] = -in->z;
#endif

#if 0
	transform->Matrix.m[0][1] = up->x;
	transform->Matrix.m[2][1] = up->y;
	transform->Matrix.m[1][1] = up->z;
	transform->Matrix.m[0][0] =  -left->x;
	transform->Matrix.m[2][0] =  -left->y;
	transform->Matrix.m[1][0] =  -left->z;
	transform->Matrix.m[0][2] = -in->x;
	transform->Matrix.m[2][2] = -in->y;
	transform->Matrix.m[1][2] = -in->z;
#endif

#if 0
	transform->Matrix.m[0][0] = -left->x;
	transform->Matrix.m[1][0] = -left->y;
	transform->Matrix.m[2][0] = -left->z;
	transform->Matrix.m[0][1] =  up->x;
	transform->Matrix.m[1][1] =  up->y;
	transform->Matrix.m[2][1] =  up->z;
	transform->Matrix.m[0][2] = -in->x;
	transform->Matrix.m[1][2] = -in->y;
	transform->Matrix.m[2][2] = -in->z;
#endif

	transform->Translation.x = 0;
	transform->Translation.y = 0;
	transform->Translation.z = 0;
	}

/// ~~~ IMPORTANT SPEED LOSS HERE ~~~~~~~~ LOSE EXTRA TRANSFORMS
void Q_PORTShell::Transform_Multiply(QpoTransform * transform1, QpoTransform * transform2, QpoTransform * result)
	{
	result->Matrix = transform1->Matrix * transform2->Matrix;

#if 0
	result->Matrix.mf[ 0] = transform2->Matrix.mf[ 0]*transform1->Matrix.mf[0] + transform2->Matrix.mf[ 1]*transform1->Matrix.mf[4] + transform2->Matrix.mf[ 2]*transform1->Matrix.mf[ 8];// + mf[ 3]*transform1->Matrix.mf[12];
	result->Matrix.mf[ 1] = transform2->Matrix.mf[ 0]*transform1->Matrix.mf[1] + transform2->Matrix.mf[ 1]*transform1->Matrix.mf[5] + transform2->Matrix.mf[ 2]*transform1->Matrix.mf[ 9];// + mf[ 3]*transform1->Matrix.mf[13];
	result->Matrix.mf[ 2] = transform2->Matrix.mf[ 0]*transform1->Matrix.mf[2] + transform2->Matrix.mf[ 1]*transform1->Matrix.mf[6] + transform2->Matrix.mf[ 2]*transform1->Matrix.mf[10];// + mf[ 3]*transform1->Matrix.mf[14];
	result->Matrix.mf[ 3] = 0.0f;//mf[ 0]*transform1->Matrix.mf[3] + mf[ 1]*transform1->Matrix.mf[7] + mf[ 2]*transform1->Matrix.mf[11] + mf[ 3]*transform1->Matrix.mf[15];

	result->Matrix.mf[ 4] = transform2->Matrix.mf[ 4]*transform1->Matrix.mf[0] + transform2->Matrix.mf[ 5]*transform1->Matrix.mf[4] + transform2->Matrix.mf[ 6]*transform1->Matrix.mf[ 8];// + mf[ 7]*transform1->Matrix.mf[12];
	result->Matrix.mf[ 5] = transform2->Matrix.mf[ 4]*transform1->Matrix.mf[1] + transform2->Matrix.mf[ 5]*transform1->Matrix.mf[5] + transform2->Matrix.mf[ 6]*transform1->Matrix.mf[ 9];// + mf[ 7]*transform1->Matrix.mf[13];
	result->Matrix.mf[ 6] = transform2->Matrix.mf[ 4]*transform1->Matrix.mf[2] + transform2->Matrix.mf[ 5]*transform1->Matrix.mf[6] + transform2->Matrix.mf[ 6]*transform1->Matrix.mf[10];// + mf[ 7]*transform1->Matrix.mf[14];
	result->Matrix.mf[ 7] = 0.0f;//mf[ 4]*transform1->Matrix.mf[3] + mf[ 5]*transform1->Matrix.mf[7] + mf[ 6]*transform1->Matrix.mf[11] + mf[ 7]*transform1->Matrix.mf[15];

	result->Matrix.mf[ 8] = transform2->Matrix.mf[ 8]*transform1->Matrix.mf[0] + transform2->Matrix.mf[ 9]*transform1->Matrix.mf[4] + transform2->Matrix.mf[10]*transform1->Matrix.mf[ 8];// + mf[11]*transform1->Matrix.mf[12];
	result->Matrix.mf[ 9] = transform2->Matrix.mf[ 8]*transform1->Matrix.mf[1] + transform2->Matrix.mf[ 9]*transform1->Matrix.mf[5] + transform2->Matrix.mf[10]*transform1->Matrix.mf[ 9];// + mf[11]*transform1->Matrix.mf[13];
	result->Matrix.mf[10] = transform2->Matrix.mf[ 8]*transform1->Matrix.mf[2] + transform2->Matrix.mf[ 9]*transform1->Matrix.mf[6] + transform2->Matrix.mf[10]*transform1->Matrix.mf[10];// + mf[11]*transform1->Matrix.mf[14];
	result->Matrix.mf[11] = 0.0f;//mf[ 8]*transform1->Matrix.mf[3] + mf[ 9]*transform1->Matrix.mf[7] + mf[10]*transform1->Matrix.mf[11] + mf[11]*transform1->Matrix.mf[15];

#if 1
	result->Matrix.mf[12] = transform2->Matrix.mf[12]*transform1->Matrix.mf[0] + transform2->Matrix.mf[13]*transform1->Matrix.mf[4] + transform2->Matrix.mf[14]*transform1->Matrix.mf[ 8] + /*mf[15]*/transform1->Matrix.mf[12];
	result->Matrix.mf[13] = transform2->Matrix.mf[12]*transform1->Matrix.mf[1] + transform2->Matrix.mf[13]*transform1->Matrix.mf[5] + transform2->Matrix.mf[14]*transform1->Matrix.mf[ 9] + /*mf[15]*/transform1->Matrix.mf[13];
	result->Matrix.mf[14] = transform2->Matrix.mf[12]*transform1->Matrix.mf[2] + transform2->Matrix.mf[13]*transform1->Matrix.mf[6] + transform2->Matrix.mf[14]*transform1->Matrix.mf[10] + /*mf[15]*/transform1->Matrix.mf[14];
	result->Matrix.mf[15] = 1.0f;//mf[12]*transform1->Matrix.mf[3] + mf[13]*transform1->Matrix.mf[7] + mf[14]*transform1->Matrix.mf[11] + mf[15]*transform1->Matrix.mf[15];
#endif
#endif

#if 0
	result->Matrix.m[0][0] = transform1->Matrix.m[0][0] * transform2->Matrix.m[0][0];
	result->Matrix.m[0][0] += transform1->Matrix.m[0][1] * transform2->Matrix.m[1][0];
	result->Matrix.m[0][0] += transform1->Matrix.m[0][2] * transform2->Matrix.m[2][0];

	result->Matrix.m[0][1] = transform1->Matrix.m[0][0] * transform2->Matrix.m[0][1];
	result->Matrix.m[0][1] += transform1->Matrix.m[0][1] * transform2->Matrix.m[1][1];
	result->Matrix.m[0][1] += transform1->Matrix.m[0][2] * transform2->Matrix.m[2][1];

	result->Matrix.m[0][2] = transform1->Matrix.m[0][0] * transform2->Matrix.m[0][2];
	result->Matrix.m[0][2] += transform1->Matrix.m[0][1] * transform2->Matrix.m[1][2];
	result->Matrix.m[0][2] += transform1->Matrix.m[0][2] * transform2->Matrix.m[2][2];

	result->Matrix.m[1][0] = transform1->Matrix.m[1][0] * transform2->Matrix.m[0][0];
	result->Matrix.m[1][0] += transform1->Matrix.m[1][1] * transform2->Matrix.m[1][0];
	result->Matrix.m[1][0] += transform1->Matrix.m[1][2] * transform2->Matrix.m[2][0];

	result->Matrix.m[1][1] = transform1->Matrix.m[1][0] * transform2->Matrix.m[0][1];
	result->Matrix.m[1][1] += transform1->Matrix.m[1][1] * transform2->Matrix.m[1][1];
	result->Matrix.m[1][1] += transform1->Matrix.m[1][2] * transform2->Matrix.m[2][1];

	result->Matrix.m[1][2] = transform1->Matrix.m[1][0] * transform2->Matrix.m[0][2];
	result->Matrix.m[1][2] += transform1->Matrix.m[1][1] * transform2->Matrix.m[1][2];
	result->Matrix.m[1][2] += transform1->Matrix.m[1][2] * transform2->Matrix.m[2][2];

	result->Matrix.m[2][0] = transform1->Matrix.m[2][0] * transform2->Matrix.m[0][0];
	result->Matrix.m[2][0] += transform1->Matrix.m[2][1] * transform2->Matrix.m[1][0];
	result->Matrix.m[2][0] += transform1->Matrix.m[2][2] * transform2->Matrix.m[2][0];

	result->Matrix.m[2][1] = transform1->Matrix.m[2][0] * transform2->Matrix.m[0][1];
	result->Matrix.m[2][1] += transform1->Matrix.m[2][1] * transform2->Matrix.m[1][1];
	result->Matrix.m[2][1] += transform1->Matrix.m[2][2] * transform2->Matrix.m[2][1];

	result->Matrix.m[2][2] = transform1->Matrix.m[2][0] * transform2->Matrix.m[0][2];
	result->Matrix.m[2][2] += transform1->Matrix.m[2][1] * transform2->Matrix.m[1][2];
	result->Matrix.m[2][2] += transform1->Matrix.m[2][2] * transform2->Matrix.m[2][2];
#endif
	}

#if 0
/// ~~~ IMPORTANT SPEED LOSS HERE ~~~~~~~~ LOSE EXTRA TRANSFORMS
void Q_PORTShell::Transform_Multiply(QpoTransform * transform1, QpoTransform * transform2, QpoTransform * result)
	{
	Mat44f *Matrix = new Mat44f;// = result->Matrix.getMatrix();

	assert(Transform_IsOrthogonal(transform1) == true);
	assert(Transform_IsOrthogonal(transform2) == true);

	//Matrix->set(Vec4f(,,,)

	Matrix[0][0] =  transform1->Matrix.m[0][0] * transform2->Matrix.m[0][0];
	Matrix[0][0] += transform1->Matrix.m[0][1] * transform2->Matrix.m[1][0];
	Matrix[0][0] += transform1->Matrix.m[0][2] * transform2->Matrix.m[2][0];

	Matrix[0][1] =  transform1->Matrix.m[0][0] * transform2->Matrix.m[0][1];
	Matrix[0][1] += transform1->Matrix.m[0][1] * transform2->Matrix.m[1][1];
	Matrix[0][1] += transform1->Matrix.m[0][2] * transform2->Matrix.m[2][1];

	Matrix[0][2] =  transform1->Matrix.m[0][0] * transform2->Matrix.m[0][2];
	Matrix[0][2] += transform1->Matrix.m[0][1] * transform2->Matrix.m[1][2];
	Matrix[0][2] += transform1->Matrix.m[0][2] * transform2->Matrix.m[2][2];

	Matrix[1][0] =  transform1->Matrix.m[1][0] * transform2->Matrix.m[0][0];
	Matrix[1][0] += transform1->Matrix.m[1][1] * transform2->Matrix.m[1][0];
	Matrix[1][0] += transform1->Matrix.m[1][2] * transform2->Matrix.m[2][0];

	Matrix[1][1] =  transform1->Matrix.m[1][0] * transform2->Matrix.m[0][1];
	Matrix[1][1] += transform1->Matrix.m[1][1] * transform2->Matrix.m[1][1];
	Matrix[1][1] += transform1->Matrix.m[1][2] * transform2->Matrix.m[2][1];

	Matrix[1][2] =  transform1->Matrix.m[1][0] * transform2->Matrix.m[0][2];
	Matrix[1][2] += transform1->Matrix.m[1][1] * transform2->Matrix.m[1][2];
	Matrix[1][2] += transform1->Matrix.m[1][2] * transform2->Matrix.m[2][2];

	Matrix[2][0] =  transform1->Matrix.m[2][0] * transform2->Matrix.m[0][0];
	Matrix[2][0] += transform1->Matrix.m[2][1] * transform2->Matrix.m[1][0];
	Matrix[2][0] += transform1->Matrix.m[2][2] * transform2->Matrix.m[2][0];

	Matrix[2][1] =  transform1->Matrix.m[2][0] * transform2->Matrix.m[0][1];
	Matrix[2][1] += transform1->Matrix.m[2][1] * transform2->Matrix.m[1][1];
	Matrix[2][1] += transform1->Matrix.m[2][2] * transform2->Matrix.m[2][1];

	Matrix[2][2] =  transform1->Matrix.m[2][0] * transform2->Matrix.m[0][2];
	Matrix[2][2] += transform1->Matrix.m[2][1] * transform2->Matrix.m[1][2];
	Matrix[2][2] += transform1->Matrix.m[2][2] * transform2->Matrix.m[2][2];

	result->Translation.x =  transform1->Matrix.m[0][0] * transform2->Translation.x;
	result->Translation.x += transform1->Matrix.m[0][1] * transform2->Translation.y;
	result->Translation.x += transform1->Matrix.m[0][2] * transform2->Translation.z;
	result->Translation.x += transform1->Translation.x;

	result->Translation.y =  transform1->Matrix.m[1][0] * transform2->Translation.x;
	result->Translation.y += transform1->Matrix.m[1][1] * transform2->Translation.y;
	result->Translation.y += transform1->Matrix.m[1][2] * transform2->Translation.z;
	result->Translation.y += transform1->Translation.y;

	result->Translation.z =  transform1->Matrix.m[2][0] * transform2->Translation.x;
	result->Translation.z += transform1->Matrix.m[2][1] * transform2->Translation.y;
	result->Translation.z += transform1->Matrix.m[2][2] * transform2->Translation.z;
	result->Translation.z += transform1->Translation.z;

	assert(Transform_IsOrthogonal(result) == true);

	result->Matrix.setMatrix( &Matrix );
	}
#endif

#if 0
/// ~~~ IMPORTANT SPEED LOSS HERE ~~~~~~~~ LOSE EXTRA TRANSFORMS
void Q_PORTShell::Transform_Multiply(QpoTransform * transform1, QpoTransform * transform2, QpoTransform * result)
	{
	Mat44f Matrix;// = result->Matrix.getMatrix();

	assert(Transform_IsOrthogonal(transform1) == true);
	assert(Transform_IsOrthogonal(transform2) == true);

	Matrix[0][0] =  transform1->Matrix.m[0][0] * transform2->Matrix.m[0][0];
	Matrix[0][0] += transform1->Matrix.m[0][2] * transform2->Matrix.m[1][0];
	Matrix[0][0] += transform1->Matrix.m[0][1] * transform2->Matrix.m[2][0];

	Matrix[0][1] =  transform1->Matrix.m[0][0] * transform2->Matrix.m[0][2];
	Matrix[0][1] += transform1->Matrix.m[0][2] * transform2->Matrix.m[1][2];
	Matrix[0][1] += transform1->Matrix.m[0][1] * transform2->Matrix.m[2][2];

	Matrix[0][2] =  transform1->Matrix.m[0][0] * transform2->Matrix.m[0][1];
	Matrix[0][2] += transform1->Matrix.m[0][2] * transform2->Matrix.m[1][1];
	Matrix[0][2] += transform1->Matrix.m[0][1] * transform2->Matrix.m[2][1];

	Matrix[1][0] =  transform1->Matrix.m[1][0] * transform2->Matrix.m[0][0];
	Matrix[1][0] += transform1->Matrix.m[1][2] * transform2->Matrix.m[1][0];
	Matrix[1][0] += transform1->Matrix.m[1][1] * transform2->Matrix.m[2][0];

	Matrix[1][1] =  transform1->Matrix.m[1][0] * transform2->Matrix.m[0][2];
	Matrix[1][1] += transform1->Matrix.m[1][2] * transform2->Matrix.m[1][2];
	Matrix[1][1] += transform1->Matrix.m[1][1] * transform2->Matrix.m[2][2];

	Matrix[1][2] =  transform1->Matrix.m[1][0] * transform2->Matrix.m[0][1];
	Matrix[1][2] += transform1->Matrix.m[1][2] * transform2->Matrix.m[1][1];
	Matrix[1][2] += transform1->Matrix.m[1][1] * transform2->Matrix.m[2][1];

	Matrix[2][0] =  transform1->Matrix.m[2][0] * transform2->Matrix.m[0][0];
	Matrix[2][0] += transform1->Matrix.m[2][2] * transform2->Matrix.m[1][0];
	Matrix[2][0] += transform1->Matrix.m[2][1] * transform2->Matrix.m[2][0];

	Matrix[2][1] =  transform1->Matrix.m[2][0] * transform2->Matrix.m[0][2];
	Matrix[2][1] += transform1->Matrix.m[2][2] * transform2->Matrix.m[1][2];
	Matrix[2][1] += transform1->Matrix.m[2][1] * transform2->Matrix.m[2][2];

	Matrix[2][2] =  transform1->Matrix.m[2][0] * transform2->Matrix.m[0][1];
	Matrix[2][2] += transform1->Matrix.m[2][1] * transform2->Matrix.m[1][1];
	Matrix[2][2] += transform1->Matrix.m[2][2] * transform2->Matrix.m[2][1];

	result->Translation.x =  transform1->Matrix.m[0][0] * transform2->Translation.x;
	result->Translation.x += transform1->Matrix.m[0][2] * transform2->Translation.y;
	result->Translation.x += transform1->Matrix.m[0][1] * transform2->Translation.z;
	result->Translation.x += transform1->Translation.x;

	result->Translation.y =  transform1->Matrix.m[1][0] * transform2->Translation.x;
	result->Translation.y += transform1->Matrix.m[1][2] * transform2->Translation.y;
	result->Translation.y += transform1->Matrix.m[1][1] * transform2->Translation.z;
	result->Translation.y += transform1->Translation.y;

	result->Translation.z =  transform1->Matrix.m[2][0] * transform2->Translation.x;
	result->Translation.z += transform1->Matrix.m[2][2] * transform2->Translation.y;
	result->Translation.z += transform1->Matrix.m[2][1] * transform2->Translation.z;
	result->Translation.z += transform1->Translation.z;

	assert(Transform_IsOrthogonal(result) == true);

	result->Matrix.setMatrix( Matrix );
	}
#endif

void Q_PORTShell::Transform_QpotoPx(QpoTransform * transform1, PxMat44 * PxMatrix)
	{
	PxMatrix->column0.x = transform1->Matrix.get_column4(0).x;
	PxMatrix->column0.y = transform1->Matrix.get_column4(0).y;
	PxMatrix->column0.z = transform1->Matrix.get_column4(0).z;
	PxMatrix->column0.w = 0;

	PxMatrix->column1.x = transform1->Matrix.get_column4(2).x;
	PxMatrix->column1.y = transform1->Matrix.get_column4(2).y;
	PxMatrix->column1.z = transform1->Matrix.get_column4(1).z;
	PxMatrix->column1.w = 0;

	PxMatrix->column2.x = transform1->Matrix.get_column4(1).x * -1;
	PxMatrix->column2.y = transform1->Matrix.get_column4(1).y * -1;
	PxMatrix->column2.z = transform1->Matrix.get_column4(2).z * -1;
	PxMatrix->column2.w = 0;

	PxMatrix->column3.x = transform1->Matrix.get_column4(3).x;
	PxMatrix->column3.y = transform1->Matrix.get_column4(3).y;
	PxMatrix->column3.z = transform1->Matrix.get_column4(3).z;
	PxMatrix->column3.w = 1;
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
	result->x = transform->Matrix.m[0][1];
	result->y = transform->Matrix.m[2][1];
	result->z = transform->Matrix.m[1][1];
	}

void Q_PORTShell::Transform_GetLeft(QpoTransform * transform, QpoVec3d * result)
	// Gets a vector that is 'left' in the frame of reference of transform->Matrix.getMatrix() (facing -Z)
	{
	result->x = transform->Matrix.m[0][0];
	result->y = transform->Matrix.m[2][0];
	result->z = transform->Matrix.m[1][0];
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
	result->x = transform->Matrix.m[0][2];
	result->y = transform->Matrix.m[2][2];
	result->z = transform->Matrix.m[1][2];
	}

void Q_PORTShell::Transform_GetIn(pMatrix * transform, QpoVec3d * result)
	// Gets a vector that is 'in' in the frame of reference of Matrix.getMatrix() (facing -Z)
	{
	result->x = -transform->m[0][2];
	result->y = -transform->m[2][2];
	result->z = -transform->m[1][2];
	}

void Q_PORTShell::Transform_GetLeft(pMatrix * transform, QpoVec3d * result)
	// Gets a vector that is 'left' in the frame of reference of Matrix.getMatrix() (facing -Z)
	{
	result->x = transform->m[0][0];
	result->y = transform->m[0][1];
	result->z = transform->m[0][2];
	}

void Q_PORTShell::Transform_GetUp(pMatrix * transform, QpoVec3d * result)
	// Gets a vector that is 'up' in the frame of reference of Matrix.getMatrix() (facing -Z)
	{
	result->x = -transform->m[1][0];
	result->y = -transform->m[1][1];
	result->z = -transform->m[1][2];
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
#if 0
	float				Dist;
	QpoVec3d			In, Left, Up;
	QpoTransform		*Original = 0;
	QpoVec3d			MirrorTranslation;

#ifdef PORTSHELL_ASSERT_DEBUG
	assert ( Qpo->Transform_IsOrthogonal(source) == true );
	assert( planenormal != NULL );
	assert( result        != NULL );
#endif

	*Original = *source;

	// Mirror the translation portion of the matrix
	Dist = Qpo->Vec3d_DotProduct(&Original->Translation, planenormal) - planedist;
	Qpo->Vec3d_AddScaled(&Original->Translation, -Dist*2.0f, planenormal, &MirrorTranslation);

	// Mirror the Rotational portion of the xform first
	Qpo->Transform_GetIn(Original, &In);
	Qpo->Vec3d_Add(&Original->Translation, &In, &In);
	Dist = Qpo->Vec3d_DotProduct(&In, planenormal) - planedist;
	Qpo->Vec3d_AddScaled(&In, -Dist*2.0f, planenormal, &In);
	Qpo->Vec3d_Subtract(&In, &MirrorTranslation, &In);
	Qpo->Vec3d_Normalize(&In);

	Qpo->Transform_GetLeft(Original, &Left);
	Qpo->Vec3d_Add(&Original->Translation, &Left, &Left);
	Dist = Qpo->Vec3d_DotProduct(&Left, planenormal) - planedist;
	Qpo->Vec3d_AddScaled(&Left, -Dist*2.0f, planenormal, &Left);
	Qpo->Vec3d_Subtract(&Left, &MirrorTranslation, &Left);
	Qpo->Vec3d_Normalize(&Left);

	Qpo->Transform_GetUp(Original, &Up);
	Qpo->Vec3d_Add(&Original->Translation, &Up, &Up);
	Dist = Qpo->Vec3d_DotProduct(&Up, planenormal) - planedist;
	Qpo->Vec3d_AddScaled(&Up, -Dist*2.0f, planenormal, &Up);
	Qpo->Vec3d_Subtract(&Up, &MirrorTranslation, &Up);
	Qpo->Vec3d_Normalize(&Up);

	Qpo->Transform_New_LeftUpIn(result, &Left, &Up, &In);

	// Must set the mirror translation here since Qpo->Transform_SetFromLeftUpIn cleared the translation portion
	Qpo->Vec3d_Set(&result->Translation, MirrorTranslation.x, MirrorTranslation.y, MirrorTranslation.z);

#ifdef PORTSHELL_ASSERT_DEBUG
	assert( Qpo->Transform_IsOrthogonal(result) == true );
#endif
#endif
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

	IsOrthonormal = Qpo->Vec3d_Compare(&Col1CrossCol2,&Col3,ORTHONORMAL_TOLERANCE);
	if (IsOrthonormal == false)
		{
		Qpo->Vec3d_Inverse(&Col3);
		IsOrthonormal = Qpo->Vec3d_Compare(&Col1CrossCol2,&Col3,ORTHONORMAL_TOLERANCE);
		}

	if (Qpo->Vec3d_IsValid(&(transform->Translation)) ==false)
		return false;

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
	if (IsOrthogonal == false)
		{
		Qpo->Vec3d_Inverse(&Col3);
		IsOrthogonal = Qpo->Vec3d_Compare(&Col1CrossCol2,&Col3,ORTHOGONAL_TOLERANCE);
		}

	if (Qpo->Vec3d_IsValid(&(transform->Translation)) ==false)
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
void Q_PORTShell::Poly_AddOnce(QpoVertex * Verts, int NumVerts, unsigned int Bitmap, UInt8 TypeFLAGS, UInt8 RendFLAGS, float Scale)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	if(g_render->view.is_inside(pVector(Verts[0].x, Verts[0].y, Verts[0].z)))
		{
		m_CC.setExecMode(CCX_MODE_POLY);
		m_CC.ScaleFT = Scale/2;

#if 0
		//##==-- TYPE
		if(NumVerts == 1 || TypeFLAGS == 0) { QCH.PolyONCE[QCH.NomPOLY].TYPE = QPOLY_TYPE_PNT; }
		if(TypeFLAGS == 1)					{ QCH.PolyONCE[QCH.NomPOLY].TYPE = QPOLY_TYPE_TRI; }
		if(TypeFLAGS == 2)					{ QCH.PolyONCE[QCH.NomPOLY].TYPE = QPOLY_TYPE_GOR; }
#endif

#if 0
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glEnable(GL_BLEND);									// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		g_render->set_camera();
#endif

		g_render->set_camera();

#if 0
		glBindTexture(GL_TEXTURE_2D, 1);			// Select Our Texture

		if(QPOLY_TYPE_PNT)
			{
			//Verts->x = g_render->camera.pos.x;
			//Verts->y = g_render->camera.pos.y;
			//Verts->z = g_render->camera.pos.z + 15;
			Verts->x = 0;
			Verts->y = 0;
			Verts->z = 0;
			Verts->a = 1;
			Verts->r = 1;
			Verts->g = 1;
			Verts->b = 1;
			m_CC.ScaleFT = 2;

			glColor4f(Verts->r, Verts->g, Verts->b, Verts->a);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
				glTexCoord2d(1,1); glVertex3f(Verts->x+m_CC.ScaleFT, Verts->y+m_CC.ScaleFT, Verts->z); // Top Right
				glTexCoord2d(0,1); glVertex3f(Verts->x-m_CC.ScaleFT, Verts->y+m_CC.ScaleFT, Verts->z); // Top Left
				glTexCoord2d(1,0); glVertex3f(Verts->x+m_CC.ScaleFT, Verts->y-m_CC.ScaleFT, Verts->z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(Verts->x-m_CC.ScaleFT, Verts->y-m_CC.ScaleFT, Verts->z); // Bottom Left
			glEnd();										// Done Building Triangle Strip
			}
#endif

#if 0
		glBindTexture(GL_TEXTURE_2D, Bitmap);			// Select Our Texture

		if(QPOLY_TYPE_PNT)
			{
			glColor4f(Verts->r, Verts->g, Verts->b, Verts->a);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
				glTexCoord2d(1,1); glVertex3f(Verts->x+m_CC.ScaleFT, Verts->y+m_CC.ScaleFT, Verts->z); // Top Right
				glTexCoord2d(0,1); glVertex3f(Verts->x-m_CC.ScaleFT, Verts->y+m_CC.ScaleFT, Verts->z); // Top Left
				glTexCoord2d(1,0); glVertex3f(Verts->x+m_CC.ScaleFT, Verts->y-m_CC.ScaleFT, Verts->z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(Verts->x-m_CC.ScaleFT, Verts->y-m_CC.ScaleFT, Verts->z); // Bottom Left
			glEnd();										// Done Building Triangle Strip
			}
#endif


		/*g_render->set_camera();
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glEnable(GL_BLEND);									// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping*/

		glBindTexture(GL_TEXTURE_2D, Bitmap);			// Select Our Texture

#if 0
		Verts->a = 1;
		Verts->r = 0.5;
		Verts->g = 0.5;
		Verts->b = 0.5;
#endif

		//if(NumVerts == 1 || TypeFLAGS == 0) { QCH.PolyONCE[QCH.NomPOLY].TYPE = QPOLY_TYPE_PNT; }
		//if(TypeFLAGS == 1)					{ QCH.PolyONCE[QCH.NomPOLY].TYPE = QPOLY_TYPE_TRI; }
		//if(TypeFLAGS == 2)

		if(TypeFLAGS == QPOLY_TYPE_PNT)
			{
			Qpo->Transform_GetIn(&g_render->camera.mat, &m_CC.InVec);
			Qpo->Transform_GetUp(&g_render->camera.mat, &m_CC.UpVec);
			Qpo->Transform_GetLeft(&g_render->camera.mat, &m_CC.LeftVec);

			m_CC.destpos.x = Verts->x;
			m_CC.destpos.y = Verts->y;
			m_CC.destpos.z = Verts->z;

			m_CC.ScaleFT = Scale * 150;
			//m_CC.ScaleFT = 5;

			m_CC.m_Red = Verts->r / 255;
			m_CC.m_Green = Verts->g / 255;
			m_CC.m_Blue = Verts->b / 255;
			m_CC.m_Alpha = Verts->a / 255;

			//glColor4ub(Verts->r, Verts->g, Verts->b, Verts->a);
			glColor4f(m_CC.m_Red, m_CC.m_Green, m_CC.m_Blue, m_CC.m_Alpha);
			glBegin(GL_TRIANGLE_STRIP);

			Qpo->Vec3d_AddScaled(&m_CC.destpos, -m_CC.ScaleFT/2, &m_CC.LeftVec, &m_CC.transvert);
			Qpo->Vec3d_AddScaled(&m_CC.transvert, m_CC.ScaleFT/2, &m_CC.UpVec, &m_CC.transvert);

			glTexCoord2d(1,1); glVertex3f(m_CC.transvert.x, m_CC.transvert.y, m_CC.transvert.z); // Top Right

			Qpo->Vec3d_AddScaled(&m_CC.destpos, m_CC.ScaleFT/2, &m_CC.LeftVec, &m_CC.transvert);
			Qpo->Vec3d_AddScaled(&m_CC.transvert, m_CC.ScaleFT/2, &m_CC.UpVec, &m_CC.transvert);

			glTexCoord2d(0,1); glVertex3f(m_CC.transvert.x, m_CC.transvert.y, m_CC.transvert.z); // Top Left

			Qpo->Vec3d_AddScaled(&m_CC.destpos, -m_CC.ScaleFT/2, &m_CC.LeftVec, &m_CC.transvert);
			Qpo->Vec3d_AddScaled(&m_CC.transvert, -m_CC.ScaleFT/2, &m_CC.UpVec, &m_CC.transvert);

			glTexCoord2d(1,0); glVertex3f(m_CC.transvert.x, m_CC.transvert.y, m_CC.transvert.z); // Bottom Right

			Qpo->Vec3d_AddScaled(&m_CC.destpos, m_CC.ScaleFT/2, &m_CC.LeftVec, &m_CC.transvert);
			Qpo->Vec3d_AddScaled(&m_CC.transvert, -m_CC.ScaleFT/2, &m_CC.UpVec, &m_CC.transvert);

			glTexCoord2d(0,0); glVertex3f(m_CC.transvert.x, m_CC.transvert.y, m_CC.transvert.z); // Bottom Left

			glEnd();
			}

		if(TypeFLAGS == QPOLY_TYPE_TRI)
			{
			m_CC.ScaleFT = 5;

			m_CC.m_Red = Verts->r / 255;
			m_CC.m_Green = Verts->g / 255;
			m_CC.m_Blue = Verts->b / 255;
			m_CC.m_Alpha = Verts->a / 255;

			//glColor4ub(Verts->r, Verts->g, Verts->b, Verts->a);
			glColor4f(m_CC.m_Red, m_CC.m_Green, m_CC.m_Blue, m_CC.m_Alpha);

			if(NumVerts == 3)
				{
				glBegin(GL_POLYGON);

				//glTexCoord2d(1,1);
				glTexCoord2d(Verts[0].u, Verts[0].v);
				glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

				//glTexCoord2d(0,1);
				glTexCoord2d(Verts[1].u, Verts[1].v);
				glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				//glTexCoord2d(1,0);
				glTexCoord2d(Verts[2].u, Verts[2].v);
				glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right

				//glEnd();
				//glBegin(GL_POLYGON);

				//### Reverse Winding
				//glTexCoord2d(1,1);
				glTexCoord2d(Verts[2].u, Verts[2].v);
				glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Right

				//glTexCoord2d(0,1);
				glTexCoord2d(Verts[1].u, Verts[1].v);
				glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				//glTexCoord2d(1,0);
				glTexCoord2d(Verts[0].u, Verts[0].v);
				glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Right

				glEnd();
				}
			else
				{
				if(NumVerts == 4)
					{
					glBegin(GL_QUADS);

					//glTexCoord2d(1,1);
					glTexCoord2d(Verts[0].u, Verts[0].v);
					glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

					//glTexCoord2d(0,1);
					glTexCoord2d(Verts[1].u, Verts[1].v);
					glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

					//glTexCoord2d(1,0);
					glTexCoord2d(Verts[2].u, Verts[2].v);
					glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right

					//glTexCoord2d(0,0);
					glTexCoord2d(Verts[3].u, Verts[3].v);
					glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Bottom Left

					//### Reverse Winding
					//glTexCoord2d(1,1);
					glTexCoord2d(Verts[3].u, Verts[3].v);
					glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Top Right

					//glTexCoord2d(0,1);
					glTexCoord2d(Verts[2].u, Verts[2].v);
					glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Left

					//glTexCoord2d(1,0);
					glTexCoord2d(Verts[1].u, Verts[1].v);
					glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Bottom Right

					//glTexCoord2d(0,0);
					glTexCoord2d(Verts[0].u, Verts[0].v);
					glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Left

					glEnd();
					}
				}
			}

		if(TypeFLAGS == QPOLY_TYPE_GOR)
			{
			m_CC.ScaleFT = 5;

			m_CC.m_Red = Verts->r / 255;
			m_CC.m_Green = Verts->g / 255;
			m_CC.m_Blue = Verts->b / 255;
			m_CC.m_Alpha = Verts->a / 255;

			//glColor4ub(Verts->r, Verts->g, Verts->b, Verts->a);
			glColor4f(m_CC.m_Red, m_CC.m_Green, m_CC.m_Blue, m_CC.m_Alpha);

			if(NumVerts == 3)
				{
				glBegin(GL_POLYGON);

				//glTexCoord2d(1,1);
				glTexCoord2d(Verts[0].u, Verts[0].v);
				glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

				//glTexCoord2d(0,1);
				glTexCoord2d(Verts[1].u, Verts[1].v);
				glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				//glTexCoord2d(1,0);
				glTexCoord2d(Verts[2].u, Verts[2].v);
				glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right

				//glEnd();
				//glBegin(GL_POLYGON);

				//### Reverse Winding
				//glTexCoord2d(1,1);
				glTexCoord2d(Verts[2].u, Verts[2].v);
				glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Right

				//glTexCoord2d(0,1);
				glTexCoord2d(Verts[1].u, Verts[1].v);
				glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				//glTexCoord2d(1,0);
				glTexCoord2d(Verts[0].u, Verts[0].v);
				glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Right

				glEnd();
				}

			if(NumVerts == 4)
				{
				glBegin(GL_QUADS);

				//glTexCoord2d(1,1);
				glTexCoord2d(Verts[0].u, Verts[0].v);
				glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

				//glTexCoord2d(0,1);
				glTexCoord2d(Verts[1].u, Verts[1].v);
				glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				//glTexCoord2d(1,0);
				glTexCoord2d(Verts[2].u, Verts[2].v);
				glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right

				//glTexCoord2d(0,0);
				glTexCoord2d(Verts[3].u, Verts[3].v);
				glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Bottom Left

				//### Reverse Winding
				//glTexCoord2d(1,1);
				glTexCoord2d(Verts[3].u, Verts[3].v);
				glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Top Right

				//glTexCoord2d(0,1);
				glTexCoord2d(Verts[2].u, Verts[2].v);
				glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Left

				//glTexCoord2d(1,0);
				glTexCoord2d(Verts[1].u, Verts[1].v);
				glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Bottom Right

				//glTexCoord2d(0,0);
				glTexCoord2d(Verts[0].u, Verts[0].v);
				glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Left

				glEnd();
				}
			}
		}

	/// Class Cache PolyOnceMode
#endif
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

	QpoPolygon * FROZENFIX;
	return FROZENFIX;
	}

void Q_PORTShell::Draw_FillRect(const QpoRect *Rect, const QpoColor *Color)
	{
	m_CC.setExecMode(CCX_MODE_DRAW);

	///// Texture Print /////
	glColor4f(Color->red, Color->green, Color->blue, Color->alpha);

	glBegin( GL_QUADS );
	glTexCoord2i(1, 0);
	glVertex2d(Rect->xmin, Rect->ymin);
	glTexCoord2i(0, 0);
	glVertex2d(Rect->xmax, Rect->ymin);
	glTexCoord2i(0, 1);
	glVertex2d(Rect->xmax, Rect->ymax);
	glTexCoord2i(1, 1);
	glVertex2d(Rect->xmin, Rect->ymax);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	}

void Q_PORTShell::Body_GetBone(QpoBody * Body, int BoneIndex, const char **BoneName, QpoTransform * Attachment, int * ParBone)
	{
	//FROZEN
	}

void Q_PORTShell::Light_Remove(QpoLight light)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
#if 0
	int nl = _->mesh->nlight - 1;
	int i_counter = 0;

	pLight *tmp = new pLight[nl];

	for(int i=0; i < _->mesh->nlight && i < nl; i++)
		{
		if(i_counter != light)
			{
			tmp[i_counter] = _->mesh->light[i];
			i_counter++;
			}

		//printf("Trace %i\n", i);
		}

	delete[] _->mesh->light;
	_->mesh->light=tmp;
	_->mesh->nlight=nl;
#endif

	_->mesh->light[(int)light].m_Live = false;
#endif
	}

/// ~~~ IMPORTANT SPEED LOSS HERE ~~~~~~~~ COLLAPSE TO SINGLE FUNCTION AND USE NEW FUNCTION
/*QpoLight * Q_PORTShell::Light_AddtoWorld(void)
	{
	QpoLight * lighthandle = 0;

	float floatvar = new float;
	float floatver = malloc(sizeof(float));

	return lighthandle;
	}*/

QpoLight Q_PORTShell::Light_AddtoWorld(QpoVec3d pos)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	for(int k=0; k < _->mesh->nlight; k++)
		{
		if(!_->mesh->light[k].m_Live)
			{
			_->mesh->light[k].m_Live = true;
			_->mesh->light[k].pos.x = pos.x;
			_->mesh->light[k].pos.y = pos.y;
			_->mesh->light[k].pos.z = pos.z;
			_->mesh->light[k].pos.w = 1;

			_->mesh->light[k].color.x = 1;
			_->mesh->light[k].color.y = 1;
			_->mesh->light[k].color.z = 1;

#if 0
			_->mesh->light[k].color.x = 0.175;
			_->mesh->light[k].color.y = 0.175;
			_->mesh->light[k].color.z = 0.175;
#endif

			_->mesh->light[k].flags = 3;

			return k;
			}
		}

	int nl = _->mesh->nlight + 1;

	pLight *tmp=0;
	tmp=new pLight[nl];
	/*if (_->mesh->light)*/ for(int i=0; i<_->mesh->nlight&&i<nl ;i++) tmp[i] = _->mesh->light[i];

	delete[] _->mesh->light;
	_->mesh->light=tmp;
	_->mesh->nlight=nl;

	pLight *i_Light = &_->mesh->light[_->mesh->nlight - 1];

	i_Light->pos.x = pos.x;
	i_Light->pos.y = pos.y;
	i_Light->pos.z = pos.z;
	i_Light->pos.w = 1;

	i_Light->color.x = 0.175;
	i_Light->color.y = 0.175;
	i_Light->color.z = 0.175;

	i_Light->flags = 3;

#if 0
	i_Light->anim_pos_x = pos.x;
	i_Light->anim_pos_y = pos.y;
	i_Light->anim_pos_z = pos.z;
#endif

#if 0
	i_Light->anim_radius.read(fp,ver);
	i_Light->anim_color.read(fp,ver);
#endif

	return _->mesh->nlight - 1;
#endif
	}

void Q_PORTShell::Light_SetAttr(QpoLight Light, QpoVec3d *Pos, QpoColor *RGBA, float Radius, bool CastShadow)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	if(Light < _->mesh->nlight)
		{
		pLight *i_Light = &_->mesh->light[(int)Light];

		i_Light->pos.x = Pos->x;
		i_Light->pos.y = Pos->y;
		i_Light->pos.z = Pos->z;
		i_Light->pos.w = 350;

		i_Light->color.x = RGBA->red/255;
		i_Light->color.y = RGBA->green/255;
		i_Light->color.z = RGBA->blue/255;

		i_Light->flags = 3;	//CastShadow

#if 0
		i_Light->anim_pos_x = Pos.x;
		i_Light->anim_pos_y = Pos.y;
		i_Light->anim_pos_z = Pos.z;
#endif

#if 0
		i_Light->anim_radius.read(fp,ver);
		i_Light->anim_color.read(fp,ver);
#endif
		}
#endif
	}

#pragma message("Server engine excludes")
bool Q_PORTShell::Sound_Init(void)
	{
#if defined(WIN32)
	//******# Init SDL ***************##
	//*********************************#
	//----------------------------------
	if(SDL_Init(SDL_INIT_AUDIO) == -1)
		{
		std::cerr << "ERROR::: SDL ::: Initialization" << std::endl;
		while(1) { /* Infinite Loop */ }
		}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
		std::cerr << "ERROR::: SDL_Mixer ::: Mix_OpenAudio" << std::endl;
		while(1) { /* Infinite Loop */ }
		}
#endif

    return 0;
}

void Q_PORTShell::Sound_Capture_Start(void)
{
	// Start audio capture
	alcCaptureStart(pCaptureDevice);

	iSamplesAvailable = 0;
}

bool Q_PORTShell::Sound_Capture_Progress(void)
{
	// Find out how many samples have been captured
	alcGetIntegerv(pCaptureDevice, ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);

#if 0
	printf("Samples available : %d\n", iSamplesAvailable);
#endif

			// When we have enough data to fill our BUFFERSIZE byte buffer, grab the samples
	if (iSamplesAvailable >= QPO_CAPTURE_RATE)
		{
		// Consume Samples
		alcCaptureSamples(pCaptureDevice, pCBuffer, QPO_CAPTURE_RATE);

#if 0
		// Write the audio data to a file
		fwrite(Buffer, BUFFERSIZE, 1, pFile);
#endif

		// Stop capture
		alcCaptureStop(pCaptureDevice);

		return false;
		}

	return true;
}

float *Q_PORTShell::Sound_Capture_Get(void)
{
	/// Convert sample to float ///
	float *i_FloatSample = new float[QPO_CAPTURE_RATE];

	for(int i_Andy = 0; i_Andy < QPO_CAPTURE_RATE; i_Andy++)
		{
		i_FloatSample[i_Andy] = pCBuffer[i_Andy];
		}

	return i_FloatSample;
}

QpoSoundDef Q_PORTShell::Sound_Load(const char * Name, const char * File)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	return Mix_LoadWAV( File );
#endif
	return 0;
	}

void Q_PORTShell::Sound_Process(void)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)

#endif
	}

int Q_PORTShell::Sound_FindSource(void)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	for(int i_Iter = 0; i_Iter < 32; i_Iter++)
		{
		if(_->SoundQueue[i_Iter] == 0) return i_Iter;
		}
	return -1;
#endif
	}

QpoSound Q_PORTShell::Sound_Play(QpoSoundDef SoundDef, float Volume, float Pan, float Pitch, bool Loop, QpoVec3d * Position)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	QpoVec3d f_Aerials = playerAV->Xform.Translation;
	QpoVec3d f_VecTo;
	float f_LengthVecTo;
	int f_LengthFINT1, f_LengthFINTMIX;
	Uint8 f_LengthInt, f_LengthMix;

	f_Aerials.y += (75 + (30*(((player->BFO.CharDATA[player->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));

	Qpo->Vec3d_Subtract(Position, &f_Aerials, &f_VecTo);
	f_LengthVecTo = Qpo->Vec3d_Length(&f_VecTo);

	//f_LengthFINT1 = f_LengthVecTo;
	f_LengthFINTMIX = f_LengthVecTo;

	//if(f_LengthFINT1 > 254) f_LengthFINT1 = 254;
	//if(f_LengthFINT1 < 0) f_LengthFINT1 = 0;

	//f_LengthInt = f_LengthFINT1;

	//if(Mix_SetPosition(m_ChannelPNT, player->Angles.y, f_LengthInt) == -1)
	//	{
	//	std::cerr << "ERROR::: Mix_PlayChannel ::: Failed to Play Sample" << std::endl;
	//	while(1) { /* Infinite Loop */ }// return -1;
	//	}

	if(Mix_PlayChannel(m_ChannelPNT, SoundDef, 0) == -1)
		{
		std::cerr << "ERROR::: Mix_PlayChannel ::: Failed to Play Sample" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	f_LengthFINTMIX = 128 - (f_LengthFINTMIX / 13);

	if(f_LengthFINTMIX >= 127) f_LengthFINTMIX = 127;
	if(f_LengthFINTMIX <= 0) f_LengthFINTMIX = 0;

	Mix_Volume(m_ChannelPNT, f_LengthFINTMIX);

	m_ChannelPNT++;
	if(m_ChannelPNT >= 8) m_ChannelPNT = 0;
#endif
	return m_ChannelPNT;
	}

QpoSound Q_PORTShell::Sound_Play_Effect(QpoSoundDef SoundDef, float Volume, float Pan, float Pitch, bool Loop, QpoVec3d * Position, bool i_RefreshEFX)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	 if(Mix_PlayChannel(-1, SoundDef, 0) == -1)
		{
		std::cerr << "ERROR::: Mix_PlayChannel ::: Failed to Play Sample" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}
#endif
	return 0;
	}

bool Q_PORTShell::Sound_SetEffect(unsigned int i_Source, bool i_Refresh)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
#if 0
	if(uiEffectOn)
		{
		if(i_Refresh) Sound_ClearEffect();
		else return true;
		}
#endif

	if(ALFWIsEFXSupported())
		{
		if (ALFWCreateAuxEffectSlot(&uiEffectSlot))
			{
			if (!ALFWCreateEffect(&uiEffect, AL_EFFECT_EAXREVERB))
				{
				//ALFWprintf("Failed to Create an EAX Reverb Effect\n");
				return false;
				}
			}
		else
			{
			//ALFWprintf("Failed to generate an Auxilary Effect Slot\n");
			return false;
			}

		// Reverb Preset is stored in legacy format, use helper function to convert to EFX EAX Reverb
		ConvertReverbParameters(&eaxHangar, &efxReverb);
			
		// Set the Effect parameters
		if (!SetEFXEAXReverbProperties(&efxReverb, uiEffect))
			ALFWprintf("Failed to set Reverb Parameters\n");

		// Load Effect into Auxiliary Effect Slot
		alAuxiliaryEffectSloti(uiEffectSlot, AL_EFFECTSLOT_EFFECT, uiEffect);

		// Enable (non-filtered) Send from Source to Auxiliary Effect Slot
		alSource3i(i_Source, AL_AUXILIARY_SEND_FILTER, uiEffectSlot, 0, AL_FILTER_NULL);

		uiEffectOn = true;

		return true;

#if 0
		ALFWprintf("Playing Source with Send to 'Bathroom' Reverb Effect\n");

		// To change one (or more) of the Reverb parameters, update the Effect Object
		// and re-attach to the Auxiliary Effect Slot ...

		// Reverb Preset is stored in legacy format, use helper function to convert to EFX EAX Reverb
		ConvertReverbParameters(&eaxBathroom, &efxReverb);

		// Set the Effect parameters
		if (!SetEFXEAXReverbProperties(&efxReverb, uiEffect))
			ALFWprintf("Failed to set Reverb Parameters\n");

		// Load Effect into Auxiliary Effect Slot
		alAuxiliaryEffectSloti(uiEffectSlot, AL_EFFECTSLOT_EFFECT, uiEffect);

		// Play Source again
		PlaySource(uiSource);

		// Clean-up ...

		// Remove Effect Send from Source
		alSource3i(uiSource, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, AL_FILTER_NULL);

		// Load NULL Effect into Effect Slot
		alAuxiliaryEffectSloti(uiEffectSlot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
		
		// Delete Effect
		alDeleteEffects(1, &uiEffect);
		
		// Delete Auxiliary Effect Slot
		alDeleteAuxiliaryEffectSlots(1, &uiEffectSlot);
#endif
		}
#endif
	}

void Q_PORTShell::Sound_ClearEffect(void)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	alAuxiliaryEffectSloti(uiEffectSlot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
	alDeleteEffects(1, &uiEffect);
	alDeleteAuxiliaryEffectSlots(1, &uiEffectSlot);
	uiEffectOn = false;
#endif
	}

void Q_PORTShell::Sound_Stop(QpoSound Sound)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	// Assume the sounds end when they end!
#endif
	}

void Q_PORTShell::Sound_Modify(QpoSound Sound, float Volume, float Pan, float Pitch, QpoVec3d * Position, QpoVec3d * Velocity)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
#if 0
	ALuint i_Source = _->SoundSource[Sound];

	if(_->SoundQueue[Sound] == 0)
		{
		alSourcePlay(i_Source);

		alSourcef(i_Source, AL_PITCH, Pitch);

		//alSourcef(i_Source, AL_GAIN, Volume);
		alSourcef(i_Source, AL_GAIN, 1);

		alSource3f(i_Source, AL_POSITION, Position->x, Position->y, Position->z);

		alSource3f(i_Source, AL_VELOCITY, Velocity->x, Velocity->y, Velocity->z);
		}
	else
		{
		alSourcef(i_Source, AL_PITCH, Pitch);

		//alSourcef(i_Source, AL_GAIN, Volume);
		alSourcef(i_Source, AL_GAIN, 1);

		alSource3f(i_Source, AL_POSITION, Position->x, Position->y, Position->z);

		alSource3f(i_Source, AL_VELOCITY, Velocity->x, Velocity->y, Velocity->z);
		}
#endif
#endif
	}

void Q_PORTShell::Sound_Close(QpoSoundDef SoundDef)
	{
	//alDeleteBuffers(1, &SoundDef);
	}

void Q_PORTShell::Sound_Shutdown(void)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	//Quit SDL_mixer
    Mix_CloseAudio();
#endif
	}

unsigned int Q_PORTShell::Tex_LoadTexture(unsigned short Flags, const char * File)
	{
#pragma message("Server engine excludes")
#if defined(WIN32)
	switch(Flags)
		{
		case 0:			// LOAD - TGA image
			{
			return unTgaLoad( File,  TGA_DEFAULT );
			}break;
		case 1:			// LOAD - PNG image
			{
			//return unTgaLoad( File,  TGA_DEFAULT );
			}break;
		}
#endif
	}

unsigned int Q_PORTShell::Tex_LoadAlphaTexture(const char * File, const char * Name, int color_key)
	{
	return 1;
	}

void Q_PORTShell::Tex_Blit(unsigned int i_texture, QpoRect *Brushrect, int x, int y)
	{
	m_CC.setExecMode(CCX_MODE_BLIT);

	///// Texture Print /////
	glBindTexture( GL_TEXTURE_2D, i_texture );

	glBegin( GL_QUADS );
	glTexCoord2i(1, 0);
	glVertex2d(x, g_render->sizey - y);
	glTexCoord2i(0, 0);
	glVertex2d(x + Brushrect->xmax, g_render->sizey - y);
	glTexCoord2i(0, 1);
	glVertex2d(x + Brushrect->xmax, (g_render->sizey - y) + Brushrect->ymax);
	glTexCoord2i(1, 1);
	glVertex2d(x, (g_render->sizey - y) + Brushrect->ymax);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	}

#pragma message("Server engine excludes")
#if defined(WIN32)
void Q_PORTShell::Tex_BlitAlpha(unsigned int lpBitmap, int nX, int nY, DWORD dwWidth, DWORD dwHeight, float fAlpha, float fU, float fV, int RED, int GREEN, int BLUE )
	{
	m_CC.setExecMode(CCX_MODE_BLIT);

	///// Texture Print /////
	glBindTexture( GL_TEXTURE_2D, lpBitmap );

	glBegin( GL_QUADS );
	glTexCoord2i(1, 0);
	glVertex2d(nX, nY);
	glTexCoord2i(0, 0);
	glVertex2d(nX + dwWidth, nY);
	glTexCoord2i(0, 1);
	glVertex2d(nX + dwWidth, nY + dwHeight);
	glTexCoord2i(1, 1);
	glVertex2d(nX, nY + dwHeight);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	}
#endif

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

bool Q_PORTShell::Collision_RayTest(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Front, QpoVec3d *Rear, int UserFlags, bool Collision, bool *Context, QpoCollision *Col)
	{
#if 0
	pVector front(Front->x, Front->y, Front->z);
	pVector back(Rear->x, Rear->y, Rear->z);

	float distance;
	pVector i_impact;
	int ret = _->mesh->ray_intersect(front, back, i_impact, distance);

	Col->Impact.x = i_impact.x;
	Col->Impact.y = i_impact.y;
	Col->Impact.z = i_impact.z;
	//Col->Avatar = 0;

	Col->Plane.Dist = 0;
	Col->Plane.Normal.x = 0;
	Col->Plane.Normal.y = 1;
	Col->Plane.Normal.z = 0;

	QpoVec3d i_ray, i_dest;

	Vec3d_Subtract(Rear, Front, &i_ray);
	Vec3d_Subtract(&Col->Impact, Front, &i_dest);

#pragma message("FIXME optimise ray picker for try concave selection")

	if((Vec3d_Length(&i_dest) <= Vec3d_Length(&i_ray)) && (ret != 0)) return true;
	else return false;
#endif

#if 1
	float distance;
	PxVec3 i_impact;
	bool i_result = QActiveFrameWork->DigiMass->acRayCollider(Col, PxVec3(Front->x,Front->y,Front->z), PxVec3(Rear->x,Rear->y,Rear->z), i_impact, distance);
#else
	bool i_result;
	float distance;
	pVector i_impact;
	pFace* i_Face = _->mesh->octree.ray_intersect(pVector(Front->x, Front->y, Front->z), pVector(Rear->x,Rear->y,Rear->z), i_impact, distance);
	//pFace* i_Face = _->mesh->octree.ray_intersect(pVector(Rear->x,Rear->y,Rear->z), pVector(Front->x, Front->y, Front->z), i_impact, distance);
	if(i_Face == 0) i_result = false;
	else i_result = true;
#endif

	if(i_result == true)
		{
		Col->Impact.x = i_impact.x;
		Col->Impact.y = i_impact.y;
		Col->Impact.z = i_impact.z;
		//Col->Avatar = 0;

		Col->Plane.Dist = 0;
		Col->Plane.Normal.x = 0;
		Col->Plane.Normal.y = 1;
		Col->Plane.Normal.z = 0;
		}

#pragma message("FIXME optimise ray picker for try concave selection")

#if 1
	if(i_result)
		{
		QpoVec3d i_ray, i_dest;

		Vec3d_Subtract(Rear, Front, &i_ray);
		Vec3d_Subtract(&Col->Impact, Front, &i_dest);

		if((Vec3d_Length(&i_dest) <= Vec3d_Length(&i_ray))) return true;
		else return false;
		}

	return false;
#else
	return i_result;
#endif
	}

bool Q_PORTShell::Collision_RayTest_Avatar(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Front, QpoVec3d *Rear, int UserFlags, bool Collision, bool *Context, QpoCollision *Col, int f_AvID, bool f_Impact)
	{
	float distance;
	PxVec3 i_impact;
	bool i_result = false;
	if(f_Impact && 0) i_result = QActiveFrameWork->DigiMass->acRayColliderImpact(Col, PxVec3(Front->x,Front->y,Front->z), PxVec3(Rear->x,Rear->y,Rear->z), i_impact, distance);
	else i_result = QActiveFrameWork->DigiMass->acRayCollider(Col, PxVec3(Front->x,Front->y,Front->z), PxVec3(Rear->x,Rear->y,Rear->z), i_impact, distance);

	Col->m_HitAvatar = false;

	QpoVec3d f_Impactal(i_impact.x, i_impact.y, i_impact.z);

	//###- Hit Player Collisions
	if(i_result)
		{
		if(f_AvID != -1)
			{
			QpoVec3d f_Player(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
			QpoVec3d f_Triangle;

			if(player->WeaponStatus == 0) player->CamMatrix.Translation.y = playerAV->Xform.Translation.y + 20 + 25;
			else player->CamMatrix.Translation.y = playerAV->Xform.Translation.y + 20 + 25 + 30;

			player->CamMatrix.Translation.y *= player->BFO.CharDATA[player->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player->BFO.CharDATA[player->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));

			Qpo->Vec3d_Subtract(&f_Impactal, &player->CamMatrix.Translation, &f_Triangle);
			if(Qpo->Vec3d_Length(&f_Triangle) < 400)
				{
				Col->Avatar = playerAV->Avatar;
				Col->m_AvatarID = -1;
				Col->m_HitAvatar = true;

				Col->Impact = f_Impactal;

				Col->Plane.Dist = 0;
				Col->Plane.Normal.x = 0;
				Col->Plane.Normal.y = 1;
				Col->Plane.Normal.z = 0;
				}

			for(int SCRAMJETO = 0; SCRAMJETO < _->NomAI; ++SCRAMJETO)
				{
				QpoVec3d f_Impacta(i_impact.x, i_impact.y, i_impact.z);
				QpoVec3d f_Player(Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.x, Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.y, Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.z);
				QpoVec3d f_Triangle;

				if(player->WeaponStatus == 0) player->CamMatrix.Translation.y = Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.y + 20 + 25;
				else player->CamMatrix.Translation.y = Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.y + 20 + 25 + 30;

				player->CamMatrix.Translation.y *= Q_Forge->Forge[SCRAMJETO].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[SCRAMJETO].CharDATA.BodySKILL.Height/100)-0.5)*2));

				Qpo->Vec3d_Subtract(&f_Impacta, &player->CamMatrix.Translation, &f_Triangle);
				if(Qpo->Vec3d_Length(&f_Triangle) < 400)
					{
					Col->Avatar = Q_Forge->Forge[SCRAMJETO].AV.Avatar;
					Col->m_AvatarID = SCRAMJETO;
					Col->m_HitAvatar = true;

					Col->Impact = f_Impactal;

					Col->Plane.Dist = 0;
					Col->Plane.Normal.x = 0;
					Col->Plane.Normal.y = 1;
					Col->Plane.Normal.z = 0;
					}
				}
			}
		else
			{
			for(int SCRAMJETO = 0; SCRAMJETO < _->NomAI; ++SCRAMJETO)
				{
				QpoVec3d f_Impacta(i_impact.x, i_impact.y, i_impact.z);
				QpoVec3d f_Player(Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.x, Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.y, Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.z);
				QpoVec3d f_Triangle;

				if(player->WeaponStatus == 0) player->CamMatrix.Translation.y = Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.y + 20 + 25;
				else player->CamMatrix.Translation.y = Q_Forge->Forge[SCRAMJETO].AV.Xform.Translation.y + 20 + 25 + 30;

				player->CamMatrix.Translation.y *= Q_Forge->Forge[SCRAMJETO].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[SCRAMJETO].CharDATA.BodySKILL.Height/100)-0.5)*2));

				Qpo->Vec3d_Subtract(&f_Impacta, &player->CamMatrix.Translation, &f_Triangle);
				if(Qpo->Vec3d_Length(&f_Triangle) < 400)
					{
					Col->Avatar = Q_Forge->Forge[SCRAMJETO].AV.Avatar;
					Col->m_AvatarID = SCRAMJETO;
					Col->m_HitAvatar = true;

					Col->Impact = f_Impactal;

					Col->Plane.Dist = 0;
					Col->Plane.Normal.x = 0;
					Col->Plane.Normal.y = 1;
					Col->Plane.Normal.z = 0;
					}
				}
			}
		}

	if(i_result == true)
		{
		QpoVec3d i_ray, i_dest;

		Vec3d_Subtract(Rear, Front, &i_ray);
		Vec3d_Subtract(&Col->Impact, Front, &i_dest);

		if((Vec3d_Length(&i_dest) <= Vec3d_Length(&i_ray)))
			{
			Col->Impact = f_Impactal;

			Col->Plane.Dist = 0;
			Col->Plane.Normal.x = 0;
			Col->Plane.Normal.y = 1;
			Col->Plane.Normal.z = 0;

			return true;
			}
		else return false;
		}

	return false;
	}

bool Q_PORTShell::Collision_RayTest_Projectile(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Front, QpoVec3d *Rear, int UserFlags, bool Collision, bool *Context, QpoCollision *Col)
	{
#if defined(ENABLE_PX_PHYSICS)
#if 1
#if 1
	float distance;
	PxVec3 i_impact;
	bool i_result = QActiveFrameWork->DigiMass->acRayCollider(Col, PxVec3(Front->x,Front->y,Front->z), PxVec3(Rear->x,Rear->y,Rear->z), i_impact, distance);
#else
	bool i_result;
	float distance;
	pVector i_impact;
	pFace* i_Face = _->mesh->octree.ray_intersect(pVector(Front->x, Front->y, Front->z), pVector(Rear->x,Rear->y,Rear->z), i_impact, distance);
	if(i_Face == 0) i_result = false;
	else i_result = true;
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
	if(!(((playerAV->Xform.Translation.x + playerAV->Mins.x) > (Front->x + 25)) || ((playerAV->Xform.Translation.x + playerAV->Maxs.x) < (Front->x - 25))) &&
	!(((playerAV->Xform.Translation.y + playerAV->Mins.y) > (Front->y + 25)) || ((playerAV->Xform.Translation.y + playerAV->Maxs.y) < (Front->y - 25))) &&
	!(((playerAV->Xform.Translation.z + playerAV->Mins.z) > (Front->z + 25)) || ((playerAV->Xform.Translation.z + playerAV->Maxs.z) < (Front->z - 25))))
		{
		//Col->Avatar = playerAV->Avatar;
		Col->m_AvatarID = -1;
		Col->m_HitAvatar = true;
		return true;
		}*/

	Col->m_AvatarID = 0;
	Col->m_HitAvatar = false;

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
#endif

	//Col->Plane.Normal.x = 0;
	//Col->Plane.Normal.y = 1;
	//Col->Plane.Normal.z = 0;

	if(i_result)
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
	int FactorFinger;
	if(Avatar.Mesh->m_BoneStructure == -1) FactorFinger = 0;
	else
		{
		if(g_render->curfps < 60 && g_render->curfps > 45) FactorFinger = 0;
		if(g_render->curfps < 45 && g_render->curfps > 30) FactorFinger = rand() % 3;
		if(g_render->curfps < 30 && g_render->curfps > 15) FactorFinger = rand() % 4;
		if(g_render->curfps < 15)						   FactorFinger = rand() % 5;

		if(Q_Forge->Forge[Avatar.IDflag].HB_Dead == 1) FactorFinger = 2;
		}

	FactorFinger = 0;

	if(FactorFinger == 0 || FactorFinger == 1)
		{
		if(Avatar.Mesh->m_BoneStructure == 0)
			{
			if(KEY_DOWN(QIN_n))
				{
				if(!keyvecvar[0])
					{
					keyvecvar[0] = 1;

					if(storelockvar[0] == 0) storelockvar[0] = 1;
					else storelockvar[0] = 0;
					}
				}
			else keyvecvar[0] = 0;

			if(KEY_DOWN(QIN_m))
				{
				if(!keyvecvar[1])
					{
					keyvecvar[1] = 1;

					if(storelockvar[1] == 0) storelockvar[1] = 1;
					else storelockvar[1] = 0;
					}
				}
			else keyvecvar[1] = 0;

			if(KEY_DOWN(QIN_b))
				{
				if(!keyvecvar[2])
					{
					keyvecvar[2] = 1;

					if(storelockvar[2] == 0) storelockvar[2] = 1;
					else storelockvar[2] = 0;
					}
				}
			else keyvecvar[2] = 0;

			if(storelockvar[2])
				{
				Avatar.Mesh->acSetPose();
				}
			else
				{
				if(storelockvar[0])
					{
					Avatar.Mesh->BlendAnimPhysicsSurgery(Motion, Time, BlendAmount);
					//Avatar.Mesh->BlendAnimPhysics(Motion, Time, BlendAmount);
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

			/*if(Avatar.Mesh->m_digiBodyMesh)
				{
				Avatar.Mesh->m_digiBodyMesh->acUpdate(0);

				//Avatar.Mesh->m_digiBodyMesh->acCollide(m_trrCell->vec_Model[1]);
				//printf("collision results size() %i\n", m_trrCell->vec_Model[0]->_tree->m_rets.size());

				Camera_Set();

				Avatar.Mesh->m_digiBodyMesh->acRenderBody(0, 1);
				}*/
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
					if(Avatar.IDflag == 250) Avatar.Mesh->BlendAnim(Motion, Time, BlendAmount);
					else Avatar.Mesh->BlendAnimTorque(Motion, Time, BlendAmount);
#endif
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
		playerAV->Avatar.Mesh->m_calModel->getMixer()->ClearAnim();
		Avatar.Mesh->ClearAnimPhysics();
#endif
		}
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
	CalBone *i_bone;
	int boneID = Q.MapSkeletonA(String);

if(i_AV->Avatar.Mesh)
	{
	std::vector<CalBone *>& vec_Bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getVectorBone();

	//if(boneID < vec_Bone.size());
	i_bone = vec_Bone[boneID];

	//CalBone *i_bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = i_bone->getRotationAbsolute();
	CalVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	CalMatrix rotationMatrix = boneort;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
	Bone->Matrix.m[0][0]=rotationMatrix.dxdx;Bone->Matrix.m[0][1]=rotationMatrix.dxdy;Bone->Matrix.m[0][2]=rotationMatrix.dxdz;
	Bone->Matrix.m[1][0]=rotationMatrix.dydx;Bone->Matrix.m[1][1]=rotationMatrix.dydy;Bone->Matrix.m[1][2]=rotationMatrix.dydz;
	Bone->Matrix.m[2][0]=rotationMatrix.dzdx;Bone->Matrix.m[2][1]=rotationMatrix.dzdy;Bone->Matrix.m[2][2]=rotationMatrix.dzdz;

	Bone->Matrix = i_AV->Xform.Matrix * Bone->Matrix;

	Qpo->Transform_RotateVector(&i_AV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = bonevector.x + i_AV->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + i_AV->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + i_AV->Xform.Translation.z;
	}
	}

void Q_PORTShell::Avatar_GetBoneTransformMP(QpoAvatarFlags f_AV, const char * String, QpoTransform * Bone)
	{
	CalBone *f_bone = f_AV.Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = f_bone->getRotationAbsolute();
	CalVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	CalMatrix rotationMatrix = boneort;

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

	Bone->Translation.x = m_CC.pResult.x + f_AV.Xform.Translation.x;
	Bone->Translation.y = m_CC.pResult.y + f_AV.Xform.Translation.y;
	Bone->Translation.z = m_CC.pResult.z + f_AV.Xform.Translation.z;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
	}

void Q_PORTShell::Avatar_GetTransformAvatar(QpoAvatarFlags * f_AV, const char * String, QpoTransform * Bone, int AIcounters)
	{
	CalBone *f_bone = f_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = f_bone->getRotationAbsolute();
	CalVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	CalMatrix rotationMatrix = boneort;

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&f_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

	glRotatef(radToDeg(-Q_Forge->Forge[AIcounters].Angles.y + PI), 0.0f, 0.0f, 1.0f);

	glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	Qpo->Transform_RotateVector(&f_AV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = bonevector.x + f_AV->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + f_AV->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + f_AV->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_GetWeaponTransform_s(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	CalBone *i_bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = i_bone->getRotationAbsolute();
	CalVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	CalQuaternion i_quat(1,0,1,0);

	CalMatrix rotationMatrix = boneort;

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glMultMatrixf((float*)g_glviewAvatar.Matrix.mf);

#if 0
	glTranslatef(-g_eyePosition.x, -g_eyePosition.y, -g_eyePosition.z);
#endif

	glMultMatrixf((float *)&f_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

#if 1
	if(player->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
		glMultMatrixf(playerAV->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
		glMultMatrixf(playerAV->Xform.Matrix.mf);
		}
#endif

#if 0
	glRotatef(radToDeg(-player->AvatarRotation + PI), 0.0f, 0.0f, 1.0f);
#endif

	glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);

	Qpo->Transform_RotateVector(&playerAV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = bonevector.x + playerAV->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + playerAV->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + playerAV->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_GetWeaponTransform_old(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	CalBone *i_bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = i_bone->getRotationAbsolute();
	CalVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	CalQuaternion i_quat(1,0,1,0);

	CalMatrix rotationMatrix = boneort;

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&i_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

	glRotatef(radToDeg(-player->AvatarRotation + PI), 0.0f, 0.0f, 1.0f);

	glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);

	Qpo->Transform_RotateVector(&i_AV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = /*bonevector.x + */playerAV->Xform.Translation.x;
	Bone->Translation.y = /*bonevector.y + */playerAV->Xform.Translation.y;
	Bone->Translation.z = /*bonevector.z + */playerAV->Xform.Translation.z;
	}

void Q_PORTShell::Avatar_GetWeaponTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	CalBone *i_bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = i_bone->getRotationAbsolute();
	CalVector bonetrans = i_bone->getTranslationAbsolute();

	QpoVec3d bonevector;
	bonevector.x = bonetrans.x;
	bonevector.y = bonetrans.y;
	bonevector.z = bonetrans.z;

	CalQuaternion i_quat(1,0,1,0);

	CalMatrix rotationMatrix = boneort;

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf((float *)&i_Matrix);
	glMultMatrixf((float *)&Bone->Matrix);

	glRotatef(radToDeg(-player->AvatarRotation + PI), 0.0f, 0.0f, 1.0f);

	glGetFloatv(GL_MODELVIEW_MATRIX, Bone->Matrix.mf);

	Qpo->Transform_RotateVector(&i_AV->Xform, &bonevector, &bonevector);

	Bone->Translation.x = bonevector.x + i_AV->Xform.Translation.x;
	Bone->Translation.y = bonevector.y + i_AV->Xform.Translation.y;
	Bone->Translation.z = bonevector.z + i_AV->Xform.Translation.z;
	}

void Q_PORTShell::AvatarView_GetBoneTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	CalBone *f_bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = f_bone->getRotationAbsolute();
	CalVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	CalMatrix rotationMatrix = boneort;
	//pMatrix f_matrix;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
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

void Q_PORTShell::AvatarView_GetBoneTransform_PntSprite(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone)
	{
	CalBone *f_bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = f_bone->getRotationAbsolute();
	CalVector bonetrans = f_bone->getTranslationAbsolute();

	Bone->Matrix.load_identity();
	Bone->Translation.x = 0;
	Bone->Translation.y = 0;
	Bone->Translation.z = 0;

	CalMatrix rotationMatrix = boneort;
	//pMatrix f_matrix;

#pragma message("FIXME:::Rotate Matrix and transform by player matrix")
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
	CalBone *i_bone = i_AV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = i_bone->getRotationAbsolute();
	CalVector bonetrans = i_bone->getTranslationAbsolute();

	CalMatrix rotationMatrix = boneort;

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
	CalBone *i_bone = Q_Forge->Forge[i_AvatarIndex].AV.Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(String));
	CalQuaternion boneort = i_bone->getRotationAbsolute();
	CalVector bonetrans = i_bone->getTranslationAbsolute();

	CalMatrix rotationMatrix = boneort;

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
	Bone->Matrix = Bone->Matrix * Q_Forge->Forge[i_AvatarIndex].AV.Viewform;

#if 0
	Bone->Matrix = Bone->Matrix * Q_Forge->Forge[i_AvatarIndex].AV.Weaponform;
#endif

	m_CC.pVector1.x = bonetrans.x;
	m_CC.pVector1.y = bonetrans.y;
	m_CC.pVector1.z = bonetrans.z;

	m_CC.pResult = m_CC.pVector1 * Q_Forge->Forge[i_AvatarIndex].AV.Viewform;

#if 0
	m_CC.pResult = m_CC.pVector1 * Q_Forge->Forge[i_AvatarIndex].AV.Weaponform;
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

/*void Q_PORTShell::Avatar_GetExtBox(QpoAvatar i_AvatarFlags, QpoAvExtBox * i_BoneBox)
	{
	i_BoneBox.Mins = i_AvatarFlags.Mins;
	i_BoneBox.Maxs = i_AvatarFlags.Maxs;
	}*/

QpoMotion Q_PORTShell::Avatar_GetMotionByName(QpoAvatar_Def * Avatar_Def, const char *Name )
	{
	QpoMotion motionhandle = 0;

	return motionhandle;
	}

//static bool operator != (const QpoAvatar& a1, const QpoAvatar& a2)
/*static inline bool QpoAvatar operator-(const QpoAvatar &v)
	{
	/*if (m1[0][0] != m2[0][0] || m1[0][1] != m2[0][1] || m1[0][2] != m2[0][2]) return true;
	if (m1[1][0] != m2[1][0] || m1[1][1] != m2[1][1] || m1[1][2] != m2[1][2]) return true;
	if (m1[2][0] != m2[2][0] || m1[2][1] != m2[2][1] || m1[2][2] != m2[2][2]) return true;

	csRef<iMeshWrapper>				spritewrapper;
	csRef<iSprite3DFactoryState>	sprite;
	csRef<iSpriteCal3DFactoryState>	cal3dsprite;
	csRef<iSprite3DState>			state;
	csRef<iSpriteCal3DState>		cal3dstate;
	iSpriteSocket*					selectedSocket;
	iSpriteCal3DSocket*				selectedCal3dSocket;
	CalModel						*Cal3dModel;
	int								Avatar;
	QpoPose							Pose;
	int								IDflag;
	int								Visible;

	return false;
	}*/

/*bool operator!= (const QpoAvatar& a1, const QpoAvatar& a2)
	{
	/*if (m1[0][0] != m2[0][0] || m1[0][1] != m2[0][1] || m1[0][2] != m2[0][2]) return true;
	if (m1[1][0] != m2[1][0] || m1[1][1] != m2[1][1] || m1[1][2] != m2[1][2]) return true;
	if (m1[2][0] != m2[2][0] || m1[2][1] != m2[2][1] || m1[2][2] != m2[2][2]) return true;*//*

	if(a1.spritewrapper == a2.spritewrapper &&
	a1.sprite == a2.sprite &&
	a1.cal3dsprite == a2.cal3dsprite &&
	a1.state == a2.state &&
	a1.cal3dstate == a2.cal3dstate &&
	a1.selectedSocket == a2.selectedSocket &&
	a1.selectedCal3dSocket == a2.selectedCal3dSocket &&
	//a1.*Cal3dModel == a2.*Cal3dModel &&
	a1.Avatar == a2.Avatar &&
	a1.Pose == a2.Pose &&
	a1.IDflag == a2.IDflag &&
	a1.Visible == a2.Visible) return true;
	else return false;*/
	//}

void Q_PORTShell::Player_SetMatrix(void)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);
#endif
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
	CalBone *i_bone = playerAV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(BoneName));
	i_bone->calculateBoundingBox();
	CalBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	CalVector i_Points[8];
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
	CalBone *i_bone = Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(BoneName));
	i_bone->calculateBoundingBox();
	CalBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	CalVector i_Points[8];
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
	CalBone *i_bone = playerAV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(BoneName));
	i_bone->calculateBoundingBox();
	CalBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	CalVector i_Points[8];
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
	CalBone *i_bone = Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(BoneName));
	i_bone->calculateBoundingBox();
	CalBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	CalVector i_Points[8];
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
#pragma message("Server Engine excludes")
#if defined(WIN32)
	CalBone *i_bone = playerAV->Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(BoneName));
	i_bone->calculateBoundingBox();
	CalBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	CalVector i_Points[8];
	i_BoneBox.computePoints(i_Points);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);

		glVertex3f(i_Points[0].x,i_Points[0].y,i_Points[0].z);
		glVertex3f(i_Points[1].x,i_Points[1].y,i_Points[1].z);

		glVertex3f(i_Points[0].x,i_Points[0].y,i_Points[0].z);
		glVertex3f(i_Points[2].x,i_Points[2].y,i_Points[2].z);

		glVertex3f(i_Points[1].x,i_Points[1].y,i_Points[1].z);
		glVertex3f(i_Points[3].x,i_Points[3].y,i_Points[3].z);

		glVertex3f(i_Points[2].x,i_Points[2].y,i_Points[2].z);
		glVertex3f(i_Points[3].x,i_Points[3].y,i_Points[3].z);

		glVertex3f(i_Points[4].x,i_Points[4].y,i_Points[4].z);
		glVertex3f(i_Points[5].x,i_Points[5].y,i_Points[5].z);

		glVertex3f(i_Points[4].x,i_Points[4].y,i_Points[4].z);
		glVertex3f(i_Points[6].x,i_Points[6].y,i_Points[6].z);

		glVertex3f(i_Points[5].x,i_Points[5].y,i_Points[5].z);
		glVertex3f(i_Points[7].x,i_Points[7].y,i_Points[7].z);

		glVertex3f(i_Points[6].x,i_Points[6].y,i_Points[6].z);
		glVertex3f(i_Points[7].x,i_Points[7].y,i_Points[7].z);

		glVertex3f(i_Points[0].x,i_Points[0].y,i_Points[0].z);
		glVertex3f(i_Points[4].x,i_Points[4].y,i_Points[4].z);

		glVertex3f(i_Points[1].x,i_Points[1].y,i_Points[1].z);
		glVertex3f(i_Points[5].x,i_Points[5].y,i_Points[5].z);

		glVertex3f(i_Points[2].x,i_Points[2].y,i_Points[2].z);
		glVertex3f(i_Points[6].x,i_Points[6].y,i_Points[6].z);

		glVertex3f(i_Points[3].x,i_Points[3].y,i_Points[3].z);
		glVertex3f(i_Points[7].x,i_Points[7].y,i_Points[7].z);

	glEnd();
#endif
	}

void Q_PORTShell::Avatar_RenderBoneBoundingBox(unsigned int i_AVIndex, const char *BoneName)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	CalBone *i_bone = Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_calModel->getSkeleton()->getBone(Q.MapSkeletonA(BoneName));
	i_bone->calculateBoundingBox();
	CalBoundingBox & i_BoneBox = i_bone->getBoundingBox();

	CalVector i_Points[8];
	i_BoneBox.computePoints(i_Points);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x, Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y, Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z);
	glMultMatrixf(Q_Forge->Forge[i_AVIndex].AV.Xform.Matrix.mf);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);

		glVertex3f(i_Points[0].x,i_Points[0].y,i_Points[0].z);
		glVertex3f(i_Points[1].x,i_Points[1].y,i_Points[1].z);

		glVertex3f(i_Points[0].x,i_Points[0].y,i_Points[0].z);
		glVertex3f(i_Points[2].x,i_Points[2].y,i_Points[2].z);

		glVertex3f(i_Points[1].x,i_Points[1].y,i_Points[1].z);
		glVertex3f(i_Points[3].x,i_Points[3].y,i_Points[3].z);

		glVertex3f(i_Points[2].x,i_Points[2].y,i_Points[2].z);
		glVertex3f(i_Points[3].x,i_Points[3].y,i_Points[3].z);

		glVertex3f(i_Points[4].x,i_Points[4].y,i_Points[4].z);
		glVertex3f(i_Points[5].x,i_Points[5].y,i_Points[5].z);

		glVertex3f(i_Points[4].x,i_Points[4].y,i_Points[4].z);
		glVertex3f(i_Points[6].x,i_Points[6].y,i_Points[6].z);

		glVertex3f(i_Points[5].x,i_Points[5].y,i_Points[5].z);
		glVertex3f(i_Points[7].x,i_Points[7].y,i_Points[7].z);

		glVertex3f(i_Points[6].x,i_Points[6].y,i_Points[6].z);
		glVertex3f(i_Points[7].x,i_Points[7].y,i_Points[7].z);

		glVertex3f(i_Points[0].x,i_Points[0].y,i_Points[0].z);
		glVertex3f(i_Points[4].x,i_Points[4].y,i_Points[4].z);

		glVertex3f(i_Points[1].x,i_Points[1].y,i_Points[1].z);
		glVertex3f(i_Points[5].x,i_Points[5].y,i_Points[5].z);

		glVertex3f(i_Points[2].x,i_Points[2].y,i_Points[2].z);
		glVertex3f(i_Points[6].x,i_Points[6].y,i_Points[6].z);

		glVertex3f(i_Points[3].x,i_Points[3].y,i_Points[3].z);
		glVertex3f(i_Points[7].x,i_Points[7].y,i_Points[7].z);

	glEnd();
#endif
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

	glColor3f(0.25f, 1.0f, 0.25f);
	glBegin(GL_LINES);

		glVertex3f(i_point[0].x, i_point[0].y, i_point[0].z);
		glVertex3f(i_point[1].x, i_point[1].y, i_point[1].z);

		glVertex3f(i_point[1].x, i_point[1].y, i_point[1].z);
		glVertex3f(i_point[3].x, i_point[3].y, i_point[3].z);

		glVertex3f(i_point[3].x, i_point[3].y, i_point[3].z);
		glVertex3f(i_point[2].x, i_point[2].y, i_point[2].z);

		glVertex3f(i_point[2].x, i_point[2].y, i_point[2].z);
		glVertex3f(i_point[0].x, i_point[0].y, i_point[0].z);

		glVertex3f(i_point[4].x, i_point[4].y, i_point[4].z);
		glVertex3f(i_point[5].x, i_point[5].y, i_point[5].z);

		glVertex3f(i_point[5].x, i_point[5].y, i_point[5].z);
		glVertex3f(i_point[7].x, i_point[7].y, i_point[7].z);

		glVertex3f(i_point[7].x, i_point[7].y, i_point[7].z);
		glVertex3f(i_point[6].x, i_point[6].y, i_point[6].z);

		glVertex3f(i_point[6].x, i_point[6].y, i_point[6].z);
		glVertex3f(i_point[4].x, i_point[4].y, i_point[4].z);

		glVertex3f(i_point[0].x, i_point[0].y, i_point[0].z);
		glVertex3f(i_point[4].x, i_point[4].y, i_point[4].z);

		glVertex3f(i_point[1].x, i_point[1].y, i_point[1].z);
		glVertex3f(i_point[5].x, i_point[5].y, i_point[5].z);

		glVertex3f(i_point[2].x, i_point[2].y, i_point[2].z);
		glVertex3f(i_point[6].x, i_point[6].y, i_point[6].z);

		glVertex3f(i_point[3].x, i_point[3].y, i_point[3].z);
		glVertex3f(i_point[7].x, i_point[7].y, i_point[7].z);

	glEnd();
	}

void Q_PORTShell::Player_RenderBoundingBoxes(void)
	{
	playerAV->Avatar.Mesh->m_calModel->getSkeleton()->calculateBoundingBoxes();
	playerAV->Avatar.Mesh->renderBoundingBox();
	}

void Q_PORTShell::Avatar_RenderBoundingBoxes(unsigned int i_AVIndex)
	{
	Q_Forge->Forge[i_AVIndex].AV.Avatar.Mesh->m_calModel->getSkeleton()->calculateBoundingBoxes();
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
#if 0
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	int i, colortype;
	png_bytep *row_pointers;
	png_error_ptr png_user_error, png_user_warn;

	Video *i_video = Video::instance();

	/* Opening output file */
	fp = fopen(FileName, "wb");
	if (fp == NULL) { unPrintError("fopen error"); }

	/* Initializing png structures and callbacks */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 
		NULL, png_user_error, png_user_warn);
	if (png_ptr == NULL) { unPrintError("png_create_write_struct error!\n"); }

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
		{
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		unPrintError("png_create_info_struct error!\n");
		}

	if (setjmp(png_jmpbuf(png_ptr)))
		{
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		}

	png_init_io(png_ptr, fp);

	colortype = PNG_COLOR_MASK_COLOR; /* grayscale not supported */

	if (i_video->screen->format->palette)
		colortype |= PNG_COLOR_MASK_PALETTE;
	else if (i_video->screen->format->Amask)
		colortype |= PNG_COLOR_MASK_ALPHA;

	png_set_IHDR(png_ptr, info_ptr, i_video->screen->w, i_video->screen->h, 8, colortype,	PNG_INTERLACE_NONE, 
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	/* Writing the image */
	png_write_info(png_ptr, info_ptr);
	png_set_packing(png_ptr);

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*i_video->screen->h);
	for (i = 0; i < i_video->screen->h; i++)
		row_pointers[i] = (png_bytep)(Uint8 *)i_video->screen->pixels + i*i_video->screen->pitch;
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	/* Cleaning out... */
	free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
#endif
	}

void Q_PORTShell::Camera_SetTransform(int/*camera*/camera, QpoTransform * transform, QpoVec3d Position)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	g_render->camera.mat_t.m[0][0]=transform->Matrix.m[1][0];
	g_render->camera.mat_t.m[0][1]=transform->Matrix.m[1][1];
	g_render->camera.mat_t.m[0][2]=transform->Matrix.m[1][2];
	g_render->camera.mat_t.m[1][0]=transform->Matrix.m[2][0];
	g_render->camera.mat_t.m[1][1]=transform->Matrix.m[2][1];
	g_render->camera.mat_t.m[1][2]=transform->Matrix.m[2][2];
	g_render->camera.mat_t.m[2][0]=transform->Matrix.m[0][0];
	g_render->camera.mat_t.m[2][1]=transform->Matrix.m[0][1];
	g_render->camera.mat_t.m[2][2]=transform->Matrix.m[0][2];

	//g_render->camera.mat = playerAV->Xform.Matrix;
	g_render->camera.pos.x = transform->Translation.x;
	g_render->camera.pos.y = transform->Translation.y;
	g_render->camera.pos.z = transform->Translation.z;

	g_render->camera.X.vec(g_render->camera.mat_t.m[0][0],g_render->camera.mat_t.m[1][0],g_render->camera.mat_t.m[2][0]);
	g_render->camera.Y.vec(g_render->camera.mat_t.m[0][1],g_render->camera.mat_t.m[1][1],g_render->camera.mat_t.m[2][1]);
	g_render->camera.Z.vec(g_render->camera.mat_t.m[0][2],g_render->camera.mat_t.m[1][2],g_render->camera.mat_t.m[2][2]);

	g_render->camera.update_mat();

	float fov=(g_render->camerafov>0?g_render->camerafov:g_render->camera.fov);
	g_render->view.build(g_render->camera.pos,g_render->camera.X,g_render->camera.Y,g_render->camera.Z,fov/g_render->aspect,g_render->aspect,g_render->farplane);
#endif
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
#pragma message("Set functions inline")
#pragma message("Server Engine excludes")
#if defined(WIN32)
	g_render->camera.fov = FOV;
#endif
	}

void Q_PORTShell::Camera_Set(void)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);

#if 0
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);
#endif
#endif
	}

void Q_PORTShell::Camera_SetPlayer(void)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);
#endif
	}

void Q_PORTShell::Camera_SetAvatar(unsigned int i_AVIndex)
	{
#pragma message("Server Engine excludes")
#if defined(WIN32)
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);
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

#if 0
	Box->GlobalFrameAxes[0].x = Box->Transform.Matrix.m[0][0] * Box->xScale;
	Box->GlobalFrameAxes[0].y = Box->Transform.Matrix.m[1][0] * Box->xScale;
	Box->GlobalFrameAxes[0].z = Box->Transform.Matrix.m[2][0] * Box->xScale;

	Box->GlobalFrameAxes[1].x = Box->Transform.Matrix.m[0][1] * Box->yScale;
	Box->GlobalFrameAxes[1].y = Box->Transform.Matrix.m[1][1] * Box->yScale;
	Box->GlobalFrameAxes[1].z = Box->Transform.Matrix.m[2][1] * Box->yScale;

	Box->GlobalFrameAxes[2].x = Box->Transform.Matrix.m[0][2] * Box->zScale;
	Box->GlobalFrameAxes[2].y = Box->Transform.Matrix.m[1][2] * Box->zScale;
	Box->GlobalFrameAxes[2].z = Box->Transform.Matrix.m[2][2] * Box->zScale;
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
	bool isOrthonormal;

#ifdef PORTSHELL_ASSERT_DEBUG
	isOrthonormal = Transform_IsOrthonormal(&(Box1->Transform));
	assert(isOrthonormal);
#endif

#ifdef PORTSHELL_ASSERT_DEBUG
	isOrthonormal = Transform_IsOrthonormal(&(Box2->Transform));
	assert(isOrthonormal);
#endif

	// test B against A and if necessary A against B
	for (c = 0; c < 2; c ++)
		{
		if (c == 0)
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
		for (i = 0; i < 3; i++)
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

		if ((radius + BoxA->xScale) < xformedCenterToCenterVector.x) return false;

		// test overlap in Y axis

		radius = (float)(fabs(inverseXFormedGlobalFrameAxes[0].y) +
			fabs(inverseXFormedGlobalFrameAxes[1].y) +
			fabs(inverseXFormedGlobalFrameAxes[2].y));

		if ((radius + BoxA->yScale) < xformedCenterToCenterVector.y) return false;

		// test overlap in Z axis

		radius = (float)(fabs(inverseXFormedGlobalFrameAxes[0].z) +
			fabs(inverseXFormedGlobalFrameAxes[1].z) +
			fabs(inverseXFormedGlobalFrameAxes[2].z));

		if ((radius + BoxA->zScale) < xformedCenterToCenterVector.z) return false;
		} // c

	return true; // all tests checked out, overlap occurred
	}

bool Q_PORTShell::Player_ExtBox_intersect(unsigned int i_AVIndex)
	{
	if (((playerAV->Xform.Translation.x + playerAV->Mins.x) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Maxs.x)) || ((playerAV->Xform.Translation.x + playerAV->Maxs.x) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Mins.x))) return false;
	if (((playerAV->Xform.Translation.y + playerAV->Mins.y) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Maxs.y)) || ((playerAV->Xform.Translation.y + playerAV->Maxs.y) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Mins.y))) return false;
	if (((playerAV->Xform.Translation.z + playerAV->Mins.z) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Maxs.z)) || ((playerAV->Xform.Translation.z + playerAV->Maxs.z) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Avatar_Player_ExtBox_intersect(unsigned int i_AVIndex)
	{
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Mins.x) > (playerAV->Xform.Translation.x + playerAV->Maxs.x)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Maxs.x) < (playerAV->Xform.Translation.x + playerAV->Mins.x))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Mins.y) > (playerAV->Xform.Translation.y + playerAV->Maxs.y)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Maxs.y) < (playerAV->Xform.Translation.y + playerAV->Mins.y))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Mins.z) > (playerAV->Xform.Translation.z + playerAV->Maxs.z)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Maxs.z) < (playerAV->Xform.Translation.z + playerAV->Mins.z))) return false;
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
	if (((playerAV->Xform.Translation.x + ColldetBox.Min.x) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Maxs.x)) || ((playerAV->Xform.Translation.x + ColldetBox.Max.x) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + Q_Forge->Forge[i_AVIndex].AV.Mins.x))) return false;
	if (((playerAV->Xform.Translation.y + ColldetBox.Min.y) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Maxs.y)) || ((playerAV->Xform.Translation.y + ColldetBox.Max.y) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + Q_Forge->Forge[i_AVIndex].AV.Mins.y))) return false;
	if (((playerAV->Xform.Translation.z + ColldetBox.Min.z) > (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Maxs.z)) || ((playerAV->Xform.Translation.z + ColldetBox.Max.z) < (Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + Q_Forge->Forge[i_AVIndex].AV.Mins.z))) return false;
	return true;
	}

bool Q_PORTShell::Collision_Avatar_Player_Intersect(unsigned int i_AVIndex)
	{
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + ColldetBox.Min.x) > (playerAV->Xform.Translation.x + playerAV->Maxs.x)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.x + ColldetBox.Max.x) < (playerAV->Xform.Translation.x + playerAV->Mins.x))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + ColldetBox.Min.y) > (playerAV->Xform.Translation.y + playerAV->Maxs.y)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.y + ColldetBox.Max.y) < (playerAV->Xform.Translation.y + playerAV->Mins.y))) return false;
	if (((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + ColldetBox.Min.z) > (playerAV->Xform.Translation.z + playerAV->Maxs.z)) || ((Q_Forge->Forge[i_AVIndex].AV.Xform.Translation.z + ColldetBox.Max.z) < (playerAV->Xform.Translation.z + playerAV->Mins.z))) return false;
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
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 1)
		{
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 2)
		{
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 3)
		{
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 4)
		{
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 5)
		{
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 6)
		{
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 7)
		{
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 8)
		{
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 9)
		{
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 10)
		{
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 11)
		{
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 12)
		{
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 13)
		{
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateY(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 14)
		{
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 15)
		{
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.x);
		}

	if(vecvar == 16)
		{
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.x);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.y);
		}

	if(vecvar == 17)
		{
		Qpo->Transform_RotateX(&player->Camrot, player->Angles.y);
		Qpo->Transform_RotateZ(&player->Camrot, player->Angles.x);
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
			/*glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
			glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Rearground
			glClearDepth(1.0f);									// Depth Buffer Setup
			glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
			glEnable(GL_BLEND);									// Enable Blending
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
			glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
			glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
			glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
			g_render->set_camera();*/

			
			glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
			//glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Rearground
			//glClearDepth(1.0f);									// Depth Buffer Setup
			glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
			glEnable(GL_BLEND);									// Enable Blending
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
			glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
			glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
			glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

#pragma message("Server Engine excludes")
#if defined(WIN32)
			//g_render->set_camera();
#endif
			} break;

		case CCX_MODE_BLIT:
			{
			glGetIntegerv(GL_VIEWPORT, vPort);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			glEnable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
			} break;

		case CCX_MODE_DRAW:
			{
			glGetIntegerv(GL_VIEWPORT, vPort);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

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

#if 0
int DrawGLScene(GLvoid)										// Here's Where We Do All The Drawing
{
	g_render->set_camera();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Rearground
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glBindTexture(GL_TEXTURE_2D, 1);			// Select Our Texture

	for (int loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
		{
		if (particle[loop].active)							// If The Particle Is Active
			{
				float x=particle[loop].x;						// Grab Our Particle X Position
				float y=particle[loop].y;						// Grab Our Particle Y Position
				float z=particle[loop].z+zoom;					// Particle Z Pos + Zoom

				// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
				//glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);
				glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

				glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
					glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
					glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
					glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
					glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
				glEnd();										// Done Building Triangle Strip

				particle[loop].x+=particle[loop].xi/(slowdown*1000);// Move On The X Axis By X Speed
				particle[loop].y+=particle[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
				particle[loop].z+=particle[loop].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

				particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
				particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
				particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
				particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

				if (particle[loop].life<0.0f)					// If Particle Is Burned Out
				{
					particle[loop].life=1.0f;					// Give It New Life
					particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
					particle[loop].x=0.0f;						// Center On X Axis
					particle[loop].y=0.0f;						// Center On Y Axis
					particle[loop].z=0.0f;						// Center On Z Axis
					particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
					particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
					particle[loop].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
					particle[loop].r=colors[col][0];			// Select Red From Color Table
					particle[loop].g=colors[col][1];			// Select Green From Color Table
					particle[loop].b=colors[col][2];			// Select Blue From Color Table
				}
			}
		}

	return true;											// Everything Went OK
}
#endif