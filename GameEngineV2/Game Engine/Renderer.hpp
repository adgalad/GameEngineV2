//
//  Renderer.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <cstdio>
#include "Utilities.hpp"
#include "Window.hpp"


class Game;
class Renderer{
	friend Game;
private:

	SDL_Renderer *renderer_   = NULL;
	Window		*main_window_ = NULL;
	Vector2D		 display_size_;


	
public:

	Renderer(Window *window){
		SetWindow(window);
	}
	
	virtual ~Renderer(){
		SDL_DestroyRenderer(renderer_);
		renderer_ = NULL;
		main_window_ = NULL;
	}
	
	/**
	 Get the size of the MainWidnow.
	 */
	
	inline Vector2D get_window_size(){
		return main_window_->get_window_size();
	}

	/**
	 Create a texture using a premade SDL_Surface.
	 */
	inline SDL_Texture *create_texture_from_surface(SDL_Surface *surface){
		if (not surface){
			fprintf(stderr,"ERROR creating texture\nsurface: %p\n%s\n",surface,SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (not renderer_) printf("hola\n");
		return SDL_CreateTextureFromSurface(renderer_, surface);
	}
	
	/**
	 Create an empty texture.
	 */
	inline SDL_Texture *create_texture(Uint32 format,
											 int access,
											 int w,
											 int h){
		return SDL_CreateTexture(renderer_, format, access, w, h);
	}
	
	/**
	 Set a texture as the renderering target. If target is NULL, the Window is 
	 set as target.
	 */
	inline void set_renderer_target(SDL_Texture *target){
		SDL_SetRenderTarget(renderer_, target);
	}
	
	inline bool has_target(){
		return SDL_GetRenderTarget(renderer_) != NULL;
	}
	
	/**
	 Use this function to clear the current rendering target with the drawing color.
	 */
	inline void clear_render(){
		SDL_RenderClear(renderer_);
	}
	
	/**
	 Draw a set of lines on the current rendering target.
	 */
	inline void draw_lines(SDL_Point *points, int n){
		SDL_RenderDrawLines(renderer_, points, n);
	}
	
	/**
	 Draw a point on the current rendering target.
	 */
	inline void draw_point(SDL_Point point){
		SDL_RenderDrawPoint(renderer_, point.x, point.y);
	}
	
	/**
	 Use this function to set the color used for drawing operations (Rect, Line, Point and Clear).
	 */
	inline void set_render_color(Color color){
		SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
	}
	/**
	 Draw a rectangle on the current rendering target.
	 */
	inline void draw_rect(Rect rect){
		SDL_Rect r = rect.toSDLRect();
		SDL_RenderDrawRect(renderer_, &r);
	}
	
	/**
	 Use this function to update the screen with any rendering performed since the previous call.
	 */
	inline void render_present(){
		display_size_ =  main_window_->get_window_size();
		SDL_RenderPresent(renderer_);
		SDL_RenderClear(renderer_);
	}
	

	
	/** 
	 Initialize the Renderer.
	 */
	void SetWindow(Window *window);
	

	/**
	 Use this function to copy a portion of the texture to the current rendering target.
	 */
	void RenderCopy(SDL_Texture	*texture,
						   Rect		*srcRect,
						   Rect		*destRect,
						   double	angle,
						   bool		invert);
};


#endif /* Renderer_hpp */
