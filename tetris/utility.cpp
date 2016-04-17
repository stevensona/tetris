//#include "randomc.h"
#include <random>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "utility.h"

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; } //HACK for precompiled SDL1.2 on vs2015

std::default_random_engine rng;
std::uniform_int_distribution<int> dist(0, 6);

using namespace std;

void reseed()
{
	rng.seed(SDL_GetTicks());
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

SDL_Color buildSDLColor( const uint8_t R, const uint8_t G, const uint8_t B, const uint8_t A )
{

	return{ R, G, B, A };
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
	auto attempts = 0, new_piece = 0;
	do {
		new_piece = dist(rng);
	} while (attempts++ < 3 || new_piece == current);
	
	return new_piece;

}