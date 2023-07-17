/*

	unGameEvents - Game Events
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

///// Keep this light as it will use a script parser eventually !!!!

#include <cassert>
#include <iostream>
#include "SDL.h"

#include "../QActiveFramewrk.h"

#include "../../Server/unsStringCompressor.h"
#include "../../Server/UNSResource.h"

#include "../Utility/unConsole.h"

#include "../../DigitalMass/Source/Geometry/unTrrCellSettings.h"

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-MeleeHits.h"
#include "Q-WE-BulletSystem.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-CloudControl.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-AI-NNbot.h"

using namespace QAGE;
using namespace GUI;
using namespace RakNet;

bool KeyPress = false;

bool testc(void)
{
	printf("Trace testc\n");
	return true;
}

class testclass
{
public:
	bool testfunction(void) { printf("Trace m_testfunctioninstance\n"); return true; }
};

testclass m_testclass;

namespace QAGE
{

bool QActiveFramewrk::acGizmoTrans(const EventArgs& e)
{
	printf("Trace acGizmoTrans\n");

#if 0
	bool (*functionPtr)(void) = NULL;

	void (unAvatar::*pt2Member01)(int) = NULL;
	float (unAvatar::*pt2Member02)(void) = NULL;

	pt2Member01 = &unAvatar::executeAction;
	pt2Member02 = &unAvatar::getLodLevel;

	typedef testclass i_typedefinition;

	functionPtr = &i_typedefinition::testfunction;

	//printf("Member function 01 Address %ul\n", pt2Member01);
	//printf("Member function 02 Address %ul\n", pt2Member02);

	unAvatar instance1;
	float result = (instance1.*pt2Member02)();
#endif

	float trrscale = TCELL_GRID_SCALE;

	if(m_trrCursorType == 0)
		{
		/// Instance Gizmo
		if(!m_buildActive) return false;
		
		QpoVec3d gizmopos = trrcursor->getPos();

		///// Four Compass Directions
		if(e.m_response->EventID == 0)
			{
			trrcursor->incPos(0, 0, trrscale * GUI_GIZMO_MULT3);
			//trrbill->setScale(5);
			}

		if(e.m_response->EventID == 1)
			{
			trrcursor->incPos(trrscale * GUI_GIZMO_MULT3, 0, 0);
			}

		if(e.m_response->EventID == 2)
			{
			trrcursor->incPos(0, 0, -trrscale * GUI_GIZMO_MULT3);
			}

		if(e.m_response->EventID == 3)
			{
			trrcursor->incPos(-trrscale * GUI_GIZMO_MULT3, 0, 0);
			}

		//// Acellerated Movement
		if(e.m_response->EventID == 4)
			{
			trrcursor->incPos(0, 0, trrscale * GUI_GIZMO_MULT2);
			}

		if(e.m_response->EventID == 5)
			{
			trrcursor->incPos(trrscale * GUI_GIZMO_MULT1, 0, 0);
			}

		if(e.m_response->EventID == 6)
			{
			trrcursor->incPos(0, 0, -trrscale * GUI_GIZMO_MULT2);
			}

		if(e.m_response->EventID == 7)
			{
			trrcursor->incPos(-trrscale * GUI_GIZMO_MULT1, 0, 0);
			}

		if(e.m_response->EventID == 8)
			{
			trrcursor->incPos(0, 0, trrscale * GUI_GIZMO_MULT1);
			}

		if(e.m_response->EventID == 9)
			{
			trrcursor->incPos(0, 0, -trrscale * GUI_GIZMO_MULT1);
			}

		////// Height Adjustments
		if(e.m_response->EventID == 10)
			{
			trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT3, 0);
			}

		if(e.m_response->EventID == 11)
			{
			trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT2, 0);
			}

		if(e.m_response->EventID == 12)
			{
			trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT1, 0);
			}

		if(e.m_response->EventID == 13)
			{
			trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT1, 0);
			}

		if(e.m_response->EventID == 14)
			{
			trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT2, 0);
			}

		if(e.m_response->EventID == 15)
			{
			trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT3, 0);
			}

		float stretch = TCELL_GRID_SIZE * trrscale;

		if(m_trrToolIndex != 0)		////// AXIAL alligned tool
			{
			QpoVec3d i_qpovec = trrcursor->getPos();
			PxVec3 i_vectorgizmo(gizmopos.x, gizmopos.y, gizmopos.z);
			PxVec3 i_vectorpoint(i_qpovec.x, i_qpovec.y, i_qpovec.z);

			///// Place the tool
			if(m_trrToolCutter == 2 || m_trrToolCutter == 3) acToolPlace(i_vectorgizmo, i_vectorpoint, m_trrToolCutter, 0);
			if(m_trrToolLevel == 1 || m_trrToolLevel == 2 || m_trrToolLevel == 2) acToolPlace(i_vectorgizmo, i_vectorpoint, m_trrToolLevel + 3, 0);
			if(m_trrToolRaise == 1 || m_trrToolRaise == 2) acToolPlace(i_vectorgizmo, i_vectorpoint, m_trrToolRaise + 6, 0);
			if(m_trrToolSmooth == 1) acToolPlace(i_vectorgizmo, i_vectorpoint, m_trrToolSmooth + 9, 0);

			//for (int k=0; k < veccellbuffer.size(); ++k) veccellbuffer[k]->m_resetCount++;
			}
		}
	else
		{
		if(m_trrCursorType == 1)
			{
			///// Four Compass Directions
			if(e.m_response->EventID == 0)
				{
				m_trrToolScale += 1;

				printf("Trace m_trrToolScale %f\n", m_trrToolScale);
				}

			if(e.m_response->EventID == 1)
				{
				///Remember x axis invert
				}

			if(e.m_response->EventID == 2)
				{
				if(m_trrToolScale - 1 > 1) m_trrToolScale -= 1;
				else m_trrToolScale = 1;

				printf("Trace m_trrToolScale %f\n", m_trrToolScale);
				}

#if 0
			if(e.m_response->EventID == 3)
				{
				//// Shape change
				}

			//// Acellerated Movement
			if(e.m_response->EventID == 4)
				{
				trrcursor->incPos(0, 0, trrscale * GUI_GIZMO_MULT2);
				}

			if(e.m_response->EventID == 5)
				{
				trrcursor->incPos(trrscale * GUI_GIZMO_MULT1, 0, 0);
				}

			if(e.m_response->EventID == 6)
				{
				trrcursor->incPos(0, 0, -trrscale * GUI_GIZMO_MULT2);
				}

			if(e.m_response->EventID == 7)
				{
				trrcursor->incPos(-trrscale * GUI_GIZMO_MULT1, 0, 0);
				}

			if(e.m_response->EventID == 8)
				{
				trrcursor->incPos(0, 0, trrscale * GUI_GIZMO_MULT1);
				}

			if(e.m_response->EventID == 9)
				{
				trrcursor->incPos(0, 0, -trrscale * GUI_GIZMO_MULT1);
				}

			////// Height Adjustments
			if(e.m_response->EventID == 10)
				{
				trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT3, 0);
				}

			if(e.m_response->EventID == 11)
				{
				trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT2, 0);
				}

			if(e.m_response->EventID == 12)
				{
				trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT1, 0);
				}

			if(e.m_response->EventID == 13)
				{
				trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT1, 0);
				}

			if(e.m_response->EventID == 14)
				{
				trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT2, 0);
				}

			if(e.m_response->EventID == 15)
				{
				trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT3, 0);
				}
#endif
			}
		}

#if 0
			int cellx,celly;
			int gx,gy;
			veccellbuffer.clear();

			QpoVec3d i_cursorvec = trrcursor->getPos();
			PxVec3 sizevec(i_cursorvec.x, i_cursorvec.y, i_cursorvec.z);
			sizevec -= gizmopos;
			PxVec3 strvec = sizevec;
			float size = sizevec.normalize();
			int span = TRR_GRID_SIZE * TCELL_GRID_SCALE;
			m_cellspan = (int)ceil((float)size/span) + 1;
			PxVec3 pntvec = gizmopos;
			PxVec3 brushvec;
			bool dupcheck;

			if(size > (TRR_GRID_SIZE * TCELL_GRID_SCALE))
				{
				size = (TRR_GRID_SIZE * TCELL_GRID_SCALE);
				strvec = sizevec * size;
				}

			for (int cv=0; cv < m_cellspan; ++cv)
				{
				brushvec = pntvec - gizmopos;
				if(brushvec.normalize() > size) pntvec = gizmopos;

				////// Loop Point ////// Push one cell //////
				m_terrain->findCell(pntvec, &cellx, &celly);
				icTerrainCell* cell = m_terrain->searchTerrain(cellx, celly);
				dupcheck = false;
				for (int k=0; k < veccellbuffer.size(); ++k) if(cell == veccellbuffer[k]) dupcheck = true;
				if(!dupcheck) veccellbuffer.push_back(cell);

				///// Edge Update Check
				cell->trrGrid.acLocateStack(pntvec, &gx, &gy);

				///// Right edge checks
				if(gx == TRR_GRID_SIZE - 1)
					{
					m_terrain->findCell(PxVec3(pntvec.x + TCELL_GRID_SCALE, pntvec.y, pntvec.z), &cellx, &celly);
					icTerrainCell* edgecell = m_terrain->searchTerrain(cellx, celly);
					dupcheck = false;
					for (int k=0; k < veccellbuffer.size(); ++k) if(edgecell == veccellbuffer[k]) dupcheck = true;
					if(!dupcheck) veccellbuffer.push_back(edgecell);
					}

				if(gy == TRR_GRID_SIZE - 1)
					{
					m_terrain->findCell(PxVec3(pntvec.x, pntvec.y, pntvec.z + TCELL_GRID_SCALE), &cellx, &celly);
					icTerrainCell* belowcell = m_terrain->searchTerrain(cellx, celly);
					dupcheck = false;
					for (int k=0; k < veccellbuffer.size(); ++k) if(belowcell == veccellbuffer[k]) dupcheck = true;
					if(!dupcheck) veccellbuffer.push_back(belowcell);
					}

				pntvec += strvec;
				}

			///// Place the tool
			if(m_trrToolCutter == 2 || m_trrToolCutter == 3) acToolPlace(gizmopos, trrcursor->getPos(), m_trrToolCutter, 0);
			if(m_trrToolLevel == 1 || m_trrToolLevel == 2 || m_trrToolLevel == 2) acToolPlace(gizmopos, trrcursor->getPos(), m_trrToolLevel + 3, 0);
			if(m_trrToolRaise == 1 || m_trrToolRaise == 2) acToolPlace(gizmopos, trrcursor->getPos(), m_trrToolRaise + 6, 0);
			if(m_trrToolSmooth == 1) acToolPlace(gizmopos, trrcursor->getPos(), m_trrToolSmooth + 9, 0);

			for (int k=0; k < veccellbuffer.size(); ++k) veccellbuffer[k]->m_resetCount++;
			}
		}
	else if(m_trrCursorType == 1)
		{
		///// Four Compass Directions
		if(e.m_response->EventID == 0)
			{
			m_trrToolScale += 1;

			printf("Trace m_trrToolScale %f\n", m_trrToolScale);
			}

		if(e.m_response->EventID == 1)
			{
			///Remember x axis invert
			}

		if(e.m_response->EventID == 2)
			{
			if(m_trrToolScale - 1 > 1) m_trrToolScale -= 1;
			else m_trrToolScale = 1;

			printf("Trace m_trrToolScale %f\n", m_trrToolScale);
			}

		if(e.m_response->EventID == 3)
			{
			//// Shape change
			}

#if 1
		//// Acellerated Movement
		if(e.m_response->EventID == 4)
			{
			trrcursor->incPos(0, 0, trrscale * GUI_GIZMO_MULT2);
			trrbill->incPos(0, 0, trrscale * GUI_GIZMO_MULT2);
			}

		if(e.m_response->EventID == 5)
			{
			trrcursor->incPos(trrscale * GUI_GIZMO_MULT1, 0, 0);
			trrbill->incPos(trrscale * GUI_GIZMO_MULT1, 0, 0);
			}

		if(e.m_response->EventID == 6)
			{
			trrcursor->incPos(0, 0, -trrscale * GUI_GIZMO_MULT2);
			trrbill->incPos(0, 0, -trrscale * GUI_GIZMO_MULT2);
			}

		if(e.m_response->EventID == 7)
			{
			trrcursor->incPos(-trrscale * GUI_GIZMO_MULT1, 0, 0);
			trrbill->incPos(-trrscale * GUI_GIZMO_MULT1, 0, 0);
			}

		if(e.m_response->EventID == 8)
			{
			trrcursor->incPos(0, 0, trrscale * GUI_GIZMO_MULT1);
			trrbill->incPos(0, 0, trrscale * GUI_GIZMO_MULT1);
			}

		if(e.m_response->EventID == 9)
			{
			trrcursor->incPos(0, 0, -trrscale * GUI_GIZMO_MULT1);
			trrbill->incPos(0, 0, -trrscale * GUI_GIZMO_MULT1);
			}

		////// Height Adjustments
		if(e.m_response->EventID == 10)
			{
			trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT3, 0);
			trrbill->incPos(0, trrscale * GUI_GIZMO_MULT3, 0);
			}

		if(e.m_response->EventID == 11)
			{
			trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT2, 0);
			trrbill->incPos(0, trrscale * GUI_GIZMO_MULT2, 0);
			}

		if(e.m_response->EventID == 12)
			{
			trrcursor->incPos(0, trrscale * GUI_GIZMO_MULT1, 0);
			trrbill->incPos(0, trrscale * GUI_GIZMO_MULT1, 0);
			}

		if(e.m_response->EventID == 13)
			{
			trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT1, 0);
			trrbill->incPos(0, -trrscale * GUI_GIZMO_MULT1, 0);
			}

		if(e.m_response->EventID == 14)
			{
			trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT2, 0);
			trrbill->incPos(0, -trrscale * GUI_GIZMO_MULT2, 0);
			}

		if(e.m_response->EventID == 15)
			{
			trrcursor->incPos(0, -trrscale * GUI_GIZMO_MULT3, 0);
			trrbill->incPos(0, -trrscale * GUI_GIZMO_MULT3, 0);
			}
#endif
		}

		}
#endif

	return true;
}

bool QActiveFramewrk::acGizmoSymbols(const EventArgs& e)
{
	printf("Trace QActiveFramewrk::acGizmoSymbols\n");

	///// trr Tool Placement
	if(e.m_response->EventID == 16)
		{
		if(m_trrToolCutter == 1) m_trrToolCutter = 0;
		else if(m_trrToolCutter == 2) m_trrToolCutter = 3;
		else if(m_trrToolCutter == 3) m_trrToolCutter = 2;
		else m_trrToolCutter = 1;
		}

	///// trr Tool Cutting
	if(e.m_response->EventID == 17)
		{
		if(m_trrToolCutter == 2) m_trrToolCutter = 0;
		else if(m_trrToolCutter == 1) m_trrToolCutter = 3;
		else if(m_trrToolCutter == 3) m_trrToolCutter = 1;
		else m_trrToolCutter = 2;
		}

	///// trr Tool Level Floor
	if(e.m_response->EventID == 18)
		{
		if(m_trrToolLevel == 1) m_trrToolLevel = 0;
		else if(m_trrToolLevel == 2) m_trrToolLevel = 3;
		else if(m_trrToolLevel == 3) m_trrToolLevel = 2;
		else m_trrToolLevel = 1;
		}

	///// trr Tool Level Ceiling
	if(e.m_response->EventID == 19)
		{
		if(m_trrToolLevel == 2) m_trrToolLevel = 0;
		else if(m_trrToolLevel == 1) m_trrToolLevel = 3;
		else if(m_trrToolLevel == 3) m_trrToolLevel = 1;
		else m_trrToolLevel = 2;
		}

	///// trr Tool Raise
	if(e.m_response->EventID == 20)
		{
		if(m_trrToolRaise == 1) m_trrToolRaise = 0;
		else if(m_trrToolRaise == 2 || m_trrToolRaise == 0) m_trrToolRaise = 1;
		}

	///// trr Tool Lower
	if(e.m_response->EventID == 21)
		{
		if(m_trrToolRaise == 2) m_trrToolRaise = 0;
		else if(m_trrToolRaise == 1 || m_trrToolRaise == 0) m_trrToolRaise = 2;
		}

	///// trr Tool Smooth
	if(e.m_response->EventID == 22)
		{
		if(m_trrToolSmooth == 1) m_trrToolSmooth = 0;
		else m_trrToolSmooth = 1;
		}

	if(e.m_response->EventID == 23)
		{
		if(m_trrUpdate == 1) m_trrUpdate = 0;
		else m_trrUpdate = 1;
		}

	if(e.m_response->EventID == 24)
		{
		m_trrUpdate = 2;
		}

	m_buildActive = true;
	acBuildMode(m_buildActive);

	m_trrToolIndex = m_trrToolCutter + m_trrToolLevel + m_trrToolRaise + m_trrToolSmooth;

	return true;
}

bool QActiveFramewrk::acGameEventsFrame(void)
{
	if(KEY_DOWN(QIN_RBUTTON) && !KEY_DOWN(QIN_SHIFT) && !g_render->fullscreen && 0)
		{
		PxVec3 i_vecpoint;
#if 0
		int i_Cell;
		/*if(g_render->fullscreen) i_vecpoint = DigiMass->acPick(temppos.x, temppos.y);
		else*/ i_vecpoint = DigiMass->acPick(temppos.x - 8, temppos.y - 48, &i_Cell);
