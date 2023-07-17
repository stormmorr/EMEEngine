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

using namespace Cube;

namespace Cube
{

#define WORLD_XSIZE 3
#define WORLD_ZSIZE 3

#define WORLD_BLOCK_STRENGTH_DEFAULT 195.0f
#define WORLD_DMG_DEFAULT 0.9f

#define WORLD_SMALLBG_HEIGHT_MAX 1

#define LOAD_DISTANCE 4
#define VIEW_DISTANCE 650.0f

#define VOXEL_STATE_NOT_OK 0
#define VOXEL_STATE_OK 1
#define VOXEL_STATE_EXIT 2

#define VOXEL_MARCH_DIV 10
#define VOXEL_RENDER_SIZE 7.0f
#define VOX_GRID_SIZE = 26;

typedef unsigned char uint8;

enum MergedSide
{
	MergedSide_None = 0,

	MergedSide_X_Positive = 1,
	MergedSide_X_Negative = 2,
	MergedSide_Y_Positive = 4,
	MergedSide_Y_Negative = 8,
	MergedSide_Z_Positive = 16,
	MergedSide_Z_Negative = 32,
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
	BlockType_NumTypes,
	};

enum BuildingType
	{
	BuildingType_Default = 0,
	BuildingType_SmallBuilding,
	BuildingType_Shed,
	BuildingType_House,
	BuildingType_SkyScraper,
	BuildingType_Shop,
	BuildingType_FactionBase,
	BuildingType_Sentry,
	BuildingType_Tower,
	BuildingType_Barracade,
	BuildingType_NumTypes,
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

struct VoxelGridCoordKeys {
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

		bool CollideMarchPoint(BiVector f_Front, BiVector f_Rear, int f_x, int f_y, int f_z, BiVector* f_ImpactPoint);

		int ray_intersect(const BiVector& ro, const BiVector& rd, BiVector* ip, float* dist);

		  /////////////
		 // Make
		//
		bool Make_ApplyDamageSphere(BiVector f_Point, float f_Radius, float f_Power, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ);

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
		VoxelGrid* GetxMinus(void);
		VoxelGrid* GetxPlus(void);
		VoxelGrid* GetyMinus(void);
		VoxelGrid* GetyPlus(void);
		VoxelGrid* GetzMinus(void);
		VoxelGrid* GetzPlus(void);
		void SetxMinus(VoxelGrid* pVoxelGrid);
		void SetxPlus(VoxelGrid* pVoxelGrid);
		void SetyMinus(VoxelGrid* pVoxelGrid);
		void SetyPlus(VoxelGrid* pVoxelGrid);
		void SetzMinus(VoxelGrid* pVoxelGrid);
		void SetzPlus(VoxelGrid* pVoxelGrid);
		
		aabb* m_aabb;
		bool m_Served;
		int nom_Child;
		int nom_Parent;

		// Counters
		int m_numRebuilds;

		static const int VOXEL_GRID_SIZE VOX_GRID_SIZE;
		static const int VOXEL_GRID_SIZE_SQUARED = VOXEL_GRID_SIZE * VOXEL_GRID_SIZE;
		static const int VOXEL_GRID_SIZE_CUBED = VOXEL_GRID_SIZE * VOXEL_GRID_SIZE * VOXEL_GRID_SIZE;
		static const float BLOCK_RENDER_SIZE;
		static const float BLOCK_RENDER_SIZE_Y;
		static const float VOXEL_GRID_RADIUS;
		static float BLOCK_RENDER_ADJUST;

		// VOXEL_GRID neighbours
		int m_numNeighbours;
		VoxelGrid* m_CkXSub;
		VoxelGrid* m_CkXAdd;
		VoxelGrid* m_CkYSub;
		VoxelGrid* m_CkYAdd;
		VoxelGrid* m_CkZSub;
		VoxelGrid* m_CkZAdd;

