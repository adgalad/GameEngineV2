//
//  Vector.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp


#ifdef __cplusplus
#include "GE_SDL.hpp"

#define Epsilon 0.00001

#define Point SDL_Point

namespace engine {

class Vector2D {
  SERIALIZE
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar,x);
    TAG(ar,y);
  }
  
public:
	
	double x = 0;
	double y = 0;
	
	Vector2D();
	
	Vector2D(double, double);
	
	Vector2D(SDL_Point);
	
	inline SDL_Point to_SDL_Point() const { return {(int)x, (int)y}; }
#define to_Point to_SDL_Point
	inline Vector2D operator = (SDL_Point p) const { return Vector2D(p.x,p.y); }
	
	Vector2D operator +(Vector2D) const;
	
	Vector2D operator -(Vector2D) const;
	
	Vector2D operator -() const;
	
	Vector2D operator *(double) const;
		
	double operator *(Vector2D) const;

	Vector2D operator /(double) const;
	
	void operator += (Vector2D);
	
	void operator -= (Vector2D);
	
	void operator *= (double);
	
	void operator *= (Vector2D);
	
	void operator /= (double);
	
	bool operator == (Vector2D);
	
  Vector2D round();
  
	double length() const;
  
  double squareLength() const;
	
	Vector2D unitary() const;
	
	Vector2D normal() const;
	
	inline string toStr() const{
		return	"(" + to_string(x) + ", " + to_string(y) + ")";
	}
	
  Vector2D round_ceil() const{
    return Vector2D(ceil(x), ceil(y));
  }
  
  Vector2D round_floor() const{
    return Vector2D(floor(x), floor(y));
  }
};




class Vector3D {
public:
	
	double x = 0;
	double y = 0;
	double z = 0;
	
	Vector3D();
	
	Vector3D(double x, double y, double z = 0);
	
	inline SDL_Point to_SDL_Point() { return {(int)x, (int)y}; }
	
	Vector3D operator +(Vector3D);
	
	Vector3D operator -(Vector3D);
	
	Vector3D operator -();
	
	Vector3D operator *(int);
	
	Vector3D operator *(double);
	
	double operator * (Vector3D);
	
	bool operator == (Vector3D);
	
	double length();
	
	Vector3D unitary();
	
	Vector3D normal();
	
	string toStr(){
		return	"(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")" ;
	}
	
};
}
#endif
#endif /* Vector_hpp */
