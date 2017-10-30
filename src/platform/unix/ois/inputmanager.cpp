#include "inputmanager.h"

#include <stdio.h>  // printf, NULL
#include <stdlib.h> // strtoull

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 * 
 * \param[in] window
 *   Уникальный идентификатор окна.
 */
InputManager::InputManager(u32 window)
	: _window(static_cast<::Window>(window)), _keyboardUsed(false), _mouseUsed(false) {
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
InputManager::~InputManager() {
	// Empty
}

/*!
 * \brief
 *   Создает объект устройства ввода.
 *
 * \param[in] type
 *   Тип устройства.
 */
foundation::Object *InputManager::createDevice(DeviceTypes type) {
	if (NOT _window AND hasFreeDevice(type))
		return NULL;

	foundation::Object *device = NULL;

	switch(type) {
	case kDeviceType_Keyboard:
		device = createKeyboard();
		break;
	case kDeviceType_Mouse:
		device = createMouse();
		break;
	default:
		break;
	}

	if (NOT device)
		printf("No devices match requested type.\n");

	return device;
}

foundation::Object *InputManager::createKeyboard() {
	foundation::Object *device = new Keyboard(this);
	if (NOT device)
		return NULL;

	registerObject(device);

	return device;
}

foundation::Object *InputManager::createMouse() {
	foundation::Object *device = new Mouse(this);
	if (NOT device)
		return NULL;

	registerObject(device);

	return device;
}

/*!
 * \brief
 *   Проверяет устройство.
 *
 * \param[in] type
 *   Тип устройства для проверки.
 */
int InputManager::hasFreeDevice(DeviceTypes type) {
	switch(type) {
	case kDeviceType_Keyboard:
		return _keyboardUsed;
	case kDeviceType_Mouse:
		return _mouseUsed;
	default:
		return 0;
	}
}

/*!
 * \brief
 *   Устанавливает логическое значение использования клавиатуры.
 *
 * \param[in] used
 *   Обрабатывать события от клавиатуры?
 *
 * \note
 *   Внутренний метод.
 */
void InputManager::setKeyboardUsed(bool used) {
	_keyboardUsed = used;
}

/*!
 * \brief
 *   Устанавливает логическое значение использования мышки.
 *
 * \param[in] used
 *   Обрабатывать события от мышки?
 *
 * \note
 *   Внутренний метод.
 */
void InputManager::setMouseUsed(bool used) {
	_mouseUsed = used;
}

/*!
 * \brief
 *   Получает идентификатор окна.
 */
::Window InputManager::getWindow() {
	return _window;
}

NAMESPACE_END(ois)
NAMESPACE_END(sway)