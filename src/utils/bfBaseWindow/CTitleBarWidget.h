#ifndef CTITLEBARWIDGET_H
#define CTITLEBARWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QEvent>
#include <QPixmap>
#include <QHBoxLayout>
#include "CTitleToolTip.h"

# pragma execution_character_set("utf-8") 

class CTitleBarWidget : public QWidget
{
	Q_OBJECT

public:
	CTitleBarWidget
		(
		QWidget* parent=0,
		bool bClose=false,
		bool bIco=false,
		bool bName=false,
		bool bMin=false,
		bool bMax=false
		);
	virtual ~CTitleBarWidget();

signals:
	void signalMinBtnClicked(bool);
	void signalMaxBtnClicked(bool);
	void signalCloseBtnClicked(bool);
	void signalSetWidgetNormal();

public:
	inline void SetIcoLabelFixedSize(int width, int height) {
		if (NULL != m_pLabelIco) {
			m_pLabelIco->setFixedSize(width, height);
		}
	}
	inline void SetIcoLabelStyleSheet(const QString& styleSheet) {
		if (NULL != m_pLabelIco) {
			m_pLabelIco->setStyleSheet(styleSheet);
		}
	}
	inline void SetIcoLabelImagePath(const QString& imagePath) {
		if (NULL != m_pLabelIco) {
			if (!imagePath.isEmpty()) {
				m_pLabelIco->setPixmap(QPixmap(imagePath));
			}
		}
	}
	inline void SetIcoLabelObjectName(const QString& objectName) {
		if (NULL != m_pLabelIco) {
			m_pLabelIco->setObjectName(objectName);
		}
	}
	inline void SetIcoLabelVisible(bool bVisible) 
	{
		if (NULL != m_pLabelIco) {
			m_pLabelIco->setVisible(bVisible);
		}
	}
	inline QLabel* GetIcoLabel() {
		return m_pLabelIco;
	}

	inline void SetTitleLabelFixedSize(int width, int height) {
		if (NULL != m_pLabelName) {
			m_pLabelName->setFixedSize(width, height);
		}
	}
	inline void SetTitleLabelStyleSheet(const QString& styleSheet) {
		if (NULL != m_pLabelName) {
			m_pLabelName->setStyleSheet(styleSheet);
		}
	}
	inline void SetTitleLabelText(const QString& text) {
		if (nullptr != m_pLabelIco)
		{
			m_pLabelIco->setVisible(false);
		}
		if (NULL != m_pLabelName) {
			m_pLabelName->setText(text);
		}
	}
	inline void SetTitleLabelObjectName(const QString& objectName) {
		if (NULL != m_pLabelName) {
			m_pLabelName->setObjectName(objectName);
		}
	}
	inline void SetTitleLabelVisible(bool bVisible) {
		if (NULL != m_pLabelName) {
			m_pLabelName->setVisible(bVisible);
		}
	}
	inline QLabel* GetTitleLabel() {
		return m_pLabelName;
	}

	inline void SetMinButtonFixedSize(int width, int height) {
		if (NULL != m_pBtnMin) {
			m_pBtnMin->setFixedSize(width, height);
		}
	}
	inline void SetMinButtonlStyleSheet(const QString& styleSheet) {
		if (NULL != m_pBtnMin) {
			m_pBtnMin->setStyleSheet(styleSheet);
		}
	}
	inline void SetMinButtonText(const QString& text) {
		if (NULL != m_pBtnMin) {
			m_pBtnMin->setText(text);
		}
	}
	inline void SetMinButtonObjectName(const QString& objectName) {
		if (NULL != m_pBtnMin) {
			m_pBtnMin->setObjectName(objectName);
		}
	}
	inline void SetMinButtonVisible(bool bVisible) {
		if (NULL != m_pBtnMin) {
			m_pBtnMin->setVisible(bVisible);
		}
	}
	inline QPushButton* GetMinButton() {
		return m_pBtnMin;
	}

	inline void SetMaxButtonFixedSize(int width, int height) {
		if (NULL != m_pBtnMax) {
			m_pBtnMax->setFixedSize(width, height);
		}
	}
	inline void SetMaxButtonlStyleSheet(const QString& styleSheet) {
		if (NULL != m_pBtnMax) {
			m_pBtnMax->setStyleSheet(styleSheet);
		}
	}
	inline void SetMaxButtonText(const QString& text) {
		if (NULL != m_pBtnMax) {
			m_pBtnMax->setText(text);
		}
	}
	inline void SetMaxButtonObjectName(const QString& objectName) {
		if (NULL != m_pBtnMax) {
			m_pBtnMax->setObjectName(objectName);
		}
	}
	inline void SetMaxButtonVisible(bool bVisible) {
		if (NULL != m_pBtnMax) {
			m_pBtnMax->setVisible(bVisible);
		}
	}
	inline QPushButton* GetMaxButton() {
		return m_pBtnMax;
	}

	inline void SetCloseButtonFixedSize(int width, int height) {
		if (NULL != m_pBtnClose) {
			m_pBtnClose->setFixedSize(width, height);
		}
	}
	inline void SetCloseButtonlStyleSheet(const QString& styleSheet) {
		if (NULL != m_pBtnClose) {
			m_pBtnClose->setStyleSheet(styleSheet);
		}
	}
	inline void SetCloseButtonText(const QString& text) {
		if (NULL != m_pBtnClose) {
			m_pBtnClose->setText(text);
		}
	}
	inline void SetCloseButtonObjectName(const QString& objectName) {
		if (NULL != m_pBtnClose) {
			m_pBtnClose->setObjectName(objectName);
		}
	}
	inline void SetCloseButtonVisible(bool bVisible) {
		if (NULL != m_pBtnClose) {
			m_pBtnClose->setVisible(bVisible);
		}
	}
	inline QPushButton* GetCloseButton() {
		return m_pBtnClose;
	}


protected:
	virtual void mousePressEvent(QMouseEvent* evt);
	virtual void mouseMoveEvent(QMouseEvent* evt);
	virtual void mouseReleaseEvent(QMouseEvent* evt);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual bool eventFilter(QObject *watched, QEvent *event);

private slots:
	void slotMinBtnClicked(bool);
	void slotMaxBtnClicked(bool);
	void slotCloseBtnClicked(bool);

protected:
	QPoint m_point;
	QPoint windowTopLeftPoint;
	bool m_bPressed;

protected:
	QLabel* m_pSplitter;
	QLabel* m_pLabelIco;
	QLabel* m_pLabelName;
	QPushButton* m_pBtnMin;
	QPushButton* m_pBtnMax;
	QPushButton* m_pBtnClose;
};

#endif // CTITLEBARWIDGET_H
