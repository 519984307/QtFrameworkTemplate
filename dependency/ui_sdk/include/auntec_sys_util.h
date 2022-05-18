#ifndef __AUNTEC_SYS_UTIL_H
#define __AUNTEC_SYS_UTIL_H

#include "auntec_base_types.h"

#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief ��ȡ�ļ���С
	@param path �ļ�·��
	@return �ļ������ڷ���0
	*/
	int64_t auntec_get_file_size(const char* path);

	/*!
	@brief ��ȡ�ļ��д�С
	@param path �ļ���·��
	@param fileCounter ͳ���ļ�����
	@return �ļ��в����ڷ���0
	*/
	uint64_t auntec_get_folder_size(const char* dir, int* fileCounter=NULL);

	/*!
	@brief ���û�������
	@param evName ������
	@param evValue ����ֵ
	@note param��ҪUTF8����
	@return �Ƿ�ɹ����û�������
	*/
	bool auntec_set_environment_variable(const char* pEvName, const char* pEvValue);

	/*!
	@brief ��ȡ��������
	@param [in] evName ������ UTF8����
	@return ���ػ�������ֵ,UTF8����
	*/
	string auntec_get_environment_variable(const char* pEvName);

	/*!
	@brief ɾ����������
	@param name ����������
	@return ɾ���ɹ�����ʧ��
	*/
	bool auntec_delete_environment_variable(const char* pEvName);

#ifdef WIN32
	/*!
	��ʱ���ص�
	*/
	typedef void (*auntec_timer_proc_t)(void* pData);

	/*!
	��װ��ʱ��
	*/
	void* auntec_install_timer(unsigned int ms, auntec_timer_proc_t onTimer, void* pData);

	/*!
	ж�ض�ʱ��
	*/
	void auntec_uninstall_timer(void* pTimer);
#endif

	/*!
	@brief ����DLL
	@param path DLL��·����
	@return �ɹ�DLL�ľ����ʧ�ܷ���NULL
	*/
	void* auntec_load_dll(const char* path);

	/*!
	@brief ��ȡ������ַ
	@param hModule DLL�ľ��
	@param proc ������
	@return �ɹ����غ�������ڵ�ַ��ʧ�ܷ���NULL
	*/
	void* auntec_get_proc_addr(void* hModule, const char* proc);

	/*!
	@brief �ͷ�DLL
	@param hModule DLL���
	*/
	void auntec_free_dll(void* hModule);

	/*!
	@brief ����DLL�ļ���·��
	@param path �ļ���·��
	*/
	void auntec_dll_set_load_path(const char* path);

	/*!
	@brief ����һ��GUID�ַ�������ʽ��{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X} ʾ����{6984FDC9-9608-483C-BCDF-519BE652CEAD}
	@param haveBrace �Ƿ����{}
	@return GUID�ַ���
	*/
	string auntec_create_guid(bool haveBrace=true);
#ifdef WIN32
	wstring auntec_create_guidw(bool haveBrace=true);
#endif

	/*!
	@brief sleep
	@param nMilliseconds sleep����ֵ, ��λ���� 
	*/
	void auntec_sleep(uint32_t nMilliseconds);

	/*!
	@brief
	[1] Microsoft Windows OS \n
	The function retrieves the system time, in milliseconds. \n 
	The system time is the time elapsed since Windows was started.
	@return ����ֵ 
	*/
	uint32_t auntec_getticks();

#ifdef WIN32
	/*!
	@brief ������ϵͳλ��
	@return ����true���ʾ��ǰϵͳΪ64λ
	*/
	bool auntec_os_is64bit();

	typedef enum{
		AUNTEC_OS_TYPE_UNKNOWN = -1,
		AUNTEC_OS_TYPE_XP,
		AUNTEC_OS_TYPE_VISTA,
		AUNTEC_OS_TYPE_WIN7,
		AUNTEC_OS_TYPE_WIN7_SPX,
		AUNTEC_OS_TYPE_WIN8,
		AUNTEC_OS_TYPE_WIN10,
		AUNTEC_OS_TYPE_WIN_OTHER,
		AUNTEC_OS_TYPE_MACOS
	}AuntecOSType;

	/*!
	@brief ������ϵͳ����
	@return ���ص�ǰ����ϵͳ���ͣ����Բ鿴AuntecOSType
	*/
	AuntecOSType auntec_os_type();

	/*!
	@brief ��ȡ����ϵͳ����
	@return ����ϵͳ����
	*/
	string auntec_system_name();

	/*!
	@brief ��ȡ����ϵͳ�汾
	@return ����ϵͳ�汾
	*/
	string auntec_system_version();
	
	/*!
	@brief ��ȡapp����
	@return app����
	*/
	string auntec_app_name();

	/*!
	@brief ��ȡapp�汾��
	@return app�汾��
	*/
	string auntec_app_version();
	
	/*!
	@brief ��ȡmac��ַ
	@return mac��ַ
	*/
	string auntec_mac_address();
#endif
}

#endif
