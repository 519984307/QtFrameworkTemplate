#ifndef __AUNTEC_SYS_UTIL_H
#define __AUNTEC_SYS_UTIL_H

#include "auntec_base_types.h"

#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief 获取文件大小
	@param path 文件路径
	@return 文件不存在返回0
	*/
	int64_t auntec_get_file_size(const char* path);

	/*!
	@brief 获取文件夹大小
	@param path 文件夹路径
	@param fileCounter 统计文件数量
	@return 文件夹不存在返回0
	*/
	uint64_t auntec_get_folder_size(const char* dir, int* fileCounter=NULL);

	/*!
	@brief 设置环境变量
	@param evName 变量名
	@param evValue 变量值
	@note param需要UTF8编码
	@return 是否成功设置环境变量
	*/
	bool auntec_set_environment_variable(const char* pEvName, const char* pEvValue);

	/*!
	@brief 获取环境变量
	@param [in] evName 变量名 UTF8编码
	@return 返回环境变量值,UTF8编码
	*/
	string auntec_get_environment_variable(const char* pEvName);

	/*!
	@brief 删除环境变量
	@param name 环境变量名
	@return 删除成功或者失败
	*/
	bool auntec_delete_environment_variable(const char* pEvName);

#ifdef WIN32
	/*!
	定时器回调
	*/
	typedef void (*auntec_timer_proc_t)(void* pData);

	/*!
	安装定时器
	*/
	void* auntec_install_timer(unsigned int ms, auntec_timer_proc_t onTimer, void* pData);

	/*!
	卸载定时器
	*/
	void auntec_uninstall_timer(void* pTimer);
#endif

	/*!
	@brief 加载DLL
	@param path DLL的路径名
	@return 成功DLL的句柄，失败返回NULL
	*/
	void* auntec_load_dll(const char* path);

	/*!
	@brief 获取函数地址
	@param hModule DLL的句柄
	@param proc 函数名
	@return 成功返回函数的入口地址，失败返回NULL
	*/
	void* auntec_get_proc_addr(void* hModule, const char* proc);

	/*!
	@brief 释放DLL
	@param hModule DLL句柄
	*/
	void auntec_free_dll(void* hModule);

	/*!
	@brief 设置DLL的加载路径
	@param path 文件夹路径
	*/
	void auntec_dll_set_load_path(const char* path);

	/*!
	@brief 创建一个GUID字符串，格式：{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X} 示例：{6984FDC9-9608-483C-BCDF-519BE652CEAD}
	@param haveBrace 是否包含{}
	@return GUID字符串
	*/
	string auntec_create_guid(bool haveBrace=true);
#ifdef WIN32
	wstring auntec_create_guidw(bool haveBrace=true);
#endif

	/*!
	@brief sleep
	@param nMilliseconds sleep的数值, 单位毫秒 
	*/
	void auntec_sleep(uint32_t nMilliseconds);

	/*!
	@brief
	[1] Microsoft Windows OS \n
	The function retrieves the system time, in milliseconds. \n 
	The system time is the time elapsed since Windows was started.
	@return 毫秒值 
	*/
	uint32_t auntec_getticks();

#ifdef WIN32
	/*!
	@brief 检测操作系统位数
	@return 返回true则表示当前系统为64位
	*/
	bool auntec_os_is64bit();

	typedef enum{
		AUNTEC_OS_TYPE_UNKNOWN = -1,
		AUNTEC_OS_TYPE_XP,
		AUNTEC_OS_TYPE_VISTA,
		AUNTEC_OS_TYPE_WIN7,
		AUNTEC_OS_TYPE_WIN7_SPX,
		AUNTEC_OS_TYPE_WIN8,
		AUNTEC_OS_TYPE_WIN10,
		AUNTEC_OS_TYPE_WIN_OTHER,
		AUNTEC_OS_TYPE_MACOS
	}AuntecOSType;

	/*!
	@brief 检测操作系统类型
	@return 返回当前操作系统类型，可以查看AuntecOSType
	*/
	AuntecOSType auntec_os_type();

	/*!
	@brief 获取操作系统名称
	@return 操作系统名称
	*/
	string auntec_system_name();

	/*!
	@brief 获取操作系统版本
	@return 操作系统版本
	*/
	string auntec_system_version();
	
	/*!
	@brief 获取app名称
	@return app名称
	*/
	string auntec_app_name();

	/*!
	@brief 获取app版本号
	@return app版本号
	*/
	string auntec_app_version();
	
	/*!
	@brief 获取mac地址
	@return mac地址
	*/
	string auntec_mac_address();
#endif
}

#endif
