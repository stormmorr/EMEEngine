/*

Cube.h - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <string>
#include <iostream>

#ifdef JNI
#include <dxgi1_4.h>
#include <d3d11_3.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>
#include "DeviceResources.h"
#include "ShaderStructures.h"
#else
#include "Common/DeviceResources.h"
#include "Content/ShaderStructures.h"
#endif

#include "Code/Musion/Code.h"
#include "Code/Musion/CodeLine.h"
#include "Code/Musion/Function.h"
#include "Code/Musion/Operator.h"
#include "Code/Musion/System.h"

#include "math.h"

//Include Bitcoin Key
#include "key.h"

#include "picosha2.h"

using namespace ecoin;
using namespace Cube;

namespace ecoin
{

	class Contract;

}

#define PI ((float)3.14159265358979323846f)

#if 0
#define uint unsigned int
#else
#define uint int
#endif

#define ECN_TX_FEE 0.01

#if 1
#define ECOIN_SECURE 1
#endif

#if 1
#define ECOIN_QCOM_UPDATE_FROM_HESH 1
#endif

#if 0
#define ECOIN_STORE_SIM 1
#endif

#define ECOIN_TX_NIB_SIZE 12
#define ECOIN_TX_CONFIRM_SIZE 3 //reccomended 1-3 slower less compute production
#define ECOIN_TX_REFERON_NIB_RATIO 1
#define ECOIN_TX_BLOCK_NIB_COUNT 2

    /////////////////////////
   // ICS Forward Defines //
  /////////////////////////

#define ICS_FLOAT 5.6f
#define ICS_FLOAT_MID_FIRST 1.0f
#define ICS_FLOAT_MID_SECOND 2.0f
#define ICS_INTEGER_STACK_HIGH 1000000

#define ICS_INTEGER_STACK (ICS_INTEGER_STACK_HIGH / 3)
#define ICS_FLOAT_STACK_HIGH ((ICS_FLOAT * 2.0f) - ICS_FLOAT_MID_SECOND)
#define ICS_FLOAT_VALUE_MUL (ICS_FLOAT_STACK_HIGH / ICS_INTEGER_STACK)
#define ICS_FLOAT_MID_INT (ICS_FLOAT_MID_SECOND / ICS_FLOAT_VALUE_MUL)
#define ICS_FLOAT_HALF (ICS_FLOAT_STACK_HIGH * 0.5f)
#define ICS_FLOAT_MIN (ICS_FLOAT * -1.0f)
#define ICS_FLOAT_MAX ICS_FLOAT
#define ICS_INT_MID_FIRST (ICS_FLOAT_MID_FIRST / ICS_FLOAT_VALUE_MUL)
#define ICS_INT_MID_SECOND (ICS_FLOAT_MID_SECOND / ICS_FLOAT_VALUE_MUL)

#define ICS_RESULTANT_COUNT 12
#define ICS_RESULTANT_POINT_COUNT 11
#define ICS_RESULTANT_MIN ICS_FLOAT_MIN
#define ICS_RESULTANT_MAX ICS_FLOAT_MAX
#define ICS_RESULTANT_FACTOR (ICS_FLOAT_STACK_HIGH / ICS_RESULTANT_COUNT)
#define ICS_RESULTANT_POINT ((ICS_RESULTANT_POINT_COUNT * ICS_RESULTANT_FACTOR) + ICS_FLOAT_MID_SECOND)

    ///////////////
   /// Globals ///
  ///////////////

extern char* g_heshfield[60];
extern char* g_cubefield[60];
extern char* g_adifield[60];
extern char* g_blockfield[60];
extern char* g_sharefield[60];
extern char* g_jobfield[60];
extern char* g_jobvarfield[60];
extern char* g_transfield[60];
extern char* g_addrfield[60];
extern char* g_eventfield[60];
extern char* g_reffield[60];
extern char* g_chancefield[60];
extern char* g_txinsyncfield[60];
extern char* g_txoutsyncfield[60];
extern char* g_syncfield[60];

extern int g_HeshFieldCount;
extern int g_CubeFieldCount;
extern int g_ShareFieldCount;
extern int g_BlockFieldCount;
extern int g_TransFieldCount;

extern time_t g_Currtime;
extern time_t g_Storetime;
extern time_t g_CurrtimeSEC;
extern time_t g_StoretimeSEC;
extern time_t g_currenttime;
extern time_t g_storagetime;
extern int g_timeDiff;
extern int g_timeActual;
extern int g_timeCnt;
extern int g_timeCntLast;
extern winrt::hstring g_timetext;
extern ULONGLONG g_TimeStamp;
extern float g_RADX;
extern float g_RADY;
extern float g_RADZ;

extern bool g_Hold;

extern std::vector<int> g_vec_Cube;

extern ULONGLONG g_TimeStamp;

extern bool g_HeshFull;
extern int g_Timer;
extern int g_ID;
extern bool g_FlipRefreshMiner;

extern char* g_AppLog;
extern std::string g_KHash;
extern std::string g_AddtoOut;

extern int g_nomHesh;

extern std::vector<int> g_vec_Bookmark;

extern std::string g_FilePath;

extern int g_JobID;
extern int g_BlockType;

extern double g_AverageSaleValue;
extern double g_EcoinDifficulty;

extern std::string g_Tab[9];

extern int g_TabSelected;

extern int g_codeON;
extern int g_codemode;
extern std::string g_codeCMD;
extern winrt::hstring g_curr_Selection;
extern int g_curr_SelectionEnd;
extern int g_curr_SelectionStart;

extern int g_codeIndex;
extern std::string g_codeStorage[4];

extern int g_Var1Type;
extern std::string g_Var1Name;
extern float g_Var1Float;
extern int g_Var1Int;

extern int g_Var2Type;
extern std::string g_Var2Name;
extern float g_Var2Float;
extern int g_Var2Int;

extern int g_OprType;
extern std::string g_OprName;

extern int g_FuncType;
extern std::string g_FuncName;

extern int g_Arg1Type;
extern std::string g_Arg1Name;
extern float g_Arg1Float;
extern int g_Arg1Int;

extern int g_Arg2Type;
extern std::string g_Arg2Name;
extern float g_Arg2Float;
extern int g_Arg2Int;

extern picosha2::hash256_one_by_one g_hasha;

#define ESL_COMMAND_CLOSE 0
#define ESL_COMMAND_OPEN 1

#define ESL_CMDMODE_VAR 0
#define ESL_CMDMODE_OPR 1
#define ESL_CMDMODE_FUNC 2

namespace Cube
{

extern bool ag_hex2bin(unsigned char *p, const char *hexstr, size_t len);
extern void ag_bin2hex(char *s, std::vector<unsigned int> p, size_t len);
extern void ag_bin2hex(char *s, std::vector<unsigned char> p, size_t len);
extern void ag_bin2hex(char *s, float p);
extern char *phex(const void *p, size_t n);

extern char* ag_ClearChar(int f_Size);

  ///////////////////////////
 // Save Complete Publish //
//
#define SCP_FLT_SCALE 1.0f
#define SCP_PREC_UPP 500.0f
#define SCP_PREC_ONE 0.11072891f
#define SCP_PREC_TEN 1.51467891f
#define SCP_PREC_LGE 33.01435412f
#define SCP_LEN_AMP 3.47198474f
#define SCP_ELM_PUSH 2.57198474f
#define SCP_ELM_ONCE 3
#define SCP_ADD_ON 2.0f

#define CUBE_TX_TYPE_ATOB 1
#define CUBE_TX_TYPE_ATOBCHANGE 2
#define CUBE_TX_TYPE_GENESIS 3
#define CUBE_TX_TYPE_GENESIS_REWARD 4
#define CUBE_TX_TYPE_GENESIS_TRADE_REWARD 5
#define CUBE_TX_TYPE_TRADE_REWARD 6

#define VERIFY_FAIL false
#define VERIFY_SUCCEEDING true

#define CUBE_COM_TYPE_RACKLEVEL 0
#define CUBE_COM_TYPE_COMPONENT 1

#define CUBE_COM_FACTORY_OSCILLATOR 0
#define CUBE_COM_FACTORY_ADSR 1
#define CUBE_COM_FACTORY_HIPASSFILTER 2
#define CUBE_COM_FACTORY_LOPASSFILTER 3
#define CUBE_COM_FACTORY_DISTORTION 4
#define CUBE_COM_FACTORY_LFO 5
#define CUBE_COM_FACTORY_COMPRESSOR 6
#define CUBE_COM_FACTORY_CHORUS 7
#define CUBE_COM_FACTORY_REVERB 8
#define CUBE_COM_FACTORY_DELAY 9
#define CUBE_COM_FACTORY_FREQUENCER 10
#define CUBE_COM_FACTORY_SEQUENCER 11
#define CUBE_COM_FACTORY_PINBOARDSEQUENCER 12
#define CUBE_COM_FACTORY_LEVEL 13
#define CUBE_COM_FACTORY_MIDIIN 14
#define CUBE_COM_FACTORY_MIDIOUT 15
#define CUBE_COM_FACTORY_FLOATIN 16
#define CUBE_COM_FACTORY_FLOATOUT 17
#define CUBE_COM_FACTORY_VOLTIN 18
#define CUBE_COM_FACTORY_VOLTOUT 19
#define CUBE_COM_FACTORY_POSTIN 20
#define CUBE_COM_FACTORY_POSTOUT 21
#define CUBE_COM_FACTORY_MIDIPATCH 22
#define CUBE_COM_FACTORY_FLOATPATCH 23
#define CUBE_COM_FACTORY_VOLTPATCH 24
#define CUBE_COM_FACTORY_POSTPATCH 25
#define CUBE_COM_FACTORY_KNOB 26
#define CUBE_COM_FACTORY_VERTSLIDER 27
#define CUBE_COM_FACTORY_HORIZSLIDER 28
#define CUBE_COM_FACTORY_BUTTON 29

#define CUBE_TRI_SHOT_A 0
#define CUBE_TRI_SHOT_B 1
#define CUBE_TRI_SHOT_C 2
#define CUBE_TRI_SHOT_TOTAL 100

#define GEN_MAX_CON 8

#define CUBE_LOG_WELD_ATTACH 0
#define CUBE_LOG_SERVED 1
#define CUBE_LOG_POSITIONED 2
#define CUBE_LOG_PUSHBACK 3
#define CUBE_LOG_PULLFORD 4
#define CUBE_LOG_GROW 5
#define CUBE_LOG_SHRINK 6
#define CUBE_LOG_TRANSLATION 7
#define CUBE_LOG_TRANSFORMATION 8

#define CUBE_PUCK_BASE 10

#define CUBE_PORT_XNEG 0
#define CUBE_PORT_XPOS 1
#define CUBE_PORT_YNEG 2
#define CUBE_PORT_YPOS 3
#define CUBE_PORT_ZNEG 4
#define CUBE_PORT_ZPOS 5

#if 0
#define CUBE_AABB_USE_COLOR
#endif

#define CUBE_RND_WARM 35000
#define CUBE_RND_TOLL 500
#define CUBE_RAND3 1
#define CUBE_HESH_SIZE 26

#if 0
#define CUBE_LAYER true
#endif

#define CUBEBIT_DEFAULT_MAX_INT 65535
#define CUBEBIT_DEFAULT_MIN_INT 0
#define CUBEBIT_DEFAULT_MAX_FLOAT 1.0f
#define CUBEBIT_DEFAULT_MIN_FLOAT 0.0f
#define CUBEBIT_DEFAULT_TYPE 0

#define ACE 0
#define TWO 1
#define THREE 2
#define FOUR 3
#define FIVE 4
#define SIX 5
#define SEVEN 6
#define EIGHT 7
#define NINE 8
#define TEN 9
#define JACK 10
#define QUEEN 11
#define KING 12
#define BICARD_NOMCARD 13
#define BISUIT_CLUBS 0
#define BISUIT_HEARTS 1
#define BISUIT_SPADES 2
#define BISUIT_DIAMONDS 3
#define BISUIT_NOMSUITS 4

#define VECDOM(v1,v2) ((v1).m_X*(v2).m_X+(v1).m_Y*(v2).m_Y+(v1).m_Z*(v2).m_Z)

#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2];

#define ECOIN_CLS_COM 0
#define ECOIN_CLS_INPUT 1
#define ECOIN_CLS_OUTPUT 2
#define ECOIN_CLS_WIRE 3
#define ECOIN_CLS_COM_BIRTH 4
#define ECOIN_CLS_INPUT_BIRTH 5
#define ECOIN_CLS_OUTPUT_BIRTH 6
#define ECOIN_CLS_WIRE_BIRTH 7

	  ////////////////////
	 // TAPE
	//
	extern void seedrand(int f_Seed);
	extern float randomTape(void);

	extern void TapeOn(void);
	extern void TapeOff(void);

	extern int m_currentTape;
	extern bool m_TapeStatus;

	  /////////////////////
	 // Random
	//
	extern int randomFac(void);
	extern float random(void);
	extern float ag_RVC(void);
	extern int g_Fingat;
	extern float g_swit;

	class CubeBicycle;
	class float3;
	class float4;
	class aabb;
	class BiVector;
	class osiBiVector;

	class BiColor
		{
		public:
			BiColor()
				{
				std::string f_ref_CurrentPath = "BiTex::BiTex";

				m_R = 0;
				m_G = 0;
				m_B = 0;
				m_A = 0;
				}

			BiColor(float r, float g, float b, float a)
				{
				m_R = r;
				m_G = g;
				m_B = b;
				m_A = a;
				}

			~BiColor() {};

			float m_R;
			float m_G;
			float m_B;
			float m_A;
		};

	class BiTex
		{
		public:
			BiTex()
				{
				std::string f_ref_CurrentPath = "BiTex::BiTex";

				m_U = 0;
				m_V = 0;
				}

			BiTex(float u, float v)
				{
				std::string f_ref_CurrentPath = "BiTex::BiTex";

				m_U = u;
				m_V = v;
				}

			~BiTex() {};

			float m_U;
			float m_V;
		};

	struct Carriage
		{
		float m_X;
		float m_Y;
		float m_Z;
		};

	extern Carriage agRun_visualminer(float f_X, float f_Y, float f_Z);

	class CubeKEY : public ecom_base
		{
		public:
			CubeKEY();

			void acPush(int f_Type);

			std::shared_ptr<BiVector> acCenter(void);

			int acFindinLog(int f_Msg);

			bool m_Served;

			std::shared_ptr<aabb> m_aabb;
			std::shared_ptr<CubeBicycle> m_Link;

			int nom_Child;
			int nom_Parent;

			std::vector<unsigned int> vec_Log;

			std::vector<std::shared_ptr<Cube::CubeKEY>> vec_Child;
			std::vector<std::shared_ptr<Cube::CubeKEY>> vec_Parent;
		};

	class CubeResults : public ecom_base
		{
		public:
			CubeResults()
				{
				std::string f_ref_CurrentPath = "ag_GatherTransactions";

#ifndef OSI_MEM_APP
				ac_Push(m_FinalResult, f_ref_CurrentPath + g_ref_Div + "m_FinalResult");
				ac_Push(m_CurrentNib, f_ref_CurrentPath + g_ref_Div + "m_CurrentNib");
				ac_Push(m_ReferencesPad, f_ref_CurrentPath + g_ref_Div + "m_ReferencesPad");
				ac_Push(m_Result, f_ref_CurrentPath + g_ref_Div + "m_Result");
				ac_Push(m_HashNibCount, f_ref_CurrentPath + g_ref_Div + "m_HashNibCount");
#endif

				acClear();
				}

			~CubeResults()
				{
				acClear();
				}

			void acClear()
				{
				m_FinalResult.clear();
				m_CurrentNib.clear();
				m_ReferencesPad.clear();
				m_Result.clear();
				m_HashNibCount = 0;
				m_Job_Complete = false;
				}

			std::string m_FinalResult;
			std::string m_CurrentNib;
			std::string m_ReferencesPad;
			std::string m_Result;
			int m_HashNibCount;
			bool m_Job_Complete;
		};

	class BicycleContainer : public ecom_base
		{
		public:
			BicycleContainer()
				{
				std::string f_ref_CurrentPath = "BicycleContainer::BicycleContainer";

				acClear();

#ifndef OSI_MEM_APP
				ac_Push(m_ADMAX, f_ref_CurrentPath + g_ref_Div + "m_ADMAX");
				ac_Push(m_ADHIGH, f_ref_CurrentPath + g_ref_Div + "m_ADHIGH");
				ac_Push(m_ADLOW, f_ref_CurrentPath + g_ref_Div + "m_ADLOW");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "avStage", (void(ecom_base::*)(void))&BicycleContainer::avStage);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_IsOK", (void(ecom_base::*)(void))&BicycleContainer::ac_IsOK);
#endif
				}

			~BicycleContainer()
				{
				acClear();
				}

			void acClear(void)
				{
				vec_Key.clear();

				m_ADMAX = 15;
				m_ADHIGH = 15;
				m_ADLOW = 4;
				}

			void avStage(void);
			void ac_IsOK(void);

			std::vector<std::shared_ptr<CubeKEY>> vec_Key;

			int m_ADMAX;
			int m_ADHIGH;
			int m_ADLOW;
		};

	extern std::vector<std::shared_ptr<BicycleContainer>> g_BicycleContainer;

	class CubeTXIN : public ecom_base
		{
		public:
			CubeTXIN()
				{
				std::string f_ref_CurrentPath = "CubeTXIN::CubeTXIN";

				acClear();

#ifndef OSI_MEM_APP
				ac_Push(m_txid, f_ref_CurrentPath + g_ref_Div + "m_txid");
				ac_Push(m_txinid, f_ref_CurrentPath + g_ref_Div + "m_txinid");
				ac_Push(m_gnshareid, f_ref_CurrentPath + g_ref_Div + "m_gnshareid");
				ac_Push(m_vout, f_ref_CurrentPath + g_ref_Div + "m_vout");
				ac_Push(m_pubkey, f_ref_CurrentPath + g_ref_Div + "m_pubkey");
				ac_Push(m_sig, f_ref_CurrentPath + g_ref_Div + "m_sig");
				ac_Push(m_sigstr, f_ref_CurrentPath + g_ref_Div + "m_sigstr");
				ac_Push(m_amt, f_ref_CurrentPath + g_ref_Div + "m_amt");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&CubeTXIN::acClear);
#endif
				}

			~CubeTXIN()
				{
				acClear();
				}

			void acClear(void)
				{
				m_txid = -1;
				m_txinid = -1;
				m_gnshareid = -1;
				m_vout.clear();
				m_pubkey.clear();
				m_sig.clear();
				m_sigstr.clear();
				}

			int m_txid;
			int m_txinid;
			int m_gnshareid;
			std::string m_vout;
			std::string m_pubkey;
			std::vector<unsigned char> m_sig;
			std::string m_sigstr;
			float m_amt;
		};

	class CubeTXOUT : public ecom_base
		{
		public:
			CubeTXOUT()
				{
				std::string f_ref_CurrentPath = "CubeTXOUT::CubeTXOUT";

				acClear();

#ifndef OSI_MEM_APP
				ac_Push(m_txid, f_ref_CurrentPath + g_ref_Div + "m_txid");
				ac_Push(m_txoutid, f_ref_CurrentPath + g_ref_Div + "m_txoutid");
				ac_Push(m_adrid, f_ref_CurrentPath + g_ref_Div + "m_adrid");
				ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
				ac_Push(m_txoutamt, f_ref_CurrentPath + g_ref_Div + "m_txoutamt");
				ac_Push(m_owneramt, f_ref_CurrentPath + g_ref_Div + "m_owneramt");
				ac_Push(m_Flag, f_ref_CurrentPath + g_ref_Div + "m_Flag");
				ac_Push(m_myelementcount, f_ref_CurrentPath + g_ref_Div + "m_myelementcount");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&CubeTXOUT::acClear);
#endif
				}

			~CubeTXOUT()
				{
				acClear();
				}

			void acClear(void)
				{
				m_txid = -1;
				m_txoutid = -1;
				m_adrid = -1;
				m_owner.clear();
				m_txoutamt = 0.0f;
				m_owneramt = 0.0f;
				m_Flag = 0;
				m_myelementcount = 0;
				}

			int m_txid;
			int m_txoutid;
			int m_adrid;
			int m_myelementcount;
			std::string m_owner;
			float m_txoutamt;
			float m_owneramt;
			int m_Flag;
		};

	class CubeTransaction : public ecom_base
		{
		public:
			CubeTransaction()
				{
				std::string f_ref_CurrentPath = "CubeTransaction::CubeTransaction";

				acClear();

#ifndef OSI_MEM_APP
				ac_Push(m_txid, f_ref_CurrentPath + g_ref_Div + "m_txid");
				ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
				ac_Push(m_hdid, f_ref_CurrentPath + g_ref_Div + "m_hdid");
				ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
				ac_Push(m_amt, f_ref_CurrentPath + g_ref_Div + "m_amt");
				ac_Push(m_fee, f_ref_CurrentPath + g_ref_Div + "m_fee");
				ac_Push(m_reward, f_ref_CurrentPath + g_ref_Div + "m_reward");
				ac_Push(m_status, f_ref_CurrentPath + g_ref_Div + "m_status");
				ac_Push(m_type, f_ref_CurrentPath + g_ref_Div + "m_type");
				ac_Push(m_jobid, f_ref_CurrentPath + g_ref_Div + "m_jobid");
				ac_Push(m_rewardid, f_ref_CurrentPath + g_ref_Div + "m_rewardid");
				ac_Push(m_shareid, f_ref_CurrentPath + g_ref_Div + "m_shareid");
				ac_Push(m_confirmation, f_ref_CurrentPath + g_ref_Div + "m_confirmation");
				ac_Push(m_locktime, f_ref_CurrentPath + g_ref_Div + "m_locktime");
				ac_Push(m_fresh, f_ref_CurrentPath + g_ref_Div + "m_fresh");
				ac_Push(m_blocktype, f_ref_CurrentPath + g_ref_Div + "m_blocktype");
				ac_Push(m_Hashnib, f_ref_CurrentPath + g_ref_Div + "m_Hashnib");
				ac_Push(m_blockid, f_ref_CurrentPath + g_ref_Div + "m_blockid");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHash", (void(ecom_base::*)(void))&CubeTransaction::acHash);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSynchronize", (void(ecom_base::*)(void))&CubeTransaction::acSynchronize);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acUpdateSync", (void(ecom_base::*)(void))&CubeTransaction::acUpdateSync);
#endif
				}

			~CubeTransaction()
				{
				m_txin.clear();
				m_txout.clear();
				}

			CubeTransaction(std::string f_A, std::string f_B, float f_amt)
				{
				std::string f_ref_CurrentPath = "CubeTransaction::CubeTransaction";

				acClear();

				ag_StatusLive(f_ref_CurrentPath, "f_txin");
				std::shared_ptr<CubeTXIN> f_txin = std::make_shared_reflect<CubeTXIN>();

				f_txin->m_vout = f_A;
				m_txin.push_back(f_txin);

				ag_StatusLive(f_ref_CurrentPath, "f_txout");
				std::shared_ptr<CubeTXOUT> f_txout = std::make_shared_reflect<CubeTXOUT>();

				f_txout->m_owner = f_B;
				f_txout->m_txoutamt = f_amt;
				f_txout->m_owneramt = f_amt;

				m_amt = f_amt;
				m_txout.push_back(f_txout);

#ifndef OSI_MEM_APP
				ac_Push(m_txid, f_ref_CurrentPath + g_ref_Div + "m_txid");
				ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
				ac_Push(m_hdid, f_ref_CurrentPath + g_ref_Div + "m_hdid");
				ac_Push(m_owner, f_ref_CurrentPath + g_ref_Div + "m_owner");
				ac_Push(m_amt, f_ref_CurrentPath + g_ref_Div + "m_amt");
				ac_Push(m_fee, f_ref_CurrentPath + g_ref_Div + "m_fee");
				ac_Push(m_reward, f_ref_CurrentPath + g_ref_Div + "m_reward");
				ac_Push(m_status, f_ref_CurrentPath + g_ref_Div + "m_status");
				ac_Push(m_type, f_ref_CurrentPath + g_ref_Div + "m_type");
				ac_Push(m_jobid, f_ref_CurrentPath + g_ref_Div + "m_jobid");
				ac_Push(m_rewardid, f_ref_CurrentPath + g_ref_Div + "m_rewardid");
				ac_Push(m_shareid, f_ref_CurrentPath + g_ref_Div + "m_shareid");
				ac_Push(m_confirmation, f_ref_CurrentPath + g_ref_Div + "m_confirmation");
				ac_Push(m_locktime, f_ref_CurrentPath + g_ref_Div + "m_locktime");
				ac_Push(m_fresh, f_ref_CurrentPath + g_ref_Div + "m_fresh");
				ac_Push(m_blocktype, f_ref_CurrentPath + g_ref_Div + "m_blocktype");
				ac_Push(m_Hashnib, f_ref_CurrentPath + g_ref_Div + "m_Hashnib");
				ac_Push(m_blockid, f_ref_CurrentPath + g_ref_Div + "m_blockid");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acHash", (void(ecom_base::*)(void))&CubeTransaction::acHash);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSynchronize", (void(ecom_base::*)(void))&CubeTransaction::acSynchronize);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acUpdateSync", (void(ecom_base::*)(void))&CubeTransaction::acUpdateSync);
#endif
				}

			void acClear(void)
				{
				m_txin.clear();
				m_txout.clear();
				m_amt = 0.0f;
				m_blocktype = -1;
				m_Hash = "";
				m_Hashnib = "G";
				m_txid = -1;
				m_fee = 0.0f;
				m_blockid = 0;
				m_hdid = "";
				m_owner = "";
				m_reward = 0.0f;
				m_rewardid = 0;
				m_status = 1;
				m_type = 0;
				m_shareid = 0;
				m_confirmation = 0;
				m_locktime = 0;
				m_fresh = true;
				}

			bool isValid(void)
				{
				std::string f_ref_CurrentPath = "CubeTransaction::isValid";

				bool f_Valid = true;

				if(m_txout.size() < 1)
					{
					f_Valid = false;

					return f_Valid;
					}

				if(m_txin.size() != 1)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_txin");
					std::shared_ptr<CubeTXIN> f_txin = std::make_shared_reflect<CubeTXIN>();

					f_txin->m_vout = "Genesis Tracking";
					m_txin.push_back(f_txin);

					char* g_txinsyncvalue[6];

					for(int f_s1 = 0; f_s1 < 6; f_s1++)
						{
						g_txinsyncvalue[f_s1] = (char*)malloc(sizeof(char) * 256);
						}

					printf("Connected to ecoin server...\n");

					sprintf(g_txinsyncvalue[0], "%i", m_txid);
					sprintf(g_txinsyncvalue[1], "%s", f_txin->m_vout.c_str());
					sprintf(g_txinsyncvalue[2], "");
					sprintf(g_txinsyncvalue[3], "");
					sprintf(g_txinsyncvalue[4], "%f", 0.0f);
					sprintf(g_txinsyncvalue[5], "%i", 1);

					g_SafeL[0]->Insert("txin", (const char **)g_txinsyncfield, (const char **)g_txinsyncvalue, 6, false, false);
					}

				if(m_txin[0]->m_txid == -1)
					{
					f_Valid = false;
					}

				if(m_txout[0]->m_txid == -1)
					{
					f_Valid = false;
					}

				return f_Valid;
				}

			std::vector<std::shared_ptr<CubeTXIN>> m_txin;
			std::vector<std::shared_ptr<CubeTXOUT>> m_txout;

			void acHash(void);
			void acSynchronize(void);
			void acUpdateSync(void);

			std::string m_Hash;
			std::string m_Hashnib;
			std::string m_hdid;
			std::string m_owner;

			float m_amt;
			float m_fee;
			float m_reward;

			int m_status;
			int m_type;
			int m_txid;
			int m_jobid;
			int m_rewardid;
			int m_blocktype;
			int m_shareid;
			int m_confirmation;
			int m_locktime;
			int m_blockid;

			bool m_fresh;
		};

	class CubeCollision : public ecom_base
		{
		public:
			CubeCollision()
				{
				std::string f_ref_CurrentPath = "CubeCollision::CubeCollision";

				m_BicycleIndex = 0;
				m_SideIndex = 0;

#ifndef OSI_MEM_APP
				ac_Push(m_BicycleIndex, f_ref_CurrentPath + g_ref_Div + "m_BicycleIndex");
				ac_Push(m_SideIndex, f_ref_CurrentPath + g_ref_Div + "m_SideIndex");
#endif
				}

			CubeCollision(int f_B, int f_S)
				{
				std::string f_ref_CurrentPath = "CubeCollision::CubeCollision";

				m_BicycleIndex = f_B;
				m_SideIndex = f_S;

#ifndef OSI_MEM_APP
				ac_Push(m_BicycleIndex, f_ref_CurrentPath + g_ref_Div + "m_BicycleIndex");
				ac_Push(m_SideIndex, f_ref_CurrentPath + g_ref_Div + "m_SideIndex");
#endif
				}

			~CubeCollision()
				{
				m_BicycleIndex = 0;
				m_SideIndex = 0;
				}

			int m_BicycleIndex;
			int m_SideIndex;
		};

	class CubeHASH_originstring : public ecom_base
		{
		public:
			CubeHASH_originstring()
				{
				std::string f_ref_CurrentPath = "CubeHASH_originstring::CubeHASH_originstring";

				acClear();
				
#ifndef OSI_MEM_APP
				ac_Push(m_str_Input, f_ref_CurrentPath + g_ref_Div + "m_str_Input");
				ac_Push(m_OutputHash, f_ref_CurrentPath + g_ref_Div + "m_OutputHash");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&CubeHASH_originstring::acClear);
#endif
				};

			~CubeHASH_originstring() { acClear(); };

			void acClear()
				{
				m_str_Input.clear();
				m_OutputHash.clear();
				}

			void acPushBool(bool f_Bool)
				{
				if(f_Bool)
					{
					m_str_Input += "1";
					}
				else
					{
					m_str_Input += "0";
					}
				}

			void acPushInt(int f_Int)
				{
				char* f_Char = ag_ClearChar(128);
				sprintf(f_Char, "%i", f_Int);
				m_str_Input += f_Char;
				delete f_Char;
				}

			void acPushFloat(float f_Float)
				{
				char* f_Char = ag_ClearChar(128);
				sprintf(f_Char, "%f", f_Float);
				m_str_Input += f_Char;
				delete f_Char;
				}

			void acPushDouble(double f_Double)
				{
				char* f_Char = ag_ClearChar(128);
				sprintf(f_Char, "%lf", f_Double);
				m_str_Input += f_Char;
				delete f_Char;
				}

			void acPushString(std::string f_String)
				{
				m_str_Input += f_String;
				}

			std::string acGetInput(void)
				{
				return m_str_Input;
				}

			int acSize(void)
				{
				return m_str_Input.size();
				}

			std::string m_str_Input;
			std::string m_OutputHash;
		};

	class CubeHASH : public ecom_base
		{
		public:
			CubeHASH()
				{
				std::string f_ref_CurrentPath = "CubeHASH::CubeHASH";

				m_vec_Input.clear();
				m_OutputHash.clear();

#ifndef OSI_MEM_APP
				ac_Push(m_vec_Input, f_ref_CurrentPath + g_ref_Div + "m_vec_Input");
				ac_Push(m_OutputHash, f_ref_CurrentPath + g_ref_Div + "m_OutputHash");
#endif
				};

			~CubeHASH()
				{
				m_vec_Input.clear();
				m_OutputHash.clear();
				};

			std::vector<unsigned int> m_vec_Input;
			std::string m_OutputHash;
		};

	class unMutexCC : public ecom_base
		{
		public:
			unMutexCC()
				{
				mBlock = false;
				mFired = false;
				}
			~unMutexCC() {};
	
			bool mBlock;
			bool mFired;

			void ac_Fire(void)
				{
				int f_x = 1;
				if(f_x == 5)
					{
					f_x = 0;
					}
				while(mFired) { /*wait*/ }
				mFired = true;
				printf("ac_Fire\n");
				}

			void ac_Free(void)
				{
				mFired = false;
				printf("ac_Free\n");
				}
		};

	class CubeTier;

	class CubeShare : public ecom_base
		{
		public:
			CubeShare()
				{
				std::string f_ref_CurrentPath = g_ref_global_start + "CubeShare::CubeShare";

				m_ID = 1;
				m_Score = 0;
				m_Owner.clear();
				m_Date.clear();
				m_Amount = 0.0f;
				m_Tier = nullptr;

#ifndef OSI_MEM_APP
				ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
				ac_Push(m_Score, f_ref_CurrentPath + g_ref_Div + "m_Score");
				ac_Push(m_Owner, f_ref_CurrentPath + g_ref_Div + "m_Owner");
				ac_Push(m_Date, f_ref_CurrentPath + g_ref_Div + "m_Date");
				ac_Push(m_Amount, f_ref_CurrentPath + g_ref_Div + "m_Amount");
				ac_Push(m_ECN_Amount, f_ref_CurrentPath + g_ref_Div + "m_ECN_Amount");
				ac_Push(m_RewardAmount, f_ref_CurrentPath + g_ref_Div + "m_RewardAmount");
#endif
				};

			~CubeShare()
				{
				m_ID = 1;
				m_Score = 0;
				m_Owner.clear();
				m_Date.clear();
				m_Amount = 0.0f;
				m_ECN_Amount = 0.0f;
				m_RewardAmount = 0.0f;
				m_Tier = nullptr;
				};

			int m_ID;
			int m_Score;
			std::shared_ptr<CubeTier> m_Tier;
			std::string m_Owner;
			std::string m_Date;
			float m_Amount;
			float m_ECN_Amount;
			float m_RewardAmount;
		};

	class CubeTier : public ecom_base
		{
		public:
			CubeTier()
				{
				std::string f_ref_CurrentPath = g_ref_global_start + "CubeTier::CubeTier";

				m_Level = 0;

#ifndef OSI_MEM_APP
				ac_Push(m_Level, f_ref_CurrentPath + g_ref_Div + "m_Level");
#endif
				};
			~CubeTier()
				{
				m_Level = 0;
				};

			std::vector<std::shared_ptr<CubeShare>> m_vec_Share;
			int m_Level;
		};

	class CubePeer : public ecom_base
		{
		public:
			CubePeer()
				{
				std::string f_ref_CurrentPath = g_ref_global_start + "CubePeer::CubePeer";

				m_Share.clear();
				m_Amount = 0.0f;

#ifndef OSI_MEM_APP
				ac_Push(m_Owner, f_ref_CurrentPath + g_ref_Div + "m_Owner");
				ac_Push(m_Amount, f_ref_CurrentPath + g_ref_Div + "m_Amount");
#endif
				}
			~CubePeer()
				{
				m_Share.clear();
				m_Amount = 0.0f;
				}

			std::vector<std::shared_ptr<CubeShare>> m_Share;
			std::string m_Owner;
			float m_Amount;
			float m_ECN_Amount;
		};

