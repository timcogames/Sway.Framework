#ifndef SWAY_GL_SHADEROBJECT_H
#define SWAY_GL_SHADEROBJECT_H

#include "resource.h"
#include "shaderpreprocessor.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct ShaderObjectCreateInfo {
	u32 type;
	std::string source;
	ShaderPreprocessorRef_t preprocessor;
};

/*!
 * \brief
 *   Представление шейдерного объекта.
 */
class ShaderObject : public Resource {
public:
	static GLenum getGLType(u32 type);

	static ShaderObject *create(const ShaderObjectCreateInfo &createInfo);

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] type
	 *   Тип создаваемого шейдера.
	 */
	ShaderObject(const u32 type);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~ShaderObject();

	/*!
	 * \brief
	 *   Выполняет компиляцию шейдерного объекта.
	 * 
	 * \param[in] source
	 *   Исходный код шейдера.
	 */
	void compile(lpcstr source);

	/*!
	 * \brief
	 *   Возвращает статус компиляции.
	 * 
	 * \return
	 *   Если компиляция прошла успешно 'true', иначе 'false'.
	 */
	bool isCompiled() const;

	/*!
	 * \brief
	 *   Получает тип шейдерного объекта.
	 * 
	 * \return
	 *   Тип шейдерного объекта.
	 */
	u32 getType() const;

	bool available() const;

private:
	u32 _type; /*!< Тип шейдера. */
	bool _compiled;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADEROBJECT_H