#ifndef SWAY_GL_SHADERPROGRAM_H
#define SWAY_GL_SHADERPROGRAM_H

#include "../math/math.h"
#include "shaderobject.h"
#include "shadertype.h"
#include "glprereqs.h"

#include <set>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Представление шейдерной программы.
 */
class ShaderProgram : public Resource {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderProgram();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~ShaderProgram();

	/*!
	 * \brief
	 *   Связывает шейдерный объект с программным объектом.
	 * 
	 * \param[in] shader
	 *   Указатель на связываемый шейдерный объект.
	 * 
	 * \sa
	 *   detach(ResourceHandle_t)
	 */
	void attach(ShaderObject *shader);

	/*!
	 * \brief
	 *   Отсоединяет шейдерный объект от программного объекта.
	 * 
	 * \param[in] handle
	 *   Отвязываемый шейдерный объект.
	 * 
	 * \sa
	 *   attach(ShaderObject *)
	 */
	void detach(ResourceHandle_t handle);
	
	/*!
	 * \brief
	 *   Компоновка шей­дерных объектов.
	 */
	void link();

	bool isLinked() const;
	
	/*!
	 * \brief
	 *   Проверяет программный объект.
	 */
	void validate();

	bool isValidated() const;

	void use();

	void unuse();

	bool isUsed() const;

	void setUniformVector4(const std::string &uniform, const math::TVector4<f32> &vector4);
	
	void setUniformColor(const std::string &uniform, const math::TColor<f32> &color);

private:
	std::set<u32> _shaderHandleSet;

	bool _linked;
	bool _validated;

	UniformVec4fUmap_t _uniformVec4fSets;

	s32 _numActiveUniforms;
	s32 _numActiveAttributes;
	s32 _uniformMaxLength;
	s32 _attributeMaxLength;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERPROGRAM_H