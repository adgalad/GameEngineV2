//
//  Window.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#ifdef __cplusplus
#include "Vector.hpp"

namespace engine {
	
class Window {
public:
	SDL_Window *sdl_window;
	
	Window(string name, Uint32 w, Uint32 h, Uint32 flags = SDL_WINDOW_RESIZABLE);
	
	~Window();
	
	inline Vector2D get_size(){
		int x,y;
		SDL_GetWindowSize(sdl_window, &x, &y);
		return Vector2D(x,y);
	}
	
};
}
#endif

#endif /* Window_hpp */
