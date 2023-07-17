//////////////////////////////////////////////////////////////////////
/*

    CSharedStruct.h - Shared Memory Class
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

   void Release();
   bool Acquire(char *Name, bool i_construct = true);

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
   //QSharedStruct();
   Acquire(Name);
}

template <class StructType>
void QSharedStruct<StructType>::Release()
{
   if (m_pvData)
   {
      UnmapViewOfFile(m_pvData);
      m_pvData = NULL;
   }

   if (m_hFileMapping)
   {
      CloseHandle(m_hFileMapping);
   }
}

template <class StructType>
bool QSharedStruct<StructType>::Acquire(char *Name, bool i_construct)
{
	m_dwMaxDataSize = 0;
	m_hFileMapping = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(StructType), Name);

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

	SetNamedSecurityInfo(Name, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);

	m_dwMaxDataSize = sizeof(StructType);
	//strncpy(m_hSharedName, Name, MAX_PATH - 1);

	m_pvData = (StructType *) MapViewOfFile( m_hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

	::new(m_pvData) StructType;

	printf("QSharedStruct Initialized at %i\n", (int)m_pvData);

	if (m_pvData == NULL)
		{
		CloseHandle(m_hFileMapping);
		printf("ERROR:::QSharedStruct initialization handle NULL\n");
		for(;;) {};
		return false;
		}

   return true;
}

#endif