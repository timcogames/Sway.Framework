#ifndef SWAY_PLATFORM_UNIX_OIS_KEYBOARD_H
#define SWAY_PLATFORM_UNIX_OIS_KEYBOARD_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

class Keyboard : public foundation::Object
{
	DECLARE_OBJECT(Keyboard, foundation::Object)

public:
	boost::function<void(const InputEventKeyPress &)> onKeyPressed;
	boost::function<void(const InputEventKeyRelease &)> onKeyReleased;

public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	Keyboard(InputManager *creator);

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	virtual ~Keyboard();

	void capture();

	void connect(KeyboardListener *listener);

  private:
	/*!
	 * \fn void Keyboard::_initialize()
	 * \brief Инициализация устройства.
	 *
	 * \note Внутренний метод, вызывается в конструкторе.
	 */
	void _initialize();

	void _injectKeyDown(XEvent event);

	void _injectKeyUp(XEvent event);

  private:
	::Display *_display;
	::Window _window;

	bool _grab;
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_KEYBOARD_H