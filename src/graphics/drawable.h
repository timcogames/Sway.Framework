#ifndef SWAY_GRAPHICS_DRAWABLE_H
#define SWAY_GRAPHICS_DRAWABLE_H

#include "graphicsprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Drawable {
public:
	struct Vertex {
		f32 position[3];
		f32 uv[2];
	};

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Drawable(Material *material, bool indexed);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~Drawable();

	void create(const struct DrawableCreateInfo &info, gl::VertexElementContainer_t vertexElements);

	gl::BufferObject *getVBO();

	gl::BufferObject *getIBO();

	gl::VertexAttributeBinding *getVertexAttributeBinding();
	
	Material *getMaterial();

	bool hasIndexes() const;

private:
	std::string _uniqueId;  /*!< Уникальный идентификатор. */
	gl::BufferObject *_vbo; /*!< Объект буфера вершин. */
	gl::BufferObject *_ibo; /*!< Объект буфера индексов. */
	gl::VertexAttributeBinding *_vertexAttributeBinding;
	bool _indexed;
	Material *_material;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_DRAWABLE_H