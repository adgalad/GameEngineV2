//
//  Time.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/24/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp


#ifdef __cplusplus
#include "GE_SDL.hpp"

namespace engine {
  
  class Time {
    static Time _time;
    Uint32 _lastTick = 0;
    
  public:
    Time(){
      
    }
    
    static void Update() {
      _time._lastTick = SDL_GetTicks();
    }
    inline static Uint32 getTicks(){ return SDL_GetTicks(); }
    
    static double getDeltaTime(){
      return (SDL_GetTicks() - _time._lastTick)/1000.0;
    }
    
  };
  

}



#endif
#endif /* Time_hpp */
