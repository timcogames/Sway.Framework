#include "hardwarebuffer.h"
#include "hardwarebufferusageutils.h"
#include "hardwarebuffertargetutils.h"
#include "primitivetopologyutils.h"
#include "extensions.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 * 
 * \param[in] target
 *   Тип данных.
 */
HardwareBuffer::HardwareBuffer(HardwareBufferTargets target)
	: _target(HardwareBufferTargetUtils::toGL(target))
	, _bufferHandle(0)
	, _capacity(0)
	, _byteStride(0)
{
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
HardwareBuffer::~HardwareBuffer()
{
	// Empty
}

/*!
 * \brief
 *   Создает аппаратный буфер.
 * 
 * \param[in] createInfo
 *   Начальная информация.
 */
void HardwareBuffer::create(const HardwareBufferCreateInfo &createInfo)
{
	setByteStride(createInfo.byteStride);
	setCapacity(createInfo.capacity);

	s32 dataSize = _capacity * _byteStride;

	Extensions::glGenBuffersARB(1, &_bufferHandle);
	Extensions::glBindBufferARB(_target, _bufferHandle);
	Extensions::glBufferDataARB(_target, dataSize, createInfo.data, HardwareBufferUsageUtils::toGL(createInfo.usage));

	int bufferSize = 0;
	Extensions::glGetBufferParameterivARB(_target, GL_BUFFER_SIZE_ARB, &bufferSize);
	if (dataSize != bufferSize) {
		Extensions::glDeleteBuffersARB(1, &_bufferHandle);
		_bufferHandle = 0;
	}
}

/*!
 * \brief
 *   Удаляет аппаратный буфер.
 */
void HardwareBuffer::destroy()
{
	if (Extensions::glIsBufferARB(_bufferHandle))
		Extensions::glDeleteBuffersARB(1, &_bufferHandle);
}

/*!
 * \brief
 *   Изменяет данные в уже существующем буфере.
 * 
 * \param[in] offset
 *   Начало изменяемого блока данных.
 * 
 * \param[in] size
 *   Размер изменяемого блока данных.
 * 
 * \param[in] source
 *   Область памяти, содержащая новые значения.
 */
void HardwareBuffer::updateSubdata(u32 offset, u32 size, const void *source)
{
	if (Extensions::glIsBufferARB(_bufferHandle)) {
		Extensions::glBindBufferARB(_target, _bufferHandle);
		Extensions::glBufferSubDataARB(_target, offset, size, source);
		Extensions::glBindBufferARB(_target, 0);
	}
}

void HardwareBuffer::updateSubdata(const void *source)
{
	updateSubdata(0, _capacity * _byteStride, source);
}

/*!
 * \brief
 *   Делает буфер текущим.
 */
void HardwareBuffer::bind()
{
	Extensions::glBindBufferARB(_target, _bufferHandle);
}

/*!
 * \brief
 *   Делает текущим пустой буфер.
 */
void HardwareBuffer::unbind()
{
	Extensions::glBindBufferARB(_target, 0);
}

void HardwareBuffer::drawPrimitives(PrimitiveTopologies topology, u32 first, u32 count)
{
	glDrawArrays(PrimitiveTopologyUtils::toGL(topology), first, count);
}

void HardwareBuffer::drawIndexedPrimitives(PrimitiveTopologies topology, HardwareBuffer *ibo, DataTypeInfo::Types dataType)
{	
	Extensions::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, ibo->getObjectHandle());

	glDrawElements(PrimitiveTopologyUtils::toGL(topology), ibo->getCapacity(), DataTypeInfo::toGL(dataType), NULL);

	Extensions::glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}

HardwareBufferHandle_t HardwareBuffer::getObjectHandle() const
{
	return _bufferHandle;
}

/*!
 * \brief
 *   Устанавливает количество элементов в массиве.
 * 
 * \param[in] capacity
 *   Количество элементов в массиве.
 */
void HardwareBuffer::setCapacity(s32 capacity)
{
	_capacity = capacity;
}

/*!
 * \brief
 *   Получает количество элементов в массиве.
 */
s32 HardwareBuffer::getCapacity() const
{
	return _capacity;
}

void HardwareBuffer::setByteStride(s32 byteStride)
{
	_byteStride = byteStride;
}

s32 HardwareBuffer::getByteStride() const
{
	return _byteStride;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)