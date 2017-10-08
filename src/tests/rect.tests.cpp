#include <boost/test/unit_test.hpp>

#include "../math/math.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(TRectTestSuite)

/*!
 * Убеждаемся, что конструктор по умолчанию приводит все компоненты к нулю.
 */
BOOST_AUTO_TEST_CASE(TRectTestCase_DefaultConstructor)
{
	math::TRect<s32> rect;

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
	const s32 x = 8, y = 16, w = 32, h = 64;
	
	math::TRect<s32> rect = math::TRect<s32>(x, y, w, h);

	BOOST_CHECK_EQUAL(rect.getL(), x);
	BOOST_CHECK_EQUAL(rect.getT(), y);
	BOOST_CHECK_EQUAL(rect.getR(), x + w);
	BOOST_CHECK_EQUAL(rect.getB(), y + h);
	BOOST_CHECK_EQUAL(rect.getW(), w);
	BOOST_CHECK_EQUAL(rect.getH(), h);
}

BOOST_AUTO_TEST_CASE(TRectTestCase_Offset)
{
	const s32 x = 8, y = 16, w = 32, h = 64;
	const s32 xoffset = 2, yoffset = 4;

	math::TRect<s32> rect = math::TRect<s32>(x, y, w, h);
	rect.offset(xoffset, yoffset);

	BOOST_CHECK_EQUAL(rect.getL(), x + xoffset);
	BOOST_CHECK_EQUAL(rect.getT(), y + yoffset);
	BOOST_CHECK_EQUAL(rect.getR(), x + xoffset + w);
	BOOST_CHECK_EQUAL(rect.getB(), y + yoffset + h);
	BOOST_CHECK_EQUAL(rect.getW(), w);
	BOOST_CHECK_EQUAL(rect.getH(), h);
}

/*!
 * Убеждаемся, что преобразование в TSize<type> проходит правильно.
 */
BOOST_AUTO_TEST_CASE(TRectTestCase_ConvertToSize)
{
	const s32 x = 8, y = 16, w = 32, h = 64;

	math::TRect<s32> rect = math::TRect<s32>(x, y, w, h);
	math::TSize<s32> size = rect.toSize();

	BOOST_CHECK_EQUAL(size.getW(), w);
	BOOST_CHECK_EQUAL(size.getH(), h);
}

BOOST_AUTO_TEST_SUITE_END()