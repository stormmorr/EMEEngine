/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	- Minor Component -Avatar When In Human Form-
		-Header File Classifications-

*/

#ifndef __Q_WE_WorldEffects__
#define __Q_WE_WorldEffects__

namespace GVARS
{

class Q_Expandro
{
public:
	QpoVertex		LVert;			//Structure holding hitflash's position in world space, alpha values and colour
	unsigned int	*Bitmap;		//Bitmap to texture the particle
	float			Scale;			//Scale
	float			MaxScale;		//Maximum size the ring will expand to
};


class Q_HitFlash
{
public:
	QpoVertex		LVert;			//Structure holding hitflash's position in world space, alpha values and colour
	int	Type;						//Type of poly.	Normally : QPOLY_TYPE_PNT
	Uint32			RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int	*Bitmap;		//Bitmap to texture the particle
	float			Scale;			//Scale
};


class Q_EffectObject
{
public:
	float			TYPE;
	float			INT;
	int				ON;
	float			Red;
	float			Green;
	float			Blue;
	float			Alpha;
	float			Scale;
	float			TIMER;
	float			CNT;
	int				ID;
};


class Q_TrailPoint		//*----Trail Points----*
{
public:
	QpoVec3d	Pos;			//Position in World Space
	QpoVec3d	DriftVec;
	float		DriftSTR;
	QpoVec3d	StartLeft,StartRight,EndLeft,EndRight;
	QpoVec3d	CameraVector; //vector between camera pos and Start
	QpoVec3d	LaserVector;
	float		Width,Width2;
	QpoColor	StartColor,EndColor;
	QpoVertex	LVerts[6];
	float		TimeElapsed;	//Counter for timing
	float		LifeOfPoint;	//Counter for timing
	int			TYPE;			//Type of Trail
	int			ParentID;
	int			Live;			//Live Switch   0 = OFF / 1 = ON
};


class Q_VaporTrailCLS		//*----Vapor Trails----*
{
public:
	Q_TrailPoint	TrailPoint[500];
	float			LifeOfPoint;
	float			StartWidth;
	float			WidthExpand;
	int				NomPoints;
	int				Live;
};


class Q_WindWakeCLS		//*----Limb Flames----*
{
public:
	QpoVertex		Lvert[48][4];	//Vertices position, alpha values and colour
	int	Type;						//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32			RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	//unsigned int	*Bitmap;		//Bitmap to texture the particle
	float			ScaleBIT;			//Scale
	float			Scale;			//Scale
	float			ScaleSP;			//Scale
	QpoTransform	RoTMatrix;
	QpoVec3d		RMIN;
	QpoTransform	AlignMatrix;

	int				matmem1r,matmem1g,matmem1b;
	int				matmem2r,matmem2g,matmem2b;
	QpoTransform	LineStartXF,LineEndXF;
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		STRPos;			//Position in World Space
	QpoVec3d		PosEnd;			//End of Bolt in world space
	float			Length;			//Length of bolt
	float			Width;			//Width of bolt
	float			LengNum;
	QpoVec3d		LengthVec;		//Length vector
	QpoVec3d		WidthVec;		//Width vector
	QpoVec3d		VertFNT;			//Position of the first vertex
	QpoVec3d		VertT1;			//Position of the Top first vertex
	QpoVec3d		VertT15;			//Position of the Top first vertex
	QpoVec3d		VertT2;			//Position of the Top second vertex
	QpoVec3d		VertT25;			//Position of the Top first vertex
	QpoVec3d		VertT3;			//Position of the Top third vertex
	QpoVec3d		VertT35;			//Position of the Top first vertex
	QpoVec3d		VertT4;			//Position of the Top fourth vertex
	QpoVec3d		VertT45;			//Position of the Top first vertex
	QpoVec3d		VertT5;			//Position of the Top first vertex
	QpoVec3d		VertT55;			//Position of the Top first vertex
	QpoVec3d		VertT6;			//Position of the Top second vertex
	QpoVec3d		VertT65;			//Position of the Top first vertex
	QpoVec3d		VertT7;			//Position of the Top third vertex
	QpoVec3d		VertT75;			//Position of the Top first vertex
	QpoVec3d		VertT8;			//Position of the Top fourth vertex
	QpoVec3d		VertT85;			//Position of the Top first vertex

	QpoVec3d		VertB1;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB15;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB2;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB25;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB3;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB35;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB4;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB45;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB5;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB55;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB6;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB65;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB7;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB75;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB8;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB85;			//Position of the Bottom fourth vertex

