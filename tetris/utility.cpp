#include "randomc.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "utility.h"

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }


TRandomMotherOfAll rg( SDL_GetTicks() );

using namespace std;

void reseed()
{
	rg = TRandomMotherOfAll( SDL_GetTicks() );
}

SDL_Surface *loadSDLSurface( const char *file )
{
	SDL_Surface *dest = IMG_Load( file );

	if (dest != NULL)
		cout << "loaded " << file << '\n';
	else
		cout << "failed to load " << file << '\n';

	return dest;
}

void freeSDLSurface( SDL_Surface *surface, const char *file )
{
	SDL_FreeSurface( surface );

	cout << "freed " << file << '\n';


}

SDL_Color buildSDLColor( int R, int G, int B, int A )
{
	SDL_Color res = { R, G, B, A };
	return res;
}

SDL_Rect buildSDLRect( int x, int y, int w, int h )
{
	SDL_Rect res;
	res.x = x;
	res.y = y;
	res.w = w;
	res.h = h;
	return res;
}

int getRandomPiece( int current )
{
	if( current == -1 )
		return rg.IRandom( 0, 6 );

	int newpiece = rg.IRandom( 0, 6 );
	if( newpiece == current)
		newpiece = rg.IRandom( 0, 6 );
	if( newpiece == current)
		newpiece = rg.IRandom( 0, 6 );
	return newpiece;

}