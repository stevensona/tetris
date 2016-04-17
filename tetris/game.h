#ifndef __game_h__
#define __game_h__

#include "task.h"
#include "board.h"
#include "piece.h"

class game : public task
{

private:
	void renderPiece( SDL_Surface *screen, int x, int y, int id);
	SDL_Surface *gameTiles;
	SDL_Surface *gameLayout;
	SDL_Surface *gamePrev;
	SDL_Surface *gamePause;

	SDL_Rect srcTile;
	SDL_Rect destTile;
	SDL_Rect srcBack;
	SDL_Rect destPause;

	Mix_Chunk *sndRotate;
	Mix_Chunk *sndDrop;
	Mix_Chunk *sndMove;
	Mix_Chunk *sndClear;
	Mix_Chunk *sndSingle;
	Mix_Chunk *sndDouble;
	Mix_Chunk *sndTriple;
	Mix_Chunk *sndTetris;
	Mix_Chunk *sndHold;

	piece active;
	int next;
	int hold;
	bool swapped;

	bool bKeyRight;
	bool bKeyLeft;
	bool bKeyUp;
	bool bKeyDown;

	bool paused;

	unsigned int repRight;
	unsigned int repLeft;
	unsigned int repUp;
	unsigned int repDown;
	int score;
	int linesCleared;
	bool gameOver;

public:
	static game *instance();
	void init();
	void cleanUp();

	void resume();
	void pause();

	void update( taskmanager *tskmgr );
	void draw( taskmanager *tskmgr );


	

private:
	static game *pInstance;
};
#endif