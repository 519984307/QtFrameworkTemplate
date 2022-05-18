#include "CTitleBarWidget.h"
#include <qevent.h>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include "CPushButton.h"
#include "BFSkinManager.h"

# pragma execution_character_set("utf-8")  

CTitleBarWidget::CTitleBarWidget
	(
	QWidget* parent/*=0*/,
	bool bClose/*=false*/,
	bool bIco/*=false*/,
	bool bName/*=false*/,
	bool bMin/*=false*/,
	bool bMax/*=false*/
	):
	QWidget(parent), m_pLabelIco(NULL), m_pLabelName(NULL), m_pBtnMin(NULL),
	m_pBtnMax(NULL), m_pBtnClose(NULL), m_bPressed(false)
{
	if (bIco) {
		m_pLabelIco = new QLabel(this);
	}

	if (bName) {
		m_pLabelName = new QLabel(this);

        //标题lab字体设置 
        QFont font = m_pLabelName->font();
        font.setFamily(QString::fromUtf8("Microsoft Yahei"));
        font.setPixelSize(14);
        m_pLabelName->setFont(font);
        QString label_style = "background-color:" + BFSkinManager::GetDialogTitleBar().name(QColor::HexArgb) + ";color:" + BFSkinManager::GetTextColor(0).name(QColor::HexRgb) + ";";
        m_pLabelName->setStyleSheet(label_style);
	}

	if (bMin) {
		m_pBtnMin = new CPushButton(this);
		if (NULL != m_pBtnMin) {
			connect(m_pBtnMin, SIGNAL(clicked(bool)), this, SLOT(slotMinBtnClicked(bool)));
		}
	}

	if (bMax) {
		m_pBtnMax = new QPushButton(this);
		if (NULL != m_pBtnMax) {
			connect(m_pBtnMax, SIGNAL(clicked(bool)), this, SLOT(slotMaxBtnClicked(bool)));
		}
	}

	if (bClose) 
	{
		m_pBtnClose = new QPushButton(this);
		if (NULL != m_pBtnClose) {
			connect(m_pBtnClose, SIGNAL(clicked(bool)), this, SLOT(slotCloseBtnClicked(bool)));
		}

	//标题栏关闭按钮
	//QString close_style = "background-color:" + BFSkinManager::GetDialogTitleBar().name(QColor::HexArgb)+";";

	QString close_style = "background-color:rgba(0,0,0,0);";
	m_pBtnClose->setStyleSheet(close_style);

	m_pBtnClose->installEventFilter(this);
	}

	//CResourceManagerWidget* p = CAppSingleton::getInstance()->GetMainWnd();
	//CBillfishManagerWidget* parentWidget = p->GetBillfishManagerWidget();
	this->setMouseTracking(true);

}

CTitleBarWidget::~CTitleBarWidget()
{


}

void CTitleBarWidget::mousePressEvent(QMouseEvent* evt)
{
	if (NULL != evt) 
	{
		//全局坐标
		m_point = evt->globalPos();

		windowTopLeftPoint = this->parentWidget()-> frameGeometry().topLeft();
	}
	m_bPressed = true;
}

void CTitleBarWidget::mouseMoveEvent(QMouseEvent* evt)
{
	if (NULL != evt && m_bPressed && Qt::LeftButton == evt->buttons()) 
	{
		QRect thisRect = this->rect();
		QRect moveRect = thisRect.adjusted(5, 5, 5, 0);
		if (!moveRect.contains(evt->pos()) && this->cursor().shape() != Qt::ArrowCursor)
		{
			return;
		}

		emit signalSetWidgetNormal();
		QWidget* parent = parentWidget();
		if (NULL != parent) 
		{
			//获取父窗口全局坐标
			QPoint point = parent->pos();

			////父窗口原点+位移量 但是错误！
			//int tar_x = point.x() + evt->globalX() - m_point.x();
			//int tar_y = point.y() + evt->globalY() - m_point.y();
			//parent->move(tar_x,tar_y);
			//qDebug() << "offset:" << evt->globalX() - m_point.x() <<"---"<< evt->globalY() - m_point.y();
			//qDebug() << "origin" << m_point.x() << " " << m_point.y();
			//qDebug() << "now" << evt->globalX() << " " << evt->globalY();
			//parent->move(point + distance);
		
			QPoint distance = evt->globalPos() - m_point;
			//改变窗口的位置
			parent->move(windowTopLeftPoint + distance);
		}
	}
	return QWidget::mouseMoveEvent(evt);
}

void CTitleBarWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit signalMaxBtnClicked(true);
}

bool CTitleBarWidget::eventFilter(QObject *watched, QEvent *event)
{
	return QWidget::eventFilter(watched, event);
}

void CTitleBarWidget::mouseReleaseEvent(QMouseEvent* evt)
{
	m_bPressed = false;
}

void CTitleBarWidget::slotMinBtnClicked(bool bClicked)
{
	emit signalMinBtnClicked(bClicked);
}

void CTitleBarWidget::slotMaxBtnClicked(bool bClicked)
{
	emit signalMaxBtnClicked(bClicked);
}

void CTitleBarWidget::slotCloseBtnClicked(bool bClicked)
{	emit signalCloseBtnClicked(bClicked);
}
