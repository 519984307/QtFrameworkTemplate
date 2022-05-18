#pragma once
#include <qwidget.h>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>

class CTitleToolTip :
	public QWidget
{
public :
	CTitleToolTip(QWidget *parent = nullptr);
	~CTitleToolTip();

	void setToolTip(QString toolTip) { m_toolTip->setText(toolTip); }
	QString getToolTip() { return m_toolTip->text(); }

	void setPos(int x, int y);

protected:
	void paintEvent(QPaintEvent *event);

private:
	QLabel *m_toolTip;
};

