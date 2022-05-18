#ifndef SOFTWARE_OPERATE_TYPE_H__
#define SOFTWARE_OPERATE_TYPE_H__

/*!
@brief ��������
@param page_code OPEN_PURCHASE
*/
#define OPEN_PURCHASE "0004"
/////////////////////////<OPEN_PURCHASE Start>/////////////////////////
	/*!
	@brief ����˵�����������
	@param event_code OPEN_PURCHASE_MENU
	@param operate_message �Զ���
	*/
	#define OPEN_PURCHASE_MENU "0001"

	/*!
	@brief ���ע�����ѿ�������
	@param event_code OPEN_PURCHASE_MENU
	@param operate_message �Զ���
	*/
	#define OPEN_PURCHASE_REGISTERWIDGET "0002"

	/*!
	@brief �������Ԥ��ҳ��Title��ע����������
	@param event_code OPEN_PURCHASE_MENU
	@param operate_message ����������
	*/
	#define OPEN_PURCHASE_DATAITEM_TITLE "0003"
/////////////////////////<OPEN_PURCHASE End>/////////////////////////


/*!
@brief iCloud��¼ҳ��
@param page_code ICLOUD_LOGIN_PAGECODE
*/
#define ICLOUD_LOGIN_PAGECODE "0005"
/////////////////////////<ICLOUD_LOGIN_PAGECODE Start>/////////////////////////
	/*!
	@brief �����ʼ��¼��ť
	@param event_code ICLOUD_LOGIN_PAGECODE_LOGIN
	@param operate_message �Զ���
	*/
	#define ICLOUD_LOGIN_PAGECODE_LOGIN "0001"
/////////////////////////<ICLOUD_LOGIN_PAGECODE End>/////////////////////////


/*!
@brief iCloud�˻�չʾҳ��
@param page_code ICLOUD_ACCOUNT_PAGECODE
*/
#define ICLOUD_ACCOUNT_PAGECODE "0006"
/////////////////////////<ICLOUD_ACCOUNT_PAGECODE Start>/////////////////////////
	/*!
	@brief ������ذ�ť
	@param event_code ICLOUD_ACCOUNT_PAGECODE_DOWNLOAD
	@param operate_message �Զ���
	*/
	#define ICLOUD_ACCOUNT_PAGECODE_DOWNLOAD "0001"

	/*!
	@brief ���ɾ����ť
	@param event_code ICLOUD_ACCOUNT_PAGECODE_DELETE
	@param operate_message �Զ���
	*/
	#define ICLOUD_ACCOUNT_PAGECODE_DELETE "0002"

	/*!
	@brief ���ɨ�谴ť
	@param event_code ICLOUD_ACCOUNT_PAGECODE_SCAN
	@param operate_message �Զ���
	*/
	#define ICLOUD_ACCOUNT_PAGECODE_SCAN "0003"
/////////////////////////<ICLOUD_ACCOUNT_PAGECODE End>/////////////////////////


/*!
@brief ����ģʽ�л�
@param page_code SWITCH_SCAN_MODE
*/
#define SWITCH_SCAN_MODE "0007"
/////////////////////////<SWITCH_SCAN_MODE Start>/////////////////////////
	/*!
	@brief ����豸ģʽ
	@param event_code SWITCH_SCAN_MODE_MOBILE
	@param operate_message �Զ���
	*/
	#define SWITCH_SCAN_MODE_MOBILE "0001"

	/*!
	@brief ���iTunes����ģʽ
	@param event_code SWITCH_SCAN_MODE_ITUNES
	@param operate_message �Զ���
	*/
	#define SWITCH_SCAN_MODE_ITUNES "0002"

	/*!
	@brief ���iCloud����ģʽ
	@param event_code SWITCH_SCAN_MODE_ICLOUD
	@param operate_message �Զ���
	*/
	#define SWITCH_SCAN_MODE_ICLOUD "0003"
/////////////////////////<SWITCH_SCAN_MODE End>/////////////////////////


