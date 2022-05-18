#include "system_os.h"
#include <assert.h>
#include <algorithm>
#include <sstream>
#include<vector>
#include<iomanip>
#include <algorithm>
#include<QString>


using namespace std;


namespace libCommonUtils
{

struct CPUInfo
{
	std::string model;
	int speed;
	struct CPUTimes
	{
		uint64_t user;
		uint64_t nice;
		uint64_t sys;
		uint64_t idle;
		uint64_t irq;
	} cpu_times;
};

#if defined(D_OS_MACOS)
    #include <sys/types.h>
    #include <sys/sysctl.h>
#endif
    
//#if defined(D_OS_WIN)

#include <ntstatus.h>
#include <Windows.h>
#include <powrprof.h>
#include <winreg.h>

#pragma comment(lib, "Powrprof.lib")
#pragma comment(lib,"Advapi32.lib")

typedef struct _PROCESSOR_POWER_INFORMATION
{
	ULONG Number;
	ULONG MaxMhz;
	ULONG CurrentMhz;
	ULONG MhzLimit;
	ULONG MaxIdleState;
	ULONG CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION {
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER DpcTime;
    LARGE_INTEGER InterruptTime;
    ULONG InterruptCount;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

#ifndef _NTDEF_
  typedef LONG NTSTATUS;
  typedef NTSTATUS *PNTSTATUS;
#endif

#ifndef NT_SUCCESS
# define NT_SUCCESS(status) (((NTSTATUS) (status)) >= 0)
#endif

#ifndef NTAPI
	#define NTAPI __stdcall
#endif // !NTAPI


#ifndef SystemProcessorPerformanceInformation
# define SystemProcessorPerformanceInformation 8
#endif

typedef NTSTATUS (NTAPI *pfnNtQuerySystemInformation)
                 (UINT SystemInformationClass,
                  PVOID SystemInformation,
                  ULONG SystemInformationLength,
                  PULONG ReturnLength);

static pfnNtQuerySystemInformation s_NtQuerySystemInformationline = NULL;

static pfnNtQuerySystemInformation DyGetNtQuerySystemInformationline()
{
	if (!s_NtQuerySystemInformationline) {
		HMODULE ntdll_module = GetModuleHandleA("ntdll.dll");
		if (ntdll_module) {
			s_NtQuerySystemInformationline = (pfnNtQuerySystemInformation)GetProcAddress(
				ntdll_module,
				"NtQuerySystemInformation");
			assert(s_NtQuerySystemInformationline);
		} else {
			assert(0);
		}
	}

	return s_NtQuerySystemInformationline;

}

static inline BOOL RTLGetVersionEx(OSVERSIONINFOEXW& result)
{
	//result = { sizeof(OSVERSIONINFOEXW), 0, 0, 0, 0, {'\0'}};
	memset(&result, 0, sizeof(result));
	result.dwOSVersionInfoSize = sizeof(result);
#ifndef D_OS_WINCE
#define GetProcAddressA GetProcAddress
#endif

	// GetModuleHandle is not supported in WinRT and linking to it at load time
	// will not pass the Windows App Certification Kit... but it exists and is functional,
	// so use some unusual but widely used techniques to get a pointer to it
#ifdef D_OS_WINRT
	// 1. Get HMODULE of kernel32.dll, using the address of some function exported by that DLL
	HMODULE kernelModule = moduleHandleForFunction(reinterpret_cast<LPCVOID>(VirtualQuery));
	if (D_UNLIKELY(!kernelModule))
		return FALSE;

	// 2. Get pointer to GetModuleHandle so we can then load other arbitrary modules (DLLs)
	typedef HMODULE(WINAPI *GetModuleHandleFunction)(LPCWSTR);
	GetModuleHandleFunction pGetModuleHandle = reinterpret_cast<GetModuleHandleFunction>(
		GetProcAddressA(kernelModule, "GetModuleHandleW"));
	if (D_UNLIKELY(!pGetModuleHandle))
		return FALSE;
#else
#define pGetModuleHandle GetModuleHandleW
#endif

#ifndef D_OS_WINCE
	HMODULE ntdll = pGetModuleHandle(L"ntdll.dll");
	//if (D_UNLIKELY(!ntdll))
	//	return FALSE;

	// NTSTATUS is not defined on WinRT
	typedef LONG NTSTATUS;
	typedef NTSTATUS (NTAPI *RtlGetVersionFunction)(LPOSVERSIONINFOEXW);

	// RtlGetVersion is documented public API but we must load it dynamically
	// because linking to it at load time will not pass the Windows App Certification Kit
	// https://msdn.microsoft.com/en-us/library/windows/hardware/ff561910.aspx
	RtlGetVersionFunction pRtlGetVersion = reinterpret_cast<RtlGetVersionFunction>(
		GetProcAddressA(ntdll, "RtlGetVersion"));
	//if (D_UNLIKELY(!pRtlGetVersion))
	//	return FALSE;

	// GetVersionEx() has been deprecated in Windows 8.1 and will return
	// only Windows 8 from that version on, so use the kernel API function.
	pRtlGetVersion(&result); // always returns STATUS_SUCCESS
#else // !Q_OS_WINCE
	GetVersionEx(&result);
#endif

	return TRUE;
}

std::string winOSDisplayName() {
  OSVERSIONINFOEXW vi;  // OSVERSIONINFOEX is supported starting at Windows 2000
  vi.dwOSVersionInfoSize = sizeof(vi);
  if (RTLGetVersionEx(vi) == 0) {
    return "winOSDisplayName RTLGetVersionEx failed.";
  }
  switch (vi.dwMajorVersion) {
    case 10:
      switch (vi.dwMinorVersion) {
        case 0:
          return vi.wProductType == VER_NT_WORKSTATION ? "Windows 10"
                                                       : "Windows Server 2016";
      }
    case 6:
      switch (vi.dwMinorVersion) {
        case 0:
          return vi.wProductType == VER_NT_WORKSTATION ? "Windows Vista"
                                                       : "Windows Server 2008";
        case 1:
          return vi.wProductType == VER_NT_WORKSTATION
                     ? "Windows 7"
                     : "Windows Server 2008 R2";
        case 2:
          return vi.wProductType == VER_NT_WORKSTATION ? "Windows 8"
                                                       : "Windows Server 2012";
        case 3:
          return vi.wProductType == VER_NT_WORKSTATION
                     ? "Windows 8.1"
                     : "Windows Server 2012 R2";
        default:
          return "Unknown";
      }
    case 5:
      switch (vi.dwMinorVersion) {
        case 0:
          return "Windows 2000";
        case 1:
          return "Windows XP";
        case 2:
          return "Windows Server 2003/Windows Server 2003 R2";
        default:
          return "Unknown";
      }
    default:
      return "Unknown";
  }
}

static std::string read_reg_string(HKEY rootKey, LPCSTR szSubKey, LPCSTR szKeyName)
{
	std::string retValue = "";
	char location[1024];
	HKEY hKey = NULL;
	long ret = RegOpenKeyExA(rootKey,szSubKey,NULL, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &hKey);
	if (ret == ERROR_SUCCESS)
	{
		DWORD dwLength = 1024;
		ret = RegQueryValueExA(hKey, szKeyName, NULL, NULL, (LPBYTE)location, &dwLength);//���һ������������Ϊ��
		if (ret == ERROR_SUCCESS)
		{
			retValue = location;
		}
	}
	if (hKey) {
		RegCloseKey(hKey);
	}
	return retValue;
}

static uint32_t read_reg_int(HKEY rootKey, LPCSTR szSubKey, LPCSTR szKeyName)
{
	uint32_t retValue = -1;
	HKEY hKey = NULL;
	long ret = RegOpenKeyExA(rootKey,szSubKey,
		NULL, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &hKey);
	if (ret == ERROR_SUCCESS) {
		uint32_t location = -1;
		DWORD dwLength = sizeof(location);
		ret = RegQueryValueExA(hKey, szKeyName, NULL, NULL, (LPBYTE)&location, &dwLength);//���һ������������Ϊ��
		if (ret == ERROR_SUCCESS) {
			retValue = location;
		}
	}
	if (hKey) {
		RegCloseKey(hKey);
	}
	return retValue;
}

std::string winOSVersion()
{
	OSVERSIONINFOEXW vi;
	vi.dwOSVersionInfoSize = sizeof(vi);
	if (RTLGetVersionEx(vi) == 0) {
		return "winOSVersion RTLGetVersionEx failed.";
	}

	std::string ret;
	if (vi.dwMajorVersion >= 10)
	{
		std::string win_edition_id = read_reg_string(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "EditionID");
		std::string win_release_id = read_reg_string(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ReleaseId");
		uint32_t win_ubr = read_reg_int(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "UBR");
		QString need_str = QString("%1.%2 (%3,%4, Build %5.%6)").arg(vi.dwMajorVersion).arg(vi.dwMinorVersion).arg(QString::fromStdString(win_edition_id)).arg(QString::fromStdString(win_release_id)).arg(vi.dwBuildNumber & 0xFFFF).arg(win_ubr);
		ret = need_str.toStdString();
	}
	else
	{
		//boost::format fmt("%d.%d (Build %d)");
		//fmt % vi.dwMajorVersion % vi.dwMinorVersion % (vi.dwBuildNumber & 0xFFFF);
		QString need_str = QString("%1.%2 (Build %3)").arg(QString::number(vi.dwMajorVersion)).arg(QString::number(vi.dwMinorVersion)).arg(QString::number(vi.dwBuildNumber & 0xFFFF));
		ret = need_str.toStdString();
	}
	return ret;
}

std::string winOSArchitecture()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	switch (si.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL:
		return "IA32";
	case PROCESSOR_ARCHITECTURE_MIPS:
		return "MIPS";
	case PROCESSOR_ARCHITECTURE_ALPHA:
		return "ALPHA";
	case PROCESSOR_ARCHITECTURE_PPC:
		return "PPC";
	case PROCESSOR_ARCHITECTURE_IA64:
		return "IA64";
#ifdef PROCESSOR_ARCHITECTURE_IA32_ON_WIN64
	case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
		return "IA64/32";
#endif
#ifdef PROCESSOR_ARCHITECTURE_AMD64
	case PROCESSOR_ARCHITECTURE_AMD64:
		return "AMD64";
#endif
	default:
		return "Unknown";
	}
}

bool Is64BitWindows()
{
	HMODULE hmoudle = LoadLibraryW(L"kernel32");
	if (NULL == hmoudle) {
		return false;
}

	typedef void (WINAPI* LPFN_PGNSI)(LPSYSTEM_INFO);
	LPFN_PGNSI lpfnGNSI = (LPFN_PGNSI)GetProcAddress(hmoudle, "GetNativeSystemInfo");
	if (NULL != lpfnGNSI) {
		SYSTEM_INFO si = { 0 };
		lpfnGNSI(&si);
		if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
			return true;
		}
	} else {
		typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
		LPFN_ISWOW64PROCESS lpfnIsWOW64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(hmoudle, "IsWow64Process");
		if (NULL != lpfnIsWOW64Process) {
			BOOL b64 = FALSE;
			if (lpfnIsWOW64Process(GetCurrentProcess(), &b64) && b64) {
				return true;
			}
		}
	}
	return false;
}
//
//std::string GetWindowsSystemDrive()
//{
//	std::string ret = "C:\\";
//	char str[MAX_PATH] = {0};
//	if (GetWindowsDirectoryA(str, MAX_PATH) > 0) {
//		ret = str;
//		ret = ExtractFileDrive(ret);
//		ret += "\\";
//	}
//	return ret;
//}
//
//bool IsWindows10OrAbove()
//{
//	OSVERSIONINFOEXW vi;
//	vi.dwOSVersionInfoSize = sizeof(vi);
//	if (RTLGetVersionEx(vi) == 0) {
//		return false;
//	}
//	return vi.dwMajorVersion > 10 || (vi.dwMajorVersion == 10 && vi.dwMinorVersion >= 0);
//}
//
//bool IsWindows81OrAbove()
//{
//	OSVERSIONINFOEXW vi;
//	vi.dwOSVersionInfoSize = sizeof(vi);
//	if (RTLGetVersionEx(vi) == 0) {
//		return false;
//	}
//	return vi.dwMajorVersion > 6 || (vi.dwMajorVersion == 6 && vi.dwMinorVersion >= 3);
//}
//
//bool IsWindows8OrAbove()
//{
//	OSVERSIONINFOEXW vi;
//	vi.dwOSVersionInfoSize = sizeof(vi);
//	if (RTLGetVersionEx(vi) == 0) {
//		return false;
//	}
//	return vi.dwMajorVersion > 6 || (vi.dwMajorVersion == 6 && vi.dwMinorVersion >= 2);
//}
//
//bool IsWindows7OrAbove()
//{
//	OSVERSIONINFOEXW vi;
//	vi.dwOSVersionInfoSize = sizeof(vi);
//	if (RTLGetVersionEx(vi) == 0) {
//		return false;
//	}
//	return vi.dwMajorVersion > 6 || (vi.dwMajorVersion == 6 && vi.dwMinorVersion >= 1);
//}
//
//bool IsWindows7()
//{
//	OSVERSIONINFOEXW vi;
//	vi.dwOSVersionInfoSize = sizeof(vi);
//	if (RTLGetVersionEx(vi) == 0) {
//		return false;
//	}
//	return (vi.dwMajorVersion == 6 && vi.dwMinorVersion == 1);
//}

static uint64_t freemem()
{
	MEMORYSTATUSEX memory_status;
	memory_status.dwLength = sizeof(memory_status);
	if (!GlobalMemoryStatusEx(&memory_status)) {
		return -1;
	}
	return (uint64_t)memory_status.ullAvailPhys;
}

static uint64_t totalmem()
{
	MEMORYSTATUSEX memory_status;
	memory_status.dwLength = sizeof(memory_status);
	if (!GlobalMemoryStatusEx(&memory_status)) {
		return -1;
	}
	return (uint64_t)memory_status.ullTotalPhys;
}
//
//static bool cpus(std::vector<CPUInfo>& cpu_infos)
//{
//	SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION* sppi;
//	DWORD sppi_size;
//	SYSTEM_INFO system_info;
//	DWORD cpu_count, r, i;
//	NTSTATUS status;
//	ULONG result_size;
//	CPUInfo cpuInfo;
//	bool err;
//
//	cpu_count = 0;
//	sppi = NULL;
//
//	pfnNtQuerySystemInformation NtQuerySystemInformationline  = DyGetNtQuerySystemInformationline();
//	if (!NtQuerySystemInformationline) {
//		return false;
//	}
//
//
//	GetSystemInfo(&system_info);
//	cpu_count = system_info.dwNumberOfProcessors;
//
//	sppi_size = cpu_count * sizeof(*sppi);
//	sppi = (SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION*)malloc(sppi_size);
//	if (sppi == NULL) {
//		err = false;
//		goto error;
//	}
//
//	status = NtQuerySystemInformationline(SystemProcessorPerformanceInformation,
//		sppi,
//		sppi_size,
//		&result_size);
//	if (!NT_SUCCESS(status)) {
//		err = false;
//		goto error;
//	}
//
//	assert(result_size == sppi_size);
//
//	for (i = 0; i < cpu_count; i++) {
//		WCHAR key_name[128];
//		HKEY processor_key;
//		DWORD cpu_speed;
//		DWORD cpu_speed_size = sizeof(cpu_speed);
//		WCHAR cpu_brand[256];
//		DWORD cpu_brand_size = sizeof(cpu_brand);
//		int len;
//
//		len = _snwprintf(key_name,
//			__ARRAY_SIZE__(key_name),
//			L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\%d",
//			i);
//
//		assert(len > 0 && len < __ARRAY_SIZE__(key_name));
//
//		r = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
//			key_name,
//			0,
//			KEY_QUERY_VALUE,
//			&processor_key);
//		if (r != ERROR_SUCCESS) {
//			err = false;
//			goto error;
//		}
//
//		if (RegQueryValueExW(processor_key,
//			L"~MHz",
//			NULL,
//			NULL,
//			(BYTE*)&cpu_speed,
//			&cpu_speed_size) != ERROR_SUCCESS) {
//			err = false;
//			RegCloseKey(processor_key);
//			goto error;
//		}
//
//		if (RegQueryValueExW(processor_key,
//			L"ProcessorNameString",
//			NULL,
//			NULL,
//			(BYTE*)&cpu_brand,
//			&cpu_brand_size) != ERROR_SUCCESS) {
//			err = false;
//			RegCloseKey(processor_key);
//			goto error;
//		}
//
//		RegCloseKey(processor_key);
//
//		CPUInfo* cpu_info = &cpuInfo;
//		cpu_info->speed = cpu_speed;
//		cpu_info->cpu_times.user = sppi[i].UserTime.QuadPart / 10000;
//		cpu_info->cpu_times.sys = (sppi[i].KernelTime.QuadPart -
//			sppi[i].IdleTime.QuadPart) / 10000;
//		cpu_info->cpu_times.idle = sppi[i].IdleTime.QuadPart / 10000;
//		cpu_info->cpu_times.irq = sppi[i].InterruptTime.QuadPart / 10000;
//		cpu_info->cpu_times.nice = 0;
//		cpu_info->model = wide_to_utf8(cpu_brand);
//		cpu_infos.push_back(cpuInfo);
//	}
//
//	free(sppi);
//
//	return true;
//
//error:
//	free(sppi);
//	return err;
//}

std::string GetSystemVersionInfo()
{
	char buffer[512] = "unsupport";
#if defined(D_OS_WIN)
	int32_t bit = Is64BitWindows() ? 64 : 32;
	sprintf(buffer, "%s, %s, arch = %s, %dbit",
		winOSDisplayName().c_str(),        //系统展示名
		winOSVersion().c_str(),
		winOSArchitecture().c_str(), bit);   //架构
#endif
	return buffer;
}

//int GetCPUCoreCount()
//{
//#if defined(D_OS_WIN)
//	int count = 1;
//	SYSTEM_INFO si;
//	GetSystemInfo(&si);
//	count = std::max((int)si.dwNumberOfProcessors, count);
//	return count;
//#elif defined(D_OS_MACOS)
//	unsigned count;
//	std::size_t size = sizeof(count);
//	if (sysctlbyname("hw.ncpu", &count, &size, 0, 0))
//		return 1;
//	else
//		return count;
//#else
//	///< FIXME ƽ̨δʵ��
//	assert(0);
//	return -1;
//#endif
//}

#if defined(D_OS_WIN)

#define MAKE_TAG(ch1, ch2, ch3, ch4) (\
	(((uint32_t)(ch4)) << 24) | \
	(((uint32_t)(ch3)) << 16) | \
	(((uint32_t)(ch2)) << 8) | \
	((uint32_t)(ch1)) \
	)

static inline uint16_t getUShort(const unsigned char *p)
{
	uint16_t val;
	val = *p++ << 8;
	val |= *p;

	return val;
}

static std::wstring getEnglishName(const unsigned char *table, uint32_t bytes)
{
	std::wstring i18n_name;
	enum {
		NameRecordSize = 12,
		FamilyId = 1,
		MS_LangIdEnglish = 0x009
	};

	// get the name table
	uint16_t count;
	uint16_t string_offset;
	const unsigned char *names;

	int microsoft_id = -1;
	int apple_id = -1;
	int unicode_id = -1;

	if (getUShort(table) != 0)
		goto error;

	count = getUShort(table + 2);
	string_offset = getUShort(table + 4);
	names = table + 6;

	if (string_offset >= bytes || 6 + count * NameRecordSize > string_offset)
		goto error;

	for (int i = 0; i < count; ++i) {
		// search for the correct name entry

		uint16_t platform_id = getUShort(names + i * NameRecordSize);
		uint16_t encoding_id = getUShort(names + 2 + i * NameRecordSize);
		uint16_t language_id = getUShort(names + 4 + i * NameRecordSize);
		uint16_t name_id = getUShort(names + 6 + i * NameRecordSize);

		if (name_id != FamilyId)
			continue;

		enum {
			PlatformId_Unicode = 0,
			PlatformId_Apple = 1,
			PlatformId_Microsoft = 3
		};

		uint16_t length = getUShort(names + 8 + i * NameRecordSize);
		uint16_t offset = getUShort(names + 10 + i * NameRecordSize);
		if (DWORD(string_offset + offset + length) >= bytes)
			continue;

		if ((platform_id == PlatformId_Microsoft
			&& (encoding_id == 0 || encoding_id == 1))
			&& (language_id & 0x3ff) == MS_LangIdEnglish
			&& microsoft_id == -1)
			microsoft_id = i;
		// not sure if encoding id 4 for Unicode is utf16 or ucs4...
		else if (platform_id == PlatformId_Unicode && encoding_id < 4 && unicode_id == -1)
			unicode_id = i;
		else if (platform_id == PlatformId_Apple && encoding_id == 0 && language_id == 0)
			apple_id = i;
	}
	{
		bool unicode = false;
		int id = -1;
		if (microsoft_id != -1) {
			id = microsoft_id;
			unicode = true;
		} else if (apple_id != -1) {
			id = apple_id;
			unicode = false;
		} else if (unicode_id != -1) {
			id = unicode_id;
			unicode = true;
		}
		if (id != -1) {
			uint16_t length = getUShort(names + 8 + id * NameRecordSize);
			uint16_t offset = getUShort(names + 10 + id * NameRecordSize);
			if (unicode) {
				// utf16

				length /= 2;
				i18n_name.resize(length);
				const unsigned char *string = table + string_offset + offset;
				for (int i = 0; i < length; ++i)
					i18n_name[i] = getUShort(string + 2 * i);
			} else {
				// Apple Roman

				i18n_name.resize(length);
				const unsigned char *string = table + string_offset + offset;
				for (int i = 0; i < length; ++i)
					i18n_name[i] = getUShort(string + i);
			}
		}
	}
error:
	return i18n_name;
}

std::wstring getEnglishName(const std::wstring& familyName)
{
	std::wstring i18n_name;

	HDC hdc = GetDC(0);
	LOGFONTW lf;
	memset(&lf, 0, sizeof(lf));
	size_t copy_size = LF_FACESIZE < familyName.length() ? LF_FACESIZE : familyName.length();
	memcpy(lf.lfFaceName, familyName.data(), copy_size * sizeof(wchar_t));
	lf.lfCharSet = DEFAULT_CHARSET;
	HFONT hfont = CreateFontIndirectW(&lf);

	if (!hfont) {
		ReleaseDC(0, hdc);
		return std::wstring();
	}

	HGDIOBJ oldobj = SelectObject(hdc, hfont);

	const DWORD name_tag = MAKE_TAG('n', 'a', 'm', 'e');

	// get the name table
	unsigned char *table = 0;

	DWORD bytes = GetFontData(hdc, name_tag, 0, 0, 0);
	if (bytes == GDI_ERROR) {
		// ### Unused variable
		/* int err = GetLastError(); */
		goto error;
	}

	table = new unsigned char[bytes];
	GetFontData(hdc, name_tag, 0, table, bytes);
	if (bytes == GDI_ERROR)
		goto error;

	i18n_name = getEnglishName(table, bytes);
error:
	delete[] table;
	SelectObject(hdc, oldobj);
	DeleteObject(hfont);
	ReleaseDC(0, hdc);

	return i18n_name;
}

#endif

std::string GetSystemFontFile(const std::string &faceName)
{
	std::string ret = "";
#if defined(D_OS_WIN)
	static const LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	HKEY hKeyLocal = NULL;
	HKEY hKeyUser = NULL;
	LONG result;
	std::wstring wsFontFile;
	do 
	{
		std::wstring wsFaceName = MoyeaBased::utf8_to_wide(faceName.c_str());  
		std::wstring wsFontEngName = getEnglishName(wsFaceName);
		if (wsFontEngName.empty()) {
			assert(0);
			break;
		}

		// Open Windows font registry key
		result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKeyLocal);
		if (result != ERROR_SUCCESS) {
			assert(0);
			break;
		}

		DWORD maxValueNameSize, maxValueDataSize;
		result = RegQueryInfoKeyW(hKeyLocal, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
		if (result != ERROR_SUCCESS) {
			assert(0);
			break;
		}

		DWORD valueIndex = 0;
		LPWSTR valueName = new WCHAR[maxValueNameSize];
		LPBYTE valueData = new BYTE[maxValueDataSize];
		DWORD valueNameSize, valueDataSize, valueType;

		// Look for a matching font name
		do {

			wsFontFile.clear();
			valueDataSize = maxValueDataSize;
			valueNameSize = maxValueNameSize;

			result = RegEnumValueW(hKeyLocal, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

			valueIndex++;

			if (result != ERROR_SUCCESS || valueType != REG_SZ) {
				continue;
			}

			std::wstring wsValueName(valueName, valueNameSize);
			// Found a match
			if (_wcsnicmp(wsFontEngName.c_str(), wsValueName.c_str(), wsFontEngName.length()) == 0) {
				wsFontFile.assign((LPWSTR)valueData, valueDataSize);
				break;
			}

			// ʹ�ô����ַ�����һ�Σ���ֹĳЩ���������Ҳ���
			if (_wcsnicmp(wsFaceName.c_str(), wsValueName.c_str(), wsFaceName.length()) == 0) {
				wsFontFile.assign((LPWSTR)valueData, valueDataSize);
				break;
			}

		} while (result != ERROR_NO_MORE_ITEMS);

		delete[] valueName;
		delete[] valueData;

		if (!wsFontFile.empty()) {
			break;
		}

		// Open Windows font registry key
		result = RegOpenKeyExW(HKEY_CURRENT_USER, fontRegistryPath, 0, KEY_READ, &hKeyLocal);
		if (result != ERROR_SUCCESS) {
			assert(0);
			break;
		}

		result = RegQueryInfoKeyW(hKeyLocal, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
		if (result != ERROR_SUCCESS) {
			assert(0);
			break;
		}

		valueIndex = 0;
		valueName = new WCHAR[maxValueNameSize];
		valueData = new BYTE[maxValueDataSize];

		// Look for a matching font name
		do {

			wsFontFile.clear();
			valueDataSize = maxValueDataSize;
			valueNameSize = maxValueNameSize;

			result = RegEnumValueW(hKeyLocal, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

			valueIndex++;

			if (result != ERROR_SUCCESS || valueType != REG_SZ) {
				continue;
			}

			std::wstring wsValueName(valueName, valueNameSize);

			// Found a match
			if (_wcsnicmp(wsFontEngName.c_str(), wsValueName.c_str(), wsFontEngName.length()) == 0) {
				wsFontFile.assign((LPWSTR)valueData, valueDataSize);
				break;
			}

			// ʹ�ô����ַ�����һ�Σ���ֹĳЩ���������Ҳ���
			if (_wcsnicmp(wsFaceName.c_str(), wsValueName.c_str(), wsFaceName.length()) == 0) {
				wsFontFile.assign((LPWSTR)valueData, valueDataSize);
				break;
			}

		} while (result != ERROR_NO_MORE_ITEMS);

		delete[] valueName;
		delete[] valueData;
	} while (0);

	do {
		if (wsFontFile.empty()) {
			assert(0);
			break;
		}
		for (size_t ii = 0; ii < wsFontFile.size(); ii++) {
			if (wsFontFile[ii] == L'\0') {
				wsFontFile.erase(ii);
				break;
			}
		}

		// Build full font file path
		WCHAR winDir[MAX_PATH];
		GetWindowsDirectoryW(winDir, MAX_PATH);

		std::wstringstream ss;
		ss << winDir << "\\Fonts\\" << wsFontFile;
		wsFontFile = ss.str();

		ret = MoyeaBased::wide_to_utf8(wsFontFile.c_str());

	} while (0);

	if (hKeyLocal) {
		RegCloseKey(hKeyLocal);
	}
	hKeyLocal = NULL;

	if (hKeyUser) {
		RegCloseKey(hKeyUser);
	}
	hKeyUser = NULL;

#elif defined(D_OS_MACOS)
	assert(0);
#else
	assert(0);
#endif
	return ret;
}

std::string CSystemOS::human_hardware()
{
#if defined(D_OS_WIN)
	uint64_t totalMem = totalmem() / 1024 / 1024;
	uint64_t freeMem = freemem() / 1024 / 1024;
	std::vector<CPUInfo> cpu_infos;
	std::stringstream ss;

	uint64_t idle = 0;
	uint64_t user = 0;
	uint64_t sys = 0;
	for (uint32_t i = 0; i < cpu_infos.size(); i++) {
		CPUInfo& cpu = cpu_infos[i];
		idle += cpu.cpu_times.idle;
		user += cpu.cpu_times.user;
		sys += cpu.cpu_times.sys;
	}

	uint64_t total = idle + user + sys;
	double fuser, fsys, fidle;
	fuser = double(user) / total * 100;
	fsys = double(sys) / total * 100;
	fidle = double(idle) / total * 100;

	std::stringstream cpu_usage;	// user = 2.15, sys = 6.38, idle = 93.15
	cpu_usage << std::fixed << std::setprecision(2);
	cpu_usage << "user = " << fuser << ", sys = " << fsys << ",idle = " << fidle;
	ss << "[cpu]" << " count = " << cpu_infos.size() << ", usage = " << cpu_usage.str() << std::endl;
	for (uint32_t i = 0; i < cpu_infos.size(); i++) {
		CPUInfo& cpu = cpu_infos[i];
		ss << " ";
		ss << "model=" << cpu.model << ", ";
		ss << "speed=" << cpu.speed;
		ss << std::endl;
	}
	ss << "[memory]" << " total = " << totalMem << "(MB)" << ", free = " << freeMem << "(MB)";
	return ss.str();
#else 
	return "human_hardware : unsupport os!";
#endif
}


std::string CSystemOS::human_current_state()
{
#if defined(D_OS_WIN)
	std::stringstream ss;
	SYSTEM_POWER_STATUS power;
	BOOL bOK = GetSystemPowerStatus(&power);
	if (bOK)
	{
		//boost::format fmt("ACLineStatus = %d, BatteryFlag = %d, BatteryLifePercent = %d, BatteryLifeTime = %d(S), BatteryFullLifeTime = %d(S)");
		//fmt % (int)power.ACLineStatus % (int)power.BatteryFlag % (int)power.BatteryLifePercent % power.BatteryLifeTime % power.BatteryFullLifeTime;
		//ss << "[power] " << fmt.str() << std::endl;
		QString hand = "[power] ";
		QString background_color_str = QString("ACLineStatus = %1, BatteryFlag = %2, BatteryLifePercent = %3, BatteryLifeTime = %4(S), BatteryFullLifeTime = %5(S)").arg(QString::number((int)power.ACLineStatus)).arg(QString::number((int)power.BatteryFlag)).arg(QString::number((int)power.BatteryLifePercent)).arg(QString::number((int)power.BatteryLifeTime)).arg(QString::number((int)power.BatteryFullLifeTime));
		QString power_result_str = hand + background_color_str;
	}

	//SYSTEM_INFO si;
	//GetSystemInfo(&si);
	//CMallocAllocator buffer;
	//buffer.Malloc(sizeof(PROCESSOR_POWER_INFORMATION) * si.dwNumberOfProcessors);
	//PPROCESSOR_POWER_INFORMATION ppi = (PPROCESSOR_POWER_INFORMATION)buffer.GetHandle();
	//NTSTATUS status = CallNtPowerInformation(ProcessorInformation, NULL, 0, buffer.GetHandle(), buffer.Size());
	//if (status == STATUS_SUCCESS)
	//{
	//	ss << "[cpu]" << " count = " << si.dwNumberOfProcessors << std::endl;
	//	for (size_t ii = 0; ii < si.dwNumberOfProcessors; ii++)
	//	{
	//		PPROCESSOR_POWER_INFORMATION pi = &ppi[ii];
	//		//boost::format fmt("Number = %d, MaxMhz = %d, CurrentMhz = %d, MhzLimit = %d, MaxIdleState = %d, CurrentIdleState = %d");
	//		//fmt % pi->Number % pi->MaxMhz % pi->CurrentMhz % pi->MaxMhz % pi->MaxIdleState % pi->CurrentIdleState;
	//		//ss << " " << fmt.str() << std::endl;
	//	}
	//}
	//return ss.str();

	return "";
#else
	return "human_current_state : unsupport os!";
#endif
}
}
