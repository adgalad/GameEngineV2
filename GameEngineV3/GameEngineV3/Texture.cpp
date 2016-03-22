//
//  Texture.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Texture.hpp"

Renderer *Texture::_renderer = NULL;

Texture::Texture() {}

Texture::Texture(string name,
				 Color color,
				 Uint32 w,
				 Uint32 h
				 ){
	sdl_surface = SDL_CreateRGBSurface(0, w, h, 32, RMASK, GMASK, BMASK, AMASK);
	SDL_FillRect(sdl_surface,
				 NULL,
				 SDL_MapRGBA(sdl_surface->format,
							 color.r,
							 color.g,
							 color.b,
							 color.a)
				 );
	
	source_rect = Rect(0, 0, w, h);
	sdl_texture = SDL_CreateTextureFromSurface(_renderer->sdl_renderer, sdl_surface);
	name = name;
}

Texture::Texture(string name, string image,Uint32 rows, Uint32 columns){
	this->name = name;
	loadImage(image,rows,columns);
}

Texture::Texture(string name, SDL_Surface *surface){
	this->name  = name;
	sdl_surface = surface;
	sdl_texture = SDL_CreateTextureFromSurface(_renderer->sdl_renderer, surface);
	source_rect.w = sdl_surface->w;
	source_rect.h = sdl_surface->h;
}

Texture::~Texture(){
	SDL_FreeSurface(sdl_surface);
	SDL_DestroyTexture(sdl_texture);
	sdl_surface = NULL;
	sdl_texture = NULL;
}



Texture *Texture::null(){
	Texture *texture = new Texture;
	texture->loadImage(NULL_TEXTURE, 1, 1);
	return texture;
}

void Texture::loadImage(string file, int rows, int columns){
	SDL_DestroyTexture(sdl_texture);
	SDL_FreeSurface(sdl_surface);
	path_ = file;
	sdl_surface = IMG_Load(path_.c_str());
	
	sdl_texture = SDL_CreateTextureFromSurface(_renderer->sdl_renderer, sdl_surface);
	if (!sdl_texture){
		fprintf(stderr
				,"ERROR creating texture\ntexture: %p\n%s\n"
				,sdl_texture
				,SDL_GetError()
				);
		exit(EXIT_FAILURE);
	}
	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = sdl_surface->w/rows;
	source_rect.h = sdl_surface->h/columns;
}

void Texture::Render(Vector2D position, int angle, bool inverted){
	if (!sdl_texture) {
		printf("ERROR Trying to render a NULL texture\ntexture: %p\n",sdl_texture);
		exit(EXIT_FAILURE);
	}

	Rect destRect;
	destRect.x = (int)position.x;
	destRect.y = (int)position.y;

	destRect.w = this->source_rect.w;
	destRect.h = this->source_rect.h;

	_renderer->RenderCopy(sdl_texture, &this->source_rect, &destRect, angle, inverted);

}