#endif

#if 0
		DigiMass->acPositionTool(temppos.x - 8, temppos.y - 48, 1);
#endif

		//veccellbuffer = DigiMass->acTool(temppos.x - 8, temppos.y - 48, 1, m_trrToolScale, &i_vecpoint);

#if 0
		trrcursor->setPos(i_vecpoint.x, i_vecpoint.y, i_vecpoint.z);
		if(gPickStay) DigiMass->PickSetPosition(i_vecpoint);

		QpoVec3d i_Position;
		i_Position.x = i_vecpoint.x;
		i_Position.y = i_vecpoint.y;
		i_Position.z = i_vecpoint.z;

		///// Add point Light
		if(m_BuildLight.m_ON) Qpo->Light_SetAttr(m_BuildLight.m_Light, &i_Position, &m_BuildLight.m_Color, m_BuildLight.m_Radius, false);
		else
			{
			m_BuildLight.m_Light = Qpo->Light_AddtoWorld(i_Position);

			m_BuildLight.m_Radius = 1500;
			m_BuildLight.m_Color.red = 255;
			m_BuildLight.m_Color.green = 255;
			m_BuildLight.m_Color.blue = 255;
			m_BuildLight.m_Color.alpha = 255;

			m_BuildLight.m_ON = true;
			}

		if(i_Cell > 0 && i_Cell < f_TrrBank->m_TerrainCell.size())
			{
			//PxVec3 i_pos = f_TrrBank->acGetPosition(i_Cell - 1, 0);
			//f_TrrBank->acSetPosition(i_Cell - 1, 0, i_pos.x, i_pos.y - 0.25, i_pos.z);

			//veccellbuffer.push_back(i_Cell);

			//DigiMass->acPositionTool(temppos.x - 8, temppos.y - 48, 1);
			}
