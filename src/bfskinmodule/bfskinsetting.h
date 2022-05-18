/*
BillFish_2.0皮肤管理(颜色+图片)
*/
#pragma once
#include <QObject>
#include <QColor>
#include <QPixmap>
#include <QMap>

static const QString kHuaBanImportRuleObjectName = "HuaBanImportRuleObjectName";
static const QString kImportHistoryObjectName = "importHistory";
static const QString kHuaBanImportObjectName = "HuaBanImportObjectName";
static const QString kAboutObjectName = "about";
static const QString kCreateSuccessObjectName = "CreateSuccessDialog";
static const QString kFeedbackObjectName = "feedback";
static const QString kPreferencesWindow = "PreferencesWindow";
static const QString kMainWidget = "MainWidget";
static const QString kImportMethodDialog = "ImportMethodDialog";
static const QString kCreateLibraryDialog = "CreateLibraryDialog";
static const QString kNetBatchCollect = "NetBatchCollect";
static const QString kNetSingleCollect = "NetSingleCollect";
static const QString kHuaBanSelectedFolderObjectName =
    "HuaBanSelectedFolderObjectName";

//宏1:获取带有image:资源路径
#define GetSkinResource(path) \
  BFSkinSetting::GetInstance()->GetResourcePath(path);

//宏2:获取资源相对路径(运行目录下)
#define GetSkinResourceAbsolutePath(path) \
  BFSkinSetting::GetInstance()->GetResourceAbsolutePath(path);

//宏3:获取带有border-image:资源路径
#define GetSkinResourceBorderImage(path) \
  BFSkinSetting::GetInstance()->GetResourcePathBorderImage(path);

//软件通用箭头大小
#define SoftWareArrowIconWidth   8
#define SoftWareArrowIconHeight  7


//皮肤类型
enum SkinType
{
	BlackMode,
	WhiteMode
};

#if defined BUILD_SKIN_LIB
    #define TEST_LIB_EXPORT Q_DECL_EXPORT
#else
    #define TEST_LIB_EXPORT Q_DECL_IMPORT
#endif

class TEST_LIB_EXPORT BFSkinSetting{
public:
	static BFSkinSetting*GetInstance();
	static void Delete();

	//切换皮肤,相应的所有控件的皮肤和颜色需要切换
	void SwitchSkinMode(SkinType);

	//将资源文件拼接成样式表,放入样式表中
	QString GetResourcePath(QString file_name);

	//将资源文件以border-image拼接成样式表
	QString GetResourcePathBorderImage(QString file_name);

	//获取资源绝对路径
	QString  GetResourceAbsolutePath(QString file_name);

	//获取文字的family
    QString GetFontFamily();

    //获取彩色的文件夹图标
    /*
     灰色       0
     蓝色       1
     绿色       2
     青色       3
     橘色       4
     黄色       5
     红色       6
     粉色       7
     紫色       8
     */
    QPixmap GetFolderImgWithColor(qint32 color);


	//获取文件夹对应颜色QColor
	QColor GetFolderColor(qint32 color_index);


    //加载json-config文件加载内存
    void LoadConfig();
    //加载颜色配置文件夹整体qss
    void LoadQss();

    qreal GetDpi();
    void SetDpi(qreal dpi);

    QPixmap GetSvgPixmapWithName(const QString& svg_resource_name);

   private:
    BFSkinSetting();
    ~BFSkinSetting();
    BFSkinSetting& operator=(BFSkinSetting&) = delete;
    BFSkinSetting(BFSkinSetting&) = delete;

