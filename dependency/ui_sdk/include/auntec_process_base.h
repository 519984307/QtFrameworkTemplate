#ifndef __AUNTEC_PROCESS_BASE_H
#define __AUNTEC_PROCESS_BASE_H

#include "auntec_base_types.h"

#ifndef WIN32
#include <pthread.h>
#endif

namespace AuntecBased
{
	/*!
	@brief ��������
	*/
	class CAuntecBasedProcess
	{
	public:
		/*!
		@brief ��������
		@param cmdline ����������
		*/
		CAuntecBasedProcess(
#ifdef WIN32
			const wchar_t* cmdLine
#else
			const char* cmdLine
#endif
			);
		virtual ~CAuntecBasedProcess();

	public:
		/*!
		@brief �����Ƿ��ڶ�������ʱ�ȴ����̵Ľ���
		@param bWait �Ƿ�ȴ�
		@note Ĭ��Ϊ�ȴ����̽���
		*/
		void SetWaitWhenDestruct(bool bWait);

		/*!
		@brief ���н���
		@param bSuspend ����ʱ�Ƿ����
		@return �Ƿ�ɹ�����
		*/
		bool Run(bool bSuspend);

		/*!
		@brief ���н��̲��Ҳ���ʾ����
		@param bSuspend ����ʱ�Ƿ����
		@return �Ƿ�ɹ�����
		*/
		bool RunBackgroundly(bool bSuspend);

		/*!
		@brief �������
		*/
		void Suspend();

		/*!
		@brief �ָ�����Ľ���
		*/
		void Resume();

		/*!
		@brief �ȴ������˳�
		@details �����ֵȴ��Ľ��:
		- ��tʱ����, �����˳���, ��ʱWait�������ز��ҷ���ֵΪtrue
		- �ڳ�����tʱ��, ����û���˳�, ��ʱWait�������ز��ҷ���false
		- ��tΪ0xFFFFFFFFʱ����һֱ�ȵ������˳��ŷ���
		@param t �ȴ�ʱ��, ��λ����, 0xFFFFFFFF��ʾ�ȴ�ֱ�������˳�
		@return ���趨��ʱ���ڽ����˳�ʱ����true, ���򷵻�false	
		*/
		bool Wait(uint32_t t);

		/*!
		@brief ǿ����ֹ���̲����ý����˳���
		@param nCode �˳���
		@return �ɹ�����true, ʧ�ܷ���false
		*/
		bool Terminate(uint32_t nCode);

		/*!
		@brief ��ȡ�˳���
		@param nCode [OUT] �˳���
		@return �Ƿ�ɹ����, û�гɹ���ÿ����ǽ���û������������������û���˳�.
		*/
		bool GetExitCode(uint32_t& nCode);

		// ��ȡ���̾��
#ifdef WIN32
		HANDLE GetProcessHandle();
#endif

		// ��ȡ����ID
#ifdef __APPLE__
		int32_t GetProcesspId();
#endif

	private:
		/*!
		@brief ��������
		@param bBackgroundly �Ƿ���������
		@return �ɹ�����true, ʧ�ܷ���false
		*/
		bool RunInternal(bool bSuspend, bool bBackgroundly);
		/*!
		@brief �߳��������
		*/
#ifdef __APPLE__
		static void* ProcessLuanchThread(void* p);
		void LaunchProcess();
#endif

	private:
		bool m_bWaitWhenDestruct; ///< �ڶ�������ʱ�Ƿ�ȴ����̽���
#ifdef WIN32
		wchar_t* m_CmdLine; ///< ������
		HANDLE m_hProcess; ///< ���̾��
		HANDLE m_hThread; ///< ���̵����߳̾��
#else
		char* m_CmdLine; ///< ������
		pid_t volatile m_pid; ///< ���̱�ʶ
		pthread_t volatile m_LaunchThread; ///< �ȴ��������̵��߳�
		bool m_bSuspended;
		bool m_bBackgroundly;
		uint32_t m_ExitCode;
#endif
	};
}

#endif
