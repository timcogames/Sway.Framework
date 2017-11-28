#ifndef SWAY_UTILS_GUID_H
#define SWAY_UTILS_GUID_H

#include "stringhelper.h"
#include "../defines.h"
#include "../types.h"

#include <string> // std::string
#include <stdlib.h> // rand()

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(utils)

/* Пустой идентификатор. */
static const std::string EmptyGuid = "00000000-0000-0000-0000-000000000000";

class Guid {
public:
	/*!
	 * \brief
	 *   Генерирует уникальный идентификатор.
	 */
	static std::string generate() {
		return StringHelper::format("%x%x-%x-%x-%x-%x%x%x",
			rand(), rand(),
			rand(),
			((rand() & 0x0fff) | 0x4000),
			rand() % 0x3fff + 0x8000,
			rand(), rand(), rand());
	}

	/*!
	 * \brief
	 *   Проверяет уникальный идентификатор на валидность.
	 * 
	 * \param[in] guid
	 *   Идентификатор который следует проверить.
	 */
	static bool empty(const std::string &guid) {
		return (guid == EmptyGuid);
	}
};

NAMESPACE_END(utils)
NAMESPACE_END(sway)

#endif // SWAY_UTILS_GUID_H