#ifndef __AUNTEC_DATE_BASE_H
#define __AUNTEC_DATE_BASE_H

#include "auntec_base_types.h"

#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief ����
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
	@brief ����+ʱ��
	*/
	class AuntecDateTime:public AuntecDate
	{
	public:
		/*!
		@brief ��ʼ��Ϊ����ϵͳ����+ʱ��
		*/
		AuntecDateTime();
		/*!
		@brief ������ʼ��ʱ��
		@param second Ĭ�ϴ�1970-1-1����ʼ�������
		@param from2001 second�Ǵ�2001-1-1��ʼ���������
		*/
		AuntecDateTime(int64_t second, bool from2001 = false);
		AuntecDateTime(int hour, int minute, int second);
		AuntecDateTime(int year, int month, int day, int hour, int minute, int second);
		/*!
		@brief MM_DD_YYYY(�ո�)HH:MM:SS�ַ���ʱ���ʽ��ʼ��
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
		@brief ת��ΪIOS�ڴ洢��ʱ����������2001-1-1����ǰ�洢ʱ�������
		*/
		int64_t ToIOSDateTime();
		int64_t To1970Time();

		void AddSecond(int32_t s);
		/*!
		@brief ��ȡ��ǰʱ����UTC���ʱ��
		@return ����ƫ������ַ���,���й�����"-0800",����08=hours,00=minutes
		@note Сʱ�ͷ����������
		*/
		static string GetUtcOffsetHHMM();
		//��ȡ��ǰʱ����UTC���ʱ�䣺��λs
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
