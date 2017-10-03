#include <boost/test/unit_test.hpp>

#include "../defines.h"
#include "../memory/safedeletemacros.h"
#include "../foundation/objectmetadata.h"
#include "../foundation/object.h"
#include "../foundation/declareobjectmacros.h"
#include "../foundation/context.h"

USING_NAMESPACE(sway)

class ThingyContext : public foundation::Context
{
 public:
	ThingyContext() {}
	virtual ~ThingyContext() {}
};

class ThingyObject : public foundation::Object
{
	DECLARE_OBJECT(ThingyObject, foundation::Object)

 public:
	ThingyObject(foundation::Context *context): foundation::Object(context) {}
	~ThingyObject() {}
};

BOOST_AUTO_TEST_SUITE(test_suite)
BOOST_AUTO_TEST_CASE(test_case)
{
	ThingyContext *context = new ThingyContext();
	context->registerObject(new ThingyObject(context));

	ThingyObject *object = (ThingyObject *)context->getObject("ThingyObject");
	BOOST_CHECK(object->getClassName() == "ThingyObject");
	BOOST_CHECK(context->getObjectCount() == 1);

	context->unregisterObject("ThingyObject");
	BOOST_CHECK(context->getObjectCount() == 0);

	SAFE_DELETE(object);
	SAFE_DELETE(context);
}
BOOST_AUTO_TEST_SUITE_END()