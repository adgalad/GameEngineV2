//
//  Window.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "Vector.hpp"

class Window {
	Vector2D size;
public:
	SDL_Window *sdl_window;
	
	Window(string name, Uint32 w, Uint32 h, Uint32 flags = SDL_WINDOW_RESIZABLE){
		if (SDL_Init(0) < 0){
			fprintf(stderr, "ERROR initializing SDL.\n%s",SDL_GetError());
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
		size = Vector2D(w,h);
		printf("SDL was initialized succesfully.\n");
	}
	~Window(){
		SDL_DestroyWindow(sdl_window);
		sdl_window = NULL;
	}
	
	inline Vector2D get_size(){	return size; }
	
};

#endif /* Window_hpp */
