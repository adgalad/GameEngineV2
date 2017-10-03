//
//  Timer.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 11/5/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include "Time.hpp"
#include "ObjectModule.hpp"

namespace engine {
  
  class Timer : public ObjectModule {
    
  private:
    Uint32  _tick;
    int  _resetTimer = 0;
    int  _timer;
    bool _started = false;
    bool _pause   = false;
    
  public:
    Timer(int ms){
      _resetTimer = ms;
      _timer = ms;
    }
    
    virtual void Start(){};
    
    void StartTimer(){
      _started = true;
      _tick = Time::getTicks();
    }
    
    void StopTimer(){
      _started = false;
    }
    
    void PauseTimer(){
      _pause = true;
    }
    
    void ResumeTimer(){
      _pause = false;
      _tick = Time::getTicks();
    }
    
    void ResetTimer(int ms = -1){
      if (ms == -1) {
        _timer = _resetTimer;
      } else {
        _timer = ms;
      }
      _tick = Time::getTicks();
    }
    
    void Update(){
      
      if (_started){
        if (_timer <= 0){
          Finish();
        }
        else if (_timer > 0 and !_pause) {
          Uint32 newTick = Time::getTicks();
          _timer -= (newTick - _tick);
          _tick = newTick;
        }
      }
    }
    
    inline Uint32 getTimeLeft() { return _timer; }
    
    inline bool finished() {
      return _timer < 0 && _started;
    }
    
    virtual void Finish(){ };
    
  };
  
  
  class TimerOld : public ObjectModule {
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
    TimerOld(){}
    
    ~TimerOld(){}
    
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
EXPORT_ABSTRACT_KEY(TimerOld)
#endif /* Timer_hpp */
