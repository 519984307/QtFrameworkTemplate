#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include <QVariant>
#include <QWidget>

#include "utilsexport.h"

class UTILS_EXPORT ToolButton : public QToolButton
{
    Q_OBJECT

    Q_PROPERTY(QSize fixedsize READ size WRITE setFixedSize)
    Q_PROPERTY(int fixedwidth READ width WRITE setFixedWidth)
    Q_PROPERTY(int fixedheight READ height WRITE setFixedHeight)
    Q_PROPERTY(QPixmap multiIcon READ pixmap WRITE setMultiIcon)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QString themeIcon READ themeIcon WRITE setThemeIcon)
    Q_PROPERTY(QIcon fallbackIcon READ icon WRITE setFallbackIcon)

public:
    explicit ToolButton(QWidget* parent = 0);

    void setData(const QVariant &data);
    QVariant data();

    void setMultiIcon(const QPixmap &image);
    void setMultiIcon(const QString &imagePath);
    QPixmap pixmap() { return m_normalIcon; }

    void setThemeIcon(const QString &image);
    QString themeIcon() { return m_themeIcon; }

    void setFallbackIcon(const QIcon &image);
    void setIcon(const QIcon &image);

    void setShowMenuInside(bool inside);
    bool showMenuInside() const;

signals:
    void middleMouseClicked();
    void controlClicked();

public slots:
    void showMenu();

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    void paintEvent(QPaintEvent* e);

    bool m_usingMultiIcon;
    bool m_showMenuInside;

    QPixmap m_normalIcon;
    QPixmap m_hoverIcon;
    QPixmap m_activeIcon;
    QPixmap m_disabledIcon;

    QString m_themeIcon;
    QVariant m_data;
};

#endif // TOOLBUTTON_H
