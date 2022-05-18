//2.0弹窗的基类

#ifndef CPOPUPDIALOG_H
#define CPOPUPDIALOG_H

#include <QDialog>
#include <QVBoxLayout>

class CPopupDialog : public QDialog
{
	Q_OBJECT

public:
	CPopupDialog
		(
			QWidget* parent = 0,   //父窗口
            bool bClose = true,    //是否增加关闭按钮
            bool bTitle = true,    //是否增加名称标题栏
            bool bRepaint = true,  //采用paint方式上色，目前无用
            bool bDelete = true,  //关闭即销毁，慎用，确保释放完全
            bool bIcon = true     //是否显示图标label
		);
	virtual ~CPopupDialog();

public:
	void SwitchStyleSheet();           //样式切换
	void Open();
    void ModalShow();

public:
	void SetTitleLabelFixedSize(int width, int height);                             //标题lab大小
	void SetTitleLabelStyleSheet(const QString& styleSheet);                //标题lab样式
	void SetTitleLabelText(const QString& text);                                    //标题lab文字
	void SetTitleLabelObjectName(const QString& objectName);         //标题lab对象名
	void SetTitleLabelVisible(bool bVisible);                                           //标题lab可见
	void setTitleFixedHeight(int height);                                                 //标题固定高
	void SetIconImagePath(const QString & strPath);                            //图标路径

	void SetCloseButtonFixedSize(int width, int height);                        //关闭按钮固定大小
	void SetCloseButtonlStyleSheet(const QString& styleSheet);          //关闭按钮样式
	void SetCloseButtonText(const QString& text);                               //关闭按钮文字
	void SetCloseButtonObjectName(const QString& objectName);    //关闭按钮对象名
	void SetCloseButtonVisible(bool bVisible);                                      //关闭按钮可见
	void SetDownloadFolder(bool value, int fWidth);                            //未知


protected:
	virtual void paintEvent(QPaintEvent* paint);
	virtual void closeEvent(QCloseEvent* event);
	virtual void hideEvent(QHideEvent* event);


protected slots:
	virtual void slotCloseBtnClicked(bool);

private:
	void DrawBorderShadow(QPainter& paint);      //画阴影，2.0无用
																			 
protected:															  
	QWidget*              m_pTitleBar;                          //标题栏wid
	QVBoxLayout*       m_pClientLayout;                  //业务逻辑扩充layout
	QWidget*              m_wid_main;                         //包装的iwd_main
};

#endif
