#include "tabwidget.h"
#include "tabbar.h"
#include <QLabel>
#include <QDebug>
#include <QMimeData>
#include <QMovie>
#include "toolbutton.h"
#include <QDragEnterEvent>
#include <QTimer>

TabWidget::TabWidget(QWidget *parent) :
    QWidget(parent)
{
    m_tabBar = NULL;
    m_previousWidget = NULL;
    m_currentWidget = NULL;

    m_stackedWidget = new QStackedWidget;
    m_mainnLayout = new QVBoxLayout (this);
    m_mainnLayout->setContentsMargins (0, 0, 0, 0);
    m_mainnLayout->setSpacing (0);
    m_mainnLayout->addWidget (m_stackedWidget, 1);
    connect(m_stackedWidget, SIGNAL(currentChanged(int)), SLOT(updateCurrentTabCloseButton(int)));
    connect(m_stackedWidget, SIGNAL(widgetRemoved(int)), SLOT(updateCurrentTabCloseButton(int)));
    connect(m_stackedWidget, SIGNAL(widgetRemoved(int)),
            SLOT(onTabRemoved(int)));

    m_lastContextMenuTab = -1;

//    connect(this, SIGNAL(tabRemoved(QWidget*)), SLOT(onTabRemoved(QWidget*)));
    setLayout(m_mainnLayout);
}

void TabWidget::setTabBar(TabBar *tabBar, bool bInsertToLayout)
{
    m_tabBar = tabBar;
    m_tabBar->setShape (QTabBar::RoundedNorth);

    connect (m_tabBar,
             SIGNAL (addNewTab()),
             this,
             SLOT (onAddNewTab ()));
    connect (m_tabBar,
             SIGNAL (tabCloseRequested (int)),
             this,
             SLOT (onTabCloseRequested (int)));
    connect (m_tabBar,
             SIGNAL (tabWasInserted (int)),
             this,
             SLOT (onTabInserted (int)));
//    connect (m_tabBar,
//             SIGNAL (tabWasRemoved (int)),
//             this,
//             SLOT (onTabRemoved (int)));

    connect (m_tabBar,
             SIGNAL (tabMoved (int, int)),
             this,
             SLOT (onTabMoved (int, int)));
    connect (m_tabBar,
             SIGNAL (currentChanged (int)),
             this,
             SLOT (onCurrentChanged (int)));
    connect (m_tabBar,
             SIGNAL (customContextMenuRequested (const QPoint&)),
             this,
             SLOT (onContextMenuRequested (const QPoint&)));
    connect (m_tabBar,
             SIGNAL (releasedMouseAfterMove (int)),
             this,
             SLOT (onReleaseMouseAfterMove (int)));

    m_tabBar->setTabWidget(this);
    if(bInsertToLayout)
    {
        m_mainnLayout->insertWidget(0, m_tabBar, 0);
    }
}

int TabWidget::widgetCount () const
{
    return m_stackedWidget->count ();
}

QWidget* TabWidget::widget (int index) const
{
    return m_stackedWidget->widget (index);
}

void TabWidget::onAddNewTab()
{

}

void TabWidget::onTabCloseRequested(int index)
{
    qDebug() << "on tab colosed requested: " << index;
    removeTab(index);
}

void TabWidget::onTabInserted(int index)
{
    Q_UNUSED(index);
}

void TabWidget::onTabDestroyed()
{
    QWidget* tab = qobject_cast<QWidget*>(sender());
    if(tab)
    {
        if(m_tabCloseButtons.contains(tab))
        {
            QToolButton* button = m_tabCloseButtons.take(tab);
            button->deleteLater();
        }

        if (tab == m_previousWidget)
            m_previousWidget = 0;
    }
}

void TabWidget::onTabRemoved(int index)
{
//    Q_UNUSED(index);
    qDebug() << "tab removed" << index;

    //m_stackedWidget->removeWidget (widget (index));
    if(index >=0 && index < m_tabBar->count())
    {
        m_tabBar->removeTab (index);
    }

    if(m_stackedWidget->count() == 0)
    {
        emit allTabsClosed();
    }
}

