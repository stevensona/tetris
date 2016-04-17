#pragma once

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

private:
	static title *pInstance;

};
