//
//  Scene.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Object.hpp"

class Scene {

public:
	string name;
	vector<Object *> objs;
	Texture *background = NULL;
	
	Scene(){};
	Scene (string name, Rect size){
		this->name = name;
		target_texture = new Texture();
		target_texture->createTargetTexture("Target Texture Scene "+name, size);
	}


	inline Vector2D getTargetTextureSize(){
		return target_texture->getSize();
	}
	
	inline void Update(){
		for (int i  = 0 ; i < objs.size(); i ++){
			objs[i]->Update();
		}
	}
	
	inline void Render(){
		target_texture->setAsRenderTarget();
		if (background){
			background->Render(Vector2D(0,0));
		}
		for (int i  = 0 ; i < objs.size(); i ++){
			objs[i]->Render();
		}
		Texture::_renderer->set_renderer_target(NULL);
		target_texture->Render(Vector2D(0,0));
	}
private:
	Texture *target_texture;
};

#endif /* Scene_hpp */
