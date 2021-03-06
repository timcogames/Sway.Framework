#include <boost/test/unit_test.hpp>

#include "../math/math.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(TSizeTestSuite)

/*!
 * Убеждаемся, что конструктор по умолчанию приводит все компоненты к нулю.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_DefaultConstructor) {
	const math::TSize<s32> size;

	BOOST_CHECK_EQUAL(size.getW(), 0);
	BOOST_CHECK_EQUAL(size.getH(), 0);
}

/*!
 * Убеждаемся, что конструктор устанавливает все значения компонентов в те, 
 * которые были заданы.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_ComponentConstructor) {
	const s32 w = 1, h = 2;
	const math::TSize<s32> size(w, h);

	BOOST_CHECK_EQUAL(size.getW(), w);
	BOOST_CHECK_EQUAL(size.getH(), h);
}

BOOST_AUTO_TEST_CASE(TSizeTestCase_ScalarConstructor) {
	const s32 w = 1, h = 2;
	const math::TSize<s32> size(math::TSize<s32>(w, h));

	BOOST_CHECK_EQUAL(size.getW(), w);
	BOOST_CHECK_EQUAL(size.getH(), h);
}

/*!
 * Тест для оператора равенства.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_EqualityOperator1) {
	const math::TSize<s32> size1(0, 0), size2(0, 0);

	BOOST_CHECK_EQUAL(size1 == size2, true);
}

/*!
 * Тест для оператора равенства.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_EqualityOperator2) {
	const math::TSize<s32> size1(1, 0), size2(0, 0);

	BOOST_CHECK_EQUAL(size1 == size2, false);
}

/*!
 * Тест для оператора равенства.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_EqualityOperator3) {
	const math::TSize<s32> size1(0, 0), size2(0, 2);

	BOOST_CHECK_EQUAL(size1 == size2, false);
}

BOOST_AUTO_TEST_CASE(TSizeTestCase_EqualityOperator4) {
	const math::TSize<s32> size(1, 2);
	
	BOOST_CHECK_EQUAL(size, math::TSize<s32>(1, 2));
}

/*!
 * Тест для оператора неравенства.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_NonEqualityOperator1) {
	const math::TSize<s32> size1(1, 2), size2(1, 2);

	BOOST_CHECK_EQUAL(size1 != size2, false);
}

/*!
 * Тест для оператора неравенства.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_NonEqualityOperator2) {
	const math::TSize<s32> size1(1, 2), size2(0, 2);

	BOOST_CHECK_EQUAL(size1 != size2, true);
}

/*!
 * Тест для оператора неравенства.
 */
BOOST_AUTO_TEST_CASE(TSizeTestCase_NonEqualityOperator3) {
	const math::TSize<s32> size1(1, 2), size2(1, 0);

	BOOST_CHECK_EQUAL(size1 != size2, true);
}

BOOST_AUTO_TEST_SUITE_END()