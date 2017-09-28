#include "rendercontext.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cassert>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
RenderContext::RenderContext()
	: _fbconfig(nullptr)
{
	// Empty
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
RenderContext::~RenderContext()
{
	// Empty
}

/*!
 * \brief Создает контекст визуализации.
 *
 * \param display Идентификатор сервера.
 * \param window Идентификатор окна.
 */
void RenderContext::createContext(::Display *display, ::Window window)
{
	assert(display);
	assert(window);

	_internalData.display = display;
	_internalData.window = window;
	
	_internalData.context = glXCreateNewContext(_internalData.display, _fbconfig, GLX_RGBA_TYPE, 0, True);
	if (NOT _internalData.context)
		throw std::runtime_error("Cannot create context.");

	if (NOT glXIsDirect(_internalData.display, _internalData.context))
		printf("Indirect GLX rendering context obtained.\n");
}

/*!
 * \brief Уничтожает контекст визуализации.
 */
void RenderContext::destroyContext()
{
	assert(_internalData.display);

	if (_internalData.context)
	{
		if (NOT doneCurrent())
		{
			// Empty
		}

		glXDestroyContext(_internalData.display, _internalData.context);
	}
}

/*!
 * \brief Прикрепляет контекст к окну.
 *
 * \sa RenderContext::doneCurrent()
 */
bool RenderContext::makeCurrent()
{
	assert(_internalData.display);
	assert(_internalData.window);

	if (glXGetCurrentContext() != _internalData.context)
		return glXMakeCurrent(_internalData.display, _internalData.window, _internalData.context);

	return false;
}

/*!
 * \brief Освобождаем контекст.
 *
 * \sa RenderContext::makeCurrent()
 */
bool RenderContext::doneCurrent()
{
	assert(_internalData.display);

	return glXMakeCurrent(_internalData.display, None, nullptr);
}

/*!
 * \brief Обмен буферов.
 */
void RenderContext::swap()
{
	assert(_internalData.display);
	assert(_internalData.window);

	glXSwapBuffers(_internalData.display, _internalData.window);
}

XVisualInfo *RenderContext::chooseBestFBConfig(::Display *display)
{
	assert(display);

	const int attrs[] = {
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_DOUBLEBUFFER, True,
		GLX_RED_SIZE, 0,
		GLX_GREEN_SIZE, 0,
		GLX_BLUE_SIZE, 0,
		GLX_ALPHA_SIZE, 0,
		GLX_DEPTH_SIZE, 0,
		GLX_STENCIL_SIZE, 0,
		GLX_SAMPLE_BUFFERS, 0,
		GLX_SAMPLES, 0,
		None, None};

	int numConfigs;
	//GLXFBConfig *configs = glXGetFBConfigs(display, DefaultScreen(display), &numConfigs);
	GLXFBConfig *configs = glXChooseFBConfig(display, DefaultScreen(display), attrs, &numConfigs);
	if (NOT configs)
		throw std::runtime_error("Failed to retrieve a framebuffer configurations.");

	int best = -1, bestNumSamples = -1;
	for (int i = 0; i < numConfigs; ++i)
	{
		int numMultisample, numSamples;
		glXGetFBConfigAttrib(display, configs[i], GLX_SAMPLE_BUFFERS, &numMultisample);
		glXGetFBConfigAttrib(display, configs[i], GLX_SAMPLES, &numSamples);

		if (best < 0 OR (numMultisample AND (numSamples > bestNumSamples)))
			best = i, bestNumSamples = numSamples;
	}

	_fbconfig = configs[best];

	XFree(configs);

	return glXGetVisualFromFBConfig(display, _fbconfig);
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)