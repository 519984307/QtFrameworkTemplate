#ifndef SOFTWARE_ERROR_CODE_H__
#define SOFTWARE_ERROR_CODE_H__

/*!
@brief 错误等级定义
*/
#define ERROR_CODE_LEVEL_FATAL   1
#define ERROR_CODE_LEVEL_ERROR   2
#define ERROR_CODE_LEVEL_WARNING 3
#define ERROR_CODE_LEVEL_INFO    4
#define ERROR_CODE_LEVEL_DEBUG   5
#define ERROR_CODE_LEVEL_PROFILE 6

/*!
@brief 软件崩溃
@param category_code SOFTWARE_CREASH
*/
#define SOFTWARE_CREASH "0001"
//////////////////<SOFTWARE_CREASH Start>//////////////////
/*!
@brief 崩溃
@param level fatal
@param log_code SOFTWARE_CREASH_REPORT
@param log_data 自定义
@param extend_data 自定义
@param files *.zip
*/
#define SOFTWARE_CREASH_REPORT "0001"
//////////////////<SOFTWARE_CREASH End>//////////////////


/*!
@brief 软件状态
@param category_code SOFTWARE_STATE
*/
#define SOFTWARE_STATE "0002"
//////////////////<SOFTWARE_STATE Start>//////////////////
	/*!
	@brief 打开
	@param level info
	@param log_code SOFTWARE_STATE_OPEN
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_STATE_OPEN "0001"

	/*!
	@brief 关闭
	@param level info
	@param log_code SOFTWARE_STATE_CLOSE
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_STATE_CLOSE "0002"
//////////////////<SOFTWARE_STATE End>//////////////////


/*!
@brief iCloud相关的操作码定义
@param category_code SOFTWARE_ICLOUD
*/
#define SOFTWARE_ICLOUD "0025"
//////////////////<SOFTWARE_ICLOUD Start>//////////////////
	/*!
	@brief 登录失败(密码错误)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_PASSWORD
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_PASSWORD "0001"

	/*!
	@brief 登录失败(网络错误)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_NONETWORK
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files *.zip
	*/
	#define   SOFTWARE_ICLOUD_LOGIN_ERROR_NONETWORK "0002"

	/*!
	@brief 登录失败(网络超时)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_TIMEOUT
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_TIMEOUT "0003"

	/*!
	@brief 登录失败(用户取消)
	@param level warning
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_CANCEL
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_CANCEL "0004"

	/*!
	@brief 登录失败(两部验证)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_STEP
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_STEP "0005"

	/*!
	@brief 登录失败(未知错误)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_ERROR_UNKNOWN
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_ERROR_UNKNOWN "0006"

	/*!
	@brief 登录成功
	@param level info
	@param log_code SOFTWARE_ICLOUD_LOGIN_SUCCESS
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_LOGIN_SUCCESS "0007"

	/*!
	@brief 下载失败(备份无文件)
	@param level error
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_ERROR_NOFILE
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_ERROR_NOFILE "0008"

	/*!
	@brief 下载失败(未知错误)
	@param level error
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_ERROR_UNKNOWN
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_ERROR_UNKNOWN "0009"

	/*!
	@brief 下载成功
	@param level info
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_SUCCESS
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_SUCCESS "0010"

	/*!
	@brief 用户取消下载
	@param level warning
	@param log_code SOFTWARE_ICLOUD_DOWNLOAD_CANCEL
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_DOWNLOAD_CANCEL "0013"

	/*!
	@brief 账户备份信息
	@param level info
	@param log_code SOFTWARE_ICLOUD_ACCOUNT_INFO
	@param log_data md5(iCloud account)
	@param extend_data json: {[serial, size, version, snapshot id], [serial, size, version, snapshot id]...}
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_ACCOUNT_INFO "0011"

	/*!
	@brief 开始下载
	@param level info
	@param log_code SOFTWARE_ICLOUD_START_DOWNLOAD
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_START_DOWNLOAD "0012"

	/*!
	@brief 登录失败(账户未开启)
	@param level error
	@param log_code SOFTWARE_ICLOUD_LOGIN_NOT_USE
	@param log_data md5(iCloud account)
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_LOGIN_NOT_USE "0014"

	/*!
	@brief 开始扫描
	@param level info
	@param log_code SOFTWARE_ICLOUD_START_SCAN
	@param log_data 填写mobile-icloud
	@param extend_data 设备序列号/UDID 优先选择设备序列号，如设备序列号不存在则选择设备UDID，如果都不存在则不填写
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_START_SCAN "0015"

	/*!
	@brief ICloud下载完成后创建备份成功
	@param level info
	@param log_code SOFTWARE_ICLOUD_BACKUP_CHOOSE_SUCCESS
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files 未使用
	*/
	#define SOFTWARE_ICLOUD_BACKUP_CHOOSE_SUCCESS "0016"

	/*!
	@brief ICloud下载完成后创建备份失败
	@param level error
	@param log_code SOFTWARE_ICLOUD_BACKUP_CHOOSE_ERROR
	@param log_data md5(iCloud account)
	@param extend_data snapshot id
	@param files *.zip
	*/
	#define SOFTWARE_ICLOUD_BACKUP_CHOOSE_ERROR "0017"
