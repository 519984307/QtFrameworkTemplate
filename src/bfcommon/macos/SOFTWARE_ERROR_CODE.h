#ifndef SOFTWARE_ERROR_CODE_H__
#define SOFTWARE_ERROR_CODE_H__

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


#endif
