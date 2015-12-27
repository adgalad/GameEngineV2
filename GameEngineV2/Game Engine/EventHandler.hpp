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

class EventHandler {

	
public:
	
	static SDL_Event event;
	static Uint8 *keyState;
	static bool running;
	
	static void getKeyState(){
		keyState = (Uint8*)SDL_GetKeyboardState(NULL);
	}
};
#endif /* EventHandler_hpp */
