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

#if 0
#define VOXEL_NEIGHBOURHOOD true
#endif

using namespace GVARS;
using namespace Cube;
using namespace std;

int g_Width = 2560;
int g_Height = 1440;

namespace Cube
{

bool IsMergedXNegative(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_X_Negative) == MergedSide_X_Negative; }
bool IsMergedXPositive(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_X_Positive) == MergedSide_X_Positive; }
bool IsMergedYNegative(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Y_Negative) == MergedSide_Y_Negative; }
bool IsMergedYPositive(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Y_Positive) == MergedSide_Y_Positive; }
bool IsMergedZNegative(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Z_Negative) == MergedSide_Z_Negative; }
bool IsMergedZPositive(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Z_Positive) == MergedSide_Z_Positive; }

//Grid Manager
std::shared_ptr<VoxelGridManager> g_VoxelGridManager;

//Warzone of Grid Manager
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

VoxelGrid::VoxelGrid()
{
	throw;
}

VoxelGrid::VoxelGrid(int f_ManagerIndex)
{
	m_rebuild = 1;

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

	mVertexFloor1StrBuffer = 0;
	mVertexFloor2StrBuffer = 0;
	mVertexFloor1RedBuffer = 0;
	mVertexFloor2RedBuffer = 0;
	mVertexFloor1GreenBuffer = 0;
	mVertexFloor2GreenBuffer = 0;
	mVertexFloor1BlueBuffer = 0;
	mVertexFloor2BlueBuffer = 0;

	m_War_Zone = nullptr;

	Initialize();
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

	m_XSub_full = false;
	m_XAdd_full = false;
	m_YSub_full = false;
	m_YAdd_full = false;
	m_ZSub_full = false;
	m_ZAdd_full = false;

	m_PlacedIn = false;
	m_PlacedInLast = false;
}

// Creation and destruction
void VoxelGrid::SetCreated(bool created)
{
	m_created = created;
}

bool VoxelGrid::IsCreated(void)
{
	return m_created;
}

void VoxelGrid::Setup(void)
{
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
					float yPosition = m_position.m_Y + (y * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

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
		return BlockType_Default;

	return m_VX_Core->m_blockType[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

bool VoxelGrid::GetActive(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		return false;

	unsigned int colour = m_VX_Core->m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
	unsigned int alpha = (colour & 0xFF000000) >> 24;
	unsigned int blue = (colour & 0x00FF0000) >> 16;
	unsigned int green = (colour & 0x0000FF00) >> 8;
	unsigned int red = (colour & 0x000000FF);

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
#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif

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

bool VoxelGridManager::GetActive_GlobalPoint(BiVector position, std::shared_ptr<VoxelGrid> f_ResultGrid, int* f_ResultX, int* f_ResultY, int* f_ResultZ)
{
	int gridX;
	int gridY;
	int gridZ;

	GetGridFromPosition(position, &gridX, &gridY, &gridZ);

	std::shared_ptr<VoxelGrid> f_Grid = GetVoxelGrid(gridX, gridY, gridZ);

	if(f_Grid != nullptr)
		{
		if (f_Grid->m_rebuild == 1)
			return false;

		int f_Local_X = (position.m_X / (VOXEL_RENDER_SIZE * 2)) - (VoxelGrid::VOXEL_GRID_SIZE * gridX);
		int f_Local_Y = (position.m_X / (VOXEL_RENDER_SIZE * 2)) - (VoxelGrid::VOXEL_GRID_SIZE * gridX);
		int f_Local_Z = (position.m_X / (VOXEL_RENDER_SIZE * 2)) - (VoxelGrid::VOXEL_GRID_SIZE * gridX);

		if ((f_Local_X < 0) || (f_Local_X >= VoxelGrid::VOXEL_GRID_SIZE) ||
			(f_Local_Y < 0) || (f_Local_Y >= VoxelGrid::VOXEL_GRID_SIZE) ||
			(f_Local_Z < 0) || (f_Local_Z >= VoxelGrid::VOXEL_GRID_SIZE))
			{
#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif

			return false;
			}

		unsigned int colour = f_Grid->m_VX_Core->m_colour[f_Local_X + f_Local_Y * VoxelGrid::VOXEL_GRID_SIZE + f_Local_Z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
		unsigned int alpha = (colour & 0xFF000000) >> 24;
		unsigned int blue = (colour & 0x00FF0000) >> 16;
		unsigned int green = (colour & 0x0000FF00) >> 8;
		unsigned int red = (colour & 0x000000FF);

		if (alpha > 0)
			{
			*(f_ResultX) = f_Local_X;
			*(f_ResultY) = f_Local_Y;
			*(f_ResultZ) = f_Local_Z;

			return true;
			}
		}

	return false;
}

float VoxelGrid::GetStrength(int x, int y, int z)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return 0.0f;

	float f_Result = m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];

	return f_Result;
}

void VoxelGrid::GetColour(int x, int y, int z, float* r, float* g, float* b, float* a)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

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

// Block colour
void VoxelGrid::SetColour(int x, int y, int z, float r, float g, float b, float a, bool setBlockType)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

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
	if((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

	bool changed = ((m_VX_Core->m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] == colour) == false);

	if(changed)
		{
		m_VoxelGridChangedDuringBatchUpdate = true;
		}

	m_VX_Core->m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = colour;

	if(setBlockType)
		{
		unsigned int blockB = (colour & 0x00FF0000) >> 16;
		unsigned int blockG = (colour & 0x0000FF00) >> 8;
		unsigned int blockR = (colour & 0x000000FF);
		m_VX_Core->m_blockType[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = BlockType_Default;
		}
}

void VoxelGrid::SetColourType(int x, int y, int z, float r, float g, float b, float a, BlockType f_BlockType)
{
	if((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

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
	SetColourType(x, y, z, colour, f_BlockType);
}

void VoxelGrid::SetColourType(int x, int y, int z, unsigned int colour, BlockType f_BlockType)
{
	if((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

	bool changed = ((m_VX_Core->m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] == colour) == false);

	if(changed)
		{
		m_VoxelGridChangedDuringBatchUpdate = true;
		}

	m_VX_Core->m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = colour;
	m_VX_Core->m_blockType[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = BlockType_Default;
	
	switch(f_BlockType)
		{
		case BlockType_Default:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = WORLD_BLOCK_STRENGTH_DEFAULT;
			} break;
		
		case BlockType_Iron:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 750.0f;
			} break;

		case BlockType_Cement:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 175.0f;
			} break;

		case BlockType_Steel:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 600.0f;
			} break;

		case BlockType_Brick:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 150.0f;
			} break;

		case BlockType_Wood:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 105.0f;
			} break;

		case BlockType_Stone:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 500.0f;
			} break;

		case BlockType_Metal:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 285.0f;
			} break;

		case BlockType_Plaster:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 65.0f;
			} break;

		case BlockType_Glass:
			{
			m_VX_Core->m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 38.0f;
			} break;
		}
}

void VoxelGrid::SetStrength(int x, int y, int z, float f_Strength)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		return;

	m_VX_Core->m_blockStrength[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED] = f_Strength;
}

unsigned int VoxelGrid::GetColour(int x, int y, int z)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		return 0;

	return m_VX_Core->m_colour[x + y * VoxelGrid::VOXEL_GRID_SIZE + z * VoxelGrid::VOXEL_GRID_SIZE_SQUARED];
}

