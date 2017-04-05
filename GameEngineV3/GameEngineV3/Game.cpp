//
//  Game.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Game.hpp"



using namespace engine;

Game * const Game::Application = new Game(NULL,NULL);

Game::Game(Window *window, Renderer *renderer){
  
	this->main_window = window;
	this->renderer		  = renderer;
	Texture::renderer = renderer;
	Sound::Init();
	framerate.setFPS(60);
	running = true;
}

Game::~Game(){
	delete main_window;
	delete renderer;
	Sound::Quit();
}



void Game::setMaxFramesPerSecond(Uint32 n){
	framerate.setFPS(n);
}
void Game::QuitGame(){
	running = false;
	
}
void Game::Run() {
  printf("-> %p\n",this->currentScene.get());
	currentScene->Init();

	framerate.Init();
  Uint32 init = SDL_GetTicks();
  int fps = 0;
  printf("-> %p\n",this->currentScene.get());
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
			currentScene->reset();
    }

		/// Updates and Renders the Scene and its objects
		currentScene->InternalUpdate();
		currentScene->InternalRender();
		
		/// Presents the render to the window
		renderer->renderPresent();
    ++fps;
		framerate.Update();
	}

}

void Game::SetWindow(Window *window, Renderer *renderer){
  this->main_window = window;
  this->renderer		  = renderer;
  Texture::renderer = renderer;
  Sound::Init();
  framerate.setFPS(60);
  running = true;
}

void saveGame(std::string filename, const engine::Game &obj){
  std::ofstream ofs(filename);
  assert(ofs.good());
  
  boost::archive::xml_oarchive oa(ofs);
  
  
  TAG_OA(oa, obj);
  ofs.close();
}

void loadGame(std::string filename, engine::Game &obj){
  std::ifstream ifs(filename);
  assert(ifs.good());


    boost::archive::xml_iarchive ia(ifs);

  
  TAG_IA(ia,obj);
  ifs.close();
}
