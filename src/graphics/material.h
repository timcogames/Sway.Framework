#ifndef SWAY_GRAPHICS_MATERIAL_H
#define SWAY_GRAPHICS_MATERIAL_H

#include "graphicsprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

struct MaterialInitialInfo {
	gl::ShaderObjectCreateInfo vsoInfo;
	gl::ShaderObjectCreateInfo fsoInfo;
	gl::TextureCreateInfo texInfo;
};

class Material {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Material(const MaterialInitialInfo &info);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~Material();

	void bind();

	void unbind();

	gl::ShaderProgram *getShaderProgram();

private:
	gl::ShaderProgram *_shaderProgram;
	gl::TextureObject *_texture;
	gl::TextureSampler *_textureSampler;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_MATERIAL_H