/*

Wallet.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

#include "pplawait.h"
#include "Wallet.h"
#include "Code\Hash\base58.h"

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

using namespace winrt;

namespace ecoin
{

std::shared_ptr<Wallet> g_Wallet;

bool g_WalletOpen = false;
int g_EmployeeID = -1;
double g_WALLETBANK;
double g_StoreWALLETBANK;
double g_EVALUE;
double g_ECOINPERSECOND;
int g_HESHSAVEID;
float g_TX = 0.0f;
float g_BossLVLMin = 0.0f;

bool g_Pressed = false;

Wallet::Wallet()
{
	std::string f_ref_CurrentPath = "Wallet::Wallet";

	m_Start = false;
	m_OK = false;

	m_Count = 0;
	m_CountYNG = true;
	m_HeshCount = 0;
	m_HeshRCount = 0;
	m_Repeat = false;
	m_ChangeIdx = 0;
	m_RefreshLVL = 31;
	m_RefreshCNT = 0;

	m_my_EGBP_pledge = 0.0f;
	m_my_ECN_pledge = 0.0f;
	m_my_Active_pledge = true;
	m_my_pledge_shareID = 0;
	m_pledge_Total = 0.0f;

	m_current_IDX = 0;

	m_vec_blockledger.clear();
	m_vec_difficulty.clear();
	m_vec_eslid.clear();
	m_vec_targetid.clear();
	m_vec_blockid.clear();
	m_vec_score.clear();
	m_vec_maxvote.clear();
	m_vec_eslcode.clear();
	m_vec_pledgetype.clear();
	m_vec_maxpledge.clear();
	m_vec_targetbreach.clear();
	m_vec_owner.clear();
	m_vec_scoremax.clear();
	m_vec_markmax.clear();
	m_vec_markmin.clear();
	m_vec_jobboardid.clear();
	m_vec_blocktype.clear();
	m_vec_bckred.clear();
	m_vec_bckgreen.clear();
	m_vec_bckblue.clear();
	m_vec_price.clear();

	//Globals Push
#ifndef OSI_MEM_APP
	ag_Push(g_KeepShare, f_ref_CurrentPath + g_ref_global_Div + "g_KeepShare");
	ag_Push(g_Found_Share, f_ref_CurrentPath + g_ref_global_Div + "g_Found_Share");
	ag_Push(g_Found_Block, f_ref_CurrentPath + g_ref_global_Div + "g_Found_Block");
	ag_Push(g_Found_Msg, f_ref_CurrentPath + g_ref_global_Div + "g_Found_Msg");
	ag_Push(g_CoolDown, f_ref_CurrentPath + g_ref_global_Div + "g_CoolDown");
	ag_Push(g_CoolBoost, f_ref_CurrentPath + g_ref_global_Div + "g_CoolBoost");
	ag_Push(g_PEERCNT, f_ref_CurrentPath + g_ref_global_Div + "g_PEERCNT");
	ag_Push(g_SHARECNT, f_ref_CurrentPath + g_ref_global_Div + "g_SHARECNT");
	ag_Push(g_GameOpen, f_ref_CurrentPath + g_ref_global_Div + "g_GameOpen");
	ag_Push(g_Editor_ON, f_ref_CurrentPath + g_ref_global_Div + "g_Editor_ON");
	ag_Push(g_CopyStackPageN, f_ref_CurrentPath + g_ref_global_Div + "g_CopyStackPageN");
	ag_Push(g_BoardPushHeightAdjust, f_ref_CurrentPath + g_ref_global_Div + "g_BoardPushHeightAdjust");
	ag_Push(g_ComPositionToPoint2fFactor, f_ref_CurrentPath + g_ref_global_Div + "g_ComPositionToPoint2fFactor");
	ag_Push(g_ComICOPositionToComPositionX, f_ref_CurrentPath + g_ref_global_Div + "g_ComICOPositionToComPositionX");
	ag_Push(g_ComICOPositionToComPositionY, f_ref_CurrentPath + g_ref_global_Div + "g_ComICOPositionToComPositionY");
	ag_Push(g_CarriageReturnX, f_ref_CurrentPath + g_ref_global_Div + "g_CarriageReturnX");
	ag_Push(g_TXD_Scan, f_ref_CurrentPath + g_ref_global_Div + "g_TXD_Scan");
	ag_Push(g_OCSCP_ThreadCount, f_ref_CurrentPath + g_ref_global_Div + "g_OCSCP_ThreadCount");
	ag_Push(g_ConnectedECD, f_ref_CurrentPath + g_ref_global_Div + "g_ConnectedECD");
	ag_Push(g_LowtonMark, f_ref_CurrentPath + g_ref_global_Div + "g_LowtonMark");
	ag_Push(g_OCSCP_LowtonMark, f_ref_CurrentPath + g_ref_global_Div + "g_OCSCP_LowtonMark");
	ag_Push(g_RenderHesh, f_ref_CurrentPath + g_ref_global_Div + "g_RenderHesh");
	ag_Push(g_LowtonOn, f_ref_CurrentPath + g_ref_global_Div + "g_LowtonOn");
	ag_Push(g_espo_ShareOffset, g_Found_Text + g_ref_global_Div + "g_espo_ShareOffset");
	ag_Push(g_espo_Peer, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Peer");
	ag_Push(g_espo_Score, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Score");
	ag_Push(g_espo_Amount, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Amount");
	ag_Push(g_espo_ECN_Amount, f_ref_CurrentPath + g_ref_global_Div + "g_espo_ECN_Amount");
	ag_Push(g_espo_Owner, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Owner");
	ag_Push(g_espo_Date, f_ref_CurrentPath + g_ref_global_Div + "g_espo_Date");
	ag_Push(g_CurrentComID, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentComID");
	ag_Push(g_CurrentSharePrice, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentSharePrice");
	ag_Push(g_CurrentShareID, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentShareID");
	ag_Push(g_Once, f_ref_CurrentPath + g_ref_global_Div + "g_Once");
	ag_Push(g_JobID, f_ref_CurrentPath + g_ref_global_Div + "g_JobID");
	ag_Push(g_ShareCount, f_ref_CurrentPath + g_ref_global_Div + "g_ShareCount");
	ag_Push(g_CurrentShareOffset, f_ref_CurrentPath + g_ref_global_Div + "g_CurrentShareOffset");
	ag_Push(g_PEER, f_ref_CurrentPath + g_ref_global_Div + "g_PEER");
	ag_Push(g_EventOffset, f_ref_CurrentPath + g_ref_global_Div + "g_EventOffset");
	ag_Push(g_GUItimer, f_ref_CurrentPath + g_ref_global_Div + "g_GUItimer");
	ag_Push(g_SaveComplete_ThreadCount, f_ref_CurrentPath + g_ref_global_Div + "g_SaveComplete_ThreadCount");
	ag_Push(g_Diviner_ThreadCount, f_ref_CurrentPath + g_ref_global_Div + "g_Diviner_ThreadCount");
	ag_Push(g_BoughtCom, f_ref_CurrentPath + g_ref_global_Div + "g_BoughtCom");
	ag_Push(g_MyOwnCom, f_ref_CurrentPath + g_ref_global_Div + "g_MyOwnCom");
	ag_Push(g_CountLM, f_ref_CurrentPath + g_ref_global_Div + "g_CountLM");
#endif

	 ////////////////////////////////////
	// Cube Global Function Container //
	ag_StatusLive(g_ref_global_start + g_ref_fun_Div, "Cag");
	Cag = std::make_shared_reflect<_Cag>();

#ifndef OSI_MEM_APP
	ac_Push(m_Bank_ecoin, f_ref_CurrentPath + g_ref_Div + "m_Bank_ecoin");
	ac_Push(m_Price, f_ref_CurrentPath + g_ref_Div + "m_Price");
	ac_Push(m_Unit, f_ref_CurrentPath + g_ref_Div + "m_Unit");
	ac_Push(m_TX, f_ref_CurrentPath + g_ref_Div + "m_TX");
	ac_Push(m_Circulationamt, f_ref_CurrentPath + g_ref_Div + "m_Circulationamt");
	ac_Push(m_Start, f_ref_CurrentPath + g_ref_Div + "m_Start");
	ac_Push(m_RefreshLVL, f_ref_CurrentPath + g_ref_Div + "m_RefreshLVL");
	ac_Push(m_Reward, f_ref_CurrentPath + g_ref_Div + "m_Reward");
	ac_Push(m_RewardID, f_ref_CurrentPath + g_ref_Div + "m_RewardID");
	ac_Push(m_my_EGBP_pledge, f_ref_CurrentPath + g_ref_Div + "m_my_EGBP_pledge");
	ac_Push(m_my_ECN_pledge, f_ref_CurrentPath + g_ref_Div + "m_my_ECN_pledge");
	ac_Push(m_my_Active_pledge, f_ref_CurrentPath + g_ref_Div + "m_my_Active_pledge");
	ac_Push(m_my_pledge_shareID, f_ref_CurrentPath + g_ref_Div + "m_my_pledge_shareID");
	ac_Push(m_pledge_Total, f_ref_CurrentPath + g_ref_Div + "m_pledge_Total");
	ac_Push(m_vec_blockledger, f_ref_CurrentPath + g_ref_Div + "m_vec_blockledger");
	ac_Push(m_vec_difficulty, f_ref_CurrentPath + g_ref_Div + "m_vec_difficulty");
	ac_Push(m_vec_eslid, f_ref_CurrentPath + g_ref_Div + "m_vec_eslid");
	ac_Push(m_vec_targetid, f_ref_CurrentPath + g_ref_Div + "m_vec_targetid");
	ac_Push(m_vec_blockid, f_ref_CurrentPath + g_ref_Div + "m_vec_blockid");
	ac_Push(m_vec_score, f_ref_CurrentPath + g_ref_Div + "m_vec_score");
	ac_Push(m_vec_maxvote, f_ref_CurrentPath + g_ref_Div + "m_vec_maxvote");
	ac_Push(m_vec_eslcode, f_ref_CurrentPath + g_ref_Div + "m_vec_eslcode");
	ac_Push(m_vec_pledgetype, f_ref_CurrentPath + g_ref_Div + "m_vec_pledgetype");
	ac_Push(m_vec_maxpledge, f_ref_CurrentPath + g_ref_Div + "m_vec_maxpledge");
	ac_Push(m_vec_startbreach, f_ref_CurrentPath + g_ref_Div + "m_vec_startbreach");
	ac_Push(m_vec_targetbreach, f_ref_CurrentPath + g_ref_Div + "m_vec_targetbreach");
	ac_Push(m_vec_owner, f_ref_CurrentPath + g_ref_Div + "m_vec_owner");
	ac_Push(m_vec_scoremax, f_ref_CurrentPath + g_ref_Div + "m_vec_scoremax");
	ac_Push(m_vec_markmax, f_ref_CurrentPath + g_ref_Div + "m_vec_markmax");
	ac_Push(m_vec_markmin, f_ref_CurrentPath + g_ref_Div + "m_vec_markmin");
	ac_Push(m_vec_jobboardid, f_ref_CurrentPath + g_ref_Div + "m_vec_jobboardid");
	ac_Push(m_vec_blocktype, f_ref_CurrentPath + g_ref_Div + "m_vec_blocktype");
	ac_Push(m_vec_bckred, f_ref_CurrentPath + g_ref_Div + "m_vec_bckred");
	ac_Push(m_vec_bckgreen, f_ref_CurrentPath + g_ref_Div + "m_vec_bckgreen");
	ac_Push(m_vec_bckblue, f_ref_CurrentPath + g_ref_Div + "m_vec_bckblue");
	ac_Push(m_vec_price, f_ref_CurrentPath + g_ref_Div + "m_vec_price");
	
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acExec_preference_PayBlock", (bool(ecom_base::*)(void))&Wallet::acExec_preference_PayBlock);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acExec_preference_PayShare_Package", (bool(ecom_base::*)(void))&Wallet::acExec_preference_PayShare_Package);
#endif

#if 0
	printf("   //////////////////////////////////\n");
	printf("  // - ecoin a digital currency - //\n");
	printf(" // WELCOME TO YOUR ECOIN WALLET //\n");
	printf("//////////////////////////////////\n");
#endif

	m_CTX = std::make_shared<ECCVerifyHandle>();
}

Wallet::~Wallet()
{
	m_vec_Key.clear();
}

bool Wallet::acGet_assetContractbyID(float f_CostAmt, int f_ComID)
{			//using comid only capability
	return acGet_assetContractbyID(-1, f_CostAmt, f_ComID);
}

float Wallet::acGet_RewardFactor(void)
{
	return (50.0f / m_Reward);
}

bool Wallet::acGet_assetContractbyID(int f_ShareID, float f_CostAmt, int f_ComID)
{
	if(f_ShareID <= 0)
		{
		return true;
		}

	if(f_ComID > 0)
		{
#if 0
		mutex_qcomdb.lock();
#endif

		char* modquery = ag_ClearChar(1000);
		::sprintf(modquery, "SELECT id, owner, cost FROM com WHERE id = %i", f_ComID);
		g_SafeL[2]->acSelectCommand(modquery, false, false);
		delete modquery;

		int f_ModLCount = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[2]->acEntry(0)[0].at(0) == '0')
			{
			f_ModLCount = 0;
			}
		else
			{
			f_ModLCount = g_Schedular[2]->acEntrySize();
			}

		//checks
		if(f_ModLCount > 0)
			{
			std::string f_Owner = g_Schedular[2]->acEntry(0)[1];
			float f_Cost = atof(g_Schedular[2]->acEntry(0)[2].c_str());

			//my component
			if(f_Owner.compare(GetAdr()) == 0)
				{
#if 0
				mutex_qcomdb.unlock();
#endif

				return true;
				}

			//unproper costing
			if(f_CostAmt <= 0.0f)
				{
				if(f_Cost > 0.0f)
					{
					f_CostAmt = f_Cost;
					}
				else
					{
#if 0
					mutex_qcomdb.unlock();
#endif

					return true;
					}
				}
#if 1 //default load free
			else
				{
#if 0
				mutex_qcomdb.unlock();
#endif

				return true;
				}
#endif
			}
		else
			{ //not exist
#if 0
			mutex_qcomdb.unlock();
#endif

			return false;
			}

#if 0
		mutex_qcomdb.unlock();
#endif
		}

	bool f_Locked = false;
	
	if(f_ShareID > 0)
		{
		g_Schedular[1]->m_MainMutex.lock();
		f_Locked = true;

		char* modquery = ag_ClearChar(1000);
		::sprintf(modquery, "SELECT id, owner, price FROM share WHERE id = %i", f_ShareID);
		g_SafeL[1]->acSelectCommand(modquery, false, false, true);
		delete modquery;

		int f_ModLCount = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[1]->acEntry(0)[0].at(0) == '0')
			{
			f_ModLCount = 0;
			}
		else
			{
			f_ModLCount = g_Schedular[1]->acEntrySize();
			}

		//checks
		if(f_ModLCount > 0)
			{
			std::string f_Owner = g_Schedular[1]->acEntry(0)[1];
			float f_Cost = atof(g_Schedular[1]->acEntry(0)[2].c_str());

			//my share
			if(f_Owner.compare(GetAdr()) == 0)
				{
				if(f_Locked == true)
					{
					g_Schedular[1]->m_MainMutex.unlock();
					}

				return true;
				}

			//unproper costing
			if(f_CostAmt <= 0.0f)
				{
				if(f_Cost > 0.0f)
					{
					f_CostAmt = f_Cost;
					}
				else
					{
					if(f_Locked == true)
						{
						g_Schedular[1]->m_MainMutex.unlock();
						}

					return true;
					}
				}
			else //default load free
				{
				if(f_Locked == true)
					{
					g_Schedular[1]->m_MainMutex.unlock();
					}

				return true;
				}
			}
		else
			{ //not exist
			if(f_Locked == true)
				{
				g_Schedular[1]->m_MainMutex.unlock();
				}

			return false;
			}
		}

	  //-Assume proper pricing and cost value above zero
	 //////////////
	// continue...
	char* modquery = ag_ClearChar(1000);
	::sprintf(modquery, "SELECT id, amtpay, paypubkey, payvsign, timet FROM modpay WHERE (payowner = '%s') AND ((shareid = %i) OR (comid = %i))", GetAdr().c_str(), f_ShareID, f_ComID);
	g_SafeL[1]->acSelectCommand(modquery, false, false, true);
	delete modquery;

	int f_ModLCount = 0;

	float f_PayMass = 0.0f;

	//ECN::Stat::: f_ModLCount
	if(g_Schedular[1]->acEntry(0)[0].at(0) == '0')
		{
		f_ModLCount = 0;
		}
	else
		{
		f_ModLCount = g_Schedular[1]->acEntrySize();
		}

	int f_time = 0;

	if(f_ModLCount == 1)
		{
		int f_ID = ::atoi(g_Schedular[1]->acEntry(0)[0].c_str());
		f_time = ::atoi(g_Schedular[1]->acEntry(0)[4].c_str());

		if(f_ID > 0)
			{
			float f_PaidAmt = atof(g_Schedular[1]->acEntry(0)[1].c_str());

			if(f_PaidAmt > 0.0f)
				{
				f_PayMass += f_PaidAmt;
				}
			}
		}

	bool h_OK = false;

	if(f_PayMass >= f_CostAmt)
		{
		std::string f_PubKey = g_Schedular[1]->acEntry(0)[2];

		std::string f_Signiture = g_Schedular[1]->acEntry(0)[3];

		std::string f_InputHash = "";

		//add extra data like status etc.
		f_InputHash += GetAdr();
		f_InputHash += f_PubKey;

		char* f_Char = ag_ClearChar(5);
		::sprintf(f_Char, "%i", 0);

		f_InputHash += f_Char;
		delete f_Char;

		f_Char = ag_ClearChar(16);
		::sprintf(f_Char, "%i", f_ShareID);
		std::string f_newassetContract = "BUYSHAREID#";
		f_newassetContract += f_Char;
		delete f_Char;

		f_InputHash += f_newassetContract;

		f_Char = ag_ClearChar(16);
		::sprintf(f_Char, "%i", -1);
		f_InputHash += f_Char;
		delete f_Char;
		f_InputHash += "eslcode";

		f_Char = ag_ClearChar(32);
		::sprintf(f_Char, "%i", f_ShareID);
		f_InputHash += f_Char;
		delete f_Char;

		f_Char = ag_ClearChar(16);
		::sprintf(f_Char, "%i", f_ComID);
		f_InputHash += f_Char;
		delete f_Char;

		float f_ProductPrice = f_CostAmt;

		f_Char = ag_ClearChar(32);
		::sprintf(f_Char, "%f", f_ProductPrice);
		f_InputHash += f_Char;
		delete f_Char;

		f_Char = ag_ClearChar(64);
		::sprintf(f_Char, "%i", f_time);
		f_InputHash += f_Char;
		delete f_Char;

		std::string f_Hash = "";

		g_hasha.init(); //reset hasher state
		g_hasha.process(f_InputHash.begin(), f_InputHash.end());
		g_hasha.finish();
		picosha2::get_hash_hex_string(g_hasha, f_Hash);

		h_OK = Cag->ag_Verify_PublicSigniture(f_PubKey, f_Hash, f_Signiture);

		if(h_OK == false)
			{
#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif //add debug message
			}
		else
			{
			if(f_Locked == true)
				{
				g_Schedular[1]->m_MainMutex.unlock();
				}

			return true;
			}
		}
	
	//-common flow also check ECN transactions
	char* txquery = ag_ClearChar(1000);
	::sprintf(txquery, "SELECT id, amt FROM transactions WHERE status != -5 AND confirmation = 6 AND shareid = %i AND owner = '%s'", f_ShareID, GetAdr().c_str());
	g_SafeL[1]->acSelectCommand(txquery, false, false, true);
	delete txquery;

	int f_TXLCount = 0;

	//ECN::Stat::: f_TXLCount
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_TXLCount = 0;
		}
	else
		{
		f_TXLCount = g_Schedular[0]->acEntrySize();
		}

	if(f_TXLCount > 0)
		{
		for(int f_Jet = 0; f_Jet < f_TXLCount; f_Jet++)
			{
			int f_ID = ::atoi(g_Schedular[0]->acEntry(f_Jet)[0].c_str());

			if(f_ID > 0)
				{
				float f_PaidAmt = atof(g_Schedular[0]->acEntry(f_Jet)[1].c_str());

				if(f_PaidAmt > 0.0f)
					{
					f_PayMass + -f_PaidAmt;

					if(f_PaidAmt >= f_CostAmt)
						{
						if(f_Locked == true)
							{
							g_Schedular[1]->m_MainMutex.unlock();
							}

						return true; //win conditions
						}
					}
				}
			}
		}

	if(f_Locked == true)
		{
		g_Schedular[1]->m_MainMutex.unlock();
		}
	
	return false;
}

float Wallet::acGet_assetContractbyID(int f_ShareID, int f_ComID)
{
	float f_CumulativeValue = 0.0f;

	bool f_Locked = false;

	char* modquery = ag_ClearChar(1000);
	::sprintf(modquery, "SELECT id, amtpay FROM modpay WHERE (payowner = '%s') AND ((shareid = %i) OR ((comid > 0) AND (comid = %i)))", GetAdr().c_str(), f_ShareID, f_ComID, f_ComID);
	g_SafeL[0]->acSelectCommand(modquery, false, false);
	delete modquery;

	int f_ModLCount = 0;
		
	//ECN::Stat::: f_ModLCount
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_ModLCount = 0;
		}
	else
		{
		f_ModLCount = g_Schedular[0]->acEntrySize();
		}

	//Already paid! return bill amount paid.
	if(f_ModLCount > 0)
		{
		for(int f_Jet = 0; f_Jet < f_ModLCount; f_Jet++)
			{
			int f_ID = ::atoi(g_Schedular[0]->acEntry(0)[0].c_str());

			if(f_ID > 0)
				{
				f_CumulativeValue += atof(g_Schedular[0]->acEntry(0)[1].c_str());
				}
			}
		}

	//\/ cont. No previous payments for this item FRESH Check 1. com exists 2. !my com else return -5.0f 3. return com cost
	if(f_ShareID <= 0)
		{
		char* modquery2 = ag_ClearChar(1000);
		::sprintf(modquery2, "SELECT id, owner FROM com WHERE id = %i", f_ComID);
		g_SafeL[2]->acSelectCommand(modquery2, false, false);
		delete modquery2;

		int f_ModLCount2 = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[2]->acEntry(0)[0].at(0) == '0')
			{
			f_ModLCount2 = 0;
			}
		else
			{
			f_ModLCount2 = g_Schedular[2]->acEntrySize();
			}

		if(f_ModLCount2 == 1) //com exists
			{
			int f_ID = ::atoi(g_Schedular[0]->acEntry(0)[0].c_str());

			if(f_ID > 0) //com id good
				{
				if(g_Schedular[0]->acEntry(0)[1].compare(GetAdr()) == 0)
					{
					return -5.0f;
					}
				else
					{
					return f_CumulativeValue;
					}
				}
			}
		else
			{
			//add debug message
			}
		}
	else
		{
		g_Schedular[1]->m_MainMutex.lock();
		f_Locked = true;

		char* modquery2 = ag_ClearChar(1000);
		::sprintf(modquery2, "SELECT id, owner FROM share WHERE id = %i", f_ShareID);
		g_SafeL[1]->acSelectCommand(modquery2, false, false, true);
		delete modquery2;

		int f_ModLCount2 = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[1]->acEntry(0)[0].at(0) == '0')
			{
			f_ModLCount2 = 0;
			}
		else
			{
			f_ModLCount2 = g_Schedular[1]->acEntrySize();
			}

		if(f_ModLCount2 > 1)
			{	//my component
			if(GetAdr().compare(g_Schedular[1]->acEntry(f_ModLCount2 - 1)[1]) == 0)
				{
				if(f_Locked == true)
					{
					g_Schedular[1]->m_MainMutex.unlock();
					}

				return -5.0f;
				}
			else
				{
				//-common flow also check ECN transactions
				char* txquery = ag_ClearChar(1000);
				::sprintf(txquery, "SELECT id, amt FROM transactions WHERE ((status != -5) AND (confirmation = 6) AND (shareid = %i) AND (owner = '%s'))", f_ShareID, GetAdr().c_str());
				g_SafeL[1]->acSelectCommand(txquery, false, false);
				delete txquery;

				int f_TXLCount = 0;

				//ECN::Stat::: f_TXLCount
				if(g_Schedular[1]->acEntry(0)[0].at(0) == '0')
					{
					f_TXLCount = 0;
					}
				else
					{
					f_TXLCount = g_Schedular[1]->acEntrySize();
					}

				if(f_TXLCount > 0)
					{
					for(int f_Jet = 0; f_Jet < f_TXLCount; f_Jet++)
						{
						int f_ID = ::atoi(g_Schedular[1]->acEntry(f_Jet)[0].c_str());

						if(f_ID > 0)
							{
							float f_PaidAmt = atof(g_Schedular[1]->acEntry(f_Jet)[1].c_str());

							if(f_PaidAmt > 0.0f)
								{
								f_CumulativeValue += f_PaidAmt;
								}
							}
						}
					}

				if(f_Locked == true)
					{
					g_Schedular[1]->m_MainMutex.unlock();
					}

				return f_CumulativeValue;
				}
			}
		}

	if(f_Locked == true)
		{
		g_Schedular[1]->m_MainMutex.unlock();
		}

	//\/ cont. Return -1.0f for com ! exist
	
	return -1.0f;
}

bool Wallet::acBuy_ShareComID(int f_ComID, float f_PayAmt, float f_CostAmt, int f_ShareID)
{
	std::string f_ref_CurrentPath = "Wallet::acBuy_ShareComID";

	if(g_WalletOpen == true)
		{
		double f_BalanceCPS = GetBalanceCPS(true, 0);

		float f_PaidAmt = acGet_assetContractbyID(f_ShareID, f_ComID);

		float f_BillAmt = f_CostAmt - f_PaidAmt;

		if(f_PaidAmt < f_CostAmt)
			{
			if(f_BillAmt > f_BalanceCPS)
				{
				return false;
				}
			}
		else if(f_BillAmt <= 0.0f)
			{
			return true;
			}

		if(m_Bank_ecoin_constant > 0.0f)
			{
			char* g_modpayvalue[11];
			char* g_modpayfield[11];

			for(int f_s = 0; f_s < 11; f_s++)
				{
				g_modpayvalue[f_s] = (char*)malloc(sizeof(char) * 512);
				g_modpayfield[f_s] = (char*)malloc(sizeof(char) * 512);
				}

			::sprintf(g_modpayfield[0], "payowner");
			::sprintf(g_modpayfield[1], "paypubkey");
			::sprintf(g_modpayfield[2], "payvsign");
			::sprintf(g_modpayfield[3], "status");
			::sprintf(g_modpayfield[4], "assetcontract");
			::sprintf(g_modpayfield[5], "qamid");
			::sprintf(g_modpayfield[6], "forkref");
			::sprintf(g_modpayfield[7], "shareid");
			::sprintf(g_modpayfield[8], "comid");
			::sprintf(g_modpayfield[9], "amtpay");
			::sprintf(g_modpayfield[10], "timet");

			std::string f_InputHash = "";

			//add extra data like status etc.
			f_InputHash += GetAdr();
			f_InputHash += m_vec_Key[0]->m_pubkey;
			char* f_Char = ag_ClearChar(5);
			::sprintf(f_Char, "%i", 0);
			f_InputHash += f_Char;
			delete f_Char;

			f_Char = ag_ClearChar(16);
			::sprintf(f_Char, "%i", f_ShareID);
			std::string f_newassetContract = "BUYSHAREID#";
			f_newassetContract += f_Char;
			delete f_Char;
			f_InputHash += f_newassetContract;

			f_Char = ag_ClearChar(16);
			::sprintf(f_Char, "%i", -1);
			f_InputHash += f_Char;
			delete f_Char;
			f_InputHash += "eslcode";

			f_Char = ag_ClearChar(32);
			::sprintf(f_Char, "%i", f_ShareID);
			f_InputHash += f_Char;
			delete f_Char;

			f_Char = ag_ClearChar(16);
			::sprintf(f_Char, "%i", f_ComID);
			f_InputHash += f_Char;
			delete f_Char;

			float f_ProductPrice = f_BillAmt;

			f_Char = ag_ClearChar(32);
			::sprintf(f_Char, "%f", f_ProductPrice);
			f_InputHash += f_Char;
			delete f_Char;

			time_t f_currentTime;
			time(&f_currentTime);

			f_Char = ag_ClearChar(64);
			::sprintf(f_Char, "%i", f_currentTime);
			f_InputHash += f_Char;
			delete f_Char;

			g_hasha.init(); //reset hasher state
			g_hasha.process(f_InputHash.begin(), f_InputHash.end());
			g_hasha.finish();

			std::string f_HashOutput = "";

			picosha2::get_hash_hex_string(g_hasha, f_HashOutput);

			unsigned char k[32];

			Cube::ag_hex2bin(k, f_HashOutput.c_str(), 64);

			uint256& f_256uint = reinterpret_cast<uint256&>(k);

			std::vector<unsigned char> f_sig;

			bool f_res = m_vec_Key[0]->Sign(f_256uint, f_sig);

			char f_k[142];

			Cube::ag_bin2hex((char*)f_k, f_sig, 71);

			std::string f_vsign = "";

			for(int j2o = 0; j2o < 142; j2o++)
				{
				f_vsign.push_back(f_k[j2o]);
				}

			::sprintf(g_modpayvalue[0], "%s", GetAdr().c_str());
			::sprintf(g_modpayvalue[1], "%s", m_vec_Key[0]->m_pubkey.c_str());
			::sprintf(g_modpayvalue[2], "%s", f_vsign.c_str());
			::sprintf(g_modpayvalue[3], "%i", 0);
			::sprintf(g_modpayvalue[4], "%s", f_newassetContract.c_str());
			::sprintf(g_modpayvalue[5], "%i", -1);
			::sprintf(g_modpayvalue[6], "%s", "eslcode");
			::sprintf(g_modpayvalue[7], "%i", f_ShareID);
			::sprintf(g_modpayvalue[8], "%i", f_ComID);
			::sprintf(g_modpayvalue[9], "%f", f_PayAmt);
			::sprintf(g_modpayvalue[10], "%i", f_currentTime);

			int f_SyncUniqueID = g_SafeL[0]->Insert("modpay", (const char **)g_modpayfield, (const char **)g_modpayvalue, 11, true, false);

			for(int f_s = 0; f_s < 11; f_s++)
				{
				free(g_modpayvalue[f_s]);
				free(g_modpayfield[f_s]);
				}

			acPay_preference(f_ComID, f_PayAmt, ecoin_Preferences::ecoin_Pref_ShareCom);

			  //////////////////////////////
			 // setBalance version 5.1.3 //
			//////////////////////////////

			return acSet_ConstantBalance(GetAdr(), (f_PayAmt * -1));
			}
		else
			{
			return false;
			}
		}

	return false;
}

int Wallet::acSet_ConstantBalance(std::string f_owner, float f_AmtDiff)
{
	char* f_balancequery = ag_ClearChar(256);
	::sprintf(f_balancequery, "SELECT id, amt FROM employee WHERE owner = '%s'", f_owner.c_str());
	g_SafeL[0]->acSelectCommand(f_balancequery, true, false);
	delete f_balancequery;

	int f_ownersCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_ownersCount = 0;
		}
	else
		{
		f_ownersCount = g_Schedular[0]->acEntrySize();
		}

	if(f_ownersCount == 1)
		{
		int f_ID = ::atoi(g_Schedular[0]->acEntry(0)[0].c_str());
		float f_amt = atof(g_Schedular[0]->acEntry(0)[1].c_str());

		if(f_amt + f_AmtDiff < 0.0f)
			{
			return 0;
			}
		else
			{
			f_amt += f_AmtDiff;
			}

		char* f_ownervalue[3];
		char* f_ownerfield[3];
		char* f_ownerwhere[3];

		f_ownervalue[0] = (char*)malloc(sizeof(char) * 1024);
		f_ownerfield[0] = (char*)malloc(sizeof(char) * 1024);
		f_ownerwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(f_ownerfield[0], "amt");
		::sprintf(f_ownervalue[0], "%f", f_amt);
		::sprintf(f_ownerwhere[0], "id = %i", f_ID);

		g_SafeL[0]->Update("employee", (const char**)f_ownerfield, (const char**)f_ownervalue, 1, f_ownerwhere[0], true, false);

		free(f_ownervalue[0]);
		free(f_ownerfield[0]);
		free(f_ownerwhere[0]);

		return 1;
		}
	else if(f_ownersCount == 0)
		{
		char* g_syncWalletvalue[5];
		char* g_syncWalletfield[5];

		for(int f_s = 0; f_s < 5; f_s++)
			{
			g_syncWalletvalue[f_s] = (char*)malloc(sizeof(char) * 256);
			g_syncWalletfield[f_s] = (char*)malloc(sizeof(char) * 256);
			}

		::sprintf(g_syncWalletfield[0], "owner");
		::sprintf(g_syncWalletfield[1], "amt");
		::sprintf(g_syncWalletfield[2], "bosslvlmin");
		::sprintf(g_syncWalletfield[3], "toke_version");
		::sprintf(g_syncWalletfield[4], "toke_currency");

		::sprintf(g_syncWalletvalue[0], "%s", f_owner.c_str());

		if(f_AmtDiff > 0.0f)
			{
			::sprintf(g_syncWalletvalue[1], "%f", f_AmtDiff);
			}
		else
			{
			::sprintf(g_syncWalletvalue[1], "%f", 0.0f);
			}

		::sprintf(g_syncWalletvalue[2], "%f", 0.0f);
		::sprintf(g_syncWalletvalue[3], "%i", 1);
		::sprintf(g_syncWalletvalue[4], "%s", "eGBP");

		int f_SyncUniqueID = g_SafeL[0]->Insert("employee", (const char **)g_syncWalletfield, (const char **)g_syncWalletvalue, 5, true, false);

		for(int f_s = 0; f_s < 5; f_s++)
			{
			free(g_syncWalletvalue[f_s]);
			free(g_syncWalletfield[f_s]);
			}

		if(f_AmtDiff >= 0.0f)
			{
			return 1;
			}
		else
			{
			return 0;
			}
		}

	return 0;
}

void Wallet::acPay_preference(int f_ShareID, float f_Amt, int f_TypeID)
{
	switch(f_TypeID)
		{
		case ecoin_Preferences::ecoin_Pref_TypeNameBlock: //fixme
			{
#if 0
			acExec_preference_PayBlock();
#endif
			}break;

		case ecoin_Preferences::ecoin_Pref_TimedPledge: //fixme
			{
			g_QcomManager->m_preference_ShareID = f_ShareID;
			g_QcomManager->m_preference_Amt = f_Amt;

			acExec_preference_PayBlock();
			}break;

		case ecoin_Preferences::ecoin_Pref_MaxPledge:
			{
			g_QcomManager->m_preference_ShareID = f_ShareID;
			g_QcomManager->m_preference_Amt = f_Amt;

			acExec_preference_PayBlock();
			}break;

		case ecoin_Preferences::ecoin_Pref_ShareCom:
			{
			g_QcomManager->m_preference_ShareID = f_ShareID;
			g_QcomManager->m_preference_Amt = f_Amt;

			acExec_preference_PayShare_Package();
			}break;
		}
}

void Wallet::acExec_preference_PayBlock(void)
{
	char* f_payquery = ag_ClearChar(2048);
	::sprintf(f_payquery, "UPDATE employee SET employee.amt = employee.amt + ((SELECT IFNULL(SUM(pledge), 0.0) / (SELECT IFNULL(SUM(pledge), 1.0) FROM reference WHERE blockid = %i) FROM reference WHERE reference.owner = employee.owner AND reference.blockid = %i) * (SELECT IFNULL(SUM(pledge), 0.0) FROM reference WHERE blockid = %i))", g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX], g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX], g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX]);
	g_SafeL[0]->UpdateQuery(f_payquery);
	delete f_payquery;
}

void Wallet::acExec_preference_PayShare_Package(void)
{
	int f_ShareID = g_QcomManager->m_preference_ShareID;
	float f_Amt = g_QcomManager->m_preference_Amt;

	if(f_ShareID > 0)
		{
		if((float)GetBalanceCPS(true, 0) - f_Amt < 0.0f)
			{
			char* f_payquery = ag_ClearChar(2048);

			::sprintf(f_payquery, "UPDATE employee SET employee.amt = employee.amt + ((SELECT IFNULL(SUM(pledge), 0.0) / (SELECT IFNULL(SUM(pledge), 1.0) FROM reference WHERE shareid = %i) FROM reference WHERE reference.owner = employee.owner AND reference.shareid = %i) * (SELECT IFNULL(SUM(pledge), 0.0) FROM reference WHERE shareid = %i))", f_ShareID, f_ShareID, f_ShareID);

			g_SafeL[0]->UpdateQuery(f_payquery);

		    delete f_payquery;

			SetBalanceCPS(f_Amt * -1.0f);

			g_PreComLock = true;
			}
		else
			{
#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif		//add debug message
			}
		}
	else
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}
}

void Wallet::Open(void)
{
	  /////////////////////////////////////
	 // Data Layer Field Initialisation //
	/////////////////////////////////////

	for(int f_Count = 0; f_Count < 60; f_Count++)
		{
		g_cubefield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_adifield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_blockfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_sharefield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_jobfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_jobvarfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_transfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_addrfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_eventfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_chancefield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_reffield[f_Count] = (char*)malloc(sizeof(char) * 1024);
		g_addrfield[f_Count] = (char*)malloc(sizeof(char) * 256);
		g_txinsyncfield[f_Count] = (char*)malloc(sizeof(char) * 256);
		g_txoutsyncfield[f_Count] = (char*)malloc(sizeof(char) * 256);
		g_syncfield[f_Count] = (char*)malloc(sizeof(char) * 256);
		}

	sprintf(g_chancefield[0], "chance");
	sprintf(g_chancefield[1], "srcshareid");
	sprintf(g_chancefield[2], "resshareid");
	sprintf(g_chancefield[3], "srcblockid");
	sprintf(g_chancefield[4], "resblockid");

	sprintf(g_reffield[0], "assetid");
	sprintf(g_reffield[1], "assetofficeid");
	sprintf(g_reffield[2], "username");
	sprintf(g_reffield[3], "hdid");
	sprintf(g_reffield[4], "level");
	sprintf(g_reffield[5], "access");
	sprintf(g_reffield[6], "shareid");
	sprintf(g_reffield[7], "status");
	sprintf(g_reffield[8], "jobid");
	sprintf(g_reffield[9], "blockid");
	sprintf(g_reffield[10], "comid");
	sprintf(g_reffield[11], "comment");
	sprintf(g_reffield[12], "score");
	sprintf(g_reffield[13], "category");
	sprintf(g_reffield[14], "owner");
	sprintf(g_reffield[15], "pledge");
	sprintf(g_reffield[16], "ecnpledge");

	sprintf(g_eventfield[0], "appid");
	sprintf(g_eventfield[1], "type");
	sprintf(g_eventfield[2], "shareid");
	sprintf(g_eventfield[3], "blockid");
	sprintf(g_eventfield[4], "score");
	sprintf(g_eventfield[5], "category");
	sprintf(g_eventfield[6], "owner");
	sprintf(g_eventfield[7], "pathowner");
	sprintf(g_eventfield[8], "reward");
	sprintf(g_eventfield[9], "pledge");
	sprintf(g_eventfield[10], "fee");

	for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
		{
		sprintf(g_cubefield[f_Int2 * 3], "vert%ix", f_Int2 + 1);
		sprintf(g_cubefield[(f_Int2 * 3) + 1], "vert%iy", f_Int2 + 1);
		sprintf(g_cubefield[(f_Int2 * 3) + 2], "vert%iz", f_Int2 + 1);
		}

	for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
		{
		sprintf(g_cubefield[(24 + (f_Int3 * 3))], "vert%ir", f_Int3 + 1);
		sprintf(g_cubefield[(24 + (f_Int3 * 3)) + 1], "vert%ig", f_Int3 + 1);
		sprintf(g_cubefield[(24 + (f_Int3 * 3)) + 2], "vert%ib", f_Int3 + 1);
		}

	sprintf(g_cubefield[48], "blockid");
	sprintf(g_cubefield[49], "shareid");
	sprintf(g_cubefield[50], "jobid");
	sprintf(g_cubefield[51], "eslid");
	sprintf(g_cubefield[52], "targetid");
	sprintf(g_cubefield[53], "eslcode");
	sprintf(g_cubefield[54], "difficulty");

	sprintf(g_adifield[0], "adindex");
	sprintf(g_adifield[1], "cubeindex");
	sprintf(g_adifield[2], "heshid");
	
	sprintf(g_blockfield[0], "mark");
	sprintf(g_blockfield[1], "assetid");
	sprintf(g_blockfield[2], "assetofficeid");
	sprintf(g_blockfield[3], "jobid");
	sprintf(g_blockfield[4], "eslid");
	sprintf(g_blockfield[5], "targetid");
	sprintf(g_blockfield[6], "shareid");
	sprintf(g_blockfield[7], "eslcode");
	sprintf(g_blockfield[8], "difficulty");
	sprintf(g_blockfield[9], "score");
	sprintf(g_blockfield[10], "maxvote");
	sprintf(g_blockfield[11], "blockledger");
	sprintf(g_blockfield[12], "owner");
	sprintf(g_blockfield[13], "shares");
	sprintf(g_blockfield[14], "bckred");
	sprintf(g_blockfield[15], "bckgreen");
	sprintf(g_blockfield[16], "bckblue");
	sprintf(g_blockfield[17], "reward");
	sprintf(g_blockfield[18], "pledge");
	sprintf(g_blockfield[19], "ecnpledge");
	sprintf(g_blockfield[20], "fee");
	sprintf(g_blockfield[21], "price");
	sprintf(g_blockfield[22], "blocktype");
	sprintf(g_blockfield[23], "breach");

	sprintf(g_sharefield[0], "mark");
	sprintf(g_sharefield[1], "markfloat");
	sprintf(g_sharefield[2], "assetid");
	sprintf(g_sharefield[3], "assetofficeid");
	sprintf(g_sharefield[4], "jobid");
	sprintf(g_sharefield[5], "jobboardid");
	sprintf(g_sharefield[6], "eslid");
	sprintf(g_sharefield[7], "targetid");
	sprintf(g_sharefield[8], "eslcode");
	sprintf(g_sharefield[9], "difficulty");
	sprintf(g_sharefield[10], "score");
	sprintf(g_sharefield[11], "maxvote");
	sprintf(g_sharefield[12], "shareledger");
	sprintf(g_sharefield[13], "jobledger");
	sprintf(g_sharefield[14], "owner");
	sprintf(g_sharefield[15], "bckred");
	sprintf(g_sharefield[16], "bckgreen");
	sprintf(g_sharefield[17], "bckblue");
	sprintf(g_sharefield[18], "comid");
	sprintf(g_sharefield[19], "reward");
	sprintf(g_sharefield[20], "pledge");
	sprintf(g_sharefield[21], "ecnpledge");
	sprintf(g_sharefield[22], "fee");
	sprintf(g_sharefield[23], "price");
	sprintf(g_sharefield[24], "blocktype");

	sprintf(g_jobfield[0], "assetofficeid");
	sprintf(g_jobfield[1], "targetid");
	sprintf(g_jobfield[2], "blockid");
	sprintf(g_jobfield[3], "blocktype");
	sprintf(g_jobfield[4], "eslcode");
	sprintf(g_jobfield[5], "pledgetype");
	sprintf(g_jobfield[6], "pledgemax");
	sprintf(g_jobfield[7], "targetbreach");
	sprintf(g_jobfield[8], "startbreach");
	sprintf(g_jobfield[9], "owner");
	sprintf(g_jobfield[10], "scoremax");
	sprintf(g_jobfield[11], "markmax");
	sprintf(g_jobfield[12], "markmin");
	sprintf(g_jobfield[13], "reward");
	sprintf(g_jobfield[14], "rewardid");

	sprintf(g_jobvarfield[0], "jobid");
	sprintf(g_jobvarfield[1], "name");
	sprintf(g_jobvarfield[2], "groupname");
	sprintf(g_jobvarfield[3], "value");

	sprintf(g_transfield[0], "assetid");
	sprintf(g_transfield[1], "assetofficeid");
	sprintf(g_transfield[2], "sender");
	sprintf(g_transfield[3], "recipient");
	sprintf(g_transfield[4], "jobid");
	sprintf(g_transfield[5], "confirmed");

	sprintf(g_addrfield[0], "assetid");
	sprintf(g_addrfield[1], "assetofficeid");
	sprintf(g_addrfield[2], "owner");
	sprintf(g_addrfield[3], "amt");

	sprintf(g_txinsyncfield[0], "transactionid");
	sprintf(g_txinsyncfield[1], "vout");
	sprintf(g_txinsyncfield[2], "pubkey");
	sprintf(g_txinsyncfield[3], "vsign");
	sprintf(g_txinsyncfield[4], "amt");
	sprintf(g_txinsyncfield[5], "gnshareid");

	sprintf(g_txoutsyncfield[0], "transactionid");
	sprintf(g_txoutsyncfield[1], "adrid");
	sprintf(g_txoutsyncfield[2], "owner");
	sprintf(g_txoutsyncfield[3], "txoutamt");
	sprintf(g_txoutsyncfield[4], "owneramt");
	sprintf(g_txoutsyncfield[5], "myelementcount");

	sprintf(g_syncfield[0], "status");
	sprintf(g_syncfield[1], "locktime");
	sprintf(g_syncfield[2], "confirmation");
	sprintf(g_syncfield[3], "hdid");
	sprintf(g_syncfield[4], "shareid");
	sprintf(g_syncfield[5], "gnshareid");
	sprintf(g_syncfield[6], "jobid");
	sprintf(g_syncfield[7], "rewardid");
	sprintf(g_syncfield[8], "blocktype");
	sprintf(g_syncfield[9], "hash");
	sprintf(g_syncfield[10], "hashnib");
	sprintf(g_syncfield[11], "amt");
	sprintf(g_syncfield[12], "fee");
	sprintf(g_syncfield[13], "reward");
	sprintf(g_syncfield[14], "owner");
	sprintf(g_syncfield[15], "blockid");
	sprintf(g_syncfield[16], "typed");

	g_Pressed = false;

	std::string f_ref_CurrentPath = g_ref_global_start + "Wallet::Open";

	g_CubeHeshExport = std::make_shared<Cube::CubeHeshExporter>();

	ag_StatusLive(f_ref_CurrentPath, "g_QcomManager", true);
	g_QcomManager = std::make_shared_reflect<QcomManager>();

	ag_StatusLive(f_ref_CurrentPath, "g_SafeL[0]", true);
	g_SafeL[0] = std::make_shared_reflect<icSafeL>(0);

	ag_StatusLive(f_ref_CurrentPath, "g_SafeL[1]", true);
	g_SafeL[1] = std::make_shared_reflect<icSafeL>(1);

	ag_StatusLive(f_ref_CurrentPath, "g_SafeL[2]", true);
	g_SafeL[2] = std::make_shared_reflect<icSafeL>(2);

	bool f_Int = true;

	if(g_Wallet->m_Start == true)
		{
		f_Int = g_SafeL[0]->Wallet_Connect();
		}

	g_ConnectedECD = f_Int;

#ifdef ECOIN_PROCEDURE_UPLOAD
#ifdef ECOIN_PROCEDURE_RESET
	ag_Upload_Procedures(true);
#else
	ag_Upload_Procedures();
#endif
#endif

	bool f_Sane = false;

	while(!f_Sane)
		{
		bool f_Un = ECC_Start();

		if(!f_Un)
			{
			if(ECC_InitSanityCheck() == true)
				{
				f_Sane = true;
				}
			else
				{
				ECC_Stop();
				}
			}
		else
			{
			ECC_Stop();
			}
		}

	//### QUANTUM PORTION ###//
#if 0
	Q.CoreAcquire();
#else
	Q.CoreAllocate();
#endif

	ag_PortShell_Initialisation();
	
	Qpo->Sound_Init();

	Q.InterfaceSounds();
}

std::string Wallet::Prepare(void)
{
	std::string f_Result;
	f_Result.clear();
	acBufwriteValueDouble(&f_Result, g_WALLETBANK);
	acBufwriteValueInteger(&f_Result, g_HESHSAVEID);
	acBufwriteValueInteger(&f_Result, 5000);
	acBufwriteValueInteger(&f_Result, m_ChangeIdx);
	acBufwriteValueInteger(&f_Result, m_vec_Key.size());

	for(int f_m = 0; f_m < m_vec_Key.size(); f_m++)
		{
		f_Result = f_Result + ag_Key_Serialize(m_vec_Key[f_m]);
		}

	m_Bank_ecoin = g_WALLETBANK;

	return f_Result;
}

std::string ag_Key_Serialize(std::shared_ptr<CKey> f_key)
{
	 //////////
	// Pass //
	std::string f_Result;
	f_Result.clear();

	char *lx2 = (char*)malloc(f_key->keydata.size() * 2 * sizeof(char));

	int i2;
	for (i2 = 0; i2 < f_key->keydata.size(); i2++)
		{
		::sprintf(lx2 + (i2 * 2) , "%02x", f_key->keydata[i2]);
		}

	std::string f_OutputKey2(lx2);
	std::string f_OutputKey2v3;

	f_OutputKey2v3.clear();
	for(int f_g = 0; f_g < 16; f_g++)
		{
		f_OutputKey2v3.push_back(f_OutputKey2[f_g]);
		}

	acBufwriteValueInteger(&f_Result, f_key->m_prefix);

	f_Result = f_Result + f_OutputKey2v3;
	f_Result = f_Result + "::::";

	std::string f_PUBKEY = f_key->m_pubkey;
	f_Result = f_Result + f_PUBKEY + "::::";

	std::string f_ADR = f_key->m_owner;
	f_Result = f_Result + f_ADR + "::::";

	return f_Result;
}

std::string Wallet::Prepare_Start(void)
{
	std::string f_Result;
	f_Result.clear();

	acBufwriteValueDouble(&f_Result, 0.0f);
	acBufwriteValueInteger(&f_Result, 0);
	acBufwriteValueInteger(&f_Result, 5000);
	acBufwriteValueInteger(&f_Result, 0);
	acBufwriteValueInteger(&f_Result, 5);

	std::shared_ptr<CKey> f_1key = ag_GenerateAddress(1);

	m_vec_Key.push_back(f_1key);

	std::string f_ResultKey = ag_Key_Serialize(f_1key);
	f_Result = f_Result + f_ResultKey;

	std::shared_ptr<CKey> f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	m_Bank_ecoin = 0.0f;
	m_Bank_ecoin_constant = 0.0f;
	m_Bank_Adr = f_1key->m_owner;

	return f_Result;
}

#ifdef ECOIN_WALLET_SAVE_ASYNC
std::future<void> Wallet::Update(void)
{
	if(g_WalletFile.IsAvailable() == true)
		{
		  //////////////
		 // Update
		//  Wallet
		std::string f_StringBuf = Prepare();

		::winrt::Windows::Storage::CachedFileManager::DeferUpdates(g_WalletFile);

		// write to file
		await winrt::Windows::Storage::FileIO::WriteTextAsync(g_WalletFile, StrUsingStr(f_StringBuf));

		// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
		// Completing updates may require Windows to ask for user input.
		::winrt::Windows::Storage::Provider::FileUpdateStatus status = co_await ::winrt::Windows::Storage::CachedFileManager::CompleteUpdatesAsync(g_WalletFile);

		if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::Complete)
			{
			m_OK = true;
			m_Repeat = false;
			g_WalletOpen = true;
			}
		else if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::CompleteAndRenamed)
			{
			m_OK = true;
			m_Repeat = false;
			g_WalletOpen = true;
			}
		else
			{
#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif //add debug message
			}
		}

	co_return;
}
#else
void Wallet::Update(void)
{
	winrt::Windows::Storage::StorageFolder f_LocalFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();

	winrt::hstring f_PathString = f_LocalFolder.Path();

	std::string f_ecoKeyStr = to_string(f_PathString) += std::string("\\KeyData.eco");

	FILE* f_WalletFile = fopen(f_ecoKeyStr.c_str(), "w");

	std::string f_StringBuf = Prepare();

	fprintf(f_WalletFile, "%s\n", f_StringBuf.c_str());

	fclose(f_WalletFile);
}
#endif

double Wallet::GetBalance(bool f_InDollars, int f_UI)
{
	if(m_RefreshLVL > 3)
		{
		m_Bank_ecoin = 0.0;

		for(int f_I = 0; f_I < m_vec_Key.size(); f_I++)
			{
			char* f_balquery = ag_ClearChar(256);
			::sprintf(f_balquery, "SELECT id, amt FROM address WHERE owner = '%s'", m_vec_Key[f_I]->m_owner.c_str());
			g_SafeL[f_UI]->acSelectCommand(f_balquery, true, false);
			delete f_balquery;

			int f_ADRCount = 0;
		
			if(g_Schedular[f_UI]->acEntry(0)[0].at(0) == '0')
				{
				f_ADRCount = 0;
				}
			else
				{
				f_ADRCount = g_Schedular[f_UI]->acEntrySize();
				}

			if(f_ADRCount == 1)
				{
				int f_IDAMT = ::atoi(g_Schedular[f_UI]->acEntry(0)[0].c_str());
				m_Bank_ecoin += atof(g_Schedular[f_UI]->acEntry(0)[1].c_str());
				}

#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif
			}

		m_RefreshLVL = 0;

		if(f_InDollars == true)
			{
			return m_Bank_ecoin * GetEValue(f_UI);
			}
		}
	else
		{
		m_RefreshCNT++;

		if(m_RefreshCNT > 4)
			{
			m_RefreshCNT = 0;
			m_RefreshLVL++;
			}
		}

	if(m_Bank_ecoin != 0.0f)
		{
		if(f_InDollars == true)
			{
			return m_Bank_ecoin * m_Price;
			}
		}
	else
		{
		return 0.0f;
		}

	return m_Bank_ecoin;
}

void Wallet::StartCPS(void)
{
	m_Bank_ecoin_constant = 0.0f;

	char* g_syncWalletvalue[5];
	char* g_syncWalletfield[5];

	for(int f_s = 0; f_s < 5; f_s++)
		{
		g_syncWalletvalue[f_s] = (char*)malloc(sizeof(char) * 256);
		g_syncWalletfield[f_s] = (char*)malloc(sizeof(char) * 256);
		}

	::sprintf(g_syncWalletfield[0], "owner");
	::sprintf(g_syncWalletfield[1], "amt");
	::sprintf(g_syncWalletfield[2], "bosslvlmin");
	::sprintf(g_syncWalletfield[3], "toke_version");
	::sprintf(g_syncWalletfield[4], "toke_currency");

	::sprintf(g_syncWalletvalue[0], "%s", GetAdr().c_str());
	::sprintf(g_syncWalletvalue[1], "%f", m_Bank_ecoin_constant);
	::sprintf(g_syncWalletvalue[2], "%f", g_BossLVLMin);
	::sprintf(g_syncWalletvalue[3], "%i", 1);
	::sprintf(g_syncWalletvalue[4], "%s", "eGBP");

	int f_SyncUniqueID = g_SafeL[0]->Wallet_Insert("employee", (const char **)g_syncWalletfield, (const char **)g_syncWalletvalue, 5, true, false);

	for(int f_s = 0; f_s < 5; f_s++)
		{
		free(g_syncWalletvalue[f_s]);
		free(g_syncWalletfield[f_s]);
		}

	g_EmployeeID = f_SyncUniqueID;
}

void Wallet::SetBalanceCPS(float f_FloatBalance)
{
	char* f_constantupvalue[1];
	char* f_constantupfield[1];
	char* f_constantupwhere[1];

	f_constantupvalue[0] = (char*)malloc(sizeof(char) * 1024);
	f_constantupfield[0] = (char*)malloc(sizeof(char) * 1024);
	f_constantupwhere[0] = (char*)malloc(sizeof(char) * 1024);

	::sprintf(f_constantupfield[0], "amt");
	::sprintf(f_constantupvalue[0], "%f", f_FloatBalance);
	::sprintf(f_constantupwhere[0], "owner = '%s'", GetAdr().c_str());

	g_SafeL[0]->Update("employee", (const char**)f_constantupfield, (const char**)f_constantupvalue, 1, f_constantupwhere[0], true, false);

	free(f_constantupvalue[0]);
	free(f_constantupfield[0]);
	free(f_constantupwhere[0]);
}

double Wallet::GetBalanceCPS(bool f_InDollars, int f_UI)
{
	m_Bank_ecoin_constant = 0.0f;

	int f_SearchOne = 1;

	for(int f_I = 0; f_I < f_SearchOne/*m_vec_Key.size()*/; f_I++)
		{
		char* f_balquery = ag_ClearChar(150);
		::sprintf(f_balquery, "SELECT id, amt FROM employee WHERE owner = '%s'", m_vec_Key[f_I]->m_owner.c_str());
		g_SafeL[f_UI]->acSelectCommand(f_balquery, true, false);
		delete f_balquery;

		int f_BalCount = 0;
		
		if(g_Schedular[f_UI]->acEntry(0)[0].at(0) == '0')
			{
			f_BalCount = 0;
			}
		else
			{
			f_BalCount = g_Schedular[f_UI]->acEntrySize();
			}

		if(f_BalCount == 1)
			{
			g_EmployeeID = ::atoi(g_Schedular[f_UI]->acEntry(0)[0].c_str());
			m_Bank_ecoin_constant += atof(g_Schedular[f_UI]->acEntry(0)[1].c_str());
			}
#ifdef ECOIN_DEBUG_BREAKS
		else
			{
			__debugbreak();
			}
#endif
		}

	return m_Bank_ecoin_constant;
}

