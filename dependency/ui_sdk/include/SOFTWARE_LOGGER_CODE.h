#ifndef SOFTWARE_ERROR_CODE_H__
#define SOFTWARE_ERROR_CODE_H__

/*!
@brief ����ȼ�����
*/
#define ERROR_CODE_LEVEL_FATAL   1
#define ERROR_CODE_LEVEL_ERROR   2
#define ERROR_CODE_LEVEL_WARNING 3
#define ERROR_CODE_LEVEL_INFO    4
#define ERROR_CODE_LEVEL_DEBUG   5
#define ERROR_CODE_LEVEL_PROFILE 6

/*!
@brief �������
@param category_code SOFTWARE_CREASH
*/
#define SOFTWARE_CREASH "0001"
//////////////////<SOFTWARE_CREASH Start>//////////////////
/*!
@brief ����
@param level fatal
@param log_code SOFTWARE_CREASH_REPORT
@param log_data �Զ���
@param extend_data �Զ���
@param files *.zip
*/
#define SOFTWARE_CREASH_REPORT "0001"
//////////////////<SOFTWARE_CREASH End>//////////////////


/*!
@brief ���״̬
@param category_code SOFTWARE_STATE
*/
#define SOFTWARE_STATE "0002"
//////////////////<SOFTWARE_STATE Start>//////////////////
	/*!
	@brief ��
	@param level info
	@param log_code SOFTWARE_STATE_OPEN
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_STATE_OPEN "0001"

	/*!
	@brief �ر�
	@param level info
	@param log_code SOFTWARE_STATE_CLOSE
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_STATE_CLOSE "0002"
//////////////////<SOFTWARE_STATE End>//////////////////


/*!
@brief iCloud��صĲ����붨��
@param category_code SOFTWARE_ICLOUD
*/
#define SOFTWARE_ICLOUD "0025"
//////////////////<SOFTWARE_ICLOUD Start>//////////////////
	/*!
	@brief ��¼ʧ��(�������)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_PASSWORD
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_PASSWORD "0001"

	/*!
	@brief ��¼ʧ��(�������)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_NONETWORK
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define   SOFTWARE_ICLOUD_LOGIN_ERROR_NONETWORK "0002"

	/*!
	@brief ��¼ʧ��(���糬ʱ)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_TIMEOUT
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_TIMEOUT "0003"

	/*!
	@brief ��¼ʧ��(�û�ȡ��)
	@param level warning
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_CANCEL
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_CANCEL "0004"

	/*!
	@brief ��¼ʧ��(������֤)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_STEP
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_STEP "0005"

	/*!
	@brief ��¼ʧ��(δ֪����)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_UNKNOWN
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_UNKNOWN "0006"

	/*!
	@brief ��¼�ɹ�
	@param level info
	@param log_code SOFTWARE_ICLOUD_LOGIN_SUCCESS
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_LOGIN_SUCCESS "0007"

	/*!
	@brief ����ʧ��(�������ļ�)
	@param level error
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_ERROR_NOFILE
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_ERROR_NOFILE "0008"

	/*!
	@brief ����ʧ��(δ֪����)
	@param level error
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_ERROR_UNKNOWN
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_ERROR_UNKNOWN "0009"

	/*!
	@brief ���سɹ�
	@param level info
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_SUCCESS
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_SUCCESS "0010"

	/*!
	@brief �û�ȡ������
	@param level warning
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_CANCEL
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_CANCEL "0013"

	/*!
	@brief �˻�������Ϣ
	@param level info
	@param log_code SOFTWARE_ICLOUD_ACCOUNT_INFO
	@param log_data md5(iCloud account)
	@param extend_data json: {[serial, size, version, snapshot id], [serial, size, version, snapshot id]...}
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_ACCOUNT_INFO "0011"

	/*!
	@brief ��ʼ����
	@param level info
	@param log_code SOFTWARE_ICLOUD_START_DOWNLOAD
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_START_DOWNLOAD "0012"

	/*!
	@brief ��¼ʧ��(�˻�δ����)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_NOT_USE
	@param log_data md5(iCloud account)
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_NOT_USE "0014"

	/*!
	@brief ��ʼɨ��
	@param level info
	@param log_code SOFTWARE_ICLOUD_START_SCAN
	@param log_data ��дmobile-icloud
	@param extend_data �豸���к�/UDID ����ѡ���豸���кţ����豸���кŲ�������ѡ���豸UDID�����������������д
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_START_SCAN "0015"

	/*!
	@brief ICloud������ɺ󴴽����ݳɹ�
	@param level info
	@param log_code SOFTWARE_ICLOUD_BACKUP_CHOOSE_SUCCESS
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files δʹ��
	*/
	#define SOFTWARE_ICLOUD_BACKUP_CHOOSE_SUCCESS "0016"

	/*!
	@brief ICloud������ɺ󴴽�����ʧ��
	@param level error
	@param log_code SOFTWARE_ICLOUD_BACKUP_CHOOSE_ERROR
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_BACKUP_CHOOSE_ERROR "0017"
//////////////////<SOFTWARE_ICLOUD End>//////////////////


/*!
@brief �Զ���װiTunes�붨��
@param category_code SOFTWARE_INSTALL_ITUNES
*/
#define SOFTWARE_INSTALL_ITUNES "0026"
//////////////////<SOFTWARE_INSTALL_ITUNES Start>//////////////////
	/*!
	@brief ����ʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_DOWNLOAD_ERROR
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_DOWNLOAD_ERROR "0001"

	/*!
	@brief ȡ������
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_DOWNLOAD_CANCEL
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_DOWNLOAD_CANCEL "0002"

	/*!
	@brief ��ѹʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_DECOMPRESS_ERROR
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_DECOMPRESS_ERROR "0003"

	/*!
	@brief ȡ����ѹ
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_DECOMPRESS_CANCEL
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_DECOMPRESS_CANCEL "0004"

	/*!
	@brief ��װʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_SETUP_ERROR
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_SETUP_ERROR "0005"

	/*!
	@brief ȡ����װ
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_SETUP_CANCEL
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_SETUP_CANCEL "0006"

	/*!
	@brief �������سɹ�
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_LOAD_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_LOAD_SUCCESS "0007"

	/*!
	@brief ��������ʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_LOAD_ERROR
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_LOAD_ERROR "0008"

	/*!
	@brief ��ȡiTunes���ص�ַʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_GETURL_ERROR
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_GETURL_ERROR "0009"

	/*!
	@brief ȡ����ȡiTunes���ص�ַ
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_GETURL_CANCEL
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_GETURL_CANCEL "0010"

	/*!
	@brief δ��װiTunes����
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_NEED_INSTALL
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_NEED_INSTALL "0013"

	/*!
	@brief �������δ����
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_NEED_SERVICES
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_NEED_SERVICES "0014"

	/*!
	@brief ��ȡiTunes���ص�ַ�ɹ�
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_GETURL_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_GETURL_SUCCESS "0015"

	/*!
	@brief �������
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_DOWNLOAD_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_DOWNLOAD_SUCCESS "0016"

	/*!
	@brief ��ѹ���
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_DECOMPRESS_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_DECOMPRESS_SUCCESS "0017"

	/*!
	@brief ��װ�ɹ�
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_SETUP_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_SETUP_SUCCESS "0018"

	/*!
	@brief itunes��װʧ������ʧ��
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_UNKNOWN_ERROR
	@param log_data �Զ���
	@param extend_data �������ͣ�1603��1618��1620��
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_ITUNES_UNKNOWN_ERROR "0019"
//////////////////<SOFTWARE_INSTALL_ITUNES End>//////////////////


/*!
@brief QQ�����Ϣ�ռ��붨��
@param category_code SOFTWARE_QQ_OPERATION
*/
#define SOFTWARE_QQ_OPERATION "0027"
//////////////////<SOFTWARE_QQ_OPERATION Start>//////////////////
	/*!
	@brief QQ�˺�����
	@param level info
	@param log_code SOFTWARE_QQ_OPERATION_ACCOUNTINFO
	@param log_data ÿ���˻���Ӧ�����ݿ��ļ���С,��','��Ϊ�ָ���,��: [size1,size2,size3....]
	@param extend_data �˻�����
	@param files δʹ��
	*/
	#define SOFTWARE_QQ_OPERATION_ACCOUNTINFO "0001"

	/*!
	@brief QQ�汾
	@param level info
	@param log_code SOFTWARE_QQ_OPERATION_VERSION
	@param log_data json: {[bound_id, verison], [bound_id, verison], [bound_id, verison]...}
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_QQ_OPERATION_VERSION "0002"
//////////////////<SOFTWARE_QQ_OPERATION End>//////////////////


/*!
@brief �ռ��������������Ϣ
@param category_code SOFTWARE_WECHAT_OPERATION
*/
#define SOFTWARE_COLLECT_OTHER_PRODUCT "0028"
//////////////////<SOFTWARE_COLLECT_OTHER_PRODUCT Start>//////////////////
	/*!
	@brief ��Ʒ��Ϣ
	@param level info
	@param log_code SOFTWARE_QQ_OPERATION_VERSION
	@param log_data ��Ʒ��Ϣ: app_name:app_version
	@param extend_data �Ƿ�ע��: True/False
	@param files δʹ��
	*/
	#define SOFTWARE_COLLECT_OTHER_PRODUCT_INFO "0001"
