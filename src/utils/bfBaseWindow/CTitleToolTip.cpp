#include "CTitleToolTip.h"
#include "BFSkinManager.h"
#include <QLayout>

CTitleToolTip::CTitleToolTip(QWidget * parent) :QWidget(parent)
{
	this->setAttribute(Qt::WA_DeleteOnClose);								//关闭时释放
	this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint|Qt::Tool);							//无边框
	this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);	//保持在最上方
	this->setAttribute(Qt::WA_TranslucentBackground, true);					//透明
	this->setFixedSize(QSize(160, 20));

	//this->setStyleSheet(QString("background:") + BFBackGroundColorGet().name() + QString(";border:1px solid gray;font-size:12px;}"));

	m_toolTip = new QLabel(this);
	QString toolTipStr = QString("color:" + BFTextColorGet(0).name(QColor::HexArgb) + ";;font-size:12px;font-family:\"Microsoft YaHei\";");
	m_toolTip->setStyleSheet(toolTipStr);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setAlignment(Qt::AlignCenter);
	layout->addWidget(m_toolTip);
}

CTitleToolTip::~CTitleToolTip()
{

}

void CTitleToolTip::setPos(int x, int y)
{
	this->move(x,y);
}

void CTitleToolTip::paintEvent(QPaintEvent * event)
{
	QPainter p(this);
	p.setPen(QColor(Qt::gray));
	p.setBrush(QColor(BFBackGroundColorGet().name()));
	p.drawRoundedRect(this->rect(),2,2);
	QWidget::paintEvent(event);
}
