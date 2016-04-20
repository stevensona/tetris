#pragma once

#include <fstream>
#include <string.h>
#include "state.h"

struct savedScore
{
	std::string name;
	int score;
};

class HighscoreState : public State
{
private:
	SDL_Texture *hsBack, *hsEYN;
	std::ofstream fileout;
	std::ifstream filein;
	savedScore scores[6];
	int scoreSlot;
	int currentScore;

public:

	HighscoreState(StateManager *owner);
	~HighscoreState();

	void resume() override;
	void pause() override;

	void update() override;
	void draw() override;

	void setCurrentScore( int score );

};
