#include"CIndexToCopyResultDialog.h"
#include<QDebug>
#include<QDesktopServices>
#include<QUrl>
#include<../bfskinmodule/bfskinsetting.h>
#include<QEvent>
# pragma execution_character_set("utf-8") 

class CResourceManagerWidget;

CIndexToCopyResultDialog::CIndexToCopyResultDialog(QWidget * parent)
	:CPopupDialog(parent, true, true, false)
{
  this->setFixedSize(400, 229);
  this->InitUi();
  connect(m_okBtn, SIGNAL(clicked()), this, SLOT(slotOkClicked()));
  connect(m_failedResBtn, SIGNAL(clicked()), this, SLOT(slotFailedClicked()));
  connect(m_load_path, SIGNAL(clicked()), this, SLOT(slotRelocationPaht()));
  connect(m_delete_source, SIGNAL(clicked()), this, SLOT(slotDelSouce()));
  connect(m_not_handle, SIGNAL(clicked()), this, SLOT(slotCancelClicked()));
}

CIndexToCopyResultDialog::~CIndexToCopyResultDialog()
{
}

void CIndexToCopyResultDialog::SwitchStyleSheet()
{
  //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓索引结果模式
  //索引结果大标题窗口
  QString lab_title_str = "color:"+ BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  m_lab_title->setStyleSheet(lab_title_str);

  //转换成功数量标题
  QString lab_success_title_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  m_lab_success_title->setStyleSheet(lab_success_title_str);

  //转换失败数量标题
  QString lab_failed_title_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  m_lab_failed_title->setStyleSheet(lab_failed_title_str);

  //成功数量 //蓝湖-主色
  QString lab_success_str = "color:" + BFSkinSetting::GetInstance()->GetMainColor().name(QColor::HexArgb);
  m_lab_success->setStyleSheet(lab_success_str);

  //失败数量//蓝湖-辅色-黄
  QString lab_failed_str = "color:" + BFSkinSetting::GetInstance()->GetYellowColor().name(QColor::HexArgb);
  m_lab_failed->setStyleSheet(lab_failed_str);

  //OK按钮
  QString btn_ok_str;
  btn_ok_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  btn_ok_str += ";border-radius:14px;background-color:";
  btn_ok_str += BFSkinSetting::GetInstance()->GetMainColor().name(QColor::HexArgb);
  btn_ok_str += ";";
  m_okBtn->setStyleSheet(btn_ok_str);


  //为什么转换失败
  QString lab_icon_str = GetSkinResource("common_question_normal.svg");
  m_failed_why_lab->setStyleSheet(lab_icon_str);

  //失败素材按钮
  QString btn_failed_str;
  btn_failed_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  btn_failed_str += ";border-radius:14px;background-color:";
  btn_failed_str += BFSkinSetting::GetInstance()->GetInputAndButtonColor().name(QColor::HexArgb);
  btn_failed_str += ";";
  m_failedResBtn->setStyleSheet(btn_failed_str);

  //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓索引路径丢失模式
    //路径丢失标题
  QString lose_lab_title_str= "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  m_lose_lab_title->setStyleSheet(lose_lab_title_str);

  //路径丢失内容
  QString lose_lab_context_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  m_lab_context->setStyleSheet(lose_lab_context_str);

  //路径丢失为什么丢失图标
  QString lose_lab_why_lose_icon_str = GetSkinResource("common_question_normal.svg");
  m_why_lost_icon->setStyleSheet(lose_lab_why_lose_icon_str);

  //路径丢失为什么丢失文字
  QString lose_lab_why_lose_text_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb);
  m_why_lose_text->setStyleSheet(lose_lab_why_lose_text_str);

  //路径丢失加载路径按钮
  QString lose_lab_load_path_str;
  lose_lab_load_path_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  lose_lab_load_path_str += ";border-radius:14px;background-color:";
  lose_lab_load_path_str += BFSkinSetting::GetInstance()->GetMainColor().name(QColor::HexArgb);
  lose_lab_load_path_str += ";";
  m_load_path->setStyleSheet(lose_lab_load_path_str);

  //路径丢失删除资源按钮
  QString lose_lab_delete_source_str;
  lose_lab_delete_source_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  lose_lab_delete_source_str += ";border-radius:14px;background-color:";
  lose_lab_delete_source_str += BFSkinSetting::GetInstance()->GetInputAndButtonColor().name(QColor::HexArgb);
  lose_lab_delete_source_str += ";";
  m_delete_source->setStyleSheet(lose_lab_delete_source_str);

  //路径丢失删除资源按钮
  QString lose_lab_not_handle_str;
  lose_lab_not_handle_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  lose_lab_not_handle_str += ";border-radius:14px;background-color:";
  lose_lab_not_handle_str += BFSkinSetting::GetInstance()->GetInputAndButtonColor().name(QColor::HexArgb);
  lose_lab_not_handle_str += ";";
  m_not_handle->setStyleSheet(lose_lab_not_handle_str);
}