#if 0
	class ShareContainer : public ecom_base
		{
		public:
			ShareContainer()
				{
				std::string f_ref_CurrentPath = "ShareContainer::ShareContainer";

				m_espo_Owner.clear();
				m_espo_Date.clear();
				m_Peer.clear();
				m_espo_ShareOffset = 0;
				m_espo_Peer = 0;
				m_espo_ID = 0;
				m_espo_Score = 0;
				m_espo_Amount = 0.0f;
				m_espo_ECN_Amount = 0.0f;

#ifndef OSI_MEM_APP
				ac_Push(m_espo_Owner, f_ref_CurrentPath + g_ref_Div + "m_espo_Owner");
				ac_Push(m_espo_Date, f_ref_CurrentPath + g_ref_Div + "m_espo_Date");
				ac_Push(m_espo_ShareOffset, f_ref_CurrentPath + g_ref_Div + "m_espo_ShareOffset");
				ac_Push(m_espo_Peer, f_ref_CurrentPath + g_ref_Div + "m_espo_Peer");
				ac_Push(m_espo_ID, f_ref_CurrentPath + g_ref_Div + "m_espo_ID");
				ac_Push(m_espo_Score, f_ref_CurrentPath + g_ref_Div + "m_espo_Score");
				ac_Push(m_espo_Amount, f_ref_CurrentPath + g_ref_Div + "m_espo_Amount");
				ac_Push(m_espo_ECN_Amount, f_ref_CurrentPath + g_ref_Div + "m_espo_ECN_Amount");
#endif
				};

			~ShareContainer()
				{
				m_espo_Owner.clear();
				m_espo_Date.clear();
				m_Peer.clear();
				m_espo_ShareOffset = 0;
				m_espo_Peer = 0;
				m_espo_ID = 0;
				m_espo_Score = 0;
				m_espo_Amount = 0.0f;
				m_espo_ECN_Amount = 0.0f;
				};

			std::shared_ptr<CubePeer> acPeerfromOwner(std::string f_Owner)
				{
				for(int f_Helly = 0; f_Helly < m_Peer.size(); f_Helly++)
					{
					std::shared_ptr<CubePeer> f_Peer = m_Peer[f_Helly];

					if(f_Peer->m_Owner.compare(f_Owner) == 0)
						{
						return f_Peer;
						}
					}

				for(;;)
					{
					//ECN::ADVWARN::Peer not found using owner = f_Owner.c_str();
					}

				return nullptr;
				}

			std::vector<std::shared_ptr<CubePeer>> m_Peer;
			int m_espo_ShareOffset;
			int m_espo_Peer;
			int m_espo_ID;
			int m_espo_Score;
			float m_espo_Amount;
			float m_espo_ECN_Amount;
			std::string m_espo_Owner;
			std::string m_espo_Date;
		};
