#include "tabbar.h"
#include <QDrag>
#include <QDropEvent>
#include <QMouseEvent>
#include <QStyle>
#include <QStylePainter>
#include <QStyleOption>
#include <QApplication>
#include <QDebug>
#include <QToolButton>
#include <QMimeData>
#include <QString>
#include <QTimer>
#include "tabwidget.h"

TabBar::TabBar(TabWidget *parent) :
    QTabBar(parent),
    m_tabWidget(parent)
{
    m_buttonAddTab = new AddTabButton(this, this);
    connect(m_buttonAddTab, SIGNAL(clicked()), this, SIGNAL(addNewTab()));
    setSelectionBehaviorOnRemove (QTabBar::SelectLeftTab);
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Minimum);
    setExpanding (false);
    setIconSize (QSize (16, 16));
    setContextMenuPolicy (Qt::CustomContextMenu);
    setElideMode (Qt::ElideRight);
    setDocumentMode (true);
    setMovable (true);
    setAcceptDrops (true);
    setUsesScrollButtons(false);

    m_bInMove = false;
    m_maxTabWidth = 100;
    m_dragIndex = -1;


    moveAddTabButton(0);
}


TabBar::TabBar(QWidget *parent) :
    QTabBar(parent)
{
    setSelectionBehaviorOnRemove (QTabBar::SelectLeftTab);
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Minimum);
    setExpanding (false);
    setIconSize (QSize (16, 16));
    setContextMenuPolicy (Qt::CustomContextMenu);
    setElideMode (Qt::ElideRight);
    setDocumentMode (true);
    setMovable (true);
    setAcceptDrops (true);
    setUsesScrollButtons(false);

    m_bInMove = false;
    m_maxTabWidth = 100;
    m_dragIndex = -1;
    m_tabWidget = NULL;

    m_buttonAddTab = new AddTabButton(this, this);
    connect(m_buttonAddTab, SIGNAL(clicked()), this, SIGNAL(addNewTab()));
    moveAddTabButton(0);
}



void TabBar::setTabClosable (int index, bool closable, QToolButton *closeButton)
{
    if (index < 0 ||
            index >= count ())
    {
        qWarning () << Q_FUNC_INFO
                    << "invalid index "
                    << index;
        return;
    }
    setTabButton (index, closeButtonPosition (), closable ? closeButton : 0);
}
QTabBar::ButtonPosition TabBar::iconButtonPosition()
{
    return  QTabBar::LeftSide;
}


QTabBar::ButtonPosition TabBar::closeButtonPosition ()
{
    return QTabBar::RightSide;// static_cast<QTabBar::ButtonPosition> (style ()->
    //                 styleHint (QStyle::SH_TabBar_CloseButtonPosition));
}

void TabBar::setTabWidget(TabWidget *tabWidget)
{
    m_tabWidget = tabWidget;
}

void TabBar::setInMove (bool inMove)
{
    m_bInMove = inMove;
}


void TabBar::setMaxTabWidth(int width)
{
    m_maxTabWidth = width;
}

bool TabBar::isAddTabButtonVisible() const
{
    return m_buttonAddTab->isVisible();
}

void TabBar::setAddTabButtonVisible(bool bVisible)
{
    m_buttonAddTab->setVisible(bVisible);
    this->update();
}

QSize TabBar::tabSizeHint (int index) const
{
    QSize size = QTabBar::tabSizeHint (index);
    const int tc = count ();
    if (tc == 0)
        return size;
    if (m_tabWidths.contains(index))
    {
        size.setWidth(m_tabWidths[index]);
        return size;
    }
    int selfDefineTabTotalWidth = 0;
    foreach (int tabWidth, m_tabWidths.values())
    {
        selfDefineTabTotalWidth += tabWidth;
    }
    if (isAddTabButtonVisible())
    {
        const int target = std::min (m_maxTabWidth,
                                     (this->size ().width () - selfDefineTabTotalWidth - m_buttonAddTab->width()) / (tc - m_tabWidths.count()));
        size.setWidth (target);
        if(index == tc - 1)
        {
            updateAddTabButtonPos();
        }
    }
    else
    {
        const int target = std::min (m_maxTabWidth,
                                     (this->size ().width () - selfDefineTabTotalWidth) / (tc - m_tabWidths.count()));
        size.setWidth (target);
    }

    return size;
}

