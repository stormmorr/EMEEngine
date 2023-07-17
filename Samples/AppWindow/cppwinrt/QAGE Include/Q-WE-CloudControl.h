/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	- Minor Component -Avatar When In Human Form-
		-Header File Classifications-

*/

#ifndef __Q_WE_CloudControl__
#define __Q_WE_CloudControl__

namespace GVARS
{

class Q_CloudCLS		//*----QA CLOUDS----*
{
public:
	int			CloudType;
	float		CloudRed,CloudGreen,CloudBlue;
	int			CloudSpecCnt;
	QpoVec3d	CloudPos;
	float		CloudAlpha;
	float		CloudRED;
	float		CloudBLUE;
	float		CloudGREEN;
	float		CloudGRAVITY;
	float		CloudSCALEINC;
	float		CloudALPHAINC;
	float		CloudScale;
	int			CloudScaleDIR;
	QpoVertex	CloudLVert;
	QpoVec3d	CloudTraVec;
	float		CloudSpeed;
	int			CloudInit;			//Initialisation flag 1 at start 0 after one pass
	int			CloudLive;
	int			CloudMatCNT;
	QpoVec3d	CloudMins;
	QpoVec3d	CloudMaxs;
};


class Q_Global_Cloud
{
public:
	Q_Global_Cloud()
		{
		m_ArrayMx = 5000;
		}

	Q_CloudCLS Cloud[2500];

	int m_ArrayMx;
};

extern QSharedStruct<Q_Global_Cloud> Q_Cloud;


};//END namespace GVARS

#endif