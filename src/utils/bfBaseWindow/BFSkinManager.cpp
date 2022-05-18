
#include "BFSkinManager.h"
#include <QCoreApplication>

BFSkinManager BFSkinMgr;

QColor BFSkinManager::backGroundColor;
QColor BFSkinManager::borderLineColor;
QColor BFSkinManager::barColor;
QColor BFSkinManager::fontColor;
QColor BFSkinManager::backGroundBarColor;
QColor BFSkinManager::statusColor;
QColor BFSkinManager::bkBarColor;
QColor BFSkinManager::buttonColor;
QColor BFSkinManager::buttonLineColor;
QColor BFSkinManager::buttonLineColor1;
QColor BFSkinManager::menuHoverColor;
QColor BFSkinManager::otherBkBarColor;
QColor BFSkinManager::color_icon_back;
QColor BFSkinManager::complete_color;



QColor BFSkinManager::TextColor[4] = {QColor("#1A1A1A"), QColor("#3F3F3F"), QColor("#666666"), QColor("#999999")};


//软件更新页面用颜色
QColor BFSkinManager::update_page_bar;                   //标题栏颜色
QColor BFSkinManager::update_page_context;               //页内容颜色
QColor BFSkinManager::update_page_confirm_btn_text;      //确认向按钮文字颜色
QColor BFSkinManager::update_page_cancel_btn_text;       //取消向按钮文字颜色
QColor BFSkinManager::update_page_confirm_btn_back;      //确认向按钮背景颜色
QColor BFSkinManager::update_page_cancel_btn_back;       //取消向按钮背景颜色
QColor BFSkinManager::update_page_verinfo_border;        //版本信息边框
QColor BFSkinManager::update_page_verinfo_text;          //版本信息文字颜色
QColor BFSkinManager::update_page_verinfo_back;          //版本信息背景


//弹窗
QColor BFSkinManager::dialog_title_bar_color;           //标题颜色
QColor BFSkinManager::dialog_context_color;             //内容页颜色


//CMain边框
QColor BFSkinManager::main_bord_color;



//主视图窗口
QColor BFSkinManager::pic_view_select_color;    //视图选中颜色
QColor BFSkinManager::pic_view_text_name_color; //视图名称颜色框颜色
QColor BFSkinManager::pic_view_text_other_color;//视图信息颜色框颜色
QColor BFSkinManager::pic_view_dir_pic_front_color;  //视图文件夹图片前景色
QColor BFSkinManager::pic_view_dir_pic_behind_color; //视图文件夹图片后景色


//花瓣导入页面
QColor BFSkinManager::huaban_title_text_color;          //内部标题文字颜色
QColor BFSkinManager::huaban_tips_lab_text_color;       //lab提示文字颜色
QColor BFSkinManager::huaban_tips_lab_text_color_type_0;//lab提示文字颜色类型
QColor BFSkinManager::huaban_input_text_color;          //输入框文字颜色
QColor BFSkinManager::huaban_wrong_tips_text_color;     //错误提示框文字颜色
QColor BFSkinManager::huaban_input_background_color;    //花瓣导入背景颜色
QColor BFSkinManager::huaban_input_border_color;        //边框颜色
QColor BFSkinManager::huaban_count_tips_text_color;     //花瓣数量提示文字
QColor BFSkinManager::huaban_count_tips_win_text_color; //花瓣数量弹窗文字
QColor BFSkinManager::huaban_count_tips_win_back_color; //花瓣数量弹窗背景颜色

//设置中心页面
QColor BFSkinManager::setting_center_btns_wid_color;    //用户中心左侧按钮wid底色
QColor BFSkinManager::setting_center_btn_check_color;   //用户中心左侧按钮选中底色
QColor BFSkinManager::setting_center_btn_uncheck_color; //用户中心左侧按钮未选中底色
QColor BFSkinManager::setting_center_page_color;        //用户中心右侧内容底色
QColor BFSkinManager::setting_center_close_btn_color;   //用户中心关闭按钮
QColor BFSkinManager::setting_center_save_btn_color;    //用户中心保存按钮
QColor BFSkinManager::setting_center_edit_back_color;    //用户中心输入框背景颜色
QColor BFSkinManager::setting_center_edit_border_color;    //用户中心输入框边框颜色

