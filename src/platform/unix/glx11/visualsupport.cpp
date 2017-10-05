#include "visualsupport.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cassert>
#include <stdio.h> // memset

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
VisualSupport::VisualSupport()
{
	// Empty
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
VisualSupport::~VisualSupport()
{
	// Empty
}

XVisualInfo VisualSupport::chooseBestSuitable(void *display)
{
	int numVisuals;
	XVisualInfo *visuals = XGetVisualInfo(static_cast<::Display *>(display), 0, NULL, &numVisuals);

	printf("Found %d matching visual configs.\n", numVisuals);

	if (visuals AND (numVisuals > 0))
	{
		int bestScore = -1, bestNumSamples = -1;
		XVisualInfo bestVisual = XVisualInfo();

		for (int i = 0; i < numVisuals; ++i)
		{
			VisualAttributes attrs = _getMultisampleAttrs(static_cast<::Display *>(display), visuals[i]);
			
			if (bestScore < 0 OR (attrs.numMultisample AND (attrs.numSamples > bestNumSamples)))
				bestScore = i, bestNumSamples = attrs.numSamples;
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

VisualAttributes VisualSupport::_getMultisampleAttrs(::Display *display, XVisualInfo visual)
{
	lpcstr extensions = glXQueryExtensionsString(display, visual.screen);
	VisualAttributes attrs;

	if (extensions AND strstr(extensions, "GLX_ARB_multisample")) {
		glXGetConfig(display, &visual, GLX_SAMPLE_BUFFERS_ARB, &attrs.numMultisample);
		glXGetConfig(display, &visual, GLX_SAMPLES_ARB, &attrs.numSamples);
	}
	else {
		attrs.numMultisample = 0;
		attrs.numSamples = 0;
	}

	return attrs;
}

GLXFBConfig VisualSupport::getFBConfig(void *display, u32 visualId)
{
	const int attrs[] = {None};

	int xScreen = XDefaultScreen(static_cast<::Display *>(display));
	int numConfigs;

	GLXFBConfig *configs = glXChooseFBConfig(static_cast<::Display *>(display), xScreen, attrs, &numConfigs);
	if (NOT configs)
		throw std::runtime_error("Failed to retrieve a VisualSupport configurations.");

	GLXFBConfig fbconfig = 0;
	for (int i = 0; i < numConfigs; ++i)
	{
		XVisualInfo *visual = glXGetVisualFromFBConfig(static_cast<::Display *>(display), configs[i]);
		if (visual->visualid == visualId)
		{
			fbconfig = configs[i];

			XFree(visual);
			break;
		}

		XFree(visual);
	}

	return fbconfig;
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)