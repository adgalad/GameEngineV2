//
//  main.cpp
//  Client
//
//  Created by Carlos Spaggiari Roa on 6/29/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include <iostream>
#include "Client.hpp"


int main(int argc, const char * argv[]) {
  
  GameEngineInit();
  Window   *main_window = new Window("Game Engine V3", 800,600);
  Renderer2D *renderer    = new Renderer2D(main_window);
  Application.SetWindow(main_window, renderer);
  
  Options.showColliders = true;
  
  Client c;
  c.Start();
  
  GameEngineQuit();
  
    return 0;
}