    // QString(num0,num1,num2,num3)形式转成QColor
    QColor StrIntoQColor(QString);
    void LoadFloderSvg();


public:
	void  SetSkinColor(SkinType);                     //设置皮肤颜色
    void  SetFontFamilyStr();
	void  SetAlphaValue(int);                         //设置alpha数值
	static BFSkinSetting*                             m_skin_setting;
	SkinType                                          m_cur_skin_type;
	quint8                                            m_a_value;        //颜色的阿尔法数值

//↓↓↓↓↓↓↓↓↓↓↓↓↓文件夹不同颜色图标↓↓↓↓↓↓↓↓↓↓↓↓↓
    QPixmap m_grey_folder;
    QPixmap m_blue_folder;
    QPixmap m_green_folder;
    QPixmap m_cyan_folder;
    QPixmap m_orange_folder;
    QPixmap m_yellow_folder;
    QPixmap m_red_folder;
    QPixmap m_pink_folder;
    QPixmap m_purple_folder;
//↓↓↓↓↓↓↓↓↓↓↓↓↓软件通用颜色↓↓↓↓↓↓↓↓↓↓↓↓↓
	QColor main_color;                               //主色
	QColor green_color;                              //辅色-绿色
	QColor orange_color;                             //辅色-橙色
	QColor yellow_color;                             //辅色-黄色
	QColor common_first_color;                       //通用-重要
	QColor common_second_color;                      //通用-次要
	QColor common_third_color;                       //通用-再次
	QColor common_input_color;                       //通用-输入
	QColor common_mode_light_color;                  //模块-浅色
	QColor common_mode_dark_color;                   //模块-深色
	QColor stroke_popup_color;                       //弹窗描边
	QColor input_and_button_color;                   //输入框及默认按钮
	QColor other_button_color;                       //其他按钮颜色
	QColor split_color;                              //分割线颜色
	QColor scroll_bar_color;                         //滚动条
	QColor options_color;                            //选择项颜色
	QColor mask_default_color;                       //遮罩默认颜色
	QColor mask_focus_color;                         //遮罩聚焦颜色

	QColor GetMainColor();            
	QColor GetGreenColor();
	QColor GetOrangeColor();
	QColor GetYellowColor();
	QColor GetCommonFirstColor();
	QColor GetCommonSecondColor();
	QColor GetCommonThridColor();
	QColor GetCommonInputColor();
	QColor GetCommonModeLightColor();
	QColor GetCommonModeDarkColor();
	QColor GetStrokePopupColor();
	QColor GetInputAndButtonColor();
	QColor GetOtherButtonColor();
	QColor GetSplitColor();
	QColor GetScrollBarColor();
	QColor GetOptinsColor();
	QColor GetMaskDefaultColor();
	QColor GetMaskFocusColor();

	void SetMainColor(QColor);
	void SetGreenColor(QColor);
	void SetOrangeColor(QColor);
	void SetYellowColor(QColor);
	void SetCommonFirstColor(QColor);
	void SetCommonSecondColor(QColor);
	void SetCommonThridColor(QColor);
	void SetCommonInputColor(QColor);
	void SetCommonModeLightColor(QColor);
	void SetCommonModeDarkColor(QColor);
	void SetStrokePopupColor(QColor);
	void SetInputAndButtonColor(QColor);
	void SetOtherButtonColor(QColor);
	void SetSplitColor(QColor);
	void SetScrollBarColor(QColor);
	void SetOptinsColor(QColor);
	void SetMaskDefaultColor(QColor);
	void SetMaskFocusColor(QColor);

//↓↓↓↓↓↓↓↓↓↓↓↓↓字体
	//容器index-各个皮肤的字体必须一一对应
	QVector<QColor> text_color_vec;            //用户中心字体颜色
	//index0:通用-重要
	//index1:通用-次要
	//index2:通用-再次
	//index3:通用-输入

	void SetTextColor(QVector<QColor>text_color);
	//index:字体的级别
	QColor GetTextColor(int index);

//↓↓↓↓↓↓↓↓↓↓↓↓↓左侧
//模块0:左侧通用色
	QColor left_win_backgounrd_color;                  //左侧背景颜色
	void   SetLeftWinBackgroundColor(QColor);    //Set左侧背景颜色
	QColor GetLeftWinBackgroundColor();            //Get左侧背景颜色


//模块1:左侧标题栏
//模块2:左侧资源导入栏
//模块3:左侧树
	QColor m_node_select_color;            //树选中颜色
	void SetNodeSelectColor(QColor);    //设置树节点选中颜色
	QColor GetNodeSelectColor();          //获取

	QColor m_tree_scroll_handle_color; 
	void SetTreeScrollHandleColor(QColor);
	QColor GetTreeScrollHandleColor();

	QColor m_tree_rename_back_color;
	void SetTreeRenameBackColor(QColor);
	QColor GetTreeRenameBackColor();


//模块4:左侧文件夹搜索

//↓↓↓↓↓↓↓↓↓↓↓↓↓中侧
//模块1:中侧通用色
	QColor mid_win_backgounrd_color;                  //中侧背景颜色
	void   SetMidWinBackgroundColor(QColor);    //Set中侧背景颜色
	QColor GetMidWinBackgroundColor();            //Get中侧背景颜色

//模块2：中侧导航栏
	QColor m_scroll_sliver_color;                    //中侧放大滚动条条子颜色
	QColor m_scroll_handle_color;                 //放大滚动条手柄颜色
	QColor m_nav_search_back_color;           //搜索背景颜色


