/*

VoxelGrid.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "qcom.h"
#include "Code/CLS/Target.h"
#include "qam.h"

#ifdef QUANTUM_MIX
#include "MathHelper.h"

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

#include "q-keydefinitions.h"

#if 0
#include "Render/FrustumG.h"
#endif

using namespace GVARS;
#endif

using namespace Cube;
using namespace std;

extern winrt::Windows::UI::Xaml::Controls::SwapChainPanel g_swapChainPanel;

namespace Cube
{
#define STRING(s) #s

std::shared_ptr<QcomManager> g_QcomManager;
std::shared_ptr<Qcom> g_PreCom = nullptr;

std::shared_mutex mutex_qcomdb;
std::shared_mutex g_Operatio_Muti;

bool g_PreComBool = false;
bool g_PreComLock = false;
int g_PreComBoughtIN = 0;
bool g_PreComInclude = false;
float g_BossLVLMin = 0.0000;

std::vector<std::shared_ptr<QcomOutput>> g_Wiring_Output;
std::vector<std::shared_ptr<QcomInput>> g_Wiring_Input;

std::vector<std::shared_ptr<Qcom>> g_Paste_Buffer;

int ag_Get_ClassType(std::string f_Packet)
{
	if((f_Packet.compare("Var") == 0) ||
		(f_Packet.compare("Variable") == 0))
		{
		return ctVariable;
		}
	else if(f_Packet.compare("CClass") == 0)
		{
		return ctCClass;
		}
	else if(f_Packet.compare("EClass") == 0)
		{
		return ctEClass;
		}
	else if((f_Packet.compare("Qcom") == 0) ||
			(f_Packet.compare("com") == 0) ||
			(f_Packet.compare("ecom") == 0))
		{
		return ctQcom;
		}
	else if((f_Packet.compare("Input") == 0) ||
			(f_Packet.compare("QcomInput") == 0) ||
			(f_Packet.compare("IN") == 0))
		{
		return ctQcomInput;
		}
	else if((f_Packet.compare("Output") == 0) ||
			(f_Packet.compare("QcomOutput") == 0) ||
			(f_Packet.compare("OUT") == 0))
		{
		return ctQcomOutput;
		}
	else if((f_Packet.compare("ComFunctionX") == 0) ||
			(f_Packet.compare("ComX") == 0) ||
			(f_Packet.compare("excom") == 0))
		{
		return ctComFunctionX;
		}
	else if(f_Packet.compare("Share") == 0)
		{
		return ctShare;
		}
	else if(f_Packet.compare("Element") == 0)
		{
		return ctElement;
		}

	return - 1;
}

std::string ag_ForwardProtocol(std::string f_InputProtocol)
{
	std::string f_ResultString = "";

	for(int f_I = 0; f_I < f_InputProtocol.length(); f_I++)
		{
		char f_c = f_InputProtocol.at(f_I);

		if(f_c == ':')
			{
			f_ResultString.push_back('¬'); // pack compiler colon as db tilda
			}
		else
			{
			f_ResultString.push_back(f_c);
			}
		}

	return f_ResultString;
}

std::string ag_ReadProtocol(std::string f_InputProtocol)
{
	std::string f_ResultString = "";

	for(int f_I = 0; f_I < f_InputProtocol.length(); f_I++)
		{
		char f_c = f_InputProtocol.at(f_I);

		if(f_c == '¬')
			{
			f_ResultString.push_back(':'); // recover compilers colon
			}
		else
			{
			f_ResultString.push_back(f_c);
			}
		}

	return f_ResultString;
}

GLuint QcomCompileShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *sourceArray[1] = { source.c_str() };
    glShaderSource(shader, 1, sourceArray, NULL);
    glCompileShader(shader);

    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if(compileResult == 0)
		{
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Shader compilation failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
#if 0
        throw Exception::CreateException(E_FAIL, ref new Platform::String(errorMessage.c_str()));
#endif
		}

    return shader;
}

GLuint QcomCompileProgram(const std::string &vsSource, const std::string &fsSource)
{
    GLuint program = glCreateProgram();

    if(program == 0)
		{
#if 0
        throw Exception::CreateException(E_FAIL, L"unRenderer Program creation failed");
#endif

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
		}

    GLuint vs = QcomCompileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = QcomCompileShader(GL_FRAGMENT_SHADER, fsSource);

    if(vs == 0 || fs == 0)
		{
        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(program);
        return 0;
		}

    glAttachShader(program, vs);
    glDeleteShader(vs);

    glAttachShader(program, fs);
    glDeleteShader(fs);

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if(linkStatus == 0)
		{
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Program link failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 

#if 0
        throw Exception::CreateException(E_FAIL, ref new Platform::String(errorMessage.c_str()));
#endif
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
		}

    return program;
}

Qcom::Qcom()
{
	std::string f_ref_CurrentPath = "Qcom::Qcom";

	//ag_StatusLive(f_ref_CurrentPath, "m_position");
	m_position = std::make_shared<Cube::BiVector>(0.0f);

	ac_Clear();

	m_Save = true;

	Initialize();

	m_ID = -1551;

	m_QamLevel = 0;

	m_BossLVLMin = g_BossLVLMin;

#ifndef OSI_MEM_APP
	ac_Push(m_rebuild, f_ref_CurrentPath + g_ref_Div + "m_rebuild");
	ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
	ac_Push(m_parentcomid, f_ref_CurrentPath + g_ref_Div + "m_parentcomid");
	ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
	ac_Push(m_Execute_Priority, f_ref_CurrentPath + g_ref_Div + "m_Execute_Priority");
	ac_Push(m_parentx, f_ref_CurrentPath + g_ref_Div + "m_parentx");
	ac_Push(m_parenty, f_ref_CurrentPath + g_ref_Div + "m_parenty");
	ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
	ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
	ac_Push(m_Selected, f_ref_CurrentPath + g_ref_Div + "m_Selected");
	ac_Push(m_HighLighted, f_ref_CurrentPath + g_ref_Div + "m_HighLighted");
	ac_Push(m_rseed, f_ref_CurrentPath + g_ref_Div + "m_rseed");
	ac_Push(m_seedinfo, f_ref_CurrentPath + g_ref_Div + "m_seedinfo");
	ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
	ac_Push(m_name, f_ref_CurrentPath + g_ref_Div + "m_name");
	ac_Push(m_overload, f_ref_CurrentPath + g_ref_Div + "m_overload");
	ac_Push(m_description, f_ref_CurrentPath + g_ref_Div + "m_description");
	ac_Push(m_vision, f_ref_CurrentPath + g_ref_Div + "m_vision");
	ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
	ac_Push(m_VoteScore, f_ref_CurrentPath + g_ref_Div + "m_VoteScore");
	ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
	ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
	ac_Push(m_Cost, f_ref_CurrentPath + g_ref_Div + "m_Cost");
	ac_Push(m_BossLVLMin, f_ref_CurrentPath + g_ref_Div + "m_BossLVLMin");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Clear", (void(ecom_base::*)(void))&Qcom::ac_Clear);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "Initialize", (void(ecom_base::*)(void))&Qcom::Initialize);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "GenerateBuffers", (void(ecom_base::*)(void))&Qcom::GenerateBuffers);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "Unload", (void(ecom_base::*)(void))&Qcom::Unload);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&Qcom::ac_Save);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Execute", (void(ecom_base::*)(void))&Qcom::ac_Execute);
#endif
}

Qcom::~Qcom()
{
	ac_Clear();

	Unload();
}

void Qcom::ac_Clear(void)
{
	m_position->m_X = 0.0f;
	m_position->m_Y = 0.0f;

	m_vec_Vertex.clear();
	m_vec_Normal.clear();
	m_vec_Color.clear();
	m_vec_Tex.clear();
	m_vec_Index.clear();

	m_ID = -1;
	m_parentcomid = -1;
	m_birthcomid = -1;

	m_ParentCom = nullptr;

	m_vec_Qcom.clear();
	m_vec_Execute_Chain.clear();

	m_vec_Input.clear();
	m_vec_Output.clear();
	m_vec_ComWire.clear();

	m_vec_GenScript.clear();
	m_vec_ESLFunction.clear();

	m_Frame_ESLFunction = nullptr;

	m_Execute_Priority = -1;

	m_genScript = nullptr;

	m_parentx = 0.0f;
	m_parenty = 0.0f;
	m_Save = false;
	m_typed = 0;

	m_QamLevel = 0;
	m_QamID = -1;
	m_Cost = 0.0f;
	m_BossLVLMin = 0.0f;

	m_Selected = false;
	m_HighLighted = false;

	m_Trial_Length = -1;

	m_VoteScore = 0;
}

#if 0
bool BiProtocolExNode::acExecute(int f_PEXMAPIDX, int f_Layer, int f_SwitchFinger)
{
	m_Layer = f_Layer;
	bool f_OneOn = false;

	if((f_PEXMAPIDX == m_PEXMAPIDX) && (f_SwitchFinger == m_SwitchFinger))
		{
		m_PrlCom->ac_Execute();

		f_OneOn = true;

#ifdef PEX_EXECUTE_AFFINITY
		return true;
#endif
		}
	//else layer ?
	f_Layer++;

	for(int f_PrlCount = 0; f_PrlCount < m_vec_NodeChildren.size(); f_PrlCount++)
		{
		std::shared_ptr<BiProtocolExNode> f_PEX = m_vec_NodeChildren[f_PrlCount];

		if(f_PEX->acExecute(f_PEXMAPIDX, f_Layer, f_SwitchFinger) == true)
			{
			f_OneOn = true;

#ifdef PEX_EXECUTE_AFFINITY
			return true;
#endif
			}
		}

	return f_OneOn;
}

bool BiProtocolExNode::acInstallPEX(std::shared_ptr<Qcom> f_Com, int f_PEXMAPIDX, int f_Layer, int f_SwitchFinger)
{
	m_Layer = f_Layer;
	bool f_OneOn = false;

	if((f_PEXMAPIDX == m_PEXMAPIDX) && (f_SwitchFinger == m_SwitchFinger))
		{
		acAddPEX(f_Com, f_PEXMAPIDX, f_SwitchFinger);

		f_OneOn = true;

#ifdef PEX_INSTALL_AFFINITY
		return true;
#endif
		}
	//else layer ?
	f_Layer++;

	for(int f_PrlCount = 0; f_PrlCount < m_vec_NodeChildren.size(); f_PrlCount++)
		{
		std::shared_ptr<BiProtocolExNode> f_PEX = m_vec_NodeChildren[f_PrlCount];

		if(f_PEX->acExecute(f_PEXMAPIDX, f_Layer, f_SwitchFinger) == true)
			{
			f_OneOn = true;

#ifdef PEX_INSTALL_AFFINITY
			return true;
#endif
			}
		}

	return f_OneOn;
}
#endif

void Qcom_genScript::ac_Clear(void)
{
	m_vec_InitLine.clear();
	m_vec_InitLineOrder.clear();
	m_vec_InitLineOrderID.clear();
	m_vec_InitLineOrdered.clear();
	m_vec_InitLineOrderedID.clear();
}

void Qcom_eslfunction::ac_Clear(void)
{
	m_vec_InitLine.clear();
	m_vec_InitLineOrder.clear();
	m_vec_InitLineOrderID.clear();
	m_vec_InitLineOrdered.clear();
	m_vec_InitLineOrderedID.clear();

	m_Contract = nullptr;
}

void Qcom::ac_Execute(void)
{
	//1... Compute Availability
	if(m_Trial_Length != -1)
		{
		time_t f_Time;
		time(&f_Time);

		if(f_Time > m_Trial_Length)
			{
			return;
			}
		}

	//2... Perform Com Purpose
	m_Frame_ESLFunction->ac_Execute();

	//3... 'ON' chain calculating the result
 	for(int f_XY = 0; f_XY < m_vec_Execute_Chain.size(); f_XY++)
		{
		std::shared_ptr<Qcom> f_com = m_vec_Execute_Chain[f_XY];

		f_com->ac_Execute();
		}
}

void Qcom_eslfunction::ac_Compile_Execute(void) //qcom compiling and pre-compiling
{
	//make new contract
	if(m_Contract == nullptr)
		{
		m_Contract = std::make_shared<ecoin::Contract>((std::shared_ptr<Qcom_eslfunction>)this);
		}

	m_Contract->m_Active = true;
}

void Qcom_eslfunction::ac_Execute(void)
{
	//[verify] compile state
	ac_Compile_Execute();

	//[LOCK]
	g_Operatio_Muti.lock();

	int f_SessionContractID = g_vec_OperatorScope_Contract.size();

	//add to globaql scope
	g_vec_OperatorScope_Contract.push_back(m_Contract);

	//[UNLOCK]
	g_Operatio_Muti.unlock();

	//start work
	m_Contract->acWork();

	//[LOCK]
	g_Operatio_Muti.lock();

	//remove from global scope
	for(int f_XY = 0; f_XY < g_vec_OperatorScope_Contract.size(); f_XY++)
		{
		std::shared_ptr<Contract> f_Contract = g_vec_OperatorScope_Contract[f_XY];

		if(f_Contract->m_ContractID == m_Contract->m_ContractID)
			{
			for(int f_Jet = f_XY; f_Jet < g_vec_OperatorScope_Contract.size() - 1; f_Jet++)
				{
				g_vec_OperatorScope_Contract[f_Jet] = g_vec_OperatorScope_Contract[f_Jet + 1];
				}

			g_vec_OperatorScope_Contract.pop_back();
			}
		}

	//[UNLOCK]
	g_Operatio_Muti.unlock();
}

// Initialize
void Qcom::Initialize()
{
	m_rebuild = true;
}

void Qcom::Unload(void)
{
#ifdef OGL_RENDER
	if(mVertexPositionBuffer)
		{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		}
	if(mVertexNormalBuffer)
		{
		glDeleteBuffers(1, &mVertexNormalBuffer);
		}
	if(mVertexColorBuffer)
		{
		glDeleteBuffers(1, &mVertexColorBuffer);
		}
	if(mVertexTexCoordBuffer)
		{
		glDeleteBuffers(1, &mVertexTexCoordBuffer);
		}
#endif
}

void Qcom::GenerateBuffers(void)
{
#ifdef OGL_RENDER
	const unsigned int f_VertNom = m_vec_Vertex.size() * 3;
	const unsigned int f_ColorNom = m_vec_Color.size() * 4;
	const unsigned int f_UVNom = m_vec_Tex.size() * 2;
	const unsigned int f_IndexNom = m_vec_Index.size() * 3;

	GLfloat* f_Position = new GLfloat[f_VertNom];
	GLfloat* f_Normal = new GLfloat[f_VertNom];
	GLfloat* f_Color = new GLfloat[f_ColorNom];
	GLfloat* f_Tex = new GLfloat[f_UVNom];
	short* f_Index = new short[f_IndexNom];

	for (unsigned int f_VertexCount = 0; f_VertexCount < m_vec_Vertex.size(); f_VertexCount++)
		{
		f_Position[(f_VertexCount * 3)] = m_vec_Vertex[f_VertexCount].m_X;
		f_Position[(f_VertexCount * 3) + 1] = m_vec_Vertex[f_VertexCount].m_Y;
		f_Position[(f_VertexCount * 3) + 2] = m_vec_Vertex[f_VertexCount].m_Z;
		}

	for (unsigned int f_NormalCount = 0; f_NormalCount < m_vec_Normal.size(); f_NormalCount++)
		{
		f_Normal[(f_NormalCount * 3)] = m_vec_Normal[f_NormalCount].m_X;
		f_Normal[(f_NormalCount * 3) + 1] = m_vec_Normal[f_NormalCount].m_Y;
		f_Normal[(f_NormalCount * 3) + 2] = m_vec_Normal[f_NormalCount].m_Z;
		}

	for (unsigned int f_ColorCount = 0; f_ColorCount < m_vec_Color.size(); f_ColorCount++)
		{
		f_Color[(f_ColorCount * 4)] = m_vec_Color[f_ColorCount].m_R;
		f_Color[(f_ColorCount * 4) + 1] = m_vec_Color[f_ColorCount].m_G;
		f_Color[(f_ColorCount * 4) + 2] = m_vec_Color[f_ColorCount].m_B;
		f_Color[(f_ColorCount * 4) + 3] = m_vec_Color[f_ColorCount].m_A;
		}

	for (unsigned int f_TexCount = 0; f_TexCount < m_vec_Tex.size(); f_TexCount++)
		{
		f_Tex[(f_TexCount * 2)] = m_vec_Tex[f_TexCount].m_U;
		f_Tex[(f_TexCount * 2) + 1] = m_vec_Tex[f_TexCount].m_V;
		}

	for (unsigned int f_IndexCount = 0; f_IndexCount < m_vec_Index.size(); f_IndexCount++)
		{
		f_Index[(f_IndexCount * 3)] = m_vec_Index[f_IndexCount].m_A;
		f_Index[(f_IndexCount * 3) + 1] = m_vec_Index[f_IndexCount].m_B;
		f_Index[(f_IndexCount * 3) + 2] = m_vec_Index[f_IndexCount].m_C;
		}

	glGenBuffers(1, &mVertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Position, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_IndexNom, f_Index, GL_STATIC_DRAW);
#endif
}

Qcom::Qcom(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "Qcom::Qcom";

	//ag_StatusLive(f_ref_CurrentPath, "m_position");
	m_position = std::make_shared<Cube::BiVector>(0.0f);

	ac_Clear();

	m_BossLVLMin = g_BossLVLMin;

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());

		m_owner = g_Schedular[2]->acEntry(f_ID)[1];
		m_name = g_Schedular[2]->acEntry(f_ID)[2];
		m_overload = g_Schedular[2]->acEntry(f_ID)[3];
		m_description = g_Schedular[2]->acEntry(f_ID)[4];
		m_vision = g_Schedular[2]->acEntry(f_ID)[5];
		m_NameGroup = g_Schedular[2]->acEntry(f_ID)[6];
		m_VoteScore = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
		m_seedinfo = g_Schedular[2]->acEntry(f_ID)[8];
		m_parentcomid = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
		m_parentx = atof(g_Schedular[2]->acEntry(f_ID)[10].c_str());
		m_parenty = atof(g_Schedular[2]->acEntry(f_ID)[11].c_str());
		m_birthcomid = atoi(g_Schedular[2]->acEntry(f_ID)[12].c_str());
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[13].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[14].c_str());
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[15].c_str());
		m_Cost = atoi(g_Schedular[2]->acEntry(f_ID)[16].c_str());
		}
	else
		{
		//Build the query
		char* f_comquery = new char[512];
		sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed, cost FROM com WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_comquery, false, false);
		delete[] f_comquery;

		m_ID = f_ID;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_owner = g_Schedular[2]->acEntry(0)[1];
			m_name = g_Schedular[2]->acEntry(0)[2];
			m_overload = g_Schedular[2]->acEntry(0)[3];
			m_description = g_Schedular[2]->acEntry(0)[4];
			m_vision = g_Schedular[2]->acEntry(0)[5];
			m_NameGroup = g_Schedular[2]->acEntry(0)[6];
			m_VoteScore = atoi(g_Schedular[2]->acEntry(0)[7].c_str());
			m_seedinfo = g_Schedular[2]->acEntry(0)[8];
			m_parentcomid = atoi(g_Schedular[2]->acEntry(0)[9].c_str());
			m_parentx = atof(g_Schedular[2]->acEntry(0)[10].c_str());
			m_parenty = atof(g_Schedular[2]->acEntry(0)[11].c_str());
			m_birthcomid = atoi(g_Schedular[2]->acEntry(0)[12].c_str());
			m_QamLevel = atoi(g_Schedular[2]->acEntry(0)[13].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(0)[14].c_str());
			m_typed = atoi(g_Schedular[2]->acEntry(0)[15].c_str());
			m_Cost = atof(g_Schedular[2]->acEntry(0)[16].c_str());
			}
		}

	m_Save = false;

#ifndef OSI_MEM_APP
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Clear", (void(ecom_base::*)(void))&Qcom::ac_Clear);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "Initialize", (void(ecom_base::*)(void))&Qcom::Initialize);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "GenerateBuffers", (void(ecom_base::*)(void))&Qcom::GenerateBuffers);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "Unload", (void(ecom_base::*)(void))&Qcom::Unload);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&Qcom::ac_Save);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Execute", (void(ecom_base::*)(void))&Qcom::ac_Execute);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelect", (void(ecom_base::*)(void))&Qcom::acSelect);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHighLight", (void(ecom_base::*)(void))&Qcom::acHighLight);

	ac_Push(m_rebuild, f_ref_CurrentPath + g_ref_Div + "m_rebuild");
	ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
	ac_Push(m_parentcomid, f_ref_CurrentPath + g_ref_Div + "m_parentcomid");
	ac_Push(m_birthcomid, f_ref_CurrentPath + g_ref_Div + "m_birthcomid");
	ac_Push(m_Execute_Priority, f_ref_CurrentPath + g_ref_Div + "m_Execute_Priority");
	ac_Push(m_parentx, f_ref_CurrentPath + g_ref_Div + "m_parentx");
	ac_Push(m_parenty, f_ref_CurrentPath + g_ref_Div + "m_parenty");
	ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
	ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
	ac_Push(m_Selected, f_ref_CurrentPath + g_ref_Div + "m_Selected");
	ac_Push(m_HighLighted, f_ref_CurrentPath + g_ref_Div + "m_HighLighted");
	ac_Push(m_rseed, f_ref_CurrentPath + g_ref_Div + "m_rseed");
	ac_Push(m_seedinfo, f_ref_CurrentPath + g_ref_Div + "m_seedinfo");
	ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
	ac_Push(m_name, f_ref_CurrentPath + g_ref_Div + "m_name");
	ac_Push(m_overload, f_ref_CurrentPath + g_ref_Div + "m_overload");
	ac_Push(m_description, f_ref_CurrentPath + g_ref_Div + "m_description");
	ac_Push(m_vision, f_ref_CurrentPath + g_ref_Div + "m_vision");
	ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
	ac_Push(m_VoteScore, f_ref_CurrentPath + g_ref_Div + "m_VoteScore");
	ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
	ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
	ac_Push(m_Cost, f_ref_CurrentPath + g_ref_Div + "m_Cost");
	ac_Push(m_BossLVLMin, f_ref_CurrentPath + g_ref_Div + "m_BossLVLMin");
#endif
}

WireCom::WireCom(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "WireCom::WireCom";

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_NameGroup = g_Schedular[2]->acEntry(f_ID)[1];
		m_ComWire = g_QcomManager->ac_Find_ComWire_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[2].c_str()));
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[3].c_str());
		m_X = atof(g_Schedular[2]->acEntry(f_ID)[4].c_str());
		m_Y = atof(g_Schedular[2]->acEntry(f_ID)[5].c_str());
		m_ParentCom = g_QcomManager->ac_Find_Com_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str()));
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
		}
	else
		{
		//Build the query
		char* f_comquery = new char[512];
		sprintf(f_comquery, "SELECT id, namegroup, comwireid, typed, vertx, verty, parentcomid, qamlevel, qamid FROM wirecom WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_comquery, false, false);
		delete[] f_comquery;

		m_ID = f_ID;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_NameGroup = g_Schedular[2]->acEntry(f_ID)[1];
			m_ComWire = g_QcomManager->ac_Find_ComWire_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[2].c_str()));
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[3].c_str());
			m_X = atof(g_Schedular[2]->acEntry(f_ID)[4].c_str());
			m_Y = atof(g_Schedular[2]->acEntry(f_ID)[5].c_str());
			m_ParentCom = g_QcomManager->ac_Find_Com_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str()));
			m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
			}
		}

	m_Save = false;

#ifndef OSI_MEM_APP
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&WireCom::ac_Save);

	ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
	ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");
	ac_Push(m_typed, f_ref_CurrentPath + g_ref_Div + "m_typed");
	ac_Push(m_NameGroup, f_ref_CurrentPath + g_ref_Div + "m_NameGroup");
	ac_Push(m_QamLevel, f_ref_CurrentPath + g_ref_Div + "m_QamLevel");
	ac_Push(m_QamID, f_ref_CurrentPath + g_ref_Div + "m_QamID");
	ac_Push(m_X, f_ref_CurrentPath + g_ref_Div + "m_X");
	ac_Push(m_Y, f_ref_CurrentPath + g_ref_Div + "m_Y");
	ac_Push(m_Time, f_ref_CurrentPath + g_ref_Div + "m_Time");
#endif
}

QcomInput::QcomInput(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "QcomInput::QcomInput";

	acClear();

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_owner = g_Schedular[2]->acEntry(f_ID)[1];
		m_name = g_Schedular[2]->acEntry(f_ID)[2];
		m_description = g_Schedular[2]->acEntry(f_ID)[3];
		m_vision = g_Schedular[2]->acEntry(f_ID)[4];
		m_InputfunctionID = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
		m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
		m_ICOID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
		}
	else
		{
		//Build the query
		char* f_inputquery = new char[512];
		sprintf(f_inputquery, "SELECT id, owner, name, description, vision, inputfunctionid, comid, icoid, qamlevel, qamid, typed FROM cominput WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_inputquery, false, false);
		delete[] f_inputquery;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_owner = g_Schedular[2]->acEntry(f_ID)[1];
			m_name = g_Schedular[2]->acEntry(f_ID)[2];
			m_description = g_Schedular[2]->acEntry(f_ID)[3];
			m_vision = g_Schedular[2]->acEntry(f_ID)[4];
			m_InputfunctionID = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
			m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
			m_ICOID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
			m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
			}
		}

#ifndef OSI_MEM_APP
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&QcomInput::ac_Save);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelect", (void(ecom_base::*)(void))&QcomInput::acSelect);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHighLight", (void(ecom_base::*)(void))&QcomInput::acHighLight);

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

QcomControl::QcomControl(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "QcomControl::QcomControl";

	acClear();

	//ag_StatusLive(f_ref_CurrentPath, "m_position");
	m_position = std::make_shared<Cube::BiVector>(0.0f);

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_owner = g_Schedular[2]->acEntry(f_ID)[1];
		m_name = g_Schedular[2]->acEntry(f_ID)[2];
		m_description = g_Schedular[2]->acEntry(f_ID)[3];
		m_vision = g_Schedular[2]->acEntry(f_ID)[4];
		m_ControlfunctionID = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
		m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
		m_ICOID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
		}
	else
		{
		//Build the query
		char* f_functionquery = new char[512];
		sprintf(f_functionquery, "SELECT id, owner, name, description, vision, controlfunctionid, comid, icoid, qamlevel, qamid, typed FROM eslfunction WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_functionquery, false, false);
		delete[] f_functionquery;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_owner = g_Schedular[2]->acEntry(f_ID)[1];
			m_name = g_Schedular[2]->acEntry(f_ID)[2];
			m_description = g_Schedular[2]->acEntry(f_ID)[3];
			m_vision = g_Schedular[2]->acEntry(f_ID)[4];
			m_ControlfunctionID = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
			m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
			m_ICOID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
			m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
			}
		}

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
}

QcomOutput::QcomOutput(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "QcomOutput::QcomOutput";

	acClear();

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_owner = g_Schedular[2]->acEntry(f_ID)[1];
		m_name = g_Schedular[2]->acEntry(f_ID)[2];
		m_description = g_Schedular[2]->acEntry(f_ID)[3];
		m_vision = g_Schedular[2]->acEntry(f_ID)[4];
		m_OutputfunctionID = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
		m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
		m_ICOID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
		}
	else
		{
		//Build the query
		char* f_functionquery = new char[512];
		sprintf(f_functionquery, "SELECT id, owner, name, description, vision, outputfunctionid, comid, icoid, qamlevel, qamid, typed FROM eslfunction WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_functionquery, false, false);
		delete[] f_functionquery;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_owner = g_Schedular[2]->acEntry(f_ID)[1];
			m_name = g_Schedular[2]->acEntry(f_ID)[2];
			m_description = g_Schedular[2]->acEntry(f_ID)[3];
			m_vision = g_Schedular[2]->acEntry(f_ID)[4];
			m_OutputfunctionID = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
			m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
			m_ICOID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
			m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
			}
		}

#ifndef OSI_MEM_APP
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (void(ecom_base::*)(void))&QcomOutput::ac_Save);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelect", (void(ecom_base::*)(void))&QcomOutput::acSelect);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHighLight", (void(ecom_base::*)(void))&QcomOutput::acHighLight);

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

#pragma message("WARNING loading input output mysql without super namegroups")

Qcom_genScript::Qcom_genScript(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "Qcom_genScript::Qcom_genScript";

	ac_Clear();

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_owner = g_Schedular[2]->acEntry(f_ID)[1];
		m_name = g_Schedular[2]->acEntry(f_ID)[2];
		m_description = g_Schedular[2]->acEntry(f_ID)[3];
		m_vision = g_Schedular[2]->acEntry(f_ID)[4];
		m_seedinfo = g_Schedular[2]->acEntry(f_ID)[5];
		m_NameGroup = g_Schedular[2]->acEntry(f_ID)[6];
		m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
		}
	else
		{
		//Build the query
		char* f_initquery = new char[512];
		sprintf(f_initquery, "SELECT id, owner, name, description, vision, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_initquery, false, false);
		delete[] f_initquery;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_owner = g_Schedular[2]->acEntry(f_ID)[1];
			m_name = g_Schedular[2]->acEntry(f_ID)[2];
			m_description = g_Schedular[2]->acEntry(f_ID)[3];
			m_vision = g_Schedular[2]->acEntry(f_ID)[4];
			m_seedinfo = g_Schedular[2]->acEntry(f_ID)[5];
			m_NameGroup = g_Schedular[2]->acEntry(f_ID)[6];
			m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
			m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
			}
		}

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
#endif
}

Qcom_eslfunction::Qcom_eslfunction(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "Qcom_eslfunction::Qcom_eslfunction";

	ac_Clear();

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_owner = g_Schedular[2]->acEntry(f_ID)[1];
		m_name = g_Schedular[2]->acEntry(f_ID)[2];
		m_description = g_Schedular[2]->acEntry(f_ID)[3];
		m_vision = g_Schedular[2]->acEntry(f_ID)[4];
		m_TargetString = g_Schedular[2]->acEntry(f_ID)[5];
		m_seedinfo = g_Schedular[2]->acEntry(f_ID)[6];
		m_NameGroup = g_Schedular[2]->acEntry(f_ID)[7];
		m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[11].c_str());
		}
	else
		{
		//Build the query
		char* f_functionquery = new char[512];
		sprintf(f_functionquery, "SELECT id, owner, name, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM eslfunction WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_functionquery, false, false);
		delete[] f_functionquery;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_owner = g_Schedular[2]->acEntry(f_ID)[1];
			m_name = g_Schedular[2]->acEntry(f_ID)[2];
			m_description = g_Schedular[2]->acEntry(f_ID)[3];
			m_vision = g_Schedular[2]->acEntry(f_ID)[4];
			m_TargetString = g_Schedular[2]->acEntry(f_ID)[5];
			m_seedinfo = g_Schedular[2]->acEntry(f_ID)[6];
			m_NameGroup = g_Schedular[2]->acEntry(f_ID)[7];
			m_ComID = atoi(g_Schedular[2]->acEntry(f_ID)[8].c_str());
			m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[9].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[10].c_str());
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[11].c_str());
			}
		}

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
}

QcomWire::QcomWire(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "QcomWire::QcomWire";

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_NameGroup = g_Schedular[2]->acEntry(f_ID)[1];
		m_Output = g_QcomManager->ac_Find_ComOutput_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[2].c_str()));
		m_OutputCom = g_QcomManager->ac_Find_Com_ByID(m_Output->m_ComID);
		m_Input = g_QcomManager->ac_Find_ComInput_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[3].c_str()));
		m_InputCom = g_QcomManager->ac_Find_Com_ByID(m_Output->m_ComID);
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[4].c_str());
		m_parentcomid = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
		m_ParentCom = g_QcomManager->ac_Find_Com_ByID(m_parentcomid);
		m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
		}
	else
		{
		//Build the query
		char* f_comwirequery = new char[512];
		sprintf(f_comwirequery, "SELECT id, owner, namegroup, outputid, inputid, typed, parentcomid, qamlevel, qamid FROM comwire WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_comwirequery, false, false);
		delete[] f_comwirequery;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_NameGroup = g_Schedular[2]->acEntry(f_ID)[1];
			m_Output = g_QcomManager->ac_Find_ComOutput_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[2].c_str()));
			m_OutputCom = g_QcomManager->ac_Find_Com_ByID(m_Output->m_ComID);
			m_Input = g_QcomManager->ac_Find_ComInput_ByID(atoi(g_Schedular[2]->acEntry(f_ID)[3].c_str()));
			m_InputCom = g_QcomManager->ac_Find_Com_ByID(m_Output->m_ComID);
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[4].c_str());
			m_parentcomid = atoi(g_Schedular[2]->acEntry(f_ID)[5].c_str());
			m_ParentCom = g_QcomManager->ac_Find_Com_ByID(m_parentcomid);
			m_QamLevel = atoi(g_Schedular[2]->acEntry(f_ID)[6].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[7].c_str());
			}
		}

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

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_IsOK", (void(ecom_base::*)(void))&QcomWire::ac_Save);
#endif
}

DecisionCom::DecisionCom(int f_ID, bool f_loadall)
{
	std::string f_ref_CurrentPath = "DecisionCom::DecisionCom";

	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
		m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[1].c_str());
		m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[2].c_str());

		ag_StatusLive(f_ref_CurrentPath, "m_QamInfo");
		m_QamInfo = std::make_shared_reflect<DecisionCom_QamInfo>();

		m_QamInfo->m_originalsourceqamid = atoi(g_Schedular[2]->acEntry(f_ID)[3].c_str());
		m_QamInfo->m_SourceOwner = g_Schedular[2]->acEntry(f_ID)[4];
		m_QamInfo->m_OriginOwner = g_Schedular[2]->acEntry(f_ID)[5];
		acSet_Type(g_Schedular[2]->acEntry(f_ID)[6]);
		acSet_Target(g_Schedular[2]->acEntry(f_ID)[7]);
		acSet_Name(g_Schedular[2]->acEntry(f_ID)[8]);
		}
	else
		{
		//Build the query
		char* f_comquery = new char[512];
		sprintf(f_comquery, "SELECT typed, qamid, originalsourceqamid, sourceowner, originowner, modtype, modtarget, modname FROM decisioncom WHERE id = %i", f_ID);
		g_SafeL[2]->acSelectCommand(f_comquery, false, false);
		delete[] f_comquery;

		if(g_Schedular[2]->acEntrySize() > 0)
			{
			m_ID = f_ID;
			m_typed = atoi(g_Schedular[2]->acEntry(f_ID)[0].c_str());
			m_QamID = atoi(g_Schedular[2]->acEntry(f_ID)[1].c_str());

			ag_StatusLive(f_ref_CurrentPath, "m_QamInfo");
			m_QamInfo = std::make_shared_reflect<DecisionCom_QamInfo>();

			m_QamInfo->m_originalsourceqamid = atoi(g_Schedular[2]->acEntry(f_ID)[2].c_str());
			m_QamInfo->m_SourceOwner = g_Schedular[2]->acEntry(f_ID)[3];
			m_QamInfo->m_OriginOwner = g_Schedular[2]->acEntry(f_ID)[4];
			acSet_Type(g_Schedular[2]->acEntry(f_ID)[5]);
			acSet_Target(g_Schedular[2]->acEntry(f_ID)[6]);
			acSet_Name(g_Schedular[2]->acEntry(f_ID)[7]);
			}
		}

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
}

std::shared_ptr<BiDecisionQ> DecisionCom::acGen_DecisionQ_fromDecisionCom(void)
{
	std::string f_ref_CurrentPath = "DecisionCom::acGen_DecisionQ_fromDecisionCom";

	ag_StatusLive(f_ref_CurrentPath, "m_QamInfo");
	std::shared_ptr<BiDecisionQ> f_Result_Q = make_shared<BiDecisionQ>(atoi(m_Mod_Name[0][0].c_str()), atoi(m_Mod_Name[0][1].c_str()), atoi(m_Mod_Name[0][2].c_str()));

	for(int f_XYZ = 1; f_XYZ < m_Mod_Target.size(); f_XYZ++)
		{
		std::string f_TargetName = m_Mod_Target[f_XYZ];

		ag_StatusLive(f_ref_CurrentPath, "f_Result_DSO");
		std::shared_ptr<BiDecisionOverride> f_Result_DSO = make_shared<BiDecisionOverride>(atoi(m_Mod_Name[f_XYZ][0].c_str()), atoi(m_Mod_Name[f_XYZ][1].c_str()), atoi(m_Mod_Name[f_XYZ][2].c_str()));

		f_Result_Q->m_vec_DecisionOverride.push_back(f_Result_DSO);
		}

	for(int f_Jet = 0; f_Jet < m_Mod_Target.size(); f_Jet += 2)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_Result_Q->acAdd_Answer");
		f_Result_Q->acAdd_Answer(std::make_shared<BiDecisionA>(m_Mod_Target[f_Jet], m_Mod_Target[f_Jet + 1], m_Trial_Length));
		}

	return f_Result_Q;
}

void Qcom::acSelect(bool f_Selection)
{
	m_Selected = f_Selection;
}

void QcomInput::acSelect(bool f_Selection)
{
	m_Selected = f_Selection;
}

void QcomOutput::acSelect(bool f_Selection)
{
	m_Selected = f_Selection;
}

void QcomWire::acSelect(bool f_Selection)
{
	m_Selected = f_Selection;
}

void QcomManager::acSelectNone(void)
{
	for(int f_Jet = 0; f_Jet < m_vec_Qcom.size(); f_Jet++)
		{
		m_vec_Qcom[f_Jet]->acSelect(false);
		}
}

void Qcom::acHighLight(bool f_HighLighted)
{
	m_HighLighted = f_HighLighted;
}

void QcomInput::acHighLight(bool f_HighLighted)
{
	m_HighLighted = f_HighLighted;
}

void QcomOutput::acHighLight(bool f_HighLighted)
{
	m_HighLighted = f_HighLighted;
}

void QcomWire::acHighLight(bool f_HighLighted)
{
	m_HighLighted = f_HighLighted;
}

void QcomManager::acHighLightNone(void)
{
	for(int f_Jet = 0; f_Jet < m_vec_Qcom.size(); f_Jet++)
		{
		m_vec_Qcom[f_Jet]->acHighLight(false);
		}
}

void BiDecisionQ::acSelectOverrides(bool f_Clear)
{
	if(f_Clear == true)
		{
		g_QcomManager->acSelectNone();
		}

	if(acCheck_Show() == true)
		{
		g_QcomManager->ac_Find_Com_ByID(m_Existence_ID)->m_Selected = true;

		for(int f_Jet = 0; f_Jet < m_vec_DecisionOverride.size(); f_Jet++)
			{
			g_QcomManager->ac_Find_Com_ByID(m_vec_DecisionOverride[f_Jet]->m_Existence_ID)->m_Selected = true;
			}
		}
}

void DecisionCom::acGen_DecisionCom_fromDecisionQ(std::shared_ptr<BiDecisionQ> f_DecisionQ)
{
	if(m_typed == 1)
		{
		std::string f_NameTextB = "";
		std::string f_NameText = "";

		for(int f_XYZ = 0; f_XYZ < f_DecisionQ->m_vec_DecisionOverride.size(); f_XYZ++)
			{
			std::shared_ptr<BiDecisionOverride> f_Deccom = f_DecisionQ->m_vec_DecisionOverride[f_XYZ];

			char* f_Char = ag_ClearChar(1024);

			sprintf(f_Char, "%i.%i.%i:", f_Deccom->m_PipeChan, f_Deccom->m_Existence_ID, f_Deccom->m_Existence_ShareID);

			f_NameText += f_Char;
			}

		char* f_Char = ag_ClearChar(1024);

		sprintf(f_Char, "%i.%i.%i:", f_DecisionQ->m_PipeChan, f_DecisionQ->m_Existence_ID, f_DecisionQ->m_Existence_ShareID);

		f_NameTextB += f_Char;
		f_NameTextB += f_NameText;

		//set name
		acSet_Name(f_NameTextB);

		std::string f_TargetTextC = "";

		for(int f_XYZ = 0; f_XYZ < f_DecisionQ->m_vec_DecisionA.size(); f_XYZ++)
			{
			std::shared_ptr<BiDecisionA> f_DecisionA = f_DecisionQ->m_vec_DecisionA[f_XYZ];

			f_TargetTextC += f_DecisionA->m_TitleText;
			f_TargetTextC += f_DecisionA->m_ObjectNameOverride;
			}

		//set target
		acSet_Target(f_TargetTextC);

		acSet_Type("1.");
		}
}

void DecisionCom::ac_Save(void)
{
	std::string f_ref_CurrentPath = "DecisionCom::ac_Save";

	if(m_ID == -1551)
		{
		char* f_decisioncomfield[8];
		char* f_decisioncomvalue[8];

		for(int f_Count = 0; f_Count < 8; f_Count++)
			{
			f_decisioncomfield[f_Count] = (char*)malloc(sizeof(char) * 2512);
			f_decisioncomvalue[f_Count] = (char*)malloc(sizeof(char) * 2512);
			}

		sprintf(f_decisioncomfield[0], "typed");
		sprintf(f_decisioncomfield[1], "qamid");
		sprintf(f_decisioncomfield[2], "originalsourceqamid");
		sprintf(f_decisioncomfield[3], "sourceowner");
		sprintf(f_decisioncomfield[4], "originowner");
		sprintf(f_decisioncomfield[5], "modtype");
		sprintf(f_decisioncomfield[6], "modtarget");
		sprintf(f_decisioncomfield[7], "modname");

		sprintf(f_decisioncomvalue[0], "%i", m_typed);
		sprintf(f_decisioncomvalue[1], "%i", m_QamID);
		sprintf(f_decisioncomvalue[2], "%i", m_QamInfo->m_originalsourceqamid);
		sprintf(f_decisioncomvalue[3], "%s", m_QamInfo->m_SourceOwner.c_str());
		sprintf(f_decisioncomvalue[4], "%s", m_QamInfo->m_OriginOwner.c_str());
		sprintf(f_decisioncomvalue[5], "%s", acGet_Type().c_str());
		sprintf(f_decisioncomvalue[6], "%s", acGet_Target().c_str());
		sprintf(f_decisioncomvalue[7], "%s", acGet_Name().c_str());

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("decisioncom", (const char **)f_decisioncomfield, (const char **)f_decisioncomvalue, 8, false, false);

		mutex_qcomdb.unlock();
		}
	else
		{
		char* f_decisioncomwhere[1];
		char* f_decisioncomfield[8];
		char* f_decisioncomvalue[8];

		for(int f_Count = 0; f_Count < 8; f_Count++)
			{
			f_decisioncomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_decisioncomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		f_decisioncomwhere[0] = (char*)malloc(sizeof(char) * 512);

		sprintf(f_decisioncomfield[0], "typed");
		sprintf(f_decisioncomfield[1], "qamid");
		sprintf(f_decisioncomfield[2], "originalsourceqamid");
		sprintf(f_decisioncomfield[3], "sourceowner");
		sprintf(f_decisioncomfield[4], "originowner");
		sprintf(f_decisioncomfield[5], "modtype");
		sprintf(f_decisioncomfield[6], "modtarget");
		sprintf(f_decisioncomfield[7], "modname");

		sprintf(f_decisioncomvalue[0], "%i", m_typed);
		sprintf(f_decisioncomvalue[1], "%i", m_QamID);
		sprintf(f_decisioncomvalue[2], "%i", m_QamInfo->m_originalsourceqamid);
		sprintf(f_decisioncomvalue[3], "%s", m_QamInfo->m_SourceOwner.c_str());
		sprintf(f_decisioncomvalue[4], "%s", m_QamInfo->m_OriginOwner.c_str());
		sprintf(f_decisioncomvalue[5], "%s", acGet_Type().c_str());
		sprintf(f_decisioncomvalue[6], "%s", acGet_Target().c_str());
		sprintf(f_decisioncomvalue[7], "%s", acGet_Name().c_str());

		sprintf(f_decisioncomwhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("decisioncom", (const char **)f_decisioncomfield, (const char **)f_decisioncomvalue, 8, f_decisioncomwhere[0], false, false);

		mutex_qcomdb.unlock();
		}
}

void WireCom::ac_Save(void)
{
	std::string f_ref_CurrentPath = "DecisionCom::ac_Save";

	if(m_ID == -1551)
		{
		char* f_wirecomfield[8];
		char* f_wirecomvalue[8];

		for(int f_Count = 0; f_Count < 8; f_Count++)
			{
			f_wirecomfield[f_Count] = (char*)malloc(sizeof(char) * 2512);
			f_wirecomvalue[f_Count] = (char*)malloc(sizeof(char) * 2512);
			}

		sprintf(f_wirecomfield[0], "namegroup");
		sprintf(f_wirecomfield[1], "comwireid");
		sprintf(f_wirecomfield[2], "typed");
		sprintf(f_wirecomfield[3], "vertx");
		sprintf(f_wirecomfield[4], "verty");
		sprintf(f_wirecomfield[5], "parentcomid");
		sprintf(f_wirecomfield[6], "qamid");
		sprintf(f_wirecomfield[7], "qamlevel");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_wirecomvalue[0], "%s", m_NameGroup.c_str());
		sprintf(f_wirecomvalue[1], "%i", m_ComWire->m_ID);
		sprintf(f_wirecomvalue[2], "%i", m_typed);
		sprintf(f_wirecomvalue[3], "%f", m_X);
		sprintf(f_wirecomvalue[4], "%f", m_Y);
		sprintf(f_wirecomvalue[5], "%i", m_ParentCom->m_ID);
		sprintf(f_wirecomvalue[6], "%i", m_QamID);
		sprintf(f_wirecomvalue[7], "%i", m_QamLevel);

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("wirecom", (const char **)f_wirecomfield, (const char **)f_wirecomvalue, 6, false, false);

		mutex_qcomdb.unlock();
		}
	else
		{
		char* f_wirecomwhere[1];
		char* f_wirecomfield[8];
		char* f_wirecomvalue[8];

		for(int f_Count = 0; f_Count < 7; f_Count++)
			{
			f_wirecomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_wirecomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		f_wirecomwhere[0] = (char*)malloc(sizeof(char) * 512);

		sprintf(f_wirecomfield[0], "namegroup");
		sprintf(f_wirecomfield[1], "typed");
		sprintf(f_wirecomfield[2], "sourceowner");
		sprintf(f_wirecomfield[3], "originowner");
		sprintf(f_wirecomfield[4], "modtype");
		sprintf(f_wirecomfield[5], "modtarget");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_wirecomvalue[0], "%s", m_NameGroup.c_str());
		sprintf(f_wirecomvalue[1], "%i", m_typed);
		sprintf(f_wirecomvalue[2], "%f", m_X);
		sprintf(f_wirecomvalue[3], "%f", m_Y);
		sprintf(f_wirecomvalue[4], "%i", m_QamLevel);
		sprintf(f_wirecomvalue[5], "%i", m_QamID);

		sprintf(f_wirecomwhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("wirecom", (const char **)f_wirecomfield, (const char **)f_wirecomvalue, 6, f_wirecomwhere[0], false, false);

		mutex_qcomdb.unlock();
		}
}

void QcomWire::ac_Save(void)
{
	std::string f_ref_CurrentPath = "DecisionCom::ac_Save";

	if(m_ID == -1551)
		{
		char* f_comwirefield[8];
		char* f_comwirevalue[8];

		for(int f_Count = 0; f_Count < 8; f_Count++)
			{
			f_comwirefield[f_Count] = (char*)malloc(sizeof(char) * 2512);
			f_comwirevalue[f_Count] = (char*)malloc(sizeof(char) * 2512);
			}

		sprintf(f_comwirefield[0], "namegroup");
		sprintf(f_comwirefield[1], "outputid");
		sprintf(f_comwirefield[2], "inputid");
		sprintf(f_comwirefield[3], "typed");
		sprintf(f_comwirefield[4], "parentcomid");
		sprintf(f_comwirefield[5], "qamlevel");
		sprintf(f_comwirefield[6], "qamid");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_comwirevalue[0], "%s", m_NameGroup.c_str());
		sprintf(f_comwirevalue[1], "%i", m_Output->m_ID);
		sprintf(f_comwirevalue[2], "%i", m_Input->m_ID);
		sprintf(f_comwirevalue[3], "%i", m_typed);
		sprintf(f_comwirevalue[4], "%i", m_ParentCom->m_ID);
		sprintf(f_comwirevalue[5], "%i", m_QamLevel);
		sprintf(f_comwirevalue[6], "%i", m_QamID);

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("comwire", (const char **)f_comwirefield, (const char **)f_comwirevalue, 7, false, false);

		mutex_qcomdb.unlock();
		}
	else
		{
		char* f_comwirewhere[1];
		char* f_comwirefield[8];
		char* f_comwirevalue[8];

		for(int f_Count = 0; f_Count < 7; f_Count++)
			{
			f_comwirefield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_comwirevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		f_comwirewhere[0] = (char*)malloc(sizeof(char) * 512);

		sprintf(f_comwirefield[0], "namegroup");
		sprintf(f_comwirefield[1], "outputid");
		sprintf(f_comwirefield[2], "inputid");
		sprintf(f_comwirefield[3], "typed");
		sprintf(f_comwirefield[4], "parentcomid");
		sprintf(f_comwirefield[5], "qamlevel");
		sprintf(f_comwirefield[6], "qamid");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_comwirevalue[0], "%s", m_NameGroup.c_str());
		sprintf(f_comwirevalue[1], "%i", m_Output->m_ID);
		sprintf(f_comwirevalue[2], "%i", m_Input->m_ID);
		sprintf(f_comwirevalue[3], "%i", m_typed);
		sprintf(f_comwirevalue[4], "%i", m_ParentCom->m_ID);
		sprintf(f_comwirevalue[5], "%i", m_QamLevel);
		sprintf(f_comwirevalue[6], "%i", m_QamID);

		sprintf(f_comwirewhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("comwire", (const char **)f_comwirefield, (const char **)f_comwirevalue, 6, f_comwirewhere[0], false, false);

		mutex_qcomdb.unlock();
		}
}

void QcomInput::ac_Save(void)
{
	std::string f_ref_CurrentPath = "QcomInput::ac_Save";

	if(m_ID == -1551)
		{
		char* f_inputcomfield[10];
		char* f_inputcomvalue[10];

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_inputcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_inputcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_inputcomfield[0], "owner");
		sprintf(f_inputcomfield[1], "name");
		sprintf(f_inputcomfield[2], "description");
		sprintf(f_inputcomfield[3], "vision");
		sprintf(f_inputcomfield[4], "inputfunctionid");
		sprintf(f_inputcomfield[5], "comid");
		sprintf(f_inputcomfield[6], "icoid");
		sprintf(f_inputcomfield[7], "qamlevel");
		sprintf(f_inputcomfield[8], "qamid");
		sprintf(f_inputcomfield[9], "typed");

		sprintf(f_inputcomvalue[0], "%s", m_owner.c_str());
		sprintf(f_inputcomvalue[1], "%s", m_name.c_str());
		sprintf(f_inputcomvalue[2], "%s", m_description.c_str());
		sprintf(f_inputcomvalue[3], "%s", m_vision.c_str());
		sprintf(f_inputcomvalue[4], "%i", m_InputfunctionID);
		sprintf(f_inputcomvalue[5], "%i", m_ComID);
		sprintf(f_inputcomvalue[6], "%i", m_ICOID);
		sprintf(f_inputcomvalue[7], "%i", m_QamLevel);
		sprintf(f_inputcomvalue[8], "%i", m_QamID);
		sprintf(f_inputcomvalue[9], "%i", m_typed);

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("cominput", (const char **)f_inputcomfield, (const char **)f_inputcomvalue, 10, false, false);

		mutex_qcomdb.unlock();
		}
	else
		{
		char* f_inputcomwhere[1];
		char* f_inputcomfield[10];
		char* f_inputcomvalue[10];

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_inputcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_inputcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		f_inputcomwhere[0] = (char*)malloc(sizeof(char) * 512);

		sprintf(f_inputcomfield[0], "owner");
		sprintf(f_inputcomfield[1], "name");
		sprintf(f_inputcomfield[2], "description");
		sprintf(f_inputcomfield[3], "vision");
		sprintf(f_inputcomfield[4], "inputfunctionid");
		sprintf(f_inputcomfield[5], "comid");
		sprintf(f_inputcomfield[6], "icoid");
		sprintf(f_inputcomfield[7], "qamlevel");
		sprintf(f_inputcomfield[8], "qamid");
		sprintf(f_inputcomfield[9], "typed");

		sprintf(f_inputcomvalue[0], "%s", m_owner.c_str());
		sprintf(f_inputcomvalue[1], "%s", m_name.c_str());
		sprintf(f_inputcomvalue[2], "%s", m_description.c_str());
		sprintf(f_inputcomvalue[3], "%s", m_vision.c_str());
		sprintf(f_inputcomvalue[4], "%i", m_InputfunctionID);
		sprintf(f_inputcomvalue[5], "%i", m_ComID);
		sprintf(f_inputcomvalue[6], "%i", m_ICOID);
		sprintf(f_inputcomvalue[7], "%i", m_QamLevel);
		sprintf(f_inputcomvalue[8], "%i", m_QamID);
		sprintf(f_inputcomvalue[9], "%i", m_typed);

		sprintf(f_inputcomwhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("cominput", (const char **)f_inputcomfield, (const char **)f_inputcomvalue, 10, f_inputcomwhere[0], false, false);

		mutex_qcomdb.unlock();
		}

	if(m_InputFunction != nullptr)
		{
		m_InputFunction->ac_Save();
		}
}

void QcomControl::ac_Save(void)
{
	std::string f_ref_CurrentPath = "QcomControl::ac_Save";

	if(m_ID == -1551)
		{
		char* f_controlcomfield[10];
		char* f_controlcomvalue[10];

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_controlcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_controlcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_controlcomfield[0], "owner");
		sprintf(f_controlcomfield[1], "name");
		sprintf(f_controlcomfield[2], "description");
		sprintf(f_controlcomfield[3], "vision");
		sprintf(f_controlcomfield[4], "controlfunctionid");
		sprintf(f_controlcomfield[5], "comid");
		sprintf(f_controlcomfield[6], "icoid");
		sprintf(f_controlcomfield[7], "qamlevel");
		sprintf(f_controlcomfield[8], "qamid");
		sprintf(f_controlcomfield[9], "typed");

		sprintf(f_controlcomvalue[0], "%s", m_owner.c_str());
		sprintf(f_controlcomvalue[1], "%s", m_name.c_str());
		sprintf(f_controlcomvalue[2], "%s", m_description.c_str());
		sprintf(f_controlcomvalue[3], "%s", m_vision.c_str());
		sprintf(f_controlcomvalue[4], "%i", m_ControlfunctionID);
		sprintf(f_controlcomvalue[5], "%i", m_ComID);
		sprintf(f_controlcomvalue[6], "%i", m_ICOID);
		sprintf(f_controlcomvalue[7], "%i", m_QamLevel);
		sprintf(f_controlcomvalue[8], "%i", m_QamID);
		sprintf(f_controlcomvalue[9], "%i", m_typed);

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("comcontrol", (const char **)f_controlcomfield, (const char **)f_controlcomvalue, 10, false, false);

		mutex_qcomdb.unlock();
		}
	else
		{
		char* f_controlcomwhere[1];
		char* f_controlcomfield[10];
		char* f_controlcomvalue[10];

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_controlcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_controlcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		f_controlcomwhere[0] = (char*)malloc(sizeof(char) * 512);

		sprintf(f_controlcomfield[0], "owner");
		sprintf(f_controlcomfield[1], "name");
		sprintf(f_controlcomfield[2], "description");
		sprintf(f_controlcomfield[3], "vision");
		sprintf(f_controlcomfield[4], "controlfunctionid");
		sprintf(f_controlcomfield[5], "comid");
		sprintf(f_controlcomfield[6], "icoid");
		sprintf(f_controlcomfield[7], "qamlevel");
		sprintf(f_controlcomfield[8], "qamid");
		sprintf(f_controlcomfield[9], "typed");

		sprintf(f_controlcomvalue[0], "%s", m_owner.c_str());
		sprintf(f_controlcomvalue[1], "%s", m_name.c_str());
		sprintf(f_controlcomvalue[2], "%s", m_description.c_str());
		sprintf(f_controlcomvalue[3], "%s", m_vision.c_str());
		sprintf(f_controlcomvalue[4], "%i", m_ControlfunctionID);
		sprintf(f_controlcomvalue[5], "%i", m_ComID);
		sprintf(f_controlcomvalue[6], "%i", m_ICOID);
		sprintf(f_controlcomvalue[7], "%i", m_QamLevel);
		sprintf(f_controlcomvalue[8], "%i", m_QamID);
		sprintf(f_controlcomvalue[9], "%i", m_typed);

		sprintf(f_controlcomwhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("comcontrol", (const char **)f_controlcomfield, (const char **)f_controlcomvalue, 10, f_controlcomwhere[0], false, false);

		mutex_qcomdb.unlock();
		}

	if(m_ControlFunction != nullptr)
		{
		m_ControlFunction->ac_Save();
		}
}

void QcomOutput::ac_Save(void)
{
	std::string f_ref_CurrentPath = "QcomOutput::ac_Save";

	if(m_ID == -1551)
		{
		char* f_outputcomfield[10];
		char* f_outputcomvalue[10];

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_outputcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_outputcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_outputcomfield[0], "owner");
		sprintf(f_outputcomfield[1], "name");
		sprintf(f_outputcomfield[2], "description");
		sprintf(f_outputcomfield[3], "vision");
		sprintf(f_outputcomfield[4], "outputfunctionid");
		sprintf(f_outputcomfield[5], "comid");
		sprintf(f_outputcomfield[6], "icoid");
		sprintf(f_outputcomfield[7], "qamlevel");
		sprintf(f_outputcomfield[8], "qamid");
		sprintf(f_outputcomfield[9], "typed");

		sprintf(f_outputcomvalue[0], "%s", m_owner.c_str());
		sprintf(f_outputcomvalue[1], "%s", m_name.c_str());
		sprintf(f_outputcomvalue[2], "%s", m_description.c_str());
		sprintf(f_outputcomvalue[3], "%s", m_vision.c_str());
		sprintf(f_outputcomvalue[4], "%i", m_OutputfunctionID);
		sprintf(f_outputcomvalue[5], "%i", m_ComID);
		sprintf(f_outputcomvalue[6], "%i", m_ICOID);
		sprintf(f_outputcomvalue[7], "%i", m_QamLevel);
		sprintf(f_outputcomvalue[8], "%i", m_QamID);
		sprintf(f_outputcomvalue[9], "%i", m_typed);

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("comoutput", (const char **)f_outputcomfield, (const char **)f_outputcomvalue, 10, false, false);

		mutex_qcomdb.unlock();
		}
	else
		{
		char* f_outputcomwhere[1];
		char* f_outputcomfield[10];
		char* f_outputcomvalue[10];

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_outputcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_outputcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		f_outputcomwhere[0] = (char*)malloc(sizeof(char) * 512);

		sprintf(f_outputcomfield[0], "owner");
		sprintf(f_outputcomfield[1], "name");
		sprintf(f_outputcomfield[2], "description");
		sprintf(f_outputcomfield[3], "vision");
		sprintf(f_outputcomfield[4], "outputfunctionid");
		sprintf(f_outputcomfield[5], "comid");
		sprintf(f_outputcomfield[6], "icoid");
		sprintf(f_outputcomfield[7], "qamlevel");
		sprintf(f_outputcomfield[8], "qamid");
		sprintf(f_outputcomfield[9], "typed");

		sprintf(f_outputcomvalue[0], "%s", m_owner.c_str());
		sprintf(f_outputcomvalue[1], "%s", m_name.c_str());
		sprintf(f_outputcomvalue[2], "%s", m_description.c_str());
		sprintf(f_outputcomvalue[3], "%s", m_vision.c_str());
		sprintf(f_outputcomvalue[4], "%i", m_OutputfunctionID);
		sprintf(f_outputcomvalue[5], "%i", m_ComID);
		sprintf(f_outputcomvalue[6], "%i", m_ICOID);
		sprintf(f_outputcomvalue[7], "%i", m_QamLevel);
		sprintf(f_outputcomvalue[8], "%i", m_QamID);
		sprintf(f_outputcomvalue[9], "%i", m_typed);

		sprintf(f_outputcomwhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("comoutput", (const char **)f_outputcomfield, (const char **)f_outputcomvalue, 10, f_outputcomwhere[0], false, false);

		mutex_qcomdb.unlock();
		}

	if(m_OutputFunction != nullptr)
		{
		m_OutputFunction->ac_Save();
		}
}

void Qcom_genScript::ac_Save(void)
{
	std::string f_ref_CurrentPath = "Qcom_genScript::ac_Save";

	if(m_ID == -1551)
		{
		char* f_genfield[10];
		char* f_genvalue[10];

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_genfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_genvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_genfield[0], "owner");
		sprintf(f_genfield[1], "name");
		sprintf(f_genfield[2], "description");
		sprintf(f_genfield[3], "vision");
		sprintf(f_genfield[4], "seedinfo");
		sprintf(f_genfield[5], "namegroup");
		sprintf(f_genfield[6], "comid");
		sprintf(f_genfield[7], "qamlevel");
		sprintf(f_genfield[8], "qamid");
		sprintf(f_genfield[9], "typed");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_genvalue[0], "%s", m_owner.c_str());
		sprintf(f_genvalue[1], "%s", m_name.c_str());
		sprintf(f_genvalue[2], "%s", m_description.c_str());
		sprintf(f_genvalue[3], "%s", m_vision.c_str());
		sprintf(f_genvalue[4], "%s", m_seedinfo.c_str());
		sprintf(f_genvalue[5], "%s", m_NameGroup.c_str());
		sprintf(f_genvalue[6], "%i", m_ComID);
		sprintf(f_genvalue[7], "%i", m_QamLevel);
		sprintf(f_genvalue[8], "%i", m_QamID);
		sprintf(f_genvalue[9], "%i", m_typed);

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("inlscript", (const char **)f_genfield, (const char **)f_genvalue, 10, false, false);

		mutex_qcomdb.unlock();

		for(int f_XYZ = 0; f_XYZ < m_vec_InitLineOrdered.size(); f_XYZ++)
			{
			if(m_vec_InitLineOrderedID[f_XYZ] <= 0)
				{
				char* f_inlLinefield[8];
				char* f_inlLinevalue[8];

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_inlLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_inlLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_inlLinefield[0], "owner");
				sprintf(f_inlLinefield[1], "namegroup");
				sprintf(f_inlLinefield[2], "codestring");
				sprintf(f_inlLinefield[3], "lineno");
				sprintf(f_inlLinefield[4], "functionid");
				sprintf(f_inlLinefield[5], "qamlevel");
				sprintf(f_inlLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_inlLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_inlLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_inlLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_inlLinevalue[3], "%i", f_XYZ);
				sprintf(f_inlLinevalue[4], "%i", m_ID);
				sprintf(f_inlLinevalue[5], "%i", m_QamLevel);
				sprintf(f_inlLinevalue[6], "%i", m_QamID);

				mutex_qcomdb.lock();

				int f_ID = g_SafeL[2]->Insert("inlcodeline", (const char **)f_inlLinefield, (const char **)f_inlLinevalue, 7, false, false);

				mutex_qcomdb.unlock();
				}
			else
				{
				char* f_inlLinefield[8];
				char* f_inlLinevalue[8];
				char* f_inlLinewhere[1];

				f_inlLinewhere[0] = (char*)malloc(sizeof(char) * 512);

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_inlLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_inlLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_inlLinefield[0], "owner");
				sprintf(f_inlLinefield[1], "namegroup");
				sprintf(f_inlLinefield[2], "codestring");
				sprintf(f_inlLinefield[3], "lineno");
				sprintf(f_inlLinefield[4], "functionid");
				sprintf(f_inlLinefield[5], "qamlevel");
				sprintf(f_inlLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_inlLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_inlLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_inlLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_inlLinevalue[3], "%i", f_XYZ);
				sprintf(f_inlLinevalue[4], "%i", m_ID);
				sprintf(f_inlLinevalue[5], "%i", m_QamLevel);
				sprintf(f_inlLinevalue[6], "%i", m_QamID);

				sprintf(f_inlLinewhere[0], "id = %i", m_vec_InitLineOrderedID[f_XYZ]);

				mutex_qcomdb.lock();

				g_SafeL[2]->Update("inlcodeline", (const char**)f_inlLinefield, (const char**)f_inlLinevalue, 7, f_inlLinewhere[0], false, false);

				mutex_qcomdb.unlock();
				}
			}
		}
	else
		{
		char* f_genfield[10];
		char* f_genvalue[10];
		char* f_genwhere[1];

		f_genwhere[0] = (char*)malloc(sizeof(char) * 512);

		for(int f_Count = 0; f_Count < 10; f_Count++)
			{
			f_genfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_genvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_genfield[0], "owner");
		sprintf(f_genfield[1], "name");
		sprintf(f_genfield[2], "description");
		sprintf(f_genfield[3], "vision");
		sprintf(f_genfield[4], "seedinfo");
		sprintf(f_genfield[5], "namegroup");
		sprintf(f_genfield[6], "comid");
		sprintf(f_genfield[7], "qamlevel");
		sprintf(f_genfield[8], "qamid");
		sprintf(f_genfield[9], "typed");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_genvalue[0], "%s", m_owner.c_str());
		sprintf(f_genvalue[1], "%s", m_name.c_str());
		sprintf(f_genvalue[2], "%s", m_description.c_str());
		sprintf(f_genvalue[3], "%s", m_vision.c_str());
		sprintf(f_genvalue[4], "%s", m_seedinfo.c_str());
		sprintf(f_genvalue[5], "%s", m_NameGroup.c_str());
		sprintf(f_genvalue[6], "%i", m_ComID);
		sprintf(f_genvalue[7], "%i", m_QamLevel);
		sprintf(f_genvalue[8], "%i", m_QamID);
		sprintf(f_genvalue[9], "%i", m_typed);

		sprintf(f_genwhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("inlscript", (const char**)f_genfield, (const char**)f_genvalue, 11, f_genwhere[0], false, false);

		mutex_qcomdb.unlock();

		for(int f_XYZ = 0; f_XYZ < m_vec_InitLineOrdered.size(); f_XYZ++)
			{
			if(m_vec_InitLineOrderedID[f_XYZ] <= 0)
				{
				char* f_inlLinefield[8];
				char* f_inlLinevalue[8];

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_inlLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_inlLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_inlLinefield[0], "owner");
				sprintf(f_inlLinefield[1], "namegroup");
				sprintf(f_inlLinefield[2], "codestring");
				sprintf(f_inlLinefield[3], "lineno");
				sprintf(f_inlLinefield[4], "functionid");
				sprintf(f_inlLinefield[5], "qamlevel");
				sprintf(f_inlLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_inlLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_inlLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_inlLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_inlLinevalue[3], "%i", f_XYZ);
				sprintf(f_inlLinevalue[4], "%i", m_ID);
				sprintf(f_inlLinevalue[5], "%i", m_QamLevel);
				sprintf(f_inlLinevalue[6], "%i", m_QamID);

				mutex_qcomdb.lock();

				int f_ID = g_SafeL[2]->Insert("inlcodeline", (const char **)f_inlLinefield, (const char **)f_inlLinevalue, 7, false, false);

				mutex_qcomdb.unlock();
				}
			else
				{
				char* f_inlLinefield[8];
				char* f_inlLinevalue[8];
				char* f_inlLinewhere[1];

				f_inlLinewhere[0] = (char*)malloc(sizeof(char) * 512);

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_inlLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_inlLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_inlLinefield[0], "owner");
				sprintf(f_inlLinefield[1], "namegroup");
				sprintf(f_inlLinefield[2], "codestring");
				sprintf(f_inlLinefield[3], "lineno");
				sprintf(f_inlLinefield[4], "functionid");
				sprintf(f_inlLinefield[5], "qamlevel");
				sprintf(f_inlLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_inlLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_inlLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_inlLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_inlLinevalue[3], "%i", f_XYZ);
				sprintf(f_inlLinevalue[4], "%i", m_ID);
				sprintf(f_inlLinevalue[5], "%i", m_QamLevel);
				sprintf(f_inlLinevalue[6], "%i", m_QamID);

				sprintf(f_inlLinewhere[0], "id = %i", m_vec_InitLineOrderedID[f_XYZ]);

				mutex_qcomdb.lock();

				g_SafeL[2]->Update("inlcodeline", (const char**)f_inlLinefield, (const char**)f_inlLinevalue, 7, f_inlLinewhere[0], false, false);

				mutex_qcomdb.unlock();
				}
			}
		}
}

void Qcom_eslfunction::ac_Save(void)
{
	std::string f_ref_CurrentPath = "Qcom_eslfunction::ac_Save";

	if(m_ID == -1551)
		{
		char* f_eslfield[11];
		char* f_eslvalue[11];

		for(int f_Count = 0; f_Count < 11; f_Count++)
			{
			f_eslfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_eslvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_eslfield[0], "owner");
		sprintf(f_eslfield[1], "name");
		sprintf(f_eslfield[2], "description");
		sprintf(f_eslfield[3], "vision");
		sprintf(f_eslfield[4], "targetstr");
		sprintf(f_eslfield[5], "seedinfo");
		sprintf(f_eslfield[6], "namegroup");
		sprintf(f_eslfield[7], "comid");
		sprintf(f_eslfield[8], "qamlevel");
		sprintf(f_eslfield[9], "qamid");
		sprintf(f_eslfield[10], "typed");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_eslvalue[0], "%s", m_owner.c_str());
		sprintf(f_eslvalue[1], "%s", m_name.c_str());
		sprintf(f_eslvalue[2], "%s", m_description.c_str());
		sprintf(f_eslvalue[3], "%s", m_vision.c_str());
		sprintf(f_eslvalue[4], "%s", m_TargetString.c_str());
		sprintf(f_eslvalue[5], "%s", m_seedinfo.c_str());
		sprintf(f_eslvalue[6], "%s", m_NameGroup.c_str());
		sprintf(f_eslvalue[7], "%i", m_ComID);
		sprintf(f_eslvalue[8], "%i", m_QamLevel);
		sprintf(f_eslvalue[9], "%i", m_QamID);
		sprintf(f_eslvalue[10], "%i", m_typed);

		mutex_qcomdb.lock();

		m_ID = g_SafeL[2]->Insert("eslfunction", (const char **)f_eslfield, (const char **)f_eslvalue, 11, false, false);

		mutex_qcomdb.unlock();

		for(int f_XYZ = 0; f_XYZ < m_vec_InitLineOrdered.size(); f_XYZ++)
			{
			if(m_vec_InitLineOrderedID[f_XYZ] <= 0)
				{
				char* f_eslLinefield[7];
				char* f_eslLinevalue[7];

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_eslLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_eslLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}
					
				sprintf(f_eslLinefield[0], "owner");
				sprintf(f_eslLinefield[1], "namegroup");
				sprintf(f_eslLinefield[2], "codestring");
				sprintf(f_eslLinefield[3], "lineno");
				sprintf(f_eslLinefield[4], "functionid");
				sprintf(f_eslLinefield[5], "qamlevel");
				sprintf(f_eslLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_eslLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_eslLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_eslLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_eslLinevalue[3], "%i", f_XYZ);
				sprintf(f_eslLinevalue[4], "%i", m_ID);
				sprintf(f_eslLinevalue[5], "%i", m_QamLevel);
				sprintf(f_eslLinevalue[6], "%i", m_QamID);

				mutex_qcomdb.lock();

				int f_ID = g_SafeL[2]->Insert("eslcodeline", (const char **)f_eslLinefield, (const char **)f_eslLinevalue, 7, false, false);

				mutex_qcomdb.unlock();
				}
			else
				{
				char* f_eslLinefield[7];
				char* f_eslLinevalue[7];
				char* f_eslLinewhere[1];

				f_eslLinewhere[0] = (char*)malloc(sizeof(char) * 512);

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_eslLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_eslLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_eslLinefield[0], "owner");
				sprintf(f_eslLinefield[1], "namegroup");
				sprintf(f_eslLinefield[2], "codestring");
				sprintf(f_eslLinefield[3], "lineno");
				sprintf(f_eslLinefield[4], "functionid");
				sprintf(f_eslLinefield[5], "qamlevel");
				sprintf(f_eslLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_eslLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_eslLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_eslLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_eslLinevalue[3], "%i", f_XYZ);
				sprintf(f_eslLinevalue[4], "%i", m_ID);
				sprintf(f_eslLinevalue[5], "%i", m_QamLevel);
				sprintf(f_eslLinevalue[6], "%i", m_QamID);

				sprintf(f_eslLinewhere[0], "id = %i", m_vec_InitLineOrderedID[f_XYZ]);

				mutex_qcomdb.lock();

				g_SafeL[2]->Update("eslcodeline", (const char**)f_eslLinefield, (const char**)f_eslLinevalue, 7, f_eslLinewhere[0], false, false);

				mutex_qcomdb.unlock();
				}
			}
		}
	else
		{
		char* f_eslfield[11];
		char* f_eslvalue[11];
		char* f_eslwhere[1];

		f_eslwhere[0] = (char*)malloc(sizeof(char) * 512);

		for(int f_Count = 0; f_Count < 11; f_Count++)
			{
			f_eslfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_eslvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_eslfield[0], "owner");
		sprintf(f_eslfield[1], "name");
		sprintf(f_eslfield[2], "description");
		sprintf(f_eslfield[3], "vision");
		sprintf(f_eslfield[4], "targetstr");
		sprintf(f_eslfield[5], "seedinfo");
		sprintf(f_eslfield[6], "namegroup");
		sprintf(f_eslfield[7], "comid");
		sprintf(f_eslfield[8], "qamlevel");
		sprintf(f_eslfield[9], "qamid");
		sprintf(f_eslfield[10], "typed");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_eslvalue[0], "%s", m_owner.c_str());
		sprintf(f_eslvalue[1], "%s", m_name.c_str());
		sprintf(f_eslvalue[2], "%s", m_description.c_str());
		sprintf(f_eslvalue[3], "%s", m_vision.c_str());
		sprintf(f_eslvalue[4], "%s", m_TargetString.c_str());
		sprintf(f_eslvalue[5], "%s", m_seedinfo.c_str());
		sprintf(f_eslvalue[6], "%s", m_NameGroup.c_str());
		sprintf(f_eslvalue[7], "%i", m_ComID);
		sprintf(f_eslvalue[8], "%i", m_QamLevel);
		sprintf(f_eslvalue[9], "%i", m_QamID);
		sprintf(f_eslvalue[10], "%i", m_typed);

		sprintf(f_eslwhere[0], "id = %i", m_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->Update("eslfunction", (const char**)f_eslfield, (const char**)f_eslvalue, 11, f_eslwhere[0], false, false);

		mutex_qcomdb.unlock();

		for(int f_XYZ = 0; f_XYZ < m_vec_InitLineOrdered.size(); f_XYZ++)
			{
			if(m_vec_InitLineOrderedID[f_XYZ] <= 0)
				{
				char* f_eslLinefield[7];
				char* f_eslLinevalue[7];

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_eslLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_eslLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_eslLinefield[0], "owner");
				sprintf(f_eslLinefield[1], "namegroup");
				sprintf(f_eslLinefield[2], "codestring");
				sprintf(f_eslLinefield[3], "lineno");
				sprintf(f_eslLinefield[4], "functionid");
				sprintf(f_eslLinefield[5], "qamlevel");
				sprintf(f_eslLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_eslLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_eslLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_eslLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_eslLinevalue[3], "%i", f_XYZ);
				sprintf(f_eslLinevalue[4], "%i", m_ID);
				sprintf(f_eslLinevalue[5], "%i", m_QamLevel);
				sprintf(f_eslLinevalue[6], "%i", m_QamID);

				mutex_qcomdb.lock();

				int f_ID = g_SafeL[2]->Insert("eslcodeline", (const char **)f_eslLinefield, (const char **)f_eslLinevalue, 7, false, false);

				mutex_qcomdb.unlock();
				}
			else
				{
				char* f_eslLinefield[7];
				char* f_eslLinevalue[7];
				char* f_eslLinewhere[1];

				f_eslLinewhere[0] = (char*)malloc(sizeof(char) * 512);

				for(int f_Count = 0; f_Count < 7; f_Count++)
					{
					f_eslLinefield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_eslLinevalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_eslLinefield[0], "owner");
				sprintf(f_eslLinefield[1], "namegroup");
				sprintf(f_eslLinefield[2], "codestring");
				sprintf(f_eslLinefield[3], "lineno");
				sprintf(f_eslLinefield[4], "functionid");
				sprintf(f_eslLinefield[5], "qamlevel");
				sprintf(f_eslLinefield[6], "qamid");

				if(m_NameGroup.length() == 0)
					{
					m_NameGroup = "DefaultNamegroup";
					}

				sprintf(f_eslLinevalue[0], "%s", m_owner.c_str());
				sprintf(f_eslLinevalue[1], "%s", m_NameGroup.c_str());
				sprintf(f_eslLinevalue[2], "%s", ag_ForwardProtocol(m_vec_InitLineOrdered[f_XYZ]).c_str());
				sprintf(f_eslLinevalue[3], "%i", f_XYZ);
				sprintf(f_eslLinevalue[4], "%i", m_ID);
				sprintf(f_eslLinevalue[5], "%i", m_QamLevel);
				sprintf(f_eslLinevalue[6], "%i", m_QamID);

				sprintf(f_eslLinewhere[0], "id = %i", m_vec_InitLineOrderedID[f_XYZ]);

				mutex_qcomdb.lock();

				g_SafeL[2]->Update("eslcodeline", (const char**)f_eslLinefield, (const char**)f_eslLinevalue, 7, f_eslLinewhere[0], false, false);

				mutex_qcomdb.unlock();
				}
			}
		}
}

void Qcom::ac_Save(void)
{
	std::string f_ref_CurrentPath = "Qcom::ac_Save";

	if(m_ID == -1551)
		{
		char* f_qcomfield[17];
		char* f_qcomvalue[17];

		for(int f_Count = 0; f_Count < 17; f_Count++)
			{
			f_qcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_qcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_qcomfield[0], "owner");
		sprintf(f_qcomfield[1], "name");
		sprintf(f_qcomfield[2], "overload");
		sprintf(f_qcomfield[3], "description");
		sprintf(f_qcomfield[4], "vision");
		sprintf(f_qcomfield[5], "namegroup");
		sprintf(f_qcomfield[6], "score");
		sprintf(f_qcomfield[7], "seedinfo");
		sprintf(f_qcomfield[8], "parentcomid");
		sprintf(f_qcomfield[9], "parentx");
		sprintf(f_qcomfield[10], "parenty");
		sprintf(f_qcomfield[11], "birthcomid");
		sprintf(f_qcomfield[12], "qamlevel");
		sprintf(f_qcomfield[13], "qamid");
		sprintf(f_qcomfield[14], "typed");
		sprintf(f_qcomfield[15], "cost");
		sprintf(f_qcomfield[16], "bosslvlmin");

		if(m_NameGroup.length() == 0)
			{
			m_NameGroup = "DefaultNamegroup";
			}

		sprintf(f_qcomvalue[0], "%s", m_owner.c_str());
		sprintf(f_qcomvalue[1], "%s", m_name.c_str());
		sprintf(f_qcomvalue[2], "%s", m_overload.c_str());
		sprintf(f_qcomvalue[3], "%s", m_description.c_str());
		sprintf(f_qcomvalue[4], "%s", m_vision.c_str());
		sprintf(f_qcomvalue[5], "%s", m_NameGroup.c_str());
		sprintf(f_qcomvalue[6], "%i", m_VoteScore);
		sprintf(f_qcomvalue[7], "%s", m_seedinfo.c_str());
		sprintf(f_qcomvalue[8], "%i", m_parentcomid);
		sprintf(f_qcomvalue[9], "%f", m_parentx);
		sprintf(f_qcomvalue[10], "%f", m_parenty);
		sprintf(f_qcomvalue[11], "%i", m_birthcomid);
		sprintf(f_qcomvalue[12], "%i", m_QamLevel);
		sprintf(f_qcomvalue[13], "%i", m_QamID);
		sprintf(f_qcomvalue[14], "%i", m_typed);
		sprintf(f_qcomvalue[15], "%f", m_Cost);
		sprintf(f_qcomvalue[16], "%f", m_BossLVLMin);

		mutex_qcomdb.lock();

		int f_qcomUniqueID = g_SafeL[2]->Insert("com", (const char **)f_qcomfield, (const char **)f_qcomvalue, 17, false, false);

		mutex_qcomdb.unlock();

		m_ID = f_qcomUniqueID;

		m_genScript->m_ComID = m_ID;
		m_genScript->m_owner = m_owner;
		m_genScript->m_QamID = m_QamID;
		m_genScript->m_QamLevel = m_QamLevel;

		if(m_genScript->m_ID == -1551)
			{
			char* f_qcomINLfield[10];
			char* f_qcomINLvalue[10];

			for(int f_Count = 0; f_Count < 10; f_Count++)
				{
				f_qcomINLfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qcomINLvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			sprintf(f_qcomINLfield[0], "owner");
			sprintf(f_qcomINLfield[1], "name");
			sprintf(f_qcomINLfield[2], "description");
			sprintf(f_qcomINLfield[3], "vision");
			sprintf(f_qcomINLfield[4], "namegroup");
			sprintf(f_qcomINLfield[5], "seedinfo");
			sprintf(f_qcomINLfield[6], "comid");
			sprintf(f_qcomINLfield[7], "qamlevel");
			sprintf(f_qcomINLfield[8], "qamid");
			sprintf(f_qcomINLfield[9], "typed");

			if(m_genScript->m_NameGroup.length() == 0)
				{
				m_genScript->m_NameGroup = "DefaultNamegroup";
				}

			sprintf(f_qcomINLvalue[0], "%s", m_genScript->m_owner.c_str());
			sprintf(f_qcomINLvalue[1], "%s", m_genScript->m_name.c_str());
			sprintf(f_qcomINLvalue[2], "%s", m_genScript->m_description.c_str());
			sprintf(f_qcomINLvalue[3], "%s", m_genScript->m_vision.c_str());
			sprintf(f_qcomINLvalue[4], "%s", m_genScript->m_NameGroup.c_str());
			sprintf(f_qcomINLvalue[5], "%s", m_genScript->m_seedinfo.c_str());
			sprintf(f_qcomINLvalue[6], "%i", m_genScript->m_ComID);
			sprintf(f_qcomINLvalue[7], "%i", m_genScript->m_QamLevel);
			sprintf(f_qcomINLvalue[8], "%i", m_genScript->m_QamID);
			sprintf(f_qcomINLvalue[9], "%i", m_genScript->m_typed);

			mutex_qcomdb.lock();

			int f_qcomINLUniqueID = g_SafeL[2]->Insert("inlscript", (const char **)f_qcomINLfield, (const char **)f_qcomINLvalue, 10, false, false);

			mutex_qcomdb.unlock();

			m_genScript->m_ID = f_qcomINLUniqueID;

			for(int f_XY = 0; f_XY < m_genScript->m_vec_InitLineOrdered.size(); f_XY++)
				{
				char* f_qcomINLlinefield[8];
				char* f_qcomINLlinevalue[8];

				for(int f_Count = 0; f_Count < 8; f_Count++)
					{
					f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
					f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
					}

				sprintf(f_qcomINLlinefield[0], "owner");
				sprintf(f_qcomINLlinefield[1], "namegroup");
				sprintf(f_qcomINLlinefield[2], "codestring");
				sprintf(f_qcomINLlinefield[3], "lineno");	
				sprintf(f_qcomINLlinefield[4], "inlscriptid");
				sprintf(f_qcomINLlinefield[5], "typed");
				sprintf(f_qcomINLlinefield[6], "qamlevel");
				sprintf(f_qcomINLlinefield[7], "qamid");

				sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
				sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
				sprintf(f_qcomINLlinevalue[2], "%s", ag_ForwardProtocol(m_genScript->m_vec_InitLineOrdered[f_XY]).c_str());
				sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
				sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
				sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_typed);
				sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamLevel);
				sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_QamID);

				mutex_qcomdb.lock();

				int f_qcomINLlineUniqueID = g_SafeL[2]->Insert("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, false, false);
					
				if(f_XY < m_genScript->m_vec_InitLineOrderedID.size())
					{
					m_genScript->m_vec_InitLineOrderedID[f_XY] = f_qcomINLlineUniqueID;
					}
				else
					{
					m_genScript->m_vec_InitLineOrderedID.push_back(f_qcomINLlineUniqueID);
					}

				mutex_qcomdb.unlock();
				}
			}
		else
			{
			char* f_qcomINLwhere[1];
			char* f_qcomINLfield[10];
			char* f_qcomINLvalue[10];

			for(int f_Count = 0; f_Count < 10; f_Count++)
				{
				f_qcomINLfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qcomINLvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_qcomINLwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_qcomINLfield[0], "owner");
			sprintf(f_qcomINLfield[1], "name");
			sprintf(f_qcomINLfield[2], "description");
			sprintf(f_qcomINLfield[3], "vision");
			sprintf(f_qcomINLfield[4], "namegroup");
			sprintf(f_qcomINLfield[5], "seedinfo");
			sprintf(f_qcomINLfield[6], "comid");
			sprintf(f_qcomINLfield[7], "qamlevel");
			sprintf(f_qcomINLfield[8], "qamid");
			sprintf(f_qcomINLfield[9], "typed");

			if(m_genScript->m_NameGroup.length() == 0)
				{
				m_genScript->m_NameGroup = "DefaultNamegroup";
				}

			sprintf(f_qcomINLvalue[0], "%s", m_genScript->m_owner.c_str());
			sprintf(f_qcomINLvalue[1], "%s", m_genScript->m_name.c_str());
			sprintf(f_qcomINLvalue[2], "%s", m_genScript->m_description.c_str());
			sprintf(f_qcomINLvalue[3], "%s", m_genScript->m_vision.c_str());
			sprintf(f_qcomINLvalue[4], "%s", m_genScript->m_NameGroup.c_str());
			sprintf(f_qcomINLvalue[5], "%s", m_genScript->m_seedinfo.c_str());
			sprintf(f_qcomINLvalue[6], "%i", m_genScript->m_ComID);
			sprintf(f_qcomINLvalue[7], "%i", m_genScript->m_QamLevel);
			sprintf(f_qcomINLvalue[8], "%i", m_genScript->m_QamID);
			sprintf(f_qcomINLvalue[9], "%i", m_genScript->m_typed);

			sprintf(f_qcomINLwhere[0], "id = %i", m_genScript->m_ID);

			mutex_qcomdb.lock();

			g_SafeL[2]->Update("inlscript", (const char **)f_qcomINLfield, (const char **)f_qcomINLvalue, 10, f_qcomINLwhere[0], false, false);

			mutex_qcomdb.unlock();

			for(int f_XY = 0; f_XY < m_genScript->m_vec_InitLineOrdered.size(); f_XY++)
				{
				if((m_genScript->m_vec_InitLineOrderedID[f_XY] == -5) || (m_genScript->m_vec_InitLineOrderedID[f_XY] == -1551))
					{
					char* f_qcomINLlinefield[8];
					char* f_qcomINLlinevalue[8];

					for(int f_Count = 0; f_Count < 8; f_Count++)
						{
						f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
						f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
						}

					sprintf(f_qcomINLlinefield[0], "owner");
					sprintf(f_qcomINLlinefield[1], "namegroup");
					sprintf(f_qcomINLlinefield[2], "codestring");
					sprintf(f_qcomINLlinefield[3], "lineno");	
					sprintf(f_qcomINLlinefield[4], "inlscriptid");
					sprintf(f_qcomINLlinefield[5], "qamlevel");
					sprintf(f_qcomINLlinefield[6], "qamid");
					sprintf(f_qcomINLlinefield[7], "typed");

					sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
					sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
					sprintf(f_qcomINLlinevalue[2], "%s", ag_ForwardProtocol(m_genScript->m_vec_InitLineOrdered[f_XY]).c_str());
					sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
					sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
					sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_QamLevel);
					sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamID);
					sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_typed);

					mutex_qcomdb.lock();

					int f_qcomINLlineUniqueID = g_SafeL[2]->Insert("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, false, false);

					m_genScript->m_vec_InitLineOrderedID[f_XY] = f_qcomINLlineUniqueID;

					mutex_qcomdb.unlock();
					}
				else
					{
					char* f_qcomINLlinefield[8];
					char* f_qcomINLlinevalue[8];
					char* f_qcomINLlinewhere[1];

					for(int f_Count = 0; f_Count < 8; f_Count++)
						{
						f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
						f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
						}

					f_qcomINLlinewhere[0] = (char*)malloc(sizeof(char) * 2048);

					sprintf(f_qcomINLlinefield[0], "owner");
					sprintf(f_qcomINLlinefield[1], "namegroup");
					sprintf(f_qcomINLlinefield[2], "codestring");
					sprintf(f_qcomINLlinefield[3], "lineno");	
					sprintf(f_qcomINLlinefield[4], "inlscriptid");
					sprintf(f_qcomINLlinefield[5], "qamlevel");
					sprintf(f_qcomINLlinefield[6], "qamid");
					sprintf(f_qcomINLlinefield[7], "typed");

					sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
					sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
					sprintf(f_qcomINLlinevalue[2], "%s", ag_ForwardProtocol(m_genScript->m_vec_InitLineOrdered[f_XY]).c_str());
					sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
					sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
					sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_QamLevel);
					sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamID);
					sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_typed);

					sprintf(f_qcomINLlinewhere[0], "id = %i", m_genScript->m_vec_InitLineOrderedID[f_XY]);

					mutex_qcomdb.lock();

					g_SafeL[2]->Update("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, f_qcomINLlinewhere[0], false, false);

					mutex_qcomdb.unlock();
					}
				}
			}
		}
	else
		{
		if(m_Save)
			{
			char* f_qcomwhere[1];
			char* f_qcomfield[17];
			char* f_qcomvalue[17];

			for(int f_Count = 0; f_Count < 17; f_Count++)
				{
				f_qcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_qcomwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_qcomfield[0], "owner");
			sprintf(f_qcomfield[1], "name");
			sprintf(f_qcomfield[2], "overload");
			sprintf(f_qcomfield[3], "description");
			sprintf(f_qcomfield[4], "vision");
			sprintf(f_qcomfield[5], "namegroup");
			sprintf(f_qcomfield[6], "score");
			sprintf(f_qcomfield[7], "seedinfo");
			sprintf(f_qcomfield[8], "parentcomid");
			sprintf(f_qcomfield[9], "parentx");
			sprintf(f_qcomfield[10], "parenty");
			sprintf(f_qcomfield[11], "birthcomid");
			sprintf(f_qcomfield[12], "qamlevel");
			sprintf(f_qcomfield[13], "qamid");
			sprintf(f_qcomfield[14], "typed");
			sprintf(f_qcomfield[15], "cost");
			sprintf(f_qcomfield[16], "bosslvlmin");

			if(m_NameGroup.length() == 0)
				{
				m_NameGroup = "DefaultNamegroup";
				}

			sprintf(f_qcomvalue[0], "%s", m_owner.c_str());
			sprintf(f_qcomvalue[1], "%s", m_name.c_str());
			sprintf(f_qcomvalue[2], "%s", m_overload.c_str());
			sprintf(f_qcomvalue[3], "%s", m_description.c_str());
			sprintf(f_qcomvalue[4], "%s", m_vision.c_str());
			sprintf(f_qcomvalue[5], "%s", m_NameGroup.c_str());
			sprintf(f_qcomvalue[6], "%i", m_VoteScore);
			sprintf(f_qcomvalue[7], "%s", m_seedinfo.c_str());
			sprintf(f_qcomvalue[8], "%i", m_parentcomid);
			sprintf(f_qcomvalue[9], "%f", m_parentx);
			sprintf(f_qcomvalue[10], "%f", m_parenty);
			sprintf(f_qcomvalue[11], "%i", m_birthcomid);
			sprintf(f_qcomvalue[12], "%i", m_QamLevel);
			sprintf(f_qcomvalue[13], "%i", m_QamID);
			sprintf(f_qcomvalue[14], "%i", m_typed);
			sprintf(f_qcomvalue[15], "%f", m_Cost);
			sprintf(f_qcomvalue[16], "%f", m_BossLVLMin);

			sprintf(f_qcomwhere[0], "id = %i", m_ID);

			mutex_qcomdb.lock();

			g_SafeL[2]->Update("com", (const char **)f_qcomfield, (const char **)f_qcomvalue, 17, f_qcomwhere[0], false, false);

			mutex_qcomdb.unlock();

			char* f_qcomINLwhere[1];
			char* f_qcomINLfield[10];
			char* f_qcomINLvalue[10];

			for(int f_Count = 0; f_Count < 10; f_Count++)
				{
				f_qcomINLfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qcomINLvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_qcomINLwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_qcomINLfield[0], "owner");
			sprintf(f_qcomINLfield[1], "name");
			sprintf(f_qcomINLfield[2], "description");
			sprintf(f_qcomINLfield[3], "vision");
			sprintf(f_qcomINLfield[4], "namegroup");
			sprintf(f_qcomINLfield[5], "seedinfo");
			sprintf(f_qcomINLfield[6], "comid");
			sprintf(f_qcomINLfield[7], "qamlevel");
			sprintf(f_qcomINLfield[8], "qamid");
			sprintf(f_qcomINLfield[9], "typed");

			if(m_genScript->m_NameGroup.length() == 0)
				{
				m_genScript->m_NameGroup = "DefaultNamegroup";
				}

			sprintf(f_qcomINLvalue[0], "%s", m_genScript->m_owner.c_str());
			sprintf(f_qcomINLvalue[1], "%s", m_genScript->m_name.c_str());
			sprintf(f_qcomINLvalue[2], "%s", m_genScript->m_description.c_str());
			sprintf(f_qcomINLvalue[3], "%s", m_genScript->m_vision.c_str());
			sprintf(f_qcomINLvalue[4], "%s", m_genScript->m_NameGroup.c_str());
			sprintf(f_qcomINLvalue[5], "%s", m_genScript->m_seedinfo.c_str());
			sprintf(f_qcomINLvalue[6], "%i", m_genScript->m_ComID);
			sprintf(f_qcomINLvalue[7], "%i", m_genScript->m_QamLevel);
			sprintf(f_qcomINLvalue[8], "%i", m_genScript->m_QamID);
			sprintf(f_qcomINLvalue[9], "%i", m_genScript->m_typed);

			sprintf(f_qcomINLwhere[0], "id = %i", m_genScript->m_ID);

			mutex_qcomdb.lock();

			g_SafeL[2]->Update("inlscript", (const char **)f_qcomINLfield, (const char **)f_qcomINLvalue, 10, f_qcomINLwhere[0], false, false);

			mutex_qcomdb.unlock();

			for(int f_XY = 0; f_XY < m_genScript->m_vec_InitLineOrdered.size(); f_XY++)
				{
				if((m_genScript->m_vec_InitLineOrderedID[f_XY] == -5) || (m_genScript->m_vec_InitLineOrderedID[f_XY] == -1551))
					{
					char* f_qcomINLlinefield[8];
					char* f_qcomINLlinevalue[8];

					for(int f_Count = 0; f_Count < 8; f_Count++)
						{
						f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
						f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
						}

					sprintf(f_qcomINLlinefield[0], "owner");
					sprintf(f_qcomINLlinefield[1], "namegroup");
					sprintf(f_qcomINLlinefield[2], "codestring");
					sprintf(f_qcomINLlinefield[3], "lineno");	
					sprintf(f_qcomINLlinefield[4], "inlscriptid");
					sprintf(f_qcomINLlinefield[5], "qamlevel");
					sprintf(f_qcomINLlinefield[6], "qamid");
					sprintf(f_qcomINLlinefield[7], "typed");

					sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
					sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
					sprintf(f_qcomINLlinevalue[2], "%s", ag_ForwardProtocol(m_genScript->m_vec_InitLineOrdered[f_XY]).c_str());
					sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
					sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
					sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_QamLevel);
					sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamID);
					sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_typed);

					mutex_qcomdb.lock();

					int f_qcomINLlineUniqueID = g_SafeL[2]->Insert("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, false, false);

					m_genScript->m_vec_InitLineOrderedID[f_XY] = f_qcomINLlineUniqueID;

					mutex_qcomdb.unlock();
					}
				else
					{
					char* f_qcomINLlinefield[8];
					char* f_qcomINLlinevalue[8];
					char* f_qcomINLlinewhere[1];

					for(int f_Count = 0; f_Count < 8; f_Count++)
						{
						f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
						f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
						}

					f_qcomINLlinewhere[0] = (char*)malloc(sizeof(char) * 2048);

					sprintf(f_qcomINLlinefield[0], "owner");
					sprintf(f_qcomINLlinefield[1], "namegroup");
					sprintf(f_qcomINLlinefield[2], "codestring");
					sprintf(f_qcomINLlinefield[3], "lineno");	
					sprintf(f_qcomINLlinefield[4], "inlscriptid");
					sprintf(f_qcomINLlinefield[5], "qamlevel");
					sprintf(f_qcomINLlinefield[6], "qamid");
					sprintf(f_qcomINLlinefield[7], "typed");

					sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
					sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
					sprintf(f_qcomINLlinevalue[2], "%s", ag_ForwardProtocol(m_genScript->m_vec_InitLineOrdered[f_XY]).c_str());
					sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
					sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
					sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_QamLevel);
					sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamID);
					sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_typed);

					sprintf(f_qcomINLlinewhere[0], "id = %i", m_genScript->m_vec_InitLineOrderedID[f_XY]);

					mutex_qcomdb.lock();

					g_SafeL[2]->Update("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, f_qcomINLlinewhere[0], false, false);

					mutex_qcomdb.unlock();
					}
				}

			m_Save = false;
			}
		}

	for(int f_XYZ = 0; f_XYZ < m_vec_ESLFunction.size(); f_XYZ++)
		{
		m_vec_ESLFunction[f_XYZ]->m_ComID = m_ID;
		m_vec_ESLFunction[f_XYZ]->m_owner = m_owner;
		m_vec_ESLFunction[f_XYZ]->m_QamID = m_QamID;
		m_vec_ESLFunction[f_XYZ]->m_QamLevel = m_QamLevel;

		m_vec_ESLFunction[f_XYZ]->ac_Save();
		}

	if(m_Frame_ESLFunction != nullptr)
		{
		m_Frame_ESLFunction->m_ComID = m_ID;
		m_Frame_ESLFunction->m_owner = m_owner;
		m_Frame_ESLFunction->m_QamID = m_QamID;
		m_Frame_ESLFunction->m_QamLevel = m_QamLevel;

		m_Frame_ESLFunction->ac_Save();
		}

	for(int f_XYZ = 0; f_XYZ < m_vec_Input.size(); f_XYZ++)
		{
		m_vec_Input[f_XYZ]->m_ComID = m_ID;
		m_vec_Input[f_XYZ]->m_owner = m_owner;
		m_vec_Input[f_XYZ]->m_QamID = m_QamID;
		m_vec_Input[f_XYZ]->m_QamLevel = m_QamLevel;

		m_vec_Input[f_XYZ]->ac_Save();
		}

	for(int f_XYZ = 0; f_XYZ < m_vec_Output.size(); f_XYZ++)
		{
		m_vec_Output[f_XYZ]->m_ComID = m_ID;
		m_vec_Output[f_XYZ]->m_owner = m_owner;
		m_vec_Output[f_XYZ]->m_QamID = m_QamID;
		m_vec_Output[f_XYZ]->m_QamLevel = m_QamLevel;

		m_vec_Output[f_XYZ]->ac_Save();
		}
}

void QcomManager::ac_LoadAll(int f_QamID, int f_QamLevel)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_LoadAll";
	acClearGrid();

	//Build the query
	char* f_comquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed, cost FROM com WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed, cost FROM com WHERE qamid = %i", f_QamID);
		}

	mutex_qcomdb.lock();

	g_SafeL[2]->acSelectCommand(f_comquery, false, false);

	delete[] f_comquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_com");
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>(f_count, true);

			m_vec_Qcom.push_back(f_com);
			}

		//Build the tree
		for(int f_count = 0; f_count < m_vec_Qcom.size(); f_count++)
			{
			std::shared_ptr<Qcom> f_com = m_vec_Qcom[f_count];

			f_com->m_ParentCom = g_QcomManager->ac_Find_Com_ByID(f_com->m_parentcomid);

			f_com->m_ParentCom->m_vec_Qcom.push_back(f_com);
			}
		}

	//load all cominput
	//Build the query
	char* f_inputquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_inputquery, "SELECT id, owner, name, description, vision, inputfunctionid, comid, icoid, qamlevel, qamid, typed FROM cominput WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_inputquery, "SELECT id, owner, name, description, vision, inputfunctionid, comid, icoid, qamlevel, qamid, typed FROM cominput WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_inputquery, false, false);

	delete[] f_inputquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_comInput");
			std::shared_ptr<QcomInput> f_comInput = std::make_shared_reflect<QcomInput>(f_count, true);

			std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(f_comInput->m_ComID);

			f_com->m_vec_Input.push_back(f_comInput);

			m_vec_Input.push_back(f_comInput);
			}
		}

	//load all comoutput
	//Build the query
	char* f_outputquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_outputquery, "SELECT id, owner, name, description, vision, outputinitid, comid, icoid, qamlevel, qamid, typed FROM comoutput WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_outputquery, "SELECT id, owner, name, description, vision, outputinitid, comid, icoid, qamlevel, qamid, typed FROM comoutput WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_outputquery, false, false);

	delete[] f_outputquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_comoutput");
			std::shared_ptr<QcomOutput> f_comoutput = std::make_shared_reflect<QcomOutput>(f_count, true);

			std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(f_comoutput->m_ComID);

			f_com->m_vec_Output.push_back(f_comoutput);

			m_vec_Output.push_back(f_comoutput);
			}
		}

	//load all Generation Scripts
	//Build the query
	char* f_initquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_initquery, "SELECT id, owner, name, description, vision, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_initquery, "SELECT id, owner, name, description, vision, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_initquery, false, false);

	delete[] f_initquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_InitScript");
			std::shared_ptr<Qcom_genScript> f_InitScript = std::make_shared_reflect<Qcom_genScript>(f_count, true);

			std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(f_InitScript->m_ComID);

			f_com->m_vec_GenScript.push_back(f_InitScript);

			m_vec_GenScript.push_back(f_InitScript);
			}
		}

	//load all com esl Functions
	//Build the query
	char* f_functionquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_functionquery, "SELECT id, owner, name, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM eslfunction WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_functionquery, "SELECT id, owner, name, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM eslfunction WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_functionquery, false, false);

	delete[] f_functionquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_InitScript");
			std::shared_ptr<Qcom_eslfunction> f_Function = std::make_shared_reflect<Qcom_eslfunction>(f_count, true);

			m_vec_ESLFunction.push_back(f_Function);
			}

		acPlace_FunctionCom();
		}

	//load all comwire
	//Build the query
	char* f_comwirequery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_comwirequery, "SELECT id, owner, namegroup, outputid, inputid, typed, parentcomid, qamlevel, qamid FROM comwire WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_comwirequery, "SELECT id, owner, namegroup, outputid, inputid, typed, parentcomid, qamlevel, qamid FROM comwire WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_comwirequery, false, false);

	delete[] f_comwirequery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_comwire");
			std::shared_ptr<QcomWire> f_comwire = std::make_shared_reflect<QcomWire>(f_count, true);

			m_vec_ComWire.push_back(f_comwire);
			}
		}

	//load all wirecom
	//Build the query
	char* f_wirecomquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_wirecomquery, "SELECT id, namegroup, comwireid, typed, vertx, verty, parentcomid, qamlevel, qamid FROM wirecom WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_wirecomquery, "SELECT id, namegroup, comwireid, typed, vertx, verty, parentcomid, qamlevel, qamid FROM wirecom WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_wirecomquery, false, false);

	delete[] f_wirecomquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_wirecom");
			std::shared_ptr<WireCom> f_wirecom = std::make_shared_reflect<WireCom>(f_count, true);

			m_vec_WireCom.push_back(f_wirecom);
			}
		}

	g_vec_DecisionsManager[0]->acLoad_DecisionCom(f_QamID);

	mutex_qcomdb.unlock();

	ac_PlushScripts(f_QamID, f_QamLevel);

	ac_Wire(f_QamID, f_QamLevel);
}

void QcomManager::acPlace_FunctionCom(void)
{
	for(int f_XY = 0; f_XY < m_vec_ESLFunction.size(); f_XY++)
		{
		std::shared_ptr<Qcom_eslfunction> f_function = m_vec_ESLFunction[f_XY];

		std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(f_function->m_ComID);

		std::string f_TargetString = f_function->m_TargetString;
		std::string f_TargetTypeString = "";
		std::string f_TargetIndexNumberString = "";

		if(f_TargetString.length() < 6)
			{
			return;
			}

		for(int f_SF = 0; f_SF < f_TargetString.length(); f_SF++)
			{
			if(f_SF < 6)
				{
				f_TargetTypeString.push_back(f_TargetString.at(f_SF));
				}
			else
				{
				f_TargetIndexNumberString.push_back(f_TargetString.at(f_SF));
				}
			}

		if(f_TargetTypeString.compare("onLoad") == 0)
			{
			f_com->m_vec_ESLFunction.push_back(f_function);
			}
		else if(f_TargetTypeString.compare("Frame_") == 0)
			{
			f_com->m_Frame_ESLFunction = f_function;
			}
		else if(f_TargetTypeString.compare("Input_") == 0)
			{
			int f_TargetIndexNumber = atoi(f_TargetIndexNumberString.c_str());

			if((f_TargetIndexNumber > 0) && (f_TargetIndexNumber < f_com->m_vec_Input.size()))
				{
				std::shared_ptr<QcomInput> f_Input = f_com->m_vec_Input[f_TargetIndexNumber];

				if(f_Input->m_InputfunctionID == f_function->m_ID)
					{
					f_Input->m_InputFunction = f_function;

					f_Input->m_ComID = f_com->m_ID;

					f_Input->m_owner = f_com->m_owner;
					}
				else
					{
					throw;
					}
				}
			}
		else if(f_TargetTypeString.compare("Output") == 0)
			{
			int f_TargetIndexNumber = atoi(f_TargetIndexNumberString.c_str());

			if((f_TargetIndexNumber > 0) && (f_TargetIndexNumber < f_com->m_vec_Output.size()))
				{
				std::shared_ptr<QcomOutput> f_Output = f_com->m_vec_Output[f_TargetIndexNumber];

				if(f_Output->m_OutputfunctionID == f_function->m_ID)
					{
					f_Output->m_OutputFunction = f_function;

					f_Output->m_ComID = f_com->m_ID;

					f_Output->m_owner = f_com->m_owner;
					}
				else
					{
					throw;
					}
				}
			}
		}
}

void DecisionManager::acLoad_DecisionCom(int f_QamID)
{
	std::string f_ref_CurrentPath = "DecisionManager::acLoad_DecisionCom";

	//load all decisioncom
	//Build the query
	char* f_decisioncomquery = new char[512];
	sprintf(f_decisioncomquery, "SELECT id, typed, qamid, originalsourceqamid, sourceowner, originowner, modtype, modtarget, modname FROM decisioncom WHERE originalsourceqamid = %i", f_QamID);
	g_SafeL[2]->acSelectCommand(f_decisioncomquery, false, false);
	delete[] f_decisioncomquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_decisioncom");
			std::shared_ptr<DecisionCom> f_decisioncom = std::make_shared_reflect<DecisionCom>(f_count, true);

			m_vec_DecisionCom.push_back(f_decisioncom);
			}
		}
}

void QcomManager::ac_LoadAll_Append(int f_QamID, int f_QamLevel)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_LoadAll_Append";

	//Build the query
	char* f_comquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed, cost FROM com WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed, cost FROM com WHERE qamid = %i", f_QamID);
		}

	mutex_qcomdb.lock();

	g_SafeL[2]->acSelectCommand(f_comquery, false, false);

	delete[] f_comquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_com");
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>(f_count, true);
			std::shared_ptr<Qcom> f_localcom = g_QcomManager->ac_Find_Com_ByID(atoi(g_Schedular[2]->acEntry(f_count)[0].c_str()));

			//check same comid
			if((f_com->m_ID <= 0) && (f_localcom->m_ID > 0))
				{
				m_vec_Qcom.push_back(f_com);
				}
			else
				{
				if((f_com->m_ID > 0) && (f_localcom->m_ID <= 0))
					{
					m_vec_Qcom.push_back(f_com);
					}
				else
					{
					if(f_com->m_ID != f_localcom->m_ID)
						{
						m_vec_Qcom.push_back(f_com);
						}
					else //else check birthcomid
						{
						std::shared_ptr<Qcom> f_Com = ac_Find_Com_ByID(f_com->m_ID);
						std::shared_ptr<Qcom> f_localCom = ac_Find_Com_ByID(f_localcom->m_ID);

						if((f_Com->m_birthcomid <= 0) && (f_localCom->m_birthcomid > 0))
							{
							m_vec_Qcom.push_back(f_com);
							}
						else
							{
							if((f_Com->m_birthcomid > 0) && (f_localCom->m_birthcomid <= 0))
								{
								m_vec_Qcom.push_back(f_com);
								}
							else
								{
								if(f_Com->m_birthcomid != f_localCom->m_birthcomid)
									{
									m_vec_Qcom.push_back(f_com);
									}
								}
							}
						}
					}
				}
			}
		}

	//Build the tree
	for(int f_count = 0; f_count < m_vec_Qcom.size(); f_count++)
		{
		std::shared_ptr<Qcom> f_com = m_vec_Qcom[f_count];

		f_com->m_ParentCom = g_QcomManager->ac_Find_Com_ByID(f_com->m_parentcomid);

		f_com->m_ParentCom->m_vec_Qcom.push_back(f_com);
		}

	//load all cominput
	//Build the query
	char* f_inputquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_inputquery, "SELECT id, owner, name, description, vision, inputfunctionid, comid, icoid, qamlevel, qamid, typed FROM cominput WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_inputquery, "SELECT id, owner, name, description, vision, inputfunctionid, comid, icoid, qamlevel, qamid, typed FROM cominput WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_inputquery, false, false);

	delete[] f_inputquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_comInput");
			std::shared_ptr<QcomInput> f_comInput = std::make_shared_reflect<QcomInput>(f_count, true);
			std::shared_ptr<QcomInput> f_localcomInput = g_QcomManager->ac_Find_ComInput_ByID(atoi(g_Schedular[2]->acEntry(f_count)[0].c_str()));

			std::shared_ptr<Qcom> f_comst = g_QcomManager->ac_Find_Com_ByID(f_comInput->m_ComID);

			//check same comid
			if((f_comInput->m_ComID <= 0) && (f_localcomInput->m_ComID > 0))
				{
				f_comst->m_vec_Input.push_back(f_comInput);

				m_vec_Input.push_back(f_comInput);
				}
			else
				{
				if((f_comInput->m_ComID > 0) && (f_localcomInput->m_ComID <= 0))
					{
					f_comst->m_vec_Input.push_back(f_comInput);

					m_vec_Input.push_back(f_comInput);
					}
				else
					{
					if(f_comInput->m_ComID != f_localcomInput->m_ComID)
						{
						f_comst->m_vec_Input.push_back(f_comInput);

						m_vec_Input.push_back(f_comInput);
						}
					else //else check birthcomid
						{
						std::shared_ptr<Qcom> f_InputCom = ac_Find_Com_ByID(f_comInput->m_ComID);
						std::shared_ptr<Qcom> f_localInputCom = ac_Find_Com_ByID(f_localcomInput->m_ComID);

						if((f_InputCom->m_birthcomid <= 0) && (f_localInputCom->m_birthcomid > 0))
							{
							f_comst->m_vec_Input.push_back(f_comInput);

							m_vec_Input.push_back(f_comInput);
							}
						else
							{
							if((f_InputCom->m_birthcomid > 0) && (f_localInputCom->m_birthcomid <= 0))
								{
								f_comst->m_vec_Input.push_back(f_comInput);

								m_vec_Input.push_back(f_comInput);
								}
							else
								{
								if(f_InputCom->m_birthcomid != f_localInputCom->m_birthcomid)
									{
									f_comst->m_vec_Input.push_back(f_comInput);

									m_vec_Input.push_back(f_comInput);
									}
								}
							}
						}
					}
				}
			}
		}

	//load all comoutput
	//Build the query
	char* f_outputquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_outputquery, "SELECT id, owner, name, description, vision, outputinitid, comid, icoid, qamlevel, qamid, typed FROM comoutput WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_outputquery, "SELECT id, owner, name, description, vision, outputinitid, comid, icoid, qamlevel, qamid, typed FROM comoutput WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_outputquery, false, false);

	delete[] f_outputquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_comOutput");
			std::shared_ptr<QcomOutput> f_comOutput = std::make_shared_reflect<QcomOutput>(f_count, true);
			std::shared_ptr<QcomOutput> f_localcomOutput = g_QcomManager->ac_Find_ComOutput_ByID(atoi(g_Schedular[2]->acEntry(f_count)[0].c_str()));

			std::shared_ptr<Qcom> f_comst = g_QcomManager->ac_Find_Com_ByID(f_comOutput->m_ComID);

			//check same comid
			if((f_comOutput->m_ComID <= 0) && (f_localcomOutput->m_ComID > 0))
				{
				f_comst->m_vec_Output.push_back(f_comOutput);

				m_vec_Output.push_back(f_comOutput);
				}
			else
				{
				if((f_comOutput->m_ComID > 0) && (f_localcomOutput->m_ComID <= 0))
					{
					f_comst->m_vec_Output.push_back(f_comOutput);

					m_vec_Output.push_back(f_comOutput);
					}
				else
					{
					if(f_comOutput->m_ComID != f_localcomOutput->m_ComID)
						{
						f_comst->m_vec_Output.push_back(f_comOutput);

						m_vec_Output.push_back(f_comOutput);
						}
					else //else check birthcomid
						{
						std::shared_ptr<Qcom> f_OutputCom = ac_Find_Com_ByID(f_comOutput->m_ComID);
						std::shared_ptr<Qcom> f_localOutputCom = ac_Find_Com_ByID(f_localcomOutput->m_ComID);

						if((f_OutputCom->m_birthcomid <= 0) && (f_localOutputCom->m_birthcomid > 0))
							{
							f_comst->m_vec_Output.push_back(f_comOutput);

							m_vec_Output.push_back(f_comOutput);
							}
						else
							{
							if((f_OutputCom->m_birthcomid > 0) && (f_localOutputCom->m_birthcomid <= 0))
								{
								f_comst->m_vec_Output.push_back(f_comOutput);

								m_vec_Output.push_back(f_comOutput);
								}
							else
								{
								if(f_OutputCom->m_birthcomid != f_localOutputCom->m_birthcomid)
									{
									f_comst->m_vec_Output.push_back(f_comOutput);

									m_vec_Output.push_back(f_comOutput);
									}
								}
							}
						}
					}
				}
			}
		}

	//load all Generation Scripts
	//Build the query
	char* f_initquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_initquery, "SELECT id, owner, name, description, vision, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_initquery, "SELECT id, owner, name, description, vision, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_initquery, false, false);

	delete[] f_initquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_InitScript");
			std::shared_ptr<Qcom_genScript> f_InitScript = std::make_shared_reflect<Qcom_genScript>(f_count, true);
			std::shared_ptr<Qcom_genScript> f_localInitScript = g_QcomManager->ac_Find_GenerationScript_ByID(atoi(g_Schedular[2]->acEntry(f_count)[0].c_str()));

			std::shared_ptr<Qcom> f_comst = g_QcomManager->ac_Find_Com_ByID(f_InitScript->m_ComID);

			//check same comid
			if((f_InitScript->m_ComID <= 0) && (f_localInitScript->m_ComID > 0))
				{
				f_comst->m_vec_GenScript.push_back(f_InitScript);

				m_vec_GenScript.push_back(f_InitScript);
				}
			else
				{
				if((f_InitScript->m_ComID > 0) && (f_localInitScript->m_ComID <= 0))
					{
					f_comst->m_vec_GenScript.push_back(f_InitScript);

					m_vec_GenScript.push_back(f_InitScript);
					}
				else
					{
					if(f_InitScript->m_ComID != f_localInitScript->m_ComID)
						{
						f_comst->m_vec_GenScript.push_back(f_InitScript);

						m_vec_GenScript.push_back(f_InitScript);
						}
					else //else check birthcomid
						{
						std::shared_ptr<Qcom> f_GenCom = ac_Find_Com_ByID(f_InitScript->m_ComID);
						std::shared_ptr<Qcom> f_localGenCom = ac_Find_Com_ByID(f_localInitScript->m_ComID);

						if((f_GenCom->m_birthcomid <= 0) && (f_localGenCom->m_birthcomid > 0))
							{
							f_comst->m_vec_GenScript.push_back(f_InitScript);

							m_vec_GenScript.push_back(f_InitScript);
							}
						else
							{
							if((f_GenCom->m_birthcomid > 0) && (f_localGenCom->m_birthcomid <= 0))
								{
								f_comst->m_vec_GenScript.push_back(f_InitScript);

								m_vec_GenScript.push_back(f_InitScript);
								}
							else
								{
								if(f_GenCom->m_birthcomid != f_localGenCom->m_birthcomid)
									{
									f_comst->m_vec_GenScript.push_back(f_InitScript);

									m_vec_GenScript.push_back(f_InitScript);
									}
								}
							}
						}
					}
				}
			}
		}

	//load all com esl Functions
	//Build the query
	char* f_functionquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_functionquery, "SELECT id, owner, name, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM eslfunction WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_functionquery, "SELECT id, owner, name, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM eslfunction WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_functionquery, false, false);

	delete[] f_functionquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_Function");
			std::shared_ptr<Qcom_eslfunction> f_Function = std::make_shared_reflect<Qcom_eslfunction>(f_count, true);
			std::shared_ptr<Qcom_eslfunction> f_localFunction = ac_Find_Function_ByID(atoi(g_Schedular[2]->acEntry(f_count)[0].c_str()));

			//check same comid
			if((f_Function->m_ComID <= 0) && (f_localFunction->m_ComID > 0))
				{
				m_vec_ESLFunction.push_back(f_Function);
				}
			else
				{
				if((f_Function->m_ComID > 0) && (f_localFunction->m_ComID <= 0))
					{
					m_vec_ESLFunction.push_back(f_Function);
					}
				else
					{
					if(f_Function->m_ComID != f_localFunction->m_ComID)
						{
						m_vec_ESLFunction.push_back(f_Function);
						}
					else //else check birthcomid
						{
						std::shared_ptr<Qcom> f_FunctionCom = ac_Find_Com_ByID(f_Function->m_ComID);
						std::shared_ptr<Qcom> f_localFunctionCom = ac_Find_Com_ByID(f_localFunction->m_ComID);

						if((f_FunctionCom->m_birthcomid <= 0) && (f_localFunctionCom->m_birthcomid > 0))
							{
							m_vec_ESLFunction.push_back(f_Function);
							}
						else
							{
							if((f_FunctionCom->m_birthcomid > 0) && (f_localFunctionCom->m_birthcomid <= 0))
								{
								m_vec_ESLFunction.push_back(f_Function);
								}
							else
								{
								if(f_FunctionCom->m_birthcomid != f_localFunctionCom->m_birthcomid)
									{
									m_vec_ESLFunction.push_back(f_Function);
									}
								}
							}
						}
					}
				}
			}
		}

	acPlace_FunctionCom();

	//load all comwire
	//Build the query
	char* f_comwirequery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_comwirequery, "SELECT id, owner, namegroup, outputid, inputid, typed, parentcomid, qamlevel, qamid FROM comwire WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_comwirequery, "SELECT id, owner, namegroup, outputid, inputid, typed, parentcomid, qamlevel, qamid FROM comwire WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_comwirequery, false, false);

	delete[] f_comwirequery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_comwire");
			std::shared_ptr<QcomWire> f_comwire = std::make_shared_reflect<QcomWire>(f_count, true);
			std::shared_ptr<QcomWire> f_localcomwire = ac_Find_ComWire_ByID(atoi(g_Schedular[2]->acEntry(f_count)[0].c_str()));

			//check output of the comwire
			if((f_comwire->m_OutputCom->m_ID <= 0) && (f_localcomwire->m_OutputCom->m_ID > 0))
				{
				m_vec_ComWire.push_back(f_comwire);
				}
			else
				{
				if((f_comwire->m_OutputCom->m_ID > 0) && (f_localcomwire->m_OutputCom->m_ID <= 0))
					{
					m_vec_ComWire.push_back(f_comwire);
					}
				else
					{
					if(f_comwire->m_OutputCom->m_ID != f_localcomwire->m_OutputCom->m_ID)
						{
						m_vec_ComWire.push_back(f_comwire);
						}
					else //else check input of the comwire
						{
						if((f_comwire->m_InputCom->m_ID <= 0) && (f_localcomwire->m_InputCom->m_ID > 0))
							{
							m_vec_ComWire.push_back(f_comwire);
							}
						else
							{
							if((f_comwire->m_InputCom->m_ID > 0) && (f_localcomwire->m_InputCom->m_ID <= 0))
								{
								m_vec_ComWire.push_back(f_comwire);
								}
							else
								{
								if(f_comwire->m_InputCom->m_ID != f_localcomwire->m_InputCom->m_ID)
									{
									m_vec_ComWire.push_back(f_comwire);
									}
								else //else check output of outputs
									{
									if((f_comwire->m_Output->m_ID <= 0) && (f_localcomwire->m_Output->m_ID > 0))
										{
										m_vec_ComWire.push_back(f_comwire);
										}
									else
										{
										if((f_comwire->m_Output->m_ID > 0) && (f_localcomwire->m_Output->m_ID <= 0))
											{
											m_vec_ComWire.push_back(f_comwire);
											}
										else
											{
											if(f_comwire->m_Output->m_ID != f_localcomwire->m_Output->m_ID)
												{
												m_vec_ComWire.push_back(f_comwire);
												}
											else //else check input of inputs
												{
												if((f_comwire->m_Input->m_ID <= 0) && (f_localcomwire->m_Input->m_ID > 0))
													{
													m_vec_ComWire.push_back(f_comwire);
													}
												else
													{
													if((f_comwire->m_Input->m_ID > 0) && (f_localcomwire->m_Input->m_ID <= 0))
														{
														m_vec_ComWire.push_back(f_comwire);
														}
													else
														{
														if(f_comwire->m_Input->m_ID != f_localcomwire->m_Input->m_ID)
															{
															m_vec_ComWire.push_back(f_comwire);
															}
														else //else check birthcomid of output
															{
															if((f_comwire->m_Output->m_birthcomid <= 0) && (f_localcomwire->m_Output->m_birthcomid > 0))
																{
																m_vec_ComWire.push_back(f_comwire);
																}
															else
																{
																if((f_comwire->m_Output->m_birthcomid > 0) && (f_localcomwire->m_Output->m_birthcomid <= 0))
																	{
																	m_vec_ComWire.push_back(f_comwire);
																	}
																else
																	{
																	if(f_comwire->m_Output->m_birthcomid != f_localcomwire->m_Output->m_birthcomid)
																		{
																		m_vec_ComWire.push_back(f_comwire);
																		}
																	else //else check birthcomid of input
																		{
																		if((f_comwire->m_Input->m_birthcomid <= 0) && (f_localcomwire->m_Input->m_birthcomid > 0))
																			{
																			m_vec_ComWire.push_back(f_comwire);
																			}
																		else
																			{
																			if((f_comwire->m_Input->m_birthcomid > 0) && (f_localcomwire->m_Input->m_birthcomid <= 0))
																				{
																				m_vec_ComWire.push_back(f_comwire);
																				}
																			else
																				{
																				if(f_comwire->m_Input->m_birthcomid != f_localcomwire->m_Input->m_birthcomid)
																					{
																					m_vec_ComWire.push_back(f_comwire);
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

	//load all wirecom
	//Build the query
	char* f_wirecomquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_wirecomquery, "SELECT id, namegroup, comwireid, typed, vertx, verty, parentcomid, qamlevel, qamid FROM wirecom WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_wirecomquery, "SELECT id, namegroup, comwireid, typed, vertx, verty, parentcomid, qamlevel, qamid FROM wirecom WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_wirecomquery, false, false);

	delete[] f_wirecomquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		for(int f_count = 0; f_count < g_Schedular[2]->acEntrySize(); f_count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_wirecom");
			std::shared_ptr<WireCom> f_wirecom = std::make_shared_reflect<WireCom>(f_count, true);
			std::shared_ptr<WireCom> f_localwirecom = ac_Find_WireCom_ByID(atoi(g_Schedular[2]->acEntry(f_count)[0].c_str()));

			if(f_localwirecom->m_ID <= 0)
				{
				m_vec_WireCom.push_back(f_wirecom);
				}
			else
				{
				if((f_wirecom->m_ComWire->m_ID <= 0) && (f_localwirecom->m_ComWire->m_ID > 0))
					{
					m_vec_WireCom.push_back(f_wirecom);
					}
				else
					{
					if((f_wirecom->m_ComWire->m_ID > 0) && (f_localwirecom->m_ComWire->m_ID > 0))
						{
						m_vec_WireCom.push_back(f_wirecom);
						}
					else
						{
						if(f_wirecom->m_ComWire->m_ID != f_localwirecom->m_ComWire->m_ID)
							{
							m_vec_WireCom.push_back(f_wirecom);
							}
						else //else check output of the comwire
							{
							if((f_wirecom->m_ComWire->m_OutputCom->m_ID <= 0) && (f_localwirecom->m_ComWire->m_OutputCom->m_ID > 0))
								{
								m_vec_WireCom.push_back(f_wirecom);
								}
							else
								{
								if((f_wirecom->m_ComWire->m_OutputCom->m_ID > 0) && (f_localwirecom->m_ComWire->m_OutputCom->m_ID <= 0))
									{
									m_vec_WireCom.push_back(f_wirecom);
									}
								else
									{
									if(f_wirecom->m_ComWire->m_OutputCom->m_ID != f_localwirecom->m_ComWire->m_OutputCom->m_ID)
										{
										m_vec_WireCom.push_back(f_wirecom);
										}
									else //else check input of the comwire
										{
										if((f_wirecom->m_ComWire->m_InputCom->m_ID <= 0) && (f_localwirecom->m_ComWire->m_InputCom->m_ID > 0))
											{
											m_vec_WireCom.push_back(f_wirecom);
											}
										else
											{
											if((f_wirecom->m_ComWire->m_InputCom->m_ID > 0) && (f_localwirecom->m_ComWire->m_InputCom->m_ID <= 0))
												{
												m_vec_WireCom.push_back(f_wirecom);
												}
											else
												{
												if(f_wirecom->m_ComWire->m_InputCom->m_ID != f_localwirecom->m_ComWire->m_InputCom->m_ID)
													{
													m_vec_WireCom.push_back(f_wirecom);
													}
												else //else check output of outputs
													{
													if((f_wirecom->m_ComWire->m_Output->m_ID <= 0) && (f_localwirecom->m_ComWire->m_Output->m_ID > 0))
														{
														m_vec_WireCom.push_back(f_wirecom);
														}
													else
														{
														if((f_wirecom->m_ComWire->m_Output->m_ID > 0) && (f_localwirecom->m_ComWire->m_Output->m_ID <= 0))
															{
															m_vec_WireCom.push_back(f_wirecom);
															}
														else
															{
															if(f_wirecom->m_ComWire->m_Output->m_ID != f_localwirecom->m_ComWire->m_Output->m_ID)
																{
																m_vec_WireCom.push_back(f_wirecom);
																}
															else //else check input of inputs
																{
																if((f_wirecom->m_ComWire->m_Input->m_ID <= 0) && (f_localwirecom->m_ComWire->m_Input->m_ID > 0))
																	{
																	m_vec_WireCom.push_back(f_wirecom);
																	}
																else
																	{
																	if((f_wirecom->m_ComWire->m_Input->m_ID > 0) && (f_localwirecom->m_ComWire->m_Input->m_ID <= 0))
																		{
																		m_vec_WireCom.push_back(f_wirecom);
																		}
																	else
																		{
																		if(f_wirecom->m_ComWire->m_Input->m_ID != f_localwirecom->m_ComWire->m_Input->m_ID)
																			{
																			m_vec_WireCom.push_back(f_wirecom);
																			}
																		else //else check birthcomid of output
																			{
																			if((f_wirecom->m_ComWire->m_Output->m_birthcomid <= 0) && (f_localwirecom->m_ComWire->m_Output->m_birthcomid > 0))
																				{
																				m_vec_WireCom.push_back(f_wirecom);
																				}
																			else
																				{
																				if((f_wirecom->m_ComWire->m_Output->m_birthcomid > 0) && (f_localwirecom->m_ComWire->m_Output->m_birthcomid <= 0))
																					{
																					m_vec_WireCom.push_back(f_wirecom);
																					}
																				else
																					{
																					if(f_wirecom->m_ComWire->m_Output->m_birthcomid != f_localwirecom->m_ComWire->m_Output->m_birthcomid)
																						{
																						m_vec_WireCom.push_back(f_wirecom);
																						}
																					else //else check birthcomid of input
																						{
																						if((f_wirecom->m_ComWire->m_Input->m_birthcomid <= 0) && (f_localwirecom->m_ComWire->m_Input->m_birthcomid > 0))
																							{
																							m_vec_WireCom.push_back(f_wirecom);
																							}
																						else
																							{
																							if((f_wirecom->m_ComWire->m_Input->m_birthcomid > 0) && (f_localwirecom->m_ComWire->m_Input->m_birthcomid <= 0))
																								{
																								m_vec_WireCom.push_back(f_wirecom);
																								}
																							else
																								{
																								if(f_wirecom->m_ComWire->m_Input->m_birthcomid != f_localwirecom->m_ComWire->m_Input->m_birthcomid)
																									{
																									m_vec_WireCom.push_back(f_wirecom);
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

	mutex_qcomdb.unlock();

	ac_PlushScripts(f_QamID, f_QamLevel);

	ac_Wire(f_QamID, f_QamLevel);
}

void QcomManager::ac_PlushScripts(int f_QamID, int f_QamLevel)
{
	//genScripts
	//Build the query
	char* f_initquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_initquery, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM inlcodeline WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_initquery, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM inlcodeline WHERE qamid = %i", f_QamID);
		}

	mutex_qcomdb.lock();
	
	g_SafeL[2]->acSelectCommand(f_initquery, false, false);

	delete[] f_initquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		int f_IDXLock = -1;
		for (int f_countLine = 0; f_countLine < g_Schedular[2]->acEntrySize(); f_countLine++)
			{
			int f_INLScriptIndex = atoi(g_Schedular[2]->acEntry(f_countLine)[5].c_str());

			if(f_IDXLock < 0 || m_vec_GenScript[f_IDXLock]->m_ID != f_IDXLock)
				{
				bool f_Scan = true;
				int f_rai = 0;
				int f_Index = 0;

				while(f_Scan == true)
					{
					if(m_vec_GenScript[f_rai]->m_ID == f_INLScriptIndex)
						{
						f_Scan = false;
						f_Index = f_rai;
						}

					f_rai++;

					if(f_rai >= m_vec_GenScript.size())
						{
						f_Scan = false;
						f_Index = -1;
						}
					}

				if(f_Index >= 0)
					{
					m_vec_GenScript[f_Index]->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_GenScript[f_Index]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_GenScript[f_Index]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					f_IDXLock = f_Index;
					}
				else
					{
					m_vec_defGenScript->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_defGenScript->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_defGenScript->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					f_IDXLock = -1;
					}
				}
			else
				{
				if(f_IDXLock >= 0)
					{
					m_vec_GenScript[f_IDXLock]->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_GenScript[f_IDXLock]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_GenScript[f_IDXLock]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					}
				else
					{
					m_vec_defGenScript->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_defGenScript->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_defGenScript->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					}
				}
			}
		}

	//genScripts
	//Build the query
	char* f_eslquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_eslquery, "SELECT id, owner, namegroup, codestring, lineno, functionid, qamlevel, qamid FROM eslcodeline WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_eslquery, "SELECT id, owner, namegroup, codestring, lineno, functionid, qamlevel, qamid FROM eslcodeline WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_eslquery, false, false);

	delete[] f_eslquery;

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		int f_IDXLock = -1;
		for (int f_countLine = 0; f_countLine < g_Schedular[2]->acEntrySize(); f_countLine++)
			{
			int f_ESLFunctionIndex = atoi(g_Schedular[2]->acEntry(f_countLine)[5].c_str());

			if(f_IDXLock < 0 || m_vec_ESLFunction[f_IDXLock]->m_ID != f_IDXLock)
				{
				bool f_Scan = true;
				int f_rai = 0;
				int f_Index = 0;

				while(f_Scan == true)
					{
					if(m_vec_ESLFunction[f_rai]->m_ID == f_ESLFunctionIndex)
						{
						f_Scan = false;
						f_Index = f_rai;
						}

					f_rai++;

					if(f_rai >= m_vec_ESLFunction.size())
						{
						f_Scan = false;
						f_Index = -1;
						}
					}

				if(f_Index >= 0)
					{
					m_vec_ESLFunction[f_Index]->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_ESLFunction[f_Index]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_ESLFunction[f_Index]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					f_IDXLock = f_Index;
					}
				else
					{
					m_vec_defESLFunction->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_defESLFunction->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_defESLFunction->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					f_IDXLock = -1;
					}
				}
			else
				{
				if(f_IDXLock >= 0)
					{
					m_vec_ESLFunction[f_IDXLock]->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_ESLFunction[f_IDXLock]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_ESLFunction[f_IDXLock]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					}
				else
					{
					m_vec_defESLFunction->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
					m_vec_defESLFunction->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
					m_vec_defESLFunction->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
					}
				}
			}
		}

	for(int f_countScript = 0; f_countScript < m_vec_GenScript.size(); f_countScript++)
		{
		std::shared_ptr<Qcom_genScript> f_InitScript = m_vec_GenScript[f_countScript];
		
		for(int f_countLine = 0; f_countLine < f_InitScript->m_vec_InitLine.size(); f_countLine++)
			{
			for(int f_countOrder = 0; f_countOrder < f_InitScript->m_vec_InitLineOrder.size(); f_countLine++)
				{
				if (f_InitScript->m_vec_InitLineOrder[f_countOrder] == f_countLine)
					{
					f_InitScript->m_vec_InitLineOrdered.push_back(f_InitScript->m_vec_InitLine[f_countOrder]);
					f_InitScript->m_vec_InitLineOrderedID.push_back(f_InitScript->m_vec_InitLineOrderID[f_countOrder]);
					}
				}
			}

		if(f_InitScript->m_vec_InitLineOrdered.size() != f_InitScript->m_vec_InitLine.size())
			{
			throw;
			}
		}

	for(int f_countFunction = 0; f_countFunction < m_vec_ESLFunction.size(); f_countFunction++)
		{
		std::shared_ptr<Qcom_eslfunction> f_Function = m_vec_ESLFunction[f_countFunction];

		f_Function->m_FunctionLine.clear();
		
		for(int f_countLine = 0; f_countLine < f_Function->m_vec_InitLine.size(); f_countLine++)
			{
			for(int f_countOrder = 0; f_countOrder < f_Function->m_vec_InitLineOrder.size(); f_countLine++)
				{
				if (f_Function->m_vec_InitLineOrder[f_countOrder] == f_countLine)
					{
					f_Function->m_vec_InitLineOrdered.push_back(f_Function->m_vec_InitLine[f_countOrder]);
					f_Function->m_vec_InitLineOrderedID.push_back(f_Function->m_vec_InitLineOrderID[f_countOrder]);
					f_Function->m_FunctionLine += f_Function->m_vec_InitLine[f_countOrder];
					}
				}
			}

		if(f_Function->m_vec_InitLineOrdered.size() != f_Function->m_vec_InitLine.size())
			{
			throw;
			}

		 //////////////////////////////
		// Contractual Obligation
#if 0
		f_Function->acCompile();
#endif
		}

	mutex_qcomdb.unlock();

#pragma message("FIXME:::Functionise")
}

std::vector<std::shared_ptr<BiPacket>> QcomManager::acSearch_PacketbyName(std::string f_Name)
{
	std::vector<std::shared_ptr<BiPacket>> f_vec_Result;

	f_vec_Result.clear();

	for(int f_XY = 0; f_XY < m_vec_Packet.size(); f_XY++)
		{
		std::shared_ptr<BiPacket> f_Packet = m_vec_Packet[f_XY];

		if(f_Packet->m_Name.compare(f_Name) == 0)
			{
			f_vec_Result.push_back(f_Packet);
			}
		else
			{
			for(int f_Helly = 0; f_Helly < f_Packet->m_vec_Packet.size(); f_Helly++)
				{
				std::shared_ptr<BiPacket> f_PacketG = f_Packet->m_vec_Packet[f_XY];

				if(f_PacketG->m_Name.compare(f_Name) == 0)
					{
					f_vec_Result.push_back(f_PacketG);
					}
				}
			}
		}

	return f_vec_Result;
}

void QcomManager::acParse_GenScript(std::shared_ptr<Qcom> f_com)
{
	std::string f_ref_CurrentPath = "QcomManager::acParse_GenScript";

	if(f_com->m_genScript)
		{
		std::shared_ptr<Qcom_genScript> f_GenScript = f_com->m_genScript;

		for(int f_LCount = 0; f_LCount < f_GenScript->m_vec_InitLineOrdered.size(); f_LCount++)
			{
			std::vector<std::string> f_vec_Package;
			std::string f_StrLine = f_GenScript->m_vec_InitLineOrdered[f_LCount];
			std::string f_Packet = "";

			for(int f_CCount = 0; f_CCount < f_StrLine.length(); f_CCount++)
				{
				char f_c = f_StrLine.at(f_CCount);

				if((f_c == ' ') || (f_CCount >= f_StrLine.length() - 1))
					{
					f_vec_Package.push_back(f_Packet);
					f_Packet.clear();
					}
				else
					{
					f_Packet.push_back(f_c);
					}
				}

			if(f_vec_Package[0].compare("Complete") == 0)
				{
				std::string f_Name = f_vec_Package[1];

				std::vector<std::shared_ptr<BiPacket>> f_BiPacket = acSearch_PacketbyName(f_Name);

				for(int f_XY = 0; f_XY < f_BiPacket.size(); f_XY++)
					{
					if(f_BiPacket[f_XY]->m_Name.length() > 0)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_NewPacket");
						std::shared_ptr<BiPacket> f_NewPacket = std::make_shared_reflect<BiPacket>();

						f_NewPacket->m_InsertElementType = COM_PAK_TYPE_COMPLETE;
						f_NewPacket->m_ClassType = ag_Get_ClassType(f_vec_Package[2]);
						f_NewPacket->m_Name = f_vec_Package[3];
						f_NewPacket->m_DefaultValue = f_vec_Package[4];
						f_NewPacket->m_ShareID = atoi(f_vec_Package[5].c_str());
						f_NewPacket->m_Element = atoi(f_vec_Package[6].c_str());
						f_NewPacket->m_Operator_Com = f_com;

						if(f_vec_Package.size() >= 8)
							{
							f_NewPacket->m_Comment = f_vec_Package[7];
							}

						f_BiPacket[f_XY]->m_vec_Packet.push_back(f_NewPacket);
						}
					}
				}
			else if(f_vec_Package[0].compare("Insert") == 0)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_NewPacket");
				std::shared_ptr<BiPacket> f_NewPacket = std::make_shared_reflect<BiPacket>();

				f_NewPacket->m_InsertElementType = COM_PAK_TYPE_INSERT;
				f_NewPacket->m_ClassType = ag_Get_ClassType(f_vec_Package[1]);
				f_NewPacket->m_Name = f_vec_Package[2];
				f_NewPacket->m_DefaultValue = f_vec_Package[3];
				f_NewPacket->m_ShareID = atoi(f_vec_Package[4].c_str());
				f_NewPacket->m_Element = atoi(f_vec_Package[5].c_str());
				f_NewPacket->m_Operator_Com = f_com;

				if(f_vec_Package.size() >= 7)
					{
					f_NewPacket->m_Comment = f_vec_Package[6];
					}

				m_vec_Packet.push_back(f_NewPacket);
				}
			else if(f_vec_Package[0].compare("Delete") == 0)
				{
				std::string f_Name = f_vec_Package[1];

				std::vector<std::shared_ptr<BiPacket>> f_BiPacket = acSearch_PacketbyName(f_Name);

				for(int f_XY = 0; f_XY < f_BiPacket.size(); f_XY++)
					{
					if(f_BiPacket[f_XY]->m_Name.length() > 0)
						{
						ag_StatusLive(f_ref_CurrentPath, "f_NewPacket");
						std::shared_ptr<BiPacket> f_NewPacket = std::make_shared_reflect<BiPacket>();

						f_NewPacket->m_InsertElementType = COM_PAK_TYPE_DELETE;
						f_NewPacket->m_ClassType = ag_Get_ClassType(f_vec_Package[2]);
						f_NewPacket->m_Name = f_vec_Package[3];
						f_NewPacket->m_DefaultValue = f_vec_Package[4];
						f_NewPacket->m_ShareID = atoi(f_vec_Package[5].c_str());
						f_NewPacket->m_Element = atoi(f_vec_Package[6].c_str());
						f_NewPacket->m_Operator_Com = f_com;

						if(f_vec_Package.size() >= 8)
							{
							f_NewPacket->m_Comment = f_vec_Package[7];
							}

						f_BiPacket[f_XY]->m_vec_Packet_Delete.push_back(f_NewPacket);
						}
					}
				}
			else
				{
				throw;
				}
			}
		}

	for(int f_X = 0; f_X < f_com->m_vec_Qcom.size(); f_X++)
		{
		acParse_GenScript(f_com->m_vec_Qcom[f_X]);
		}
}

std::shared_ptr<Qcom> ag_MotherCom(void)
{
	std::string f_ref_CurrentPath = "ag_MotherCom";

	ag_StatusLive(f_ref_CurrentPath, "g_QcomManager->mam_Qcom");
	std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

	f_com->m_birthcomid = -1;
	f_com->m_BossLVLMin = g_BossLVLMin;
	f_com->m_name = "Ecom";

#if 0
	f_com->m_owner = g_Wallet->GetAdr();
#else
	if(g_WalletOpen == true)
		{
		f_com->m_owner = g_Wallet->GetAdr();
		}
	else
		{
		f_com->m_owner = "";
		}
#endif

	f_com->m_description = "";
	f_com->m_parentcomid = -5;
	f_com->m_rebuild = true;
	f_com->m_Save = true;
	f_com->m_VoteScore = 0;
	f_com->m_Cost = 0.0;
	f_com->m_genScript = nullptr;
	f_com->m_QamID = g_QamID;
	f_com->m_QamLevel = 0;

	return f_com;
}

void QcomManager::acDisplayOn(void)
{
	std::string f_ref_CurrentPath = "QcomManager::acDisplayOn";

	if(m_DisplayOn == false)
		{
		m_DisplayOn = true;
		}

	if(mam_Qcom->m_owner.length() <= 0)
		{
		mam_Qcom->m_owner = g_Wallet->GetAdr();
		}
}

void QcomManager::ac_Wire(int f_QamID, int f_QamLevel)
{
	for(int f_countCom = 0; f_countCom < m_vec_Qcom.size(); f_countCom++)
		{
		std::shared_ptr<Qcom> f_com = m_vec_Qcom[f_countCom];

		//if(f_com->
		}
}

void QcomManager::GenerateBuffers(void)
{
#ifdef OGL_RENDER
	float f_Z_offset = 250.0f;
	float f_Y_offset = 0.0f;

	// Then set up the cube geometry.
    GLfloat vertexPositions[] =
    {
        -360.0f, -200.0f + f_Y_offset, -4.0f + f_Z_offset,
        -360.0f, -200.0f + f_Y_offset,  4.0f + f_Z_offset,
        -360.0f,  200.0f + f_Y_offset, -4.0f + f_Z_offset,
        -360.0f,  200.0f + f_Y_offset,  4.0f + f_Z_offset,
         360.0f, -200.0f + f_Y_offset, -4.0f + f_Z_offset,
         360.0f, -200.0f + f_Y_offset,  4.0f + f_Z_offset,
         360.0f,  200.0f + f_Y_offset, -4.0f + f_Z_offset,
         360.0f,  200.0f + f_Y_offset,  4.0f + f_Z_offset,
    };

    glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
    {
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    glGenBuffers(1, &mVertexColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    short indices[] =
    {
        0, 1, 2, // -x
        1, 3, 2,

        4, 6, 5, // +x
        5, 6, 7,

        0, 5, 1, // -y
        0, 4, 5,

        2, 7, 6, // +y
        2, 3, 7,
              
        0, 6, 4, // -z
        0, 2, 6,
              
        1, 7, 3, // +z
        1, 5, 7,
    };

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#ifdef OGL_NORMALIZED
	glGenBuffers(1, &mVertexNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);
#endif
#endif
}

QcomManager::QcomManager() :
    mWindowWidth(0),
    mWindowHeight(0),
    mDrawCount(0)
{
	std::string f_ref_CurrentPath = "QcomManager::QcomManager";

#ifdef OGL_RENDER
	// Vertex Shader source
    const std::string vs = STRING
		(
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec3 uPos;
		uniform vec4 cameraTrans;
        attribute vec3 aPosition;
		attribute vec3 aNormal;
        attribute vec4 aColor;
		attribute vec2 aUV;
		varying vec3 vPosition;
		varying vec3 vNormal;
        varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			vec4 f_Position = vec4(aPosition, 1.0);

			f_Position = uProjMatrix * uViewMatrix * f_Position;

			vPosition = f_Position.xyz;
			vNormal = aNormal;
			vColor = aColor;
			vUV = aUV;
			
			gl_Position = f_Position;
			}
		);

	// Fragment Shader source
	const std::string fs = STRING
		(
		precision mediump float;
		uniform sampler2D f_texture;
		varying vec3 vPosition;
		varying vec3 vNormal;
		varying vec4 vColor;
		varying vec2 vUV;
		void main()
			{
			//vec4 f_Color = texture2D(f_texture, gl_PointCoord);
			vec4 f_Color = vColor;
			gl_FragColor = f_Color;
			}
		);

	// Vertex Shader source
    const std::string vs_m = STRING
    (
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec4 f_Pos;
		uniform vec4 f_Color;
		uniform float f_Scale;
        attribute vec3 aPosition;
        attribute vec4 aColor;
		varying vec3 vPosition;
        varying vec4 vColor;
        void main()
        {
			vec4 f_Position = vec4(aPosition, 1.0);
			f_Position = uProjMatrix * uViewMatrix * uModelMatrix * f_Position;
			vColor = aColor;
			vColor.r *= f_Color.r;
			vColor.g *= f_Color.g;
			vColor = (0.5 * vec4(0.27, 0.45, 0.2, 1.0)) + (0.5 * vColor);
			vPosition = f_Position.xyz;
			gl_Position = f_Position;
        }
    );

    // Fragment Shader source
    const std::string fs_m = STRING
    (
        precision mediump float;
		//uniform sampler2D f_texture;
		varying vec3 vPosition;
        varying vec4 vColor;
        void main()
        {
			//vec4 f_Color = texture2D(f_texture, gl_PointCoord);

			gl_FragColor = vColor;
        }
    );

	// Vertex Shader source
    const std::string vs_grid = STRING
    (
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec4 f_Pos;
		uniform float f_Scale;
        attribute vec3 aPosition;
        attribute vec4 aColor;
		varying vec3 vPosition;
        varying vec4 vColor;
        void main()
        {
			vec4 f_Position = vec4(aPosition, 1.0);
			f_Position = uProjMatrix * uViewMatrix * uModelMatrix * f_Position;
			f_Position.x += f_Pos.x;
			f_Position.y += f_Pos.y;
			vColor = aColor;
			vPosition = f_Position.xyz;
			gl_Position = f_Position;
			//gl_PointSize = 250.0 * f_Scale;
        }
    );

    // Fragment Shader source
    const std::string fs_grid = STRING
    (
        precision mediump float;
		//uniform sampler2D f_texture;
		varying vec3 pos;
        varying vec4 color;
        void main()
			{
			//vec4 f_Color = texture2D(f_texture, gl_PointCoord);

			float BORDER_WIDTH = 0.1;

			float4 f_White = float4(1.0, 1.0, 1.0, 1.0);
	
			float f_Xsl = input.color.r * 1.0;
			float f_Ysl = input.color.g * 1.0;
			float f_Zsl = input.color.b * 1.0;

			float f_AlphaX = 1.0;
			float f_AlphaY = 1.0;
			float f_Alpha = 1.0;

			if(f_Zsl > 0.0)
				{
				f_Alpha = 1.0;
				}
			else
				{
				if(f_Xsl < 0.1)
					{
					if(f_Ysl < 0.1)
						{
						f_AlphaX = 1.0 - (f_Xsl / BORDER_WIDTH);
						f_AlphaY = 1.0 - (f_Ysl / BORDER_WIDTH);
						f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
						}
					else if(f_Ysl > 0.9)
						{
						f_AlphaX = 1.0 - (f_Xsl / BORDER_WIDTH);
						f_AlphaY = ((f_Ysl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
						f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
						}
					else
						{
						f_Alpha = 1.0 - (f_Xsl / BORDER_WIDTH); 
						}
					}
				else if(f_Xsl > 0.9)
					{
					if(f_Ysl < 0.1)
						{
						f_AlphaX = ((f_Xsl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
						f_AlphaY = 1.0 - (f_Ysl / BORDER_WIDTH);
						f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
						}
					else if(f_Ysl > 0.9)
						{
						f_AlphaX = ((f_Xsl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
						f_AlphaY = ((f_Ysl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
						f_Alpha = (f_AlphaX + f_AlphaY) / 2.0;
						}
					else
						{
						f_Alpha = ((f_Xsl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
						}
					}
				else
					{
					if(f_Ysl < 0.1)
						{
						f_Alpha = 1.0 - (f_Ysl / BORDER_WIDTH);
						}
					else if(f_Ysl > 0.9)
						{
						f_Alpha = ((f_Ysl - (1.0 - BORDER_WIDTH)) / BORDER_WIDTH);
						}
					else
						{
						f_Alpha = 1.0;
						}
					}
				}

			//Starts Inner 0 - 1 <=> Outer 3 - 4

			float f_TrueAlpha = 1.0;

			float4 f_GradientColor0 = float4(0.1, 0.1, 0.1, f_TrueAlpha);
			float4 f_GradientColor1 = float4(0.53, 0.37, 0.9, f_TrueAlpha);
			float4 f_GradientColor2 = float4(0.703, 0.17, 0.3, f_TrueAlpha);
			float4 f_GradientColor3 = float4(0.2, 0.17, 0.4, f_TrueAlpha);
			float4 f_GradientColor4 = float4(0.8, 0.8, 0.8, f_TrueAlpha);
			float f_GradientLength1 = 0.3;
			float f_GradientLength2 = 0.5;
			float f_GradientLength3 = 0.8;

			if((f_Alpha >= 0.0) && (f_Alpha < f_GradientLength1))
				{
				return f_GradientColor0 * (f_GradientColor1 * (f_Alpha / f_GradientLength1));
				}
			else if((f_Alpha > f_GradientLength1) && (f_Alpha < f_GradientLength2))
				{
				return f_GradientColor1 * (f_GradientColor2 * (f_Alpha / f_GradientLength2));
				}
			else if((f_Alpha > f_GradientLength2) && (f_Alpha < f_GradientLength3))
				{
				return f_GradientColor2 * (f_GradientColor3 * (f_Alpha / f_GradientLength3));
				}
			else if((f_Alpha > f_GradientLength3) && (f_Alpha < 1.0))
				{
				return f_GradientColor3 * (f_GradientColor4 * f_Alpha);
				}
			else
				{
				return f_White;
				}
			}
		);

    // Set up the shader and its uniform/attribute locations.
    mProgram = QcomCompileProgram(vs, fs);
    mPositionAttribLocation = glGetAttribLocation(mProgram, "aPosition");
	mNormalAttribLocation = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocation = glGetAttribLocation(mProgram, "aColor");
	mTexCoordAttribLocation = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
    mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
    mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");
	mCameraTranslationUniformLocation = glGetUniformLocation(mProgram, "cameraTrans");

	mProgramM = QcomCompileProgram(vs_m, fs_m);
	mPositionAttribLocationM = glGetAttribLocation(mProgramM, "aPosition");
	//mNormalAttribLocationM = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocationM = glGetAttribLocation(mProgramM, "aColor");
	//mTexCoordAttribLocationM = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocationM = glGetUniformLocation(mProgramM, "uModelMatrix");
	mViewUniformLocationM = glGetUniformLocation(mProgramM, "uViewMatrix");
	mProjUniformLocationM = glGetUniformLocation(mProgramM, "uProjMatrix");

	mProgramGrid = QcomCompileProgram(vs_grid, fs_grid);
	mPositionAttribLocationGrid = glGetAttribLocation(mProgramGrid, "aPosition");
	//mNormalAttribLocationM = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocationGrid = glGetAttribLocation(mProgramGrid, "aColor");
	//mTexCoordAttribLocationM = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocationGrid = glGetUniformLocation(mProgramGrid, "uModelMatrix");
	mViewUniformLocationGrid = glGetUniformLocation(mProgramGrid, "uViewMatrix");
	mProjUniformLocationGrid = glGetUniformLocation(mProgramGrid, "uProjMatrix");

	mPosUniformLocationGrid = glGetUniformLocation(mProgramGrid, "f_Pos");
	mColorUniformLocationGrid = glGetUniformLocation(mProgramM, "f_Color");

	g_Width = 3600;
	g_Height = 1900;

	GenerateBuffers();
#endif

	m_Open = false;

	m_current_X = 0.0f;
	m_current_Y = 0.0f;

	m_current_X_jeb = 0.0f;
	m_current_Y_jeb = 0.0f;
	m_current_Zoom = 0.0f;

	m_PointerCharge = false;

	m_drag_on = false;

	m_drag_X = 0.0f;
	m_drag_Y = 0.0f;

	ag_StatusLive(f_ref_CurrentPath, "f_DecisionManager");

	std::shared_ptr<DecisionManager> f_DecisionManager = std::make_shared_reflect<DecisionManager>();

	ag_StatusLive(f_ref_CurrentPath, "f_DecisionManager->m_Wheel");

	f_DecisionManager->m_Wheel = std::make_shared_reflect<DecisionWheel>();

	f_DecisionManager->acLoad_ApplicationSpecificLegacy();

	g_vec_DecisionsManager.push_back(f_DecisionManager);

	//used to reset the path stack for data naming very important resets to remove any references of the supplied pathstring
	ag_CentraliseCull("DecisionManager::acLoad_ApplicationSpecificLegacy");

	m_DisplayOn = false;

	mam_Qcom = ag_MotherCom();

	m_Qcom = mam_Qcom;

#ifndef OSI_MEM_APP
	ac_Push(m_DisplayOn, f_ref_CurrentPath + g_ref_Div + "m_DisplayOn");
	ac_Push(m_rebuild, f_ref_CurrentPath + g_ref_Div + "m_rebuild");
	ac_Push(m_Open, f_ref_CurrentPath + g_ref_Div + "m_Open");
	ac_Push(m_PointerCharge, f_ref_CurrentPath + g_ref_Div + "m_PointerCharge");
	ac_Push(m_drag_on, f_ref_CurrentPath + g_ref_Div + "m_drag_on");
	ac_Push(m_current_X, f_ref_CurrentPath + g_ref_Div + "m_current_X");
	ac_Push(m_current_Y, f_ref_CurrentPath + g_ref_Div + "m_current_Y");
	ac_Push(m_current_X_jeb, f_ref_CurrentPath + g_ref_Div + "m_current_X_jeb");
	ac_Push(m_current_Y_jeb, f_ref_CurrentPath + g_ref_Div + "m_current_Y_jeb");
	ac_Push(m_drag_X, f_ref_CurrentPath + g_ref_Div + "m_drag_X");
	ac_Push(m_drag_Y, f_ref_CurrentPath + g_ref_Div + "m_drag_Y");
	ac_Push(m_current_Zoom, f_ref_CurrentPath + g_ref_Div + "m_current_Zoom");
	ac_Push(m_ecomSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_ecomSelectedCount");
	ac_Push(m_inputSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_inputSelectedCount");
	ac_Push(m_outputSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_outputSelectedCount");
	ac_Push(m_wireSelectedCount, f_ref_CurrentPath + g_ref_Div + "m_wireSelectedCount");
	ac_Push(mDrawCount, f_ref_CurrentPath + g_ref_Div + "mDrawCount");
	ac_Push(m_QcomCount, f_ref_CurrentPath + g_ref_Div + "m_QcomCount");
	ac_Push(mWindowWidth, f_ref_CurrentPath + g_ref_Div + "mWindowWidth");
	ac_Push(mWindowHeight, f_ref_CurrentPath + g_ref_Div + "mWindowHeight");
	ac_Push(m_preference_ShareID, f_ref_CurrentPath + g_ref_Div + "m_preference_ShareID");
	ac_Push(m_preference_Amt, f_ref_CurrentPath + g_ref_Div + "m_preference_Amt");

	//Management SG
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&QcomManager::acClear);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClearGrid", (void(ecom_base::*)(void))&QcomManager::acClearGrid);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClearGridNew", (void(ecom_base::*)(void))&QcomManager::acClearGridNew);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "GenerateBuffers", (void(ecom_base::*)(void))&QcomManager::GenerateBuffers);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acRenderGrid", (void(ecom_base::*)(void))&QcomManager::acRenderGrid);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_FireLTClick", (void(ecom_base::*)(void))&QcomManager::ac_FireLTClick);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_FireRTClick", (void(ecom_base::*)(void))&QcomManager::ac_FireRTClick);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_DragGrid", (void(ecom_base::*)(void))&QcomManager::ac_DragGrid);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_com_base_v1", (void(ecom_base::*)(void))&QcomManager::ac_com_base_v1);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_LoadAll", (void(ecom_base::*)(void))&QcomManager::ac_LoadAll);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_LoadAll_Append", (void(ecom_base::*)(void))&QcomManager::ac_LoadAll_Append);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_PlushScripts", (void(ecom_base::*)(void))&QcomManager::ac_PlushScripts);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Wire", (void(ecom_base::*)(void))&QcomManager::ac_Wire);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acParse_GenScript", (void(ecom_base::*)(void))&QcomManager::acParse_GenScript);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelectNone", (void(ecom_base::*)(void))&QcomManager::acSelectNone);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHighLightNone", (void(ecom_base::*)(void))&QcomManager::acHighLightNone);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPlace_FunctionCom", (void(ecom_base::*)(void))&QcomManager::acPlace_FunctionCom);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acDisplayOn", (void(ecom_base::*)(void))&QcomManager::acDisplayOn);

#ifdef REFLECT_WORK_EXT
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Find_Com_ByID", (std::shared_ptr<ecom_base>(ecom_base::*)(int))&QcomManager::ac_Find_Com_ByID, 0);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Find_ComWire_ByID", (std::shared_ptr<ecom_base>(ecom_base::*)(int))&QcomManager::ac_Find_ComWire_ByID, 0);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Find_ComInput_ByID", (std::shared_ptr<ecom_base>(ecom_base::*)(int))&QcomManager::ac_Find_ComInput_ByID, 0);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Find_ComOutput_ByID", (std::shared_ptr<ecom_base>(ecom_base::*)(int))&QcomManager::ac_Find_ComOutput_ByID, 0);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Find_WireCom_ByID", (std::shared_ptr<ecom_base>(ecom_base::*)(int))&QcomManager::ac_Find_WireCom_ByID, 0);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Find_Function_ByID", (std::shared_ptr<ecom_base>(ecom_base::*)(int))&QcomManager::ac_Find_Function_ByID, 0);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Find_GenerationScript_ByID", (std::shared_ptr<ecom_base>(ecom_base::*)(int))&QcomManager::ac_Find_GenerationScript_ByID, 0);
#endif

#ifdef OGL_RENDER
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "GenerateBuffersGrid", /*(ecom_base::ControllerMethod_void)*/&QcomManager::GenerateBuffersGrid);
#endif

