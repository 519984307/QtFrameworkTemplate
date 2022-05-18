#include "CustomControls.h"
#include "../bfqtutils.h"
#include "../bfskinmodule/bfskinsetting.h"
#include "CNewWidget.h"
#include <QAbstractItemView>
#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QEvent>
#include <QListView>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QScrollBar>
#include <QStyleFactory>
#include <qsvgrenderer.h>
#include <QDir>
#include <QPalette>
#pragma execution_character_set("utf-8")

#define SHADOW_WIDTH 15     // 窗口阴影宽度
#define TRIANGLE_WIDTH 15   // 小三角的宽度
#define TRIANGLE_HEIGHT 15  // 小三角的高度

RoundComboBox::RoundComboBox(QWidget* parent /* = nullptr */)
    : QWidget(parent) {
  m_pComboBox = new QComboBox(this);
  m_pComboBox->setEditable(false);
  m_pComboBox->setContextMenuPolicy(Qt::NoContextMenu);

  connect(m_pComboBox, &QComboBox::currentTextChanged, this,
          &RoundComboBox::signal_currentTextChanged);
}

RoundComboBox::~RoundComboBox() {}

void RoundComboBox::setStyleValue(int nWidth, int nHeight, int nRadius,
                                  int nFontSize, const QColor& bkColor,
                                  const QColor& fontColor,
                                  int nMinWidth /* = 100 */) {
  m_pComboBox->setFixedSize(nWidth - nRadius * 2, nHeight);
  setFixedSize(nWidth, nHeight);
  m_pComboBox->move(nRadius, 0);

  QString strStyle =
      QString(
          "background:%1;border-radius:%2px;font-size:%3px;border:none;font-"
          "family:\"Microsoft YaHei\";color:%4;")
          .arg(bkColor.name())
          .arg(nRadius)
          .arg(nFontSize)
          .arg(fontColor.name());
  setStyleSheet(strStyle);

#if _WIN32
  // combox 样式
  QString combox_style = "QComboBox{padding-left:10px;background:" +
                         bkColor.name(QColor::HexArgb) + ";color:";
  combox_style += fontColor.name(QColor::HexArgb);
  combox_style += ";}";
  combox_style +=
      "QComboBox::drop-down{padding-top:8px;padding-right:10px;width:5px;"
      "height:6px;background-color:rgba(0,0,0,0);" +
      BFSkinSetting::GetInstance()->GetResourcePath(
          "choice_dropbox_arrow.svg") +
      "}";
  // TODO : 22724 【批量重命名】批量重命名下缺少功能 不知道为什么不能正常显示
  // 先屏蔽
  // combox_style += "QComboBox QAbstractItemView{border:1px solid" +
  // BFSkinSetting::GetInstance()->GetPopupWinBorderColor().name(QColor::HexArgb)
  // + ";border-radius:8px;outline:0px;color:" +
  //  BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb) +
  //  ";background-color:" +
  //  BFSkinSetting::GetInstance()->GetPopupWinBackgroundColor().name(QColor::HexArgb)
  //  +
  //  ";min-width:"+ QString::number(nMinWidth) + "px;}";
  m_pComboBox->setStyleSheet(combox_style);
#else
  QString styleSheet;
  styleSheet +=
      "QComboBox{border-radius:11px;padding-left:10px;background:" +
      BFSkinSetting::GetInstance()->GetSettingLibComboxBackColor().name(
          QColor::HexArgb) +
      ";color:";
  styleSheet +=
      BFSkinSetting::GetInstance()->GetTextColor(3).name(QColor::HexArgb);
  styleSheet += ";}";
  styleSheet +=
      "QComboBox::drop-down{padding-top:8px;padding-right:10px;width:5px;"
      "height:6px;background:transparent;" +
      BFSkinSetting::GetInstance()->GetResourcePath(
          "choice_dropbox_arrow.svg") +
      "}";
  //	styleSheet += "QComboBox QAbstractItemView{border: 1px solid " +
  // BFSkinSetting::GetInstance()->GetPopupWinBorderColor().name(QColor::HexArgb)
  //+ ";border-radius:8px;outline:0px;color:" +
  // BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb) +
  //";background:" +
  // BFSkinSetting::GetInstance()->GetPopupWinBackgroundColor().name(QColor::HexArgb)
  //+ "}";
  styleSheet +=
      "QComboBox QAbstractItemView{border: 0px solid " +
      BFSkinSetting::GetInstance()->GetPopupWinBorderColor().name(
          QColor::HexArgb) +
      ";border-radius:8px;outline:0px;color:" +
      BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb) +
      ";background:" +
      BFSkinSetting::GetInstance()->GetPopupWinBackgroundColor().name(
          QColor::HexArgb) +
      "}";

  QListView* _listView = new QListView();
  BFComboBoxViewDelegate* _delegate = new BFComboBoxViewDelegate(_listView);
  _listView->setItemDelegate(_delegate);
  _listView->setSpacing(0);
  _listView->setContentsMargins(0, 0, 0, 0);
  m_pComboBox->setView(_listView);
  m_pComboBox->setStyleSheet(styleSheet);

  QScrollBar* verticalBar = m_pComboBox->view()->verticalScrollBar();
  QString barStyle =
      QString(
          "QScrollBar::handle:vertical{ "
          "width:6px;border-radius:3px;background: ") +
      BFSkinSetting::GetInstance()->GetScrollBarColor().name() + QString(";}") +
      QString("QScrollBar:vertical{ width:6px;border:none;}") +
      QString("QScrollBar::add-page:vertical{width:0px;background-color:") +
      BFSkinSetting::GetInstance()
          ->GetConditionFilterColorSelectColor()
          .name() +
      QString(";}") +
      QString("QScrollBar::sub-page:vertical {width:0px;background-color:") +
      BFSkinSetting::GetInstance()
          ->GetConditionFilterColorSelectColor()
          .name() +
      QString(";}") +
      QString("QScrollBar::add-line:vertical{width:0px;height:0px;}") +
      QString("QScrollBar::sub-line:vertical {width:0px;height:0px;}");
  verticalBar->setStyleSheet(barStyle);
  m_pComboBox->setStyle(QStyleFactory::create("Windows"));
  m_pComboBox->view()->parentWidget()->setWindowFlags(Qt::Popup |
                                                      Qt::FramelessWindowHint);
  m_pComboBox->view()->parentWidget()->setAttribute(
      Qt::WA_TranslucentBackground);

