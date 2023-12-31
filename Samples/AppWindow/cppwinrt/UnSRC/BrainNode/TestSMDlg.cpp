// TestSMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestSM.h"
#include "TestSMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSMDlg dialog

CTestSMDlg::CTestSMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestSMDlg)
	m_sWrite = _T("");
	m_sRead = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSMDlg)
	DDX_Text(pDX, IDC_EDIT_WRITEVALUE, m_sWrite);
	DDX_Text(pDX, IDC_EDIT_READVALUE, m_sRead);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestSMDlg, CDialog)
	//{{AFX_MSG_MAP(CTestSMDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITETOQUEUE, OnButtonWritetoqueue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSMDlg message handlers

BOOL CTestSMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestSMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestSMDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestSMDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestSMDlg::OnButtonCreate() 
{
	m_cSharedMemory.Open("TestPool", 20);
}

void CTestSMDlg::OnButtonRemove() 
{
	m_cSharedMemory.Close();
}

void CTestSMDlg::OnButtonWrite() 
{
	UpdateData(true);

	switch(m_cSharedMemory.Write(m_sWrite.GetBuffer(1), 20, 5000))
	{
	case CSharedMemory::MEM_SUCCESS:
		break;
	case CSharedMemory::MEM_ERROR_CLOSED:
		AfxMessageBox("Not opened");
		break;
	case CSharedMemory::MEM_ERROR_TIMEOUT:
		AfxMessageBox("Timeout");
		break;
	case CSharedMemory::MEM_ERROR_OTHERPARTY:
		AfxMessageBox("Other party disconnected");
		m_cSharedMemory.Close();
		break;
	case CSharedMemory::MEM_ERROR_UNKNOWN:
		AfxMessageBox("Unknown");
		break;
	}
}

void CTestSMDlg::OnButtonWritetoqueue() 
{
	UpdateData(true);

	switch(m_cSharedMemory.WriteToQueue(m_sWrite.GetBuffer(1), 20))
	{
	case CSharedMemory::MEM_SUCCESS:
		break;
	case CSharedMemory::MEM_ERROR_CLOSED:
		AfxMessageBox("Not opened");
		break;
	case CSharedMemory::MEM_ERROR_OTHERPARTY:
		AfxMessageBox("Other party disconnected");
		m_cSharedMemory.Close();
		break;
	case CSharedMemory::MEM_ERROR_UNKNOWN:
		AfxMessageBox("Unknown");
		break;
	}
}

void CTestSMDlg::OnButtonRead() 
{
	char	sBuf[20];
	switch (m_cSharedMemory.Read(sBuf, 20, 5000))
	{
	case CSharedMemory::MEM_SUCCESS:
		m_sRead = sBuf;
		UpdateData(false);
		break;
	case CSharedMemory::MEM_ERROR_CLOSED:
		AfxMessageBox("Not opened");
		break;
	case CSharedMemory::MEM_ERROR_TIMEOUT:
		AfxMessageBox("Timeout");
		break;
	case CSharedMemory::MEM_ERROR_OTHERPARTY:
		AfxMessageBox("Other party disconnected");
		m_cSharedMemory.Close();
		break;
	case CSharedMemory::MEM_ERROR_UNKNOWN:
		AfxMessageBox("Unknown");
		break;
	}
}
