//
//  Pokemon.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/26/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Pokemon_hpp
#define Pokemon_hpp

#include "O1.hpp"
#include "Game.hpp"


void loadTest(Game *game);



class Bush : public Object{
  SERIALIZE
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG_BASE(ar, Object);
    rc = (RectangleCollider*)getModule("RectangleCollider");
  }
  
	RectangleCollider *rc;
	
	void Start(){
		rc = (RectangleCollider*)getModule("RectangleCollider");
	}
	void AfterRender(){
//		Application.renderer()->setDrawColor(Color::red);
//		Texture::drawRect(rc->absolute_rect);
//		Application.renderer()->setDrawColor(Color::black);
	}
};

void loadPokemon(Game *game);

#endif /* Pokemon_hpp */
