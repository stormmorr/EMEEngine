/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "../Target.h"

class classPack
{
public:
	classPack() {};

	int m_XY;
	int f_indexInsta;
	int f_indexFunction;
	std::vector<std::string> build_LastNameClose;
	std::vector<int> build_LastTypeClose;
};

std::vector<std::shared_ptr<classPack>> g_vec_Input_Pack_takeMeasure;
std::vector<std::shared_ptr<classPack>> g_vec_Input_PackB_takeMeasure;

int g_idx_vec_Input_Pack_takeMeasure = 0;
int g_idx_vec_Input_PackB_takeMeasure = 0;

std::string namefunction1(std::shared_ptr<classTarget_JScript> f_Target, std::shared_ptr<classTestArg> f_testARG)
{
	std::string f_Name = "name"; //f_Target.acMakeUnisonVARG(f_unisonARG);

	return f_Name;
}

std::shared_ptr<classAchievement> testfunction1(std::shared_ptr<classTarget_JScript> f_Target, std::shared_ptr<classTestArg> f_testARG)
{
	std::shared_ptr<classAchievement> f_Achievement = std::make_shared<classAchievement>();

	//PULL ANALYTICAL FUNCTIONS EXAMPLES GIVEN
	//if(g_wwj_principalrunners_LastTypeClose[0] == )

	return f_Achievement;
}

std::shared_ptr<classAchievement> testfunction_affinity(std::shared_ptr<classTarget_JScript> f_Target, std::shared_ptr<classTestArg> f_testARG)
{
	std::shared_ptr<classAchievement> f_Achievement = std::make_shared<classAchievement>();

	//PULL ANALYTICAL FUNCTIONS EXAMPLES GIVEN
	if(g_idx_vec_Input_Pack_takeMeasure > 0)
		{
		for(int f_XY = 0; f_XY < g_idx_vec_Input_Pack_takeMeasure; f_XY++)
			{
			std::shared_ptr<classPack> f_Pack = g_vec_Input_Pack_takeMeasure[f_XY];

			if(f_Pack->f_indexFunction > (f_testARG->f_indexFunction - 300))
				{
				if(f_Pack->build_LastTypeClose[0] == g_ThisType)
					{
					bool f_Found = true;

					for(int f_Jet = 0; (f_Jet < g_ThisName.length()) && (f_Jet < f_Pack->build_LastNameClose[0].length()); f_Jet++)
						{
						if(g_ThisName.at(f_Jet) != f_Pack->build_LastNameClose[0].at(f_Jet))
							{
							f_Found = false;
							}
						}

					if(f_Found = true)
						{
						std::shared_ptr<classPack> f_vec_Pack = std::make_shared<classPack>();

						f_Pack->m_XY = f_XY;
						f_Pack->f_indexInsta = f_testARG->f_indexInsta;
						f_Pack->f_indexFunction = f_testARG->f_indexFunction;
						f_Pack->build_LastNameClose = f_testARG->build_LastNameClose;
						f_Pack->build_LastTypeClose = f_testARG->build_LastTypeClose;

						g_vec_Input_PackB_takeMeasure.push_back(f_Pack);
						g_idx_vec_Input_PackB_takeMeasure++;
						}
					}

				for(int f_Helly = 0; f_Helly < g_idx_vec_Input_PackB_takeMeasure; f_Helly++)
					{
					std::shared_ptr<classPack> f_PackB = g_vec_Input_PackB_takeMeasure[f_Helly];

					if(f_PackB->m_XY == f_Helly)
						{
						bool f_Void = false;
						for(int f_Test = 0; f_Test < f_PackB->build_LastTypeClose.size(); f_Test++)
							{
							if(f_PackB->build_LastTypeClose[f_Test] == -5)
								{
								f_Void = true;
								}

							if(f_Void == false)
								{
								if(f_PackB->build_LastTypeClose[f_Test] == INSTA_TYPE_CONDITIONAL)
									{
									f_Achievement->m_Mark->m_vec_Int[4] += 100;
									f_Achievement->m_Mark->m_vec_Int[5] += 50;
									f_Achievement->m_Success = true;
									}
								}
							}
						}
					}
				}
			}
		}

	bool f_Found = true;

	for(int f_Jet = 0; (f_Jet < g_ThisName.length()) && (f_Jet < g_vec_scrInputName[g_idx_vec_scrInputName - 1].length()); f_Jet++)
		{
		bool f_Found = true;
				
		if(g_ThisName.at(f_Jet) != g_vec_scrInputName[g_idx_vec_scrInputName - 1].at(f_Jet))
			{
			f_Found = false;
			}
		}
				
	if(f_Found = true && (f_testARG->f_indexInsta >= 1))
		{
		std::shared_ptr<classPack> f_Pack = std::make_shared<classPack>();

		f_Pack->m_XY = 1;
		f_Pack->f_indexInsta = f_testARG->f_indexInsta;
		f_Pack->f_indexFunction = f_testARG->f_indexFunction;
		f_Pack->build_LastNameClose = f_testARG->build_LastNameClose;
		f_Pack->build_LastTypeClose = f_testARG->build_LastTypeClose;

		g_vec_Input_Pack_takeMeasure.push_back(f_Pack);
		g_idx_vec_Input_Pack_takeMeasure++;
		}

	return f_Achievement;
}

