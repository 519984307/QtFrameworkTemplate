#pragma once
#include <QWidget>
#include <QScrollBar>
/*
2.0项目所有出现继承自QAbstractScrollArea的项目都可以应用该滚动条
悬浮滚动条-例子说明
鼠标移动到控件上时显示滚动条，鼠标离开控件则隐藏滚动条
目前只实现垂直滚动条，代码简单
需要水平滚动条的看懂该类后可自行添加
继承QScrollBar作为组件，添加到你需要添加的控件当中
*/

#include <QListWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>

#define BFScrollBarWidthFront 5
#define BFScrollBarWidthBehind 8

class BFScrollBar : public QScrollBar
{
	Q_OBJECT
public:
	explicit BFScrollBar(Qt::Orientation t, QWidget* parent = 0);
	~BFScrollBar();


	//新增接口，之前的外部设置BFScroll较为繁琐，索性传入需要的指针内部设置
    void SetScrollArea(QAbstractScrollArea* area,int h_margin = 0,int v_margin = 0);
	void AnimationShow();   //动画显示
	void AnimationHide();   //动画隐藏

private:
	void SwitchStyleSheet();  //样式表
	void InitAnimation();     //设置动画
	void AnimationEnter();    //动画鼠标进入
	void AnimationLeave();    //动画鼠标移除


public slots:
	void slot_valueChange_scrollBar(int);
	void slot_rangeChanged(int min, int max);

protected:
	//鼠标进入事件
	void enterEvent(QEvent* event);
	//鼠标移出事件
	void leaveEvent(QEvent* event);
	//显示事件
	void showEvent(QShowEvent* event);
	//过滤监控的area一些事件
    virtual bool eventFilter(QObject* object, QEvent* event) override;

	//隐藏
	virtual void hideEvent(QHideEvent* event);


private:
    QAbstractScrollArea* m_watched_area;  //待监控的area


private:
	//开始动画(当鼠标进入BFSCroll的时候，触发)
	QPropertyAnimation* m_animation_geo_start;      //形状渐变类
	QGraphicsOpacityEffect* m_wid_opacity;          //渐变控制
	QPropertyAnimation* m_animation_color_start;    //颜色渐变类
	QParallelAnimationGroup* animation_group_start; //组动画

	//结束动画(当鼠标离开BFSCroll的时候，触发)
	QPropertyAnimation* m_animation_geo_end;        //形状渐变类
	QPropertyAnimation* m_animation_color_end;      //颜色渐变类
	QParallelAnimationGroup* animation_group_end;   //组动画

	//显示动画(当进入Area的区域的时候显示BFScroll)
	QPropertyAnimation* m_animation_color_show;     //颜色渐变类

	//结束动画(当离开Area的区域的时候隐藏BFScroll)
	QPropertyAnimation* m_animation_color_hide;     //颜色渐变类

	//水平margin，垂直margin
    int m_h_margin = 0;
    int m_v_margin = 0;
};

