/*

Decisions - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "SecondaryAppWindowPageDX.h"

#include "Include/Cube.h"

#include "Code/Work/Contract.h"
#include "Code/Work/Schedular.h"

#include "Code/Cube/qcom.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

extern winrt::Windows::UI::Xaml::Controls::SwapChainPanel g_swapChainPanel;

using namespace Cube;

namespace Cube
{
	//ComID
#define ECOIN_CID_INPUTSENSE 35
#define ECOIN_SHARESHOP_OWNCOM "own"
#define ECOIN_SHARESHOP_GROUP_KITS "kit"

std::vector<std::shared_ptr<DecisionManager>> g_vec_DecisionsManager;

	///////////////////////////////////////////
   ///////////////////////////////////////////
  // LoadAll (HARD-CODED) Known Decisions
 //	acLoad...
//
void DecisionManager::acLoad_ApplicationSpecificLegacy(void)
{
	std::string f_ref_CurrentPath = "DecisionManager::acLoad_ApplicationSpecificLegacy";

	 //////////////////////////////////////////////////////////
    // Generic Answers - Nothing Entered - Nothing Selected //
	ag_StatusLive(f_ref_CurrentPath, "f_ClickContractAnswer");
	std::shared_ptr<BiDecisionA> f_ClickContractAnswer = std::make_shared_reflect<BiDecisionA>("Click to Change Contract Type", acLoadA_ContractToggle() + ":");
	ag_StatusLive(f_ref_CurrentPath, "f_InsertBeginAnswer");
	std::shared_ptr<BiDecisionA> f_InsertBeginAnswer = std::make_shared_reflect<BiDecisionA>("Click to Insert Input Sense", acLoadA_InsertCom(ECOIN_CID_INPUTSENSE) + ":");

	 /////////////////////////////////////////////////////////////////////////
    // Shop Own Buy Full Grid Answers - Nothing Entered - Nothing Selected //
	ag_StatusLive(f_ref_CurrentPath, "f_LoadOwnAnswer");
	std::shared_ptr<BiDecisionA> f_LoadOwnAnswer = std::make_shared_reflect<BiDecisionA>("Click to Load Own E-Grid", acLoadA_ShareShop(ECOIN_SHARESHOP_OWNCOM) + ":");
	ag_StatusLive(f_ref_CurrentPath, "f_BuySearchShopWholeKitsAnswer");
	std::shared_ptr<BiDecisionA> f_BuySearchShopWholeKitsAnswer = std::make_shared_reflect<BiDecisionA>("Click to Search Whole Buy Kits", acLoadA_ShareShop(ECOIN_SHARESHOP_GROUP_KITS) + ":");

	 ////////////////////////////////////////////////////////////
	// Generic Decisions - Nothing Entered - Nothing Selected //
	ag_StatusLive(f_ref_CurrentPath, "f_EmptyDecision");
	std::shared_ptr<BiDecisionQ> f_EmptyDecision = std::make_shared_reflect<BiDecisionQ>();

	f_EmptyDecision->m_ecomSelectedCount = -100;
	f_EmptyDecision->m_inputSelectedCount = -100;
	f_EmptyDecision->m_outputSelectedCount = -100;
	f_EmptyDecision->m_wireSelectedCount = -100;

	f_EmptyDecision->acAdd_Answer(f_ClickContractAnswer);
	f_EmptyDecision->acAdd_Answer(f_InsertBeginAnswer);
	f_EmptyDecision->acAdd_Answer(f_LoadOwnAnswer);
	f_EmptyDecision->acAdd_Answer(f_BuySearchShopWholeKitsAnswer);

	m_vec_DecisionQ.push_back(f_EmptyDecision);

	 //////////////////////////////////////////
    // Generic Decisions - Nothing Selected //
	ag_StatusLive(f_ref_CurrentPath, "f_Decision1");
	std::shared_ptr<BiDecisionQ> f_Decision1 = std::make_shared_reflect<BiDecisionQ>();

	f_Decision1->m_ecomSelectedCount = 0;
	f_Decision1->m_inputSelectedCount = 0;
	f_Decision1->m_outputSelectedCount = 0;
	f_Decision1->m_wireSelectedCount = 0;

	f_Decision1->acAdd_Answer(f_ClickContractAnswer);
	f_Decision1->acAdd_Answer(f_InsertBeginAnswer);
	f_Decision1->acAdd_Answer(f_LoadOwnAnswer);
	f_Decision1->acAdd_Answer(f_BuySearchShopWholeKitsAnswer);

	m_vec_DecisionQ.push_back(f_Decision1);

	 ///////////////////////////////////////////
    // Generic Decisions - One ECOM Selected //
	ag_StatusLive(f_ref_CurrentPath, "f_DecisionOne");
	std::shared_ptr<BiDecisionQ> f_DecisionOne = std::make_shared_reflect<BiDecisionQ>();

	f_DecisionOne->m_ecomSelectedCount = 1;
	f_DecisionOne->m_inputSelectedCount = 0;
	f_DecisionOne->m_outputSelectedCount = 0;
	f_DecisionOne->m_wireSelectedCount = 0;

	f_DecisionOne->acAdd_Answer(f_ClickContractAnswer);
	f_DecisionOne->acAdd_Answer(f_InsertBeginAnswer);

	m_vec_DecisionQ.push_back(f_DecisionOne);

	std::shared_ptr<BiDecisionA> f_CopyAnswer = nullptr;
	std::shared_ptr<BiDecisionA> f_CutAnswer = nullptr;
	std::shared_ptr<BiDecisionA> f_PasteAnswer = nullptr;
	std::shared_ptr<BiDecisionA> f_DeleteAnswer = nullptr;

	 //////////////////////////////////////
    // EDIT Answers - One ECOM Selected //
	if(m_Wheel->m_vec_Selection_com.size() > 0)
		{
		std::string f_AnswerString = "";

		for(int f_Jet = 0; f_Jet < m_Wheel->m_vec_Selection_com.size(); f_Jet++)
			{
			f_AnswerString += acLoadA_CopyCom(m_Wheel->m_vec_Selection_com[f_Jet]);
			}

		ag_StatusLive(f_ref_CurrentPath, "f_CopyAnswer");
		f_CopyAnswer = std::make_shared_reflect<BiDecisionA>("Click to Copy Items", f_AnswerString + ":");

		f_AnswerString.clear();

		for(int f_Jet = 0; f_Jet < m_Wheel->m_vec_Selection_com.size(); f_Jet++)
			{
			f_AnswerString += acLoadA_PasteCom(m_Wheel->m_vec_Selection_com[f_Jet]);
			}

		ag_StatusLive(f_ref_CurrentPath, "f_PasteAnswer");
		f_PasteAnswer = std::make_shared_reflect<BiDecisionA>("Click to Paste Items", f_AnswerString + ":");

		f_AnswerString.clear();

		for(int f_Jet = 0; f_Jet < m_Wheel->m_vec_Selection_com.size(); f_Jet++)
			{
			f_AnswerString += acLoadA_DeleteCom(m_Wheel->m_vec_Selection_com[f_Jet]);
			}

		ag_StatusLive(f_ref_CurrentPath, "f_DeleteAnswer");
		f_DeleteAnswer = std::make_shared_reflect<BiDecisionA>("Click to Delete Items", f_AnswerString + ":");

		f_AnswerString.clear();

		for(int f_Jet = 0; f_Jet < m_Wheel->m_vec_Selection_com.size(); f_Jet++)
			{
			f_AnswerString += acLoadA_CutCom(m_Wheel->m_vec_Selection_com[0]);
			}

		ag_StatusLive(f_ref_CurrentPath, "f_CutAnswer");
		f_CutAnswer = std::make_shared_reflect<BiDecisionA>("Click to Cut Items", f_AnswerString + ":");
		}

	 //////////////////////////////////////////////
    // Generic Decisions - One >= ECOM Selected //
	ag_StatusLive(f_ref_CurrentPath, "f_DecisionEdit");
	std::shared_ptr<BiDecisionQ> f_DecisionEdit = std::make_shared_reflect<BiDecisionQ>();

	f_DecisionEdit->m_ecomSelectedCount = -101;
	f_DecisionEdit->m_inputSelectedCount = -101;
	f_DecisionEdit->m_outputSelectedCount = -101;
	f_DecisionEdit->m_wireSelectedCount = -101;

	f_DecisionEdit->acAdd_Answer(f_DeleteAnswer);
	f_DecisionEdit->acAdd_Answer(f_CutAnswer);
	f_DecisionEdit->acAdd_Answer(f_CopyAnswer);
	f_DecisionEdit->acAdd_Answer(f_PasteAnswer);

	m_vec_DecisionQ.push_back(f_DecisionEdit);

	 //////////////////////////////////////
    // Wire Answers - Two ECOM Selected //
	if((m_Wheel->m_vec_Selection_com.size() >= 2) && (m_Wheel->m_vec_Selection_output.size() >= 1) && (m_Wheel->m_vec_Selection_input.size() >= 1))
		{
		ag_StatusLive(f_ref_CurrentPath, "f_StandardWireAnswer");
		std::shared_ptr<BiDecisionA> f_StandardWireAnswer = std::make_shared_reflect<BiDecisionA>("Click to Standard Wire Two Components", acLoadA_WireStandard(m_Wheel->m_vec_Selection_com[0], m_Wheel->m_vec_Selection_com[1], m_Wheel->m_vec_Selection_output[0], m_Wheel->m_vec_Selection_input[0]) + ":");

		 ////////////////////////////////////////
		// Wire Decisions - Two ECOM Selected //
		ag_StatusLive(f_ref_CurrentPath, "f_DecisionStandardWire");
		std::shared_ptr<BiDecisionQ> f_DecisionStandardWire = std::make_shared_reflect<BiDecisionQ>();

		f_DecisionStandardWire->m_ecomSelectedCount = 2;
		f_DecisionStandardWire->m_inputSelectedCount = 1;
		f_DecisionStandardWire->m_outputSelectedCount = 1;
		f_DecisionStandardWire->m_wireSelectedCount = 0;

		f_DecisionStandardWire->acAdd_Answer(f_StandardWireAnswer);

		m_vec_DecisionQ.push_back(f_DecisionStandardWire);
		}
}

std::string DecisionManager::acLoadA_InsertCom(int f_CID)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "makcom_%i-", f_CID);

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_ContractToggle(void)
{
	char* f_Char = ag_ClearChar(256);

	sprintf(f_Char, "contra_");

	return std::string(f_Char);
}

std::string DecisionManager::acLoadA_ShareShop(std::string f_ModeString)
{
	char* f_CID_Char = ag_ClearChar(5000);

	sprintf(f_CID_Char, "shrshp_%s_", f_ModeString.c_str());

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_DeleteCom(std::shared_ptr<Qcom> f_com)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "delcom_%i-", f_com->m_ID);

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_CutCom(std::shared_ptr<Qcom> f_com)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "cutcom_%i-", f_com->m_ID);

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_CopyCom(std::shared_ptr<Qcom> f_com)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "copcom_%i-", f_com->m_ID);

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_PasteCom(std::shared_ptr<Qcom> f_com)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "pascom_%i-", f_com->m_ID);

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_WireStandard(std::shared_ptr<Qcom> f_A, std::shared_ptr<Qcom> f_B, std::shared_ptr<QcomOutput> f_A_output, std::shared_ptr<QcomInput> f_B_input)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "wircom_%i-output_%i-wircom_%i-input_%i-", f_A->m_ID, f_A_output->m_ID, f_B->m_ID, f_B_input->m_ID);

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_QamByID(int f_QamID, int f_Trial)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "updqam_%i-", f_QamID);

	return std::string(f_CID_Char);
}

std::string DecisionManager::acLoadA_QamStabilise(void)
{
	char* f_CID_Char = ag_ClearChar(256);

	sprintf(f_CID_Char, "allqam_%i-", g_QamID);

	return std::string(f_CID_Char);
}

bool BiDecisionA::acApply(void)
{
	std::string f_ref_CurrentPath = "BiDecisionA::acApply";

	if((m_Trial_Length > 0) && (m_Trial_QamID > 0))
		{
		time_t f_Time;
		time(&f_Time);
		m_Trial_Length += f_Time;
		}

	int f_Length = m_ObjectNameOverride.length();
	int f_Shuttle = 0;

	bool f_ScanFull = true;
	while(f_ScanFull == true)
		{
		std::vector<std::string> f_funcom;
		std::vector<std::string> f_funcomID;
		std::string f_Carriage = "";

		bool f_Scan = true;
		while(f_Scan == true)
			{
			char f_c = m_ObjectNameOverride.at(f_Shuttle);

			if(f_c == ':')
				{
				f_Scan = false;
				f_ScanFull = false;
				}
			else if(f_c == '_')
				{
				f_funcom.push_back(f_Carriage);
				f_Scan = false;
				}
			else if(f_c == '-')
				{
				f_funcomID.push_back(f_Carriage);
				f_Scan = false;
				}
			else
				{
				f_Carriage.push_back(f_c);
				}
			}

		//each unit of protocol scope uppermost
		if(f_funcom[0].compare("makcom") == 0)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_com");
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>(atoi(f_funcomID[0].c_str()));

			g_QcomManager->m_vec_Qcom.push_back(f_com);
			g_QcomManager->m_Qcom->m_vec_Qcom.push_back(f_com);
			}
		else if(f_funcom[0].compare("allqam") == 0)
			{
			bool f_Update = false;

			for(int f_Jet = 0; f_Jet < g_QcomManager->m_vec_Qcom.size(); f_Jet++)
				{
				std::shared_ptr<Qcom> f_com = g_QcomManager->m_vec_Qcom[f_Jet];

				int f_QamID = atoi(f_funcomID[0].c_str());

				if (f_com->m_QamID != f_QamID)
					{
					f_com->m_QamID = f_QamID;

					f_com->m_Save = true;

					f_Update = true;
					}
				}

			if(f_Update == true)
				{
				g_QcomManager->m_Qcom->ac_Save();
				}
			}
		else if(f_funcom[0].compare("updqam") == 0)
			{
			bool f_Update = false;

			for(int f_Jet = 0; f_Jet < g_QcomManager->m_vec_Qcom.size(); f_Jet++)
				{
				std::shared_ptr<Qcom> f_com = g_QcomManager->m_vec_Qcom[f_Jet];

				int f_QamID = atoi(f_funcomID[0].c_str());

				if (f_com->m_QamID == f_QamID)
					{
					f_com->m_QamID = g_QamID;

					f_com->m_Save = true;

					f_Update = true;
					}
				}

			if(f_Update == true)
				{
				g_QcomManager->m_Qcom->ac_Save();
				}
			}
		else if(f_funcom[0].compare("wircom") == 0)
			{
			int f_ComIDA = atoi(f_funcomID[0].c_str());
			int f_ComIndexA = atoi(f_funcomID[1].c_str());
			int f_ComIDB = atoi(f_funcomID[2].c_str());
			int f_ComIndexB = atoi(f_funcomID[3].c_str());

			if((f_ComIDA <= 0) || (f_funcom[1].compare("output") != 0) ||
				(f_ComIDB <= 0) || (f_funcom[1].compare("input") != 0))
				{
				return false;
				}

#if 0
			std::shared_ptr<Qcom> f_com_A = g_QcomManager->ac_Find_Com_ByID(atoi(f_funcomID[0].c_str()));
			std::shared_ptr<Qcom> f_com_B = g_QcomManager->ac_Find_Com_ByID(atoi(f_funcomID[2].c_str()));
#endif

			std::shared_ptr<QcomOutput> f_com_A_output = g_QcomManager->ac_Find_ComOutput_ByID(atoi(f_funcomID[1].c_str()));
			std::shared_ptr<QcomInput> f_com_B_input = g_QcomManager->ac_Find_ComInput_ByID(atoi(f_funcomID[3].c_str()));

			g_QcomManager->m_Wiring_Output.push_back(f_com_A_output);
			g_QcomManager->m_Wiring_Input.push_back(f_com_B_input);
			}
		else if(f_funcom[0].compare("pascom") == 0)
			{
			for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_Paste_Buffer.size(); f_XY++)
				{
				g_QcomManager->m_vec_Qcom.push_back(g_vec_DecisionsManager[0]->m_Paste_Buffer[f_XY]);
				g_QcomManager->m_Qcom->m_vec_Qcom.push_back(g_vec_DecisionsManager[0]->m_Paste_Buffer[f_XY]);
				}
			}
		else if(f_funcom[0].compare("copcom") == 0)
			{
			g_vec_DecisionsManager[0]->m_Paste_Buffer.clear();

			for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size(); f_XY++)
				{
				g_vec_DecisionsManager[0]->m_Paste_Buffer.push_back(g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com[f_XY]);
				}
			}
		else if(f_funcom[0].compare("cutcom") == 0)
			{
			g_vec_DecisionsManager[0]->m_Paste_Buffer.clear();

			for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_com = g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com[f_XY];
				
				g_vec_DecisionsManager[0]->m_Paste_Buffer.push_back(f_com);
				}
			}
		else if(f_funcom[0].compare("delcom") == 0)
			{
			std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(atoi(f_funcomID[0].c_str()));
			}
		else if(f_funcom[0].compare("contra") == 0)
			{
			//
			}
		else if(f_funcom[0].compare("shrshp") == 0)
			{
			g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
				{
				std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

				winrt::Windows::UI::Xaml::Controls::StackPanel f_shopStack = g_swapChainPanel.FindName(StrUsingStr("shopStack")).as<winrt::Windows::UI::Xaml::Controls::StackPanel>();
				f_shopStack.Visibility(::winrt::Windows::UI::Xaml::Visibility::Visible);

				winrt::Windows::UI::Xaml::Controls::TextBox f_shopName = g_swapChainPanel.FindName(StrUsingStr("shopsearchnametextBox")).as<winrt::Windows::UI::Xaml::Controls::TextBox>();
				f_shopName.Text(StrUsingStr(f_funcom[1]));

				winrt::Windows::UI::Xaml::Controls::TextBox f_shopDesc = g_swapChainPanel.FindName(StrUsingStr("shopsearchdescriptiontextBox")).as<winrt::Windows::UI::Xaml::Controls::TextBox>();
				f_shopName.Text(StrUsingStr(""));

				winrt::Windows::UI::Xaml::Controls::TextBox f_shopTag = g_swapChainPanel.FindName(StrUsingStr("shopsearchprefixtextBox")).as<winrt::Windows::UI::Xaml::Controls::TextBox>();
				f_shopName.Text(StrUsingStr(""));

				winrt::Windows::UI::Xaml::Controls::Button f_shopSearchButton = g_swapChainPanel.FindName(StrUsingStr("shopsearchbutton")).as<winrt::Windows::UI::Xaml::Controls::Button>();
		
				f_shopSearchButton.Command().Execute(f_shopSearchButton.CommandParameter());
				});
			}
		}

	return true;
}

bool BiDecisionA::acUnApply(void)
{
	std::string f_ref_CurrentPath = "BiDecisionA::acUnApply";

	if((m_Trial_Length > 0) && (m_Trial_QamID > 0))
		{
		time_t f_Time;
		time(&f_Time);
		m_Trial_Length += f_Time;
		}

	int f_Length = m_ObjectNameOverride.length();
	int f_Shuttle = 0;

	bool f_ScanFull = true;
	while(f_ScanFull == true)
		{
		std::vector<std::string> f_funcom;
		std::vector<std::string> f_funcomID;
		std::string f_Carriage = "";

		bool f_Scan = true;
		while(f_Scan == true)
			{
			char f_c = m_ObjectNameOverride.at(f_Shuttle);

			if(f_c == ':')
				{
				f_Scan = false;
				f_ScanFull = false;
				}
			else if(f_c == '_')
				{
				f_funcom.push_back(f_Carriage);
				f_Scan = false;
				}
			else if(f_c == '-')
				{
				f_funcomID.push_back(f_Carriage);
				f_Scan = false;
				}
			else
				{
				f_Carriage.push_back(f_c);
				}
			}

		//each unit of protocol scope uppermost
		if(f_funcom[0].compare("makcom") == 0)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_com");
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>(atoi(f_funcomID[0].c_str()));

			g_QcomManager->m_vec_Qcom.push_back(f_com);
			g_QcomManager->m_Qcom->m_vec_Qcom.push_back(f_com);
			}
		else if(f_funcom[0].compare("allqam") == 0)
			{
			bool f_Update = false;

			for(int f_Jet = 0; f_Jet < g_QcomManager->m_vec_Qcom.size(); f_Jet++)
				{
				std::shared_ptr<Qcom> f_com = g_QcomManager->m_vec_Qcom[f_Jet];

				int f_QamID = atoi(f_funcomID[0].c_str());

				if (f_com->m_QamID != f_QamID)
					{
					f_com->m_QamID = f_QamID;

					f_com->m_Save = true;

					f_Update = true;
					}
				}

			if(f_Update == true)
				{
				g_QcomManager->m_Qcom->ac_Save();
				}
			}
		else if(f_funcom[0].compare("updqam") == 0)
			{
			bool f_Update = false;

			for(int f_Jet = 0; f_Jet < g_QcomManager->m_vec_Qcom.size(); f_Jet++)
				{
				std::shared_ptr<Qcom> f_com = g_QcomManager->m_vec_Qcom[f_Jet];

				int f_QamID = atoi(f_funcomID[0].c_str());

				if (f_com->m_QamID == f_QamID)
					{
					f_com->m_QamID = g_QamID;

					f_com->m_Save = true;

					f_Update = true;
					}
				}

			if(f_Update == true)
				{
				g_QcomManager->m_Qcom->ac_Save();
				}
			}
		else if(f_funcom[0].compare("wircom") == 0)
			{
			int f_ComIDA = atoi(f_funcomID[0].c_str());
			int f_ComIndexA = atoi(f_funcomID[1].c_str());
			int f_ComIDB = atoi(f_funcomID[2].c_str());
			int f_ComIndexB = atoi(f_funcomID[3].c_str());

			if((f_ComIDA <= 0) || (f_funcom[1].compare("output") != 0) ||
				(f_ComIDB <= 0) || (f_funcom[1].compare("input") != 0))
				{
				return false;
				}

#if 0
			std::shared_ptr<Qcom> f_com_A = g_QcomManager->ac_Find_Com_ByID(atoi(f_funcomID[0].c_str()));
			std::shared_ptr<Qcom> f_com_B = g_QcomManager->ac_Find_Com_ByID(atoi(f_funcomID[2].c_str()));
#endif

			std::shared_ptr<QcomOutput> f_com_A_output = g_QcomManager->ac_Find_ComOutput_ByID(atoi(f_funcomID[1].c_str()));
			std::shared_ptr<QcomInput> f_com_B_input = g_QcomManager->ac_Find_ComInput_ByID(atoi(f_funcomID[3].c_str()));

			g_QcomManager->m_Wiring_Output.push_back(f_com_A_output);
			g_QcomManager->m_Wiring_Input.push_back(f_com_B_input);
			}
		else if(f_funcom[0].compare("pascom") == 0)
			{
			for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_Paste_Buffer.size(); f_XY++)
				{
				g_QcomManager->m_vec_Qcom.push_back(g_vec_DecisionsManager[0]->m_Paste_Buffer[f_XY]);
				g_QcomManager->m_Qcom->m_vec_Qcom.push_back(g_vec_DecisionsManager[0]->m_Paste_Buffer[f_XY]);
				}
			}
		else if(f_funcom[0].compare("copcom") == 0)
			{
			g_vec_DecisionsManager[0]->m_Paste_Buffer.clear();

			for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size(); f_XY++)
				{
				g_vec_DecisionsManager[0]->m_Paste_Buffer.push_back(g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com[f_XY]);
				}
			}
		else if(f_funcom[0].compare("cutcom") == 0)
			{
			g_vec_DecisionsManager[0]->m_Paste_Buffer.clear();

			for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_com = g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com[f_XY];
				
				g_vec_DecisionsManager[0]->m_Paste_Buffer.push_back(f_com);
				}
			}
		else if(f_funcom[0].compare("delcom") == 0)
			{
			std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(atoi(f_funcomID[0].c_str()));
			}
		else if(f_funcom[0].compare("contra") == 0)
			{
			//
			}
		else if(f_funcom[0].compare("shrshp") == 0)
			{
			g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
				{
				std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

				winrt::Windows::UI::Xaml::Controls::StackPanel f_shopStack = g_swapChainPanel.FindName(StrUsingStr("shopStack")).as<winrt::Windows::UI::Xaml::Controls::StackPanel>();
				f_shopStack.Visibility(::winrt::Windows::UI::Xaml::Visibility::Visible);

				winrt::Windows::UI::Xaml::Controls::TextBox f_shopName = g_swapChainPanel.FindName(StrUsingStr("shopsearchnametextBox")).as<winrt::Windows::UI::Xaml::Controls::TextBox>();
				f_shopName.Text(StrUsingStr(f_funcom[1]));

				winrt::Windows::UI::Xaml::Controls::TextBox f_shopDesc = g_swapChainPanel.FindName(StrUsingStr("shopsearchdescriptiontextBox")).as<winrt::Windows::UI::Xaml::Controls::TextBox>();
				f_shopName.Text(StrUsingStr(""));

				winrt::Windows::UI::Xaml::Controls::TextBox f_shopTag = g_swapChainPanel.FindName(StrUsingStr("shopsearchprefixtextBox")).as<winrt::Windows::UI::Xaml::Controls::TextBox>();
				f_shopName.Text(StrUsingStr(""));

				winrt::Windows::UI::Xaml::Controls::Button f_shopSearchButton = g_swapChainPanel.FindName(StrUsingStr("shopsearchbutton")).as<winrt::Windows::UI::Xaml::Controls::Button>();
		
				f_shopSearchButton.Command().Execute(f_shopSearchButton.CommandParameter());
				});
			}
		}

	return true;
}

};