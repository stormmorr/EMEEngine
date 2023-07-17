// TestSMDlg.h : header file
//

#if !defined(AFX_TESTSMDLG_H__EF764F27_5B9E_11D3_863D_00A0244A9CA7__INCLUDED_)
#define AFX_TESTSMDLG_H__EF764F27_5B9E_11D3_863D_00A0244A9CA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedMemory.h"
/////////////////////////////////////////////////////////////////////////////
// CTestSMDlg dialog

class CTestSMDlg : public CDialog
{
// Construction
public:
	CTestSMDlg(CWnd* pParent = NULL);	// standard constructor
	CSharedMemory	m_cSharedMemory;

// Dialog Data
	//{{AFX_DATA(CTestSMDlg)
	enum { IDD = IDD_TESTSM_DIALOG };
	CString	m_sWrite;
	CString	m_sRead;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSMDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestSMDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCreate();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonWrite();
	afx_msg void OnButtonRead();
	afx_msg void OnButtonWritetoqueue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSMDLG_H__EF764F27_5B9E_11D3_863D_00A0244A9CA7__INCLUDED_)
