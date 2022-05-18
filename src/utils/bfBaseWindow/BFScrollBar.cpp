#include "BFScrollBar.h"
#include <QScrollBar>
#include <QFile>
#include<QEvent>
#include<QDebug>
#include "bfskinmodule/bfskinsetting.h"

#define BFScrollBarAnimationStartTime  150
#define BFScrollBarAnimationEndTime    150
#define BFScrollBarAnimationShowTime  150
#define BFScrollBarAnimationHideTime    150



#define BFScrollBarAnimationOpacityMouseLeaveValue    0.6
#define BFScrollBarAnimationOpacityMouseEnterValue     1
#define BFScrollBarAnimationOpacityInitValue          0.0

BFScrollBar::BFScrollBar(Qt::Orientation t, QWidget* parent) : QScrollBar(parent),
m_animation_geo_start(NULL),
m_wid_opacity(NULL),
m_animation_color_start(NULL),
animation_group_start(NULL),
m_animation_geo_end(NULL),
m_animation_color_end(NULL),
animation_group_end(NULL),
m_animation_color_show(NULL),
m_animation_color_hide(NULL),
m_watched_area(NULL) {
  //样式表
  this->SwitchStyleSheet();
  //动画
  this->InitAnimation();
  this->setOrientation(t);
  this->setRange(0, 0);
  this->hide();

  this->setContextMenuPolicy(Qt::NoContextMenu);
}

 BFScrollBar::~BFScrollBar() {
#ifdef _DEBUG
  qDebug() << "BFScrollBar::~BFScrollBar()";
#endif
}

void BFScrollBar::SwitchStyleSheet()
{
	    QString verticalBarStyle =
		QString("QScrollBar:vertical {border:none;background-color:rgba(100,0,0,0); width: 4px;border-radius:2px;}") +
        QString("QScrollBar::handle:vertical {margin:0px;border-radius: 2px;min-height:30px ;background-color:" + BFSkinSetting::GetInstance()->GetTreeScrollHandleColor().name(QColor::HexArgb) + ";}") +
		QString("QScrollBar::add-page:vertical{background-color:rgba(0,0,0,0);}") +
		QString("QScrollBar::sub-page:vertical{background-color:rgba(0,0,0,0);}") +
		QString("QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {border: 0px solid grey;width: 0px;height:0px;background-color:rgba(0,0,0,0);}") +
		QString("QScrollBar::add-line:vertical{subcontrol-origin:margin;border:0px;width:0px;height:0px;}") +
		QString("QScrollBar::sub-line:vertical{subcontrol-origin:margin;border:0px;width:0px;height:0px;}");
	    this->setStyleSheet(verticalBarStyle);
}

void BFScrollBar::InitAnimation()
{
	//开始动画设置
	//形变动画
	m_animation_geo_start = new QPropertyAnimation(this, "geometry", this);
	//加设颜色渐变类
	m_wid_opacity = new QGraphicsOpacityEffect(this);
	m_wid_opacity->setOpacity(BFScrollBarAnimationOpacityMouseLeaveValue);
	this->setGraphicsEffect(m_wid_opacity);
	//渐变动画
	m_animation_color_start = new QPropertyAnimation(m_wid_opacity, "opacity", this);
	m_animation_color_start->setDuration(BFScrollBarAnimationStartTime);
	m_animation_color_start->setStartValue(BFScrollBarAnimationOpacityMouseLeaveValue);
	m_animation_color_start->setEndValue(1.0);
	//加入动画组
	animation_group_start = new QParallelAnimationGroup(this);
	//animation_group_start->addAnimation(m_animation_geo_start);
	animation_group_start->addAnimation(m_animation_color_start);

	////结束动画设置
	////形变动画
	m_animation_geo_end = new QPropertyAnimation(this, "geometry", this);
	//渐变动画
	m_animation_color_end = new QPropertyAnimation(m_wid_opacity, "opacity", this);
	m_animation_color_end->setDuration(BFScrollBarAnimationEndTime);
	m_animation_color_end->setStartValue(1.0);
	m_animation_color_end->setEndValue(BFScrollBarAnimationOpacityMouseLeaveValue);
	//加入动画组
	animation_group_end = new QParallelAnimationGroup(this);
	//animation_group_end->addAnimation(m_animation_geo_end);
	animation_group_end->addAnimation(m_animation_color_end);

	///显示动画设置
	m_animation_color_show = new QPropertyAnimation(m_wid_opacity, "opacity", this);
	m_animation_color_show->setDuration(BFScrollBarAnimationShowTime);
	m_animation_color_show->setStartValue(BFScrollBarAnimationOpacityInitValue);
	m_animation_color_show->setEndValue(BFScrollBarAnimationOpacityMouseLeaveValue);


	///隐藏动画设置
	m_animation_color_hide = new QPropertyAnimation(m_wid_opacity, "opacity", this);
	m_animation_color_hide->setDuration(BFScrollBarAnimationShowTime);
	m_animation_color_hide->setStartValue(BFScrollBarAnimationOpacityMouseLeaveValue);
	m_animation_color_hide->setEndValue(BFScrollBarAnimationOpacityInitValue);
	connect(m_animation_color_hide, &QPropertyAnimation::finished, this, [this]()
	{
		this->hide();
	});
}

