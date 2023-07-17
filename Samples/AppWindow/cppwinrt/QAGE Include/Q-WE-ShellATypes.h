/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	- Minor Component -Avatar When In Human Form-
		-Header File Classifications-
*/

#ifndef __Q_WE_ShellATypes__
#define __Q_WE_ShellATypes__

namespace GVARS
{

#define VP_TYPE_VECTOR 0
#define VP_TYPE_MATRIX 1
#define VP_TYPE_PMATRIX 2

#define MAX_NOM_VALID_POINTERS 500

class Q_ValidPointerCLS		//*----Small Energy Attacks----*
{
public:
	int			AvID;
	
	float		Scale;
	int			Alpha;
	int			Type;
	int			Live;

	QpoVec3d	Pos;						//Position of the light and the energy in world space
	QpoVec3d	TraVec;

	QpoVec3d	LeftVec;
	QpoVec3d	UpVec;
	QpoVec3d	InVec;

	QpoTransform Transform;

	QpoLight	Light;					//Dynamic Light
	QpoColor	Color;					//Color of the light
};

class Q_Global_ValidPointer
{
public:
	Q_ValidPointerCLS ValidPointer[MAX_NOM_VALID_POINTERS];
};

extern QSharedStruct<Q_Global_ValidPointer> Q_ValidPointer;

};//END namespace GVARS

#endif