//////////////////<SOFTWARE_COLLECT_OTHER_PRODUCT End>//////////////////


/*!
@brief ΢�������Ϣ�ռ��붨��
@param category_code SOFTWARE_WECHAT_OPERATION
*/
#define SOFTWARE_WECHAT_OPERATION "0029"
//////////////////<SOFTWARE_WECHAT_OPERATION Start>//////////////////
	/*!
	@brief ΢���˺�����
	@param level info
	@param log_code SOFTWARE_WECHAT_OPERATION_ACCOUNTINFO
	@param log_data json: ÿ���˻���Ӧ�����ݿ��ļ���С,��','��Ϊ�ָ���,��: [size1,size2,size3....]
	@param extend_data �˻�����
	@param files δʹ��
	*/
	#define SOFTWARE_WECHAT_OPERATION_ACCOUNTINFO "0001"

	/*!
	@brief ΢�Ű汾
	@param level info
	@param log_code SOFTWARE_WECHAT_OPERATION_VERSION
	@param log_data json: {[bound_id, verison], [bound_id, verison], [bound_id, verison]...}
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_WECHAT_OPERATION_VERSION "0002"
//////////////////<SOFTWARE_WECHAT_OPERATION End>//////////////////


/*!
@brief �豸ҳ����Ϣ�붨��
@param category_code SOFTWARE_MOBILE_DEVICE
*/
#define SOFTWARE_MOBILE_DEVICE "0034"
//////////////////<SOFTWARE_MOBILE_DEVICE Start>//////////////////
	/*!
	@brief δ֪����(���Ӻ�, android/iosͨ��)
	@param level error
	@param log_code SOFTWARE_MOBILE_DEVICE_UNKNOWNERROR
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_MOBILE_DEVICE_UNKNOWNERROR "0001"

	/*!
	@brief δ����(���Ӻ�, ios)
	@param level error
	@param log_code SOFTWARE_MOBILE_DEVICE_NOTTRUSTED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_MOBILE_DEVICE_NOTTRUSTED "0002"

	/*!
	@brief �����汾��ƥ��(���Ӻ�, ios)
	@param level error
	@param log_code SOFTWARE_MOBILE_DEVICE_LOWERITUNES
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_MOBILE_DEVICE_LOWERITUNES "0003"

	/*!
	@brief �ɹ�(���Ӻ�, android/iosͨ��)
	@param level info
	@param log_code SOFTWARE_MOBILE_DEVICE_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_MOBILE_DEVICE_SUCCESS "0004"

	/*!
	@brief ����(������, ios)
	@param level warning
	@param log_code SOFTWARE_MOBILE_DEVICE_PASSWORDPROTECTED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_MOBILE_DEVICE_PASSWORDPROTECTED "0005"

	/*!
	@brief ����(������, ios)
	@param level warning
	@param log_code SOFTWARE_MOBILE_DEVICE_TRUSTCOMPUTER
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_MOBILE_DEVICE_TRUSTCOMPUTER "0006"

	/*!
	@brief ��ʼɨ��(android/iosͨ��)
	@param level info
	@param log_code SOFTWARE_MOBILE_DEVICE_START_SCAN
	@param log_data ��дmobile-device
	@param extend_data �豸���к�/UDID ����ѡ���豸���кţ����豸���кŲ�������ѡ���豸UDID�����������������д
	@param files δʹ��
	*/
	#define SOFTWARE_MOBILE_DEVICE_START_SCAN "0007"

	/*!
	@brief ��ʼ����(android/iosͨ��)
	@param level info
	@param log_code SOFTWARE_MOBILE_DEVICE_START_CONNECT
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_MOBILE_DEVICE_START_CONNECT "0008"
	
	 /*!
    @brief δROOT(���Ӻ�, android)
    @param level error
    @param log_code SOFTWARE_MOBILE_DEVICE_ERROR_NOROOT
    @param log_data �Զ���
    @param extend_data �Զ���
    @param files *.zip
    */
    #define SOFTWARE_MOBILE_DEVICE_ERROR_NOROOT "0009"

    /*!
    @brief ����δ��װ(������, android)
    @param level warning
    @param log_code SOFTWARE_MOBILE_DEVICE_NODRIVER
    @param log_data �Զ���
    @param extend_data �Զ���
    @param files δʹ��
    */
    #define SOFTWARE_MOBILE_DEVICE_NODRIVER "0010"

    /*!
    @brief δ�򿪵���ģʽ(������, android)
    @param level warning
    @param log_code SOFTWARE_MOBILE_DEVICE_NODEBUG
    @param log_data �Զ���
    @param extend_data �Զ���
    @param files δʹ��
    */
    #define SOFTWARE_MOBILE_DEVICE_NODEBUG "0011"

    /*!
    @brief USBδ��Ȩ(������, android)
    @param level warning
    @param log_code SOFTWARE_MOBILE_DEVICE_NOAUTHOR
    @param log_data �Զ���
    @param extend_data �Զ���
    @param files δʹ��
    */
    #define SOFTWARE_MOBILE_DEVICE_NOAUTHOR "0012"

    /*!
    @brief ��������ģʽ(���Ӻ�, android)
    @param level info
    @param log_code SOFTWARE_MOBILE_DEVICE_SUCCESS_DOWNGRADE
    @param log_data �Զ���
    @param extend_data �Զ���
    @param files δʹ��
    */
    #define SOFTWARE_MOBILE_DEVICE_SUCCESS_DOWNGRADE "0013"
