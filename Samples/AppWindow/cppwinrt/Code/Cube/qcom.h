/*

qcom.h - ECOM Native Decl osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QCOM_H
#define QCOM_H

#include "Include/Cube.h"
#include "Code/Work/Schedular.h"
#include "qam.h"

#include <vector>
#include <map>
#include <boost/any.hpp>

using namespace Cube;
using namespace ecoin;

enum Pex_IDX
{
	PEX_MAIN_NODE_IDX,
	PEX_EXCOM_MAIN_IDX,
	PEX_INSTALL_MAIN_IDX,
	EXCOM_MAIN_INSERT_IDX,
	EXCOM_MAIN_COMPLETE_IDX,
	EXCOM_MAIN_REMOVE_IDX,
	PEX_IDX_MAX
};

#define PEX_EXECUTE_AFFINITY 1
#define PEX_INSTALL_AFFINITY 1

namespace Cube
{
extern float g_BossLVLMin;

extern std::shared_mutex mutex_qcomdb;
extern std::shared_mutex g_Operatio_Muti;

#if 0
#define OGL_RENDER 1
#endif

#define COM_PAK_TYPE_INSERT 0
#define COM_PAK_TYPE_COMPLETE 1
#define COM_PAK_TYPE_DELETE 2

#define COM_PAK_UNACTIVATED 0
#define COM_PAK_ACTIVATED 1

#define COM_PAKX_STAGE_TITLE 0
#define COM_PAKX_STAGE_EQUAL 1
#define COM_PAKX_STAGE_QUOTE 2
#define COM_PAKX_STAGE_OFF 3

enum Function_Execution_Typing
{
	FuncExec_System_Load,
	FuncExec_Share_Chain,
	FuncExec_Once_Not_Often,
	FuncExec_Async_Driver,
	FuncExec_Interval,
	FuncExec_Timed,
	FuncExec_Total
};

extern int ag_Get_ClassType(std::string f_Packet);

enum
{
	ctVariable,
	ctCClass,
	ctEClass,
	ctQcom,
	ctQcomInput,
	ctQcomOutput,
	ctComFunctionX,
	ctShare,
	ctElement,
	ctMax
};

class ComFunctionButtonSlot : public ecom_base
{
public:
	ComFunctionButtonSlot()
		{
		std::string f_ref_CurrentPath = "Qcom::Qcom";

#ifndef OSI_MEM_APP
		ac_Push(m_ButtonText, f_ref_CurrentPath + g_ref_Div + "m_ButtonText");
		ac_Push(m_Panel, f_ref_CurrentPath + g_ref_Div + "m_Panel");
		ac_Push(m_PanelStack, f_ref_CurrentPath + g_ref_Div + "m_PanelStack");
		ac_Push(m_Button, f_ref_CurrentPath + g_ref_Div + "m_Button");
#endif

		m_ButtonText.clear();
		m_Panel = 0;
		m_PanelStack = 0;
		m_Button = 0;
		};

	~ComFunctionButtonSlot()
		{
		m_ButtonText.clear();
		m_Panel = 0;
		m_PanelStack = 0;
		m_Button = 0;
		};

	std::string m_ButtonText;

	int m_Panel;
	int m_PanelStack;
	int m_Button;
};

class Qcom_genScript : public ecom_base
{
public:
	Qcom_genScript()
		{
		std::string f_ref_CurrentPath = "Qcom_genScript::Qcom_genScript";

		ac_Clear();

		m_ID = -1551;
		m_QamID = g_QamID;

#ifndef OSI_MEM_APP
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&Qcom_genScript::ac_Save);

		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_rseed, f_ref_CurrentPath + g_ref_Div + "m_rseed");
		ac_Push(m_seedinfo, f_ref_CurrentPath + g_ref_Div + "m_seedinfo");
		ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
		ac_Push(m_name, f_ref_CurrentPath + g_ref_Div + "m_name");
		ac_Push(m_description, f_ref_CurrentPath + g_ref_Div + "m_description");
		ac_Push(m_vision, f_ref_CurrentPath + g_ref_Div + "m_vision");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
		ac_Push(m_vec_InitLine, f_ref_CurrentPath + g_ref_Div + "m_vec_InitLine");
		ac_Push(m_vec_InitLineOrder, f_ref_CurrentPath + g_ref_Div + "m_vec_InitLineOrder");
		ac_Push(m_vec_InitLineOrderID, f_ref_CurrentPath + g_ref_Div + "m_vec_InitLineOrderID");
		ac_Push(m_vec_InitLineOrdered, f_ref_CurrentPath + g_ref_Div + "m_vec_InitLineOrdered");
		ac_Push(m_vec_InitLineOrderedID, f_ref_CurrentPath + g_ref_Div + "m_vec_InitLineOrderedID");
#endif
		};

	Qcom_genScript(int f_ID, bool f_loadall = false);

	~Qcom_genScript() { ac_Clear(); };

	void ac_Clear(void);

	void ac_Save(void);

	int m_ID;
	int m_ComID;
	int m_birthcomid;
	bool m_Save;
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;
	std::string m_NameGroup;

	int m_rseed;
	std::string m_seedinfo;
	std::string m_TargetString;

	//Active code mapping
	std::vector<std::string> m_vec_InitLine;
	std::vector<int> m_vec_InitLineOrder;
	std::vector<int> m_vec_InitLineOrderID;
	std::vector<std::string> m_vec_InitLineOrdered;
	std::vector<int> m_vec_InitLineOrderedID;

	int m_QamLevel;
	int m_QamID;
};

class Qcom_eslfunction : public ecom_base
{
public:
	Qcom_eslfunction()
		{
		std::string f_ref_CurrentPath = "Qcom_eslfunction::Qcom_eslfunction";

		ac_Clear();

		m_ID = -1551;
		m_QamID = g_QamID;

#ifndef OSI_MEM_APP
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&Qcom_eslfunction::ac_Save);

		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_rseed, f_ref_CurrentPath + g_ref_Div + "m_rseed");
		ac_Push(m_seedinfo, f_ref_CurrentPath + g_ref_Div + "m_seedinfo");
		ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
		ac_Push(m_name, f_ref_CurrentPath + g_ref_Div + "m_name");
		ac_Push(m_description, f_ref_CurrentPath + g_ref_Div + "m_description");
		ac_Push(m_vision, f_ref_CurrentPath + g_ref_Div + "m_vision");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
#endif
		};

	Qcom_eslfunction(int f_ID, bool f_loadall = false);

	~Qcom_eslfunction()
		{ ac_Clear(); };

	void ac_Clear(void);
	void ac_Save(void);

	void ac_Compile_Execute(void);
	void ac_Execute(void);

	int m_ID;
	int m_ComID;
	int m_birthcomid;
	bool m_Save;
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_classname;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	int m_rseed;
	std::string m_seedinfo;
	std::string m_TargetString;
	std::string m_FunctionLine;

	//Active code mapping
	std::vector<std::string> m_vec_InitLine;
	std::vector<int> m_vec_InitLineOrder;
	std::vector<int> m_vec_InitLineOrderID;
	std::vector<std::string> m_vec_InitLineOrdered;
	std::vector<int> m_vec_InitLineOrderedID;
	std::vector<int> m_vec_ResultIDXupdateLineNumber;

	//esl contract
	std::shared_ptr<ecoin::Contract> m_Contract;

	std::shared_ptr<Variable> m_Result_Var;
	std::shared_ptr<ClassVar> m_Result_ClassVar;

	int m_QamLevel;
	int m_QamID;
};

class QcomInput : public ecom_base
{
public:
	QcomInput()
		{
		std::string f_ref_CurrentPath = "QcomInput::QcomInput";

		acClear();

		m_ID = -1551;
		m_HighLighted = false;
		m_Selected = false;
		m_QamID = g_QamID;

		ag_StatusLive(f_ref_CurrentPath, "m_InputFunction");
		m_InputFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();

#ifndef OSI_MEM_APP
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&QcomInput::ac_Save);
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelect", (void(ecom_base::*)(bool))&QcomInput::acSelect, false);
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHighLight", (void(ecom_base::*)(bool))&QcomInput::acHighLight, false);

		ac_Push(m_rebuild, f_ref_CurrentPath + g_ref_Div + "m_rebuild");
		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
		ac_Push(m_parentx, f_ref_CurrentPath + g_ref_Div + "m_parentx");
		ac_Push(m_parenty, f_ref_CurrentPath + g_ref_Div + "m_parenty");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_Selected, f_ref_CurrentPath + g_ref_Div + "m_Selected");
		ac_Push(m_HighLighted, f_ref_CurrentPath + g_ref_Div + "m_HighLighted");
		ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
		ac_Push(m_name, f_ref_CurrentPath + g_ref_Div + "m_name");
		ac_Push(m_description, f_ref_CurrentPath + g_ref_Div + "m_description");
		ac_Push(m_vision, f_ref_CurrentPath + g_ref_Div + "m_vision");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
#endif
		}

	QcomInput(int f_ID, bool f_loadall = false);

	~QcomInput() {};

	void acClear(void)
		{
		//ag_StatusLive(f_ref_CurrentPath, "m_position");
		m_position = std::make_shared<Cube::BiVector>(0.0f);

		m_typed = 0;
		}

	void ac_Save(void);

	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

		/////////////
	   // GL
	  //
	 ///
	///
#if 0
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;

	// Indices
	GLuint mIndexBuffer;
#endif

	std::shared_ptr<BiVector> m_position;

	std::vector<BiVector> m_vec_Vertex;
	std::vector<BiVector> m_vec_Normal;
	std::vector<BiColor> m_vec_Color;
	std::vector<BiTex> m_vec_Tex;
	std::vector<Index> m_vec_Index;

	std::vector<std::shared_ptr<Variable>> m_vec_InputVar;

	bool m_rebuild;

	int m_ID;
	int m_ComID;
	int m_ICOID;
	int m_birthcomid;

	float m_parentx;
	float m_parenty;

	bool m_Save;
	int m_typed;

	bool m_Selected;
	bool m_HighLighted;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;
	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_InputfunctionID;
	int m_InputfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_InputFunction;

	int m_QamLevel;
	int m_QamID;
};

class QcomControl : public ecom_base
{
public:
	QcomControl()
		{
		std::string f_ref_CurrentPath = "QcomControl::QcomControl";

		acClear();

		//ag_StatusLive(f_ref_CurrentPath, "m_position");
		m_position = std::make_shared<Cube::BiVector>(0.0f);

		m_ID = -1551;
		m_QamID = g_QamID;

		ag_StatusLive(f_ref_CurrentPath, "m_ControlFunction");
		m_ControlFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();

#ifndef OSI_MEM_APP
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&QcomControl::ac_Save);

		ac_Push(m_rebuild, f_ref_CurrentPath + g_ref_Div + "m_rebuild");
		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
		ac_Push(m_parentx, f_ref_CurrentPath + g_ref_Div + "m_parentx");
		ac_Push(m_parenty, f_ref_CurrentPath + g_ref_Div + "m_parenty");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
		ac_Push(m_name, f_ref_CurrentPath + g_ref_Div + "m_name");
		ac_Push(m_description, f_ref_CurrentPath + g_ref_Div + "m_description");
		ac_Push(m_vision, f_ref_CurrentPath + g_ref_Div + "m_vision");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
#endif
		};

	QcomControl(int f_ID, bool f_loadall = false);

	~QcomControl() { acClear(); };

	void acClear(void)
		{
		m_vec_Vertex.clear();
		m_vec_Normal.clear();
		m_vec_Color.clear();
		m_vec_Tex.clear();
		m_vec_Index.clear();
		m_typed = 0;
		}

	void ac_Save(void);

		/////////////
	   // GL
	  //
	 ///
#if 0
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;

	// Indices
	GLuint mIndexBuffer;
#endif

	std::shared_ptr<BiVector> m_position;

	std::vector<std::shared_ptr<BiVector>> m_vec_Vertex;
	std::vector<std::shared_ptr<BiVector>> m_vec_Normal;
	std::vector<BiColor*> m_vec_Color;
	std::vector<BiTex*> m_vec_Tex;
	std::vector<Index*> m_vec_Index;

	std::vector<std::shared_ptr<Variable>> m_vec_ControlVar;

	bool m_rebuild;

	int m_ID;
	int m_ComID;
	int m_ICOID;
	int m_birthcomid;

	float m_parentx;
	float m_parenty;

	bool m_Save;
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;
	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_ControlfunctionID;
	int m_ControlfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_ControlFunction;

	int m_QamLevel;
	int m_QamID;
};

class QcomOutput : public ecom_base
{
public:
	QcomOutput()
		{
		std::string f_ref_CurrentPath = "QcomOutput::QcomOutput";

		acClear();

		m_ID = -1551;
		m_HighLighted = false;
		m_Selected = false;
		m_QamID = g_QamID;

		ag_StatusLive(f_ref_CurrentPath, "m_OutputFunction");
		m_OutputFunction = std::make_shared_reflect<Cube::Qcom_eslfunction>();

#ifndef OSI_MEM_APP
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&QcomOutput::ac_Save);
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelect", (void(ecom_base::*)(bool))&QcomOutput::acSelect, false);
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHighLight", (void(ecom_base::*)(bool))&QcomOutput::acHighLight, false);

		ac_Push(m_rebuild, f_ref_CurrentPath + g_ref_Div + "m_rebuild");
		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
		ac_Push(m_parentx, f_ref_CurrentPath + g_ref_Div + "m_parentx");
		ac_Push(m_parenty, f_ref_CurrentPath + g_ref_Div + "m_parenty");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_Selected, f_ref_CurrentPath + g_ref_Div + "m_Selected");
		ac_Push(m_HighLighted, f_ref_CurrentPath + g_ref_Div + "m_HighLighted");
		ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
		ac_Push(m_name, f_ref_CurrentPath + g_ref_Div + "m_name");
		ac_Push(m_description, f_ref_CurrentPath + g_ref_Div + "m_description");
		ac_Push(m_vision, f_ref_CurrentPath + g_ref_Div + "m_vision");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
#endif
		};

	QcomOutput(int f_ID, bool f_loadall = false);

	~QcomOutput() {};

	void acClear(void)
		{
		//ag_StatusLive(f_ref_CurrentPath, "m_position");
		m_position = std::make_shared<Cube::BiVector>(0.0f);

		m_typed = 0;
		}

#if 0 // OpenGL Initialize
	void Initialize(void);
	void Unload(void);
	void GenerateBuffers(void);
#endif

	void ac_Save(void);
	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

	std::shared_ptr<BiVector> m_position;

		/////////////
	   // GL
	  //
	 ///
#if 0
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;
	GLuint mIndexBuffer;
#endif

	std::vector<std::shared_ptr<BiVector>> m_vec_Vertex;
	std::vector<std::shared_ptr<BiVector>> m_vec_Normal;
	std::vector<BiColor*> m_vec_Color;
	std::vector<BiTex*> m_vec_Tex;
	std::vector<Index*> m_vec_Index;

	std::vector<std::shared_ptr<Variable>> m_vec_OutputVar;

	bool m_rebuild;

	int m_ID;
	int m_ComID;
	int m_ICOID;
	int m_birthcomid;

	float m_parentx;
	float m_parenty;

	bool m_Save;
	int m_typed;

	bool m_Selected;
	bool m_HighLighted;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_OutputfunctionID;
	int m_OutputfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_OutputFunction;

	int m_QamLevel;
	int m_QamID;
};

class QcomWire;

class Qcom : public ecom_base
{
public:
	Qcom();
	Qcom(int f_ID, bool f_loadall = false);

	~Qcom();

	void ac_Clear(void);

	// Initialize
	void Initialize(void);
	void GenerateBuffers(void);
	void Unload(void);

	void ac_Save(void);
	void ac_Execute(void);

	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

		/////////////
	   // GL
	  //
	 ///
#ifdef OGL_RENDER
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;
	GLuint mIndexBuffer;
#endif

	std::shared_ptr<BiVector> m_position;

	std::vector<BiVector> m_vec_Vertex;
	std::vector<BiVector> m_vec_Normal;
	std::vector<BiColor> m_vec_Color;
	std::vector<BiTex> m_vec_Tex;
	std::vector<Index> m_vec_Index;

	bool m_rebuild;

	int m_ID;
	int m_parentcomid;
	int m_birthcomid;
	int m_PackageShareID;

	std::shared_ptr<Qcom> m_ParentCom;

	std::vector<std::shared_ptr<Qcom>> m_vec_Qcom;
	std::vector<std::shared_ptr<Qcom>> m_vec_Execute_Chain;

	std::vector<std::shared_ptr<QcomInput>> m_vec_Input;
	std::vector<std::shared_ptr<QcomOutput>> m_vec_Output;
	std::vector<std::shared_ptr<QcomWire>> m_vec_ComWire;

	std::vector<std::shared_ptr<Qcom_genScript>> m_vec_GenScript;
	std::vector<std::shared_ptr<Qcom_eslfunction>> m_vec_ESLFunction;

	std::shared_ptr<Qcom_eslfunction> m_Frame_ESLFunction; 

	int m_Execute_Priority;

	float m_parentx;
	float m_parenty;

	bool m_Save;
	int m_typed;

	bool m_Selected;
	bool m_HighLighted;

	int m_rseed;
	std::string m_seedinfo;

	std::string m_owner;
	std::string m_name;
	std::string m_overload;
	std::string m_description;
	std::string m_vision;
	std::string m_NameGroup;

	int m_VoteScore;

	std::shared_ptr<Qcom_genScript> m_genScript;

	int m_QamLevel;
	int m_QamID;

	int m_Trial_Length;

	float m_Cost;
	float m_BossLVLMin;
};

class QcomWire : public ecom_base
{
public:
	QcomWire()
		{
		std::string f_ref_CurrentPath = g_ref_global_start + "QcomWire::QcomWire";

		m_Time = 0.0f;
		m_ID = -1551;
		m_HighLighted = false;
		m_Selected = false;

#ifndef OSI_MEM_APP
		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_parentcomid, f_ref_CurrentPath + g_ref_Div + "m_parentcomid");
		ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
		ac_Push(m_Xmin, f_ref_CurrentPath + g_ref_Div + "m_Xmin");
		ac_Push(m_Ymin, f_ref_CurrentPath + g_ref_Div + "m_parentcomid");
		ac_Push(m_Xmax, f_ref_CurrentPath + g_ref_Div + "m_Xmax");
		ac_Push(m_Ymax, f_ref_CurrentPath + g_ref_Div + "m_Ymax");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_Length, f_ref_CurrentPath + g_ref_Div + "m_Length");
		ac_Push(m_Height, f_ref_CurrentPath + g_ref_Div + "m_Height");
		ac_Push(m_indexCount, f_ref_CurrentPath + g_ref_Div + "m_indexCount");
		ac_Push(m_Time, f_ref_CurrentPath + g_ref_Div + "m_Time");
		ac_Push(m_Selected, f_ref_CurrentPath + g_ref_Div + "m_Selected");
		ac_Push(m_HighLighted, f_ref_CurrentPath + g_ref_Div + "m_HighLighted");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&QcomWire::ac_Save);
#endif
		};

	QcomWire(int f_ID, bool f_loadall = false);

	~QcomWire() {};

	void ac_Save(void);

	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

	int m_ID;
	int m_parentcomid;
	int m_birthcomid;

	std::shared_ptr<Qcom> m_ParentCom;

	bool m_Save;
	int m_typed;

	std::string m_NameGroup;

	std::shared_ptr<QcomOutput> m_Output;
	std::shared_ptr<Qcom> m_OutputCom;

	std::shared_ptr<QcomInput> m_Input;
	std::shared_ptr<Qcom> m_InputCom;

	int m_QamLevel;
	int m_QamID;

	float m_Xmin;
	float m_Ymin;
	float m_Xmax;
	float m_Ymax;

	float m_Length;
	float m_Height;

	int m_indexCount;

	float m_Time;

	bool m_Selected;
	bool m_HighLighted;

	std::vector<BiVector> m_vec_Vertice;
	std::vector<BiVector> m_vec_Color;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_curvevertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_curveindexBuffer;
};

class WireCom : public ecom_base
{
public:
	WireCom()
		{
		std::string f_ref_CurrentPath = g_ref_global_start + "WireCom::WireCom";

		m_Time = 0.0f;
		m_ID = -1551;
		m_NameGroup.clear();

#ifndef OSI_MEM_APP
		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
		ac_Push(m_X, f_ref_CurrentPath + g_ref_Div + "m_X");
		ac_Push(m_Y, f_ref_CurrentPath + g_ref_Div + "m_Y");
		ac_Push(m_Time, f_ref_CurrentPath + g_ref_Div + "m_Time");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&WireCom::ac_Save);
#endif
		};

	WireCom(float f_X, float f_Y)
		{
		std::string f_ref_CurrentPath = g_ref_global_start + "WireCom::WireCom";

		m_Time = 0.0f;
		m_ID = -1551;
		m_X = f_X;
		m_Y = f_Y;
		m_NameGroup.clear();

#ifndef OSI_MEM_APP
		ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
		ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
		ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
		ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
		ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
		ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
		ac_Push(m_X, f_ref_CurrentPath + g_ref_Div + "m_X");
		ac_Push(m_Y, f_ref_CurrentPath + g_ref_Div + "m_Y");
		ac_Push(m_Time, f_ref_CurrentPath + g_ref_Div + "m_Time");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&WireCom::ac_Save);
#endif
		};

	~WireCom()
		{
		m_NameGroup.clear();
		};

	WireCom(int f_ID, bool f_loadall = false);

	void ac_Save(void);

	int m_ID;
	bool m_Save;
	int m_typed;

	std::string m_NameGroup;

	float m_X;
	float m_Y;

	std::shared_ptr<QcomWire> m_ComWire;
	std::shared_ptr<Qcom> m_ParentCom;

	int m_QamLevel;
	int m_QamID;

	float m_Time;
};

class BiPacket : public ecom_base
{
public:
	BiPacket()
		{
		std::string f_ref_CurrentPath = g_ref_global_start + "BiPacket::BiPacket";

		acClear();

#ifndef OSI_MEM_APP
		ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
		ac_Push(m_DefaultValue, f_ref_CurrentPath + g_ref_Div + "m_DefaultValue");
		ac_Push(m_Comment, f_ref_CurrentPath + g_ref_Div + "m_Comment");
		ac_Push(m_InsertElementType, f_ref_CurrentPath + g_ref_Div + "m_InsertElementType");
		ac_Push(m_ClassType, f_ref_CurrentPath + g_ref_Div + "m_ClassType");
		ac_Push(m_ShareID, f_ref_CurrentPath + g_ref_Div + "m_ShareID");
		ac_Push(m_Element, f_ref_CurrentPath + g_ref_Div + "m_Element");
		ac_Push(m_Activate_Status, f_ref_CurrentPath + g_ref_Div + "m_Activate_Status");
		ac_Push(m_Visible, f_ref_CurrentPath + g_ref_Div + "m_Visible");
		ac_Push(m_vec_Package_XElement_Title, f_ref_CurrentPath + g_ref_Div + "m_vec_Package_XElement_Title");
		ac_Push(m_vecvec_Package_Arg_Title, f_ref_CurrentPath + g_ref_Div + "m_vecvec_Package_Arg_Title");
		ac_Push(m_vecvec_Package_Arg_Data, f_ref_CurrentPath + g_ref_Div + "m_vecvec_Package_Arg_Data");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&BiPacket::acClear);
#endif
		}

	~BiPacket()
		{
		acClear();
		}

	void acClear(void)
		{
		m_InsertElementType = -1;
		m_ClassType = -1;
		m_ShareID = -1;
		m_Element = -1;
		m_Name.clear();
		m_DefaultValue.clear();
		m_Activate_Status = COM_PAK_UNACTIVATED;
		m_Visible = true;
		}

	std::shared_ptr<Qcom> m_Operator_Com;

	std::string m_Name;
	std::string m_DefaultValue;
	std::string m_Comment;

	int m_InsertElementType;
	int m_ClassType;
	int m_ShareID;
	int m_Element;

	int m_Activate_Status;
	bool m_Visible;

	std::vector<std::shared_ptr<BiPacket>> m_vec_Packet;
	std::vector<std::shared_ptr<BiPacket>> m_vec_Packet_Delete;

	std::vector<std::string> m_vec_Package_XElement_Title;
	std::vector<std::vector<std::string>> m_vecvec_Package_Arg_Title;
	std::vector<std::vector<std::string>> m_vecvec_Package_Arg_Data;
};

class QcomManager : public ecom_base
{
public:
	/* Public methods */
	QcomManager();
	~QcomManager();

	void acClear(void);
	void acClearGrid(void);
	void acClearGridNew(std::shared_ptr<Qcom> f_NewCom);

	void GenerateBuffers(void);

	void acQcom_Frame(void);
	bool acRenderGrid(void);

	//user controls
	void ac_FireLTClick(void);
	void ac_FireRTClick(void);

	void ac_DragGrid(float f_X, float f_Y);

	//first run only! dev
	void ac_com_base_v1(bool f_memOnly = false);

	void ac_LoadAll(int f_QamID, int f_QamLevel = -5);
	void ac_LoadAll_Append(int f_QamID, int f_QamLevel = -5);
	void ac_PlushScripts(int f_QamID, int f_QamLevel = -5);
	void ac_Wire(int f_QamID, int f_QamLevel = -5);
	void acParse_GenScript(std::shared_ptr<Qcom> f_com);
	void acSelectNone(void);
	void acHighLightNone(void);
	void acPlace_FunctionCom(void);
	void acDisplayOn(void);

	std::shared_ptr<Qcom> ac_Find_Com_ByID(int f_ID);
	std::shared_ptr<QcomWire> ac_Find_ComWire_ByID(int f_ID);
	std::shared_ptr<QcomInput> ac_Find_ComInput_ByID(int f_ID);
	std::shared_ptr<QcomOutput> ac_Find_ComOutput_ByID(int f_ID);
	std::shared_ptr<WireCom> ac_Find_WireCom_ByID(int f_ID);
	std::shared_ptr<Qcom_eslfunction> ac_Find_Function_ByID(int f_ID);
	std::shared_ptr<Qcom_genScript> ac_Find_GenerationScript_ByID(int f_ID);
	std::vector<std::shared_ptr<BiPacket>> acSearch_PacketbyName(std::string f_Name);

	std::shared_ptr<Qcom> mam_Qcom;
	std::shared_ptr<Qcom> m_Qcom;
	std::shared_ptr<Qcom_genScript> m_vec_defGenScript;
	std::shared_ptr<Qcom_eslfunction> m_vec_defESLFunction;

	std::vector<std::shared_ptr<BiPacket>> m_vec_Packet;

	std::vector<std::shared_ptr<Qcom>> m_SaveCom;
	std::vector<std::shared_ptr<Qcom>> m_vec_Qcom;

	std::vector<std::shared_ptr<QcomInput>> m_vec_Input;
	std::vector<std::shared_ptr<QcomOutput>> m_vec_Output;

	std::vector<std::shared_ptr<Qcom_genScript>> m_vec_GenScript;
	std::vector<std::shared_ptr<Qcom_eslfunction>> m_vec_ESLFunction;

	std::vector<std::shared_ptr<QcomWire>> m_vec_ComWire;
	std::vector<std::shared_ptr<WireCom>> m_vec_WireCom;

	std::vector<std::shared_ptr<QcomInput>> m_Wiring_Input;
	std::vector<std::shared_ptr<QcomOutput>> m_Wiring_Output;

	//Display
	bool m_DisplayOn;
	bool m_rebuild;
	bool m_Open;
	bool m_PointerCharge;
	bool m_drag_on;

	float m_current_X;
	float m_current_Y;
	float m_current_X_jeb;
	float m_current_Y_jeb;
	float m_drag_X;
	float m_drag_Y;
	float m_current_Zoom;

	int m_ecomSelectedCount;
	int m_inputSelectedCount;
	int m_outputSelectedCount;
	int m_wireSelectedCount;

	int m_preference_ShareID;
	float m_preference_Amt;

	std::shared_mutex m_Qcom_Muti;
	
	int mDrawCount;
	int m_QcomCount;

	    /////////////
	   // GL
	  //
	 ///
	///
