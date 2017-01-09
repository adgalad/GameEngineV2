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
Vector2D::Vector2D(){
	x = 0;
	y = 0;
}

Vector2D::Vector2D(double x, double y){
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D(SDL_Point p){
	this->x = p.x;
	this->y = p.y;
}


/* Plus */
Vector2D Vector2D::operator + (Vector2D b) const
{
	return Vector2D(x+b.x, y+b.y);
}

/* Minus */
Vector2D Vector2D::operator - (Vector2D b) const
{
	return Vector2D(x-b.x, y-b.y);
}

Vector2D Vector2D::operator - () const
{
	return Vector2D(-x, -y);
}


double Vector2D::operator * (Vector2D p) const
{
	return x*y + p.x*p.y ;
}


Vector2D Vector2D::operator * (double p) const
{
	return Vector2D(x*p, y*p);
}

void Vector2D::operator += (Vector2D p)
{
	this->x += p.x;
	this->y += p.y;
}

Vector2D Vector2D::operator / (double p) const
{
	return Vector2D(x/p, y/p);
}


void Vector2D::operator -= (Vector2D p)
{
	this->x -= p.x;
	this->y -= p.y;
}

void Vector2D::operator *= (double p)
{
	this->x *= p;
	this->y *= p;
}

void Vector2D::operator /= (double p)
{
	this->x /= p;
	this->y /= p;
}

bool Vector2D::operator == (Vector2D v)
{
	return (fabs(x-v.x) <= Epsilon and
					fabs(y-v.y) <= Epsilon);
}

Vector2D Vector2D::round(){
  return Vector2D(roundf(x), roundf(y));
}

double Vector2D::length() const
{
	return sqrt(x*x + y*y);
}

Vector2D Vector2D::unitary() const
{
	float mag = length();
	Vector2D b(x/mag, y/mag);    // vector b's length is always ~ 1
	return b;
}

Vector2D Vector2D::normal() const
{
	return Vector2D(y,-x);
}


//-//-//-//-//-//-//
//    VECTOR3D    //
//-//-//-//-//-//-//

Vector3D::Vector3D(){
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

/* Plus */
Vector3D Vector3D::operator + (Vector3D b){
	return Vector3D(x+b.x, y+b.y, z+b.z);
}


/* Minus */
Vector3D Vector3D::operator - (Vector3D b){
	return Vector3D(x-b.x, y-b.y, z-b.z);
}

Vector3D Vector3D::operator - (){
	return Vector3D(-x, -y, -z);
}



double Vector3D::operator * (Vector3D p)
{
	return x*y + p.x*p.y ;
}

Vector3D Vector3D::operator * (int p)
{
	return Vector3D(x*p, y*p, z*p) ;
}


bool Vector3D::operator == (Vector3D v)
{
	return (x == v.x and y == v.y and z == v.z);
}

Vector3D Vector3D::operator * (double p)
{
	return Vector3D(x*p, y*p, z*p);
}

double Vector3D::length()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::unitary()
{
	double mag = length();
	Vector3D b(x/mag, y/mag, z/mag);    // vector b's length is always 1
	return b;
}

Vector3D Vector3D::normal()
{

	return Vector3D(y,-x,z);
}
