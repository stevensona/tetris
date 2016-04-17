#ifndef __board_h__
#define __board_h__

#include "taskmanager.h"
#include "config.h"

class board
{

private:
	int states[ BWIDTH ][ BHEIGHT ];
public:
	static board *instance();
	board();
	void clear();
	void render( taskmanager *tskmgr, SDL_Surface *surface, SDL_Rect *tile );
	int update( taskmanager *tskmgr ); //returns number of lines cleared
	int getBlock( int x, int y );
	void setBlock( int x, int y, int color );
private:
	static board *pInstance;
};

#endif