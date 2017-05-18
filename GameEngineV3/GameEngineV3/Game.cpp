//
//  Game.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Game.hpp"



using namespace engine;

Game Application = Game(NULL,NULL);

Game::Game(Window *window, Renderer *renderer){
  
	main_window = window;
	_renderer	  = renderer;
	Texture::renderer = renderer;
	Sound::Init();
	framerate.setFPS(60);
	running = true;
}

Game::~Game(){
	delete main_window;
	delete _renderer;
	Sound::Quit();
}



void Game::setMaxFramesPerSecond(Uint32 n){
	framerate.setFPS(n);
}
void Game::QuitGame(){
	running = false;
	
}
void Game::Run() {
	currentScene->Init();

	framerate.Init();
  Uint32 init = SDL_GetTicks();
  int fps = 0;
	while (running) {
    if (init + 1000 <= SDL_GetTicks()){
      fps = 0;
      init = SDL_GetTicks();
    }
		Time::Update();
		
		/// Clears Render
//		renderer->clearRender();
		
		/// Gets new Input events every loop
		Input::Update();
		
		/// Exit events and global events
		if (Input::KeyDown(KEY_ESCAPE) || Input::Quit()){
			QuitGame();
		}
		else if (Input::KeyPressed(KEY_N)){
			currentScene->Reset();
    }


    // Set color
    if (Input::KeyPressed(KEY_Z)){
      glClearColor ( 0.0, 1.0, 0.5, 1.0 );
    } else if (Input::KeyPressed(KEY_X)){
      glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    }
    
    
    // Clear back buffer
    glClear ( GL_COLOR_BUFFER_BIT );
    
    SDL_GL_SwapWindow(main_window->sdl_window);
    
		/// Updates and Renders the Scene and its objects
//		currentScene->InternalUpdate();
//		currentScene->InternalRender();
//		
//		/// Presents the render to the window
//		_renderer->renderPresent();
    ++fps;
		framerate.Update();
	}

}

void Game::SetWindow(Window *window, Renderer *renderer){
  main_window = window;
  _renderer		= renderer;
  Texture::renderer = renderer;
  Sound::Init();
  framerate.setFPS(60);
  running = true;
  _glContext = SDL_GL_CreateContext(window->sdl_window);
  if (_glContext == NULL)
  {
    printf( "OpenGL context could not be created!\nSDL Error: %s\n", SDL_GetError() );
    exit(EXIT_FAILURE);
  }
  
}

void saveGame(std::string filename, const engine::Game &obj){
  std::ofstream ofs(filename);
  assert(ofs.good());
  
  OUT_ARCHIVE oa(ofs);
  
  
  TAG_OA(oa, obj);
  ofs.close();
}

void loadGame(std::string filename, engine::Game &obj){
  std::ifstream ifs(filename);
  assert(ifs.good());


  IN_ARCHIVE ia(ifs);

  
  TAG_IA(ia,obj);
  ifs.close();
}
