#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#define SCOREX 300
#define SCOREY 20
#define	SCOREX2 10
#define	SCOREY2 0
#define SCOREBARW 348
#define SCOREBARH 40
#define SCOREBAR_ADJUSTX 113	//bar - background
#define SCOREBAR_ADJUSTY 31		//bar - background
#define EXPAND_DELAY 4			//frames of the effect
#define SCOREBAR_EXPANDX 367
#define SCOREBAR_EXPANDY 60
#define SFX 10	
#include "Header.h"
#include "LTexture.h"
class Score
{
private:
	int CurrentScore;
	LTexture ScoreBackground;
	LTexture ScoreBar;
	int ObtainScore;
public:
	Score();
	int GetScore();
	void operator++(int);	//point +1
	void Render(int i=1);
};


#endif // SCORE_H_INCLUDED
