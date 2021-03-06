//
//  main.cpp
//  Test
//
//  Created by Carlos Spaggiari Roa on 5/25/16.
//  Copyright © 2016 ARSC. All rights reserved.
//


#define CATCH_CONFIG_MAIN // Catch creates a main


#include "Vector.hpp"
#include "catch.hpp"

using namespace engine;

TEST_CASE("Vector3"){
	Vector3 v = Vector3(2, 3,10);
	REQUIRE( v.x == 2 );
	REQUIRE( v.y == 3 );
	REQUIRE( v.z == 10 );
	
	Vector3 u = Vector3(-10,5,-6);
	Vector3 w = Vector3(2,3,10);
	
	REQUIRE( not (u == v) );
	REQUIRE( not (v == u) );
	REQUIRE( (w == v) );
	REQUIRE( (v == w) );
	//Test Plus
	w = u+v;
	REQUIRE( w == Vector3(-8,8,4) );
	
	
	//Test Minus
	w = v-u;
	REQUIRE( w == Vector3(12,-2,16) );
	
	
//	//Test Plus Assign
//	w = v;
//	w += u;
//	REQUIRE( w == v+u );
//	
//	
//	//Test Minus Assign
//	w = v;
//	w -= u;
//	REQUIRE( w == v-u );
	
	
	//Test that empty initialization is a null Vector3 (0,0)
	REQUIRE(w == w + Vector3());
	
	//Test Unary Minus
	REQUIRE( Vector3() - v == -v     );
	REQUIRE( Vector3()     == -v + v );
	
	// Test Times
	REQUIRE( w*3 == w+w+w);
	REQUIRE( (w+w)*2 == (w*2) + (w*2) );
	REQUIRE( Vector3(-1,1,-1)*-1 == Vector3(1,-1,1) );
	REQUIRE( w*3.0 == w+w+w);
	REQUIRE( (w+w)*2.2 == (w*2.2) + (w*2.2) );
	REQUIRE( Vector3(-1,1,-1)*-1.0 == Vector3(1,-1,1) );
	
//	//Test Divide
//	w = Vector3(20,-20,20);
//	REQUIRE( ((w/2)/2)*8 == w*2 );
//	REQUIRE( Vector3(-1,1,-1)/-1 == Vector3(1,-1,1) );
	
//	// Times Assign
//	w = v;
//	w *= -2;
//	w *= -1;
//	REQUIRE( w == v*2 );
	
//	// Divide Assign
//	w = v;
//	w /= -2;
//	w /= -1;
//	REQUIRE( w == v/2 );
	
	// Cross Product
	REQUIRE(u*v == u.x*u.y + v.x*v.y );
	REQUIRE(u*v == v*u);
	
	// Length
	REQUIRE(u.length() == sqrt(u.x*u.x + u.y*u.y + u.z*u.z));
	
	
	//Unitary Vector
	REQUIRE(u.unitary() == Vector3(u.x/u.length(),
								   u.y/u.length(),
								   u.z/u.length())
			);
	
	
	// Normal Vector
	REQUIRE(u.normal() == Vector3(u.y,-u.x,u.z));
	
}

TEST_CASE( "Vector2" ) {
	//Test Initialization
	Vector2 v = Vector2(10,-10);
	REQUIRE( v.x == 10 );
	REQUIRE( v.y == -10 );
	
	//Test Plus
	Vector2 u = Vector2(-10,5);
	Vector2 w = v+u;
	REQUIRE( w.x == 0 );
	REQUIRE( w.y == -5 );
	
	
	//Test Minus
	w = v-u;
	REQUIRE( w.x == 20 );
	REQUIRE( w.y == -15 );
	
	
	//Test Plus Assign
	w = v;
	w += u;
	REQUIRE( w.x == 0 );
	REQUIRE( w.y == -5 );
	
	
	//Test Minus Assign
	w = v;
	w -= u;
	REQUIRE( w.x == 20 );
	REQUIRE( w.y == -15 );
	
	//Test Equality of Plus and Plus Assign
	w = v;
	w += u;
	REQUIRE( w == (v+u) );

	//Test Equality of Minus and Minus Assign
	w = v;
	w -= u;
	REQUIRE( w == (v-u) );
	
	//Test that empty initialization is a null Vector2 (0,0)
	REQUIRE(w == w + Vector2());
	
	//Test Unary Minus
	REQUIRE( Vector2() - v == -v     );
	REQUIRE( Vector2()     == -v + v );
	
	// Test Times
	REQUIRE( w*3 == w+w+w);
	REQUIRE( (w+w)*2 == (w*2) + (w*2) );
	REQUIRE( Vector2(-1,1)*-1 == Vector2(1,-1) );
	
	//Test Divide
	w = Vector2(20,-20);
	REQUIRE( ((w/2)/2)*8 == w*2 );
	REQUIRE( Vector2(-1,1)/-1 == Vector2(1,-1) );
	
	// Times Assign
	w = v;
	w *= -2;
	w *= -1;
	REQUIRE( w == v*2 );
	
	// Divide Assign
	w = v;
	w /= -2;
	w /= -1;
	REQUIRE( w == v/2 );
	
	// Cross Product
	REQUIRE(u*v == u.x*u.y + v.x*v.y );
	REQUIRE(u*v == v*u);
	
	// Length
	REQUIRE(u.length() == sqrt(u.x*u.x + u.y*u.y));
	
	// Normal Vector
	REQUIRE(u.normal() == Vector2(u.y,-u.x));
	
	// Unitary Vector
	REQUIRE(u.unitary() == Vector2(u.x/u.length(), u.y/u.length()) );
	
	//Test toSDLPoint
	SDL_Point p1 = {10,-10};
	SDL_Point p2 = v.toSDLPoint();
	REQUIRE( p1.x == p2.x );
	REQUIRE( p1.x == p2.x );
	REQUIRE( Vector2(p2) == v );
}
