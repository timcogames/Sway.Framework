#include "shaderpreprocessor.h"
#include "../utils/file.h"
#include "../utils/stringhelper.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
ShaderPreprocessor::ShaderPreprocessor(u32 version, const std::string &profile)
	: _version(version)
	, _profile(profile) {
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
ShaderPreprocessor::~ShaderPreprocessor() {
	// Empty
}

void ShaderPreprocessor::addDefine(const std::string &name, const std::string &value) {
	if (NOT name.empty())
		_definitions[name] = value;
}

bool ShaderPreprocessor::isDefined(const std::string &name) const {
    if (NOT name.empty())
        return _definitions.find(name) != _definitions.end();

    return false;
}

void ShaderPreprocessor::evaluate(std::ostream &into) {
	into << "#version " << _version << (_profile.empty() ? "": " ") << _profile << std::endl;

	BOOST_FOREACH(DefineContainer_t::value_type pair, _definitions)
		into << "#define " << pair.first << (pair.second.empty() ? "": " ") << pair.second << std::endl;
}

/*!
 * \brief
 *   Получает версию шейдера.
 * 
 * \return
 *   Номер версии шейдера.
 */
u32 ShaderPreprocessor::getVersion() const {
	return _version;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)