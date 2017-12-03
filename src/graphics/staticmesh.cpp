#include "staticmesh.h"
#include "rendersubqueue.h"
#include "renderqueue.h"
#include "drawable.h"
#include "material.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue
	, Material *material, bool indexed, const struct DrawableCreateInfo &info, gl::VertexElementContainer_t vertexElements) {

	auto drawable = boost::make_shared<Drawable>(material, indexed);
	drawable->create(info, vertexElements);

	subqueue->addDrawable(drawable);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
StaticMesh::~StaticMesh() {
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)