/*
��������н���
1.������                auto  //�����ϰ汾�����䣬���ö�����
2.��ɫ�����زĿ�·��   -o=path
3.��ɫ����ini·��      -b=path
*/

#pragma once
#include "utilsexport.h"
#include <QObject>

class UTILS_EXPORT BFCommandLineParser{
public:
   //@brief:�Ƿ������������������
   static bool IsSetAutoRun();
   //@brief:��ȡ�����������������ֵ
   static QString GetAutoRunValue();


   //@brief:�Ƿ�����ɫ�����زĿ�·��
   static bool IsSetGreenPacketLibPath();
   //@brief:��ȡ��ɫ�����زĿ�·��
   static QString GetGreenPacketLibPath();


    //@brief:�Ƿ�����ɫ����������ļ�
   static bool IsSetGreenPacketBuryPointIniPath();
   //@brief:��ȡ�����ɫ�������ļ�
   static QString GetGreenPacketBuryPointIniPath();


private:
	BFCommandLineParser();
	~BFCommandLineParser();
    BFCommandLineParser(BFCommandLineParser&)=delete;
    BFCommandLineParser&operator=(BFCommandLineParser&)= delete;
};
