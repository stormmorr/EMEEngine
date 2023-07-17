/*

    UserAccount - Woffle User Accounts
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <string>

namespace Woffle
{

class UserAccount
{
public:
	UserAccount();
	~UserAccount();

	string m_email;
	string m_password;
	string m_nick;

	float m_userActionCredit;

};

};

#endif