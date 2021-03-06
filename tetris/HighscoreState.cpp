#include <memory>
#include "MenuState.h"
#include "HighscoreState.h"

using namespace std;

HighscoreState::HighscoreState(StateManager *owner): currentScore(0), scoreSlot(0) {
	this->owner = owner;
	filein.open( "data/tetris.highscores", std::ios::binary );
	for( int i = 0; i < 6; i++ )
		filein.read( ( char * ) ( &scores[i] ), sizeof( scores[i] ) );
	filein.close();

	hsBack = loadTexture(owner->renderer, "data/highscore.png");
	hsEYN = loadTexture(owner->renderer, "data/eyn.png");

	if( currentScore != -1 )
	{
		for( int i = 0; i < 6; i++ )
			if( currentScore > scores[i].score )
			{
				for( int k = 5; k > i; k-- )
					scores[k] = scores[k - 1];
				scores[i].name = "";
				scores[i].score = currentScore;
				scoreSlot = i;
				currentScore = -2;
			}


	}
}

HighscoreState::~HighscoreState()
{
	destroyTexture(hsBack);
	destroyTexture(hsEYN);
	
}

void HighscoreState::resume(){}
void HighscoreState::pause(){}

void HighscoreState::update()
{
	SDL_Event evnt;
	SDL_Keycode key;

	while( SDL_PollEvent( &evnt ) )
	{
		if( evnt.type == SDL_KEYDOWN )
		{
			key = evnt.key.keysym.sym;

			if( key == SDLK_ESCAPE )
				owner->change(make_shared<MenuState>(owner) );
			if( currentScore == -2 )
			{
				if( key == SDLK_BACKSPACE )
					if( scores[scoreSlot].name.length() > 0 )
						scores[scoreSlot].name.resize( scores[scoreSlot].name.length() - 1 );
				if( key == SDLK_RETURN )
				{
					currentScore = -1;
					fileout.open( "data/tetris.highscores", std::ios::binary );
					for( int i = 0; i < 6; i++ )
						fileout.write( ( char * ) ( &scores[i] ), sizeof( scores[i] ) );
					fileout << std::flush;
					fileout.close();
				}
				if( scores[scoreSlot].name.length() < 15 )
				{
					if( key == SDLK_q )	scores[scoreSlot].name.append( "Q" );
					if( key == SDLK_w ) scores[scoreSlot].name.append( "W" );
					if( key == SDLK_e ) scores[scoreSlot].name.append( "E" );
					if( key == SDLK_r ) scores[scoreSlot].name.append( "R" );
					if( key == SDLK_t ) scores[scoreSlot].name.append( "T" );
					if( key == SDLK_y ) scores[scoreSlot].name.append( "Y" );
					if( key == SDLK_u ) scores[scoreSlot].name.append( "U" );
					if( key == SDLK_i ) scores[scoreSlot].name.append( "I" );
					if( key == SDLK_o ) scores[scoreSlot].name.append( "O" );
					if( key == SDLK_p ) scores[scoreSlot].name.append( "P" );
					if( key == SDLK_a ) scores[scoreSlot].name.append( "A" );
					if( key == SDLK_s ) scores[scoreSlot].name.append( "S" );
					if( key == SDLK_d ) scores[scoreSlot].name.append( "D" );
					if( key == SDLK_f ) scores[scoreSlot].name.append( "F" );
					if( key == SDLK_g ) scores[scoreSlot].name.append( "G" );
					if( key == SDLK_h ) scores[scoreSlot].name.append( "H" );
					if( key == SDLK_j ) scores[scoreSlot].name.append( "J" );
					if( key == SDLK_k ) scores[scoreSlot].name.append( "K" );
					if( key == SDLK_l ) scores[scoreSlot].name.append( "L" );
					if( key == SDLK_z ) scores[scoreSlot].name.append( "Z" );
					if( key == SDLK_x ) scores[scoreSlot].name.append( "X" );
					if( key == SDLK_c ) scores[scoreSlot].name.append( "C" );
					if( key == SDLK_v ) scores[scoreSlot].name.append( "V" );
					if( key == SDLK_b ) scores[scoreSlot].name.append( "B" );
					if( key == SDLK_n ) scores[scoreSlot].name.append( "N" );
					if( key == SDLK_m ) scores[scoreSlot].name.append( "M" );

					if( key == SDLK_1 ) scores[scoreSlot].name.append( "1" );
					if( key == SDLK_2 ) scores[scoreSlot].name.append( "2" );
					if( key == SDLK_3 ) scores[scoreSlot].name.append( "3" );
					if( key == SDLK_4 ) scores[scoreSlot].name.append( "4" );
					if( key == SDLK_5 ) scores[scoreSlot].name.append( "5" );
					if( key == SDLK_6 ) scores[scoreSlot].name.append( "6" );
					if( key == SDLK_7 ) scores[scoreSlot].name.append( "7" );
					if( key == SDLK_8 ) scores[scoreSlot].name.append( "8" );
					if( key == SDLK_9 ) scores[scoreSlot].name.append( "9" );
					if( key == SDLK_0 ) scores[scoreSlot].name.append( "0" );
					if( key == SDLK_SPACE ) scores[scoreSlot].name.append( " " );

				}



			}


		}
	}

}

void HighscoreState::draw()
{
	SDL_RenderCopy(owner->renderer, hsBack, NULL, NULL);
	for( int i = 0;i < 6; i++ )
	{
		//char cscore[20];
		//TODO fix
		/*
		sprintf_s( cscore, sizeof( cscore ), "%i", scores[i].score );
		mgr->printString( scores[i].name.c_str(), &buildSDLRect( 80, 175 + 40 * i, 300, 300), buildSDLColor( 255, 221, 0, 255 ) );
	
		mgr->printString( cscore, &buildSDLRect( 350, 175 + 40 * i, 300, 300), buildSDLColor( 255, 221, 0, 255 ) );*/

	}
	if (currentScore == -2)
		SDL_RenderCopy(owner->renderer, hsEYN, NULL, &buildSDLRect(0, 480 - 88, 640, 88));
	SDL_RenderPresent(owner->renderer);

}

void HighscoreState::setCurrentScore( int score )
{
	currentScore = score;
}
