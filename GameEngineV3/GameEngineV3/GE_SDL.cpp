//
//  GE_SDL.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "GE_SDL.hpp"


using namespace engine;



void engine::error (string err){
	fprintf(stderr,"%s\n",err.c_str());

}

void engine::GameEngineInit(){
	Debug::Init();
	Debug::WriteLog(true);
	Debug::ShowLog(true);
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR: initializing SDL.\n"+string(SDL_GetError())).c_str(),
                             NULL);
		engine::error("ERROR: initializing SDL.\n"+string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	
	if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP) == 0){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR: initializing SDL Image.\n"+string(SDL_GetError())).c_str(),
                             NULL);
		engine::error("ERROR: initializing SDL Image.\n"+string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	
	TTF_Init();

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR initializing SDL Mixer.\n"+string(SDL_GetError())).c_str(),
                             NULL);
		engine::error("ERROR initializing SDL Mixer.\n"+string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	Debug::Log("SDL2 loaded succesfully.");
	Debug::Log("SDL2 Image loaded succesfully.");
	Debug::Log("SDL2 TTF loaded succesfully.");
	Debug::Log("SDL2 Mixer loaded succesfully.");
}

void engine::GameEngineQuit(){
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();
}