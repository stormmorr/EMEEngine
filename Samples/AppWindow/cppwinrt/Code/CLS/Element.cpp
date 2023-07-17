/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Target.h"

using namespace std;
using namespace ecoin;

namespace ecoin
{

BiVector g_SA_Vec;

void classElement::acGen_fromBicycle(std::shared_ptr<CubeBicycle> f_Bicycle)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "SecondaryAppWindowPageDX::acLoadShare";

	for(int f_Helly = 0; f_Helly < f_Bicycle->vec_Vertex.size(); f_Helly++)
		{
		vec_Vertex.push_back(f_Bicycle->vec_Vertex[f_Helly]);
		}

	for(int f_Helly = 0; f_Helly < f_Bicycle->vec_Color.size(); f_Helly++)
		{
		vec_Color.push_back(f_Bicycle->vec_Color[f_Helly]);
		}

	m_aabb = make_shared<aabb>();
	m_aabb->empty();

	for(unsigned int f_CountVertex = 0; f_CountVertex < vec_Vertex.size(); f_CountVertex++)
		{
		m_aabb->acAdd_vector(vec_Vertex[f_CountVertex]);
		}

	m_Center = m_aabb->center();
	m_Volume = m_aabb->volume();
}

void classElement::acSetup_Corners(void)
{
	classCorner f_Corner1;
	f_Corner1.acSpecify(vec_Vertex[0], vec_Vertex[1], vec_Vertex[4], vec_Vertex[2]);
	m_Result.m_vec_Corner.push_back(f_Corner1);

	classCorner f_Corner2;
	f_Corner2.acSpecify(vec_Vertex[1], vec_Vertex[0], vec_Vertex[5], vec_Vertex[3]);
	m_Result.m_vec_Corner.push_back(f_Corner2);

	classCorner f_Corner3;
	f_Corner3.acSpecify(vec_Vertex[2], vec_Vertex[3], vec_Vertex[6], vec_Vertex[0]);
	m_Result.m_vec_Corner.push_back(f_Corner3);

	classCorner f_Corner4;
	f_Corner4.acSpecify(vec_Vertex[3], vec_Vertex[2], vec_Vertex[7], vec_Vertex[1]);
	m_Result.m_vec_Corner.push_back(f_Corner4);

	classCorner f_Corner5;
	f_Corner5.acSpecify(vec_Vertex[4], vec_Vertex[5], vec_Vertex[0], vec_Vertex[6]);
	m_Result.m_vec_Corner.push_back(f_Corner5);

	classCorner f_Corner6;
	f_Corner6.acSpecify(vec_Vertex[5], vec_Vertex[4], vec_Vertex[1], vec_Vertex[7]);
	m_Result.m_vec_Corner.push_back(f_Corner6);

	classCorner f_Corner7;
	f_Corner7.acSpecify(vec_Vertex[6], vec_Vertex[7], vec_Vertex[2], vec_Vertex[4]);
	m_Result.m_vec_Corner.push_back(f_Corner7);

	classCorner f_Corner8;
	f_Corner8.acSpecify(vec_Vertex[7], vec_Vertex[6], vec_Vertex[3], vec_Vertex[5]);
	m_Result.m_vec_Corner.push_back(f_Corner8);
}

void classElement::acSync_fromBicycle(std::shared_ptr<CubeBicycle> f_Bicycle)
{
	for(int f_Helly = 0; f_Helly < f_Bicycle->vec_Vertex.size(); f_Helly++)
		{
		vec_Vertex[f_Helly]->m_X = f_Bicycle->vec_Vertex[f_Helly]->m_X;
		vec_Vertex[f_Helly]->m_Y = f_Bicycle->vec_Vertex[f_Helly]->m_Y;
		vec_Vertex[f_Helly]->m_Z = f_Bicycle->vec_Vertex[f_Helly]->m_Z;
		}

	for(int f_Helly = 0; f_Helly < f_Bicycle->vec_Color.size(); f_Helly++)
		{
		vec_Color[f_Helly]->m_X = f_Bicycle->vec_Color[f_Helly]->m_X;
		vec_Color[f_Helly]->m_Y = f_Bicycle->vec_Color[f_Helly]->m_Y;
		vec_Color[f_Helly]->m_Z = f_Bicycle->vec_Color[f_Helly]->m_Z;
		}

	while(vec_Color.size() < 8)
		{
		vec_Color.push_back(vec_Color[0]);
		}
}