double Wallet::GetEValue(int f_UI)
{
	char* f_coinquery = ag_ClearChar(256);
	::sprintf(f_coinquery, "SELECT id, price, tx, unit, visits FROM coin WHERE id = 1");
	g_SafeL[f_UI]->acSelectCommand(f_coinquery, true, false);
	delete f_coinquery;

	int f_CoinCount = 0;
		
	if(g_Schedular[f_UI]->acEntry(0)[0].at(0) == '0')
		{
		f_CoinCount = 0;
		}
	else
		{
		f_CoinCount = g_Schedular[f_UI]->acEntrySize();
		}

	if(f_CoinCount > 0)
		{
		int f_ID = ::atoi(g_Schedular[f_UI]->acEntry(0)[0].c_str());
		int f_Visits = ::atoi(g_Schedular[f_UI]->acEntry(0)[4].c_str());
		f_Visits++;

		g_EVALUE = atof(g_Schedular[f_UI]->acEntry(0)[1].c_str());
		m_Unit = atof(g_Schedular[f_UI]->acEntry(0)[3].c_str());
		m_TX = atof(g_Schedular[f_UI]->acEntry(0)[2].c_str());
		m_Price = g_EVALUE;

		char* f_visitupvalue[1];
		char* f_visitupfield[1];
		char* f_visitupwhere[1];

		f_visitupvalue[0] = ag_ClearChar(1024);
		f_visitupfield[0] = ag_ClearChar(1024);
		f_visitupwhere[0] = ag_ClearChar(1024);

		::sprintf(f_visitupfield[0], "visits");
		::sprintf(f_visitupvalue[0], "%i", f_Visits);
		::sprintf(f_visitupwhere[0], "id = %i", f_ID);

		g_SafeL[f_UI]->Update("coin", (const char **)f_visitupfield, (const char **)f_visitupvalue, 1, (const char*)f_visitupwhere[0], true, false);

		delete f_visitupvalue[0];
		delete f_visitupfield[0];
		delete f_visitupwhere[0];

		int f_CalcVisitsf = f_Visits % 75;

		if(f_CalcVisitsf == 75)
			{
			m_RefreshEValueLVL = 1;
			}
		else
			{
			m_RefreshEValueLVL = 0;
			}
		}
	else
		{
		m_RefreshEValueLVL = 1;
		}

	if(m_RefreshEValueLVL > 0)
		{
		char* f_circulationquery = ag_ClearChar(150);
		::sprintf(f_circulationquery, "SELECT COUNT(id) SUM(amt) FROM address WHERE amt > 0.0");
		g_SafeL[f_UI]->acSelectCommand_GlobalStorageWealth(f_circulationquery);
		delete f_circulationquery;

		int f_adrCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_adrCount = 0;
			}
		else
			{
			f_adrCount = g_Schedular[0]->acEntrySize();
			}

		int f_TotalEcoinAreas = 0;

		if(f_adrCount == 1)
			{
			f_TotalEcoinAreas = ::atoi(g_Schedular[f_UI]->acEntry(0)[0].c_str());

			m_Circulationamt = atof(g_Schedular[f_UI]->acEntry(0)[1].c_str());
			}
		else
			{
			m_Circulationamt = 0.0f;
			}

		if(m_Circulationamt == 0.0f)
			{
			m_Circulationamt = 50.0f;
			}

		char* f_coinquery2 = ag_ClearChar(150);
		::sprintf(f_coinquery2, "SELECT id, price, tx, unit FROM coin WHERE id = 1");
		g_SafeL[f_UI]->acSelectCommand(f_coinquery2, true, true);
		delete f_coinquery2;

		int f_eleCount = 0;
		
		if(g_Schedular[f_UI]->acEntry(0)[0].at(0) == '0')
			{
			f_eleCount = 0;
			}
		else
			{
			f_eleCount = g_Schedular[f_UI]->acEntrySize();
			}

		if(f_eleCount > 0)
			{
			int f_IDELEM = ::atoi(g_Schedular[f_UI]->acEntry(0)[0].c_str());
			g_EVALUE = atof(g_Schedular[f_UI]->acEntry(0)[1].c_str());
			m_Unit = atof(g_Schedular[f_UI]->acEntry(0)[3].c_str());
			m_TX = atof(g_Schedular[f_UI]->acEntry(0)[2].c_str());
			m_Price = g_EVALUE;

			if(g_TX < m_TX)
				{
				g_TX = m_TX;
				}
			}
		else		//insert coin record - first time
			{
			char* g_syncWalletvalue[5];
			char* g_syncWalletfield[5];

			for(int f_s = 0; f_s < 5; f_s++)
				{
				g_syncWalletvalue[f_s] = (char*)malloc(sizeof(char) * 256);
				g_syncWalletfield[f_s] = (char*)malloc(sizeof(char) * 256);
				}

			::sprintf(g_syncWalletfield[0], "assetofficeid");
			::sprintf(g_syncWalletfield[1], "price");
			::sprintf(g_syncWalletfield[2], "tx");
			::sprintf(g_syncWalletfield[3], "unit");
			::sprintf(g_syncWalletfield[4], "visits");

			::sprintf(g_syncWalletvalue[0], "%i", 3);
			::sprintf(g_syncWalletvalue[1], "%f", 1.0f);
			::sprintf(g_syncWalletvalue[2], "%f", 5.09f);
			::sprintf(g_syncWalletvalue[3], "%f", 5.09f);
			::sprintf(g_syncWalletvalue[4], "%i", 1);

			int f_SyncUniqueID = g_SafeL[f_UI]->Insert("coin", (const char **)g_syncWalletfield, (const char **)g_syncWalletvalue, 5, true, false);

			for(int f_s = 0; f_s < 5; f_s++)
				{
				free(g_syncWalletvalue[f_s]);
				free(g_syncWalletfield[f_s]);
				}

			g_EVALUE = 1.16f;
			m_Unit = 5.09f;
			m_TX = 5.09f;
			m_Price = g_EVALUE;
			}

#if 0
		  //////////////
		 //START COIN//
		//
		if(g_EVALUE <= 0.0f)
			{
			float f_StorageWealth = 50.0f;
			m_TX = 5.09;
			m_Price = (f_StorageWealth + m_TX) / f_Circulationamt;
			g_EVALUE = m_Price;
			}

		//Coin GunPrice Increase Range
		g_EVALUE = 15.0f / 500.0f;

		float f_Days_Active_Average = 120;
		float f_timeSpan = f_Days_Active_Average;

		//Calc TX over time within acceptable
		m_TX = m_Circulationamt / f_timeSpan;
		g_TX = m_TX;

		//When coin TX high ratio select tx.amt over datetime instead

		   ////////////////////
		  // Equation
		 // Storage Wealth
		// Value/Worth
		m_Price = (g_EVALUE * m_TX);
		g_EVALUE = m_Price;

		char* f_coinupvalue[3];
		char* f_coinupfield[3];
		char* f_coinupwhere[1];

		f_coinupvalue[0] = (char*)malloc(sizeof(char) * 1024);
		f_coinupfield[0] = (char*)malloc(sizeof(char) * 1024);
		f_coinupvalue[1] = (char*)malloc(sizeof(char) * 1024);
		f_coinupfield[1] = (char*)malloc(sizeof(char) * 1024);
		f_coinupvalue[2] = (char*)malloc(sizeof(char) * 1024);
		f_coinupfield[2] = (char*)malloc(sizeof(char) * 1024);
		f_coinupwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(f_coinupfield[0], "price");
		::sprintf(f_coinupfield[1], "tx");
		::sprintf(f_coinupfield[2], "unit");
		::sprintf(f_coinupvalue[0], "%f", m_Price);
		::sprintf(f_coinupvalue[1], "%f", m_TX);
		::sprintf(f_coinupvalue[2], "%f", m_Unit);
		::sprintf(f_coinupwhere[0], "assetofficeid = %i", 3);

		g_SafeL[f_UI]->Update("coin", (const char **)f_coinupfield, (const char **)f_coinupvalue, 3, f_coinupwhere[0], true, false);

		free(f_coinupvalue[0]);
		free(f_coinupfield[0]);
		free(f_coinupvalue[1]);
		free(f_coinupfield[1]);
		free(f_coinupvalue[2]);
		free(f_coinupfield[2]);
		free(f_coinupwhere[0]);
#endif
		}

	return m_Price;
}

std::shared_ptr<CKey> Wallet::GetNextChangeKey(void)
{
	std::shared_ptr<CKey> f_Key = m_vec_Key[1];

	int f_counter = m_ChangeIdx;

	m_ChangeIdx++;

	for(int f_helly = 1; f_helly < m_vec_Key.size(); f_helly++)
		{
		if(m_vec_Key[f_helly]->m_prefix == 2)
			{
			f_counter--;
			}

		if(f_counter < 0)
			{
			f_Key = m_vec_Key[f_helly];
			}
		}

	return f_Key;
}

bool Wallet::acFindChangeAdr(std::string f_Adr)
{
	for(int f_helly = 0; f_helly < m_vec_Key.size(); f_helly++)
		{
		if(m_vec_Key[f_helly]->m_prefix == 2)
			{
			if(m_vec_Key[f_helly]->m_owner.compare(f_Adr) == 0)
				{
				return true;
				}
			}
		}

	return false;
}

std::string Wallet::GetAdr(void)
{
	return m_vec_Key[0]->m_owner;
}

std::shared_ptr<CKey> ag_GenerateAddress(int f_Prefix)
{
	std::string f_ref_CurrentPath = "ag_GenerateAddress";

		///////////////
	   // Research
	  // Entropy
	 // Key
	// Privacy
	while(true)
		{
		std::string f_Address = "";

#ifdef ECOIN_REFLECTED_WALLET
		ag_StatusLive(f_ref_CurrentPath, "key");
		std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>(f_Prefix);
#else
		std::shared_ptr<CKey> key = std::make_shared<CKey>(f_Prefix);
#endif

		key->MakeNewKey(true);

		CPubKey pubkey = key->GetPubKey();
		bool f_keypass = key->VerifyPubKey(pubkey);

		std::vector<unsigned char, secure_allocator<unsigned char> > keydata;

		keydata.clear();

		for(int f_Jet = 0; f_Jet < 32; f_Jet++)
			{
			keydata.push_back(pubkey.vch[f_Jet]);
			}

		char *f_Char = new char[64];

		for(int i = 0; i < 32; i++)
			{
			::sprintf((char*)f_Char + (i * 2), "%02x", keydata[i]);
			}

		key->m_pubkey = f_Char;

		delete[] f_Char;

		uint256 hash;
		CHash256().Write(&keydata[0], 32).Finalize(hash.begin());

		uint160 hash4;
		CHash160().Write(hash.begin(), 32).Finalize(hash4.begin());

		std::vector<unsigned char> f_vec_UnsignedChar5;

		unsigned char *f_p5 = new unsigned char[20];

		Cube::ag_hex2bin(f_p5, hash4.GetHex().c_str(), hash4.GetHex().size());

		for(int f_lm5 = 0; f_lm5 < 20; f_lm5++)
			{
			f_vec_UnsignedChar5.push_back(f_p5[f_lm5]);
			}

		f_Address = ((std::string)EncodeBase58((const std::vector<unsigned char> &)f_vec_UnsignedChar5)).c_str();

		char* adrquery = ag_ClearChar(512);
		::sprintf(adrquery, "SELECT id FROM address WHERE owner = '%s'", f_Address.c_str());
		g_SafeL[0]->acWallet_SelectCommand(adrquery, false, false);
		delete adrquery;

		int f_AdrLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_AdrLCount = 0;
			}
		else
			{
			f_AdrLCount = g_Schedular[0]->acEntrySize();
			}

		// assume remote connection for windows
		if(f_AdrLCount == 0)
			{
			// GenerateAddress - f_Address
			char* g_addrvalue[4];
			char* fg_addrfield[4];

			g_addrvalue[0] = (char*)malloc(sizeof(char) * 256);
			g_addrvalue[1] = (char*)malloc(sizeof(char) * 256);
			g_addrvalue[2] = (char*)malloc(sizeof(char) * 256);
			g_addrvalue[3] = (char*)malloc(sizeof(char) * 256);

			fg_addrfield[0] = (char*)malloc(sizeof(char) * 256);
			fg_addrfield[1] = (char*)malloc(sizeof(char) * 256);
			fg_addrfield[2] = (char*)malloc(sizeof(char) * 256);
			fg_addrfield[3] = (char*)malloc(sizeof(char) * 256);

			::sprintf(g_addrvalue[0], "%i", 1);
			::sprintf(g_addrvalue[1], "%i", 3);
			::sprintf(g_addrvalue[2], "%s", f_Address.c_str());
			::sprintf(g_addrvalue[3], "%f", 0.0f);

			::sprintf(fg_addrfield[0], "assetid");
			::sprintf(fg_addrfield[1], "assetofficeid");
			::sprintf(fg_addrfield[2], "owner");
			::sprintf(fg_addrfield[3], "amt");

			int f_AddressUniqueID = g_SafeL[0]->Wallet_Insert("address", (const char **)fg_addrfield, (const char **)g_addrvalue, 4, false, false);

			free(g_addrvalue[0]);
			free(g_addrvalue[1]);
			free(g_addrvalue[2]);
			free(g_addrvalue[3]);

			free(fg_addrfield[0]);
			free(fg_addrfield[1]);
			free(fg_addrfield[2]);
			free(fg_addrfield[3]);

			// Unique Payment Address Found Addresses - f_AddressUniqueID
			key->m_owner = f_Address;

			return key;
			}
		}
}

std::shared_ptr<CKey> ag_GenerateAddress(int f_Prefix, bool f_Inside)
{
	std::string f_ref_CurrentPath = "ag_GenerateAddress";

		///////////////
	   // Research
	  // Entropy
	 // Key
	// Privacy
	while(true)
		{
		std::string f_Address = "";

#ifdef ECOIN_REFLECTED_WALLET
		ag_StatusLive(f_ref_CurrentPath, "key");
		std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>(f_Prefix);
#else
		std::shared_ptr<CKey> key = std::make_shared<CKey>(f_Prefix);
#endif

		key->MakeNewKey(true);

		CPubKey pubkey = key->GetPubKey();
		bool f_keypass = key->VerifyPubKey(pubkey);

		std::vector<unsigned char, secure_allocator<unsigned char> > keydata;

		keydata.clear();

		for(int f_Jet = 0; f_Jet < 32; f_Jet++)
			{
			keydata.push_back(pubkey.vch[f_Jet]);
			}

		char *f_Char = new char[64];
		 
		int i;
		for(i = 0; i < 32; i++)
			{
			::sprintf((char*)f_Char + (i * 2), "%02x", keydata[i]);
			}

		key->m_pubkey = f_Char;

		delete[] f_Char;

		uint256 hash;
		CHash256().Write(&keydata[0], 32).Finalize(hash.begin());

		uint160 hash4;
		CHash160().Write(hash.begin(), 32).Finalize(hash4.begin());

		std::vector<unsigned char> f_vec_UnsignedChar5;

		unsigned char *f_p5 = new unsigned char[20];

		Cube::ag_hex2bin(f_p5, hash4.GetHex().c_str(), hash4.GetHex().size());

		for(int f_lm5 = 0; f_lm5 < 20; f_lm5++)
			{
			f_vec_UnsignedChar5.push_back(f_p5[f_lm5]);
			}

		f_Address = ((std::string)EncodeBase58((const std::vector<unsigned char> &)f_vec_UnsignedChar5)).c_str();

		char* adrquery = ag_ClearChar(1000);
		::sprintf(adrquery, "SELECT id FROM address WHERE owner = '%s'", f_Address.c_str());
		g_SafeL[0]->acSelectCommand(adrquery, false, false);
		delete adrquery;

		int f_AdrLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_AdrLCount = 0;
			}
		else
			{
			f_AdrLCount = g_Schedular[0]->acEntrySize();
			}

		printf("ECN::Stat::: f_AdrLCount %i\n", f_AdrLCount);

		// assume remote connection for windows
		if(f_AdrLCount == 0)
			{
			// GenerateAddress - f_Address);
			char* g_addrvalue[4];
			char* fg_addrfield[4];

			g_addrvalue[0] = (char*)malloc(sizeof(char) * 256);
			g_addrvalue[1] = (char*)malloc(sizeof(char) * 256);
			g_addrvalue[2] = (char*)malloc(sizeof(char) * 256);
			g_addrvalue[3] = (char*)malloc(sizeof(char) * 256);

			fg_addrfield[0] = (char*)malloc(sizeof(char) * 256);
			fg_addrfield[1] = (char*)malloc(sizeof(char) * 256);
			fg_addrfield[2] = (char*)malloc(sizeof(char) * 256);
			fg_addrfield[3] = (char*)malloc(sizeof(char) * 256);

			::sprintf(g_addrvalue[0], "%i", 1);
			::sprintf(g_addrvalue[1], "%i", 3);
			::sprintf(g_addrvalue[2], "%s", f_Address.c_str());
			::sprintf(g_addrvalue[3], "%f", 0.0f);

			::sprintf(fg_addrfield[0], "assetid");
			::sprintf(fg_addrfield[1], "assetofficeid");
			::sprintf(fg_addrfield[2], "owner");
			::sprintf(fg_addrfield[3], "amt");

			int f_AddressUniqueID = g_SafeL[0]->Insert("address", (const char **)fg_addrfield, (const char **)g_addrvalue, 4, false, false);

			free(g_addrvalue[0]);
			free(g_addrvalue[1]);
			free(g_addrvalue[2]);
			free(g_addrvalue[3]);

			free(fg_addrfield[0]);
			free(fg_addrfield[1]);
			free(fg_addrfield[2]);
			free(fg_addrfield[3]);

			// Unique Payment Address Found Addresses - f_AddressUniqueID
			key->m_owner = f_Address;

			return key;
			}
		}
}

void Wallet::acPullHash(int f_NibCount)
{
	if(f_NibCount >= ECOIN_TX_BLOCK_NIB_COUNT) // Win conditions nibs complete
		{
		ag_Freshanon<int>(m_vec_jobid, m_current_IDX, g_JobID);

		char* txnibquery = ag_ClearChar(1000);
		::sprintf(txnibquery, "SELECT IFNULL(MAX(id), 0), jobledger FROM share WHERE ((jobid = %i) AND (jobledger != 'G'))", m_vec_jobid[m_current_IDX]);
		g_SafeL[0]->acSelectCommand(txnibquery, 2, false);
		delete txnibquery;

		int f_TxNibLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_TxNibLCount = 0;
			}
		else
			{
			f_TxNibLCount = g_Schedular[0]->acEntrySize();
			}

		if(f_TxNibLCount == 1)
			{
			ag_FreshOn<std::string>(m_vec_blockledger, m_current_IDX, g_Schedular[0]->acEntry(0)[1]);
			}
		}
}

void Wallet::acTestForBlock(int f_BlockType, std::shared_ptr<Cube::CubeResults> f_Results, bool f_SureBlock)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPageDX::acTestForBlock";

	switch(f_BlockType)
		{					  // also called default block inputadd
		case ecoin_BlockType::ecoin_Block_Target_TypeName: //complete
			{
			if(f_SureBlock == true)
				{
				acPullHash(f_Results->m_HashNibCount);

#if 0			// Score based rewards keep on
				if(ecoin_Reward_WinnerAll)
					{
					char* f_BlockQuery = ag_ClearChar(255);
					::sprintf(f_BlockQuery, "UPDATE address SET address.amt = address.amt + %f WHERE owner = '%s'", m_Reward, GetAdr().c_str());
					g_SafeL[0]->UpdateQuery(f_BlockQuery);
					delete f_BlockQuery;
					}
#endif

				acSave_currentBlock(f_Results);

				ag_StatusLive(f_ref_CurrentPath, "f_BlockAck");
				std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_BLOCK), g_ShareID, g_PEERCNT);

				f_Ack->m_ECN = 50.0f;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = GetAdr();
				f_Ack->m_BlockID = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];
				g_Ackent.push_back(f_Ack);

				g_PEERCNT = 0;
				g_SHARECNT = 0;

				// Democratic or score based rewards keep on make one genesis coin for block founder
