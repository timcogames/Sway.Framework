#ifndef SWAY_PLATFORM_UNIX_GLX11_VISUALSUPPORT_H
#define SWAY_PLATFORM_UNIX_GLX11_VISUALSUPPORT_H

#include "glx11prereqs.h"
#include "visualattributes.h"
#include <boost/noncopyable.hpp> // boost::noncopyable

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class VisualSupport : private boost::noncopyable
{
public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	VisualSupport();

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	~VisualSupport();

	XVisualInfo chooseBestSuitable(void *display);

	GLXFBConfig getFBConfig(void *display, u32 visualId);

private:
	VisualAttributes _getMultisampleAttrs(::Display *display, XVisualInfo visual);
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_VISUALSUPPORT_H