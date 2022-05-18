#include "CornerBubble.h"
#include <QLayout>
#include <QApplication>
#include <QLabel>

CornerBubble::CornerBubble(const QString &content)
{
	m_content = content;
	m_bgColor = Qt::red;
	m_borderColor = Qt::white;
	m_contentColor = Qt::white;
	m_radius = 8;
	m_borderWidth = 2;
	m_fontSize = 10;
}


CornerBubble::~CornerBubble(void)
{
}

QPixmap CornerBubble::getCornerBubbleImage()
{
	QWidget widget;
	widget.setStyleSheet("background: transparent;");
	QLabel *label = new QLabel(m_content);
	label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet(QString(
		"background-color: %1;"
		"min-height: %2px;"
		"max-height: %3px;"
		"border-style: solid;"
		"border-width: %4px;"
		"border-color: %5;"
		"border-radius: %6px;"
		"margin: 0px;"
		"color: %7;"
		"min-width: %8px;"
		"font-size: %9px;")
		.arg(m_bgColor.name())
		.arg(2 * (m_radius - m_borderWidth))
		.arg(2 * (m_radius - m_borderWidth))
		.arg(m_borderWidth)
		.arg(m_borderColor.name())
		.arg(m_radius)
		.arg(m_contentColor.name())
		.arg(2 * (m_radius - m_borderWidth))
		.arg(m_fontSize)
        );
    QPixmap pixmap = label->grab();
	widget.setFixedSize(label->size());
	QLayout *layout = new QVBoxLayout(&widget);
	layout->setMargin(0);
	layout->addWidget(label);
    QPixmap widgetPix = widget.grab();
    delete label;
	return widgetPix;
}


