#pragma once

#include "SDL.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <memory>
#include <vector>


#include "config.h"
#include "utility.h"

class State;

class StateManager
{

private:
	std::vector<std::shared_ptr<State>> mTasks;
	bool mRunning;

	TTF_Font *bkFont; //why is this here

	bool initText();
	void closeText();

public:
	StateManager();
	~StateManager();

	void change(std::shared_ptr<State> state);
	void push(std::shared_ptr<State> state);
	void pop();

	void update();
	void draw();

	bool running()
	{
		return mRunning;
	}

	void quit()
	{
		mRunning = false;
	}



	void printString( const char *text, SDL_Rect *destrect, SDL_Color color );

	SDL_Surface *screen;

};
