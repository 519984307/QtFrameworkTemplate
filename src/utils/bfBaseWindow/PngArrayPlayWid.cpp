#include "PngArrayPlayWid.h"
#include "ui_PngArrayPlayWid.h"
#include<QTimer>
#include"QtFlieOperation.h"
#include<QDebug>
#pragma execution_character_set("utf-8") 

PngArrayPlayWid::PngArrayPlayWid(QWidget* parent)
  : QWidget(parent)
{
  ui = new Ui::PngArrayPlayWid();
  ui->setupUi(this);

  play_timer = new QTimer(this);
  play_timer->setInterval(300);
  play_timer->setSingleShot(false);
  connect(play_timer, SIGNAL(timeout()), this, SLOT(SlotPlayTimeOut()));
}

PngArrayPlayWid::~PngArrayPlayWid()
{
  delete ui;
}

void PngArrayPlayWid::SetPlayInterval(int time)
{
  if (play_timer)
  {
    play_timer->setInterval(time);
  }
}

void PngArrayPlayWid::LoadImageVec(QString file_path)
{
  QByteArray ba = file_path.toUtf8(); // must
  const char* ch = ba.data();
  bool is_dir_exist = QtFlieOperation::GetQtFileOperation()->IsDirectory(ch);

  if (!is_dir_exist)
  {
    return;
  }

  QStringList file_list = QtFlieOperation::GetQtFileOperation()->GetFolderFilesPath(file_path);
  if (0 == file_list.size())
  {
    return;
  }

  for (int i = 0; i < file_list.size(); i++)
  {
    QString cur_str = file_list[i];
    QImage cur_img;
    bool ret = cur_img.load(cur_str);
	if (ret) {
		img_list.append(cur_img);
	}

  }

  ui->lab_png_play->SetPngVec(img_list);
}

void PngArrayPlayWid::Start()
{
  if (!play_timer->isActive())
  {
    play_timer->start();
  }
}

void PngArrayPlayWid::Stop()
{
  if (play_timer->isActive())
  {
    play_timer->stop();
  }
}


void PngArrayPlayWid::SlotPlayTimeOut()
{
  int total_frame = ui->lab_png_play->GetTotalFrame();
  int cur_frame = ui->lab_png_play->GetCurFrame();

  //中间帧或者头帧
  if (cur_frame >= 0 && cur_frame < total_frame - 1)
  {
    cur_frame++;
  }

  //尾帧
  if (cur_frame == total_frame - 1)
  {
    cur_frame = 0;
  }

  ui->lab_png_play->SetCurFrame(cur_frame);
  ui->lab_png_play->update();
}



void PngArrayLabel::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

  if (m_img_list.size() == 0)
  {
    QWidget::paintEvent(event);
    return;
  }
  QImage cur_img = m_img_list.at(m_cur_frame);
  QRect rect = this->rect();

  QPixmap pix = QPixmap::fromImage(cur_img);
  //painter.setOpacity(0.4);
  painter.drawPixmap(rect, pix);
}
