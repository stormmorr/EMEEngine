/*

VoxelGrid.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef VOXELGRID_H
#define VOXELGRID_H

#include <vector>
#include <map>

#include "Include/Cube.h"

#include "Q-PortSHELL-VAR.h"

using namespace Cube;

namespace Cube
{

#define WORLD_BLOCK_STRENGTH_DEFAULT 195.0f
#define WORLD_DMG_DEFAULT 36.0f

#define WORLD_STRENGTH_THRESH 80.0f
#define WORLD_BREAK_THRESH_REDUCE 5.5f
#define WORLD_HEAT_THRESH_CELCIUS 133.0f
#define WORLD_HEAT_ROOM_TEMP 33.0f
#define WORLD_HEAT_COLLECTIVE_GAIN 6.0f
#define WORLD_HEAT_COLLECTIVE_LOSS 4.0f
#define WORLD_HEAT_FRK_AMT 0.035f
#define WORLD_HEAT_REDUCE 4.0f
#define WORLD_HEAT_REDUCE_AMT 0.0175f
#define WORLD_EXPLOSIVE_FORCE_THRESH 35.5f
#define WORLD_REDUCE_AMT 5.5f
#define WORLD_DISTANCE_REDUCE 100.0f
#define WORLD_CUBE_RESIST_AIR_POWER 45.745f
#define WORLD_AV_REACTION_IMPACT_FACTOR 10.3f
#define WORLD_FRAME_COUNT 4000
#define WORLD_SMALLBG_HEIGHT_MAX 1

#define WAR_ZONE_POM_MIN 1
#define WAR_ZONE_POM_MAX 1
#define WAR_ZONE_SMALL_MIN 3
#define WAR_ZONE_SMALL_MAX 6
#define WAR_ZONE_MEDIUM_MIN 2
#define WAR_ZONE_MEDIUM_MAX 5
#define WAR_ZONE_LARGE_MIN 1
#define WAR_ZONE_LARGE_MAX 4
#define WAR_ZONE_OBJECT_MIN 1
#define WAR_ZONE_OBJECT_MAX 4
#define WAR_ZONE_OBJECT_RAND_MIN 1
#define WAR_ZONE_OBJECT_RAND_MAX 6
#define WAR_ZONE_RAND_DIST_CULL_MIN 1.0f
#define WAR_ZONE_RAND_DIST_CULL_MAX 10.0f
#define WAR_ZONE_CLONING_CHANCE 1455 // 688 // 355
#define WAR_ZONE_LAMP_MIN 10
#define WAR_ZONE_LAMP_MAX 20
#define WAR_ZONE_SAVE_ALLWAYS 1

#define LOAD_DISTANCE 2 // 2 // 3
#define VIEW_DISTANCE 2050.0f //1500.0f //1920.0f // 1030.0f

#define VOXEL_ENGINE_THREAD_COUNT 6
#define VOXEL_MARCH_DIV 10

#define VOXEL_RENDER_SIZE 5.0f //"0.5f VVVGood 1 Blocks" //1.5f
#define VOX_GRID_SIZE = 100 //26 //90
#define VOX_GRID_SIZE_REL 100 //26 //90

#define WAR_ZONE_EXTENTS_RADIUS (VOX_GRID_SIZE_REL * (VOXEL_RENDER_SIZE * 2.0f)) * 2.6579f

#if 1
#define WORLD_DAMAGE_EVERY_UPDATE 1
#endif

#if 1
#define VOXEL_BUILD_PROGGRESSIVE 1
#endif

#if 1
#define TERRAIN_UPDATE_MUTEX 1
#endif

#if 0
#define VOXDMG_FULL_TIMESCALE 1
#endif

#define VOX_BY2 ((float)VOX_GRID_SIZE_REL * VOXEL_RENDER_SIZE)

#define AVATAR_STEP_UP 20.0f

typedef unsigned char uint8;

enum MergedSide
{
	MergedSide_None = 0,

	MergedSide_X_Positive = 1,
	MergedSide_X_Negative = 2,
	MergedSide_Y_Positive = 4,
	MergedSide_Y_Negative = 8,
	MergedSide_Z_Positive = 16,
	MergedSide_Z_Negative = 32
};

enum BlockType
{
	BlockType_Default = 0,
	BlockType_Iron,
	BlockType_Cement,
	BlockType_Steel,
	BlockType_Brick,
	BlockType_Wood,
	BlockType_Stone,
	BlockType_Metal,
	BlockType_Plaster,
	BlockType_Glass,
	BlockType_Qcom_Default,
	BlockType_NumTypes
};

enum BlockStat_Argument
{
	BlockArg_Default = 0,
	BlockArg_Flight_Thresh,
	BlockArg_Heat_Resistance,
	BlockArg_Absorbance,
	BlockArg_Brittle,
	BlockArg_Malleability,
	BlockArg_Strength,
	BlockArg_Weight,
	BlockArg_Conductive,
	BlockArg_Explosive,
	BlockArg_Interactive,
	BlockArg_Kinematic,
	BlockArg_Qcom_Default,
	BlockArg_NumTypes
};

enum VoxelLimbState
{
	LimbState_Default = 0,
	LimbState_Begin,
	LimbState_InFlight,
	LimbState_AtRest,
	LimbState_Empty,
	LimbState_NumTypes
};

enum BuildingType
{
	BuildingType_Default = 0,
	BuildingType_SmallBuilding,
	BuildingType_LampPost,
	BuildingType_Shed,
	BuildingType_House,
	BuildingType_SkyScraper,
	BuildingType_Shop,
	BuildingType_FactionBase,
	BuildingType_Sentry,
	BuildingType_Tower,
	BuildingType_Barracade,
	BuildingType_NumTypes
};

enum QEngineMode
{
	QEngine_Default = 0,
	QEngine_Minimal,
	QEngine_World,
	QEngine_NumTypes
};

class VoxelVector
{
public:
	VoxelVector() { acClear(); };

	VoxelVector(int f_Index, int f_BIDX, int f_BIDY, int f_BIDZ)
		{
		m_BIDX = f_BIDX;
		m_BIDY = f_BIDY;
		m_BIDZ = f_BIDZ;
		m_Index = f_Index;
		};

	VoxelVector(int f_BIDX, int f_BIDY, int f_BIDZ)
		{
		m_BIDX = f_BIDX;
		m_BIDY = f_BIDY;
		m_BIDZ = f_BIDZ;
		m_Index = 0;
		};

	~VoxelVector() { acClear(); };

	void acClear(void)
		{
		m_BIDX = 0;
		m_BIDY = 0;
		m_BIDZ = 0;
		m_Index = 0;
		}

	void acLoadOn_BlockForce(BiVector f_LoadOnVector)
		{
		m_LoadOnVector = f_LoadOnVector;
		}

	// Constantly applied each Frame of Grid->acSimulateCores(f_TimeScale)
	BiVector m_LoadOnVector;

	int m_BIDX;
	int m_BIDY;
	int m_BIDZ;

	int m_Index;
};

class VoxelBlock
{
public:
	VoxelBlock() { acClear(); };

	VoxelBlock(int f_Index, int f_BIDX, int f_BIDY, int f_BIDZ)
		{
		acClear();

		m_BIDX = f_BIDX;
		m_BIDY = f_BIDY;
		m_BIDZ = f_BIDZ;

		m_Index = f_Index;
		};

	VoxelBlock(int f_Index, int f_BIDX, int f_BIDY, int f_BIDZ, float f_MoveSpeed, float f_Heat, float f_Intensity)
		{
		m_BIDX = f_BIDX;
		m_BIDY = f_BIDY;
		m_BIDZ = f_BIDZ;

		m_Prop_Speed = f_MoveSpeed;
		m_Heat = f_Heat;
		m_Intensity = f_Intensity;

		m_Index = f_Index;

		m_Heat_Frk = 0.0f;
		};

	~VoxelBlock() { acClear(); };

	void acClear(void)
		{
		m_BIDX = 0;
		m_BIDY = 0;
		m_BIDZ = 0;

		m_Index = 0;

		m_Prop_Speed = 0.0f;
		m_Heat = 0.0f;
		m_Intensity = 0.0f;

		m_Heat_Frk = 0.0f;
		}

	float m_Prop_Speed;
	float m_Heat;
	float m_Heat_Frk;
	float m_Intensity;

	int m_BIDX;
	int m_BIDY;
	int m_BIDZ;

	int m_Index;
};

class BlockMark
{
public:
	BlockMark() { acClear(); };

	BlockMark(int f_VecX, int f_VecY)
		{
		m_VecX = f_VecX;
		m_VecY = f_VecY;
		};

	~BlockMark() { acClear(); };

	void acClear(void)
		{
		m_VecX = 0;
		m_VecY = 0;
		}

	int m_VecX;
	int m_VecY;
};

class MarkLayer
{
public:
	MarkLayer() { acClear(); };

	MarkLayer(BlockMark f_Begin, BlockMark f_Finish, float f_StepX, float f_StepY, float f_ChangeX, float f_ChangeY, float f_FullEdgePower,	float f_PropagationReductionPerc)
		{
		acClear();

		m_Begin = f_Begin;
		m_Finish = f_Finish;

		m_StepX = f_StepX;
		m_StepY = f_StepY;
		m_ChangeX = f_ChangeX;
		m_ChangeY = f_ChangeY;
		m_FullEdgePower = f_FullEdgePower;
		m_PropagationReductionPerc = f_PropagationReductionPerc;
		};

	MarkLayer(float f_FullEdgePower, float f_PropagationReductionPerc)
		{
		acClear();

		m_FullEdgePower = f_FullEdgePower;
		m_PropagationReductionPerc = f_PropagationReductionPerc;

		m_ForwardSpeed = -5.0f;
		};

	~MarkLayer() { acClear(); };

	void acClear(void)
		{
		m_StepX = 0.0f;
		m_StepY = 0.0f;
		m_ChangeX = 0.0f;
		m_ChangeY = 0.0f;
		m_FullEdgePower = 0.0f;
		m_PropagationReductionPerc = 0.0f;
		m_ForwardSpeed = 0.0f;
		}

	void acSetSpeed(float f_SetSpeed)
		{
		m_ForwardSpeed = f_SetSpeed;
		}

	BlockMark m_Begin;
	BlockMark m_Finish;
	BlockMark m_CurrentMark;

	float m_StepX;
	float m_StepY;
	float m_ChangeX;
	float m_ChangeY;

	float m_FullEdgePower;
	float m_PropagationReductionPerc;

	float m_ForwardSpeed;
};

class VoxelDamageMask
{
public:
	VoxelDamageMask() { acClear(); throw; };

	VoxelDamageMask(VoxelBlock f_OriginBlock, BiVector f_ImpactIn, BiVector f_ImpactPoint);
	VoxelDamageMask(BiVector f_ImpactIn, BiVector f_ImpactPoint);
	VoxelDamageMask(BiVector f_ImpactPoint, int f_Radius);

	~VoxelDamageMask() { acClear(); };
	
	void acClear(void)
		{
		m_vec_MarkLayer.clear();

		m_stepX = 0;
		m_stepY = 0;
		m_stepZ = 0;

		m_radius = 1;
		m_Count = 0;

		m_SingleUnit = 0.0f;
		}

	bool acSimulateFrame(float f_TimeScale);

	bool acSimulateFrameXY(float f_TimeScale);
	bool acSimulateFrameGrow(void);

	bool acGrowRadius(int f_Radius)
		{
		m_radius = f_Radius;
		}

	bool m_is_naturalOriginBlock;

	VoxelBlock m_OriginBlock;

	BiVector m_ImpactIn;
	BiVector m_ImpactPoint;
	BiVector m_ImpactNormal;
	BiVector m_CurrentPoint;
	BiVector m_UpVec;
	BiVector m_RightVec;

	float m_SingleUnit;

	int m_stepX;
	int m_stepY;
	int m_stepZ;

	int m_radius;

	int m_Count;

	std::vector<std::shared_ptr<MarkLayer>> m_vec_MarkLayer;
};

class VoxelGrid;

class Building
{
public:
	Building() { acClear(); };
	~Building() { acClear(); };

	void acClear(void)
		{
		m_ON = false;

		m_Perc_X = 0;
		m_Perc_Y = 0;
		m_Perc_Z = 0;
		}

	bool acPush_Grid(std::shared_ptr<VoxelGrid> f_Grid);

	int m_Perc_X;
	int m_Perc_Y;
	int m_Perc_Z;

	BiVector m_Pos;

	int m_Width;
	int m_Length;
	int m_Height;

	int m_MinX;
	int m_MinY;
	int m_MinZ;

	int m_MaxX;
	int m_MaxY;
	int m_MaxZ;

	bool m_ON;
};

class LightStr
{
public:
	LightStr() {};
	~LightStr() {};

	std::shared_ptr<Building> m_Building;

	float m_Radius;
	QpoColor m_RGBA;
};

class WarZone
{
public:
	WarZone();
	WarZone(BiVector f_NewOrigin);
	~WarZone() { acClear(); };

	void acClear(void)
		{
		m_vec_Building.clear();
		m_vec_LightStr.clear();

		acSet_Extents(0.0f);
		}

	void acInitialize(void);

	void acSet_Extents(float f_Extents);

	  ////////////////////
	 // BUILDING ////////
	//
	std::vector<std::shared_ptr<Building>> m_vec_Building;

	std::vector<int> m_vec_WorkStatus_Building;

	std::shared_mutex m_BuildingMuti;

	  /////////////////
	 // LIGHT ////////
	//
	std::vector<std::shared_ptr<LightStr>> m_vec_LightStr;

	 ////////////////////
	// Light Building //
	std::vector<std::shared_ptr<Building>> m_vec_Light_Building;

	std::vector<int> m_vec_WorkStatus_Light_Building;

	std::shared_mutex m_LightBuildingMuti;

	float m_AxisExtent;

	int m_Zone_X;
	int m_Zone_Y;
	int m_Zone_Z;

	BiVector m_position;

	// Building Work
	std::vector<std::shared_ptr<std::vector<int>>> m_vec_WorkComp;
};

struct VoxelGridCoordKeys
{
	int x;
	int y;
	int z;
};

inline bool const operator==(const VoxelGridCoordKeys& l, const VoxelGridCoordKeys& r)
{
	return l.x == r.x && l.y == r.y && l.z == r.z;
};

inline bool const operator<(const VoxelGridCoordKeys& l, const VoxelGridCoordKeys& r)
{
	if (l.x < r.x)  return true;
	if (l.x > r.x)  return false;

	if (l.y < r.y)  return true;
	if (l.y > r.y)  return false;

	if (l.z < r.z)  return true;
	if (l.z > r.z)  return false;

	return false;
};

class VoxelGridCore;
class VoxelGrid;

class VoxelLimb
{
public:
	VoxelLimb() { acClear(); throw; };
	VoxelLimb(int f_ManagerIndex, int f_MinX, int f_MinY, int f_MinZ, int f_MaxX, int f_MaxY, int f_MaxZ);
	~VoxelLimb() { acClear(); };

	void acClear(void);

	// Initialize
	void Initialize(void);
	void RebuildMesh(float f_Scale = 1.0f);
	void CreateMeshCubeDetail(float f_Scale = 1.0f);
	std::string HashMeshColourCube(void);

	void CompleteMesh(void);
	void UpdateEmptyFlag(void);
	void GenerateBuffers(void);

	void acRenderReserve(void);

	void SetNeedsRebuild(bool rebuild, bool f_ReserveReady = false);

	BlockType GetBlockType(int x, int y, int z);

	void SetCreated(bool created);
	void SetGrid(int x, int y, int z);
	void SetPosition(BiVector pos);

	unsigned int AddVertexToMesh(BiVector p1, BiVector n1, float r, float g, float b, float a);
	unsigned int AddTextureCoordinatesToMesh(float u, float v);
	void AddTriangleToMesh(unsigned int v1, unsigned int v2, unsigned int v3);

	void UpdateMergedSide(int* merged, int blockx, int blocky, int blockz, int width, int height, BiVector* p1, BiVector* p2, BiVector* p3, BiVector* p4, int startX, int startY, int maxX, int maxY, bool positive, bool zFace, bool xFace, bool yFace);

	bool IsMergedXNegative(int* merged, int x, int y, int z, int width, int height);
	bool IsMergedXPositive(int* merged, int x, int y, int z, int width, int height);
	bool IsMergedYNegative(int* merged, int x, int y, int z, int width, int height);
	bool IsMergedYPositive(int* merged, int x, int y, int z, int width, int height);
	bool IsMergedZNegative(int* merged, int x, int y, int z, int width, int height);
	bool IsMergedZPositive(int* merged, int x, int y, int z, int width, int height);

	void Make_Alone(void);

	void acPreCalc_Cache(void);
	void acCoreCalc(float f_TimeScale);

	void acInvalidate_Cache(void);

	//###- Limb VX Core
	std::shared_ptr<VoxelGridCore> m_VX_Core;

	std::shared_ptr<VoxelGrid> m_GridRef;

	VoxelLimbState m_State;

	// Physics
	std::vector<std::shared_ptr<VoxelVector>> m_vec_ForceOnVector;

	Cube::BiVector m_VelocityVector;

	int m_UID;

	// Counters
	int m_numRebuilds;

	int m_MinX;
	int m_MinY;
	int m_MinZ;

	int m_MaxX;
	int m_MaxY;
	int m_MaxZ;

	int m_local_MinX;
	int m_local_MinY;
	int m_local_MinZ;

	int m_local_MaxX;
	int m_local_MaxY;
	int m_local_MaxZ;

	int m_Xpos;
	int m_Ypos;
	int m_Zpos;

	// Limb Orientation Transform
	QpoTransform Xform;

	// Reserve Limb Orientation Transform
	QpoTransform res_Xform;

	// grid start position
	Cube::BiVector m_position;

	// grid mid position
	Cube::BiVector m_midpoint;

	   /////////////
	  // GL
	 //
	/// Primary Buffers
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;
	GLuint mIndexBuffer;

	///  Reserve Buffers
	GLuint mresVertexPositionBuffer;
	GLuint mresVertexNormalBuffer;
	GLuint mresVertexColorBuffer;
	GLuint mresVertexTexCoordBuffer;
	GLuint mresIndexBuffer;

	bool m_ShowOff;
	bool m_ReserveReady;

	GLuint m_FaceCount;

	std::vector<std::shared_ptr<Cube::BiVector>> m_vec_Vertex;
	std::vector<std::shared_ptr<Cube::BiVector>> m_vec_Normal;
	std::vector<std::shared_ptr<Cube::BiColor>> m_vec_Color;
	std::vector<std::shared_ptr<Cube::BiTex>> m_vec_Tex;
	std::vector<std::shared_ptr<Cube::Index>> m_vec_Index;

	// Flags for empty VoxelGrid and completely surrounded
	bool m_emptyVoxelGrid;
	bool m_full;

	// Setup and creation flags
	bool m_created;
	bool m_setup;
	bool m_isUnloading;
	bool m_isRebuildingMesh;
	bool m_deleteCachedMesh;

	int m_rebuild;
	int m_repeatbuild;
	int m_build_count;

	int m_gridX;
	int m_gridY;
	int m_gridZ;

	std::string m_Hash;

	int m_ManagerIndex;
	bool m_isParent;

	std::shared_ptr<VoxelLimb> m_Self;
	std::shared_ptr<VoxelLimb> m_Parent;

	std::vector<std::shared_ptr<VoxelLimb>> m_Child;

	// Physics Cach-able Constant
	int m_constant_BlockCount;
	float m_constant_DensityMax;

	BiVector m_Moment;

	float m_AirResistance;
	float m_AirResistanceFactor;

	int m_Simulating;
	int m_rebuildCache;
};

class QpoCollision;

class VoxelGrid// : public ecom_base
	{
	public:
		VoxelGrid();
		VoxelGrid(int f_ManagerIndex);
		~VoxelGrid();

		// Initialize
		void Initialize(void);

		void CreateMesh(void);
		void CreateMeshCubeColour(void);
		void CreateMeshCubeDetail(float f_Scale = 1.0f);

		  /////////////
		 // Cube
		//
		std::string HashMeshColourCube(void);

		bool CollidePointHeight(BiVector f_Point, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ);
		bool CollidePointHeightField(BiVector f_Point, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ);

		// best
		bool CollideMarchPoint(QpoCollision* f_Collision);
		bool CollideCheckPoint(BiVector f_Front, BiVector f_Rear, BiVector* f_ImpactPoint, BiVector* f_ImpactNormal);

		  /////////////
		 // Make
		//
		bool Make_ApplyDamageSphere(BiVector f_Point, float f_Radius, float f_Power, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ);
		void Make_Alone(void);

		unsigned int AddVertexToMesh(BiVector p1, BiVector n1, float r, float g, float b, float a);
		unsigned int AddTextureCoordinatesToMesh(float u, float v);
		void AddTriangleToMesh(unsigned int v1, unsigned int v2, unsigned int v3);

		bool GetActive(int x, int y, int z);
		unsigned int GetColour(int x, int y, int z);
		void GetColour(int x, int y, int z, float* r, float* g, float* b, float* a);
		float GetStrength(int x, int y, int z);
		BlockType GetBlockType(int x, int y, int z);

		//### Limbless
		bool GetActive_Limbless(int x, int y, int z);

		void SetColour(int x, int y, int z, float r, float g, float b, float a, bool setBlockType = false);
		void SetColour(int x, int y, int z, unsigned int colour, bool setBlockType = false);
		void SetColourType(int x, int y, int z, float r, float g, float b, float a, BlockType f_BlockType);
		void SetColourType(int x, int y, int z, unsigned int colour, BlockType f_BlockType);
		void SetStrength(int x, int y, int z, float f_Strength);
		void SetBlockType(int x, int y, int z, BlockType blockType);

		void GenerateBuffers(void);
		void GenerateBuffersColour(void);

		void CompleteMesh(void);
		void CompleteMeshColour(void);

		void UpdateEmptyFlag(void);
		void UpdateMergedSide(int *merged, int blockx, int blocky, int blockz, int width, int height, BiVector *p1, BiVector *p2, BiVector *p3, BiVector *p4, int startX, int startY, int maxX, int maxY, bool positive, bool zFace, bool xFace, bool yFace);

		void RebuildMesh(float f_Scale = 1.0f);
		void RebuildMeshColour(void);

		void UpdateWallFlags(void);
		bool UpdateSurroundedFlag(void);

		void Setup(void);
		bool IsSetup(void);

		void acRenderReserve(void);

		void SetNeedsRebuild(bool rebuild, bool rebuildNeighours, bool f_ReserveReady = false);
		void SetGrid(int x, int y, int z);
		void SetCreated(bool created);
		bool IsCreated(void);

		int acSearch_WithHash_Limb(std::string f_Hash);

		// Position
		void SetPosition(BiVector pos);
		BiVector GetPosition(void);

		bool acSimulateCore(float f_TimeScale);

		void acApply_BlockDamage(int f_Index, int f_blk_X, int f_blk_Y, int f_blk_Z, float f_Strength, float f_ExplosiveForce, float f_HeatPower);
		void acApply_BlockProp(int f_Index, int f_blk_X, int f_blk_Y, int f_blk_Z, float f_Strength, float f_HeatPower);
		void acApply_BlastProp(int f_Index, int f_blk_X, int f_blk_Y, int f_blk_Z, float f_ExplosivePower, BiVector f_BlastCenter);

		bool acMake_BlockFlight(std::shared_ptr<VoxelVector> f_VoxVector, float f_ExplosiveForcePower = 1.0f, float f_ExplosiveHeatIntensity = 1.0f);

		std::shared_ptr<VoxelLimb> acMake_PushLimb(int f_MinX, int f_MinY, int f_MinZ, int f_MaxX, int f_MaxY, int f_MaxZ);
		std::shared_ptr<VoxelLimb> OnVoxelLimb(std::shared_ptr<VoxelVector> f_VoxVector);
		std::shared_ptr<VoxelLimb> OnVoxelLimb(int f_X, int f_Y, int f_Z);

		int GetNumNeighbours(void);
		void SetNumNeighbours(int neighbours);

		std::shared_ptr<VoxelGrid> GetxMinus(void);
		std::shared_ptr<VoxelGrid> GetxPlus(void);
		std::shared_ptr<VoxelGrid> GetyMinus(void);
		std::shared_ptr<VoxelGrid> GetyPlus(void);
		std::shared_ptr<VoxelGrid> GetzMinus(void);
		std::shared_ptr<VoxelGrid> GetzPlus(void);

		void SetxMinus(std::shared_ptr<VoxelGrid> pVoxelGrid);
		void SetxPlus(std::shared_ptr<VoxelGrid> pVoxelGrid);
		void SetyMinus(std::shared_ptr<VoxelGrid> pVoxelGrid);
		void SetyPlus(std::shared_ptr<VoxelGrid> pVoxelGrid);
		void SetzMinus(std::shared_ptr<VoxelGrid> pVoxelGrid);
		void SetzPlus(std::shared_ptr<VoxelGrid> pVoxelGrid);

		aabb* m_aabb;

		std::shared_ptr<WarZone> m_War_Zone;

		// Counters
		int m_numRebuilds;

		static const int VOXEL_GRID_SIZE VOX_GRID_SIZE;
		static const int VOXEL_GRID_SIZE_SQUARED = VOXEL_GRID_SIZE * VOXEL_GRID_SIZE;
		static const int VOXEL_GRID_SIZE_CUBED = VOXEL_GRID_SIZE * VOXEL_GRID_SIZE * VOXEL_GRID_SIZE;
		static const float BLOCK_RENDER_SIZE;

		// VOXEL_GRID neighbours
		int m_numNeighbours;

		std::shared_ptr<VoxelGrid> m_CkXSub;
		std::shared_ptr<VoxelGrid> m_CkXAdd;
		std::shared_ptr<VoxelGrid> m_CkYSub;
		std::shared_ptr<VoxelGrid> m_CkYAdd;
		std::shared_ptr<VoxelGrid> m_CkZSub;
		std::shared_ptr<VoxelGrid> m_CkZAdd;

		// Flags for empty VoxelGrid and completely surrounded
		bool m_emptyVoxelGrid;
		bool m_surroundedVoxelGrid;
		bool m_full;

		// Setup and creation flags
		bool m_created;
		bool m_setup;
		bool m_isUnloading;
		int m_rebuild;
		int m_repeatbuild;
		int m_build_count;
		bool m_rebuildNeighours;
		bool m_isRebuildingMesh;
		bool m_deleteCachedMesh;

		// Used for testing if VoxelGrid completely covers neighbour VoxelGrids
		bool m_XSub_full;
		bool m_XAdd_full;
		bool m_YSub_full;
		bool m_YAdd_full;
		bool m_ZSub_full;
		bool m_ZAdd_full;

		int m_UID;

		int m_gridX;
		int m_gridY;
		int m_gridZ;

		// grid start position
		BiVector m_position;

		// grid start position
		BiVector m_midpoint;

		std::shared_ptr<VoxelGridCore> m_VX_Core;

		   /////////////
		  // GL
		 //
		/// Primary Buffers
		GLuint mVertexPositionBuffer;
		GLuint mVertexNormalBuffer;
		GLuint mVertexColorBuffer;
		GLuint mVertexTexCoordBuffer;
		GLuint mIndexBuffer;

		///  Reserve Buffers
		GLuint mresVertexPositionBuffer;
		GLuint mresVertexNormalBuffer;
		GLuint mresVertexColorBuffer;
		GLuint mresVertexTexCoordBuffer;
		GLuint mresIndexBuffer;

		bool m_ShowOff;
		bool m_ReserveReady;

		GLuint m_FaceCount;

		std::vector<std::shared_ptr<BiVector>> m_vec_Vertex;
		std::vector<std::shared_ptr<BiVector>> m_vec_Normal;
		std::vector<std::shared_ptr<BiColor>> m_vec_Color;
		std::vector<std::shared_ptr<BiTex>> m_vec_Tex;
		std::vector<std::shared_ptr<Index>> m_vec_Index;

		bool m_VoxelGridChangedDuringBatchUpdate;

		bool m_PlacedIn;
		bool m_PlacedInLast;

		std::string m_Hash;

		int m_ManagerIndex;
		bool m_isParent;

		std::shared_ptr<VoxelGrid> m_Self;
		std::shared_ptr<VoxelGrid> m_Parent;
		std::vector<std::shared_ptr<VoxelGrid>> m_Child;
		std::vector<std::shared_ptr<VoxelLimb>> m_vec_VoxelLimb;

		std::shared_ptr<VoxelLimb> m_VoxelLimb_MeM;

		int m_TimedExit;

		int m_Xpos;
		int m_Ypos;
		int m_Zpos;
	};

class VoxelGridCore : public ecom_base
{
public:
	VoxelGridCore(std::shared_ptr<VoxelGrid> f_Grid)
		{
		m_GridRef = f_Grid;

		std::string f_ref_CurrentPath = g_ref_global_start + "VoxelGridCore::VoxelGridCore";

		m_colour = new unsigned int[VoxelGrid::VOXEL_GRID_SIZE_CUBED];
		m_blockType = new unsigned int[VoxelGrid::VOXEL_GRID_SIZE_CUBED];
		m_blockStrength = new float[VoxelGrid::VOXEL_GRID_SIZE_CUBED];

		for(int i = 0; i < VoxelGrid::VOXEL_GRID_SIZE_CUBED; i++)
			{
			m_colour[i] = 0;
			m_blockType[i] = BlockType_Default;
			m_blockStrength[i] = WORLD_BLOCK_STRENGTH_DEFAULT;
			}

#ifndef OSI_MEM_APP
		ac_Push(*(m_colour), f_ref_CurrentPath + g_ref_Div + "m_colour");
		ac_Push(*(m_blockType), f_ref_CurrentPath + g_ref_Div + "m_blockType");
		ac_Push(*(m_blockStrength), f_ref_CurrentPath + g_ref_Div + "m_blockStrength");
#endif
		}

	~VoxelGridCore()
		{
		delete m_colour;
		delete m_blockType;
		delete m_blockStrength;
		m_vec_Prop_energy_Block.clear();
		m_vec_LoadOn_VoxelVector.clear();
		};

	bool GetActive(int x, int y, int z);

	unsigned int GetColour(int x, int y, int z);
	void GetColour(int x, int y, int z, float* r, float* g, float* b, float* a);

	BlockType GetBlockType(int x, int y, int z);

	float GetStrength(int x, int y, int z);
	void SetStrength(int x, int y, int z, float f_Strength);

	void SetColourType(int x, int y, int z, float r, float g, float b, float a, BlockType f_BlockType);
	void SetColourType(int x, int y, int z, unsigned int colour, BlockType f_BlockType);

	void SetColour(int x, int y, int z, float r, float g, float b, float a);
	void SetColour(int x, int y, int z, unsigned int colour);

	void SetNeedsRebuild(bool rebuild, bool rebuildNeighours, int f_blk_X, int f_blk_Y, int f_blk_Z, bool f_ReserveReady = false);

	  //////////////
	 // Data
	// The blocks colour data
	unsigned int* m_colour;

	// Block type
	unsigned int* m_blockType;

	// Block Strength
	float* m_blockStrength;

	std::vector<std::shared_ptr<VoxelBlock>> m_vec_Prop_energy_Block;
	std::vector<std::shared_ptr<VoxelVector>> m_vec_LoadOn_VoxelVector;

	std::shared_ptr<VoxelGrid> m_GridRef;
};

class VoxelGridManager : public ecom_base
{
public:
	VoxelGridManager();
	~VoxelGridManager();

	GLuint acShader(GLenum type, const std::string& source);
	GLuint acProgram(const std::string& vsSource, const std::string& fsSource);

	// VoxelGrid Creation
	void CreateNewVoxelGrid(int x, int y, int z);
	void UpdateVoxelGridNeighbours(std::shared_ptr<VoxelGrid> pVoxelGrid, int x, int y, int z);

	int acSearch_WithHash(std::string f_Hash);
	int acSearch_WithHash_Limb(std::string f_Hash);

	   ///////////////
	  // Make
	 // Gen Layer
	//
	void Make_Gen_Building(uint8 f_BuildingType, BiVector f_FloorCenter, std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	void Make_Gen_Building_Light(uint8 f_BuildingType, BiVector f_FloorCenter, std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);

	bool Make_Gen_IntWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	bool Make_Gen_ExtWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);

	void Make_Gen_Rand_Small_Building(std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	void Make_Gen_Rand_Small_Lighting(std::shared_ptr<LightStr> f_LightStr, std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid);

	bool Make_Place_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	bool Make_Place_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);

	//Base Building Block Function
	bool Make_Gen_Cuboid(BlockType f_BlockType, float f_MinX, float f_MinY, float f_MinZ, float f_MaxX, float f_MaxY, float f_MaxZ, int VColorRed, int VColorGreen, int VColorBlue, int VColorAlpha, std::shared_ptr<VoxelGrid> f_VoxelGrid, std::shared_ptr<VoxelLimb> f_CurrentLimb, bool f_NewLimb = false);
	bool Make_Gen_Point(BlockType f_BlockType, int f_PointX, int f_PointY, int f_PointZ, int VColorRed, int VColorGreen, int VColorBlue, int VColorAlpha, std::shared_ptr<VoxelLimb> f_CurrentLimb);

	// Getting VoxelGrid and positional information
	void GetGridFromPosition(BiVector position, int* gridX, int* gridY, int* gridZ);
	std::shared_ptr<VoxelGrid> GetVoxelGridFromPosition(BiVector position);
	std::shared_ptr<VoxelGrid> GetVoxelGridFromPosition(float posX, float posY, float posZ);
	std::shared_ptr<VoxelGrid> GetVoxelGrid(int aX, int aY, int aZ);
	std::shared_ptr<VoxelGridCore> GetVoxelGridCore(int aX, int aY, int aZ);

	bool GetActive_Global(int x, int y, int z);
	bool GetActive_GlobalPoint(BiVector position, std::shared_ptr<VoxelGrid>* f_ResultGrid, int* f_ResultX, int* f_ResultY, int* f_ResultZ);

	void acFullRebuild(void);

	unsigned int AddVertexToMeshNeighbourhood(std::shared_ptr<VoxelGrid> f_VoxelGrid, int str_x, int str_y, int str_z, BiVector p1, BiVector n1, float r, float g, float b, float a);

	void Position_Player(BiVector f_Position);

	void Draw(BiVector f_Position);

	std::vector<std::shared_ptr<VoxelGrid>> m_VoxelGridsVector;
	std::vector<std::shared_ptr<VoxelLimb>> m_VoxelLimbVector;

	std::vector<std::shared_ptr<VoxelGrid>> m_vec_EngineWork_Grid;
	std::vector<std::shared_ptr<VoxelLimb>> m_vec_EngineWork_Limb;

	std::vector<std::shared_ptr<VoxelGrid>> m_vec_EngineWork_WIP_Grid;
	std::vector<std::shared_ptr<VoxelLimb>> m_vec_EngineWork_WIP_Limb;

	std::shared_mutex m_Muti_EngineWork;
	std::shared_mutex m_OGL_Mutex;

	int m_EngineWork_ThreadCount;

	std::vector<int> m_vec_running_EngineThread_IDX;

	int mx_Grid_UID;
	int mx_Limb_UID;

	void acInitialiseReflection(void)
		{ 	//FIXME
#pragma message("FIXME Push() all relative class member functions from init function in manager constructor(),... for all Managers.")
		std::string f_ref_CurrentPath_VX_Mgr = g_ref_global_start + "VoxelGridManager::VoxelGridManager";

		ag_PushFunction(f_ref_CurrentPath_VX_Mgr + g_ref_fun_Div + "GetVoxelGridCore", /*(ecom_base::ControllerMethod_void)*/&VoxelGridManager::GetVoxelGridCore);

		std::string f_ref_CurrentPath_VXCore = g_ref_global_start + "VoxelGridCore::VoxelGridCore";

		ag_PushFunction(f_ref_CurrentPath_VXCore + g_ref_fun_Div + "SetNeedsRebuild", /*(ecom_base::ControllerMethod_void)*/&VoxelGridCore::SetNeedsRebuild);

