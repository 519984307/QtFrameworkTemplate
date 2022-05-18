
#ifndef __BFSKINMANAGER_INCLUDED__
#define __BFSKINMANAGER_INCLUDED__

#include <QString>
#include <QColor>
#include <QImage>

extern int g_SkinStyle;

#define BFBorderLineColorGet()  BFSkinManager::GetBorderLineColor()
#define BFBackGroundColorGet()  BFSkinManager::GetBackGroundColor()	 // 背景
#define BFGetBarColor()		    BFSkinManager::GetBarColor()		 // 背景1
#define BFGetBKBarColor()	    BFSkinManager::GetBKBarColor()		 // 背景2
#define BFFontColorGet()	    BFSkinManager::GetFontColor()
#define BFTextColorGet(i)	    BFSkinManager::GetTextColor(i)
#define BFGetStatusColor()	    BFSkinManager::GetStatusColor()
#define BFGetResourcePath(x)    QString(BFSkinManager::GetResourceName(x))
#define BFGetBorderImagePath(x) QString(BFSkinManager::GetResourceNameFromBorderImage(x))
#define BFGetButtonColor()		BFSkinManager::GetButtonColor()
#define BFGetButtonLineColor()  BFSkinManager::GetButtonLineColor()
#define BFGetButtonLineColor1() BFSkinManager::GetButtonLineColor1()
#define BFGetMenuHoverColor()   BFSkinManager::GetMenuHoverColor()
#define BFGetOtherBKColor()     BFSkinManager::GetOtherBKColor()     //弹窗标题栏
#define BFGetIconBackColor()    BFSkinManager::GetIconBackColor()
#define BFGetCompleteColor()    BFSkinManager::GetCompleteColor()

#define BFGetSkinTyle()			g_SkinStyle


class BFSkinManager
{
public:
	BFSkinManager();
	~BFSkinManager();

	static void SetBackGroundColor(const QColor& c);
	static void SetBarColor(const QColor& c);
	static void SetBKBarColor(const QColor& c);
	static void SetOtherBKColor(const QColor& c);

	static void SetBorderLineColor(const QColor& c);
	static void SetFontColor(const QColor& c);
	static void SetStatusColor(const QColor& c);
	//static void SetBackGroundBarColor(const QColor& c);
	static void SetTextColor(int skin);
	static void SetButtonColor(const QColor&c);
	static void SetButtonLineColor(const QColor&c);
	static void SetButtonLineColor1(const QColor&c);
	static void SetMenuHoverColor(const QColor&c);
	static void SetIconBackColor(const QColor&c);          //icon底色
	static void SetCompleteColor(const QColor&c);


	static QColor & GetBackGroundColor();	
	static QColor & GetBorderLineColor();	
	static QColor & GetBarColor();
	static QColor & GetFontColor();
	static QColor & GetStatusColor();
	static QColor & GetBKBarColor();
	static QColor & GetButtonColor();
	static QColor & GetOtherBKColor();
	static QColor & GetTextColor(int);       //文字颜色
	static QColor & GetButtonLineColor();
	static QColor & GetButtonLineColor1();
	static QColor & GetMenuHoverColor();
	static QColor & GetIconBackColor();     //icon底色
	static QColor & GetCompleteColor();



	static QString & GetResourceName(QString resourceName);
	static QString & GetResourceNameFromBorderImage(QString resourceName);



private:
	static QColor backGroundColor;          // 背景颜色     
	static QColor borderLineColor;          // 边框颜色
	static QColor barColor;
	static QColor backGroundBarColor;
	static QColor fontColor;
	static QColor statusColor;
	static QColor bkBarColor;
	static QColor buttonColor;
	static QColor buttonLineColor;
	static QColor buttonLineColor1;
	static QColor menuHoverColor;
	static QColor otherBkBarColor;

	static QColor color_icon_back;             //ICON背景色
// Text Color
	static QColor TextColor[4];

	static QColor complete_color;              //下拉菜单背景颜色



//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓主视图参数
public:
	static void SetMainBorderColor(const QColor& c);


