#ifndef NETWORKCHECKER_H
#define NETWORKCHECKER_H

#include <QThread>
#include <QStringList>
#include "utilsexport.h"
#include <QMutex>

class UTILS_EXPORT NetworkChecker : public QThread
{
    Q_OBJECT
public:
    explicit NetworkChecker(const QStringList& hosts,  QObject *parent = 0, int timeInterval = 500);
    ~NetworkChecker();

signals:

public slots:
    void stop();

protected:
    void run();

signals:
    void networkCheckSuccessed(QString host);
    void networkCheckFailed(QString host);

private:
    QStringList m_hosts;
    int m_timeInterval;
    bool m_bStop;
    QMutex m_mutex;
};

#endif // NETWORKCHECKER_H
