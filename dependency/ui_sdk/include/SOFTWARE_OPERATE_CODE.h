#ifndef SOFTWARE_OPERATE_TYPE_H__
#define SOFTWARE_OPERATE_TYPE_H__

/*!
@brief 购买链接
@param page_code OPEN_PURCHASE
*/
#define OPEN_PURCHASE "0004"
/////////////////////////<OPEN_PURCHASE Start>/////////////////////////
	/*!
	@brief 点击菜单栏购买链接
	@param event_code OPEN_PURCHASE_MENU
	@param operate_message 自定义
	*/
	#define OPEN_PURCHASE_MENU "0001"

	/*!
	@brief 点击注册提醒框购买链接
	@param event_code OPEN_PURCHASE_MENU
	@param operate_message 自定义
	*/
	#define OPEN_PURCHASE_REGISTERWIDGET "0002"

	/*!
	@brief 点击据项预览页面Title栏注册提醒链接
	@param event_code OPEN_PURCHASE_MENU
	@param operate_message 数据项掩码
	*/
	#define OPEN_PURCHASE_DATAITEM_TITLE "0003"
/////////////////////////<OPEN_PURCHASE End>/////////////////////////


/*!
@brief iCloud登录页面
@param page_code ICLOUD_LOGIN_PAGECODE
*/
#define ICLOUD_LOGIN_PAGECODE "0005"
/////////////////////////<ICLOUD_LOGIN_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击开始登录按钮
	@param event_code ICLOUD_LOGIN_PAGECODE_LOGIN
	@param operate_message 自定义
	*/
	#define ICLOUD_LOGIN_PAGECODE_LOGIN "0001"
/////////////////////////<ICLOUD_LOGIN_PAGECODE End>/////////////////////////


/*!
@brief iCloud账户展示页面
@param page_code ICLOUD_ACCOUNT_PAGECODE
*/
#define ICLOUD_ACCOUNT_PAGECODE "0006"
/////////////////////////<ICLOUD_ACCOUNT_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击下载按钮
	@param event_code ICLOUD_ACCOUNT_PAGECODE_DOWNLOAD
	@param operate_message 自定义
	*/
	#define ICLOUD_ACCOUNT_PAGECODE_DOWNLOAD "0001"

	/*!
	@brief 点击删除按钮
	@param event_code ICLOUD_ACCOUNT_PAGECODE_DELETE
	@param operate_message 自定义
	*/
	#define ICLOUD_ACCOUNT_PAGECODE_DELETE "0002"

	/*!
	@brief 点击扫描按钮
	@param event_code ICLOUD_ACCOUNT_PAGECODE_SCAN
	@param operate_message 自定义
	*/
	#define ICLOUD_ACCOUNT_PAGECODE_SCAN "0003"
/////////////////////////<ICLOUD_ACCOUNT_PAGECODE End>/////////////////////////


/*!
@brief 三大模式切换
@param page_code SWITCH_SCAN_MODE
*/
#define SWITCH_SCAN_MODE "0007"
/////////////////////////<SWITCH_SCAN_MODE Start>/////////////////////////
	/*!
	@brief 点击设备模式
	@param event_code SWITCH_SCAN_MODE_MOBILE
	@param operate_message 自定义
	*/
	#define SWITCH_SCAN_MODE_MOBILE "0001"

	/*!
	@brief 点击iTunes备份模式
	@param event_code SWITCH_SCAN_MODE_ITUNES
	@param operate_message 自定义
	*/
	#define SWITCH_SCAN_MODE_ITUNES "0002"

	/*!
	@brief 点击iCloud备份模式
	@param event_code SWITCH_SCAN_MODE_ICLOUD
	@param operate_message 自定义
	*/
	#define SWITCH_SCAN_MODE_ICLOUD "0003"
/////////////////////////<SWITCH_SCAN_MODE End>/////////////////////////


