//////////////////////////////////////////////////////////////////////
/*

    QSharedStruct.h - Shared Memory Class
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/
//////////////////////////////////////////////////////////////////////

#if !defined(QSharedStruct_H_)
#define QSharedStruct_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aclapi.h"

#define CreateFileMappingA CreateFileMappingW

typedef struct PlacementMarker
{
	unsigned int m_Count;
} PlacementMarker;

template <class StructType>
class QSharedStruct
{
public:
	HANDLE m_hFileMapping;
	char   m_hSharedName[MAX_PATH];
	DWORD  m_dwMaxDataSize;
	StructType *m_pvData;

	bool m_bCreated;

public:
	QSharedStruct();
	QSharedStruct(char *Name);
	~QSharedStruct();

	void Release(void);

	bool Acquire(char *Name, int i_case = 0);
	void Allocate(void); // char* Name, bool i_construct = true);

	bool Recieve(char *Name, bool i_construct = true);

	StructType *operator->();

	StructType * operator=(StructType * rhs) { return (StructType*)this; };
};


template <class StructType>
StructType *QSharedStruct<StructType>::operator->()
{
	return m_pvData;
}

template <class StructType>
QSharedStruct<StructType>::QSharedStruct()
{
	m_hFileMapping = NULL;
}

template <class StructType>
QSharedStruct<StructType>::~QSharedStruct()
{
	Release();
}


template <class StructType>
QSharedStruct<StructType>::QSharedStruct(char *Name)
{
	m_hFileMapping = NULL;
	
	Acquire(Name);
}

template <class StructType>
void QSharedStruct<StructType>::Release()
{
#if 0

   if(m_pvData)
		{
		UnmapViewOfFile(m_pvData);
		m_pvData = NULL;
		}

   if(m_hFileMapping)
		{
		CloseHandle(m_hFileMapping);
		}

#else

	delete m_pvData;

#endif
}

template <class StructType>
bool QSharedStruct<StructType>::Acquire(char *Name, int i_case)
{
	char casecntbuf[100];

	_itoa(i_case, casecntbuf, 10);

	std::string i_strcase = casecntbuf;
	std::string i_strname = Name;
	std::string i_name = i_strname + i_strcase;

#if 1 // QAGE_DESKTOP
	m_dwMaxDataSize = 0;
	m_hFileMapping = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(StructType), (LPCWSTR)i_name.c_str());

	if(m_hFileMapping == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::QSharedStruct m_hFileMapping handle NULL name %s\n", i_name.c_str());
		}

	// OK, if we're the first person to create this
	// file mapping object
	// we want to clear the ACL, so
	// anyone else can access this object
	//
	// If we don't do this, and a service creates the file mapping
	// User processes won't be able to access it.

	// So, we set the DACL to NULL, which effectively
	// grants Everyone All Access

	// More complicated ACLs are left as an exercise for the reader
	// (because I sure as hell can't figure them out!)

	//*SetNamedSecurityInfo((char*)i_name.c_str(), SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);

	m_dwMaxDataSize = sizeof(StructType);

	m_pvData = (StructType *) MapViewOfFile( m_hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

	::new(m_pvData) StructType;

	if(m_pvData == NULL)
		{
		CloseHandle(m_hFileMapping);
		printf("ERROR:::QSharedStruct initialization handle NULL name %s\n", i_name.c_str());
		}
#else
	Allocate(Name, true);
#endif

   return true;
}

template <class StructType>
void QSharedStruct<StructType>::Allocate(void) //char *Name, bool i_construct)
{
	m_dwMaxDataSize = 0;

#if 0
	m_pvData = (StructType*) malloc (sizeof (StructType));
#endif

	m_pvData = new StructType;
}

template <class StructType>
bool QSharedStruct<StructType>::Recieve(char *Name, bool i_construct)
{
	m_dwMaxDataSize = 0;

	//*m_hFileMapping = OpenFileMapping (FILE_MAP_ALL_ACCESS, false, Name);

	if (m_hFileMapping == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::QSharedStruct m_hFileMapping handle NULL\n");
		for(;;) {};
		return false;
		}

	// OK, if we're the first person to create this
	// file mapping object
	// we want to clear the ACL, so
	// anyone else can access this object
	//
	// If we don't do this, and a service creates the file mapping
	// User processes won't be able to access it.

	// So, we set the DACL to NULL, which effectively
	// grants Everyone All Access

	// More complicated ACLs are left as an exercise for the reader
	// (because I sure as hell can't figure them out!)

	//SetNamedSecurityInfo(Name, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);

	//*m_dwMaxDataSize = sizeof(StructType);
	//strncpy(m_hSharedName, Name, MAX_PATH - 1);

	//*m_pvData = (StructType *) MapViewOfFile( m_hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	//::new(m_pvData) StructType;

	//*if (m_pvData == NULL)
	//*	{
	//*	CloseHandle(m_hFileMapping);
	//*	printf("ERROR:::QSharedStruct initialization handle NULL\n");
	//*	for(;;) {};
	//*	return false;
	//*	}

   return true;
}

#endif