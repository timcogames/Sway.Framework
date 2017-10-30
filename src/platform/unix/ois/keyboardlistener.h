#ifndef SWAY_PLATFORM_UNIX_OIS_KEYBOARDLISTENER_H
#define SWAY_PLATFORM_UNIX_OIS_KEYBOARDLISTENER_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

class KeyboardListener {
public:
	/*!
	 * \brief
	 *   Виртуальный деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~KeyboardListener() {
		// Empty
	}

	virtual void onKeyPressed(const InputEventKeyPress &) {
		// Empty
	}

	virtual void onKeyReleased(const InputEventKeyRelease &) {
		// Empty
	}
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_KEYBOARDLISTENER_H