#if 1
				Cag->ag_makeGenesisCoin();
#endif
				}
			}break;

		case ecoin_BlockType::ecoin_Block_Target_TimedType: //complete
			{
			if(g_Wallet->m_vec_score[m_current_IDX] >= m_vec_maxvote[m_current_IDX])
				{
				acPullHash(f_Results->m_HashNibCount);

				acSave_currentBlock(f_Results);

				ag_StatusLive(f_ref_CurrentPath, "f_BlockAck");
				std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_BLOCK), g_ShareID, g_PEERCNT);

				f_Ack->m_ECN = 50.0f;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = GetAdr();
				f_Ack->m_BlockID = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];
				g_Ackent.push_back(f_Ack);

				g_PEERCNT = 0;
				g_SHARECNT = 0;

				Cag->ag_makeGenesisCoin();
				}
			}break;

		case ecoin_BlockType::ecoin_Block_Target_SCP: //complete
			{
			if(f_SureBlock == true)
				{
				acPullHash(f_Results->m_HashNibCount);

				acSave_currentBlock(f_Results);

				ag_StatusLive(f_ref_CurrentPath, "f_BlockAck");
				std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_BLOCK), g_ShareID, g_PEERCNT);

				f_Ack->m_ECN = 50.0f;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = GetAdr();
				f_Ack->m_BlockID = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];
				g_Ackent.push_back(f_Ack);

				g_PEERCNT = 0;
				g_SHARECNT = 0;

				Cag->ag_makeGenesisCoin();
				}
			}break;
			
		case ecoin_BlockType::ecoin_Block_TimedPledge: //complete
			{
			if(g_Wallet->m_vec_score[m_current_IDX] >= m_vec_maxvote[m_current_IDX])
				{
				acPullHash(f_Results->m_HashNibCount);

				acSave_currentBlock(f_Results);

				ag_StatusLive(f_ref_CurrentPath, "f_BlockAck");
				std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_BLOCK), g_ShareID, g_PEERCNT);

				f_Ack->m_ECN = 50.0f;
				f_Ack->m_Origin = 1;
				f_Ack->m_Owner = GetAdr();
				f_Ack->m_BlockID = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];
				g_Ackent.push_back(f_Ack);

				g_PEERCNT = 0;
				g_SHARECNT = 0;

				Cag->ag_makeGenesisCoin();

				acPay_preference(-1, -1.0, ecoin_Preferences::ecoin_Pref_TimedPledge);
				}
			}break;

		case ecoin_BlockType::ecoin_Block_MaxPledge: //complete
			{
			char* f_GSharequery2 = ag_ClearChar(512);
			::sprintf(f_GSharequery2, "SELECT IFNULL(SUM(pledge + (ecnpledge * %f)), 0), (SELECT SUM(pledge + (ecnpledge * %f)) FROM reference WHERE ((jobid = %i) AND (owner = '%s'))) FROM reference WHERE ((shareid = %i) AND (jobid = %i) AND (owner = '%s'))", m_Price, m_Price, g_JobID, g_Wallet->GetAdr().c_str(), g_ShareID, g_JobID, g_Wallet->GetAdr().c_str());
			g_SafeL[0]->acSelectCommand(f_GSharequery2, false, false);
			delete f_GSharequery2;

			int f_GShareCount = 0;

			if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
				{
				f_GShareCount = 0;
				}
			else
				{
				f_GShareCount = g_Schedular[0]->acEntrySize();
				}

			if(f_GShareCount == 1)
				{
				float f_SummationPledge = atof(g_Schedular[0]->acEntry(0)[0].c_str());

				g_Wallet->m_vec_score[m_current_IDX] = int(atof(g_Schedular[0]->acEntry(0)[1].c_str()));

				if(f_SummationPledge > m_vec_maxpledge[m_current_IDX])
					{
					acPullHash(f_Results->m_HashNibCount);

					acSave_currentBlock(f_Results);

					ag_StatusLive(f_ref_CurrentPath, "f_BlockAck");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_BLOCK), g_ShareID, g_PEERCNT);

					f_Ack->m_ECN = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = GetAdr();
					f_Ack->m_BlockID = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];
					g_Ackent.push_back(f_Ack);

					g_PEERCNT = 0;
					g_SHARECNT = 0;

					Cag->ag_makeGenesisCoin();

					acPay_preference(-1, -1.0, ecoin_Preferences::ecoin_Pref_MaxPledge);
					}
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif
			}break;

		case ecoin_BlockType::ecoin_Block_MaxTimedPledge: //complete
			{
			char* f_GSharequery2 = ag_ClearChar(512);
			::sprintf(f_GSharequery2, "SELECT IFNULL(SUM(pledge + (ecnpledge * %f)), 0), (SELECT SUM(pledge + (ecnpledge * %f)) FROM reference WHERE ((jobid = %i) AND (owner = '%s'))) FROM reference WHERE ((shareid = %i) AND (jobid = %i) AND (owner = '%s'))", m_Price, m_Price, g_JobID, g_Wallet->GetAdr().c_str(), g_ShareID, g_JobID, g_Wallet->GetAdr().c_str());
			g_SafeL[0]->acSelectCommand(f_GSharequery2, false, false);
			delete f_GSharequery2;

			int f_GShareCount = 0;

			if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
				{
				f_GShareCount = 0;
				}
			else
				{
				f_GShareCount = g_Schedular[0]->acEntrySize();
				}

			if(f_GShareCount == 1)
				{
				float f_SummationPledge = atof(g_Schedular[0]->acEntry(0)[0].c_str());

				g_Wallet->m_vec_score[m_current_IDX] = atof(g_Schedular[0]->acEntry(0)[1].c_str());

				 /////////////////////////////////////////
				// timed and height winning conditions //
				if(((f_SummationPledge > m_vec_maxpledge[m_current_IDX]) || (g_Wallet->m_vec_score[m_current_IDX] >= m_vec_maxvote[m_current_IDX])))
					{
					acPullHash(f_Results->m_HashNibCount);

					acSave_currentBlock(f_Results);

					ag_StatusLive(f_ref_CurrentPath, "f_BlockAck");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(static_cast<int>(ACK_TYPE::ACK_TYPE_BLOCK), g_ShareID, g_PEERCNT);

					f_Ack->m_ECN = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = GetAdr();
					f_Ack->m_BlockID = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];
					g_Ackent.push_back(f_Ack);

					g_PEERCNT = 0;
					g_SHARECNT = 0;

					Cag->ag_makeGenesisCoin();

					acPay_preference(-1, -1.0, ecoin_Preferences::ecoin_Pref_MaxPledge);
					}
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif
			}break;
		}
}

