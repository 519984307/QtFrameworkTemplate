#ifndef CPOPUPTITLEBARWIDGET_H
#define CPOPUPTITLEBARWIDGET_H

#include "CTitleBarWidget.h"
#include <QPainter>
class CPopupTitleBarWidget : public CTitleBarWidget
{
	Q_OBJECT

public:
	CPopupTitleBarWidget
	(
		QWidget*move_wid=0,
		QWidget* parent = 0,
		bool bClose = false,
		bool bTitle = false,
		bool bRepaint = false,
		bool bIcon = true,
		int  radius = 4
		);
	~CPopupTitleBarWidget();

	inline void SetDownloadFolderDialog(bool value,int fWidth) {
		m_isDownloadFolder = value;
		m_fWidth = fWidth;
	}

	//标题栏圆角 getter setter
	void setRadius(int radius) { m_radius = radius; }
	int getRadius() { return m_radius; }

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void mouseMoveEvent(QMouseEvent*event);
	virtual void mousePressEvent(QMouseEvent* evt);

private:
	void drawTitleBar(QPainter *painter);

private:
	bool m_bRepaint;
	bool m_isDownloadFolder = false;			//是否是浏览器指定文件夹。如果是，绘制标题栏时要特殊处理。
	int m_fWidth = 220;							//浏览器指定文件夹窗口的标题栏第一段颜色长度。
	int m_radius = 5;							//标题栏圆角
	QWidget* m_move_wid;
};
#endif // CPOPUPTITLEBARWIDGET_H