	QpoVec3d		VertM1;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM15;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM2;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM25;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM3;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM35;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM4;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM45;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM5;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM55;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM6;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM65;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM7;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM75;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM8;			//Position of the Bottom fourth vertex
	QpoVec3d		VertM85;			//Position of the Bottom fourth vertex
	
	float		MAINALPHA;
	float		AlphaMAX;
	int			ShiftFlag;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	int			AvID;
	int			Init;
	int			ON;
	int			INIT;

	QpoVec3d	MeMPos;
	float		MeMScale;
	float		MeMAlphaMAX;
	QpoVec3d	MeMINvectorAPC;
	float		MeMJinkSpecialON;

	QpoVec3d	Traj;

	const char *Limb;
	int			MaterialCNT,MaterialCNT2;

	//Jink Fog
	QpoVec3d	JFogFront,JFogLeft,JFogBack,JFogRight;
	QpoVec3d	JFogIn,JFogPos;
	float		JFogSize,JFogLight,JFogVLight;
	int			JFogExist;
	int			FaceWidth,FaceHeight;
};


class Q_TexTriEffectCLS		//*----Textured Tri Effects----*
{
public:
	int			EffectType;		//Type of Textured Tri Effect

	QpoVertex	Lvert[30][4];	//Vertices position, alpha values and colour
	int	PolyType;				//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;			//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	int			MaterialCNT,MaterialCNT2;	//Material Counters
	float		Scale;							//Scale of Whole Effect
	float		ScaleBIT;							//Bitmap Scale

	QpoVec3d	VecIn,VecUp;
	QpoVec3d	ExpandVec;
	float		LengthDist,ExpandDist;

	//### Line Definitions used for FLAME TRAILS
	QpoVec3d		VecLeftT,VecLeftB,VecInL,VecInR,VecUpLB,VecUpRB,VecUpLT,VecUpRT;
	QpoTransform	LineStartXF,LineEndXF;
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecRight;
	
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		PosB;			//Position in World Space
	QpoVec3d		STRPos;			//Storage of Position in World Space
	QpoVec3d		VertT1;			//Position of the Top first vertex
	QpoVec3d		VertT2;			//Position of the Top second vertex
	QpoVec3d		VertT3;			//Position of the Top third vertex
	QpoVec3d		VertT4;			//Position of the Top fourth vertex
	QpoVec3d		VertT5;			//Position of the Top first vertex
	QpoVec3d		VertT6;			//Position of the Top second vertex
	QpoVec3d		VertT7;			//Position of the Top third vertex
	QpoVec3d		VertT8;			//Position of the Top fourth vertex
	QpoVec3d		VertB1;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB2;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB3;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB4;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB5;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB6;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB7;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB8;			//Position of the Bottom fourth vertex

	QpoVec3d		VertT15;			//Position of the Top first vertex
	QpoVec3d		VertT25;			//Position of the Top second vertex
	QpoVec3d		VertT35;			//Position of the Top third vertex
	QpoVec3d		VertT45;			//Position of the Top fourth vertex
	QpoVec3d		VertT55;			//Position of the Top first vertex
	QpoVec3d		VertT65;			//Position of the Top second vertex
	QpoVec3d		VertT75;			//Position of the Top third vertex
	QpoVec3d		VertT85;			//Position of the Top fourth vertex
	QpoVec3d		VertB15;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB25;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB35;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB45;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB55;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB65;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB75;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB85;			//Position of the Bottom fourth vertex

	float		Ut,Ub;

	float		Alpha;			//Effect Alpha Value
	float		Red,Green,Blue;	//Effect Colour
	int			Count;			//Optional- Counter for timing
	int			Live;			//Live Switch   0 = OFF / 1 = ON
	int			Init;
};


class Q_PinEffectMeshCLS		//*----Pin Effect Mesh----*
{
public:
	int			EffectType;				//Type of Effect
	int			BaseShape;				//Shape of Effect
	float		EffectScale;
	float		MoveScale;				//Scale of effect movement
	QpoVec3d	Origin;					//Point of Origin
	QpoVec3d	VecIn,VecUp,VecRight;	//Orientation vectors
	int			MaxNumX,MaxNumY;
	QpoVec3d	StartPos,Posfloater;
	int			EffectLive;							//Live Switch   0 = OFF / 1 = ON
	int			NoMLines;

	float		EffectAlpha;						//Effect Alpha Value
	float		EffectRed,EffectGreen,EffectBlue;	//Effect Colour
	int	PolyType;									//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;						//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON

	float		EffectMoveAng;
	float		LineMoveIncZ[1][150];

