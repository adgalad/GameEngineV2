//
//  Ghost.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 4/4/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "Ghost.hpp"


void Ghost::setFrightened (){
  if ( mode == Dead) return;
  scaryFace = true;
  scary = true;
  TimerGhost *t = (TimerGhost*)timer;
  if (not saved.alreadySaved){
    saved.timer = t->getTimeLeft();
    saved.wave = t->nwave;
    saved.mode = mode;
  }
  saved.alreadySaved = true;
  t->ResetTimer(5000);
  mode = Frightened;
  anim->setSprite("frightened");
  dir = reverse();
  vel = 2;
  
}

void Ghost::outFrightened (){
  scaryFace = false;
  
  TimerGhost *t = (TimerGhost*)timer;
  t->nwave = saved.wave;
  t->ResetTimer(saved.timer);
  saved.alreadySaved = false;
  mode = saved.mode;
  vel = 4;
  switch (dir) {
    case Up:    anim->setSprite("up");
    case Down:  anim->setSprite("down");
    case Right: anim->setSprite("right");
    case Left:  anim->setSprite("left");
  }
}
