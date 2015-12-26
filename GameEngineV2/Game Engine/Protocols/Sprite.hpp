//
//  Sprite.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/14/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include "Texture.hpp"

class Sprite : public Texture {
protected:
	vector<Rect> collisionRects;
	vector<int>  collisionMap;
	
	int r = 1;					 /**< Number of rows. */
	int c = 1;					 /**< Number of columns. */
public:
	
	virtual void loadImage(string file, int rows, int columns){
		Texture::loadImage(file);
		collisionRects.reserve(sizeof(Rect)*c*r);
		c = columns;
		r = rows;
		srcRect.w = srcRect.w / columns;
		srcRect.h = srcRect.h / rows;
		
		for(int i = 0 ; i < r*c ; i++){
			collisionRects.push_back(srcRect);
		}
	}

	/**
	 Returns the number of rows. if the texture is not a sprite, it's always 1.
	 */
	inline int rows() {return r;}
	
	/**
	 Returns the number of columns. if the texture is not a sprite, it's always 1.
	 */
	inline int columns() {return c;}
	
	virtual Rect getCollisionRect(Tuple<int> frame){
		return collisionRects[frame.y*columns()+frame.x];
	}
};

#endif /* Sprite_hpp */