#ifdef ESL_ACCEPT_VECTOR_CLASSVAR
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSearch_PacketbyName", /*(ecom_base::ControllerMethod_void)*/(ecom_base::vector_argument_slicer)&QcomManager::acSearch_PacketbyName);
#endif
#endif
}

QcomManager::~QcomManager()
{
#ifdef OGL_RENDER
    if(mProgram != 0)
		{
        glDeleteProgram(mProgram);
        mProgram = 0;
		}

	if(mProgramM != 0)
		{
        glDeleteProgram(mProgramM);
        mProgramM = 0;
		}

	if(mProgramGrid != 0)
		{
        glDeleteProgram(mProgramGrid);
        mProgramGrid = 0;
		}

	if(mVertexPositionBuffer)
		{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		}

#ifdef OGL_NORMALIZED
	if(mVertexNormalBuffer)
		{
		glDeleteBuffers(1, &mVertexNormalBuffer);
		}
#endif

	if(mVertexColorBuffer)
		{
		glDeleteBuffers(1, &mVertexColorBuffer);
		}

#ifdef OGL_NORMALIZED
	if(mVertexTexCoordBuffer)
		{
		glDeleteBuffers(1, &mVertexTexCoordBuffer);
		}
#endif

	if(mVertexPositionBufferGrid)
		{
		glDeleteBuffers(1, &mVertexPositionBufferGrid);
		}

#ifdef OGL_NORMALIZED
	if(mVertexNormalBufferGrid)
		{
		glDeleteBuffers(1, &mVertexNormalBufferGrid);
		}
#endif

	if(mVertexColorBufferGrid)
		{
		glDeleteBuffers(1, &mVertexColorBufferGrid);
		}

#ifdef OGL_NORMALIZED
	if(mVertexTexCoordBufferGrid)
		{
		glDeleteBuffers(1, &mVertexTexCoordBufferGrid);
		}
#endif
#endif

	acClear();
}

