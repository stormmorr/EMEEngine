/*

System - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAMSYSTEM_H
#define QAMSYSTEM_H

#include <vector>
#include <math.h>

namespace ecoin
{

	class qamSystem
	{
	public:
		qamSystem();
		~qamSystem();

		std::shared_ptr<Variable> av_Var(std::string f_String);

		std::shared_ptr<Variable> Pos;
		std::shared_ptr<Variable> Posx;
		std::shared_ptr<Variable> Posy;
		std::shared_ptr<Variable> Posz;
		std::shared_ptr<Variable> Color;
		std::shared_ptr<Variable> Matrix1;
		std::shared_ptr<Variable> Matrix2;
		std::shared_ptr<Variable> Matrix3;
		std::shared_ptr<Variable> Matrix4;

		std::shared_ptr<Variable> nonce;

		std::vector<std::shared_ptr<Variable>> m_Global;
	};

};

#endif