#if 1
		std::string f_MappingString = g_ref_global_start + "SecondaryAppWindowPageOGL::SecondaryAppWindowPageOGL" + g_ref_Path_Div + "g_VoxelGridManager" + g_ref_Div + "class Cube::VoxelGridManager" + g_ref_Div + "0" + g_ref_Div;

		std::shared_ptr<ecom_base> f_VoxelGridManagerRefBase = nullptr;

		if(g_Map_ecomRefBase.find(f_MappingString) != g_Map_ecomRefBase.end())
			{//////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////
			f_VoxelGridManagerRefBase = g_Map_ecomRefBase[f_MappingString];
			}
		else
			{
			__debugbreak(); //VX Manager not found in reflection! Lose!
			}

		//###- Invocation Stage -###//
		/*std::function<std::shared_ptr<Cube::VoxelGridCore>(int, int, int)> f_FuncDef = ag_any_cast<std::function<std::shared_ptr<Cube::VoxelGridCore>(int, int, int)>>(g_Map_Function[f_ref_CurrentPath_VX_Mgr + g_ref_fun_Div + "GetVoxelGridCore"]);// , f_VoxelGridManagerRefBase, 0, 0, 0); //ag_any_cast<std::function<std::shared_ptr<VoxelGridCore>(int, int, int)>>(g_Map_Function[f_ref_CurrentPath_VX_Mgr + g_ref_fun_Div + "GetVoxelGridCore"]);

		int f_X = 0;
		int f_Y = 0;
		int f_Z = 0;

		std::function<std::shared_ptr<Cube::VoxelGridCore>(int, int, int)> f_FuncDefInst = std::bind(f_FuncDef, f_VoxelGridManagerRefBase, _1, f_X, _2, f_Y, _3, f_Z);

		std::shared_ptr<Cube::VoxelGridCore> f_returnCore = f_FuncDefInst(f_X, f_Y, f_Z);*/

		//std::shared_ptr<ecom_base> f_VXGridCore_base = f_VoxelGridManagerRefBase->ac_Invoke(f_FuncDef/*f_ref_CurrentPath_VX_Mgr + g_ref_fun_Div + "GetVoxelGridCore"*/, 0, 0, 0);

		std::shared_ptr<ecom_base> f_VXGridCore_base = f_VoxelGridManagerRefBase->ac_Invoke(ag_any_cast<std::shared_ptr<ecom_base>(ecom_base::* /**/)(int, int, int)>(g_Map_Function[f_ref_CurrentPath_VX_Mgr + g_ref_fun_Div + "GetVoxelGridCore"]), 0, 0, 0);

		 //////////////////////////////////////////////////////////////////////////
		//###- Reflect 'VoxelGridCore::SetsNeedsRebuild()' from 'ecom_base' -###//

		unsigned int alpha = (int)(1.0f * 255) << 24;
		unsigned int blue = (int)(0.7f * 255) << 16;
		unsigned int green = (int)(0.6f * 255) << 8;
		unsigned int red = (int)(0.9f * 255);

		unsigned int colour = red + green + blue + alpha;

		unsigned int* f_ArrayUInt = f_VXGridCore_base->m_Map_UInt[f_ref_CurrentPath_VXCore + g_ref_Div + "m_colour"];

		for(int f_Jet = 1; f_Jet < 10; f_Jet++)
			{
			f_ArrayUInt[50 + f_Jet * VoxelGrid::VOXEL_GRID_SIZE + 50 * VoxelGrid::VOXEL_GRID_SIZE_SQUARED] = colour;

			unsigned int f_OneVXBlockColour_One = f_ArrayUInt[50 + f_Jet * VoxelGrid::VOXEL_GRID_SIZE + 50 * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];

			if(f_OneVXBlockColour_One > 0)
				{
#if 1
				__debugbreak(); //bit 1 Win!
#endif
				}
			else
				{
				__debugbreak(); //bit 0 Lose!
				}
			}

