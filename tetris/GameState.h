#pragma once

#include "State.h"
#include "board.h"
#include "piece.h"

class GameState : public State {

private:
	void renderPreview( SDL_Renderer *renderer, int x, int y, int id);
	SDL_Texture *tiles, *background, *pieces, *paused;
	SDL_Rect srcTile, destTile, srcBack, destPause;
	Mix_Chunk *sndRotate, *sndDrop, *sndMove, *sndClear;
	Mix_Chunk *sndSingle, *sndDouble, *sndTriple, *sndTetris;
	Mix_Chunk *sndHold;

	Piece active;
	Board board;
	int next, hold;
	bool swappedPiece;

	bool bKeyRight, bKeyLeft, bKeyUp, bKeyDown;

	bool isPaused;

	unsigned int repRight, repLeft, repUp, repDown;

	int score, linesCleared;
	bool gameOver;

public:

	GameState(StateManager *owner);
	~GameState();

	void resume() override;
	void pause() override;

	void update() override;
	void draw() override;

};