//////////////////<SOFTWARE_ICLOUD End>//////////////////


/*!
@brief 自动安装iTunes码定义
@param category_code SOFTWARE_INSTALL_ITUNES
*/
#define SOFTWARE_INSTALL_ITUNES "0026"
//////////////////<SOFTWARE_INSTALL_ITUNES Start>//////////////////
	/*!
	@brief 下载失败
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_DOWNLOAD_ERROR
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_DOWNLOAD_ERROR "0001"

	/*!
	@brief 取消下载
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_DOWNLOAD_CANCEL
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_DOWNLOAD_CANCEL "0002"

	/*!
	@brief 解压失败
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_DECOMPRESS_ERROR
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_DECOMPRESS_ERROR "0003"

	/*!
	@brief 取消解压
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_DECOMPRESS_CANCEL
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_DECOMPRESS_CANCEL "0004"

	/*!
	@brief 安装失败
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_SETUP_ERROR
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_SETUP_ERROR "0005"

	/*!
	@brief 取消安装
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_SETUP_CANCEL
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_SETUP_CANCEL "0006"

	/*!
	@brief 驱动加载成功
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_LOAD_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_LOAD_SUCCESS "0007"

	/*!
	@brief 驱动加载失败
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_LOAD_ERROR
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_LOAD_ERROR "0008"

	/*!
	@brief 获取iTunes下载地址失败
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_GETURL_ERROR
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_GETURL_ERROR "0009"

	/*!
	@brief 取消获取iTunes下载地址
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_GETURL_CANCEL
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_GETURL_CANCEL "0010"

	/*!
	@brief 未安装iTunes驱动
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_NEED_INSTALL
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_NEED_INSTALL "0013"

	/*!
	@brief 服务程序未启动
	@param level error
	@param log_code SOFTWARE_INSTALL_ITUNES_NEED_SERVICES
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_ITUNES_NEED_SERVICES "0014"

	/*!
	@brief 获取iTunes下载地址成功
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_GETURL_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_GETURL_SUCCESS "0015"

	/*!
	@brief 下载完成
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_DOWNLOAD_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_DOWNLOAD_SUCCESS "0016"

	/*!
	@brief 解压完成
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_DECOMPRESS_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_DECOMPRESS_SUCCESS "0017"

	/*!
	@brief 安装成功
	@param level info
	@param log_code SOFTWARE_INSTALL_ITUNES_SETUP_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_SETUP_SUCCESS "0018"

	/*!
	@brief itunes安装失败驱动失败
	@param level warning
	@param log_code SOFTWARE_INSTALL_ITUNES_UNKNOWN_ERROR
	@param log_data 自定义
	@param extend_data 错误类型（1603、1618、1620）
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_ITUNES_UNKNOWN_ERROR "0019"
//////////////////<SOFTWARE_INSTALL_ITUNES End>//////////////////


/*!
@brief QQ相关信息收集码定义
@param category_code SOFTWARE_QQ_OPERATION
*/
#define SOFTWARE_QQ_OPERATION "0027"
//////////////////<SOFTWARE_QQ_OPERATION Start>//////////////////
	/*!
	@brief QQ账号数量
	@param level info
	@param log_code SOFTWARE_QQ_OPERATION_ACCOUNTINFO
	@param log_data 每个账户对应的数据库文件大小,以','作为分隔符,例: [size1,size2,size3....]
	@param extend_data 账户数量
	@param files 未使用
	*/
	#define SOFTWARE_QQ_OPERATION_ACCOUNTINFO "0001"

	/*!
	@brief QQ版本
	@param level info
	@param log_code SOFTWARE_QQ_OPERATION_VERSION
	@param log_data json: {[bound_id, verison], [bound_id, verison], [bound_id, verison]...}
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_QQ_OPERATION_VERSION "0002"
//////////////////<SOFTWARE_QQ_OPERATION End>//////////////////


/*!
@brief 收集竞争对手软件信息
@param category_code SOFTWARE_WECHAT_OPERATION
*/
#define SOFTWARE_COLLECT_OTHER_PRODUCT "0028"
//////////////////<SOFTWARE_COLLECT_OTHER_PRODUCT Start>//////////////////
	/*!
	@brief 产品信息
	@param level info
	@param log_code SOFTWARE_QQ_OPERATION_VERSION
	@param log_data 产品信息: app_name:app_version
	@param extend_data 是否注册: True/False
	@param files 未使用
	*/
	#define SOFTWARE_COLLECT_OTHER_PRODUCT_INFO "0001"