void classTarget_JScript::acLoad_Biscuit(void)
{
	g_EnablePR = true;

	g_vec_scrInputName.push_back("firstinput");
	g_idx_vec_scrInputName++;

	g_vec_scrInputHTML.push_back("<input type=\"number\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"1\" min=\"1\" max=\"5\">");
	g_idx_vec_scrInputHTML++;

	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;

	g_vec_scrInputNameCuteFunc.push_back(&namefunction1);
	g_idx_vec_scrInputNameCuteFunc++;

	//g_vec_scrInputPlaceCuteFunc[g_idx_vec_scrInputPlaceCuteFunc] = INSTA_TYPE_VAR_CALL;
	//g_idx_vec_scrInputPlaceCuteFunc++;

	g_vec_scrInputTestCuteFunc.push_back(&testfunction1);
	g_idx_vec_scrInputTestCuteFunc++;


	g_vec_scrInputName.push_back("wwb_ecnbase_ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;

	g_vec_scrInputHTML.push_back("Ex");
	g_idx_vec_scrInputHTML++;

	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;

	g_vec_scrInputNameCuteFunc.push_back(&namefunction1);
	g_idx_vec_scrInputNameCuteFunc++;

	//g_vec_scrInputPlaceCuteFunc[g_idx_vec_scrInputPlaceCuteFunc] = INSTA_TYPE_VAR_CALL;
	//g_idx_vec_scrInputPlaceCuteFunc++;

	g_vec_scrInputTestCuteFunc.push_back(&testfunction_affinity);
	g_idx_vec_scrInputTestCuteFunc++;


	g_vec_scrInputName.push_back("wwb_ecnbase_ag_GenerateName");
	g_idx_vec_scrInputName++;

	g_vec_scrInputHTML.push_back("Ex");
	g_idx_vec_scrInputHTML++;

	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;

	g_vec_scrInputName.push_back("wwb_ecnbase_acMakeUnison");
	g_idx_vec_scrInputName++;

	g_vec_scrInputHTML.push_back("Ex");
	g_idx_vec_scrInputHTML++;

	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;

	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;

	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;

	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;

	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;

	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;

	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;

	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;

	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;

	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;

	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;

	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;

	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;

	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;

	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;

	std::shared_ptr<classBridge> f_ControlBridge1 = std::make_shared<classBridge>();

	f_ControlBridge1->ac_add_Path(g_idx_vec_scrControlName - 1, INSTA_TYPE_CONDITIONAL, LINE_TYPE_CONTROL);
	f_ControlBridge1->ac_add_Path(0, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_ControlBridge1->ac_add_Path(1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);

	g_vec_control_Bridge.push_back(f_ControlBridge1);
	g_idx_vec_control_Bridge++;

	g_vec_scrOutputName.push_back("f_Result");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;

	std::shared_ptr<classBridge> f_OutputBridge1 = std::make_shared<classBridge>();

	f_OutputBridge1->ac_add_Path(g_idx_vec_scrOutputName - 1, INSTA_TYPE_VAR_CALL, LINE_TYPE_OUTPUT);
	f_OutputBridge1->ac_add_Path(0, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_OutputBridge1->ac_add_Path(1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_OutputBridge1->ac_add_Path(-5, INSTA_TYPE_VAR_CALL, LINE_TYPE_NORMAL);

	g_vec_output_Bridge.push_back(f_OutputBridge1);
	g_idx_vec_output_Bridge++;

	g_vec_scrOutputName.push_back("window.getElementById(wwb_base_output1).innerHTML");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;

	g_vec_scrOutputName.push_back("window.getElementById(wwb_navbar_output1).innerHTML");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;

	g_vec_scrOutputName.push_back("window.getElementById(wwb_content1_output1).innerHTML");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;

	g_vec_scrOutputName.push_back("window.getElementById(wwb_deploy_output1).innerHTML");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;

	g_vec_scrOutputName.push_back("window.getElementById(wwb_mission_output1).innerHTML");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;

	g_vec_scrOutputName.push_back("window.getElementById(wwb_mission_output2).innerHTML");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;

	g_vec_scrOutputName.push_back("return ");
	g_idx_vec_scrOutputName++;

	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;

	std::shared_ptr<classBridge> f_OutputBridge2 = std::make_shared<classBridge>();

	f_OutputBridge2->ac_add_Path(g_idx_vec_scrOutputName - 1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_OUTPUT);
	f_OutputBridge2->ac_add_Path(-5, INSTA_TYPE_VAR_DEF, LINE_TYPE_INPUT);

	g_vec_output_Bridge.push_back(f_OutputBridge2);
	g_idx_vec_output_Bridge++;
}