// Block type
void VoxelGrid::SetBlockType(int x, int y, int z, BlockType blockType)
{
	if ((x < 0) || (x >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VoxelGrid::VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VoxelGrid::VOXEL_GRID_SIZE))
		return;

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

unsigned int VoxelGridManager::AddVertexToMeshNeighbourhood(std::shared_ptr<VoxelGrid> f_VoxelGrid, int str_x, int str_y, int str_z, BiVector p1, BiVector n1, float r, float g, float b, float a)
{
#if 0
	   //////////////////
	  // m_vec Mesh
	 //
	//
	f_VoxelGrid->m_vec_Vertex.push_back(std::make_shared<BiVector>(p1.m_X + f_VoxelGrid->m_position.m_X, p1.m_Y + f_VoxelGrid->m_position.m_Y, (p1.m_Z * -1.0f) + (f_VoxelGrid->m_position.m_Z * -1.0f)));
	f_VoxelGrid->m_vec_Normal.push_back(std::make_shared<BiVector>(n1.m_X, n1.m_Y, n1.m_Z * -1.0f));
	f_VoxelGrid->m_vec_Color.push_back(std::make_shared<BiColor>(r, g, b, a));

	  ////////////////////
	 // Neighbourhood
	//
	for(int f_x = str_x; f_x < (str_x + 2); f_x++)
		{
		for(int f_y = str_y; f_y < (str_y + 2); f_y++)
			{
			for(int f_z = str_z; f_z < (str_z + 2); f_z++)
				{
				int f_gridX = f_VoxelGrid->m_gridX;
				int f_gridY = f_VoxelGrid->m_gridY;
				int f_gridZ = f_VoxelGrid->m_gridZ;

				int f_blkX = f_x;
				int f_blkY = f_y;
				int f_blkZ = f_z;

				if(f_x < 0)
					{
					f_gridX--;
					f_blkX = VoxelGrid::VOXEL_GRID_SIZE + f_blkX;
					}

				if(f_x >= VoxelGrid::VOXEL_GRID_SIZE)
					{
					f_gridX++;
					f_blkX = f_blkX - VoxelGrid::VOXEL_GRID_SIZE;
					}

				if(f_y < 0)
					{
					f_gridY--;
					f_blkY = VoxelGrid::VOXEL_GRID_SIZE + f_blkY;
					}

				if(f_y >= VoxelGrid::VOXEL_GRID_SIZE)
					{
					f_gridY++;
					f_blkY = f_blkY - VoxelGrid::VOXEL_GRID_SIZE;
					}

				if(f_z < 0)
					{
					f_gridZ--;
					f_blkZ = VoxelGrid::VOXEL_GRID_SIZE + f_blkZ;
					}

				if(f_z >= VoxelGrid::VOXEL_GRID_SIZE)
					{
					f_gridZ++;
					f_blkZ = f_blkZ - VoxelGrid::VOXEL_GRID_SIZE;
					}

				std::shared_ptr<VoxelGrid> f_Voxel = GetVoxelGrid(f_gridX, f_gridY, f_gridZ);

				  ////////////////
				 // Voxel
				//
				if(f_Voxel)
					{
					if(f_Voxel->m_created == true)
						{
						if(f_blkX >= 0 &&
							f_blkX < VoxelGrid::VOXEL_GRID_SIZE &&
							f_blkY >= 0 &&
							f_blkY < VoxelGrid::VOXEL_GRID_SIZE &&
							f_blkZ >= 0 &&
							f_blkZ < VoxelGrid::VOXEL_GRID_SIZE)
							{
							if(f_Voxel->GetActive(f_blkX, f_blkY, f_blkZ) == true)
								{
								if(f_y - str_y == 0)
									{
									f_VoxelGrid->m_vec_Floor1Str.push_back(f_Voxel->GetStrength(f_blkX, f_blkY, f_blkZ));

									float* f_R = new float(0);
									float* f_G = new float(0);
									float* f_B = new float(0);
									float* f_A = new float(0);

									f_Voxel->GetColour(f_blkX, f_blkY, f_blkZ, f_R, f_G, f_B, f_A);

									f_VoxelGrid->m_vec_Floor1Red.push_back(*f_R);
									f_VoxelGrid->m_vec_Floor1Green.push_back(*f_G);
									f_VoxelGrid->m_vec_Floor1Blue.push_back(*f_B);
									}
								else if(f_y - str_y == 1)
									{
									f_VoxelGrid->m_vec_Floor2Str.push_back(f_Voxel->GetStrength(f_blkX, f_blkY, f_blkZ));

									float* f_R = new float(0);
									float* f_G = new float(0);
									float* f_B = new float(0);
									float* f_A = new float(0);

									f_Voxel->GetColour(f_blkX, f_blkY, f_blkZ, f_R, f_G, f_B, f_A);

									f_VoxelGrid->m_vec_Floor2Red.push_back(*f_R);
									f_VoxelGrid->m_vec_Floor2Green.push_back(*f_G);
									f_VoxelGrid->m_vec_Floor2Blue.push_back(*f_B);
									}
								/*else if(f_y - str_y == 2)
									{
									f_VoxelGrid->m_vec_Floor3Str.push_back(f_Voxel->GetStrength(f_blkX, f_blkY, f_blkZ));

									float* f_R = new float(0);
									float* f_G = new float(0);
									float* f_B = new float(0);
									float* f_A = new float(0);

									f_Voxel->GetColour(f_blkX, f_blkY, f_blkZ, f_R, f_G, f_B, f_A);

									//f_VoxelGrid->m_vec_Floor3Red.push_back(*f_R);
									//f_VoxelGrid->m_vec_Floor3Green.push_back(*f_G);
									//f_VoxelGrid->m_vec_Floor3Blue.push_back(*f_B);
									}*/
								/*else if(f_y - str_y == 3)
									{
									f_VoxelGrid->m_vec_Floor4Str.push_back(f_Voxel->GetStrength(f_blkX, f_blkY, f_blkZ));

									float* f_R = new float(0);
									float* f_G = new float(0);
									float* f_B = new float(0);
									float* f_A = new float(0);

									f_Voxel->GetColour(f_blkX, f_blkY, f_blkZ, f_R, f_G, f_B, f_A);

									f_VoxelGrid->m_vec_Floor4Red.push_back(*f_R);
									f_VoxelGrid->m_vec_Floor4Green.push_back(*f_G);
									f_VoxelGrid->m_vec_Floor4Blue.push_back(*f_B);
									}*/
								}
							else // !GetActive()
								{
								if(f_y - str_y == 0)
									{
									f_VoxelGrid->m_vec_Floor1Str.push_back(0.0f);
									f_VoxelGrid->m_vec_Floor1Red.push_back(0.0f);
									f_VoxelGrid->m_vec_Floor1Green.push_back(0.0f);
									f_VoxelGrid->m_vec_Floor1Blue.push_back(0.0f);
									}
								else if(f_y - str_y == 1)
									{
									f_VoxelGrid->m_vec_Floor2Str.push_back(0.0f);
									f_VoxelGrid->m_vec_Floor2Red.push_back(0.0f);
									f_VoxelGrid->m_vec_Floor2Green.push_back(0.0f);
									f_VoxelGrid->m_vec_Floor2Blue.push_back(0.0f);
									}
								/*else if(f_y - str_y == 2)
									{
									f_VoxelGrid->m_vec_Floor3Str.push_back(0.0f);
									//f_VoxelGrid->m_vec_Floor3Red.push_back(0.0f);
									//f_VoxelGrid->m_vec_Floor3Green.push_back(0.0f);
									//f_VoxelGrid->m_vec_Floor3Blue.push_back(0.0f);
									}*/
								/*else if(f_y - str_y == 3)
									{
									//f_VoxelGrid->m_vec_Floor4Str.push_back(0.0f);
									//f_VoxelGrid->m_vec_Floor4Red.push_back(0.0f);
									//f_VoxelGrid->m_vec_Floor4Green.push_back(0.0f);
									//f_VoxelGrid->m_vec_Floor4Blue.push_back(0.0f);
									}*/
								}
							}
						}
					}
				else // !Voxel
					{
					if(f_y - str_y == 0)
						{
						f_VoxelGrid->m_vec_Floor1Str.push_back(0.0f);
						f_VoxelGrid->m_vec_Floor1Red.push_back(0.0f);
						f_VoxelGrid->m_vec_Floor1Green.push_back(0.0f);
						f_VoxelGrid->m_vec_Floor1Blue.push_back(0.0f);
						}
					else if(f_y - str_y == 1)
						{
						f_VoxelGrid->m_vec_Floor2Str.push_back(0.0f);
						f_VoxelGrid->m_vec_Floor2Red.push_back(0.0f);
						f_VoxelGrid->m_vec_Floor2Green.push_back(0.0f);
						f_VoxelGrid->m_vec_Floor2Blue.push_back(0.0f);
						}
					/*else if(f_y - str_y == 2)
						{
						f_VoxelGrid->m_vec_Floor3Str.push_back(0.0f);
						//f_VoxelGrid->m_vec_Floor3Red.push_back(0.0f);
						//f_VoxelGrid->m_vec_Floor3Green.push_back(0.0f);
						//f_VoxelGrid->m_vec_Floor3Blue.push_back(0.0f);
						}*/
					/*else if(f_y - str_y == 3)
						{
						//f_VoxelGrid->m_vec_Floor4Str.push_back(0.0f);
						//f_VoxelGrid->m_vec_Floor4Red.push_back(0.0f);
						//f_VoxelGrid->m_vec_Floor4Green.push_back(0.0f);
						//f_VoxelGrid->m_vec_Floor4Blue.push_back(0.0f);
						}*/
					}
				}
			}
		}

#if 0
	printf("f_VoxelGrid->m_vec_Floor1Str.size() = %i\n", f_VoxelGrid->m_vec_Floor1Str.size());
	printf("f_VoxelGrid->m_vec_Floor2Str.size() = %i\n", f_VoxelGrid->m_vec_Floor2Str.size());
	printf("f_VoxelGrid->m_vec_Floor3Str.size() = %i\n", f_VoxelGrid->m_vec_Floor3Str.size());
	printf("f_VoxelGrid->m_vec_Floor4Str.size() = %i\n", f_VoxelGrid->m_vec_Floor4Str.size());
#endif

	return f_VoxelGrid->m_vec_Vertex.size() - 1;
#endif

	return 0;
}

unsigned int VoxelGrid::AddTextureCoordinatesToMesh(float u, float v)
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

#ifdef VOXEL_NEIGHBOURHOOD
	glGenBuffers(1, &mVertexFloor1StrBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor1StrBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor1Str.size(), &m_vec_Floor1Str[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexFloor2StrBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor2StrBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor2Str.size(), &m_vec_Floor2Str[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexFloor1RedBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor1RedBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor1Red.size(), &m_vec_Floor1Red[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexFloor2RedBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor2RedBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor2Red.size(), &m_vec_Floor2Red[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexFloor1GreenBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor1GreenBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor1Green.size(), &m_vec_Floor1Green[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexFloor2GreenBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor2GreenBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor2Green.size(), &m_vec_Floor2Green[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexFloor1BlueBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor1BlueBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor1Blue.size(), &m_vec_Floor1Blue[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexFloor2BlueBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexFloor2BlueBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vec_Floor2Blue.size(), &m_vec_Floor2Blue[0], GL_STATIC_DRAW);
#endif
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

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);
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
				if (GetActive(x, y, z) == false)
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
					if (doZPositive && ((z == VOXEL_GRID_SIZE - 1) || z < VOXEL_GRID_SIZE - 1 && GetActive(x, y, z + 1) == false))
						{
						bool addSide = true;

						if ((z == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);
							if (pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, y, 0) == false);
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
					if(doZNegative && ((z == 0) || (z > 0 && GetActive(x, y, z - 1) == false)))
						{
						bool addSide = true;

						if((z == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, y, VOXEL_GRID_SIZE - 1) == false);
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
					if(doXPositive && ((x == VOXEL_GRID_SIZE - 1) || (x < VOXEL_GRID_SIZE - 1 && GetActive(x + 1, y, z) == false)))
						{
						bool addSide = true;

						if ((x == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(0, y, z) == false);
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
					if(doXNegative && ((x == 0) || (x > 0 && GetActive(x - 1, y, z) == false)))
						{
						bool addSide = true;

						if((x == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(VOXEL_GRID_SIZE - 1, y, z) == false);
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
					if(doYPositive && ((y == VOXEL_GRID_SIZE - 1) || (y < VOXEL_GRID_SIZE - 1 && GetActive(x, y + 1, z) == false)))
						{
						bool addSide = true;

						if((y == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, 0, z) == false);
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
					if(doYNegative && ((y == 0) || (y > 0 && GetActive(x, y - 1, z) == false)))
						{
						bool addSide = true;

						if((y == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, VOXEL_GRID_SIZE - 1, z) == false);
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
    if(mVertexColorBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexColorBuffer);
        mVertexColorBuffer = 0;
		}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for(int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for(int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				if(GetActive(x, y, z) == false)
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

					BiVector f_1((x * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE);
					BiVector f_2((x * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE);
					BiVector f_3((x * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE);
					BiVector f_4((x * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE);
					BiVector f_5((x * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE);
					BiVector f_6((x * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE);
					BiVector f_7((x * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE);
					BiVector f_8((x * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (y * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE, (z * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE);

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

std::string VoxelGrid::HashMeshColourCube(bool f_MeshOnly)
{
	CubeHASH_originstring* f_HashPad = new CubeHASH_originstring();

	float* r = new float(0.0f);
	float* g = new float(0.0f);
	float* b = new float(0.0f);
	float* a = new float(0.0f);

	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for(int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for(int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				bool f_Active = GetActive(x, y, z);
				
				f_HashPad->acPushBool(f_Active);

				if(f_Active && !f_MeshOnly)
					{
					GetColour(x, y, z, r, g, b, a);

					f_HashPad->acPushFloat(*(r));
					f_HashPad->acPushFloat(*(g));
					f_HashPad->acPushFloat(*(b));
					f_HashPad->acPushFloat(*(a));
					}
				}
			}
		}

	g_hasha.init(); //reset hasher state
	g_hasha.process(f_HashPad->m_str_Input.begin(), f_HashPad->m_str_Input.end());
	g_hasha.finish();
	picosha2::get_hash_hex_string(g_hasha, f_HashPad->m_OutputHash);

	printf("MeshHash-%s\n", f_HashPad->m_OutputHash.c_str());

	m_Hash = f_HashPad->m_OutputHash;
	m_HashMeshOnly = f_MeshOnly;

	return f_HashPad->m_OutputHash;
}

void VoxelGrid::CreateMeshCube(float f_Scale)
{
	if(m_isParent == false)
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
		}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	std::string f_HashStr = HashMeshColourCube(true);

	int f_ParentGridID = g_VoxelGridManager->acSearch_WithHash(f_HashStr, true);

	if((f_ParentGridID >= 0) && (f_ParentGridID != m_ManagerIndex))
		{
		std::shared_ptr<VoxelGrid> f_VoxParent = g_VoxelGridManager->m_VoxelGridsVector[f_ParentGridID];

		f_VoxParent->m_isParent = true;

		m_Parent = f_VoxParent;

		f_VoxParent->m_Child.push_back(m_Self);

		m_isParent = false;
		}
	else
		{
		m_isParent = true;

		for(int x = 0; x < VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VOXEL_GRID_SIZE; z++)
					{
					if(GetActive(x, y, z) == false)
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

						BiVector f_1((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
						BiVector f_2((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
						BiVector f_3((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
						BiVector f_4((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
						BiVector f_5((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
						BiVector f_6((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
						BiVector f_7((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
						BiVector f_8((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));

						n1.m_X = -1.0f;
						n1.m_Y = 0.0f;
						n1.m_Z = 0.0f;

						v1 = AddVertexToMesh(f_1, n1, r, g, b, a);
						v2 = AddVertexToMesh(f_2, n1, r, g, b, a);
						v3 = AddVertexToMesh(f_3, n1, r, g, b, a);
						v4 = AddVertexToMesh(f_4, n1, r, g, b, a);

						t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

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
						t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

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
						t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

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
						t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

						AddTriangleToMesh(v3, v7, v8);
						AddTriangleToMesh(v3, v8, v4);

						n1.m_X = 0.0f;
						n1.m_Y = 0.0f;
						n1.m_Z = 1.0f;

						v1 = AddVertexToMesh(f_1, n1, r, g, b, a);
						v3 = AddVertexToMesh(f_3, n1, r, g, b, a);
						v5 = AddVertexToMesh(f_5, n1, r, g, b, a);
						v7 = AddVertexToMesh(f_7, n1, r, g, b, a);

						t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

						AddTriangleToMesh(v1, v5, v7);
						AddTriangleToMesh(v1, v7, v3);

						n1.m_X = 0.0f;
						n1.m_Y = 0.0f;
						n1.m_Z = -1.0f;

						v2 = AddVertexToMesh(f_2, n1, r, g, b, a);
						v4 = AddVertexToMesh(f_4, n1, r, g, b, a);
						v6 = AddVertexToMesh(f_6, n1, r, g, b, a);
						v8 = AddVertexToMesh(f_8, n1, r, g, b, a);

						t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
						t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

						AddTriangleToMesh(v2, v4, v8);
						AddTriangleToMesh(v2, v8, v6);
						}
					}
				}
			}
		}
}

void VoxelGrid::CreateMeshCubeDetail(float f_Scale)
{
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	// parent
	if(m_isParent == true)
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
		}

	if(m_build_count == 0)
		{
		std::string f_HashStr = HashMeshColourCube(true);

		int f_ParentGridID = g_VoxelGridManager->acSearch_WithHash(f_HashStr, true);

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
	if((m_isParent == false) || (m_full == true) || (m_surroundedVoxelGrid == true))
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
				if(GetActive(x, y, z) == false)
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

					/*BiVector p1((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector p2((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector p3((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector p4((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector p5((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector p6((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector p7((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector p8((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));*/

					/*BiVector f_1((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_2((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_3((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_4((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_5((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_6((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_7((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_8((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));*/

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
					if(doZPositive && ((z == VOXEL_GRID_SIZE - 1) || z < VOXEL_GRID_SIZE - 1 && GetActive(x, y, z + 1) == false))
						{
						bool addSide = true;

						if ((z == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);
							if (pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, y, 0) == false);
								}
							}

						if (addSide)
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

#if 1
#define CURRENT_WINDING 1
#endif

#if 1
#define ORIGINAL_WINDING 1
#endif

#if 1
#define TOP_WINDING 1
#endif

#ifndef CURRENT_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#ifndef TOP_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v2, v3, v4);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v2);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v2, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
#endif
#endif
#endif
#endif
#endif
							}
						}

						// Back
					if(doZNegative && ((z == 0) || (z > 0 && GetActive(x, y, z - 1) == false)))
						{
						bool addSide = true;

						if((z == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, y, VOXEL_GRID_SIZE - 1) == false);
								}
							}

						if (addSide)
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

#ifndef CURRENT_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#ifndef TOP_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v2, v3, v4);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v2);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v2, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
#endif
#endif
#endif
#endif
#endif
							}
						}

						// Right
					if(doXPositive && ((x == VOXEL_GRID_SIZE - 1) || (x < VOXEL_GRID_SIZE - 1 && GetActive(x + 1, y, z) == false)))
						{
						bool addSide = true;

						if ((x == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(0, y, z) == false);
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

#ifndef CURRENT_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#ifndef TOP_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v2, v3, v4);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v2);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v2, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
#endif
#endif
#endif
#endif
#endif
							}
						}

						// Left
					if(doXNegative && ((x == 0) || (x > 0 && GetActive(x - 1, y, z) == false)))
						{
						bool addSide = true;

						if((x == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(VOXEL_GRID_SIZE - 1, y, z) == false);
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

#ifndef CURRENT_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#ifndef TOP_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v2, v3, v4);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v2);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v2, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
#endif
#endif
#endif
#endif
#endif
							}
						}

						// Top
					if(doYPositive && ((y == VOXEL_GRID_SIZE - 1) || (y < VOXEL_GRID_SIZE - 1 && GetActive(x, y + 1, z) == false)))
						{
						bool addSide = true;

						if((y == VOXEL_GRID_SIZE - 1))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, 0, z) == false);
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

#ifndef CURRENT_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#ifndef TOP_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v2, v3, v4);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v2);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v2, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
#endif
#endif
#endif
#endif
#endif
							}
						}

						// Bottom
					if(doYNegative && ((y == 0) || (y > 0 && GetActive(x, y - 1, z) == false)))
						{
						bool addSide = true;

						if((y == 0))
							{
							std::shared_ptr<VoxelGrid> pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
							if(pVoxelGrid == NULL || pVoxelGrid->IsSetup())
								{
								addSide = pVoxelGrid != NULL && (pVoxelGrid->GetActive(x, VOXEL_GRID_SIZE - 1, z) == false);
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

#ifndef CURRENT_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#ifndef TOP_WINDING
#ifdef ORIGINAL_WINDING
							AddTriangleToMesh(v1, v2, v3);
							AddTriangleToMesh(v1, v3, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v3);
#endif
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v2, v3, v4);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v4, v2);
#else
#if 0
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v1, v2, v4);
#else
							AddTriangleToMesh(v1, v3, v2);
							AddTriangleToMesh(v3, v1, v4);
#endif
#endif
#endif
#endif
#endif
							}
						}
					}
				}
			}
		}

	// Delete the merged array
	delete(l_merged);
}

void VoxelGrid::CreateMeshCubeNeighbourhood(float f_Scale)
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

	if(mVertexFloor1StrBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor1StrBuffer);
		mVertexFloor1StrBuffer = 0;
		}

	if(mVertexFloor2StrBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor2StrBuffer);
		mVertexFloor2StrBuffer = 0;
		}

	if(mVertexFloor1RedBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor1RedBuffer);
		mVertexFloor1RedBuffer = 0;
		}

	if(mVertexFloor2RedBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor2RedBuffer);
		mVertexFloor2RedBuffer = 0;
		}

	if(mVertexFloor1GreenBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor1GreenBuffer);
		mVertexFloor1GreenBuffer = 0;
		}

	if(mVertexFloor2GreenBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor2GreenBuffer);
		mVertexFloor2GreenBuffer = 0;
		}

	if(mVertexFloor1BlueBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor1BlueBuffer);
		mVertexFloor1BlueBuffer = 0;
		}

	if(mVertexFloor2BlueBuffer != 0)
		{
        glDeleteBuffers(1, &mVertexFloor2BlueBuffer);
		mVertexFloor2BlueBuffer = 0;
		}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for(int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for(int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				if(GetActive(x, y, z) == false)
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

					BiVector f_1((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_2((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_3((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_4((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_5((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_6((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_7((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) - (BLOCK_RENDER_SIZE * f_Scale));
					BiVector f_8((x * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (y * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale), (z * ((BLOCK_RENDER_SIZE * f_Scale) * 2.0f)) + (BLOCK_RENDER_SIZE * f_Scale));

					n1.m_X = 1.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = -1.0f;

					v1 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y - 1, z - 1, f_1, n1, r, g, b, a);
					v2 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y - 1, z, f_2, n1, r, g, b, a);
					v3 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y, z - 1, f_3, n1, r, g, b, a);
					v4 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y, z, f_4, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v1, v3, v2);
					AddTriangleToMesh(v2, v3, v4);

					n1.m_X = 1.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = -1.0f;

					v5 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y - 1, z - 1, f_5, n1, r, g, b, a);
					v6 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y - 1, z, f_6, n1, r, g, b, a);
					v7 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y, z - 1, f_7, n1, r, g, b, a);
					v8 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 1, y, z, f_8, n1, r, g, b, a);
					
					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v5, v6, v7);
					AddTriangleToMesh(v6, v8, v7);

					n1.m_X = 0.0f;
					n1.m_Y = -1.0f;
					n1.m_Z = 0.0f;

					v1 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 2, f_1, n1, r, g, b, a);
					v2 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 1, f_2, n1, r, g, b, a);
					v3 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 2, f_3, n1, r, g, b, a);
					v4 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 1, f_4, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					n1.m_X = 0.0f;
					n1.m_Y = 1.0f;
					n1.m_Z = 0.0f;

					v5 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 2, f_5, n1, r, g, b, a);
					v6 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 1, f_6, n1, r, g, b, a);
					v7 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 2, f_7, n1, r, g, b, a);
					v8 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 1, f_8, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v1, v2, v6);
					AddTriangleToMesh(v1, v6, v5);

					AddTriangleToMesh(v3, v7, v8);
					AddTriangleToMesh(v3, v8, v4);

					n1.m_X = 0.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = -1.0f;

					v1 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 2, f_1, n1, r, g, b, a);
					v2 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 1, f_2, n1, r, g, b, a);
					v3 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 2, f_3, n1, r, g, b, a);
					v4 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 1, f_4, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					n1.m_X = 0.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = 1.0f;

					v5 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 2, f_5, n1, r, g, b, a);
					v6 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 2, z - 1, f_6, n1, r, g, b, a);
					v7 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 2, f_7, n1, r, g, b, a);
					v8 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(m_Self, x - 2, y - 1, z - 1, f_8, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v1, v5, v7);
					AddTriangleToMesh(v1, v7, v3);

					AddTriangleToMesh(v2, v4, v8);
					AddTriangleToMesh(v2, v8, v6);
					}
				}
			}
		}
}

void VoxelGrid::CompleteMeshColour(void)
{
	GenerateBuffersColour();

	m_isRebuildingMesh = false;
}

void VoxelGrid::CompleteMesh(void)
{
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

	m_rebuild = 0;
	m_build_count++;
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
	if (pVoxelGridXMinus != NULL && pVoxelGridXMinus->m_XAdd_full &&
	    pVoxelGridXPlus != NULL && pVoxelGridXPlus->m_XSub_full &&
	    pVoxelGridYMinus != NULL && pVoxelGridYMinus->m_YAdd_full &&
	    pVoxelGridYPlus != NULL && pVoxelGridYPlus->m_YSub_full &&
	    pVoxelGridZMinus != NULL && pVoxelGridZMinus->m_ZAdd_full &&
	    pVoxelGridZPlus != NULL && pVoxelGridZPlus->m_ZSub_full)
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

void VoxelGrid::UpdateMergedSide(int *merged, int blockx, int blocky, int blockz, int width, int height, BiVector *p1, BiVector *p2, BiVector *p3, BiVector *p4, int startX, int startY, int maxX, int maxY, bool positive, bool zFace, bool xFace, bool yFace)
{
	bool doMore = true;
	unsigned int incrementX = 0;
	unsigned int incrementZ = 0;
	unsigned int incrementY = 0;

	int change = 1;
	if (positive == false)
	{
		//change = -1;
	}

	if (zFace || yFace)
	{
		incrementX = 1;
		incrementY = 1;
	}
	if (xFace)
	{
		incrementZ = 1;
		incrementY = 1;
	}

	// 1st phase
	int incrementer = 1;
	while (doMore)
	{
		if (startX + incrementer >= maxX)
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
				if ((xFace && positive && blockx + incrementX + 1 == VOXEL_GRID_SIZE) ||
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

				if (doPhase1Merge)
				{
					if (zFace || yFace)
					{
						(*p2).m_X += change * ((BLOCK_RENDER_SIZE * 2.0f));
						(*p3).m_X += change * ((BLOCK_RENDER_SIZE * 2.0f));
					}
					if (xFace)
					{
						(*p2).m_Z += change * ((BLOCK_RENDER_SIZE * 2.0f));
						(*p3).m_Z += change * ((BLOCK_RENDER_SIZE * 2.0f));
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

		if (zFace || yFace)
		{
			incrementX += change;
		}
		if (xFace)
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
	while (doMore)
	{
		if (startY + incrementer >= maxY)
		{
			doMore = false;
		}
		else
		{
			for (int i = 0; i < loop - 1; i++)
			{
				// Don't do any phase 2 merging is we have any inactive blocks or already merged blocks on the row
				if (zFace)
				{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					GetColour(blockx + i, blocky + incrementY, blockz, &r2, &g2, &b2, &a2);

					if (positive && (blockz + 1) < VOXEL_GRID_SIZE && GetActive(blockx + i, blocky + incrementY, blockz + 1) == true)
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
					}
					*/
					else if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
					{
						// Failed colour check
						doMore = false;
					}
				}
				if (xFace)
				{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					GetColour(blockx, blocky + incrementY, blockz + i, &r2, &g2, &b2, &a2);

					if (positive && (blockx + 1) < VOXEL_GRID_SIZE && GetActive(blockx + 1, blocky + incrementY, blockz + i) == true)
					{
						doMore = false;
					}
					else if (!positive && (blockx) > 0 && GetActive(blockx - 1, blocky + incrementY, blockz + i) == true)
					{
						doMore = false;
					}
					else if (GetActive(blockx, blocky + incrementY, blockz + i) == false || (positive ? (IsMergedXPositive(merged, blockx, blocky + incrementY, blockz + i, width, height) == true) : (IsMergedXNegative(merged, blockx, blocky + incrementY, blockz + i, width, height) == true)))
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
				if (yFace)
				{
					float r1, r2, g1, g2, b1, b2, a1, a2;
					GetColour(blockx, blocky, blockz, &r1, &g1, &b1, &a1);
					GetColour(blockx + i, blocky, blockz + incrementY, &r2, &g2, &b2, &a2);

					if (positive && (blocky + 1) < VOXEL_GRID_SIZE && GetActive(blockx + i, blocky + 1, blockz + incrementY) == true)
					{
						doMore = false;
					}
					else if (!positive && blocky > 0 && GetActive(blockx + i, blocky - 1, blockz + incrementY) == true)
					{
						doMore = false;
					}
					else if (GetActive(blockx + i, blocky, blockz + incrementY) == false || (positive ? (IsMergedYPositive(merged, blockx + i, blocky, blockz + incrementY, width, height) == true) : (IsMergedYNegative(merged, blockx + i, blocky, blockz + incrementY, width, height) == true)))
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
					else if ((r1 != r2 || g1 != g2 || b1 != b2 || a1 != a2) /*&& allMerge == false*/)
					{
						// Failed colour check
						doMore = false;
					}
				}
			}

			if (doMore == true)
			{
				if (zFace || xFace)
				{
					(*p3).m_Y += change * ((BLOCK_RENDER_SIZE * 2.0f));
					(*p4).m_Y += change * ((BLOCK_RENDER_SIZE * 2.0f));
				}
				if (yFace)
				{
					(*p3).m_Z += change * ((BLOCK_RENDER_SIZE * 2.0f));
					(*p4).m_Z += change * ((BLOCK_RENDER_SIZE * 2.0f));
				}

				for (int i = 0; i < loop - 1; i++)
				{
					if (positive)
					{
						if (zFace)
						{
							merged[(blockx + i) + (blocky + incrementY)*width + blockz*width*height] |= MergedSide_Z_Positive;
						}
						if (xFace)
						{
							merged[blockx + (blocky + incrementY)*width + (blockz + i)*width*height] |= MergedSide_X_Positive;
						}
						if (yFace)
						{
							merged[(blockx + i) + blocky*width + (blockz + incrementY)*width*height] |= MergedSide_Y_Positive;
						}
					}
					else
					{
						if (zFace)
						{
							merged[(blockx + i) + (blocky + incrementY)*width + blockz*width*height] |= MergedSide_Z_Negative;
						}
						if (xFace)
						{
							merged[blockx + (blocky + incrementY)*width + (blockz + i)*width*height] |= MergedSide_X_Negative;
						}
						if (yFace)
						{
							merged[(blockx + i) + blocky*width + (blockz + incrementY)*width*height] |= MergedSide_Y_Negative;
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

#if 0
	m_vec_Floor1Str.clear();
	m_vec_Floor2Str.clear();
	m_vec_Floor1Red.clear();
	m_vec_Floor2Red.clear();
	m_vec_Floor1Green.clear();
	m_vec_Floor2Green.clear();
	m_vec_Floor1Blue.clear();
	m_vec_Floor2Blue.clear();
#endif

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
				pVoxelGridXMinus->SetNeedsRebuild(true, false);
			if(pVoxelGridXPlus != NULL && pVoxelGridXPlus->IsSetup() == true)
				pVoxelGridXPlus->SetNeedsRebuild(true, false);
			if(pVoxelGridYMinus != NULL && pVoxelGridYMinus->IsSetup() == true)
				pVoxelGridYMinus->SetNeedsRebuild(true, false);
			if(pVoxelGridYPlus != NULL && pVoxelGridYPlus->IsSetup() == true)
				pVoxelGridYPlus->SetNeedsRebuild(true, false);
			if(pVoxelGridZMinus != NULL && pVoxelGridZMinus->IsSetup() == true)
				pVoxelGridZMinus->SetNeedsRebuild(true, false);
			if(pVoxelGridZPlus != NULL && pVoxelGridZPlus->IsSetup() == true)
				pVoxelGridZPlus->SetNeedsRebuild(true, false);

			m_rebuildNeighours = false;
			}
		}

#ifdef VOXEL_NEIGHBOURHOOD
	CreateMeshCubeNeighbourhood(f_Scale);
#else
	CreateMeshCubeDetail(f_Scale);
#endif

	m_numRebuilds++;
}

void VoxelGrid::RebuildMeshColour(void)
{
	m_isRebuildingMesh = true;

	m_vec_Vertex.clear();
	m_vec_Normal.clear();
	m_vec_Color.clear();
	m_vec_Tex.clear();
	m_vec_Index.clear();

#if 0
	m_vec_Floor1Str.clear();
	m_vec_Floor2Str.clear();
	m_vec_Floor1Red.clear();
	m_vec_Floor2Red.clear();
	m_vec_Floor1Green.clear();
	m_vec_Floor2Green.clear();
	m_vec_Floor1Blue.clear();
	m_vec_Floor2Blue.clear();
#endif

	CreateMeshCubeColour();

	m_numRebuilds++;
	m_rebuild = 1;
}

void VoxelGrid::SetNeedsRebuild(bool rebuild, bool rebuildNeighours)
{
	if(rebuild == true)
		{
		m_rebuild = 1;
		m_rebuildNeighours = rebuildNeighours;
		}
}

VoxelGridManager::VoxelGridManager()
{
#ifdef VOXEL_NEIGHBOURHOOD
    const std::string vs = STRING
		(
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec3 uPos;
        attribute vec3 aPosition;
		attribute vec3 aNormal;
        attribute vec4 aColor;
		attribute vec2 aUV;
		attribute vec4 aFloor1Str;
		attribute vec4 aFloor2Str;
		attribute vec4 aFloor1Red;
		attribute vec4 aFloor2Red;
		attribute vec4 aFloor1Green;
		attribute vec4 aFloor2Green;
		attribute vec4 aFloor1Blue;
		attribute vec4 aFloor2Blue;
		varying vec3 vPosition;
		varying vec3 vNormal;
        varying vec4 vColor;
		varying vec2 vUV;
		varying vec4 vOcclusion;
		varying vec4 vTransport;
        void main()
			{
			vec4 f_Position = vec4(aPosition, 1.0);
			f_Position.xyz += uPos;
			vPosition = f_Position.xyz;
			vec4 f_Normal = vec4(aNormal, 1.0);
			f_Position = uProjMatrix * uViewMatrix * uModelMatrix * f_Position;
			f_Normal = uModelMatrix * f_Normal;
			vNormal = normalize(f_Normal.xyz);
			vColor = aColor;
			vUV = aUV;
			gl_Position = f_Position;

			vOcclusion = vec4(0, 0, 0, 0);
			vTransport = vec4(0, 0, 0, 0);
			vec4 f_Dirt = vec4(0.0158, 0.0158, 0.0158, 0.0158);

			float count = 0.0;

			if(aFloor1Str.x > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor1Red.x &&
					vColor.g != aFloor1Green.x &&
					vColor.b != aFloor1Blue.x)
					{
					vTransport.r += aFloor1Red.x;
					vTransport.g += aFloor1Green.x;
					vTransport.b += aFloor1Blue.x;
					}

				count += 1.0;
				}

			if(aFloor1Str.y > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor1Red.y &&
					vColor.g != aFloor1Green.y &&
					vColor.b != aFloor1Blue.y)
					{
					vTransport.r += aFloor1Red.y;
					vTransport.g += aFloor1Green.y;
					vTransport.b += aFloor1Blue.y;
					}

				count += 1.0;
				}

			if(aFloor1Str.z > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor1Red.z &&
					vColor.g != aFloor1Green.z &&
					vColor.b != aFloor1Blue.z)
					{
					vTransport.r += aFloor2Red.z;
					vTransport.g += aFloor2Green.z;
					vTransport.b += aFloor2Blue.z;
					}

				count += 1.0;
				}

			if(aFloor1Str.w > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor1Red.w &&
					vColor.g != aFloor1Green.w &&
					vColor.b != aFloor1Blue.w)
					{
					vTransport.r += aFloor1Red.w;
					vTransport.g += aFloor1Green.w;
					vTransport.b += aFloor1Blue.w;
					}

				count += 1.0;
				}

			if(aFloor2Str.x > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor2Red.x &&
					vColor.g != aFloor2Green.x &&
					vColor.b != aFloor2Blue.x)
					{
					vTransport.r += aFloor2Red.x;
					vTransport.g += aFloor2Green.x;
					vTransport.b += aFloor2Blue.x;
					}

				count += 1.0;
				}

			if(aFloor2Str.y > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor2Red.y &&
					vColor.g != aFloor2Green.y &&
					vColor.b != aFloor2Blue.y)
					{
					vTransport.r += aFloor2Red.y;
					vTransport.g += aFloor2Green.y;
					vTransport.b += aFloor2Blue.y;
					}

				count += 1.0;
				}

			if(aFloor2Str.z > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor2Red.z &&
					vColor.g != aFloor2Green.z &&
					vColor.b != aFloor2Blue.z)
					{
					vTransport.r += aFloor2Red.z;
					vTransport.g += aFloor2Green.z;
					vTransport.b += aFloor2Blue.z;
					}

				count += 1.0;
				}

			if(aFloor1Str.w > 0.0)
				{
				vOcclusion += f_Dirt;

				if(vColor.r != aFloor2Red.w &&
					vColor.g != aFloor2Green.w &&
					vColor.b != aFloor2Blue.w)
					{
					vTransport.r += aFloor2Red.w;
					vTransport.g += aFloor2Green.w;
					vTransport.b += aFloor2Blue.w;
					}

				count += 1.0;
				}

			vTransport /= 2.0;
			}
		);

#else
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
		varying vec3 camPos;
		varying vec3 vNormal;
        varying vec4 vColor;
		varying vec2 vUV;

        void main()
			{
			vec4 f_AttrPosition = vec4(aPosition, 1.0);
			vec4 f_Normal = vec4(aNormal, 1.0);

			//vec4 f_WorldObjectAttrPosition = uProjMatrix * uViewMatrix * uModelMatrix * f_AttrPosition;

			vec4 f_ModelAttrPosition = uModelMatrix * f_AttrPosition;

			//f_Normal = uProjMatrix * uViewMatrix * uModelMatrix * f_Normal;

			f_Normal = uModelMatrix * f_Normal; //\/wk


			// interim translation
			f_ModelAttrPosition.xyz += uPos;
			
			//vec4 f_absPosition = vec4(f_ModelAttrPosition.xyz, 1.0);
			vec3 f_absPosition = f_ModelAttrPosition.xyz;

			//f_absPosition.z *= -1.0;
			//f_absPosition.y *= -1.0;

			vec3 f_CameraFac = uCam;

			f_CameraFac.y *= -1.0;

			f_ModelAttrPosition.xyz -= f_CameraFac;

			vec4 f_MVP_AttrPosition = uProjMatrix * uViewMatrix * f_ModelAttrPosition;

			//f_absPosition = uProjMatrix * uViewMatrix * f_absPosition;

			absPosition = f_absPosition;

			//absPosition = f_MVP_AttrPosition.xyz;

			//f_Normal = uProjMatrix * uViewMatrix * f_Normal; //wk off

			//absPosition = f_ModelAttrPosition.xyz;


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

		uniform sampler2D uTexture;

		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
		uniform float uLightNom;
		uniform float uSeed;

		varying vec3 absPosition;
		varying vec3 camPos;
		varying vec3 vNormal;
		varying vec4 vColor;
		varying vec2 vUV;

        void main()
			{
			//initially seed the psuedo random generator with absolute position
			seed(vec3(uSeed * absPosition.x, uSeed * absPosition.y, uSeed * absPosition.z));

			vec3 f_vNormal = normalize(vNormal); //opt on

			vec4 f_AmbientColor = vColor; //texture2D(uTexture, vTexCoord);

			// call for fragment
			float f_qsX = rand();
			float f_qsY = rand();
			float f_qsZ = rand();

			// sun effect
			vec3 f_SunLightPos = vec3(-0.3, 1.0, 0.7);
			vec4 f_SunLightColor = vec4(0.92, 0.87, 0.79, 1.0);

			vec4 randElement = vec4(f_qsX * f_SunLightColor.x, f_qsY * f_SunLightColor.y, f_qsZ * f_SunLightColor.z, 1.0);

			f_SunLightColor = (f_SunLightColor * 0.8) + (randElement * 0.2); //wk

			vec3 f_L = normalize(f_SunLightPos);

			vec4 sunIdiff = vec4(f_SunLightColor.rgb * max(dot(f_vNormal, f_L), 0.0), 1.0);

			sunIdiff = clamp(sunIdiff, 0.0, 1.0);

			sunIdiff *= 0.07; // *= 0.03

			vec4 f_AccumulationBuffer = sunIdiff * 5.35;

			//vec4 f_AccumulationBuffer = (Idiff * f_SunRadius) * (1.0 - (f_SunDistanceL / 1525.0)); //750 //650 //800? //655.3

			// Lights Loop
			int f_LightNom = int(uLightNom);

			float f_ProcCount = 0.0;
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

						/*if(f_constant_dist < 1450.0)
							{
							vec4 f_CalcVec = (Idiffl * (f_LightRadius / 40.0)) * (1.0 - (f_constant_dist / 1450.0)); // 750.0 // 654.0 // 850.0 // 55.0

							f_AccumulationBuffer += f_CalcVec;
							
							f_ProcCount += 1.0;
							}*/

						vec4 f_CalcVec = clamp((Idiffl * (f_LightRadius / 40.0)), 0.0, 1.0) * (1.0 - clamp((f_constant_dist / 1450.0), 0.0, 1.0)); // 750.0 // 654.0 // 850.0 // 55.0

						f_AccumulationBuffer += f_CalcVec;

						f_ProcCount += 1.0;
						}						//(7%) OF (0.0 -> 1.0)
					}
				}

			// add sun
			f_ProcCount += 1.0;

			// compile resultance accumulation
			vec4 f_Result = f_AccumulationBuffer / f_ProcCount;

			// [zero] blend
			f_Result.a = 1.0;

			// set pixel color
			gl_FragColor = f_AmbientColor * f_Result;
			}
		);
#endif

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

#if 0
	mFloor1StrAttribLocation = glGetAttribLocation(mProgram, "aFloor1Str");
	mFloor2StrAttribLocation = glGetAttribLocation(mProgram, "aFloor2Str");
	mFloor1RedAttribLocation = glGetAttribLocation(mProgram, "aFloor1Red");
	mFloor2RedAttribLocation = glGetAttribLocation(mProgram, "aFloor2Red");
	mFloor1GreenAttribLocation = glGetAttribLocation(mProgram, "aFloor1Green");
	mFloor2GreenAttribLocation = glGetAttribLocation(mProgram, "aFloor2Green");
	mFloor1BlueAttribLocation = glGetAttribLocation(mProgram, "aFloor1Blue");
	mFloor2BlueAttribLocation = glGetAttribLocation(mProgram, "aFloor2Blue");
#endif
}

