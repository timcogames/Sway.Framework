#include "hardwarebuffer.h"
#include "hardwarebufferusageutils.h"
#include "hardwarebuffertargetutils.h"
#include "primitivetopologyutils.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

PFNGLGENBUFFERSARBPROC glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) glXGetProcAddressARB((const GLubyte*) "glGenBuffersARB");
PFNGLBINDBUFFERARBPROC glBindBufferARB = (PFNGLBINDBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glBindBufferARB");
PFNGLBUFFERDATAARBPROC glBufferDataARB = (PFNGLBUFFERDATAARBPROC) glXGetProcAddressARB((const GLubyte*) "glBufferDataARB");
PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetBufferParameterivARB");
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) glXGetProcAddressARB((const GLubyte*) "glDeleteBuffersARB");
PFNGLISBUFFERARBPROC glIsBufferARB = (PFNGLISBUFFERARBPROC) glXGetProcAddressARB((const GLubyte*) "glIsBufferARB");
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) glXGetProcAddressARB((const GLubyte*) "glBufferSubDataARB");

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
HardwareBuffer::HardwareBuffer(HardwareBufferTargets target)
	: _target(HardwareBufferTargetUtils::toGL(target))
	, _bufferId(0)
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
 *   Создает буфер.
 * 
 * \list
 *   \i Генерируем буфер.
 *   \i Делаем буфер текущим.
 *   \i Передать данные в аппаратный буфер.
 * \endlist
 * 
 * \param createInfo[in]
 *   Начальная информация.
 */
void HardwareBuffer::create(const HardwareBufferCreateInfo &createInfo)
{
	setByteStride(createInfo.byteStride);
	setCapacity(createInfo.capacity);

	s32 dataSize = _capacity * _byteStride;

	glGenBuffersARB(1, &_bufferId);
	glBindBufferARB(_target, _bufferId);
	glBufferDataARB(_target, dataSize, createInfo.data, HardwareBufferUsageUtils::toGL(createInfo.usage));

	int bufferSize = 0;
	glGetBufferParameterivARB(_target, GL_BUFFER_SIZE_ARB, &bufferSize);
	if (dataSize != bufferSize) {
		glDeleteBuffersARB(1, &_bufferId);
		_bufferId = 0;
	}
}

/*!
 * \brief
 *   Удаляет аппаратный буфер.
 */
void HardwareBuffer::destroy()
{
	if (glIsBufferARB(_bufferId))
		glDeleteBuffersARB(1, &_bufferId);
}

void HardwareBuffer::updateSubData(u32 offset, u32 size, const void *source)
{
	if (glIsBufferARB(_bufferId)) {
		glBindBufferARB(_target, _bufferId);
		glBufferSubDataARB(_target, offset, size, source);
		glBindBufferARB(_target, 0);
	}
}

void HardwareBuffer::updateSubData(const void *source)
{
	updateSubData(0, _capacity * _byteStride, source);
}

/*!
 * \brief
 *   Делает буфер текущим.
 */
void HardwareBuffer::bind()
{

}

/*!
 * \brief
 *   Делает текущим пустой буфер.
 */
void HardwareBuffer::unbind()
{

}

void HardwareBuffer::drawPrimitives(PrimitiveTopologies topology, u32 first, u32 count)
{

}

void HardwareBuffer::drawIndexedPrimitives(PrimitiveTopologies topology, HardwareBuffer *ibo, DataTypeInfo::Types dataType)
{	
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, ibo->getObjectHandle());

	glDrawElements(PrimitiveTopologyUtils::toGL(topology), ibo->getCapacity(), DataTypeInfo::toGL(dataType), NULL);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}

u32 HardwareBuffer::getObjectHandle() const
{
	return _bufferId;
}

void HardwareBuffer::setCapacity(s32 capacity)
{
	_capacity = capacity;
}

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