/*!
@brief .NetFramework自动安装页
@param page_code NETFRAMEWORK_INSTALL_PAGECODE
*/
#define NETFRAMEWORK_INSTALL_PAGECODE "0008"
/////////////////////////<NETFRAMEWORK_INSTALL_PAGECODE End>/////////////////////////
	/*!
	@brief 点击取消按钮
	@param event_code NETFRAMEWORK_INSTALL_PAGECODE_CANCEL
	@param operate_message 自定义
	*/
	#define NETFRAMEWORK_INSTALL_PAGECODE_CANCEL "0001"

	/*!
	@brief 点击安装按钮
	@param event_code NETFRAMEWORK_INSTALL_PAGECODE_INSTALL
	@param operate_message 自定义
	*/
	#define NETFRAMEWORK_INSTALL_PAGECODE_INSTALL "0002"

	/*!
	@brief 点击重试按钮
	@param event_code NETFRAMEWORK_INSTALL_PAGECODE_RETRY
	@param operate_message 自定义
	*/
	#define NETFRAMEWORK_INSTALL_PAGECODE_RETRY "0003"
/////////////////////////<NETFRAMEWORK_INSTALL_PAGECODE End>/////////////////////////


/*!
@brief iCloud下载数据项选择页
@param page_code ICLOUD_DOWNLOAD_CONFIG_PAGECODE
*/
#define ICLOUD_DOWNLOAD_CONFIG_PAGECODE "0009"
/////////////////////////<ICLOUD_DOWNLOAD_CONFIG_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击取消按钮
	@param event_code ICLOUD_DOWNLOAD_CONFIG_PAGECODE_CANCEL
	@param operate_message 自定义
	*/
	#define ICLOUD_DOWNLOAD_CONFIG_PAGECODE_CANCEL "0001"

	/*!
	@brief 点击选择按钮
	@param event_code ICLOUD_DOWNLOAD_CONFIG_PAGECODE_DOWNLOAD
	@param operate_message 已选择数据项的功能掩码
	*/
	#define ICLOUD_DOWNLOAD_CONFIG_PAGECODE_DOWNLOAD "0002"
/////////////////////////<ICLOUD_DOWNLOAD_CONFIG_PAGECODE End>/////////////////////////


/*!
@brief 设备展示页
@param page_code MOBILE_DEVICE_PAGECODE
*/
#define MOBILE_DEVICE_PAGECODE "0010"
/////////////////////////<MOBILE_DEVICE_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击开始扫描(常规设备)
	@param event_code MOBILE_DEVICE_PAGECODE_NORMAL
	@param operate_message 自定义
	*/
	#define MOBILE_DEVICE_PAGECODE_NORMAL "0001"

	/*!
	@brief 点击开始扫描(DFU模式设备)
	@param event_code MOBILE_DEVICE_PAGECODE_ADVANCE
	@param operate_message 自定义
	*/
	#define MOBILE_DEVICE_PAGECODE_ADVANCE "0002"

	/*!
	@brief 点击已连接 但未识别
	@param event_code 
	@param operate_message 未定义
	*/
	#define MOBILE_DEVICE_PAGECODE_UNIDENTIFY "0003"
/////////////////////////<MOBILE_DEVICE_PAGECODE End>/////////////////////////


/*!
@brief iTunes备份展示页
@param page_code ITUNES_BACKUP_PAGECODE
*/
#define ITUNES_BACKUP_PAGECODE "0011"
/////////////////////////<ITUNES_BACKUP_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击表格恢复按钮
	@param event_code ITUNES_BACKUP_PAGECODE_SELECT
	@param operate_message 自定义
	*/
	#define ITUNES_BACKUP_PAGECODE_SELECT "0001"
	/*!
	@brief 点击选择其他目录按钮
	@param event_code ITUNES_BACKUP_PAGECODE_CHOOSE
	@param operate_message 自定义
	*/
	#define ITUNES_BACKUP_PAGECODE_CHOOSE "0002"
/////////////////////////<ITUNES_BACKUP_PAGECODE End>/////////////////////////


/*!
@brief iTunes备份自定义选择页面
@param page_code ITUNES_BACKUP_CHOOSE_PAGECODE
*/
#define ITUNES_BACKUP_CHOOSE_PAGECODE "0012"
/////////////////////////<ITUNES_BACKUP_CHOOSE_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击选定按钮
	@param event_code ITUNES_BACKUP_CHOOSE_PAGECODE_SELECT
	@param operate_message 自定义
	*/
	#define ITUNES_BACKUP_CHOOSE_PAGECODE_SELECT "0001"

	/*!
	@brief 点击取消按钮
	@param event_code ITUNES_BACKUP_CHOOSE_PAGECODE_CANCEL
	@param operate_message 自定义
	*/
	#define ITUNES_BACKUP_CHOOSE_PAGECODE_CANCEL "0002"
/////////////////////////<ITUNES_BACKUP_CHOOSE_PAGECODE End>/////////////////////////

/*!
@brief iCloud空备份提醒框(低级)
*/
#define MESSAGEBOX_ICLOUD_NODATA_PAGECODE "5001"
#define   MESSAGEBOX_ICLOUD_NODATA_FUNCTION_ACCEPT "0001"   // 确定
#define   MESSAGEBOX_ICLOUD_NODATA_FUNCTION_OPENLINK "0002" // 打开链接
#define   MESSAGEBOX_ICLOUD_NODATA_FUNCTION_CLOSED "0003"   // 关闭

/*!
@brief iCloud空备份提醒框(高级)
*/
#define MESSAGEBOX_ICLOUD_NODATA_ADVANCE_PAGECODE "5002"
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_ACCEPT   "0001" // 确定
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_REJECT   "0002" // 取消
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_CLOSED   "0003" // 关闭
#define   MESSAGEBOX_ICLOUD_NODATA_ADVANCE_FUNCTION_OPENLINK "0004" // 打开链接

/*!
@brief iCloud9提醒框
*/
#define MESSAGEBOX_ICLOUD9_REMINDERS_PAGECODE "5003"
#define   MESSAGEBOX_ICLOUD9_REMINDERS_ACCEPT "0001"        // 确定
#define   MESSAGEBOX_ICLOUD9_REMINDERS_CLOSED "0002"        // 关闭
#define   MESSAGEBOX_ICLOUD9_REMINDERS_CONTACTUSLINK "0003" // 联系我们

/*!
@brief 备份错误提醒框(LSP)
*/
#define MESSAGEBOX_BACKUP_LSP_PAGECODE "5004"
#define   MESSAGEBOX_BACKUP_LSP_FUNCTION_ACCEPT "0001" // 确定
#define   MESSAGEBOX_BACKUP_LSP_FUNCTION_REJECT "0002" // 取消

/*!
@brief 扫描无数据提醒框
*/
#define MESSAGEBOX_SCAN_NODATA_REMINDER_PAGECODE "5006"
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_ACCEPT "0001"         // 确定
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_CLOSED "0002"         // 关闭
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_CONTACTUS_LINK "0003" // 联系我们
#define   MESSAGEBOX_SCAN_NODATA_REMINDER_FUNCTION_KNOWMORE_LINK "0004"  // 了解更多

/*!
@brief 扫描无数据(NoApp)提醒框
*/
#define MESSAGEBOX_SCAN_NOAPP_REMINDER_PAGECODE "5007"
#define   MESSAGEBOX_SCAN_NOAPP_REMINDER_FUNCTION_ACCEPT "0001" // 确定
#define   MESSAGEBOX_SCAN_NOAPP_REMINDER_FUNCTION_CLOSED "0002" // 关闭
#define   MESSAGEBOX_SCAN_NOAPP_REMINDER_FUNCTION_LINK   "0003" // 打开链接

/*!
@brief 备份等待提醒框
*/
#define MESSAGEBOX_BACKUP_REMIDER_PAGECODE "5008"
#define   MESSAGEBOX_BACKUP_REMIDER_FUNCTION_BTNCLOSE "0001" // 关闭