void QcomManager::acClear(void)
{
	m_vec_Packet.clear();

	for(int f_XY = 0; f_XY < m_vec_Qcom.size(); f_XY++)
		{
		std::shared_ptr<Qcom> f_com = m_vec_Qcom[f_XY];

		f_com->ac_Clear();
		}

	m_vec_Qcom.clear();

	for(int f_XY = 0; f_XY < m_vec_Qcom.size(); f_XY++)
		{
		std::shared_ptr<Qcom_genScript> f_script = m_vec_GenScript[f_XY];

		f_script->ac_Clear();
		}

	m_vec_GenScript.clear();

	for(int f_XY = 0; f_XY < m_vec_Qcom.size(); f_XY++)
		{
		std::shared_ptr<Qcom_eslfunction> f_function = m_vec_ESLFunction[f_XY];

		f_function->ac_Clear();
		}

	m_vec_ESLFunction.clear();

	m_vec_ComWire.clear();
	m_vec_WireCom.clear();

	m_SaveCom.clear();

	m_vec_Input.clear();
	m_vec_Output.clear();

	m_preference_ShareID = 0;
	m_preference_Amt = 0;
}

bool QcomManager::acRenderGrid(void)
{
#ifdef OGL_RENDER
	if(!m_Open)
		{
		return false;
		}

#if 1
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
#else
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);
#endif

