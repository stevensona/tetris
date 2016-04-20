#include "piece.h"

Piece::Piece(Board* board) : board(board), level(500) {
	reset( getRandomPiece( -1 ) );
}

int Piece::getTarget()
{
	int real = posY;
	int targ = posY;
	while( !getCollision() )
		posY++;
	targ = posY - 1;
	posY = real;
	return targ;
}
void Piece::levelUp()
{
	if( level > 50 )
		level -= 50;
}

int Piece::getLevel()
{
	return ( ( 500 - level ) / 50 ) + 1;
}

int Piece::getWidth()
{
	return getMaxX() - getMinX();
}

int Piece::getHeight()
{
	return getMaxY() - getMinY();
}

int Piece::getMaxX()
{
	int max = 0;
	for( int x = 0; x < 4; x++ )
		for( int y = 0; y < 4; y++ )
			if( shape[ x ][ y ] != 0 )
				if( x > max )
					max = x;
	return max;
	
}

int Piece::getMaxY()
{
	int max = 0;
	for( int y = 0; y < 4; y++ )
		for( int x = 0; x < 4; x++ )
			if( shape[ x ][ y ] != 0 )
				if( y > max )
					max = y;
	return max;
}


int Piece::getMinX()
{
	int min = 3;
	for( int x = 3; x > -1; x-- )
		for( int y = 3; y > -1; y-- )
			if( shape[ x ][ y ] != 0 )
				if( x < min )
					min = x;
	return min;
	
}

int Piece::getMinY()
{
	int min = 3;
	for( int y = 3; y > -1; y-- )
		for( int x = 3; x > -1; x-- )
			if( shape[ x ][ y ] != 0 )
				if( y < min )
					min = y;
	return min;
}

bool Piece::getCollision()
{

	for( int x = 0; x < 4; x++ )
		for( int y = 0; y < 4; y++ )
			if(board->getBlock( posX + x, posY + y ) != 0 &&
				shape[ x ][ y ] != 0)
				return true;
	if( posY + getMaxY() >= BoardHeight ) return true;


	return false;

}

bool Piece::update()
{
	int oPosX = posX;
	if( posX + getMinX() < 0 )
		posX = 0 - getMinX();
	if( posX + getMaxX() > BoardWidth - 1 )
		posX = BoardWidth - 1 - getMaxX();
	if( getCollision() ) posX = oPosX;

	int oPosY = posY;
	if( posY + getMaxY() > BoardHeight - 1 )
		posY = BoardHeight - 1 - getMaxY();
	if( posY + getMinY() < 0 )
		posY = 0 - getMinY();
	if( getCollision() ) posY = oPosY;



	if( SDL_GetTicks() - lastDrop > level ) 	{ //Time to make me fall!
		if( posY + getMaxY() < BoardHeight - 1 ) {
			posY++;
			if( getCollision() ) {
				posY--;

			} else {
				lastDrop = SDL_GetTicks();
				lastMove = SDL_GetTicks();
				freeFall++;
			}
		}

	}

	if( SDL_GetTicks() - lastMove > 500 )
	{
		addToBoard();
		return false;
	}

	return true;

}

int Piece::getFreeFall()
{
	return freeFall;
}

void Piece::render(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *tile1 )
{

	SDL_Rect destTile;
	SDL_Rect srcTile;

	srcTile.w = tile1->w; srcTile.h = tile1->h; srcTile.y = tile1->y;
	destTile.w = tile1->w; destTile.h = tile1->h;

	for( int x = 0; x < 4; x++ )
	{
		for( int y = 0; y < 4; y++ )
		{
			if( shape[ x ][ y ] != 0 )
			{
				destTile.x = 192 + 1 + 22 * posX + 22 * x;
				destTile.y = 18 + 1 + 22 * posY + 22 * y;
				srcTile.x = tile1->x + ( tile1->w + 1 ) * ( shape[ x ][ y ] - 1 );
				SDL_RenderCopy(renderer, texture, &srcTile, &destTile);
			}

		}
	}

}

