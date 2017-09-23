#include "inputmanager.h"
#include "mouse.h"

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
Mouse::Mouse(InputManager *creator)
    : foundation::Object(creator), _display(NULL), _window(None)
{
    static_cast<InputManager *>(getContext())->_setMouseUsed(true);

    _initialize();
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
Mouse::~Mouse()
{
    if (_display)
    {
        if (_grab)
            XUngrabPointer(_display, CurrentTime);

        XCloseDisplay(_display);
    }

    static_cast<InputManager *>(getContext())->_setMouseUsed(false);
}

/*!
 * \fn void Mouse::_initialize()
 * \brief Инициализация устройства.
 *
 * \note Внутренний метод, вызывается в конструкторе.
 */
void Mouse::_initialize()
{
    if (_display)
        XCloseDisplay(_display);
    _display = NULL;

    _window = static_cast<InputManager *>(getContext())->_getWindow();
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

        switch (event.type)
        {
        case MotionNotify:
            std::cout << "Mouse X:" << event.xmotion.x << ", Y: " << event.xmotion.y << "\n";
            break;
        case ButtonPress:
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
            break;
        case ButtonRelease:
            if (event.xbutton.button == 1)
                std::cout << "Left mouse up\n";
            else if (event.xbutton.button == 2)
                std::cout << "Middle mouse up\n";
            else if (event.xbutton.button == 3)
                std::cout << "Right mouse up\n";
            break;
        }
    }
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