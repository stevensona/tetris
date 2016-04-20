#pragma once

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *file);

void destroyTexture( SDL_Texture *texture);

SDL_Color buildSDLColor(const uint8_t R, const uint8_t G, const uint8_t B, const uint8_t A);

SDL_Rect buildSDLRect(const int16_t x, const int16_t y, const uint16_t w, const uint16_t h);


void reseed();

int getRandomPiece( int current );