//////////////////<SOFTWARE_MOBILE_DEVICE End>//////////////////


/*!
@brief FrameWork���أ���װ��ע�����
@param category_code SOFTWARE_INSTALL_FRAMEWORK
*/
#define SOFTWARE_INSTALL_FRAMEWORK "0035"
//////////////////<SOFTWARE_INSTALL_FRAMEWORK Start>//////////////////
	/*!
	@brief Framework�Ѱ�װ
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_YES
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_YES "0001"

	/*!
	@brief Frameworkδ��װ
	@param level warning
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_NO
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_NO "0002"

	/*!
	@brief Framework���سɹ�
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_SUCCESS "0003"

	/*!
	@brief Framework����ʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_FAILED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_FAILED "0004"

	/*!
	@brief Frameworkȡ������
	@param level warning
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_CANCEL
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_CANCEL "0005"

	/*!
	@brief Framework��װ�ɹ�
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_INSTALL_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_INSTALL_SUCCESS "0006"

	/*!
	@brief Framework��װʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_INSTALL_FAILED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_INSTALL_FAILED "0007"

	/*!
	@brief Frameworkȡ����װ
	@param level warning
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_INSTALL_CANCEL
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_INSTALL_CANCEL "0008"

	/*!
	@brief Framework���ע��ɹ�
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_REGISTER_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_REGISTER_SUCCESS "0009"

	/*!
	@brief Framework���ע��ʧ��
	@param level error
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_REGISTER_FAILED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_REGISTER_FAILED "0010"
//////////////////<SOFTWARE_INSTALL_FRAMEWORK End>//////////////////


/*!
@brief iTunes�����б�
@param category_code SOFTWARE_ITUNES_BACKUP
*/
#define SOFTWARE_ITUNES_BACKUP "0036"
//////////////////<SOFTWARE_ITUNES_BACKUP Start>//////////////////
	/*!
	@brief �ռ��û�������Ϣ
	@param level info
	@param log_code SOFTWARE_ITUNES_BACKUP_INFO
	@param log_data json: {[serial, udid, size, version], [serial, udid, size, version]...}
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_ITUNES_BACKUP_INFO "0001"

	/*!
	@brief ���û��Զ���Ŀ¼�ɹ�
	@param level info
	@param log_code SOFTWARE_ITUNES_BACKUP_CHOOSE_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_ITUNES_BACKUP_CHOOSE_SUCCESS "0002"

	/*!
	@brief ���û��Զ���Ŀ¼ʧ��
	@param level error
	@param log_code SOFTWARE_ITUNES_BACKUP_CHOOSE_ERROR
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_ITUNES_BACKUP_CHOOSE_ERROR "0003"

	/*!
	@brief ��ʼɨ��
	@param level info
	@param log_code SOFTWARE_ITUNES_BACKUP_START_SCAN
	@param log_data ��дmoible-backup
	@param extend_data �豸���к�/UDID ����ѡ���豸���кţ����豸���кŲ�������ѡ���豸UDID�����������������д
	@param files δʹ��
	*/
	#define SOFTWARE_ITUNES_BACKUP_START_SCAN "0004"
