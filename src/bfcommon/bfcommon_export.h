#ifndef BFCOMMON_EXPORT_H
#define BFCOMMON_EXPORT_H

#include <qglobal.h>
#if defined BUILD_COMMON_LIB
    #define COMMON_LIB_EXPORT Q_DECL_EXPORT
#else
    #define COMMON_LIB_EXPORT Q_DECL_IMPORT
#endif


#endif // BFCOMMON_EXPORT_H
