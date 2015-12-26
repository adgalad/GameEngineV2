//
//  Geometry.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Geometry.hpp"
#include <stdlib.h>

//////

Rect::Rect(int x, int y, int w, int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

SDL_Rect Rect::toSDLRect(){
	const SDL_Rect r = {x,y,w,h};

	return r;
}

Tuple<int> Rect::size(){
	return Point(w,h);
}

Tuple<int> Rect::position(){
	return Point(x,y);
}


/////////////////
//     SIZE    //
/////////////////

Size Size::operator+(Size b){
	Size r;
	r.setSize(w+b.w, h+b.h, d+b.d);
	return r;
}