#ifdef OGL_RENDER
	GLuint mProgram;
	GLuint mProgramM;
	GLuint mProgramGrid;

	GLsizei mWindowWidth;
	GLsizei mWindowHeight;

	GLint mModelUniformLocation;
	GLint mViewUniformLocation;
	GLint mProjUniformLocation;

	GLint mCameraTranslationUniformLocation;

	GLint mModelUniformLocationM;
	GLint mViewUniformLocationM;
	GLint mProjUniformLocationM;

	GLint mModelUniformLocationGrid;
	GLint mViewUniformLocationGrid;
	GLint mProjUniformLocationGrid;

	GLint mPosUniformLocation;
	GLint mPosUniformLocationGrid;
	GLint mColorUniformLocationGrid;

	GLint mPositionAttribLocation;
	GLint mNormalAttribLocation;
	GLint mColorAttribLocation;
	GLint mTexCoordAttribLocation;

	GLint mPositionAttribLocationM;
	//GLint mNormalAttribLocationM;
	GLint mColorAttribLocationM;
	//GLint mTexCoordAttribLocationM;

	GLint mPositionAttribLocationGrid;
	//GLint mNormalAttribLocationM;
	GLint mColorAttribLocationGrid;
	//GLint mTexCoordAttribLocationM;

	GLint mLightPosUniformLocation;
	GLint mLightColorUniformLocation;
	GLint mLightNomUniformLocation;

		/////////////
	   // GL
	  //
	 ///
	GLuint mVertexPositionBuffer;
	GLuint mVertexColorBuffer;

	// Indices
	GLuint mIndexBuffer;

	// Grid
	GLuint mVertexPositionBufferGrid;
	GLuint mVertexColorBufferGrid;

	// Indices
	GLuint mIndexBufferGrid;
