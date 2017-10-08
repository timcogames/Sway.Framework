#include <boost/test/unit_test.hpp>

#include "../math/math.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(TColorTestSuite)

/*!
 * Убеждаемся, что конструктор по умолчанию приводит все компоненты к нулю.
 */
BOOST_AUTO_TEST_CASE(TColorTestCase_DefaultConstructor)
{
	math::TColor<float> color;

	BOOST_CHECK_EQUAL(color.getR(), 0.0f);
	BOOST_CHECK_EQUAL(color.getG(), 0.0f);
	BOOST_CHECK_EQUAL(color.getB(), 0.0f);
	BOOST_CHECK_EQUAL(color.getA(), 1.0f);
}

/*!
 * Убеждаемся, что конструктор устанавливает все значения компонентов в те, 
 * которые были заданы.
 */
BOOST_AUTO_TEST_CASE(TColorTestCase_ComponentConstructor)
{
	const float r = 0.1f, g = 0.2f, b = 0.3f, a = 1.0f;
	
	math::TColor<float> color = math::TColor<float>(r, g, b, a);

	BOOST_CHECK_EQUAL(color.getR(), r);
	BOOST_CHECK_EQUAL(color.getG(), g);
	BOOST_CHECK_EQUAL(color.getB(), b);
	BOOST_CHECK_EQUAL(color.getA(), a);
}

/*!
 * Убеждаемся, что преобразование в TVector4<type> проходит правильно.
 */
BOOST_AUTO_TEST_CASE(TColorTestCase_ConvertToVector4)
{
	const float r = 0.1f, g = 0.2f, b = 0.3f, a = 1.0f;

	math::TColor<float> color = math::TColor<float>(r, g, b, a);
	math::TVector4<float> vec4 = color.toVec4();

	BOOST_CHECK_EQUAL(vec4.getX(), r);
	BOOST_CHECK_EQUAL(vec4.getY(), g);
	BOOST_CHECK_EQUAL(vec4.getZ(), b);
	BOOST_CHECK_EQUAL(vec4.getW(), a);
}

BOOST_AUTO_TEST_SUITE_END()