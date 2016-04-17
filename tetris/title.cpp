#include "title.h"
#include "menu.h"

title *title::pInstance = 0;

title *title::instance()
{
	if( pInstance == 0 )
		pInstance = new title;

	return pInstance;
}

void title::init()
{

	titleScreen = loadSDLSurface( "data/title.png" );


}

void title::cleanUp()
{
	
	freeSDLSurface( titleScreen, "data/title.png" );

}

void title::resume(){}
void title::pause(){}

void title::update( taskmanager *tskmgr )
{

	SDL_Event evnt;
	while( SDL_PollEvent( &evnt ) )
	{
		switch( evnt.type )
		{
		
		case SDL_KEYDOWN:
			switch( evnt.key.keysym.sym )
			{
			case SDLK_ESCAPE:
				tskmgr->quit();
				break;
			case SDLK_RETURN:
				tskmgr->changeTask( menu::instance() );
				break;
			default:
				break;
			}
		
		default:
			break;
		
		}
	}

}

void title::draw( taskmanager *tskmgr )
{

	SDL_BlitSurface( titleScreen, NULL, tskmgr->screen, NULL );
	SDL_Flip( tskmgr->screen );

}

