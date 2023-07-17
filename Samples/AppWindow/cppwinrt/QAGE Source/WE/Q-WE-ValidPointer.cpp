/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Shell Alpha-
	*/#include "pch.h"/*- Minor Component -Coordinate Position Locator-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "math.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-PntSprite.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-ShellAPrototypes.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-WE-MeleeHits.h"

#include "Q-WE-ShellATypes.h"

using namespace GVARS;

namespace GVARS
{

QSharedStruct<Q_Global_ValidPointer> Q_ValidPointer;

	//######## Set Counters ##########

int NomValidPointer = 0;
int MaxNomValidPointer = MAX_NOM_VALID_POINTERS;

void Q_ShellAlpha::ValidPointer_Frame(int Count)
	{
#if 0 // QAGE_DESKTOP
	QpoVec3d i_Vector;

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glDisable(GL_BLEND);								// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	printf("unTrace Type %i\n", Q_ValidPointer->ValidPointer[Count].Type);

	switch(Q_ValidPointer->ValidPointer[Count].Type)
		{
		case VP_TYPE_VECTOR:
			{
			i_Vector = Q_ValidPointer->ValidPointer[Count].TraVec;
			Qpo->Camera_Set();
			glColor3f(1.0f, 0.0f, 1.0f);	//PURPLE
			//*glBegin(GL_LINES);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x, Q_ValidPointer->ValidPointer[Count].Pos.y, Q_ValidPointer->ValidPointer[Count].Pos.z);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			//*glEnd();
			ValidPointer_RenderPointXYZ(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			}break;

		case VP_TYPE_MATRIX:
			{
			i_Vector = Q_ValidPointer->ValidPointer[Count].LeftVec;
			Qpo->Camera_Set();
			glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
			//*glBegin(GL_LINES);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x, Q_ValidPointer->ValidPointer[Count].Pos.y, Q_ValidPointer->ValidPointer[Count].Pos.z);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			//*glEnd();
			ValidPointer_RenderPointXYZ(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));

			i_Vector = Q_ValidPointer->ValidPointer[Count].UpVec;
			Qpo->Camera_Set();
			glColor3f(1.0f, 0.0f, 0.0f);	//RED
			//*glBegin(GL_LINES);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x, Q_ValidPointer->ValidPointer[Count].Pos.y, Q_ValidPointer->ValidPointer[Count].Pos.z);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			//*glEnd();
			ValidPointer_RenderPointXYZ(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));

			i_Vector = Q_ValidPointer->ValidPointer[Count].InVec;
			Qpo->Camera_Set();
			glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
			//*glBegin(GL_LINES);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x, Q_ValidPointer->ValidPointer[Count].Pos.y, Q_ValidPointer->ValidPointer[Count].Pos.z);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			//*glEnd();
			ValidPointer_RenderPointXYZ(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			}break;

		case VP_TYPE_PMATRIX:
			{
			i_Vector = Q_ValidPointer->ValidPointer[Count].LeftVec;
			Qpo->Camera_Set();
			glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
			//*glBegin(GL_LINES);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x, Q_ValidPointer->ValidPointer[Count].Pos.y, Q_ValidPointer->ValidPointer[Count].Pos.z);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			//*glEnd();
			ValidPointer_RenderPointXYZ(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));

			i_Vector = Q_ValidPointer->ValidPointer[Count].UpVec;
			Qpo->Camera_Set();
			glColor3f(1.0f, 0.0f, 0.0f);	//RED
			//*glBegin(GL_LINES);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x, Q_ValidPointer->ValidPointer[Count].Pos.y, Q_ValidPointer->ValidPointer[Count].Pos.z);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			//*glEnd();
			ValidPointer_RenderPointXYZ(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));

			i_Vector = Q_ValidPointer->ValidPointer[Count].InVec;
			Qpo->Camera_Set();
			glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
			//*glBegin(GL_LINES);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x, Q_ValidPointer->ValidPointer[Count].Pos.y, Q_ValidPointer->ValidPointer[Count].Pos.z);
			glVertex3f(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			//*glEnd();
			ValidPointer_RenderPointXYZ(Q_ValidPointer->ValidPointer[Count].Pos.x + (i_Vector.x * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.y + (i_Vector.y * Q_ValidPointer->ValidPointer[Count].Scale), Q_ValidPointer->ValidPointer[Count].Pos.z + (i_Vector.z * Q_ValidPointer->ValidPointer[Count].Scale));
			}break;
		}

	glEnable(GL_BLEND);
#endif
	}

void Q_ShellAlpha::ValidPointer_RenderPoint(QpoVec3d Position)
	{
	QpoVertex ILvert;
	ILvert.x = Position.x;
	ILvert.y = Position.y;
	ILvert.z = Position.z;
	ILvert.r = 255;
	ILvert.g = 255;
	ILvert.b = 255;
	ILvert.a = 0.5;

	Qpo->Poly_AddOnce(&ILvert, 1, Medias->greenyN, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.25f);
	}

void Q_ShellAlpha::ValidPointer_RenderPointXYZ(float PosX, float PosY, float PosZ)
	{
	QpoVertex ILvert;
	ILvert.x = PosX;
	ILvert.y = PosY;
	ILvert.z = PosZ;
	ILvert.r = 255;
	ILvert.g = 255;
	ILvert.b = 255;
	ILvert.a = 0.5;

	Qpo->Poly_AddOnce(&ILvert, 1, Medias->greenyN, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.25f);
	}

};