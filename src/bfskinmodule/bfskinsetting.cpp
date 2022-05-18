#include "bfskinsetting.h"
#include "utils/QtFlieOperation.h"
#include "utils/regexp.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QPainter>
#include <QScreen>
#include <QSvgRenderer>
#include <QWidget>

BFSkinSetting* BFSkinSetting::m_skin_setting = nullptr;

qreal BFSkinSetting::GetDpi() { return m_dpi; }

void BFSkinSetting::SetDpi(qreal dpi) {
  if (dpi <= 1.01) {
    return;
  }

  m_dpi = dpi;
}

static qreal GetMaxDpi() {
  qreal max_dpi = 1;
  QList<QScreen*> screens = QApplication::screens();
  for (QScreen* screen : screens) {
    qreal dpi = screen->devicePixelRatio();
    if (dpi > max_dpi) {
      max_dpi = dpi;
    }
  }
  return max_dpi;
}

QPixmap BFSkinSetting::GetSvgPixmapWithName(const QString& svg_resource_name) {
  if (svg_resource_name.isEmpty()) {
    Q_ASSERT(false);
    return QPixmap();
  }

  QString preference_normal_str =
      GetSkinResourceAbsolutePath(svg_resource_name);
  // tree_list_all_normal  nav_dropbox_array_normal
  auto m_render_preference_normal = new QSvgRenderer(preference_normal_str);
  QSize size_preference_normal = m_render_preference_normal->defaultSize();
  auto dpi = GetMaxDpi();
  QImage image_preference_normal(size_preference_normal.width() * dpi,
                                 size_preference_normal.height() * dpi,
                                 QImage::Format_ARGB32_Premultiplied);
  image_preference_normal.fill(Qt::transparent);
  QPainter painter_preference_normal(&image_preference_normal);
  m_render_preference_normal->render(&painter_preference_normal);
  QPixmap m_pix_preference_normal(QPixmap::fromImage(image_preference_normal));
  m_pix_preference_normal.setDevicePixelRatio(dpi);
  delete m_render_preference_normal;

  return m_pix_preference_normal;
}

QColor BFSkinSetting::GetMainColor() { return main_color; }

QColor BFSkinSetting::GetGreenColor() { return green_color; }

QColor BFSkinSetting::GetOrangeColor() { return orange_color; }

QColor BFSkinSetting::GetYellowColor() { return yellow_color; }

QColor BFSkinSetting::GetCommonFirstColor() { return common_first_color; }

QColor BFSkinSetting::GetCommonSecondColor() { return common_second_color; }

QColor BFSkinSetting::GetCommonThridColor() { return common_third_color; }

void BFSkinSetting::SetCommonFirstColor(QColor color) {
  common_first_color = color;
}

void BFSkinSetting::SetCommonSecondColor(QColor color) {
  common_second_color = color;
}

void BFSkinSetting::SetCommonThridColor(QColor color) {
  common_third_color = color;
}

QColor BFSkinSetting::GetCommonInputColor() { return common_input_color; }

QColor BFSkinSetting::GetCommonModeLightColor() {
  return common_mode_light_color;
}

QColor BFSkinSetting::GetCommonModeDarkColor() {
  return common_mode_dark_color;
}

void BFSkinSetting::SetCommonInputColor(QColor color) {
  common_input_color = color;
}

void BFSkinSetting::SetCommonModeLightColor(QColor color) {
  common_mode_light_color = color;
}

void BFSkinSetting::SetCommonModeDarkColor(QColor color) {
  common_mode_dark_color = color;
}

void BFSkinSetting::SetStrokePopupColor(QColor color) {
  stroke_popup_color = color;
}

void BFSkinSetting::SetInputAndButtonColor(QColor color) {
  input_and_button_color = color;
}

void BFSkinSetting::SetOtherButtonColor(QColor color) {
  other_button_color = color;
}

void BFSkinSetting::SetSplitColor(QColor color) { split_color = color; }

void BFSkinSetting::SetScrollBarColor(QColor color) {
  scroll_bar_color = color;
}

void BFSkinSetting::SetOptinsColor(QColor color) { options_color = color; }

void BFSkinSetting::SetMaskDefaultColor(QColor color) {
  mask_default_color = color;
}

void BFSkinSetting::SetMaskFocusColor(QColor color) {
  mask_focus_color = color;
}

QColor BFSkinSetting::GetStrokePopupColor() { return stroke_popup_color; }

QColor BFSkinSetting::GetInputAndButtonColor() {
  return input_and_button_color;
}

QColor BFSkinSetting::GetOtherButtonColor() { return other_button_color; }

QColor BFSkinSetting::GetSplitColor() { return split_color; }

QColor BFSkinSetting::GetScrollBarColor() { return scroll_bar_color; }

QColor BFSkinSetting::GetOptinsColor() { return options_color; }

QColor BFSkinSetting::GetMaskDefaultColor() { return mask_default_color; }

QColor BFSkinSetting::GetMaskFocusColor() { return mask_focus_color; }

void BFSkinSetting::SetMainColor(QColor color) { main_color = color; }

void BFSkinSetting::SetGreenColor(QColor color) { green_color = color; }

void BFSkinSetting::SetOrangeColor(QColor color) { orange_color = color; }

void BFSkinSetting::SetYellowColor(QColor color) { yellow_color = color; }

void BFSkinSetting::SetTextColor(QVector<QColor> text_color) {
  text_color_vec = text_color;
}

QColor BFSkinSetting::GetTextColor(int index) {
  if (index >= text_color_vec.size()) {
    return QColor(111, 111, 111);
  }
  return text_color_vec.at(index);
}

void BFSkinSetting::SetLeftWinBackgroundColor(QColor color) {
  left_win_backgounrd_color = color;
}

QColor BFSkinSetting::GetLeftWinBackgroundColor() {
  return left_win_backgounrd_color;
}

void BFSkinSetting::SetNodeSelectColor(QColor color) {
  m_node_select_color = color;
}

QColor BFSkinSetting::GetNodeSelectColor() { return m_node_select_color; }

void BFSkinSetting::SetTreeScrollHandleColor(QColor c) {
  m_tree_scroll_handle_color = c;
}

QColor BFSkinSetting::GetTreeScrollHandleColor() {
  return m_tree_scroll_handle_color;
}

void BFSkinSetting::SetTreeRenameBackColor(QColor c) {
  m_tree_rename_back_color = c;
}

QColor BFSkinSetting::GetTreeRenameBackColor() {
  return m_tree_rename_back_color;
}

void BFSkinSetting::SetMidWinBackgroundColor(QColor color) {
  mid_win_backgounrd_color = color;
}

QColor BFSkinSetting::GetMidWinBackgroundColor() {
  return mid_win_backgounrd_color;
}

void BFSkinSetting::SetNavScrollSliverColor(QColor color) {
  m_scroll_sliver_color = color;
}

void BFSkinSetting::SetNavScrollHandleColor(QColor color) {
  m_scroll_handle_color = color;
}

void BFSkinSetting::SetNavSearchBackColor(QColor color) {
  m_nav_search_back_color = color;
}

QColor BFSkinSetting::GetNavSearchBackColor() {
  return m_nav_search_back_color;
}

QColor BFSkinSetting::GetNavScrollSliverColor() {
  return m_scroll_sliver_color;
}

QColor BFSkinSetting::GetNavScrollHandleColor() {
  return m_scroll_handle_color;
}

void BFSkinSetting::SetRightWinBackgroundColor(QColor color) {
  right_win_backgounrd_color = color;
}

QColor BFSkinSetting::GetRightWinBackgroundColor() {
  return right_win_backgounrd_color;
}

void BFSkinSetting::SetRightWinBlue1(QColor color) { right_win_blue1 = color; }

QColor BFSkinSetting::GetRightWinBlue1() { return right_win_blue1; }

void BFSkinSetting::SetRightInfoExportBtnColor(QColor color) {
  m_right_info_export_btn_color = color;
}

QColor BFSkinSetting::GetRightInfoExportBtnColor() {
  return m_right_info_export_btn_color;
}

void BFSkinSetting::SetRightNameEditBackColor(QColor color) {
  m_right_info_name_edit_back_color = color;
}

QColor BFSkinSetting::GetRightNameEditBackColor() {
  return m_right_info_name_edit_back_color;
}

void BFSkinSetting::setRightFont1(QColor color) { m_right_info_font_1 = color; }

QColor BFSkinSetting::GetRightFont1() { return m_right_info_font_1; }

void BFSkinSetting::setRightTagFontColor(QColor color) {
  m_right_info_tag_font_color = color;
}