void Piece::rotate()
{
	int temp[ 4 ][ 4 ];
	for( int x = 0; x < 4; x++ )
		for( int y = 0; y < 4; y++ ) {
			temp[ x ][ y ] = shape[ x ][ y ];
			shape[ x ][ y ] = 0;
		}

	rotation++;
	if( rotation > 3 )
		rotation = 0;
	switch( shapeID )
	{
	case shpT:
		if( rotation == 0 )	{
			shape[2][1] = 3;
			shape[1][1] = 3;
			shape[3][1] = 3;
			shape[2][2] = 3;
		} else if( rotation == 1 ) {
			shape[2][1] = 3;
			shape[2][0] = 3;
			shape[2][2] = 3;
			shape[3][1] = 3;
		} else if( rotation == 2 ) {
			shape[2][1] = 3;
			shape[2][0] = 3;
			shape[3][1] = 3;
			shape[1][1] = 3;
		} else if( rotation == 3 ) {
			shape[2][1] = 3;
			shape[1][1] = 3;
			shape[2][0] = 3;
			shape[2][2] = 3;
		}
		break;

	case shpL:
		if( rotation == 0 ) {
			shape[2][1] = 1;
			shape[1][1] = 1;
			shape[1][2] = 1;
			shape[3][1] = 1;
		} else if( rotation == 1 ) {
			shape[2][1] = 1;
			shape[2][0] = 1;
			shape[2][2] = 1;
			shape[3][2] = 1;
		} else if( rotation == 2 ) {
			shape[2][1] = 1;
			shape[1][1] = 1;
			shape[3][1] = 1;
			shape[3][0] = 1;
		} else if( rotation == 3 ) {
			shape[2][1] = 1;
			shape[2][0] = 1;
			shape[1][0] = 1;
			shape[2][2] = 1;
		}
		break;

	case shpJ:
		if( rotation == 0 ) {
			shape[2][1] = 2;
			shape[1][1] = 2;
			shape[3][2] = 2;
			shape[3][1] = 2;
		} else if( rotation == 1 ) {
			shape[2][1] = 2;
			shape[2][0] = 2;
			shape[3][0] = 2;
			shape[2][2] = 2;
		} else if( rotation == 2 ) {
			shape[2][1] = 2;
			shape[1][1] = 2;
			shape[3][1] = 2;
			shape[1][0] = 2;
		} else if( rotation == 3 ) {
			shape[2][1] = 2;
			shape[2][0] = 2;
			shape[2][2] = 2;
			shape[1][2] = 2;
		}
		break;

	case shpO:
		shape[2][1] = 4;
		shape[1][1] = 4;
		shape[1][2] = 4;
		shape[2][2] = 4;
		break;

	case shpS:
		if( rotation == 0 ) {
			shape[2][1] = 6;
			shape[3][1] = 6;
			shape[2][2] = 6;
			shape[1][2] = 6;
		} else if( rotation == 1 ) {
			shape[2][1] = 6;
			shape[2][0] = 6;
			shape[3][1] = 6;
			shape[3][2] = 6;
		} else if( rotation == 2 ) {
			shape[2][1] = 6;
			shape[3][1] = 6;
			shape[2][2] = 6;
			shape[1][2] = 6;
		} else if( rotation == 3 ) {
			shape[2][1] = 6;
			shape[2][0] = 6;
			shape[3][1] = 6;
			shape[3][2] = 6;
		}
		break;

	case shpZ:
		if( rotation == 0 )
		{
			shape[2][1] = 7;
			shape[1][1] = 7;
			shape[2][2] = 7;
			shape[3][2] = 7;
		}
		if( rotation == 1 )
		{
			shape[2][1] = 7;
			shape[3][1] = 7;
			shape[3][0] = 7;
			shape[2][2] = 7;
		}
		if( rotation == 2 )
		{
			shape[2][1] = 7;
			shape[1][1] = 7;
			shape[2][2] = 7;
			shape[3][2] = 7;
		}
		if( rotation == 3 )
		{
			shape[2][1] = 7;
			shape[3][1] = 7;
			shape[3][0] = 7;
			shape[2][2] = 7;
		}
		break;

	case shpI:
		if( rotation == 0 )
		{
			shape[2][1] = 5;
			shape[1][1] = 5;
			shape[3][1] = 5;
			shape[0][1] = 5;
		}
		if( rotation == 1 )
		{
			shape[2][1] = 5;
			shape[2][0] = 5;
			shape[2][2] = 5;
			shape[2][3] = 5;
		}
		if( rotation == 2 )
		{
			shape[2][1] = 5;
			shape[1][1] = 5;
			shape[3][1] = 5;
			shape[0][1] = 5;
		}
		if( rotation == 3 )
		{
			shape[2][1] = 5;
			shape[2][0] = 5;
			shape[2][2] = 5;
			shape[2][3] = 5;
		}
		break;
	}

	if( getCollision() )
		posY--;

	if( getCollision() )
	{
		posY++;
		for( int x = 0; x < 4; x++ )
			for( int y = 0; y < 4; y++ )
				shape[ x ][ y ] = temp[ x ][ y ];

		rotation--;
		if( rotation < 3 )
			rotation = 3;
	}
	else
		lastMove = SDL_GetTicks();

}

