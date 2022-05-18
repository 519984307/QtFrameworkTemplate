#ifndef __AUNTEC_DIR_UTIL_H
#define __AUNTEC_DIR_UTIL_H

#include "auntec_base_types.h"

#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief �𼶴����ļ���
	*/
	bool auntec_make_dir(const char* path);
#ifdef WIN32
	bool auntec_make_dir(const wchar_t* path);
#endif

	/*!
	@brief �ݹ�ɾ���ļ���
	*/
	void auntec_delete_dir(const char* path);
#ifdef WIN32
	void auntec_delete_dir(const wchar_t* path);
#endif

	/*!
	@brief ɾ���ļ�
	*/
	bool auntec_delete_file(const char* path);

	/*!
	@brief �޸��ļ���/�ļ���, �����ƶ��ļ��л��ļ���
	@param src Դ�ļ������ļ���·��
	@param dest Ŀ���ļ������ļ���·��
	@return �ɹ�����true, ʧ�ܷ���false
	*/
	bool auntec_move_file(const char* pSrc, const char* pDst);

	/*!
	�ļ��Ƿ����
	*/
	bool auntec_file_exists(const char* path);
#ifdef WIN32
	bool auntec_file_exists(const wchar_t* path);
#endif

	/*!
	@brief Ŀ¼�Ƿ����
	*/
	bool auntec_dir_exists(const char* path);
#ifdef WIN32
	bool auntec_dir_exists(const wchar_t* path);
#endif

	/*!
	@brief �ļ����Ҿ��
	*/
	typedef struct auntec_find_data auntec_find_data;

	/*!
	@brief ���ҵ�һ���ļ�, ���ز��Ҿ��
	@param path �ļ���·��
	@param pattern ƥ�������, ʹ��*?����ƥ��
	@return �ɹ����ز��Ҿ��, ʧ�ܷ���NULL
	*/
	auntec_find_data* auntec_find_first(const char* path, const char* pattern);

	/*!
	@brief ������һ���ļ�
	*/
	bool auntec_find_next(auntec_find_data* pFindData);

	/*!
	@brief ��ǰ�ļ��Ƿ����ļ���
	*/
	bool auntec_find_is_folder(auntec_find_data* pFindData);

	/*!
	@brief ��ȡ�ļ�·��
	*/
	string auntec_find_get_path(auntec_find_data* pFindData);

	/*!
	@brief �ر��ļ����Ҿ��
	*/
	void auntec_find_close(auntec_find_data* pFindData);

	/*!
	@brief ��ȡ�ļ���ȫ·��
	*/
	string auntec_expand_path(const char* path);

	/*!
	@brief ·���ָ���
	*/
#ifdef WIN32
	const char system_file_path_delimiter = '\\';
	const char system_file_path_delimiter_str[] = "\\";
#else
	const char system_file_path_delimiter = '/';
	const char system_file_path_delimiter_str[] = "/";
#endif

	/*!
	@brief ���ļ�·��׷��б��
	*/
	string auntec_include_path_backslash(const char* path);
#ifdef WIN32
	wstring auntec_include_path_backslash(const wchar_t* path);
#endif

	/*!
	@brief ��ȡ�ļ�����׺�����û�к�׺�ͷ���""
	*/
	string auntec_extract_file_ext(const char* path);

	/*!
	@brief ��ȡ�ļ���
	*/
	string auntec_extract_file_name(const char* path);
#ifdef WIN32
	wstring auntec_extract_file_name(const wchar_t* path);
#endif
	/*!
	@brief ��ȡ�ļ�·��
	*/
	string auntec_extract_file_path(const char* path);
#ifdef WIN32
	wstring auntec_extract_file_path(const wchar_t* path);
#endif

	/*!
	@brief �����û�����Ŀ¼
	@return ��Ŀ¼������б��
	*/
	string auntec_get_home_path();

	/*!
	@brief ��ȡ�����п�ִ���ļ���·��
	@return ʧ�ܷ��ؿ��ַ���
	*/
	string auntec_get_executable_path();
#ifdef WIN32
	wstring auntec_get_executable_pathw();
#endif
}

/*!
@brief ��ȡ�����п�ִ���ļ����ڵ�Ŀ¼��·��
*/
#define auntec_get_executable_directory() AuntecBased::auntec_include_path_backslash(AuntecBased::auntec_extract_file_path(AuntecBased::auntec_get_executable_path().c_str()).c_str())
#ifdef WIN32
#	define auntec_get_executable_directoryw() AuntecBased::auntec_include_path_backslash(AuntecBased::auntec_extract_file_path(AuntecBased::auntec_get_executable_pathw().c_str()).c_str())
#endif

#endif
