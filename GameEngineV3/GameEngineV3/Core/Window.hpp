//
//  Window.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#ifdef __cplusplus
#include "Vector.hpp"

namespace engine {
	
class Window {
public:
	SDL_Window *sdl_window;
  
	Window(string name, Uint32 w, Uint32 h, Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	
  Window(const void *data);
  
	~Window();

#ifdef ENGINE_OPENGL
  SDL_GLContext mainContext;
#endif
  
	Vector2 getSize(){
		int x,y;
		SDL_GetWindowSize(sdl_window, &x, &y);
		return Vector2(x,y);
	}
  
//  void bindAsRenderTarget(){
//    switch (__graphic_mode){
//      case OPENGL:{
//        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//        Vector2 s = getSize();
//        glViewport(0, 0, s.x, s.y);
//      }
//      default:
//        error("Invalid Graphic Mode.");
//        exit(EXIT_FAILURE);
//    }
//  }
//  

  void SwapWindow();
	
};
}
#endif

#endif /* Window_hpp */
