#include "vertexattributebinding.h"
#include "vertexdeclaration.h"
#include "vertexattribute.h"
#include "vertexelement.h"
#include "hardwarebuffer.h"
#include "extensions.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
VertexAttributeBinding::VertexAttributeBinding()
	: _vertexLayoutOffset(0)
	, _vertexAttributeOffset(0) {

	/* Получаем максимальный номер для положения вершинного атрибута. */
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
VertexAttributeBinding::~VertexAttributeBinding() {
	_attributes.clear();
}

void VertexAttributeBinding::mergeLayout() {
	for (u32 i = 0; i < _vertexDeclaration.get()->getElementCount(); ++i)
		addAttribute(getAttributeNameBySemantic(_vertexDeclaration.get()->getElementAtIndex(i).semantic));

	for (u32 i = 0; i < _vertexDeclaration.get()->getElementCount(); ++i) {
		VertexElement vertexElement = _vertexDeclaration.get()->getElementAtIndex(i);

		VertexAttributeContainer_t::iterator iter = _attributes.find(getAttributeNameBySemantic(vertexElement.semantic));
		if (iter != _attributes.end()) {
			VertexAttribute &attribute = iter->second;

			attribute.dataType = kType_Float;
			attribute.enabled = true;
			attribute.normalized = false;
			attribute.customized = false;

			switch (vertexElement.semantic) {
			case kVertexElementSemantic_Position:
				attribute.componentCount = TypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);
				
				_vertexLayoutOffset += TypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Color:
				attribute.componentCount = TypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);
				
				_vertexLayoutOffset += TypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_TexCoord:
				attribute.componentCount = TypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += TypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Normal:
				attribute.componentCount = TypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += TypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Tangent:
				attribute.componentCount = TypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += TypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Binormal:
				attribute.componentCount = TypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += TypeInfo::getElementSize(vertexElement.dataType);
				break;

			default:
				break;
			}
		}
	}
}

void VertexAttributeBinding::addAttribute(const std::string &attributeName) {
	s32 location = Extensions::glGetAttribLocationARB(_program->getHandle(), attributeName.c_str());
	if (location >= 0 AND location <= _maxVertexAttributes) {
		VertexAttribute attribute;
		attribute.location = location;
		attribute.componentCount = 0;
		attribute.dataType = kType_Float;
		attribute.enabled = false;
		attribute.normalized = false;
		attribute.customized = false;
		attribute.pointer = NULL;

		_attributes.insert(std::make_pair(attributeName, attribute));
	}
}

void VertexAttributeBinding::addAttributes(std::initializer_list<std::string> attributeNames) {
	for (auto attribute: attributeNames)
		addAttribute(attribute);
}

void VertexAttributeBinding::setVertexInputAttributeDescription(const std::string &attributeName, int size, u32 dataType, bool normalized) {
	if (_vertexAttributeOffset == 0)
		_vertexAttributeOffset = getVertexLayoutOffset();

	VertexAttributeContainer_t::iterator iter = _attributes.find(attributeName);
	if (iter == _attributes.end())
		return;

	VertexAttribute &attribute = iter->second;
	attribute.componentCount = size;
	attribute.dataType = dataType;
	attribute.enabled = true;
	attribute.normalized = normalized;
	attribute.customized = true;
	attribute.pointer = BUFFER_OFFSET(_vertexAttributeOffset);

	_vertexAttributeOffset += TypeInfo::getElementSize(dataType) * size;
}

void VertexAttributeBinding::enable(u32 byteStride) {
	BOOST_FOREACH(VertexAttribute &attribute, _attributes | boost::adaptors::map_values) { 
		if (attribute.enabled) {
			Extensions::glVertexAttribPointerARB(attribute.location, attribute.componentCount, TypeUtils::toGL(attribute.dataType), attribute.normalized, byteStride, attribute.pointer);
			Extensions::glEnableVertexAttribArrayARB(attribute.location);
		}
	}
}

void VertexAttributeBinding::disable() {
	BOOST_FOREACH(VertexAttribute &attribute, _attributes | boost::adaptors::map_values) { 
		if (attribute.enabled)
			Extensions::glDisableVertexAttribArrayARB(attribute.location);
	}

	_vertexAttributeOffset = 0;
}

u32 VertexAttributeBinding::getVertexLayoutOffset() const {
	return _vertexLayoutOffset;
}

void VertexAttributeBinding::setShaderProgram(ShaderProgram *program) {
	_program = program;
}

void VertexAttributeBinding::setVertexDeclaration(boost::shared_ptr<VertexDeclaration> vertexDeclaration) {
	_vertexDeclaration = vertexDeclaration;
}

boost::shared_ptr<VertexDeclaration> VertexAttributeBinding::getVertexDeclaration() {
	return _vertexDeclaration;
}

void VertexAttributeBinding::setAttributes(VertexAttributeContainer_t attributes) {
	_attributes = attributes;
}

VertexAttributeContainer_t VertexAttributeBinding::getAttributes() {
	return _attributes;
}

void VertexAttributeBinding::setMaxVertexAttributes(int maxVertexAttributes) {
	_maxVertexAttributes = maxVertexAttributes;
}

int VertexAttributeBinding::getMaxVertexAttributes() {
	return _maxVertexAttributes;
}

std::string VertexAttributeBinding::getAttributeNameBySemantic(VertexElementSemantics semantic) const {
	switch (semantic) {
		case kVertexElementSemantic_Position: return VERTEX_ATTRIBUTE_POSITION;
		case kVertexElementSemantic_Color: return VERTEX_ATTRIBUTE_COLOR;
		case kVertexElementSemantic_TexCoord: return VERTEX_ATTRIBUTE_TEXCOORD0;
		case kVertexElementSemantic_Normal: return VERTEX_ATTRIBUTE_NORMAL;
		case kVertexElementSemantic_Tangent: return VERTEX_ATTRIBUTE_TANGENT;
		case kVertexElementSemantic_Binormal: return VERTEX_ATTRIBUTE_BINORMAL;
		default: return "";
	}
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)