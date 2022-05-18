#include "BFFontSetting.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

#pragma execution_character_set("utf-8") 

BFFont * BFFont::bf_font = 0;

BFFont * BFFont::GetInstance()
{
	if (bf_font == 0)
	{
		bf_font = new BFFont();
	}
	return bf_font;
}

void BFFont::SetLanguageMode(int mode)
{
	m_langeuge_mode = mode;
}

BFFont::BFFont()
{
	m_langeuge_mode = 0;
}

void BFFont::GetSetting()
{
	m_chinese_family = QString::fromUtf8("Microsoft Yahei");
	m_chinese_pointSize_level_Max = 30;
	m_chinese_pointSize_level_1 = 16;
	m_chinese_pointSize_level_2 = 14;
	m_chinese_pointSize_level_3 = 12;
	m_chinese_pointSize_level_Min = 8;

	m_english_family = QString::fromUtf8("Arial");
	m_english_pointSize_level_Max = 30;
	m_english_pointSize_level_1 = 20;
	m_english_pointSize_level_2 = 14;
	m_english_pointSize_level_3 = 10;
	m_english_pointSize_level_Min = 8;

	m_digital_family = QString::fromUtf8("黑体");
	m_digital_pointSize_level_Max2 = 50;
	m_digital_pointSize_level_Max = 30;
	m_digital_pointSize_level_1 = 20;
	m_digital_pointSize_level_2 = 14;
	m_digital_pointSize_level_3 = 10;
	m_digital_pointSize_level_Min = 8;

	m_symbol_family = QString::fromUtf8("黑体");
	m_symbol_pointSize_level_Max = 30;
	m_symbol_pointSize_level_1 = 20;
	m_symbol_pointSize_level_2 = 14;
	m_symbol_pointSize_level_3 = 10;
	m_symbol_pointSize_level_Min = 8;



	m_chinese_levelMax.setFamily(m_chinese_family);
	m_chinese_levelMax.setPixelSize(m_chinese_pointSize_level_Max);
	m_chinese_level1.setFamily(m_chinese_family);
	m_chinese_level1.setPixelSize(m_chinese_pointSize_level_1);
	m_chinese_level2.setFamily(m_chinese_family);
	m_chinese_level2.setPixelSize(m_chinese_pointSize_level_2);
	m_chinese_level3.setFamily(m_chinese_family);
	m_chinese_level3.setPixelSize(m_chinese_pointSize_level_3);
	m_chinese_levelMin.setFamily(m_chinese_family);
	m_chinese_levelMin.setPixelSize(m_chinese_pointSize_level_Min);

	m_english_levelMax.setFamily(m_english_family);
	m_english_levelMax.setPixelSize(m_english_pointSize_level_Max);
	m_english_level1.setFamily(m_english_family);
	m_english_level1.setPixelSize(m_english_pointSize_level_1);
	m_english_level2.setFamily(m_english_family);
	m_english_level2.setPixelSize(m_english_pointSize_level_2);
	m_english_level3.setFamily(m_english_family);
	m_english_level3.setPixelSize(m_english_pointSize_level_3);
	m_english_levelMin.setFamily(m_english_family);
	m_english_levelMin.setPixelSize(m_english_pointSize_level_Min);

	m_digital_levelMax2.setFamily(m_digital_family);
	m_digital_levelMax2.setPixelSize(m_digital_pointSize_level_Max2);
	m_digital_levelMax.setFamily(m_digital_family);
	m_digital_levelMax.setPixelSize(m_digital_pointSize_level_Max);
	m_digital_level1.setFamily(m_digital_family);
	m_digital_level1.setPixelSize(m_digital_pointSize_level_1);
	m_digital_level2.setFamily(m_digital_family);
	m_digital_level2.setPixelSize(m_digital_pointSize_level_2);
	m_digital_level3.setFamily(m_digital_family);
	m_digital_level3.setPixelSize(m_digital_pointSize_level_3);
	m_digital_levelMin.setFamily(m_digital_family);
	m_digital_levelMin.setPixelSize(m_digital_pointSize_level_Min);

	m_symbol_levelMax.setFamily(m_symbol_family);
	m_symbol_levelMax.setPixelSize(m_symbol_pointSize_level_Max);
	m_symbol_level1.setFamily(m_symbol_family);
	m_symbol_level1.setPixelSize(m_symbol_pointSize_level_1);
	m_symbol_level2.setFamily(m_symbol_family);
	m_symbol_level2.setPixelSize(m_symbol_pointSize_level_2);
	m_symbol_level3.setFamily(m_symbol_family);
	m_symbol_level3.setPixelSize(m_symbol_pointSize_level_3);
	m_symbol_levelMin.setFamily(m_symbol_family);
	m_symbol_levelMin.setPixelSize(m_symbol_pointSize_level_Min);

	return;



	//QString dirpath = CT20IniMainPath;
	//QString file_name = "\\BFFontIni.ini";
	//QString filepath = dirpath + file_name;

	//先不写文件,默认读内存
	QString filepath = "";

	QDir dir;

	if (!QFile::exists(filepath))
	{
		m_chinese_family = QString::fromLocal8Bit("黑体");
		m_chinese_pointSize_level_Max = 30;
		m_chinese_pointSize_level_1 = 20;
		m_chinese_pointSize_level_2 = 14;
		m_chinese_pointSize_level_3 = 12;
		m_chinese_pointSize_level_Min = 8;

		m_english_family = QString::fromLocal8Bit("Arial");
		m_english_pointSize_level_Max = 30;
		m_english_pointSize_level_1 = 20;
		m_english_pointSize_level_2 = 14;
		m_english_pointSize_level_3 = 10;
		m_english_pointSize_level_Min = 8;

		m_digital_family = QString::fromLocal8Bit("黑体");
		m_digital_pointSize_level_Max2 = 50;
		m_digital_pointSize_level_Max = 30;
		m_digital_pointSize_level_1 = 20;
		m_digital_pointSize_level_2 = 14;
		m_digital_pointSize_level_3 = 10;
		m_digital_pointSize_level_Min = 8;

		m_symbol_family = QString::fromLocal8Bit("黑体");
		m_symbol_pointSize_level_Max = 30;
		m_symbol_pointSize_level_1 = 20;
		m_symbol_pointSize_level_2 = 14;
		m_symbol_pointSize_level_3 = 10;
		m_symbol_pointSize_level_Min = 8;

		QDir dir;
		//dir.mkpath(dirpath);
		QFile file(filepath);
		file.open(QIODevice::ReadWrite | QIODevice::Text);
		QTextStream data(&file);
		(data) << "***************Chinese Font******************" << "\r\n";
		(data) << "Chinese_Font:" << m_chinese_family << "\r\n";
		(data) << "ChineseFont_Level_Max:" << m_chinese_pointSize_level_Max << "\r\n";
		(data) << "ChineseFont_Level_1:" << m_chinese_pointSize_level_1 << "\r\n";
		(data) << "ChineseFont_Level_2:" << m_chinese_pointSize_level_2 << "\r\n";
		(data) << "ChineseFont_Level_3:" << m_chinese_pointSize_level_3 << "\r\n";
		(data) << "ChineseFont_Level_Min:" << m_chinese_pointSize_level_Min << "\r\n";
		(data) << "***************English Font******************" << "\r\n";
		(data) << "English_Font:" << m_english_family << "\r\n";
		(data) << "English_Font_Level_Max:" << m_english_pointSize_level_Max << "\r\n";
		(data) << "English_Font_Level_1:" << m_english_pointSize_level_1 << "\r\n";
		(data) << "English_Font_Level_2:" << m_english_pointSize_level_2 << "\r\n";
		(data) << "English_Font_Level_3:" << m_english_pointSize_level_3 << "\r\n";
		(data) << "English_Font_Level_Min:" << m_english_pointSize_level_Min << "\r\n";
		(data) << "***************Digital Font******************" << "\r\n";
		(data) << "Digital_Font:" << m_digital_family << "\r\n";
		(data) << "Digital_Font_Level_Max2:" << m_digital_pointSize_level_Max2 << "\r\n";
		(data) << "Digital_Font_Level_Max:" << m_digital_pointSize_level_Max << "\r\n";
		(data) << "Digital_Font_Level_1:" << m_digital_pointSize_level_1 << "\r\n";
		(data) << "Digital_Font_Level_2:" << m_digital_pointSize_level_2 << "\r\n";
		(data) << "Digital_Font_Level_3:" << m_digital_pointSize_level_3 << "\r\n";
		(data) << "Digital_Font_Level_Min:" << m_digital_pointSize_level_Min << "\r\n";
		(data) << "***************Symbol Font******************" << "\r\n";
		(data) << "Symbol_Font:" << m_symbol_family << "\r\n";
		(data) << "Symbol_Font_Level_Max:" << m_symbol_pointSize_level_Max << "\r\n";
		(data) << "Symbol_Font_Level_1:" << m_symbol_pointSize_level_1 << "\r\n";
		(data) << "Symbol_Font_Level_2:" << m_symbol_pointSize_level_2 << "\r\n";
		(data) << "Symbol_Font_Level_3:" << m_symbol_pointSize_level_3 << "\r\n";
		(data) << "Symbol_Font_Level_Min:" << m_symbol_pointSize_level_Min << "\r\n";
		file.close();
	}
	else
	{
		QFile file(filepath);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{

			while (!file.atEnd())
			{
				QByteArray line = file.readLine();
				QString str = QString::fromLocal8Bit(line);
				QStringList  datalist = str.split(":");

				if (datalist.size() == 2)
				{
					if (datalist.at(0) == "Chinese_Font")
						m_chinese_family = datalist.at(1).simplified();
					if (datalist.at(0) == "ChineseFont_Level_Max")
						m_chinese_pointSize_level_Max = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "ChineseFont_Level_1")
						m_chinese_pointSize_level_1 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "ChineseFont_Level_2")
						m_chinese_pointSize_level_2 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "ChineseFont_Level_3")
						m_chinese_pointSize_level_3 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "ChineseFont_Level_Min")
						m_chinese_pointSize_level_Min = datalist.at(1).simplified().toInt();

					if (datalist.at(0) == "English_Font")
						m_english_family = datalist.at(1).simplified();
					if (datalist.at(0) == "English_Font_Level_Max")
						m_english_pointSize_level_Max = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "English_Font_Level_1")
						m_english_pointSize_level_1 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "English_Font_Level_2")
						m_english_pointSize_level_2 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "English_Font_Level_3")
						m_english_pointSize_level_3 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "English_Font_Level_Min")
						m_english_pointSize_level_Min = datalist.at(1).simplified().toInt();

					if (datalist.at(0) == "Digital_Font")
						m_digital_family = datalist.at(1).simplified();
					if (datalist.at(0) == "Digital_Font_Level_Max2")
						m_digital_pointSize_level_Max2 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Digital_Font_Level_Max")
						m_digital_pointSize_level_Max = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Digital_Font_Level_1")
						m_digital_pointSize_level_1 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Digital_Font_Level_2")
						m_digital_pointSize_level_2 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Digital_Font_Level_3")
						m_digital_pointSize_level_3 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Digital_Font_Level_Min")
						m_digital_pointSize_level_Min = datalist.at(1).simplified().toInt();

					if (datalist.at(0) == "Symbol_Font")
						m_symbol_family = datalist.at(1).simplified();
					if (datalist.at(0) == "Symbol_Font_Level_Max")
						m_symbol_pointSize_level_Max = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Symbol_Font_Level_1")
						m_symbol_pointSize_level_1 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Symbol_Font_Level_2")
						m_symbol_pointSize_level_2 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Symbol_Font_Level_3")
						m_symbol_pointSize_level_3 = datalist.at(1).simplified().toInt();
					if (datalist.at(0) == "Symbol_Font_Level_Min")
						m_symbol_pointSize_level_Min = datalist.at(1).simplified().toInt();
				}
			}
		}
		file.close();
	}

	m_chinese_levelMax.setFamily(m_chinese_family);
	m_chinese_levelMax.setPixelSize(m_chinese_pointSize_level_Max);
	m_chinese_level1.setFamily(m_chinese_family);
	m_chinese_level1.setPixelSize(m_chinese_pointSize_level_1);
	m_chinese_level2.setFamily(m_chinese_family);
	m_chinese_level2.setPixelSize(m_chinese_pointSize_level_2);
	m_chinese_level3.setFamily(m_chinese_family);
	m_chinese_level3.setPixelSize(m_chinese_pointSize_level_3);
	m_chinese_levelMin.setFamily(m_chinese_family);
	m_chinese_levelMin.setPixelSize(m_chinese_pointSize_level_Min);

	m_english_levelMax.setFamily(m_english_family);
	m_english_levelMax.setPixelSize(m_english_pointSize_level_Max);
	m_english_level1.setFamily(m_english_family);
	m_english_level1.setPixelSize(m_english_pointSize_level_1);
	m_english_level2.setFamily(m_english_family);
	m_english_level2.setPixelSize(m_english_pointSize_level_2);
	m_english_level3.setFamily(m_english_family);
	m_english_level3.setPixelSize(m_english_pointSize_level_3);
	m_english_levelMin.setFamily(m_english_family);
	m_english_levelMin.setPixelSize(m_english_pointSize_level_Min);

	m_digital_levelMax2.setFamily(m_digital_family);
	m_digital_levelMax2.setPixelSize(m_digital_pointSize_level_Max2);
	m_digital_levelMax.setFamily(m_digital_family);
	m_digital_levelMax.setPixelSize(m_digital_pointSize_level_Max);
	m_digital_level1.setFamily(m_digital_family);
	m_digital_level1.setPixelSize(m_digital_pointSize_level_1);
	m_digital_level2.setFamily(m_digital_family);
	m_digital_level2.setPixelSize(m_digital_pointSize_level_2);
	m_digital_level3.setFamily(m_digital_family);
	m_digital_level3.setPixelSize(m_digital_pointSize_level_3);
	m_digital_levelMin.setFamily(m_digital_family);
	m_digital_levelMin.setPixelSize(m_digital_pointSize_level_Min);

	m_symbol_levelMax.setFamily(m_symbol_family);
	m_symbol_levelMax.setPixelSize(m_symbol_pointSize_level_Max);
	m_symbol_level1.setFamily(m_symbol_family);
	m_symbol_level1.setPixelSize(m_symbol_pointSize_level_1);
	m_symbol_level2.setFamily(m_symbol_family);
	m_symbol_level2.setPixelSize(m_symbol_pointSize_level_2);
	m_symbol_level3.setFamily(m_symbol_family);
	m_symbol_level3.setPixelSize(m_symbol_pointSize_level_3);
	m_symbol_levelMin.setFamily(m_symbol_family);
	m_symbol_levelMin.setPixelSize(m_symbol_pointSize_level_Min);
}