#endif
}

QComboBox* RoundComboBox::getComboBox() { return m_pComboBox; }

void RoundComboBox::paintEvent(QPaintEvent* event) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

PopUpComboBox::PopUpComboBox(QWidget* parent) : QComboBox(parent) {
#ifdef _WIN32
  // TODO : 临时方案 浏览器采集 下拉框不正常 先屏蔽
  //	QListView* pListView = new QListView(this);
  //	pListView->setSpacing(0);
  //	pListView->setContentsMargins(0, 0, 0, 0);
  //	setView(pListView);

  view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint |
                                   Qt::NoDropShadowWindowHint);
  view()->window()->setAttribute(Qt::WA_TranslucentBackground);
  view()->window()->setStyleSheet("border:0px;");
#else

  QListView* pListView = new QListView(this);
  BFComboBoxViewDelegate* _delegate = new BFComboBoxViewDelegate(pListView);
  pListView->setItemDelegate(_delegate);
  pListView->setSpacing(0);
  pListView->setContentsMargins(0, 0, 0, 0);
  setView(pListView);

  view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint |
                                   Qt::NoDropShadowWindowHint);
  view()->window()->setAttribute(Qt::WA_TranslucentBackground);

  setStyle(QStyleFactory::create("Windows"));

#endif

  this->view()->installEventFilter(this);
}

PopUpComboBox::~PopUpComboBox() {}

void PopUpComboBox::setPopListViewWidth(int nWidth) {
  view()->setFixedWidth(nWidth);
}

void PopUpComboBox::setComboBoxStyle(const QString& strComboxStyle,
                                     const QString& strListViewStyle,
                                     const QString& strScrollBarStyle) {
  view()->setStyleSheet(strListViewStyle);
  this->setStyleSheet(strComboxStyle);
  view()->verticalScrollBar()->setStyleSheet(strScrollBarStyle);

  QFont font_12;
  font_12.setPixelSize(12);
  font_12.setFamily(QString::fromUtf8("微软雅黑"));
  this->setFont(font_12);
}