/*!
@brief 数据项选择页
@param page_code TOOLS_WIDGET_PAGECODE
*/
#define TOOLS_WIDGET_PAGECODE "0013"
/////////////////////////<TOOLS_WIDGET_PAGECODE Start>/////////////////////////
	/*!
	@brief 导出所有
	@param event_code TOOLS_WIDGET_PAGECODE_EXPORTALL
	@param operate_message 自定义
	*/
	#define TOOLS_WIDGET_PAGECODE_EXPORTALL "0001"

	/*!
	@brief 打开数据项
	@param event_code TOOLS_WIDGET_PAGECODE_DATAITEM_OPEN
	@param operate_message 数据项掩码
	*/
	#define TOOLS_WIDGET_PAGECODE_DATAITEM_OPEN "0002"

	/*!
	@brief 关闭数据项
	@param event_code TOOLS_WIDGET_PAGECODE_DATAITEM_CLOSE
	@param operate_message 数据项掩码
	*/
	#define TOOLS_WIDGET_PAGECODE_DATAITEM_CLOSE "0003"
	
	/*!
    @brief 更多数据项
    @param event_code TOOLS_WIDGET_PAGECODE_MORE_DATA
    @param operate_message 自定义
    */
    #define TOOLS_WIDGET_PAGECODE_MORE_DATA "0004"
/////////////////////////<TOOLS_WIDGET_PAGECODE End>/////////////////////////


/*!
@brief 数据项导出页
@param page_code DATA_PLUGIN_PAGECODE
*/
#define DATA_PLUGIN_PAGECODE "0014"
/////////////////////////<DATA_PLUGIN_PAGECODE Start>/////////////////////////
	/*!
	@brief 导出到PC
	@param event_code DATA_PLUGIN_PAGECODE_EXPORT_TOPC
	@param operate_message 数据项掩码/是否为微信联系人数据项导出微信聊天记录
	*/
	#define DATA_PLUGIN_PAGECODE_EXPORT_TOPC "0001"

	/*!
	@brief 导出到设备
	@param event_code DATA_PLUGIN_PAGECODE_EXPORT_TODEVICE
	@param operate_message 数据项掩码
	*/
	#define DATA_PLUGIN_PAGECODE_EXPORT_TODEVICE "0002"

	/*!
	@brief 多媒体预览
	@param event_code DATA_PLUGIN_PAGECODE_PREVIEW_MEDIA
	@param operate_message 数据项掩码|是否为微信聊天记录弹出框
	*/
	#define DATA_PLUGIN_PAGECODE_PREVIEW_MEDIA "0003"
	
	/*!
	@brief 点击搜索
	@param event_code DATA_PLUGIN_PAGECODE_SEARCH
	@param operate_message 数据项|关键词
	*/
	#define DATA_PLUGIN_PAGECODE_SEARCH "0004"
/////////////////////////<DATA_PLUGIN_PAGECODE End>/////////////////////////

/*!
@brief 软件启动注册页
@param page_code REGISTE_PAGECODE
*/
#define REGISTE_PAGECODE "0015"
/////////////////////////<REGISTE_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击购买
	@param event_code REGISTE_PAGECODE_PURCHASE
	@param operate_message 未定义
	*/
	#define REGISTE_PAGECODE_PURCHASE "0001"

	/*!
	@brief 点击试用
	@param event_code REGISTE_PAGECODE_TRIAL
	@param operate_message 未定义
	*/
	#define REGISTE_PAGECODE_TRIAL "0002"

	/*!
	@brief 点击注册
	@param event_code REGISTE_PAGECODE_REGISTE
	@param operate_message 未定义
	*/
	#define REGISTE_PAGECODE_REGISTE "0003"

	/*!
	@brief 点击关闭 
	@param event_code REGISTE_PAGECODE_CLOSE
	@param operate_message 未定义
	*/
	#define REGISTE_PAGECODE_CLOSE "0004"
/////////////////////////<REGISTE_PAGECODE End>/////////////////////////

