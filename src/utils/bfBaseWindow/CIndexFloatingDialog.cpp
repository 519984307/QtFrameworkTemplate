#include "CIndexFloatingDialog.h"
#include "../bfskinmodule/bfskinsetting.h"
#include "BFQtUtils.h"
#include "BFSkinManager.h"
#include "CPopupTitleBarWidget.h"
#include <QApplication>
#include <QDesktopServices>
#include <QScrollBar>
#include <QTextBlock>
#include <QTimer>

CIndexFloatingDialog* CIndexFloatingDialog::m_instance = nullptr;
CIndexFloatingDialog::CIndexFloatingDialog(QString text, QWidget* parent,
                                           bool bClose, bool bTitle,
                                           bool bRepaint /*
                                           bool bDelete = true,
                                           bool bIcon = true*/
                                           )
    : CPopupDialog(parent, bClose, bTitle, bRepaint, true, false),
      m_format_check_timer(NULL) {
  //设置下各个字体
  font_10.setFamily("Microsoft YaHei");
  font_10.setPixelSize(10);

  font_11.setFamily("Microsoft YaHei");
  font_11.setPixelSize(11);

  font_12.setFamily("Microsoft YaHei");
  font_12.setPixelSize(12);

  font_13.setFamily("Microsoft YaHei");
  font_13.setPixelSize(13);

  this->setFixedSize(230, 92);
  this->setAttribute(Qt::WA_DeleteOnClose, false);

  //第一行label
  m_textLabel = new QLabel(text, this);
  m_textLabel->move(10, 10);
  m_textLabel->setFixedSize(230, 25);
  m_textLabel->setAlignment(Qt::AlignTop);
  m_textLabel->setOpenExternalLinks(true);
  m_textLabel->setWordWrap(true);
  m_textLabel->setFont(font_12);
  connect(m_textLabel, &QLabel::linkActivated, this,
          &CIndexFloatingDialog::SlotFirstLabLinkActivated);

  //第二行label
  m_secondTextLabel = new QLabel(text, this);
  m_secondTextLabel->move(10, 30);
  m_secondTextLabel->setFixedSize(230, 15);
  m_secondTextLabel->setAlignment(Qt::AlignTop);
  m_secondTextLabel->setOpenExternalLinks(false);
  m_secondTextLabel->setWordWrap(true);
  m_secondTextLabel->setFont(font_12);
  connect(m_secondTextLabel, &QLabel::linkActivated, this,
          &CIndexFloatingDialog::SlotSecondLabLinkActivated);

  //第三行label
  m_thirdTextLabel = new QLabel(text, this);
  m_thirdTextLabel->move(10, 50);
  m_thirdTextLabel->setFixedSize(230, 15);
  m_thirdTextLabel->setAlignment(Qt::AlignTop);
  m_thirdTextLabel->setOpenExternalLinks(false);
  m_thirdTextLabel->setWordWrap(true);
  m_thirdTextLabel->setFont(font_12);
  connect(m_thirdTextLabel, &QLabel::linkActivated, this,
          &CIndexFloatingDialog::SlotThirdLabLinkActivated);

  //第四行label
  m_fourthTextLabel = new QLabel(text, this);
  m_fourthTextLabel->move(10, 70);
  m_fourthTextLabel->setFixedSize(230, 15);
  m_fourthTextLabel->setAlignment(Qt::AlignTop);
  m_fourthTextLabel->setOpenExternalLinks(false);
  m_fourthTextLabel->setWordWrap(true);
  m_fourthTextLabel->setFont(font_12);
  connect(m_fourthTextLabel, &QLabel::linkActivated, this,
          &CIndexFloatingDialog::SlotFourthLabLinkActivated);

  //网址控件
  m_urlEdit = new QTextEdit(this);
  m_urlEdit->setFont(font_12);
  m_urlEdit->setFixedSize(180, 50);
  m_urlEdit->setAcceptRichText(false);
  m_urlEdit->setContextMenuPolicy(Qt::NoContextMenu);
  m_urlEdit->setPlaceholderText(QString::fromUtf8("请输入网址"));
  m_urlEdit->setWordWrapMode(QTextOption::WrapAnywhere);
  connect(m_urlEdit, &QTextEdit::textChanged, [=]() { m_urlChanged = true; });
  m_browserLookBtn = new QPushButton(QString::fromUtf8("浏览器查看"), this);
  m_browserLookBtn->setFont(font_12);
  m_browserLookBtn->setFixedSize(80, 22);
  connect(m_browserLookBtn, &QPushButton::clicked, [=]() {
    if (!m_urlEdit->toPlainText().isEmpty()) {
      auto sourceUrl = m_urlEdit->toPlainText();

      ////
      ///openUrl打开本地路径失败，所以先用正则表达式判断区分网址。网址和本地路径区别处理
      //         //匹配网址正则表达式
      //         QRegExp rx(
      //             "(https?|ftp|file)://[-A-Za-z0-9+&@#/"
      //             "%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");
      //         if (rx.exactMatch(sourceUrl))
      bool ret = QDesktopServices::openUrl(sourceUrl);
      /*           else
                     BFQtUtils::showInGraphicalShell(sourceUrl);*/
    }
  });

  //备注控件
  m_noteEdit = new QTextEdit(this);
  m_noteEdit->setFont(font_12);
  m_noteEdit->setFixedSize(180, 96);
  m_noteEdit->setAcceptRichText(false);
  m_noteEdit->setContextMenuPolicy(Qt::NoContextMenu);
  m_noteEdit->setPlaceholderText(QString::fromUtf8("请输入备注"));
  m_noteEdit->setWordWrapMode(QTextOption::WrapAnywhere);
  connect(m_noteEdit, &QTextEdit::textChanged, [=]() { m_noteChanged = true; });
  //去除字符数量限制
  // connect(m_noteEdit, &QTextEdit::textChanged, [=]()
  //{
  ////限制备注最长为60
  // QString text = m_noteEdit->toPlainText();
  // if (text.length() > 60)
  //{
  //	text = text.mid(0, 60);
  //	m_noteEdit->setText(text);
  //	m_noteEdit->moveCursor(QTextCursor::End);
  //}
  //});

  //文件夹描述控件
  m_folderDesEdit = new QTextEdit(this);
  m_folderDesEdit->setFont(font_12);
  m_folderDesEdit->setFixedSize(180, 96);
  m_folderDesEdit->setAcceptRichText(false);
  m_folderDesEdit->setContextMenuPolicy(Qt::NoContextMenu);
  m_folderDesEdit->setPlaceholderText(QString::fromUtf8("请输入文件夹描述"));
  m_folderDesEdit->setWordWrapMode(QTextOption::WrapAnywhere);
  connect(m_folderDesEdit, &QTextEdit::textChanged,
          [=]() { m_desChanged = true; });

  //网址备注编辑标志位
  m_urlChanged = false;
  m_noteChanged = false;
  m_desChanged = false;

  //标志位
  m_bUrl = false;
  m_bNote = false;
  m_bRightIndex = false;
  m_bFolderTag = false;
  m_bLibBtn = false;

  this->SwitchStyleSheet();

  //隐藏全部控件
  hideAllWidget();

  this->installEventFilter(this);

  //窗口置于顶端 ps对于这种悬浮窗来说 顶层
  //和窗口失去活动关闭是几乎必须要的两个属性
#ifdef _WIN32
  this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
#else
  //这里先打开 settingcenter 然后选择素材库 然后在显示详情 就会出现
  //indexfloatingdialog 乱飞的情况 所以作出以下修改
  this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
#endif
}

