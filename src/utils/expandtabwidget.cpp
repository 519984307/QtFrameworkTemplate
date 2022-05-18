#include "expandtabwidget.h"
#include <QDebug>
#include <QPaintEvent>

TabPushButton::TabPushButton(QWidget *parent):
    QPushButton(parent)
{
    setCheckable(true);
    setChecked(false);
    connect(this, SIGNAL(clicked()), SLOT(onClicked()));
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_buttonState = BS_UNKNOW;
}

void TabPushButton::setBorderStyle(const WidgetBorderStyle& style)
{
    setStyleSheet(QString("QPushButton{"
                          "border-top: %1px;"
                          "border-left: %2px;"
                          "border-right: %3px;"
                          "border-bottom: %4px;"
                          "border-image: url(%5);"
                          "}"

                          "QPushButton:hover{"
                          "border-image: url(%6);"
                          "}"
                          "QPushButton:checked{"
                          "border-image: url(%7);"
                          "}"
                          ).arg(style.border.top)
                  .arg(style.border.left)
                  .arg(style.border.right)
                  .arg(style.border.bottom)
                  .arg(style.urls.normal)
                  .arg(style.urls.hover)
                  .arg(style.urls.selected)
                  );
}

void TabPushButton::setTabButtonIcon(const QString& iconNormal, const QString& iconHover, const QString& iconSelected)
{
    m_iconNormal = QIcon(iconNormal);
    m_iconSelected = QIcon(iconSelected);
    m_iconHover = QIcon(iconHover);
    update();
}


void TabPushButton::setTabButtonIcon(const QIcon& iconNormal, const QIcon &iconHover, const QIcon& iconSelected)
{
    m_iconNormal = iconNormal;
    m_iconSelected = iconSelected;
    m_iconHover = iconHover;
    update();
}

void TabPushButton::onClicked()
{
    setChecked(true);
}

void TabPushButton::paintEvent(QPaintEvent *e)
{
    if(underMouse() && !isChecked())
    {
        if(BS_HOVER != m_buttonState)
        {
            m_buttonState = BS_HOVER;
            setIcon(m_iconHover);
        }
    }
    else if(isChecked())
    {
        if(BS_SELECTED != m_buttonState)
        {
            m_buttonState = BS_SELECTED;
            setIcon(m_iconSelected);
        }
    }
    else
    {
        if(BS_NORMAL != m_buttonState)
        {
            m_buttonState = BS_NORMAL;
            setIcon(m_iconNormal);
        }
    }
    QPushButton::paintEvent(e);
}

ExpandTabWidget::ExpandTabWidget(QWidget *parent) :
    QWidget(parent)
{
    m_stackedWidget = new QStackedWidget(this);

    m_layoutMain = new QVBoxLayout(this);
    m_layoutMain->setSpacing(0);
    m_layoutMain->setContentsMargins(0,0,0,0);
    m_tabBarWidget = new QWidget(this);

    m_layoutMain->addWidget(m_tabBarWidget, 0);
    m_layoutMain->addWidget(m_stackedWidget, 1);
}

//void ExpandTabWidget::setTabBarMargin(int left, int top, int right, int bottom)
//{
//	m_tabBar->layout()->setContentsMargins(left, top, right, bottom);
//}

//void ExpandTabWidget::setTabBarBackground(const QString& background)
//{
//	m_tabBar->setStyleSheet(QString(
//		"QWidget#tabBar {"
//		"	background-image: url(%1);"
//		"}"
//		).arg(background));
//}

void ExpandTabWidget::setTabButtonBorderStyle(const WidgetBorderStyle& style)
{
    m_tabButtonStyle = style;
    foreach(TabPushButton* btn, m_tabButtonsMap.keys())
    {
        btn->setBorderStyle(m_tabButtonStyle);
    }
}