#endif

	class ShareContainerExt : public ecom_base
		{
		public:
			ShareContainerExt()
				{
				std::string f_ref_CurrentPath = "ShareContainer::ShareContainer";

				m_espo_Owner.clear();
				m_espo_Date.clear();
				m_espo_ShareOffset = 0;
				m_espo_Peer = 0;
				m_espo_ID = 0;
				m_espo_Score = 0.0f;
				m_espo_Amount = 0.0f;
				m_espo_ECN_Amount = 0.0f;
				m_espo_ScoreSum = 0.0f;
				m_espo_PeerCount = 0;
				m_espo_SharesOnPeerCount = 0;
				m_espo_TotalShares = 0;
				m_espo_TotalSharesOwnPeer = 0;

#ifndef OSI_MEM_APP
				ac_Push(m_espo_Owner, f_ref_CurrentPath + g_ref_Div + "m_espo_Owner");
				ac_Push(m_espo_Date, f_ref_CurrentPath + g_ref_Div + "m_espo_Date");
				ac_Push(m_espo_ShareOffset, f_ref_CurrentPath + g_ref_Div + "m_espo_ShareOffset");
				ac_Push(m_espo_Peer, f_ref_CurrentPath + g_ref_Div + "m_espo_Peer");
				ac_Push(m_espo_ID, f_ref_CurrentPath + g_ref_Div + "m_espo_ID");
				ac_Push(m_espo_Score, f_ref_CurrentPath + g_ref_Div + "m_espo_Score");
				ac_Push(m_espo_Amount, f_ref_CurrentPath + g_ref_Div + "m_espo_Amount");
				ac_Push(m_espo_ECN_Amount, f_ref_CurrentPath + g_ref_Div + "m_espo_ECN_Amount");
				ac_Push(m_espo_ScoreSum, f_ref_CurrentPath + g_ref_Div + "m_espo_ScoreSum");
				ac_Push(m_espo_PeerCount, f_ref_CurrentPath + g_ref_Div + "m_espo_PeerCount");
				ac_Push(m_espo_SharesOnPeerCount, f_ref_CurrentPath + g_ref_Div + "m_espo_SharesOnPeerCount");
				ac_Push(m_espo_TotalShares, f_ref_CurrentPath + g_ref_Div + "m_espo_TotalShares");
				ac_Push(m_espo_TotalSharesOwnPeer, f_ref_CurrentPath + g_ref_Div + "m_espo_TotalSharesOwnPeer");
#endif
				};

			~ShareContainerExt()
				{
				m_espo_Owner.clear();
				m_espo_Date.clear();
				m_espo_ShareOffset = 0;
				m_espo_Peer = 0;
				m_espo_ID = 0;
				m_espo_Score = 0.0f;
				m_espo_Amount = 0.0f;
				m_espo_ECN_Amount = 0.0f;
				m_espo_ScoreSum = 0.0f;
				m_espo_PeerCount = 0;
				m_espo_SharesOnPeerCount = 0;
				m_espo_TotalShares = 0;
				m_espo_TotalSharesOwnPeer = 0;
				};

			int m_espo_ShareOffset;
			int m_espo_Peer;
			int m_espo_ID;
			float m_espo_Score;
			float m_espo_Amount;
			float m_espo_ECN_Amount;
			std::string m_espo_Owner;
			std::string m_espo_Date;

			//extras
			float m_espo_ScoreSum;
			int m_espo_PeerCount;
			int m_espo_SharesOnPeerCount;

			int m_espo_TotalShares;
			int m_espo_TotalSharesOwnPeer;
			int m_espo_OwnPeerIndex;
		};

	class BiRand
		{
		public:
			BiRand() { m_Seed = Cube::random(); m_ProgressCount = 0; m_Value = Cube::random(); }
			BiRand(float f_Seed)
				{ m_Seed = f_Seed; m_ProgressCount = 0;	m_Value = Cube::random(); }

			float acGet(void)
				{
				m_Value = Cube::random() * m_Seed;
				m_Seed = Cube::random();
				m_ProgressCount++;
				return m_Value;
				}

		float m_Seed;
		int m_ProgressCount;
		float m_Value;
		};

	class CubeCKey : public ecom_base
		{
		public:
			CubeCKey()
				{
				m_str_Address.clear();
				}
			CubeCKey(CKey f_CKey)
				{
				m_str_Address.clear();
				m_Key = f_CKey;
				}
			~CubeCKey()
				{
				m_str_Address.clear();
				}

			void acSavetoWallet(void);

			void acSerialize(void);
			void acDeSerialize(void);

			CKey m_Key;
			CPubKey m_PubKey;
			std::string m_str_Address;
		};

	class BiCard : public ecom_base
		{
		public:
			BiCard()
				{
				m_Value = Cube::randomFac() % BICARD_NOMCARD;
				m_Suit = Cube::randomFac() % BISUIT_NOMSUITS;
				acCardColour();
				};
			~BiCard() {};

			void Draw(void)
				{
				m_Value = Cube::randomFac() % BICARD_NOMCARD;
				m_Suit = Cube::randomFac() % BISUIT_NOMSUITS;
				acCardColour();
				};

			void acCardColour(void)
				{
				switch(m_Suit)
					{
					case BISUIT_CLUBS:
						{
						m_ColourRed = false;
						m_ColourBlack = true;
						}break;

					case BISUIT_SPADES:
						{
						m_ColourRed = false;
						m_ColourBlack = true;
						}break;

					case BISUIT_DIAMONDS:
						{
						m_ColourRed = true;
						m_ColourBlack = false;
						}break;

					case BISUIT_HEARTS:
						{
						m_ColourRed = true;
						m_ColourBlack = false;
						}break;
					}
				}

			int m_Value;
			int m_Suit;
			bool m_ColourRed;
			bool m_ColourBlack;
		};

	class BiCardPad : public ecom_base
		{
		public:
			BiCardPad() {};
			~BiCardPad() {};

			void Clear(void)
				{
				m_Card.clear();
				};

			void Compute(void)
				{
				m_Card.clear();
				};

			float Play(void)
				{
				float f_Result = 0.0f;
				return f_Result;
				};

			std::vector<BiCard> m_Card;
			bool f_Win;
		};

	class BiDeck : public ecom_base
		{
		public:
			BiDeck() {};
			~BiDeck() {};

			/*void acShuffle(void)
				{
				for(int f_Index = 0; f_Index < 52; f_Index++)
					{
					m_Card[f_Index].Draw();
					}
				}*/

			BiCard acDealOne(void)
				{
				BiCard f_Card;
				return f_Card;
				}

		//BiCard m_Card[52];
		};

	class Bi21 : public ecom_base
		{
		public:
			Bi21(float f_Stake, int f_NomCardPads)
				{  //////////////////////
				  //
				 // Deal First Card
				//
				for(int f_Pad = 0; f_Pad < f_NomCardPads; f_Pad++)
					{
					m_CardPad[f_Pad].m_Card.push_back(m_Deck.acDealOne());
					}

				m_Dealer.m_Card.push_back(m_Deck.acDealOne());

				   //////////////////////
				  //
				 // Deal Second Card
				//
				for(int f_Pad = 0; f_Pad < f_NomCardPads; f_Pad++)
					{
					m_CardPad[f_Pad].m_Card.push_back(m_Deck.acDealOne());
					}

				m_Dealer.m_Card.push_back(m_Deck.acDealOne());
				};
			~Bi21() {};

			float acPlay(void)
				{  //////////////
				  //
				 // Play
				//
				float f_Result = 0.0f;
				for(int f_Pad = 0; f_Pad < m_NomCardPads; f_Pad++)
					{
					f_Result += m_CardPad[f_Pad].Play();
					}

				m_Dealer.Play();
				//if(m_Dealer.)
				};

			float m_Stake;
			int m_NomCardPads;
			BiDeck m_Deck;
			BiCardPad m_CardPad[15];
			BiCardPad m_Dealer;
		};

