//
//  Renderer.cpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#include "Renderer.hpp"

SDL_Renderer *Renderer::renderer = NULL;
SDL_Window	 *Renderer::mainWindow = NULL;
Size		 Renderer::displaySize;
Size		 Renderer::canvasSize;
Camera		 *Renderer::camera = NULL;


void Renderer::createRenderer(SDL_Window *window){
	if (not window){
		fprintf(stderr,"ERROR creating renderer\nwindow: %p\n",window);
		exit(EXIT_FAILURE);
	}
	
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	displaySize.w = displayMode.w;
	displaySize.h = displayMode.h;
	mainWindow    = window;
	renderer      = SDL_CreateRenderer(window, 0,
									   SDL_RENDERER_ACCELERATED |
									   SDL_RENDERER_TARGETTEXTURE);
	camera = new Camera();
	camera->displaySize = &displaySize;
	if (not renderer){
		fprintf(stderr,
				"ERROR creating renderer\nrenderer: %p\n%s",
				window,
				SDL_GetError()
				);
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);
	printf("Renderer created succesfully\n");
}


void Renderer::renderCopy(SDL_Texture	*texture,
						  Rect			*srcRect,
						  Rect			*destRect,
						  bool			isStatic,
						  double		angle,
						  bool			invert)
{
#ifdef GameEngineDebug
	if (not texture){
		fprintf(stderr,"ERROR rendering texture\ntexture: %p\n",texture);
		exit(EXIT_FAILURE);
	}
#endif
	if (!isStatic){
		destRect->x += camera->position.x;
		destRect->y += camera->position.y;
	}

	SDL_Rect srect = srcRect->toSDLRect();
	SDL_Rect drect = destRect->toSDLRect();
	if (invert){
		SDL_RenderCopyEx(renderer,
						 texture,
						 &srect,
						 &drect,
						 angle,
						 NULL,
						 SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopyEx(renderer,
						 texture,
						 &srect,
						 &drect,
						 angle,
						 NULL,
						 SDL_FLIP_NONE);
	}
}
