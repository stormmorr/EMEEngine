/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -World Effects Control-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-WE-PntSprite.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-WorldEffects.h"

using namespace GVARS;

namespace GVARS
{

	//########  - POLYGON SHAPES -  ########//

void Q_COREFunctions::DrawFace(QpoVec3d **Verts)
{
	QpoVertex	LVerts[4];
	int			i;

	Tempfloat1 = (((float)rand() / 32767) * 75);

		LVerts[0].r = 255 * (1-_->ScannerLevelFactor);
		LVerts[0].g = 255 * _->ScannerLevelFactor;
		LVerts[0].b = 0;
		LVerts[0].a = Tempfloat1;
		LVerts[0].u = 0;
		LVerts[0].v = 0;
		LVerts[0].x = Verts[0]->x;
		LVerts[0].y = Verts[0]->y;
		LVerts[0].z = Verts[0]->z;

		LVerts[1].r = 255 * (1-_->ScannerLevelFactor);
		LVerts[1].g = 255 * _->ScannerLevelFactor;
		LVerts[1].b = 0;
		LVerts[1].a = Tempfloat1;
		LVerts[1].u = 1;
		LVerts[1].v = 0;
		LVerts[1].x = Verts[1]->x;
		LVerts[1].y = Verts[1]->y;
		LVerts[1].z = Verts[1]->z;

		LVerts[2].r = 255 * (1-_->ScannerLevelFactor);
		LVerts[2].g = 255 * _->ScannerLevelFactor;
		LVerts[2].b = 0;
		LVerts[2].a = Tempfloat1;
		LVerts[2].u = 1;
		LVerts[2].v = 1;
		LVerts[2].x = Verts[2]->x;
		LVerts[2].y = Verts[2]->y;
		LVerts[2].z = Verts[2]->z;

		LVerts[3].r = 255 * (1-_->ScannerLevelFactor);
		LVerts[3].g = 255 * _->ScannerLevelFactor;
		LVerts[3].b = 0;
		LVerts[3].a = Tempfloat1;
		LVerts[3].u = 0;
		LVerts[3].v = 1;
		LVerts[3].x = Verts[3]->x;
		LVerts[3].y = Verts[3]->y;
		LVerts[3].z = Verts[3]->z;

	//Qpo->Poly_AddOnce(&LVerts[0], 4, Medias->ScanBone, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
	Qpo->Poly_AddOnce(&LVerts[0], 4, Medias->FlameSingle, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 5.0f);
}


void Q_COREFunctions::DrawOrientedBoundBox(QpoVec3d *Pos, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ)
{
	static	QpoVec3d	Verts[8];
	static	QpoVec3d *	Faces[6][4] =
	{
		{ &Verts[0], &Verts[1], &Verts[2], &Verts[3] },
		{ &Verts[4], &Verts[5], &Verts[6], &Verts[7] },
		{ &Verts[3], &Verts[2], &Verts[6], &Verts[7] },
		{ &Verts[1], &Verts[0], &Verts[4], &Verts[5] },
		{ &Verts[0], &Verts[3], &Verts[7], &Verts[4] },
		{ &Verts[2], &Verts[1], &Verts[5], &Verts[6] },
	};

	int			i;

	for	(i = 0; i < 8; i++)
		Qpo->Vec3d_Copy(Pos, &Verts[i]);

	Qpo->Vec3d_Add(&Verts[0],DX,&Verts[0]);
	Qpo->Vec3d_Add(&Verts[0],DY,&Verts[0]);

	Qpo->Vec3d_Add(&Verts[1],DY,&Verts[1]);

	Qpo->Vec3d_Add(&Verts[2],DY,&Verts[2]);
	Qpo->Vec3d_Add(&Verts[2],DZ,&Verts[2]);

	Qpo->Vec3d_Add(&Verts[3],DX,&Verts[3]);
	Qpo->Vec3d_Add(&Verts[3],DY,&Verts[3]);
	Qpo->Vec3d_Add(&Verts[3],DZ,&Verts[3]);

	Qpo->Vec3d_Add(&Verts[4],DX,&Verts[4]);

	Qpo->Vec3d_Add(&Verts[6],DZ,&Verts[6]);

	Qpo->Vec3d_Add(&Verts[7],DX,&Verts[7]);
	Qpo->Vec3d_Add(&Verts[7],DZ,&Verts[7]);

	for	(i = 0; i < 6; i++)
		Q.DrawFace(&Faces[i][0]);
}


void Q_COREFunctions::DrawRectFromVec3ds(QpoVec3d *vec1, QpoVec3d *vec2, QpoVec3d *vec3, QpoVec3d *vec4, unsigned int bmpPtr,float alpha, float red, float green, float blue, int Flags)
{
	QpoVertex	LVerts[4];
	int			i;

	for(i=0; i<4; i++)	
		{
		LVerts[i].r = red;
		LVerts[i].g = green;
		LVerts[i].b = blue;
		LVerts[i].a = alpha;	//100
		}

	LVerts[3].x = vec1->x;
	LVerts[3].y = vec1->y;
	LVerts[3].z = vec1->z;
	LVerts[2].x = vec2->x;
	LVerts[2].y = vec2->y;
	LVerts[2].z = vec2->z;
	LVerts[1].x = vec3->x;
	LVerts[1].y = vec3->y;
	LVerts[1].z = vec3->z;
	LVerts[0].x = vec4->x;
	LVerts[0].y = vec4->y;
	LVerts[0].z = vec4->z;

	/*LVerts[2].r = 0.0f;  //DEBUG so can see which is start & end
	LVerts[2].g = 0.0f;
	LVerts[2].b = 0.0f;
	LVerts[3].r = 0.0f;  //DEBUG so can see which is start & end
	LVerts[3].g = 0.0f;
	LVerts[3].b = 0.0f;*/

	if (/*bmpPtr == NULL IMP*/0)
		{
		Qpo->Poly_AddOnce(&LVerts[0], 4, NULL, QPOLY_TYPE_GOR, QPOLY_REND_NO_OCCLUDE, 1.0f);
		}
	else
		{
		LVerts[0].u = 0.0f;
		LVerts[0].v = 1.0f;
		LVerts[1].u = 1.0f;
		LVerts[1].v = 1.0f;
		LVerts[2].u = 1.0f;
		LVerts[2].v = 0.0f;
		LVerts[3].u = 0.0f;
		LVerts[3].v = 0.0f;
		if(Flags == 0) Qpo->Poly_AddOnce(&LVerts[0], 4, bmpPtr, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
		else Qpo->Poly_AddOnce(&LVerts[0], 4, bmpPtr, QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
		}

	return;
}

};