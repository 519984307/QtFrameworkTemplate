#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDir>
#include <QHash>
#include <QTimer>
#include <QPointer>
#include <QTranslator>
#include <QDomDocument>
#if QT_VERSION < 0x050000
#include <QApplication>
#else
#include <QtWidgets/QApplication>
#endif
#include <QPluginLoader>
#include <QSessionManager>

#include "interfaces/ipluginmanager.h"

#include "definitions/version.h"
#include "definitions/commandline.h"
#include "definitions/plugininitorders.h"


enum ShutdownKind {
    SK_WORK,
    SK_QUIT,
    SK_RESTART
};

struct PluginItem
{
    IPlugin *plugin;
    IPluginInfo *info;
    QPluginLoader *loader;
    QTranslator *translator;
};

QString GetHomePath();

class PluginManager :
            public QObject,
            public IPluginManager
{
    Q_OBJECT
    Q_INTERFACES(IPluginManager)
public:
    PluginManager(QApplication *AParent);
    ~PluginManager();
    virtual QObject *instance() { return this; }
    virtual QString version() const;
    virtual QString revision() const;
    virtual QDateTime revisionDate() const;
    virtual bool isShutingDown() const;
    virtual QString homePath() const;
    virtual QString tempPath() const;
    virtual QString resourcesPath() const;
    virtual QString themePath() const;
    virtual QString translationsPath() const;
    virtual QString datasPath() const;
    virtual QString commonResourcesPath() const;
    virtual void setHomePath(const QString &APath);
    virtual void setLocale(QLocale::Language ALanguage, QLocale::Country ACountry);
    virtual void setTheme(const QString& theme);
    virtual QString theme() const;
    virtual IPlugin* pluginInstance(const QUuid &AUuid) const;
    virtual QList<IPlugin *> pluginInterface(const QString &AInterface = QString()) const;
    virtual const IPluginInfo *pluginInfo(const QUuid &AUuid) const;
    virtual QList<QUuid> pluginDependencesOn(const QUuid &AUuid) const;
    virtual QList<QUuid> pluginDependencesFor(const QUuid &AUuid) const;
    void loadSettings();
public slots:
    virtual void quit();
    virtual void start();
    virtual void restart();
    virtual void delayShutdown();
    virtual void continueShutdown();
#ifdef Q_OS_MAC
    void onDockIconClicked();
#endif
signals:
    void aboutToQuit();
    void shutdownStarted();

    void about();

#ifdef Q_OS_MAC
    void dockIconClicked();
#endif
protected:
    void saveSettings();
    void loadPlugins();
    bool initPlugins();
    void startPlugins();
    void updateTheme();
protected:
    void startShutdown();
    void finishShutdown();
    void closeTopLevelWidgets();
protected:
    void removePluginItem(const QUuid &AUuid, const QString &AError);
    void unloadPlugin(const QUuid &AUuid, const QString &AError = QString());
    bool checkDependences(const QUuid &AUuid) const;
    bool checkConflicts(const QUuid AUuid) const;
    QList<QUuid> getConflicts(const QUuid &AUuid) const;
    void loadCoreTranslations(const QDir &ADir, const QString &ALocaleName);
protected:
    bool isPluginEnabled(const QString &AFile) const;
    QDomElement savePluginInfo(const QString &AFile, const IPluginInfo *AInfo);
    void savePluginError(const QString &AFile, const QString &AEror);
    void removePluginsInfo(const QStringList &ACurFiles);
protected slots:
    void onApplicationAboutToQuit();
    void onApplicationCommitDataRequested(QSessionManager &AManager);
    void onShutdownTimerTimeout();
private:
    int m_shutdownKind;
    int m_shutdownDelayCount;
    QTimer m_shutdownTimer;
private:
    QString m_dataPath;
    QDomDocument m_pluginsSetup;
    QTranslator *m_qtTranslator;
    QTranslator *m_utilsTranslator;
    QTranslator *m_loaderTranslator;
    QStringList m_blockedPlugins;
    QHash<QUuid, PluginItem> m_pluginItems;
    mutable QMultiHash<QString, IPlugin *> m_plugins;
    bool m_isShuttingDown{false};
};

#endif
