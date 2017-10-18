#ifndef SWAY_GL_VERTEXATTRIBUTEBINDING_H
#define SWAY_GL_VERTEXATTRIBUTEBINDING_H

#include "shader.h"
#include "vertexelementsemantics.h"
#include "vertexattribute.h"
#include "datatypeinfo.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class VertexAttributeBinding
{
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

	void setVertexInputAttributeDescription(const std::string &attributeName, int size, DataTypeInfo::Types dataType, bool isNormalized);

	void bind();

	void unbind();

	u32 getVertexLayoutOffset() const;

	void setShaderPointer(IShader *shader);
	
	IShader *getShaderPointer();

	void setVertexDeclarationPointer(VertexDeclaration *vertexDeclaration);

	VertexDeclaration *getVertexDeclarationPointer();

	void setVertexBufferPointer(HardwareBuffer *vertexBuffer);

	HardwareBuffer *getVertexBufferPointer();

	void setAttributes(VertexAttributeContainer_t attributes);

	VertexAttributeContainer_t getAttributes();

	void setMaxVertexAttributes(int maxVertexAttributes);

	int getMaxVertexAttributes();

protected:
	std::string getAttributeNameBySemantic(VertexElementSemantics semantic) const;

private:
	IShader *_shader;
	VertexDeclaration *_vertexDeclaration;
	HardwareBuffer *_vertexBuffer;
	VertexAttributeContainer_t _attributes;
	int _maxVertexAttributes;

	u32 _vertexLayoutOffset;
	u32 _vertexAttributeOffset;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXATTRIBUTEBINDING_H