//
//  Texture.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Texture.hpp"

using namespace engine;

Renderer2D *Texture::_renderer = NULL;

Texture::Texture() {

}

Texture::Texture(string name, Color color, Uint32 w, Uint32 h):
  name(name), type(SOLID_COLOR), source_rect(Rect(0, 0, w, h))
{
  createColorTexture();
}

Texture::Texture(string name, string image,Uint32 rows, Uint32 columns):
  name(name), path(image), type(STANDARD)
{
	loadImage(image,rows,columns);
}

Texture::Texture(string name, string path, SDL_Surface *surface) :
    name(name), path(path), type(SPRITE)
{
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

void Texture::createColorTexture(){
  sdl_surface = SDL_CreateRGBSurface(0, source_rect.w, source_rect.h, 32,
                                     RMASK, GMASK, BMASK, AMASK);
  SDL_FillRect(sdl_surface,
               NULL,
               SDL_MapRGBA(sdl_surface->format,
                           color.r,
                           color.g,
                           color.b,
                           color.a)
               );
  sdl_texture = SDL_CreateTextureFromSurface(_renderer->sdl_renderer, sdl_surface);
}

void Texture::drawCircle(Circle circle){
	float x1, y1, x2, y2;
	float PI = 3.1416;
	int n = PI*circle.radius.x*circle.radius.y/10;
	
  float theta = 2*PI/n;
	
  x1 = circle.radius.x*cosf(theta) + circle.center.x;
	y1 = circle.radius.y*sinf(theta) + circle.center.y;
	
  for (int i = 1 ; i <= n+1; ++i){
		x2 = circle.radius.x*cosf(theta*(i)) + circle.center.x;
		y2 = circle.radius.y*sinf(theta*(i)) + circle.center.y;
		SDL_RenderDrawLine(_renderer->sdl_renderer, x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
	}
	
}

void Texture::drawFilledCircle(Circle circle, Color outline, Color filler){
  Color oldColor = _renderer->getDrawColor();
  
  _renderer->setDrawColor(filler);
  for (int x = circle.center.x - circle.radius.x ; x <= circle.center.x ; x++)
  {
    for (int y = circle.center.y - circle.radius.y ; y <= circle.center.y; y++)
    {
      // we don't have to take the square root, it's slow
      if (pow(x - circle.center.x,2) + pow(y - circle.center.y,2) <= circle.radius.x * circle.radius.y)
      {
        int xSym = circle.center.x - (x - circle.center.x);
        int ySym = circle.center.y - (y - circle.center.y);
        SDL_RenderDrawPoint(_renderer->sdl_renderer, x, y);
        SDL_RenderDrawPoint(_renderer->sdl_renderer, x, ySym);
        SDL_RenderDrawPoint(_renderer->sdl_renderer, xSym, y);
        SDL_RenderDrawPoint(_renderer->sdl_renderer, xSym, ySym);
      }
    }
  }
  if (not (outline == filler)) {
    _renderer->setDrawColor(outline);
    drawCircle(circle);
  }
  
  _renderer->setDrawColor(oldColor);
  
}

void Texture::loadImage(string file, int rows, int columns){
	SDL_DestroyTexture(sdl_texture);
	SDL_FreeSurface(sdl_surface);
	path = file;
	sdl_surface = IMG_Load(path.c_str());
	if (!sdl_surface){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR: Could not create surface\n "+string(SDL_GetError())).c_str(),
                             NULL);
		error("ERROR: Could not create surface\n "+string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	sdl_texture = SDL_CreateTextureFromSurface(_renderer->sdl_renderer, sdl_surface);
	if (!sdl_texture){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR: Could not create texture\n " + string(SDL_GetError())).c_str(),
                             NULL);
		error("ERROR: Could not create texture\n " + string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = sdl_surface->w/rows;
	source_rect.h = sdl_surface->h/columns;
}

void Texture::Render(Vector2 position, Vector2 scale, Rect *srcRect, int angle, bool inverted){
	if (!sdl_texture) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             "ERROR: Trying to render a NULL texture\ntexture",
                             NULL);
		error("ERROR: Trying to render a NULL texture\ntexture");
		exit(EXIT_FAILURE);
	}
	Rect destRect;
	destRect.x = (int)position.x;
	destRect.y = (int)position.y;
	
  
	if (srcRect){
		destRect.w = srcRect->w* scale.x;
		destRect.h = srcRect->h* scale.y;
		_renderer->RenderCopy(sdl_texture, srcRect, &destRect, angle, inverted);
	}
	else {
		destRect.w = this->source_rect.w* scale.x;
		destRect.h = this->source_rect.h* scale.y;
		_renderer->RenderCopy(sdl_texture, &this->source_rect, &destRect, angle, inverted);
	}


}


EXPORT_IMPLEMENT(Texture)