void CIndexFloatingDialog::SlotFirstLabLinkActivated(QString) { this->close(); }

void CIndexFloatingDialog::SlotSecondLabLinkActivated(QString str) {
  if (QString::fromUtf8("设置素材封面") == str) {
    //设置素材封面
    emit signSetSourceCoverByFloat();
  } else if (QString::fromUtf8("详细教程") == str) {
    QDesktopServices::openUrl(QUrl("https://www.billfish.cn/soft-b24-change"));
  } else if (QString::fromUtf8("为什么会丢失") == str) {
    QDesktopServices::openUrl(QUrl("https://www.billfish.cn/soft-d06-why"));
  } else if (QString::fromUtf8("查看格式支持教程") == str) {
    QDesktopServices::openUrl(QUrl("https://www.billfish.cn/soft-d38-dif"));
  } else if (QString::fromUtf8("什么是索引素材") == str) {
    QDesktopServices::openUrl(QUrl("https://www.billfish.cn/soft-d06-what"));
  }
  this->close();
}

void CIndexFloatingDialog::SlotThirdLabLinkActivated(QString str) {
  if (QString::fromUtf8("偏好设置") == str) {
      emit SigOpenSettingWin();
  }
  this->close();
}

void CIndexFloatingDialog::SlotFourthLabLinkActivated(QString) {
  this->close();
}

