//
//  Entity.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "EventHandlerObject.hpp"
#include "PhysicObject.hpp"
#include "Camera.hpp"

class Entity : public PhysicObject, public EventHandlerObject{
	static int	__id;
	
public:
	std::vector<std::string> script_paths;
	
	Entity(){
		_id = __id++;
		currentFrame = Point<int>(0, 0);
		script_paths.clear();
	}

	virtual inline void loop(){
		PhysicObject::loop();
		isStatic = true;
	}
	
	virtual bool eventHandler(){
		Uint8 *keyState = EventHandler::get()->keyState;
		switch (EventHandler::get()->event.type) {
			case SDL_KEYDOWN:
				if (keyState[SDL_GetScancodeFromKey(SDLK_m)])
				{
					
				}
				switch (EventHandler::get()->event.key.keysym.sym) {
					case SDLK_n:
						break;
						
					default:
						break;
				}
		}
		return true;
	}
	
	void setAsCameraTarget(Camera *camera){
		camera->setCameraTarget(&position);
	}
	virtual void print(){
		printf("Entity {\n\tid: %d\n\tname: %s\n\ttexture: %s\n\tx: %f  y: %f\n",_id,name.c_str(),texture->name.c_str(),position.x,position.y);
		for (int i = 0 ; i < script_paths.size(); i++) {
			printf("\tscript: %s\n",script_paths[i].c_str());
		}
		printf("  }\n\n");
	}
};

#endif /* Entity_hpp */