void classElement::acSync_fromBicycle_affinity(std::shared_ptr<CubeBicycle> f_Bicycle)
{
	m_aabb->empty();

	for(unsigned int f_CountVertex = 0; f_CountVertex < vec_Vertex.size(); f_CountVertex++)
		{
		m_aabb->acAdd_vector(vec_Vertex[f_CountVertex]);
		}

	m_Center = m_aabb->center();
	m_Volume = m_aabb->volume();
}

void classElement::acStructuredAnalysis(void)
{
	g_SA_Vec.m_X = vec_Vertex[1]->m_X - vec_Vertex[0]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[1]->m_Y - vec_Vertex[0]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[1]->m_Z - vec_Vertex[0]->m_Z;
	m_Result.m_Dist01 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[2]->m_X - vec_Vertex[3]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[2]->m_Y - vec_Vertex[3]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[2]->m_Z - vec_Vertex[3]->m_Z;
	m_Result.m_Dist23 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[4]->m_X - vec_Vertex[5]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[4]->m_Y - vec_Vertex[5]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[4]->m_Z - vec_Vertex[5]->m_Z;
	m_Result.m_Dist45 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[6]->m_X - vec_Vertex[7]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[6]->m_Y - vec_Vertex[7]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[6]->m_Z - vec_Vertex[7]->m_Z;
	m_Result.m_Dist67 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[0]->m_X - vec_Vertex[2]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[0]->m_Y - vec_Vertex[2]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[0]->m_Z - vec_Vertex[2]->m_Z;
	m_Result.m_Dist02 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[1]->m_X - vec_Vertex[3]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[1]->m_Y - vec_Vertex[3]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[1]->m_Z - vec_Vertex[3]->m_Z;
	m_Result.m_Dist13 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[4]->m_X - vec_Vertex[6]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[4]->m_Y - vec_Vertex[6]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[4]->m_Z - vec_Vertex[6]->m_Z;
	m_Result.m_Dist46 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[5]->m_X - vec_Vertex[7]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[5]->m_Y - vec_Vertex[7]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[5]->m_Z - vec_Vertex[7]->m_Z;
	m_Result.m_Dist57 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[0]->m_X - vec_Vertex[4]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[0]->m_Y - vec_Vertex[4]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[0]->m_Z - vec_Vertex[4]->m_Z;
	m_Result.m_Dist04 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[1]->m_X - vec_Vertex[5]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[1]->m_Y - vec_Vertex[5]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[1]->m_Z - vec_Vertex[5]->m_Z;
	m_Result.m_Dist15 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[2]->m_X - vec_Vertex[6]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[2]->m_Y - vec_Vertex[6]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[2]->m_Z - vec_Vertex[6]->m_Z;
	m_Result.m_Dist26 = g_SA_Vec.acLength();

	g_SA_Vec.m_X = vec_Vertex[3]->m_X - vec_Vertex[7]->m_X;
	g_SA_Vec.m_Y = vec_Vertex[3]->m_Y - vec_Vertex[7]->m_Y;
	g_SA_Vec.m_Z = vec_Vertex[3]->m_Z - vec_Vertex[7]->m_Z;
	m_Result.m_Dist37 = g_SA_Vec.acLength();

	m_Result.m_Dist01234567 = (m_Result.m_Dist01 + m_Result.m_Dist23 + m_Result.m_Dist45 + m_Result.m_Dist67) / 4; //X
	m_Result.m_Dist02134657 = (m_Result.m_Dist02 + m_Result.m_Dist13 + m_Result.m_Dist46 + m_Result.m_Dist57) / 4; //Z
	m_Result.m_Dist04152637 = (m_Result.m_Dist04 + m_Result.m_Dist15 + m_Result.m_Dist26 + m_Result.m_Dist37) / 4; //Y

	m_Result.m_SurfToLegRatioX = ((m_Result.m_Dist01234567 - m_Result.m_Dist02134657) + (m_Result.m_Dist01234567 - m_Result.m_Dist04152637));
	m_Result.m_SurfToLegRatioZ = ((m_Result.m_Dist02134657 - m_Result.m_Dist01234567) + (m_Result.m_Dist02134657 - m_Result.m_Dist04152637));
	m_Result.m_SurfToLegRatioY = ((m_Result.m_Dist04152637 - m_Result.m_Dist02134657) + (m_Result.m_Dist04152637 - m_Result.m_Dist01234567));

	if((m_Result.m_SurfToLegRatioX > m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioX > m_Result.m_SurfToLegRatioZ))
		{
		if((m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioY / m_Result.m_SurfToLegRatioX;
			}
		else if((m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioY))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioZ / m_Result.m_SurfToLegRatioX;
			}
		}
	else if((m_Result.m_SurfToLegRatioY > m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioY > m_Result.m_SurfToLegRatioZ))
		{
		if((m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioX / m_Result.m_SurfToLegRatioY;
			}
		else if((m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioY))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioZ / m_Result.m_SurfToLegRatioY;
			}
		}
	else if((m_Result.m_SurfToLegRatioZ > m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioZ > m_Result.m_SurfToLegRatioX))
		{
		if((m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioX / m_Result.m_SurfToLegRatioZ;
			}
		else if((m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioY / m_Result.m_SurfToLegRatioZ;
			}
		}

	m_Result.m_LevelParent = -1;
	m_Result.m_Parent = nullptr;
}

int classElement::acSize_Surface(void)
{
	int f_ResultCount = 0;

	for(int f_Int = 0; f_Int < m_vec_Surface.size(); f_Int++)
		{
		if(m_vec_Surface[f_Int]->m_FULLON == true)
			{
			f_ResultCount++;
			}
		}

	return f_ResultCount;
}

int classElement::acSize_Leg(void)
{
	int f_ResultCount = 0;

	for(int f_Int = 0; f_Int < m_vec_Leg.size(); f_Int++)
		{
		if(m_vec_Leg[f_Int]->m_FULLON == true)
			{
			f_ResultCount++;
			}
		}

	return f_ResultCount;
}

float classElement::acCompare(shared_ptr<classElement> f_Element, float f_QualityRank, bool f_testVolumes)
{
	float f_Mark = 0;

	if(m_vec_Element.size() < f_Element->m_vec_Element.size())
		{
		f_Mark += 37.8f;
		}
	else
		{
		if(f_testVolumes)
			{
			for(int f_Count = 0; f_Count < m_vec_Element.size(); f_Count++)
				{
				std::shared_ptr<classElement> f_TestElement = m_vec_Element[f_Count];

				if(f_Count < f_Element->m_vec_Element.size())
					{
					std::shared_ptr<classElement> f_sizeTestElement = f_Element->m_vec_Element[f_Count];

					float f_Float = (f_TestElement->m_Volume - f_sizeTestElement->m_Volume) * f_QualityRank;

					if(f_Float >= 0)
						{
						f_Mark += f_Float;
						}
					else
						{
						f_Mark -= f_Float;
						}
					}
				}
			}
		}

	if(m_vec_Surface.size() < f_Element->acSize_Surface())
		{
		f_Mark += 14.8f;
		}

	if(m_vec_Leg.size() < f_Element->acSize_Leg())
		{
		f_Mark += 8.58f;
		}

	return f_Mark;
}

void classElementScript::acGen_fromElement(shared_ptr<classElement> f_Element, int f_ScriptLanguageScheme)
{
	g_SchemaRef[0].m_X = float(3.121113539F);
	g_SchemaRef[0].m_Y = float(3.773584266F);
	g_SchemaRef[0].m_Z = float(3.952468634F);

	std::string f_ref_CurrentPath = "classElementScript::acGen_fromElement";

	int f_WordCount = ag_takeMeasurementINTV0(f_Element, 1, 5, 1);

	std::vector<int> f_ProgOpen;

	for(int f_jet = 0; f_jet < f_WordCount; f_jet++)
		{
		int f_ComponentType = ag_takeMeasurementINTV0(f_Element, 1, 2);
		int f_BitCount = ag_takeMeasurementINTV0(f_Element, 1, 20, 2);

		ag_StatusLive(f_ref_CurrentPath, "f_Component");
		std::shared_ptr<classComponent> f_Component = std::make_shared_reflect<classComponent>(f_ComponentType);

		f_Component->m_Name = ag_NameStamp0(ag_takeMeasurement0(f_Element), f_ComponentType, f_BitCount);

		for(int f_XYZ = 0; f_XYZ < f_BitCount; f_XYZ++)
			{
			if(f_XYZ == 0)
				{
				switch(f_ComponentType)
					{
					case COMPONENT_TYPE_VARINSTA:
						{
						int f_VariableType = ag_takeMeasurementINTV0(f_Element, 1, 1);
						int f_VariableState = ag_takeMeasurementINTV0(f_Element, 1, 2, 3);

						switch(f_VariableType)
							{
							case VARIABLE_TYPE_INT:
								{
								if(f_VariableState == VARIABLE_STATE_NORMAL)
									{
									f_Component->m_vec_String.push_back("int ");
									}
								else
									{
									f_Component->m_vec_String.push_back("int* ");
									}
								} break;	
							}
						} break;

					case COMPONENT_TYPE_FUNCTIONCALL:
						{
						f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
						f_Component->m_vec_String.push_back("[");
						f_ProgOpen.push_back(3);
						} break;
					}

				if(f_BitCount == 1) //1
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
					}
				else
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
					f_Component->m_vec_String.push_back(" = ");
					}
				}
			else
				{
				if(f_BitCount == COMPONENT_CNT_BASE) //2
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
					}
				else
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));

					int f_AddType = ag_takeMeasurementINTV0(f_Element, 1, 3, 2);
							
					switch(f_AddType)
						{
						case COMPONENT_ELEMENT_TYPE_VARIABLE:
							{
							f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
							} break;

						case COMPONENT_ELEMENT_TYPE_FUNCTION:
							{
							f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
							f_Component->m_vec_String.push_back("[");
							f_ProgOpen.push_back(3);
							} break;

						case COMPONENT_ELEMENT_TYPE_PROG:
							{
							int f_ProgType = ag_takeMeasurementINTV0(f_Element, 1, 3);

							switch(f_ProgType)
								{
								case PROG_TYPE_OPERATOR:
									{
									int f_OperatorType = ag_takeMeasurementINTV0(f_Element, 1, 1);

									switch(f_OperatorType)
										{
										case OPERATOR_TYPE_PLUS:
											{
											f_Component->m_vec_String.push_back(" + ");
											} break;
										}
									} break;
								case PROG_TYPE_BKT:
									{
									f_ProgOpen.push_back(1);
									f_Component->m_vec_String.push_back("[");
									} break;
								case PROG_TYPE_PAREN:
									{
									f_ProgOpen.push_back(2);
									f_Component->m_vec_String.push_back(" {");
									} break;
								}
							} break;
						}
					}

				if(f_ProgOpen.size() >= 1)
					{
					if((f_ProgOpen[f_ProgOpen.size() - 1] == 1) && (f_Component->m_vec_String[f_Component->m_vec_String.size() - 1].compare("[") != 0))
						{
						f_Component->m_vec_String.push_back("]");
						f_ProgOpen.pop_back();
						}

					if((f_ProgOpen[f_ProgOpen.size() - 1] == 2) && (f_Component->m_vec_String[f_Component->m_vec_String.size() - 1].compare("{") != 0))
						{
						f_Component->m_vec_String.push_back("}");
						f_ProgOpen.pop_back();
						}
					}
				}
			}

		 ////////
		//Post process events
		f_Component->m_vec_String.push_back(";");

		f_Component->m_String.clear();
		for(int f_Comb = 0; f_Comb < f_Component->m_vec_String.size(); f_Comb++)
			{
			f_Component->m_String += f_Component->m_vec_String[f_Comb];
			}

		m_vec_Component.push_back(f_Component);
		}

	m_Data.clear();

	for(int f_RS = 0; f_RS < m_vec_Component.size(); f_RS++)
		{
		m_Data += m_vec_Component[f_RS]->m_String;
		}

	m_Hash.clear();

	g_hasha.init(); //reset hasher state
	g_hasha.process(m_Data.begin(), m_Data.end());
	g_hasha.finish();
	picosha2::get_hash_hex_string(g_hasha, m_Hash);
}

