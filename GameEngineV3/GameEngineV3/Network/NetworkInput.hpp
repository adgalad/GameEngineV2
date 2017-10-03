//
//  NetworkInput.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 7/2/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef NetworkInput_hpp
#define NetworkInput_hpp

#include "NetworkPlayer.hpp"
namespace engine {
  

  

  
class NetworkInput : public InputT {
  
  inline bool _registerEvent( bool eventHappened,
                              SDL_EventType type,
                              KeyCode key)
  {
    if (eventHappened and Options.currentObject){
      ObjectType oType = ((Object*)Options.currentObject)->getType();
      if (oType == NETWORK_PLAYER) {
        KeyEventP kep = {type, key};
        _netEvents.push_back(kep);
      }
    }
    return eventHappened;
  }
  
public:
  inline void Update() {
    auto i = _netEvents.begin();
    foreach(i, _netEvents){
      cout << "Event: " << i->type << ", " << i->key << endl;
    }
    _netEvents.clear();
    InputT::Update();
  }
  inline bool KeyPressed(KeyCode key) {
    return _registerEvent(InputT::KeyPressed(key), SDL_KEYDOWN, key);
  }
  
  /**
   *  Checks if a key was realesed.
   *
   *  @param key Any value from the KeyCode enum.
   *
   *  @return Returns True if the key was released.
   */
  inline bool KeyReleased(KeyCode key) {
    return _registerEvent(InputT::KeyReleased(key), SDL_KEYUP, key);
    
  }
  
  
  /**
   *  Checks if a key is being held down.
   *
   *  @param key Any value from the KeyCode enum.
   *
   *  @return Returns True if the key is pressed.
   */
  inline bool KeyDown(KeyCode key) {
    return _registerEvent(InputT::KeyDown(key), SDL_KEYDOWN, key);
    
  }
};
}


#endif /* NetworkInput_hpp */
