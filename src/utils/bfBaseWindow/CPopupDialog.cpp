#include <QGraphicsDropShadowEffect>
#include <QCoreApplication>
#include <QPainter>

#include "CPopupTitleBarWidget.h"
#include "CPopupDialog.h"
#include <qMath.h>
#include <QStyleOption>
#include <QPainterPath>
#include "bfskinmodule/bfskinsetting.h"

#define SHADOW_DIALOG_WIDTH 10

CPopupDialog::CPopupDialog
	(
	QWidget* parent/*=0*/,
	bool bClose/*=true*/,
	bool bTitle/*=true*/,
	bool bRepaint/*=true*/,
	bool bDelete/*=true*/,
	bool bIcon
	)
	:
QDialog( parent, Qt::FramelessWindowHint ),
m_pClientLayout(NULL), m_pTitleBar(NULL)
{
	if ( bDelete )
	{
		this->setAttribute(Qt::WA_DeleteOnClose);
	}

	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowIcon(QIcon(BFSkinSetting::GetInstance()->GetResourceAbsolutePath("nav_logo.svg")));

	//加装一层产品wid_main
	m_wid_main = new QWidget(this);
	QGridLayout*wid_main_layout = new QGridLayout(this);
	wid_main_layout->addWidget(m_wid_main);
	wid_main_layout->setSpacing(0);
	wid_main_layout->setContentsMargins(0, 0, 0, 0);
	wid_main_layout->setObjectName(QString::fromUtf8("main_layout"));


	//子类逻辑在m_pClientLayout扩充
	QVBoxLayout* pMainLayout = new QVBoxLayout(m_wid_main);
	if (NULL != pMainLayout)
	{
		m_pTitleBar = new CPopupTitleBarWidget(this, m_wid_main, bClose, bTitle, bRepaint, bIcon);
		if (NULL != m_pTitleBar) 
		{
			QSizePolicy sp = m_pTitleBar->sizePolicy();
			sp.setVerticalPolicy(QSizePolicy::Fixed);
			m_pTitleBar->setSizePolicy(sp);
			if (bClose) 
			{
				connect(m_pTitleBar, SIGNAL(signalCloseBtnClicked(bool)), this, SLOT(slotCloseBtnClicked(bool)));
			}
			pMainLayout->addWidget(m_pTitleBar);
		}
		//设置控件之间的间距为0
		pMainLayout->setSpacing(0);
		pMainLayout->addStretch();
		pMainLayout->setContentsMargins(0, 0, 0, 0);

                m_pClientLayout = new QVBoxLayout;
                if (NULL != m_pClientLayout)
		{
			pMainLayout->addLayout(m_pClientLayout);
		}
		pMainLayout->addStretch();
		setLayout(pMainLayout);
	}

	//样式表切换
	m_wid_main->setObjectName("wid_main");
	this->SwitchStyleSheet();
}

CPopupDialog::~CPopupDialog()
{

}

void CPopupDialog::SwitchStyleSheet()
{
	//主体窗口相应设置
	QString win_style_str;
     win_style_str+="#wid_main{background-color:";
     win_style_str += BFSkinSetting::GetInstance()->GetPopupWinBackgroundColor().name(QColor::HexArgb);
     win_style_str += ";border-radius:";
     win_style_str += QString::number(8);//整个软件下拉框以及弹窗圆角
	 win_style_str+="px;border:1px solid; border-color:";
     win_style_str+= BFSkinSetting::GetInstance()->GetPopupWinBorderColor().name(QColor::HexArgb);
	 win_style_str += ";}";
	 m_wid_main->setStyleSheet(win_style_str);
}

void CPopupDialog::Open()
{
    //GSTODO show弹窗之前判断？
    //if (BFMainWin::GetInstance()->IsGuideState()) {
        //return false;
    //}
    //BFMainWin::GetInstance()->SetMaskWidShow(true);
#ifdef _WIN32
  this->open();
#endif

#ifdef __APPLE__
    this->setModal(true);
    this->show();
#endif
}

void CPopupDialog::ModalShow() {
  //引导状态不显示任何弹窗 GSTODO show弹窗之前判断？
  //if (BFMainWin::GetInstance()->IsGuideState()) {
    //return;
  //}    
  this->setModal(true);
#ifdef _WIN32
  this->open();
#endif

#ifdef __APPLE__
    this->show();
#endif

}