//void TabWidget::onTabRemoved(QWidget *tab)
//{
//    emit tabRemoved(tab);
//    qDebug() << "tab removed widget";

//}

void TabWidget::onTabMoved(int from, int to)
{
    if(!m_tabBar->isMoving())
    {
        m_stackedWidget->insertWidget (to, m_stackedWidget->widget (from));
        setCurrentIndex (to);
    }
}

void TabWidget::onCurrentChanged(int index)
{
    setCurrentIndex(index);
    //    if(m_currentIndex != index)
    //    {
    //        if(!m_tabCLoseIconSelected.isNull())
    //        {
    //            if(m_tabCloseButtons.contains(m_stackedWidget->currentWidget()))
    //            {
    //                m_tabCloseButtons[m_stackedWidget->currentWidget()]->setMultiIcon(m_tabCloseIconNormal);
    //            }

    //        }
    //        m_currentIndex = index;
    //        m_stackedWidget->setCurrentIndex(index);
    //        if(!m_tabCLoseIconSelected.isNull())
    //        {
    //            if(m_tabCloseButtons.contains(m_stackedWidget->currentWidget()))
    //            {
    //                m_tabCloseButtons[m_stackedWidget->currentWidget()]->setMultiIcon(m_tabCloseIconNormal);
    //            }

    //        }
    //        m_tabBar->updateAddTabButtonPos();
    //    }

}

void TabWidget::setCurrentTab (int tabIndex)
{
    m_tabBar->setCurrentIndex (tabIndex);
}

void TabWidget::setCurrentWidget (QWidget *widget)
{
    if (!widget)
        return;

    int index = m_stackedWidget->indexOf (widget);
    setCurrentIndex (index);
}

void TabWidget::onContextMenuRequested (const QPoint& point)
{
    if (point.isNull ())
        return;

    QMenu *menu = new QMenu ("", m_tabBar);
    int index = m_tabBar->tabAt (point);

    if (index == -1)
    {
        Q_FOREACH (QAction *act, m_tabBarActions)
        {
            if (!act)
            {
                qWarning () << Q_FUNC_INFO
                            << "detected null pointer";
                continue;
            }
            menu->addAction (act);
        }
    }
    else if ((index == m_tabBar->count () - 1) &&
             m_tabBar->isAddTabButtonVisible())
    {

    }
    else
    {
        m_lastContextMenuTab = index;
        delete menu;
        menu = tabMenu (index);
    }
    if(menu)
    {
        menu->exec (m_tabBar->mapToGlobal (point));
        delete menu;
    }


}

void TabWidget::onReleaseMouseAfterMove(int index)
{
    m_stackedWidget->insertWidget (index, m_stackedWidget->widget (m_currentIndex));
    setCurrentIndex(index);
}

void TabWidget::setPreviousTab ()
{
    setCurrentWidget (m_previousWidget);
}


int TabWidget::addTab (QWidget *widget, bool bCloseable, const QString& text, const HH::NewTabPositionFlags &openFlags)
{
    return addTab (widget, bCloseable, QIcon (), text, openFlags);
}

int TabWidget::addTab (QWidget *widget, bool bCloseable,
                       const QIcon& icon, const QString& text, const HH::NewTabPositionFlags &openFlags)
{
    Q_UNUSED(openFlags);
    if (!widget)
    {
        qWarning () << Q_FUNC_INFO
                    << "There is no widget to add to SeaprateTabWidget"
                    << (widget);
        return -1;
    }

    if (m_stackedWidget->indexOf (widget) != -1)
        return -1;

    int newIndex = 0;
    if(m_stackedWidget->count() == 0)
        m_currentWidget = widget;
    m_stackedWidget->addWidget (widget);
    connect(widget, SIGNAL(destroyed()), SLOT(onTabDestroyed()));
    newIndex = m_tabBar->addTab(icon, text);

    m_tabBar->setTabToolTip (newIndex, text);

    //    if (m_tabBar->currentIndex () >= widgetCount())
    //        setCurrentTab (widgetCount () - 1);
    if(bCloseable)
    {
        ToolButton* closeButton = newTabCloseButton(newIndex);
        if(closeButton)
        {
            m_tabCloseButtons[widget] = closeButton;
            if(!m_tabCLoseIconSelected.isNull() && m_stackedWidget->count() == 1)
            {
                closeButton->setMultiIcon(m_tabCLoseIconSelected);
            }
        }

    }
    setCurrentIndex(newIndex);
    return newIndex;
}

