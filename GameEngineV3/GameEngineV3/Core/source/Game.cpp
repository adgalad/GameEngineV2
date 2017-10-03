//
//  Game.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Game.hpp"
#include <SDL2/SDL_syswm.h>

using namespace engine;



Game Application = Game(NULL,NULL);

Game::Game(Window *window, Renderer2D *renderer){
  
	main_window = window;
	_renderer	  = renderer;
	Texture::_renderer = renderer;
	Sound::Init();
	framerate.setFPS(60);
  Input = new InputT();
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
    printf("hollla\n\n\n\n");
    if (init + 1000 <= SDL_GetTicks()){
      fps = 0;
      init = SDL_GetTicks();
    }
		Time::Update();
		
		// Clears Render
//		renderer->clearRender();
		
		// Gets new Input events every loop
		Input->Update();
		
		/// Exit events and global events
		if (Input->KeyDown(KEY_ESCAPE) || Input->Quit()){
			QuitGame();
		}
		else if (Input->KeyPressed(KEY_N)){
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

#include "Pokemon.hpp"
void* Cocoa_Game_Window(){
  GameEngineInit();
  Window   *main_window = new Window("SDL", 512, 512);
  Renderer2D *renderer  = new Renderer2D(main_window);
  Application.SetWindow(main_window, renderer);
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_ClearError();
  if (SDL_GetWindowWMInfo(main_window->sdl_window, &info) == SDL_FALSE){
    printf("ERROR: %s\n", SDL_GetError());
  }
  return (void*)info.info.cocoa.window;
}

void Cocoa_Game_Run(){
  Options.showColliders = true;
  
  //  loadTest(&Application);
  loadPokemon(&Application);
  //  LoadSP(&Application);
  //  loadGol();
  //  loadGridTest(&game);
  //  loadChess(&game);
  //  loadPacman();
  //  loadDraw();
  //  Application.currentScene = shared_ptr<Scene>(new NNCircle);
  
  
  
  Application.setMaxFramesPerSecond(60);
  //  delete game;
  //
  //  Window   *tmain_window = new Window("Game Engine V3", 800,600);
  //  Renderer2D *trenderer    = new Renderer2D(tmain_window);
  //  Game     *tgame        = new Game(tmain_window, trenderer);
  //  loadGame("/Users/carlosspaggiari/Game.xml", game);
  //    thread t (&Server::Start, &s);
  Application.Run();
  //  saveSerialize<Game>("/Users/carlosspaggiari/Game.xml", Application);
  //  loadGame("/Users/carlosspaggiari/Game.xml", game);
  
  
  
  GameEngineQuit();
  
  
  //  delete game;
}