//////////////////<SOFTWARE_COLLECT_OTHER_PRODUCT End>//////////////////


/*!
@brief 微信相关信息收集码定义
@param category_code SOFTWARE_WECHAT_OPERATION
*/
#define SOFTWARE_WECHAT_OPERATION "0029"
//////////////////<SOFTWARE_WECHAT_OPERATION Start>//////////////////
	/*!
	@brief 微信账号数量
	@param level info
	@param log_code SOFTWARE_WECHAT_OPERATION_ACCOUNTINFO
	@param log_data json: 每个账户对应的数据库文件大小,以','作为分隔符,例: [size1,size2,size3....]
	@param extend_data 账户数量
	@param files 未使用
	*/
	#define SOFTWARE_WECHAT_OPERATION_ACCOUNTINFO "0001"

	/*!
	@brief 微信版本
	@param level info
	@param log_code SOFTWARE_WECHAT_OPERATION_VERSION
	@param log_data json: {[bound_id, verison], [bound_id, verison], [bound_id, verison]...}
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_WECHAT_OPERATION_VERSION "0002"
//////////////////<SOFTWARE_WECHAT_OPERATION End>//////////////////


/*!
@brief 设备页面信息码定义
@param category_code SOFTWARE_MOBILE_DEVICE
*/
#define SOFTWARE_MOBILE_DEVICE "0034"
//////////////////<SOFTWARE_MOBILE_DEVICE Start>//////////////////
	/*!
	@brief 未知错误(连接后, android/ios通用)
	@param level error
	@param log_code SOFTWARE_MOBILE_DEVICE_UNKNOWNERROR
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_MOBILE_DEVICE_UNKNOWNERROR "0001"

	/*!
	@brief 未信任(连接后, ios)
	@param level error
	@param log_code SOFTWARE_MOBILE_DEVICE_NOTTRUSTED
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_MOBILE_DEVICE_NOTTRUSTED "0002"

	/*!
	@brief 驱动版本不匹配(连接后, ios)
	@param level error
	@param log_code SOFTWARE_MOBILE_DEVICE_LOWERITUNES
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_MOBILE_DEVICE_LOWERITUNES "0003"

	/*!
	@brief 成功(连接后, android/ios通用)
	@param level info
	@param log_code SOFTWARE_MOBILE_DEVICE_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_MOBILE_DEVICE_SUCCESS "0004"

	/*!
	@brief 锁屏(连接中, ios)
	@param level warning
	@param log_code SOFTWARE_MOBILE_DEVICE_PASSWORDPROTECTED
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_MOBILE_DEVICE_PASSWORDPROTECTED "0005"

	/*!
	@brief 信任(连接中, ios)
	@param level warning
	@param log_code SOFTWARE_MOBILE_DEVICE_TRUSTCOMPUTER
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_MOBILE_DEVICE_TRUSTCOMPUTER "0006"

	/*!
	@brief 开始扫描(android/ios通用)
	@param level info
	@param log_code SOFTWARE_MOBILE_DEVICE_START_SCAN
	@param log_data 填写mobile-device
	@param extend_data 设备序列号/UDID 优先选择设备序列号，如设备序列号不存在则选择设备UDID，如果都不存在则不填写
	@param files 未使用
	*/
	#define SOFTWARE_MOBILE_DEVICE_START_SCAN "0007"

	/*!
	@brief 开始连接(android/ios通用)
	@param level info
	@param log_code SOFTWARE_MOBILE_DEVICE_START_CONNECT
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_MOBILE_DEVICE_START_CONNECT "0008"
	
	 /*!
    @brief 未ROOT(连接后, android)
    @param level error
    @param log_code SOFTWARE_MOBILE_DEVICE_ERROR_NOROOT
    @param log_data 自定义
    @param extend_data 自定义
    @param files *.zip
    */
    #define SOFTWARE_MOBILE_DEVICE_ERROR_NOROOT "0009"

    /*!
    @brief 驱动未安装(连接中, android)
    @param level warning
    @param log_code SOFTWARE_MOBILE_DEVICE_NODRIVER
    @param log_data 自定义
    @param extend_data 自定义
    @param files 未使用
    */
    #define SOFTWARE_MOBILE_DEVICE_NODRIVER "0010"

    /*!
    @brief 未打开调试模式(连接中, android)
    @param level warning
    @param log_code SOFTWARE_MOBILE_DEVICE_NODEBUG
    @param log_data 自定义
    @param extend_data 自定义
    @param files 未使用
    */
    #define SOFTWARE_MOBILE_DEVICE_NODEBUG "0011"

    /*!
    @brief USB未授权(连接中, android)
    @param level warning
    @param log_code SOFTWARE_MOBILE_DEVICE_NOAUTHOR
    @param log_data 自定义
    @param extend_data 自定义
    @param files 未使用
    */
    #define SOFTWARE_MOBILE_DEVICE_NOAUTHOR "0012"

    /*!
    @brief 降级备份模式(连接后, android)
    @param level info
    @param log_code SOFTWARE_MOBILE_DEVICE_SUCCESS_DOWNGRADE
    @param log_data 自定义
    @param extend_data 自定义
    @param files 未使用
    */
    #define SOFTWARE_MOBILE_DEVICE_SUCCESS_DOWNGRADE "0013"
