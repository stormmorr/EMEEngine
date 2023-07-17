/*

    Trr Terrain File Descriptor
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include "unTrr.h"

/// trrcolor

namespace trr
{

trrcolor::trrcolor()// :
	//AmbientColor( {0.5f, 0.5f, 0.5f} ),
	//DiffuseColor( {0.6f, 0.6f, 0.6f} ),
	//EmissiveColor( {0.4f, 0.4f, 0.4f} ),
	//SpecularColor( {0.2f, 0.2f, 0.2f} )
{
	SpecularExponent = 50;
	Opacity = 1;
}

trrcolor::~trrcolor()
{
	//Destructor / Town / Name / Age / Salary
}

/// trrvertex

trrvertex::trrvertex(float Y) :
	Color()
{
	y_vertex = Y;
}

trrvertex::~trrvertex()
{
	//Destructor / Town / Name / Age / Salary
}

trrgrid::trrgrid()
{
}

trrgrid::~trrgrid()
{
	//Destructor / Town / Name / Age / Salary

	/// Grid Overlays Detail and LOD, placement affects entities
	/// Scenario MMO classic desert style
	/// Binary cube relationships, seconds pass rand , jig
}

trrBinaryCube* trrgrid::SetBC(int gridX, int gridY, int layer)
{
	int GX,GY,GT;
	trrBinaryCube* cube = new trrBinaryCube();

	/// FIXME OPTIMISE MAX MIN SELECTION
	float htMax = 0;
	float htMin = 0;
	bool setMax = false;
	bool setMin = false;
	bool null[TRR_B_C_DIM][TRR_B_C_DIM];

	/// Find Minimum and Maximum Valies
	GY = gridY - 1;
	for (int z=0; z < TRR_B_C_DIM; ++z)
		{
		GX = gridX - 1;
		for (int x=0; x < TRR_B_C_DIM; ++x)
			{
			/// Layer Cancel
			null[x][z] = true;
			for (int v=0; v < Grid[GX][GY].layers.size(); ++v)
				if(v == layer) null[x][z] = false;

			if(!null[x][z])
				{		/// Set Maximum
				if(Grid[GX][GY].layers[layer].y_vertex >= Grid[gridX][gridY].layers[layer].y_vertex + m_BCthreshold)
					{
					if(Grid[GX][GY].layers[layer].y_vertex < htMax || !setMax) htMax = Grid[GX][GY].layers[layer].y_vertex;	setMax = true;
					}
				else	/// Set Minimum
					{
					if(Grid[GX][GY].layers[layer].y_vertex <= Grid[gridX][gridY].layers[layer].y_vertex - m_BCthreshold)
						{
						if(Grid[GX][GY].layers[layer].y_vertex > htMin || !setMin) htMin = Grid[GX][GY].layers[layer].y_vertex; setMin = true;
						}
					}
				}
			GX++;
			}
		GY++;
		}

	//GT = 1;
	//for (int y=TRR_B_C_DIM-1; y >= 0; --y)
	//	{
	GY = gridY - 1;
	for (int z=0; z < TRR_B_C_DIM; ++z)
		{
		GX = gridX - 1;
		for (int x=0; x < TRR_B_C_DIM; ++x)
			{
			/// Access Layer Separation
			//for (int t=0; t < Grid[GX][GY].layers.size(); t+=2)
			//	{
			//	if(t == 0) /// First layer
			//		{
					/// Layer Cancel
					if(null[x][z]) cube->setColumn(x, z, 0, 0, 0);
					else
						{
						/// Middle 'y' Selection
						if(Grid[GX][GY].layers[layer].y_vertex >= Grid[gridX][gridY].layers[layer].y_vertex - m_BCthreshold &&
						   Grid[GX][GY].layers[layer].y_vertex <= Grid[gridX][gridY].layers[layer].y_vertex + m_BCthreshold)
						   cube->setColumn(x, z, 0, 1, 1);
						else
							{	/// Upper Grid Collumn
							if(Grid[GX][GY].layers[layer].y_vertex > Grid[gridX][gridY].layers[layer].y_vertex + m_BCthreshold)
								{
								cube->setColumn(x, z, 1, 1, 1);
								if(Grid[GX][GY].layers[layer].y_vertex > htMax + m_BCthreshold)
									{
									cube->setAngle(-15);
									cube->m_valid = false;
									}
								}
							else
								{
								if(Grid[GX][GY].layers[layer].y_vertex < htMin - m_BCthreshold)
									{
									cube->setColumn(x, z, 0, 0, 0);
									}
								else cube->setColumn(x, z, 0, 0, 1);
								}
							}
						}
			//		}
			//	else
			//		{
			//		if(t & 1) /// Layer is Odd and Terminator
			//			{
			//			if(Grid[GX][GY].layers[t].y_vertex >= Grid[gridX][gridY].layers[layer].y_vertex + GT &&
			//			   Grid[GX][GY].layers[t-1].y_vertex <= Grid[gridX][gridY].layers[layer].y_vertex + GT)
			//				{
			//				//bit = true;
			//				}
			//			}
			//		}
			//	}

			/// FIXME: add boolean bitwise operations
			GX++;
			}
		GY++;
		}
	//GT--;
	//}

#if 0
	printf("Binary Cube:\n");
	printf("Binary Cube - %i %i %i - %i %i %i - %i %i %i\n", cube->getBit(0, 0, 0), cube->getBit(1, 0, 0), cube->getBit(2, 0, 0), cube->getBit(0, 0, 1), cube->getBit(1, 0, 1), cube->getBit(2, 0, 1), cube->getBit(0, 0, 2), cube->getBit(1, 0, 2), cube->getBit(2, 0, 2));
	printf("Binary Cube - %i %i %i - %i %i %i - %i %i %i\n", cube->getBit(0, 1, 0), cube->getBit(1, 1, 0), cube->getBit(2, 1, 0), cube->getBit(0, 1, 1), cube->getBit(1, 1, 1), cube->getBit(2, 1, 1), cube->getBit(0, 1, 2), cube->getBit(1, 1, 2), cube->getBit(2, 1, 2));
	printf("Binary Cube - %i %i %i - %i %i %i - %i %i %i\n", cube->getBit(0, 2, 0), cube->getBit(1, 2, 0), cube->getBit(2, 2, 0), cube->getBit(0, 2, 1), cube->getBit(1, 2, 1), cube->getBit(2, 2, 1), cube->getBit(0, 2, 2), cube->getBit(1, 2, 2), cube->getBit(2, 2, 2));
#endif
	return cube;
}

void trrBinaryCube::Print(void)
{
	printf("Binary Cube - %i %i %i - %i %i %i - %i %i %i\n", bit[0] [2] [0], bit[1] [2] [0], bit[2] [2] [0], bit[0] [2] [1], bit[1] [2] [1], bit[2] [2] [1], bit[0] [2] [2], bit[1] [2] [2], bit[2] [2] [2]);
	printf("Binary Cube - %i %i %i - %i %i %i - %i %i %i\n", bit[0] [1] [0], bit[1] [1] [0], bit[2] [1] [0], bit[0] [1] [1], bit[1] [1] [1], bit[2] [1] [1], bit[0] [1] [2], bit[1] [1] [2], bit[2] [1] [2]);
	printf("Binary Cube - %i %i %i - %i %i %i - %i %i %i\n", bit[0] [0] [0], bit[1] [0] [0], bit[2] [0] [0], bit[0] [0] [1], bit[1] [0] [1], bit[2] [0] [1], bit[0] [0] [2], bit[1] [0] [2], bit[2] [0] [2]);
	printf("            - Angle %i\n", m_angle);
}

trrveclayer::trrveclayer()
{

}

trrveclayer::~trrveclayer()
{
	//Destructor / Town / Name / Age / Salary
}

trrBinaryCube::trrBinaryCube()
{
	m_valid = true;
}

trrBinaryCube::~trrBinaryCube()
{
	//Destructor / Town / Name / Age / Salary
}

bool trrBinaryCube::Cook(void)
{
	if(!m_valid) return false;

	int factor = 1;
	m_angle = 0;

	for (int x=TRR_B_C_DIM - 1; x >= 0; --x)
		{
		for (int y=TRR_B_C_DIM - 1; y >= 0; --y)
			{
			for (int z=TRR_B_C_DIM - 1; z >= 0; --z)
				{
				m_angle += bit[x][y][z] * factor;
				factor *= 2;
				}
			}
		}

	return true;
}

void trrBinaryCube::setIdentity(void)
{
	bit[0][2][0] = 0;
	bit[1][2][0] = 0;
	bit[2][2][0] = 0;

	bit[0][2][1] = 0;
	bit[1][2][1] = 0;
	bit[2][2][1] = 0;

	bit[0][2][2] = 0;
	bit[1][2][2] = 0;
	bit[2][2][2] = 0;

	bit[0][1][0] = 1;
	bit[1][1][0] = 1;
	bit[2][1][0] = 1;

	bit[0][1][1] = 1;
	bit[1][1][1] = 1;
	bit[2][1][1] = 1;

	bit[0][1][2] = 1;
	bit[1][1][2] = 1;
	bit[2][1][2] = 1;

	bit[0][0][0] = 1;
	bit[1][0][0] = 1;
	bit[2][0][0] = 1;

	bit[0][0][1] = 1;
	bit[1][0][1] = 1;
	bit[2][0][1] = 1;

	bit[0][0][2] = 1;
	bit[1][0][2] = 1;
	bit[2][0][2] = 1;
}

void trrBinaryCube::MirrorX()	//EXPERIMENTAL
{
	int face[TRR_B_C_DIM];
	int row[TRR_B_C_DIM][TRR_B_C_DIM];

	//face = bit[0][0];
	//bit[0] = bit[2];
}

////// '.trr' File Saving //////
void trrgrid::save(const char* filename)
{
	FILE* f = fopen(filename, "w");
    if (f == 0)
        throw std::string("Failed to open trr descriptor");

	////// Value Injection //////
	int vixptr = 0;
	int vixcnt = 0;
	int redptr = 0;
	int layercnt = 0;
    for (int y=0; y < TRR_GRID_SIZE; ++y)
		{
        for (int x=0; x < TRR_GRID_SIZE; ++x)
			{
			trrDec.layercnt.push_back(Grid[x][y].layers.size());
			layercnt++;
			for (int v=0; v < Grid[x][y].layers.size(); v++)
				{
				trrDec.vixer.push_back(Grid[x][y].layers[v].y_vertex);
				vixcnt++;
				}
			}
		}

	float* buffer = new float[layercnt+vixcnt];
	buffer[0] = layercnt+vixcnt;
	for (int c=0; c < layercnt; ++c)
		{
		buffer[vixptr] = trrDec.layercnt[c];
		vixptr++;
		for (int v=0; v < trrDec.layercnt[c]; ++v)
			{
			buffer[vixptr] = trrDec.vixer[redptr];
			redptr++;
			vixptr++;
			}
		}

	fwrite(buffer, 4, layercnt+vixcnt, f);

	fclose(f);
}

////// '.trr' File Saving //////
void trrgrid::saveFast(const char* filename)
{
	FILE* f = fopen(filename, "w");
    if (f == 0)
        throw std::string("Failed to open trr descriptor");

	////// Value Injection //////
	int vixptr = 0;
	float* buffer;// = new float[layercnt+vixcnt];

    for (int y=0; y < TRR_GRID_SIZE; ++y)
		{
        for (int x=0; x < TRR_GRID_SIZE; ++x)
			{
			buffer[vixptr] = Grid[x][y].layers.size();
			for (int v=0; v < Grid[x][y].layers.size(); v++)
				{
				buffer[vixptr] = Grid[x][y].layers[v].y_vertex;
				vixptr++;
				}
			}
		}

	for (int c=0; c < vixptr; ++c)
		{
		printf("vixel print %f\n", buffer[c]);
		//Sleep(250);
		}

	fwrite(buffer, 4, vixptr, f);

	fclose(f);
}

////// '.trr' File Loading //////
void trrgrid::load(const char* filename)
{
	//FILE* f = fopen(filename, "rb");
	FILE* f = fopen("terrain/raw/soap.trr", "rb");
    if (f == 0)
        throw std::string("Failed to open trr descriptor");

	////// Vixel Count //////
	fseek(f, 0, SEEK_END);
    size_t flen = ftell(f);
    fseek(f, 0, SEEK_SET);

    int nbVixels = flen/4;

	///// Read Data /////
	float* buffer = new float[nbVixels];
	fread(buffer, 4, nbVixels, f);
	fclose(f);

	trrvertex t_trrvertex(0);
	int vixptr = 0;
	int layercnt = 0;
	
	for (int y=0; y < TRR_GRID_SIZE; ++y)
		{
        for (int x=0; x < TRR_GRID_SIZE; ++x)
			{
			layercnt = buffer[vixptr];
			vixptr++;
			for (int c=0; c < layercnt; ++c)
				{
				t_trrvertex.y_vertex = buffer[vixptr];
				Grid[x][y].layers.push_back( t_trrvertex );
				vixptr++;
				}
			}
		}


	printf("||- trrGrid Loaded - %s \n", filename);
}

#if 0
	fseek(f, 0, SEEK_END);
    size_t flen = ftell(f);
    fseek(f, 0, SEEK_SET);

    nverts = flen/4;
    int dim = (int)sqrtf(nverts);
    assert(dim == terrain->getCellDim());

    float* buffer = new float[nverts];
    fread(buffer, 4, nverts, f);
    fclose(f);
#endif

void trrgrid::acLocateStack(/*Vec3f vectex,*/ int* x, int* y)
{
	//Vec3f trans = vectex - m_pos;
	//float distx = trans[0] / m_scale;
	//float disty = trans[2] / m_scale;
	//*x = (int)(distx + (TRR_GRID_SIZE / 2));
	//*y = (int)(disty + (TRR_GRID_SIZE / 2));
}