//////////////////<SOFTWARE_ITUNES_BACKUP End>//////////////////


/*!
@brief �豸�򱸷ݼ��
@param category_code SOFTWARE_CHECK_SETUP
*/
#define SOFTWARE_CHECK_SETUP "0037"
//////////////////<SOFTWARE_CHECK_SETUP Start>//////////////////
	/*!
	@brief �������ͨ��
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_LOCKSCREEN_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_CHECK_SETUP_LOCKSCREEN_SUCCESS "0001"

	/*!
	@brief ����������
	@param level error
	@param log_code SOFTWARE_CHECK_SETUP_LOCKSCREEN_FAILED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_CHECK_SETUP_LOCKSCREEN_FAILED "0002"

	/*!
	@brief ���ݼ��ܼ��ͨ��
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_PASSWORD_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_CHECK_SETUP_BACKUP_PASSWORD_SUCCESS "0003"

	/*!
	@brief ���ݼ��ܼ�����
	@param level error
	@param log_code SOFTWARE_CHECK_SETUP_PASSWORD_FAILED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_CHECK_SETUP_BACKUP_PASSWORD_FAILED "0004"

	/*!
	@brief ���뱣�����ͨ��
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_PW_PROTECTED_SUCCESS
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_CHECK_SETUP_PW_PROTECTED_SUCCESS "0005"

	/*!
	@brief ���뱣�����ͨ��
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_PW_PROTECTED_FAILED
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_CHECK_SETUP_PW_PROTECTED_FAILED "0006"
//////////////////<SOFTWARE_CHECK_SETUP End>//////////////////


/*!
@brief ������ָ���Ϣ��
@param category_code SOFTWARE_RECOVER_DATA
*/
#define SOFTWARE_RECOVER_DATA "0038"
//////////////////<SOFTWARE_RECOVER_DATA Start>//////////////////
	/*!
	@brief ����(��ʼ����)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_START
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_START "0001"

	/*!
	@brief ����(�����ļ���������)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_MANIFEST
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_MANIFEST "0002"

	/*!
	@brief ����(����ʧ��)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_DECRYPT
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_DECRYPT "0003"

	/*!
	@brief ����(��������)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_LOCKERR
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_LOCKERR "0004"

	/*!
	@brief ����(ͨ��ʧ��)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_SOCKETERR
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_SOCKETERR "0005"

	/*!
	@brief ����(PC���̿ռ䲻��)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_FREESPACE
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_FREESPACE "0006"

	/*!
	@brief ����(�û���������)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_SETUP
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_SETUP "0007"

	/*!
	@brief ����(PC����д����)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_DISKERR
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_DISKERR "0008"

	/*!
	@brief ����(LSP����)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_LSPERR
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_LSPERR "0009"

	/*!
	@brief ����(�豸�ռ䲻��)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_DEVFREESPACE
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_DEVFREESPACE "0010"

	/*!
	@brief ����(�豸�ļ���ռ��)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_MULTIERROR
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_MULTIERROR "0011"

	/*!
	@brief ����(unknown-domain)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWNDOMAIN
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWNDOMAIN "0012"

	/*!
	@brief ����(δ֪����)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWN
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWN "0013"

	/*!
	@brief ����(ȡ������)
	@param level warning
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_CANCEL
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_CANCEL "0014"

	/*!
	@brief ����(���ݳɹ�)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_SUCCESS
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_SUCCESS "0015"

	/*!
	@brief ɨ��(��ʼɨ��)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_SCAN_START
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_START "0016"

	/*!
	@brief ɨ��(������Ŀ��App)
	@param level warning
	@param log_code SOFTWARE_SCAN_DATA_SCAN_ERROR_NOAPP
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_ERROR_NOAPP "0017"

	/*!
	@brief ɨ��(ȱʧ�ļ�)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_SCAN_ERROR_LACKFILE
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_ERROR_LACKFILE "0018"

	/*!
	@brief ɨ��(δ֪����)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_SCAN_ERROR_UNKNOWN
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_ERROR_UNKNOWN "0019"

	/*!
	@brief ɨ��(ȡ��ɨ��)
	@param level warning
	@param log_code SOFTWARE_SCAN_DATA_SCAN_CANCEL
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_CANCEL "0020"

	/*!
	@brief ɨ��(ɨ��ɹ�)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_SCAN_SUCCESS
	@param log_data ����������
	@param extend_data ɨ����豸����(device/backup/icloud)
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_SUCCESS "0021" 

	/*!
	@brief ɨ��ɹ��󣬻ָ�����������
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_NUMBER
	@param log_data ����������
	@param extend_data ��������Ŀ(��: ����(112) ΢����Ϣ(11,100,9))
	@param files δʹ��
	*/
	#define SOFTWARE_SCAN_DATA_NUMBER "0022" 

	/*!
	@brief �����ݣ�ȱʧ��Ҫ�ļ�
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_LACKFILE
	@param log_data ����������
	@param extend_data ɨ����豸���ͣ�device/backup��
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_LACKFILE "0023"

	/*!
	@brief �����ݣ������豸����ԱȨ��ʧ��
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_NOSUPPER
	@param log_data ����������
	@param extend_data ɨ����豸���ͣ�device/backup��
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_NOSUPPER "0024"

	/*!
	@brief �����ݣ���ȡ�豸�ļ�ʧ��
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_NOPULL
	@param log_data ����������
	@param extend_data ɨ����豸���ͣ�device/backup��
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_NOPULL "0025"

	/*!
	@brief �����ݣ���ѹ�豸�����ļ�ʧ��
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_DECOMPRESS
	@param log_data ����������
	@param extend_data ɨ����豸���ͣ�device/backup��
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_DECOMPRESS "0126"

	/*!
	@brief �����ݣ���Ϣ����δ֪�쳣
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_UNKNOWNRECMSG
	@param log_data ����������
	@param extend_data ɨ����豸���ͣ�device/backup��
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_UNKNOWNRECMSG "0026"

	/*!
	@brief manifest.db��С�Ѽ�
	@param level info
	@param log_code SOFTWARE_BACKUP_DATA_MANIFEST_SIZE
	@param log_data ����������
	@param extend_data ���ݿ��С
	@param files δʹ��
	*/
	#define SOFTWARE_BACKUP_DATA_MANIFEST_SIZE "0027"

	/*!
	@brief manifest.db����ʱ���Ѽ�
	@param level info
	@param log_code SOFTWARE_BACKUP_DATA_ANALYSE_TIME
	@param log_data ����������
	@param extend_data �����ļ�ʱ��
	@param files δʹ��
	*/
	#define SOFTWARE_BACKUP_DATA_ANALYSE_TIME "0028"
