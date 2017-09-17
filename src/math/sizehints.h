#ifndef SWAY_MATH_SIZEHINTS_H
#define SWAY_MATH_SIZEHINTS_H

#include "size.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

template <typename T>
struct TSizeHints
{
	TSize<T> min;
	TSize<T> max;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_SIZEHINTS_H