#if 0
		//###- Before Update Break!
		__debugbreak(); //Win!
#endif

		   ////////////////////////////////////////////////////
		  //###- Reflect 'VoxelGridCore::SetsNeedsRebuild()'//
		 // (ac_Invoke)
	    // 
		//f_VXGridCore_base->ac_Invoke_Varet(1, f_ref_CurrentPath_VXCore + g_ref_fun_Div + "SetNeedsRebuild", /*f_Returning*/false, true, false, 50, 9, 50, true);

#if 0
		//###- Completion Break!
		__debugbreak(); //Win!
#endif
#endif
		}

private:

	// VoxelGrids storage
	std::map<VoxelGridCoordKeys, std::shared_ptr<VoxelGrid>> m_VoxelGridsMap;
	std::map<VoxelGridCoordKeys, std::shared_ptr<VoxelGridCore>> m_VoxelCoresMap;

	    /////////////
	   // GL
	  //
	 ///
	///
	GLuint mProgram;

	GLint mModelUniformLocation;
	GLint mViewUniformLocation;
	GLint mProjUniformLocation;
	GLint mPosUniformLocation;
	GLint mCamUniformLocation;

	GLint mPositionAttribLocation;
	GLint mNormalAttribLocation;
	GLint mColorAttribLocation;
	GLint mTexCoordAttribLocation;

	GLint mLightPosUniformLocation;
	GLint mLightColorUniformLocation;
	GLint mLightNomUniformLocation;

	GLint mTimeUniformLocation;
	GLint mFrameUniformLocation;

	time_t m_StorageTime;
};

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
			Normal.acSet(0.0f, 0.0f, 0.0f);
			Ratio = 0.0f;
			m_VXGrid = nullptr;
			}

		QpoAvatar							Avatar;
		bool								m_HitAvatar;
		int									m_PxActorID;					// Pointer to what physics actor's id was hit (if any)
		int									m_AvatarID;						// Pointer to what avatar was hit (if any)	
		BiVector							Impact;							// Impact Point
		BiVector							Normal;							// Impact Normal
		float								Ratio;							// Percent from 0 to 1.0, how far along the line for the impact point
		QpoPlane							Plane;							// Impact Plane

		BiVector							Front;							// Impact Point
		BiVector							Rear;

		std::shared_ptr<Cube::VoxelGrid>	m_VXGrid;
		Cube::VoxelVector					m_VXBlock;
};


