#ifndef SWAY_GL_SHADERPROGRAMBASE_H
#define SWAY_GL_SHADERPROGRAMBASE_H

#include "../math/math.h"
#include "shadertypes.h"
#include "glprereqs.h"
#include "exportmacros.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class IShader
{
public:
	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~IShader() {}

	/*!
	 * \brief
	 *   Читает файл с исходным кодом шейдера.
	 * 
	 * \param[in] filename
	 *   Имя файла.
	 */
	virtual std::string readFile(lpcstr filename) = 0;

	/*!
	 * \brief
	 *   Создает и выполняет компиляцию шейдерного объекта.
	 * 
	 * \param[in] type
	 *   Тип создаваемого шейдера.
	 * 
	 * \param[in] source
	 *   Исходный код шейдера.
	 */
	virtual u32 compile(ShaderTypes type, lpcstr source) = 0;

	/*!
	 * \brief
	 *   Связывает шейдерные объекты с программным объектом.
	 * 
	 * \param[in] shaders
	 *   Дескрипторы связываемых шейдерных объектов.
	 */
	virtual void attach(std::vector<u32> shaders) = 0;

	/*!
	 * \brief
	 *   Отсоединяет шейдерный объект от программного объекта.
	 * 
	 * \param[in] shaders
	 *   Дескрипторы отвязываемых шейдерных объектов.
	 */
	virtual void detach(std::vector<u32> shaders) = 0;
	
	/*!
	 * \brief
	 *   Компоновка шей­дерных объектов.
	 */
	virtual void link() = 0;
	
	/*!
	 * \brief
	 *   Проверяет программный объект.
	 */
	virtual void validate() = 0;

	virtual void use() = 0;

	virtual void unuse() = 0;

	virtual b32 isUsed() const = 0;

	virtual void setUniformVector4(const std::string &uniform, const math::TVector4<float> &vector4) = 0;
	
	virtual void setUniformColor(const std::string &uniform, const math::TColor<float> &color) = 0;

	virtual u32 getShaderProgram() const = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

IShader *allocateShader();
void freeShader(IShader *object);

#ifdef __cplusplus
}
#endif

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERPROGRAMBASE_H