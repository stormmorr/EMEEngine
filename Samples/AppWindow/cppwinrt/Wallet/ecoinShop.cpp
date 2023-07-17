/*

eshop.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "ecoinShop.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>

#include "Code/Work/Schedular.h"

#include "Wallet.h"

using namespace ecoin;

namespace ecoin
{

int g_Type = 0;
string g_TypeName = "";

int ag_FindTypefromText(std::string f_ESL_Code)
{
	//Target_TypeName
	if(f_ESL_Code.compare("FRMESH") == 0) //Basic Cube Structural Only Mesh
		{
		return 1;
		}
	else if(f_ESL_Code.compare("FRTGME") == 0)
		{
		return 2;
		}
	else if(f_ESL_Code.compare("FRECOM") == 0)	//SCP
		{
		return 3;
		}
	else if(f_ESL_Code.compare("FRTGEC") == 0) //ECOM Functionality 
		{
		return 4;
		}
	else if(f_ESL_Code.compare("FRESLS") == 0) //Single Script ESL
		{
		return 5;
		}
	else if(f_ESL_Code.compare("FRTGES") == 0) //Single Script ESL Target
		{
		return 6;
		}
	else if(f_ESL_Code.compare("FRGENS") == 0) //INL Generation Script
		{
		return 7;
		}
	else if(f_ESL_Code.compare("FRTGGE") == 0) //INL Generation Script Target
		{
		return 8;
		}
	else if(f_ESL_Code.compare("FRJSSC") == 0) //eJavaScript Script
		{
		return 9;
		}
	else if(f_ESL_Code.compare("FRTGJS") == 0) //eJavaScript Script Target
		{
		return 10;
		}
	else if(f_ESL_Code.compare("FVMESH") == 0) //Target_VoteDriven
		{
		return 11;
		}

	return 0;
}

int ag_FindTypefromCode(std::string f_ESL_Code)
{
	std::string f_ProductName;
	std::string f_ProductDescription;
	std::string f_ProductTypeText;

	f_ProductName.clear();
	f_ProductDescription.clear();
	f_ProductTypeText.clear();

	int f_HeadMode = 0;
	for(int f_XYZ = 0; f_XYZ < f_ESL_Code.length(); f_XYZ++)
		{
		char f_Char = f_ESL_Code.at(f_XYZ);

		if(f_Char == ECOIN_SHOP_PROTOCOL_SEPARATOR)
			{
			f_HeadMode++;
			}
		else
			{
			if(f_HeadMode == 0)
				{
				f_ProductTypeText.push_back(f_Char);
				}
			else if(f_HeadMode == 1)
				{
				f_ProductName.push_back(f_Char);
				}
			else
				{
				f_ProductDescription.push_back(f_Char);
				}
			}
		}

	return ag_FindTypefromText(f_ProductTypeText);
}

std::string ag_FindPrefixfromCode(std::string f_ESL_Code)
{
	std::string f_ProductName;
	std::string f_ProductDescription;
	std::string f_ProductTypeText;

	f_ProductName.clear();
	f_ProductDescription.clear();
	f_ProductTypeText.clear();

	int f_HeadMode = 0;
	for(int f_XYZ = 0; f_XYZ < f_ESL_Code.length(); f_XYZ++)
		{
		char f_Char = f_ESL_Code.at(f_XYZ);

		if(f_Char == ECOIN_SHOP_PROTOCOL_SEPARATOR)
			{
			f_HeadMode++;
			}
		else
			{
			if(f_HeadMode == 0)
				{
				f_ProductTypeText.push_back(f_Char);
				}
			else if(f_HeadMode == 1)
				{
				f_ProductName.push_back(f_Char);
				}
			else
				{
				f_ProductDescription.push_back(f_Char);
				}
			}
		}

	return f_ProductTypeText;
}

eshop::eshop(int f_IDX)
{
	std::string f_ref_CurrentPath = "eshop::eshop";

	m_IDX = f_IDX;

	m_ShopPage = 1;

#ifndef OSI_MEM_APP
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&eshop::acClear);

	//global referencing
	ag_Push(g_Type, f_ref_CurrentPath + g_ref_global_Div + "g_Type");
	ag_Push(g_TypeName, f_ref_CurrentPath + g_ref_global_Div + "g_TypeName");
	ag_Push(m_ShopPage, f_ref_CurrentPath + g_ref_global_Div + "m_ShopPage");
#endif
}

eshop::~eshop()
{
	if(m_vec_Product.size() > 0)
		{
		acClear();
		}
}

std::string eshop::acSearch_Shop(std::string f_Name, std::string f_Description, std::string f_Prefix)
{
	ag_Freshanon<int>(g_Wallet->m_vec_MainMode, m_IDX, ECOIN_MODE_VIEWING);

	if((g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_NONVIEW) || (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
		{
		return std::string("Oops please pause divining or compression for shop search,...");
		}

	int f_NameLength = f_Name.length();
	int f_DescriptionLength = f_Description.length();
	int f_PrefixLength = f_Prefix.length();

	f_Name = "%" + f_Name + "%";
	f_Description = "%" + f_Description + "%";
	f_Prefix = "%" + f_Prefix + "%";

	int f_ShopPage = m_ShopPage;

	if(f_ShopPage < 1)
		{
		f_ShopPage = 1;
		}

	bool f_BoughtCom = g_BoughtCom;
	bool f_MyOwnCom = g_MyOwnCom;

	if(f_NameLength == 0)
		{
		if(f_DescriptionLength == 0)
			{
			if(f_PrefixLength == 0)
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share ORDER BY id DESC LIMIT %i", ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE owner = '%s' ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE owner = '%s' ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}
				
				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By All Results, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			else
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' ORDER BY id DESC LIMIT %i", f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) AND (sharelist.eslcode LIKE '%s') UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) AND (sharelistB.eslcode LIKE '%s') ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}

				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By Prefix Alone, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			}
		else
			{
			if(f_PrefixLength > 0)
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE (eslcode LIKE '%s' OR eslcode LIKE '%s') ORDER BY id DESC LIMIT %i", f_Description.c_str(), f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE (eslcode LIKE '%s' OR eslcode LIKE '%s') AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Description.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) AND ((sharelist.eslcode LIKE '%s') OR (sharelist.eslcode LIKE '%s')) UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) AND ((sharelistB.eslcode LIKE '%s') OR (sharelistB.eslcode LIKE '%s')) ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), f_Description.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), f_Description.c_str(), f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE (eslcode LIKE '%s' OR eslcode LIKE '%s') AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Description.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}

				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By Description And Prefix, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			else
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' ORDER BY id DESC LIMIT %i", f_Description.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Description.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) AND (sharelist.eslcode LIKE '%s') UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) AND sharelistB.eslcode LIKE '%s' ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), f_Description.c_str(), g_Wallet->GetAdr().c_str(), f_Description.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Description.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}
				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By Description Alone, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			}
		}
	else //name > 0
		{
		if(f_DescriptionLength == 0)
			{
			if(f_PrefixLength == 0)
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) AND sharelist.eslcode LIKE '%s' UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) AND sharelistB.eslcode LIKE '%s' ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), f_Name.c_str(), g_Wallet->GetAdr().c_str(), f_Name.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE eslcode LIKE '%s' AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}

				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By Name Alone, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			else
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE (eslcode LIKE '%s' OR eslcode LIKE '%s') ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE (eslcode LIKE '%s' OR eslcode LIKE '%s') AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) AND ((sharelist.eslcode LIKE '%s') OR (sharelist.eslcode LIKE '%s')) UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) AND ((sharelistB.eslcode LIKE '%s') OR (sharelistB.eslcode LIKE '%s')) ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), f_Name.c_str(),  f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), f_Name.c_str(), f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE (eslcode LIKE '%s' OR eslcode LIKE '%s') AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}

				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By Name And Prefix, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			}
		else
			{
			if(f_PrefixLength > 0)
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE ((eslcode LIKE '%s') OR (eslcode LIKE '%s') OR (eslcode LIKE '%s')) ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Description.c_str(), f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE ((eslcode LIKE '%s') OR (eslcode LIKE '%s') OR (eslcode LIKE '%s')) AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Description.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) AND ((sharelist.eslcode LIKE '%s') OR (sharelist.eslcode LIKE '%s') OR (sharelist.eslcode LIKE '%s')) UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) AND ((sharelistB.eslcode LIKE '%s') OR (sharelistB.eslcode LIKE '%s') OR (sharelistB.eslcode LIKE '%s')) ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), f_Name.c_str(), f_Description.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), f_Name.c_str(), f_Description.c_str(), f_Prefix.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE ((eslcode LIKE '%s') OR (eslcode LIKE '%s') OR (eslcode LIKE '%s')) AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Description.c_str(), f_Prefix.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}

				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By Name/Description/Prefix, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			else
				{
				char* shopquery = ag_ClearChar(3000);

				if(f_BoughtCom == false)
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share ((eslcode LIKE '%s') OR (eslcode LIKE '%s')) ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Description.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE ((eslcode LIKE '%s') OR (eslcode LIKE '%s') AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Description.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
				else
					{
					if(f_MyOwnCom == false)
						{
						std::sprintf(shopquery, "SELECT sharelist.id, sharelist.score, sharelist.eslcode, sharelist.price, sharelist.dated FROM share AS sharelist INNER JOIN modpay AS modlist ON ((modlist.shareid = sharelist.id) AND (modlist.amtpay >= sharelist.price) AND (modlist.payowner = '%s')) AND ((sharelist.eslcode LIKE '%s') OR (sharelist.eslcode LIKE '%s')) UNION ALL SELECT sharelistB.id, sharelistB.score, sharelistB.eslcode, sharelistB.price, sharelistB.dated FROM share AS sharelistB INNER JOIN transactions AS txlist ON ((txlist.shareid = sharelistB.id) AND (txlist.confirmation = 6) AND (txlist.status != -5) AND (txlist.amt >= sharelistB.price) AND (txlist.owner = '%s')) AND ((sharelistB.eslcode LIKE '%s') OR (sharelistB.eslcode LIKE '%s')) ORDER BY id DESC LIMIT %i", g_Wallet->GetAdr().c_str(), f_Name.c_str(), f_Description.c_str(), g_Wallet->GetAdr().c_str(), f_Name.c_str(), f_Description.c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					else
						{
						std::sprintf(shopquery, "SELECT id, score, eslcode, price, dated FROM share WHERE ((eslcode LIKE '%s') OR (eslcode LIKE '%s') AND owner = '%s' ORDER BY id DESC LIMIT %i", f_Name.c_str(), f_Description.c_str(), g_Wallet->GetAdr().c_str(), ECOIN_SEARCH_ROW_MAX);
						}
					}
			
				g_SafeL[0]->acSelectCommand(shopquery, false, false);

				delete shopquery;

				int f_ShopLCount = 0;
		
				if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
					{
					f_ShopLCount = 0;
					}
				else
					{
					f_ShopLCount = g_Schedular[0]->acEntrySize();
					}

				char* shopreturn = ag_ClearChar(1000);
				std::sprintf(shopreturn, "Searching By Name And Description, Page (%i) ResultCount (%i)...", f_ShopPage, f_ShopLCount);
				std::string f_ReturnStr = shopreturn;
				delete shopreturn;
				return f_ReturnStr;
				}
			}
		}

	return std::string("Oops please enter search terms,...");
}

int eshop::acPopulate(void)
{
	m_vec_Product.clear();

	int f_ConLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_ConLCount = 0;
		}
	else
		{
		f_ConLCount = g_Schedular[0]->acEntrySize();
		}

	int f_ProductCount = 0;

	//assume remote connection for windows
	if(f_ConLCount > 0)
		{
		for(int f_XY = 0; f_XY < f_ConLCount; f_XY++)
			{
			shared_ptr<eshop_Product> f_Product = make_shared<eshop_Product>();

			f_Product->m_ShareID = ::atoi(g_Schedular[0]->acEntry(f_XY)[0].c_str());
			f_Product->m_Score = ::atoi(g_Schedular[0]->acEntry(f_XY)[1].c_str());
			f_Product->m_CostCPS = atof(g_Schedular[0]->acEntry(f_XY)[3].c_str());
			f_Product->m_ComID = -1; //::atoi(g_Schedular[0]->acEntry(f_XY][4].c_str());
			//...

			std::string f_ESL_Code = g_Schedular[0]->acEntry(f_XY)[2];
			
			std::string f_ProductName;
			std::string f_ProductDescription;
			std::string f_ProductTypeText;

			f_ProductName.clear();
			f_ProductDescription.clear();
			f_ProductTypeText.clear();

			int f_HeadMode = 0;

			for(int f_XYZ = 0; f_XYZ < f_ESL_Code.length(); f_XYZ++)
				{
				char f_Char = f_ESL_Code.at(f_XYZ);

				if(f_Char == ECOIN_SHOP_PROTOCOL_SEPARATOR)
					{
					f_HeadMode++;
					}
				else
					{
					if(f_HeadMode == 0)
						{
						f_ProductTypeText.push_back(f_Char);
						}
					else if(f_HeadMode == 1)
						{
						f_ProductName.push_back(f_Char);
						}
					else
						{
						f_ProductDescription.push_back(f_Char);
						}
					}
				}

			char numbuf5[100];
			_itoa(f_Product->m_ShareID, numbuf5, 10);

			f_Product->m_Name = f_ProductName + " (" + numbuf5 + ")";
			f_Product->m_Description = f_ProductDescription;
			f_Product->m_TypeText = f_ProductTypeText;
			f_Product->m_Type = ag_FindTypefromText(f_ProductTypeText);

			m_vec_Product.push_back(f_Product);
			f_ProductCount++;
			}
		}

	return f_ProductCount;
}

};