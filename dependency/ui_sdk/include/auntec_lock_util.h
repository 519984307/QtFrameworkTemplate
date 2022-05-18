#ifndef __AUNTEC_LOCK_UTIL_H
#define __AUNTEC_LOCK_UTIL_H

#include "auntec_base_types.h"

#ifndef WIN32
#include <pthread.h>
#endif

namespace AuntecBased
{
	/*!
	@brief ��ʼ���ٽ���
	*/
	void* auntec_init_critical(void);

	/*!
	@brief ɾ���ٽ���
	*/
	void auntec_delete_critical(void* pCritical);

	/*!
	@brief �����ٽ���
	*/
	void auntec_enter_critical(void* pCritical);

	/*!
	@brief �뿪�ٽ���
	*/
	void auntec_leave_critical(void* pCritical);

	/*! 
	@brief ������
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
	@brief �¼�����, ������Windows Event��ͬ
	@details �¼�����������״̬, true/false, ��false״̬��Wait(INFINITE)����ס�̵߳ȵ�Set�����ŷ���
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
		bool m_bAutoReset; ///< �Ƿ��Զ�����
#ifdef WIN32
		HANDLE m_hEvent; ///< WIN32�¼����
#else
		bool m_bOk;
		bool m_bState; ///< ״̬
		pthread_mutex_t m_mutex; ///< pthread������
		pthread_cond_t m_cond; ///< pthread��������
#endif
	};

	/*!
	@brief �ٽ����Զ���
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
	@brief CXMutex�Զ���
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
