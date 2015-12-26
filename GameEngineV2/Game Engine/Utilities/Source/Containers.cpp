//
//  Containers.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Containers.hpp"

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


