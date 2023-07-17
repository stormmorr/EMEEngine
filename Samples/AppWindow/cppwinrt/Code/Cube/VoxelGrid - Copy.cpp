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

#include "MathHelper.h"
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

#if 1
#define VOXEL_NORMAL true
#endif

using namespace GVARS;
using namespace Cube;
using namespace std;

namespace Cube
{
bool IsMergedXNegative(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_X_Negative) == MergedSide_X_Negative; }
bool IsMergedXPositive(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_X_Positive) == MergedSide_X_Positive; }
bool IsMergedYNegative(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Y_Negative) == MergedSide_Y_Negative; }
bool IsMergedYPositive(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Y_Positive) == MergedSide_Y_Positive; }
bool IsMergedZNegative(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Z_Negative) == MergedSide_Z_Negative; }
bool IsMergedZPositive(int *merged, int x, int y, int z, int width, int height) { return (merged[x + y*width + z*width*height] & MergedSide_Z_Positive) == MergedSide_Z_Positive; }

VoxelGridManager* g_VoxelGridManager;

#define STRING(s) #s

GLuint CompileShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *sourceArray[1] = { source.c_str() };
    glShaderSource(shader, 1, sourceArray, NULL);
    glCompileShader(shader);

    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if (compileResult == 0)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Shader compilation failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 
		std::string f_errorMessage = to_string(errorMessage);

		printf("SHADER ERROR:::VX:::%s\n", f_errorMessage.c_str());

#if 1
#if 0
		throw;
#else
		while(true)
			{
			//pause
			}
#endif
#endif
    }

    return shader;
}

GLuint CompileProgram(const std::string &vsSource, const std::string &fsSource)
{
    GLuint program = glCreateProgram();

    if(program == 0)
		{
        throw;
		}

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

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

    if (linkStatus == 0)
		{
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Program link failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end());

        throw;
		}

    return program;
}

// A VoxelGrid cube is double this render size, since we create from - to + for each axis.
const float VoxelGrid::BLOCK_RENDER_SIZE = VOXEL_RENDER_SIZE;
// The VoxelGrid radius is an approximation of a sphere that will enclose totally our cuboid. (Used for culling)
const float VoxelGrid::VOXEL_GRID_RADIUS = sqrt(((VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE*2.0f)*(VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE*2.0f))*2.0f) / 2.0f + ((VoxelGrid::BLOCK_RENDER_SIZE*2.0f)*2.0f);

float VoxelGrid::BLOCK_RENDER_ADJUST = 1.5f;

float PHASE_RESONANCE = 0.009;
float g_FactorTelioch = 0.0f;
bool g_FactorDIR = true;

VoxelGrid::VoxelGrid()
{
	throw;
}

VoxelGrid::VoxelGrid(int f_ManagerIndex)
{
	m_Parent = nullptr;

	m_ParentID = -5;
	m_ManagerIndex = f_ManagerIndex;

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
	m_XSub_full = false;
	m_XAdd_full = false;
	m_YSub_full = false;
	m_YAdd_full = false;
	m_ZSub_full = false;
	m_ZAdd_full = false;

	// Blocks data
	m_colour = new unsigned int[VOXEL_GRID_SIZE_CUBED];
	m_blockType = new BlockType[VOXEL_GRID_SIZE_CUBED];
	m_blockStrength = new float[VOXEL_GRID_SIZE_CUBED];

	for(int i = 0; i < VOXEL_GRID_SIZE_CUBED; i++)
		{
		m_colour[i] = 0;
		m_blockType[i] = BlockType_Default;
		m_blockStrength[i] = WORLD_BLOCK_STRENGTH_DEFAULT;
		}

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

void VoxelGrid::Unload()
{
	delete m_colour;
	delete m_blockType;
}

void VoxelGrid::Setup(void)
{
	for(int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for(int z = 0; z < VOXEL_GRID_SIZE; z++)
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

			for(int y = 0; y < VOXEL_GRID_SIZE; y++)
				{
				float yPosition = m_position.m_Y + (y * (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f));

				if (m_Grid_blockSet[x][y][z] == true)
					{
					SetColour(x, y, z, m_Grid_colour[x][y][z]);
					}
				else
					{
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

	SetNeedsRebuild(true, true);
}

BlockType VoxelGrid::GetBlockType(int x, int y, int z)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return BlockType_Default;

	return m_blockType[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];
}

void VoxelGrid::SetBlockColour(int x, int y, int z, unsigned int colour)
{
	m_Grid_blockSet[x][y][z] = true;
	m_Grid_colour[x][y][z] = colour;
}

bool VoxelGrid::GetActive(int x, int y, int z)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return false;

	unsigned colour = m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];
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

float VoxelGrid::GetStrength(int x, int y, int z)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return 0.0f;

	float f_Result = m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];

	return f_Result;
}

void VoxelGrid::GetColour(int x, int y, int z, float* r, float* g, float* b, float* a)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

	unsigned int colour = m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];
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
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

	bool changed = ((m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] == colour) == false);

	if(changed)
		{
		m_VoxelGridChangedDuringBatchUpdate = true;
		}

	m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = colour;

	if (setBlockType)
	{
		unsigned int blockB = (colour & 0x00FF0000) >> 16;
		unsigned int blockG = (colour & 0x0000FF00) >> 8;
		unsigned int blockR = (colour & 0x000000FF);
		m_blockType[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = BlockType_Default;
	}
}

void VoxelGrid::SetColourType(int x, int y, int z, float r, float g, float b, float a, BlockType f_BlockType)
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
	SetColourType(x, y, z, colour, f_BlockType);
}

void VoxelGrid::SetColourType(int x, int y, int z, unsigned int colour, BlockType f_BlockType)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

	bool changed = ((m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] == colour) == false);

	if(changed)
		{
		m_VoxelGridChangedDuringBatchUpdate = true;
		}

	m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = colour;
	m_blockType[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = BlockType_Default;
	
	switch(f_BlockType)
		{
		case BlockType_Default:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = WORLD_BLOCK_STRENGTH_DEFAULT;
			} break;
		
		case BlockType_Iron:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 750.0f;
			} break;

		case BlockType_Cement:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 175.0f;
			} break;

		case BlockType_Steel:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 600.0f;
			} break;

		case BlockType_Brick:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 150.0f;
			} break;

		case BlockType_Wood:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 105.0f;
			} break;

		case BlockType_Stone:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 500.0f;
			} break;

		case BlockType_Metal:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 285.0f;
			} break;

		case BlockType_Plaster:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 65.0f;
			} break;

		case BlockType_Glass:
			{
			m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = 38.0f;
			} break;
		}
}

void VoxelGrid::SetStrength(int x, int y, int z, float f_Strength)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

	m_blockStrength[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = f_Strength;
}

unsigned int VoxelGrid::GetColour(int x, int y, int z)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return 0;

	return m_colour[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED];
}

// Block type
void VoxelGrid::SetBlockType(int x, int y, int z, BlockType blockType)
{
	if ((x < 0) || (x >= VOXEL_GRID_SIZE) ||
		(y < 0) || (y >= VOXEL_GRID_SIZE) ||
		(z < 0) || (z >= VOXEL_GRID_SIZE))
		return;

	m_blockType[x + y * VOXEL_GRID_SIZE + z * VOXEL_GRID_SIZE_SQUARED] = blockType;
}

unsigned int VoxelGrid::AddVertexToMesh(BiVector p1, BiVector n1, float r, float g, float b, float a)
{
	  //////////////////
	 // m_vec Mesh
	//
	m_vec_Vertex.push_back(new BiVector(p1.m_X, p1.m_Y, (p1.m_Z * -1)));
	m_vec_Normal.push_back(new BiVector(n1.m_X, n1.m_Y, n1.m_Z));
	m_vec_Color.push_back(new BiColor(r, g, b, a));

	return m_vec_Vertex.size() - 1;
}


unsigned int VoxelGridManager::AddVertexToMeshNeighbourhood(VoxelGrid* f_VoxelGrid, int str_x, int str_y, int str_z, BiVector p1, BiVector n1, float r, float g, float b, float a)
{
	   //////////////////
	  // m_vec Mesh
	 //
	//
	f_VoxelGrid->m_vec_Vertex.push_back(new BiVector(p1.m_X + f_VoxelGrid->m_position.m_X, p1.m_Y + f_VoxelGrid->m_position.m_Y, (p1.m_Z * -1) + (f_VoxelGrid->m_position.m_Z * -1)));
	f_VoxelGrid->m_vec_Normal.push_back(new BiVector(n1.m_X, n1.m_Y, n1.m_Z));
	f_VoxelGrid->m_vec_Color.push_back(new BiColor(r, g, b, a));

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

				VoxelGrid* f_Voxel = GetVoxelGrid(f_gridX, f_gridY, f_gridZ);

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
}

unsigned int VoxelGrid::AddTextureCoordinatesToMesh(float u, float v)
{
	m_vec_Tex.push_back(new BiTex(u, v));
	return m_vec_Tex.size() - 1;
}

