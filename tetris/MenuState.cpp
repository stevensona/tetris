#include <iostream>
#include <memory>
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "HighscoreState.h"

using namespace std;


MenuState::MenuState()
{

	menuBackground	= loadSDLSurface( "data/menu.png" );
	menuButtons		= loadSDLSurface( "data/buttons.png" );

	sndMove			=  Mix_LoadWAV( "data/smenu.wav");
	sndSelect		= Mix_LoadWAV( "data/sselect.wav");
	if( sndMove == NULL ) cout << "move not loaded. stop the tape!!\n";

	b1u.x = 54; b1u.y = 2; b1u.w = 76; b1u.h = 39;
	b1d.x = 55; b1d.y = 138; b1d.w = 75; b1d.h = 39;
	b1t.x = SWIDTH / 2 - b1u.w / 2;
	b1t.y = SHEIGHT / 2;
	b1t.w = b1u.w;
	b1t.h = b1u.h;

	b2u.x = 2; b2u.y = 50; b2u.w = 182; b2u.h = 38;
	b2d.x = 2; b2d.y = 186; b2d.w = 182; b2d.h = 38;
	b2t.x = SWIDTH / 2 - b2u.w / 2;
	b2t.y = b1t.y + b1u.h + 3;
	b2t.w = b2u.w;
	b2t.h = b2u.h;

	b3u.x = 55; b3u.y = 98; b3u.w = 78; b3u.h = 32;
	b3d.x = 55; b3d.y = 234; b3d.w = 78; b3d.h = 32;
	b3t.x = SWIDTH / 2 - b3u.w / 2;
	b3t.y = b2t.y + b2u.h + 3;
	b3t.w = b3u.w;
	b3t.h = b3u.h;

	selection = 1;

}

MenuState::~MenuState()
{

	Mix_FreeChunk( sndMove );
	Mix_FreeChunk( sndSelect );
	freeSDLSurface( menuBackground, "data/menu.png" );
	freeSDLSurface( menuButtons,	"data/buttons.png" );

}

void MenuState::resume(){}
void MenuState::pause(){}

void MenuState::update( StateManager *tskmgr )
{
	
	SDL_Event evnt;
	SDLKey key;
	while( SDL_PollEvent( &evnt ) )
	{
		switch( evnt.type )
		{
		
		case SDL_KEYDOWN:
			key = evnt.key.keysym.sym;

			if( key == SDLK_ESCAPE )
				tskmgr->change(make_shared<TitleState>());

			if( key == SDLK_RETURN || key == SDLK_SPACE )
			{
				Mix_PlayChannel( -1, sndSelect, 0 );
				switch( selection )
				{
				case 1:
					tskmgr->change(make_shared<GameState>());
					break;
				case 2:
					//HighscoreState::instance()->setCurrentScore(-1);
					//tskmgr->changeTask(make_shared<HighscoreState>());
					break;
				case 3:
					tskmgr->quit();
					break;
				}
			}

			if( key == SDLK_UP )
			{
				Mix_PlayChannel( -1, sndMove, 0 );
				selection--;
				if( selection < 1 )
					selection = 1;
			}

			if( key == SDLK_DOWN )
			{
				Mix_PlayChannel( -1, sndMove, 0 );
				selection++;
				if( selection > 3 )
					selection = 3;
			}
			break;

		default:
			break;
		}
	}

}

void MenuState::draw( StateManager *tskmgr )
{
	SDL_BlitSurface( menuBackground, NULL, tskmgr->screen, NULL );
	switch( selection )
	{
	case 1:
		SDL_BlitSurface( menuButtons, &b1d, tskmgr->screen, &b1t );
		SDL_BlitSurface( menuButtons, &b2u, tskmgr->screen, &b2t );
		SDL_BlitSurface( menuButtons, &b3u, tskmgr->screen, &b3t );
		break;
	case 2:
		SDL_BlitSurface( menuButtons, &b1u, tskmgr->screen, &b1t );
		SDL_BlitSurface( menuButtons, &b2d, tskmgr->screen, &b2t );
		SDL_BlitSurface( menuButtons, &b3u, tskmgr->screen, &b3t );
		break;
	case 3:
		SDL_BlitSurface( menuButtons, &b1u, tskmgr->screen, &b1t );
		SDL_BlitSurface( menuButtons, &b2u, tskmgr->screen, &b2t );
		SDL_BlitSurface( menuButtons, &b3d, tskmgr->screen, &b3t );
		break;
	default:
		selection = 1;
		break;
	}
	SDL_Flip( tskmgr->screen );

}

