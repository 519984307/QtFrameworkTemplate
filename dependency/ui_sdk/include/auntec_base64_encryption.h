#ifndef AUNTEC_BASE64_ENCRYPTION_H__
#define AUNTEC_BASE64_ENCRYPTION_H__

#include <string>

namespace AuntecBased
{
	/*!
	@brief base-64 ����
	@param data ����Դ����
	@param size Դ���ݳ���
	@param bLine �Ƿ�֧�ֻ���
	@return ���ر��������
	*/
	std::string auntec_base64_encode(const unsigned char* data, int size, bool bLine=true);

	/*!
	@brief base-64 ����
	@param data ����Դ����
	@param size Դ���ݳ���
	@param outBytes �����������ʵ����
	@return ���ر��������
	@note ��������ݳ���,���ֽ�Ϊ��λ,�벻Ҫͨ������ֵ����,outBytes�����ǵĽ���󳤶�
	*/
	std::string auntec_base64_decode(const char* data, int size, int& outBytes);
}

#endif
