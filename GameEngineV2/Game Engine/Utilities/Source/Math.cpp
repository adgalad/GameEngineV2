//
//  Math.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Math.hpp"




////////////////////
//    VECTOR2D    //
////////////////////
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
Vector2D Vector2D::operator + (Vector2D b){
	return Vector2D(x+b.x, y+b.y);
}

/* Minus */
Vector2D Vector2D::operator - (Vector2D b){
	return Vector2D(x-b.x, y-b.y);
}

Vector2D Vector2D::operator - (){
	return Vector2D(-x, -y);
}


double Vector2D::operator * (Vector2D p)
{
	return x*y + p.x*p.y ;
}

Vector2D Vector2D::operator * (int p)
{
	return Vector2D(x*p, y*p) ;
}

Vector2D Vector2D::operator * (double p)
{
	return Vector2D(x*p, y*p);
}

double Vector2D::length(){
	return sqrt(x*x + y*y);
}

Vector2D Vector2D::unitaryVector()
{
	float mag = sqrt(x*x + y*y);
	Vector2D b(x/mag, y/mag);    // vector b's length is always 1
	return b;
}

Vector2D Vector2D::normalVector()
{
	return Vector2D(y,-x);
}


////////////////////
//    VECTOR3D    //
////////////////////

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
	return Vector3D(x-b.x, y-b.y, z+b.z);
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

Vector3D Vector3D::operator * (double p)
{
	return Vector3D(x*p, y*p, z*p);
}


Vector3D Vector3D::unitaryVector()
{
	float mag = sqrt(x*x + y*y + z*z);
	Vector3D b(x/mag, y/mag, z/mag);    // vector b's length is always 1
	return b;
}

Vector3D Vector3D::normalVector()
{
	printf("3D Normal vector not revised yet\n");
	return Vector3D(y,-x,z);
}