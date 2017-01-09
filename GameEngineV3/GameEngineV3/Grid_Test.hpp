//
//  Grid_Test.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 11/7/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Grid_Test_hpp
#define Grid_Test_hpp

#include "Game.hpp"
#include "Grid2D.hpp"

#define tile "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/master-tileset.png"

using namespace engine;

class Jugador : public Object{

public:
  
  Animator* anim;
  
  Jugador(){}
  
  void Start(){
    anim = (Animator*)getModule("Animator");
    anim->setRenderDelay(-1);
  }
  
  void Update(){
    int n = 5;
    if (Input::KeyDown(KEY_W)){
        move(Vector2D(0,-n));
        anim->setSprite("Jugador_up");
    } else if (Input::KeyDown(KEY_S)){
        move(Vector2D(0,n));
        anim->setSprite("Jugador_down");
    } else if (Input::KeyDown(KEY_A)){
        move(Vector2D(-n,0));
        anim->setSprite("Jugador_left");
    } else if (Input::KeyDown(KEY_D)){
        move(Vector2D(n,0));
        anim->setSprite("Jugador_right");
    }
    
  }

  
};

namespace boost {
  namespace serialization {
template <class Archive>
void serialize(Archive & ar, Jugador & g, const unsigned int version){
  ar & make_nvp(BOOST_PP_STRINGIZE(Object),
                base_object<Object>(g));
}}}

class Mapa : public Grid2D{
  
#define w 100
#define h 100

public:
  
  Mapa() : Grid2D("Scenita", Rect(0, 0, w, h), Vector2D(64,64)) {
    Texture *grama = new Texture("grama", tile);
    addTexture(grama);
    for (int i = 0 ; i < w ; i++) {
      for (int j = 0 ; j < h ; j++){
        addTile(new Tile(grama), i, j);
      }
    }
  }
};

namespace boost {
  namespace serialization {
template <class Archive>
void serialize(Archive & ar, Mapa & g, const unsigned int version){
  ar & make_nvp(BOOST_PP_STRINGIZE(Grid2D),
                base_object<Grid2D>(g));
}}}

EXPORT_KEY(Jugador);
EXPORT_KEY(Mapa);

void loadGridTest(Game *game);
#endif /* Grid_Test_hpp */
