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
#include "string"
using namespace std;
class Rect {
	
public:
	
	double x = 0;
	double y = 0;
	double w = 0;
	double h = 0;
	
	Rect(){};
	
	Rect(double x, double y, double w, double h);
	
	Rect intersection(Rect a, Rect b){ return Rect(0,0,0,0);};
	
	SDL_Rect toSDLRect();
	
	Vector2D size();
	
	Vector2D position();
	
	string toStr(){
		return	"("  + to_string(x) +
				", " + to_string(y) +
				", " + to_string(w) +
				", " + to_string(h) + ")";
	}
};



class Segment
{
public:
	Vector2D *p0, *p1;
	float length;
	
	Segment(){}
	
	explicit Segment(Vector2D *v1, Vector2D *v2)
	{
		p0 = v1;
		p1 = v2;
		length = sqrtf((p1->x - p0->x) * (p1->x - p0->x) +
					   (p1->y - p0->y) * (p1->y - p0->y) );
	}
	
	Vector2D direction()
	{
		return Vector2D(p1->x-p0->x, p1->y-p0->y);
	}
};


#endif /* Geometry_hpp */


