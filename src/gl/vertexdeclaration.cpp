#include "vertexdeclaration.h"
#include <algorithm> // std::find_if

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
VertexDeclaration::VertexDeclaration(VertexElementContainer_t elements)
	: _elements(elements)
	, _totalSize(0)
{
	for (auto element : elements)
		_totalSize += element.getElementSize();
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
VertexDeclaration::~VertexDeclaration()
{
	_elements.clear();
}

VertexElementContainer_t VertexDeclaration::getVertexElements() const
{
	return _elements;
}

VertexElement VertexDeclaration::getElementAtIndex(u32 index) const
{
	return _elements[index];
}

u32 VertexDeclaration::getElementCount() const
{
	return static_cast<u32>(_elements.size());
}

u32 VertexDeclaration::getTotalSize() const
{
	return _totalSize;
}

bool VertexDeclaration::hasElement(u32 stream, VertexElementSemantics semantic, VertexDataTypes dataType) const
{
	// Критерий поиска.
	auto pred = [stream, semantic, dataType](const VertexElement &element) {
		return element.stream == stream AND element.semantic == semantic AND element.dataType == dataType;
	};

	// Ищем элемент по критерию.
	auto iter = std::find_if(_elements.begin(), _elements.end(), pred);
	if (iter != _elements.end())
		return true;

	return false;
}


NAMESPACE_END(gl)
NAMESPACE_END(sway)