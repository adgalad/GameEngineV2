//
//  ObjectModule.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/22/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "ObjectModule.hpp"
#include "Object.cpp"
using namespace engine;

template <class Scene>
ObjectModuleT<Scene>::~ObjectModuleT(){
	setName("");
};

template <class Scene>
string ObjectModuleT<Scene>::getName(){
	return name;
}

template <class Scene>
void ObjectModuleT<Scene>::setName(string name){
	this->name = name;
}

template <class Scene>
void ObjectModuleT<Scene>::setObject(ObjectT<Scene,ObjectModuleT<Scene>> *obj){
	if (object == NULL){
		object = obj;
	} else {
		printf("Modules can't have more than one Object\n");
	}
}