VoxelGridManager::~VoxelGridManager()
{
    if(mProgram != 0)
		{
        glDeleteProgram(mProgram);

        mProgram = 0;
		}
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
	//Temp
	float VOX_SIZE VOX_GRID_SIZE;

	acSet_Extents((VOX_SIZE * (VOXEL_RENDER_SIZE * 2.0f)) * WAR_ZONE_EXTENTS_RADIUS);

	int f_SmallCount = 2 + (Cube::randomFac() % WAR_ZONE_SMALL_MAX);
	int f_MediumCount = 1 + (Cube::randomFac() % WAR_ZONE_MEDIUM_MAX);
	int f_LargeCount = 1 + (Cube::randomFac() % WAR_ZONE_LARGE_MAX);

	int f_LampCount = 5 + (Cube::randomFac() % WAR_ZONE_LAMP_MAX);

       ///////////////
	  ///////////////
	 // ONE ////////
	//
	for(int f_Zfact = 0; f_Zfact < f_SmallCount; f_Zfact++)
		{
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5) * 2) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 15.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5) * 2) * m_AxisExtent);

		f_Building->m_Width = (Cube::randomFac() % 9) + (Cube::randomFac() % 8);
		f_Building->m_Length = (Cube::randomFac() % 9) + (Cube::randomFac() % 8);
		f_Building->m_Height = 6.0f + (4.0f * Cube::random());

		m_vec_Building.push_back(f_Building);
		}

	   ///////////////
	  ///////////////
	 // TWO ////////
	//
	for(int f_Zfact = 0; f_Zfact < f_MediumCount; f_Zfact++)
		{
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5) * 2) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 15.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5) * 2) * m_AxisExtent);

		f_Building->m_Width = (Cube::randomFac() % 18) + (Cube::randomFac() % 10);
		f_Building->m_Length = (Cube::randomFac() % 18) + (Cube::randomFac() % 10);
		f_Building->m_Height = 8.0f + (6.0f * Cube::random());

		m_vec_Building.push_back(f_Building);
		}

	   /////////////////
	  /////////////////
	 // THREE ////////
	//
	for(int f_Zfact = 0; f_Zfact < f_LargeCount; f_Zfact++)
		{
		std::shared_ptr<Building> f_Building = std::make_shared<Building>();

		bool f_Direction = Cube::randomFac() % 2;

		f_Building->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5) * 2) * m_AxisExtent);
		f_Building->m_Pos.m_Y = 15.0f;
		f_Building->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5) * 2) * m_AxisExtent);

		f_Building->m_Width = (Cube::randomFac() % 120) + (Cube::randomFac() % 25);
		f_Building->m_Length = (Cube::randomFac() % 250) + (Cube::randomFac() % 3);
		f_Building->m_Height = (90.0f * Cube::random()) + (25.0f * Cube::random());

		m_vec_Building.push_back(f_Building);
		}

	   /////////////////
	  /////////////////
	 // LIGHT ////////
	//
	for(int f_Zfact = 0; f_Zfact < f_LampCount; f_Zfact++)
		{
		std::shared_ptr<LightStr> f_LightStr = std::make_shared<LightStr>();

		f_LightStr->m_Pos.m_X = m_position.m_X + (((Cube::random() - 0.5) * 2) * m_AxisExtent);
		f_LightStr->m_Pos.m_Y = 15.0f;
		f_LightStr->m_Pos.m_Z = m_position.m_Z + (((Cube::random() - 0.5) * 2) * m_AxisExtent);

		f_LightStr->m_Width = 2;
		f_LightStr->m_Length = 2;
		f_LightStr->m_Height = (35 * Cube::random()) + 10;

		f_LightStr->m_RGBA.alpha = ((Cube::random() * 0.8f) + 0.2f) * 255.0f;
		f_LightStr->m_RGBA.red = ((Cube::random() * 0.8f) + 0.2f) * 255.0f;
		f_LightStr->m_RGBA.green = ((Cube::random() * 0.8f) + 0.2f) * 255.0f;
		f_LightStr->m_RGBA.blue = ((Cube::random() * 0.8f) + 0.2f) * 255.0f;

		f_LightStr->m_Radius = ((Cube::random() * 2300.0f) + 900.0f);

		m_vec_LightStr.push_back(f_LightStr);
		}
}

