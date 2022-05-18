#ifndef EXPANDTABBAR_H
#define EXPANDTABBAR_H

#include <QTabBar>
#include <QTabWidget>
#include <QIcon>
#include <QMap>

class ExpandTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit ExpandTabBar(QTabWidget *tabWidget);
    void setSizeHeight(const int height){m_sizeHeight = height;}

    void setTabIcons(const QMap<int, QPixmap> &icons);
signals:
    
public slots:

protected:
    QSize tabSizeHint(int index) const;
    void paintEvent (QPaintEvent* ev);
    
private:
    QTabWidget* m_tabWidget;
    QMap<int, QPixmap> m_icons;
    int m_sizeHeight;
};

#endif // EXPANDTABBAR_H
