#ifndef LIBPW_GLOBAL_H
#define LIBPW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBPW_LIBRARY)
#  define LIBPWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBPWSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBPW_GLOBAL_H