#else
	int mWindowWidth;
	int mWindowHeight;
#endif
};

extern std::shared_ptr<QcomManager> g_QcomManager;

extern std::shared_ptr<Qcom> g_PreCom;
extern bool g_PreComBool;
extern bool g_PreComLock;
extern int g_PreComBoughtIN;
extern bool g_PreComInclude;

extern std::shared_ptr<Qcom_genScript> gqcom_INLfromComID(int f_ComID);
extern std::shared_ptr<Qcom_genScript> gqcom_INLfromString(std::string f_String);

class SelectionPreList : public ecom_base
{
public:
	SelectionPreList()
		{
		std::string f_ref_CurrentPath = g_ref_global_start + "SelectionPreList::SelectionPreList";

#if 0
		ag_StatusLive(f_ref_CurrentPath, "m_position");
#endif

		m_position = std::make_shared<BiVector>(0.0f);

		acClear();

#ifndef OSI_MEM_APP
		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&BiPacket::acClear);
#endif
		}

	~SelectionPreList()
		{
		m_position = nullptr;

		acClear();
		}

	void acClear(void)
		{
		m_vec_com.clear();
		m_vec_input.clear();
		m_vec_output.clear();
		m_vec_wire.clear();
		}

	void acPush(std::shared_ptr<Qcom> f_com)
		{
		m_vec_com.push_back(f_com);
		}

	void acPush(std::shared_ptr<QcomInput> f_com)
		{
		m_vec_input.push_back(f_com);
		}

	void acPush(std::shared_ptr<QcomOutput> f_com)
		{
		m_vec_output.push_back(f_com);
		}

	void acPush(std::shared_ptr<QcomWire> f_com)
		{
		m_vec_wire.push_back(f_com);
		}

	std::shared_ptr<Qcom> acSelectionList_ByBiDistance(void);
	int acSelectionList_ByBiDistanceChase(void);

	std::vector<std::shared_ptr<Qcom>> m_vec_com;
	std::vector<std::shared_ptr<QcomInput>> m_vec_input;
	std::vector<std::shared_ptr<QcomOutput>> m_vec_output;
	std::vector<std::shared_ptr<QcomWire>> m_vec_wire;

	std::shared_ptr<BiVector> m_position;
};

