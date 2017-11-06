#ifndef SWAY_MATH_VERTEX_H
#define SWAY_MATH_VERTEX_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Базовая структура представления вершины.
 * 
 * \node
 *   Содержит только позицию вершины.
 */
struct VertexPosition {
	f32 x, y, z;

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	VertexPosition() {
		x = y = z = 0.0f;
	}

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	explicit VertexPosition(const TVector3<f32> &position) {
		setPosition(position);
	}

	void setPosition(const TVector3<f32> &position) {
		x = position.getX();
		y = position.getY();
		z = position.getZ();
	}

	TVector3<f32> getPosition() const {
		return TVector3<f32>(x, y, z);
	}
};

/*!
 * \brief
 *   Структура представления вершины.
 * 
 * \node
 *   Содержит позицию и цвет вершины.
 */
struct VertexColor : public VertexPosition {
	f32 r, g, b, a;

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	VertexColor() {
		r = g = b = a = 0.0f;
	}

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	explicit VertexColor(const TVector3<f32> &position, const TColor<f32> &color)
		: VertexPosition(position) {
		setColor(color);
	}

	void setColor(const TColor<f32> &color) {
		r = color.getR();
		g = color.getG();
		b = color.getB();
		a = color.getA();
	}

	TColor<f32> getColor() const {
		return TColor<f32>(r, g, b, a);
	}
};

/*!
 * \brief
 *   Структура представления вершины.
 * 
 * \node
 *   Содержит позицию, цвет и текстурные координаты вершины.
 */
struct VertexTexCoord : public VertexPosition {
	f32 u, v;

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	VertexTexCoord() {
		u = v = 0.0f;
	}

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	explicit VertexTexCoord(const TVector3<f32> &position, const TVector2<f32> &texCoord)
		: VertexPosition(position) {
		setTexCoord(texCoord);
	}

	void setTexCoord(const TVector2<f32> &texCoord) {
		u = texCoord.getX();
		v = texCoord.getY();
	}

	TVector2<f32> getTexCoord() const {
		return TVector2<f32>(u, v);
	}
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_VERTEX_H