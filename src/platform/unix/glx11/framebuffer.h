#ifndef SWAY_PLATFORM_UNIX_GLX11_FRAMEBUFFER_H
#define SWAY_PLATFORM_UNIX_GLX11_FRAMEBUFFER_H

#include "glx11prereqs.h"
#include "framebufferconfig.h"
#include <boost/noncopyable.hpp> // boost::noncopyable

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class FrameBuffer : private boost::noncopyable
{
  public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	FrameBuffer();

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	~FrameBuffer();

	void chooseBestConfig(::Display *display);

	XVisualInfo *getVisual(::Display *display);

	FrameBufferConfig getConfigAttrs(::Display *display, GLXFBConfig fbconfig);

	void describeConfig(::Display *display, FrameBufferConfig config);

private:
	GLXFBConfig _fbconfig;
	FrameBufferConfig _config;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_FRAMEBUFFER_H