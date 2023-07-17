/*

VoxelGrid.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "predator.h"

#include "qam.h"

using namespace Cube;

namespace Cube
{
std::vector<std::shared_ptr<predatorInstanceManager>> g_vec_PredatorManager;

predatorInstance::predatorInstance()
{
	std::string f_ref_CurrentPath = "predatorInstance::predatorInstance";

	ac_Clear();

#ifndef OSI_MEM_APP
	ac_Push(m_HDX, f_ref_CurrentPath + g_ref_Div + "m_HDX");
	ac_Push(m_IDX, f_ref_CurrentPath + g_ref_Div + "m_IDX");
	ac_Push(m_Panel_Set, f_ref_CurrentPath + g_ref_Div + "m_Panel_Set");
	ac_Push(m_ComID, f_ref_CurrentPath + g_ref_Div + "m_ComID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Clear", (void(ecom_base::*)(void))&predatorInstance::ac_Clear);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSave", (void(ecom_base::*)(void))&predatorInstance::acSave);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSaveAll", (void(ecom_base::*)(void))&predatorInstance::acSaveAll);
#endif
}

predatorInstance::predatorInstance(std::shared_ptr<Qcom> f_com)
{
	std::string f_ref_CurrentPath = "predatorInstance::predatorInstance";

	ac_Clear();

#ifndef OSI_MEM_APP
	ac_Push(m_HDX, f_ref_CurrentPath + g_ref_Div + "m_HDX");
	ac_Push(m_IDX, f_ref_CurrentPath + g_ref_Div + "m_IDX");
	ac_Push(m_Panel_Set, f_ref_CurrentPath + g_ref_Div + "m_Panel_Set");
	ac_Push(m_ComID, f_ref_CurrentPath + g_ref_Div + "m_ComID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Clear", (void(ecom_base::*)(void))&predatorInstance::ac_Clear);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSave", (void(ecom_base::*)(void))&predatorInstance::acSave);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSaveAll", (void(ecom_base::*)(void))&predatorInstance::acSaveAll);
#endif

	m_ComID = f_com->m_ID;

	if(f_com->m_vec_ESLFunction.size() > 0)
		{
		acInsertPanel(0, 0, f_com->m_vec_ESLFunction[0]);
		}

	if(f_com->m_Frame_ESLFunction != nullptr)
		{
		acInsertPanel(1, 0, f_com->m_Frame_ESLFunction);
		}

	for(int f_XY = 0; f_XY < f_com->m_vec_Input.size(); f_XY++)
		{
		acInsertPanel(2, f_XY, f_com->m_vec_Input[f_XY]->m_InputFunction);
		}

	for(int f_XY = 0; f_XY < f_com->m_vec_Output.size(); f_XY++)
		{
		acInsertPanel(3, f_XY, f_com->m_vec_Output[f_XY]->m_OutputFunction);
		}
}

void predatorInstance::ac_Clear(void)
{
	m_HDX = 0;
	m_IDX = 0;
	m_ComID = 0;
	m_Panel_Set = false;
	m_vec_onLoad.clear();
	m_vec_Frame.clear();
	m_vec_Input.clear();
	m_vec_Output.clear();
	m_vec_Undo.clear();
	m_vec_Redo.clear();
}

void predatorInstance::acInsertPanel(int f_HDX, int f_IDX, std::shared_ptr<Qcom_eslfunction> f_function)
{
	std::string f_ref_CurrentPath = "predatorInstance::acInsertPanel";
	ag_StatusLive(f_ref_CurrentPath, "f_Panel");
	std::shared_ptr<predatorPanelText> f_Panel = std::make_shared_reflect<predatorPanelText>(f_function);

	f_Panel->m_ComID = m_ComID;

	f_Panel->m_HCX = f_HDX;
	f_Panel->m_ICX = f_IDX;

	if(acPushPanel(f_HDX, f_IDX, f_Panel) == false)
		{ throw; }
}

bool ag_Changes(std::string f_A, std::string f_B)
{
	if(f_A.compare(f_B) == 0)
		{
		return false;
		}
	else
		{
		return true;
		}
}

void predatorPanelText::acSave(void) //comparatively
{
	std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(m_ComID);

	if(f_com != nullptr)
		{
		if((m_HCX >= 0) && (m_HCX < 4))
			{
			switch(m_HCX)
				{
				case 0: //onLoad
					{
					if(m_ICX < f_com->m_vec_ESLFunction.size())
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = f_com->m_vec_ESLFunction[0];

						std::vector<std::string> f_LineOrdered;
						std::string f_Carriage;
						f_Carriage.clear();

						for(int f_XY = 0; f_XY < m_Text.length(); f_XY++)
							{
							char f_A = m_Text.at(f_XY);
						
							if((f_A == '\n') || (f_A == '\r'))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							else
								{
								f_Carriage.push_back(f_A);
								}

							if(f_XY >= (m_Text.length() - 1))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							}

						std::vector<std::string> f_vec_CheckList;
						std::vector<int> f_vec_CheckID;
						std::vector<int> f_vec_CheckIDX;
						f_vec_CheckList.clear();
						f_vec_CheckID.clear();
						f_vec_CheckIDX.clear();

						f_Function->m_FunctionLine.clear();
		
						for(int f_countLine = 0; f_countLine < f_LineOrdered.size(); f_countLine++)
							{
							bool f_SkipLine = false;

							if(f_countLine < f_Function->m_vec_InitLineOrdered.size())
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered[f_countLine] = f_vec_CheckList[f_YS];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = f_vec_CheckID[f_YS];
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									std::string f_InitLineOrdered = f_Function->m_vec_InitLineOrdered[f_countLine];

									if(ag_Changes(f_LineOrdered[f_countLine], f_InitLineOrdered) == true)
										{	//Changed Line Detected, store for checks above and set safel id to re-insert newline
										if(f_Function->m_vec_InitLineOrderedID[f_countLine] > 0)
											{
											f_vec_CheckList.push_back(f_InitLineOrdered);
											f_vec_CheckID.push_back(f_Function->m_vec_InitLineOrderedID[f_countLine]);
											f_vec_CheckIDX.push_back(f_countLine);
											}

										f_Function->m_vec_InitLineOrdered[f_countLine] = f_LineOrdered[f_countLine];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = -1551;
										f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
										} //print Line
									}
								}
							else
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered.push_back(f_vec_CheckList[f_YS]);
										f_Function->m_vec_InitLineOrderedID.push_back(f_vec_CheckID[f_YS]);
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									f_Function->m_vec_InitLineOrdered.push_back(f_LineOrdered[f_countLine]);
									f_Function->m_vec_InitLineOrderedID.push_back(-1551);
									f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
									f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
									}//print Line
								}
							}

						 //////////////////////////////
						// Contractual Obligation
						f_com->ac_Save();
						}
					}break;

				case 1: //Frame
					{
					if(f_com->m_Frame_ESLFunction)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = f_com->m_Frame_ESLFunction;

						std::vector<std::string> f_LineOrdered;
						std::string f_Carriage;
						f_Carriage.clear();

						for(int f_XY = 0; f_XY < m_Text.length(); f_XY++)
							{
							char f_A = m_Text.at(f_XY);
						
							if((f_A == '\n') || (f_A == '\r'))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							else
								{
								f_Carriage.push_back(f_A);
								}

							if(f_XY >= (m_Text.length() - 1))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							}

						std::vector<std::string> f_vec_CheckList;
						std::vector<int> f_vec_CheckID;
						std::vector<int> f_vec_CheckIDX;
						f_vec_CheckList.clear();
						f_vec_CheckID.clear();
						f_vec_CheckIDX.clear();

						f_Function->m_FunctionLine.clear();
		
						for(int f_countLine = 0; f_countLine < f_LineOrdered.size(); f_countLine++)
							{
							bool f_SkipLine = false;

							if(f_countLine < f_Function->m_vec_InitLineOrdered.size())
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered[f_countLine] = f_vec_CheckList[f_YS];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = f_vec_CheckID[f_YS];
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									std::string f_InitLineOrdered = f_Function->m_vec_InitLineOrdered[f_countLine];

									if(ag_Changes(f_LineOrdered[f_countLine], f_InitLineOrdered) == true)
										{	//Changed Line Detected, store for checks above and set safel id to re-insert newline
										if(f_Function->m_vec_InitLineOrderedID[f_countLine] > 0)
											{
											f_vec_CheckList.push_back(f_InitLineOrdered);
											f_vec_CheckID.push_back(f_Function->m_vec_InitLineOrderedID[f_countLine]);
											f_vec_CheckIDX.push_back(f_countLine);
											}

										f_Function->m_vec_InitLineOrdered[f_countLine] = f_LineOrdered[f_countLine];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = -1551;
										f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
										} //print Line
									}
								}
							else
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered.push_back(f_vec_CheckList[f_YS]);
										f_Function->m_vec_InitLineOrderedID.push_back(f_vec_CheckID[f_YS]);
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									f_Function->m_vec_InitLineOrdered.push_back(f_LineOrdered[f_countLine]);
									f_Function->m_vec_InitLineOrderedID.push_back(-1551);
									f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
									f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
									}//print Line
								}
							}

						 //////////////////////////////
						// Contractual Obligation
						f_com->ac_Save();
						}
					}break;

				case 2: //Input
					{
					if(m_ICX < f_com->m_vec_Input.size())
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = f_com->m_vec_Input[m_ICX]->m_InputFunction;

						std::vector<std::string> f_LineOrdered;
						std::string f_Carriage;
						f_Carriage.clear();

						for(int f_XY = 0; f_XY < m_Text.length(); f_XY++)
							{
							char f_A = m_Text.at(f_XY);
						
							if((f_A == '\n') || (f_A == '\r'))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							else
								{
								f_Carriage.push_back(f_A);
								}

							if(f_XY >= (m_Text.length() - 1))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							}

						std::vector<std::string> f_vec_CheckList;
						std::vector<int> f_vec_CheckID;
						std::vector<int> f_vec_CheckIDX;
						f_vec_CheckList.clear();
						f_vec_CheckID.clear();
						f_vec_CheckIDX.clear();

						f_Function->m_FunctionLine.clear();
		
						for(int f_countLine = 0; f_countLine < f_LineOrdered.size(); f_countLine++)
							{
							bool f_SkipLine = false;

							if(f_countLine < f_Function->m_vec_InitLineOrdered.size())
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered[f_countLine] = f_vec_CheckList[f_YS];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = f_vec_CheckID[f_YS];
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									std::string f_InitLineOrdered = f_Function->m_vec_InitLineOrdered[f_countLine];

									if(ag_Changes(f_LineOrdered[f_countLine], f_InitLineOrdered) == true)
										{	//Changed Line Detected, store for checks above and set safel id to re-insert newline
										if(f_Function->m_vec_InitLineOrderedID[f_countLine] > 0)
											{
											f_vec_CheckList.push_back(f_InitLineOrdered);
											f_vec_CheckID.push_back(f_Function->m_vec_InitLineOrderedID[f_countLine]);
											f_vec_CheckIDX.push_back(f_countLine);
											}

										f_Function->m_vec_InitLineOrdered[f_countLine] = f_LineOrdered[f_countLine];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = -1551;
										f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
										} //print Line
									}
								}
							else
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered.push_back(f_vec_CheckList[f_YS]);
										f_Function->m_vec_InitLineOrderedID.push_back(f_vec_CheckID[f_YS]);
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									f_Function->m_vec_InitLineOrdered.push_back(f_LineOrdered[f_countLine]);
									f_Function->m_vec_InitLineOrderedID.push_back(-1551);
									f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
									f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
									}//print Line
								}
							}

						 //////////////////////////////
						// Contractual Obligation
						f_com->ac_Save();
						}
					}break;

				case 3: //Output
					{
					if(m_ICX < f_com->m_vec_Output.size())
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = f_com->m_vec_Output[m_ICX]->m_OutputFunction;

						std::vector<std::string> f_LineOrdered;
						std::string f_Carriage;
						f_Carriage.clear();

						for(int f_XY = 0; f_XY < m_Text.length(); f_XY++)
							{
							char f_A = m_Text.at(f_XY);
						
							if((f_A == '\n') || (f_A == '\r'))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							else
								{
								f_Carriage.push_back(f_A);
								}

							if(f_XY >= (m_Text.length() - 1))
								{
								f_LineOrdered.push_back(f_Carriage);
								f_Carriage.clear();
								}
							}

						std::vector<std::string> f_vec_CheckList;
						std::vector<int> f_vec_CheckID;
						std::vector<int> f_vec_CheckIDX;
						f_vec_CheckList.clear();
						f_vec_CheckID.clear();
						f_vec_CheckIDX.clear();

						f_Function->m_FunctionLine.clear();
		
						for(int f_countLine = 0; f_countLine < f_LineOrdered.size(); f_countLine++)
							{
							bool f_SkipLine = false;

							if(f_countLine < f_Function->m_vec_InitLineOrdered.size())
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered[f_countLine] = f_vec_CheckList[f_YS];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = f_vec_CheckID[f_YS];
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									std::string f_InitLineOrdered = f_Function->m_vec_InitLineOrdered[f_countLine];

									if(ag_Changes(f_LineOrdered[f_countLine], f_InitLineOrdered) == true)
										{	//Changed Line Detected, store for checks above and set safel id to re-insert newline
										if(f_Function->m_vec_InitLineOrderedID[f_countLine] > 0)
											{
											f_vec_CheckList.push_back(f_InitLineOrdered);
											f_vec_CheckID.push_back(f_Function->m_vec_InitLineOrderedID[f_countLine]);
											f_vec_CheckIDX.push_back(f_countLine);
											}

										f_Function->m_vec_InitLineOrdered[f_countLine] = f_LineOrdered[f_countLine];
										f_Function->m_vec_InitLineOrderedID[f_countLine] = -1551;
										f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
										} //print Line
									}
								}
							else
								{
								for(int f_YS = 0; f_YS < f_vec_CheckList.size(); f_YS++)
									{
									if(ag_Changes(f_vec_CheckList[f_YS], f_LineOrdered[f_countLine]) == false)
										{
										f_Function->m_vec_InitLineOrdered.push_back(f_vec_CheckList[f_YS]);
										f_Function->m_vec_InitLineOrderedID.push_back(f_vec_CheckID[f_YS]);
										f_Function->m_FunctionLine += f_vec_CheckList[f_YS];
										f_Function->m_vec_ResultIDXupdateLineNumber.push_back(f_countLine);

										for(int f_SH = f_YS; f_SH < (f_vec_CheckList.size() - 1); f_SH++)
											{
											f_vec_CheckList[f_SH] = f_vec_CheckList[f_SH + 1];
											f_vec_CheckID[f_SH] = f_vec_CheckID[f_SH + 1];
											f_vec_CheckIDX[f_SH] = f_vec_CheckIDX[f_SH + 1];
											}

										f_vec_CheckList.pop_back();
										f_vec_CheckID.pop_back();
										f_vec_CheckIDX.pop_back();

										f_YS = f_vec_CheckList.size();
										f_SkipLine = true;
										}
									}

								if(f_SkipLine == false)
									{
									f_Function->m_vec_InitLineOrdered.push_back(f_LineOrdered[f_countLine]);
									f_Function->m_vec_InitLineOrderedID.push_back(-1551);
									f_Function->m_FunctionLine += f_LineOrdered[f_countLine];
									f_Function->m_vec_ResultIDXupdateLineNumber.push_back(-1551);
									}//print Line
								}
							}

						 //////////////////////////////
						// Contractual Obligation
						f_com->ac_Save();
						}
					}break;
				}
			}
		}
}

winrt::hstring predatorInstance::acOpen(int f_HDX, int f_IDX)
{
	if(m_Panel_Set == true)
		{
		m_Panel->acSave();
		}

	std::shared_ptr<predatorPanelText> f_Panel = acPullPanel(f_HDX, f_IDX);

	m_Panel = f_Panel;
	m_Panel_Set = true;

	return StrUsingStr(f_Panel->m_Text);
}

std::shared_ptr<predatorPanelText> predatorInstance::acPullPanel(int f_HDX, int f_IDX)
{
	std::string f_ref_CurrentPath = "predatorInstance::acPullPanel";

	if((f_HDX >= 0) && (f_HDX < 4))
		{
		switch(f_HDX)
			{
			case 0: //onLoad
				{
				if(f_IDX < m_vec_onLoad.size())
					{
					return m_vec_onLoad[f_IDX];
					}
				}break;

			case 1: //Frame
				{
				if(f_IDX < m_vec_Frame.size())
					{
					return m_vec_Frame[f_IDX];
					}
				}break;

			case 2: //Input
				{
				if(f_IDX < m_vec_Input.size())
					{
					return m_vec_Input[f_IDX];
					}
				}break;

			case 3: //Output
				{
				if(f_IDX < m_vec_Output.size())
					{
					return m_vec_Output[f_IDX];
					}
				}break;
			}
		}

	ag_StatusLive(f_ref_CurrentPath, "return(predatorPanelText)");

	return std::make_shared<predatorPanelText>();
}

bool predatorInstance::acPushPanel(int f_HDX, int f_IDX, std::shared_ptr<predatorPanelText> f_PushPanel)
{
	f_PushPanel->m_HCX = f_HDX;
	f_PushPanel->m_ICX = f_IDX;

	if((f_HDX >= 0) && (f_HDX < 4))
		{
		switch(f_HDX)
			{
			case 0: //onLoad
				{
				m_vec_onLoad.push_back(f_PushPanel);
				return true;
				}break;

			case 1: //onLoad
				{
				m_vec_Frame.push_back(f_PushPanel);
				return true;
				}break;

			case 2: //onLoad
				{
				m_vec_Input.push_back(f_PushPanel);
				return true;
				}break;

			case 3: //onLoad
				{
				m_vec_Output.push_back(f_PushPanel);
				return true;
				}break;
			}
		}

	return false;
}

void predatorInstance::acSave(void)
{
	m_Panel->acSave();
}

void predatorInstance::acSaveAll(void)
{
	for(int f_XY = 0; f_XY < m_vec_onLoad.size(); f_XY++)
		{
		m_vec_onLoad[f_XY]->acSave();
		}

	for(int f_XY = 0; f_XY < m_vec_Frame.size(); f_XY++)
		{
		m_vec_Frame[f_XY]->acSave();
		}

	for(int f_XY = 0; f_XY < m_vec_Input.size(); f_XY++)
		{
		m_vec_Input[f_XY]->acSave();
		}

	for(int f_XY = 0; f_XY < m_vec_Output.size(); f_XY++)
		{
		m_vec_Output[f_XY]->acSave();
		}
}

void predatorInstanceManager::acSave(void)
{
	m_PredatorIns->acSave();
}

void predatorInstanceManager::acSaveAll(void)
{
	for(int f_XY = 0; f_XY < m_vec_PredatorIns.size(); f_XY++)
		{
		m_vec_PredatorIns[f_XY]->acSaveAll();
		}
}

std::shared_ptr<predatorInstance> predatorInstanceManager::acSearchIns_byComID(std::shared_ptr<Qcom> f_com)
{
	std::string f_ref_CurrentPath = "predatorInstanceManager::acSearchIns_byComID";

	for(int f_XY = 0; f_XY < m_vec_PredatorIns.size(); f_XY++)
		{
		std::shared_ptr<predatorInstance> f_Ins = m_vec_PredatorIns[f_XY];

		if(f_Ins->m_ComID == f_com->m_ID)
			{
			m_PredatorIns = f_Ins;

			return f_Ins;
			}
		}

	ag_StatusLive(f_ref_CurrentPath, "f_Ins");
	std::shared_ptr<predatorInstance> f_Ins = std::make_shared_reflect<predatorInstance>(f_com);

	m_vec_PredatorIns.push_back(f_Ins);

	m_PredatorIns = f_Ins;

	return f_Ins;
}

};