void CIndexToCopyResultDialog::slotOkClicked()
{
  int ret = NO_DEL_FILE;
	return QDialog::done(ret);
}

void CIndexToCopyResultDialog::slotFailedClicked()
{
  int ret = CheckFailedFile;
  return QDialog::done(ret);
}

void CIndexToCopyResultDialog::slotCancelClicked()
{
	this->close();
}

void CIndexToCopyResultDialog::slotRelocationPaht()
{
	QDialog::done(RE_LOACATION);
}

void CIndexToCopyResultDialog::slotDelSouce() { QDialog::done(DEL_FILE); }

bool CIndexToCopyResultDialog::eventFilter(QObject* target, QEvent* event)
{
	if (target == m_why_lost_icon && event->type() == QEvent::MouseButtonPress)
	{
		QDesktopServices::openUrl(QUrl("https://www.billfish.cn/soft-b53-lose"));
	}
	if (target == m_why_lose_text && event->type() == QEvent::MouseButtonPress)
	{
		QDesktopServices::openUrl(QUrl("https://www.billfish.cn/soft-b53-lose"));
	}
	if (target == m_failed_why_lab && event->type() == QEvent::MouseButtonPress)
	{
		QDesktopServices::openUrl(QUrl("https://www.billfish.cn/soft-b38-lose"));
	}
	return   CPopupDialog::eventFilter(target, event); ;
}


int CIndexToCopyResultDialog::showIndexLostDialog() {
  //蓝狐上大小
  this->setFixedSize(364, 271);


  //开放关闭显示
  m_failedResBtn->hide();
  m_okBtn->hide();
  m_lab_title->hide();
  m_lab_success_title->hide();
  m_lab_failed_title->hide();
  m_lab_success->hide();
  m_lab_failed->hide();
  m_failed_why_lab->hide();

  m_lose_lab_title->show();
  m_lab_context->show();
  m_why_lost_icon->show();
  m_why_lose_text->show();
  m_load_path->show();
  m_delete_source->show();
  m_not_handle->show();


  return this->exec();
}

int CIndexToCopyResultDialog::showIndexToCopyResultDialog()
{
  //蓝狐上大小
  this->setFixedSize(304, 246);

	//如果存在失败素材，显示【失败素材按钮】,否则不显示
	bool failedBtn = m_failedCount > 0 ? true:false;

	m_failedResBtn->setVisible(failedBtn);
  m_okBtn->setVisible(true);
  m_lab_title->show();
  m_lab_success_title->show();
  m_lab_failed_title->show();
  m_lab_success->show();
  m_lab_failed->show();
  m_failed_why_lab->show();

  //关闭显示
  m_lose_lab_title->hide();
  m_lab_context->hide();
  m_why_lost_icon->hide();
  m_why_lose_text->hide();
  m_load_path->hide();
  m_delete_source->hide();
  m_not_handle->hide();

	//调整按钮位置
	//如果存在失败素材
	if (failedBtn)
	{}
	//如果不存在失败素材
	else
	{
    //将ok按钮x移动到中间位置
    int new_ok_x = (this->width()-m_okBtn->width()) / 2;
    int old_y = m_okBtn->y();
		m_okBtn->move(new_ok_x, old_y);
	}
	return this->exec();
}