//隐藏所有子控件
void CIndexFloatingDialog::hideAllWidget() {
  QList<QWidget*> childList = {
      m_textLabel, m_secondTextLabel, m_thirdTextLabel, m_fourthTextLabel,
      m_urlEdit,   m_browserLookBtn,  m_noteEdit,       m_folderDesEdit};

  foreach (QWidget* widget, childList) { widget->setVisible(false); }
}

CIndexFloatingDialog* CIndexFloatingDialog::getInstance(QWidget* parent) {
  if (!m_instance) {
#ifdef __APPLE__
    // TODO luqi 这里是 mac bug mapfromglobal 和 mapfromparent
    // 值一样导致位置不对
    m_instance = new CIndexFloatingDialog("", nullptr);
#else
    m_instance = new CIndexFloatingDialog("", parent);
#endif
  }
  return m_instance;
}

void CIndexFloatingDialog::move(int x, int y) {
#ifdef __APPLE__
  // TODO luqi 这里是 mac bug mapfromglobal 和 mapfromparent 值一样导致位置不对
  QWidget::setGeometry(x, y, size().width(), size().height());
#else
  CPopupDialog::move(x, y);
#endif
}

void CIndexFloatingDialog::move(const QPoint& p) {
  CIndexFloatingDialog::move(p.x(), p.y());
}

void CIndexFloatingDialog::show() {
#ifdef __APPLE__
  // TODO luqi 这里show的以后 在qt有bug 会在show中调用 toggleMax的时候有可能
  // 窗体初始的位置错误 导致tip乱飞
  auto pos = this->pos();
  CPopupDialog::show();
  move(pos);
#else
  CPopupDialog::show();
#endif
}

CIndexFloatingDialog::~CIndexFloatingDialog() { m_instance = nullptr; }

