#pragma once

#include "SDL.h"
#include "Board.h"

enum class Shapes { T, L, J, O, S, Z, I }; //TODO
enum class Colors {}; //TODO
#define shpT 0
#define shpL 1
#define shpJ 2
#define shpO 3
#define shpS 4
#define shpZ 5
#define shpI 6

class Piece
{
private:
	int shape[ 4 ][ 4 ];
	unsigned int lastDrop;
	unsigned int lastMove;
	int posX;
	int posY;
	int rotation;
	int getMaxX();
	int getMaxY();
	int getMinX();
	int getMinY();
	int getWidth();
	int getHeight();
	int shapeID;
	unsigned int level;
	bool getCollision();
	int freeFall;

	Board* board;

public:
	Piece(Board* board);
	int getFreeFall();
	void render(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *tile1);
	void rotate();
	int getID();
	bool reset( int id ); //should be called before using and returns false if game over
	int getTarget(); //returns y value of ghost target thing
	void renderTarget(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *tile1 );
	int drop( int next );
	bool update(); //false = new piece
	void setShape( int id );
	void moveRight();
	void moveLeft();
	void moveDown();
	void addToBoard();
	void levelUp();
	int getLevel();
};
