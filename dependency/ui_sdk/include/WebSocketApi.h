/********************************************************************
	fileName:	WebSocketApi.h
	author:		wynn
	created:	2017/12/10
	purpose:	Websocket长连接接口
*********************************************************************/

#ifndef __WEBSOCKET_API_H
#define __WEBSOCKET_API_H

#include "auntec_base_types.h"
#include "INetworkAccess.h"

#ifdef __cplusplus
extern "C" {
#endif

	#include <stdio.h>
#ifdef _MSC_VER
#	include <windows.h>
#endif

	#ifdef _MSC_VER
	#define WSSCALL		__stdcall
	#elif defined(__GNUC__)
	#if defined(__ppc__) || defined(__ppc64__)
	#define WSSCALL 
	#else
	#define WSSCALL __attribute__((stdcall))
	#endif
	#else 
	#define WSSCALL 
	#endif

	#ifdef _MSC_VER
		/* Windows - set up dll import/export decorators. */
	#	define WSS_API extern
	#elif __APPLE__
	#	define WSS_API __attribute__((visibility("default")))
	#elif defined(__GUNC__)
	#	define WSS_API extern __attribute__((visibility("default")))
	#else
	#	define WSS_API
	#endif

	/***********************************Websocket相关 开始**********************************/
	//所有协议号定义
	enum	
	{
		msg_socketclose = 0x01,		//服务器断开		--不需要处理LPARAM参数
		msg_reconnect = 0x02,		//服务器重连成功	--不需要处理LPARAM参数
		msg_serverpush = 0x03,		//服务器推送		--需要调用WebSocketReleaseData释放内存
		msg_max = 0xFF				//其他
	};
	
	typedef struct __wssHandle* wssHandle;
	typedef bool (WSSCALL *WSS_NOTIFY_CALLBACK)(void* pObj, WPARAM wParam, LPARAM lParam); //如果没有hwnd，可以通过回调函数传回clientid
	/*!
	@brief 创建对象
	@param pwsh wssHandle指针对象
	@return int
	*/
	WSS_API int WSSCALL WSS_Create(wssHandle* phandler);

	/*!
	@brief 设置主窗口句柄
	@param handler wssHandle对象
	@param hMainWnd 调用者窗口句柄，用于接收通知信息
	@param nMsg 消息类型
	@return int
	*/
	WSS_API int WSSCALL WSS_SetHwndInfo(wssHandle handler, HWND hMainWnd, UINT nMsg);

	/*!
	@brief 设置服务器地址
	@param handler wssHandle对象
	@param hostAddr 服务器地址
	@param hostPort 服务器端口
	@param bSSL		是否支持SSL/TLS
	@return int
	*/
	WSS_API int WSSCALL WSS_SetHostInfo(wssHandle handler, const char* hostAddr, unsigned short hostPort, BYTE bSSL);

	/*!
	@brief 设置服务器地址
	@param handler wssHandle对象
	@param pNetInfo 网络连接信息
	@return int
	*/
	WSS_API int WSSCALL WSS_SetNetInfo(wssHandle handler,NETCONN_INFO* pNetInfo);

	/*!
	@brief 设置回调函数
	@param handler wssHandle对象
	@param cb	回调函数
	@return int
	*/
	WSS_API int WSSCALL WSS_SetCallBack(wssHandle handler, WSS_NOTIFY_CALLBACK cb, void* pCbCtx);

	/*!
	@brief 初始化Websocket
	@param handler wssHandle对象
	@return 是否成功
	*/
	WSS_API int WSSCALL WSS_Init(wssHandle handler);
	
	/*!
	@brief 初始化Websocket
	@param handler wssHandle对象
	@return client_id
	*/
	WSS_API const char* WSSCALL WSS_InitAndConnect(wssHandle handler);
	/*!
	@brief 关闭Websocket 不要调用多次
	@param handler wssHandle对象
	@return 
	*/
	WSS_API void WSSCALL WSS_Destroy(wssHandle handler);

	/*!
	@brief 释放内存
	@param pdata 推送到主窗口的消息
	*/
	WSS_API void WSSCALL WSS_Free_Data(void * pdata);
	/***********************************Websocket相关 结束**********************************/

#ifdef __cplusplus
}
#endif

#endif /* __WEBSOCKET_API_H */
