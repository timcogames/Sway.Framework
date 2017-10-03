#include <boost/test/unit_test.hpp>

#include "../math/math.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(TRectTestSuite)

/*!
 * Убеждаемся, что конструктор по умолчанию приводит все компоненты к нулю.
 */
BOOST_AUTO_TEST_CASE(TRectTestCase_DefaultConstructor)
{
	const math::TRect<s32> rect;

	BOOST_CHECK_EQUAL(rect.getL(), 0);
	BOOST_CHECK_EQUAL(rect.getT(), 0);
	BOOST_CHECK_EQUAL(rect.getR(), 0);
	BOOST_CHECK_EQUAL(rect.getB(), 0);
}

/*!
 * Убеждаемся, что конструктор устанавливает все значения компонентов в те, 
 * которые были заданы.
 */
BOOST_AUTO_TEST_CASE(TRectTestCase_ComponentConstructor)
{
	const s32 x = 1, y = 2, w = 3, h = 4;
	const math::TRect<s32> rect(x, y, w, h);

	BOOST_CHECK_EQUAL(rect.getL(), x);
	BOOST_CHECK_EQUAL(rect.getT(), y);
	BOOST_CHECK_EQUAL(rect.getW(), w);
	BOOST_CHECK_EQUAL(rect.getH(), h);
}

BOOST_AUTO_TEST_SUITE_END()