//
//  Timer.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 11/5/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Timer.hpp"

using namespace engine;

void Timer::Update() {
  if ( _active and _firstTick + _timeTrigger <= SDL_GetTicks() ){
    _active    = false;
    _triggered = true;
    trigger();
  } else if (_active){
    printf("%d:%d\n", timeLeft()/1000, (timeLeft()%1000)/10);
  }
}
EXPORT_IMPLEMENT(Timer);
