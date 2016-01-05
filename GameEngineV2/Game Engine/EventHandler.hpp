//
//  EventHandler.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef EventHandler_hpp
#define EventHandler_hpp

#include <SDL2/SDL.h>
class Game;
class EventHandler {
	friend Game;
	static EventHandler *__eventHandler_instance__;
	
	EventHandler(){};
	
	virtual ~EventHandler(){

	}

public:
	
	static EventHandler *get(){
		if (__eventHandler_instance__ == NULL) {
			__eventHandler_instance__ = new EventHandler();
		}
		return __eventHandler_instance__;
	}
	SDL_Event event;
	bool running;
	Uint8 *keyState = NULL;
	void updateKeyState(){
		keyState = (Uint8*)SDL_GetKeyboardState(NULL);
	}
};
#endif /* EventHandler_hpp */
