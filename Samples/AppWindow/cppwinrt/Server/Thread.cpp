#include "Thread.h"
#include <algorithm>
#include <iostream>

#define	INTERNAL_LOCK		if (s_InternalThreadSynchronization.m_pMutex) \
							SDL_mutexP(s_InternalThreadSynchronization.m_pMutex);
#define	INTERNAL_UNLOCK		if (s_InternalThreadSynchronization.m_pMutex) \
							SDL_mutexV(s_InternalThreadSynchronization.m_pMutex);

/////////////////////////////////////////////////////////////////////////////
// CThread static members
std::list<CThread::THREAD_SYNCHRONICITY*> CThread::s_synchronicityList;
CThread::CInternalSynchronization CThread::s_InternalThreadSynchronization;
SDL_mutex * CThread::s_pProcessLockObject = 0;
std::string CThreadErrors::s_strERROR_THREAD_ALREADY_STARTED;
/////////////////////////////////////////////////////////////////////////////

CThreadErrors::CThreadErrors(CThread* pThread /*= NULL*/)
{
	m_pThread = pThread;
	m_strErrorMsg = "";
	m_nErrorType = CThreadErrors::UNKNOWN_ERROR;
}

CThread* CThreadErrors::GetThread() const
{
	return m_pThread;
}

void CThreadErrors::SetThread(CThread* pThread)
{
	m_pThread = pThread;
}

void CThreadErrors::SetErrorMsg(std::string strErrorMsg)
{
	m_strErrorMsg = strErrorMsg;
}

std::string CThreadErrors::GetErrorMsg() const
{
	return m_strErrorMsg;
}

void CThreadErrors::SetType(int nErrorType)
{
	m_nErrorType = nErrorType;
}

int CThreadErrors::GetType() const
{
	return m_nErrorType;
}

std::string CThreadErrors::GetLastSystemErrorMsg()
{
	std::string strErrMsg = SDL_GetError();
	return strErrMsg;
}
/////////////////////////////////////////////////////////////////////////////
CThread::CInternalSynchronization::CInternalSynchronization()
{
	CThread::ResetSynchronizationList();
	m_pMutex = SDL_CreateMutex();
}

CThread::CInternalSynchronization::~CInternalSynchronization()
{
	CThread::ResetSynchronizationList();
	SDL_DestroyMutex(m_pMutex);
}

/////////////////////////////////////////////////////////////////////////////

void CThread::OpenProcessLocking()
{
	if(!CThread::s_pProcessLockObject)
	{
		CThread::s_pProcessLockObject = SDL_CreateMutex();
	}
}

void CThread::ProcessLock()
{
	if (CThread::s_pProcessLockObject)
		SDL_mutexP(CThread::s_pProcessLockObject);
}

void CThread::ProcessUnlock()
{
	if (CThread::s_pProcessLockObject)
		SDL_mutexV(CThread::s_pProcessLockObject);
}

void CThread::CloseProcessLocking()
{
	if (CThread::s_pProcessLockObject)
	{
		SDL_DestroyMutex(CThread::s_pProcessLockObject);
		CThread::s_pProcessLockObject = NULL;
	};
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Worker Thread Class implementation ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CThread::CThread(void* pOwnerObject, icThreadData *pData)
{
	m_pOwnerObject = pOwnerObject;
	m_pData	= pData;
	m_bIsSynchronized = false;
	m_bSupportSignalNotification = false;
	m_pCurrentRuntimeSynchronizationObject = 0;
	m_pSDLCond = 0;
	m_strThreadHandlerClassName	= "";
	ResetThreadRuntimeData();
}

CThread::~CThread()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	UnregisterNotificationObject();
	ResetThreadRuntimeData();
	// Unlock ///////////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////////
}

void CThread::SetOwnerParams(void* pOwnerObject, icThreadData *pData)
{
	m_pOwnerObject = pOwnerObject;
	m_pData	= pData;
}

void CThread::GetOwnerParams(void *& pOwnerObject, icThreadData *& pData) const
{
	pOwnerObject = m_pOwnerObject;
	pData = m_pData;
}

