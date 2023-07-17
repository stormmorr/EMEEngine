/*

    ThreadData.h - Thread Data Management
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef _THREAD_DATA_H_
#define _THREAD_DATA_H_

class icThreadData;

class Data_Interface
{
public:
	virtual icThreadData * ReadData() = 0;
	virtual void WriteData(icThreadData *) = 0;
};


class icThreadData : public Data_Interface
{
public:
	virtual icThreadData * ReadData() = 0;
	virtual void WriteData(icThreadData *) = 0;
};

#endif //_THREAD_DATA_H_