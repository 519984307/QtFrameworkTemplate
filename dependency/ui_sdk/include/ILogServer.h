#ifndef __ILOG_SERVER_H
#define __ILOG_SERVER_H

#include "auntec_base_types.h"
//#include <vector>
//#include <map>
//using namespace std;

// log level
#define LOG_ERROR_LEVEL_FATAL        1
#define LOG_ERROR_LEVEL_ERROR       2
#define LOG_ERROR_LEVEL_WARNING 3
#define LOG_ERROR_LEVEL_INFO          4
#define LOG_ERROR_LEVEL_DEBUG      5
#define LOG_ERROR_LEVEL_PROFILE     6

// install type
#define LOG_INSTALL_TYPE_INSTALL       1
#define LOG_INSTALL_TYPE_UNINSTALL 2
#define LOG_INSTALL_TYPE_UPDATE       3


#define LOG_MID_VERSION_1		0	//v1.0	旧
#define LOG_MID_VERSION_2		1	//v1.1	新

#define LOG_MID_VERSION_1_0		0	//v1.0	新
#define LOG_MID_VERSION_1_1		1	//v1.1	新
#define LOG_MID_VERSION_1_2		2	//v1.2	新
#define LOG_MID_VERSION_REG		20	//reg

//一个list最多500个字段
#ifndef MAX_REPORT_LIST_NUM
#	define MAX_REPORT_LIST_NUM 500
#endif

//每个字段最多250个字符
#ifndef MAX_REPORT_LIST_ITEM_NUM
#	define MAX_REPORT_LIST_ITEM_NUM 250
#endif

namespace MMobile{
	class IDevice;
}

// 崩溃自定义回调原型
// param const char* dmp文件路径（UTF-8字符）
typedef void (STDCALL* CRASH_REPORT_CALLBACK)(const char*);

/*!
@brief 信息收集接口
*/
class ILogServer
{
public:
	/*!
	@brief 日志收集
	*/
	virtual void STDCALL LogError
													(
													int level,
													const char* categoryCode,
													const char* logCode,
													const char* logData=NULL,
													const char* extendData=NULL
													) = 0;

	/*!
	@note SensorAddEvent接口与ClearProperty接口必须配对使用
		  为了保证线程安全，因此内部在ClearProperty接口中加锁，在SensorAddEvent接口释放锁
	*/
	virtual void STDCALL SensorAddEvent
													(
													const char* eventName
													) = 0;
	virtual void STDCALL ClearProperty
													(
													) = 0;
	virtual void STDCALL insertInt
													(
													const char* name,
													int value
													) = 0;
	virtual void STDCALL insertFloat
													(
													const char* name,
													float value
													) = 0;
	virtual void STDCALL insertBool
													(
													const char* name,
													bool value
													) = 0;
	virtual void STDCALL insertStr
													(
													const char* name,
													const char* value
													) = 0;
	virtual void STDCALL insertList
													(
													const char* name,
													char* arrData,
													int* arrLength,
													int arrNum
													) = 0;
	virtual void STDCALL LogError2
													(
													int level,
													const char* categoryCode,
													const char* logCode,
													const char* logFile,
													const char* logData=NULL,
													const char* extendData=NULL
													) = 0;

	/*!
	@brief 操作信息收集
	*/
	virtual void STDCALL LogOperateInfo
															(
															const char* pageCode,
															const char* eventCode,
															const char* operateMsg=NULL
															) = 0;

	/*!
	@brief 安装信息收集
	*/
	virtual void STDCALL LogInstall
													(
													int type,
													const char* version=NULL,
													const char* url=NULL
													) = 0;

	/*!
	@brief 设备信息收集
	*/
	virtual void STDCALL LogDeviceInfo(MMobile::IDevice* pDevice) = 0;

	/*!
	@brief 打开url
	*/
	virtual void STDCALL OpenUrl(const wchar_t* url,
		const char* spmFunc = NULL,
		const char* spmMode = NULL) = 0;

	/*!
	@brief 构建http待发送数据
	*/
	virtual void* STDCALL BuildHttpData
															(
															const char* url,
															const void* pData,
															const int dataLen,
															int& rlen,
															const char* pszFilePath = NULL,
															const char* host=NULL, 
															const char* ifVer=NULL) = 0;

	/*!
	@brief 解密数据
	*/
	virtual void* STDCALL DecryptData
															(
															const void* pData,
															const int dataLen,
															int& rlen
															) = 0;

