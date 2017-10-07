#ifndef SWAY_MATH_MATHPREREQS_H
#define SWAY_MATH_MATHPREREQS_H

#include "../types.h"
#include "../defines.h"

#include <string> // std::string
#include <iostream> // std::ostream
#include <sstream> // std::basic_stringstream

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

template<typename type>
class TPoint;

template<typename type>
class TSize;

template<typename type>
class TRect;

/*!
 * \class
 *   TColor
 * 
 * \brief
 *   Шаблонный класс представения цвета.
 */
template<typename type>
class TColor;

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_MATHPREREQS_H