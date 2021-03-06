#ifndef SWAY_FOUNDATION_CONTEXT_H
#define SWAY_FOUNDATION_CONTEXT_H

#include "../defines.h"
#include "../types.h"
#include "object.h"

#include <string>
#include <map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(foundation)

typedef std::map<std::string, Object *> ObjectMap_t;
typedef std::map<std::string, Object *>::const_iterator ObjectMapConstIter_t;

class Context {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Context();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~Context();

	/*!
	 * \brief
	 *   Регистрирует объект в контейнере текущего контекста.
	 *
	 * \param[in] object
	 *   Указатель на объект, который следует добавить в контейнер.
	 * 
	 * \sa
	 *   unregisterObject(const std::string &)
	 */
	virtual void registerObject(Object *object);

	/*!
	 * \brief
	 *   Разрегистрирует объект из контейнера текущего контекста.
	 *
	 * \param[in] objectType
	 *   Тип объекта.
	 * 
	 * \sa
	 *   registerObject(Object *)
	 */
	virtual void unregisterObject(const std::string &objectType);

	/*!
	 * \brief
	 *   Получает объект из контейнера текущего контекста.
	 *
	 * \param[in] objectType
	 *   Тип объекта.
	 */
	virtual Object *getObject(const std::string &objectType) const;

	/*!
	 * \brief
	 *   Получает количество зарегистрированных объектов.
	 */
	virtual u32 getObjectCount() const;

  private:
	ObjectMap_t _objects; /*!< Контейнер объектов. */
};

NAMESPACE_END(foundation)
NAMESPACE_END(sway)

#endif // SWAY_FOUNDATION_CONTEXT_H