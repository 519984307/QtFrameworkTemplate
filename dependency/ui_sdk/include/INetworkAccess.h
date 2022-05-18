#ifndef __INETWORK_ACCESS_H
#define __INETWORK_ACCESS_H

#include "auntec_base_types.h"
#include <string>


#define PROXY_TYPE_HTTP   1
#define PROXY_TYPE_SOCKS4 2
#define PROXY_TYPE_SOCKS5 3

typedef struct tagProxyConnInfo  //网络连接结构
{
	//proxy info
	uint32_t connType;
	char proxyHost[255];
	uint32_t proxyPort;
	char proxyUser[255];
	char proxyPasswd[255];
}PROXY_INFO;
typedef struct tagNetConnInfo  //网络连接结构
{
	//server info
	char srvHost[255];
	uint32_t srvPort;
	bool bSSL;

	//proxy info
	PROXY_INFO *proxyInfo; 
}NETCONN_INFO,*PNETCONN_INFO;

/*!
@brief Http网络访问接口
@note 目前导出接口还很简单，后续逐步完善
*/
class INetworkAccess
{
public:
	virtual void* STDCALL Post(const char* url, int& rlen, bool bSSL=false) = 0;
	virtual void* STDCALL PostEx(const char* url, const void* pData, const int datalen, int& rlen, bool bSSL=false) = 0;
	virtual void* STDCALL Post(const char* host, unsigned short port, const void* pData, const int datalen, int& rlen, bool bSSL=false) = 0;
	virtual void* STDCALL PostEx(const char* host, unsigned short port, const void* pData, const int datalen, int& rlen, int timeout, bool bSSL=false) = 0;
	virtual void* STDCALL Get(const char* url, int& rlen, bool bSSL=false) = 0;
	virtual void* STDCALL Head(const char* url, int& rlen, bool bSSL=false) = 0;

	virtual void* STDCALL Get(const char* url, int& rlen, const char* pExtendHeader,int timeout,bool bSSL=false) = 0;
	virtual void STDCALL SetPostValue(const char* key,const char* value) = 0;
	virtual void STDCALL ClearPostValue() = 0;
	virtual void* STDCALL BuildHttpData(const char* host, const char* url, const char* sdkVersion, int& len,const char* pExtendHeader = NULL) = 0;
	virtual void STDCALL FreeData(void* pData) = 0;
	virtual void STDCALL Free() = 0;
	virtual void* STDCALL PostEx(NETCONN_INFO* pNetInfo,const void* pData, const int datalen, int& rlen, int timeout) = 0;
	virtual void* STDCALL Get(NETCONN_INFO* pNetInfo,const char* url, int& rlen, const char* pExtendHeader,int timeout) = 0;
};

/*!
@brief 创建Http网络访问接口
*/
extern "C"
EXPORT
INetworkAccess* STDCALL CreateNetworkAccess();


extern "C"
EXPORT
bool STDCALL TestProxy(NETCONN_INFO* proxyInfo);

#endif