////// '.trr' Tool PokeVertex //////
void trrgrid::acPokeVertex(int x, int y, float toolY, int toolIndex)
{
	/*for (int v=0; v < Grid[x][y].layers.size(); v+=2)
		{
		if(v == 0) /// First layer
			{
			if(Grid[x+1][y-1].layers[v].y_vertex != Grid[x][y-1].layers[0].y_vertex) //vmatch = true;
			}
		else
			{
			if(v & 1) /// Layer is Odd and Terminator
				{
				if(Grid[x+1][y-1].layers[v].y_vertex >= Grid[x][y-1].layers[0].y_vertex &&
				   Grid[x+1][y-1].layers[v-1].y_vertex <= Grid[x][y-1].layers[0].y_vertex)
					{
					//vmatch = true;
					}
				}
			}
		}*/
}

////// '.trr' Tool LevelVertex //////
void trrgrid::acLevelVertex(int x, int y, float toolY, int toolIndex)
{
	if(toolIndex == 1)
		{
		for (int v=0; v < Grid[x][y].layers.size(); v+=2)
			{
			if(v == 0) /// First layer
				{
				if(Grid[x][y].layers.size() == 1 || toolY < Grid[x][y].layers[v+1].y_vertex) Grid[x][y].layers[0].y_vertex = toolY;
				}
			else
				{
				if(v & 1) /// Layer is Odd and Terminator
					{
					if(toolY < Grid[x][y].layers[v-1].y_vertex)
						{
						Grid[x][y].layers[v-1].y_vertex = toolY;
						v = Grid[x][y].layers.size();
						}
					}
				}
			}
		}
	else
		{
		if(toolIndex == 2 || toolIndex == 3 || toolIndex == 4 || toolIndex == 5 || toolIndex == 6 || toolIndex == 10)
			{
			for (int v=0; v < Grid[x][y].layers.size(); v+=2)
				{
				if(v == 0) /// First layer
					{
					if(Grid[x][y].layers.size() == 1 || toolY < Grid[x][y].layers[v+2].y_vertex) Grid[x][y].layers[0].y_vertex = toolY;
					}
				else
					{
					if(v & 1) /// Layer is Odd and Terminator
						{
						if((toolY > Grid[x][y].layers[v].y_vertex || v == Grid[x][y].layers.size() - 1) ||
						   (toolY > Grid[x][y].layers[v].y_vertex && toolY < Grid[x][y].layers[v+1].y_vertex))
							{
							Grid[x][y].layers[v].y_vertex = toolY;
							v = Grid[x][y].layers.size();
							}
						}
					}
				}
			}
		else
			{
			if(toolIndex == 7 || toolIndex == 8)
				{
				for (int v=0; v < Grid[x][y].layers.size(); v+=2)
					{
					if(v == 0) /// First layer
						{
						if(Grid[x][y].layers.size() == 1 || Grid[x][y].layers[v+2].y_vertex + toolY < Grid[x][y].layers[v+2].y_vertex) Grid[x][y].layers[0].y_vertex += toolY;
						}
					else
						{
						if(v & 1) /// Layer is Odd and Terminator
							{
							if((toolY > Grid[x][y].layers[v].y_vertex || v == Grid[x][y].layers.size() - 1) ||
							   (toolY > Grid[x][y].layers[v].y_vertex && toolY < Grid[x][y].layers[v+1].y_vertex))
								{
								Grid[x][y].layers[v].y_vertex += toolY;
								v = Grid[x][y].layers.size();
								}
							}
						}
					}
				}
			}
		}
}

void trrveclayer::acReset(void)
{
	//vecvert.clear();
	vecsearch.clear();
	vecedge.clear();
	vecxedge.clear();
	vecxload.clear();
	vecxterm.clear();
	//vecface.clear();
	//vecseal.clear();
	vecmktri.clear();
	vecCube.clear();
}

};