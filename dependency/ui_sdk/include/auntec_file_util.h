#ifndef __AUNTEC_FILE_UTIL_H
#define __AUNTEC_FILE_UTIL_H

#include "auntec_base_types.h"

namespace AuntecBased
{
	/*!
	@brief �ļ��������
	@note ����file_read, file_seek ��ϵ�к���
	*/
#ifdef WIN32
	typedef HANDLE file_handle_t;
#else
	typedef int file_handle_t;
#endif

	///File mode
	const uint16_t fmCreate = 0xFFFF;
	const uint16_t fmOpenRead       = 0x0000;
	const uint16_t fmOpenWrite      = 0x0001;
	const uint16_t fmOpenReadWrite  = 0x0002;

	const uint16_t fmShareCompat    = 0x0000 ; // DOS compatibility mode is not portable
	const uint16_t fmShareExclusive = 0x0010;
	const uint16_t fmShareDenyWrite = 0x0020;
	const uint16_t fmShareDenyRead  = 0x0030 ; // write-only not supported on all platforms
	const uint16_t fmShareDenyNone  = 0x0040;

	/*
	@brief �����ļ�
	@param fileName �ļ���
	@return �ɹ������ļ������ʧ�ܷ���-1
	*/
	file_handle_t auntec_file_create(const char* pFileName);

	/*
	@brief ���ļ�
	@param fileName �ļ���
	@param mode ���ļ���ģʽ���μ��궨�壭File mode
	@return �ɹ������ļ������ʧ�ܷ���-1
	*/
	file_handle_t auntec_file_open(const char* pFileName, uint16_t mode);

	/*
	@brief ��һ���ļ����ȡCount�ֽڵ�Buffer��
	@param handle �ļ����
	@param buffer ������ָ��
	@param Count Ҫ��ȡ���ֽ���
	@return �ɹ����ض�ȡ���ֽ�����ʧ�ܷ���-1
	*/
	int auntec_file_read(file_handle_t handle, void* pBuf, uint32_t count, bool* bEof=NULL);

	/*
	@brief ��Bufferд��Count�ֽڵ�һ���ļ���
	@param handle �ļ����
	@param buffer ������ָ��
	@param Count Ҫд����ֽ���
	@return �ɹ�ʱ����д����ֽ�����ʧ�ܷ���-1
	*/
	int auntec_file_write(file_handle_t handle, const void* pBuf, uint32_t count);

	/*
	@brief ���ļ��ĵ�ǰλ������Ϊ�ļ���β
	@param handle �ļ����
	*/
	bool auntec_file_set_current_end(file_handle_t handle);

	/*
	@brief �����ļ���ǰλ�õ�nOrigin��nOffsetλ��
	@param handle �ļ����
	@param nOffset λ��
	@param nOrigin  SEEK_SET, SEEK_CUR, SEEK_END
	@return �ɹ�ʱ����λ�ã�ʧ�ܷ���-1
	*/
	int64_t auntec_file_seek(file_handle_t handle, int64_t nOffset, int nOrigin);

	/*
	@brief �ر��ļ�
	@param handle �ļ����
	*/
	void auntec_file_close(file_handle_t handle);

	// ö����Seekʱ��λ��
	enum AuntecSeekOrigin{
		///����ʼ
		asoFromBeginning=SEEK_SET, 
		///���ĵ�ǰλ��
		asoFromCurrent=SEEK_CUR,
		///���Ľ���λ��
		asoFromEnd=SEEK_END
	};

	/*!
	@interface IAuntecStream
	@brief Auntec Stream Interface
	*/
	class IAuntecStream
	{
	public:
		/*!
		@brief ��ȡ��ǰλ��
		@return ��ǰλ��
		*/
		virtual int64_t STDCALL GetPosition() = 0;

		/*!
		@brief ���õ�ǰλ��
		@return �ɹ�ʱ���ص�ǰλ�� ʧ��ʱ����-1
		*/
		virtual int64_t STDCALL SetPosition(const int64_t pos) = 0; 
		/*!
		@brief ��������С
		@return ��ȡ��ǰ����С
		*/
		virtual int64_t STDCALL GetSize() = 0; 

