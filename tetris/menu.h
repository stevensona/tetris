#ifndef __menu_h__
#define __menu_h__

#include "task.h"

class menu : public task
{

private:

	SDL_Rect b1u, b2u, b3u; //Source rect up
	SDL_Rect b1d, b2d, b3d; //Source rect down
	SDL_Rect b1t, b2t, b3t; //Target rect

	SDL_Surface *menuBackground;
	SDL_Surface *menuButtons;

	Mix_Chunk *sndMove;
	Mix_Chunk *sndSelect;

	int selection;

public:
	static menu *instance();
	void init();
	void cleanUp();

	void resume();
	void pause();

	void update( taskmanager *tskmgr );
	void draw( taskmanager *tskmgr );

private:
	static menu *pInstance;
};
#endif