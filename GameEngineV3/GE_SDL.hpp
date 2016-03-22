//
//  SDL.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef SDL_hpp
#define SDL_hpp


#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <string>
#include <vector>

using namespace std;


void GameEngineInit();

void GameEngineQuit();

#endif /* SDL_hpp */
