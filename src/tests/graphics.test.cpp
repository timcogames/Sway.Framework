#define BOOST_TEST_MODULE RenderSubsystemFixture

#include <boost/test/included/unit_test.hpp>
#include <boost/make_shared.hpp>

#include "../memory/safedeletemacros.h"
#include "../graphics/rendersubsystem.h"
#include "../graphics/renderqueue.h"
#include "../graphics/rendersubqueue.h"

USING_NAMESPACE(sway::graphics)

BOOST_AUTO_TEST_SUITE(test_suite)
BOOST_AUTO_TEST_CASE(test_case)
{
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