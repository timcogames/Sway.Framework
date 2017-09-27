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

	_contextData.display = display;
	_contextData.window = window;
	
	_contextData.context = glXCreateNewContext(_contextData.display, _fbconfig, GLX_RGBA_TYPE, 0, True);
	if (NOT _contextData.context)
		throw std::runtime_error("Cannot create context.");

	if (NOT glXIsDirect(_contextData.display, _contextData.context))
		printf("Indirect GLX rendering context obtained.\n");
}

/*!
 * \brief Уничтожает контекст визуализации.
 */
void RenderContext::destroyContext()
{
	assert(_contextData.display);

	if (_contextData.context)
	{
		if (NOT doneCurrent())
		{
			// Empty
		}

		glXDestroyContext(_contextData.display, _contextData.context);
	}
}

/*!
 * \brief Прикрепляет контекст к окну.
 *
 * \sa RenderContext::doneCurrent()
 */
bool RenderContext::makeCurrent()
{
	assert(_contextData.display);
	assert(_contextData.window);

	if (glXGetCurrentContext() != _contextData.context)
		return glXMakeCurrent(_contextData.display, _contextData.window, _contextData.context);

	return false;
}

/*!
 * \brief Освобождаем контекст.
 *
 * \sa RenderContext::makeCurrent()
 */
bool RenderContext::doneCurrent()
{
	assert(_contextData.display);

	return glXMakeCurrent(_contextData.display, None, nullptr);
}

/*!
 * \brief Обмен буферов.
 */
void RenderContext::swapBuffers()
{
	assert(_contextData.display);
	assert(_contextData.window);

	glXSwapBuffers(_contextData.display, _contextData.window);
}

XVisualInfo *RenderContext::chooseBestFBConfig(::Display *display)
{
	assert(display);

	const int attributes[] = {
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
	GLXFBConfig *configs = glXChooseFBConfig(display, DefaultScreen(display), attributes, &numConfigs);
	if (NOT configs)
		throw std::runtime_error("Failed to retrieve a framebuffer configurations.");

	int best = -1, bestNumSamples = -1;
	for (int i = 0; i < numConfigs; ++i)
	{
		XVisualInfo *visualInfo = glXGetVisualFromFBConfig(display, configs[i]);
		if (visualInfo)
		{
			int sampleBuffers, samples;
			glXGetFBConfigAttrib(display, configs[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
			glXGetFBConfigAttrib(display, configs[i], GLX_SAMPLES, &samples);

			if (best < 0 OR (sampleBuffers AND(samples > bestNumSamples)))
				best = i, bestNumSamples = samples;
		}

		XFree(visualInfo);
	}

	_fbconfig = configs[best];

	XFree(configs);

	return glXGetVisualFromFBConfig(display, _fbconfig);
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)