		//Base Matrix
	QpoVec3d	BaseVert[1][150][150];			//Base Vertices position
	QpoVec3d	BaseVertSTR[1][150][150];		//Base Vertices stored starting position

		//Individual Cells
	int			CellType;							//Type of Cell
	int			CellShape;							//Shape of Cell
	QpoVec3d	CellVert1[1][150][150];			//Cell Vertices position
	QpoVec3d	CellVert1STR[1][150][150];			//Cell Vertices stored position
	QpoVertex	Lvert[1][150][150][4][3];		//Vertices position, alpha values and colour

	float		CellMoveIncZ;

	int			CellMaterialCNT[1][150][150];		//Material Counters
	float		CellScaleBIT;								//Bitmap Scale
	float		CellScale;									//Scale of All Cells

	float		CellAlpha[1][150][150];			//Cell Alpha Value
	float		CellRed[1][150][150];				//Cell Colour
	float		CellGreen[1][150][150];			//Cell Colour
	float		CellBlue[1][150][150];				//Cell Colour
	int			CellLive[1][150][150];				//Live Switch   0 = OFF / 1 = ON

		//# Used For Ring PEF Meshes
	float		PushBrushDist;
	QpoVec3d	BrushVec;
	float		RotateAng;
	QpoTransform RotateMatrix;
	float		RingScale;
	QpoVec3d	LineCenter[150];
	QpoVec3d	PointerVec;
	float		ExpandAMT[150];
	float		BaseXINC[1][150][150],BaseYINC[1][150][150],BaseZINC[1][150][150];
	float		CellXINC[1][150][150],CellYINC[1][150][150],CellZINC[1][150][150];
	float		Distance;
	float		LineTimer[1][150];

		//# Used For Sphere PEF Meshes
	QpoVec3d	EffCenter;
	float		SphereRadius;
	float		LineAlpha[1][150];
	int			LineReleased[1][150];
	QpoVec3d	FlowDir;
	QpoVec3d	WakeStartPos;
};


class Q_TrailLineCLS		//*----Trail Lines----*
{
public:
	QpoVertex	Lvert[10][4];		//Vertices position, alpha values and colour
	int			SectionLIVE[10];	//Section of trail is Live if = '1'
	int	Type;						//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;		//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	//unsigned int	*Bitmap;			//Bitmap to texture the particle
	int			BitmapPTR;			//Flag to state the bitmap used for texturing
	float		Scale;				//Scale

	QpoVec3d	PushVec,PushVecS;
	QpoVec3d	EXvert,EXvert1,EXvert4,EXpandVec;
	QpoVec3d	EXvert2,EXvert3;
	float		AFADE[50];
	float		PSfactor;
	QpoVec3d	AvatarCENTER;
	int			LINK;

	int			MaterialCNT;

	float		Ut,Ub;

	QpoTransform	LineStartXF,LineEndXF;
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecRight;
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		PosEnd;			//End of Bolt in world space
	float			LengthL;			//Length of bolt
	float			LengthR;			//Length of bolt
	float			PushScale;			//Length of bolt
	float			Width;			//Width of bolt
	float			LengNum;
	QpoVec3d		LengthVec;		//Length vector
	QpoVec3d		WidthVec;		//Width vector
	QpoVec3d		Vert1;			//Position of the first vertex
	QpoVec3d		Vert2;			//Position of the second vertex
	QpoVec3d		Vert3;			//Position of the third vertex
	QpoVec3d		Vert4;			//Position of the fourth vertex
	QpoVec3d		ORIGVert3;			//Position of the third vertex
	QpoVec3d		ORIGVert4;			//Position of the fourth vertex
	QpoVec3d		Vertex;			//Optional- Destination (world space)
	QpoTransform	Roton;
	float		AlpFade;
	int			ShiftFlag;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
};


class Q_SparkCLS		//*----Spark System----*
{
public:
	QpoVertex	Lvert[3][4];	//Structure holding particles position in world space, alpha values and colour
	int	Type;			//Type of poly.	Normally : QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int	*Bitmap;		//Bitmap to texture the particle
	float		Scale;			//Scale
	float		ScaleBIT;			//Scale
	QpoVec3d	VecIn,VecLeft,VecUp,VecSTR;
	int			PointToBULHIT;
	int			FadeDir;
	float		TraLength;
	QpoCollision Collision;
	int			SmokeTrail;
	int			CloudTimer;
	int			MatCnt;

	int			EffectType;

