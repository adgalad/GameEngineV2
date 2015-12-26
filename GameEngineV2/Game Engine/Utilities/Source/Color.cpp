//
//  Color.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Color.hpp"
Color Color::red   = Color(255,0,0,255);
Color Color::green = Color(0,255,0,255);
Color Color::blue  = Color(0,0,255,255);
Color Color::black = Color(0,0,0,255);
Color Color::white = Color(255,255,255,255);

Color::Color(){
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

SDL_Color Color::to_SDL_Color(){
	return {r,g,b,a};
}