class BiDecisionA : public ecom_base
	{
	public:
		BiDecisionA(std::string f_TitleText, std::string f_ObjectNameOverride, int f_Trial_Length = -1, int f_Trial_QamID = 0)
			{
			std::string f_ref_CurrentPath = "BiDecisionA::BiDecisionA";

			m_TitleText.clear();
			m_TitleText = f_TitleText;
			m_ObjectNameOverride.clear();
			m_ObjectNameOverride = f_ObjectNameOverride;
			m_Trial_Length = f_Trial_Length;
			m_Trial_QamID = f_Trial_QamID;
			m_Applied = false;

#ifndef OSI_MEM_APP
			ac_Push(m_TitleText, f_ref_CurrentPath + g_ref_Div + "m_TitleText");
			ac_Push(m_ObjectNameOverride, f_ref_CurrentPath + g_ref_Div + "m_ObjectNameOverride");
			ac_Push(m_Trial_Length, f_ref_CurrentPath + g_ref_Div + "m_Trial_Length");
			ac_Push(m_Trial_QamID, f_ref_CurrentPath + g_ref_Div + "m_Trial_QamID");
			ac_Push(m_Applied, f_ref_CurrentPath + g_ref_Div + "m_Applied");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acApply", (bool(ecom_base::*)(void))&BiDecisionA::acApply);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acUnApply", (bool(ecom_base::*)(void))&BiDecisionA::acUnApply);
#endif
			};

		~BiDecisionA() { m_TitleText.clear(); m_ObjectNameOverride.clear(); m_Trial_QamID = 0; m_Trial_Length = -1; m_Applied = false; };

		bool acApply(void);
		bool acUnApply(void);

		std::string m_TitleText;
		std::string m_ObjectNameOverride;
		int m_Trial_Length;
		int m_Trial_QamID;
		bool m_Applied;
	};

