#ifndef __highscore_h__
#define __highscore_h__
#include <fstream>
#include <string.h>
#include "task.h"

struct savedScore
{
	std::string name;
   int score;
};

class highscore : public task
{
private:
	SDL_Surface *hsBack;
	SDL_Surface *hsEYN;
	std::ofstream fileout;
	std::ifstream filein;
	savedScore scores[6];
	int scoreSlot;
	int currentScore;

public:
	static highscore *instance();
	highscore();
	void init();
	void cleanUp();

	void resume();
	void pause();

	void update( taskmanager *tskmgr );
	void draw( taskmanager *tskmgr );

	void changeTask( taskmanager *tskmgr, task *tsk );

	void setCurrentScore( int score );

private:
	static highscore *pInstance;
};
#endif