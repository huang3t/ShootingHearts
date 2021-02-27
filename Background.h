#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include"Header.h"
#include"LTexture.h"
#include"score.h"
#include"Heart.h"
class Background
{
    private:
        LTexture bg1;
        LTexture bg2;
        LTexture bg3;
        LTexture bg4;
        LTexture bg5; //there are 5 Textures
		bool Explode; // for my function
		bool Turn; //also for mt funciton
		bool fake;  // for my function again
		bool Question;  //still for my function
		int WarningFrame;// the motion of Warning(fake turn)
		int RealTurnFrame;// turn around(1~4)
		int TurnBackFrame;//turn back(4~1)
		bool TurnOnce; // to stop him from turning when the score remain unchainged


    public:
        Background(); // constructor
        Background(int x);  //constructor with value(for stage 2)  (this is overloading)
        int GetBg(int bg = 1); // function with initial value(bg = 1 is the normal case)
		void Move(Score&);//to get correct frame
		void Move(Score&, bool ans); // function overloading, this is for stage 2
		bool SetExplode(bool);// set my bool variable Explode to true or false
		void render(int i=2); //to render picture
		void ChangeTurnOnce(); // to set the TurnOnce


};



#endif // BACKGROUND_H_INCLUDED
