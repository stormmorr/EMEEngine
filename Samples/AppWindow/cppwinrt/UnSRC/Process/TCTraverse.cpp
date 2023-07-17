// TCTraverse.cpp: implementation of the TCTraverse class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "windows.h"
#include "TCTraverse.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCTraverse::TCTraverse()
{

}

TCTraverse::~TCTraverse()
{
	VirtualFree(
		m_lpBuffer,
		0,
		MEM_RELEASE
	);
}

int TCTraverse::mInit(HANDLE hProcess, MEMORY_BASIC_INFORMATION &mbi, long lBufferSize)
{
	m_hProcess = hProcess;
	memcpy(&m_mbi, &mbi, sizeof(mbi));
	m_lpBuffer = VirtualAlloc(NULL, //Any Address
		lBufferSize,
		MEM_COMMIT,	//Allocate it
		PAGE_READWRITE);	
	if(m_lpBuffer == NULL) return 0;
	m_lBufferSize = lBufferSize;
	return 1;
}

//Load the next buffer.
//1 = ok, -1 = less bytes than expected
//0 = No bytes read. (Out of range)
int TCTraverse::mLoad(int blockNo)
{
	DWORD dwOffset = 0;
	LPVOID lpAddress;
	DWORD dwBytesRead;

	dwOffset = m_lBufferSize * blockNo;
	if(dwOffset < m_mbi.RegionSize)
	{
		//Set m_lBytesInBuffer to amount of data buffer will hold.
		m_lBytesInBuffer = m_mbi.RegionSize - dwOffset;
		if(m_lBytesInBuffer > m_lBufferSize)
			m_lBytesInBuffer = m_lBufferSize;
		lpAddress = (LPVOID)((DWORD)m_mbi.BaseAddress + dwOffset);
		ReadProcessMemory(
			m_hProcess,
			lpAddress,
			m_lpBuffer,
			m_lBytesInBuffer,
			&dwBytesRead);
		if(m_lBytesInBuffer == dwBytesRead) 
			return 1;
		if(dwBytesRead > 0)
			return -1;
	}
	return 0;
}
