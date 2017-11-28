#ifndef SWAY_GL_TEXTUREOBJECT_H
#define SWAY_GL_TEXTUREOBJECT_H

#include "resource.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class TextureObject : public Resource {
public:
	static GLenum translateTargetToGLenum(u32 target);

	static GLenum translatePixelFormatToGLenum(u32 format);

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TextureObject();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~TextureObject();

	void create(const TextureCreateInfo &createInfo);

	/*!
	 * \brief
	 *   Устанавливает активацию текстурного блока.
	 * 
	 * \note
	 *   Блок GL_TEXTURE0_ARB всегда активирован по-умолчанию.
	 *
	 * \param[in] channel
	 *   Канал текстурного блока.
	 */
	void setActive(s32 channel);

	void bind();

	void unbind();

	/*!
	 * \brief
	 *   Получает текстурную цель.
	 *
	 * \return
	 *   Текстурная цель.
	 */
	u32 getTarget() const;

private:
	u32 _target; /*!< Текстурная цель. */
	u32 _format;
	u32 _internalFormat;

	s32 _maxTextureSize;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTUREOBJECT_H