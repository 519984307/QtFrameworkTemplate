#ifndef ztool_h__
#define ztool_h__
#include "bfcommon_export.h"
/*!
@brief 压缩回调原型
@param pctx 回调自定义参数
@return 返回非0取消压缩
*/
typedef int (__stdcall *zip_compress_callback)(void* pctx);

/*!
@brief 压缩
@param src 原始文件/文件夹
@param dst zip文件全路径
@param parten 通配符
@param pcb 压缩回调接口
@param pctx 压缩回调自定义参数
@return 成功返回0
*/
int COMMON_LIB_EXPORT zip_compress2(const wchar_t* src, const wchar_t* dst, const wchar_t* parten, zip_compress_callback pcb, void* pctx);
int COMMON_LIB_EXPORT zip_compress(const wchar_t* src, const wchar_t* dst, zip_compress_callback pcb, void* pctx);

/*!
@brief 解压回调原型
@param pctx 回调自定义参数
@return 返回非0取消解压
*/
typedef zip_compress_callback zip_uncompress_callback;

/*!
@brief 解压缩
@param src zip文件全路径
@param dst 输出文件夹路径
@param pcb 解压回调接口
@param pctx 解压回调自定义参数
@return 成功返回0
*/
int COMMON_LIB_EXPORT zip_uncompress(const wchar_t* src, const wchar_t* dst, zip_uncompress_callback pcb, void* pctx);

#endif
