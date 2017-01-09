//
//  Window.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Window.hpp"

using namespace engine;

Window::Window(string name, Uint32 w, Uint32 h, Uint32 flags){
	if (SDL_Init(0) < 0){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR initializing SDL.\n "+string(SDL_GetError())).c_str(),
                             NULL);
		error("ERROR initializing SDL.\n "+string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	sdl_window = SDL_CreateWindow(name.c_str(),			// window title
								  SDL_WINDOWPOS_UNDEFINED,  // initial x position
								  SDL_WINDOWPOS_UNDEFINED,  // initial y position
								  w,						// width, in pixels
								  h,						// height, in pixels
								  flags						// flags - see below
								  //SDL_WINDOW_MAXIMIZED
								  );
	Debug::Log("Window was initialized succesfully.");
}

Window::~Window(){
	SDL_DestroyWindow(sdl_window);
	sdl_window = NULL;
}
