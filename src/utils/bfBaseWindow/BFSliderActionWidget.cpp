#include "BFSliderActionWidget.h"
#include "bfskinmodule/bfskinsetting.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QMouseEvent>

BFSliderActionWidget::BFSliderActionWidget(QWidget* parent) : QWidget(parent) {
  m_minus_btn = new QPushButton(this);
  m_minus_btn->setIconSize(QSize(9, 9));
  m_minus_btn->setIcon(
      QIcon(BFSkinSetting::GetInstance()->GetSvgPixmapWithName("list_minus.svg")));
  m_minus_btn->setFixedSize(19, 19);
  connect(m_minus_btn, &QPushButton::clicked, this,
          [=]() { zoomInOneStep(); });

  m_plus_btn = new QPushButton(this);
  m_plus_btn->setIconSize(QSize(9, 9));
  m_plus_btn->setIcon(QIcon(
      BFSkinSetting::GetInstance()->GetSvgPixmapWithName("list_plus.svg")));
  m_plus_btn->setFixedSize(19, 19);
  connect(m_plus_btn, &QPushButton::clicked, this,
          [=]() { zoomOutOneStep(); });

  m_slider = new QSlider(Qt::Horizontal, this);
  m_slider->setFixedWidth(80);
  connect(m_slider, &QSlider::valueChanged, this,
          &BFSliderActionWidget::signalScrollValueChanged);
  m_slider->setInvertedAppearance(true);
  m_slider->installEventFilter(this);

  QHBoxLayout* m_main_layout = new QHBoxLayout(this);
  m_main_layout->setSpacing(5);
  m_main_layout->setContentsMargins(0, 0, 0, 0);
  m_main_layout->setMargin(0);
  m_main_layout->setAlignment(Qt::AlignCenter);
  m_main_layout->addWidget(m_minus_btn);
  m_main_layout->addWidget(m_slider);
  m_main_layout->addWidget(m_plus_btn);

  //放大缩小条子
  QString slider_str =
      ("QSlider"
       "{"
       "background-color:rgba(255,255,255,0);"
       "border-radius:0px;"
       "}"

       "QSlider::add-page:horizontal"
       "{"
       "background-color:"+
       BFSkinSetting::GetInstance()->GetNavScrollSliverColor().name(
           QColor::HexArgb) +
       ";"
       "border-radius:1px;"
       "}"

       "QSlider::sub-page:horizontal"
       "{"
       "background-color:#4F84FA"
       ";"
       "border-radius:1px;"
       "}"

       "QSlider::groove:horizontal"
       "{"
       "background:transparent;"
       "height:3px;"
       "}"

       "QSlider::handle:horizontal"
       "{"
       "width:13px;"
       "margin:-5px 0px -5px 0px;"
       "border-radius:6px;"
       "background-color:#E0E7FA"
       ";"
       "}");
  m_slider->setStyleSheet(slider_str);

  QString btn_style =
      "QPushButton{background:transparent;border:0px;} QPushButton:hover{border-radius:6px;background:#272936;}";
  m_minus_btn->setStyleSheet(btn_style);
  m_plus_btn->setStyleSheet(btn_style);
}

void BFSliderActionWidget::setZoomValue(int min, int max, int value) {
  m_slider->blockSignals(true);
  m_slider->setMinimum(min * 10);
  m_slider->setMaximum(max * 10);
  m_slider->setValue(value * 10);
  m_slider->blockSignals(false);
}

void BFSliderActionWidget::zoomOutOneStep() {
  int cur_value = m_slider->value();
  int max_value = m_slider->minimum();

  if (cur_value > max_value) {
    m_slider->setValue(cur_value - 10);
  }
}

void BFSliderActionWidget::zoomInOneStep() {
  int cur_value = m_slider->value();
  int max_value = m_slider->maximum();

  if (cur_value < max_value) {
    m_slider->setValue(cur_value + 10);
  }
}

bool BFSliderActionWidget::eventFilter(QObject* watched, QEvent* event) {

  if (watched ==m_slider )  //判断类型
  {
    if (event->type() == QEvent::MouseButtonPress) {
      QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
      if (mouseEvent->button() == Qt::LeftButton)  //判断左键
      {
        int max_value = m_slider->maximum();
        int min_value = m_slider->minimum();
        int dur = max_value - min_value;

        //由于滚动条逆置 真正的pos要用 dur减去pos
        double slider_width = m_slider->width();
        double mouse_pos = (double)mouseEvent->x();
        double distance = slider_width - mouse_pos;
        double rate = distance / slider_width;
        double value_distance = dur * rate;
        int pos = min_value + value_distance;

        //这里为了手柄能范围在区域之内 用了10进行一个猜测判断
        if ((pos < m_slider->sliderPosition() - 10) ||
            (pos > m_slider->sliderPosition() + 10)) {
          m_slider->setValue(pos);
          return true;
        } else {
          return QWidget::eventFilter(watched, event);
          //return true;
        }
      }
    }

    if (event->type() == QEvent::MouseButtonRelease) {
      return true;
    }
  }

  return QWidget::eventFilter(watched, event);
}
int BFSliderActionWidget::getZoomValue() { return m_slider->value(); }