void TabBar::mouseReleaseEvent (QMouseEvent *event)
{
    m_dragIndex = -1;
    int index = tabAt (event->pos ());

    if (m_bInMove)
    {
        m_bInMove = false;
        emit releasedMouseAfterMove (currentIndex ());
        emit currentChanged (currentIndex ());
        if (!m_buttonAddTab->isVisible())
        {
            updateAddTabButtonPos();
            m_buttonAddTab->show();
        }
    }
    else if (isAddTabButtonVisible() && index != -1 &&
             event->button () == Qt::MidButton &&
             index != count () - 1)
        emit tabCloseRequested(index);

    QTabBar::mouseReleaseEvent (event);
}

void TabBar::mousePressEvent (QMouseEvent *event)
{
    setMovable (QApplication::keyboardModifiers () == Qt::NoModifier);

    if (event->button () == Qt::LeftButton && !m_bInMove && count() > 1)
    {
        m_ptDragStartPos = event->pos ();
        m_dragIndex = tabAt (event->pos ());

    }
    QTabBar::mousePressEvent (event);
}

void TabBar::mouseMoveEvent (QMouseEvent *event)
{
    if(m_dragIndex != -1 && !m_bInMove && (event->pos () - m_ptDragStartPos).manhattanLength () >= QApplication::startDragDistance ())
    {
        m_bInMove = true;
        if (isAddTabButtonVisible())
        {
            m_buttonAddTab->hide();
        }
        //        QWidget* widget = m_tabWidget->widget (m_dragIndex);

        //        QPixmap px = widget->grab();
        //        px = px.scaledToWidth (px.width () / 2, Qt::SmoothTransformation);

        //        QDrag* drag = new QDrag (this);
        //        QMimeData* data = new QMimeData ();
        //        data->setData ("x-leechcraft/tab-drag-action", "reordering");
        //        drag->setMimeData (data);
        //        drag->setPixmap (px);
        //        drag->exec ();

    }
    QTabBar::mouseMoveEvent (event);
}

void TabBar::dragEnterEvent (QDragEnterEvent *event)
{
    //    if (tabAt (event->pos ()) == count () - 1)
    //        return;

    //    const QMimeData* data = event->mimeData ();
    //    const QStringList& formats = data->formats ();
    //    if (formats.contains ("x-leechcraft/tab-drag-action") &&
    //            data->data ("x-leechcraft/tab-drag-action") == "reordering")
    //        event->acceptProposedAction ();
    QTabBar::dragEnterEvent(event);
}

void TabBar::dropEvent (QDropEvent *event)
{
    const int to = tabAt (event->pos ());

    if (m_dragIndex == to)
        return;

    moveTab (m_dragIndex, to);
    emit releasedMouseAfterMove (to);
    event->acceptProposedAction ();
}

void TabBar::mouseDoubleClickEvent (QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent (event);
    if (tabAt (event->pos ()) == -1)
        emit addNewTab();
}

void TabBar::tabInserted (int index)
{
    QTabBar::tabInserted (index);
    emit tabWasInserted (index);
    updateAddTabButtonPos();
}

void TabBar::tabRemoved (int index)
{
    QTabBar::tabRemoved (index);
    emit tabWasRemoved (index);
    updateAddTabButtonPos();
}

