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
	
	virtual bool eventHandler(){
		acceleration = Point<float>(0, 0);
		Uint8 *keyState = EventHandler::get()->keyState;
		int a = 8;
		if (keyState[SDL_GetScancodeFromKey(key[Up])]){
			if (keyState[SDL_GetScancodeFromKey(key[Down])]){
				acceleration.y = 0;
				setAnimated(false);
			}
			else{
				acceleration.y += -a;
				setAnimated(true);
			}
		}
		else if (keyState[SDL_GetScancodeFromKey(key[Down])]){
			acceleration.y += a;
			setAnimated(true);
		}
		
		if (keyState[SDL_GetScancodeFromKey(key[Left])]){
			if (keyState[SDL_GetScancodeFromKey(key[Right])]){
				acceleration.x = 0;
				setAnimated(false);
			}
			else{
				acceleration.x += -a;
				inverted = true;
				setAnimated(true);
			}
		}
		else if (keyState[SDL_GetScancodeFromKey(key[Right])]){
			acceleration.x += a;
			inverted = false;
			setAnimated(true);
		}
	
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
				break;
			
			case SDL_KEYUP:
				bool moveOnY =	keyState[SDL_GetScancodeFromKey(key[Up])] ||
								keyState[SDL_GetScancodeFromKey(key[Down])],
					 moveOnX =	keyState[SDL_GetScancodeFromKey(key[Left])] ||
								keyState[SDL_GetScancodeFromKey(key[Right])];

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
		return true;
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
	virtual bool eventHandler(){
		Player::eventHandler();
		Uint8 *keyState = EventHandler::get()->keyState;
		switch (EventHandler::get()->event.type) {
			case SDL_KEYDOWN:
				if (keyState[SDL_GetScancodeFromKey(SDLK_COMMA)]){
					removeVertex();
				}
				else if (keyState[SDL_GetScancodeFromKey(SDLK_PERIOD)]){
					addVertex();
				}
				break;
			default:
				break;
		}
		return true;
	}
	
};
#endif /* Player_hpp */
