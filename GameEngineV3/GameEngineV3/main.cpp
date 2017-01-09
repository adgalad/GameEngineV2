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


int main(int argc, const char * argv[]) {
  
	GameEngineInit();

	Window   *main_window = new Window("Game Engine V3", 800,600);
	Renderer *renderer    = new Renderer(main_window);
	Game     *game       =  new Game(main_window, renderer);
	
//  loadTest(&game);
//  loadPokemon(&game);
//  LoadSP(game);
//	loadGol(&game);
//  loadGridTest(&game);
//  loadChess(&game);
//	game->setMaxFramesPerSecond(30);
  
//  delete game;
//  
//  Window   *tmain_window = new Window("Game Engine V3", 800,600);
//  Renderer *trenderer    = new Renderer(tmain_window);
//  Game     *tgame        = new Game(tmain_window, trenderer);
  loadGame("/Users/carlosspaggiari/Game.bit", *game);
  
	game->Run();
  saveGame("/Users/carlosspaggiari/Game.bit", *game);
	GameEngineQuit();
  
  
	return 0;
}
