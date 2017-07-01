//
//  Window.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Window.hpp"

using namespace engine;

Window::Window(string name, Uint32 w, Uint32 h, Uint32 flags){
	if (SDL_Init(0) < 0){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("ERROR initializing SDL.\n "+string(SDL_GetError())).c_str(),
                             NULL);
		error("ERROR initializing SDL.\n "+string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	sdl_window = SDL_CreateWindow(name.c_str(),			// window title
								  SDL_WINDOWPOS_UNDEFINED,  // initial x position
								  SDL_WINDOWPOS_UNDEFINED,  // initial y position
								  w,						// width, in pixels
								  h,						// height, in pixels
                  flags					// flags
								  );
  
  
#ifdef ENGINE_OPENGL
  mainContext = SDL_GL_CreateContext(sdl_window);
  if (mainContext == NULL)
  {
    printf( "OpenGL context could not be created!\nSDL Error: %s\n", SDL_GetError() );
    exit(EXIT_FAILURE);
  }

  // Set our OpenGL version.
  // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  
  // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  
  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  
  // This makes our buffer swap syncronized with the monitor's vertical refresh
  SDL_GL_SetSwapInterval(1);
  
  // Init GLEW
  // Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
#ifndef __APPLE__
  glewExperimental = GL_TRUE;
  glewInit();
#endif
#endif
	Debug::Log("Window was initialized succesfully.");
}

Window::~Window(){
	SDL_DestroyWindow(sdl_window);
	sdl_window = NULL;
#ifdef ENGINE_OPENGL
  SDL_GL_DeleteContext(mainContext);
#endif
}


void Window::SwapWindow(){
  SDL_GL_SwapWindow(sdl_window);
}
