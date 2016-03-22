//
//  Window.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/19/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp


#include <SDL2/SDL.h>
#include "Math.hpp"

class Window {
public:
	
	SDL_Window  *window = NULL;
	
	Window(int w = 640, int h = 480, int flag = SDL_WINDOW_RESIZABLE){
		if (SDL_Init(0) < 0){
			fprintf(stderr, "ERROR initializing SDL.\n%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
		window = SDL_CreateWindow("Game Engine V2 - Recovered",	// window title
								  SDL_WINDOWPOS_UNDEFINED,  // initial x position
								  SDL_WINDOWPOS_UNDEFINED,  // initial y position
								  w,						// width, in pixels
								  h,						// height, in pixels
								  flag						// flags - see below
								  //SDL_WINDOW_MAXIMIZED
								  );
		if (window == NULL){
			fprintf(stderr, "ERROR creating window SDL.\n%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
		printf("SDL was initialized succesfully.\n");
	}
	
	~Window(){
		SDL_DestroyWindow(window);
		window = NULL;
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	}
	
	inline Vector2D get_window_size(){
		SDL_Point size;
		SDL_GetWindowSize(window, &size.x, &size.y);
		return Vector2D(size);
	}
	
	virtual void loop(){
		
	}
	virtual void render(){
	
	}


};





#endif /* Window_hpp */
