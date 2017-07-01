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

Game::Game(Window *window, Renderer2D *renderer){
  
	main_window = window;
	_renderer	  = renderer;
	Texture::_renderer = renderer;
	Sound::Init();
	framerate.setFPS(60);
	running = true;
}

Game::~Game(){
	delete main_window;
	delete _renderer;
//  if (server) delete server;
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
		
		// Clears Render
//		renderer->clearRender();
		
		// Gets new Input events every loop
		Input::Update();
		
		/// Exit events and global events
		if (Input::KeyDown(KEY_ESCAPE) || Input::Quit()){
			QuitGame();
		}
		else if (Input::KeyPressed(KEY_N)){
			currentScene->Reset();
    }
    
		// Updates and Renders the Scene and its objects
    
		currentScene->InternalUpdate();
    
		currentScene->InternalRender();
		
    // Presents the render to the window
		_renderer->renderPresent();
    ++fps;
		framerate.Update();

	}

}

void Game::SetWindow(Window *window, Renderer2D *renderer){
  main_window = window;
  _renderer		= renderer;
  Texture::_renderer = renderer;
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


template <class T> void saveSerialize(std::string filename, const T &obj){
  std::ofstream ofs(filename);
  assert(ofs.good());
  
  OUT_ARCHIVE oa(ofs);
  
  
  TAG_OA(oa, obj);
  ofs.close();
}

template <class T> void loadSerialize(std::string filename, T &obj){
  std::ifstream ifs(filename);
  assert(ifs.good());


  IN_ARCHIVE ia(ifs);

  
  TAG_IA(ia,obj);
  ifs.close();
}

template void saveSerialize<Scene>(string file, const Scene & obj);
template void loadSerialize<Scene>(string file, Scene &obj);
