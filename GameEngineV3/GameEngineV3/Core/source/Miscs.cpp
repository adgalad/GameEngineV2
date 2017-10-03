//
//  Miscs.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/18/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "GE_SDL.hpp"


using namespace engine;

string readFile(string file){
  // Open file
  ifstream t(file);
  
  // Read file into buffer
  stringstream buffer;
  buffer << t.rdbuf();
  
  return buffer.str();
}
