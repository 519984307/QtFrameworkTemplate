#ifndef AUNTEC_BASE64_ENCRYPTION_H__
#define AUNTEC_BASE64_ENCRYPTION_H__

#include <string>

namespace AuntecBased
{
	/*!
	@brief base-64 编码
	@param data 编码源数据
	@param size 源数据长度
	@param bLine 是否支持换行
	@return 返回编码后数据
	*/
	std::string auntec_base64_encode(const unsigned char* data, int size, bool bLine=true);

	/*!
	@brief base-64 解码
	@param data 编码源数据
	@param size 源数据长度
	@param outBytes 解码后数据真实长度
	@return 返回编码后数据
	@note 输出的数据长度,以字节为单位,请不要通过返回值计算,outBytes是真是的解码后长度
	*/
	std::string auntec_base64_decode(const char* data, int size, int& outBytes);
}

#endif
