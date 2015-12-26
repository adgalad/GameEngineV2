//
//  Scene.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Player.hpp"
#include "Widget.hpp"

class Scene : public Widget{
	static int __id;
	Texture *texture = NULL;
	
	Rect rect;
	
public:

	List entities;/**< List with all the Entity objects inside the scene */
	List players; /**< List with all the Widget objects inside the scene */
	
	virtual ~Scene(){
		texture = NULL;
	}
	Scene(){
		_id = __id++;
	};
	
	virtual void eventHandler(SDL_Event *event, Uint8 *keyStates){
		switch (event->type) {
		}
		for (int i = 0; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->eventHandler(event, keyStates);
		}
		for (int i = 0; i < entities.size(); i++) {
			((Entity*)entities[i])->eventHandler(event, keyStates);
		}
		for (int i = 0; i < players.size(); i++) {
			((Player*)players[i])->eventHandler(event, keyStates);
		}
		
	}
	
	virtual void loop(){
		for (int i = 0; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->loop();
		}
		for (int i = 0; i < entities.size(); i++) {
			((Entity*)entities[i])->loop();
		}
		for (int i = 0; i < players.size(); i++) {
			((Player*)players[i])->loop();
		}
	}
	
	virtual void render(){
		Widget::render();

		for (int i = 0; i < entities.size(); i++) {
			((Entity*)entities[i])->render();
		}
		for (int i = 0; i < players.size(); i++) {
			((Player*)players[i])->render();
		}
	}
};
#endif /* Scene_hpp */
