/*

    unTerrainCell - Terrain Loader
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#if 0
#include "nvsg/CoreTypes.h"

#include "nvmath/Vec2f.h"
#include "nvmath/Trafo.h"
#include "nvsg/Face.h"
#include "nvsg/FaceAttribute.h"
#include "nvsg/GeoNode.h"
#include "nvsg/Material.h"
#include "nvsg/TextureAttribute.h"
#include "nvsg/Transform.h"
#include "nvsg/Triangles.h"
#include "nvsg/HighlightBox.h"
#include "nvsg/DepthAttribute.h"
#endif

#include "unTerrainCell.h"

#include "../Utility/icConsole.h"
//#include "Physics/icPhysics.h"
//#include "Physics/icPhysicsObjectCreator.h"
//#include "../GameShell.h"

//#include "nvutil/DbgNew.h" // this must be the last include

//using nvmath::pVector;
//using nvmath::Trafo;

//nvsg::CgFxHandle *unTerrainCell::cgfxHdl = 0;

unTerrainCell::unTerrainCell()// :
    //terrainPhysicsHdl(0)
{
	std::string string1;
	std::string string2;
	std::string string3 = string1 + string2;
}

unTerrainCell::~unTerrainCell()
{
}

void unTerrainCell::init()
{
}

void unTerrainCell::shutdown()
{
    //if (m_trafo)
    //    m_trafo->removeRef();
}

void unTerrainCell::load(const char* filename, int ix, int iy, bool rlock)
{
    //using namespace nvmath;
    //using namespace nvsg;
    //using namespace nvutil;

    //unTerrain* terrain = unTerrain::instance();

#if 0
	trrelement element;

	for (int z=0; z < TRR_GRID_SIZE; ++z)
		{
			trrGrid.Grid[5][3].push_back(element);
		}

	for (int v=1; v < TRR_GRID_SIZE; ++v)
		{
		trrGrid.Grid[v].push_back(element);
		}
#endif

	trrvertex t_trrvertex(0);

	trrGrid.setBCthreshold(0.01);

#if 0
	////// Load trrGrid //////
	trrGrid.load(filename);
#endif

#if 1
	for (int y=0; y < TRR_GRID_SIZE; ++y)
		{
        for (int x=0; x < TRR_GRID_SIZE; ++x)
			{
			trrGrid.Grid[x][y].layers.push_back( t_trrvertex );
			}
		}
#endif
#if 0

	//// Layer Instigator
	//// Layer Terminator
	t_trrvertex.y_vertex = 7;
	trrGrid.Grid[4][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[5][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[9][4].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 5;
	trrGrid.Grid[5][5].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][5].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][5].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 7;
	trrGrid.Grid[9][5].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 5;
	trrGrid.Grid[5][6].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][6].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][6].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 7;
	trrGrid.Grid[9][6].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 5;
	trrGrid.Grid[5][7].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][7].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][7].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 7;
	trrGrid.Grid[9][7].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 5;
	trrGrid.Grid[5][8].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][8].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][8].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 7;
	trrGrid.Grid[9][8].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[5][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[9][9].layers.push_back( t_trrvertex );

	//// Layer Terminator
	t_trrvertex.y_vertex = 8;
	trrGrid.Grid[4][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[5][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][4].layers.push_back( t_trrvertex );
	trrGrid.Grid[9][4].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 10;
	trrGrid.Grid[5][5].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][5].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][5].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 8;
	trrGrid.Grid[9][5].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 10;
	trrGrid.Grid[5][6].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][6].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][6].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 8;
	trrGrid.Grid[9][6].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 10;
	trrGrid.Grid[5][7].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][7].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][7].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 8;
	trrGrid.Grid[9][7].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 10;
	trrGrid.Grid[5][8].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][8].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][8].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_vertex = 8;
	trrGrid.Grid[9][8].layers.push_back( t_trrvertex );

	trrGrid.Grid[4][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[5][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[6][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[7][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[8][9].layers.push_back( t_trrvertex );
	trrGrid.Grid[9][9].layers.push_back( t_trrvertex );
#endif

#if 0
	trrGrid.Grid[1][9].layers[0].y_vertex = 1;
	trrGrid.Grid[2][9].layers[0].y_vertex = 1;
	trrGrid.Grid[3][9].layers[0].y_vertex = 1;
	trrGrid.Grid[4][9].layers[0].y_vertex = 1;
	trrGrid.Grid[5][9].layers[0].y_vertex = 1;
	trrGrid.Grid[6][9].layers[0].y_vertex = 1;
	trrGrid.Grid[7][9].layers[0].y_vertex = 1;
	trrGrid.Grid[8][9].layers[0].y_vertex = 1;
	trrGrid.Grid[9][9].layers[0].y_vertex = 1;

	trrGrid.Grid[1][8].layers[0].y_vertex = 1;
	trrGrid.Grid[2][8].layers[0].y_vertex = 1;
	trrGrid.Grid[3][8].layers[0].y_vertex = 1;
	trrGrid.Grid[4][8].layers[0].y_vertex = 1;
	trrGrid.Grid[5][8].layers[0].y_vertex = 1;
	trrGrid.Grid[6][8].layers[0].y_vertex = 1;
	trrGrid.Grid[7][8].layers[0].y_vertex = 1;
	trrGrid.Grid[8][8].layers[0].y_vertex = 1;
	trrGrid.Grid[9][8].layers[0].y_vertex = 1;

	trrGrid.Grid[1][3].layers[0].y_vertex = 1;
	trrGrid.Grid[2][3].layers[0].y_vertex = 1;
	trrGrid.Grid[3][3].layers[0].y_vertex = 1;
	trrGrid.Grid[4][3].layers[0].y_vertex = 1;
	trrGrid.Grid[5][3].layers[0].y_vertex = 1;
	trrGrid.Grid[6][3].layers[0].y_vertex = 1;
	trrGrid.Grid[7][3].layers[0].y_vertex = 1;
	trrGrid.Grid[8][3].layers[0].y_vertex = 1;
	trrGrid.Grid[9][3].layers[0].y_vertex = 1;

	trrGrid.Grid[1][4].layers[0].y_vertex = 2;
	trrGrid.Grid[2][4].layers[0].y_vertex = 2;
	trrGrid.Grid[3][4].layers[0].y_vertex = 2;
	trrGrid.Grid[4][4].layers[0].y_vertex = 2;
	trrGrid.Grid[5][4].layers[0].y_vertex = 2;
	trrGrid.Grid[6][4].layers[0].y_vertex = 2;
	trrGrid.Grid[7][4].layers[0].y_vertex = 2;
	trrGrid.Grid[8][4].layers[0].y_vertex = 2;
	trrGrid.Grid[9][4].layers[0].y_vertex = 2;

	trrGrid.Grid[1][5].layers[0].y_vertex = 1;
	trrGrid.Grid[2][5].layers[0].y_vertex = 1;
	trrGrid.Grid[3][5].layers[0].y_vertex = 1;
	trrGrid.Grid[4][5].layers[0].y_vertex = 1;
	trrGrid.Grid[5][5].layers[0].y_vertex = 1;
	trrGrid.Grid[6][5].layers[0].y_vertex = 1;
	trrGrid.Grid[7][5].layers[0].y_vertex = 1;
	trrGrid.Grid[8][5].layers[0].y_vertex = 1;
	trrGrid.Grid[9][5].layers[0].y_vertex = 1;
#endif

	////// trr-end //////
	trrveclayer t_trrveclayer;

	/// Push first layer
	veclayer.push_back( t_trrveclayer );

	int dim = TRR_GRID_SIZE;

    const float scale = m_scale;
	
	trrGrid.setScale(m_scale);
	m_resetCount = 0;

    float fdim = m_fdim = (float)(dim-1)*scale;
    float sx = -(dim-1)*scale*0.5;
    float fy = sx;

    float tx=0,ty=0;
    float td=(1.0 / (dim-1)) * m_texscale;

	/// Variable declaration
	bool Exists = false;
	bool vmatch = false;
	bool xload = false;
	bool xedge = false;
	bool xspan = false;
	bool xterm = false;
	bool yedge = false;
	bool yspan = false;
	bool yterm = false;
	bool xtrail = false;
	bool xgain = false;

	int ThisVert = 0;
	int VertTrav = 0;
	int VertSpace = 0;
	int search = 0;
	int memseal = 0;
	int makeTri = 0;
	bool mkTri = false;
	pVector ThisVertex;
	pVector CheckVertex;

	Face3 faceA,faceB;
	Face3 termfaceA,termfaceB;
	Face3 sealA,sealB;

	/// Universal Binary Cube
	trrBinaryCube* bCube = new trrBinaryCube();

	/// Layer Traverser
	int layertrav = 0;
	nverts = 0;
	nfaces = 0;
	nseals = 0;

	/// Cell Floor Loading
    size_t i = 0;
    for (int y=0; y < dim; ++y)
		{
        float fx = sx;
        tx = 0;
        for (int x=0; x < dim; ++x)
			{
			/// Existance checks
			Exists = false;

			if(x == (TRR_GRID_SIZE - 1)) xterm = true;
			else xterm = false;

			/// Neighbour Existance Checks | Minor Overlap Detection and Clashing Vertex Removal
			if(x != 0 && x != (TRR_GRID_SIZE - 1) && y != 0/* && y != (TRR_GRID_SIZE - 1)*/)
				{
				xload = false;
				vmatch = false;
				for (int v=0; v < trrGrid.Grid[x+1][y-1].layers.size(); v+=2)
					{
					if(v == 0) /// First layer
						{
						if(trrGrid.Grid[x+1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[0].y_vertex) vmatch = true;
						}
					else
						{
						if(v & 1) /// Layer is Odd and Terminator
							{
							if(trrGrid.Grid[x+1][y-1].layers[v].y_vertex >= trrGrid.Grid[x][y-1].layers[0].y_vertex &&
							   trrGrid.Grid[x+1][y-1].layers[v-1].y_vertex <= trrGrid.Grid[x][y-1].layers[0].y_vertex)
								{
								vmatch = true;
								}
							}
						}
					}
				if(vmatch) { Exists = true; xload = true; }
				else
					{
					vmatch = false;
					for (int v=0; v < trrGrid.Grid[x-1][y-1].layers.size(); v+=2)
						{
						if(v == 0) /// First layer
							{
							if(trrGrid.Grid[x-1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[0].y_vertex) vmatch = true;
							}
						else
							{
							if(v & 1) /// Layer is Odd and Terminator
								{
								if(trrGrid.Grid[x-1][y-1].layers[v].y_vertex >= trrGrid.Grid[x][y-1].layers[0].y_vertex &&
								   trrGrid.Grid[x-1][y-1].layers[v-1].y_vertex <= trrGrid.Grid[x][y-1].layers[0].y_vertex)
									{
									vmatch = true;
									}
								}
							}
						}
					if(vmatch) { Exists = true; xload = true; }
					else
						{
						vmatch = false;
						for (int v=0; v < trrGrid.Grid[x][y-1].layers.size(); v+=2)
							{
							if(v == 0) /// First layer
								{
								if(trrGrid.Grid[x][y-1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
								}
							else
								{
								if(v & 1) /// Layer is Odd and Terminator
									{
									if(trrGrid.Grid[x][y-1].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
									   trrGrid.Grid[x][y-1].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
										{
										vmatch = true;
										}
									}
								}
							}
						if(vmatch) { Exists = true; }
						else
							{
							vmatch = false;
							for (int v=0; v < trrGrid.Grid[x+1][y].layers.size(); v+=2)
								{
								if(v == 0) /// First layer
									{
									if(trrGrid.Grid[x+1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
									}
								else
									{
									if(v & 1) /// Layer is Odd and Terminator
										{
										if(trrGrid.Grid[x+1][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
										   trrGrid.Grid[x+1][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
											{
											vmatch = true;
											}
										}
									}
								}
							if(vmatch) { Exists = true; }
								{
								vmatch = false;
								for (int v=0; v < trrGrid.Grid[x-1][y].layers.size(); v+=2)
									{
									if(v == 0) /// First layer
										{
										if(trrGrid.Grid[x-1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
										}
									else
										{
										if(v & 1) /// Layer is Odd and Terminator
											{
											if(trrGrid.Grid[x-1][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
											   trrGrid.Grid[x-1][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									}
								if(vmatch) Exists = true;
								else
									{
									vmatch = false;
									for (int v=0; v < trrGrid.Grid[x][y+1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x][y+1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
											}
										else
											{
											if(v & 1) /// Layer is Odd and Terminator
												{
												if(trrGrid.Grid[x][y+1].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
												   trrGrid.Grid[x][y+1].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
													{
													vmatch = true;
													}
												}
											}
										}
									if(vmatch) Exists = true;
									else
										{
										/*/// Neighbour Five check	//HOLD LAYER HEIGHT VISIBILITY
										vmatch = false;
										for (int v=0; v < trrGrid.Grid[x][y].layers.size(); v+=2)
											{
											if(v == 0) /// First layer
												{
												if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex + trrGrid.getScale()) vmatch = true;
												}
											else
												{
												if(v & 1) /// Layer is Odd and Terminator
													{
													if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex + trrGrid.getScale() &&
													   trrGrid.Grid[x][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex + trrGrid.getScale())
														{
														vmatch = true;
														}
													}
												}
											}*/
										/*if(!vmatch) Exists = true;
										else
											{
											/// Neighbour Six check
											vmatch = false;
											for (int v=0; v < trrGrid.Grid[x][y].layers.size(); v+=2)
												{
												if(v == 0) /// First layer
													{
													if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex - trrGrid.getScale()) vmatch = true;
													}
												else
													{
													if(v & 1) /// Layer is Odd and Terminator
														{
														if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex - trrGrid.getScale() &&
														   trrGrid.Grid[x][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex - trrGrid.getScale())
															{
															vmatch = true;
															}
														}
													}
												}
											if(!vmatch) Exists = true;
											}*/
										}
									}
								}
							}
						}
					}

				/// Generate trrBinaryCube
				if(Exists && y != (TRR_GRID_SIZE - 1))
					{
					bCube = trrGrid.SetBC(x, y, 0);
					bCube->Cook();

					///// TEMPORARY EXCLUDE
					/*for(int t=0; t < TRR_NB_TEMPLATES; ++t)
						{
						if(bCube->Compare(terrain->trrTemplateCube[t].getAngle()) == 0)
							{
							Exists = false;
							//printf("REFUSED m_angle = %i template id %i\n", bCube->getAngle(), t);
							}
						}*/
					}
				}
			else
				{
				Exists = true;
				bCube->setIdentity();
				bCube->Cook();
				}

			/// Set first layer faces
			if(Exists)
				{
				veclayer[0].addVert(fx, trrGrid.Grid[x][y].layers[0].y_vertex, fy);
				veclayer[0].vecsearch.push_back(0);
				veclayer[0].vecxload.push_back(xload);
				veclayer[0].vecxterm.push_back(xterm);
				veclayer[0].addBC(bCube);
				nverts++;

				ThisVert = veclayer[0].vecvert.size() - 1;
				VertTrav = veclayer[0].vecvert.size() - 3;

				VertSpace = 0;
				search = 0;
				mkTri = false;

				/// Optimise Add edge convertion
				if(x > 0 && y > 0 && VertTrav >= 0)
					{
					faceA.m_v1 = faceB.m_v3 = ThisVert;					/// Floor Vertex Assignment 1
					faceB.m_v2 = ThisVert - 1;						/// Floor Vertex Assignment 2

					ThisVertex = veclayer[0].vecvert[ThisVert - 1];
					CheckVertex = veclayer[0].vecvert[ThisVert];

					while(VertTrav >= 0)
						{
						if(veclayer[0].vecvert[VertTrav][0] >= veclayer[0].vecvert[ThisVert - 1][0] || VertTrav == 0 || veclayer[0].vecvert[VertTrav][1] != CheckVertex[1])
							search++;

						if(search < 1)	////// Simularity Checks //////
							{
							if(veclayer[0].vecvert[VertTrav][2] == ThisVertex[2] && veclayer[0].vecvert[VertTrav][1] == ThisVertex[1] && veclayer[0].vecvert[VertTrav][1] == CheckVertex[1] && !veclayer[0].vecxload[veclayer[0].vecface[veclayer[0].vecface.size() - 1].m_v3] && veclayer[0].vecvert[veclayer[0].vecface[veclayer[0].vecface.size() - 1].m_v2][0] != sx)	//24/06/07 Added Deconstructive change //ARCHIVE:  && !veclayer[0].vecxedge[VertTrav] //ARCHIVE:   && !veclayer[0].vecxload[veclayer[0].vecface[VertTrav+1][0]
								{
								int makeTri = veclayer[0].vecmktri.size() - 1;
								if(makeTri >= 0)
									{
									faceB.m_v2 = veclayer[0].vecface[veclayer[0].vecface.size() - 1].m_v2;		/// Floor Vertex Assignment 2

									if(veclayer[0].vecmktri[makeTri])
										{
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 1].m_v1]--;
										veclayer[0].clearFace();
										nfaces--;
										}
									else
										{
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 1].m_v1]--;
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 2].m_v2]--;
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 2].m_v3]--;
										veclayer[0].clearFace();
										veclayer[0].clearFace();
										nfaces-=2;
										}

									VertTrav = faceB.m_v2;

									veclayer[0].vecmktri.pop_back();
									}
								else faceB.m_v2 = VertTrav;
								search++;
								VertTrav--;
								}
							else
								{
								search++;
								VertTrav--;
								}
							}
						else
							{
							if((veclayer[0].vecvert[VertTrav][0] == veclayer[0].vecvert[faceB.m_v2][0] && veclayer[0].vecsearch[VertTrav] < 3) ||
							   (veclayer[0].vecvert[VertTrav][0] == veclayer[0].vecvert[faceB.m_v2][0] && veclayer[0].vecsearch[VertTrav + 1] < 1))
								{
								faceA.m_v3 = VertTrav;							/// Vertex Assignment 3
								faceB.m_v1 = VertTrav;							/// Vertex Assignment 3
								veclayer[0].vecsearch[VertTrav]++;
								VertTrav = -1;
								}
							else
								{
								if((veclayer[0].vecvert[VertTrav][2] < veclayer[0].vecvert[faceB.m_v2][2]) && (veclayer[0].vecvert[VertTrav][0] < veclayer[0].vecvert[faceB.m_v2][0]))
									{
									VertSpace = VertTrav;

									if(veclayer[0].vecvert[VertSpace][2] >= veclayer[0].vecvert[faceB.m_v2][2])
										VertSpace = faceB.m_v2;

									while(VertSpace < faceB.m_v2)
										{
										if(veclayer[0].vecsearch[VertSpace] < 1)
											{
											faceA.m_v3 = VertSpace;				/// Vertex Assignment 3
											faceB.m_v1 = VertSpace;				/// Vertex Assignment 3
											veclayer[0].vecsearch[VertSpace]++;
											VertSpace = faceB.m_v2;
											}
										else
											{
											if((/*veclayer[0].vecxterm[VertSpace] &&*/ veclayer[0].vecvert[VertSpace][0] >= veclayer[0].vecvert[faceB.m_v2][0]) ||
											   (veclayer[0].vecsearch[VertSpace] < 2 && veclayer[0].vecvert[VertSpace][0] == veclayer[0].vecvert[faceB.m_v3][0]))
												{
												faceA.m_v3 = VertSpace;
												faceB.m_v1 = VertSpace;			/// Vertex Assignment 3
												veclayer[0].vecsearch[VertSpace]++;
												VertSpace = faceB.m_v2;
												mkTri = true;
												}
											}
										VertSpace++;
										}
									VertTrav = -1;
									}
								}
							}
						VertTrav--;
						}

					VertTrav = veclayer[0].vecvert.size() - 2;
					VertSpace = 0;
					search = 0;

					while(VertTrav >= 0 && !mkTri)	/// Locate Fourth Vertex
						{
						if(veclayer[0].vecvert[VertTrav][0] >= veclayer[0].vecvert[ThisVert][0])
							search = 1;

						if(search > 0)
							{
							if(veclayer[0].vecvert[VertTrav][0] == veclayer[0].vecvert[ThisVert][0] &&
								veclayer[0].vecsearch[VertTrav] < 2)
								{
								faceA.m_v2 = VertTrav;							/// Vertex Assignment 4
								veclayer[0].vecsearch[VertTrav]++;
								VertTrav = -1;
								}
							else
								{
								if(veclayer[0].vecvert[VertTrav][0] < veclayer[0].vecvert[ThisVert][0])
									{
									VertSpace = VertTrav;

									if(veclayer[0].vecvert[VertSpace][2] >= veclayer[0].vecvert[ThisVert][2])
										VertSpace = ThisVert;

									while(VertSpace < ThisVert)
										{
										if(veclayer[0].vecsearch[VertSpace] == 0)
											{
											faceA.m_v2 = VertSpace;				/// Vertex Assignment 4
											veclayer[0].vecsearch[VertSpace]++;
											VertSpace = ThisVert;
											}
										VertSpace++;
										}

									VertTrav = -1;
									}
								}
							}
						VertTrav--;
						}

					if(!mkTri)
						{
						veclayer[0].addFace(faceA);
						veclayer[0].addFace(faceB);
						nfaces+=2;
						}
					else
						{
						veclayer[0].addFace(faceB);
						nfaces++;
						}

					veclayer[0].vecmktri.push_back(mkTri);
					}
				}

			///////// Other Layer Vertices /////////
			for (layertrav = 1; layertrav < trrGrid.Grid[x][y].layers.size(); ++layertrav)	/// Add by two ?
				{
				if(layertrav & 1) /// Layer is Odd and Instigator
					{			/////	Instigator	/////
					/// Existance checks
					Exists = false;
					xedge = true;
					xspan = true;
					yedge = true;
					yspan = true;
					yterm = true;
					xtrail = true;
					xgain = true;

					if(x == (TRR_GRID_SIZE - 1)) xterm = true;
					else xterm = false;

					/// Neighbour Existance Checks | Minor Overlap Detection and Clashing Vertex Removal
					if(x != 0 && x != (TRR_GRID_SIZE - 1) && y != 0)
						{
						///// Extents Divisal /////
						if(!xterm)
							{ xterm = true;
							for (int v=0; v < trrGrid.Grid[x+1][y].layers.size(); ++v)
								if(v == layertrav) xterm = false; }

						for (int v=0; v < trrGrid.Grid[x][y-1].layers.size(); ++v)
							if(v == layertrav) yedge = false;

						for (int v=0; v < trrGrid.Grid[x][y-2].layers.size(); ++v)
							if(v == layertrav) yspan = false;

						for (int v=0; v < trrGrid.Grid[x][y+1].layers.size(); ++v)
							if(v == layertrav) yterm = false;

						for (int v=0; v < trrGrid.Grid[x-1][y].layers.size(); ++v)
							if(v == layertrav) xedge = false;

						for (int v=0; v < trrGrid.Grid[x-2][y].layers.size(); ++v)
							if(v == layertrav) xspan = false;

						for (int v=0; v < trrGrid.Grid[x-1][y-1].layers.size(); ++v)
							if(v == layertrav) xtrail = false;

						for (int v=0; v < trrGrid.Grid[x+1][y-1].layers.size(); ++v)
							if(v == layertrav) xgain = false;

						if(!xedge && !xterm && !yedge)
							{
							xload = false;
							if(!xgain)
								{
								vmatch = false;
								for (int v=1; v < trrGrid.Grid[x+1][y-1].layers.size(); v+=2)
									{
									if(v == 0) /// First layer
										{
										if(trrGrid.Grid[x+1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
										}
									else
										{
										if(trrGrid.Grid[x+1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
											{
											vmatch = true;
											}
										}
									}
								}
							else vmatch = true;
							if(vmatch) { Exists = true; xload = true; }
							else
								{
								if(!xtrail)
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x-1][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x-1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x-1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									}
								else vmatch = true;
								if(vmatch) { Exists = true; xload = true; }
								else
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									if(vmatch) { Exists = true; }
									else
										{
										vmatch = false;
										for (int v=1; v < trrGrid.Grid[x+1][y].layers.size(); v+=2)
											{
											if(v == 0) /// First layer
												{
												if(trrGrid.Grid[x+1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
												}
											else
												{
												if(trrGrid.Grid[x+1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
													{
													vmatch = true;
													}
												}
											}
										if(vmatch) { Exists = true; }
										else
											{
											vmatch = false;
											for (int v=1; v < trrGrid.Grid[x-1][y].layers.size(); v+=2)
												{
												if(v == 0) /// First layer
													{
													if(trrGrid.Grid[x-1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
													}
												else
													{
													if(trrGrid.Grid[x-1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
														{
														vmatch = true;
														}
													}
												}
											if(vmatch) Exists = true;
											else
												{
												vmatch = false;
												for (int v=1; v < trrGrid.Grid[x][y+1].layers.size(); v+=2)
													{
													if(v == 0) /// First layer
														{
														if(trrGrid.Grid[x][y+1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
														}
													else
														{
														if(trrGrid.Grid[x][y+1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
															{
															vmatch = true;
															}
														}
													}
												if(vmatch) Exists = true;
												else
													{
													/*/// Neighbour Five check	//HOLD LAYER HEIGHT VISIBILITY
													vmatch = false;
													for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
														{
														if(v == 0) /// First layer
															{
															if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale()) vmatch = true;
															}
														else
															{
															if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale())
																{
																vmatch = true;
																}
															}
														}*/
													/*if(!vmatch) Exists = true;
													else
														{
														/// Neighbour Six check
														vmatch = false;
														for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
															{
															if(v == 0) /// First layer
																{
																if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale()) vmatch = true;
																}
															else
																{
																if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale())
																	{
																	vmatch = true;
																	}
																}
															}
														if(!vmatch) Exists = true;
														}*/
													}
												}
											}
										}
									}
								}

							/// Generate trrBinaryCube
							if(Exists && y != (TRR_GRID_SIZE - 1))
								{
								bCube = trrGrid.SetBC(x, y, layertrav);
								bCube->Cook();

								///// TEMPORARY EXCLUDE
								/*for(int t=0; t < TRR_NB_TEMPLATES; ++t)
									{
									if(bCube->Compare(terrain->trrTemplateCube[t].getAngle()) == 0)
										{
										Exists = false;
										//printf("REFUSED m_angle = %i template id %i\n", bCube->getAngle(), t);
										}
									}*/
								}
							}
						else
							{
							Exists = true;
							bCube->setIdentity();
							bCube->Cook();
							}
						}
					else	/// Optimise Tail Refusal BC
						{
						Exists = true;
						bCube->setIdentity();
						bCube->Cook();
						}

					/// Existance Checks
					if(Exists)
						{
						if(layertrav + 1 > veclayer.size())
							{
							trrveclayer t_trrveclayer;

							t_trrveclayer.addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							t_trrveclayer.vecsearch.push_back(0);
							t_trrveclayer.vecxload.push_back(xload);
							t_trrveclayer.vecxedge.push_back(xedge);
							t_trrveclayer.vecxterm.push_back(xterm);
							t_trrveclayer.addBC(bCube);
							nverts++;

							veclayer.push_back( t_trrveclayer );
							}
						else
							{
							veclayer[layertrav].addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							veclayer[layertrav].vecsearch.push_back(0);
							veclayer[layertrav].vecxload.push_back(xload);
							veclayer[layertrav].vecxedge.push_back(xedge);
							veclayer[layertrav].vecxterm.push_back(xterm);
							veclayer[layertrav].addBC(bCube);
							nverts++;
							}

						ThisVert = veclayer[layertrav].vecvert.size() - 1;
						VertTrav = veclayer[layertrav].vecvert.size() - 3;

						VertSpace = 0;
						search = 0;
						mkTri = false;

						/// Optimise Add edge convertion | Combine three booleans? point??
						if(!xedge && !yedge && VertTrav >= 0)
							{
							faceA.m_v1 = faceB.m_v2 = ThisVert;					/// Floor Vertex Assignment 1
							faceB.m_v3 = ThisVert - 1;						/// Floor Vertex Assignment 2

							ThisVertex = veclayer[layertrav].vecvert[ThisVert - 1];
							CheckVertex = veclayer[layertrav].vecvert[ThisVert];

							while(VertTrav >= 0)
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert - 1][0] || VertTrav == 0 || veclayer[layertrav].vecvert[VertTrav][1] != CheckVertex[1])
									search++;

								if(search < 1)	////// Simularity Checks //////
									{
									if(veclayer[layertrav].vecvert[VertTrav][2] == ThisVertex[2] && veclayer[layertrav].vecvert[VertTrav][1] == ThisVertex[1] && veclayer[layertrav].vecvert[VertTrav][1] == CheckVertex[1] && !veclayer[layertrav].vecxload[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v1] && !veclayer[layertrav].vecxedge[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v2])	//24/06/07 Added Deconstructive change //ARCHIVE:  && !veclayer[0].vecxedge[VertTrav] //ARCHIVE:   && !veclayer[0].vecxload[veclayer[0].vecface[VertTrav+1][0]
										{
										int makeTri = veclayer[layertrav].vecmktri.size() - 1;
										if(makeTri >= 0)
											{
											faceB.m_v3 = veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v2;		/// Floor Vertex Assignment 2

											if(veclayer[layertrav].vecmktri[makeTri])
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v1]--;
												veclayer[layertrav].clearFace();
												nfaces--;
												}
											else
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v1]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2].m_v2]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2].m_v3]--;
												veclayer[layertrav].clearFace();
												veclayer[layertrav].clearFace();
												nfaces-=2;
												}

											VertTrav = faceB.m_v3;

											veclayer[layertrav].vecmktri.pop_back();
											}
										else faceB.m_v3 = VertTrav;
										search++;
										VertTrav--;
										}
									else
										{
										search++;
										VertTrav--;
										}
									}
								else
									{
									if((veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[faceB.m_v3][0] && veclayer[layertrav].vecsearch[VertTrav] < 3) ||
									   (veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[faceB.m_v3][0] && veclayer[layertrav].vecsearch[VertTrav + 1] < 1))
										{
										faceA.m_v2 = VertTrav;							/// Vertex Assignment 3
										faceB.m_v1 = VertTrav;							/// Vertex Assignment 3
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if((veclayer[layertrav].vecvert[VertTrav][2] < veclayer[layertrav].vecvert[faceB.m_v3][2]) && (veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[faceB.m_v3][0]))
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[faceB.m_v3][2])
												VertSpace = faceB.m_v3;

											while(VertSpace < faceB.m_v3)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] < 1)
													{
													faceA.m_v2 = VertSpace;				/// Vertex Assignment 3
													faceB.m_v1 = VertSpace;				/// Vertex Assignment 3
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = faceB.m_v3;
													}
												else
													{
													if((/*veclayer[layertrav].vecxterm[VertSpace] &&*/ veclayer[layertrav].vecvert[VertSpace][0] >= veclayer[layertrav].vecvert[faceB.m_v3][0]) ||
													   (veclayer[layertrav].vecsearch[VertSpace] < 2 && veclayer[layertrav].vecvert[VertSpace][0] == veclayer[layertrav].vecvert[faceB.m_v2][0]))
														{
														faceA.m_v2 = VertSpace;
														faceB.m_v1 = VertSpace;			/// Vertex Assignment 3
														veclayer[layertrav].vecsearch[VertSpace]++;
														VertSpace = faceB.m_v3;
														mkTri = true;
														}
													}
												VertSpace++;
												}
											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							VertTrav = veclayer[layertrav].vecvert.size() - 2;
							VertSpace = 0;
							search = 0;

							while(VertTrav >= 0 && !mkTri)	/// Locate Fourth Vertex
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert][0])
									search = 1;

								if(search > 0)
									{
									if(veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[ThisVert][0] &&
										veclayer[layertrav].vecsearch[VertTrav] < 2)
										{
										faceA.m_v3 = VertTrav;							/// Vertex Assignment 4
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if(veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[ThisVert][0])
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[ThisVert][2])
												VertSpace = ThisVert;

											while(VertSpace < ThisVert)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] == 0)
													{
													faceA.m_v3 = VertSpace;				/// Vertex Assignment 4
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = ThisVert;
													}
												VertSpace++;
												}

											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							if(!mkTri)
								{
								veclayer[layertrav].addFace(faceA);
								veclayer[layertrav].addFace(faceB);
								nfaces+=2;
								}
							else
								{
								veclayer[layertrav].addFace(faceB);
								nfaces++;
								}

							veclayer[layertrav].vecmktri.push_back(mkTri);
							}
						}
					}	///// Instigator /////
				else
					{	///// Terminator /////
					/// Existance checks
					Exists = false;
					xedge = true;
					yedge = true;
					yspan = true;
					yterm = true;
					xtrail = true;
					xgain = true;

					if(x == (TRR_GRID_SIZE - 1)) xterm = true;
					else xterm = false;

					/// Neighbour Existance Checks | Minor Overlap Detection and Clashing Vertex Removal
					if(x != 0 && x != (TRR_GRID_SIZE - 1) && y != 0)
						{
						///// Extents Divisal /////
						if(!xterm)
							{ xterm = true;
							for (int v=0; v < trrGrid.Grid[x+1][y].layers.size(); ++v)
								if(v == layertrav) xterm = false; }

						for (int v=0; v < trrGrid.Grid[x][y-1].layers.size(); ++v)
							if(v == layertrav) yedge = false;

						for (int v=0; v < trrGrid.Grid[x][y-2].layers.size(); ++v)
							if(v == layertrav) yspan = false;

						for (int v=0; v < trrGrid.Grid[x][y+1].layers.size(); ++v)
							if(v == layertrav) yterm = false;

						for (int v=0; v < trrGrid.Grid[x-1][y].layers.size(); ++v)
							if(v == layertrav) xedge = false;

						for (int v=0; v < trrGrid.Grid[x-1][y-1].layers.size(); ++v)
							if(v == layertrav) xtrail = false;

						for (int v=0; v < trrGrid.Grid[x+1][y-1].layers.size(); ++v)
							if(v == layertrav) xgain = false;

						if(!xedge && !xterm && !yedge)
							{
							xload = false;
							if(!xgain)
								{
								vmatch = false;
								for (int v=1; v < trrGrid.Grid[x+1][y-1].layers.size(); v+=2)
									{
									if(v == 0) /// First layer
										{
										if(trrGrid.Grid[x+1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
										}
									else
										{
										if(trrGrid.Grid[x+1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
											{
											vmatch = true;
											}
										}
									}
								}
							else vmatch = true;
							if(vmatch) { Exists = true; xload = true; }
							else
								{
								if(!xgain)
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x-1][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x-1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x-1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									}
								else vmatch = true;
								if(vmatch) { Exists = true; xload = true; }
								else
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x][y-1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									if(vmatch) { Exists = true; }
									else
										{
										vmatch = false;
										for (int v=1; v < trrGrid.Grid[x+1][y].layers.size(); v+=2)
											{
											if(v == 0) /// First layer
												{
												if(trrGrid.Grid[x+1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
												}
											else
												{
												if(trrGrid.Grid[x+1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
													{
													vmatch = true;
													}
												}
											}
										if(vmatch) { Exists = true; }
										else
											{
											vmatch = false;
											for (int v=1; v < trrGrid.Grid[x-1][y].layers.size(); v+=2)
												{
												if(v == 0) /// First layer
													{
													if(trrGrid.Grid[x-1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
													}
												else
													{
													if(trrGrid.Grid[x-1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
														{
														vmatch = true;
														}
													}
												}
											if(vmatch) Exists = true;
											else
												{
												vmatch = false;
												for (int v=1; v < trrGrid.Grid[x][y+1].layers.size(); v+=2)
													{
													if(v == 0) /// First layer
														{
														if(trrGrid.Grid[x][y+1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
														}
													else
														{
														if(trrGrid.Grid[x][y+1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
															{
															vmatch = true;
															}
														}
													}
												if(vmatch) Exists = true;
												else
													{
													/*/// Neighbour Five check	//HOLD LAYER HEIGHT VISIBILITY
													vmatch = false;
													for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
														{
														if(v == 0) /// First layer
															{
															if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale()) vmatch = true;
															}
														else
															{
															if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale())
																{
																vmatch = true;
																}
															}
														}*/
													/*if(!vmatch) Exists = true;
													else
														{
														/// Neighbour Six check
														vmatch = false;
														for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
															{
															if(v == 0) /// First layer
																{
																if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale()) vmatch = true;
																}
															else
																{
																if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale())
																	{
																	vmatch = true;
																	}
																}
															}
														if(!vmatch) Exists = true;
														}*/
													}
												}
											}
										}
									}
								}

							/// Generate trrBinaryCube
							if(Exists && y != (TRR_GRID_SIZE - 1))
								{
								bCube = trrGrid.SetBC(x, y, layertrav);
								bCube->Cook();

								///// TEMPORARY EXCLUDE
								/*for(int t=0; t < TRR_NB_TEMPLATES; ++t)
									{
									if(bCube->Compare(terrain->trrTemplateCube[t].getAngle()) == 0)
										{
										Exists = false;
										//printf("REFUSED m_angle = %i template id %i\n", bCube->getAngle(), t);
										}
									}*/
								}
							}
						else
							{
							Exists = true;
							bCube->setIdentity();
							bCube->Cook();
							}
						}
					else
						{
						Exists = true;
						bCube->setIdentity();
						bCube->Cook();
						}

					/// Existance Checks
					if(Exists)
						{
						if(layertrav + 1 > veclayer.size())
							{
							trrveclayer t_trrveclayer;

							t_trrveclayer.addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							t_trrveclayer.vecsearch.push_back(0);
							t_trrveclayer.vecxload.push_back(xload);
							t_trrveclayer.vecxedge.push_back(xedge);
							t_trrveclayer.vecxterm.push_back(xterm);
							t_trrveclayer.addBC(bCube);
							nverts++;

							veclayer.push_back( t_trrveclayer );
							}
						else
							{
							veclayer[layertrav].addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							veclayer[layertrav].vecsearch.push_back(0);
							veclayer[layertrav].vecxload.push_back(xload);
							veclayer[layertrav].vecxedge.push_back(xedge);
							veclayer[layertrav].vecxterm.push_back(xterm);
							veclayer[layertrav].addBC(bCube);
							nverts++;
							}

						ThisVert = veclayer[layertrav].vecvert.size() - 1;
						VertTrav = veclayer[layertrav].vecvert.size() - 3;

						VertSpace = 0;
						search = 0;
						mkTri = false;

						/// Optimise Add edge convertion
						if(!xedge && !yedge && VertTrav >= 0)
							{
							termfaceA.m_v1 = termfaceB.m_v3 = ThisVert;					/// Floor Vertex Assignment 1
							termfaceB.m_v2 = ThisVert - 1;						/// Floor Vertex Assignment 2

							ThisVertex = veclayer[layertrav].vecvert[ThisVert - 1];
							CheckVertex = veclayer[layertrav].vecvert[ThisVert];

							while(VertTrav >= 0)
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert - 1][0] || VertTrav == 0 || veclayer[layertrav].vecvert[VertTrav][1] != CheckVertex[1])
									search++;

								if(search < 1)	////// Simularity Checks //////
									{
									if(veclayer[layertrav].vecvert[VertTrav][2] == ThisVertex[2] && veclayer[layertrav].vecvert[VertTrav][1] == ThisVertex[1] && veclayer[layertrav].vecvert[VertTrav][1] == CheckVertex[1] && !veclayer[layertrav].vecxload[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v3] && !veclayer[layertrav].vecxedge[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v2])	//24/06/07 Added Deconstructive change //ARCHIVE:  && !veclayer[0].vecxedge[VertTrav] //ARCHIVE:   && !veclayer[0].vecxload[veclayer[0].vecface[VertTrav+1][0]
										{
										int makeTri = veclayer[layertrav].vecmktri.size() - 1;
										if(makeTri >= 0)
											{
											termfaceB.m_v2 = veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v2;		/// Floor Vertex Assignment 2

											if(veclayer[layertrav].vecmktri[makeTri])
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v1]--;
												veclayer[layertrav].clearFace();
												nfaces--;
												}
											else
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1].m_v1]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2].m_v2]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2].m_v3]--;
												veclayer[layertrav].clearFace();
												veclayer[layertrav].clearFace();
												nfaces-=2;

												for(; memseal > 0; --memseal)
													{
													veclayer[layertrav].clearSeal();
													veclayer[layertrav].clearSeal();
													nseals-=2;
													}
												}

											VertTrav = termfaceB.m_v2;

											veclayer[layertrav].vecmktri.pop_back();
											}
										else termfaceB.m_v2 = VertTrav;
										search++;
										VertTrav--;
										}
									else
										{
										search++;
										VertTrav--;
										}
									}
								else
									{
								    if((veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[termfaceB.m_v2][0] && veclayer[layertrav].vecsearch[VertTrav] < 3) ||
									   (veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[termfaceB.m_v2][0] && veclayer[layertrav].vecsearch[VertTrav + 1] < 1))
										{
										termfaceA.m_v3 = VertTrav;							/// Vertex Assignment 3
										termfaceB.m_v1 = VertTrav;							/// Vertex Assignment 3
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if((veclayer[layertrav].vecvert[VertTrav][2] < veclayer[layertrav].vecvert[termfaceB.m_v2][2]) && (veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[termfaceB.m_v2][0]))
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[termfaceB.m_v2][2])
												VertSpace = termfaceB.m_v2;

											while(VertSpace < termfaceB.m_v2)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] < 1)
													{
													termfaceA.m_v3 = VertSpace;				/// Vertex Assignment 3
													termfaceB.m_v1 = VertSpace;				/// Vertex Assignment 3
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = termfaceB.m_v2;
													}
												else
													{
													if((/*veclayer[layertrav].vecxterm[VertSpace] &&*/ veclayer[layertrav].vecvert[VertSpace][0] >= veclayer[layertrav].vecvert[termfaceB.m_v2][0]) ||
													   (veclayer[layertrav].vecsearch[VertSpace] < 2 && veclayer[layertrav].vecvert[VertSpace][0] == veclayer[layertrav].vecvert[termfaceB.m_v3][0]))
														{
														termfaceA.m_v3 = VertSpace;
														termfaceB.m_v1 = VertSpace;			/// Vertex Assignment 3
														veclayer[layertrav].vecsearch[VertSpace]++;
														VertSpace = termfaceB.m_v2;
														mkTri = true;
														}
													}
												VertSpace++;
												}
											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							VertTrav = veclayer[layertrav].vecvert.size() - 2;
							VertSpace = 0;
							search = 0;

							while(VertTrav >= 0 && !mkTri)	/// Locate Fourth Vertex
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert][0])
									search = 1;

								if(search > 0)
									{
									if(veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[ThisVert][0] &&
										veclayer[layertrav].vecsearch[VertTrav] < 2)
										{
										termfaceA.m_v2 = VertTrav;							/// Vertex Assignment 4
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if(veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[ThisVert][0])
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[ThisVert][2])
												VertSpace = ThisVert;

											while(VertSpace < ThisVert)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] == 0)
													{
													termfaceA.m_v2 = VertSpace;				/// Vertex Assignment 4
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = ThisVert;
													}
												VertSpace++;
												}

											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							/// Seal Memory
							memseal = 0;

							if(!mkTri)
								{
								veclayer[layertrav].addFace(termfaceA);
								veclayer[layertrav].addFace(termfaceB);
								nfaces+=2;

								////// Layer Connection Seal //////
								if(yspan)
									{
									sealA.m_v1 = termfaceA.m_v2;
									sealA.m_v2 = faceA.m_v3;
									sealA.m_v3 = faceA.m_v2;

									sealA.m_v1 = faceA.m_v2;
									sealA.m_v2 = termfaceA.m_v3;
									sealA.m_v3 = termfaceA.m_v2;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}

								if(yterm)
									{
									sealA.m_v1 = faceA.m_v1;
									sealA.m_v2 = termfaceB.m_v2;
									sealA.m_v3 = termfaceA.m_v1;

									sealA.m_v1 = termfaceB.m_v2;
									sealA.m_v2 = faceA.m_v1;
									sealA.m_v3 = faceB.m_v3;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}

								if(xspan)
									{
									sealA.m_v1 = termfaceB.m_v2;
									sealA.m_v2 = termfaceA.m_v3;
									sealA.m_v3 = faceB.m_v3;

									sealA.m_v1 = faceA.m_v2;
									sealA.m_v2 = faceB.m_v3;
									sealA.m_v3 = termfaceB.m_v1;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}

								if(xterm)
									{
									sealA.m_v1 = faceA.m_v3;
									sealA.m_v2 = faceB.m_v2;
									sealA.m_v3 = termfaceA.m_v2;

									sealA.m_v1 = termfaceA.m_v1;
									sealA.m_v2 = termfaceA.m_v2;
									sealA.m_v3 = faceB.m_v2;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}
								}
							else
								{
								veclayer[layertrav].addFace(termfaceB);
								nfaces++;
								}

							veclayer[layertrav].vecmktri.push_back(mkTri);
							}
						}
					}	/////	Terminator	/////
				}	

            fx += scale;
            tx += td;
            i++;
			}

        fy += scale;
        ty += td;
		}

    //delete [] buffer;

#if 0	//Temporary Excluded
	////// Vertex Transmission //////
	vertices = new pVector[nverts];
    Vec2f* texc = new Vec2f[nverts];

	float tex = 0;
	float tey = 0;
	int tet = 0;
	int Vcount = 0;
	int Fcount = 0;

	/// First Layer
	for (int v=0; v < veclayer[0].vecvert.size(); v++)
		{
		if(veclayer[0].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 0) tey = 1;
		else if(veclayer[0].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 1) tey = 0;

		vertices[Vcount] = veclayer[0].vecvert[v];
		texc[Vcount].set(tex, tey);

		if(v == veclayer[0].vecvert.size() - 1)
			{
			tex = 1;
			}
		else if(tex == 0)
			{
			tex = 1 * (veclayer[0].vecvert[v][0] - veclayer[0].vecvert[v+1][0]) / scale;
			}
		else if(tex != 0)
			{
			tex = 0;
			}

		Vcount++;
		}

	veclayer[0].Vindex = Vcount;

	////// Other Layers //////
	for (layertrav = 1; layertrav < veclayer.size(); ++layertrav)	/// Add by two ?
		{
		for (int v=0; v < veclayer[layertrav].vecvert.size(); v++)
			{
			if(veclayer[layertrav].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 0) tey = 1;
			else if(veclayer[layertrav].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 1) tey = 0;

			vertices[Vcount] = veclayer[layertrav].vecvert[v];
			texc[Vcount].set(tex, tey);

			if(v == veclayer[layertrav].vecvert.size() - 1)
				{
				tex = 1;
				}
			else if(tex == 0)
				{
				tex = 1 * (veclayer[0].vecvert[v][0] - veclayer[0].vecvert[v+1][0]) / scale;
				}
			else if(tex != 0)
				{
				tex = 0;
				}

			Vcount++;
			}

		veclayer[layertrav].Vindex = Vcount;
		}

	////// Face Transmission //////
  faces = new Face3[nfaces+nseals];

	for (int f=0; f < veclayer[0].vecface.size(); f++)
		{
		faces[Fcount] = veclayer[0].vecface[f];
		Fcount++;
		}

	////// Other Layers //////
	for (layertrav = 1; layertrav < veclayer.size(); ++layertrav)
		{
		for (int f=0; f < veclayer[layertrav].vecface.size(); f++)
			{
			faces[Fcount][0] = veclayer[layertrav].vecface[f][0] + veclayer[layertrav - 1].Vindex;
			faces[Fcount][1] = veclayer[layertrav].vecface[f][1] + veclayer[layertrav - 1].Vindex;
			faces[Fcount][2] = veclayer[layertrav].vecface[f][2] + veclayer[layertrav - 1].Vindex;
			Fcount++;
			}

		if(!(layertrav & 1)) /// Layer is Even and Terminator
			{
			for (int f=0; f < veclayer[layertrav].vecseal.size(); f+=2)
				{
				faces[Fcount][0] = veclayer[layertrav].vecseal[f][0] + veclayer[layertrav - 1].Vindex;
				faces[Fcount][1] = veclayer[layertrav].vecseal[f][1] + veclayer[layertrav - 2].Vindex;
				faces[Fcount][2] = veclayer[layertrav].vecseal[f][2] + veclayer[layertrav - 2].Vindex;
				Fcount++;

				faces[Fcount][0] = veclayer[layertrav].vecseal[f + 1][0] + veclayer[layertrav - 2].Vindex;
				faces[Fcount][1] = veclayer[layertrav].vecseal[f + 1][1] + veclayer[layertrav - 1].Vindex;
				faces[Fcount][2] = veclayer[layertrav].vecseal[f + 1][2] + veclayer[layertrav - 1].Vindex;
				Fcount++;
				}
			}
		}
#endif

#if 0
	std::ostringstream ss;
    ss << "terrain/raw/x" << ix << "y" << iy << ".raw";
  	//ss << "terrain/raw/soap.trr";
    //cell->load("terrain/raw/soap.trr", x, y);

	FILE* f = fopen(ss.str().c_str(), "rb");
    if (f == 0)
    throw std::string("Failed to open terrain cell file");

  fseek(f, 0, SEEK_END);
  size_t flen = ftell(f);
  fseek(f, 0, SEEK_SET);

  int nverts2 = flen/4;
  dim = (int)sqrtf(nverts2);
  assert(dim == terrain->getCellDim());

  float* buffer = new float[nverts2];
  fread(buffer, 4, nverts2, f);
  fclose(f);
#endif

#if 0
  pVector* vertices2 = new pVector[nverts2];
  Vec2f* texc2 = new Vec2f[nverts2];
  //physverts = new NxVec3[nverts];

  fdim = m_fdim = (float)(dim-1)*scale;
  sx = -(dim-1)*scale*0.5;
  fy = sx;

  tx=0,ty=0;
  td=(1.0 / (dim-1)) * m_texscale;

  pVector cellpos = terrain->findCellCenter(ix, iy);

  i = 0;
  for (int y=0; y<dim; ++y)
  {
    float fx = sx;
    tx = 0;
    for (int x=0; x<dim; ++x)
    {
      //vertices2[i].set(fx, buffer[i]*scale, fy);
	  vertices2[i].set(fx, (rand() % 500)/100, fy);
      //physverts[i] = NxVec3(fx + cellpos[0], buffer[i]*scale + cellpos[1], fy + cellpos[2]);
      texc2[i].set(tx,ty);
      fx += scale;
      tx += td;
      ++i;
    }
    fy += scale;
    ty += td;
  }

  delete [] buffer;

  int nfaces2 = (dim-1)*(dim-1)*2;
  nseals = 0;
  Face3* faces2 = new Face3[nfaces2];
  //physfaces = new NxU32[nfaces*3];

  i = 0;
  int ti = 0;
  int pi = 0;
  for (int y=0; y<dim-1; y++)
  {
    for (int x=0; x<dim-1; x++)
    {
      faces2[ti][0] = i;
      faces2[ti][1] = i+dim;
      faces2[ti][2] = i+1;
      //physfaces[pi] = i;
      //physfaces[pi+1] = i+dim;
      //physfaces[pi+2] = i+1;
      ti++;
      pi+=3;
      faces2[ti][0] = i+1+dim;
      faces2[ti][1] = i+1;
      faces2[ti][2] = i+dim;
      //physfaces[pi] = i+1+dim;
      //physfaces[pi+1] = i+1;
      //physfaces[pi+2] = i+dim;
      ti++;
      pi+=3;
      i++;
    }
    i++;
  }
#endif

#if 0
	////// Load trrGrid //////
	trrGrid.save(filename);
#endif

	icConsoleAttribute(CONSOLE_INIT);
	printf("||-trr grid loaded %s scale %f\n", filename, scale);
	icConsoleReset();

    m_x = ix;
    m_y = iy;
    m_idx = m_y*m_terrainWidth+m_x;

    //std::cout << "  " << nverts << " verts / " << nfaces << " faces" << std::endl;

#if 0

    Game* game = Game::instance();
    if (rlock)
        game->lockRender();

	// Create a VertexAttributeSet with vertices and normals
	WritableObject<VertexAttributeSet> pVAS( CreateHandle(VertexAttributeSetHandle) );

  terrainPhysicsHdl = icPhysicsObjectCreator::instance ()->createTerrainObject (this);
  Trafo tr;
  trrGrid.m_pos = terrain->findCellCenter(m_x, m_y);
  tr.setTranslation(trrGrid.m_pos);
  WritableObject<icPhysicsObject> (terrainPhysicsHdl)->setTransform (tr);

	pVAS->setVertices( vertices, nverts );
	delete [] vertices;

	pVAS->setTexCoords( 0,2, (float*)texc, nverts );
	delete [] texc;

	//pVAS->setNormals( n, 36 );

	// Create a PrimitiveSet, in this case triangles.
	WritableObject<Triangles> pShape( CreateHandle(TrianglesHandle) );
	pShape->setVertexAttributeSet( nvutil::getHandle<VertexAttributeSetHandle>(pVAS) );
	pShape->setFaces(faces, nfaces);
	generateNormals(&*pShape);
	delete [] faces;

	//pShape->attachHighlightObject(CreateHandle(HighlightBoxHandle));

	TextureAttributeHandle* texAttribHdl = CreateHandle(TextureAttributeHandle);
		{
		WritableObject<TextureAttribute>(texAttribHdl)->bindTextureAttributeItem(terrain->getGrassTexture(),0);
		WritableObject<TextureAttribute>(texAttribHdl)->bindTextureAttributeItem(terrain->getSandTexture(),1);
		WritableObject<TextureAttribute>(texAttribHdl)->bindTextureAttributeItem(terrain->getRockTexture(),2);
		}

	// Create state set. Add material and render mode.
	WritableObject<StateSet> pStateSet( CreateHandle(StateSetHandle) );
    pStateSet->addAttribute (getCgFx ());
	pStateSet->addAttribute (texAttribHdl);

	// Setup the whole scene graph
	m_geo = CreateHandle(GeoNodeHandle);
	WritableObject<GeoNode> pGeoNode(m_geo);
	//m_geo->addRef();
	pGeoNode->addGeometry( nvutil::getHandle<nvsg::DrawableHandle>( pShape ), nvutil::getHandle<StateSetHandle>( pStateSet ) );

	WritableObject<icPhysicsObject> (terrainPhysicsHdl)->addChild (m_geo);
    terrainPhysicsHdl->addRef();

#ifndef LINUX // No PhysX under Linux yet.
	//PhysicsCookCell();
#endif

    if (rlock) game->unlockRender();
#endif
}

void unTerrainCell::acShiftCell(pVector startpos, pVector destpos)
{
#if 0
  WritableObject<icPhysicsObject> physObj (terrainPhysicsHdl);
	Trafo tr;
	trrGrid.m_pos += destpos - startpos;
	printf("trrGrid.m_pos x %f y %f z %f\n", trrGrid.m_pos[0], trrGrid.m_pos[1], trrGrid.m_pos[2]);
	tr.setTranslation(trrGrid.m_pos);
	physObj->setTransform(tr);
#endif
}

void unTerrainCell::acResetCell(void)
{
  //using namespace nvmath;
  //using namespace nvsg;
  //using namespace nvutil;

#if 0
    unTerrain* terrain = unTerrain::instance();

	/// Push first layer
	veclayer.clear();

	////// trr-end //////
	trrveclayer t_trrveclayer;

	veclayer.push_back(t_trrveclayer);

	int dim = TRR_GRID_SIZE;

    const float scale = m_scale;

    float fdim = m_fdim = (float)(dim-1)*scale;
    float sx = -(dim-1)*scale*0.5;
    float fy = sx;

    float tx=0,ty=0;
    float td=(1.0 / (dim-1)) * m_texscale;

	/// Variable declaration
	bool Exists = false;
	bool vmatch = false;
	bool xload = false;
	bool xedge = false;
	bool xspan = false;
	bool xterm = false;
	bool yedge = false;
	bool yspan = false;
	bool yterm = false;
	bool xtrail = false;
	bool xgain = false;

	int ThisVert = 0;
	int VertTrav = 0;
	int VertSpace = 0;
	int search = 0;
	int memseal = 0;
	int makeTri = 0;
	bool mkTri = false;
	pVector ThisVertex;
	pVector CheckVertex;

	Face3 faceA,faceB;
	Face3 termfaceA,termfaceB;
	Face3 sealA,sealB;

	/// Universal Binary Cube
	trrBinaryCube* bCube = new trrBinaryCube();

	/// Layer Traverser
	int layertrav = 0;
	nverts = 0;
	nfaces = 0;
	nseals = 0;

	/// Cell Floor Loading
    size_t i = 0;
    for (int y=0; y < dim; ++y)
		{
        float fx = sx;
        tx = 0;
        for (int x=0; x < dim; ++x)
			{
			/// Existance checks
			Exists = false;

			if(x == (TRR_GRID_SIZE - 1)) xterm = true;
			else xterm = false;

			/// Neighbour Existance Checks | Minor Overlap Detection and Clashing Vertex Removal
			if(x != 0 && x != (TRR_GRID_SIZE - 1) && y != 0/* && y != (TRR_GRID_SIZE - 1)*/)
				{
				xload = false;
				vmatch = false;
				for (int v=0; v < trrGrid.Grid[x+1][y-1].layers.size(); v+=2)
					{
					if(v == 0) /// First layer
						{
						if(trrGrid.Grid[x+1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[0].y_vertex) vmatch = true;
						}
					else
						{
						if(v & 1) /// Layer is Odd and Terminator
							{
							if(trrGrid.Grid[x+1][y-1].layers[v].y_vertex >= trrGrid.Grid[x][y-1].layers[0].y_vertex &&
							   trrGrid.Grid[x+1][y-1].layers[v-1].y_vertex <= trrGrid.Grid[x][y-1].layers[0].y_vertex)
								{
								vmatch = true;
								}
							}
						}
					}
				if(vmatch) { Exists = true; xload = true; }
				else
					{
					vmatch = false;
					for (int v=0; v < trrGrid.Grid[x-1][y-1].layers.size(); v+=2)
						{
						if(v == 0) /// First layer
							{
							if(trrGrid.Grid[x-1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[0].y_vertex) vmatch = true;
							}
						else
							{
							if(v & 1) /// Layer is Odd and Terminator
								{
								if(trrGrid.Grid[x-1][y-1].layers[v].y_vertex >= trrGrid.Grid[x][y-1].layers[0].y_vertex &&
								   trrGrid.Grid[x-1][y-1].layers[v-1].y_vertex <= trrGrid.Grid[x][y-1].layers[0].y_vertex)
									{
									vmatch = true;
									}
								}
							}
						}
					if(vmatch) { Exists = true; xload = true; }
					else
						{
						vmatch = false;
						for (int v=0; v < trrGrid.Grid[x][y-1].layers.size(); v+=2)
							{
							if(v == 0) /// First layer
								{
								if(trrGrid.Grid[x][y-1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
								}
							else
								{
								if(v & 1) /// Layer is Odd and Terminator
									{
									if(trrGrid.Grid[x][y-1].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
									   trrGrid.Grid[x][y-1].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
										{
										vmatch = true;
										}
									}
								}
							}
						if(vmatch) { Exists = true; }
						else
							{
							vmatch = false;
							for (int v=0; v < trrGrid.Grid[x+1][y].layers.size(); v+=2)
								{
								if(v == 0) /// First layer
									{
									if(trrGrid.Grid[x+1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
									}
								else
									{
									if(v & 1) /// Layer is Odd and Terminator
										{
										if(trrGrid.Grid[x+1][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
										   trrGrid.Grid[x+1][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
											{
											vmatch = true;
											}
										}
									}
								}
							if(vmatch) { Exists = true; }
								{
								vmatch = false;
								for (int v=0; v < trrGrid.Grid[x-1][y].layers.size(); v+=2)
									{
									if(v == 0) /// First layer
										{
										if(trrGrid.Grid[x-1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
										}
									else
										{
										if(v & 1) /// Layer is Odd and Terminator
											{
											if(trrGrid.Grid[x-1][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
											   trrGrid.Grid[x-1][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									}
								if(vmatch) Exists = true;
								else
									{
									vmatch = false;
									for (int v=0; v < trrGrid.Grid[x][y+1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x][y+1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[0].y_vertex) vmatch = true;
											}
										else
											{
											if(v & 1) /// Layer is Odd and Terminator
												{
												if(trrGrid.Grid[x][y+1].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex &&
												   trrGrid.Grid[x][y+1].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex)
													{
													vmatch = true;
													}
												}
											}
										}
									if(vmatch) Exists = true;
									else
										{
										/*/// Neighbour Five check	//HOLD LAYER HEIGHT VISIBILITY
										vmatch = false;
										for (int v=0; v < trrGrid.Grid[x][y].layers.size(); v+=2)
											{
											if(v == 0) /// First layer
												{
												if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex + trrGrid.getScale()) vmatch = true;
												}
											else
												{
												if(v & 1) /// Layer is Odd and Terminator
													{
													if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex + trrGrid.getScale() &&
													   trrGrid.Grid[x][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex + trrGrid.getScale())
														{
														vmatch = true;
														}
													}
												}
											}*/
										/*if(!vmatch) Exists = true;
										else
											{
											/// Neighbour Six check
											vmatch = false;
											for (int v=0; v < trrGrid.Grid[x][y].layers.size(); v+=2)
												{
												if(v == 0) /// First layer
													{
													if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex - trrGrid.getScale()) vmatch = true;
													}
												else
													{
													if(v & 1) /// Layer is Odd and Terminator
														{
														if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[0].y_vertex - trrGrid.getScale() &&
														   trrGrid.Grid[x][y].layers[v-1].y_vertex <= trrGrid.Grid[x][y].layers[0].y_vertex - trrGrid.getScale())
															{
															vmatch = true;
															}
														}
													}
												}
											if(!vmatch) Exists = true;
											}*/
										}
									}
								}
							}
						}
					}

				/// Generate trrBinaryCube
				if(Exists && y != (TRR_GRID_SIZE - 1))
					{
					bCube = trrGrid.SetBC(x, y, 0);
					bCube->Cook();

					for(int t=0; t < TRR_NB_TEMPLATES; ++t)
						{
						if(bCube->Compare(terrain->trrTemplateCube[t].getAngle()) == 0)
							{
							Exists = false;
							//printf("REFUSED m_angle = %i template id %i\n", bCube->getAngle(), t);
							}
						}
					}
				}
			else
				{
				Exists = true;
				bCube->setIdentity();
				bCube->Cook();
				}

			/// Set first layer faces
			if(Exists)
				{
				veclayer[0].addVert(fx, trrGrid.Grid[x][y].layers[0].y_vertex, fy);
				veclayer[0].vecsearch.push_back(0);
				veclayer[0].vecxload.push_back(xload);
				veclayer[0].vecxterm.push_back(xterm);
				veclayer[0].addBC(bCube);
				nverts++;

				ThisVert = veclayer[0].vecvert.size() - 1;
				VertTrav = veclayer[0].vecvert.size() - 3;

				VertSpace = 0;
				search = 0;
				mkTri = false;

				/// Optimise Add edge convertion
				if(x > 0 && y > 0 && VertTrav >= 0)
					{
					faceA.m_v1 = faceB.m_v3 = ThisVert;					/// Floor Vertex Assignment 1
					faceB.m_v2 = ThisVert - 1;						/// Floor Vertex Assignment 2

					ThisVertex = veclayer[0].vecvert[ThisVert - 1];
					CheckVertex = veclayer[0].vecvert[ThisVert];

					while(VertTrav >= 0)
						{
						if(veclayer[0].vecvert[VertTrav][0] >= veclayer[0].vecvert[ThisVert - 1][0] || VertTrav == 0 || veclayer[0].vecvert[VertTrav][1] != CheckVertex[1])
							search++;

						if(search < 1)	////// Simularity Checks //////
							{
							if(veclayer[0].vecvert[VertTrav][2] == ThisVertex[2] && veclayer[0].vecvert[VertTrav][1] == ThisVertex[1] && veclayer[0].vecvert[VertTrav][1] == CheckVertex[1] && !veclayer[0].vecxload[veclayer[0].vecface[veclayer[0].vecface.size() - 1][2]] && veclayer[0].vecvert[veclayer[0].vecface[veclayer[0].vecface.size() - 1][1]][0] != sx)	//24/06/07 Added Deconstructive change //ARCHIVE:  && !veclayer[0].vecxedge[VertTrav] //ARCHIVE:   && !veclayer[0].vecxload[veclayer[0].vecface[VertTrav+1][0]
								{
								int makeTri = veclayer[0].vecmktri.size() - 1;
								if(makeTri >= 0)
									{
									faceB.m_v2 = veclayer[0].vecface[veclayer[0].vecface.size() - 1][1];		/// Floor Vertex Assignment 2

									if(veclayer[0].vecmktri[makeTri])
										{
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 1][0]]--;
										veclayer[0].clearFace();
										nfaces--;
										}
									else
										{
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 1][0]]--;
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 2][1]]--;
										veclayer[0].vecsearch[veclayer[0].vecface[veclayer[0].vecface.size() - 2][2]]--;
										veclayer[0].clearFace();
										veclayer[0].clearFace();
										nfaces-=2;
										}

									VertTrav = faceB.m_v2;

									veclayer[0].vecmktri.pop_back();
									}
								else faceB.m_v2 = VertTrav;
								search++;
								VertTrav--;
								}
							else
								{
								search++;
								VertTrav--;
								}
							}
						else
							{
							if((veclayer[0].vecvert[VertTrav][0] == veclayer[0].vecvert[faceB.m_v2][0] && veclayer[0].vecsearch[VertTrav] < 3) ||
							   (veclayer[0].vecvert[VertTrav][0] == veclayer[0].vecvert[faceB.m_v2][0] && veclayer[0].vecsearch[VertTrav + 1] < 1))
								{
								faceA.m_v3 = VertTrav;							/// Vertex Assignment 3
								faceB.m_v1 = VertTrav;							/// Vertex Assignment 3
								veclayer[0].vecsearch[VertTrav]++;
								VertTrav = -1;
								}
							else
								{
								if((veclayer[0].vecvert[VertTrav][2] < veclayer[0].vecvert[faceB.m_v2][2]) && (veclayer[0].vecvert[VertTrav][0] < veclayer[0].vecvert[faceB.m_v2][0]))
									{
									VertSpace = VertTrav;

									if(veclayer[0].vecvert[VertSpace][2] >= veclayer[0].vecvert[faceB.m_v2][2])
										VertSpace = faceB.m_v2;

									while(VertSpace < faceB.m_v2)
										{
										if(veclayer[0].vecsearch[VertSpace] < 1)
											{
											faceA.m_v3 = VertSpace;				/// Vertex Assignment 3
											faceB.m_v1 = VertSpace;				/// Vertex Assignment 3
											veclayer[0].vecsearch[VertSpace]++;
											VertSpace = faceB.m_v2;
											}
										else
											{
											if((/*veclayer[0].vecxterm[VertSpace] &&*/ veclayer[0].vecvert[VertSpace][0] >= veclayer[0].vecvert[faceB.m_v2][0]) ||
											   (veclayer[0].vecsearch[VertSpace] < 2 && veclayer[0].vecvert[VertSpace][0] == veclayer[0].vecvert[faceB.m_v3][0]))
												{
												faceA.m_v3 = VertSpace;
												faceB.m_v1 = VertSpace;			/// Vertex Assignment 3
												veclayer[0].vecsearch[VertSpace]++;
												VertSpace = faceB.m_v2;
												mkTri = true;
												}
											}
										VertSpace++;
										}
									VertTrav = -1;
									}
								}
							}
						VertTrav--;
						}

					VertTrav = veclayer[0].vecvert.size() - 2;
					VertSpace = 0;
					search = 0;

					while(VertTrav >= 0 && !mkTri)	/// Locate Fourth Vertex
						{
						if(veclayer[0].vecvert[VertTrav][0] >= veclayer[0].vecvert[ThisVert][0])
							search = 1;

						if(search > 0)
							{
							if(veclayer[0].vecvert[VertTrav][0] == veclayer[0].vecvert[ThisVert][0] &&
								veclayer[0].vecsearch[VertTrav] < 2)
								{
								faceA.m_v2 = VertTrav;							/// Vertex Assignment 4
								veclayer[0].vecsearch[VertTrav]++;
								VertTrav = -1;
								}
							else
								{
								if(veclayer[0].vecvert[VertTrav][0] < veclayer[0].vecvert[ThisVert][0])
									{
									VertSpace = VertTrav;

									if(veclayer[0].vecvert[VertSpace][2] >= veclayer[0].vecvert[ThisVert][2])
										VertSpace = ThisVert;

									while(VertSpace < ThisVert)
										{
										if(veclayer[0].vecsearch[VertSpace] == 0)
											{
											faceA.m_v2 = VertSpace;				/// Vertex Assignment 4
											veclayer[0].vecsearch[VertSpace]++;
											VertSpace = ThisVert;
											}
										VertSpace++;
										}

									VertTrav = -1;
									}
								}
							}
						VertTrav--;
						}

					if(!mkTri)
						{
						veclayer[0].addFace(faceA);
						veclayer[0].addFace(faceB);
						nfaces+=2;
						}
					else
						{
						veclayer[0].addFace(faceB);
						nfaces++;
						}

					veclayer[0].vecmktri.push_back(mkTri);
					}
				}

			///////// Other Layer Vertices /////////
			for (layertrav = 1; layertrav < trrGrid.Grid[x][y].layers.size(); ++layertrav)	/// Add by two ?
				{
				if(layertrav & 1) /// Layer is Odd and Instigator
					{			/////	Instigator	/////
					/// Existance checks
					Exists = false;
					xedge = true;
					xspan = true;
					yedge = true;
					yspan = true;
					yterm = true;
					xtrail = true;
					xgain = true;

					if(x == (TRR_GRID_SIZE - 1)) xterm = true;
					else xterm = false;

					/// Neighbour Existance Checks | Minor Overlap Detection and Clashing Vertex Removal
					if(x != 0 && x != (TRR_GRID_SIZE - 1) && y != 0)
						{
						///// Extents Divisal /////
						if(!xterm)
							{ xterm = true;
							for (int v=0; v < trrGrid.Grid[x+1][y].layers.size(); ++v)
								if(v == layertrav) xterm = false; }

						for (int v=0; v < trrGrid.Grid[x][y-1].layers.size(); ++v)
							if(v == layertrav) yedge = false;

						for (int v=0; v < trrGrid.Grid[x][y-2].layers.size(); ++v)
							if(v == layertrav) yspan = false;

						for (int v=0; v < trrGrid.Grid[x][y+1].layers.size(); ++v)
							if(v == layertrav) yterm = false;

						for (int v=0; v < trrGrid.Grid[x-1][y].layers.size(); ++v)
							if(v == layertrav) xedge = false;

						for (int v=0; v < trrGrid.Grid[x-2][y].layers.size(); ++v)
							if(v == layertrav) xspan = false;

						for (int v=0; v < trrGrid.Grid[x-1][y-1].layers.size(); ++v)
							if(v == layertrav) xtrail = false;

						for (int v=0; v < trrGrid.Grid[x+1][y-1].layers.size(); ++v)
							if(v == layertrav) xgain = false;

						if(!xedge && !xterm && !yedge)
							{
							xload = false;
							if(!xgain)
								{
								vmatch = false;
								for (int v=1; v < trrGrid.Grid[x+1][y-1].layers.size(); v+=2)
									{
									if(v == 0) /// First layer
										{
										if(trrGrid.Grid[x+1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
										}
									else
										{
										if(trrGrid.Grid[x+1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
											{
											vmatch = true;
											}
										}
									}
								}
							else vmatch = true;
							if(vmatch) { Exists = true; xload = true; }
							else
								{
								if(!xtrail)
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x-1][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x-1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x-1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									}
								else vmatch = true;
								if(vmatch) { Exists = true; xload = true; }
								else
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									if(vmatch) { Exists = true; }
									else
										{
										vmatch = false;
										for (int v=1; v < trrGrid.Grid[x+1][y].layers.size(); v+=2)
											{
											if(v == 0) /// First layer
												{
												if(trrGrid.Grid[x+1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
												}
											else
												{
												if(trrGrid.Grid[x+1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
													{
													vmatch = true;
													}
												}
											}
										if(vmatch) { Exists = true; }
										else
											{
											vmatch = false;
											for (int v=1; v < trrGrid.Grid[x-1][y].layers.size(); v+=2)
												{
												if(v == 0) /// First layer
													{
													if(trrGrid.Grid[x-1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
													}
												else
													{
													if(trrGrid.Grid[x-1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
														{
														vmatch = true;
														}
													}
												}
											if(vmatch) Exists = true;
											else
												{
												vmatch = false;
												for (int v=1; v < trrGrid.Grid[x][y+1].layers.size(); v+=2)
													{
													if(v == 0) /// First layer
														{
														if(trrGrid.Grid[x][y+1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
														}
													else
														{
														if(trrGrid.Grid[x][y+1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
															{
															vmatch = true;
															}
														}
													}
												if(vmatch) Exists = true;
												else
													{
													/*/// Neighbour Five check	//HOLD LAYER HEIGHT VISIBILITY
													vmatch = false;
													for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
														{
														if(v == 0) /// First layer
															{
															if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale()) vmatch = true;
															}
														else
															{
															if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale())
																{
																vmatch = true;
																}
															}
														}*/
													/*if(!vmatch) Exists = true;
													else
														{
														/// Neighbour Six check
														vmatch = false;
														for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
															{
															if(v == 0) /// First layer
																{
																if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale()) vmatch = true;
																}
															else
																{
																if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale())
																	{
																	vmatch = true;
																	}
																}
															}
														if(!vmatch) Exists = true;
														}*/
													}
												}
											}
										}
									}
								}

							/// Generate trrBinaryCube
							if(Exists && y != (TRR_GRID_SIZE - 1))
								{
								bCube = trrGrid.SetBC(x, y, layertrav);
								bCube->Cook();

								for(int t=0; t < TRR_NB_TEMPLATES; ++t)
									{
									if(bCube->Compare(terrain->trrTemplateCube[t].getAngle()) == 0)
										{
										Exists = false;
										//printf("REFUSED m_angle = %i template id %i\n", bCube->getAngle(), t);
										}
									}
								}
							}
						else
							{
							Exists = true;
							bCube->setIdentity();
							bCube->Cook();
							}
						}
					else	/// Optimise Tail Refusal BC
						{
						Exists = true;
						bCube->setIdentity();
						bCube->Cook();
						}

					/// Existance Checks
					if(Exists)
						{
						if(layertrav + 1 > veclayer.size())
							{
							trrveclayer t_trrveclayer;

							t_trrveclayer.addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							t_trrveclayer.vecsearch.push_back(0);
							t_trrveclayer.vecxload.push_back(xload);
							t_trrveclayer.vecxedge.push_back(xedge);
							t_trrveclayer.vecxterm.push_back(xterm);
							t_trrveclayer.addBC(bCube);
							nverts++;

							veclayer.push_back( t_trrveclayer );
							}
						else
							{
							veclayer[layertrav].addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							veclayer[layertrav].vecsearch.push_back(0);
							veclayer[layertrav].vecxload.push_back(xload);
							veclayer[layertrav].vecxedge.push_back(xedge);
							veclayer[layertrav].vecxterm.push_back(xterm);
							veclayer[layertrav].addBC(bCube);
							nverts++;
							}

						ThisVert = veclayer[layertrav].vecvert.size() - 1;
						VertTrav = veclayer[layertrav].vecvert.size() - 3;

						VertSpace = 0;
						search = 0;
						mkTri = false;

						/// Optimise Add edge convertion | Combine three booleans? point??
						if(!xedge && !yedge && VertTrav >= 0)
							{
							faceA.m_v1 = faceB.m_v2 = ThisVert;					/// Floor Vertex Assignment 1
							faceB.m_v3 = ThisVert - 1;						/// Floor Vertex Assignment 2

							ThisVertex = veclayer[layertrav].vecvert[ThisVert - 1];
							CheckVertex = veclayer[layertrav].vecvert[ThisVert];

							while(VertTrav >= 0)
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert - 1][0] || VertTrav == 0 || veclayer[layertrav].vecvert[VertTrav][1] != CheckVertex[1])
									search++;

								if(search < 1)	////// Simularity Checks //////
									{
									if(veclayer[layertrav].vecvert[VertTrav][2] == ThisVertex[2] && veclayer[layertrav].vecvert[VertTrav][1] == ThisVertex[1] && veclayer[layertrav].vecvert[VertTrav][1] == CheckVertex[1] && !veclayer[layertrav].vecxload[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][1]] && !veclayer[layertrav].vecxedge[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][2]])	//24/06/07 Added Deconstructive change //ARCHIVE:  && !veclayer[0].vecxedge[VertTrav] //ARCHIVE:   && !veclayer[0].vecxload[veclayer[0].vecface[VertTrav+1][0]
										{
										int makeTri = veclayer[layertrav].vecmktri.size() - 1;
										if(makeTri >= 0)
											{
											faceB.m_v3 = veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][2];		/// Floor Vertex Assignment 2

											if(veclayer[layertrav].vecmktri[makeTri])
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][0]]--;
												veclayer[layertrav].clearFace();
												nfaces--;
												}
											else
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][0]]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2][1]]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2][2]]--;
												veclayer[layertrav].clearFace();
												veclayer[layertrav].clearFace();
												nfaces-=2;
												}

											VertTrav = faceB.m_v3;

											veclayer[layertrav].vecmktri.pop_back();
											}
										else faceB.m_v3 = VertTrav;
										search++;
										VertTrav--;
										}
									else
										{
										search++;
										VertTrav--;
										}
									}
								else
									{
									if((veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[faceB.m_v3][0] && veclayer[layertrav].vecsearch[VertTrav] < 3) ||
									   (veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[faceB.m_v3][0] && veclayer[layertrav].vecsearch[VertTrav + 1] < 1))
										{
										faceA.m_v2 = VertTrav;							/// Vertex Assignment 3
										faceB.m_v1 = VertTrav;							/// Vertex Assignment 3
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if((veclayer[layertrav].vecvert[VertTrav][2] < veclayer[layertrav].vecvert[faceB.m_v3][2]) && (veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[faceB.m_v3][0]))
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[faceB.m_v3][2])
												VertSpace = faceB.m_v3;

											while(VertSpace < faceB.m_v3)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] < 1)
													{
													faceA.m_v2 = VertSpace;				/// Vertex Assignment 3
													faceB.m_v1 = VertSpace;				/// Vertex Assignment 3
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = faceB.m_v3;
													}
												else
													{
													if((/*veclayer[layertrav].vecxterm[VertSpace] &&*/ veclayer[layertrav].vecvert[VertSpace][0] >= veclayer[layertrav].vecvert[faceB.m_v3][0]) ||
													   (veclayer[layertrav].vecsearch[VertSpace] < 2 && veclayer[layertrav].vecvert[VertSpace][0] == veclayer[layertrav].vecvert[faceB.m_v2][0]))
														{
														faceA.m_v2 = VertSpace;
														faceB.m_v1 = VertSpace;			/// Vertex Assignment 3
														veclayer[layertrav].vecsearch[VertSpace]++;
														VertSpace = faceB.m_v3;
														mkTri = true;
														}
													}
												VertSpace++;
												}
											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							VertTrav = veclayer[layertrav].vecvert.size() - 2;
							VertSpace = 0;
							search = 0;

							while(VertTrav >= 0 && !mkTri)	/// Locate Fourth Vertex
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert][0])
									search = 1;

								if(search > 0)
									{
									if(veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[ThisVert][0] &&
										veclayer[layertrav].vecsearch[VertTrav] < 2)
										{
										faceA.m_v3 = VertTrav;							/// Vertex Assignment 4
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if(veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[ThisVert][0])
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[ThisVert][2])
												VertSpace = ThisVert;

											while(VertSpace < ThisVert)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] == 0)
													{
													faceA.m_v3 = VertSpace;				/// Vertex Assignment 4
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = ThisVert;
													}
												VertSpace++;
												}

											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							if(!mkTri)
								{
								veclayer[layertrav].addFace(faceA);
								veclayer[layertrav].addFace(faceB);
								nfaces+=2;
								}
							else
								{
								veclayer[layertrav].addFace(faceB);
								nfaces++;
								}

							veclayer[layertrav].vecmktri.push_back(mkTri);
							}
						}
					}	///// Instigator /////
				else
					{	///// Terminator /////
					/// Existance checks
					Exists = false;
					xedge = true;
					yedge = true;
					yspan = true;
					yterm = true;
					xtrail = true;
					xgain = true;

					if(x == (TRR_GRID_SIZE - 1)) xterm = true;
					else xterm = false;

					/// Neighbour Existance Checks | Minor Overlap Detection and Clashing Vertex Removal
					if(x != 0 && x != (TRR_GRID_SIZE - 1) && y != 0)
						{
						///// Extents Divisal /////
						if(!xterm)
							{ xterm = true;
							for (int v=0; v < trrGrid.Grid[x+1][y].layers.size(); ++v)
								if(v == layertrav) xterm = false; }

						for (int v=0; v < trrGrid.Grid[x][y-1].layers.size(); ++v)
							if(v == layertrav) yedge = false;

						for (int v=0; v < trrGrid.Grid[x][y-2].layers.size(); ++v)
							if(v == layertrav) yspan = false;

						for (int v=0; v < trrGrid.Grid[x][y+1].layers.size(); ++v)
							if(v == layertrav) yterm = false;

						for (int v=0; v < trrGrid.Grid[x-1][y].layers.size(); ++v)
							if(v == layertrav) xedge = false;

						for (int v=0; v < trrGrid.Grid[x-1][y-1].layers.size(); ++v)
							if(v == layertrav) xtrail = false;

						for (int v=0; v < trrGrid.Grid[x+1][y-1].layers.size(); ++v)
							if(v == layertrav) xgain = false;

						if(!xedge && !xterm && !yedge)
							{
							xload = false;
							if(!xgain)
								{
								vmatch = false;
								for (int v=1; v < trrGrid.Grid[x+1][y-1].layers.size(); v+=2)
									{
									if(v == 0) /// First layer
										{
										if(trrGrid.Grid[x+1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
										}
									else
										{
										if(trrGrid.Grid[x+1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
											{
											vmatch = true;
											}
										}
									}
								}
							else vmatch = true;
							if(vmatch) { Exists = true; xload = true; }
							else
								{
								if(!xgain)
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x-1][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x-1][y-1].layers[v].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x-1][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y-1].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									}
								else vmatch = true;
								if(vmatch) { Exists = true; xload = true; }
								else
									{
									vmatch = false;
									for (int v=1; v < trrGrid.Grid[x][y-1].layers.size(); v+=2)
										{
										if(v == 0) /// First layer
											{
											if(trrGrid.Grid[x][y-1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
											}
										else
											{
											if(trrGrid.Grid[x][y-1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
												{
												vmatch = true;
												}
											}
										}
									if(vmatch) { Exists = true; }
									else
										{
										vmatch = false;
										for (int v=1; v < trrGrid.Grid[x+1][y].layers.size(); v+=2)
											{
											if(v == 0) /// First layer
												{
												if(trrGrid.Grid[x+1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
												}
											else
												{
												if(trrGrid.Grid[x+1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
													{
													vmatch = true;
													}
												}
											}
										if(vmatch) { Exists = true; }
										else
											{
											vmatch = false;
											for (int v=1; v < trrGrid.Grid[x-1][y].layers.size(); v+=2)
												{
												if(v == 0) /// First layer
													{
													if(trrGrid.Grid[x-1][y].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
													}
												else
													{
													if(trrGrid.Grid[x-1][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
														{
														vmatch = true;
														}
													}
												}
											if(vmatch) Exists = true;
											else
												{
												vmatch = false;
												for (int v=1; v < trrGrid.Grid[x][y+1].layers.size(); v+=2)
													{
													if(v == 0) /// First layer
														{
														if(trrGrid.Grid[x][y+1].layers[v].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex) vmatch = true;
														}
													else
														{
														if(trrGrid.Grid[x][y+1].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex)
															{
															vmatch = true;
															}
														}
													}
												if(vmatch) Exists = true;
												else
													{
													/*/// Neighbour Five check	//HOLD LAYER HEIGHT VISIBILITY
													vmatch = false;
													for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
														{
														if(v == 0) /// First layer
															{
															if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale()) vmatch = true;
															}
														else
															{
															if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex + trrGrid.getScale())
																{
																vmatch = true;
																}
															}
														}*/
													/*if(!vmatch) Exists = true;
													else
														{
														/// Neighbour Six check
														vmatch = false;
														for (int v=1; v < trrGrid.Grid[x][y].layers.size(); v+=2)
															{
															if(v == 0) /// First layer
																{
																if(trrGrid.Grid[x][y].layers[v].y_vertex >= trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale()) vmatch = true;
																}
															else
																{
																if(trrGrid.Grid[x][y].layers[layertrav].y_vertex != trrGrid.Grid[x][y].layers[layertrav].y_vertex - trrGrid.getScale())
																	{
																	vmatch = true;
																	}
																}
															}
														if(!vmatch) Exists = true;
														}*/
													}
												}
											}
										}
									}
								}

							/// Generate trrBinaryCube
							if(Exists && y != (TRR_GRID_SIZE - 1))
								{
								bCube = trrGrid.SetBC(x, y, layertrav);
								bCube->Cook();

								for(int t=0; t < TRR_NB_TEMPLATES; ++t)
									{
									if(bCube->Compare(terrain->trrTemplateCube[t].getAngle()) == 0)
										{
										Exists = false;
										//printf("REFUSED m_angle = %i template id %i\n", bCube->getAngle(), t);
										}
									}
								}
							}
						else
							{
							Exists = true;
							bCube->setIdentity();
							bCube->Cook();
							}
						}
					else
						{
						Exists = true;
						bCube->setIdentity();
						bCube->Cook();
						}

					/// Existance Checks
					if(Exists)
						{
						if(layertrav + 1 > veclayer.size())
							{
							trrveclayer t_trrveclayer;

							t_trrveclayer.addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							t_trrveclayer.vecsearch.push_back(0);
							t_trrveclayer.vecxload.push_back(xload);
							t_trrveclayer.vecxedge.push_back(xedge);
							t_trrveclayer.vecxterm.push_back(xterm);
							t_trrveclayer.addBC(bCube);
							nverts++;

							veclayer.push_back( t_trrveclayer );
							}
						else
							{
							veclayer[layertrav].addVert(fx, trrGrid.Grid[x][y].layers[layertrav].y_vertex, fy);
							veclayer[layertrav].vecsearch.push_back(0);
							veclayer[layertrav].vecxload.push_back(xload);
							veclayer[layertrav].vecxedge.push_back(xedge);
							veclayer[layertrav].vecxterm.push_back(xterm);
							veclayer[layertrav].addBC(bCube);
							nverts++;
							}

						ThisVert = veclayer[layertrav].vecvert.size() - 1;
						VertTrav = veclayer[layertrav].vecvert.size() - 3;

						VertSpace = 0;
						search = 0;
						mkTri = false;

						/// Optimise Add edge convertion
						if(!xedge && !yedge && VertTrav >= 0)
							{
							termfaceA.m_v1 = termfaceB.m_v3 = ThisVert;					/// Floor Vertex Assignment 1
							termfaceB.m_v2 = ThisVert - 1;						/// Floor Vertex Assignment 2

							ThisVertex = veclayer[layertrav].vecvert[ThisVert - 1];
							CheckVertex = veclayer[layertrav].vecvert[ThisVert];

							while(VertTrav >= 0)
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert - 1][0] || VertTrav == 0 || veclayer[layertrav].vecvert[VertTrav][1] != CheckVertex[1])
									search++;

								if(search < 1)	////// Simularity Checks //////
									{
									if(veclayer[layertrav].vecvert[VertTrav][2] == ThisVertex[2] && veclayer[layertrav].vecvert[VertTrav][1] == ThisVertex[1] && veclayer[layertrav].vecvert[VertTrav][1] == CheckVertex[1] && !veclayer[layertrav].vecxload[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][2]] && !veclayer[layertrav].vecxedge[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][1]])	//24/06/07 Added Deconstructive change //ARCHIVE:  && !veclayer[0].vecxedge[VertTrav] //ARCHIVE:   && !veclayer[0].vecxload[veclayer[0].vecface[VertTrav+1][0]
										{
										int makeTri = veclayer[layertrav].vecmktri.size() - 1;
										if(makeTri >= 0)
											{
											termfaceB.m_v2 = veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][1];		/// Floor Vertex Assignment 2

											if(veclayer[layertrav].vecmktri[makeTri])
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][0]]--;
												veclayer[layertrav].clearFace();
												nfaces--;
												}
											else
												{
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 1][0]]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2][1]]--;
												veclayer[layertrav].vecsearch[veclayer[layertrav].vecface[veclayer[layertrav].vecface.size() - 2][2]]--;
												veclayer[layertrav].clearFace();
												veclayer[layertrav].clearFace();
												nfaces-=2;

												for(; memseal > 0; --memseal)
													{
													veclayer[layertrav].clearSeal();
													veclayer[layertrav].clearSeal();
													nseals-=2;
													}
												}

											VertTrav = termfaceB.m_v2;

											veclayer[layertrav].vecmktri.pop_back();
											}
										else termfaceB.m_v2 = VertTrav;
										search++;
										VertTrav--;
										}
									else
										{
										search++;
										VertTrav--;
										}
									}
								else
									{
								    if((veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[termfaceB.m_v2][0] && veclayer[layertrav].vecsearch[VertTrav] < 3) ||
									   (veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[termfaceB.m_v2][0] && veclayer[layertrav].vecsearch[VertTrav + 1] < 1))
										{
										termfaceA.m_v3 = VertTrav;							/// Vertex Assignment 3
										termfaceB.m_v1 = VertTrav;							/// Vertex Assignment 3
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if((veclayer[layertrav].vecvert[VertTrav][2] < veclayer[layertrav].vecvert[termfaceB.m_v2][2]) && (veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[termfaceB.m_v2][0]))
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[termfaceB.m_v2][2])
												VertSpace = termfaceB.m_v2;

											while(VertSpace < termfaceB.m_v2)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] < 1)
													{
													termfaceA.m_v3 = VertSpace;				/// Vertex Assignment 3
													termfaceB.m_v1 = VertSpace;				/// Vertex Assignment 3
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = termfaceB.m_v2;
													}
												else
													{
													if((/*veclayer[layertrav].vecxterm[VertSpace] &&*/ veclayer[layertrav].vecvert[VertSpace][0] >= veclayer[layertrav].vecvert[termfaceB.m_v2][0]) ||
													   (veclayer[layertrav].vecsearch[VertSpace] < 2 && veclayer[layertrav].vecvert[VertSpace][0] == veclayer[layertrav].vecvert[termfaceB.m_v3][0]))
														{
														termfaceA.m_v3 = VertSpace;
														termfaceB.m_v1 = VertSpace;			/// Vertex Assignment 3
														veclayer[layertrav].vecsearch[VertSpace]++;
														VertSpace = termfaceB.m_v2;
														mkTri = true;
														}
													}
												VertSpace++;
												}
											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							VertTrav = veclayer[layertrav].vecvert.size() - 2;
							VertSpace = 0;
							search = 0;

							while(VertTrav >= 0 && !mkTri)	/// Locate Fourth Vertex
								{
								if(veclayer[layertrav].vecvert[VertTrav][0] >= veclayer[layertrav].vecvert[ThisVert][0])
									search = 1;

								if(search > 0)
									{
									if(veclayer[layertrav].vecvert[VertTrav][0] == veclayer[layertrav].vecvert[ThisVert][0] &&
										veclayer[layertrav].vecsearch[VertTrav] < 2)
										{
										termfaceA.m_v2 = VertTrav;							/// Vertex Assignment 4
										veclayer[layertrav].vecsearch[VertTrav]++;
										VertTrav = -1;
										}
									else
										{
										if(veclayer[layertrav].vecvert[VertTrav][0] < veclayer[layertrav].vecvert[ThisVert][0])
											{
											VertSpace = VertTrav;

											if(veclayer[layertrav].vecvert[VertSpace][2] >= veclayer[layertrav].vecvert[ThisVert][2])
												VertSpace = ThisVert;

											while(VertSpace < ThisVert)
												{
												if(veclayer[layertrav].vecsearch[VertSpace] == 0)
													{
													termfaceA.m_v2 = VertSpace;				/// Vertex Assignment 4
													veclayer[layertrav].vecsearch[VertSpace]++;
													VertSpace = ThisVert;
													}
												VertSpace++;
												}

											VertTrav = -1;
											}
										}
									}
								VertTrav--;
								}

							/// Seal Memory
							memseal = 0;

							if(!mkTri)
								{
								veclayer[layertrav].addFace(termfaceA);
								veclayer[layertrav].addFace(termfaceB);
								nfaces+=2;

								////// Layer Connection Seal //////
								if(yspan)
									{
									sealA.m_v1 = termfaceA.m_v2;
									sealA.m_v2 = faceA.m_v3;
									sealA.m_v3 = faceA.m_v2;

									sealA.m_v1 = faceA.m_v2;
									sealA.m_v2 = termfaceA.m_v3;
									sealA.m_v3 = termfaceA.m_v2;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}

								if(yterm)
									{
									sealA.m_v1 = faceA.m_v1;
									sealA.m_v2 = termfaceB.m_v2;
									sealA.m_v3 = termfaceA.m_v1;

									sealA.m_v1 = termfaceB.m_v2;
									sealA.m_v2 = faceA.m_v1;
									sealA.m_v3 = faceB.m_v3;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}

								if(xspan)
									{
									sealA.m_v1 = termfaceB.m_v2;
									sealA.m_v2 = termfaceA.m_v3;
									sealA.m_v3 = faceB.m_v3;

									sealA.m_v1 = faceA.m_v2;
									sealA.m_v2 = faceB.m_v3;
									sealA.m_v3 = termfaceB.m_v1;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}

								if(xterm)
									{
									sealA.m_v1 = faceA.m_v3;
									sealA.m_v2 = faceB.m_v2;
									sealA.m_v3 = termfaceA.m_v2;

									sealA.m_v1 = termfaceA.m_v1;
									sealA.m_v2 = termfaceA.m_v2;
									sealA.m_v3 = faceB.m_v2;

									veclayer[layertrav].addSeal(sealA);
									veclayer[layertrav].addSeal(sealB);
									nseals+=2;
									memseal++;
									}
								}
							else
								{
								veclayer[layertrav].addFace(termfaceB);
								nfaces++;
								}

							veclayer[layertrav].vecmktri.push_back(mkTri);
							}
						}
					}	/////	Terminator	/////
				}	

            fx += scale;
            tx += td;
            i++;
			}

        fy += scale;
        ty += td;
		}

	////// Vertex Transmission //////
    //pVector* verts = new pVector[nverts];
	vertices = new pVector[nverts];
    Vec2f* texc = new Vec2f[nverts];

	int tex = 0;
	int tey = 0;
	int tet = 0;
	int texcount = 0;
	int Vcount = 0;
	int Fcount = 0;

	/// First Layer
	for (int v=0; v < veclayer[0].vecvert.size(); v++)
		{
		if(veclayer[0].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 0) tey = 1;
		else if(veclayer[0].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 1) tey = 0;

		vertices[Vcount] = veclayer[0].vecvert[v];
		texc[Vcount].set(tex, tey);

		if(v == veclayer[0].vecvert.size() - 1)
			{
			tex = 1;
			}
		else if(tex == 0)
			{
			tex = 1;// * (veclayer[0].vecvert[v][0] - veclayer[0].vecvert[v+1][0]) / scale;
			}
		else if(tex != 0)
			{
			tex = 0;
			}

		Vcount++;
		}

	veclayer[0].Vindex = Vcount;

	////// Other Layers //////
	for (layertrav = 1; layertrav < veclayer.size(); ++layertrav)	/// Add by two ?
		{
		for (int v=0; v < veclayer[layertrav].vecvert.size(); v++)
			{
			if(veclayer[layertrav].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 0) tey = 1;
			else if(veclayer[layertrav].vecvert[v][0] == (-(dim-1)*scale*0.5) + ((dim-1)*scale) && tey == 1) tey = 0;

			vertices[Vcount] = veclayer[layertrav].vecvert[v];
			texc[Vcount].set(tex, tey);

			if(v == veclayer[layertrav].vecvert.size() - 1)
				{
				tex = 1;
				}
			else if(tex == 0)
				{
				tex = 1;// * (veclayer[0].vecvert[v][0] - veclayer[0].vecvert[v+1][0]) / scale;
				}
			else if(tex != 0)
				{
				tex = 0;
				}

			Vcount++;
			}

		veclayer[layertrav].Vindex = Vcount;
		}

	////// Face Transmission //////
  faces = new Face3[nfaces+nseals];
	int phystrav = 0;
	
	for (int f=0; f < veclayer[0].vecface.size(); f++)
		{
		faces[Fcount] = veclayer[0].vecface[f];
		Fcount++;
		}

	////// Other Layers //////
	for (layertrav = 1; layertrav < veclayer.size(); ++layertrav)
		{
		for (int f=0; f < veclayer[layertrav].vecface.size(); f++)
			{
			faces[Fcount][0] = veclayer[layertrav].vecface[f][0] + veclayer[layertrav - 1].Vindex;
			faces[Fcount][1] = veclayer[layertrav].vecface[f][1] + veclayer[layertrav - 1].Vindex;
			faces[Fcount][2] = veclayer[layertrav].vecface[f][2] + veclayer[layertrav - 1].Vindex;
			Fcount++;
			}

		if(!(layertrav & 1)) /// Layer is Even and Terminator
			{
			for (int f=0; f < veclayer[layertrav].vecseal.size(); f+=2)
				{
				faces[Fcount][0] = veclayer[layertrav].vecseal[f][0] + veclayer[layertrav - 1].Vindex;
				faces[Fcount][1] = veclayer[layertrav].vecseal[f][1] + veclayer[layertrav - 2].Vindex;
				faces[Fcount][2] = veclayer[layertrav].vecseal[f][2] + veclayer[layertrav - 2].Vindex;
				Fcount++;

				faces[Fcount][0] = veclayer[layertrav].vecseal[f + 1][0] + veclayer[layertrav - 2].Vindex;
				faces[Fcount][1] = veclayer[layertrav].vecseal[f + 1][1] + veclayer[layertrav - 1].Vindex;
				faces[Fcount][2] = veclayer[layertrav].vecseal[f + 1][2] + veclayer[layertrav - 1].Vindex;
				Fcount++;
				}
			}
		}

#if 0
	////// Load trrGrid //////
	trrGrid.save(filename);
#endif

	icConsoleAttribute(CONSOLE_INIT);
	printf("||-trr grid reset\n");
	icConsoleReset();

    Game* game = Game::instance();
    /*if (rlock)*/ game->lockRender();

	// Create a VertexAttributeSet with vertices and normals
	WritableObject<VertexAttributeSet> pVAS( CreateHandle(VertexAttributeSetHandle) );
  
  Game::instance ()->removeRootChild (terrainPhysicsHdl);
  terrainPhysicsHdl->removeRef ();
  terrainPhysicsHdl = icPhysicsObjectCreator::instance ()->createTerrainObject (this);
  Trafo tr;
  trrGrid.m_pos = terrain->findCellCenter(m_x, m_y);
  tr.setTranslation(trrGrid.m_pos);
  WritableObject<icPhysicsObject> (terrainPhysicsHdl)->setTransform (tr);

	pVAS->setVertices( vertices, nverts );
	delete [] vertices;

	pVAS->setTexCoords( 0,2, (float*)texc, nverts );
	delete [] texc;

	// Create a PrimitiveSet, in this case triangles.
	WritableObject<Triangles> pShape( CreateHandle(TrianglesHandle) );
	pShape->setVertexAttributeSet( nvutil::getHandle<VertexAttributeSetHandle>(pVAS) );
	pShape->setFaces(faces, nfaces+nseals);
	generateNormals(&*pShape);
	delete [] faces;

	TextureAttributeHandle* texAttribHdl = CreateHandle(TextureAttributeHandle);
		{
		WritableObject<TextureAttribute>(texAttribHdl)->bindTextureAttributeItem(terrain->getGrassTexture(),0);
		WritableObject<TextureAttribute>(texAttribHdl)->bindTextureAttributeItem(terrain->getSandTexture(),1);
		WritableObject<TextureAttribute>(texAttribHdl)->bindTextureAttributeItem(terrain->getRockTexture(),2);
		}

	// Create state set. Add material and render mode.
	WritableObject<StateSet> pStateSet( CreateHandle(StateSetHandle) );
	pStateSet->addAttribute(getCgFx ());
	pStateSet->addAttribute(texAttribHdl);

	// Setup the whole scene graph
	//m_geo->removeRef();
	m_geo = CreateHandle(GeoNodeHandle);
	WritableObject<GeoNode> pGeoNode(m_geo);

	pGeoNode->addGeometry( nvutil::getHandle<nvsg::DrawableHandle>( pShape ),
		nvutil::getHandle<StateSetHandle>( pStateSet ) );

	// make the trafo
	//m_trafo->removeRef();
	WritableObject<icPhysicsObject> terrainPhysics (terrainPhysicsHdl);
	terrainPhysics->addChild (m_geo);
	terrainPhysicsHdl->addRef ();
	Game::instance ()->addRootChild (terrainPhysicsHdl);

#ifndef LINUX // No PhysX under Linux yet.
	//PhysicsCookCell();
#endif

    /*if (rlock)*/ game->unlockRender();

#endif
}

#if 0
nvsg::CgFxHandle *unTerrainCell::getCgFx ()
{
  if (!cgfxHdl)
  {
    cgfxHdl = CreateHandle (CgFxHandle);
    {
      std::string err;
      WritableObject<CgFxEffect> cgfxEffect (ReadableObject<CgFx>(cgfxHdl)->getEffect());
      std::string currentpath;
      nvutil::GetCurrentDir (currentpath);
      currentpath += "./../data/shaders/terrain/Terrain.fx";
      if (!cgfxEffect->createFromFile(currentpath.c_str (), err))
        assert (0);
      float levels[2] = {0.0f, 5.0f};
      cgfxEffect->setFloatParameterValue (cgfxEffect->getParameterByName ("g_fTextureLevels"), levels);
    }
  }
  return cgfxHdl;
}
#endif

#if 0
bool unTerrainCell::hit (const nvmath::pVector& orig, const nvmath::pVector& dir, float maxDist, pVector *outPoint,
                         pVector *outNormal)
{
  NxRaycastHit hit;
  NxRay ray;
  ray.orig = NxVec3 (orig[0], orig[1], orig[2]);
  ray.dir = NxVec3 (dir[0], dir[1], dir[2]);
  ray.dir.normalize ();
  if (ReadableObject<icPhysicsObject> (terrainPhysicsHdl)->raycast (
    ray, maxDist, NX_RAYCAST_IMPACT | NX_RAYCAST_NORMAL, hit, false))
  {
    *outPoint = pVector (hit.worldImpact.x, hit.worldImpact.y, hit.worldImpact.z);
    if (outNormal)
      *outNormal = pVector (hit.worldNormal.x, hit.worldNormal.y, hit.worldNormal.z);
    return true;
  }

  return false;
}
#endif