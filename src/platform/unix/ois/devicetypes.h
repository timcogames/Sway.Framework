#ifndef SWAY_PLATFORM_UNIX_OIS_DEVICETYPES_H
#define SWAY_PLATFORM_UNIX_OIS_DEVICETYPES_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

/*!
 * \enum
 *   DeviceTypes
 * 
 * \brief
 *   Перечисление типов устройств ввода.
 */
enum DeviceTypes {
	kDeviceType_Keyboard = 0, /*!< Клавиатура. */
	kDeviceType_Mouse = 1     /*!< Мышка. */
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_DEVICETYPES_H