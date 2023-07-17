#ifndef _THREAD_H_
#define _THREAD_H_

#include <SDL.h>
#include <SDL_thread.h>
#include <vector>
#include <string>
#include <list>
#include "ThreadData.h"

class unMutexCC
{
public:
	unMutexCC()
		{
		mBlock = false;
		mFired = false;
		}
	~unMutexCC() {};
	
	bool mBlock;
	bool mFired;

	void ac_Fire(void)
		{
		while(mFired)
			{
			/*wait*/
			int f_XY = 50;
			}

		mFired = true;
		}

	void ac_Free(void)
		{
		mFired = false;
		}
};

// Internal CThread Interface macros ////////////////////////////////////////
#define	SUPPORT_THREAD_SYNCHRONIZATION(ClassName)	m_strThreadHandlerClassName = #ClassName; \
													m_bIsSynchronized = true;
#define	SUPPORT_THREAD_NOTIFICATION					m_bSupportSignalNotification = true;
/////////////////////////////////////////////////////////////////////////////

class CThread;

class CThreadErrors
{
public:
	//SERVER EDIT
	/*static*/ enum {UNKNOWN_ERROR	= 0,
				 CANNOT_CREATE_THREAD = 1,
				 THREAD_ALREADY_STARTED = 2,
				 CANNOT_TERMINATE_THREAD = 3,
				 CANNOT_CREATE_NOTIFICATION_OBJECT = 4,
				 CANNOT_SIGNAL_NOTIFICATION_OBJECT = 5};

//	Default error message texts
	static std::string s_strERROR_THREAD_ALREADY_STARTED;

	CThreadErrors(CThread* pThread = 0);
	CThread * GetThread() const;
	std::string	GetErrorMsg() const;
	int	GetType() const;
	static std::string GetLastSystemErrorMsg();

	//virtual int	ReportError(int nType, int nMessageID = 0);

// Attributes & Operations & Overridables
protected:
	CThread * m_pThread;
	std::string	m_strErrorMsg;
	int m_nErrorType;

	void SetThread(CThread* pThread);
	void SetErrorMsg(std::string strErrorMsg);
	void SetType(int nType);
};


class CThread
{
public:
	//SERVER EDIT
	/*static*/ enum {DW_OK					= 0x00000000,
				 DW_ERROR				= 0xFFFFFFFF,
				 DW_UNDEFINED			= 0xFFFFFFFE,
				 DW_TIMEOUT_ELAPSED		= 0xFFFFFFFD,
				 DW_INFINITE			= 0xFFFFFFFF,
				 THREAD_CREATED			= 0,
				 THREAD_STOPPED			= 1,
				 THREAD_RUNNING			= 2,
				 THREAD_PAUSED			= 3,
				 THREAD_CONTINUING		= 4,
				 THREAD_PENDING			= 5,
				 THREAD_USER_ACTIVITY	= 6};

	CThread(void* pOwnerObject = 0, icThreadData * data = 0);
	virtual ~CThread();


	SDL_Thread *GetHandle() const;
	int	GetID() const;
	int	GetActivityStatus() const;
	void	Start();
	void	Run();
	void	Pause();
	void	Continue();
	void	Reset();
	bool	Stop(int &status);
	
	void	Kill();
	void	PostCommand(int nCommand);
	void	ResetCommands();
	void	SetOwnerParams(void* pOwnerObject, icThreadData *pData = 0);
	void	GetOwnerParams( void *& pOwnerObject, icThreadData *& pData) const;
	bool	WaitForActivityStatus(int nActivityStatus, int dwTimeout = CThread::DW_INFINITE) const;
	static void OpenProcessLocking();
	static void CloseProcessLocking();
	static void ProcessLock();
	static void ProcessUnlock();
	static int ControllingFunction(void * lpParameter);
// Attributes
protected:
	//SERVER EDIT
	/*static*/ enum {CMD_NONE					= 0,
				 CMD_TIMEOUT_ELAPSED		= 1,
				 CMD_INITIALIZE				= 2,
				 CMD_RUN					= 3,
				 CMD_PAUSE					= 4,
				 CMD_CONTINUE				= 5,
				 CMD_RESET					= 6,
				 CMD_STOP					= 7,
				 CMD_USER_COMMAND			= 8,
				 BASE_DELAY_INTERVAL		= 100};

	bool m_bSupportSignalNotification;
	bool m_bIsSynchronized;
	std::string	m_strThreadHandlerClassName;

// Operations
protected:
	void SetActivityStatus(int nActivityStatus);
	void Lock();
	void Unlock();
	void WaitForNotification(int & nIncomingCommand, int dwDefaultTimeout = CThread::DW_INFINITE);
	bool HandleCommandImmediately(int nCommand);

// Overridables
protected:
	// Main virtual Thread task method implemented in CThread-derived classes...
	// The only method that must be implemented in some CThread-derived class.
	/////////////////////////////////////////////////////////////////////////////
	virtual int ThreadHandler() = 0;
	virtual void OnKill();
private:
	class CInternalSynchronization
	{
	public:
		CInternalSynchronization();
		~CInternalSynchronization();
		//SDL_mutex *m_pMutex;
	};

	friend class CInternalSynchronization;

	typedef struct _THREAD_SYNCHRONICITY_TAG
	{
		std::string strThreadHandlerClassName;
		//SDL_mutex *	pCriticalSection;
		long dwCountOfRunningThreads;
	} THREAD_SYNCHRONICITY;

	static	std::list<THREAD_SYNCHRONICITY*> s_synchronicityList;
	static	CInternalSynchronization s_InternalThreadSynchronization;
	static	void ResetSynchronizationList();
	//static	//SDL_mutex * s_pProcessLockObject;
	
	THREAD_SYNCHRONICITY * m_pCurrentRuntimeSynchronizationObject;
	SDL_Thread * m_pSDLThread;
	SDL_cond * m_pSDLCond;
	int	m_dwThreadID;
	long m_dwStackSize;
	int	m_dwThreadExitCode;
	volatile int m_nActivityStatus;
	void * m_pOwnerObject;
	icThreadData *m_pData;
	std::vector<int> m_nCommandList;

	bool RegisterNotificationObject(std::string& strError);
	void UnregisterNotificationObject();
	bool PostThreadCommand(int nCommand, std::string& strError);
	bool ReceiveCommand(int& nIncomingCommand);
	void ResetThreadObject();

	void ResetThreadRuntimeData();
	void ResetSynchronizationObject(THREAD_SYNCHRONICITY& synchronizingObject);
	void RegisterRuntimeSynchronization();
	void UnregisterRuntimeSynchronization();
	void UpdateRuntimeSynchronizationObject(THREAD_SYNCHRONICITY& synchronizingObject);
	void DeleteRuntimeSynchronizationObject();
	bool FindRuntimeSynchronizationObject();
	THREAD_SYNCHRONICITY * GetRuntimeSynchronizationObject();
};

#endif