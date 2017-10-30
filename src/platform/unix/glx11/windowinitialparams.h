#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWINITIALPARAMS_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWINITIALPARAMS_H

#include "glx11prereqs.h"
#include "windowsizes.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowInitialParams {
	lpcstr title;                              /*!< Заголовок окна. */
	math::TPoint<s32> position;                /*!< Позиция окна. */
	math::TSize<s32> sizes[kWindowSize_COUNT]; /*!< Размеры окна. */
	bool resizable;                            /*!< Возможность изменения размера. */
	bool fullscreen;                           /*!< Полноэкранный/оконный режим. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWINITIALPARAMS_H