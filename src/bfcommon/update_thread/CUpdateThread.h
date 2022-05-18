#ifndef CUPDATE_THREAD_H__
#define CUPDATE_THREAD_H__

#include "auntec_thread_base.h"
#include "auntec_sys_util.h"
#include <vector>
#include "bfcommon_export.h"
using namespace std;

#ifndef auntec_soft_is64bit
#define auntec_soft_is64bit() (8 == sizeof(void*))
#endif

struct COMMON_LIB_EXPORT UpdateInformation{
	UpdateInformation(): size(0), bForce(false), bLatest(false){
		bSoftX64 = auntec_soft_is64bit();
#ifdef WIN32
		bOsX64 = AuntecBased::auntec_os_is64bit();
#else
		bOsX64 = true;
#endif
	}
	~UpdateInformation(){ ClearData(); }
	void ClearData(){
		size = 0;
		bForce = false;
		bLatest = false;
		string().swap(strMd5);
		string().swap(strVersion);
		string().swap(strPkgUrl);
		string().swap(strUpdateInfo);
		string().swap(strOnlineTime);
		string().swap(strPkgUrl_x86);
		string().swap(strPkgUrl_x64);
	}
	int64_t size;
	bool bForce;
	bool bLatest;
	string strMd5;
	string strVersion;
	string strPkgUrl;
	string strUpdateInfo;
	string strOnlineTime;
	string strPkgUrl_x86;
	string strPkgUrl_x64;
	bool bSoftX64;
	bool bOsX64;
};

typedef void (*thread_finished_callback)(void* pCtx, bool bComplete);

class COMMON_LIB_EXPORT CUpdateThread:public AuntecBased::CAuntecBasedThread
{
public:
	CUpdateThread(thread_finished_callback pCb, void* pCtx, UpdateInformation& latest, vector<UpdateInformation*>& historys,std::string curVer);
	~CUpdateThread();

protected:
	virtual uint32_t Execute();

private:
	MEXP
	std::string BuildSendData(const char* packageSystemSupport);
	MEXP
	std::string ParseRecvData(const std::string& strRecvData);
	MEXP
	std::string QueryUpdateInfo(const char* packageSystemSupport);
	MEXP
	bool ParseUpdateInfo(const std::string& _info, UpdateInformation& _uif, bool bReadHistory=true);

private:
	bool m_bExit;
	UpdateInformation& m_latest;
	vector<UpdateInformation*>& m_historys;

	thread_finished_callback m_pCb;
	void* m_pCtx;

	void* m_lpNetwork;
	std::string m_curVer;
};

#endif
