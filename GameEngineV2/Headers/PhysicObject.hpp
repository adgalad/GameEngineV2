//
//  PhysicObject.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/24/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef PhysicObject_hpp
#define PhysicObject_hpp

#include "TextureRenderer.hpp"

class PhysicObject : public TextureRenderer{
	
protected:
	Tuple<int> tick;
	Tuple<float> velocity;
	Tuple<float> acceleration;

	
public:
	float gravity = 9.8;
	float maxSpeed  = 16;
	
	
	inline void stopX(){
		acceleration.x = 0;
		tick.x = 0;
	}
	
	inline void stopY(){
		acceleration.y = 0;
		tick.y = 0;
	}
	
	void updateVelocity() {
		
		tick.x += (acceleration.x != 0);
		tick.y += (acceleration.y != 0);
		velocity.x = tick.x*acceleration.x;
		if (velocity.x > maxSpeed)		 velocity.x = maxSpeed;
		else if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;
		
		velocity.y = tick.y*acceleration.y;
		if (velocity.y > maxSpeed)		 velocity.y = maxSpeed;
		else if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;
	}
	
	
	void moveEvent(){
		updateVelocity();
		position = position + velocity;
		
		if (position.x < 0)
			position.x = 0;
		else if (position.x + texture->getRect().w > Renderer::canvasSize.w)
			position.x = Renderer::canvasSize.w - texture->getRect().w;
		if (position.y < 0)
			position.y = 0;
		else if (position.y + texture->getRect().h > Renderer::canvasSize.h)
			position.y = Renderer::canvasSize.h - texture->getRect().h;
	}
	
};
#endif /* PhysicObject_hpp */