QColor BFSkinSetting::GetRightTagFontColor() {
  return m_right_info_tag_font_color;
}

void BFSkinSetting::setRightTagCrossColor(QColor color) {
  m_right_info_tag_cross_color = color;
}

QColor BFSkinSetting::GetRightTagCrossColor() {
  return m_right_info_tag_cross_color;
}

void BFSkinSetting::setRightResInfoFontColor(QColor color) {
  m_right_info_res_info_font_color = color;
}

QColor BFSkinSetting::GetRightResInfoFontColor() {
  return m_right_info_res_info_font_color;
}

void BFSkinSetting::setTagPopupTabStrFontColor(QColor color) {
  m_tag_popup_tabStr_font_color = color;
}

QColor BFSkinSetting::GetTagPopupTabStrFontColor() {
  return m_tag_popup_tabStr_font_color;
}

void BFSkinSetting::setTagPopupTabBackUnselectedColor(QColor color) {
  m_tag_popup_tab_back_unselected_color = color;
}

QColor BFSkinSetting::GetTagPopupTabBackUnselectedColor() {
  return m_tag_popup_tab_back_unselected_color;
}

void BFSkinSetting::setTagPopupTabBackSelectedColor(QColor color) {
  m_tag_popup_tab_back_selected_color = color;
}

QColor BFSkinSetting::GetTagPopupTabBackSelectedColor() {
  return m_tag_popup_tab_back_selected_color;
}

void BFSkinSetting::setTagPopupClassifyFontColor(QColor color) {
  m_tag_popup_classify_font_color = color;
}

QColor BFSkinSetting::GetTagPopupClassifyFontColor() {
  return m_tag_popup_classify_font_color;
}

void BFSkinSetting::setRightScrollHandleColor(QColor color) {
  m_right_info_scroll_handle_color = color;
}

QColor BFSkinSetting::GetRightScrollHandleColor() {
  return m_right_info_scroll_handle_color;
}

void BFSkinSetting::setTagPopupCreateTip(QColor color) {
  m_tag_popup_create_tip = color;
}

QColor BFSkinSetting::GetTagPopupCreateTip() { return m_tag_popup_create_tip; }

void BFSkinSetting::setRightTagGroupSelectColor(QColor color) {
  m_right_tag_group_select_color = color;
}

QColor BFSkinSetting::GetRightTagGroupSelectColor() {
  return m_right_tag_group_select_color;
}

void BFSkinSetting::setRightTagGroupSelectStyleColor(QColor color) {
  m_right_tag_group_select_style_color = color;
}

QColor BFSkinSetting::GetRightTagGroupSelectStyleColor() {
  return m_right_tag_group_select_style_color;
}

void BFSkinSetting::setRightTagRemoveBtnBackColor(QColor color) {
  m_right_tag_remove_btn_back_color = color;
}

QColor BFSkinSetting::GetRightTagRemoveBtnBackColor() {
  return m_right_tag_remove_btn_back_color;
}

void BFSkinSetting::setTagManagerFontColor1(QColor color) {
  m_tag_manager_font_color1 = color;
}

QColor BFSkinSetting::GetTagManagerFontColor1() {
  return m_tag_manager_font_color1;
}

void BFSkinSetting::setTagManagerFontColor2(QColor color) {
  m_tag_manager_font_color2 = color;
}

QColor BFSkinSetting::GetTagManagerFontColor2() {
  return m_tag_manager_font_color2;
}

void BFSkinSetting::setTagManagerFontColor3(QColor color) {
  m_tag_manager_font_color3 = color;
}

QColor BFSkinSetting::GetTagManagerFontColor3() {
  return m_tag_manager_font_color3;
}

void BFSkinSetting::setTagManagerSelectedColor(QColor color) {
  m_tag_manager_selected_color = color;
}

QColor BFSkinSetting::GetTagManagerSelectedColor() {
  return m_tag_manager_selected_color;
}

void BFSkinSetting::setTagManagerTagItemRightFontColor(QColor color) {
  m_tag_manager_tag_item_right_font_color = color;
}

QColor BFSkinSetting::GetTagManagerTagItemRightFontColor() {
  return m_tag_manager_tag_item_right_font_color;
}

void BFSkinSetting::setTagManagerTagItemInitBackColor(QColor color) {
  m_tag_manager_tag_item_init_back_color = color;
}

QColor BFSkinSetting::GetTagManagerTagItemInitBackColor() {
  return m_tag_manager_tag_item_init_back_color;
}

void BFSkinSetting::setTagManagerTagGroupItemBackColor(QColor color) {
  m_tag_manager_tag_Group_item_back_color = color;
}

QColor BFSkinSetting::GetTagManagerTagGroupItemBackColor() {
  return m_tag_manager_tag_Group_item_back_color;
}

void BFSkinSetting::setSettingBtnNormalColor(QColor color) {
  m_setting_btn_normal_color = color;
}

QColor BFSkinSetting::GetSettingBtnNormalColor() {
  return m_setting_btn_normal_color;
}

void BFSkinSetting::setSettingBtnSelectedColor(QColor color) {
  m_setting_btn_selected_color = color;
}

QColor BFSkinSetting::GetSettingBtnSelectedColor() {
  return m_setting_btn_selected_color;
}

void BFSkinSetting::setSettingFormatImageColor(QColor color) {
  m_setting_format_image_color = color;
}

QColor BFSkinSetting::GetSettingFormatImageColor() {
  return m_setting_format_image_color;
}

void BFSkinSetting::setSettingFormatFileColor(QColor color) {
  m_setting_format_file_color = color;
}

QColor BFSkinSetting::GetSettingFormatFileColor() {
  return m_setting_format_file_color;
}

void BFSkinSetting::setSettingFormatSourceColor(QColor color) {
  m_setting_format_source_color = color;
}

QColor BFSkinSetting::GetSettingFormatSourceColor() {
  return m_setting_format_source_color;
}

void BFSkinSetting::setSettingFormatOtherColor(QColor color) {
  m_setting_format_other_color = color;
}

QColor BFSkinSetting::GetSettingFormatOtherColor() {
  return m_setting_format_other_color;
}

void BFSkinSetting::setSettingFormatItemBackColor(QColor color) {
  m_setting_format_item_back_color = color;
}

QColor BFSkinSetting::GetSettingFormatItemBackColor() {
  return m_setting_format_item_back_color;
}

void BFSkinSetting::setSettingLibComboxBackColor(QColor color) {
  m_setting_lib_combox_back_color = color;
}

QColor BFSkinSetting::GetSettingLibComboxBackColor() {
  return m_setting_lib_combox_back_color;
}

void BFSkinSetting::setSettingLibSwitchColor(QColor color) {
  m_setting_lib_switch_color = color;
}

QColor BFSkinSetting::GetSettingLibSwitchColor() {
  return m_setting_lib_switch_color;
}

void BFSkinSetting::setSettingLibMergehColor(QColor color) {
  m_setting_lib_merge_color = color;
}

QColor BFSkinSetting::GetSettingLibMergeColor() {
  return m_setting_lib_merge_color;
}

void BFSkinSetting::setSettingLibDetailColor(QColor color) {
  m_setting_lib_detail_color = color;
}

QColor BFSkinSetting::GetSettingLibDetailColor() {
  return m_setting_lib_detail_color;
}

void BFSkinSetting::setSettingLibRemoveColor(QColor color) {
  m_setting_lib_remove_color = color;
}

QColor BFSkinSetting::GetSettingLibRemoveColor() {
  return m_setting_lib_remove_color;
}

void BFSkinSetting::setSettingLibDelColor(QColor color) {
  m_setting_lib_del_color = color;
}

QColor BFSkinSetting::GetSettingLibDelColor() {
  return m_setting_lib_del_color;
}

void BFSkinSetting::setSettingSpacingLineColor(QColor color) {
  m_setting_spacing_line_color = color;
}

QColor BFSkinSetting::GetSettingSpacingLineColor() {
  return m_setting_spacing_line_color;
}

void BFSkinSetting::SetPopupWinBackgroundColor(QColor color) {
  m_popup_win_background_color = color;
}

void BFSkinSetting::SetPopupWinBorderColor(QColor color) {
  m_popup_win_border_color = color;
}

void BFSkinSetting::SetPopupWinBlueColor(QColor color) {
  m_popup_win_blue_color = color;
}

void BFSkinSetting::SetPopupWinGrayColor1(QColor color) {
  m_popup_win_gray_color1 = color;
}

QColor BFSkinSetting::GetPopupWinBackgroundColor() {
  return m_popup_win_background_color;
}

QColor BFSkinSetting::GetPopupWinBorderColor() {
  return m_popup_win_border_color;
}

