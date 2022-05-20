#ifndef IMAINWIDGET_H
#define IMAINWIDGET_H

#include <QtGlobal>
#include <skinmanager.h>

#define MAINWIDGET_UUID "{89586123-e83d-451c-a1d5-84ff78b76d79}"


class IMainWidget
{
public:
    virtual QWidget *instance() = 0;


//添加外部模块需要访问的接口


};

class IMainWidgetPlugin
{
public:
    virtual QObject *instance() = 0;
    virtual IMainWidget *mainWidget() const = 0;
    virtual void showMainWidget() = 0;

protected:
    virtual void mainWidgetCreated() = 0;
    virtual void aboutToSignOut() = 0;
};

Q_DECLARE_INTERFACE(IMainWidget,"QtFrameworkTemplate.Plugin.IMainWidget/1.0")
Q_DECLARE_INTERFACE(IMainWidgetPlugin,"QtFrameworkTemplate.Plugin.IMainWidgetPlugin/1.0")
#endif
