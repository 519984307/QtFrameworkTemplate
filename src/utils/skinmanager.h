#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QObject>
#include "NcFramelessHelper.h"
#include <QWidget>
#include <QPixmap>
#include <QMap>
#include "utilsexport.h"

#define DEFAULT_SKINWIDGET_RESIZE_BORDERWIDTH   5

struct SkinWidgetBGSizes{
    SkinWidgetBGSizes()
    {
        border = 0;
        radius = 0;
        topBarHeight = 0;
        rightBarWidth = 0;
        bottomBarHeight = 0;
        leftBarWidth = 0;
    }
    int border;
    int radius;
    int topBarHeight;
    int bottomBarHeight;
    int leftBarWidth;
    int rightBarWidth;
};

struct SkinWidgetSubBGs{
    QPixmap topLeftCorner;
    QPixmap topBorder;
    QPixmap topRightCorner;
    QPixmap rightBorder;
    QPixmap bottomRightCorner;
    QPixmap bottomBorder;
    QPixmap bottomLeftCorner;
    QPixmap leftBorder;
    QPixmap topBar;
    QPixmap rightBar;
    QPixmap bottomBar;
    QPixmap leftBar;
    QPixmap central;
};

struct SkinWidgetData
{
    SkinWidgetBGSizes bgSizes;
    QPixmap pixmapSourceBG;
    bool bCompressPixmap;
    bool bTopBottomFirst;    //拉升时,以头和底优先
    SkinWidgetData(){
        bTopBottomFirst = true;
        bCompressPixmap = true;
    }
};


class ISkinWidget
{
public:
    virtual QWidget* instance() = 0;
    virtual bool isResizable() const = 0;
    virtual int resizeBorderWidth() const = 0;
    virtual bool isMaximized() const = 0;
    virtual void setMaximized(const bool bMaximized) = 0;
    virtual QRect restoreRect() const = 0;
    virtual void setRestoreRect(const QRect restoreRect) = 0;
    virtual SkinWidgetData skinData() const = 0;
    virtual void initSkinData() = 0;
protected:
    virtual void widgetDestroyed() = 0;
    virtual void maximizeButtonClicked() = 0;
    virtual void minimizeButtonClicked() = 0;
};

Q_DECLARE_INTERFACE(ISkinWidget,"AUNBOX.ISkinWidget/1.0")

class SkinManager;

class ISkinManagerHolder{
public:
    virtual SkinManager* skinManager() = 0;
};

Q_DECLARE_INTERFACE(ISkinManagerHolder,"AUNBOX.ISkinManagerHolder/1.0")

class UTILS_EXPORT SkinManager :
        public QObject
{
    Q_OBJECT
public:
    explicit SkinManager(QObject *parent = 0);
    void registSkinWidget(ISkinWidget* widget);
    static SkinManager* sharedManager();
    void setWidgetResizable(ISkinWidget* widget);
    void showWidgetMaximize(ISkinWidget* widget);
    void showWidgetNormal(ISkinWidget* widget);

protected slots:
    void onWidgetDestroyed();
    void onWidgetMaximizeButtonClicked();
    void onWidgetMinimizeButtonClicked();

protected:
    QPixmap generateWidgetBG(ISkinWidget *widget) const;
    QPixmap getWidgetBG(ISkinWidget* widget);
    SkinWidgetSubBGs generateWidgetSubBGs(ISkinWidget* skinWidget);
    virtual bool eventFilter( QObject* obj, QEvent* event );
    void paintWidget(ISkinWidget* widget);
private:
    mutable QHash<QString, QMap<ISkinWidget*, QPixmap> > m_widgetBGs;
    QMap<QString, QPixmap> m_widgetRecommendedBGs;
    QMap<QString, QPixmap> m_widgetMaximizeBGs;
    QMap<QString, SkinWidgetSubBGs> m_widgetSubBGs;
    NcFramelessHelper* m_framelessHelper;
};

#endif // SKINMANAGER_H