/*!
@brief .NetFramework�Զ���װҳ
@param page_code NETFRAMEWORK_INSTALL_PAGECODE
*/
#define NETFRAMEWORK_INSTALL_PAGECODE "0008"
/////////////////////////<NETFRAMEWORK_INSTALL_PAGECODE End>/////////////////////////
	/*!
	@brief ���ȡ����ť
	@param event_code NETFRAMEWORK_INSTALL_PAGECODE_CANCEL
	@param operate_message �Զ���
	*/
	#define NETFRAMEWORK_INSTALL_PAGECODE_CANCEL "0001"

	/*!
	@brief �����װ��ť
	@param event_code NETFRAMEWORK_INSTALL_PAGECODE_INSTALL
	@param operate_message �Զ���
	*/
	#define NETFRAMEWORK_INSTALL_PAGECODE_INSTALL "0002"

	/*!
	@brief ������԰�ť
	@param event_code NETFRAMEWORK_INSTALL_PAGECODE_RETRY
	@param operate_message �Զ���
	*/
	#define NETFRAMEWORK_INSTALL_PAGECODE_RETRY "0003"
/////////////////////////<NETFRAMEWORK_INSTALL_PAGECODE End>/////////////////////////


/*!
@brief iCloud����������ѡ��ҳ
@param page_code ICLOUD_DOWNLOAD_CONFIG_PAGECODE
*/
#define ICLOUD_DOWNLOAD_CONFIG_PAGECODE "0009"
/////////////////////////<ICLOUD_DOWNLOAD_CONFIG_PAGECODE Start>/////////////////////////
	/*!
	@brief ���ȡ����ť
	@param event_code ICLOUD_DOWNLOAD_CONFIG_PAGECODE_CANCEL
	@param operate_message �Զ���
	*/
	#define ICLOUD_DOWNLOAD_CONFIG_PAGECODE_CANCEL "0001"

	/*!
	@brief ���ѡ��ť
	@param event_code ICLOUD_DOWNLOAD_CONFIG_PAGECODE_DOWNLOAD
	@param operate_message ��ѡ��������Ĺ�������
	*/
	#define ICLOUD_DOWNLOAD_CONFIG_PAGECODE_DOWNLOAD "0002"
/////////////////////////<ICLOUD_DOWNLOAD_CONFIG_PAGECODE End>/////////////////////////


/*!
@brief �豸չʾҳ
@param page_code MOBILE_DEVICE_PAGECODE
*/
#define MOBILE_DEVICE_PAGECODE "0010"
/////////////////////////<MOBILE_DEVICE_PAGECODE Start>/////////////////////////
	/*!
	@brief �����ʼɨ��(�����豸)
	@param event_code MOBILE_DEVICE_PAGECODE_NORMAL
	@param operate_message �Զ���
	*/
	#define MOBILE_DEVICE_PAGECODE_NORMAL "0001"

	/*!
	@brief �����ʼɨ��(DFUģʽ�豸)
	@param event_code MOBILE_DEVICE_PAGECODE_ADVANCE
	@param operate_message �Զ���
	*/
	#define MOBILE_DEVICE_PAGECODE_ADVANCE "0002"

	/*!
	@brief ��������� ��δʶ��
	@param event_code 
	@param operate_message δ����
	*/
	#define MOBILE_DEVICE_PAGECODE_UNIDENTIFY "0003"
/////////////////////////<MOBILE_DEVICE_PAGECODE End>/////////////////////////


/*!
@brief iTunes����չʾҳ
@param page_code ITUNES_BACKUP_PAGECODE
*/
#define ITUNES_BACKUP_PAGECODE "0011"
/////////////////////////<ITUNES_BACKUP_PAGECODE Start>/////////////////////////
	/*!
	@brief ������ָ���ť
	@param event_code ITUNES_BACKUP_PAGECODE_SELECT
	@param operate_message �Զ���
	*/
	#define ITUNES_BACKUP_PAGECODE_SELECT "0001"
	/*!
	@brief ���ѡ������Ŀ¼��ť
	@param event_code ITUNES_BACKUP_PAGECODE_CHOOSE
	@param operate_message �Զ���
	*/
	#define ITUNES_BACKUP_PAGECODE_CHOOSE "0002"
