//
//  Object.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Texture.hpp"
#include "Input.hpp"
#include "ObjectModule.hpp"

struct Transform {
	Vector2D position;
	Vector2D scale;
};

class Object {
	Transform _initial_transform;
	vector<ObjectModule *> modules;
public:

	static Input *_input;

	Transform transform { Vector2D(0,0), Vector2D(0,0)};
	
	Texture *texture = NULL;
	Object() {}
	
	void Init(){
		Start();
		for (int i = 0 ; i < modules.size() ; ++i){
			modules[i]->Start();
		}
		_initial_transform = transform;
	}
	
	void reset(){
		transform = _initial_transform;
	}
	
	ObjectModule *getModule(string module_name){
		for (int i = 0 ; i < modules.size() ; i++){
			if (modules[i]->getName() == module_name){
				return modules[i];
			}
		}
		return NULL;
	}
	
	void addModule(ObjectModule *module){
		for (int i = 0 ; i < modules.size() ; i++){
			if (modules[i]->getName() == module->getName()){
				return;
			}
		}
		modules.push_back(module);
		module->setObject(this);
	}
	
	void Render(){
		if (!texture){
			printf("Texture is NULL\n");
			return;
		}
		texture->Render(transform.position);
	}
	
	void InternalUpdate(){
		Update();
		for (int i = 0 ; i < modules.size() ; i++){
			modules[i]->Update();
		}
	}
	
	virtual void Start(){
		
	}
	
	virtual void Update(){
		
	}
};




#endif /* Object_hpp */
