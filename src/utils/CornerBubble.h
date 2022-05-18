#ifndef CORNERBUBBLE_H
#define CORNERBUBBLE_H

#include <QPixmap>
#include "utilsexport.h"

class UTILS_EXPORT CornerBubble
{
public:
	CornerBubble(const QString &content);
	~CornerBubble(void);
	void setBgColor(const QColor &color) {m_bgColor = color;}
	void setContentColor(const QColor &color) {m_contentColor = color;}
	void setBorderColor(const QColor &color) {m_borderColor = color;}
	void setBorderWidth(int width) {m_borderWidth = width;}
	void setRadius(int radius) {m_radius = radius;}
	void setFontSize(int size) {m_fontSize = size;}

	int borderWidth() const {return m_borderWidth;}
	int radius() const {return m_radius;}
	int fontSize() const {return m_fontSize;}
	QColor bgColor() const {return m_bgColor;}
	QColor contentColor() const {return m_contentColor;}
	QColor borderColor() const {return m_borderColor;}
	QString content() const {return m_content;}

	QPixmap getCornerBubbleImage();
	

private:
	QColor m_bgColor;
	QColor m_contentColor;
	QColor m_borderColor;
	int m_borderWidth;
	int m_radius;
	int m_fontSize;
	QString m_content;
};

#endif

