#include "mainapplication.h"

#include <QDir>
#include <QDebug>
#include <QTimer>
#include <QUuid>
#include <QThread>
#include <QJsonDocument>
#include <QProxyStyle>
#include <QSettings>
#include <QStyleOption>
#include <QScreen>
#include <QMetaEnum>
#include <QOperatingSystemVersion>
#include "utils/system_os.h"

#include "utils/console.h"

#include "tools.h"
#include "regexp.h"
#include "definitions/version.h"
#include "utils/system_os.h"
//#include "system_defines.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/fileappender.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/logmanager.h"
#include "log4qt/ttcclayout.h"
#include "utils/bfcrossplatformutils.h"
#include "bfcommon/bfcommon.h"
#include "bfcommon/APP_GLOBAL_CONSTANT.h"
#include <QDesktopServices>

#ifdef _WIN32
#include <QtWinExtras\QWinJumpList>
#include <ShlObj.h>
#include <windows.h>
#endif

#pragma execution_character_set("utf-8")

#ifdef Q_OS_MAC

#include <objc/objc.h>
#include <objc/message.h>


bool dockClickHandler(id self,SEL _cmd,...)
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    ((MainApplication*)qApp)->onClickOnDock();
    return true;
}

int quitFromDockMenuHandler(id self, SEL _cmd,...){
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    ((MainApplication*)qApp)->onMacDockQuit();
    return 0;
}

#endif

#ifdef Q_OS_WIN
class CustomStyle : public QProxyStyle
{
  void drawControl(ControlElement element, const QStyleOption* option,
                   QPainter* painter, const QWidget* widget) const {
    if (option && option->styleObject) {
      if ((element == QStyle::CE_RadioButton || element == QStyle::CE_CheckBox))
        option->styleObject->setProperty("_q_no_animation", true);
      QProxyStyle::drawControl(element, option, painter, widget);
    }
  }

};
#endif

static void STDCALL APP_CRASH_CALLBACK_IMPL(const char*) {
#ifdef __PROMOTE_CHANNEL_TRACKING__
  SERVER_SENSOR_ENABLE_COMMIT(true);  // 强制提交信息
#endif
#ifdef _WIN32
  QDesktopServices::openUrl(
      QUrl(QString("https://www.billfish.cn/soft-b01-qun")));
  FatalAppExit(-1, QString::fromUtf8("*** Billfish意外退出! 联系QQ群457778686 反馈此问题。 ***").toStdWString().c_str());
#endif
}

#ifdef _WIN32
static BOOL SetRegistryValue(HKEY hOpenKey, LPCTSTR szKey,
                                     LPCTSTR szValue, LPCTSTR szData) {
  // validate input
  if (!hOpenKey || !szKey || !szKey[0] || !szValue || !szData) {
    ::SetLastError(E_INVALIDARG);
    return FALSE;
  }

  BOOL bRetVal = FALSE;
  DWORD dwDisposition;
  DWORD dwReserved = 0;
  HKEY hTempKey = (HKEY)0;

  // length specifier is in bytes, and some TCHAR
  // are more than 1 byte each
  DWORD dwBufferLength = lstrlen(szData) * sizeof(TCHAR);

  // Open key of interest
  // Assume all access is okay and that all keys will be stored to file
  // Utilize the default security attributes
  if (ERROR_SUCCESS == ::RegCreateKeyEx(hOpenKey, szKey, dwReserved, (LPTSTR)0,
                                        REG_OPTION_NON_VOLATILE, KEY_SET_VALUE,
                                        0, &hTempKey, &dwDisposition)) {
    // dwBufferLength must include size of terminating nul
    // character when using REG_SZ with RegSetValueEx function
    dwBufferLength += sizeof(TCHAR);

    if (ERROR_SUCCESS == ::RegSetValueEx(hTempKey, (LPTSTR)szValue, dwReserved,
                                         REG_SZ, (LPBYTE)szData,
                                         dwBufferLength)) {
      bRetVal = TRUE;
    }
  }

  // close opened key
  if (hTempKey) {
    ::RegCloseKey(hTempKey);
  }

  return bRetVal;
}
#endif


