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

#include "Q-PortSHELL-VAR.h"

using namespace Cube;

namespace Cube
{

#define WORLD_BLOCK_STRENGTH_DEFAULT 195.0f
#define WORLD_DMG_DEFAULT 0.9f

#define WORLD_SMALLBG_HEIGHT_MAX 1

#define WAR_ZONE_SMALL_MAX 6
#define WAR_ZONE_MEDIUM_MAX 6
#define WAR_ZONE_LARGE_MAX 3
#define WAR_ZONE_LAMP_MAX 9
#define WAR_ZONE_SAVE_ALLWAYS 1
#define WAR_ZONE_EXTENTS_RADIUS 3.0f

#define LOAD_DISTANCE 2 // 2 // 3
#define VIEW_DISTANCE 1030.0f // 1030.0f
#define VIEW_DISTANCE 1030.0f // 1030.0f

#define VOXEL_STATE_NOT_OK 0
#define VOXEL_STATE_OK 1
#define VOXEL_STATE_EXIT 2
#define VOXEL_MARCH_DIV 10

#define VOXEL_RENDER_SIZE 5.0f
#define VOX_GRID_SIZE = 64 //26
#define VOX_GRID_SIZE_REL 64 //26
#define VOX_GRID_BY2 32.0f

#if 1
#define TERRAIN_UPDATE_MUTEX 1
#endif

#if 0
#define VOXDMG_FULL_TIMESCALE 1
#endif

#define VOX_BY2 (VOX_GRID_BY2 * VOXEL_RENDER_SIZE * 2.0f)

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
	BlockType_NumTypes
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

class VoxelBlock
{
public:
	VoxelBlock() { acClear(); };
	VoxelBlock(int f_BIDX, int f_BIDY, int f_BIDZ)
		{
		m_BIDX = f_BIDX;
		m_BIDY = f_BIDY;
		m_BIDZ = f_BIDZ;
		};
	~VoxelBlock() { acClear(); };

	void acClear(void)
		{
		m_BIDX = 0;
		m_BIDY = 0;
		m_BIDZ = 0;
		}

	int m_BIDX;
	int m_BIDY;
	int m_BIDZ;
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
		m_Begin = f_Begin;
		m_Finish = f_Finish;

		m_StepX = f_StepX;
		m_StepY = f_StepY;
		m_ChangeX = f_ChangeX;
		m_ChangeY = f_ChangeY;
		m_FullEdgePower = f_FullEdgePower;
		m_PropagationReductionPerc = f_PropagationReductionPerc;
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
	VoxelDamageMask(VoxelBlock f_OriginBlock, BiVector f_ImpactIn, BiVector f_ImpactPoint, BiVector f_ImpactNormal);
	VoxelDamageMask(BiVector f_ImpactIn, BiVector f_ImpactPoint, BiVector f_ImpactNormal);
	~VoxelDamageMask() { acClear(); };

	void acClear(void)
		{
		m_vec_MarkLayer.clear();
		}

	bool acSimulateFrame(float f_TimeScale);

	bool m_is_naturalOriginBlock;

	VoxelBlock m_OriginBlock;

	BiVector m_ImpactIn;
	BiVector m_ImpactPoint;
	BiVector m_ImpactNormal;
	BiVector m_CurrentPoint;
	BiVector m_IncrementVec;
	BiVector m_UpVec;
	BiVector m_RightVec;

	float m_SingleUnit;

	std::vector<std::shared_ptr<MarkLayer>> m_vec_MarkLayer;
};

class Building
{
public:
	Building() {};
	~Building() {};

	BiVector m_Pos;

	int m_Width;
	int m_Length;
	int m_Height;
};

class LightStr
{
public:
	LightStr() {};
	~LightStr() {};

	BiVector m_Pos;

	int m_Width;
	int m_Length;
	int m_Height;

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

	  /////////////////
	 // LIGHT ////////
	//
	std::vector<std::shared_ptr<LightStr>> m_vec_LightStr;

	float m_AxisExtent;

	int m_Zone_X;
	int m_Zone_Y;
	int m_Zone_Z;

	BiVector m_position;
};

struct VoxelGridCoordKeys
{
	int x;
	int y;
	int z;
};

class VX
{
public:
	VX()
		{
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
		m_State = 0;
		f_Renderon = false;
		};
	~VX()
		{
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
		m_State = 0;
		f_Renderon = false;
		};

	int m_X;
	int m_Y;
	int m_Z;