	void SetNavScrollSliverColor(QColor);  
	void SetNavScrollHandleColor(QColor);
	void SetNavSearchBackColor(QColor);               //设置搜索背景颜色

	QColor GetNavScrollSliverColor();
	QColor GetNavScrollHandleColor();
	QColor GetNavSearchBackColor();


//模块3：中侧筛选色
	QColor condition_filter_color_select_color;          //颜色筛选模块
	void   SetConditionFilterColorSelectColor(QColor);  //Set背景颜色
	QColor GetConditionFilterColorSelectColor();        //Get右侧背景颜色

	QColor condition_filter_control_background_color;	//文本控件背景颜色
	void   SetConditionFilterControlBackGroundColor(QColor);  //Set背景颜色
	QColor GetConditionFilterControlBackGroundColor();        //Get右侧背景颜色

	QColor condition_filter_select_control_background_color;	//选择控件背景颜色
	void   SetConditionFilterSelectControlBackGroundColor(QColor color);  //Set背景颜色
	QColor GetConditionFilterSelectControlBackGroundColor();        //Get右侧背景颜色

	QColor condition_filter_combox_control_text_color;	//combox控件文字颜色
	void   SetConditionFilterComboxControlTextColor(QColor color);  //Set背景颜色
	QColor GetConditionFilterComboxControlTextColor();        //Get右侧背景颜色

	QColor condition_filter_listitem_hover_color;	//combox控件文字颜色
	void   SetConditionFilterListItemHoverColor(QColor color);  //Set背景颜色
	QColor GetConditionFilterListItemHoverColor();        //Get右侧背景颜色

	QColor condition_filter_item_select_back_color; //项选择背景色
	void  SetConditionFilterItemSelectBackColor(QColor color);
	QColor  GetConditionFilterItemSelectBackColor();

	QColor condition_filter_search_back_color;//筛选搜索栏背景色
    void SetConditionFilterSearchBackColor(QColor color);
    QColor GetConditionFilterSearchBackColor();


    QColor condition_filter_list_select_item_back_color;  //筛选下拉框list选择的项背景色
    void   SetConditionFilterListSelectItemBackColor(QColor color);
    QColor GetConditionFilterListSelectItemBackColor();


	QColor condition_filter_list_hover_item_back_color;  //筛选下拉框list悬浮项背景色
    void SetConditionFilterListHoverItemBackColor(QColor color);
    QColor GetConditionFilterListHoverItemBackColor();


  //模块4：中侧列表预览
  QColor  m_list_preview_folder_front_color;  //文件夹项无图片前景色
  void  SetListPreviewFolderFrontColor(QColor color);
  QColor  GetListPreviewFolderFrontColor();

  QColor m_list_preview_folder_behind_color; //文件夹项无图片后景色
  void  SetListPreviewFolderBehindColor(QColor color);
  QColor  GetListPreviewFolderBehindColor();

  QColor  m_list_format_back_color;  //格式背景颜色
  void SetListPreViewFormatBackColor(QColor);  //设置格式背景色
  QColor GetListPreViewFormatBackColor(); //得到格式背景色

  QColor  m_list_preview_scroll_handle_color;       //视图列表滚动条颜色
  void SetListPreViewScrollHandleColor(QColor); 
  QColor GetListPreViewScrollHandleColor();

  QColor  m_list_preview_scroll_handle_hover_color;       //视图列表滚动条颜色
  void SetListPreViewScrollHandleHoverColor(QColor c);
  QColor GetListPreViewScrollHandleHoverColor();


  QColor m_list_preview_rename_back_color;
  void SetListPreviewRenameBackColor(QColor);
  QColor GetListPreviewRenameBackColor();


//↓↓↓↓↓↓↓↓↓↓↓↓↓右侧
//模块1:右侧通用色
	QColor right_win_backgounrd_color;                        //右侧背景颜色
	void   SetRightWinBackgroundColor(QColor);          //Set右侧背景颜色
	QColor GetRightWinBackgroundColor();                  //Get右侧背景颜色

