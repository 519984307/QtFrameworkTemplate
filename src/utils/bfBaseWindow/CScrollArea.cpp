#include "CScrollArea.h"
#include <QWheelEvent>
#include <QScrollBar>

CScrollArea::CScrollArea(QWidget* parent) :
	QScrollArea(parent)
{
	QScrollBar * _v = verticalScrollBar();
	_v -> hide();
}

CScrollArea::~CScrollArea()
{

}

void CScrollArea::paintEvent(QPaintEvent *event)
{
	QScrollArea::paintEvent(event);
}

void CScrollArea::resizeEvent(QResizeEvent *event)
{
	QScrollBar * _v = verticalScrollBar();
	_v -> show();
	QScrollArea::resizeEvent(event);
}

void CScrollArea::mousePressEvent(QMouseEvent *e)
{
	//e -> accept();
	QScrollArea::mousePressEvent( e );
}

void CScrollArea::wheelEvent( QWheelEvent * event )
{
	event -> ignore();
}





















