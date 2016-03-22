//
//  Math.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Math_hpp
#define Math_hpp

#include <SDL2/SDL.h>
#include <string>
#include <math.h>


using namespace std;


/**
 Create and return a Tuple.
 */



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


template <typename type>
inline int abs(type a){
	return a < 0 ? -a : a;
}

#endif /* Math_hpp */
