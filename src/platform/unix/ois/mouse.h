#ifndef SWAY_PLATFORM_UNIX_OIS_MOUSE_H
#define SWAY_PLATFORM_UNIX_OIS_MOUSE_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

class Mouse : public foundation::Object
{
	DECLARE_OBJECT(Mouse, foundation::Object)

public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Mouse(InputManager *creator);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~Mouse();

	void capture();

	void hide(bool hide);

private:
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
	void _initialize();

	void _injectMouseMove(XEvent event);
	
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
	bool _injectMouseButtonDown(XEvent event);
	
	bool _injectMouseButtonUp(XEvent event);

	bool _injectMouseButtonClick();

	bool _injectMouseButtonDoubleClick();

private:
	::Display *_display;
	::Window _window;
	bool _grab;
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_MOUSE_H