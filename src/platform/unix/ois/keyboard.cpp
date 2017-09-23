#include "inputmanager.h"
#include "keyboard.h"

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
Keyboard::Keyboard(InputManager *creator)
	: foundation::Object(creator), _display(NULL), _window(None)
{
	static_cast<InputManager *>(getContext())->_setKeyboardUsed(true);

	_initialize();
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
Keyboard::~Keyboard()
{
	if (_display)
	{
		if (_grab)
			XUngrabKeyboard(_display, CurrentTime);

		XCloseDisplay(_display);
	}

	static_cast<InputManager *>(getContext())->_setKeyboardUsed(false);
}

void Keyboard::_initialize()
{
	if (_display)
		XCloseDisplay(_display);
	_display = NULL;

	_window = static_cast<InputManager *>(getContext())->_getWindow();
	if (NOT(_display = XOpenDisplay(NULL)))
		return;

	XSelectInput(_display, _window, KeyPressMask | KeyReleaseMask | KeymapStateMask);

	if (_grab)
		XGrabKeyboard(_display, _window, True, GrabModeAsync, GrabModeAsync, CurrentTime);
}

void Keyboard::capture()
{
	KeySym keysym = NoSymbol;
	XEvent event = {};

	while (XPending(_display) > 0)
	{
		XNextEvent(_display, &event);

		if (event.type == KeyPress)
		{
			u8 buffer[6] = {0, 0, 0, 0, 0, 0};
			int len = XLookupString(&event.xkey, (lpstr)buffer, 6, &keysym, 0);
			if (len > 0)
				std::cout << "Key pressed: " << buffer << " - " << len << " - " << keysym << '\n';
		}
		else if (event.type == KeyRelease)
		{
			u8 buffer[6] = {0, 0, 0, 0, 0, 0};
			int len = XLookupString(&event.xkey, (lpstr)buffer, 6, &keysym, 0);
			if (len > 0)
				std::cout << "Key released: " << buffer << " - " << len << " - " << keysym << '\n';
		}
	}
}

NAMESPACE_END(ois)
NAMESPACE_END(sway)