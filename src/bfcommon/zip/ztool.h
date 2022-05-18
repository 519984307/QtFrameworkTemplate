#ifndef ztool_h__
#define ztool_h__
#include "bfcommon_export.h"
/*!
@brief ѹ���ص�ԭ��
@param pctx �ص��Զ������
@return ���ط�0ȡ��ѹ��
*/
typedef int (__stdcall *zip_compress_callback)(void* pctx);

/*!
@brief ѹ��
@param src ԭʼ�ļ�/�ļ���
@param dst zip�ļ�ȫ·��
@param parten ͨ���
@param pcb ѹ���ص��ӿ�
@param pctx ѹ���ص��Զ������
@return �ɹ�����0
*/
int COMMON_LIB_EXPORT zip_compress2(const wchar_t* src, const wchar_t* dst, const wchar_t* parten, zip_compress_callback pcb, void* pctx);
int COMMON_LIB_EXPORT zip_compress(const wchar_t* src, const wchar_t* dst, zip_compress_callback pcb, void* pctx);

/*!
@brief ��ѹ�ص�ԭ��
@param pctx �ص��Զ������
@return ���ط�0ȡ����ѹ
*/
typedef zip_compress_callback zip_uncompress_callback;

/*!
@brief ��ѹ��
@param src zip�ļ�ȫ·��
@param dst ����ļ���·��
@param pcb ��ѹ�ص��ӿ�
@param pctx ��ѹ�ص��Զ������
@return �ɹ�����0
*/
int COMMON_LIB_EXPORT zip_uncompress(const wchar_t* src, const wchar_t* dst, zip_uncompress_callback pcb, void* pctx);

#endif
