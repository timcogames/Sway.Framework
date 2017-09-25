#ifndef SWAY_OIS_INPUTMANAGER_H
#define SWAY_OIS_INPUTMANAGER_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <string>
#include <map>

#include "devicetypes.h"
#include "keyboard.h"
#include "mouse.h"

#include "../../../foundation/context.h"
#include "../../../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

class InputManager : public foundation::Context
{
  public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	InputManager();

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	virtual ~InputManager();

	/*!
	 * \brief Создает объект устройства ввода.
	 *
	 * \param type Тип устройства.
	 */
	foundation::Object *createInputObject(DeviceTypes type);

	/*!
	 * \brief Инициализация.
	 *
	 * \param params Список параметров.
	 */
	void initialize(ParamList &params);

	/*!
	 * \brief Устанавливает логическое значение использования клавиатуры.
	 *
	 * \param used Обрабатывать события от клавиатуры?
	 *
	 * \note Внутренний метод.
	 */
	void _setKeyboardUsed(bool used);

	/*!
	 * \brief Устанавливает логическое значение использования мышки.
	 *
	 * \param used Обрабатывать события от мышки?
	 *
	 * \note Внутренний метод.
	 */
	void _setMouseUsed(bool used);

	::Window _getWindow();

  private:
	::Window _window;

  public:
	bool _keyboardUsed; /*!< Используется ли клавиатура. */
	bool _mouseUsed; /*!< Используется ли мышка. */
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_OIS_INPUTMANAGER_H