//////////////////<SOFTWARE_MOBILE_DEVICE End>//////////////////


/*!
@brief FrameWork下载，安装和注册相关
@param category_code SOFTWARE_INSTALL_FRAMEWORK
*/
#define SOFTWARE_INSTALL_FRAMEWORK "0035"
//////////////////<SOFTWARE_INSTALL_FRAMEWORK Start>//////////////////
	/*!
	@brief Framework已安装
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_YES
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_YES "0001"

	/*!
	@brief Framework未安装
	@param level warning
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_NO
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_NO "0002"

	/*!
	@brief Framework下载成功
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_SUCCESS "0003"

	/*!
	@brief Framework下载失败
	@param level error
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_FAILED
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_FAILED "0004"

	/*!
	@brief Framework取消下载
	@param level warning
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_CANCEL
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_DOWNLOAD_CANCEL "0005"

	/*!
	@brief Framework安装成功
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_INSTALL_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_INSTALL_SUCCESS "0006"

	/*!
	@brief Framework安装失败
	@param level error
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_INSTALL_FAILED
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_INSTALL_FAILED "0007"

	/*!
	@brief Framework取消安装
	@param level warning
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_INSTALL_CANCEL
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_INSTALL_CANCEL "0008"

	/*!
	@brief Framework组件注册成功
	@param level info
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_REGISTER_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_REGISTER_SUCCESS "0009"

	/*!
	@brief Framework组件注册失败
	@param level error
	@param log_code SOFTWARE_INSTALL_FRAMEWORK_REGISTER_FAILED
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_INSTALL_FRAMEWORK_REGISTER_FAILED "0010"
//////////////////<SOFTWARE_INSTALL_FRAMEWORK End>//////////////////


/*!
@brief iTunes备份列表
@param category_code SOFTWARE_ITUNES_BACKUP
*/
#define SOFTWARE_ITUNES_BACKUP "0036"
//////////////////<SOFTWARE_ITUNES_BACKUP Start>//////////////////
	/*!
	@brief 收集用户备份信息
	@param level info
	@param log_code SOFTWARE_ITUNES_BACKUP_INFO
	@param log_data json: {[serial, udid, size, version], [serial, udid, size, version]...}
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_ITUNES_BACKUP_INFO "0001"

	/*!
	@brief 打开用户自定义目录成功
	@param level info
	@param log_code SOFTWARE_ITUNES_BACKUP_CHOOSE_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_ITUNES_BACKUP_CHOOSE_SUCCESS "0002"

	/*!
	@brief 打开用户自定义目录失败
	@param level error
	@param log_code SOFTWARE_ITUNES_BACKUP_CHOOSE_ERROR
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_ITUNES_BACKUP_CHOOSE_ERROR "0003"

	/*!
	@brief 开始扫描
	@param level info
	@param log_code SOFTWARE_ITUNES_BACKUP_START_SCAN
	@param log_data 填写moible-backup
	@param extend_data 设备序列号/UDID 优先选择设备序列号，如设备序列号不存在则选择设备UDID，如果都不存在则不填写
	@param files 未使用
	*/
	#define SOFTWARE_ITUNES_BACKUP_START_SCAN "0004"
