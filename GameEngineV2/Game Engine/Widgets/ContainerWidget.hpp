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
	
//	virtual void loop(){
//		
//		
//	}

};

#endif /* ContainerWidget_hpp */