void Wallet::acSet_IDX(int f_IDX)
{
	m_current_IDX = f_IDX;
}

void Wallet::acSave_currentJob(void)
{
	char* g_blockvalue[24];

	for(int f_Count = 0; f_Count < 24; f_Count++)
		{
		g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
		}

	// add appeasement
	ag_Freshanon<int>(m_vec_eslid, m_current_IDX, g_CountLM);
	ag_Freshanon<int>(m_vec_targetid, m_current_IDX, ECOIN_DEFAULT_TARGETID);
	ag_Freshanon<float>(m_vec_price, m_current_IDX, 0.0f);
	ag_Freshanon<int>(m_vec_blocktype, m_current_IDX, ECOIN_DEFAULT_BLOCKID);
	ag_Freshanon<int>(m_vec_targetbreach, m_current_IDX, 1);

	sprintf(g_blockvalue[0], "%i", 0);
	sprintf(g_blockvalue[1], "%i", 0);
	sprintf(g_blockvalue[2], "%i", 3);
	sprintf(g_blockvalue[3], "%i", g_JobID);
	sprintf(g_blockvalue[4], "%i", m_vec_eslid[m_current_IDX]);
	sprintf(g_blockvalue[5], "%i", m_vec_targetid[m_current_IDX]);
	sprintf(g_blockvalue[6], "%i", g_ShareID); //SET ON BLOCK FOUND
	sprintf(g_blockvalue[7], "%s-%i#%s", "BLOCK", g_BlockType, g_TypeName.c_str());
	sprintf(g_blockvalue[8], "%f", 0.0f);
	sprintf(g_blockvalue[9], "%i", 0);
	sprintf(g_blockvalue[10], "%i", 10);
	sprintf(g_blockvalue[11], "%s", "BLKLEDGER");
	sprintf(g_blockvalue[12], "%s", "BLKOWNER");
	sprintf(g_blockvalue[13], "%i", 0);
	sprintf(g_blockvalue[14], "%f", 0.5f);
	sprintf(g_blockvalue[15], "%f", 0.4f);
	sprintf(g_blockvalue[16], "%f", 0.97f);
	sprintf(g_blockvalue[17], "%f", m_Reward);
	sprintf(g_blockvalue[18], "%f", 0.0f);
	sprintf(g_blockvalue[19], "%f", 0.0f);
	sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
	sprintf(g_blockvalue[21], "%f", m_vec_price[m_current_IDX]);
	sprintf(g_blockvalue[22], "%i", m_vec_blocktype[m_current_IDX]);
	sprintf(g_blockvalue[23], "%i", m_vec_targetbreach[m_current_IDX]);

	ag_FreshOn<int>(g_Wallet->m_vec_blockid, m_current_IDX, g_SafeL[0]->Insert("block", (const char**)g_blockfield, (const char**)g_blockvalue, 24, false, false));

	for(int f_Count = 0; f_Count < 24; f_Count++)
		{
		free(g_blockvalue[f_Count]);
		}

	ag_Freshanon<int>(g_Wallet->m_vec_blocktype, m_current_IDX, 0);
	ag_Freshanon<int>(g_Wallet->m_vec_scoremax, m_current_IDX, 0);
	ag_Freshanon<float>(g_Wallet->m_vec_markmax, m_current_IDX, 0.0f);
	ag_Freshanon<float>(g_Wallet->m_vec_markmin, m_current_IDX, 0.0f);
	ag_Freshanon<float>(g_Wallet->m_vec_maxvote, m_current_IDX, 0.0f);
	ag_Freshanon<int>(g_Wallet->m_vec_pledgetype, m_current_IDX, 0);
	ag_Freshanon<int>(g_Wallet->m_vec_maxpledge, m_current_IDX, 0);
	ag_Freshanon<int>(g_Wallet->m_vec_targetbreach, m_current_IDX, 0);
	ag_Freshanon<std::string>(g_Wallet->m_vec_owner, m_current_IDX, g_Wallet->GetAdr());

	char* g_jobvalue[15];

	for(int f_Count = 0; f_Count < 15; f_Count++)
		{
		g_jobvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
		}

	::sprintf(g_jobvalue[0], "%i", 3);
	::sprintf(g_jobvalue[1], "%i", m_vec_targetid[m_current_IDX]);
	::sprintf(g_jobvalue[2], "%i", m_vec_blockid[m_current_IDX]);
	::sprintf(g_jobvalue[3], "%i", m_vec_blocktype[m_current_IDX]);
	::sprintf(g_jobvalue[4], "%s", g_TypeName.c_str());
	::sprintf(g_jobvalue[5], "%i", m_vec_pledgetype[m_current_IDX]);
	::sprintf(g_jobvalue[6], "%i", m_vec_maxpledge[m_current_IDX]);
	::sprintf(g_jobvalue[7], "%i", m_vec_targetbreach[m_current_IDX]);

	time_t f_CurrentTime;
	time(&f_CurrentTime);

	::sprintf(g_jobvalue[8], "%i", f_CurrentTime);
	::sprintf(g_jobvalue[9], "%s", m_vec_owner[m_current_IDX].c_str());
	::sprintf(g_jobvalue[10], "%f", m_vec_scoremax[m_current_IDX]);
	::sprintf(g_jobvalue[11], "%f", m_vec_markmax[m_current_IDX]);
	::sprintf(g_jobvalue[12], "%f", m_vec_markmin[m_current_IDX]);
	::sprintf(g_jobvalue[13], "%f", m_Reward);
	::sprintf(g_jobvalue[14], "%i", m_RewardID);

	ag_FreshOn<int>(m_vec_jobboardid, m_current_IDX, g_SafeL[0]->Insert("job", (const char **)g_jobfield, (const char **)g_jobvalue, 15, false, false));

	for(int f_Count = 0; f_Count < 15; f_Count++)
		{
		free(g_jobvalue[f_Count]);
		}

	if(m_vec_jobvar_index.size() > 0)
		{
		for(int f_Jet = 0; f_Jet < m_vec_jobvar_index[m_current_IDX].size(); f_Jet++)
			{
			int f_Index = m_vec_jobvar_index[m_current_IDX][f_Jet];

			acSave_currentJobVar(f_Index, m_vec_jobboardid[m_current_IDX]);

			m_vec_jobvar_save[m_current_IDX][f_Jet] = false;
			m_vec_jobvar_textupdate[m_current_IDX][f_Jet] = false;
			}
		}
}

