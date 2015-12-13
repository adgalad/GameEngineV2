//
//  Texture.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/19/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Texture.hpp"
int Texture::__id = 0;
List Texture::textures;

Texture::Texture() {
	_id = __id++;
	name = "texture "+std::to_string( _id );
	textures.pushBack(this);
	srcRect = Rect(0, 0, 0, 0);

}

Texture::~Texture(){
	ListObject::~ListObject();
#ifdef GameEngineDebug
	printf("Deleting object: %p id: %d name: '%s'\n",this,id(),name.c_str());
#endif
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = NULL;
	texture = NULL;
}

Texture *Texture::createRGBTexture(SDL_Color color,
								   unsigned int w,
								   unsigned int h
								 ){
	Texture *RGBTexture = new Texture();
	RGBTexture->surface = SDL_CreateRGBSurface(0, w, h, 32, RMASK, GMASK, BMASK, AMASK);
	SDL_FillRect(RGBTexture->surface,
				 NULL,
				 SDL_MapRGBA(RGBTexture->surface->format,
							color.r,
							color.g,
							color.b,
							color.a)
				 );

	RGBTexture->srcRect = Rect(0, 0, w, h);
	RGBTexture->texture = Renderer::createTextureFromSurface(RGBTexture->surface);
	
	return RGBTexture;
}

Texture *Texture::null(){
	Texture *texture = new Texture;
	texture->loadImage(NULL_TEXTURE, 1, 1);
	return texture;
}

void Texture::loadImage(string file, int rows, int columns){
	path = file;
	surface = IMG_Load(path.c_str());

	texture = Renderer::createTextureFromSurface(surface);
	if (!texture){
		fprintf(stderr
				,"ERROR creating texture\ntexture: %p\nid: %d\n%s\n"
				,texture
				,_id
				,SDL_GetError()
				);
		exit(EXIT_FAILURE);
	}
	r = rows;
	c = columns;
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = surface->w / columns;
	srcRect.h = surface->h / rows;
}

void Texture::renderTexture(Tuple<float> position,
							Tuple<int> frame,
							int angle,
							bool inverted,
							Rect *rect){
	if (!texture) {
		printf("ERROR Trying to render a NULL texture\ntexture: %p\nid %d\n",texture,_id);
		exit(EXIT_FAILURE);
	}
	srcRect.x   = frame.x*srcRect.w;
	srcRect.y   = frame.y*srcRect.h;
	Rect destRect;
	
	if (rect) {
		destRect.w = rect->w;
		destRect.h = rect->h;
		destRect.x = (int)position.x;
		destRect.y = (int)position.y;
		Renderer::renderCopy(texture, rect, &destRect, angle, inverted);
	}
	else {
		destRect.w = srcRect.w;
		destRect.h = srcRect.h;
		destRect.x = (int)position.x;
		destRect.y = (int)position.y;
		Renderer::renderCopy(texture, &srcRect, &destRect, angle, inverted);
	}




}

