//AM 20190102
#include "Header.h"


timer::timer(){
	tiktok = new LTexture*[31];
	this->loadmedia();
	reset();
	now = SDL_GetTicks();
	duration = now-start;
	sec = duration / 1000;
	sec %= 31;
}

timer::~timer(){
    for(int i=0;i<=30;i++){
    	delete tiktok[i];
    }
    delete []tiktok;
}

void timer::reset(){
	start = SDL_GetTicks();
}

void timer::render(int i){
	now = SDL_GetTicks();
	duration = now-start;
	sec = duration / 1000;
	int ms = duration%1000;
	int y = -20*(ms-500)*(ms-500)/500/500+20;
	sec %= 31;
    if(i==1)
	tiktok[sec]->render(timerX,timerY-y);
    else tiktok[sec]->render(timer2X,timer2Y-y);
}

bool timer::loadmedia(){
    //Loading success flag
    bool success = true;
    for(int i=0;i<31;i++) tiktok[i]=new LTexture;
    //Load PNG texture
    tiktok[0]->loadFromFile("clock30.png");
    tiktok[1]->loadFromFile("clock29.png");
    tiktok[2]->loadFromFile("clock28.png");
    tiktok[3]->loadFromFile("clock27.png");
    tiktok[4]->loadFromFile("clock26.png");
    tiktok[5]->loadFromFile("clock25.png");
    tiktok[6]->loadFromFile("clock24.png");
    tiktok[7]->loadFromFile("clock23.png");
    tiktok[8]->loadFromFile("clock22.png");
    tiktok[9]->loadFromFile("clock21.png");
    tiktok[10]->loadFromFile("clock20.png");
    tiktok[11]->loadFromFile("clock19.png");
    tiktok[12]->loadFromFile("clock18.png");
    tiktok[13]->loadFromFile("clock17.png");
    tiktok[14]->loadFromFile("clock16.png");
    tiktok[15]->loadFromFile("clock15.png");
    tiktok[16]->loadFromFile("clock14.png");
    tiktok[17]->loadFromFile("clock13.png");
    tiktok[18]->loadFromFile("clock12.png");
    tiktok[19]->loadFromFile("clock11.png");
    tiktok[20]->loadFromFile("clock10.png");
    tiktok[21]->loadFromFile("clock9.png");
    tiktok[22]->loadFromFile("clock8.png");
    tiktok[23]->loadFromFile("clock7.png");
    tiktok[24]->loadFromFile("clock6.png");
    tiktok[25]->loadFromFile("clock5.png");
    tiktok[26]->loadFromFile("clock4.png");
    tiktok[27]->loadFromFile("clock3.png");
    tiktok[28]->loadFromFile("clock2.png");
    tiktok[29]->loadFromFile("clock1.png");
    tiktok[30]->loadFromFile("clock0.png");
    for(int i=0;i<=30;i++){
        if( tiktok == NULL )
        {
            printf( "Failed to load texture image!\n" );
            success = false;
        }}
    return success;
}

Uint32 timer::GetTime(){
    now = SDL_GetTicks();
    duration = now - start;
    return duration;
}