void BFScrollBar::SetScrollArea(QAbstractScrollArea* area, int h_margin,
                                int v_margin) {
  if (area)
  {
    m_watched_area = area;

	m_h_margin = h_margin;
    m_v_margin = v_margin;

	//安装事件过滤器
    m_watched_area->installEventFilter(this);


	//设置滚动条隐藏
    m_watched_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_watched_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->hide();

	//连接相应的信号和槽
	//检测的滚动条数值动，该滚动条数值变
    connect(m_watched_area->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this,
            SLOT(slot_valueChange_scrollBar(int)));

	//该滚动条数值变 通知检测的滚动条
	connect(this, &BFScrollBar::valueChanged, [&](int value) {
      m_watched_area->verticalScrollBar()->setValue(value);
    });

    //监测的滚动条范围变
    connect(m_watched_area->verticalScrollBar(), SIGNAL(rangeChanged(int, int)),
            this, SLOT(slot_rangeChanged(int, int)));

	//刷新
	this->update();
  }
}

void BFScrollBar::AnimationShow() {
	//已经播放return
	if (m_animation_color_show->state() == QAbstractAnimation::Running)
	{
		return;
	}

	//显示之前设置下步长
    int page_step = m_watched_area->verticalScrollBar()->pageStep();
    this->setPageStep(page_step);

	//显示
	this->show();
	m_animation_color_show->start();
}

void BFScrollBar::AnimationHide()
{
	//已经播放return
	if (m_animation_color_hide->state() == QAbstractAnimation::Running)
	{
		return;
	}
	//动画结束启动
	m_animation_color_hide->start();
}

void BFScrollBar::AnimationEnter()
{
	//一定是已经显示的

	//获取当前的位置，以改位置作为基准
	QRect ori_rect = this->geometry();

	int end_x = ori_rect.x()- (BFScrollBarWidthBehind- BFScrollBarWidthFront);
	int end_y = ori_rect.y();
	int end_width = BFScrollBarWidthBehind;
	int end_height =  ori_rect.height();

	QRect cur_rect = QRect(end_x, end_y, end_width, end_height);

	//显示的时候配置下形状动画
	m_animation_geo_start->setDuration(BFScrollBarAnimationStartTime);
	m_animation_geo_start->setStartValue(ori_rect);
	m_animation_geo_start->setEndValue(cur_rect); //+4为了保证遮住搜索图标

	if (animation_group_start->state() != QAbstractAnimation::Running)
	{
		animation_group_start->start();
	}
}

void BFScrollBar::AnimationLeave()
{
	//一定是已经显示的
   //获取当前的位置，以改位置作为基准
	QRect ori_rect = this->geometry();
	int end_x = ori_rect.x()+ (BFScrollBarWidthBehind - BFScrollBarWidthFront);
	int end_y = ori_rect.y();
	int end_width = BFScrollBarWidthFront;
	int end_height = ori_rect.height();
	QRect cur_rect = QRect(end_x, end_y, end_width, end_height);

	//显示的时候配置下形状动画
	m_animation_geo_end->setDuration(BFScrollBarAnimationEndTime);
	m_animation_geo_end->setStartValue(ori_rect);
	m_animation_geo_end->setEndValue(cur_rect);

	if (animation_group_end->state() != QAbstractAnimation::Running)
	{
		animation_group_end->start();
	}
}

void BFScrollBar::slot_rangeChanged(int min, int max)
{
  this->setMinimum(min);
  this->setRange(0, max);

  if (m_watched_area) {
    int page_step = m_watched_area->verticalScrollBar()->pageStep();
    this->setPageStep(page_step);
  } else {
    int page_step = 0.75 * (this->height() + max);
    this->setPageStep(page_step);
  }

  if (max <= 0) {
    this->hide();
  } else {
    //如果包含鼠标
    if (this->geometry().contains(this->mapFromGlobal(QCursor::pos()))) {
      this->show();
    }
  }
}

void BFScrollBar::enterEvent(QEvent* event)
{
	this->AnimationEnter();
	return QScrollBar::enterEvent(event);
}

void BFScrollBar::leaveEvent(QEvent* event)
{
  //qDebug() << "BFScrollBar::leaveEvent(QEvent* event)";
	this->AnimationLeave();
	return QScrollBar::leaveEvent(event);
}

void BFScrollBar::showEvent(QShowEvent* event)
{
	return QScrollBar::showEvent(event);
}

bool BFScrollBar::eventFilter(QObject* object, QEvent* event) {

	if (m_watched_area)
	{

     //大小改变
    if (object == m_watched_area && event->type() == QEvent::Resize)
	{
       //大小改变自定义滚动条位置
       int x =
           m_watched_area->width() - BFScrollBarWidthFront - 4 + m_h_margin;  //设置偏移值
       QRect need_rect = QRect(x, 1 + +m_v_margin, BFScrollBarWidthFront,
                               m_watched_area->height() - 2);
       this->setGeometry(need_rect);
    }

	//进入
    if (object == m_watched_area && event->type() == QEvent::Enter)
	{
      //qDebug() << "BFScrollBar::eventFilter Enter m_watched_area";
      //滚动条显示
      int scroll_max = this->maximum();
      if (scroll_max > 0) {

        this->AnimationShow();
      }
    }

    //离开
    if (object == m_watched_area && event->type() == QEvent::Leave)
	{
      //滚动条直接隐藏
      this->AnimationHide();
      //大小恢复自定义滚动条位置
      int x = m_watched_area->width() - BFScrollBarWidthFront - 4 +
              m_h_margin;  //设置偏移值
      this->setGeometry(x,  1 + m_v_margin, BFScrollBarWidthFront,
                        m_watched_area->height() - 2);
    }
    }
	return QScrollBar::eventFilter(object, event);
}

void BFScrollBar::hideEvent(QHideEvent* event) {
	int test_hide = 0;
  //qDebug() << "BFScrollBar::hideEvent";
}

void BFScrollBar::slot_valueChange_scrollBar(int value)
{
	this->setValue(value);
}