ToolButton* TabWidget::newTabCloseButton(int index)
{
    if(index >=0 && index < widgetCount())
    {
        ToolButton* closeButton = new ToolButton(m_tabBar);
        closeButton->setMultiIcon(m_tabCloseIconNormal);
        closeButton->setToolTip(tr("Close"));
        closeButton->setAutoRaise(true);
        closeButton->setFocusPolicy(Qt::NoFocus);
        m_tabBar->setTabClosable(index, true, closeButton);
        connect(closeButton, SIGNAL(clicked()), SLOT(onTabCloseButtonClicked()));
        return closeButton;
    }
    return NULL;

}

void TabWidget::updateCurrentTabCloseButton(int index)
{
    Q_UNUSED(index);
    if(!m_tabCLoseIconSelected.isNull())
    {
        for(int i=0; i<m_stackedWidget->count(); i++)
        {
            QWidget* wdt = widget(i);
            if(m_tabCloseButtons.contains(wdt))
            {
                if(i == m_stackedWidget->currentIndex())
                {

                    m_tabCloseButtons[wdt]->setMultiIcon(m_tabCLoseIconSelected);
                }
                else
                {
                    m_tabCloseButtons[wdt]->setMultiIcon(m_tabCloseIconNormal);
                }
            }

        }
    }
}

int TabWidget::insertTab (int index, QWidget *widget, bool bCloseable,
                          const QString& text)
{
    return insertTab (index, widget, bCloseable, QIcon (), text);
}

int TabWidget::insertTab (int index, QWidget *widget, bool bCloseable,
                          const QIcon& icon, const QString& text)
{
    int newIndex = index;
    if (index > widgetCount ())
        newIndex = widgetCount ();

    if(m_stackedWidget->count() == 0)
        m_currentWidget = widget;
    m_stackedWidget->insertWidget (index, widget);
    connect(widget, SIGNAL(destroyed()), SLOT(onTabDestroyed()));

    int idx = m_tabBar->insertTab (newIndex, icon, text);
    m_tabBar->setTabToolTip (idx, text);

    //    if (m_tabBar->currentIndex () >= widgetCount ())
    //        setCurrentTab (widgetCount () - 1);

    if(bCloseable)
    {
        ToolButton* closeButton = newTabCloseButton(idx);
        if(closeButton)
        {
            m_tabCloseButtons[widget] = closeButton;
        }
    }

    setCurrentIndex(idx);
    return idx;
}

void TabWidget::removeTab (int index)
{
    qDebug() << "remove tab: " << index;
    if (index >= widgetCount () || index < 0)
    {
        qWarning () << Q_FUNC_INFO
                    << "invalid index"
                    << index;
        return;
    }
//    if(m_tabCloseButtons.contains(m_stackedWidget->widget (index)))
//    {
//        QToolButton* button = m_tabCloseButtons.take(m_stackedWidget->widget (index));
//        button->deleteLater();
//    }

//    if (m_stackedWidget->widget (index) == m_previousWidget)
//        m_previousWidget = 0;


    QWidget* tab = widget(index);
    m_stackedWidget->removeWidget (tab);
//    m_tabBar->removeTab (index);
//    tab->disconnect();
//    tab->deleteLater();

//    if(m_stackedWidget->count() == 0)
//    {
//        emit allTabsClosed();
//    }
//    this->onTabRemoved(index);
//    if(m_tabCloseButtons.contains(m_stackedWidget->widget (index)))
//    {
//        QToolButton* button = m_tabCloseButtons.take(m_stackedWidget->widget (index));
//        button->deleteLater();
//    }

//    if (m_stackedWidget->widget (index) == m_previousWidget)
//        m_previousWidget = 0;

//    QWidget* tab = widget(index);
//    m_stackedWidget->removeWidget (widget (index));
//    m_tabBar->removeTab (index);
//    emit tabRemoved(tab);
//    if(m_stackedWidget->count() == 0)
//    {
//        emit allTabsClosed();
//    }
}

