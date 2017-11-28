#include "material.h"

#include "../gl/vertexelement.h"
#include "../gl/texturefilter.h"
#include "../gl/texturewrap.h"
#include "../utils/file.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
Material::Material(const MaterialInitialInfo &info) {
	_shaderProgram = new gl::ShaderProgram();
	_shaderProgram->attach(gl::ShaderObject::create(info.vsoInfo));
	_shaderProgram->attach(gl::ShaderObject::create(info.fsoInfo));
	
	_shaderProgram->link();
	if (_shaderProgram->isLinked()) {
		// Empty
	}

	_shaderProgram->validate();
	if (_shaderProgram->isValidated()) {
		// Empty
	}

	_texture = new gl::TextureObject();
	_texture->create(info.texInfo);

	_textureSampler = new gl::TextureSampler(_texture);
	_textureSampler->setFilter(gl::kTextureFilter_Nearest);
	_textureSampler->setWrapMode(gl::kTextureWrap_Clamp, gl::kTextureWrap_Clamp, gl::kTextureWrap_Clamp);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
Material::~Material() {
	SAFE_DELETE(_textureSampler);
	SAFE_DELETE(_texture);
	SAFE_DELETE(_shaderProgram);
}

void Material::bind() {
	_shaderProgram->use();
	_texture->setActive(0);
	_texture->bind();
}

void Material::unbind() {
	_texture->unbind();
	_shaderProgram->unuse();
}

gl::ShaderProgram *Material::getShaderProgram() {
	return _shaderProgram;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)