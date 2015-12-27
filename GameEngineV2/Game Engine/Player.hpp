//
//  Player.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Entity.hpp"
#include "Polygon.hpp"

enum moveIndex {
	Up = 0,
	Down,
	Left,
	Right
};

class Player : public Entity {
	
public:
	int key[4] = {	SDLK_UP,
					SDLK_DOWN,
					SDLK_LEFT,
					SDLK_RIGHT};
	
	virtual void eventHandler(){
		acceleration = Point<float>(0, 0);
		int a = 8;
		if (EventHandler::keyState[SDL_GetScancodeFromKey(key[Up])]){
			acceleration.y += -a;
			setAnimated(true);
		}
		if (EventHandler::keyState[SDL_GetScancodeFromKey(key[Down])]){
			acceleration.y += a;
			setAnimated(true);
		}
		
		if (EventHandler::keyState[SDL_GetScancodeFromKey(key[Left])]){
			acceleration.x += -a;
			inverted = true;
			setAnimated(true);
		}
		if (EventHandler::keyState[SDL_GetScancodeFromKey(key[Right])]){
			acceleration.x += a;
			inverted = false;
			setAnimated(true);
		}
	
		switch (EventHandler::event.type) {
			case SDL_KEYDOWN:
				if (EventHandler::keyState[SDL_GetScancodeFromKey(SDLK_m)])
				{
					
				}
				switch (EventHandler::event.key.keysym.sym) {
					case SDLK_n:
						break;
						
					default:
						break;
				}
				break;
			
			case SDL_KEYUP:
				bool moveOnY =	EventHandler::keyState[SDL_GetScancodeFromKey(key[Up])] ||
								EventHandler::keyState[SDL_GetScancodeFromKey(key[Down])],
					 moveOnX =	EventHandler::keyState[SDL_GetScancodeFromKey(key[Left])] ||
								EventHandler::keyState[SDL_GetScancodeFromKey(key[Right])];

				if ( !moveOnX && !moveOnY ){
					setAnimated(false);
					stopX();
					stopY();
				}
				else if (!moveOnY){
					stopY();
				}
				else if (!moveOnX){
					acceleration.x = 0;
					stopX();
				}
		}
	}
};

class PlayerPoligonito : public Player {
	
public:
	PlayerPoligonito(){
		Poligonito *p = new Poligonito();
		p->color = Color(255, 0, 0);
		p->addVertex();
		p->addVertex();
		texture = p;
		
	}
	void addVertex(){
		Poligonito *p = (Poligonito*)texture;
		p->addVertex();
	}
	
	void removeVertex() {
		Poligonito *p = (Poligonito*)texture;
		p->removeVertex();
		
	}
	
	void loop(){
		angle+= 3;
		Player::loop();
	}
	void eventHandler(){
		Player::eventHandler();
		switch (EventHandler::event.type) {
			case SDL_KEYDOWN:
				if (EventHandler::keyState[SDL_GetScancodeFromKey(SDLK_COMMA)]){
					removeVertex();
				}
				else if (EventHandler::keyState[SDL_GetScancodeFromKey(SDLK_PERIOD)]){
					addVertex();
				}
				break;
			default:
				break;
		}
	}
	
};
#endif /* Player_hpp */
