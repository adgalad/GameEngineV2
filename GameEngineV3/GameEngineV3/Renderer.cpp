//
//  Renderer.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Renderer.hpp"

using namespace engine;

Renderer::Renderer(){}

Renderer::Renderer(Window *window){
	if (not window){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             "ERROR: creating renderer. NULL window",
                             NULL);
		error("ERROR: creating renderer. NULL window");
		exit(EXIT_FAILURE);
	}
	
	this->window    = window;
	sdl_renderer    = SDL_CreateRenderer(window->sdl_window, 0,
										 SDL_RENDERER_ACCELERATED |
										 SDL_RENDERER_TARGETTEXTURE);
	if (not sdl_renderer){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR: Could not create renderer\n "+string(SDL_GetError())).c_str(),
                              NULL);
		error("ERROR: Could not create renderer\n "+string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(sdl_renderer);
	Debug::Log("Renderer created succesfully");
}

Renderer::~Renderer(){
	SDL_DestroyRenderer(sdl_renderer);
	sdl_renderer = NULL;
	window = NULL;
}

void Renderer::RenderCopy(SDL_Texture	*texture,
						  Rect			*srcRect,
						  Rect			*destRect,
						  int			  angle,
						  bool			inverted)
{
#ifdef GameEngineDebug
	if (not texture){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             "ERROR: Trying to render a NULL texture",
                             NULL);
		error("ERROR: Trying to render a NULL texture");
		exit(EXIT_FAILURE);
	}
#endif
	SDL_Rect srect = srcRect->to_sdl_rect();
	SDL_Rect drect = destRect->to_sdl_rect();
	
	SDL_RenderCopyEx(sdl_renderer,
					 texture,
					 &srect,
					 &drect,
					 0,
					 NULL,
					 SDL_FLIP_NONE);
	
}

