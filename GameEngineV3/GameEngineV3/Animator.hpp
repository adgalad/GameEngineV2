//
//  Animator.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Animator_hpp
#define Animator_hpp

#include "Object.hpp"

class Sprite{
	int current_texture = 0;
public:
	string name;
	vector<Texture *> sheet;

	Sprite(){};
	
	Sprite(string name, string image, int rows, int columns){
		this->name = name;
		SDL_Surface *surface = IMG_Load(image.c_str());
		SDL_Rect rect = {0,0,surface->w/rows, surface->h/columns};
		
		for (int j = 0 ; j < columns ; j ++)
		{
			for (int i = 0 ; i < rows ; i ++)
			{
				rect.x = i * rect.w;
				rect.y = j * rect.h;
				SDL_Surface *sprite_surface = SDL_CreateRGBSurface(surface->flags,
													 rect.w, rect.h,
													 surface->format->BitsPerPixel,
													 surface->format->Rmask,
													 surface->format->Gmask,
													 surface->format->Bmask,
													 surface->format->Amask);
				SDL_BlitSurface(surface, &rect, sprite_surface, 0);
				Texture *texture = new Texture(name+" Tex "+to_string(j*rows+1),
											   sprite_surface);
				sheet.push_back(texture);
				
				/* Save to bmp */
				//				SDL_SaveBMP(sprite_surface,("/Users/carlosspaggiari/ge_images_test/"+name+" Tex "+to_string(j*rows+1)+".png").c_str());
			}
		}
		SDL_FreeSurface(surface);
	}
	
	~Sprite(){
		for (int i = 0 ; i < sheet.size(); i++)
		{
			delete sheet[i];
			sheet[i] = NULL;
		}
	}
	
	inline Texture *getNextTexture(){
		current_texture = (current_texture + 1) % sheet.size();
		
		return sheet[current_texture];
	}
	inline void reset(){
		current_texture = 0;
	}
};


class Animator : public ObjectModule{
	Sprite *current_sprite;
	int current_sprite_id;
	
	
public:
	vector<Sprite *> sprites;
	

	
	Animator(){
		setName("");
	}
	
	~Animator(){
		for (int i = 0 ; i < sprites.size(); i++)
		{
			delete sprites[i];
			sprites[i] = NULL;
		}
	}
	
	
	void Start(){
		if (current_sprite == NULL){
			if (sprites[0] == NULL){
				printf("Error: No sprite in the animator\n");
				return;
			}
			current_sprite = sprites[0];
		}
	}
	
	void Update(){
		object->texture = current_sprite->getNextTexture();
	}
	
	inline void setName(string name){
		ObjectModule::setName("Animator");
	}
	
	inline void setSprite(string name){
		if (current_sprite->name == name) return;
		for (int i = 0 ; i < sprites.size(); i++)
		{
			if (sprites[i]->name == name ){
				current_sprite = sprites[i];
				current_sprite_id = i;
				current_sprite->reset();
				return;
			}
		}
		printf("Couldn't find such sprite in the Animator.\n\tname = %s\n", name.c_str());
	}
	
	void setCurrentSpriteId(int id){
		if (current_sprite_id != id && id >= 0 && id < sprites.size()){
			current_sprite_id = id;
			current_sprite = sprites[id];
			current_sprite->reset();
		}
	}

	
};

#endif /* Animator_hpp */