QColor BFSkinSetting::GetPopupWinBlueColor() { return m_popup_win_blue_color; }

QColor BFSkinSetting::GetPopupWinGrayColor1() {
  return m_popup_win_gray_color1;
}

void BFSkinSetting::SetSkinSwitchWinScrollHandle(QColor color) {
  m_skin_switch_win_scroll_handle = color;
}

void BFSkinSetting::SetSkinSwitchWinScrollAcross(QColor color) {
  m_skin_switch_win_scroll_across = color;
}

void BFSkinSetting::SetSkinSwitchWinScrollNotAcross(QColor color) {
  m_skin_switch_win_scroll_not_across = color;
}

QColor BFSkinSetting::GetSkinSwitchWinScrollHandle() {
  return m_skin_switch_win_scroll_handle;
}

QColor BFSkinSetting::GetSkinSwitchWinScrollAcross() {
  return m_skin_switch_win_scroll_across;
}

QColor BFSkinSetting::GetSkinSwitchWinScrollNotAcross() {
  return m_skin_switch_win_scroll_not_across;
}

void BFSkinSetting::SetMenuBackgroundColor(QColor color) {
  m_menu_background_color = color;
}

void BFSkinSetting::SetMenuBorderColor(QColor color) {
  m_menu_border_color = color;
}

void BFSkinSetting::SetMenuSeparatorLineColor(QColor color) {
  m_menu_separator_line_color = color;
}

QColor BFSkinSetting::GetMenuBackgroundColor() {
  return m_menu_background_color;
}

QColor BFSkinSetting::GetMenuBorderColor() { return m_menu_border_color; }

QColor BFSkinSetting::GetMenuSeparatorLineColor() {
  return m_menu_separator_line_color;
}

void BFSkinSetting::SetToolTipBackgroundColor(QColor color) {
  m_tool_tip_win_background_color = color;
}

void BFSkinSetting::SetToolTipBorderColor(QColor color) {
  m_tool_tip_win_border_color = color;
}

QColor BFSkinSetting::GetToolTipBackgroundColor() {
  return m_tool_tip_win_background_color;
}

QColor BFSkinSetting::GetToolTipBorderColor() {
  return m_tool_tip_win_border_color;
}

void BFSkinSetting::SetUpdateLibWinStartUpdateLibColor(QColor color) {
  m_update_lib_win_start_update_lib_btn_color = color;
}

void BFSkinSetting::SetUpdateLibWinCloseSoftWareColor(QColor color) {
  m_update_lib_win_close_software_btn_color = color;
}

void BFSkinSetting::SetUpdateLibWinOpenOtherLibColor(QColor color) {
  m_update_lib_win_open_other_lib_btn_color = color;
}

QColor BFSkinSetting::GetUpdateLibWinStartUpdateLibColor() {
  return m_update_lib_win_start_update_lib_btn_color;
}

QColor BFSkinSetting::GetUpdateLibWinCloseSoftWareColor() {
  return m_update_lib_win_close_software_btn_color;
}

QColor BFSkinSetting::GetUpdateLibWinOpenOtherLibColor() {
  return m_update_lib_win_open_other_lib_btn_color;
}

void BFSkinSetting::SetImportProgressBackColor(QColor color) {
  m_import_progress_background_color = color;
}

void BFSkinSetting::SetImportProgressSelectedColor(QColor color) {
  m_import_progress_selected_color = color;
}

void BFSkinSetting::SetImportProgressUnSelectedColor(QColor color) {
  m_import_progress_unselected_color = color;
}

QColor BFSkinSetting::GetImportProgressBackColor() {
  return m_import_progress_background_color;
}

QColor BFSkinSetting::GetImportProgressSelectedColor() {
  return m_import_progress_selected_color;
}

QColor BFSkinSetting::GetImportProgressUnSelectedColor() {
  return m_import_progress_unselected_color;
}

void BFSkinSetting::SetConditionFilterColorSelectColor(QColor color) {
  condition_filter_color_select_color = color;
}

QColor BFSkinSetting::GetConditionFilterColorSelectColor() {
  qDebug() << condition_filter_color_select_color.name(QColor::HexArgb);
  return condition_filter_color_select_color;
}

void BFSkinSetting::SetConditionFilterControlBackGroundColor(QColor color) {
  condition_filter_control_background_color = color;
}

QColor BFSkinSetting::GetConditionFilterControlBackGroundColor() {
  return condition_filter_control_background_color;
}

void BFSkinSetting::SetConditionFilterSelectControlBackGroundColor(
    QColor color) {
  condition_filter_select_control_background_color = color;
}

QColor BFSkinSetting::GetConditionFilterSelectControlBackGroundColor() {
  return condition_filter_select_control_background_color;
}

void BFSkinSetting::SetConditionFilterComboxControlTextColor(QColor color) {
  condition_filter_combox_control_text_color = color;
}

QColor BFSkinSetting::GetConditionFilterComboxControlTextColor() {
  return condition_filter_combox_control_text_color;
}

void BFSkinSetting::SetConditionFilterListItemHoverColor(QColor color) {
  condition_filter_listitem_hover_color = color;
}

QColor BFSkinSetting::GetConditionFilterListItemHoverColor() {
  return condition_filter_listitem_hover_color;
}

void BFSkinSetting::SetConditionFilterItemSelectBackColor(QColor color) {
  condition_filter_item_select_back_color = color;
}

QColor BFSkinSetting::GetConditionFilterItemSelectBackColor() {
  return condition_filter_item_select_back_color;
}

void BFSkinSetting::SetConditionFilterSearchBackColor(QColor color) {
  condition_filter_search_back_color = color;
}

QColor BFSkinSetting::GetConditionFilterSearchBackColor() {
  return condition_filter_search_back_color;
}

void BFSkinSetting::SetConditionFilterListSelectItemBackColor(QColor color) {
  condition_filter_list_select_item_back_color = color;
}

QColor BFSkinSetting::GetConditionFilterListSelectItemBackColor() {
  return condition_filter_list_select_item_back_color;
}

void BFSkinSetting::SetConditionFilterListHoverItemBackColor(QColor color) {
  condition_filter_list_hover_item_back_color = color;
}

QColor BFSkinSetting::GetConditionFilterListHoverItemBackColor() {
  return condition_filter_list_hover_item_back_color;
}

void BFSkinSetting::SetListPreviewFolderFrontColor(QColor color) {
  m_list_preview_folder_front_color = color;
}

QColor BFSkinSetting::GetListPreviewFolderFrontColor() {
  return m_list_preview_folder_front_color;
}

void BFSkinSetting::SetListPreviewFolderBehindColor(QColor color) {
  m_list_preview_folder_behind_color = color;
}

QColor BFSkinSetting::GetListPreviewFolderBehindColor() {
  return m_list_preview_folder_behind_color;
}

QColor BFSkinSetting::GetListPreViewFormatBackColor() {
  return m_list_format_back_color;
}

void BFSkinSetting::SetListPreViewScrollHandleColor(QColor c) {
  m_list_preview_scroll_handle_color = c;
}

QColor BFSkinSetting::GetListPreViewScrollHandleColor() {
  return m_list_preview_scroll_handle_color;
}

void BFSkinSetting::SetListPreViewScrollHandleHoverColor(QColor c) {
  m_list_preview_scroll_handle_hover_color = c;
}

QColor BFSkinSetting::GetListPreViewScrollHandleHoverColor() {
  return m_list_preview_scroll_handle_hover_color;
}

void BFSkinSetting::SetListPreviewRenameBackColor(QColor color) {
  m_list_preview_rename_back_color = color;
}

QColor BFSkinSetting::GetListPreviewRenameBackColor() {
  return m_list_preview_rename_back_color;
}

void BFSkinSetting::SetListPreViewFormatBackColor(QColor color) {
  m_list_format_back_color = color;
}

void BFSkinSetting::setBatchDownloadControlsBkColor(const QColor& color) {
  m_batchDownloadControlBkColor = color;
}

QColor BFSkinSetting::getBatchDownloadControlsBkColor() {
  return m_batchDownloadControlBkColor;
}

void BFSkinSetting::SetBatchRenameEditBackColor(QColor color) {
  m_batch_rename_edit_back_color = color;
}

QColor BFSkinSetting::GetBatchRenameEditBackColor() {
  return m_batch_rename_edit_back_color;
}

void BFSkinSetting::SetPopupProgressBarSelectColor(QColor color) {
  popup_progressbar_select_color = color;
}

QColor BFSkinSetting::GetPopupProgressBarSelectColor() {
  return popup_progressbar_select_color;
}

