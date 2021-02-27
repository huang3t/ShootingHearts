#ifndef Header_h
#define Header_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */
#include <sstream>
#include <vector>


#include "Background.h"
#include "timer.h"
#include "Score.h"
#include "Heart.h"
#include "LTexture.h"

extern int SCREEN_WIDTH; 		//globalfunction.cpp
extern int SCREEN_HEIGHT;		//..

//Starts up SDL and creates window
extern bool init();				//..

extern SDL_Event &e;

extern Mix_Music* gMusic;

//Frees media and shuts down SDL
extern void close();

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer*	gRenderer;
extern Mix_Music*		gMusic;
#endif /* Header_h */

