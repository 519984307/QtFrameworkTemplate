#pragma once
#include <qwidget.h>

#include <QLabel>
#include <QIcon>
#include <QTimer>

#define NOTIFICATION_HEIGHT 28				//控件高度
#define NOTIFICATION_H_PADDING 20			//控件两侧水平padding
#define NOTIFICATION_ICON_TEXT_SPACING 6	//图标和文字的spacing

//通知悬浮窗。可设置有无图标，几秒之后销毁
class CNotificationFloatingWidget :
    public QWidget
{
public:
	CNotificationFloatingWidget(QWidget* parent);
	~CNotificationFloatingWidget();

public:
	void initUi();										//初始化界面				
	void setContents(QString iconName, QString text);	//设置图标和文字
	void SwitchStyleSheet();							//设置样式表
	void adjustWidth();								    //根据是否有图标和文字长度调整控件长度
	void setFloatingPosY(int y);						//设置显示位置
	void setFloatingBackColor(QColor color);			//设置通知悬浮窗背景颜色


	void setTextFont(QFont font);						//设置字体格式
	void setIconVisible(bool visible);					//设置图标是否可见
	void setDestoryTime(int time = 0);			   //设置销毁时间 time为0时不定时销毁

protected:
	void showEvent(QShowEvent* event);

private:
	QLabel *m_showLabel;	//文字内容
	QLabel *m_icon;		    	//图标内容
	QTimer *m_timer;		    //销毁定时器
	QFont  m_textFont;		    //文字字体格式

	int m_posX;				//位置X	x坐标未用到，不需要计算，基本都是显示在控件中间的位置
	int m_posY;				//位置Y
	int m_destoryTime;		//延迟销毁时间

	bool m_bIcon;			//标志位：是否显示图标
};