void BFSkinSetting::SetPopupProgressBarUnSelectColor1(QColor color) {
  popup_progressbar_unselect_color1 = color;
}

QColor BFSkinSetting::GetPopupProgressBarUnSelectColor1() {
  return popup_progressbar_unselect_color1;
}

void BFSkinSetting::SetPopupProgressBarUnSelectColor2(QColor color) {
  popup_progressbar_unselect_color2 = color;
}

QColor BFSkinSetting::GetPopupProgressBarUnSelectColor2() {
  return popup_progressbar_unselect_color2;
}

void BFSkinSetting::SetNotificationBackColor1(QColor color) {
  m_notification_back_color1 = color;
}

QColor BFSkinSetting::GetNotificationBackColor1() {
  return m_notification_back_color1;
}

void BFSkinSetting::SetNotificationBackColor2(QColor color) {
  m_notification_back_color2 = color;
}

QColor BFSkinSetting::GetNotificationBackColor2() {
  return m_notification_back_color2;
}

void BFSkinSetting::SetUpdateFailedColor(QColor color) {
  m_update_failed_color = color;
}

QColor BFSkinSetting::GetUpdateFailedColor() { return m_update_failed_color; }

void BFSkinSetting::SetBubbleWinBackColor(QColor color) {
  m_bubblewin_back_color = color;
}

QColor BFSkinSetting::GetBubbleWinBackColor() { return m_bubblewin_back_color; }

void BFSkinSetting::SetBubbleWinBorderColor(QColor color) {
  m_bubblewin_border_color = color;
}

QColor BFSkinSetting::GetBubbleWinBorderColor() {
  return m_bubblewin_border_color;
}

void BFSkinSetting::SetBubbleWinLineColor(QColor color) {
  m_bubblewin_line_color = color;
}

QColor BFSkinSetting::GetBubbleWinLineColor() { return m_bubblewin_line_color; }

void BFSkinSetting::SetSideMainColor(QColor color) {
  m_side_main_color = color;
}

QColor BFSkinSetting::GetSideMainColor() { return m_side_main_color; }

void BFSkinSetting::SetSideArrowColor(QColor color) {
  m_side_arrow_color = color;
}

QColor BFSkinSetting::GetSideArrowColor() { return m_side_arrow_color; }

void BFSkinSetting::SetWidgetStyleSheetWithQssName(QWidget* widget,
                                                   const QString& qss_name) {
  if (!widget) {
    Q_ASSERT(!"SetWidgetStyleSheetWithQssName widget is null");
    return;
  }

  if (qss_name.isEmpty()) {
    Q_ASSERT(!"SetWidgetStyleSheetWithQssName qss_name is empty");
    return;
  }

  if (m_styleSheetMap.contains(qss_name)) {
    widget->setStyleSheet(m_styleSheetMap[qss_name]);

  } else {
    Q_ASSERT(!"SetWidgetStyleSheetWithQssName m_styleSheetMap not contasins qss_name");
    return;
  }
}

BFSkinSetting* BFSkinSetting::GetInstance() {
  if (!m_skin_setting) {
    m_skin_setting = new BFSkinSetting;
  }
  return m_skin_setting;
}

void BFSkinSetting::Delete() {
  if (m_skin_setting) {
    delete m_skin_setting;
    m_skin_setting = NULL;
  }
}

void BFSkinSetting::SwitchSkinMode(SkinType mode) {
  if (m_cur_skin_type != mode) {
    SetSkinColor(mode);
    m_cur_skin_type = mode;
  }
}

QString BFSkinSetting::GetResourcePath(QString file_name) {
  QDir resourcesDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
  if (resourcesDir.dirName() == "MacOS") {
    resourcesDir.cdUp();
  }
#endif
  resourcesDir.cd("Resources");

  QString folder_path = resourcesDir.absolutePath() + "/";
  folder_path += "skin";
  folder_path += "/";

  switch (m_cur_skin_type) {
    case BlackMode:
      folder_path += "black";
      break;
    case WhiteMode:
      folder_path += "white";
      break;
    default:
      break;
  }

  folder_path += "/";
  folder_path += "image";
  folder_path += "/";
  QFileInfo info(folder_path);

  QString url = QString("image:url(") + info.absoluteFilePath();
  QString need_path = url + file_name + QString(");");
  return need_path;
}

QString BFSkinSetting::GetResourcePathBorderImage(QString file_name) {
  QDir resourcesDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
  if (resourcesDir.dirName() == "MacOS") {
    resourcesDir.cdUp();
  }
#endif
  resourcesDir.cd("Resources");

  QString folder_path = resourcesDir.absolutePath() + QDir::separator();
  folder_path += "skin";
  folder_path += QDir::separator();

  switch (m_cur_skin_type) {
    case BlackMode:
      folder_path += "black";
      break;
    case WhiteMode:
      folder_path += "white";
      break;
    default:
      break;
  }

  folder_path += QDir::separator();
  folder_path += "image";
  folder_path += QDir::separator();

  QFileInfo info(folder_path);

  QString url = QString("border-image:url(") + info.absoluteFilePath();
  QString need_path = url + file_name + QString(");");

  return need_path;
}

QString BFSkinSetting::GetResourceAbsolutePath(QString file_name) {
  if (file_name.isEmpty()) {
    return "";
  }

  QDir resourcesDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
  if (resourcesDir.dirName() == "MacOS") {
    resourcesDir.cdUp();
  }
#endif
  resourcesDir.cd("Resources");

  QString folder_path = resourcesDir.absolutePath() + QDir::separator();
  folder_path += "skin";
  folder_path += QDir::separator();

  switch (m_cur_skin_type) {
    case BlackMode:
      folder_path += "black";
      break;
    case WhiteMode:
      folder_path += "white";
      break;
    default:
      break;
  }

  folder_path += QDir::separator();
  folder_path += "image";
  folder_path += QDir::separator();

  QString need_path = folder_path + file_name;
  return need_path;
}

QString BFSkinSetting::GetFontFamily() { return mFontFamily; }