		/*!
		@brief �������Ĵ�С
		@return �ɹ�ʱ���ص�ǰλ�� ʧ��ʱ����false
		*/
		virtual bool STDCALL SetSize(const int64_t newSize) = 0; 

		/*!
		@brief �ӻ�����Buffer��ǰλ�����ȡCount��С������
		@param Buffer ������ָ��
		@param Count  Ҫ��ȡ���ֽڴ�С
		@return ���ض�ȡ���ֽڴ�С ʧ�ܷ��أ�1
		*/
		virtual int32_t STDCALL Read(void* pBuf, uint32_t count) = 0 ;

		/*!
		@brief ��Count��С������д��������Buffer�ĵ�ǰλ��
		@param Buffer ������ָ��
		@param Count  Ҫд��ĵ��ֽڴ�С
		@return ����д����ֽڴ�С ʧ��ʱ���أ�1
		*/
		virtual int32_t STDCALL Write(const void* pBuf, uint32_t count) = 0;

		/*!
		@brief ����ǰλ���ƶ���Origin+offset��λ��
		@param Offset�����Origin��λ��
		@param Origin Ҫ�ƶ�����λ��.��ʼ,��ǰ,��β���ַ�ʽ
		@return ���ز������λ�� ʧ��ʱ���أ�1
		*/
		virtual int64_t STDCALL Seek(const int64_t offset,  AuntecSeekOrigin origin) = 0;

		/*!
		@brief ����һ��������Count�ֽ�
		@detail ����һ����Source�п���Count�ֽڣ�Ȼ�󽫵�ǰλ���ƶ�Count�ֽڣ�Ȼ�󷵻ؿ������ֽ�����
					���CountΪ0�������ڶ�ȡ֮ǰ��Source��λ������Ϊ0��Ȼ�󿽱�Source��ȫ�����ݡ����Count��Ϊ0��������Source�ĵ�ǰλ�ÿ�ʼ����
		@param Source Դ����ָ��
		@count  ��ʼ������λ��
		@return �������ֽ���
		*/
		virtual int64_t STDCALL CopyFrom(IAuntecStream* pSource, int64_t count) = 0;

		/*!
		@brief �Ƿ�����ʽ����
		@details ��ʽ����ֻ�ܴ�ǰ����������ߴ�ǰ����д��������������������д
		*/
		virtual bool STDCALL IsStream() = 0;

		/*!
		@brief �Ƿ�������β��
		*/
		virtual bool STDCALL Eof() = 0;

		/*!
		@brief �ͷ����������
		*/
		virtual void STDCALL Free() = 0;
	};

	/*!
	@class CAuntecStreamImpl
	@brief IAuntecStreamʵ��
	*/
	class CAuntecStreamImpl:public IAuntecStream
	{
	public: 
		virtual ~CAuntecStreamImpl(){}

	public:
		virtual int64_t STDCALL GetPosition();
		virtual int64_t STDCALL SetPosition(const int64_t pos);
		virtual int64_t STDCALL GetSize();
		virtual bool STDCALL SetSize(const int64_t newSize);
		virtual int64_t STDCALL CopyFrom(IAuntecStream* pSource, int64_t count);
		virtual void STDCALL Free();
		virtual bool STDCALL IsStream();
	};

	/*!
	@class CAuntecHandleStream
	@brief CAuntecHandleStream abstract class
	*/
	class CAuntecHandleStream:public CAuntecStreamImpl
	{
	public:
		MEXP
		CAuntecHandleStream(file_handle_t handle);
		virtual ~CAuntecHandleStream(){};

	public:
		virtual bool STDCALL SetSize(const int64_t newSize);
		virtual int32_t STDCALL Read(void* pBuf, uint32_t count );
		virtual int32_t STDCALL Write(const void* pBuf, uint32_t count);
		virtual int64_t STDCALL Seek(const int64_t offset, AuntecSeekOrigin origin);
		virtual file_handle_t STDCALL GetHandle();
		virtual bool STDCALL Eof();

	protected:
		bool m_bEof;
		file_handle_t m_Handle;
	};

	/*!
	@class CAuntecFileStream
	@brief �ļ���
	*/
	class CAuntecFileStream:public CAuntecHandleStream
	{
	public:
		MEXP
		CAuntecFileStream(const char* pFileName, uint16_t mode);
		virtual ~CAuntecFileStream();
	};
}

#endif
