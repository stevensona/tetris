#include <iostream>
#include "board.h"
#include "piece.h"
#include "MenuState.h"
#include "GameState.h"
#include "HighscoreState.h"


using namespace std;

GameState::GameState() : board(), active(&board) {
	reseed();

	gameOver = !active.reset( getRandomPiece( -1 ) );
	next = getRandomPiece( active.getID() );
	hold = -1;
	swappedPiece = false;
	score = 0;
	linesCleared = 0;
	gameOver = false;
	bKeyRight = false;
	bKeyLeft = false;
	bKeyUp = false;
	bKeyDown = false;
	paused = false;

	gameLayout		= loadSDLSurface( "data/layout.png" );
	gameTiles		= loadSDLSurface( "data/tile.bmp" );
	gamePrev		= loadSDLSurface( "data/preview.png" );
	gamePause		= loadSDLSurface( "data/pause.png" );

	sndRotate		= Mix_LoadWAV( "data/srotate.wav" );
	sndDrop			= Mix_LoadWAV( "data/sdrop.wav");
	sndMove			= Mix_LoadWAV( "data/smove.wav");
	sndClear		= Mix_LoadWAV( "data/sclear.wav");
	sndSingle		= Mix_LoadWAV( "data/vsingle.wav");
	sndDouble		= Mix_LoadWAV( "data/vdouble.wav");
	sndTriple		= Mix_LoadWAV( "data/vtriple.wav");
	sndTetris		= Mix_LoadWAV( "data/vtetris.wav");
	sndHold			= Mix_LoadWAV( "data/shold.wav");

	srcTile.x = 25; srcTile.y = 1; srcTile.w = 21; srcTile.h = 21;
	srcBack.x = 1; srcBack.y = 1; srcBack.w = 23; srcBack.h = 23;
	destTile.w = 21; destTile.h = 21;

	destPause.x = 320 - 200; destPause.y = 240 - 150;
	destPause.w = 400; destPause.h = 300;

	for( int x = 0; x < BoardWidth; x++ ) {
		for( int y = 0; y < BoardHeight; y++ ) {
			destTile.x = 192 + 22 * x;
			destTile.y = 18 + 22 * y;
			SDL_BlitSurface( gameTiles, &srcBack, gameLayout, &destTile );
		}
	}
}

GameState::~GameState()
{
	Mix_FreeChunk( sndRotate );
	Mix_FreeChunk( sndDrop );
	Mix_FreeChunk( sndMove );
	Mix_FreeChunk( sndClear );
	Mix_FreeChunk( sndSingle );
	Mix_FreeChunk( sndDouble );
	Mix_FreeChunk( sndTriple );
	Mix_FreeChunk( sndTetris );
	Mix_FreeChunk( sndHold );

	freeSDLSurface( gameLayout, "data/layout.png" );
	freeSDLSurface( gameTiles, "data/tile.bmp" );
	freeSDLSurface( gamePrev, "data/preview.png" );
	freeSDLSurface( gamePause, "data/pause.png" );
}

void GameState::resume(){}
void GameState::pause(){}

void GameState::renderPiece( SDL_Surface *screen, int x, int y, int id)
{

	SDL_Rect src;
	SDL_Rect dest;
	if( id == shpT || id == shpJ || id == shpL || id == shpO ) src.y = 1;
	else src.y = 84;

	if( id == shpL || id == shpI ) src.x = 1;
	if( id == shpJ || id == shpS ) src.x = 84;
	if( id == shpT || id == shpZ ) src.x = 167;
	if( id == shpO ) src.x = 250;
	src.w = 83; src.h = 83;
	dest.w = 83; dest.h = 83;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface( gamePrev, &src, screen, &dest );

}

