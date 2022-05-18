#include "BFMessageBox.h"
#include "BFSkinManager.h"
#include "bfskinmodule/bfskinsetting.h"
#include "ui_BFMessageBox.h"
#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QFont>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
#include <QThread>

#define SHADOW_WIDTH 10

//静态成员初始化
BFMessageBox* BFMessageBox::messbox = NULL;

#pragma execution_character_set("utf-8")

void BFMessageBox::setCloseBtnVisible(bool visible) {
  ui->btn_close->setVisible(visible);
}

BFMessageBox::BFMessageBox(QWidget* parent) : QDialog(parent) {
  ui = new Ui::BFMessageBox;
  ui->setupUi(this);

  //去掉边框
  this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
  this->resize(400, 200);
  // Ui初始化
  this->InitUi();
  //透明
  this->setAttribute(Qt::WA_TranslucentBackground);
  //图标
  // this->setWindowIcon(QIcon(BFSkinGet("logo_18.svg")));
  //名称
  this->setWindowTitle("BillFish");

  return_value = None;
  messbox = NULL;
  cur_mode = OK_Mode;
}

void BFMessageBox::SwitchStyleSheet() {
  //主体
  QString win_style_str;
  win_style_str += "#main_wid{background-color:";
  win_style_str +=
      BFSkinSetting::GetInstance()->GetPopupWinBackgroundColor().name(
          QColor::HexArgb);
  win_style_str += ";border-radius:10px;border:1px solid; border-color:";
  win_style_str += BFSkinSetting::GetInstance()->GetPopupWinBorderColor().name(
      QColor::HexArgb);
  win_style_str += ";}";
  ui->main_wid->setStyleSheet(win_style_str);

  //标题
  QString lab_title_str;
  lab_title_str = "background-color:rgba(0,0,0,0);color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  lab_title_str += ";";
  ui->tips_lab->setStyleSheet(lab_title_str);

  //提示内容
  QString lab_context_str;
  lab_context_str =
      "background-color:rgba(0,0,0,0);color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  lab_context_str += ";";
  ui->lab_context->setStyleSheet(lab_context_str);

  // OK
  QString btn_ok_str;
  btn_ok_str = "color:" + BFSkinSetting::GetInstance()->GetTextColor(0).name(
                              QColor::HexArgb);
  btn_ok_str += ";border-radius:14px;background-color:";
  btn_ok_str +=
      BFSkinSetting::GetInstance()->GetMainColor().name(QColor::HexArgb);
  btn_ok_str += ";";
  ui->ok_btn->setStyleSheet(btn_ok_str);

  //确认
  QString btn_confirm_str;
  btn_confirm_str =
      "color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  btn_confirm_str += ";border-radius:14px;background-color:";
  btn_confirm_str +=
      BFSkinSetting::GetInstance()->GetMainColor().name(QColor::HexArgb);
  btn_confirm_str += ";";
  ui->confirm_btn->setStyleSheet(btn_confirm_str);

  //取消
  QString btn_cancel_str;
  btn_cancel_str =
      "color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
  btn_cancel_str += ";border-radius:14px;background-color:";
  btn_cancel_str += BFSkinSetting::GetInstance()->GetInputAndButtonColor().name(
      QColor::HexArgb);
  btn_cancel_str += ";";
  ui->cancel_btn->setStyleSheet(btn_cancel_str);

  //关闭按钮
  QString btn_close_str = GetSkinResource("mainbody_close.svg");
  btn_close_str += "background-color:transparent;";
  btn_close_str += "background:transparent;";
  btn_close_str += "border:none;";
  ui->btn_close->setStyleSheet(btn_close_str);
}

void BFMessageBox::InitUi() {
  //大小
  this->setFixedSize(364, 225);

  //备用字体
  QFont font_16;
  font_16.setPixelSize(16);
  font_16.setFamily(QString::fromUtf8("Microsoft Yahei"));

  QFont font_13;
  font_13.setPixelSize(13);
  font_13.setFamily(QString::fromUtf8("Microsoft Yahei"));

  //标题
  ui->tips_lab->setFixedSize(364, 17);
  ui->tips_lab->move(0, 30);
  ui->tips_lab->setFont(font_16);
  ui->tips_lab->setAlignment(Qt::AlignCenter);

  //内容
  ui->lab_context->setFixedSize(300, 70);
  ui->lab_context->move(30, 76);
  ui->lab_context->setFont(font_13);

  ui->lab_context->setOpenExternalLinks(true);

  //确定按钮
  ui->confirm_btn->setFixedSize(106, 28);
  ui->confirm_btn->move(56, 167);
  ui->confirm_btn->setFont(font_13);
  ui->confirm_btn->setFocusPolicy(Qt::ClickFocus);

  //取消
  ui->cancel_btn->setFixedSize(106, 28);
  ui->cancel_btn->move(202, 167);
  ui->cancel_btn->setFont(font_13);
  ui->cancel_btn->setFocusPolicy(Qt::ClickFocus);

  // Ok按钮
  ui->ok_btn->setFixedSize(106, 28);
  ui->ok_btn->move(129, 167);
  ui->ok_btn->setFont(font_13);
  ui->cancel_btn->setFocusPolicy(Qt::ClickFocus);

  //关闭按钮
  ui->btn_close->setFixedSize(16, 16);
  ui->btn_close->move(330, 10);
  ui->btn_close->setFont(font_13);

  //样式切换
  this->SwitchStyleSheet();
}

void BFMessageBox::HideCloseButton() { ui->btn_close->hide(); }

BFMessageBox::~BFMessageBox() {
  messbox = nullptr;
  delete ui;
  qDebug() << "BFMessage exec destory";
}

