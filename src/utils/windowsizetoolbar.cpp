#include "windowsizetoolbar.h"
#include <QSpacerItem>

WindowSizeToolBar::WindowSizeToolBar(QWidget *parent) :
    QWidget(parent)
{
    m_closeButton = NULL;
    m_minimizeButton = NULL;
    m_MaximumButton = NULL;
    m_mainLayout = NULL;
    m_buttonsLayout = NULL;
}

void WindowSizeToolBar::initializeButtons(bool bContainCloseButton, bool bContainMinimizeButton, bool bContainMaximumButton)
{
    if(!m_mainLayout)
    {
        m_mainLayout = new QVBoxLayout(this);
        m_mainLayout->setContentsMargins(0, 0, 0, 0);
        m_mainLayout->setSpacing(0);
    }

    if(!m_buttonsLayout)
    {
        m_buttonsLayout = new QHBoxLayout(NULL);
        m_buttonsLayout->setContentsMargins(0, 0, 0, 0);
        m_buttonsLayout->setSpacing(0);
    }

    m_mainLayout->addLayout(m_buttonsLayout);
    m_mainLayout->addStretch();

    if(bContainCloseButton && !m_closeButton)
    {
        m_closeButton = new ToolButton(this);
        m_closeButton->setToolTip(tr("Close"));
        //m_closeButton->setAttribute(Qt::WA_Hover, true);
        connect(m_closeButton, SIGNAL(clicked()), this, SIGNAL(closeButtonClicked()));

    }
    if(bContainMinimizeButton && !m_minimizeButton)
    {
        m_minimizeButton = new ToolButton(this);
        m_minimizeButton->setToolTip(tr("Minimize"));
        connect(m_minimizeButton, SIGNAL(clicked()), this, SIGNAL(minimizeButtonClicked()));

    }
    if(bContainMaximumButton && !m_MaximumButton)
    {
        m_MaximumButton = new ToolButton(this);
        m_MaximumButton->setToolTip(tr("Maximum"));
        connect(m_MaximumButton, SIGNAL(clicked()), this, SIGNAL(maximumButtonClicked()));
    }
//#ifdef Q_OS_MAC
//    if(m_closeButton)
//    {
//        m_buttonsLayout->addWidget(m_closeButton, 0, buttonsVAlign);
//    }
//    if(m_minimizeButton)
//    {
//        m_buttonsLayout->addWidget(m_minimizeButton, 0, buttonsVAlign);
//    }
//    if(m_MaximumButton)
//    {
//        m_buttonsLayout->addWidget(m_MaximumButton, 0, buttonsVAlign);
//    }
//#endif

//#ifdef Q_OS_WIN
    if(m_minimizeButton)
    {
        m_buttonsLayout->addWidget(m_minimizeButton);
    }
    if(m_MaximumButton)
    {
        m_buttonsLayout->addWidget(m_MaximumButton);
    }
    if(m_closeButton)
    {
        m_buttonsLayout->addWidget(m_closeButton);
    }
//#endif

}
