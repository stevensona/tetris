#include <memory>

#include "TitleState.h"
#include "MenuState.h"

using namespace std;

TitleState::TitleState(StateManager *owner) {
	this->owner = owner;
	titleScreen = loadTexture(owner->renderer, "data/title.png");
}

TitleState::~TitleState() {
	destroyTexture(titleScreen);
}

void TitleState::resume(){}
void TitleState::pause(){}

void TitleState::update() {

	SDL_Event evnt;
	while( SDL_PollEvent( &evnt ) )
	{
		switch( evnt.type ) {
		
		case SDL_KEYDOWN:
			switch(evnt.key.keysym.sym) {
			case SDLK_ESCAPE:
				owner->quit();
				break;
			case SDLK_RETURN:
				owner->change(make_shared<MenuState>(owner));
				break;
			}
		}
	}
}

void TitleState::draw() {
	SDL_RenderCopy(owner->renderer, titleScreen, NULL, NULL);
	SDL_RenderPresent(owner->renderer);
}

