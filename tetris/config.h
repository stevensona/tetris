#pragma once

const int SWIDTH = 640;
const int SHEIGHT = 480;
const int SBITS = 32;
#define SFLAGS		SDL_HWSURFACE | SDL_DOUBLEBUF// | SDL_FULLSCREEN

#define ARATE		22050
#define AFORMAT		AUDIO_S16
#define ACHANNELS	2
#define ABUFFERS	4096

#define WINDOWTITLE "Tetris"

#define BWIDTH		10
#define BHEIGHT		20

#define KEYDELAY	100
