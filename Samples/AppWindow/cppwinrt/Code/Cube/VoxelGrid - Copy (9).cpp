/*

VoxelGrid.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "VoxelGrid.h"

#include "simplexnoise.h"

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "q-keydefinitions.h"

#include "Render/unRenderer/unRenderer.h"

using namespace GVARS;
using namespace Cube;
using namespace std;

int g_Width = 2560;
int g_Height = 1440;

namespace Cube
{

bool IsMergedXNegative(int *merged, int x, int y, int z, int width, int height)
{
	return (merged[x + y*width + z*width*height] & MergedSide_X_Negative) == MergedSide_X_Negative;
}

bool IsMergedXPositive(int *merged, int x, int y, int z, int width, int height)
{
	return (merged[x + y*width + z*width*height] & MergedSide_X_Positive) == MergedSide_X_Positive;
}

bool IsMergedYNegative(int *merged, int x, int y, int z, int width, int height)
{
	return (merged[x + y*width + z*width*height] & MergedSide_Y_Negative) == MergedSide_Y_Negative;
}

bool IsMergedYPositive(int *merged, int x, int y, int z, int width, int height)
{
	return (merged[x + y*width + z*width*height] & MergedSide_Y_Positive) == MergedSide_Y_Positive;
}

bool IsMergedZNegative(int *merged, int x, int y, int z, int width, int height)
{
	return (merged[x + y*width + z*width*height] & MergedSide_Z_Negative) == MergedSide_Z_Negative;
}

bool IsMergedZPositive(int *merged, int x, int y, int z, int width, int height)
{
	return (merged[x + y*width + z*width*height] & MergedSide_Z_Positive) == MergedSide_Z_Positive;
}

bool VoxelLimb::IsMergedXNegative(int *merged, int x, int y, int z, int width, int height)
{
	bool f_SeparateEdge = false;

	if (x == m_MinX)
		f_SeparateEdge = true;

	if (y == m_MinY)
		f_SeparateEdge = true;

	if (z == m_MinZ)
		f_SeparateEdge = true;

	if (x == m_MaxX - 1)
		f_SeparateEdge = true;

	if (y == m_MaxY - 1)
		f_SeparateEdge = true;

	if (z == m_MaxZ - 1)
		f_SeparateEdge = true;

	return ((merged[x + y*width + z*width*height] & MergedSide_X_Negative) == MergedSide_X_Negative) && (f_SeparateEdge == false);
}

bool VoxelLimb::IsMergedXPositive(int *merged, int x, int y, int z, int width, int height)
{
	bool f_SeparateEdge = false;

	if (x == m_MinX)
		f_SeparateEdge = true;

	if (y == m_MinY)
		f_SeparateEdge = true;

	if (z == m_MinZ)
		f_SeparateEdge = true;

	if (x == m_MaxX - 1)
		f_SeparateEdge = true;

	if (y == m_MaxY - 1)
		f_SeparateEdge = true;

	if (z == m_MaxZ - 1)
		f_SeparateEdge = true;

	return ((merged[x + y*width + z*width*height] & MergedSide_X_Positive) == MergedSide_X_Positive) && (f_SeparateEdge == false);
}

bool VoxelLimb::IsMergedYNegative(int *merged, int x, int y, int z, int width, int height)
{
	bool f_SeparateEdge = false;

	if (x == m_MinX)
		f_SeparateEdge = true;

	if (y == m_MinY)
		f_SeparateEdge = true;

	if (z == m_MinZ)
		f_SeparateEdge = true;

	if (x == m_MaxX - 1)
		f_SeparateEdge = true;

	if (y == m_MaxY - 1)
		f_SeparateEdge = true;

	if (z == m_MaxZ - 1)
		f_SeparateEdge = true;

	return ((merged[x + y*width + z*width*height] & MergedSide_Y_Negative) == MergedSide_Y_Negative) && (f_SeparateEdge == false);
}

bool VoxelLimb::IsMergedYPositive(int *merged, int x, int y, int z, int width, int height)
{
	bool f_SeparateEdge = false;

	if (x == m_MinX)
		f_SeparateEdge = true;

	if (y == m_MinY)
		f_SeparateEdge = true;

	if (z == m_MinZ)
		f_SeparateEdge = true;

	if (x == m_MaxX - 1)
		f_SeparateEdge = true;

	if (y == m_MaxY - 1)
		f_SeparateEdge = true;

	if (z == m_MaxZ - 1)
		f_SeparateEdge = true;

	return ((merged[x + y*width + z*width*height] & MergedSide_Y_Positive) == MergedSide_Y_Positive) && (f_SeparateEdge == false);
}

bool VoxelLimb::IsMergedZNegative(int *merged, int x, int y, int z, int width, int height)
{
	bool f_SeparateEdge = false;

	if (x == m_MinX)
		f_SeparateEdge = true;

	if (y == m_MinY)
		f_SeparateEdge = true;

	if (z == m_MinZ)
		f_SeparateEdge = true;

	if (x == m_MaxX - 1)
		f_SeparateEdge = true;

	if (y == m_MaxY - 1)
		f_SeparateEdge = true;

	if (z == m_MaxZ - 1)
		f_SeparateEdge = true;

	return ((merged[x + y*width + z*width*height] & MergedSide_Z_Negative) == MergedSide_Z_Negative) && (f_SeparateEdge == false);
}

bool VoxelLimb::IsMergedZPositive(int *merged, int x, int y, int z, int width, int height)
{
	bool f_SeparateEdge = false;

	if (x == m_MinX)
		f_SeparateEdge = true;

	if (y == m_MinY)
		f_SeparateEdge = true;

	if (z == m_MinZ)
		f_SeparateEdge = true;

	if (x == m_MaxX - 1)
		f_SeparateEdge = true;

	if (y == m_MaxY - 1)
		f_SeparateEdge = true;

	if (z == m_MaxZ - 1)
		f_SeparateEdge = true;

	return ((merged[x + y*width + z*width*height] & MergedSide_Z_Positive) == MergedSide_Z_Positive) && (f_SeparateEdge == false);
}

// Engine Mode
QEngineMode g_EngineMode = QEngineMode::QEngine_Default;

// Grid Manager
std::shared_ptr<VoxelGridManager> g_VoxelGridManager;

// Warzone of Grid Manager
std::shared_ptr<WarZone_Manager> g_WarZoneManager;

#define STRING(s) #s

GLuint VoxelGridManager::acShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *sourceArray[1] = { source.c_str() };
    glShaderSource(shader, 1, sourceArray, NULL);
    glCompileShader(shader);

    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if(compileResult == 0)
		{
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Shader compilation failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 

		std::string f_ErrorString = to_string(errorMessage);

#if 0
		printf("SHADER ERROR:::VX:::%s\n", f_ErrorString.c_str());
#endif
#if 0
		throw;
#endif
#if 1
#ifdef ECOIN_DEBUG_BREAKS 
		__debugbreak();
#endif //add debug message
#endif
		}

    return shader;
}

GLuint VoxelGridManager::acProgram(const std::string &vsSource, const std::string &fsSource)
{
    GLuint program = glCreateProgram();

    if(program == 0)
		{
        throw;
		}

    GLuint vs = acShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = acShader(GL_FRAGMENT_SHADER, fsSource);

    if (vs == 0 || fs == 0)
		{
        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(program);
        return 0;
		}

    glAttachShader(program, vs);
    glDeleteShader(vs);

    glAttachShader(program, fs);
    glDeleteShader(fs);

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if(linkStatus == 0)
		{
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Program link failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end());

		std::string f_ErrorString = to_string(errorMessage);

#if 0
		printf("SHADER ERROR:::VX:::%s\n", f_ErrorString.c_str());
#endif
#if 0
		throw;
#endif
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
		}

    return program;
}

// A VoxelGrid cube is double this render size, since we create from - to + for each axis.
const float VoxelGrid::BLOCK_RENDER_SIZE = VOXEL_RENDER_SIZE;

void VoxelLimb::acClear(void)
{
	m_vec_ForceOnVector.clear();

	m_VX_Core = nullptr;

	m_State = VoxelLimbState::LimbState_Empty;
}

VoxelLimb::VoxelLimb(int f_ManagerIndex, int f_MinX, int f_MinY, int f_MinZ, int f_MaxX, int f_MaxY, int f_MaxZ)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	m_rebuild = 1;
	m_repeatbuild = 0;
	m_rebuildCache = 1;
	m_Simulating = 1;

	m_UID = g_VoxelGridManager->mx_Limb_UID;

	g_VoxelGridManager->mx_Limb_UID++;

	m_Parent = nullptr;
	m_Self = nullptr;
	m_setup = true;

	m_isParent = true;

	m_build_count = 0;

	m_ManagerIndex = f_ManagerIndex;

	m_VX_Core = nullptr;

	m_State = VoxelLimbState::LimbState_Begin;

	mVertexPositionBuffer = 0;
	mVertexNormalBuffer = 0;
	mVertexColorBuffer = 0;
	mVertexTexCoordBuffer = 0;

	mIndexBuffer = 0;

	m_MinX = f_MinX;
	m_MinY = f_MinY;
	m_MinZ = f_MinZ;

	m_MaxX = f_MaxX;
	m_MaxY = f_MaxY;
	m_MaxZ = f_MaxZ;

	m_local_MinX = m_MinX - m_Xpos;
	m_local_MinY = m_MinY - m_Ypos;
	m_local_MinZ = m_MinZ - m_Zpos;

	m_local_MaxX = m_MinX - m_Xpos;
	m_local_MaxY = m_MinY - m_Ypos;
	m_local_MaxZ = m_MinZ - m_Zpos;

	Initialize();

	m_AirResistance = 0.001;

	m_AirResistanceFactor = 1.0f - m_AirResistance;
}

VoxelGrid::VoxelGrid()
{
	throw;
}

VoxelGrid::VoxelGrid(int f_ManagerIndex)
{
	m_rebuild = 1;
	m_repeatbuild = 0;

	m_UID = g_VoxelGridManager->mx_Grid_UID;

	g_VoxelGridManager->mx_Grid_UID++;

	m_Parent = nullptr;
	m_Self = nullptr;
	m_setup = false;

	m_isParent = true;

	m_build_count = 0;

	m_aabb = nullptr;

	m_ManagerIndex = f_ManagerIndex;

	mVertexPositionBuffer = 0;
	mVertexNormalBuffer = 0;
	mVertexColorBuffer = 0;
	mVertexTexCoordBuffer = 0;

	mIndexBuffer = 0;

	m_War_Zone = nullptr;

	m_vec_VoxelLimb.clear();

	Initialize();

	m_TimedExit = 0;
}

VoxelGrid::~VoxelGrid()
{
#if 0
	Unload();
#endif
}

// Initialize
void VoxelGrid::Initialize()
{
	// Neighbours
	m_numNeighbours = 0;
	m_CkXSub = NULL;
	m_CkXAdd = NULL;
	m_CkYSub = NULL;
	m_CkYAdd = NULL;
	m_CkZSub = NULL;
	m_CkZAdd = NULL;

	// Grid
	m_gridX = 0;
	m_gridY = 0;
	m_gridZ = 0;

	// Flags
	m_emptyVoxelGrid = false;
	m_surroundedVoxelGrid = false;
	m_full = false;

	m_ShowOff = false;
	m_ReserveReady = false;

	m_FaceCount = 0;

	m_XSub_full = false;
	m_XAdd_full = false;
	m_YSub_full = false;
	m_YAdd_full = false;
	m_ZSub_full = false;
	m_ZAdd_full = false;

	m_PlacedIn = false;
	m_PlacedInLast = false;
}

// Initialize
void VoxelLimb::Initialize()
{
	// Grid
	m_gridX = 0;
	m_gridY = 0;
	m_gridZ = 0;

	// Flags
	m_emptyVoxelGrid = false;
	m_full = false;

	m_ShowOff = false;
	m_ReserveReady = false;

	m_FaceCount = 0;
}

// Creation and destruction
void VoxelGrid::SetCreated(bool created)
{
	m_created = created;

	if(m_repeatbuild > 0)
		{
		m_repeatbuild = 0;

		RebuildMesh();
		CompleteMesh();
		SetCreated(true);
		}
}

// Creation and destruction
void VoxelLimb::SetCreated(bool created)
{
	m_created = created;

	if(m_repeatbuild > 0)
		{
		m_repeatbuild = 0;

		RebuildMesh();
		CompleteMesh();
		SetCreated(true);
		}
}

bool VoxelGrid::IsCreated(void)
{
	return m_created;
}

void VoxelGrid::Setup(void)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	if(m_setup == false)
		{
		for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
			{
			for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
				{
				float xPosition = m_position.m_X + x;
				float zPosition = m_position.m_Z + z;

				//Biome biome = VoxGame::GetInstance()->GetBiomeManager()->GetBiome(BiVector(xPosition, 0.0f, zPosition));

				// Get the 
				float noise = octave_noise_2d(4.0f, 0.3f, 1.0f, xPosition, zPosition);
				float noiseNormalized = ((noise + 1.0f) * 0.5f);
				float noiseHeight = noiseNormalized * 6.5f;

				// Multiple by mountain ratio
				float mountainNoise = octave_noise_2d(4.0f, 0.3f, 0.0075f, xPosition, zPosition);
				float mountainNoiseNormalise = (mountainNoise + 1.0f) * 0.5f;
				float mountainMultiplier = 3.0f * mountainNoiseNormalise;
				noiseHeight *= mountainMultiplier;

				// Smooth out for towns
				//float townMultiplier = 1.3f;// VoxGame::GetInstance()->GetBiomeManager()->GetTowMultiplier(BiVector(xPosition, 0.0f, zPosition));
				//noiseHeight *= townMultiplier;

				noiseHeight *= 1.0f;

				float f_Height = 4.5f;

				for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
					{
					float yPosition = m_position.m_Y + (y * BLOCK_RENDER);

					if(yPosition < noiseHeight)
						{
						if(y + (m_gridY * VOXEL_GRID_SIZE) < f_Height)
							{
							float colorNoise = octave_noise_3d(4.0f, 0.3f, 0.005f, xPosition, yPosition, zPosition);
							float colorNoiseNormalized = ((colorNoise + 1.0f) * 0.5f);

							float red = 0.65f;
							float green = 0.80f;
							float blue = 0.00f;
							float alpha = 1.0f;
							BlockType blockType = BlockType_Default;

							//m_pBiomeManager->GetVoxelGridColourAndBlockType(xPosition, yPosition, zPosition, noise, colorNoiseNormalized, &red, &green, &blue, &blockType);

							SetColour(x, y, z, red, green, blue, alpha);
							SetBlockType(x, y, z, blockType);
							}
						}
					}

#if 0
				// Tree generation
				if (m_gridY >= 0) // Only above ground
				{
					// Trees
					if ((GetRandomNumber(0, 2000) >= 2000))
					{
						float minTreeHeight = 0.0f;
						if (biome == Biome_GrassLand)
						{
							minTreeHeight = 0.5f;
						}
						else if (biome == Biome_Desert)
						{
							minTreeHeight = 0.0f;
						}
						else if (biome == Biome_AshLand)
						{
							minTreeHeight = 0.25f;
						}

						if (noiseNormalized >= minTreeHeight)
						{
							BiVector treePos = BiVector(xPosition, noiseHeight, zPosition);

							if (biome == Biome_GrassLand)
							{
								g_VoxelGridManager->ImportQubicleBinary("media/gamedata/terrain/plains/smalltree.qb", treePos, QubicleImportDirection_Normal);
							}
							else if (biome == Biome_Desert)
							{
								g_VoxelGridManager->ImportQubicleBinary("media/gamedata/terrain/desert/cactus1.qb", treePos, QubicleImportDirection_Normal);
							}
							else if (biome == Biome_Tundra)
							{
								g_VoxelGridManager->ImportQubicleBinary("media/gamedata/terrain/tundra/tundra_tree1.qb", treePos, QubicleImportDirection_Normal);
							}
							else if (biome == Biome_AshLand)
							{
								g_VoxelGridManager->ImportQubicleBinary("media/gamedata/terrain/ashlands/ashtree1.qb", treePos, QubicleImportDirection_Normal);
							}
						}
					}

					// Scenery
					// TODO : Create scenery using poisson disc and also using instance manager.
					//if((GetRandomNumber(0, 1000) >= 995))
					//	{
					//	if (noiseNormalized >= 0.5f)
					//		{
					//		BiVector pos = BiVector(xPosition, noiseHeight, zPosition);
					//		m_pSceneryManager->AddSceneryObject("flower", "media/gamedata/terrain/plains/flower1.qb", pos, BiVector(0.0f, 0.0f, 0.0f), QubicleImportDirection_Normal, QubicleImportDirection_Normal, 0.08f, GetRandomNumber(0, 360, 2));
					//		}
					//	}
					}
#endif
				}
			}

		m_setup = true;
		}
}

BlockType VoxelGrid::GetBlockType(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return BlockType_Default;
		}

	return m_VX_Core->m_blockType[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

BlockType VoxelLimb::GetBlockType(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return BlockType_Default;
		}

	return m_VX_Core->m_blockType[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

BlockType VoxelGridCore::GetBlockType(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return BlockType_Default;
		}

	return m_blockType[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

bool VoxelGrid::GetActive(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return false;
		}

	unsigned int colour = m_VX_Core->m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];

	unsigned int alpha = (colour & 0xFF000000) >> 24;

#if 0
	unsigned int blue = (colour & 0x00FF0000) >> 16;
	unsigned int green = (colour & 0x0000FF00) >> 8;
	unsigned int red = (colour & 0x000000FF);
#endif

	if(alpha == 0)
		{
		return false;
		}

	return true;
}

bool VoxelGrid::GetActive_Limbless(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return false;
		}

	std::shared_ptr<VoxelLimb> f_Limb = OnVoxelLimb(x, y, z);

	if(f_Limb == nullptr)
		{
		unsigned int colour = m_VX_Core->m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];

		unsigned int alpha = (colour & 0xFF000000) >> 24;

#if 0
		unsigned int blue = (colour & 0x00FF0000) >> 16;
		unsigned int green = (colour & 0x0000FF00) >> 8;
		unsigned int red = (colour & 0x000000FF);
#endif

		if(alpha <= 0)
			{
			return false;
			}
		else
			{
			return true;
			}
		}

	return false;
}

bool VoxelGridCore::GetActive(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return false;
		}

	unsigned int colour = m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];

	unsigned int alpha = (colour & 0xFF000000) >> 24;

	if(alpha == 0)
		{
		return false;
		}

	return true;
}

bool VoxelGridManager::GetActive_Global(int x, int y, int z)
{
	int f_Xplus_Grid = x / VOX_GRID_SIZE_REL;
	int f_Local_X = x - (VOX_GRID_SIZE_REL * f_Xplus_Grid);

	int f_Yplus_Grid = x / VOX_GRID_SIZE_REL;
	int f_Local_Y = y - (VOX_GRID_SIZE_REL * f_Yplus_Grid);

	int f_Zplus_Grid = x / VOX_GRID_SIZE_REL;
	int f_Local_Z = z - (VOX_GRID_SIZE_REL * f_Zplus_Grid);

	std::shared_ptr<VoxelGrid> f_Grid = GetVoxelGrid(f_Xplus_Grid, f_Xplus_Grid, f_Xplus_Grid);

	if(f_Grid != nullptr)
		{
		if (f_Grid->m_rebuild == 1)
			return false;

		if ((f_Local_X < 0) || (f_Local_X >= VoxelGrid::VOXEL_GRID_SIZE) ||
			(f_Local_Y < 0) || (f_Local_Y >= VoxelGrid::VOXEL_GRID_SIZE) ||
			(f_Local_Z < 0) || (f_Local_Z >= VoxelGrid::VOXEL_GRID_SIZE))
			{
			return false;
			}

		unsigned int colour = f_Grid->m_VX_Core->m_colour[f_Local_X + f_Local_Y * VoxelGrid::VOXEL_GRID_SIZE + f_Local_Z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
		unsigned int alpha = (colour & 0xFF000000) >> 24;
		unsigned int blue = (colour & 0x00FF0000) >> 16;
		unsigned int green = (colour & 0x0000FF00) >> 8;
		unsigned int red = (colour & 0x000000FF);

		if(alpha > 0)
			{
			return true;
			}
		}

	return false;
}

bool VoxelGridManager::GetActive_GlobalPoint(BiVector position, std::shared_ptr<VoxelGrid>* f_ResultGrid, int* f_ResultX, int* f_ResultY, int* f_ResultZ)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	std::shared_ptr<VoxelGrid> f_Grid = GetVoxelGridFromPosition(position);

	if(f_Grid != nullptr)
		{
		if(f_Grid->m_rebuild == 1)
			{
			return false;
			}

		float f_Xclip_FLT = (position.m_X / BLOCK_RENDER);
		float f_Yclip_FLT = (position.m_Y / BLOCK_RENDER);
		float f_Zclip_FLT = (position.m_Z / BLOCK_RENDER);

		float f_Full_X = 0;
		float f_Fract_X = modf(f_Xclip_FLT, &f_Full_X);

		float f_Full_Y = 0;
		float f_Fract_Y = modf(f_Yclip_FLT, &f_Full_Y);

		float f_Full_Z = 0;
		float f_Fract_Z = modf(f_Zclip_FLT, &f_Full_Z);

		int f_Xclip = f_Full_X;
		int f_Yclip = f_Full_Y;
		int f_Zclip = f_Full_Z;

		if (f_Fract_X < 0.0f)
			f_Xclip -= 1;
		if (f_Fract_Y < 0.0f)
			f_Yclip -= 1;
		if (f_Fract_Z < 0.0f)
			f_Zclip -= 1;

		int f_Local_X = f_Xclip - f_Grid->m_Xpos;
		int f_Local_Y = f_Yclip - f_Grid->m_Ypos;
		int f_Local_Z = f_Zclip - f_Grid->m_Zpos;

		if ((f_Local_X < 0) || (f_Local_X >= VoxelGrid::VOXEL_GRID_SIZE) ||
			(f_Local_Y < 0) || (f_Local_Y >= VoxelGrid::VOXEL_GRID_SIZE) ||
			(f_Local_Z < 0) || (f_Local_Z >= VoxelGrid::VOXEL_GRID_SIZE))
			{
			return false;
			}

		// Set result grid
		*(f_ResultGrid) = f_Grid;

		std::shared_ptr<VoxelLimb> f_In_Limb = f_Grid->OnVoxelLimb(f_Local_X, f_Local_Y, f_Local_Z);

		bool f_inActive = false;

		if(f_In_Limb != nullptr)
			{
			f_inActive = f_In_Limb->m_VX_Core->GetActive(f_Local_X, f_Local_Y, f_Local_Z);

			unsigned int colour = f_In_Limb->m_VX_Core->m_colour[f_Local_X + f_Local_Y * VoxelGrid::VOXEL_GRID_SIZE + f_Local_Z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];

			unsigned int alpha = (colour & 0xFF000000) >> 24;

			if(alpha > 0)
				{
				*(f_ResultX) = f_Local_X;
				*(f_ResultY) = f_Local_Y;
				*(f_ResultZ) = f_Local_Z;

				return true;
				}
			}
		else
			{
			f_inActive = f_Grid->m_VX_Core->GetActive(f_Local_X, f_Local_Y, f_Local_Z);

			unsigned int colour = f_Grid->m_VX_Core->m_colour[f_Local_X + f_Local_Y * VoxelGrid::VOXEL_GRID_SIZE + f_Local_Z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];

			unsigned int alpha = (colour & 0xFF000000) >> 24;

			if(alpha > 0)
				{
				*(f_ResultX) = f_Local_X;
				*(f_ResultY) = f_Local_Y;
				*(f_ResultZ) = f_Local_Z;

				return true;
				}
			}
		}

	return false;
}

float VoxelGrid::GetStrength(int x, int y, int z)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return 0.0f;
		}

	return m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];
}

float VoxelGridCore::GetStrength(int x, int y, int z)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return 0.0f;
		}

	return m_blockStrength[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

void VoxelGrid::GetColour(int x, int y, int z, float* r, float* g, float* b, float* a)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	unsigned int colour = m_VX_Core->m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];
	unsigned int alpha = (colour & 0xFF000000) >> 24;
	unsigned int blue = (colour & 0x00FF0000) >> 16;
	unsigned int green = (colour & 0x0000FF00) >> 8;
	unsigned int red = (colour & 0x000000FF);

	*r = (float)(red / 255.0f);
	*g = (float)(green / 255.0f);
	*b = (float)(blue / 255.0f);
	*a = 1.0f;
}

void VoxelGridCore::GetColour(int x, int y, int z, float* r, float* g, float* b, float* a)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	unsigned int colour = m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];

	unsigned int alpha = (colour & 0xFF000000) >> 24;
	unsigned int blue = (colour & 0x00FF0000) >> 16;
	unsigned int green = (colour & 0x0000FF00) >> 8;
	unsigned int red = (colour & 0x000000FF);

	*r = (float)(red / 255.0f);
	*g = (float)(green / 255.0f);
	*b = (float)(blue / 255.0f);
	*a = 1.0f;
}

// Block colour
void VoxelGrid::SetColour(int x, int y, int z, float r, float g, float b, float a, bool setBlockType)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;
	if (r < 0.0f) r = 0.0f;
	if (g < 0.0f) g = 0.0f;
	if (b < 0.0f) b = 0.0f;

	unsigned int alpha = (int)(a * 255) << 24;
	unsigned int blue = (int)(b * 255) << 16;
	unsigned int green = (int)(g * 255) << 8;
	unsigned int red = (int)(r * 255);

	unsigned int colour = red + green + blue + alpha;

	SetColour(x, y, z, colour, setBlockType);
}

void VoxelGrid::SetColour(int x, int y, int z, unsigned int colour, bool setBlockType)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	bool changed = ((m_VX_Core->m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] == colour) == false);

	if(changed)
		{
		m_VoxelGridChangedDuringBatchUpdate = true;
		}

	m_VX_Core->m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = colour;

	if(setBlockType)
		{
		m_VX_Core->m_blockType[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = BlockType_Default;
		}
}

void VoxelGrid::SetColourType(int x, int y, int z, float r, float g, float b, float a, BlockType f_BlockType)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	if(r > 1.0f) r = 1.0f;
	if(g > 1.0f) g = 1.0f;
	if(b > 1.0f) b = 1.0f;
	if(r < 0.0f) r = 0.0f;
	if(g < 0.0f) g = 0.0f;
	if(b < 0.0f) b = 0.0f;

	unsigned int alpha = (int)(a * 255) << 24;
	unsigned int blue = (int)(b * 255) << 16;
	unsigned int green = (int)(g * 255) << 8;
	unsigned int red = (int)(r * 255);

	unsigned int colour = red + green + blue + alpha;

	SetColourType(x, y, z, colour, f_BlockType);
}

void VoxelGridCore::SetColourType(int x, int y, int z, float r, float g, float b, float a, BlockType f_BlockType)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	if(r > 1.0f) r = 1.0f;
	if(g > 1.0f) g = 1.0f;
	if(b > 1.0f) b = 1.0f;
	if(r < 0.0f) r = 0.0f;
	if(g < 0.0f) g = 0.0f;
	if(b < 0.0f) b = 0.0f;

	unsigned int alpha = (int)(a * 255) << 24;
	unsigned int blue = (int)(b * 255) << 16;
	unsigned int green = (int)(g * 255) << 8;
	unsigned int red = (int)(r * 255);

	unsigned int colour = red + green + blue + alpha;

	SetColourType(x, y, z, colour, f_BlockType);
}

void VoxelGridCore::SetColour(int x, int y, int z, float r, float g, float b, float a)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	if(r > 1.0f) r = 1.0f;
	if(g > 1.0f) g = 1.0f;
	if(b > 1.0f) b = 1.0f;
	if(r < 0.0f) r = 0.0f;
	if(g < 0.0f) g = 0.0f;
	if(b < 0.0f) b = 0.0f;

	unsigned int alpha = (int)(a * 255) << 24;
	unsigned int blue = (int)(b * 255) << 16;
	unsigned int green = (int)(g * 255) << 8;
	unsigned int red = (int)(r * 255);

	unsigned int colour = red + green + blue + alpha;

	SetColour(x, y, z, colour);
}

void VoxelGridCore::SetColour(int x, int y, int z, unsigned int colour)
{
	//Set Colour Absolutely
	m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED] = colour;
}

void VoxelGrid::SetColourType(int x, int y, int z, unsigned int colour, BlockType f_BlockType)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	int index = x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED;

	bool changed = ((m_VX_Core->m_colour[index] == colour) == false);

	if(changed)
		{
		m_VoxelGridChangedDuringBatchUpdate = true;
		}

	m_VX_Core->m_colour[index] = colour;
	m_VX_Core->m_blockType[index] = BlockType_Default;
	m_VX_Core->m_blockStrength[index] = ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Strength);
}

void VoxelGridCore::SetColourType(int x, int y, int z, unsigned int colour, BlockType f_BlockType)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	int index = x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED;

	m_colour[index] = colour;
	m_blockType[index] = BlockType_Default;
	m_blockStrength[index] = ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Strength);
}

void VoxelGrid::SetStrength(int x, int y, int z, float f_Strength)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	m_VX_Core->m_blockStrength[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED] = f_Strength;
}

void VoxelGridCore::SetStrength(int x, int y, int z, float f_Strength)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	m_blockStrength[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED] = f_Strength;
}

unsigned int VoxelGrid::GetColour(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		return 0;

	return m_VX_Core->m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

unsigned int VoxelGridCore::GetColour(int x, int y, int z)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return 0;
		}

	return m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

// Block type
void VoxelGrid::SetBlockType(int x, int y, int z, BlockType blockType)
{
	if((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
	   (z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		{
		return;
		}

	m_VX_Core->m_blockType[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED] = blockType;
}

unsigned int VoxelGrid::AddVertexToMesh(BiVector p1, BiVector n1, float r, float g, float b, float a)
{
	  //////////////////
	 // m_vec Mesh
	//
	m_vec_Vertex.push_back(std::make_shared<BiVector>(p1.m_X, p1.m_Y, (p1.m_Z * -1)));
	m_vec_Normal.push_back(std::make_shared<BiVector>(n1.m_X, n1.m_Y, n1.m_Z));
	m_vec_Color.push_back(std::make_shared<BiColor>(r, g, b, a));

	return m_vec_Vertex.size() - 1;
}

unsigned int VoxelLimb::AddVertexToMesh(BiVector p1, BiVector n1, float r, float g, float b, float a)
{
	  //////////////////
	 // m_vec Mesh
	//
	m_vec_Vertex.push_back(std::make_shared<BiVector>(p1.m_X, p1.m_Y, (p1.m_Z * -1)));
	m_vec_Normal.push_back(std::make_shared<BiVector>(n1.m_X, n1.m_Y, n1.m_Z));
	m_vec_Color.push_back(std::make_shared<BiColor>(r, g, b, a));

	return m_vec_Vertex.size() - 1;
}

unsigned int VoxelGrid::AddTextureCoordinatesToMesh(float u, float v)
{
	m_vec_Tex.push_back(std::make_shared<BiTex>(u, v));

	return m_vec_Tex.size() - 1;
}

unsigned int VoxelLimb::AddTextureCoordinatesToMesh(float u, float v)
{
	m_vec_Tex.push_back(std::make_shared<BiTex>(u, v));

	return m_vec_Tex.size() - 1;
}

void VoxelGrid::AddTriangleToMesh(unsigned int v1, unsigned int v2, unsigned int v3)
{
	std::shared_ptr<Index> f_Index = std::make_shared<Index>();

	f_Index->m_A = v1;
	f_Index->m_B = v2;
	f_Index->m_C = v3;

	m_vec_Index.push_back(f_Index);
}

void VoxelLimb::AddTriangleToMesh(unsigned int v1, unsigned int v2, unsigned int v3)
{
	std::shared_ptr<Index> f_Index = std::make_shared<Index>();

	f_Index->m_A = v1;
	f_Index->m_B = v2;
	f_Index->m_C = v3;

	m_vec_Index.push_back(f_Index);
}

void VoxelGrid::GenerateBuffers(void)
{
	const unsigned int f_VertNom = m_vec_Vertex.size() * 3;
	const unsigned int f_ColorNom = m_vec_Color.size() * 4;
	const unsigned int f_UVNom = m_vec_Tex.size() * 2;
	const unsigned int f_IndexNom = m_vec_Index.size() * 3;

	GLfloat* f_Position = new GLfloat[f_VertNom];
	GLfloat* f_Normal = new GLfloat[f_VertNom];
	GLfloat* f_Color = new GLfloat[f_ColorNom];
	GLfloat* f_Tex = new GLfloat[f_UVNom];
	short* f_Index = new short[f_IndexNom];
	
	for(unsigned int f_VertexCount = 0; f_VertexCount < m_vec_Vertex.size(); f_VertexCount++)
		{
		f_Position[(f_VertexCount * 3)] = m_vec_Vertex[f_VertexCount]->m_X;
		f_Position[(f_VertexCount * 3) + 1] = m_vec_Vertex[f_VertexCount]->m_Y;
		f_Position[(f_VertexCount * 3) + 2] = m_vec_Vertex[f_VertexCount]->m_Z;
		}

	for(unsigned int f_NormalCount = 0; f_NormalCount < m_vec_Normal.size(); f_NormalCount++)
		{
		f_Normal[(f_NormalCount * 3)] = m_vec_Normal[f_NormalCount]->m_X;
		f_Normal[(f_NormalCount * 3) + 1] = m_vec_Normal[f_NormalCount]->m_Y;
		f_Normal[(f_NormalCount * 3) + 2] = m_vec_Normal[f_NormalCount]->m_Z;
		}

	for(unsigned int f_ColorCount = 0; f_ColorCount < m_vec_Color.size(); f_ColorCount++)
		{
		f_Color[(f_ColorCount * 4)] = m_vec_Color[f_ColorCount]->m_R;
		f_Color[(f_ColorCount * 4) + 1] = m_vec_Color[f_ColorCount]->m_G;
		f_Color[(f_ColorCount * 4) + 2] = m_vec_Color[f_ColorCount]->m_B;
		f_Color[(f_ColorCount * 4) + 3] = m_vec_Color[f_ColorCount]->m_A;
		}

	for(unsigned int f_TexCount = 0; f_TexCount < m_vec_Tex.size(); f_TexCount++)
		{
		f_Tex[(f_TexCount * 2)] = m_vec_Tex[f_TexCount]->m_U;
		f_Tex[(f_TexCount * 2) + 1] = m_vec_Tex[f_TexCount]->m_V;
		}

	for(unsigned int f_IndexCount = 0; f_IndexCount < m_vec_Index.size(); f_IndexCount++)
		{
		f_Index[(f_IndexCount * 3)] = m_vec_Index[f_IndexCount]->m_A;
		f_Index[(f_IndexCount * 3) + 1] = m_vec_Index[f_IndexCount]->m_B;
		f_Index[(f_IndexCount * 3) + 2] = m_vec_Index[f_IndexCount]->m_C;
		}

	g_VoxelGridManager->m_OGL_Mutex.lock();

	if(m_ReserveReady == true)
		{
		glGenBuffers(1, &mresVertexPositionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexPositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Position, GL_STATIC_DRAW);

		glGenBuffers(1, &mresVertexNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

		glGenBuffers(1, &mresVertexColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

		glGenBuffers(1, &mresVertexTexCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexTexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);

		glGenBuffers(1, &mresIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mresIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_IndexNom, f_Index, GL_STATIC_DRAW);
		}
	else
		{
		glGenBuffers(1, &mVertexPositionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Position, GL_STATIC_DRAW);

		glGenBuffers(1, &mVertexNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

		glGenBuffers(1, &mVertexColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

		glGenBuffers(1, &mVertexTexCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);

		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_IndexNom, f_Index, GL_STATIC_DRAW);

		m_FaceCount = m_vec_Index.size() * 3;
		}

	g_VoxelGridManager->m_OGL_Mutex.unlock();
}

void VoxelLimb::GenerateBuffers(void)
{
	const unsigned int f_VertNom = m_vec_Vertex.size() * 3;
	const unsigned int f_ColorNom = m_vec_Color.size() * 4;
	const unsigned int f_UVNom = m_vec_Tex.size() * 2;
	const unsigned int f_IndexNom = m_vec_Index.size() * 3;

	GLfloat* f_Position = new GLfloat[f_VertNom];
	GLfloat* f_Normal = new GLfloat[f_VertNom];
	GLfloat* f_Color = new GLfloat[f_ColorNom];
	GLfloat* f_Tex = new GLfloat[f_UVNom];
	short* f_Index = new short[f_IndexNom];
	
	for(unsigned int f_VertexCount = 0; f_VertexCount < m_vec_Vertex.size(); f_VertexCount++)
		{
		f_Position[(f_VertexCount * 3)] = m_vec_Vertex[f_VertexCount]->m_X;
		f_Position[(f_VertexCount * 3) + 1] = m_vec_Vertex[f_VertexCount]->m_Y;
		f_Position[(f_VertexCount * 3) + 2] = m_vec_Vertex[f_VertexCount]->m_Z;
		}

	for(unsigned int f_NormalCount = 0; f_NormalCount < m_vec_Normal.size(); f_NormalCount++)
		{
		f_Normal[(f_NormalCount * 3)] = m_vec_Normal[f_NormalCount]->m_X;
		f_Normal[(f_NormalCount * 3) + 1] = m_vec_Normal[f_NormalCount]->m_Y;
		f_Normal[(f_NormalCount * 3) + 2] = m_vec_Normal[f_NormalCount]->m_Z;
		}

	for(unsigned int f_ColorCount = 0; f_ColorCount < m_vec_Color.size(); f_ColorCount++)
		{
		f_Color[(f_ColorCount * 4)] = m_vec_Color[f_ColorCount]->m_R;
		f_Color[(f_ColorCount * 4) + 1] = m_vec_Color[f_ColorCount]->m_G;
		f_Color[(f_ColorCount * 4) + 2] = m_vec_Color[f_ColorCount]->m_B;
		f_Color[(f_ColorCount * 4) + 3] = m_vec_Color[f_ColorCount]->m_A;
		}

	for(unsigned int f_TexCount = 0; f_TexCount < m_vec_Tex.size(); f_TexCount++)
		{
		f_Tex[(f_TexCount * 2)] = m_vec_Tex[f_TexCount]->m_U;
		f_Tex[(f_TexCount * 2) + 1] = m_vec_Tex[f_TexCount]->m_V;
		}

	for(unsigned int f_IndexCount = 0; f_IndexCount < m_vec_Index.size(); f_IndexCount++)
		{
		f_Index[(f_IndexCount * 3)] = m_vec_Index[f_IndexCount]->m_A;
		f_Index[(f_IndexCount * 3) + 1] = m_vec_Index[f_IndexCount]->m_B;
		f_Index[(f_IndexCount * 3) + 2] = m_vec_Index[f_IndexCount]->m_C;
		}

	g_VoxelGridManager->m_OGL_Mutex.lock();

	if(m_ReserveReady == true)
		{
		glGenBuffers(1, &mresVertexPositionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexPositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Position, GL_STATIC_DRAW);

		glGenBuffers(1, &mresVertexNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

		glGenBuffers(1, &mresVertexColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

		glGenBuffers(1, &mresVertexTexCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mresVertexTexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);

		glGenBuffers(1, &mresIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mresIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_IndexNom, f_Index, GL_STATIC_DRAW);
		}
	else
		{
		glGenBuffers(1, &mVertexPositionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Position, GL_STATIC_DRAW);

		glGenBuffers(1, &mVertexNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

		glGenBuffers(1, &mVertexColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

		glGenBuffers(1, &mVertexTexCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);

		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_IndexNom, f_Index, GL_STATIC_DRAW);

		m_FaceCount = m_vec_Index.size() * 3;
		}

	g_VoxelGridManager->m_OGL_Mutex.unlock();
}

void VoxelGrid::GenerateBuffersColour(void)
{
	const unsigned int f_ColorNom = m_vec_Color.size() * 4;
	GLfloat* f_Color = new GLfloat[f_ColorNom];

	for(unsigned int f_ColorCount = 0; f_ColorCount < m_vec_Color.size(); f_ColorCount++)
		{
		f_Color[(f_ColorCount * 4)] = m_vec_Color[f_ColorCount]->m_R;
		f_Color[(f_ColorCount * 4) + 1] = m_vec_Color[f_ColorCount]->m_G;
		f_Color[(f_ColorCount * 4) + 2] = m_vec_Color[f_ColorCount]->m_B;
		f_Color[(f_ColorCount * 4) + 3] = m_vec_Color[f_ColorCount]->m_A;
		}

	g_VoxelGridManager->m_OGL_Mutex.lock();

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

	g_VoxelGridManager->m_OGL_Mutex.unlock();
}

	// Create mesh
void VoxelGrid::CreateMesh(void)
{
    if(mVertexPositionBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexPositionBuffer);
        mVertexPositionBuffer = 0;
		}

    if(mVertexColorBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexColorBuffer);
        mVertexColorBuffer = 0;
		}

	if(mVertexTexCoordBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexTexCoordBuffer);
		mVertexTexCoordBuffer = 0;
		}

    if(mIndexBuffer != 0)
		{
        glDeleteBuffers(1, &mIndexBuffer);
        mIndexBuffer = 0;
		}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	int *l_merged;
	l_merged = new int[VOXEL_GRID_SIZE_CUBED];

	for (unsigned int j = 0; j < VOXEL_GRID_SIZE_CUBED; j++)
		{
		l_merged[j] = MergedSide_None;
		}

	for (int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for (int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for (int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				if (GetActive_Limbless(x, y, z) == false)
					{
					continue;
					}
				else
					{
					GetColour(x, y, z, &r, &g, &b, &a);

					a = 1.0f;

					BiVector p1(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p2(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p3(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p4(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					BiVector p5(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					BiVector p6(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					BiVector p7(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					BiVector p8(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					BiVector n1;
					unsigned int v1, v2, v3, v4;
					unsigned int t1, t2, t3, t4;

					bool doXPositive = (IsMergedXPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doXNegative = (IsMergedXNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doYPositive = (IsMergedYPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doYNegative = (IsMergedYNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doZPositive = (IsMergedZPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doZNegative = (IsMergedZNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);

					// Front
					if (doZPositive && ((z == VOXEL_GRID_SIZE - 1) || z < VOXEL_GRID_SIZE - 1 && GetActive_Limbless(x, y, z + 1) == false))
						{
						bool addSide = true;

						if ((z == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);

							if (pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive_Limbless(x, y, 0) == false);
								}
							}

						if (addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p1, &p2, &p3, &p4, x, y, endX, endY, true, true, false, false);

							n1 = BiVector(0.0f, 0.0f, 1.0f);
							v1 = AddVertexToMesh(p1, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p2, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p3, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p4, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Back
					if(doZNegative && ((z == 0) || (z > 0 && GetActive_Limbless(x, y, z - 1) == false)))
						{
						bool addSide = true;

						if((z == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);

							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive_Limbless(x, y, VOXEL_GRID_SIZE - 1) == false);
								}
							}

						if (addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p5, &p8, &p7, x, y, endX, endY, false, true, false, false);

							n1 = BiVector(0.0f, 0.0f, -1.0f);
							v1 = AddVertexToMesh(p5, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p6, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p7, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p8, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Right
					if(doXPositive && ((x == VOXEL_GRID_SIZE - 1) || (x < VOXEL_GRID_SIZE - 1 && GetActive_Limbless(x + 1, y, z) == false)))
						{
						bool addSide = true;

						if ((x == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);

							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive_Limbless(0, y, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p5, &p2, &p3, &p8, z, y, endX, endY, true, false, true, false);

							n1 = BiVector(1.0f, 0.0f, 0.0f);
							v1 = AddVertexToMesh(p2, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p3, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Left
					if(doXNegative && ((x == 0) || (x > 0 && GetActive_Limbless(x - 1, y, z) == false)))
						{
						bool addSide = true;

						if((x == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);

							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive_Limbless(VOXEL_GRID_SIZE - 1, y, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p1, &p4, &p7, z, y, endX, endY, false, false, true, false);

							n1 = BiVector(-1.0f, 0.0f, 0.0f);
							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p1, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p4, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Top
					if(doYPositive && ((y == VOXEL_GRID_SIZE - 1) || (y < VOXEL_GRID_SIZE - 1 && GetActive_Limbless(x, y + 1, z) == false)))
						{
						bool addSide = true;

						if((y == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);

							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive_Limbless(x, 0, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p7, &p8, &p3, &p4, x, z, endX, endY, true, false, false, true);

							n1 = BiVector(0.0f, 1.0f, 0.0f);
							v1 = AddVertexToMesh(p4, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p3, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}

					p1 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p2 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p3 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p4 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z + BLOCK_RENDER_SIZE);
					p5 = BiVector(x + BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p6 = BiVector(x - BLOCK_RENDER_SIZE, y - BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p7 = BiVector(x - BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);
					p8 = BiVector(x + BLOCK_RENDER_SIZE, y + BLOCK_RENDER_SIZE, z - BLOCK_RENDER_SIZE);

					// Bottom
					if(doYNegative && ((y == 0) || (y > 0 && GetActive_Limbless(x, y - 1, z) == false)))
						{
						bool addSide = true;

						if((y == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);

							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive_Limbless(x, VOXEL_GRID_SIZE - 1, z) == false);
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p5, &p2, &p1, x, z, endX, endY, false, false, false, true);

							n1 = BiVector(0.0f, -1.0f, 0.0f);
							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							v3 = AddVertexToMesh(p2, n1, r, g, b, a);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							v4 = AddVertexToMesh(p1, n1, r, g, b, a);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
							}
						}
					}
				}
			}
		}

	// Delete the merged array
	delete l_merged;
}

void VoxelGrid::CreateMeshCubeColour(void)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRIDSIZE = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

    if(mVertexColorBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexColorBuffer);
        mVertexColorBuffer = 0;
		}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
		{
		for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
			{
			for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
				{
				if(GetActive_Limbless(x, y, z) == false)
					{
					continue;
					}
				else
					{
					GetColour(x, y, z, &r, &g, &b, &a);
					a = 1.0f;

					BiVector n1;
					unsigned int v1, v2, v3, v4, v5, v6, v7, v8;
					unsigned int t1, t2, t3, t4;

					BiVector f_1((x * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) - BLOCK_RENDER_SIZE);
					BiVector f_2((x * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) + BLOCK_RENDER_SIZE);
					BiVector f_3((x * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) - BLOCK_RENDER_SIZE);
					BiVector f_4((x * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) + BLOCK_RENDER_SIZE);
					BiVector f_5((x * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) - BLOCK_RENDER_SIZE);
					BiVector f_6((x * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) - BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) + BLOCK_RENDER_SIZE);
					BiVector f_7((x * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) - BLOCK_RENDER_SIZE);
					BiVector f_8((x * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (y * BLOCK_RENDER) + BLOCK_RENDER_SIZE, (z * BLOCK_RENDER) + BLOCK_RENDER_SIZE);

					n1.m_X = -1.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = 0.0f;

					v1 = AddVertexToMesh(f_1, n1, r, g, b, a);
					v2 = AddVertexToMesh(f_2, n1, r, g, b, a);
					v3 = AddVertexToMesh(f_3, n1, r, g, b, a);
					v4 = AddVertexToMesh(f_4, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v1, v3, v2);
					AddTriangleToMesh(v2, v3, v4);

					n1.m_X = 1.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = 0.0f;

					v5 = AddVertexToMesh(f_5, n1, r, g, b, a);
					v6 = AddVertexToMesh(f_6, n1, r, g, b, a);
					v7 = AddVertexToMesh(f_7, n1, r, g, b, a);
					v8 = AddVertexToMesh(f_8, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v5, v6, v7);
					AddTriangleToMesh(v6, v8, v7);

					n1.m_X = 0.0f;
					n1.m_Y = -1.0f;
					n1.m_Z = 0.0f;

					v1 = AddVertexToMesh(f_1, n1, r, g, b, a);
					v2 = AddVertexToMesh(f_2, n1, r, g, b, a);
					v5 = AddVertexToMesh(f_5, n1, r, g, b, a);
					v6 = AddVertexToMesh(f_6, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v1, v2, v6);
					AddTriangleToMesh(v1, v6, v5);

					n1.m_X = 0.0f;
					n1.m_Y = 1.0f;
					n1.m_Z = 0.0f;

					v3 = AddVertexToMesh(f_3, n1, r, g, b, a);
					v4 = AddVertexToMesh(f_4, n1, r, g, b, a);
					v7 = AddVertexToMesh(f_7, n1, r, g, b, a);
					v8 = AddVertexToMesh(f_8, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v3, v7, v8);
					AddTriangleToMesh(v3, v8, v4);

					n1.m_X = 0.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = -1.0f;

					v1 = AddVertexToMesh(f_1, n1, r, g, b, a);
					v5 = AddVertexToMesh(f_5, n1, r, g, b, a);
					v7 = AddVertexToMesh(f_7, n1, r, g, b, a);
					v3 = AddVertexToMesh(f_3, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v1, v5, v7);
					AddTriangleToMesh(v1, v7, v3);

					n1.m_X = 0.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = 1.0f;

					v2 = AddVertexToMesh(f_2, n1, r, g, b, a);
					v4 = AddVertexToMesh(f_4, n1, r, g, b, a);
					v6 = AddVertexToMesh(f_6, n1, r, g, b, a);
					v8 = AddVertexToMesh(f_8, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v2, v4, v8);
					AddTriangleToMesh(v2, v8, v6);
					}
				}
			}
		}
}

std::string VoxelGrid::HashMeshColourCube(void)
{
	picosha2::hash256_one_by_one f_hasha;

	CubeHASH_originstring* f_HashPad = new CubeHASH_originstring();

	float* r = new float(0.0f);
	float* g = new float(0.0f);
	float* b = new float(0.0f);
	float* a = new float(0.0f);

	m_Hash.clear();

	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for(int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for(int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				bool f_Active = GetActive_Limbless(x, y, z);
				
				f_HashPad->acPushBool(f_Active);

				if(f_Active)
					{
					f_HashPad->acPushInt(x);
					f_HashPad->acPushInt(y);
					f_HashPad->acPushInt(z);

					m_VX_Core->GetColour(x, y, z, r, g, b, a);

					f_HashPad->acPushFloat(*(r));
					f_HashPad->acPushFloat(*(g));
					f_HashPad->acPushFloat(*(b));
					f_HashPad->acPushFloat(*(a));

					f_HashPad->acPushFloat(m_VX_Core->GetStrength(x, y, z));
					}
				}
			}
		}

	f_hasha.init(); //reset hasher state
	f_hasha.process(f_HashPad->m_str_Input.begin(), f_HashPad->m_str_Input.end());
	f_hasha.finish();
	picosha2::get_hash_hex_string(f_hasha, f_HashPad->m_OutputHash);

	m_Hash = f_HashPad->m_OutputHash;

	f_HashPad->acClear();

	delete f_HashPad;

	delete r;
	delete g;
	delete b;
	delete a;

	return m_Hash;
}

std::string VoxelLimb::HashMeshColourCube(void)
{
	picosha2::hash256_one_by_one f_hasha;

	CubeHASH_originstring* f_HashPad = new CubeHASH_originstring();

	float* r = new float(0.0f);
	float* g = new float(0.0f);
	float* b = new float(0.0f);
	float* a = new float(0.0f);

	m_Hash.clear();

	for(int x = m_MinX; x < m_MaxX; x++)
		{
		int Xbegin = (x - m_Xpos);

		for(int y = m_MinY; y < m_MaxY; y++)
			{
			int Ybegin = (y - m_Ypos);

			for(int z = m_MinZ; z < m_MaxZ; z++)
				{
				int Zbegin = (z - m_Zpos);

				if( (Xbegin >= 0) &&
					(Ybegin >= 0) &&
					(Zbegin >= 0) &&
					(Xbegin < VoxelGrid::VOXEL_GRID_SIZE) &&
					(Ybegin < VoxelGrid::VOXEL_GRID_SIZE) &&
					(Zbegin < VoxelGrid::VOXEL_GRID_SIZE))
					{
					bool f_Active = m_VX_Core->GetActive(Xbegin, Ybegin, Zbegin);
				
					f_HashPad->acPushBool(f_Active);

					if(f_Active == true)
						{
						f_HashPad->acPushInt(Xbegin);
						f_HashPad->acPushInt(Ybegin);
						f_HashPad->acPushInt(Zbegin);

						m_VX_Core->GetColour(Xbegin, Ybegin, Zbegin, r, g, b, a);

						f_HashPad->acPushFloat(*(r));
						f_HashPad->acPushFloat(*(g));
						f_HashPad->acPushFloat(*(b));
						f_HashPad->acPushFloat(*(a));

						f_HashPad->acPushFloat(m_VX_Core->GetStrength(Xbegin, Ybegin, Zbegin));
						}
					}
				}
			}
		}

	f_hasha.init(); //reset hasher state
	f_hasha.process(f_HashPad->m_str_Input.begin(), f_HashPad->m_str_Input.end());
	f_hasha.finish();
	picosha2::get_hash_hex_string(f_hasha, f_HashPad->m_OutputHash);

	m_Hash = f_HashPad->m_OutputHash;

	f_HashPad->acClear();

	delete f_HashPad;

	delete r;
	delete g;
	delete b;
	delete a;

	return m_Hash;
}

void VoxelGrid::CreateMeshCubeDetail(float f_Scale)
{
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	// parent
	if(m_ReserveReady == false)
		{
		if(m_isParent == true)
			{
			g_VoxelGridManager->m_OGL_Mutex.lock();

			if(mVertexPositionBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexPositionBuffer);

				mVertexPositionBuffer = 0;
				}

			if(mVertexColorBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexColorBuffer);

				mVertexColorBuffer = 0;
				}

			if(mVertexNormalBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexNormalBuffer);

				mVertexNormalBuffer = 0;
				}

			if(mVertexTexCoordBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexTexCoordBuffer);

				mVertexTexCoordBuffer = 0;
				}

			if(mIndexBuffer != 0)
				{
				glDeleteBuffers(1, &mIndexBuffer);

				mIndexBuffer = 0;
				}

			g_VoxelGridManager->m_OGL_Mutex.unlock();
			}
		}

	if(m_build_count == 0)
		{
		std::string f_HashStr = HashMeshColourCube();

		int f_ParentGridID = g_VoxelGridManager->acSearch_WithHash(f_HashStr);

		// detect 'child'
		if((f_ParentGridID >= 0) && (f_ParentGridID != m_ManagerIndex))
			{
			std::shared_ptr<VoxelGrid> f_VoxParent = g_VoxelGridManager->m_VoxelGridsVector[f_ParentGridID];

			f_VoxParent->m_isParent = true;

			m_Parent = f_VoxParent;

			f_VoxParent->m_Child.push_back(m_Self);

			m_isParent = false;
			}
		}

	// swift return
	if((m_isParent == false) || ((m_full == true) && (m_surroundedVoxelGrid == true)))
		{
		return;
		}

	// assume 'parent'
	m_isParent = true;

	int *l_merged;

	l_merged = new int[VOXEL_GRID_SIZE_CUBED];

	for(unsigned int j = 0; j < VOXEL_GRID_SIZE_CUBED; j++)
		{
		l_merged[j] = MergedSide_None;
		}

	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for(int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for(int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				if(GetActive_Limbless(x, y, z) == false)
					{
					continue;
					}
				else
					{
					GetColour(x, y, z, &r, &g, &b, &a);

					a = 1.0f;

					BiVector n1;

					unsigned int v1, v2, v3, v4;
					unsigned int t1, t2, t3, t4;

					BiVector p1((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE);
					BiVector p2((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE);
					BiVector p3((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE);
					BiVector p4((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE);
					BiVector p5((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE);
					BiVector p6((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE);
					BiVector p7((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE);
					BiVector p8((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + BLOCK_RENDER_SIZE, (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - BLOCK_RENDER_SIZE);

					bool doXPositive = (IsMergedXPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doXNegative = (IsMergedXNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doYPositive = (IsMergedYPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doYNegative = (IsMergedYNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doZPositive = (IsMergedZPositive(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);
					bool doZNegative = (IsMergedZNegative(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE) == false);

					// Front
					if(doZPositive && ((z == VOXEL_GRID_SIZE - 1) || ((z < VOXEL_GRID_SIZE - 1) && (GetActive_Limbless(x, y, z + 1) == false))))
						{
						bool addSide = true;

						if(z == VOXEL_GRID_SIZE - 1)
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);

							if(pVoxelGrid != nullptr)
								{
								if(pVoxelGrid->IsSetup() == true)
									{
									addSide = !(pVoxelGrid->GetActive_Limbless(x, y, 0));
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p1, &p2, &p3, &p4, x, y, endX, endY, true, true, false, false);

							n1.m_X = 0.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = 1.0f;

							v1 = AddVertexToMesh(p1, n1, r, g, b, a);
							v2 = AddVertexToMesh(p2, n1, r, g, b, a);
							v3 = AddVertexToMesh(p3, n1, r, g, b, a);
							v4 = AddVertexToMesh(p4, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					// Back
					if(doZNegative && ((z == 0) || ((z > 0) && (GetActive_Limbless(x, y, z - 1) == false))))
						{
						bool addSide = true;

						if((z == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);

							if(pVoxelGrid != nullptr)
								{
								if(pVoxelGrid->IsSetup() == true)
									{
									addSide = !(pVoxelGrid->GetActive_Limbless(x, y, VOXEL_GRID_SIZE - 1));
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p5, &p8, &p7, x, y, endX, endY, false, true, false, false);

							n1.m_X = 0.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = -1.0f;

							v1 = AddVertexToMesh(p5, n1, r, g, b, a);
							v2 = AddVertexToMesh(p6, n1, r, g, b, a);
							v3 = AddVertexToMesh(p7, n1, r, g, b, a);
							v4 = AddVertexToMesh(p8, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					// Right
					if(doXPositive && ((x == VOXEL_GRID_SIZE - 1) || ((x < VOXEL_GRID_SIZE - 1) && (GetActive_Limbless(x + 1, y, z) == false))))
						{
						bool addSide = true;

						if((x == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);

							if(pVoxelGrid != nullptr)
								{
								if(pVoxelGrid->IsSetup() == true)
									{
									addSide = !(pVoxelGrid->GetActive_Limbless(0, y, z));
									}
								}
							}

						if(addSide)
							{
							int endX = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p5, &p2, &p3, &p8, z, y, endX, endY, true, false, true, false);

							n1.m_X = 1.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p2, n1, r, g, b, a);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							v4 = AddVertexToMesh(p3, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					// Left
					if(doXNegative && ((x == 0) || ((x > 0) && (GetActive_Limbless(x - 1, y, z) == false))))
						{
						bool addSide = true;

						if((x == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);

							if(pVoxelGrid != nullptr)
								{
								if(pVoxelGrid->IsSetup() == true)
									{
									addSide = !(pVoxelGrid->GetActive_Limbless(VOXEL_GRID_SIZE - 1, y, z));
									}
								}
							}

						if(addSide)
							{
							int endX = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (y / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p1, &p4, &p7, z, y, endX, endY, false, false, true, false);

							n1.m_X = -1.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							v2 = AddVertexToMesh(p1, n1, r, g, b, a);
							v3 = AddVertexToMesh(p4, n1, r, g, b, a);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					// Top
					if(doYPositive && ((y == VOXEL_GRID_SIZE - 1) || ((y < VOXEL_GRID_SIZE - 1) && (GetActive_Limbless(x, y + 1, z) == false))))
						{
						bool addSide = true;

						if((y == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);

							if(pVoxelGrid != nullptr)
								{
								if(pVoxelGrid->IsSetup() == true)
									{
									addSide = !(pVoxelGrid->GetActive_Limbless(x, 0, z));
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p7, &p8, &p3, &p4, x, z, endX, endY, true, false, false, true);

							n1.m_X = 0.0f;
							n1.m_Y = 1.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p4, n1, r, g, b, a);
							v2 = AddVertexToMesh(p3, n1, r, g, b, a);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					// Bottom
					if(doYNegative && ((y == 0) || ((y > 0) && (GetActive_Limbless(x, y - 1, z) == false))))
						{
						bool addSide = true;

						if((y == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);

							if(pVoxelGrid != nullptr)
								{
								if(pVoxelGrid->IsSetup() == true)
									{
									addSide = !(pVoxelGrid->GetActive_Limbless(x, VOXEL_GRID_SIZE - 1, z));
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;
							int endY = (z / VOXEL_GRID_SIZE) * VOXEL_GRID_SIZE + VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VOXEL_GRID_SIZE, VOXEL_GRID_SIZE, &p6, &p5, &p2, &p1, x, z, endX, endY, false, false, false, true);

							n1.m_X = 0.0f;
							n1.m_Y = -1.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							v3 = AddVertexToMesh(p2, n1, r, g, b, a);
							v4 = AddVertexToMesh(p1, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}
					}
				}
			}
		}

	// Delete the merged array
	delete [] l_merged;
}

void VoxelLimb::CreateMeshCubeDetail(float f_Scale)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRIDSIZE = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	// parent
	if(m_ReserveReady == false)
		{
		if(m_isParent == true)
			{
			g_VoxelGridManager->m_OGL_Mutex.lock();

			if(mVertexPositionBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexPositionBuffer);

				mVertexPositionBuffer = 0;
				}

			if(mVertexColorBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexColorBuffer);

				mVertexColorBuffer = 0;
				}

			if(mVertexNormalBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexNormalBuffer);

				mVertexNormalBuffer = 0;
				}

			if(mVertexTexCoordBuffer != 0)
				{
				glDeleteBuffers(1, &mVertexTexCoordBuffer);

				mVertexTexCoordBuffer = 0;
				}

			if(mIndexBuffer != 0)
				{
				glDeleteBuffers(1, &mIndexBuffer);

				mIndexBuffer = 0;
				}

			g_VoxelGridManager->m_OGL_Mutex.unlock();
			}
		}

	if(m_build_count == 0)
		{
		std::string f_HashStr = HashMeshColourCube();

		int f_ParentLimbID = m_GridRef->acSearch_WithHash_Limb(f_HashStr);

		// detect 'child'
		if((f_ParentLimbID >= 0) && (f_ParentLimbID != m_ManagerIndex))
			{
			std::shared_ptr<VoxelLimb> f_LimbParent = g_VoxelGridManager->m_VoxelLimbVector[f_ParentLimbID];

			char* f_alphaSig = ag_ClearChar(100);

			sprintf(f_alphaSig, "Limb %i as Child of %i", m_ManagerIndex, f_ParentLimbID);

			m_Hash = f_alphaSig;

			f_LimbParent->m_isParent = true;

			m_Parent = f_LimbParent;
			 
			f_LimbParent->m_Child.push_back(m_Self);

			m_isParent = false;
			}
		}

	// swift return
	if((m_isParent == false)/* || (m_full == true)*/)
		{
		return;
		}

	// assume 'parent'
	m_isParent = true;

	int *l_merged;

	l_merged = new int[VoxelGrid::VOXEL_GRID_SIZE_CUBED];

	for(unsigned int j = 0; j < VoxelGrid::VOXEL_GRID_SIZE_CUBED; j++)
		{
		l_merged[j] = MergedSide_None;
		}

	for(int vx = m_MinX; vx < m_MaxX; vx++)
		{
		int x = (vx - m_Xpos);

		for(int vy = m_MinY; vy < m_MaxY; vy++)
			{
			int y = (vy - m_Ypos);

			for(int vz = m_MinZ; vz < m_MaxZ; vz++)
				{
				int z = (vz - m_Zpos);

				if(m_VX_Core->GetActive(x, y, z) == false)
					{
					continue;
					}
				else
					{
					m_VX_Core->GetColour(x, y, z, &r, &g, &b, &a);

					a = 1.0f;

					BiVector n1;

					unsigned int v1, v2, v3, v4;
					unsigned int t1, t2, t3, t4;

					BiVector p1((x * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE);
					BiVector p2((x * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE);
					BiVector p3((x * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE);
					BiVector p4((x * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE);
					BiVector p5((x * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE);
					BiVector p6((x * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE);
					BiVector p7((x * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE);
					BiVector p8((x * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER * f_Scale)) + VoxelGrid::BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER * f_Scale)) - VoxelGrid::BLOCK_RENDER_SIZE);

					bool doXPositive = (IsMergedXPositive(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE) == false);
					bool doXNegative = (IsMergedXNegative(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE) == false);
					bool doYPositive = (IsMergedYPositive(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE) == false);
					bool doYNegative = (IsMergedYNegative(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE) == false);
					bool doZPositive = (IsMergedZPositive(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE) == false);
					bool doZNegative = (IsMergedZNegative(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE) == false);

					std::shared_ptr<VoxelLimb> f_In_Zpos_Limb = m_GridRef->OnVoxelLimb(x, y, z + 1);

					bool f_ZinActive = false;

					if(f_In_Zpos_Limb != nullptr)
						{
						f_ZinActive = f_In_Zpos_Limb->m_VX_Core->GetActive(x, y, z + 1);
						}

					// Front
					if(doZPositive && ((z == VoxelGrid::VOXEL_GRID_SIZE - 1) || ((z < VoxelGrid::VOXEL_GRID_SIZE - 1) && (f_ZinActive == false)) || (z == m_MaxZ - 1)))
						{
						bool addSide = true;

						if(z <= m_MaxZ - 1)
							{
							if(z == (VoxelGrid::VOXEL_GRID_SIZE - 1))
								{
								std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);

								if(pVoxelGrid != nullptr)
									{
									if(pVoxelGrid->IsSetup() == true)
										{
										std::shared_ptr<VoxelVector> f_In_Zneg_VoxVector = std::make_shared<VoxelVector>(x, y, 0);

										std::shared_ptr<VoxelLimb> f_In_Zneg_Limb = pVoxelGrid->OnVoxelLimb(f_In_Zneg_VoxVector);

										if(f_In_Zneg_Limb != nullptr)
											{
											addSide = !(f_In_Zneg_Limb->m_VX_Core->GetActive(x, y, 0));
											}
										}
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;
							int endY = (y / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE, &p1, &p2, &p3, &p4, x, y, endX, endY, true, true, false, false);

							n1.m_X = 0.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = 1.0f;

							v1 = AddVertexToMesh(p1, n1, r, g, b, a);
							v2 = AddVertexToMesh(p2, n1, r, g, b, a);
							v3 = AddVertexToMesh(p3, n1, r, g, b, a);
							v4 = AddVertexToMesh(p4, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					std::shared_ptr<VoxelLimb> f_Out_Zneg_Limb = m_GridRef->OnVoxelLimb(x, y, z - 1);

					bool f_ZoutActive = false;

					if(f_Out_Zneg_Limb != nullptr)
						{
						f_ZoutActive = f_Out_Zneg_Limb->m_VX_Core->GetActive(x, y, z - 1);
						}

					// Back
					if(doZNegative && ((z == 0) || ((z > 0) && (f_ZoutActive == false)) || (z == m_MinZ)))
						{
						bool addSide = true;

						if(z > m_MinZ)
							{
							if(z == 0)
								{
								std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);

								if(pVoxelGrid != nullptr)
									{
									if(pVoxelGrid->IsSetup() == true)
										{
										std::shared_ptr<VoxelVector> f_In_Zneg_VoxVector = std::make_shared<VoxelVector>(x, y, 0);

										std::shared_ptr<VoxelLimb> f_In_Zneg_Limb = pVoxelGrid->OnVoxelLimb(f_In_Zneg_VoxVector);

										if(f_In_Zneg_Limb != nullptr)
											{
											addSide = !(f_In_Zneg_Limb->m_VX_Core->GetActive(x, y, VoxelGrid::VOXEL_GRID_SIZE - 1));
											}
										}
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;
							int endY = (y / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE, &p6, &p5, &p8, &p7, x, y, endX, endY, false, true, false, false);

							n1.m_X = 0.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = -1.0f;

							v1 = AddVertexToMesh(p5, n1, r, g, b, a);
							v2 = AddVertexToMesh(p6, n1, r, g, b, a);
							v3 = AddVertexToMesh(p7, n1, r, g, b, a);
							v4 = AddVertexToMesh(p8, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					std::shared_ptr<VoxelLimb> f_Xpos_Limb = m_GridRef->OnVoxelLimb(x + 1, y, z);

					bool f_XposActive = false;

					if(f_Xpos_Limb != nullptr)
						{
						f_XposActive = f_Xpos_Limb->m_VX_Core->GetActive(x + 1, y, z);
						}

					// Right
					if(doXPositive && ((x == VoxelGrid::VOXEL_GRID_SIZE - 1) || (x < VoxelGrid::VOXEL_GRID_SIZE - 1 && f_XposActive == false) || (x == m_MaxX - 1)))
						{
						bool addSide = true;

						if(x < m_MaxX - 1)
							{
							if((x == VoxelGrid::VOXEL_GRID_SIZE - 1))
								{
								std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);

								if(pVoxelGrid != nullptr)
									{
									if(pVoxelGrid->IsSetup() == true)
										{
										std::shared_ptr<VoxelVector> f_Xpos_VoxVector = std::make_shared<VoxelVector>(x, y, 0);

										std::shared_ptr<VoxelLimb> f_Right_Xpos_Limb = pVoxelGrid->OnVoxelLimb(f_Xpos_VoxVector);

										if(f_Right_Xpos_Limb != nullptr)
											{
											addSide = f_Right_Xpos_Limb->m_VX_Core->GetActive(0, y, z);
											}
										}
									}
								}
							}

						if(addSide)
							{
							int endX = (z / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;
							int endY = (y / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE, &p5, &p2, &p3, &p8, z, y, endX, endY, true, false, true, false);

							n1.m_X = 1.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p2, n1, r, g, b, a);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							v4 = AddVertexToMesh(p3, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					std::shared_ptr<VoxelLimb> f_Xneg_Limb = m_GridRef->OnVoxelLimb(x - 1, y, z);

					bool f_XnegActive = false;

					if(f_Xneg_Limb != nullptr)
						{
						f_XnegActive = f_Xneg_Limb->m_VX_Core->GetActive(x - 1, y, z);
						}

					// Left
					if(doXNegative && ((x == 0) || ((x > 0) && (f_XnegActive == false)) || (x == m_MinX)))
						{
						bool addSide = true;

						if(x > m_MinX)
							{
							if((x == 0))
								{
								std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);

								if(pVoxelGrid != nullptr)
									{
									if(pVoxelGrid->IsSetup() == true)
										{
										std::shared_ptr<VoxelVector> f_Xneg_VoxVector = std::make_shared<VoxelVector>(VoxelGrid::VOXEL_GRID_SIZE - 1, y, z);

										std::shared_ptr<VoxelLimb> f_Left_Xneg_Limb = pVoxelGrid->OnVoxelLimb(f_Xneg_VoxVector);

										if(f_Left_Xneg_Limb != nullptr)
											{
											addSide = f_Left_Xneg_Limb->m_VX_Core->GetActive(VoxelGrid::VOXEL_GRID_SIZE - 1, y, z);
											}
										}
									}
								}
							}

						if(addSide)
							{
							int endX = (z / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;
							int endY = (y / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE, &p6, &p1, &p4, &p7, z, y, endX, endY, false, false, true, false);

							n1.m_X = -1.0f;
							n1.m_Y = 0.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							v2 = AddVertexToMesh(p1, n1, r, g, b, a);
							v3 = AddVertexToMesh(p4, n1, r, g, b, a);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					std::shared_ptr<VoxelLimb> f_Ypos_Limb = m_GridRef->OnVoxelLimb(x, y + 1, z);

					bool f_YposActive = false;

					if(f_Ypos_Limb != nullptr)
						{
						f_YposActive = f_Ypos_Limb->m_VX_Core->GetActive(x, y + 1, z);
						}

					// Top
					if(doYPositive && ((y == VoxelGrid::VOXEL_GRID_SIZE - 1) || ((y < VoxelGrid::VOXEL_GRID_SIZE - 1) && (f_YposActive == false)) || (y == m_MaxY)))
						{
						bool addSide = true;

						if((y < m_MaxY - 1))
							{
							if((y == VoxelGrid::VOXEL_GRID_SIZE - 1))
								{
								std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);

								if(pVoxelGrid != nullptr)
									{
									if(pVoxelGrid->IsSetup() == true)
										{
										std::shared_ptr<VoxelVector> f_Ypos_VoxVector = std::make_shared<VoxelVector>(x, 0, z);

										std::shared_ptr<VoxelLimb> f_Up_Ypos_Limb = pVoxelGrid->OnVoxelLimb(f_Ypos_VoxVector);

										if(f_Up_Ypos_Limb != nullptr)
											{
											addSide = f_Up_Ypos_Limb->m_VX_Core->GetActive(x, 0, z);
											}
										}
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;
							int endY = (z / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE, &p7, &p8, &p3, &p4, x, z, endX, endY, true, false, false, true);

							n1.m_X = 0.0f;
							n1.m_Y = 1.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p4, n1, r, g, b, a);
							v2 = AddVertexToMesh(p3, n1, r, g, b, a);
							v3 = AddVertexToMesh(p8, n1, r, g, b, a);
							v4 = AddVertexToMesh(p7, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}

					std::shared_ptr<VoxelLimb> f_Yneg_Limb = m_GridRef->OnVoxelLimb(x, y - 1, z);

					bool f_YnegActive = false;

					if(f_Yneg_Limb != nullptr)
						{
						f_YnegActive = f_Yneg_Limb->m_VX_Core->GetActive(x, y - 1, z);
						}

					// Bottom
					if(doYNegative && ((y == 0) || (y > 0 && f_YnegActive == false) || (y == m_MinY)))
						{
						bool addSide = true;

						if((y > m_MinY))
							{
							if((y == 0))
								{
								std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);

								if(pVoxelGrid != nullptr)
									{
									if(pVoxelGrid->IsSetup() == true)
										{
										std::shared_ptr<VoxelVector> f_Yneg_VoxVector = std::make_shared<VoxelVector>(x, VoxelGrid::VOXEL_GRID_SIZE - 1, z);

										std::shared_ptr<VoxelLimb> f_Bottom_Yneg_Limb = pVoxelGrid->OnVoxelLimb(f_Yneg_VoxVector);

										if(f_Bottom_Yneg_Limb != nullptr)
											{
											addSide = f_Bottom_Yneg_Limb->m_VX_Core->GetActive(x, VoxelGrid::VOXEL_GRID_SIZE - 1, z);
											}
										}
									}
								}
							}

						if(addSide)
							{
							int endX = (x / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;
							int endY = (z / VoxelGrid::VOXEL_GRID_SIZE) * VoxelGrid::VOXEL_GRID_SIZE + VoxelGrid::VOXEL_GRID_SIZE;

							UpdateMergedSide(l_merged, x, y, z, VoxelGrid::VOXEL_GRID_SIZE, VoxelGrid::VOXEL_GRID_SIZE, &p6, &p5, &p2, &p1, x, z, endX, endY, false, false, false, true);

							n1.m_X = 0.0f;
							n1.m_Y = -1.0f;
							n1.m_Z = 0.0f;

							v1 = AddVertexToMesh(p6, n1, r, g, b, a);
							v2 = AddVertexToMesh(p5, n1, r, g, b, a);
							v3 = AddVertexToMesh(p2, n1, r, g, b, a);
							v4 = AddVertexToMesh(p1, n1, r, g, b, a);

							t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
							t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
							t3 = AddTextureCoordinatesToMesh(1.0f, 1.0f);
							t4 = AddTextureCoordinatesToMesh(0.0f, 1.0f);

							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
							}
						}
					}
				}
			}
		}

	// Delete the merged array
	delete [] l_merged;
}

void VoxelGrid::CompleteMeshColour(void)
{
	GenerateBuffersColour();

	m_isRebuildingMesh = false;
}

void VoxelGrid::CompleteMesh(void)
{
	m_rebuild = 1;

	UpdateEmptyFlag();

	if(m_emptyVoxelGrid == false)
		{
		if(m_isParent == false)
			{
			if(m_Parent->m_emptyVoxelGrid == false)
				{
				if(m_Parent->mVertexPositionBuffer != 0)
					{
					mVertexPositionBuffer = m_Parent->mVertexPositionBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mVertexColorBuffer != 0)
					{
					mVertexColorBuffer = m_Parent->mVertexColorBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mVertexNormalBuffer != 0)
					{
					mVertexNormalBuffer = m_Parent->mVertexNormalBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mVertexTexCoordBuffer != 0)
					{
					mVertexTexCoordBuffer = m_Parent->mVertexTexCoordBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mIndexBuffer != 0)
					{
					mIndexBuffer = m_Parent->mIndexBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}
				}
			}
		else
			{
			GenerateBuffers();
			}
		}

	m_isRebuildingMesh = false;

	m_build_count++;
	m_rebuild = 0;
}

void VoxelLimb::CompleteMesh(void)
{
	m_rebuild = 1;

	UpdateEmptyFlag();

	if(m_emptyVoxelGrid == false)
		{
		if(m_isParent == false)
			{
			if(m_Parent->m_emptyVoxelGrid == false)
				{
				if(m_Parent->mVertexPositionBuffer != 0)
					{
					mVertexPositionBuffer = m_Parent->mVertexPositionBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mVertexColorBuffer != 0)
					{
					mVertexColorBuffer = m_Parent->mVertexColorBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mVertexNormalBuffer != 0)
					{
					mVertexNormalBuffer = m_Parent->mVertexNormalBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mVertexTexCoordBuffer != 0)
					{
					mVertexTexCoordBuffer = m_Parent->mVertexTexCoordBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}

				if(m_Parent->mIndexBuffer != 0)
					{
					mIndexBuffer = m_Parent->mIndexBuffer;
					}
				else
					{
					m_Parent->m_emptyVoxelGrid = true;
					}
				}
			}
		else
			{
			GenerateBuffers();
			}
		}

	m_isRebuildingMesh = false;

	m_build_count++;
	m_rebuild = 0;
}

void VoxelGrid::UpdateWallFlags(void)
{
	// Figure out if we have any full walls(sides) and are a completely surrounded VOXEL_GRID
	int x_minus = 0;
	int x_plus = 0;
	int y_minus = 0;
	int y_plus = 0;
	int z_minus = 0;
	int z_plus = 0;

	for(int y = 0; y < VOXEL_GRID_SIZE; y++)
		{
		for(int z = 0; z < VOXEL_GRID_SIZE; z++)
			{
			if(GetActive(0, y, z) == true)
				{
				x_minus++;
				}

			if(GetActive(VOXEL_GRID_SIZE - 1, y, z) == true)
				{
				x_plus++;
				}
			}
		}

	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for (int z = 0; z < VOXEL_GRID_SIZE; z++)
			{
			if(GetActive(x, 0, z) == true)
				{
				y_minus++;
				}

			if(GetActive(x, VOXEL_GRID_SIZE - 1, z) == true)
				{
				y_plus++;
				}
			}
		}

	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for(int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			if(GetActive(x, y, 0) == true)
				{
				z_minus++;
				}

			if(GetActive(x, y, VOXEL_GRID_SIZE - 1) == true)
				{
				z_plus++;
				}
			}
		}

	// Reset the wall flags first
	m_XSub_full = false;
	m_XAdd_full = false;
	m_YSub_full = false;
	m_YAdd_full = false;
	m_ZSub_full = false;
	m_ZAdd_full = false;

	// Set the flags to show if we have any sides completely full
	int wallsize = VOXEL_GRID_SIZE*VOXEL_GRID_SIZE;

	m_full = true;

	if(x_minus == wallsize)
		m_XSub_full = true;
	else
		m_full = false;

	if(x_plus == wallsize)
		m_XAdd_full = true;
	else
		m_full = false;

	if(y_minus == wallsize)
		m_YSub_full = true;
	else
		m_full = false;

	if(y_plus == wallsize)
		m_YAdd_full = true;
	else
		m_full = false;

	if(z_minus == wallsize)
		m_ZSub_full = true;
	else
		m_full = false;

	if(z_plus == wallsize)
		m_ZAdd_full = true;
	else
		m_full = false;
}

bool VoxelGrid::UpdateSurroundedFlag(void)
{
	std::shared_ptr<VoxelGrid> pVoxelGridXMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
	std::shared_ptr<VoxelGrid> pVoxelGridXPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
	std::shared_ptr<VoxelGrid> pVoxelGridYMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
	std::shared_ptr<VoxelGrid> pVoxelGridYPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
	std::shared_ptr<VoxelGrid> pVoxelGridZMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
	std::shared_ptr<VoxelGrid> pVoxelGridZPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);

	// Check our neighbor VOXEL_GRIDs
	if (((pVoxelGridXMinus == NULL) || pVoxelGridXMinus->m_XAdd_full) &&
	    ((pVoxelGridXPlus == NULL) || pVoxelGridXPlus->m_XSub_full) &&
		((pVoxelGridYMinus == NULL) || pVoxelGridYMinus->m_YAdd_full) &&
	    ((pVoxelGridYPlus == NULL) || pVoxelGridYPlus->m_YSub_full) &&
	    ((pVoxelGridZMinus == NULL) || pVoxelGridZMinus->m_ZAdd_full) &&
	    ((pVoxelGridZPlus == NULL) || pVoxelGridZPlus->m_ZSub_full))
		{
		m_surroundedVoxelGrid = true;
		}
	else
		{
		m_surroundedVoxelGrid = false;
		}

	return true;
}

void VoxelGrid::UpdateEmptyFlag(void)
{
	// Figure out if we are a completely empty VoxelGrid
	int numVerts = m_vec_Vertex.size();
	int numTriangles = m_vec_Index.size();

	if(m_isParent == true)
		{
		if(numVerts == 0 && numTriangles == 0)
			{
			m_emptyVoxelGrid = true;
			}
		else
			{
			m_emptyVoxelGrid = false;
			}
		}
	else
		{
		m_emptyVoxelGrid = false;
		}
}

void VoxelLimb::UpdateEmptyFlag(void)
{
	// Figure out if we are a completely empty VoxelGrid
	int numVerts = m_vec_Vertex.size();
	int numTriangles = m_vec_Index.size();

	if(m_isParent == true)
		{
		if(numVerts == 0 && numTriangles == 0)
			{
			m_emptyVoxelGrid = true;
			}
		else
			{
			m_emptyVoxelGrid = false;
			}
		}
	else
		{
		m_emptyVoxelGrid = false;
		}
}

void VoxelGrid::UpdateMergedSide(int *merged, int blockx, int blocky, int blockz, int width, int height, BiVector *p1, BiVector *p2, BiVector *p3, BiVector *p4, int startX, int startY, int maxX, int maxY, bool positive, bool zFace, bool xFace, bool yFace)
{
	const float BLOCK_RENDER = (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);

	bool doMore = true;

	unsigned int incrementX = 0;
	unsigned int incrementZ = 0;
	unsigned int incrementY = 0;

	int change = 1;

	if(positive == false)
		{
		//change = -1;
		}

	if(zFace || yFace)
		{
		incrementX = 1;
		incrementY = 1;
		}

	if(xFace)
		{
		incrementZ = 1;
		incrementY = 1;
		}

	// 1st phase
	int incrementer = 1;

	while(doMore == true)
		{
		if(startX + incrementer >= maxX)
			{
			doMore = false;
			}
		else
			{
			bool doPhase1Merge = true;
			float r1, r2, g1, g2, b1, b2, a1, a2;
			GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
			GetColour(blockx + incrementX, blocky, blockz + incrementZ, &r2, &g2, &b2, &a2);
			//if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx + incrementX][blocky][blockz + incrementZ].GetBlockType())
			//{
			// Don't do any phase 1 merging if we don't have the same block type.
			//	doPhase1Merge = false;
			//	doMore = false;
			//}
			/*//else*/ if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
				{
				// Don't do any phase 1 merging if we don't have the same colour variation
				doPhase1Merge = false;
				doMore = false;
				}
			else
				{
				if((xFace && positive && blockx + incrementX + 1 == VOXEL_GRID_SIZE) ||
					(xFace && !positive && blockx + incrementX == 0) ||
					(yFace && positive && blocky + 1 == VOXEL_GRID_SIZE) ||
					(yFace && !positive && blocky == 0) ||
					(zFace && positive && blockz + incrementZ + 1 == VOXEL_GRID_SIZE) ||
					(zFace && !positive && blockz + incrementZ == 0))
					{
					doPhase1Merge = false;
					doMore = false;
					}
				// Don't do any phase 1 merging if we find an inactive block or already merged block in our path
				else if (xFace && positive && (blockx + incrementX + 1) < VOXEL_GRID_SIZE && GetActive(blockx + incrementX + 1, blocky, blockz + incrementZ) == true)
					{
					doPhase1Merge = false;
					doMore = false;
					}
				else if (xFace && !positive && (blockx + incrementX) > 0 && GetActive(blockx + incrementX - 1, blocky, blockz + incrementZ) == true)
					{
					doPhase1Merge = false;
					doMore = false;
					}
				else if (yFace && positive && (blocky + 1) < VOXEL_GRID_SIZE && GetActive(blockx + incrementX, blocky + 1, blockz + incrementZ) == true)
					{
					doPhase1Merge = false;
					doMore = false;
					}
				else if (yFace && !positive && blocky > 0 && GetActive(blockx + incrementX, blocky - 1, blockz + incrementZ) == true)
					{
					doPhase1Merge = false;
					doMore = false;
					}
				else if (zFace && positive && (blockz + incrementZ + 1) < VOXEL_GRID_SIZE && GetActive(blockx + incrementX, blocky, blockz + incrementZ + 1) == true)
					{
					doPhase1Merge = false;
					doMore = false;
					}
				else if (zFace && !positive && (blockz + incrementZ) > 0 && GetActive(blockx + incrementX, blocky, blockz + incrementZ - 1) == true)
					{
					doPhase1Merge = false;
					doMore = false;
					}
				else if (GetActive(blockx + incrementX, blocky, blockz + incrementZ) == false)
					{
					doPhase1Merge = false;
					doMore = false;
					}
				else
					{
					if (xFace)
						{
						doPhase1Merge = positive ? (IsMergedXPositive(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false) : (IsMergedXNegative(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false);
						}
					if (zFace)
						{
						doPhase1Merge = positive ? (IsMergedZPositive(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false) : (IsMergedZNegative(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false);
						}
					if (yFace)
						{
						doPhase1Merge = positive ? (IsMergedYPositive(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false) : (IsMergedYNegative(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false);
						}
					}

				if(doPhase1Merge)
					{
					if (zFace || yFace)
						{
						(*p2).m_X += change * (BLOCK_RENDER);
						(*p3).m_X += change * BLOCK_RENDER;
						}
					if (xFace)
						{
						(*p2).m_Z += change * (BLOCK_RENDER);
						(*p3).m_Z += change * BLOCK_RENDER;
						}

					if (positive)
						{
						if (zFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Z_Positive;
							}
						if (xFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_X_Positive;
							}
						if (yFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Y_Positive;
							}
						}
					else
						{
						if (zFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Z_Negative;
							}
						if (xFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_X_Negative;
							}
						if (yFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Y_Negative;
							}
						}
					}
				else
					{
					doMore = false;
					}
				}
			}

		if(zFace || yFace)
			{
			incrementX += change;
			}

		if(xFace)
			{
			incrementZ += change;
			}

		incrementer += change;
		}

	// 2nd phase
	int loop = incrementer;
	incrementer = 0;
	incrementer = incrementY;

	doMore = true;

	while(doMore)
		{
		if (startY + incrementer >= maxY)
			{
			doMore = false;
			}
		else
			{
			for(int i = 0; i < loop - 1; i++)
				{
				// Don't do any phase 2 merging is we have any inactive blocks or already merged blocks on the row
				if(zFace)
					{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					GetColour(blockx + i, blocky + incrementY, blockz, &r2, &g2, &b2, &a2);

					if (positive && (blockz + 1) < VoxelGrid::VOXEL_GRID_SIZE && GetActive(blockx + i, blocky + incrementY, blockz + 1) == true)
						{
						doMore = false;
						}
					else if (!positive && blockz > 0 && GetActive(blockx + i, blocky + incrementY, blockz - 1) == true)
						{
						doMore = false;
						}
					else if (GetActive(blockx + i, blocky + incrementY, blockz) == false || (positive ? (IsMergedZPositive(merged, blockx + i, blocky + incrementY, blockz, width, height) == true) : (IsMergedZNegative(merged, blockx + i, blocky + incrementY, blockz, width, height) == true)))
						{
						// Failed active or already merged check
						doMore = false;
						}
					/*else if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx + i][blocky + incrementY][blockz].GetBlockType())
						{
						// Failed block type check
						doMore = false;
						}*/
					else if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
						{
						// Failed colour check
						doMore = false;
						}
					}

				if(xFace)
					{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					GetColour(blockx, blocky + incrementY, blockz + i, &r2, &g2, &b2, &a2);

					if(positive && (blockx + 1) < VOXEL_GRID_SIZE && GetActive(blockx + 1, blocky + incrementY, blockz + i) == true)
						{
						doMore = false;
						}
					else if(!positive && (blockx) > 0 && GetActive(blockx - 1, blocky + incrementY, blockz + i) == true)
						{
						doMore = false;
						}
					else if(GetActive(blockx, blocky + incrementY, blockz + i) == false || (positive ? (IsMergedXPositive(merged, blockx, blocky + incrementY, blockz + i, width, height) == true) : (IsMergedXNegative(merged, blockx, blocky + incrementY, blockz + i, width, height) == true)))
						{
						// Failed active or already merged check
						doMore = false;
						}
					/*else if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx][blocky + incrementY][blockz + i].GetBlockType())
						{
						// Failed block type check
						doMore = false;
						}
					*/
					else if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
						{
						// Failed colour check
						doMore = false;
						}
					}

				if(yFace)
					{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					GetColour(blockx + i, blocky, blockz + incrementY, &r2, &g2, &b2, &a2);

					if(positive && (blocky + 1) < VOXEL_GRID_SIZE && GetActive(blockx + i, blocky + 1, blockz + incrementY) == true)
						{
						doMore = false;
						}
					else if(!positive && blocky > 0 && GetActive(blockx + i, blocky - 1, blockz + incrementY) == true)
						{
						doMore = false;
						}
					else if(GetActive(blockx + i, blocky, blockz + incrementY) == false || (positive ? (IsMergedYPositive(merged, blockx + i, blocky, blockz + incrementY, width, height) == true) : (IsMergedYNegative(merged, blockx + i, blocky, blockz + incrementY, width, height) == true)))
						{
						// Failed active or already merged check
						doMore = false;
						}
					/*else if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx + i][blocky][blockz + incrementY].GetBlockType())
						{
						// Failed block type check
						doMore = false;
						}
					*/
					else if((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
						{
						// Failed colour check
						doMore = false;
						}
					}
				}

			if(doMore == true)
				{
				if(zFace || xFace)
					{
					(*p3).m_Y += change * BLOCK_RENDER;
					(*p4).m_Y += change * BLOCK_RENDER;
					}
				if(yFace)
					{
					(*p3).m_Z += change * BLOCK_RENDER;
					(*p4).m_Z += change * BLOCK_RENDER;
					}

				for(int i = 0; i < loop - 1; i++)
					{
					if(positive)
						{
						if(zFace)
							{
							merged[(blockx + i) + (blocky + incrementY)*width + blockz*width*height] |= MergedSide_Z_Positive;
							}
						if(xFace)
							{
							merged[blockx + (blocky + incrementY)*width + (blockz + i)*width*height] |= MergedSide_X_Positive;
							}
						if(yFace)
							{
							merged[(blockx + i) + blocky*width + (blockz + incrementY)*width*height] |= MergedSide_Y_Positive;
							}
						}
					else
						{
						if(zFace)
							{
							merged[(blockx + i) + (blocky + incrementY) * width + blockz*width*height] |= MergedSide_Z_Negative;
							}
						if(xFace)
							{
							merged[blockx + (blocky + incrementY) * width + (blockz + i) * width * height] |= MergedSide_X_Negative;
							}
						if(yFace)
							{
							merged[(blockx + i) + blocky * width + (blockz + incrementY) * width * height] |= MergedSide_Y_Negative;
							}
						}
					}
				}
			}

		incrementY += change;
		incrementer += change;
		}
}

void VoxelLimb::UpdateMergedSide(int *merged, int blockx, int blocky, int blockz, int width, int height, BiVector *p1, BiVector *p2, BiVector *p3, BiVector *p4, int startX, int startY, int maxX, int maxY, bool positive, bool zFace, bool xFace, bool yFace)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	bool doMore = true;

	unsigned int incrementX = 0;
	unsigned int incrementY = 0;
	unsigned int incrementZ = 0;

	int change = 1;

	if(positive == false)
		{
		//change = -1;
		}

	if(zFace || yFace)
		{
		incrementX = 1;
		incrementY = 1;
		}

	if(xFace)
		{
		incrementZ = 1;
		incrementY = 1;
		}

	// 1st phase
	int incrementer = 1;

	while(doMore)
		{
		if(startX + incrementer >= maxX)
			{
			doMore = false;
			}
		else
			{
			bool doPhase1Merge = true;

			float r1, r2, g1, g2, b1, b2, a1, a2;
			m_VX_Core->GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
			m_VX_Core->GetColour(blockx + incrementX, blocky, blockz + incrementZ, &r2, &g2, &b2, &a2);
			//if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx + incrementX][blocky][blockz + incrementZ].GetBlockType())
			//{
			// Don't do any phase 1 merging if we don't have the same block type.
			//	doPhase1Merge = false;
			//	doMore = false;
			//}
			/*//else*/ if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
				{
				// Don't do any phase 1 merging if we don't have the same colour variation
				doPhase1Merge = false;
				doMore = false;
				}
			else
				{
				if((xFace && positive && (blockx + incrementX + 1 == VoxelGrid::VOXEL_GRID_SIZE || blockx + incrementX + 1 >= m_MaxX)) ||
					(xFace && !positive && (blockx + incrementX == 0 || blockx + incrementX < m_MinX)) ||
					(yFace && positive && (blocky + 1 == VoxelGrid::VOXEL_GRID_SIZE && blocky + 1 >= m_MaxY)) ||
					(yFace && !positive && (blocky == 0 || blocky < m_MinY)) ||
					(zFace && positive && (blockz + incrementZ + 1 == VoxelGrid::VOXEL_GRID_SIZE || blockz + incrementZ + 1 >= m_MaxZ)) ||
					(zFace && !positive && (blockz + incrementZ == 0 || blockz + incrementZ < m_MinZ)))
					{
					doPhase1Merge = false;
					doMore = false;
					}
				// Don't do any phase 1 merging if we find an inactive block or already merged block in our path
				else
					{
					bool f_inc_ON = m_VX_Core->GetActive(blockx + incrementX + 1, blocky, blockz + incrementZ);

					if(xFace && positive && (blockx + incrementX + 1) < m_MaxX && f_inc_ON == true)
						{
						doPhase1Merge = false;
						doMore = false;
						}
					else
						{
						bool f_inc1_ON = m_VX_Core->GetActive(blockx + incrementX + 1, blocky, blockz + incrementZ);

						if (xFace && !positive && (blockx + incrementX) > 0 && f_inc1_ON == true)
							{
							doPhase1Merge = false;
							doMore = false;
							}
						else
							{
							bool f_inc2_ON = m_VX_Core->GetActive(blockx + incrementX, blocky + 1, blockz + incrementZ);

							if (yFace && positive && (blocky + 1) < m_MaxX && f_inc2_ON == true)
								{
								doPhase1Merge = false;
								doMore = false;
								}
							else
								{
								bool f_inc3_ON = m_VX_Core->GetActive(blockx + incrementX, blocky - 1, blockz + incrementZ);

								if (yFace && !positive && blocky > 0 && f_inc3_ON == true)
									{
									doPhase1Merge = false;
									doMore = false;
									}
								else
									{
									bool f_inc4_ON = m_VX_Core->GetActive(blockx + incrementX, blocky, blockz + incrementZ + 1);

									if (zFace && positive && (blockz + incrementZ + 1) < m_MaxX && f_inc4_ON == true)
										{
										doPhase1Merge = false;
										doMore = false;
										}
									else
										{
										bool f_inc5_ON = m_VX_Core->GetActive(blockx + incrementX, blocky, blockz + incrementZ - 1);

										if (zFace && !positive && (blockz + incrementZ) > 0 && f_inc5_ON == true)
											{
											doPhase1Merge = false;
											doMore = false;
											}
										else
											{
											bool f_inc6_ON = m_VX_Core->GetActive(blockx + incrementX, blocky, blockz + incrementZ);

											if (f_inc6_ON == false)
												{
												doPhase1Merge = false;
												doMore = false;
												}
											else
												{
												if (xFace)
													{
													doPhase1Merge = positive ? (IsMergedXPositive(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false) : (IsMergedXNegative(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false);
													}
												if (zFace)
													{
													doPhase1Merge = positive ? (IsMergedZPositive(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false) : (IsMergedZNegative(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false);
													}
												if (yFace)
													{
													doPhase1Merge = positive ? (IsMergedYPositive(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false) : (IsMergedYNegative(merged, blockx + incrementX, blocky, blockz + incrementZ, width, height) == false);
													}
												}
											}
										}
									}
								}
							}
						}
					}

				if(doPhase1Merge)
					{
					if (zFace || yFace)
						{
						(*p2).m_X += change * BLOCK_RENDER;
						(*p3).m_X += change * BLOCK_RENDER;
						}
					if (xFace)
						{
						(*p2).m_Z += change * BLOCK_RENDER;
						(*p3).m_Z += change * BLOCK_RENDER;
						}

					if (positive)
						{
						if (zFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Z_Positive;
							}
						if (xFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_X_Positive;
							}
						if (yFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Y_Positive;
							}
						}
					else
						{
						if (zFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Z_Negative;
							}
						if (xFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_X_Negative;
							}
						if (yFace)
							{
							merged[(blockx + incrementX) + blocky*width + (blockz + incrementZ)*width*height] |= MergedSide_Y_Negative;
							}
						}
					}
				else
					{
					doMore = false;
					}
				}
			}

		if(zFace || yFace)
			{
			incrementX += change;
			}

		if(xFace)
			{
			incrementZ += change;
			}

		incrementer += change;
		}

	// 2nd phase
	int loop = incrementer;
	incrementer = 0;
	incrementer = incrementY;

	doMore = true;

	while(doMore)
		{
		if (startY + incrementer >= maxY)
			{
			doMore = false;
			}
		else
			{
			for(int i = 0; i < loop - 1; i++)
				{
				// Don't do any phase 2 merging is we have any inactive blocks or already merged blocks on the row
				if(zFace)
					{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					m_VX_Core->GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					m_VX_Core->GetColour(blockx + i, blocky + incrementY, blockz, &r2, &g2, &b2, &a2);

					if (positive && (((blockz + 1) < VoxelGrid::VOXEL_GRID_SIZE) || ((blockz + 1) < m_MaxZ)) && m_VX_Core->GetActive(blockx + i, blocky + incrementY, blockz + 1) == true)
						{
						doMore = false;
						}
					else if (!positive && blockz > 0 && m_VX_Core->GetActive(blockx + i, blocky + incrementY, blockz - 1) == true)
						{
						doMore = false;
						}
					else if (m_VX_Core->GetActive(blockx + i, blocky + incrementY, blockz) == false || (positive ? (IsMergedZPositive(merged, blockx + i, blocky + incrementY, blockz, width, height) == true) : (IsMergedZNegative(merged, blockx + i, blocky + incrementY, blockz, width, height) == true)))
						{
						// Failed active or already merged check
						doMore = false;
						}
					/*else if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx + i][blocky + incrementY][blockz].GetBlockType())
						{
						// Failed block type check
						doMore = false;
						}*/
					else if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
						{
						// Failed colour check
						doMore = false;
						}
					}

				if(xFace)
					{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					m_VX_Core->GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					m_VX_Core->GetColour(blockx, blocky + incrementY, blockz + i, &r2, &g2, &b2, &a2);

					if(positive && (blockx + 1) < m_MaxX && m_VX_Core->GetActive(blockx + 1, blocky + incrementY, blockz + i) == true)
						{
						doMore = false;
						}
					else if(!positive && (blockx) > 0 && m_VX_Core->GetActive(blockx - 1, blocky + incrementY, blockz + i) == true)
						{
						doMore = false;
						}
					else if(m_VX_Core->GetActive(blockx, blocky + incrementY, blockz + i) == false || (positive ? (IsMergedXPositive(merged, blockx, blocky + incrementY, blockz + i, width, height) == true) : (IsMergedXNegative(merged, blockx, blocky + incrementY, blockz + i, width, height) == true)))
						{
						// Failed active or already merged check
						doMore = false;
						}
					/*else if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx][blocky + incrementY][blockz + i].GetBlockType())
						{
						// Failed block type check
						doMore = false;
						}
					*/
					else if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
						{
						// Failed colour check
						doMore = false;
						}
					}

				if(yFace)
					{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					m_VX_Core->GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					m_VX_Core->GetColour(blockx + i, blocky, blockz + incrementY, &r2, &g2, &b2, &a2);

					if(positive && (blocky + 1) < VoxelGrid::VOXEL_GRID_SIZE && m_VX_Core->GetActive(blockx + i, blocky + 1, blockz + incrementY) == true)
						{
						doMore = false;
						}
					else if(!positive && blocky > 0 && m_VX_Core->GetActive(blockx + i, blocky - 1, blockz + incrementY) == true)
						{
						doMore = false;
						}
					else if(m_VX_Core->GetActive(blockx + i, blocky, blockz + incrementY) == false || (positive ? (IsMergedYPositive(merged, blockx + i, blocky, blockz + incrementY, width, height) == true) : (IsMergedYNegative(merged, blockx + i, blocky, blockz + incrementY, width, height) == true)))
						{
						// Failed active or already merged check
						doMore = false;
						}
					/*else if(m_pBlocks[blockx][blocky][blockz].GetBlockType() != m_pBlocks[blockx + i][blocky][blockz + incrementY].GetBlockType())
						{
						// Failed block type check
						doMore = false;
						}
					*/
					else if((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
						{
						// Failed colour check
						doMore = false;
						}
					}
				}

			if(doMore == true)
				{
				if(zFace || xFace)
					{
					(*p3).m_Y += change * BLOCK_RENDER;
					(*p4).m_Y += change * BLOCK_RENDER;
					}
				if(yFace)
					{
					(*p3).m_Z += change * BLOCK_RENDER;
					(*p4).m_Z += change * BLOCK_RENDER;
					}

				for(int i = 0; i < loop - 1; i++)
					{
					if(positive)
						{
						if(zFace)
							{
							merged[(blockx + i) + (blocky + incrementY)*width + blockz*width*height] |= MergedSide_Z_Positive;
							}
						if(xFace)
							{
							merged[blockx + (blocky + incrementY)*width + (blockz + i)*width*height] |= MergedSide_X_Positive;
							}
						if(yFace)
							{
							merged[(blockx + i) + blocky*width + (blockz + incrementY)*width*height] |= MergedSide_Y_Positive;
							}
						}
					else
						{
						if(zFace)
							{
							merged[(blockx + i) + (blocky + incrementY) * width + blockz*width*height] |= MergedSide_Z_Negative;
							}
						if(xFace)
							{
							merged[blockx + (blocky + incrementY) * width + (blockz + i) * width * height] |= MergedSide_X_Negative;
							}
						if(yFace)
							{
							merged[(blockx + i) + blocky * width + (blockz + incrementY) * width * height] |= MergedSide_Y_Negative;
							}
						}
					}
				}
			}

		incrementY += change;
		incrementer += change;
		}
}

bool VoxelGrid::IsSetup(void)
{
	return m_setup;
}

// Rebuild
void VoxelGrid::RebuildMesh(float f_Scale)
{
	m_rebuild = 1;

	m_isRebuildingMesh = true;

	m_vec_Vertex.clear();
	m_vec_Normal.clear();
	m_vec_Color.clear();
	m_vec_Tex.clear();
	m_vec_Index.clear();

	if(f_Scale == 1.0f)
		{
		// Update our wall flags, so that our neighbors can check if they are surrounded
		UpdateWallFlags();
		UpdateSurroundedFlag();

		std::shared_ptr<VoxelGrid> pVoxelGridXMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
		std::shared_ptr<VoxelGrid> pVoxelGridXPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
		std::shared_ptr<VoxelGrid> pVoxelGridYMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
		std::shared_ptr<VoxelGrid> pVoxelGridYPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
		std::shared_ptr<VoxelGrid> pVoxelGridZMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
		std::shared_ptr<VoxelGrid> pVoxelGridZPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);

		if(pVoxelGridXMinus != NULL && pVoxelGridXMinus->IsSetup() == true)
			pVoxelGridXMinus->UpdateSurroundedFlag();
		if(pVoxelGridXPlus != NULL && pVoxelGridXPlus->IsSetup() == true)
			pVoxelGridXPlus->UpdateSurroundedFlag();
		if(pVoxelGridYMinus != NULL && pVoxelGridYMinus->IsSetup() == true)
			pVoxelGridYMinus->UpdateSurroundedFlag();
		if(pVoxelGridYPlus != NULL && pVoxelGridYPlus->IsSetup() == true)
			pVoxelGridYPlus->UpdateSurroundedFlag();
		if(pVoxelGridZMinus != NULL && pVoxelGridZMinus->IsSetup() == true)
			pVoxelGridZMinus->UpdateSurroundedFlag();
		if(pVoxelGridZPlus != NULL && pVoxelGridZPlus->IsSetup() == true)
			pVoxelGridZPlus->UpdateSurroundedFlag();

		// Rebuild neighbours
		if(m_rebuildNeighours)
			{
			if(pVoxelGridXMinus != NULL && pVoxelGridXMinus->IsSetup() == true)
				pVoxelGridXMinus->SetNeedsRebuild(true, false, m_ReserveReady);
			if(pVoxelGridXPlus != NULL && pVoxelGridXPlus->IsSetup() == true)
				pVoxelGridXPlus->SetNeedsRebuild(true, false, m_ReserveReady);
			if(pVoxelGridYMinus != NULL && pVoxelGridYMinus->IsSetup() == true)
				pVoxelGridYMinus->SetNeedsRebuild(true, false, m_ReserveReady);
			if(pVoxelGridYPlus != NULL && pVoxelGridYPlus->IsSetup() == true)
				pVoxelGridYPlus->SetNeedsRebuild(true, false, m_ReserveReady);
			if(pVoxelGridZMinus != NULL && pVoxelGridZMinus->IsSetup() == true)
				pVoxelGridZMinus->SetNeedsRebuild(true, false, m_ReserveReady);
			if(pVoxelGridZPlus != NULL && pVoxelGridZPlus->IsSetup() == true)
				pVoxelGridZPlus->SetNeedsRebuild(true, false, m_ReserveReady);

			m_rebuildNeighours = false;
			}
		}

	m_rebuild = 1;

	CreateMeshCubeDetail(f_Scale);

	m_numRebuilds++;

	m_rebuild = 1;
}

// Rebuild
void VoxelLimb::RebuildMesh(float f_Scale)
{
	m_rebuild = 1;

	m_isRebuildingMesh = true;

	m_vec_Vertex.clear();
	m_vec_Normal.clear();
	m_vec_Color.clear();
	m_vec_Tex.clear();
	m_vec_Index.clear();

	CreateMeshCubeDetail(f_Scale);

	m_numRebuilds++;

	m_rebuild = 1;
}

void VoxelGrid::RebuildMeshColour(void)
{
	m_isRebuildingMesh = true;

	m_vec_Vertex.clear();
	m_vec_Normal.clear();
	m_vec_Color.clear();
	m_vec_Tex.clear();
	m_vec_Index.clear();

	CreateMeshCubeColour();

	m_numRebuilds++;
	m_rebuild = 1;
}

void VoxelGrid::SetNeedsRebuild(bool rebuild, bool rebuildNeighours, bool f_ReserveReady)
{
	if(rebuild == true)
		{
		if(m_rebuild == 0)
			{
			m_rebuild = 1;
			m_rebuildNeighours = rebuildNeighours;
			m_ReserveReady = f_ReserveReady;
			}
		else
			{
			m_repeatbuild = 1;
			m_rebuildNeighours = rebuildNeighours;
			m_ReserveReady = f_ReserveReady;
			}
		}
}

void VoxelLimb::SetNeedsRebuild(bool rebuild, bool f_ReserveReady)
{
	if(rebuild == true)
		{
		m_rebuild = 1;
		m_ReserveReady = f_ReserveReady;
		m_rebuildCache = 1;
		}
}

void VoxelGrid::acRenderReserve(void)
{
	if(m_ReserveReady == true)
		{
		//Forward Reserve Buffers Cull
		g_VoxelGridManager->m_OGL_Mutex.lock();

		if(mVertexPositionBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexPositionBuffer);
			}

		if(mVertexNormalBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexNormalBuffer);
			}

		if(mVertexColorBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexColorBuffer);
			}

		if(mVertexTexCoordBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexTexCoordBuffer);
			}

		if(mIndexBuffer != 0)
			{
			glDeleteBuffers(1, &mIndexBuffer);
			}

		g_VoxelGridManager->m_OGL_Mutex.unlock();

		mVertexPositionBuffer = mresVertexPositionBuffer;
		mVertexNormalBuffer = mresVertexNormalBuffer;
		mVertexColorBuffer = mresVertexColorBuffer;
		mVertexTexCoordBuffer = mresVertexTexCoordBuffer;
		mIndexBuffer = mresIndexBuffer;

		m_FaceCount = m_vec_Index.size() * 3;

		m_ReserveReady = false;
		}
}

void VoxelLimb::acRenderReserve(void)
{
	if(m_ReserveReady == true)
		{
		//Forward Reserve Buffers Cull
		g_VoxelGridManager->m_OGL_Mutex.lock();

		if(mVertexPositionBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexPositionBuffer);
			}

		if(mVertexNormalBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexNormalBuffer);
			}

		if(mVertexColorBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexColorBuffer);
			}

		if(mVertexTexCoordBuffer != 0)
			{
			glDeleteBuffers(1, &mVertexTexCoordBuffer);
			}

		if(mIndexBuffer != 0)
			{
			glDeleteBuffers(1, &mIndexBuffer);
			}

		g_VoxelGridManager->m_OGL_Mutex.unlock();

		mVertexPositionBuffer = mresVertexPositionBuffer;
		mVertexNormalBuffer = mresVertexNormalBuffer;
		mVertexColorBuffer = mresVertexColorBuffer;
		mVertexTexCoordBuffer = mresVertexTexCoordBuffer;
		mIndexBuffer = mresIndexBuffer;

		m_FaceCount = m_vec_Index.size() * 3;

		m_ReserveReady = false;
		}
}

VoxelGridManager::VoxelGridManager()
{
	const std::string vs = STRING
		(
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec3 uPos;
		uniform vec3 uCam;
        attribute vec3 aPosition;
		attribute vec3 aNormal;
        attribute vec4 aColor;
		attribute vec2 aUV;
		varying vec3 absPosition;
		varying vec3 vNormal;
        varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			vec4 f_AttrPosition = vec4(aPosition, 1.0);
			vec4 f_Normal = vec4(aNormal, 1.0);

			vec4 f_ModelAttrPosition = uModelMatrix * f_AttrPosition;

			f_Normal = uModelMatrix * f_Normal; //\/wk

			// interim translation
			f_ModelAttrPosition.xyz += uPos; // grid position away
			
			vec3 f_absPosition = f_ModelAttrPosition.xyz;

			vec3 f_CameraFac = uCam;

			f_CameraFac.y *= -1.0;

			f_ModelAttrPosition.xyz -= f_CameraFac; // p1 cam subtract

			vec4 f_MVP_AttrPosition = uProjMatrix * uViewMatrix * f_ModelAttrPosition;

			absPosition = f_absPosition;

			vNormal = f_Normal.xyz; //wk
			vNormal.z *= -1.0; // all good!

			vUV = aUV;
			vColor = aColor;

			gl_Position = f_MVP_AttrPosition;
			}
		);

	const std::string fs = STRING
		(
		precision mediump float;

		vec3 g_seed_store;

		void seed(vec3 co)
			{
			g_seed_store = co;
			}

		float rand(void)
			{
			float f_result = fract(sin(dot(g_seed_store, vec3(12.9898, 78.233, 45.5432))) * 43758.5453);
			
			seed(vec3(f_result, f_result, f_result));

			return f_result;
			}

		vec4 al_Naturalize(vec4 f_InputColour, float f_X)
			{
			float f_Y = (f_X * f_X) * (f_X * -1.0); //swk

			vec4 f_ResultColourRGBA = f_InputColour * f_Y;

			return f_ResultColourRGBA;
			}
		
		uniform sampler2D uTexture;
		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
		uniform float uLightNom;
		uniform float uSeed;
		uniform float uTime;
		varying vec3 absPosition;
		varying vec3 vNormal;
		varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			float f_ProcCount = 0.0;

			//initially seed the psuedo random generator with absolute position
			seed(vec3(uSeed * absPosition.x, uSeed * absPosition.y, uSeed * absPosition.z));

			vec3 f_vNormal = normalize(vNormal); //opt on

			// pull ambient from current texture
			vec4 f_AmbientColor = vColor; //texture2D(uTexture, vTexCoord);

			// call for fragment
			float f_qsX = (rand() - 0.5) * 2.0;
			float f_qsY = (rand() - 0.5) * 2.0;
			float f_qsZ = (rand() - 0.5) * 2.0;
			float f_qsR = ((rand() - 0.5) * 2.0) * 1.5; //\/ swk 0.8

			vec4 randElement = vec4(f_qsX, f_qsY, f_qsZ, 1.0);

			float f_TimeBoh = sin(uTime);

			// accul Buffer
			vec4 f_AccumulationBuffer = vec4(0.0, 0.0, 0.0, 0.0);

			if(f_TimeBoh > 0.0)
				{
				//- sun effect -//
				vec3 f_SunLightPos = vec3(-3.93, 5.0, 0.7);
				vec4 f_SunLightColor = vec4(0.92, 0.87, 0.79, 1.0);

				float f_localTimeBoh = min(f_TimeBoh, 0.3);

				randElement *= (f_localTimeBoh * 1.45); //swk !!! 1.45

				f_SunLightColor = (f_SunLightColor * 0.85) + (randElement * 0.85); //wk

				vec3 f_L = normalize(f_SunLightPos);

				vec4 sunIdiff = vec4(f_SunLightColor.rgb * max(dot(f_vNormal, f_L), 0.0), 1.0);

				sunIdiff = clamp(sunIdiff, 0.0, 1.0);

				sunIdiff *= 0.07; // *= 0.03

				vec4 f_sunLight = clamp((f_AmbientColor * sunIdiff) * (f_qsR * f_localTimeBoh), 0.0, 1.0); // 1.795 summer day-8

				float f_sunMullLength = sqrt(f_sunLight.x * f_sunLight.x + f_sunLight.y * f_sunLight.y + f_sunLight.z * f_sunLight.z);

				float f_sunOffFac = clamp(f_sunMullLength, 0.0, 1.0);

				f_ProcCount += (1.0 - (f_sunOffFac * 0.5)) + 0.5; //swk 0.9775

				//- final pixel sun -//
				f_AccumulationBuffer = f_sunLight * ((f_SunLightColor * 0.475) + (f_AmbientColor * 0.475)); // summer day-
				}
			else // quantum moon
				{
				//- moon effect -//
				vec3 f_MoonLightPos = vec3(0.0, 5.0, 2.7);
				vec4 f_MoonLightColor = vec4(0.92, 0.92, 1.0, 1.0);

				float f_localTimeBoh = min(abs(f_TimeBoh), 0.3);

				f_localTimeBoh = max(f_localTimeBoh, 0.87);

				randElement *= (f_localTimeBoh * 1.45); //swk !!! 2.85

				f_MoonLightColor = (f_MoonLightColor * 0.87) + randElement; //wk

				vec3 f_L = normalize(f_MoonLightPos);

				vec4 MoonIdiff = vec4(f_MoonLightColor.rgb * max(dot(f_vNormal, f_L), 0.0), 1.0);

				MoonIdiff = clamp(MoonIdiff, 0.0, 1.0);

				MoonIdiff *= 0.07; // *= 0.03

				vec4 f_MoonLight = clamp((f_AmbientColor * MoonIdiff) * (f_qsR * f_TimeBoh), 0.0, 1.0); // 1.795 summer day-8

				float f_MoonMullLength = sqrt(f_MoonLight.x * f_MoonLight.x + f_MoonLight.y * f_MoonLight.y + f_MoonLight.z * f_MoonLight.z);

				float f_MoonOffFac = clamp(f_MoonMullLength, 0.0, 1.0);

				f_ProcCount += (1.0 - (f_MoonOffFac * 0.5)) + 0.5; //swk 0.89

				//- final pixel Moon -//
				f_AccumulationBuffer = f_MoonLight; // summer day-
				}

			// Lights Loop
			int f_LightNom = int(uLightNom);

			for(int f_i = 0; f_i < 10; f_i++)
				{
				if(f_i < f_LightNom)
					{
					if(uLightPos[f_i].w > 0.0)
						{
						vec3 f_LightPos = uLightPos[f_i].xyz;
						float f_LightRadius = uLightPos[f_i].w;

						//float f_LightAlpha = uLightColor[f_i].w;

						vec3 to_light = f_LightPos - absPosition;
						vec3 to_light_norm = normalize(to_light);

						// Scale the color of this fragment based on its angle to the light.                //wk???
						vec4 Idiffl = vec4(uLightColor[f_i].rgb * max(dot(f_vNormal, to_light_norm), 0.0), 1.0);

						Idiffl = clamp(Idiffl, 0.0, 1.0);

						Idiffl *= 0.07; // *= 0.03

						// Scale the power of this fragment based on its distance to the light.
						float f_constant_dist = sqrt(to_light.x * to_light.x + to_light.y * to_light.y + to_light.z * to_light.z);

							//(7%) OF (0.0 -> 1.0)                //33.0
						vec4 f_CalcVec = (Idiffl * (f_LightRadius / 24.4)) * (1.0 - clamp((f_constant_dist / 1450.0), 0.0, 1.0)); // 750.0 // 654.0 // 850.0 // 55.0 - 1450.0

						vec4 f_lightCalcVec = (f_AmbientColor * (f_CalcVec * 0.877)) + (f_CalcVec * 0.125);

						float f_MullLength = sqrt(f_lightCalcVec.x * f_lightCalcVec.x + f_lightCalcVec.y * f_lightCalcVec.y + f_lightCalcVec.z * f_lightCalcVec.z);

						float f_OffFac = clamp(f_MullLength, 0.0, 1.0);

						f_ProcCount += (1.0 - (f_OffFac * 0.5)); // 0.965 swk

						f_AccumulationBuffer += f_lightCalcVec;
						}
					}
				}

			// compile resultance accumulation
			vec4 f_Result = f_AccumulationBuffer / f_ProcCount;

			// [zero] blend
			f_Result.a = 1.0;

			// set pixel color
			gl_FragColor = f_Result;
			}
		);

    // Set up the shader and its uniform/attribute locations.
    mProgram = acProgram(vs, fs);

    mPositionAttribLocation = glGetAttribLocation(mProgram, "aPosition");
	mNormalAttribLocation = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocation = glGetAttribLocation(mProgram, "aColor");
	mTexCoordAttribLocation = glGetAttribLocation(mProgram, "aUV");

	mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
    mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
    mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");
	mPosUniformLocation = glGetUniformLocation(mProgram, "uPos");
	mCamUniformLocation = glGetUniformLocation(mProgram, "uCam");

	mLightPosUniformLocation = glGetUniformLocation(mProgram, "uLightPos");
	mLightColorUniformLocation = glGetUniformLocation(mProgram, "uLightColor");
	mLightNomUniformLocation = glGetUniformLocation(mProgram, "uLightNom");

	mTimeUniformLocation = glGetUniformLocation(mProgram, "uSeed");
	mFrameUniformLocation = glGetUniformLocation(mProgram, "uTime");

	m_VoxelGridsVector.clear();
	m_VoxelLimbVector.clear();

	m_VoxelGridsMap.clear();
	m_VoxelCoresMap.clear();

	m_StorageTime = 0;

	m_EngineWork_ThreadCount = 0;

	mx_Grid_UID = 0;
	mx_Limb_UID = 0;
}

VoxelGridManager::~VoxelGridManager()
{
    if(mProgram != 0)
		{
        glDeleteProgram(mProgram);

        mProgram = 0;
		}

	m_VoxelGridsVector.clear();
	m_VoxelLimbVector.clear();

	m_VoxelGridsMap.clear();
	m_VoxelCoresMap.clear();
}

bool WarZone_Manager::acPushGridOrigin(BiVector f_NewGridOrigin, std::shared_ptr<Cube::VoxelGrid> f_Grid)
{
	float f_Extent = 0.0f;

	if(f_Grid != nullptr)
		{
		if(f_Grid->m_War_Zone != nullptr)
			{
			m_current_WarZone = f_Grid->m_War_Zone;

			float f_PushExtent = ((m_current_WarZone->m_AxisExtent + 400.0f) * 2.0f);

			float f_New_Origin_X = (float)m_current_WarZone->m_Zone_X * f_PushExtent;
			float f_New_Origin_Y = (float)m_current_WarZone->m_Zone_Y * f_PushExtent;
			float f_New_Origin_Z = (float)m_current_WarZone->m_Zone_Z * f_PushExtent;

			m_current_Zone_Origin = BiVector(f_New_Origin_X, f_New_Origin_Y, f_New_Origin_Z);
			}
		}

	if(m_current_WarZone != nullptr)
		{
		f_Extent = m_current_WarZone->m_AxisExtent;
		}

	if(f_NewGridOrigin.m_X > m_current_Zone_Origin.m_X + (f_Extent + 400.0f))
		{
		int f_X_IntStr = m_current_WarZone->m_Zone_X;
		int f_Y_IntStr = m_current_WarZone->m_Zone_Y;
		int f_Z_IntStr = m_current_WarZone->m_Zone_Z;

		BiVector f_NewWarzoneOrigin = m_current_Zone_Origin;

		f_NewWarzoneOrigin.m_X += (f_Extent + 400.0f);

		m_current_WarZone = std::make_shared<WarZone>(f_NewWarzoneOrigin);

		m_current_WarZone->acInitialize();

		m_current_WarZone->m_Zone_X = f_X_IntStr + 1;
		m_current_WarZone->m_Zone_Y = f_Y_IntStr;
		m_current_WarZone->m_Zone_Z = f_Z_IntStr;

		m_current_Zone_Origin = f_NewWarzoneOrigin;

#ifdef WAR_ZONE_SAVE_ALLWAYS
		m_vec_WarZone.push_back(m_current_WarZone);
#endif

		if(f_Grid != nullptr)
			{
			if(f_Grid->m_War_Zone == nullptr)
				{
				f_Grid->m_War_Zone = m_current_WarZone;
				}
			}

		return true;
		}

	if(f_NewGridOrigin.m_X < m_current_Zone_Origin.m_X - (f_Extent + 400.0f))
		{
		int f_X_IntStr = m_current_WarZone->m_Zone_X;
		int f_Y_IntStr = m_current_WarZone->m_Zone_Y;
		int f_Z_IntStr = m_current_WarZone->m_Zone_Z;

		BiVector f_NewWarzoneOrigin = m_current_Zone_Origin;

		f_NewWarzoneOrigin.m_X -= (f_Extent + 400.0f);

		m_current_WarZone = std::make_shared<WarZone>(f_NewWarzoneOrigin);

		m_current_WarZone->acInitialize();

		m_current_WarZone->m_Zone_X = f_X_IntStr - 1;
		m_current_WarZone->m_Zone_Y = f_Y_IntStr;
		m_current_WarZone->m_Zone_Z = f_Z_IntStr;

		m_current_Zone_Origin = f_NewWarzoneOrigin;

#ifdef WAR_ZONE_SAVE_ALLWAYS
		m_vec_WarZone.push_back(m_current_WarZone);
#endif

		if(f_Grid != nullptr)
			{
			if(f_Grid->m_War_Zone == nullptr)
				{
				f_Grid->m_War_Zone = m_current_WarZone;
				}
			}

		return true;
		}

	if(f_NewGridOrigin.m_Y > m_current_Zone_Origin.m_Y + (f_Extent + 400.0f))
		{
		int f_X_IntStr = m_current_WarZone->m_Zone_X;
		int f_Y_IntStr = m_current_WarZone->m_Zone_Y;
		int f_Z_IntStr = m_current_WarZone->m_Zone_Z;

		BiVector f_NewWarzoneOrigin = m_current_Zone_Origin;

		f_NewWarzoneOrigin.m_Y += (f_Extent + 400.0f);

		m_current_WarZone = std::make_shared<WarZone>(f_NewWarzoneOrigin);

		m_current_WarZone->acInitialize();

		m_current_WarZone->m_Zone_X = f_X_IntStr;
		m_current_WarZone->m_Zone_Y = f_Y_IntStr + 1;
		m_current_WarZone->m_Zone_Z = f_Z_IntStr;

		m_current_Zone_Origin = f_NewWarzoneOrigin;

#ifdef WAR_ZONE_SAVE_ALLWAYS
		m_vec_WarZone.push_back(m_current_WarZone);
#endif

		if(f_Grid != nullptr)
			{
			if(f_Grid->m_War_Zone == nullptr)
				{
				f_Grid->m_War_Zone = m_current_WarZone;
				}
			}

		return true;
		}

	if(f_NewGridOrigin.m_Y < m_current_Zone_Origin.m_Y - (f_Extent + 400.0f))
		{
		int f_X_IntStr = m_current_WarZone->m_Zone_X;
		int f_Y_IntStr = m_current_WarZone->m_Zone_Y;
		int f_Z_IntStr = m_current_WarZone->m_Zone_Z;

		BiVector f_NewWarzoneOrigin = m_current_Zone_Origin;

		f_NewWarzoneOrigin.m_Y -= (f_Extent + 400.0f);

		m_current_WarZone = std::make_shared<WarZone>(f_NewWarzoneOrigin);

		m_current_WarZone->acInitialize();

		m_current_WarZone->m_Zone_X = f_X_IntStr;
		m_current_WarZone->m_Zone_Y = f_Y_IntStr - 1;
		m_current_WarZone->m_Zone_Z = f_Z_IntStr;

		m_current_Zone_Origin = f_NewWarzoneOrigin;

#ifdef WAR_ZONE_SAVE_ALLWAYS
		m_vec_WarZone.push_back(m_current_WarZone);
#endif

		if(f_Grid != nullptr)
			{
			if(f_Grid->m_War_Zone == nullptr)
				{
				f_Grid->m_War_Zone = m_current_WarZone;
				}
			}

		return true;
		}

	if(f_NewGridOrigin.m_Z > m_current_Zone_Origin.m_Z + (f_Extent + 400.0f))
		{
		int f_X_IntStr = m_current_WarZone->m_Zone_X;
		int f_Y_IntStr = m_current_WarZone->m_Zone_Y;
		int f_Z_IntStr = m_current_WarZone->m_Zone_Z;

		BiVector f_NewWarzoneOrigin = m_current_Zone_Origin;

		f_NewWarzoneOrigin.m_Z += (f_Extent + 400.0f);

		m_current_WarZone = std::make_shared<WarZone>(f_NewWarzoneOrigin);

		m_current_WarZone->acInitialize();

		m_current_WarZone->m_Zone_X = f_X_IntStr;
		m_current_WarZone->m_Zone_Y = f_Y_IntStr;
		m_current_WarZone->m_Zone_Z = f_Z_IntStr + 1;

		m_current_Zone_Origin = f_NewWarzoneOrigin;

#ifdef WAR_ZONE_SAVE_ALLWAYS
		m_vec_WarZone.push_back(m_current_WarZone);
#endif

		if(f_Grid != nullptr)
			{
			if(f_Grid->m_War_Zone == nullptr)
				{
				f_Grid->m_War_Zone = m_current_WarZone;
				}
			}

		return true;
		}

	if(f_NewGridOrigin.m_Z < m_current_Zone_Origin.m_Z - (f_Extent + 400.0f))
		{
		int f_X_IntStr = m_current_WarZone->m_Zone_X;
		int f_Y_IntStr = m_current_WarZone->m_Zone_Y;
		int f_Z_IntStr = m_current_WarZone->m_Zone_Z;

		BiVector f_NewWarzoneOrigin = m_current_Zone_Origin;

		f_NewWarzoneOrigin.m_Z -= (f_Extent + 400.0f);

		m_current_WarZone = std::make_shared<WarZone>(f_NewWarzoneOrigin);

		m_current_WarZone->acInitialize();

		m_current_WarZone->m_Zone_X = f_X_IntStr;
		m_current_WarZone->m_Zone_Y = f_Y_IntStr;
		m_current_WarZone->m_Zone_Z = f_Z_IntStr - 1;

		m_current_Zone_Origin = f_NewWarzoneOrigin;

#ifdef WAR_ZONE_SAVE_ALLWAYS
		m_vec_WarZone.push_back(m_current_WarZone);
#endif

		if(f_Grid != nullptr)
			{
			if(f_Grid->m_War_Zone == nullptr)
				{
				f_Grid->m_War_Zone = m_current_WarZone;
				}
			}

		return true;
		}

	if(m_current_WarZone == nullptr)
		{
		m_current_WarZone = std::make_shared<WarZone>(f_NewGridOrigin);

		m_current_WarZone->acInitialize();

		m_current_WarZone->m_Zone_X = 0;
		m_current_WarZone->m_Zone_Y = 0;
		m_current_WarZone->m_Zone_Z = 0;

		m_current_Zone_Origin = BiVector(0.0f, 0.0f, 0.0f);

#ifdef WAR_ZONE_SAVE_ALLWAYS
		m_vec_WarZone.push_back(m_current_WarZone);
#endif

		if(f_Grid != nullptr)
			{
			if(f_Grid->m_War_Zone == nullptr)
				{
				f_Grid->m_War_Zone = m_current_WarZone;
				}
			}

		return true;
		}

	return false;
}

WarZone_Manager::WarZone_Manager()
{
	acClear();

	acPushGridOrigin(BiVector(0.0f));
}

void WarZone::acSet_Extents(float f_Extents)
{
	m_AxisExtent = f_Extents;
}

WarZone::WarZone()
{
	throw;
}

WarZone::WarZone(BiVector f_NewOrigin) : m_position(f_NewOrigin)
{
	acClear();
}

void WarZone::acInitialize(void)
{
	acSet_Extents(WAR_ZONE_EXTENTS_RADIUS);

#if 0
	int f_POM = WAR_ZONE_POM_MIN + (Cube::randomFac() % (WAR_ZONE_POM_MAX - WAR_ZONE_POM_MIN));

	if((WAR_ZONE_POM_MIN == 1) && (WAR_ZONE_POM_MAX == 1))
		{
		f_POM = 1;
		}
#else
	int f_POM = 2;
#endif

	int f_SmallCount = (WAR_ZONE_SMALL_MIN + (Cube::randomFac() % (WAR_ZONE_SMALL_MAX - WAR_ZONE_SMALL_MIN))) * f_POM;
	int f_MediumCount = (WAR_ZONE_MEDIUM_MIN + (Cube::randomFac() % (WAR_ZONE_MEDIUM_MAX - WAR_ZONE_MEDIUM_MIN))) * f_POM;
	int f_LargeCount = (WAR_ZONE_LARGE_MIN + (Cube::randomFac() % (WAR_ZONE_LARGE_MAX - WAR_ZONE_LARGE_MIN))) * f_POM;

	int f_ObjectCount = (WAR_ZONE_OBJECT_MIN + (Cube::randomFac() % (WAR_ZONE_OBJECT_MAX - WAR_ZONE_OBJECT_MIN))) * f_POM;

#if 0
	int f_LampCount = (WAR_ZONE_LAMP_MIN + (Cube::randomFac() % (WAR_ZONE_LAMP_MAX - WAR_ZONE_LAMP_MIN))) * f_POM;
#else
	int f_LampCount = (WAR_ZONE_LAMP_MIN + (Cube::randomFac() % (WAR_ZONE_LAMP_MAX - WAR_ZONE_LAMP_MIN)));
	f_LampCount *= 1.6;
#endif

        ///////////////
	   ///////////////
	  // ONE ////////
	 //
	// Lock Building Production
	m_BuildingMuti.lock();

	for(int f_Zfact = 0; f_Zfact < f_SmallCount; f_Zfact++)
		{
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		f_Building->m_Width = (14 + ((Cube::randomFac() % 15) + (Cube::randomFac() % 15))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Length = (14 + ((Cube::randomFac() % 15) + (Cube::randomFac() % 15))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Height = (28 + ((Cube::randomFac() % 16) + (Cube::randomFac() % 15))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 0.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);

		m_vec_Building.push_back(f_Building);
		m_vec_WorkStatus_Building.push_back(0);

		if((Cube::randomFac() % WAR_ZONE_CLONING_CHANCE) <= 32)
			{
			int f_Count = WAR_ZONE_OBJECT_RAND_MIN + (Cube::randomFac() % (WAR_ZONE_OBJECT_RAND_MAX - WAR_ZONE_OBJECT_RAND_MIN));

			float f_DISTCULL = WAR_ZONE_RAND_DIST_CULL_MIN + (Cube::random() * (WAR_ZONE_RAND_DIST_CULL_MAX - WAR_ZONE_RAND_DIST_CULL_MIN));

			for(int f_Jet = 0; f_Jet < f_Count; f_Jet++)
				{
				std::shared_ptr<Building> f_CloneBuilding = std::make_shared<Building>();

				f_CloneBuilding->m_Width = f_Building->m_Width;
				f_CloneBuilding->m_Length = f_Building->m_Length;
				f_CloneBuilding->m_Height = f_Building->m_Height;

				f_CloneBuilding->m_Pos.m_X = f_Building->m_Pos.m_X + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Y = f_Building->m_Pos.m_Y + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Z = f_Building->m_Pos.m_Z + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));

				m_vec_Building.push_back(f_CloneBuilding);
				m_vec_WorkStatus_Building.push_back(0);
				}
			}
		}

	   ///////////////
	  ///////////////
	 // TWO ////////
	//
	for(int f_Zfact = 0; f_Zfact < f_MediumCount; f_Zfact++)
		{
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		f_Building->m_Width = (13 + ((Cube::randomFac() % 15) + (Cube::randomFac() % 15))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Length = (13 + ((Cube::randomFac() % 15) + (Cube::randomFac() % 15))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Height = (15 + ((Cube::randomFac() % 18) + (Cube::randomFac() % 15))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 0.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);

		m_vec_Building.push_back(f_Building);
		m_vec_WorkStatus_Building.push_back(0);

		if((Cube::randomFac() % WAR_ZONE_CLONING_CHANCE) <= 8)
			{
			int f_Count = WAR_ZONE_OBJECT_RAND_MIN + (Cube::randomFac() % (WAR_ZONE_OBJECT_RAND_MAX - WAR_ZONE_OBJECT_RAND_MIN));

			float f_DISTCULL = WAR_ZONE_RAND_DIST_CULL_MIN + (Cube::random() * (WAR_ZONE_RAND_DIST_CULL_MAX - WAR_ZONE_RAND_DIST_CULL_MIN));

			for(int f_Jet = 0; f_Jet < f_Count; f_Jet++)
				{
				std::shared_ptr<Building> f_CloneBuilding = std::make_shared<Building>();

				f_CloneBuilding->m_Width = f_Building->m_Width;
				f_CloneBuilding->m_Length = f_Building->m_Length;
				f_CloneBuilding->m_Height = f_Building->m_Height;

				f_CloneBuilding->m_Pos.m_X = f_Building->m_Pos.m_X + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Y = f_Building->m_Pos.m_Y + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Z = f_Building->m_Pos.m_Z + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));

				m_vec_Building.push_back(f_CloneBuilding);
				m_vec_WorkStatus_Building.push_back(0);
				}
			}
		}

	   /////////////////
	  /////////////////
	 // THREE ////////
	//
	for(int f_Zfact = 0; f_Zfact < f_LargeCount; f_Zfact++)
		{
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		bool f_Direction = Cube::randomFac() % 2;

		f_Building->m_Width = (14 + ((Cube::randomFac() % 30) + (Cube::randomFac() % 30))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Length = (14 + ((Cube::randomFac() % 30) + (Cube::randomFac() % 30))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Height = (15 + ((Cube::randomFac() % 8) + (Cube::randomFac() % 9))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 0.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);

		m_vec_Building.push_back(f_Building);
		m_vec_WorkStatus_Building.push_back(0);

		if((Cube::randomFac() % WAR_ZONE_CLONING_CHANCE) <= 12)
			{
			int f_Count = WAR_ZONE_OBJECT_RAND_MIN + Cube::randomFac() % ((WAR_ZONE_OBJECT_RAND_MAX / 3) - (WAR_ZONE_OBJECT_RAND_MIN / 3));

			float f_DISTCULL = WAR_ZONE_RAND_DIST_CULL_MIN + (Cube::random() * (WAR_ZONE_RAND_DIST_CULL_MAX - WAR_ZONE_RAND_DIST_CULL_MIN));

			for(int f_Jet = 0; f_Jet < f_Count; f_Jet++)
				{
				std::shared_ptr<Building> f_CloneBuilding = std::make_shared<Building>();

				f_CloneBuilding->m_Width = f_Building->m_Width;
				f_CloneBuilding->m_Length = f_Building->m_Length;
				f_CloneBuilding->m_Height = f_Building->m_Height;

				f_CloneBuilding->m_Pos.m_X = f_Building->m_Pos.m_X + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Y = f_Building->m_Pos.m_Y + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Z = f_Building->m_Pos.m_Z + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));

				m_vec_Building.push_back(f_CloneBuilding);
				m_vec_WorkStatus_Building.push_back(0);
				}
			}
		}

	   /////////////////
	  /////////////////
	 // FOUR /////////
	//
#if 1
	for(int f_Zfact = 0; f_Zfact < f_ObjectCount; f_Zfact++)
		{
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		bool f_Direction = Cube::randomFac() % 2;

		f_Building->m_Width = (16 + ((Cube::randomFac() % 27) + (Cube::randomFac() % 17))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Length = (16 + ((Cube::randomFac() % 27) + (Cube::randomFac() % 17))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));
		f_Building->m_Height = (16 + ((Cube::randomFac() % 29) + (Cube::randomFac() % 19))) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 0.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);

		m_vec_Building.push_back(f_Building);
		m_vec_WorkStatus_Building.push_back(0);

		if((Cube::randomFac() % WAR_ZONE_CLONING_CHANCE) < 14)
			{
			int f_Count = WAR_ZONE_OBJECT_RAND_MIN + (Cube::randomFac() % (WAR_ZONE_OBJECT_RAND_MAX - WAR_ZONE_OBJECT_RAND_MIN));

			float f_DISTCULL = WAR_ZONE_RAND_DIST_CULL_MIN + (Cube::random() * (WAR_ZONE_RAND_DIST_CULL_MAX - WAR_ZONE_RAND_DIST_CULL_MIN));

			for(int f_Jet = 0; f_Jet < f_Count; f_Jet++)
				{
				std::shared_ptr<Building> f_CloneBuilding = std::make_shared<Building>();

				f_CloneBuilding->m_Width = f_Building->m_Width;
				f_CloneBuilding->m_Length = f_Building->m_Length;
				f_CloneBuilding->m_Height = f_Building->m_Height;

				f_CloneBuilding->m_Pos.m_X = f_Building->m_Pos.m_X + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Y = f_Building->m_Pos.m_Y + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));
				f_CloneBuilding->m_Pos.m_Z = f_Building->m_Pos.m_Z + (((Cube::random() - 0.5f) * 2.0f) * (m_AxisExtent / f_DISTCULL));

				m_vec_Building.push_back(f_CloneBuilding);
				m_vec_WorkStatus_Building.push_back(0);
				}
			}
		}

	m_BuildingMuti.unlock();
#endif

	   /////////////////
	  /////////////////
	 // LIGHT ////////
	//
	m_LightBuildingMuti.lock();

	for(int f_Zfact = 0; f_Zfact < f_LampCount; f_Zfact++)
		{
		std::shared_ptr<LightStr> f_LightStr = std::make_shared<LightStr>();
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		f_Building->m_Width = (1 + (Cube::randomFac() % 4)) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

		if(Cube::randomFac() % 10 <= 8)
			{
			f_Building->m_Length = f_Building->m_Width;
			}
		else
			{
			if(Cube::randomFac() % 10 >= 4)
				{
				f_Building->m_Length = f_Building->m_Width / 2;
				}
			else
				{
				f_Building->m_Length = f_Building->m_Width * 2;
				}
			}

		f_Building->m_Height = (5 + (Cube::randomFac() % 14)) * (10 / (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

		f_LightStr->m_RGBA.alpha = 255.0f;
		f_LightStr->m_RGBA.red = ((Cube::random() * 0.65f) + 0.45f) * 255.0f;
		f_LightStr->m_RGBA.green = ((Cube::random() * 0.65f) + 0.45f) * 255.0f;
		f_LightStr->m_RGBA.blue = ((Cube::random() * 0.65f) + 0.45f) * 255.0f;

		f_LightStr->m_Building = f_Building;

		f_LightStr->m_Radius = ((Cube::random() * 1500.0f) + 500.0f);

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 0.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5f) * 2.0f) * m_AxisExtent);

		m_vec_LightStr.push_back(f_LightStr);
		m_vec_Light_Building.push_back(f_Building);
		m_vec_WorkStatus_Light_Building.push_back(0);
		}

	// UnLock Building Production 
	m_LightBuildingMuti.unlock();
}

// Getting VoxelGrid and positional information
void VoxelGridManager::GetGridFromPosition(BiVector position, int* gridX, int* gridY, int* gridZ)
{
	const float GRIDSIZE = (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

	float f_X_GridFlt = position.m_X / GRIDSIZE;
	float f_Y_GridFlt = position.m_Y / GRIDSIZE;
	float f_Z_GridFlt = position.m_Z / GRIDSIZE;

	float f_Full_X = 0;
	float f_Fract_X = modf(f_X_GridFlt, &f_Full_X);

	float f_Full_Y = 0;
	float f_Fract_Y = modf(f_Y_GridFlt, &f_Full_Y);

	float f_Full_Z = 0;
	float f_Fract_Z = modf(f_Z_GridFlt, &f_Full_Z);

	int f_Xgrid = f_Full_X;
	int f_Ygrid = f_Full_Y;
	int f_Zgrid = f_Full_Z;

	if(f_Fract_X < 0.0f)
		f_Xgrid -= 1;
	if(f_Fract_Y < 0.0f)
		f_Ygrid -= 1;
	if(f_Fract_Z < 0.0f)
		f_Zgrid -= 1;

	//Flip Z axis
	f_Zgrid *= -1.0f;

	*(gridX) = f_Xgrid;
	*(gridY) = f_Ygrid;
	*(gridZ) = f_Zgrid;
}

std::shared_ptr<VoxelGrid> VoxelGridManager::GetVoxelGridFromPosition(float posX, float posY, float posZ)
{
	int gridX = 0;
	int gridY = 0;
	int gridZ = 0;

	GetGridFromPosition(BiVector(posX, posY, posZ), &gridX, &gridY, &gridZ);

	return GetVoxelGrid(gridX, gridY, gridZ);
}

std::shared_ptr<VoxelGrid> VoxelGridManager::GetVoxelGridFromPosition(BiVector position)
{
	int gridX = 0;
	int gridY = 0;
	int gridZ = 0;

	GetGridFromPosition(position, &gridX, &gridY, &gridZ);

	return GetVoxelGrid(gridX, gridY, gridZ);
}

void VoxelGridManager::Draw(BiVector f_Position)
{
	glEnable(GL_DEPTH_TEST);

#if 0 // poss temp
	glEnable(GL_TEXTURE_2D);
#endif

#if 1
	glDisable(GL_BLEND);

#else
	glEnable(GL_BLEND);

#if 1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
#else
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

#endif

#if 0 // ???
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
#endif

	if(mProgram == 0)
		{
		return;
		}

	glUseProgram(mProgram);

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
	glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	  /////////////////
	 // Q_Light
	//
	ag_Calc_Light(f_Position);

	glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
	glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
	glUniform1f(mLightNomUniformLocation, g_LightNom);

	glUniform3f(mCamUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);

	g_UpdatingMuti.lock();

	int f_i = g_VoxelGridManager->m_VoxelGridsVector.size();

	int f_manageid = 0;

	g_UpdatingMuti.unlock();

	for(int i = 0; i < f_i; i++)
		{
		if(m_VoxelGridsVector[i]->m_isParent == true)
			{
			if((m_VoxelGridsVector[i]->m_emptyVoxelGrid == false) && (m_VoxelGridsVector[i]->m_full == false))
				{
				if(m_VoxelGridsVector[i]->m_created == true)
					{
					if((m_VoxelGridsVector[i]->m_rebuild == 0) || ((m_VoxelGridsVector[i]->m_rebuild > 0) && (m_VoxelGridsVector[i]->m_ReserveReady == true)))
						{
						std::shared_ptr<VoxelGrid> f_ParentGrid = m_VoxelGridsVector[i];

						if(f_ParentGrid->m_rebuild == 0)
							{
							f_ParentGrid->acRenderReserve();
							}

						bool f_BuffersUpl = false;

						BiVector f_Parent_PlayerGridVector(f_Position.m_X - (f_ParentGrid->m_position.m_X + /*VOX_BY2*/0.0f), f_Position.m_Y - (f_ParentGrid->m_position.m_Y + /*VOX_BY2*/0.0f), f_Position.m_Z - (f_ParentGrid->m_position.m_Z + /*VOX_BY2*/0.0f));

						float f_DistP = f_Parent_PlayerGridVector.acLength();

						if((f_DistP < VIEW_DISTANCE) && (f_ParentGrid->m_ShowOff == false))
							{
							MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
							glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

							glUniform3f(mPosUniformLocation, f_ParentGrid->m_position.m_X, f_ParentGrid->m_position.m_Y, f_ParentGrid->m_position.m_Z);

							glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexPositionBuffer);
							glEnableVertexAttribArray(mPositionAttribLocation);
							glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexNormalBuffer);
							glEnableVertexAttribArray(mNormalAttribLocation);
							glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexColorBuffer);
							glEnableVertexAttribArray(mColorAttribLocation);
							glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexTexCoordBuffer);
							glEnableVertexAttribArray(mTexCoordAttribLocation);
							glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_ParentGrid->mIndexBuffer);

							f_BuffersUpl = true;

							// parent grid
							if(f_ParentGrid->m_FaceCount > 0)
								{
								glUniform1f(mTimeUniformLocation, Cube::random());

								glUniform1f(mFrameUniformLocation, g_TimeDiff);

								// GL_TRIANGLES Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
								glDrawElements(GL_TRIANGLES, f_ParentGrid->m_FaceCount, GL_UNSIGNED_SHORT, 0);
								}
							}

						// Playground
						for(int f_XY = 0; f_XY < f_ParentGrid->m_Child.size(); f_XY++)
							{
							std::shared_ptr<VoxelGrid> f_ChildGrid = f_ParentGrid->m_Child[f_XY];
			
							BiVector f_Child_PlayerGridVector(f_Position.m_X - (f_ChildGrid->m_position.m_X + /*VOX_BY2*/0.0f), f_Position.m_Y - (f_ChildGrid->m_position.m_Y + /*VOX_BY2*/0.0f), f_Position.m_Z - (f_ChildGrid->m_position.m_Z + /*VOX_BY2*/0.0f));

							float f_DistC = f_Child_PlayerGridVector.acLength();

							if((f_DistC < VIEW_DISTANCE) && (f_ChildGrid->m_ShowOff == false))
								{
								glUniform3f(mPosUniformLocation, f_ChildGrid->m_position.m_X, f_ChildGrid->m_position.m_Y, f_ChildGrid->m_position.m_Z);

								if(f_BuffersUpl == false)
									{
									glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexPositionBuffer);
									glEnableVertexAttribArray(mPositionAttribLocation);
									glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexNormalBuffer);
									glEnableVertexAttribArray(mNormalAttribLocation);
									glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexColorBuffer);
									glEnableVertexAttribArray(mColorAttribLocation);
									glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, f_ParentGrid->mVertexTexCoordBuffer);
									glEnableVertexAttribArray(mTexCoordAttribLocation);
									glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_ParentGrid->mIndexBuffer);

									f_BuffersUpl = true;
									}

								// parent grid
								if(f_ChildGrid->m_created == true)
									{
									if(f_ChildGrid->m_rebuild == 0)
										{
										if(f_ChildGrid->m_FaceCount > 0)
											{
											glUniform1f(mTimeUniformLocation, Cube::random());

											glUniform1f(mFrameUniformLocation, g_TimeDiff);

											// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
											glDrawElements(GL_TRIANGLES, f_ChildGrid->m_FaceCount, GL_UNSIGNED_SHORT, 0);
											}
										}
									}
								}
							}

						  //
						 // Limbs
						//////////////
						if((f_DistP < VIEW_DISTANCE)) // Parent in view
							{
							// Parent Limbs
							for(int f_LY = 0; f_LY < f_ParentGrid->m_vec_VoxelLimb.size(); f_LY++)
								{
								if(f_ParentGrid->m_vec_VoxelLimb[f_LY]->m_isParent == true)
									{
									if(f_ParentGrid->m_vec_VoxelLimb[f_LY]->m_emptyVoxelGrid == false)
										{
										if(f_ParentGrid->m_vec_VoxelLimb[f_LY]->m_created == true)
											{
											if((f_ParentGrid->m_vec_VoxelLimb[f_LY]->m_rebuild == 0) || ((f_ParentGrid->m_vec_VoxelLimb[f_LY]->m_rebuild > 0) && (f_ParentGrid->m_vec_VoxelLimb[f_LY]->m_ReserveReady == true)))
												{
												std::shared_ptr<VoxelLimb> f_Limb = f_ParentGrid->m_vec_VoxelLimb[f_LY];

												if(f_Limb->m_rebuild == 0)
													{
													f_Limb->acRenderReserve();
													}

												bool f_BuffersUpLimb = false;

												 //////////////////////////////
												////// Render Limb Mesh //////
												if(f_Limb->m_ShowOff == false)
													{
#if 0
													glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, f_Limb->Xform.Matrix.mf);

													glUniform3f(mPosUniformLocation, /*f_ParentGrid->m_position.m_X +*/f_Limb->m_position.m_X, f_Limb->m_position.m_Y, f_Limb->m_position.m_Z);
#else
													MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
													glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

													glUniform3f(mPosUniformLocation, f_ParentGrid->m_position.m_X, f_ParentGrid->m_position.m_Y, f_ParentGrid->m_position.m_Z);
#endif

													glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexPositionBuffer);
													glEnableVertexAttribArray(mPositionAttribLocation);
													glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

													glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexNormalBuffer);
													glEnableVertexAttribArray(mNormalAttribLocation);
													glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

													glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexColorBuffer);
													glEnableVertexAttribArray(mColorAttribLocation);
													glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

													glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexTexCoordBuffer);
													glEnableVertexAttribArray(mTexCoordAttribLocation);
													glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

													glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Limb->mIndexBuffer);

													f_BuffersUpLimb = true;

													// parent grid
													if(f_Limb->m_FaceCount > 0)
														{
														glUniform1f(mTimeUniformLocation, Cube::random());

														glUniform1f(mFrameUniformLocation, g_TimeDiff);

														// GL_TRIANGLES Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
														glDrawElements(GL_TRIANGLES, f_Limb->m_FaceCount, GL_UNSIGNED_SHORT, 0);
														}
													}

												// Limb Playground
												for(int f_LXY = 0; f_LXY < f_Limb->m_Child.size(); f_LXY++)
													{
													std::shared_ptr<VoxelLimb> f_ChildLimb = f_Limb->m_Child[f_LXY];

													if(f_ChildLimb)
														{
														if(f_ChildLimb->m_created == true)
															{
															if(f_ChildLimb->m_rebuild == 0)
																{
																if(f_ChildLimb->m_ShowOff == false)
																	{
#if 0
																	glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, f_ChildLimb->Xform.Matrix.mf);

																	glUniform3f(mPosUniformLocation, /*f_ParentGrid->m_position.m_X +*/f_ChildLimb->m_position.m_X, f_ChildLimb->m_position.m_Y, f_ChildLimb->m_position.m_Z);
#endif

																	if(f_BuffersUpLimb == false)
																		{
																		glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexPositionBuffer);
																		glEnableVertexAttribArray(mPositionAttribLocation);
																		glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

																		glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexNormalBuffer);
																		glEnableVertexAttribArray(mNormalAttribLocation);
																		glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

																		glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexColorBuffer);
																		glEnableVertexAttribArray(mColorAttribLocation);
																		glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

																		glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexTexCoordBuffer);
																		glEnableVertexAttribArray(mTexCoordAttribLocation);
																		glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

																		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Limb->mIndexBuffer);

																		f_BuffersUpLimb = true;
																		}

																	// Child Limb
																	if(f_Limb->m_FaceCount > 0)
																		{
																		glUniform1f(mTimeUniformLocation, Cube::random());

																		glUniform1f(mFrameUniformLocation, g_TimeDiff);

																		// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
																		glDrawElements(GL_TRIANGLES, f_Limb->m_FaceCount, GL_UNSIGNED_SHORT, 0);
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}

						 ///////////////////////////////////
						// Playground - Limbs Extension
						for(int f_XY = 0; f_XY < f_ParentGrid->m_Child.size(); f_XY++)
							{
							std::shared_ptr<VoxelGrid> f_ChildGrid = f_ParentGrid->m_Child[f_XY];

							BiVector f_Child_PlayerGridVector(f_Position.m_X - (f_ChildGrid->m_position.m_X + /*VOX_BY2*/0.0f), f_Position.m_Y - (f_ChildGrid->m_position.m_Y + /*VOX_BY2*/0.0f), f_Position.m_Z - (f_ChildGrid->m_position.m_Z + /*VOX_BY2*/0.0f));

							float f_DistF = f_Child_PlayerGridVector.acLength();

							if((f_DistF < VIEW_DISTANCE) && (f_ChildGrid->m_ShowOff == false))
								{
								// Parent Limbs
								for(int f_LYX = 0; f_LYX < f_ChildGrid->m_vec_VoxelLimb.size(); f_LYX++)
									{
									if(f_ChildGrid->m_vec_VoxelLimb[f_LYX]->m_isParent == true)
										{
										if(f_ChildGrid->m_vec_VoxelLimb[f_LYX]->m_emptyVoxelGrid == false)
											{
											if(f_ChildGrid->m_vec_VoxelLimb[f_LYX]->m_created == true)
												{
												if((f_ChildGrid->m_vec_VoxelLimb[f_LYX]->m_rebuild == 0) || ((f_ChildGrid->m_vec_VoxelLimb[f_LYX]->m_rebuild > 0) && (f_ChildGrid->m_vec_VoxelLimb[f_LYX]->m_ReserveReady == true)))
													{
													std::shared_ptr<VoxelLimb> f_Limb = f_ChildGrid->m_vec_VoxelLimb[f_LYX];

													if(f_Limb->m_rebuild == 0)
														{
														f_Limb->acRenderReserve();
														}

													bool f_BuffersUpLimbr = false;

													 //////////////////////////////
													////// Render Limb Mesh //////
													if(f_Limb->m_ShowOff == false)
														{
#if 0
														glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, f_Limb->Xform.Matrix.mf);

														glUniform3f(mPosUniformLocation, /*f_ParentGrid->m_position.m_X +*/f_Limb->m_position.m_X, f_Limb->m_position.m_Y, f_Limb->m_position.m_Z);
#else
														MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
														glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

														glUniform3f(mPosUniformLocation, f_ChildGrid->m_position.m_X, f_ChildGrid->m_position.m_Y, f_ChildGrid->m_position.m_Z);
#endif

														glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexPositionBuffer);
														glEnableVertexAttribArray(mPositionAttribLocation);
														glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

														glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexNormalBuffer);
														glEnableVertexAttribArray(mNormalAttribLocation);
														glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

														glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexColorBuffer);
														glEnableVertexAttribArray(mColorAttribLocation);
														glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

														glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexTexCoordBuffer);
														glEnableVertexAttribArray(mTexCoordAttribLocation);
														glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

														glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Limb->mIndexBuffer);

														f_BuffersUpLimbr = true;

														// parent grid
														if(f_Limb->m_FaceCount > 0)
															{
															glUniform1f(mTimeUniformLocation, Cube::random());

															glUniform1f(mFrameUniformLocation, g_TimeDiff);

															// GL_TRIANGLES Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
															glDrawElements(GL_TRIANGLES, f_Limb->m_FaceCount, GL_UNSIGNED_SHORT, 0);
															}
														}

													// Limb Playground
													for(int f_LXYX = 0; f_LXYX < f_Limb->m_Child.size(); f_LXYX++)
														{
														std::shared_ptr<VoxelLimb> f_ChildLimb = f_Limb->m_Child[f_LXYX];

														if(f_ChildLimb)
															{
															if(f_ChildLimb->m_created == true)
																{
																if(f_ChildLimb->m_rebuild == 0)
																	{
																	if(f_ChildLimb->m_ShowOff == false)
																		{
#if 0
																		glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, f_Limb->Xform.Matrix.mf);

																		glUniform3f(mPosUniformLocation, /*f_ParentGrid->m_position.m_X +*/f_Limb->m_position.m_X, f_Limb->m_position.m_Y, f_Limb->m_position.m_Z);
#endif

																		if(f_BuffersUpLimbr == false)
																			{
																			glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexPositionBuffer);
																			glEnableVertexAttribArray(mPositionAttribLocation);
																			glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

																			glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexNormalBuffer);
																			glEnableVertexAttribArray(mNormalAttribLocation);
																			glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

																			glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexColorBuffer);
																			glEnableVertexAttribArray(mColorAttribLocation);
																			glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

																			glBindBuffer(GL_ARRAY_BUFFER, f_Limb->mVertexTexCoordBuffer);
																			glEnableVertexAttribArray(mTexCoordAttribLocation);
																			glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

																			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_Limb->mIndexBuffer);

																			f_BuffersUpLimbr = true;
																			}

																		// Child grid
																		if(f_Limb->m_FaceCount > 0)
																			{
																			glUniform1f(mTimeUniformLocation, Cube::random());

																			glUniform1f(mFrameUniformLocation, g_TimeDiff);

																			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
																			glDrawElements(GL_TRIANGLES, f_Limb->m_FaceCount, GL_UNSIGNED_SHORT, 0);
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

		g_UpdatingMuti.lock();

		int f_Newi = g_VoxelGridManager->m_VoxelGridsVector.size();

		int f_Newmanageid = g_VoxelGridManager->m_VoxelGridsVector[i]->m_ManagerIndex;

		if(f_Newi != f_i)
			{
			if(f_Newmanageid != f_manageid)
				{
				for(int f_jet = 0; f_jet < f_Newi; f_jet++)
					{
					if(f_jet == f_manageid)
						{
						// new vector index for loop
						i = f_jet;

						// reset loop
						f_jet == f_Newi;
						}
					}
				}

			f_i = f_Newi;
			}
		else
			{
			if(i + 1 < f_Newi)
				{
				f_manageid = g_VoxelGridManager->m_VoxelGridsVector[i + 1]->m_ManagerIndex;
				}
			}

		g_UpdatingMuti.unlock();
		}
}

// Grid
void VoxelGrid::SetGrid(int x, int y, int z)
{
	m_gridX = x;
	m_gridY = y;
	m_gridZ = z;
}

// Position
void VoxelGrid::SetPosition(BiVector pos)
{
	const float BLOCK_RENDER = (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);

	m_position = pos;

	m_midpoint = pos;

	m_midpoint += BiVector(VOX_BY2);

	m_Xpos = m_position.m_X / BLOCK_RENDER;
	m_Ypos = m_position.m_Y / BLOCK_RENDER;
	m_Zpos = (m_position.m_Z * -1.0f) / BLOCK_RENDER;
}

// Grid
void VoxelLimb::SetGrid(int x, int y, int z)
{
	m_gridX = x;
	m_gridY = y;
	m_gridZ = z;
}

// Position
void VoxelLimb::SetPosition(BiVector pos)
{
	const float BLOCK_RENDER = (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);

	m_position = pos;

	m_midpoint = pos;

	m_midpoint += BiVector(VOX_BY2);

	m_Xpos = m_position.m_X / BLOCK_RENDER;
	m_Ypos = m_position.m_Y / BLOCK_RENDER;
	m_Zpos = (m_position.m_Z * -1.0f) / BLOCK_RENDER;
}

BiVector VoxelGrid::GetPosition(void)
{
	return m_position;
}

// VoxelGrid Creation
void VoxelGridManager::CreateNewVoxelGrid(int x, int y, int z)
{
	const float BLOCK_RENDER = (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_RENDER = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	VoxelGridCoordKeys coordKeys;

	coordKeys.x = x;
	coordKeys.y = y;
	coordKeys.z = z;

	// Create a new VoxelGrid at this grid position
	std::shared_ptr<VoxelGrid> pNewVoxelGrid = std::make_shared<VoxelGrid>(m_VoxelGridsVector.size());

	pNewVoxelGrid->m_Self = pNewVoxelGrid;

	map<VoxelGridCoordKeys, std::shared_ptr<VoxelGridCore>>::iterator it = m_VoxelCoresMap.find(coordKeys);

	if(it != m_VoxelCoresMap.end())
		{
		std::shared_ptr<VoxelGridCore> lpVoxCore = m_VoxelCoresMap[coordKeys];

		pNewVoxelGrid->m_VX_Core = lpVoxCore;

		pNewVoxelGrid->m_setup = true;
		}
	else
		{
		// Create a new Voxel Core for this grid
		pNewVoxelGrid->m_VX_Core = std::make_shared<VoxelGridCore>();
		}

	float xPos = x * GRID_RENDER;
	float yPos = y * GRID_RENDER;
	float zPos = z * GRID_RENDER;

	pNewVoxelGrid->SetPosition(BiVector(xPos, yPos, zPos));
	pNewVoxelGrid->SetGrid(coordKeys.x, coordKeys.y, coordKeys.z);
	pNewVoxelGrid->SetNeedsRebuild(true, true);

	g_UpdatingMuti.lock();

	// vector and map references
	m_VoxelGridsMap[coordKeys] = pNewVoxelGrid;
	m_VoxelCoresMap[coordKeys] = pNewVoxelGrid->m_VX_Core;

	m_VoxelGridsVector.push_back(pNewVoxelGrid);

	g_UpdatingMuti.unlock();

#if 0
	pNewVoxelGrid->RebuildMesh();
	pNewVoxelGrid->CompleteMesh();
	pNewVoxelGrid->SetCreated(true);

	UpdateVoxelGridNeighbours(pNewVoxelGrid, x, y, z);
#endif
}

void VoxelGridManager::acFullRebuild(void)
{
	for(int f_Helly = 0; f_Helly < g_VoxelGridManager->m_VoxelGridsVector.size(); f_Helly++)
		{
		std::shared_ptr<VoxelGrid> f_Grid = g_VoxelGridManager->m_VoxelGridsVector[f_Helly];

		if((f_Grid->m_setup == true) && (f_Grid->m_rebuild <= 0))
			{
			//QAM
			if(g_QAM)
				{
				for(int f_Cnt = 0; f_Cnt < g_QAM->m_vec_Terrain.size(); f_Cnt++)
					{
					qamTerrain* f_Terrain = g_QAM->m_vec_Terrain[f_Cnt];

					if(f_Terrain->Make_Place_Terrain(f_Grid))
						{
						f_Grid->SetNeedsRebuild(true, true, true);
						}
					}
				}

			//QBUILDING
			for(int f_Cnt = 0; f_Cnt < 1; f_Cnt++)
				{
				//...
				}
			}
		}
}

std::shared_ptr<VoxelGrid> VoxelGridManager::GetVoxelGrid(int aX, int aY, int aZ)
{
	VoxelGridCoordKeys VoxelGridKey;

	VoxelGridKey.x = aX;
	VoxelGridKey.y = aY;
	VoxelGridKey.z = aZ;

	g_UpdatingMuti.lock();

	std::map<VoxelGridCoordKeys, std::shared_ptr<VoxelGrid>>::iterator it = m_VoxelGridsMap.find(VoxelGridKey);

	if(it != m_VoxelGridsMap.end())
		{
		std::shared_ptr<VoxelGrid> lpReturn = m_VoxelGridsMap[VoxelGridKey];

		g_UpdatingMuti.unlock();

		return lpReturn;
		}

	g_UpdatingMuti.unlock();

	return nullptr;
}

// Neighbours
int VoxelGrid::GetNumNeighbours()
{
	return m_numNeighbours;
}

void VoxelGrid::SetNumNeighbours(int neighbours)
{
	m_numNeighbours = neighbours;
}

std::shared_ptr<VoxelGrid> VoxelGrid::GetxMinus()
{
	return m_CkXSub;
}

std::shared_ptr<VoxelGrid> VoxelGrid::GetxPlus()
{
	return m_CkXAdd;
}

std::shared_ptr<VoxelGrid> VoxelGrid::GetyMinus()
{
	return m_CkYSub;
}

std::shared_ptr<VoxelGrid> VoxelGrid::GetyPlus()
{
	return m_CkYAdd;
}

std::shared_ptr<VoxelGrid> VoxelGrid::GetzMinus()
{
	return m_CkZSub;
}

std::shared_ptr<VoxelGrid> VoxelGrid::GetzPlus()
{
	return m_CkZAdd;
}

void VoxelGrid::SetxMinus(std::shared_ptr<VoxelGrid> pVoxelGrid)
{
	m_CkXSub = pVoxelGrid;
}

void VoxelGrid::SetxPlus(std::shared_ptr<VoxelGrid> pVoxelGrid)
{
	m_CkXAdd = pVoxelGrid;
}

void VoxelGrid::SetyMinus(std::shared_ptr<VoxelGrid> pVoxelGrid)
{
	m_CkYSub = pVoxelGrid;
}

void VoxelGrid::SetyPlus(std::shared_ptr<VoxelGrid> pVoxelGrid)
{
	m_CkYAdd = pVoxelGrid;
}

void VoxelGrid::SetzMinus(std::shared_ptr<VoxelGrid> pVoxelGrid)
{
	m_CkZSub = pVoxelGrid;
}

void VoxelGrid::SetzPlus(std::shared_ptr<VoxelGrid> pVoxelGrid)
{
	m_CkZAdd = pVoxelGrid;
}

bool VoxelGrid::CollidePointHeight(BiVector f_Point, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ)
{
	const float BLOCK_RENDER = (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_RENDER = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	f_Point.m_Z *= -1.0f;

	bool f_Collide = false;

	if(f_Point.m_X >= (f_x * GRID_RENDER) &&
		f_Point.m_X < ((f_x + 1) * GRID_RENDER) &&
		f_Point.m_Y >= (f_y * GRID_RENDER) &&
		f_Point.m_Y < ((f_y + 1) * GRID_RENDER) &&
		f_Point.m_Z >= (f_z * GRID_RENDER) &&
		f_Point.m_Z < ((f_z + 1) * GRID_RENDER))
		{
		for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
					{
					if(GetActive(x, y, z))
						{
						if((f_Point.m_X > ((f_x * GRID_RENDER) + ((x * BLOCK_RENDER)))) &&
							(f_Point.m_X < ((f_x * GRID_RENDER) + (((x + 1) * BLOCK_RENDER)))) &&
							(f_Point.m_Y > ((f_y * GRID_RENDER) + ((y * BLOCK_RENDER)))) &&
							(f_Point.m_Y < ((f_y * GRID_RENDER) + (((y + 1) * BLOCK_RENDER)))) &&
							(f_Point.m_Z > ((f_z * GRID_RENDER) + ((z * BLOCK_RENDER)))) &&
							(f_Point.m_Z < ((f_z * GRID_RENDER) + (((z + 1) * BLOCK_RENDER)))))
							{
							f_Collide = true;
							SetColour(x, y, z, 1.0f, 0.5, 0.8, 1.0f);
							*(f_ResX) = x;
							*(f_ResY) = y;
							*(f_ResZ) = z;
							}
						}
					}
				}
			}
		}

	return f_Collide;
}

bool VoxelGrid::CollidePointHeightField(BiVector f_Point, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ)
{
	const float BLOCK_RENDER = (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_RENDER = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	// axis flip
#if 0
	f_Point.m_Z *= -1.0f;
#endif

	bool f_Collide = false;

	if((f_Point.m_X >= (f_x * GRID_RENDER)) &&
		(f_Point.m_X < ((f_x + 1) * GRID_RENDER)) &&
		(f_Point.m_Y >= (f_y * GRID_RENDER)) &&
		(f_Point.m_Y < ((f_y + 1) * GRID_RENDER)) &&
		(f_Point.m_Z >= (f_z * GRID_RENDER)) &&
		(f_Point.m_Z < ((f_z + 1) * GRID_RENDER)))
		{
		for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
					{
					if(GetActive(x, y, z))
						{
						if((f_Point.m_X >= ((f_x * GRID_RENDER) + ((x * BLOCK_RENDER)))) &&
							(f_Point.m_X < ((f_x * GRID_RENDER) + (((x + 1) * BLOCK_RENDER)))) &&
							(f_Point.m_Y >= ((f_y * GRID_RENDER) + ((y * BLOCK_RENDER)))) &&
							(f_Point.m_Y < ((f_y * GRID_RENDER) + (((y + 1) * BLOCK_RENDER)))) &&
							(f_Point.m_Z >= ((f_z * GRID_RENDER) + ((z * BLOCK_RENDER)))) &&
							(f_Point.m_Z < ((f_z * GRID_RENDER) + (((z + 1) * BLOCK_RENDER)))))
							{
							f_Collide = true;
							SetColour(x, y, z, 1.0f, 0.5, 0.8, 1.0f);
							*(f_ResX) = x;
							*(f_ResY) = y;
							*(f_ResZ) = z;

							int f_Height = 0;
							for(int f_fy = 0; f_fy < VOXEL_GRID_SIZE; f_fy++)
								{
								if(GetActive(x, f_fy, z) && f_fy > f_Height)
									{
									f_Height = f_fy;
									}
								}

							*(f_ResY) = f_Height;
							}
						}
					}
				}
			}
		}

	return f_Collide;
}

bool VoxelGrid::CollideMarchPoint(QpoCollision* f_Collision)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRIDSIZE = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	BiVector f_Front = f_Collision->Front;

	Cube::BiVector f_DefVec = f_Front - f_Collision->Rear;

	float f_DefaultVecLength = f_DefVec.acLength();

	if(f_DefaultVecLength < BLOCK_RENDER / VOXEL_MARCH_DIV)
		{
		f_DefaultVecLength += BLOCK_RENDER / VOXEL_MARCH_DIV;
		}

	float f_Infact = f_DefaultVecLength;

	QpoVec3d MotionVec;

	MotionVec.x = f_DefVec.m_X;
	MotionVec.y = f_DefVec.m_Y;
	MotionVec.z = f_DefVec.m_Z;

	Qpo->Vec3d_Normalize(&MotionVec);

	Cube::BiVector f_Vec1 = f_Collision->Rear;

	int Xacting = 0;
	int Yacting = 0;
	int Zacting = 0;

	//Stage 1 Test Ray Line
	bool f_Collide = false;

	while((f_DefaultVecLength > 0.0f) && (f_Collide == false))
		{
		if((f_Vec1.m_X >= ((float)m_gridX * GRIDSIZE)) &&
			(f_Vec1.m_X < (((float)m_gridX + 1) * GRIDSIZE)) &&
			(f_Vec1.m_Y >= ((float)m_gridY * GRIDSIZE)) &&
			(f_Vec1.m_Y < (((float)m_gridY + 1) * GRIDSIZE)) &&
			(f_Vec1.m_Z >= ((float)(m_gridZ * -1) * GRIDSIZE)) &&
			(f_Vec1.m_Z < (((float)(m_gridZ * -1) + 1) * GRIDSIZE)))
			{
			int f_Xclip = ((int)f_Vec1.m_X / (int)BLOCK_RENDER);
			int f_Yclip = ((int)f_Vec1.m_Y / (int)BLOCK_RENDER);
			int f_Zclip = ((int)f_Vec1.m_Z / (int)BLOCK_RENDER);

			Xacting = f_Xclip - m_Xpos;
			Yacting = f_Yclip - m_Ypos;
			Zacting = f_Zclip - m_Zpos;

#ifdef VOXELDMG_AREAEFFECT
			int Xfin = Xacting + 1;
			int Yfin = Yacting + 1;
			int Zfin = Zacting + 1;

			for(int x = Xacting; x < Xfin; x++)
				{
				for(int y = Yacting; y < Yfin; y++)
					{
					for(int z = Zacting; z < Zfin; z++)
						{
#endif

						if((m_rebuild > 0) && (m_setup == false))
							{
							f_Collision->Impact.acSet(f_Vec1.m_X, f_Vec1.m_Y, f_Vec1.m_Z);

							f_Collision->m_VXBlock.m_BIDX = Xacting;
							f_Collision->m_VXBlock.m_BIDY = Yacting;
							f_Collision->m_VXBlock.m_BIDZ = Zacting;

							// calc grid square Default impact normal
							BiVector f_BlockCenter((((float)m_gridX * GRIDSIZE) + (GRIDSIZE / 2.0f)),
													(((float)m_gridY * GRIDSIZE) + (GRIDSIZE / 2.0f)),
													(((float)(m_gridZ * -1) * GRIDSIZE) + (GRIDSIZE / 2.0f)));

							f_Collision->Normal.m_X = f_Vec1.m_X - f_BlockCenter.m_X;
							f_Collision->Normal.m_X = f_Vec1.m_Y - f_BlockCenter.m_Y;
							f_Collision->Normal.m_Z = f_Vec1.m_Z - f_BlockCenter.m_Z;

							f_Collision->Normal.acNormalize();

							//default building return
							return true;
							}

						if(GetActive(Xacting, Yacting, Zacting) == true)
							{

#ifdef SUPER_SECURE_MARCH
							BiVector f_Vec2 = f_Vec1;
							BiVector f_VecLengthVec2(f_Vec2.m_X + (MotionVec.x * ((BLOCK_RENDER_SIZE) / (VOXEL_MARCH_DIV))), f_Vec2.m_Y + (MotionVec.y * ((BLOCK_RENDER_SIZE) / (VOXEL_MARCH_DIV))), f_Vec2.m_Z + (MotionVec.z * ((BLOCK_RENDER_SIZE) / (VOXEL_MARCH_DIV))));

							float f_DefLength = f_DefaultVecLength;

							float fm_Vec2Length = f_VecLengthVec2.acLength();

							if(f_DefLength < 1.0f / VOXEL_MARCH_DIV)
								{
								f_DefLength = 1.0f / VOXEL_MARCH_DIV;
								}

							while((fm_Vec2Length > 0.0f) && (f_Collide == false))
								{
#endif

								float f_CubeMinX = ((float)m_gridX * GRIDSIZE) + (Xacting * BLOCK_RENDER);
								float f_CubeMinY = ((float)m_gridY * GRIDSIZE) + (Yacting * BLOCK_RENDER);
								float f_CubeMinZ = ((float)(m_gridZ * -1) * GRIDSIZE) + (Zacting * BLOCK_RENDER);

								if(m_gridX < 0)
									{
									f_CubeMinX -= BLOCK_RENDER;
									}

								if(m_gridY < 0)
									{
									f_CubeMinY -= BLOCK_RENDER;
									}

								if((m_gridZ * -1) < 0) // swk
									{
									f_CubeMinZ -= BLOCK_RENDER;
									}

								float f_CubeMaxX = f_CubeMinX + BLOCK_RENDER;
								float f_CubeMaxY = f_CubeMinY + BLOCK_RENDER;
								float f_CubeMaxZ = f_CubeMinZ + BLOCK_RENDER;

#ifdef SUPER_SECURE_MARCH
								if( (f_Vec2.m_X >= f_CubeMinX) &&
									(f_Vec2.m_X < f_CubeMaxX) &&
									(f_Vec2.m_Y >= f_CubeMinY) &&
									(f_Vec2.m_Y < f_CubeMaxY) &&
									(f_Vec2.m_Z >= f_CubeMinZ) &&
									(f_Vec2.m_Z < f_CubeMaxZ))
									{
#endif

									// Impact! calc grid square impact normal
									f_Collide = true;

									f_Collision->Impact.acSet(f_Vec1.m_X, f_Vec1.m_Y, f_Vec1.m_Z);

									f_Collision->m_VXBlock.m_BIDX = Xacting;
									f_Collision->m_VXBlock.m_BIDY = Yacting;
									f_Collision->m_VXBlock.m_BIDZ = Zacting;

#if 0
									SetColour(x, y, z, 1.0f, 0.5, 0.8, 1.0f);
#endif

									float f_AmpValue = (BLOCK_RENDER / VOXEL_MARCH_DIV) * 1.5f;

									float f_MinDiffX = f_Vec1.m_X - f_CubeMinX;
									float f_MaxDiffX = f_CubeMaxX - f_Vec1.m_X;

									float f_MinDiffY = f_Vec1.m_Y - f_CubeMinY;
									float f_MaxDiffY = f_CubeMaxY - f_Vec1.m_Y;

									float f_MinDiffZ = f_Vec1.m_Z - f_CubeMinZ;
									float f_MaxDiffZ = f_CubeMaxZ - f_Vec1.m_Z;

									uint f_Bok[3];

									f_Bok[0] = 0; // 0 Min - 1 Max
									f_Bok[1] = 0;
									f_Bok[2] = 0; // 2 Min < AmpValue - 3 Max < AmpValue

									if(f_MinDiffX < f_MaxDiffX) // MinX
										{
										if(f_MinDiffX < f_AmpValue)
											{
											f_Bok[0] = 2;
											}
										else
											{
											f_Bok[0] = 0;
											}
										}
									else
										{
										if(f_MaxDiffX < f_AmpValue)
											{
											f_Bok[0] = 3;
											}
										else
											{
											f_Bok[0] = 1;
											}
										}

									if(f_MinDiffY < f_MaxDiffY) //MinX - MinY
										{
										if(f_MinDiffY < f_AmpValue)
											{
											f_Bok[1] = 2;
											}
										else
											{
											f_Bok[1] = 0;
											}
										}
									else
										{
										if(f_MaxDiffY < f_AmpValue)
											{
											f_Bok[1] = 3;
											}
										else
											{
											f_Bok[1] = 1;
											}
										}

									if(f_MinDiffZ < f_MaxDiffZ) //MinX - MinY - MinZ
										{
										if(f_MinDiffZ < f_AmpValue)
											{
											f_Bok[2] = 2;
											}
										else
											{
											f_Bok[2] = 0;
											}
										}
									else
										{
										if(f_MaxDiffZ < f_AmpValue)
											{
											f_Bok[2] = 3;
											}
										else
											{
											f_Bok[2] = 1;
											}
										}

									 // First test all main directions X- X+ Y- Y+ Z- Z+
									//
									if((f_Bok[0] == 3) && (f_Bok[1] < 2) && (f_Bok[2] < 2))
										{
										f_Collision->Normal.m_X = 1.0f; // X+
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}
									
									if((f_Bok[0] == 2) && (f_Bok[1] < 2) && (f_Bok[2] < 2))
										{
										f_Collision->Normal.m_X = -1.0f; // X-
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[1] == 3) && (f_Bok[0] < 2) && (f_Bok[2] < 2))
										{
										f_Collision->Normal.m_X = 0.0f; // Y+
										f_Collision->Normal.m_Y = 1.0f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[1] == 2) && (f_Bok[0] < 2) && (f_Bok[2] < 2))
										{
										f_Collision->Normal.m_X = 0.0f; // Y-
										f_Collision->Normal.m_Y = -1.0f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[2] == 3) && (f_Bok[0] < 2) && (f_Bok[1] < 2))
										{
										f_Collision->Normal.m_X = 0.0f; // Z+
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = 1.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[2] == 2) && (f_Bok[0] < 2) && (f_Bok[1] < 2))
										{
										f_Collision->Normal.m_X = 0.0f; // Z-
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = -1.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									 // ? ok test four corners Z-
									//
									if((f_Bok[0] == 2) && (f_Bok[1] == 3) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Y+ Z-
										f_Collision->Normal.m_Y = 0.5f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 2) && (f_Bok[1] == 2) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Y- Z-
										f_Collision->Normal.m_Y = -0.5f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[1] == 3) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Y+ Z-
										f_Collision->Normal.m_Y = 0.5f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[1] == 2) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Y- Z-
										f_Collision->Normal.m_Y = -0.5f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									 // ? ok test four corners Z+
									//
									if((f_Bok[0] == 2) && (f_Bok[1] == 3) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Y+ Z+
										f_Collision->Normal.m_Y = 0.5f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 2) && (f_Bok[1] == 2) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Y- Z+
										f_Collision->Normal.m_Y = -0.5f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[1] == 3) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Y+ Z+
										f_Collision->Normal.m_Y = 0.5f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[1] == 2) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Y- Z+
										f_Collision->Normal.m_Y = -0.5f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									 // ? - check all 12 edges extreme
									//
									if((f_Bok[0] == 2) && (f_Bok[1] == 3))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Y+
										f_Collision->Normal.m_Y = 0.5f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[1] == 3))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Y+
										f_Collision->Normal.m_Y = 0.5f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 2) && (f_Bok[1] == 2))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Y-
										f_Collision->Normal.m_Y = -0.5f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[1] == 2))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Y-
										f_Collision->Normal.m_Y = -0.5f;
										f_Collision->Normal.m_Z = 0.0f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 2) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Z+
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Z+
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 2) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = -0.5f; //X-Z-
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[0] == 3) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = 0.5f; //X+Z-
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[1] == 2) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = 0.0f; //Z-Y-
										f_Collision->Normal.m_Y = -0.5f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[1] == 3) && (f_Bok[2] == 2))
										{
										f_Collision->Normal.m_X = 0.0f; //Z-Y+
										f_Collision->Normal.m_Y = 0.5f;
										f_Collision->Normal.m_Z = -0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[1] == 2) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = -0.5f; //Z+Y-
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									if((f_Bok[1] == 3) && (f_Bok[2] == 3))
										{
										f_Collision->Normal.m_X = 0.5f; //Z+Y+
										f_Collision->Normal.m_Y = 0.0f;
										f_Collision->Normal.m_Z = 0.5f;

										f_Collision->Normal.acNormalize();

										return f_Collide;
										}

									// calc grid square Default impact normal
									BiVector f_BlockCenter((((float)m_gridX * GRIDSIZE) + ((((float)Xacting * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE))),
														   (((float)m_gridY * GRIDSIZE) + ((((float)Yacting * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE))),
														   (((float)(m_gridZ * -1) * GRIDSIZE) + ((((float)Zacting * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE))));

									f_Collision->Normal.m_X = f_Vec1.m_X - f_BlockCenter.m_X;
									f_Collision->Normal.m_X = f_Vec1.m_Y - f_BlockCenter.m_Y;
									f_Collision->Normal.m_Z = f_Vec1.m_Z - f_BlockCenter.m_Z;

									f_Collision->Normal.acNormalize();

									//default normal return || Cube::random(x, y, z);
									return f_Collide;

#ifdef SUPER_SECURE_MARCH
									}

								if(fm_Vec2Length != FLT_MAX)
									{
									fm_Vec2Length -= 1.0f / VOXEL_MARCH_DIV;

									if(fm_Vec2Length <= 0.0f)
										{
										fm_Vec2Length = FLT_MAX;
										f_DefLength = FLT_MAX;

										f_Vec2 = f_Front;
										}
									else
										{
										f_DefLength -= BLOCK_RENDER / VOXEL_MARCH_DIV;

										f_Vec2.m_X += (MotionVec.x * (BLOCK_RENDER / VOXEL_MARCH_DIV));
										f_Vec2.m_Y += (MotionVec.y * (BLOCK_RENDER / VOXEL_MARCH_DIV));
										f_Vec2.m_Z += (MotionVec.z * (BLOCK_RENDER / VOXEL_MARCH_DIV));
										}

									if(f_DefLength <= 0.0f)
										{
										fm_Vec2Length = 0.0f;
										f_Infact = BLOCK_RENDER;
										}
									}
								else
									{
									fm_Vec2Length = 0.0f;
									f_DefLength = 0.0f;
									f_Infact = BLOCK_RENDER;
									}
								}
#endif
							}
						else
							{
							f_Infact = BLOCK_RENDER;
							}
