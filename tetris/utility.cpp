//#include "randomc.h"
#include <random>
#include <iostream>
#include <exception>
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

	if (dest == nullptr) {
		throw(runtime_error("failed to load surface"));
	}

	return dest;
}

void freeSDLSurface( SDL_Surface *surface, const char *file )
{
	SDL_FreeSurface( surface );

}

SDL_Color buildSDLColor( const uint8_t R, const uint8_t G, const uint8_t B, const uint8_t A )
{

	return{ R, G, B, A };
}

SDL_Rect buildSDLRect(const int16_t x, const int16_t y, const uint16_t w, const uint16_t h )
{
	return { x, y, w, h };
}

int getRandomPiece( int current )
{
	auto attempts = 0, new_piece = 0;
	do {
		new_piece = dist(rng);
	} while (attempts++ < 3 || new_piece == current);
	
	return new_piece;

}