#include "CLineEdited.h"
#include <QEvent>

CLineEdited::CLineEdited(QWidget *parent)
	:QLineEdit(parent)
{
	installEventFilter( this );
	this->setContextMenuPolicy(Qt::NoContextMenu);
	//setMaxLength(20);
#ifdef __APPLE__
	setAttribute(Qt::WA_MacShowFocusRect,0);
#endif
}

CLineEdited::~CLineEdited()
{

}

void CLineEdited::focusInEvent(QFocusEvent* event)
{
	QLineEdit::focusInEvent( event );
	emit signFocusIn();
}

bool CLineEdited::eventFilter( QObject* obj, QEvent* event )
{
	if (event->type() == QEvent::FocusIn)
	{

	}
	return QLineEdit::eventFilter(obj, event);
}

void CLineEdited::paintEvent(QPaintEvent * e)
{
	QLineEdit::paintEvent(e);
}


