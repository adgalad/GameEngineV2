//
//  SP.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/26/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "SP.hpp"

shared_ptr<Texture> Bullet::bulletRight;
shared_ptr<Texture> Bullet::bulletLeft;

EXPORT_IMPLEMENT(SP)
EXPORT_IMPLEMENT(SP1)
EXPORT_IMPLEMENT(Bullet)
EXPORT_IMPLEMENT(Target)
EXPORT_IMPLEMENT(TimerJumpAfterBullet)

double circlef(double x){
	return sqrt(5*5-x*x);
}

void plot(double (*f)(double), Vector2 range, int n, Vector2 scale)
{
	
	Vector2 p2;
    double r    = (range.y - range.x)/n;
    Vector2 p1 = Vector2(range.x*scale.x, -f(range.x)*scale.y)+Vector2(150,150);
	for (double i = range.x+r ; i <= range.y; i += r){
		
		p2 = Vector2(i*scale.x, -f(i)*scale.y)+Vector2(50,150);
		Texture::drawLine(p1, p2);
		p1 = p2;
	}
}


void Target::Start(){
  tag = "target";
  rc = (RectangleCollider*)getModule("RectangleCollider");
  Rect texRect = texture->getRect();
  rc->rect = Rect(0, 0, texRect.w, texRect.h);
}

void Target::EnterTrigger(Object *other) {
  printf("hola\n");
  if (other->tag == "bullet"){
    remove();
  }
}

void Target::AfterRender(){
  Application.renderer()->setDrawColor(Color::red);
  Texture::drawRect(rc->absolute_rect);
  Application.renderer()->setDrawColor(Color::black);
}


Bullet::Bullet(bool d) {
  direction = d;
  if (!bulletRight) {
    bulletRight = shared_ptr<Texture>(new Texture("bullet", BulletRight));
    bulletLeft  = shared_ptr<Texture>(new Texture("bullet", BulletLeft ));
  }
  if (direction)
    texture = bulletRight;
  else
    texture = bulletLeft;
  
}

void Bullet::Start(){
  tag = "bullet";

  Rect r = texture->getRect();
  rc = new RectangleCollider(Rect(0,0, r.w, r.h));
  rc->setTrigger(true);
  addModule(rc);
}

void Bullet::Update(){
  if (direction)
    move(Vector2(5, 0));
  else
    move(Vector2(-5,0));
  
}

void Bullet::EnterTrigger(Object *other){
  if (other->tag == "target") {
    remove();
  }
}

void Bullet::AfterRender(){
  Application.renderer()->setDrawColor(Color::red);
  Texture::drawRect(rc->absolute_rect);
  Application.renderer()->setDrawColor(Color::black);
}



void SP::Start(){
  anim = (Animator*)          getModule("Animator");
  rc   = (RectangleCollider*) getModule("RectangleCollider");

  sword.setChannel(0);
  sword.loadSound(SwordSound);
}

void SP::Update() {
  float n = 3;
  if (steps > 0) {
    move(moveVector);
    --steps;
  } else {
  
    if (Input::KeyDown(KEY_LEFT_ARROW)){
      direction = false;
      steps = 20/n;
      moveVector = Vector2(-5*n,0);
    }
    
    if (Input::KeyDown(KEY_RIGHT_ARROW)){
      direction = true;
      steps = 20/n;
      moveVector = Vector2(5*n,0);
    }

    
    /* Check if the object moving and its direcction */
    if (steps > 0){
      if (direction) anim->setSprite("walk_right");
      else           anim->setSprite("walk_left");
    } else {
      if (direction) anim->setSprite("stand_right");
      else           anim->setSprite("stand_left");
    }
  }
}

void SP::EnterCollision(Object *others){
  
}

void SP::AfterRender(){
  
}
void SP1::Start(){
  anim  = (Animator*)          getModule("Animator");
  rc    = (RectangleCollider*) getModule("RectangleCollider");
  pc    = (PhysicController*)  getModule("PhysicController");
  timer = new TimerJumpAfterBullet();
  addModule(timer);
//  		onGroundCollider = (RectangleCollider*) getModule("onGroundCollider");
  rc10 = new RectangleCollider();
  rc10->rect = Rect(10,10,30,30);
  this->addModule(rc10);
  
  direction = true;
  moving = false;
  pc->setGravity(Vector2(0, 3));
  pc->maxVelocity = Vector2(speed,speed*2);
  sword.setChannel(0);
  sword.loadSound(SwordSound);
  timer->setTimer(3000);
}

void SP1::Update() {
  moving = false;
  
  if (Input::KeyDown(KEY_LEFT_ARROW)){
    pc->addForce(Vector2(-speed,0));
    direction = false;
    moving = true;
  }
  
  
  if (Input::KeyDown(KEY_RIGHT_ARROW)){
    pc->addForce(Vector2(speed,0));
    direction = true;
    moving = true;
  }
  //		if (Input::KeyDown(KEY_DOWN_ARROW)){
  //			move(Vector2(0,n));
  //			moving = true;
  //		}
  if (Input::KeyDown(KEY_UP_ARROW)){
    if (onGround) pc->addForce(Vector2(0,-speed*2));
  }
  if (Input::KeyPressed(KEY_M)){
    if (not timer->isActive()) timer->active();
    Bullet *b = new Bullet(direction);
    b->name = "bullet";
    b->setPosition(direction
                   ? transform.position + Vector2(texture->getSize().x,0)
                   : transform.position - Vector2(b->texture->getSize().x,0));
    b->Init();
    scene->addObject(b);
    sword.play(0);
  }
  
  /* Check if the object moving and its direcction */
  if (moving){
    if (direction) anim->setSprite("walk_right");
    else           anim->setSprite("walk_left");
  } else {
    if (direction) anim->setSprite("stand_right");
    else           anim->setSprite("stand_left");
  }
  onGround = false;
}

void SP1::EnterCollision(Object *others){
  if (others->tag == "ground"){
    onGround = true;
  }
}

void SP1::AfterRender(){
  
}



