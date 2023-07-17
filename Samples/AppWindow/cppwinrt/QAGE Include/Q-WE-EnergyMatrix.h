/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

		Header File Classifications
				Energy Matrix Definitions

*/

#ifndef __Q_WE_EnergyMatrix__
#define __Q_WE_EnergyMatrix__

namespace GVARS
{

class Q_EnergyMatrixCLS		//*----Energy Matrix----*
{
public:
	int				GlobalSCALE;
	Q_MatrixBlock	QMATBlock[175];
	int				NomQMatBlocks;
	int				NomNetZonesINC;
	int				NetZONEINC[175];

	int				ShadINCX,ShadINCY,ShadINCZ;

	double			CurrentPOSX;
	double			CurrentPOSY;
	double			CurrentPOSZ;

	double			CurrentDTESTX;
	double			CurrentDTESTY;
	double			CurrentDTESTZ;

	QpoVec3d			CurrentMINS;
	QpoVec3d			CurrentMAXS;

	QpoVec3d			ActualMINS;
	QpoVec3d			ActualMAXS;

	QpoVec3d			ConstructMINS;
	QpoVec3d			ConstructMAXS;

	int				ZoneCHECK;
	int				ZoneACTIVE;

	//#### FUNCTIONS DEFINITIONS
	void PlayerAffectMatrix(void);
	void AvatarAffectMatrix(int AIcounter);

	void ZoneControl(void);

	void ZoneExitCheck(void);

	void TimeScaleReset(void);
};


class Q_Global_EnergyMatrix
{
public:
	Q_EnergyMatrixCLS EnergyMatrix;
};

extern QSharedStruct<Q_Global_EnergyMatrix> Q_EnergyMatrix;


};//END namespace GVARS

#endif