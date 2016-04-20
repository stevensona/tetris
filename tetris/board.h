#pragma once

#include "StateManager.h"
#include "config.h"

class Board
{

private:
	int states[ BoardWidth ][ BoardHeight ];
public:

	Board();
	void render( StateManager *mgr, SDL_Texture *surface, SDL_Rect *tile );
	int update(); //returns number of lines cleared
	int getBlock(int x, int y) const;
	void setBlock( int x, int y, int color );

};
