//
//  Vector.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Vector.hpp"

using namespace engine;

//-//-//-//-//-//-//
//    VECTOR2D    //
//-//-//-//-//-//-//
Vector2::Vector2(){
	x = 0;
	y = 0;
}

Vector2::Vector2(double x, double y){
	this->x = x;
	this->y = y;
}

Vector2::Vector2(SDL_Point p){
	this->x = p.x;
	this->y = p.y;
}


/* Plus */
Vector2 Vector2::operator + (Vector2 b) const
{
	return Vector2(x+b.x, y+b.y);
}

/* Minus */
Vector2 Vector2::operator - (Vector2 b) const
{
	return Vector2(x-b.x, y-b.y);
}

Vector2 Vector2::operator - () const
{
	return Vector2(-x, -y);
}


double Vector2::operator * (Vector2 p) const
{
	return x*y + p.x*p.y ;
}


Vector2 Vector2::operator * (double p) const
{
	return Vector2(x*p, y*p);
}

void Vector2::operator += (Vector2 p)
{
	this->x += p.x;
	this->y += p.y;
}

Vector2 Vector2::operator / (double p) const
{
	return Vector2(x/p, y/p);
}


void Vector2::operator -= (Vector2 p)
{
	this->x -= p.x;
	this->y -= p.y;
}

void Vector2::operator *= (double p)
{
	this->x *= p;
	this->y *= p;
}

void Vector2::operator /= (double p)
{
	this->x /= p;
	this->y /= p;
}

bool Vector2::operator == (Vector2 v)
{
	return (fabs(x-v.x) <= Epsilon and
					fabs(y-v.y) <= Epsilon);
}

Vector2 Vector2::round(){
  return Vector2(roundf(x), roundf(y));
}

double Vector2::length() const
{
	return sqrt(x*x + y*y);
}

double Vector2::squareLength() const
{
  return x*x + y*y;
}

Vector2 Vector2::unitary() const
{
	float mag = length();
	Vector2 b(x/mag, y/mag);    // vector b's length is always ~ 1
	return b;
}

Vector2 Vector2::normal() const
{
	return Vector2(y,-x);
}


//-//-//-//-//-//-//
//    VECTOR3D    //
//-//-//-//-//-//-//

Vector3::Vector3(){
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

/* Plus */
Vector3 Vector3::operator + (Vector3 b){
	return Vector3(x+b.x, y+b.y, z+b.z);
}


/* Minus */
Vector3 Vector3::operator - (Vector3 b){
	return Vector3(x-b.x, y-b.y, z-b.z);
}

Vector3 Vector3::operator - (){
	return Vector3(-x, -y, -z);
}



double Vector3::operator * (Vector3 p)
{
	return x*y + p.x*p.y ;
}

Vector3 Vector3::operator * (int p)
{
	return Vector3(x*p, y*p, z*p) ;
}


bool Vector3::operator == (Vector3 v)
{
	return (x == v.x and y == v.y and z == v.z);
}

Vector3 Vector3::operator * (double p)
{
	return Vector3(x*p, y*p, z*p);
}

double Vector3::length()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::unitary()
{
	double mag = length();
	Vector3 b(x/mag, y/mag, z/mag);    // vector b's length is always 1
	return b;
}

Vector3 Vector3::normal()
{

	return Vector3(y,-x,z);
}
