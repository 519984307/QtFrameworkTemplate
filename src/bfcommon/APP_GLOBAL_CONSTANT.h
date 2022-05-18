#ifndef APP_GLOBAL_CONSTANT_H__
#define APP_GLOBAL_CONSTANT_H__

/*!
@brief 产品ID
*/
#ifdef __APPLE__
static const char APP_ID[] = "88888888";
#else
static const char APP_ID[] = "10301011";
#endif
/*!
@brief 产品Key
*/
#ifdef __APPLE__
static const char APP_KEY[] = "8D3FE9D1D11F4114B89D46DCE9321605";
#else
#ifdef _DEBUG // 内网
static const char APP_KEY[] = "c1893da96a2147957d9fd0baf077b48d";
#else
static const char APP_KEY[] = "c1893da96a2147957d9fd0baf077b48d";
#endif
#endif

/*!
@brief support服务器域名
*/
#ifdef _DEBUG
static const char SUPPORT_SERVER_HOST[] = "support.aunapi.cc";
#else
static const char SUPPORT_SERVER_HOST[] = "support.aunapi.com";
#endif


/*!
@brief 更新接口服务器域名
*/
#ifdef _DEBUG
static const char UPGRADE_SERVER_HOST[] = "10.10.20.102";
#else
static const char UPGRADE_SERVER_HOST[] = "front-gw.aunapi.com";
#endif

/*!
@brief 反馈接口服务器域名
*/
// #ifdef _DEBUG
// static const char FEEDBACK_SERVER_HOST[] = "ucenter.aunapi.cc";
// #else
// static const char FEEDBACK_SERVER_HOST[] = "ucenter.aunapi.com";
// #endif
#define FEEDBACK_SERVER_HOST SUPPORT_SERVER_HOST

/*!
@brief API版本
*/
static const char SERVER_API_VERSION[] = "/v1.1";

/*!
@brief 服务器端口号
*/
#ifdef _DEBUG
static const unsigned short SERVER_PORT = 80;
#else
static const unsigned short SERVER_PORT = 443;
#endif

/*!
@brief 检查更新服务器端口号
*/
#ifdef _DEBUG
static const unsigned short UPGRADE_SERVER_PORT = 8889;
#else
static const unsigned short UPGRADE_SERVER_PORT = 443;
#endif

/*!
@brief 是否加密访问
*/
#ifdef _DEBUG
static bool SERVER_SLL_ENABLE = false;
#else
static bool SERVER_SLL_ENABLE = true;
#endif

/*!
@brief 更新接口
*/
#if defined(WIN32) || defined(_WIN32)
static const char APP_UPGRADE_URL[] = "/applicationService/app/upgrade/checkEncrypt";
#elif defined(__APPLE__)
static const char APP_UPGRADE_URL[] = "/version/upgrade";
#endif

/*
@brief 反馈接口
*/
static const char APP_FEEDBACK_URL[] = "/feedback/save";


static const wchar_t APP_GUID[] = L"{5D1C4995-CFC4-4212-8358-E5B69581BEA0}";

#endif