void VoxelGrid::AddTriangleToMesh(unsigned int v1, unsigned int v2, unsigned int v3)
{
	Index* f_Index = new Index();
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
							VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);
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
							VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
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
							VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
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
							VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
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
							VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
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
							VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
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
	if(!m_isParent && (m_ParentID == -5))
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
		VoxelGrid* f_VoxParent = g_VoxelGridManager->m_VoxelGridsVector[f_ParentGridID];

		m_Parent = f_VoxParent;
		m_ParentID = f_ParentGridID;

		f_VoxParent->m_Child.push_back(this);

		f_VoxParent->m_isParent = true;

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
	if((m_isParent == false) && (m_ParentID == -5))
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
		VoxelGrid* f_VoxParent = g_VoxelGridManager->m_VoxelGridsVector[f_ParentGridID];

		m_Parent = f_VoxParent;
		m_ParentID = f_ParentGridID;

		f_VoxParent->m_Child.push_back(this);

		f_VoxParent->m_isParent = true;

		m_isParent = false;
		}
	else
		{
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
								VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);
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
								t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

								AddTriangleToMesh(v1, v3, v2);
								AddTriangleToMesh(v1, v4, v3);
								}
							}

							// Back
						if(doZNegative && ((z == 0) || (z > 0 && GetActive(x, y, z - 1) == false)))
							{
							bool addSide = true;

							if((z == 0))
								{
								VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
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
								t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

								AddTriangleToMesh(v1, v3, v2);
								AddTriangleToMesh(v1, v4, v3);
								}
							}

							// Right
						if(doXPositive && ((x == VOXEL_GRID_SIZE - 1) || (x < VOXEL_GRID_SIZE - 1 && GetActive(x + 1, y, z) == false)))
							{
							bool addSide = true;

							if ((x == VOXEL_GRID_SIZE - 1))
								{
								VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
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
								t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

								AddTriangleToMesh(v1, v3, v2);
								AddTriangleToMesh(v1, v4, v3);
								}
							}

							// Left
						if(doXNegative && ((x == 0) || (x > 0 && GetActive(x - 1, y, z) == false)))
							{
							bool addSide = true;

							if((x == 0))
								{
								VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
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
								t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

								AddTriangleToMesh(v1, v3, v2);
								AddTriangleToMesh(v1, v4, v3);
								}
							}

							// Top
						if(doYPositive && ((y == VOXEL_GRID_SIZE - 1) || (y < VOXEL_GRID_SIZE - 1 && GetActive(x, y + 1, z) == false)))
							{
							bool addSide = true;

							if((y == VOXEL_GRID_SIZE - 1))
								{
								VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
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
								t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

								AddTriangleToMesh(v1, v3, v2);
								AddTriangleToMesh(v1, v4, v3);
								}
							}

							// Bottom
						if(doYNegative && ((y == 0) || (y > 0 && GetActive(x, y - 1, z) == false)))
							{
							bool addSide = true;

							if((y == 0))
								{
								VoxelGrid* pVoxelGrid = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
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
								t2 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t3 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
								t4 = AddTextureCoordinatesToMesh(0.0f, 0.0f);

								AddTriangleToMesh(v1, v3, v2);
								AddTriangleToMesh(v1, v4, v3);
								}
							}
						}
					}
				}
			}
		}
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

					v1 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y - 1, z - 1, f_1, n1, r, g, b, a);
					v2 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y - 1, z, f_2, n1, r, g, b, a);
					v3 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y, z - 1, f_3, n1, r, g, b, a);
					v4 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y, z, f_4, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v1, v3, v2);
					AddTriangleToMesh(v2, v3, v4);

					n1.m_X = 1.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = -1.0f;

					v5 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y - 1, z - 1, f_5, n1, r, g, b, a);
					v6 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y - 1, z, f_6, n1, r, g, b, a);
					v7 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y, z - 1, f_7, n1, r, g, b, a);
					v8 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 1, y, z, f_8, n1, r, g, b, a);
					
					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					AddTriangleToMesh(v5, v6, v7);
					AddTriangleToMesh(v6, v8, v7);

					n1.m_X = 0.0f;
					n1.m_Y = -1.0f;
					n1.m_Z = 0.0f;

					v1 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 2, f_1, n1, r, g, b, a);
					v2 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 1, f_2, n1, r, g, b, a);
					v3 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 2, f_3, n1, r, g, b, a);
					v4 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 1, f_4, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					n1.m_X = 0.0f;
					n1.m_Y = 1.0f;
					n1.m_Z = 0.0f;

					v5 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 2, f_5, n1, r, g, b, a);
					v6 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 1, f_6, n1, r, g, b, a);
					v7 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 2, f_7, n1, r, g, b, a);
					v8 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 1, f_8, n1, r, g, b, a);

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

					v1 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 2, f_1, n1, r, g, b, a);
					v2 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 1, f_2, n1, r, g, b, a);
					v3 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 2, f_3, n1, r, g, b, a);
					v4 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 1, f_4, n1, r, g, b, a);

					t1 = AddTextureCoordinatesToMesh(0.0f, 0.0f);
					t2 = AddTextureCoordinatesToMesh(1.0f, 0.0f);
					t3 = AddTextureCoordinatesToMesh(0.0f, 1.0f);
					t4 = AddTextureCoordinatesToMesh(1.0f, 1.0f);

					n1.m_X = 0.0f;
					n1.m_Y = 0.0f;
					n1.m_Z = 1.0f;

					v5 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 2, f_5, n1, r, g, b, a);
					v6 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 2, z - 1, f_6, n1, r, g, b, a);
					v7 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 2, f_7, n1, r, g, b, a);
					v8 = g_VoxelGridManager->AddVertexToMeshNeighbourhood(this, x - 2, y - 1, z - 1, f_8, n1, r, g, b, a);

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
	// is child
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
				throw;
				}

			if(m_Parent->mVertexColorBuffer != 0)
				{
				mVertexColorBuffer = m_Parent->mVertexColorBuffer;
				}
			else
				{
				throw;
				}

			if(m_Parent->mVertexNormalBuffer != 0)
				{
				mVertexNormalBuffer = m_Parent->mVertexNormalBuffer;
				}
			else
				{
				throw;
				}

			if(m_Parent->mVertexTexCoordBuffer != 0)
				{
				mVertexTexCoordBuffer = m_Parent->mVertexTexCoordBuffer;
				}
			else
				{
				throw;
				}

			if(m_Parent->mIndexBuffer != 0)
				{
				mIndexBuffer = m_Parent->mIndexBuffer;
				}
			else
				{
				throw;
				}
			}
		}
	else
		{
		GenerateBuffers();
		}

	UpdateEmptyFlag();

	m_isRebuildingMesh = false;
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

	for (int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for (int z = 0; z < VOXEL_GRID_SIZE; z++)
			{
			if (GetActive(x, 0, z) == true)
				{
				y_minus++;
				}

			if (GetActive(x, VOXEL_GRID_SIZE - 1, z) == true)
				{
				y_plus++;
				}
			}
		}

	for (int x = 0; x < VOXEL_GRID_SIZE; x++)
		{
		for (int y = 0; y < VOXEL_GRID_SIZE; y++)
			{
			if (GetActive(x, y, 0) == true)
				{
				z_minus++;
				}

			if (GetActive(x, y, VOXEL_GRID_SIZE - 1) == true)
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
	if(x_minus == wallsize)
		m_XSub_full = true;

	if(x_plus == wallsize)
		m_XAdd_full = true;

	if(y_minus == wallsize)
		m_YSub_full = true;

	if(y_plus == wallsize)
		m_YAdd_full = true;

	if(z_minus == wallsize)
		m_ZSub_full = true;

	if(z_plus == wallsize)
		m_ZAdd_full = true;
}

bool VoxelGrid::UpdateSurroundedFlag(void)
{
	VoxelGrid* pVoxelGridXMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
	VoxelGrid* pVoxelGridXPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
	VoxelGrid* pVoxelGridYMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
	VoxelGrid* pVoxelGridYPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
	VoxelGrid* pVoxelGridZMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
	VoxelGrid* pVoxelGridZPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);

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

	if (numVerts == 0 && numTriangles == 0)
		{
		m_emptyVoxelGrid = true;
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
	m_isRebuildingMesh = true;

	m_vec_Vertex.clear();
	m_vec_Normal.clear();
	m_vec_Color.clear();
	m_vec_Tex.clear();
	m_vec_Index.clear();

	m_vec_Floor1Str.clear();
	m_vec_Floor2Str.clear();
	m_vec_Floor1Red.clear();
	m_vec_Floor2Red.clear();
	m_vec_Floor1Green.clear();
	m_vec_Floor2Green.clear();
	m_vec_Floor1Blue.clear();
	m_vec_Floor2Blue.clear();

#if 1
#ifdef VOXEL_NEIGHBOURHOOD
	CreateMeshCubeNeighbourhood(f_Scale);
#else
#if 0
	CreateMeshCube(f_Scale);
#else
	CreateMeshCubeDetail(f_Scale);
#endif
#endif
#else
	CreateMeshCubeNeighbourhood(f_Scale);
#endif

	if(f_Scale == 1.0f)
		{
		// Update our wall flags, so that our neighbors can check if they are surrounded
		//UpdateWallFlags();
		//UpdateSurroundedFlag();

#if 0
		VoxelGrid* pVoxelGridXMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX - 1, m_gridY, m_gridZ);
		VoxelGrid* pVoxelGridXPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX + 1, m_gridY, m_gridZ);
		VoxelGrid* pVoxelGridYMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY - 1, m_gridZ);
		VoxelGrid* pVoxelGridYPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY + 1, m_gridZ);
		VoxelGrid* pVoxelGridZMinus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ - 1);
		VoxelGrid* pVoxelGridZPlus = g_VoxelGridManager->GetVoxelGrid(m_gridX, m_gridY, m_gridZ + 1);

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
#endif
		}

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

	m_vec_Floor1Str.clear();
	m_vec_Floor2Str.clear();
	m_vec_Floor1Red.clear();
	m_vec_Floor2Red.clear();
	m_vec_Floor1Green.clear();
	m_vec_Floor2Green.clear();
	m_vec_Floor1Blue.clear();
	m_vec_Floor2Blue.clear();

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

VoxelGridManager::VoxelGridManager() :
    mWindowWidth(0),
    mWindowHeight(0),
    mDrawCount(0)
{
	// Vertex Shader source
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
		uniform vec4 cameraTrans;
        attribute vec3 aPosition;
		attribute vec3 aNormal;
        attribute vec4 aColor;
		attribute vec2 aUV;
		varying vec3 absPosition;
		varying vec3 vPosition;
		varying float vNormalX;
		varying float vNormalY;
		varying float vNormalZ;
        varying vec4 vColor;
		varying vec2 vUV;
		varying vec3 vPos;
		varying vec3 vcPos;
        void main()
			{
			vec4 f_Position = vec4(aPosition, 1.0);
			f_Position.xyz += uPos;

			vec4 f_Pos = f_Position;

			f_Position = uProjMatrix * uViewMatrix * uModelMatrix * f_Position;

			vec4 fv_Pos = vec4(uPos, 1.0);

			f_Pos = uModelMatrix * f_Pos;

			vPosition = f_Pos.xyz;

			vNormalX = aNormal.x;
			vNormalY = aNormal.y;
			vNormalZ = aNormal.z;

			vColor = aColor;
			vColor.a *= ((vPosition.z * -1.0) / 250.0);

			if(vColor.a < 0.11)
				{
				vColor.a = 0.11;
				}

			vUV = aUV;
			vPos = fv_Pos.xyz;
			absPosition = f_Position.xyz;
			vcPos = cameraTrans.xyz;

			gl_Position = f_Position;
			}
		);
#endif

		// Fragment Shader source
    const std::string fs = STRING
		(
		precision mediump float;

		float rand(vec3 co)
			{
			float f_result = fract(sin(dot(co.xyz, vec3(12.9898, 78.233, 45.5432))) * 43758.5453);
			return f_result;
			}

		uniform sampler2D f_texture;
		varying vec3 absPosition;
		varying vec3 vPosition;
		varying float vNormalX;
		varying float vNormalY;
		varying float vNormalZ;
		varying vec4 vColor;
		varying vec2 vUV;
		varying vec3 vPos;
		varying vec3 vcPos;
		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
		uniform float uLightNom;
		uniform float uSeed;
        void main()
			{
			float f_SunLightNom = 0.0;
			float f_LightNom = 0.0;

			vec3 f_Hard_Normal = vec3(0.0, 1.0, 0.0);
			vec3 vNormal = vec3(vNormalX, vNormalY, vNormalZ);

			vNormal = normalize(vNormal);

			vec4 f_Color = vColor; //texture2D(f_texture, vTexCoord);
			vec4 f_AmbientColor = f_Color;
			vec4 f_AccumulationBuffer = vec4(0.0, 0.0, 0.0, 0.0);

			float f_qsX = rand(vec3(uSeed * absPosition.x * absPosition.y * absPosition.z));
			//float f_qsY = rand(vec3(f_qsX));
			//float f_qsZ = rand(vec3(f_qsY));

			vec4 randElement = vec4(f_qsX * 0.2, f_qsX * 0.2, f_qsX * 0.2, 1.0);

			vec3 f_SunLightPos = vec3(300.0, 6400000.0, 1850.0);
			vec4 f_SunLightColor = vec4(0.93, 0.88, 0.80, 1.0);

			f_SunLightColor = (f_SunLightColor * 0.87) + (randElement * 0.13);

			float f_SunRadius = 10000000.0;

			vec3 f_L = (f_SunLightPos - absPosition);// -vPosition;
			vec3 L = normalize(f_L);
			vec4 Idiff = vec4(f_SunLightColor.rgb * max(dot(vNormal, L), 0.0), 1.0);
			Idiff = clamp(Idiff, 0.0, 1.0);
			Idiff *= 0.03;

			float f_SunDistanceL = sqrt(dot(f_L, f_L));

			vec4 f_SunAccumulationBuffer = (Idiff * ((f_SunRadius) / f_SunDistanceL)) * 20.0;
			f_SunLightNom += 1.0;

			float f_ProcCount = 0.0;
			for(int f_i = 0; f_i < 10; f_i++)
				{
				if(f_ProcCount < uLightNom)
					{
					if(uLightPos[f_i].w > 0.0)
						{
						vec3 f_LightPos = uLightPos[f_i].xyz;

						float f_LightRadius = uLightPos[f_i].w;
						vec3 position = vPosition;

						vec3 to_light = (f_LightPos - position) - vcPos;
						vec3 to_light_norm = normalize(to_light);

						vec4 Idiffl = vec4(uLightColor[f_i].rgb * max(dot(vNormal, to_light_norm), 0.0), 1.0);
						Idiffl = clamp(Idiffl, 0.0, 1.0);
						Idiffl *= 0.03;

						// Scale the color of this fragment based on its angle to the light.
						f_AccumulationBuffer += Idiffl * (f_LightRadius / 20.0);

						float f_Intensity = 0.4;
						float f_IntenseInvert = (1.0 - f_Intensity) * 5.0;

						f_LightNom += 1.0 * f_IntenseInvert;
						}
					}

				f_ProcCount += 1.0;
				}

			vec4 f_Result = vec4(0.0, 0.0, 0.0, 0.0);
			float f_sunamp = 0.5;
			float f_amp = 0.5;

			f_Result.r += (f_SunAccumulationBuffer.r / (f_SunLightNom)) * f_sunamp;
			f_Result.g += (f_SunAccumulationBuffer.g / (f_SunLightNom)) * f_sunamp;
			f_Result.b += (f_SunAccumulationBuffer.b / (f_SunLightNom)) * f_sunamp;
			f_Result.a += (f_SunAccumulationBuffer.a / (f_SunLightNom)) * f_sunamp;

			if(f_LightNom >= 1.0)
				{
				f_Result.r += (f_AccumulationBuffer.r / (f_LightNom)) * f_amp;
				f_Result.g += (f_AccumulationBuffer.g / (f_LightNom)) * f_amp;
				f_Result.b += (f_AccumulationBuffer.b / (f_LightNom)) * f_amp;
				f_Result.a += (f_AccumulationBuffer.a / (f_LightNom)) * f_amp;
				}

			f_Result.a = 1.0;

			gl_FragColor = f_AmbientColor * f_Result;
			gl_FragColor.a = 1.0;
			}
		);

    // Set up the shader and its uniform/attribute locations.
    mProgram = CompileProgram(vs, fs);
    mPositionAttribLocation = glGetAttribLocation(mProgram, "aPosition");
	mNormalAttribLocation = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocation = glGetAttribLocation(mProgram, "aColor");
	mTexCoordAttribLocation = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
    mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
    mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");
	mPosUniformLocation = glGetUniformLocation(mProgram, "uPos");
	mLightPosUniformLocation = glGetUniformLocation(mProgram, "uLightPos");
	mLightColorUniformLocation = glGetUniformLocation(mProgram, "uLightColor");
	mLightNomUniformLocation = glGetUniformLocation(mProgram, "uLightNom");
	mTimeUniformLocation = glGetUniformLocation(mProgram, "uSeed");
	mCameraTranslationUniformLocation = glGetUniformLocation(mProgram, "cameraTrans");

	mFloor1StrAttribLocation = glGetAttribLocation(mProgram, "aFloor1Str");
	mFloor2StrAttribLocation = glGetAttribLocation(mProgram, "aFloor2Str");
	mFloor1RedAttribLocation = glGetAttribLocation(mProgram, "aFloor1Red");
	mFloor2RedAttribLocation = glGetAttribLocation(mProgram, "aFloor2Red");
	mFloor1GreenAttribLocation = glGetAttribLocation(mProgram, "aFloor1Green");
	mFloor2GreenAttribLocation = glGetAttribLocation(mProgram, "aFloor2Green");
	mFloor1BlueAttribLocation = glGetAttribLocation(mProgram, "aFloor1Blue");
	mFloor2BlueAttribLocation = glGetAttribLocation(mProgram, "aFloor2Blue");

