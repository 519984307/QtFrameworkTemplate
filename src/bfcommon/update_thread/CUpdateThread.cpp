#if defined(MACX_UISDK) | defined (_WIN32)
#include "ILogServer.h"
#include "INetworkAccess.h"
#endif

#include "auntec_string_util.h"
#include "auntec_sys_util.h"

#include "json/json.h"

#include "CUpdateThread.h"
#include "../APP_GLOBAL_CONSTANT.h"
#ifdef __APPLE__
#include "UpgradeInfo/NewVersionInfo.h"
#include  <pthread.h>
#endif // __APPLE__

#include <QDebug>

#ifdef WIN32
#define FREE_NETWORK_INTERFACE(x)\
if (NULL != x) { \
	((INetworkAccess*)x)->Free(); \
	x = NULL; \
}
#else
#define FREE_NETWORK_INTERFACE(x)
#endif

#define CHECK_THREAD_STATE(x) \
if ((x)) { \
	throw "user cancel update thread"; \
}

#define QUERY_X86_UPDATA_PARAM "1"
#define QUERY_X64_UPDATA_PARAM "2"

CUpdateThread::CUpdateThread
(
thread_finished_callback pCb,
void* pCtx,
UpdateInformation& latest,
vector<UpdateInformation*>& historys,
std::string curVer
) :
	m_latest(latest),
	m_historys(historys),
	m_pCb(pCb),
	m_pCtx(pCtx),
	m_bExit(false),
	m_lpNetwork(NULL),
	m_curVer(curVer)
{
	// 清理数据
	m_latest.ClearData();
	for (size_t i = 0, iend = m_historys.size(); i < iend; i++) {
		UpdateInformation* _p = m_historys[i];
		if (_p) {
			delete _p;
		}
	}
	vector<UpdateInformation*>().swap(m_historys);

	CAuntecBasedThread::Resume();
#if defined(MACX_UISDK) | defined (_WIN32)
	AuntecBased::auntec_sleep(1);
#endif
}

CUpdateThread::~CUpdateThread()
{
	m_bExit = true;
	if (CAuntecBasedThread::IsSuspended()) {
		CAuntecBasedThread::Resume();
	}
#if defined(_DEBUG) && defined(WIN32)
	if (!CAuntecBasedThread::Wait(50)) {
		::TerminateThread((HANDLE)CAuntecBasedThread::GetThreadHandle(), 0);
	}
#else
    CAuntecBasedThread::Wait(INFINITE);
#endif
	FREE_NETWORK_INTERFACE(m_lpNetwork);
}

uint32_t CUpdateThread::Execute()
{
#if defined(MACX_UISDK) | defined (_WIN32)
	bool _ret = false;
	try {
		// 延迟3s执行
		for (int i = 0; i < 100; i++) {
			AuntecBased::auntec_sleep(30);
			CHECK_THREAD_STATE(m_bExit);
		}

		// 创建网络访问接口
		m_lpNetwork = CreateNetworkAccess();
		if (NULL == m_lpNetwork) {
			throw "create network access error";
		}
		CHECK_THREAD_STATE(m_bExit);

		// 请求信息
		if (AuntecBased::auntec_os_is64bit()) {
			// 获取64位的信息
			std::string _recv_data_x64 = QueryUpdateInfo(QUERY_X64_UPDATA_PARAM);
			if (_recv_data_x64.empty()) {
				throw "query x64 update info failed";
			}
			//std::wstring _recv_data_x64_w = AuntecBased::utf8_2_wide(_recv_data_x64.c_str());
			CHECK_THREAD_STATE(m_bExit);
			_ret = ParseUpdateInfo(_recv_data_x64, m_latest);
			if (_ret) {
				if (m_latest.bLatest) {
					m_latest.strPkgUrl_x64 = m_latest.strPkgUrl;
				}
			}
			else {
                qDebug("CUpdateThread::Execute parse 64bit software update info failed");
			}

			// 获取32位的信息
			if (_ret && m_latest.bLatest && !auntec_soft_is64bit()) {
				std::string _recv_data_x86 = QueryUpdateInfo(QUERY_X86_UPDATA_PARAM);
				if (!_recv_data_x86.empty()) {
					CHECK_THREAD_STATE(m_bExit);
					UpdateInformation _uif;
					if (ParseUpdateInfo(_recv_data_x86, _uif, false)) {
						m_latest.strPkgUrl_x86 = _uif.strPkgUrl;
					}
					else {
                        qDebug("CUpdateThread::Execute parse 32bit software update info failed");
					}
				}
				else {
                    qDebug("CUpdateThread::Execute query 32bit software update info failed");
				}
			}
		}
		else {
			// 获取32位的信息
			std::string _recv_data_x86 = QueryUpdateInfo(QUERY_X86_UPDATA_PARAM);
			if (_recv_data_x86.empty()) {
				throw "query x86 update info failed";
			}
			CHECK_THREAD_STATE(m_bExit);
			_ret = ParseUpdateInfo(_recv_data_x86, m_latest);
			if (_ret) {
				m_latest.strPkgUrl_x86 = m_latest.strPkgUrl;
			}
			else {
                qDebug("CUpdateThread::Execute parse 32bit software update info failed");
			}
		}
	}
	catch (...) {}
	FREE_NETWORK_INTERFACE(m_lpNetwork);
	if (!m_bExit) {
		m_pCb(m_pCtx, _ret);
	}
#else
	NewVersonInfo versionInfo;
	VersionInfo info;
	bool success = versionInfo.fetch(false, info, m_pCb, m_pCtx);
	if (success) {
		m_latest.bForce = info.bForce;
		m_latest.bLatest = info.bLatest;
		m_latest.strVersion = info.strVersion;
		m_latest.strUpdateInfo = info.strUpdateInfo;
		m_latest.strPkgUrl = info.strPkgUrl;
		m_latest.strMd5 = info.strMd5;
		m_latest.strOnlineTime = info.strOnlineTime;
		if (!m_latest.strPkgUrl.empty()) {
			m_latest.strPkgUrl_x64 = m_latest.strPkgUrl;
		}
	}

	if (!m_bExit) {
		m_pCb(m_pCtx, success);
	}
#endif
	return 0;
		}

