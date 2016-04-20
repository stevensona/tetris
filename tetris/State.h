#pragma once
#include <memory>
#include "StateManager.h"

class State
{
protected:
	StateManager *owner;

public:

	virtual void resume() = 0;
	virtual void pause() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;

	void changeTask(StateManager& mgr, std::shared_ptr<State> tsk )	{
		mgr.change(tsk);
	}



};