#endif

#if 0
		///// Place trr tool set
		int cellx,celly;
		int gx,gy;
		veccellbuffer.clear();

		f_TrrBank->acLocateCell(i_vecpoint, &cellx, &celly);
#endif

#if 0
		float size = (m_trrToolScale*2);
		int span = TRR_GRID_SIZE * TCELL_GRID_SCALE;
		m_cellspanx = (int)ceil((float)size/span) + 1;
		m_cellspany = (int)ceil((float)size/span) + 1;
		PxVec3 pntvec = i_vecpoint;
		int cellinc = 0;
		bool dupcheck;
		bool collumn = false;

		if(size > (TRR_GRID_SIZE * TCELL_GRID_SCALE)) size = (TRR_GRID_SIZE * TCELL_GRID_SCALE);

		pntvec.z = i_vecpoint.z - m_trrToolScale;
		for (int cy=0; cy < m_cellspany; ++cy)
			{
			pntvec.x = i_vecpoint.x - m_trrToolScale;
			if(pntvec.z > i_vecpoint.z + m_trrToolScale) pntvec.z = i_vecpoint.z + m_trrToolScale;	/// FIXME: toolShape == m_trrToolScalexm_trrToolScale

			for (int cx=0; cx < m_cellspanx; ++cx)
				{
				if(pntvec.x > i_vecpoint.x + m_trrToolScale) pntvec.x = i_vecpoint.x + m_trrToolScale;	/// FIXME: toolScale == m_trrToolScale

				////// Loop Point ////// Push one cell //////
				m_terrain->findCell(pntvec, &cellx, &celly);
				icTerrainCell* cell = m_terrain->searchTerrain(cellx, celly);
				dupcheck = false;
				for (int k=0; k < veccellbuffer.size(); ++k) if(cell == veccellbuffer[k]) dupcheck = true;
				if(!dupcheck)
					{
					veccellbuffer.push_back(cell);
					cellinc++;
					}

				///// Edge Update Check
				cell->trrGrid.acLocateStack(pntvec, cell->m_Instance[0].x, cell->m_Instance[0].y, cell->m_Instance[0].z, &gx, &gy);

				///// Right edge checks
				if(gx == TRR_GRID_SIZE - 1)
					{
					m_terrain->findCell(PxVec3(pntvec.x + TCELL_GRID_SCALE, pntvec.y, pntvec.z), &cellx, &celly);
					icTerrainCell* edgecell = m_terrain->searchTerrain(cellx, celly);
					dupcheck = false;
					for (int k=0; k < veccellbuffer.size(); ++k) if(edgecell == veccellbuffer[k]) dupcheck = true;
					if(!dupcheck) veccellbuffer.push_back(edgecell);
					}

				if(gy == TRR_GRID_SIZE - 1 && cy == (m_cellspany - 1))
					{
					m_terrain->findCell(PxVec3(pntvec.x, pntvec.y, pntvec.z + TCELL_GRID_SCALE), &cellx, &celly);
					icTerrainCell* belowcell = m_terrain->searchTerrain(cellx, celly);
					dupcheck = false;
					for (int k=0; k < veccellbuffer.size(); ++k) if(belowcell == veccellbuffer[k]) dupcheck = true;
					if(!dupcheck) veccellbuffer.push_back(belowcell);
					}
				pntvec.x += size;
				}
			if(cellinc == 1) collumn = true;
			cellinc = 0;
			pntvec.z += size;
			}

		///// Row
		if(cellinc == 0) m_cellspany = 1;
		///// Collumn
		if(collumn) m_cellspanx = 1;
#endif


		///// Place the tool
		if(m_trrToolCutter == 2 || m_trrToolCutter == 3) acToolPlace(i_vecpoint, i_vecpoint, m_trrToolCutter, 1);
		if(m_trrToolLevel == 1 || m_trrToolLevel == 2 || m_trrToolLevel == 3) acToolPlace(i_vecpoint, i_vecpoint, m_trrToolLevel + 3, 1);
		if(m_trrToolRaise == 1 || m_trrToolRaise == 2) acToolPlace(i_vecpoint, i_vecpoint, m_trrToolRaise + 6, 1);
		if(m_trrToolSmooth == 1) acToolPlace(i_vecpoint, i_vecpoint, m_trrToolSmooth + 9, 1);

		//for (int k=0; k < veccellbuffer.size(); ++k) veccellbuffer[k]->m_resetCount++;
		}

	if(m_trrCursorType == 1 && m_trrToolIndex != 0)
		{
		if(m_trrCursorAlpha + 0.2 < 1)
			{
			m_trrCursorAlpha += 0.2;

			//WritableObject<CgFxEffect> trreffect (ReadableObject<CgFx>(trrspherefx)->getEffect());
			//trreffect->setFloatParameterValue (trreffect->getParameterByName ("g_fAlpha"), &m_trrCursorAlpha);
			}
		else m_trrCursorAlpha = 1;
		}
	else
		{
		if(m_trrCursorAlpha - 0.2 > 0)
			{
			m_trrCursorAlpha -= 0.2;

			//WritableObject<CgFxEffect> trreffect (ReadableObject<CgFx>(trrspherefx)->getEffect());
			//trreffect->setFloatParameterValue (trreffect->getParameterByName ("g_fAlpha"), &m_trrCursorAlpha);
			}
		else m_trrCursorAlpha = 0;
		}

	if(KEY_DOWN(QIN_MBUTTON))
		{
		DigiMass->PickActor(gMouseDepth, temppos.x - 8, temppos.y - 48);

		if(KEY_DOWN(QIN_RBUTTON))
			{
			//if(!vecvarDpress[3])
			//	{
			//	vecvarDpress[3] = true;

				if(gPickStay) gPickStay = false;
				else gPickStay = true;
			//	}
			}
		//else vecvarDpress[3] = false;
		}
	else
		{
		if(!gPickStay) DigiMass->PickRelease();
		}

	//Position
	//QActiveFrameWork->f_TrrBank->acAddClone(0, i_gridincrement, -355.446411, -i_gridincrement);