MEXP
std::string CUpdateThread::BuildSendData(const char* packageSystemSupport)
{
	std::string _send_data;
#if defined(MACX_UISDK) | defined (_WIN32)
	std::string _json_data;
	{
		Json::Value _json_values;
        _json_values["appId"] = APP_ID;
        _json_values["versionCode"] = m_curVer;
		_json_values["queryHistory"] = true;
		_json_values["packageSystemSupport"] = packageSystemSupport;
		_json_data = _json_values.toStyledString();
	}

	int _data_size = 0;
	char* _data = static_cast<char*>(GetLogServer()->BuildHttpData
	(
        APP_UPGRADE_URL,
		_json_data.c_str(),
		(int)_json_data.size(),
		_data_size,
		NULL,
        UPGRADE_SERVER_HOST,
		""
	));
	if (NULL != _data && _data_size > 0) {
		_send_data.resize(_data_size);
		memcpy(&(_send_data[0]), _data, _data_size);
		GetLogServer()->FreeData(_data);
	}
	else {
        qDebug("CUpdateThread::BuildSendData encrypt send data failed");
	}
#endif
	return _send_data;
}

MEXP
std::string CUpdateThread::ParseRecvData(const std::string& strRecvData)
{
	static const char _json_Key_code[] = "code";
	static const char _json_Key_data[] = "data";

	std::string _dec_data;
#if defined(MACX_UISDK) | defined (_WIN32)
	std::string _res_data;
	{
		Json::Reader _json_read;
		Json::Value _json_value;
		if (_json_read.parse(strRecvData, _json_value)) {
			if (_json_value.isMember(_json_Key_code) &&
				_json_value.isMember(_json_Key_data) &&
				_json_value[_json_Key_code].asString() == "server.success") {
				_res_data = _json_value[_json_Key_data].asString();
			}
			else {
                qDebug("CUpdateThread::ParseRecvData json data invalid");
			}
		}
		else {
            qDebug("CUpdateThread::ParseRecvData json parse failed");
		}
	}

	if (!_res_data.empty()) {
		int _data_size = 0;
		char* _data = static_cast<char*>(GetLogServer()->DecryptData
		(
			_res_data.c_str(),
			(int)_res_data.length(),
			_data_size
		));
		if (NULL != _data && _data_size > 0) {
			_dec_data.resize(_data_size);
			memcpy(&(_dec_data[0]), _data, _data_size);
			GetLogServer()->FreeData(_data);
		}
		else {
            qDebug("CUpdateThread::ParseRecvData decrypt res data failed");
		}
	}
#endif
	return _dec_data;
}

