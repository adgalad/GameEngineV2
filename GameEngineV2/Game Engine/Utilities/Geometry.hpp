//
//  Geometry.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include "Math.hpp"


class Rect {
	
public:
	
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	
	Rect(){};
	
	Rect(int x, int y, int w, int h);
	
	Rect intersection(Rect a, Rect b){ return Rect(0,0,0,0);};
	
	SDL_Rect toSDLRect();
	
	Tuple<int> size();
	
	Tuple<int> position();
};


class Size{
public:
	int w = 0;
	int h = 0;
	int d = 0;
	
	inline void setSize(int w, int h, int d = 0){
		this->w = w;
		this->h = h;
		this->d = d;
	}
	
	Size operator+(Size b);
};


class Segment
{
public:
	Vector *p0, *p1;
	float length;
	
	Segment(){}
	
	explicit Segment(Vector *v1, Vector *v2)
	{
		p0 = v1;
		p1 = v2;
		length = sqrtf((p1->x - p0->x) * (p1->x - p0->x) +
					   (p1->y - p0->y) * (p1->y - p0->y) );
	}
	
	Vector direction()
	{
		return Vector(p1->x-p0->x, p1->y-p0->y);
	}
};


#endif /* Geometry_hpp */


