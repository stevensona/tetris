#pragma once

#include "state.h"

class MenuState : public State
{

private:

	SDL_Rect b1u, b2u, b3u; //Source rect up
	SDL_Rect b1d, b2d, b3d; //Source rect down
	SDL_Rect b1t, b2t, b3t; //Target rect

	SDL_Texture *menuBackground;
	SDL_Texture *menuButtons;

	Mix_Chunk *sndMove;
	Mix_Chunk *sndSelect;

	int selection;

public:
	MenuState(StateManager *owner);
	~MenuState();

	void resume() override;
	void pause() override;

	void update() override;
	void draw() override;

};
