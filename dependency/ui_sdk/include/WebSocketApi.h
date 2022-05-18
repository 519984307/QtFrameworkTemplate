/********************************************************************
	fileName:	WebSocketApi.h
	author:		wynn
	created:	2017/12/10
	purpose:	Websocket�����ӽӿ�
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

	/***********************************Websocket��� ��ʼ**********************************/
	//����Э��Ŷ���
	enum	
	{
		msg_socketclose = 0x01,		//�������Ͽ�		--����Ҫ����LPARAM����
		msg_reconnect = 0x02,		//�����������ɹ�	--����Ҫ����LPARAM����
		msg_serverpush = 0x03,		//����������		--��Ҫ����WebSocketReleaseData�ͷ��ڴ�
		msg_max = 0xFF				//����
	};
	
	typedef struct __wssHandle* wssHandle;
	typedef bool (WSSCALL *WSS_NOTIFY_CALLBACK)(void* pObj, WPARAM wParam, LPARAM lParam); //���û��hwnd������ͨ���ص���������clientid
	/*!
	@brief ��������
	@param pwsh wssHandleָ�����
	@return int
	*/
	WSS_API int WSSCALL WSS_Create(wssHandle* phandler);

	/*!
	@brief ���������ھ��
	@param handler wssHandle����
	@param hMainWnd �����ߴ��ھ�������ڽ���֪ͨ��Ϣ
	@param nMsg ��Ϣ����
	@return int
	*/
	WSS_API int WSSCALL WSS_SetHwndInfo(wssHandle handler, HWND hMainWnd, UINT nMsg);

	/*!
	@brief ���÷�������ַ
	@param handler wssHandle����
	@param hostAddr ��������ַ
	@param hostPort �������˿�
	@param bSSL		�Ƿ�֧��SSL/TLS
	@return int
	*/
	WSS_API int WSSCALL WSS_SetHostInfo(wssHandle handler, const char* hostAddr, unsigned short hostPort, BYTE bSSL);

	/*!
	@brief ���÷�������ַ
	@param handler wssHandle����
	@param pNetInfo ����������Ϣ
	@return int
	*/
	WSS_API int WSSCALL WSS_SetNetInfo(wssHandle handler,NETCONN_INFO* pNetInfo);

	/*!
	@brief ���ûص�����
	@param handler wssHandle����
	@param cb	�ص�����
	@return int
	*/
	WSS_API int WSSCALL WSS_SetCallBack(wssHandle handler, WSS_NOTIFY_CALLBACK cb, void* pCbCtx);

	/*!
	@brief ��ʼ��Websocket
	@param handler wssHandle����
	@return �Ƿ�ɹ�
	*/
	WSS_API int WSSCALL WSS_Init(wssHandle handler);
	
	/*!
	@brief ��ʼ��Websocket
	@param handler wssHandle����
	@return client_id
	*/
	WSS_API const char* WSSCALL WSS_InitAndConnect(wssHandle handler);
	/*!
	@brief �ر�Websocket ��Ҫ���ö��
	@param handler wssHandle����
	@return 
	*/
	WSS_API void WSSCALL WSS_Destroy(wssHandle handler);

	/*!
	@brief �ͷ��ڴ�
	@param pdata ���͵������ڵ���Ϣ
	*/
	WSS_API void WSSCALL WSS_Free_Data(void * pdata);
	/***********************************Websocket��� ����**********************************/

#ifdef __cplusplus
}
#endif

#endif /* __WEBSOCKET_API_H */
