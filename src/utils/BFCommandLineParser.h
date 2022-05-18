/*
软件命令行解析
1.自启动                auto  //兼容老版本，不变，不用短命令
2.绿色包打开素材库路径   -o=path
3.绿色包埋单ini路径      -b=path
*/

#pragma once
#include "utilsexport.h"
#include <QObject>

class UTILS_EXPORT BFCommandLineParser{
public:
   //@brief:是否有软件自启动命令行
   static bool IsSetAutoRun();
   //@brief:获取软件自启动命令行数值
   static QString GetAutoRunValue();


   //@brief:是否有绿色包打开素材库路径
   static bool IsSetGreenPacketLibPath();
   //@brief:获取绿色包打开素材库路径
   static QString GetGreenPacketLibPath();


    //@brief:是否有绿色包埋点配置文件
   static bool IsSetGreenPacketBuryPointIniPath();
   //@brief:获取软件绿色包配置文件
   static QString GetGreenPacketBuryPointIniPath();


private:
	BFCommandLineParser();
	~BFCommandLineParser();
    BFCommandLineParser(BFCommandLineParser&)=delete;
    BFCommandLineParser&operator=(BFCommandLineParser&)= delete;
};
