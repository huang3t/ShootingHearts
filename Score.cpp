#include"Score.h"
#include"Heart.h"

Score::Score()
{
    CurrentScore = 0;
    ObtainScore = 0;
    ScoreBackground.loadFromFile("ScoreBackground.png");
    ScoreBar.loadFromFile("ScoreBar.png");
}


int Score::GetScore(){
	return CurrentScore;
}

void Score::Render(int i){
if(i==1){
		int dx=SCOREBAR_EXPANDX - SCOREBARW,
			dy=SCOREBAR_EXPANDY - SCOREBARH;
	ScoreBackground.render
		(	SCOREX+(ObtainScore?-SFX:0),
			SCOREY+(ObtainScore?-SFX:0),
			(ObtainScore?SFX*2:0),
			(ObtainScore?SFX*2:0)
		);
	ScoreBar.render
		(	SCOREX+SCOREBAR_ADJUSTX,
			SCOREY+SCOREBAR_ADJUSTY+(ObtainScore?-SFX:0),
		 	dx,
		 	dy+(ObtainScore? SFX*2:0),
			CurrentScore
		);
	if(ObtainScore>0) ObtainScore ++;
	if(ObtainScore==EXPAND_DELAY)ObtainScore=0;}
else if(i==2){
	int dx=SCOREBAR_EXPANDX - SCOREBARW,
	dy=SCOREBAR_EXPANDY - SCOREBARH;
	ScoreBackground.render
		(	SCOREX2+(ObtainScore?-SFX:0),
			SCOREY2+(ObtainScore?-SFX:0),
			(ObtainScore?SFX*2:0),
			(ObtainScore?SFX*2:0)
		);
	ScoreBar.render
		(	SCOREX2+SCOREBAR_ADJUSTX,
			SCOREY2+SCOREBAR_ADJUSTY+(ObtainScore?-SFX:0),
		 	dx,
		 	dy+(ObtainScore? SFX*2:0),
			CurrentScore
		);
	if(ObtainScore>0) ObtainScore ++;
	if(ObtainScore==EXPAND_DELAY)ObtainScore=0;}

}


void Score::operator++(int){
	CurrentScore++;
	ObtainScore = 1;
}
