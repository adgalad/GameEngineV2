//
//  Math.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Math.hpp"

template <>
Tuple<int> Point(int x, int y, int z){
	Tuple<int> p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}

template <>
Tuple<float> Point(float x, float y, float z){
	Tuple<float> p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}


/////////////////
//    TUPLE    //
/////////////////


template <>
Tuple<int> Tuple<int>::operator+(Tuple<int> b){
	return Point<int>(x+b.x, y+b.y, z+b.z);
}

template <>
Tuple<int> Tuple<int>::operator-(Tuple<int> b){
	return Point<int>(x-b.x, y-b.y, z-b.z);
}

template <>
Tuple<int> Tuple<int>::operator-(){
	return Point<int>(-x, -y, -z);
}


template <>
Tuple<float> Tuple<float>::operator+(Tuple<float> b){
	return Point<float>(x+b.x, y+b.y, z+b.z);
}

template <>
Tuple<float> Tuple<float>::operator-(Tuple<float> b){
	return Point<float>(x-b.x, y-b.y, z-b.z);
}

template <>
Tuple<float> Tuple<float>::operator-(){
	return Point<float>(-x, -y, -z);
}

/////////////////
//	  VECTOR   //
/////////////////

float Vector::operator * (Vector p)
{
	return x*y + p.x*p.y ;
}

Vector Vector::operator + (int p)
{
	return Vector(x+p, y+p, z+p) ;
}


Vector Vector::unitaryVector()
{
	float mag = sqrt(x*x + y*y + z*z);
	Vector b(x/mag, y/mag, z/mag);    // vector b's length is always 1
	return b;
}

Vector Vector::normalVector()
{
	return Vector(y,-x);
}
