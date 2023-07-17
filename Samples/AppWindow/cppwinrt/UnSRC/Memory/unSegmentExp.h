/*

	unSegment - Memory Management
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef SEGMENT_H
#define SEGMENT_H

#include "unSegmentHeader.h"
#include "unIdentManager.h"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "Aclapi.h"

#include <vector>

#define SIZE_INT sizeof(int)
#define UN_SEGMENT_DEFAULT_SIZE 65536

using namespace std;
using namespace UN;
using namespace boost::interprocess;
namespace ip = boost::interprocess;

#define DllImport  __declspec( dllimport )
#define DllExport  __declspec( dllexport )

namespace UN
{

struct unSeg
{
	void *m_Start;
	void *m_End;
};

class unSegmentMgr
{
public:
	unSegmentMgr() :
	m_unSegment(create_only, "UnificationSPC", UN_SEGMENT_DEFAULT_SIZE)
	{}

	managed_shared_memory m_unSegment;

	~unSegmentMgr() {};

	void acShutdown(bool i_CFlag)
		{
		if(i_CFlag) shared_memory_object::remove("UnificationSPC");
		}
};

class unSegmentFrame
{
public:
	unSegmentFrame() :
	m_unSegment(open_only, "UnificationSPC")
	{}

	managed_shared_memory m_unSegment;

	~unSegmentFrame() {};

	void acShutdown(bool i_CFlag)
		{
		}
};

extern DllExport managed_shared_memory *m_unSegment;

extern DllExport unSegmentMgr *m_unSegFrame;

void acSegmentInitialize(bool i_CFlag);

template<typename T>
class unSegment
{
public:
	unSegment() {};
	~unSegment() {};

	char m_SystemIdent[UN_IDENT_LEN];
	int *m_currentPtr;

	unSeg m_AddressMap;

	void acMapSharedAccess(char *i_Ident, int i_FileSize = 0)
		{
		//*HANDLE i_FileMapping = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, i_FileSize, i_Ident);

		//*if (i_FileMapping == NULL)
		//*	{
		//*	int err = GetLastError();
		//*	printf("ERROR:::unSegment::MapSharedAccess m_hFileMapping handle NULL errorcode...%i\n", err);
		//*	for(;;) {};
		//*	}

		//*SetNamedSecurityInfo(i_Ident, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);

		//*void *i_FilePtr = MapViewOfFile(i_FileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, i_FileSize);

		//*if (i_FilePtr == NULL)
		//*	{
		//*	CloseHandle(i_FileMapping);
		//*	printf("ERROR:::unSegment::MapSharedAccess MapViewOfFile pointer NULL\n");
		//*	for(;;) {};
		//*	}

		//*m_AddressMap.m_Start = i_FilePtr;
		//*m_AddressMap.m_End = (int*) i_FilePtr + i_FileSize;

#pragma message("WARNING possibly add single char reduction to memcpy for both name instances")
		//*strncpy_s(m_SystemIdent, i_Ident, UN_IDENT_LEN);

		//::new(m_pvData) StructType;
		}

	void acPrintHeader(int i_NomElements)
		{
		m_currentPtr = (int*) m_AddressMap.m_Start;

		// Print Header Vector Count
		*m_currentPtr = i_NomElements;
		m_currentPtr += SIZE_INT; 
		}

	void acAdd(T i_Element)
		{
		T i_Insertion = (T) i_currentPtr;

		//::new(i_Insertion) T;

		i_currentPt += sizeof(T);
		}

private:
	//static OsirusCore* s_instance;
};

};

#endif