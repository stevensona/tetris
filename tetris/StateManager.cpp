
#include <iostream>
#include <exception>
#include "StateManager.h"
#include "State.h"

using namespace std;

StateManager::StateManager()
{
	cout << "initializing subsystems\n";

	if( SDL_Init( SDL_INIT_TIMER ) < 0 ) {
		throw(runtime_error("timer initialization failed"));
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		throw(runtime_error("audio initialization failed"));
	}
	if( Mix_OpenAudio( ARATE, AFORMAT, ACHANNELS, ABUFFERS ) ) {
		throw(runtime_error("audio initialization failed"));
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw(runtime_error("video initialization failed"));
	}

	if( !initText() ) {
		throw(runtime_error("font initialization failed"));
	}

	window = SDL_CreateWindow( WINDOWTITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		ScreenWidth, ScreenHeight, SFLAGS );
	renderer = SDL_CreateRenderer(window, -1, 0);
	if( window == nullptr ) {
		throw(runtime_error("screen initialization failed"));
	}

	mRunning = true;

}

StateManager::~StateManager()
{
	Mix_CloseAudio();
	closeText();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void StateManager::change(shared_ptr<State> state)
{
	mTasks.clear();
	mTasks.push_back(state);
	update();
	SDL_RenderClear(renderer);
}

void StateManager::push(shared_ptr<State> state)
{
	if (!mTasks.empty()) {
		mTasks.back()->pause();
	}
	mTasks.push_back(state);
}

void StateManager::pop()
{
	mTasks.pop_back();
	if(!mTasks.empty()) {
		mTasks.back()->resume();
	}
}

void StateManager::update()
{
	if(!mTasks.empty()) {
		mTasks.back()->update();
	}
}

void StateManager::draw()
{
	if(!mTasks.empty()) {
		mTasks.back()->draw();
	}
}

bool StateManager::initText()
{
	if(TTF_Init() == -1 )
		return false;
	bkFont = TTF_OpenFont( "data/bk.ttf", 25 );
	if(bkFont == nullptr)
		return false;
	return true;

}

void StateManager::closeText()
{
	TTF_CloseFont( bkFont );
	TTF_Quit();
}

void StateManager::printString( const char *text, SDL_Rect *destrect, SDL_Color color )
{
	//SDL_Surface *textsurf = TTF_RenderText_Blended( bkFont, text, color );
	//SDL_BlitSurface( textsurf, NULL, window, destrect );
	//SDL_FreeSurface( textsurf );

	//TODO FIX THIS
}