#include "vertexattributebinding.h"
#include "vertexdeclaration.h"
#include "vertexattribute.h"
#include "vertexelement.h"
#include "hardwarebuffer.h"
#include "shaderbuilder.h"
#include "extensions.h"

#include <boost/foreach.hpp> // BOOST_FOREACH
#include <boost/range/adaptor/map.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
VertexAttributeBinding::VertexAttributeBinding()
	: _shader(NULL)
	, _vertexLayoutOffset(0)
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

			attribute.isEnabled = true;
			attribute.dataType = DataTypeInfo::kType_Float;
			attribute.isNormalized = false;
			attribute.isCustomAttribute = false;

			switch (vertexElement.semantic) {
			case kVertexElementSemantic_Position:
				attribute.componentCount = DataTypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += DataTypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Color:
				attribute.componentCount = DataTypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += DataTypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_TexCoord:
				attribute.componentCount = DataTypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += DataTypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Normal:
				attribute.componentCount = DataTypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += DataTypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Tangent:
				attribute.componentCount = DataTypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += DataTypeInfo::getElementSize(vertexElement.dataType);
				break;

			case kVertexElementSemantic_Binormal:
				attribute.componentCount = DataTypeInfo::getComponentCount(vertexElement.dataType);
				attribute.pointer = BUFFER_OFFSET(_vertexLayoutOffset);

				_vertexLayoutOffset += DataTypeInfo::getElementSize(vertexElement.dataType);
				break;

			default:
				break;
			}
		}
	}
}

void VertexAttributeBinding::addAttribute(const std::string &attributeName) {
	s32 location = Extensions::glGetAttribLocationARB(_shader->getShaderProgram(), attributeName.c_str());
	if (location >= 0 AND location <= _maxVertexAttributes) {
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

void VertexAttributeBinding::addAttributes(std::initializer_list<std::string> attributeNames) {
	for (auto attribute: attributeNames)
		addAttribute(attribute);
}

void VertexAttributeBinding::setVertexInputAttributeDescription(const std::string &attributeName, int size, u32 dataType, bool isNormalized) {
	if (_vertexAttributeOffset == 0)
		_vertexAttributeOffset = getVertexLayoutOffset();

	VertexAttributeContainer_t::iterator iter = _attributes.find(attributeName);
	if (iter == _attributes.end())
		return;

	VertexAttribute &attribute = iter->second;
	attribute.isEnabled = true;
	attribute.componentCount = size;
	attribute.dataType = dataType;
	attribute.isNormalized = isNormalized;
	attribute.isCustomAttribute = true;
	attribute.pointer = BUFFER_OFFSET(_vertexAttributeOffset);

	_vertexAttributeOffset += DataTypeInfo::getElementSize(dataType) * size;
}

void VertexAttributeBinding::enable(u32 byteStride) {
	BOOST_FOREACH(VertexAttribute &attribute, _attributes | boost::adaptors::map_values) { 
		if (attribute.isEnabled) {
			Extensions::glVertexAttribPointerARB(attribute.location, attribute.componentCount, DataTypeInfo::toGL(attribute.dataType), attribute.isNormalized, byteStride, attribute.pointer);
			Extensions::glEnableVertexAttribArrayARB(attribute.location);
		}
	}
}

void VertexAttributeBinding::disable() {
	BOOST_FOREACH(VertexAttribute &attribute, _attributes | boost::adaptors::map_values) { 
		if (attribute.isEnabled)
			Extensions::glDisableVertexAttribArrayARB(attribute.location);
	}

	_vertexAttributeOffset = 0;
}

u32 VertexAttributeBinding::getVertexLayoutOffset() const {
	return _vertexLayoutOffset;
}

void VertexAttributeBinding::setShader(IShader *shader) {
	_shader = shader;
}

IShader *VertexAttributeBinding::getShader() {
	return _shader;
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