#if 0
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
#endif

	if(mProgramM == 0)
		{
		return false;
		}

	glUseProgram(mProgramM);

	//for(int f_Ral = 0; f_Ral < m_vec_Qcom.size(); f_Ral++)
	//	{
	//	std::shared_ptr<Qcom> f_Qcom = m_vec_Qcom[f_Ral];

		BiVector f_Pos(0.0f, 0.0f, 0.0f);
		//BiVector f_VecTo(f_Qcom->m_pos->m_X - f_Pos.m_X, f_Qcom->m_pos->m_Y - f_Pos.m_Y, f_Qcom->m_pos->m_Z - f_Pos.m_Z);
		BiVector f_VecTo(0.0f, 0.0f, 0.0f);

		float f_Dist = f_VecTo.acLength();
		if(f_Dist < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
			glEnableVertexAttribArray(mPositionAttribLocationM);
			glVertexAttribPointer(mPositionAttribLocationM, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexNormalBuffer);
			//glEnableVertexAttribArray(mNormalAttribLocation);
			//glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, /*f_Qcom->*/mVertexColorBuffer);
			glEnableVertexAttribArray(mColorAttribLocationM);
			glVertexAttribPointer(mColorAttribLocationM, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexTexCoordBuffer);
			//glEnableVertexAttribArray(mTexCoordAttribLocation);
			//glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, /*f_Qcom->*/mIndexBuffer);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI / (float)4.0f));
#endif
			glUniformMatrix4fv(mModelUniformLocationM, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocationM, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocationM, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
			glUniform4f(mColorUniformLocationGrid, m_current_X / 720.0f, m_current_Y / 400.0f, 0.0f, 1.0f);
#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
			glDrawElements(GL_TRIANGLES, 2 * 6 * 3, GL_UNSIGNED_SHORT, 0);
			}
		//}

	glLineWidth(2.0f);

	if(mProgramGrid == 0)
		{
		return false;
		}

	glUseProgram(mProgramGrid);

	//for(int f_Ral = 0; f_Ral < m_vec_Qcom.size(); f_Ral++)
	//	{
	//	std::shared_ptr<Qcom> f_Qcom = m_vec_Qcom[f_Ral];

		BiVector f_PosL(0.0f, 0.0f, 0.0f);
		//BiVector f_VecTo(f_Qcom->m_pos->m_X - f_Pos.m_X, f_Qcom->m_pos->m_Y - f_Pos.m_Y, f_Qcom->m_pos->m_Z - f_Pos.m_Z);
		BiVector f_VecToL(0.0f, 0.0f, 0.0f);

		float f_DistL = f_VecToL.acLength();
		if(f_DistL < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBufferGrid);
			glEnableVertexAttribArray(mPositionAttribLocationGrid);
			glVertexAttribPointer(mPositionAttribLocationGrid, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexNormalBuffer);
			//glEnableVertexAttribArray(mNormalAttribLocation);
			//glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, /*f_Qcom->*/mVertexColorBufferGrid);
			glEnableVertexAttribArray(mColorAttribLocationGrid);
			glVertexAttribPointer(mColorAttribLocationGrid, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexTexCoordBuffer);
			//glEnableVertexAttribArray(mTexCoordAttribLocation);
			//glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, /*f_Qcom->*/mIndexBufferGrid);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI / (float)4.0f));
#endif
			glUniformMatrix4fv(mModelUniformLocationGrid, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocationGrid, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocationGrid, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			glUniform4f(mPosUniformLocationGrid, m_current_X_jeb, m_current_Y_jeb, m_current_Zoom, 1.0f);

#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			glDrawElements(GL_LINES, (36 + 20) * 2, GL_UNSIGNED_SHORT, 0);
			}
		//}
#endif

	return true;
}