#ifdef VOXELDMG_AREAEFFECT
						}
					}
				}
#endif
			}
		else
			{
			f_Collision->Rear = f_Vec1;

			f_Collision->Normal.m_X = 0.0f;
			f_Collision->Normal.m_Y = 0.0f;
			f_Collision->Normal.m_Z = 0.0f;

			return false;
			}

		f_Vec1.m_X += (MotionVec.x * f_Infact);
		f_Vec1.m_Y += (MotionVec.y * f_Infact);
		f_Vec1.m_Z += (MotionVec.z * f_Infact);

		f_DefaultVecLength -= f_Infact;
		}

	//Stage 2 Test Front Nib
	if((f_Front.m_X >= ((float)m_gridX * GRIDSIZE)) &&
		(f_Front.m_X < (((float)m_gridX + 1) * GRIDSIZE)) &&
		(f_Front.m_Y >= ((float)m_gridY * GRIDSIZE)) &&
		(f_Front.m_Y < (((float)m_gridY + 1) * GRIDSIZE)) &&
		(f_Front.m_Z >= ((float)(m_gridZ * -1) * GRIDSIZE)) &&
		(f_Front.m_Z < (((float)(m_gridZ * -1) + 1) * GRIDSIZE)))
		{
		int f_Xclip = ((int)f_Front.m_X / (int)BLOCK_RENDER);
		int f_Yclip = ((int)f_Front.m_Y / (int)BLOCK_RENDER);
		int f_Zclip = ((int)f_Front.m_Z / (int)BLOCK_RENDER);

		Xacting = f_Xclip - m_Xpos;
		Yacting = f_Yclip - m_Ypos;
		Zacting = f_Zclip - m_Zpos;

#ifdef VOXELDMG_AREAEFFECT
		int Xfin = Xacting + 1;
		int Yfin = Yacting + 1;
		int Zfin = Zacting + 1;

		for(int x = Xacting; x < Xfin; x++)
			{
			for(int y = Yacting; y < Yfin; y++)
				{
				for(int z = Zacting; z < Zfin; z++)
					{
#endif

					if((m_rebuild > 0) && (m_setup == false))
						{
						f_Collision->Impact.acSet(f_Front.m_X, f_Front.m_Y, f_Front.m_Z);

						f_Collision->m_VXBlock.m_BIDX = Xacting;
						f_Collision->m_VXBlock.m_BIDY = Yacting;
						f_Collision->m_VXBlock.m_BIDZ = Zacting;

						// calc grid square Default impact normal
						BiVector f_BlockCenter((((float)m_gridX * GRIDSIZE) + (GRIDSIZE / 2.0f)),
												(((float)m_gridY * GRIDSIZE) + (GRIDSIZE / 2.0f)),
												(((float)(m_gridZ * -1) * GRIDSIZE) + (GRIDSIZE / 2.0f)));

						f_Collision->Normal.m_X = f_Front.m_X - f_BlockCenter.m_X;
						f_Collision->Normal.m_X = f_Front.m_Y - f_BlockCenter.m_Y;
						f_Collision->Normal.m_Z = f_Front.m_Z - f_BlockCenter.m_Z;

						f_Collision->Normal.acNormalize();

						//default building return
						return true;
						}

					if(GetActive(Xacting, Yacting, Zacting) == true)
						{
						float f_CubeMinX = ((float)m_gridX * GRIDSIZE) + (Xacting * BLOCK_RENDER);
						float f_CubeMinY = ((float)m_gridY * GRIDSIZE) + (Yacting * BLOCK_RENDER);
						float f_CubeMinZ = ((float)(m_gridZ * -1) * GRIDSIZE) + (Zacting * BLOCK_RENDER);

						if(m_gridX < 0)
							{
							f_CubeMinX -= BLOCK_RENDER;
							}

						if(m_gridY < 0)
							{
							f_CubeMinY -= BLOCK_RENDER;
							}

						if((m_gridZ * -1) < 0) // swk
							{
							f_CubeMinZ -= BLOCK_RENDER;
							}

						float f_CubeMaxX = f_CubeMinX + BLOCK_RENDER;
						float f_CubeMaxY = f_CubeMinY + BLOCK_RENDER;
						float f_CubeMaxZ = f_CubeMinZ + BLOCK_RENDER;

						if( (f_Front.m_X >= f_CubeMinX) &&
							(f_Front.m_X < f_CubeMaxX) &&
							(f_Front.m_Y >= f_CubeMinY) &&
							(f_Front.m_Y < f_CubeMaxY) &&
							(f_Front.m_Z >= f_CubeMinZ) &&
							(f_Front.m_Z < f_CubeMaxZ))
							{
							// Impact! calc grid square impact normal
							f_Collide = true;

							f_Collision->Impact.acSet(f_Front.m_X, f_Front.m_Y, f_Front.m_Z);

							f_Collision->m_VXBlock.m_BIDX = Xacting;
							f_Collision->m_VXBlock.m_BIDY = Yacting;
							f_Collision->m_VXBlock.m_BIDZ = Zacting;

#if 0
							SetColour(x, y, z, 1.0f, 0.5, 0.8, 1.0f);
#endif

							float f_AmpValue = (BLOCK_RENDER / VOXEL_MARCH_DIV) * 1.5f;

							float f_MinDiffX = f_Front.m_X - f_CubeMinX;
							float f_MaxDiffX = f_CubeMaxX - f_Front.m_X;

							float f_MinDiffY = f_Front.m_Y - f_CubeMinY;
							float f_MaxDiffY = f_CubeMaxY - f_Front.m_Y;

							float f_MinDiffZ = f_Front.m_Z - f_CubeMinZ;
							float f_MaxDiffZ = f_CubeMaxZ - f_Front.m_Z;

							uint f_Bok[3];

							f_Bok[0] = 0; // 0 Min - 1 Max
							f_Bok[1] = 0;
							f_Bok[2] = 0; // 2 Min < AmpValue - 3 Max < AmpValue

							if(f_MinDiffX < f_MaxDiffX) // MinX
								{
								if(f_MinDiffX < f_AmpValue)
									{
									f_Bok[0] = 2;
									}
								else
									{
									f_Bok[0] = 0;
									}
								}
							else
								{
								if(f_MaxDiffX < f_AmpValue)
									{
									f_Bok[0] = 3;
									}
								else
									{
									f_Bok[0] = 1;
									}
								}

							if(f_MinDiffY < f_MaxDiffY) //MinX - MinY
								{
								if(f_MinDiffY < f_AmpValue)
									{
									f_Bok[1] = 2;
									}
								else
									{
									f_Bok[1] = 0;
									}
								}
							else
								{
								if(f_MaxDiffY < f_AmpValue)
									{
									f_Bok[1] = 3;
									}
								else
									{
									f_Bok[1] = 1;
									}
								}

							if(f_MinDiffZ < f_MaxDiffZ) //MinX - MinY - MinZ
								{
								if(f_MinDiffZ < f_AmpValue)
									{
									f_Bok[2] = 2;
									}
								else
									{
									f_Bok[2] = 0;
									}
								}
							else
								{
								if(f_MaxDiffZ < f_AmpValue)
									{
									f_Bok[2] = 3;
									}
								else
									{
									f_Bok[2] = 1;
									}
								}

							 // First test all main directions X- X+ Y- Y+ Z- Z+
							//
							if((f_Bok[0] == 3) && (f_Bok[1] < 2) && (f_Bok[2] < 2))
								{
								f_Collision->Normal.m_X = 1.0f; // X+
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}
									
							if((f_Bok[0] == 2) && (f_Bok[1] < 2) && (f_Bok[2] < 2))
								{
								f_Collision->Normal.m_X = -1.0f; // X-
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[1] == 3) && (f_Bok[0] < 2) && (f_Bok[2] < 2))
								{
								f_Collision->Normal.m_X = 0.0f; // Y+
								f_Collision->Normal.m_Y = 1.0f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[1] == 2) && (f_Bok[0] < 2) && (f_Bok[2] < 2))
								{
								f_Collision->Normal.m_X = 0.0f; // Y-
								f_Collision->Normal.m_Y = -1.0f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[2] == 3) && (f_Bok[0] < 2) && (f_Bok[1] < 2))
								{
								f_Collision->Normal.m_X = 0.0f; // Z+
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = 1.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[2] == 2) && (f_Bok[0] < 2) && (f_Bok[1] < 2))
								{
								f_Collision->Normal.m_X = 0.0f; // Z-
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = -1.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							 // ? ok test four corners Z-
							//
							if((f_Bok[0] == 2) && (f_Bok[1] == 3) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Y+ Z-
								f_Collision->Normal.m_Y = 0.5f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 2) && (f_Bok[1] == 2) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Y- Z-
								f_Collision->Normal.m_Y = -0.5f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[1] == 3) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Y+ Z-
								f_Collision->Normal.m_Y = 0.5f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[1] == 2) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Y- Z-
								f_Collision->Normal.m_Y = -0.5f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							 // ? ok test four corners Z+
							//
							if((f_Bok[0] == 2) && (f_Bok[1] == 3) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Y+ Z+
								f_Collision->Normal.m_Y = 0.5f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 2) && (f_Bok[1] == 2) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Y- Z+
								f_Collision->Normal.m_Y = -0.5f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[1] == 3) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Y+ Z+
								f_Collision->Normal.m_Y = 0.5f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[1] == 2) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Y- Z+
								f_Collision->Normal.m_Y = -0.5f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							 // ? - check all 12 edges extreme
							//
							if((f_Bok[0] == 2) && (f_Bok[1] == 3))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Y+
								f_Collision->Normal.m_Y = 0.5f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[1] == 3))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Y+
								f_Collision->Normal.m_Y = 0.5f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 2) && (f_Bok[1] == 2))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Y-
								f_Collision->Normal.m_Y = -0.5f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[1] == 2))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Y-
								f_Collision->Normal.m_Y = -0.5f;
								f_Collision->Normal.m_Z = 0.0f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 2) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Z+
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Z+
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 2) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = -0.5f; //X-Z-
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[0] == 3) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = 0.5f; //X+Z-
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[1] == 2) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = 0.0f; //Z-Y-
								f_Collision->Normal.m_Y = -0.5f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[1] == 3) && (f_Bok[2] == 2))
								{
								f_Collision->Normal.m_X = 0.0f; //Z-Y+
								f_Collision->Normal.m_Y = 0.5f;
								f_Collision->Normal.m_Z = -0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[1] == 2) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = -0.5f; //Z+Y-
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							if((f_Bok[1] == 3) && (f_Bok[2] == 3))
								{
								f_Collision->Normal.m_X = 0.5f; //Z+Y+
								f_Collision->Normal.m_Y = 0.0f;
								f_Collision->Normal.m_Z = 0.5f;

								f_Collision->Normal.acNormalize();

								return f_Collide;
								}

							// calc grid square Default impact normal
							BiVector f_BlockCenter((((float)m_gridX * GRIDSIZE) + ((((float)Xacting * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE))),
													(((float)m_gridY * GRIDSIZE) + ((((float)Yacting * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE))),
													(((float)(m_gridZ * -1) * GRIDSIZE) + ((((float)Zacting * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE))));

							f_Collision->Normal.m_X = f_Front.m_X - f_BlockCenter.m_X;
							f_Collision->Normal.m_X = f_Front.m_Y - f_BlockCenter.m_Y;
							f_Collision->Normal.m_Z = f_Front.m_Z - f_BlockCenter.m_Z;

							f_Collision->Normal.acNormalize();

							//default normal return || Cube::random(x, y, z);
							return f_Collide;
							}
						}

#ifdef VOXELDMG_AREAEFFECT
					}
				}
			}