	/*!
	@brief 获取唯一识别码
	*/
	virtual const char* STDCALL GetMid() = 0;

	/*!
	@brief 释放数据
	*/
	virtual void STDCALL FreeData(void* pData) = 0;
    /*!
	@brief 设置是否允许提交，若不允许，则缓存起来，待允许后统一按顺序提交
	*/
	virtual void STDCALL SetEnableCommit(bool enable) = 0;
    
	/*!
	@brief 设置神策distanct_id
	*/
	virtual void STDCALL SetSensorDistanctId(const char* id) = 0;
	
	/*!
	@brief 设置神策默认属性
	*/
	virtual void STDCALL SetSensorProperty(const char* key, const char* val) = 0;

	/*!
	@brief 设置app崩溃回调
	*/
	virtual void STDCALL SetCrashReportCallback(CRASH_REPORT_CALLBACK pCallbcak) = 0;

	/*!
	@brief 主动上报崩溃
	@param lpFilePath 崩溃堆栈文件全路径(utf8)
	*/
	virtual void STDCALL SendCrashStackFile(const char* lpFilePath) = 0;

	/*!
	@brief 判断是否首次启动软件
	*/
	virtual const bool STDCALL IsFirstStart() = 0;
};

/*!
@brief 初始化logserver
@param logPath 日志路径
@param pAppId app ID
@param pDefaultHost 服务器默认域名
@param ndefaultport 服务器默认端口号
@param bHttps 是否使用https
@param urlVersion 网络接口版本
@param MidVersion 生成mid的算法版本
@param bSandbox 是否开启沙盒调试
@param pJnzPath jnz模块的路径
@param pDefaultSensorHost 神策服务器域名
@param nDefaultSensorPort 神策服务器端口
@param pDefaultSensorUrl 神策数据上报接口地址
@param bMainProcess 是否上报启动事件
*/
extern "C"
EXPORT
void STDCALL InitLogServer
						(
						const char* logPath,
						const char* pAppId,
						const char* pAppKey,
						const char* pDefaultHost,
						int ndefaultport,
						bool bHttps,
						const char* urlVersion,
						int MIdVersion=LOG_MID_VERSION_1,
						bool bSandbox=false,
						const char* pJnzPath=NULL,
						const char* pDefaultSensorHost="sa.aunload.com",
						int nDefaultSensorPort=8106,
						const char* pDefaultSensorUrl="/sa?project=default",
						bool bMainProcess=true
						);

extern "C"
EXPORT
ILogServer* STDCALL GetLogServer();

extern "C"
EXPORT
void STDCALL ReleaseLogServer();


#define SERVER_LOG_ERROR GetLogServer()->LogError
#define SERVER_DEVICE_INFO GetLogServer()->LogDeviceInfo
#define SERVER_OPERATE_INFO GetLogServer()->LogOperateInfo
#define SERVER_MID GetLogServer()->GetMid()
#define SERVER_BUILD_HTTP GetLogServer()->BuildHttpData
#define SERVER_FREE_DATA GetLogServer()->FreeData
#define SERVER_DECRYPT_DATA GetLogServer()->DecryptData
#define SERVER_OPEN_URL GetLogServer()->OpenUrl
#define SERVER_LOG_ERROR2 GetLogServer()->LogError2
#define SERVER_SENSOR_CLEAR GetLogServer()->ClearProperty
#define SERVER_SENSOR_INSERT_INT GetLogServer()->insertInt
#define SERVER_SENSOR_INSERT_FLOAT GetLogServer()->insertFloat
#define SERVER_SENSOR_INSERT_BOOL GetLogServer()->insertBool
#define SERVER_SENSOR_INSERT_STR GetLogServer()->insertStr
#define SERVER_SENSOR_INSERT_LIST GetLogServer()->insertList
#define SERVER_SENSOR_EVENT GetLogServer()->SensorAddEvent
#define SERVER_SENSOR_ENABLE_COMMIT GetLogServer()->SetEnableCommit
#define SERVER_SENSOR_SET_DISTANCT_ID GetLogServer()->SetSensorDistanctId
#define SERVER_SENSOR_SET_PROPERTY GetLogServer()->SetSensorProperty
#define SERVER_CRASH_REPORT_CALLBACK GetLogServer()->SetCrashReportCallback
#define SERVER_SEND_CRASH_STACK_FILE GetLogServer()->SendCrashStackFile

#endif
