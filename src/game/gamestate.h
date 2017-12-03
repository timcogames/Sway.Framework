#ifndef SWAY_GAME_GAMESTATE_H
#define SWAY_GAME_GAMESTATE_H

#include "gamestatemachine.h"
#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class GameState {
public:
	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~GameState() = default;

	/*!
	 * \brief
	 *   Выполняться при входе в состояние.
	 */
	virtual void enter() = 0;

	/*!
	 * \brief
	 *   Выполняться при выходе из состояния.
	 */
	virtual void exit() = 0;

	virtual void pause() = 0;

	virtual void resume() = 0;

	/*!
	 * \brief
	 *   Вызывается в текущем состоянии FSM на каждом этапе обновления.
	 */
    virtual void update() = 0;

	/*!
	 * \brief
	 *   Устанавливает контекст.
	 * 
	 * \param[in] context
	 *   Указатель на контекст.
	 */
	void setContext(foundation::Context *context) {
		_context = context;
	}

	/*!
	 * \brief
	 *   Получает подсистему.
	 */
	template <class type_t>
	type_t *getSubsystem() const {
		return static_cast<type_t *>(_context->getObject(type_t::getObjectMetadata()->getClassName()));
	}

private:
	foundation::Context *_context; /*!< Контекст. */
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif // SWAY_GAME_GAMESTATE_H