void CIndexFloatingDialog::showFloatingDialog(const QString& text) {
  hideAllWidget();

  //先4行全部展示
  m_textLabel->setVisible(true);
  m_secondTextLabel->setVisible(true);
  m_thirdTextLabel->setVisible(true);
  m_fourthTextLabel->setVisible(true);

  //字体
  m_textLabel->setFont(font_12);
  m_secondTextLabel->setFont(font_12);
  m_thirdTextLabel->setFont(font_12);
  m_fourthTextLabel->setFont(font_12);

  m_textLabel->setText(text);
  if (text == TEXT_LOST_INDEX) {
    this->setFixedSize(152, 52);

    QString first_line_str = QString::fromUtf8("该索引素材的路径已丢失");
    QString second_line_str = QString::fromUtf8(
        "<a style = 'color: #FF1B90FB;' href = "
        "为什么会丢失>为什么会丢失？</a>");
    m_textLabel->setText(first_line_str);
    m_secondTextLabel->setText(second_line_str);
    m_thirdTextLabel->setVisible(false);
    m_fourthTextLabel->setVisible(false);
  } else if (text == TEXT_SUPPORT_IMPORT) {
    this->setFixedSize(230, 92);

    QString first_line_str =
        QString::fromUtf8("该格式素材暂时仅支持导入不支持生成");
    QString second_line_str = QString::fromUtf8(
        "缩略图，您可以自定义 <a style='color: #FF1B90FB;' href = "
        "设置素材封面>设置素材封面</a>");
    QString third_line_str = QString::fromUtf8(
        "还可以在<a style='color: #FF1B90FB;' href = "
        "偏好设置>偏好设置</a>中设置更多您希望");
    QString fourth_line_str = QString::fromUtf8("导入的格式");

    m_textLabel->setText(first_line_str);
    m_secondTextLabel->setText(second_line_str);
    m_thirdTextLabel->setText(third_line_str);
    m_fourthTextLabel->setText(fourth_line_str);
  } else if (text == TEXT_WHAT_INDEX) {
    this->setFixedSize(116, 52);
    m_secondTextLabel->setText(TEXT_WHAT_INDEX_SECOND);
  } else if (text == TEXT_CLEAR_FILTER_CONDITION) {
    //出现不能超过两次
    static int show_count = 0;
    if (show_count <2) {
      this->setFixedSize(92, 35);
      m_textLabel->setText(TEXT_CLEAR_FILTER_CONDITION);
      show_count++;
    } else {
      return;
    }
  }

  this->show();
}

void CIndexFloatingDialog::showColorFloating(const QString& colorText,
                                             const QString& percentText) {
  hideAllWidget();
  m_textLabel->setVisible(true);
  m_secondTextLabel->setVisible(true);

  //字体
  m_textLabel->setFont(font_12);
  m_secondTextLabel->setFont(font_12);
  m_thirdTextLabel->setFont(font_12);
  m_fourthTextLabel->setFont(font_12);

  m_textLabel->setText(colorText);
  m_textLabel->move(8, 5);

  m_secondTextLabel->setText(percentText);
  m_secondTextLabel->move(8, 23);

  this->setFixedSize(108, 46);
  this->show();
}

void CIndexFloatingDialog::showColorFloating(const QString& tip) {
  hideAllWidget();
  m_textLabel->setVisible(true);

  //字体
  m_textLabel->setFont(font_10);

  m_textLabel->setText(tip);
  m_textLabel->move(8 - 1, 5 - 1 - 1);

  this->setFixedSize(72, 22);
  this->show();
}

void CIndexFloatingDialog::showUrlFloating(const QString& text) {
#ifdef __APPLE__
  this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
#endif

  hideAllWidget();
  m_urlEdit->setVisible(true);
  m_browserLookBtn->setVisible(true);

  m_urlEdit->setText(text);
  m_urlEdit->moveCursor(QTextCursor::End);
  m_urlEdit->move(12, 12);
  m_browserLookBtn->move(62, 78);
  this->setFixedSize(204, 120);

  ////网址控件行间距设置
  QTextDocument* urlDoc = m_urlEdit->document();
  QTextCursor urlCusor = m_urlEdit->textCursor();
  for (QTextBlock it = urlDoc->begin(); it != urlDoc->end(); it = it.next()) {
    QTextBlockFormat tbf = it.blockFormat();
    /*tbf.setLineHeight(3, QTextBlockFormat::LineDistanceHeight);*/
    // tbf.setLineHeight(18, QTextBlockFormat::FixedHeight);
    tbf.setLineHeight(120, QTextBlockFormat::ProportionalHeight);
    urlCusor.setPosition(it.position());
    urlCusor.setBlockFormat(tbf);
    m_urlEdit->setTextCursor(urlCusor);
  }

  m_urlChanged = false;
  this->show();
}

