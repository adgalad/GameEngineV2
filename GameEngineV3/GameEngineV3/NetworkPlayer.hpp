//
//  NetworkPlayer.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 7/2/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef NetworkPlayer_hpp
#define NetworkPlayer_hpp

#include "Object.hpp"


class UserEvent {
public:
  SDL_Event event;
  int id;
  
};

class NetworkPlayer : public Object {
  

public:
  
  virtual void InternalUpdate(){
    Options.currentObject = this;
    Object::InternalUpdate();
    Options.currentObject = NULL;
  }
  
  int networkId;
  
  NetworkPlayer() : Object(){
    setType(NETWORK_PLAYER);
  }
};

#endif /* NetworkPlayer_hpp */
