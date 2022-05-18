#include "pluginmanager.h"

#include <QtDebug>
#include <QWidget>
#include <QTimer>
#include <QStack>
#include <QThread>
#include <QProcess>
#include <QLibrary>
#include <QFileInfo>
#include <QSettings>
#include <QLibraryInfo>
#include <QDebug>
#include <QTextCodec>
#include "regexp.h"
#include <QApplication>
#include <QMessageBox>
//#include "bfEventTrack/bfEventTrack.h"
#include "bfskinsetting.h"
//#include "interfaces/imainwidget.h"
#include"utils/BFCommandLineParser.h"
#pragma execution_character_set("utf-8")

#define DELAYED_QUIT_TIMEOUT 5000
#define DELAYED_COMMIT_TIMEOUT 2000

#define SVN_DATA_PATH "DataPath"
#define SVN_LOCALE_NAME "Locale"
#define FILE_PLUGINS_SETTINGS "plugins.xml"
#define THEME_SETTINGS_KEY "theme"
#define COMMON_RESOURCE_PATH "common"

#ifdef SVNINFO
#  include "svninfo.h"
#  define SVN_DATE                  ""
#else
#  define SVN_DATE                  ""
#  define SVN_REVISION              "0"
#endif

#if defined(Q_OS_WIN)
#  define ENV_APP_DATA              "APPDATA"
#  define DIR_APP_DATA              APPLICATION_NAME
#  define PATH_APP_DATA             APPLICATION_NAME
#elif defined(Q_OS_MAC)
#  define ENV_APP_DATA              "HOME"
#  define DIR_APP_DATA              APPLICATION_NAME
#  define PATH_APP_DATA             "Library/Application Support/" DIR_APP_DATA
#endif

#if defined(Q_OS_WIN)
#  define LIB_PREFIX_SIZE           0
#else
#  define LIB_PREFIX_SIZE           3
#endif

const QString kPluginDir = "ui_plugins";

PluginManager::PluginManager(QApplication *AParent) : QObject(AParent)
{
    m_shutdownKind = SK_WORK;
    m_shutdownDelayCount = 0;

    m_qtTranslator = new QTranslator(this);
    m_utilsTranslator = new QTranslator(this);
    m_loaderTranslator = new QTranslator(this);

    m_shutdownTimer.setSingleShot(true);
    connect(&m_shutdownTimer,SIGNAL(timeout()),SLOT(onShutdownTimerTimeout()));

    //connect(AParent,SIGNAL(aboutToQuit()),SLOT(onApplicationAboutToQuit()));
    connect(AParent,SIGNAL(commitDataRequest(QSessionManager &)),SLOT(onApplicationCommitDataRequested(QSessionManager &)));
}

PluginManager::~PluginManager()
{

}

QString PluginManager::version() const
{
    return CLIENT_VERSION;
}

QString PluginManager::revision() const
{
    static const QString rev = QString(SVN_REVISION).contains(':') ? QString(SVN_REVISION).split(':').value(1) : QString(SVN_REVISION);
    return rev;
}

QDateTime PluginManager::revisionDate() const
{
    return QDateTime::fromString(SVN_DATE,"yyyy/MM/dd hh:mm:ss");
}

bool PluginManager::isShutingDown() const
{
  if(m_isShuttingDown){
    return true;
  }
    return m_shutdownKind != SK_WORK;
}

QString PluginManager::homePath() const
{
    return m_dataPath;
}

QString PluginManager::tempPath() const
{
    QString temp = "temp";
    QDir tempDir(m_dataPath);
    if(!tempDir.exists(temp))
        tempDir.mkpath(temp);
    tempDir.cd(temp);
    return tempDir.absolutePath();
}

QString PluginManager::resourcesPath() const
{
    QDir resourcesDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
    if (resourcesDir.dirName() == "MacOS") {
        resourcesDir.cdUp();
    }
#endif
    resourcesDir.cd("Resources");
    return resourcesDir.absolutePath();
}

QString PluginManager::themePath() const
{
    return QString("%1/themes/%2").arg(resourcesPath()).arg(theme());
}

QString PluginManager::translationsPath() const
{
    return QString("%1/translations").arg(resourcesPath());
}

QString PluginManager::datasPath() const
{
    return QString("%1/datas").arg(resourcesPath());
}

QString PluginManager::commonResourcesPath() const
{
    QDir dir(homePath());
    if(!dir.exists(COMMON_RESOURCE_PATH))
        dir.mkpath(COMMON_RESOURCE_PATH);
    dir.cd(COMMON_RESOURCE_PATH);
    return dir.absolutePath();
}