QVector<QColor> BFSkinManager::setting_center_text_color = { QColor(255,255,255,255),QColor(255, 255, 255, 255),QColor(255, 255, 255, 255 ),QColor(255, 255, 255, 255)};      //用户中心字体颜色







void BFSkinManager::SetMainBorderColor(const QColor& c)
{
	main_bord_color = c;
}

QColor & BFSkinManager::GetMainBorderColor()
{
	return main_bord_color;
}

void BFSkinManager::SetSettingCenterBtnsWidColor(const QColor& c)
{
	setting_center_btns_wid_color = c;
}

void BFSkinManager::SetSettingCenterBtnCheckColor(const QColor& c)
{
	setting_center_btn_check_color = c;
}

void BFSkinManager::SetSettingCenterBtnUnCheckColor(const QColor& c)
{
	setting_center_btn_uncheck_color = c;
}

void BFSkinManager::SetSettingCenterPageColor(const QColor& c)
{
	setting_center_page_color = c;
}


void BFSkinManager::SetSettingCenterCloseBtnColor(const QColor& c)
{
	setting_center_close_btn_color = c;
}

void BFSkinManager::SetSettingCenterSaveBtnColor(const QColor& c)
{
	setting_center_save_btn_color = c;
}

void BFSkinManager::SetSettingCenterEditBackColor(const QColor& c)
{
	setting_center_edit_back_color = c;
}

void BFSkinManager::SetSettingCenterEditBorderColor(const QColor& c)
{
	setting_center_edit_border_color = c;
}

void BFSkinManager::SetSettingCenterTextColor(QVector<QColor>vector_color)
{
	setting_center_text_color = vector_color;
}

QColor& BFSkinManager::GetSettingCenterBtnsWidColor()
{
	return setting_center_btns_wid_color;
}

QColor& BFSkinManager::GetSettingCenterBtnCheckColor()
{
	return setting_center_btn_check_color;
}

QColor& BFSkinManager::GetSettingCenterBtnUnCheckColor()
{
	return setting_center_btn_uncheck_color;
}

QColor& BFSkinManager::GetSettingCenterPageColor()
{
	return setting_center_page_color;
}


QColor& BFSkinManager::GetSettingCenterCloseBtnColor()
{
	return setting_center_close_btn_color;
}

QColor& BFSkinManager::GetSettingCenterSaveBtnColor()
{
	return setting_center_save_btn_color;
}

QColor& BFSkinManager::GetSettingCenterEditBackColor()
{
	return setting_center_edit_back_color;
}

QColor& BFSkinManager::GetSettingCenterEditBorderColor()
{
	return setting_center_edit_border_color;
}

QColor BFSkinManager::GetSettingCenterTextColor(int index)
{
	if (index >= setting_center_text_color.size())
	{
		return QColor(111, 111, 111);
	}
	return setting_center_text_color.at(index);
}

