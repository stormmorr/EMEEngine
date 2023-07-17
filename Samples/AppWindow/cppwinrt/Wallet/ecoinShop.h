/*

Wallet.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ESHOP_H
#define ESHOP_H

#include <vector>
#include <string>
#include <memory>

namespace ecoin
{
extern int g_Type;
extern std::string g_TypeName;

#define ECOIN_SHOP_PROTOCOL_SEPARATOR '#'

#define ECOIN_SHOP_WILDCARD_SW "\%%s\%"

class eshop_Product : public ecom_base
{
public:

	eshop_Product()
		{
		acClear();
		}
	~eshop_Product()
		{
		acClear();
		}

	void acClear(void)
		{
		m_Name.clear();
		m_Description.clear();
		m_Cost = 0.0f;
		m_CostCPS = 0.0f;
		m_ShareID = -1;
		m_ComID = -1;
		m_Score = 0;
		}

	std::string m_Name;
	std::string m_Description;
	std::string m_TypeText;
	int m_Type;
	float m_Cost;
	float m_CostCPS;
	int m_ShareID;
	int m_ComID;
	int m_Score;
};

class eshop : public ecom_base
{
public:
	eshop(int f_IDX);
	~eshop();

	void acClear(void)
		{
		m_vec_Product.clear();
		}

	std::string acSearch_Shop(std::string f_Name, std::string f_Description, std::string f_Prefix);

	int acPopulate(void);

	std::vector<std::shared_ptr<eshop_Product>> m_vec_Product;

	int m_ShopPage;

	int m_IDX;
};

extern int ag_FindTypefromText(std::string f_ESL_Code);

extern int ag_FindTypefromCode(std::string f_ESL_Code);

extern std::string ag_FindPrefixfromCode(std::string f_ESL_Code);

};

#endif