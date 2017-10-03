//
//  O1.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/22/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef O1_hpp
#define O1_hpp

#ifdef __cplusplus

#include "Animator.hpp"
#include "Collision.hpp"
#include "PhysicController.hpp"
#include "NetworkPlayer.hpp"
#include "Game.hpp"

using namespace engine ;

class O2 : public Object{
	
	RectangleCollider *rc;
	
	void Start(){
		rc = (RectangleCollider*)getModule("RectangleCollider");
	}
	
	void AfterRender(){
		Rect r = rc->absolute_rect;
		r.x -= 1;
		r.y -= 1;
		r.w += 2;
		r.h += 2;
		Application.renderer()->setDrawColor(Color::red);
		Texture::drawRect(r);
		Application.renderer()->setDrawColor(Color::black);
	}
};


class O1 : public NetworkPlayer {
public:
	
  SERIALIZE
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar, direction);
    TAG(ar, xs);
    TAG(ar, ys);
    TAG(ar, trigger);    
    TAG_BASE(ar, Object);
  }

	bool direction;
	int xs,ys;
	bool trigger;
	Animator *animator;
	RectangleCollider *rc;
	PhysicController *pc;

  void Start(){
		direction = true;
		animator = (Animator*)getModule("Animator");
		rc = (RectangleCollider*)getModule("RectangleCollider");
		pc = (PhysicController*)getModule("PhysicController");
    pc->maxVelocity = Vector2(50,500);
		if (not (pc and rc and animator)){
			error("Error: Couldn't find a module. The program will be terminated.");
		}
	}
	
	void Update(){
		
		bool moving = false;

		double n = 10.0;
		xs = 0;
		ys = 0;
		if (Input->KeyDown(KEY_LEFT_ARROW)){
//			pc->addForce(Vector2(-5,0));
			move(Vector2(-n,0));
			xs = -n;
			direction = false;
			moving = true;

		}
		if (Input->KeyDown(KEY_RIGHT_ARROW)){
//			pc->addForce(Vector2(5,0));
			move(Vector2(n,0));
			xs = n;
			direction = true;
			moving = true;
			
		}
//		if (Input->KeyDown(KEY_UP_ARROW)){
//			pc->addForce(Vector2(0,-5));
//		}
//		
		if (Input->KeyDown(KEY_DOWN_ARROW)){
			pc->addForce(Vector2(0,5));
		}
		if (Input->KeyDown(KEY_UP_ARROW)){
			pc->addForce(Vector2(0,-9));

//			move(Vector2(0,-n));
			ys = n;
			moving = true;
		}
//		if (Input->KeyDown(KEY_DOWN_ARROW)){
//			move(Vector2(0,n));
//			ys = n;
//			moving = true;
//		}
		
		if (Input->KeyDown(KEY_NUMPAD_PLUS)){
			setScale(transform.scale + Vector2(0.1,0.1));
		}
		else if (Input->KeyDown(KEY_NUMPAD_MINUS)){
			setScale(transform.scale - Vector2(0.1,0.1));
		}
		
		if (Input->KeyDown(KEY_COMMA)){
			pc->addForce(Vector2(5,-5));
		}
		if (moving) {
			if (direction){
				animator->setSprite("walk_right");
			} else {
				animator->setSprite("walk_left");
			}
		} else {
			if (direction){
				animator->setSprite("stand_right");
			} else {
				animator->setSprite("stand_left");
			}
		}

	}
	
	void EnterCollision(Object *other){

	}
	
	void EnterTrigger(Object *other){
		trigger = true;
	}
	
	void AfterRender(){
		Rect r = rc->absolute_rect;
		r.x -= 1;
		r.y -= 1;
		r.w += 2;
		r.h += 2;
		
		if (trigger) Application.renderer()->setDrawColor(Color::green);
		else		 Application.renderer()->setDrawColor(Color::red);
		
		Texture::drawRect(r);
		Application.renderer()->setDrawColor(Color::black);
		
		trigger = false;
	}
	
};

class O3 : public Object {
public:
	
	bool direction;
	int xs,ys;
	Animator *animator;
	RectangleCollider *rc;
	PhysicController *pc;
    
    ~O3(){
        if (animator) delete animator;
        if (rc)       delete rc;
        if (pc)       delete pc;
    }
    
	void Start(){
		direction = true;
		animator = (Animator*)getModule("Animator");
		rc = (RectangleCollider*)getModule("RectangleCollider");
		pc = (PhysicController*)getModule("PhysicController");
	}
	
	void Update(){
		
		bool moving = false;
		
		double n = 10.0;
		xs = 0;
		ys = 0;
		if (Input->KeyDown(KEY_A)){
			move(Vector2(-n,0));
			xs = -n;
			direction = false;
			moving = true;
			
		}
		if (Input->KeyDown(KEY_D)){
			move(Vector2(n,0));
			xs = n;
			direction = true;
			moving = true;
			
		}
		if (Input->KeyDown(KEY_W)){
			move(Vector2(0,-n));
			ys = n;
			moving = true;
		}
		if (Input->KeyDown(KEY_S)){
			move(Vector2(0,n));
			ys = n;
			moving = true;
		}
		
		if (Input->KeyDown(KEY_NUMPAD_PLUS)){
			setScale(transform.scale + Vector2(0.1,0.1));
		}
		else if (Input->KeyDown(KEY_NUMPAD_MINUS)){
			setScale(transform.scale - Vector2(0.1,0.1));
		}
    if (moving) {
      if (direction){
        animator->setSprite("walk_right");
      } else {
        animator->setSprite("walk_left");
      }
    } else {
      if (direction){
        animator->setSprite("stand_right");
      } else {
        animator->setSprite("stand_left");
      }
    }
		
	}
	
	void EnterCollision(Object *other){
		
	}


	void AfterRender(){
		Application.renderer()->setDrawColor(Color::red);
		Texture::drawRect(rc->absolute_rect);
		Application.renderer()->setDrawColor(Color::black);
	}
	
};

#endif


EXPORT_KEY(O1);



#endif /* O1_hpp */