void initSkin(int style)
{
	if (style == 1)	// 黑色皮肤
	{
		g_SkinStyle = 1;

		BFSetBackGroundColor(QColor("#2C2C2C"));
		BFSetBorderLineColor(QColor("#181818"));
		BFSetBarColor(QColor("#2C2C2C"));
		BFSetFontColor(QColor("#EEEEEE"));
		BFSetButtonColor(QColor(255, 255, 255, 48));
		BFSetTextColor(1);
		BFSetButtonLineColor(QColor(255, 255, 255, 48));
		BFSetBackGroundBarColor(QColor("#2C2C2C"));
		BFSetOtherBKBarColor(QColor("#5E5E5E"));
		BFSetButtonLineColor1(QColor("#2C2C2C"));
		BFSetMenuHoverColor(QColor(255,255,255,20));

		BFSetIconBackColor(QColor(44, 44, 44));
		BFSetCompleteColor(QColor(64, 62, 65));


		//软件更新页面
		BFSkinManager::SetUpdatePageBar(QColor(75, 75, 75, 255));
		BFSkinManager::SetUpdatePageContext(QColor(64, 62, 63));
		BFSkinManager::SetUpdatePageConfirmBtnText(QColor(255, 255, 255));
		BFSkinManager::SetUpdatePageCancelBtnText(QColor(255, 255, 255));
		BFSkinManager::SetUpdatePageConfirmBtnBack(QColor(23, 142, 240));
		BFSkinManager::SetUpdatePageCancelBtnBack(QColor(255, 255, 255, 255 * 0.3));
		BFSkinManager::SetUpdatePageVerInfoBorder(QColor(43, 43, 43));
		BFSkinManager::SetUpdatePageVerInfoText(QColor(255, 255, 255, 255 * 0.65));
		BFSkinManager::SetUpdatePageVerInfoBack(QColor(43, 43, 43, 255));


		//Cmain边框
		BFSkinManager::SetMainBorderColor(QColor(44, 44, 44, 255));


		//大部分弹窗样式
		BFSkinManager::SetDialogTitleBar(QColor(76, 74, 75, 255));
		BFSkinManager::SetDialogContext(QColor(63, 63, 63, 255));

		//右侧视图选中颜色
		BFSkinManager::SetPicViewSelectColor(QColor(255, 255, 255, 18));
		BFSkinManager::SetPicViewTextNameColor(QColor(166, 166, 166, 255));
		BFSkinManager::SetPicViewTextOtherColor(QColor(102, 102, 102, 255));
		BFSkinManager::SetPicViewDirPicFrontColor(QColor(66, 66, 66, 255));
		BFSkinManager::SetPicViewDirPicBehindColor(QColor(92, 92, 92, 255));

		//花瓣导入
		BFSkinManager::SetHuaBanTitleTextColor(QColor(255,255,255,255*0.85));
		BFSkinManager::SetHuaBanTipsLabTextColor(QColor(255, 255, 255, 255*0.65));
		BFSkinManager::SetHuaBanTipsLabTextColor_type_0(QColor(255, 255, 255, 255*0.45));
		BFSkinManager::SetHuaBanInputTextColor(QColor(255, 255, 255, 255*0.35));
		BFSkinManager::SetHuaBanWrongTipsTextColor(QColor(240, 67, 64, 255));
		BFSkinManager::SetHuaBanInputBackGroundColor(QColor(44,44,44,0.96*255));
		BFSkinManager::SetHuaBanInputBorderColor(QColor(255, 255, 255, 255*0.2));
		BFSkinManager::SetHuaBanCountTipTextColor(QColor(255, 255, 255, 255*0.4));
		BFSkinManager::SetHuaBanInputCountWinTextColor(QColor(255, 255, 255, 0.85 * 255));
		BFSkinManager::SetHuaBanInputCountWinBackColor(QColor(102, 102, 102, 255));


		//用户中心设置
		BFSkinManager::SetSettingCenterBtnsWidColor(QColor(44,44,44,255));
		BFSkinManager::SetSettingCenterBtnCheckColor(QColor(63, 63, 63, 255));
		BFSkinManager::SetSettingCenterBtnUnCheckColor(QColor(44, 44, 44, 255));
		BFSkinManager::SetSettingCenterPageColor(QColor(63, 63, 63, 255));
		BFSkinManager::SetSettingCenterCloseBtnColor(QColor(255, 255, 255, 255*0.15));
		BFSkinManager::SetSettingCenterSaveBtnColor(QColor(32, 124, 255, 255));
		BFSkinManager::SetSettingCenterEditBackColor(QColor(44, 44, 44, 255));
		BFSkinManager::SetSettingCenterEditBorderColor(QColor(255, 255, 255, 255*0.2));
		QVector<QColor>need_setting_center_text_color = {QColor(255,255,255,255 * 0.45),QColor(255, 255, 255, 255 * 0.65),QColor(255, 255, 255, 255 * 0.85),QColor(255, 255, 255, 255 * 1)};
		BFSkinManager::SetSettingCenterTextColor(need_setting_center_text_color);



	}
	else    // 白色皮肤
	{
		g_SkinStyle = 0;

		BFSetBackGroundColor(QColor("#FFFFFF"));
		BFSetBorderLineColor(QColor("#D8D8D8"));
		BFSetBarColor(QColor("#FAFAFA"));
		BFSetFontColor(QColor("#1A1A1A"));
		BFSetBackGroundBarColor(QColor("#F2F2F2"));
		BFSetStausColor(QColor("#1B90FB"));
		BFSetButtonColor(QColor("#FFFFFF"));
		BFSetTextColor(0);
		BFSetButtonLineColor(QColor("#D8D8D8"));
		BFSetOtherBKBarColor(QColor("#F9F9F9"));
		BFSetButtonLineColor1(QColor("#D8D8D8"));
		BFSetMenuHoverColor(QColor("#EDEDED"));


		BFSetIconBackColor(QColor(249, 249, 249, 255));
		BFSetCompleteColor(QColor(255, 255, 255, 255));



		//软件更新页面
		BFSkinManager::SetUpdatePageBar(QColor(251, 248, 249));
		BFSkinManager::SetUpdatePageContext(QColor(255, 254, 255));
		BFSkinManager::SetUpdatePageConfirmBtnText(QColor(255, 255, 255));
		BFSkinManager::SetUpdatePageCancelBtnText(QColor(102, 102, 102));
		BFSkinManager::SetUpdatePageConfirmBtnBack(QColor(23, 142, 240));
		BFSkinManager::SetUpdatePageCancelBtnBack(QColor(242, 242, 242));
		BFSkinManager::SetUpdatePageVerInfoBorder(QColor(216, 216, 216));
		BFSkinManager::SetUpdatePageVerInfoText(QColor(102, 102, 102, 255));
		BFSkinManager::SetUpdatePageVerInfoBack(QColor(249, 249, 249));


		//Cmain边框
		BFSkinManager::SetMainBorderColor(QColor(242, 242, 242, 255));


		//大部分弹窗样式
		BFSkinManager::SetDialogTitleBar(QColor(251, 248, 249));
		BFSkinManager::SetDialogContext(QColor(255, 254, 255));

		//右侧视图选中颜色
		BFSkinManager::SetPicViewSelectColor(QColor(27, 144, 251, 50));
		BFSkinManager::SetPicViewTextNameColor(QColor(0, 0, 0, 255));
		BFSkinManager::SetPicViewTextOtherColor(QColor(0, 0, 0, 255));
		BFSkinManager::SetPicViewDirPicFrontColor(QColor(27, 144, 251, 255));
		BFSkinManager::SetPicViewDirPicBehindColor(QColor(27, 144, 251, 255 * 0.65));


		//花瓣导入
		BFSkinManager::SetHuaBanTitleTextColor(QColor(26,26, 26, 255));
		BFSkinManager::SetHuaBanTipsLabTextColor(QColor(102, 102, 102, 255));
		BFSkinManager::SetHuaBanTipsLabTextColor_type_0(QColor(153, 153, 153, 255));
		BFSkinManager::SetHuaBanInputTextColor(QColor(204, 204, 204, 255));
		BFSkinManager::SetHuaBanWrongTipsTextColor(QColor(255, 0, 0, 255));
		BFSkinManager::SetHuaBanInputBackGroundColor(QColor(255, 255, 255, 255));
		BFSkinManager::SetHuaBanInputBorderColor(QColor(216, 216, 216, 255));
		BFSkinManager::SetHuaBanCountTipTextColor(QColor(153, 153, 153, 255));
		BFSkinManager::SetHuaBanInputCountWinTextColor(QColor(102, 102, 102, 255));
		BFSkinManager::SetHuaBanInputCountWinBackColor(QColor(242, 242, 242, 255));


		//用户中心设置
		BFSkinManager::SetSettingCenterBtnsWidColor(QColor(242, 242, 242, 255));
		BFSkinManager::SetSettingCenterBtnCheckColor(QColor(255, 255, 255, 255));
		BFSkinManager::SetSettingCenterBtnUnCheckColor(QColor(242, 242, 242, 255));
		BFSkinManager::SetSettingCenterPageColor(QColor(255, 255, 255, 255));
		BFSkinManager::SetSettingCenterCloseBtnColor(QColor(242, 242, 242, 255));
		BFSkinManager::SetSettingCenterSaveBtnColor(QColor(32, 124, 255, 255));
		BFSkinManager::SetSettingCenterEditBackColor(QColor(255, 255, 255, 255));
		BFSkinManager::SetSettingCenterEditBorderColor(QColor(217, 217, 217, 255*0.2));
		QVector<QColor>need_setting_center_text_color = { QColor(153,153,153,255),QColor(102, 102, 102, 255),QColor(26, 26, 26, 255),QColor(255, 255, 255, 255 * 1) };
		BFSkinManager::SetSettingCenterTextColor(need_setting_center_text_color);
	}
}