#ifdef OSI_MEMORY_BIVECTOR_REF

	class BiVector
		{
		public:
			BiVector()
				{
				m_X = 0.0f; m_Y = 0.0f; m_Z = 0.0f;
				}

			BiVector(std::shared_ptr<BiVector> f_Vec)
				{
				m_X = f_Vec->m_X;
				m_Y = f_Vec->m_Y;
				m_Z = f_Vec->m_Z;
				}

			BiVector(float f_X, float f_Y, float f_Z)
				{ 
				m_X = f_X; m_Y = f_Y; m_Z = f_Z;
				}

			BiVector(float f_X, float f_Y, float f_Z, float f_W)
				{
				m_X = f_X; m_Y = f_Y; m_Z = f_Z;
				}

			BiVector(float f_M)
				{
				m_X = f_M; m_Y = f_M; m_Z = f_M;
				}

			BiVector(bool f_Mode)
				{ 
				m_X = 0.0f;
				m_Y = 0.0f;
				m_Z = 0.0f;

				m_Mode = 0;
				}

			void operator*=(const float &f)
				{
				m_X *= f;
				m_Y *= f;
				m_Z *= f;
				}

			BiVector operator*(const float &f)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X * f;
				f_Vector.m_Y = m_Y * f;
				f_Vector.m_Z = m_Z * f;
				return f_Vector;
				}

			void operator+=(const BiVector &v)
				{
				m_X += v.m_X;
				m_Y += v.m_Y;
				m_Z += v.m_Z;
				}

			BiVector operator+(const BiVector &v)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X + v.m_X;
				f_Vector.m_X = m_Y + v.m_Y;
				f_Vector.m_X = m_Z + v.m_Z;
				return f_Vector;
				}

			void operator-=(const BiVector &v)
				{
				m_X -= v.m_X;
				m_Y -= v.m_Y;
				m_Z -= v.m_Z;
				}

			BiVector operator-(const BiVector &v)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X - v.m_X;
				f_Vector.m_Y = m_Y - v.m_Y;
				f_Vector.m_Z = m_Z - v.m_Z;
				return f_Vector;
				}

			void cross(const BiVector &v1, const BiVector &v2)
				{
				m_X = v1.m_Y * v2.m_Z - v1.m_Z * v2.m_Y;
				m_Y = v1.m_Z * v2.m_X - v1.m_X * v2.m_Z;
				m_Z = v1.m_X * v2.m_Y - v1.m_Y * v2.m_X;
				}

			void acPushRandSphere(float f_Radius, float f_Seed)
				{
				f_Radius *= 1.5;

				for(int f_Cntr = 0; f_Cntr < 7; f_Cntr++)
					{
					BiRand f_BiRand(f_Seed);
					BiVector f_Vector((f_BiRand.acGet() - 0.5f) * f_Radius, (f_BiRand.acGet() - 0.5f) * f_Radius, (f_BiRand.acGet() - 0.5f) * f_Radius);
				
					m_X += f_Vector.m_X * f_Radius;
					m_Y += f_Vector.m_Y * f_Radius;
					m_Z += f_Vector.m_Z * f_Radius;
					}
				}

			void acRun_visualminer(int g_Verbose = false)
				{
				BiVector f_Result;
				Carriage f_Car;
				f_Car = Cube::agRun_visualminer(m_X, m_Y, m_Z);

				m_X = f_Car.m_X;
				m_Y = f_Car.m_Y;
				m_Z = f_Car.m_Z;
				}

			void acBoundaryRanging(void)
				{
				if((m_X < 1.0f) && (m_X > 0.0f))
					{
					while(m_X < 1.0f)
						{
						m_X += SCP_PREC_ONE;
						}
					}

				if((m_X > -1.0f) && (m_X < 0.0f))
					{
					while(m_X > -1.0f)
						{
						m_X -= SCP_PREC_ONE;
						}
					}

				if((m_Y < 1.0f) && (m_Y > 0.0f))
					{
					while(m_Y < 1.0f)
						{
						m_Y += SCP_PREC_ONE;
						}
					}

				if((m_Y > -1.0f) && (m_Y < 0.0f))
					{
					while(m_Y > -1.0f)
						{
						m_Y -= SCP_PREC_ONE;
						}
					}

				if((m_Z < 1.0f) && (m_Z > 0.0f))
					{
					while(m_Z < 1.0f)
						{
						m_Z += SCP_PREC_ONE;
						}
					}

				if((m_Z > -1.0f) && (m_Z < 0.0f))
					{
					while(m_Z > -1.0f)
						{
						m_Z -= SCP_PREC_ONE;
						}
					}

				while(m_X >= 10.0f)
					{
					m_X -= SCP_PREC_TEN;
					}

				while(m_X <= -10.0f)
					{
					m_X += SCP_PREC_TEN;
					}

				while(m_Y >= 10.0f)
					{
					m_Y -= SCP_PREC_TEN;
					}

				while(m_Y <= -10.0f)
					{
					m_Y += SCP_PREC_TEN;
					}

				while(m_Z >= 10.0f)
					{
					m_Z -= SCP_PREC_TEN;
					}

				while(m_Z <= -10.0f)
					{
					m_Z += SCP_PREC_TEN;
					}
				}

			void acLargeBoundaryRanging(void)
				{
				while(m_X >= SCP_PREC_UPP)
					{
					m_X -= SCP_PREC_LGE;
					}

				while(m_X <= (-1.0f * SCP_PREC_UPP))
					{
					m_X += SCP_PREC_LGE;
					}

				while(m_Y >= SCP_PREC_UPP)
					{
					m_Y -= SCP_PREC_LGE;
					}

				while(m_Y <= (-1.0f * SCP_PREC_UPP))
					{
					m_Y += SCP_PREC_LGE;
					}

				while(m_Z >= SCP_PREC_UPP)
					{
					m_Z -= SCP_PREC_LGE;
					}

				while(m_Z <= (-1.0f * SCP_PREC_UPP))
					{
					m_Z += SCP_PREC_LGE;
					}
				}

			void acMidShift(void)
				{
				if((m_X > -1.0f) && (m_X < 0.0f))
					{
					m_X += 2.0f;
					}
				else if((m_X >= 0.0f) && (m_X < 1.0f))
					{
					m_X += 1.0f;
					}

				if((m_Y > -1.0f) && (m_Y < 0.0f))
					{
					m_Y += 2.0f;
					}
				else if((m_Y >= 0.0f) && (m_Y < 1.0f))
					{
					m_Y += 1.0f;
					}

				if((m_Z > -1.0f) && (m_Z < 0.0f))
					{
					m_Z += 2.0f;
					}
				else if((m_Z >= 0.0f) && (m_Z < 1.0f))
					{
					m_Z += 1.0f;
					}
				}

			void acIntegerPosition(int f_IntegerValue)
				{
				//Save CheckPoint in Hesh
				int f_VertPush = 0;

				//Index Correction Value
				while(f_IntegerValue > ICS_INTEGER_STACK)
					{
					f_IntegerValue -= ICS_INTEGER_STACK;

					f_VertPush++;
					}

				switch(f_VertPush)
					{
					case 0:
						{
						float f_FloatVertexValue = (float)f_IntegerValue * ICS_FLOAT_VALUE_MUL;

						m_X = f_FloatVertexValue - ICS_FLOAT;

						acMidShift();
						}break;

					case 1:
						{
						float f_FloatVertexValue = (float)f_IntegerValue * ICS_FLOAT_VALUE_MUL;

						m_X = ICS_FLOAT_MAX;
						m_Y = f_FloatVertexValue - ICS_FLOAT;

						acMidShift();
						}break;

					case 2:
						{
						float f_FloatVertexValue = (float)f_IntegerValue * ICS_FLOAT_VALUE_MUL;

						m_X = ICS_FLOAT_MAX;
						m_Y = ICS_FLOAT_MAX;
						m_Z = f_FloatVertexValue - ICS_FLOAT;

						acMidShift();
						}break;

#ifdef ECOIN_DEBUG_BREAKS
					default:
						{
						__debugbreak();
						}break;
#endif
					}
				}

			//Provide Integer
			int acInteger(void)
				{
				int f_IntVertexValue = 0;

				float f_Bertec = m_X;

				if((f_Bertec > -1.0f) && (f_Bertec < 0.0f))
					{
					f_Bertec -= ICS_INT_MID_SECOND;
					}
				else if(f_Bertec >= 0.0f)
					{
					f_Bertec -= ICS_INT_MID_FIRST;
					}

				f_Bertec += ICS_FLOAT;

				f_Bertec /= ICS_FLOAT_VALUE_MUL;

				f_IntVertexValue += (int)f_Bertec;

				if(f_IntVertexValue >= ICS_INTEGER_STACK)
					{
					f_Bertec = m_Y;

					if((f_Bertec > -1.0f) && (f_Bertec < 0.0f))
						{
						f_Bertec -= ICS_INT_MID_SECOND;
						}
					else if(f_Bertec >= 0.0f)
						{
						f_Bertec -= ICS_INT_MID_FIRST;
						}

					f_Bertec += ICS_FLOAT;

					f_Bertec /= ICS_FLOAT_VALUE_MUL;

					f_IntVertexValue += (int)f_Bertec;

					if(f_IntVertexValue >= (ICS_INTEGER_STACK * 2))
						{
						f_Bertec = m_Z;

						if((f_Bertec > -1.0f) && (f_Bertec < 0.0f))
							{
							f_Bertec -= ICS_INT_MID_SECOND;
							}
						else if(f_Bertec >= 0.0f)
							{
							f_Bertec -= ICS_INT_MID_FIRST;
							}

						f_Bertec += ICS_FLOAT;

						f_Bertec /= ICS_FLOAT_VALUE_MUL;

						f_IntVertexValue += (int)f_Bertec;

#ifdef ECOIN_DEBUG_BREAKS
						if(f_IntVertexValue > ICS_INTEGER_STACK_HIGH)
							{
							__debugbreak();
							}
#endif
						}
					}
				
				return f_IntVertexValue;
				}

			void acResolve_precision(float f_Scale)
				{
				acBoundaryRanging();

				m_X *= f_Scale;
				m_Y *= f_Scale;
				m_Z *= f_Scale;
				}

			void acSet(float f_X, float f_Y, float f_Z)
				{
				m_X = f_X;
				m_Y = f_Y;
				m_Z = f_Z;
				}

			void acPrepare(void)
				{
				BiVector f_Result(m_Z * -1, m_Y, m_X);

				m_X = f_Result.m_X;
				m_Y = f_Result.m_Y;
				m_Z = f_Result.m_Z;
				}

			float acDot(void)
				{
				return(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
				}

			float acDot(BiVector f_Vec2)
				{
				return(m_X * f_Vec2.m_X + m_Y * f_Vec2.m_Y + m_Z * f_Vec2.m_Z);
				}

			float acLength(void)
				{
				float f_Length = (float)sqrt(acDot());

				return f_Length;
				}

			BiVector acCross(BiVector f_Up)
				{
				BiVector f_Result(0.0f);

				f_Result.m_X = m_Y * f_Up.m_Z - m_Z * f_Up.m_Y;
				f_Result.m_Y = m_Z * f_Up.m_X - m_X * f_Up.m_Z;
				f_Result.m_Z = m_X * f_Up.m_Y - m_Y * f_Up.m_X;

				return f_Result;
				}

			void acNormalize(void)
				{
				float len = m_X * m_X + m_Y * m_Y + m_Z * m_Z;

				if(len > 0)
					{
					len = 1.0f / sqrtf(len);

					m_X *= len;
					m_Y *= len;
					m_Z *= len;
					}
				}

			void ac_ValueSet(float f_Value)
				{
				if(m_Mode == 0)
					{
					m_X = f_Value;
					}
				else if(m_Mode == 1)
					{
					m_Y = f_Value;
					}
				else if(m_Mode == 2)
					{
					m_Z = f_Value;
					}

				m_Mode += 1;
				}

			char ac_CharValue(void)
				{
				if(m_Mode == 0)
					{
					float f_Result = m_X;

					if((f_Result > -1.0f) && (f_Result < 0.0f))
						{
						f_Result -= ICS_FLOAT_MID_FIRST;
						}
					else if(f_Result >= 0.0f)
						{
						f_Result -= ICS_FLOAT_MID_SECOND;
						}

					int f_Integer = (int)((f_Result + ICS_FLOAT) / ICS_RESULTANT_FACTOR);

					m_Mode += 1;

					if(f_Integer == 11)
						{
						return '.';
						}
					else if(f_Integer == 12)
						{
						return 'E';
						}

					return (char)(f_Integer + '0');
					}
				else if(m_Mode == 1)
					{
					float f_Result = m_Y;

					if((f_Result > -1.0f) && (f_Result < 0.0f))
						{
						f_Result -= ICS_FLOAT_MID_FIRST;
						}
					else if(f_Result >= 0.0f)
						{
						f_Result -= ICS_FLOAT_MID_SECOND;
						}

					int f_Integer = (int)((f_Result + ICS_FLOAT) / ICS_RESULTANT_FACTOR);

					m_Mode += 1;

					if(f_Integer == 11)
						{
						return '.';
						}
					else if(f_Integer == 12)
						{
						return 'E';
						}

					return (char)(f_Integer + '0');
					}
				else if(m_Mode == 2)
					{
					float f_Result = m_Z;

					if((f_Result > -1.0f) && (f_Result < 0.0f))
						{
						f_Result -= ICS_FLOAT_MID_FIRST;
						}
					else if(f_Result >= 0.0f)
						{
						f_Result -= ICS_FLOAT_MID_SECOND;
						}

					int f_Integer = (int)((f_Result + ICS_FLOAT) / ICS_RESULTANT_FACTOR);

					m_Mode += 1;

					if(f_Integer == 11)
						{
						return '.';
						}
					else if(f_Integer == 12)
						{
						return 'E';
						}

					return (char)(f_Integer + '0');
					}
				}

		public:
			float m_X;
			float m_Y;
			float m_Z;

			char m_Mode;
		};

