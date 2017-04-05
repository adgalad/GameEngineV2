//
//  SP.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/26/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef SP_hpp
#define SP_hpp

#ifdef __cplusplus
#include "Animator.hpp"
#include "Collision.hpp"
#include "Timer.hpp"
#include "Scene.hpp"

#define BulletRight "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/BulletRight.png"
#define BulletLeft  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/BulletLeft.png"
#define SwordSound  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/sword.mp3"
#define SPScript    "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/SP.lua"


using namespace engine ;

double circlef(double x);

void plot(double (*f)(double),Vector2D range,int n = 100, Vector2D scale = Vector2D(1,1));

class Target : public Object {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, Object);
    TAG(ar,rc);
  }
  
	RectangleCollider *rc;
  void Start();
	
  void EnterTrigger(Object *other);
	
  void AfterRender();
};

class TimerJumpAfterBullet : public TimerOld {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, TimerOld);
    TAG(ar,pc);
  }
  
  PhysicController *pc = NULL;
  void Init(){
    pc = (PhysicController*)object->getModule("PhysicController");
  }
  
  void trigger() {
    pc->addForce(Vector2D(0,-20));
  }
  
};

class Bullet : public Object {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, Object);
    TAG(ar,direction);
    TAG(ar,bulletRight);
    TAG(ar,bulletLeft);
  }
	RectangleCollider *rc;
  Bullet(){};
public:
  Bullet(bool d);
	
  void Start();
	
  void Update();
	
  void EnterTrigger(Object *other);
	
  void AfterRender();
private:
	bool direction;
	static shared_ptr<Texture> bulletRight;
	static shared_ptr<Texture> bulletLeft;
};









class SP1 : public Object {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, ObjectT);
    TAG(ar, direction);
    TAG(ar, moving);
    TAG(ar, onGround);
    TAG(ar, speed);
    
  }
public:
	bool direction;
	bool moving;
	bool onGround;
	Animator *anim;
  TimerJumpAfterBullet *timer;
	RectangleCollider *rc;
	RectangleCollider *rc10;
  LuaScript script = LuaScript(SPScript);
  float speed = script.get<float>("sp.speed");

	PhysicController *pc;
  
	Sound sword;
	
  void Start();
	
  void Update();
	
  void EnterCollision(Object *others);
	
  void AfterRender();
};








class SP : public Object {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, ObjectT);
    TAG(ar, steps);
    TAG(ar, direction);
    TAG(ar, moveVector);
  }
public:
  Animator *anim;
  RectangleCollider *rc;
  float steps = 0;
  int direction = 0;
  Vector2D moveVector;
  
  Sound sword;
  
  void Start();
  
  void Update();
  
  void EnterCollision(Object *others);
  
  void AfterRender();
};

EXPORT_KEY(SP)
EXPORT_KEY(SP1)
EXPORT_KEY(Bullet)
EXPORT_KEY(Target)
EXPORT_KEY(TimerJumpAfterBullet)
#endif


#endif /* SP_hpp */