void BFSkinManager::SetHuaBanTitleTextColor(const QColor& c)
{
	huaban_title_text_color = c;
}

void BFSkinManager::SetHuaBanTipsLabTextColor(const QColor& c)
{
	huaban_tips_lab_text_color = c;
}

void BFSkinManager::SetHuaBanTipsLabTextColor_type_0(const QColor& c)
{
	huaban_tips_lab_text_color_type_0 = c;
}

void BFSkinManager::SetHuaBanInputTextColor(const QColor& c)
{
	huaban_input_text_color = c;
}

void BFSkinManager::SetHuaBanWrongTipsTextColor(const QColor& c)
{
	huaban_wrong_tips_text_color = c;
}

void BFSkinManager::SetHuaBanInputBackGroundColor(const QColor& c)
{
	huaban_input_background_color = c;
}

void BFSkinManager::SetHuaBanInputBorderColor(const QColor& c)
{
	huaban_input_border_color = c;
}

QColor& BFSkinManager::GetHuaBanTitleTextColor()
{
	return huaban_title_text_color;
} 

QColor& BFSkinManager::GetHuaBanTipsLabTextColor()
{
	return huaban_tips_lab_text_color;
}

QColor& BFSkinManager::GetHuaBanTipsLabTextColor_type_0()
{
	return huaban_tips_lab_text_color_type_0;
}

