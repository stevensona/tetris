#pragma once
#include <memory>
#include "StateManager.h"

class State
{

public:

	virtual void resume() = 0;
	virtual void pause() = 0;

	virtual void update(StateManager* tskmgr) = 0;
	virtual void draw(StateManager* tskmgr) = 0;

	void changeTask(StateManager& tskmgr, std::shared_ptr<State> tsk )
	{
		tskmgr.change(tsk);
	}

};
