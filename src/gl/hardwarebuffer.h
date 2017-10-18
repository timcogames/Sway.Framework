#ifndef SWAY_GL_HARDWAREBUFFER_H
#define SWAY_GL_HARDWAREBUFFER_H

#include "hardwarebuffercreateinfo.h"
#include "hardwarebuffertargets.h"
#include "primitivetopologies.h"
#include "datatypeinfo.h"

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class HardwareBuffer
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] target
	 *   Тип данных.
	 */
	HardwareBuffer(HardwareBufferTargets target);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~HardwareBuffer();

	/*!
	 * \brief
	 *   Создает аппаратный буфер.
	 * 
	 * \param[in] createInfo
	 *   Начальная информация.
	 */
	void create(const HardwareBufferCreateInfo &createInfo);
	
	/*!
	 * \brief
	 *   Удаляет аппаратный буфер.
	 */
	void destroy();

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

	void updateSubdata(const void *source);

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

	void drawPrimitives(PrimitiveTopologies topology, u32 first, u32 count);

	void drawIndexedPrimitives(PrimitiveTopologies topology, HardwareBuffer *ibo, DataTypeInfo::Types dataType);

	HardwareBufferHandle_t getObjectHandle() const;

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

	void setByteStride(s32 byteStride);
	
	s32 getByteStride() const;

private:
	u32 _target;
	HardwareBufferHandle_t _bufferHandle; /*!< Идентификатор буфера. */

	s32 _capacity;
	s32 _byteStride;

	PrimitiveTopologies _topology;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFER_H