//
//  Map.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 9/24/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Grid2D.hpp"


using namespace engine;

Grid2D::Grid2D(string name, Rect gridSize, Vector2D tileSize)
  : Scene(name,Rect(0,0,gridSize.w * tileSize.x, gridSize.h * tileSize.y))
  , _tileSize(tileSize), _gridSize(gridSize)
{
  init();
}


void Grid2D::init(){

  Rect sceneRect = camera.getSceneRect();
  _tileMap = new Texture();
  _tileMap->createTargetTexture(name, sceneRect);
  _tiles.reserve(_gridSize.w);
  _tiles.resize(_gridSize.w);
  for (int i = 0 ; i < _tiles.size(); ++i) {
    _tiles[i].reserve(_gridSize.h);
    _tiles[i].resize(_gridSize.h);
  }
}

EXPORT_IMPLEMENT(Tile);
EXPORT_IMPLEMENT(Grid2D);