#if 0
	//WritableObject<PointLight> pointlight (pointLitHdl);
	//PxVec3 raytest = acScreenRay(m_mousex, m_mousey);
	
	//ReadableObject<nvsg::Camera> pCamera(GVARS::Camera);
	//PxVec3 rayOrigin = PxVec3();
	//PxVec3 rayDirection = PxVec3();
	//pCamera->getPickRay(m_mousex, 600-m_mousey, 800, 600, rayOrigin, rayDirection);

	//rayDirection.normalize();

	//raytest += rayDirection * m_player->m_zoomfactor;

	//WritableObject<icBillboard> trrbill (trrcursorbill);
	//trrbill->setPosition(raytest);
	//trrbill->updateCamera (GVARS::Camera);
	//pointlight->setPosition(raytest);

	//PxVec3 boardpos = trrbill->getPos();

	//printf("Trace billboard pos x %f y %f z %f\n", boardpos[0], boardpos[1], boardpos[2]);

	////// 3D frame
	if(m_buildActive)
		{	//// BUILD MODE
		//WritableObject<icBillboard> (trrcursorbill)->updateCamera (GVARS::Camera);

		if(m_trrCursorType == 1)
			{
			if(m_trrToolCutter == 1 || m_trrToolCutter == 2 || m_trrToolCutter == 3 || m_trrToolLevel == 1 || m_trrToolLevel == 2 || m_trrToolLevel == 3 || m_trrToolRaise == 1 || m_trrToolRaise == 2 || m_trrToolSmooth == 1)	//// FIXME add button for selecting mouse ray picker
				{
				//WritableObject<icBillboard> trrcursor (trrcursor);
				//WritableObject<icBillboard> trrbill (trrcursorbill);

				//ReadableObject<nvsg::Camera> pCamera(GVARS::Camera);

				//PxVec3 campos = pCamera->getPos();
				//PxVec3 gizpos = campos + (pCamera->getDirection() * (float)65);

				//PxVec3 raytest = acScreenRay(m_mousex, m_mousey);

				//// IF cursor and Sphere
				//trrcursor->setPosition (raytest);
				//trrbill->setPosition (raytest);

				//Trafo trafo;
				//trafo.setTranslation (PxVec3(raytest[0], raytest[1] + 0.075, raytest[2]));
				//WritableObject<Transform> (trrtrans)->setTrafo (trafo);

				if(m_mouseright)
					{
					int cellx,celly;
					int gx,gy;
					veccellbuffer.clear();

					float size = (m_trrToolScale*2);
					int span = TRR_GRID_SIZE * TCELL_GRID_SCALE;
					m_cellspanx = (int)ceil((float)size/span) + 1;
					m_cellspany = (int)ceil((float)size/span) + 1;
					PxVec3 pntvec = raytest;
					int cellinc = 0;
					bool dupcheck;
					bool collumn = false;

					if(size > (TRR_GRID_SIZE * TCELL_GRID_SCALE)) size = (TRR_GRID_SIZE * TCELL_GRID_SCALE);

					pntvec.z = raytest[2] - m_trrToolScale;
					for (int cy=0; cy < m_cellspany; ++cy)
						{
						pntvec.x = raytest[0] - m_trrToolScale;
						if(pntvec.z > raytest[2] + m_trrToolScale) pntvec.z = raytest[2] + m_trrToolScale;	/// FIXME: toolShape == m_trrToolScalexm_trrToolScale

						for (int cx=0; cx < m_cellspanx; ++cx)
							{
							if(pntvec.x > raytest[0] + m_trrToolScale) pntvec.x = raytest[0] + m_trrToolScale;	/// FIXME: toolScale == m_trrToolScale

							////// Loop Point ////// Push one cell //////
							m_terrain->findCell(pntvec, &cellx, &celly);
							icTerrainCell* cell = m_terrain->searchTerrain(cellx, celly);
							dupcheck = false;
							for (int k=0; k < veccellbuffer.size(); ++k) if(cell == veccellbuffer[k]) dupcheck = true;
							if(!dupcheck)
								{
								veccellbuffer.push_back(cell);
								cellinc++;
								}

							///// Edge Update Check
							cell->trrGrid.acLocateStack(pntvec, &gx, &gy);

							///// Right edge checks
							if(gx == TRR_GRID_SIZE - 1)
								{
								m_terrain->findCell(PxVec3(pntvec.x + TCELL_GRID_SCALE, pntvec.y, pntvec.z), &cellx, &celly);
								icTerrainCell* edgecell = m_terrain->searchTerrain(cellx, celly);
								dupcheck = false;
								for (int k=0; k < veccellbuffer.size(); ++k) if(edgecell == veccellbuffer[k]) dupcheck = true;
								if(!dupcheck) veccellbuffer.push_back(edgecell);
								}

							if(gy == TRR_GRID_SIZE - 1 && cy == (m_cellspany - 1))
								{
								m_terrain->findCell(PxVec3(pntvec.x, pntvec.y, pntvec.z + TCELL_GRID_SCALE), &cellx, &celly);
								icTerrainCell* belowcell = m_terrain->searchTerrain(cellx, celly);
								dupcheck = false;
								for (int k=0; k < veccellbuffer.size(); ++k) if(belowcell == veccellbuffer[k]) dupcheck = true;
								if(!dupcheck) veccellbuffer.push_back(belowcell);
								}
							pntvec.x += size;
							}
						if(cellinc == 1) collumn = true;
						cellinc = 0;
						pntvec.z += size;
						}

					///// Row
					if(cellinc == 0) m_cellspany = 1;
					///// Collumn
					if(collumn) m_cellspanx = 1;

					///// Place the tool
					if(m_trrToolCutter == 2 || m_trrToolCutter == 3) acToolPlace(raytest, raytest, m_trrToolCutter, 1);
					if(m_trrToolLevel == 1 || m_trrToolLevel == 2 || m_trrToolLevel == 3) acToolPlace(raytest, raytest, m_trrToolLevel + 3, 1);
					if(m_trrToolRaise == 1 || m_trrToolRaise == 2) acToolPlace(raytest, raytest, m_trrToolRaise + 6, 1);
					if(m_trrToolSmooth == 1) acToolPlace(raytest, raytest, m_trrToolSmooth + 9, 1);

					for (int k=0; k < veccellbuffer.size(); ++k) veccellbuffer[k]->m_resetCount++;
					}
				}
			}

		if(m_trrCursorType == 1 && m_trrToolIndex != 0)
			{
			if(m_trrCursorAlpha + 0.2 < 1)
				{
				m_trrCursorAlpha += 0.2;

				WritableObject<CgFxEffect> trreffect (ReadableObject<CgFx>(trrspherefx)->getEffect());
				trreffect->setFloatParameterValue (trreffect->getParameterByName ("g_fAlpha"), &m_trrCursorAlpha);
				}
			else m_trrCursorAlpha = 1;
			}
		else
			{
			if(m_trrCursorAlpha - 0.2 > 0)
				{
				m_trrCursorAlpha -= 0.2;

				WritableObject<CgFxEffect> trreffect (ReadableObject<CgFx>(trrspherefx)->getEffect());
				trreffect->setFloatParameterValue (trreffect->getParameterByName ("g_fAlpha"), &m_trrCursorAlpha);
				}
			else m_trrCursorAlpha = 0;
			}
#endif

#if 1
		if(m_mousemid_limb)
			{
			m_buildActive = true;
			if(m_trrCursorType == 1)
				{
				m_trrCursorType = 0;

				//trrcursor->setPosition (raytest);
				//trrbill->setPosition (raytest);
				}
			else m_trrCursorType = 1;
			}
#endif

#if 0
		}
#endif

	return true;
}

////// '.trr' Process Placement Tool //////
bool QActiveFramewrk::acToolPlace(PxVec3 startpos, PxVec3 destpos, int toolIndex, int toolShape)
{
	printf("Trace QActiveFramewrk::acToolPlace\n");

	if(toolShape == 0)		  ////// TOOL Point Placement
		{
		float theta,height = 0;

		if(toolIndex != 0)
			{
			//// Cell Buffer Increment
			int bufferinc = 0;

			//// Construct Vertex Placement
			PxVec3 trans = destpos - startpos;
			int nbVertex = trans.magnitude() / TCELL_GRID_SCALE;

			for (int k=0; k < nbVertex; ++k)
				{
				int x,y;
				PxVec3 vertpos = startpos + (trans * (float)k);

#pragma warning("FIXME::Add edge checking then increment reset counters")
				for(int i_celliter = 0; i_celliter < veccellbuffer.size(); i_celliter++)
					{
					f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLocateStack(vertpos, f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->m_Instance[0]->x, f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->m_Instance[0]->y, f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->m_Instance[0]->z, &x, &y);

					if((x >= 0 && x < TRR_GRID_SIZE) && (y >= 0 && y < TRR_GRID_SIZE))
						{
						f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLevelVertex(x, y, vertpos[1], toolIndex);
						}
					}
				}
			}
		}
	else if(toolShape == 1)	  ////// TOOL Sphere Placement
		{
		if(toolIndex < 9)
			{
			//// Sphere Stack
			acSphereStack(destpos, m_trrToolScale, toolIndex);
			}
		if(toolIndex == 10)
			{
			//// Smooth Stack
			acSphereSmooth(destpos, m_trrToolScale, toolIndex);
			}
		}

	return true;

#if 0
	if(toolShape == 0)		  ////// TOOL Point Placement
		{
		float theta,height = 0;

		if(toolIndex != 0)
			{
			//// Cell Buffer Increment
			int bufferinc = 0;

			//// Construct Vertex Placement
			PxVec3 trans = destpos - startpos;
			int nbVertex = trans.normalize() / TCELL_GRID_SCALE;

			for (int k=0; k < nbVertex; ++k)
				{
				int x,y;
				PxVec3 vertpos = startpos + (trans * (float)k);
				veccellbuffer[bufferinc]->trrGrid.acLocateStack(vertpos, &x, &y);
				if(x < 1 || x > TRR_GRID_SIZE - 1 || y < 1 || y > TRR_GRID_SIZE - 1)
					{
					bufferinc++;
					veccellbuffer[bufferinc]->trrGrid.acLocateStack(vertpos, &x, &y);
					if(x < 2) x = 128;
					if(x > TRR_GRID_SIZE - 1) x = 1;
					if(y < 2) x = 128;
					if(y > TRR_GRID_SIZE - 1) y = 1;
					} 
				
				veccellbuffer[bufferinc]->trrGrid.acLevelVertex(x, y, vertpos[1], toolIndex);

				////// Edge Seam Joining
				if(x == TRR_GRID_SIZE - 1)
					{
					if(toolIndex == 2 || toolIndex == 3) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, y, height + vertpos[1], toolIndex);
					else if(toolIndex == 7) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, y, (sqrt(height))/2, toolIndex);
					else if(toolIndex == 8) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, y, (-sqrt(height))/3, toolIndex);
					else if(toolIndex == 4 || toolIndex == 5 || toolIndex == 6) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, y, vertpos[1], toolIndex);
					}

				if(y == TRR_GRID_SIZE - 1)
					{
					///// Inner Edge
					if(toolIndex == 2 || toolIndex == 3) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(x, 0, height + vertpos[1], toolIndex);
					else if(toolIndex == 7) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(x, 0, (sqrt(height))/2, toolIndex);
					else if(toolIndex == 8) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(x, 0, (-sqrt(height))/3, toolIndex);
					else if(toolIndex == 4 || toolIndex == 5 || toolIndex == 6) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(x, 0, vertpos[1], toolIndex);
					}
				}
			}
		}
	else if(toolShape == 1)	  ////// TOOL Sphere Placement
		{
		if(toolIndex < 9)
			{
			//// Sphere Stack
			acSphereStack(destpos, m_trrToolScale, toolIndex);
			}

		if(toolIndex == 10)
			{
			//// Smooth Stack
			acSphereSmooth(destpos, m_trrToolScale, toolIndex);
			}
		}

	return true;
