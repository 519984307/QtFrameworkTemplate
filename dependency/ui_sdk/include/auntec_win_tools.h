#ifndef _AUNTEC_WIN_TOOLS_H
#define _AUNTEC_WIN_TOOLS_H

#include "auntec_base_types.h"
#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief �ļ���Сת�������ص��ļ��ַ�����С"B,KB,MB,GB,TB"
	@param nFileSize �ļ��Ĵ�С
	*/
	string convert_file_size(int64_t nFileSize);

#ifdef WIN32
	/*!
	@brief ��ȡѡ���ļ��У�����ѡ���ļ������ֳɹ�����ʧ��
	@param defaultPath Ĭ���ļ���·��
	@param selectPath ��ȡ���ļ���·��
	@param selectBufSize ��ȡ�ļ���·������󳤶�
	@param hOwner ����ӵ����
	@param caption ���ڱ���
	*/
	bool get_select_folder(const wchar_t* defaultPath, wchar_t* selectBuf, int selectBufSize, HWND hOwner=NULL, const wchar_t* caption=NULL);

	wstring convert_file_size_w(int64_t nFileSize);

	wstring get_image_resolution( void* pBuffer,uint32_t len );
#endif
}

#endif
