//
//  ContainerWidget.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/10/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef ContainerWidget_hpp
#define ContainerWidget_hpp

#include "Widget.hpp"

class ContainerWidget : public Widget {
	
public:
	
	ContainerWidget(Color color, int w, int h){
		texture = Texture::createRGBTexture(color, w, h);
		frameRect = Rect(0, 0, w, h);
	}
	
	virtual bool eventHandler(){
		int n = 10;
		
		if (EventHandler::get()->event.type == SDL_KEYDOWN){
			Uint8 *keyState = EventHandler::get()->keyState;
			if (keyState[SDL_GetScancodeFromKey(SDLK_KP_2)]){
				movePosition(Point<float>(0,n));
				return true;
			}
			if (keyState[SDL_GetScancodeFromKey(SDLK_KP_8)]){
				movePosition(Point<float>(0,-n));
				return true;
			}
			if (keyState[SDL_GetScancodeFromKey(SDLK_KP_6)]){
				movePosition(Point<float>(n,0));
				return true;
			}
			if (keyState[SDL_GetScancodeFromKey(SDLK_KP_4)]){
				movePosition(Point<float>(-n,0));
				return true;
			}
		}
		return true;
	}
//	virtual void loop(){
//		
//		
//	}

};

#endif /* ContainerWidget_hpp */
