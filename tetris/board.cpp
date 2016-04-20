#include "board.h"

Board::Board()
{
	for (int x = 0; x < BoardWidth; x++)
	{
		for (int y = 0; y < BoardHeight; y++)
		{
			states[x][y] = 0;
		}
	}
}

void Board::render( StateManager *mgr, SDL_Texture *surface, SDL_Rect *tile1 )
{

	SDL_Rect destTile;
	SDL_Rect srcTile;

	srcTile.w = tile1->w; srcTile.h = tile1->h; srcTile.y = tile1->y;
	destTile.w = tile1->w; destTile.h = tile1->h;

	for( int x = 0; x < BoardWidth; x++ )
	{
		for( int y = 0; y < BoardHeight; y++ )
		{
			if( states[ x ][ y ] != 0 )
			{
				destTile.x = 192 + 1 + 22 * x;
				destTile.y = 18 + 1 + 22 * y;
				srcTile.x = tile1->x + ( tile1->w + 1 ) * ( states[ x ][ y ] - 1 );
				SDL_RenderCopy(mgr->renderer, surface, &srcTile, &destTile);
			}

		}
	}

}

int Board::update()
{
	int cleared = 0;
	for( int y = BoardHeight - 1; y > -1; y-- )
	{
		bool full = true;
		for( int x = 0; x < BoardWidth; x++ )
			if( states[ x ][ y ] == 0 )
				full = false;
		if( full == true )
		{
			cleared++;
			for( int k = y; k > 0; k-- )
				for( int x = 0; x < BoardWidth; x++ )
				{
					states[ x ][ k ] = states[ x ][ k - 1 ];
					states[ x ][ k - 1 ] = 0;
				}
			y++;
		}
	}
	return cleared;
}

int Board::getBlock(int x, int y) const
{
	if( x > -1 && x < BoardWidth  && y > -1 && y < BoardHeight )
		return states[ x ][ y ];
	else
		return 0;
}

void Board::setBlock( int x, int y, int color )
{

	if( x > -1 && x < BoardWidth  && y > -1 && y < BoardHeight )
		states[ x ][ y ] = color;

}