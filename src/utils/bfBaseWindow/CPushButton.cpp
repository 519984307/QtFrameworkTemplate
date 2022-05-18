#include "CPushButton.h"
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include "CNewWidget.h"

#pragma execution_character_set("utf-8") 

CPushButton::CPushButton(QWidget* parent) :
	QPushButton(parent)
{
	setMouseTracking(true);
	//setAttribute(Qt::WA_TransparentForMouseEvents, true);
	m_Parent = parent;

	m_globalTipWidgt = NULL;
	openTip();
}

CPushButton::~CPushButton()
{
	if (nullptr != m_globalTipWidgt)
	{
		delete m_globalTipWidgt;
		m_globalTipWidgt = nullptr;
	}
}

void CPushButton::LoadTipText(QString strText)
{
	m_strText = strText;
}

void CPushButton::enterEvent(QEvent* event)
{
	if (!m_bOpen)
	{
		QPushButton::enterEvent(event);
		return;
	}


	ShowGlobalTip(QPoint(rect().bottomLeft()), rect().width(), m_strText, this);
	QPushButton::enterEvent(event);

}

void CPushButton::leaveEvent(QEvent* event)
{
	HideGlobalTip();
	QPushButton::leaveEvent(event);
}

void CPushButton::closeEvent(QCloseEvent* event)
{
	//[2020.11.16 TOM]裁剪按钮提示遗留问题
	HideGlobalTip();
	QPushButton::closeEvent(event);
}

void CPushButton::moveEvent(QMoveEvent* event)
{
	//[2020.11.16 TOM]裁剪按钮提示遗留问题
	HideGlobalTip();
	QPushButton::moveEvent(event);
}

void CPushButton::mouseMoveEvent(QMouseEvent* e)
{
	QPushButton::mouseMoveEvent(e);
}

void CPushButton::mousePressEvent(QMouseEvent* e)
{
	HideGlobalTip();
	QPushButton::mousePressEvent(e);
}

void CPushButton::mouseReleaseEvent(QMouseEvent* e)
{
	HideGlobalTip();
	QPushButton::mouseReleaseEvent(e);
}


void CPushButton::ShowGlobalTip(QPoint pt, int iLength, QString strTooltip, QWidget* p)
{

	if (m_globalTipWidgt == NULL)
	{
		m_globalTipWidgt = new CNewWidget(NULL);
	}



		//其他普通的一般的悬浮窗，用文字大小作为宽度,特殊的窗口也是通过这个来获取实际宽度，这里不需要区分
		int textLength = ((CNewWidget*)m_globalTipWidgt)->LoadText(strTooltip);
		if (textLength > iLength)
		{
			//提示wid大于按钮宽度
			pt.setX(pt.x() - (textLength - iLength) / 2);
		}
		else
		{
			//提示wid小于按钮宽度
			pt.setX(pt.x() + (iLength - textLength) / 2);
		}

	if (strTooltip.startsWith(QString::fromUtf8("打开素材网址"))|
        strTooltip.startsWith(QString::fromUtf8("打开素材文件夹"))) {
		//显示在控件上方
		pt.setY(pt.y() - rect().height() - m_globalTipWidgt->height());
    } else {
        //显示在控件下方，大约定在死在点的下方4px处
        pt.setY(pt.y() + 4);
    }
	QPoint _gPt = p->mapToGlobal(pt);
	m_globalTipWidgt->move(_gPt);
	m_globalTipWidgt->Show();

	QApplication::processEvents();
}

void CPushButton::HideGlobalTip()
{
	if (m_globalTipWidgt)
	{
		m_globalTipWidgt->Hide();
	}
}






