#else

	class BiVector : public ecom_base_flap
		{
		public:
			BiVector()
				{ m_X = 0.0f; m_Y = 0.0f; m_Z = 0.0f; }

			BiVector(float f_X, float f_Y, float f_Z)
				{ m_X = f_X; m_Y = f_Y; m_Z = f_Z; }

			BiVector(float f_X, float f_Y, float f_Z, float f_W)
				{ m_X = f_X; m_Y = f_Y; m_Z = f_Z; }

			BiVector(float f_M)
				{ m_X = f_M; m_Y = f_M; m_Z = f_M; }

			void operator*=(const float &f)
				{
				m_X *= f;
				m_Y *= f;
				m_Z *= f;
				}

			BiVector operator*(const float &f)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X * f;
				f_Vector.m_X = m_Y * f;
				f_Vector.m_X = m_Z * f;
				return f_Vector;
				}

			void operator+=(const BiVector &v)
				{
				m_X += v.m_X;
				m_Y += v.m_Y;
				m_Z += v.m_Z;
				}

			BiVector operator+(const BiVector &v)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X + v.m_X;
				f_Vector.m_X = m_Y + v.m_Y;
				f_Vector.m_X = m_Z + v.m_Z;
				return f_Vector;
				}

			void operator-=(const BiVector &v)
				{
				m_X -= v.m_X;
				m_Y -= v.m_Y;
				m_Z -= v.m_Z;
				}

			BiVector operator-(const BiVector &v)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X - v.m_X;
				f_Vector.m_Y = m_Y - v.m_Y;
				f_Vector.m_Z = m_Z - v.m_Z;
				return f_Vector;
				}

			void cross(const BiVector &v1, const BiVector &v2)
				{
				m_X = v1.m_Y * v2.m_Z - v1.m_Z * v2.m_Y;
				m_Y = v1.m_Z * v2.m_X - v1.m_X * v2.m_Z;
				m_Z = v1.m_X * v2.m_Y - v1.m_Y * v2.m_X;
				}

			void acPushRandSphere(float f_Radius, float f_Seed)
				{
				f_Radius *= 1.5;

				for (int f_Cntr = 0; f_Cntr < 7; f_Cntr++)
					{
					BiRand f_BiRand(f_Seed);
					BiVector f_Vector((f_BiRand.acGet() - 0.5f) * f_Radius, (f_BiRand.acGet() - 0.5f) * f_Radius, (f_BiRand.acGet() - 0.5f) * f_Radius);
				
					m_X += f_Vector.m_X * f_Radius;
					m_Y += f_Vector.m_Y * f_Radius;
					m_Z += f_Vector.m_Z * f_Radius;
					}
				}

			void acRun_visualminer(int g_Verbose = false)
				{
				BiVector f_Result;
				Carriage f_Car;
				f_Car = Cube::agRun_visualminer(m_X, m_Y, m_Z);

				m_X = f_Car.m_X;
				m_Y = f_Car.m_Y;
				m_Z = f_Car.m_Z;
				}

			void acBoundaryRanging(void)
				{
				if((m_X < 1.0f) && (m_X > 0.0f))
					{
					while(m_X < 1.0f)
						{
						m_X += SCP_PREC_ONE;
						}
					}

				if((m_X > -1.0f) && (m_X < 0.0f))
					{
					while(m_X > -1.0f)
						{
						m_X -= SCP_PREC_ONE;
						}
					}

				if((m_Y < 1.0f) && (m_Y > 0.0f))
					{
					while(m_Y < 1.0f)
						{
						m_Y += SCP_PREC_ONE;
						}
					}

				if((m_Y > -1.0f) && (m_Y < 0.0f))
					{
					while(m_Y > -1.0f)
						{
						m_Y -= SCP_PREC_ONE;
						}
					}

				if((m_Z < 1.0f) && (m_Z > 0.0f))
					{
					while(m_Z < 1.0f)
						{
						m_Z += SCP_PREC_ONE;
						}
					}

				if((m_Z > -1.0f) && (m_Z < 0.0f))
					{
					while(m_Z > -1.0f)
						{
						m_Z -= SCP_PREC_ONE;
						}
					}

				while(m_X >= 10.0f)
					{
					m_X -= SCP_PREC_TEN;
					}

				while(m_X <= -10.0f)
					{
					m_X += SCP_PREC_TEN;
					}

				while(m_Y >= 10.0f)
					{
					m_Y -= SCP_PREC_TEN;
					}

				while(m_Y <= -10.0f)
					{
					m_Y += SCP_PREC_TEN;
					}

				while(m_Z >= 10.0f)
					{
					m_Z -= SCP_PREC_TEN;
					}

				while(m_Z <= -10.0f)
					{
					m_Z += SCP_PREC_TEN;
					}
				}

			void acLargeBoundaryRanging(void)
				{
				while(m_X >= SCP_PREC_UPP)
					{
					m_X -= SCP_PREC_LGE;
					}

				while(m_X <= (-1.0f * SCP_PREC_UPP))
					{
					m_X += SCP_PREC_LGE;
					}

				while(m_Y >= SCP_PREC_UPP)
					{
					m_Y -= SCP_PREC_LGE;
					}

				while(m_Y <= (-1.0f * SCP_PREC_UPP))
					{
					m_Y += SCP_PREC_LGE;
					}

				while(m_Z >= SCP_PREC_UPP)
					{
					m_Z -= SCP_PREC_LGE;
					}

				while(m_Z <= (-1.0f * SCP_PREC_UPP))
					{
					m_Z += SCP_PREC_LGE;
					}
				}

			void acResolve_precision(float f_Scale)
				{
				acBoundaryRanging();

				m_X *= f_Scale;
				m_Y *= f_Scale;
				m_Z *= f_Scale;
				}

			void acPrepare(void)
				{
				BiVector f_Result(m_Z * -1, m_Y, m_X);

				m_X = f_Result.m_X;
				m_Y = f_Result.m_Y;
				m_Z = f_Result.m_Z;
				}

			float acDot(void)
				{
				return(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
				}

			float acDot(BiVector f_Vec2)
				{
				return(m_X * f_Vec2.m_X + m_Y * f_Vec2.m_Y + m_Z * f_Vec2.m_Z);
				}

			float acLength(void)
				{
				float f_Length = (float)sqrt(acDot());

				return f_Length;
				}

			BiVector acCross(BiVector f_Up)
				{
				BiVector f_Result(0);

				f_Result.m_X = m_Y * f_Up.m_Z - m_Z * f_Up.m_Y;
				f_Result.m_Y = m_Z * f_Up.m_X - m_X * f_Up.m_Z;
				f_Result.m_Z = m_X * f_Up.m_Y - m_Y * f_Up.m_X;

				return f_Result;
				}

			void acNormalize(void)
				{
				float len = m_X * m_X + m_Y * m_Y + m_Z * m_Z;

				if(len > 0)
					{
					len = 1.0f / sqrtf(len);
					m_X *= len;
					m_Y *= len;
					m_Z *= len;
					}
				}

		public:
			float m_X;
			float m_Y;
			float m_Z;
		};

#endif

	class Index
		{
		public:
			Index()
				{
				m_FaceNormal = std::make_shared<BiVector>(0.0f);
				m_A = 0;
				m_B = 0;
				m_C = 0;
				}

			std::shared_ptr<BiVector> m_FaceNormal;

			int m_A;
			int m_B;
			int m_C;
		};

	class BiPlane : public ecom_base
		{
		public:
			BiPlane()
				{
				std::string f_ref_CurrentPath = g_ref_global_start + "BiPlane::BiPlane";

#if 0
				ag_StatusLive(f_ref_CurrentPath, "m_Dir");
#endif

				m_Dir = std::make_shared<BiVector>(0.0f);

				m_Dir->m_X = 0.0f;
				m_Dir->m_Y = 1.0f;
				m_Dir->m_Z = 0.0f;
				m_Dist = 0;

#ifndef OSI_MEM_APP
				ac_Push(m_Dist, f_ref_CurrentPath + g_ref_Div + "m_Dist");
#endif
				};

			~BiPlane() { m_Dir = nullptr; };

			std::shared_ptr<BiVector> m_Dir;
			float m_Dist;
		};

	class aabb
		{
		public:
			aabb();

			bool collide(const aabb& b) const;
			bool isin(std::shared_ptr<aabb> b);
			bool collide(std::shared_ptr<aabb> b);
			bool inside(std::shared_ptr<BiVector> p);

			aabb &operator += (const aabb &);
			aabb &operator += (const std::shared_ptr<BiVector> &p);

			void acAdd_vector(std::shared_ptr<BiVector> p);

			float width()  const { return _max->m_X - _min->m_X; }
			float height() const { return _max->m_Y - _min->m_Y; }
			float depth()  const { return _max->m_Z - _min->m_Z; }

			std::shared_ptr<BiVector> center();
			std::shared_ptr<BiVector> centered();
			float volume();
			void empty();

			std::shared_ptr<BiVector> _min;
			std::shared_ptr<BiVector> _max;
			std::shared_ptr<BiVector> _center;

#ifdef CUBE_AABB_USE_COLOR
			BiVector _color;
			void visualization();
#endif
		};

	class aap
		{
		public:
			char xyz;
			float p;

			aap(char, float);
			aap(const aabb&);
			bool inside(std::shared_ptr<BiVector> p1, std::shared_ptr<BiVector> p2, std::shared_ptr<BiVector> p3) const;
			bool inside(std::shared_ptr<BiVector> mid) const;
		};

