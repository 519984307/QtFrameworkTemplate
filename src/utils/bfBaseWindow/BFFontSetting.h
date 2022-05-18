//字体配置文件,在样式表里可以不用设置字体,全部统一SetFont
//[2020.10.21 Tom]
#pragma once
#include <QObject>
#include <QFont>

class BFFont : public QObject
{
public:
	static BFFont *GetInstance();          //单例模式		
	void SetLanguageMode(int mode);      // 0=默认 1=中文 2=英文
	void GetSetting();                   //获取字体配置

	QFont Get_CHINESE_FONT_LEVEL_MAX() 
	{
		if (m_langeuge_mode == 0 || m_langeuge_mode == 1)
			return m_chinese_levelMax;
		else if (m_langeuge_mode == 2)
			return m_english_levelMax;
		else
			return m_chinese_levelMax;
	};

	QFont Get_CHINESE_FONT_LEVEL_1() 
	{
		if (m_langeuge_mode == 0 || m_langeuge_mode == 1)
			return m_chinese_level1;
		else if (m_langeuge_mode == 2)
			return m_english_level1;
		else
			return m_chinese_level1;
	};

	QFont Get_CHINESE_FONT_LEVEL_2()
	{
		if (m_langeuge_mode == 0 || m_langeuge_mode == 1)
			return m_chinese_level2;
		else if (m_langeuge_mode == 2)
			return m_english_level2;
		else
			return m_chinese_level2;
	};

	QFont Get_CHINESE_FONT_LEVEL_3() 
	{
		if (m_langeuge_mode == 0 || m_langeuge_mode == 1)
			return m_chinese_level3;
		else if (m_langeuge_mode == 2)
			return m_english_level3;
		else
			return m_chinese_level3;
	};

	QFont Get_CHINESE_FONT_LEVEL_MIN() 
	{
		if (m_langeuge_mode == 0 || m_langeuge_mode == 1)
			return m_chinese_levelMin;
		else if (m_langeuge_mode == 2)
			return m_english_levelMin;
		else
			return m_chinese_levelMin;
	};

	QFont Get_ENGLISH_FONT_LEVEL_MAX() { return m_english_levelMax; };
	QFont Get_ENGLISH_FONT_LEVEL_1() { return m_english_level1; };
	QFont Get_ENGLISH_FONT_LEVEL_2() { return m_english_level2; };
	QFont Get_ENGLISH_FONT_LEVEL_3() { return m_english_level3; };
	QFont Get_ENGLISH_FONT_LEVEL_MIN() { return m_english_levelMin; };

	QFont Get_DIGITAL_FONT_LEVEL_MAX2() { return m_digital_levelMax2; };
	QFont Get_DIGITAL_FONT_LEVEL_MAX() { return m_digital_levelMax; };
	QFont Get_DIGITAL_FONT_LEVEL_1() { return m_digital_level1; };
	QFont Get_DIGITAL_FONT_LEVEL_2() { return m_digital_level2; };
	QFont Get_DIGITAL_FONT_LEVEL_3() { return m_digital_level3; };
	QFont Get_DIGITAL_FONT_LEVEL_MIN() { return m_digital_levelMin; };

	QFont Get_SYMBOL_FONT_LEVEL_MAX() { return m_symbol_levelMax; };
	QFont Get_SYMBOL_FONT_LEVEL_1() { return m_symbol_level1; };
	QFont Get_SYMBOL_FONT_LEVEL_2() { return m_symbol_level2; };
	QFont Get_SYMBOL_FONT_LEVEL_3() { return m_symbol_level3; };
	QFont Get_SYMBOL_FONT_LEVEL_MIN() { return m_symbol_levelMin; };
private:
	BFFont();

	int m_langeuge_mode;

	//中文字体
	QString m_chinese_family;//字体名称
	int m_chinese_pointSize_level_Max;
	int m_chinese_pointSize_level_1;//点大小
	int m_chinese_pointSize_level_2;
	int m_chinese_pointSize_level_3;
	int m_chinese_pointSize_level_Min;
	//英文字体
	QString m_english_family;
	int m_english_pointSize_level_Max;
	int m_english_pointSize_level_1;
	int m_english_pointSize_level_2;
	int m_english_pointSize_level_3;
	int m_english_pointSize_level_Min;
	//数字字体
	QString m_digital_family;
	int m_digital_pointSize_level_Max2;
	int m_digital_pointSize_level_Max;
	int m_digital_pointSize_level_1;
	int m_digital_pointSize_level_2;
	int m_digital_pointSize_level_3;
	int m_digital_pointSize_level_Min;
	//符号字体
	QString m_symbol_family;
	int m_symbol_pointSize_level_Max;
	int m_symbol_pointSize_level_1;
	int m_symbol_pointSize_level_2;
	int m_symbol_pointSize_level_3;
	int m_symbol_pointSize_level_Min;