void TabWidget::removeAllTabs()
{
    while(widgetCount() > 0)
    {
        removeTab(0);
    }
}

void TabWidget::removeTab(QWidget *widget)
{
    removeTab(indexOf(widget));
}

int TabWidget::tabAt (const QPoint& point)
{
    return m_tabBar->tabAt (point);
}

void TabWidget::moveTab (int from, int to)
{
    m_tabBar->moveTab (from, to);
}


void TabWidget::addAction2TabBar (QAction *act)
{
    if(m_tabBarActions.indexOf(act) < 0)
    {
        m_tabBarActions << act;
        connect (act,
                 SIGNAL (destroyed (QObject*)),
                 this,
                 SLOT (onActionDestroyed ()));
    }

}

void TabWidget::insertAction2TabBar (int index, QAction *act)
{
    if(m_tabBarActions.indexOf(act) < 0)
    {
        m_tabBarActions.insert (index, act);
        connect (act,
                 SIGNAL (destroyed (QObject*)),
                 this,
                 SLOT (onActionDestroyed ()));
    }

}

void TabWidget::insertAction2TabBar (QAction *before, QAction *action)
{
    int idx = m_tabBarActions.indexOf (before);
    if (idx < 0)
        idx = m_tabBarActions.size ();
    insertAction2TabBar (idx, action);
}

void TabWidget::addWidget2MainLayout(QWidget *widget)
{
    m_mainnLayout->addWidget(widget, 0);
}

void TabWidget::insertWidget2MainLayout(int index, QWidget *widget)
{
    m_mainnLayout->insertWidget(index, widget, 0);
}

void TabWidget::removeWidgetFromMainLayout(QWidget * widget)
{
    m_mainnLayout->removeWidget(widget);
}

int TabWidget::mainLayoutWidgetCount()
{
    return m_mainnLayout->count();
}

void TabWidget::setTabCloseIcon(const QPixmap &iconNormal, const QPixmap &iconSelected)
{
    m_tabCloseIconNormal = iconNormal;
    m_tabCLoseIconSelected = iconSelected;
}

void TabWidget::setCurrentIndex (int index)
{
    if (index >= widgetCount ())
        index = widgetCount () - 1;

    if(index == m_stackedWidget->currentIndex())
    {
        return;
    }
    m_previousWidget = m_stackedWidget->currentWidget();
    //qDebug()  << "current tab index" << m_stackedWidget->currentIndex();
    m_stackedWidget->setCurrentIndex (index);
    m_currentWidget = m_stackedWidget->currentWidget();
    //qDebug()  << "current tab index" << m_stackedWidget->currentIndex();
    m_currentIndex = index;
    m_tabBar->setCurrentIndex (index);
    updateCurrentTabCloseButton();

}

int TabWidget::indexOf (QWidget *page) const
{
    return m_stackedWidget->indexOf (page);
}

int TabWidget::currentIndex () const
{
    return m_tabBar->currentIndex ();
}

QWidget* TabWidget::currentWidget () const
{
    return m_stackedWidget->currentWidget ();
}

QString TabWidget::tabText (int index) const
{
    return m_tabBar->tabText(index);
}

