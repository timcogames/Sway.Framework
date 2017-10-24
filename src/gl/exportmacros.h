#ifndef SWAY_GL_EXPORTMACROS_H
#define SWAY_GL_EXPORTMACROS_H

#define DLL_EXPORT __attribute__((visibility("default")))
#define DLL_IMPORT
#if (__GNUC__ > 4) 
#	define DLL_LOCAL __attribute__((visibility("hidden")))
#else
#	define DLL_LOCAL
#endif

#ifdef LIBRARY_COMPILE
#   define LIBRARY_PUBLIC DLL_EXPORT
#	define LIBRARY_EXTERN
#else
#   define LIBRARY_PUBLIC DLL_IMPORT
#	define LIBRARY_EXTERN extern
#endif

#endif // SWAY_GL_EXPORTMACROS_H