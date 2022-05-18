#ifndef EXPANDTABWIDGET_H
#define EXPANDTABWIDGET_H

#include <QWidget>
#include "utilsexport.h"
#include <QBoxLayout>
#include "skinmanager.h"
#include <QPixmap>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QStackedWidget>


typedef struct _WidgetBorder{
    int top;
    int left;
    int right;
    int bottom;
    int height;
    int width;
    int radius;
}WidgetBorder;

typedef struct _StyleUrls{
    QString normal;
    QString hover;
    QString pressed;
    QString selected;
    QString disabled;
    QString readonly;
    QString background;
}StyleUrls;

typedef struct _WidgetBorderStyle{
    StyleUrls urls;
    WidgetBorder border;
}WidgetBorderStyle;

class UTILS_EXPORT TabPushButton : public QPushButton
{
    Q_OBJECT

    enum ButtonState{
        BS_UNKNOW,
        BS_NORMAL,
        BS_HOVER,
        BS_SELECTED
    };
public:
    explicit TabPushButton(QWidget *parent = 0);
    void setTabButtonIcon(const QString& iconNormal, const QString& iconHover, const QString& iconSelected);
    void setTabButtonIcon(const QIcon& iconNormal, const QIcon& iconHover, const QIcon& iconSelected);
	void setBorderStyle(const WidgetBorderStyle& style);

public slots:
	void onClicked();

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void selected();

private:
    QIcon m_iconSelected;
    QIcon m_iconNormal;
    QIcon m_iconHover;
    ButtonState m_buttonState;
};

class UTILS_EXPORT ExpandTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExpandTabWidget(QWidget *parent = 0);
    //void setTabBarMargin(int left, int top, int right, int bottom);
    //void setTabBarBackground(const QString& background);
	void setTabButtonBorderStyle(const WidgetBorderStyle& style);
    void setTabButtonIcon(QWidget* widget, const QString& iconNormal, const QString& iconHover, const QString& iconSelected);
    void setTabButtonIcon(QWidget* widget, const QIcon& iconNormal, const QIcon& iconHover, const QIcon& iconSelected);
    //void setTabButtonSeperator(const QString& seperator);
	void setTabText(QWidget* widget, const QString& text);
    void addTab(QWidget* widget, int order, const QString& tp = "");
    void setCurrentIndex(int index);
	void setCurrentWidget(QWidget* widget);
    int currentIndex() const;
    QWidget* widget(int index) const;
    QWidget* currentWidget()const;
    //QWidget* tabBar() {return m_tabBar;}
    int indexOf(QWidget* widget)const;
    void setTabButtonIconSize(const QSize& size = QSize(32,32));
    //void setTabVisible(int index, const bool bVisible = true);
    //void setTabVisible(QWidget* widget, const bool bVisible = true);
	bool isTabVisible(int index);
	bool isTabVisible(QWidget* widget);
    void setTabBarHeight(int height);

signals:
    void currentIndexChanged(int index);
    
public slots:
    void onTabButtonClicked(bool bChecked);

protected:
    void resizeEvent(QResizeEvent * event);
    void updateTabSizes();

private:
    QStackedWidget* m_stackedWidget;
    //QWidget* m_tabBar;
    QHBoxLayout* m_tabBarLayout;
    QVBoxLayout* m_layoutMain;
    QMap<TabPushButton*, QWidget*> m_tabButtonsMap;
    QMap<QWidget*, int> m_tabWidgetOrders;
	WidgetBorderStyle m_tabButtonStyle;
    QWidget* m_tabBarWidget;
    int m_tabBarHeight;
    //QPixmap m_seperatorPixmap;
    //QList<QLabel *> m_seperatorLabels;
};

#endif // EXPANDTABWIDGET_H
