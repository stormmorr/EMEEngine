/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CORNER_H
#define CORNER_H

#include <vector>
#include <math.h>

#include "Include/Cube.h"
#include "Element.h"

using namespace Cube;

namespace ecoin
{

	enum CLS_CornerType
	{
		CLS_Corner
	};

	class classCorner
	{
	public:
		classCorner();
		~classCorner();

		void acMake(void);
		
		void acSpecify(shared_ptr<BiVector> f_Corner, shared_ptr<BiVector> f_X, shared_ptr<BiVector> f_Y, shared_ptr<BiVector> f_Z);
		bool acClassify(void);

		shared_ptr<BiVector> m_Corner;
		shared_ptr<BiVector> m_X;
		shared_ptr<BiVector> m_Y;
		shared_ptr<BiVector> m_Z;
	};

};

#endif