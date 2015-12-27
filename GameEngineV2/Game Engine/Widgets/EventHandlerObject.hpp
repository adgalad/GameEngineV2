//
//  EventHandlerObject.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef EventHandlerObject_hpp
#define EventHandlerObject_hpp

#include "EventHandler.hpp"


class EventHandlerObject {
	
	friend class Game;
public:
	virtual void _eventHandler(){
		eventHandler();
	}

	virtual void eventHandler(){}

};
#endif /* EventHandlerObject_hpp */
