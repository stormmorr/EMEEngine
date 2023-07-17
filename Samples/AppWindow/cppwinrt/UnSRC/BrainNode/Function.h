/*

	Command - Osirus Command
	Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef OSIFUNCTION_H
#define OSIFUNCTION_H

namespace OSI
{

typedef struct Parameter
{
	std::string m_Text;
} Parameter;

typedef struct CName
{
	std::string m_Text;
} CName;

typedef struct Argument
{
	std::vector<Parameter> m_Parameter;
	std::string m_Name;
} Argument;

typedef struct Function
{
	CName m_Name;
	std::vector<Parameter> m_Return;
	std::vector<Argument> m_Argument;
} Function;

};

#endif