class BiDecisionOverride : public ecom_base
	{
	public:
		BiDecisionOverride()
			{
			std::string f_ref_CurrentPath = "BiDecisionOverride::BiDecisionOverride";

			m_Existence_ID = -1;
			m_Existence_ShareID = -1;
			m_PipeChan = 0;

#ifndef OSI_MEM_APP
			ac_Push(m_PipeChan, f_ref_CurrentPath + g_ref_Div + "m_PipeChan");
			ac_Push(m_Existence_ID, f_ref_CurrentPath + g_ref_Div + "m_Existence_ID");
			ac_Push(m_Existence_ShareID, f_ref_CurrentPath + g_ref_Div + "m_Existence_ShareID");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acScan", (bool(ecom_base::*)(void))&BiDecisionOverride::acScan);
#endif
			};

		BiDecisionOverride(int f_ComID, int f_PipeChan = 0, int f_ShareID = -1) { m_Existence_ID = f_ComID; m_PipeChan = f_PipeChan; m_Existence_ShareID = f_ShareID; };
		~BiDecisionOverride() {};

#pragma message("Once::Added-g_ShareManager->acPushShareID(acLoadShare(ID))-Proceed with Existance ShareID")

		bool acScan(void)
			{
			switch(m_PipeChan)
				{
				case ECOIN_CLS_COM:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Qcom.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Qcom[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_INPUT:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Input.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Input[f_XY]->m_ID == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_OUTPUT:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Output.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Output[f_XY]->m_ID == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_WIRE:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_ComWire.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_ComWire[f_XY]->m_ID == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_COM_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Qcom.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Qcom[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_INPUT_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Input.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Input[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_OUTPUT_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Output.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Output[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_WIRE_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_ComWire.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_ComWire[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;
				}

			return false;
			}

		int m_PipeChan;
		int m_Existence_ID;
		int m_Existence_ShareID;
	};

class BiDecisionQ : public ecom_base
	{
	public:
		BiDecisionQ(int f_PipeChan = 0, int f_ComID = -1, int f_ShareID = -1)
			{
			std::string f_ref_CurrentPath = "BiDecisionQ::BiDecisionQ";

			acClear();

			m_PipeChan = f_PipeChan;
			m_Existence_ID = f_ComID;
			m_Existence_ShareID = f_ShareID;

			acStoreCount();

#ifndef OSI_MEM_APP
			ac_Push(m_ecomSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_ecomSelectedCount");
			ac_Push(m_inputSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_inputSelectedCount");
			ac_Push(m_outputSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_outputSelectedCount");
			ac_Push(m_wireSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_wireSelectedCount");
			ac_Push(m_Visible, f_ref_CurrentPath + g_ref_Div + "m_Visible");
			ac_Push(m_Trial_Length_Remain, f_ref_CurrentPath + g_ref_Div + "m_Trial_Length_Remain");
			ac_Push(m_PipeChan, f_ref_CurrentPath + g_ref_Div + "m_PipeChan");
			ac_Push(m_Existence_ID, f_ref_CurrentPath + g_ref_Div + "m_Existence_ID");
			ac_Push(m_Existence_ShareID, f_ref_CurrentPath + g_ref_Div + "m_Existence_ShareID");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelectOverrides", (void(ecom_base::*)(bool))&BiDecisionQ::acSelectOverrides, false);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&BiDecisionQ::acClear);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acStoreCount", (bool(ecom_base::*)(void))&BiDecisionQ::acStoreCount);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acCheck_Show", (bool(ecom_base::*)(void))&BiDecisionQ::acCheck_Show);
#endif

			if(f_ComID >= 0)
				{
				ag_StatusLive(f_ref_CurrentPath, "m_vec_DecisionOverride");
				m_vec_DecisionOverride.push_back(std::make_shared_reflect<BiDecisionOverride>(f_ComID, f_PipeChan, f_ShareID));
				}
			else if(f_ShareID >= 0)
				{
				ag_StatusLive(f_ref_CurrentPath, "m_vec_DecisionOverride");
				m_vec_DecisionOverride.push_back(std::make_shared_reflect<BiDecisionOverride>(f_ComID, f_PipeChan, f_ShareID));
				}
			};

		~BiDecisionQ() { acClear(); };

		void acSelectOverrides(bool f_Clear = false);

		void acClear(void)
			{
			m_vec_DecisionOverride.clear();
			m_vec_DecisionA.clear();

			m_PipeChan = -1;
			m_Existence_ID = -1;
			m_Existence_ShareID = -1;
			m_ecomSelectedCount = -101;
			m_inputSelectedCount = -101;
			m_outputSelectedCount = -101;
			m_wireSelectedCount = -101;
			m_Visible = true;
			m_Trial_Length_Remain = -1;
			}

		//reflection interop bridging ?
		void acAdd_Answer(std::shared_ptr<BiDecisionA> f_DecisionA)
			{
			m_vec_DecisionA.push_back(f_DecisionA);
			}

		bool acStoreCount(void)
			{
			m_ecomSelectedCount = -105;
			m_inputSelectedCount = -105;
			m_outputSelectedCount = -105;
			m_wireSelectedCount = -105;

			return true;
			};

		bool acCheck_Show(void)
			{
			if(m_ecomSelectedCount != -105)
				{
				if(m_ecomSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_Qcom.size() >= 1)
						{
						return true;
						}
					}

				if(m_inputSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_Input.size() >= 1)
						{
						return true;
						}
					}

				if(m_outputSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_Output.size() >= 1)
						{
						return true;
						}
					}

				if(m_wireSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_ComWire.size() >= 1)
						{
						return true;
						}
					}

				if(m_ecomSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_Qcom.size() == 0)
						{
						return true;
						}
		
					}

				if(m_inputSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_Input.size() == 0)
						{
						return true;
						}
					}

				if(m_outputSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_Output.size() == 0)
						{
						return true;
						}
					}

				if(m_wireSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_ComWire.size() == 0)
						{
						return true;
						}
					}

				if(g_QcomManager->m_ecomSelectedCount == m_ecomSelectedCount)
					{
					return true;
					}

				if(g_QcomManager->m_inputSelectedCount == m_inputSelectedCount)
					{
					return true;
					}

				if(g_QcomManager->m_outputSelectedCount == m_outputSelectedCount)
					{
					return true;
					}

				if(g_QcomManager->m_wireSelectedCount == m_wireSelectedCount)
					{
					return true;
					}
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_DecisionOverride.size(); f_XYZ++)
				{
				std::shared_ptr<BiDecisionOverride> f_Oride = m_vec_DecisionOverride[f_XYZ];

				if(f_Oride->acScan() == true)
					{
					return true;
					}
				}

			return false;
			};

		int m_ecomSelectedCount;
		int m_inputSelectedCount;
		int m_outputSelectedCount;
		int m_wireSelectedCount;

		std::vector<std::shared_ptr<BiDecisionOverride>> m_vec_DecisionOverride;
		std::vector<std::shared_ptr<BiDecisionA>> m_vec_DecisionA;

		bool m_Visible;

		int m_Trial_Length_Remain;

		int m_PipeChan;
		int m_Existence_ID;
		int m_Existence_ShareID;
	};

