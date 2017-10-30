#ifndef SWAY_FOUNDATION_OBJECTMETADATA_H
#define SWAY_FOUNDATION_OBJECTMETADATA_H

#include "../defines.h"
#include "../types.h"
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(foundation)

class ObjectMetadata {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param[in] className
	 *   Имя класса.
	 * 
	 * \param[in] superclass
	 *   Указатель на объект метаданных базового класса.
	 */
	ObjectMetadata(lpcstr className, const ObjectMetadata *superclass)
		: _superclass(superclass), _className(className) {
		// Empty
	}

	/*!
	 * \brief
	 *   Получает метаданные базового класса.
	 */
	const ObjectMetadata *getSuperclass() const {
		return _superclass;
	}

	/*!
	 * \brief
	 *   Получает имя класса.
	 */
	const std::string &getClassName() const {
		return _className;
	}

private:
	const ObjectMetadata *_superclass; /*!< Метаданные базового класса. */
	std::string _className; /*!< Имя класса. */
};

NAMESPACE_END(foundation)
NAMESPACE_END(sway)

#endif // SWAY_FOUNDATION_OBJECTMETADATA_H