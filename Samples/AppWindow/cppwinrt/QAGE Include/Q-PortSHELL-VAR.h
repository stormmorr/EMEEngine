/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -QAGE - PORTSHELL-
	- Minor Component -= Variable Type Definitions =-
		-Instance of Port Shell Header File-

*/

#ifndef __Q_PortSHELL_VAR__
#define __Q_PortSHELL_VAR__

//#### INCLUDE ENGINE SPECIFIC HEADERS

#pragma message("FIXME::: Scan for Optimisation")

/// Engine Includes
//
#include "pMath.h"
#include <vector>
#include <map>

/// Unification Includes
#include "Q-FUNC-Datatypes.h"

#ifndef QAGE_POINT
#include "../UnSRC/Utility/QSharedStruct.h"
#else
#include "../UnSRC/Utility/QSharedStruct-Point.h"
#endif

#if 0
#include "../UnSRC/Avatar/unMesh.h"
#else
class unAvatar;
class CalCoreAnimation;
#endif

class pVector;
class pMatrix;

//##### Unification Console #####//
extern int g_unC_RowON;
extern int g_unCStrSize;
extern std::vector<std::string> g_unConsole_vec_str;
extern std::vector<int> g_unC_vec_ind;
extern std::string g_unConsoleText[10];
extern int g_unCoutcnt;
extern int g_unCoutcntSTR;
//##### Unification Console #####//

using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::Graphics::Display;

//########=====----- ACTIVE VARIABLE TYPES -----=====########

class QpoVec3d
{
public:
	QpoVec3d() {};

	QpoVec3d(float f_x, float f_y, float f_z)
		{
		x = f_x;
		y = f_y;
		z = f_z;
		};

	~QpoVec3d() {};

	void acSet(float f_x, float f_y, float f_z)
		{
		x = f_x;
		y = f_y;
		z = f_z;
		};

	float x,y,z;
};

#include "launcher.h"

using namespace MMAudioPlayer;

typedef pVector QpoVector;

typedef pMatrix QpoMatrix;

typedef struct QpoTransform
{
	pMatrix		Matrix;
	QpoVec3d	Translation;
	//Net
	QpoVec3d	GhostTranslation;
} QpoTransform;

typedef struct QpoAvExtBox
{
	QpoVec3d Mins;
	QpoVec3d Maxs;
} QpoAvExtBox;

typedef struct QpoBox
{
	float xScale, yScale, zScale;
	QpoVec3d GlobalFrameAxes[3];
	QpoTransform Transform, TransformInv;
} QpoBox;

typedef pMatrix QpoBufferMAT;

typedef int QpoLight;

typedef int QpoPose;

//### PLANE FLUX

typedef struct QpoPlane
{
	QpoVec3d	Normal;									// Orientation of plane
	float		Dist;									// Distance from origin
} QpoPlane;

typedef int QpoMotion;

typedef int QpoAvatar_Def;

typedef /*csFog*/ int QpoFog;

//*typedef iTextureWrapper * QpoTexture;

typedef unsigned int * QpoTexture;

//*typedef csRect QpoRect;

typedef struct QpoRect
{
	/// Rectangle bounds.
	float xmin, ymin, xmax, ymax;
} QpoRect;

//*typedef csPoly3D QpoVertex;

typedef struct QpoVertex
{
float x, y, z;		// 3d vertex
float u, v;			// Uv's
float r, g, b, a;	// color
} QpoVertex;

typedef struct QpoPolygon
{
float x, y, z;		// 3d vertex
float u, v;			// Uv's
float r, g, b, a;	// color
} QpoPolygon;

//*typedef /*csColor4*/ int QpoColor;

typedef struct QpoColor
{
float red, green, blue, alpha;	// color
} QpoColor;

typedef struct QpoLightInfo
{
	QpoLight m_Light;
	QpoColor m_Color;
	QpoVec3d m_Pos;
	float m_Radius;
	bool m_ON;
} QpoLightInfo;

typedef int *QpoCamera;

//##### INACTIVE VAR TYPES

typedef int geWorld_Model;

typedef int QpoMotionPath;

typedef int QpoLevelEntity;

typedef int QpoLevelEntity_EntitySet;

typedef int QpoFont;

typedef int QpoBoneCollisionInfo;

typedef int QpoBody;

typedef int QpoLight_DLight;

typedef int QpoDRV_RGB;

typedef int QpoBuffer_Data;

typedef int QpoEnvironmentOptions;

//##### SELF DEFINITIONS

typedef struct QpoExtBox
{
	QpoVec3d Min;
	QpoVec3d Max;
} QpoExtBox;

typedef struct QpoVectorBox
{
	QpoVector Min;
	QpoVector Max;
} QpoVectorBox;

// Lit vertex
typedef struct QpoVertexdef
{
	float X, Y, Z;		// 3d vertex
	float u, v;			// Uv's
	float r, g, b, a;	// color
} QpoVertexdef;

