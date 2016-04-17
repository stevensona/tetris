#pragma once

#include "State.h"
#include "board.h"
#include "piece.h"

class GameState : public State {

private:
	void renderPiece( SDL_Surface *screen, int x, int y, int id);
	SDL_Surface *gameTiles, *gameLayout, *gamePrev, *gamePause;
	SDL_Rect srcTile, destTile, srcBack, destPause;
	Mix_Chunk *sndRotate, *sndDrop, *sndMove, *sndClear;
	Mix_Chunk *sndSingle, *sndDouble, *sndTriple, *sndTetris;
	Mix_Chunk *sndHold;

	Piece active;
	Board board;
	int next, hold;
	bool swappedPiece;

	bool bKeyRight, bKeyLeft, bKeyUp, bKeyDown;

	bool paused;

	unsigned int repRight, repLeft, repUp, repDown;

	int score, linesCleared;
	bool gameOver;

public:

	GameState();
	~GameState();

	void resume() override;
	void pause() override;

	void update(StateManager *tskmgr) override;
	void draw(StateManager *tskmgr) override;

};