void CThread::ResetThreadRuntimeData()
{
	m_pSDLThread = 0;
	m_dwThreadID = 0;
	m_nActivityStatus = CThread::THREAD_STOPPED;
	m_pCurrentRuntimeSynchronizationObject = 0;
	m_nCommandList.clear();
}

void CThread::ResetThreadObject()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	UnregisterRuntimeSynchronization();
	ResetThreadRuntimeData();
	// Unlock ///////////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CThread Attributes and Operations

// Exact-Class specific Synchronization helper methods
void CThread::ResetSynchronizationList()
{
	if (CThread::s_synchronicityList.size() > 0)
	{
		typedef std::list<THREAD_SYNCHRONICITY*> LIST;

		LIST::iterator i;

		for (i = CThread::s_synchronicityList.begin(); i != CThread::s_synchronicityList.end(); ++i)
        {
			if ((*i)->pCriticalSection)
			{
				SDL_DestroyMutex((*i)->pCriticalSection);
			}
			delete (THREAD_SYNCHRONICITY*)(*i);
		}
		CThread::s_synchronicityList.clear();
	}
}

void CThread::ResetSynchronizationObject(THREAD_SYNCHRONICITY& synchronizationObject)
{
	synchronizationObject.strThreadHandlerClassName	= "";
	synchronizationObject.pCriticalSection = 0;
	synchronizationObject.dwCountOfRunningThreads = 0;
}

void CThread::UpdateRuntimeSynchronizationObject(THREAD_SYNCHRONICITY& synchronizationObject)
{
	std::replace(CThread::s_synchronicityList.begin(), CThread::s_synchronicityList.end(), m_pCurrentRuntimeSynchronizationObject, &synchronizationObject);
}

void CThread::DeleteRuntimeSynchronizationObject()
{
	CThread::s_synchronicityList.remove(m_pCurrentRuntimeSynchronizationObject);
	delete m_pCurrentRuntimeSynchronizationObject;
}

bool CThread::FindRuntimeSynchronizationObject()
{
	typedef std::list<THREAD_SYNCHRONICITY*> LIST;

	LIST::iterator i;

	for (i = CThread::s_synchronicityList.begin(); i != CThread::s_synchronicityList.end(); ++i)
    {
		if((*i)->strThreadHandlerClassName == m_strThreadHandlerClassName)
		{
			m_pCurrentRuntimeSynchronizationObject = *i;
			return true;
		}
	}

	return false;
}

CThread::THREAD_SYNCHRONICITY * CThread::GetRuntimeSynchronizationObject()
{
	return m_pCurrentRuntimeSynchronizationObject;
}

void CThread::RegisterRuntimeSynchronization()
{
	if (m_bIsSynchronized)
	{
		THREAD_SYNCHRONICITY * runtimeSynchronizationObject;

		if (!FindRuntimeSynchronizationObject())
		{
			runtimeSynchronizationObject = new THREAD_SYNCHRONICITY;
			ResetSynchronizationObject(*runtimeSynchronizationObject);
			runtimeSynchronizationObject->strThreadHandlerClassName = m_strThreadHandlerClassName;
			runtimeSynchronizationObject->dwCountOfRunningThreads++;
			runtimeSynchronizationObject->pCriticalSection = SDL_CreateMutex();
			CThread::s_synchronicityList.push_back(runtimeSynchronizationObject);
			m_pCurrentRuntimeSynchronizationObject = runtimeSynchronizationObject;
		}
		else
		{
			runtimeSynchronizationObject = GetRuntimeSynchronizationObject();
			runtimeSynchronizationObject->dwCountOfRunningThreads++;
			UpdateRuntimeSynchronizationObject(*runtimeSynchronizationObject);
		}
	}
}

