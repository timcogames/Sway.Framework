#include "surfacecontext.h"
#include "canvas.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cassert>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
SurfaceContext::SurfaceContext(Canvas *canvas, VisualSupport *support, s32 visualId)
{
	_internalData.xDisplay = static_cast<::Display *>(canvas->getXDisplay());
	_internalData.glxDrawable = static_cast<::Window>(canvas->getXWindow());
	_internalData.glxFBConfig = support->getFBConfig(_internalData.xDisplay, visualId);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
SurfaceContext::~SurfaceContext()
{
	// Empty
}

bool SurfaceContext::checkGLXExtension()
{
	int glxErrorBase, glxEventBase;
	if (NOT glXQueryExtension(_internalData.xDisplay, &glxErrorBase, &glxEventBase))
	{
		printf("X display does not support the GLX extension.");
		return false;
	}

	return true;
}

bool SurfaceContext::checkGLXVersion()
{
	int glxVersionMajor, glxVersionMinor;
	if (NOT glXQueryVersion(_internalData.xDisplay, &glxVersionMajor, &glxVersionMinor))
	{
		printf("Unable to retrieve GLX version.");
		return false;
	}

	return true;
}

/*!
 * \brief
 *   Создает контекст визуализации.
 */
void SurfaceContext::create()
{
	_internalData.glxContext = glXCreateNewContext(_internalData.xDisplay, _internalData.glxFBConfig, GLX_RGBA_TYPE, 0, True);
	if (NOT _internalData.glxContext)
		throw std::runtime_error("Unable to create GLX context.");

	if (NOT glXIsDirect(_internalData.xDisplay, _internalData.glxContext))
		printf("Unable to create direct rendering context.\n");
}

/*!
 * \brief
 *   Уничтожает контекст визуализации.
 */
void SurfaceContext::destroy()
{
	if (NOT doneCurrent())
		printf("Failed to deactivate shared context before sharing.\n");

	glXDestroyContext(_internalData.xDisplay, _internalData.glxContext);
}

/*!
 * \brief
 *   Прикрепляет контекст к окну.
 *
 * \sa
 *   SurfaceContext::doneCurrent()
 */
bool SurfaceContext::makeCurrent()
{
	if (glXGetCurrentContext() != _internalData.glxContext)
		return glXMakeCurrent(_internalData.xDisplay, _internalData.glxDrawable, _internalData.glxContext);

	return false;
}

/*!
 * \brief
 *   Освобождаем контекст.
 *
 * \sa
 *   SurfaceContext::makeCurrent()
 */
bool SurfaceContext::doneCurrent()
{
	return glXMakeCurrent(_internalData.xDisplay, None, NULL);
}

/*!
 * \brief
 *   Обмен буферов.
 */
void SurfaceContext::present()
{
	glXSwapBuffers(_internalData.xDisplay, _internalData.glxDrawable);
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)