/*

    Trr Terrain File Descriptor
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __icTrr_h__
#define __icTrr_h__

/// Standard Includes
#include <vector>

/// Engine Specific Includes
#include "unGeometry.h"
#include "pMath.h"

//----------------------------------------------------------------------------//
// Defines                                                                    //
//----------------------------------------------------------------------------//

namespace trr
{

//#define TRR_GRID_SIZE 11
#define TRR_GRID_SIZE 129
#define TRR_B_C_DIM 3
#define TRR_B_C_THRESHOLD 5
#define TRR_NB_TEMPLATES 26

#define PI_VARIANT ?

//----------------------------------------------------------------------------//
// Class Declarations                                                         //
//----------------------------------------------------------------------------//

class trrBinaryCubeManager
{

};

class trrBinaryCube		// Binary/Bit Cube
{
public:
	trrBinaryCube();
    virtual ~trrBinaryCube();

	/// Template Constructor
	void mkTemplate(int Template);

	inline void setAngle(int angle) { m_angle = angle; }
	inline int getAngle(void) { return m_angle; }

	inline int getBit(int indx, int indy, int indz) { return bit[indx][indy][indz]; }
	inline void setBit(int indx, int indy, int indz, int value) { bit[indx][indy][indz] = value; }
	inline void setColumn(int indx, int indz, int value2, int value1, int value0) { bit[indx][2][indz] = value2; bit[indx][1][indz] = value1; bit[indx][0][indz] = value0; }
	inline void setXRow(int indy, int indz, int valueA, int valueB, int valueC) { bit[0][indy][indz] = valueA; bit[1][indy][indz] = valueB; bit[2][indy][indz] = valueC; }

	inline int Compare(int angle) { return angle - m_angle; }

	void Print(void);
	void Sort(void);
	void Search(void);

	void setIdentity(void);

	bool Cook(void);
	void MirrorX(void);

	bool m_valid;

	/// FIXME: Add Operators

private:
	int bit[TRR_B_C_DIM][TRR_B_C_DIM][TRR_B_C_DIM];
	int m_angle;
};

class trrcolor
{
public:
	trrcolor();
    virtual ~trrcolor();

private:
	float* ind[3];

	//float AmbientColor[3];
	//float DiffuseColor[3];
	//float EmissiveColor[3];
	//float SpecularColor[3];

	float SpecularExponent;
	float Opacity;
};

class trrvertex
{
public:
	trrvertex(float Y);
    virtual ~trrvertex();

	float y_vertex;

private:
	trrcolor* Color;
};

class trrelement
{
public:
	trrelement() {};
	virtual ~trrelement() {};

	std::vector<trrvertex> layers;
};

class trrdescriptor
{
public:
	trrdescriptor() {};
	virtual ~trrdescriptor() {};

	std::vector<int> layercnt;
	std::vector<float> vixer;
};

class trrgrid
{
public:
	trrgrid();
    virtual ~trrgrid();

	float getScale(void) { return m_scale; }
	void setScale(float scale) { m_scale = scale; }

	void setBCthreshold(float threshold) { m_BCthreshold = threshold; }

	trrBinaryCube* SetBC(int gridX, int gridY, int layer);

	void save(const char* filename);
	void saveFast(const char* filename);
	void load(const char* filename);

	void acLocateStack(/*pVector vectex,*/ int* x, int* y);
	void acPokeVertex(int x, int y, float toolY, int toolIndex);
	void acLevelVertex(int x, int y, float toolY, int toolIndex);

	//icVector<icVector<trrelement>> Grid;
	//icVector<icVector<trrdescriptor>> trrDec;

	trrelement Grid[TRR_GRID_SIZE][TRR_GRID_SIZE];
	trrdescriptor trrDec;

	//pVector m_pos;

private:
	float m_BCthreshold;
	float m_scale;
};

class trrveclayer
{
public:
	trrveclayer();
    virtual ~trrveclayer();

	pVector getVec(int index) { return vecvert[index]; }
	void addVert(float x, float y, float z) { vecvert.push_back(pVector(x, y, z)); }
	Face3 getFace(int index) { return vecface[index]; }
	void addFace(Face3 face) { vecface.push_back(face); }
	void addSeal(Face3 face) { vecseal.push_back(face); }
	void addBC(trrBinaryCube* bCube) { vecCube.push_back(bCube); }
	void clearFace(void) { vecface.pop_back(); }
	void clearSeal(void) { vecseal.pop_back(); }

	void acReset(void);

	int Vindex;

	std::vector<pVector> vecvert;
	std::vector<int> vecsearch;
	std::vector<bool> vecedge;
	std::vector<bool> vecxedge;
	std::vector<bool> vecxload;
	std::vector<bool> vecxterm;
	std::vector<Face3> vecface;
	std::vector<Face3> vecseal;
	std::vector<bool> vecmktri;
	std::vector<trrBinaryCube*> vecCube;
};

};

#endif	//__icTrr_h__