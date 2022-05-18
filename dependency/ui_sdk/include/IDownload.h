#ifndef AUNTEC_DOWNLOAD_MANAGER_H__
#define AUNTEC_DOWNLOAD_MANAGER_H__

#include "auntec_base_types.h"

// 下载器工作状态
#define DOWNLOAD_STATE_WAIT 0 // 等待
#define DOWNLOAD_STATE_RUN 1 // 运行中
#define DOWNLOAD_STATE_PAUSE 2 // 暂停
#define DOWNLOAD_STATE_STOP 3 // 用户取消
#define DOWNLOAD_STATE_COMPLETE 4 // 完成
#define DOWNLOAD_STATE_ERROR 5 // 错误


// 下载器错误返回值 wynn
#define DOWNLOAD_ERROR_NORMAL					0   // 成功
#define DOWNLOAD_ERROR_DNS					   -1   // DNS解析失败
#define DOWNLOAD_ERROR_SOCKET				   -2   // Socket创建失败
#define DOWNLOAD_ERROR_NETWORK				   -3   // 网络通信失败
#define DOWNLOAD_ERROR_GETURL				   -4   // 获取URL失败
#define DOWNLOAD_ERROR_EXCEPT				   -5   // 其他异常
/*!
@brief 下载器接口
*/
class IDownload
{
public:
	/*!
	@brief 启动下载
	*/
	virtual bool STDCALL Start() = 0;

	/*!
	@brief 暂停下载
	@note 未实现
	*/
	virtual bool STDCALL Pause() = 0;

	/*!
	@brief 恢复下载
	@note 未实现
	*/
	virtual bool STDCALL Resume() = 0;

	/*!
	@brief 取消下载
	*/
	virtual bool STDCALL Stop() = 0;

	/*!
	@brief 获取下载进度
	*/
	virtual int STDCALL Percent() = 0;

	/*!
	@brief 获取下载状态THREAD_STATE_...
	*/
	virtual int STDCALL State() = 0;

	/*!
	@brief 获取下载错误类型 DOWNLOAD_ERROR_...
	*/
	virtual int STDCALL Error() = 0;

	/*!
	@brief 释放
	*/
	virtual void STDCALL Free() = 0;
};

/*!
@brief 创建下载器
@param url 下载地址
@param filePath 本地缓存路径
@param threadCount 下载线程数
@param timeOut 单次网络连接超时时长
@param errLoopTimes 失败重试次数
@return 成功返回下载接口，否则返回NULL
*/
extern "C"
EXPORT
IDownload* CreateDownloader
												(
												const char* url,
												const char* filePath,
												int threadCount=4,
												int timeOut=5000,
												int errLoopTimes=1000
												);

#endif