#include "Heart.h"
#include "Background.h"
#include "Score.h"

#include <cstdlib>

//----------------------------------//
//static member assignment

bool heart::pause = false;
int heart::explosion_frame = 0;
LTexture* heart::HeartTypes = new LTexture[14];

//----------------------------------//
//member function def
heart::heart(){
	frame = 0;
	pointframe = 0;
	SetXY(1);
}

heart::heart(int i){	//constructor for GAME II
	frame = 0;
	pointframe = 0;
	SetXY(2);
}

bool heart::render(){
	//std::cout<<"frame="<<frame<<" , pointframe="<<pointframe<<std::endl;
	//~~這邊碎掉圖片用得分代替
	if( pointframe==0 ){
		if(explosion_frame==0 )
			HeartTypes[0].render(x[frame],y[frame]);
		else if(1<=explosion_frame&&explosion_frame<=EXPLODE_BREAK)
			HeartTypes[0].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*0/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*1/9)
			HeartTypes[5].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*1/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*2/9)
			HeartTypes[6].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*2/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*3/9)
			HeartTypes[7].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*3/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*4/9)
			HeartTypes[8].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*4/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*5/9)
			HeartTypes[9].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*5/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*6/9)
			HeartTypes[10].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*6/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*7/9)
			HeartTypes[11].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*7/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*8/9)
			HeartTypes[12].render(x[frame],y[frame]);
		else if(  EXPLODE_BREAK+EXPLODE_VANISH*8/9 <=explosion_frame  &&  explosion_frame<=  EXPLODE_BREAK+EXPLODE_VANISH*9/9)
			HeartTypes[13].render(x[frame],y[frame]);
		else;}
    return true;
}

void heart::move(Background& bg, Score& sc){
	if(pointframe==0){
	if(pause==false){	//not exploding (exploding-> no move)
		if(frame==FLY-1) 				//heart is on head
		{
			if(bg.GetBg()==4)	//turning back //~~
				{explosion_frame=1;pause=true;}

			else //~~
				//not turning back and during game
				{sc++;}
		}
		else{frame++;}}
	}
}


int heart::getFrame(){
	return frame;
}

void heart::update_explosion_frame(Background& bg){
	if(explosion_frame==0) ;
	else if(explosion_frame<120) explosion_frame++;
	else if(explosion_frame==120) {explosion_frame=0; pause=false;}
	bg.SetExplode(pause);
}

bool heart::ReturnPause(){
	return pause;
}

int heart::GetExplodeFrame(){
    return explosion_frame;
}

void heart::SetXY(int i){
	if(i==1){
		int headx = HEADX + HEADW * rand()/RAND_MAX;
		int heady = HEADY + HEADH * rand()/RAND_MAX;
	    for(int i=0;i<FLY;i++){
		x[i]=HEART_X0+i*(headx-HEART_X0)/(FLY-1); //~~
		y[i]=(HEART_Y0-heady)*(x[i]-headx)*(x[i]-headx)/(headx-HEART_X0)/(headx-HEART_X0)+heady;} //~~1
	}
	else if(i==2){
		int headx = HYUNX + HYUNW * rand()/RAND_MAX;
		int heady = HYUNY + HYUNH * rand()/RAND_MAX;
	    for(int i=0;i<FLY;i++){
		x[i]=HYUNX0+i*(headx-HYUNX0)/(FLY-1); //~~
		y[i]=(HYUNY0-heady)*(x[i]-headx)*(x[i]-headx)/(headx-HYUNX0)/(headx-HYUNX0)+heady;} //~~1
	}
}

void heart::Load(){
	HeartTypes[0].loadFromFile("BrokenHeart0.png");

	HeartTypes[1].loadFromFile("star1.png");
	HeartTypes[2].loadFromFile("star2.png");
	HeartTypes[3].loadFromFile("star3.png");
	HeartTypes[4].loadFromFile("star4.png");

	HeartTypes[5].loadFromFile("BrokenHeart1.png");
	HeartTypes[6].loadFromFile("BrokenHeart2.png");
	HeartTypes[7].loadFromFile("BrokenHeart3.png");
	HeartTypes[8].loadFromFile("BrokenHeart4.png");
	HeartTypes[9].loadFromFile("BrokenHeart5.png");
	HeartTypes[10].loadFromFile("BrokenHeart6.png");
	HeartTypes[11].loadFromFile("BrokenHeart7.png");
	HeartTypes[12].loadFromFile("BrokenHeart8.png");
	HeartTypes[13].loadFromFile("BrokenHeart9.png");

}

bool heart::GetPointRender(){
	if(1<=pointframe && pointframe<=5) {HeartTypes[1].render(x[frame],y[frame]);}
	else if(6<=pointframe && pointframe<=10) {HeartTypes[2].render(x[frame],y[frame]);}
	else if(11<=pointframe && pointframe<=15) {HeartTypes[3].render(x[frame],y[frame]);}
	else if(16<=pointframe && pointframe<=20) {HeartTypes[4].render(x[frame],y[frame]);}
	if(pointframe>0)	pointframe++;
	if(pointframe==21){return true;}
	else return false;
}

bool heart::SetGetPoint(){
	if(pointframe==0){
		pointframe++;return true;}
	return false;
}
