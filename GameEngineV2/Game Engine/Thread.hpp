//
//  Thread.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Thread_hpp
#define Thread_hpp

#include <SDL2/SDL.h>


class Thread {
	SDL_Thread *thread;
public:
	Thread(){
		thread = NULL;
	}
	
	Thread(SDL_ThreadFunction fn,
		   const char*        name,
		   void*              data){
		thread = SDL_CreateThread(fn, name, data);
		if (!thread) {
			printf("SDL_CreateThread failed: %s\n", SDL_GetError());
		}
	}
	
	void waitThread(){
		SDL_WaitThread(thread, NULL);
	}
};
#endif /* Thread_hpp */
