#ifndef SWAY_GRAPHICS_GRAPHICSPREREQUISITES_H
#define SWAY_GRAPHICS_GRAPHICSPREREQUISITES_H

#define RENDER_SUBQUEUE_GROUP_COUNT 2

#include "../gl/gl.h"
#include "../defines.h"
#include "../types.h"

#include <iostream> // std::cout
#include <vector> // std::vector
#include <functional> // std::bind
#include <algorithm> // std::sort

#include <boost/shared_ptr.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

struct DrawableCreateInfo;

class Material;
class Drawable;
class StaticMesh;
class RenderSubqueue;
class RenderQueue;
class RenderSubsystem;

typedef boost::shared_ptr<Drawable> DrawableRef_t;
typedef std::vector<DrawableRef_t> DrawableRefVector_t;

typedef boost::shared_ptr<class RenderSubqueue> RenderSubqueueRef_t;;
typedef std::vector<RenderSubqueueRef_t> RenderSubqueueRefVector_t;

typedef boost::shared_ptr<class RenderQueue> RenderQueueRef_t;
typedef std::vector<RenderQueueRef_t> RenderQueueRefVector_t;

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_GRAPHICSPREREQUISITES_H