	static QColor & GetMainBorderColor();

private:
	static QColor main_bord_color;              //大窗口边框颜色

//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

//↓↓↓↓↓↓↓↓↓↓↓↓↓↓软件更新页面用颜色
public:
	static void SetUpdatePageBar(const QColor& c);
	static void SetUpdatePageContext(const QColor& c);
	static void SetUpdatePageConfirmBtnText(const QColor& c);
	static void SetUpdatePageCancelBtnText(const QColor& c);
	static void SetUpdatePageConfirmBtnBack(const QColor& c);
	static void SetUpdatePageCancelBtnBack(const QColor& c);
	static void SetUpdatePageVerInfoBorder(const QColor& c);
	static void SetUpdatePageVerInfoText(const QColor& c);
	static void SetUpdatePageVerInfoBack(const QColor& c);

	static QColor& GetUpdatePageBar();
	static QColor& GetUpdatePageContext();
	static QColor& GetUpdatePageConfirmBtnText();
	static QColor& GetUpdatePageCancelBtnText();
	static QColor& GetUpdatePageConfirmBtnBack();
	static QColor& GetUpdatePageCancelBtnBack();
	static QColor& GetUpdatePageVerInfoBorder();
	static QColor& GetUpdatePageVerInfoText();
	static QColor& GetUpdatePageVerInfoBack();

private:
	static QColor update_page_bar;                   //标题栏颜色
	static QColor update_page_context;               //页内容颜色
	static QColor update_page_confirm_btn_text;      //确认向按钮文字颜色
	static QColor update_page_cancel_btn_text;       //取消向按钮文字颜色
	static QColor update_page_confirm_btn_back;      //确认向按钮背景颜色
	static QColor update_page_cancel_btn_back;       //取消向按钮背景颜色
	static QColor update_page_verinfo_border;        //版本信息边框
	static QColor update_page_verinfo_text;          //版本信息文字颜色
	static QColor update_page_verinfo_back;          //版本信息背景
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑软件更新页面用颜色




//↓↓↓↓↓↓↓↓↓↓↓↓↓↓软件弹窗popup颜色样式
public:
	static void SetDialogTitleBar(const QColor& c);
	static void SetDialogContext(const QColor& c);

	static QColor& GetDialogTitleBar();
	static QColor& GetDialogContext();

private:
	static QColor dialog_title_bar_color;
	static QColor dialog_context_color;
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑软件弹窗颜色样式



//↓↓↓↓↓↓↓↓↓↓↓↓↓↓主视图窗口
public:
	static void SetPicViewSelectColor(const QColor& c);
	static void SetPicViewTextNameColor(const QColor& c);
	static void SetPicViewTextOtherColor(const QColor& c);
	static void SetPicViewDirPicFrontColor(const QColor& c);
	static void SetPicViewDirPicBehindColor(const QColor& c);


	static QColor& GetPicViewSelectColor();
	static QColor& GetPicViewTextNameColor();
	static QColor& GetPicViewTextOtherColor();
	static QColor& GetPicViewDirPicFrontColor();
	static QColor& GetPicViewDirPicBehindColor();

private:
	static QColor pic_view_select_color;         //视图选中颜色
	static QColor pic_view_text_name_color;      //视图名字文字颜色
	static QColor pic_view_text_other_color;     //视图其他信息颜色

	static QColor pic_view_dir_pic_front_color;  //视图文件夹图片前景色
	static QColor pic_view_dir_pic_behind_color; //视图文件夹图片后景色
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑主视图窗口



//↓↓↓↓↓↓↓↓↓↓↓↓↓花瓣导入特殊样式
public:
	static void SetHuaBanTitleTextColor(const QColor& c);
	static void SetHuaBanTipsLabTextColor(const QColor& c);
	static void SetHuaBanTipsLabTextColor_type_0(const QColor& c);
	static void SetHuaBanInputTextColor(const QColor& c);
	static void SetHuaBanWrongTipsTextColor(const QColor& c);
	static void SetHuaBanInputBackGroundColor(const QColor& c);
	static void SetHuaBanInputBorderColor(const QColor& c);
	static void SetHuaBanCountTipTextColor(const QColor& c);
	static void SetHuaBanInputCountWinTextColor(const QColor& c);
	static void SetHuaBanInputCountWinBackColor(const QColor& c);


