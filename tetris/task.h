#ifndef __task_h__
#define __task_h__

#include "taskmanager.h"

class task
{

protected:
	task(){}

public:

	virtual void init() = 0;
	virtual void cleanUp() = 0;

	virtual void resume() = 0;
	virtual void pause() = 0;

	virtual void update( taskmanager *tskmgr ) = 0;
	virtual void draw( taskmanager *tskmgr ) = 0;

	void changeTask( taskmanager *tskmgr, task *tsk )
	{
		tskmgr->changeTask( tsk );
	}

};

#endif