QColor& BFSkinManager::GetHuaBanInputTextColor()
{
	return huaban_input_text_color;
}

QColor& BFSkinManager::GetHuaBanWrongTipsTextColor()
{
	return huaban_wrong_tips_text_color;
}

QColor& BFSkinManager::GetHuaBanInputBackGroundColor()
{
	return huaban_input_background_color;
}

QColor& BFSkinManager::GetHuaBanInputBorderColor()
{
	return huaban_input_border_color;
}

QColor& BFSkinManager::GetHuaBanCountTipTextColor()
{
	return huaban_count_tips_text_color;
}

void BFSkinManager::SetHuaBanCountTipTextColor(const QColor& c)
{
	huaban_count_tips_text_color = c;
}

QColor& BFSkinManager::GetHuaBanInputCountWinTextColor()
{
	return huaban_count_tips_win_text_color;
}

void BFSkinManager::SetHuaBanInputCountWinTextColor(const QColor& c)
{
	huaban_count_tips_win_text_color = c;
}

QColor& BFSkinManager::GetHuaBanInputCountWinBackColor()
{
	return huaban_count_tips_win_back_color;
}

void BFSkinManager::SetHuaBanInputCountWinBackColor(const QColor& c)
{
	huaban_count_tips_win_back_color = c;
}