class QpoAvatarFlags
{
	public:
		bool acRender(void);

		QpoVec3d Ang;
		QpoVec3d OldPos;
		QpoVec3d NewPos;
		QpoVec3d PosGst;
		int CollisionCount;
		QpoCollision Collision;
		QpoVec3d In;
		QpoVec3d Up;
		QpoVec3d Left;
		QpoVec3d Right;
		float upspeed;
		QpoVec3d Mins;
		QpoVec3d Maxs;
		QpoMotion Motion[150];
		QpoAvatar_Def *ActorDef;
		QpoAvatar_Def *AvatarDef;
		QpoTransform Xform;
		QpoTransform STR_Xform;
		QpoMatrix Viewform;
		QpoMatrix Weaponform;
		QpoAvatar Avatar;
		QpoVec3d VecTo;
		QpoVec3d VecToAngle;

		int m_ImpactCount;
};

class QpoInstanceFlags
{
	public:
		bool acRender(void);

		QpoVec3d Ang;
		QpoVec3d OldPos;
		QpoVec3d NewPos;
		QpoCollision Collision;
		QpoVec3d In;
		QpoVec3d Up;
		QpoVec3d Left;
		QpoVec3d Right;
		float upspeed;
		QpoVec3d Mins;
		QpoVec3d Maxs;
		QpoMotion Motion[150];
		QpoAvatar_Def *ActorDef;
		QpoAvatar_Def *AvatarDef;
		QpoTransform Xform;
		QpoTransform Viewform;
		unsigned int Avatar;
		int	IDflag;
		int	Visible;
		QpoVec3d Scale;
		float m_Alpha;
};


