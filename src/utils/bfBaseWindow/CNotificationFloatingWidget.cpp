#include "CNotificationFloatingWidget.h"
#include "bfskinmodule/bfskinsetting.h"
#include "bfqtutils.h"

#include <QHBoxLayout>

CNotificationFloatingWidget::CNotificationFloatingWidget(QWidget* parent) :QWidget(parent), m_showLabel(NULL), m_icon(NULL), m_timer(NULL), m_bIcon(true)
, m_posX(-1), m_posY(-1), m_destoryTime(0)
{
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setFixedSize(130, 28);
	
	initUi();
	SwitchStyleSheet();
}

CNotificationFloatingWidget::~CNotificationFloatingWidget()
{
}

void CNotificationFloatingWidget::initUi()
{
	m_textFont.setFamily("Microsoft YaHei");
	m_textFont.setPixelSize(12);
	//文字控件
	m_showLabel = new QLabel(this);
	m_showLabel->setFont(m_textFont);

	//图标控件
	m_icon = new QLabel(this);
	m_icon->setFixedSize(12, 12);

	//销毁定时器
	m_timer = new QTimer(this);
	m_timer->setInterval(200);
	connect(m_timer, &QTimer::timeout, [=]()
	{
		this->close();
	});

	//layout布局
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->setAlignment(Qt::AlignCenter);
	hLayout->setMargin(0);
	hLayout->setSpacing(0);
	hLayout->setContentsMargins(0, 0, 0, 0);
	hLayout->addWidget(m_icon);
	hLayout->setSpacing(NOTIFICATION_ICON_TEXT_SPACING);
	hLayout->addWidget(m_showLabel);
}

void CNotificationFloatingWidget::setContents(QString iconName, QString text)
{
	//设置图标
	//m_icon->setStyleSheet("background:red");
	QString indexIconStyle =
		"QLabel{border:0px;" + BFSkinSetting::GetInstance()->GetResourcePath(iconName) + "}";
	m_icon->setStyleSheet(indexIconStyle);
	//设置文字
    int textWidth = BfQtUtils::WidthWithFixString(m_textFont, text);
	m_showLabel->setText(text);
	m_showLabel->setFixedWidth(textWidth);

	adjustWidth();
}

void CNotificationFloatingWidget::SwitchStyleSheet()
{
	//背景颜色和圆角
	this->setObjectName("floatingWidget");
	QString widget_style = "#floatingWidget{border-radius:6px;background:" + BFSkinSetting::GetInstance()->GetNotificationBackColor1().name(QColor::HexArgb) + ";}";
	this->setStyleSheet(widget_style);

	//文字内容颜色
	QString text_style = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
	m_showLabel->setStyleSheet(text_style);
}

void CNotificationFloatingWidget::adjustWidth()
{
	//重置控件宽度。控件宽度 = 左侧padding+图标宽度+文字宽度+右侧padding
    int textWidth = BfQtUtils::WidthWithFixString(m_textFont, m_showLabel->text());
	int widgetWidth = NOTIFICATION_H_PADDING + textWidth + NOTIFICATION_H_PADDING;
	widgetWidth += m_bIcon ? (m_icon->width()) : 0;
	this->setFixedSize(widgetWidth, NOTIFICATION_HEIGHT);
}

void CNotificationFloatingWidget::setFloatingPosY(int y)
{
	m_posY = y;
}

void CNotificationFloatingWidget::setFloatingBackColor(QColor color)
{
	//背景颜色和圆角
	this->setObjectName("floatingWidget");
	QString widget_style = "#floatingWidget{border-radius:6px;background:" + color.name(QColor::HexArgb) + ";}";
	this->setStyleSheet(widget_style);
}

void CNotificationFloatingWidget::setTextFont(QFont font)
{
	m_textFont = font;
	m_showLabel->setFont(font);

	adjustWidth();
}

void CNotificationFloatingWidget::setIconVisible(bool visible)
{
	m_bIcon = visible;
	m_icon->setVisible(visible);

	adjustWidth();
}

void CNotificationFloatingWidget::setDestoryTime(int time)
{
	m_destoryTime = time;
}

void CNotificationFloatingWidget::showEvent(QShowEvent* event)
{
	//显示时计算显示位置
	if (m_posX == -1 && m_posY == -1)
	{
		int posX = (((QWidget*)this->parent())->width() - this->width()) / 2;
		this->move(posX, 80);
	}
	else
	{
		int posX = (((QWidget*)this->parent())->width() - this->width()) / 2;
		this->move(posX, m_posY);
	}

	//如果延迟销毁时间大于0，启动延迟销毁
	if (m_destoryTime != 0 && m_destoryTime > 0)
	{
		m_timer->start(m_destoryTime);
	}
	else
	{
		m_timer->start(3000);
	}
}