/////////////////////////<ITUNES_BACKUP_PAGECODE End>/////////////////////////


/*!
@brief iTunes�����Զ���ѡ��ҳ��
@param page_code ITUNES_BACKUP_CHOOSE_PAGECODE
*/
#define ITUNES_BACKUP_CHOOSE_PAGECODE "0012"
/////////////////////////<ITUNES_BACKUP_CHOOSE_PAGECODE Start>/////////////////////////
	/*!
	@brief ���ѡ����ť
	@param event_code ITUNES_BACKUP_CHOOSE_PAGECODE_SELECT
	@param operate_message �Զ���
	*/
	#define ITUNES_BACKUP_CHOOSE_PAGECODE_SELECT "0001"

	/*!
	@brief ���ȡ����ť
	@param event_code ITUNES_BACKUP_CHOOSE_PAGECODE_CANCEL
	@param operate_message �Զ���
	*/
	#define ITUNES_BACKUP_CHOOSE_PAGECODE_CANCEL "0002"
/////////////////////////<ITUNES_BACKUP_CHOOSE_PAGECODE End>/////////////////////////

/*!
@brief iCloud�ձ������ѿ�(�ͼ�)
*/
#define MESSAGEBOX_ICLOUD_NODATA_PAGECODE "5001"
#define   MESSAGEBOX_ICLOUD_NODATA_FUNCTION_ACCEPT "0001"   // ȷ��
#define   MESSAGEBOX_ICLOUD_NODATA_FUNCTION_OPENLINK "0002" // ������
#define   MESSAGEBOX_ICLOUD_NODATA_FUNCTION_CLOSED "0003"   // �ر�

/*!
@brief iCloud�ձ������ѿ�(�߼�)
*/
#define MESSAGEBOX_ICLOUD_NODATA_ADVANCE_PAGECODE "5002"
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_ACCEPT   "0001" // ȷ��
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_REJECT   "0002" // ȡ��
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_CLOSED   "0003" // �ر�
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_OPENLINK "0004" // ������

/*!
@brief iCloud9���ѿ�
*/
#define MESSAGEBOX_ICLOUD9_REMINDERS_PAGECODE "5003"
#define   MESSAGEBOX_ICLOUD9_REMINDERS_ACCEPT "0001"        // ȷ��
#define   MESSAGEBOX_ICLOUD9_REMINDERS_CLOSED "0002"        // �ر�
#define   MESSAGEBOX_ICLOUD9_REMINDERS_CONTACTUSLINK "0003" // ��ϵ����

/*!
@brief ���ݴ������ѿ�(LSP)
*/
#define MESSAGEBOX_BACKUP_LSP_PAGECODE "5004"
#define   MESSAGEBOX_BACKUP_LSP_FUNCTION_ACCEPT "0001" // ȷ��
#define   MESSAGEBOX_BACKUP_LSP_FUNCTION_REJECT "0002" // ȡ��

/*!
@brief ɨ�����������ѿ�
*/
#define MESSAGEBOX_SCAN_NODATA_REMINDER_PAGECODE "5006"
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_ACCEPT "0001"         // ȷ��
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_CLOSED "0002"         // �ر�
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_CONTACTUS_LINK "0003" // ��ϵ����
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_KNOWMORE_LINK "0004"  // �˽����

/*!
@brief ɨ��������(NoApp)���ѿ�
*/
#define MESSAGEBOX_SCAN_NOAPP_REMINDER_PAGECODE "5007"
#define   MESSAGEBOX_SCAN_NOAPP_REMINDER_FUNCTION_ACCEPT "0001" // ȷ��
#define   MESSAGEBOX_SCAN_NOAPP_REMINDER_FUNCTION_CLOSED "0002" // �ر�
#define   MESSAGEBOX_SCAN_NOAPP_REMINDER_FUNCTION_LINK   "0003" // ������

