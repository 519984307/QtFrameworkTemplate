#ifndef __AUNTEC_STRING_UTIL_H
#define __AUNTEC_STRING_UTIL_H

#include "auntec_base_types.h"

#include <string>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

namespace AuntecBased
{
	/*!
	@brief ��UTF8�ַ���ת���ɱ����ַ���
	@param pText UTF8�ַ���
	@return �����ַ���
	*/
	string utf8_2_local(const char* pText);

	/*!
	@brief �������ַ���ת����Utf8�ַ���
	@param pText �����ַ���
	@return Utf8�ַ���
	*/
	string local_2_utf8(const char* pText);

	/*!
	@brief �������ַ���ת���ɿ��ַ���
	@param pText �����ַ���
	@return ���ַ���
	*/
	wstring local_2_wide(const char* pText);

	/*!
	@brief ��Utf8�ַ���ת����Unicode�ַ���
	@param pText Utf8�ַ���
	@return Unicode�ַ���
	*/
	wstring utf8_2_wide(const char* pText);

	/*!
	@brief ��Unicode�ַ���ת����Utf8�ַ���
	@param pText Unicode�ַ���
	@return Utf8�ַ���
	*/
	string wide_2_utf8(const wchar_t* pText);

	/*!
	@brief �����ַ�����ɾ���ַ�����ߵ�chars�ַ��б��е��ַ�
	@param text ��������ַ���
	@param chars ��Ҫɾ�����ַ�
	@return ����ú���ַ���
	*/
	string trim_left(const char* pText, const char* pChars);
#ifdef WIN32
	wstring trim_left(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief �����ַ�����ɾ���ַ����ұ߱ߵ�chars�ַ��б��е��ַ�
	@param text ��������ַ���
	@param chars ��Ҫɾ�����ַ�
	@return ����ú���ַ���
	*/
	string trim_right(const char* pText, const char* pChars);
#ifdef WIN32
	wstring trim_right(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief �����ַ�����ɾ���ַ�����ߵ�chars�ַ��б��е��ַ�
	@param text ��������ַ���
	@param chars ��Ҫɾ�����ַ�
	@return ����ú���ַ���
	*/
	string trim(const char* pText, const char* pChars);
#ifdef WIN32
	wstring trim(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief ���ַ���ת���ɴ�д�ַ���
	@return ת������ַ���
	*/
	string upper_case(const char* pText);
#ifdef WIN32
	wstring upper_case(const wchar_t* pText);
#endif

	/*!
	@brief ���ַ���ת����Сд�ַ���
	@return ת������ַ���
	*/
	string lower_case(const char* pText);
#ifdef WIN32
	wstring lower_case(const wchar_t* pText);
#endif

	/*!
	@brief �ָ��ַ���
	@param text �ȴ��ָ���ַ���
	@param chars �ָ����
	*/
	vector<string> str_split(const char* pText, const char* pChars);
#ifdef WIN32
	vector<wstring> str_split(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief ���ַ����в����ַ�����λ��
	@param text Դ�ַ���
	@param start ��ʼ����
	@param needle Ҫ���ҵ��ַ���
	@return �ɹ�����needle��text�е�������û�ҵ��򷵻�-1
	*/
	int str_left_pos(const char* pText, unsigned int start, const char* pNeedle);
#ifdef WIN32
	int str_left_pos(const wchar_t* pText, unsigned int start, const wchar_t* pNeedle);
#endif

	/*!
	@brief ���ַ����в����ַ�����λ�� (����������)
	@param text Դ�ַ���
	@param start ��ʼ����
	@param needle Ҫ���ҵ��ַ���
	@return �ɹ�����needle��text�е�������û�ҵ��򷵻�-1
	*/
	int str_right_pos(const char* pText, unsigned int start, const char* pNeedle);
#ifdef WIN32
	int str_right_pos(const wchar_t* pText, unsigned int start, const wchar_t* pNeedle);
#endif

	/*!
	@brief ����text����n���ַ�
	*/
	string left_str(const char* pText, unsigned int n);
#ifdef WIN32
	wstring left_str(const wchar_t* pText, unsigned int n);
#endif

	/*!
	@brief ����text�Ҳ��n���ַ�
	*/
	string right_str(const char* pText, unsigned int n);
#ifdef WIN32
	wstring right_str(const wchar_t* pText, unsigned int n);
#endif

	/*!
	@brief ����text��start��ʼ��len���ַ�
	*/
	string sub_str(const char* pText, unsigned int start, unsigned int len);

	/*!
	@brief �ַ����滻
	@param text Դ�ַ���
	@param find ��Ҫ���滻���ַ���
	@param replace ��Ҫ�滻�ɵ��ַ���
	@return �滻����ַ���
	*/
	string str_replace(const char* pText, const char* pFind, const char* pReplace);
#ifdef WIN32
	wstring str_replace(const wchar_t* pText, const wchar_t* pFind, const wchar_t* pReplace);
#endif

	/*!
	@brief �ַ���ת������
	*/
	int64_t string_to_long(const char* pText);
#ifdef WIN32
	int64_t string_to_long(const wchar_t* pText);
#endif

	/*!
	@brief ������ת�ַ���
	*/
	string long_to_string(int64_t val);

	/*!
    @brief text �Ƿ�ƥ��pattern
    @param text �ȴ�ƥ����ַ���
    @param pattern ģʽ�ַ���,����*��ʾ�������ַ�,?��ʾһ���ַ�,�����ַ���ʾ�ַ�����
    @return �Ƿ�ɹ�ƥ��
    */
    bool str_match(const char* text, const char* pattern);

	/*!
    @brief text ��ʽ���ַ���
    */
	string str_format(const char* format,...);

#ifdef WIN32
	/*!
    @brief text ��ʽ���ַ���
    */
	wstring str_format(const wchar_t* format,...);

	/*!
    @brief text url����
    */
	string URLDecode( const void* data, int size );

	/*
	 @brief text utf�����ַ���ת��Ϊutf��
	*/
	string TranslateC2SA(const char* src);


	/*
	 @brief text utf�����ַ���ת��Ϊ���ֽ�
	*/
	wstring TranslateC2SW(const char* src);
#endif

#if !defined(NDEBUG)
	void print_msg(const char* file, const uint32_t line, const char* format, ...);
#	define msg_box(...) print_msg(__FILE__, __LINE__, __VA_ARGS__)
#else
#	define msg_box(expression,...)	((void)0)
#endif
}

#endif