//////////////////<SOFTWARE_ITUNES_BACKUP End>//////////////////


/*!
@brief 设备或备份检测
@param category_code SOFTWARE_CHECK_SETUP
*/
#define SOFTWARE_CHECK_SETUP "0037"
//////////////////<SOFTWARE_CHECK_SETUP Start>//////////////////
	/*!
	@brief 锁屏检测通过
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_LOCKSCREEN_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_CHECK_SETUP_LOCKSCREEN_SUCCESS "0001"

	/*!
	@brief 锁屏检测错误
	@param level error
	@param log_code SOFTWARE_CHECK_SETUP_LOCKSCREEN_FAILED
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_CHECK_SETUP_LOCKSCREEN_FAILED "0002"

	/*!
	@brief 备份加密检测通过
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_PASSWORD_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_CHECK_SETUP_BACKUP_PASSWORD_SUCCESS "0003"

	/*!
	@brief 备份加密检测错误
	@param level error
	@param log_code SOFTWARE_CHECK_SETUP_PASSWORD_FAILED
	@param log_data 自定义
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_CHECK_SETUP_BACKUP_PASSWORD_FAILED "0004"

	/*!
	@brief 密码保护检测通过
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_PW_PROTECTED_SUCCESS
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_CHECK_SETUP_PW_PROTECTED_SUCCESS "0005"

	/*!
	@brief 密码保护检测通过
	@param level info
	@param log_code SOFTWARE_CHECK_SETUP_PW_PROTECTED_FAILED
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_CHECK_SETUP_PW_PROTECTED_FAILED "0006"
//////////////////<SOFTWARE_CHECK_SETUP End>//////////////////


/*!
@brief 数据项恢复信息码
@param category_code SOFTWARE_RECOVER_DATA
*/
#define SOFTWARE_RECOVER_DATA "0038"
//////////////////<SOFTWARE_RECOVER_DATA Start>//////////////////
	/*!
	@brief 备份(开始备份)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_START
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_START "0001"

	/*!
	@brief 备份(索引文件解析错误)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_MANIFEST
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_MANIFEST "0002"

	/*!
	@brief 备份(解密失败)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_DECRYPT
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_DECRYPT "0003"

	/*!
	@brief 备份(锁屏错误)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_LOCKERR
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_LOCKERR "0004"

	/*!
	@brief 备份(通信失败)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_SOCKETERR
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_SOCKETERR "0005"

	/*!
	@brief 备份(PC磁盘空间不足)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_FREESPACE
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_FREESPACE "0006"

	/*!
	@brief 备份(用户打开了设置)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_SETUP
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_SETUP "0007"

	/*!
	@brief 备份(PC磁盘写错误)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_DISKERR
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_DISKERR "0008"

	/*!
	@brief 备份(LSP错误)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_LSPERR
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_LSPERR "0009"

	/*!
	@brief 备份(设备空间不足)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_DEVFREESPACE
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_DEVFREESPACE "0010"

	/*!
	@brief 备份(设备文件被占用)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_MULTIERROR
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_MULTIERROR "0011"

	/*!
	@brief 备份(unknown-domain)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWNDOMAIN
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWNDOMAIN "0012"

	/*!
	@brief 备份(未知错误)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWN
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_ERROR_UNKNOWN "0013"

	/*!
	@brief 备份(取消备份)
	@param level warning
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_CANCEL
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_CANCEL "0014"

	/*!
	@brief 备份(备份成功)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_BACKUP_SUCCESS
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_BACKUP_SUCCESS "0015"

	/*!
	@brief 扫描(开始扫描)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_SCAN_START
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_START "0016"

	/*!
	@brief 扫描(不存在目标App)
	@param level warning
	@param log_code SOFTWARE_SCAN_DATA_SCAN_ERROR_NOAPP
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_ERROR_NOAPP "0017"

	/*!
	@brief 扫描(缺失文件)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_SCAN_ERROR_LACKFILE
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_ERROR_LACKFILE "0018"

	/*!
	@brief 扫描(未知错误)
	@param level error
	@param log_code SOFTWARE_SCAN_DATA_SCAN_ERROR_UNKNOWN
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files *.zip
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_ERROR_UNKNOWN "0019"

	/*!
	@brief 扫描(取消扫描)
	@param level warning
	@param log_code SOFTWARE_SCAN_DATA_SCAN_CANCEL
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_CANCEL "0020"

	/*!
	@brief 扫描(扫描成功)
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_SCAN_SUCCESS
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型(device/backup/icloud)
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_SCAN_SUCCESS "0021" 

	/*!
	@brief 扫描成功后，恢复的数据数量
	@param level info
	@param log_code SOFTWARE_SCAN_DATA_NUMBER
	@param log_data 数据项掩码
	@param extend_data 数据总条目(例: 短信(112) 微信消息(11,100,9))
	@param files 未使用
	*/
	#define SOFTWARE_SCAN_DATA_NUMBER "0022" 

	/*!
	@brief （备份）缺失必要文件
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_LACKFILE
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型（device/backup）
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_LACKFILE "0023"

	/*!
	@brief （备份）请求设备管理员权限失败
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_NOSUPPER
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型（device/backup）
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_NOSUPPER "0024"

	/*!
	@brief （备份）拉取设备文件失败
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_NOPULL
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型（device/backup）
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_NOPULL "0025"

	/*!
	@brief （备份）解压设备备份文件失败
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_DECOMPRESS
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型（device/backup）
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_DECOMPRESS "0126"

	/*!
	@brief （备份）消息接收未知异常
	@param level error
	@param log_code SOFTWARE_BACKUP_DATA_ERROR_UNKNOWNRECMSG
	@param log_data 数据项掩码
	@param extend_data 扫描的设备类型（device/backup）
	@param files *.zip
	*/
	#define SOFTWARE_BACKUP_DATA_ERROR_UNKNOWNRECMSG "0026"

	/*!
	@brief manifest.db大小搜集
	@param level info
	@param log_code SOFTWARE_BACKUP_DATA_MANIFEST_SIZE
	@param log_data 数据项掩码
	@param extend_data 数据库大小
	@param files 未使用
	*/
	#define SOFTWARE_BACKUP_DATA_MANIFEST_SIZE "0027"

	/*!
	@brief manifest.db解析时长搜集
	@param level info
	@param log_code SOFTWARE_BACKUP_DATA_ANALYSE_TIME
	@param log_data 数据项掩码
	@param extend_data 解析文件时长
	@param files 未使用
	*/
	#define SOFTWARE_BACKUP_DATA_ANALYSE_TIME "0028"
