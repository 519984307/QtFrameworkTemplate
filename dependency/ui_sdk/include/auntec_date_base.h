#ifndef __AUNTEC_DATE_BASE_H
#define __AUNTEC_DATE_BASE_H

#include "auntec_base_types.h"

#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief 日期
	*/
	class AuntecDate
	{
	public:
		AuntecDate();
		AuntecDate(int year, int month, int day);
		~AuntecDate();

	public:
		void SetDate(int year, int month, int day);

		virtual void Print();
		//yyyy-MM-dd
		string ToYYYY_MM_DD();
		//MM-dd-yyyy
		string ToMM_DD_YYYY();

	protected:
		int m_year;
		int m_month;
		int m_day;
	};

	/*!
	@brief 日期+时间
	*/
	class AuntecDateTime:public AuntecDate
	{
	public:
		/*!
		@brief 初始化为现在系统日期+时间
		*/
		AuntecDateTime();
		/*!
		@brief 秒数初始化时间
		@param second 默认从1970-1-1整开始计算的秒
		@param from2001 second是从2001-1-1开始计算的秒数
		*/
		AuntecDateTime(int64_t second, bool from2001 = false);
		AuntecDateTime(int hour, int minute, int second);
		AuntecDateTime(int year, int month, int day, int hour, int minute, int second);
		/*!
		@brief MM_DD_YYYY(空格)HH:MM:SS字符串时间格式初始化
		*/
		AuntecDateTime(const char* strDate);
		~AuntecDateTime();

	public:
		void SetDateTime(int64_t second, bool from2001 = false);
		void SetCurrent();
		virtual void Print();
		//hh:mm:ssZ
		string ToHHMMSS();
		string ToHH_MM_SS();
		string ToMM_DD_YYYYHHMMSS();
		string ToYYYY_MM_DD_HHMMSS();
		/*!
		@brief 转换为IOS内存储的时间秒数即从2001-1-1至当前存储时间的秒数
		*/
		int64_t ToIOSDateTime();
		int64_t To1970Time();

		void AddSecond(int32_t s);
		/*!
		@brief 获取当前时区与UTC相差时间
		@return 返回偏移组合字符串,如中国返回"-0800",其中08=hours,00=minutes
		@note 小时和分钟是组合数
		*/
		static string GetUtcOffsetHHMM();
		//获取当前时区与UTC相差时间：单位s
		static int32_t GetUtcOffset();

	public:
		int m_hour;
		int m_minute;
		int m_second;

	private:
		void Init(const time_t &now);
	};

}

#endif