void PopUpComboBox::showPopup() {
  bool oldAnimationEffects = qApp->isEffectEnabled(Qt::UI_AnimateCombo);
  qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);

  QComboBox::showPopup();
  qApp->setEffectEnabled(Qt::UI_AnimateCombo, oldAnimationEffects);
}

bool PopUpComboBox::eventFilter(QObject* obj, QEvent* e) {
  bool handled = false;
  if (e->type() == QEvent::Show) {
#ifdef _WIN32
    if (obj == view()) {
      QWidget* frame = findChild<QFrame*>();
      frame->move(frame->x(), frame->y() - this->height() - frame->height());
    }
#endif
  }

  if (!handled) {
    handled = QComboBox::eventFilter(obj, e);
  }
  return handled;
}

BFComboBoxViewDelegate::BFComboBoxViewDelegate(QWidget* parent)
    : QStyledItemDelegate(parent) {}

BFComboBoxViewDelegate::~BFComboBoxViewDelegate() {}

void BFComboBoxViewDelegate::paint(QPainter* painter,
                                   const QStyleOptionViewItem& option,
                                   const QModelIndex& index) const {
  if (index.data().canConvert<QString>()) {
    QFont font_yahei_13;
    font_yahei_13.setFamily("Microsoft YaHei");
    font_yahei_13.setPixelSize(13);

    QString str = index.data().toString();

    QRect r = option.rect;
    painter->setFont(font_yahei_13);
    painter->setPen(BFSkinSetting::GetInstance()->GetTextColor(0));

    str = BfQtUtils::FontAdjustWidth(font_yahei_13, option.rect.width() - 30,
                                     str);
    painter->drawText(QPoint(20, r.y() + 33), str);
  }
}

QSize BFComboBoxViewDelegate::sizeHint(const QStyleOptionViewItem& option,
                                       const QModelIndex& index) const {
  QSize size(135, 33);

  //如果是最后一行，高度要多显示20
  int itemCount = -1;
  QListView* _listView = dynamic_cast<QListView*>(this->parent());
  if (_listView) {
    int i1 = (_listView->model()->rowCount() - 1);
    int i2 = index.row();
    if ((_listView->model()->rowCount() - 1) == index.row()) {
      size = QSize(135, 53);
    }
  }

  return size;
}

CToolTip::CToolTip() {
  m_globalTipWidgt = NULL;
  m_menuTipWidget = NULL;
}

CToolTip::~CToolTip() {}

void CToolTip::showGlobalTip(QPoint pt, int iLength, QString strTooltip,
                             QWidget* out_parent_widget) {
  pt.setY(pt.y() + 4);
  if (!m_globalTipWidgt) {
    m_globalTipWidgt = new CNewWidget(out_parent_widget);
    int textLength = ((CNewWidget*)m_globalTipWidgt)->LoadText(strTooltip);
    // m_globalTipWidgt->setFixedSize(220, 50);
    if (textLength > iLength) {
      pt.setX(pt.x() - (textLength - iLength) / 2);
      m_globalTipWidgt->move(pt);
      ((CNewWidget*)m_globalTipWidgt)->Show();
    } else {
      pt.setX(pt.x() + (iLength - textLength) / 2);
      m_globalTipWidgt->move(pt);
      ((CNewWidget*)m_globalTipWidgt)->Show();
    }
  } else {
    int textLength = ((CNewWidget*)m_globalTipWidgt)->LoadText(strTooltip);
    if (textLength > iLength) {
      pt.setX(pt.x() - (textLength - iLength) / 2);
      m_globalTipWidgt->move(pt);
      ((CNewWidget*)m_globalTipWidgt)->Show();
    } else {
      pt.setX(pt.x() + (iLength - textLength) / 2);
      m_globalTipWidgt->move(pt);
      ((CNewWidget*)m_globalTipWidgt)->Show();
    }
  }
  QApplication::processEvents();
}

void CToolTip::hideGlobalTip() {
  if (m_globalTipWidgt) {
    m_globalTipWidgt->hide();
  }
}