#ifdef _WIN32

static BOOL RegeditYourFile(QString ExtName)

{
  QString csKey = ExtName;

  static TCHAR szProgPath[512] = {0};

  ::GetModuleFileName(
      NULL, szProgPath,
      sizeof(szProgPath) /
          sizeof(TCHAR));  //本执行程序的路径，用来在命令模式下也可以打开该

  //类型的文件

  QString csTempText;

  // just pass file path in quotes on command line

  csTempText = QString::fromWCharArray(szProgPath);

  csTempText += " %1";

  QString m_csDocumentDescription = "Billfish";

  static TCHAR csDocumentDescription[32] = {0};

  m_csDocumentDescription.toWCharArray(csDocumentDescription);

  csTempText = QString::fromWCharArray(szProgPath);

  csTempText += ",1";

  QString m_csDocumentDefaultIcon = csTempText;

  TCHAR emptyStr[16] = {0};

  QString strEmpty = QString("");
  strEmpty.toWCharArray(emptyStr);

  csKey = "Software\\Classes\\.BillfishPack";

  TCHAR csKeyArray[128] = {0};
  csKey.toWCharArray(csKeyArray);

  SetRegistryValue(HKEY_CURRENT_USER, csKeyArray, emptyStr,
                   csDocumentDescription);

  SetRegistryValue(HKEY_LOCAL_MACHINE, csKeyArray, emptyStr,
                   csDocumentDescription);

  // 注册默认图标

  // DefaultIcon

  static TCHAR csDocumentDefaultIcon[128] = {0};

  m_csDocumentDefaultIcon.toWCharArray(csDocumentDefaultIcon);

  if (!m_csDocumentDefaultIcon.isEmpty())

  {
    QString csIconKey = "Software\\Classes\\Billfish\\DefaultIcon";

    static TCHAR csIconArray[128] = {0};
    csIconKey.toWCharArray(csIconArray);

    SetRegistryValue(HKEY_CURRENT_USER, csIconArray, emptyStr,
                     csDocumentDefaultIcon);

    SetRegistryValue(HKEY_LOCAL_MACHINE, csIconArray, emptyStr,
                     csDocumentDefaultIcon);
  }

  SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST | SHCNF_FLUSHNOWAIT, 0, 0);

  return TRUE;
}


