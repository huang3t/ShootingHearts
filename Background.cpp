#include"Background.h"
#include"Heart.h"

Background::Background()     // my constructor
{
    bg1.loadFromFile("hogan1.png");
    bg2.loadFromFile("hogan2.png");
    bg3.loadFromFile("hogan3.png");
    bg4.loadFromFile("hogan4.png");
    bg5.loadFromFile("warning.png");  // load all this picture
    WarningFrame = -1;
    RealTurnFrame = -1;
    TurnBackFrame = -1;  // initialize the frame, -1 means they are not enabled
    Explode = false;
    Turn = false;
    fake = false;
    TurnOnce = false;
    Question = false; // all false(initial state)
}

Background::Background(int x)
{
    bg1.loadFromFile("hyun1.jpg");
    bg2.loadFromFile("hyun2.jpg");
    bg3.loadFromFile("hyun3.jpg");
    bg4.loadFromFile("hyun4.jpg");
    bg5.loadFromFile("warning.png");  // stage 2, load other pictures
    WarningFrame = -1;
    RealTurnFrame = -1;
    TurnBackFrame = -1;
    Explode = false;
    Turn = false;
    fake = false;
    TurnOnce = false;
    Question = false;

}



bool Background::SetExplode(bool pause)//to know whether it's exploding
{
    Explode=pause;return Explode; // the variable is from "heart"
}

int Background::GetBg(int bg)//to get correct background
{
    if(WarningFrame<0 && RealTurnFrame<0 && TurnBackFrame<0) {bg = 1;} // initial state


    else if(WarningFrame>=0 && WarningFrame<15 && RealTurnFrame<0)  {bg = 1;}//start to warn(exist 15/120fps second)
    else if(WarningFrame>=15 && WarningFrame<45 && RealTurnFrame<0) {bg = 5;}//this is exclamation mark(exist 30/120fps second)
    else if(WarningFrame>=45 && WarningFrame<=60 && RealTurnFrame<0) {bg = 1;}



    else if(RealTurnFrame>=0 && RealTurnFrame<10 && TurnBackFrame<0)  {bg = 1;}//start to turn around
    else if(RealTurnFrame>=10 && RealTurnFrame<25 && TurnBackFrame<0) {bg = 2;}
    else if(RealTurnFrame>=25 && RealTurnFrame<40 && TurnBackFrame<0) {bg = 3;}

    else if(RealTurnFrame>=40 && RealTurnFrame<=100 && TurnBackFrame<0) {bg = 4;} //fully turned, and no heart hit hogan(stay 0.5 sec and turn back)
    else if(RealTurnFrame>=200 && RealTurnFrame<560 && TurnBackFrame<0) {bg = 4;}//fully turned and hearts hit hogan(punishment 3 sec)


    else if(TurnBackFrame>=0 && TurnBackFrame<15) {bg = 3;}//turn back
    else if(TurnBackFrame>=15 && TurnBackFrame<=30) {bg = 2;}


    return bg;
}

void Background::Move(Score& sc)// to get correct frame
{
    if(fake!= true && !TurnOnce &&(sc.GetScore()==35 || sc.GetScore()==65))
    {
        fake = true;
        WarningFrame = 0;
    }
    else if(fake==true)
    {
        if(WarningFrame>=0 && WarningFrame<60) WarningFrame++;//nothing happened, just turn
        else if(WarningFrame==60)//warning end
        {
            TurnOnce = true;
            WarningFrame = -1;//set to initial state
            fake = false;//start to real turn
        }
    }

    if(!Turn && !TurnOnce && (sc.GetScore()==20 || sc.GetScore() == 50 || sc.GetScore()==70 || sc.GetScore() == 83 || sc.GetScore() == 93))
        {Turn = true;WarningFrame = 0;}//if score is 20, 50 or 90, hogan will turn
    else if(Turn==true)
    {
        if(WarningFrame>=0 && WarningFrame<60) WarningFrame++;//nothing happened, just turn
        else if(WarningFrame==60)//warning end
        {
            WarningFrame = -1;//set to initial state
            RealTurnFrame = 0;//start to real turn
        }
        if(RealTurnFrame>=0 && RealTurnFrame<100)//the real turn range
        {
            RealTurnFrame++;//nothing happened, turn
            if(RealTurnFrame>=40 && Explode==true)//when reach hogan4, deal with heart hit
            {
                RealTurnFrame = 200;//if heart hits hogan during frame30~90(hogan4), goes to the punishment
            }
        }
        else if(RealTurnFrame==100)//end this peacefully(no heart hit hogan)
        {
            Explode=false;
            RealTurnFrame = -1;//set to initial state
            TurnBackFrame = 0;//start to turn back
        }
        else if(RealTurnFrame>=200 && RealTurnFrame<560) {RealTurnFrame++;}//the punishment range(2sec)
        else if(RealTurnFrame==560)
        {
            Explode=false;
            RealTurnFrame = -1;//end the punishment
            TurnBackFrame = 0;//start to turn back
        }
        if(TurnBackFrame>=0 && TurnBackFrame<30) TurnBackFrame++;//just turn back
        else if(TurnBackFrame==30)
        {
            TurnBackFrame = -1;//set to initial
            Turn = false;//end the turn process, set to false
            TurnOnce = true;
        }
            //  else return;
    }

}

