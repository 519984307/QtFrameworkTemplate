#ifndef __AUNTEC_PROCESS_BASE_H
#define __AUNTEC_PROCESS_BASE_H

#include "auntec_base_types.h"

#ifndef WIN32
#include <pthread.h>
#endif

namespace AuntecBased
{
	/*!
	@brief 创建进程
	*/
	class CAuntecBasedProcess
	{
	public:
		/*!
		@brief 创建进程
		@param cmdline 进程命令行
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
		@brief 设置是否在对象析构时等待进程的结束
		@param bWait 是否等待
		@note 默认为等待进程结束
		*/
		void SetWaitWhenDestruct(bool bWait);

		/*!
		@brief 运行进程
		@param bSuspend 运行时是否挂起
		@return 是否成功启动
		*/
		bool Run(bool bSuspend);

		/*!
		@brief 运行进程并且不显示窗体
		@param bSuspend 运行时是否挂起
		@return 是否成功启动
		*/
		bool RunBackgroundly(bool bSuspend);

		/*!
		@brief 挂起进程
		*/
		void Suspend();

		/*!
		@brief 恢复挂起的进程
		*/
		void Resume();

		/*!
		@brief 等待进程退出
		@details 有两种等待的结果:
		- 在t时间内, 进程退出了, 此时Wait函数返回并且返回值为true
		- 在超出了t时间, 进程没能退出, 此时Wait函数返回并且返回false
		- 当t为0xFFFFFFFF时函数一直等到进程退出才返回
		@param t 等待时间, 单位毫秒, 0xFFFFFFFF表示等待直到进程退出
		@return 在设定的时间内进程退出时返回true, 否则返回false	
		*/
		bool Wait(uint32_t t);

		/*!
		@brief 强行终止进程并设置进程退出码
		@param nCode 退出码
		@return 成功返回true, 失败返回false
		*/
		bool Terminate(uint32_t nCode);

		/*!
		@brief 获取退出码
		@param nCode [OUT] 退出码
		@return 是否成功获得, 没有成功获得可能是进程没有启动过或者启动了没有退出.
		*/
		bool GetExitCode(uint32_t& nCode);

		// 获取进程句柄
#ifdef WIN32
		HANDLE GetProcessHandle();
#endif

		// 获取进程ID
#ifdef __APPLE__
		int32_t GetProcesspId();
#endif

	private:
		/*!
		@brief 启动进程
		@param bBackgroundly 是否隐藏启动
		@return 成功返回true, 失败返回false
		*/
		bool RunInternal(bool bSuspend, bool bBackgroundly);
		/*!
		@brief 线程启动入口
		*/
#ifdef __APPLE__
		static void* ProcessLuanchThread(void* p);
		void LaunchProcess();
#endif

	private:
		bool m_bWaitWhenDestruct; ///< 在对象析构时是否等待进程结束
#ifdef WIN32
		wchar_t* m_CmdLine; ///< 命令行
		HANDLE m_hProcess; ///< 进程句柄
		HANDLE m_hThread; ///< 进程的主线程句柄
#else
		char* m_CmdLine; ///< 命令行
		pid_t volatile m_pid; ///< 进程标识
		pthread_t volatile m_LaunchThread; ///< 等待启动进程的线程
		bool m_bSuspended;
		bool m_bBackgroundly;
		uint32_t m_ExitCode;
#endif
	};
}

#endif
