//
//  Pokemon.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/26/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Pokemon.hpp"




void loadTest(Game *game){
	Scene *scene = new Scene("scene1", Rect(0,0,500,500));
	
	Texture *bg = new Texture("background", Color::blue, 500, 500);
	
	O1 *obj = new O1();
	O2 *obj2 = new O2();
	O2 *obj3 = new O2();
	
	Sprite *spr1 = new Sprite("stand_right",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi crop.png",
							  1,1);
	Sprite *spr2 = new Sprite("walk_right",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi.png",
							  1,8);
	Sprite *spr3 = new Sprite("stand_left",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi crop inverted.png",
							  1,1);
	Sprite *spr4 = new Sprite("walk_left",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi inverted.png",
							  1,8);
	Animator *anim = new Animator();
	
	RectangleCollider *rc1 = new RectangleCollider();
	RectangleCollider *rc2 = new RectangleCollider();
	RectangleCollider *rc3 = new RectangleCollider();
	
	PhysicController *pc = new PhysicController();

	anim->insertSprite(spr1);
	anim->insertSprite(spr2);
	anim->insertSprite(spr3);
	anim->insertSprite(spr4);
	
	obj->addModule(anim);
	obj->addModule(rc1);
	obj->addModule(pc);
	obj->setPosition(Vector2(200,200));
	//	obj2->texture = new Texture("2", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi crop.png");
	obj2->setPosition(Vector2(200,100));
	obj2->addModule(rc2);
	
	obj3->texture = NULL;
	obj3->addModule(rc3);
	
	scene->background = bg;
	scene->addObject(obj);
	scene->addObject(obj2);
  scene->addObject(obj3);
  scene->background = bg;
	game->currentScene = shared_ptr<Scene>(scene);
}




void loadPokemon(Game *game)
{
	
	
	shared_ptr<Texture> grass
        = shared_ptr<Texture>(new Texture("grass",
          "/Users/carlosspaggiari/GameEngineV3/GameEngineV3/Resources/grass.bmp"));
//	Texture *bush = new Texture("bush", "/Users/carlosspaggiari/GameEngineV3/GameEngineV3/pokemon/bush.bmp");
    
	shared_ptr<Scene> s1 =
        shared_ptr<Scene>(new Scene("pokemon scene", Rect(0,0,30*16,30*16)));
	for (int i = 0 ; i < 1; ++i)
	{
		for (int j = 0 ; j < 1 ; ++j)
		{
			Object *obj =  new Object();
			obj->texture = grass;
			obj->setPosition(Vector2(i*16,j*16));
			s1->addObject(obj);
		}
	}
	
	
	
	O1 *obj = new O1();
	Sprite *spr1 = new Sprite("stand_right",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi crop.png",
							  1,1);
	Sprite *spr2 = new Sprite("walk_right",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi.png",
							  1,8);
	Sprite *spr3 = new Sprite("stand_left",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi crop inverted.png",
							  1,1);
	Sprite *spr4 = new Sprite("walk_left",
							  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/yoshi inverted.png",
							  1,8);
	
	Animator *anim = new Animator();
	Animator *anim2 = new Animator();
	RectangleCollider *rc1 = new RectangleCollider();
	RectangleCollider *rc2 = new RectangleCollider();
	
	
	anim->insertSprite(spr1);
	anim->insertSprite(spr2);
	anim->insertSprite(spr3);
	anim->insertSprite(spr4);
	
	anim2->insertSprite(spr1);
	anim2->insertSprite(spr2);
	anim2->insertSprite(spr3);
	anim2->insertSprite(spr4);
	PhysicController *pc = new PhysicController();
	
	obj->addModule(anim);
	obj->addModule(pc);
	obj->addModule(rc1);
	obj->setPosition(Vector2(50,50));
	
	O3 *obj2 = new O3;
	obj2->addModule(anim2);
	obj2->addModule(rc2);
	
    
    RectangleCollider *brc1 = new RectangleCollider();
    RectangleCollider *brc2 = new RectangleCollider();
    RectangleCollider *brc3 = new RectangleCollider();
    RectangleCollider *brc4 = new RectangleCollider();
	
    Object *bush1 = new Object();
    bush1->setPosition(Vector2(0,0));
    bush1->addModule(brc1);
    brc1->rect = Rect(0,0,20*16,5);
    
    Object *bush2 = new Object();
    bush2->setPosition(Vector2(0,0));
    bush2->addModule(brc2);
    brc2->rect = Rect(0,0,5,20*16);
    
    Object *bush3 = new Object();
    bush3->setPosition(Vector2(20*16,0));
    bush3->addModule(brc3);
    brc3->rect = Rect(0,0,5,20*16);
    //    brc3->setTrigger(true);
    
    Object *bush4 = new Object();
    bush4->setPosition(Vector2(0,20*16));
    bush4->addModule(brc4);
    brc4->rect = Rect(0,0,20*16,5);
  
	
	
	s1->addObject(bush1);
	s1->addObject(bush2);
	s1->addObject(bush3);
	s1->addObject(bush4);
	s1->addObject(obj);
//	s1->addObject(obj2);
	game->currentScene = s1;
	
}