class WarZone_Manager
{
	public:
		WarZone_Manager();
		~WarZone_Manager() { acClear(); };

		void acClear(void)
			{
			m_current_WarZone = nullptr;

			m_vec_WarZone.clear();
			}

		void acOnPushGrid(std::shared_ptr<VoxelGrid> f_VoxelGrid)
			{
			acPushGridOrigin(f_VoxelGrid->m_position, f_VoxelGrid);
			}

		// Push Origin
		bool acPushGridOrigin(BiVector f_NewGridOrigin, std::shared_ptr<Cube::VoxelGrid> f_Grid = nullptr);

		std::shared_ptr<WarZone> m_current_WarZone;

		std::vector<std::shared_ptr<WarZone>> m_vec_WarZone;

		BiVector m_current_Zone_Origin;
};

extern std::shared_ptr<VoxelGridManager> g_VoxelGridManager;

extern std::shared_ptr<WarZone_Manager> g_WarZoneManager;

extern float ag_BlockType_Varg(BlockType f_BlockType, int f_BlockArg);

extern int ag_min(int f_In, int f_min);
extern int ag_max(int f_In, int f_max);

extern float ag_min(float f_In, float f_min);
extern float ag_max(float f_In, float f_max);

extern QEngineMode g_EngineMode;

//###- Stealth Declare -###
//### Stage Two Generate Stealth Variable Extern Declarations
#if 0
extern GLenum type;
extern std::string source;
extern std::string vsSource;
extern std::string fsSource;
extern int x;
extern int y;
extern int z;
extern std::shared_ptr<VoxelGrid> pVoxelGrid;
extern std::string f_Hash;
// Make
extern uint8 f_BuildingType;
extern BiVector f_FloorCenter;
extern std::shared_ptr<Building> f_Building;
extern std::shared_ptr<VoxelGrid> f_VoxelGrid;
extern int VWidth;
extern int vLength;
extern int vHeight;
extern BiVector f_Position;
extern std::shared_ptr<LightStr> f_LightStr;
//Base Building Block Function
extern float f_MinX;
extern float f_MinY;
extern float f_MinZ;
extern float f_MaxX;
extern float f_MaxY;
extern float f_MaxZ;
extern int VColorRed;
extern int VColorGreen;
extern int VColorBlue;
extern int VColorAlpha;
extern std::shared_ptr<VoxelLimb> f_CurrentLimb;
extern bool f_NewLimb;
extern int f_PointX;
extern int f_PointY;
extern int f_PointZ;
// Getting VoxelGrid and positional information
extern int* gridX;
extern int* gridY;
extern int* gridZ;
extern float posX;
extern float posY;
extern float posZ;
extern int aX;
extern int aY;
extern int aZ;
extern std::shared_ptr<VoxelGrid>* f_ResultGrid;
extern int* f_ResultX;
extern int* f_ResultY;
extern int* f_ResultZ;
extern int str_x;
extern int str_y;
extern int str_z;
extern BiVector p1;
extern BiVector n1;
extern float r;
extern float g;
extern float b;
extern float a;
#endif

};

#endif