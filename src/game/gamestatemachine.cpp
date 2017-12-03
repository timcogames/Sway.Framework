#include "gamestatemachine.h"
#include "gamestate.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(game)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
GameStateMachine::GameStateMachine() = default;

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
GameStateMachine::~GameStateMachine() {
	while (NOT _states.empty()) {
		_states.back()->exit();
		_states.pop_back();
	}
}

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
void GameStateMachine::changeState(GameState *state, foundation::Context *context) {
	while (NOT _states.empty()) {
		_states.back()->exit();
		_states.pop_back();
	}

	_states.push_back(state);
	_states.back()->setContext(context);
	_states.back()->enter();
}

void GameStateMachine::pushState(GameState *state, foundation::Context *context) {
	if (NOT _states.empty())
		_states.back()->pause();

	_states.push_back(state);
	_states.back()->setContext(context);
	_states.back()->enter();
}

void GameStateMachine::popState() {
	while (NOT _states.empty()) {
		_states.back()->exit();
		_states.pop_back();
	}

	if (NOT _states.empty())
		_states.back()->resume();
}

void GameStateMachine::update() {
	_states.back()->update();
}

NAMESPACE_END(game)
NAMESPACE_END(sway)