void CIndexToCopyResultDialog::setSucAndFailedCount(QVector<qint64> fail_pho_vec, int failedCount, int sucCount)
{
  m_failed_pho_vec = fail_pho_vec;
  m_failedCount = failedCount;
  m_sucCount = sucCount;

  //界面赋值
  m_lab_success->setText(QString::number(m_sucCount));
  m_lab_failed->setText(QString::number(m_failedCount));
}

void CIndexToCopyResultDialog::InitUi()
{
  //备选字体
  QFont font_13;
  font_13.setPixelSize(13);
  font_13.setFamily(QString::fromUtf8("Microsoft Yahei"));

  QFont font_16;
  font_16.setPixelSize(16);
  font_16.setFamily(QString::fromUtf8("Microsoft Yahei"));

  QFont font_12;
  font_12.setPixelSize(12);
  font_12.setFamily(QString::fromUtf8("Microsoft Yahei"));

  //自身设置
  this->SetTitleLabelVisible(false);
  this->SetTitleLabelText("");
  this->SetCloseButtonVisible(true);

  //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓索引结果模式
  //索引结果大标题窗口
  m_lab_title = new QLabel(this);
  m_lab_title->hide();
  m_lab_title->setFixedSize(96,16);
  m_lab_title->move(104,30);
  m_lab_title->setText(QString::fromUtf8("素材转换完成"));
  m_lab_title->setFont(font_16);

  //转换成功数量标题
  m_lab_success_title = new QLabel(this);
  m_lab_success_title->hide();
  m_lab_success_title->setFixedSize(78, 13);
  m_lab_success_title->move(50, 86);
  m_lab_success_title->setText(QString::fromUtf8("转换成功数量"));
  m_lab_success_title->setFont(font_13);

  //转换失败数量标题
  m_lab_failed_title = new QLabel(this);
  m_lab_failed_title->hide();
  m_lab_failed_title->setFixedSize(78, 13);
  m_lab_failed_title->move(176, 86);
  m_lab_failed_title->setText(QString::fromUtf8("转换失败数量"));
  m_lab_failed_title->setFont(font_13);


  //为什么转换失败
  m_failed_why_lab = new QLabel(this);
  m_failed_why_lab->hide();
  m_failed_why_lab->setFixedSize(14, 14);
  m_failed_why_lab->move(256, 85);
  m_failed_why_lab->setText(QString::fromUtf8(""));
  m_failed_why_lab->setFont(font_13);
  m_failed_why_lab->installEventFilter(this);


  //成功数量(实际情况和蓝湖位置不一致)
  m_lab_success = new QLabel(this);
  m_lab_success->hide();
  m_lab_success->setFixedSize(78, 18);
  m_lab_success->move(50, 117);
  m_lab_success->setText(QString::fromUtf8("XX"));
  m_lab_success->setAlignment(Qt::AlignHCenter);
  m_lab_success->setFont(font_16);

  //失败数量(实际情况和蓝湖位置不一致)
  m_lab_failed = new QLabel(this);
  m_lab_failed->hide();
  m_lab_failed->setFixedSize(78, 18);
  m_lab_failed->move(176, 117);
  m_lab_failed->setText(QString::fromUtf8("XX"));
  m_lab_failed->setAlignment(Qt::AlignHCenter);
  m_lab_failed->setFont(font_16);

  //OK按钮
  m_okBtn = new QPushButton(this);
  m_okBtn->hide();
  m_okBtn->setFixedSize(106, 28);
  m_okBtn->move(34, 188);
  m_okBtn->setText(QString::fromUtf8("好的"));
  m_okBtn->setFont(font_13);

  //失败素材按钮
  m_failedResBtn = new QPushButton(this);
  m_failedResBtn->hide();
  m_failedResBtn->setFixedSize(106, 28);
  m_failedResBtn->move(164, 188);
  m_failedResBtn->setText(QString::fromUtf8("失败素材"));
  m_failedResBtn->setFont(font_13);




  //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓索引路径丢失模式
  //路径丢失标题
  m_lose_lab_title = new QLabel(this);
  m_lose_lab_title->hide();
  m_lose_lab_title->setFixedSize(96, 16);
  m_lose_lab_title->move(134, 30);
  m_lose_lab_title->setText(QString::fromUtf8("索引路径丢失"));
  m_lose_lab_title->setFont(font_16);

 //路径丢失内容
  m_lab_context = new QLabel(this);
  m_lab_context->hide();
  m_lab_context->setFixedSize(300, 100);
  m_lab_context->move(30, 74);
  m_lab_context->setText(QString::fromUtf8("<p style='line-height:20px'>该素材的索引路径已失效，对原位置素材进行改名或移动都可能造成路径的丢失，您需要重新加载原图才能继续操作</p>"));
  m_lab_context->setWordWrap(true);
  m_lab_context->setFont(font_13);
  m_lab_context->setAlignment(Qt::AlignLeft|Qt::AlignTop);

//路径丢失为什么丢失图标
  m_why_lost_icon = new QLabel(this);
  m_why_lost_icon->hide();
  m_why_lost_icon->setFixedSize(14, 14);
  m_why_lost_icon->move(30, 149);
  m_why_lost_icon->setText("");
  m_why_lost_icon->setFont(font_13);
  m_why_lost_icon->installEventFilter(this);

//路径丢失为什么丢失文字
  m_why_lose_text = new QLabel(this);
  m_why_lose_text->hide();
  m_why_lose_text->setFixedSize(84, 14);
  m_why_lose_text->move(50, 150);
  m_why_lose_text->setText(QString::fromUtf8("为什么会失效"));
  m_why_lose_text->setFont(font_12);
  m_why_lose_text->installEventFilter(this);

//路径丢失加载路径按钮
  m_load_path = new QPushButton(this);
  m_load_path->hide();
  m_load_path->setFixedSize(90, 28);
  m_load_path->move(31, 213);
  m_load_path->setText(QString::fromUtf8("加载路径"));
  m_load_path->setFont(font_13);

//路径丢失删除资源按钮
  m_delete_source = new QPushButton(this);
  m_delete_source->hide();
  m_delete_source->setFixedSize(90, 28);
  m_delete_source->move(137, 213);
  m_delete_source->setText(QString::fromUtf8("删除素材"));
  m_delete_source->setFont(font_13);


 //路径丢失删除资源按钮
  m_not_handle = new QPushButton(this);
  m_not_handle->hide();
  m_not_handle->setFixedSize(90, 28);
  m_not_handle->move(243, 213);
  m_not_handle->setText(QString::fromUtf8("暂不处理"));
  m_not_handle->setFont(font_13);



  //切换样式表
  this->SwitchStyleSheet();
}










