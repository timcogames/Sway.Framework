#include "drawable.h"
#include "drawabledescription.h"
#include "material.h"
#include "../utils/guid.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
Drawable::Drawable(Material *material, bool indexed)
	: _vbo(NULL)
	, _ibo(NULL)
	, _material(material)
	, _indexed(indexed) {

	_uniqueId = utils::Guid::generate();
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
Drawable::~Drawable() {
	SAFE_DELETE(_vertexAttributeBinding);
	SAFE_DELETE(_ibo);
	SAFE_DELETE(_vbo);
}

void Drawable::create(const struct DrawableCreateInfo &info, gl::VertexElementContainer_t vertexElements) {
	_vbo = gl::BufferObject::create(info.vboInfo);

	if (_indexed)
		_ibo = gl::BufferObject::create(info.iboInfo);

	_vertexAttributeBinding = new gl::VertexAttributeBinding();
	_vertexAttributeBinding->setShaderProgram(_material->getShaderProgram());
	_vertexAttributeBinding->setVertexDeclaration(boost::make_shared<gl::VertexDeclaration>(vertexElements));
	_vertexAttributeBinding->mergeLayout();
}

/*!
 * \brief 
 *   Получает указатель на объект вершинного буфера.
 *
 * \sa 
 *   getIBO()
 */
gl::BufferObject *Drawable::getVBO() {
	return _vbo;
}

/*!
 * \brief 
 *   Получает указатель на объект индексного буфера.
 *
 * \sa 
 *   getVBO()
 */
gl::BufferObject *Drawable::getIBO() {
	return _ibo;
}

gl::VertexAttributeBinding *Drawable::getVertexAttributeBinding() {
	return _vertexAttributeBinding;
}

/*!
 * \brief 
 *   Получает указатель на материал.
 */
Material *Drawable::getMaterial() {
	return _material;
}

bool Drawable::hasIndexes() const {
	return _indexed;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)