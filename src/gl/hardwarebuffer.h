#ifndef SWAY_GL_HARDWAREBUFFER_H
#define SWAY_GL_HARDWAREBUFFER_H

#include "hardwarebufferdescription.h"
#include "hardwarebuffertargets.h"
#include "primitivetopologies.h"
#include "datatypeinfo.h"

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class HardwareBuffer {
public:
	static GLenum getGLTarget(u32 target);

	static GLenum getGLUsage(u32 usage);

	static HardwareBuffer *create(const HardwareBufferCreateInfo &info);

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	HardwareBuffer(const HardwareBufferDescription &desc);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~HardwareBuffer();

	/*!
	 * \brief
	 *   Устанавливает данные в аппаратный буфер.
	 * 
	 * \param[in] data
	 *   Первоначальный данные.
	 */
	b32 allocate(const void *data);

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
	void updateSubdata(u32 offset, u32 size, const void *source);

	/*!
	 * \brief
	 *   Изменяет данные в уже существующем буфере.
	 * 
	 * \param[in] source
	 *   Область памяти, содержащая новые значения.
	 */
	void updateSubdata(const void *source);

	void *map();

	void unmap();

	/*!
	 * \brief
	 *   Делает буфер текущим.
	 */
	void bind();

	/*!
	 * \brief
	 *   Делает текущим пустой буфер.
	 */
	void unbind();

	/*!
	 * \brief
	 *   Получает дескриптор буфера.
	 */
	HardwareBufferHandle_t getBufferHandle() const;

	/*!
	 * \brief
	 *   Получает выделенный размер данных.
	 */
	u32 getAllocedSize() const;

	/*!
	 * \brief
	 *   Устанавливает целевой тип буфера.
	 * 
	 * \param[in] target
	 *   Целевой тип буфера.
	 */
	void setTarget(u32 target);

	/*!
	 * \brief
	 *   Получает целевой тип буфера.
	 */
	u32 getTarget() const;

	/*!
	 * \brief
	 *   Устанавливает режим работы с данными.
	 * 
	 * \param[in] usage
	 *   Режим работы.
	 */
	void setUsage(u32 usage);
	
	/*!
	* \brief
	*   Получает режим работы с данными.
	*/
	u32 getUsage() const;

	/*!
	 * \brief
	 *   Устанавливает количество элементов в массиве.
	 * 
	 * \param[in] capacity
	 *   Количество элементов в массиве.
	 */
	void setCapacity(s32 capacity);

	/*!
	 * \brief
	 *   Получает количество элементов в массиве.
	 */
	s32 getCapacity() const;

	/*!
	 * \brief
	 *   Устанавливает размер структуры данных.
	 * 
	 * \param[in] byteStride
	 *   Размер структуры.
	 */
	void setByteStride(s32 byteStride);
	
	/*!
	 * \brief
	 *   Получает размер структуры данных.
	 */
	s32 getByteStride() const;

	/*!
	 * \brief
	 *   Устанавливает тип данных.
	 * 
	 * \param[in] type
	 *   Тип данных.
	 */
	void setDataType(u32 type);
	
	/*!
	 * \brief
	 *   Получает тип данных.
	 */
	u32 getDataType() const;

private:
	HardwareBufferHandle_t _bufferHandle; /*!< Идентификатор буфера. */
	s32 _allocedSize;
	u32 _target;
	u32 _usage;
	s32 _capacity;
	s32 _byteStride;
	u32 _datatype;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFER_H