#include "context.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(foundation)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
Context::Context()
{
	// Empty
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
Context::~Context()
{
	_objects.clear();
}

/*!
 * \brief Регистрирует объект в контейнере текущего контекста.
 *
 * \param object Указатель на объект, который следует добавить в контейнер.
 * \sa Context::unregisterObject(const std::string &)
 */
void Context::registerObject(Object *object)
{
	if (NOT object)
		return;

	_objects.insert(std::make_pair(object->getClassName(), object));
}

/*!
 * \brief Разрегистрирует объект из контейнера текущего контекста.
 *
 * \param objectType Тип объекта.
 * \sa Context::registerObject(Object *)
 */
void Context::unregisterObject(const std::string &objectType)
{
	ObjectMapConstIter iter = _objects.find(objectType);
	if (iter != _objects.end())
		_objects.erase(iter);
}

/*!
 * \brief Получает объект из контейнера текущего контекста.
 *
 * \param objectType Тип объекта.
 */
Object *Context::getObject(const std::string &objectType) const
{
	ObjectMapConstIter iter = _objects.find(objectType);
	if (iter != _objects.end())
		return iter->second;

	return 0;
}

/*!
 * \brief Получает количество зарегистрированных объектов.
 */
u32 Context::getObjectCount() const
{
	return _objects.size();
}

NAMESPACE_END(foundation)
NAMESPACE_END(sway)