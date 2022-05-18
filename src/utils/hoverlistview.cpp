#include "hoverlistview.h"

HoverHelperDelegate::HoverHelperDelegate(QObject *parent /*= 0*/)
: QItemDelegate(parent), m_isInView(false)
{

}

void HoverHelperDelegate::setInView(bool inView)
{
	m_isInView = inView;
}

bool HoverHelperDelegate::isInView() const
{
	return m_isInView;
}

HoverListView::HoverListView(QWidget *parent)
	: QListView(parent)
{
	setMouseTracking(true);
	setAttribute(Qt::WA_Hover, true);
    setAttribute(Qt::WA_MacShowFocusRect, false);
}

HoverListView::~HoverListView()
{
}

void HoverListView::enterEvent(QEvent *event)
{
	// set is in view
	QAbstractItemDelegate *d = this->itemDelegate();
	if (d)
	{
		HoverHelperDelegate *hhd = qobject_cast<HoverHelperDelegate *>(d);
		if (hhd)
			hhd->setInView(true);
	}

	this->update();
	QListView::enterEvent(event);
}

void HoverListView::leaveEvent(QEvent *event)
{
	// set is not in view
	QAbstractItemDelegate *d = this->itemDelegate();
	if (d)
	{
		HoverHelperDelegate *hhd = qobject_cast<HoverHelperDelegate *>(d);
		if (hhd)
			hhd->setInView(false);
	}

	this->update();
	QListView::leaveEvent(event);
}