void PluginManager::setHomePath(const QString &APath)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(SVN_DATA_PATH, APath);
}

void PluginManager::setLocale(QLocale::Language ALanguage, QLocale::Country ACountry)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    if (ALanguage != QLocale::C)
        settings.setValue(SVN_LOCALE_NAME, QLocale(ALanguage, ACountry).name());
    else
        settings.remove(SVN_LOCALE_NAME);
}

void PluginManager::setTheme(const QString &theme)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(THEME_SETTINGS_KEY, theme);
    updateTheme();
}

QString PluginManager::theme() const
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    return settings.value(THEME_SETTINGS_KEY, "default").toString();
}

void PluginManager::updateTheme()
{
    QString themePath = this->themePath();
    themePath += "/";
    QFile cssFile(themePath + "main.css");
    cssFile.open(QFile::ReadOnly);
    QString css = cssFile.readAll();
    cssFile.close();
#ifdef QZ_WS_X11
    if (QFile(themePath + "linux.css").exists()) {
        cssFile.setFileName(themePath + "linux.css");
        cssFile.open(QFile::ReadOnly);
        css.append(cssFile.readAll());
        cssFile.close();
    }
#endif
#ifdef Q_OS_MAC
    if (QFile(themePath + "mac.css").exists()) {
        cssFile.setFileName(themePath + "mac.css");
        cssFile.open(QFile::ReadOnly);
        css.append(cssFile.readAll());
        cssFile.close();
    }
#endif
#if defined(Q_OS_WIN) || defined(Q_OS_OS2)
    if (QFile(themePath + "windows.css").exists()) {
        cssFile.setFileName(themePath + "windows.css");
        cssFile.open(QFile::ReadOnly);
        css.append(cssFile.readAll());
        cssFile.close();
    }
#endif

    QString relativePath = QDir::current().relativeFilePath(themePath);

    css.replace(RegExp("url\\s*\\(\\s*([^\\*:\\);]+)\\s*\\)", Qt::CaseSensitive),
                QString("url(%1\\1)").arg(relativePath + "/"));
    //qDebug() << relativePath;
    //qDebug() << css;
    qApp->setStyleSheet(css);
}

IPlugin *PluginManager::pluginInstance(const QUuid &AUuid) const
{
    return m_pluginItems.contains(AUuid) ? m_pluginItems.value(AUuid).plugin : NULL;
}

QList<IPlugin *> PluginManager::pluginInterface(const QString &AInterface) const
{
    //QList<IPlugin *> plugins;
    if (!m_plugins.contains(AInterface))
    {
        foreach(PluginItem pluginItem, m_pluginItems)
            if (AInterface.isEmpty() || pluginItem.plugin->instance()->inherits(AInterface.toLatin1().data()))
                m_plugins.insertMulti(AInterface,pluginItem.plugin);
    }
    return m_plugins.values(AInterface);
}

const IPluginInfo *PluginManager::pluginInfo(const QUuid &AUuid) const
{
    return m_pluginItems.contains(AUuid) ? m_pluginItems.value(AUuid).info : NULL;
}

QList<QUuid> PluginManager::pluginDependencesOn(const QUuid &AUuid) const
{
    static QStack<QUuid> deepStack;
    deepStack.push(AUuid);

    QList<QUuid> plugins;
    QHash<QUuid, PluginItem>::const_iterator it = m_pluginItems.constBegin();
    while (it != m_pluginItems.constEnd())
    {
        if (!deepStack.contains(it.key()) && it.value().info->dependences.contains(AUuid))
        {
            plugins += pluginDependencesOn(it.key());
            plugins.append(it.key());
        }
        ++it;
    }

    deepStack.pop();
    return plugins;
}

QList<QUuid> PluginManager::pluginDependencesFor(const QUuid &AUuid) const
{
    static QStack<QUuid> deepStack;
    deepStack.push(AUuid);

    QList<QUuid> plugins;
    if (m_pluginItems.contains(AUuid))
    {
        QList<QUuid> dependences = m_pluginItems.value(AUuid).info->dependences;
        foreach(QUuid depend, dependences)
        {
            if (!deepStack.contains(depend) && m_pluginItems.contains(depend))
            {
                plugins.append(depend);
                plugins += pluginDependencesFor(depend);
            }
        }
    }

    deepStack.pop();
    return plugins;
}