int g_SkinStyle = 0;


void BFSkinManager::SetPicViewSelectColor(const QColor& c)
{
	pic_view_select_color = c;
}

void BFSkinManager::SetPicViewTextNameColor(const QColor& c)
{
	pic_view_text_name_color = c;
}

void BFSkinManager::SetPicViewTextOtherColor(const QColor& c)
{
	pic_view_text_other_color = c;
}

void BFSkinManager::SetPicViewDirPicFrontColor(const QColor& c)
{
	pic_view_dir_pic_front_color = c;
}

void BFSkinManager::SetPicViewDirPicBehindColor(const QColor& c)
{
	pic_view_dir_pic_behind_color = c;
}

QColor& BFSkinManager::GetPicViewSelectColor()
{
	return pic_view_select_color;
}

QColor& BFSkinManager::GetPicViewTextNameColor()
{
	return pic_view_text_name_color;
}

QColor& BFSkinManager::GetPicViewTextOtherColor()
{
	return pic_view_text_other_color;
}



QColor& BFSkinManager::GetPicViewDirPicFrontColor()
{
	return pic_view_dir_pic_front_color;
}

QColor& BFSkinManager::GetPicViewDirPicBehindColor()
{
	return pic_view_dir_pic_behind_color;
}

BFSkinManager::BFSkinManager()
{

}

BFSkinManager::~BFSkinManager()
{

}

void BFSkinManager::SetBackGroundColor(const QColor& c)
{
	backGroundColor = c;
}

void BFSkinManager::SetBorderLineColor(const QColor& c)
{
	borderLineColor = c;
}

void BFSkinManager::SetBarColor(const QColor& c)
{
	barColor = c;
}

void BFSkinManager::SetOtherBKColor(const QColor& c)
{
	otherBkBarColor = c;
}

void BFSkinManager::SetFontColor(const QColor& c)
{
	fontColor = c;
}

void BFSkinManager::SetStatusColor(const QColor& c)
{
	statusColor = c;
}

void BFSkinManager::SetButtonColor(const QColor&c )
{
	buttonColor = c;
}

//void BFSkinManager::SetBackGroundBarColor(const QColor& c)
//{
//	bkBarColor = c;
//}

void BFSkinManager::SetBKBarColor(const QColor& c)
{
	bkBarColor = c;
}

void BFSkinManager::SetButtonLineColor(const QColor&c)
{
	buttonLineColor = c;
}

void BFSkinManager::SetButtonLineColor1(const QColor&c)
{
	buttonLineColor1 = c;
}

void BFSkinManager::SetMenuHoverColor(const QColor&c)
{
	menuHoverColor = c;
}

void BFSkinManager::SetIconBackColor(const QColor&c)
{
	color_icon_back = c;
}

void BFSkinManager::SetCompleteColor(const QColor&c)
{
	complete_color = c;
}

void BFSkinManager::SetTextColor(int skin)
{
	if ( skin == 1 ) {	// 黑色皮肤
		TextColor[0] = QColor(255, 255, 255, 217);
		TextColor[1] = QColor(255, 255, 255, 166);
		TextColor[2] = QColor(255, 255, 255, 115);
		TextColor[3] = QColor(255, 255, 255, 77);
	}
	else {		// 白色皮肤
		TextColor[0] = QColor("#1A1A1A");
		TextColor[1] = QColor("#3F3F3F");
		TextColor[2] = QColor("#666666");
		TextColor[3] = QColor("#999999");
	}
}

QColor & BFSkinManager::GetBackGroundColor()
{
	return backGroundColor;
}

QColor & BFSkinManager::GetBorderLineColor()
{
	return borderLineColor;
}

QColor & BFSkinManager::GetBarColor()
{
	return barColor;
}

QColor & BFSkinManager::GetFontColor()
{
	return fontColor;
}

QColor & BFSkinManager::GetStatusColor()
{
	return statusColor;
}