//////////////////<SOFTWARE_RECOVER_DATA End>//////////////////


/*!
@brief ���������Ϣ��
@param category_code SOFTWARE_EXPORT_DATA
*/
#define SOFTWARE_EXPORT_DATA "0039"
//////////////////<SOFTWARE_EXPORT_DATA Start>//////////////////
	/*!
	@brief ������PC�ɹ�
	@param level info
	@param log_code SOFTWARE_EXPORT_DATA_TOPC_SUCCESS
	@param log_data ����������
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_EXPORT_DATA_TOPC_SUCCESS "0001"

	/*!
	@brief ������PCʧ��
	@param level error
	@param log_code SOFTWARE_EXPORT_DATA_TOPC_FAILED
	@param log_data ����������
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_EXPORT_DATA_TOPC_FAILED "0002"

	/*!
	@brief �������豸�ɹ�
	@param level info
	@param log_code SOFTWARE_EXPORT_DATA_TODEVICE_SUCCESS
	@param log_data ����������
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_EXPORT_DATA_TODEVICE_SUCCESS "0003"

	/*!
	@brief �������豸ʧ��
	@param level error
	@param log_code SOFTWARE_EXPORT_DATA_TODEVICE_FAILED
	@param log_data ����������
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_EXPORT_DATA_TODEVICE_FAILED "0004"
//////////////////<SOFTWARE_EXPORT_DATA End>//////////////////


/*!
@brief �ֱ�����Ϣ��
@param category_code SOFTWARE_SCREEN
*/
#define SOFTWARE_SCREEN "0040"
//////////////////<SOFTWARE_SCREEN Start>//////////////////
	/*!
	@brief �����ֱ���
	@param level info
	@param log_code SOFTWARE_NORMAL_SCREEN_REPORT
	@param log_data ���X�߶�
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_NORMAL_SCREEN_REPORT "0001"
		/*!
	@brief �߱���
	@param level info
	@param log_code SOFTWARE_HIGH_SCREEN_REPORT
	@param log_data ���X�߶�
	@param extend_data �Զ���
	@param files *.zip
	*/
	#define SOFTWARE_HIGH_SCREEN_REPORT "0002"
