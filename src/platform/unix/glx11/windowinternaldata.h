#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWINTERNALDATA_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWINTERNALDATA_H

#include "glx11prereqs.h"
#include "atoms.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowInternalData
{
	::Display *xDisplay;      /*!< Идентификатор сервера. */
	s32 xScreen;
	::Window xRoot;           /*!< Идентификатор корневого окна. */
	XVisualInfo xVisual;
	Colormap xColormap;
	::Window xWindow;         /*!< Идентификатор окна. */
	Atom xAtoms[kAtom_COUNT];
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWINTERNALDATA_H