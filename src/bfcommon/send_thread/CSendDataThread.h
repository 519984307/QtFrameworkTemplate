#ifndef _FEEDBACK_THREAD
#define _FEEDBACK_THREAD

#include "bfcommon_export.h"
#include "auntec_thread_base.h"
#include <string>
#include <deque>


class INetworkAccess;

typedef struct NetworkInfo* PNetworkInfo;

class COMMON_LIB_EXPORT CSendDataThread
{
public:
	static CSendDataThread* Instance();
    void AddNetworkInfo(const std::string& sendData, const std::string& filePath=std::string());

private:
	CSendDataThread();
	~CSendDataThread();
	static unsigned __stdcall thread_entry(void* pCtx);

private:
	bool                     m_bExit;
	void*                    m_pMutex;
	void*                    m_pCond;
	void*                    m_pThread;
	INetworkAccess*          m_pNetworkAccess;
	std::deque<PNetworkInfo> m_networkInfos;
};

#endif // !_DATA_FEEDBACK_THREAD