//CIndexToCopyDelSourceDialog::CIndexToCopyDelSourceDialog(QWidget * parent):CPopupDialog(parent, true, true, false)
//{
//  this->InitUi();
//
//	connect(m_noDelBtn, SIGNAL(clicked()), this, SLOT(slotNoDel()));
//	connect(m_delBtn, SIGNAL(clicked()), this, SLOT(slotDel()));
//  connect(m_is_no_caution_box, SIGNAL(toggled(bool)), this, SLOT(SlotNoCation(bool)));
//}
//
//CIndexToCopyDelSourceDialog::~CIndexToCopyDelSourceDialog()
//{
//}
//
//void CIndexToCopyDelSourceDialog::SwitchStyleSheet()
//{
//  //大标题窗口
//  QString lab_title_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
//  m_lab_title->setStyleSheet(lab_title_str);
//
//  //内容
//  QString lab_context_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
//  m_lab_context->setStyleSheet(lab_context_str);
//
//  //不再提醒按钮
//  QString no_caution_box_str = "QCheckBox{color:" + BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb) + ";}QCheckBox::indicator{ width:13px; height:13px;}" +
//    "QCheckBox::indicator:unchecked{" + GetSkinResource("choice_normal.svg");
//  no_caution_box_str += ";}QCheckBox::indicator:checked{" + GetSkinResource("choice_single_select.svg");
//  no_caution_box_str += "}";
//  m_is_no_caution_box->setStyleSheet(no_caution_box_str);
//  qDebug() << no_caution_box_str;
//
//  //不删除按钮
//  QString btn_no_delete_str;
//  btn_no_delete_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
//  btn_no_delete_str += ";border-radius:14px;background-color:";
//  btn_no_delete_str += BFSkinSetting::GetInstance()->GetMainColor().name(QColor::HexArgb);
//  btn_no_delete_str += ";";
//  m_noDelBtn->setStyleSheet(btn_no_delete_str);
//
//  //删除按钮
//  QString btn_delete_str;
//  btn_delete_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
//  btn_delete_str += ";border-radius:14px;background-color:";
//  btn_delete_str += BFSkinSetting::GetInstance()->GetInputAndButtonColor().name(QColor::HexArgb);
//  btn_delete_str += ";";
//  m_delBtn->setStyleSheet(btn_delete_str);
//}
//
//void CIndexToCopyDelSourceDialog::slotNoDel()
//{
//	QDialog::done(NO_DEL_ORIGIN_FILE);
//}
//
//void CIndexToCopyDelSourceDialog::slotDel()
//{
//	QDialog::done(DEL_ORIGIN_FILE);
//}
//
//void CIndexToCopyDelSourceDialog::SlotNoCation(bool flag)
//{
//}
//
//void CIndexToCopyDelSourceDialog::InitUi()
//{
//  //自身
//  this->setFixedSize(364, 204);
//  this->SetTitleLabelVisible(false);
//  this->SetTitleLabelText("");
//  this->SetCloseButtonVisible(true);
//
//  //备选字体
//  QFont font_13;
//  font_13.setPixelSize(13);
//  font_13.setFamily(QString::fromUtf8("Microsoft Yahei"));
//
//  QFont font_16;
//  font_16.setPixelSize(16);
//  font_16.setFamily(QString::fromUtf8("Microsoft Yahei"));
//
//  QFont font_12;
//  font_12.setPixelSize(12);
//  font_12.setFamily(QString::fromUtf8("Microsoft Yahei"));
//
//  //标题
//  m_lab_title = new QLabel(this);
//  m_lab_title->show();
//  m_lab_title->setFixedSize(144, 16);
//  m_lab_title->move(110, 30);
//  m_lab_title->setText(QString::fromUtf8("是否删除原路径文件"));
//  m_lab_title->setFont(font_16);
//
//  //内容
//  m_lab_context = new QLabel(this);
//  m_lab_context->show();
//  m_lab_context->setFixedSize(299, 40);
//  m_lab_context->move(30, 76);
//  m_lab_context->setWordWrap(true);
//  m_lab_context->setText(QString::fromUtf8("<p style='line-height:20px'>相关素材已经复制到当前素材库所在文件夹内，您是否需要删除旧的原路径上的文件</p>"));
//  m_lab_context->setFont(font_13);
//
//  //不再提醒弹窗
//  m_is_no_caution_box = new QCheckBox(this);
//  m_is_no_caution_box->show();
//  m_is_no_caution_box->setFixedSize(100, 13);
//  m_is_no_caution_box->move(30, 154);
//  m_is_no_caution_box->setText(QString::fromUtf8("不再提醒"));
//  m_is_no_caution_box->setFont(font_12);
//
//  //不删除按钮
//  m_noDelBtn = new QPushButton(this);
//  m_noDelBtn->show();
//  m_noDelBtn->setFixedSize(96, 28);
//  m_noDelBtn->move(126, 146);
//  m_noDelBtn->setText(QString::fromUtf8("不删除"));
//  m_noDelBtn->setFont(font_13);
//
//  //删除按钮
//  m_delBtn = new QPushButton(this);
//  m_delBtn->show();
//  m_delBtn->setFixedSize(96, 28);
//  m_delBtn->move(238, 146);
//  m_delBtn->setText(QString::fromUtf8("删除"));
//  m_delBtn->setFont(font_13);
//
//  //改变样式表
//  this->SwitchStyleSheet();
//}