BfLoadingWidget::BfLoadingWidget(qint32 borderLength, qint32 logoWidth,
                                 qint32 logoHeight,
                                 QWidget* parent /*= nullptr*/) {
  m_borderLength = borderLength;
  m_logoWidth = logoWidth;
  m_logoHeight = logoHeight;

  QString pixPath = GetSkinResourceAbsolutePath("loading_border.png");
  m_loadingBorder.load(pixPath);
  m_loadingBorder = m_loadingBorder.scaled(
      m_borderLength, m_borderLength, Qt::KeepAspectRatio,
      Qt::TransformationMode::SmoothTransformation);

  m_tipText = new QLabel(this);
  m_tipText->setFixedSize(98, 14);

  m_tipText->setAlignment(Qt::AlignCenter);
  m_tipText->setText(QString::fromUtf8("正在加载中..."));

  //加载svg
  LoadSvg();

  QString strLabelStyle =
      QString(
          "border:0px;color:%1;font-family:"
          "\"Microsoft YaHei\";font-size:12px;")
          .arg(BFSkinSetting::GetInstance()->text_color_vec[0].name());
  m_tipText->setStyleSheet(strLabelStyle);
  m_Timer = new QTimer(this);
  connect(m_Timer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
  m_Timer->start(10);
}

BfLoadingWidget::~BfLoadingWidget() {}

void BfLoadingWidget::LoadSvg() {
  qreal dpi = BFSkinSetting::GetInstance()->GetDpi();
  // logo
  QString path_logo = GetSkinResourceAbsolutePath("loading_logo.svg");
  QSvgRenderer render_logo(path_logo);
  QSize size_logo = QSize(m_logoWidth, m_logoHeight);
  QImage image_logo(QSize(size_logo.width() * dpi, size_logo.height() * dpi),
                    QImage::Format_ARGB32_Premultiplied);

  image_logo.fill(Qt::transparent);
  QPainter painter_logo(&image_logo);
  render_logo.render(&painter_logo);
  m_load_logo = new QPixmap(QPixmap::fromImage(image_logo));

  //外部框架
  QString path_border = GetSkinResourceAbsolutePath("loading_border.svg");
  QSvgRenderer render_border(path_border);
  QSize size_border = QSize(m_borderLength, m_borderLength);
  QImage image_border(
      QSize(size_border.width() * dpi, size_border.height() * dpi),
      QImage::Format_ARGB32_Premultiplied);

  image_border.fill(Qt::transparent);
  QPainter painter_border(&image_border);
  render_border.render(&painter_border);
  m_load_outline = new QPixmap(QPixmap::fromImage(image_border));
}

void BfLoadingWidget::updatePixmap() {
  m_pixRat += 4;
  m_pixRat = m_pixRat % 360;
  update();
}

void BfLoadingWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                         QPainter::SmoothPixmapTransform);
  m_tipText->move((this->width() - 98) / 2,
                  (this->height() - 14) / 2 + m_borderLength + 16);

  QRect rect =
      QRect((this->width() - m_logoWidth) / 2,
            (this->height() - m_logoHeight) / 2, m_logoWidth, m_logoHeight);
  painter.drawPixmap(rect, *m_load_logo);

  painter.save();
  //painter.translate(this->width() / 2, this->height()/2);
  painter.rotate(m_pixRat % 360);
 // painter.translate(-m_borderLength / 2, -m_borderLength / 2);
  QRect border_rect = QRect((this->width() - m_borderLength) / 2,
                            (this->height() - m_borderLength) / 2,
                            m_borderLength, m_borderLength);
  painter.drawPixmap(border_rect, *m_load_outline);
  qDebug() << border_rect;
  painter.restore();
}

BFLineEdit::BFLineEdit(QWidget* wid) : QLineEdit(wid) {
  SetUserStyleSheet(false);
  this->setContextMenuPolicy(Qt::NoContextMenu);

  //设置背景字体颜色
  QPalette palette = this->palette();
  palette.setColor(QPalette::All, QPalette::PlaceholderText, QColor(162, 171, 195,255));
  this->setPalette(palette);

#ifdef __APPLE__
  setAttribute(Qt::WA_MacShowFocusRect, 0);
#endif
}

