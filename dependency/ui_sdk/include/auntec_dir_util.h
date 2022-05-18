#ifndef __AUNTEC_DIR_UTIL_H
#define __AUNTEC_DIR_UTIL_H

#include "auntec_base_types.h"

#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief 逐级创建文件夹
	*/
	bool auntec_make_dir(const char* path);
#ifdef WIN32
	bool auntec_make_dir(const wchar_t* path);
#endif

	/*!
	@brief 递归删除文件夹
	*/
	void auntec_delete_dir(const char* path);
#ifdef WIN32
	void auntec_delete_dir(const wchar_t* path);
#endif

	/*!
	@brief 删除文件
	*/
	bool auntec_delete_file(const char* path);

	/*!
	@brief 修改文件夹/文件名, 或者移动文件夹或文件名
	@param src 源文件或者文件夹路径
	@param dest 目标文件或者文件夹路径
	@return 成功返回true, 失败返回false
	*/
	bool auntec_move_file(const char* pSrc, const char* pDst);

	/*!
	文件是否存在
	*/
	bool auntec_file_exists(const char* path);
#ifdef WIN32
	bool auntec_file_exists(const wchar_t* path);
#endif

	/*!
	@brief 目录是否存在
	*/
	bool auntec_dir_exists(const char* path);
#ifdef WIN32
	bool auntec_dir_exists(const wchar_t* path);
#endif

	/*!
	@brief 文件查找句柄
	*/
	typedef struct auntec_find_data auntec_find_data;

	/*!
	@brief 查找第一个文件, 返回查找句柄
	@param path 文件夹路径
	@param pattern 匹配的名字, 使用*?进行匹配
	@return 成功返回查找句柄, 失败返回NULL
	*/
	auntec_find_data* auntec_find_first(const char* path, const char* pattern);

	/*!
	@brief 查找下一个文件
	*/
	bool auntec_find_next(auntec_find_data* pFindData);

	/*!
	@brief 当前文件是否是文件夹
	*/
	bool auntec_find_is_folder(auntec_find_data* pFindData);

	/*!
	@brief 获取文件路径
	*/
	string auntec_find_get_path(auntec_find_data* pFindData);

	/*!
	@brief 关闭文件查找句柄
	*/
	void auntec_find_close(auntec_find_data* pFindData);

	/*!
	@brief 获取文件的全路径
	*/
	string auntec_expand_path(const char* path);

	/*!
	@brief 路径分隔符
	*/
#ifdef WIN32
	const char system_file_path_delimiter = '\\';
	const char system_file_path_delimiter_str[] = "\\";
#else
	const char system_file_path_delimiter = '/';
	const char system_file_path_delimiter_str[] = "/";
#endif

	/*!
	@brief 给文件路径追加斜杠
	*/
	string auntec_include_path_backslash(const char* path);
#ifdef WIN32
	wstring auntec_include_path_backslash(const wchar_t* path);
#endif

	/*!
	@brief 获取文件名后缀，如果没有后缀就返回""
	*/
	string auntec_extract_file_ext(const char* path);

	/*!
	@brief 获取文件名
	*/
	string auntec_extract_file_name(const char* path);
#ifdef WIN32
	wstring auntec_extract_file_name(const wchar_t* path);
#endif
	/*!
	@brief 获取文件路径
	*/
	string auntec_extract_file_path(const char* path);
#ifdef WIN32
	wstring auntec_extract_file_path(const wchar_t* path);
#endif

	/*!
	@brief 返回用户的主目录
	@return 主目录，不带斜杠
	*/
	string auntec_get_home_path();

	/*!
	@brief 获取进程中可执行文件的路径
	@return 失败返回空字符串
	*/
	string auntec_get_executable_path();
#ifdef WIN32
	wstring auntec_get_executable_pathw();
#endif
}

/*!
@brief 获取进程中可执行文件所在的目录的路径
*/
#define auntec_get_executable_directory() AuntecBased::auntec_include_path_backslash(AuntecBased::auntec_extract_file_path(AuntecBased::auntec_get_executable_path().c_str()).c_str())
#ifdef WIN32
#	define auntec_get_executable_directoryw() AuntecBased::auntec_include_path_backslash(AuntecBased::auntec_extract_file_path(AuntecBased::auntec_get_executable_pathw().c_str()).c_str())
#endif

#endif
