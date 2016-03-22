//
//  Renderer.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Renderer.hpp"



void Renderer::RenderCopy(SDL_Texture	*texture,
						  Rect			*srcRect,
						  Rect			*destRect,
						  int			angle,
						  bool			inverted)
{
#ifdef GameEngineDebug
	if (not texture){
		fprintf(stderr,"ERROR rendering texture\ntexture: %p\n",texture);
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