class SelectionSave;

class DecisionWheel : public ecom_base
	{
	public:
		DecisionWheel()
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "DecisionWheel::DecisionWheel";

			//ag_StatusLive(f_ref_CurrentPath, "m_SelectPosition");
			m_SelectPosition = std::make_shared<Cube::BiVector>(0.0f);

			//ag_StatusLive(f_ref_CurrentPath, "m_position");
			m_position = std::make_shared<Cube::BiVector>(0.0f);

			acClear();

			m_Selection_Bank.clear();

			m_SelectionIndex = 0;
			m_DecisionIndex = 0;

			m_Layer = 0;
			m_LayerPos = 0;

#ifndef OSI_MEM_APP
			ac_Push(m_LengthPosition, f_ref_CurrentPath + g_ref_Div + "m_LengthPosition");
			ac_Push(m_Layer, f_ref_CurrentPath + g_ref_Div + "m_Layer");
			ac_Push(m_LayerPos, f_ref_CurrentPath + g_ref_Div + "m_LayerPos");
			ac_Push(m_SelectionIndex, f_ref_CurrentPath + g_ref_Div + "m_SelectionIndex");
			ac_Push(m_DecisionIndex, f_ref_CurrentPath + g_ref_Div + "m_DecisionIndex");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPressOut", (bool(ecom_base::*)(void))&DecisionWheel::acPressOut);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPressIn", (bool(ecom_base::*)(void))&DecisionWheel::acPressIn);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClearHighLight", (bool(ecom_base::*)(void))&DecisionWheel::acClearHighLight);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&DecisionWheel::acClear);