void PluginManager::quit() {
  qInfo() << "Quit";
  if (m_shutdownKind == SK_WORK) {
    m_shutdownKind = SK_QUIT;
    startShutdown();
  }
}

void PluginManager::start() {
    m_shutdownTimer.stop();
    m_shutdownKind = SK_WORK;
    m_shutdownDelayCount = 0;

    qDebug() << "PluginManager::start()";
    updateTheme();

    //BFSkinSetting::GetInstance()->LoadConfig();
    //BFSkinSetting::GetInstance()->LoadQss();

    loadPlugins();
    if (initPlugins())
    {
        saveSettings();
        //createMenuActions();
        //declareShortcuts();
        startPlugins();
        m_blockedPlugins.clear();
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(start()));
    }
}

void PluginManager::restart()
{
    if (m_shutdownKind == SK_WORK)
    {
        m_shutdownKind = SK_RESTART;
        startShutdown();
    }
}

void PluginManager::delayShutdown()
{
    if (m_shutdownKind != SK_WORK)
    {
        m_shutdownDelayCount++;
    }
}

void PluginManager::continueShutdown()
{
    if (m_shutdownKind != SK_WORK)
    {
        m_shutdownDelayCount--;
        if (m_shutdownDelayCount <= 0)
            m_shutdownTimer.start(0);
    }
}

#ifdef Q_OS_MAC
void PluginManager::onDockIconClicked()
{
    emit dockIconClicked();
}

#endif

QString GetHomePath()
{
    QStringList args = qApp->arguments();
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    QLocale locale(QLocale::C,  QLocale::AnyCountry);
    if (args.contains(CLO_LOCALE))
    {
      locale = QLocale(args.value(args.indexOf(CLO_LOCALE) + 1));
    }
    if (locale.language() == QLocale::C &&
        !settings.value(SVN_LOCALE_NAME).toString().isEmpty()) {
      locale = QLocale(settings.value(SVN_LOCALE_NAME).toString());
    }
    if (locale.language() == QLocale::C) {
      locale = QLocale::system();
    }
    //    QLocale::setDefault(locale);
    QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::AnyCountry));
    QString dataPath = QString();
    if (args.contains(CLO_APP_DATA_DIR)) {
      QDir dir(args.value(args.indexOf(CLO_APP_DATA_DIR) + 1));
      if (dir.exists() &&
          (dir.exists(DIR_APP_DATA) || dir.mkpath(DIR_APP_DATA)) &&
          dir.cd(DIR_APP_DATA))
        dataPath = dir.absolutePath();
    }
    if (dataPath.isNull()) {
      QDir dir(qApp->applicationDirPath());
      if (dir.exists(DIR_APP_DATA) && dir.cd(DIR_APP_DATA))
            dataPath = dir.absolutePath();
    }
    if (dataPath.isNull() && !settings.value(SVN_DATA_PATH).toString().isEmpty())
    {
        QDir dir(settings.value(SVN_DATA_PATH).toString());
        if (dir.exists() && (dir.exists(DIR_APP_DATA) || dir.mkpath(DIR_APP_DATA)) && dir.cd(DIR_APP_DATA))
            dataPath = dir.absolutePath();
    }
    if (dataPath.isNull())
    {
        foreach(QString env, QProcess::systemEnvironment())
        {
            if (env.startsWith(ENV_APP_DATA"="))
            {
                QDir dir(env.split("=").value(1));
                if (dir.exists() && (dir.exists(PATH_APP_DATA) || dir.mkpath(PATH_APP_DATA)) && dir.cd(PATH_APP_DATA))
                    dataPath = dir.absolutePath();
            }
        }
    }
    if (dataPath.isNull())
    {
        QDir dir(QDir::homePath());
        if (dir.exists() && (dir.exists(DIR_APP_DATA) || dir.mkpath(DIR_APP_DATA)) && dir.cd(DIR_APP_DATA))
            dataPath = dir.absolutePath();
    }

    return dataPath;
}