typedef struct QpoRGBA
{
	float r, g, b, a;
} QpoRGBA;

	//*----Avatar Structure----*

class QpoAvatar
{
public:
	unAvatar						*Mesh;
	QpoPose							Pose;
	int								IDflag;
	int								Visible;
	QpoVec3d						Scale;
	CalCoreAnimation				*AvatarANIM[150];
	int								NomAvAnim;
	float							m_Alpha;
};

	//*----Avatar Operators----*

inline bool operator!= (QpoAvatar a1, QpoAvatar a2)
	{
	if(a1.IDflag != a2.IDflag)
		{
		return true;
		}
	else
		{
		return false;
		}
	}

inline bool operator== (QpoAvatar a1, QpoAvatar a2)
	{
	if(a1.IDflag == a2.IDflag)
		{
		return true;
		}
	else
		{
		return false;
		}
	}

inline bool operator!= (QpoAvatar a1, int a2)
	{
	if(a1.IDflag != a2)
		{
		return true;
		}
	else
		{
		return false;
		}
	}

inline bool operator== (QpoAvatar a1, int a2)
	{
	if(a1.IDflag == a2)
		{
		return true;
		}
	else
		{
		return false;
		}
	}

//### COLLISION FLUX - Repositioned in VoxelGrid.h
#if 0
class QpoCollision
{
	public:
		QpoCollision() : m_VXBlock(0, 0, 0, 0)
			{ acClear(); }
		~QpoCollision()
			{ acClear(); }

		void acClear(void)
			{
			m_HitAvatar = false;
			m_PxActorID = -1;
			m_AvatarID = -1;
			Impact.acSet(0.0f, 0.0f, 0.0f);
			Normal.null();
			Ratio = 0.0f;
			m_VXGrid = nullptr;
			}

		int									m_PxActorID;					// Pointer to what physics actor's id was hit (if any)
		QpoAvatar							Avatar;							// Pointer to what avatar was hit (if any)	
		int									m_AvatarID;							
		QpoVec3d							Impact;							// Impact Point
		float								Ratio;							// Percent from 0 to 1.0, how far along the line for the impact point
		QpoPlane							Plane;							// Impact Plane
		bool								m_HitAvatar;
		QpoVector							Normal;
		std::shared_ptr<Cube::VoxelGrid>	m_VXGrid;
		Cube::VoxelVector					m_VXBlock;
};
#endif

#ifndef QpoCollision
typedef struct digiVec3d
{
	float x,y,z;
} digiVec3d;

typedef pVector digiVector;

typedef struct digiPlane
{
	digiVec3d	Normal;									// Orientation of plane
	float		Dist;									// Distance from origin
} digiPlane;

typedef struct DigiCollision
{
	digiPlane		Plane;
	digiVector		Normal;
	digiVec3d		Impact;
	int				m_AvatarID;
	bool			m_HitAvatar;
} DigiCollision;
#endif

class QpoAvatarImage
{
public:
	QpoTransform Xform;
	QpoMatrix Viewform;
	QpoMatrix Weaponform;
	QpoVec3d Angles;
};

//########=====----- GLOBAL VARIABLE DEFINITIONS -----=====########

namespace GVARS
{

	typedef std::shared_ptr<MMAudioPlayer::SoundEffect> QpoSound;
	typedef int QpoSoundDef;

