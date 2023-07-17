/*

    unTerrainCell - Terrain Loader
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unTerrain_TerrainCell_h__
#define __unTerrain_TerrainCell_h__

//#include "icConstants.h"
//#include "nvsg/CoreTypes.h"
//#include "Physics/icPhysicsObject.h"
//#include "nvmath/Vec3f.h"
#include "unTrr.h"

using namespace trr;

struct unTerrainCellComp;

class unTerrainCell
{
public:
  unTerrainCell();
  virtual ~unTerrainCell();

  void init();
  void shutdown();

  void load(const char* filename, int ix, int iy, bool rlock=true);
  void acResetCell(void);

  float getDim() const                    {return m_fdim;}
  //nvsg::NodeHandle* getHandle() const     {return terrainPhysicsHdl;}

  int getX() const     {return m_x;}
  int getY() const     {return m_y;}
  int getIdx() const   {return m_idx;}

  void acShiftCell(pVector startpos, pVector destpos);

  trrgrid trrGrid;
  int m_resetCount;

  size_t getVerticesCount () {return nverts;}
  size_t getFacesCount (size_t LOD) {return nfaces;}
  trr::Face3 *getFaces (size_t LOD) {return faces;}
  pVector *getVertices () {return vertices;}

  //icPhysicsObjectHandle *getPhysicsObject () {return terrainPhysicsHdl;}
  //bool hit (const pVector& orig, const pVector& dir, float maxDist, Vec3f *outPoint, Vec3f *outNormal = 0);

private:

  //nvsg::CgFxHandle *getCgFx ();

  //icPhysicsObjectHandle *terrainPhysicsHdl;
  //nvsg::GeoNodeHandle* m_geo;
  //static nvsg::CgFxHandle *cgfxHdl;

  pVector *vertices;
  trr::Face3 *faces;

  int nverts;
  int nfaces;
  int nseals;

  float m_fdim;

  int m_x;
  int m_y;
  int m_idx;

  /// New Terrain Super Class Inherit
  float m_scale;
  float m_texscale;
  float m_terrainWidth;

  friend struct unTerrainCellComp;

  std::vector<trrveclayer> veclayer;
};

struct unTerrainCellComp
{
  bool operator() (const unTerrainCell* a, const unTerrainCell* b) const
  {
    return a->m_y < b->m_y || a->m_x < b->m_x;
  }
};

#endif
