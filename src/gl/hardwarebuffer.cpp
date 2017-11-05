#include "hardwarebuffer.h"
#include "extensions.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum HardwareBuffer::getGLTarget(u32 target) {
	switch (target) {
	case kHardwareBufferTarget_Array: return GL_ARRAY_BUFFER_ARB;
	case kHardwareBufferTarget_ElementArray: return GL_ELEMENT_ARRAY_BUFFER_ARB;
	default: return INVALID_TYPE;
	}
}

GLenum HardwareBuffer::getGLUsage(u32 usage) {
	switch (usage) {
	case kHardwareBufferUsage_Static: return GL_STATIC_DRAW_ARB;
	case kHardwareBufferUsage_Dynamic: return GL_DYNAMIC_DRAW_ARB;
	case kHardwareBufferUsage_Stream: return GL_STREAM_DRAW_ARB;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Создает аппаратный буфер.
 */
HardwareBuffer *HardwareBuffer::create(const HardwareBufferCreateInfo &info) {
	HardwareBuffer *instance = new HardwareBuffer(info.description);
	if (instance->allocate(info.data)) return instance;
	SAFE_DELETE(instance);
	return 0;
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
HardwareBuffer::HardwareBuffer(const HardwareBufferDescription &desc)
	: _allocedSize(0) {

	setTarget(desc.target);
	setUsage(desc.usage);
	setByteStride(desc.byteStride);
	setCapacity(desc.capacity);
	setDataType(desc.datatype);

	/* Создает аппаратный буфер. */
	Extensions::glGenBuffersARB(1, &_resourceHandle);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
HardwareBuffer::~HardwareBuffer() {
	/* Удаляет аппаратный буфер. */
	Extensions::glDeleteBuffersARB(1, &_resourceHandle);
}

/*!
 * \brief
 *   Устанавливает данные в аппаратный буфер.
 * 
 * \param[in] data
 *   Первоначальный данные.
 */
bool HardwareBuffer::allocate(const void *data) {
	s32 dataSize = _capacity * _byteStride;

	Extensions::glBindBufferARB(_target, _resourceHandle);
	Extensions::glBufferDataARB(_target, dataSize, data, _usage);

	Extensions::glGetBufferParameterivARB(_target, GL_BUFFER_SIZE_ARB, &_allocedSize);
	if (_allocedSize != dataSize)
		return false;

	return true;
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
 * 
 * \sa
 *   HardwareBuffer::updateSubdata(const void *)
 */
void HardwareBuffer::updateSubdata(u32 offset, u32 size, const void *source) {
	if (Extensions::glIsBufferARB(_resourceHandle)) {
		Extensions::glBindBufferARB(_target, _resourceHandle);
		Extensions::glBufferSubDataARB(_target, offset, size, source);
		Extensions::glBindBufferARB(_target, 0);
	}
}

/*!
 * \brief
 *   Изменяет данные в уже существующем буфере.
 * 
 * \param[in] source
 *   Область памяти, содержащая новые значения.
 * 
 * \sa
 *   HardwareBuffer::updateSubdata(u32, u32, const void *)
 */
void HardwareBuffer::updateSubdata(const void *source) {
	updateSubdata(0, _capacity * _byteStride, source);
}

void *HardwareBuffer::map() {
	Extensions::glBindBufferARB(_target, _resourceHandle);
	GLvoid *mapped = Extensions::glMapBufferARB(_target, GL_WRITE_ONLY_ARB);
	if (NOT mapped)
		return NULL;
	Extensions::glBindBufferARB(_target, 0);

	return mapped;
}

void HardwareBuffer::unmap() {
	Extensions::glBindBufferARB(_target, _resourceHandle);
	Extensions::glUnmapBufferARB(_target);
	Extensions::glBindBufferARB(_target, 0);
}

/*!
 * \brief
 *   Делает буфер текущим.
 * 
 * \sa
 *   HardwareBuffer::unbind()
 */
void HardwareBuffer::bind() {
	Extensions::glBindBufferARB(_target, _resourceHandle);
}

/*!
 * \brief
 *   Делает текущим пустой буфер.
 * 
 * \sa
 *   HardwareBuffer::bind()
 */
void HardwareBuffer::unbind() {
	Extensions::glBindBufferARB(_target, 0);
}

/*!
 * \brief
 *   Получает выделенный размер данных.
 */
u32 HardwareBuffer::getAllocedSize() const {
	return _allocedSize;
}

/*!
 * \brief
 *   Устанавливает целевой тип буфера.
 * 
 * \param[in] target
 *   Целевой тип буфера.
 */
void HardwareBuffer::setTarget(u32 target) {
	_target = getGLTarget(target);
}

/*!
 * \brief
 *   Получает целевой тип буфера.
 */
u32 HardwareBuffer::getTarget() const {
	switch (_target) {
	case GL_ARRAY_BUFFER_ARB: return kHardwareBufferTarget_Array;
	case GL_ELEMENT_ARRAY_BUFFER_ARB: return kHardwareBufferTarget_ElementArray;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Устанавливает режим работы с данными.
 * 
 * \param[in] usage
 *   Режим работы.
 */
void HardwareBuffer::setUsage(u32 usage) {
	_usage = getGLUsage(usage);
}

/*!
 * \brief
*   Получает режим работы с данными.
 */
u32 HardwareBuffer::getUsage() const {
	switch (_usage) {
	case GL_STATIC_DRAW_ARB: return kHardwareBufferUsage_Static;
	case GL_DYNAMIC_DRAW_ARB: return kHardwareBufferUsage_Dynamic;
	case GL_STREAM_DRAW_ARB: return kHardwareBufferUsage_Stream;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Устанавливает количество элементов в массиве.
 * 
 * \param[in] capacity
 *   Количество элементов в массиве.
 */
void HardwareBuffer::setCapacity(s32 capacity) {
	_capacity = capacity;
}

/*!
 * \brief
 *   Получает количество элементов в массиве.
 */
s32 HardwareBuffer::getCapacity() const {
	return _capacity;
}

/*!
 * \brief
 *   Устанавливает размер структуры данных.
 * 
 * \param[in] byteStride
 *   Размер структуры.
 */
void HardwareBuffer::setByteStride(s32 byteStride) {
	_byteStride = byteStride;
}

/*!
 * \brief
 *   Получает размер структуры данных.
 */
s32 HardwareBuffer::getByteStride() const {
	return _byteStride;
}

/*!
 * \brief
 *   Устанавливает тип данных.
 * 
 * \param[in] type
 *   Тип данных.
 */
void HardwareBuffer::setDataType(u32 type) {
	_datatype = type;
}

/*!
 * \brief
 *   Получает тип данных.
 * 
 * \return
 *   Тип данных.
 */
u32 HardwareBuffer::getDataType() const {
	return _datatype;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)