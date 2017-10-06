#ifndef SWAY_DEFINES_H
#define SWAY_DEFINES_H

#define OR  ||
#define AND &&
#define NOT !

#define DONT_CARE -1

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

#endif // SWAY_DEFINES_H