#endif

		}
	else //Shift onto Next VoxelGrid
		{
		f_Collision->Rear = f_Vec1;

		f_Collision->Normal.m_X = 0.0f;
		f_Collision->Normal.m_Y = 0.0f;
		f_Collision->Normal.m_Z = 0.0f;

		return false;
		}

	return f_Collide;
}

bool VoxelGrid::CollideCheckPoint(BiVector f_FrontPoint, BiVector f_RearPoint, BiVector* f_ImpactPoint, BiVector* f_ImpactNormal)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRIDSIZE = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	Cube::BiVector f_Vec1 = f_FrontPoint;

	bool f_Collide = false;

	if((f_Vec1.m_X >= ((float)m_gridX * GRIDSIZE)) &&
		(f_Vec1.m_X < (((float)m_gridX + 1) * GRIDSIZE)) &&
		(f_Vec1.m_Y >= ((float)m_gridY * GRIDSIZE)) &&
		(f_Vec1.m_Y < (((float)m_gridY + 1) * GRIDSIZE)) &&
		(f_Vec1.m_Z >= ((float)(m_gridZ * -1) * GRIDSIZE)) &&
		(f_Vec1.m_Z < (((float)(m_gridZ * -1) + 1) * GRIDSIZE)))
		{
		int f_Xclip = (int)f_Vec1.m_X / (int)BLOCK_RENDER;
		int f_Yclip = (int)f_Vec1.m_Y / (int)BLOCK_RENDER;
		int f_Zclip = (int)f_Vec1.m_Z / (int)BLOCK_RENDER;

		int Xacting = f_Xclip - m_Xpos;
		int Yacting = f_Yclip - m_Ypos;
		int Zacting = f_Zclip - m_Zpos;

		if((m_rebuild > 0) && (m_setup == false))
			{
			f_ImpactPoint->m_X = f_Vec1.m_X;
			f_ImpactPoint->m_Y = f_Vec1.m_Y;
			f_ImpactPoint->m_Z = f_Vec1.m_Z;

			// calc grid Default impact normal
			BiVector f_BlockCenter((((float)m_gridX * GRIDSIZE) + (GRIDSIZE / 2.0f)),
									(((float)m_gridY * GRIDSIZE) + (GRIDSIZE / 2.0f)),
									(((float)(m_gridZ * -1) * GRIDSIZE) + (GRIDSIZE / 2.0f)));

			f_ImpactNormal->m_X = f_Vec1.m_X - f_BlockCenter.m_X;
			f_ImpactNormal->m_Y = f_Vec1.m_Y - f_BlockCenter.m_Y;
			f_ImpactNormal->m_Z = f_Vec1.m_Z - f_BlockCenter.m_Z;

			f_ImpactNormal->acNormalize();

			//default building return
			return true;
			}

		if(GetActive(Xacting, Yacting, Zacting) == true)
			{
			f_Collide = true;

			*(f_ImpactPoint) = f_Vec1;

			f_ImpactNormal->m_X = 0.0f;
			f_ImpactNormal->m_Y = 1.0f;
			f_ImpactNormal->m_Z = 0.0f;
			}
		}

	return f_Collide;
}

