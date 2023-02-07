#ifndef MAINWIDGETPLUGIN_H
#define MAINWIDGETPLUGIN_H

#include "interfaces/ipluginmanager.h"
#include"interfaces/MainWidget/imainwidget.h"
#include"mainwidget.h"

class MainWidgetPlugin :
		public QObject,
		public IPlugin,
        public IMainWidgetPlugin
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "mainwidget.json")
#endif
    Q_INTERFACES(IPlugin IMainWidgetPlugin)
   public:
    MainWidgetPlugin();
    ~MainWidgetPlugin();
	virtual QObject* instance() { return this; }
	//IPlugin
    virtual QUuid pluginUuid() const { return MAINWIDGET_UUID; }
    virtual void pluginInfo(IPluginInfo *aPluginInfo);
    virtual bool initConnections(IPluginManager *aPluginManager, int &aInitOrder);
	virtual bool initObjects();
	virtual bool initSettings();
    virtual bool startPlugin();
    //IMainWidgetPlugin
    virtual IMainWidget *mainWidget() const;
    virtual void showMainWidget();
    virtual void showStartupDialog();
    virtual void closeStartupDialog();
    virtual bool isStartDialogVisible() const;

signals:
    void mainWidgetCreated();
    void aboutToSignOut();

protected slots:
    void onAboutToClose();
    void onMainWidgetAboutToDestory();

private:
    IPluginManager *m_pluginManager = NULL;
    MainWidget *m_mainWidget = NULL;
};

#endif // MAINWIDGETPLUGIN_H
