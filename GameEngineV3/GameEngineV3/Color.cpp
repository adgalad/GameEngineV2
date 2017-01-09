//
//  Color.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Color.hpp"

using namespace engine;

Color Color::red   = Color(255,0,0,255);
Color Color::green = Color(0,255,0,255);
Color Color::yellow = Color(255,255,0,255);
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

Color::Color(Uint8 hexValue){
    this->r = hexValue & RMASK;
    this->g = (hexValue & GMASK) >> 8;
    this->b = (hexValue & BMASK) >> 16;
    this->a = (hexValue & AMASK) >> 24;
}

SDL_Color Color::to_SDL_Color(){
		return {r,g,b,a};
}