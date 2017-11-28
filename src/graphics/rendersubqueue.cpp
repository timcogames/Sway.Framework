#include "rendersubqueue.h"
#include "rendersubqueuegroup.h"
#include "drawable.h"
#include "material.h"
#include "../gl/primitivetopology.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
RenderSubqueue::RenderSubqueue()
	: _group(kRenderSubqueueGroup_Opaque) {
	// Empty
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 * 
 * \param[in] groupIdx
 *   Индекс группы.
 */
RenderSubqueue::RenderSubqueue(u32 groupIdx)
	: _group(groupIdx) {
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
RenderSubqueue::~RenderSubqueue() {
	// Empty
}

void RenderSubqueue::addDrawable(DrawableRef_t drawable) {
	_drawables.push_back(drawable);
}

/*!
 * \brief
 *   Метод отрисовки.
 */
void RenderSubqueue::render() {
	gl::BufferObject *currentVBO = NULL, *currentIBO = NULL;

	BOOST_FOREACH (DrawableRef_t drawable, _drawables) {
		currentVBO = drawable->getVBO();
		currentIBO = drawable->getIBO();
	
		drawable->getMaterial()->bind();
		currentVBO->bind();
		drawable->getVertexAttributeBinding()->enable(currentVBO->getByteStride());

		_drawCall.update(gl::kPrimitiveTopology_TriangleList, currentIBO->getCapacity(), currentIBO->getDataType(), drawable->hasIndexes());
		_drawCall.execute(currentIBO);
	
		drawable->getVertexAttributeBinding()->disable();
		currentVBO->unbind();
		drawable->getMaterial()->unbind();
	}
}

/*!
 * \brief
 *   Устанавливает индекс группы.
 */
void RenderSubqueue::setGroupIdx(u32 groupIdx) {
	_group = groupIdx;
}

/*!
 * \brief
 *   Получает индекс группы.
 */
u32 RenderSubqueue::getGroupIdx() const {
	return _group;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)