void CThread::UnregisterRuntimeSynchronization()
{
	if (m_bIsSynchronized)
	{
		if (m_pCurrentRuntimeSynchronizationObject)
		{
			THREAD_SYNCHRONICITY * runtimeSynchronizationObject;
			runtimeSynchronizationObject = GetRuntimeSynchronizationObject();

			if (runtimeSynchronizationObject->dwCountOfRunningThreads > 1)
			{
				runtimeSynchronizationObject->dwCountOfRunningThreads--;
				UpdateRuntimeSynchronizationObject(*runtimeSynchronizationObject);
			}
			else
			{
				SDL_DestroyMutex(runtimeSynchronizationObject->pCriticalSection);
				DeleteRuntimeSynchronizationObject();
				m_pCurrentRuntimeSynchronizationObject = 0;
			}
		}
	}
}
void CThread::Lock()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_bIsSynchronized && m_pCurrentRuntimeSynchronizationObject)
	{
		THREAD_SYNCHRONICITY * runtimeSynchronizationObject = GetRuntimeSynchronizationObject();
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		SDL_mutexP(runtimeSynchronizationObject->pCriticalSection);
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	};
}

void CThread::Unlock()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_bIsSynchronized && m_pCurrentRuntimeSynchronizationObject)
	{
		THREAD_SYNCHRONICITY * runtimeSynchronizationObject = GetRuntimeSynchronizationObject();
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		SDL_mutexV(runtimeSynchronizationObject->pCriticalSection);
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	}
}

SDL_Thread * CThread::GetHandle() const
{
	return m_pSDLThread;
}

int CThread::GetID() const
{
	return m_dwThreadID;
}

void CThread::SetActivityStatus(int nActivityStatus)
{
	m_nActivityStatus = nActivityStatus;
}

int CThread::GetActivityStatus() const
{
	return m_nActivityStatus;
}

bool CThread::WaitForActivityStatus(int nActivityStatus, int dwTimeout) const
{
	int dwCount = 0, dwMaxCount = 0;
	dwMaxCount = (dwTimeout * 100) / CThread::BASE_DELAY_INTERVAL;

	while (m_nActivityStatus != nActivityStatus	&&
		   m_pSDLThread &&
		   (dwTimeout == CThread::DW_INFINITE || dwCount++ < dwMaxCount))
	{
		SDL_Delay(CThread::BASE_DELAY_INTERVAL);
	};

	return (m_nActivityStatus == nActivityStatus);
}


bool CThread::PostThreadCommand(int nCommand, std::string& strError)
{
	//strError.clear();
	if (m_bSupportSignalNotification &&	m_pSDLCond && nCommand != CThread::CMD_NONE)
	{
		if (m_nCommandList.size() > 0 &&
			m_nCommandList[m_nCommandList.size() - 1] == nCommand)
			return true;

		m_nCommandList.push_back(nCommand);
		if (SDL_CondSignal(m_pSDLCond))
		{
			//strError = CThreadErrors::GetLastSystemErrorMsg();
			return true;
		}
		else
			return true;
	}
	else
		return true;
}

void CThread::PostCommand(int nCommand)
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	std::string strError;
	if (m_pSDLThread && !PostThreadCommand(nCommand, strError))
	{
		//std::cout << strError;
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
	}
}

void CThread::ResetCommands()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	m_nCommandList.clear();
	// Unlock ///////////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////////
}

bool CThread::HandleCommandImmediately(int nCommand)
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_pSDLThread && m_bSupportSignalNotification && nCommand != CMD_NONE)
	{
		m_nCommandList.insert(m_nCommandList.begin(), nCommand);
		// Unlock ///////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////
		return false;
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return false;
	}
}

bool CThread::ReceiveCommand(int& nIncomingCommand)
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	nIncomingCommand = CThread::CMD_NONE;
	if (m_bSupportSignalNotification && m_pSDLCond)
	{
		if (m_nCommandList.size() > 0)
		{
			nIncomingCommand = m_nCommandList[0];
			m_nCommandList.erase(m_nCommandList.begin());
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return true;
		}
		else
		{
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return false;
		}
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////////
		return false;
	};
}

bool CThread::RegisterNotificationObject(std::string& strError)
{
	if (m_bSupportSignalNotification && !m_pSDLCond)
	{
		if ((m_pSDLCond = SDL_CreateCond()) == 0)
		{
			strError = CThreadErrors::GetLastSystemErrorMsg();
			return false;
		}
		else
			return true;
	}
	else
		return true;
}