void QcomManager::acQcom_Frame(void)
{
	/*m_Scan_Frame

	while(m_Scan_Frame)
		if(g_WalletOpen == true)
			{
			if(g_Wallet->m_vec_MainMode[m_IDX] != ECOIN_MODE_COMPRESS)
				{
				mutex_swap.lock();

				if(g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW)
					{
					while(m_sceneRenderer->m_cnt_DIV_Thread < g_Diviner_ThreadCount)
						{
						std::thread f_Thread(&Sample3DSceneRenderer::acGen_GenHesh, m_sceneRenderer.get());

						f_Thread.detach();

						m_sceneRenderer->m_cnt_DIV_Thread++;
						}
					}

				if(g_QcomManager->m_Open == true)
					{
					if(g_RenderHesh == true)
						{
						m_sceneRenderer->acCreateAdmaxDependentResources();

						m_sceneRenderer->RestoreTargetedBuffers();

						g_RenderHesh = false;
						}

					Update();

					try
						{
						if(Render())
							{
							m_deviceResources->Present();
							}
						}
					catch(...)
						{
						int i = 1;
						}
					}
				else
					{
					if(::g_TargetedHesh)
						{
						if(g_RenderHesh == true)
							{
							m_sceneRenderer->acCreateAdmaxDependentResources();

							m_sceneRenderer->RestoreTargetedBuffers();

							Update();

							try
								{
								if(Render())
									{
									m_deviceResources->Present();
									}
								}

							catch(...)
								{
								int i = 1;
								}

							g_RenderHesh = false;
							}
						}
					}

				mutex_swap.unlock();
				}
			else
				{
				std::string f_ref_CurrentPath = g_ref_flow_reset + "ecoinMain::StartRenderLoop";

				m_sceneRenderer->m_IDX = m_IDX;

				while(m_sceneRenderer->m_cnt_SCP_Thread < g_SaveComplete_ThreadCount)
					{
					if(g_LowtonOn == false)
						{
						g_BlockType = ecoin_BlockType::ecoin_Block_Target_SCP;

						g_LowtonOn = true;

						int f_ComID = ::g_QcomManager->m_Qcom->m_ID;
						float f_Cost = ::g_QcomManager->m_Qcom->m_Cost;
						int f_ShareID = ::g_QcomManager->m_Qcom->m_PackageShareID;

						std::shared_ptr<Qcom> f_com = nullptr;

						//if one com selected save only this one as main shall insert
						if(g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com.size() == 1)
							{
							f_com = g_vec_DecisionsManager[0]->m_Wheel->m_vec_Selection_com[0];

							f_ComID = f_com->m_ID;

							if(f_com->m_Cost > 0.0f)
								{
								f_Cost = f_com->m_Cost;
								}
							}

						g_classLMap->m_Patched = false;

						ag_StatusLive(f_ref_CurrentPath, "g_Lowton");
						g_Lowton = std::make_shared_reflect<Cube::CubeHESH>(g_classLMap->m_ADMAX, g_classLMap->m_ADMAX, g_classLMap->m_ADMAX, g_CountLM);
						ag_StatusLive(f_ref_CurrentPath, "g_Lowton_Collection");
						g_Lowton_Collection = std::make_shared_reflect<classCollection>();
						ag_StatusLive(f_ref_CurrentPath, "g_LowtonHash");
						g_LowtonHash = std::make_shared_reflect<Cube::CubeHASH_originstring>();

						m_sceneRenderer->m_DB_AccessLock.lock();

						g_JobID = g_Wallet->acGet_JobID(m_IDX);

						float f_Difficulty = 0.0f;

						std::string f_ShareLedgerPrimer = g_classLMap->acLenseMapHash();

						//ECN::Hesh...Check Reaquire Sending BlockHesh Elements
						char* query = ag_ClearChar(512); // AND comid = %i , f_ComID when QamLoadAll implemented
						::sprintf(query, "SELECT id, bckred, bckgreen, bckblue FROM share WHERE shareledger = '%s' ORDER BY score DESC", f_ShareLedgerPrimer.c_str());
						g_SafeL[0]->acSelectCommand(query, 2, false);
						delete query;

						if(g_Schedular[0]->acEntry(0)[0].at(0) != '0')
							{
							g_ShareID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());

							Cube::BiVector f_BCK(atof(g_Schedular[0]->acEntry(0)[1].c_str()), atof(g_Schedular[0]->acEntry(0)[2].c_str()), atof(g_Schedular[0]->acEntry(0)[3].c_str()));

							char* cubequery = ag_ClearChar(3000);
							::sprintf(cubequery, "SELECT id, vert1x, vert1y, vert1z, vert2x, vert2y, vert2z, vert3x, vert3y, vert3z, vert4x, vert4y, vert4z, vert5x, vert5y, vert5z, vert6x, vert6y, vert6z, vert7x, vert7y, vert7z, vert8x, vert8y, vert8z, vert1r, vert1g, vert1b, vert2r, vert2g, vert2b, vert3r, vert3g, vert3b, vert4r, vert4g, vert4b, vert5r, vert5g, vert5b, vert6r, vert6g, vert6b, vert7r, vert7g, vert7b, vert8r, vert8g, vert8b, shareid, jobid, eslid, targetid, eslcode, difficulty FROM cube WHERE shareid = %i ORDER BY eslid ASC#", g_ShareID);
							g_SafeL[0]->acSelectCommand(cubequery, false, false);
							delete cubequery;

							int f_adCount = 0;

							int f_CountLM = g_CountLM;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_adCount = 0;
								}
							else
								{
								f_adCount = g_Schedular[0]->acEntrySize();

								f_CountLM = atoi(g_Schedular[0]->acEntry(0)[52].c_str());
								}

							//CountLM Measurement Count Value
							g_CountLM = f_CountLM;

							//ECN::f_adCount
							g_BicycleContainer[0]->m_ADMAX = f_adCount;
							g_BicycleContainer[0]->m_ADHIGH = f_adCount;
							g_BicycleContainer[0]->m_ADLOW = f_adCount;

							//convert ADMAX to scoreand maxvote
							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)((g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX) * ECOIN_REWARD_ON) /*ECN_OPER_REWARD*//* + ECOIN_SCP_INSTANT_BONUS);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, ECOIN_REWARD_ON /*ECN_OPER_REWARD*//* + ECOIN_SCP_INSTANT_BONUS);

							f_Difficulty = (((float)g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX)) * ECOIN_SCP_DEFAULT_BASEDIFF;

							ag_StatusLive(f_ref_CurrentPath, "f_Heshr");
							std::shared_ptr<Cube::CubeHESH> f_Heshr = ::std::make_shared_reflect<Cube::CubeHESH>(f_adCount, f_adCount, f_adCount, f_CountLM);

							for(int f_Int = 0; f_Int < f_adCount; f_Int++)
								{
								ag_StatusLive(f_ref_CurrentPath, "f_Bike");
								std::shared_ptr<Cube::CubeBicycle> f_Bike = ::std::make_shared_reflect<Cube::CubeBicycle>();

								f_Bike->acClear();

								for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
									{
									ag_StatusLive(f_ref_CurrentPath, "f_Vector");
									std::shared_ptr<Cube::BiVector> f_Vector = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[0]->acEntry(f_Int)[1 + (f_Int2 * 3)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 1)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[1 + ((f_Int2 * 3) + 2)].c_str()));

									f_Bike->vec_Vertex.push_back(f_Vector);
									}

								f_Bike->vec_Color.clear();

								for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
									{
									ag_StatusLive(f_ref_CurrentPath, "f_Color");
									std::shared_ptr<Cube::BiVector> f_Color = ::std::make_shared<Cube::BiVector>((float)atof(g_Schedular[0]->acEntry(f_Int)[25 + (f_Int3 * 3)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 1)].c_str()), (float)atof(g_Schedular[0]->acEntry(f_Int)[25 + ((f_Int3 * 3) + 2)].c_str()));

									f_Bike->vec_Color.push_back(f_Color);
									}

								ag_StatusLive(f_ref_CurrentPath, "f_Element");
								std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Bike);

								g_Lowton_Collection->m_vec_Element.push_back(f_Element);
								g_Lowton_Collection->m_idx_vec_Element++;

								f_Heshr->vec_Bicycle.push_back(f_Bike);
								}

							  ////////////
							 // HESH   //
							//        //
							int f_PortCNTR = 0;
							f_Heshr->m_adIndex.clear();

							while(f_Heshr->m_adIndex.size() < f_adCount)
								{
								f_Heshr->m_adIndex.push_back(f_PortCNTR);
								f_PortCNTR++;
								}

							f_Heshr->m_bckred = f_BCK.m_X;
							f_Heshr->m_bckgreen = f_BCK.m_Y;
							f_Heshr->m_bckblue = f_BCK.m_Z;

							ag_FreshOn<float>(g_Wallet->m_vec_bckred, m_IDX, f_Heshr->m_bckred);
							ag_FreshOn<float>(g_Wallet->m_vec_bckgreen, m_IDX, f_Heshr->m_bckgreen);
							ag_FreshOn<float>(g_Wallet->m_vec_bckblue, m_IDX, f_Heshr->m_bckblue);

							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)f_Difficulty + 100.0f);
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, f_CountLM);
							ag_FreshOn<float>(g_Wallet->m_vec_difficulty, m_IDX, (float)ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, ecoin_BlockType::ecoin_Block_Target_SCP);
							ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_ShareLedgerPrimer);
							ag_FreshOn<float>(g_Wallet->m_vec_price, m_IDX, f_Cost);
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);

							ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, -1);

							f_Heshr->ac_IsOK();

							g_Once = true;
							g_Lowton = f_Heshr;
							g_TargetedHesh = f_Heshr;
							g_RenderHesh = true;

							//JOB Mainly
							char* jobquery = ag_ClearChar(512);
							::sprintf(jobquery, "SELECT id, blocktype, eslcode, pledgetype, pledgemax, targetbreach, owner, scoremax, markmax, markmin, reward, rewardid, startbreach, blockid, dated FROM job WHERE blockid = (SELECT id FROM block WHERE ((shareid = %i) AND (jobid = %i))) ORDER BY dated DESC LIMIT 1", g_ShareID, g_JobID);
							g_SafeL[0]->acSelectCommand(jobquery, 2, false);
							delete jobquery;
						
							int f_jobLCount = 0;

							if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
								{
								f_jobLCount = 0;
								}
							else
								{
								f_jobLCount = g_Schedular[0]->acEntrySize();
								}

							//ECN::Stat::: f_jobLCount
							if(f_jobLCount > 0)
								{
								ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, g_BlockType);
								ag_FreshOn<int>(g_Wallet->m_vec_scoremax, m_IDX, atof(g_Schedular[0]->acEntry(0)[7].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmax, m_IDX, atof(g_Schedular[0]->acEntry(0)[8].c_str()));
								ag_FreshOn<float>(g_Wallet->m_vec_markmin, m_IDX, atof(g_Schedular[0]->acEntry(0)[9].c_str()));
								ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_IDX, 0.0f);
								ag_FreshOn<int>(g_Wallet->m_vec_pledgetype, m_IDX, atoi(g_Schedular[0]->acEntry(0)[3].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_maxpledge, m_IDX, atoi(g_Schedular[0]->acEntry(0)[4].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_targetbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[5].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_startbreach, m_IDX, atoi(g_Schedular[0]->acEntry(0)[12].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_IDX, g_Wallet->GetAdr());
								ag_FreshOn<int>(g_Wallet->m_vec_jobboardid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_IDX, atoi(g_Schedular[0]->acEntry(0)[13].c_str()));
								ag_Freshanon<std::string>(g_Wallet->m_vec_eslcode, m_IDX, g_TypeName);
								ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_ShareID);

								g_Found_Msg = 15;

								char* f_Chr = ag_ClearChar(2500);
								::sprintf(f_Chr, "Group Founder onSHR#(...%i) Job#(...%i)!", g_ShareID, g_Wallet->m_vec_jobboardid[m_IDX]);
								std::string f_ChrString = f_Chr;
								delete f_Chr;

								g_Found_Text = f_ChrString;

								if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
									{
									std::vector<float> f_vec_jobvar_value;
									std::vector<std::string> f_vec_jobvar_groupname;
									std::vector<std::string> f_vec_jobvar_name;
									std::vector<int> f_vec_jobvar_index;
									std::vector<int> f_vec_jobvarid;
									std::vector<bool> f_vec_jobvar_save;
									std::vector<bool> f_vec_jobvar_textupdate;

									f_vec_jobvar_value.push_back(18.57f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("MATCH_MIXIN");
									f_vec_jobvar_index.push_back(0);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(0.0143f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("MATCH_THRESH");
									f_vec_jobvar_index.push_back(1);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(1.341f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("MATCH_THRESH_UP");
									f_vec_jobvar_index.push_back(2);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(12.55f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("COMPARE_QUALITY");
									f_vec_jobvar_index.push_back(3);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(33.7357f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("COMPARE_THRESH");
									f_vec_jobvar_index.push_back(4);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									f_vec_jobvar_value.push_back(98.0f);
									f_vec_jobvar_groupname.push_back("FRMESH BaseDefaults");
									f_vec_jobvar_name.push_back("LOWTON_STORAGE");
									f_vec_jobvar_index.push_back(5);
									f_vec_jobvarid.push_back(0);
									f_vec_jobvar_save.push_back(false);
									f_vec_jobvar_textupdate.push_back(false);

									g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
									g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
									g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
									g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
									g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
									g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
									g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

									g_Wallet->m_vec_jobvar_current_index.push_back(0);
									}
								else
									{
									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(18.57f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("MATCH_MIXIN");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(0.0143f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("MATCH_THRESH");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(1);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(1.341f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("MATCH_THRESH_UP");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(2);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(12.55f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("COMPARE_QUALITY");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(3);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(33.7357f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("COMPARE_THRESH");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(4);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);

									g_Wallet->m_vec_jobvar_value[m_IDX].push_back(98.0f);
									g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back("FRMESH BaseDefaults");
									g_Wallet->m_vec_jobvar_name[m_IDX].push_back("LOWTON_STORAGE");
									g_Wallet->m_vec_jobvar_index[m_IDX].push_back(5);
									g_Wallet->m_vec_jobvarid[m_IDX].push_back(0);
									g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
									g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
									}

								char* jobvarquery = ag_ClearChar(512);
								::sprintf(jobvarquery, "SELECT id, name, groupname, value, dated FROM jobvar WHERE jobid = %i ORDER BY dated DESC", atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
								g_SafeL[0]->acSelectCommand(jobvarquery, 2, false);
								delete jobvarquery;
						
								int f_jobvarLCount = 0;

								if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
									{
									f_jobvarLCount = 0;
									}
								else
									{
									f_jobvarLCount = g_Schedular[0]->acEntrySize();
									}

								//ECN::Stat::: f_jobvarLCount
								if(f_jobvarLCount > 0)
									{
									if(m_IDX >= g_Wallet->m_vec_jobvar_current_index.size())
										{
										std::vector<float> f_vec_jobvar_value;
										std::vector<std::string> f_vec_jobvar_groupname;
										std::vector<std::string> f_vec_jobvar_name;
										std::vector<int> f_vec_jobvar_index;
										std::vector<int> f_vec_jobvarid;
										std::vector<bool> f_vec_jobvar_save;
										std::vector<bool> f_vec_jobvar_textupdate;

										for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
											{
											f_vec_jobvar_value.push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
											f_vec_jobvar_groupname.push_back(g_Schedular[0]->acEntry(0)[2]);
											f_vec_jobvar_name.push_back(g_Schedular[0]->acEntry(0)[1]);
											f_vec_jobvar_index.push_back(f_Jet);
											f_vec_jobvarid.push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
											f_vec_jobvar_save.push_back(false);
											f_vec_jobvar_textupdate.push_back(false);
											}

										g_Wallet->m_vec_jobvar_value.push_back(f_vec_jobvar_value);
										g_Wallet->m_vec_jobvar_groupname.push_back(f_vec_jobvar_groupname);
										g_Wallet->m_vec_jobvar_name.push_back(f_vec_jobvar_name);
										g_Wallet->m_vec_jobvar_index.push_back(f_vec_jobvar_index);
										g_Wallet->m_vec_jobvarid.push_back(f_vec_jobvarid);
										g_Wallet->m_vec_jobvar_save.push_back(f_vec_jobvar_save);
										g_Wallet->m_vec_jobvar_textupdate.push_back(f_vec_jobvar_textupdate);

										g_Wallet->m_vec_jobvar_current_index.push_back(0);
										}
									else
										{
										g_Wallet->m_vec_jobvar_value[m_IDX].clear();
										g_Wallet->m_vec_jobvar_groupname[m_IDX].clear();
										g_Wallet->m_vec_jobvar_name[m_IDX].clear();
										g_Wallet->m_vec_jobvar_index[m_IDX].clear();
										g_Wallet->m_vec_jobvarid[m_IDX].clear();
										g_Wallet->m_vec_jobvar_save[m_IDX].clear();
										g_Wallet->m_vec_jobvar_textupdate[m_IDX].clear();

										g_Wallet->m_vec_jobvar_current_index[m_IDX] = 0;

										for(int f_Jet = 0; f_Jet < f_jobvarLCount; f_Jet++)
											{
											g_Wallet->m_vec_jobvar_value[m_IDX].push_back(atof(g_Schedular[0]->acEntry(0)[3].c_str()));
											g_Wallet->m_vec_jobvar_groupname[m_IDX].push_back(g_Schedular[0]->acEntry(0)[2]);
											g_Wallet->m_vec_jobvar_name[m_IDX].push_back(g_Schedular[0]->acEntry(0)[1]);
											g_Wallet->m_vec_jobvar_index[m_IDX].push_back(f_Jet);
											g_Wallet->m_vec_jobvarid[m_IDX].push_back(atoi(g_Schedular[0]->acEntry(0)[0].c_str()));
											g_Wallet->m_vec_jobvar_save[m_IDX].push_back(false);
											g_Wallet->m_vec_jobvar_textupdate[m_IDX].push_back(false);
											}
										}
									}
								}
							else
								{
								g_Wallet->acSet_IDX(m_IDX);
								g_Wallet->acSave_currentJob();

								g_Found_Msg = 15;

								char* f_Chr = ag_ClearChar(2500);
								::sprintf(f_Chr, "Group Founder onSHR#(...%i) Job#(...%i)!", g_ShareID, g_Wallet->m_vec_jobboardid[m_IDX]);
								std::string f_ChrString = f_Chr;
								delete f_Chr;

								g_Found_Text = f_ChrString;
								}
							}
						else
							{
							//CountLM Measurement Count Value
							int f_CountLM = g_CountLM;

							//ECN::f_adCount
							g_BicycleContainer[0]->m_ADMAX = 0;
							g_BicycleContainer[0]->m_ADHIGH = 0;
							g_BicycleContainer[0]->m_ADLOW = 0;

							//convert ADMAX to score and maxvote
							ag_FreshOn<float>(g_Wallet->m_vec_score, m_IDX, (float)ECOIN_SCP_INSTANT_BONUS);
							ag_FreshOn<float>(g_Wallet->m_vec_maxvote, m_IDX, ECOIN_REWARD_ON /*ECN_OPER_REWARD*//* + ECOIN_SCP_INSTANT_BONUS);

							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)ECOIN_SCP_INSTANT_BONUS);
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, f_CountLM);
							ag_FreshOn<float>(g_Wallet->m_vec_difficulty, m_IDX, (float)ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_FreshOn<int>(g_Wallet->m_vec_blocktype, m_IDX, ecoin_BlockType::ecoin_Block_Target_SCP);
							ag_Freshanon<std::string>(g_Wallet->m_vec_blockledger, m_IDX, "EMPTY");
							ag_FreshOn<float>(g_Wallet->m_vec_price, m_IDX, f_Cost);
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);

							ag_Freshanon<int>(g_Wallet->m_vec_jobboardid, m_IDX, -1);

							char* g_sharevalue[25];

							for(int f_Count = 0; f_Count < 25; f_Count++)
								{
								g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
								}

							::sprintf(g_sharevalue[0], "%i", (int)g_Wallet->m_vec_mark[m_IDX]);
							::sprintf(g_sharevalue[1], "%f", (float)g_Wallet->m_vec_mark[m_IDX]);
							::sprintf(g_sharevalue[2], "%i", 1);
							::sprintf(g_sharevalue[3], "%i", 3);
							::sprintf(g_sharevalue[4], "%i", g_JobID);
							::sprintf(g_sharevalue[5], "%i", g_Wallet->m_vec_jobboardid[m_IDX]);
							::sprintf(g_sharevalue[6], "%i", g_Wallet->m_vec_eslid[m_IDX]);
							::sprintf(g_sharevalue[7], "%i", g_Wallet->m_vec_targetid[m_IDX]);
							::sprintf(g_sharevalue[8], "%s", g_TypeName.c_str());
							::sprintf(g_sharevalue[9], "%f", g_Wallet->m_vec_difficulty[m_IDX]);
							::sprintf(g_sharevalue[10], "%f", g_Wallet->m_vec_score[m_IDX]);
							::sprintf(g_sharevalue[11], "%f", g_Wallet->m_vec_maxvote[m_IDX]);
							::sprintf(g_sharevalue[12], "%s", f_ShareLedgerPrimer.c_str());
							::sprintf(g_sharevalue[13], "%s", g_Wallet->m_vec_blockledger[m_IDX].c_str());
							::sprintf(g_sharevalue[14], "%s", g_Wallet->GetAdr().c_str());
							::sprintf(g_sharevalue[15], "%f", 0.5f);
							::sprintf(g_sharevalue[16], "%f", 0.4f);
							::sprintf(g_sharevalue[17], "%f", 0.97f);
							::sprintf(g_sharevalue[18], "%i", g_CurrentComID);
							::sprintf(g_sharevalue[19], "%f", g_Wallet->m_Reward);
							::sprintf(g_sharevalue[20], "%f", 0.0f);
							::sprintf(g_sharevalue[21], "%f", 0.0f);
							::sprintf(g_sharevalue[22], "%f", ECN_TX_FEE);
							::sprintf(g_sharevalue[23], "%f", g_Wallet->m_vec_price[m_IDX]);
							::sprintf(g_sharevalue[24], "%i", g_BlockType);

							g_ShareID = g_SafeL[0]->Insert("share", (const char **)g_sharefield, (const char **)g_sharevalue, 25, 2, false);

							for(int f_Count = 0; f_Count < 25; f_Count++)
								{
								free(g_sharevalue[f_Count]);
								}

							  ///////////////
							 // Add Share //
							///////////////
							char* balancequery = ag_ClearChar(1000);
							::sprintf(balancequery, "Call acTopUpPeerBalanceAdvance(%i, %i)", g_ShareID, g_JobID);
							g_SafeL[0]->acSelectCommand(balancequery, 2, false);
							delete balancequery;

							std::shared_ptr<ShareContainerExt> f_PG = ag_SelectPeerGraphExt(g_JobID, 0, g_ShareID, g_CurrentShareOffset, g_PEER);

							g_CurrentShareOffset = f_PG->m_espo_ShareOffset;
							g_CurrentShareOffsetMAX = f_PG->m_espo_SharesOnPeerCount;
							g_PEER = f_PG->m_espo_Peer;
							g_PEERCNT = f_PG->m_espo_PeerCount;
							g_PEERMAX = f_PG->m_espo_PeerCount;

							g_JobID = g_Wallet->acGet_JobID(m_IDX);

							g_Wallet->acSet_IDX(m_IDX);
							g_Wallet->acSave_currentJob();

							g_Found_Msg = 15;

							char* f_Chr = ag_ClearChar(2500);
							::sprintf(f_Chr, "Group Founder onSHR#(...%i) Job#(...%i)!", g_ShareID, g_Wallet->m_vec_jobboardid[m_IDX]);
							std::string f_ChrString = f_Chr;
							delete f_Chr;

							g_Found_Text = f_ChrString;

							 ///////////////////////////////////////////////////////////////////////
							// Toss share calculation transaction onto next block/jobid as yield //
							ag_addGenesisTracking(g_ShareID, ecoin_BlockType::ecoin_Block_Target_SCP, 0);

							 /////////////////////////////////////////////////
							// Update Current SCP-Share according to Block //
							std::string f_Freshanon = "GenesisBlock";

							ag_Freshanon<std::string>(g_Wallet->m_vec_prevblock, m_IDX, f_Freshanon);

							std::string f_previousblock = g_Wallet->m_vec_prevblock[m_IDX];

							 /////////////////////
							// Gather StepHash //
							std::shared_ptr<Cube::CubeResults> f_Res = ag_GatherTransactions(g_JobID, m_IDX);

							 /////////////
							// TX Hash //
							std::string f_tx = f_Res->m_Result;

							 //////////////
							// JOB Hash //
							std::string f_job = f_tx + f_previousblock;

							 //////////////
							// job-hash //
							std::string f_TXJob_OutputHash = "";

							g_hasha.init(); //reset hasher state
							g_hasha.process(f_job.begin(), f_job.end());
							g_hasha.finish();
							picosha2::get_hash_hex_string(g_hasha, f_TXJob_OutputHash);

							ag_FreshOn<int>(g_Wallet->m_vec_mark, m_IDX, (int)100 * (int)((float)g_BicycleContainer[0]->m_ADMAX / (float)g_classLMap->m_ADMAX));
							ag_FreshOn<int>(g_Wallet->m_vec_eslid, m_IDX, g_CountLM);
							ag_Freshanon<float>(g_Wallet->m_vec_difficulty, m_IDX, ECOIN_SCP_DEFAULT_BASEDIFF);
							ag_Freshanon<int>(g_Wallet->m_vec_blocktype, m_IDX, ecoin_BlockType::ecoin_Block_Target_SCP);
							ag_FreshOn<std::string>(g_Wallet->m_vec_blockledger, m_IDX, f_TXJob_OutputHash);
							
							ag_FreshOn<int>(g_Wallet->m_vec_targetid, m_IDX, g_classLMap->m_ADMAX);
							}

						m_sceneRenderer->m_DB_AccessLock.unlock();
						}

					std::thread f_Thread(&Sample3DSceneRenderer::acSaveCompletePublish_GenHesh_Upper_Reflection, m_sceneRenderer.get());

					f_Thread.detach();

					m_sceneRenderer->m_cnt_SCP_Thread++;
					}

				mutex_swap.lock();

				if(g_TargetedHesh)
					{
					if(g_RenderHesh == true)
						{
						m_sceneRenderer->acCreateAdmaxDependentResources();

						m_sceneRenderer->RestoreTargetedBuffers();

						Update();

						try
							{
							if(Render() == true)
								{
								m_deviceResources->Present();
								}
							}
						catch(...)
							{
							int i = 1;
							}

						g_RenderHesh = false;
						}
					}

				mutex_swap.unlock();
				}*/
}