bool RegisterBillfishURI() {
  bool ret = false;

  HKEY h = HKEY_CURRENT_USER;
  LPCWSTR lpszRoot = L"Software\\Classes\\Billfish";

  LPCWSTR lpszName = L"Billfish";
  LPCWSTR lpszShell = L"shell\\open\\command\\";
  LPCWSTR lpszProtocol = L"Billfish URI Protocol";

  QString appPath = QApplication::applicationFilePath();
  appPath = appPath.replace("/", "\\");
  QString szPath = "\"" + appPath + "\" \"%1\"";
  std::wstring wszPath = szPath.toStdWString();

  // HKEY_CURRENT_USER\Software\Classes
  HKEY hRoot = 0;
  if (ERROR_SUCCESS == RegOpenKeyW(h, lpszRoot, &hRoot)) {
    wchar_t szText[1024];
    bool bNameOK = false, bPathOK = false;

    LONG lText = _countof(szText);
    if (ERROR_SUCCESS != RegQueryValueW(hRoot, 0, szText, &lText)) {
      if (ERROR_SUCCESS == RegSetValueW(hRoot, 0, REG_SZ, lpszName,
                                        wcslen(lpszName) * sizeof(wchar_t)))
        bNameOK = true;
      else {
        assert(0);
        QString u = QString::fromStdWString(lpszName);
        qInfo() << "Error: RegSetValue to " << u << " failed "
                << GetLastError();
      }
    } else if (QString::fromStdWString(szText) ==
               QString::fromStdWString(lpszName)) {
      bNameOK = true;
    } else if (ERROR_SUCCESS ==
               RegSetValueW(hRoot, 0, REG_SZ, lpszName,
                            wcslen(lpszName) * sizeof(wchar_t))) {
      bNameOK = true;
    } else {
      assert(0);
      QString u = QString::fromStdWString(lpszName);
      qInfo() << "Error: RegModifyValue to " << u << " failed "
              << GetLastError();
    }

    lText = _countof(szText);
    if (ERROR_SUCCESS != RegQueryValueW(hRoot, lpszShell, szText, &lText)) {
      if (ERROR_SUCCESS == RegSetValueW(hRoot, lpszShell, REG_SZ,
                                        wszPath.c_str(),
                                        wszPath.length() * sizeof(wchar_t)))
        bPathOK = true;
      else {
        assert(0);
        QString us = QString::fromStdWString(lpszShell);
        QString up = QString::fromStdWString(wszPath);
        qInfo() << "Error: RegSetValue " << us << ":" << up << " failed "
                << GetLastError();
      }
    } else if (QString::fromStdWString(szText) == QString::fromStdWString(wszPath)){
      bPathOK = true;
    } else if (ERROR_SUCCESS ==
               RegSetValueW(hRoot, lpszShell, REG_SZ, wszPath.c_str(),
                            wszPath.length() * sizeof(wchar_t))) {
      bPathOK = true;
    } else {
      assert(0);
      QString us = QString::fromStdWString(lpszShell);
      QString up = QString::fromStdWString(wszPath);
      qInfo() << "Error: RegModifyValue "<<us<<":"<<up<<" failed "<<GetLastError();
    }
    RegCloseKey(hRoot);

    ret = bPathOK;
  } else if (ERROR_SUCCESS != RegCreateKeyW(h, lpszRoot, &hRoot)) {
    qInfo() << "Error: Can not create register key for uri schema. "
            << GetLastError();
    assert(0);
  } else {
    if (0) {
    } else if (ERROR_SUCCESS !=
               RegSetValueW(hRoot, 0, REG_SZ, lpszName, wcslen(lpszName))) {
      qInfo()<<"Error: Can not set protocol name."<<GetLastError();
    } else if (ERROR_SUCCESS !=
               RegSetValueExW(hRoot, L"URL Protocol", 0, REG_SZ,
                              (LPBYTE)lpszProtocol,
                              wcslen(lpszProtocol) * sizeof(wchar_t))) {
      qInfo()<<"Error: Can not set uri protocol."<< GetLastError();
    } else if (ERROR_SUCCESS !=
               RegSetValueW(hRoot, lpszShell, REG_SZ, wszPath.c_str(),
                            wszPath.length() * sizeof(wchar_t))) {
      qInfo()<<"Error: Can not set uri shell open."<<GetLastError();
    } else {
      ret = true;
    }
    if (ERROR_SUCCESS != RegCloseKey(hRoot)) {
      assert(0);
    }
  }

  return ret;
}

#endif  // _WIN32

