#ifndef __AUNTEC_FILE_UTIL_H
#define __AUNTEC_FILE_UTIL_H

#include "auntec_base_types.h"

namespace AuntecBased
{
	/*!
	@brief 文件句柄类型
	@note 用于file_read, file_seek 等系列函数
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
	@brief 创建文件
	@param fileName 文件名
	@return 成功返回文件句柄，失败返回-1
	*/
	file_handle_t auntec_file_create(const char* pFileName);

	/*
	@brief 打开文件
	@param fileName 文件名
	@param mode 打开文件的模式，参见宏定义－File mode
	@return 成功返回文件句柄，失败返回-1
	*/
	file_handle_t auntec_file_open(const char* pFileName, uint16_t mode);

	/*
	@brief 从一个文件里读取Count字节到Buffer里
	@param handle 文件句柄
	@param buffer 缓冲区指针
	@param Count 要读取的字节数
	@return 成功返回读取的字节数，失败返回-1
	*/
	int auntec_file_read(file_handle_t handle, void* pBuf, uint32_t count, bool* bEof=NULL);

	/*
	@brief 将Buffer写入Count字节到一个文件里
	@param handle 文件句柄
	@param buffer 缓冲区指针
	@param Count 要写入的字节数
	@return 成功时返回写入的字节数，失败返回-1
	*/
	int auntec_file_write(file_handle_t handle, const void* pBuf, uint32_t count);

	/*
	@brief 将文件的当前位置设置为文件结尾
	@param handle 文件句柄
	*/
	bool auntec_file_set_current_end(file_handle_t handle);

	/*
	@brief 设置文件当前位置到nOrigin＋nOffset位置
	@param handle 文件句柄
	@param nOffset 位移
	@param nOrigin  SEEK_SET, SEEK_CUR, SEEK_END
	@return 成功时返回位置，失败返回-1
	*/
	int64_t auntec_file_seek(file_handle_t handle, int64_t nOffset, int nOrigin);

	/*
	@brief 关闭文件
	@param handle 文件句柄
	*/
	void auntec_file_close(file_handle_t handle);

	// 枚举流Seek时的位置
	enum AuntecSeekOrigin{
		///流开始
		asoFromBeginning=SEEK_SET, 
		///流的当前位置
		asoFromCurrent=SEEK_CUR,
		///流的结束位置
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
		@brief 获取当前位置
		@return 当前位置
		*/
		virtual int64_t STDCALL GetPosition() = 0;

		/*!
		@brief 设置当前位置
		@return 成功时返回当前位置 失败时返回-1
		*/
		virtual int64_t STDCALL SetPosition(const int64_t pos) = 0; 
		/*!
		@brief 设置流大小
		@return 获取当前流大小
		*/
		virtual int64_t STDCALL GetSize() = 0; 

		/*!
		@brief 设置流的大小
		@return 成功时返回当前位置 失败时返回false
		*/
		virtual bool STDCALL SetSize(const int64_t newSize) = 0; 

		/*!
		@brief 从缓冲区Buffer当前位置里读取Count大小的数据
		@param Buffer 缓冲区指针
		@param Count  要读取的字节大小
		@return 返回读取的字节大小 失败返回－1
		*/
		virtual int32_t STDCALL Read(void* pBuf, uint32_t count) = 0 ;

		/*!
		@brief 把Count大小的数据写到缓冲区Buffer的当前位置
		@param Buffer 缓冲区指针
		@param Count  要写入的的字节大小
		@return 返回写入的字节大小 失败时返回－1
		*/
		virtual int32_t STDCALL Write(const void* pBuf, uint32_t count) = 0;

		/*!
		@brief 将当前位置移动到Origin+offset的位置
		@param Offset相对于Origin的位移
		@param Origin 要移动到的位置.开始,当前,结尾三种方式
		@return 返回操作后的位置 失败时返回－1
		*/
		virtual int64_t STDCALL Seek(const int64_t offset,  AuntecSeekOrigin origin) = 0;

		/*!
		@brief 从另一个流里拷贝Count字节
		@detail 从另一个流Source中拷贝Count字节，然后将当前位置移动Count字节，然后返回拷贝的字节数。
					如果Count为0，函数在读取之前将Source的位置设置为0，然后拷贝Source的全部内容。如果Count不为0，函数从Source的当前位置开始读。
		@param Source 源流的指针
		@count  开始拷贝的位置
		@return 拷贝的字节数
		*/
		virtual int64_t STDCALL CopyFrom(IAuntecStream* pSource, int64_t count) = 0;

		/*!
		@brief 是否是流式对象
		@details 流式对象只能从前往后读，或者从前往后写，而不能随机读或者随机写
		*/
		virtual bool STDCALL IsStream() = 0;

		/*!
		@brief 是否到了流的尾部
		*/
		virtual bool STDCALL Eof() = 0;

		/*!
		@brief 释放这个流对象
		*/
		virtual void STDCALL Free() = 0;
	};

	/*!
	@class CAuntecStreamImpl
	@brief IAuntecStream实现
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
	@brief 文件流
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