	//Added For use with Cleric Heal and energy transmission
	QpoLight	Light;						//Dynamic Light
	QpoColor	LightColor;					//Color of the light

	int			Released;
	int			Absorbed;

	int			HealTarget;

	float		AvatarLightR,AvatarLightG,AvatarLightB;
	float		AvatarINCR,AvatarINCG,AvatarINCB;
	float		LightRedFULL,LightGreenFULL,LightBlueFULL;

	QpoVec3d	CameraVector;
	QpoVec3d	Left;

	QpoVec3d	Pos;			//Position in World Space
	QpoVec3d	PosBrush;			//Position in World Space
	QpoVec3d	OldPos;			//Position in World Space
	float		Speed;
	float		Gravity;
	float		GravSTR;
	float		DownSpeed;

	QpoVec3d	VertF1;			//Position of the first vertex
	QpoVec3d	VertF2;			//Position of the second vertex
	QpoVec3d	VertM1;			//Position of the third vertex
	QpoVec3d	VertM2;			//Position of the third vertex
	QpoVec3d	VertM3;			//Position of the fourth vertex
	QpoVec3d	VertM4;			//Position of the fourth vertex
	QpoVec3d	VertB1;			//Position of the fourth vertex

	float		AlpFade;
	int			Timer;
	int			TimerGoal;
	int			ShiftFlag;
	int			Bounce;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	QpoVec3d	TraVec;			//Trajectory vector
	QpoVec3d	STRVec;
	QpoVec3d	TargetVec;
};


class Q_HSparkCLS		//*----Spark System----*
{
public:
	QpoVertex	Lvert[25][4];	//Structure holding particles position in world space, alpha values and colour
	float		Scale;			//Scale
	float		ScaleSTR;
	float		ScaleBIT;			//Scale
	QpoVec3d	VecIn,VecLeft,VecUp,VecSTR;
	int			PointToBULHIT;
	int			HTYPE;
	int			FadeDir;
	float		TraLength;
	QpoCollision Collision;
	int			SmokeTrail;
	int			CloudTimer;
	float		CNTR;

	int			AvID;
	float		TempDist;
	QpoVec3d	TempVec1;
	QpoVec3d	TempVecLeft,TempVecUp;

	QpoVertex		LaserLV;
	int			DisplayAlpha;
	int			DisplayColor;
	float		DisplayScale;

	//Added For use with Cleric Heal and energy transmission
	QpoLight	Light;						//Dynamic Light
	QpoColor	LightColor;					//Color of the light
	int			LightON;

	int			CoronaMatCnt,CoronaMatCntDIR;

	int			Released;
	int			Absorbed;

	int			HealTarget;

	float		AvatarLightR,AvatarLightG,AvatarLightB;
	float		AvatarINCR,AvatarINCG,AvatarINCB;
	float		LightRedFULL,LightGreenFULL,LightBlueFULL;

	QpoVec3d	CameraVector;
	QpoVec3d	Left;

	QpoVec3d	Pos;			//Position in World Space
	QpoVec3d	PosBrush;			//Position in World Space
	QpoVec3d	OldPos;			//Position in World Space
	float		Speed;
	float		Gravity;
	//float		GravSTR;
	float		DownSpeed;
	float		DownSpeedSTR;

	QpoVec3d		VertF1;			//Position of the Front vertex

	QpoVec3d		VertB1;			//Position of the third vertex
	QpoVec3d		VertB2;			//Position of the third vertex
	QpoVec3d		VertB3;			//Position of the fourth vertex
	QpoVec3d		VertB4;			//Position of the fourth vertex
	QpoVec3d		VertB5;			//Position of the fourth vertex
	QpoVec3d		VertB6;			//Position of the fourth vertex
	QpoVec3d		VertB7;			//Position of the fourth vertex
	QpoVec3d		VertB8;			//Position of the fourth vertex

	QpoVec3d		VertT1;			//Position of the third vertex
	QpoVec3d		VertT2;			//Position of the third vertex
	QpoVec3d		VertT3;			//Position of the fourth vertex
	QpoVec3d		VertT4;			//Position of the fourth vertex
	QpoVec3d		VertT5;			//Position of the fourth vertex
	QpoVec3d		VertT6;			//Position of the fourth vertex
	QpoVec3d		VertT7;			//Position of the fourth vertex
	QpoVec3d		VertT8;			//Position of the fourth vertex

	QpoVec3d		VertE1;			//Position of the Front vertex

