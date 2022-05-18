#pragma once
#include <QWidget>

class QPushButton;
class QSlider;

class BFSliderActionWidget : public QWidget {
  Q_OBJECT
 public:
  explicit BFSliderActionWidget(QWidget* parent);
  void setZoomValue(int min, int max, int value);
  void zoomOutOneStep();
  void zoomInOneStep();
  bool eventFilter(QObject* watched, QEvent* event);
  int getZoomValue();
 signals:
  void signalScrollValueChanged(int);

 private:
  QPushButton* m_minus_btn = nullptr;
  QPushButton* m_plus_btn = nullptr;
  QSlider* m_slider = nullptr;
};