/*!
@brief 点击聊天记录联系人名称
@param page_code MESSSAGE_CLICK_USER_DETAIL
*/
#define MESSSAGE_CLICK_USER_DETAIL "0016"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL Start>/////////////////////////
	/*!
	@brief 点击标题栏联系人名称
	@param event_code MESSSAGE_CONTENT_CLICK_USER_DETAIL_TITLE
	@param operate_message 未定义
	*/
	#define MESSSAGE_CLICK_USER_DETAIL_TITLE "0001"

	/*!
	@brief 点击对话框联系人名称
	@param event_code MESSSAGE_CLICK_USER_DETAIL_CONTENT
	@param operate_message 未定义
	*/
	#define MESSSAGE_CLICK_USER_DETAIL_CONTENT "0002"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL End>/////////////////////////

/*
@brief 选择排序类型
@param page_code MESSSAGE_CLICK_USER_DETAIL
*/
#define CLICK_SORT "0017"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL Start>/////////////////////////
	/*!
	@brief 点击标题栏联系人名称
	@param event_code 数据项|排序类别
	@param operate_message 未定义
	*/
	#define CLICK_SORT_MESSSAGE "0001"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL End>/////////////////////////


/*
@brief 微信联系人页面
@param page_code MESSSAGE_CLICK_USER_DETAIL
*/
#define CLICK_WECHAT_CONTACT "0018"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL Start>/////////////////////////
	/*!
	@brief 点击关联微信消息
	@param event_code 
	@param operate_message 分组信息 好友/群聊
	*/
	#define CLICK_WECHAT_CONTACT_MSG "0001"
/////////////////////////<MESSSAGE_CLICK_USER_DETAIL End>/////////////////////////


/*!
@brief 消息记录
@param page_code MESSAGE_TITLE
*/
#define MESSAGE_TITLE "0019"
/////////////////////////<MESSAGE_TITLE Start>/////////////////////////
	/*!
	@brief 点击排序
	@param event_code MESSAGE_TITLE_
	@param operate_message 未定义
	*/
	#define MESSAGE_TITLE_SORT "0001"
	/*!
	@brief 点击反馈
	@param event_code MESSAGE_TITLE_FEEDBACK
	@param operate_message 未定义
	*/
	#define MESSAGE_TITLE_FEEDBACK "0002"
/////////////////////////<MAIN_TITLE_BAR End>/////////////////////////


/*!
@brief 标题栏
@param page_code MAIN_TITLE_BAR
*/
#define MAIN_TITLE_BAR "2000"
/////////////////////////<MAIN_TITLE_BAR Start>/////////////////////////
	/*!
	@brief 点击登录按钮
	@param event_code MAIN_TITLE_BAR_LOGIN
	@param operate_message 未定义
	*/
	#define MAIN_TITLE_BAR_LOGIN "0001"

	/*!
	@brief 点击购买
	@param event_code MAIN_TITLE_BAR_PURCHASE
	@param operate_message 未定义
	*/
	#define MAIN_TITLE_BAR_PURCHASE "0002"

	/*!
	@brief  登录后，点击昵称
	@param event_code MAIN_TITLE_BAR_NIKENAME
	@param operate_message 未定义
	*/
	#define MAIN_TITLE_BAR_NIKENAME "0003"
/////////////////////////<MAIN_TITLE_BAR End>/////////////////////////

/*!
@brief 登录页
@param page_code LOGIN_PAGECODE
*/
#define LOGIN_PAGECODE "2001"
/////////////////////////<LOGIN_PAGECODE Start>/////////////////////////
	/*!
	@brief 点击登录按钮
	@param event_code LOGIN_PAGECODE_CLICK_LOGIN
	@param operate_message 未定义
	*/
	#define LOGIN_PAGECODE_CLICK_LOGIN "0001"

	/*!
	@brief 点击立即注册
	@param event_code LOGIN_PAGECODE_CLICK_REGISTER
	@param operate_message 未定义
	*/
	#define LOGIN_PAGECODE_CLICK_REGISTER "0002"

	/*!
	@brief 点击此处(老用户提醒)
	@param event_code LOGIN_PAGECODE_CLICK_OLD_USER_REMINDER
	@param operate_message 未定义
	*/
	#define LOGIN_PAGECODE_CLICK_OLD_USER_REMINDER "0003"

	/*!
	@brief 点击关闭 
	@param event_code LOGIN_PAGECODE_CLOSE
	@param operate_message 未定义
	*/
	#define LOGIN_PAGECODE_CLOSE "0004"
	
	/*!
	@brief 重试获取微信二维码
	@param event_code LOGIN_PAGECODE_RETRY_GET_QR
	@param operate_message 未定义
	*/
	#define LOGIN_PAGECODE_RETRY_GET_QR "0005"
