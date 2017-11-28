#ifndef SWAY_GL_TEXTURESAPLER_H
#define SWAY_GL_TEXTURESAPLER_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class TextureSampler {
public:
	static GLenum translateWrapToGLenum(u32 wrap);

	static GLenum translateCompareFuncToGLenum(u32 compareFunc);

	static GLenum translateStencilOpToGLenum(u32 stencilOp);

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TextureSampler(TextureObject *texture);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~TextureSampler();

	void setFilter(u32 filter);

	void setWrapMode(u32 wrapS, u32 wrapT, u32 wrapR);

	void setStencilFunc(u32 stencilFunc, s32 reference, u32 mask);

	/*!
	 * \brief
	 *   Получает максимальный уровень анизотропной фильтрации.
	 *
	 * \return
	 *   Уровень анизотропной фильтрации.
	 */
	s32 getMaxAnisotropicLevel() const;

private:
	TextureObject *_texture;
	s32 _maxAnisotropy; /*!< Максимальный уровень анизотропной фильтрации. */
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTURESAPLER_H