#ifndef LSYSTEM_GLOBAL_H
#define LSYSTEM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LSYSTEM_LIBRARY)
#  define LSYSTEMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LSYSTEMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LSYSTEM_GLOBAL_H