QColor & BFSkinManager::GetBKBarColor()
{
	return bkBarColor;
}

QColor & BFSkinManager::GetButtonColor()
{
	return buttonColor;
}

QColor & BFSkinManager::GetOtherBKColor()
{
	return otherBkBarColor;
}

QColor & BFSkinManager::GetButtonLineColor()
{
	return buttonLineColor;
}

QColor & BFSkinManager::GetButtonLineColor1()
{
	return buttonLineColor1;
}

QColor & BFSkinManager::GetMenuHoverColor()
{
	return menuHoverColor;
}

QColor & BFSkinManager::GetIconBackColor()
{
	return color_icon_back;
}

QString& BFSkinManager::GetResourceName(QString resourceName)
{
	static QString path;

	#ifdef _WIN32
	QString SkinPath = QString("");
	#else
	QString SkinPath = QString("/../");
	#endif
	
	if (g_SkinStyle == 0)
	{
		static QString url = QString("image:url(") + QCoreApplication::applicationDirPath() + SkinPath +  QString("/Resources/");
		path = url + resourceName + QString(");}");
	}
	else {
		static QString url = QString("image:url(") + QCoreApplication::applicationDirPath() + SkinPath + QString("/Resources/Resource_black/");
		path = url + resourceName + QString(");}");
	}

	return path;
}

QString& BFSkinManager::GetResourceNameFromBorderImage(QString resourceName)
{

	static QString path;
	#ifdef _WIN32
	QString SkinPath = QString("");
	#else
	QString SkinPath = QString("/../");
	#endif
	
	if (g_SkinStyle == 0) {
		static QString url = QString("border-image:url(") + QCoreApplication::applicationDirPath() + SkinPath + QString("/Resources/");
		path = url + resourceName + QString(");}");
	}
	else {
		static QString url = QString("border-image:url(") + QCoreApplication::applicationDirPath() + SkinPath + QString("/Resources/Resource_black/");
		path = url + resourceName + QString(");}");
	}

	return path;
}



QColor & BFSkinManager::GetCompleteColor()
{
	return complete_color;
}

QColor & BFSkinManager::GetTextColor(int index)
{
	return BFSkinManager::TextColor[index];
}


QString BFSkinGet(const char* lpszFileName)
{
	static QString strResourceDirectory;
	if (strResourceDirectory.isEmpty()) {

    #ifdef _WIN32
            if (g_SkinStyle == 0)
            {
                strResourceDirectory = QCoreApplication::applicationDirPath() + "/Resources/";
            }
            else {
                strResourceDirectory = QCoreApplication::applicationDirPath() + "/Resources/Resource_black/";

            }
    #else
            if (g_SkinStyle == 0)
                {
                    strResourceDirectory = QCoreApplication::applicationDirPath() + "/../Resources/";
                }
                else {
                    strResourceDirectory = QCoreApplication::applicationDirPath() + "/../Resources/Resource_black/";

                }
    #endif
	}
	return QString(strResourceDirectory + lpszFileName);
}

bool BFSkinGet(const char* lpszFileName, QImage& image)
{
	return true;
}

void BFSetButtonColor(const QColor& c)
{
	BFSkinManager::SetButtonColor(c);
}

void BFSetBackGroundColor(const QColor& c)
{
	BFSkinManager::SetBackGroundColor(c);
}

void BFSetBorderLineColor(const QColor& c)
{
	BFSkinManager::SetBorderLineColor(c);
}

void BFSetBarColor(const QColor& c)
{
	BFSkinManager::SetBarColor(c);
}

void BFSetBackGroundBarColor(const QColor& c)
{
	BFSkinManager::SetBKBarColor(c);
}

void BFSetFontColor(const QColor& c)
{
	BFSkinManager::SetFontColor(c);
}

void BFSetStausColor(const QColor& c)
{
	BFSkinManager::SetStatusColor(c);
}

void BFSetTextColor(int skin)
{
	BFSkinManager::SetTextColor(skin);
}