MainApplication::MainApplication(int &argc, char **argv) :
    QtSingleApplication("{5D1C4995-CFC4-4212-8358-E5B69581BEA1}",argc, argv)
{
    if(isRunning())
    {
        return;
    }
    setApplicationName(APPLICATION_NAME);
    setApplicationVersion(CLIENT_VERSION);
    setOrganizationDomain(ORGANIZATION_NAME);
    //messageReceived(const QString &message);
    connect(this,SIGNAL(messageReceived(QString)),this,SLOT(onMessageReceived(QString)));
#ifdef Q_OS_MAC
    m_macDockMenu = 0;
    m_macMenuBar = 0;

    // mac os x 10.13 崩溃
    Class cls = objc_getClass("NSApplication");
    objc_object *appInst = objc_msgSend((objc_object*)cls, sel_registerName("sharedApplication"));

    if(appInst != NULL)
    {
        objc_object* delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        Class delClass = (Class)objc_msgSend(delegate,  sel_registerName("class"));
        SEL closeHandle = sel_registerName("applicationShouldTerminate:");
        if (class_getInstanceMethod(delClass, closeHandle)) {
            if (class_replaceMethod(delClass, closeHandle, (IMP)quitFromDockMenuHandler, "B@:"))
                qDebug() << "Registered quit click handler (replaced original method)";
            else
                qWarning() << "Failed to replace method for quit click handler";
        }
        else {
            if (class_addMethod(delClass, closeHandle, (IMP)quitFromDockMenuHandler,"B@:"))
                qDebug() << "Registered quit click handler";
            else
                qWarning() << "Failed to register quit click handler";
        }
    }
#endif

#ifdef Q_OS_WIN
    setStyle(new CustomStyle);
#endif

    QDir resourcesDir(QApplication::applicationDirPath());
#if defined(Q_OS_MAC)
    if (resourcesDir.dirName() == "MacOS") {
        resourcesDir.cdUp();
    }
#endif
    resourcesDir.cd("Resources");

    Log4Qt::PropertyConfigurator::configure(resourcesDir.absolutePath() + "/log4qt.conf");
#ifdef QT_DEBUG
    Log4Qt::LogManager::setHandleQtMessages(false);
#else
    Log4Qt::LogManager::setHandleQtMessages(true);
#endif

    QList<Log4Qt::Appender*> appenders = Log4Qt::Logger::rootLogger()->appenders();
    for(int i=0; i<appenders.size(); i++)
    {
        Log4Qt::Appender* appender = appenders[i];
        Log4Qt::FileAppender* fileAppender = dynamic_cast<Log4Qt::FileAppender*>(appender);
        if(fileAppender)
        {
            QString homePath = GetHomePath();
            QDir dir(homePath);
            if (!dir.exists()) {
              dir.mkpath(homePath);
            }
            fileAppender->setFile(homePath + "/billfish_ui.log");
            fileAppender->activateOptions();
            break;
        }
    }

    qInfo(
        "----------------------------------- Start Application "
        "-----------------------------------");
    qInfo() << QString("APP Version : ") + BfCrossPlatformUtils::AppVersion();
    QScreen* screen = QGuiApplication::primaryScreen();
    if (screen) {
      qreal logicalDotsPerInch = screen->logicalDotsPerInch();
      qreal physicalDotsPerInch = screen->physicalDotsPerInch();
      double dpi = logicalDotsPerInch / 96;
      //QString info;

      qInfo() << "primaryScreen Size:" << screen->size()
               << "physicalDotsPerInch:" << physicalDotsPerInch
               << "logicalDotsPerInch:" << logicalDotsPerInch << "dpi:" << dpi;
    }

    setQuitOnLastWindowClosed(false);

    m_id = QUuid::createUuid().toString();
    connect(this, SIGNAL(aboutToQuit()), SLOT(onAboutToQuit()));

    m_pluginManager = NULL;
   // m_mainWidgetPlugin = NULL;
    newPluginManager();

    QString homePathQ = m_pluginManager->homePath() + "/";
    std::string homePath = homePathQ.toStdString();
#ifdef WIN32
#ifdef QT_DEBUG
    bfInitLogServer(homePath.c_str(), APP_ID, APP_KEY, SUPPORT_SERVER_HOST,
                    SERVER_PORT, SERVER_SLL_ENABLE, SERVER_API_VERSION,
                    BF_LOG_MID_VERSION_1_2, false, "Jnz.dll", "sa.aunload.com",
                    8106, "/sa?project=default");
#else
    bfInitLogServer(homePath.c_str(), APP_ID, APP_KEY, SUPPORT_SERVER_HOST,
                    SERVER_PORT, SERVER_SLL_ENABLE, SERVER_API_VERSION,
                    BF_LOG_MID_VERSION_1_2, false, "Jnz.dll", "sa.aunload.com",
                    8106, "/sa?project=production");
#endif

    ILogServer* pLogServer = GetLogServer();
    if (NULL != pLogServer) {
      pLogServer->SetCrashReportCallback(APP_CRASH_CALLBACK_IMPL);
    }
#else
#ifdef QT_DEBUG
    bfInitLogServer(homePath.c_str(), APP_ID, APP_KEY, SUPPORT_SERVER_HOST,
                    SERVER_PORT, SERVER_SLL_ENABLE, SERVER_API_VERSION,
                    BF_LOG_MID_VERSION_1_2, false, "Jnz.dylib", "sa.aunload.com",
                    8106, "/sa?project=default");
#else
    bfInitLogServer(homePath.c_str(), APP_ID, APP_KEY, SUPPORT_SERVER_HOST,
                    SERVER_PORT, SERVER_SLL_ENABLE, SERVER_API_VERSION,
                    BF_LOG_MID_VERSION_1_2, false, "Jnz.dylib", "sa.aunload.com",
                    8106, "/sa?project=production");
#endif
#endif



    m_pluginManager->start();
    

    //打印mid
    const char* mid = SERVER_MID;
    QString mid_info = QString("[MID] ").append((mid == NULL) ? "null" : mid);
    qInfo() << mid_info;
#ifdef WIN32
    //打印系统信息：操作体统版本和位数
    QSysInfo::WinVersion ver = QSysInfo::windowsVersion();
    QString strVer = QString::number(ver);
    if (ver == QSysInfo::WinVersion::WV_WINDOWS7) strVer == "win7";
    else if (ver == QSysInfo::WinVersion::WV_WINDOWS8)
      strVer == "win8";
    else if (ver == QSysInfo::WinVersion::WV_WINDOWS10)
      strVer == "win10";
    char buffer[512] = "unsupport";
#if defined(D_OS_WIN)
    int32_t bit = libCommonUtils::Is64BitWindows() ? 64 : 32;
    sprintf(buffer, "%s, %s, arch = %s, %dbit",
            libCommonUtils::winOSDisplayName().c_str(),  //系统展示名
            libCommonUtils::winOSVersion().c_str(),
            libCommonUtils::winOSArchitecture().c_str(),
            bit);  //架构
#endif
    qInfo(QString("[os_info] ").append(strVer.toUtf8()).append(" ").append(buffer).toUtf8());
    //打印cpu信息
    QSettings* CPU = new QSettings(
        "HKEY_LOCAL_"
        "MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
        QSettings::NativeFormat);
    QString cpu = CPU->value("ProcessorNameString").toString();
    delete CPU;
    qInfo(QString("[cpu]").append(cpu).toUtf8());
#else
    qInfo() << "System Version "<< QOperatingSystemVersion::current();
#endif
    //initPlugin();

#ifdef WIN32
    //RegisterBillfishURI();
    //RegeditYourFile("");
#endif
}

