#include "inputdialog.h"
#include "ui_inputdialog.h"
#include <QPushButton>

InputDialog::InputDialog(const QString &themePath, const QString initStr /* = "" */, QWidget *parent /* = 0 */) :
QDialog(parent),
ui(new Ui::InputDialog)
{
	ui->setupUi(this);
//    ui->pushButtonClose->setVisible(false);
//	connect(ui->pushButtonClose, SIGNAL(clicked()), SLOT(reject()));
	ui->lineEditInput->setPlaceholderText(QString());
	ui->lineEditInput->setText(initStr);
    //setMainLayout(ui->verticalLayoutMain);
    resize(392, 208);
    //setResizeable(false);

	//ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!initStr.isEmpty());
	connect(ui->lineEditInput, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    //connect(SkinManager::instance()->instance(), SIGNAL(skinChanged()), SLOT(onSkinChanged()));
    //onSkinChanged();

    //Qt5.3.0版本的bug，标准按钮没有翻译，采用临时解决方案，后续更新sdk后可以删除这段代码
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    //Qt5.3.0版本的bug，标准按钮没有翻译，采用临时解决方案，后续更新sdk后可以删除这段代码
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setObjectName("pushbutton-gray");
	m_canEmpty = true;
    m_themePath = themePath;
    m_maxUtf8Length = 1000;
    initSkinData();
}

InputDialog::~InputDialog()
{
	delete ui;
    emit widgetDestroyed();
}

/*void InputDialog::onSkinChanged()
{
	WidgetSkin skin = SkinManager::instance()->widgetSkin(SKINS_INPUTDIALOG);
	if (skin.bValid)
	{
		setBG(QPixmap(skin.bgs[SKINS_INPUTDIALOG_BG].bgFileName), skin.bgs[SKINS_INPUTDIALOG_BG].bgSizes);
		StylePushButton::Info info;
		info.tooltip = tr("Close");
		info.urlNormal = skin.stylePushButtonUrls[SKINS_TITLEBUTTON_CLOSE].normal;
		info.urlHover = skin.stylePushButtonUrls[SKINS_TITLEBUTTON_CLOSE].hover;
		info.urlPressed = skin.stylePushButtonUrls[SKINS_TITLEBUTTON_CLOSE].pressed;
		ui->pushButtonClose->setInfo(info, StylePushButton::State1st);
		setOffsetMargins(QMargins(0,-1,-1,0));

		ui->labelTitle->setStyleSheet("QLabel{font: bold;}");
	}
}*/

void InputDialog::setTitle(const QString &title)
{
	ui->labelTitle->setText(title);
	setWindowTitle(title);
}

void InputDialog::setTip(const QString &tip)
{
	ui->labelTip->setText(tip);
}

void InputDialog::setPlaceholderText(const QString& placeholderText)
{
	ui->lineEditInput->setPlaceholderText(placeholderText);
}

void InputDialog::setLineEditText(const QString &text)
{
    ui->lineEditInput->setText(text);
}

void InputDialog::setMaxInputUtf8Length(int len)
{
    //ui->lineEditInput->setMaxLength(len);
    m_maxUtf8Length = len;
}

void InputDialog::setMaxInputLength(int len)
{
    ui->lineEditInput->setMaxLength(len);
}

QString InputDialog::result()
{
	return ui->lineEditInput->text();
}

void InputDialog::onTextChanged(const QString & text)
{
	if(!m_canEmpty)
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
	else
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    if(text.toUtf8().length() > m_maxUtf8Length)
    {
        QString str = text;
        if(!str.isEmpty())
        {
            do{
                str.remove(str.length() - 1, 1);
            } while(str.toUtf8().length() > m_maxUtf8Length && !str.isEmpty());
        }
        ui->lineEditInput->setText(str);
    }
//    if(text.toUtf8().length() <= m_maxUtf8Length - 3)
//        ui->lineEditInput->setMaxLength(m_maxUtf8Length);
//    else
//        ui->lineEditInput->setMaxLength(text.length());
}

void InputDialog::setCanEmpty(bool b)
{
	m_canEmpty = b;
	if(b)
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
	else
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!result().isEmpty());
}

//ISkinWidget
bool InputDialog::isResizable() const
{
    return false;
}
int InputDialog::resizeBorderWidth() const
{
    return 0;
}
bool InputDialog::isMaximized() const
{
    return m_bMaximized;
}

void InputDialog::setMaximized(const bool bMaximized)
{
    m_bMaximized = bMaximized;
}

QRect InputDialog::restoreRect() const
{
    return m_restoreRect;
}

void InputDialog::setRestoreRect(const QRect restoreRect)
{
    //Q_UNUSED(restoreRect);
    m_restoreRect = restoreRect;
}

void InputDialog::initSkinData()
{
    m_bMaximized = false;

    m_skinData.pixmapSourceBG = QPixmap(m_themePath+"/messagebox/bg.png");
    m_skinData.bgSizes.border = 8;
    m_skinData.bgSizes.radius = 12;
    m_skinData.bgSizes.topBarHeight = 50;
    //m_skinData.bTopBottomFirst = false;

    ui->widgetSizeToolBar->initializeButtons(true, false,false);
    connect(ui->widgetSizeToolBar->closeButton(), SIGNAL(clicked()), SLOT(reject()));
    ui->widgetSizeToolBar->closeButton()->setMultiIcon(QPixmap(m_themePath + "/chatdialog/titlebar-close.png"));

    SkinManager::sharedManager()->registSkinWidget(this);
}
