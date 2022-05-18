#include "log.h"
#include <QCoreApplication>

Log4Qt::Logger* Utils::logger()
{
    ILoggerProvider* loggerProvider = qobject_cast<ILoggerProvider*>(qApp);
    if(loggerProvider)
        return loggerProvider->logger();
    return NULL;
}
