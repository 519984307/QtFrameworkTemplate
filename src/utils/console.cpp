#include "console.h"
#include <QLabel>
#include <QDateTime>
#include <QApplication>
#include <QDir>
#include <QJsonDocument>
#include <QProcess>
#include <QDebug>
#include <QPushButton>

#include "widgetmanager.h"
#include "definitions/version.h"

#define LOG_DIR "log"
#define DEFUALT_MAX_LOG_FILE_SIZE   (1 << 22)   //4M
#define DEFUALT_MAX_LOG_FILE_BAK    5


#if defined(Q_OS_WIN)
#  define ENV_APP_DATA              "APPDATA"
#  define PATH_APP_DATA             ORGANIZATION_NAME"/"
#elif defined(Q_OS_MAC)
#  define ENV_APP_DATA              "HOME"
#  define PATH_APP_DATA             "Library/Application Support/"
#endif

Logger::Logger()
{
    m_level = ConsoleLogLevel_None;
    m_console = NULL;
    m_logFile = NULL;
}

Logger::Logger(int level, Console *console)
{
    m_level = level;
    m_console = console;
    m_logFile = NULL;
}

Logger::~Logger()
{
    if(m_logFile)
    {
        if(m_logFile->isOpen())
        {
            m_logFile->flush();
            m_logFile->close();
        }
        delete m_logFile;
        m_logFile = NULL;
    }
}


QFile* Logger::logFile()
{
    if(!m_console)
        return NULL;
    if(m_logFile)
    {
        if(m_logFile->size() < m_console->logFileMaxSize())
            return m_logFile;
        m_logFile->flush();
        m_logFile->close();
        delete m_logFile;
    }
    m_logFile = newLogFile();
    return m_logFile;
}

QFile* Logger::newLogFile()
{
    if(!m_console)
        return NULL;
    QDir dir(m_console->logFilePath());
    if(dir.exists())
    {
        QString filename = "roll";
        switch (m_level) {
        case ConsoleLogLevel_Debug:
            filename = "debug";
            break;
        case ConsoleLogLevel_Info:
            filename = "info";
            break;
        case ConsoleLogLevel_Warn:
            filename = "warn";
            break;
        case ConsoleLogLevel_Critical:
            filename = "critial";
            break;
        default:
            filename = "roll";
            break;
        }
        QString newFileName = QString("%1/%2.log").arg(dir.absolutePath()).arg(filename);
        if(!QFile::exists(newFileName))
        {
            QFile *file = new QFile(newFileName);
            if(file->open(QFile::WriteOnly | QFile::Append))
            {
                return file;
            }
        }
        else
        {
            QFile *file = new QFile(newFileName);
            if(file->open(QFile::WriteOnly | QFile::Append))
            {
                if(file->size() < m_console->logFileMaxSize())
                    return file;
                file->close();
            }

            for(int i = m_console->maxLogFileBak()-1; i>=0; i--)
            {
                QString nextFileName = QString("%1/%2%3.log").arg(dir.absolutePath()).arg(filename).arg(i+1);
                if(QFile::exists(nextFileName))
                {
                    QFile::remove(nextFileName);
                }
                QString currentFileName = QString("%1/%2%3.log").arg(dir.absolutePath()).arg(filename).arg(i);
                if(i == 0)
                {
                    currentFileName = newFileName;
                }
                if(QFile::exists(currentFileName))
                {
                    QFile::rename(currentFileName, nextFileName);
                }
            }
            file->setFileName(newFileName);
            if(file->open(QFile::WriteOnly | QFile::Append))
            {
                return file;
            }
        }
    }
    return NULL;
}

Console::Console() :
    m_debugLogger(ConsoleLogLevel_Debug, this),
    m_infoLogger(ConsoleLogLevel_Info, this),
    m_warnLogger(ConsoleLogLevel_Warn, this),
    m_criticalLogger(ConsoleLogLevel_Critical, this)
{
    m_consoleDialog = NULL;
    m_minLogLevel = ConsoleLogLevel_Debug;
    m_logFileMaxSize = DEFUALT_MAX_LOG_FILE_SIZE;
    m_logFilePath = defaultLogFilePath();
    m_maxLogFileBak = DEFUALT_MAX_LOG_FILE_BAK;
}

Console::~Console()
{
    if(m_consoleDialog)
    {
        m_consoleDialog->close();
        m_consoleDialog->deleteLater();
    }
}

Console* Console::globalConsole()
{
    IConsoleHolder* consoleHolder = qobject_cast<IConsoleHolder*>(qApp);
    if(consoleHolder)
    {
        return consoleHolder->console();
    }
    else
    {
        static Console* _console = NULL;
        if(_console == NULL)
        {
            _console = new Console();
        }
        return _console;
    }
}

void Console::showConsoleDialog()
{
    if(m_consoleDialog == NULL)
    {
        m_consoleDialog = new ConsoleDialog();
    }
    WidgetManager::showActivateRaiseWindow(m_consoleDialog);
}

Logger& Console::logger(int level)
{
    switch (level) {
    case ConsoleLogLevel_Debug:
        return m_debugLogger;
        break;
    case ConsoleLogLevel_Info:
        return m_infoLogger;
        break;
    case ConsoleLogLevel_Warn:
        return m_warnLogger;
        break;
    case ConsoleLogLevel_Critical:
        return m_criticalLogger;
        break;
    default:
        break;
    }
    static Logger tempLogger = Logger();
    return tempLogger;
}

