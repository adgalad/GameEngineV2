//
//  Renderer.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Window.hpp"
#include "Color.hpp"
#include "Geometry.hpp"

class Renderer {
public:
	SDL_Renderer *sdl_renderer;
	Window *window;
	
	Renderer(){}
	Renderer(Window *window){
		if (not window){
			fprintf(stderr,"ERROR creating renderer. No window\nwindow: %p\n",window);
			exit(EXIT_FAILURE);
		}
		
		this->window    = window;
		sdl_renderer    = SDL_CreateRenderer(window->sdl_window, 0,
									   SDL_RENDERER_ACCELERATED |
									   SDL_RENDERER_TARGETTEXTURE);
		if (not sdl_renderer){
			fprintf(stderr,
					"ERROR creating renderer\nrenderer: %p\n%s",
					sdl_renderer,
					SDL_GetError()
					);
			exit(EXIT_FAILURE);
		}
		SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderClear(sdl_renderer);
		printf("Renderer created succesfully\n");
	}
	
	virtual ~Renderer(){
		SDL_DestroyRenderer(sdl_renderer);
		sdl_renderer = NULL;
		window = NULL;
	}
	
	/**
	 Get the size of the MainWidnow.
	 */
	
	inline Vector2D get_window_size(){
		return window->get_size();
	}
	
	
	/**
	 Set a texture as the renderering target. If target is NULL, the Window is
	 set as target.
	 */
	inline void set_renderer_target(SDL_Texture *target){
		SDL_SetRenderTarget(sdl_renderer, target);
	}
	
	inline bool has_target(){
		return SDL_GetRenderTarget(sdl_renderer) != NULL;
	}
	
	/**
	 Use this function to clear the current rendering target with the drawing color.
	 */
	inline void clear_render(){
		SDL_RenderClear(sdl_renderer);
	}
	
	/**
	 Draw a set of lines on the current rendering target.
	 */
	inline void draw_lines(SDL_Point *points, int n){
		SDL_RenderDrawLines(sdl_renderer, points, n);
	}
	
	/**
	 Draw a point on the current rendering target.
	 */
	inline void draw_point(SDL_Point point){
		SDL_RenderDrawPoint(sdl_renderer, point.x, point.y);
	}
	
	/**
	 Use this function to set the color used for drawing operations (Rect, Line, Point and Clear).
	 */
	inline void set_render_color(Color color){
		SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
	}
	/**
	 Draw a rectangle on the current rendering target.
	 */
	inline void draw_rect(Rect rect){
		SDL_Rect r = rect.to_sdl_rect();
		SDL_RenderDrawRect(sdl_renderer, &r);
	}
	
	/**
	 Use this function to update the screen with any rendering performed since the previous call.
	 */
	inline void render_present(){
		SDL_RenderPresent(sdl_renderer);
		SDL_RenderClear(sdl_renderer);
	}
	
	void RenderCopy(SDL_Texture	*texture,
					Rect		*srcRect,
					Rect		*destRect,
					int			angle = 0,
					bool		inverted = false);
};

#endif /* Renderer_hpp */
