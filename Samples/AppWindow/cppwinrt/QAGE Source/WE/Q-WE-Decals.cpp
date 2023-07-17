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
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

	//########  - POLYGON SHAPES -  ########//

bool Q_COREFunctions::AddDecal(QpoVec3d impact, QpoVec3d COLnormal, float Scale, int DTYPE)
	{
	// set up the vertices
	QpoVec3d VertCoords[4];
	float Width, Height;
	QpoVec3d right, up;
	QpoVertex Verts[4];

	if(DTYPE == 1) Scale *= 5;

	Width = Scale * 2;
	Height = Scale * 2;

	//if(_->NomDecal > 1498) return false;
	if(_->NomDecal > 998) _->NomDecal = 0;

	// Note:  The following code is based on code by Ralph Deane
	
	if(fab(COLnormal.y) > fab(COLnormal.x))
		{
		major = 1;
		if(fab(COLnormal.z) > fab(COLnormal.y))
			major = 2;
		}
	else
		{
		if(fab(COLnormal.z) > fab(COLnormal.x))
			major = 2;
		}
	
	if(fab(COLnormal.x)==1.0f || fab(COLnormal.y)==1.0f || fab(COLnormal.z)==1.0f)
		{
		if ((major == 0 && COLnormal.x > 0) || major == 1)
			{
				right.x = 0.0f;
				right.y = 0.0f;
				right.z = -1.0f;
			}
		else if (major == 0)
			{
				right.x = 0.0f;
				right.y = 0.0f;
				right.z = 1.0f;
			}
		else 
			{
				right.x = COLnormal.z;
				right.y = 0.0f;
				right.z = 0.0f;
			}
		}
	else Qpo->Vec3d_CrossProduct(&qAxis[major], &COLnormal, &right);

	Qpo->Vec3d_CrossProduct(&COLnormal, &right, &up);
	Qpo->Vec3d_Normalize(&up);
	Qpo->Vec3d_Normalize(&right);
	
	Qpo->Vec3d_Scale(&right, Width / 2.0f, &right);
	Qpo->Vec3d_Scale(&up, Height / 2.0f, &up);
	
	Qpo->Vec3d_AddScaled(&impact, 1.25f, &COLnormal, &impact);

	//calculate vertices from corners
	VertCoords[1].x = impact.x + ((-right.x - up.x));
	VertCoords[1].y = impact.y + ((-right.y - up.y));
	VertCoords[1].z = impact.z + ((-right.z - up.z));
	
	VertCoords[2].x = impact.x + ((right.x - up.x));
	VertCoords[2].y = impact.y + ((right.y - up.y));
	VertCoords[2].z = impact.z + ((right.z - up.z));
	
	VertCoords[3].x = impact.x + ((right.x + up.x));
	VertCoords[3].y = impact.y + ((right.y + up.y));
	VertCoords[3].z = impact.z + ((right.z + up.z));
	
	VertCoords[0].x = impact.x + ((-right.x + up.x));
	VertCoords[0].y = impact.y + ((-right.y + up.y));
	VertCoords[0].z = impact.z + ((-right.z + up.z));

	// check clipping
#pragma todo(check clipping here)

	// copy into useful form
	Verts[0].u = Verts[0].v = 0.0f;
	Verts[1].u = 1.0f;
	Verts[1].v = 0.0f;
	Verts[2].u = Verts[2].v = 1.0f;
	Verts[3].u = 0.0f;
	Verts[3].v = 1.0f;

	for(int i = 0; i < 4; i++)
		{
		Verts[i].r = Verts[i].g = Verts[i].b = Verts[i].a = 255.0f;
		VertCoords[i].x = VertCoords[i].x;
		VertCoords[i].y = VertCoords[i].y;
		VertCoords[i].z = VertCoords[i].z;
		Verts[i].x = VertCoords[i].x;
		Verts[i].y = VertCoords[i].y;
		Verts[i].z = VertCoords[i].z;
		}

	//#### SETUP Q_Medias->DECAL INFO ONLY STRUCT FOR LATER REFERENCE ####

	Q_Decal->Decal[_->NomDecal].Pos = impact;									//Position in World Space
	Q_Decal->Decal[_->NomDecal].Scale = 0.2 + (((float)rand() / 32767) * 3);	//Scale
	Q_Decal->Decal[_->NomDecal].Alpha = 255;									//Alpha
	Q_Decal->Decal[_->NomDecal].Count = 0;									//Optional- Counter for timing

	if(DTYPE == 0) Q_Decal->Decal[_->NomDecal].TYPE = rand()%21;				//Type of Decal
	if(DTYPE == 1) Q_Decal->Decal[_->NomDecal].TYPE = 22 + (rand()%2);
	if(DTYPE == 2) Q_Decal->Decal[_->NomDecal].TYPE = 25;
	if(DTYPE == 3) Q_Decal->Decal[_->NomDecal].TYPE = 26 + (rand()%1);

	Q_Decal->Decal[_->NomDecal].Live = 1;										//Live Switch   0 = OFF / 1 = ON

	// draw!
	Q_Decal->Decal[_->NomDecal].Polygon = Qpo->Poly_Add(Verts, 4, Medias->DECAL[Q_Decal->Decal[_->NomDecal].TYPE], QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT | QPOLY_REND_NO_OCCLUDE, 1.0f);

	_->NomDecal++;

	return true;
	}

};