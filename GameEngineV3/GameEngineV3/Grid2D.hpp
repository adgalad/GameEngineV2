//
//  Grid2D.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 9/24/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Grid2D_hpp
#define Grid2D_hpp

#ifdef __cplusplus

#include "Game.hpp"
#include "Animator.hpp"


#define Tiles vector<vector<Tile*>>


namespace engine {
  class Tile {
    SERIALIZE
    
    template <class Archive>
    void serialize(Archive & ar, const unsigned int version){
      TAG(ar, texture);
      TAG(ar, position);
    }
    
    Texture* texture = NULL;
    
  public:
    Tile(){}
    Vector2 position;
    
    Tile(Texture* t){
      texture = t;
    }
    
    inline void Render(){
      texture->Render(position);
    }
    
  };
  
  
  class Grid2D : public Scene {
    SERIALIZE
    
    template <class Archive>
    void save(Archive & ar, const unsigned int version) const {
      TAG_BASE(ar, Scene);
      TAG(ar, _tileSize);
      TAG(ar, _tiles);
      TAG(ar, _textures);
    }
    
    template <class Archive>
    void load(Archive & ar, const unsigned int version){
      TAG_BASE(ar, Scene);
      TAG(ar, _tileSize);
      TAG(ar, _tiles);
      TAG(ar, _textures);
      init();
    }
    
    SPLIT_SERIALIZATION
    
    void init();
    
    Grid2D(){};
  public:
    Grid2D(string name, Rect size, Vector2 tileSize);
    
    
    
    inline vector<Tile*>* operator [](int i){
      return &_tiles[i];
    }
    
    void Start() {
      Scene::Start();
      
      _tileMap->setAsRenderTarget();
      for (int i = 0 ; i < (int)_tiles.size(); ++i){
        for (int j = 0 ; j < (int)_tiles[i].size(); ++j){
          _tiles[i][j]->Render();
        }
      }
      Application.setSceneAsRenderTarget();
      
    }
    
    virtual void Render() {
      Rect srcRect = camera.getCameraRect();
      
      _tileMap->Render(Vector2(srcRect.x,srcRect.y), Vector2(1,1), &srcRect);
    }
    
    virtual void addTile(Tile *tile, int i, int j){
      _tiles[i][j] = tile;
      tile->position = Vector2(_tileSize.x*i,_tileSize.y*j);
    }
    
    void addTexture(Texture* t){
      _textures.push_back(t);
    }
    
  private:
    Vector2         _tileSize;
    Rect             _gridSize;
    vector<Texture*> _textures;
    Texture*         _tileMap = NULL;
    Tiles            _tiles;
  };
}


EXPORT_KEY(Tile);
EXPORT_ABSTRACT_KEY(Grid2D);


#endif

#endif /* Grid2D_hpp */