void GameState::update( StateManager *tskmgr )
{
	SDL_Event evnt;
	SDLKey key;

	while( SDL_PollEvent( &evnt ) ) {
		if( evnt.type == SDL_KEYDOWN ) {
			key = evnt.key.keysym.sym;
			if (key == SDLK_p) {
				paused = !paused;
				return;
			}
			if( key == SDLK_ESCAPE )
				gameOver = true;
		}
		if( !paused ) {
			switch( evnt.type ) {
			
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym) {
				case SDLK_UP:
					bKeyUp = true;
					repUp = SDL_GetTicks() - KEYDELAY * 2 - 1;
					break;
				case SDLK_DOWN:
					bKeyDown = true;
					repDown = SDL_GetTicks() - int(KEYDELAY * 1.5) - 1;
					break;
				case SDLK_RIGHT:
					bKeyRight = true;
					repRight = SDL_GetTicks() - int(KEYDELAY * 1.5) - 1;
					break;
				case SDLK_LEFT:
					bKeyLeft = true;
					repLeft = SDL_GetTicks() - int(KEYDELAY * 1.5) - 1;
					break;
				case SDLK_SPACE:
					Mix_PlayChannel(-1, sndDrop, 0);
					next = active.drop(next);
					if (next == -1)
						gameOver = true;
					swappedPiece = false;
					score += ((21 + (3 * active.getLevel())) - active.getFreeFall());
					break;
				case SDLK_LSHIFT:
					if(!swappedPiece) {
						Mix_PlayChannel(-1, sndHold, 0);
						int temp = active.getID();
						if (hold != -1)
							gameOver = !active.reset(hold);
						else {
							gameOver = !active.reset(next);
							next = getRandomPiece(active.getID());
						}
						hold = temp;
						swappedPiece = true;
					}
				}
				break;

			case SDL_KEYUP:
				switch (evnt.key.keysym.sym) {
				case SDLK_UP:
					bKeyUp = false;
					break;
				case SDLK_DOWN:
					bKeyDown = false;
					break;
				case SDLK_RIGHT:
					bKeyRight = false;
					break;
				case SDLK_LEFT:
					bKeyLeft = false;
				}

			}
		}
	}
	if (paused)
		return;

	if( bKeyUp && SDL_GetTicks() - repUp > int( KEYDELAY * 1.5 ) ) {
		Mix_PlayChannel( -1, sndRotate, 0 );
		repUp = SDL_GetTicks();
		active.rotate();
	}
	if( bKeyDown && SDL_GetTicks() - repDown > int( KEYDELAY * 1.5 ) ) {
		Mix_PlayChannel( -1, sndMove, 0 );
		repDown = SDL_GetTicks();
		active.moveDown();
	}
	if( bKeyRight && SDL_GetTicks() - repRight > int( KEYDELAY * 1.5 ) ) {
		Mix_PlayChannel( -1, sndMove, 0 );
		repRight = SDL_GetTicks();
		active.moveRight();
	}
	if( bKeyLeft && SDL_GetTicks() - repLeft > int( KEYDELAY * 1.5 ) ) {
		Mix_PlayChannel( -1, sndMove, 0 );
		repLeft = SDL_GetTicks();
		active.moveLeft();
	}

	int cleared = board.update( tskmgr );
	if( cleared > 0 ) Mix_PlayChannel( -1, sndClear, 0 );
	if( cleared == 1 ) Mix_PlayChannel( -1, sndSingle, 0 );
	if( cleared == 2 ) Mix_PlayChannel( -1, sndDouble, 0 );
	if( cleared == 3 ) Mix_PlayChannel( -1, sndTriple, 0 );
	if( cleared == 4 ) Mix_PlayChannel( -1, sndTetris, 0 );
	linesCleared += cleared;
	if( linesCleared >= 10 )
	{
		linesCleared -= 10;
		active.levelUp();
	}
	score += cleared * cleared;
	if( !active.update() )
	{
		gameOver = !active.reset( next );
		next = getRandomPiece( active.getID() );
		swappedPiece = false;
		score += ( ( 21 + ( 3 * active.getLevel() ) ) - active.getFreeFall() );
	}
	if (gameOver)
	{
		cout << "score = " << score << '\n';
		//HighscoreState::instance()->setCurrentScore( score );
		//tskmgr->change(make_shared<HighscoreState>());
		tskmgr->change(make_shared<MenuState>());
	}


}

void GameState::draw(StateManager *tskmgr )
{
	SDL_BlitSurface( gameLayout, NULL, tskmgr->screen, NULL );
	board.render( tskmgr, gameTiles, &srcTile );
	active.renderTarget( tskmgr, gameTiles, &srcTile );
	active.render( tskmgr, gameTiles, &srcTile );
	renderPiece( tskmgr->screen, 433, 87, next );
	if( hold != -1 ) renderPiece( tskmgr->screen, 541, 87, hold );
	//char cscore[20];
	//char clevel[20];

	//TODO FIX this
	/*sprintf_s( cscore, sizeof( cscore ), "%i", score );
	sprintf_s( clevel, sizeof( clevel ), "%i", active.getLevel() );
	
	tskmgr->printString( cscore, &buildSDLRect( 465, 265, 129, 30), buildSDLColor( 255, 221, 0, 255 ) );
	tskmgr->printString( clevel, &buildSDLRect( 465, 362, 129, 30), buildSDLColor( 255, 221, 0, 255 ) );*/

	if( paused )
		SDL_BlitSurface( gamePause, NULL, tskmgr->screen, &destPause );

	SDL_Flip( tskmgr->screen );
}