#endif
			}

		~DecisionWheel()
			{
			acClear();

			m_SelectPosition = nullptr;
			m_position = nullptr;
		
			m_Selection_Bank.clear();
			
			m_SelectionIndex = 0;
			m_DecisionIndex = 0;

			m_Layer = 0;
			m_LayerPos = 0;
			}

		void acClear(void)
			{
			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_com.size(); f_XYZ++)
				{
				m_vec_Selection_com[f_XYZ]->acSelect(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_input.size(); f_XYZ++)
				{
				m_vec_Selection_input[f_XYZ]->acSelect(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_output.size(); f_XYZ++)
				{
				m_vec_Selection_output[f_XYZ]->acSelect(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_wire.size(); f_XYZ++)
				{
				m_vec_Selection_wire[f_XYZ]->acSelect(false);
				}

			m_vec_Selection_com.clear();
			m_vec_Selection_input.clear();
			m_vec_Selection_output.clear();
			m_vec_Selection_wire.clear();
			m_Selection_base = nullptr;
			}

		void acClearHighLight(void)
			{
			if(m_LayerPos == 0)
				{
				for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_com.size(); f_XYZ++)
					{
					m_vec_HighLighted_com[f_XYZ]->acHighLight(false);
					}

				m_vec_HighLighted_com.clear();
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_input.size(); f_XYZ++)
				{
				m_vec_HighLighted_input[f_XYZ]->acHighLight(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_output.size(); f_XYZ++)
				{
				m_vec_HighLighted_output[f_XYZ]->acHighLight(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_wire.size(); f_XYZ++)
				{
				m_vec_HighLighted_wire[f_XYZ]->acHighLight(false);
				}

			m_vec_HighLighted_input.clear();
			m_vec_HighLighted_output.clear();
			m_vec_HighLighted_wire.clear();
			}

		bool acSelectionGrow(BiVector f_Direction);

		bool acReposition(BiVector f_Direction, bool f_Click = false);

		std::shared_ptr<SelectionPreList> acMakeList(void);

		void acSelectBox(BiVector f_Min2D, BiVector f_Max2D)
			{
			acClearHighLight();

			std::vector<std::shared_ptr<Qcom>> f_vec_ComList_Within;

			for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_X > f_Min2D.m_X &&
					f_Com->m_position->m_Y > f_Min2D.m_Y &&
					f_Com->m_position->m_X < f_Max2D.m_X &&
					f_Com->m_position->m_Y < f_Max2D.m_Y)
					{
					m_vec_Selection_com.push_back(f_Com);

					m_position->m_X = f_Com->m_position->m_X;
					m_position->m_Y = f_Com->m_position->m_Y;

					f_Com->acHighLight(true);
					}
				}
			}

		void acPressIn(void)
			{
			m_LayerPos++;

			acClearHighLight();

			if(m_LayerPos >= 2)
				{
				acClear();

				m_LayerPos = 0;

				m_Layer++;

				if(m_vec_Selection_com.size() == 1)
					{
					std::shared_ptr<Qcom> f_com = m_vec_Selection_com[0];

					g_QcomManager->m_Qcom = f_com;
					}
				else
					{
					m_LayerPos = 1;

					m_Layer--;
					}
				}
			else
				{
				if(m_vec_Selection_com.size() == 1)
					{
					std::shared_ptr<Qcom> f_com = m_vec_Selection_com[0];

					if(f_com->m_vec_Input.size() > 0)
						{
						std::shared_ptr<QcomInput> f_Input = f_com->m_vec_Input[0];

						f_Input->acHighLight(true);

						m_vec_HighLighted_input.push_back(f_Input);

						m_position = f_Input->m_position;
						}
					else if(f_com->m_vec_Output.size() > 0)
						{
						std::shared_ptr<QcomOutput> f_Output = f_com->m_vec_Output[0];

						f_Output->acHighLight(true);

						m_vec_HighLighted_output.push_back(f_Output);

						m_position = f_Output->m_position;
						}
					}
				}
			}

		void acPressOut(void)
			{
			m_LayerPos--;

			if(m_LayerPos < 0)
				{
				acClear();

				m_LayerPos = 1;

				m_Layer--;

				if(m_Layer >= 0)
					{
					std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(g_QcomManager->m_Qcom->m_parentcomid);

					g_QcomManager->m_Qcom = f_com;
					}
				else if(m_Layer >= -1)
					{
					g_QcomManager->m_Qcom = g_QcomManager->mam_Qcom;
					}
				else if(m_Layer < -5)
					{
					m_Layer = -5;
					}
				}
			else
				{
				acClearHighLight();
				}
			}

		int m_LengthPosition;
		int m_Layer;
		int m_LayerPos;

		std::shared_ptr<BiVector> m_SelectPosition;
		std::shared_ptr<BiVector> m_position;

		std::vector<std::shared_ptr<SelectionSave>> m_Selection_Bank;

		int m_SelectionIndex;
		int m_DecisionIndex;

		std::shared_ptr<Cube::Qcom> m_Selection_base;
		std::vector<std::shared_ptr<Cube::Qcom>> m_vec_Selection_com;
		std::vector<std::shared_ptr<Cube::QcomInput>> m_vec_Selection_input;
		std::vector<std::shared_ptr<Cube::QcomOutput>> m_vec_Selection_output;
		std::vector<std::shared_ptr<Cube::QcomWire>> m_vec_Selection_wire;

		std::vector<std::shared_ptr<Cube::Qcom>> m_vec_HighLighted_com;
		std::vector<std::shared_ptr<Cube::QcomInput>> m_vec_HighLighted_input;
		std::vector<std::shared_ptr<Cube::QcomOutput>> m_vec_HighLighted_output;
		std::vector<std::shared_ptr<Cube::QcomWire>> m_vec_HighLighted_wire;
	};

class DecisionCom_QamInfo : public ecom_base
	{
	public:
		DecisionCom_QamInfo()
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "DecisionCom_QamInfo::DecisionCom_QamInfo";

#ifndef OSI_MEM_APP
			ac_Push(m_SourceOwner, f_ref_CurrentPath + g_ref_Div + "m_SourceOwner");
			ac_Push(m_OriginOwner, f_ref_CurrentPath + g_ref_Div + "m_OriginOwner");
			ac_Push(m_originalsourceqamid, f_ref_CurrentPath + g_ref_Div + "m_originalsourceqamid");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&DecisionWheel::acClear);
#endif

			acClear();
			};

		~DecisionCom_QamInfo() { acClear(); };

		void acClear(void)
			{
			m_originalsourceqamid = -1;
			m_OriginOwner.clear();
			m_SourceOwner.clear();
			};

		std::string m_SourceOwner;
		std::string m_OriginOwner;
		int m_originalsourceqamid;
	};

class DecisionCom : public ecom_base
	{
	public:
		DecisionCom()
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "DecisionCom::DecisionCom";

#ifndef OSI_MEM_APP
			ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
			ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
			ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
			ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
			ac_Push(m_Trial_Length, f_ref_CurrentPath + g_ref_Div + "m_Trial_Length");
			ac_Push(m_Mod_Type, f_ref_CurrentPath + g_ref_Div + "m_Mod_Type");
			ac_Push(m_Mod_Target, f_ref_CurrentPath + g_ref_Div + "m_Mod_Target");
			ac_Push(m_Mod_Name, f_ref_CurrentPath + g_ref_Div + "m_Mod_Name");
			ac_Push(m_Selected_Mod_Index, f_ref_CurrentPath + g_ref_Div + "m_Selected_Mod_Index");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&DecisionCom::ac_Save);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&DecisionCom::acClear);
#endif

			acClear();
			};

		DecisionCom(int f_ID, bool f_loadall = false);

		~DecisionCom()
			{
			acClear();
			};

		void acClear(void)
			{
			m_typed = 1;
			m_QamID = 0;
			m_QamLevel = 0;
			m_Mod_Type.clear();
			m_Mod_Target.clear();
			m_Mod_Name.clear();
			m_Selected_Mod_Index = 0;
			m_Trial_Length = -1;
			};

		void ac_Save(void);

		void acInsert_Mod_Target(int f_Type, std::string f_Mod_Target);
		void acSelect_Mod_Target(std::string f_Mod_Target, int f_Index = -5);
		void acComplete_Mod_Target(std::string f_Mod_Name, int f_Index = -5);
		void acComplete_Mod_Target(std::string f_Mod_Name, std::string f_Mod_Target);

		//cls type interop
		std::shared_ptr<BiDecisionQ> acGen_DecisionQ_fromDecisionCom(void);
		void acGen_DecisionCom_fromDecisionQ(std::shared_ptr<BiDecisionQ> f_DecisionQ);

		std::string acGet_Type(void);
		std::string acGet_Target(void);
		std::string acGet_Name(void);

		void acSet_Type(std::string f_Type_Buffer);
		void acSet_Target(std::string f_Target_Buffer);
		void acSet_Name(std::string f_Name_Buffer);

		std::vector<int> m_Mod_Type;
		std::vector<std::string> m_Mod_Target;
		std::vector<std::vector<std::string>> m_Mod_Name;
		int m_Selected_Mod_Index;

		int m_Trial_Length;

		int m_ID;
		int m_typed;
		int m_QamID;
		int m_QamLevel;
		std::shared_ptr<DecisionCom_QamInfo> m_QamInfo;
	};

