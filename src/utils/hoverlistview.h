#ifndef HOVERLISTVIEW_H
#define HOVERLISTVIEW_H

#include "utilsexport.h"
#include <QListView>
#include <QItemDelegate>

class UTILS_EXPORT HoverHelperDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	HoverHelperDelegate(QObject *parent = 0);
	void setInView(bool inView);
	bool isInView() const;

private:
	bool m_isInView;
};

class UTILS_EXPORT HoverListView : public QListView
{
	Q_OBJECT

public:
	HoverListView(QWidget *parent = 0);
	~HoverListView();

protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
};

#endif // HOVERLISTVIEW_H
