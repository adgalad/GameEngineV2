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
#include "GameEngineUtilities.hpp"
#include "Camera.hpp"


class Renderer{
	friend class Game;
private:
	static SDL_Renderer *renderer;

	static SDL_Window   *mainWindow;
	static Size			displaySize;

public:
	static Size			canvasSize;
	static Camera		*camera;

	
	virtual ~Renderer(){
		
	}
	
	/**
	 Get the size of the MainWidnow.
	 */
	
	static inline Size getDisplaySize(){
		return displaySize;
	}

	/**
	 Create a texture using a premade SDL_Surface.
	 */
	static inline SDL_Texture *createTextureFromSurface(SDL_Surface *surface){
		if (not surface){
			fprintf(stderr,"ERROR creating texture\nsurface: %p\n%s\n",surface,SDL_GetError());
			exit(EXIT_FAILURE);
		}
		return SDL_CreateTextureFromSurface(renderer, surface);
	}
	
	/**
	 Create an empty texture.
	 */
	static inline SDL_Texture *createTexture(Uint32 format,
											 int access,
											 int w,
											 int h){
		return SDL_CreateTexture(renderer, format, access, w, h);
	}
	
	/**
	 Set a texture as the renderering target. If target is NULL, the MainWindow is 
	 set as target.
	 */
	static inline void setRendererTarget(SDL_Texture *target){
		SDL_SetRenderTarget(renderer, target);
	}
	
	static inline bool hasTarget(){
		return SDL_GetRenderTarget(renderer) != NULL;
	}
	
	/**
	 Use this function to clear the current rendering target with the drawing color.
	 */
	static inline void clearRender(){
		SDL_RenderClear(renderer);
	}
	
	/**
	 Draw a set of lines on the current rendering target.
	 */
	static inline void drawLines(SDL_Point *points, int n){
		SDL_RenderDrawLines(renderer, points, n);
	}
	
	/**
	 Draw a point on the current rendering target.
	 */
	static inline void drawPoint(SDL_Point point){
		SDL_RenderDrawPoint(renderer, point.x, point.y);
	}
	
	/**
	 Use this function to set the color used for drawing operations (Rect, Line, Point and Clear).
	 */
	static inline void setRenderColor(SDL_Color color){
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}
	/**
	 Draw a rectangle on the current rendering target.
	 */
	static inline void drawRect(Rect rect){
		SDL_Rect r = rect.toSDLRect();
		SDL_RenderDrawRect(renderer, &r);
	}
	
	/**
	 Use this function to update the screen with any rendering performed since the previous call.
	 */
	static inline void renderPresent(){
		SDL_GetWindowSize(mainWindow, &displaySize.w, &displaySize.h);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		
	}
	
	static void setCanvasSize(Size canvas){
		canvasSize = canvas;
		camera->canvas = &canvasSize;
		
	}
	
	/** 
	 Initialize the Renderer.
	 */
	static void createRenderer(SDL_Window *window);
	

	/**
	 Use this function to copy a portion of the texture to the current rendering target.
	 */
	static void renderCopy(SDL_Texture	*texture,
						   Rect		*srcRect,
						   Rect		*destRect,
						   double		angle,
						   bool			invert);
};
#endif /* Renderer_hpp */
