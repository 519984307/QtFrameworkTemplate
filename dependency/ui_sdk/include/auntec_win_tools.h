#ifndef _AUNTEC_WIN_TOOLS_H
#define _AUNTEC_WIN_TOOLS_H

#include "auntec_base_types.h"
#include <string>
using namespace std;

namespace AuntecBased
{
	/*!
	@brief 文件大小转换，返回的文件字符串大小"B,KB,MB,GB,TB"
	@param nFileSize 文件的大小
	*/
	string convert_file_size(int64_t nFileSize);

#ifdef WIN32
	/*!
	@brief 获取选中文件夹，返回选中文件夹名字成功还是失败
	@param defaultPath 默认文件夹路径
	@param selectPath 获取的文件夹路径
	@param selectBufSize 获取文件夹路径的最大长度
	@param hOwner 窗口拥有者
	@param caption 窗口标题
	*/
	bool get_select_folder(const wchar_t* defaultPath, wchar_t* selectBuf, int selectBufSize, HWND hOwner=NULL, const wchar_t* caption=NULL);

	wstring convert_file_size_w(int64_t nFileSize);

	wstring get_image_resolution( void* pBuffer,uint32_t len );
#endif
}

#endif
