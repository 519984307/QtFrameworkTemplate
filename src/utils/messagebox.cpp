#include "messagebox.h"
#include "ui_messagebox.h"
#include "skinmanager.h"
#include <QPushButton>

WidgetMessageBox::WidgetMessageBox(Type type, const QString& tip, QDialogButtonBox::StandardButtons btns,
                                   const QString &themePath, const QString& title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageBox)
{
	ui->setupUi(this);
    setObjectName("message-box");
    m_type = type;
	m_clickedRole = QDialogButtonBox::RejectRole;
	ui->labelTitle->setText(title);
	setWindowTitle(title);

	ui->labelTip->setText(tip);
	
    //setMainLayout(ui->verticalLayoutMain);
	ui->buttonBox->setStandardButtons(btns);

	connect(ui->buttonBox, SIGNAL(accepted()), SLOT(accept()));
	connect(ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));
	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), SLOT(buttonClicked(QAbstractButton*)));

    //Qt5.3.0版本的bug，标准按钮没有翻译，采用临时解决方案，后续更新sdk后可以删除这段代码
    if(ui->buttonBox->button(QDialogButtonBox::Cancel))
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    if(ui->buttonBox->button(QDialogButtonBox::Ok))
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    if(ui->buttonBox->button(QDialogButtonBox::Yes))
        ui->buttonBox->button(QDialogButtonBox::Yes)->setText(tr("Yes"));
    if(ui->buttonBox->button(QDialogButtonBox::No))
        ui->buttonBox->button(QDialogButtonBox::No)->setText(tr("No"));
    //Qt5.3.0版本的bug，标准按钮没有翻译，采用临时解决方案，后续更新sdk后可以删除这段代码
    if(ui->buttonBox->button(QDialogButtonBox::Cancel))
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setObjectName("pushbutton-gray");
    ui->buttonBox->layout()->setSpacing(10);

	// compute the dialog height
	QStringList tipLines = tip.split(QChar('\n'));
	int lines = 0;
	QFontMetrics fontMetrics = ui->labelTip->fontMetrics();
	foreach (QString tipLine, tipLines)
	{
		int tipLen = fontMetrics.width(tipLine);
		lines += tipLen/240 + 1;
	}
	int lineHeight = (fontMetrics.height()+10) * (lines+1);
	if (lineHeight < 64)
		lineHeight = 64;
    int height = 140 + lineHeight;
    resize(356, height);
    m_themePath = themePath;

    initSkinData();
    initTheme();

}

WidgetMessageBox::~WidgetMessageBox()
{
	delete ui;
    emit widgetDestroyed();
}

void WidgetMessageBox::setButtonText(QDialogButtonBox::StandardButton which, const QString &text)
{
    QPushButton* btn = ui->buttonBox->button(which);
    if(btn)
    {
        btn->setText(text);
    }
}

void WidgetMessageBox::buttonClicked(QAbstractButton *button)
{
	m_clickedRole = ui->buttonBox->buttonRole(button);
}

void WidgetMessageBox::initTheme()
{
    switch (m_type) {
    case Success:
        ui->labelIcon->setPixmap(QPixmap(m_themePath + "/messagebox/success.png"));
        break;
    case Failed:
        ui->labelIcon->setPixmap(QPixmap(m_themePath + "/messagebox/failed.png"));
        break;
    case Question:
        ui->labelIcon->setPixmap(QPixmap(m_themePath + "/messagebox/question.png"));
        break;
    case Information:
        ui->labelIcon->setPixmap(QPixmap(m_themePath + "/messagebox/info.png"));
        break;
    case Warning:
        ui->labelIcon->setPixmap(QPixmap(m_themePath + "/messagebox/warning.png"));
        break;
    default:
        ui->labelIcon->setPixmap(QPixmap(m_themePath + "/messagebox/success.png"));
        break;
    }
    //ui->labelIcon->setPixmap(QPixmap(m_themePath + "/messagebox/info.png"));
    ui->widgetSizeToolBar->closeButton()->setMultiIcon(QPixmap(m_themePath + "/chatdialog/titlebar-close.png"));
}

//ISkinWidget
bool WidgetMessageBox::isResizable() const
{
    return false;
}
int WidgetMessageBox::resizeBorderWidth() const
{
    return 0;
}
bool WidgetMessageBox::isMaximized() const
{
    return m_bMaximized;
}

void WidgetMessageBox::setMaximized(const bool bMaximized)
{
    m_bMaximized = bMaximized;
}

QRect WidgetMessageBox::restoreRect() const
{
    return m_restoreRect;
}

void WidgetMessageBox::setRestoreRect(const QRect restoreRect)
{
    //Q_UNUSED(restoreRect);
    m_restoreRect = restoreRect;
}

void WidgetMessageBox::initSkinData()
{
    m_bMaximized = false;

    m_skinData.pixmapSourceBG = QPixmap(m_themePath+"/messagebox/bg.png");
    m_skinData.bgSizes.border = 8;
    m_skinData.bgSizes.radius = 12;
    m_skinData.bgSizes.topBarHeight = 50;
    //m_skinData.bTopBottomFirst = false;

    ui->widgetSizeToolBar->initializeButtons(true, false,false);
    connect(ui->widgetSizeToolBar->closeButton(), SIGNAL(clicked()), SLOT(reject()));

    SkinManager::sharedManager()->registSkinWidget(this);
}

