#ifndef SWAY_FOUNDATION_OBJECT_H
#define SWAY_FOUNDATION_OBJECT_H

#include "objectmetadata.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(foundation)

class Context;

/*!
 * \brief
 *   Базовый класс для объектов.
 */
class Object {
	friend class Context;

public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param[in] context
	 *   Контекст.
	 */
	Object(Context *context)
		 : _context(context) {
		// Empty
	}

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~Object() {
		// Empty
	}

	/*!
	 * \brief
	 *   Получает метаданные текущего класса.
	 */
	static const ObjectMetadata *getObjectMetadata() { return 0; }

	/*!
	 * \brief
	 *   Получает метаданные базового класса.
	 */
	virtual const ObjectMetadata *getSuperclass() const = 0;

	/*!
	 * \brief
	 *   Получает имя класса.
	 */
	virtual const std::string &getClassName() const = 0;

	/*!
	 * \brief
	 *   Получает контекст.
	 */
	Context *getContext() const {
		return _context;
	}

private:
	Context *_context; /*!< Контекст. */
};

NAMESPACE_END(foundation)
NAMESPACE_END(sway)

#endif // SWAY_FOUNDATION_OBJECT_H