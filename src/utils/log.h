#ifndef LOG_H
#define LOG_H

#include "utilsexport.h"
#include <log4qt/logger.h>

class ILoggerProvider{
public:
    virtual Log4Qt::Logger* logger() = 0;
};

Q_DECLARE_INTERFACE(ILoggerProvider,"Utils.ILoggerProvider/1.0")

namespace Utils {
Log4Qt::Logger* UTILS_EXPORT logger();

}


#endif //LOG_H
