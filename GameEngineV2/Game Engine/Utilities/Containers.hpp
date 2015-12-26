//
//  Containers.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Containers_hpp
#define Containers_hpp

#include "ListObject.hpp"
#include <vector>


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

#endif /* Containers_hpp */