bool Piece::reset( int id )
{
	freeFall = 0;
	rotation = 0;
	posX = 3;
	posY = -1;
	lastMove = SDL_GetTicks();
	lastDrop = lastMove;
	for( int x = 0; x < 4; x++ )
		for( int y = 0; y < 4; y++ )
			shape[ x ][ y ] = 0;

	switch( id )
	{
	case shpT:
		shape[2][1] = 3;
		shape[1][1] = 3;
		shape[3][1] = 3;
		shape[2][2] = 3;
		break;
	case shpL:
		shape[2][1] = 1;
		shape[1][1] = 1;
		shape[1][2] = 1;
		shape[3][1] = 1;
		break;
	case shpJ:
		shape[2][1] = 2;
		shape[1][1] = 2;
		shape[3][2] = 2;
		shape[3][1] = 2;
		break;
	case shpO:
		shape[2][1] = 4;
		shape[1][1] = 4;
		shape[1][2] = 4;
		shape[2][2] = 4;
		break;
	case shpS:
		shape[2][1] = 6;
		shape[3][1] = 6;
		shape[2][2] = 6;
		shape[1][2] = 6;
		break;
	case shpZ:
		shape[2][1] = 7;
		shape[1][1] = 7;
		shape[2][2] = 7;
		shape[3][2] = 7;
		break;
	case shpI:
		shape[2][1] = 5;
		shape[1][1] = 5;
		shape[3][1] = 5;
		shape[0][1] = 5;
		break;
	}
	shapeID = id;
	if( getCollision() ) return false;
	return true;

}

void Piece::renderTarget(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *tile1) {

	SDL_Rect destTile;
	SDL_Rect srcTile;
	int targY = getTarget();
	srcTile.w = tile1->w; srcTile.h = tile1->h; srcTile.y = tile1->y;
	destTile.w = tile1->w; destTile.h = tile1->h;
	//TODO make slightly transparent
	SDL_SetTextureAlphaMod( texture, 128 );
	for( int x = 0; x < 4; x++ )
	{
		for( int y = 0; y < 4; y++ )
		{
			if( shape[ x ][ y ] != 0 )
			{
				destTile.x = 192 + 1 + 22 * posX + 22 * x;
				destTile.y = 18 + 1 + 22 * targY + 22 * y;
				srcTile.x = tile1->x + ( tile1->w + 1 ) * ( 7 );
				SDL_RenderCopy(renderer, texture, &srcTile, &destTile);
			}

		}
	}
	SDL_SetTextureAlphaMod(texture, 255);


}

int Piece::getID()
{
	return shapeID;
}

int Piece::drop( int next )
{
	posY = getTarget();
	addToBoard();
	if( !reset( next ) ) return -1;
	return getRandomPiece( shapeID );
}

void Piece::setShape( int id ){}

void Piece::moveRight()
{
	posX++;
	if( getCollision() )
		posX--;
	else
		lastMove = SDL_GetTicks();
}

void Piece::moveLeft()
{

	posX--;
	if( getCollision() )
		posX++;
	else
		lastMove = SDL_GetTicks();

}

void Piece::moveDown()
{
	posY++;
	if( getCollision() )
		posY--;
	else
		lastMove = SDL_GetTicks();
}

void Piece::addToBoard()
{
	for( int x = 0; x < 4; x++ )
		for( int y = 0; y < 4; y++ )
			if( shape[ x ][ y ] != 0 )
				board->setBlock( posX + x, posY + y, shape[ x ][ y ] );
}