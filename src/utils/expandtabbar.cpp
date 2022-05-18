#include "expandtabbar.h"
#include <QStylePainter>
#include <QStyleOptionTabV2>
#include <QPainter>

ExpandTabBar::ExpandTabBar(QTabWidget *tabWidget) :
    QTabBar(tabWidget)
{
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_tabWidget = tabWidget;
    m_sizeHeight = 30;
}


QSize ExpandTabBar::tabSizeHint(int index) const
{
    QSize size = QTabBar::tabSizeHint(index);
    size.setHeight(m_sizeHeight);
    float temp = m_tabWidget->width() * 1.0 / m_tabWidget->count();
    size.setWidth(temp);
    if(index == count() - 1 && index > 0)
    {
        size.setWidth(m_tabWidget->width() - ((int)temp) * index);
    }

    return size;
}

void ExpandTabBar::setTabIcons(const QMap<int, QPixmap> &icons)
{
    m_icons = icons;
}

void ExpandTabBar::paintEvent (QPaintEvent *ev)
{
    //QPainter painterTabBar(this);
    QTabBar::paintEvent (ev);
    QStylePainter painter (this);
    for(int i=0; i<count(); i++)
    {
        QStyleOptionTabV2 option;
        initStyleOption (&option, i);
        painter.drawItemPixmap (option.rect, Qt::AlignCenter,
                                m_icons[i]);
    }
}
