#ifndef LIBORSAASIFT_GLOBAL_H
#define LIBORSAASIFT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBORSAASIFT_LIBRARY)
#  define LIBORSAASIFTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBORSAASIFTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBORSAASIFT_GLOBAL_H