#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QIcon>

#include "utilsexport.h"

class QMouseEvent;

class UTILS_EXPORT ClickableLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QSize fixedsize READ size WRITE setFixedSize)
    Q_PROPERTY(int fixedwidth READ width WRITE setFixedWidth)
    Q_PROPERTY(int fixedheight READ height WRITE setFixedHeight)
    Q_PROPERTY(QString themeIcon READ themeIcon WRITE setThemeIcon)
    Q_PROPERTY(QIcon fallbackIcon READ fallbackIcon WRITE setFallbackIcon)

public:
    explicit ClickableLabel(QWidget* parent = 0);
    void setClickable(bool bAble = true);
    bool isClickable()const {return m_bClickable;}
    QString themeIcon() const;
    void setThemeIcon(const QString &name);

    QIcon fallbackIcon() const;
    void setFallbackIcon(const QIcon &image);

signals:
    void clicked(QPoint);
    void clicked();
    void middleClicked(QPoint);
    void hoverEnter();
    void hoverLeave();

protected:
    void mouseReleaseEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void enterEvent(QEvent *ev);
    void leaveEvent(QEvent *ev);
private:
    QString m_themeIcon;
    bool m_bLeftPressed;
    bool m_bMiddlePressed;
    bool m_bClickable;

};

#endif // CLICKABLELABEL_H
