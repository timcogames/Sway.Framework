#ifndef SWAY_PLATFORM_UNIX_OIS_INPUTMANAGER_H
#define SWAY_PLATFORM_UNIX_OIS_INPUTMANAGER_H

#include "oisprereqs.h"
#include "devicetypes.h"
#include "keyboard.h"
#include "mouse.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

class InputManager : public foundation::Context
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param window
	 *   Уникальный идентификатор окна.
	 */
	InputManager(u32 window);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~InputManager();

	/*!
	 * \brief
	 *   Создает объект устройства ввода.
	 *
	 * \param type
	 *   Тип устройства.
	 */
	foundation::Object *createDevice(DeviceTypes type);

	foundation::Object *createKeyboard();
	foundation::Object *createMouse();

	/*!
	 * \brief
	 *   Проверяет устройство.
	 *
	 * \param type
	 *   Тип устройства для проверки.
	 */
	int hasFreeDevice(DeviceTypes type);

	/*!
	 * \brief
	 *   Устанавливает логическое значение использования клавиатуры.
	 *
	 * \param used
	 *   Обрабатывать события от клавиатуры?
	 *
	 * \note
	 *   Внутренний метод.
	 */
	void setKeyboardUsed(bool used);

	/*!
	 * \brief
	 *   Устанавливает логическое значение использования мышки.
	 *
	 * \param used
	 *   Обрабатывать события от мышки?
	 *
	 * \note
	 *   Внутренний метод.
	 */
	void setMouseUsed(bool used);

	/*!
	 * \brief
	 *   Получает идентификатор окна.
	 */
	::Window getWindow();

public:
	::Window _window; /*!< Идентификатор окна. */
	bool _keyboardUsed; /*!< Используется ли клавиатура. */
	bool _mouseUsed; /*!< Используется ли мышка. */
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_INPUTMANAGER_H