#include <boost/test/unit_test.hpp>

#include "../math/math.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(TMatrix4TestSuite)

/*!
 * Убеждаемся, что конструктор по умолчанию приводит матрицу к единичной.
 */
BOOST_AUTO_TEST_CASE(TMatrix4TestCase_DefaultConstructor)
{
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

BOOST_AUTO_TEST_SUITE_END()