/////////////////////////<LOGIN_PAGECODE End>/////////////////////////

/*!
@brief 授权结果
@param page_code AUTH_RESULT_PAGE
*/
#define PURCHASE_PAGE "2002"
/////////////////////////<PURCHASE_PAGE Start>/////////////////////////
	/*!
	@brief 点击支付
	@param event_code PURCHASE_PAGE_PAY
	@param operate_message 未定义
	*/
	#define PURCHASE_PAGE_PAY "0001"

	/*!
	@brief 点击关闭
	@param event_code PURCHASE_PAGE_CLOSE
	@param operate_message 未定义
	*/
	#define PURCHASE_PAGE_CLOSE "0002"
/////////////////////////<PURCHASE_PAGE End>/////////////////////////

/*!
@brief 授权结果
@param page_code AUTH_RESULT_PAGE
*/
#define AUTH_RESULT_PAGE "2003"
/////////////////////////<AUTH_RESULT_PAGE Start>/////////////////////////
	/*!
	@brief 点击授权
	@param event_code AUTH_RESULT_PAGE_CLICK_AUTH
	@param operate_message 未定义
	*/
	#define AUTH_RESULT_PAGE_CLICK_AUTH "0001"

	/*!
	@brief 点击关闭
	@param event_code AUTH_RESULT_PAGE_CLICK_CLOSE
	@param operate_message 未定义
	*/
	#define AUTH_RESULT_PAGE_CLICK_CLOSE "0002"
/////////////////////////<AUTH_RESULT_PAGE End>/////////////////////////


/*!
@brief 个人中心
@param page_code USER_CENTER_PAGE
*/
#define USER_CENTER_PAGE "2004"
/////////////////////////<USER_CENTER_PAGE Start>/////////////////////////
	/*!
	@brief 点击绑定注册码
	@param event_code USER_CENTER_PAGE_BIND_CODE
	@param operate_message 未定义
	*/
	#define USER_CENTER_PAGE_BIND_CODE "0001"

	/*!
	@brief 点击购买授权
	@param event_code USER_CENTER_PAGE_PURCHASE
	@param operate_message 未定义
	*/
	#define USER_CENTER_PAGE_PURCHASE "0002"
	
	/*!
	@brief 点击绑定授权
	@param event_code USER_CENTER_PAGE_BIND_AUTH
	@param operate_message 未定义
	*/
	#define USER_CENTER_PAGE_BIND_AUTH "0003"
	
	/*!
	@brief 点击关闭
	@param event_code USER_CENTER_PAGE_CLOSE
	@param operate_message 未定义
	*/
	#define USER_CENTER_PAGE_CLOSE "0004"
/////////////////////////<USER_CENTER_PAGE End>/////////////////////////



/*!
@brief 绑定验证码
@param page_code BIND_REGISTER_CODE_PAGE
*/
#define BIND_CHECK_CODE_PAGE "2005"
/////////////////////////<BIND_REGISTER_CODE_PAGE Start>/////////////////////////
	/*!
	@brief 点击立即验证
	@param event_code BIND_CHECK_CODE_PAGE_CHECK
	@param operate_message 未定义
	*/
	#define BIND_CHECK_CODE_PAGE_CHECK "0001"

	/*!
	@brief 关闭
	@param event_code BIND_CHECK_CODE_PAGE_WINDOW
	@param operate_message 未定义
	*/
	#define BIND_CHECK_CODE_PAGE_CLOSE "0002"
