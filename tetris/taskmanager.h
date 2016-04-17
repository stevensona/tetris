#ifndef __taskmanager_h__
#define __taskmanager_h__



#include "SDL.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <vector>


#include "config.h"
#include "utility.h"

class task;

class taskmanager
{

private:
	std::vector< task* > mTasks;
	bool mRunning;

	TTF_Font *bkFont;

	bool mTaskUpdated;
	bool initText();
	void closeText();

	

public:
	taskmanager(){}
	int init();
	void cleanUp();

	void changeTask( task *tsk );
	void pushTask( task *tsk );
	void popTask();

	void update();
	void draw();

	bool running()
	{
		return mRunning;
	}

	void quit()
	{
		mRunning = false;
	}



	void printString( const char *text, SDL_Rect *destrect, SDL_Color color );

	SDL_Surface *screen;

};

#endif