//
//  main.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include <iostream>
#include "GE_SDL.hpp"
#include "Game.hpp"
#include "Pokemon.hpp"
#include "Chess.hpp"
#include "SP_Scene.hpp"
#include "Grid_Test.hpp"
#include "GameOfLife.hpp"
#include "Pacman.hpp"

int main(int argc, const char * argv[]) {
  
  
	GameEngineInit();

	Window   *main_window = new Window("Game Engine V3", 800,600);
	Renderer *renderer    = new Renderer(main_window);
  Game::Application->SetWindow(main_window, renderer);

//  loadTest(&Application);
//  loadPokemon(&game);
//  LoadSP(&game);
//  loadGol();
//  loadGridTest(&game);
//  loadChess(&game);
  loadPacman();
  
	Game::Application->setMaxFramesPerSecond(40);
  
//  delete game;
//  
//  Window   *tmain_window = new Window("Game Engine V3", 800,600);
//  Renderer *trenderer    = new Renderer(tmain_window);
//  Game     *tgame        = new Game(tmain_window, trenderer);
//  loadGame("/Users/carlosspaggiari/Game.xml", game);
  
	Game::Application->Run();
//  saveGame("/Users/carlosspaggiari/Game.xml", game);
//  loadGame("/Users/carlosspaggiari/Game.xml", game);
	GameEngineQuit();
  
//  delete game;
	return 0;
}