void CIndexFloatingDialog::showNoteFloating(const QString& text) {
#ifdef __APPLE__
  this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
#endif
  hideAllWidget();
  m_noteEdit->setVisible(true);

  this->update();

  m_noteEdit->setText(text);
  m_noteEdit->moveCursor(QTextCursor::End);
  m_noteEdit->move(12, 12);
  this->setFixedSize(204, 120);

  //备注控件行间距设置
  QTextDocument* noteDoc = m_noteEdit->document();
  QTextCursor noteCursor = m_noteEdit->textCursor();
  for (QTextBlock it = noteDoc->begin(); it != noteDoc->end(); it = it.next()) {
    QTextBlockFormat tbf = it.blockFormat();
    tbf.setLineHeight(6, QTextBlockFormat::LineDistanceHeight);
    noteCursor.setPosition(it.position());
    noteCursor.setBlockFormat(tbf);
    m_noteEdit->setTextCursor(noteCursor);
  }

  m_noteChanged = false;
  this->show();
}

void CIndexFloatingDialog::showFolderDesFloating(const QString& text) {
#ifdef __APPLE__
  this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
#endif

  hideAllWidget();
  m_folderDesEdit->setVisible(true);

  this->update();

  m_folderDesEdit->setText(text);
  m_folderDesEdit->moveCursor(QTextCursor::End);
  m_folderDesEdit->move(12, 12);
  this->setFixedSize(204, 120);

  m_desChanged = false;
  this->show();
}

void CIndexFloatingDialog::showFolderTagFloatingDialog(const QString& text1,
                                                       const QString& text2,
                                                       const QString& text3) {
  hideAllWidget();
  m_textLabel->setVisible(true);
  m_secondTextLabel->setVisible(true);
  m_secondTextLabel->setVisible(true);
  m_thirdTextLabel->setVisible(true);

  //字体
  m_textLabel->setFont(font_12);
  m_secondTextLabel->setFont(font_12);
  m_thirdTextLabel->setFont(font_12);
  m_fourthTextLabel->setFont(font_12);

  m_textLabel->setText(text1);
  m_textLabel->move(10, 8);

  m_secondTextLabel->setText(text2);
  m_secondTextLabel->move(10, 28);

  m_thirdTextLabel->setText(text3);
  m_thirdTextLabel->move(10, 48);

  this->setFixedSize(230, 72);
  this->show();
}

void CIndexFloatingDialog::showWhiteFloatDialog(const QString& str) {
  //隐藏所有
  hideAllWidget();

  //保留第一个
  m_textLabel->setVisible(true);
  m_secondTextLabel->setVisible(false);
  m_thirdTextLabel->setVisible(false);
  m_fourthTextLabel->setVisible(false);

  //字体
  m_textLabel->setFont(font_10);
  // m_secondTextLabel->setFont(font_10);
  // m_thirdTextLabel->setFont(font_10);
  // m_fourthTextLabel->setFont(font_10);

  // label设置
  m_textLabel->setFixedSize(150, 13);
  m_textLabel->move(6, 6);
  m_textLabel->setText(str);

  //大小控制
  this->setFixedSize(162, 25);
  this->show();
}

void CIndexFloatingDialog::showImportTipsFloatDialog(const QString&) {
  //隐藏所有
  hideAllWidget();

  //保留第一个 和第二个
  m_textLabel->setVisible(true);
  m_secondTextLabel->setVisible(true);
  m_thirdTextLabel->setVisible(false);
  m_fourthTextLabel->setVisible(false);

  //字体
  m_textLabel->setFont(font_12);
  m_secondTextLabel->setFont(font_12);
  // m_thirdTextLabel->setFont(font_10);
  // m_fourthTextLabel->setFont(font_10);

  // label设置
  m_textLabel->setFixedSize(156, 15);
  m_textLabel->move(10, 10);
  m_textLabel->setText(QString::fromUtf8("想了解三种方式有什么区别？"));

  m_secondTextLabel->setFixedSize(150, 15);
  m_secondTextLabel->move(10, 30);

  QString second_str = "< a style = 'color:";
  second_str +=
      BFSkinSetting::GetInstance()->GetMainColor().name(QColor::HexArgb);
  second_str += ";' href = 详细教程>点击查看更详细教程</a>";

  m_secondTextLabel->setText(second_str);

  QPoint point = this->pos();

  //大小控制
  this->setFixedSize(176, 52);

  this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
  this->show();
  this->activateWindow();

  QApplication::processEvents();
}