void TabWidget::setTabText (int index, const QString& text)
{
    if (index < 0 || index >= widgetCount ())
    {
        qWarning () << Q_FUNC_INFO
                    << "invalid index"
                    << index;
        return;
    }
    m_tabBar->setTabText (index, text);
}


QIcon TabWidget::tabIcon (int index) const
{
    if (!validIndex(index)) {
        return QIcon();
    }

    QLabel* label = qobject_cast<QLabel*>(m_tabBar->tabButton(index, m_tabBar->iconButtonPosition()));
    if (label && label->pixmap()) {
        return QIcon(*label->pixmap());
    }
    return QIcon();
}

QString TabWidget::tabToolTip (int index) const
{
    return m_tabBar->tabToolTip (index);
}

void TabWidget::setTabToolTip (int index, const QString& tip)
{
    if (index < 0 ||
            index >= widgetCount ())
    {
        qWarning () << Q_FUNC_INFO
                    << "invalid index"
                    << index;
        return;
    }

    m_tabBar->setTabToolTip (index, tip);
}

QMenu* TabWidget::tabMenu (int index)
{
    Q_UNUSED(index);
    return NULL;
}

void TabWidget::onActionDestroyed ()
{
    Q_FOREACH (QAction* act, m_tabBarActions)
        if (!act || act == sender ())
            m_tabBarActions.removeAll (act);
}

void TabWidget::onTabCloseButtonClicked()
{
    ToolButton* closeButton = qobject_cast<ToolButton*> (sender());
    QWidget* widget = m_tabCloseButtons.key(closeButton);
    if(widget)
    {
        onTabCloseRequested(indexOf(widget));
    }
}


void TabWidget::startTabAnimation(int index)
{
    if (!validIndex(index)) {
        return;
    }

    QLabel* label = qobject_cast<QLabel*>(m_tabBar->tabButton(index, m_tabBar->iconButtonPosition()));
    if (!label) {
        label = new QLabel();
        label->setObjectName("tab-icon");
        label->resize(QSize(16, 16));
        m_tabBar->setTabButton(index, m_tabBar->iconButtonPosition(), label);
    }

    if (label->movie()) {
        label->movie()->start();
        return;
    }

    QMovie* movie = new QMovie(m_loadAnimationFilePath, QByteArray(), label);
    movie->setScaledSize(label->size());
    movie->start();

    label->setMovie(movie);
}

void TabWidget::stopTabAnimation(int index)
{
    if (!validIndex(index)) {
        return;
    }

    QLabel* label = qobject_cast<QLabel*>(m_tabBar->tabButton(index, m_tabBar->iconButtonPosition()));

    if (label && label->movie()) {
        label->movie()->stop();
    }
}

void TabWidget::hideTabIcon(int index)
{
    if (!validIndex(index)) {
        return;
    }

    QLabel* label = qobject_cast<QLabel*>(m_tabBar->tabButton(index, m_tabBar->iconButtonPosition()));

    if (label) {
        m_tabBar->setTabButton(index, m_tabBar->iconButtonPosition(), NULL);
        //label->setVisible(bVisible);
        label->deleteLater();
    }
}

void TabWidget::setLoadAnimationFilePath(const QString &filepath)
{
    m_loadAnimationFilePath = filepath;
}


void TabWidget::setTabIcon(int index, const QIcon &icon)
{
    if (!validIndex(index)) {
        return;
    }
    hideTabIcon(index);
    if(!icon.isNull())
        m_tabBar->setTabIcon(index, icon);
//    if(icon.isNull())
//    {
//        hideTabIcon(index);
//    }

//    QLabel* label = qobject_cast<QLabel*>(m_tabBar->tabButton(index, m_tabBar->iconButtonPosition()));
//    if (!label) {
//        label = new QLabel();
//        label->setObjectName("tab-icon");
//        label->resize(16, 16);
//        m_tabBar->setTabButton(index, m_tabBar->iconButtonPosition(), label);
//    }

//    label->setPixmap(icon.pixmap(16, 16));
    //m_tabBar->setTabIcon(index, icon);
}

