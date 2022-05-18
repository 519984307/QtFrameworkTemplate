#ifndef _CNEWWIDGET_H_
#define _CNEWWIDGET_H_

//包一层动画透明显示效果
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include <QWidget>


class CNewWidget : public QWidget
{
	Q_OBJECT

public:
	CNewWidget( QWidget* parent = 0 );
	~CNewWidget();

	void   Show();
	void   Hide();

	//读取文字并且设置适合文字的宽度
	int        LoadText(QString strText);
	void     InitAnimation();

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);

private:
	QString m_strText;
	QGraphicsOpacityEffect*  m_opacity_effect;               //渐变控制
	QPropertyAnimation*       m_animation;                     //渐变动画

private slots:
	void     AnimationFinished();
};
#endif
