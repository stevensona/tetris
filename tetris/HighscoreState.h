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
	SDL_Surface *hsBack;
	SDL_Surface *hsEYN;
	std::ofstream fileout;
	std::ifstream filein;
	savedScore scores[6];
	int scoreSlot;
	int currentScore;

public:

	HighscoreState();
	~HighscoreState();

	void resume() override;
	void pause() override;

	void update( StateManager *tskmgr ) override;
	void draw( StateManager *tskmgr ) override;

	void setCurrentScore( int score );

};