	QFont m_chinese_levelMax;
	QFont m_chinese_level1;
	QFont m_chinese_level2;
	QFont m_chinese_level3;
	QFont m_chinese_levelMin;

	QFont m_english_levelMax;
	QFont m_english_level1;
	QFont m_english_level2;
	QFont m_english_level3;
	QFont m_english_levelMin;

	QFont m_digital_levelMax2;
	QFont m_digital_levelMax;
	QFont m_digital_level1;
	QFont m_digital_level2;
	QFont m_digital_level3;
	QFont m_digital_levelMin;

	QFont m_symbol_levelMax;
	QFont m_symbol_level1;
	QFont m_symbol_level2;
	QFont m_symbol_level3;
	QFont m_symbol_levelMin;

protected:
	static BFFont *bf_font;
};

//中文字体
#define BF_FONT_CHINESE_LEVEL_MAX BFFont::GetInstance()->Get_CHINESE_FONT_LEVEL_MAX()
#define BF_FONT_CHINESE_LEVEL_1 BFFont::GetInstance()->Get_CHINESE_FONT_LEVEL_1()
#define BF_FONT_CHINESE_LEVEL_2 BFFont::GetInstance()->Get_CHINESE_FONT_LEVEL_2()
#define BF_FONT_CHINESE_LEVEL_3 BFFont::GetInstance()->Get_CHINESE_FONT_LEVEL_3()
#define BF_FONT_CHINESE_LEVEL_MIN BFFont::GetInstance()->Get_CHINESE_FONT_LEVEL_MIN()
//英文字体
#define BF_FONT_ENGLISH_LEVEL_MAX BFFont::GetInstance()->Get_ENGLISH_FONT_LEVEL_MAX()
#define BF_FONT_ENGLISH_LEVEL_1 BFFont::GetInstance()->Get_ENGLISH_FONT_LEVEL_1()
#define BF_FONT_ENGLISH_LEVEL_2 BFFont::GetInstance()->Get_ENGLISH_FONT_LEVEL_2()
#define BF_FONT_ENGLISH_LEVEL_3 BFFont::GetInstance()->Get_ENGLISH_FONT_LEVEL_3()
#define BF_FONT_ENGLISH_LEVEL_MIN BFFont::GetInstance()->Get_ENGLISH_FONT_LEVEL_MIN()
//数字字体
#define BF_FONT_DIGITAL_LEVEL_MAX_2 BFFont::GetInstance()->Get_DIGITAL_FONT_LEVEL_MAX2()
#define BF_FONT_DIGITAL_LEVEL_MAX BFFont::GetInstance()->Get_DIGITAL_FONT_LEVEL_MAX()
#define BF_FONT_DIGITAL_LEVEL_1 BFFont::GetInstance()->Get_DIGITAL_FONT_LEVEL_1()
#define BF_FONT_DIGITAL_LEVEL_2 BFFont::GetInstance()->Get_DIGITAL_FONT_LEVEL_2()
#define BF_FONT_DIGITAL_LEVEL_3 BFFont::GetInstance()->Get_DIGITAL_FONT_LEVEL_3()
#define BF_FONT_DIGITAL_LEVEL_MIN BFFont::GetInstance()->Get_DIGITAL_FONT_LEVEL_MIN()
//符号字体
#define BF_FONT_SYMBOL_LEVEL_MAX BFFont::GetInstance()->Get_SYMBOL_FONT_LEVEL_MAX()
#define BF_FONT_SYMBOL_LEVEL_1 BFFont::GetInstance()->Get_SYMBOL_FONT_LEVEL_1()
#define BF_FONT_SYMBOL_LEVEL_2 BFFont::GetInstance()->Get_SYMBOL_FONT_LEVEL_2()
#define BF_FONT_SYMBOL_LEVEL_3 BFFont::GetInstance()->Get_SYMBOL_FONT_LEVEL_3()
#define BF_FONT_SYMBOL_LEVEL_MIN BFFont::GetInstance()->Get_SYMBOL_FONT_LEVEL_MIN()
