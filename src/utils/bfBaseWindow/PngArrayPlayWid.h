#pragma once

#include <QWidget>
#include <QLabel>
#include <QPainter>
namespace Ui { class PngArrayPlayWid; };

class QTimer;

class PngArrayLabel :public QLabel
{
  Q_OBJECT
public:
  PngArrayLabel(QWidget* parent) :QLabel(parent)
  {
    this->setStyleSheet("background-color:rgba(0, 0, 0, 0);");
  }
  void   SetPngVec(QList<QImage>img_list) { m_img_list = img_list; }
  int      GetCurFrame() { return  m_cur_frame; }
  void    SetCurFrame(int cur_frame) { m_cur_frame = cur_frame; }
  int       GetTotalFrame() { return  m_img_list.size(); }

  virtual void paintEvent(QPaintEvent* event);
private:
  QList<QImage>          m_img_list;
  int                                m_cur_frame = 0;
};







class PngArrayPlayWid : public QWidget
{
  Q_OBJECT

public:
  PngArrayPlayWid(QWidget* parent = Q_NULLPTR);
  ~PngArrayPlayWid();


  //播放间隔
  void SetPlayInterval(int time = 200);
  //加载image,按顺序加载文件夹内所有png图片
  void LoadImageVec(QString);

  void Start();
  void Stop();

private:
  Ui::PngArrayPlayWid* ui;

  //存储png qimage
  QList<QImage>           img_list;

  //定时器,播放timer
  QTimer* play_timer;

private slots:
  void SlotPlayTimeOut();
};
