#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QToolButton>
#include <QFlags>
#include "toolbutton.h"
#include <definitions/namespace.h>
#include "utilsexport.h"

class TabBar;

class UTILS_EXPORT TabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = 0);

    virtual int widgetCount () const;
    virtual QWidget* widget (int index) const;
    void setCurrentTab (int tabIndex);
    void setCurrentWidget (QWidget *widget);
    void setPreviousTab ();

    void setCurrentIndex (int index);
    virtual int indexOf (QWidget *widget) const;
    virtual int currentIndex () const;
    virtual QWidget* currentWidget () const;

    virtual QString tabText (int index) const;
    virtual void setTabText (int index, const QString& text);

    virtual QIcon tabIcon (int index) const;
    virtual void setTabIcon (int index, const QIcon& icon);

    virtual QString tabToolTip (int index) const;
    virtual void setTabToolTip (int index, const QString& toolTip);

    virtual QMenu* tabMenu (int);

    int addTab (QWidget *widget, bool bCloseable, const QString& text, const HH::NewTabPositionFlags &openFlags = HH::NT_SelectedTab);
    int addTab (QWidget *widget, bool bCloseable, const QIcon& icon, const QString& text, const HH::NewTabPositionFlags &openFlags = HH::NT_SelectedTab);
    int insertTab (int index, QWidget *widget, bool bCloseable, const QString& text);
    int insertTab (int index, QWidget *widget, bool bCloseable,
                   const QIcon& icon, const QString& text);
    void removeTab (int index);
    void removeAllTabs();
    void removeTab(QWidget *widget);

    inline bool validIndex(int index) const { return index >= 0 && index < widgetCount(); }

    int tabAt (const QPoint& point);
    void moveTab (int from, int to);

    void addAction2TabBar (QAction *action);
    void insertAction2TabBar (int position, QAction *action);
    void insertAction2TabBar (QAction *before, QAction *action);


    int lastContextMenuTab() const {return m_lastContextMenuTab;}

    void addWidget2MainLayout(QWidget* widget);
    void insertWidget2MainLayout(int index, QWidget* widget);
    void removeWidgetFromMainLayout(QWidget*widget);
    int mainLayoutWidgetCount();

    void setTabBar(TabBar* tabBar, bool bInsertToLayout = false);
    TabBar* tabBar() {return m_tabBar;}
    void setTabCloseIcon(const QPixmap& iconNormal, const QPixmap& iconSelected = QPixmap());
    QStackedWidget* stackedWidget() {return m_stackedWidget;}
    QVBoxLayout* mainLayout() {return m_mainnLayout;}

    void startTabAnimation(int index);
    void stopTabAnimation(int index);
    void hideTabIcon(int index);
    void setLoadAnimationFilePath(const QString& filepath);

public slots:


signals:
    void tabInserted (int index);
    void tabRemoved (int index);
    void tabRemoved(QWidget* tab);
    void tabCloseRequested (int index);
    void newTabMenuRequested ();
    void currentChanged (int index);
    void tabMoved (int from, int to);
    void allTabsClosed();

protected slots:
    virtual void onAddNewTab();
    void onTabCloseRequested(int index);
    void onTabInserted(int index);
    virtual void onTabRemoved(int index);
//    virtual void onTabRemoved(QWidget* tab);
    void onTabMoved(int from, int to);
    void onCurrentChanged(int index);
    void onContextMenuRequested (const QPoint& point);
    void onReleaseMouseAfterMove(int index);
    void onActionDestroyed ();
    void onTabCloseButtonClicked();
    void updateCurrentTabCloseButton(int index = 0);
    void onTabDestroyed();


protected:
    ToolButton *newTabCloseButton(int index);


private:
    QStackedWidget* m_stackedWidget;
    TabBar* m_tabBar;
    QVBoxLayout *m_mainnLayout;

    QWidget *m_currentWidget;
    int m_currentIndex;
    QWidget *m_previousWidget;
    QList<QAction*> m_tabBarActions;
    int m_lastContextMenuTab;
    QHash<QWidget*, ToolButton*> m_tabCloseButtons;
    QPixmap m_tabCloseIconNormal;
    QPixmap m_tabCLoseIconSelected;
    QString m_loadAnimationFilePath;
};
#endif // TABWIDGET_H
