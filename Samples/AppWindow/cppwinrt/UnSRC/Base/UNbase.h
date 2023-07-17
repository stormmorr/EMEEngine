/*

    UNbase - Base Definitions
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef _UN_Base_
#define _UN_Base_

#include <vector>
#include "../Utility/datatypes.h"

#if 0
#include "../../DigitalMass/Source/Geometry/unTrr.h"
#endif

namespace UN
{

enum UnifiedVariableDesc
{
  UNV_PUBLIC,
  UNV_PRIVATE,
  UNV_PROTECTED,
};

enum UnifiedStructDesc
{
  UNS_PUBLIC,
  UNS_PRIVATE,
  UNS_PROTECTED,
};

enum UnifiedClassDesc
{
  UNC_PUBLIC,
  UNC_PRIVATE,
  UNC_PROTECTED,
};

typedef struct UNstack
{
std::vector<bool> m_stack;
} UNstack;

typedef struct UNsheet
{
std::vector<int> m_list;
} UNsheet;

typedef struct UNscale
{
int m_divisor[3];
} UNscale;

typedef struct UNstruct
{
std::vector<UNstack> m_stack;
std::vector<UNsheet> m_sheet;
} UNstruct;

typedef struct UNfunctionDEF
{
std::vector<UNstack> m_stack;
std::vector<UNsheet> m_sheet;
} UNfunctionDEF;

typedef struct UNtemplate
{
UNstruct *m_protovar;
UNstruct *m_protomap;
} UNtemplate;

class UNclass
{
public:
	UNclass()
		{
		m_public = new UNstruct;
		m_private = new UNstruct;
		m_protected = new UNstruct;
		};
	~UNclass()
		{
		delete m_public;
		delete m_private;
		delete m_protected;
		};

	///// Constructors /////
	UNclass(const UNclass &src);
	UNclass(const UNstruct &src, unsigned int e_index);

	UNstruct *getPublic() { return m_public; };
	UNstruct *getPrivate() { return m_private; };
	UNstruct *getProtected() { return m_protected; };

	////// Epsilon third row
	////// Scan Source ->
	UNstruct *m_public;
	UNtemplate m_pubT;
	UN::UNscale m_pubdiv;

private:

	UNstruct *m_private;
	UNtemplate m_priT;
	UN::UNscale m_pridiv;

protected:

	UNstruct *m_protected;
	UNtemplate m_proT;
	UN::UNscale m_prodiv;
};

typedef struct UNmap
{
  std::vector<int> vecint;
  std::vector<unsigned int> vecuint;
  std::vector<float> vecfloat;
  std::vector<char> vecchar;
  std::vector<unsigned char> vecuchar;
  std::vector<bool> vecbool;

  std::vector<class UN::UNclass> vecclass;
} UNmap;

class UNtrip
{
public:
	std::vector<UN::UNstruct> im_variable;
	std::vector<UN::UNsheet> sep_variable;

	std::vector<UN::UNstruct> im_struct;
	std::vector<UN::UNsheet> sep_struct;

	std::vector<UN::UNclass> im_class;
	std::vector<UN::UNsheet> sep_class;

private:
	void refresh(void);
	void manage(void);
};

#pragma message ("FIXME::: Load Protocols and Language Directives")

};

#endif