	int m_State;
	bool f_Renderon;
};

inline bool const operator==(const VoxelGridCoordKeys& l, const VoxelGridCoordKeys& r) {
	return l.x == r.x && l.y == r.y && l.z == r.z;
};

inline bool const operator<(const VoxelGridCoordKeys& l, const VoxelGridCoordKeys& r) {
	if (l.x < r.x)  return true;
	if (l.x > r.x)  return false;

	if (l.y < r.y)  return true;
	if (l.y > r.y)  return false;

	if (l.z < r.z)  return true;
	if (l.z > r.z)  return false;

	return false;
};

class VoxelGrid
	{
	public:
		VoxelGrid();
		VoxelGrid(int f_ManagerIndex);

		~VoxelGrid();

		// Initialize
		void Initialize(void);
		void Unload(void);

		void CreateMesh(void);
		void CreateMeshCube(float f_Scale = 1.0f);
		void CreateMeshCubeNeighbourhood(float f_Scale = 1.0f);
		void CreateMeshCubeColour(void);
		void CreateMeshCubeDetail(float f_Scale = 1.0f);

		  /////////////
		 // Cube
		//
		std::string HashMeshColourCube(bool f_MeshOnly = false);

		bool CollidePoint(BiVector f_Point, int x, int y, int z);
		bool CollidePointHeight(BiVector f_Point, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ);
		bool CollidePointHeightField(BiVector f_Point, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ);

		bool CollideMarchPoint(BiVector f_Front, BiVector f_Rear, int f_x, int f_y, int f_z, BiVector* f_ImpactPoint, BiVector* f_ImpactNormal);

		bool CollideCheckPoint(BiVector f_Front, BiVector f_Rear, int f_x, int f_y, int f_z, BiVector* f_ImpactPoint, BiVector* f_ImpactNormal);

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

		void SetColour(int x, int y, int z, float r, float g, float b, float a, bool setBlockType = false);
		void SetColour(int x, int y, int z, unsigned int colour, bool setBlockType = false);
		void SetColourType(int x, int y, int z, float r, float g, float b, float a, BlockType f_BlockType);
		void SetColourType(int x, int y, int z, unsigned int colour, BlockType f_BlockType);
		void SetStrength(int x, int y, int z, float f_Strength);
		void SetBlockType(int x, int y, int z, BlockType blockType);
		void SetBlockColour(int x, int y, int z, unsigned int colour);

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

		void SetNeedsRebuild(bool rebuild, bool rebuildNeighours);

		void SetGrid(int x, int y, int z);

		void SetCreated(bool created);
		bool IsCreated(void);

		// Position
		void SetPosition(BiVector pos);
		BiVector GetPosition(void);

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

		int m_gridX;
		int m_gridY;
		int m_gridZ;

		// grid start position
		BiVector m_position;

		// grid start position
		BiVector m_midpoint;

		  //////////////
		 // Data
		// The blocks colour data
		unsigned int *m_colour;

		// Block type
		BlockType *m_blockType;

		// Block Strength
		float *m_blockStrength;

		  ////////////////
		 // Grid
		// Grid Set
		bool m_Grid_blockSet[VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE];

		// Grid Colour
		unsigned int m_Grid_colour[VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE];

		// Block type
		BlockType m_Grid_blockType[VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE];

		// Block Strength
		float m_Grid_blockStrength[VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE][VoxelGrid::VOXEL_GRID_SIZE];

		   /////////////
		  // GL
		 //
		///
		GLuint mVertexPositionBuffer;
		GLuint mVertexNormalBuffer;
		GLuint mVertexColorBuffer;
		GLuint mVertexTexCoordBuffer;

		// Neighbourhood
		GLuint mVertexFloor1StrBuffer;
		GLuint mVertexFloor2StrBuffer;
		GLuint mVertexFloor1RedBuffer;
		GLuint mVertexFloor2RedBuffer;
		GLuint mVertexFloor1GreenBuffer;
		GLuint mVertexFloor2GreenBuffer;
		GLuint mVertexFloor1BlueBuffer;
		GLuint mVertexFloor2BlueBuffer;

		// Indices
		GLuint mIndexBuffer;

		std::vector<BiVector*> m_vec_Vertex;
		std::vector<BiVector*> m_vec_Normal;
		std::vector<BiColor*> m_vec_Color;
		std::vector<BiTex*> m_vec_Tex;
		std::vector<Index*> m_vec_Index;

		std::vector<float> m_vec_Floor1Str;
		std::vector<float> m_vec_Floor2Str;
		std::vector<float> m_vec_Floor1Red;
		std::vector<float> m_vec_Floor2Red;
		std::vector<float> m_vec_Floor1Green;
		std::vector<float> m_vec_Floor2Green;
		std::vector<float> m_vec_Floor1Blue;
		std::vector<float> m_vec_Floor2Blue;

		bool m_VoxelGridChangedDuringBatchUpdate;

		VX* m_VX;

		bool m_PlacedIn;
		bool m_PlacedInLast;