void BFSetButtonLineColor(const QColor& c)
{
	BFSkinManager::SetButtonLineColor(c);
}

void BFSetButtonLineColor1(const QColor& c)
{
	BFSkinManager::SetButtonLineColor1(c);
}

void BFSetMenuHoverColor(const QColor & c)
{
	BFSkinManager::SetMenuHoverColor(c);
}

void BFSetOtherBKBarColor(const QColor& c)
{
	BFSkinManager::SetOtherBKColor(c);
}

void BFSetIconBackColor(const QColor& c)
{
	BFSkinManager::SetIconBackColor(c);
}

void BFSetCompleteColor(const QColor& c)
{
	BFSkinManager::SetCompleteColor(c);
}

//QColor& BFBackGroundColorGet()
//{
//	return BFSkinManager::GetBackGroundColor();
//}
//
//QColor& BFBorderLineColorGet()
//{
//	return BFSkinManager::GetBorderLineColor();
//}
//
//QColor& BFGetBarColor()
//{
//	return BFSkinManager::GetBarColor();
//}
//
//QColor& BFFontColorGet()
//{
//	return BFSkinManager::GetFontColor();
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//更新页面/////////////////////////////////
void BFSkinManager::SetUpdatePageBar(const QColor& c)
{
	update_page_bar = c;
}
void BFSkinManager::SetUpdatePageContext(const QColor& c)
{
	update_page_context = c;
}
void BFSkinManager::SetUpdatePageConfirmBtnText(const QColor& c)
{
	update_page_confirm_btn_text = c;
}
void BFSkinManager::SetUpdatePageCancelBtnText(const QColor& c)
{
	update_page_cancel_btn_text = c;
}
void BFSkinManager::SetUpdatePageConfirmBtnBack(const QColor& c)
{
	update_page_confirm_btn_back = c;
}
void BFSkinManager::SetUpdatePageCancelBtnBack(const QColor& c)
{
	update_page_cancel_btn_back = c;
}
void BFSkinManager::SetUpdatePageVerInfoBorder(const QColor& c)
{
	update_page_verinfo_border = c;
}
void BFSkinManager::SetUpdatePageVerInfoText(const QColor& c)
{
	update_page_verinfo_text = c;
}
void BFSkinManager::SetUpdatePageVerInfoBack(const QColor& c)
{
	update_page_verinfo_back = c;
}
 QColor& BFSkinManager::GetUpdatePageBar()
{
	return update_page_bar;
}
 QColor& BFSkinManager::GetUpdatePageContext()
{
	 return update_page_context;
}
 QColor& BFSkinManager::GetUpdatePageConfirmBtnText()
{
	 return update_page_confirm_btn_text;
}
 QColor& BFSkinManager::GetUpdatePageCancelBtnText()
{
	 return update_page_cancel_btn_text;
}
 QColor& BFSkinManager::GetUpdatePageConfirmBtnBack()
{
	 return update_page_confirm_btn_back;
}
 QColor& BFSkinManager::GetUpdatePageCancelBtnBack()
{
	 return update_page_cancel_btn_back;
}
 QColor& BFSkinManager::GetUpdatePageVerInfoBorder()
{
	 return update_page_verinfo_border;
}
 QColor& BFSkinManager::GetUpdatePageVerInfoText()
{
	 return update_page_verinfo_text;
}
 QColor& BFSkinManager::GetUpdatePageVerInfoBack()
{
	 return update_page_verinfo_back;
}


 //大部分弹窗样式
 void BFSkinManager::SetDialogTitleBar(const QColor& c)
 {
	 dialog_title_bar_color = c;
 }
 void BFSkinManager::SetDialogContext(const QColor& c)
 {
	 dialog_context_color = c;
 }


 QColor& BFSkinManager::GetDialogTitleBar()
 {
	 return dialog_title_bar_color;
 }
 QColor& BFSkinManager::GetDialogContext()
 {
	 return dialog_context_color;
 }

