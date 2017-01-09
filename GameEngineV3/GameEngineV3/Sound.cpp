//
//  Sound.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Sound.hpp"

using namespace engine;

Mix_Music *Sound::_current_music = NULL;
int        Sound::_numChannel = 16;