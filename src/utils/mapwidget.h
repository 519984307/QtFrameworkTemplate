#pragma once
#include <QLabel>
#include <QObject>
//图标加载控件
class BFSvgWidget : public QLabel {
	Q_OBJECT
 public:
  BFSvgWidget(const QString& path, QWidget* parent);
  ~BFSvgWidget();

 public:
  void setSvgPath(const QString& path);
  void setPixmap(const QPixmap& pixmap);

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event);

signals:
  void clicked();

 private:
  QPixmap m_pixmap;
  qreal m_dpi;
};