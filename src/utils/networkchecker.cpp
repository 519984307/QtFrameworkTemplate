#include "networkchecker.h"
#include <QProcess>
#include <QDebug>

NetworkChecker::NetworkChecker(const QStringList &hosts, QObject *parent, int timeInterval) :
    QThread(parent)
{
    m_hosts = hosts;
    m_timeInterval = timeInterval;
}

NetworkChecker::~NetworkChecker()
{
    m_bStop = true;
    wait();
}

void NetworkChecker::run()
{
    m_bStop = false;
    int count = 0;
    while(!m_bStop)
    {
        QString host;
        foreach( host, m_hosts )
        {
            int exitCode;

            //qDebug() << "ping " + host << endl;
#ifdef Q_OS_WIN
            //QString strArg = "ping " + host + " -n 1 -i 2";
            QString strArg = "ping " + host + " -n 1";
            exitCode = QProcess::execute(strArg);
#else
            //其他平台(Linux或Mac)
            exitCode = QProcess::execute("ping",  QStringList() << "-c 1" << "-t 2" << host);
#endif

            if(0 == exitCode)
            {
                //it's alive
                //qDebug() << "shell ping " + host + " sucessed!";
                //发射该IP在线的信号
                count = 0;
                emit networkCheckSuccessed(host);
            } else {
                //qDebug() << "shell ping " + host + " failed!";
                //发射IP离线的信号
                count++;
                if(count > 10)
                    emit networkCheckFailed(host);
            }
        }
        msleep(m_timeInterval);
    }
}

void NetworkChecker::stop()
{
    m_mutex.lock();
    m_bStop = true;
    m_mutex.unlock();
}