#ifdef OSI_MEMORY_BICYCLE_REF
	class CubeBicycle : public ecom_base
		{
		public:
			CubeBicycle()
				{
				std::string f_ref_CurrentPath = "CubeBicycle::CubeBicycle";

				acClear();

				vec_Vertex.reserve(8);
				vec_Color.reserve(8);

#ifndef OSI_MEM_APP
				ac_Push(m_indexCount, f_ref_CurrentPath + g_ref_Div + "m_indexCount");
				ac_Push(m_Refresh, f_ref_CurrentPath + g_ref_Div + "m_Refresh");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&CubeBicycle::acClear);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acRefresh", (void(ecom_base::*)(void))&CubeBicycle::acRefresh);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "avGrow", (void(ecom_base::*)(void))&CubeBicycle::avGrow);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "avTranslate", (void(ecom_base::*)(void))&CubeBicycle::avTranslate);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "avPushBack", (void(ecom_base::*)(void))&CubeBicycle::avPushBack);
				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSerialise", (void(ecom_base::*)(void))&CubeBicycle::acSerialise);
#endif
				};

			//Add to Wallet Compressed Data Streams Evolution
			CubeBicycle(std::string f_Buffer, uint* f_Chk);

			void acClear(void)
				{
				vec_Vertex.clear();
				vec_Color.clear();

				m_indexCount = 0;
				m_Refresh = 0;
				}

			void acRefresh(void)
				{
				//do nothing
				}

			void avGrow(float f_Amount);
			void avTranslate(Cube::BiVector f_Vector);
			void avPushBack(int f_Step);
			void acSerialise(std::string* f_String);

			int m_Refresh;
			int m_indexCount;

			std::vector<std::shared_ptr<Cube::BiVector>> vec_Vertex;
			std::vector<std::shared_ptr<Cube::BiVector>> vec_Color;

#ifndef JNI
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
#else
			std::shared_ptr<aabb> m_aabb;

			GLuint mVertexPositionBuffer;
			GLuint mVertexColorBuffer;
			GLuint mVertexNormalBuffer;
			GLuint mIndexBuffer;
			GLuint mTexCoordBuffer;
#endif
		};
#else
	class CubeBicycle : public ecom_base_flap
		{
		public:
			CubeBicycle()
				{
				acClear();

				vec_Vertex.reserve(8);
				vec_Color.reserve(8);
				};

			CubeBicycle(std::string f_Buffer, uint* f_Chk);

			void acClear(void)
				{
				vec_Vertex.clear();
				vec_Color.clear();

				m_indexCount = 0;
				m_Refresh = 0;
				}

			void acRefresh(void)
				{
				//do nothing
				}

			void avGrow(float f_Amount);
			void avTranslate(Cube::BiVector f_Vector);
			void avPushBack(int f_Step);
			void acSerialise(std::string* f_String);

			int m_Refresh;
			int m_indexCount;

			std::vector<std::shared_ptr<Cube::BiVector>> vec_Vertex;
			std::vector<std::shared_ptr<Cube::BiVector>> vec_Color;

#ifndef JNI
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
#else
			std::shared_ptr<aabb> m_aabb;

			GLuint mVertexPositionBuffer;
			GLuint mVertexColorBuffer;
			GLuint mVertexNormalBuffer;
			GLuint mIndexBuffer;
			GLuint mTexCoordBuffer;
#endif
		};
