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
#include <math.h>

template <typename type> class Tuple;


/**
 Create and return a Tuple.
 */

template <class type> Tuple<type> Point(type x, type y, type z = 0);


template <typename type>
class Tuple {
public:
	type x = 0;
	type y = 0;
	type z = 0;
	
	inline Tuple<int> to_int(){ return Point<int>(x, y, z); }
	
	inline Tuple<float> to_float(){ return Point<float>(x, y, z); }
	
	inline SDL_Point to_SDL_Point() { SDL_Point p; p.x = x; p.y = y; return p;}
	
	Tuple<type> operator+(Tuple<type> b);
	
	Tuple<type> operator-(Tuple<type> b);
	
	Tuple<type> operator-();
	
};

class Vector : public Tuple<float> {
public:
	
	Vector(float x, float y, float z = 0){
		this->x = x;
		this->y = y;
	}
	
	float operator * (Vector p);
	
	Vector operator + (int p);
	
	Vector unitaryVector();
	
	Vector normalVector();
};


template <typename type>
inline int abs(type a){
	return a < 0 ? -a : a;
}

#endif /* Math_hpp */