void QcomManager::ac_FireLTClick(void)
{
	ag_Click("QcomManager::ac_FireLTClick");
}

void QcomManager::ac_FireRTClick(void)
{
	ag_Click("QcomManager::ac_FireRTClick");
}

float whl_fp(float f_currA, float f_div)
{
	while(f_currA > f_div)
		{
		f_currA -= f_div;
		}

	return f_currA;
}

float whl_fpmin(float f_currA, float f_div)
{
	while(f_currA < f_div)
		{
		f_currA += f_div;
		}

	return f_currA;
}

void QcomManager::ac_DragGrid(float f_X, float f_Y)
{
	if(!m_drag_on)
		{
		m_drag_X = f_X;
		m_drag_Y = f_Y;
		m_drag_on = true;
		}
	else
		{
		m_current_X -= ((f_X - m_drag_X) / (3600.0f / 720.0f)) / 8.0f;
		m_current_Y -= ((f_Y - m_drag_Y) / (1900.0f / 400.0f)) / 8.0f;
		m_drag_X = f_X;
		m_drag_Y = f_Y;
 		m_drag_on = true;
		}
}

void QcomManager::ac_com_base_v1(bool f_memOnly)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_com_base_v1";
	ag_StatusLive(f_ref_CurrentPath, "f_com");
	std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();
}

