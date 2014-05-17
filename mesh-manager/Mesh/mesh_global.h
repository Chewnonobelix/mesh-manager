#ifndef MESH_GLOBAL_H
#define MESH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MESH_LIBRARY)
#  define MESHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MESHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MESH_GLOBAL_H
