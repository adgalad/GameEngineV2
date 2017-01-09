//
//  Geometry.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Geometry.hpp"

using namespace engine;

Rect::Rect(){
	x = 0;
	y = 0;
	w = 0;
	h = 0;
};

Rect::Rect(int x, int y, int w, int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void Rect::operator = (Rect other)
{
	this->x = other.x;
	this->y = other.y;
	this->w = other.w;
	this->h = other.h;
}


Circle::Circle(Vector2D center, double radio){
	this->center = center;
	this->radio = Vector2D(radio,radio);
}

Circle::Circle(Vector2D center, Vector2D radio){
	this->center = center;
	this->radio = radio;
}