std::string ag_takeMeasurement0(shared_ptr<classElement> f_Vertex)
{
	//query modern take measurement

	return std::string("X");
}

//element level specify schema
int ag_takeMeasurementINTV0(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth) // scale resolution 1-3
{
	//query modern take measurement

	return 1;
}

std::string ag_NameStamp0(std::string f_Measurement, int f_Type, int f_BitCount)
{
	std::string f_Result = "";

	switch(f_Type)
		{
		case COMPONENT_TYPE_VARINSTA:
			{
			char f_Char[150];
			FillChar(f_Char, 150);
			sprintf(f_Char, "Variable-%i", f_BitCount);
			f_Result += f_Char;
			} break;
		case COMPONENT_TYPE_FUNCTIONCALL:
			{
			char f_Char[150];
			FillChar(f_Char, 150);
			sprintf(f_Char, "FunctionCall-%i", f_BitCount);
			f_Result += f_Char;
			} break;
		}

	return f_Result;
}

std::string ag_GenerateValue0(std::string f_Measurement)
{
	char* f_ValueStream = (char*)f_Measurement.c_str();

	int *f_Int = (int*)reinterpret_cast<int*>(f_ValueStream);

	char f_Char[150];
	FillChar(f_Char, 150);
	sprintf(f_Char, "%i", *(f_Int));

	std::string f_Result = f_Char;

	return f_Result;
}

};