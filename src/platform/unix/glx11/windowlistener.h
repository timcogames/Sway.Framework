#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWLISTENER_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWLISTENER_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class WindowListener {
public:
	/*!
	 * \brief
	 *   Виртуальный деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~WindowListener() {
		// Empty
	}

	virtual void onCreate(const WindowEventCreate &) {
		// Empty
	}

	virtual void onResize(const WindowEventResize &) {
		// Empty
	}

	virtual void onRedraw(const WindowEventRedraw &) {
		// Empty
	}

	virtual void onGainFocus(const WindowEventGeneric &) {
		// Empty
	}

	virtual void onLostFocus(const WindowEventGeneric &) {
		// Empty
	}
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWLISTENER_H