int VoxelGridManager::acSearch_WithHash(std::string f_Hash)
{
	for(int f_Int = 0; f_Int < m_VoxelGridsVector.size(); f_Int++)
		{
		std::shared_ptr<VoxelGrid> f_Grid = m_VoxelGridsVector[f_Int];

		if(f_Grid->m_Hash.compare(f_Hash) == 0)
			{
			return f_Int;
			}
		}

	return -5;
}

int VoxelGridManager::acSearch_WithHash_Limb(std::string f_Hash)
{
	for(int f_Int = 0; f_Int < m_VoxelLimbVector.size(); f_Int++)
		{
		std::shared_ptr<VoxelLimb> f_Limb = m_VoxelLimbVector[f_Int];

		if(f_Limb->m_Hash.compare(f_Hash) == 0)
			{
			return f_Int;
			}
		}

	return -5;
}

int VoxelGrid::acSearch_WithHash_Limb(std::string f_Hash)
{
	for(int f_Int = 0; f_Int < m_vec_VoxelLimb.size(); f_Int++)
		{
		std::shared_ptr<VoxelLimb> f_Limb = m_vec_VoxelLimb[f_Int];

		if(f_Limb->m_Hash.compare(f_Hash) == 0)
			{
			return f_Int;
			}
		}

	return -5;
}

