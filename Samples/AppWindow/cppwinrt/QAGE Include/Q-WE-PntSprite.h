/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	- Minor Component -Point Sprites-
		-Header File Classifications-

*/

#ifndef __Q_WE_PntSprite__
#define __Q_WE_PntSprite__

namespace GVARS
{

class Q_PntSpriteCLS		//*----Particle System----*
{
public:
	QpoVertex	Lvert;			//Structure holding particles position in world space, alpha values and colour
	int	Type;					//Type of poly.	Normally : QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	float		Scale;			//Scale
	int			PartType;		//Particle Type
	int			AvID;
	float		Alpha,Alpha2,AlphaSTR;
	int			R,G,B,IR,IG,IB;
	float		Speed;
	float		SpeedMAX;
	float		TempDist;
	int			AlphaDIR;
	int			AlphaDIR2;
	QpoVec3d	InitPos,Pos,PosSTR;			//Position vector in world space
	float		IncX,IncY,IncZ;	//Trajectory
	QpoVec3d	TraVec;			//Trajectory vector
	QpoVec3d	VecLeft,VecUp;	//Trajectory vector
	QpoVec3d	TempVec1;		//Trajectory vector
	QpoVec3d	Dest;			//Optional- Destination (world space)
	int			SpeedDIR;
	int			AlphaCNT;
	int			AlphaLOCK;
	int			ATTLightON;
	int			ATTCoronaMatt;
	int			ATTCoronaMattDIR;
	int			CoronaMatCntDIR;
	int			CoronaMatCnt;
	int			MATCNT;

	int			LinkON;
	int			LinkTARGET;
	int			LinkALPHADIR;
	float		LinkALPHA;

	QpoVec3d	TrajALTER;

	int			CoronaON;
	int			CoronaALPHADIR;
	float		CoronaALPHA;

	float		RotAMT;
	float		RotAMTSTR;

	QpoVec3d	Vert1,Vert2,Vert3,Vert1STR,Vert2STR,Vert3STR;
	QpoVertex	Lverts[5];

	float		QA_EFF_INTENSITY;

	float		PushOUT;
	float		HeightPos;
	QpoColor	ATTLightColor;
	QpoLight	ATTLight;
	QpoVertex	ATTCoronaLvert;
	float		CNTR;
	QpoVec3d	OldPos;
	QpoCollision Collision;
	int			Direction;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Particle Live Switch   0 = OFF / 1 = ON
};

#define Q_PNTSPRITE_MAX 9000

class Q_Global_PntSprite
{
public:
	Q_Global_PntSprite()
		{
		m_ArrayMx = Q_PNTSPRITE_MAX;
		}

	Q_PntSpriteCLS PntSprite[Q_PNTSPRITE_MAX];

	int m_ArrayMx;
};

extern QSharedStruct<Q_Global_PntSprite> Q_PntSprite;

};//END namespace GVARS

#endif