void ExpandTabWidget::setTabButtonIcon(QWidget* widget, const QString& iconNormal, const QString &iconHover, const QString& iconSelected)
{
    if (m_tabButtonsMap.values().contains(widget))
    {
        m_tabButtonsMap.key(widget)->setTabButtonIcon(iconNormal, iconHover, iconSelected);
    }
}


void ExpandTabWidget::setTabButtonIcon(QWidget* widget, const QIcon& iconNormal, const QIcon &iconHover, const QIcon& iconSelected)
{
    if (m_tabButtonsMap.values().contains(widget))
    {
        m_tabButtonsMap.key(widget)->setTabButtonIcon(iconNormal, iconHover, iconSelected);
    }
}

//void ExpandTabWidget::setTabButtonSeperator(const QString& seperator)
//{
//	m_seperatorPixmap = QPixmap(seperator);
//	if (!m_seperatorPixmap.isNull())
//	{
//		foreach(QLabel* sepLabel, m_seperatorLabels)
//		{
//			if (sepLabel)
//			{
//				sepLabel->setPixmap(m_seperatorPixmap);
//				sepLabel->setFixedSize(m_seperatorPixmap.size());
//			}
//		}
//	}
//	else
//	{
//		foreach(QLabel* sepLabel, m_seperatorLabels)
//		{
//			if (sepLabel)
//			{
//				sepLabel->setFixedSize(QSize(0, 0));
//			}
//		}
//	}
//}

void ExpandTabWidget::setTabText(QWidget* widget, const QString& text)
{
	if (m_tabButtonsMap.values().contains(widget))
	{
		m_tabButtonsMap.key(widget)->setText(text);
	}
}

void ExpandTabWidget::addTab(QWidget *widget, int order, const QString &tp)
{
	// insert widget
    int index = m_stackedWidget->count();
    if(m_stackedWidget->count() > 0)
    {
        for(int i=m_stackedWidget->count()-1; i>=0; i--)
        {
            QWidget* addedWidget = m_stackedWidget->widget(i);
            if(m_tabWidgetOrders.contains(addedWidget) &&
                    m_tabWidgetOrders[addedWidget] <= order)
            {
                index = i+1;
                break;
            }
            if(i == 0)
                index = 0;
        }
    }
    m_stackedWidget->insertWidget(index, widget);
    m_tabWidgetOrders[widget] = order;

	// insert tab button first

    TabPushButton* btn = new TabPushButton(m_tabBarWidget);
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setIconSize(QSize(28,28));
    if(!tp.isEmpty())
        btn->setToolTip(tp);
    btn->setBorderStyle(m_tabButtonStyle);
    btn->setFixedHeight(m_tabBarHeight);
    m_tabButtonsMap[btn] = widget;
    connect(btn, SIGNAL(clicked(bool)), SLOT(onTabButtonClicked(bool)));
//    m_tabBarLayout->setContentsMargins(0,0,0,0);

    updateTabSizes();
    setCurrentIndex(0);
}

void ExpandTabWidget::setCurrentIndex(int index)
{
    if (index <0 || index >= m_stackedWidget->count())
    {
        return;
    }
    QWidget* widget = m_stackedWidget->widget(index);
    foreach (TabPushButton* btn, m_tabButtonsMap.keys()) {
        if(m_tabButtonsMap[btn] != widget)
        {
            btn->setChecked(false);
        }
        else
        {
            btn->setChecked(true);
        }
    }
    m_stackedWidget->setCurrentIndex(index);
    emit currentIndexChanged(index);
}

void ExpandTabWidget::setCurrentWidget(QWidget* widget)
{
	setCurrentIndex(m_stackedWidget->indexOf(widget));
}

int ExpandTabWidget::currentIndex() const
{
    return m_stackedWidget->currentIndex();
}

void ExpandTabWidget::onTabButtonClicked(bool bChecked)
{
    TabPushButton* btn = qobject_cast<TabPushButton*>(sender());
    if(btn && bChecked)
    {
        setCurrentIndex(m_stackedWidget->indexOf(m_tabButtonsMap[btn]));
        //qDebug() << btn->pos();
    }
}