	QColor right_win_blue1;								//右侧 蓝色
	void   SetRightWinBlue1(QColor colro);					//Set右侧背景颜色
	QColor GetRightWinBlue1();							//Get右侧背景颜色

//模块2：右侧信息栏
	QColor m_right_info_export_btn_color;      //导出按钮颜色(导出全部素材 + 导出文件夹)
	void     SetRightInfoExportBtnColor(QColor);
	QColor GetRightInfoExportBtnColor();

	QColor	m_right_info_name_edit_back_color;		//右侧栏名称edit背景颜色
	void	SetRightNameEditBackColor(QColor);
	QColor	GetRightNameEditBackColor();

	QColor m_right_info_font_1;					//右侧栏字体1颜色，使用处：右侧栏名称控件字体
	void setRightFont1(QColor color);
	QColor GetRightFont1();

	QColor m_right_info_tag_font_color;				//右侧栏标签控件字体颜色
	void setRightTagFontColor(QColor color);
	QColor GetRightTagFontColor();

	QColor m_right_info_tag_cross_color;			//右侧栏标签控件叉号颜色
	void setRightTagCrossColor(QColor color);
	QColor GetRightTagCrossColor();

	QColor m_right_info_res_info_font_color;		//右侧栏素材信息字体颜色
	void setRightResInfoFontColor(QColor color);
	QColor GetRightResInfoFontColor();

//模块3:标签弹窗
	QColor m_tag_popup_tabStr_font_color;			//标签弹窗选项卡字体颜色
	void setTagPopupTabStrFontColor(QColor color);
	QColor GetTagPopupTabStrFontColor();

	QColor m_tag_popup_tab_back_unselected_color;	//标签弹窗选项卡未选中背景色
	void setTagPopupTabBackUnselectedColor(QColor color);
	QColor GetTagPopupTabBackUnselectedColor();

	QColor m_tag_popup_tab_back_selected_color;		//标签弹窗选项卡选中背景色
	void setTagPopupTabBackSelectedColor(QColor color);
	QColor GetTagPopupTabBackSelectedColor();

	QColor m_tag_popup_classify_font_color;			//标签弹窗分类首字母字体颜色
	void setTagPopupClassifyFontColor(QColor color);
	QColor GetTagPopupClassifyFontColor();

	QColor m_right_info_scroll_handle_color;				//标签弹窗滚动条颜色
	void setRightScrollHandleColor(QColor color);
	QColor GetRightScrollHandleColor();

	QColor m_tag_popup_create_tip;				//标签弹窗滚动条颜色
	void setTagPopupCreateTip(QColor color);
	QColor GetTagPopupCreateTip();

//模块4:标签面板
    QColor m_right_tag_group_select_color;  //右侧标签面板分组选中颜色
    void setRightTagGroupSelectColor(QColor color);
    QColor GetRightTagGroupSelectColor();    
	QColor m_right_tag_group_select_style_color;  //右侧标签面板分组选中样式颜色
    void setRightTagGroupSelectStyleColor(QColor color);
    QColor GetRightTagGroupSelectStyleColor();
    QColor m_right_tag_remove_btn_back_color;  //右侧标签移除按钮背景色
    void setRightTagRemoveBtnBackColor(QColor color);
    QColor GetRightTagRemoveBtnBackColor();

//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓其他模块↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

//标签管理
//通用
  QColor m_tag_manager_font_color1;				    //标签管理颜色1：分类按钮字体颜色
  void setTagManagerFontColor1(QColor color);
  QColor GetTagManagerFontColor1();

  QColor m_tag_manager_font_color2;				    //标签管理颜色2：标签管理模块名称
  void setTagManagerFontColor2(QColor color);
  QColor GetTagManagerFontColor2();

  QColor m_tag_manager_font_color3;				    //标签管理颜色3：标签管理模块标签熟料、模块描述
  void setTagManagerFontColor3(QColor color);
  QColor GetTagManagerFontColor3();

  QColor m_tag_manager_selected_color;		    //标签管理选中颜色（蓝色）
  void setTagManagerSelectedColor(QColor color);
  QColor GetTagManagerSelectedColor();

  QColor m_tag_manager_tag_item_right_font_color;		    //标签管理的标签项右侧数量的字体颜色
  void setTagManagerTagItemRightFontColor(QColor color);
  QColor GetTagManagerTagItemRightFontColor();