#endif
}

void QActiveFramewrk::acSphereStack(PxVec3 origin, float scale, int toolIndex)
{
	printf("Trace QActiveFramewrk::acSphereStack\n");

	//// Locate Center Point
	int posx,posy;

	for(int i_celliter = 0; i_celliter < veccellbuffer.size(); i_celliter++)
		{
		f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLocateStack(origin, f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->m_Instance[0]->x, f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->m_Instance[0]->y, f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->m_Instance[0]->z, &posx, &posy);

		if((posx >= 0 && posx < TRR_GRID_SIZE) && (posy >= 0 && posy < TRR_GRID_SIZE))
			{
			printf("Trace Point 1\n");
			//// Normalise Variables
			float gscale = (float)TCELL_GRID_SCALE;
			float ruler = scale / gscale;
			printf("Trace ruler %f\n", ruler);
			float theta, height;
			int dim = ruler * 2;
			int gridx = posx - scale;
			int gridy = posy - scale;
			int bx = gridx;
			int by = gridy;
			bool edgetrav = false;
			PxVec3 pntvec = origin;
			PxVec3 brushvec;

			printf("Trace scale %f gridy %i dim %i\n", scale, gridy, dim);

			//// Stack Loop
			pntvec.z = origin.z - ruler;
			for (int y = gridy; y < gridy + dim; ++y)
				{
				pntvec.x = origin.x - ruler;

				printf("Trace Point 2\n");

				if(y >= 0 && y < TRR_GRID_SIZE)
					{

					printf("Trace Point 3\n");

					for (int x = gridx; x < gridx + dim; ++x)
						{

						printf("Trace Point 4\n");

						if(x >= 0 && x < TRR_GRID_SIZE)
							{

							printf("Trace Point 5\n");

							brushvec = pntvec - origin;
							float length = brushvec.magnitude();

							if(length <= ruler)
								{

								printf("Trace Point 6\n");

								/////// Member of Stack Calculate Height
								theta = acos(length / ruler);
								height = sin(theta) * ruler;

#pragma warning("FIXME::Add edge checking then increment reset counters")

								if((x >= 0 && x < TRR_GRID_SIZE) && (y >= 0 && y < TRR_GRID_SIZE))
									{
									printf("Trace Point 7\n");
									
									if(toolIndex == 1 || toolIndex == 3) f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLevelVertex(bx, by, height + origin.y, toolIndex);
									else if(toolIndex == 2 || toolIndex == 3) f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLevelVertex(bx, by, 0, toolIndex);
									else if(toolIndex == 7) f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLevelVertex(bx, by, (sqrt(height))/2, toolIndex);
									else if(toolIndex == 8) f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLevelVertex(bx, by, (-sqrt(height))/3, toolIndex);
									else if(toolIndex == 4 || toolIndex == 5 || toolIndex == 6) f_TrrBank->m_TerrainCell[veccellbuffer[i_celliter]]->trrGrid->acLevelVertex(bx, by, origin.y, toolIndex);
									}
								}
							}
						}

					pntvec.x += gscale;
					}
				pntvec.z += gscale;
				}
			}//END if bounds check
		}//END for loop

#if 0
	//// Locate Center Point
	int posx,posy;
	veccellbuffer[0]->trrGrid.acLocateStack(origin, &posx, &posy);

	//// Normalise Variables
	float gscale = TCELL_GRID_SCALE;
	float ruler = scale / gscale;
	float theta,height;
	int dim = ruler * 2;
	int gridx = posx - scale;
	int gridy = posy - scale;
	int bx = gridx;
	int by = gridy;
	bool edgetrav = false;
	PxVec3 pntvec = origin;
	PxVec3 brushvec;

	//// Cell Buffer Increment
	int bufferinc = 0;
	int bufferstr = 0;

	//// Stack Loop
	pntvec.z = origin.z - ruler;
	for (int y = gridy; y < gridy + dim; ++y)
		{
		pntvec.x = origin.x - ruler;
		bx = gridx;

		if(by >= TRR_GRID_SIZE)
			{
			//// trrpass Package
			bufferstr = bufferinc + 1;
			by = 1;
			}

		////// Reset Buffer Position
		bufferinc = bufferstr;

		for (int x = gridx; x < gridx + dim; ++x)
			{
			brushvec = pntvec - origin;
			float length = brushvec.normalize();
			if(length <= ruler)
				{
				//// Loop Point
				if(bx >= 0 && by >= 0)
					{
					if(bx >= TRR_GRID_SIZE)
						{
						//// trrpass Package
						if(edgetrav && y == (gridy + dim) - 1)
							{
							//bufferinc += m_cellspanx;
							bufferinc += 2;
							bx = 1;
							}
						else
							{
							bufferinc++;
							bx = 1;
							}

						///// Reset Edge Traversing
						edgetrav = false;
						}

					/////// Member of Stack Calculate Height
					theta = acos(length / ruler);
					height = sin(theta) * ruler;

					if(toolIndex == 1 || toolIndex == 3) veccellbuffer[bufferinc]->trrGrid.acLevelVertex(bx, by, height + origin.y, toolIndex);
					else if(toolIndex == 2 || toolIndex == 3) veccellbuffer[bufferinc]->trrGrid.acLevelVertex(bx, by, 0, toolIndex);
					else if(toolIndex == 7) veccellbuffer[bufferinc]->trrGrid.acLevelVertex(bx, by, (sqrt(height))/2, toolIndex);
					else if(toolIndex == 8) veccellbuffer[bufferinc]->trrGrid.acLevelVertex(bx, by, (-sqrt(height))/3, toolIndex);
					else if(toolIndex == 4 || toolIndex == 5 || toolIndex == 6) veccellbuffer[bufferinc]->trrGrid.acLevelVertex(bx, by, origin.y, toolIndex);

					////// Edge Seam Joining
					if(bx == TRR_GRID_SIZE - 1)
						{
						if(toolIndex == 1 || toolIndex == 3) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, by, height + origin.y, toolIndex);
						else if(toolIndex == 2 || toolIndex == 3) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, by, 0, toolIndex);
						else if(toolIndex == 7) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, by, (sqrt(height))/2, toolIndex);
						else if(toolIndex == 8) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, by, (-sqrt(height))/3, toolIndex);
						else if(toolIndex == 4 || toolIndex == 5 || toolIndex == 6) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, by, origin.y, toolIndex);
						}

					if(by == TRR_GRID_SIZE - 1)
						{
						if(y == (gridy + dim) - 1)	///// Outer Edge Bottom
							{
							if(toolIndex == 1 || toolIndex == 3) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(bx, 0, height + origin.y, toolIndex);
							else if(toolIndex == 2 || toolIndex == 3) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(bx, 0, 0, toolIndex);
							else if(toolIndex == 7) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(bx, 0, (sqrt(height))/2, toolIndex);
							else if(toolIndex == 8) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(bx, 0, (-sqrt(height))/3, toolIndex);
							else if(toolIndex == 4 || toolIndex == 5 || toolIndex == 6) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(bx, 0, origin.y, toolIndex);
							edgetrav = true;
							}
						else						///// Inner Edge
							{
							if(toolIndex == 1 || toolIndex == 3) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(bx, 0, height + origin.y, toolIndex);
							else if(toolIndex == 2 || toolIndex == 3) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(bx, 0, 0, toolIndex);
							else if(toolIndex == 7) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(bx, 0, (sqrt(height))/2, toolIndex);
							else if(toolIndex == 8) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(bx, 0, (-sqrt(height))/3, toolIndex);
							else if(toolIndex == 4 || toolIndex == 5 || toolIndex == 6) veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(bx, 0, origin.y, toolIndex);
							edgetrav = true;
							}
						}
					}                                                                                                                                                                                                                       
				}

			bx++;
			pntvec.x += gscale;
			}
		by++;
		pntvec.z += gscale;
		}