#if 0
    // Then set up the cube geometry.
    GLfloat vertexPositions[] =
		{
        -4.0f, -4.0f, -4.0f,
        -4.0f, -4.0f,  4.0f,
        -4.0f,  4.0f, -4.0f,
        -4.0f,  4.0f,  4.0f,
         4.0f, -4.0f, -4.0f,
         4.0f, -4.0f,  4.0f,
         4.0f,  4.0f, -4.0f,
         4.0f,  4.0f,  4.0f,
		};

    glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	// Then set up the cube geometry.
	GLfloat vertexNormals[] =
		{
		-4.0f, -4.0f, -4.0f,
		-4.0f, -4.0f,  4.0f,
		-4.0f,  4.0f, -4.0f,
		-4.0f,  4.0f,  4.0f,
		4.0f, -4.0f, -4.0f,
		4.0f, -4.0f,  4.0f,
		4.0f,  4.0f, -4.0f,
		4.0f,  4.0f,  4.0f,
		};

	glGenBuffers(1, &mVertexNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexNormals), vertexNormals, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
		{
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
		};

    glGenBuffers(1, &mVertexColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

	// Then set up the cube geometry.
	GLfloat vertexUV[] =
		{
		-4.0f, -4.0f,
		-4.0f, -4.0f,
		-4.0f,  4.0f,
		-4.0f,  4.0f,
		4.0f, -4.0f,
		4.0f, -4.0f,
		4.0f,  4.0f,
		4.0f,  4.0f,
		};

	glGenBuffers(1, &mVertexTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexUV), vertexUV, GL_STATIC_DRAW);

    short indices[] =
		{
        0, 1, 2, // -x
        1, 3, 2,

        4, 6, 5, // +x
        5, 6, 7,

        0, 5, 1, // -y
        0, 4, 5,

        2, 7, 6, // +y
        2, 3, 7,
              
        0, 6, 4, // -z
        0, 2, 6,
              
        1, 7, 3, // +z
        1, 5, 7,
		};

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif

	g_Width = 3600;
	g_Height = 1900;
}

