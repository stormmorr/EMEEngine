/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -PHYSICS-
	*/#include "pch.h"/*- Minor Component -General Physics-

*/

//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

	//##### GENERAL PHYSICS #####

QpoVec3d Q_COREFunctions::PHY_BounceVector(QpoVec3d TraVec, QpoVec3d Normal)	//PHYSICS SYSTEM Calculate true bounce vector
{
	float		VecLength;
	QpoTransform	SurfaceMatrix,VectorMatrix;
	QpoVec3d		SurfaceLeft,SurfaceUp,SurfaceIn;
	QpoVec3d		VectorLeft,VectorUp,VectorIn;
	

	//#- Normalise Trajectory Vector
	VecLength = Qpo->Vec3d_Length(&TraVec);
	Qpo->Vec3d_Normalize(&TraVec);


	//#- Calculate Surface Planes
	Qpo->Transform_New(&SurfaceMatrix);
						
	SurfaceIn = Normal;

	if(SurfaceIn.x == 0 && SurfaceIn.z == 0)
		{
		SurfaceLeft.x = -1;
		SurfaceLeft.y = 0;
		SurfaceLeft.z = 0;
		}
	else
		{
		Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
		Qpo->Transform_RotateVector(&RotateMatrix, &SurfaceIn, &SurfaceLeft);
		SurfaceLeft.y = 0;
		}

	Qpo->Vec3d_CrossProduct(&SurfaceIn, &SurfaceLeft, &SurfaceUp);


	//#- Calculate Vector Matrix
	Qpo->Transform_New(&VectorMatrix);

	VectorIn = TraVec;

	if(VectorIn.x == 0 && VectorIn.z == 0)
		{
		VectorLeft.x = -1;
		VectorLeft.y = 0;
		VectorLeft.z = 0;
		}
	else
		{
		Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
		Qpo->Transform_RotateVector(&RotateMatrix, &VectorIn, &VectorLeft);
		VectorLeft.y = 0;
		}

	Qpo->Vec3d_CrossProduct(&VectorIn, &VectorLeft, &VectorUp);

	Qpo->Transform_New_LeftUpIn(&VectorMatrix, &VectorLeft, &VectorUp, &VectorIn);


	//#- Mirror The Vector Matrix By the Surface Planes
	Qpo->Vec3d_Normalize(&SurfaceLeft);
	Qpo->Vec3d_Normalize(&SurfaceUp);

	Qpo->Transform_Mirror(&VectorMatrix, &SurfaceLeft, 0, &VectorMatrix);
	Qpo->Transform_Mirror(&VectorMatrix, &SurfaceUp, 0, &VectorMatrix);

	Qpo->Transform_GetIn(&VectorMatrix, &TraVec);
	Qpo->Vec3d_Inverse(&TraVec);

	Qpo->Vec3d_Scale(&TraVec, VecLength, &TraVec);


	//#- Return The Trajectory Vector
	return TraVec;
}

/*
   Calculate the line segment PaPb that is the shortest route between
   two lines P1P2 and P3P4. Calculate also the values of mua and mub where
      Pa = P1 + mua (P2 - P1)
      Pb = P3 + mub (P4 - P3)
   Return false if no solution exists.
*/

int Q_COREFunctions::Q_LineLineintersect(QpoVec3d p1,QpoVec3d p2,QpoVec3d p3,QpoVec3d p4,QpoVec3d *pa,QpoVec3d *pb/*,double *mua, double *mub*/)
{
   QpoVec3d p13,p43,p21;
   double d1343,d4321,d1321,d4343,d2121;
   double numer,denom;
   double mua,mub;

   p13.x = p1.x - p3.x;
   p13.y = p1.y - p3.y;
   p13.z = p1.z - p3.z;
   p43.x = p4.x - p3.x;
   p43.y = p4.y - p3.y;
   p43.z = p4.z - p3.z;
   if (Q_ABS(p43.x)  < Q_EPSILON && Q_ABS(p43.y)  < Q_EPSILON && Q_ABS(p43.z)  < Q_EPSILON)
      return(false);
   p21.x = p2.x - p1.x;
   p21.y = p2.y - p1.y;
   p21.z = p2.z - p1.z;
   if (Q_ABS(p21.x)  < Q_EPSILON && Q_ABS(p21.y)  < Q_EPSILON && Q_ABS(p21.z)  < Q_EPSILON)
      return(false);

   d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
   d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
   d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
   d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
   d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

   denom = d2121 * d4343 - d4321 * d4321;
   if (Q_ABS(denom) < Q_EPSILON)
      return(false);
   numer = d1343 * d4321 - d1321 * d4343;

   mua = numer / denom;
   mub = (d1343 + d4321 * (mua)) / d4343;

   pa->x = p1.x + mua * p21.x;
   pa->y = p1.y + mua * p21.y;
   pa->z = p1.z + mua * p21.z;
   pb->x = p3.x + mub * p43.x;
   pb->y = p3.y + mub * p43.y;
   pb->z = p3.z + mub * p43.z;

   return(true);
}

};