//
//  Framerate.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 6/9/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Framerate_hpp
#define Framerate_hpp

#include "Time.hpp"

namespace engine {

class Framerate {
  
public:
	Framerate (){}
	
	void Init(){
    
//		_currentfps = 1;
    _start = Time::getTicks();

	}
  inline Uint32 getFPS() const { return _maxfps; }
  
	void Update() {
    
    Uint32 currentTick = Time::getTicks();
    int    delta       = (int)currentTick - (int)_start;
    
    _start = currentTick;
    if (delta < _avg) SDL_Delay(2*(_avg - delta)); // Delay between each loop.
                                                   // Reasons for the factor 2
                                                   // are still unknown.
                                                   // It just work :).
	}
	
	inline void setFPS(Uint32 fps){
		_maxfps = fps;
    _avg    = 1000/fps;
	}
private:
	Uint32 _maxfps;
  int    _avg;
	Uint32 _start;
};
}
#endif /* Framerate_hpp */
