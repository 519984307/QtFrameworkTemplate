#include "CListSearchLineEdit.h"
#include "ui_CListSearchLineEdit.h"
#include "bfskinmodule/bfskinsetting.h"
#include <QEvent>
CListSearchLineEdit::CListSearchLineEdit(QWidget *parent)
    : QWidget(parent), m_list_widget(NULL) {
	ui = new Ui::CListSearchLineEdit();
	ui->setupUi(this);


    InitUi();
    SwitchStyleSheet();
}

CListSearchLineEdit::~CListSearchLineEdit()
{
	delete ui;
}

void CListSearchLineEdit::SetSearchTipText(QString text) {
  m_tips_text = text;
  ui->lineEdit->setPlaceholderText(m_tips_text);
}

void CListSearchLineEdit::ClearSearch(bool is_send_sig) {
  if (is_send_sig) {
    ui->lineEdit->clear();
  } else {
    ui->lineEdit->blockSignals(true);
    ui->lineEdit->clear();
    ui->lineEdit->blockSignals(false);
  }
}

void CListSearchLineEdit::ReSearchCurText() {
  SlotSearchTextChanged(ui->lineEdit->text());
}

void CListSearchLineEdit::InitUi() {
  //自身
  this->setAttribute(Qt::WA_InputMethodEnabled, true);  //接受输入法事件

  //图标label


   //搜索lineedit
   //输入框
   //字体
   QFont input_font;
   input_font.setPixelSize(12);
   input_font.setFamily(QString::fromUtf8("Microsoft Yahei"));
   ui->lineEdit->setFont(input_font);
   ui->lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
   //为输入字体
   ui->lineEdit->setPlaceholderText(QString::fromUtf8(""));
   ui->lineEdit->setAttribute(Qt::WA_InputMethodEnabled,true);  //接受输入法事件
   ui->lineEdit->installEventFilter(this);
   //ui->edit_search_input->setClearButtonEnabled(false);
   bool ret = connect(ui->lineEdit, SIGNAL(textChanged(QString)),
                      this, SLOT(SlotSearchTextChanged(QString)));
#ifdef __APPLE__
    ui->lineEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
#endif

}

void CListSearchLineEdit::SwitchStyleSheet() {
  //自身
  QString style_wid ="background-color:rgba(0,0,0,0);";
  this->setStyleSheet(style_wid);

  //main_wid
  QString style_main_wid = "border:0px;border-radius:6px;background-color:";
  style_main_wid +=
      BFSkinSetting::GetInstance()->GetConditionFilterSearchBackColor().name(QColor::HexArgb);
  style_main_wid += ";";
  ui->wid_main->setStyleSheet(style_main_wid);

  //搜索图标按钮
  QString btn_search_icon = "QLabel{border:0px;" +
                            BFSkinSetting::GetInstance()->GetResourcePath(
                                "nav_picview_search_normal.svg") +
                            "}";
                            //"QPushButton:hover{" +
                            //BFSkinSetting::GetInstance()->GetResourcePath(
                            //    "nav_picview_search_hover.svg") +
                            //"}";
  ui->lab_icon->setStyleSheet(btn_search_icon);


  //搜索输入框
  QString edit_input_str =
      "color:" +
      BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb);
  edit_input_str += ";background-color:rgba(0,0,0,0);border:0px;";
  ui->lineEdit->setStyleSheet(edit_input_str);

}

bool CListSearchLineEdit::eventFilter(QObject* watched, QEvent* event) {
  if (watched == ui->lineEdit) {
    if (event->type() == QEvent::FocusIn) {
      //搜索输入框
      QString style_main_wid =
          "border-radius:6px;background-color:rgba(31,32,45,255);border:1px "
          "solid;border-color:rgba(172, 178, 198,255);";
      ui->wid_main->setStyleSheet(style_main_wid);

    } else if (event->type() == QEvent::FocusOut) {
      //搜索状态
      QString style_main_wid = "border-radius:6px;border:0px;background-color:";
      style_main_wid += BFSkinSetting::GetInstance()
                            ->GetConditionFilterSearchBackColor()
                            .name(QColor::HexArgb);
      style_main_wid += ";";
      ui->wid_main->setStyleSheet(style_main_wid);
    }
  }

  return QWidget::eventFilter(watched, event);
}

void CListSearchLineEdit::SlotSearchTextChanged(QString str) {
    if (!m_list_widget) {
    return;
    }

    QString cur_str = str;

    if (cur_str.isEmpty()){
        //将m_list_widget所有项设置为显示
        int count = m_list_widget->count();
        for (int i = 0; i < count; i++) {
        QListWidgetItem* item = m_list_widget->item(i);
        item->setHidden(false);
        }
    }
    else {

       //判断m_list_widget的项文字如果包含所属相关文字则保留，否则隐藏
      int count = m_list_widget->count();
      for (int i = 0; i < count; i++) {
        QListWidgetItem* item = m_list_widget->item(i);

        QString item_name = item->data(Qt::UserRole + 1).toString();
        if (item_name.contains(str, Qt::CaseInsensitive)) {
          item->setHidden(false);
        } else {
        item->setHidden(true);
        }
      }
    }
}
