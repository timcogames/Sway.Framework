#ifndef SWAY_GL_HARDWAREBUFFER_H
#define SWAY_GL_HARDWAREBUFFER_H

#include "hardwarebuffercreateinfo.h"
#include "hardwarebuffertargets.h"
#include "primitivetopologies.h"
#include "datatypeinfo.h"

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

#define BUFFER_OFFSET(x)((char*)NULL + (x))

class HardwareBuffer
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
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
	 * \list
	 *   \i Генерируем буфер.
	 *   \i Делаем буфер текущим.
	 *   \i Передать данные в аппаратный буфер.
	 * \endlist
	 * 
	 * \param createInfo[in]
	 *   Начальная информация.
	 */
	void create(const HardwareBufferCreateInfo &createInfo);
	
	/*!
	 * \brief
	 *   Удаляет аппаратный буфер.
	 */
	void destroy();
	
	void updateSubData(u32 offset, u32 size, const void *source);

	void updateSubData(const void *source);

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

	u32 getObjectHandle() const;

	void setCapacity(s32 capacity);
	s32 getCapacity() const;

	void setByteStride(s32 byteStride);
	s32 getByteStride() const;

private:
	u32 _target;
	u32 _bufferId; /*!< Идентификатор буфера. */

	s32 _capacity;
	s32 _byteStride;

	PrimitiveTopologies _topology;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFER_H