/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef TARGET_SCRIPT_H
#define TARGET_SCRIPT_H

#include <vector>
#include <math.h>

#include "Include/Cube.h"

#include "Collection.h"

#include "Result.h"


using namespace Cube;
using namespace std;

namespace ecoin
{

	class classTarget
	{
	public:
		classTarget()
			{
			m_Collection = new classCollection();
			m_Collection->acClear();
			}
		classTarget(CubeHESH* f_Hesh);

		bool acSimplify(void);
		bool acEvolve(void);
		bool acAdapt(void);

		void acGen_Humanoid(void);
		void acGen_Vehicle_Ground(void);

		void acLoad_from_TargetID(int f_TargetID);

		void acPrintStats(void);

		bool acCompare(classTarget* f_Target, float f_QualityLvl, float f_Grade, bool f_testVolumes);

		void acSaveCloud(std::string f_Name);

		float m_Mark;

		classCollection* m_Collection;
		classWorth m_Worth;
	};

};

#endif