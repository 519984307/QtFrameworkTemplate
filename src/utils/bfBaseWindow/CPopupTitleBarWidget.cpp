#include <QPainter>
#include <QStyleOption>

#include "CPopupTitleBarWidget.h"
#include "BFSkinManager.h"
#include "bfskinmodule/bfskinsetting.h"

#define POPUP_TITLE_HEIGHT 48

CPopupTitleBarWidget::CPopupTitleBarWidget
	(
	QWidget*move_wid,
	QWidget* parent/*=0*/,
	bool bClose/*=false*/,
	bool bTitle/*=false*/,
	bool bRepaint/*=false*/,
	bool bIcon,
	int  radius
	):
CTitleBarWidget
	(
	parent,
	bClose,
	bIcon/*false*/,
	bTitle
	), m_bRepaint(bRepaint),m_radius(radius), m_move_wid(NULL)
{
	setFixedHeight(POPUP_TITLE_HEIGHT);

	//QString style = QString("background-color:") + BFGetOtherBKColor().name(QColor::HexRgb) + QString(";");
	QString style = QString("background-color:rgba(100,100,100,255);border-top-left-radius:10px;border-top-right-radius:10px;");
	this->setStyleSheet(style);

	QHBoxLayout* pMainLayout = new QHBoxLayout;
	if (NULL != pMainLayout) {
		pMainLayout -> setContentsMargins(10, 0, 15, 3);

		// 增加icon
		if ( NULL != m_pLabelIco ) {
			pMainLayout -> addSpacing( 3 );
			pMainLayout -> addWidget( m_pLabelIco );
			pMainLayout -> addSpacing( 3 );
		}

		if (NULL != m_pLabelName) 
		{
			//m_pLabelName->setStyleSheet
			//(
			//	"QLabel { color: rgb(34, 34, 34); font-size: 14px; font-family: \"Microsoft YaHei\"; }"
			//);
			//QString style = QString("QLabel{color: rgb(34, 34, 34);background:") + BFGetOtherBKColor().name() + QString(";font-size: 14px; font-family: \"Microsoft YaHei\";}");
			//m_pLabelName->setStyleSheet(style);
			pMainLayout -> addWidget( m_pLabelName );
		}

		pMainLayout -> setSpacing(0);
		pMainLayout -> addStretch();
		if (NULL != m_pBtnClose) {
            m_pBtnClose -> setFixedSize( 12, 12 );
			m_pBtnClose -> setObjectName("popwindCloseBtn");
            m_pBtnClose->setFocusPolicy(Qt::NoFocus);
            QString btn_close_str = GetSkinResource("mainbody_close.svg");
			btn_close_str += "background-color:rgba(0,0,0,0);";
			m_pBtnClose->setStyleSheet(btn_close_str);
			//叉号布局，用于调整叉号的位置
			QHBoxLayout* closeLayout = new QHBoxLayout();
			closeLayout->setMargin(0);
			closeLayout->setSpacing(0);
            closeLayout->setContentsMargins(0, 16, 2, 0);
			closeLayout->addWidget(m_pBtnClose);
            pMainLayout->addLayout(closeLayout);
		}

		setLayout( pMainLayout );
	}

	m_move_wid = move_wid;
}

CPopupTitleBarWidget::~CPopupTitleBarWidget()
{
}

void CPopupTitleBarWidget::paintEvent(QPaintEvent *e)
{
	//if ( m_bRepaint ) 
	//{ 
	//	// FIX 1304
	//	QPainter painter(this);
	//	painter.fillRect(rect() - QMargins(0, 0, 0, 0), BFSkinManager::GetDialogTitleBar());
	//	painter.setPen(Qt::NoPen);
	//	//根据是否是浏览器指定文件夹的窗口绘制不同的标题栏。
	//	if (m_isDownloadFolder)
	//	{
	//		painter.setBrush(BFBackGroundColorGet());
	//		painter.drawRect(QRect(rect().x(), rect().y(), m_fWidth, rect().height()));
	//		painter.setBrush(BFSkinManager::GetDialogTitleBar());
	//		painter.drawRect(QRect(rect().x() + m_fWidth, rect().y(), rect().width() - m_fWidth, rect().height()));
	//	}
	//	else
	//	{
	//		painter.setBrush(BFSkinManager::GetDialogTitleBar());
	//		painter.drawRoundedRect(rect(), 10, 10); 
	//	}
	//}
	return CTitleBarWidget::paintEvent(e);
}

void CPopupTitleBarWidget::mouseMoveEvent(QMouseEvent*event)
{
	if (NULL != event && m_bPressed && Qt::LeftButton == event->buttons())
	{
		QRect thisRect = this->rect();
		QRect moveRect = thisRect.adjusted(5, 5, 5, 0);
		if (!moveRect.contains(event->pos()) && this->cursor().shape() != Qt::ArrowCursor)
		{
			return;
		}

		emit signalSetWidgetNormal();

		if (NULL != m_move_wid)
		{
			//获取移动窗口的全局坐标
			QPoint point = m_move_wid->pos();
			////父窗口原点+位移量 但是错误！
			//int tar_x = point.x() + evt->globalX() - m_point.x();
			//int tar_y = point.y() + evt->globalY() - m_point.y();
			//parent->move(tar_x,tar_y);
			//qDebug() << "offset:" << evt->globalX() - m_point.x() <<"---"<< evt->globalY() - m_point.y();
			//qDebug() << "origin" << m_point.x() << " " << m_point.y();
			//qDebug() << "now" << evt->globalX() << " " << evt->globalY();
			//parent->move(point + distance);
			QPoint distance = event->globalPos() - m_point;
			//改变窗口的位置
			m_move_wid->move(windowTopLeftPoint + distance);
		}
	}
	return QWidget::mouseMoveEvent(event);
}

void CPopupTitleBarWidget::mousePressEvent(QMouseEvent* evt)
{
	if (NULL != evt)
	{
		//全局坐标
		m_point = evt->globalPos();
		windowTopLeftPoint = m_move_wid->frameGeometry().topLeft();
	}
	m_bPressed = true;
}

void CPopupTitleBarWidget::drawTitleBar(QPainter *painter)
{
	// FIX 1304
	painter->setPen(Qt::NoPen);
	//根据是否是浏览器指定文件夹的窗口绘制不同的标题栏。
	if (m_isDownloadFolder)
	{
		painter->setBrush(BFBackGroundColorGet());
		painter->drawRect(QRect(rect().x(), rect().y(), m_fWidth, rect().height()));
		painter->setBrush(BFSkinManager::GetDialogTitleBar());
		painter->drawRoundedRect(QRect(rect().x() + m_fWidth, rect().y(), rect().width() - m_fWidth, rect().height()), getRadius(), getRadius());
		painter->drawRect(QRect(rect().x() + m_fWidth, rect().y() + rect().height() / 2, rect().width() - m_fWidth, rect().height() / 2));
	}
	else
	{
		painter->setBrush(BFSkinManager::GetDialogTitleBar());
		painter->drawRoundedRect(rect(), getRadius(), getRadius());
		painter->drawRect(QRect(rect().x(), rect().y() + rect().height() / 2, rect().width(), rect().height() / 2));
	}
}
