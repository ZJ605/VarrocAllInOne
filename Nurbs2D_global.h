#ifndef NURBS2D_GLOBAL_H
#define NURBS2D_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NURBS2D_LIBRARY)
#  define NURBS2D_EXPORT Q_DECL_EXPORT
#else
#  define NURBS2D_EXPORT Q_DECL_IMPORT
#endif

#endif // NURBS2D_GLOBAL_H
