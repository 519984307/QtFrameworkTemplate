#ifndef STYLEVIEWER_H
#define STYLEVIEWER_H

#include <QtGlobal>
#if QT_VERSION < 0x050000
#include <QWebView>
#else
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QWidget>
#endif
#include "chatwebpage.h"
#include "message.h"

class StyleViewer :
			public QWebView
{
    Q_OBJECT

public:
    StyleViewer(const QString &chatImagePath, QWidget *AParent);
	~StyleViewer();
public:
	virtual QSize sizeHint() const;

signals:
    void webViewScrollToTop();

    void enter();
    void leave();

protected slots:
	void onShortcutActivated();
	void slotInspectElement();
    void scrollToTop();
    void imageSaveAs();
    void onCopyActionTriggered();


protected:
	void contextMenuEvent(QContextMenuEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
private:
    int m_scrollDeltaY;
    QString m_chatImagePath;
    QString m_hittingImagePath;
};

#endif // STYLEVIEWER_H
