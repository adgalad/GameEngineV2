//
//  Geometry.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include "GE_SDL.hpp"

class Rect {
public:
	int x;
	int y;
	int w;
	int h;
	
	Rect(){
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	};
	
	Rect(int x, int y, int w, int h){
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	
	void operator = (Rect other)
	{
		this->x = other.x;
		this->y = other.y;
		this->w = other.w;
		this->h = other.h;
	}
	
	SDL_Rect to_sdl_rect(){
		return {x,y,w,h};
	}
};

#endif /* Geometry_hpp */
