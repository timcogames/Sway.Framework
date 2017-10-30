#include <boost/test/unit_test.hpp>

#include "../math/math.h"

USING_NAMESPACE(sway)

static const s32 IDEN_MAT4[4][4] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

static const s32 RAND_MAT4[4][4] = {
	6, 5, 9, 8,
	8, 0, 3, 4,
	8, 2, 7, 9,
	1, 1, 5, 3
};

BOOST_AUTO_TEST_SUITE(TMatrix4TestSuite)

/*!
 * Убеждаемся, что конструктор по умолчанию приводит матрицу к единичной.
 */
BOOST_AUTO_TEST_CASE(TMatrix4TestCase_DefaultConstructor) {
	const math::TMatrix4<s32> mat4;

	BOOST_CHECK_EQUAL(mat4.get(0, 0), 1);
	BOOST_CHECK_EQUAL(mat4.get(0, 1), 0);
	BOOST_CHECK_EQUAL(mat4.get(0, 2), 0);
	BOOST_CHECK_EQUAL(mat4.get(0, 3), 0);

	BOOST_CHECK_EQUAL(mat4.get(1, 0), 0);
	BOOST_CHECK_EQUAL(mat4.get(1, 1), 1);
	BOOST_CHECK_EQUAL(mat4.get(1, 2), 0);
	BOOST_CHECK_EQUAL(mat4.get(1, 3), 0);

	BOOST_CHECK_EQUAL(mat4.get(2, 0), 0);
	BOOST_CHECK_EQUAL(mat4.get(2, 1), 0);
	BOOST_CHECK_EQUAL(mat4.get(2, 2), 1);
	BOOST_CHECK_EQUAL(mat4.get(2, 3), 0);

	BOOST_CHECK_EQUAL(mat4.get(3, 0), 0);
	BOOST_CHECK_EQUAL(mat4.get(3, 1), 0);
	BOOST_CHECK_EQUAL(mat4.get(3, 2), 0);
	BOOST_CHECK_EQUAL(mat4.get(3, 3), 1);
}

/*!
 * Убеждаемся, что установка всех компонентов матрицы проходит правильно.
 */
BOOST_AUTO_TEST_CASE(TMatrix4TestCase_Set) {
	math::TMatrix4<s32> mat4;

	mat4.set(0, 0, RAND_MAT4[0][0]);
	mat4.set(0, 1, RAND_MAT4[0][1]);
	mat4.set(0, 2, RAND_MAT4[0][2]);
	mat4.set(0, 3, RAND_MAT4[0][3]);

	mat4.set(1, 0, RAND_MAT4[1][0]);
	mat4.set(1, 1, RAND_MAT4[1][1]);
	mat4.set(1, 2, RAND_MAT4[1][2]);
	mat4.set(1, 3, RAND_MAT4[1][3]);

	mat4.set(2, 0, RAND_MAT4[2][0]);
	mat4.set(2, 1, RAND_MAT4[2][1]);
	mat4.set(2, 2, RAND_MAT4[2][2]);
	mat4.set(2, 3, RAND_MAT4[2][3]);

	mat4.set(3, 0, RAND_MAT4[3][0]);
	mat4.set(3, 1, RAND_MAT4[3][1]);
	mat4.set(3, 2, RAND_MAT4[3][2]);
	mat4.set(3, 3, RAND_MAT4[3][3]);

	BOOST_CHECK_EQUAL(NOT memcmp(mat4.get(), RAND_MAT4, 16), true);
}

BOOST_AUTO_TEST_SUITE_END()