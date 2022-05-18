#ifndef CONSOLE_H
#define CONSOLE_H

#include "utilsexport.h"
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QDialog>
#include <QFile>


enum ConsoleLogLevel{
    ConsoleLogLevel_Debug = 0,
    ConsoleLogLevel_Info,
    ConsoleLogLevel_Warn,
    ConsoleLogLevel_Critical,
    ConsoleLogLevel_None
};

class ConsoleDialog;
class Console;

class IConsoleHolder{
public:
    virtual Console* console() = 0;
};

Q_DECLARE_INTERFACE(IConsoleHolder,"AUNBOX.IConsoleHolder/1.0")

class UTILS_EXPORT Logger
{
public:
    Logger();
    Logger(int level, Console* console);
    ~Logger();
    int level() const {return m_level;}
    QFile* logFile();

protected:

    QFile* newLogFile();

private:
    Console* m_console;
    int m_level;
    QFile* m_logFile;
};


Logger& UTILS_EXPORT consoleDebug();
Logger& UTILS_EXPORT consoleInfo();
Logger& UTILS_EXPORT consoleWarn();
Logger& UTILS_EXPORT consoleCritical();

class UTILS_EXPORT Console
{
public:
    Console();
    ~Console();
    static Console* globalConsole();
    void showConsoleDialog();
    static QString showConsoleDialogCmd() {return "##show console##";}
    ConsoleDialog* consoleDialog() {return m_consoleDialog;}
    Logger& logger(int level);
    static void debug(const QString& text);
    static void info(const QString& text);
    static void warn(const QString& text);
    static void critical(const QString& text);
    void append(int level, const QString& text);
    void init(const QString& configFile);
    static QString defaultLogFilePath();
    static QString levelString(int level);
    Console& operator<<(const char * s);

    static QString textToLog(int level, const QString &text);

    int minLogLevel() const {return m_minLogLevel;}
    QString logFilePath() const {return m_logFilePath;}
    qint64 logFileMaxSize() const {return m_logFileMaxSize;}
    int maxLogFileBak() const {return m_maxLogFileBak;}

private:
    ConsoleDialog* m_consoleDialog;
    int m_minLogLevel;
    QString m_logFilePath;
    qint64 m_logFileMaxSize;
    int m_maxLogFileBak;
    Logger m_debugLogger;
    Logger m_infoLogger;
    Logger m_warnLogger;
    Logger m_criticalLogger;
};


class UTILS_EXPORT ConsoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConsoleDialog(QWidget *parent = 0);
    ~ConsoleDialog();

    void append(const QString& text);

protected slots:
    void onClearClicked();

private:
   QVBoxLayout* m_mainLayout;
   QTextBrowser* m_textBrowser;
   QPushButton* m_clearButton;
};


#endif // CONSOLE_H
