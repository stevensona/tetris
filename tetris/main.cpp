
#include <memory>

#include "StateManager.h"
#include "State.h"
#include "TitleState.h"

using namespace std;

int main( int argc, char *argv[] )
{
	unsigned int start;
	unsigned int end;

	StateManager mgr;

	mgr.change(make_shared<TitleState>());
	
	while(mgr.running()) {

		start = SDL_GetTicks();
		mgr.update();
		mgr.draw();
		end = SDL_GetTicks();
		if( end > start && end - start < 33 )
			SDL_Delay( 33 - ( end - start ) );

	}
	return 0;
}