		std::string m_Hash;
		bool m_HashMeshOnly;

		int m_ManagerIndex;
		bool m_isParent;

		std::shared_ptr<VoxelGrid> m_Self;
		std::shared_ptr<VoxelGrid> m_Parent;
		std::vector<std::shared_ptr<VoxelGrid>> m_Child;
	};

class VoxelGridManager
{
public:
	VoxelGridManager();
	~VoxelGridManager();

	GLuint acShader(GLenum type, const std::string& source);
	GLuint acProgram(const std::string& vsSource, const std::string& fsSource);

	// VoxelGrid Creation
	void CreateNewVoxelGrid(int x, int y, int z);
	void UnloadVoxelGrid(std::shared_ptr<VoxelGrid> pVoxelGrid);
	void UpdateVoxelGridNeighbours(std::shared_ptr<VoxelGrid> pVoxelGrid, int x, int y, int z);

	int acSearch_WithHash(std::string f_Hash, bool f_MeshOnly = false);

	   ///////////////
	  // Make
	 // Gen Layer
	//
	bool Make_Gen_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	bool Make_Gen_IntWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	bool Make_Gen_ExtWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	bool Make_Gen_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	bool Make_Gen_Rand_Small_Lighting(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid, QpoColor f_RGBA, float f_Radius);

	bool Make_Place_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);
	bool Make_Place_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid = nullptr);

	// Getting VoxelGrid and positional information
	void GetGridFromPosition(BiVector position, int* gridX, int* gridY, int* gridZ);
	std::shared_ptr<VoxelGrid> GetVoxelGridFromPosition(float posX, float posY, float posZ);
	std::shared_ptr<VoxelGrid> GetVoxelGrid(int aX, int aY, int aZ);
	bool FindClosestFloor(BiVector position, BiVector* floorPosition);

	bool GetActive_Global(int x, int y, int z);
	bool GetActive_GlobalPoint(BiVector position, std::shared_ptr<VoxelGrid> f_ResultGrid, int* f_ResultX, int* f_ResultY, int* f_ResultZ);

	void acFullRebuild(void);

	unsigned int AddVertexToMeshNeighbourhood(std::shared_ptr<VoxelGrid> f_VoxelGrid, int str_x, int str_y, int str_z, BiVector p1, BiVector n1, float r, float g, float b, float a);

	// Getting the active block state given a position and VoxelGrid information
	bool GetBlockActiveFrom3DPosition(float x, float y, float z, BiVector *blockPos, int* blockX, int* blockY, int* blockZ, std::shared_ptr<VoxelGrid>* pVoxelGrid);
	void GetBlockGridFrom3DPositionVoxelGridStorage(float x, float y, float z, int* blockX, int* blockY, int* blockZ);

	// Explosions
	void CreateBlockDestroyParticleEffect(float r, float g, float b, float a, BiVector blockPosition);
	void ExplodeSphere(BiVector position, float radius);

	// Collectible block objects
	void CreateCollectibleBlock(BlockType blockType, BiVector blockPos);

	void Position_Player(BiVector f_Position);

	// Rendering
	void Render(bool shadowRender);

	void Draw(BiVector f_Position);
	void DrawGI(BiVector f_Position);

	void DrawCube(void);
	void DrawPoints(void);

	std::vector<std::shared_ptr<VoxelGrid>> m_VoxelGridsVector;

	std::shared_mutex m_Voxel_Muti;

private:
	// VoxelGrid Material
	unsigned int m_VoxelGridMaterialID;

	// VoxelGrids storage
	std::map<VoxelGridCoordKeys, std::shared_ptr<VoxelGrid>> m_VoxelGridsMap;
	std::vector<VoxelGridCoordKeys*> m_coordKeysVector;

	std::vector<VX*> m_vec_VX;

	// VoxelGrid counters
	int m_numVoxelGridsLoaded;
	int m_numVoxelGridsRender;

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

	GLint mPositionAttribLocation;
	GLint mNormalAttribLocation;
	GLint mColorAttribLocation;
	GLint mTexCoordAttribLocation;

#if 0
	GLint mFloor1StrAttribLocation;
	GLint mFloor2StrAttribLocation;
	GLint mFloor1RedAttribLocation;
	GLint mFloor2RedAttribLocation;
	GLint mFloor1GreenAttribLocation;
	GLint mFloor2GreenAttribLocation;
	GLint mFloor1BlueAttribLocation;
	GLint mFloor2BlueAttribLocation;
#endif

	GLint mLightPosUniformLocation;
	GLint mLightColorUniformLocation;
	GLint mLightNomUniformLocation;

	GLint mTimeUniformLocation;

	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;
	GLuint mIndexBuffer;
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

};

#endif