	float		AlpFade;
	int			Timer;
	int			TimerGoal;
	int			ShiftFlag;
	int			Bounce;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	QpoVec3d	TraVec;			//Trajectory vector
	QpoVec3d	STRVec;
	QpoVec3d	TargetVec;
};


class Q_SpikeCLS		//*----Heavy Hit Spike----*
{
public:
	int			EffectType;
	float		Scale;			//Scale
	int			EnergyID;
	int			AvID;

	QpoVec3d		CameraVector;
	QpoVec3d		Left;

	QpoVec3d		CenterPos;		//Position of Central Vert in World Space
	QpoVec3d		FrontPos;		//Position of Front Vert in World Space
	QpoVec3d		TailPos;		//Position of Front Vert in World Space

	float		DistBetween;

	int			MoveTail;

	QpoVec3d		TraVec;			//Trajectory vector
	QpoVec3d		OutVec;			//OutWard vector
	float		IncX,IncY,IncZ;

	float		Width;
	float		Gravity;
	float		Speed;

	float		SelFinger;

	int			FadeDir;
	float		AlpFade;
	int			Timer;
	int			TimerGoal;
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
};


class Q_PowerFlashCLS		//*----Bullet----*
{
public:
	QpoVertex	Lvert[3][4];	//Structure holding particles position in world space, alpha values and colour
	int	Type;			//Type of poly.	Normally : QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	float		Scale;			//Scale
	float		ScaleBIT;			//Scale
	QpoVec3d		VecIn,VecLeft,VecUp,VecSTR;
	float		TraLength;
	QpoCollision Collision;
	int			SmokeTrail;
	int			CloudTimer;
	int			MatCNT;
	float		MatCNTtimer;
	float		Size;

	int			EffectType;

	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		OldPos;			//Position in World Space
	float		Speed;
	float		Gravity;
	float		GravSTR;

	QpoVec3d		VertF1;			//Position of the first vertex
	QpoVec3d		VertF2;			//Position of the second vertex
	QpoVec3d		VertM1;			//Position of the third vertex
	QpoVec3d		VertM2;			//Position of the third vertex
	QpoVec3d		VertM3;			//Position of the fourth vertex
	QpoVec3d		VertM4;			//Position of the fourth vertex
	QpoVec3d		VertB1;			//Position of the fourth vertex

	float		EffRED,EffGREEN,EffBLUE;

	QpoVec3d		CameraVector;

	float		AlpFade;
	float		Timer;
	float		TimerGoal;
	int			ShiftFlag;
	int			Bounce;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	QpoVec3d		TraVec;			//Trajectory vector
	QpoVec3d		STRVec;
	QpoVec3d		TargetVec;
};


class Q_DecalCLS		//*----Particle System----*
{
public:
	QpoPolygon	*Polygon;	//Actual Polygon
	QpoVec3d	Pos;			//Position in World Space
	float		Scale;			//Scale
	int			Alpha;			//Alpha
	int			Count;			//Optional- Counter for timing
	int			TYPE;			//Type of Decal
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
};


class Q_Global_BBlood
{
public:
	Q_SparkCLS BBlood[550];
};

extern QSharedStruct<Q_Global_BBlood> Q_BBlood;

class Q_Global_PowerFlash
{
public:
	Q_PowerFlashCLS PowerFlash[1];
};

extern QSharedStruct<Q_Global_PowerFlash> Q_PowerFlash;

class Q_Global_Spike
{
public:
	Q_SpikeCLS HHSpike[750];
};

extern QSharedStruct<Q_Global_Spike> Q_HHSpike;

class Q_Global_HSpark
{
public:
	Q_HSparkCLS HealSpark[500];
};

extern QSharedStruct<Q_Global_HSpark> Q_HealSpark;

class Q_Global_Spark
{
public:
	Q_SparkCLS BSparks[500];
};

extern QSharedStruct<Q_Global_Spark> Q_BSparks;

class Q_Global_VaporTrail
{
public:
	Q_VaporTrailCLS VaporTrail[500];
};

extern QSharedStruct<Q_Global_VaporTrail> Q_VaporTrail;

class Q_Global_WindWake
{
public:
	Q_WindWakeCLS WindWake[251];
};

extern QSharedStruct<Q_Global_WindWake> Q_WindWake;

class Q_Global_PinEffectMesh
{
public:
	Q_PinEffectMeshCLS PinEffectMesh[1];
};

extern QSharedStruct<Q_Global_PinEffectMesh> Q_PinEffectMesh;

class Q_Global_Decal
{
public:
	Q_DecalCLS Decal[100];
};

extern QSharedStruct<Q_Global_Decal> Q_Decal;


};//END namespace GVARS

#endif