#ifndef SWAY_PLATFORM_UNIX_OIS_DEVICETYPES_H
#define SWAY_PLATFORM_UNIX_OIS_DEVICETYPES_H

#include "../../../defines.h"
#include <string>
#include <map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

enum DeviceTypes
{
	kDeviceType_Unknown = 0,  /*!< Неизвестное устройство. */
	kDeviceType_Keyboard = 1, /*!< Клавиатура. */
	kDeviceType_Mouse = 2     /*!< Мышка. */
};

typedef std::multimap<DeviceTypes, std::string> DeviceList;
typedef std::multimap<std::string, std::string> ParamList;

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_DEVICETYPES_H