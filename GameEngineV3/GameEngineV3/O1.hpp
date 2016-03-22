//
//  O1.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/22/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef O1_hpp
#define O1_hpp

#include "Animator.hpp"

class O1 : public Object {
public:
	
	bool direction;
	Animator *animator;
	
	void Start(){
		direction = true;
		animator = (Animator*)getModule("Animator");
	}
	
	void Update(){
		bool moving = false;
		
		int n = 7;
		if (_input->KeyDown(KEY_LEFT_ARROW)){
			transform.position.x -= n;
			direction = false;
			moving = true;
		}
		if (_input->KeyDown(KEY_RIGHT_ARROW)){
			transform.position.x += n;
			direction = true;
			moving = true;
		}
		if (_input->KeyDown(KEY_UP_ARROW)){
			transform.position.y -= n;
			moving = true;
		}
		if (_input->KeyDown(KEY_DOWN_ARROW)){
			transform.position.y += n;
			moving = true;
		}
		
		if (moving){
			if (direction){
				animator->setSprite("walk_right");
			} else {
				animator->setCurrentSpriteId(3);
			}
		} else {
			if (direction){
				animator->setCurrentSpriteId(0);
			} else {
				animator->setCurrentSpriteId(2);
			}
		}
	}
	
};

#endif /* O1_hpp */
