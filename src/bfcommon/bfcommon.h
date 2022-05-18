#ifndef BFCOMMON_H
#define BFCOMMON_H
#include "bfcommon_export.h"
#include "ILogServer.h"
#define BF_LOG_MID_VERSION_1		0	//v1.0	旧
#define BF_LOG_MID_VERSION_2		1	//v1.1	新
#define BF_LOG_MID_VERSION_1_0		0	//v1.0	新
#define BF_LOG_MID_VERSION_1_1		1	//v1.1	新
#define BF_LOG_MID_VERSION_1_2		2	//v1.2	新
#define BF_LOG_MID_VERSION_REG		20	//reg


void COMMON_LIB_EXPORT bfInitLogServer
                (
                const char* logPath,
                const char* pAppId,
                const char* pAppKey,
                const char* pDefaultHost,
                int ndefaultport,
                bool bHttps,
                const char* urlVersion,
                int MIdVersion=BF_LOG_MID_VERSION_1,
                bool bSandbox=false,
                const char* pJnzPath=nullptr,
                const char* pDefaultSensorHost="sa.aunload.com",
                int nDefaultSensorPort=8106,
                const char* pDefaultSensorUrl="/sa?project=default",
                bool bMainProcess=true
                );

void COMMON_LIB_EXPORT bfReleaseLogserver();

#endif // BFCOMMON_H