QWidget* ExpandTabWidget::widget(int index) const
{
    return m_stackedWidget->widget(index);
}

QWidget* ExpandTabWidget::currentWidget() const
{
    return m_stackedWidget->currentWidget();
}

int ExpandTabWidget::indexOf(QWidget *widget) const
{
    return m_stackedWidget->indexOf(widget);
}

void ExpandTabWidget::setTabButtonIconSize(const QSize &size)
{
    foreach (TabPushButton* btn, m_tabButtonsMap.keys()) {
        btn->setIconSize(size);
    }
}

//void ExpandTabWidget::setTabVisible(int index, const bool bVisible /* = true */)
//{
//	if (index >= 0 && index < m_stackedWidget->count())
//	{
//		QWidget* widget = m_stackedWidget->widget(index);
//		TabPushButton* btn = qobject_cast<TabPushButton*>(m_tabButtonsMap.key(widget));
//		if (btn->isVisible() != bVisible)
//		{
//			btn->setVisible(bVisible);
			
//			// check if this tab is the last one, if not last, need to set the seperator visibility
//			if (m_stackedWidget->count() > 1)
//			{
//				int tabButtonIndex = 2*index;
//				if (tabButtonIndex == 0)
//				{
//					if (m_seperatorLabels.count() > 1 && m_seperatorLabels[1] != 0)
//						m_seperatorLabels[1]->setVisible(bVisible);
//				}
//				else
//				{
//					if (m_seperatorLabels.count() > tabButtonIndex && m_seperatorLabels[tabButtonIndex-1] != 0 )
//						m_seperatorLabels[tabButtonIndex-1]->setVisible(bVisible);
//				}
//			}

//			if (!bVisible)
//			{
//				if ((index+1) >= m_stackedWidget->count())
//				{
//					setCurrentIndex(0);
//				}
//				else
//				{
//					setCurrentIndex(index + 1);
//				}
//			}
//		}
//	}
//}

//void ExpandTabWidget::setTabVisible(QWidget* widget,const bool bVisible /* = true */)
//{
//	int index = m_stackedWidget->indexOf(widget);
//	setTabVisible(index, bVisible);
//}

bool ExpandTabWidget::isTabVisible(int index)
{
	if (index >= 0 && index < m_stackedWidget->count())
	{
		QWidget* widget = m_stackedWidget->widget(index);
		TabPushButton* btn = qobject_cast<TabPushButton*>(m_tabButtonsMap.key(widget));
		return btn->isVisible();
	}
	return false;
}

bool ExpandTabWidget::isTabVisible(QWidget* widget)
{
	int index = m_stackedWidget->indexOf(widget);
	return isTabVisible(index);
}

void ExpandTabWidget::setTabBarHeight(int height)
{
    m_tabBarWidget->setFixedHeight(height);
    m_tabBarHeight = height;
    foreach(TabPushButton* btn, m_tabButtonsMap.keys())
    {
        btn->setFixedHeight(height);
    }
}

void ExpandTabWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateTabSizes();
}

void ExpandTabWidget::updateTabSizes()
{
    QList<TabPushButton*> tabs = m_tabButtonsMap.keys();
    if(tabs.count() > 0)
    {
        int tabWidth = width() / tabs.count();
        for(int i=0; i<tabs.count(); i++)
        {
            int index = m_stackedWidget->indexOf(m_tabButtonsMap.value(tabs.at(i)));
            if(index == tabs.count() - 1)
            {
                tabs.at(i)->setFixedWidth(width() - tabWidth*(tabs.count() - 1));
            }
            else
            {
                tabs.at(i)->setFixedWidth(tabWidth);
            }
            tabs.at(i)->move(QPoint(index*tabWidth, tabs.at(i)->pos().y()));
        }
    }
}
