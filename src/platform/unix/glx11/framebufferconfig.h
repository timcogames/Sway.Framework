#ifndef SWAY_PLATFORM_UNIX_GLX11_FRAMEBUFFERCONFIG_H
#define SWAY_PLATFORM_UNIX_GLX11_FRAMEBUFFERCONFIG_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct FrameBufferConfig
{
	s32 configId;
	s32 visualId;
	s32 visualType;
	s32 bufferSize;
	s32 level;
	s32 renderType;
	s32 doubleBuffer;
	s32 stereo;
	s32 auxBuffers;
	
	//!@{
	// name colorbuffer
	s32 redSize;
	s32 greenSize;
	s32 blueSize;
	s32 alphaSize;
	//!@}

	//!@{
	s32 depthSize;
	s32 stencilSize;
	//!@}

	//!@{
	// name ms
	s32 numMultisample;
	s32 numSamples;
	//!@}
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_FRAMEBUFFERCONFIG_H