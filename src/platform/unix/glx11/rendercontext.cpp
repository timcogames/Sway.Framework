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
	: _context(nullptr), _fbconfig(nullptr)
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
 */
void RenderContext::createContext(::Display *display)
{
	assert(display);
	
	_context = glXCreateNewContext(display, _fbconfig, GLX_RGBA_TYPE, 0, True);
	if (NOT _context)
		throw std::runtime_error("Cannot create context.");

	if (NOT glXIsDirect(display, _context))
		printf("Indirect GLX rendering context obtained.\n");
}

/*!
 * \brief Уничтожает контекст визуализации.
 *
 * \param display Идентификатор сервера.
 */
void RenderContext::destroyContext(::Display *display)
{
	assert(display);

	if (_context)
	{
		if (NOT releaseCurrent(display))
		{
			// Empty
		}

		glXDestroyContext(display, _context);
	}
}

/*!
 * \brief Прикрепляет контекст к окну.
 *
 * \param display Идентификатор сервера.
 * \param window Идентификатор окна.
 *
 * \sa RenderContext::releaseCurrent(::Display *)
 */
bool RenderContext::makeCurrent(::Display *display, ::Window window)
{
	assert(display);
	assert(window);

	if (glXGetCurrentContext() != _context)
		return glXMakeCurrent(display, window, _context);

	return false;
}

/*!
 * \brief Освобождаем контекст.
 *
 * \param display Идентификатор сервера.
 *
 * \sa RenderContext::makeCurrent(::Display *, ::Window)
 */
bool RenderContext::releaseCurrent(::Display *display)
{
	assert(display);

	return glXMakeCurrent(display, None, nullptr);
}

/*!
 * \brief Обмен буферов.
 *
 * \param display Идентификатор сервера.
 * \param window Идентификатор окна.
 */
void RenderContext::swapBuffers(::Display *display, ::Window window)
{
	assert(display);
	assert(window);

	glXSwapBuffers(display, window);
}

XVisualInfo *RenderContext::chooseBestFBConfig(::Display* display)
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

			if (best < 0 OR(sampleBuffers AND(samples > bestNumSamples)))
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