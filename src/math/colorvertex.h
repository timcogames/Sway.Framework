#ifndef SWAY_MATH_COLORVERTEX_H
#define SWAY_MATH_COLORVERTEX_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Структура представления вершины.
 */
struct ColorVertex {
	f32 x, y, z;
	f32 r, g, b, a;

	static ColorVertex set(const TVector3<f32> &position, const TColor<f32> &color) {
		ColorVertex vertex;
	
		vertex.x = position.getX();
		vertex.y = position.getY();
		vertex.z = position.getZ();
	
		vertex.r = color.getR();
		vertex.g = color.getG();
		vertex.b = color.getB();
		vertex.a = color.getA();
	
		return vertex;
	}
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_COLORVERTEX_H