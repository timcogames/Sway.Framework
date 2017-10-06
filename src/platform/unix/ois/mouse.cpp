#include "mouse.h"
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
Mouse::Mouse(InputManager *creator)
	: foundation::Object(creator), _display(NULL), _window(None)
{
	static_cast<InputManager *>(getContext())->setMouseUsed(true);

	_initialize();
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
Mouse::~Mouse()
{
	if (_display)
	{
		if (_grab)
			XUngrabPointer(_display, CurrentTime);

		XCloseDisplay(_display);
	}

	static_cast<InputManager *>(getContext())->setMouseUsed(false);
}

/*!
 * \fn
 *   void Mouse::_initialize()
 * 
 * \brief
 *   Инициализация устройства.
 *
 * \note
 *   Внутренний метод, вызывается в конструкторе.
 */
void Mouse::_initialize()
{
	if (_display)
		XCloseDisplay(_display);
	_display = NULL;

	_window = static_cast<InputManager *>(getContext())->getWindow();
	if (NOT(_display = XOpenDisplay(NULL)))
		return;

	XSelectInput(_display, _window, ButtonPressMask | ButtonReleaseMask | PointerMotionMask);

	if (_grab)
		XGrabPointer(_display, _window, True, 0, GrabModeAsync, GrabModeAsync, _window, None, CurrentTime);
}

void Mouse::capture()
{
	XEvent event = {};

	while (XPending(_display) > 0)
	{
		XNextEvent(_display, &event);

		if (event.type == MotionNotify) _injectMouseMove(event);
		else if (event.type == ButtonPress) _injectMouseButtonDown(event);
		else if (event.type == ButtonRelease) _injectMouseButtonUp(event);
	}
}

void Mouse::_injectMouseMove(XEvent event)
{
	std::cout << "Mouse X:" << event.xmotion.x << ", Y: " << event.xmotion.y << "\n";
}

/*!
 * \brief
 *   Функция, которая отправляет событие с кнопки мыши в приемник.
 * 
 * \param event
 *   Событие кнопки мыши.
 * 
 * \return
 *   - True, если устройство ввода обрабатывается приемником.
 *   - False, если устройство ввода не был обработан приемником.
 */
bool Mouse::_injectMouseButtonDown(XEvent event)
{
	if (event.xbutton.button == 1)
		std::cout << "Left mouse down\n";
	else if (event.xbutton.button == 2)
		std::cout << "Middle mouse down\n";
	else if (event.xbutton.button == 3)
		std::cout << "Right mouse down\n";
	else if (event.xbutton.button == 4)
		std::cout << "Mouse scroll up\n";
	else if (event.xbutton.button == 5)
		std::cout << "Mouse scroll down\n";

	return true;
}

bool Mouse::_injectMouseButtonUp(XEvent event)
{
	if (event.xbutton.button == 1)
		std::cout << "Left mouse up\n";
	else if (event.xbutton.button == 2)
		std::cout << "Middle mouse up\n";
	else if (event.xbutton.button == 3)
		std::cout << "Right mouse up\n";

	return true;
}

bool Mouse::_injectMouseButtonClick()
{
	return true;
}

bool Mouse::_injectMouseButtonDoubleClick()
{
	return true;
}

void Mouse::hide(bool hide)
{
	//if (hide)
	//    XDefineCursor(_display, _window, cursor);
	//else
	//    XUndefineCursor(_display, _window);
}

NAMESPACE_END(ois)
NAMESPACE_END(sway)