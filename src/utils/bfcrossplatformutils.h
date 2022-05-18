#ifndef BFCROSSPLATFORMUTILS_H
#define BFCROSSPLATFORMUTILS_H

#include "utilsexport.h"
#include <string>
class UTILS_EXPORT BfCrossPlatformUtils
{
public:
    //获取应用版本号
    static QString AppVersion();
    //获取临时文件名
    static std::string GetTmpFileName(const std::string& folder, const std::string& ext);
};

#endif // BFCROSSPLATFORMUTILS_H