#endif
}

void QActiveFramewrk::acSphereSmooth(PxVec3 origin, float scale, int toolIndex)
{
#if 0
	//// Locate Center Point
	int posx,posy;
	veccellbuffer[0]->trrGrid.acLocateStack(origin, &posx, &posy);

	//// Normalise Variables
	float gscale = TCELL_GRID_SCALE;
	float ruler = scale / gscale;
	int dim = ruler * 2;
	int gridx = posx - scale;
	int gridy = posy - scale;
	int bx = gridx;
	int by = gridy;
	bool edgetrav = false;
	PxVec3 pntvec = origin;
	PxVec3 brushvec;
	int pntmap = 0;
	int cntmap = 0;
	float adjustment = 0;
	float factor;

	//// Cell Buffer Increment
	int bufferinc = 0;
	int bufferstr = 0;

	//// Generate Helper Map
	float* vertexmap = new float[(scale*2) * (scale*2)];

	//// Grid Traverse Loop
	for (int y = gridy; y < gridy + dim; ++y)
		{
		bx = gridx;

		if(by >= TRR_GRID_SIZE)
			{
			//// trrpass Package
			bufferstr = bufferinc + 1;
			by = 1;
			}

		////// Reset Buffer Position
		bufferinc = bufferstr;

		for (int x = gridx; x < gridx + dim; ++x)
			{
			//// Loop Point
			if(bx >= 0 && by >= 0)
				{
				if(bx >= TRR_GRID_SIZE)
					{
					//// trrpass Package
					bufferinc++;
					bx = 1;
					}

				vertexmap[pntmap] = veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
				pntmap++;
				}
			bx++;
			}
		by++;
		}

	//// Normalise Variables
	bx = gridx;
	by = gridy;
	pntvec = origin;

	//// Cell Buffer Increment
	bufferinc = 0;
	bufferstr = 0;

	//// Stack Loop
	pntvec.z = origin.z - ruler;
	for (int y = gridy; y < gridy + dim; ++y)
		{
		pntvec.x = origin.x - ruler;
		bx = gridx;

		if(by >= TRR_GRID_SIZE)
			{
			//// trrpass Package
			bufferstr = bufferinc + 1;
			by = 1;
			}

		////// Reset Buffer Position
		bufferinc = bufferstr;

		for (int x = gridx; x < gridx + dim; ++x)
			{
			brushvec = pntvec - origin;
			float length = brushvec.normalize();

			if(length <= ruler)
				{
				//// Loop Point
				if(bx >= 0 && by >= 0)
					{
					if(bx >= TRR_GRID_SIZE)
						{
						//// trrpass Package
						if(edgetrav && y == (gridy + dim) - 1)
							{
							//bufferinc += m_cellspanx;
							bufferinc += 2;
							bx = 1;
							}
						else
							{
							bufferinc++;
							bx = 1;
							}

						///// Reset Edge Traversing
						edgetrav = false;
						}

					//// Generate Smoothing Height Adjustment
					//// First Row
					adjustment = 0;
					if(x - 1 >= gridx && y - 1 >= gridy) factor = vertexmap[(cntmap - (int)dim) - 1] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;

					if(y - 1 >= gridy) factor = vertexmap[cntmap - (int)dim] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;

					if(x + 1 < gridx + dim && y - 1 >= gridy) factor = vertexmap[(cntmap - (int)dim) + 1] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;

					//// Middle Row
					if(x - 1 >= gridx) factor = vertexmap[cntmap - 1] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;

					factor = vertexmap[cntmap] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					adjustment += factor;

					if(x + 1 < gridx + dim) factor = vertexmap[cntmap + 1] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;

					//// Bottom Row
					if(x - 1 >= gridx && y + 1 < gridy + dim) factor = vertexmap[(cntmap + (int)dim) - 1] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;

					if(y + 1 < gridy + dim) factor = vertexmap[cntmap + (int)dim] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;

					if(x + 1 < gridx + dim && y + 1 < gridy + dim) factor = vertexmap[(cntmap + (int)dim) + 1] - veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height;
					else factor = 0;
					adjustment += factor;
					adjustment = veccellbuffer[bufferinc]->trrGrid.Grid[bx][by].layers[0].y_height + (adjustment/25);

					///// Smooth Vert
					veccellbuffer[bufferinc]->trrGrid.acLevelVertex(bx, by, adjustment, toolIndex);

					////// Edge Seam Joining
					if(bx == TRR_GRID_SIZE - 1) veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(0, by, adjustment, toolIndex);

					if(by == TRR_GRID_SIZE - 1)
						{
						if(y == (gridy + dim) - 1)	///// Outer Edge Bottom
							{
							veccellbuffer[bufferinc+1]->trrGrid.acLevelVertex(bx, 0, adjustment, toolIndex);
							edgetrav = true;
							}
						else						///// Inner Edge
							{
							veccellbuffer[bufferinc+m_cellspanx]->trrGrid.acLevelVertex(bx, 0, adjustment, toolIndex);
							edgetrav = true;
							}
						}
					}
				}

			//// Increment Vertex Map Counter
			cntmap++;

			bx++;
			pntvec.x += gscale;
			}
		by++;
		pntvec.z += gscale;
		}

	delete [] vertexmap;

#endif
}

PxVec3 QActiveFramewrk::acRayPick(PxVec3 origin, PxVec3 destination)
{
#if 0
   //we will use a RayIntersectTraverser and get the intersection point.
   //If there is no intersection point, so we will compute the intersection point
   // between the ray and a virtual plane perpendicular plane, passing by 0

   nvtraverser::RayIntersectTraverser * pPicker;
   pPicker = new nvtraverser::RayIntersectTraverser;
   //pPicker->addRef(); //I don't think it is still used on NVSG 3.2, but I'm not sure at all

#if 0
   ReadableObject<Camera> pCamera(Camera);

   PxVec3 rayOrigin = PxVec3();
   PxVec3 rayDirection = PxVec3();
   int m_iRAHeight = 600;// = int(m_pRA->getViewportHeight());
   int m_iRAWidth = 800;// = int(m_pRA->getViewportWidth());

   //pCamera->getPickRay(screenx, m_iRAHeight-screeny, m_iRAWidth, m_iRAHeight, rayOrigin, rayDirection);
   //pPicker->setRay( rayOrigin, rayDirection );

   PxVec3 direction = destination - origin;

   direction.normalize();

   pPicker->setRay( origin, direction );

   // do the hit test
   pPicker->setViewState(m_player->getViewState());
   pPicker->apply(m_sceneHdl);

   if (pPicker->getNumberOfIntersections() > 0)
   {
	   nvtraverser::Intersection intersection = pPicker->getNearest();

	   return intersection.getIsp();
   
       //setTargetPosition(intersection.getIsp(), Camera);
   }
   else //if we don't touch anything, so we try to compute the intersection with the virtual perpendicular plane passing by 0   
   {
	   return destination;
#if 0
       float t;

       //N = Normal vector to the plan in front of the camera
       PxVec3 N = -(pCamera->getDirection());
       PxVec3 Q;

       //getTargetPosition(Camera, Q);

       float alpha = -N[0]*Q[0] - N[1]*Q[1] - N[2]*Q[2];
       float NRo = N*rayOrigin;
       float NRd = N*rayDirection;
       t = (-alpha - NRo) / NRd;

       PxVec3 Rt = rayOrigin + rayDirection*t;

       //setTargetPosition(Rt, pCameraHdl);
#endif
   }

   // clean up
   //pPicker->removeRef();
   pPicker->release();
   pPicker = NULL;
#endif
#endif
return PxVec3(0,0,0);
}

