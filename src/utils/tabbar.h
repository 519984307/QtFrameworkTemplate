#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>
#include <QToolButton>
#include "toolbutton.h"
#include "utilsexport.h"
class TabWidget;
class AddTabButton;

class UTILS_EXPORT TabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit TabBar(TabWidget *parent = 0);
    explicit TabBar(QWidget *Parent = 0);
    void setTabClosable (int index, bool closable, QToolButton *closeButton = 0);
    QTabBar::ButtonPosition iconButtonPosition();
    QTabBar::ButtonPosition closeButtonPosition ();

    void setTabWidget(TabWidget* tabWidget);

    void setInMove (bool inMove);
    void setMaxTabWidth(int width);
    bool isMoving() const {return m_bInMove;}
    bool isAddTabButtonVisible() const;

    void wheelEvent(QWheelEvent* event);
    void setAddTabButtonVisible(bool bVisible);
    AddTabButton* addTabButton() {return m_buttonAddTab;}
    void updateAddTabButtonPos() const;
    void setTabWidth(int index, int width);

protected:
    QSize tabSizeHint (int) const;
    void mouseReleaseEvent (QMouseEvent*);
    void mousePressEvent (QMouseEvent*);
    void mouseMoveEvent (QMouseEvent*);
    void dragEnterEvent (QDragEnterEvent*);
    void dropEvent (QDropEvent*);
    void mouseDoubleClickEvent (QMouseEvent*);
    void tabInserted (int);
    void tabRemoved (int);
    void moveAddTabButton(int posX) const;
    void resizeEvent(QResizeEvent * event);

    virtual void paintEvent (QPaintEvent* ev);
signals:
    void addNewTab ();
    void tabWasInserted (int);
    void tabWasRemoved (int);
    void releasedMouseAfterMove (int index);

private:
    bool m_bInMove;
    TabWidget *m_tabWidget;
    QPoint m_ptDragStartPos;
    int m_dragIndex;
    int m_maxTabWidth;
    AddTabButton* m_buttonAddTab;
    QMap<int, int> m_tabWidths;

};


class UTILS_EXPORT AddTabButton : public ToolButton
{
public:
    explicit AddTabButton(QWidget* parent, TabBar* tabBar);

protected:
    void wheelEvent(QWheelEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

    TabBar* m_tabBar;
    //TabWidget* m_tabWidget;
};


#endif // TABBAR_H
