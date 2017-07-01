//
//  DrawPrimitives.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/5/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "DrawPrimitives.hpp"


void loadDraw(){
  Application.currentScene = shared_ptr<Scene>(new DrawFigures());
}
