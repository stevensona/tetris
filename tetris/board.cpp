#include "board.h"

board *board::pInstance = 0;

board *board::instance()
{
	if( pInstance == 0 )
		pInstance = new board();

	return pInstance;
}

board::board()
{
	clear();
}

void board::clear()
{
	for( int x = 0; x < BWIDTH; x++ )
	{
		for( int y = 0; y < BHEIGHT; y++ )
		{
			states[ x ][ y ] = 0;
		}
	}
}

void board::render( taskmanager *tskmgr, SDL_Surface *surface, SDL_Rect *tile1 )
{

	SDL_Rect destTile;
	SDL_Rect srcTile;

	srcTile.w = tile1->w; srcTile.h = tile1->h; srcTile.y = tile1->y;
	destTile.w = tile1->w; destTile.h = tile1->h;

	for( int x = 0; x < BWIDTH; x++ )
	{
		for( int y = 0; y < BHEIGHT; y++ )
		{
			if( states[ x ][ y ] != 0 )
			{
				destTile.x = 192 + 1 + 22 * x;
				destTile.y = 18 + 1 + 22 * y;
				srcTile.x = tile1->x + ( tile1->w + 1 ) * ( states[ x ][ y ] - 1 );
				SDL_BlitSurface( surface, &srcTile, tskmgr->screen, &destTile );
			}

		}
	}

}

int board::update( taskmanager *tskmgr )
{
	int cleared = 0;
	for( int y = BHEIGHT - 1; y > -1; y-- )
	{
		bool full = true;
		for( int x = 0; x < BWIDTH; x++ )
			if( states[ x ][ y ] == 0 )
				full = false;
		if( full == true )
		{
			cleared++;
			for( int k = y; k > 0; k-- )
				for( int x = 0; x < BWIDTH; x++ )
				{
					states[ x ][ k ] = states[ x ][ k - 1 ];
					states[ x ][ k - 1 ] = 0;
				}
			y++;
		}
	}
	return cleared;
}

int board::getBlock( int x, int y )
{
	if( x > -1 && x < BWIDTH  && y > -1 && y < BHEIGHT )
		return states[ x ][ y ];
	else
		return 0;
}

void board::setBlock( int x, int y, int color )
{

	if( x > -1 && x < BWIDTH  && y > -1 && y < BHEIGHT )
		states[ x ][ y ] = color;

}