// Getting VoxelGrid and positional information
void VoxelGridManager::GetGridFromPosition(BiVector position, int* gridX, int* gridY, int* gridZ)
{
	*gridX = (int)((position.m_X + VoxelGrid::BLOCK_RENDER_SIZE) / VoxelGrid::VOXEL_GRID_SIZE);
	*gridY = (int)((position.m_Y + VoxelGrid::BLOCK_RENDER_SIZE) / VoxelGrid::VOXEL_GRID_SIZE);
	*gridZ = (int)((position.m_Z + VoxelGrid::BLOCK_RENDER_SIZE) / VoxelGrid::VOXEL_GRID_SIZE);

	if (position.m_X <= -0.5f)
		*gridX -= 1;
	if (position.m_Y <= -0.5f)
		*gridY -= 1;
	if (position.m_Z <= -0.5f)
		*gridZ -= 1;
}

std::shared_ptr<VoxelGrid> VoxelGridManager::GetVoxelGridFromPosition(float posX, float posY, float posZ)
{
	int gridX = (int)((posX + VoxelGrid::BLOCK_RENDER_SIZE) / VoxelGrid::VOXEL_GRID_SIZE);
	int gridY = (int)((posY + VoxelGrid::BLOCK_RENDER_SIZE) / VoxelGrid::VOXEL_GRID_SIZE);
	int gridZ = (int)((posZ + VoxelGrid::BLOCK_RENDER_SIZE) / VoxelGrid::VOXEL_GRID_SIZE);

	if(posX <= -0.5f)
		gridX -= 1;

	if(posY <= -0.5f)
		gridY -= 1;

	if(posZ <= -0.5f)
		gridZ -= 1;

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

	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
	glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

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

	g_UpdatingMuti.lock();

	int f_i = g_VoxelGridManager->m_VoxelGridsVector.size();

	int f_manageid = 0;

	g_UpdatingMuti.unlock();

	for(int i = 0; i < f_i; i++)
		{
		if(m_VoxelGridsVector[i]->m_isParent == true)
			{
			if(m_VoxelGridsVector[i]->m_emptyVoxelGrid == false)
				{
				if(m_VoxelGridsVector[i]->m_created == true)
					{
					if(m_VoxelGridsVector[i]->m_rebuild < 1)
						{
						std::shared_ptr<VoxelGrid> f_ParentGrid = m_VoxelGridsVector[i];

						bool f_BuffersUpl = false;
						int f_FaceCount = 0;

						BiVector f_Parent_PlayerGridVector(f_Position.m_X - (f_ParentGrid->m_position.m_X + /*VOX_BY2*/0.0f), f_Position.m_Y - (f_ParentGrid->m_position.m_Y + /*VOX_BY2*/0.0f), f_Position.m_Z - (f_ParentGrid->m_position.m_Z + /*VOX_BY2*/0.0f));

						float f_DistP = f_Parent_PlayerGridVector.acLength();

						if(f_DistP < VIEW_DISTANCE)
							{
							glUniform3f(mPosUniformLocation, f_ParentGrid->m_position.m_X, f_ParentGrid->m_position.m_Y, f_ParentGrid->m_position.m_Z);
							glUniform3f(mCamUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);

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

							f_FaceCount = f_ParentGrid->m_vec_Index.size() * 3;

							f_BuffersUpl = true;

#ifdef VOXEL_NEIGHBOURHOOD
							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1StrBuffer);
							glEnableVertexAttribArray(mFloor1StrAttribLocation);
							glVertexAttribPointer(mFloor1StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2StrBuffer);
							glEnableVertexAttribArray(mFloor2StrAttribLocation);
							glVertexAttribPointer(mFloor2StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1RedBuffer);
							glEnableVertexAttribArray(mFloor1RedAttribLocation);
							glVertexAttribPointer(mFloor1RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2RedBuffer);
							glEnableVertexAttribArray(mFloor2RedAttribLocation);
							glVertexAttribPointer(mFloor2RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1GreenBuffer);
							glEnableVertexAttribArray(mFloor1GreenAttribLocation);
							glVertexAttribPointer(mFloor1GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2GreenBuffer);
							glEnableVertexAttribArray(mFloor2GreenAttribLocation);
							glVertexAttribPointer(mFloor2GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1BlueBuffer);
							glEnableVertexAttribArray(mFloor1BlueAttribLocation);
							glVertexAttribPointer(mFloor1BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

							glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2BlueBuffer);
							glEnableVertexAttribArray(mFloor2BlueAttribLocation);
							glVertexAttribPointer(mFloor2BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
#endif

							// parent grid
							if(f_FaceCount > 0)
								{
								glUniform1f(mTimeUniformLocation, Cube::random());

								// GL_TRIANGLES Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
								glDrawElements(GL_TRIANGLES, f_FaceCount, GL_UNSIGNED_SHORT, 0);
								}
							}

						// Playground
						for(int f_XY = 0; f_XY < f_ParentGrid->m_Child.size(); f_XY++)
							{
							std::shared_ptr<VoxelGrid> f_ChildGrid = f_ParentGrid->m_Child[f_XY];
			
							BiVector f_Child_PlayerGridVector(f_Position.m_X - (f_ChildGrid->m_position.m_X + /*VOX_BY2*/0.0f), f_Position.m_Y - (f_ChildGrid->m_position.m_Y + /*VOX_BY2*/0.0f), f_Position.m_Z - (f_ChildGrid->m_position.m_Z + /*VOX_BY2*/0.0f));

							float f_DistC = f_Child_PlayerGridVector.acLength();

							if(f_DistC < VIEW_DISTANCE)
								{
								glUniform3f(mPosUniformLocation, f_ChildGrid->m_position.m_X, f_ChildGrid->m_position.m_Y, f_ChildGrid->m_position.m_Z);
								glUniform3f(mCamUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);

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

									f_FaceCount = f_ParentGrid->m_vec_Index.size() * 3;

									f_BuffersUpl = true;

#ifdef VOXEL_NEIGHBOURHOOD
									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1StrBuffer);
									glEnableVertexAttribArray(mFloor1StrAttribLocation);
									glVertexAttribPointer(mFloor1StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2StrBuffer);
									glEnableVertexAttribArray(mFloor2StrAttribLocation);
									glVertexAttribPointer(mFloor2StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1RedBuffer);
									glEnableVertexAttribArray(mFloor1RedAttribLocation);
									glVertexAttribPointer(mFloor1RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2RedBuffer);
									glEnableVertexAttribArray(mFloor2RedAttribLocation);
									glVertexAttribPointer(mFloor2RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1GreenBuffer);
									glEnableVertexAttribArray(mFloor1GreenAttribLocation);
									glVertexAttribPointer(mFloor1GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2GreenBuffer);
									glEnableVertexAttribArray(mFloor2GreenAttribLocation);
									glVertexAttribPointer(mFloor2GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1BlueBuffer);
									glEnableVertexAttribArray(mFloor1BlueAttribLocation);
									glVertexAttribPointer(mFloor1BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

									glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2BlueBuffer);
									glEnableVertexAttribArray(mFloor2BlueAttribLocation);
									glVertexAttribPointer(mFloor2BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
#endif
									}

								// parent grid
								if(f_ChildGrid->m_created == true)
									{
									if(f_ChildGrid->m_rebuild == 0)
										{
										if(f_FaceCount > 0)
											{
											glUniform1f(mTimeUniformLocation, Cube::random());

											// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
											glDrawElements(GL_TRIANGLES, f_FaceCount, GL_UNSIGNED_SHORT, 0);
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

void VoxelGridManager::DrawGI(BiVector f_Position)
{
#if 1
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
#else
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);
#endif

#if 0
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
#endif

	if(mProgram == 0)
		return;

	glUseProgram(mProgram);

	int f_Size = m_VoxelGridsVector.size();

	for(unsigned int i = 0; i < f_Size; i++)
		{
		if(m_VoxelGridsVector[i]->m_created)
			{
			BiVector f_BiVector(m_VoxelGridsVector[i]->m_position.m_X - f_Position.m_X, m_VoxelGridsVector[i]->m_position.m_Y - f_Position.m_Y, m_VoxelGridsVector[i]->m_position.m_Z - f_Position.m_Z);

			float f_Dist = f_BiVector.acLength();
			if(f_Dist < VIEW_DISTANCE)
				{
				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexPositionBuffer);
				glEnableVertexAttribArray(mPositionAttribLocation);
				glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexNormalBuffer);
				glEnableVertexAttribArray(mNormalAttribLocation);
				glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexColorBuffer);
				glEnableVertexAttribArray(mColorAttribLocation);
				glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexTexCoordBuffer);
				glEnableVertexAttribArray(mTexCoordAttribLocation);
				glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VoxelGridsVector[i]->mIndexBuffer);

				  /////////////////////////////
				 // Neighbourhood Voxels
				//
#ifdef VOXEL_NEIGHBOURHOOD
				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1StrBuffer);
				glEnableVertexAttribArray(mFloor1StrAttribLocation);
				glVertexAttribPointer(mFloor1StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2StrBuffer);
				glEnableVertexAttribArray(mFloor2StrAttribLocation);
				glVertexAttribPointer(mFloor2StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1RedBuffer);
				glEnableVertexAttribArray(mFloor1RedAttribLocation);
				glVertexAttribPointer(mFloor1RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2RedBuffer);
				glEnableVertexAttribArray(mFloor2RedAttribLocation);
				glVertexAttribPointer(mFloor2RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1GreenBuffer);
				glEnableVertexAttribArray(mFloor1GreenAttribLocation);
				glVertexAttribPointer(mFloor1GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2GreenBuffer);
				glEnableVertexAttribArray(mFloor2GreenAttribLocation);
				glVertexAttribPointer(mFloor2GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor1BlueBuffer);
				glEnableVertexAttribArray(mFloor1BlueAttribLocation);
				glVertexAttribPointer(mFloor1BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[i]->mVertexFloor2BlueBuffer);
				glEnableVertexAttribArray(mFloor2BlueAttribLocation);
				glVertexAttribPointer(mFloor2BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
#endif

				MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
				glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

				MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
				glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

				MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
				glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

				glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);

#if 0
				glBindTexture(GL_TEXTURE_2D, f_Bitmap);
				glUniform1i(mTextureUniformLocation, 0);
#endif

				ag_Calc_Light(f_Position);

				glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
				glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
				glUniform1f(mLightNomUniformLocation, g_LightNom);

				// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
				glDrawElements(GL_TRIANGLES, m_VoxelGridsVector[i]->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
				//printf("glDrawElements(%i)\n", m_VoxelGridsVector[i]->m_vec_Index.size());
				}
			else
				{
				//reorder array
				for(int f_c = i; f_c < (m_VoxelGridsVector.size() - 1); f_c++)
					{
					m_VoxelGridsVector[f_c] = m_VoxelGridsVector[f_c + 1];
					}

				m_VoxelGridsVector.pop_back();
				}
			}
		}
}

void VoxelGridManager::DrawCube(void)
{
#if 0
	glDisable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);

	if(mProgram == 0)
		return;

	glUseProgram(mProgram);

	for(unsigned int i = 0; i < 1; i++)
		{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
		glEnableVertexAttribArray(mPositionAttribLocation);
		glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
		glEnableVertexAttribArray(mNormalAttribLocation);
		glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
		glEnableVertexAttribArray(mColorAttribLocation);
		glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
		glEnableVertexAttribArray(mTexCoordAttribLocation);
		glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

		MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

		MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
		glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

#if 0
		glEnable(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, f_Bitmap);
		glUniform1i(mTextureUniformLocation, 0);
#endif

		// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
		glDrawElements(GL_TRIANGLES, (2 * 6) * 3, GL_UNSIGNED_SHORT, 0);
		}
#endif
}

void VoxelGridManager::DrawPoints(void)
{
#if 0
	//float f_X, float f_Y, float f_Z, float f_Red, float f_Green, float f_Blue, float f_Alpha, unsigned int f_Bitmap, float f_Scale
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    
    if(mProgram == 0)
		{
        return;
		}

    glUseProgram(mProgram);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glEnableVertexAttribArray(mPositionAttribLocation);
    glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glEnableVertexAttribArray(mColorAttribLocation);
    glVertexAttribPointer(mColorAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

    MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
    glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

    MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
    glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	//float f_Pos[4];

	//if(g_ZoomFactor == 0 || 1)
	//	{
		//f_Pos[0] = f_X;
		//f_Pos[1] = f_Z + f_Y;
		//f_Pos[2] = 0;
	//	}
	//else
	//	{
	//	f_Pos[0] = f_X - (playerAV[g_Player]->Xform.Translation.x * g_ZoomFactor);
	//	f_Pos[1] = (f_Y + f_Z) - ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Xform.Translation.y)* g_ZoomFactor);
	//	f_Pos[2] = f_Z * (1 - g_ZoomFactor);
	//	}

	//f_Pos[3] = 1.0f;

	//glUniform4fv(mPosUniformLocation, 1, f_Pos);

	//float f_Color[4];

	//f_Color[0] = f_Red;
	//f_Color[1] = f_Green;
	//f_Color[2] = f_Blue;
	//f_Color[3] = f_Alpha;

	//glUniform4fv(mColorUniformLocation, 1, f_Color);
	//glUniform1f(mScaleUniformLocation, f_Scale * 5.0f);

	//glBindTexture(GL_TEXTURE_2D, f_Bitmap);
	//glUniform1i(mTextureUniformLocation, 0);

    // Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, 0);
#endif
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
	m_position = pos;

	m_midpoint = pos;

	m_midpoint += BiVector(VOX_BY2);
}

BiVector VoxelGrid::GetPosition(void)
{
	return m_position;
}

// VoxelGrid Creation
void VoxelGridManager::CreateNewVoxelGrid(int x, int y, int z)
{
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

	float xPos = x * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	float yPos = y * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	float zPos = z * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);

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
						f_Grid->SetNeedsRebuild(true, true);
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

	map<VoxelGridCoordKeys, std::shared_ptr<VoxelGrid>>::iterator it = m_VoxelGridsMap.find(VoxelGridKey);

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
	bool f_Collide = false;
	if(f_Point.m_X >= (f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_X < ((f_x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Y >= (f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Y < ((f_y + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Z >= (f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Z < ((f_z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))
		{
		for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
					{
					if(GetActive(x, y, z))
						{
						if((f_Point.m_X > ((f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((x * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_X < ((f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((x + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y > ((f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((y * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y < ((f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((y + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z > ((f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((z * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z < ((f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((z + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))))
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
	bool f_Collide = false;
	if((f_Point.m_X >= (f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_X < ((f_x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y >= (f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y < ((f_y + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z >= (f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z < ((f_z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))))
		{
		for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
					{
					if(GetActive(x, y, z))
						{
						if((f_Point.m_X >= ((f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((x * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_X < ((f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((x + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y >= ((f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((y * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y < ((f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((y + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z >= ((f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((z * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z < ((f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((z + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))))))
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

bool VoxelGrid::CollideMarchPoint(BiVector f_Front, BiVector f_Rear, int f_x, int f_y, int f_z, BiVector* f_ImpactPoint, BiVector* f_ImpactNormal)
{
	if(m_rebuild > 0)
		{
		return true;
		}

	Cube::BiVector f_DefVec = f_Front - f_Rear;

	float f_DefaultVecLength = f_DefVec.acLength();

	if(f_DefaultVecLength < 3.0f / VOXEL_MARCH_DIV)
		{
		f_DefaultVecLength += 3.0f / VOXEL_MARCH_DIV;
		}
	else if(f_DefaultVecLength > (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)) * 1.0f)
		{
		f_DefaultVecLength = (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)) * 1.0f;
		}

	QpoVec3d MotionVec;

	MotionVec.x = f_DefVec.m_X;
	MotionVec.y = f_DefVec.m_Y;
	MotionVec.z = f_DefVec.m_Z;

	Qpo->Vec3d_Normalize(&MotionVec);

	Cube::BiVector f_Vec1 = f_Rear;

	int f_Xclip = f_Vec1.m_X;
	int f_Yclip = f_Vec1.m_Y;
	int f_Zclip = f_Vec1.m_Z;

	int f_Xpos = m_position.m_X;
	int f_Ypos = m_position.m_Y;
	int f_Zpos = m_position.m_Z;

	bool f_Collide = false;

	while((f_DefaultVecLength > 0.0f) && (f_Collide == false))
		{
		if((f_Vec1.m_X >= ((float)f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_X < (((float)f_x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Y >= ((float)f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Y < (((float)f_y + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Z >= ((float)f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Z < (((float)f_z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))))
			{
			int Xacting = ((f_Xpos - (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE)) - f_Xclip) / 10; // adjust here
			int Yacting = ((f_Ypos - (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE)) - f_Yclip) / 10; // adjust here
			int Zacting = ((f_Zpos - (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE)) - f_Zclip) / 10; // adjust here

			int Xbegin = Xacting - 1; // adjust here
			int Ybegin = Yacting - 1; // adjust here
			int Zbegin = Zacting - 1; // adjust here

			int Xfin = Xacting + 1; // adjust here
			int Yfin = Yacting + 1; // adjust here
			int Zfin = Zacting + 1; // adjust here

			for(int x = Xbegin; x < Xfin; x++)
				{
				for(int y = Ybegin; y < Yfin; y++)
					{
					for(int z = Zbegin; z < Zfin; z++)
						{
						if(GetActive(x, y, z))
							{
							BiVector f_Vec2 = f_Vec1;
							Cube::BiVector f_VecLengthVec2((f_Vec2.m_X + (MotionVec.x * ((BLOCK_RENDER_SIZE) / (VOXEL_MARCH_DIV)))), (f_Vec2.m_Y + (MotionVec.y * ((BLOCK_RENDER_SIZE) / (VOXEL_MARCH_DIV)))), (f_Vec2.m_Z + (MotionVec.z * ((BLOCK_RENDER_SIZE) / (VOXEL_MARCH_DIV)))));
							float f_DefLength = f_DefaultVecLength;

							float fm_Vec2Length = f_VecLengthVec2.acLength();

							if(f_DefLength < 1.0f / VOXEL_MARCH_DIV)
								{
								f_DefLength = 1.0f / VOXEL_MARCH_DIV;
								}

							if((fm_Vec2Length < BLOCK_RENDER_SIZE * 3.7f) || 1)
								{
								while((fm_Vec2Length > 0.0f) && (f_Collide == false))
									{
									if (f_Vec2.m_X >= (((float)f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((float)x * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
										f_Vec2.m_X < (((float)f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((((float)x + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
										f_Vec2.m_Z >= (((float)f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((float)z * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
										f_Vec2.m_Z < (((float)f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((((float)z + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
										f_Vec2.m_Y >= (((float)f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((float)y * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
										f_Vec2.m_Y < (((float)f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((((float)y + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))))
										{
										f_ImpactNormal->m_X = 0.0f;
										f_ImpactNormal->m_Y = 1.0f;
										f_ImpactNormal->m_Z = 0.0f;

										f_Collide = true;
										*(f_ImpactPoint) = f_Vec2;

#if 0
										SetColour(x, y, z, 1.0f, 0.5, 0.8, 1.0f);
#endif

										x = Xfin;
										y = Yfin;
										z = Zfin;
										}

									f_Vec2.m_X += (MotionVec.x * (BLOCK_RENDER_SIZE / VOXEL_MARCH_DIV));
									f_Vec2.m_Y += (MotionVec.y * (BLOCK_RENDER_SIZE / VOXEL_MARCH_DIV));
									f_Vec2.m_Z += (MotionVec.z * (BLOCK_RENDER_SIZE / VOXEL_MARCH_DIV));
									fm_Vec2Length -= BLOCK_RENDER_SIZE / VOXEL_MARCH_DIV;
									f_DefLength -= BLOCK_RENDER_SIZE / VOXEL_MARCH_DIV;

									if(f_DefLength <= 0.0f)
										{
										//f_Vec1 = f_Vec2;
										fm_Vec2Length = 0.0f;
										}
									}
								}
							}
						}
					}
				}
			}

		f_Vec1.m_X += (MotionVec.x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE)));
		f_Vec1.m_Y += (MotionVec.y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE)));
		f_Vec1.m_Z += (MotionVec.z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE)));

		f_DefaultVecLength -= (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE));

		if(f_DefaultVecLength < 0.0f)
			{
			f_Vec1 = f_Front;
			}
		}

	return f_Collide;
}

bool VoxelGrid::CollideCheckPoint(BiVector f_FrontPoint, BiVector f_RearPoint, int f_x, int f_y, int f_z, BiVector* f_ImpactPoint, BiVector* f_ImpactNormal)
{
	if(m_rebuild > 0)
		{
		return true;
		}

	Cube::BiVector f_DefVec = f_FrontPoint - f_RearPoint;

	float f_DefaultVecLength = f_DefVec.acLength();

	if(f_DefaultVecLength < 3.0f / VOXEL_MARCH_DIV)
		{
		f_DefaultVecLength += 3.0f / VOXEL_MARCH_DIV;
		}
	else if(f_DefaultVecLength > (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)) * 1.0f)
		{
		f_DefaultVecLength = (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)) * 1.0f;
		}

	QpoVec3d MotionVec;

	MotionVec.x = f_DefVec.m_X;
	MotionVec.y = f_DefVec.m_Y;
	MotionVec.z = f_DefVec.m_Z;

	Qpo->Vec3d_Normalize(&MotionVec);

	Cube::BiVector f_Vec1 = f_FrontPoint;

	int f_Xclip = f_Vec1.m_X;
	int f_Yclip = f_Vec1.m_Y;
	int f_Zclip = f_Vec1.m_Z;

	int f_Xpos = m_position.m_X;
	int f_Ypos = m_position.m_Y;
	int f_Zpos = m_position.m_Z;

	bool f_Collide = false;

	if((f_Vec1.m_X >= ((float)f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Vec1.m_X < (((float)f_x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Vec1.m_Y >= ((float)f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Vec1.m_Y < (((float)f_y + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Vec1.m_Z >= ((float)f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Vec1.m_Z < (((float)f_z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))))
		{
		int Xacting = ((f_Xpos - (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE)) - f_Xclip) / 10; // adjust here
		int Yacting = ((f_Ypos - (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE)) - f_Yclip) / 10; // adjust here
		int Zacting = ((f_Zpos - (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE)) - f_Zclip) / 10; // adjust here

		int Xbegin = Xacting - 1; // adjust here
		int Ybegin = Yacting - 1; // adjust here
		int Zbegin = Zacting - 1; // adjust here

		int Xfin = Xacting + 1; // adjust here
		int Yfin = Yacting + 1; // adjust here
		int Zfin = Zacting + 1; // adjust here

		for(int x = Xbegin; x < Xfin; x++)
			{
			for(int y = Ybegin; y < Yfin; y++)
				{
				for(int z = Zbegin; z < Zfin; z++)
					{
					if(GetActive(x, y, z))
						{
						if(f_Vec1.m_X >= (((float)f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((float)x * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
							f_Vec1.m_X < (((float)f_x * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((((float)x + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
							f_Vec1.m_Z >= (((float)f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((float)z * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
							f_Vec1.m_Z < (((float)f_z * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((((float)z + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
							f_Vec1.m_Y >= (((float)f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + (((float)y * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))) &&
							f_Vec1.m_Y < (((float)f_y * (VoxelGrid::VOXEL_GRID_SIZE * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f))) + ((((float)y + 1) * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f)))))
							{
							f_ImpactNormal->m_X = 0.0f;
							f_ImpactNormal->m_Y = 1.0f;
							f_ImpactNormal->m_Z = 0.0f;

							f_Collide = true;
							*(f_ImpactPoint) = f_Vec1;

#if 0
							SetColour(x, y, z, 1.0f, 0.5, 0.8, 1.0f);
#endif

							x = Xfin;
							y = Yfin;
							z = Zfin;
							}
						}
					}
				}
			}
		}

	return f_Collide;
}

int VoxelGridManager::acSearch_WithHash(std::string f_Hash, bool f_MeshOnly)
{
	for(int f_Int = 0; f_Int < m_VoxelGridsVector.size(); f_Int++)
		{
		std::shared_ptr<VoxelGrid> f_Grid = m_VoxelGridsVector[f_Int];

		if(f_Grid->m_Hash.compare(f_Hash) == 0)
			{
			if(f_Grid->m_HashMeshOnly == f_MeshOnly)
				{
				return f_Int;
				}
			}
		}

	return -5;
}

bool VoxelGridManager::Make_Gen_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
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
	 //   Build    //
	//............//
	g_VoxelGridManager->Make_Gen_Building(BuildingType_SmallBuilding, f_FloorCenter, vWidth, vLength, vHeight, f_Position, f_VoxelGrid);

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
				if(((vLength - 4) > 1) &&
				   ((vHeight - 2) > 0))
					{
					g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, 3, vLength - 4, vHeight - 2, f_Position, f_VoxelGrid);
					}
				}
			else
				{
				if(((vWidth - 4) > 1) &&
				   ((vHeight - 2) > 0))
					{
					g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
					}
				}
			}break;

		case 3:
			{
			int f_IntFinger = Cube::randomFac() % 4;

			if(f_IntFinger == 0)
				{
				if(vLength > vWidth)
					{
					if(((vWidth - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						float f_IncZ = (((float)vLength / 3.0f) * (float)BLOCK_RENDER) / 2.0f;
						float f_Upper = f_FloorCenter.m_Z + f_IncZ;
						float f_Lower = f_FloorCenter.m_Z - f_IncZ;
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X, f_Upper, f_FloorCenter.m_Z), vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X, f_Lower, f_FloorCenter.m_Z), vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						}
					}
				else
					{
					if(((vLength - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						float f_IncX = (((float)vWidth / 3.0f) * (float)BLOCK_RENDER) / 2.0f;
						float f_Left = f_FloorCenter.m_X + f_IncX;
						float f_Right = f_FloorCenter.m_X - f_IncX;
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Left, f_FloorCenter.m_Y, f_FloorCenter.m_Z), 3, vLength - 4, vHeight - 2, f_Position, f_VoxelGrid);
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_Right, f_FloorCenter.m_Y, f_FloorCenter.m_Z), 3, vLength - 4, vHeight - 2, f_Position, f_VoxelGrid);
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
					if(((vWidth - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						}

					if((((vLength / 2) - 4) > 1) &&
						((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X, f_FloorCenter.m_Y, f_FloorCenter.m_Z + ((float)vLength / 2.0f) * BLOCK_RENDER), 3, (vLength / 2) - 4, vHeight - 2, f_Position, f_VoxelGrid);
						}
					} //.. Wall Lower
				else if(f_RandomFingerInt == 1)
					{
					if(((vWidth - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						}

					if((((vLength / 2) - 4) > 1) &&
						((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X, f_FloorCenter.m_Y, f_FloorCenter.m_Z - ((float)vLength / 2.0f) * BLOCK_RENDER), 3, (vLength / 2) - 4, vHeight - 2, f_Position, f_VoxelGrid);
						}
					} //.. Wall Lower
				else if(f_RandomFingerInt == 2)
					{
					if((vLength - 4 > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, 3, vLength - 4, vHeight - 2, f_Position, f_VoxelGrid);
						}

					if((((vWidth / 2) - 4) > 1) &&
						((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X - (((float)vWidth / 2.0f) * BLOCK_RENDER), f_FloorCenter.m_Y, f_FloorCenter.m_Z), (vWidth / 2) - 4, (vLength / 2) - 4, vHeight - 2, f_Position, f_VoxelGrid);
						}
					} //.. Wall Left
				else if(f_RandomFingerInt == 3)
					{
					if((vLength - 4 > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, 3, vLength - 4, vHeight - 2, f_Position, f_VoxelGrid);
						}

					if((((vWidth / 2) - 4) > 1) &&
						((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X + (((float)vWidth / 2.0f) * BLOCK_RENDER), f_FloorCenter.m_Y, f_FloorCenter.m_Z), (vWidth / 2) - 4, (vLength / 2) - 4, vHeight - 2, f_Position, f_VoxelGrid);
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
					if(((vWidth - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						}
					if(((vWidth - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X, f_FloorCenter.m_Y, f_FloorCenter.m_Z + ((vLength / 2.0f) * BLOCK_RENDER)), vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						}
					}
				else if(f_RandomisedFingerInt == 1)
					{
					if(((vWidth - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(f_FloorCenter, vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						}
					if(((vWidth - 4) > 1) &&
					   ((vHeight - 2) > 0))
						{
						g_VoxelGridManager->Make_Gen_IntWall(BiVector(f_FloorCenter.m_X, f_FloorCenter.m_Y, f_FloorCenter.m_Z - ((vLength / 2.0f) * BLOCK_RENDER)), vWidth - 4, 3, vHeight - 2, f_Position, f_VoxelGrid);
						}
					}
				}
			}break;
		}

	return true;
}

bool VoxelGridManager::Make_Gen_Rand_Small_Lighting(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid, QpoColor f_RGBA, float f_Radius)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	   ////        ////
	  //..	Rand  ..//
	 //..  Small ..//
	////        ////
	int f_Height = Cube::randomFac() % (((vWidth * vLength) / 40) + 1);

	   ////////////////
	  //  Machine   //
	 //   Build    //
	//............//
	bool f_BuildingGenerated = g_VoxelGridManager->Make_Gen_Building(BuildingType_LampPost, f_FloorCenter, vWidth, vLength, vHeight, f_Position, f_VoxelGrid);

	if(f_BuildingGenerated == true)
		{
		QpoVec3d f_Pos(f_FloorCenter.m_X, f_FloorCenter.m_Y + ((vHeight + 1) * BLOCK_RENDER), f_FloorCenter.m_Z);

		QpoLight f_NewLight = Qpo->Light_AddtoWorld(f_Pos);

		Qpo->Light_SetAttr(f_NewLight, &f_Pos, &f_RGBA, f_Radius, true);

		return true;
		}

	return false;
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

bool VoxelGridManager::Make_Gen_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	  ///////////////////
	 // Min
	//
	float f_MinX = f_FloorCenter.m_X - ((VWidth / 2) * (BLOCK_RENDER));
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = f_FloorCenter.m_Z - ((vLength / 2) * (BLOCK_RENDER));
	float f_MaxX = f_FloorCenter.m_X + ((VWidth / 2) * (BLOCK_RENDER));
	float f_MaxY = f_FloorCenter.m_Y + (vHeight * (BLOCK_RENDER));
	float f_MaxZ = f_FloorCenter.m_Z + ((vLength / 2) * (BLOCK_RENDER));

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

	if((f_MinX < ((x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
		(f_MaxX > (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
		{
		if((f_MinY < ((y + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
			(f_MaxY > (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
			{
			if((f_MinZ < ((z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
				(f_MaxZ > (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
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
								float f_BlockXmin = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vx * (BLOCK_RENDER)));
								float f_BlockXmax = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vx + 1) * (BLOCK_RENDER)));
								float f_BlockYmin = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vy * (BLOCK_RENDER)));
								float f_BlockYmax = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vy + 1) * (BLOCK_RENDER)));
								float f_BlockZmin = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vz * (BLOCK_RENDER)));
								float f_BlockZmax = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vz + 1) * (BLOCK_RENDER)));

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
										f_VoxelGrid->SetColourType(vx, vy, vz, 0.65f, 0.65f, 0.65f, 1.0f, BlockType_Cement);
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
									else if(((f_BlockXmin >= f_Min_PlasterXmn) && (f_BlockXmin < (f_Max_PlasterXmn)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockZmin < (f_Max_PlasterZen))) ||
											((f_BlockXmin >= f_Min_PlasterXen) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockZmin < (f_Max_PlasterZen))) ||
											((f_BlockYmin >= f_Min_PlasterYmn) && (f_BlockYmin < (f_Max_PlasterYmn)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockXmin < (f_Max_PlasterZen))) ||
											((f_BlockYmin >= f_Min_PlasterYen) && (f_BlockYmin < (f_Max_PlasterYen)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockZmin >= (f_Min_PlasterZmn)) && (f_BlockXmin < (f_Max_PlasterZen))) ||
											((f_BlockZmin >= f_Min_PlasterZmn) && (f_BlockZmin < (f_Max_PlasterZmn)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen))) ||
											((f_BlockZmin >= f_Min_PlasterZen) && (f_BlockZmin < (f_Max_PlasterZen)) && (f_BlockXmin >= (f_Min_PlasterXmn)) && (f_BlockXmin < (f_Max_PlasterXen)) && (f_BlockYmin >= (f_Min_PlasterYmn)) && (f_BlockYmin < (f_Max_PlasterYen))))
										{ /////////
										 // Plaster
										//
										f_VoxelGrid->SetColourType(vx, vy, vz, 1.0f, 1.0f, 1.0f, 1.0f, BlockType_Plaster);
										f_Collide = true;
										}
									else
										{
										f_VoxelGrid->SetColour(vx, vy, vz, 0.0f, 0.0f, 0.0f, 0.0f);
										f_Collide = true;
										}
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

bool VoxelGridManager::Make_Place_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	  ///////////////////
	 // Min
	//
	float f_MinX = f_FloorCenter.m_X - ((VWidth / 2) * (BLOCK_RENDER));
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = f_FloorCenter.m_Z - ((vLength / 2) * (BLOCK_RENDER));
	float f_MaxX = f_FloorCenter.m_X + ((VWidth / 2) * (BLOCK_RENDER));
	float f_MaxY = f_FloorCenter.m_Y + (vHeight * (BLOCK_RENDER));
	float f_MaxZ = f_FloorCenter.m_Z + ((vLength / 2) * (BLOCK_RENDER));

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

	if((f_MinX < ((x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
		(f_MaxX > (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
		{
		if((f_MinY < ((y + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
			(f_MaxY > (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
			{
			if((f_MinZ < ((z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
				(f_MaxZ > (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
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
								float f_BlockXmin = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vx * (BLOCK_RENDER)));
								float f_BlockXmax = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vx + 1) * (BLOCK_RENDER)));
								float f_BlockYmin = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vy * (BLOCK_RENDER)));
								float f_BlockYmax = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vy + 1) * (BLOCK_RENDER)));
								float f_BlockZmin = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vz * (BLOCK_RENDER)));
								float f_BlockZmax = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vz + 1) * (BLOCK_RENDER)));

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
	bool f_Alter = false;
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;
	const float GRID_RENDER = (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER));

	int f_Xsgrid = 0;
	int f_Ysgrid = 0;
	int f_Zsgrid = 0;

	float f_grs_X = f_Position.m_X;
	float f_grs_Y = f_Position.m_Y;
	float f_grs_Z = f_Position.m_Z * -1.0f;

	if(f_grs_X >= 0)
		{
		while(f_grs_X >= GRID_RENDER)
			{
			f_grs_X -= GRID_RENDER;
			f_Xsgrid++;
			}
		}
	else
		{
		while(f_grs_X <= -GRID_RENDER)
			{
			f_grs_X += GRID_RENDER;
			f_Xsgrid--;
			}
		}

	if(f_grs_Y >= 0)
		{
		while(f_grs_Y >= GRID_RENDER)
			{
			f_grs_Y -= GRID_RENDER;
			f_Ysgrid++;
			}
		}
	else
		{
		while(f_grs_Y <= -GRID_RENDER)
			{
			f_grs_Y += GRID_RENDER;
			f_Ysgrid--;
			}
		}

	if(f_grs_Z >= 0)
		{
		while(f_grs_Z >= GRID_RENDER)
			{
			f_grs_Z -= GRID_RENDER;
			f_Zsgrid++;
			}
		}
	else
		{
		while(f_grs_Z <= -GRID_RENDER)
			{
			f_grs_Z += GRID_RENDER;
			f_Zsgrid--;
			}
		}

	for(int f_X = f_Xsgrid - MISS_DISTANCE; f_X < f_Xsgrid + MISS_DISTANCE; f_X++)
		{
		for(int f_Y = f_Ysgrid - MISS_DISTANCE; f_Y < f_Ysgrid + MISS_DISTANCE; f_Y++)
			{
			for(int f_Z = f_Zsgrid - MISS_DISTANCE; f_Z < f_Zsgrid + MISS_DISTANCE; f_Z++)
				{
				std::shared_ptr<VoxelGrid> f_VoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);

				if(f_VoxelGrid == nullptr)
					{
					if (((f_X >= f_Xsgrid - LOAD_DISTANCE) && (f_X < f_Xsgrid + LOAD_DISTANCE)) &&
						((f_Y >= f_Ysgrid - LOAD_DISTANCE) && (f_Y < f_Ysgrid + LOAD_DISTANCE)) &&
						((f_Z >= f_Zsgrid - LOAD_DISTANCE) && (f_Z < f_Zsgrid + LOAD_DISTANCE)))
						{
						CreateNewVoxelGrid(f_X, f_Y, f_Z);

						std::shared_ptr<VoxelGrid> f_NewVoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);

						Cube::g_WarZoneManager->acOnPushGrid(f_NewVoxelGrid);
						}
					}
				else
					{
					if ((f_X < f_Xsgrid - LOAD_DISTANCE) ||
						(f_X >= f_Xsgrid + LOAD_DISTANCE) ||
						(f_Y < f_Ysgrid - LOAD_DISTANCE) ||
						(f_Y >= f_Ysgrid + LOAD_DISTANCE) ||
						(f_Z < f_Zsgrid - LOAD_DISTANCE) ||
						(f_Z >= f_Zsgrid + LOAD_DISTANCE))
						{
						std::shared_ptr<VoxelGrid> f_MissVoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);

						if(f_MissVoxelGrid != nullptr)
							{
							if(f_MissVoxelGrid->m_Child.size() > 0)
								{
								f_MissVoxelGrid->Make_Alone();
								}

							 ///////////////////////
							// freeze any access //
							f_MissVoxelGrid->m_rebuild = 1;

							VoxelGridCoordKeys coordKeys;

							coordKeys.x = f_X;
							coordKeys.y = f_Y;
							coordKeys.z = f_Z;

							m_VoxelGridsMap[coordKeys] = nullptr;

							f_MissVoxelGrid->m_VX_Core = nullptr;

							if(f_MissVoxelGrid->mVertexPositionBuffer != 0)
								{
								glDeleteBuffers(1, &f_MissVoxelGrid->mVertexPositionBuffer);
								f_MissVoxelGrid->mVertexPositionBuffer = 0;
								}

							if(f_MissVoxelGrid->mVertexNormalBuffer != 0)
								{
								glDeleteBuffers(1, &f_MissVoxelGrid->mVertexNormalBuffer);
								f_MissVoxelGrid->mVertexNormalBuffer = 0;
								}

							if(f_MissVoxelGrid->mVertexColorBuffer != 0)
								{
								glDeleteBuffers(1, &f_MissVoxelGrid->mVertexColorBuffer);
								f_MissVoxelGrid->mVertexColorBuffer = 0;
								}

							if(f_MissVoxelGrid->mVertexTexCoordBuffer != 0)
								{
								glDeleteBuffers(1, &f_MissVoxelGrid->mVertexTexCoordBuffer);
								f_MissVoxelGrid->mVertexTexCoordBuffer = 0;
								}

							if(f_MissVoxelGrid->mIndexBuffer != 0)
								{
								glDeleteBuffers(1, &f_MissVoxelGrid->mIndexBuffer);
								f_MissVoxelGrid->mIndexBuffer = 0;
								}

							 ///////////////////////
							// clear vertex data //
							f_MissVoxelGrid->m_vec_Vertex.clear();
							f_MissVoxelGrid->m_vec_Normal.clear();
							f_MissVoxelGrid->m_vec_Color.clear();
							f_MissVoxelGrid->m_vec_Tex.clear();
							f_MissVoxelGrid->m_vec_Index.clear();

							g_UpdatingMuti.lock();

							// Array Re-Order
							for(int f_XY = f_MissVoxelGrid->m_ManagerIndex; f_XY < m_VoxelGridsVector.size() - 1; f_XY++)
								{
								m_VoxelGridsVector[f_XY] = m_VoxelGridsVector[f_XY + 1];

								m_VoxelGridsVector[f_XY]->m_ManagerIndex = f_XY;
								}

							m_VoxelGridsVector.pop_back();

							g_UpdatingMuti.unlock();
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
		}
}

bool VoxelGridManager::Make_Gen_IntWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, std::shared_ptr<VoxelGrid> f_VoxelGrid)
{
	const float BLOCK_RENDER = VoxelGrid::BLOCK_RENDER_SIZE * 2.0f;

	  ///////////////////
	 // Min
	//
	float f_MinX = f_FloorCenter.m_X - ((VWidth / 2) * (BLOCK_RENDER));
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = f_FloorCenter.m_Z - ((vLength / 2) * (BLOCK_RENDER));
	float f_MaxX = f_FloorCenter.m_X + ((VWidth / 2) * (BLOCK_RENDER));
	float f_MaxY = f_FloorCenter.m_Y + (vHeight * (BLOCK_RENDER));
	float f_MaxZ = f_FloorCenter.m_Z + ((vLength / 2) * (BLOCK_RENDER));

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

	if((f_MinX < ((x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
		(f_MaxX > (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
		{
		if((f_MinZ < ((z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
			(f_MaxZ > (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
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
							float f_BlockXmin = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vx * (BLOCK_RENDER)));
							float f_BlockXmax = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vx + 1) * (BLOCK_RENDER)));
							float f_BlockYmin = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vy * (BLOCK_RENDER)));
							float f_BlockYmax = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vy + 1) * (BLOCK_RENDER)));
							float f_BlockZmin = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vz * (BLOCK_RENDER)));
							float f_BlockZmax = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vz + 1) * (BLOCK_RENDER)));

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

	  ///////////////////
	 // Min
	//
	float f_MinX = f_FloorCenter.m_X - ((VWidth / 2) * (BLOCK_RENDER));
	float f_MinY = f_FloorCenter.m_Y;
	float f_MinZ = f_FloorCenter.m_Z - ((vLength / 2) * (BLOCK_RENDER));
	float f_MaxX = f_FloorCenter.m_X + ((VWidth / 2) * (BLOCK_RENDER));
	float f_MaxY = f_FloorCenter.m_Y + (vHeight * (BLOCK_RENDER));
	float f_MaxZ = f_FloorCenter.m_Z + ((vLength / 2) * (BLOCK_RENDER));

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

	if((f_MinX < ((x + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
		(f_MaxX > (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
		{
		if((f_MinZ < ((z + 1) * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))) &&
			(f_MaxZ > (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)))))
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
							float f_BlockXmin = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vx * (BLOCK_RENDER)));
							float f_BlockXmax = (x * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vx + 1) * (BLOCK_RENDER)));
							float f_BlockYmin = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vy * (BLOCK_RENDER)));
							float f_BlockYmax = (y * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vy + 1) * (BLOCK_RENDER)));
							float f_BlockZmin = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + (vz * (BLOCK_RENDER)));
							float f_BlockZmax = (z * (VoxelGrid::VOXEL_GRID_SIZE * (BLOCK_RENDER)) + ((vz + 1) * (BLOCK_RENDER)));

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
	bool f_Collide = false;
	bool f_Rebuild = false;

	int f_Xclip = f_Point.m_X;
	int f_Yclip = f_Point.m_Y;
	int f_Zclip = f_Point.m_Z;

	int f_Xpos = m_position.m_X;
	int f_Ypos = m_position.m_Y;
	int f_Zpos = m_position.m_Z;

	int f_RadiusInt = (int)f_Radius;

	if((f_Point.m_X >= (f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_X < ((f_x + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y >= (f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y < ((f_y + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z >= (f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z < ((f_z + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))))
		{
		int Xacting = ((f_Xpos - (VOXEL_GRID_SIZE * BLOCK_RENDER_SIZE)) - f_Xclip) / 10; // adjust here
		int Yacting = ((f_Ypos - (VOXEL_GRID_SIZE * BLOCK_RENDER_SIZE)) - f_Yclip) / 10; // adjust here
		int Zacting = ((f_Zpos - (VOXEL_GRID_SIZE * BLOCK_RENDER_SIZE)) - f_Zclip) / 10; // adjust here

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
					if(GetActive(x, y, z))
						{
						float f_TugX = (float)x + 0.5f;
						float f_TugY = (float)y + 0.5f;
						float f_TugZ = (float)z + 0.5f;
						float f_CentralX = (((f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((f_TugX * (BLOCK_RENDER_SIZE * 2.0f)))));
						float f_CentralY = (((f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((f_TugY * (BLOCK_RENDER_SIZE * 2.0f)))));
						float f_CentralZ = (((f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((f_TugZ * (BLOCK_RENDER_SIZE * 2.0f)))));
						
						BiVector f_Central(f_CentralX, f_CentralY, f_CentralZ);
						BiVector f_ForceVec = f_Central - f_Point;

						float f_ForceFac = f_ForceVec.acLength();
						float f_PowerFac = WORLD_DMG_DEFAULT * f_Power;

						   ////////////
						  // Damage //
						 ////////////
						if(f_ForceFac <= f_Radius)
							{
							f_PowerFac *= 1.0f - (f_ForceFac / f_Radius);
							f_Collide = true;

							float f_Strength = GetStrength(x, y, z);
							f_Strength -= f_PowerFac;

							if(f_Strength <= 0)
								{
								 ////////////////////////////////////////////
								// set for update on aync engine thread ////
								m_rebuild = 1;

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
						}
					}
				}
			}
		}

	if(f_Rebuild)
		{
		Make_Alone();
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

bool VoxelGrid::CollidePoint(BiVector f_Point, int f_x, int f_y, int f_z)
{
	bool f_Collide = false;
	for (int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for (int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			for (int z = 0; z < VOXEL_GRID_SIZE; z++)
				{
				if(GetActive(x, y, z))
					{
					if(f_Point.m_X > (((x * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE) + (f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
						f_Point.m_X < (((x * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE) + (f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
						f_Point.m_Y > (((y * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE) + (f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
						f_Point.m_Y < (((y * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE) + (f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
						f_Point.m_Z > (((z * (BLOCK_RENDER_SIZE * 2.0f)) - BLOCK_RENDER_SIZE) + (f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
						f_Point.m_Z < (((z * (BLOCK_RENDER_SIZE * 2.0f)) + BLOCK_RENDER_SIZE) + (f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))))
						{
						f_Collide = true;
						}
					}
				}
			}
		}

	return f_Collide;
}

VoxelDamageMask::VoxelDamageMask(VoxelBlock f_OriginBlock, BiVector f_ImpactIn, BiVector f_ImpactPoint, BiVector f_ImpactNormal)
{
	acClear();

	m_is_naturalOriginBlock = true;

	//origin block known
	m_OriginBlock = f_OriginBlock;

	m_ImpactIn = f_ImpactIn;

	m_ImpactIn.acNormalize();

	m_ImpactPoint = f_ImpactPoint;
	m_ImpactNormal = f_ImpactNormal;
	m_CurrentPoint = m_ImpactPoint;
	m_IncrementVec = m_ImpactIn * (1.0f / (float)VOXEL_RENDER_SIZE);

	QpoVec3d f_TraVec(m_ImpactIn.m_X, m_ImpactIn.m_Y, m_ImpactIn.m_Z);
	QpoVec3d f_Up(0.0f, 1.0f, 0.0f);
	QpoVec3d f_LeftToRight(0.0f, 0.0f, 0.0f);
	Qpo->Vec3d_CrossProduct(&f_TraVec, &f_Up, &f_LeftToRight);
	Qpo->Vec3d_Inverse(&f_LeftToRight);

	m_RightVec = BiVector(f_LeftToRight.x, /*f_LeftToRight.y*/ 0.0f, f_LeftToRight.z);
	m_RightVec.acNormalize();

	m_UpVec = BiVector(0.0f, 1.0f, 0.0f);
	m_UpVec.acNormalize();

	m_SingleUnit = VOXEL_RENDER_SIZE * 2.0f;

#if 0
	Qpo->Transform_New_LeftUpIn(&Q_SEnergy->SEnergy[_->NomSEnergy].Matrix, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.In);
#endif
}

VoxelDamageMask::VoxelDamageMask(BiVector f_ImpactIn, BiVector f_ImpactPoint, BiVector f_ImpactNormal)
{
	acClear();

	m_is_naturalOriginBlock = false;

	m_ImpactIn = f_ImpactIn;

	m_ImpactIn.acNormalize();

	m_ImpactPoint = f_ImpactPoint;
	m_ImpactNormal = f_ImpactNormal;
	m_CurrentPoint = m_ImpactPoint;
	m_IncrementVec = m_ImpactIn * (1.0f / (float)VOXEL_RENDER_SIZE);

	QpoVec3d f_TraVec(m_ImpactIn.m_X, m_ImpactIn.m_Y, m_ImpactIn.m_Z);
	QpoVec3d f_Up(0.0f, 1.0f, 0.0f);
	QpoVec3d f_LeftToRight(0.0f, 0.0f, 0.0f);
	Qpo->Vec3d_CrossProduct(&f_TraVec, &f_Up, &f_LeftToRight);
	Qpo->Vec3d_Inverse(&f_LeftToRight);

	m_RightVec = BiVector(f_LeftToRight.x, /*f_LeftToRight.y*/ 0.0f, f_LeftToRight.z);
	m_RightVec.acNormalize();

	m_UpVec = BiVector(0.0f, 1.0f, 0.0f);
	m_UpVec.acNormalize();

	m_SingleUnit = VOXEL_RENDER_SIZE * 2.0f;

#if 0
	Qpo->Transform_New_LeftUpIn(&Q_SEnergy->SEnergy[_->NomSEnergy].Matrix, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.In);
#endif
}

bool VoxelDamageMask::acSimulateFrame(float f_TimeScale)
{
	bool f_Collide = false;

	for(int f_LayerIDX = 0; f_LayerIDX < m_vec_MarkLayer.size(); f_LayerIDX++)
		{
		std::shared_ptr<MarkLayer> f_MarkLayer = m_vec_MarkLayer[f_LayerIDX];

		f_MarkLayer->m_CurrentMark.m_VecX = f_MarkLayer->m_Begin.m_VecX;
		f_MarkLayer->m_CurrentMark.m_VecY = f_MarkLayer->m_Begin.m_VecY;

		// current point begins at impact point
		m_CurrentPoint.m_X += f_MarkLayer->m_CurrentMark.m_VecX * m_SingleUnit;
		m_CurrentPoint.m_Y += f_MarkLayer->m_CurrentMark.m_VecY * m_SingleUnit;

		BiVector f_Cpos = m_CurrentPoint;

		int f_StepOriginX = f_MarkLayer->m_StepX;

		for(f_MarkLayer->m_CurrentMark.m_VecY = f_MarkLayer->m_Begin.m_VecY; f_MarkLayer->m_CurrentMark.m_VecY < f_MarkLayer->m_Finish.m_VecY; f_MarkLayer->m_CurrentMark.m_VecY++)
			{
			f_MarkLayer->m_StepX = f_StepOriginX;

			for(f_MarkLayer->m_CurrentMark.m_VecX = f_MarkLayer->m_Begin.m_VecX; f_MarkLayer->m_CurrentMark.m_VecX < f_MarkLayer->m_Finish.m_VecX; f_MarkLayer->m_CurrentMark.m_VecX++)
				{
				std::shared_ptr<VoxelGrid> f_GridOn;

				if(f_GridOn->m_rebuild == 0)
					{
					int f_ResultOnX;
					int f_ResultOnY;
					int f_ResultOnZ;

					f_Collide = g_VoxelGridManager->GetActive_GlobalPoint(f_Cpos, f_GridOn, &f_ResultOnX, &f_ResultOnY, &f_ResultOnZ);

					if(f_Collide)
						{

						}
					}

				f_Cpos += m_RightVec * (m_SingleUnit * f_MarkLayer->m_StepX);
				f_MarkLayer->m_StepX += f_MarkLayer->m_ChangeX;
				}

			f_Cpos -= m_UpVec * (m_SingleUnit * f_MarkLayer->m_StepY);
			f_MarkLayer->m_StepY += f_MarkLayer->m_ChangeY;
			}

#ifdef VOXDMG_FULL_TIMESCALE
		m_CurrentPoint += m_ImpactIn * (f_MarkLayer->m_ForwardSpeed * f_TimeScale);
#else
		m_CurrentPoint += m_ImpactIn * f_MarkLayer->m_ForwardSpeed;
#endif
		}

	return f_Collide;
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

};