//////////////////<SOFTWARE_RECOVER_DATA End>//////////////////


/*!
@brief 数据项导出信息码
@param category_code SOFTWARE_EXPORT_DATA
*/
#define SOFTWARE_EXPORT_DATA "0039"
//////////////////<SOFTWARE_EXPORT_DATA Start>//////////////////
	/*!
	@brief 导出到PC成功
	@param level info
	@param log_code SOFTWARE_EXPORT_DATA_TOPC_SUCCESS
	@param log_data 数据项掩码
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_EXPORT_DATA_TOPC_SUCCESS "0001"

	/*!
	@brief 导出到PC失败
	@param level error
	@param log_code SOFTWARE_EXPORT_DATA_TOPC_FAILED
	@param log_data 数据项掩码
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_EXPORT_DATA_TOPC_FAILED "0002"

	/*!
	@brief 导出到设备成功
	@param level info
	@param log_code SOFTWARE_EXPORT_DATA_TODEVICE_SUCCESS
	@param log_data 数据项掩码
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_EXPORT_DATA_TODEVICE_SUCCESS "0003"

	/*!
	@brief 导出到设备失败
	@param level error
	@param log_code SOFTWARE_EXPORT_DATA_TODEVICE_FAILED
	@param log_data 数据项掩码
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_EXPORT_DATA_TODEVICE_FAILED "0004"
//////////////////<SOFTWARE_EXPORT_DATA End>//////////////////


/*!
@brief 分辨率信息码
@param category_code SOFTWARE_SCREEN
*/
#define SOFTWARE_SCREEN "0040"
//////////////////<SOFTWARE_SCREEN Start>//////////////////
	/*!
	@brief 正常分辨率
	@param level info
	@param log_code SOFTWARE_NORMAL_SCREEN_REPORT
	@param log_data 宽度X高度
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_NORMAL_SCREEN_REPORT "0001"
		/*!
	@brief 高辨率
	@param level info
	@param log_code SOFTWARE_HIGH_SCREEN_REPORT
	@param log_data 宽度X高度
	@param extend_data 自定义
	@param files *.zip
	*/
	#define SOFTWARE_HIGH_SCREEN_REPORT "0002"
