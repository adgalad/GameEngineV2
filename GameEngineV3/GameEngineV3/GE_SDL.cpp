//
//  SDL.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "GE_SDL.hpp"


void GameEngineInit(){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		fprintf(stderr, "ERROR initializing SDL.\n%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP) == 0){
		fprintf(stderr, "ERROR initializing SDL Image.\n%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	TTF_Init();
}

void GameEngineQuit(){
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