std::shared_ptr<Qcom> QcomManager::ac_Find_Com_ByID(int f_ID)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_Find_Com_ByID";

	for(int f_XY = 0; f_XY < m_vec_Qcom.size(); f_XY++)
		{
		if(m_vec_Qcom[f_XY]->m_ID == f_ID)
			{
			return m_vec_Qcom[f_XY];
			}
		}

	return nullptr;
}

std::shared_ptr<WireCom> QcomManager::ac_Find_WireCom_ByID(int f_ID)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_Find_WireCom_ByID";

	for(int f_XY = 0; f_XY < m_vec_WireCom.size(); f_XY++)
		{
		if(m_vec_WireCom[f_XY]->m_ID == f_ID)
			{
			return m_vec_WireCom[f_XY];
			}
		}

	return nullptr;
}

std::shared_ptr<QcomWire> QcomManager::ac_Find_ComWire_ByID(int f_ID)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_Find_ComWire_ByID";

	for(int f_XY = 0; f_XY < m_vec_ComWire.size(); f_XY++)
		{
		if(m_vec_ComWire[f_XY]->m_ID == f_ID)
			{
			return m_vec_ComWire[f_XY];
			}
		}

	return nullptr;
}

std::shared_ptr<QcomInput> QcomManager::ac_Find_ComInput_ByID(int f_ID)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_Find_ComInput_ByID";

	for(int f_XY = 0; f_XY < m_vec_Input.size(); f_XY++)
		{
		if(m_vec_Input[f_XY]->m_ID == f_ID)
			{
			return m_vec_Input[f_XY];
			}
		}

	return nullptr;
}

std::shared_ptr<QcomOutput> QcomManager::ac_Find_ComOutput_ByID(int f_ID)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_Find_ComOutput_ByID";

	for(int f_XY = 0; f_XY < m_vec_Output.size(); f_XY++)
		{
		if(m_vec_Output[f_XY]->m_ID == f_ID)
			{
			return m_vec_Output[f_XY];
			}
		}

	return nullptr;
}

std::shared_ptr<Qcom_eslfunction> QcomManager::ac_Find_Function_ByID(int f_ID)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_Find_Function_ByID";

	for(int f_XY = 0; f_XY < m_vec_ESLFunction.size(); f_XY++)
		{
		if(m_vec_ESLFunction[f_XY]->m_ID == f_ID)
			{
			return m_vec_ESLFunction[f_XY];
			}
		}

	return nullptr;
}

std::shared_ptr<Qcom_genScript> QcomManager::ac_Find_GenerationScript_ByID(int f_ID)
{
	std::string f_ref_CurrentPath = "QcomManager::ac_Find_GenerationScript_ByID";

	for(int f_XY = 0; f_XY < m_vec_GenScript.size(); f_XY++)
		{
		if(m_vec_GenScript[f_XY]->m_ID == f_ID)
			{
			return m_vec_GenScript[f_XY];
			}
		}

	return nullptr;
}

void DecisionManager::acFrame(void)
{
	//frame instantiation
	time_t f_keepTime;
	time(&f_keepTime);

	while(0)
		{
		time_t f_CurrentTime;
		time(&f_CurrentTime);

		int f_DoubleInt = f_CurrentTime - f_keepTime;

#if 0
		if(g_QamStatus > QAM_STATUS_NULL)
			{
			if(f_DoubleInt >= 60)
				{
				time(&f_keepTime);

				bool f_Update = false;

				int f_DecisionComCount = m_vec_DecisionCom.size();

				mutex_qcomdb.lock();

				acLoad_DecisionCom(g_QamID);

				mutex_qcomdb.unlock();

				for(int f_XY = f_DecisionComCount; f_XY < m_vec_DecisionCom.size(); f_XY++)
					{
					std::shared_ptr<DecisionCom> f_decisioncom = m_vec_DecisionCom[f_XY];

					std::shared_ptr<BiDecisionQ> f_DecisionQ = f_decisioncom->acGen_DecisionQ_fromDecisionCom();

					m_vec_DecisionQ.push_back(f_DecisionQ);

					g_QcomManager->ac_LoadAll_Append(f_decisioncom->m_QamInfo->m_originalsourceqamid);

					f_Update = true;
					}

#if 0
				for(int f_XY = 0; f_XY < g_vec_DecisionsManager[0]->m_vec_DecisionQ.size(); f_XY++)
					{
					std::shared_ptr<BiDecisionQ> f_Q = g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_XY];

					std::shared_ptr<DecisionCom> f_Deccom = std::make_shared_reflect<DecisionCom>();

					f_Deccom->acGen_DecisionCom_fromDecisionQ(f_Q);

					f_Deccom->ac_Save();

					f_Update = true;
					}
#endif

				if(f_Update == true)
					{
					std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

					if(f_WHL->m_DecisionIndex >= (g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHL->m_SelectionIndex]->m_vec_DecisionA.size() - 1))
						{
						g_swapChainPanel.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [=]()
							{
							std::shared_ptr<DecisionWheel> f_WHLS = g_vec_DecisionsManager[0]->m_Wheel;

							winrt::Windows::UI::Xaml::Controls::TextBlock f_decisionsTitleTextBlock = g_swapChainPanel.FindName(StrUsingStr("decisionsTitle")).as<winrt::Windows::UI::Xaml::Controls::TextBlock>();
							winrt::Windows::UI::Xaml::Controls::Button f_decisionsButtonTextBlock = g_swapChainPanel.FindName(StrUsingStr("decisionsButton")).as<winrt::Windows::UI::Xaml::Controls::Button>();
							winrt::Windows::UI::Xaml::Controls::TextBox f_decisionsB1TextBox = g_swapChainPanel.FindName(StrUsingStr("decisionB1textBox")).as<winrt::Windows::UI::Xaml::Controls::TextBox>();

							f_decisionsTitleTextBlock.Text(StrUsingStr(g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHLS->m_SelectionIndex]->m_vec_DecisionA[f_WHLS->m_DecisionIndex]->m_TitleText));
							f_decisionsB1TextBox.Text(StrUsingStr(g_vec_DecisionsManager[0]->m_vec_DecisionQ[f_WHLS->m_SelectionIndex]->m_vec_DecisionA[f_WHLS->m_DecisionIndex]->m_ObjectNameOverride));
							f_decisionsButtonTextBlock.Content(box_value(StrUsingStr("Apply")));
							});
						}
					}
				}
			}

		Sleep(3500);
#endif
		}
}

void DecisionCom::acInsert_Mod_Target(int f_Type, std::string f_Mod_Target)
{
	m_Selected_Mod_Index = m_Mod_Type.size();
	m_Mod_Type.push_back(f_Type);
	m_Mod_Target.push_back(f_Mod_Target);
}

void DecisionCom::acSelect_Mod_Target(std::string f_Mod_Target, int f_Index)
{
	if((f_Index > 0) && (f_Index < m_Mod_Name.size()))
		{
		m_Selected_Mod_Index = f_Index;
		}
	else
		{
		for(int f_XY = 0; f_XY < m_Mod_Name.size(); f_XY++)
			{
			if(m_Mod_Target[f_XY].compare(f_Mod_Target) == 0)
				{
				m_Selected_Mod_Index = f_XY;
				f_XY = m_Mod_Type.size();
				}
			}
		}
}

void DecisionCom::acComplete_Mod_Target(std::string f_Mod_Name, int f_Index)
{
	if((f_Index > 0) && (f_Index < m_Mod_Name.size()))
		{
		m_Selected_Mod_Index = f_Index;
		acComplete_Mod_Target(f_Mod_Name);
		}
	else
		{
		m_Mod_Name[m_Selected_Mod_Index].push_back(f_Mod_Name);
		}
}

void DecisionCom::acComplete_Mod_Target(std::string f_Mod_Name, std::string f_Mod_Target)
{
	acSelect_Mod_Target(f_Mod_Target);

	acComplete_Mod_Target(f_Mod_Name);
}

std::string DecisionCom::acGet_Type(void)
{
	std::string f_StringResult;
	f_StringResult.clear();

	for(int f_XY = 0; f_XY < m_Mod_Type.size(); f_XY++)
		{
		char* f_Char = new char[256];

		sprintf(f_Char, "%i...", m_Mod_Type[f_XY]);

		f_StringResult += f_Char;

		delete[] f_Char;
		}

	return f_StringResult;
}

std::string DecisionCom::acGet_Target(void)
{
	std::string f_StringResult;
	f_StringResult.clear();

	for(int f_XY = 0; f_XY < m_Mod_Target.size(); f_XY++)
		{
		char* f_Char = new char[256];

		sprintf(f_Char, "%s...", m_Mod_Target[f_XY].c_str());

		f_StringResult += f_Char;

		delete[] f_Char;
		}

	return f_StringResult;
}

std::string DecisionCom::acGet_Name(void)
{
	std::string f_StringResult;
	f_StringResult.clear();

	for(int f_XY = 0; f_XY < m_Mod_Name.size(); f_XY++)
		{
		for(int f_Jet = 0; f_Jet < m_Mod_Name[f_XY].size(); f_Jet++)
			{
			char* f_Char = new char[256];

			sprintf(f_Char, "%s...", m_Mod_Name[f_XY][f_Jet].c_str());

			f_StringResult += f_Char;

			delete[] f_Char;
			}
		}

	return f_StringResult;
}

void DecisionCom::acSet_Type(std::string f_Type_Buffer)
{
	m_Mod_Type.clear();

	std::string f_Carriage;
	f_Carriage.clear();

	bool f_Sunk = false;

	for(int f_XY = 0; f_XY < f_Type_Buffer.length(); f_XY++)
		{
		char f_Char = f_Type_Buffer.at(f_XY);

		if(f_Char == '.')
			{
			if(f_Sunk == false)
				{
				m_Mod_Type.push_back(atoi(f_Carriage.c_str()));

				f_Carriage.clear();
				}

			f_Sunk = true;
			}
		else
			{
			f_Carriage.push_back(f_Char);

			f_Sunk = false;
			}
		}
}

void DecisionCom::acSet_Target(std::string f_Target_Buffer)
{
	m_Mod_Target.clear();

	std::string f_Carriage;
	f_Carriage.clear();

	bool f_Sunk = false;
	for(int f_XY = 0; f_XY < f_Target_Buffer.length(); f_XY++)
		{
		char f_Char = f_Target_Buffer.at(f_XY);

		if(f_Char == '.')
			{
			if(f_Sunk == false)
				{
				m_Mod_Target.push_back(f_Carriage.c_str());
				f_Carriage.clear();
				}

			f_Sunk = true;
			}
		else
			{
			f_Carriage.push_back(f_Char);
			f_Sunk = false;
			}
		}
}

void DecisionCom::acSet_Name(std::string f_Name_Buffer)
{
	m_Mod_Name.clear();

	bool f_Sunc = false;
	bool f_Sunk = false;

	std::string f_Carriage;
	f_Carriage.clear();

	std::vector<std::string> f_vec_String;
	f_vec_String.clear();

	for(int f_XY = 0; f_XY < f_Name_Buffer.length(); f_XY++)
		{
		char f_Char = f_Name_Buffer.at(f_XY);

		if(f_Char == ':')
			{
			if(f_Sunc == false)
				{
				m_Mod_Name.push_back(f_vec_String);

				f_vec_String.clear();
				}

			f_Sunc = true;
			}
		else
			{
			if(f_Char == '.')
				{
				if(f_Sunk == false)
					{
					f_vec_String.push_back(f_Carriage.c_str());

					f_Carriage.clear();
					}

				f_Sunk = true;
				}
			else
				{
				if((f_Sunc == false) && (f_Sunk == false))
					{
					f_Carriage.push_back(f_Char);

					f_Sunc = false;
					f_Sunk = false;
					}
				}
			}
		}
}

std::shared_ptr<Qcom_genScript> gqcom_INLfromComID(int f_ComID)
{
	//important surround calls to here with mutex_qcomdb.lock();
	std::string f_ref_CurrentPath = "gqcom_INLfromComID";

	char* f_initquery = new char[512];
	sprintf(f_initquery, "SELECT id, owner, name, description, vision, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE comid = %i", f_ComID);
	g_SafeL[2]->acSelectCommand(f_initquery, false, false);
	delete[] f_initquery;

	ag_StatusLive(f_ref_CurrentPath, "f_NewScript");
	std::shared_ptr<Qcom_genScript> f_NewScript = std::make_shared_reflect<Qcom_genScript>(0, true);

	if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
		{
		int f_inlScriptID = atoi(g_Schedular[2]->acEntry(0)[0].c_str());

		//Build the query
		char* f_init2query = new char[512];

		sprintf(f_init2query, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM inlcodeline WHERE inlscriptid = %i", f_inlScriptID);

		g_SafeL[2]->acSelectCommand(f_init2query, false, false);

		delete[] f_init2query;

		if(g_Schedular[2]->acEntry(0)[0].at(0) != '0')
			{
			for (int f_countLine = 0; f_countLine < g_Schedular[2]->acEntrySize(); f_countLine++)
				{
				f_NewScript->m_vec_InitLine.push_back(ag_ReadProtocol(g_Schedular[2]->acEntry(f_countLine)[3]));
				f_NewScript->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[4].c_str()));
				f_NewScript->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->acEntry(f_countLine)[0].c_str()));
				}

			for(int f_countLine = 0; f_countLine < f_NewScript->m_vec_InitLine.size(); f_countLine++)
				{
				for(int f_countOrder = 0; f_countOrder < f_NewScript->m_vec_InitLineOrder.size(); f_countOrder++)
					{
					if(f_NewScript->m_vec_InitLineOrder[f_countOrder] == f_countLine)
						{
						f_NewScript->m_vec_InitLineOrdered.push_back(f_NewScript->m_vec_InitLine[f_countOrder]);
						f_NewScript->m_vec_InitLineOrderedID.push_back(f_NewScript->m_vec_InitLineOrderID[f_countOrder]);
						}
					}
				}

			if(f_NewScript->m_vec_InitLineOrdered.size() != f_NewScript->m_vec_InitLine.size())
				{
				throw;
				}
			}
		}

	return f_NewScript;
}

std::shared_ptr<Qcom_genScript> gqcom_INLfromString(std::string f_String)
{
	std::string f_ref_CurrentPath = "gqcom_INLfromString";

	ag_StatusLive(f_ref_CurrentPath, "f_NewScript");
	std::shared_ptr<Qcom_genScript> f_NewScript = std::make_shared_reflect<Qcom_genScript>();

	int f_Index = 0;

	std::string f_Buffer;
	f_Buffer.clear();

	bool f_Scan = true;
	while(f_Scan == true)
		{
		char f_Char = f_String.at(f_Index);

		if((f_Char == '\r') || (f_Char == '\n') || (f_Index == f_String.length() - 1))
			{
			if(f_Char != '\r')
				{
				f_Buffer.push_back(f_Char);
				}

			std::string f_Str = f_Buffer;

			f_NewScript->m_vec_InitLine.push_back(f_Str);
			f_NewScript->m_vec_InitLineOrdered.push_back(f_Str);
			f_NewScript->m_vec_InitLineOrderedID.push_back(-5);

			f_Buffer.clear();
			}
		else
			{
			f_Buffer.push_back(f_Char);
			}

		f_Index++;

		if(f_Index >= f_String.length())
			{
			f_Scan = false;
			}
		}

	return f_NewScript;
}

void QcomManager::acClearGrid(void)
{
	std::string f_ref_CurrentPath = "QcomManager::acClearGrid";

#ifdef QCOM_CLEAR_FULL
	m_vec_Qcom.clear();

	m_vec_Input.clear();
	m_vec_Output.clear();

	m_vec_GenScript.clear();
	m_vec_ESLFunction.clear();

	m_vec_ComWire.clear();
	m_vec_WireCom.clear();

	m_Wiring_Input.clear();
	m_Wiring_Output.clear();
#endif

	m_SaveCom.push_back(m_Qcom);

	mam_Qcom = ag_MotherCom();

	m_Qcom = mam_Qcom;
}

void QcomManager::acClearGridNew(std::shared_ptr<Qcom> f_NewCom)
{
	std::string f_ref_CurrentPath = "QcomManager::acClearGridNew";

#ifdef QCOM_CLEAR_FULL
	m_vec_Qcom.clear();

	m_vec_Input.clear();
	m_vec_Output.clear();

	m_vec_GenScript.clear();
	m_vec_ESLFunction.clear();

	m_vec_ComWire.clear();
	m_vec_WireCom.clear();

	m_Wiring_Input.clear();
	m_Wiring_Output.clear();
#endif

	m_SaveCom.push_back(m_Qcom);

	mam_Qcom = f_NewCom;

	m_Qcom = mam_Qcom;
}

