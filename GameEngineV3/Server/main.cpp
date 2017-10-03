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
#include "NetworkInput.hpp"


int main(int argc, const char * argv[]) {
  
  GameEngineInit();
  Window   *main_window = new Window("Game Engine V3", 800,600);
  Renderer2D *renderer    = new Renderer2D(main_window);
  Application.SetWindow(main_window, renderer);
  
  Options.showColliders = true;

  loadPokemon(&Application);
  
  Application.setMaxFramesPerSecond(60);
  Server s;

  thread t (&Server::Start, &s);
  Input = new NetworkInput();
  Application.Run();

  
  s.Stop();
  t.join();

  if (true) ;
  else if (true) ;
  else if (true) ;
  else printf("hola");
  

  GameEngineQuit();
  
  //  delete game;
  return 0;
}

