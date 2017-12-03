#ifndef SWAY_GRAPHICS_STATICMESH_H
#define SWAY_GRAPHICS_STATICMESH_H

#include "graphicsprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class StaticMesh {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	StaticMesh(RenderSubqueueRef_t subqueue
		, Material *material, bool indexed, const struct DrawableCreateInfo &info, gl::VertexElementContainer_t vertexElements);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~StaticMesh();

private:
	boost::shared_ptr<Drawable> _drawable;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_STATICMESH_H