#ifndef UTILS_EXPORT
#include <qglobal.h>
#ifndef UTILS_STATIC
#define UTILS_STATIC
#endif

#if !defined(UTILS_STATIC)
#    if defined(BUILD_UTILS)
#        define UTILS_EXPORT Q_DECL_EXPORT
#    else
#        define UTILS_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define UTILS_EXPORT
#endif

#endif //UTILSEXPORT_H
