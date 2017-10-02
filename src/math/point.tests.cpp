#define BOOST_TEST_MODULE MathTestModule
#include <boost/test/included/unit_test.hpp>

#include "point.h"

#include "../defines.h"
#include "../types.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(TPointTestSuite)

/*!
 * Убеждаемся, что конструктор по умолчанию приводит все компоненты к нулю.
 */
BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
	const math::TPoint<s32> point;

	BOOST_CHECK_EQUAL(point.getX(), 0);
	BOOST_CHECK_EQUAL(point.getY(), 0);
}

/*!
 * Убеждаемся, что конструктор устанавливает все значения компонентов в те, 
 * которые были заданы.
 */
BOOST_AUTO_TEST_CASE(ComponentConstructor)
{
	const s32 x = 1, y = 2;
	const math::TPoint<s32> point(x, y);

	BOOST_CHECK_EQUAL(point.getX(), x);
	BOOST_CHECK_EQUAL(point.getY(), y);
}

BOOST_AUTO_TEST_CASE(ScalarConstructor)
{
	const s32 x = 1, y = 2;
	const math::TPoint<s32> size(math::TPoint<s32>(x, y));

	BOOST_CHECK_EQUAL(size.getX(), x);
	BOOST_CHECK_EQUAL(size.getY(), y);
}

/*!
 * Тест для оператора равенства.
 */
BOOST_AUTO_TEST_CASE(EqualityOperator1)
{
	const math::TPoint<s32> point1(0, 0), point2(0, 0);

	BOOST_CHECK_EQUAL(point1 == point2, true);
}

/*!
 * Тест для оператора равенства.
 */
BOOST_AUTO_TEST_CASE(EqualityOperator2)
{
	const math::TPoint<s32> point1(1, 0), point2(0, 0);

	BOOST_CHECK_EQUAL(point1 == point2, false);
}

/*!
 * Тест для оператора равенства.
 */
BOOST_AUTO_TEST_CASE(EqualityOperator3)
{
	const math::TPoint<s32> point1(0, 0), point2(0, 2);

	BOOST_CHECK_EQUAL(point1 == point2, false);
}

/*!
 * Тест для оператора неравенства.
 */
BOOST_AUTO_TEST_CASE(NonEqualityOperator1)
{
	const math::TPoint<s32> point1(1, 2), point2(1, 2);

	BOOST_CHECK_EQUAL(point1 != point2, false);
}

/*!
 * Тест для оператора неравенства.
 */
BOOST_AUTO_TEST_CASE(NonEqualityOperator2)
{
	const math::TPoint<s32> point1(1, 2), point2(0, 2);

	BOOST_CHECK_EQUAL(point1 != point2, true);
}

/*!
 * Тест для оператора неравенства.
 */
BOOST_AUTO_TEST_CASE(NonEqualityOperator3)
{
	const math::TPoint<s32> point1(1, 2), point2(1, 0);

	BOOST_CHECK_EQUAL(point1 != point2, true);
}

BOOST_AUTO_TEST_SUITE_END()