/////////////////////////<BIND_REGISTER_CODE_PAGE End>/////////////////////////


/*!
@brief 绑定软件授权页
@param page_code BIND_REGISTER_CODE_PAGE
*/
#define BIND_AUTH_PAGE "2006"
/////////////////////////<BIND_REGISTER_CODE_PAGE Start>/////////////////////////
	/*!
	@brief 点击重试
	@param event_code BIND_AUTH_PAGE_TRY
	@param operate_message 未定义
	*/
	#define BIND_AUTH_PAGE_TRY "0001"

	/*!
	@brief 点击订立即使用
	@param event_code BIND_AUTH_PAGE_USER
	@param operate_message 未定义
	*/
	#define BIND_AUTH_PAGE_USER "0002"
	
	/*!
	@brief 点击关闭
	@param event_code BIND_AUTH_PAGE_CLOSE
	@param operate_message 未定义
	*/
	#define BIND_AUTH_PAGE_CLOSE "0003"
	
	/*!
	@brief 点击绑定
	@param event_code BIND_AUTH_PAGE_CLICK_BIND
	@param operate_message 未定义
	*/
	#define BIND_AUTH_PAGE_CLICK_BIND "0004"
/////////////////////////<BIND_REGISTER_CODE_PAGE End>/////////////////////////


/*!
@brief 绑定软件授权页
@param page_code OLD_USER_REMINDER_PAGE
*/
#define OLD_USER_REMINDER_PAGE "2007"
/////////////////////////<OLD_USER_REMINDER_PAGE Start>/////////////////////////
	/*!
	@brief 点此登录后绑定
	@param event_code OLD_USER_REMINDER_PAGE_CLICK_LOGIN
	@param operate_message 未定义
	*/
	#define OLD_USER_REMINDER_PAGE_CLICK_LOGIN "0001"

	/*!
	@brief 点击关闭
	@param event_code OLD_USER_REMINDER_PAGE_CLOSE
	@param operate_message 未定义
	*/
	#define OLD_USER_REMINDER_PAGE_CLOSE "0002"
/////////////////////////<OLD_USER_REMINDER_PAGE End>/////////////////////////



/*!
@brief 弹出购买窗口位置
@param page_code PURCHASE_SOURCE
*/
#define PURCHASE_SOURCE "2008"
/////////////////////////<PURCHASE_SOURCE Start>/////////////////////////
	/*!
	@brief 点击数据项后因超限等原因弹出购买
	@param event_code PURCHASE_SHOW_MENU
	@param operate_message 未定义
	*/
	#define PURCHASE_SOURCE_CLICK_DATA_PLUGIN "0001"

	/*!
	@brief 数据项导出
	@param event_code PURCHASE_SOURCE_PLUGIN_EXPORT
	@param operate_message 未定义
	*/
	#define PURCHASE_SOURCE_PLUGIN_EXPORT "0002"
/////////////////////////<PURCHASE_SOURCE End>/////////////////////////


/*!
@brief 弹出购买窗口位置
@param page_code PURCHASE_SOURCE
*/
#define START_TRAIL_WINDOW "2009"
/////////////////////////<PURCHASE_SOURCE Start>/////////////////////////
	/*!
	@brief 点击登录购买
	@param event_code START_TRAIL_WINDOW_PURCHASE
	@param operate_message 未定义
	*/
	#define START_TRAIL_WINDOW_PURCHASE "0001"

	/*!
	@brief 点击登录试用
	@param event_code START_TRAIL_WINDOW_TRAIL
	@param operate_message 未定义
	*/
	#define START_TRAIL_WINDOW_TRAIL "0002"
	
	/*!
	@brief 点击关闭
	@param event_code START_TRAIL_WINDOW_CLOSE
	@param operate_message 未定义
	*/
	#define START_TRAIL_WINDOW_CLOSE "0003"
/////////////////////////<PURCHASE_SOURCE End>/////////////////////////

#endif