void BFLineEdit::SetUserStyleSheet(bool select) {
  QString styleSheet;
  if (select) {
    //搜索输入框
    styleSheet =
        "font-size:12px;font-family:\"Microsoft "
        "YaHei\";border-radius:4px;background-color:rgba(31,32,45,255);border:"
        "1px "
        "solid;border-color:rgba(172, 178, "
        "198,255);qproperty-alignment:AlignHCenter;color:";
    styleSheet +=
        BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb);
    styleSheet += ";";

  } else {
    //搜索状态
    styleSheet =
        "font-size:12px;font-family:\"Microsoft "
        "YaHei\";border-radius:4px;background-color:rgba(42,44,56,255);border:"
        "1px;solid;border-color:";
    styleSheet += BFSkinSetting::GetInstance()->GetPopupWinBorderColor().name(
        QColor::HexArgb);
    styleSheet += ";qproperty-alignment:AlignHCenter;color:";
    styleSheet +=
        BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb);
    styleSheet += ";";
  }
  this->setStyleSheet(styleSheet);
}

void BFLineEdit::focusInEvent(QFocusEvent* e) {
  SetUserStyleSheet(true);
  return QLineEdit::focusInEvent(e);
}

void BFLineEdit::focusOutEvent(QFocusEvent* e) {
  SetUserStyleSheet(false);
  return QLineEdit::focusOutEvent(e);
}

BFFilterComboBoxViewDelegate::BFFilterComboBoxViewDelegate(QWidget* parent)
    : QStyledItemDelegate(parent) {}

BFFilterComboBoxViewDelegate::~BFFilterComboBoxViewDelegate() {}

void BFFilterComboBoxViewDelegate::paint(QPainter* painter,
                                         const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const {
  if (index.data().canConvert<QString>()) {
    QFont font_yahei_13;
    font_yahei_13.setFamily("Microsoft YaHei");
    font_yahei_13.setPixelSize(13);
    QString str = index.data().toString();
    QRect r = option.rect;
    painter->setFont(font_yahei_13);
    painter->setPen(BFSkinSetting::GetInstance()->GetTextColor(0));
    painter->drawText(r, Qt::AlignCenter, str);
  }
}

QSize BFFilterComboBoxViewDelegate::sizeHint(const QStyleOptionViewItem& option,
                                             const QModelIndex& index) const {
  QSize size(50, 20);

  ////如果是最后一行，高度要多显示20
  // int itemCount = -1;
  // QListView* _listView = dynamic_cast<QListView*>(this->parent());
  // if (_listView) {
  //  int i1 = (_listView->model()->rowCount() - 1);
  //  int i2 = index.row();
  //  if ((_listView->model()->rowCount() - 1) == index.row()) {
  //    size = QSize(50, 30);
  //  }
  //}

  return size;
}

BFEclipseLinkWidget::BFEclipseLinkWidget(QColor color, QString link_str,
                                         int diameter, QString svg_name,
                                         QSize icon_size, QWidget* parent)
    : QWidget(parent) {
  m_diameter = diameter;
  m_color = color;
  m_link = link_str;
  m_icon_name = svg_name;
  m_icon_size = icon_size;
  //大小设置
  this->setFixedSize(m_diameter, m_diameter);
  //加载图标
  LoadIcon();
}

BFEclipseLinkWidget::~BFEclipseLinkWidget() {}

void BFEclipseLinkWidget::paintEvent(QPaintEvent* e) {
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                         QPainter::SmoothPixmapTransform);
  //画背景
  painter.setPen(Qt::NoPen);
  if (click_state) {
    painter.setBrush(BFSkinSetting::GetInstance()->GetMainColor());
  }
  else
  {
     painter.setBrush(Qt::white);
  }
  painter.drawEllipse(this->rect());
  //画图标
  int x_pos = (this->rect().width() - m_icon_size.width()) / 2;
  int y_pos = (this->rect().height() - m_icon_size.height()) / 2;
  painter.drawPixmap(
      QRect(x_pos, y_pos, m_icon_size.width(), m_icon_size.height()),
      m_pixmap);

  return QWidget::paintEvent(e);
}

void BFEclipseLinkWidget::mouseReleaseEvent(QMouseEvent* event) {
  bool ret = QDesktopServices::openUrl(m_link);
  click_state = false;
  update();
  return QWidget::mouseReleaseEvent(event);
}

void BFEclipseLinkWidget::mousePressEvent(QMouseEvent* event) {
  click_state = true;
  update();
  return QWidget::mousePressEvent(event);
}

