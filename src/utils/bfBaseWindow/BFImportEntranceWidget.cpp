#include "BFImportEntranceWidget.h"
#include "bfskinmodule/bfskinsetting.h"
#include <QShowEvent>
#include <QPainter>
#include <qsvgrenderer.h>
#include <QDebug>


#define BFImportEntranceWidgetInitOpacity 1
#define BFImportEntranceWidgetHideOpacity 0
#define BFImportEntranceWidgetHideTime 200


#pragma execution_character_set("utf-8")


BFImportEntranceWidget::BFImportEntranceWidget(QWidget* parent) : QPushButton(parent), is_expand(false)/*, m_pixmap_expand(QPixmap()), m_pixmap_shrink(QPixmap())*/
{
  //蓝湖固定的大小
  this->setFixedSize(82, 32);

  //读取svg到内存
  //LoadStylePixmap();


  //配置动画
  this->SetAnimation();


  //检测超出区域按钮变为收缩状态的定时器
  m_check_leave_time = new QTimer(this);
  m_check_leave_time->setSingleShot(false);
  m_check_leave_time->setInterval(100);
  connect(m_check_leave_time, SIGNAL(timeout()), this,
          SLOT(SlotCheckMouseLeave()), Qt::UniqueConnection);
}

 BFImportEntranceWidget::~BFImportEntranceWidget() {
#ifdef _DEBUG
  qDebug() << "BFImportEntranceWidget::~BFImportEntranceWidget()";
#endif
}

void BFImportEntranceWidget::SetToolWid(BFImportEntranceToolWidget*tool_wid)
{
  m_tool_wid = tool_wid;
}

void BFImportEntranceWidget::SetAnimation() {
  //形变动画
  m_animation_geo_start = new QPropertyAnimation(this, "geometry", this);
  m_animation_geo_start->setDuration(BFImportEntranceWidgetHideTime);
}

void BFImportEntranceWidget::resizeEvent(QResizeEvent* event)
{
  QPushButton::resizeEvent(event);
}

void BFImportEntranceWidget::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing |
                         QPainter::SmoothPixmapTransform);
  if (is_expand)
  {
	  painter.drawPixmap(this->rect(), getExpandPixmap());
  }
  else
  {
	  painter.drawPixmap(this->rect(), getShrinkPixmap());
  }
}

void BFImportEntranceWidget::enterEvent(QEvent* event)
{
  //已经是展开状态不操作
  if (is_expand) {
    return;
  }

  //动画未结束不操作
  if (m_animation_geo_start->state() == QPropertyAnimation::Running) {
    return;
  }

  if (m_check_leave_time->isActive()) {
    m_check_leave_time->stop();
  }

  //开始展开动画
  StartAnimation(true);

  is_expand = true;

  this->update();

  //每次进入的时候打开收缩定时器检测
  m_check_leave_time->start();
}

void BFImportEntranceWidget::leaveEvent(QEvent* event)
{
	this->update();
}

void BFImportEntranceWidget::mousePressEvent(QMouseEvent* event) {
#ifdef _DEBUG
  qDebug() << "BFImportEntranceWidget::mousePressEvent";
#endif
  if (event->button() == Qt::RightButton) {
    emit SigShowImportEnterToolWid();
  }
  return QPushButton::mousePressEvent(event);
}

void BFImportEntranceWidget::hideEvent(QHideEvent* event) {
  is_expand = false;
  m_check_leave_time->stop();
}

// void BFImportEntranceWidget::LoadStylePixmap() {
// 
// 	//不展开图
// 	QString image_shrink = GetSkinResourceAbsolutePath("import_entrance_shrink.svg");
// 	QSvgRenderer svg_render_shrink(image_shrink);
// 	QPixmap pix_shrink(this->rect().size() * g_fGlobalDPI);
// 	pix_shrink.fill(Qt::transparent);  //设置背景透明
// 	QPainter p_shrink(&pix_shrink);
// 	p_shrink.setRenderHint(QPainter::SmoothPixmapTransform);
// 	svg_render_shrink.render(&p_shrink);
// 
// 	m_pixmap_shrink = pix_shrink;
// 
// 
// 	//展开图
// 	QString image_expand = GetSkinResourceAbsolutePath("import_entrance_expand.svg");
// 	QSvgRenderer svg_render_expand(image_expand);
// 	QPixmap pix_expand(this->rect().size() * g_fGlobalDPI);
// 	pix_expand.fill(Qt::transparent);  //设置背景透明
// 	QPainter p_expand(&pix_expand);
// 	p_expand.setRenderHint(QPainter::SmoothPixmapTransform);
// 	svg_render_expand.render(&p_expand);
// 	m_pixmap_expand = pix_expand;
// }

