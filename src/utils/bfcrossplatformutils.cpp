#include "bfcrossplatformutils.h"
#include <QString>
#include <string.h>
#if defined (_WIN32)
#include <windows.h>
#pragma comment(lib, "version.lib")
#endif


#if defined(WIN32)
    #include <Windows.h>
    #include <process.h>
    #include <mmsystem.h>
    #include <objbase.h>
#else
    #include <dlfcn.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <limits.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/param.h>
    #include <sys/sysctl.h>
    #include <uuid/uuid.h>
    #include <unistd.h>
#endif

#ifdef __APPLE__
#include "Platform/MacOs/SystemUtilsCInterface.h"
#include <mach/mach_time.h>
#include <mach-o/dyld.h>
#endif

typedef struct LANGANDCODEPAGE__ {
    uint16_t wLanguage;
    uint16_t wCodePage;
}LANGANDCODEPAGE;

QString BfCrossPlatformUtils::AppVersion()
{
#ifdef WIN32
    QString qStrVer;
    std::wstring version;
    wchar_t* pBuf = NULL;
    //DWORD dwHandle = 0;
    uint32_t dwInfoSize = 0;
    uint32_t cbTranslate = 0;
    uint32_t dwBytes = 0;
    wchar_t* lpBuffer = NULL;
    LANGANDCODEPAGE* lpTranslate = NULL;
    wchar_t filePath[4096] = { 0 };
    wchar_t verBuf[4096] = { 0 };


    DWORD dwHandle = 0;
    if (GetModuleFileNameW(NULL, filePath, 4095) <= 0) {
        goto err_proc;
    }

    dwInfoSize = GetFileVersionInfoSizeW(filePath, &dwHandle);
    if (dwInfoSize <= 0) {
        goto err_proc;
    }

    pBuf = (wchar_t*)malloc((dwInfoSize + 1) * 2);
    if (NULL == pBuf) {
        goto err_proc;
    }

    if (!GetFileVersionInfoW(filePath, 0, dwInfoSize, pBuf)) {
        goto err_proc;
    }

    if (!VerQueryValueW(pBuf, L"\\VarFileInfo\\Translation", (LPVOID*)&lpTranslate, &cbTranslate)) {
        goto err_proc;
    }

    wsprintfW(verBuf, L"\\StringFileInfo\\%04x%04x\\%s", lpTranslate->wLanguage, lpTranslate->wCodePage, L"ProductVersion");
    if (VerQueryValueW(pBuf, verBuf, (LPVOID*)&lpBuffer, &dwBytes)) {
        version = lpBuffer;
    }

err_proc:
    if (pBuf != NULL) {
        free(pBuf);
    }
    if (version.size() > 0) {
        qStrVer = QString::fromStdWString(version);
        qStrVer = qStrVer.replace(",",".");
    }else
    {
        qStrVer = "1.0.0.1";
    }

    return qStrVer;
#endif

#ifdef __APPLE__
    std::string tmp(getMacAppVersion());

    return QString::fromStdString(tmp);
#endif

}

std::string BfCrossPlatformUtils::GetTmpFileName(const std::string &folder, const std::string &ext)
{
#ifdef WIN32
    wchar_t path[MAX_PATH];
    std::wstring folder_wide;
    if (folder.empty()) {
        wchar_t folder_wide_arr[MAX_PATH+1];
        uint32_t nSize = GetTempPathW(MAX_PATH, folder_wide_arr);
        if (nSize == 0) {
            return "";
        }
            folder_wide = folder_wide_arr;
        } else {
            folder_wide = QString::fromStdString(folder.c_str()).toStdWString();
        }
        if (GetTempFileNameW(folder_wide.c_str(), L"", 0, path) == 0) {
            return "";
        }
        std::wstring r = path;
        DeleteFileW(path);
        r += QString::fromStdString(ext.c_str()).toStdWString();
        return QString::fromStdWString(r.c_str()).toStdString();
#else
  char* pfull=NULL;
  if (folder.empty()) {
    pfull = tempnam(NULL, "tmpf");
  } else {
    //pfull = tempnam(utf8_to_local(folder.c_str()).c_str(), "tmpf");
    pfull = tempnam(folder.c_str(), "tmpf");
  }
  if (pfull == NULL) {
    //ThrowUnexpected();
    return "";
  }
  //MallocAllocator ma;
  //ma.Attach(pfull);
  //string r = local_to_utf8(pfull);
  std::string r = pfull;
  free(pfull);
  return r + ext;
#endif
}