		// Flags for empty VoxelGrid and completely surrounded
		bool m_emptyVoxelGrid;
		bool m_surroundedVoxelGrid;

		// Setup and creation flags
		bool m_created;
		bool m_setup;
		bool m_isUnloading;
		int m_rebuild;
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

		BiVector m_position;

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

		int m_ParentID;
		bool m_isParent;
		VoxelGrid* m_Parent;
		std::vector<VoxelGrid*> m_Child;
	};

class VoxelGridManager
{
public:
	/* Public methods */
	VoxelGridManager();
	~VoxelGridManager();

	// VoxelGrid Creation
	void CreateNewVoxelGrid(int x, int y, int z);
	void UnloadVoxelGrid(VoxelGrid* pVoxelGrid);
	void UpdateVoxelGridNeighbours(VoxelGrid* pVoxelGrid, int x, int y, int z);

	void CreatePlayerVoxelGrid(BiVector f_Position, int f_Player, float f_Scale);

	int acSearch_WithHash(std::string f_Hash, bool f_MeshOnly = false);

	   ///////////////
	  // Make
	 // Gen Layer
	//
	bool Make_Gen_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid = nullptr);
	bool Make_Gen_IntWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid = nullptr);
	bool Make_Gen_ExtWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid = nullptr);
	bool Make_Gen_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid = nullptr);

	bool Make_Place_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid = nullptr);
	bool Make_Place_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid = nullptr);

	// Getting VoxelGrid and positional information
	void GetGridFromPosition(BiVector position, int* gridX, int* gridY, int* gridZ);
	VoxelGrid* GetVoxelGridFromPosition(float posX, float posY, float posZ);
	VoxelGrid* GetVoxelGrid(int aX, int aY, int aZ);
	bool FindClosestFloor(BiVector position, BiVector* floorPosition);

	void acFullRebuild(void);

	unsigned int AddVertexToMeshNeighbourhood(VoxelGrid* f_VoxelGrid, int str_x, int str_y, int str_z, BiVector p1, BiVector n1, float r, float g, float b, float a);

	// Getting the active block state given a position and VoxelGrid information
	bool GetBlockActiveFrom3DPosition(float x, float y, float z, BiVector *blockPos, int* blockX, int* blockY, int* blockZ, VoxelGrid** pVoxelGrid);
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

	void DrawPlayer(BiVector f_Position, int f_Player);

	VoxelGrid* m_playerVoxelGrid[4];

	std::vector<Building*> m_vec_Building;

	std::vector<VoxelGrid*> m_VoxelGridsVector;

	std::shared_mutex m_Voxel_Muti;

private:
	// VoxelGrid Material
	unsigned int m_VoxelGridMaterialID;

	// VoxelGrids storage
	std::map<VoxelGridCoordKeys, VoxelGrid*> m_VoxelGridsMap;
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

	GLsizei mWindowWidth;
	GLsizei mWindowHeight;

	GLint mModelUniformLocation;
	GLint mViewUniformLocation;
	GLint mProjUniformLocation;

	GLint mCameraTranslationUniformLocation;

	GLint mPosUniformLocation;

	GLint mPositionAttribLocation;
	GLint mNormalAttribLocation;
	GLint mColorAttribLocation;
	GLint mTexCoordAttribLocation;

	GLint mFloor1StrAttribLocation;
	GLint mFloor2StrAttribLocation;
	GLint mFloor1RedAttribLocation;
	GLint mFloor2RedAttribLocation;
	GLint mFloor1GreenAttribLocation;
	GLint mFloor2GreenAttribLocation;
	GLint mFloor1BlueAttribLocation;
	GLint mFloor2BlueAttribLocation;

	GLint mLightPosUniformLocation;
	GLint mLightColorUniformLocation;
	GLint mLightNomUniformLocation;

	GLint mTimeUniformLocation;

	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;
	GLuint mIndexBuffer;

	int mDrawCount;
};

extern VoxelGridManager* g_VoxelGridManager;

};

#endif