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
	
	virtual void eventHandler(SDL_Event *event, Uint8 *keyStates){
		acceleration = Point<float>(0, 0);
		int a = 8;
		if (keyStates[SDL_GetScancodeFromKey(key[Up])]){
			acceleration.y += -a;
			setAnimated(true);
		}
		if (keyStates[SDL_GetScancodeFromKey(key[Down])]){
			acceleration.y += a;
			setAnimated(true);
		}
		
		if (keyStates[SDL_GetScancodeFromKey(key[Left])]){
			acceleration.x += -a;
			inverted = true;
			setAnimated(true);
		}
		if (keyStates[SDL_GetScancodeFromKey(key[Right])]){
			acceleration.x += a;
			inverted = false;
			setAnimated(true);
		}
	
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
				break;
			
			case SDL_KEYUP:
				bool moveOnY =	keyStates[SDL_GetScancodeFromKey(key[Up])] ||
								keyStates[SDL_GetScancodeFromKey(key[Down])],
					 moveOnX =	keyStates[SDL_GetScancodeFromKey(key[Left])] ||
								keyStates[SDL_GetScancodeFromKey(key[Right])];

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
	void eventHandler(SDL_Event *event, Uint8 *keyStates){
		Player::eventHandler(event, keyStates);
		switch (event->type) {
			case SDL_KEYDOWN:
				if (keyStates[SDL_GetScancodeFromKey(SDLK_COMMA)]){
					removeVertex();
				}
				else if (keyStates[SDL_GetScancodeFromKey(SDLK_PERIOD)]){
					addVertex();
				}
				break;
			default:
				break;
		}
	}
	
};
#endif /* Player_hpp */
