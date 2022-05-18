#define _LARGEFILE64_SOURCE
#include "auntec_thread_base.h"
#include <stdarg.h>
#include <string.h>
#include <iomanip>
#include <sys/stat.h>

#if defined(WIN32)
    #include <Windows.h>
    #include <process.h>
    #include <mmsystem.h>
    #include <objbase.h>
#else
    #include <dlfcn.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <limits.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/param.h>
    #include <sys/sysctl.h>
    #include <uuid/uuid.h>
    #include <unistd.h>
#endif

#ifdef __APPLE__
#include <mach/mach_time.h>
#include <mach-o/dyld.h>
#endif

#include "CBaseException.h"
#include "res_keeper.h"

#ifdef _MSC_VER
#pragma warning( disable : 4996)
#endif


namespace AuntecBased {

CAuntecBasedThread::CAuntecBasedThread()
{
    bool bSuspend = true;//make sure suspend the thread
    m_bThreadExists = true;
#ifdef WIN32
    uint32_t tid;
    uint32_t flag = 0;
    if (bSuspend) {
        flag = CREATE_SUSPENDED;
    }
    m_bSuspended = bSuspend;
    m_ThreadHandle = _beginthreadex(NULL, 0, ThreadProc, this, flag, &tid);
    if (m_ThreadHandle == NULL) {
        ThrowUnexpected();
    }
#else
    m_bSuspended = bSuspend;
    if (pthread_create(&m_ThreadHandle, NULL, ThreadProc, this) != 0) {
        ThrowUnexpected();
    }
#endif
}

CAuntecBasedThread::~CAuntecBasedThread()
{
#ifdef WIN32
    if (m_ThreadHandle != NULL) {
        if (m_bSuspended)
        {
            assert(m_ThreadHandle != NULL);
            ResumeThread((HANDLE)m_ThreadHandle);
        }
        Wait(INFINITE);
        CloseHandle((HANDLE)m_ThreadHandle);
        m_ThreadHandle = NULL;
    }
#else
    if (m_bThreadExists) {
        void* pExit=NULL;
       pthread_join(m_ThreadHandle, &pExit);
    }
#endif
}

void CAuntecBasedThread::Suspend()
{
    m_bSuspended = true;
#ifdef WIN32
    assert(m_ThreadHandle != NULL);
    SuspendThread((HANDLE)m_ThreadHandle);
#endif
}

void CAuntecBasedThread::Resume()
{
    m_bSuspended = false;
#ifdef WIN32
    assert(m_ThreadHandle != NULL);
    ResumeThread((HANDLE)m_ThreadHandle);
#endif
}

bool CAuntecBasedThread::Wait(uint32_t t)
{
#ifdef WIN32
    if (WaitForSingleObject((HANDLE)m_ThreadHandle, t) == WAIT_OBJECT_0) {
        return true;
    } else return false;
#else
    uint32_t ta=0;
    if (t != INFINITE) {
        while(m_bThreadExists) {
            if (ta >= t) {
                return !m_bThreadExists;
            }
            usleep(10000); //10ms
            ta += 10;
        }
        return true;
    } else {
        while(m_bThreadExists) {
            usleep(10000);
        }
        return true;
    }
#endif
}

bool CAuntecBasedThread::IsSuspended()
{
  return m_bSuspended;
}

bool CAuntecBasedThread::GetExitCode(uint32_t& nCode)
{
#ifdef WIN32
    if (m_bThreadExists) {
        return false;
    } else {
        return GetExitCodeThread((HANDLE)m_ThreadHandle, (LPDWORD)&nCode) != 0;
    }
#else
    if (m_bThreadExists) {
        return false;
    } else {
        nCode = m_ThreadExitCode;
        return true;
    }
#endif
}

#ifdef WIN32
uint32_t STDCALL CAuntecBasedThread::ThreadProc(void* p)
{
    CAuntecBasedThread* pThis = (CAuntecBasedThread*)p;
    assert(p != NULL);

    uint32_t nCode = (uint32_t)-1;
    if (!pThis->m_bSuspended)
    {
        try {
            nCode = pThis->Execute();
        } CatchAllAndCopy();
    }
    pThis->m_ThreadException.Copy(GetMoyeaException());
    FreeExp();
    pThis->m_bThreadExists = false;
    _endthreadex(nCode);
    return nCode;
}

uintptr_t CAuntecBasedThread::GetThreadHandle()
{
    return m_ThreadHandle;
}

#else
void* CAuntecBasedThread::ThreadProc(void* p)
{
    CAuntecBasedThread* pThis = (CAuntecBasedThread*)p;
    assert(p != NULL);

    while(pThis->IsSuspended()) {
        usleep(10000);
    }
    uint32_t nCode = (uint32_t)-1;
    try {
        nCode = pThis->Execute();
    } CatchAllAndCopy();
    pThis->m_ThreadExitCode = nCode;
    pThis->m_bThreadExists = false;
    pthread_exit(NULL);
    return NULL;
}

pthread_t CAuntecBasedThread::GetThreadHandle()
{
    return m_ThreadHandle;
}
#endif

}
