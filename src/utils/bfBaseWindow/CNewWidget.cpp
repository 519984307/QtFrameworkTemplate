#include "CNewWidget.h"
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "BFSkinManager.h"
#include<QDebug>
#include "bfskinmodule/bfskinsetting.h"

#define  ToolAnimationTime 300

#pragma execution_character_set("utf-8") 

CNewWidget::CNewWidget(QWidget* parent):
	QWidget(parent)
{
	setAttribute(Qt::WA_TransparentForMouseEvents, true);
#ifdef _WIN32
        this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint |
                             Qt::WindowStaysOnTopHint);
#endif
#ifdef __APPLE__
	setWindowFlags(Qt::ToolTip);
#endif

	setAttribute(Qt::WA_TranslucentBackground, true);
	this->InitAnimation();
}

CNewWidget::~CNewWidget()
{
	if (m_opacity_effect)
	{
		delete m_opacity_effect;
		m_opacity_effect = NULL;
	}

	if (m_animation)
	{
		delete m_animation;
		m_animation = NULL;
	}
}


void CNewWidget::Show()
{
	if (QAbstractAnimation::Stopped == m_animation->state())
	{
		this->show();
		m_animation->start();
	}
}

void CNewWidget::Hide()
{
	//启动中则取消动画
	if (QAbstractAnimation::Running == m_animation->state())
	{
		m_animation->stop();
	}
	//qDebug() << "=================CNewWidget  m_animation  Hide";
	//自身必须隐藏
	this->hide();
}

int CNewWidget::LoadText(QString strText)
{
	m_strText = strText;


	if (QString::fromUtf8("显示设置") == m_strText)
	{
		//显示设置为蓝湖固定大小 (142,38)
		//setGeometry(0, 0,142,38);
        setFixedSize(142, 38);
		return 142;
	}
	else
	{
		//其他一般的悬浮窗口用文字宽度和高度定大小
		QFont font_12;
		font_12.setFamily("Microsoft YaHei");
		font_12.setPixelSize(12);
		font_12.setStyleStrategy(QFont::ForceOutline);
		QFontMetrics metric(font_12);
		QSize size = metric.size(Qt::TextSingleLine, strText);
		//setGeometry(0, 0, size.width() + 8, size.height() + 6);
        setFixedSize(size.width() + 8, size.height() + 6);
		return size.width() + 8;
	}
}

void CNewWidget::InitAnimation()
{
	m_opacity_effect = new QGraphicsOpacityEffect(this);
	m_opacity_effect->setOpacity(1);
	this->setGraphicsEffect(m_opacity_effect);

	m_animation = new QPropertyAnimation(m_opacity_effect, "opacity", this);
	m_animation->setDuration(ToolAnimationTime);
	m_animation->setStartValue(0.1);
	m_animation->setEndValue(1.0);
	connect(m_animation, SIGNAL(finished()), this, SLOT(AnimationFinished()));
}

void CNewWidget::mousePressEvent(QMouseEvent *event)
{
	event -> ignore();
	QWidget::mousePressEvent(event);
}

void CNewWidget::paintEvent( QPaintEvent *event )
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	QFont font;
	font.setFamily(QString::fromUtf8("Microsoft Yahei"));
	font.setPixelSize(10);
	font.setStyleStrategy(QFont::ForceOutline);

    //画背景圆角矩形
    painter.setBrush(BFSkinSetting::GetInstance()->GetToolTipBackgroundColor());
    painter.setPen(BFSkinSetting::GetInstance()->GetToolTipBorderColor());
	painter.drawRoundedRect(rect(), 6, 4);



	if (QString::fromUtf8("显示设置") == m_strText)
	{
		painter.setFont(font);

		//第一行
		QRect first_rect = QRect(51, 6, 40, 11);
        //颜色
        painter.setPen(BFSkinSetting::GetInstance()->GetTextColor(0));
		painter.drawText(first_rect, Qt::AlignCenter, QString::fromUtf8("显示设置"));

		//第二行
        QRect second_rect = QRect(6, 22, 130, 11);
        painter.setPen(BFSkinSetting::GetInstance()->GetTextColor(1));
        painter.drawText(second_rect, Qt::AlignCenter,
                         QString::fromUtf8("信息、隐藏设置"));
        }
	else
	{
		//普通项
		//画字体
        painter.setFont(font);
        painter.setPen(BFSkinSetting::GetInstance()->GetTextColor(0));
		painter.drawText(rect(), Qt::AlignCenter, m_strText);
	}
}



void CNewWidget::AnimationFinished()
{

}
