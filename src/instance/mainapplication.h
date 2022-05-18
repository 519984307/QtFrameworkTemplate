#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QApplication>
#include <QMenuBar>
#include <QMenu>

#include <QList>
#include <QMap>
#include <QUuid>
#include <QTimer>

#include "utils/console.h"
#include "utils/skinmanager.h"
#include "utils/log.h"

#include "interfaces/iglobalsetting.h"
//#include "interfaces/imainwidget.h"

#include "pluginmanager.h"
#include "qtsingleapplication.h"

class MainApplication : public QtSingleApplication, public IConsoleHolder, public ISkinManagerHolder, public ILoggerProvider
{
    Q_OBJECT
    Q_INTERFACES(IConsoleHolder ISkinManagerHolder ILoggerProvider)

public:
    MainApplication(int &argc, char** argv);
    ~MainApplication();
    void setMainWidgetVisible(bool visible);
#ifdef Q_OS_MAC
    QMenu* macDockMenu();
    QMenuBar *macMenuBar();
#endif
    //IConsoleHolder
    virtual Console* console();
    //ISkinManagerHolder
    virtual SkinManager* skinManager();
    //ILoggerProvider
    virtual Log4Qt::Logger* logger();

    virtual QString applicationName() const;
    virtual QString applicationId() const;

signals:
    void shutdown();
public slots:
    void newPluginManager();
    void onPluginManagerAboutToQuit();
    void onMessageReceived(QString msg);

#ifdef Q_OS_MAC
public slots:
    void onClickOnDock();
    void onMacDockQuit();
#endif

protected slots:
    void onAboutToQuit();

protected:
    void quitInstanceByManagerRequest();
    void initPlugin();

private:
    QString m_id;

public:
    QString m_dataDir;
    QString m_themeDir;
#ifdef Q_OS_MAC
    QMenu *m_macDockMenu;
    QMenuBar *m_macMenuBar;
#endif
    PluginManager* m_pluginManager;
};

#endif // MAINAPPLICATION_H
