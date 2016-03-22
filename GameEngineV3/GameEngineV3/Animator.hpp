//
//  Animator.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Animator_hpp
#define Animator_hpp

#include "Texture.hpp"

class Sprite{
public:
	string name;
	vector<Texture *> textures;
	int current_texture = 0;
	
	Sprite(){};
	
	~Sprite(){
		for (int i = 0 ; i < textures.size(); i++)
		{
			delete textures[i];
			textures[i] = NULL;
		}
	}
	
	inline Texture *getNextTexture(){
		++current_texture;
		return textures[current_texture];
	}
};

class Animator {
public:
	vector<Sprite *> sprites;
	int current_sprite = 0;
	
	Animator(){}
	
	~Animator(){
		for (int i = 0 ; i < sprites.size(); i++)
		{
			delete sprites[i];
			sprites[i] = NULL;
		}
	}
	
	
	inline void setSprite(string name){
		for (int i = 0 ; i < sprites.size(); i++)
		{
			if (sprites[i]->name == name ){
				current_sprite = i;
				return;
			}
		}
		printf("Couldn't find such sprite in the Animator.\n\tname = %s\n", name.c_str());
	}
	inline Texture* getNextTexture() {
		return sprites[current_sprite]->getNextTexture();
	}
	
};

#endif /* Animator_hpp */
