#include "CSendDataThread.h"
#if defined(MACX_UISDK) | defined (_WIN32)
#include "ILogServer.h"
#include "INetworkAccess.h"
#endif
#include "APP_GLOBAL_CONSTANT.h"
#include "../thread/thread_cond.h"
#include "json/json.h"
struct NetworkInfo{
	std::string strUrl;
	std::string strSendData;
	std::string strFilePath;
};

CSendDataThread::CSendDataThread()
{
#if defined(MACX_UISDK) | defined (_WIN32)
	m_bExit = false;

	m_pNetworkAccess = CreateNetworkAccess();
	assert(m_pNetworkAccess);

	m_pMutex = pthreadx_mutex_init();
	assert(m_pMutex);

	m_pCond = pthreadx_cond_init();
	assert(m_pCond);

	m_pThread = pthreadx_create(thread_entry, this);
	assert(m_pThread);
	pthreadx_sleep(1);
#endif
}

CSendDataThread::~CSendDataThread(void)
{
#if defined(MACX_UISDK) | defined (_WIN32)
	m_bExit = true;
	if (NULL != m_pThread) {
		pthreadx_cond_signal(m_pCond, 0);
		pthreadx_destroy((pthreadx_t)m_pThread);
		m_pThread = NULL;
	}

	if (NULL != m_pCond) {
		pthreadx_cond_destroy(m_pCond);
		m_pCond = NULL;
	}

	pthreadx_mutex_lock(m_pMutex);
	for (int i = 0, count = m_networkInfos.size(); i < count; i++) {
		SAFE_DELETE(m_networkInfos[i]);
	}
	m_networkInfos.clear();
	pthreadx_mutex_unlock(m_pMutex);

	if (NULL != m_pMutex) {
		pthreadx_mutex_destroy(m_pMutex);
		m_pMutex = NULL;
	}
#endif
}

CSendDataThread* CSendDataThread::Instance()
{
	static CSendDataThread thead;
	return &thead;
}

void CSendDataThread::AddNetworkInfo(const std::string& sendData, const std::string& filePath/*=std::string()*/)
{
#if defined(MACX_UISDK) | defined (_WIN32)
	NetworkInfo* pInfo = new NetworkInfo;
	if (NULL != pInfo) {
        Json::Value root;
        Json::Value extend;
        root["kxuid"] = "";
        root["suggestion"] = sendData.c_str();
        root["extend"] = extend;
        pInfo->strUrl = APP_FEEDBACK_URL;
        pInfo->strSendData = root.toStyledString().c_str();
		pInfo->strFilePath = filePath;
		pthreadx_mutex_lock(m_pMutex);
		m_networkInfos.push_back(pInfo);
		pthreadx_mutex_unlock(m_pMutex);
		pthreadx_cond_signal(m_pCond, 0);
	}
#endif
}

unsigned __stdcall CSendDataThread::thread_entry(void* pCtx)
{
#if defined(MACX_UISDK) | defined (_WIN32)
	try{
		NetworkInfo* pInfo = NULL;
		ILogServer* pls = GetLogServer();
		CSendDataThread* p = (CSendDataThread*)pCtx;
		INetworkAccess* pna = p->m_pNetworkAccess;

		if(NULL == pls || NULL == pna){
			return 1; // 异常
		}

		while(!p->m_bExit){
			pthreadx_cond_wait(p->m_pCond);
			if(p->m_bExit){
				break;
			}

			while(p->m_networkInfos.size() > 0){
				pthreadx_mutex_lock(p->m_pMutex);
				pInfo = p->m_networkInfos.front();
				p->m_networkInfos.pop_front();
				pthreadx_mutex_unlock(p->m_pMutex);
				if(p->m_bExit){
					SAFE_DELETE(pInfo);
					break;
				}

				if(NULL != pInfo){
					int nLen = 0;
					void* pEnc = pls->BuildHttpData(pInfo->strUrl.c_str(), pInfo->strSendData.c_str(), pInfo->strSendData.length(), nLen, pInfo->strFilePath.empty()?NULL:pInfo->strFilePath.c_str());
					if(NULL != pEnc && nLen > 0)
					{
						int nPostReurnLen = 0;
						void* pData = pna->PostEx(FEEDBACK_SERVER_HOST, SERVER_PORT, pEnc, nLen, nPostReurnLen, 5000, SERVER_SLL_ENABLE);
						if(NULL != pData)
						{
							pna->FreeData(pData);
						}
						pls->FreeData(pEnc);
					}
					SAFE_DELETE(pInfo);
				}

				if(p->m_bExit){
					break;
				}
			}

		}
	}catch(...){}
#endif
	return 0;
}
