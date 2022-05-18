#ifndef system_os_h__
#define system_os_h__


#include <string>

//#include "boost_shared_ptr.h"
//#include "base_object.h"

namespace libCommonUtils
{

 //CLASS_BOOST_SHARED_PTR(CSystemOS)

class CSystemOS
{
public:
	///< CPU 内存 等硬件信息
	static std::string human_hardware();
	///< 当前状态：电源信息，当前CPU主频
	static std::string human_current_state();
};

//#if defined(D_OS_WIN)
	///< 判断是否为64位系统
	bool Is64BitWindows();
//	/* 获取系统盘符 如 C:\ */`
//	std::string GetWindowsSystemDrive();
//	///< 判断是否为Win10及以上系统
//	bool IsWindows10OrAbove();
//	///< 判断是否为Win8.1及以上系统
//	bool IsWindows81OrAbove();
//	///< 判断是否为Win8及以上系统
//	bool IsWindows8OrAbove();
//	///< 判断是否为Win7及以上系统
//	bool IsWindows7OrAbove();
//	///< 判断是否为Win7系统
//	bool IsWindows7();
//#endif

std::string GetSystemVersionInfo();

std::string winOSVersion();

std::string winOSDisplayName();

std::string winOSArchitecture();

//int GetCPUCoreCount();

///< 根据系统字体名，获取字体文件路径
std::string GetSystemFontFile(const std::string &faceName);

}

#endif // system_os_h__
