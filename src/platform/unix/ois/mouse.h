#ifndef SWAY_OIS_MOUSE_H
#define SWAY_OIS_MOUSE_H

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
class Mouse : public foundation::Object
{
	DECLARE_OBJECT(Mouse, foundation::Object)

  public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	Mouse(InputManager *creator);

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	virtual ~Mouse();

	void capture();

	void hide(bool hide);

  private:
	/*!
	 * \fn void Mouse::_initialize()
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

#endif // SWAY_OIS_MOUSE_H