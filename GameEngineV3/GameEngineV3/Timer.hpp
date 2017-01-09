//
//  Timer.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 11/5/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include "ObjectModule.hpp"

namespace engine {
  class Timer : public ObjectModule {
    SERIALIZE
    template <class Archive>
    void serialize(Archive & ar, const unsigned int version){
      TAG_BASE(ar, ObjectModule);
      TAG(ar,_timeTrigger);
      TAG(ar,_firstTick);
      TAG(ar,_active);
      TAG(ar,_triggered);
    }
    
  public:
    Timer(){}
    
    ~Timer(){}
    
    inline void activeWithSeconds(Uint32 seconds){
      _timeTrigger = seconds * 1000;
      _firstTick    = SDL_GetTicks();
      _active      = true;
      _triggered   = false;
    }
    
    inline void activeWithMiliseconds(Uint32 mileseconds){
      _timeTrigger = mileseconds;
      _firstTick    = SDL_GetTicks();
      _active      = true;
      _triggered   = false;
    }
    
    inline void setTimer(Uint32 mileseconds){
      _timeTrigger = mileseconds;
    }
    
    inline void active(){
      _firstTick    = SDL_GetTicks();
      _active      = true;
      _triggered   = false;
    }
    
    
    
    inline bool wasTriggered(){ return _triggered;}
    
    inline bool isActive(){ return _active; }
    
    inline Uint32 timeLeft(){ return _firstTick + _timeTrigger - SDL_GetTicks();}
    
    inline Uint32 timerDuration(){ return _timeTrigger;}
    
    virtual void Update();
    
    virtual void Start(){}
    
  private:
    Uint32 _timeTrigger;
    Uint32 _firstTick;
    bool   _active;
    bool   _triggered;
    
    virtual void trigger(){}
    
  };
}
using namespace engine;
EXPORT_ABSTRACT_KEY(Timer)
#endif /* Timer_hpp */
