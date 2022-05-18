#ifndef CHYPERLINKLABEL_H
#define CHYPERLINKLABEL_H

#include <QLabel>

class CHyperlinkLabel : public QLabel {
  Q_OBJECT

 public:
  CHyperlinkLabel(QWidget* parent = 0);
  ~CHyperlinkLabel();

 public:
  // example <a style='color:red;font-family:\"Microsoft
  // YaHei\";font-size:14px;' href = www..com>%1</a>
  inline void SetHoverStyle(const QString& hoverStyle) { m_hover = hoverStyle; }
  // example <a style='color:red;font-family:\"Microsoft
  // YaHei\";font-size:14px;' href = www..com>%1</a>
  inline void SetNormalStyle(const QString& normalStyle) {
    m_normal = normalStyle;
  }
  inline void SetHyperlikeText(const QString& text) {
    m_text = text;
    setText(m_normal.arg(m_text));
  }

  inline void SetCursorHoverShape(Qt::CursorShape cursorType) {
    m_cursorType = cursorType;
  }

 protected:
  virtual void enterEvent(QEvent* evt);
  virtual void leaveEvent(QEvent* evt);

 private:
  Qt::CursorShape m_cursorType;
  QString m_hover;
  QString m_normal;
  QString m_text;
};

#endif  // CHYPERLINKLABEL_H
