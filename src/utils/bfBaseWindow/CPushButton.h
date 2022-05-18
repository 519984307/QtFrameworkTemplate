#ifndef CPushButton_H
#define CPushButton_H

#include <QPushButton>

class CNewWidget;

class CPushButton : public QPushButton
{
	Q_OBJECT

public:
	CPushButton(QWidget* parent = 0);
	~CPushButton();

	void LoadTipText(QString strText);
	void closeTip() { m_bOpen = false; }
	void openTip() { m_bOpen = true; }

	void ShowGlobalTip(QPoint pt, int iLength, QString strTooltip, QWidget* p);
	void HideGlobalTip();

protected:
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
	void closeEvent(QCloseEvent* event);
	void moveEvent(QMoveEvent* event);

private:
	QString                m_strText;
	QWidget*            m_Parent;                  //父窗口
	bool                     m_bOpen;                 //标签是否已经打开
	CNewWidget*     m_globalTipWidgt;   //tip Widget
};



#endif
