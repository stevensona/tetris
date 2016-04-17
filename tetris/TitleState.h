#pragma once

#include "State.h"

class TitleState : public State
{

private:
	SDL_Surface *titleScreen;

public:
	
	TitleState();
	~TitleState();

	void resume() override;
	void pause() override;

	void update( StateManager *mgr ) override;
	void draw( StateManager *mgr ) override;


};
