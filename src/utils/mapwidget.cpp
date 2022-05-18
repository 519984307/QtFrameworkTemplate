#include "mapwidget.h"
#include "bfskinmodule/bfskinsetting.h"
#include <QPainter>
#include <QSvgRenderer>
BFSvgWidget::BFSvgWidget(const QString& path, QWidget* parent)
    : QLabel(parent) {
  // TODO 获取DPI
  m_dpi = BFSkinSetting::GetInstance()->GetDpi();

  setSvgPath(path);
}

BFSvgWidget::~BFSvgWidget() {}

void BFSvgWidget::setSvgPath(const QString& path) {
  QSvgRenderer render_svg(path);

  qreal dpi = BFSkinSetting::GetInstance()->GetDpi();
  QSize default_size = render_svg.defaultSize() * dpi;  //图片默认大小
  QImage img(default_size, QImage::Format_ARGB32_Premultiplied);
  img.fill(Qt::transparent);
  QPainter painter(&img);
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                         QPainter::SmoothPixmapTransform);
  render_svg.render(&painter);
  m_pixmap = QPixmap::fromImage(img);
  m_pixmap.setDevicePixelRatio(dpi);
}

void BFSvgWidget::setPixmap(const QPixmap& pixmap) { m_pixmap = pixmap; }

void BFSvgWidget::paintEvent(QPaintEvent*) {
  QPainter p(this);
  p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                   QPainter::SmoothPixmapTransform);
  //由SVGRender读取的图片大小可能和控件大小不同，需要缩放
  /* if (m_pixmap.size() != this->size()) {
     double dpi = 1;
     m_pixmap =
         m_pixmap.scaled(this->size().width() * dpi, this->size().height() *
   dpi, Qt::KeepAspectRatio, Qt::SmoothTransformation);
   }*/
  if (!m_pixmap.isNull()) p.drawPixmap(this->rect(), m_pixmap);
}

void BFSvgWidget::mouseReleaseEvent(QMouseEvent* event) {
  emit clicked();
  QWidget::mouseReleaseEvent(event);
}
