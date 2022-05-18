#ifndef __AUNTEC_THREAD_BASE_H
#define __AUNTEC_THREAD_BASE_H

#include "auntec_base_types.h"

#ifndef WIN32
#include <pthread.h>
#endif

namespace AuntecBased
{
	/*!
	@brief Auntec线程基类
	@details 该类自动初始化C运行库和线程异常对象,以及自动释放线程异常对象. 使用方法:
	- 从CAuntecBasedThread继承
	- 重写Execute函数, 当Execute函数返回时线程自动结束
	- 创建派生类对象
	- 使用Resume, Subspend, Wait等函数控制和同步线程
	*/
	class CAuntecBasedThread
	{
	public:
		/*!
		@brief 创建Auntec线程
		@detail 创建时一定是挂起了线程，需要使用Resume恢复挂起的线程
		*/
		CAuntecBasedThread();
		virtual ~CAuntecBasedThread();

	public:
		/*!
		@brief 挂起线程
		@note 在非Win32平台下这个函数仅仅设置IsSuspended标志，由派生类的Execute过程主动检测该标志而进行休眠
		*/
		void Suspend();

		/*!
		@brief 恢复挂起的线程
		@note 在非Win32平台下这个函数仅仅设置IsSuspended标志，由派生类的Execute过程主动检测该标志而进行苏醒
		*/
		void Resume();

		/*!
		@brief 等待线程退出
		@details 有两种等待的结果:
		- 在t时间内, 线程退出了, 此时Wait函数返回并且返回值为true
		- 在超出了t时间, 线程没能退出, 此时Wait函数返回并且返回false
		- 当t为0xFFFFFFFF时函数一直等到线程退出才返回
		@param t 等待时间, 单位毫秒, 0xFFFFFFFF表示等待直到线程退出
		@return 在设定的时间内线程退出时返回true, 否则返回false
		@note 不讲将线程挂起, 然后去进行等待, 这样如果没有其它线程解除该线程的挂起, 那么调用Wait的线程将死锁
		*/
		bool Wait(uint32_t t);

		/*!
		@brief 获取线程的退出码
		@param nCode [OUT] 接受退出码
		@return 当线程退出时返回true,并且nCode接收线程退出码, 线程未退出则返回false
		*/
		bool GetExitCode(uint32_t& nCode);

	protected:
		/*!
		@brief 由派生类实现的执行函数
		@return 线程的退出码
		*/
		virtual uint32_t Execute(void) = 0;

		/*!
		@brief 由派生类的Execute函数调用检测当前是否处于挂起状态
		*/
		bool IsSuspended();

		/*!
		@brief 由派生类的Execute函数调用获取当前线程句柄
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
		///线程是否处于挂起状态
		bool volatile m_bSuspended;
		///线程是否存在
		bool volatile m_bThreadExists; 
#ifdef WIN32
		uintptr_t m_ThreadHandle;
#else
		uint32_t m_ThreadExitCode; ///< 线程退出码
		pthread_t m_ThreadHandle;
#endif
	};
}

#endif
