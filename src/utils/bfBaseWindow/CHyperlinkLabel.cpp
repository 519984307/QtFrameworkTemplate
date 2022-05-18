#include "CHyperlinkLabel.h"
#include <QColor>

CHyperlinkLabel::CHyperlinkLabel(QWidget* parent) : QLabel(parent) {
  m_cursorType = Qt::PointingHandCursor;
  m_hover = QStringLiteral("<a style='color:") +
            QColor(79, 132, 250, 255).name(QColor::HexArgb) +
            QStringLiteral(
                ";font-family:\"Microsoft YaHei\";font-size:13px;' href = "
                "www..com>%1</a>");
  // m_normal = QStringLiteral("<a style='color:#666666;font-family:\"Microsoft
  // YaHei\";font-size:14px;' href = www..com>%1</a>");

  QString normalStyle = QStringLiteral("<a style='color:") +
                        QColor(162, 171, 195, 255).name(QColor::HexArgb) +
                        QStringLiteral(
                            ";font-family:\"Microsoft YaHei\";font-size:13x;' "
                            "href = www..com>%1</a>");
  m_normal = normalStyle;
}

CHyperlinkLabel::~CHyperlinkLabel() {}

void CHyperlinkLabel::enterEvent(QEvent* evt) {
  this->setCursor(QCursor(m_cursorType));
  this->setText(m_hover.arg(m_text));
}

void CHyperlinkLabel::leaveEvent(QEvent* evt) {
  this->unsetCursor();
  this->setText(m_normal.arg(m_text));
}