void PluginManager::loadSettings()
{
    QStringList args = qApp->arguments();
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
    QLocale locale(QLocale::C,  QLocale::AnyCountry);
    if (args.contains(CLO_LOCALE))
    {
      locale = QLocale(args.value(args.indexOf(CLO_LOCALE) + 1));
    }
    if (locale.language() == QLocale::C &&
        !settings.value(SVN_LOCALE_NAME).toString().isEmpty()) {
      locale = QLocale(settings.value(SVN_LOCALE_NAME).toString());
    }
    if (locale.language() == QLocale::C) {
      locale = QLocale::system();
    }
    //    QLocale::setDefault(locale);
    QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::AnyCountry));
    m_dataPath = QString();
    if (args.contains(CLO_APP_DATA_DIR)) {
      QDir dir(args.value(args.indexOf(CLO_APP_DATA_DIR) + 1));
      if (dir.exists() &&
          (dir.exists(DIR_APP_DATA) || dir.mkpath(DIR_APP_DATA)) &&
          dir.cd(DIR_APP_DATA))
        m_dataPath = dir.absolutePath();
    }
    if (m_dataPath.isNull()) {
      QDir dir(qApp->applicationDirPath());
      if (dir.exists(DIR_APP_DATA) && dir.cd(DIR_APP_DATA))
            m_dataPath = dir.absolutePath();
    }
    if (m_dataPath.isNull() && !settings.value(SVN_DATA_PATH).toString().isEmpty())
    {
        QDir dir(settings.value(SVN_DATA_PATH).toString());
        if (dir.exists() && (dir.exists(DIR_APP_DATA) || dir.mkpath(DIR_APP_DATA)) && dir.cd(DIR_APP_DATA))
            m_dataPath = dir.absolutePath();
    }
    if (m_dataPath.isNull())
    {
        foreach(QString env, QProcess::systemEnvironment())
        {
            if (env.startsWith(ENV_APP_DATA"="))
            {
                QDir dir(env.split("=").value(1));
                if (dir.exists() && (dir.exists(PATH_APP_DATA) || dir.mkpath(PATH_APP_DATA)) && dir.cd(PATH_APP_DATA))
                    m_dataPath = dir.absolutePath();
            }
        }
    }
    if (m_dataPath.isNull())
    {
        QDir dir(QDir::homePath());
        if (dir.exists() && (dir.exists(DIR_APP_DATA) || dir.mkpath(DIR_APP_DATA)) && dir.cd(DIR_APP_DATA))
            m_dataPath = dir.absolutePath();
    }
    m_pluginsSetup.clear();
    QDir homeDir(m_dataPath+"/log");
    QFile file(homeDir.absoluteFilePath(FILE_PLUGINS_SETTINGS));
    if (file.exists() && file.open(QFile::ReadOnly))
        m_pluginsSetup.setContent(&file,true);
    file.close();

    if (m_pluginsSetup.documentElement().tagName() != "plugins")
    {
        m_pluginsSetup.clear();
        m_pluginsSetup.appendChild(m_pluginsSetup.createElement("plugins"));
    }
}

void PluginManager::saveSettings()
{
    if (!m_pluginsSetup.documentElement().isNull())
    {
        QDir homeDir(m_dataPath+"/log");
        QFile file(homeDir.absoluteFilePath(FILE_PLUGINS_SETTINGS));
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(m_pluginsSetup.toString(3).toUtf8());
            file.flush();
            file.close();
        }
    }
}

void PluginManager::loadPlugins()
{
    QDir pluginsDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cd("Resources");
    }
