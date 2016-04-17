//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <stdlib.h>

#include "taskmanager.h"
#include "task.h"

#include "title.h"

int main( int argc, char *argv[] )
{
	unsigned int start;
	unsigned int end;

	//ShowCursor( false );

	taskmanager *mgr = new taskmanager();

	if( mgr->init() == 0 )
	{
		mgr->changeTask( title::instance() );
	}

	while( mgr->running() )
	{

		start = SDL_GetTicks();
		mgr->update();
		mgr->draw();
		end = SDL_GetTicks();
		if( end > start && end - start < 33 )
			SDL_Delay( 33 - ( end - start ) );

	}

	mgr->cleanUp();

	delete mgr;

	return 0;

}