void Wallet::acSave_currentJobVar(int f_Index, int f_JobIndex)
{
	if(m_vec_jobvarid[m_current_IDX][f_Index] > 0)
		{
		char* g_jobvarvalue[4];
		char* f_ownerwhere[1];

		for(int f_Jet = 0; f_Jet < 4; f_Jet++)
			{
			g_jobvarvalue[f_Jet] = (char*)malloc(sizeof(char) * 1024);
			}

		f_ownerwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(g_jobvarvalue[0], "%i", f_JobIndex);
		::sprintf(g_jobvarvalue[1], "%s", m_vec_jobvar_name[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[2], "%s", m_vec_jobvar_groupname[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[3], "%f", m_vec_jobvar_value[m_current_IDX][f_Index]);

		::sprintf(f_ownerwhere[0], "id = %i", m_vec_jobvarid[m_current_IDX][f_Index]);

		g_SafeL[0]->Update("jobvar", (const char**)g_jobvarvalue, (const char**)g_jobfield, 4, f_ownerwhere[0], true, false);

		for(int f_Jet = 0; f_Jet < 4; f_Jet++)
			{
			free(g_jobvarvalue[f_Jet]);
			}

		free(f_ownerwhere[0]);
		}
	else
		{
		char* g_jobvarvalue[4];

		for(int f_Count = 0; f_Count < 4; f_Count++)
			{
			g_jobvarvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		::sprintf(g_jobvarvalue[0], "%i", f_JobIndex);
		::sprintf(g_jobvarvalue[1], "%s", m_vec_jobvar_name[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[2], "%s", m_vec_jobvar_groupname[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[3], "%f", m_vec_jobvar_value[m_current_IDX][f_Index]);

		int f_JobUniqueID = g_SafeL[0]->Insert("jobvar", (const char **)g_jobvarfield, (const char **)g_jobvarvalue, 4, false, false);

		for(int f_Count = 0; f_Count < 4; f_Count++)
			{
			free(g_jobvarvalue[f_Count]);
			}
		}
}

void Wallet::acSave_currentBlock(std::shared_ptr<Cube::CubeResults> f_Results)
{
	if(m_vec_blockid[m_current_IDX] > 0) // update current block
		{
		g_JobID = g_Wallet->acGet_JobID(m_current_IDX);

		if(f_Results->m_Job_Complete == true)
			{
			g_JobID = g_Wallet->acSet_JobID(g_Wallet->m_current_IDX, 1);

			ag_FreshOn<int>(g_Wallet->m_vec_jobid, g_Wallet->m_current_IDX, g_JobID);
			}

		 ///////////////////////////////////////////////////////////////////////
		// Toss share calculation transaction onto next block/jobid as yield //
		Cag->ag_addGenesisTracking(g_ShareID, ecoin_BlockType::ecoin_Block_Target_SCP, g_BicycleContainer[0]->m_ADMAX);

		 /////////////////////////////////////////////////
		// Update Current SCP-Share according to Block //
		std::string f_Freshanon = "GenesisBlock";

		ag_Freshanon<std::string>(g_Wallet->m_vec_prevblock, m_current_IDX, f_Freshanon);

		std::string f_previousblock = g_Wallet->m_vec_prevblock[m_current_IDX];

		 /////////////////////
		// Gather StepHash //
		std::shared_ptr<Cube::CubeResults> f_Res = Cag->ag_GatherTransactions(g_JobID, m_current_IDX);

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

		ag_FreshOn<std::string>(m_vec_blockledger, m_current_IDX, f_TXJob_OutputHash);

		char* g_blockvalue[19];
		char* gf_blockfield[19];
		char* f_blockwhere[1];

		for(int f_Count = 0; f_Count < 19; f_Count++)
			{
			g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			gf_blockfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		f_blockwhere[0] = (char*)malloc(sizeof(char) * 512);

		sprintf(gf_blockfield[0], "mark");
		sprintf(gf_blockfield[1], "jobid");
		sprintf(gf_blockfield[2], "shareid");
		sprintf(gf_blockfield[3], "eslcode");
		sprintf(gf_blockfield[4], "difficulty");
		sprintf(gf_blockfield[5], "score");
		sprintf(gf_blockfield[6], "maxvote");
		sprintf(gf_blockfield[7], "blockledger");
		sprintf(gf_blockfield[8], "owner");
		sprintf(gf_blockfield[9], "bckred");
		sprintf(gf_blockfield[10], "bckgreen");
		sprintf(gf_blockfield[11], "bckblue");
		sprintf(gf_blockfield[12], "reward");
		sprintf(gf_blockfield[13], "pledge");
		sprintf(gf_blockfield[14], "ecnpledge");
		sprintf(gf_blockfield[15], "fee");
		sprintf(gf_blockfield[16], "price");
		sprintf(gf_blockfield[17], "blocktype");
		sprintf(gf_blockfield[18], "breach");

		ag_Freshanon<float>(m_vec_current_pledge, m_current_IDX, 0.0f);
		ag_Freshanon<float>(m_vec_current_ecnpledge, m_current_IDX, 0.0f);

		sprintf(g_blockvalue[0], "%i", m_vec_mark[m_current_IDX]);
		sprintf(g_blockvalue[1], "%i", g_JobID);
		sprintf(g_blockvalue[2], "%i", g_ShareID);
		sprintf(g_blockvalue[3], "%s#CurrentNib#%s#Final#%s#ReferencePad#%s", g_TypeName.c_str(), f_Results->m_CurrentNib.c_str(), f_Results->m_FinalResult.c_str(), f_Results->m_ReferencesPad.c_str());
		sprintf(g_blockvalue[4], "%f", m_vec_difficulty[m_current_IDX]);
		sprintf(g_blockvalue[5], "%f", m_vec_score[m_current_IDX]);
		sprintf(g_blockvalue[6], "%f", m_vec_scoremax[m_current_IDX]);
		sprintf(g_blockvalue[7], "%s", m_vec_blockledger[m_current_IDX].c_str());
		sprintf(g_blockvalue[8], "%s", GetAdr().c_str());
		sprintf(g_blockvalue[9], "%f", m_vec_bckred[m_current_IDX]);
		sprintf(g_blockvalue[10], "%f", m_vec_bckgreen[m_current_IDX]);
		sprintf(g_blockvalue[11], "%f", m_vec_bckblue[m_current_IDX]);
		sprintf(g_blockvalue[12], "%f", m_Reward);
		sprintf(g_blockvalue[13], "%f", m_vec_current_pledge[m_current_IDX]);
		sprintf(g_blockvalue[14], "%f", m_vec_current_ecnpledge[m_current_IDX]);
		sprintf(g_blockvalue[15], "%f", ECN_TX_FEE);
		sprintf(g_blockvalue[16], "%f", m_vec_price[m_current_IDX]);
		sprintf(g_blockvalue[17], "%i", m_vec_blocktype[m_current_IDX]);

		time_t f_CurrentTime;
		time(&f_CurrentTime);

		sprintf(g_blockvalue[18], "%i", f_CurrentTime);

		sprintf(f_blockwhere[0], "id = %i", m_vec_blockid[m_current_IDX]);

		g_SafeL[0]->Update("block", (const char**)g_blockvalue, (const char**)gf_blockfield, 19, f_blockwhere[0], true, false);

		for(int f_Count = 0; f_Count < 19; f_Count++)
			{
			free(g_blockvalue[f_Count]);
			free(gf_blockfield[f_Count]);
			}

		free(f_blockwhere[0]);
		}
}

float Wallet::acSelect_JobVar(int f_IDX, std::string f_JobString)
{
	if(f_IDX < m_vec_jobvar_name.size())
		{
		for(int f_Jet = 0; f_Jet < m_vec_jobvar_name[f_IDX].size(); f_Jet++)
			{
			if(f_JobString.compare(m_vec_jobvar_name[f_IDX][f_Jet]) == 0)
				{
				return m_vec_jobvar_value[f_IDX][f_Jet];
				}
			}
		}

	return 0.0f;
}

int Wallet::acGet_JobID(int f_IDX, int f_Layer, bool f_MainMutex)
{
	char* blokquery = ag_ClearChar(2555);
	::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block WHERE jobid = (SELECT MAX(jobid) FROM block) ORDER BY dated DESC LIMIT 1");
	g_SafeL[f_Layer]->acSelectCommand(blokquery, 2, false, f_MainMutex);
	delete blokquery;

	int f_blokLCount = 0;

	if(g_Schedular[f_Layer]->acEntry(0)[0].at(0) == '0')
		{
		f_blokLCount = 0;
		}
	else
		{
		f_blokLCount = g_Schedular[f_Layer]->acEntrySize();
		}

	ag_Freshanon<int>(m_vec_joborigin, f_IDX, -1);

	if(f_blokLCount > 0)
		{
		ag_FreshOn<int>(m_vec_jobid, f_IDX, ::atoi(g_Schedular[f_Layer]->acEntry(0)[1].c_str()));
		ag_FreshOn<std::string>(m_vec_prevblock, f_IDX, g_Schedular[f_Layer]->acEntry(0)[2]);

		return m_vec_jobid[f_IDX];
		}
	else
		{
		ag_FreshOn<int>(m_vec_jobid, f_IDX, 0);
		ag_FreshOn<std::string>(m_vec_prevblock, f_IDX, "GENESISBLOCK");

		m_vec_joborigin[f_IDX] = m_vec_jobid[f_IDX];

		return m_vec_jobid[f_IDX];
		}

	return 0;
}

int Wallet::acSet_JobID(int f_IDX, int f_Increment)
{
	ag_FreshOn<int>(m_vec_jobid, f_IDX, g_JobID + f_Increment);

	g_JobID = m_vec_jobid[f_IDX];

	char* Jobquery = ag_ClearChar(1024);
	::sprintf(Jobquery, "UPDATE transactions SET jobid = %i WHERE ((status != -5) AND (jobid < %i) AND (confirmation < 6))", m_vec_jobid[f_IDX], m_vec_jobid[f_IDX]);
	int f_Resp = g_SafeL[0]->acCommand(Jobquery, 0, false, true);
	delete Jobquery;

	return m_vec_jobid[f_IDX];
}

};