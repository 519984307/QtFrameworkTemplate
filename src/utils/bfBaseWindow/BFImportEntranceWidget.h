#pragma once
#include <QAbstractSlider>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>


class BFImportEntranceToolWidget : public QWidget {
  Q_OBJECT
 public:
  void SetRect(QRect);
  void Show(QRect);
  void SwitchStyleSheet();

 protected:
  virtual void hideEvent(QHideEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);
  virtual bool eventFilter(QObject*, QEvent*);
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void enterEvent(QEvent* event) override;
  virtual void leaveEvent(QEvent* event) override;
  virtual void paintEvent(QPaintEvent* event);
  virtual void showEvent(QShowEvent* event);
 public:
  BFImportEntranceToolWidget(QWidget* parent = Q_NULLPTR);
  ~BFImportEntranceToolWidget();
  BFImportEntranceToolWidget(BFImportEntranceToolWidget&) = delete;
  BFImportEntranceToolWidget& operator=(BFImportEntranceToolWidget&) = delete;


signals: 
  void SigHideImportBall();

 private:
  //void LoadStylePixmap();  //加载样式图
  const QPixmap& getBackPixmap();


 private:
   bool    m_is_hover;
   static QPixmap *m_back_svg_pix;
};





class BFImportEntranceWidget : public QPushButton
{
  Q_OBJECT
 public:
  BFImportEntranceWidget(QWidget* parent);
  ~BFImportEntranceWidget();

  void SetToolWid(BFImportEntranceToolWidget*);
  void SetAnimation();

 protected:
  void resizeEvent(QResizeEvent* event);
  void paintEvent(QPaintEvent* event);
  virtual void enterEvent(QEvent* event) override;
  virtual void leaveEvent(QEvent* event) override;
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void hideEvent(QHideEvent* event);


 private:
  //void LoadStylePixmap();  //加载样式图

  //开始动画 is_expand：true展开动画 false收缩动画
  void StartAnimation(bool is_expand);

  const QPixmap& getExpandPixmap();
  const QPixmap& getShrinkPixmap();

signals:
  void SigShowImportEnterToolWid();

public slots:
  void SlotCheckMouseLeave();

 private:
    QTimer*                     m_check_leave_time = NULL;
    BFImportEntranceToolWidget* m_tool_wid=NULL; //工具类的指针
    bool                        is_expand;            //是否是展开状态
    static QPixmap                     *m_pixmap_expand;   //展开图
    static QPixmap                     *m_pixmap_shrink;   //收缩图
    QPropertyAnimation*         m_animation_geo_start;  //形状渐变类
};
