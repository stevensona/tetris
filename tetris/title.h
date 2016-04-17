#ifndef __title_h__
#define __title_h__

#include "task.h"

class title : public task
{

private:
	SDL_Surface *titleScreen;

public:
	static title *instance();
	void init();
	void cleanUp();

	void resume();
	void pause();

	void update( taskmanager *tskmgr );
	void draw( taskmanager *tskmgr );

	void changeTask( taskmanager *tskmgr, task *tsk );

private:
	static title *pInstance;

};


#endif