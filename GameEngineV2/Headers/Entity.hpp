//
//  Entity.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "ListObject.hpp"
#include "PhysicObject.hpp"

class Entity : public PhysicObject, public ListObject{
	static int	__id;
	
public:
	std::vector<std::string> script_paths;
	
	Entity(){
		_id = __id++;
		currentFrame = Point<int>(0, 0);
		script_paths.clear();
	}

	virtual inline void loop(){
		moveEvent();
	}
	
	virtual void eventHandler(SDL_Event *event, Uint8 *keyStates){
		switch (event->type) {
				
			case SDL_KEYDOWN:
				if (keyStates[SDL_GetScancodeFromKey(SDLK_m)])
				{
					
				}
				switch (event->key.keysym.sym) {
					case SDLK_n:
						break;
						
					default:
						break;
				}
		}
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
