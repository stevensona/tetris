#include <memory>

#include "TitleState.h"
#include "MenuState.h"

using namespace std;

TitleState::TitleState() {
	titleScreen = loadSDLSurface( "data/title.png" );
}

TitleState::~TitleState() {
	freeSDLSurface( titleScreen, "data/title.png");
}

void TitleState::resume(){}
void TitleState::pause(){}

void TitleState::update( StateManager *mgr ) {

	SDL_Event evnt;
	while( SDL_PollEvent( &evnt ) )
	{
		switch( evnt.type ) {
		
		case SDL_KEYDOWN:
			switch(evnt.key.keysym.sym) {
			case SDLK_ESCAPE:
				mgr->quit();
				break;
			case SDLK_RETURN:
				mgr->change(make_shared<MenuState>());
				break;
			}
		}
	}
}

void TitleState::draw(StateManager *mgr) {
	SDL_BlitSurface( titleScreen, NULL, mgr->screen, NULL );
	SDL_Flip( mgr->screen );
}

