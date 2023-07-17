/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Header File Classifications-
	- Minor Component -QShellA Function Prototypes-

*/

#ifndef QSHELLAPROTOTYPES_H
#define QSHELLAPROTOTYPES_H

using namespace GVARS;

//--------------------------------------------------------------------
// INTERNAL FUNCTION PROTOTYPES
//--------------------------------------------------------------------

namespace GVARS
{

class Q_ShellAlpha
{
public:

	virtual void ValidPointer_Frame(int Count);

	virtual void ValidPointer_RenderPoint(QpoVec3d Position);

	virtual void ValidPointer_RenderPointXYZ(float PosX, float PosY, float PosZ);
};

static Q_ShellAlpha Q_ShellA;

extern int NomValidPointer;
extern int MaxNomValidPointer;

};

#pragma message ("###  QShellA Prototypes  [Q-ShellAPrototypes.h]")

#endif