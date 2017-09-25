#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWCONFIG_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWCONFIG_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowConfig
{
	lpcstr title;                    /*!< Заголовок окна. */
	math::TPoint<s32> position;      /*!< Позиция окна. */
	math::TSize<s32> size;           /*!< Размер окна. */
	math::TSizeHints<s32> sizeHints; /*!< Минимальный/максимальный размер окна. */
	bool resizable;                  /*!< Возможность изменения размера. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWCONFIG_H