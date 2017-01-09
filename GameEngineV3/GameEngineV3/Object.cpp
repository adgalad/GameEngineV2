//
//  Object.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Object.hpp"

using namespace engine;

template<class Scene, class ObjectModule>
int ObjectT<Scene,ObjectModule>::_id = 1;

template<class Scene, class ObjectModule>
ObjectT<Scene,ObjectModule>::ObjectT() : transform(_transform)
                 , movement(_movement)
                 , deleted(_deleted)
                 , hidden(_hidden)
{
	id = _id;
	++_id;
	_transform = { Vector2D(0,0), Vector2D(1,1)};
}


template<class Scene, class ObjectModule>
ObjectT<Scene,ObjectModule>::ObjectT(string name) : transform(_transform)
                            , movement(_movement)
                            , deleted(_deleted)
                            , hidden(_hidden)
{
	this->name = name;
	id = _id;
	++_id;
	_transform = { Vector2D(0,0), Vector2D(1,1)};
}


//ObjectT<Scene,ObjectModule>::~ObjectT()
template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::Init()
{
	Start();
	for (int i = 0 ; i < modules.size() ; ++i){
		modules[i]->Init();
	}
	_initial_transform = transform;
}


template<class Scene, class ObjectModule>
ObjectModule *ObjectT<Scene,ObjectModule>::getModule(string module_name)
{
	for (int i = 0 ; i < modules.size() ; ++i){
		if (modules[i]->getName() == module_name){
			return modules[i];
		}
	}
	return NULL;
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::addModule(ObjectModule *module)
{
	string name = module->getName();
	if (name == "PhysicController" || name == "Animator"){
		for (int i = 0 ; i < modules.size() ; ++i){
			if (modules[i]->getName() == module->getName()){
				error("Warning: Duplicate module named '" + name + "'");
				return;
			}
		}
	}
	modules.push_back(module);
	module->setObject(this);
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::setPosition(Vector2D new_position)
{
	_transform.position = new_position;
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::setScale(Vector2D new_scale)
{
	_transform.scale = new_scale;
	if (_transform.scale.x < 0) _transform.scale.x = 0;
	if (_transform.scale.y < 0) _transform.scale.y = 0;
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::move(Vector2D move)
{
	_movement += move.round();

}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::Render(){
	if (!texture || hidden){
		return;
	}
  texture->Render(transform.position, transform.scale);
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::InternalUpdate(){
  _deleted = __deleted;
	Update();
	for (int i = 0 ; i < modules.size() ; ++i){
		modules[i]->Update();
	}
	_transform.position += movement;
	_movement = Vector2D(0,0);

}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::Start(){

}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::Update(){
	
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::EnterCollision(ObjectT *other){
	
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::EnterTrigger(ObjectT *other){
	
}

template<class Scene, class ObjectModule>
void ObjectT<Scene,ObjectModule>::AfterRender(){
	
}

