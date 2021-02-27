#ifndef Heart_h
#define Heart_h
#include "LTexture.h"

#define FLY 61 //how many frames is the flying process
#define EXPLODE_END 120 //after this pause=false
#define EXPLODE_VANISH 60 // frames during heartbroken 1~9
#define EXPLODE_BREAK 30 // frames during heartbroken 0

#define HEADX 450
#define HEADY 160
#define HEADW 100	//the area of target
#define HEADH 30	//the area of target
#define HEART_X0 300    //initial heart pos x
#define HEART_Y0 600    //initial heart pos y

#define HYUNX 	267
#define HYUNY 	286
#define HYUNW	82
#define HYUNH	59
#define HYUNX0	500//422
#define HYUNY0	556

class heart{
private:
	int frame; 					//the index of pos=0~60
	int pointframe;				
		//the index of star process 10 frames
	static int explosion_frame;
		//the index of exploding process which is 120 frames
		//0 means normal hearttype, otherwise exploding
//3 MEMBERS BELOW ARE MARKED STATIC 0103//
	double x[FLY];
	double y[FLY];
	static bool pause;
		//pause = no reaction when clicking mouse
	static LTexture* HeartTypes; //0 normal 1>4star 5>13broke
public:
	heart();
	heart(int);
	void 	SetXY(int);			//static member x[]y[]
	void 	Load();
	bool 	render();			//render correct texture
	int 	getFrame(); 		//return frame index
	static void update_explosion_frame(class Background&);
	bool 	ReturnPause();
    void 	move(class Background& , class Score&);
    int 	GetExplodeFrame();
    bool	SetGetPoint();
    bool	GetPointRender(); //true then delete
};

#endif //Heart_h
