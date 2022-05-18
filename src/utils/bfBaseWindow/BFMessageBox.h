//***************封装下通用提示窗   [2020.10.21 Tom]*********************

//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓用法↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
/*
auto msg_box =  BFMessageBox::CreateMessageBox(this->window());
msg_box->SetProperty(BFMessageBox::CancelAndConfirm_Mode,
QString::fromUtf8("我是标题"), QString::fromUtf8("我我是内容"),this->window());

connect(msg_box,&BFMessageBox::signalResult,this,[this](BFMessageBox::ReturnValue
value){ if(value == BFMessageBox::Confirm){

      }
});


msg_box->ModalShow();



*/
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

#pragma once
#include <QDialog>

class QCloseEvent;

namespace Ui {
class BFMessageBox;
};

class BFMessageBox : public QDialog {
  Q_OBJECT
 public:
  //获取实例
  //  static BFMessageBox* GetInstance(QWidget* parent);
  static BFMessageBox* CreateMessageBox(QWidget* parent);
  //自定义返回值 不用QDialog内置的accept和reject
  enum ReturnValue {
    OK,       //返回好的 0
    Confirm,  //返回确定 1
    Cancel,   //返回取消  2
    None,     //初始化为None 3
  };

  void ModalShow();

  //模式 只有OK 或者只有取消和确认
  enum Mode {
    OK_Mode,                // OK模式(只有OK按钮)
    CancelAndConfirm_Mode,  //确认和取消模式(有确认和取消)
    ALL_Mode,  //三个按钮 都有(目前只有 素材库丢失用到)
    CancelAndConfirm_Mode_And_Close_With_Out_Cacnel,  //确认和取消模式(有确认和取消
                                                      //右上角关闭不是默认取消
                                                      //目前素材库索引丢失)
  };

  //模式和内容索性连一起了
  void SetButtonText(QString confirm, QString cancel, QString ok);
  void SetProperty(Mode mode, QString title, QString text, QWidget* widget);
  // ReturnValue GetReturnValue() { return return_value; };

  void SwitchStyleSheet();
  void InitUi();
  void HideCloseButton();

 public:
  ~BFMessageBox();
  BFMessageBox(BFMessageBox&) = delete;
  BFMessageBox& operator=(BFMessageBox&) = delete;

  void setCloseBtnVisible(bool visible);  //设置关闭按钮是否可见

 signals:
  void signExecInThread(Mode mode, QString title, QString text,
                        QWidget* widget);

  void signalResult(ReturnValue value);

 private:
  BFMessageBox(QWidget* parent = Q_NULLPTR);

  static BFMessageBox* messbox;
  Ui::BFMessageBox* ui;
  ReturnValue return_value;  //返回值
  Mode cur_mode;
  bool m_bMask = false;  //遮罩层是否显示

 protected:
  virtual void paintEvent(QPaintEvent* event);
  virtual void closeEvent(QCloseEvent* event);
  virtual void hideEvent(QHideEvent* event);

 private:
  void DrawBorderShadow(QPainter& paint);

 private slots:
  void on_confirm_btn_clicked();
  void on_ok_btn_clicked();
  void on_cancel_btn_clicked();
  void on_btn_close_clicked();
  void slotExecInThread(Mode mode, QString title, QString text,
                        QWidget* widget);
};