//////////////////<SOFTWARE_SCREEN End>//////////////////


/*!
@brief momo相关信息收集码定义
@param category_code SOFTWARE_MOMO_OPERATION
*/
#define SOFTWARE_MOMO_OPERATION "0041"
//////////////////<SOFTWARE_MOMO_OPERATION Start>//////////////////
	/*!
	@brief 陌陌账号数量
	@param level info
	@param log_code SOFTWARE_MOMO_OPERATION_ACCOUNTINFO
	@param log_data 每个账户对应的数据库文件大小,以','作为分隔符,例: [size1,size2,size3....]
	@param extend_data 账户数量
	@param files 未使用
	*/
	#define SOFTWARE_MOMO_OPERATION_ACCOUNTINFO "0001"

	/*!
	@brief 陌陌版本
	@param level info
	@param log_code SOFTWARE_MOMO_OPERATION_VERSION
	@param log_data json: {[bound_id, verison], [bound_id, verison], [bound_id, verison]...}
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_MOMO_OPERATION_VERSION "0002"
//////////////////<SOFTWARE_MOMO_OPERATION End>//////////////////

/*!
@brief 软件注册相关信息收集
@param category_code SOFTWARE_REGISTE
*/
#define SOFTWARE_REGISTE "0042"
//////////////////<SOFTWARE_REGISTE Start>//////////////////
	/*!
	@brief 软件启动时自动弹出注册框
	@param level info
	@param log_code SOFTWARE_REGISTE_LAUNCH
	@param log_data 自定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_REGISTE_LAUNCH "0001"

	/*!
	@brief 注册成功
	@param level info
	@param log_code SOFTWARE_REGISTE_SUCCESS
	@param log_data 未定义
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_REGISTE_SUCCESS "0002"

	/*!
	@brief 注册失败
	@param level warning
	@param log_code SOFTWARE_REGISTE_FAILURE
	@param log_data 错误码 
	@param extend_data 自定义
	@param files 未使用
	*/
	#define SOFTWARE_REGISTE_FAILURE "0003"
	
	
	/*!
	@brief 注册设备所需时间：正常流程
	@param level info
	@param log_code SOFTWARE_REGISTE_DEVICE_TIME_NORMAL
	@param log_data 注册所需时间，ms 
	@param extend_data 成功true,失败false
	@param files 未使用
	*/
	#define SOFTWARE_REGISTE_DEVICE_TIME_NORMAL "0004"
	
	/*!
	@brief 注册设备所需时间:在数据项里面，注册成功后，注册设备
	@param level info
	@param log_code SOFTWARE_REGISTE_DEVICE_TIME_DATA
	@param log_data 注册所需时间，ms 
	@param extend_data 成功true,失败false
	@param files 未使用
	*/
	#define SOFTWARE_REGISTE_DEVICE_TIME_DATA "0005"
	
		/*!
	@brief 注册设备所需时间:在数据项里面，点到导出pc，注册成功后，注册设备
	@param level info
	@param log_code SOFTWARE_REGISTE_DEVICE_TIME_RECOVERY
	@param log_data 注册所需时间，ms 
	@param extend_data 成功true,失败false
	@param files 未使用
	*/
	#define SOFTWARE_REGISTE_DEVICE_TIME_RECOVERY "0006"
//////////////////<SOFTWARE_REGISTE End>//////////////////




/*!
@brief 数据项搜索
@param category_code DATA_PLUGIN_SEARCH
*/
#define DATA_PLUGIN_SEARCH "0043"
//////////////////<DATA_PLUGIN_SEARCH Start>//////////////////
	/*!
	@brief 搜索开始
	@param level info
	@param log_code DATA_PLUGIN_SEARCH_START
	@param log_data 数据项掩码
	@param extend_data 数据项会话总数
	@param files 未使用
	*/
	#define DATA_PLUGIN_SEARCH_START "0001"

	/*!
	@brief 搜索结束
	@param level info
	@param log_code DATA_PLUGIN_SEARCH_END
	@param log_data 数据项掩码
	@param extend_data 搜索到的会话数
	@param files 未使用
	*/
	#define DATA_PLUGIN_SEARCH_END "0002"
//////////////////<DATA_PLUGIN_SEARCH End>//////////////////



