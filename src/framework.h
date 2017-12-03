#ifndef SWAY_FRAMEWORK_H
#define SWAY_FRAMEWORK_H

#include "foundation/context.h"
#include "graphics/graphics.h"
#include "game/gamestatemachine.h"

#include "defines.h"
#include "types.h"

NAMESPACE_BEGIN(sway)

class Framework : public foundation::Context {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Framework();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~Framework();

	void start(game::GameState *state);

	void update();

private:
	boost::shared_ptr<graphics::RenderSubsystem> _renderSubsystem;
	boost::shared_ptr<graphics::RenderQueue> _renderQueue;

	game::GameStateMachine *_finiteStateMachine;
};

NAMESPACE_END(sway)

#endif // SWAY_FRAMEWORK_H