VoxelGridManager::~VoxelGridManager()
{
    if(mProgram != 0)
		{
        glDeleteProgram(mProgram);
        mProgram = 0;
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

VoxelGrid* VoxelGridManager::GetVoxelGridFromPosition(float posX, float posY, float posZ)
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

void VoxelGridManager::DrawPlayer(BiVector f_Position, int f_Player)
{
#if 0
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

	if (mProgram == 0)
		return;

	glUseProgram(mProgram);

	
	VoxelGrid* f_VoxelGrid = m_playerVoxelGrid[f_Player];
	BiVector f_Pos(-f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
	BiVector f_VecTo = f_VoxelGrid->m_position - f_Pos;

	float f_Dist = f_VecTo.acLength();
	if(f_Dist < 800.0f)
		{
		glBindBuffer(GL_ARRAY_BUFFER, f_VoxelGrid->mVertexPositionBuffer);
		glEnableVertexAttribArray(mPositionAttribLocation);
		glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, f_VoxelGrid->mVertexNormalBuffer);
		glEnableVertexAttribArray(mNormalAttribLocation);
		glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, f_VoxelGrid->mVertexColorBuffer);
		glEnableVertexAttribArray(mColorAttribLocation);
		glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, f_VoxelGrid->mVertexTexCoordBuffer);
		glEnableVertexAttribArray(mTexCoordAttribLocation);
		glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_VoxelGrid->mIndexBuffer);

#if 0
		MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
		g_Spin += 0.0015;
#else
		MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
		glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

		MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

		MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
		glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

		glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
#if 0
		glEnable(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, f_Bitmap);
		glUniform1i(mTextureUniformLocation, 0);
#endif

		float f_LightDist[50];
		bool f_LightTest[50];
		int f_LightIndex[50];

		g_LightPos[0] = 0;
		g_LightPos[1] = 0;
		g_LightPos[2] = 0;
		g_LightPos[3] = 0;
		g_LightPos[4] = 0;
		g_LightPos[5] = 0;
		g_LightPos[6] = 0;
		g_LightPos[7] = 0;
		g_LightPos[8] = 0;
		g_LightPos[9] = 0;
		g_LightPos[10] = 0;
		g_LightPos[11] = 0;
		g_LightPos[12] = 0;
		g_LightPos[13] = 0;
		g_LightPos[14] = 0;
		g_LightPos[15] = 0;
		g_LightPos[16] = 0;
		g_LightPos[17] = 0;
		g_LightPos[18] = 0;
		g_LightPos[19] = 0;
		g_LightPos[20] = 0;
		g_LightPos[21] = 0;
		g_LightPos[22] = 0;
		g_LightPos[23] = 0;
		g_LightPos[24] = 0;
		g_LightPos[25] = 0;
		g_LightPos[26] = 0;
		g_LightPos[27] = 0;
		g_LightPos[28] = 0;
		g_LightPos[29] = 0;
		g_LightPos[30] = 0;
		g_LightPos[31] = 0;
		g_LightPos[32] = 0;
		g_LightPos[33] = 0;
		g_LightPos[34] = 0;
		g_LightPos[35] = 0;
		g_LightPos[36] = 0;
		g_LightPos[37] = 0;
		g_LightPos[38] = 0;
		g_LightPos[39] = 0;

		g_LightColor[0] = 0;
		g_LightColor[1] = 0;
		g_LightColor[2] = 0;
		g_LightColor[3] = 0;
		g_LightColor[4] = 0;
		g_LightColor[5] = 0;
		g_LightColor[6] = 0;
		g_LightColor[7] = 0;
		g_LightColor[8] = 0;
		g_LightColor[9] = 0;
		g_LightColor[10] = 0;
		g_LightColor[11] = 0;
		g_LightColor[12] = 0;
		g_LightColor[13] = 0;
		g_LightColor[14] = 0;
		g_LightColor[15] = 0;
		g_LightColor[16] = 0;
		g_LightColor[17] = 0;
		g_LightColor[18] = 0;
		g_LightColor[19] = 0;
		g_LightColor[20] = 0;
		g_LightColor[21] = 0;
		g_LightColor[22] = 0;
		g_LightColor[23] = 0;
		g_LightColor[24] = 0;
		g_LightColor[25] = 0;
		g_LightColor[26] = 0;
		g_LightColor[27] = 0;
		g_LightColor[28] = 0;
		g_LightColor[29] = 0;
		g_LightColor[30] = 0;
		g_LightColor[31] = 0;
		g_LightColor[32] = 0;
		g_LightColor[33] = 0;
		g_LightColor[34] = 0;
		g_LightColor[35] = 0;
		g_LightColor[36] = 0;
		g_LightColor[37] = 0;
		g_LightColor[38] = 0;
		g_LightColor[39] = 0;

		if(Q_Nom_Light > 10)
			{
			Q_Nom_Light = 10;
			}

		int f_Count = 0;
		for(int f_Point = 0; f_Point < Q_Nom_Light; f_Point++)
			{
			while (!g_Light[f_Count].m_ON)
				{
				f_Count++;
				}

			Cube::BiVector f_PositionB(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 45, playerAV[g_Player]->Xform.Translation.z);
			Cube::BiVector f_PosB(g_Light[f_Count].m_Pos.x, g_Light[f_Count].m_Pos.y, g_Light[f_Count].m_Pos.z);
			Cube::BiVector f_VecToB = f_PositionB - f_PosB;

			float f_DistB = f_VecToB.acLength();
			f_LightDist[f_Point] = f_DistB;
			f_LightIndex[f_Point] = f_Count;
			f_LightTest[f_Point] = true;
			f_Count++;
			}

		for(int f_F = 0; f_F < 10; f_F++)
			{
			float f_Max = 1200.0f;
			int f_Shortest = 0;
			bool f_Any = false;
			for(int f_L = 0; f_L < Q_Nom_Light; f_L++)
				{
				if (f_LightTest[f_L])
					{
					if (f_LightDist[f_L] < f_Max)
						{
						f_Max = f_LightDist[f_L];
						f_Shortest = f_L;
						f_Any = true;
						}
					}
				}


			

			//////////
			// Light
			//
			if(f_Any)
				{
				f_LightTest[f_Shortest] = false;

				g_LightPos[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Pos.x;
				g_LightPos[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Pos.y;
				g_LightPos[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Pos.z * -1.0f;
				g_LightPos[(f_F * 4) + 3] = g_Light[f_LightIndex[f_Shortest]].m_Radius;
				g_LightColor[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Color.red / 255;
				g_LightColor[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Color.green / 255;
				g_LightColor[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Color.blue / 255;
				g_LightColor[(f_F * 4) + 3] = g_FactorTelioch;
				g_LightNom += 1.0f;
				}
			else
				{
				g_LightPos[f_F * 4] = 0.0f;
				g_LightPos[(f_F * 4) + 1] = 0.0f;
				g_LightPos[(f_F * 4) + 2] = 0.0f;
				g_LightPos[(f_F * 4) + 3] = 0.0f;
				g_LightColor[f_F * 4] = 0.0f;
				g_LightColor[(f_F * 4) + 1] = 0.0f;
				g_LightColor[(f_F * 4) + 2] = 0.0f;
				g_LightColor[(f_F * 4) + 3] = 0.0f;
				}
			}

		glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
		glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));

#if 0
		float g_LightPos[4];
		float g_LightColor[4];
		float f_LightDist[50];
		bool f_LightTest[50];
		int f_LightIndex[50];
		int g_LightNom = 0;

		if(Q_Nom_Light > 10)
			{
			Q_Nom_Light = 10;
			}

		int f_Count = 0;
		for(int f_Point = 0; f_Point < Q_Nom_Light; f_Point++)
			{
			while(!g_Light[f_Count].m_ON)
				{
				f_Count++;
				}

			BiVector f_Pos(g_Light[f_Count].m_Pos.x, g_Light[f_Count].m_Pos.y, g_Light[f_Count].m_Pos.z);
			BiVector f_VecTo = f_Position - f_Pos;

			float f_Dist = f_VecTo.acLength();
			f_LightDist[f_Point] = f_Dist;
			f_LightIndex[f_Point] = f_Count;
			f_LightTest[f_Point] = true;
			}

		for(int f_F = 0; f_F < 10; f_F++)
			{
			float f_Max = 1200.0f;
			int f_Shortest = 0;
			bool f_Any = false;
			for(int f_L = 0; f_L < Q_Nom_Light; f_L++)
				{
				if(f_LightTest[f_L])
					{
					if(f_LightDist[f_L] < f_Max)
						{
						f_Max = f_LightDist[f_L];
						f_Shortest = f_L;
						f_Any = true;
						}
					}
				}

			  //////////
			 // Light
			//
			if(f_Any)
				{
				f_LightTest[f_Shortest] = false;

				g_LightPos[0] = g_Light[f_LightIndex[f_Shortest]].m_Pos.x;
				g_LightPos[1] = g_Light[f_LightIndex[f_Shortest]].m_Pos.y;
				g_LightPos[2] = g_Light[f_LightIndex[f_Shortest]].m_Pos.z;
				g_LightPos[3] = g_Light[f_LightIndex[f_Shortest]].m_Radius;
				g_LightColor[0] = g_Light[f_LightIndex[f_Shortest]].m_Color.red / 255;
				g_LightColor[1] = g_Light[f_LightIndex[f_Shortest]].m_Color.green / 255;
				g_LightColor[2] = g_Light[f_LightIndex[f_Shortest]].m_Color.blue / 255;
				g_LightColor[3] = g_Light[f_LightIndex[f_Shortest]].m_Color.alpha / 255;

				glUniform4fv(mLightPosUniformLocation, 1, &(g_LightPos[0]));
				glUniform4fv(mLightColorUniformLocation, 1, &(g_LightColor[0]));
				g_LightNom++;
				}
			else
				{
				f_F = 10;
				}
			}
#endif

#if 1
		glUniform1f(mLightNomUniformLocation, g_LightNom);
#endif

		// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
		glDrawElements(GL_TRIANGLES, f_VoxelGrid->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
		}
}

void VoxelGridManager::Draw(BiVector f_Position)
{
#if 0
	f_Position.m_X += f_axisX;
	f_Position.m_Y += f_axisY;
	f_Position.m_Z += f_axisZ;
#endif

#if 0
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
#else
#if 1
	glDisable(GL_BLEND);
#else
	glEnable(GL_BLEND);
#endif
#if 1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
#else
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
#if 1
	glEnable(GL_DEPTH_TEST);
#endif
#endif

#if 0
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
#endif

	if(g_FactorDIR)
		{
		if(g_FactorTelioch > 2.0)
			{
			g_FactorTelioch = 2.0f;
			g_FactorDIR = false;
			}
		else
			{
			g_FactorTelioch += Cube::random() * PHASE_RESONANCE;
			}
		}
	else
		{
		if(g_FactorTelioch < 0.0f)
			{
			g_FactorTelioch = 0.0f;
			g_FactorDIR = true;
			}
		else
			{
			g_FactorTelioch -= Cube::random() * PHASE_RESONANCE;
			}
		}

	if(mProgram == 0)
		return;

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
	float f_LightDist[5000];
	bool f_LightTest[5000];
	bool f_LightSelect[5000];
	int f_LightIndex[5000];

	g_LightNom = 0.0f;

	for(int f_Helly = 0; f_Helly < 10; f_Helly++)
		{
		f_LightSelect[f_Helly] = false;
		f_LightTest[f_Helly] = true;
		g_LightPos[f_Helly] = 0;
		g_LightPos[f_Helly] = 0;
		g_LightPos[f_Helly] = 0;
		g_LightPos[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		}

	int f_Count = 0;
	int f_CountIndex = 0;
	for(int f_Point = 0; f_Point < Q_Nom_Light_Orig; f_Point++)
		{
		if((f_Count < Q_Nom_Light))
			{
			while(!(g_Light[f_Count].m_ON) && ((g_Light[f_Count].m_Radius < 0.0f) || (g_Light[f_Count].m_Radius > 10000.0f)))
				{
				f_Count++;
				}

			if(f_Count < 5000)
				{
				if(f_LightSelect[f_CountIndex] == false)
					{
					f_LightSelect[f_CountIndex] = true;
					BiVector f_Pos(g_Light[f_Count].m_Pos.x, g_Light[f_Count].m_Pos.y, g_Light[f_Count].m_Pos.z);
					BiVector f_VecTo = f_Position - f_Pos;

					float f_Dist = f_VecTo.acLength();
					f_LightDist[f_CountIndex] = f_Dist;
					f_LightIndex[f_CountIndex] = f_Count;
					f_LightTest[f_CountIndex] = true;
					f_LightSelect[f_CountIndex] = true;
					f_CountIndex++;
					}
				}
			}
		else
			{
			f_Point = Q_Nom_Light_Orig;
			}

		f_Count++;
		}

	int f_NewLightNom = f_CountIndex;

	for(int f_F = 0; f_F < 10; f_F++)
		{
		float f_Max = 10000.0f;
		int f_Shortest = 0;
		bool f_Any = false;
		for(int f_L = 0; f_L < f_NewLightNom; f_L++)
			{
			if(f_LightTest[f_L])
				{
				if(f_LightDist[f_L] < f_Max)
					{
					f_Max = f_LightDist[f_L];
					f_Shortest = f_L;
					f_Any = true;
					}
				}
			}

		  //////////
		 // Light
		//
		if(f_Any)
			{
			f_LightTest[f_Shortest] = false;
						
			g_LightPos[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Pos.x * -1.0f;
			g_LightPos[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Pos.y;
			g_LightPos[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Pos.z * -1.0f;
			g_LightPos[(f_F * 4) + 3] = g_Light[f_LightIndex[f_Shortest]].m_Radius * 15.0f;
			g_Light[f_LightIndex[f_Shortest]].m_Radius -= 50.0f;
			g_LightColor[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Color.red / 255;
			g_LightColor[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Color.green / 255;
			g_LightColor[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Color.blue / 255;
			g_LightColor[(f_F * 4) + 3] = g_FactorTelioch;
			g_LightNom += 1.0f;
			}
		else
			{
			g_LightPos[f_F * 4] = 0.0f;
			g_LightPos[(f_F * 4) + 1] = 0.0f;
			g_LightPos[(f_F * 4) + 2] = 0.0f;
			g_LightPos[(f_F * 4) + 3] = 0.0f;
			g_LightColor[f_F * 4] = 0.0f;
			g_LightColor[(f_F * 4) + 1] = 0.0f;
			g_LightColor[(f_F * 4) + 2] = 0.0f;
			g_LightColor[(f_F * 4) + 3] = 0.0f;
			}
		}

#if 0
	g_LightPos[0] = playerAV[0]->Xform.Translation.x * -1;
	g_LightPos[1] = playerAV[0]->Xform.Translation.y + 130.0f;
	g_LightPos[2] = playerAV[0]->Xform.Translation.z * -1;
	g_LightPos[3] = 1000.0f;
	g_LightColor[0] = 0.9f;
	g_LightColor[1] = 0.9f;
	g_LightColor[2] = 0.6f;
	g_LightColor[3] = 1.0f;
	g_LightNom++;

	if(g_LightonXDir == 0)
		{
		g_LightonX += 10;

		if(g_LightonX >= 500.0f)
			{
			g_LightonXDir = 1;
			g_LightonX = 500.0f;
			}
		}
	else
		{
		g_LightonX -= 10;

		if(g_LightonX <= -500.0f)
			{
			g_LightonXDir = 0;
			g_LightonX = -500.0f;
			}
		}

	if(g_LightonZDir == 0)
		{
		g_LightonZ += 10;

		if(g_LightonZ >= 500.0f)
			{
			g_LightonZDir = 1;
			g_LightonZ = 500.0f;
			}
		}
	else
		{
		g_LightonZ -= 10;

		if(g_LightonZ <= -500.0f)
			{
			g_LightonZDir = 0;
			g_LightonZ = -500.0f;
			}
		}

	if(g_LightonXDir == 0)
		{
		g_LightonG += 0.01;

		if(g_LightonG >= 1.0f)
			{
			g_LightonG = 1.0f;
			}
		}
	else
		{
		g_LightonG -= 0.01;

		if(g_LightonG <= 0.0f)
			{
			g_LightonG = 0.0f;
			}
		}

	if(g_LightonZDir == 0)
		{
		g_LightonR += 0.01;

		if(g_LightonR >= 1.0f)
			{
			g_LightonR = 1.0f;
			}
		}
	else
		{
		g_LightonR -= 0.01;

		if(g_LightonR <= 0.0f)
			{
			g_LightonR = 0.0f;
			}
		}

	g_LightPos[4] = g_LightonX;
	g_LightPos[5] = g_LightonY;
	g_LightPos[6] = g_LightonZ;
	g_LightPos[7] = g_LightonRadius;
	g_LightColor[4] = g_LightonR;
	g_LightColor[5] = g_LightonG;
	g_LightColor[6] = g_LightonB;
	g_LightColor[7] = 1.0f;
	g_LightNom++;
#endif

#if 0
	g_LightNom = 0;
#endif

	glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
	glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));

	glUniform1f(mLightNomUniformLocation, g_LightNom);

	glUniform1f(mTimeUniformLocation, (float)rand() / 32767);

#if 0
	pFrustum f_View;

	float cameraDistance = (((750.0f / g_Zoom) * (1 - g_ZoomFactor)) + 300.0f) * g_ArenaSize;

	float fov = 115.0f;
	float aspect = float(1280.0f) / float(1080.0f);
	float farplane = 10000.0f;
	pVector f_camX(1.0f, 0.0f, 0.0f);
	pVector f_camY(0.0f, 1.0f, 0.5f);
	pVector f_camZ(0.0f, -1.0f, 1.0f);

	pVector f_PlayerPos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	f_camX.normalize();
	f_camY.normalize();
	f_camZ.normalize();

	pVector f_CamPos = f_PlayerPos + (f_camZ * (cameraDistance * 2));

	f_View.build(f_CamPos,
		f_camX,
		f_camY,
		f_camZ,
		fov / aspect,
		aspect,
		farplane);

#if 0
	f_View.draw();
#endif
#endif

	int f_Size = m_VoxelGridsVector.size();

	for(unsigned int f_VoxelGridCount = 0; f_VoxelGridCount < f_Size; f_VoxelGridCount++)
		{
#if 0
		float PclipX = (f_ModelViewProj.m[0][0] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X) + (f_ModelViewProj.m[0][1] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y) + (f_ModelViewProj.m[0][2] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z) + (f_ModelViewProj.m[0][3] * 1.0f);
		float PclipY = (f_ModelViewProj.m[1][0] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X) + (f_ModelViewProj.m[1][1] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y) + (f_ModelViewProj.m[1][2] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z) + (f_ModelViewProj.m[1][3] * 1.0f);
		float PclipZ = (f_ModelViewProj.m[2][0] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X) + (f_ModelViewProj.m[2][1] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y) + (f_ModelViewProj.m[2][2] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z) + (f_ModelViewProj.m[2][3] * 1.0f);
		float PclipW = (f_ModelViewProj.m[3][0] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X) + (f_ModelViewProj.m[3][1] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y) + (f_ModelViewProj.m[3][2] * m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z) + (f_ModelViewProj.m[3][3] * 1.0f);
		bool f_IN = abs(PclipX) < PclipW && abs(PclipY) < PclipW &&	0.0 < PclipZ && PclipZ < PclipW;
#endif

		bool f_Bool = true;
		BiVector f_Pos = m_VoxelGridsVector[f_VoxelGridCount]->m_position;

		if(f_Pos.m_Z < playerAV[0]->Xform.Translation.z - 400.0f)
			{
			f_Bool = false;
			}
			
		BiVector f_BiVector(m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X + f_Position.m_X, m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y + f_Position.m_Y, m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z + f_Position.m_Z);

		float f_Dist = f_BiVector.acLength();
		if(f_Dist < VIEW_DISTANCE)
			{
		//if(/*f_View.is_inside(pVector(m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X, m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y, m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z)) || */1)
		//	{
			if(m_VoxelGridsVector[f_VoxelGridCount]->m_VX || 1)
				{
				if(/*(m_VoxelGridsVector[f_VoxelGridCount]->m_VX->f_Renderon == true) && */(m_VoxelGridsVector[f_VoxelGridCount]->m_created == true) && (m_VoxelGridsVector[f_Count]->m_rebuild < 1))
					{
					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexPositionBuffer);
					glEnableVertexAttribArray(mPositionAttribLocation);
					glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexNormalBuffer);
					glEnableVertexAttribArray(mNormalAttribLocation);
					glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexColorBuffer);
					glEnableVertexAttribArray(mColorAttribLocation);
					glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexTexCoordBuffer);
					glEnableVertexAttribArray(mTexCoordAttribLocation);
					glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mIndexBuffer);

#ifdef VOXEL_NEIGHBOURHOOD
#if 0
					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1StrBuffer);
					glEnableVertexAttribArray(mFloor1StrAttribLocation);
					glVertexAttribPointer(mFloor1StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2StrBuffer);
					glEnableVertexAttribArray(mFloor2StrAttribLocation);
					glVertexAttribPointer(mFloor2StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1RedBuffer);
					glEnableVertexAttribArray(mFloor1RedAttribLocation);
					glVertexAttribPointer(mFloor1RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2RedBuffer);
					glEnableVertexAttribArray(mFloor2RedAttribLocation);
					glVertexAttribPointer(mFloor2RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1GreenBuffer);
					glEnableVertexAttribArray(mFloor1GreenAttribLocation);
					glVertexAttribPointer(mFloor1GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2GreenBuffer);
					glEnableVertexAttribArray(mFloor2GreenAttribLocation);
					glVertexAttribPointer(mFloor2GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1BlueBuffer);
					glEnableVertexAttribArray(mFloor1BlueAttribLocation);
					glVertexAttribPointer(mFloor1BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

					glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2BlueBuffer);
					glEnableVertexAttribArray(mFloor2BlueAttribLocation);
					glVertexAttribPointer(mFloor2BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
#endif
#endif

					//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
					glUniform3f(mPosUniformLocation, f_Position.m_X + m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X, f_Position.m_Y + m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y, f_Position.m_Z + m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z);

#if 0
#if 0
					MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
					g_Spin += 0.0015;
#else
					MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

					MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

					MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
					glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

#if 0
					MathHelper::Matrix4 f_ModelViewProj = MathHelper::SimpleModelMatrix((float)0.0f);

					f_ModelViewProj.m[0][0] = modelMatrix.m[0][0] * viewMatrix.m[0][0] * projectionMatrix.m[0][0];
					f_ModelViewProj.m[0][1] = modelMatrix.m[0][1] * viewMatrix.m[0][1] * projectionMatrix.m[0][1];
					f_ModelViewProj.m[0][2] = modelMatrix.m[0][2] * viewMatrix.m[0][2] * projectionMatrix.m[0][2];
					f_ModelViewProj.m[0][3] = modelMatrix.m[0][3] * viewMatrix.m[0][3] * projectionMatrix.m[0][3];

					f_ModelViewProj.m[1][0] = modelMatrix.m[1][0] * viewMatrix.m[1][0] * projectionMatrix.m[1][0];
					f_ModelViewProj.m[1][1] = modelMatrix.m[1][1] * viewMatrix.m[1][1] * projectionMatrix.m[1][1];
					f_ModelViewProj.m[1][2] = modelMatrix.m[1][2] * viewMatrix.m[1][2] * projectionMatrix.m[1][2];
					f_ModelViewProj.m[1][3] = modelMatrix.m[1][3] * viewMatrix.m[1][3] * projectionMatrix.m[1][3];

					f_ModelViewProj.m[2][0] = modelMatrix.m[2][0] * viewMatrix.m[2][0] * projectionMatrix.m[2][0];
					f_ModelViewProj.m[2][1] = modelMatrix.m[2][1] * viewMatrix.m[2][1] * projectionMatrix.m[2][1];
					f_ModelViewProj.m[2][2] = modelMatrix.m[2][2] * viewMatrix.m[2][2] * projectionMatrix.m[2][2];
					f_ModelViewProj.m[2][3] = modelMatrix.m[2][3] * viewMatrix.m[2][3] * projectionMatrix.m[2][3];

					f_ModelViewProj.m[3][0] = modelMatrix.m[3][0] * viewMatrix.m[3][0] * projectionMatrix.m[3][0];
					f_ModelViewProj.m[3][1] = modelMatrix.m[3][1] * viewMatrix.m[3][1] * projectionMatrix.m[3][1];
					f_ModelViewProj.m[3][2] = modelMatrix.m[3][2] * viewMatrix.m[3][2] * projectionMatrix.m[3][2];
					f_ModelViewProj.m[3][3] = modelMatrix.m[3][3] * viewMatrix.m[3][3] * projectionMatrix.m[3][3];
#endif
#if 0
					float g_LightPos[40];
					float g_LightColor[40];
					float g_LightNom = 0.0f;
#endif

					float f_LightDist[5000];
					bool f_LightTest[5000];
					bool f_LightSelect[5000];
					int f_LightIndex[5000];

					if(Q_Nom_Light > 10)
						{
						Q_Nom_Light = 10;
						}

					for(int f_Helly = 0; f_Helly < 10; f_Helly++)
						{
						f_LightSelect[f_Helly] = false;
						f_LightTest[f_Helly] = true;
						g_LightPos[f_Helly] = 0;
						g_LightPos[f_Helly] = 0;
						g_LightPos[f_Helly] = 0;
						g_LightPos[f_Helly] = 0;
						g_LightColor[f_Helly] = 0;
						g_LightColor[f_Helly] = 0;
						g_LightColor[f_Helly] = 0;
						g_LightColor[f_Helly] = 0;
						}

					int f_Count3 = 0;
					for(int f_Point = 0; f_Point < Q_Nom_Light; f_Point++)
						{
						while(!g_Light[f_Count3].m_ON && f_Count3 < 5000)
							{
							f_Count3++;
							}

						if(f_Count3 < 5000)
							{
							g_Light[f_Count3].m_Radius -= 0.09f;
							if(g_Light[f_Count3].m_Radius <= 0)
								{
								g_Light[f_Count3].m_ON = 0;
								g_Light[f_Count3].m_Radius = 0;
								}
							}

						f_Count3++;
						}

#if 1
					int f_Count = 0;
					for(int f_Point = 0; f_Point < Q_Nom_Light; f_Point++)
						{
						while(!g_Light[f_Count].m_ON && f_Count < 5000)
							{
							f_Count++;
							}

						if(f_Count < 5000)
							{
							if(f_LightSelect[f_Count] == false)
								{
								f_LightSelect[f_Count] = true;
								BiVector f_Pos(g_Light[f_Count].m_Pos.x, g_Light[f_Count].m_Pos.y, g_Light[f_Count].m_Pos.z);
								BiVector f_VecTo = f_Position - f_Pos;

								float f_Dist = f_VecTo.acLength();
								f_LightDist[f_Point] = f_Dist;
								f_LightIndex[f_Point] = f_Count;
								f_LightTest[f_Point] = true;
								f_LightSelect[f_Count] = true;
								}
							}

						f_Count++;
						}

					for(int f_F = 0; f_F < 10; f_F++)
						{
						float f_Max = 10000.0f;
						int f_Shortest = 0;
						bool f_Any = false;
						for(int f_L = 0; f_L < Q_Nom_Light; f_L++)
							{
							if(f_LightTest[f_L])
								{
								if(f_LightDist[f_L] < f_Max)
									{
									f_Max = f_LightDist[f_L];
									f_Shortest = f_L;
									f_Any = true;
									}
								}
							}

							//////////
							// Light
						//
						if(f_Any)
							{
							f_LightTest[f_F] = false;
						
							/*g_Light[f_LightIndex[f_Shortest]].m_Radius -= 15.95f;
							if(g_Light[f_LightIndex[f_Shortest]].m_Radius < 0)
								{
								g_Light[f_LightIndex[f_Shortest]].m_Radius = 0;
								g_Light[f_LightIndex[f_Shortest]].m_ON = false;
								Q_Nom_Light--;
								}*/

							if(f_Shortest < 5000)
								{
								if(f_LightIndex[f_Shortest] < 5000)
									{
									g_LightPos[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Pos.x;
									g_LightPos[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Pos.y;
									g_LightPos[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Pos.z * -1.0f;
									g_LightPos[(f_F * 4) + 3] = g_Light[f_LightIndex[f_Shortest]].m_Radius;
									g_LightColor[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Color.red / 255;
									g_LightColor[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Color.green / 255;
									g_LightColor[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Color.blue / 255;
									g_LightColor[(f_F * 4) + 3] = g_FactorTelioch;
									g_LightNom += 1.0f;
									}
								else
									{
									g_LightPos[f_F * 4] = 0.0f;
									g_LightPos[(f_F * 4) + 1] = 0.0f;
									g_LightPos[(f_F * 4) + 2] = 0.0f;
									g_LightPos[(f_F * 4) + 3] = 0.0f;
									g_LightColor[f_F * 4] = 0.0f;
									g_LightColor[(f_F * 4) + 1] = 0.0f;
									g_LightColor[(f_F * 4) + 2] = 0.0f;
									g_LightColor[(f_F * 4) + 3] = 0.0f;
									}
								}
							else
								{
								g_LightPos[f_F * 4] = 0.0f;
								g_LightPos[(f_F * 4) + 1] = 0.0f;
								g_LightPos[(f_F * 4) + 2] = 0.0f;
								g_LightPos[(f_F * 4) + 3] = 0.0f;
								g_LightColor[f_F * 4] = 0.0f;
								g_LightColor[(f_F * 4) + 1] = 0.0f;
								g_LightColor[(f_F * 4) + 2] = 0.0f;
								g_LightColor[(f_F * 4) + 3] = 0.0f;
								}
							}
						else
							{
							g_LightPos[f_F * 4] = 0.0f;
							g_LightPos[(f_F * 4) + 1] = 0.0f;
							g_LightPos[(f_F * 4) + 2] = 0.0f;
							g_LightPos[(f_F * 4) + 3] = 0.0f;
							g_LightColor[f_F * 4] = 0.0f;
							g_LightColor[(f_F * 4) + 1] = 0.0f;
							g_LightColor[(f_F * 4) + 2] = 0.0f;
							g_LightColor[(f_F * 4) + 3] = 0.0f;
							}
						}
#endif

#if 0
					g_LightPos[0] = playerAV[0]->Xform.Translation.x;
					g_LightPos[1] = playerAV[0]->Xform.Translation.y + 15.0f;
					g_LightPos[2] = playerAV[0]->Xform.Translation.z * -1;
					g_LightPos[3] = 800.0f;
					g_LightColor[0] = 0.8f;
					g_LightColor[1] = 0.9f;
					g_LightColor[2] = 1.0f;
					g_LightColor[3] = 1.0f;
					g_LightNom += 1.0f;

					for(int f_Int = 0; f_Int < 10; f_Int++)
						{
						printf("x %f y %f z %f r %f\n", g_LightPos[f_Int * 4], g_LightPos[(f_Int * 4) + 1], g_LightPos[(f_Int * 4) + 2], g_LightPos[(f_Int * 4) + 3]);
						}
#endif

					glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
					glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));

					glUniform1f(mLightNomUniformLocation, g_LightNom);
#endif

					float f_Transport[4];
					float f_Team[4];
					f_Transport[0] = f_Position.m_X;
					f_Transport[1] = 0;
					f_Transport[2] = -f_Position.m_Z;
					f_Transport[3] = 1.0f;

					glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));

					int f_FaceCount = m_VoxelGridsVector[f_VoxelGridCount]->m_vec_Index.size() * 3;

					// parent grid
					if(m_VoxelGridsVector[f_VoxelGridCount]->m_ParentID >= 0)
						{
						if(m_VoxelGridsVector[f_VoxelGridCount]->m_Parent != nullptr)
							{
							if(m_VoxelGridsVector[f_VoxelGridCount]->m_Parent->m_created == true)
								{
								if(m_VoxelGridsVector[f_VoxelGridCount]->m_Parent->m_rebuild == 0)
									{
									if(m_VoxelGridsVector[f_VoxelGridCount]->m_Parent->m_emptyVoxelGrid == false)
										{
										f_FaceCount = m_VoxelGridsVector[f_VoxelGridCount]->m_Parent->m_vec_Index.size() * 3;

										if(f_FaceCount == 0)
											{
											// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
											glDrawElements(GL_TRIANGLES, f_FaceCount, GL_UNSIGNED_SHORT, 0);
											}
										}
									}
								}
							}
						}
					else
						{ // child grid
						if(f_FaceCount == 0)
							{
							// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
							glDrawElements(GL_TRIANGLES, f_FaceCount, GL_UNSIGNED_SHORT, 0);
							}
						}
					}
				else
					{
					//reorder array
#if 0
					m_VoxelGridsVector[f_VoxelGridCount]->m_VX->m_State = VOXEL_STATE_EXIT;
					delete m_VoxelGridsVector[f_VoxelGridCount];

					for(int f_c = f_VoxelGridCount; f_c < (m_VoxelGridsVector.size() - 1); f_c++)
						{
						m_VoxelGridsVector[f_c] = m_VoxelGridsVector[f_c + 1];

#if 0
						m_vec_VX[f_c] = m_vec_VX[f_c + 1];
#endif
						}

					m_VoxelGridsVector.pop_back();
					f_Size--;
#endif
					}
				}
			}
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

	for(unsigned int f_VoxelGridCount = 0; f_VoxelGridCount < f_Size; f_VoxelGridCount++)
		{
		if(m_VoxelGridsVector[f_VoxelGridCount]->m_created)
			{
			BiVector f_BiVector(m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_X - f_Position.m_X, m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Y - f_Position.m_Y, m_VoxelGridsVector[f_VoxelGridCount]->m_position.m_Z - f_Position.m_Z);

			float f_Dist = f_BiVector.acLength();
			if(f_Dist < VIEW_DISTANCE)
				{
				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexPositionBuffer);
				glEnableVertexAttribArray(mPositionAttribLocation);
				glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexNormalBuffer);
				glEnableVertexAttribArray(mNormalAttribLocation);
				glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexColorBuffer);
				glEnableVertexAttribArray(mColorAttribLocation);
				glVertexAttribPointer(mColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexTexCoordBuffer);
				glEnableVertexAttribArray(mTexCoordAttribLocation);
				glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mIndexBuffer);

				  /////////////////////////////
				 // Neighbourhood Voxels
				//
#ifdef VOXEL_NEIGHBOURHOOD
				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1StrBuffer);
				glEnableVertexAttribArray(mFloor1StrAttribLocation);
				glVertexAttribPointer(mFloor1StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2StrBuffer);
				glEnableVertexAttribArray(mFloor2StrAttribLocation);
				glVertexAttribPointer(mFloor2StrAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1RedBuffer);
				glEnableVertexAttribArray(mFloor1RedAttribLocation);
				glVertexAttribPointer(mFloor1RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2RedBuffer);
				glEnableVertexAttribArray(mFloor2RedAttribLocation);
				glVertexAttribPointer(mFloor2RedAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1GreenBuffer);
				glEnableVertexAttribArray(mFloor1GreenAttribLocation);
				glVertexAttribPointer(mFloor1GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2GreenBuffer);
				glEnableVertexAttribArray(mFloor2GreenAttribLocation);
				glVertexAttribPointer(mFloor2GreenAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor1BlueBuffer);
				glEnableVertexAttribArray(mFloor1BlueAttribLocation);
				glVertexAttribPointer(mFloor1BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_VoxelGridsVector[f_VoxelGridCount]->mVertexFloor2BlueBuffer);
				glEnableVertexAttribArray(mFloor2BlueAttribLocation);
				glVertexAttribPointer(mFloor2BlueAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
#endif

#if 0
				MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
				g_Spin += 0.0015;
#else
				MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
#endif
				glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

				MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
				glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

				MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
				glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

				glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
#if 0
				glEnable(GL_TEXTURE);
				glBindTexture(GL_TEXTURE_2D, f_Bitmap);
				glUniform1i(mTextureUniformLocation, 0);
#endif

#if 1
#if 0
				float g_LightPos[40];
				float g_LightColor[40];
				float g_LightNom = 0.0f;
#endif

				float f_LightDist[5000];
				bool f_LightTest[5000];
				int f_LightIndex[5000];

#if 1
				if(Q_Nom_Light > 10)
					{
					Q_Nom_Light = 10;
					}

				int f_Count = 0;
				for(int f_Point = 0; f_Point < Q_Nom_Light; f_Point++)
					{
					while(!g_Light[f_Count].m_ON)
						{
						f_Count++;
						}

					BiVector f_PosBC(g_Light[f_Count].m_Pos.x, g_Light[f_Count].m_Pos.y, g_Light[f_Count].m_Pos.z);
					BiVector f_VecToBC = f_Position - f_PosBC;

					float f_DistBC = f_VecToBC.acLength();
					f_LightDist[f_Point] = f_DistBC;
					f_LightIndex[f_Point] = f_Count;
					f_LightTest[f_Point] = true;
					}

				for(int f_F = 0; f_F < 10; f_F++)
					{
					float f_Max = 1200.0f;
					int f_Shortest = 0;
					bool f_Any = false;
					for(int f_L = 0; f_L < Q_Nom_Light; f_L++)
						{
						if(f_LightTest[f_L])
							{
							if(f_LightDist[f_L] < f_Max)
								{
								f_Max = f_LightDist[f_L];
								f_Shortest = f_L;
								f_Any = true;
								}
							}
						}

					  //////////
					 // Light
					//
					if(f_Any)
						{
						f_LightTest[f_Shortest] = false;

						g_LightPos[0] = g_Light[f_LightIndex[f_Shortest]].m_Pos.x;
						g_LightPos[1] = g_Light[f_LightIndex[f_Shortest]].m_Pos.y;
						g_LightPos[2] = g_Light[f_LightIndex[f_Shortest]].m_Pos.z;
						g_LightPos[3] = g_Light[f_LightIndex[f_Shortest]].m_Radius;
						g_LightColor[0] = g_Light[f_LightIndex[f_Shortest]].m_Color.red / 255;
						g_LightColor[1] = g_Light[f_LightIndex[f_Shortest]].m_Color.green / 255;
						g_LightColor[2] = g_Light[f_LightIndex[f_Shortest]].m_Color.blue / 255;
						g_LightColor[3] = g_Light[f_LightIndex[f_Shortest]].m_Color.alpha / 255;

						glUniform4fv(mLightPosUniformLocation, 1, &(g_LightPos[0]));
						glUniform4fv(mLightColorUniformLocation, 1, &(g_LightColor[0]));
						g_LightNom += 1.0f;
						}
					else
						{
						f_F = 10;
						}
					}

				glUniform1f(mLightNomUniformLocation, g_LightNom);
#else
				g_LightPos[0] = -5000.0f;
				g_LightPos[1] = 10000.0f;
				g_LightPos[2] = 4000.0f;
				g_LightPos[3] = 1.0f;
				g_LightColor[0] = 0.95f;
				g_LightColor[1] = 0.72f;
				g_LightColor[2] = 0.45f;
				g_LightColor[3] = 1.0f;
				g_LightPos[4] = -5000.0f;
				g_LightPos[5] = 10000.0f;
				g_LightPos[6] = 4000.0f;
				g_LightPos[7] = 1.0f;
				g_LightColor[4] = 0.95f;
				g_LightColor[5] = 0.72f;
				g_LightColor[6] = 0.45f;
				g_LightColor[7] = 1.0f;
				g_LightPos[8] = -5000.0f;
				g_LightPos[9] = 10000.0f;
				g_LightPos[10] = 4000.0f;
				g_LightPos[11] = 1.0f;
				g_LightColor[8] = 0.95f;
				g_LightColor[9] = 0.72f;
				g_LightColor[10] = 0.45f;
				g_LightColor[11] = 1.0f;
				g_LightPos[12] = -5000.0f;
				g_LightPos[13] = 10000.0f;
				g_LightPos[14] = 4000.0f;
				g_LightPos[15] = 1.0f;
				g_LightColor[12] = 0.95f;
				g_LightColor[13] = 0.72f;
				g_LightColor[14] = 0.45f;
				g_LightColor[15] = 1.0f;
				g_LightPos[16] = -5000.0f;
				g_LightPos[17] = 10000.0f;
				g_LightPos[18] = 4000.0f;
				g_LightPos[19] = 1.0f;
				g_LightColor[16] = 0.95f;
				g_LightColor[17] = 0.72f;
				g_LightColor[18] = 0.45f;
				g_LightColor[19] = 1.0f;
				g_LightPos[20] = -5000.0f;
				g_LightPos[21] = 10000.0f;
				g_LightPos[22] = 4000.0f;
				g_LightPos[23] = 1.0f;
				g_LightColor[20] = 0.95f;
				g_LightColor[21] = 0.72f;
				g_LightColor[22] = 0.45f;
				g_LightColor[23] = 1.0f;
				g_LightPos[24] = -5000.0f;
				g_LightPos[25] = 10000.0f;
				g_LightPos[26] = 4000.0f;
				g_LightPos[27] = 1.0f;
				g_LightColor[24] = 0.95f;
				g_LightColor[25] = 0.72f;
				g_LightColor[26] = 0.45f;
				g_LightColor[27] = 1.0f;
				g_LightPos[28] = -5000.0f;
				g_LightPos[29] = 10000.0f;
				g_LightPos[30] = 4000.0f;
				g_LightPos[31] = 1.0f;
				g_LightColor[28] = 0.95f;
				g_LightColor[29] = 0.72f;
				g_LightColor[30] = 0.45f;
				g_LightColor[31] = 1.0f;
				g_LightPos[32] = -5000.0f;
				g_LightPos[33] = 10000.0f;
				g_LightPos[34] = 4000.0f;
				g_LightPos[35] = 1.0f;
				g_LightColor[32] = 0.95f;
				g_LightColor[33] = 0.72f;
				g_LightColor[34] = 0.45f;
				g_LightColor[35] = 1.0f;
				g_LightPos[36] = -5000.0f;
				g_LightPos[37] = 10000.0f;
				g_LightPos[38] = 4000.0f;
				g_LightPos[39] = 1.0f;
				g_LightColor[36] = 0.95f;
				g_LightColor[37] = 0.72f;
				g_LightColor[38] = 0.45f;
				g_LightColor[39] = 1.0f;

				glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
				glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));

				g_LightNom = 10.0f;

				glUniform1f(mLightNomUniformLocation, g_LightNom);
#endif
#endif
				// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
				glDrawElements(GL_TRIANGLES, m_VoxelGridsVector[f_VoxelGridCount]->m_vec_Index.size() * 3, GL_UNSIGNED_SHORT, 0);
				//printf("glDrawElements(%i)\n", m_VoxelGridsVector[f_VoxelGridCount]->m_vec_Index.size());
				}
			else
				{
				//reorder array
				m_VoxelGridsVector[f_VoxelGridCount]->m_VX->m_State = VOXEL_STATE_EXIT;
				delete m_VoxelGridsVector[f_VoxelGridCount];

				for(int f_c = f_VoxelGridCount; f_c < (m_VoxelGridsVector.size() - 1); f_c++)
					{
					m_VoxelGridsVector[f_c] = m_VoxelGridsVector[f_c + 1];

#if 0
					m_vec_VX[f_c] = m_vec_VX[f_c + 1];
#endif
					}

				m_VoxelGridsVector.pop_back();
				//f_Size--;
				}
			}
		}
}

void VoxelGridManager::DrawCube(void)
{
	glDisable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);

	if(mProgram == 0)
		return;

	glUseProgram(mProgram);

	for(unsigned int f_VoxelGridCount = 0; f_VoxelGridCount < 1; f_VoxelGridCount++)
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

#if 0
		printf("DrawCube = %i", (2 * 6) * 3);
#endif
		}
}

