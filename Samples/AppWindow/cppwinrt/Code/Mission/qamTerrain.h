/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAMTERRAIN_H
#define QAMTERRAIN_H

#include <vector>
#include <math.h>

#include "qamType.h"
#include "qamVariable.h"

#include "VoxelGrid.h"

using namespace ecoin;
using namespace Cube;

namespace ecoin
{
	extern int g_QamID;

	class qamTerrain : public qamType
	{
	public:
		qamTerrain() : qamType(qamTYPE_Terrain) { acClear(); m_QamID = g_QamID; };
		qamTerrain(int f_ID);
		~qamTerrain() { acClear(); }

		void acClear(void)
			{
			m_X = 0.0f;
			m_Y = 0.0f;
			m_Z = 0.0f;
			m_Xrot = 0.0f;
			m_Yrot = 0.0f;
			m_Zrot = 0.0f;
			m_TerrainInsertFillX = 1;
			m_TerrainInsertFillY = 1;
			m_TerrainInsertFillZ = 1;
			m_TerrainInsertMoveX = 1;
			m_TerrainInsertMoveY = 1;
			m_TerrainInsertMoveZ = 1;
			m_TerrainInsertNegatedX = 0;
			m_TerrainInsertNegatedY = 0;
			m_TerrainInsertNegatedZ = 0;
			m_TerrainInsertMaxX = 1;
			m_TerrainInsertMaxY = 1;
			m_TerrainInsertMaxZ = 1;
			m_TerrainInsertFillXres = 1;
			m_TerrainInsertFillYres = 1;
			m_TerrainInsertFillZres = 1;
			m_TerrainInsertMoveXres = 1;
			m_TerrainInsertMoveYres = 1;
			m_TerrainInsertMoveZres = 1;
			m_TerrainInsertNegatedXres = 0;
			m_TerrainInsertNegatedYres = 0;
			m_TerrainInsertNegatedZres = 0;
			m_TerrainInsertMaxXres = 1;
			m_TerrainInsertMaxYres = 1;
			m_TerrainInsertMaxZres = 1;
			m_materialid = 1;
			m_DefaultShape = 1;
			m_Order = 1;
			m_Type = 1;
			m_Repeat = 1;
			m_QamLevel = 1;
			m_QamID = 1;
			m_ID = -1551;
			m_Save = false;
			m_Updated = false;
			}

		void ac_Compute(void);
		void ac_Save(void);

		void acVoxprint(std::shared_ptr<VoxelGrid> f_Grid);
		void acVoxprint(int f_Grid);

		////	/////
		/// MAKE ///
		//		//
		bool Make_Place_Terrain(std::shared_ptr<VoxelGrid> f_Grid = nullptr);
		bool Make_Place_Terrain(int f_Grid);

		std::string m_NameGroup;

		float m_X;
		float m_Y;
		float m_Z;

		float m_Xrot;
		float m_Yrot;
		float m_Zrot;

		int m_TerrainInsertFillX;
		int m_TerrainInsertFillY;
		int m_TerrainInsertFillZ;
		int m_TerrainInsertMoveX;
		int m_TerrainInsertMoveY;
		int m_TerrainInsertMoveZ;
		int m_TerrainInsertNegatedX;
		int m_TerrainInsertNegatedY;
		int m_TerrainInsertNegatedZ;
		int m_TerrainInsertMaxX;
		int m_TerrainInsertMaxY;
		int m_TerrainInsertMaxZ;
		int m_TerrainInsertFillXres;
		int m_TerrainInsertFillYres;
		int m_TerrainInsertFillZres;
		int m_TerrainInsertMoveXres;
		int m_TerrainInsertMoveYres;
		int m_TerrainInsertMoveZres;
		int m_TerrainInsertNegatedXres;
		int m_TerrainInsertNegatedYres;
		int m_TerrainInsertNegatedZres;
		int m_TerrainInsertMaxXres;
		int m_TerrainInsertMaxYres;
		int m_TerrainInsertMaxZres;
		int m_materialid;
		int m_DefaultShape;

		int m_Order;
		int m_Type;
		int m_Repeat;

		int m_QamLevel;
		int m_QamID;

		int m_ID;
		bool m_Save;

		bool m_Updated;
	};

};

#endif