class DecisionManager : public ecom_base
	{
	public:
		DecisionManager()
			{
			std::string f_ref_CurrentPath = "DecisionManager::DecisionManager";

#ifndef OSI_MEM_APP
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acFrame", (bool(ecom_base::*)(void))&DecisionManager::acFrame);
			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acLoad_ApplicationSpecificLegacy", (bool(ecom_base::*)(void))&DecisionManager::acLoad_ApplicationSpecificLegacy);
#endif

			acClear();

			m_vec_DecisionCom.clear();

			std::thread f_Thread(&DecisionManager::acFrame, this);

			f_Thread.detach();

			m_Frame = &f_Thread;
			};

		~DecisionManager()
			{
			m_vec_DecisionCom.clear();
			};

		void acClear(void)
			{
			m_vec_DecisionQ.clear();
			};

		std::string acLoadA_ContractToggle(void);
		std::string acLoadA_InsertCom(int f_CID);
		std::string acLoadA_ShareShop(std::string f_ModeString);
		std::string acLoadA_DeleteCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_CutCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_CopyCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_PasteCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_WireStandard(std::shared_ptr<Qcom> f_A, std::shared_ptr<Qcom> f_B, std::shared_ptr<QcomOutput> f_A_output, std::shared_ptr<QcomInput> f_B_input);
		std::string acLoadA_QamByID(int f_QamID, int f_Trial);
		std::string acLoadA_QamStabilise(void);

		void acLoad_ApplicationSpecificLegacy(void);
		void acLoad_DecisionCom(int f_QamID);
		
		void acFrame(void);

		std::thread* m_Frame;

		std::shared_ptr<DecisionWheel> m_Wheel;

		std::vector<std::shared_ptr<BiDecisionQ>> m_vec_DecisionQ;
		std::vector<std::shared_ptr<DecisionCom>> m_vec_DecisionCom;

		std::vector<std::shared_ptr<Qcom>> m_Paste_Buffer;

		std::vector<std::shared_ptr<BiDecisionA>> m_UnDo;
	};

extern std::vector<std::shared_ptr<DecisionManager>> g_vec_DecisionsManager;

class SelectionSave
{
public:
	SelectionSave()
		{
#if 0
		std::string f_ref_CurrentPath = "SelectionSave::SelectionSave";
#endif

		m_vec_Selection_com.clear();
		m_vec_Selection_input.clear();
		m_vec_Selection_output.clear();
		m_vec_Selection_wire.clear();

		std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_com.size(); f_Jet++)
			{
			m_vec_Selection_com.push_back(f_WHL->m_vec_Selection_com[f_Jet]);
			}

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_input.size(); f_Jet++)
			{
			m_vec_Selection_input.push_back(f_WHL->m_vec_Selection_input[f_Jet]);
			}

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_output.size(); f_Jet++)
			{
			m_vec_Selection_output.push_back(f_WHL->m_vec_Selection_output[f_Jet]);
			}

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_wire.size(); f_Jet++)
			{
			m_vec_Selection_wire.push_back(f_WHL->m_vec_Selection_wire[f_Jet]);
			}
		}

	~SelectionSave()
		{
		m_vec_Selection_com.clear();
		m_vec_Selection_input.clear();
		m_vec_Selection_output.clear();
		m_vec_Selection_wire.clear();
		}

	std::vector<std::shared_ptr<Cube::Qcom>> m_vec_Selection_com;
	std::vector<std::shared_ptr<Cube::QcomInput>> m_vec_Selection_input;
	std::vector<std::shared_ptr<Cube::QcomOutput>> m_vec_Selection_output;
	std::vector<std::shared_ptr<Cube::QcomWire>> m_vec_Selection_wire;
};

class BiCheckpointDescriptor : public ecom_base
{
public:
	BiCheckpointDescriptor(std::string f_FunctionLocation, std::string f_PositioninFunction)
		{
		std::string f_ref_CurrentPath = "BiCheckpointDescriptor::BiCheckpointDescriptor";

#ifndef OSI_MEM_APP
		ac_Push(m_FunctionLocation, f_ref_CurrentPath + g_ref_Div + "m_FunctionLocation");
		ac_Push(m_PositioninFunction, f_ref_CurrentPath + g_ref_Div + "m_PositioninFunction");
		ac_Push(m_Affinity, f_ref_CurrentPath + g_ref_Div + "m_Affinity");
		ac_Push(m_AdType, f_ref_CurrentPath + g_ref_Div + "m_AdType");

		make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&DecisionManager::acClear);
#endif

		acClear();

		m_FunctionLocation = f_FunctionLocation;
		m_PositioninFunction = f_PositioninFunction;
		};

	~BiCheckpointDescriptor() { acClear(); };

	void acClear(void)
		{
		m_FunctionLocation.clear();
		m_PositioninFunction.clear();
		m_AdType = -1;
		};

	bool acCheck(std::shared_ptr<BiCheckpointDescriptor> f_DescC)
		{
		if(m_FunctionLocation.compare(f_DescC->m_FunctionLocation) == 0)
			{
			if(m_PositioninFunction.compare(f_DescC->m_PositioninFunction) == 0)
				{
				m_Qcom->ac_Execute();

				return true;
				}
			}

		return false;
		}

	std::string m_FunctionLocation;
	std::string m_PositioninFunction;

	std::shared_ptr<Qcom> m_Qcom;

	bool m_Affinity;

	int m_AdType;
	std::shared_ptr<Qcom_eslfunction> m_AdinDecisionsManager;
};

#if 0
class BiProtocolExNode : public ecom_base
{
public:
	BiProtocolExNode() { acClear(); };
	~BiProtocolExNode() { acClear(); };

	void acClear(void)
		{
		m_NodeParent = nullptr;
		m_vec_NodeChildren.clear();
		m_PEXMAPIDX = -1;
		m_SwitchFinger = -1;
		m_Layer = 0;
		m_PrlCom = nullptr;
		};

	std::shared_ptr<BiProtocolExNode> acAddPEX(std::shared_ptr<Qcom> f_Com, int f_PEXMAPIDX, int f_SwitchFinger)
		{
		std::string f_ref_CurrentPath = "BiProtocolExNode::acAddPEX";

		ag_StatusLive(f_ref_CurrentPath, "f_Pex");

		std::shared_ptr<BiProtocolExNode> f_Pex = std::make_shared_reflect<BiProtocolExNode>();

		f_Pex->m_NodeParent = static_cast<std::shared_ptr<BiProtocolExNode>>(this);
		f_Pex->m_PrlCom = f_Com;
		f_Pex->m_PEXMAPIDX = f_PEXMAPIDX;
		f_Pex->m_SwitchFinger = f_SwitchFinger;

		m_vec_NodeChildren.push_back(f_Pex);

		return f_Pex;
		}

	bool acInstallPEX(std::shared_ptr<Qcom> f_Com, int f_PEXMAPIDX, int f_Layer, int f_SwitchFinger);

	bool acExecute(int f_PEXMAPIDX, int f_Layer, int f_SwitchFinger);

	std::shared_ptr<BiProtocolExNode> m_NodeParent;
	std::vector<std::shared_ptr<BiProtocolExNode>> m_vec_NodeChildren;
	std::shared_ptr<Qcom> m_PrlCom;

	int m_PEXMAPIDX;
	int m_SwitchFinger;
	int m_Layer;
};
#endif

};

#if 0
extern std::shared_ptr<BiProtocolExNode> g_MainNode;
extern std::shared_ptr<BiProtocolExNode> g_ExcomPexMain;
extern std::shared_ptr<BiProtocolExNode> g_InstallMain;
#endif

#endif