/*
放置一些小的控件大全
*/

#pragma once
#include <QObject>
#include <QWidget>
#include<QLabel>
#include <QComboBox>
#include <QTimer>
#include<qlineedit.h>
#include<QStyledItemDelegate>
#include "utilsexport.h"
//自定义控件：圆角 combobox
class UTILS_EXPORT RoundComboBox : public QWidget {
  Q_OBJECT
public:
  RoundComboBox(QWidget* parent = nullptr);
  ~RoundComboBox();

  void setStyleValue(int nWidth, int nHeight, int nRadius, int nFontSize, const QColor& bkColor, const QColor& fontColor, int nMinWidth = 100);

  QComboBox* getComboBox();

signals:
  void signal_currentTextChanged(const QString& text);

protected:
  void paintEvent(QPaintEvent* event);

private:
  QComboBox* m_pComboBox = nullptr;
};



class BFComboBoxViewDelegate : public QStyledItemDelegate {
 public:
  BFComboBoxViewDelegate(QWidget* parent);
  ~BFComboBoxViewDelegate();

  //重写重画函数
  void paint(QPainter* painter, const QStyleOptionViewItem& option,
             const QModelIndex& index) const;
  QSize sizeHint(const QStyleOptionViewItem& option,
                 const QModelIndex& index) const;
};



//自定义combobox控件，下拉框向上弹出
class PopUpComboBox : public QComboBox
{
	Q_OBJECT
public:
	PopUpComboBox(QWidget* parent = nullptr);
	~PopUpComboBox();

	void setPopListViewWidth(int nWidth);

	void setComboBoxStyle(const QString& strComboxStyle, const QString &strListViewStyle, const QString &strScrollBarStyle);

protected:
	void showPopup() override;

	bool eventFilter(QObject* obj, QEvent* e) override;
};



//树模块用到的悬浮提示窗体
class CToolTip {
 public:
  CToolTip();
  ~CToolTip();

  void showGlobalTip(QPoint pt, int iLength, QString strTooltip,
                     QWidget* p = NULL);
  void hideGlobalTip();
 private:
  QLabel* m_ToolTip_up;
  QWidget* m_ParentWidget_up;

  QLabel* m_ToolTip_down;
  QWidget* m_ParentWidget_down;

  QWidget* m_globalTipWidgt;
  QFrame* m_globalTipFrame;

  QWidget* m_menuTipWidget;
  QFrame* m_menuTipFrame;
};


class BfLargerModeLoadingWidget : public QWidget {
  Q_OBJECT
 public:
  BfLargerModeLoadingWidget(qint32 borderLength, qint32 logoWidth,
                            qint32 logoHeight,
                  QWidget* parent = nullptr);
  ~BfLargerModeLoadingWidget();

 private slots:
  void updatePixmap();

 protected:
  void paintEvent(QPaintEvent* event);

 private:
  QMovie* m_movie = nullptr;
  QLabel* m_movieLabel = nullptr;
  QLabel* m_logoLabel = nullptr;
  QLabel* m_tipText = nullptr;
  qint32 m_pixRat = 0;
  QTimer* m_Timer = nullptr;
  QPixmap m_loadingBorder;
  qint32 m_borderLength = 76;
  qint32 m_logoWidth = 36;
  qint32 m_logoHeight = 43;
};


class BfLoadingWidget : public QWidget {
  Q_OBJECT
 public:
  BfLoadingWidget(qint32 borderLength,qint32 logoWidth,qint32 logoHeight,QWidget* parent = nullptr);
  ~BfLoadingWidget();


 private:
  //@brief:读取两个图片的
  void LoadSvg();

 private slots:
  void updatePixmap();

 protected:
  void paintEvent(QPaintEvent* event);

 private:
  QLabel* m_tipText = nullptr;
  qint32 m_pixRat = 0;
  QTimer* m_Timer = nullptr;
  QPixmap m_loadingBorder;
  qint32 m_borderLength = 76;
  qint32 m_logoWidth = 36;
  qint32 m_logoHeight = 43;

private:
  QPixmap* m_load_logo=nullptr;
  QPixmap* m_load_outline=nullptr;
};


//软件整体输入框
class BFLineEdit : public QLineEdit {
 public:
  BFLineEdit(QWidget* wid);


  //@brief:设置样式状态
  //@paramter:state:true:选中 false:常规
  virtual void SetUserStyleSheet(bool select);


 protected:
  void focusInEvent(QFocusEvent* e);
  void focusOutEvent(QFocusEvent* e);
};





class BFFilterComboBoxViewDelegate : public QStyledItemDelegate {
 public:
  BFFilterComboBoxViewDelegate(QWidget* parent);
  ~BFFilterComboBoxViewDelegate();

  //重写重画函数
  void paint(QPainter* painter, const QStyleOptionViewItem& option,
             const QModelIndex& index) const;
  QSize sizeHint(const QStyleOptionViewItem& option,
                 const QModelIndex& index) const;
};




class BFEclipseLinkWidget:public QWidget
{
  Q_OBJECT
public:
  BFEclipseLinkWidget(QColor color,QString link_str,int diameter,QString svg_name,QSize icon_size,QWidget* parent=NULL);
  ~BFEclipseLinkWidget();

protected:
   virtual void paintEvent(QPaintEvent*);
   virtual void mouseReleaseEvent(QMouseEvent* event);
   virtual void mousePressEvent(QMouseEvent* event);

private:
  void LoadIcon();

private:
  QColor m_color;
  QString m_link;
  //@brief:图标名称 xxx.svg
  QString m_icon_name;
  int m_diameter;
  QPixmap m_pixmap=QPixmap();
  QSize m_icon_size;
  bool click_state=false;
};