  QColor m_tag_manager_tag_item_init_back_color;		    //标签管理的标签项右侧数量的字体颜色
  void setTagManagerTagItemInitBackColor(QColor color);
  QColor GetTagManagerTagItemInitBackColor();

 //模块0：标签分类
  QColor m_tag_manager_tag_Group_item_back_color;		//标签分类item的背景色
  void setTagManagerTagGroupItemBackColor(QColor color);
  QColor GetTagManagerTagGroupItemBackColor();

  //偏好设置
  QColor m_setting_spacing_line_color;		//分割线颜色
  void setSettingSpacingLineColor(QColor color);
  QColor GetSettingSpacingLineColor();
  //左侧按钮
  QColor m_setting_btn_normal_color;		//左侧按钮正常颜色
  void setSettingBtnNormalColor(QColor color);
  QColor GetSettingBtnNormalColor();

  QColor m_setting_btn_selected_color;		//左侧按钮选中颜色
  void setSettingBtnSelectedColor(QColor color);
  QColor GetSettingBtnSelectedColor();

  //格式设置
  QColor m_setting_format_image_color;		//图像标签颜色
  void setSettingFormatImageColor(QColor color);
  QColor GetSettingFormatImageColor();

  QColor m_setting_format_file_color;		//文件标签颜色
  void setSettingFormatFileColor(QColor color);
  QColor GetSettingFormatFileColor();

  QColor m_setting_format_source_color;		//源文件标签颜色
  void setSettingFormatSourceColor(QColor color);
  QColor GetSettingFormatSourceColor();

  QColor m_setting_format_other_color;		//其他标签颜色
  void setSettingFormatOtherColor(QColor color);
  QColor GetSettingFormatOtherColor();

  QColor m_setting_format_item_back_color;		//支持导入的格式Item颜色
  void setSettingFormatItemBackColor(QColor color);
  QColor GetSettingFormatItemBackColor();

  //素材库设置
  QColor m_setting_lib_combox_back_color;		//素材库下拉框背景颜色
  void setSettingLibComboxBackColor(QColor color);
  QColor GetSettingLibComboxBackColor();

  //素材库操作按钮颜色
  QColor m_setting_lib_switch_color;		//切换
  void setSettingLibSwitchColor(QColor color);
  QColor GetSettingLibSwitchColor();

  QColor m_setting_lib_merge_color;		//合并
  void setSettingLibMergehColor(QColor color);
  QColor GetSettingLibMergeColor();

  QColor m_setting_lib_detail_color;		//详情
  void setSettingLibDetailColor(QColor color);
  QColor GetSettingLibDetailColor();

  QColor m_setting_lib_remove_color;		//解除
  void setSettingLibRemoveColor(QColor color);
  QColor GetSettingLibRemoveColor();

  QColor m_setting_lib_del_color;		//删除
  void setSettingLibDelColor(QColor color);
  QColor GetSettingLibDelColor();

//所有弹窗模块通用
	QColor  m_popup_win_background_color;
	QColor  m_popup_win_border_color;
	QColor  m_popup_win_blue_color;		//所有弹窗模块中的蓝色字体
	QColor  m_popup_win_gray_color1;	//所有弹窗模块中的灰色1

	void SetPopupWinBackgroundColor(QColor);
	void SetPopupWinBorderColor(QColor);
	void SetPopupWinBlueColor(QColor);
	void SetPopupWinGrayColor1(QColor);

	QColor GetPopupWinBackgroundColor();
	QColor GetPopupWinBorderColor();
	QColor GetPopupWinBlueColor();
	QColor GetPopupWinGrayColor1();

//皮肤选择弹窗
	QColor m_skin_switch_win_scroll_handle;               //皮肤切换窗口进度条手柄
	QColor m_skin_switch_win_scroll_across;                //皮肤切换窗口进度条划过区域
	QColor m_skin_switch_win_scroll_not_across;         //皮肤切换窗口进度条未划过区域

	void SetSkinSwitchWinScrollHandle(QColor);
	void SetSkinSwitchWinScrollAcross(QColor);
	void SetSkinSwitchWinScrollNotAcross(QColor);

	QColor GetSkinSwitchWinScrollHandle();
	QColor GetSkinSwitchWinScrollAcross();
	QColor GetSkinSwitchWinScrollNotAcross();

//菜单模块
	QColor m_menu_background_color;       //菜单背景颜色
	QColor m_menu_border_color;               //菜单边框颜色
	QColor m_menu_separator_line_color;    //菜单分割线颜色

