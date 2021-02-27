#ifndef CLOCK_H
#define CLOCK_H
#include"LTexture.h"
#define timerX -100
#define timerY -50
#define timer2X	410 //152
#define timer2Y	360 //71

class timer{
private:
	LTexture** tiktok = NULL;
	Uint32 start,now,duration;
	int sec;

public:
    timer();
	~timer();
	void reset();
    bool loadmedia();
	void render(int i=1);
	Uint32 GetTime();//now-start in ms
};


#endif // CLOCK_H
