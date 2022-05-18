#include "BFHidenSideWidget.h"
#include "bfskinmodule/bfskinsetting.h"
#include <QCursor>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

#define SideWidgetWidth 10
#define SideWidgetHeight 70

BFHidenSideWidget::BFHidenSideWidget(QWidget* parent)
    : QWidget(parent), m_parent(parent) {
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

  m_show_timer = new QTimer(this);
  m_show_timer->setInterval(200);
  connect(m_show_timer, &QTimer::timeout, this,
          &BFHidenSideWidget::slotShowTimerTimeout);
  m_hide_timer = new QTimer(this);
  m_hide_timer->setInterval(200);
  connect(m_hide_timer, &QTimer::timeout, this,
          &BFHidenSideWidget::slotHideTimerTimeout);
  this->setMouseTracking(true);
  m_parent->setMouseTracking(true);
  m_parent->installEventFilter(this);
}

void BFHidenSideWidget::slotStartTimer() {
  m_show_timer->start(10);
  m_hide_timer->stop();
}

void BFHidenSideWidget::slotStopTimer() { m_show_timer->stop(); }

void BFHidenSideWidget::slotShowTimerTimeout() {
  m_show = true;
  m_hide_timer->start(1500);
  m_show_timer->stop();
  this->setFixedWidth(10);
  calcPanterRegion();
  this->update();
}

void BFHidenSideWidget::slotHideTimerTimeout() {
  m_show = false;
  m_hide_timer->stop();
  this->setFixedWidth(m_show ? SideWidgetWidth : 1);
  calcPanterRegion();
  this->update();
}

bool BFHidenSideWidget::eventFilter(QObject* watched, QEvent* event) {
  if (watched == m_parent && event->type() == QEvent::Resize) {
    calcPanterRegion();
  }
  return false;
}

void BFHidenSideWidget::paintEvent(QPaintEvent* event) {
  QPainter p(this);
  p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                   QPainter::SmoothPixmapTransform);
  p.setPen(Qt::NoPen);
  if (m_show) {
    drawWidget(p);
  } else {
    //p.setBrush(BFSkinSetting::GetInstance()->GetMidWinBackgroundColor());
    p.setBrush(QColor(0,0,0,0));
    p.drawRect(this->rect());
  }
  QWidget::paintEvent(event);
}

void BFHidenSideWidget::mouseMoveEvent(QMouseEvent* event) {
  if (m_show && getPath().contains(event->pos())) {
    m_hide_timer->start(1500);
    emit signalTriggered(this, true);
    setCursor(Qt::PointingHandCursor);
  } else {
    if (this->rect().contains(event->pos())) {
      emit signalTriggered(this);
    }
    setCursor(Qt::ArrowCursor);
  }
  QWidget::mouseMoveEvent(event);
}

void BFHidenSideWidget::calcTriangle() {
  //计算三角区域
  m_left_triangle.clear();
  m_left_triangle.moveTo(QPoint(2, this->height() / 2));
  m_left_triangle.lineTo(QPoint(this->width() - 2, this->height() / 2 + 6));
  m_left_triangle.lineTo(QPoint(this->width() - 2, this->height() / 2 - 6));
  m_left_triangle.lineTo(QPoint(2, this->height() / 2));
  //计算右侧三角区域
  m_right_triangle.clear();
  m_right_triangle.moveTo(QPoint(this->width() - 2, this->height() / 2));
  m_right_triangle.lineTo(QPoint(2, this->height() / 2 + 6));
  m_right_triangle.lineTo(QPoint(2, this->height() / 2 - 6));
  m_right_triangle.lineTo(QPoint(this->width() - 2, this->height() / 2));

  m_cur_triangle = m_b_left_triangle ? m_left_triangle : m_right_triangle;
}

BFLeftHidenSideWidget::BFLeftHidenSideWidget(QWidget* parent)
    : BFHidenSideWidget(parent) {}

