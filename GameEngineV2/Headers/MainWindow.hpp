//
//  MainWindow.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/19/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef MainWindow_hpp
#define MainWindow_hpp


#include "Renderer.hpp"

class MainWindow {
	
private:
	SDL_Window   *window   = NULL;
	
public:
	MainWindow(){
		if (SDL_Init(0) < 0){
			fprintf(stderr, "ERROR initializing SDL.\n%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
		window = SDL_CreateWindow("Game Engine V2",			// window title
								  SDL_WINDOWPOS_UNDEFINED,  // initial x position
								  SDL_WINDOWPOS_UNDEFINED,  // initial y position
								  640,                      // width, in pixels
								  480,                      // height, in pixels
								  SDL_WINDOW_RESIZABLE		// flags - see below
								  //SDL_WINDOW_MAXIMIZED
								  );
		Renderer::createRenderer(window);
		printf("SDL was initialized succesfully.\n");
	}
	
	~MainWindow(){
		SDL_DestroyWindow(window);
		window = NULL;
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	}
	Size getWindowSize(){
		Size size;
		SDL_GetWindowSize(window, &size.w, &size.h);
		return size;
	}

};





#endif /* MainWindow_hpp */