void CPopupDialog::paintEvent(QPaintEvent* paint)
{
	//QPainter painter(this);
	//painter.setPen(Qt::NoPen);
	//painter.setBrush(BFSkinSetting::GetInstance()->GetPopupWinBackgroundColor());
	//painter.drawRect(this->rect());
	////外矩形绘制阴影 
	////相当于依次画10个a值递减德矩形
	////[2020.10.26 Tom]
	//DrawBorderShadow(painter);
	////内矩形绘制颜色
	//QRect adjust = this->rect().adjusted(SHADOW_DIALOG_WIDTH, SHADOW_DIALOG_WIDTH, -SHADOW_DIALOG_WIDTH, -SHADOW_DIALOG_WIDn);TH);
	////painter.setBrush(QBrush(/*Qt::white*/BFBackGroundColorGet()));
	//painter.setBrush(QBrush(BFSkinManager::GetDialogContext()));
	//painter.setPen(Qt::NoPe
	//painter.drawRect(adjust);
	////painter.drawRoundedRect(adjust, 10, 10);
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	//return QDialog::paintEvent(paint);
}

void CPopupDialog::closeEvent(QCloseEvent* event)
{
    //BFMainWin::GetInstance()->SetMaskWidShow(false);
}

void CPopupDialog::hideEvent(QHideEvent* event)
{
    //BFMainWin::GetInstance()->SetMaskWidShow(false);
}

void CPopupDialog::slotCloseBtnClicked( bool )
{
	close();
	// Todo：需要接口使用者重载后拦截软件关闭信息
}

void CPopupDialog::DrawBorderShadow(QPainter& painter)
{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(SHADOW_DIALOG_WIDTH, SHADOW_DIALOG_WIDTH, this->width() - 2 * SHADOW_DIALOG_WIDTH, this->height() - 2 * SHADOW_DIALOG_WIDTH);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));

	QColor color(180, 180, 180);
	for (int i = 0; i < 10; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		QRect need_rect = QRect(SHADOW_DIALOG_WIDTH - i, SHADOW_DIALOG_WIDTH - i, this->width() - (SHADOW_DIALOG_WIDTH - i) * 2, this->height() - (SHADOW_DIALOG_WIDTH - i) * 2);
		
		path.addRect(need_rect);
		//path.addRoundedRect(need_rect, 10, 10);


		int alpha_value = 150 - i /*qSqrt(i)*/ * 50;
		if (alpha_value < 0)
		{
			alpha_value = 0;
		}
		color.setAlpha(alpha_value);


		if (i > 3)
		{
			color.setAlpha(0);
		}
		painter.setPen(color);
		painter.drawPath(path);
	}
}

void CPopupDialog::setTitleFixedHeight(int height)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->setFixedHeight( height );
	}
}

void CPopupDialog::SetTitleLabelFixedSize(int width, int height)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetTitleLabelFixedSize(width, height);
	}
}

void CPopupDialog::SetTitleLabelStyleSheet(const QString& styleSheet)
{
	if (NULL != m_pTitleBar) 
	{
		((CPopupTitleBarWidget*)m_pTitleBar)->SetTitleLabelStyleSheet(styleSheet);
	}
}

void CPopupDialog::SetTitleLabelText(const QString& text)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetTitleLabelText(text);
	}
}

void CPopupDialog::SetTitleLabelObjectName(const QString& objectName)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetTitleLabelObjectName(objectName);
	}
}

void CPopupDialog::SetTitleLabelVisible(bool bVisible)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetTitleLabelVisible(bVisible);
	}
}

void CPopupDialog::SetCloseButtonFixedSize(int width, int height)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetCloseButtonFixedSize(width, height);
	}
}

void CPopupDialog::SetCloseButtonlStyleSheet(const QString& styleSheet)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetCloseButtonlStyleSheet(styleSheet);
	}
}

void CPopupDialog::SetCloseButtonText(const QString& text)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetCloseButtonText(text);
	}
}

void CPopupDialog::SetCloseButtonObjectName(const QString& objectName)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetCloseButtonObjectName(objectName);
	}
}

void CPopupDialog::SetCloseButtonVisible(bool bVisible)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetCloseButtonVisible(bVisible);
	}
}

void CPopupDialog::SetDownloadFolder(bool value, int fWidth)
{
	((CPopupTitleBarWidget*)m_pTitleBar)->SetDownloadFolderDialog(true, fWidth);
}

void CPopupDialog::SetIconImagePath(const QString & strPath)
{
	if (NULL != m_pTitleBar) {
		((CPopupTitleBarWidget*)m_pTitleBar)->SetIcoLabelImagePath( strPath );
	}
}
