//
//  TextureRenderer.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/24/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef TextureRenderer_hpp
#define TextureRenderer_hpp

#include "Texture.hpp"

class TextureRenderer : public ListObject{


protected:
	bool animated = false;
	Texture *texture = NULL;
	SDL_Point currentFrame;
	Rect frameRect;
	bool isStatic = false;
	
	

	Vector2D position;
public:
	
	int angle = 0;
	bool inverted = false;
	
	TextureRenderer(){
		currentFrame = {0,0};
		position	 = Vector2D (0, 0);
	}
	
	virtual ~TextureRenderer(){
		texture = NULL;
	}
	
	inline Vector2D getTextureSize(){
		Rect rect = texture->getRect();
		Vector2D s;
		s.x = rect.w;
		s.y = rect.h;
		return s;
	}
	
	inline void setAnimated(bool animated){
		this->animated = animated;
		if (!animated) currentFrame.y = 0;
	}
	
	inline Vector2D getPosition() {
		return position;
	}
	
	inline void setPosition(Vector2D p){
		position = p;
	}
	
	virtual void loop(){

	}
	

	
};
#endif /* TextureRenderer_hpp */
