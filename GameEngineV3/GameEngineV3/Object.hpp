//
//  Object.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Texture.hpp"
#include "Input.hpp"

struct Transform {
	Vector2D position;
	Vector2D scale;
};

class Object {
public:
	static Input *_input;
	
	Transform transform { Vector2D(0,0), Vector2D(0,0)};
	Texture *texture = NULL;
	
	Object() {}
	
	void Render(){
		if (!texture){
			printf("Texture is NULL\n");
		}
		texture->Render(transform.position);
	}
	
	virtual void Update(){
		
	}
};

class O1 : public Object {
public:
	void Update(){
		if (_input->KeyDown(KEY_LEFT_ARROW)){
			transform.position.x--;
		}
		if (_input->KeyDown(KEY_RIGHT_ARROW)){
			transform.position.x++;
		}
		if (_input->KeyDown(KEY_UP_ARROW)){
			transform.position.y--;
		}
		if (_input->KeyDown(KEY_DOWN_ARROW)){
			transform.position.y++;
		}
	}
};


#endif /* Object_hpp */
