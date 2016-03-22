//
//  Geometry.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Geometry.hpp"
#include <stdlib.h>
#include <math.h>
//////

Rect::Rect(double x, double y, double w, double h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

SDL_Rect Rect::toSDLRect(){
	const SDL_Rect r = {(int)x,(int)y, (int)w, (int)h};

	return r;
}

Vector2D Rect::size(){
	return Vector2D(w,h);
}

Vector2D Rect::position(){
	return Vector2D(x,y);
}

