//
//  Vector.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include "GE_SDL.hpp"
#include <string>

class Vector2D {
public:
	
	double x = 0;
	double y = 0;
	
	Vector2D();
	
	Vector2D(double, double);
	
	Vector2D(SDL_Point);
	
	inline SDL_Point to_SDL_Point() { SDL_Point p; p.x = x; p.y = y; return p;}
	
	inline Vector2D operator = (SDL_Point p) { return Vector2D(p.x,p.y); }
	
	Vector2D operator +(Vector2D);
	
	Vector2D operator -(Vector2D);
	
	Vector2D operator -();
	
	Vector2D operator *(int);
	
	Vector2D operator *(double);
	
	double operator * (Vector2D);
	
	double length();
	
	Vector2D unitaryVector();
	
	Vector2D normalVector();
	
	inline string toStr(){
		return	"(" + to_string(x) + ", " + to_string(y) + ")";
	}
	
};




class Vector3D {
public:
	
	double x = 0;
	double y = 0;
	double z = 0;
	
	Vector3D();
	
	Vector3D(double x, double y, double z = 0);
	
	inline SDL_Point to_SDL_Point() { SDL_Point p; p.x = x; p.y = y; return p;}
	
	Vector3D operator +(Vector3D);
	
	Vector3D operator -(Vector3D);
	
	Vector3D operator -();
	
	Vector3D operator *(int);
	
	Vector3D operator *(double);
	
	double operator * (Vector3D);
	
	
	
	Vector3D unitaryVector();
	
	Vector3D normalVector();
	
	string toStr(){
		return	"(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")" ;
	}
	
};

#endif /* Vector_hpp */