void TabBar::paintEvent (QPaintEvent *ev)
{
#ifdef Q_OS_MAC
    Q_UNUSED(ev);

    QStylePainter painter(this);

    for(int i = 0; i < count(); ++i)
    {
        QStyleOptionTabV2 option;
        initStyleOption(&option, i);
        //printf("tab text: %s\n", option.text.toLatin1().data());
        painter.drawControl(QStyle::CE_TabBarTab, option);
        //painter.drawItemPixmap(option.rect, 0, QPixmap("selected.png"));
        //painter.drawItemText(option.rect, 0, palette(), 1, option.text);
    }
#else
    Q_UNUSED(ev);

    QStylePainter painter(this);

    for(int i = 0; i < count(); ++i)
    {
        QStyleOptionTabV2 option;
        initStyleOption(&option, i);
        //printf("tab text: %s\n", option.text.toLatin1().data());
        painter.drawControl(QStyle::CE_TabBarTab, option);
        //painter.drawItemPixmap(option.rect, 0, QPixmap("selected.png"));
        //painter.drawItemText(option.rect, 0, palette(), 1, option.text);
    }

    //QTabBar::paintEvent (ev);
#endif
    //QTabBar::paintEvent (ev);


    //QStylePainter painter (this);

    //    Q_UNUSED(ev);
    //    QStyleOption opt;
    //    opt.init(this);
    //    QPainter p(this);
    //    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    //    if (count () > 0)
    //    {
    //        QStyleOptionTabV2 option;
    //        initStyleOption (&option, count () - 1);
    //        painter.drawItemPixmap (option.rect, Qt::AlignCenter,
    //                                m_addTabButtonIcon);
    //    }
}

void TabBar::wheelEvent(QWheelEvent* event)
{
    QTabBar::wheelEvent(event);
}

void TabBar::moveAddTabButton(int posX) const
{
    int posY = (height() - m_buttonAddTab->height()) / 2;
    posX = qMin(posX, width() - m_buttonAddTab->width());
    m_buttonAddTab->move(posX, posY);
}

void TabBar::resizeEvent(QResizeEvent *event)
{
    updateAddTabButtonPos();
    QTabBar::resizeEvent(event);
}

void TabBar::updateAddTabButtonPos() const
{
    int xForAddTabButton = this->size ().width () - m_buttonAddTab->width();
    const int tc = count ();
    int width = 0;
    if(m_tabWidths.count() > 0)
    {
        width = 0;
        for(int i=0; i<m_tabWidths.values().count(); i++)
        {
            width += m_tabWidths.values().at(i);
        }
        width += (tc-m_tabWidths.count())*m_maxTabWidth;
    }
    else
    {
        width = tc * m_maxTabWidth;
    }
    if(width + 2 < (this->size().width() - m_buttonAddTab->width()))
    {
        xForAddTabButton = width + 2;
    }

    moveAddTabButton(xForAddTabButton);
}

void TabBar::setTabWidth(int index, int width)
{
    m_tabWidths[index] = width;
    this->update();
}


AddTabButton::AddTabButton(QWidget *parent, TabBar* tabBar)
    : ToolButton(parent)
    , m_tabBar(tabBar)
{
    setObjectName("tabwidget-button-addtab");
    //setMultiIcon(QPixmap(":/resources/tabbar-addtab.png"));
    setAutoRaise(true);
    setFocusPolicy(Qt::NoFocus);
    setAcceptDrops(true);
    setToolTip(TabWidget::tr("New Tab"));
}

void AddTabButton::wheelEvent(QWheelEvent* event)
{
    m_tabBar->wheelEvent(event);
}

void AddTabButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton && rect().contains(event->pos())) {
        //m_tabWidget->addTabFromClipboard();
    }

    ToolButton::mouseReleaseEvent(event);
}

void AddTabButton::dragEnterEvent(QDragEnterEvent* event)
{
    const QMimeData* mime = event->mimeData();

    if (mime->hasUrls()) {
        event->acceptProposedAction();
        return;
    }

    ToolButton::dragEnterEvent(event);
}

void AddTabButton::dropEvent(QDropEvent* event)
{
    const QMimeData* mime = event->mimeData();

    if (!mime->hasUrls()) {
        ToolButton::dropEvent(event);
        return;
    }

    //    foreach (const QUrl &url, mime->urls()) {
    //        //m_tabWidget->addTab(url, Ww::NT_SelectedNewEmptyTab);
    //    }
}




