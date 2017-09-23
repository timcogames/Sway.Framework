#ifndef SWAY_GRAPHICS_PREREQUISITES_H
#define SWAY_GRAPHICS_PREREQUISITES_H

#include "../defines.h"
#include "../types.h"

#include "renderqueuepriorities.h"
#include "rendersubqueuegroups.h"

#include <iostream> // std::cout
#include <vector> // std::vector
#include <functional> // std::bind
#include <algorithm> // std::sort

#include <boost/shared_ptr.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderSubqueue;
class RenderQueue;
class RenderSubsystem;

typedef boost::shared_ptr<RenderSubqueue> RenderSubqueuePtr;
typedef std::vector<RenderSubqueuePtr> RenderSubqueueVec;

typedef boost::shared_ptr<RenderQueue> RenderQueuePtr;
typedef std::vector<RenderQueuePtr> RenderQueueVec;

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_PREREQUISITES_H