#endif

	class CubeHESH : public ecom_base
		{
		public:
			CubeHESH()
				{
				std::string f_ref_CurrentPath = "CubeHESH::CubeHESH";

				acClear();

#ifndef OSI_MEM_APP
				ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
				ac_Push(m_RotateX, f_ref_CurrentPath + g_ref_Div + "m_RotateX");
				ac_Push(m_RotateY, f_ref_CurrentPath + g_ref_Div + "m_RotateY");
				ac_Push(m_RotateZ, f_ref_CurrentPath + g_ref_Div + "m_RotateZ");
				ac_Push(m_bckred, f_ref_CurrentPath + g_ref_Div + "m_RotateX");
				ac_Push(m_bckgreen, f_ref_CurrentPath + g_ref_Div + "m_RotateY");
				ac_Push(m_bckblue, f_ref_CurrentPath + g_ref_Div + "m_RotateZ");
				ac_Push(m_ValueBank, f_ref_CurrentPath + g_ref_Div + "m_ValueBank");
				ac_Push(m_ADMAX, f_ref_CurrentPath + g_ref_Div + "m_ADMAX");
				ac_Push(m_ADHIGH, f_ref_CurrentPath + g_ref_Div + "m_ADHIGH");
				ac_Push(m_ADLOW, f_ref_CurrentPath + g_ref_Div + "m_ADLOW");
				ac_Push(m_CountLM, f_ref_CurrentPath + g_ref_Div + "m_CountLM");
				ac_Push(m_adIndex, f_ref_CurrentPath + g_ref_Div + "m_adIndex");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_IsOK", (void(ecom_base::*)(void))&CubeHESH::ac_IsOK);
#endif
				}

			CubeHESH(int f_ADMAX, int f_ADHIGH, int f_ADLOW, int f_CountLM = -1)
				{
				std::string f_ref_CurrentPath = "CubeHESH::CubeHESH";

				acClear();

				m_ADMAX = f_ADMAX;
				m_ADHIGH = f_ADHIGH;
				m_ADLOW = f_ADLOW;

				m_CountLM = f_CountLM;

#ifndef OSI_MEM_APP
				ac_Push(m_ID, f_ref_CurrentPath + g_ref_Div + "m_ID");
				ac_Push(m_RotateX, f_ref_CurrentPath + g_ref_Div + "m_RotateX");
				ac_Push(m_RotateY, f_ref_CurrentPath + g_ref_Div + "m_RotateY");
				ac_Push(m_RotateZ, f_ref_CurrentPath + g_ref_Div + "m_RotateZ");
				ac_Push(m_bckred, f_ref_CurrentPath + g_ref_Div + "m_RotateX");
				ac_Push(m_bckgreen, f_ref_CurrentPath + g_ref_Div + "m_RotateY");
				ac_Push(m_bckblue, f_ref_CurrentPath + g_ref_Div + "m_RotateZ");
				ac_Push(m_ValueBank, f_ref_CurrentPath + g_ref_Div + "m_ValueBank");
				ac_Push(m_ADMAX, f_ref_CurrentPath + g_ref_Div + "m_ADMAX");
				ac_Push(m_ADHIGH, f_ref_CurrentPath + g_ref_Div + "m_ADHIGH");
				ac_Push(m_ADLOW, f_ref_CurrentPath + g_ref_Div + "m_ADLOW");
				ac_Push(m_CountLM, f_ref_CurrentPath + g_ref_Div + "m_CountLM");
				ac_Push(m_adIndex, f_ref_CurrentPath + g_ref_Div + "m_adIndex");

				make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_IsOK", (void(ecom_base::*)(void))&CubeHESH::ac_IsOK);
#endif
				}

			CubeHESH(std::string f_Buffer, uint* f_Chk);

			~CubeHESH()
				{
				acClear();
				}

			void acClear(void)
				{
				for(int f_XY = 0; f_XY < vec_Bicycle.size(); f_XY++)
					{
					vec_Bicycle[f_XY]->vec_Vertex.clear();
					vec_Bicycle[f_XY]->vec_Color.clear();
					}

				vec_Bicycle.clear();
				m_adIndex.clear();

				m_vec_Collision.clear();

				m_ADMAX = g_BicycleContainer[0]->m_ADMAX;
				m_ADHIGH = g_BicycleContainer[0]->m_ADHIGH;
				m_ADLOW = g_BicycleContainer[0]->m_ADLOW;

				m_CountLM = -5;
				}

			void ac_IsOK(void)
				{
				if(m_adIndex.size() != vec_Bicycle.size())
					{
					if(m_adIndex.size() < vec_Bicycle.size())
						{
						int f_sindex = m_adIndex.size();

						while(m_adIndex.size() < vec_Bicycle.size())
							{
							m_adIndex.push_back(f_sindex);

							f_sindex++;
							}
						}
					else
						{
						while(m_adIndex.size() > vec_Bicycle.size())
							{
							m_adIndex.pop_back();
							}
						}
					}

				for(int f_Jet = 0; f_Jet < vec_Bicycle.size(); f_Jet++)
					{
					std::shared_ptr<CubeBicycle> f_Bike = vec_Bicycle[f_Jet];

					bool f_GradePass = true;

					if(f_Bike->vec_Vertex.size() != 8)
						{
						f_GradePass = false;
						}

					if(f_Bike->vec_Color.size() != 8)
						{
						if(f_Bike->vec_Color.size() > 8)
							{
							while(f_Bike->vec_Color.size() > 8)
								{
								f_Bike->vec_Color.pop_back();
								}
							}
						else
							{
							if(f_Bike->vec_Color.size() >= 1)
								{
								while(f_Bike->vec_Color.size() < 8)
									{
									f_Bike->vec_Color.push_back(f_Bike->vec_Color[0]);
									}
								}
							else
								{
								f_GradePass = false;
								}
							}
						}

					if(f_GradePass == false)
						{
						int f_Index = vec_Bicycle.size() - 1;

						while(vec_Bicycle.size() > f_Jet)
							{
							vec_Bicycle[f_Index]->acClear();

							vec_Bicycle.pop_back();
							m_adIndex.pop_back();

							f_Index--;
							}
						}
					}
				}

			std::string acHashMap(std::string f_NameString, int f_ID)
				{
				std::shared_ptr<Cube::CubeHASH_originstring> f_MapHash = std::make_shared<Cube::CubeHASH_originstring>();

				f_MapHash->acClear();

				f_MapHash->acPushString(f_NameString);
				f_MapHash->acPushInt(f_ID);

				f_MapHash->acPushFloat(m_bckred);
				f_MapHash->acPushFloat(m_bckgreen);
				f_MapHash->acPushFloat(m_bckblue);
				f_MapHash->acPushFloat(m_ValueBank);
				f_MapHash->acPushInt(m_ADMAX);
				f_MapHash->acPushInt(m_ADHIGH);
				f_MapHash->acPushInt(m_ADLOW);
				f_MapHash->acPushInt(m_CountLM);

				for(int f_Jet = 0; f_Jet < vec_Bicycle.size(); f_Jet++)
					{
					std::shared_ptr<CubeBicycle> f_Bicycle = vec_Bicycle[f_Jet];

					for(int f_XY = 0; f_XY < f_Bicycle->vec_Vertex.size(); f_XY++)
						{
						std::shared_ptr<Cube::BiVector> f_Vertex = f_Bicycle->vec_Vertex[f_XY];

						f_MapHash->acPushFloat(f_Vertex->m_X);
						f_MapHash->acPushFloat(f_Vertex->m_Y);
						f_MapHash->acPushFloat(f_Vertex->m_Z);
						}

					for(int f_XY = 0; f_XY < f_Bicycle->vec_Color.size(); f_XY++)
						{
						std::shared_ptr<Cube::BiVector> f_Color = f_Bicycle->vec_Color[f_XY];

						f_MapHash->acPushFloat(f_Color->m_X);
						f_MapHash->acPushFloat(f_Color->m_Y);
						f_MapHash->acPushFloat(f_Color->m_Z);
						}
					}

				std::string f_InputResult = f_MapHash->acGetInput();

				g_hasha.init(); //reset hasher state
				g_hasha.process(f_InputResult.begin(), f_InputResult.end());
				g_hasha.finish();
				picosha2::get_hash_hex_string(g_hasha, f_MapHash->m_OutputHash);

				return f_MapHash->m_OutputHash;
				}

			void acSaveCloud(std::string f_Name, int f_ID);

			void acSerialise(std::string* f_String);

			int m_ID;
			unsigned long long m_Timestamp;

			float m_RotateX;
			float m_RotateY;
			float m_RotateZ;

			float m_bckred;
			float m_bckgreen;
			float m_bckblue;

			float m_ValueBank;

			int m_ADMAX;
			int m_ADHIGH;
			int m_ADLOW;

			int m_CountLM;

			std::vector<int> m_adIndex;
			std::vector<std::shared_ptr<CubeBicycle>> vec_Bicycle;
			std::vector<std::shared_ptr<CubeCollision>> m_vec_Collision;
			std::shared_ptr<Cube::CubeHASH_originstring> m_Hash;
		};

	  /////////////////////////
	 /// START Cubetronics ///
	/////////////////////////

	class float3 : public ecom_base
		{
		public:
			float3() { x = 0; y = 0; z = 0; r = 0; g = 0; b = 0; }
			float3(float f_V) { x = f_V; y = f_V; z = f_V; r = f_V; g = f_V; b = f_V; }
			float3(float f_X, float f_Y, float f_Z) { x = f_X; y = f_Y; z = f_Z; r = 0.0f; g = 0.0f; b = 0.0f; }
			float3(int f_Type)
				{
				x = random() - 0.5;
				y = random() - 0.5;
				z = random() - 0.5;
				r = random();
				g = random();
				b = random();
				}

			float3 operator=(const BiVector &v) const
				{
				return float3(v.m_X, v.m_Y, v.m_Z);
				}

			bool operator==(const float3 &v) const
				{
				if (x != v.x) return false;
				if (y != v.y) return false;
				if (z != v.z) return false;
				return true;
				}

			void acNormalize(void)
				{
				double len = x * x + y * y + z * z;
				if(len > 0.0)
					{
					len = 1.0 / sqrt(len);
					x *= len;
					y *= len;
					z *= len;
					}
				}

			float x, y, z;
			float r, g, b;
		};

	class float4 : public ecom_base
		{
		public:
			float4() { x = 0; y = 0; z = 0; w = 0; }
			float4(float f_V) { x = f_V; y = f_V; z = f_V; w = f_V; }
			float4(float f_X, float f_Y, float f_Z, float f_W) { x = f_X; y = f_Y; z = f_Z; w = f_W; }
			float4(float f_X, float3 f_Y) { x = f_X; y = f_Y.x; z = f_Y.y; w = f_Y.z; }

			float4 operator=(const BiVector &v) const
				{
				return float4(v.m_X, v.m_Y, v.m_Z, 1.0f);
				}

			float x, y, z, w;
		};

	class matrix : public ecom_base
		{
		public:
			union
				{
				float m[4][4];	//!< matrix elements
				float mf[16];	//!< matrix elements
				};

			matrix()
				{
				mf[0] = mf[5] = mf[10] = mf[15] = 1.0f;
				mf[1] = mf[2] = mf[3] =
				mf[4] = mf[6] = mf[7] =
				mf[8] = mf[9] = mf[11] =
				mf[12] = mf[13] = mf[14] = 0.0f;
				}

			float3 operator*(const float3 &v) const
				{
				return float3(
					v.x*mf[0] + v.y*mf[4] + v.z*mf[8] + /*v.w*/mf[12],
					v.x*mf[1] + v.y*mf[5] + v.z*mf[9] + /*v.w*/mf[13],
					v.x*mf[2] + v.y*mf[6] + v.z*mf[10] + /*v.w*/mf[14]/*,
					v.x*mf[3] + v.y*mf[7] + v.z*mf[11] + v.w*mf[15]*/
					);
				}

			float4 operator*(const float4 &v) const
				{
				return float4(
					v.x*mf[0] + v.y*mf[4] + v.z*mf[8] + v.w*mf[12],
					v.x*mf[1] + v.y*mf[5] + v.z*mf[9] + v.w*mf[13],
					v.x*mf[2] + v.y*mf[6] + v.z*mf[10] + v.w*mf[14],
					v.x*mf[3] + v.y*mf[7] + v.z*mf[11] + v.w*mf[15]
					);
				}

			void operator*=(const matrix &m1)
				{
				matrix m2;

				m2.mf[0] = mf[0] * m1.mf[0] + mf[1] * m1.mf[4] + mf[2] * m1.mf[8];// + mf[ 3]*m1.mf[12];
				m2.mf[1] = mf[0] * m1.mf[1] + mf[1] * m1.mf[5] + mf[2] * m1.mf[9];// + mf[ 3]*m1.mf[13];
				m2.mf[2] = mf[0] * m1.mf[2] + mf[1] * m1.mf[6] + mf[2] * m1.mf[10];// + mf[ 3]*m1.mf[14];
				m2.mf[3] = 0.0f;//mf[ 0]*m1.mf[3] + mf[ 1]*m1.mf[7] + mf[ 2]*m1.mf[11] + mf[ 3]*m1.mf[15];

				m2.mf[4] = mf[4] * m1.mf[0] + mf[5] * m1.mf[4] + mf[6] * m1.mf[8];// + mf[ 7]*m1.mf[12];
				m2.mf[5] = mf[4] * m1.mf[1] + mf[5] * m1.mf[5] + mf[6] * m1.mf[9];// + mf[ 7]*m1.mf[13];
				m2.mf[6] = mf[4] * m1.mf[2] + mf[5] * m1.mf[6] + mf[6] * m1.mf[10];// + mf[ 7]*m1.mf[14];
				m2.mf[7] = 0.0f;//mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[7] + mf[ 6]*m1.mf[11] + mf[ 7]*m1.mf[15];

				m2.mf[8] = mf[8] * m1.mf[0] + mf[9] * m1.mf[4] + mf[10] * m1.mf[8];// + mf[11]*m1.mf[12];
				m2.mf[9] = mf[8] * m1.mf[1] + mf[9] * m1.mf[5] + mf[10] * m1.mf[9];// + mf[11]*m1.mf[13];
				m2.mf[10] = mf[8] * m1.mf[2] + mf[9] * m1.mf[6] + mf[10] * m1.mf[10];// + mf[11]*m1.mf[14];
				m2.mf[11] = 0.0f;//mf[ 8]*m1.mf[3] + mf[ 9]*m1.mf[7] + mf[10]*m1.mf[11] + mf[11]*m1.mf[15];

				m2.mf[12] = mf[12] * m1.mf[0] + mf[13] * m1.mf[4] + mf[14] * m1.mf[8] + /*mf[15]*/m1.mf[12];
				m2.mf[13] = mf[12] * m1.mf[1] + mf[13] * m1.mf[5] + mf[14] * m1.mf[9] + /*mf[15]*/m1.mf[13];
				m2.mf[14] = mf[12] * m1.mf[2] + mf[13] * m1.mf[6] + mf[14] * m1.mf[10] + /*mf[15]*/m1.mf[14];
				m2.mf[15] = 1.0f;//mf[12]*m1.mf[3] + mf[13]*m1.mf[7] + mf[14]*m1.mf[11] + mf[15]*m1.mf[15];

				*this = m2;
				}


#ifndef JNI
			void operator=(const DirectX::XMMATRIX &m1)
				{
				matrix m2;

#ifdef ARM_ARCH
				m2.mf[0] = m1.r->n128_f32[0];
				m2.mf[1] = m1.r->n128_f32[1];
				m2.mf[2] = m1.r->n128_f32[2];
				m2.mf[3] = m1.r->n128_f32[3];

				m2.mf[4] = m1.r->n128_f32[4];
				m2.mf[5] = m1.r->n128_f32[5];
				m2.mf[6] = m1.r->n128_f32[6];
				m2.mf[7] = m1.r->n128_f32[7];

				m2.mf[8] = m1.r->n128_f32[8];
				m2.mf[9] = m1.r->n128_f32[9];
				m2.mf[10] = m1.r->n128_f32[10];
				m2.mf[11] = m1.r->n128_f32[11];

				m2.mf[12] = m1.r->n128_f32[12];
				m2.mf[13] = m1.r->n128_f32[13];
				m2.mf[14] = m1.r->n128_f32[14];
				m2.mf[15] = m1.r->n128_f32[15];
#else
				m2.mf[0] = m1.r->m128_f32[0];
				m2.mf[1] = m1.r->m128_f32[1];
				m2.mf[2] = m1.r->m128_f32[2];
				m2.mf[3] = m1.r->m128_f32[3];

				m2.mf[4] = m1.r->m128_f32[4];
				m2.mf[5] = m1.r->m128_f32[5];
				m2.mf[6] = m1.r->m128_f32[6];
				m2.mf[7] = m1.r->m128_f32[7];

				m2.mf[8] = m1.r->m128_f32[8];
				m2.mf[9] = m1.r->m128_f32[9];
				m2.mf[10] = m1.r->m128_f32[10];
				m2.mf[11] = m1.r->m128_f32[11];

				m2.mf[12] = m1.r->m128_f32[12];
				m2.mf[13] = m1.r->m128_f32[13];
				m2.mf[14] = m1.r->m128_f32[14];
				m2.mf[15] = m1.r->m128_f32[15];
#endif

				*this = m2;
				}
#endif
		};

	// Per-vertex data used as input to the vertex shader.
	typedef struct VertexShaderInput
		{
		float3 pos;
		float3 color;
		} VertexShaderInput;

	// Per-pixel color data passed through the pixel shader.
	typedef struct PixelShaderInput
		{
		float4 pos;
		float3 color;
		} PixelShaderInput;

	class CubeHeshExporter : public ecom_base
		{
		public:
			CubeHeshExporter() { acClear(); }
			~CubeHeshExporter() { acClear(); }

			void acClear(void)
				{
				m_vec_Result.clear();
				BiCount = 0;
				BiVectorCount = 0;
				};

			void acPrepare(void) { acClear(); }

			std::vector<PixelShaderInput> m_vec_Result;
			int BiCount;
			int BiVectorCount;
		};

	class BiMesh;
	class BiMeshData;

	class BiSphere : public ecom_base
		{
		public:
			BiSphere()
				{
				m_Pos.m_X = 0;
				m_Pos.m_Y = 0;
				m_Pos.m_Z = 0;
				m_Dist = 0.0f;
				m_Mesh = nullptr;
				}
			BiSphere(BiMesh* f_Mesh)
				{
				m_Mesh = f_Mesh;
				m_Pos.m_X = 0;
				m_Pos.m_Y = 0;
				m_Pos.m_Z = 0;
				m_Dist = 0.0f;
				m_Mesh = nullptr;
				}
			BiSphere(BiVector f_Pos, float f_Dist)
				{
				m_Pos = f_Pos;
				m_Dist = f_Dist;
				m_Mesh = nullptr;
				}
			~BiSphere() {};

			void acPushRadius(float f_Length);

#if 1
			bool RaySphereIntersect(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection);
#endif

			BiMesh* m_Mesh;
			BiVector m_Pos;
			float m_Dist;
		};

	class BiNote : public ecom_base
		{
		public:
			BiNote()
				{
				m_Note = 0;
				m_Velocity = 0.0f;
				m_Frequency = 0.0f;
				m_TimeStart = 0.0f;
				m_TimeEnd = 0.0f;
				}
			~BiNote()
				{
				m_Note = 0;
				m_Velocity = 0.0f;
				m_Frequency = 0.0f;
				m_TimeStart = 0.0f;
				m_TimeEnd = 0.0f;
				};

			int m_Note;
			float m_Velocity;
			float m_Frequency;

			float m_TimeStart;
			float m_TimeEnd;
		};

	class BiMidi : public ecom_base
		{
		public:
			BiMidi()
				{
				m_vec_NoteOn.clear();
				}
			BiMidi(BiMesh* f_Mesh)
				{
				m_vec_NoteOn.clear();
				}
			BiMidi(BiVector f_Pos, float f_Dist)
				{
				m_vec_NoteOn.clear();
				}
			~BiMidi() {};

			std::vector<BiNote*> m_vec_NoteOn;
		};

	class BiVolt : public ecom_base
		{
		public:
			BiVolt()
				{
				m_vec_Volt.clear();
				m_SourceType = 0;
				};
			~BiVolt()
				{
				m_vec_Volt.clear();
				m_SourceType = 0;
				};

			std::vector<double> m_vec_Volt;
			int m_SourceType;
		};
	
	class BiMesh : public ecom_base
		{
		public:
#if 1
			BiMesh() : m_Name("BiMesh")
#else
			BiMesh() : m_Hash(random()), m_Name("BiMesh")
#endif
				{
				m_OK = false;
				m_RotationZ = 0.0f;
				};

#if 1
			BiMesh(std::string f_Name) : m_Name(f_Name)
#else
			BiMesh(std::string f_Name) : m_Hash(random()), m_Name(f_Name)
#endif
				{
				m_OK = false;
				m_RotationZ = 0.0f;
				};

			~BiMesh()
				{
#if 0
				m_vertexShader.Reset();
				m_pixelShader.Reset();
				m_inputLayout.Reset();
				m_vertexBuffer.Reset();
				m_indexBuffer.Reset();
#endif

				m_vec_PathIN.clear();
				m_vec_PathOUT.clear();
				delete m_Sphere;
				}

			void acMark(int f_Type);

#if 0
			bool acInteract(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection);
#endif

			BiSphere* m_Sphere;

			std::vector<BiMesh*> m_vec_PathIN;
			std::vector<BiMesh*> m_vec_PathOUT;

			std::vector<BiMesh*> m_vec_Input;
			std::vector<BiMesh*> m_vec_Output;

			std::vector<BiMeshData*> m_vec_MeshData;

			int m_VertCount;
			int m_indexCount;

#if 0
			Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
			Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
			Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
#endif

			float m_Finger;

#if 0
			Hash m_Hash;
#endif

			int m_InteractionType;

			std::string m_Name;
			std::string m_Path;

			int m_Type;
			int m_Factory;

			float m_RotationZ;

			float m_X;
			float m_Y;
			float m_Z;

			bool m_OK;
		};

	class BiMeshContainer : public ecom_base
		{
		public:
			BiMeshContainer()
				{
				m_vec_AllMesh.clear();
				m_vec_LevelRack.clear();
				m_vec_Sphere.clear();
				m_Int = false;
				m_Action = nullptr;
				};

			~BiMeshContainer()
				{
				for(int f_Count = 0; f_Count < m_vec_AllMesh.size(); f_Count++)
					{
					delete m_vec_AllMesh[f_Count];
					}

				m_vec_AllMesh.clear();
				m_vec_LevelRack.clear();
				m_vec_Sphere.clear();
				m_Int = false;
				m_Action = nullptr;
				};

			void acClearInteractions(void);
			void acInteract(float f_MouseX, float f_MouseY);

			void acPushLevel(BiMesh* f_Mesh)
				{
				m_vec_AllMesh.push_back(f_Mesh);
				m_vec_Sphere.push_back(f_Mesh->m_Sphere);
				m_vec_LevelRack.push_back(f_Mesh);
				}

			void acPushCom(BiMesh* f_Mesh, int f_Level)
				{
				f_Mesh->m_vec_PathOUT.push_back(m_vec_LevelRack[f_Level]);
				m_vec_AllMesh.push_back(f_Mesh);
				m_vec_Sphere.push_back(f_Mesh->m_Sphere);
				m_vec_LevelRack[f_Level]->m_vec_PathIN.push_back(f_Mesh);
				}

			BiMesh* m_Action;
			bool m_Int;

			std::vector<BiMesh*> m_vec_AllMesh;
			std::vector<BiMesh*> m_vec_LevelRack;
			std::vector<BiSphere*> m_vec_Sphere;
		};

	class BiMeshCore : public ecom_base
		{
		public:
			BiMeshCore()
				{
				m_Type = 0;
				m_Factory = 0;
				m_Time = 0.0f;
				};

			BiMeshCore(int f_Type, int f_Factory)
				{
				m_Type = f_Type;
				m_Factory = f_Factory;
				m_Time = 0.0f;
				};

			~BiMeshCore()
				{
				m_Type = 0;
				m_Factory = 0;
				m_Time = 0.0f;
				};

			void acPrepare(float f_Time);

			void acProcess(float f_Time);

			int m_Type;
			int m_Factory;

			float m_Time;

			std::vector<double> m_Input;
			std::vector<double> m_Output;
			std::vector<BiVolt> m_VoltInput;
			std::vector<BiVolt> m_VoltOutput;
			std::vector<BiMidi> m_MidiInput;
			std::vector<BiMidi> m_MidiOutput;

			 ////////////////////
			// ESL with speed
		};

	class BiUV : public ecom_base
		{
		public:
			BiUV(float f_U, float f_V)
				{
				m_U = f_U;
				m_V = f_V;
				}; 
			
			BiUV()
				{
				m_U = 0.0f;
				m_V = 0.0f;
				};

			~BiUV()
				{
				m_U = 0.0f;
				m_V = 0.0f;
				};

			float m_U;
			float m_V;
		};

	class BiRGBA : public ecom_base
		{
		public:
			BiRGBA(float f_R, float f_G, float f_B, float f_A)
				{
				m_R = f_R;
				m_G = f_G;
				m_B = f_B;
				m_A = f_A;
				};

			BiRGBA()
				{
				m_R = 0.0f;
				m_G = 0.0f;
				m_B = 0.0f;
				m_A = 0.0f;
				};

			~BiRGBA()
				{
				m_R = 0.0f;
				m_G = 0.0f;
				m_B = 0.0f;
				m_A = 0.0f;
				};

			float m_R;
			float m_G;
			float m_B;
			float m_A;
		};

	class BiMeshData : public ecom_base
		{
		public:
			BiMeshData()
				{
				m_vec_Vertex.clear();
				m_vec_Color.clear();
				m_vec_Normal.clear();
				m_vec_UV.clear();
				m_vec_Index.clear();
				m_vec_FaceNorm.clear();
				m_VertNom = 0;
				m_FaceNom = 0;
				m_Status = 0;
				m_IndexNom = 0;
				}

			~BiMeshData()
				{
				m_vec_Vertex.clear();
				m_vec_Color.clear();
				m_vec_Normal.clear();
				m_vec_UV.clear();
				m_vec_Index.clear();
				m_vec_FaceNorm.clear();
				m_VertNom = 0;
				m_FaceNom = 0;
				m_Status = 0;
				m_IndexNom = 0;
				}

			int acAddVertex(BiVector f_Vertex)
				{
				m_vec_Vertex.push_back(f_Vertex);
				m_VertNom++;
				return m_VertNom - 1;
				}

			int acAddVertex(BiVector f_Vertex, BiVector f_Normal)
				{
				m_vec_Vertex.push_back(f_Vertex);
				m_vec_Normal.push_back(f_Normal);
				m_VertNom++;
				return m_VertNom - 1;
				}

			int acAddVertex(float f_X, float f_Y, float f_Z, float f_R, float f_G, float f_B, float f_A, BiVector f_Normal)
				{
#ifdef GENERIC_BUILD
				Generic::VertexPositionColor f_VC;
				f_VC.pos.x = f_X;
				f_VC.pos.y = f_Y;
				f_VC.pos.z = f_Z;
				f_VC.color.x = f_R;
				f_VC.color.y = f_G;
				f_VC.color.z = f_B;
				m_vec_VertexColor.push_back(f_VC);
				m_vec_Color.push_back(BiRGBA(f_R, f_G, f_B, f_A));
				m_vec_Vertex.push_back(BiVector(f_X, f_Y, f_Z));
				m_vec_Normal.push_back(f_Normal);
				m_VertNom++;
#endif

				return m_VertNom - 1;
				}

			void acAddColor(BiRGBA f_RGBA)
				{
				m_vec_Color.push_back(f_RGBA);
				}

			void acAddUV(BiUV f_UV)
				{
				m_vec_UV.push_back(f_UV);
				}

			void acAddNormal(BiVector f_Normal)
				{
				m_vec_Normal.push_back(f_Normal);
				}

			void acAddFace(int f_A, int f_B, int f_C)
				{
				m_vec_Index.push_back((unsigned short)f_A);
				m_vec_Index.push_back((unsigned short)f_B);
				m_vec_Index.push_back((unsigned short)f_C);
				m_FaceNom++;
				m_IndexNom += 3;
				}

			std::vector<BiVector> m_vec_Vertex;
#ifdef GENERIC_BUILD
			std::vector<Generic::VertexPositionColor> m_vec_VertexColor;
#endif
			std::vector<BiRGBA> m_vec_Color;
			std::vector<BiVector> m_vec_Normal;
			std::vector<BiUV> m_vec_UV;

			std::vector<unsigned short> m_vec_Index;
			std::vector<BiVector> m_vec_FaceNorm;

			int m_VertNom;
			int m_FaceNom;
			int m_IndexNom;
			int m_Status;
		};

	enum CUBE_BIT_TYPE
		{
		qbtyperandomfloat,
		qbtyperandomint,
		qbtypeprogressfloat,
		qbtypeprogressint,
		qbtypenull,
		qbtypeTotal
		};

	class cube_Bit : public ecom_base
		{
		public:
			cube_Bit()
				{
				acClear();
				}

			cube_Bit(int f_StartInt, int f_MinInt, int f_MaxInt, int f_Type, int f_Prog, int f_Depth)
				{
				acClear();

				m_TraceInt = f_StartInt;
				m_TraceIntMax = f_MaxInt;
				m_TraceIntMin = f_MinInt;
				m_Type = f_Type;
				m_TraceIntProg = f_Prog;
				m_Depth = f_Depth;
				}

			cube_Bit(float f_StartFloat, float f_MinFloat, float f_MaxFloat, int f_Type, float f_Prog, int f_Depth)
				{
				acClear();

				m_TraceFloat = f_StartFloat;
				m_TraceFloatMax = f_MaxFloat;
				m_TraceFloatMin = f_MinFloat;
				m_Type = f_Type;
				m_TraceFloatProg = f_Prog;
				m_Depth = f_Depth;
				}

			cube_Bit(float f_StartFloat, float f_MinFloat, float f_MaxFloat)
				{
				acClear();

				m_TraceFloat = f_StartFloat;
				m_TraceFloatMax = f_MaxFloat;
				m_TraceFloatMin = f_MinFloat;
				m_Type = qbtyperandomfloat;
				m_TraceFloatProg = 1.0;
				m_Depth = 0;
				}

			~cube_Bit()
				{
				acClear();
				}

			void acClear(void)
				{
				m_TraceInt = 0;
				m_TraceIntMax = CUBEBIT_DEFAULT_MAX_INT;
				m_TraceIntMin = CUBEBIT_DEFAULT_MIN_INT;
				m_TraceFloat = 0.0;
				m_TraceFloatMax = CUBEBIT_DEFAULT_MAX_FLOAT;
				m_TraceFloatMin = CUBEBIT_DEFAULT_MIN_FLOAT;
				m_Type = CUBEBIT_DEFAULT_TYPE;
				m_TraceIntProg = 0;
				m_TraceFloatProg = 0.0f;
				m_cubeBit = nullptr;
				m_Depth = 0;
				}

			void acRandomise(void)
				{
				switch (m_Type)
					{
					case qbtyperandomfloat:
						{
						m_TraceFloat = m_TraceFloatMin + ((((float)rand() / 32767) * m_TraceFloatMax) + m_TraceFloatMin);
						}break;

					case qbtyperandomint:
						{
						m_TraceInt = m_TraceIntMin + ((rand() % m_TraceIntMax) + m_TraceIntMin);
						}break;
					}
				}

			void acProg(void)
				{
				switch(m_Type)
					{
					case qbtyperandomfloat:
						{
						m_TraceFloat = m_TraceFloatMin + ((((float)rand() / 32767) * m_TraceFloatMax) + m_TraceFloatMin);
						}break;

					case qbtyperandomint:
						{
						m_TraceInt = m_TraceIntMin + ((rand() % m_TraceIntMax) + m_TraceIntMin);
						}break;

					case qbtypeprogressfloat:
						{
						m_TraceFloat = m_TraceFloatProg;

						if(m_TraceFloat > m_TraceFloatMax)
							{
							m_TraceIntProg *= -1;
							m_TraceFloat = m_TraceFloatMax;
							}

						if(m_TraceFloat < m_TraceFloatMin)
							{
							m_TraceIntProg *= -1;
							m_TraceFloat = m_TraceFloatMin;
							}
						}break;

					case qbtypeprogressint:
						{
						m_TraceInt = m_TraceIntProg;

						if(m_TraceInt > m_TraceIntMax)
							{
							m_TraceIntProg *= -1;
							m_TraceInt = m_TraceIntMax;
							}

						if(m_TraceInt < m_TraceIntMin)
							{
							m_TraceIntProg *= -1;
							m_TraceInt = m_TraceIntMin;
							}
						}break;
					}
				}

			int m_Type;
			int m_TraceInt;
			int m_TraceIntMax;
			int m_TraceIntMin;
			int m_TraceIntProg;
			float m_TraceFloat;
			float m_TraceFloatMax;
			float m_TraceFloatMin;
			float m_TraceFloatProg;
			cube_Bit* m_cubeBit;
			int m_Depth;
		};

	class cube_Bit_container : public ecom_base
		{
		public:
			cube_Bit_container()
				{
				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 0;
				m_ChangeCount = 0;
				m_RefreshCount = 15;
				}

			cube_Bit_container(int f_RefreshCount)
				{
				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 0;
				m_ChangeCount = 0;
				m_RefreshCount = f_RefreshCount;
				}

			~cube_Bit_container()
				{
				for(int count = 0; count < m_vec_cube_Bit.size(); count++)
					{
					delete m_vec_cube_Bit[count];
					}

				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 0;
				m_ChangeCount = 0;
				}

			void acRefresh()
				{
				m_CurrentTrace = 0;
				m_CurrentSheet++;
				m_ChangeCount = 0;

				if(m_CurrentSheet > m_RefreshCount)
					{
					acReset();
					}
				else
					{
					for(int f_Count = 0; f_Count < (rand() % 5); f_Count++)
						{
						acProg();
						}
					}
				}

			void acReset()
				{
				for(int count = 0; count < m_vec_cube_Bit.size(); count++)
					{
					delete m_vec_cube_Bit[count];
					}

				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 1;
				m_ChangeCount = 0;
				}

			void acRandomise()
				{
				for(int f_Count = 0; f_Count < m_vec_cube_Bit.size(); f_Count++)
					{
					m_vec_cube_Bit[f_Count]->acRandomise();
					}
				}

			void acProg()
				{
				for(int f_Count = 0; f_Count < m_vec_cube_Bit.size(); f_Count++)
					{
					m_vec_cube_Bit[f_Count]->acProg();
					}
				}
			
			std::vector<cube_Bit*> m_vec_cube_Bit;
			int m_CurrentTrace;
			int m_CurrentSheet;
			int m_ChangeCount;
			int m_RefreshCount;
		};

	extern float frac(float f_Float);
	extern float dot(float3 f_A, float3 f_B);
	extern PixelShaderInput visualminer(VertexShaderInput input);

	extern void agSet_offsetvec(float3 f_Vector);
	extern std::vector<std::shared_ptr<CubeHESH>> g_HESH;

	extern void ag_AttachCube(std::shared_ptr<Cube::CubeKEY> f_Target, std::shared_ptr<Cube::CubeKEY> f_Subject, float f_Margin);

	extern std::shared_ptr<Cube::CubeKEY> ChooseKEY(int f_Count = 1);
	
	extern matrix g_model;
	extern matrix g_view;
	extern matrix g_projection;

	extern float3 g_RandomSeed;
	extern float3 g_offsetVec;

	extern float g_Float;

	extern BiVector g_eye;
	extern BiVector g_at;

	extern std::shared_mutex g_Applog_Muti;
	extern std::shared_mutex g_Mysql_Muti;
	extern std::shared_mutex g_Socket_Muti;
	extern std::shared_mutex g_Count_Muti;
	extern std::shared_mutex g_Share_Muti;
	extern std::shared_mutex g_Other_Muti;

	extern std::shared_ptr<Cube::CubeHESH> g_TargetedHesh;
	extern std::vector<std::shared_ptr<Cube::CubeTransaction>> g_vec_Successfull_TX;
	extern std::shared_ptr<Cube::CubeHeshExporter> g_CubeHeshExport;
	extern std::shared_ptr<Cube::BiMeshContainer> g_MeshContainer;

	 //////////////////////////
	// Cube Global Function //
	class _Cag : public ecom_base
		{
		public:
			typedef base_type(ecom_base::* Cag_base)(void);
			typedef void(ecom_base::* Cag_slicer)(void);

#ifdef CUBE_EXTENDED_GET_TX //un-supported overload currently
			std::shared_ptr<Cube::CubeTransaction> ag_getTX(int f_ShareID, float f_CostCPS);
#endif

			std::shared_ptr<Cube::CubeTransaction> ag_getTX(int f_txid, int f_txoutid = -1);

			bool ag_VerifyTXIN(std::shared_ptr<CubeTXIN> f_txin, float f_amount);

			std::shared_ptr<Cube::CubeTransaction> ag_get_TXfromvout(std::string f_vout);

			void ag_Upload_Procedures(bool f_ResetProc = false);

			float ag_CalcOwnerGenesisTX(std::string f_Owner, int f_ShareID, std::shared_ptr<Cube::CubeTransaction> f_TX);

			bool ag_Verify_TX_ReHash_VerifySigniture(std::shared_ptr<Cube::CubeTransaction> f_TX);

			bool ag_Verify_PublicSigniture(std::string f_PubKey, std::string f_Hash, std::string f_Sign);

			float ag_OwnerBalance(std::string f_owner);

			void ag_UpdateOwnerBalance(std::string f_Owner, float f_Amount);

			std::shared_ptr<Cube::ShareContainerExt> ag_SelectPeerGraphExt(int f_JobID, int f_ServLay, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_MainMutex = false);

			bool ag_makeGenesisCoin(void);

			bool ag_addGenesisTracking(int f_gnid, int f_blocktype, int f_elementinc = 0);

			int ag_GenerateTransaction(std::string f_A, std::string f_B, float f_amt, std::shared_ptr<CubeTransaction> f_tx = nullptr);

			std::shared_ptr<Cube::CubeResults> ag_GatherTransactions(int f_JobID, int f_IDX);

			std::string ag_GatherAllReferences(int f_JobID, int f_IDX);

			std::string ag_cont_VerifySingleTransaction(std::shared_ptr<CubeTransaction> f_Transaction, bool f_initialVerified);

			std::string ag_cont_VerifyResult(std::shared_ptr<CubeTransaction> f_Transaction, bool f_initialVerified);
		};

	extern std::shared_ptr<_Cag> Cag;

};

#include "Code\Work\Contract.h"
#include "Code\Work\Schedular.h"
#include "Wallet\Wallet.h"

#endif