void CIndexFloatingDialog::showFormatFloating(const QRect& iconRect) {
  //隐藏所有
  hideAllWidget();

  //保留第一个 和第二个
  m_textLabel->setVisible(true);
  m_secondTextLabel->setVisible(true);

  this->setFixedSize(176, 52);

  QString first_line_str = QString::fromUtf8("支持导入和支持解析的区别");
  QString second_line_str = QString::fromUtf8(
      "<a style = 'color: #FF1B90FB;' href = "
      "查看格式支持教程>查看格式支持教程</a>");
  m_textLabel->setText(first_line_str);
  m_secondTextLabel->setText(second_line_str);
  m_thirdTextLabel->setVisible(false);
  m_fourthTextLabel->setVisible(false);

  //开启区域检测定时器，如果鼠标不在指定图标和悬浮窗区域，关闭悬浮窗。
  if (!m_format_check_timer) {
    m_format_check_timer = new QTimer(this);
    m_format_check_timer->setInterval(200);
    connect(m_format_check_timer, &QTimer::timeout, [=]() {
      if (!(this->underMouse()) && !(iconRect.contains(QCursor::pos()))) {
        this->close();
        m_format_check_timer->stop();
      }
    });
  }

  m_format_check_timer->start(200);
  this->exec();
}

void CIndexFloatingDialog::setUrlEnable(bool enable) {
  m_urlEdit->setEnabled(enable);
}

void CIndexFloatingDialog::setNoteEnable(bool enable) {
  m_noteEdit->setEnabled(enable);
}

void CIndexFloatingDialog::setFolderDesEnable(bool enable) {
  m_folderDesEdit->setEnabled(enable);
}

void CIndexFloatingDialog::showLibBtnFloatDialog(const QString& text) {
  //隐藏所有
  hideAllWidget();

  //保留第一个
  m_textLabel->setVisible(true);
  m_textLabel->setText(text);
  //字体
  m_textLabel->setFont(font_12);
  m_textLabel->move(10, 4);

  int _width = BfQtUtils::WidthWithFixString(font_12, text);
  m_textLabel->setFixedWidth(_width + 20);
  this->setFixedSize(_width + 20, 25);
  this->show();
}

QString CIndexFloatingDialog::getDialogMode() { return m_textLabel->text(); }