void CThread::UnregisterNotificationObject()
{
	if (m_bSupportSignalNotification && m_pSDLCond)
	{
		SDL_DestroyCond(m_pSDLCond);
		m_pSDLCond = 0;
	}
}

void CThread::WaitForNotification(int& nIncomingCommand, int dwDefaultTimeout)
{
	if (m_bSupportSignalNotification && m_pSDLCond)
	{
		int dwEvent;
		bool bExit = false;

		do
		{
			if (!ReceiveCommand(nIncomingCommand))
			{
				dwEvent = SDL_CondWaitTimeout(m_pSDLCond, m_pCurrentRuntimeSynchronizationObject->pCriticalSection, dwDefaultTimeout);

				switch (dwEvent)
				{
				case 0:
					break;

				case SDL_MUTEX_TIMEDOUT:
					nIncomingCommand = CThread::CMD_TIMEOUT_ELAPSED;
					bExit = true;
					break;

				default:
					break;
				}
			}
			else
				break;
		} while (!bExit);
	}
	else
		nIncomingCommand = CThread::CMD_NONE;
}

void CThread::Run()
{
	PostCommand(CThread::CMD_RUN);
}

void CThread::Pause()
{
	PostCommand(CThread::CMD_PAUSE);
}

void CThread::Continue()
{
	PostCommand(CThread::CMD_CONTINUE);
}

void CThread::Reset()
{
	PostCommand(CThread::CMD_RESET);
}

int CThread::ControllingFunction(void * lpParameter)
{
	int dwExitCode = ((CThread *)lpParameter)->ThreadHandler();
	((CThread *)lpParameter)->ResetThreadObject();
	return dwExitCode;
}
/////////////////////////////////////////////////////////////////////////////

void CThread::Start()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	std::string strError;

	ResetThreadRuntimeData();

	if (!RegisterNotificationObject(strError))
	{
		//std::cout << strError;
		// Unlock ///////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////
		return;
	}

	RegisterRuntimeSynchronization();
	m_pSDLThread = SDL_CreateThread(ControllingFunction, this);
	if (m_pSDLThread)
	{
		if (!PostThreadCommand(CThread::CMD_INITIALIZE, strError))
		{
			SDL_KillThread(m_pSDLThread);
			UnregisterRuntimeSynchronization();
			ResetThreadRuntimeData();
			//std::cout << strError;
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
		}
		else
		{
			SetActivityStatus(CThread::THREAD_CREATED);
			// Unlock ///////////////////////////////////////////////////////
			INTERNAL_UNLOCK
			/////////////////////////////////////////////////////////////////
			return;
		}
	}
	else
	{
		//strError = CThreadErrors::GetLastSystemErrorMsg();
		//std::cout << strError;
		// Unlock ///////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////
	}
}

bool CThread::Stop(int& status)
{

	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	std::string strError;
	if (!PostThreadCommand(CThread::CMD_STOP, strError))
	{
		std::cout << strError;
		// Unlock ///////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////
	}
	else
	{
		// Unlock ///////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////
	}

	SDL_WaitThread(m_pSDLThread, &status);
	// Lock /////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////
	if (m_pSDLThread)
		UnregisterRuntimeSynchronization();
	
	ResetThreadRuntimeData();
	// Unlock ///////////////////////////////////////////////////////////
	INTERNAL_UNLOCK
	/////////////////////////////////////////////////////////////////////
	return true;
}


void CThread::OnKill()
{
	// Does nothing by default //////////////////////////////////////////////
}

void CThread::Kill()
{
	// Lock /////////////////////////////////////////////////////////////////
	INTERNAL_LOCK
	/////////////////////////////////////////////////////////////////////////
	if (m_pSDLThread)
	{
		SDL_KillThread(m_pSDLThread);
		UnregisterRuntimeSynchronization();
		ResetThreadRuntimeData();

		// Do necessary cleanup after the thread has been actually destroyed
		OnKill();
		// Unlock ///////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////
	}
	else
	{
		ResetThreadRuntimeData();
		// Unlock ///////////////////////////////////////////////////////
		INTERNAL_UNLOCK
		/////////////////////////////////////////////////////////////////
	}	
}