PxVec3 QActiveFramewrk::acScreenRay(int screenx, int screeny)
{
#if 0
   //we will use a RayIntersectTraverser and get the intersection point.
   //If there is no intersection point, so we will compute the intersection point
   // between the ray and a virtual plane perpendicular plane, passing by 0

   nvtraverser::RayIntersectTraverser * pPicker;
   pPicker = new nvtraverser::RayIntersectTraverser;
   //pPicker->addRef(); //I don't think it is still used on NVSG 3.2, but I'm not sure at all

   ReadableObject<nvsg::Camera> pCamera(GVARS::Camera);

   PxVec3 rayOrigin = PxVec3();
   PxVec3 rayDirection = PxVec3();
   int m_iRAHeight = 600;// = int(m_pRA->getViewportHeight());
   int m_iRAWidth = 800;// = int(m_pRA->getViewportWidth());

   pCamera->getPickRay(screenx, m_iRAHeight-screeny, m_iRAWidth, m_iRAHeight, rayOrigin, rayDirection);
   pPicker->setRay( rayOrigin, rayDirection );

   //PxVec3 direction = destination - origin;

   //direction.normalize();

   //pPicker->setRay( origin, direction );

   // do the hit test
   pPicker->setViewState(m_player->getViewState());
   pPicker->apply(m_sceneHdl);

   if (pPicker->getNumberOfIntersections() > 0)
   {
	   nvtraverser::Intersection intersection = pPicker->getNearest();

	   DrawableHandle* object = intersection.getDrawable();

	   PxVec3 intersectray = intersection.getIsp();

	   if(object != trrsphereobj && intersectray.normalize() > 1) return intersection.getIsp();

#if 0
	   nvtraverser::Intersection intersection = pPicker->getNearest();

	   DrawableHandle* object = intersection.getDrawable();

	   if(object ==  trrsphereobj) return PxVec3(0,0,0);

	   return intersection.getIsp();
#endif

	PxVec3 stretchvec;
    PxVec3 nearvec;
	float stretchlength = -1;
	float nearlength = -1;

	for (int k=0; k < pPicker->getNumberOfIntersections(); ++k)
		{
		const nvtraverser::Intersection* intersections = pPicker->getIntersections();

		DrawableHandle* object = intersections[k].getDrawable();

		if(object !=  trrsphereobj)
			{
			stretchvec = intersections[k].getIsp() - rayOrigin;
			stretchlength = stretchvec.normalize();
			if(stretchlength < nearlength || nearlength == -1)
				{
				nearvec = intersections[k].getIsp();
				nearlength = stretchlength;
				}
			}
		}

		intersectray = nearvec;

		if(nearvec.normalize() > 1) return nearvec;
   
       //setTargetPosition(intersection.getIsp(), Camera);
   }
   else //if we don't touch anything, so we try to compute the intersection with the virtual perpendicular plane passing by 0   
   {
	   return PxVec3(0,0,0);
#if 0
       float t;

       //N = Normal vector to the plan in front of the camera
       PxVec3 N = -(pCamera->getDirection());
       PxVec3 Q;

       //getTargetPosition(Camera, Q);

       float alpha = -N[0]*Q[0] - N[1]*Q[1] - N[2]*Q[2];
       float NRo = N*rayOrigin;
       float NRd = N*rayDirection;
       t = (-alpha - NRo) / NRd;

       PxVec3 Rt = rayOrigin + rayDirection*t;

       //setTargetPosition(Rt, pCameraHdl);
#endif
   }

   // clean up
   //pPicker->removeRef();
   pPicker->release();
   pPicker = NULL;
#endif

return PxVec3(0,0,0);
}

void QActiveFramewrk::acBuildMode(bool buildMode)
{
#if 0
	if(buildMode && !m_trrCursorActive)
		{
		Game* i_game = Game::instance();

		m_trrCursorActive = true;

		/*trrcursor = CreateHandle (icBillboardHandle);
		  {
			WritableObject<icBillboard> trrcursor (trrcursor);
			trrcursor->initialize (Vec2f (1.5, 1.5), PxVec3 (0, 1, 0));
		  }*/
		trrcursorbill = CreateHandle (icBillboardHandle);
		  {
			WritableObject<icBillboard> trrbill (trrcursorbill);
			trrbill->initialize (Vec2f (1.5, 1.5), PxVec3 (0, 1, 0), 7);
		  }
		//i_game->addRootChild (trrcursor);
		i_game->addRootChild (trrcursorbill);

		trrsphere = CreateHandle (GeoNodeHandle);
		trrtrans = CreateHandle (TransformHandle);
		WritableObject<Transform> (trrtrans)->addChild (trrsphere);

#if 0
		CgFxHandle *cgfxHdl = CreateHandle (CgFxHandle);
			{
			std::string err;
			WritableObject<CgFxEffect> cgfxEffect (ReadableObject<CgFx>(cgfxHdl)->getEffect());
			std::string currentpath;
			vutil::GetCurrentDir (currentpath);
			currentpath += "./../data/shaders/sky/Sky.fx";
			if (!cgfxEffect->createFromFile(currentpath.c_str (), err))
			  assert (0);
			}
#endif

		icTextureBank* i_texturebank = icTextureBank::instance();

		TextureAttributeHandle *texAttribHdl = CreateHandle(TextureAttributeHandle);
		WritableObject<TextureAttribute> texAttrib (texAttribHdl);

		////// Gizmo //////
		texAttrib->bindTextureAttributeItem(i_texturebank->vecNVtextures[3],0);

		trrspherefx = CreateHandle (CgFxHandle);
			{
			std::string err;
			WritableObject<CgFxEffect> cgfxEffect (ReadableObject<CgFx>(trrspherefx)->getEffect());
			std::string currentpath;
			nvutil::GetCurrentDir (currentpath);
			currentpath += "./../data/shaders/trrTool.fx";
			if (!cgfxEffect->createFromFile(currentpath.c_str (), err))
				assert (0);

			float alpha = 0.6f;
			cgfxEffect->setFloatParameterValue (cgfxEffect->getParameterByName ("g_fAlpha"), &alpha);

			float size = 1.0f;
			cgfxEffect->setFloatParameterValue (cgfxEffect->getParameterByName ("g_fSize"), &size);

			ReadableObject<TextureAttributeItem> texItem (i_texturebank->vecNVtextures[3]);
			cgfxEffect->setSamplerTextureImage (cgfxEffect->getParameterByName ("samDiffuseMap"),
			texItem->getTextureImage ());
			}

		StateSetHandle *stateSetHdl = CreateHandle (StateSetHandle);
			{
			WritableObject<StateSet> stateSet (stateSetHdl);
			stateSet->addAttribute(trrspherefx);
			stateSet->addAttribute(texAttribHdl);
			}

		WritableObject<GeoNode> sphereNode (trrsphere);

		TrianglesHandle *triangleshand = icShapesHelper::createSphereGeometry (PxVec3(5,5,5), 100, true);
		WritableObject<Triangles> triangles (triangleshand);
		trrsphereobj = nvutil::getHandle<DrawableHandle>( triangles );

		sphereNode->addGeometry (triangleshand, stateSetHdl);

		i_game->addRootChild (trrtrans);
		}
#endif
}

bool QActiveFramewrk::acGuiIntCancel(const EventArgs& e)
{
	/////// Cancel Panes
#if 0
	m_GUI->vecpane[e.m_response->m_PaneID]->m_visible = false;
#endif

	acRequestData("Data/QoreResource/TestDocument.qore", 4, 15);

#if 0
	if(!i_ServerRes)
		{
#endif
		m_GUI->m_DocumentBank->m_Document.push_back(new TumDocument("Data/QoreResource/TestDocument.qore", "Data/QoreResource/TestDocument.qore"));

#if 0
		}
#endif

	return true;
}

bool QActiveFramewrk::acRequestLine(const char *i_Filename, unsigned int i_AddressIndex)
{
	int useTimeStamp;
	long timeStamp;
	int typeId;

	useTimeStamp = ID_TIMESTAMP;
	timeStamp = RakNet::GetTime();
	typeId = UNS_REQUEST_LINE;

	//BitStream *i_BitStream = new BitStream;
	/*i_BitStream->acPushAlloc(useTimeStamp);
	i_BitStream.acPushAlloc(timeStamp);
	i_BitStream.acPushAlloc(typeId);

	i_BitStream.acPushAlloc(i_AddressIndex);*/
	//WriteStringToBitStream(i_Filename, i_BitStream);

	//unPeer->Send(i_BitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
	return true;
}

bool QActiveFramewrk::acRequestData(const char *i_Filename, unsigned int i_StartIndex, unsigned int i_EndIndex)
{
	//BitStream i_BitTransfer(UNS_REQUEST_DATA);

	//icBitStream.acPushAlloc(i_StartIndex);
	//icBitStream.acPushAlloc(i_EndIndex);
	//WriteStringToBitStream(i_Filename, i_BitTransfer);

	bool i_Success;// = unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
	return i_Success;
}

bool QActiveFramewrk::acRequestPage(const char *i_Filename, unsigned int i_StartIndex, unsigned int i_NomLines)
{
	int useTimeStamp;
	long timeStamp;
	int typeId;

	useTimeStamp = ID_TIMESTAMP;
	timeStamp = RakNet::GetTime();
	typeId = UNS_REQUEST_PAGE;

	//BitStream *i_BitStream = new BitStream;
	/*i_BitStream.acPushAlloc(useTimeStamp);
	i_BitStream.acPushAlloc(timeStamp);
	i_BitStream.acPushAlloc(typeId);

	i_BitStream.acPushAlloc(i_StartIndex);
	i_BitStream.acPushAlloc(i_NomLines);*/
	//WriteStringToBitStream(i_Filename, i_BitStream);

	//unPeer->Send(i_BitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
	return true;
}

