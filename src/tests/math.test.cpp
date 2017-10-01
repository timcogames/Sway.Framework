#define BOOST_TEST_MODULE test_math
#include <boost/test/included/unit_test.hpp>

#include "../defines.h"
#include "../math/size.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(test_suite_size)
BOOST_AUTO_TEST_CASE(test_size)
{
	math::TSize<s32> size (1, 2);
    BOOST_CHECK_EQUAL(size.getW(), 1);
	BOOST_CHECK_EQUAL(size.getH(), 2);
	BOOST_CHECK_EQUAL(size, math::TSize<s32>(1, 2));
}
BOOST_AUTO_TEST_SUITE_END()