void VoxelGridManager::Make_Gen_Rand_Small_Building(std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	   ////        ////
	  //..	Rand  ..//
	 //..  Small ..//
	////        ////
#if 0
	int f_FloorNom = (Cube::randomFac() % WORLD_SMALLBG_HEIGHT_MAX) + 1;
	int f_RoomNom[WORLD_SMALLBG_HEIGHT_MAX];
	int f_WallNom[WORLD_SMALLBG_HEIGHT_MAX];
	int f_SurfaceNom[WORLD_SMALLBG_HEIGHT_MAX];
	int f_DoorNom[WORLD_SMALLBG_HEIGHT_MAX];

#if 0
	int f_WindowNom[WORLD_SMALL_BUILDING_HEIGHT_MAX];
#endif

	for(int f_Count = 0; f_Count < f_FloorNom; f_Count++)
		{
		f_RoomNom[f_Count] = Cube::randomFac() % (((f_Building->m_Width * f_Building->m_Length) / 40) + 1);
		f_WallNom[f_Count] = f_RoomNom[f_Count] - 1;
		f_SurfaceNom[f_Count] = Cube::randomFac() % (((f_Building->m_Width * f_Building->m_Length) / 40) + 1);
		f_DoorNom[f_Count] = Cube::randomFac() % (((f_Building->m_Width * f_Building->m_Length) / 60) + 1);

		//alpha blending required
#if 0
		f_WindowNom[f_Count] = Cube::randomFac() % (((f_Building->m_Width * f_Building->m_Length) / 20) + 1);
#endif
		}
#endif

	   ////////////////
	  //  Machine   //
	 //   Build    //
	//............//
	g_VoxelGridManager->Make_Gen_Building(BuildingType_SmallBuilding, f_Building->m_Pos, f_Building, f_VoxelGrid);

#if 0
	switch(f_RoomNom[0])
		{
		case 0:
			{
#if 0
			printf("make WARNING Small Rand Building contains zero rooms\n");
#endif
			}break;

		case 1:
			{
			//Unused
			}break;

		case 2:
			{
			if(Cube::randomFac() % 5 >= 3)
				{
				if(((f_Building->m_Length - 4) > 1) &&
				   ((f_Building->m_Height - 2) > 0))
					{
					g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, 3, f_Building->m_Length - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
					}
				}
			else
				{
				if(((f_Building->m_Width - 4) > 1) &&
				   ((f_Building->m_Height - 2) > 0))
					{
					g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
					}
				}
			}break;

		case 3:
			{
			int f_IntFinger = Cube::randomFac() % 4;

			if(f_IntFinger == 0)
				{
				if(f_Building->m_Length > f_Building->m_Width)
					{
					if(((f_Building->m_Width - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						float f_IncZ = (((float)f_Building->m_Length / 3.0f) * (float)BLOCK_RENDER) / 2.0f;
						float f_Upper = f_Building->m_Pos.m_Z + f_IncZ;
						float f_Lower = f_Building->m_Pos.m_Z - f_IncZ;
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X, f_Upper, f_Building->m_Pos.m_Z), f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X, f_Lower, f_Building->m_Pos.m_Z), f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					}
				else
					{
					if(((f_Building->m_Length - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						float f_IncX = (((float)f_Building->m_Width / 3.0f) * (float)BLOCK_RENDER) / 2.0f;
						float f_Left = f_Building->m_Pos.m_X + f_IncX;
						float f_Right = f_Building->m_Pos.m_X - f_IncX;
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Left, f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z), 3, f_Building->m_Length - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Right, f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z), 3, f_Building->m_Length - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					}
				}
			else if(f_IntFinger == 1)
				{
				int f_RandomFingerInt = Cube::randomFac() % 4;

				    //////////////////
				  // Orientation
				 //
				//..
				//.. Separate Upper
				if(f_RandomFingerInt == 0)
					{
					if(((f_Building->m_Width - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}

					if((((f_Building->m_Length / 2) - 4) > 1) &&
						((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X, f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z + ((float)f_Building->m_Length / 2.0f) * BLOCK_RENDER), 3, (f_Building->m_Length / 2) - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					} //.. Wall Lower
				else if(f_RandomFingerInt == 1)
					{
					if(((f_Building->m_Width - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}

					if((((f_Building->m_Length / 2) - 4) > 1) &&
						((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X, f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z - ((float)f_Building->m_Length / 2.0f) * BLOCK_RENDER), 3, (f_Building->m_Length / 2) - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					} //.. Wall Lower
				else if(f_RandomFingerInt == 2)
					{
					if((f_Building->m_Length - 4 > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, 3, f_Building->m_Length - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}

					if((((f_Building->m_Width / 2) - 4) > 1) &&
						((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X - (((float)f_Building->m_Width / 2.0f) * BLOCK_RENDER), f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z), (f_Building->m_Width / 2) - 4, (f_Building->m_Length / 2) - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					} //.. Wall Left
				else if(f_RandomFingerInt == 3)
					{
					if((f_Building->m_Length - 4 > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, 3, f_Building->m_Length - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}

					if((((f_Building->m_Width / 2) - 4) > 1) &&
						((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X + (((float)f_Building->m_Width / 2.0f) * BLOCK_RENDER), f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z), (f_Building->m_Width / 2) - 4, (f_Building->m_Length / 2) - 4, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					}
				else
					{
					//error
					throw;
					}
				}
			else if(f_IntFinger == 2)
				{
				int f_RandomisedFingerInt = Cube::randomFac() % 2;

				if(f_RandomisedFingerInt == 0)
					{
					if(((f_Building->m_Width - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					if(((f_Building->m_Width - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X, f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z + ((f_Building->m_Length / 2.0f) * BLOCK_RENDER)), f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					}
				else if(f_RandomisedFingerInt == 1)
					{
					if(((f_Building->m_Width - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_Building->m_Pos, f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					if(((f_Building->m_Width - 4) > 1) &&
					   ((f_Building->m_Height - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Building->m_Pos.m_X, f_Building->m_Pos.m_Y, f_Building->m_Pos.m_Z - ((f_Building->m_Length / 2.0f) * BLOCK_RENDER)), f_Building->m_Width - 4, 3, f_Building->m_Height - 2, f_Building->m_Pos, f_VoxelGrid);
						}
					}
				}
			}break;
		}
#endif
}

int ag_min(int f_In, int f_min)
{
	if(f_In >= f_min)
		{
		return f_In;
		}

	return f_min;
}

int ag_max(int f_In, int f_max)
{
	if(f_In < f_max)
		{
		return f_In;
		}

	return f_max;
}

float ag_min(float f_In, float f_min)
{
	if(f_In >= f_min)
		{
		return f_In;
		}

	return f_min;
}

float ag_max(float f_In, float f_max)
{
	if(f_In < f_max)
		{
		return f_In;
		}

	return f_max;
}

bool Building::acPush_Grid(std::shared_ptr<VoxelGrid> f_Grid)
{
	if(m_ON == true)
		{
		return false;
		}

	int f_ScreenMinX = (m_MinX - f_Grid->m_Xpos);
	int f_ScreenMinY = (m_MinY - f_Grid->m_Ypos);
	int f_ScreenMinZ = (m_MinZ - f_Grid->m_Zpos);

	int f_ScreenMaxX = (m_MaxX - f_Grid->m_Xpos);
	int f_ScreenMaxY = (m_MaxY - f_Grid->m_Ypos);
	int f_ScreenMaxZ = (m_MaxZ - f_Grid->m_Zpos);

	if( ((f_ScreenMinX < VoxelGrid::VOXEL_GRID_SIZE) && (f_ScreenMaxX > 0)) &&
		((f_ScreenMinY < VoxelGrid::VOXEL_GRID_SIZE) && (f_ScreenMaxY > 0)) &&
		((f_ScreenMinZ < VoxelGrid::VOXEL_GRID_SIZE) && (f_ScreenMaxZ > 0)))
		{
		int f_AddX = ag_max(f_ScreenMaxX, VoxelGrid::VOXEL_GRID_SIZE) - ag_min(f_ScreenMinX, 0);
		int f_AddY = ag_max(f_ScreenMaxY, VoxelGrid::VOXEL_GRID_SIZE) - ag_min(f_ScreenMinY, 0);
		int f_AddZ = ag_max(f_ScreenMaxZ, VoxelGrid::VOXEL_GRID_SIZE) - ag_min(f_ScreenMinZ, 0);

		if(m_Perc_X < m_Width)
			{
			m_Perc_X += f_AddX;
			}

		if(m_Perc_Y < m_Height)
			{
			m_Perc_Y += f_AddY;
			}

		if(m_Perc_Z < m_Length)
			{
			m_Perc_Z += f_AddZ;
			}
		}

	if( (m_Perc_X == m_Width) &&
		(m_Perc_Y == m_Height) &&
		(m_Perc_Z == m_Length))
		{
		m_ON = true;

		return false;
		}

	return true;
}

void VoxelGridManager::Make_Gen_Rand_Small_Lighting(std::shared_ptr<LightStr> f_LightStr, std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	   ////////////////
	  //  Machine   //
	 //   Build    //
	//............//
	Make_Gen_Building_Light(BuildingType_LampPost, f_Building->m_Pos, f_Building, f_VoxelGrid);
}

bool VoxelGridManager::Make_Place_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	   ////        ////
	  //..	Rand  ..//
	 //..  Small ..//
	////        ////
	int f_FloorNom = (Cube::randomFac() % WORLD_SMALLBG_HEIGHT_MAX) + 1;
	int f_RoomNom[WORLD_SMALLBG_HEIGHT_MAX];
	int f_WallNom[WORLD_SMALLBG_HEIGHT_MAX];
	int f_SurfaceNom[WORLD_SMALLBG_HEIGHT_MAX];
	int f_DoorNom[WORLD_SMALLBG_HEIGHT_MAX];

#if 0
	int f_WindowNom[WORLD_SMALL_BUILDING_HEIGHT_MAX];
#endif

	for(int f_Count = 0; f_Count < f_FloorNom; f_Count++)
		{
		f_RoomNom[f_Count] = Cube::randomFac() % (((vWidth * vLength) / 40) + 1);
		f_WallNom[f_Count] = f_RoomNom[f_Count] - 1;
		f_SurfaceNom[f_Count] = Cube::randomFac() % (((vWidth * vLength) / 40) + 1);
		f_DoorNom[f_Count] = Cube::randomFac() % (((vWidth * vLength) / 60) + 1);

		//alpha blending required
#if 0
		f_WindowNom[f_Count] = Cube::randomFac() % (((vWidth * vLength) / 20) + 1);
#endif
		}

	   ////////////////
	  //  Machine   //
	 //   Place    //
	//............//

	return g_VoxelGridManager->Make_Place_Building(BuildingType_SmallBuilding, f_FloorCenter, vWidth, vLength, vHeight, f_Position, f_VoxelGrid);
}

// Base Building Function
void VoxelGridManager::Make_Gen_Building(uint8 f_BuildingType, BiVector f_FloorCenter, std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER;

	  /////////////////////////
	 // Min/Max by 'Block'
	//
#if 0
	float f_MinX = f_FloorCenter.m_X - ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = (f_FloorCenter.m_Z * -1.0) - ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);

	float f_MaxX = f_FloorCenter.m_X + ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MaxY = f_FloorCenter.m_Y + (f_Building->m_Height * BLOCK_RENDER);
	float f_MaxZ = (f_FloorCenter.m_Z * -1.0f) + ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);
#else
	float f_MinX = f_FloorCenter.m_X - ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = f_FloorCenter.m_Z - ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);

	float f_MaxX = f_FloorCenter.m_X + ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MaxY = f_FloorCenter.m_Y + (f_Building->m_Height * BLOCK_RENDER);
	float f_MaxZ = f_FloorCenter.m_Z + ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);
#endif

	// Remain and save in Block World Space

	f_Building->m_MinX = f_MinX / BLOCK_RENDER;
	f_Building->m_MinY = f_MinY / BLOCK_RENDER;
	f_Building->m_MinZ = f_MinZ / BLOCK_RENDER;

	f_Building->m_MaxX = f_MaxX / BLOCK_RENDER;
	f_Building->m_MaxY = f_MaxY / BLOCK_RENDER;
	f_Building->m_MaxZ = f_MaxZ / BLOCK_RENDER;

	   ///////////////////////
	  // Interior
	 // Cement
	// X
	float f_Min_CementXmn = f_MinX;
	float f_Max_CementXmn = f_MinX + (1.15f * (BLOCK_RENDER));
	float f_Min_CementXen = f_MaxX - (1.15f * (BLOCK_RENDER));
	float f_Max_CementXen = f_MaxX;
	// Y
	float f_Min_CementYmn = f_MinY;
	float f_Max_CementYmn = f_MinY + (1.15f * (BLOCK_RENDER));
	float f_Min_CementYen = f_MaxY - (1.15f * (BLOCK_RENDER));
	float f_Max_CementYen = f_MaxY;
	// Z
	float f_Min_CementZmn = f_MinZ;
	float f_Max_CementZmn = f_MinZ + (1.15f * (BLOCK_RENDER));
	float f_Min_CementZen = f_MaxZ - (1.15f * (BLOCK_RENDER));
	float f_Max_CementZen = f_MaxZ;

	  ////////////////////
	 // Brick
	// X
	float f_Min_BrickXmn = f_Max_CementXmn;
	float f_Max_BrickXmn = f_Max_CementXmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickXen = f_Min_CementXen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickXen = f_Min_CementXen;
	// Y
	float f_Min_BrickYmn = f_Max_CementYmn;
	float f_Max_BrickYmn = f_Max_CementYmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickYen = f_Min_CementYen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickYen = f_Min_CementYen;
	// Z
	float f_Min_BrickZmn = f_Max_CementZmn;
	float f_Max_BrickZmn = f_Max_CementZmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickZen = f_Min_CementZen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickZen = f_Min_CementZen;

	  ////////////////////
	 // Plaster
	// X
	float f_Min_PlasterXmn = f_Max_BrickXmn;
	float f_Max_PlasterXmn = f_Max_BrickXmn + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterXen = f_Min_BrickXen - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterXen = f_Min_BrickXen;
	// Y
	float f_Min_PlasterYmn = f_Max_BrickYmn;
	float f_Max_PlasterYmn = f_Max_BrickYmn + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterYen = f_Min_BrickYen - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterYen = f_Min_BrickYen;
	// Z
	float f_Min_PlasterZmn = f_Max_BrickZmn;
	float f_Max_PlasterZmn = f_Max_BrickZmn + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterZen = f_Min_BrickZen - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterZen = f_Min_BrickZen;

	std::shared_ptr<VoxelLimb> f_BuildingLimb = nullptr;

	   //////////////////////
	  // 6 Cement Blocks
	 // 
	// Z-
	bool f_Collide = false;

	f_Collide = Make_Gen_Cuboid(BlockType_Cement, f_Max_CementXmn, f_Max_CementYmn, f_Min_CementZmn, f_Min_CementXen, f_Min_CementYen, f_Max_CementZmn, 0.65f * 255, 0.65f * 255, 0.65f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Cement, f_Max_CementXmn, f_Max_CementYmn, f_Min_CementZen, f_Min_CementXen, f_Min_CementYen, f_Max_CementZen, 0.65f * 255, 0.65f * 255, 0.65f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X-
	f_Collide = Make_Gen_Cuboid(BlockType_Cement, f_Min_CementXmn, f_Max_CementYmn, f_Max_CementZmn, f_Max_CementXmn, f_Min_CementYen, f_Max_CementZen, 0.65f * 255, 0.65f * 255, 0.65f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X+
	f_Collide = Make_Gen_Cuboid(BlockType_Cement, f_Min_CementXen, f_Max_CementYmn, f_Max_CementZmn, f_Max_CementXen, f_Min_CementYen, f_Max_CementZen, 0.65f * 255, 0.65f * 255, 0.65f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z-
	f_Collide = Make_Gen_Cuboid(BlockType_Cement, f_Min_CementXmn, f_Max_CementYmn, f_Max_CementZmn, f_Max_CementXen, f_Min_CementYmn, f_Max_CementZen, 0.65f * 255, 0.65f * 255, 0.65f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Cement, f_Min_CementXmn, f_Max_CementYen, f_Max_CementZmn, f_Max_CementXen, f_Min_CementYmn, f_Max_CementZen, 0.65f * 255, 0.65f * 255, 0.65f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	  // 6 Brick Blocks
	 // 
	// Z-
	f_Collide = Make_Gen_Cuboid(BlockType_Brick, f_Max_BrickXmn, f_Max_BrickYmn, f_Min_BrickZmn, f_Min_BrickXen, f_Min_BrickYen, f_Max_BrickZmn, 1.0f * 255, 0.05f * 255, 0.05f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Brick, f_Max_BrickXmn, f_Max_BrickYmn, f_Min_BrickZen, f_Min_BrickXen, f_Min_BrickYen, f_Max_BrickZen, 1.0f * 255, 0.05f * 255, 0.05f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X-
	f_Collide = Make_Gen_Cuboid(BlockType_Brick, f_Min_BrickXmn, f_Max_BrickYmn, f_Max_BrickZmn, f_Max_BrickXmn, f_Min_BrickYen, f_Max_BrickZen, 1.0f * 255, 0.05f * 255, 0.05f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X+
	f_Collide = Make_Gen_Cuboid(BlockType_Brick, f_Min_BrickXen, f_Max_BrickYmn, f_Max_BrickZmn, f_Max_BrickXen, f_Min_BrickYen, f_Max_BrickZen, 1.0f * 255, 0.05f * 255, 0.05f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z-
	f_Collide = Make_Gen_Cuboid(BlockType_Brick, f_Min_BrickXmn, f_Max_BrickYmn, f_Max_BrickZmn, f_Max_BrickXen, f_Min_BrickYmn, f_Max_BrickZen, 1.0f * 255, 0.05f * 255, 0.05f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Brick, f_Min_BrickXmn, f_Max_BrickYen, f_Max_BrickZmn, f_Max_BrickXen, f_Min_BrickYmn, f_Max_BrickZen, 1.0f * 255, 0.05f * 255, 0.05f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	  // 6 Plaster Blocks
	 // 
	// Z-
	f_Collide = Make_Gen_Cuboid(BlockType_Plaster, f_Max_PlasterXmn, f_Max_PlasterYmn, f_Min_PlasterZmn, f_Min_PlasterXen, f_Min_PlasterYen, f_Max_PlasterZmn, 0.99f * 255, 0.97f * 255, 0.93f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Plaster, f_Max_PlasterXmn, f_Max_PlasterYmn, f_Min_PlasterZen, f_Min_PlasterXen, f_Min_PlasterYen, f_Max_PlasterZen, 0.99f * 255, 0.97f * 255, 0.93f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X-
	f_Collide = Make_Gen_Cuboid(BlockType_Plaster, f_Min_PlasterXmn, f_Max_PlasterYmn, f_Max_PlasterZmn, f_Max_PlasterXmn, f_Min_PlasterYen, f_Max_PlasterZen, 0.99f * 255, 0.97f * 255, 0.93f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X+
	f_Collide = Make_Gen_Cuboid(BlockType_Plaster, f_Min_PlasterXen, f_Max_PlasterYmn, f_Max_PlasterZmn, f_Max_PlasterXen, f_Min_PlasterYen, f_Max_PlasterZen, 0.99f * 255, 0.97f * 255, 0.93f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z-
	f_Collide = Make_Gen_Cuboid(BlockType_Plaster, f_Min_PlasterXmn, f_Max_PlasterYmn, f_Max_PlasterZmn, f_Max_PlasterXen, f_Min_PlasterYmn, f_Max_PlasterZen, 0.99f * 255, 0.97f * 255, 0.93f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Plaster, f_Min_PlasterXmn, f_Max_PlasterYen, f_Max_PlasterZmn, f_Max_PlasterXen, f_Min_PlasterYmn, f_Max_PlasterZen, 0.99f * 255, 0.97f * 255, 0.93f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	//END Make_Gen_Building
}

void VoxelGridManager::Make_Gen_Building_Light(uint8 f_BuildingType, BiVector f_FloorCenter, std::shared_ptr<Building> f_Building, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER;

	  /////////////////////////
	 // Min/Max by 'Block'
	//
#if 0
	float f_MinX = f_FloorCenter.m_X - ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = (f_FloorCenter.m_Z * -1.0) - ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);

	float f_MaxX = f_FloorCenter.m_X + ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MaxY = f_FloorCenter.m_Y + (f_Building->m_Height * BLOCK_RENDER);
	float f_MaxZ = (f_FloorCenter.m_Z * -1.0f) + ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);
#else
	float f_MinX = f_FloorCenter.m_X - ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = f_FloorCenter.m_Z - ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);

	float f_MaxX = f_FloorCenter.m_X + ((f_Building->m_Width / 2.0f) * BLOCK_RENDER);
	float f_MaxY = f_FloorCenter.m_Y + (f_Building->m_Height * BLOCK_RENDER);
	float f_MaxZ = f_FloorCenter.m_Z + ((f_Building->m_Length / 2.0f) * BLOCK_RENDER);
#endif

	// Remain and save in Block World Space

	f_Building->m_MinX = f_MinX / BLOCK_RENDER;
	f_Building->m_MinY = f_MinY / BLOCK_RENDER;
	f_Building->m_MinZ = f_MinZ / BLOCK_RENDER;

	f_Building->m_MaxX = f_MaxX / BLOCK_RENDER;
	f_Building->m_MaxY = f_MaxY / BLOCK_RENDER;
	f_Building->m_MaxZ = f_MaxZ / BLOCK_RENDER;

	   ///////////////////////
	  // Interior
	 // Cement
	// X
	float f_Min_ShellXmn = f_MinX;
	float f_Max_ShellXmn = f_MinX + (1.15f * (BLOCK_RENDER));
	float f_Min_ShellXen = f_MaxX - (1.15f * (BLOCK_RENDER));
	float f_Max_ShellXen = f_MaxX;
	// Y
	float f_Min_ShellYmn = f_MinY;
	float f_Max_ShellYmn = f_MinY + (1.15f * (BLOCK_RENDER));
	float f_Min_ShellYen = f_MaxY - (1.15f * (BLOCK_RENDER));
	float f_Max_ShellYen = f_MaxY;
	// Z
	float f_Min_ShellZmn = f_MinZ;
	float f_Max_ShellZmn = f_MinZ + (1.15f * (BLOCK_RENDER));
	float f_Min_ShellZen = f_MaxZ - (1.15f * (BLOCK_RENDER));
	float f_Max_ShellZen = f_MaxZ;

	std::shared_ptr<VoxelLimb> f_BuildingLimb = nullptr;

	   //////////////////////
	  // 6 Shell Blocks
	 // 
	// Z-
	bool f_Collide = false;

	f_Collide = Make_Gen_Cuboid(BlockType_Steel, f_Max_ShellXmn, f_Max_ShellYmn, f_Min_ShellZmn, f_Min_ShellXen, f_Min_ShellYen, f_Max_ShellZmn, 0.25f * 255, 0.55f * 255, 0.15f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Steel, f_Max_ShellXmn, f_Max_ShellYmn, f_Min_ShellZen, f_Min_ShellXen, f_Min_ShellYen, f_Max_ShellZen, 0.25f * 255, 0.55f * 255, 0.15f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X-
	f_Collide = Make_Gen_Cuboid(BlockType_Steel, f_Min_ShellXmn, f_Max_ShellYmn, f_Max_ShellZmn, f_Max_ShellXmn, f_Min_ShellYen, f_Max_ShellZen, 0.25f * 255, 0.55f * 255, 0.15f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// X+
	f_Collide = Make_Gen_Cuboid(BlockType_Steel, f_Min_ShellXen, f_Max_ShellYmn, f_Max_ShellZmn, f_Max_ShellXen, f_Min_ShellYen, f_Max_ShellZen, 0.25f * 255, 0.55f * 255, 0.15f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z-
	f_Collide = Make_Gen_Cuboid(BlockType_Steel, f_Min_ShellXmn, f_Max_ShellYmn, f_Max_ShellZmn, f_Max_ShellXen, f_Min_ShellYmn, f_Max_ShellZen, 0.25f * 255, 0.55f * 255, 0.15f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	// Z+
	f_Collide = Make_Gen_Cuboid(BlockType_Steel, f_Min_ShellXmn, f_Max_ShellYen, f_Max_ShellZmn, f_Max_ShellXen, f_Min_ShellYmn, f_Max_ShellZen, 0.25f * 255, 0.55f * 255, 0.15f * 255, 1.0f * 255, f_VoxelGrid, f_BuildingLimb, true);

	//END Make_Gen_Building
}

bool VoxelGridManager::Make_Gen_Cuboid(BlockType f_BlockType, float f_MinX, float f_MinY, float f_MinZ, float f_MaxX, float f_MaxY, float f_MaxZ, int VColorRed, int VColorGreen, int VColorBlue, int VColorAlpha, std::shared_ptr<VoxelGrid> f_VoxelGrid, std::shared_ptr<VoxelLimb> f_CurrentLimb, bool f_NewLimb)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRIDSIZE = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	bool f_Collide = false;

	  ///////////////////
	 // Min - Max
	//
#if 1
	if((f_MinX < (((float)f_VoxelGrid->m_gridX + 1) * GRIDSIZE)) &&
		((((float)f_VoxelGrid->m_gridX) * GRIDSIZE) < f_MaxX) &&
		(f_MinY < (((float)f_VoxelGrid->m_gridY + 1) * GRIDSIZE)) &&
		((((float)f_VoxelGrid->m_gridY) * GRIDSIZE) < f_MaxY) &&
		(f_MinZ < (((float)(f_VoxelGrid->m_gridZ * -1) + 1) * GRIDSIZE)) &&
		((((float)(f_VoxelGrid->m_gridZ * -1)) * GRIDSIZE) < f_MaxZ))
#else
	if((f_MinX < (((float)f_VoxelGrid->m_gridX + 1) * GRIDSIZE)) &&
		((((float)f_VoxelGrid->m_gridX) * GRIDSIZE) < f_MaxX) &&
		(f_MinY < (((float)f_VoxelGrid->m_gridY + 1) * GRIDSIZE)) &&
		((((float)f_VoxelGrid->m_gridY) * GRIDSIZE) < f_MaxY) &&
		(f_MinZ < (((float)f_VoxelGrid->m_gridZ + 1) * GRIDSIZE)) &&
		((((float)f_VoxelGrid->m_gridZ) * GRIDSIZE) < f_MaxZ))
#endif
		{
		int f_Building_MinX = f_MinX / BLOCK_RENDER;
		int f_Building_MinY = f_MinY / BLOCK_RENDER;
		int f_Building_MinZ = f_MinZ / BLOCK_RENDER;

		int f_Building_MaxX = f_MaxX / BLOCK_RENDER;
		int f_Building_MaxY = f_MaxY / BLOCK_RENDER;
		int f_Building_MaxZ = f_MaxZ / BLOCK_RENDER;

		  //////////
		 // Grid //
		//std::shared_ptr<VoxelLimb> f_NewLimb
		for(int vx = f_Building_MinX; vx < f_Building_MaxX; vx++)
			{
			int Xbegin = (vx - f_VoxelGrid->m_Xpos);

			for(int vy = f_Building_MinY; vy < f_Building_MaxY; vy++)
				{
				int Ybegin = (vy - f_VoxelGrid->m_Ypos);

				for(int vz = f_Building_MinZ; vz < f_Building_MaxZ; vz++)
					{		
					int Zbegin = (vz - f_VoxelGrid->m_Zpos);

					if( (Xbegin >= 0) &&
						(Ybegin >= 0) &&
						(Zbegin >= 0) &&
						(Xbegin < VoxelGrid::VOXEL_GRID_SIZE) &&
						(Ybegin < VoxelGrid::VOXEL_GRID_SIZE) &&
						(Zbegin < VoxelGrid::VOXEL_GRID_SIZE))
						{
						 ///////////////////////////////////
						// Make New Limb if not supplied //
						if(f_Collide == false)
							{
							if(f_NewLimb == true)
								{
								f_CurrentLimb = f_VoxelGrid->acMake_PushLimb(f_Building_MinX, f_Building_MinY, f_Building_MinZ, f_Building_MaxX, f_Building_MaxY, f_Building_MaxZ);

								f_CurrentLimb->m_GridRef = f_VoxelGrid;
								}
							}

						f_CurrentLimb->m_VX_Core->SetColourType(Xbegin, Ybegin, Zbegin, VColorRed, VColorGreen, VColorBlue, VColorAlpha, f_BlockType);

						f_CurrentLimb->m_VX_Core->SetStrength(Xbegin, Ybegin, Zbegin, ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Strength));

						f_Collide = true;
						}
					}
				}
			}
		}

	return f_Collide;
}

bool VoxelGridManager::Make_Gen_Point(BlockType f_BlockType, int f_PointX, int f_PointY, int f_PointZ, int VColorRed, int VColorGreen, int VColorBlue, int VColorAlpha, std::shared_ptr<VoxelLimb> f_CurrentLimb)
{
	 ///////////////////////////////////
	// Make New Limb if not supplied //
	
	  /////////
	 // Grid
	//
	if(f_CurrentLimb != nullptr)
		{
		f_CurrentLimb->m_VX_Core->SetColourType(f_PointX, f_PointY, f_PointZ, VColorRed / 255.0f, VColorGreen / 255.0f, VColorBlue / 255.0f, VColorAlpha / 255.0f, f_BlockType);

		return true;
		}

	return false;
}

bool VoxelGridManager::Make_Place_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER;

	  ///////////////////
	 // Min
	//
	float f_MinX = f_FloorCenter.m_X - ((VWidth / 2) * (BLOCK_RENDER));
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = (f_FloorCenter.m_Z * -1.0f) - ((vLength / 2) * (BLOCK_RENDER));
	float f_MaxX = f_FloorCenter.m_X + ((VWidth / 2) * (BLOCK_RENDER));
	float f_MaxY = f_FloorCenter.m_Y + (vHeight * (BLOCK_RENDER));
	float f_MaxZ = (f_FloorCenter.m_Z * -1.0f) + ((vLength / 2) * (BLOCK_RENDER));

	   ///////////////////////
	  // Interior
	 // Cement
	// X
	float f_Min_CementXmn = f_MinX;
	float f_Max_CementXmn = f_MinX + (1.15f * (BLOCK_RENDER));
	float f_Min_CementXen = f_MaxX - (1.15f * (BLOCK_RENDER));
	float f_Max_CementXen = f_MaxX;
	// Y
	float f_Min_CementYmn = f_MinY;
	float f_Max_CementYmn = f_MinY + (1.15f * (BLOCK_RENDER));
	float f_Min_CementYen = f_MaxY - (1.15f * (BLOCK_RENDER));
	float f_Max_CementYen = f_MaxY;
	// Z
	float f_Min_CementZmn = f_MinZ;
	float f_Max_CementZmn = f_MinZ + (1.15f * (BLOCK_RENDER));
	float f_Min_CementZen = f_MaxZ - (1.15f * (BLOCK_RENDER));
	float f_Max_CementZen = f_MaxZ;

	  ////////////////////
	 // Brick
	// X
	float f_Min_BrickXmn = f_Max_CementXmn;
	float f_Max_BrickXmn = f_Max_CementXmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickXen = f_Min_CementXen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickXen = f_Min_CementXen;
	// Y
	float f_Min_BrickYmn = f_Max_CementYmn;
	float f_Max_BrickYmn = f_Max_CementYmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickYen = f_Min_CementYen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickYen = f_Min_CementYen;
	// Z
	float f_Min_BrickZmn = f_Max_CementZmn;
	float f_Max_BrickZmn = f_Max_CementZmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickZen = f_Min_CementZen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickZen = f_Min_CementZen;

	  ////////////////////
	 // Plaster
	// X
	float f_Min_PlasterXmn = f_Max_BrickXmn;
	float f_Max_PlasterXmn = f_Max_BrickXmn + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterXen = f_Min_BrickXen - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterXen = f_Min_BrickXen;
	// Y
	float f_Min_PlasterYmn = f_Max_BrickYmn;
	float f_Max_PlasterYmn = f_Max_BrickYmn + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterYen = f_Min_BrickYen - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterYen = f_Min_BrickYen;
	// Z
	float f_Min_PlasterZmn = f_Max_BrickZmn;
	float f_Max_PlasterZmn = f_Max_BrickZmn + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterZen = f_Min_BrickZen - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterZen = f_Min_BrickZen;

	bool f_Collide = false;

	int x = f_VoxelGrid->m_gridX;
	int y = f_VoxelGrid->m_gridY;
	int z = f_VoxelGrid->m_gridZ;

	if((f_MinX < ((x + 1) * GRID_RENDER)) &&
		(f_MaxX > (x * GRID_RENDER)))
		{
		if((f_MinY < ((y + 1) * GRID_RENDER)) &&
			(f_MaxY > (y * GRID_RENDER)))
			{
			if((f_MinZ < (((z * -1) + 1) * GRID_RENDER)) &&
				(f_MaxZ > ((z * -1) * GRID_RENDER)))
				{ /////////
				 // Grid
				//
				for(int vx = 0; vx < VoxelGrid::VOXEL_GRID_SIZE; vx++)
					{
					for(int vy = 0; vy < VoxelGrid::VOXEL_GRID_SIZE; vy++)
						{
						for(int vz = 0; vz < VoxelGrid::VOXEL_GRID_SIZE; vz++)
							{/////////
							// Grid
							if(f_VoxelGrid->GetActive(vx, vy, vz) || 1)
								{
								float f_BlockXmin = (x * GRID_RENDER + (vx * (BLOCK_RENDER)));
								float f_BlockXmax = (x * GRID_RENDER + ((vx + 1) * (BLOCK_RENDER)));
								float f_BlockYmin = (y * GRID_RENDER + (vy * (BLOCK_RENDER)));
								float f_BlockYmax = (y * GRID_RENDER + ((vy + 1) * (BLOCK_RENDER)));
								float f_BlockZmin = ((z * -1) * GRID_RENDER + (vz * (BLOCK_RENDER)));
								float f_BlockZmax = ((z * -1) * GRID_RENDER + ((vz + 1) * (BLOCK_RENDER)));

								if(((f_BlockXmin >= f_MinX) && (f_BlockXmin < f_MaxX)) &&
									((f_BlockYmin >= f_MinY) && (f_BlockYmin < f_MaxY)) &&
									((f_BlockZmin >= f_MinZ) && (f_BlockZmin < f_MaxZ)))
									{ // In Area
									f_Collide = true;
									}
								}
							}
						}
					}
				}
			}
		}

	return f_Collide;
}

void VoxelGridManager::Position_Player(BiVector f_Position)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER));

	bool f_Alter = false;

	float f_Xsgrid_Floating = (f_Position.m_X / BLOCK_RENDER) / (float)VoxelGrid::VOXEL_GRID_SIZE;
	float f_Ysgrid_Floating = (f_Position.m_Y / BLOCK_RENDER) / (float)VoxelGrid::VOXEL_GRID_SIZE;
	float f_Zsgrid_Floating = (f_Position.m_Z / BLOCK_RENDER) / (float)VoxelGrid::VOXEL_GRID_SIZE;

	int f_grids_X = f_Xsgrid_Floating;
	int f_grids_Y = f_Ysgrid_Floating;
	int f_grids_Z = f_Zsgrid_Floating * -1;

	for(int f_X = f_grids_X - LOAD_DISTANCE; f_X < f_grids_X + LOAD_DISTANCE; f_X++)
		{
		for(int f_Y = f_grids_Y - LOAD_DISTANCE; f_Y < f_grids_Y + LOAD_DISTANCE; f_Y++)
			{
			for(int f_Z = f_grids_Z - LOAD_DISTANCE; f_Z < f_grids_Z + LOAD_DISTANCE; f_Z++)
				{
				std::shared_ptr<VoxelGrid> f_VoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);

				if(f_VoxelGrid == nullptr)
					{
					if(((f_X >= f_grids_X - LOAD_DISTANCE) && (f_X < f_grids_X + LOAD_DISTANCE)) &&
						((f_Y >= f_grids_Y - LOAD_DISTANCE) && (f_Y < f_grids_Y + LOAD_DISTANCE)) &&
						((f_Z >= f_grids_Z - LOAD_DISTANCE) && (f_Z < f_grids_Z + LOAD_DISTANCE)))
						{
						CreateNewVoxelGrid(f_X, f_Y, f_Z);

						std::shared_ptr<VoxelGrid> f_NewVoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);

						Cube::g_WarZoneManager->acOnPushGrid(f_NewVoxelGrid);
						}
					}
				else
					{
					std::shared_ptr<VoxelGrid> f_SameVoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);

					Cube::g_WarZoneManager->acOnPushGrid(f_SameVoxelGrid);
					}
				}
			}
		}

	//### Conditional Timed Exit for all Grids outside load range
	time_t f_CurrentTime;
	time(&f_CurrentTime);

	if(f_CurrentTime > m_StorageTime + 10)
		{
		m_StorageTime = f_CurrentTime;

		//Reset Players Impact
		for(int f_Player = 0; f_Player < g_PlayerNom; f_Player++)
			{
			playerAV[f_Player]->m_ImpactCount = 0;
			}

		//Reset Avatars Impact
		for(int f_AIflag = 0; f_AIflag < _->NomAI; f_AIflag++)
			{
			Q_Forge->Forge[f_AIflag].AV.m_ImpactCount = 0;
			}

		//VoxelGrid Array
		for(int f_XY = 0; f_XY < m_VoxelGridsVector.size(); f_XY++)
			{
			std::shared_ptr<VoxelGrid> f_Grid = m_VoxelGridsVector[f_XY];

			if( (f_Grid->m_gridX < f_grids_X - LOAD_DISTANCE) ||
				(f_Grid->m_gridX >= f_grids_X + LOAD_DISTANCE) ||
				(f_Grid->m_gridY < f_grids_Y - LOAD_DISTANCE) ||
				(f_Grid->m_gridY >= f_grids_Y + LOAD_DISTANCE) ||
				(f_Grid->m_gridZ < f_grids_Z - LOAD_DISTANCE) ||
				(f_Grid->m_gridZ >= f_grids_Z + LOAD_DISTANCE))
				{
				f_Grid->m_TimedExit++;

				if(f_Grid->m_TimedExit > 6) // One Minute Passed
					{
					if(f_Grid != nullptr)
						{
						f_Grid->Make_Alone();

						 ///////////////////////
						// freeze any access //
						f_Grid->m_ShowOff = true;

						f_Grid->m_VX_Core = nullptr;

						g_VoxelGridManager->m_OGL_Mutex.lock();

						if(f_Grid->mVertexPositionBuffer != 0)
							{
							glDeleteBuffers(1, &f_Grid->mVertexPositionBuffer);
							f_Grid->mVertexPositionBuffer = 0;
							}

						if(f_Grid->mVertexNormalBuffer != 0)
							{
							glDeleteBuffers(1, &f_Grid->mVertexNormalBuffer);
							f_Grid->mVertexNormalBuffer = 0;
							}

						if(f_Grid->mVertexColorBuffer != 0)
							{
							glDeleteBuffers(1, &f_Grid->mVertexColorBuffer);
							f_Grid->mVertexColorBuffer = 0;
							}

						if(f_Grid->mVertexTexCoordBuffer != 0)
							{
							glDeleteBuffers(1, &f_Grid->mVertexTexCoordBuffer);
							f_Grid->mVertexTexCoordBuffer = 0;
							}

						if(f_Grid->mIndexBuffer != 0)
							{
							glDeleteBuffers(1, &f_Grid->mIndexBuffer);
							f_Grid->mIndexBuffer = 0;
							}

						g_VoxelGridManager->m_OGL_Mutex.unlock();

							///////////////////////
						// clear vertex data //
						f_Grid->m_vec_Vertex.clear();
						f_Grid->m_vec_Normal.clear();
						f_Grid->m_vec_Color.clear();
						f_Grid->m_vec_Tex.clear();
						f_Grid->m_vec_Index.clear();

						//Limbs - Add check if parent and within grid
						for(int f_Jet = 0; f_Jet < m_VoxelLimbVector.size(); f_Jet++)
							{
							std::shared_ptr<VoxelLimb> f_Limb = m_VoxelLimbVector[f_Jet];

							g_VoxelGridManager->m_OGL_Mutex.lock();

							if(f_Limb->mVertexPositionBuffer != 0)
								{
								glDeleteBuffers(1, &f_Limb->mVertexPositionBuffer);
								f_Limb->mVertexPositionBuffer = 0;
								}

							if(f_Limb->mVertexNormalBuffer != 0)
								{
								glDeleteBuffers(1, &f_Limb->mVertexNormalBuffer);
								f_Limb->mVertexNormalBuffer = 0;
								}

							if(f_Limb->mVertexColorBuffer != 0)
								{
								glDeleteBuffers(1, &f_Limb->mVertexColorBuffer);
								f_Limb->mVertexColorBuffer = 0;
								}

							if(f_Limb->mVertexTexCoordBuffer != 0)
								{
								glDeleteBuffers(1, &f_Limb->mVertexTexCoordBuffer);
								f_Limb->mVertexTexCoordBuffer = 0;
								}

							if(f_Limb->mIndexBuffer != 0)
								{
								glDeleteBuffers(1, &f_Limb->mIndexBuffer);
								f_Limb->mIndexBuffer = 0;
								}

							g_VoxelGridManager->m_OGL_Mutex.unlock();

								///////////////////////
							// clear vertex data //
							f_Limb->m_vec_Vertex.clear();
							f_Limb->m_vec_Normal.clear();
							f_Limb->m_vec_Color.clear();
							f_Limb->m_vec_Tex.clear();
							f_Limb->m_vec_Index.clear();
							}

						g_UpdatingMuti.lock();

						// Array Re-Order
						for(int f_XYS = f_Grid->m_ManagerIndex; f_XYS < m_VoxelGridsVector.size() - 1; f_XYS++)
							{
							m_VoxelGridsVector[f_XYS] = m_VoxelGridsVector[f_XYS + 1];

							m_VoxelGridsVector[f_XYS]->m_ManagerIndex = f_XYS;
							}

						m_VoxelGridsVector.pop_back();

						g_UpdatingMuti.unlock();
						}
					}
				}
			}
		}
}

bool VoxelGridManager::Make_Gen_IntWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER;

	  ///////////////////
	 // Min
	//
	float f_MinX = f_FloorCenter.m_X - ((VWidth / 2) * (BLOCK_RENDER));
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = (f_FloorCenter.m_Z * -1.0f) - ((vLength / 2) * (BLOCK_RENDER));
	float f_MaxX = f_FloorCenter.m_X + ((VWidth / 2) * (BLOCK_RENDER));
	float f_MaxY = f_FloorCenter.m_Y + (vHeight * (BLOCK_RENDER));
	float f_MaxZ = (f_FloorCenter.m_Z * -1.0f) + ((vLength / 2) * (BLOCK_RENDER));

	   ///////////////////////
	  // Interior
	 // Cement
	// X
	float f_Min_PlasterXmn = f_MinX;
	float f_Max_PlasterXmn = f_MinX + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterXen = f_MaxX - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterXen = f_MaxX;
	// Y
	float f_Min_PlasterYmn = f_MinY;
	float f_Max_PlasterYmn = f_MinY + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterYen = f_MaxY - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterYen = f_MaxY;
	// Z
	float f_Min_PlasterZmn = f_MinZ;
	float f_Max_PlasterZmn = f_MinZ + (1.15f * (BLOCK_RENDER));
	float f_Min_PlasterZen = f_MaxZ - (1.15f * (BLOCK_RENDER));
	float f_Max_PlasterZen = f_MaxZ;

	  ////////////////////
	 // Brick
	// X
	float f_Min_BrickXmn = f_Max_PlasterXmn;
	float f_Max_BrickXmn = f_Max_PlasterXmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickXen = f_Min_PlasterXen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickXen = f_Min_PlasterXen;
	// Y
	float f_Min_BrickYmn = f_Max_PlasterYmn;
	float f_Max_BrickYmn = f_Max_PlasterYmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickYen = f_Min_PlasterYen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickYen = f_Min_PlasterYen;
	// Z
	float f_Min_BrickZmn = f_Max_PlasterZmn;
	float f_Max_BrickZmn = f_Max_PlasterZmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickZen = f_Min_PlasterZen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickZen = f_Min_PlasterZen;

	bool f_Collide = false;

	int x = f_VoxelGrid->m_gridX;
	int y = 0;
	int z = f_VoxelGrid->m_gridZ;

	if((f_MinX < ((x + 1) * GRID_RENDER)) &&
		(f_MaxX > (x * GRID_RENDER)))
		{
		if((f_MinZ < (((z * -1) + 1) * GRID_RENDER)) &&
			(f_MaxZ > ((z * -1) * GRID_RENDER)))
			{ /////////
			 // Grid
			//
			for(int vx = 0; vx < VoxelGrid::VOXEL_GRID_SIZE; vx++)
				{
				for(int vy = 0; vy < VoxelGrid::VOXEL_GRID_SIZE; vy++)
					{
					for(int vz = 0; vz < VoxelGrid::VOXEL_GRID_SIZE; vz++)
						{/////////
						// Grid
						if(f_VoxelGrid->GetActive(vx, vy, vz) || 1)
							{
							float f_BlockXmin = (x * GRID_RENDER) + (vx * BLOCK_RENDER);
							float f_BlockXmax = (x * GRID_RENDER) + ((vx + 1) * BLOCK_RENDER);
							float f_BlockYmin = (y * GRID_RENDER) + (vy * BLOCK_RENDER);
							float f_BlockYmax = (y * GRID_RENDER) + ((vy + 1) * BLOCK_RENDER);
							float f_BlockZmin = ((z * -1) * GRID_RENDER) + (vz * BLOCK_RENDER);
							float f_BlockZmax = ((z * -1) * GRID_RENDER) + ((vz + 1) * BLOCK_RENDER);

							if(((f_BlockXmin >= f_MinX) && (f_BlockXmin < f_MaxX)) &&
								((f_BlockYmin >= f_MinY) && (f_BlockYmin < f_MaxY)) &&
								((f_BlockZmin >= f_MinZ) && (f_BlockZmin < f_MaxZ)))
								{ // In Area
									// Min Cem
								if(((f_BlockXmin >= f_Min_PlasterXmn) && (f_BlockXmin < (f_Max_PlasterXmn)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockZmin < (f_Max_PlasterZen))) ||
									((f_BlockXmin >= f_Min_PlasterXen) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockZmin < (f_Max_PlasterZen))) ||
									((f_BlockYmin >= f_Min_PlasterYmn) && (f_BlockYmin < (f_Max_PlasterYmn)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockXmin < (f_Max_PlasterZen))) ||
									((f_BlockYmin >= f_Min_PlasterYen) && (f_BlockYmin < (f_Max_PlasterYen)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockXmin < (f_Max_PlasterZen))) ||
									((f_BlockZmin >= f_Min_PlasterZmn) && (f_BlockZmin < (f_Max_PlasterZmn)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen))) ||
									((f_BlockZmin >= f_Min_PlasterZen) && (f_BlockZmin < (f_Max_PlasterZen)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen))))
									{ /////////
									 // Cement
									//
									f_VoxelGrid->SetColourType(vx, vy, vz, 1.0f, 1.0f, 1.0f, 1.0f, BlockType_Plaster);

									f_Collide = true;
									}
								else if(((f_BlockXmin >= f_Min_BrickXmn) && (f_BlockXmin < (f_Max_BrickXmn)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockZmin < (f_Max_BrickZen))) ||
										((f_BlockXmin >= f_Min_BrickXen) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockZmin < (f_Max_BrickZen))) ||
										((f_BlockYmin >= f_Min_BrickYmn) && (f_BlockYmin < (f_Max_BrickYmn)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockXmin < (f_Max_BrickZen))) ||
										((f_BlockYmin >= f_Min_BrickYen) && (f_BlockYmin < (f_Max_BrickYen)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockXmin < (f_Max_BrickZen))) ||
										((f_BlockZmin >= f_Min_BrickZmn) && (f_BlockZmin < (f_Max_BrickZmn)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen))) ||
										((f_BlockZmin >= f_Min_BrickZen) && (f_BlockZmin < (f_Max_BrickZen)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen))))
									{ /////////
									 // Brick
									//
									f_VoxelGrid->SetColourType(vx, vy, vz, 1.0f, 0.05f, 0.05f, 1.0f, BlockType_Brick);

									f_Collide = true;
									}
								else 
									{ /////////
									 // Brick
									//
									f_VoxelGrid->SetColourType(vx, vy, vz, 1.0f, 0.05f, 0.05f, 1.0f, BlockType_Brick);

									f_Collide = true;
									}
								}
							}
						}
					}
				}
			}
		}

	return f_Collide;
}

bool VoxelGridManager::Make_Gen_ExtWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER;

	  ///////////////////
	 // Min
	//
	float f_MinX = f_FloorCenter.m_X - ((VWidth / 2) * (BLOCK_RENDER));
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = (f_FloorCenter.m_Z * -1.0f) - ((vLength / 2) * (BLOCK_RENDER));
	float f_MaxX = f_FloorCenter.m_X + ((VWidth / 2) * (BLOCK_RENDER));
	float f_MaxY = f_FloorCenter.m_Y + (vHeight * (BLOCK_RENDER));
	float f_MaxZ = (f_FloorCenter.m_Z * -1.0f) + ((vLength / 2) * (BLOCK_RENDER));

	   ///////////////////////
	  // Interior
	 // Cement
	// X
	float f_Min_CementXmn = f_MinX;
	float f_Max_CementXmn = f_MinX + (1.15f * (BLOCK_RENDER));
	float f_Min_CementXen = f_MaxX - (1.15f * (BLOCK_RENDER));
	float f_Max_CementXen = f_MaxX;
	// Y
	float f_Min_CementYmn = f_MinY;
	float f_Max_CementYmn = f_MinY + (1.15f * (BLOCK_RENDER));
	float f_Min_CementYen = f_MaxY - (1.15f * (BLOCK_RENDER));
	float f_Max_CementYen = f_MaxY;
	// Z
	float f_Min_CementZmn = f_MinZ;
	float f_Max_CementZmn = f_MinZ + (1.15f * (BLOCK_RENDER));
	float f_Min_CementZen = f_MaxZ - (1.15f * (BLOCK_RENDER));
	float f_Max_CementZen = f_MaxZ;

	  ////////////////////
	 // Brick
	// X
	float f_Min_BrickXmn = f_Max_CementXmn;
	float f_Max_BrickXmn = f_Max_CementXmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickXen = f_Min_CementXen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickXen = f_Min_CementXen;
	// Y
	float f_Min_BrickYmn = f_Max_CementYmn;
	float f_Max_BrickYmn = f_Max_CementYmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickYen = f_Min_CementYen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickYen = f_Min_CementYen;
	// Z
	float f_Min_BrickZmn = f_Max_CementZmn;
	float f_Max_BrickZmn = f_Max_CementZmn + (1.15f * (BLOCK_RENDER));
	float f_Min_BrickZen = f_Min_CementZen - (1.15f * (BLOCK_RENDER));
	float f_Max_BrickZen = f_Min_CementZen;

	bool f_Collide = false;

	int x = f_VoxelGrid->m_gridX;
	int y = 0;
	int z = f_VoxelGrid->m_gridZ;

	if((f_MinX < ((x + 1) * GRID_RENDER)) &&
		(f_MaxX > (x * GRID_RENDER)))
		{
		if((f_MinZ < (((z * -1) + 1) * GRID_RENDER)) &&
			(f_MaxZ > ((z * -1) * GRID_RENDER)))
			{ /////////
			 // Grid
			//
			for(int vx = 0; vx < VoxelGrid::VOXEL_GRID_SIZE; vx++)
				{
				for(int vy = 0; vy < VoxelGrid::VOXEL_GRID_SIZE; vy++)
					{
					for(int vz = 0; vz < VoxelGrid::VOXEL_GRID_SIZE; vz++)
						{/////////
						// Grid
						if(f_VoxelGrid->GetActive(vx, vy, vz) || 1)
							{
							float f_BlockXmin = (x * GRID_RENDER + (vx * (BLOCK_RENDER)));
							float f_BlockXmax = (x * GRID_RENDER + ((vx + 1) * (BLOCK_RENDER)));
							float f_BlockYmin = (y * GRID_RENDER + (vy * (BLOCK_RENDER)));
							float f_BlockYmax = (y * GRID_RENDER + ((vy + 1) * (BLOCK_RENDER)));
							float f_BlockZmin = ((z * -1) * GRID_RENDER + (vz * (BLOCK_RENDER)));
							float f_BlockZmax = ((z * -1) * GRID_RENDER + ((vz + 1) * (BLOCK_RENDER)));

							if(((f_BlockXmin >= f_MinX) && (f_BlockXmin < f_MaxX)) &&
								((f_BlockYmin >= f_MinY) && (f_BlockYmin < f_MaxY)) &&
								((f_BlockZmin >= f_MinZ) && (f_BlockZmin < f_MaxZ)))
								{ // In Area
								 // Min Cem
								if(((f_BlockXmin >= f_Min_CementXmn) && (f_BlockXmin < (f_Max_CementXmn)) && (f_BlockYmin >= (f_Min_CementYmn)) && (f_BlockYmin < (f_Max_CementYen)) && (f_BlockZmin >= (f_Min_CementZmn)) && (f_BlockZmin < (f_Max_CementZen))) ||
									((f_BlockXmin >= f_Min_CementXen) && (f_BlockXmin < (f_Max_CementXen)) && (f_BlockYmin >= (f_Min_CementYmn)) && (f_BlockYmin < (f_Max_CementYen)) && (f_BlockZmin >= (f_Min_CementZmn)) && (f_BlockZmin < (f_Max_CementZen))) ||
									((f_BlockYmin >= f_Min_CementYmn) && (f_BlockYmin < (f_Max_CementYmn)) && (f_BlockXmin >= (f_Min_CementXmn)) && (f_BlockXmin < (f_Max_CementXen)) && (f_BlockZmin >= (f_Min_CementZmn)) && (f_BlockXmin < (f_Max_CementZen))) ||
									((f_BlockYmin >= f_Min_CementYen) && (f_BlockYmin < (f_Max_CementYen)) && (f_BlockXmin >= (f_Min_CementXmn)) && (f_BlockXmin < (f_Max_CementXen)) && (f_BlockZmin >= (f_Min_CementZmn)) && (f_BlockXmin < (f_Max_CementZen))) ||
									((f_BlockZmin >= f_Min_CementZmn) && (f_BlockZmin < (f_Max_CementZmn)) && (f_BlockXmin >= (f_Min_CementXmn)) && (f_BlockXmin < (f_Max_CementXen)) && (f_BlockYmin >= (f_Min_CementYmn)) && (f_BlockYmin < (f_Max_CementYen))) ||
									((f_BlockZmin >= f_Min_CementZen) && (f_BlockZmin < (f_Max_CementZen)) && (f_BlockXmin >= (f_Min_CementXmn)) && (f_BlockXmin < (f_Max_CementXen)) && (f_BlockYmin >= (f_Min_CementYmn)) && (f_BlockYmin < (f_Max_CementYen))))
									{ /////////
									 // Cement
									//
									f_VoxelGrid->SetColourType(vx, vy, vz, 1.0f, 1.0f, 1.0f, 1.0f, BlockType_Cement);
									f_Collide = true;
									}
								else if(((f_BlockXmin >= f_Min_BrickXmn) && (f_BlockXmin < (f_Max_BrickXmn)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockZmin < (f_Max_BrickZen))) ||
										((f_BlockXmin >= f_Min_BrickXen) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockZmin < (f_Max_BrickZen))) ||
										((f_BlockYmin >= f_Min_BrickYmn) && (f_BlockYmin < (f_Max_BrickYmn)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockXmin < (f_Max_BrickZen))) ||
										((f_BlockYmin >= f_Min_BrickYen) && (f_BlockYmin < (f_Max_BrickYen)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockZmin >= (f_Min_BrickZmn)) && (f_BlockXmin < (f_Max_BrickZen))) ||
										((f_BlockZmin >= f_Min_BrickZmn) && (f_BlockZmin < (f_Max_BrickZmn)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen))) ||
										((f_BlockZmin >= f_Min_BrickZen) && (f_BlockZmin < (f_Max_BrickZen)) && (f_BlockXmin >= (f_Min_BrickXmn)) && (f_BlockXmin < (f_Max_BrickXen)) && (f_BlockYmin >= (f_Min_BrickYmn)) && (f_BlockYmin < (f_Max_BrickYen))))
									{ /////////
									 // Brick
									//
									f_VoxelGrid->SetColourType(vx, vy, vz, 1.0f, 0.05f, 0.05f, 1.0f, BlockType_Brick);
									f_Collide = true;
									}
								else 
									{ /////////
									 // Brick
									//
									f_VoxelGrid->SetColourType(vx, vy, vz, 1.0f, 0.05f, 0.05f, 1.0f, BlockType_Brick);
									f_Collide = true;
									}
								}
							}
						}
					}
				}
			}
		}

	return f_Collide;
}

bool VoxelGrid::Make_ApplyDamageSphere(BiVector f_Point, float f_Radius, float f_Power, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_SIZE = (VOXEL_GRID_SIZE * BLOCK_RENDER);

	bool f_Collide = false;
	bool f_Rebuild = false;

	int f_RadiusInt = (int)f_Radius;

	if((f_Point.m_X >= (f_x * GRID_SIZE)) &&
		(f_Point.m_X < ((f_x + 1) * GRID_SIZE)) &&
		(f_Point.m_Y >= (f_y * GRID_SIZE)) &&
		(f_Point.m_Y < ((f_y + 1) * GRID_SIZE)) &&
		(f_Point.m_Z >= ((f_z * -1) * GRID_SIZE)) &&
		(f_Point.m_Z < (((f_z * -1) + 1) * GRID_SIZE)))
		{
		int f_Xclip = (int)f_Point.m_X / (int)BLOCK_RENDER;
		int f_Yclip = (int)f_Point.m_Y / (int)BLOCK_RENDER;
		int f_Zclip = (int)f_Point.m_Z / (int)BLOCK_RENDER;

		int Xacting = f_Xclip - m_Xpos;
		int Yacting = f_Yclip - m_Ypos;
		int Zacting = f_Zclip - m_Zpos;

		int Xbegin = Xacting - f_RadiusInt; // adjust here
		int Ybegin = Yacting - f_RadiusInt; // adjust here
		int Zbegin = Zacting - f_RadiusInt; // adjust here

		int Xfin = Xacting + f_RadiusInt; // adjust here
		int Yfin = Yacting + f_RadiusInt; // adjust here
		int Zfin = Zacting + f_RadiusInt; // adjust here

		  ///////////////
		 // Inside VX //
		///////////////
		for(int x = Xbegin; x < Xfin; x++)
			{
			for(int y = Ybegin; y < Yfin; y++)
				{
				for(int z = Zbegin; z < Zfin; z++)
					{
					if(GetActive(x, y, z) == true)
						{
						float f_CentralX = (f_x * GRID_SIZE) + ((x * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE);
						float f_CentralY = (f_y * GRID_SIZE) + ((y * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE);
						float f_CentralZ = ((f_z * -1) * GRID_SIZE) + ((z * BLOCK_RENDER) + VoxelGrid::BLOCK_RENDER_SIZE);
						
						BiVector f_Central(f_CentralX, f_CentralY, f_CentralZ);
						BiVector f_ForceVec = f_Central - f_Point;

						float f_ForceFac = f_ForceVec.acLength();
						float f_PowerFac = f_Power * WORLD_DMG_DEFAULT;

						   ////////////
						  // Damage //
						 ////////////
						if(f_ForceFac <= f_Radius)
							{
							f_PowerFac *= 1.0f - (f_ForceFac / f_Radius);
							f_Collide = true;

							float f_Strength = m_VX_Core->GetStrength(x, y, z);
							f_Strength -= f_PowerFac;

							// Detect if any limbs changed
							std::shared_ptr<VoxelLimb> f_Limb = OnVoxelLimb(x, y, z);

							if(f_Limb == nullptr)
								{
								if(f_Strength <= 0)
									{
									SetColour(x, y, z, 0.0f, 0.0, 0.0, 0.0f);
									SetStrength(x, y, z, 0.0f);

									*(f_ResX) = x;
									*(f_ResY) = y;
									*(f_ResZ) = z;

									f_Rebuild = true;
									}
								else
									{
									SetStrength(x, y, z, f_Strength);
									}
								}
							else
								{
								if(f_Strength <= 0)
									{
									f_Limb->m_VX_Core->SetColour(x, y, z, 0.0f, 0.0, 0.0, 0.0f);
									f_Limb->m_VX_Core->SetStrength(x, y, z, 0.0f);

									*(f_ResX) = x;
									*(f_ResY) = y;
									*(f_ResZ) = z;
									}
								else
									{
									f_Limb->m_VX_Core->SetStrength(x, y, z, f_Strength);
									}

								f_Limb->Make_Alone();

								f_Limb->SetNeedsRebuild(true, true);
								}
							}
						}
					}
				}
			}
		}

	if(f_Rebuild)
		{
		Make_Alone();

		SetNeedsRebuild(true, false, true);
		}

	return f_Collide;
}

void VoxelGrid::Make_Alone(void)
{
	if(m_Child.size() > 0)
		{
		std::shared_ptr<VoxelGrid> f_NewParent = m_Child[0];

		f_NewParent->m_isParent = true;

		for(int f_Jet = m_Child.size() - 1; f_Jet >= 0; f_Jet--)
			{
			std::shared_ptr<VoxelGrid> f_Child = m_Child[f_Jet];

			m_Child.pop_back();

			f_Child->m_Parent = f_NewParent;

			f_NewParent->m_Child.push_back(f_Child);
			}
		}
}

void VoxelLimb::Make_Alone(void)
{
	if(m_Child.size() > 0)
		{
		std::shared_ptr<VoxelLimb> f_NewParent = m_Child[0];

		f_NewParent->m_isParent = true;

		for(int f_Jet = m_Child.size() - 1; f_Jet >= 0; f_Jet--)
			{
			std::shared_ptr<VoxelLimb> f_Child = m_Child[f_Jet];

			m_Child.pop_back();

			f_Child->m_Parent = f_NewParent;

			f_NewParent->m_Child.push_back(f_Child);
			}
		}
}

VoxelDamageMask::VoxelDamageMask(VoxelBlock f_OriginBlock, BiVector f_ImpactIn, BiVector f_ImpactPoint)
{
	acClear();

	m_is_naturalOriginBlock = true;

	//origin block known
	m_OriginBlock = f_OriginBlock;

	m_ImpactIn = f_ImpactIn;

	m_ImpactIn.acNormalize();

	m_ImpactPoint = f_ImpactPoint;
	m_CurrentPoint = m_ImpactPoint;

	QpoVec3d f_TraVec(m_ImpactIn.m_X, m_ImpactIn.m_Y, m_ImpactIn.m_Z);

	QpoTransform f_Transform;

	float f_Y_Diff = f_TraVec.y;
	float f_X_Diff = f_TraVec.x;

	Qpo->Transform_New_ZRotation(&f_Transform, f_Y_Diff * (PI * 2.0f));
	Qpo->Transform_New_YRotation(&f_Transform, f_X_Diff * (PI * 2.0f)); //swk || * PI || Z ?

	QpoVec3d f_In;
	QpoVec3d f_Right;
	QpoVec3d f_Up;

	Qpo->Transform_GetIn(&f_Transform, &f_In);
	Qpo->Transform_GetLeft(&f_Transform, &f_Right);
	Qpo->Transform_GetUp(&f_Transform, &f_Up);

	// Right Vector
	Qpo->Vec3d_Inverse(&f_Right);

	m_RightVec = BiVector(f_Right.x, f_Right.y, f_Right.z);
	m_RightVec.acNormalize();

	m_UpVec = BiVector(f_Up.x, f_Up.y, f_Up.z);
	m_UpVec.acNormalize();

	m_SingleUnit = VOXEL_RENDER_SIZE * 2.0f;

#if 0
	Qpo->Vec3d_CrossProduct(&f_TraVec, &f_Up, &f_LeftToRight);
	Qpo->Vec3d_Inverse(&f_LeftToRight);

	Qpo->Transform_New_LeftUpIn(&Q_SEnergy->SEnergy[_->NomSEnergy].Matrix, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.In);
#endif
}

VoxelDamageMask::VoxelDamageMask(BiVector f_ImpactIn, BiVector f_ImpactPoint)
{
	acClear();

	m_is_naturalOriginBlock = false;

	m_ImpactIn = f_ImpactIn;

	m_ImpactIn.acNormalize();

	m_ImpactPoint = f_ImpactPoint;
	m_CurrentPoint = m_ImpactPoint;

	QpoVec3d f_TraVec(m_ImpactIn.m_X, m_ImpactIn.m_Y, m_ImpactIn.m_Z);

	QpoTransform f_Transform;

	float f_SpinFac = 0.0f;
	float f_Y_Diff = f_TraVec.y * (PI / 2.0f);

	if((f_TraVec.x > -1.0f) && (f_TraVec.x < 0.0f))
		{
		if((f_TraVec.z >= 0.0f) && (f_TraVec.z < 1.0f))
			{
			f_SpinFac = abs(f_TraVec.x)  * (PI /2.0f);
			}
		else if((f_TraVec.z >= -1.0f) && (f_TraVec.z < 0.0f))
			{
			f_SpinFac = f_TraVec.x * (PI / 2.0f);
			}
		}
	else if((f_TraVec.x > 0.0f) && (f_TraVec.x < 1.0f))
		{
		if((f_TraVec.z >= 0.0f) && (f_TraVec.z < 1.0f))
			{
			f_SpinFac = f_TraVec.x  * (PI / 2.0f);
			}
		else if((f_TraVec.z >= -1.0f) && (f_TraVec.z < 0.0f))
			{
			f_SpinFac = ((1.0f - f_TraVec.x) * (PI / 2.0f)) + (PI / 2.0f);
			}
		}

	//Ange.x = -(PI / 2.0f);
	Ange.x = f_Y_Diff;
	Ange.y = f_SpinFac;
	Ange.z = 0;

	Qpo->Transform_New(&f_Transform);

	f_Transform.Matrix.load_identity();

	Qpo->Transform_RotateX(&f_Transform, Ange.x);
	Qpo->Transform_RotateY(&f_Transform, Ange.y); //Clock Wise - <<< or Anti Clock Wise +
	//Qpo->Transform_RotateZ(&f_Transform, Ange.z);

	QpoVec3d f_In;
	QpoVec3d f_Right;
	QpoVec3d f_Up;

	Qpo->Transform_GetIn(&f_Transform, &f_In);
	Qpo->Transform_GetLeft(&f_Transform, &f_Right);
	Qpo->Transform_GetUp(&f_Transform, &f_Up);

	// Right Vector
	Qpo->Vec3d_Inverse(&f_Right);

	m_RightVec = BiVector(f_Right.x, f_Right.y, f_Right.z);
	m_RightVec.acNormalize();

	m_UpVec = BiVector(f_Up.x, f_Up.y, f_Up.z);
	m_UpVec.acNormalize();

	m_SingleUnit = VOXEL_RENDER_SIZE * 2.0f;

#if 0
	Qpo->Transform_New_LeftUpIn(&Q_SEnergy->SEnergy[_->NomSEnergy].Matrix, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.In);
#endif
}

VoxelDamageMask::VoxelDamageMask(BiVector f_ImpactPoint, int f_Radius)
{
	acClear();

	m_radius = f_Radius;

	m_is_naturalOriginBlock = false;

	m_ImpactPoint = f_ImpactPoint;
}

void VoxelGrid::acApply_BlockDamage(int f_Index, int f_blk_X, int f_blk_Y, int f_blk_Z, float f_Strength, float f_ExplosiveForce, float f_HeatPower)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	//Lower Strength
	m_VX_Core->m_blockStrength[f_Index] -= f_Strength;

	BlockType f_BlockType = m_VX_Core->m_blockType[f_Index];

	float* f_R = new float(0.0f);
	float* f_G = new float(0.0f);
	float* f_B = new float(0.0f);
	float* f_A = new float(0.0f);

	m_VX_Core->GetColour(f_blk_X, f_blk_Y, f_blk_Z, f_R, f_G, f_B, f_A);

	float f_rev_R = *(f_R);
	float f_rev_G = *(f_G);
	float f_rev_B = *(f_B);
	float f_rev_A = *(f_A);

	delete f_R;
	delete f_G;
	delete f_B;
	delete f_A;

	// Mod Red
	f_rev_R = clamp(f_rev_R + f_Strength, 0.0f, 1.0f);

	// Mod Alpha
	f_rev_A = clamp(m_VX_Core->m_blockStrength[f_Index] / ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Strength), 0.0f, 1.0f);

	m_VX_Core->SetColour(f_blk_X, f_blk_Y, f_blk_Z, f_rev_R, f_rev_G, f_rev_B, f_rev_A);

	float f_StrDamageMull = f_Strength;

	if(f_Strength > WORLD_STRENGTH_THRESH)
		{
		f_StrDamageMull += f_ExplosiveForce;

		if(m_VX_Core->m_blockStrength[f_Index] <= 0.0f)
			{
			f_StrDamageMull += abs(m_VX_Core->m_blockStrength[f_Index]);
			}

		Cube::BiVector f_BlockCenter(((float)f_blk_X * BLOCK_RENDER) * (GRID_RENDER * (float)m_gridX) + VoxelGrid::BLOCK_RENDER_SIZE,
									 ((float)f_blk_Y * BLOCK_RENDER) * (GRID_RENDER * (float)m_gridY) + VoxelGrid::BLOCK_RENDER_SIZE,
									 ((float)f_blk_Z * BLOCK_RENDER) * (GRID_RENDER * (float)(m_gridZ * -1)) + VoxelGrid::BLOCK_RENDER_SIZE);

		acApply_BlastProp(f_Index, f_blk_X, f_blk_Y, f_blk_Z, f_ExplosiveForce + f_StrDamageMull, f_BlockCenter);
		}
	else
		{
		if(f_HeatPower > WORLD_HEAT_THRESH_CELCIUS)
			{
			if(m_VX_Core->m_blockStrength[f_Index] > 0.0f)
				{
				if((f_BlockType == BlockType_Wood) || (f_BlockType == BlockType_Plaster))
					{
					acApply_BlockProp(f_Index, f_blk_X, f_blk_Y, f_blk_Z, f_Strength, f_HeatPower);
					}
				}
			}
		}

#ifndef WORLD_DAMAGE_EVERY_UPDATE
	if(m_VX_Core->m_blockStrength[f_Index] > 0.0f)
		{
		// Detect if any limbs changed
		std::shared_ptr<VoxelLimb> f_Limb = OnVoxelLimb(f_blk_X, f_blk_Y, f_blk_Z);

		if(f_Limb != nullptr)
			{
			f_Limb->Make_Alone();

			f_Limb->SetNeedsRebuild(true, true);
			}
		else
			{
			Make_Alone();

			SetNeedsRebuild(true, false, true);
			}
		}
#else
	// Detect if any limbs changed
	std::shared_ptr<VoxelLimb> f_Limb = OnVoxelLimb(f_blk_X, f_blk_Y, f_blk_Z);

	if(f_Limb != nullptr)
		{
		f_Limb->Make_Alone();

		f_Limb->SetNeedsRebuild(true, true);
		}
	else
		{
		Make_Alone();

		SetNeedsRebuild(true, false, true);
		}
#endif
}

void VoxelGrid::acApply_BlockProp(int f_Index, int f_blk_X, int f_blk_Y, int f_blk_Z, float f_Strength, float f_HeatPower)
{
	// add scene node voxelgrid
	m_VX_Core->m_vec_Prop_energy_Block.push_back(std::make_shared<VoxelBlock>(f_blk_X + f_blk_Y * VoxelGrid::VOXEL_GRID_SIZE + f_blk_Z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, f_blk_X, f_blk_Y, f_blk_Z, f_Strength, f_HeatPower, f_Strength * f_HeatPower));
}

void VoxelGrid::acApply_BlastProp(int f_Index, int f_blk_X, int f_blk_Y, int f_blk_Z, float f_ExplosivePower, BiVector f_BlastCenter)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_SIZE = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	if( ((f_blk_X >= 0) && (f_blk_X < VoxelGrid::VOXEL_GRID_SIZE)) &&
		((f_blk_Y >= 0) && (f_blk_Y < VoxelGrid::VOXEL_GRID_SIZE)) &&
		((f_blk_Z >= 0) && (f_blk_Z < VoxelGrid::VOXEL_GRID_SIZE)))
		{
		std::shared_ptr<VoxelVector> f_Block = std::make_shared<VoxelVector>(f_blk_X + f_blk_Y * VoxelGrid::VOXEL_GRID_SIZE + f_blk_Z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, f_blk_X, f_blk_Y, f_blk_Z);

		BiVector f_BlockCenter(((float)f_blk_X * BLOCK_RENDER) * ((float)GRID_SIZE * (float)m_gridX) + VoxelGrid::BLOCK_RENDER_SIZE,
							   ((float)f_blk_Y * BLOCK_RENDER) * ((float)GRID_SIZE * (float)m_gridY) + VoxelGrid::BLOCK_RENDER_SIZE,
							   ((float)f_blk_Z * BLOCK_RENDER) * ((float)GRID_SIZE * (float)(m_gridZ * -1)) + VoxelGrid::BLOCK_RENDER_SIZE);

		BiVector f_VecTo = f_BlockCenter - f_BlastCenter;

		float f_Length = f_VecTo.acLength();

		f_VecTo.acNormalize();
	
		float f_LengthInv = 1.0f - (f_Length / WORLD_DISTANCE_REDUCE);

		if(f_LengthInv > 0.0f)
			{
			BiVector f_LoadOn_Vector = f_VecTo * f_LengthInv * f_ExplosivePower;

			if(f_LoadOn_Vector.acLength() > 0.07f)
				{
				f_Block->acLoadOn_BlockForce(f_LoadOn_Vector);

				// add scene node voxelgrid
				m_VX_Core->m_vec_LoadOn_VoxelVector.push_back(f_Block);
				}
			}
		}
}

bool VoxelGrid::acSimulateCore(float f_TimeScale)
{
	//Propagated VoxelBlock Scene Nodes
	for(int f_Jet = 0; f_Jet < m_VX_Core->m_vec_Prop_energy_Block.size(); f_Jet++)
		{
		std::shared_ptr<VoxelBlock> f_VoxBlock = m_VX_Core->m_vec_Prop_energy_Block[f_Jet];

		if(f_VoxBlock->m_Heat > (WORLD_HEAT_ROOM_TEMP + (WORLD_HEAT_ROOM_TEMP / 2.0f)))
			{
			acApply_BlockDamage(f_VoxBlock->m_Index, f_VoxBlock->m_BIDX, f_VoxBlock->m_BIDY, f_VoxBlock->m_BIDZ, f_VoxBlock->m_Heat, 1.0f, f_VoxBlock->m_Heat);
			}

		if(m_VX_Core->m_blockStrength[f_VoxBlock->m_Index] > 0.0f)
			{
			if(Cube::random() >= 0.5f)
				{
				f_VoxBlock->m_Heat_Frk += WORLD_HEAT_FRK_AMT * (Cube::random() * WORLD_HEAT_COLLECTIVE_LOSS);
				}
			else
				{
				f_VoxBlock->m_Heat_Frk -= WORLD_HEAT_FRK_AMT * (Cube::random() * WORLD_HEAT_COLLECTIVE_GAIN);
				}

			BlockType f_BlockType = GetBlockType(f_VoxBlock->m_BIDX, f_VoxBlock->m_BIDX, f_VoxBlock->m_BIDZ);

			float f_ResistanceArg = ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Heat_Resistance);

			f_VoxBlock->m_Heat -= (f_VoxBlock->m_Heat_Frk / f_ResistanceArg);
			}
		else //block burnt up
			{
			//central reorder
			for(int f_XY = f_Jet; f_XY < m_VX_Core->m_vec_LoadOn_VoxelVector.size() - 1; f_XY++)
				{
				m_VX_Core->m_vec_LoadOn_VoxelVector[f_XY] = m_VX_Core->m_vec_LoadOn_VoxelVector[f_XY + 1];
				}

			m_VX_Core->m_vec_LoadOn_VoxelVector.pop_back();
			}
		}

	  ///////////////////////////////////////////////////////////////
	 //###                                                     ###//
	//### VoxelVector .LoadOn. Scene Force Vector .Unloading. ###//
	bool f_Attached = true;

	for(int f_Jet = 0; f_Jet < m_VX_Core->m_vec_LoadOn_VoxelVector.size(); f_Jet++)
		{
		std::shared_ptr<VoxelVector> f_VoxVector = m_VX_Core->m_vec_LoadOn_VoxelVector[f_Jet];

		float f_ForcePower = f_VoxVector->m_LoadOnVector.acLength();

		BlockType f_BlockType = GetBlockType(f_VoxVector->m_BIDX, f_VoxVector->m_BIDY, f_VoxVector->m_BIDZ);

		float f_BrittleArg = ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Brittle);

		float f_UntilFlightArg = ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Flight_Thresh);

		if(f_ForcePower > f_BrittleArg / WORLD_BREAK_THRESH_REDUCE) // Win Conditions! Block Damage
			{
			// unload vector A
			f_ForcePower -= f_BrittleArg / (WORLD_BREAK_THRESH_REDUCE * 2.707f);

			acApply_BlockDamage(f_VoxVector->m_Index, f_VoxVector->m_BIDX, f_VoxVector->m_BIDY, f_VoxVector->m_BIDZ, f_ForcePower, f_ForcePower, f_ForcePower * (WORLD_HEAT_ROOM_TEMP / WORLD_HEAT_REDUCE));
			}

		if(m_VX_Core->m_blockStrength[f_VoxVector->m_Index] > 0.0f)
			{
			if(f_ForcePower > f_UntilFlightArg)
				{
				// unload vector B
				f_ForcePower -= f_UntilFlightArg / (WORLD_BREAK_THRESH_REDUCE * 2.707f);

				if(f_ForcePower > 0.01f)
					{
					BiVector f_MotionVec = f_VoxVector->m_LoadOnVector;

					f_MotionVec.acNormalize();

					f_VoxVector->m_LoadOnVector = f_MotionVec * f_ForcePower;
					}
				else
					{
					f_VoxVector->m_LoadOnVector = BiVector(0.0f);

					//central reorder
					for(int f_XY = f_Jet; f_XY < m_VX_Core->m_vec_LoadOn_VoxelVector.size() - 1; f_XY++)
						{
						m_VX_Core->m_vec_LoadOn_VoxelVector[f_XY] = m_VX_Core->m_vec_LoadOn_VoxelVector[f_XY + 1];
						}

					m_VX_Core->m_vec_LoadOn_VoxelVector.pop_back();
					}
			
				acMake_BlockFlight(f_VoxVector, f_ForcePower, WORLD_HEAT_REDUCE_AMT);

#if 0
				Make_Alone();

				SetNeedsRebuild(true, false, true);
#endif

				f_Attached = false;
				}
			else //conditional pull away shall never breach
				{
				BiVector f_MotionVec = f_VoxVector->m_LoadOnVector;

				f_MotionVec.acNormalize();

				f_VoxVector->m_LoadOnVector = f_MotionVec * f_ForcePower;
				}
			}
		else //else block destroyed
			{
			for(int f_XY = f_Jet; f_XY < m_VX_Core->m_vec_LoadOn_VoxelVector.size() - 1; f_XY++)
				{
				m_VX_Core->m_vec_LoadOn_VoxelVector[f_XY] = m_VX_Core->m_vec_LoadOn_VoxelVector[f_XY + 1];
				}

			m_VX_Core->m_vec_LoadOn_VoxelVector.pop_back();

			f_Jet--;

			if(f_Jet < 0)
				{
				f_Jet = 0;
				}
			}
		}

	return true;
}

void VoxelLimb::acInvalidate_Cache(void)
{
	m_rebuildCache = 1;
}

void VoxelLimb::acPreCalc_Cache(void)
{
	if(m_rebuildCache == 1)
		{
		m_constant_BlockCount = 0;
		m_constant_DensityMax = 0.0f;

		for(int f_X = m_local_MinX; f_X < m_local_MaxX; f_X++)
			{
			for(int f_Y = m_local_MinY; f_Y < m_local_MaxY; f_Y++)
				{
				for(int f_Z = m_local_MinZ; f_Z < m_local_MaxZ; f_Z++)
					{
					if(m_VX_Core->GetActive(f_X, f_Y, f_Z) == true)
						{
						m_constant_BlockCount++;

						BlockType f_BlockType = GetBlockType(f_X, f_Y, f_Z);

						float f_Strength = m_VX_Core->GetStrength(f_X, f_Y, f_Z);

						float f_DefaultStrength = ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Strength);

						float f_StrengthPerc = f_Strength / f_DefaultStrength;

						float f_DefaultWeight = ag_BlockType_Varg(f_BlockType, BlockStat_Argument::BlockArg_Weight);

						float f_CurrentDensity = f_DefaultWeight * f_StrengthPerc;

						m_constant_DensityMax += f_CurrentDensity;
						}
					}
				}
			}

		m_rebuildCache = 0;
		}
}

//Check List
//1. Install proper weightts for density by material

void VoxelLimb::acCoreCalc(float f_TimeScale)
{
	m_Simulating = 1;

	acPreCalc_Cache();

	//apply momentum
	BiVector f_Pos(Xform.Translation.x, Xform.Translation.y, Xform.Translation.z);
	BiVector f_BiMoment = f_Pos + m_Moment;

	QpoVec3d f_NewPos(f_BiMoment.m_X, f_BiMoment.m_Y, f_BiMoment.m_Z);

	//Collision Detection
	QpoCollision f_Collision;

	bool f_SweepTestCollide = Qpo->Collision_RayTest(NULL, NULL, &Xform.Translation, &f_NewPos, 0xffffffff, NULL, NULL, &f_Collision);

	if(f_SweepTestCollide == true)
		{
		QpoVec3d f_InVector(0.0f, 0.0f, 0.0f);
		Qpo->Vec3d_Subtract(&f_NewPos, &Xform.Translation, &f_InVector);
		BiVector f_ImpactIn(f_InVector.x, f_InVector.y, f_InVector.z);
		float f_mull = min(f_ImpactIn.acLength(), 1.0f);
		f_ImpactIn.acNormalize();

		int f_X = (_->Box.xScale * 1.34f) / 2.0f;
		int f_Y = (_->Box.yScale * 1.34f) / 2.0f;

		f_mull *= m_constant_DensityMax;

		Qpo->Collision_Make_Impact_Grid(f_Collision.Impact, f_ImpactIn, f_BiMoment, f_Collision.m_VXGrid, BlockMark(f_X * -1, f_Y * -1), BlockMark(f_X, f_Y), f_mull, f_mull / 10.0f, f_mull / 10.0f);

		QpoVec3d f_Normal(f_Collision.Normal.m_X, f_Collision.Normal.m_Y, f_Collision.Normal.m_Z);

		//Bounce Moment
		QpoVec3d f_ResultMoment = Q.PHY_BounceVector(f_InVector, f_Normal);

		m_Moment.acSet(f_ResultMoment.x, f_ResultMoment.y, f_ResultMoment.z);
		}
	else
		{
		//Wind resistance
		m_Moment = m_Moment * m_AirResistanceFactor;
		}

	m_Simulating = 0;
}

std::shared_ptr<VoxelLimb> VoxelGrid::acMake_PushLimb(int f_MinX, int f_MinY, int f_MinZ, int f_MaxX, int f_MaxY, int f_MaxZ)
{
	// Make New Limb Class
	std::shared_ptr<VoxelLimb> f_Limb = std::make_shared<VoxelLimb>(m_vec_VoxelLimb.size(), f_MinX, f_MinY, f_MinZ, f_MaxX, f_MaxY, f_MaxZ);

	f_Limb->SetPosition(m_position);
	f_Limb->SetGrid(m_gridX, m_gridY, m_gridZ);

	g_UpdatingMuti.lock();

	if(m_vec_VoxelLimb.size() > 0)
		{	// setup is true previous limb if any
		m_vec_VoxelLimb[m_vec_VoxelLimb.size() - 1]->m_setup = true;
		}

	f_Limb->m_VX_Core = m_VX_Core;

	// vector references
	m_vec_VoxelLimb.push_back(f_Limb);

	g_VoxelGridManager->m_VoxelLimbVector.push_back(f_Limb);

	g_UpdatingMuti.unlock();

	return f_Limb;
}

std::shared_ptr<VoxelLimb> VoxelGrid::OnVoxelLimb(std::shared_ptr<VoxelVector> f_VoxVector)
{
	// scan for limb optimize add matrix rotations to ghost start position
	return OnVoxelLimb(f_VoxVector->m_BIDX, f_VoxVector->m_BIDY, f_VoxVector->m_BIDZ);
}

std::shared_ptr<VoxelLimb> VoxelGrid::OnVoxelLimb(int f_X, int f_Y, int f_Z)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	if(m_VoxelLimb_MeM != nullptr)
		{
		if( (m_VoxelLimb_MeM->m_setup == false) &&
			(f_X > m_VoxelLimb_MeM->m_MinX - m_Xpos) &&
			(f_X <= m_VoxelLimb_MeM->m_MaxX - m_Xpos) &&
			(f_Y > m_VoxelLimb_MeM->m_MinY - m_Ypos) &&
			(f_Y <= m_VoxelLimb_MeM->m_MaxY - m_Ypos) &&
			(f_Z > m_VoxelLimb_MeM->m_MinZ - m_Zpos) &&
			(f_Z <= m_VoxelLimb_MeM->m_MaxZ - m_Zpos))
			return m_VoxelLimb_MeM;
		}

	// scan for limb optimize add matrix rotations to ghost start position
	for(int f_Cycl = 0; f_Cycl < m_vec_VoxelLimb.size(); f_Cycl++)
		{
		std::shared_ptr<VoxelLimb> f_Limb = m_vec_VoxelLimb[f_Cycl];

		if (f_Limb == NULL)
			continue;

		if (f_Limb->m_setup == false)
			continue;

		if (f_X < f_Limb->m_MinX - m_Xpos)
			continue;

		if (f_X >= f_Limb->m_MaxX - m_Xpos)
			continue;

		if (f_Y < f_Limb->m_MinY - m_Ypos)
			continue;

		if (f_Y >= f_Limb->m_MaxY - m_Ypos)
			continue;

		if (f_Z < f_Limb->m_MinZ - m_Zpos)
			continue;

		if (f_Z >= f_Limb->m_MaxZ - m_Zpos)
			continue;
		
		m_VoxelLimb_MeM = f_Limb;

		return f_Limb;
		}

	return nullptr;
}

bool VoxelGrid::acMake_BlockFlight(std::shared_ptr<VoxelVector> f_VoxVector, float f_ExplosiveForcePower, float f_ExplosiveHeatIntensity)
{
	std::shared_ptr<VoxelLimb> f_Limb = OnVoxelLimb(f_VoxVector);

	if(f_Limb != nullptr)
		{
		f_Limb->m_vec_ForceOnVector.push_back(f_VoxVector);

		if(f_Limb->m_State == VoxelLimbState::LimbState_Begin)
			{
			f_Limb->m_VelocityVector = f_VoxVector->m_LoadOnVector;

			f_Limb->m_State = VoxelLimbState::LimbState_InFlight;

#if 0
			Make_Alone();
#endif
			}
		else if(f_Limb->m_State == VoxelLimbState::LimbState_AtRest)
			{
			f_Limb->m_VelocityVector = f_VoxVector->m_LoadOnVector;

			f_Limb->m_State = VoxelLimbState::LimbState_InFlight;

#if 0
			Make_Alone();
#endif
			}
		else if(f_Limb->m_State == VoxelLimbState::LimbState_InFlight)
			{
			f_Limb->m_VelocityVector += f_VoxVector->m_LoadOnVector;

#if 0
			Make_Alone();
#endif
			}
		else
			{
			//// assume empty cull
			}

		return true;
		}

	return false;
}

bool VoxelDamageMask::acSimulateFrame(float f_TimeScale)
{
	if(m_vec_MarkLayer[0]->m_ForwardSpeed > 0.0f)
		{
		return acSimulateFrameXY(f_TimeScale);
		}
	else
		{
		return acSimulateFrameGrow();
		}
}

bool VoxelDamageMask::acSimulateFrameXY(float f_TimeScale)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_SIZE = (VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	bool f_Collide = false;
	bool f_isEmpty = true;

	int f_ResultOnX = 0;
	int f_ResultOnY = 0;
	int f_ResultOnZ = 0;

	std::shared_ptr<VoxelGrid> f_GridOn = nullptr;

	for(int f_LayerIDX = 0; f_LayerIDX < m_vec_MarkLayer.size(); f_LayerIDX++)
		{
		std::shared_ptr<MarkLayer> f_MarkLayer = m_vec_MarkLayer[f_LayerIDX];

		// current point begins at impact point
		BiVector f_Cpos(0.0f);

		// Simple Rectangle Mask #
		for(f_MarkLayer->m_CurrentMark.m_VecY = 0; f_MarkLayer->m_CurrentMark.m_VecY < f_MarkLayer->m_Finish.m_VecY; f_MarkLayer->m_CurrentMark.m_VecY++)
			{
			f_Cpos.m_X = m_CurrentPoint.m_X + (m_UpVec.m_X * ((m_SingleUnit * (float)f_MarkLayer->m_CurrentMark.m_VecY) - (((m_SingleUnit / 2.0f) * (float)f_MarkLayer->m_Finish.m_VecY) + (m_SingleUnit / 2.0f))));
			f_Cpos.m_Y = m_CurrentPoint.m_Y + (m_UpVec.m_Y * ((m_SingleUnit * (float)f_MarkLayer->m_CurrentMark.m_VecY) - (((m_SingleUnit / 2.0f) * (float)f_MarkLayer->m_Finish.m_VecY) + (m_SingleUnit / 2.0f))));
			f_Cpos.m_Z = m_CurrentPoint.m_Z + (m_UpVec.m_Z * ((m_SingleUnit * (float)f_MarkLayer->m_CurrentMark.m_VecY) - (((m_SingleUnit / 2.0f) * (float)f_MarkLayer->m_Finish.m_VecY) + (m_SingleUnit / 2.0f))));

			for(f_MarkLayer->m_CurrentMark.m_VecX = 0; f_MarkLayer->m_CurrentMark.m_VecX < f_MarkLayer->m_Finish.m_VecX; f_MarkLayer->m_CurrentMark.m_VecX++)
				{
				f_Cpos.m_X = f_Cpos.m_X + (m_RightVec.m_X * ((m_SingleUnit * (float)f_MarkLayer->m_CurrentMark.m_VecX) - (((m_SingleUnit / 2.0f) * (float)f_MarkLayer->m_Finish.m_VecX) + (m_SingleUnit / 2.0f))));
				f_Cpos.m_Y = f_Cpos.m_Y + (m_RightVec.m_Y * ((m_SingleUnit * (float)f_MarkLayer->m_CurrentMark.m_VecX) - (((m_SingleUnit / 2.0f) * (float)f_MarkLayer->m_Finish.m_VecX) + (m_SingleUnit / 2.0f))));
				f_Cpos.m_Z = f_Cpos.m_Z + (m_RightVec.m_Z * ((m_SingleUnit * (float)f_MarkLayer->m_CurrentMark.m_VecX) - (((m_SingleUnit / 2.0f) * (float)f_MarkLayer->m_Finish.m_VecX) + (m_SingleUnit / 2.0f))));

				f_Collide = g_VoxelGridManager->GetActive_GlobalPoint(f_Cpos, &f_GridOn, &f_ResultOnX, &f_ResultOnY, &f_ResultOnZ);

				if(f_GridOn != nullptr)
					{
					if(f_GridOn->m_rebuild == 0)
						{
						if(f_Collide == true)
							{ // Solid Hit //
							f_GridOn->acApply_BlockDamage(f_ResultOnX + f_ResultOnY * VoxelGrid::VOXEL_GRID_SIZE + f_ResultOnZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, f_ResultOnX, f_ResultOnY, f_ResultOnZ, f_MarkLayer->m_FullEdgePower, (f_MarkLayer->m_FullEdgePower / f_MarkLayer->m_PropagationReductionPerc), (f_MarkLayer->m_FullEdgePower / WORLD_HEAT_THRESH_CELCIUS));

							// VOXDMG Reduction //
							f_MarkLayer->m_FullEdgePower -= f_MarkLayer->m_PropagationReductionPerc * 9.25f; //swk
							}
						}
					}
				}
			}

#ifdef VOXDMG_FULL_TIMESCALE
		m_CurrentPoint += m_ImpactIn * (f_MarkLayer->m_ForwardSpeed * f_TimeScale);
#else
		m_CurrentPoint += m_ImpactIn * f_MarkLayer->m_ForwardSpeed;
#endif

		if(f_MarkLayer->m_FullEdgePower <= 0.0f)
			{
			// Conditional re-order and Pop_Back()
			for(int f_Jet = f_LayerIDX; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
				{
				m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
				}

			m_vec_MarkLayer.pop_back();

			if(m_vec_MarkLayer.size() >= 1)
				{
				f_LayerIDX--;
				}
			else
				{
				f_isEmpty = true;
				}
			}
		else
			{
			f_isEmpty = false;
			}
		}

	return f_isEmpty;
}

bool VoxelDamageMask::acSimulateFrameGrow(void)
{
	if(m_vec_MarkLayer.size() < 0)
		{
		return false;
		}

	std::shared_ptr<MarkLayer> f_MarkLayer = m_vec_MarkLayer[0];
	std::shared_ptr<VoxelGrid> f_GridOn = nullptr;

	int f_ResultOnX = 0;
	int f_ResultOnY = 0;
	int f_ResultOnZ = 0;

	bool f_Collide = g_VoxelGridManager->GetActive_GlobalPoint(m_ImpactPoint, &f_GridOn, &f_ResultOnX, &f_ResultOnY, &f_ResultOnZ);

	if(f_GridOn != nullptr)
		{
		if(f_GridOn->m_rebuild == 0)
			{
			if(f_Collide == true)
				{
				f_GridOn->acApply_BlockDamage(f_ResultOnX + f_ResultOnY * VoxelGrid::VOXEL_GRID_SIZE + f_ResultOnZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, f_ResultOnX, f_ResultOnY, f_ResultOnZ, f_MarkLayer->m_FullEdgePower, f_MarkLayer->m_FullEdgePower / WORLD_REDUCE_AMT, f_MarkLayer->m_FullEdgePower);
				}
			}
		}
	else
		{
		// Conditional re-order and Pop_Back()
		for(int f_Jet = 0; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
			{
			m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
			}

		m_vec_MarkLayer.pop_back();

		if(m_vec_MarkLayer.size() <= 0)
			{
			return true;
			}
		else
			{
			return false;
			}
		}

	//Z+
	if(m_stepZ != f_ResultOnZ + m_radius)
		{
		m_stepZ = f_ResultOnZ + m_radius;

		m_stepY = f_ResultOnY - m_radius;
		m_stepX = f_ResultOnX - m_radius;
		}

	for(m_stepX = f_ResultOnX - m_radius; m_stepX < f_ResultOnX + m_radius; m_stepX++)
		{
		for(m_stepY = f_ResultOnY - m_radius; m_stepY < f_ResultOnY + m_radius; m_stepY++)
			{
			// add scene node voxelgrid
			if(f_GridOn != nullptr)
				{
				if(f_GridOn->m_rebuild == 0)
					{
					f_GridOn->acApply_BlastProp(m_stepX + m_stepY * VoxelGrid::VOXEL_GRID_SIZE + m_stepZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, m_stepX, m_stepY, m_stepZ, f_MarkLayer->m_FullEdgePower, m_ImpactPoint);
					}
				}

			m_Count++;

			if(m_Count >= WORLD_FRAME_COUNT)
				{
				return true;
				}

			f_MarkLayer->m_FullEdgePower /= (1.0f + ((1.0f / WORLD_CUBE_RESIST_AIR_POWER) / f_MarkLayer->m_PropagationReductionPerc));

			if(f_MarkLayer->m_FullEdgePower <= 0.0f)
				{
				// Conditional re-order and Pop_Back()
				for(int f_Jet = 0; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
					{
					m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
					}

				m_vec_MarkLayer.pop_back();

				if(m_vec_MarkLayer.size() <= 0)
					{
					return true;
					}
				else
					{
					return false;
					}
				}
			}
		}

	//Z-
	if(m_stepZ != f_ResultOnZ - m_radius)
		{
		m_stepZ = f_ResultOnZ - m_radius;

		m_stepY = f_ResultOnY - m_radius;
		m_stepX = f_ResultOnX - m_radius;
		}

	for(m_stepX = f_ResultOnX - m_radius; m_stepX < f_ResultOnX + m_radius; m_stepX++)
		{
		for(m_stepY = f_ResultOnY - m_radius; m_stepY < f_ResultOnY + m_radius; m_stepY++)
			{
			// add scene node voxelgrid
			if(f_GridOn != nullptr)
				{
				if(f_GridOn->m_rebuild == 0)
					{
					f_GridOn->acApply_BlastProp(m_stepX + m_stepY * VoxelGrid::VOXEL_GRID_SIZE + m_stepZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, m_stepX, m_stepY, m_stepZ, f_MarkLayer->m_FullEdgePower, m_ImpactPoint);
					}
				}

			m_Count++;

			if(m_Count >= WORLD_FRAME_COUNT)
				{
				return true;
				}

			f_MarkLayer->m_FullEdgePower /= (1.0f + ((1.0f / WORLD_CUBE_RESIST_AIR_POWER) / f_MarkLayer->m_PropagationReductionPerc));

			if(f_MarkLayer->m_FullEdgePower <= 0.0f)
				{
				// Conditional re-order and Pop_Back()
				for(int f_Jet = 0; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
					{
					m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
					}

				m_vec_MarkLayer.pop_back();

				if(m_vec_MarkLayer.size() <= 0)
					{
					return true;
					}
				else
					{
					return false;
					}
				}
			}
		}
	
	//Y+
	if(m_stepY != f_ResultOnY + m_radius)
		{
		m_stepZ = f_ResultOnY + m_radius;

		m_stepX = f_ResultOnX - m_radius;
		m_stepY = f_ResultOnY - m_radius;
		}

	for(m_stepX = f_ResultOnX - m_radius; m_stepX < f_ResultOnX + m_radius; m_stepX++)
		{
		for(m_stepZ = f_ResultOnY - m_radius; m_stepZ < f_ResultOnY + m_radius; m_stepZ++)
			{
			// add scene node voxelgrid
			if(f_GridOn != nullptr)
				{
				if(f_GridOn->m_rebuild == 0)
					{
					f_GridOn->acApply_BlastProp(m_stepX + m_stepY * VoxelGrid::VOXEL_GRID_SIZE + m_stepZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, m_stepX, m_stepY, m_stepZ, f_MarkLayer->m_FullEdgePower, m_ImpactPoint);
					}
				}

			m_Count++;

			if(m_Count >= WORLD_FRAME_COUNT)
				{
				return true;
				}

			f_MarkLayer->m_FullEdgePower /= (1.0f + ((1.0f / WORLD_CUBE_RESIST_AIR_POWER) / f_MarkLayer->m_PropagationReductionPerc));

			if(f_MarkLayer->m_FullEdgePower <= 0.0f)
				{
				// Conditional re-order and Pop_Back()
				for(int f_Jet = 0; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
					{
					m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
					}

				m_vec_MarkLayer.pop_back();

				if(m_vec_MarkLayer.size() <= 0)
					{
					return true;
					}
				else
					{
					return false;
					}
				}
			}
		}

	//Y-
	if(m_stepY != f_ResultOnY - m_radius)
		{
		m_stepZ = f_ResultOnY - m_radius;

		m_stepX = f_ResultOnX - m_radius;
		m_stepY = f_ResultOnY - m_radius;
		}

	for(m_stepX = f_ResultOnX - m_radius; m_stepX < f_ResultOnX + m_radius; m_stepX++)
		{
		for(m_stepY = f_ResultOnY - m_radius; m_stepY < f_ResultOnY + m_radius; m_stepY++)
			{
			// add scene node voxelgrid
			if(f_GridOn != nullptr)
				{
				if(f_GridOn->m_rebuild == 0)
					{
					f_GridOn->acApply_BlastProp(m_stepX + m_stepY * VoxelGrid::VOXEL_GRID_SIZE + m_stepZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, m_stepX, m_stepY, m_stepZ, f_MarkLayer->m_FullEdgePower, m_ImpactPoint);
					}
				}

			m_Count++;

			if(m_Count >= WORLD_FRAME_COUNT)
				{
				return true;
				}

			f_MarkLayer->m_FullEdgePower /= (1.0f + ((1.0f / WORLD_CUBE_RESIST_AIR_POWER) / f_MarkLayer->m_PropagationReductionPerc));

			if(f_MarkLayer->m_FullEdgePower <= 0.0f)
				{
				// Conditional re-order and Pop_Back()
				for(int f_Jet = 0; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
					{
					m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
					}

				m_vec_MarkLayer.pop_back();

				if(m_vec_MarkLayer.size() <= 0)
					{
					return true;
					}
				else
					{
					return false;
					}
				}
			}
		}

	//X+
	if(m_stepX != f_ResultOnX + m_radius)
		{
		m_stepX = f_ResultOnX + m_radius;

		m_stepY = f_ResultOnY - m_radius;
		m_stepZ = f_ResultOnZ - m_radius;
		}

	for(m_stepY = f_ResultOnY - m_radius; m_stepY < f_ResultOnY + m_radius; m_stepY++)
		{
		for(m_stepZ = f_ResultOnZ - m_radius; m_stepZ < f_ResultOnZ + m_radius; m_stepZ++)
			{
			// add scene node voxelgrid
			if(f_GridOn != nullptr)
				{
				if(f_GridOn->m_rebuild == 0)
					{
					f_GridOn->acApply_BlastProp(m_stepX + m_stepY * VoxelGrid::VOXEL_GRID_SIZE + m_stepZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, m_stepX, m_stepY, m_stepZ, f_MarkLayer->m_FullEdgePower, m_ImpactPoint);
					}
				}

			m_Count++;

			if(m_Count >= WORLD_FRAME_COUNT)
				{
				return true;
				}

			f_MarkLayer->m_FullEdgePower /= (1.0f + ((1.0f / WORLD_CUBE_RESIST_AIR_POWER) / f_MarkLayer->m_PropagationReductionPerc));

			if(f_MarkLayer->m_FullEdgePower <= 0.0f)
				{
				// Conditional re-order and Pop_Back()
				for(int f_Jet = 0; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
					{
					m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
					}

				m_vec_MarkLayer.pop_back();

				if(m_vec_MarkLayer.size() <= 0)
					{
					return true;
					}
				else
					{
					return false;
					}
				}
			}
		}

	//X-
	if(m_stepX != f_ResultOnX - m_radius)
		{
		m_stepX = f_ResultOnX - m_radius;

		m_stepY = f_ResultOnY - m_radius;
		m_stepZ = f_ResultOnZ - m_radius;
		}

	for(m_stepY = f_ResultOnX - m_radius; m_stepY < f_ResultOnX + m_radius; m_stepY++)
		{
		for(m_stepZ = f_ResultOnY - m_radius; m_stepZ < f_ResultOnY + m_radius; m_stepZ++)
			{
			// add scene node voxelgrid
			if(f_GridOn != nullptr)
				{
				if(f_GridOn->m_rebuild == 0)
					{
					f_GridOn->acApply_BlastProp(m_stepX + m_stepY * VoxelGrid::VOXEL_GRID_SIZE + m_stepZ * VoxelGrid::VOXEL_GRID_SIZE_SQUARED, m_stepX, m_stepY, m_stepZ, f_MarkLayer->m_FullEdgePower, m_ImpactPoint);
					}
				}

			m_Count++;

			if(m_Count >= WORLD_FRAME_COUNT)
				{
				return true;
				}

			f_MarkLayer->m_FullEdgePower /= (1.0f + ((1.0f / WORLD_CUBE_RESIST_AIR_POWER) / f_MarkLayer->m_PropagationReductionPerc));

			if(f_MarkLayer->m_FullEdgePower <= 0.25f)
				{
				// Conditional re-order and Pop_Back()
				for(int f_Jet = 0; f_Jet < (m_vec_MarkLayer.size() - 1); f_Jet++)
					{
					m_vec_MarkLayer[f_Jet] = m_vec_MarkLayer[f_Jet + 1];
					}

				m_vec_MarkLayer.pop_back();

				if(m_vec_MarkLayer.size() <= 0)
					{
					return true;
					}
				else
					{
					return false;
					}
				}
			}
		}

	return true;
}

void VoxelGridManager::UpdateVoxelGridNeighbours(std::shared_ptr<VoxelGrid> pVoxelGrid, int x, int y, int z)
{
#if 0
	pVoxelGrid->SetNumNeighbours(0);

	std::shared_ptr<VoxelGrid> pVoxelGridXMinus = GetVoxelGrid(x - 1, y, z);
	std::shared_ptr<VoxelGrid> pVoxelGridXPlus = GetVoxelGrid(x + 1, y, z);
	std::shared_ptr<VoxelGrid> pVoxelGridYMinus = GetVoxelGrid(x, y - 1, z);
	std::shared_ptr<VoxelGrid> pVoxelGridYPlus = GetVoxelGrid(x, y + 1, z);
	std::shared_ptr<VoxelGrid> pVoxelGridZMinus = GetVoxelGrid(x, y, z - 1);
	std::shared_ptr<VoxelGrid> pVoxelGridZPlus = GetVoxelGrid(x, y, z + 1);

	if (pVoxelGridXMinus)
	{
		pVoxelGrid->SetNumNeighbours(pVoxelGrid->GetNumNeighbours() + 1);
		pVoxelGrid->SetxMinus(pVoxelGridXMinus);
		if (pVoxelGridXMinus->GetxPlus() == NULL)
		{
			pVoxelGridXMinus->SetNumNeighbours(pVoxelGridXMinus->GetNumNeighbours() + 1);
			pVoxelGridXMinus->SetxPlus(pVoxelGrid);
		}
	}
	if (pVoxelGridXPlus)
	{
		pVoxelGrid->SetNumNeighbours(pVoxelGrid->GetNumNeighbours() + 1);
		pVoxelGrid->SetxPlus(pVoxelGridXPlus);
		if (pVoxelGridXPlus->GetxMinus() == NULL)
		{
			pVoxelGridXPlus->SetNumNeighbours(pVoxelGridXPlus->GetNumNeighbours() + 1);
			pVoxelGridXPlus->SetxMinus(pVoxelGrid);
		}
	}
	if (pVoxelGridYMinus)
	{
		pVoxelGrid->SetNumNeighbours(pVoxelGrid->GetNumNeighbours() + 1);
		pVoxelGrid->SetyMinus(pVoxelGridYMinus);
		if (pVoxelGridYMinus->GetyPlus() == NULL)
		{
			pVoxelGridYMinus->SetNumNeighbours(pVoxelGridYMinus->GetNumNeighbours() + 1);
			pVoxelGridYMinus->SetyPlus(pVoxelGrid);
		}
	}
	if (pVoxelGridYPlus)
	{
		pVoxelGrid->SetNumNeighbours(pVoxelGrid->GetNumNeighbours() + 1);
		pVoxelGrid->SetyPlus(pVoxelGridYPlus);
		if (pVoxelGridYPlus->GetyMinus() == NULL)
		{
			pVoxelGridYPlus->SetNumNeighbours(pVoxelGridYPlus->GetNumNeighbours() + 1);
			pVoxelGridYPlus->SetyMinus(pVoxelGrid);
		}
	}
	if (pVoxelGridZMinus)
	{
		pVoxelGrid->SetNumNeighbours(pVoxelGrid->GetNumNeighbours() + 1);
		pVoxelGrid->SetzMinus(pVoxelGridZMinus);
		if (pVoxelGridZMinus->GetzPlus() == NULL)
		{
			pVoxelGridZMinus->SetNumNeighbours(pVoxelGridZMinus->GetNumNeighbours() + 1);
			pVoxelGridZMinus->SetzPlus(pVoxelGrid);
		}
	}
	if (pVoxelGridZPlus)
	{
		pVoxelGrid->SetNumNeighbours(pVoxelGrid->GetNumNeighbours() + 1);
		pVoxelGrid->SetzPlus(pVoxelGridZPlus);
		if (pVoxelGridZPlus->GetzMinus() == NULL)
		{
			pVoxelGridZPlus->SetNumNeighbours(pVoxelGridZPlus->GetNumNeighbours() + 1);
			pVoxelGridZPlus->SetzMinus(pVoxelGrid);
		}
	}
#else
	std::shared_ptr<VoxelGrid> f_XPlus = GetVoxelGrid(x + 1, y, z);
	std::shared_ptr<VoxelGrid> f_XMinus = GetVoxelGrid(x - 1, y, z);
	std::shared_ptr<VoxelGrid> f_YPlus = GetVoxelGrid(x, y + 1, z);
	std::shared_ptr<VoxelGrid> f_YMinus = GetVoxelGrid(x, y - 1, z);
	std::shared_ptr<VoxelGrid> f_ZPlus = GetVoxelGrid(x, y, z + 1);
	std::shared_ptr<VoxelGrid> f_ZMinus = GetVoxelGrid(x, y, z - 1);

	if(f_XPlus) f_XPlus->SetNeedsRebuild(true, true);
	if(f_XMinus) f_XMinus->SetNeedsRebuild(true, true);
	if(f_YPlus) f_YPlus->SetNeedsRebuild(true, true);
	if(f_YMinus) f_YMinus->SetNeedsRebuild(true, true);
	if(f_ZPlus) f_ZPlus->SetNeedsRebuild(true, true);
	if(f_ZMinus) f_ZMinus->SetNeedsRebuild(true, true);
#endif
}

float ag_BlockType_Varg(BlockType f_BlockType, int f_BlockArg)
{
	switch(f_BlockArg)
		{
		case BlockArg_Flight_Thresh:
			{
			switch(f_BlockType)
				{
				case BlockType_Iron:
					{
					return /*ReflectionBridge*/ 315.0f;
					}break;

				case BlockType_Cement:
					{
					return /*ReflectionBridge*/ 400.0f;
					}break;

				case BlockType_Steel:
					{
					return /*ReflectionBridge*/ 400.0f;
					}break;

				case BlockType_Brick:
					{
					return /*ReflectionBridge*/ 215.0f;
					}break;

				case BlockType_Wood:
					{
					return /*ReflectionBridge*/ 89.0f;
					}break;

				case BlockType_Stone:
					{
					return /*ReflectionBridge*/ 289.0f;
					}break;

				case BlockType_Metal:
					{
					return /*ReflectionBridge*/ 400.0f;
					}break;

				case BlockType_Plaster:
					{
					return /*ReflectionBridge*/ 60.0f;
					}break;

				case BlockType_Glass:
					{
					return /*ReflectionBridge*/ 140.0f;
					}break;

				case BlockType_Qcom_Default:
					{
					//...
					}break;
				}
			}break;

		case BlockArg_Heat_Resistance:
			{
			switch(f_BlockType)
				{
				case BlockType_Iron:
					{
					return /*ReflectionBridge*/ 615.0f;
					}break;

				case BlockType_Cement:
					{
					return /*ReflectionBridge*/ 400.0f;
					}break;

				case BlockType_Steel:
					{
					return /*ReflectionBridge*/ 500.0f;
					}break;

				case BlockType_Brick:
					{
					return /*ReflectionBridge*/ 215.0f;
					}break;

				case BlockType_Wood:
					{
					return /*ReflectionBridge*/ 48.0f;
					}break;

				case BlockType_Stone:
					{
					return /*ReflectionBridge*/ 189.0f;
					}break;

				case BlockType_Metal:
					{
					return /*ReflectionBridge*/ 450.0f;
					}break;

				case BlockType_Plaster:
					{
					return /*ReflectionBridge*/ 40.0f;
					}break;

				case BlockType_Glass:
					{
					return /*ReflectionBridge*/ 50.0f;
					}break;

				case BlockType_Qcom_Default:
					{
					//...
					}break;
				}
			}break;

		case BlockArg_Strength:
			{
			switch(f_BlockType)
				{
				case BlockType_Default:
					{
					return WORLD_BLOCK_STRENGTH_DEFAULT;
					} break;
		
				case BlockType_Iron:
					{
					return 750.0f;
					} break;

				case BlockType_Cement:
					{
					return 175.0f;
					} break;

				case BlockType_Steel:
					{
					return 600.0f;
					} break;

				case BlockType_Brick:
					{
					return 150.0f;
					} break;

				case BlockType_Wood:
					{
					return 105.0f;
					} break;

				case BlockType_Stone:
					{
					return 500.0f;
					} break;

				case BlockType_Metal:
					{
					return 285.0f;
					} break;

				case BlockType_Plaster:
					{
					return 65.0f;
					} break;

				case BlockType_Glass:
					{
					return 38.0f;
					} break;
				}
			}break;

		case BlockArg_Weight:
			{
			switch(f_BlockType)
				{
				case BlockType_Default:
					{
					return 1.0;
					} break;
		
				case BlockType_Iron:
					{
					return 290.7407;
					} break;

				case BlockType_Cement:
					{
					return 53.3333;
					} break;

				case BlockType_Steel:
					{
					return 32.3045;
					} break;

				case BlockType_Brick:
					{
					return 6.7901;
					} break;

				case BlockType_Wood:
					{
					return 1.8518;
					} break;

				case BlockType_Stone:
					{
					return 10.4115;
					} break;

				case BlockType_Metal:
					{
					return 285.0f;
					} break;

				case BlockType_Plaster:
					{
					return 65.0f;
					} break;

				case BlockType_Glass:
					{
					return 38.0f;
					} break;
				}
			}break;

#if 0
		case BlockArg_Flight_Thresh:
			{
			switch(f_BlockType)
				{
				case BlockType_Iron:
					{
					return /*ReflectionBridge*/ 615.0f;
					}break;

				case BlockType_Cement:
					{
					return /*ReflectionBridge*/ 400.0f;
					}break;

				case BlockType_Steel:
					{
					return /*ReflectionBridge*/ 500.0f;
					}break;

				case BlockType_Brick:
					{
					return /*ReflectionBridge*/ 215.0f;
					}break;

				case BlockType_Wood:
					{
					return /*ReflectionBridge*/ 48.0f;
					}break;

				case BlockType_Stone:
					{
					return /*ReflectionBridge*/ 189.0f;
					}break;

				case BlockType_Metal:
					{
					return /*ReflectionBridge*/ 450.0f;
					}break;

				case BlockType_Plaster:
					{
					return /*ReflectionBridge*/ 40.0f;
					}break;

				case BlockType_Glass:
					{
					return /*ReflectionBridge*/ 50.0f;
					}break;

				case BlockType_Qcom_Default:
					{
					//...
					}break;
				}
			}break;

		case BlockArg_Flight_Thresh:
			{
			switch(f_BlockType)
				{
				case BlockType_Iron:
					{

					}break;

				case BlockType_Cement:
					{

					}break;

				case BlockType_Steel:
					{

					}break;

				case BlockType_Brick:
					{

					}break;

				case BlockType_Wood:
					{

					}break;

				case BlockType_Stone:
					{

					}break;

				case BlockType_Metal:
					{

					}break;

				case BlockType_Plaster:
					{

					}break;

				case BlockType_Glass:
					{

					}break;

				case BlockType_Qcom_Default:
					{

					}break;
				}
			}break;

		case BlockArg_Flight_Thresh:
			{
			switch(f_BlockType)
				{
				case BlockType_Iron:
					{

					}break;

				case BlockType_Cement:
					{

					}break;

				case BlockType_Steel:
					{

					}break;

				case BlockType_Brick:
					{

					}break;

				case BlockType_Wood:
					{

					}break;

				case BlockType_Stone:
					{

					}break;

				case BlockType_Metal:
					{

					}break;

				case BlockType_Plaster:
					{

					}break;

				case BlockType_Glass:
					{

					}break;

				case BlockType_Qcom_Default:
					{

					}break;
				}
			}break;

		case BlockArg_Flight_Thresh:
			{
			switch(f_BlockType)
				{
				case BlockType_Iron:
					{

					}break;

				case BlockType_Cement:
					{

					}break;

				case BlockType_Steel:
					{

					}break;

				case BlockType_Brick:
					{

					}break;

				case BlockType_Wood:
					{

					}break;

				case BlockType_Stone:
					{

					}break;

				case BlockType_Metal:
					{

					}break;

				case BlockType_Plaster:
					{

					}break;

				case BlockType_Glass:
					{

					}break;

				case BlockType_Qcom_Default:
					{

					}break;
				}
			}break;
#endif
		}

	return 0.0f;
}

};