//////////////////<SOFTWARE_SCREEN End>//////////////////


/*!
@brief momo�����Ϣ�ռ��붨��
@param category_code SOFTWARE_MOMO_OPERATION
*/
#define SOFTWARE_MOMO_OPERATION "0041"
//////////////////<SOFTWARE_MOMO_OPERATION Start>//////////////////
	/*!
	@brief İİ�˺�����
	@param level info
	@param log_code SOFTWARE_MOMO_OPERATION_ACCOUNTINFO
	@param log_data ÿ���˻���Ӧ�����ݿ��ļ���С,��','��Ϊ�ָ���,��: [size1,size2,size3....]
	@param extend_data �˻�����
	@param files δʹ��
	*/
	#define SOFTWARE_MOMO_OPERATION_ACCOUNTINFO "0001"

	/*!
	@brief İİ�汾
	@param level info
	@param log_code SOFTWARE_MOMO_OPERATION_VERSION
	@param log_data json: {[bound_id, verison], [bound_id, verison], [bound_id, verison]...}
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_MOMO_OPERATION_VERSION "0002"
//////////////////<SOFTWARE_MOMO_OPERATION End>//////////////////

/*!
@brief ���ע�������Ϣ�ռ�
@param category_code SOFTWARE_REGISTE
*/
#define SOFTWARE_REGISTE "0042"
//////////////////<SOFTWARE_REGISTE Start>//////////////////
	/*!
	@brief �������ʱ�Զ�����ע���
	@param level info
	@param log_code SOFTWARE_REGISTE_LAUNCH
	@param log_data �Զ���
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_REGISTE_LAUNCH "0001"

	/*!
	@brief ע��ɹ�
	@param level info
	@param log_code SOFTWARE_REGISTE_SUCCESS
	@param log_data δ����
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_REGISTE_SUCCESS "0002"

	/*!
	@brief ע��ʧ��
	@param level warning
	@param log_code SOFTWARE_REGISTE_FAILURE
	@param log_data ������ 
	@param extend_data �Զ���
	@param files δʹ��
	*/
	#define SOFTWARE_REGISTE_FAILURE "0003"
	
	
	/*!
	@brief ע���豸����ʱ�䣺��������
	@param level info
	@param log_code SOFTWARE_REGISTE_DEVICE_TIME_NORMAL
	@param log_data ע������ʱ�䣬ms 
	@param extend_data �ɹ�true,ʧ��false
	@param files δʹ��
	*/
	#define SOFTWARE_REGISTE_DEVICE_TIME_NORMAL "0004"
	
	/*!
	@brief ע���豸����ʱ��:�����������棬ע��ɹ���ע���豸
	@param level info
	@param log_code SOFTWARE_REGISTE_DEVICE_TIME_DATA
	@param log_data ע������ʱ�䣬ms 
	@param extend_data �ɹ�true,ʧ��false
	@param files δʹ��
	*/
	#define SOFTWARE_REGISTE_DEVICE_TIME_DATA "0005"
	
		/*!
	@brief ע���豸����ʱ��:�����������棬�㵽����pc��ע��ɹ���ע���豸
	@param level info
	@param log_code SOFTWARE_REGISTE_DEVICE_TIME_RECOVERY
	@param log_data ע������ʱ�䣬ms 
	@param extend_data �ɹ�true,ʧ��false
	@param files δʹ��
	*/
	#define SOFTWARE_REGISTE_DEVICE_TIME_RECOVERY "0006"
