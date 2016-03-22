//
//  ObjectModule.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/22/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef ObjectModule_hpp
#define ObjectModule_hpp

#include "GE_SDL.hpp"

class Object;

class ObjectModule{
	
	
	
protected:
	string name;
	Object *object;
	
	ObjectModule(){};
public:
	

	
	virtual ~ObjectModule(){};
	
	inline string getName(){
		return name;
	}
	
	virtual inline void setName(string name){
		this->name = name;
	}
	
	virtual void setObject(Object *obj){
		object = obj;
	}
	
	
	
	virtual void Start() = 0;
	
	virtual void Update() = 0;
	
	
};


#endif /* ObjectModule_hpp */
