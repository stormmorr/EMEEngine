/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	- Minor Component -Melee Hits System-
		-Header File Classifications-

*/

#ifndef __Q_WE_BulletSystem__
#define __Q_WE_BulletSystem__

#include "Q-NET-ProtoMap.h"

namespace GVARS
{

class Q_BulletHitCLS
{
public:
	QpoCollision Collision;			//Point of impact in world space
	int			Bonenum;		//Number index of the bone hit
	int			Attbone;
	QpoTransform	AttboneXF;
	QpoVec3d		Reaction;		//Vector describing the bone translation required for the actors hit reaction

	Q_HitFlash		HitFlash;		//HitFlash Struct
	Q_Expandro		Expandro;		//Expandro Struct
	//Q_Particle	Blood[100];		//Blood Struct
	int				BloodAmt;		//Amount of blood to spawn
	int				NumBlood;
	int				EffectType;
	int				Init;
	QpoVec3d			TraVec;			//Trajectory vector
	float			Length;

	int				JDamageLVL;

	QpoVec3d			CollNormal;

	QpoVec3d			BulletTraj;
	float			BulletDMG;
	float			BulletPWR;

	int				AvID;
	int				AvatarHITID;

	QpoVertex	Lvert[24][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int	*Bitmap;		//Bitmap to texture the particle
	float		ScaleBIT;			//Scale
	float		Scale;			//Scale
	int			ScaleDir;
	float		ScaleSP;			//Scale
	QpoTransform	RoTMatrix;
	QpoVec3d		RMIN;
	QpoTransform	AlignMatrix;
	QpoVec3d		AligIn;
	float		AngleJP;
	
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		VertFU1;			//Position of the first vertex
	QpoVec3d		VertFU2;			//Position of the second vertex
	QpoVec3d		VertFU3;			//Position of the third vertex
	QpoVec3d		VertFU4;			//Position of the third vertex
	QpoVec3d		VertFD1;			//Position of the fourth vertex
	QpoVec3d		VertFD2;			//Position of the fourth vertex
	QpoVec3d		VertFD3;			//Position of the fourth vertex
	QpoVec3d		VertFD4;			//Position of the fourth vertex
	QpoVec3d		VertS1;				//Position of the fourth vertex
	QpoVec3d		VertS2;				//Position of the fourth vertex
	QpoVec3d		VertS3;				//Position of the fourth vertex
	QpoVec3d		VertS4;				//Position of the fourth vertex
	QpoVec3d		VertSP1,VertSP2,VertSP3,VertSP4,VertSP5,VertSP6,VertSP7,VertSP8;
	QpoVec3d		Vertex;			//Optional- Destination (world space)
	QpoTransform	Roton;
	float		AlpFade;
	int			ShiftFlag;
	int			Count;			//Optional- Counter for timing

	int			Live;			//MeleeHit Live Switch   0 = OFF / 1 = ON

	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON

	//#### TODO ADD CONSTRUCTORS
	//Q_BulletHit->BulletHitCLS()

	//#### FUNCTION PROTOTYPES
	void ControlServer(void);
	void ControlClient(void);
};


class Q_CartridgeCLS		//*----Cartridge----*
{
public:
	QpoVertex	Lvert[13][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32				RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	//iTextureWrapper	*Bitmap;		//Bitmap to texture the particle
	float				ScaleBIT;			//Scale
	float				Scale;			//Scale
	QpoTransform		AlignMatrix;
	int					SkipFlag;
	QpoVec3d			WorldPos;

	QpoLight			Light;						//Dynamic Light
	QpoColor			LightColor;					//Color of the light

	QpoVec3d			TrajVec;
	float				Xrot,Yrot,Zrot;
	float				XSpin,YSpin,ZSpin;
	float				Speed;
	int					FloorBounce;
	float				Gravity;
	QpoCollision		Collision;
	QpoVec3d			OldPos;

	
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	
	QpoVec3d		VertF1;			//Position of the first vertex
	QpoVec3d		VertF2;			//Position of the second vertex
	QpoVec3d		VertF3;			//Position of the third vertex
	QpoVec3d		VertF4;			//Position of the third vertex
	QpoVec3d		VertF5;			//Position of the fourth vertex
	QpoVec3d		VertB1;			//Position of the fourth vertex
	QpoVec3d		VertB2;			//Position of the fourth vertex
	QpoVec3d		VertB3;			//Position of the fourth vertex
	QpoVec3d		VertB4;				//Position of the fourth vertex
	QpoVec3d		VertB5;				//Position of the fourth vertex
	QpoVec3d		VertFP;				//Position of the fourth vertex
	
	QpoVec3d		Vertex;			//Optional- Destination (world space)

	int			Count;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	int			AvID;
};


class Q_MFlashCLS		//*----Muzzle Flash----*
{
public:
	QpoVertex	Lvert[3][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	float		ScaleBIT;			//Scale
	float		Scale;			//Scale
	float		ScaleSP;			//Scale
	QpoTransform	RoTMatrix;
	QpoVec3d		RMIN;
	QpoTransform	AlignMatrix;
	int			SkipFlag;

	QpoLight		Light;						//Dynamic Light
	QpoColor		LightColor;					//Color of the light

	int			JDamageLVL;
	
	QpoTransform	LineStartXF,LineEndXF;
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		PosEnd;			//End of Bolt in world space
	float		Length;			//Length of bolt
	float		Width;			//Width of bolt
	float		LengNum;
	QpoVec3d		LengthVec;		//Length vector
	QpoVec3d		WidthVec;		//Width vector
	QpoVec3d		VertFU1;			//Position of the first vertex
	QpoVec3d		VertFU2;			//Position of the second vertex
	QpoVec3d		VertFU3;			//Position of the third vertex
	QpoVec3d		VertFU4;			//Position of the third vertex
	QpoVec3d		VertFD1;			//Position of the fourth vertex
	QpoVec3d		VertFD2;			//Position of the fourth vertex
	QpoVec3d		VertFD3;			//Position of the fourth vertex
	QpoVec3d		VertFD4;			//Position of the fourth vertex
	QpoVec3d		VertS1;				//Position of the fourth vertex
	QpoVec3d		VertS2;				//Position of the fourth vertex
	QpoVec3d		VertS3;				//Position of the fourth vertex
	QpoVec3d		VertS4;				//Position of the fourth vertex
	QpoVec3d		VertSP1,VertSP2,VertSP3,VertSP4,VertSP5,VertSP6,VertSP7,VertSP8;
	QpoVec3d		Vertex;			//Optional- Destination (world space)
	QpoTransform	Roton;
	float		AlpFade;
	int			ShiftFlag;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
};


class Q_BulletCLS		//*----Bullet----*
{
public:
	QpoVertex	Lvert[13][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	//iTextureWrapper	*Bitmap;		//Bitmap to texture the particle
	float		ScaleBIT;			//Scale
	float		Scale;			//Scale
	QpoTransform	AlignMatrix;
	int			SkipFlag;
	QpoVec3d		WorldPos;
	QpoVec3d		ORIGPos;
	QpoVec3d		NewPos;			//For collision detection purposes
	QpoCollision Collision;
	QpoVec3d		TrailStart,TrailEnd;
	int			VaporID1,VaporID2,VaporID3;

	QpoLight		Light;						//Dynamic Light
	QpoColor		LightColor;					//Color of the light
	int			RDriveMATCNT;

	int			AvID;

	int			JDamageLVL;

	float		BulletDMG;
	float		BulletPWR;

	QpoVec3d		TrajVec;
	float		Xrot,Yrot,Zrot;
	float		XSpin,YSpin,ZSpin;
	float		Speed;
	int			FloorBounce;
	float		Gravity;
	
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	
	QpoVec3d		VertF1;			//Position of the first vertex
	QpoVec3d		VertF2;			//Position of the second vertex
	QpoVec3d		VertF3;			//Position of the third vertex
	QpoVec3d		VertF4;			//Position of the third vertex
	QpoVec3d		VertF5;			//Position of the fourth vertex
	QpoVec3d		VertB1;			//Position of the fourth vertex
	QpoVec3d		VertB2;			//Position of the fourth vertex
	QpoVec3d		VertB3;			//Position of the fourth vertex
	QpoVec3d		VertB4;			//Position of the fourth vertex
	QpoVec3d		VertB5;			//Position of the fourth vertex
	QpoVec3d		VertFP;			//Position of the fourth vertex
	
	QpoVec3d		Vertex;			//Optional- Destination (world space)

	int			Count;			//Optional- Counter for timing
	int			Live;			//Live Switch   0 = OFF / 1 = ON
	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON
};


class Q_Global_Bullet
{
public:
	Q_BulletCLS Bullet[QAA_NET_ARRAY_MAX];
};

extern QSharedStruct<Q_Global_Bullet> Q_Bullet;

class Q_Global_BulletHit
{
public:
	Q_BulletHitCLS BulletHit[QAA_NET_ARRAY_MAX];
};

extern QSharedStruct<Q_Global_BulletHit> Q_BulletHit;

class Q_Global_Cartridge
{
public:
	Q_CartridgeCLS Cartridge[1500];
};

extern QSharedStruct<Q_Global_Cartridge> Q_Cartridge;

class Q_Global_MFlash
{
public:
	Q_MFlashCLS MFlash[251];
};

extern QSharedStruct<Q_Global_MFlash> Q_MFlash;


};//END namespace GVARS

#endif