#endif
    if(pluginsDir.cd(kPluginDir))
    {
      QString s = pluginsDir.absolutePath();
        QString localeName = QLocale().name();
        QDir tsDir(translationsPath());

        loadCoreTranslations(tsDir,localeName);

        QStringList files = pluginsDir.entryList(QDir::Files);
        removePluginsInfo(files);

        foreach (QString file, files)
        {
            //qDebug() << pluginsDir.absoluteFilePath(file);
            QStringList error_module;
            if (QLibrary::isLibrary(file) && isPluginEnabled(file))
            {
                QPluginLoader *loader = new QPluginLoader(pluginsDir.absoluteFilePath(file),this);
                if (loader->load())
                {
                    IPlugin *plugin = qobject_cast<IPlugin *>(loader->instance());
                    if (plugin)
                    {
                        plugin->instance()->setParent(loader);
                        QUuid uid = plugin->pluginUuid();
                        if (!m_pluginItems.contains(uid))
                        {
                            PluginItem pluginItem;
                            pluginItem.plugin = plugin;
                            pluginItem.loader = loader;
                            pluginItem.info = new IPluginInfo;
                            pluginItem.translator =  NULL;

                            QTranslator *translator = new QTranslator(loader);
                            QString tsFile = file.mid(LIB_PREFIX_SIZE,file.lastIndexOf('.')-LIB_PREFIX_SIZE);
                            if (translator->load(tsFile,tsDir.absoluteFilePath(localeName)) || translator->load(tsFile,tsDir.absoluteFilePath(localeName.left(2))))
                            {
                                qApp->installTranslator(translator);
                                pluginItem.translator = translator;
                            }
                            else
                                delete translator;

                            plugin->pluginInfo(pluginItem.info);
                            savePluginInfo(file, pluginItem.info).setAttribute("uuid", uid.toString());

                            m_pluginItems.insert(uid,pluginItem);
                        }
                        else
                        {
                          error_module.append(file);
                          qInfo() << tr("Duplicate plugin uuid") << file << loader->errorString();
                            savePluginError(file, tr("Duplicate plugin uuid"));
                            delete loader;
                        }
                    }
                    else
                    {
                      error_module.append(file);
                      qInfo() << tr("Wrong plugin interface") << file << loader->errorString();
                        savePluginError(file, tr("Wrong plugin interface"));
                        delete loader;
                    }
                } else {
                  error_module.append(file);
                  qInfo() << tr("load error") << file << loader->errorString();
                  savePluginError(file, loader->errorString());
                  delete loader;
                  Q_ASSERT(false);
                }
            }

            if (!error_module.isEmpty()) {
              //BfEventTrack::GetInstance()->SendBSoftStartError(error_module);
              QString title = QString::fromUtf8("启动错误");
              QString message =
                  QString::fromUtf8("更新失败，请前往官网billfish.cn下载最新版本安装。");

              QMessageBox::critical(nullptr, title, message);

              quit();
              return;
            }
        }

        QHash<QUuid,PluginItem>::const_iterator it = m_pluginItems.constBegin();
        while (it!=m_pluginItems.constEnd())
        {
            QUuid puid = it.key();
            if (!checkDependences(puid))
            {
                unloadPlugin(puid, tr("Dependences not found"));
                it = m_pluginItems.constBegin();
            }
            else if (!checkConflicts(puid))
            {
                foreach(QUuid uid, getConflicts(puid)) {
                    unloadPlugin(uid, tr("Conflict with plugin %1").arg(puid.toString())); }
                it = m_pluginItems.constBegin();
            }
            else
            {
                ++it;
            }
        }
    }
    else
    {
        qDebug() << tr("Plugins directory not found");
        quit();
    }
}

bool PluginManager::initPlugins()
{
    bool initOk = true;
    QMultiMap<int,IPlugin *> pluginOrder;
    QHash<QUuid, PluginItem>::const_iterator it = m_pluginItems.constBegin();
    while (initOk && it!=m_pluginItems.constEnd())
    {
        int initOrder = PIO_DEFAULT;
        IPlugin *plugin = it.value().plugin;
        if (plugin->initConnections(this,initOrder))
        {
            pluginOrder.insertMulti(initOrder,plugin);
            ++it;
        }
        else
        {
            initOk = false;
            m_blockedPlugins.append(QFileInfo(it.value().loader->fileName()).fileName());
            unloadPlugin(it.key(), tr("Initialization failed"));
        }
    }

    if (initOk)
    {
        foreach(IPlugin *plugin, pluginOrder)
            plugin->initObjects();

        foreach(IPlugin *plugin, pluginOrder)
            plugin->initSettings();
    }


    return initOk;
}

void PluginManager::startPlugins() {
  qDebug() << "PluginManager::startPlugins()";
    foreach(PluginItem pluginItem, m_pluginItems)
    pluginItem.plugin->startPlugin();
}

void PluginManager::startShutdown()
{
    qInfo() << "PluginManager::startShutdown() start";
    m_shutdownTimer.start(DELAYED_QUIT_TIMEOUT);
    delayShutdown();
    emit shutdownStarted();
    //closeTopLevelWidgets();
#ifdef WIN32
    QApplication::closeAllWindows();
#endif
    continueShutdown();
    qInfo() << "PluginManager::startShutdown() end";
}

void PluginManager::finishShutdown()
{
    qInfo() << "PluginManager::finishShutdown";

    m_shutdownTimer.stop();
    if (m_shutdownKind == SK_RESTART)
    {
        onApplicationAboutToQuit();
        m_shutdownKind = SK_WORK;
        m_shutdownDelayCount = 0;

        loadSettings();
        loadPlugins();
        if (initPlugins())
        {
            saveSettings();
            //createMenuActions();
            //declareShortcuts();
            startPlugins();
            m_blockedPlugins.clear();
        }
        else
        {
            QTimer::singleShot(0,this,SLOT(restart()));
        }
    }
    else if (m_shutdownKind == SK_QUIT)
    {
        onApplicationAboutToQuit();
        QTimer::singleShot(100,qApp,SLOT(quit()));
    }

}

