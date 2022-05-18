#include "BfProgressDialog.h"
#include "bfskinmodule/bfskinsetting.h"
#include "BFSkinManager.h"
#include "bfqtutils.h"
#include <qdebug.h>
#include <QKeyEvent>
#include <QTimer>

#pragma execution_character_set("utf-8")

BfProgressDialog::BfProgressDialog(QWidget* lpParent)
    : CPopupDialog(lpParent, true, true, true, true, false) {
  InitUi();
  qDebug() << "BfProgressDialog::BfProgressDialog";
}

BfProgressDialog::~BfProgressDialog() {
  qDebug() << "BfProgressDialog::~BfProgressDialog()";
}

void BfProgressDialog::InitUi() {
  this->setObjectName("BfProgressDialog");
  this->setTitleFixedHeight(30);
  SetTitleLabelVisible(false);
  SetCloseButtonVisible(true);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setFixedSize(304, 142);
  this->setFocusPolicy(Qt::NoFocus);
  //title
  QFont font_yahei_16;
  font_yahei_16.setFamily("Microsoft YaHei");
  font_yahei_16.setPixelSize(16);

  m_titleinfoLabel = new QLabel(this);
  m_titleinfoLabel->move(0, 30 - 3 - 4);
  m_titleinfoLabel->setFixedSize(304, 30);
  m_titleinfoLabel->setAlignment(Qt::AlignCenter);
  m_titleinfoLabel->setFont(font_yahei_16);
  m_titleinfoLabel->setStyleSheet("color:" +
      BFSkinSetting::GetInstance()->GetTextColor(0).name(QColor::HexArgb));

  //progress
  m_lpProgress = new QProgressBar(this);
  assert(m_lpProgress != NULL);
  m_lpProgress->setFixedSize(244, 6);
  m_lpProgress->move(30, 82);
  m_lpProgress->setRange(0, 100);
  m_lpProgress->setFocusPolicy(Qt::NoFocus);

  m_lpProgress->setOrientation(Qt::Horizontal);
  m_lpProgress->setMinimum(0);
  m_lpProgress->setMaximum(100);
  m_lpProgress->setTextVisible(false);
  m_lpProgress->setStyleSheet("QProgressBar{background:" +
      BFSkinSetting::GetInstance()->GetPopupProgressBarUnSelectColor2().name(QColor::HexArgb) +
      ";border-radius:3px;text-align:center;} QProgressBar::chunk{border-radius:3px; background:" +
      BFSkinSetting::GetInstance()->GetPopupProgressBarSelectColor().name(QColor::HexArgb) + ";}");

  //message
  QFont font_yahei_12;
  font_yahei_12.setFamily("Microsoft YaHei");
  font_yahei_12.setPixelSize(12);
  m_lpMessage = new QLabel(this);
  assert(m_lpMessage != NULL);
  m_lpMessage->setFont(font_yahei_12);
  m_lpMessage->setStyleSheet("color:" +
      BFSkinSetting::GetInstance()->GetTextColor(1).name(QColor::HexArgb));
  m_lpMessage->setFixedSize(304, 20);
  m_lpMessage->move(0, 100);
  m_lpMessage->setAlignment(Qt::AlignHCenter);
  m_lpMessage->setFocusPolicy(Qt::NoFocus);
}

void BfProgressDialog::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    return;
  }
  CPopupDialog::keyPressEvent(event);
}

void BfProgressDialog::DoModal()
{
    Open();
}

void BfProgressDialog::SetMessage(QString strMessage)
{
    if ( !m_lpMessage ){ assert( 0 );
    }else{
        m_lpMessage -> setText( strMessage );
    }
}

void BfProgressDialog::SetTitle(QString strTitle) 
{
  if (m_titleinfoLabel) {
    m_titleinfoLabel->setText(strTitle);
    QFont font_yahei_16;
    font_yahei_16.setFamily("Microsoft YaHei");
    font_yahei_16.setPixelSize(16);
    int width = BfQtUtils::WidthWithFixString(font_yahei_16, strTitle);
    m_titleinfoLabel->setFixedWidth(width);

    int x = (this->width() - width) / 2;
    int y = m_titleinfoLabel->y();
    m_titleinfoLabel->move(x, y);
  }
}

void BfProgressDialog::SetProgress(int progress) 
{
  if (m_lpProgress) {
    m_lpProgress->setValue(progress);
  }
}

void BfProgressDialog::CloseWindow() { 
#ifdef __APPLE__
    QTimer::singleShot(500,this,[this](){
        // bug http://pms.inner.auntec.cn:8203/bug-view-24267.html
        close();
    });
#endif

#ifdef WIN32
        close();
#endif
}

void BfProgressDialog::slotCloseBtnClicked(bool val) {
  if (!m_isCanceled) {
    m_isCanceled = true;
    m_lpMessage->setText(QString::fromUtf8("正在取消任务"));
    emit userCancle();
  }
}
