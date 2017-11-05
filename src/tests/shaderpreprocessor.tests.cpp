#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp> // boost::make_shared

#include "../gl/shaderpreprocessor.h"

USING_NAMESPACE(sway)

BOOST_AUTO_TEST_SUITE(TShaderPreprocessorTestSuite)

BOOST_AUTO_TEST_CASE(TShaderPreprocessorTestCase_Define) {
	std::ostringstream out;
	auto preprocessor = boost::make_shared<gl::ShaderPreprocessor>(120, "core");
	
	preprocessor->define("ITEM1", "1");
	preprocessor->define("ITEM2", "2");
	preprocessor->define("ITEM3", "3");
	preprocessor->evaluate(out);

	std::string expected("#version 120 core\n"
		"#define ITEM1 1\n"
		"#define ITEM2 2\n"
		"#define ITEM3 3\n");

	BOOST_CHECK_EQUAL(out.str(), expected);
}

BOOST_AUTO_TEST_SUITE_END()