MainApplication::~MainApplication()
{
  bfReleaseLogserver();
  logger()->debug("----------------------------------- End Application -----------------------------------");
}

void MainApplication::setMainWidgetVisible(bool visible) {
  
  //插件内的主窗口插件设置显示和隐藏

  if (!m_mainWidgetPlugin) {
    IPlugin* plugin = NULL;
    if (m_pluginManager) {
      plugin =
          m_pluginManager->pluginInterface("IMainWidgetPlugin").value(0, NULL);
      if (plugin) {
        m_mainWidgetPlugin =
            qobject_cast<IMainWidgetPlugin*>(plugin->instance());
      }
    }
  }
  if (m_mainWidgetPlugin) {
    auto widget = m_mainWidgetPlugin->mainWidget()->instance();
    if (widget && visible) {
      widget->raise();
      widget->showNormal();
      widget->activateWindow();
    }
  }
}

#ifdef Q_OS_MAC
extern void qt_mac_set_dock_menu(QMenu* menu);

QMenu* MainApplication::macDockMenu()
{
    if (!m_macDockMenu) {
        m_macDockMenu = new QMenu(0);
#if (QT_VERSION >= 0x050200)
        qt_mac_set_dock_menu(m_macDockMenu);
#endif
    }
    return m_macDockMenu;
}