	static QColor& GetHuaBanTitleTextColor();
	static QColor& GetHuaBanTipsLabTextColor();
	static QColor& GetHuaBanTipsLabTextColor_type_0();
	static QColor& GetHuaBanInputTextColor();
	static QColor& GetHuaBanWrongTipsTextColor();
	static QColor& GetHuaBanInputBackGroundColor();
	static QColor& GetHuaBanInputBorderColor();
	static QColor& GetHuaBanCountTipTextColor();
	static QColor& GetHuaBanInputCountWinTextColor();
	static QColor& GetHuaBanInputCountWinBackColor();

private:
	static QColor huaban_title_text_color;            //内部标题文字颜色
	static QColor huaban_tips_lab_text_color;         //lab提示文字颜色
	static QColor huaban_tips_lab_text_color_type_0;  //lab类型1提示文字颜色
	static QColor huaban_input_text_color;            //输入框文字颜色
	static QColor huaban_wrong_tips_text_color;       //错误提示框文字颜色
	static QColor huaban_input_background_color;      //花瓣导入背景颜色
	static QColor huaban_input_border_color;          //边框颜色

	static QColor huaban_count_tips_text_color;        //花瓣数量提示文字
	static QColor huaban_count_tips_win_text_color;    //花瓣数量弹窗文字
	static QColor huaban_count_tips_win_back_color;    //花瓣数量弹窗背景颜色

//↑↑↑↑↑↑↑↑↑↑↑↑↑↑花瓣导入特殊样式


//↓↓↓↓↓↓↓↓↓↓↓↓↓用户配置中心
public:
	static void SetSettingCenterBtnsWidColor(const QColor& c);
	static void SetSettingCenterBtnCheckColor(const QColor& c);
	static void SetSettingCenterBtnUnCheckColor(const QColor& c);
	static void SetSettingCenterPageColor(const QColor& c);
	static void SetSettingCenterCloseBtnColor(const QColor& c);
	static void SetSettingCenterSaveBtnColor(const QColor& c);
	static void SetSettingCenterEditBackColor(const QColor& c);
	static void SetSettingCenterEditBorderColor(const QColor& c);

	static void SetSettingCenterTextColor(QVector<QColor>setting_center_text_color);


	static QColor& GetSettingCenterBtnsWidColor();
	static QColor& GetSettingCenterBtnCheckColor();
	static QColor& GetSettingCenterBtnUnCheckColor();
	static QColor& GetSettingCenterPageColor();
	static QColor& GetSettingCenterCloseBtnColor();
	static QColor& GetSettingCenterSaveBtnColor();
	static QColor& GetSettingCenterEditBackColor();
	static QColor& GetSettingCenterEditBorderColor();
	static QColor GetSettingCenterTextColor(int index);


private:
	static QColor setting_center_btns_wid_color;     //用户中心左侧按钮wid底色
	static QColor setting_center_btn_check_color;    //用户中心左侧按钮选中底色
	static QColor setting_center_btn_uncheck_color;  //用户中心左侧按钮未选中底色
	static QColor setting_center_page_color;         //用户中心右侧内容底色
	static QColor setting_center_close_btn_color;    //用户中心关闭按钮
	static QColor setting_center_save_btn_color;     //用户中心保存按钮

	static QColor setting_center_edit_back_color;    //用户中心输入框背景颜色
	static QColor setting_center_edit_border_color;    //用户中心输入框边框颜色

	//透明度分别为0.45  0.65  0.85 1
	static QVector<QColor>setting_center_text_color;      //用户中心字体颜色




//↑↑↑↑↑↑↑↑↑↑↑↑↑↑用户配置中心

};

void initSkin(int style);
QString BFSkinGet(const char* lpszFileName);
bool BFSkinGet(const char* lpszFileName, QImage& image);

void BFSetBackGroundColor( const QColor& c );
void BFSetBorderLineColor( const QColor& c );
void BFSetBarColor(const QColor& c);
void BFSetBackGroundBarColor(const QColor& c);
void BFSetFontColor(const QColor& c);
void BFSetStausColor(const QColor& c);
void BFSetTextColor(int skin);
void BFSetButtonColor(const QColor& c);
void BFSetButtonLineColor(const QColor& c);
void BFSetButtonLineColor1(const QColor& c);
void BFSetMenuHoverColor(const QColor& c);
void BFSetOtherBKBarColor(const QColor& c);
void BFSetIconBackColor(const QColor& c);
void BFSetCompleteColor(const QColor& c);
//QColor& BFFontColorGet();
//QColor& BFBackGroundColorGet();
//QColor& BFBorderLineColorGet();
//QColor& BFGetBarColor();

extern BFSkinManager BFSkinMgr;
#endif//__BFSKINMANAGER_INCLUDED__