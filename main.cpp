#include "Header.h"
#include <vector>
using namespace std;

#define FPS 120

#define STARTMUSIC	"beforestart.wav"
#define GAME1MUSIC	"shootingstarbgmusic.wav"
#define WIN1MUSIC	"lovemoment.wav"
#define LOSE1MUSIC	"Fail SOUND.wav"
#define GAME2MUSIC	"shootingstarbgmusic.wav"
#define WIN2MUSIC	"stage2success.wav"
#define LOSE2MUSIC	"Fail SOUND.wav"
#define SHOOT_SFX	"woosh.wav"
#define SCORE_SFX	"heart_success.wav"
#define BROKE_SFX	"boom.wav"
#define xHEART_SFX	"wrong.wav" ////~~~~~~

#define SBX 185		//start button x,y,w,h
#define SBY 455
#define SBW 218
#define SBH 91
#define QBX 524		//quit button x,y,w,h
#define QBY 458
#define QBW 203
#define QBH 90
#define AskBX 10
#define AskBY 500
#define AskBW 422
#define AskBH 113

int main(int argc,char* argv[]){

	bool mouse_clicked = true;
	if(!init()){ 			//start up SDL & create window
		printf("Failed to initialize!\n");
	}
	else{
		enum 		stage{start, game1, success1, fail1, game2, success2, fail2, fail22};	//game stage
		stage 		PresentStage = start;
		bool 		quit = false; 	// main loop flag
		SDL_Event 	e;				// event handler
        timer	 	cl;				// public timer

		Mix_Chunk*   	shoot_sfx[3] ;	for(int i=0;i<3;i++) {shoot_sfx[i] = Mix_LoadWAV(SHOOT_SFX);}
		Mix_Chunk*		score_sfx[3] ;	for(int i=0;i<3;i++) {score_sfx[i] = Mix_LoadWAV(SCORE_SFX);}
		Mix_Chunk*		xheart_sfx = NULL;	xheart_sfx = Mix_LoadWAV(xHEART_SFX);
		Mix_Chunk*		broke_sfx = NULL;	broke_sfx = Mix_LoadWAV(BROKE_SFX);
		Mix_Volume(3,40);	Mix_Volume(4,40);	Mix_Volume(5,40);
		Mix_VolumeMusic(80);
		if(shoot_sfx==NULL || score_sfx == NULL || broke_sfx==NULL) printf("chunk fail to load\n");
		heart* InitHeart = new heart;
        //InitHeart[0].SetXY();
        InitHeart[0].Load();
        delete InitHeart;

		while(!quit){

			while( !quit && PresentStage == start ){
				LTexture StartBG;	StartBG.loadFromFile("gamepage.png");	StartBG.render(0,0);
				SDL_RenderPresent( gRenderer );

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS(STARTMUSIC) ;	if(!gMusic){printf("%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);

				while(!quit && PresentStage == start){
					while( SDL_PollEvent(&e) != 0){
            		if( e.type == SDL_MOUSEBUTTONDOWN){
            			if 		( SBX < e.button.x && e.button.x< SBX+SBW && SBY<e.button.y && e.button.y<SBY+SBH)
            				PresentStage = game1;	//click start
            			else if ( QBX < e.button.x && e.button.x< QBX+QBW && QBY<e.button.y && e.button.y<QBY+QBH)
            				quit = true;				//click quit
            		}
            		else if( e.type == SDL_QUIT )quit = true;}}
            }

			while( !quit && PresentStage == game1){
				std::vector<heart*> hearts;

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS(GAME1MUSIC) ;	if(!gMusic){printf("%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);

                cl.reset();
				Background bg1;		// game1 bg textures
				Score sc;			// score bar
				int TempScore;		// storing current score
				Uint32 framecounter =0 ;	// for calculating delay
				bool mouse_clicked = false;	//for generating new heart

				while( !quit && cl.GetTime()<=30000 && sc.GetScore()<100){
			//preprocess
                    heart::update_explosion_frame(bg1);
					framecounter++;					//cout<<framecounter;
					SDL_RenderClear( gRenderer );
	                TempScore = sc.GetScore();
	                if(hearts.size()!=0){
                        if(hearts[0]->GetExplodeFrame()==120){	//~~
                            for(int i=0;i<hearts.size();i++){
                                delete hearts[i];
                            }
                            hearts.clear();
                        }
                        else if(hearts[0]->GetExplodeFrame()==30)
                        	Mix_PlayChannel( -1,broke_sfx, 0 );
                    }
			//user quit or mouse click
	                while( SDL_PollEvent( &e ) != 0 ){
	                    if( e.type == SDL_QUIT ) quit = true;
	                    if (e.type == SDL_MOUSEBUTTONDOWN) {
	                        mouse_clicked = true;
	                        }
                    }
	    	//set background, move Hearts
	                bg1.Move(sc);
	                if(hearts.size()!=0){
	                	for(int i=0;i<hearts.size();i++)
	                		hearts[i]->move(bg1,sc);
                    }
	    	//generate new heart
	                if(mouse_clicked == true) {
	                    if(bg1.GetBg()!=4){
	            	        Mix_PlayChannel( TempScore%3, shoot_sfx[hearts.size()%3], 0 );
	                        heart* a = new heart;//printf("new heart generated\n");
	                        hearts.push_back(a);
                        }
                        else Mix_PlayChannel( -1, xheart_sfx, 0 );
                        mouse_clicked = false;
                    }
			//set the state of heart which has got score
	                if(TempScore!=sc.GetScore()){
	                	Mix_PlayChannel( 3+TempScore%3, score_sfx[TempScore%3], 0 );
	                	int n=0;
	                	bg1.ChangeTurnOnce();
	                    while(!(hearts[n]->SetGetPoint())){
	                    	n++;}
	                }
	    	//render things
	                bg1.render(1);
	            	bool eraseheart = false;
	                if(hearts.size()!=0){
	                	for(int i=0;i<hearts.size();i++){
	                		hearts[i]->render();
	            //render or delete
	                		if(hearts[i]->GetPointRender())
	                			eraseheart = true;
	                   	}
                    }
                    if(eraseheart){
                    	if(hearts.size()!=0) delete hearts[0];
                    	hearts.erase(hearts.begin());
                    }
                    cl.render();
	                sc.Render();
	    	//delay for maintaining frame rate = 60
	                int FrameEndTime = 1000/FPS*framecounter;
	                if(cl.GetTime() < FrameEndTime ){
                            SDL_Delay(FrameEndTime - cl.GetTime());/*cout<<"DELAYED ";*/}
	    	//update
	                SDL_RenderPresent( gRenderer );
	            }
	        //determining next stage
	            if(sc.GetScore()==100) PresentStage = success1; else PresentStage = fail1;
			}

			while( !quit && PresentStage == game2){
				std::vector<heart*> hearts;

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS(GAME2MUSIC) ;	if(!gMusic){printf("game2music%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);


				Background bg1(0);		// game2 bg textures
				Score sc;			// score bar
				int TempScore;		// storing current score
				Uint32 framecounter =0 ;	// for calculating delay
				bool mouse_clicked = false;	//for generating new heart
				LTexture	Bgfk;	Bgfk.loadFromFile("hyun5.jpg");
				LTexture 	Answer;	Answer.loadFromFile("pleaseanswer.png");
				LTexture	AgainButton;	AgainButton.loadFromFile("repeat.png");
				LTexture	Question;	Question.loadFromFile("thequestion.png");
				bool 		CorrectAnswer=false;
				bool		AngryHungYun=false;
				int 		AskFrame=0;

		//~~~~~~THE SCORE WHICH TRIGGER QUESTION IS 60~~~~~~~~~~~//
				cl.reset();
				while( !quit && cl.GetTime()<=30000 && sc.GetScore()<100){
			//preprocess'
					cout<<CorrectAnswer<<"\n";
                    heart::update_explosion_frame(bg1);
					framecounter++;					//cout<<framecounter;
					SDL_RenderClear( gRenderer );
	                TempScore = sc.GetScore();
	                if(hearts.size()!=0){
                        if(hearts[0]->GetExplodeFrame()==120){	//~~
                            for(int i=0;i<hearts.size();i++){
                                delete hearts[i];
                            }
                            hearts.clear();
                        }
                        else if(hearts[0]->GetExplodeFrame()==30)
                        	Mix_PlayChannel( -1,broke_sfx, 0 );
                    }
			//user quit or mouse click
	                while( SDL_PollEvent( &e ) != 0 ){
	                    if( e.type == SDL_QUIT ) quit = true;
	                    if( e.type == SDL_MOUSEBUTTONDOWN ) {
	                        mouse_clicked = true;
	                        }
	                    if( e.type == SDL_KEYDOWN ){
	                    	if(e.key.keysym.sym==SDLK_6 && TempScore>=60 && CorrectAnswer==false){
	                    	CorrectAnswer=true;AngryHungYun=false;AskFrame=0;}
	                    }
                    }
	    	//set background, move Hearts
	                bg1.Move(sc,CorrectAnswer);
	                if(hearts.size()!=0){
	                	for(int i=0;i<hearts.size();i++)
	                		hearts[i]->move(bg1,sc);
                    }
	    	//generate new heart
	                if(mouse_clicked == true) {
	                    if(bg1.GetBg()!=4){
	            	        Mix_PlayChannel( TempScore%3, shoot_sfx[hearts.size()%3], 0 );
	                        heart* a = new heart(0);//printf("new heart generated\n");
	                        hearts.push_back(a);
                        }
                        else if (TempScore>=60 && CorrectAnswer==false &&
                        	e.button.x>AskBX && e.button.x<AskBX+AskBW && e.button.y>AskBY && e.button.y<AskBY+AskBH){
                        		AskFrame=1;AngryHungYun=true;
                        }
                        else Mix_PlayChannel( -1, xheart_sfx, 0 );
                        mouse_clicked = false;
                    }
			//set the state of heart which has got score
	                if(TempScore!=sc.GetScore()){
	                	Mix_PlayChannel( 3+TempScore%3, score_sfx[TempScore%3], 0 );
	                	int n=0;
	                	bg1.ChangeTurnOnce();
	                    while(!(hearts[n]->SetGetPoint())){
	                    	n++;}
	                }
	    	//render things
	                bg1.render();
	                if(AngryHungYun)Bgfk.render(0,0);
	                if(55<TempScore &&TempScore<60) Question.render(210,100,-150,-150);
	                if(TempScore>=60 && CorrectAnswer==false){ Answer.render(210,100,-150,-150);AgainButton.render(AskBX,AskBY,-176,-49);}
	                if(AskFrame>0){
	                	if(AskFrame==200){AskFrame=0;continue;}
	                	Question.render(210,100,-150,-150,int(AskFrame/2));
	                	AskFrame++;
	                }
	            	bool eraseheart = false;
	                if(hearts.size()!=0){
	                	for(int i=0;i<hearts.size();i++){
	                		hearts[i]->render();
	            //render or delete
	                		if(hearts[i]->GetPointRender())
	                			eraseheart = true;
	                   	}
                    }
                    if(eraseheart){
                    	if(hearts.size()!=0) delete hearts[0];
                    	hearts.erase(hearts.begin());
                    }
                    cl.render(2);
	                sc.Render(2);
	    	//delay for maintaining frame rate = 60
	                int FrameEndTime = 1000/FPS*framecounter;
	                if(cl.GetTime() < FrameEndTime ){
                            SDL_Delay(FrameEndTime - cl.GetTime());/*cout<<"DELAYED ";*/}
	    	//update
	                SDL_RenderPresent( gRenderer );
	            }
	        //determining next stage
	            if(sc.GetScore()==100) PresentStage = success2;
	             else if(AngryHungYun)PresentStage = fail22;
	               else PresentStage = fail2;
			}

			while( !quit && PresentStage == success1 ){
				LTexture SC1BG;	SC1BG.loadFromFile("stage1success.png");

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS( WIN1MUSIC ) ;	if(!gMusic){printf("%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);

				SC1BG.render(0,0);
				SDL_RenderPresent( gRenderer );
				while(!quit && PresentStage == success1){
					while( SDL_PollEvent(&e) != 0){
            		if( e.type == SDL_QUIT )quit = true;
            		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE){
            			PresentStage=game2;
            			}}}
            }

            while( !quit && PresentStage == fail1 ){
				LTexture FA1BG;	FA1BG.loadFromFile("stage1fail.png");

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS( LOSE1MUSIC ) ;	if(!gMusic){printf("%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);

				FA1BG.render(0,0);
				SDL_RenderPresent( gRenderer );
				while(!quit && PresentStage == fail1){
					while( SDL_PollEvent(&e) != 0){
            		if( e.type == SDL_QUIT )quit = true;
            		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
            			PresentStage=game1;
            			}}}
            }

            while( !quit && PresentStage == success2 ){
				LTexture SC2BG;	SC2BG.loadFromFile("AC.png");

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS( WIN2MUSIC ) ;	if(!gMusic){printf("%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);
				int i=0;

				while(!quit && PresentStage == success2){

					SDL_RenderClear( gRenderer );
					SC2BG.render2(i/10);
					i++; if(i==1000)i=0;
				SDL_RenderPresent( gRenderer );

					while( SDL_PollEvent(&e) != 0){
            		if( e.type == SDL_QUIT )quit = true;
            		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
            			PresentStage=start;
            			}}}
            }

            while( !quit && PresentStage == fail2 ){	//normal
				LTexture FA2BG;	FA2BG.loadFromFile("RE.png");

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS( LOSE2MUSIC ) ;	if(!gMusic){printf("%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);
				int i=0;


				while(!quit && PresentStage == fail2){
					SDL_RenderClear( gRenderer);
					FA2BG.render2(i/10);
					i++; if(i==1000)i=0;
								SDL_RenderPresent( gRenderer );
					while( SDL_PollEvent(&e) != 0){
            		if( e.type == SDL_QUIT )quit = true;
            		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
            			PresentStage=start;
            			}}}
            }

            while( !quit && PresentStage == fail22 ){	//angryhungyun
				LTexture FA1BG;	FA1BG.loadFromFile("WA.png");

				Mix_FreeMusic(gMusic);
				gMusic = Mix_LoadMUS( LOSE2MUSIC ) ;	if(!gMusic){printf("%s\n",Mix_GetError());}
				Mix_PlayMusic(gMusic,-1);
				int i=0;



				while(!quit && PresentStage == fail22){
					SDL_RenderClear(gRenderer);
					FA1BG.render2(i/10);
					i++;if(i==1000)i=0;
				SDL_RenderPresent( gRenderer );
					while( SDL_PollEvent(&e) != 0){
            		if( e.type == SDL_QUIT )quit = true;
            		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
            			PresentStage=start;
            			}}}
            }
		}
		for(int i=0;i<3;i++)    Mix_FreeChunk( shoot_sfx[i] );
    	for(int i=0;i<3;i++)    Mix_FreeChunk( score_sfx[i] );
    	Mix_FreeChunk( broke_sfx );
    	Mix_FreeChunk( xheart_sfx );

	}
	close();		//free resources and close SDL
	return 0;
}
