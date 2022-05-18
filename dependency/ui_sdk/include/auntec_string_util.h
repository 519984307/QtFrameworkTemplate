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
	@brief 将UTF8字符串转换成本地字符串
	@param pText UTF8字符串
	@return 本地字符串
	*/
	string utf8_2_local(const char* pText);

	/*!
	@brief 将本地字符串转换成Utf8字符串
	@param pText 本地字符串
	@return Utf8字符串
	*/
	string local_2_utf8(const char* pText);

	/*!
	@brief 将本地字符串转换成宽字符串
	@param pText 本地字符串
	@return 宽字符串
	*/
	wstring local_2_wide(const char* pText);

	/*!
	@brief 将Utf8字符串转换成Unicode字符串
	@param pText Utf8字符串
	@return Unicode字符串
	*/
	wstring utf8_2_wide(const char* pText);

	/*!
	@brief 将Unicode字符串转换成Utf8字符串
	@param pText Unicode字符串
	@return Utf8字符串
	*/
	string wide_2_utf8(const wchar_t* pText);

	/*!
	@brief 整理字符串，删除字符串左边的chars字符列表中的字符
	@param text 待整理的字符串
	@param chars 需要删除的字符
	@return 整理好后的字符串
	*/
	string trim_left(const char* pText, const char* pChars);
#ifdef WIN32
	wstring trim_left(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief 整理字符串，删除字符串右边边的chars字符列表中的字符
	@param text 待整理的字符串
	@param chars 需要删除的字符
	@return 整理好后的字符串
	*/
	string trim_right(const char* pText, const char* pChars);
#ifdef WIN32
	wstring trim_right(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief 整理字符串，删除字符串左边的chars字符列表中的字符
	@param text 待整理的字符串
	@param chars 需要删除的字符
	@return 整理好后的字符串
	*/
	string trim(const char* pText, const char* pChars);
#ifdef WIN32
	wstring trim(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief 将字符串转换成大写字符串
	@return 转换后的字符串
	*/
	string upper_case(const char* pText);
#ifdef WIN32
	wstring upper_case(const wchar_t* pText);
#endif

	/*!
	@brief 将字符串转换成小写字符串
	@return 转换后的字符串
	*/
	string lower_case(const char* pText);
#ifdef WIN32
	wstring lower_case(const wchar_t* pText);
#endif

	/*!
	@brief 分割字符串
	@param text 等待分割的字符串
	@param chars 分割符号
	*/
	vector<string> str_split(const char* pText, const char* pChars);
#ifdef WIN32
	vector<wstring> str_split(const wchar_t* pText, const wchar_t* pChars);
#endif

	/*!
	@brief 从字符串中查找字符串的位置
	@param text 源字符串
	@param start 开始索引
	@param needle 要查找的字符串
	@return 成功返回needle在text中的索引，没找到则返回-1
	*/
	int str_left_pos(const char* pText, unsigned int start, const char* pNeedle);
#ifdef WIN32
	int str_left_pos(const wchar_t* pText, unsigned int start, const wchar_t* pNeedle);
#endif

	/*!
	@brief 从字符串中查找字符串的位置 (从右往左找)
	@param text 源字符串
	@param start 开始索引
	@param needle 要查找的字符串
	@return 成功返回needle在text中的索引，没找到则返回-1
	*/
	int str_right_pos(const char* pText, unsigned int start, const char* pNeedle);
#ifdef WIN32
	int str_right_pos(const wchar_t* pText, unsigned int start, const wchar_t* pNeedle);
#endif

	/*!
	@brief 返回text左侧的n个字符
	*/
	string left_str(const char* pText, unsigned int n);
#ifdef WIN32
	wstring left_str(const wchar_t* pText, unsigned int n);
#endif

	/*!
	@brief 返回text右侧的n个字符
	*/
	string right_str(const char* pText, unsigned int n);
#ifdef WIN32
	wstring right_str(const wchar_t* pText, unsigned int n);
#endif

	/*!
	@brief 返回text从start开始的len个字符
	*/
	string sub_str(const char* pText, unsigned int start, unsigned int len);

	/*!
	@brief 字符串替换
	@param text 源字符串
	@param find 需要被替换的字符串
	@param replace 需要替换成的字符串
	@return 替换后的字符串
	*/
	string str_replace(const char* pText, const char* pFind, const char* pReplace);
#ifdef WIN32
	wstring str_replace(const wchar_t* pText, const wchar_t* pFind, const wchar_t* pReplace);
#endif

	/*!
	@brief 字符串转长整型
	*/
	int64_t string_to_long(const char* pText);
#ifdef WIN32
	int64_t string_to_long(const wchar_t* pText);
#endif

	/*!
	@brief 长整型转字符串
	*/
	string long_to_string(int64_t val);

	/*!
    @brief text 是否匹配pattern
    @param text 等待匹配的字符串
    @param pattern 模式字符串,其中*表示任意多个字符,?表示一个字符,其它字符表示字符本身
    @return 是否成功匹配
    */
    bool str_match(const char* text, const char* pattern);

	/*!
    @brief text 格式化字符串
    */
	string str_format(const char* format,...);

#ifdef WIN32
	/*!
    @brief text 格式化字符串
    */
	wstring str_format(const wchar_t* format,...);

	/*!
    @brief text url解码
    */
	string URLDecode( const void* data, int size );

	/*
	 @brief text utf码流字符串转换为utf码
	*/
	string TranslateC2SA(const char* src);


	/*
	 @brief text utf码流字符串转换为宽字节
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
