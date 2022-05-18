#ifndef __AUNTEC_THREAD_BASE_H
#define __AUNTEC_THREAD_BASE_H

#include "auntec_base_types.h"

#ifndef WIN32
#include <pthread.h>
#endif

namespace AuntecBased
{
	/*!
	@brief Auntec�̻߳���
	@details �����Զ���ʼ��C���п���߳��쳣����,�Լ��Զ��ͷ��߳��쳣����. ʹ�÷���:
	- ��CAuntecBasedThread�̳�
	- ��дExecute����, ��Execute��������ʱ�߳��Զ�����
	- �������������
	- ʹ��Resume, Subspend, Wait�Ⱥ������ƺ�ͬ���߳�
	*/
	class CAuntecBasedThread
	{
	public:
		/*!
		@brief ����Auntec�߳�
		@detail ����ʱһ���ǹ������̣߳���Ҫʹ��Resume�ָ�������߳�
		*/
		CAuntecBasedThread();
		virtual ~CAuntecBasedThread();

	public:
		/*!
		@brief �����߳�
		@note �ڷ�Win32ƽ̨�����������������IsSuspended��־�����������Execute�����������ñ�־����������
		*/
		void Suspend();

		/*!
		@brief �ָ�������߳�
		@note �ڷ�Win32ƽ̨�����������������IsSuspended��־�����������Execute�����������ñ�־����������
		*/
		void Resume();

		/*!
		@brief �ȴ��߳��˳�
		@details �����ֵȴ��Ľ��:
		- ��tʱ����, �߳��˳���, ��ʱWait�������ز��ҷ���ֵΪtrue
		- �ڳ�����tʱ��, �߳�û���˳�, ��ʱWait�������ز��ҷ���false
		- ��tΪ0xFFFFFFFFʱ����һֱ�ȵ��߳��˳��ŷ���
		@param t �ȴ�ʱ��, ��λ����, 0xFFFFFFFF��ʾ�ȴ�ֱ���߳��˳�
		@return ���趨��ʱ�����߳��˳�ʱ����true, ���򷵻�false
		@note �������̹߳���, Ȼ��ȥ���еȴ�, �������û�������߳̽�����̵߳Ĺ���, ��ô����Wait���߳̽�����
		*/
		bool Wait(uint32_t t);

		/*!
		@brief ��ȡ�̵߳��˳���
		@param nCode [OUT] �����˳���
		@return ���߳��˳�ʱ����true,����nCode�����߳��˳���, �߳�δ�˳��򷵻�false
		*/
		bool GetExitCode(uint32_t& nCode);

	protected:
		/*!
		@brief ��������ʵ�ֵ�ִ�к���
		@return �̵߳��˳���
		*/
		virtual uint32_t Execute(void) = 0;

		/*!
		@brief ���������Execute�������ü�⵱ǰ�Ƿ��ڹ���״̬
		*/
		bool IsSuspended();

		/*!
		@brief ���������Execute�������û�ȡ��ǰ�߳̾��
		*/
#ifdef WIN32
		uintptr_t GetThreadHandle();
#else 
		pthread_t GetThreadHandle();
#endif

	private:
#ifdef WIN32
		static uint32_t STDCALL ThreadProc(void* p);
#else
		static void* ThreadProc(void* p);
#endif

	private:
		///�߳��Ƿ��ڹ���״̬
		bool volatile m_bSuspended;
		///�߳��Ƿ����
		bool volatile m_bThreadExists; 
#ifdef WIN32
		uintptr_t m_ThreadHandle;
#else
		uint32_t m_ThreadExitCode; ///< �߳��˳���
		pthread_t m_ThreadHandle;
#endif
	};
}

#endif
