//
//  Texture.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/19/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Texture.hpp"
int Texture::__id = 0;

Texture::Texture() {
	_id = __id++;
	name_ = "texture "+std::to_string( _id );
	srcRect_ = Rect(0, 0, 0, 0);

}

Texture::Texture(Color color,
				 unsigned int w,
				 unsigned int h,
				 string name
				){
	_id = __id++;
	surface_ = SDL_CreateRGBSurface(0, w, h, 32, RMASK, GMASK, BMASK, AMASK);
	SDL_FillRect(surface_,
				 NULL,
				 SDL_MapRGBA(surface_->format,
							 color.r,
							 color.g,
							 color.b,
							 color.a)
				 );
	
	srcRect_ = Rect(0, 0, w, h);
//	texture_ = renderer_->create_texture_from_surface(surface_);
	name_ = name;
}

Texture::Texture(string image, string name){
	_id = __id++;
	if (name == "") this->name_ = "texture "+to_string(_id);
	else this->name_ = name;
	loadImage(image);
}

Texture::~Texture(){
	ListObject::~ListObject();
	SDL_FreeSurface(surface_);
	SDL_DestroyTexture(texture_);
	surface_ = NULL;
	texture_ = NULL;
}



Texture *Texture::null(){
	Texture *texture = new Texture;
	texture->loadImage(NULL_TEXTURE, 1, 1);
	return texture;
}

void Texture::loadImage(string file, int rows, int columns){
	SDL_DestroyTexture(texture_);
	SDL_FreeSurface(surface_);
	path_ = file;
	surface_ = IMG_Load(path_.c_str());

//	texture_ = renderer_->create_texture_from_surface(surface_);
	if (!texture_){
		fprintf(stderr
				,"ERROR creating texture\ntexture: %p\nid: %d\n%s\n"
				,texture_
				,_id
				,SDL_GetError()
				);
		exit(EXIT_FAILURE);
	}
	srcRect_.x = 0;
	srcRect_.y = 0;
	srcRect_.w = surface_->w;
	srcRect_.h = surface_->h;
}

//void Texture::renderTexture(Vector2D position,
//							Rect *srcRect,
//							bool isStatic,
//							int  angle,
//							bool inverted){
//	if (!texture_) {
//		printf("ERROR Trying to render a NULL texture\ntexture: %p\nid %d\n",texture_,_id);
//		exit(EXIT_FAILURE);
//	}
//
//	Rect destRect;
//	destRect.x = (int)position.x;
//	destRect.y = (int)position.y;
//
//	if (srcRect != NULL){
//		destRect.w = srcRect->w;
//		destRect.h = srcRect->h;
//
//		renderer_->RenderCopy(texture_, srcRect, &destRect, angle, inverted);
//	}
//	else {
//		destRect.w = this->srcRect_.w;
//		destRect.h = this->srcRect_.h;
//
//		renderer_->RenderCopy(texture_, &this->srcRect_, &destRect, angle, inverted);
//	}
//}