//////////////////<SOFTWARE_REGISTE End>//////////////////




/*!
@brief ����������
@param category_code DATA_PLUGIN_SEARCH
*/
#define DATA_PLUGIN_SEARCH "0043"
//////////////////<DATA_PLUGIN_SEARCH Start>//////////////////
	/*!
	@brief ������ʼ
	@param level info
	@param log_code DATA_PLUGIN_SEARCH_START
	@param log_data ����������
	@param extend_data ������Ự����
	@param files δʹ��
	*/
	#define DATA_PLUGIN_SEARCH_START "0001"

	/*!
	@brief ��������
	@param level info
	@param log_code DATA_PLUGIN_SEARCH_END
	@param log_data ����������
	@param extend_data �������ĻỰ��
	@param files δʹ��
	*/
	#define DATA_PLUGIN_SEARCH_END "0002"
//////////////////<DATA_PLUGIN_SEARCH End>//////////////////



/*!
@brief ��¼
@param category_code DATA_PLUGIN_SEARCH
*/
#define SOFEWARE_LOGIN "0050"
//////////////////<SOFEWARE_LOGIN Start>//////////////////
	/*!
	@brief ��¼�ɹ�
	@param level info
	@param log_code SOFEWARE_LOGIN_SUCCESS
	@param log_data ��¼�ʺ�
	@param extend_data δʹ��
	@param files δʹ��
	*/
	#define SOFEWARE_LOGIN_SUCCESS "0001"

	/*!
	@brief ��¼ʧ��
	@param level error
	@param log_code DATA_PLUGIN_SEARCH_END
	@param log_data ��¼�ʺ�
	@param extend_data ʧ��ԭ��ʧ����
	@param files *.zip
	*/
	#define SOFEWARE_LOGIN_FAILURE "0002"
	
	/*!
	@brief �������������¼����
	@param level error
	@param log_code DATA_PLUGIN_SEARCH_END
	@param log_data �Ƿ��Զ���¼���Զ���¼��1�������Զ���¼��0��
	@param extend_data δʹ��
	@param files δʹ��
	*/
	#define SOFEWARE_LOGIN_START "0003"
