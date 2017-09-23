#include "inputmanager.h"

#include <stdio.h>  // printf, NULL
#include <stdlib.h> // strtoull

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
InputManager::InputManager()
	: _keyboardUsed(false), _mouseUsed(false)
{
	_window = 0;
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
InputManager::~InputManager()
{
	// Empty
}

/*!
 * \brief Создает объект устройства ввода.
 *
 * \param type Тип устройства.
 */
foundation::Object *InputManager::createInputObject(DeviceTypes type)
{
	foundation::Object *inputObject = NULL;

	switch(type)
	{
	  case kDeviceType_Keyboard:
		inputObject = new Keyboard(this);
		break;
	  case kDeviceType_Mouse:
		inputObject = new Mouse(this);
		break;
	  case kDeviceType_Unknown:
		break;
	}

	if(inputObject)
		this->registerObject(inputObject);

	return inputObject;
}

/*!
 * \brief Инициализация.
 *
 * \param params Список параметров.
 */
void InputManager::initialize(ParamList &params)
{
	ParamList::iterator iter = params.find("WINDOW");
	if (iter == params.end())
	{
		return;
	}

	_window = strtoull(iter->second.c_str(), 0, 10);
}

NAMESPACE_END(ois)
NAMESPACE_END(sway)