void BFLeftHidenSideWidget::calcPanterRegion() {
  int x = 0;
  int y = m_show ? ((m_parent->height() - SideWidgetHeight) / 2) : 0;
  this->move(x, y);
  this->setFixedSize(10, m_show ? SideWidgetHeight : m_parent->height());

  calcTriangle();

  //左侧触发区域
  m_left_triger_rect = QRect(0, 0, SideWidgetWidth, rect().height());
  QRect left_rect(0, rect().height() / 2 - SideWidgetHeight / 2,
                  SideWidgetWidth, SideWidgetHeight);

  //计算左侧绘制区域
  QPainterPath left_path;
  left_path.moveTo(left_rect.topLeft());
  QPoint bp1, bp2;
  bp1.setX(left_rect.topRight().x() - 2);
  bp1.setY(left_rect.topRight().y() + 2);
  bp2.setX(left_rect.bottomRight().x() - 2);
  bp2.setY(left_rect.bottomRight().y() - 2);
  left_path.cubicTo(
      bp1, bp1,
      QPoint(left_rect.width(), left_rect.y() + left_rect.height() / 10));
  left_path.lineTo(
      QPoint(left_rect.width(), left_rect.y() + left_rect.height() * 9 / 10));
  left_path.cubicTo(bp2, bp2, QPoint(left_rect.bottomLeft()));
  left_path.lineTo(left_rect.topLeft());
  m_left_path = left_path;
}

void BFLeftHidenSideWidget::drawWidget(QPainter& p) {
  p.setBrush(BFSkinSetting::GetInstance()->GetSideMainColor());
  p.drawPath(m_left_path);
  p.setBrush(BFSkinSetting::GetInstance()->GetSideArrowColor());
  p.drawPath(getTriangle());
}

void BFLeftHidenSideWidget::slotShowTimerTimeout() {
  BFHidenSideWidget::slotShowTimerTimeout();
}

void BFLeftHidenSideWidget::setTriangle(bool show) {
  m_cur_triangle = show ? m_left_triangle : m_right_triangle;
  m_b_left_triangle = show ? true : false;
}

void BFLeftHidenSideWidget::mousePressEvent(QMouseEvent* event) {
  if (m_show && getPath().contains(event->pos())) {
    emit signalLeftClicked();
  }
  QWidget::mousePressEvent(event);
}

void BFLeftHidenSideWidget::slotHideTimerTimeout() {
  BFHidenSideWidget::slotHideTimerTimeout();
}

BFRightHidenSideWidget::BFRightHidenSideWidget(QWidget* parent)
    : BFHidenSideWidget(parent) {}

void BFRightHidenSideWidget::calcPanterRegion() {
  this->setFixedSize(m_show ? SideWidgetWidth : 1,
                     m_show ? SideWidgetHeight : m_parent->height());
  int width = m_show ? 10 : 1;
  int y = m_show ? ((m_parent->height()-SideWidgetHeight)/2) : 0;
  this->move(m_parent->width() - width, y);

  calcTriangle();

  //计算右侧触发区域
  m_right_triger_rect =
      QRect(this->width() - 10, 0, SideWidgetWidth, rect().height());
  QRect right_rect(this->width() - 10,
                   rect().height() / 2 - SideWidgetHeight / 2, SideWidgetWidth,
                   SideWidgetHeight);

  //计算右侧绘制区域
  QPainterPath right_path;
  right_path.moveTo(right_rect.topRight());
  QPoint bp3, bp4;
  bp3.setX(right_rect.topLeft().x() + 2);
  bp3.setY(right_rect.topLeft().y() + 2);
  bp4.setX(right_rect.bottomLeft().x() + 2);
  bp4.setY(right_rect.bottomLeft().y() - 2);
  right_path.cubicTo(
      bp3, bp3,
      QPoint(right_rect.x(), right_rect.y() + right_rect.height() / 10));
  right_path.lineTo(
      QPoint(right_rect.x(), right_rect.y() + right_rect.height() * 9 / 10));
  right_path.cubicTo(bp4, bp4, QPoint(right_rect.bottomRight()));
  right_path.lineTo(right_rect.topRight());
  m_right_path = right_path;
}

void BFRightHidenSideWidget::drawWidget(QPainter& p) {
  p.setBrush(BFSkinSetting::GetInstance()->GetSideMainColor());
  p.drawPath(m_right_path);
  p.setBrush(BFSkinSetting::GetInstance()->GetSideArrowColor());
  p.drawPath(getTriangle());
}

void BFRightHidenSideWidget::slotShowTimerTimeout() {
  BFHidenSideWidget::slotShowTimerTimeout();
}

void BFRightHidenSideWidget::setTriangle(bool show) {
  m_cur_triangle = show ? m_right_triangle : m_left_triangle;
  m_b_left_triangle = show ? false : true;
}

void BFRightHidenSideWidget::mousePressEvent(QMouseEvent* event) {
  if (m_show && getPath().contains(event->pos())) {
    emit signalRightClicked();
  }
  QWidget::mousePressEvent(event);
}

void BFRightHidenSideWidget::slotHideTimerTimeout() {
  BFHidenSideWidget::slotHideTimerTimeout();
}
