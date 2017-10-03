#include "rendercontext.h"

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
RenderContext::RenderContext()
{
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
RenderContext::~RenderContext()
{
	// Empty
}

bool RenderContext::checkGLXExtension(::Display *display)
{
	int glxErrorBase, glxEventBase;
	if (NOT glXQueryExtension(display, &glxErrorBase, &glxEventBase))
	{
		printf("X display does not support the GLX extension.");
		return false;
	}

	return true;
}

bool RenderContext::checkGLXVersion(::Display *display)
{
	int glxVersionMajor, glxVersionMinor;
	if (NOT glXQueryVersion(display, &glxVersionMajor, &glxVersionMinor))
	{
		printf("Unable to retrieve GLX version.");
		return false;
	}

	return true;
}

/*!
 * \brief
 *   Создает контекст визуализации.
 *
 * \param window
 *   Идентификатор окна.
 */
void RenderContext::createContext(::Window window)
{
	assert(_internalData.xDisplay);
	assert(window);

	_internalData.glxDrawable = window;
	
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
void RenderContext::destroyContext()
{
	assert(_internalData.xDisplay);
	assert(_internalData.glxContext);

	if (NOT doneCurrent())
		printf("Failed to deactivate shared context before sharing.\n");

	glXDestroyContext(_internalData.xDisplay, _internalData.glxContext);
}

/*!
 * \brief
 *   Прикрепляет контекст к окну.
 *
 * \sa
 *   RenderContext::doneCurrent()
 */
bool RenderContext::makeCurrent()
{
	assert(_internalData.xDisplay);
	assert(_internalData.glxDrawable);
	assert(_internalData.glxContext);

	if (glXGetCurrentContext() != _internalData.glxContext)
		return glXMakeCurrent(_internalData.xDisplay, _internalData.glxDrawable, _internalData.glxContext);

	return false;
}

/*!
 * \brief
 *   Освобождаем контекст.
 *
 * \sa
 *   RenderContext::makeCurrent()
 */
bool RenderContext::doneCurrent()
{
	assert(_internalData.xDisplay);

	return glXMakeCurrent(_internalData.xDisplay, None, nullptr);
}

/*!
 * \brief
 *   Обмен буферов.
 */
void RenderContext::present()
{
	assert(_internalData.xDisplay);
	assert(_internalData.glxDrawable);

	glXSwapBuffers(_internalData.xDisplay, _internalData.glxDrawable);
}

XVisualInfo RenderContext::selectBestVisual(::Display* display)
{
	assert(display);

	_internalData.xDisplay = display;

	int numVisuals;
	XVisualInfo *visuals = XGetVisualInfo(_internalData.xDisplay, 0, nullptr, &numVisuals);
	if (visuals)
	{
		int bestScore = -1, bestNumSamples = -1;
		XVisualInfo bestVisual = XVisualInfo();

		for (int i = 0; i < numVisuals; ++i)
		{
			FrameBufferConfig config;
			glXGetConfig(display, &visuals[i], GLX_SAMPLE_BUFFERS_ARB, &config.numMultisample);
			glXGetConfig(display, &visuals[i], GLX_SAMPLES_ARB, &config.numSamples);

			if (bestScore < 0 OR (config.numMultisample AND (config.numSamples > bestNumSamples)))
				bestScore = i, bestNumSamples = config.numSamples;
		}

		bestVisual = visuals[bestScore];

		XFree(visuals);

		return bestVisual;
	}
	else
	{
		return XVisualInfo();
	}
}

void RenderContext::chooseBestFBConfig(::Display *display)
{
	assert(display);
	
	_internalData.xDisplay = display;

	const int attrs[] =
	{
		GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
		GLX_DOUBLEBUFFER,   True,
		GLX_RED_SIZE,       0,
		GLX_GREEN_SIZE,     0,
		GLX_BLUE_SIZE,      0,
		GLX_ALPHA_SIZE,     0,
		GLX_DEPTH_SIZE,     0,
		GLX_STENCIL_SIZE,   0,
		GLX_SAMPLE_BUFFERS, 0,
		GLX_SAMPLES,        0,
		None,               None
	};

	int numFBConfigs;
	GLXFBConfig *configs = glXChooseFBConfig(display, DefaultScreen(display), attrs, &numFBConfigs);
	if (NOT configs)
		throw std::runtime_error("Failed to retrieve a framebuffer configurations.");

	//bool foundFbConfig = false;
	int best = -1, bestNumSamples = -1;
	for (int i = 0; i < numFBConfigs; ++i)
	{
		FrameBufferConfig config;
		_getMultisampleVisualConfig(configs[i], &config);

		if (best < 0 OR (config.numMultisample AND (config.numSamples > bestNumSamples)))
			best = i, bestNumSamples = config.numSamples;

		//foundFbConfig = true;
	}

	_internalData.glxFBConfig = configs[best];

	XFree(configs);
}

void RenderContext::_getMultisampleVisualConfig(GLXFBConfig fbconfig, FrameBufferConfig *config)
{
	//multisample
	glXGetFBConfigAttrib(_internalData.xDisplay, fbconfig, GLX_SAMPLE_BUFFERS, &config->numMultisample);
	glXGetFBConfigAttrib(_internalData.xDisplay, fbconfig, GLX_SAMPLES, &config->numSamples);
}

XVisualInfo *RenderContext::getVisual()
{
	assert(_internalData.xDisplay);

	return glXGetVisualFromFBConfig(_internalData.xDisplay, _internalData.glxFBConfig);
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)