// BFMessageBox* BFMessageBox::GetInstance(QWidget* parent) {
//   if (!messbox) {
//     messbox = new BFMessageBox(parent);
//   }
//   return messbox;
// }

BFMessageBox* BFMessageBox::CreateMessageBox(QWidget* parent) {
  auto msg_box = new BFMessageBox(parent);

  msg_box->setAttribute(Qt::WA_DeleteOnClose, true);
  return msg_box;
}

void BFMessageBox::ModalShow() {
  this->setModal(true);
#ifdef _WIN32
  this->open();
#endif

#ifdef __APPLE__
    this->show();
#endif
}

void BFMessageBox::SetButtonText(QString confirm, QString cancel, QString ok) {
  ui->confirm_btn->setText(confirm);
  ui->cancel_btn->setText(cancel);
  ui->ok_btn->setText(ok);
}

void BFMessageBox::SetProperty(Mode mode, QString title, QString text,
                               QWidget* parent_widget) {
  return_value = None;
  ui->retranslateUi(this);
  //确定按钮
  ui->confirm_btn->setFixedSize(106, 28);
  ui->confirm_btn->move(56, 167);

  //取消
  ui->cancel_btn->setFixedSize(106, 28);
  ui->cancel_btn->move(202, 167);

  // Ok按钮
  ui->ok_btn->setFixedSize(106, 28);
  ui->ok_btn->move(129, 167);
  this->SwitchStyleSheet();
  QString btn_cancel_str;
  switch (mode) {
    case BFMessageBox::OK_Mode:
      ui->ok_btn->setVisible(true);
      ui->confirm_btn->setVisible(false);
      ui->cancel_btn->setVisible(false);
      break;
    case BFMessageBox::CancelAndConfirm_Mode_And_Close_With_Out_Cacnel:
    case BFMessageBox::CancelAndConfirm_Mode:
      ui->ok_btn->setVisible(false);
      ui->confirm_btn->setVisible(true);
      ui->cancel_btn->setVisible(true);
      break;
    case BFMessageBox::ALL_Mode:
      ui->ok_btn->setVisible(true);
      ui->confirm_btn->setVisible(true);
      ui->cancel_btn->setVisible(true);
      //取消
      btn_cancel_str =
          "color:" +
          BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb);
      btn_cancel_str += ";border-radius:14px;background-color:";
      btn_cancel_str +=
          BFSkinSetting::GetInstance()->GetInputAndButtonColor().name(
              QColor::HexArgb);
      btn_cancel_str += ";";
      ui->ok_btn->setStyleSheet(btn_cancel_str);
      //确定按钮
      ui->confirm_btn->move(31, 167);
      //取消
      ui->cancel_btn->move(137, 167);
      // Ok按钮
      ui->ok_btn->move(243, 167);

      ui->confirm_btn->setFixedSize(90, 28);
      //取消
      ui->cancel_btn->setFixedSize(90, 28);
      // Ok按钮
      ui->ok_btn->setFixedSize(90, 28);

      break;
    default:
      break;
  }
  cur_mode = mode;

  ui->lab_context->setText(text);
  ui->btn_close->show();

  ////this->setParent(parent_widget);
  ////定在传入的窗口中间
  // int dis_width   = parent_widget->pos().x()+(parent_widget->width() -
  // this->width()) / 2; int dis_height  =
  // parent_widget->pos().y()+(parent_widget->height() - this->height()) / 2;
  // this->move( dis_width, dis_height);
  // this->setParent(parent_widget);
  //
  //定在传入的窗口中间
  // int dis_width = parent_widget->x()+(parent_widget->width() - this->width())
  // / 2; int dis_height = parent_widget->y()+(parent_widget->height() -
  // this->height()) / 2; this->move(dis_width, dis_height);

  //设置标题
  ui->tips_lab->setText(title);

  //刷新下
  this->update();
}

void BFMessageBox::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  // DrawBorderShadow(painter);

  return QDialog::paintEvent(event);
}

void BFMessageBox::closeEvent(QCloseEvent* event) {
  if (m_bMask) {
    m_bMask = false;
  }
}

void BFMessageBox::hideEvent(QHideEvent* event) {
  if (m_bMask) {
    m_bMask = false;
  }
}

void BFMessageBox::DrawBorderShadow(QPainter& painter) {
  QPainterPath path;
  path.setFillRule(Qt::WindingFill);
  path.addRect(10, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH,
               this->height() - 2 * SHADOW_WIDTH);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.fillPath(path, QBrush(Qt::white));

  QColor color(180, 180, 180);
  for (int i = 0; i < 10; i++) {
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i,
                 this->width() - (SHADOW_WIDTH - i) * 2,
                 this->height() - (SHADOW_WIDTH - i) * 2);

    int alpha_value = 150 - i /*qSqrt(i)*/ * 50;
    if (alpha_value < 0) {
      alpha_value = 0;
    }
    color.setAlpha(alpha_value);

    if (i > 3) {
      color.setAlpha(0);
    }
    painter.setPen(color);
    painter.drawPath(path);
  }
}

void BFMessageBox::on_confirm_btn_clicked() {
  this->close();
  return_value = Confirm;
  emit signalResult(return_value);
}

void BFMessageBox::on_ok_btn_clicked() {
  this->close();
  return_value = OK;
  emit signalResult(return_value);
}

void BFMessageBox::on_cancel_btn_clicked() {
  this->close();
  return_value = Cancel;
  emit signalResult(return_value);
}

void BFMessageBox::on_btn_close_clicked() {
  this->close();

  if (CancelAndConfirm_Mode == cur_mode) {
    return_value = Cancel;
    emit signalResult(return_value);
  }
}

void BFMessageBox::slotExecInThread(Mode mode, QString title, QString text,
                                    QWidget* widget) {
  this->SetProperty(mode, title, text, widget);
  this->ModalShow();
}
