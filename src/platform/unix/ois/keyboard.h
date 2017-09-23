#ifndef SWAY_OIS_KEYBOARD_H
#define SWAY_OIS_KEYBOARD_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "../../../foundation/object.h"
#include "../../../foundation/declareobjectmacros.h"
#include "../../../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

class InputManager;
class Keyboard : public foundation::Object
{
	DECLARE_OBJECT(Keyboard, foundation::Object)

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

  private:
	/*!
	 * \fn void Keyboard::_initialize()
	 * \brief Инициализация устройства.
	 *
	 * \note Внутренний метод, вызывается в конструкторе.
	 */
	void _initialize();

  private:
	::Display *_display;
	::Window _window;

	bool _grab;
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_OIS_KEYBOARD_H