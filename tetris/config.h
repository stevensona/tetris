#pragma once

const int ScreenWidth = 640;
const int ScreenHeight = 480;
const int BitDepth = 32;
#define SFLAGS		SDL_WINDOW_OPENGL// | SDL_WINDOW_FULLSCREEN_DESKTOP

#define ARATE		22050
#define AFORMAT		AUDIO_S16
#define ACHANNELS	2
#define ABUFFERS	4096

#define WINDOWTITLE "Tetris"

const int BoardWidth = 10;
const int BoardHeight = 20;

#define KEYDELAY	100