void Console::debug(const QString &text)
{
    globalConsole()->append(ConsoleLogLevel_Debug, text);
}

void Console::info(const QString &text)
{
    globalConsole()->append(ConsoleLogLevel_Info, text);
}


void Console::warn(const QString &text)
{
    globalConsole()->append(ConsoleLogLevel_Warn, text);
}


void Console::critical(const QString &text)
{
    globalConsole()->append(ConsoleLogLevel_Critical, text);
}

QString Console::textToLog(int level, const QString &text)
{
    if(level < 0 || level > ConsoleLogLevel_None)
        return QString();
    QString logInfo = levelString(level);
    logInfo += " ";
    logInfo += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz");

    logInfo += " ";
    logInfo += text;
    return logInfo;
}

void Console::append(int level, const QString &text)
{
    QString log = textToLog(level, text);
    if(m_consoleDialog && m_consoleDialog->isVisible())
    {
        m_consoleDialog->append(log);
    }
    if(level >= m_minLogLevel)
    {
//        QFile *file = logger(level).logFile();
//        if(file && file->isOpen())
//        {
//            file->write(log.toUtf8());
//            file->write(QString("\r\n").toUtf8());
//            file->flush();
//        }
    }
}

QString Console::defaultLogFilePath()
{
    QString pathAppData = PATH_APP_DATA;
    pathAppData += qApp->applicationName();
    QString path = QString();
    if (path.isNull())
    {
        foreach(QString env, QProcess::systemEnvironment())
        {
            if (env.startsWith(ENV_APP_DATA"="))
            {
                QDir dir(env.split("=").value(1));
                if (dir.exists() && (dir.exists(pathAppData) || dir.mkpath(pathAppData)) && dir.cd(pathAppData))
                    path = dir.absolutePath();
            }
        }
    }
    if (path.isNull())
    {
        QDir dir(QDir::homePath());
        if (dir.exists() && (dir.exists(qApp->applicationName()) || dir.mkpath(qApp->applicationName())) && dir.cd(qApp->applicationName()))
            path = dir.absolutePath();
    }
    if(!path.isNull())
    {
        QDir dir(path);
        if((dir.exists(LOG_DIR) || dir.mkpath(LOG_DIR)) && dir.cd(LOG_DIR))
            return dir.absolutePath();
    }
    return QString();
}

void Console::init(const QString &configFile)
{
    if(QFile::exists(configFile))
    {
        QFile file(configFile);
        if(file.open(QFile::ReadOnly))
        {
            QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
            file.close();
            if(!jsonDoc.isNull())
            {
                QVariant v = jsonDoc.toVariant();
                if(v.type() == QVariant::Map)
                {
                    QVariantMap jsonMap = qvariant_cast<QVariantMap>(v);
                    QString minLevelStr = jsonMap.value("level", "DEBUG").toString();
                    minLevelStr = minLevelStr.toUpper();
                    if(minLevelStr == "DEBUG")
                        m_minLogLevel = ConsoleLogLevel_Debug;
                    else if(minLevelStr == "INFO")
                        m_minLogLevel = ConsoleLogLevel_Info;
                    else if(minLevelStr == "WARN")
                        m_minLogLevel = ConsoleLogLevel_Warn;
                    else if(minLevelStr == "CRITICAL")
                        m_minLogLevel = ConsoleLogLevel_Critical;
                    else
                        m_minLogLevel = ConsoleLogLevel_None;
                    m_logFileMaxSize = jsonMap.value("max-file-size", DEFUALT_MAX_LOG_FILE_SIZE).toLongLong();
                    m_logFilePath = jsonMap.value("log-file-path", defaultLogFilePath()).toString();
                    m_maxLogFileBak = jsonMap.value("max-log-file-bak", DEFUALT_MAX_LOG_FILE_BAK).toInt();
                }
            }

        }

    }
}


QString Console::levelString(int level)
{
    QString str;
    switch (level) {
    case ConsoleLogLevel_Debug:
        str = "[DBG]";
        break;
    case ConsoleLogLevel_Info:
        str = "[INFO]";
        break;
    case ConsoleLogLevel_Warn:
        str = "[WARN]";
        break;
    case ConsoleLogLevel_Critical:
        str = "[CRT]";
        break;
    default:
        str = "[NOLEVEL]";
        break;
    }
    return str;
}

ConsoleDialog::ConsoleDialog(QWidget *parent) :
    QDialog(parent)
{
    setObjectName("console-dialog");
    setAttribute(Qt::WA_DeleteOnClose, false);
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_textBrowser = new QTextBrowser(this);
    m_mainLayout->addWidget(m_textBrowser, 1);

    m_clearButton = new QPushButton("clear", this);
    connect(m_clearButton, SIGNAL(clicked()), SLOT(onClearClicked()));
    m_mainLayout->addWidget(m_clearButton, 0);


    resize(QSize(960,600));
}


ConsoleDialog::~ConsoleDialog()
{

}

void ConsoleDialog::onClearClicked()
{
    m_textBrowser->clear();
}

void ConsoleDialog::append(const QString& text)
{
    m_textBrowser->append(text);
}