void BFEclipseLinkWidget::LoadIcon() {
  qreal dpi = BFSkinSetting::GetInstance()->GetDpi();
  // logo
  QString path_logo = GetSkinResourceAbsolutePath(m_icon_name);
  QSvgRenderer render_logo(path_logo);
  QSize size_logo = QSize(m_diameter, m_diameter);
  QImage image_logo(QSize(size_logo.width() * dpi, size_logo.height() * dpi),
                    QImage::Format_ARGB32_Premultiplied);

  image_logo.fill(Qt::transparent);
  QPainter painter_logo(&image_logo);
  render_logo.render(&painter_logo);
  m_pixmap = QPixmap::fromImage(image_logo);
}


BfLargerModeLoadingWidget::BfLargerModeLoadingWidget(
    qint32 borderLength,
                                           qint32 logoWidth,
                                 qint32 logoHeight,
                                 QWidget* parent /*= nullptr*/) {
  auto dpi = BFSkinSetting::GetInstance()->GetDpi();
  m_borderLength = borderLength;
  m_logoWidth = logoWidth;
  m_logoHeight = logoHeight;
  m_movieLabel = new QLabel(this);
  m_movieLabel->setFixedSize(m_borderLength, m_borderLength);

  m_logoLabel = new QLabel(this);
  m_logoLabel->setFixedSize(m_logoWidth, m_logoHeight);
  QString logoPath = GetSkinResourceAbsolutePath("loading_logo.svg");
  QPixmap logoPix(QDir::toNativeSeparators(logoPath));
  logoPix = logoPix.scaled(m_logoWidth*dpi, m_logoHeight*dpi, Qt::KeepAspectRatio,
                           Qt::TransformationMode::SmoothTransformation);
  logoPix.setDevicePixelRatio(dpi);
  m_logoLabel->setPixmap(logoPix);

  QString pixPath = GetSkinResourceAbsolutePath("loading_border.svg");
  m_loadingBorder.load(QDir::toNativeSeparators(pixPath));
  m_loadingBorder = m_loadingBorder.scaled(
      m_borderLength*dpi, m_borderLength*dpi, Qt::KeepAspectRatio,
      Qt::TransformationMode::SmoothTransformation);
  m_loadingBorder.setDevicePixelRatio(dpi);

  m_tipText = new QLabel(this);
  m_tipText->setFixedSize(98, 14);

  m_tipText->setAlignment(Qt::AlignCenter);
  m_tipText->setText(QString::fromUtf8("正在加载中..."));

  QString strLabelStyle =
      QString(
          "border:0px;color:%1;font-family:"
          "\"Microsoft YaHei\";font-size:12px;")
          .arg(BFSkinSetting::GetInstance()->text_color_vec[0].name());
  m_tipText->setStyleSheet(strLabelStyle);
  m_Timer = new QTimer(this);
  connect(m_Timer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
  m_Timer->start(10);
}

BfLargerModeLoadingWidget::~BfLargerModeLoadingWidget() {}

void BfLargerModeLoadingWidget::updatePixmap() {
  m_pixRat += 4;
  m_pixRat = m_pixRat % 360;
  update();
}

void BfLargerModeLoadingWidget::paintEvent(QPaintEvent* event) {
    auto dpi = BFSkinSetting::GetInstance()->GetDpi();
    m_movieLabel->move((this->width() - m_borderLength) / 2,
                       (this->height() - m_borderLength) / 2);

    m_tipText->move((this->width() - 98) / 2,
                    (this->height() - 14) / 2 + m_borderLength + 16);

    m_logoLabel->move((this->width() - m_logoWidth) / 2,
                      (this->height() - m_logoHeight) / 2);

    QPixmap temp(m_loadingBorder.size());
    temp.fill(Qt::transparent);
    temp.setDevicePixelRatio(dpi);
    QPainter painter(&temp);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.translate(m_borderLength / 2, m_borderLength / 2);
    painter.rotate(m_pixRat % 360);
    painter.translate(-m_borderLength / 2, -m_borderLength / 2);
    painter.drawPixmap(0, 0, m_loadingBorder);
    painter.end();
    temp.setDevicePixelRatio(dpi);
    m_movieLabel->setPixmap(temp);
}
