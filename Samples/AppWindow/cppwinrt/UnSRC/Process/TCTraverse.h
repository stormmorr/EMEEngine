// TCTraverse.h: interface for the TCTraverse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCTRAVERSE_H__203E49B0_16DE_4393_B70D_553CDF08C146__INCLUDED_)
#define AFX_TCTRAVERSE_H__203E49B0_16DE_4393_B70D_553CDF08C146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TCTraverse  
{
private:
	HANDLE m_hProcess;
	MEMORY_BASIC_INFORMATION m_mbi;
public:
	LPVOID	m_lpBuffer;
	long m_lBufferSize;
	long m_lBytesInBuffer;
	int mLoad(int blockNo);
	TCTraverse();
	virtual ~TCTraverse();
	int mInit(HANDLE hProcess, MEMORY_BASIC_INFORMATION &mbi, long lBufferSize);
};

#endif // !defined(AFX_TCTRAVERSE_H__203E49B0_16DE_4393_B70D_553CDF08C146__INCLUDED_)
