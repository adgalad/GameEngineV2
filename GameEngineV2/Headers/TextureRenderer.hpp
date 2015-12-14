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

class TextureRenderer{


protected:
	bool animated = false;
	Texture *texture = NULL;
	Tuple<int> currentFrame;
	Rect   *frameRect = NULL;

	Tuple<float> position;
public:
	
	int angle = 0;
	bool inverted = false;
	
	TextureRenderer(){
		currentFrame = Point<int>  (0, 0);
		position	 = Point<float>(0, 0);
	}
	
	virtual ~TextureRenderer(){
		texture = NULL;
	}
	
	inline Size getTextureSize(){
		Rect rect = texture->getRect();
		Size s;
		s.w = rect.w;
		s.h = rect.h;
		return s;
	}
	virtual inline void loadTextureById(int id){
		texture = (Texture*)Texture::textures.getById(id);
	}
	virtual inline void loadTextureByName(std::string name){
		texture = (Texture*)Texture::textures.getByName(name);
	}
	
	inline void setAnimated(bool animated){
		this->animated = animated;
		if (!animated) currentFrame.y = 0;
	}
	
	inline Tuple<float> *getPosition()             { return &position; }
	inline void         setPosition(Tuple<float> p){
		position = p;
	}
	
	virtual void render(){
#ifdef GameEngineDebug

		if (!texture){
			printf("WARNING: trying to render a NULL Texture\ntexture: %p\n",texture);
			texture = (Texture*)Texture::textures[0];
		}
#endif
		if (animated) {
			currentFrame.y = (currentFrame.y + 1) % texture->rows();
		}
		texture->renderTexture(position,currentFrame,angle,inverted,frameRect);
	}
	
};
#endif /* TextureRenderer_hpp */
