//
//  SP_Scene.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/26/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "SP_Scene.hpp"

#define Background "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/sf2-bg.jpg"
#define GroundTexture "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/sf2-ground.jpg"

#define SPRight      "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/sc_right.png"
#define SPStandRight "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/sc_stand_right.png"
#define SPLeft       "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/sc_left.png"
#define SPStandLeft  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/sc_stand_left.png"
#define TargetTex    "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/target_dummy.gif"

#define pokemon "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/pokemon/pokemon sprites 1111112222233333444445555566666677777888889999900000 copy.bmp"



void LoadSP(Game *game){
	Sprite *walk_right  = new Sprite("walk_right" , SPRight     , 8, 1);
	Sprite *walk_left   = new Sprite("walk_left"  , SPLeft      , 8, 1);
	Sprite *stand_right = new Sprite("stand_right", SPStandRight, 1, 1);
	Sprite *stand_left  = new Sprite("stand_left" , SPStandLeft , 1, 1);

	/*** ANIMATOR ***/
	Animator *anim = new Animator();
	anim->insertSprite(walk_right);
	anim->insertSprite(walk_left);
	anim->insertSprite(stand_right);
	anim->insertSprite(stand_left);
  
  Texture *background = new Texture("bg"       , Background);;

	Texture *groundtex  = new Texture("groundTex", GroundTexture);

	/**** Collider and Physic Controller ****/
	RectangleCollider *rc = new RectangleCollider();
	rc->rect = Rect(15,10,73,120);
	
	PhysicController *pc = new PhysicController();
	pc->maxVelocity = Vector2D(15,30);
	

	
	GroundCollision *gc = new GroundCollision();
	
	/**** SP ****/
  SP1 *sp = new SP1();
	sp->name = "sp";
	sp->addModule(anim);
	sp->addModule(pc);
	sp->addModule(rc);
	sp->addModule(gc);

	
	Object *groundobj = new Object();
  PhysicController *pcGround = new PhysicController();
  pcGround->maxVelocity = Vector2D(0,0);
  pcGround->setFriction(50);
  pcGround->affectedByGravity = false;
  RectangleCollider *groundrc = new RectangleCollider();
  groundrc->rect = groundtex->getRect();
  groundrc->setName("groundRC");
  
	groundobj->name = "ground";
	groundobj->tag  = "ground";
  groundobj->addModule(pcGround);
	groundobj->texture = shared_ptr<Texture>(groundtex);
	groundobj->setPosition(Vector2D(0,750));
	groundobj->addModule(groundrc);
	

//	/* Target Dummy */
	Target *t1 = new Target(),
			   *t2 = new Target(),
			   *t3 = new Target();
	
	shared_ptr<Texture> target = shared_ptr<Texture>(new Texture("target", TargetTex));
	
	t1->addModule(new RectangleCollider());
	t2->addModule(new RectangleCollider());
	t3->addModule(new RectangleCollider());
	t1->texture = target;
	t2->texture = target;
	t3->texture = target;
	t1->setPosition(Vector2D(500,500));
	t2->setPosition(Vector2D(600,500));
	t3->setPosition(Vector2D(700,500));
	
	
	
	
	SPScene *s = new SPScene("SP_scene", background->getRect());
	s->background = background;
	s->camera.setTarget(sp);
	s->addObject(sp);
	s->addObject(groundobj);
	s->addObject(t1);
	s->addObject(t2);
	s->addObject(t3);
	
	game->currentScene = shared_ptr<SPScene>(s);

}

EXPORT_IMPLEMENT(SPScene);