#if 0
unsigned char PacketPumpInterface::GetPacketIdentifier(Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	else
		return (unsigned char) p->data[0];
}
#else
int QActiveFramewrk::GetPacketIdentifier(Packet *p)
{
	if ((int)p->data[0] == ID_TIMESTAMP)
		return (int) p->data[sizeof(int) + sizeof(long)];
	else
		return (int) p->data[0];
}
#endif

bool QActiveFramewrk::acNetConnect(const EventArgs& e)
{
	unsStringCompressor::AddReference();
	printf("Connecting to QAGE Server\n");

	m_GUI->vecpane[3]->m_visible = false;

	//----- Connect to 'Unification QAGE Server'
	int i_clientPort = 10000;	//60007 10000
	Q_PlacementMarker->m_Count += 15;
	i_clientPort += Q_PlacementMarker->m_Count;

	printf("client port %i/n", i_clientPort);

	SocketDescriptor socketDescriptor(i_clientPort,0);

#if 0
	clientAddress.SetBinaryAddress("192.168.1.102");
#else
	clientAddress.SetBinaryAddress("localhost");
#endif

	clientAddress.port = i_clientPort;

	unPeer->Startup(1, 30, &socketDescriptor, 1);
	unPeer->SetOccasionalPing(true);

	bool Success = false;

#if 0
#if 0
	Success = unPeer->Connect("87.106.104.248", 10555, 0, 0);
#else
	Success = unPeer->Connect("localhost", 10358, "fractal18", (int) strlen("fractal18"));
#endif
#else
	Success = unPeer->Connect("82.165.16.114", 1001, "", 0);
#endif

	if(Success) printf("Connected to QAGE Server\n");
	else
		{
		printf("ERROR: Cannot connect to server\n");
		return false;
		}

#if 0
#if 1
	serveAddress.SetBinaryAddress("87.106.104.248");
	printf("serveAddress.SetBinaryAddress 87.106.104.248\n");
#else
	serveAddress.SetBinaryAddress("localhost");
	printf("serveAddress.SetBinaryAddress = 'localhost'\n");
#endif
#else
	serveAddress.SetBinaryAddress("82.165.16.114");
	printf("serveAddress.SetBinaryAddress 82.16.165.114\n");
#endif

	serveAddress.port = 1833;

#if 1
	///// Set the internal packet pump state
	if(m_PP_STATE == 0)
		{
		m_PP_STATE = 1;

		m_mutex_unPeer = SDL_CreateMutex();
		m_mutex_Packet = SDL_CreateMutex();
		m_mutex_Request = SDL_CreateMutex();
		m_mutex_State = SDL_CreateMutex();

		vec_Packet = new PacketVectorSwing();

		m_PacketSocket.m_unPeer = unPeer;
		m_PacketSocket.m_vec_Packet = vec_Packet;
		m_PacketSocket.m_mutex_unPeer = m_mutex_unPeer;
		m_PacketSocket.m_mutex_Packet = m_mutex_Packet;
		m_PacketSocket.Start();

		m_PacketPump.m_unPeer = unPeer;
		m_PacketPump.m_vec_Packet = vec_Packet;
		m_PacketPump.m_mutex_unPeer = m_mutex_unPeer;
		m_PacketPump.m_mutex_Packet = m_mutex_Packet;
		m_PacketPump.m_mutex_State = m_mutex_State;
		m_PacketPump.m_QActiveFramework = this;
		QNetwork.m_QActiveFramework = this;
		m_PacketPump.serveAddress = serveAddress;
		m_PacketPump.clientAddress = clientAddress;
		m_PacketPump.Start();

		m_PacketStack.m_unPeer = unPeer;
		m_PacketStack.m_mutex_unPeer = m_mutex_unPeer;
		m_PacketStack.m_mutex_Request = m_mutex_Request;
		m_PacketStack.m_UNSResRequest = &m_UNSResRequest;
		m_PacketStack.m_DocumentBank = m_DocumentBank;
		m_PacketStack.m_map_Documents = &m_map_Documents;
		m_PacketStack.serveAddress = serveAddress;
		m_PacketStack.clientAddress = clientAddress;
		m_PacketStack.Start();

		m_NetStart = true;
		}
#endif

return false;
}

bool QActiveFramewrk::acNetConnectQAA(SystemAddress f_Address)
{
if(!g_NetConnect)
	{
	g_NetConnect = true;
	printf("Connecting to Q.A.Arena Server\n");

	m_GUI->vecpane[3]->m_visible = false;

	//----- Connect to 'Unification QAGE Server'
	int i_clientPort = 10000;	//60007 10000
	Q_PlacementMarker->m_Count += 15;
	i_clientPort += Q_PlacementMarker->m_Count;

	printf("client port %i/n", i_clientPort);

	SocketDescriptor socketDescriptor(i_clientPort,0);

#if 1
	clientAddress.SetBinaryAddress("192.168.1.102");
#else
	clientAddress.SetBinaryAddress("localhost");
#endif

	clientAddress.port = i_clientPort;

	unPeer->Startup(1, 30, &socketDescriptor, 1);
	unPeer->SetOccasionalPing(true);

	bool Success = false;

#if 0
#if 0
	Success = unPeer->Connect("87.106.104.248", 10555, 0, 0);
#else
	Success = unPeer->Connect("localhost", 10358, "fractal18", (int) strlen("fractal18"));
#endif
#else
	Success = unPeer->Connect(f_Address.ToString(false), f_Address.port, "", 0);
#endif

	if(Success) printf("Connected to Q.A.Arena Server\n");
	else
		{
		printf("ERROR: Cannot connect to server\n");
		return false;
		}

#if 0
#if 1
	serveAddress.SetBinaryAddress("87.106.104.248");
	printf("serveAddress.SetBinaryAddress 87.106.104.248\n");
#else
	serveAddress.SetBinaryAddress("localhost");
	printf("serveAddress.SetBinaryAddress = 'localhost'\n");
#endif
#else
	serveAddress.SetBinaryAddress(f_Address.ToString(false));
	printf("serveAddress.SetBinaryAddress %s\n", f_Address.ToString(false));
#endif

	serveAddress.port = f_Address.port;

#if 1
	///// Set the internal packet pump state
	if(m_PP_STATE == 0)
		{
		m_PP_STATE = 1;

		m_mutex_unPeer = SDL_CreateMutex();
		m_mutex_Packet = SDL_CreateMutex();
		m_mutex_Request = SDL_CreateMutex();
		m_mutex_State = SDL_CreateMutex();

		vec_Packet = new PacketVectorSwing();

		m_PacketSocket.m_unPeer = unPeer;
		m_PacketSocket.m_vec_Packet = vec_Packet;
		m_PacketSocket.m_mutex_unPeer = m_mutex_unPeer;
		m_PacketSocket.m_mutex_Packet = m_mutex_Packet;
		m_PacketSocket.Start();

		m_PacketPump.m_unPeer = unPeer;
		m_PacketPump.m_vec_Packet = vec_Packet;
		m_PacketPump.m_mutex_unPeer = m_mutex_unPeer;
		m_PacketPump.m_mutex_Packet = m_mutex_Packet;
		m_PacketPump.m_mutex_State = m_mutex_State;
		m_PacketPump.m_QActiveFramework = this;
		QNetwork.m_QActiveFramework = this;
		m_PacketPump.serveAddress = serveAddress;
		m_PacketPump.clientAddress = clientAddress;
		m_PacketPump.Start();

		m_PacketStack.m_unPeer = unPeer;
		m_PacketStack.m_mutex_unPeer = m_mutex_unPeer;
		m_PacketStack.m_mutex_Request = m_mutex_Request;
		m_PacketStack.m_UNSResRequest = &m_UNSResRequest;
		m_PacketStack.m_DocumentBank = m_DocumentBank;
		m_PacketStack.m_map_Documents = &m_map_Documents;
		m_PacketStack.serveAddress = serveAddress;
		m_PacketStack.clientAddress = clientAddress;
		m_PacketStack.Start();

		m_NetStart = true;
		}
#endif

	// Set the Packet Pump MODE
	m_PacketPump.m_PP_MODE = 0;
	}

return true;
}

void QActiveFramewrk::WriteStringToBitStream(const char *myString, BitTransfer* output)
{
	stringCompressor->EncodeString(myString, UNS_LINE_MAX, output);
}

void QActiveFramewrk::WriteBitStreamToString(char *myString, BitTransfer* input)
{
	stringCompressor->DecodeString(myString, UNS_LINE_MAX, input);
}

};