	typedef struct MediaStruct
		{
		//#######-  GLOBAL TEXTUREs  -#######
		unsigned int QAEFF00A,QAEFF01A,QAEFF02A,QAEFF03A,QAEFF04A,QAEFF05A,QAEFF00,QAEFF01,QAEFF02,QAEFF03,QAEFF04,QAEFF05,Scope,MESSAGES,MESSAGESA,DECAL[28],DECALA[28],FONT[11],FONTA[11],SPAWNSpikeBmp,SPAWNSpikeBmpA,attsprite,attspriteA,KObit[15],HADSpikeBmp,HADSpikeBmpA,HHSpikeBmp,HHSpikeBmpA,EGrabCoronaA[4],EGrabCorona[4],SparkCoronaA[4],SparkCorona[4],FlameSingle,JEnergy[46],JEnergyA[46],Water[137],WaterA[137],CloudLimb,CloudLimbA,Cloud9,Cloud9A,JinkRingA[43],JinkRing[43],jinklightning,Text,TextA,HealSphere,HealSphereA,HealSparkA,RanSpark,RanSparkmid,RanSparktail,EGrabSparktail,HealSpark,HealSparkmid,HealSparktail,BulletCount,BulletCountA,BulletTrail,BulletTrailA,EnergyBarLeft,EnergyBarRight,HealthLeft,HealthLeftEXT,HealthLeftA,HealthRight,HealthRightA,Face,FaceA,flame[65],flameA[65],fire[100],fireA[100],flametrail[100],flametrailA[100],CloudBlood,CloudBloodA,ScanBox,ScanBoxA,ScanBone,ScanBoneA,Scanner,Cloud1,Cloud2,Cloud1A,Cloud3,Cloud3A,Cloud2A,expandro2,shadowA3,BulHitFlashSpin,BulHitFlashSpinA,BulHitFlash,BulHitFlashA,Sparktail,Sparkmid,SparkmidA,Spark,SparkA,LaserSight,LaserSightA,MFlashX,MFlashXA,MFlashS1,MFlashS2,MFlashS3,MFlashSA,BlackOut,BlackOutA,jinko,tet,tetA,spec,specA,radfire[64],radfireA[64],EffectsTest,nameplate[10],PulsarMid[43],PulsarMidA[43],Star[26],StarA[26],Rocket[10],RocketA[10],Pulsar[43],PulsarA[43],EnergyMuzz[43],EnergyMuzzA[43],glubber[166],glubberA[166],special[50],specialA[50],special4[50],specialA4[50],greenyN,greenyN2,greeny,greeny2,star1,star2,hudRadar,RADspritesF[3],RADspritesE[3];
		unsigned int hudRadarA,RadSpritesA,hudbottom3,hudbottom1,hudbottom1A,hudbottom2,hudbottom2A,trail1A,trail1,trail2A,trail2,schgirl,schgirlA,renzouA2,renzouA,lightning,lightningA,shadow,shadowA,shadowA2,shineE,shineEA,reticule,reticuleEA,reticuleE,toppanel,toppanel2,icon,bullet,mmine,mmineA,mmineAF,buildm,pyro1,pyro2,pyro3,EXPexpandro1,expandro1,expandro1A,dot,SLogobmp,cart1;
		unsigned int QAEFF06,QAEFF06A,QAEFF07,QAEFF07A,QAEFF08,QAEFF08A,QAEFF09,QAEFF09A,QAEFF10,QAEFF10A,QAEFF11,QAEFF11A,QAEFF12,QAEFF12A,QAEFF13,QAEFF13A,QAEFF14,QAEFF14A,QAEFF15,QAEFF15A,QAEFF16,QAEFF16A,QAEFF17,QAEFF17A,QAEFF18,QAEFF18A,QAEFF19,QAEFF19A,QAEFF20,QAEFF20A,QAEFF21,QAEFF21A,QAEFF22,QAEFF22A,QAEFF23,QAEFF23A,QAEFF24,QAEFF24A,QAEFF25,QAEFF25A,QAEFF26,QAEFF26A,QAEFF27,QAEFF28,QAEFF28A,QAEFF29,QAEFF29A,QAEFF30,QAEFF30A,QAEFF31,QAEFF31A,QAEFF32,QAEFF32A,VaporCAP,VaporLINE,VaporCAPA,VaporLINEA,QSmoke[50],QSmokeA[50];
		unsigned int shibitmap;
		unsigned int ANGELeditBitmap;

			//#######-  GLOBAL SOUNDs  -#######
		int LoopingDef2,LoopingDef3,SingleDef2,SingleDef3,S_RifleFire[13],S_RifleClipOut[10],S_RifleClipIn[10],S_RifleBoltOut[10],S_RifleBoltIn[10];
		int S_Hitwall1,S_Hitwall2,S_Hitwall3,S_Hitwall4,S_SwishN1,S_SwishN2,S_SwishN3,S_SwishN4,S_SwishH1,S_SwishH2,S_SwishH3FEMALE,S_SwishH3MALE;
		int S_SwishSpin,S_AttINITFEMALE,S_AttINITMALE,S_AttINITMULTFEMALE,S_AttINITMULTMALE,S_AttINITSMLFEMALE,S_AttINITSMLMALE;
		int S_HitN1,S_HitN1AV,S_HitSelfN1,S_HitSelfN2,S_HitB1,S_HitH1,S_HitSelfH1,S_BulletHit,S_BulletHitArmour,S_UltraBlowFEMALE,S_UltraBlowMALE;
		int S_KeyLog,S_KeyLogError,S_Jink,S_CJink,S_EJink,S_BJink,S_ShkBlock,S_DefBlock,S_BrkBlock,S_RenzouImpact,S_FireCrackle,S_JINK3ChargeStart;
		int S_JINK3Charge,S_JINK3Vocal,S_CPlasma,S_VehMBStart,S_VehMBStartLoop,S_VehMBSkid,S_VehMBPower,S_VehMBLoopPower,S_VehMBLoopPower2,S_VehMBLoopPower3;
		int S_HighKick,S_UppCutFlames,S_EnemyKO,S_PlayerKO,S_MatStart,S_MatEnd,S_Explosion,S_Explosion3000;
		int S_Renzou,S_RenzouFireRight,S_RenzouFireLeft,S_RenzouFireDouble,S_HadWarning,S_ZoneCapture,S_Footsteps,S_Build;
		int S_QuantumAngelIntro;
		int S_Hover,S_Click;
		} MediaStruct;

	extern QSharedStruct<MediaStruct> Medias;

	extern std::map< const char * , int > m_StructureA;

};

#endif