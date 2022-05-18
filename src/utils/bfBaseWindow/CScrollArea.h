#ifndef CScrollArea_H
#define CScrollArea_H
#include <QScrollArea>


class CScrollArea : public QScrollArea
{
	Q_OBJECT

public:
	CScrollArea( QWidget* parent = 0 );
	~CScrollArea();

protected:
	void wheelEvent(QWheelEvent *);
	void mousePressEvent(QMouseEvent *);
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
};



#endif