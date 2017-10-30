#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>

#include "../memory/safedeletemacros.h"
#include "../graphics/rendersubsystem.h"
#include "../graphics/renderqueue.h"
#include "../graphics/rendersubqueue.h"

USING_NAMESPACE(sway::graphics)

class RenderSubsystemFixture {
public:
	RenderSubsystemFixture() {
		BOOST_TEST_MESSAGE("constructor");

		_render = new RenderSubsystem();
	}

	~RenderSubsystemFixture() {
		BOOST_TEST_MESSAGE("destructor");

		SAFE_DELETE(_render);
	}

	RenderSubsystem *getRenderSubsystem() {
		return _render;
	}

private:
	RenderSubsystem *_render;
};

BOOST_FIXTURE_TEST_CASE(BoostWarnTest, RenderSubsystemFixture) {
	RenderSubsystem *render = getRenderSubsystem();
	render->render();

	BOOST_WARN(true);
}



BOOST_AUTO_TEST_SUITE(test_suite)

BOOST_AUTO_TEST_CASE(test_case) {
	BOOST_TEST_MESSAGE("constructor");
	auto renderSubsystem = new RenderSubsystem();

	auto queue_h = renderSubsystem->createQueue();
	queue_h->setPriority(kRenderQueuePriority_High);
	queue_h->addSubqueue(boost::make_shared<RenderSubqueue>()); // Создает буфер геометрии
	auto subqueueGroup_h = queue_h->getSubqueueGroupByIdx(kRenderSubqueueGroup_Transparent);

	auto queue_l = renderSubsystem->createQueue();
	queue_l->setPriority(kRenderQueuePriority_Low);
	queue_l->addSubqueue(boost::make_shared<RenderSubqueue>());
	auto subqueueGroup_l = queue_l->getSubqueueGroupByIdx(kRenderSubqueueGroup_Transparent);
 
	auto queue_n = renderSubsystem->createQueue();
	queue_n->setPriority(kRenderQueuePriority_Normal);
	queue_n->addSubqueue(boost::make_shared<RenderSubqueue>());
	auto subqueueGroup_n = queue_n->getSubqueueGroupByIdx(kRenderSubqueueGroup_Transparent);

	auto unsortedQueues = renderSubsystem->getQueues();
	BOOST_CHECK_EQUAL(unsortedQueues.size(), size_t(3));

	renderSubsystem->sortQueues();

	auto sortedQueues = renderSubsystem->getQueues();
	BOOST_CHECK(std::is_sorted(sortedQueues.begin(), sortedQueues.end(), RenderQueue::PriorityInDescendingOrder()) == true);

	renderSubsystem->render();

	SAFE_DELETE(renderSubsystem);
}

BOOST_AUTO_TEST_SUITE_END()