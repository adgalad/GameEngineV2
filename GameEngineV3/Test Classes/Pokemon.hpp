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
	RectangleCollider *rc;
	
	void Start(){
		rc = (RectangleCollider*)getModule("RectangleCollider");
	}
	void AfterRender(){
		Application.renderer()->setRenderColor(Color::red);
		Texture::drawRect(rc->absolute_rect);
		Application.renderer()->setRenderColor(Color::black);
	}
};

void loadPokemon(Game *game);

#endif /* Pokemon_hpp */
