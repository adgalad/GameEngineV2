//
//  Renderer2D.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Renderer2D_hpp
#define Renderer2D_hpp


#ifdef __cplusplus
#include "Window.hpp"
#include "Color.hpp"
#include "Geometry.hpp"

namespace engine {

  
  class Renderer2D {
public:
  SDL_Renderer *sdl_renderer; /// SDL Renderer2D.
  Window *window;             /// Window where all textures will be rendered.
	
  /**
   *  Default Constructor
   */
	Renderer2D();
	
  /**
   *  Build a Renderer2D bound to the given Window.
   *
   *  @param window Pointer to the Window where all textures will be rendered.
   */
	Renderer2D(Window *window);
	
  /**
   *  Default Destructor.
   */
	virtual ~Renderer2D();
	
	
  /**
   *  Set a texture as the Render's target.
   *
   *  @param target New Render's Target If target is NULL, 
   *                the Window is setted as target.
   */
	inline void setRendererTarget(SDL_Texture *target){
		SDL_SetRenderTarget(sdl_renderer, target);
	}
	
  /**
   *  Asks the render if it's rendering on a target Texture or directly in the
   *  Window.
   *
   *  @return Returns True if the Render has a target
   */
	inline bool hasTarget(){
		return SDL_GetRenderTarget(sdl_renderer) != NULL;
    
	}
  
  inline SDL_Texture *getTargetTexture(){ return SDL_GetRenderTarget(sdl_renderer); }
	
  /**
   *  Use this function to set the color used by drawing
   *  operations (Rect, Line, Point and Clear). If you need to know
   *  the current Render color use getDrawColor()
   *
   *  @param color New Render's Color
   */
	inline void setDrawColor(Color color){
		SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
	}
	/**
	 *  Use this function to update the screen with any rendering
	 *  performed since the last call. After presenting the render,
	 *  clearRender() should be called to clear the Render's buffer
	 */
	inline void renderPresent(){
    // Save the current target and set the main window as target
		SDL_Texture *t = SDL_GetRenderTarget(sdl_renderer);
		SDL_SetRenderTarget(sdl_renderer, NULL);

    // Clear the main window
    
		SDL_RenderPresent(sdl_renderer);
		
		SDL_SetRenderTarget(sdl_renderer, t);
//    clearRender();
	}
	
	/**
	 *  Use this function to clear the current rendering target with the
	 *  drawing color. It should be called after every renderPresent()
	 */
	inline void clearRender(){
		SDL_RenderClear(sdl_renderer);
	}
  
  inline void clearTarget(){
    if (SDL_GetRenderTarget(sdl_renderer) != NULL)
      SDL_RenderClear(sdl_renderer);
  }
	
	/**
	 *  Gets the Color in which the renderer draw. Colors can be setted with
	 *  setDrawColor()
	 */
	inline Color getDrawColor(){
		Color color;
		SDL_GetRenderDrawColor(sdl_renderer, &color.r, &color.g, &color.b, &color.a);
		return color;
	}
  
  /**
   *  Blits the a SDL texture into the Render's target. 
   *  Should be not used manually. Use Texture's Render() instead.
   *
   *  @param texture SDL_Texture that will be rendered.
   *  @param srcRect Where the Texture will be putted in the Render.
   *                 If NULL, puts the texture at (0,0)
   *  @param destRect The rectangle of the texture that will be shown.
   *                 If NULL, uses the whole texture.
   *  @param angle The angle of the texture in degrees
   *  @param inverted flip the texture horizontally if true.
   
   */
  void RenderCopy(SDL_Texture *texture, Rect *srcRect, Rect *destRect,
                  int angle = 0, bool inverted = false);
};
	
}

#endif
#endif /* Renderer2D_hpp */
