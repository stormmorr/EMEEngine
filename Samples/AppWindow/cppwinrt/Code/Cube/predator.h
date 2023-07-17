/*

qcom.h - ECOM Native Decl osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include "Include/Cube.h"

#include "Code/Work/Schedular.h"

#include "Code/Cube/qcom.h"

#include <vector>
#include <map>
#include <boost/any.hpp>

using namespace Cube;
using namespace ecoin;

namespace Cube
{
#define PREDATOR_ACTIONIDX_ENTER 0
#define PREDATOR_ACTIONIDX_COPYED 1
#define PREDATOR_ACTIONIDX_DELETED 2
#define PREDATOR_ACTIONIDX_PASTED 3

class predatorAction;
class predatorPanelText;

class predatorIDX : public ecom_base
{
	predatorIDX()
		{
		std::string f_ref_CurrentPath = "predatorIDX::predatorIDX";

		acClear();

#ifndef OSI_MEM_APP
		ac_Push(m_Start, f_ref_CurrentPath + g_ref_Div + "m_Start");
		ac_Push(m_Finish, f_ref_CurrentPath + g_ref_Div + "m_Finish");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&predatorIDX::acClear);
#endif
		}

	~predatorIDX() { acClear(); }

	void acClear(void)
		{
		m_Start = -1;
		m_Finish = -1;
		}

	int m_Start;
	int m_Finish;

	std::shared_ptr<predatorAction> m_predatorAction;
	std::shared_ptr<predatorPanelText> m_predatorPanelText;
};

class predatorAction : public ecom_base
{
public:
	predatorAction()
		{
		std::string f_ref_CurrentPath = "predatorAction::predatorAction";

		acClear();

#ifndef OSI_MEM_APP
		ac_Push(m_entered, f_ref_CurrentPath + g_ref_Div + "m_entered");
		ac_Push(m_deleted, f_ref_CurrentPath + g_ref_Div + "m_deleted");
		ac_Push(m_pasted, f_ref_CurrentPath + g_ref_Div + "m_pasted");
		ac_Push(m_copied, f_ref_CurrentPath + g_ref_Div + "m_copied");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&predatorAction::acClear);
#endif
		};

	predatorAction(std::string f_ActionText, UINT8 f_ActionIDX)
		{
		std::string f_ref_CurrentPath = "predatorAction::predatorAction";

		acClear();
		acPush(f_ActionText, f_ActionIDX);

#ifndef OSI_MEM_APP
		ac_Push(m_entered, f_ref_CurrentPath + g_ref_Div + "m_entered");
		ac_Push(m_deleted, f_ref_CurrentPath + g_ref_Div + "m_deleted");
		ac_Push(m_pasted, f_ref_CurrentPath + g_ref_Div + "m_pasted");
		ac_Push(m_copied, f_ref_CurrentPath + g_ref_Div + "m_copied");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&predatorAction::acClear);
#endif
		};

	~predatorAction() { acClear(); };

	void acClear(void)
		{
		m_entered.clear();
		m_deleted.clear();
		m_pasted.clear();
		m_copied.clear();
		}

	void acPush(std::string f_ActionText, UINT8 f_ActionIDX)
		{
		switch(f_ActionIDX)
			{
			case PREDATOR_ACTIONIDX_ENTER:
				{
				m_entered += f_ActionText;
				}break;

			case PREDATOR_ACTIONIDX_COPYED:
				{
				m_deleted += f_ActionText;
				}break;

			case PREDATOR_ACTIONIDX_DELETED:
				{
				m_pasted += f_ActionText;
				}break;

			case PREDATOR_ACTIONIDX_PASTED:
				{
				m_copied += f_ActionText;
				}break;
			}
		}

	std::string m_entered;
	std::string m_deleted;
	std::string m_pasted;
	std::string m_copied;

	std::shared_ptr<predatorIDX> m_predatorIDX;
};

class predatorPanelText : public ecom_base
{
public:
	predatorPanelText()
		{
		std::string f_ref_CurrentPath = "predatorPanelText::predatorPanelText";

		acClear();

#ifndef OSI_MEM_APP
		ac_Push(m_Text, f_ref_CurrentPath + g_ref_Div + "m_Text");
		ac_Push(m_HCX, f_ref_CurrentPath + g_ref_Div + "m_HCX");
		ac_Push(m_ICX, f_ref_CurrentPath + g_ref_Div + "m_ICX");
		ac_Push(m_ComID, f_ref_CurrentPath + g_ref_Div + "m_ComID");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&predatorPanelText::acClear);
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSave", (void(ecom_base::*)(void))&predatorPanelText::acSave);
#endif
		};

	predatorPanelText(std::shared_ptr<Qcom_eslfunction> f_function)
		{
		std::string f_ref_CurrentPath = "predatorPanelText::predatorPanelText";

		acClear();
		acFrom_eslfunction(f_function);

#ifndef OSI_MEM_APP
		ac_Push(m_Text, f_ref_CurrentPath + g_ref_Div + "m_Text");
		ac_Push(m_HCX, f_ref_CurrentPath + g_ref_Div + "m_HCX");
		ac_Push(m_ICX, f_ref_CurrentPath + g_ref_Div + "m_ICX");
		ac_Push(m_ComID, f_ref_CurrentPath + g_ref_Div + "m_ComID");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&predatorPanelText::acClear);
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSave", (void(ecom_base::*)(void))&predatorPanelText::acSave);
#endif
		}

	~predatorPanelText() { acClear(); };

	void acClear(void)
		{
		m_Text.clear();
		m_HCX = -1;
		m_ICX = -1;
		m_ComID = -1;
		m_QamID = -1;
		}

	void acSave(void);

	void acFrom_eslfunction(std::shared_ptr<Qcom_eslfunction> f_Function)
		{
		m_ComID = f_Function->m_ComID;
		m_QamID = f_Function->m_QamID;
		m_QamLevel = f_Function->m_QamLevel;
		m_Text.clear();

		for(int f_XY = 0; f_XY < f_Function->m_vec_InitLineOrdered.size(); f_XY++)
			{
			m_Text += f_Function->m_vec_InitLineOrdered[f_XY];
			}
		}

	std::string m_Text;
	int m_HCX;
	int m_ICX;
	int m_ComID;
	int m_QamID;
	int m_QamLevel;
};

class predatorInstance : public ecom_base
{
public:
	predatorInstance();
	predatorInstance(std::shared_ptr<Qcom> f_com);
	~predatorInstance() { ac_Clear(); };

	void ac_Clear(void);
	void acSave(void);
	void acSaveAll(void);

	winrt::hstring acOpen(int f_HDX, int f_IDX);

	void acInsertPanel(int f_HDX, int f_IDX, std::shared_ptr<Qcom_eslfunction> f_function);

	bool acPushPanel(int f_HDX, int f_IDX, std::shared_ptr<predatorPanelText> f_PushPanel);
	std::shared_ptr<predatorPanelText> acPullPanel(int f_HDX, int f_IDX);

	int m_HDX;
	int m_IDX;
	std::shared_ptr<predatorPanelText> m_Panel;
	bool m_Panel_Set;
	int m_ComID;

	//Active code mapping
protected:
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_onLoad;
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_Frame;
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_Input;
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_Output;
	std::vector<std::shared_ptr<predatorAction>> m_vec_Undo;
	std::vector<std::shared_ptr<predatorAction>> m_vec_Redo;
};

class predatorInstanceManager : public ecom_base
{
public:
	predatorInstanceManager()
		{
		std::string f_ref_CurrentPath = "predatorInstanceManager::predatorInstanceManager";

		ac_Clear();

#ifndef OSI_MEM_APP
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSave", (void(ecom_base::*)(void))&predatorInstanceManager::acSave);
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSaveAll", (void(ecom_base::*)(void))&predatorInstanceManager::acSaveAll);
#endif
		};

	~predatorInstanceManager()
		{
		ac_Clear();
		};

	winrt::hstring ac_Open_Com(std::shared_ptr<Qcom> f_com)
		{
		return acSearchIns_byComID(f_com)->acOpen(0, 0);
		}

	winrt::hstring ac_Open_HCX(int f_I, int f_C)
		{
		return m_PredatorIns->acOpen(f_I, f_C);
		}

	std::shared_ptr<predatorInstance> acSearchIns_byComID(std::shared_ptr<Qcom> f_com);

	void ac_Clear(void)
		{
		m_vec_PredatorIns.clear();
		}

	void acSave(void);
	void acSaveAll(void);

	std::shared_ptr<predatorInstance> m_PredatorIns;

	std::vector<std::shared_ptr<predatorInstance>> m_vec_PredatorIns;
};

extern std::vector<std::shared_ptr<predatorInstanceManager>> g_vec_PredatorManager;

};

#endif