void Background::Move(Score& sc, bool ans)  // function overloading for stage 2(almost the same)
{
    if(fake!= true && !TurnOnce && sc.GetScore()==30)
    {
        fake = true;
        WarningFrame = 0;
    }
    else if(fake==true)
    {
        if(WarningFrame>=0 && WarningFrame<60) WarningFrame++;//nothing happened, just turn
        else if(WarningFrame==60)//warning end
        {
            TurnOnce = true;
            WarningFrame = -1;//set to initial state
            fake = false;//start to real turn
        }
    }

    if(!Turn && !TurnOnce && sc.GetScore()== 60)// this is for question
        {Question = true;WarningFrame = 0;}//if he is going to ask question, turn
    else if(Question==true)
    {

            if(WarningFrame>=0 && WarningFrame<60) WarningFrame++;//nothing happened, just turn
            else if(WarningFrame==60)//warning end
            {
                WarningFrame = -1;//set to initial state
                RealTurnFrame = 0;//start to real turn
            }
            if(RealTurnFrame>=0 && RealTurnFrame<40)//the real turn range
            {
                RealTurnFrame++;//nothing happened, turn
            }
            if(RealTurnFrame==40)
            {
                if(ans==true) // if player answer correctly, honyun can turn back
                {
                    RealTurnFrame = -1;
                    TurnBackFrame = 0;
                }
            }
            if(TurnBackFrame>=0 && TurnBackFrame<30) TurnBackFrame++;//just turn back
            else if(TurnBackFrame==30)
            {
                TurnBackFrame = -1;//set to initial
                Question = false;//end the turn process, set to false
                TurnOnce = true;
            }
    }

    if(!Turn && !TurnOnce && (sc.GetScore()==10 || sc.GetScore() == 40 || sc.GetScore() == 88))
        {Turn = true;WarningFrame = 0;}//if score is 20, 50 or 90, hogan will turn
    else if(Turn==true)
    {

            if(WarningFrame>=0 && WarningFrame<60) WarningFrame++;//nothing happened, just turn
            else if(WarningFrame==60)//warning end
            {
                WarningFrame = -1;//set to initial state
                RealTurnFrame = 0;//start to real turn
            }
            if(RealTurnFrame>=0 && RealTurnFrame<100)//the real turn range
            {
                RealTurnFrame++;//nothing happened, turn
                if(RealTurnFrame>=40 && Explode==true)//when reach hogan4, deal with heart hit
                {
                    RealTurnFrame = 200;//if heart hits hogan during frame30~90(hogan4), goes to the punishment
                }
            }
            else if(RealTurnFrame==100)//end this peacefully(no heart hit hogan)
            {
                Explode=false;
                RealTurnFrame = -1;//set to initial state
                TurnBackFrame = 0;//start to turn back
            }
            else if(RealTurnFrame>=200 && RealTurnFrame<560) {RealTurnFrame++;}//the punishment range(2sec)
            else if(RealTurnFrame==560)
            {
                Explode=false;
                RealTurnFrame = -1;//end the punishment
                TurnBackFrame = 0;//start to turn back
            }
            if(TurnBackFrame>=0 && TurnBackFrame<30) TurnBackFrame++;//just turn back
            else if(TurnBackFrame==30)
            {
                TurnBackFrame = -1;//set to initial
                Turn = false;//end the turn process, set to false
                TurnOnce = true;
            }
    }
}

void Background::render(int i){
if(i==2)
{
    if(GetBg()==1) {bg1.render(0, 0);}
    else if(GetBg()==2) {bg2.render(0, 0);}
    else if(GetBg()==3) {bg3.render(0, 0);}
    else if(GetBg()==4) {bg4.render(0, 0);}
    else if(GetBg()==5) {bg1.render(0, 0);bg5.render(153,210,-60,-204);} // render correct picture
    else{printf("\nBG ERROR\n");}
}
else if(i==1)
{
    if(GetBg()==1) {bg1.render(0, 0);}
    else if(GetBg()==2) {bg2.render(0, 0);}
    else if(GetBg()==3) {bg3.render(0, 0);}
    else if(GetBg()==4) {bg4.render(0, 0);}
    else if(GetBg()==5) {bg1.render(0, 0);bg5.render(360,225,-60,-204);}
    else{printf("\nBG ERROR\n");}
}
}
void Background::ChangeTurnOnce() // it is called when the player scores(to avoid the bug that player will not stop turning)
{
    TurnOnce = false;
}