//////////////////<SOFEWARE_LOGIN End>//////////////////



/*!
@brief ������Ȩ��ʾ
@param category_code SOFEWARE_AUTH
*/
#define SOFEWARE_AUTH "0051"
//////////////////<SOFEWARE_AUTH Start>//////////////////
	/*!
	@brief ��������Զ�������Ȩ��ʾ
	@param level info
	@param log_code SOFEWARE_AUTH_AUTO
	@param log_data δʹ��
	@param extend_data δʹ��
	@param files δʹ��
	*/
	#define SOFEWARE_AUTH_AUTO "0001"
//////////////////<SOFEWARE_AUTH End>//////////////////

/*!
@brief ������Ȩ��ʾ
@param category_code FIRST_START_SOFTWARE
*/
#define FIRST_START_SOFTWARE "0052"
//////////////////<FIRST_START_SOFTWARE Start>//////////////////
	/*!
	@brief ��������״������������ô���
	@param level info
	@param log_code SOFEWARE_AUTH_AUTO
	@param log_data δʹ��
	@param extend_data δʹ��
	@param files δʹ��
	*/
	#define FIRST_START_SOFTWARE_WINDOW "0001"
//////////////////<FIRST_START_SOFTWARE End>//////////////////

/*!
@brief ����������Դ
@param category_code SOFTWARE_SHOW_WINDOW
*/
#define SOFTWARE_SHOW_WINDOW "0053"
//////////////////<SOFTWARE_SHOW_WINDOW Start>//////////////////
	/*!
	@brief �������򴰿ڵ���Դ
	@param level info
	@param log_code SOFTWARE_PURCHASE
	@param log_data smp�룬�����Դ
	@param extend_data δʹ��
	@param files δʹ��
	*/
	#define SOFTWARE_SHOW_WINDOW_PURCHASE "0001"
	
	/*!
	@brief ������¼���ڵ���Դ
	@param level info
	@param log_code SOFTWARE_LOGIN
	@param log_data smp�룬�����Դ
	@param extend_data δʹ��
	@param files δʹ��
	*/
	#define SOFTWARE_SHOW_WINDOW_LOGIN "0002"
//////////////////<SOFTWARE_PURCHASE End>//////////////////


/*!
@brief ������������ϵ��Խ׶������ռ�
@param DEVELOPER_DEBUG_LOG
@note �ô���Ž׶��Դ��ڣ�����Ҫ����������Ѿ���λ������ô������Ҫ��������Ƴ�
*/
#define DEVELOPER_DEBUG_LOG "9990"
//////////////////<DEVELOPER_DEBUG_LOG Start>//////////////////
	/*!
    @brief �ռ�iTunes������װʱ
    @param level error
    @param log_code DEVELOPER_DEBUG_LOG_ITUNES_MSI_LOG
    @param log_data �������Զ���
    @param extend_data �������Զ���
    @param files *.zip 
	@note ע��ô�����ռ�����־�ļ������ɿ������Զ���,��ѹ��������ļ���С���ܳ���1MB
    */
    #define DEVELOPER_DEBUG_LOG_ITUNES_MSI_LOG "0001"
	
	/*!
    @brief �ռ��ֻ�ʹ�ÿռ�ʹ���ʣ���С
    @param level info
    @param log_code DEVELOPER_DEBUG_LOG_IPHONE_USER_SIZE_AND_DISK_FREE_SIZE
    @param log_data �ֻ�ʹ�ÿռ�
    @param extend_data ����ʣ��ռ�
    @param files *.zip 
    */
    #define DEVELOPER_DEBUG_LOG_IPHONE_USER_SIZE_AND_DISK_FREE_SIZE "0002"
//////////////////<DEVELOPER_DEBUG_LOG End>//////////////////

#endif
