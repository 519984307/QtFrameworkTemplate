#ifndef BFPROGRESSDIALOG_H
#define BFPROGRESSDIALOG_H

#include "CPopupDialog.h"
#include <QLabel>
#include <QProgressBar>

class BfProgressDialog : public CPopupDialog {
  Q_OBJECT
 public:
  BfProgressDialog(QWidget* lpParent = NULL);
  ~BfProgressDialog();

  void DoModal();
  void SetMessage(QString strMessage);
  void SetTitle(QString strTitle);
  void SetProgress(int progress);
  void CloseWindow();
 signals:
  void userCancle();
 private slots:
  void slotCloseBtnClicked(bool val);

 private:
  void InitUi();

 protected:
  void keyPressEvent(QKeyEvent*);

 private:
  QLabel* m_titleinfoLabel =
      nullptr;  //标题信息（eg.正在导出素材）可以设置显示或者隐藏，调整内容
  QLabel* m_lpMessage = nullptr;  //进度信息（已完成XX%）
  QProgressBar* m_lpProgress = nullptr;
  bool m_isCanceled = false;
};

#endif  // BFPROGRESSDIALOG_H