void PluginManager::closeTopLevelWidgets()
{
    foreach(QWidget *widget, QApplication::topLevelWidgets())
        widget->close();
}

void PluginManager::removePluginItem(const QUuid &AUuid, const QString &AError)
{
    if (m_pluginItems.contains(AUuid))
    {
        PluginItem pluginItem = m_pluginItems.take(AUuid);
        if (!AError.isEmpty())
        {
            savePluginError(QFileInfo(pluginItem.loader->fileName()).fileName(), AError);
        }
        if (pluginItem.translator)
        {
            qApp->removeTranslator(pluginItem.translator);
        }
        delete pluginItem.translator;
        delete pluginItem.info;
        delete pluginItem.loader;
    }
}

void PluginManager::unloadPlugin(const QUuid &AUuid, const QString &AError)
{
    if (m_pluginItems.contains(AUuid))
    {
        foreach(QUuid uid, pluginDependencesOn(AUuid))
            removePluginItem(uid, AError);
        removePluginItem(AUuid, AError);
        m_plugins.clear();
    }
}

bool PluginManager::checkDependences(const QUuid &AUuid) const
{
    if (m_pluginItems.contains(AUuid))
    {
        QList<QUuid> dependences = m_pluginItems.value(AUuid).info->dependences;
        foreach(QUuid depend, dependences)
        {
            if (!m_pluginItems.contains(depend))
            {
                bool found = false;
                QHash<QUuid,PluginItem>::const_iterator it = m_pluginItems.constBegin();
                while (!found && it!=m_pluginItems.constEnd())
                {
                    found = it.value().info->implements.contains(depend);
                    ++it;
                }
                if (!found)
                    return false;
            }
        }
    }
    return true;
}

