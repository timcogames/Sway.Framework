#ifndef SWAY_DEFINES_H
#define SWAY_DEFINES_H

#define OR  ||
#define AND &&
#define NOT !

#define DONT_CARE -1

/*!
 * \brief
 *   Статус успеха.
 * 
 * \sa
 *   FAILURE_STATUS
 */
#define SUCCESS_STATUS 0

/*!
 * \brief
 *   Статус отказа.
 * 
 * \sa
 *   SUCCESS_STATUS
 */
#define FAILURE_STATUS 1

/*!
 * \brief
 *   Недействительный тип.
 */
#define INVALID_TYPE 0

/*!
 * \brief
 *   Открывает область пространства имен.
 *
 * \param name
 *   Имя области пространства имен.
 * 
 * \sa
 *   USING_NAMESPACE
 *   NAMESPACE_END
 */
#define NAMESPACE_BEGIN(name) namespace name {

/*!
 * \brief
 *   Закрывает область пространства имен.
 *
 * \param name
 *   Имя области пространства имен.
 * 
 * \sa
 *   USING_NAMESPACE
 *   NAMESPACE_BEGIN
 */
#define NAMESPACE_END(name) }

#define USING_NAMESPACE(name) using namespace name;

#define BLOCK_BEGIN for(;;) {
#define BLOCK_END break; }
#define NOOP(...) BLOCK_BEGIN BLOCK_END

/*!
 * \brief
 *   Преобразует объект в строку.
 *
 * \param object
 *   Объект который следует преобразовать в строку.
 */
#define STRINGIFY(object) #object
#define CASE_TOSTRING(object) case object: return STRINGIFY(object)

#endif // SWAY_DEFINES_H