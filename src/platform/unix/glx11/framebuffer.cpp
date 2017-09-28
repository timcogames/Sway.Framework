#include "framebuffer.h"

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
FrameBuffer::FrameBuffer()
	: _fbconfig(nullptr)
{
	// Empty
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
FrameBuffer::~FrameBuffer()
{
	// Empty
}

void FrameBuffer::chooseBestConfig(::Display *display)
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
	GLXFBConfig *nativeConfigs = glXChooseFBConfig(display, DefaultScreen(display), attrs, &numConfigs);
	if (NOT nativeConfigs)
		throw std::runtime_error("Failed to retrieve a framebuffer configurations.");

	printf("Found %d matching FB configs.\n", numConfigs);

	int best = -1, bestNumSamples = -1;
	for (int i = 0; i < numConfigs; ++i)
	{
		FrameBufferConfig config = getConfigAttrs(display, nativeConfigs[i]);

		if (best < 0 OR (config.numMultisample AND (config.numSamples > bestNumSamples)))
			best = i, bestNumSamples = config.numSamples;
	}

	_fbconfig = nativeConfigs[best];

	XFree(nativeConfigs);
}

XVisualInfo *FrameBuffer::getVisual(::Display *display)
{
	return glXGetVisualFromFBConfig(display, _fbconfig);
}

FrameBufferConfig FrameBuffer::getConfigAttrs(::Display *display, GLXFBConfig fbconfig)
{
	FrameBufferConfig config;
	memset(config, 0, sizeof(struct FrameBufferConfig));
	
	glXGetFBConfigAttrib(display, fbconfig, GLX_SAMPLE_BUFFERS, &config.sampleBuffers);
	glXGetFBConfigAttrib(display, fbconfig, GLX_SAMPLES, &config.samples);
	glXGetFBConfigAttrib(display, fbconfig, GLX_FBCONFIG_ID, &config.configId);
	glXGetFBConfigAttrib(display, fbconfig, GLX_VISUAL_ID, &config.visualId);
	glXGetFBConfigAttrib(display, fbconfig, GLX_X_VISUAL_TYPE, &config.visualType);
	glXGetFBConfigAttrib(display, fbconfig, GLX_BUFFER_SIZE, &config.bufferSize);
	glXGetFBConfigAttrib(display, fbconfig, GLX_LEVEL, &config.level);
	glXGetFBConfigAttrib(display, fbconfig, GLX_RENDER_TYPE, &config.renderType);
	glXGetFBConfigAttrib(display, fbconfig, GLX_DOUBLEBUFFER, &config.doubleBuffer);
	glXGetFBConfigAttrib(display, fbconfig, GLX_STEREO, &config.stereo);
	glXGetFBConfigAttrib(display, fbconfig, GLX_AUX_BUFFERS, &config.auxBuffers);
	glXGetFBConfigAttrib(display, fbconfig, GLX_RED_SIZE, &config.redSize);
	glXGetFBConfigAttrib(display, fbconfig, GLX_GREEN_SIZE, &config.greenSize);
	glXGetFBConfigAttrib(display, fbconfig, GLX_BLUE_SIZE, &config.blueSize);
	glXGetFBConfigAttrib(display, fbconfig, GLX_ALPHA_SIZE, &config.alphaSize);
	glXGetFBConfigAttrib(display, fbconfig, GLX_DEPTH_SIZE, &config.depthSize);
	glXGetFBConfigAttrib(display, fbconfig, GLX_STENCIL_SIZE, &config.stencilSize);
	glXGetFBConfigAttrib(display, fbconfig, GLX_SAMPLE_BUFFERS, &config.numMultisample);
	glXGetFBConfigAttrib(display, fbconfig, GLX_SAMPLES, &config.numSamples);

	return config;
}

void FrameBuffer::describeConfig(::Display *display, FrameBufferConfig config)
{
	printf("GLX choosen config ID: 0x%x Native Visual ID: 0x%x\n"
		"  Buffer: %d bits\n"
		"     Red: %d bits\n"
		"   Green: %d bits\n"
		"    Blue: %d bits\n"
		"   Alpha: %d bits\n"
		"   Depth: %d bits\n"
		" Stencil: %d bits\n",
		config.configId, config.visualId, 
		config.buffer, config.red, config.green, config.blue, config.alpha, config.depth, config.stencil);
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)