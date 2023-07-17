/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "ICS_Corner.h"

using namespace ecoin;

namespace ecoin
{

ICS_classCorner::ICS_classCorner(void)
{
	//...
}

ICS_classCorner::~ICS_classCorner(void)
{
	m_Corner = nullptr;
	m_X = nullptr;
	m_Y = nullptr;
	m_Z = nullptr;
}

void ICS_classCorner::acMake(void)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "ICS_classCorner::ICS_classCorner";

	ag_StatusLive(f_ref_CurrentPath, "m_Corner");
	m_Corner = make_shared<BiVector>();
	ag_StatusLive(f_ref_CurrentPath, "m_X");
	m_X = make_shared<BiVector>();
	ag_StatusLive(f_ref_CurrentPath, "m_Y");
	m_Y = make_shared<BiVector>();
	ag_StatusLive(f_ref_CurrentPath, "m_Z");
	m_Z = make_shared<BiVector>();
}

bool ICS_classCorner::acClassify(void)
{

	//float theta = asin(x);

	//FrustralOrientation from biplane
	return true;
}

void ICS_classCorner::acSpecify(shared_ptr<BiVector> f_Corner, shared_ptr<BiVector> f_X, shared_ptr<BiVector> f_Y, shared_ptr<BiVector> f_Z)
{
	m_Corner = f_Corner;
	m_X = f_X;
	m_Y = f_Y;
	m_Z = f_Z;
}

};