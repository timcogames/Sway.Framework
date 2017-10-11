#include "vertexattributebinding.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) glXGetProcAddressARB((const GLubyte*) "glDisableVertexAttribArrayARB");
PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetAttribLocationARB");
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC) glXGetProcAddressARB((const GLubyte*) "glVertexAttribPointerARB");
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) glXGetProcAddressARB((const GLubyte*) "glEnableVertexAttribArrayARB");


/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
VertexAttributeBinding::VertexAttributeBinding()
	: _shader(NULL)
	, _vertexDeclaration(NULL)
	, _vertexBuffer(NULL)
	, _vertexLayoutOffset(0)
	, _vertexAttributeOffset(0)
{
	// Получаем максимальный номер для положения вершинного атрибута.
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
VertexAttributeBinding::~VertexAttributeBinding()
{
	_attributes.clear();
	
	//SAFE_DELETE(_vertexDeclaration);
}

void VertexAttributeBinding::mergeLayout(void)
{
	for (u32 i = 0; i < _vertexDeclaration->getElementCount(); ++i)
		addAttribute(getAttributeNameBySemantic(_vertexDeclaration->getElementAtIndex(i).semantic));

	for (u32 i = 0; i < _vertexDeclaration->getElementCount(); ++i)
	{
		VertexElement vertexElement = _vertexDeclaration->getElementAtIndex(i);

		VertexAttributeContainer::iterator iter = _attributes.find(getAttributeNameBySemantic(vertexElement.semantic));
		if (iter != _attributes.end())
		{
			VertexAttribute& attribute = iter->second;

			attribute.isEnabled = true;
			attribute.dataType = DataTypeInfo::kType_Float;
			attribute.isNormalized = false;
			attribute.isCustomAttribute = false;

			switch (vertexElement.semantic)
			{
			case kVertexElementSemantic_Position:
				attribute.componentCount = vertexElement.getComponentCount();
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += vertexElement.getElementSize();
				break;

			case kVertexElementSemantic_Color:
				attribute.componentCount = vertexElement.getComponentCount();
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += vertexElement.getElementSize();
				break;

			case kVertexElementSemantic_TexCoord:
				attribute.componentCount = vertexElement.getComponentCount();
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += vertexElement.getElementSize();
				break;

			case kVertexElementSemantic_Normal:
				attribute.componentCount = vertexElement.getComponentCount();
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += vertexElement.getElementSize();
				break;

			case kVertexElementSemantic_Tangent:
				attribute.componentCount = vertexElement.getComponentCount();
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += vertexElement.getElementSize();
				break;

			case kVertexElementSemantic_Binormal:
				attribute.componentCount = vertexElement.getComponentCount();
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += vertexElement.getElementSize();
				break;

			default:
				break;
			}
		}
	}
}

void VertexAttributeBinding::addAttribute(const std::string& attributeName)
{
	s32 location = glGetAttribLocationARB(_shader->getShaderProgram(), attributeName.c_str());
	if (location >= 0 AND location <= _maxVertexAttributes)
	{
		VertexAttribute attribute;
		attribute.isEnabled = false;
		attribute.location = location;
		attribute.componentCount = 0;
		attribute.dataType = DataTypeInfo::kType_Float;
		attribute.isNormalized = false;
		attribute.isCustomAttribute = false;
		attribute.pointer = NULL;

		_attributes.insert(std::make_pair(attributeName, attribute));
	}
}

void VertexAttributeBinding::addAttributes(std::initializer_list<std::string> attributeNames)
{
	for (auto attribute: attributeNames)
		addAttribute(attribute);
}

void VertexAttributeBinding::setVertexInputAttributeDescription(const std::string& attributeName, int size, DataTypeInfo::Types dataType, bool isNormalized)
{
	if (_vertexAttributeOffset == 0)
		_vertexAttributeOffset = getVertexLayoutOffset();

	VertexAttributeContainer::iterator iter = _attributes.find(attributeName);
	if (iter == _attributes.end())
		return;

	VertexAttribute& attribute = iter->second;
	attribute.isEnabled = true;
	attribute.componentCount = size;
	attribute.dataType = dataType;
	attribute.isNormalized = isNormalized;
	attribute.isCustomAttribute = true;
	attribute.pointer = BUFFER_OFFSET(_vertexAttributeOffset);

	if (dataType == DataTypeInfo::kType_Int) _vertexAttributeOffset += sizeof(int) * size;
	else if (dataType == DataTypeInfo::kType_Float) _vertexAttributeOffset += sizeof(float) * size;
	else if (dataType == DataTypeInfo::kType_Double) _vertexAttributeOffset += sizeof(double) * size;
	else if (dataType == DataTypeInfo::kType_Short) _vertexAttributeOffset += sizeof(short) * size;
	else if (dataType == DataTypeInfo::kType_Byte) _vertexAttributeOffset += sizeof(char*) * size;
}

void VertexAttributeBinding::bind()
{
	_vertexBuffer->bind();

	for (VertexAttributeContainer::iterator iter = _attributes.begin(); iter != _attributes.end(); ++iter)
	{
		VertexAttribute attribute = iter->second;
		if (attribute.isEnabled)
		{
			glVertexAttribPointerARB(attribute.location, attribute.componentCount, DataTypeInfo::toGL(attribute.dataType), attribute.isNormalized, _vertexBuffer->getByteStride(), attribute.pointer);
			glEnableVertexAttribArrayARB(attribute.location);
		}
	}
}

void VertexAttributeBinding::unbind()
{
	for (VertexAttributeContainer::iterator iter = _attributes.begin(); iter != _attributes.end(); ++iter)
	{
		VertexAttribute attribute = iter->second;
		if (attribute.isEnabled)
			glDisableVertexAttribArrayARB(attribute.location);
	}

	_vertexBuffer->unbind();

	_vertexAttributeOffset = 0;
}

u32 VertexAttributeBinding::getVertexLayoutOffset() const
{
	return _vertexLayoutOffset;
}

ShaderProgram *VertexAttributeBinding::getShaderPointer()
{
	return _shader;
}

void VertexAttributeBinding::setShaderPointer(ShaderProgram *shader)
{
	_shader = shader;
}

VertexDeclaration *VertexAttributeBinding::getVertexDeclarationPointer()
{
	return _vertexDeclaration;
}

void VertexAttributeBinding::setVertexDeclarationPointer(VertexDeclaration *vertexDeclaration)
{
	_vertexDeclaration = vertexDeclaration;
}

HardwareBuffer *VertexAttributeBinding::getVertexBufferPointer()
{
	return _vertexBuffer;
}

void VertexAttributeBinding::setVertexBufferPointer(HardwareBuffer *vertexBuffer)
{
	_vertexBuffer = vertexBuffer;
}

VertexAttributeContainer VertexAttributeBinding::getAttributes()
{
	return _attributes;
}

void VertexAttributeBinding::setAttributes(VertexAttributeContainer attributes)
{
	_attributes = attributes;
}

int VertexAttributeBinding::getMaxVertexAttributes()
{
	return _maxVertexAttributes;
}

void VertexAttributeBinding::setMaxVertexAttributes(int maxVertexAttributes)
{
	_maxVertexAttributes = maxVertexAttributes;
}

std::string VertexAttributeBinding::getAttributeNameBySemantic(VertexElementSemantics semantic) const
{
	switch (semantic)
	{
		case kVertexElementSemantic_Position: return VERTEX_ATTRIBUTE_POSITION;
		case kVertexElementSemantic_Color:    return VERTEX_ATTRIBUTE_COLOR;
		case kVertexElementSemantic_TexCoord: return VERTEX_ATTRIBUTE_TEXCOORD0;
		case kVertexElementSemantic_Normal:   return VERTEX_ATTRIBUTE_NORMAL;
		case kVertexElementSemantic_Tangent:  return VERTEX_ATTRIBUTE_TANGENT;
		case kVertexElementSemantic_Binormal: return VERTEX_ATTRIBUTE_BINORMAL;
	default:
		return NULL;
	}
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)