/*!
@brief ���ݵȴ����ѿ�
*/
#define MESSAGEBOX_BACKUP_REMIDER_PAGECODE "5008"
#define   MESSAGEBOX_BACKUP_REMIDER_FUNCTION_BTNCLOSE "0001" // �ر�


/*!
@brief ������ѡ��ҳ
@param page_code TOOLS_WIDGET_PAGECODE
*/
#define TOOLS_WIDGET_PAGECODE "0013"
/////////////////////////<TOOLS_WIDGET_PAGECODE Start>/////////////////////////
	/*!
	@brief ��������
	@param event_code TOOLS_WIDGET_PAGECODE_EXPORTALL
	@param operate_message �Զ���
	*/
	#define TOOLS_WIDGET_PAGECODE_EXPORTALL "0001"

	/*!
	@brief ��������
	@param event_code TOOLS_WIDGET_PAGECODE_DATAITEM_OPEN
	@param operate_message ����������
	*/
	#define TOOLS_WIDGET_PAGECODE_DATAITEM_OPEN "0002"

	/*!
	@brief �ر�������
	@param event_code TOOLS_WIDGET_PAGECODE_DATAITEM_CLOSE
	@param operate_message ����������
	*/
	#define TOOLS_WIDGET_PAGECODE_DATAITEM_CLOSE "0003"
	
	/*!
    @brief ����������
    @param event_code TOOLS_WIDGET_PAGECODE_MORE_DATA
    @param operate_message �Զ���
    */
    #define TOOLS_WIDGET_PAGECODE_MORE_DATA "0004"
/////////////////////////<TOOLS_WIDGET_PAGECODE End>/////////////////////////


/*!
@brief �������ҳ
@param page_code DATA_PLUGIN_PAGECODE
*/
#define DATA_PLUGIN_PAGECODE "0014"
/////////////////////////<DATA_PLUGIN_PAGECODE Start>/////////////////////////
	/*!
	@brief ������PC
	@param event_code DATA_PLUGIN_PAGECODE_EXPORT_TOPC
	@param operate_message ����������/�Ƿ�Ϊ΢����ϵ���������΢�������¼
	*/
	#define DATA_PLUGIN_PAGECODE_EXPORT_TOPC "0001"

	/*!
	@brief �������豸
	@param event_code DATA_PLUGIN_PAGECODE_EXPORT_TODEVICE
	@param operate_message ����������
	*/
	#define DATA_PLUGIN_PAGECODE_EXPORT_TODEVICE "0002"

	/*!
	@brief ��ý��Ԥ��
	@param event_code DATA_PLUGIN_PAGECODE_PREVIEW_MEDIA
	@param operate_message ����������|�Ƿ�Ϊ΢�������¼������
	*/
	#define DATA_PLUGIN_PAGECODE_PREVIEW_MEDIA "0003"
	
	/*!
	@brief �������
	@param event_code DATA_PLUGIN_PAGECODE_SEARCH
	@param operate_message ������|�ؼ���
	*/
	#define DATA_PLUGIN_PAGECODE_SEARCH "0004"
/////////////////////////<DATA_PLUGIN_PAGECODE End>/////////////////////////

/*!
@brief �������ע��ҳ
@param page_code REGISTE_PAGECODE
*/
#define REGISTE_PAGECODE "0015"
/////////////////////////<REGISTE_PAGECODE Start>/////////////////////////
	/*!
	@brief �������
	@param event_code REGISTE_PAGECODE_PURCHASE
	@param operate_message δ����
	*/
	#define REGISTE_PAGECODE_PURCHASE "0001"

	/*!
	@brief �������
	@param event_code REGISTE_PAGECODE_TRIAL
	@param operate_message δ����
	*/
	#define REGISTE_PAGECODE_TRIAL "0002"

	/*!
	@brief ���ע��
	@param event_code REGISTE_PAGECODE_REGISTE
	@param operate_message δ����
	*/
	#define REGISTE_PAGECODE_REGISTE "0003"

	/*!
	@brief ����ر� 
	@param event_code REGISTE_PAGECODE_CLOSE
	@param operate_message δ����
	*/
	#define REGISTE_PAGECODE_CLOSE "0004"
/////////////////////////<REGISTE_PAGECODE End>/////////////////////////

/*!
@brief ��������¼��ϵ������
@param page_code MESSSAGE_CLICK_USER_DETAIL
*/
#define MESSSAGE_CLICK_USER_DETAIL "0016"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL Start>/////////////////////////
	/*!
	@brief �����������ϵ������
	@param event_code MESSSAGE_CONTENT_CLICK_USER_DETAIL_TITLE
	@param operate_message δ����
	*/
	#define MESSSAGE_CLICK_USER_DETAIL_TITLE "0001"

	/*!
	@brief ����Ի�����ϵ������
	@param event_code MESSSAGE_CLICK_USER_DETAIL_CONTENT
	@param operate_message δ����
	*/
	#define MESSSAGE_CLICK_USER_DETAIL_CONTENT "0002"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL End>/////////////////////////

/*
@brief ѡ����������
@param page_code MESSSAGE_CLICK_USER_DETAIL
*/
#define CLICK_SORT "0017"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL Start>/////////////////////////
	/*!
	@brief �����������ϵ������
	@param event_code ������|�������
	@param operate_message δ����
	*/
	#define CLICK_SORT_MESSSAGE "0001"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL End>/////////////////////////


/*
@brief ΢����ϵ��ҳ��
@param page_code MESSSAGE_CLICK_USER_DETAIL
*/
#define CLICK_WECHAT_CONTACT "0018"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL Start>/////////////////////////
	/*!
	@brief �������΢����Ϣ
	@param event_code 
	@param operate_message ������Ϣ ����/Ⱥ��
	*/
	#define CLICK_WECHAT_CONTACT_MSG "0001"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL End>/////////////////////////


/*!
@brief ��Ϣ��¼
@param page_code MESSAGE_TITLE
*/
#define MESSAGE_TITLE "0019"
/////////////////////////<MESSAGE_TITLE Start>/////////////////////////
	/*!
	@brief �������
	@param event_code MESSAGE_TITLE_
	@param operate_message δ����
	*/
	#define MESSAGE_TITLE_SORT "0001"
	/*!
	@brief �������
	@param event_code MESSAGE_TITLE_FEEDBACK
	@param operate_message δ����
	*/
	#define MESSAGE_TITLE_FEEDBACK "0002"
/////////////////////////<MAIN_TITLE_BAR End>/////////////////////////


/*!
@brief ������
@param page_code MAIN_TITLE_BAR
*/
#define MAIN_TITLE_BAR "2000"
/////////////////////////<MAIN_TITLE_BAR Start>/////////////////////////
	/*!
	@brief �����¼��ť
	@param event_code MAIN_TITLE_BAR_LOGIN
	@param operate_message δ����
	*/
	#define MAIN_TITLE_BAR_LOGIN "0001"

	/*!
	@brief �������
	@param event_code MAIN_TITLE_BAR_PURCHASE
	@param operate_message δ����
	*/
	#define MAIN_TITLE_BAR_PURCHASE "0002"

	/*!
	@brief  ��¼�󣬵���ǳ�
	@param event_code MAIN_TITLE_BAR_NIKENAME
	@param operate_message δ����
	*/
	#define MAIN_TITLE_BAR_NIKENAME "0003"
/////////////////////////<MAIN_TITLE_BAR End>/////////////////////////

/*!
@brief ��¼ҳ
@param page_code LOGIN_PAGECODE
*/
#define LOGIN_PAGECODE "2001"
/////////////////////////<LOGIN_PAGECODE Start>/////////////////////////
	/*!
	@brief �����¼��ť
	@param event_code LOGIN_PAGECODE_CLICK_LOGIN
	@param operate_message δ����
	*/
	#define LOGIN_PAGECODE_CLICK_LOGIN "0001"

	/*!
	@brief �������ע��
	@param event_code LOGIN_PAGECODE_CLICK_REGISTER
	@param operate_message δ����
	*/
	#define LOGIN_PAGECODE_CLICK_REGISTER "0002"

	/*!
	@brief ����˴�(���û�����)
	@param event_code LOGIN_PAGECODE_CLICK_OLD_USER_REMINDER
	@param operate_message δ����
	*/
	#define LOGIN_PAGECODE_CLICK_OLD_USER_REMINDER "0003"

	/*!
	@brief ����ر� 
	@param event_code LOGIN_PAGECODE_CLOSE
	@param operate_message δ����
	*/
	#define LOGIN_PAGECODE_CLOSE "0004"
	
	/*!
	@brief ���Ի�ȡ΢�Ŷ�ά��
	@param event_code LOGIN_PAGECODE_RETRY_GET_QR
	@param operate_message δ����
	*/
	#define LOGIN_PAGECODE_RETRY_GET_QR "0005"
/////////////////////////<LOGIN_PAGECODE End>/////////////////////////

/*!
@brief ��Ȩ���
@param page_code AUTH_RESULT_PAGE
*/
#define PURCHASE_PAGE "2002"
/////////////////////////<PURCHASE_PAGE Start>/////////////////////////
	/*!
	@brief ���֧��
	@param event_code PURCHASE_PAGE_PAY
	@param operate_message δ����
	*/
	#define PURCHASE_PAGE_PAY "0001"

	/*!
	@brief ����ر�
	@param event_code PURCHASE_PAGE_CLOSE
	@param operate_message δ����
	*/
	#define PURCHASE_PAGE_CLOSE "0002"
/////////////////////////<PURCHASE_PAGE End>/////////////////////////

/*!
@brief ��Ȩ���
@param page_code AUTH_RESULT_PAGE
*/
#define AUTH_RESULT_PAGE "2003"
/////////////////////////<AUTH_RESULT_PAGE Start>/////////////////////////
	/*!
	@brief �����Ȩ
	@param event_code AUTH_RESULT_PAGE_CLICK_AUTH
	@param operate_message δ����
	*/
	#define AUTH_RESULT_PAGE_CLICK_AUTH "0001"

	/*!
	@brief ����ر�
	@param event_code AUTH_RESULT_PAGE_CLICK_CLOSE
	@param operate_message δ����
	*/
	#define AUTH_RESULT_PAGE_CLICK_CLOSE "0002"
/////////////////////////<AUTH_RESULT_PAGE End>/////////////////////////


/*!
@brief ��������
@param page_code USER_CENTER_PAGE
*/
#define USER_CENTER_PAGE "2004"
/////////////////////////<USER_CENTER_PAGE Start>/////////////////////////
	/*!
	@brief �����ע����
	@param event_code USER_CENTER_PAGE_BIND_CODE
	@param operate_message δ����
	*/
	#define USER_CENTER_PAGE_BIND_CODE "0001"

	/*!
	@brief ���������Ȩ
	@param event_code USER_CENTER_PAGE_PURCHASE
	@param operate_message δ����
	*/
	#define USER_CENTER_PAGE_PURCHASE "0002"
	
	/*!
	@brief �������Ȩ
	@param event_code USER_CENTER_PAGE_BIND_AUTH
	@param operate_message δ����
	*/
	#define USER_CENTER_PAGE_BIND_AUTH "0003"
	
	/*!
	@brief ����ر�
	@param event_code USER_CENTER_PAGE_CLOSE
	@param operate_message δ����
	*/
	#define USER_CENTER_PAGE_CLOSE "0004"
/////////////////////////<USER_CENTER_PAGE End>/////////////////////////



/*!
@brief ����֤��
@param page_code BIND_REGISTER_CODE_PAGE
*/
#define BIND_CHECK_CODE_PAGE "2005"
/////////////////////////<BIND_REGISTER_CODE_PAGE Start>/////////////////////////
	/*!
	@brief ���������֤
	@param event_code BIND_CHECK_CODE_PAGE_CHECK
	@param operate_message δ����
	*/
	#define BIND_CHECK_CODE_PAGE_CHECK "0001"

	/*!
	@brief �ر�
	@param event_code BIND_CHECK_CODE_PAGE_WINDOW
	@param operate_message δ����
	*/
	#define BIND_CHECK_CODE_PAGE_CLOSE "0002"
/////////////////////////<BIND_REGISTER_CODE_PAGE End>/////////////////////////


/*!
@brief �������Ȩҳ
@param page_code BIND_REGISTER_CODE_PAGE
*/
#define BIND_AUTH_PAGE "2006"
/////////////////////////<BIND_REGISTER_CODE_PAGE Start>/////////////////////////
	/*!
	@brief �������
	@param event_code BIND_AUTH_PAGE_TRY
	@param operate_message δ����
	*/
	#define BIND_AUTH_PAGE_TRY "0001"

	/*!
	@brief ���������ʹ��
	@param event_code BIND_AUTH_PAGE_USER
	@param operate_message δ����
	*/
	#define BIND_AUTH_PAGE_USER "0002"
	
	/*!
	@brief ����ر�
	@param event_code BIND_AUTH_PAGE_CLOSE
	@param operate_message δ����
	*/
	#define BIND_AUTH_PAGE_CLOSE "0003"
	
	/*!
	@brief �����
	@param event_code BIND_AUTH_PAGE_CLICK_BIND
	@param operate_message δ����
	*/
	#define BIND_AUTH_PAGE_CLICK_BIND "0004"
/////////////////////////<BIND_REGISTER_CODE_PAGE End>/////////////////////////


/*!
@brief �������Ȩҳ
@param page_code OLD_USER_REMINDER_PAGE
*/
#define OLD_USER_REMINDER_PAGE "2007"
/////////////////////////<OLD_USER_REMINDER_PAGE Start>/////////////////////////
	/*!
	@brief ��˵�¼���
	@param event_code OLD_USER_REMINDER_PAGE_CLICK_LOGIN
	@param operate_message δ����
	*/
	#define OLD_USER_REMINDER_PAGE_CLICK_LOGIN "0001"

	/*!
	@brief ����ر�
	@param event_code OLD_USER_REMINDER_PAGE_CLOSE
	@param operate_message δ����
	*/
	#define OLD_USER_REMINDER_PAGE_CLOSE "0002"
/////////////////////////<OLD_USER_REMINDER_PAGE End>/////////////////////////



/*!
@brief �������򴰿�λ��
@param page_code PURCHASE_SOURCE
*/
#define PURCHASE_SOURCE "2008"
/////////////////////////<PURCHASE_SOURCE Start>/////////////////////////
	/*!
	@brief �������������޵�ԭ�򵯳�����
	@param event_code PURCHASE_SHOW_MENU
	@param operate_message δ����
	*/
	#define PURCHASE_SOURCE_CLICK_DATA_PLUGIN "0001"

	/*!
	@brief �������
	@param event_code PURCHASE_SOURCE_PLUGIN_EXPORT
	@param operate_message δ����
	*/
	#define PURCHASE_SOURCE_PLUGIN_EXPORT "0002"
/////////////////////////<PURCHASE_SOURCE End>/////////////////////////


/*!
@brief �������򴰿�λ��
@param page_code PURCHASE_SOURCE
*/
#define START_TRAIL_WINDOW "2009"
/////////////////////////<PURCHASE_SOURCE Start>/////////////////////////
	/*!
	@brief �����¼����
	@param event_code START_TRAIL_WINDOW_PURCHASE
	@param operate_message δ����
	*/
	#define START_TRAIL_WINDOW_PURCHASE "0001"

	/*!
	@brief �����¼����
	@param event_code START_TRAIL_WINDOW_TRAIL
	@param operate_message δ����
	*/
	#define START_TRAIL_WINDOW_TRAIL "0002"
	
	/*!
	@brief ����ر�
	@param event_code START_TRAIL_WINDOW_CLOSE
	@param operate_message δ����
	*/
	#define START_TRAIL_WINDOW_CLOSE "0003"
/////////////////////////<PURCHASE_SOURCE End>/////////////////////////

#endif