bool DecisionWheel::acReposition(BiVector f_Direction, bool f_Click)
{
	std::string f_ref_CurrentPath = "QcomManager::acClearGridNew";

	if(f_Click == false)
		{
		acClearHighLight();
		}

	if(m_LayerPos == 0)
		{
		m_position->m_X = g_QcomManager->m_current_X;
		m_position->m_Y = g_QcomManager->m_current_Y;
		m_position->m_Z = 0.0f;

		if(f_Direction.m_X >= 1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_East = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_X > m_position->m_X)
					{
					f_vec_ComList_East->acPush(f_Com);
					}
				}

			if(f_vec_ComList_East->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_East->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				if(f_com->m_HighLighted == false)
					{
					f_com->acHighLight(true);

					m_vec_HighLighted_com.push_back(f_com);

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return true;
					}
				else
					{
					f_com->acHighLight(false);

					for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
						{
						if(f_com->m_ID == m_vec_HighLighted_com[f_XY]->m_ID)
							{
							for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_com.size() - 1; f_Jet++)
								{
								m_vec_HighLighted_com[f_Jet] = m_vec_HighLighted_com[f_Jet + 1];
								}

							m_vec_HighLighted_com.pop_back();
							}
						}

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return false;
					}
				}
			}
		else if(f_Direction.m_X <= -1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_West = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_X < m_position->m_X)
					{
					f_vec_ComList_West->acPush(f_Com);
					}
				}

			if(f_vec_ComList_West->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_West->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				if(f_com->m_HighLighted == false)
					{
					f_com->acHighLight(true);

					m_vec_HighLighted_com.push_back(f_com);

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return true;
					}
				else
					{
					f_com->acHighLight(false);

					for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
						{
						if(f_com->m_ID == m_vec_HighLighted_com[f_XY]->m_ID)
							{
							for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_com.size() - 1; f_Jet++)
								{
								m_vec_HighLighted_com[f_Jet] = m_vec_HighLighted_com[f_Jet + 1];
								}

							m_vec_HighLighted_com.pop_back();
							}
						}

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return false;
					}
				}
			}
		else if(f_Direction.m_Y >= 1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_North = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_Y > m_position->m_Y)
					{
					f_vec_ComList_North->acPush(f_Com);
					}
				}

			if(f_vec_ComList_North->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_North->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				if(f_com->m_HighLighted == false)
					{
					f_com->acHighLight(true);

					m_vec_HighLighted_com.push_back(f_com);

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return true;
					}
				else
					{
					f_com->acHighLight(false);

					for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
						{
						if(f_com->m_ID == m_vec_HighLighted_com[f_XY]->m_ID)
							{
							for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_com.size() - 1; f_Jet++)
								{
								m_vec_HighLighted_com[f_Jet] = m_vec_HighLighted_com[f_Jet + 1];
								}

							m_vec_HighLighted_com.pop_back();
							}
						}

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return false;
					}
				}
			}
		else if(f_Direction.m_Y <= -1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_South = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_Y < m_position->m_Y)
					{
					f_vec_ComList_South->acPush(f_Com);
					}
				}

			if(f_vec_ComList_South->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_South->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				if(f_com->m_HighLighted == false)
					{
					f_com->acHighLight(true);

					m_vec_HighLighted_com.push_back(f_com);

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return true;
					}
				else
					{
					f_com->acHighLight(false);

					for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
						{
						if(f_com->m_ID == m_vec_HighLighted_com[f_XY]->m_ID)
							{
							for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_com.size() - 1; f_Jet++)
								{
								m_vec_HighLighted_com[f_Jet] = m_vec_HighLighted_com[f_Jet + 1];
								}

							m_vec_HighLighted_com.pop_back();
							}
						}

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return false;
					}
				}
			}
		else //unary zero three component 0.0f 0.0f 0.0f
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_Nearest = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				f_vec_ComList_Nearest->acPush(g_QcomManager->m_Qcom->m_vec_Qcom[f_XY]);
				}

			if(f_vec_ComList_Nearest->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_Nearest->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				if(f_com->m_HighLighted == false)
					{
					f_com->acHighLight(true);

					m_vec_HighLighted_com.push_back(f_com);

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return true;
					}
				else
					{
					f_com->acHighLight(false);

					for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
						{
						if(f_com->m_ID == m_vec_HighLighted_com[f_XY]->m_ID)
							{
							for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_com.size() - 1; f_Jet++)
								{
								m_vec_HighLighted_com[f_Jet] = m_vec_HighLighted_com[f_Jet + 1];
								}

							m_vec_HighLighted_com.pop_back();
							}
						}

					m_position->m_X = f_com->m_position->m_X;
					m_position->m_Y = f_com->m_position->m_Y;

					return false;
					}
				}
			}
		}
	else //layer one
		{
		if(f_Direction.m_X >= 1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_East = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_X >= m_position->m_X)
					{
					f_vec_ComList_East->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_X > m_position->m_X)
						{
						f_vec_ComList_East->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_X > m_position->m_X)
						{
						f_vec_ComList_East->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Xmin > m_position->m_X) && (f_Wire->m_Xmax > m_position->m_X))
						{
						f_vec_ComList_East->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_East->m_vec_com.size() <= 0) && (f_vec_ComList_East->m_vec_input.size() <= 0) &&
				(f_vec_ComList_East->m_vec_output.size() <= 0) && (f_vec_ComList_East->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_East->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_East->m_vec_input[0]->m_HighLighted == false)
							{
							f_vec_ComList_East->m_vec_input[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_East->m_vec_input[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
								{
								if(f_vec_ComList_East->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_input.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_input[f_Jet] = m_vec_HighLighted_input[f_Jet + 1];
										}

									m_vec_HighLighted_input.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_East->m_vec_input[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_East->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_East->m_vec_input[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_input.push_back(f_vec_ComList_East->m_vec_input[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
							{
							if(f_vec_ComList_East->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_input.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_input.push_back(f_vec_ComList_East->m_vec_input[0]);
							}
						}
					}break;

				case 1: //output
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_East->m_vec_output[0]->m_HighLighted == false)
							{
							f_vec_ComList_East->m_vec_output[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_East->m_vec_output[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
								{
								if(f_vec_ComList_East->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_output.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_output[f_Jet] = m_vec_HighLighted_output[f_Jet + 1];
										}

									m_vec_HighLighted_output.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_East->m_vec_output[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_East->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_East->m_vec_output[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_output.push_back(f_vec_ComList_East->m_vec_output[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
							{
							if(f_vec_ComList_East->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_output.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_output.push_back(f_vec_ComList_East->m_vec_output[0]);
							}
						}
					}break;

				case 2: //wire
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_East->m_vec_wire[0]->m_Selected == false)
							{
							f_vec_ComList_East->m_vec_wire[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_East->m_vec_wire[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
								{
								if(f_vec_ComList_East->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_wire.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_wire[f_Jet] = m_vec_HighLighted_wire[f_Jet + 1];
										}

									m_vec_HighLighted_wire.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_East->m_vec_wire[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_East->m_vec_wire[0]->m_OutputCom->m_position->m_X;
					m_position->m_Y = f_vec_ComList_East->m_vec_wire[0]->m_OutputCom->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_wire.push_back(f_vec_ComList_East->m_vec_wire[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
							{
							if(f_vec_ComList_East->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_wire.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_wire.push_back(f_vec_ComList_East->m_vec_wire[0]);
							}
						}
					}break;
				}
			}
		else if(f_Direction.m_X <= -1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_West = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_X <= m_position->m_X)
					{
					f_vec_ComList_West->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_X < m_position->m_X)
						{
						f_vec_ComList_West->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_X < m_position->m_X)
						{
						f_vec_ComList_West->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Xmin < m_position->m_X) && (f_Wire->m_Xmax < m_position->m_X))
						{
						f_vec_ComList_West->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_West->m_vec_com.size() <= 0) && (f_vec_ComList_West->m_vec_input.size() <= 0) &&
				(f_vec_ComList_West->m_vec_output.size() <= 0) && (f_vec_ComList_West->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_West->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_West->m_vec_input[0]->m_HighLighted == false)
							{
							f_vec_ComList_West->m_vec_input[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_West->m_vec_input[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
								{
								if(f_vec_ComList_West->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_input.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_input[f_Jet] = m_vec_HighLighted_input[f_Jet + 1];
										}

									m_vec_HighLighted_input.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_West->m_vec_input[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_West->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_West->m_vec_input[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_input.push_back(f_vec_ComList_West->m_vec_input[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
							{
							if(f_vec_ComList_West->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_input.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_input.push_back(f_vec_ComList_West->m_vec_input[0]);
							}
						}
					}break;

				case 1: //output
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_West->m_vec_output[0]->m_HighLighted == false)
							{
							f_vec_ComList_West->m_vec_output[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_West->m_vec_output[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
								{
								if(f_vec_ComList_West->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_output.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_output[f_Jet] = m_vec_HighLighted_output[f_Jet + 1];
										}

									m_vec_HighLighted_output.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_West->m_vec_output[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_West->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_West->m_vec_output[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_output.push_back(f_vec_ComList_West->m_vec_output[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
							{
							if(f_vec_ComList_West->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_output.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_output.push_back(f_vec_ComList_West->m_vec_output[0]);
							}
						}
					}break;

				case 2: //wire
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_West->m_vec_wire[0]->m_HighLighted == false)
							{
							f_vec_ComList_West->m_vec_wire[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_West->m_vec_wire[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
								{
								if(f_vec_ComList_West->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_wire.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_wire[f_Jet] = m_vec_HighLighted_wire[f_Jet + 1];
										}

									m_vec_HighLighted_wire.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_West->m_vec_wire[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_West->m_vec_wire[0]->m_Xmin + ((f_vec_ComList_West->m_vec_wire[0]->m_Xmax - f_vec_ComList_West->m_vec_wire[0]->m_Xmin) * 0.5f);
					m_position->m_Y = f_vec_ComList_West->m_vec_wire[0]->m_Ymin + ((f_vec_ComList_West->m_vec_wire[0]->m_Ymax - f_vec_ComList_West->m_vec_wire[0]->m_Ymin) * 0.5f);

					if(f_Click == false)
						{
						m_vec_HighLighted_wire.push_back(f_vec_ComList_West->m_vec_wire[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
							{
							if(f_vec_ComList_West->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_wire.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_wire.push_back(f_vec_ComList_West->m_vec_wire[0]);
							}
						}
					}break;
				}
			}
		else if(f_Direction.m_Y <= -1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_North = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_Y <= m_position->m_Y)
					{
					f_vec_ComList_North->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_Y > m_position->m_Y)
						{
						f_vec_ComList_North->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_Y > m_position->m_Y)
						{
						f_vec_ComList_North->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Ymin > m_position->m_Y) || (f_Wire->m_Ymax > m_position->m_Y))
						{
						f_vec_ComList_North->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_North->m_vec_com.size() <= 0) && (f_vec_ComList_North->m_vec_input.size() <= 0) &&
				(f_vec_ComList_North->m_vec_output.size() <= 0) && (f_vec_ComList_North->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_North->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_North->m_vec_input[0]->m_HighLighted == false)
							{
							f_vec_ComList_North->m_vec_input[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_North->m_vec_input[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
								{
								if(f_vec_ComList_North->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_input.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_input[f_Jet] = m_vec_HighLighted_input[f_Jet + 1];
										}

									m_vec_HighLighted_input.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_North->m_vec_input[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_North->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_North->m_vec_input[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_input.push_back(f_vec_ComList_North->m_vec_input[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
							{
							if(f_vec_ComList_North->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_input.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_input.push_back(f_vec_ComList_North->m_vec_input[0]);
							}
						}
					}break;

				case 1: //output
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_North->m_vec_output[0]->m_HighLighted == false)
							{
							f_vec_ComList_North->m_vec_output[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_North->m_vec_output[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
								{
								if(f_vec_ComList_North->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_output.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_output[f_Jet] = m_vec_HighLighted_output[f_Jet + 1];
										}

									m_vec_HighLighted_output.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_North->m_vec_output[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_North->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_North->m_vec_output[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_output.push_back(f_vec_ComList_North->m_vec_output[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
							{
							if(f_vec_ComList_North->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_output.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_output.push_back(f_vec_ComList_North->m_vec_output[0]);
							}
						}
					}break;

				case 2: //wire
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_North->m_vec_wire[0]->m_HighLighted == false)
							{
							f_vec_ComList_North->m_vec_wire[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_North->m_vec_wire[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
								{
								if(f_vec_ComList_North->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_wire.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_wire[f_Jet] = m_vec_HighLighted_wire[f_Jet + 1];
										}

									m_vec_HighLighted_wire.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_North->m_vec_wire[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_North->m_vec_wire[0]->m_Xmin + ((f_vec_ComList_North->m_vec_wire[0]->m_Xmax - f_vec_ComList_North->m_vec_wire[0]->m_Xmin) * 0.5f);
					m_position->m_Y = f_vec_ComList_North->m_vec_wire[0]->m_Ymin + ((f_vec_ComList_North->m_vec_wire[0]->m_Ymax - f_vec_ComList_North->m_vec_wire[0]->m_Ymin) * 0.5f);

					if(f_Click == false)
						{
						m_vec_HighLighted_wire.push_back(f_vec_ComList_North->m_vec_wire[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
							{
							if(f_vec_ComList_North->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_wire.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_wire.push_back(f_vec_ComList_North->m_vec_wire[0]);
							}
						}
					}break;
				}
			}
		else if(f_Direction.m_Y >= 1.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_South = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_X <= m_position->m_X)
					{
					f_vec_ComList_South->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_Y < m_position->m_Y)
						{
						f_vec_ComList_South->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_Y < m_position->m_Y)
						{
						f_vec_ComList_South->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Ymin < m_position->m_Y) || (f_Wire->m_Ymax < m_position->m_Y))
						{
						f_vec_ComList_South->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_South->m_vec_com.size() <= 0) && (f_vec_ComList_South->m_vec_input.size() <= 0) &&
				(f_vec_ComList_South->m_vec_output.size() <= 0) && (f_vec_ComList_South->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_South->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_South->m_vec_input[0]->m_HighLighted == false)
							{
							f_vec_ComList_South->m_vec_input[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_South->m_vec_input[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
								{
								if(f_vec_ComList_South->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_input.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_input[f_Jet] = m_vec_HighLighted_input[f_Jet + 1];
										}

									m_vec_HighLighted_input.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_South->m_vec_input[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_South->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_South->m_vec_input[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_input.push_back(f_vec_ComList_South->m_vec_input[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
							{
							if(f_vec_ComList_South->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_input.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_input.push_back(f_vec_ComList_South->m_vec_input[0]);
							}
						}
					}break;

				case 1: //output
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_South->m_vec_output[0]->m_HighLighted == false)
							{
							f_vec_ComList_South->m_vec_output[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_South->m_vec_output[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
								{
								if(f_vec_ComList_South->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_output.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_output[f_Jet] = m_vec_HighLighted_output[f_Jet + 1];
										}

									m_vec_HighLighted_output.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_South->m_vec_output[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_South->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_South->m_vec_output[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_output.push_back(f_vec_ComList_South->m_vec_output[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
							{
							if(f_vec_ComList_South->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_output.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_output.push_back(f_vec_ComList_South->m_vec_output[0]);
							}
						}
					}break;

				case 2: //wire
					{
					if(f_Click == true)
						{
						if(f_vec_ComList_South->m_vec_wire[0]->m_HighLighted == false)
							{
							f_vec_ComList_South->m_vec_wire[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList_South->m_vec_wire[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
								{
								if(f_vec_ComList_South->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_wire.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_wire[f_Jet] = m_vec_HighLighted_wire[f_Jet + 1];
										}

									m_vec_HighLighted_wire.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList_South->m_vec_wire[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList_South->m_vec_wire[0]->m_Xmin + ((f_vec_ComList_South->m_vec_wire[0]->m_Xmax - f_vec_ComList_South->m_vec_wire[0]->m_Xmin) * 0.5f);
					m_position->m_Y = f_vec_ComList_South->m_vec_wire[0]->m_Ymin + ((f_vec_ComList_South->m_vec_wire[0]->m_Ymax - f_vec_ComList_South->m_vec_wire[0]->m_Ymin) * 0.5f);

					if(f_Click == false)
						{
						m_vec_HighLighted_wire.push_back(f_vec_ComList_South->m_vec_wire[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
							{
							if(f_vec_ComList_South->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_wire.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_wire.push_back(f_vec_ComList_South->m_vec_wire[0]);
							}
						}
					}break;
				}
			}
		else
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				f_vec_ComList->acPush(f_Com);
#endif

				for(int f_XYZ = 0; f_XYZ < f_Com->m_vec_Input.size(); f_XYZ++)
					{
					f_vec_ComList->acPush(f_Com->m_vec_Input[f_XYZ]);
					}

				for(int f_XYZ = 0; f_XYZ < f_Com->m_vec_Output.size(); f_XYZ++)
					{
					f_vec_ComList->acPush(f_Com->m_vec_Output[f_XYZ]);
					}
				}

			if((f_vec_ComList->m_vec_com.size() <= 0) && (f_vec_ComList->m_vec_input.size() <= 0) &&
				(f_vec_ComList->m_vec_output.size() <= 0) && (f_vec_ComList->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:
					{
					if(f_Click == true)
						{
						if(f_vec_ComList->m_vec_input[0]->m_HighLighted == false)
							{
							f_vec_ComList->m_vec_input[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList->m_vec_input[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
								{
								if(f_vec_ComList->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_input.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_input[f_Jet] = m_vec_HighLighted_input[f_Jet + 1];
										}

									m_vec_HighLighted_input.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList->m_vec_input[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList->m_vec_input[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_input.push_back(f_vec_ComList->m_vec_input[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_input.size(); f_XY++)
							{
							if(f_vec_ComList->m_vec_input[0]->m_ID == m_vec_HighLighted_input[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_input.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_input.push_back(f_vec_ComList->m_vec_input[0]);
							}
						}
					}break;

				case 1: //output
					{
					if(f_Click == true)
						{
						if(f_vec_ComList->m_vec_output[0]->m_HighLighted == false)
							{
							f_vec_ComList->m_vec_output[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList->m_vec_output[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
								{
								if(f_vec_ComList->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_output.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_output[f_Jet] = m_vec_HighLighted_output[f_Jet + 1];
										}

									m_vec_HighLighted_output.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList->m_vec_output[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList->m_vec_output[0]->m_position->m_Y;

					if(f_Click == false)
						{
						m_vec_HighLighted_output.push_back(f_vec_ComList->m_vec_output[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_output.size(); f_XY++)
							{
							if(f_vec_ComList->m_vec_output[0]->m_ID == m_vec_HighLighted_output[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_output.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_output.push_back(f_vec_ComList->m_vec_output[0]);
							}
						}
					}break;

				case 2: //wire
					{
					if(f_Click == true)
						{
						if(f_vec_ComList->m_vec_wire[0]->m_HighLighted == false)
							{
							f_vec_ComList->m_vec_wire[0]->acHighLight(true);
							}
						else
							{
							f_vec_ComList->m_vec_wire[0]->acHighLight(false);

							for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
								{
								if(f_vec_ComList->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
									{
									for(int f_Jet = f_XY; f_Jet < m_vec_HighLighted_wire.size() - 1; f_Jet++)
										{
										m_vec_HighLighted_wire[f_Jet] = m_vec_HighLighted_wire[f_Jet + 1];
										}

									m_vec_HighLighted_wire.pop_back();
									}
								}
							}
						}
					else
						{
						f_vec_ComList->m_vec_wire[0]->acHighLight(true);
						}

					m_position->m_X = f_vec_ComList->m_vec_wire[0]->m_Xmin + ((f_vec_ComList->m_vec_wire[0]->m_Xmax - f_vec_ComList->m_vec_wire[0]->m_Xmin) * 0.5f);
					m_position->m_Y = f_vec_ComList->m_vec_wire[0]->m_Ymin + ((f_vec_ComList->m_vec_wire[0]->m_Ymax - f_vec_ComList->m_vec_wire[0]->m_Ymin) * 0.5f);

					if(f_Click == false)
						{
						m_vec_HighLighted_wire.push_back(f_vec_ComList->m_vec_wire[0]);
						}
					else
						{
						bool f_Found = false;

						for(int f_XY = 0; f_XY < m_vec_HighLighted_wire.size(); f_XY++)
							{
							if(f_vec_ComList->m_vec_wire[0]->m_ID == m_vec_HighLighted_wire[f_XY]->m_ID)
								{
								f_Found = true;
								f_XY = m_vec_HighLighted_wire.size();
								}
							}

						if(f_Found == false)
							{
							m_vec_HighLighted_wire.push_back(f_vec_ComList->m_vec_wire[0]);
							}
						}
					}break;
				}
			}
		}

	return false;
}

std::shared_ptr<SelectionPreList> DecisionWheel::acMakeList(void)
{
	std::string f_ref_CurrentPath = "DecisionWheel::acMakeList";

	ag_StatusLive(f_ref_CurrentPath, "f_List");
	std::shared_ptr<SelectionPreList> f_List = std::make_shared_reflect<SelectionPreList>();

	f_List->m_position->m_X = m_position->m_X;
	f_List->m_position->m_Y = m_position->m_Y;

	return f_List;
}

std::shared_ptr<Qcom> SelectionPreList::acSelectionList_ByBiDistance(void)
{
	std::string f_ref_CurrentPath = "SelectionPreList::acSelectionList_ByBiDistance";

	float f_Distance = FLT_MAX;

	std::shared_ptr<Qcom> f_Result_Com = nullptr;

	for(int f_XYZ = 0; f_XYZ < m_vec_com.size(); f_XYZ++)
		{
		std::shared_ptr<Qcom> f_com = m_vec_com[f_XYZ];

		//ag_StatusLive(f_ref_CurrentPath, "f_DifVec");
		std::shared_ptr<BiVector> f_DifVec = std::make_shared<Cube::BiVector>(m_position->m_X - f_com->m_position->m_X, m_position->m_Y - f_com->m_position->m_Y, m_position->m_Z - f_com->m_position->m_Z);

		float f_Length = f_DifVec->acLength();
			
		if(f_Length < f_Distance)
			{
			f_Result_Com = f_com;
			f_Distance = f_Length;
			}
		}

	return f_Result_Com;
}

int SelectionPreList::acSelectionList_ByBiDistanceChase(void)
{
	std::string f_ref_CurrentPath = "SelectionPreList::acSelectionList_ByBiDistanceChase";

	float f_Distance = FLT_MAX;
	std::shared_ptr<QcomInput> f_Result_Input = nullptr;
	std::shared_ptr<QcomOutput> f_Result_Output = nullptr;
	std::shared_ptr<QcomWire> f_Result_Wire = nullptr;
	int f_Type = 0; // Type returned = input

	for(int f_XYZ = 0; f_XYZ < m_vec_input.size(); f_XYZ++)
		{
		std::shared_ptr<QcomInput> f_input = m_vec_input[f_XYZ];

		//ag_StatusLive(f_ref_CurrentPath, "f_DifVec");
		std::shared_ptr<BiVector> f_DifVec = std::make_shared<Cube::BiVector>(m_position->m_X - f_input->m_position->m_X, m_position->m_Y - f_input->m_position->m_Y, m_position->m_Z - f_input->m_position->m_Z);

		float f_Length = f_DifVec->acLength();

		if(f_Length < f_Distance)
			{
			f_Result_Input = f_input;
			f_Distance = f_Length;
			f_Type = 0;
			}
		}

	m_vec_input.clear();

	if(f_Result_Input != nullptr)
		{
		m_vec_input.push_back(f_Result_Input);
		}

	for(int f_XYZ = 0; f_XYZ < m_vec_output.size(); f_XYZ++)
		{
		std::shared_ptr<QcomOutput> f_output = m_vec_output[f_XYZ];

		BiVector f_Vector = f_output->m_position;

		//ag_StatusLive(f_ref_CurrentPath, "f_DifVec");
		std::shared_ptr<BiVector> f_DifVec = std::make_shared<Cube::BiVector>(m_position->m_X - f_output->m_position->m_X, m_position->m_Y - f_output->m_position->m_Y, m_position->m_Z - f_output->m_position->m_Z);

		float f_Length = f_DifVec->acLength();

		if(f_Length < f_Distance)
			{
			f_Result_Output = f_output;
			f_Distance = f_Length;
			f_Type = 1;
			}
		}

	m_vec_output.clear();

	if(f_Result_Output != nullptr)
		{
		m_vec_output.push_back(f_Result_Output);
		}

	for(int f_XYZ = 0; f_XYZ < m_vec_wire.size(); f_XYZ++)
		{
		std::shared_ptr<QcomWire> f_wire = m_vec_wire[f_XYZ];

		//ag_StatusLive(f_ref_CurrentPath, "f_Vector_UpRight");
		std::shared_ptr<BiVector> f_Vector_UpRight = std::make_shared<Cube::BiVector>(f_wire->m_Xmax, f_wire->m_Ymax, 0.0f);
		//ag_StatusLive(f_ref_CurrentPath, "f_Vector_UpLeft");
		std::shared_ptr<BiVector> f_Vector_UpLeft = std::make_shared<Cube::BiVector>(f_wire->m_Xmin, f_wire->m_Ymax, 0.0f);
		//ag_StatusLive(f_ref_CurrentPath, "f_Vector_DownRight");
		std::shared_ptr<BiVector> f_Vector_DownRight = std::make_shared<Cube::BiVector>(f_wire->m_Xmax, f_wire->m_Ymin, 0.0f);
		//ag_StatusLive(f_ref_CurrentPath, "f_Vector_DownLeft");
		std::shared_ptr<BiVector> f_Vector_DownLeft = std::make_shared<Cube::BiVector>(f_wire->m_Xmin, f_wire->m_Ymin, 0.0f);

		//ag_StatusLive(f_ref_CurrentPath, "f_DifVecUpR");
		std::shared_ptr<BiVector> f_DifVecUpR = std::make_shared<Cube::BiVector>(m_position->m_X - f_Vector_UpRight->m_X, m_position->m_Y - f_Vector_UpRight->m_Y, m_position->m_Z - f_Vector_UpRight->m_Z);

		float f_LengthUpR = f_DifVecUpR->acLength();

		if(f_LengthUpR < f_Distance)
			{
			f_Result_Wire = f_wire;
			f_Distance = f_LengthUpR;
			f_Type = 2;
			}

		//ag_StatusLive(f_ref_CurrentPath, "f_DifVecUpL");
		std::shared_ptr<BiVector> f_DifVecUpL = std::make_shared<Cube::BiVector>(m_position->m_X - f_Vector_UpRight->m_X, m_position->m_Y - f_Vector_UpRight->m_Y, m_position->m_Z - f_Vector_UpRight->m_Z);

		float f_LengthUpL = f_DifVecUpL->acLength();

		if(f_LengthUpL < f_Distance)
			{
			f_Result_Wire = f_wire;
			f_Distance = f_LengthUpL;
			f_Type = 2;
			}

		//ag_StatusLive(f_ref_CurrentPath, "f_DifVecDnR");
		std::shared_ptr<BiVector> f_DifVecDnR = std::make_shared<Cube::BiVector>(m_position->m_X - f_Vector_DownRight->m_X, m_position->m_Y - f_Vector_DownRight->m_Y, m_position->m_Z - f_Vector_DownRight->m_Z);

		float f_LengthDnR = f_DifVecDnR->acLength();

		if(f_LengthDnR < f_Distance)
			{
			f_Result_Wire = f_wire;
			f_Distance = f_LengthDnR;
			f_Type = 2;
			}

		//ag_StatusLive(f_ref_CurrentPath, "f_DifVecDnL");
		std::shared_ptr<BiVector> f_DifVecDnL = std::make_shared<Cube::BiVector>(m_position->m_X - f_Vector_DownLeft->m_X, m_position->m_Y - f_Vector_DownLeft->m_Y, m_position->m_Z - f_Vector_DownLeft->m_Z);

		float f_LengthDnL = f_DifVecDnL->acLength();

		if(f_LengthDnL < f_Distance)
			{
			f_Result_Wire = f_wire;
			f_Distance = f_LengthDnL;
			f_Type = 2;
			}

		if((m_position->m_X >= f_wire->m_Xmin) &&
			(m_position->m_X <= f_wire->m_Xmax) &&
			(m_position->m_Y >= f_wire->m_Ymin) &&
			(m_position->m_Y <= f_wire->m_Ymax))
			{
			f_Result_Wire = f_wire;
			f_Distance = 0.0f;
			f_Type = 2;
			}
		}

	m_vec_wire.clear();

	if(f_Result_Wire != nullptr)
		{
		m_vec_wire.push_back(f_Result_Wire);
		}

	return f_Type;
}

bool DecisionWheel::acSelectionGrow(BiVector f_Direction)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "DecisionWheel::acSelectionGrow";

	if(m_LayerPos == 0)
		{
		if(m_vec_HighLighted_com.size() != 1)
			{
			acReposition(f_Direction);

			return true;
			}

		if(m_vec_HighLighted_com[0]->m_Selected == true)
			{
			m_vec_HighLighted_com[0]->acSelect(true);

			m_vec_Selection_com.push_back(m_vec_HighLighted_com[0]);
			}

		if(f_Direction.m_X > 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_East = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_X > m_position->m_X)
					{
					f_vec_ComList_East->acPush(f_Com);
					}
				}

			if(f_vec_ComList_East->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_East->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				f_com->acSelect(true);

				m_vec_Selection_com.push_back(f_com);

				m_position->m_X = f_com->m_position->m_X;
				m_position->m_Y = f_com->m_position->m_Y;

				return true;
				}
			}
		else if(f_Direction.m_X < 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_West = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_X < m_position->m_X)
					{
					f_vec_ComList_West->acPush(f_Com);
					}
				}

			if(f_vec_ComList_West->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_West->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				f_com->acSelect(true);

				m_vec_Selection_com.push_back(f_com);

				m_position->m_X = f_com->m_position->m_X;
				m_position->m_Y = f_com->m_position->m_Y;
			
				return true;
				}

			return true;
			}
		else if(f_Direction.m_Y > 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_North = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_Y > m_position->m_Y)
					{
					f_vec_ComList_North->acPush(f_Com);
					}
				}

			if(f_vec_ComList_North->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_North->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				f_com->acSelect(true);

				m_vec_Selection_com.push_back(f_com);

				m_position->m_X = f_com->m_position->m_X;
				m_position->m_Y = f_com->m_position->m_Y;

				return true;
				}

			return true;
			}
		else if(f_Direction.m_Y < 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_South = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position->m_Y < m_position->m_Y)
					{
					f_vec_ComList_South->acPush(f_Com);
					}
				}

			if(f_vec_ComList_South->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList_South->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				f_com->acSelect(true);

				m_vec_Selection_com.push_back(f_com);

				m_position->m_X = f_com->m_position->m_X;
				m_position->m_Y = f_com->m_position->m_Y;

				return true;
				}

			return true;
			}
		else //zero components 0.0f 0.0f 0.0f
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList = acMakeList();

			for(int f_XY = 0; f_XY < g_QcomManager->m_Qcom->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_Qcom->m_vec_Qcom[f_XY];

				//half check
				f_vec_ComList->acPush(f_Com);
				}

			if(f_vec_ComList->m_vec_com.size() <= 0)
				{
				return false;
				}

			std::shared_ptr<Qcom> f_com = f_vec_ComList->acSelectionList_ByBiDistance();

			if(f_com->m_ID != -1551)
				{
				f_com->acSelect(true);

				m_vec_Selection_com.push_back(f_com);

				m_position->m_X = f_com->m_position->m_X;
				m_position->m_Y = f_com->m_position->m_Y;

				return true;
				}

			return true;
			}
		}
	else //layerpos == 1
		{
		if(f_Direction.m_X > 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_East = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_X >= m_position->m_X)
					{
					f_vec_ComList_East->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_X > m_position->m_X)
						{
						f_vec_ComList_East->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_X > m_position->m_X)
						{
						f_vec_ComList_East->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Xmin >= m_position->m_X) || (f_Wire->m_Xmax >= m_position->m_X))
						{
						f_vec_ComList_East->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_East->m_vec_com.size() <= 0) && (f_vec_ComList_East->m_vec_input.size() <= 0) &&
				(f_vec_ComList_East->m_vec_output.size() <= 0) && (f_vec_ComList_East->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_East->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					f_vec_ComList_East->m_vec_input[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_East->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_East->m_vec_input[0]->m_position->m_Y;

					m_vec_Selection_input.push_back(f_vec_ComList_East->m_vec_input[0]);
					}break;
				case 1: //output
					{
					f_vec_ComList_East->m_vec_output[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_East->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_East->m_vec_output[0]->m_position->m_Y;

					m_vec_Selection_output.push_back(f_vec_ComList_East->m_vec_output[0]);
					}break;
				case 2: //wire
					{
					f_vec_ComList_East->m_vec_wire[0]->acSelect(true);

					//ag_StatusLive(f_ref_CurrentPath, "m_position");
					m_position = std::make_shared<Cube::BiVector>(f_vec_ComList_East->m_vec_wire[0]->m_Xmin, f_vec_ComList_East->m_vec_wire[0]->m_Ymin, 0.0f);

					m_vec_Selection_wire.push_back(f_vec_ComList_East->m_vec_wire[0]);
					}break;
				}
			}
		else if(f_Direction.m_X < 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_West = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_X <= m_position->m_X)
					{
					f_vec_ComList_West->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_X <= m_position->m_X)
						{
						f_vec_ComList_West->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_X <= m_position->m_X)
						{
						f_vec_ComList_West->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Xmin <= m_position->m_X) || (f_Wire->m_Xmax <= m_position->m_X))
						{
						f_vec_ComList_West->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_West->m_vec_com.size() <= 0) && (f_vec_ComList_West->m_vec_input.size() <= 0) &&
				(f_vec_ComList_West->m_vec_output.size() <= 0) && (f_vec_ComList_West->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_West->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					f_vec_ComList_West->m_vec_input[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_West->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_West->m_vec_input[0]->m_position->m_Y;

					m_vec_Selection_input.push_back(f_vec_ComList_West->m_vec_input[0]);
					}break;
				case 1: //output
					{
					f_vec_ComList_West->m_vec_output[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_West->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_West->m_vec_output[0]->m_position->m_Y;

					m_vec_Selection_output.push_back(f_vec_ComList_West->m_vec_output[0]);
					}break;
				case 2: //wire
					{
					f_vec_ComList_West->m_vec_wire[0]->acSelect(true);

					//ag_StatusLive(f_ref_CurrentPath, "m_position");
					m_position = std::make_shared<Cube::BiVector>(f_vec_ComList_West->m_vec_wire[0]->m_Xmin, f_vec_ComList_West->m_vec_wire[0]->m_Ymin, 0.0f);

					m_vec_Selection_wire.push_back(f_vec_ComList_West->m_vec_wire[0]);
					}break;
				}
			}
		else if(f_Direction.m_Y > 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_North = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_Y >= m_position->m_Y)
					{
					f_vec_ComList_North->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_Y >= m_position->m_Y)
						{
						f_vec_ComList_North->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_Y >= m_position->m_Y)
						{
						f_vec_ComList_North->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Ymin <= m_position->m_Y) || (f_Wire->m_Ymax >= m_position->m_Y))
						{
						f_vec_ComList_North->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_North->m_vec_com.size() <= 0) && (f_vec_ComList_North->m_vec_input.size() <= 0) &&
				(f_vec_ComList_North->m_vec_output.size() <= 0) && (f_vec_ComList_North->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_North->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					f_vec_ComList_North->m_vec_input[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_North->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_North->m_vec_input[0]->m_position->m_Y;

					m_vec_Selection_input.push_back(f_vec_ComList_North->m_vec_input[0]);
					}break;
				case 1: //output
					{
					f_vec_ComList_North->m_vec_output[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_North->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_North->m_vec_output[0]->m_position->m_Y;

					m_vec_Selection_output.push_back(f_vec_ComList_North->m_vec_output[0]);
					}break;
				case 2: //wire
					{
					f_vec_ComList_North->m_vec_wire[0]->acSelect(true);

					//ag_StatusLive(f_ref_CurrentPath, "m_position");
					m_position = std::make_shared<Cube::BiVector>(f_vec_ComList_North->m_vec_wire[0]->m_Xmin, f_vec_ComList_North->m_vec_wire[0]->m_Ymin, 0.0f);

					m_vec_Selection_wire.push_back(f_vec_ComList_North->m_vec_wire[0]);
					}break;
				}
			}
		else if(f_Direction.m_Y < 0.0f)
			{
			std::shared_ptr<SelectionPreList> f_vec_ComList_South = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				//half check
				if(f_Com->m_position->m_Y <= m_position->m_Y)
					{
					f_vec_ComList_South->acPush(f_Com);
					}
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					//half check
					if(f_Input->m_position->m_Y <= m_position->m_Y)
						{
						f_vec_ComList_South->acPush(f_Input);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					//half check
					if(f_Output->m_position->m_Y <= m_position->m_Y)
						{
						f_vec_ComList_South->acPush(f_Output);
						}
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					//half check
					if((f_Wire->m_Ymin <= m_position->m_Y) || (f_Wire->m_Ymax <= m_position->m_Y))
						{
						f_vec_ComList_South->acPush(f_Wire);
						}
					}
				}

			if((f_vec_ComList_South->m_vec_com.size() <= 0) && (f_vec_ComList_South->m_vec_input.size() <= 0) &&
				(f_vec_ComList_South->m_vec_output.size() <= 0) && (f_vec_ComList_South->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList_South->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					f_vec_ComList_South->m_vec_input[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_South->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_South->m_vec_input[0]->m_position->m_Y;

					m_vec_Selection_input.push_back(f_vec_ComList_South->m_vec_input[0]);
					}break;
				case 1: //output
					{
					f_vec_ComList_South->m_vec_output[0]->acSelect(true);

					m_position->m_X = f_vec_ComList_South->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList_South->m_vec_output[0]->m_position->m_Y;

					m_vec_Selection_output.push_back(f_vec_ComList_South->m_vec_output[0]);
					}break;
				case 2: //wire
					{
					f_vec_ComList_South->m_vec_wire[0]->acSelect(true);

					//ag_StatusLive(f_ref_CurrentPath, "m_position");
					m_position = std::make_shared<Cube::BiVector>(f_vec_ComList_South->m_vec_wire[0]->m_Xmin, f_vec_ComList_South->m_vec_wire[0]->m_Ymin, 0.0f);

					m_vec_Selection_wire.push_back(f_vec_ComList_South->m_vec_wire[0]);
					}break;
				}
			}
		else
			{
			//unary zero 0.0f 0.0f 0.0f

			std::shared_ptr<SelectionPreList> f_vec_ComList = acMakeList();

			for(int f_XY = 0; f_XY < m_vec_HighLighted_com.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = m_vec_HighLighted_com[f_XY];

#if 0
				f_vec_ComList->acPush(f_Com);
#endif

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Input.size(); f_Jet++)
					{
					std::shared_ptr<QcomInput> f_Input = f_Com->m_vec_Input[f_Jet];

					f_vec_ComList->acPush(f_Com);
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_Output.size(); f_Jet++)
					{
					std::shared_ptr<QcomOutput> f_Output = f_Com->m_vec_Output[f_Jet];

					f_vec_ComList->acPush(f_Com);
					}

				for(int f_Jet = 0; f_Jet < f_Com->m_vec_ComWire.size(); f_Jet++)
					{
					std::shared_ptr<QcomWire> f_Wire = f_Com->m_vec_ComWire[f_Jet];

					f_vec_ComList->acPush(f_Com);
					}
				}

			if((f_vec_ComList->m_vec_com.size() <= 0) && (f_vec_ComList->m_vec_input.size() <= 0) &&
				(f_vec_ComList->m_vec_output.size() <= 0) && (f_vec_ComList->m_vec_wire.size() <= 0))
				{
				return false;
				}

			int f_type = f_vec_ComList->acSelectionList_ByBiDistanceChase();

			switch(f_type)
				{
				case 0:	//input
					{
					f_vec_ComList->m_vec_input[0]->acSelect(true);

					m_position->m_X = f_vec_ComList->m_vec_input[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList->m_vec_input[0]->m_position->m_Y;

					m_vec_Selection_input.push_back(f_vec_ComList->m_vec_input[0]);
					}break;
				case 1: //output
					{
					f_vec_ComList->m_vec_output[0]->acSelect(true);

					m_position->m_X = f_vec_ComList->m_vec_output[0]->m_position->m_X;
					m_position->m_Y = f_vec_ComList->m_vec_output[0]->m_position->m_Y;

					m_vec_Selection_output.push_back(f_vec_ComList->m_vec_output[0]);
					}break;
				case 2: //wire
					{
					f_vec_ComList->m_vec_wire[0]->acSelect(true);

					//ag_StatusLive(f_ref_CurrentPath, "m_position");
					m_position = std::make_shared<Cube::BiVector>(f_vec_ComList->m_vec_wire[0]->m_Xmin, f_vec_ComList->m_vec_wire[0]->m_Ymin, 0.0f);

					m_vec_Selection_wire.push_back(f_vec_ComList->m_vec_wire[0]);
					}break;
				}

			return true;
			}
		}

	return false;
}

};