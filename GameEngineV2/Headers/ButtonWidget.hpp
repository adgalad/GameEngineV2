//
//  ButtonWidget.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/10/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef ButtonWidget_hpp
#define ButtonWidget_hpp

#include "Widget.hpp"

class ButtonWidget : public Widget{

	virtual void pressed(){
		printf("Button Pressed --\n");
		currentFrame.y = 1;
	}
	
	virtual void released(){
		printf("Button Released -- \n");
		currentFrame.y = 0;
	}
};

#endif /* ButtonWidget_hpp */