QPixmap BFSkinSetting::GetFolderImgWithColor(qint32 color) {
  QPixmap ret;
  switch (color) {
    case 0: {
      if (m_grey_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_grey_folder;
      break;
    }
    case 1: {
      if (m_blue_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_blue_folder;
      break;
    }
    case 2: {
      if (m_green_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_green_folder;
      break;
    }
    case 3: {
      if (m_cyan_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_cyan_folder;
      break;
    }
    case 4: {
      if (m_orange_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_orange_folder;
      break;
    }
    case 5: {
      if (m_yellow_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_yellow_folder;
      break;
    }
    case 6: {
      if (m_red_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_red_folder;
      break;
    }
    case 7: {
      if (m_pink_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_pink_folder;
      break;
    }
    case 8: {
      if (m_purple_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_purple_folder;
      break;
    }
    default:
      if (m_grey_folder.isNull()) {
        LoadFloderSvg();
      }
      ret = m_grey_folder;
      break;
  }
  return ret;
}

QColor BFSkinSetting::GetFolderColor(qint32 color_index) {
  QColor need_color = QColor();
  switch (color_index) {
    case 0:
      need_color = QColor(162, 171, 195, 255);
      break;

    case 1:
      need_color = QColor(79, 132, 250, 255);
      break;

    case 2:
      need_color = QColor(68, 215, 182, 255);
      break;

    case 3:
      need_color = QColor(70, 196, 234, 255);
      break;

    case 4:
      need_color = QColor(247, 181, 0, 255);
      break;

    case 5:
      need_color = QColor(255, 241, 130, 255);
      break;

    case 6:
      need_color = QColor(240, 105, 90, 255);
      break;

    case 7:
      need_color = QColor(244, 166, 232, 255);
      break;

    case 8:
      need_color = QColor(192, 83, 254, 255);
      break;

    default:
      break;
  }
  return need_color;
}

void BFSkinSetting::LoadConfig() {
  //配置文件路径
  QDir resourcesDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
  if (resourcesDir.dirName() == "MacOS") {
    resourcesDir.cdUp();
  }
#endif
  resourcesDir.cd("Resources");

  QString zip_from = resourcesDir.absolutePath() + QDir::separator();
  zip_from += "skin";
  zip_from += QDir::separator();
  zip_from += "black";
  zip_from += QDir::separator();
  zip_from += "skin_color_setting.json";

  //存在判断
  QFile file(zip_from);
  bool ret = file.exists();
  if (!ret) {
    //不存在
    Q_ASSERT(0);
    return;
  }

  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString value = file.readAll();
  file.close();

  QJsonParseError parseJsonErr;
  QJsonDocument document =
      QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
  if (!(parseJsonErr.error == QJsonParseError::NoError)) {
    //解析失败
    Q_ASSERT(0);
    return;
  }

  QJsonObject jsonObject = document.object();

  if (jsonObject.contains("SkinColorConfig")) {
    QJsonValue jsonValue = jsonObject.value("SkinColorConfig");
    qDebug() << jsonValue.type();
    QJsonObject jsonObj = jsonValue.toObject();
    //测试代码
    // QJsonValue test_value = jsonObj.value("text_color_type_1");
    // QString test = test_value.toString();
    // QJsonValue test2_value = jsonObj["text_color_type_1"];
    // QString test2 = test2_value.toString();

    //开始取值
    QColor text_color_type_1 =
        StrIntoQColor(jsonObj["text_color_type_1"].toString());
    QColor text_color_type_2 =
        StrIntoQColor(jsonObj["text_color_type_2"].toString());
    QColor text_color_type_3 =
        StrIntoQColor(jsonObj["text_color_type_3"].toString());
    QColor text_color_type_4 =
        StrIntoQColor(jsonObj["text_color_type_4"].toString());

    text_color_vec.push_back(text_color_type_1);
    text_color_vec.push_back(text_color_type_2);
    text_color_vec.push_back(text_color_type_3);
    text_color_vec.push_back(text_color_type_4);

    main_color = StrIntoQColor(jsonObj["main_color"].toString());
    green_color = StrIntoQColor(jsonObj["green_color"].toString());
    orange_color = StrIntoQColor(jsonObj["orange_color"].toString());
    yellow_color = StrIntoQColor(jsonObj["yellow_color"].toString());
    common_first_color =
        StrIntoQColor(jsonObj["common_first_color"].toString());
    common_second_color =
        StrIntoQColor(jsonObj["common_second_color"].toString());
    common_third_color =
        StrIntoQColor(jsonObj["common_third_color"].toString());
    common_input_color =
        StrIntoQColor(jsonObj["common_input_color"].toString());
    common_mode_light_color =
        StrIntoQColor(jsonObj["common_mode_light_color"].toString());
    common_mode_dark_color =
        StrIntoQColor(jsonObj["common_mode_dark_color"].toString());
    stroke_popup_color =
        StrIntoQColor(jsonObj["stroke_popup_color"].toString());
    input_and_button_color =
        StrIntoQColor(jsonObj["input_and_button_color"].toString());
    other_button_color =
        StrIntoQColor(jsonObj["other_button_color"].toString());
    split_color = StrIntoQColor(jsonObj["split_color"].toString());
    scroll_bar_color = StrIntoQColor(jsonObj["scroll_bar_color"].toString());
    options_color = StrIntoQColor(jsonObj["options_color"].toString());
    mask_default_color =
        StrIntoQColor(jsonObj["mask_default_color"].toString());
    mask_focus_color = StrIntoQColor(jsonObj["mask_focus_color"].toString());
    left_win_backgounrd_color =
        StrIntoQColor(jsonObj["left_win_backgounrd_color"].toString());
    m_node_select_color =
        StrIntoQColor(jsonObj["m_node_select_color"].toString());
    m_tree_scroll_handle_color =
        StrIntoQColor(jsonObj["m_tree_scroll_handle_color"].toString());
    m_tree_rename_back_color =
        StrIntoQColor(jsonObj["m_tree_rename_back_color"].toString());
    mid_win_backgounrd_color =
        StrIntoQColor(jsonObj["mid_win_backgounrd_color"].toString());
    m_scroll_sliver_color =
        StrIntoQColor(jsonObj["m_scroll_sliver_color"].toString());
    m_scroll_handle_color =
        StrIntoQColor(jsonObj["m_scroll_handle_color"].toString());
    m_nav_search_back_color =
        StrIntoQColor(jsonObj["m_nav_search_back_color"].toString());
    qDebug() << jsonObj["condition_filter_color_select_color"].toString();
    condition_filter_color_select_color = StrIntoQColor(
        jsonObj["condition_filter_color_select_color"].toString());
    qDebug() << condition_filter_color_select_color.name(QColor::HexArgb);
    ;
    condition_filter_control_background_color = StrIntoQColor(
        jsonObj["condition_filter_control_background_color"].toString());
    condition_filter_select_control_background_color = StrIntoQColor(
        jsonObj["condition_filter_select_control_background_color"].toString());
    condition_filter_combox_control_text_color = StrIntoQColor(
        jsonObj["condition_filter_combox_control_text_color"].toString());
    condition_filter_listitem_hover_color = StrIntoQColor(
        jsonObj["condition_filter_listitem_hover_color"].toString());
    condition_filter_item_select_back_color = StrIntoQColor(
        jsonObj["condition_filter_item_select_back_color"].toString());
    condition_filter_search_back_color =
        StrIntoQColor(jsonObj["condition_filter_search_back_color"].toString());
    condition_filter_list_select_item_back_color = StrIntoQColor(
        jsonObj["condition_filter_list_select_item_back_color"].toString());

    condition_filter_list_hover_item_back_color = StrIntoQColor(
        jsonObj["condition_filter_list_hover_item_back_color"].toString());

    m_list_preview_folder_front_color =
        StrIntoQColor(jsonObj["m_list_preview_folder_front_color"].toString());
    m_list_preview_folder_behind_color =
        StrIntoQColor(jsonObj["m_list_preview_folder_behind_color"].toString());
    m_list_format_back_color =
        StrIntoQColor(jsonObj["m_list_format_back_color"].toString());
    m_list_preview_scroll_handle_color =
        StrIntoQColor(jsonObj["m_list_preview_scroll_handle_color"].toString());
    m_list_preview_scroll_handle_hover_color = StrIntoQColor(
        jsonObj["m_list_preview_scroll_handle_hover_color"].toString());
    m_list_preview_rename_back_color =
        StrIntoQColor(jsonObj["m_list_preview_rename_back_color"].toString());
    right_win_backgounrd_color =
        StrIntoQColor(jsonObj["right_win_backgounrd_color"].toString());
    right_win_blue1 = StrIntoQColor(jsonObj["right_win_blue1"].toString());
    m_right_info_scroll_handle_color =
        StrIntoQColor(jsonObj["m_right_info_scroll_handle_color"].toString());
    m_right_info_export_btn_color =
        StrIntoQColor(jsonObj["m_right_info_export_btn_color"].toString());
    m_right_info_name_edit_back_color =
        StrIntoQColor(jsonObj["m_right_info_name_edit_back_color"].toString());
    m_right_info_font_1 =
        StrIntoQColor(jsonObj["m_right_info_font_1"].toString());
    m_right_info_tag_font_color =
        StrIntoQColor(jsonObj["m_right_info_tag_font_color"].toString());
    m_right_info_tag_cross_color =
        StrIntoQColor(jsonObj["m_right_info_tag_cross_color"].toString());
    m_right_info_res_info_font_color =
        StrIntoQColor(jsonObj["m_right_info_res_info_font_color"].toString());
    m_tag_popup_tabStr_font_color =
        StrIntoQColor(jsonObj["m_tag_popup_tabStr_font_color"].toString());
    m_tag_popup_tab_back_unselected_color = StrIntoQColor(
        jsonObj["m_tag_popup_tab_back_unselected_color"].toString());
    m_tag_popup_tab_back_selected_color = StrIntoQColor(
        jsonObj["m_tag_popup_tab_back_selected_color"].toString());
    m_tag_popup_classify_font_color =
        StrIntoQColor(jsonObj["m_tag_popup_classify_font_color"].toString());
    m_tag_popup_create_tip =
        StrIntoQColor(jsonObj["m_tag_popup_create_tip"].toString());
    m_right_tag_group_select_color =
        StrIntoQColor(jsonObj["m_right_tag_group_select_color"].toString());
    m_right_tag_group_select_style_color = StrIntoQColor(
        jsonObj["m_right_tag_group_select_style_color"].toString());
    m_right_tag_remove_btn_back_color =
        StrIntoQColor(jsonObj["m_right_tag_remove_btn_back_color"].toString());
    m_tag_manager_font_color1 =
        StrIntoQColor(jsonObj["m_tag_manager_font_color1"].toString());
    m_tag_manager_font_color2 =
        StrIntoQColor(jsonObj["m_tag_manager_font_color2"].toString());
    m_tag_manager_font_color3 =
        StrIntoQColor(jsonObj["m_tag_manager_font_color3"].toString());
    m_tag_manager_selected_color =
        StrIntoQColor(jsonObj["m_tag_manager_selected_color"].toString());
    m_tag_manager_tag_item_right_font_color = StrIntoQColor(
        jsonObj["m_tag_manager_tag_item_right_font_color"].toString());
    m_tag_manager_tag_item_init_back_color = StrIntoQColor(
        jsonObj["m_tag_manager_tag_item_init_back_color"].toString());
    m_setting_btn_normal_color =
        StrIntoQColor(jsonObj["m_setting_btn_normal_color"].toString());
    m_setting_btn_selected_color =
        StrIntoQColor(jsonObj["m_setting_btn_selected_color"].toString());
    m_setting_format_image_color =
        StrIntoQColor(jsonObj["m_setting_format_image_color"].toString());
    m_setting_format_file_color =
        StrIntoQColor(jsonObj["m_setting_format_file_color"].toString());
    m_setting_format_source_color =
        StrIntoQColor(jsonObj["m_setting_format_source_color"].toString());
    m_setting_format_other_color =
        StrIntoQColor(jsonObj["m_setting_format_other_color"].toString());
    m_setting_spacing_line_color =
        StrIntoQColor(jsonObj["m_setting_spacing_line_color"].toString());
    m_setting_format_item_back_color =
        StrIntoQColor(jsonObj["m_setting_format_item_back_color"].toString());
    m_setting_lib_combox_back_color =
        StrIntoQColor(jsonObj["m_setting_lib_combox_back_color"].toString());
    m_setting_lib_switch_color =
        StrIntoQColor(jsonObj["m_setting_lib_switch_color"].toString());
    m_setting_lib_merge_color =
        StrIntoQColor(jsonObj["m_setting_lib_merge_color"].toString());
    m_setting_lib_detail_color =
        StrIntoQColor(jsonObj["m_setting_lib_detail_color"].toString());
    m_setting_lib_remove_color =
        StrIntoQColor(jsonObj["m_setting_lib_remove_color"].toString());
    m_setting_lib_del_color =
        StrIntoQColor(jsonObj["m_setting_lib_del_color"].toString());
    m_tag_manager_tag_Group_item_back_color = StrIntoQColor(
        jsonObj["m_tag_manager_tag_Group_item_back_color"].toString());
    m_popup_win_background_color =
        StrIntoQColor(jsonObj["m_popup_win_background_color"].toString());
    m_popup_win_border_color =
        StrIntoQColor(jsonObj["m_popup_win_border_color"].toString());
    m_popup_win_blue_color =
        StrIntoQColor(jsonObj["m_popup_win_blue_color"].toString());
    m_popup_win_gray_color1 =
        StrIntoQColor(jsonObj["m_popup_win_gray_color1"].toString());
    m_skin_switch_win_scroll_handle =
        StrIntoQColor(jsonObj["m_skin_switch_win_scroll_handle"].toString());
    m_skin_switch_win_scroll_across =
        StrIntoQColor(jsonObj["m_skin_switch_win_scroll_across"].toString());
    m_skin_switch_win_scroll_not_across =
        StrIntoQColor(jsonObj["main_color"].toString());
    m_menu_background_color =
        StrIntoQColor(jsonObj["m_menu_background_color"].toString());
    m_menu_border_color =
        StrIntoQColor(jsonObj["m_menu_border_color"].toString());
    m_menu_separator_line_color =
        StrIntoQColor(jsonObj["m_menu_separator_line_color"].toString());
    m_tool_tip_win_background_color =
        StrIntoQColor(jsonObj["m_tool_tip_win_background_color"].toString());
    m_tool_tip_win_border_color =
        StrIntoQColor(jsonObj["m_tool_tip_win_border_color"].toString());
    m_update_lib_win_start_update_lib_btn_color = StrIntoQColor(
        jsonObj["m_update_lib_win_start_update_lib_btn_color"].toString());
    m_update_lib_win_close_software_btn_color = StrIntoQColor(
        jsonObj["m_update_lib_win_close_software_btn_color"].toString());
    m_update_lib_win_open_other_lib_btn_color = StrIntoQColor(
        jsonObj["m_update_lib_win_open_other_lib_btn_color"].toString());
    m_import_progress_background_color =
        StrIntoQColor(jsonObj["m_import_progress_background_color"].toString());
    m_import_progress_selected_color =
        StrIntoQColor(jsonObj["m_import_progress_selected_color"].toString());
    m_import_progress_unselected_color =
        StrIntoQColor(jsonObj["m_import_progress_unselected_color"].toString());
    m_batchDownloadControlBkColor =
        StrIntoQColor(jsonObj["m_batchDownloadControlBkColor"].toString());
    m_batch_rename_edit_back_color =
        StrIntoQColor(jsonObj["m_batch_rename_edit_back_color"].toString());
    popup_progressbar_select_color =
        StrIntoQColor(jsonObj["popup_progressbar_select_color"].toString());
    popup_progressbar_unselect_color1 =
        StrIntoQColor(jsonObj["popup_progressbar_unselect_color1"].toString());
    popup_progressbar_unselect_color2 =
        StrIntoQColor(jsonObj["popup_progressbar_unselect_color2"].toString());
    m_notification_back_color1 =
        StrIntoQColor(jsonObj["m_notification_back_color1"].toString());
    m_notification_back_color2 =
        StrIntoQColor(jsonObj["m_notification_back_color2"].toString());
    m_update_failed_color =
        StrIntoQColor(jsonObj["m_update_failed_color"].toString());
    m_bubblewin_back_color =
        StrIntoQColor(jsonObj["m_bubblewin_back_color"].toString());
    m_bubblewin_border_color =
        StrIntoQColor(jsonObj["m_bubblewin_border_color"].toString());
    m_bubblewin_line_color =
        StrIntoQColor(jsonObj["m_bubblewin_line_color"].toString());
    m_side_main_color = StrIntoQColor(jsonObj["m_side_main_color"].toString());
    m_side_arrow_color =
        StrIntoQColor(jsonObj["m_side_arrow_color"].toString());
  }
}

void BFSkinSetting::LoadQss() {
  //配置文件路径
  QDir resourcesDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
  if (resourcesDir.dirName() == "MacOS") {
    resourcesDir.cdUp();
  }
#endif
  resourcesDir.cd("Resources");

  QString qss_folder = resourcesDir.absolutePath() + QDir::separator();
  qss_folder += "skin";
  qss_folder += QDir::separator();
  qss_folder += "black";

  //获取路径中的全部css文件
  QList<QString> css_path_list;
  css_path_list =
      QtFlieOperation::GetQtFileOperation()->GetFolderFilesPath(qss_folder);
  if (0 == css_path_list.size()) {
    Q_ASSERT(0);
    return;
  }
  //从list中去除结尾不是.css的文件
  for (auto iter = css_path_list.begin(); iter != css_path_list.end();) {
    QString cur_str = *iter;
    if (!cur_str.endsWith(".css")) {
      iter = css_path_list.erase(iter);
    } else {
      iter++;
    }
  }

  //读取每个css文件中字符串进行拼接
  //  QString all_qss_str = "";
  QString relativePath = QDir::current().relativeFilePath(qss_folder);
  for (auto iter = css_path_list.begin(); iter != css_path_list.end(); iter++) {
    QString cur_str = *iter;
    QFile cur_file(cur_str);
    if (cur_file.exists()) {
      cur_file.open(QFile::ReadOnly);

      QFileInfo info(cur_str);

      QString str;
      str.append(cur_file.readAll());
      str.replace(
          RegExp("url\\s*\\(\\s*([^\\*:\\);]+)\\s*\\)", Qt::CaseSensitive),
          QString("url(%1\\1)").arg(relativePath + "/"));

      m_styleSheetMap[info.baseName()] = str;

      cur_file.close();
    }
  }
}

BFSkinSetting::BFSkinSetting()
    : m_cur_skin_type(BlackMode), m_a_value(255), mFontFamily("") {
  SetSkinColor(m_cur_skin_type);
  SetFontFamilyStr();
}

QColor BFSkinSetting::StrIntoQColor(QString ori_str) {
  QColor need_color = QColor(0, 0, 0, 0);
  QStringList list = ori_str.split(",");
  if (list.size() != 4) {
    return need_color;
  }
  int r = list[0].toInt();
  int g = list[1].toInt();
  int b = list[2].toInt();
  int a = list[3].toInt();
  need_color = QColor(r, g, b, a);
  return need_color;
}

void BFSkinSetting::LoadFloderSvg() {
  auto g_fGlobalDPI = GetDpi();
  // grey
  QString tree_folder_close_grey_path =
      GetSkinResourceAbsolutePath("tree_folder_grey_close.svg");
  QSvgRenderer* render_folder_close_grey =
      new QSvgRenderer(tree_folder_close_grey_path);
  QSize tree_folder_close_grey_size = render_folder_close_grey->defaultSize();
  QImage tree_folder_close_grey_image(
      QSize(tree_folder_close_grey_size.width() * g_fGlobalDPI,
            tree_folder_close_grey_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_grey_image.fill(Qt::transparent);
  QPainter tree_folder_close_grey_painter(&tree_folder_close_grey_image);
  render_folder_close_grey->render(&tree_folder_close_grey_painter);
  m_grey_folder = QPixmap::fromImage(tree_folder_close_grey_image);
  m_grey_folder.setDevicePixelRatio(g_fGlobalDPI);
  // blue
  QString tree_folder_close_blue_path =
      GetSkinResourceAbsolutePath("tree_folder_blue_close.svg");
  QSvgRenderer* render_folder_close_blue =
      new QSvgRenderer(tree_folder_close_blue_path);
  QSize tree_folder_close_blue_size = render_folder_close_blue->defaultSize();
  QImage tree_folder_close_blue_image(
      QSize(tree_folder_close_blue_size.width() * g_fGlobalDPI,
            tree_folder_close_blue_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_blue_image.fill(Qt::transparent);
  QPainter tree_folder_close_blue_painter(&tree_folder_close_blue_image);
  render_folder_close_blue->render(&tree_folder_close_blue_painter);
  m_blue_folder = QPixmap::fromImage(tree_folder_close_blue_image);
  m_blue_folder.setDevicePixelRatio(g_fGlobalDPI);
  // green
  QString tree_folder_close_green_path =
      GetSkinResourceAbsolutePath("tree_folder_green_close.svg");
  QSvgRenderer* render_folder_close_green =
      new QSvgRenderer(tree_folder_close_green_path);
  QSize tree_folder_close_green_size = render_folder_close_green->defaultSize();
  QImage tree_folder_close_green_image(
      QSize(tree_folder_close_green_size.width() * g_fGlobalDPI,
            tree_folder_close_green_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_green_image.fill(Qt::transparent);
  QPainter tree_folder_close_green_painter(&tree_folder_close_green_image);
  render_folder_close_green->render(&tree_folder_close_green_painter);
  m_green_folder = QPixmap::fromImage(tree_folder_close_green_image);
  m_green_folder.setDevicePixelRatio(g_fGlobalDPI);
  // cyan
  QString tree_folder_close_cyan_path =
      GetSkinResourceAbsolutePath("tree_folder_cyan_close.svg");
  QSvgRenderer* render_folder_close_cyan =
      new QSvgRenderer(tree_folder_close_cyan_path);
  QSize tree_folder_close_cyan_size = render_folder_close_cyan->defaultSize();
  QImage tree_folder_close_cyan_image(
      QSize(tree_folder_close_cyan_size.width() * g_fGlobalDPI,
            tree_folder_close_cyan_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_cyan_image.fill(Qt::transparent);
  QPainter tree_folder_close_cyan_painter(&tree_folder_close_cyan_image);
  render_folder_close_cyan->render(&tree_folder_close_cyan_painter);
  m_cyan_folder = QPixmap::fromImage(tree_folder_close_cyan_image);
  m_cyan_folder.setDevicePixelRatio(g_fGlobalDPI);
  // orange
  QString tree_folder_close_orange_path =
      GetSkinResourceAbsolutePath("tree_folder_orange_close.svg");
  QSvgRenderer* render_folder_close_orange =
      new QSvgRenderer(tree_folder_close_orange_path);
  QSize tree_folder_close_orange_size =
      render_folder_close_orange->defaultSize();
  QImage tree_folder_close_orange_image(
      QSize(tree_folder_close_orange_size.width() * g_fGlobalDPI,
            tree_folder_close_orange_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_orange_image.fill(Qt::transparent);
  QPainter tree_folder_close_orange_painter(&tree_folder_close_orange_image);
  render_folder_close_orange->render(&tree_folder_close_orange_painter);
  m_orange_folder = QPixmap::fromImage(tree_folder_close_orange_image);
  m_orange_folder.setDevicePixelRatio(g_fGlobalDPI);
  // yellow
  QString tree_folder_close_yellow_path =
      GetSkinResourceAbsolutePath("tree_folder_yellow_close.svg");
  QSvgRenderer* render_folder_close_yellow =
      new QSvgRenderer(tree_folder_close_yellow_path);
  QSize tree_folder_close_yellow_size =
      render_folder_close_yellow->defaultSize();
  QImage tree_folder_close_yellow_image(
      QSize(tree_folder_close_yellow_size.width() * g_fGlobalDPI,
            tree_folder_close_yellow_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_yellow_image.fill(Qt::transparent);
  QPainter tree_folder_close_yellow_painter(&tree_folder_close_yellow_image);
  render_folder_close_yellow->render(&tree_folder_close_yellow_painter);
  m_yellow_folder = QPixmap::fromImage(tree_folder_close_yellow_image);
  m_yellow_folder.setDevicePixelRatio(g_fGlobalDPI);
  // red
  QString tree_folder_close_red_path =
      GetSkinResourceAbsolutePath("tree_folder_red_close.svg");
  QSvgRenderer* render_folder_close_red =
      new QSvgRenderer(tree_folder_close_red_path);
  QSize tree_folder_close_red_size = render_folder_close_red->defaultSize();
  QImage tree_folder_close_red_image(
      QSize(tree_folder_close_red_size.width() * g_fGlobalDPI,
            tree_folder_close_red_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_red_image.fill(Qt::transparent);
  QPainter tree_folder_close_red_painter(&tree_folder_close_red_image);
  render_folder_close_red->render(&tree_folder_close_red_painter);
  m_red_folder = QPixmap::fromImage(tree_folder_close_red_image);
  m_red_folder.setDevicePixelRatio(g_fGlobalDPI);
  // pink
  QString tree_folder_close_pink_path =
      GetSkinResourceAbsolutePath("tree_folder_pink_close.svg");
  QSvgRenderer* render_folder_close_pink =
      new QSvgRenderer(tree_folder_close_pink_path);
  QSize tree_folder_close_pink_size = render_folder_close_pink->defaultSize();
  QImage tree_folder_close_pink_image(
      QSize(tree_folder_close_pink_size.width() * g_fGlobalDPI,
            tree_folder_close_pink_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_pink_image.fill(Qt::transparent);
  QPainter tree_folder_close_pink_painter(&tree_folder_close_pink_image);
  render_folder_close_pink->render(&tree_folder_close_pink_painter);
  m_pink_folder = QPixmap::fromImage(tree_folder_close_pink_image);
  m_pink_folder.setDevicePixelRatio(g_fGlobalDPI);
  // purple
  QString tree_folder_close_purple_path =
      GetSkinResourceAbsolutePath("tree_folder_purple_close.svg");
  QSvgRenderer* render_folder_close_purple =
      new QSvgRenderer(tree_folder_close_purple_path);
  QSize tree_folder_close_purple_size =
      render_folder_close_purple->defaultSize();
  QImage tree_folder_close_purple_image(
      QSize(tree_folder_close_purple_size.width() * g_fGlobalDPI,
            tree_folder_close_purple_size.height() * g_fGlobalDPI),
      QImage::Format_ARGB32_Premultiplied);
  tree_folder_close_purple_image.fill(Qt::transparent);
  QPainter tree_folder_close_purple_painter(&tree_folder_close_purple_image);
  render_folder_close_purple->render(&tree_folder_close_purple_painter);
  m_purple_folder = QPixmap::fromImage(tree_folder_close_purple_image);
  m_purple_folder.setDevicePixelRatio(g_fGlobalDPI);
}

void BFSkinSetting::SetSkinColor(SkinType type) {
  switch (type) {
    case BlackMode: {
      //黑皮字体颜色
      QVector<QColor> text_color_vec = {
          QColor(224, 231, 250, 255), QColor(162, 171, 195, 255),
          QColor(106, 116, 139, 255), QColor(28, 29, 49, 255)};
      SetTextColor(text_color_vec);

      //黑皮通用色彩
      SetMainColor(QColor(79, 132, 250, 255));
      SetGreenColor(QColor(68, 215, 182, 255));
      SetOrangeColor(QColor(250, 100, 0, 255));
      SetYellowColor(QColor(247, 181, 0, 255));

      SetCommonFirstColor(QColor(224, 231, 250, 255));
      SetCommonSecondColor(QColor(162, 171, 195, 255));
      SetCommonThridColor(QColor(106, 116, 139, 255));
      SetCommonInputColor(QColor(28, 29, 49, 255));

      SetCommonModeLightColor(QColor(38, 39, 53, 255));
      SetCommonModeDarkColor(QColor(31, 32, 45, 255));
      SetStrokePopupColor(QColor(48, 54, 66, 255));
      SetInputAndButtonColor(QColor(132, 142, 169, 255 * 0.2));

      SetOtherButtonColor(QColor(213, 219, 238, 255));
      SetSplitColor(QColor(54, 63, 82, 255));
      SetScrollBarColor(QColor(75, 79, 93, 255));
      SetOptinsColor(QColor(132, 142, 169, 255));
      SetMaskDefaultColor(QColor(0, 0, 0, 0));
      SetMaskFocusColor(QColor(0, 0, 0, 0));

      //模块0: 左侧通用色
      SetLeftWinBackgroundColor(QColor(31, 32, 45, m_a_value));
      //模块1: 左侧标题栏
      //模块2: 左侧资源导入栏
      //模块3: 左侧树
      SetNodeSelectColor(QColor(79, 132, 250, 255));
      SetTreeScrollHandleColor(QColor(106, 116, 139, 255));
      //SetTreeRenameBackColor(QColor(50, 53, 70, 255));

      //模块4: 左侧文件夹搜索
      //模块1: 中侧通用色
      SetMidWinBackgroundColor(QColor(38, 39, 53, m_a_value));
      //模块2：中侧导航栏
      SetNavScrollSliverColor(QColor(106, 116, 139, m_a_value));
      SetNavScrollHandleColor(QColor(79, 88, 108, m_a_value));
      SetNavSearchBackColor(QColor(132, 142, 169, 255 * 0.2));
      //模块3: 中侧筛选
      // SetConditionFilterColorSelectColor(QColor(27, 30, 52, m_a_value));
      // SetConditionFilterControlBackGroundColor(QColor(48, 51, 73,
      // m_a_value)); SetConditionFilterSelectControlBackGroundColor(QColor(132,
      // 142, 169, m_a_value));
      // SetConditionFilterComboxControlTextColor(QColor(28, 29, 49,
      // m_a_value)); SetConditionFilterListItemHoverColor(QColor("#E0E7FA"));
      // SetConditionFilterItemSelectBackColor(QColor(56,60,78));

      //模块4：中侧列表预览
      SetListPreviewFolderFrontColor(QColor(106, 116, 139));
      SetListPreviewFolderBehindColor(QColor(162, 171, 195));
      SetListPreViewFormatBackColor(QColor(0, 0, 0, 127));
      SetListPreViewScrollHandleColor(QColor(75, 79, 93, 255));
      SetListPreViewScrollHandleHoverColor(QColor(106, 116, 139, 255));
      SetListPreviewRenameBackColor(QColor(50, 53, 70, 255));

      //模块1: 右侧通用色
      SetRightWinBackgroundColor(QColor(31, 32, 45, m_a_value));
      SetRightWinBlue1(QColor(79, 132, 250, 255));
      setRightScrollHandleColor(QColor(75, 79, 93, 255));

      //模块2:右侧信息栏
      SetRightInfoExportBtnColor(QColor(132, 142, 169, 255 * 0.2));
      SetRightNameEditBackColor(QColor(132, 142, 169, 255 * 0.2));
      setRightFont1(QColor(224, 231, 250, 255));
      setRightTagFontColor(QColor(28, 29, 49, 255));
      setRightTagCrossColor(QColor(79, 88, 108, 255));
      setRightResInfoFontColor(QColor(162, 171, 195, 255));

      //模块3:右侧标签弹窗
      setTagPopupTabStrFontColor(QColor(233, 237, 246, 255));
      setTagPopupTabBackUnselectedColor(QColor(132, 142, 169, 255 * 0.2));
      setTagPopupTabBackSelectedColor(QColor(79, 132, 250, 255));
      setTagPopupClassifyFontColor(QColor(162, 171, 195, 255));
      setTagPopupCreateTip(QColor(224, 231, 250, 255));

      //标签管理
      //通用
      setTagManagerFontColor1(QColor(233, 237, 246, 255));
      setTagManagerFontColor2(QColor(224, 231, 250, 255));
      setTagManagerFontColor3(QColor(162, 171, 195, 255));
      setTagManagerSelectedColor(QColor(79, 132, 250, 255));
      setTagManagerTagItemRightFontColor(QColor(106, 116, 139, 255));
      setTagManagerTagItemInitBackColor(QColor(213, 219, 238, 255));

      //偏好设置
      //左侧按钮
      setSettingBtnNormalColor(QColor(224, 231, 250, 255));
      setSettingBtnSelectedColor(QColor(79, 132, 250, 255));
      //格式设置
      setSettingFormatImageColor(QColor(79, 132, 250, 255));
      setSettingFormatFileColor(QColor(247, 181, 0, 255));
      setSettingFormatSourceColor(QColor(68, 215, 182, 255));
      setSettingFormatOtherColor(QColor(207, 103, 248, 255));
      setSettingSpacingLineColor(QColor(54, 63, 82, 255));
      setSettingFormatItemBackColor(QColor(132, 142, 169, 255 * 0.2));
      //素材库设设置
      setSettingLibComboxBackColor(QColor(132, 142, 169, 255));
      setSettingLibSwitchColor(QColor(79, 132, 250, 255));
      setSettingLibMergehColor(QColor(68, 215, 182, 255));
      setSettingLibDetailColor(QColor(247, 181, 0, 255));
      setSettingLibRemoveColor(QColor(192, 83, 254, 255));
      setSettingLibDelColor(QColor(250, 100, 0, 255));

      //模块0：标签分类
      setTagManagerTagGroupItemBackColor(QColor(132, 142, 169, 255 * 0.2));

      //其他模块
      //所有弹窗通用模块
      SetPopupWinBackgroundColor(QColor(28, 29, 49, 255));
     // SetPopupWinBorderColor(QColor(48, 54, 66, 255));
      SetPopupWinBlueColor(QColor(79, 132, 250, 255));
      SetPopupWinGrayColor1(QColor(48, 51, 73, 255));

      //皮肤切换弹窗设置
      SetSkinSwitchWinScrollHandle(QColor(79, 132, 250, 255));
      SetSkinSwitchWinScrollAcross(QColor(79, 132, 250, 255));
      SetSkinSwitchWinScrollNotAcross(QColor(132, 142, 169, 255));

      //菜单模块(菜单不受透明度影响)
      SetMenuBackgroundColor(QColor(28, 29, 49, 255));
      SetMenuBorderColor(QColor(48, 54, 66, 255));
      SetMenuSeparatorLineColor(QColor(54, 63, 82, 255));

      //悬浮弹窗模块
      SetToolTipBackgroundColor(QColor(28, 29, 49, 255));
      SetToolTipBorderColor(QColor(48, 54, 66, 255));

      //升级库弹窗
      SetUpdateLibWinStartUpdateLibColor(QColor(79, 132, 250));
      SetUpdateLibWinCloseSoftWareColor(QColor(48, 51, 73));
      SetUpdateLibWinOpenOtherLibColor(QColor(132, 142, 169));

      //导入滚动条模块
      SetImportProgressBackColor(QColor(31, 32, 45));
      SetImportProgressSelectedColor(QColor(79, 132, 250));
      SetImportProgressUnSelectedColor(QColor(64, 65, 76));

      //批量下载
      setBatchDownloadControlsBkColor(QColor(48, 51, 73));

      //批量重命名
      SetBatchRenameEditBackColor(QColor(48, 51, 73));

      //所有弹窗进度条模块
      SetPopupProgressBarSelectColor(QColor(79, 132, 250, 255));
      SetPopupProgressBarUnSelectColor1(QColor(48, 51, 73));
      SetPopupProgressBarUnSelectColor2(QColor(132, 142, 169));

      //通知悬浮窗
      SetNotificationBackColor1(QColor(79, 132, 250, 255));
      SetNotificationBackColor2(QColor(48, 51, 73, 255));

      //更新模块
      SetUpdateFailedColor(QColor(250, 100, 0, 255));

      //气泡弹窗
      SetBubbleWinBackColor(QColor(28, 29, 49, 255));
      SetBubbleWinBorderColor(QColor(48, 54, 66, 255));
      SetBubbleWinLineColor(QColor(54, 63, 82, 255));
    }

    break;

    case WhiteMode: {
    } break;

    default:
      break;
  }
}

void BFSkinSetting::SetFontFamilyStr() { mFontFamily = "Microsoft Yahei"; }

void BFSkinSetting::SetAlphaValue(int value) {
  //设置alpha值
  m_a_value = value;

  //管理器内颜色重新加载
  SetSkinColor(m_cur_skin_type);
}

BFSkinSetting::~BFSkinSetting() {}
