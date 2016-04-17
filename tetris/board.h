#pragma once

#include "StateManager.h"
#include "config.h"

class Board
{

private:
	int states[ BoardWidth ][ BoardHeight ];
public:

	Board();
	void render( StateManager *tskmgr, SDL_Surface *surface, SDL_Rect *tile );
	int update( StateManager *tskmgr ); //returns number of lines cleared
	int getBlock(int x, int y) const;
	void setBlock( int x, int y, int color );

};
