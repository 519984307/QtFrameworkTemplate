#ifndef AUNTEC_DOWNLOAD_MANAGER_H__
#define AUNTEC_DOWNLOAD_MANAGER_H__

#include "auntec_base_types.h"

// ����������״̬
#define DOWNLOAD_STATE_WAIT 0 // �ȴ�
#define DOWNLOAD_STATE_RUN 1 // ������
#define DOWNLOAD_STATE_PAUSE 2 // ��ͣ
#define DOWNLOAD_STATE_STOP 3 // �û�ȡ��
#define DOWNLOAD_STATE_COMPLETE 4 // ���
#define DOWNLOAD_STATE_ERROR 5 // ����


// ���������󷵻�ֵ wynn
#define DOWNLOAD_ERROR_NORMAL					0   // �ɹ�
#define DOWNLOAD_ERROR_DNS					   -1   // DNS����ʧ��
#define DOWNLOAD_ERROR_SOCKET				   -2   // Socket����ʧ��
#define DOWNLOAD_ERROR_NETWORK				   -3   // ����ͨ��ʧ��
#define DOWNLOAD_ERROR_GETURL				   -4   // ��ȡURLʧ��
#define DOWNLOAD_ERROR_EXCEPT				   -5   // �����쳣
/*!
@brief �������ӿ�
*/
class IDownload
{
public:
	/*!
	@brief ��������
	*/
	virtual bool STDCALL Start() = 0;

	/*!
	@brief ��ͣ����
	@note δʵ��
	*/
	virtual bool STDCALL Pause() = 0;

	/*!
	@brief �ָ�����
	@note δʵ��
	*/
	virtual bool STDCALL Resume() = 0;

	/*!
	@brief ȡ������
	*/
	virtual bool STDCALL Stop() = 0;

	/*!
	@brief ��ȡ���ؽ���
	*/
	virtual int STDCALL Percent() = 0;

	/*!
	@brief ��ȡ����״̬THREAD_STATE_...
	*/
	virtual int STDCALL State() = 0;

	/*!
	@brief ��ȡ���ش������� DOWNLOAD_ERROR_...
	*/
	virtual int STDCALL Error() = 0;

	/*!
	@brief �ͷ�
	*/
	virtual void STDCALL Free() = 0;
};

/*!
@brief ����������
@param url ���ص�ַ
@param filePath ���ػ���·��
@param threadCount �����߳���
@param timeOut �����������ӳ�ʱʱ��
@param errLoopTimes ʧ�����Դ���
@return �ɹ��������ؽӿڣ����򷵻�NULL
*/
extern "C"
EXPORT
IDownload* CreateDownloader
												(
												const char* url,
												const char* filePath,
												int threadCount=4,
												int timeOut=5000,
												int errLoopTimes=1000
												);

#endif