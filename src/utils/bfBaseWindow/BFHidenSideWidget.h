#pragma once

#include <QPainterPath>
#include <QWidget>

class QTimer;

enum class SideType {
  E_None = 0,
  E_Left,
  E_Right,
};

class BFHidenSideWidget : public QWidget {
  Q_OBJECT
 public:
  explicit BFHidenSideWidget(QWidget* parent);
  virtual ~BFHidenSideWidget() {}
  QPainterPath getTriangle() const { return m_cur_triangle; }
  virtual void setTriangle(bool show) {}
  virtual QPainterPath getPath() = 0;

 protected:
  bool eventFilter(QObject* watched, QEvent* event);
  void paintEvent(QPaintEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 public slots:
  void slotStartTimer();
  void slotStopTimer();
  virtual void slotShowTimerTimeout();
  virtual void slotHideTimerTimeout();

 signals:
  void signalLeftClicked();                              // signal:左侧点击
  void signalRightClicked();                             // signal:右侧点击
  void signalTriggered(QWidget* w, bool force = false);  //触发显示区域

 protected:
  virtual void calcPanterRegion() = 0;       //计算绘制区域
  virtual void drawWidget(QPainter& p) = 0;  //绘制图案
  void calcTriangle();                       //计算左右三角形区域

 protected:
  QWidget* m_parent = nullptr;     //父控件
  QPainterPath m_left_triangle;    //左侧三角
  QPainterPath m_right_triangle;   //右侧三角
  QPainterPath m_cur_triangle;     //当前三角
  QTimer* m_show_timer = nullptr;  //显示计时器
  QTimer* m_hide_timer = nullptr;  //隐藏计时器
  bool m_show = false;             //显示标志位
  bool m_b_left_triangle = false;  //当前是左三角
};

class BFLeftHidenSideWidget : public BFHidenSideWidget {
  Q_OBJECT
 public:
  BFLeftHidenSideWidget(QWidget* parent);
  ~BFLeftHidenSideWidget() {}

  QPainterPath getPath() override { return m_left_path; }
  void setTriangle(bool show) override;

 protected:
  void mousePressEvent(QMouseEvent* event);

 public slots:
  void slotShowTimerTimeout() override;
  void slotHideTimerTimeout() override;

 private:
  void calcPanterRegion() override;       //计算绘制区域
  void drawWidget(QPainter& p) override;  //绘制图案

 private:
  QRect m_left_triger_rect;  //左侧触发区域
  QPainterPath m_left_path;  //左侧绘制区域
};

class BFRightHidenSideWidget : public BFHidenSideWidget {
  Q_OBJECT
 public:
  BFRightHidenSideWidget(QWidget* parent);
  ~BFRightHidenSideWidget() {}

  QPainterPath getPath() override { return m_right_path; }
  void setTriangle(bool show) override;

 protected:
  void mousePressEvent(QMouseEvent* event);

 public slots:
  void slotShowTimerTimeout() override;
  void slotHideTimerTimeout() override;

 private:
  void calcPanterRegion() override;       //计算绘制区域
  void drawWidget(QPainter& p) override;  //绘制图案

 private:
  QRect m_right_triger_rect;  //右侧触发区域
  QPainterPath m_right_path;  //右侧绘制区域
};