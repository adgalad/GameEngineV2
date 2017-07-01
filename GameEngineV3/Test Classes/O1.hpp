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
<<<<<<< HEAD
=======
#include "Game.hpp"
>>>>>>> OpenGL

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
<<<<<<< HEAD
		Texture::renderer->setRenderColor(Color::red);
		Texture::drawRect(r);
		Texture::renderer->setRenderColor(Color::black);
=======
		Application.renderer()->setDrawColor(Color::red);
		Texture::drawRect(r);
		Application.renderer()->setDrawColor(Color::black);
>>>>>>> OpenGL
	}
};

class O1 : public Object {
public:
	
<<<<<<< HEAD
=======
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
  
>>>>>>> OpenGL
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
<<<<<<< HEAD
    pc->maxVelocity = Vector2D(50,500);
=======
    pc->maxVelocity = Vector2(50,500);
>>>>>>> OpenGL
		if (not (pc and rc and animator)){
			error("Error: Couldn't find a module. The program will be terminated.");
		}
	}
	
	void Update(){
		
		bool moving = false;

		double n = 10.0;
		xs = 0;
		ys = 0;
		if (Input::KeyDown(KEY_LEFT_ARROW)){
<<<<<<< HEAD
//			pc->addForce(Vector2D(-5,0));
			move(Vector2D(-n,0));
=======
//			pc->addForce(Vector2(-5,0));
			move(Vector2(-n,0));
>>>>>>> OpenGL
			xs = -n;
			direction = false;
			moving = true;

		}
		if (Input::KeyDown(KEY_RIGHT_ARROW)){
<<<<<<< HEAD
//			pc->addForce(Vector2D(5,0));
			move(Vector2D(n,0));
=======
//			pc->addForce(Vector2(5,0));
			move(Vector2(n,0));
>>>>>>> OpenGL
			xs = n;
			direction = true;
			moving = true;
			
		}
//		if (Input::KeyDown(KEY_UP_ARROW)){
<<<<<<< HEAD
//			pc->addForce(Vector2D(0,-5));
//		}
//		
		if (Input::KeyDown(KEY_DOWN_ARROW)){
			pc->addForce(Vector2D(0,5));
		}
		if (Input::KeyDown(KEY_UP_ARROW)){
			pc->addForce(Vector2D(0,-9));

//			move(Vector2D(0,-n));
=======
//			pc->addForce(Vector2(0,-5));
//		}
//		
		if (Input::KeyDown(KEY_DOWN_ARROW)){
			pc->addForce(Vector2(0,5));
		}
		if (Input::KeyDown(KEY_UP_ARROW)){
			pc->addForce(Vector2(0,-9));

//			move(Vector2(0,-n));
>>>>>>> OpenGL
			ys = n;
			moving = true;
		}
//		if (Input::KeyDown(KEY_DOWN_ARROW)){
<<<<<<< HEAD
//			move(Vector2D(0,n));
=======
//			move(Vector2(0,n));
>>>>>>> OpenGL
//			ys = n;
//			moving = true;
//		}
		
		if (Input::KeyDown(KEY_NUMPAD_PLUS)){
<<<<<<< HEAD
			setScale(transform.scale + Vector2D(0.1,0.1));
		}
		else if (Input::KeyDown(KEY_NUMPAD_MINUS)){
			setScale(transform.scale - Vector2D(0.1,0.1));
		}
		
		if (Input::KeyDown(KEY_COMMA)){
			pc->addForce(Vector2D(5,-5));
=======
			setScale(transform.scale + Vector2(0.1,0.1));
		}
		else if (Input::KeyDown(KEY_NUMPAD_MINUS)){
			setScale(transform.scale - Vector2(0.1,0.1));
		}
		
		if (Input::KeyDown(KEY_COMMA)){
			pc->addForce(Vector2(5,-5));
>>>>>>> OpenGL
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
		
<<<<<<< HEAD
		if (trigger) Texture::renderer->setRenderColor(Color::green);
		else		 Texture::renderer->setRenderColor(Color::red);
		
		Texture::drawRect(r);
		Texture::renderer->setRenderColor(Color::black);
=======
		if (trigger) Application.renderer()->setDrawColor(Color::green);
		else		 Application.renderer()->setDrawColor(Color::red);
		
		Texture::drawRect(r);
		Application.renderer()->setDrawColor(Color::black);
>>>>>>> OpenGL
		
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
<<<<<<< HEAD
        delete animator;
        delete rc;
        delete pc;
=======
        if (animator) delete animator;
        if (rc)       delete rc;
        if (pc)       delete pc;
>>>>>>> OpenGL
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
		if (Input::KeyDown(KEY_A)){
<<<<<<< HEAD
			move(Vector2D(-n,0));
=======
			move(Vector2(-n,0));
>>>>>>> OpenGL
			xs = -n;
			direction = false;
			moving = true;
			
		}
		if (Input::KeyDown(KEY_D)){
<<<<<<< HEAD
			move(Vector2D(n,0));
=======
			move(Vector2(n,0));
>>>>>>> OpenGL
			xs = n;
			direction = true;
			moving = true;
			
		}
		if (Input::KeyDown(KEY_W)){
<<<<<<< HEAD
			move(Vector2D(0,-n));
=======
			move(Vector2(0,-n));
>>>>>>> OpenGL
			ys = n;
			moving = true;
		}
		if (Input::KeyDown(KEY_S)){
<<<<<<< HEAD
			move(Vector2D(0,n));
=======
			move(Vector2(0,n));
>>>>>>> OpenGL
			ys = n;
			moving = true;
		}
		
		if (Input::KeyDown(KEY_NUMPAD_PLUS)){
<<<<<<< HEAD
			setScale(transform.scale + Vector2D(0.1,0.1));
		}
		else if (Input::KeyDown(KEY_NUMPAD_MINUS)){
			setScale(transform.scale - Vector2D(0.1,0.1));
=======
			setScale(transform.scale + Vector2(0.1,0.1));
		}
		else if (Input::KeyDown(KEY_NUMPAD_MINUS)){
			setScale(transform.scale - Vector2(0.1,0.1));
>>>>>>> OpenGL
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
<<<<<<< HEAD
		Texture::renderer->setRenderColor(Color::red);
		Texture::drawRect(rc->absolute_rect);
		Texture::renderer->setRenderColor(Color::black);
=======
		Application.renderer()->setDrawColor(Color::red);
		Texture::drawRect(rc->absolute_rect);
		Application.renderer()->setDrawColor(Color::black);
>>>>>>> OpenGL
	}
	
};

#endif

<<<<<<< HEAD

=======
EXPORT_KEY(O1);
>>>>>>> OpenGL




#endif /* O1_hpp */
