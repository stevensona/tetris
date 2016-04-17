#ifndef __utility_h__
#define __utility_h__


SDL_Surface *loadSDLSurface( const char *file );

void freeSDLSurface( SDL_Surface *surface, const char *file );

SDL_Color buildSDLColor( int R, int G, int B, int A );

SDL_Rect buildSDLRect( int x, int y, int w, int h );



void reseed();

int getRandomPiece( int current );

#endif