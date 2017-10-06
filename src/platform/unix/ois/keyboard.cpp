#include "keyboard.h"
#include "keyboardlistener.h"
#include "keyboardevents.h"
#include "keycodes.h"
#include "keymappinglist.h"
#include "inputmanager.h"

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
Keyboard::Keyboard(InputManager *creator)
	: foundation::Object(creator), _display(NULL), _window(None)
{
	static_cast<InputManager *>(getContext())->setKeyboardUsed(true);

	_initialize();
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
Keyboard::~Keyboard()
{
	if (_display)
	{
		if (_grab)
			XUngrabKeyboard(_display, CurrentTime);

		XCloseDisplay(_display);
	}

	static_cast<InputManager *>(getContext())->setKeyboardUsed(false);
}

/*!
 * \fn
 *   void Keyboard::_initialize()
 * 
 * \brief
 *   Инициализация устройства.
 *
 * \note
 *   Внутренний метод, вызывается в конструкторе.
 */
void Keyboard::_initialize()
{
	if (_display)
		XCloseDisplay(_display);
	_display = NULL;

	_window = static_cast<InputManager *>(getContext())->getWindow();
	if (NOT(_display = XOpenDisplay(NULL)))
		return;

	XSelectInput(_display, _window, KeyPressMask | KeyReleaseMask | KeymapStateMask);

	if (_grab)
		XGrabKeyboard(_display, _window, True, GrabModeAsync, GrabModeAsync, CurrentTime);
}

void Keyboard::connect(KeyboardListener *listener)
{
	onKeyPressed = boost::bind(&KeyboardListener::onKeyPressed, listener, _1);
	onKeyReleased = boost::bind(&KeyboardListener::onKeyReleased, listener, _1);
}

void Keyboard::capture()
{
	XEvent event = {};

	while (XPending(_display) > 0)
	{
		XNextEvent(_display, &event);

		if (event.type == KeyPress AND onKeyPressed)
			_injectKeyDown(event);
		else if (event.type == KeyRelease AND onKeyReleased)
			_injectKeyUp(event);
	}
}

void Keyboard::_injectKeyDown(XEvent event)
{
	KeySym key = NoSymbol;
	XLookupString(&event.xkey, 0, 0, &key, 0);

	for (const KeyMapping &mapping : XtoKeycode)
	{
		if (mapping.keysym == key)
		{
			InputEventKeyPress keyPress;
			keyPress.keycode = mapping.keycode;

			onKeyPressed(keyPress);
		}
	}
}

void Keyboard::_injectKeyUp(XEvent event)
{
	KeySym key = NoSymbol;
	XLookupString(&event.xkey, 0, 0, &key, 0);

	for (const KeyMapping &mapping : XtoKeycode)
	{
		if (mapping.keysym == key)
		{
			InputEventKeyRelease keyRelease;
			keyRelease.keycode = mapping.keycode;

			onKeyReleased(keyRelease);
		}
	}
}

NAMESPACE_END(ois)
NAMESPACE_END(sway)