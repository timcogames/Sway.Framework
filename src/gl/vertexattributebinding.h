#ifndef SWAY_GL_VERTEXATTRIBUTEBINDING_H
#define SWAY_GL_VERTEXATTRIBUTEBINDING_H

#include "shaderprogram.h"
#include "vertexelementsemantics.h"
#include "vertexattribute.h"
#include "typeutils.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class VertexAttributeBinding {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	VertexAttributeBinding();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~VertexAttributeBinding();

	void mergeLayout();

	void addAttribute(const std::string &attributeName);

	void addAttributes(std::initializer_list<std::string> attributeNames);

	void setVertexInputAttributeDescription(const std::string &attributeName, int size, u32 dataType, bool normalized);

	void enable(u32 byteStride);

	void disable();

	u32 getVertexLayoutOffset() const;

	void setShaderProgram(ShaderProgram *program);

	void setVertexDeclaration(boost::shared_ptr<VertexDeclaration> vertexDeclaration);

	boost::shared_ptr<VertexDeclaration> getVertexDeclaration();

	void setAttributes(VertexAttributeContainer_t attributes);

	VertexAttributeContainer_t getAttributes();

	void setMaxVertexAttributes(int maxVertexAttributes);

	int getMaxVertexAttributes();

protected:
	std::string getAttributeNameBySemantic(VertexElementSemantics semantic) const;

private:
	ShaderProgram *_program;
	boost::shared_ptr<VertexDeclaration> _vertexDeclaration;
	VertexAttributeContainer_t _attributes;
	int _maxVertexAttributes;

	u32 _vertexLayoutOffset;
	u32 _vertexAttributeOffset;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXATTRIBUTEBINDING_H