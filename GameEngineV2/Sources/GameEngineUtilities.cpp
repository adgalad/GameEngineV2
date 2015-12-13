//
//  GameEngineUtilities.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "GameEngineUtilities.hpp"

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

Rect::Rect(int x, int y, int w, int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

SDL_Rect Rect::toSDLRect(){
	const SDL_Rect r = {x,y,w,h};
	return r;
}

Tuple<int> Rect::size(){
	return Point(w,h);
}

Tuple<int> Rect::position(){
	return Point(x,y);
}



SDL_Color Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}


/////////////////
//     SIZE    //
/////////////////

Size Size::operator+(Size b){
	Size r;
	r.setSize(w+b.w, h+b.h, d+b.d);
	return r;
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
//     LIST    //
/////////////////


List::~List(){
	int size = (int)objects.size();
	for (int i = 0 ; i < size; i++){
		delete objects[0];
		objects.erase(objects.begin());
	}
	objects.clear();
}



ListObject *List::getById(int id){
	if (sorted){
		int i = (int)objects.size()/2;
		int half = i;
		while(true){
			if (objects[i]->id() == id) return objects[i];
			if (half == 0) break;
			half = half/2;
			if (objects[i]->id() > id) {
				i -= half;
			}
			else{
				i += half;
			}
			
		}
	}
	else for (int i = 0 ; i < objects.size() ; i++)
	{
		if (objects[i]->id() == id) {
			return objects[i];
		}
	}
	fprintf(stderr, "WARNING couldn't find object on vector\nid: %d\n",id);
	return objects[0];
///**CUIDADO AQUIIIIIIII, AQUI VA EL NULL() antes habia "return type::null()"*/	return NULL;
}

ListObject *List::getByName(std::string name){
	for (int i = 0 ; i < objects.size() ; i++)
	{
		if (objects[i]->name == name) {
			return objects[i];
		}
	}
	fprintf(stderr, "WARNING couldn't find object on vector\nname: %s\n",name.c_str());
	/**CUIDADO AQUIIIIIIII, AQUI VA EL NULL() antes habia "return type::null()"*/
	return objects[0];
}

void List::sort(){
	std::sort(objects.begin(), objects.end(), List::comparison);
	sorted = true;
}


void List::print(){
	printf("Vector {\n");
	for (int i = 0 ; i < objects.size() ; i++)
	{
		printf("\tid: %d\n",objects[i]->id());
	}
	printf("}\n");
}

void List::pushBack(ListObject *object){
	for (int i = 0 ; i < objects.size() ; i++)
	{
		if (objects[i]->id() == object->id()) {
			fprintf(stderr,
					"WARNING trying to insert a duplicated object\nid: %d\n",
					object->id());
			return;
		}
	}
	#ifdef GameEngineDebug
		printf("Object inserted succesfully id: %d name: '%s'\n",object->id(), object->name.c_str());
	#endif
	
	objects.push_back(object);
	sorted = false;
}

void List::erese(int id){
	for (int i = 0 ; i < objects.size() ; i++)
	{
		if (objects[i]->id() == id){
			objects.erase(objects.begin()+i);
			return;
		}
	}
}




SDL_Color Color::red   = {255,0,0,255};
SDL_Color Color::green = {0,255,0,255};
SDL_Color Color::blue  = {0,0,255,255};
SDL_Color Color::black = {0,0,0,255};
SDL_Color Color::white = {255,255,255,255};