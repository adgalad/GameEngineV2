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
	
	virtual void eventHandler(){
		int n = 10;
		
		if (EventHandler::event.type == SDL_KEYDOWN){
			if (EventHandler::keyState[SDL_GetScancodeFromKey(SDLK_KP_2)]){
				movePosition(Point<float>(0,n));
				return;
			}
			if (EventHandler::keyState[SDL_GetScancodeFromKey(SDLK_KP_8)]){
				movePosition(Point<float>(0,-n));
				return;
			}
			if (EventHandler::keyState[SDL_GetScancodeFromKey(SDLK_KP_6)]){
				movePosition(Point<float>(n,0));
				return;
			}
			if (EventHandler::keyState[SDL_GetScancodeFromKey(SDLK_KP_4)]){
				movePosition(Point<float>(-n,0));
				return;
			}
		}
	}
//	virtual void loop(){
//		
//		
//	}

};

#endif /* ContainerWidget_hpp */