void BFImportEntranceWidget::StartAnimation(bool is_expand) {

	if (is_expand)
	{
    QRect cur_rect = this->geometry();
	//左移50
    QRect new_rect = QRect(cur_rect.x()-50, cur_rect.y(), cur_rect.width(), cur_rect.height());
    m_animation_geo_start->setStartValue(cur_rect);
    m_animation_geo_start->setEndValue(new_rect);
	}
	else
	{
     QRect cur_rect = this->geometry();
     //右移50
     QRect new_rect = QRect(cur_rect.x() +50, cur_rect.y(),
                            cur_rect.width(), cur_rect.height());
     m_animation_geo_start->setStartValue(cur_rect);
     m_animation_geo_start->setEndValue(new_rect);
    }
	m_animation_geo_start->start();
}

const QPixmap& BFImportEntranceWidget::getExpandPixmap() {
  static double global_expand_dpi = -2.0;
  qreal dpi = BFSkinSetting::GetInstance()->GetDpi();
  if (global_expand_dpi != dpi) {
    global_expand_dpi = dpi;
    QString image_expand =
        GetSkinResourceAbsolutePath("import_entrance_expand.svg");
    QSvgRenderer svg_render_expand(image_expand);
    QPixmap pix_expand(this->rect().size() * global_expand_dpi);
    pix_expand.fill(Qt::transparent);  //设置背景透明
    QPainter p_expand(&pix_expand);
    p_expand.setRenderHint(QPainter::SmoothPixmapTransform);
    svg_render_expand.render(&p_expand);
    if(m_pixmap_expand){
      delete m_pixmap_expand;
    }
    m_pixmap_expand = new QPixmap;
    *m_pixmap_expand = pix_expand;
  }
  return *m_pixmap_expand;
}

const QPixmap& BFImportEntranceWidget::getShrinkPixmap() {
  static qreal global_shrink_dpi = -2.0;
  qreal dpi = BFSkinSetting::GetInstance()->GetDpi();
  if (global_shrink_dpi != dpi) {
    global_shrink_dpi = dpi;
    QString image_shrink =
        GetSkinResourceAbsolutePath("import_entrance_shrink.svg");
    QSvgRenderer svg_render_shrink(image_shrink);
    QPixmap pix_shrink(this->rect().size() * global_shrink_dpi);
    pix_shrink.fill(Qt::transparent);  //设置背景透明
    QPainter p_shrink(&pix_shrink);
    p_shrink.setRenderHint(QPainter::SmoothPixmapTransform);
    svg_render_shrink.render(&p_shrink);
    if(m_pixmap_shrink){
      delete m_pixmap_shrink;
    }
    m_pixmap_shrink = new QPixmap;
    *m_pixmap_shrink = pix_shrink;
  }
  return *m_pixmap_shrink;
}

void BFImportEntranceWidget::SlotCheckMouseLeave() {
  QPoint global_point = mapToGlobal(QPoint(0, 0));
  QRect global_rect = QRect(global_point, this->size());
  QPoint cur_mouse_pos = QCursor::pos();

  if (global_rect.contains(cur_mouse_pos) || m_tool_wid->isVisible()) {
    return;
  } else {


	//动画运行状态不操作
	if (m_animation_geo_start->state() == QPropertyAnimation::Running) {
      return;
    }


    //既不在按钮区域，工具按钮又没有打开的情况下关闭变为收缩状态
    //开始收缩动画
    StartAnimation(false);
    is_expand = false;
    m_check_leave_time->stop();
  }
}

QPixmap *BFImportEntranceWidget::m_pixmap_expand = nullptr;

QPixmap *BFImportEntranceWidget::m_pixmap_shrink = nullptr;

void BFImportEntranceToolWidget::SetRect(QRect rect) {
  this->setGeometry(rect);
}

void BFImportEntranceToolWidget::Show(QRect rect) {
  this->setGeometry(rect);
  this->show();
  this->activateWindow();

}

void BFImportEntranceToolWidget::SwitchStyleSheet() {}

void BFImportEntranceToolWidget::hideEvent(QHideEvent* event) {
  return QWidget::hideEvent(event);
}

void BFImportEntranceToolWidget::keyPressEvent(QKeyEvent* event) {
  return QWidget::keyPressEvent(event);
}