bool PluginManager::checkConflicts(const QUuid AUuid) const
{
    if (m_pluginItems.contains(AUuid))
    {
        QList<QUuid> conflicts = m_pluginItems.value(AUuid).info->conflicts;
        foreach (QUuid conflict, conflicts)
        {
            if (!m_pluginItems.contains(conflict))
            {
                foreach(PluginItem pluginItem, m_pluginItems)
                    if (pluginItem.info->implements.contains(conflict))
                        return false;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

QList<QUuid> PluginManager::getConflicts(const QUuid &AUuid) const
{
    QSet<QUuid> plugins;
    if (m_pluginItems.contains(AUuid))
    {
        QList<QUuid> conflicts = m_pluginItems.value(AUuid).info->conflicts;
        foreach (QUuid conflict, conflicts)
        {
            QHash<QUuid,PluginItem>::const_iterator it = m_pluginItems.constBegin();
            while (it!=m_pluginItems.constEnd())
            {
                if (it.key()==conflict || it.value().info->implements.contains(conflict))
                    plugins+=conflict;
                ++it;
            }
        }
    }
    return plugins.toList();
}

void PluginManager::loadCoreTranslations(const QDir &ADir, const QString &ALocaleName)
{
    if (m_qtTranslator->load("qt_"+ALocaleName,ADir.absoluteFilePath(ALocaleName)) || m_qtTranslator->load("qt_"+ALocaleName,ADir.absoluteFilePath(ALocaleName.left(2))))
        qApp->installTranslator(m_qtTranslator);
    else if (m_qtTranslator->load("qt_"+QLocale().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        qApp->installTranslator(m_qtTranslator);

    if (m_loaderTranslator->load(APPLICATION_NAME,ADir.absoluteFilePath(ALocaleName)) || m_loaderTranslator->load(APPLICATION_NAME,ADir.absoluteFilePath(ALocaleName.left(2))))
        qApp->installTranslator(m_loaderTranslator);

    if (m_utilsTranslator->load("utils", ADir.absoluteFilePath(ALocaleName)) || m_utilsTranslator->load("utils",ADir.absoluteFilePath(ALocaleName.left(2))))
        qApp->installTranslator(m_utilsTranslator);
}

bool PluginManager::isPluginEnabled(const QString &AFile) const
{
    return !m_blockedPlugins.contains(AFile) && m_pluginsSetup.documentElement().firstChildElement(AFile).attribute("enabled","true") == "true";
}

QDomElement PluginManager::savePluginInfo(const QString &AFile, const IPluginInfo *AInfo)
{
    QDomElement pluginElem = m_pluginsSetup.documentElement().firstChildElement(AFile);
    if (pluginElem.isNull())
        pluginElem = m_pluginsSetup.firstChildElement("plugins").appendChild(m_pluginsSetup.createElement(AFile)).toElement();

    QDomElement nameElem = pluginElem.firstChildElement("name");
    if (nameElem.isNull())
    {
        nameElem = pluginElem.appendChild(m_pluginsSetup.createElement("name")).toElement();
        nameElem.appendChild(m_pluginsSetup.createTextNode(AInfo->name));
    }
    else
        nameElem.firstChild().toCharacterData().setData(AInfo->name);

    QDomElement descElem = pluginElem.firstChildElement("desc");
    if (descElem.isNull())
    {
        descElem = pluginElem.appendChild(m_pluginsSetup.createElement("desc")).toElement();
        descElem.appendChild(m_pluginsSetup.createTextNode(AInfo->description));
    }
    else
        descElem.firstChild().toCharacterData().setData(AInfo->description);

    QDomElement versionElem = pluginElem.firstChildElement("version");
    if (versionElem.isNull())
    {
        versionElem = pluginElem.appendChild(m_pluginsSetup.createElement("version")).toElement();
        versionElem.appendChild(m_pluginsSetup.createTextNode(AInfo->version));
    }
    else
        versionElem.firstChild().toCharacterData().setData(AInfo->version);

    QDomElement authorElem = pluginElem.firstChildElement("author");
    if (authorElem.isNull())
    {
        authorElem = pluginElem.appendChild(m_pluginsSetup.createElement("author")).toElement();
        authorElem.appendChild(m_pluginsSetup.createTextNode(AInfo->author));
    }
    else
        authorElem.firstChild().toCharacterData().setData(AInfo->author);

    pluginElem.removeChild(pluginElem.firstChildElement("depends"));
    if (!AInfo->dependences.isEmpty())
    {
        QDomElement dependsElem = pluginElem.appendChild(m_pluginsSetup.createElement("depends")).toElement();
        foreach(QUuid uid, AInfo->dependences)
            dependsElem.appendChild(m_pluginsSetup.createElement("uuid")).appendChild(m_pluginsSetup.createTextNode(uid.toString()));
    }

    pluginElem.removeChild(pluginElem.firstChildElement("error"));

    return pluginElem;
}

void PluginManager::savePluginError(const QString &AFile, const QString &AError)
{
    QDomElement pluginElem = m_pluginsSetup.documentElement().firstChildElement(AFile);
    if (pluginElem.isNull())
        pluginElem = m_pluginsSetup.firstChildElement("plugins").appendChild(m_pluginsSetup.createElement(AFile)).toElement();

    QDomElement errorElem = pluginElem.firstChildElement("error");
    if (AError.isEmpty())
    {
        pluginElem.removeChild(errorElem);
    }
    else if (errorElem.isNull())
    {
        errorElem = pluginElem.appendChild(m_pluginsSetup.createElement("error")).toElement();
        errorElem.appendChild(m_pluginsSetup.createTextNode(AError));
    }
    else
    {
        errorElem.firstChild().toCharacterData().setData(AError);
    }
}

void PluginManager::removePluginsInfo(const QStringList &ACurFiles)
{
    QDomElement pluginElem = m_pluginsSetup.documentElement().firstChildElement();
    while (!pluginElem.isNull())
    {
        if (!ACurFiles.contains(pluginElem.tagName()))
        {
            QDomElement oldElem = pluginElem;
            pluginElem = pluginElem.nextSiblingElement();
            oldElem.parentNode().removeChild(oldElem);
        }
        else
        {
            pluginElem = pluginElem.nextSiblingElement();
        }
    }
}
/*
void PluginManager::createMenuActions()
{
    IPlugin *plugin = pluginInterface("IMainDialogPlugin").value(0);
    IMainDialogPlugin *mainDialogPlugin = plugin!=NULL ? qobject_cast<IMainDialogPlugin *>(plugin->instance()) : NULL;

    if (mainDialogPlugin)
    {
        Action *aboutQt = new Action(mainWindowPlugin->mainWindow()->mainMenu());
        aboutQt->setText(tr("About Qt"));
        aboutQt->setIcon(RSR_STORAGE_MENUICONS,MNI_PLUGINMANAGER_ABOUT_QT);
        aboutQt->setShortcutId(SCT_APP_ABOUTQT);
        connect(aboutQt,SIGNAL(triggered()),QApplication::instance(),SLOT(aboutQt()));
        mainWindowPlugin->mainWindow()->mainMenu()->addAction(aboutQt,AG_MMENU_PLUGINMANAGER_ABOUT);

        Action *about = new Action(mainWindowPlugin->mainWindow()->mainMenu());
        about->setText(tr("About the program"));
        about->setIcon(RSR_STORAGE_MENUICONS,MNI_PLUGINMANAGER_ABOUT);
        about->setShortcutId(SCT_APP_ABOUTPROGRAM);
        connect(about,SIGNAL(triggered()),SLOT(onShowAboutBoxDialog()));
        mainWindowPlugin->mainWindow()->mainMenu()->addAction(about,AG_MMENU_PLUGINMANAGER_ABOUT);

        Action *pluginsDialog = new Action(mainWindowPlugin->mainWindow()->mainMenu());
        pluginsDialog->setText(tr("Setup plugins"));
        pluginsDialog->setIcon(RSR_STORAGE_MENUICONS, MNI_PLUGINMANAGER_SETUP);
        pluginsDialog->setShortcutId(SCT_APP_SETUPPLUGINS);
        connect(pluginsDialog,SIGNAL(triggered(bool)),SLOT(onShowSetupPluginsDialog(bool)));
        mainWindowPlugin->mainWindow()->mainMenu()->addAction(pluginsDialog,AG_MMENU_PLUGINMANAGER_SETUP,true);
    }
    else
    {
        onShowSetupPluginsDialog(false);
    }
}

void PluginManager::declareShortcuts()
{
    Shortcuts::declareGroup(SCTG_GLOBAL, tr("Global"), SGO_GLOBAL);

    Shortcuts::declareGroup(SCTG_APPLICATION, tr("Application"), SGO_APPLICATION);
    Shortcuts::declareShortcut(SCT_APP_ABOUTQT, tr("Show information about Qt"), QKeySequence::UnknownKey, Shortcuts::ApplicationShortcut);
    Shortcuts::declareShortcut(SCT_APP_ABOUTPROGRAM, tr("Show information about client"), QKeySequence::UnknownKey, Shortcuts::ApplicationShortcut);
    Shortcuts::declareShortcut(SCT_APP_SETUPPLUGINS, tr("Show setup plugins dialog"), QKeySequence::UnknownKey, Shortcuts::ApplicationShortcut);
}*/

void PluginManager::onApplicationAboutToQuit()
{
    qInfo() << "PluginManager::onApplicationAboutToQuit()";
    emit aboutToQuit();

    foreach(QUuid uid, m_pluginItems.keys())
        unloadPlugin(uid);

    QCoreApplication::removeTranslator(m_qtTranslator);
    QCoreApplication::removeTranslator(m_utilsTranslator);
    QCoreApplication::removeTranslator(m_loaderTranslator);
}

void PluginManager::onApplicationCommitDataRequested(QSessionManager &AManager)
{
#ifdef __APPLE__
    Q_UNUSED(AManager);
    m_shutdownKind = SK_QUIT;
    startShutdown();
    QDateTime stopTime = QDateTime::currentDateTime().addMSecs(DELAYED_COMMIT_TIMEOUT);
    while (stopTime>QDateTime::currentDateTime() && m_shutdownDelayCount>0)
        QApplication::processEvents();
    finishShutdown();
    qApp->quit();
#endif


#ifdef _WIN32
    qInfo() << "onApplicationCommitDataRequested";
    qInfo() << "MainApplication system shutdown onApplicationCommitDataRequested";
    m_isShuttingDown = true;

#endif



}
/*
void PluginManager::onShowSetupPluginsDialog(bool)
{
    if (m_pluginsDialog.isNull())
    {
        m_pluginsDialog = new SetupPluginsDialog(this,m_pluginsSetup,NULL);
        connect(m_pluginsDialog, SIGNAL(accepted()),SLOT(onSetupPluginsDialogAccepted()));
    }
    WidgetManager::showActivateRaiseWindow(m_pluginsDialog);
}

void PluginManager::onSetupPluginsDialogAccepted()
{
    saveSettings();
}


void PluginManager::onShowAboutBoxDialog()
{
    if (FAboutDialog.isNull())
        FAboutDialog = new AboutBox(this);
    WidgetManager::showActivateRaiseWindow(FAboutDialog);
}
*/

void PluginManager::onShutdownTimerTimeout()
{
    finishShutdown();
}

