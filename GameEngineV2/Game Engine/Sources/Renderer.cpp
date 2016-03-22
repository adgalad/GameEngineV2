//
//  Renderer.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Renderer.hpp"


void Renderer::SetWindow(Window *window){
	if (not window){
		fprintf(stderr,"ERROR creating renderer\nwindow: %p\n",window);
		exit(EXIT_FAILURE);
	}
	
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	display_size_.x = display_mode.w;
	display_size_.y = display_mode.h;
	main_window_    = window;
	renderer_       = SDL_CreateRenderer(window->window, 0,
									   SDL_RENDERER_ACCELERATED |
									   SDL_RENDERER_TARGETTEXTURE);
	if (not renderer_){
		fprintf(stderr,
				"ERROR creating renderer\nrenderer: %p\n%s",
				window,
				SDL_GetError()
				);
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer_);
	printf("Renderer created succesfully\n");
}


void Renderer::RenderCopy(SDL_Texture	*texture,
						  Rect			*srcRect,
						  Rect			*destRect)
{
#ifdef GameEngineDebug
	if (not texture){
		fprintf(stderr,"ERROR rendering texture\ntexture: %p\n",texture);
		exit(EXIT_FAILURE);
	}
#endif
	SDL_Rect srect = srcRect->toSDLRect();
	SDL_Rect drect = destRect->toSDLRect();

		SDL_RenderCopyEx(renderer_,
						 texture,
						 &srect,
						 &drect,
						 0,
						 NULL,
						 SDL_FLIP_NONE);

}
