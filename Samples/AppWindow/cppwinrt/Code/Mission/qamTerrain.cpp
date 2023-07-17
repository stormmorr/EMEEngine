/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "qamTerrain.h"

using namespace Cube;
using namespace ecoin;

namespace ecoin
{

qamTerrain::qamTerrain(int f_ID) : qamType(qamTYPE_Terrain)
{
	std::string f_ref_CurrentPath = "qamTerrain::qamTerrain";

	acClear();
	m_ID = f_ID;

	//Build the query
	char* f_eventquery = new char[512];
	sprintf(f_eventquery, "SELECT id, x, y, z, xrot, yrot, zrot, g_TerrainInsertFillX, g_TerrainInsertFillY, g_TerrainInsertFillZ, g_TerrainInsertMoveX, g_TerrainInsertMoveY, g_TerrainInsertMoveZ, g_TerrainInsertNegatedX, g_TerrainInsertNegatedY, g_TerrainInsertNegatedZ, g_TerrainInsertMaxX, g_TerrainInsertMaxY, g_TerrainInsertMaxZ, qmaterialid, shape, qorder, qtype, qrepeat, qamlevel, qamid, namegroup FROM qamterrain WHERE id = %i", f_ID);

	mutex_qcomdb.lock();

	g_SafeL[2]->acSelectCommand(f_eventquery, false, false);
	delete[] f_eventquery;

	if(g_Schedular[2]->acEntrySize())
		{
		m_X = atof(g_Schedular[2]->acEntry(0)[1].c_str());
		m_Y = atof(g_Schedular[2]->acEntry(0)[2].c_str());
		m_Z = atof(g_Schedular[2]->acEntry(0)[3].c_str());

		m_Xrot = atof(g_Schedular[2]->acEntry(0)[4].c_str());
		m_Yrot = atof(g_Schedular[2]->acEntry(0)[5].c_str());
		m_Zrot = atof(g_Schedular[2]->acEntry(0)[6].c_str());

		m_TerrainInsertFillX = ::atoi(g_Schedular[2]->acEntry(0)[7].c_str());
		m_TerrainInsertFillY = ::atoi(g_Schedular[2]->acEntry(0)[8].c_str());
		m_TerrainInsertFillZ = ::atoi(g_Schedular[2]->acEntry(0)[9].c_str());
		m_TerrainInsertMoveX = ::atoi(g_Schedular[2]->acEntry(0)[10].c_str());
		m_TerrainInsertMoveY = ::atoi(g_Schedular[2]->acEntry(0)[11].c_str());
		m_TerrainInsertMoveZ = ::atoi(g_Schedular[2]->acEntry(0)[12].c_str());
		m_TerrainInsertNegatedX = ::atoi(g_Schedular[2]->acEntry(0)[13].c_str());
		m_TerrainInsertNegatedY = ::atoi(g_Schedular[2]->acEntry(0)[14].c_str());
		m_TerrainInsertNegatedZ = ::atoi(g_Schedular[2]->acEntry(0)[15].c_str());
		m_TerrainInsertMaxX = ::atoi(g_Schedular[2]->acEntry(0)[16].c_str());
		m_TerrainInsertMaxY = ::atoi(g_Schedular[2]->acEntry(0)[17].c_str());
		m_TerrainInsertMaxZ = ::atoi(g_Schedular[2]->acEntry(0)[18].c_str());
			
		m_materialid = ::atoi(g_Schedular[2]->acEntry(0)[19].c_str());
		m_DefaultShape = ::atoi(g_Schedular[2]->acEntry(0)[20].c_str());
		m_Order = ::atoi(g_Schedular[2]->acEntry(0)[21].c_str());
		m_Type = ::atoi(g_Schedular[2]->acEntry(0)[22].c_str());
		m_Repeat = ::atoi(g_Schedular[2]->acEntry(0)[23].c_str());

		m_QamLevel = ::atoi(g_Schedular[2]->acEntry(0)[24].c_str());
		m_QamID = ::atoi(g_Schedular[2]->acEntry(0)[25].c_str());
		m_NameGroup = g_Schedular[2]->acEntry(0)[26];
		}

	mutex_qcomdb.unlock();
}

void qamTerrain::ac_Compute(void)
{

}

void qamTerrain::ac_Save(void)
{
	std::string f_ref_CurrentPath = "qamTerrain::ac_Save";

	if(m_ID == -1551)
		{
		//g_VoxMuti.ac_Fire();

		char* f_terrainfield[26];
		char* f_terrainvalue[26];

		for(int f_Count = 0; f_Count < 26; f_Count++)
			{
			f_terrainfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_terrainvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_terrainfield[0], "x");
		sprintf(f_terrainfield[1], "y");
		sprintf(f_terrainfield[2], "z");
		sprintf(f_terrainfield[3], "xrot");
		sprintf(f_terrainfield[4], "yrot");
		sprintf(f_terrainfield[5], "zrot");
		sprintf(f_terrainfield[6], "g_TerrainInsertFillX");
		sprintf(f_terrainfield[7], "g_TerrainInsertFillY");
		sprintf(f_terrainfield[8], "g_TerrainInsertFillZ");
		sprintf(f_terrainfield[9], "g_TerrainInsertMoveX");
		sprintf(f_terrainfield[10], "g_TerrainInsertMoveY");
		sprintf(f_terrainfield[11], "g_TerrainInsertMoveZ");
		sprintf(f_terrainfield[12], "g_TerrainInsertNegatedX");
		sprintf(f_terrainfield[13], "g_TerrainInsertNegatedY");
		sprintf(f_terrainfield[14], "g_TerrainInsertNegatedZ");
		sprintf(f_terrainfield[15], "g_TerrainInsertMaxX");
		sprintf(f_terrainfield[16], "g_TerrainInsertMaxY");
		sprintf(f_terrainfield[17], "g_TerrainInsertMaxZ");
		sprintf(f_terrainfield[18], "shape");
		sprintf(f_terrainfield[19], "qmaterialid");
		sprintf(f_terrainfield[20], "qorder");
		sprintf(f_terrainfield[21], "qtype");
		sprintf(f_terrainfield[22], "qrepeat");
		sprintf(f_terrainfield[23], "qamlevel");
		sprintf(f_terrainfield[24], "qamid");
		sprintf(f_terrainfield[25], "namegroup");

		sprintf(f_terrainvalue[0], "%f", m_X);
		sprintf(f_terrainvalue[1], "%f", m_Y);
		sprintf(f_terrainvalue[2], "%f", m_Z);
		sprintf(f_terrainvalue[3], "%f", m_Xrot);
		sprintf(f_terrainvalue[4], "%f", m_Yrot);
		sprintf(f_terrainvalue[5], "%f", m_Zrot);
		sprintf(f_terrainvalue[6], "%i", m_TerrainInsertFillX);
		sprintf(f_terrainvalue[7], "%i", m_TerrainInsertFillY);
		sprintf(f_terrainvalue[8], "%i", m_TerrainInsertFillZ);
		sprintf(f_terrainvalue[9], "%i", m_TerrainInsertMoveX);
		sprintf(f_terrainvalue[10], "%i", m_TerrainInsertMoveY);
		sprintf(f_terrainvalue[11], "%i", m_TerrainInsertMoveZ);
		sprintf(f_terrainvalue[12], "%i", m_TerrainInsertNegatedX);
		sprintf(f_terrainvalue[13], "%i", m_TerrainInsertNegatedY);
		sprintf(f_terrainvalue[14], "%i", m_TerrainInsertNegatedZ);
		sprintf(f_terrainvalue[15], "%i", m_TerrainInsertMaxX);
		sprintf(f_terrainvalue[16], "%i", m_TerrainInsertMaxY);
		sprintf(f_terrainvalue[17], "%i", m_TerrainInsertMaxZ);
		sprintf(f_terrainvalue[18], "%i", m_DefaultShape);
		sprintf(f_terrainvalue[19], "%i", m_materialid);
		sprintf(f_terrainvalue[20], "%i", m_Order);
		sprintf(f_terrainvalue[21], "%i", m_Type);
		sprintf(f_terrainvalue[22], "%i", m_Repeat);
		sprintf(f_terrainvalue[23], "%i", m_QamLevel);
		sprintf(f_terrainvalue[24], "%i", m_QamID);
		sprintf(f_terrainvalue[25], "%s", m_NameGroup.c_str());

		int f_TerrainUniqueID = g_SafeL[2]->Insert("qamterrain", (const char **)f_terrainfield, (const char **)f_terrainvalue, 26, false, false);

		m_ID = f_TerrainUniqueID;

		//g_VoxMuti.ac_Free();
		}
	else
		{
		if(m_Save)
			{
			char* f_terrainfield[26];
			char* f_terrainvalue[26];
			char* f_terrainwhere[1];

			for (int f_Count = 0; f_Count < 26; f_Count++)
				{
				f_terrainfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_terrainvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_terrainwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_terrainfield[0], "x");
			sprintf(f_terrainfield[1], "y");
			sprintf(f_terrainfield[2], "z");
			sprintf(f_terrainfield[3], "xrot");
			sprintf(f_terrainfield[4], "yrot");
			sprintf(f_terrainfield[5], "zrot");
			sprintf(f_terrainfield[6], "g_TerrainInsertFillX");
			sprintf(f_terrainfield[7], "g_TerrainInsertFillY");
			sprintf(f_terrainfield[8], "g_TerrainInsertFillZ");
			sprintf(f_terrainfield[9], "g_TerrainInsertMoveX");
			sprintf(f_terrainfield[10], "g_TerrainInsertMoveY");
			sprintf(f_terrainfield[11], "g_TerrainInsertMoveZ");
			sprintf(f_terrainfield[12], "g_TerrainInsertNegatedX");
			sprintf(f_terrainfield[13], "g_TerrainInsertNegatedY");
			sprintf(f_terrainfield[14], "g_TerrainInsertNegatedZ");
			sprintf(f_terrainfield[15], "g_TerrainInsertMaxX");
			sprintf(f_terrainfield[16], "g_TerrainInsertMaxY");
			sprintf(f_terrainfield[17], "g_TerrainInsertMaxZ");
			sprintf(f_terrainfield[18], "materialid");
			sprintf(f_terrainfield[19], "shape");
			sprintf(f_terrainfield[20], "order");
			sprintf(f_terrainfield[21], "type");
			sprintf(f_terrainfield[22], "repeat");
			sprintf(f_terrainfield[23], "qamlevel");
			sprintf(f_terrainfield[24], "qamid");
			sprintf(f_terrainfield[25], "namegroup");

			sprintf(f_terrainvalue[0], "%f", m_X);
			sprintf(f_terrainvalue[1], "%f", m_Y);
			sprintf(f_terrainvalue[2], "%f", m_Z);
			sprintf(f_terrainvalue[3], "%f", m_Xrot);
			sprintf(f_terrainvalue[4], "%f", m_Yrot);
			sprintf(f_terrainvalue[5], "%f", m_Zrot);
			sprintf(f_terrainvalue[6], "%i", m_TerrainInsertFillX);
			sprintf(f_terrainvalue[7], "%i", m_TerrainInsertFillY);
			sprintf(f_terrainvalue[8], "%i", m_TerrainInsertFillZ);
			sprintf(f_terrainvalue[9], "%i", m_TerrainInsertMoveX);
			sprintf(f_terrainvalue[10], "%i", m_TerrainInsertMoveY);
			sprintf(f_terrainvalue[11], "%i", m_TerrainInsertMoveZ);
			sprintf(f_terrainvalue[12], "%i", m_TerrainInsertNegatedX);
			sprintf(f_terrainvalue[13], "%i", m_TerrainInsertNegatedY);
			sprintf(f_terrainvalue[14], "%i", m_TerrainInsertNegatedZ);
			sprintf(f_terrainvalue[15], "%i", m_TerrainInsertMaxX);
			sprintf(f_terrainvalue[16], "%i", m_TerrainInsertMaxY);
			sprintf(f_terrainvalue[17], "%i", m_TerrainInsertMaxZ);
			sprintf(f_terrainvalue[18], "%i", m_materialid);
			sprintf(f_terrainvalue[19], "%i", m_DefaultShape);
			sprintf(f_terrainvalue[20], "%i", m_Order);
			sprintf(f_terrainvalue[21], "%i", m_Type);
			sprintf(f_terrainvalue[22], "%i", m_Repeat);
			sprintf(f_terrainvalue[23], "%i", m_QamLevel);
			sprintf(f_terrainvalue[24], "%i", m_QamID);
			sprintf(f_terrainvalue[25], "%s", m_NameGroup.c_str());

			sprintf(f_terrainwhere[0], "id = %i", m_ID);

			//g_VoxMuti.ac_Fire();

			g_SafeL[2]->Update("qamterrain", (const char **)f_terrainfield, (const char **)f_terrainvalue, 26, f_terrainwhere[0], false, false);

			//g_VoxMuti.ac_Free();

			m_Save = false;
			}
		}
}

void qamTerrain::acVoxprint(std::shared_ptr<VoxelGrid> f_Grid)
{
	const float BLOCK_RENDER = (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_SIZE = (Cube::VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	if(g_GameOpen)
		{
		BiVector f_Pos;

		for(int f_moveX = 1; f_moveX < (m_TerrainInsertMaxX + 1); f_moveX += m_TerrainInsertMoveX)
			{
			for(int f_moveY = 1; f_moveY < (m_TerrainInsertMaxY + 1); f_moveY += m_TerrainInsertMoveY)
				{
				for(int f_moveZ = 1; f_moveZ < (m_TerrainInsertMaxZ + 1); f_moveZ += m_TerrainInsertMoveZ)
					{
					for(int f_fillX = 1; f_fillX < (m_TerrainInsertFillX + 1); f_fillX++)
						{
						for(int f_fillY = 1; f_fillY < (m_TerrainInsertFillY + 1); f_fillY++)
							{
							for(int f_fillZ = 1; f_fillZ < (m_TerrainInsertFillZ + 1); f_fillZ++)
								{ ///////////////
								 // negated
								bool f_Negate = false;

								if((((m_TerrainInsertNegatedX > 0) && (f_fillX > m_TerrainInsertNegatedX)) || ((m_TerrainInsertNegatedX < 0) && (f_fillX < m_TerrainInsertFillX - (m_TerrainInsertNegatedX * -1)) || (m_TerrainInsertNegatedX == 0))) &&
								   (((m_TerrainInsertNegatedY > 0) && (f_fillY > m_TerrainInsertNegatedY)) || ((m_TerrainInsertNegatedY < 0) && (f_fillY < m_TerrainInsertFillY - (m_TerrainInsertNegatedY * -1)) || (m_TerrainInsertNegatedY == 0))) &&
								   (((m_TerrainInsertNegatedZ > 0) && (f_fillZ > m_TerrainInsertNegatedZ)) || ((m_TerrainInsertNegatedZ < 0) && (f_fillZ < m_TerrainInsertFillZ - (m_TerrainInsertNegatedZ * -1)) || (m_TerrainInsertNegatedZ == 0))))
									{
									f_Negate = false;
									}
								else
									{
									f_Negate = true;
									}

								  ///////////
								 // fpos
								//
								f_Pos.m_X = m_X + (((f_fillX * BLOCK_RENDER) * f_moveX));
								f_Pos.m_Y = m_Y + (((f_fillY * BLOCK_RENDER) * f_moveY));
								f_Pos.m_Z = (m_Z * -1.0f) + (((f_fillZ * BLOCK_RENDER) * f_moveZ));

								if( (f_Pos.m_X >= (f_Grid->m_gridX * GRID_SIZE)) &&
									(f_Pos.m_X < ((f_Grid->m_gridX + 1) * GRID_SIZE)) &&
									(f_Pos.m_Y >= (f_Grid->m_gridY * GRID_SIZE)) &&
									(f_Pos.m_Y < ((f_Grid->m_gridY + 1) * GRID_SIZE)) &&
									(f_Pos.m_Z >= ((f_Grid->m_gridZ * -1) * GRID_SIZE)) &&
									(f_Pos.m_Z < (((f_Grid->m_gridZ * -1) + 1) * GRID_SIZE)))
									{
									BiVector f_Point = f_Pos;

									  //////////////////
									 // Inside VX
									//
									for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
										{
										for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
											{
											for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
												{
												float f_TugX = (float)x + 0.5f;
												float f_TugY = (float)y + 0.5f;
												float f_TugZ = (float)z + 0.5f;
												float f_CentralX = (((f_Grid->m_gridX * GRID_SIZE) + ((f_TugX * BLOCK_RENDER))));
												float f_CentralY = (((f_Grid->m_gridY * GRID_SIZE) + ((f_TugY * BLOCK_RENDER))));
												float f_CentralZ = ((((f_Grid->m_gridZ * -1) * GRID_SIZE) + ((f_TugZ * BLOCK_RENDER))));
						
												BiVector f_Central(f_CentralX, f_CentralY, f_CentralZ);
												BiVector f_ForceVec = f_Central - f_Point;

												float f_ForceFac = f_ForceVec.acLength();

												  ///////////////////
												 // Sphere Test
												//
												if(f_ForceFac <= 15.5f)
													{
#if 0
													if(f_Grid->m_rebuild == 0)
														{
														int f_ManagerIndex = f_Grid->m_ManagerIndex;

														int gx = f_Grid->m_gridX;
														int gy = f_Grid->m_gridY;
														int gz = (f_Grid->m_gridZ * -1);

														VoxelGridCoordKeys* coordKeys = new VoxelGridCoordKeys();
														coordKeys->x = gx;
														coordKeys->y = gy;
														coordKeys->z = gz;

														// Create a new VoxelGrid at this grid position
														f_Grid = std::make_shared<VoxelGrid>(f_ManagerIndex);

														f_Grid->m_Self = f_Grid;

														float xPos = gx * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
														float yPos = gy * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
														float zPos = gz * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);

														f_Grid->SetPosition(BiVector(xPos, yPos, zPos));
														f_Grid->SetGrid(coordKeys->x, coordKeys->y, coordKeys->z);

														f_Grid->Setup();

														f_Grid->m_PlacedIn = true;
														f_Grid->m_PlacedInLast = true;
														}
#endif

													int f_X = x;
													int f_Y = y;
													int f_Z = z;

													if(f_Negate)
														{
														f_Grid->SetColour(f_X, f_Y, f_Z, 0.0f, 0.0f, 0.0f, 0.0f);
														f_Grid->SetStrength(f_X, f_Y, f_Z, 0.0f);
														}
													else
														{
														float red = 0.65f;
														float green = 0.80f;
														float blue = 0.00f;
														float alpha = 1.0f;
														BlockType blockType = Cube::BlockType::BlockType_Default;

														f_Grid->SetColour(f_X, f_Y, f_Z, red, green, blue, alpha);
														f_Grid->SetStrength(f_X, f_Y, f_Z, 0.0f);
														f_Grid->SetBlockType(f_X, f_Y, f_Z, blockType);
														}

													f_Grid->SetNeedsRebuild(true, true, true);
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

bool qamTerrain::Make_Place_Terrain(std::shared_ptr<VoxelGrid> f_Grid)
{
	const float BLOCK_RENDER = (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_SIZE = (Cube::VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

	if(g_GameOpen)
		{
		BiVector f_Pos;

#if 0
		//g_VoxMuti.ac_Fire();
#endif

		for(int f_moveX = 1; f_moveX < (m_TerrainInsertMaxX + 1); f_moveX += m_TerrainInsertMoveX)
			{
			for(int f_moveY = 1; f_moveY < (m_TerrainInsertMaxY + 1); f_moveY += m_TerrainInsertMoveY)
				{
				for(int f_moveZ = 1; f_moveZ < (m_TerrainInsertMaxZ + 1); f_moveZ += m_TerrainInsertMoveZ)
					{
					for(int f_fillX = 1; f_fillX < (m_TerrainInsertFillX + 1); f_fillX++)
						{
						for(int f_fillY = 1; f_fillY < (m_TerrainInsertFillY + 1); f_fillY++)
							{
							for(int f_fillZ = 1; f_fillZ < (m_TerrainInsertFillZ + 1); f_fillZ++)
								{
								  ///////////
								 // fpos
								//
								f_Pos.m_X = m_X + (((f_fillX * BLOCK_RENDER) * f_moveX));
								f_Pos.m_Y = m_Y + (((f_fillY * BLOCK_RENDER) * f_moveY));
								f_Pos.m_Z = (m_Z * -1.0f) + (((f_fillZ * BLOCK_RENDER) * f_moveZ));

								if( (f_Pos.m_X >= (f_Grid->m_gridX * GRID_SIZE)) &&
									(f_Pos.m_X < ((f_Grid->m_gridX + 1) * GRID_SIZE)) &&
									(f_Pos.m_Y >= (f_Grid->m_gridY * GRID_SIZE)) &&
									(f_Pos.m_Y < ((f_Grid->m_gridY + 1) * GRID_SIZE)) &&
									(f_Pos.m_Z >= ((f_Grid->m_gridZ * -1) * GRID_SIZE)) &&
									(f_Pos.m_Z < (((f_Grid->m_gridZ * -1) + 1) * GRID_SIZE)))
									{
									return true;
									}
								}
							}
						}
					}
				}
			}
	
#if 0
		//g_VoxMuti.ac_Free();
#endif
		}

	return false;
}

void qamTerrain::acVoxprint(int f_Grid)
{
	const float BLOCK_RENDER = (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_SIZE = (Cube::VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

#if 0
	if(g_GameOpen)
		{
		BiVector f_Pos;

#if 0
		//g_VoxMuti.ac_Fire();
#endif

		for(int f_moveX = 1; f_moveX < (m_TerrainInsertMaxX + 1); f_moveX += m_TerrainInsertMoveX)
			{
			for(int f_moveY = 1; f_moveY < (m_TerrainInsertMaxY + 1); f_moveY += m_TerrainInsertMoveY)
				{
				for(int f_moveZ = 1; f_moveZ < (m_TerrainInsertMaxZ + 1); f_moveZ += m_TerrainInsertMoveZ)
					{
					for(int f_fillX = 1; f_fillX < (m_TerrainInsertFillX + 1); f_fillX++)
						{
						for(int f_fillY = 1; f_fillY < (m_TerrainInsertFillY + 1); f_fillY++)
							{
							for(int f_fillZ = 1; f_fillZ < (m_TerrainInsertFillZ + 1); f_fillZ++)
								{ ///////////////
								 // negated
								bool f_Negate = false;

								if((((m_TerrainInsertNegatedX > 0) && (f_fillX > m_TerrainInsertNegatedX)) || ((m_TerrainInsertNegatedX < 0) && (f_fillX < m_TerrainInsertFillX - (m_TerrainInsertNegatedX * -1)) || (m_TerrainInsertNegatedX == 0))) &&
								   (((m_TerrainInsertNegatedY > 0) && (f_fillY > m_TerrainInsertNegatedY)) || ((m_TerrainInsertNegatedY < 0) && (f_fillY < m_TerrainInsertFillY - (m_TerrainInsertNegatedY * -1)) || (m_TerrainInsertNegatedY == 0))) &&
								   (((m_TerrainInsertNegatedZ > 0) && (f_fillZ > m_TerrainInsertNegatedZ)) || ((m_TerrainInsertNegatedZ < 0) && (f_fillZ < m_TerrainInsertFillZ - (m_TerrainInsertNegatedZ * -1)) || (m_TerrainInsertNegatedZ == 0))))
									{
									f_Negate = false;
									}
								else
									{
									f_Negate = true;
									}

								  ///////////
								 // fpos
								//
								f_Pos.m_X = m_X + (((f_fillX * BLOCK_RENDER) * f_moveX));
								f_Pos.m_Y = m_Y + (((f_fillY * BLOCK_RENDER) * f_moveY));
								f_Pos.m_Z = m_Z + (((f_fillZ * BLOCK_RENDER) * f_moveZ));

								if( (f_Pos.m_X >= (f_Grid->m_gridX * GRID_SIZE)) &&
									(f_Pos.m_X < ((f_Grid->m_gridX + 1) * GRID_SIZE)) &&
									(f_Pos.m_Y >= (f_Grid->m_gridY * GRID_SIZE)) &&
									(f_Pos.m_Y < ((f_Grid->m_gridY + 1) * GRID_SIZE)) &&
									(f_Pos.m_Z >= ((f_Grid->m_gridZ * -1) * GRID_SIZE)) &&
									(f_Pos.m_Z < (((f_Grid->m_gridZ * -1) + 1) * GRID_SIZE)))
									{
									BiVector f_Point(f_Pos.m_X, f_Pos.m_Y, f_Pos.m_Z);

										//////////////////
										// Inside VX
									//
									for(int x = 0; x < VoxelGrid::VOXEL_GRID_SIZE; x++)
										{
										for(int y = 0; y < VoxelGrid::VOXEL_GRID_SIZE; y++)
											{
											for(int z = 0; z < VoxelGrid::VOXEL_GRID_SIZE; z++)
												{
												float f_TugX = (float)x + 0.5f;
												float f_TugY = (float)y + 0.5f;
												float f_TugZ = (float)z + 0.5f;
												float f_CentralX = (((f_Grid->m_gridX * GRID_SIZE) + ((f_TugX * BLOCK_RENDER))));
												float f_CentralY = (((f_Grid->m_gridY * GRID_SIZE) + ((f_TugY * BLOCK_RENDER))));
												float f_CentralZ = ((((f_Grid->m_gridZ * -1) * GRID_SIZE) + ((f_TugZ * BLOCK_RENDER))));
						
												BiVector f_Central(f_CentralX, f_CentralY, f_CentralZ);
												BiVector f_ForceVec = f_Central - f_Point;

												float f_ForceFac = f_ForceVec.acLength();

													///////////////////
													// Sphere Test
													//
												if(f_ForceFac <= 15.5f)
													{
#if 0
													if(f_Grid->m_rebuild == 0)
														{
														int f_ManagerIndex = f_Grid->m_ManagerIndex;

														int x = f_Grid->m_gridX;
														int y = f_Grid->m_gridY;
														int z = (f_Grid->m_gridZ * -1);

														VoxelGridCoordKeys* coordKeys = new VoxelGridCoordKeys();
														coordKeys->x = x;
														coordKeys->y = y;
														coordKeys->z = z;

														// Create a new VoxelGrid at this grid position
														f_Grid = std::make_shared<VoxelGrid>(f_ManagerIndex);

														f_Grid->m_Self = f_Grid;

														float xPos = x * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
														float yPos = y * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
														float zPos = z * (VoxelGrid::VOXEL_GRID_SIZE * VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);

														f_Grid->SetPosition(BiVector(xPos, yPos, zPos));
														f_Grid->SetGrid(coordKeys->x, coordKeys->y, coordKeys->z);

														f_Grid->Setup();

														f_Grid->m_PlacedIn = true;
														f_Grid->m_PlacedInLast = true;
														}
#endif

													int f_X = x;
													int f_Y = y;
													int f_Z = z;

													if(f_Negate)
														{
														f_Grid->SetColour(f_X, f_Y, f_Z, 0.0f, 0.0f, 0.0f, 0.0f);
														f_Grid->SetStrength(f_X, f_Y, f_Z, 0.0f);
														}
													else
														{
														float red = 0.65f;
														float green = 0.80f;
														float blue = 0.00f;
														float alpha = 1.0f;
														BlockType blockType = BlockType_Default;

														f_Grid->SetColour(f_X, f_Y, f_Z, red, green, blue, alpha);
														f_Grid->SetStrength(f_X, f_Y, f_Z, 0.0f);
														f_Grid->SetBlockType(f_X, f_Y, f_Z, blockType);
														}

													f_Grid->SetNeedsRebuild(true, true, true);
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
	
#if 0
		//g_VoxMuti.ac_Free();
#endif
		}
#endif
}

bool qamTerrain::Make_Place_Terrain(int f_Grid)
{
	const float BLOCK_RENDER = (Cube::VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
	const float GRID_SIZE = (Cube::VoxelGrid::VOXEL_GRID_SIZE * BLOCK_RENDER);

#if 0
	if(g_GameOpen)
		{
		BiVector f_Pos;

#if 0
		//g_VoxMuti.ac_Fire();
#endif

		for(int f_moveX = 1; f_moveX < (m_TerrainInsertMaxX + 1); f_moveX += m_TerrainInsertMoveX)
			{
			for(int f_moveY = 1; f_moveY < (m_TerrainInsertMaxY + 1); f_moveY += m_TerrainInsertMoveY)
				{
				for(int f_moveZ = 1; f_moveZ < (m_TerrainInsertMaxZ + 1); f_moveZ += m_TerrainInsertMoveZ)
					{
					for(int f_fillX = 1; f_fillX < (m_TerrainInsertFillX + 1); f_fillX++)
						{
						for(int f_fillY = 1; f_fillY < (m_TerrainInsertFillY + 1); f_fillY++)
							{
							for(int f_fillZ = 1; f_fillZ < (m_TerrainInsertFillZ + 1); f_fillZ++)
								{
								  ///////////
								 // fpos
								//
								f_Pos.m_X = m_X + (((f_fillX * BLOCK_RENDER) * f_moveX));
								f_Pos.m_Y = m_Y + (((f_fillY * BLOCK_RENDER) * f_moveY));
								f_Pos.m_Z = m_Z + (((f_fillZ * BLOCK_RENDER) * f_moveZ));

								if( (f_Pos.m_X >= (f_Grid->m_gridX * GRID_SIZE)) &&
									(f_Pos.m_X < ((f_Grid->m_gridX + 1) * GRID_SIZE)) &&
									(f_Pos.m_Y >= (f_Grid->m_gridY * GRID_SIZE)) &&
									(f_Pos.m_Y < ((f_Grid->m_gridY + 1) * GRID_SIZE)) &&
									(f_Pos.m_Z >= ((f_Grid->m_gridZ * -1) * GRID_SIZE)) &&
									(f_Pos.m_Z < (((f_Grid->m_gridZ * -1) + 1) * GRID_SIZE)))
									{
									return true;
									}
								}
							}
						}
					}
				}
			}
	
#if 0
		//g_VoxMuti.ac_Free();
#endif
		}
#endif

	return false;
}

};