QMenuBar* MainApplication::macMenuBar()
{
    if(!m_macMenuBar){
        m_macMenuBar = new QMenuBar(0);
        //        QMenu* menuFile = new QMenu(tr("&Account"));
        //        menuFile->addAction(tr("Sign in other account"), this, SLOT(newPluginManager()))->setShortcut(QKeySequence("Ctrl+T"));
        //        m_macMenuBar->addMenu(menuFile);
    }
    return m_macMenuBar;
}

#endif

void MainApplication::initPlugin()
{
    if(m_pluginManager)
    {
        IPlugin *plugin = nullptr;
        plugin = m_pluginManager->pluginInterface("IMainWidgetPlugin").value(0,NULL);
        if (plugin)
        {
            //m_mainWidgetPlugin = qobject_cast<IMainWidgetPlugin *>(plugin->instance());
        }
    }
}

void MainApplication::newPluginManager()
{
    m_pluginManager = new PluginManager(this);
    connect(m_pluginManager, SIGNAL(aboutToQuit()), SLOT(onPluginManagerAboutToQuit()));
    connect(this, SIGNAL(shutdown()), m_pluginManager, SLOT(quit()));
    //qDebug() <<"Start new plugin manager: count=" << m_pluginManagers.count();
    m_pluginManager->loadSettings();
}

void MainApplication::onPluginManagerAboutToQuit()
{
    quit();
}

void MainApplication::onMessageReceived(QString msg) {
  if (msg == "raise_window_noop") {
    /*IPlugin* plugin = NULL;
    plugin =
        m_pluginManager->pluginInterface("IMainWidgetPlugin").value(0, NULL);
    if (plugin) {
      IMainWidgetPlugin* bfMainWidgetPlugin =
          qobject_cast<IMainWidgetPlugin*>(plugin->instance());
      if (bfMainWidgetPlugin) {
        auto widget = bfMainWidgetPlugin->mainWidget()->instance();

        widget->raise();
        widget->showNormal();
        widget->activateWindow();
      }
    }*/
  }
}

void MainApplication::onAboutToQuit()
{
#ifdef _WIN32

    if(m_pluginManager->isShutingDown()){
    qInfo() << "MainApplication isShutingDown";
        return;
    }

    qInfo() << "MainApplication system shutdown";

    IPlugin* plugin = NULL;
    plugin =
        m_pluginManager->pluginInterface("IMainWidgetPlugin").value(0, NULL);
    if (plugin) {
      //IMainWidgetPlugin* bfMainWidgetPlugin =
      //    qobject_cast<IMainWidgetPlugin*>(plugin->instance());
      //if (bfMainWidgetPlugin) {
      //  auto widget = bfMainWidgetPlugin->mainWidget();
      //  widget->DoMacDockQuit();
      //}
    }
#endif
}

Console* MainApplication::console()
{
    static Console* _console = NULL;
    if(_console == NULL)
    {
        _console = new Console();
    }
    return _console;
}


SkinManager* MainApplication::skinManager()
{
    static SkinManager* _sharedManager = NULL;
    if(_sharedManager == NULL)
    {
        _sharedManager = new SkinManager();
    }
    return _sharedManager;
}

Log4Qt::Logger* MainApplication::logger()
{
    return Log4Qt::Logger::rootLogger();
}

QString MainApplication::applicationName() const
{
    return APPLICATION_NAME;
}

QString MainApplication::applicationId() const
{
    return m_id;
}

void MainApplication::quitInstanceByManagerRequest()
{
    emit shutdown();
}

#ifdef Q_OS_MAC

void MainApplication::onClickOnDock()
{
    m_pluginManager->onDockIconClicked();
    //qDebug() << "on click on dock.";
}

void MainApplication::onMacDockQuit()
{
    IPlugin* plugin = NULL;
    plugin =
        m_pluginManager->pluginInterface("IMainWidgetPlugin").value(0, NULL);
    if (plugin) {
      IMainWidgetPlugin* bfMainWidgetPlugin =
          qobject_cast<IMainWidgetPlugin*>(plugin->instance());
      if (bfMainWidgetPlugin) {
        auto widget = bfMainWidgetPlugin->mainWidget();
        widget->DoMacDockQuit();
      }
    }
}

#endif


