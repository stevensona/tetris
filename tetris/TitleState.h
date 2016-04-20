#pragma once

#include "State.h"

class TitleState : public State
{

private:
	SDL_Texture *titleScreen;

public:
	TitleState(StateManager *owner);
	~TitleState();

	void resume() override;
	void pause() override;

	void update() override;
	void draw() override;


};
