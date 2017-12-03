#ifndef SWAY_GAME_GAMESTATEMACHINE_H
#define SWAY_GAME_GAMESTATEMACHINE_H

#include "../foundation/context.h"
#include "../defines.h"

#include <vector> // std::vector

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

class GameState;
class GameStateMachine {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	GameStateMachine();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~GameStateMachine();

	/*!
	 * \brief
	 *   Изменяет текущее состояние на новое.
	 * 
	 * \param[in] state
	 *   Указатель на новое состояние.
	 * 
	 * \param[in] context
	 *   Указатель на контекст.
	 */
	void changeState(GameState *state, foundation::Context *context);

	void pushState(GameState *state, foundation::Context *context);

	void popState();

	void update();

private:
	std::vector<GameState *> _states;
};

NAMESPACE_END(game)
NAMESPACE_END(sway)

#endif // SWAY_GAME_GAMESTATEMACHINE_H