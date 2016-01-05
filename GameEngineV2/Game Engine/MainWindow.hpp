//
//  MainWindow.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/19/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef MainWindow_hpp
#define MainWindow_hpp


#include "Widget.hpp"

class MainWindow {
	
private:
	SDL_Window   *window   = NULL;
	Rect rect;
	List subwidgets;
	
public:
	MainWindow(int w = 640, int h = 480, int flag = SDL_WINDOW_RESIZABLE){
		if (SDL_Init(0) < 0){
			fprintf(stderr, "ERROR initializing SDL.\n%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
		window = SDL_CreateWindow("Game Engine V2",			// window title
								  SDL_WINDOWPOS_UNDEFINED,  // initial x position
								  SDL_WINDOWPOS_UNDEFINED,  // initial y position
								  w,						// width, in pixels
								  h,						// height, in pixels
								  flag						// flags - see below
								  //SDL_WINDOW_MAXIMIZED
								  );
		rect = Rect(0,0,w,h);
		Renderer::get()->setWindow(window);
		printf("SDL was initialized succesfully.\n");
	}
	
	~MainWindow(){
		SDL_DestroyWindow(window);
		window = NULL;
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	}
	Rect getRect(){
		return rect;
	}
	
	
	virtual bool eventHandler(){
		EventHandler::get()->updateKeyState();
		Uint8 *keyState = EventHandler::get()->keyState;
		while(SDL_PollEvent(&EventHandler::get()->event))
		{
			switch (EventHandler::get()->event.type) {
				case SDL_QUIT:
					return false;
					
				case SDL_KEYDOWN:
					if (keyState[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
					{
						return false;
					}
					if (keyState[SDL_GetScancodeFromKey(SDLK_m)])
					{
						
					}

					switch (EventHandler::get()->event.key.keysym.sym) {
						case SDLK_n:{
							Widget *w = (Widget*)subwidgets.getByName("container");
							w->setHide(false);
							break;
						}
							
						default:
							break;
					}
				default:
					
					break;
			}
			for (int i = 0 ; i < subwidgets.size(); i++){
				((Widget*)subwidgets[i])->_eventHandler();
			}
		}
		return true;
	}
	
	
	virtual void loop(){
		SDL_GetWindowSize(window, &rect.w, &rect.h);
		for (int i = 0 ; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->loop();
		}
	}
	virtual void render(){
		for (int i = 0 ; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->render();
		}
	}

	virtual void addSubwidget(Widget *w){
		subwidgets.pushBack(w);
	}
};





#endif /* MainWindow_hpp */
