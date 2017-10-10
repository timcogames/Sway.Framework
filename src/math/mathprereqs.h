#ifndef SWAY_MATH_MATHPREREQS_H
#define SWAY_MATH_MATHPREREQS_H

#include "../types.h"
#include "../defines.h"

#include <string> // std::string
#include <iostream> // std::ostream
#include <sstream> // std::basic_stringstream

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

struct ColorVertex;

/*!
 * \brief
 *   Шаблонный класс представления точки.
 */
template<typename type>
class TPoint;

/*!
 * \brief
 *   Шаблонный класс представления размера.
 */
template<typename type>
class TSize;

/*!
 * \brief
 *   Шаблонный класс представления прямоугольной области.
 */
template<typename type>
class TRect;

/*!
 * \brief
 *   Шаблонный класс представления вектора из трех компонентов.
 */
template<typename type>
class TVector3;

/*!
 * \brief
 *   Шаблонный класс представления вектора из четырех компонентов.
 */
template<typename type>
class TVector4;

/*!
 * \brief
 *   Шаблонный класс представления цвета.
 */
template<typename type>
class TColor;

/*!
 * \brief
 *   Шаблонный класс представления матрицы.
 */
template<typename type>
class TMatrix4;

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_MATHPREREQS_H