bool BFImportEntranceToolWidget::eventFilter(QObject* obj, QEvent* event) {
  if (obj == this && QEvent::WindowDeactivate == event->type()) {
    this->hide();
  }
  return QWidget::eventFilter(obj, event);
}

void BFImportEntranceToolWidget::mousePressEvent(QMouseEvent* event) {
#ifdef _DEBUG
  qDebug() << "BFImportEntranceToolWidget::mousePressEvent";
#endif
  if (event->button() == Qt::LeftButton) {

	QPoint global_point = mapToGlobal(QPoint(0, 0));
    QRect global_rect = QRect(global_point, this->size());
    QPoint cur_mouse_pos = QCursor::pos();

	if (global_rect.contains(cur_mouse_pos)) {
      this->hide();
      emit SigHideImportBall();
    } else {

     }
  }
  return QWidget::mousePressEvent(event);
}

void BFImportEntranceToolWidget::enterEvent(QEvent* event) {
  m_is_hover = true;
  this->update();
}

void BFImportEntranceToolWidget::leaveEvent(QEvent* event) {
  m_is_hover = false;
  this->update();
}

void BFImportEntranceToolWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing |QPainter::SmoothPixmapTransform);

  painter.drawPixmap(this->rect(), getBackPixmap());

  QFont font_13;
  font_13.setFamily(QString::fromUtf8("Microsoft Yahei"));
  font_13.setPixelSize(13);

  painter.setFont(font_13);
   if (m_is_hover) {
    painter.setPen(BFSkinSetting::GetInstance()->GetTextColor(0));
  } else {
    painter.setPen(BFSkinSetting::GetInstance()->GetTextColor(1));
  }

  QString need_str = QString::fromUtf8("隐藏导入入口");

  painter.drawText(QRect(rect().x(),rect().y()+2,rect().width(),rect().height()), Qt::AlignCenter,need_str);
}

void BFImportEntranceToolWidget::showEvent(QShowEvent* event) {
  bool is_show = isVisible();
  qDebug() << is_show;
}

BFImportEntranceToolWidget::BFImportEntranceToolWidget(
    QWidget* parent /*= Q_NULLPTR*/)
    :  m_is_hover(false)/*, m_back_svg_pix(QPixmap())*/ {
  //设置弹窗属性
#ifdef WIN32
  this->setWindowFlags(/*Qt::Popup | */Qt::FramelessWindowHint);
#else
  this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#endif

  this->installEventFilter(this);

  //透明
  this->setAttribute(Qt::WA_TranslucentBackground);

  //样式
  this->SwitchStyleSheet();

  //读取svg内存图
  //this->LoadStylePixmap();
}

// void BFImportEntranceToolWidget::LoadStylePixmap() {
// 
//   QString image =GetSkinResourceAbsolutePath("hide_import_entrance.svg");
//   QSvgRenderer svg_render(image);
//   QPixmap pix(this->rect().size() * g_fGlobalDPI);
//   qDebug() << this->rect().size();
//   pix.fill(Qt::transparent);  //设置背景透明
//   QPainter p(&pix);
//   p.setRenderHint(QPainter::SmoothPixmapTransform);
//   svg_render.render(&p);
// 
//   m_back_svg_pix = pix;
// }

const QPixmap& BFImportEntranceToolWidget::getBackPixmap() {
  static double global_back_dpi = -2.0;
  auto dpi = BFSkinSetting::GetInstance()->GetDpi();
  if (global_back_dpi != dpi) {
    global_back_dpi = dpi;
    QString image = GetSkinResourceAbsolutePath("hide_import_entrance.svg");
    QSvgRenderer svg_render(image);
    QPixmap pix(this->rect().size() * global_back_dpi);
    qDebug() << this->rect().size();
    pix.fill(Qt::transparent);  //设置背景透明
    QPainter p(&pix);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    svg_render.render(&p);
    if(m_back_svg_pix){
      delete m_back_svg_pix;
    }

    m_back_svg_pix = new QPixmap;
    *m_back_svg_pix = pix;
    m_back_svg_pix->setDevicePixelRatio(global_back_dpi);
  }
  return *m_back_svg_pix;
}

QPixmap *BFImportEntranceToolWidget::m_back_svg_pix = nullptr;

BFImportEntranceToolWidget::~BFImportEntranceToolWidget() {
#ifdef _DEBUG
  qDebug() << "BFImportEntranceToolWidget::~BFImportEntranceToolWidget()";
#endif
}
