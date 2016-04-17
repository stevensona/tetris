
#include <iostream>
#include "taskmanager.h"
#include "task.h"

using namespace std;

int taskmanager::init()
{

	mRunning = false;

	cout << "initializing subsystems\n";

	if( SDL_Init( SDL_INIT_TIMER ) > -1 )
		cout << "timer initialized\n";
	else {
		cout << "timer initialization failed\n";
		return -1;
	}

	if( SDL_Init( SDL_INIT_AUDIO ) > -1 )
		cout << "audio initialized\n";
	else {
		cout << "audio initialization failed\n";
		return -1;
	}

	if( !Mix_OpenAudio( ARATE, AFORMAT, ACHANNELS, ABUFFERS ) )
		cout << "mixer initialized\n";
	else {
		cout << "mixer initialization failed\n";
		return -1;
	}

	if( SDL_Init( SDL_INIT_VIDEO ) > -1 )
		cout << "video initialized\n";
	else {
		cout << "video initialization failed\n";
		return -1;
	}

	if( initText() )
		cout << "font initialized\n";
	else {
		cout << "font initialization failed\n";
		return -1;
	}

	screen = SDL_SetVideoMode( SWIDTH, SHEIGHT, SBITS, SFLAGS );
	if( screen != NULL )
		cout << "set resolution " << SWIDTH << ", " << SHEIGHT << '@' << SBITS;
	else {
		cout << "screen initialization failed\n";
		return -1;
	}

	SDL_WM_SetCaption( WINDOWTITLE, WINDOWTITLE );

	cout << "flower started\n";
	mRunning = true;
	return 0;

}

void taskmanager::cleanUp()
{

	Mix_CloseAudio();
	closeText();

	while( !mTasks.empty() )
	{
		mTasks.back()->cleanUp();
		mTasks.pop_back();
	}
	
	SDL_FreeSurface( screen );

	SDL_Quit();

	cout << "flower stopped\n";

}

void taskmanager::changeTask( task *tsk )
{

	if( !mTasks.empty() )
	{
		mTasks.back()->cleanUp();
		mTasks.pop_back();
	}

	mTasks.push_back( tsk );
	mTasks.back()->init();
	mTaskUpdated = false;
	SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0, 0, 0 ) );

}

void taskmanager::pushTask( task *tsk )
{
	
	if( !mTasks.empty() )
		mTasks.back()->pause();

	mTasks.push_back( tsk );
	mTasks.back()->init();
	mTaskUpdated = false;

}

void taskmanager::popTask()
{

	if( !mTasks.empty() )
	{
		mTasks.back()->cleanUp();
		mTasks.pop_back();
	}

	if( !mTasks.empty() )
	{
		mTasks.back()->resume();
		mTaskUpdated = false;
	}
}

void taskmanager::update()
{

	if( !mTasks.empty() )
	{
		mTaskUpdated = true;
		mTasks.back()->update( this );
		
	}

}

void taskmanager::draw()
{

	if( !mTasks.empty() )
		if( mTaskUpdated == true )
		{
			mTasks.back()->draw( this );
			mTaskUpdated = false;
		}

}

bool taskmanager::initText()
{
	if( TTF_Init() == -1 )
		return false;
	bkFont = TTF_OpenFont( "data/bk.ttf", 25 );
	if( bkFont == NULL )
		return false;
	return true;

}

void taskmanager::closeText()
{
	TTF_CloseFont( bkFont );
	TTF_Quit();
}

void taskmanager::printString( const char *text, SDL_Rect *destrect, SDL_Color color )
{
	SDL_Surface *textsurf = TTF_RenderText_Blended( bkFont, text, color );
	SDL_BlitSurface( textsurf, NULL, screen, destrect );
	SDL_FreeSurface( textsurf );

}