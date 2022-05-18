#include "bfcommon.h"
#include "ILogServer.h"
#include "APP_GLOBAL_CONSTANT.h"
#ifdef __APPLE__
#include "macos/EventTrackCInterface.h"
#endif


void bfInitLogServer(const char *logPath, const char *pAppId, const char *pAppKey,
                     const char *pDefaultHost, int ndefaultport, bool bHttps,
                     const char *urlVersion, int MIdVersion, bool bSandbox,
                     const char *pJnzPath, const char *pDefaultSensorHost,
                     int nDefaultSensorPort, const char *pDefaultSensorUrl, bool bMainProcess)
{
    InitLogServer
            (
            logPath,
            pAppId,
            pAppKey,
            pDefaultHost,
            ndefaultport,
            bHttps,
            urlVersion,
            MIdVersion,
            bSandbox,
            pJnzPath,
            pDefaultSensorHost,
            nDefaultSensorPort,
            pDefaultSensorUrl
            );

#ifdef __APPLE__
setupTracker();

#endif

}

void bfReleaseLogserver()
{
    ReleaseLogServer();
}
