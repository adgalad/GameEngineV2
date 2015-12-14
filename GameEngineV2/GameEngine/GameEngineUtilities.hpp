//
//  GameEngineUtilities.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef GameEngineUtilities_hpp
#define GameEngineUtilities_hpp

#define GameEngineDebug

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "ListObject.hpp"
#include <math.h>


template <typename type> class Tuple;




SDL_Color Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

/**
 Create and return a Tuple.
 */

template <class type> Tuple<type> Point(type x, type y, type z = 0);

/**
 \brief Class Size
 */
class Size{
public:
	int w = 0;
	int h = 0;
	int d = 0;
	
	inline void setSize(int w, int h, int d = 0){
		this->w = w;
		this->h = h;
		this->d = d;
	}
	
	Size operator+(Size b);
};


/**
 \brief Class Tuple
 */


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


class Rect {
	
public:
	
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	
	Rect(){};
	
	Rect(int x, int y, int w, int h);
	
	SDL_Rect toSDLRect();
	
	Tuple<int> size();
	
	Tuple<int> position();
};



template <typename type>
class Vector : public Tuple<type> {
public:
	
	Vector<type> operator*(Vector<type> b);
	Vector<type> operator$(Vector<type> b);
};



template <typename type>
inline int abs(type a){
	return a < 0 ? -a : a;
}


class List {
	std::vector<ListObject*> objects;
	bool sorted = false;
	int id;
	
	static bool comparison(ListObject *a, ListObject *b){
		return a->id() < b->id();
	}

public:
	~List();
	
	inline int size(){
		return (int)objects.size();
	}
	
	inline ListObject *operator[](int i){
		return objects[i];
	}
	
	ListObject *getById(int id);
	
	ListObject *getByName(std::string name);
	
	void sort();
	
	void print();
	
	void pushBack(ListObject *object);
	
	void erese(int id);
};


class Color {
public:
	static SDL_Color red;
	static SDL_Color green;
	static SDL_Color blue;
	static SDL_Color black;
	static SDL_Color white;
};


#endif /* GameEngineUtilities_hpp */
