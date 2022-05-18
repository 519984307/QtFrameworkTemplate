#include "styleviewer.h"

#include <QShortcut>
#include <QWebHitTestResult>
#include <QMenu>
#include <QContextMenuEvent>
#include <QScrollEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QDesktopServices>
#include <QApplication>
#include <QClipboard>

StyleViewer::StyleViewer(const QString &chatImagePath, QWidget *AParent) : QWebView(AParent)
{
    setPage(new ChatWebPage(this));
	setAcceptDrops(false);
    //setContextMenuPolicy(Qt::CustomContextMenu);
    setContextMenuPolicy(Qt::DefaultContextMenu);
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QShortcut *shortcut = new QShortcut(QKeySequence::Copy,this,NULL,NULL,Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), SLOT(onShortcutActivated()));
    m_scrollDeltaY = 0;
    m_chatImagePath = chatImagePath;

//    this->page()->mainFrame()->scr
}

StyleViewer::~StyleViewer()
{

}

QSize StyleViewer::sizeHint() const
{
	return QSize(256,192);
}

void StyleViewer::onShortcutActivated()
{
    qDebug() << "StyleViewer::onShortcutActivated";
	triggerPageAction(QWebPage::Copy);
}

void StyleViewer::onCopyActionTriggered()
{
    qDebug() << "StyleViewer::onCopyActionTriggered";
}

void StyleViewer::contextMenuEvent(QContextMenuEvent *event)
{
	QWebHitTestResult r = page()->mainFrame()->hitTestContent(event->pos());
	QMenu menu(this);

#ifdef QT_DEBUG
    if (page()->settings()->testAttribute(QWebSettings::DeveloperExtrasEnabled))
    {
        QAction* inspect = new QAction("check elements", this);
        //inspect->setShortcuts(cmds.InspectShortcuts());
        connect(inspect, SIGNAL(triggered()), this, SLOT(slotInspectElement()));
        menu.addAction(inspect);
    }
#endif
    if(!r.imageUrl().isEmpty())
    {
        QString tempUrl = r.imageUrl().toString();
        if(tempUrl.contains(m_chatImagePath))
        {
            QString realUrl = m_chatImagePath + "/" + r.imageUrl().fileName();
            if(QFile::exists(realUrl))
            {
                m_hittingImagePath = realUrl;
                QAction *saveImage = new QAction(tr("image save as"), this);
                connect(saveImage, SIGNAL(triggered()), this, SLOT(imageSaveAs()));

                QAction *copyImage = new QAction(tr("copy image"), this);
                QClipboard *clipboard = QApplication::clipboard();
                QString imagePath = m_hittingImagePath;
                connect(copyImage, &QAction::triggered, [clipboard, imagePath](){
                    clipboard->setImage(QImage(imagePath));
                });

                menu.addAction(copyImage);
                menu.addAction(saveImage);
            }
        }
    }
    if (!menu.isEmpty())
    {
        menu.exec(mapToGlobal(event->pos()));
        return;
    }
    //QWebView::contextMenuEvent(event);
}

void StyleViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWebHitTestResult r = page()->mainFrame()->hitTestContent(event->pos());
    if(!r.imageUrl().isEmpty())
    {
        QString tempUrl = r.imageUrl().toString();
        if(tempUrl.contains(m_chatImagePath))
        {
            QString realUrl = m_chatImagePath + "/" + r.imageUrl().fileName();
            if(QFile::exists(realUrl))
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile(realUrl));
            }
        }
    }
    QWebView::mouseDoubleClickEvent(event);
}

void StyleViewer::enterEvent(QEvent *e)
{
    emit enter();
    QWebView::enterEvent(e);
}

void StyleViewer::leaveEvent(QEvent *e)
{
    emit leave();
    QWebView::leaveEvent(e);
}

void StyleViewer::imageSaveAs()
{
    qDebug() << "StyleViewer::imageSaveAs";
    if(!m_hittingImagePath.isEmpty())
    {
        qDebug() << "StyleViewer::imageSaveAs :" << m_hittingImagePath;
        QFileInfo info(m_hittingImagePath);
        QString newName = QFileDialog::getSaveFileName(0, tr("Save Image"),
            QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/" + info.fileName(),
            tr("Images (*.jpg)"));
        if(!newName.isEmpty())
            QFile::copy(m_hittingImagePath, newName);
        m_hittingImagePath.clear();
    }
}

void StyleViewer::slotInspectElement()
{
	if (page()->settings()->testAttribute(QWebSettings::DeveloperExtrasEnabled))
		page()->triggerAction(QWebPage::InspectElement, false);
}

void StyleViewer::wheelEvent(QWheelEvent *event)
{
    //qDebug() << "StyleViewer wheelEvent angle delta: " << event->angleDelta();
    if(event->angleDelta().y() > 0)
    {
        if(page()->mainFrame()->scrollPosition().y() <= page()->mainFrame()->scrollBarMinimum(Qt::Vertical)
                && !page()->mainFrame()->scrollBarGeometry(Qt::Vertical).isNull())
        {
            m_scrollDeltaY += event->angleDelta().y();
            if(m_scrollDeltaY > 360)
            {
                qDebug() << "StyleViewer wheelEvent arrive top!!!";
                QTimer::singleShot(0, this, SLOT(scrollToTop()));
                m_scrollDeltaY = 0;
            }
        }
    }
    else
        m_scrollDeltaY = 0;

    QWebView::wheelEvent(event);
}

void StyleViewer::scrollToTop()
{
    emit webViewScrollToTop();
}