MEXP
std::string CUpdateThread::QueryUpdateInfo(const char* packageSystemSupport)
{
	std::string _update_info;
#if defined(MACX_UISDK) | defined (_WIN32)
	char* _data = NULL;
	int _data_size = 0;
	int _loop_count = 0; // 请求失败的重试10次
	std::string _send_data, _recv_data;

	// 构建请求体数据
	_send_data = BuildSendData(packageSystemSupport);
	if (_send_data.empty()) {
		return _update_info;
	}
	CHECK_THREAD_STATE(m_bExit);

	// 请求数据
	do {
		if (_loop_count != 0) { // 如果请求失败了，则等待一会儿在执行
			for (int i = 0; i < 100; i++) {
				AuntecBased::auntec_sleep(20);
				CHECK_THREAD_STATE(m_bExit);
			}
		}
		_data = static_cast<char*>(((INetworkAccess*)m_lpNetwork)->PostEx
		(
            UPGRADE_SERVER_HOST,
            UPGRADE_SERVER_PORT,
			_send_data.c_str(),
			_send_data.length(),
			_data_size,
			3000,
            SERVER_SLL_ENABLE
		));
		if (NULL != _data && _data_size > 0) {
			_recv_data.resize(_data_size);
			memcpy(&(_recv_data[0]), _data, _data_size);
			((INetworkAccess*)m_lpNetwork)->FreeData(_data);
			break;
		}
		CHECK_THREAD_STATE(m_bExit);
	} while (_loop_count++ < 10);

	// 解密数据
	CHECK_THREAD_STATE(m_bExit);
	if (!_recv_data.empty()) {
		_update_info = ParseRecvData(_recv_data);
	}
	else {
        qDebug("CUpdateThread::QueryUpdateInfo query updata info failed");
	}
#endif
	return _update_info;
}

static void ReadUpdateInfo(Json::Value& _latest, UpdateInformation* _uif)
{
	static const char _json_changeLog[] = "changeLog";
	static const char _json_downloadUrl[] = "downloadUrl";
	static const char _json_md5[] = "md5";
	static const char _json_size[] = "size";
	static const char _json_versionCode[] = "versionCode";
	static const char _json_createTime[] = "createTime";

	if (_latest.isMember(_json_versionCode)) {
		_uif->strVersion = _latest[_json_versionCode].asString();
	}

	if (_latest.isMember(_json_changeLog)) {
		Json::Value& logs = _latest[_json_changeLog];
		for (Json::ArrayIndex i = 0, iend = logs.size(); i < iend; i++) {
			_uif->strUpdateInfo += logs[i].asString();
			_uif->strUpdateInfo += "\r\n";
		}
	}

	if (_latest.isMember(_json_createTime)) {
		_uif->strOnlineTime = _latest[_json_createTime].asString();
		_uif->strOnlineTime = AuntecBased::str_replace(_uif->strOnlineTime.c_str(), "T", " ");
	}

	if (_latest.isMember(_json_md5)) {
		_uif->strMd5 = _latest[_json_md5].asString();
	}

	if (_latest.isMember(_json_size)) {
		_uif->size = _latest[_json_size].asLargestInt();
	}

	if (_latest.isMember(_json_downloadUrl)) {
		_uif->strPkgUrl = _latest[_json_downloadUrl].asString();
	}
}

MEXP
bool CUpdateThread::ParseUpdateInfo(const std::string& _info, UpdateInformation& _uif, bool bReadHistory/* = true*/)
{
	static const char _json_business[] = "business";
	static const char _json_operation[] = "operation";
	static const char _json_latestDefault[] = "latestDefault";
	static const char _json_history[] = "history";

#if defined(MACX_UISDK) | defined (_WIN32)
	Json::Reader _read;
	Json::Value _root;
	if (!_read.parse(_info, _root)) {
		return false;
}

	if (_root.isMember(_json_business)) {
		Json::Value& _business = _root[_json_business];
		if (_business.isMember(_json_operation)) {
#ifdef _DEBUG
			_uif.bForce = false;
			_uif.bLatest = false;
#else
			switch (_business[_json_operation].asInt())
			{
			case 0:
				_uif.bForce = false;
				_uif.bLatest = false;
				break;
			case 1:
				_uif.bForce = false;
				_uif.bLatest = true;
				break;
			case 2:
				_uif.bForce = true;
				_uif.bLatest = true;
				break;
			}
#endif
		}

		if (!_uif.bLatest) {
			return true;
		}

		if (_business.isMember(_json_latestDefault)) {
			ReadUpdateInfo(_business[_json_latestDefault], &_uif);
		}

		if (bReadHistory && _business.isMember(_json_history)) {
			Json::Value& historys = _business[_json_history];
			for (Json::ArrayIndex i = 0, iend = historys.size(); i < iend; i++) {
				UpdateInformation* _p = new UpdateInformation;
				if (NULL != _p) {
					ReadUpdateInfo(historys[i], _p);
					m_historys.push_back(_p);
				}
			}
		}

		return true;
	}

#endif
	return false;
	}

