#include "bufferobject.h"
#include "buffertarget.h"
#include "bufferusage.h"
#include "bufferaccess.h"
#include "extensions.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum BufferObject::translateTargetToGLenum(u32 target) {
	switch (target) {
	case kBufferTarget_Array: return GL_ARRAY_BUFFER_ARB;
	case kBufferTarget_ElementArray: return GL_ELEMENT_ARRAY_BUFFER_ARB;
	default: return INVALID_TYPE;
	}
}

GLenum BufferObject::translateUsageToGLenum(u32 usage) {
	switch (usage) {
	case kBufferUsage_Static: return GL_STATIC_DRAW_ARB;
	case kBufferUsage_Dynamic: return GL_DYNAMIC_DRAW_ARB;
	case kBufferUsage_Stream: return GL_STREAM_DRAW_ARB;
	default: return INVALID_TYPE;
	}
}

GLenum BufferObject::translateAccessToGLenum(u32 access) {
	switch (access) {
	case kBufferAccess_Read: return GL_READ_ONLY_ARB;
	case kBufferAccess_Write: return GL_WRITE_ONLY_ARB;
	case kBufferAccess_ReadWrite: return GL_READ_WRITE_ARB;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Создает аппаратный буфер.
 */
BufferObject *BufferObject::create(const BufferCreateInfo &info) {
	BufferObject *instance = new BufferObject(info.description);
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
BufferObject::BufferObject(const BufferDescription &desc)
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
BufferObject::~BufferObject() {
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
bool BufferObject::allocate(const void *data) {
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
 *   updateSubdata(const void *)
 */
void BufferObject::updateSubdata(u32 offset, u32 size, const void *source) {
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
 *   updateSubdata(u32, u32, const void *)
 */
void BufferObject::updateSubdata(const void *source) {
	updateSubdata(0, _capacity * _byteStride, source);
}

void *BufferObject::map() {
	Extensions::glBindBufferARB(_target, _resourceHandle);
	GLvoid *mapped = Extensions::glMapBufferARB(_target, GL_WRITE_ONLY_ARB);
	if (NOT mapped)
		return NULL;
	Extensions::glBindBufferARB(_target, 0);

	return mapped;
}

void BufferObject::unmap() {
	Extensions::glBindBufferARB(_target, _resourceHandle);
	Extensions::glUnmapBufferARB(_target);
	Extensions::glBindBufferARB(_target, 0);
}

/*!
 * \brief
 *   Делает буфер текущим.
 * 
 * \sa
 *   unbind()
 */
void BufferObject::bind() {
	Extensions::glBindBufferARB(_target, _resourceHandle);
}

/*!
 * \brief
 *   Делает текущим пустой буфер.
 * 
 * \sa
 *   bind()
 */
void BufferObject::unbind() {
	Extensions::glBindBufferARB(_target, 0);
}

/*!
 * \brief
 *   Получает выделенный размер данных.
 */
u32 BufferObject::getAllocedSize() const {
	return _allocedSize;
}

/*!
 * \brief
 *   Устанавливает целевой тип буфера.
 * 
 * \param[in] target
 *   Целевой тип буфера.
 */
void BufferObject::setTarget(u32 target) {
	_target = BufferObject::translateTargetToGLenum(target);
}

/*!
 * \brief
 *   Получает целевой тип буфера.
 */
u32 BufferObject::getTarget() const {
	switch (_target) {
	case GL_ARRAY_BUFFER_ARB: return kBufferTarget_Array;
	case GL_ELEMENT_ARRAY_BUFFER_ARB: return kBufferTarget_ElementArray;
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
void BufferObject::setUsage(u32 usage) {
	_usage = BufferObject::translateUsageToGLenum(usage);
}

/*!
 * \brief
*   Получает режим работы с данными.
 */
u32 BufferObject::getUsage() const {
	switch (_usage) {
	case GL_STATIC_DRAW_ARB: return kBufferUsage_Static;
	case GL_DYNAMIC_DRAW_ARB: return kBufferUsage_Dynamic;
	case GL_STREAM_DRAW_ARB: return kBufferUsage_Stream;
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
void BufferObject::setCapacity(s32 capacity) {
	_capacity = capacity;
}

/*!
 * \brief
 *   Получает количество элементов в массиве.
 */
s32 BufferObject::getCapacity() const {
	return _capacity;
}

/*!
 * \brief
 *   Устанавливает размер структуры данных.
 * 
 * \param[in] byteStride
 *   Размер структуры.
 */
void BufferObject::setByteStride(s32 byteStride) {
	_byteStride = byteStride;
}

/*!
 * \brief
 *   Получает размер структуры данных.
 */
s32 BufferObject::getByteStride() const {
	return _byteStride;
}

/*!
 * \brief
 *   Устанавливает тип данных.
 * 
 * \param[in] type
 *   Тип данных.
 */
void BufferObject::setDataType(u32 type) {
	_datatype = type;
}

/*!
 * \brief
 *   Получает тип данных.
 * 
 * \return
 *   Тип данных.
 */
u32 BufferObject::getDataType() const {
	return _datatype;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)