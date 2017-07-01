//
//  main.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include <iostream>
#include "GE_SDL.hpp"

#include "Server.hpp"
#include "Pokemon.hpp"
#include "Chess.hpp"
#include "SP_Scene.hpp"
#include "Grid_Test.hpp"
#include "GameOfLife.hpp"
#include "Pacman.hpp"
//#include "NNCircleTest.hpp"
#include "DrawPrimitives.hpp"


int main(int argc, const char * argv[]) {

	GameEngineInit();
	Window   *main_window = new Window("Game Engine V3", 800,600);
	Renderer2D *renderer    = new Renderer2D(main_window);
  Application.SetWindow(main_window, renderer);

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
  Server s;
//  delete game;
//  
//  Window   *tmain_window = new Window("Game Engine V3", 800,600);
//  Renderer2D *trenderer    = new Renderer2D(tmain_window);
//  Game     *tgame        = new Game(tmain_window, trenderer);
//  loadGame("/Users/carlosspaggiari/Game.xml", game);
    thread t (&Server::Start, &s);
	Application.Run();
//  saveGame("/Users/carlosspaggiari/Game.xml", game);
//  loadGame("/Users/carlosspaggiari/Game.xml", game);
  
	GameEngineQuit();
  
//  delete game;
	return 0;
}