void VoxelGridManager::DrawPoints(void)
{
	//float f_X, float f_Y, float f_Z, float f_Red, float f_Green, float f_Blue, float f_Alpha, unsigned int f_Bitmap, float f_Scale
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    
    if(mProgram == 0)
        return;

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

    MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(mWindowWidth) / float(mWindowHeight));
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

	//glEnable(GL_TEXTURE);
	//glBindTexture(GL_TEXTURE_2D, f_Bitmap);
	//glUniform1i(mTextureUniformLocation, 0);

    // Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, 0);
}

#if 0
void VoxelGridManager::ExplodeSphere(BiVector position, float radius)
{
	float startx = position.x - radius;
	float starty = position.y - radius;
	float startz = position.z - radius;
	float endx = position.x + radius;
	float endy = position.y + radius;
	float endz = position.z + radius;

	VoxelGridList vVoxelGridBatchUpdateList;

	for (float x = startx; x < endx; x += VoxelGrid::BLOCK_RENDER_SIZE)
	{
		for (float y = starty; y < endy; y += VoxelGrid::BLOCK_RENDER_SIZE)
		{
			for (float z = startz; z < endz; z += VoxelGrid::BLOCK_RENDER_SIZE)
			{
				vec3 blockPosition;
				int blockX, blockY, blockZ;
				VoxelGrid* pVoxelGrid = NULL;
				bool active = GetBlockActiveFrom3DPosition(x, y, z, &blockPosition, &blockX, &blockY, &blockZ, &pVoxelGrid);

				float distance = length(blockPosition - position);

				if (pVoxelGrid != NULL)
				{
					if (distance <= radius)
					{
						if (active)
						{
							float r;
							float g;
							float b;
							float a;
							// Store the colour for particle effect later
							pVoxelGrid->GetColour(blockX, blockY, blockZ, &r, &g, &b, &a);

							// Remove the block from being active
							pVoxelGrid->SetColour(blockX, blockY, blockZ, 0);

							// Create particle effect
							if (GetRandomNumber(0, 100, 2) > 75.0f)
							{
								CreateBlockDestroyParticleEffect(r, g, b, a, blockPosition);
							}

							// Create the collectible block item
							if (GetRandomNumber(0, 100, 2) > 75.0f)
							{
								BlockType blockType = pVoxelGrid->GetBlockType(blockX, blockY, blockZ);
								CreateCollectibleBlock(blockType, blockPosition);
							}

							// Add to batch update list (no duplicates)
							bool found = false;
							for (int i = 0; i < (int)vVoxelGridBatchUpdateList.size() && found == false; i++)
							{
								if (vVoxelGridBatchUpdateList[i] == pVoxelGrid)
								{
									found = true;
								}
							}
							if (found == false)
							{
								vVoxelGridBatchUpdateList.push_back(pVoxelGrid);
								pVoxelGrid->StartBatchUpdate();
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < (int)vVoxelGridBatchUpdateList.size(); i++)
	{
		vVoxelGridBatchUpdateList[i]->StopBatchUpdate();
	}
	vVoxelGridBatchUpdateList.clear();
}
#endif

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
}

BiVector VoxelGrid::GetPosition(void)
{
	return m_position;
}

// VoxelGrid Creation
void VoxelGridManager::CreateNewVoxelGrid(int x, int y, int z)
{
	VoxelGridCoordKeys* coordKeys = new VoxelGridCoordKeys();
	coordKeys->x = x;
	coordKeys->y = y;
	coordKeys->z = z;

	// Create a new VoxelGrid at this grid position
	VoxelGrid* pNewVoxelGrid = new VoxelGrid(m_VoxelGridsVector.size());

	float xPos = x * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	float yPos = y * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	float zPos = z * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);

	pNewVoxelGrid->SetPosition(BiVector(xPos, yPos, zPos));
	pNewVoxelGrid->SetGrid(coordKeys->x, coordKeys->y, coordKeys->z);

	g_UpdatingMuti.lock();
	g_RenderVoxMuti.lock();

	m_VoxelGridsMap[*(coordKeys)] = pNewVoxelGrid;
	m_VoxelGridsVector.push_back(pNewVoxelGrid);
	m_coordKeysVector.push_back(coordKeys);

	g_RenderVoxMuti.unlock();
	g_UpdatingMuti.unlock();

	pNewVoxelGrid->Setup();
	pNewVoxelGrid->SetNeedsRebuild(true, true);

#if 0
	glGenBuffers(1, &pNewVoxelGrid->mVertexPositionBuffer);
	glGenBuffers(1, &pNewVoxelGrid->mVertexNormalBuffer);
	glGenBuffers(1, &pNewVoxelGrid->mVertexColorBuffer);
	glGenBuffers(1, &pNewVoxelGrid->mVertexTexCoordBuffer);
	glGenBuffers(1, &pNewVoxelGrid->mIndexBuffer);
#endif

#if 0
	pNewVoxelGrid->RebuildMesh();
	pNewVoxelGrid->CompleteMesh();
	pNewVoxelGrid->SetCreated(true);
#endif

#if 0
	UpdateVoxelGridNeighbours(pNewVoxelGrid, x, y, z);
#endif
}

void VoxelGridManager::acFullRebuild(void)
{
	for(int f_Helly = 0; f_Helly < g_VoxelGridManager->m_VoxelGridsVector.size(); f_Helly++)
		{
		VoxelGrid* f_Grid = g_VoxelGridManager->m_VoxelGridsVector[f_Helly];

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
		for(int f_Cnt = 0; f_Cnt < g_VoxelGridManager->m_vec_Building.size(); f_Cnt++)
			{
			Building* f_Building = g_VoxelGridManager->m_vec_Building[f_Cnt];

			if (g_VoxelGridManager->Make_Place_Rand_Small_Building(f_Building->m_Pos, f_Building->m_Width, f_Building->m_Length, f_Building->m_Height, f_Grid->m_position, f_Grid))
				{
				f_Grid->SetNeedsRebuild(true, true);
				}
			}
		}
}

VoxelGrid* VoxelGridManager::GetVoxelGrid(int aX, int aY, int aZ)
{
	VoxelGridCoordKeys VoxelGridKey;
	VoxelGridKey.x = aX;
	VoxelGridKey.y = aY;
	VoxelGridKey.z = aZ;

	//g_VoxMuti.ac_Fire();

	map<VoxelGridCoordKeys, VoxelGrid*>::iterator it = m_VoxelGridsMap.find(VoxelGridKey);
	if(it != m_VoxelGridsMap.end())
		{
		VoxelGrid* lpReturn = m_VoxelGridsMap[VoxelGridKey];

		//g_VoxMuti.ac_Free();

		return lpReturn;
		}

	//g_VoxMuti.ac_Free();

	return nullptr;
}

// VoxelGrid Creation
void VoxelGridManager::CreatePlayerVoxelGrid(BiVector f_Position, int f_Player, float f_Scale)
{
	g_Player = f_Player;
	
	// Create a new VoxelGrid at this grid position
	VoxelGrid* pNewVoxelGrid = new VoxelGrid();

	pNewVoxelGrid->SetPosition(f_Position);
	pNewVoxelGrid->Setup();
	pNewVoxelGrid->SetNeedsRebuild(false, true);
	pNewVoxelGrid->RebuildMesh(f_Scale);
	pNewVoxelGrid->CompleteMesh();
	pNewVoxelGrid->SetCreated(true);

	m_playerVoxelGrid[g_Player] = pNewVoxelGrid;
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

VoxelGrid* VoxelGrid::GetxMinus()
{
	return m_CkXSub;
}

VoxelGrid* VoxelGrid::GetxPlus()
{
	return m_CkXAdd;
}

VoxelGrid* VoxelGrid::GetyMinus()
{
	return m_CkYSub;
}

VoxelGrid* VoxelGrid::GetyPlus()
{
	return m_CkYAdd;
}

VoxelGrid* VoxelGrid::GetzMinus()
{
	return m_CkZSub;
}

VoxelGrid* VoxelGrid::GetzPlus()
{
	return m_CkZAdd;
}

void VoxelGrid::SetxMinus(VoxelGrid* pVoxelGrid)
{
	m_CkXSub = pVoxelGrid;
}

void VoxelGrid::SetxPlus(VoxelGrid* pVoxelGrid)
{
	m_CkXAdd = pVoxelGrid;
}

void VoxelGrid::SetyMinus(VoxelGrid* pVoxelGrid)
{
	m_CkYSub = pVoxelGrid;
}

void VoxelGrid::SetyPlus(VoxelGrid* pVoxelGrid)
{
	m_CkYAdd = pVoxelGrid;
}

void VoxelGrid::SetzMinus(VoxelGrid* pVoxelGrid)
{
	m_CkZSub = pVoxelGrid;
}

void VoxelGrid::SetzPlus(VoxelGrid* pVoxelGrid)
{
	m_CkZAdd = pVoxelGrid;
}

bool VoxelGrid::CollidePointHeight(BiVector f_Point, int f_x, int f_y, int f_z, int* f_ResX, int* f_ResY, int* f_ResZ)
{
	bool f_Collide = false;
	if(f_Point.m_X >= (f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_X < ((f_x + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Y >= (f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Y < ((f_y + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Z >= (f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) &&
		f_Point.m_Z < ((f_z + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))))
		{
		for(int x = 0; x < VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VOXEL_GRID_SIZE; z++)
					{
					if(GetActive(x, y, z))
						{
						if((f_Point.m_X > ((f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((x * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_X < ((f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((x + 1) * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y > ((f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((y * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y < ((f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((y + 1) * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z > ((f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((z * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z < ((f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((z + 1) * (BLOCK_RENDER_SIZE * 2.0f))))))
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
	if((f_Point.m_X >= (f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_X < ((f_x + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y >= (f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y < ((f_y + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z >= (f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z < ((f_z + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))))
		{
		for(int x = 0; x < VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VOXEL_GRID_SIZE; z++)
					{
					if(GetActive(x, y, z))
						{
						if((f_Point.m_X >= ((f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((x * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_X < ((f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((x + 1) * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y >= ((f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((y * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Y < ((f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((y + 1) * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z >= ((f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((z * (BLOCK_RENDER_SIZE * 2.0f))))) &&
							(f_Point.m_Z < ((f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((z + 1) * (BLOCK_RENDER_SIZE * 2.0f))))))
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

bool VoxelGrid::CollideMarchPoint(BiVector f_Front, BiVector f_Rear, int f_x, int f_y, int f_z, BiVector* f_ImpactPoint)
{
	Cube::BiVector f_DefVec = f_Front - f_Rear;

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

	Cube::BiVector f_Vec1 = f_Rear;

	bool f_Collide = false;

	while(f_DefaultVecLength > 0.0f && f_Collide == false)
		{
		if((f_Vec1.m_X >= ((float)f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_X < (((float)f_x + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Y >= ((float)f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Y < (((float)f_y + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Z >= ((float)f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
			(f_Vec1.m_Z < (((float)f_z + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))))
			{
#if 0
			printf("block! f_Vec1 %f %f %f f_DefaultVecLength %f\n", f_Vec1.m_X, f_Vec1.m_Y, f_Vec1.m_Z, f_DefaultVecLength);
#endif
			for(int x = 0; x < VOXEL_GRID_SIZE; x++)
				{
				for(int y = 0; y < VOXEL_GRID_SIZE; y++)
					{
					for(int z = 0; z < VOXEL_GRID_SIZE; z++)
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
								while(fm_Vec2Length > 0.0f && f_Collide == false)
									{
									if((f_Vec2.m_X >= (((float)f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((float)x * (BLOCK_RENDER_SIZE * 2.0f))))) &&
										(f_Vec2.m_X < (((float)f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((((float)x + 1) * (BLOCK_RENDER_SIZE * 2.0f))))) &&
										(f_Vec2.m_Y >= (((float)f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((float)y * (BLOCK_RENDER_SIZE * 2.0f))))) &&
										(f_Vec2.m_Y < (((float)f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((((float)y + 1) * (BLOCK_RENDER_SIZE * 2.0f))))) &&
										(f_Vec2.m_Z >= (((float)f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((float)z * (BLOCK_RENDER_SIZE * 2.0f))))) &&
										(f_Vec2.m_Z < (((float)f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((((float)z + 1) * (BLOCK_RENDER_SIZE * 2.0f))))))
										{
#if 0
										printf("COLLIDE! f_Vec1 %f %f %f\n", f_Vec1.m_X, f_Vec1.m_Y, f_Vec1.m_Z);
										printf("########################## >= %f < %f\n", (((float)f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((float)x * (BLOCK_RENDER_SIZE * 2.0f)))), (((float)f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((((float)x + 1) * (BLOCK_RENDER_SIZE * 2.0f)))));
										printf("########################## >= %f < %f\n", (((float)f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((float)y * (BLOCK_RENDER_SIZE * 2.0f)))), (((float)f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((((float)y + 1) * (BLOCK_RENDER_SIZE * 2.0f)))));
										printf("########################## >= %f < %f\n", (((float)f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + (((float)z * (BLOCK_RENDER_SIZE * 2.0f)))), (((float)f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f))) + ((((float)z + 1) * (BLOCK_RENDER_SIZE * 2.0f)))));
#endif
										f_Collide = true;
										*(f_ImpactPoint) = f_Vec2;

										SetColour(x, y, z, 1.0f, 0.5, 0.8, 1.0f);
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

		f_Vec1.m_X += (MotionVec.x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE)));
		f_Vec1.m_Y += (MotionVec.y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE)));
		f_Vec1.m_Z += (MotionVec.z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE)));

		f_DefaultVecLength -= (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE));

		if(f_DefaultVecLength < 0.0f)
			{
			f_Vec1 = f_Front;
			}
		}

	return f_Collide;
}

int VoxelGridManager::acSearch_WithHash(std::string f_Hash, bool f_MeshOnly)
{
	for(int f_Int = 0; f_Int < m_VoxelGridsVector.size(); f_Int++)
		{
		VoxelGrid* f_Grid = m_VoxelGridsVector[f_Int];

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

bool VoxelGridManager::Make_Gen_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid)
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

bool VoxelGridManager::Make_Place_Rand_Small_Building(BiVector f_FloorCenter, int vWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid)
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

bool VoxelGridManager::Make_Gen_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid)
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

#if 0
	printf("MAKE Build x %i y %i z %i\n", x, y, z);
#endif

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

bool VoxelGridManager::Make_Place_Building(uint8 f_BuildingType, BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid)
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

#if 0
	printf("MAKE Build x %i y %i z %i\n", x, y, z);
#endif

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
	float f_grs_Z = f_Position.m_Z;

	if(f_grs_X > 10000)
		{
		f_grs_X = 10000;
		}

	if(f_grs_X < -10000)
		{
		f_grs_X = -10000;
		}

	if(f_grs_Y > 10000)
		{
		f_grs_Y = 10000;
		}

	if(f_grs_Y < -10000)
		{
		f_grs_Y = -10000;
		}

	if(f_grs_Z > 10000)
		{
		f_grs_Z = 10000;
		}

	if(f_grs_Z < -10000)
		{
		f_grs_Z = -10000;
		}

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

#if 0
	printf("Start X %i Y %i Z %i\n", f_Xsgrid - LOAD_DISTANCE, 0, f_Zsgrid - LOAD_DISTANCE);
	printf("End X %i Y %i Z %i\n", f_Xsgrid + LOAD_DISTANCE, 0, f_Zsgrid + LOAD_DISTANCE);
#endif

	for(int f_Steam = 0; f_Steam < m_vec_VX.size(); f_Steam++)
		{
		m_vec_VX[f_Steam]->f_Renderon = false;
		}

#if 1
	for(int f_X = f_Xsgrid - LOAD_DISTANCE; f_X < f_Xsgrid + LOAD_DISTANCE; f_X++)
		{
		for(int f_Y = f_Ysgrid - LOAD_DISTANCE; f_Y < f_Ysgrid + LOAD_DISTANCE; f_Y++)
			{
			for(int f_Z = f_Zsgrid - LOAD_DISTANCE; f_Z < f_Zsgrid + LOAD_DISTANCE; f_Z++)
				{
				bool f_Found = false;
				bool f_OK = false;
				int f_Index = 0;
				for(int f_Fog = 0; f_Fog < m_vec_VX.size(); f_Fog++)
					{
					VX* f_VX = m_vec_VX[f_Fog];

					if((f_VX->m_X == f_X) &&
						(f_VX->m_Y == f_Y) &&
						(f_VX->m_Z == f_Z))
						{
						f_Found = true;
						f_Index = f_Fog;
						if(f_VX->m_State == VOXEL_STATE_OK)
							{
							f_OK = true;
							}

						f_VX->f_Renderon = true;
						}
					}

				if(f_Found == false)
					{
					CreateNewVoxelGrid(f_X, f_Y, f_Z);
					VoxelGrid* f_VoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);
					BiVector f_VoxelPosition(((float)f_X * GRID_RENDER) + (0.5f * GRID_RENDER), ((float)f_Y * GRID_RENDER) + (0.5f * GRID_RENDER), ((float)f_Z * GRID_RENDER) + (0.5f * GRID_RENDER));

#if 0
					for(int f_Cnt = 0; f_Cnt < g_VoxelGridManager->m_vec_Building.size(); f_Cnt++)
						{
						Building* f_Building = g_VoxelGridManager->m_vec_Building[f_Cnt];

						g_VoxelGridManager->Make_Gen_Rand_Small_Building(f_Building->m_Pos, f_Building->m_Width, f_Building->m_Length, f_Building->m_Height, f_VoxelPosition, f_VoxelGrid);
						}

#if 0
#if 0
					f_VoxelGrid->Setup();
#endif
					f_VoxelGrid->RebuildMesh();
					f_VoxelGrid->CompleteMesh();
					f_VoxelGrid->SetCreated(true);
#endif
#endif

					f_VoxelGrid->m_VX = new VX;
					f_VoxelGrid->m_VX->m_X = f_X;
					f_VoxelGrid->m_VX->m_Y = f_Y;
					f_VoxelGrid->m_VX->m_Z = f_Z;
					f_VoxelGrid->m_VX->m_State = VOXEL_STATE_OK;
					f_VoxelGrid->m_VX->f_Renderon = true;
					m_vec_VX.push_back(f_VoxelGrid->m_VX);
					f_Alter = true;
					}
				else
					{
					if(f_Found == true &&
						f_OK == false)
						{
						  ////////////
						 // reLoad
						//
						CreateNewVoxelGrid(f_X, f_Y, f_Z);
						VoxelGrid* f_VoxelGrid = GetVoxelGrid(f_X, f_Y, f_Z);

#if 0
						BiVector f_VoxelPosition(((float)f_X * GRID_RENDER) + (0.5f * GRID_RENDER), ((float)f_Y * GRID_RENDER) + (0.5f * GRID_RENDER), ((float)f_Z * GRID_RENDER) + (0.5f * GRID_RENDER));

						for(int f_Cnt = 0; f_Cnt < g_VoxelGridManager->m_vec_Building.size(); f_Cnt++)
							{
							Building* f_Building = g_VoxelGridManager->m_vec_Building[f_Cnt];

							g_VoxelGridManager->Make_Gen_Rand_Small_Building(f_Building->m_Pos, f_Building->m_Width, f_Building->m_Length, f_Building->m_Height, f_VoxelPosition, f_VoxelGrid);
							}
#endif

#if 0
#if 0
						f_VoxelGrid->Setup();
#endif
						f_VoxelGrid->RebuildMesh();
						f_VoxelGrid->CompleteMesh();
						f_VoxelGrid->SetCreated(true);
#endif

						f_VoxelGrid->m_VX = m_vec_VX[f_Index];
						f_VoxelGrid->m_VX->m_X = f_X;
						f_VoxelGrid->m_VX->m_Y = f_Y;
						f_VoxelGrid->m_VX->m_Z = f_Z;
						f_VoxelGrid->m_VX->m_State = VOXEL_STATE_OK;
						f_VoxelGrid->m_VX->f_Renderon = true;
						f_Alter = true;
						}
					}
				}
			}
		}

	if(f_Alter)
		{
		}
#endif
}

bool VoxelGridManager::Make_Gen_IntWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid)
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

bool VoxelGridManager::Make_Gen_ExtWall(BiVector f_FloorCenter, int VWidth, int vLength, int vHeight, BiVector f_Position, VoxelGrid* f_VoxelGrid)
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
	if((f_Point.m_X >= (f_x * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_X < ((f_x + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y >= (f_y * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Y < ((f_y + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z >= (f_z * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))) &&
		(f_Point.m_Z < ((f_z + 1) * (VOXEL_GRID_SIZE * (BLOCK_RENDER_SIZE * 2.0f)))))
		{
		  //////////////////
		 // Inside VX
		//
		for(int x = 0; x < VOXEL_GRID_SIZE; x++)
			{
			for(int y = 0; y < VOXEL_GRID_SIZE; y++)
				{
				for(int z = 0; z < VOXEL_GRID_SIZE; z++)
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
						   /////////
						  // Dam
						 //
						if(f_ForceFac <= f_Radius)
							{
							f_PowerFac *= 1.0f - (f_ForceFac / f_Radius);
							f_Collide = true;

							float f_Strength = GetStrength(x, y, z);
							f_Strength -= f_PowerFac;

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
						}
					}
				}
			}
		}

	if(f_Rebuild)
		{
#if 0
		Setup();
#endif
		g_UpdatingMuti.lock();

		RebuildMesh();
		CompleteMesh();
		SetCreated(true);

		g_UpdatingMuti.unlock();
		}

	return f_Collide;
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

void VoxelGridManager::UpdateVoxelGridNeighbours(VoxelGrid* pVoxelGrid, int x, int y, int z)
{
#if 0
	pVoxelGrid->SetNumNeighbours(0);

	VoxelGrid* pVoxelGridXMinus = GetVoxelGrid(x - 1, y, z);
	VoxelGrid* pVoxelGridXPlus = GetVoxelGrid(x + 1, y, z);
	VoxelGrid* pVoxelGridYMinus = GetVoxelGrid(x, y - 1, z);
	VoxelGrid* pVoxelGridYPlus = GetVoxelGrid(x, y + 1, z);
	VoxelGrid* pVoxelGridZMinus = GetVoxelGrid(x, y, z - 1);
	VoxelGrid* pVoxelGridZPlus = GetVoxelGrid(x, y, z + 1);

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
	VoxelGrid* f_XPlus = GetVoxelGrid(x + 1, y, z);
	VoxelGrid* f_XMinus = GetVoxelGrid(x - 1, y, z);
	VoxelGrid* f_YPlus = GetVoxelGrid(x, y + 1, z);
	VoxelGrid* f_YMinus = GetVoxelGrid(x, y - 1, z);
	VoxelGrid* f_ZPlus = GetVoxelGrid(x, y, z + 1);
	VoxelGrid* f_ZMinus = GetVoxelGrid(x, y, z - 1);

	if(f_XPlus) f_XPlus->SetNeedsRebuild(true, true);
	if(f_XMinus) f_XMinus->SetNeedsRebuild(true, true);
	if(f_YPlus) f_YPlus->SetNeedsRebuild(true, true);
	if(f_YMinus) f_YMinus->SetNeedsRebuild(true, true);
	if(f_ZPlus) f_ZPlus->SetNeedsRebuild(true, true);
	if(f_ZMinus) f_ZMinus->SetNeedsRebuild(true, true);
#endif
}

};