#ifndef SWAY_GL_VERTEXATTRIBUTEBINDING_H
#define SWAY_GL_VERTEXATTRIBUTEBINDING_H

#include "shaderprogram.h"
#include "vertexelementsemantics.h"
#include "vertexdeclaration.h"
#include "hardwarebuffer.h"
#include "vertexattribute.h"
#include "datatypeinfo.h"
#include "../defines.h"
#include "../types.h"

#include <initializer_list> // std::initializer_list
#include <string>
#include <GL/gl.h>

// Имена униформ.
#define SHADER_UNIFORM_NAME_MODEL_MATRIX "modelMatrix"
#define SHADER_UNIFORM_NAME_VIEW_MATRIX "viewMatrix"
#define SHADER_UNIFORM_NAME_PROJ_MATRIX "projectionMatrix"

// Имена атрибутов.
#define VERTEX_ATTRIBUTE_POSITION "attr_position"
#define VERTEX_ATTRIBUTE_COLOR "attr_color"
#define VERTEX_ATTRIBUTE_TEXCOORD0 "attr_texCoord_0"
#define VERTEX_ATTRIBUTE_TEXCOORD1 "attr_texCoord_1"
#define VERTEX_ATTRIBUTE_TEXCOORD2 "attr_texCoord_2"
#define VERTEX_ATTRIBUTE_TEXCOORD3 "attr_texCoord_3"
#define VERTEX_ATTRIBUTE_NORMAL "attr_normal"
#define VERTEX_ATTRIBUTE_TANGENT "attr_tangent"
#define VERTEX_ATTRIBUTE_BINORMAL "attr_binormal"
#define VERTEX_ATTRIBUTE_BLEND_WEIGHTS "attr_blendWeights"
#define VERTEX_ATTRIBUTE_BLEND_INDICES "attr_blendIndices"

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

	ShaderProgram *getShaderPointer();

	void setShaderPointer(ShaderProgram *shader);

	VertexDeclaration *getVertexDeclarationPointer();

	void setVertexDeclarationPointer(VertexDeclaration *vertexDeclaration);

	HardwareBuffer *getVertexBufferPointer();

	void setVertexBufferPointer(HardwareBuffer *vertexBuffer);

	VertexAttributeContainer getAttributes();

	void setAttributes(VertexAttributeContainer attributes);

	int getMaxVertexAttributes();

	void setMaxVertexAttributes(int maxVertexAttributes);

protected:
	std::string getAttributeNameBySemantic(VertexElementSemantics semantic) const;

private:
	ShaderProgram *_shader;
	VertexDeclaration *_vertexDeclaration;
	HardwareBuffer *_vertexBuffer;
	VertexAttributeContainer _attributes;
	int _maxVertexAttributes;

	u32 _vertexLayoutOffset;
	u32 _vertexAttributeOffset;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXATTRIBUTEBINDING_H