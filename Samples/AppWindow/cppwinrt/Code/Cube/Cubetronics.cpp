/*

Cubetronics - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include "Include/Cube.h"

using namespace Cube;

namespace Cube
{

std::shared_ptr<BiVector> CubeKEY::acCenter(void)
{
	std::string f_ref_CurrentPath = "CubeKEY::acCenter";
	m_aabb->empty();

	for(unsigned int f_CountVertex = 0; f_CountVertex < m_Link->vec_Vertex.size(); f_CountVertex++)
		{
		*(m_aabb) += m_Link->vec_Vertex[f_CountVertex];
		}

	ag_StatusLive(f_ref_CurrentPath, "f_Result");

	return m_aabb->center();
}

int CubeKEY::acFindinLog(int f_Msg)
{
	int f_Find = 0;

	for(unsigned int f_CountLog = 0; f_CountLog < vec_Log.size(); f_CountLog++)
		{
		if(vec_Log[f_CountLog] == f_Msg)
			{
			f_Find++;
			}
		}

	return f_Find;
}

void ag_AttachCube(std::shared_ptr<Cube::CubeKEY> f_Target, std::shared_ptr<Cube::CubeKEY> f_Subject, float f_Margin)
{
	std::shared_ptr<BiVector> f_TargetMid = f_Target->acCenter();
	std::shared_ptr<BiVector> f_SubjectMid = f_Subject->acCenter();

	BiVector f_Pos = *(f_SubjectMid) - *(f_TargetMid);

	int f_Port = f_Subject->acFindinLog(CUBE_LOG_SERVED);

	//FIXME : fiddle port / add slide variance

	switch (f_Port)
		{
		default:
		case CUBE_PORT_XNEG:
			{ ////////
			 ////////
			// Pos
			for(unsigned int f_CountVertex = 0; f_CountVertex < f_Target->m_Link->vec_Vertex.size(); f_CountVertex++)
				{
#if 0
				f_Target->m_Link->vec_Vertex[f_CountVertex]->acStore();
#endif
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += f_Pos.m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += f_Pos.m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += f_Pos.m_Z;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += BiVector(-0.5 - f_Margin, 0, 0).m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += BiVector(-0.5 - f_Margin, 0, 0).m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += BiVector(-0.5 - f_Margin, 0, 0).m_Z;
				}

			f_Subject->vec_Log.push_back(CUBE_LOG_POSITIONED);

			  //////////
			 //////////
			// Verts
			f_Target->m_Link->vec_Vertex[4] = f_Subject->m_Link->vec_Vertex[0];
			f_Target->m_Link->vec_Vertex[5] = f_Subject->m_Link->vec_Vertex[1];
			f_Target->m_Link->vec_Vertex[6] = f_Subject->m_Link->vec_Vertex[2];
			f_Target->m_Link->vec_Vertex[7] = f_Subject->m_Link->vec_Vertex[3];
			}break;

		case CUBE_PORT_XPOS:
			{ ////////
			 ////////
			// Pos
			for(unsigned int f_CountVertex = 0; f_CountVertex < f_Target->m_Link->vec_Vertex.size(); f_CountVertex++)
				{
#if 0
				f_Target->m_Link->vec_Vertex[f_CountVertex]->acStore();
#endif
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += f_Pos.m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += f_Pos.m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += f_Pos.m_Z;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += BiVector(0.5 + f_Margin, 0, 0).m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += BiVector(0.5 + f_Margin, 0, 0).m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += BiVector(0.5 + f_Margin, 0, 0).m_Z;
				}

			f_Subject->vec_Log.push_back(CUBE_LOG_POSITIONED);

			  //////////
			 //////////
			// Verts
			f_Target->m_Link->vec_Vertex[0] = f_Subject->m_Link->vec_Vertex[4];
			f_Target->m_Link->vec_Vertex[1] = f_Subject->m_Link->vec_Vertex[5];
			f_Target->m_Link->vec_Vertex[2] = f_Subject->m_Link->vec_Vertex[6];
			f_Target->m_Link->vec_Vertex[3] = f_Subject->m_Link->vec_Vertex[7];
			}break;

		case CUBE_PORT_YNEG:
			{ ////////
			 ////////
			// Pos
			for(unsigned int f_CountVertex = 0; f_CountVertex < f_Target->m_Link->vec_Vertex.size(); f_CountVertex++)
				{
#if 0
				f_Target->m_Link->vec_Vertex[f_CountVertex]->acStore();
#endif
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += f_Pos.m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += f_Pos.m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += f_Pos.m_Z;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += BiVector(0, -0.5 - f_Margin, 0).m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += BiVector(0, -0.5 - f_Margin, 0).m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += BiVector(0, -0.5 - f_Margin, 0).m_Z;
				}

			f_Subject->vec_Log.push_back(CUBE_LOG_POSITIONED);

			  //////////
			 //////////
			// Verts
			f_Target->m_Link->vec_Vertex[2] = f_Subject->m_Link->vec_Vertex[0];
			f_Target->m_Link->vec_Vertex[3] = f_Subject->m_Link->vec_Vertex[1];
			f_Target->m_Link->vec_Vertex[6] = f_Subject->m_Link->vec_Vertex[4];
			f_Target->m_Link->vec_Vertex[7] = f_Subject->m_Link->vec_Vertex[5];
			}break;

		case CUBE_PORT_YPOS:
			{ ////////
			 ////////
			// Pos
			for(unsigned int f_CountVertex = 0; f_CountVertex < f_Target->m_Link->vec_Vertex.size(); f_CountVertex++)
				{
#if 0
				f_Target->m_Link->vec_Vertex[f_CountVertex]->acStore();
#endif
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += f_Pos.m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += f_Pos.m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += f_Pos.m_Z;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += BiVector(0, 0.5 + f_Margin, 0).m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += BiVector(0, 0.5 + f_Margin, 0).m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += BiVector(0, 0.5 + f_Margin, 0).m_Z;
				}

			f_Subject->vec_Log.push_back(CUBE_LOG_POSITIONED);

			  //////////
			 //////////
			// Verts
			f_Target->m_Link->vec_Vertex[0] = f_Subject->m_Link->vec_Vertex[2];
			f_Target->m_Link->vec_Vertex[1] = f_Subject->m_Link->vec_Vertex[3];
			f_Target->m_Link->vec_Vertex[4] = f_Subject->m_Link->vec_Vertex[6];
			f_Target->m_Link->vec_Vertex[5] = f_Subject->m_Link->vec_Vertex[7];
			}break;

		case CUBE_PORT_ZNEG:
			{ ////////
			 ////////
			// Pos
			for(unsigned int f_CountVertex = 0; f_CountVertex < f_Target->m_Link->vec_Vertex.size(); f_CountVertex++)
				{
#if 0
				f_Target->m_Link->vec_Vertex[f_CountVertex]->acStore();
#endif
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += f_Pos.m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += f_Pos.m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += f_Pos.m_Z;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += BiVector(0, 0, -0.5 - f_Margin).m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += BiVector(0, 0, -0.5 - f_Margin).m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += BiVector(0, 0, -0.5 - f_Margin).m_Z;
				}

			f_Subject->vec_Log.push_back(CUBE_LOG_POSITIONED);

			  //////////
			 //////////
			// Verts
			f_Target->m_Link->vec_Vertex[1] = f_Subject->m_Link->vec_Vertex[0];
			f_Target->m_Link->vec_Vertex[3] = f_Subject->m_Link->vec_Vertex[2];
			f_Target->m_Link->vec_Vertex[7] = f_Subject->m_Link->vec_Vertex[6];
			f_Target->m_Link->vec_Vertex[5] = f_Subject->m_Link->vec_Vertex[4];
			}break;

		case CUBE_PORT_ZPOS:
			{ ////////
			 ////////
			// Pos
			for(unsigned int f_CountVertex = 0; f_CountVertex < f_Target->m_Link->vec_Vertex.size(); f_CountVertex++)
				{
#if 0
				f_Target->m_Link->vec_Vertex[f_CountVertex]->acStore();
#endif
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += f_Pos.m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += f_Pos.m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += f_Pos.m_Z;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_X += BiVector(0, 0, 0.5 + f_Margin).m_X;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Y += BiVector(0, 0, 0.5 + f_Margin).m_Y;
				f_Target->m_Link->vec_Vertex[f_CountVertex]->m_Z += BiVector(0, 0, 0.5 + f_Margin).m_Z;
				}

			f_Subject->vec_Log.push_back(CUBE_LOG_POSITIONED);

			  //////////
			 //////////
			// Verts
			f_Target->m_Link->vec_Vertex[0] = f_Subject->m_Link->vec_Vertex[1];
			f_Target->m_Link->vec_Vertex[2] = f_Subject->m_Link->vec_Vertex[3];
			f_Target->m_Link->vec_Vertex[6] = f_Subject->m_Link->vec_Vertex[7];
			f_Target->m_Link->vec_Vertex[4] = f_Subject->m_Link->vec_Vertex[5];
			}break;
		}

	f_Subject->m_Served = true;
	f_Subject->vec_Child.push_back(f_Target);
	f_Subject->nom_Child++;
	f_Subject->vec_Log.push_back(CUBE_LOG_SERVED);

	f_Target->m_Served = true;
	f_Target->vec_Parent.push_back(f_Subject);
	f_Subject->nom_Parent++;
	f_Target->vec_Log.push_back(CUBE_LOG_WELD_ATTACH);
}

};