	void SetMenuBackgroundColor(QColor);
	void SetMenuBorderColor(QColor);
	void SetMenuSeparatorLineColor(QColor);

	QColor GetMenuBackgroundColor();
	QColor GetMenuBorderColor();
	QColor GetMenuSeparatorLineColor();

	
//悬浮提示
	QColor  m_tool_tip_win_background_color;
	QColor  m_tool_tip_win_border_color;

	void SetToolTipBackgroundColor(QColor);
	void SetToolTipBorderColor(QColor);


	QColor GetToolTipBackgroundColor();
	QColor GetToolTipBorderColor();


//升级资源库弹窗
	QColor  m_update_lib_win_start_update_lib_btn_color;
	QColor  m_update_lib_win_close_software_btn_color;
	QColor  m_update_lib_win_open_other_lib_btn_color;

	void  SetUpdateLibWinStartUpdateLibColor(QColor);
	void  SetUpdateLibWinCloseSoftWareColor(QColor);
	void  SetUpdateLibWinOpenOtherLibColor(QColor);

	QColor  GetUpdateLibWinStartUpdateLibColor();
	QColor  GetUpdateLibWinCloseSoftWareColor();
	QColor  GetUpdateLibWinOpenOtherLibColor();

//导入滚动条模块
	QColor m_import_progress_background_color;
	QColor m_import_progress_selected_color;
	QColor m_import_progress_unselected_color;

	void SetImportProgressBackColor(QColor);
	void SetImportProgressSelectedColor(QColor);
	void SetImportProgressUnSelectedColor(QColor);

	QColor GetImportProgressBackColor();
	QColor GetImportProgressSelectedColor();
	QColor GetImportProgressUnSelectedColor();


  //批量下载弹框控件颜色
  QColor m_batchDownloadControlBkColor;
  void setBatchDownloadControlsBkColor(const QColor& color);
  QColor getBatchDownloadControlsBkColor();


  //批量重命名特殊颜色
  QColor m_batch_rename_edit_back_color;    //批量重命名输入框颜色
  void SetBatchRenameEditBackColor(QColor);
  QColor GetBatchRenameEditBackColor();

  //所有弹窗进度条模块
  QColor popup_progressbar_select_color;
  void SetPopupProgressBarSelectColor(QColor color);
  QColor GetPopupProgressBarSelectColor();

  QColor popup_progressbar_unselect_color1;
  void SetPopupProgressBarUnSelectColor1(QColor color);
  QColor GetPopupProgressBarUnSelectColor1();

  QColor popup_progressbar_unselect_color2;
  void SetPopupProgressBarUnSelectColor2(QColor color);
  QColor GetPopupProgressBarUnSelectColor2();

  //通知悬浮窗模块
  QColor m_notification_back_color1;				//通知悬浮窗背景颜色1
  void SetNotificationBackColor1(QColor color);
  QColor GetNotificationBackColor1();

  QColor m_notification_back_color2;				//通知悬浮窗背景颜色2
  void SetNotificationBackColor2(QColor color);
  QColor GetNotificationBackColor2();

  //更新模块
  QColor m_update_failed_color;						//下载软件失败字体颜色
  void SetUpdateFailedColor(QColor color);
  QColor GetUpdateFailedColor();


  //插件气泡弹窗
  QColor m_bubblewin_back_color;  //背景
  void SetBubbleWinBackColor(QColor color);
  QColor GetBubbleWinBackColor();


  QColor m_bubblewin_border_color; //边框
  void SetBubbleWinBorderColor(QColor color);
  QColor GetBubbleWinBorderColor();


  QColor m_bubblewin_line_color;  //旗袍弹窗中间那根线
  void SetBubbleWinLineColor(QColor color);
  QColor GetBubbleWinLineColor();

  QColor m_side_main_color;  //【隐藏左右侧按钮】主色
  void SetSideMainColor(QColor color);
  QColor GetSideMainColor();

  QColor m_side_arrow_color;  //【隐藏左右侧按钮】箭头配色
  void SetSideArrowColor(QColor color);
  QColor GetSideArrowColor();

  void SetWidgetStyleSheetWithQssName(QWidget* widget,const QString& qss_name);


private:
 QMap<QString,QString> m_styleSheetMap;
 QString mFontFamily;
 qreal m_dpi{1.0};
};
