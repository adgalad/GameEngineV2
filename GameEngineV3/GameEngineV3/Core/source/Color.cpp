//
//  Color.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Color.hpp"

using namespace engine;

Color Color::red    = Color(255,0,0,255);
Color Color::green  = Color(0,255,0,255);
Color Color::yellow = Color(255,255,0,255);
Color Color::blue   = Color(0,0,255,255);
Color Color::black  = Color(0,0,0,255);
Color Color::white  = Color(255,255,255,255);

Color::Color()
  #ifdef ENGINE2D
  {
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 0;
  #else
    : Vector4(0,0,0,0) {
        
  #endif
}

    
    
Color Color::operator + (Color c){
  #ifdef ENGINE2D
    int nr = r + c.r;
    int ng = g + c.g;
    int nb = b + c.b;
    
    return Color(nr <= 255 ? nr : 255,
                 ng <= 255 ? ng : 255,
                 nb <= 255 ? nb : 255);
  #else
    Vector4 v = this->Vector4::operator+(c);
    return Color(v.x <= 255 ? v.x : 255,
                 v.y <= 255 ? v.y : 255,
                 v.z <= 255 ? v.z : 255);
  #endif
}
    
Color Color::operator - (Color c){
  #ifdef ENGINE2D
    int nr = r - c.r;
    int ng = g - c.g;
    int nb = b - c.b;
    return Color(nr >= 0  ? nr : 0, ng >= 0 ? ng : 0, nb >= 0 ? nb : 0);
  #else
    Vector4 v = this->Vector4::operator-(c);
    return Color(v.x >= 0  ? v.x : 0, v.y >= 0 ? v.y : 0, v.z >= 0 ? v.z : 0);
  #endif
}
    

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
  #ifdef ENGINE2D
  {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  #else
    : Vector4(r/255,g/255,b/255,a/255) {
    
  #endif
}

Color::Color(Uint8 hexValue)
  #ifdef ENGINE2D
  {
    this->r = hexValue & RMASK;
    this->g = (hexValue & GMASK) >> 8;
    this->b = (hexValue & BMASK) >> 16;
    this->a = (hexValue & AMASK) >> 24;
  #else
      : Vector4(((hexValue & RMASK) >> 24)/255,
                ((hexValue & GMASK) >> 24)/255,
                ((hexValue & BMASK) >> 24)/255,
                ((hexValue & AMASK) >> 24)/255) {
        
  #endif
}