void CIndexFloatingDialog::SwitchStyleSheet() {
  //文字label样式
  QString lab_text =
      "color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  lab_text += ";";
  m_textLabel->setStyleSheet(lab_text);

  //文字label样式
  QString second_text =
      "color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  second_text += ";";
  m_secondTextLabel->setStyleSheet(second_text);

  //文字label样式
  QString third_text =
      "color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  third_text += ";";
  m_thirdTextLabel->setStyleSheet(third_text);

  //文字label样式
  QString fourth_text =
      "color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  fourth_text += ";";
  m_fourthTextLabel->setStyleSheet(third_text);

  // QTextEdit样式
  QString textEditStyle =
      QString(
          "padding-left:6px;padding-top:4px;border-radius:4px;border:0px;"
          "background:") +
      BFSkinSetting::GetInstance()->GetRightNameEditBackColor().name(
          QColor::HexArgb) +
      QString(";color:") +
      BFSkinSetting::GetInstance()->GetRightFont1().name(QColor::HexArgb);
  //网址控件样式
  m_urlEdit->setStyleSheet(textEditStyle);
  QScrollBar* verticalBar = m_urlEdit->verticalScrollBar();
  QString barStyle =
      QString(
          "QScrollBar::handle:vertical{ "
          "width:4px;border-radius:2px;background:") +
      BFSkinSetting::GetInstance()->GetRightScrollHandleColor().name(
          QColor::HexArgb) +
      QString(";} ") +
      QString("QScrollBar:vertical{ width:4px;border-radius:2px;}") +
      QString("QScrollBar::add-line:vertical{ width:0px;height:0px;}") +
      QString("QScrollBar:sub-line:vertical{ width:0px;height:0px;}") +
      QString("QScrollBar::add-page:vertical{background-color:transparent") +
      /*BFSkinSetting::GetInstance()->GetCommonModeDarkColor().name(QColor::HexArgb)
         +*/
      QString(";}") +
      QString("QScrollBar::sub-page:vertical {background-color:transparent") +
      /*BFSkinSetting::GetInstance()->GetCommonModeDarkColor().name(QColor::HexArgb)
         +*/
      QString(";}");
  verticalBar->setStyleSheet(barStyle);
  QString browserStyle =
      QString("border-radius:11px;background:") +
      BFSkinSetting::GetInstance()->GetRightWinBlue1().name(QColor::HexArgb) +
      QString(";color:") +
      BFSkinSetting::GetInstance()->GetRightFont1().name(QColor::HexArgb);
  m_browserLookBtn->setStyleSheet(browserStyle);

  //备注控件样式
  m_noteEdit->setStyleSheet(textEditStyle);
  QScrollBar* noteVerticalBar = m_noteEdit->verticalScrollBar();
  noteVerticalBar->setStyleSheet(barStyle);

  //文件夹描述
  m_folderDesEdit->setStyleSheet(textEditStyle);
  QScrollBar* desVerticalBar = m_folderDesEdit->verticalScrollBar();
  desVerticalBar->setStyleSheet(barStyle);

  //主体窗口相应设置
  QString win_style_str;
  win_style_str += "#wid_main{background-color:";
  win_style_str +=
      BFSkinSetting::GetInstance()->GetPopupWinBackgroundColor().name(
          QColor::HexArgb);
  win_style_str += ";border-radius:4px;border:1px solid; border-color:";
  win_style_str += BFSkinSetting::GetInstance()->GetPopupWinBorderColor().name(
      QColor::HexArgb);
  win_style_str += ";}";
  m_wid_main->setStyleSheet(win_style_str);
}

QString CIndexFloatingDialog::getUrl() {
  QString url = m_urlEdit->toPlainText();
  return url;
}

QString CIndexFloatingDialog::getFolderDes() {
  QString des = m_folderDesEdit->toPlainText();
  return des;
}

bool CIndexFloatingDialog::eventFilter(QObject* obj, QEvent* event) {
  auto a = event->type();
  if (obj == this && event->type() == QEvent::WindowDeactivate) {
    if (this->getDialogMode() !=
        QString::fromUtf8("想了解三种方式有什么区别？")) {
      this->close();
    }
  }
  return CPopupDialog::eventFilter(obj, event);
}

void CIndexFloatingDialog::hideEvent(QHideEvent* event) {
  //防止触发遮罩消失
  // CPopupDialog::hideEvent(event);
}

void CIndexFloatingDialog::closeEvent(QCloseEvent* event) {
#ifdef __APPLE__
  this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);
#endif

  //活动窗口回归皮肤窗口
  if (this->getDialogMode() ==
      QString::fromUtf8("白色皮肤将在后续支持，敬请期待")) {
    // BFNavigationBar::GetInstance()->SetSkinSettingWinActive();
  }

  if (this->getDialogMode() ==
      QString::fromUtf8("想了解三种方式有什么区别？")) {
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint |
                         Qt::WindowStaysOnTopHint);
  }

  //防止触发遮罩消失
  // CPopupDialog::closeEvent(event);
}

void CIndexFloatingDialog::leaveEvent(QEvent* event) {
  if (this->getDialogMode() ==
      QString::fromUtf8("想了解三种方式有什么区别？")) {
    this->close();
  }

  // QTextEdit在输入法快速输入时，总是会触发leaveEvent。为了正确隐藏悬浮窗，不再简单的通过leaveEvent关闭悬浮窗，而是通过判断鼠标是否在悬浮窗范围内。
  QRect tRect = this->geometry();
  if (!tRect.contains(QCursor::pos())) this->close();
}