/*!
@brief 登录
@param category_code DATA_PLUGIN_SEARCH
*/
#define SOFEWARE_LOGIN "0050"
//////////////////<SOFEWARE_LOGIN Start>//////////////////
	/*!
	@brief 登录成功
	@param level info
	@param log_code SOFEWARE_LOGIN_SUCCESS
	@param log_data 登录帐号
	@param extend_data 未使用
	@param files 未使用
	*/
	#define SOFEWARE_LOGIN_SUCCESS "0001"

	/*!
	@brief 登录失败
	@param level error
	@param log_code DATA_PLUGIN_SEARCH_END
	@param log_data 登录帐号
	@param extend_data 失败原因，失败码
	@param files *.zip
	*/
	#define SOFEWARE_LOGIN_FAILURE "0002"
	
	/*!
	@brief 软件启动弹出登录窗口
	@param level error
	@param log_code DATA_PLUGIN_SEARCH_END
	@param log_data 是否自动登录，自动登录“1”，非自动登录“0”
	@param extend_data 未使用
	@param files 未使用
	*/
	#define SOFEWARE_LOGIN_START "0003"
//////////////////<SOFEWARE_LOGIN End>//////////////////



/*!
@brief 弹出授权提示
@param category_code SOFEWARE_AUTH
*/
#define SOFEWARE_AUTH "0051"
//////////////////<SOFEWARE_AUTH Start>//////////////////
	/*!
	@brief 软件启动自动弹出授权提示
	@param level info
	@param log_code SOFEWARE_AUTH_AUTO
	@param log_data 未使用
	@param extend_data 未使用
	@param files 未使用
	*/
	#define SOFEWARE_AUTH_AUTO "0001"
//////////////////<SOFEWARE_AUTH End>//////////////////

/*!
@brief 弹出授权提示
@param category_code FIRST_START_SOFTWARE
*/
#define FIRST_START_SOFTWARE "0052"
//////////////////<FIRST_START_SOFTWARE Start>//////////////////
	/*!
	@brief 软件启动首次启动弹出试用窗口
	@param level info
	@param log_code SOFEWARE_AUTH_AUTO
	@param log_data 未使用
	@param extend_data 未使用
	@param files 未使用
	*/
	#define FIRST_START_SOFTWARE_WINDOW "0001"
//////////////////<FIRST_START_SOFTWARE End>//////////////////

/*!
@brief 弹出窗口来源
@param category_code SOFTWARE_SHOW_WINDOW
*/
#define SOFTWARE_SHOW_WINDOW "0053"
//////////////////<SOFTWARE_SHOW_WINDOW Start>//////////////////
	/*!
	@brief 弹出购买窗口的来源
	@param level info
	@param log_code SOFTWARE_PURCHASE
	@param log_data smp码，标记来源
	@param extend_data 未使用
	@param files 未使用
	*/
	#define SOFTWARE_SHOW_WINDOW_PURCHASE "0001"
	
	/*!
	@brief 弹出登录窗口的来源
	@param level info
	@param log_code SOFTWARE_LOGIN
	@param log_data smp码，标记来源
	@param extend_data 未使用
	@param files 未使用
	*/
	#define SOFTWARE_SHOW_WINDOW_LOGIN "0002"
//////////////////<SOFTWARE_PURCHASE End>//////////////////


/*!
@brief 开发者软件线上调试阶段数据收集
@param DEVELOPER_DEBUG_LOG
@note 该错误号阶段性存在，当需要解决的问题已经定位到，则该错误号需要从软件内移除
*/
#define DEVELOPER_DEBUG_LOG "9990"
//////////////////<DEVELOPER_DEBUG_LOG Start>//////////////////
	/*!
    @brief 收集iTunes驱动安装时
    @param level error
    @param log_code DEVELOPER_DEBUG_LOG_ITUNES_MSI_LOG
    @param log_data 开发者自定义
    @param extend_data 开发者自定义
    @param files *.zip 
	@note 注意该错误号收集的日志文件可以由开发者自定义,但压缩后的总文件大小不能超过1MB
    */
    #define DEVELOPER_DEBUG_LOG_ITUNES_MSI_LOG "0001"
	
	/*!
    @brief 收集手机使用空间和磁盘剩余大小
    @param level info
    @param log_code DEVELOPER_DEBUG_LOG_IPHONE_USER_SIZE_AND_DISK_FREE_SIZE
    @param log_data 手机使用空间
    @param extend_data 磁盘剩余空间
    @param files *.zip 
    */
    #define DEVELOPER_DEBUG_LOG_IPHONE_USER_SIZE_AND_DISK_FREE_SIZE "0002"
//////////////////<DEVELOPER_DEBUG_LOG End>//////////////////

#endif
