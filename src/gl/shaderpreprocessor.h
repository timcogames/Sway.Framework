#ifndef SWAY_GL_SHADERPREPROCESSOR_H
#define SWAY_GL_SHADERPREPROCESSOR_H

#include "glprereqs.h"
#include <ostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum ShaderProfiles {
	kShaderProfile_Core,
	kShaderProfile_Es
};

class ShaderPreprocessor {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderPreprocessor(u32 version, const std::string &profile);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~ShaderPreprocessor();

	void addDefine(const std::string &name, const std::string &value = std::string());

	bool isDefined(const std::string &name) const;

	void evaluate(std::ostream &into);

	/*!
	 * \brief
	 *   Получает версию шейдера.
	 * 
	 * \return
	 *   Номер версии шейдера.
	 */
	u32 getVersion() const;

private:
	typedef std::map<std::string, std::string> DefineContainer_t;
	DefineContainer_t _definitions;

	u32 _version; /*!< Версия шейдера. */
	std::string _profile;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERPREPROCESSOR_H