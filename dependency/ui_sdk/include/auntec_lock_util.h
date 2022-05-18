#ifndef __AUNTEC_LOCK_UTIL_H
#define __AUNTEC_LOCK_UTIL_H

#include "auntec_base_types.h"

#ifndef WIN32
#include <pthread.h>
#endif

namespace AuntecBased
{
	/*!
	@brief 初始化临界区
	*/
	void* auntec_init_critical(void);

	/*!
	@brief 删除临界区
	*/
	void auntec_delete_critical(void* pCritical);

	/*!
	@brief 进入临界区
	*/
	void auntec_enter_critical(void* pCritical);

	/*!
	@brief 离开临界区
	*/
	void auntec_leave_critical(void* pCritical);

	/*! 
	@brief 互斥锁
	*/
	class CXAuntecMutex
	{
	public:
		CXAuntecMutex();
		virtual ~CXAuntecMutex();

	public:
		bool Lock(uint32_t dwTimeoutMilliseconds = INFINITE);
		bool Unlock();

	private:
		CXAuntecMutex(const CXAuntecMutex&);
		CXAuntecMutex& operator=(const CXAuntecMutex&);

	private:
#ifdef WIN32
		HANDLE m_hMutex;
#else
		bool m_bOk;
		pthread_mutex_t m_hMutex;
		pthread_mutexattr_t m_Attr;
#endif
	};

	/*!
	@brief 事件对象, 作用与Windows Event相同
	@details 事件对象有两个状态, true/false, 在false状态下Wait(INFINITE)将锁住线程等到Set发生才返回
	*/
	class CXAuntecEvent
	{
	public:
		CXAuntecEvent(bool bAutoReset, bool bInitialState);
		~CXAuntecEvent();

	public:
		void Set();
		void Reset();
		bool Wait(uint32_t msTimeout);

	private:
		CXAuntecEvent(const CXAuntecEvent&) {};
		CXAuntecEvent& operator=(const CXAuntecEvent&) {};

	private:
		bool m_bAutoReset; ///< 是否自动重置
#ifdef WIN32
		HANDLE m_hEvent; ///< WIN32事件句柄
#else
		bool m_bOk;
		bool m_bState; ///< 状态
		pthread_mutex_t m_mutex; ///< pthread互斥量
		pthread_cond_t m_cond; ///< pthread条件变量
#endif
	};

	/*!
	@brief 临界区自动锁
	*/
	class CAuntecCriticalAutoLock
	{
	public:
		CAuntecCriticalAutoLock(void* pCritical);
		~CAuntecCriticalAutoLock();

	private:
		CAuntecCriticalAutoLock(const CAuntecCriticalAutoLock& lock);
		CAuntecCriticalAutoLock& operator = (const CAuntecCriticalAutoLock& lock);

	private:
		void* m_pCritical;
	};

	/*!
	@brief CXMutex自动琐
	*/
	class CXAuntecMutexAutoLock  
	{
	public:
		CXAuntecMutexAutoLock(CXAuntecMutex* pXMutex);
		~CXAuntecMutexAutoLock();

	private:
		CXAuntecMutexAutoLock(const CXAuntecMutexAutoLock&);
		CXAuntecMutexAutoLock& operator=(const CXAuntecMutexAutoLock&);

	private:
		CXAuntecMutex* m_pXMutex;
	};
}

#endif
