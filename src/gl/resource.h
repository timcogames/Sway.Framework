#ifndef SWAY_GL_RESOURCE_H
#define SWAY_GL_RESOURCE_H

#include "shadertypes.h"
#include "glprereqs.h"
#include "exportmacros.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class Resource {
public:
	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~Resource() {
		// Empty
	}

	/*!
	 * \brief
	 *   Получает идентификатор ресурса.
	 */
	ResourceHandle_t getHandle() const {
		return _resourceHandle;
	}

protected:
	ResourceHandle_t _resourceHandle; /*!< Идентификатор ресурса. */
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_RESOURCE_H