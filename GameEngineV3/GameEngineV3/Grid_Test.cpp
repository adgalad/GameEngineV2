//
//  Grid_Test.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 11/7/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Grid_Test.hpp"

#define JUGADOR_DOWN  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/EfisDown.png"
#define JUGADOR_UP    "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/EfisUp.png"
#define JUGADOR_RIGHT "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/EfisRight.png"
#define JUGADOR_LEFT  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/EfisLeft.png"

void loadGridTest(Game *game){

  
  Sprite* down  = new Sprite("Jugador_up"   , JUGADOR_UP    , 3, 1);
  Sprite* up    = new Sprite("Jugador_down" , JUGADOR_DOWN  , 3, 1);
  Sprite* right = new Sprite("Jugador_right", JUGADOR_RIGHT , 3, 1);
  Sprite* left  = new Sprite("Jugador_left" , JUGADOR_LEFT  , 3, 1);
  
  Animator *anim = new Animator();
  anim->insertSprite(down);
  anim->insertSprite(up);
  anim->insertSprite(right);
  anim->insertSprite(left);
  anim->setSprite("Jugador_down");
  
  Jugador* jugador = new Jugador();
  jugador->addModule(anim);
  
  shared_ptr<Mapa> m = shared_ptr<Mapa>(new Mapa());
  m->addObject(jugador);
  m->camera.setTarget(jugador);
  
  
  game->currentScene = m;
  
}

EXPORT_IMPLEMENT(Jugador)
EXPORT_IMPLEMENT(Mapa)
