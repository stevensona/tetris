
#include <iostream>
#include "StateManager.h"
#include "State.h"

using namespace std;

StateManager::StateManager()
{
	cout << "initializing subsystems\n";

	if( SDL_Init( SDL_INIT_TIMER ) > -1 )
		cout << "timer initialized\n";
	else {
		cout << "timer initialization failed\n";
	}

	if( SDL_Init( SDL_INIT_AUDIO ) > -1 )
		cout << "audio initialized\n";
	else {
		cout << "audio initialization failed\n";
	}

	if( !Mix_OpenAudio( ARATE, AFORMAT, ACHANNELS, ABUFFERS ) )
		cout << "mixer initialized\n";
	else {
		cout << "mixer initialization failed\n";
	}

	if( SDL_Init( SDL_INIT_VIDEO ) > -1 )
		cout << "video initialized\n";
	else {
		cout << "video initialization failed\n";
	}

	if( initText() )
		cout << "font initialized\n";
	else {
		cout << "font initialization failed\n";
	}

	screen = SDL_SetVideoMode( SWIDTH, SHEIGHT, SBITS, SFLAGS );
	if( screen != NULL )
		cout << "set resolution " << SWIDTH << ", " << SHEIGHT << '@' << SBITS;
	else {
		cout << "screen initialization failed\n";
	}

	SDL_WM_SetCaption( WINDOWTITLE, WINDOWTITLE );

	cout << "flower started\n";
	mRunning = true;

}

StateManager::~StateManager()
{
	Mix_CloseAudio();
	closeText();

	SDL_FreeSurface( screen );
	SDL_Quit();

	cout << "flower stopped\n";

}

void StateManager::change(shared_ptr<State> state)
{
	mTasks.clear();
	mTasks.push_back(state);
	update();
	SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0, 0, 0 ) );
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
		mTasks.back()->update(this);
	}
}

void StateManager::draw()
{
	if(!mTasks.empty()) {
		mTasks.back()->draw(this);
	}
}

bool StateManager::initText()
{
	if( TTF_Init() == -1 )
		return false;
	bkFont = TTF_OpenFont( "data/bk.ttf", 25 );
	if( bkFont == NULL )
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
	SDL_Surface *textsurf = TTF_RenderText_Blended( bkFont, text, color );
	SDL_BlitSurface( textsurf, NULL, screen, destrect );
	SDL_FreeSurface( textsurf );
}