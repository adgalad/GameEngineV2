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
	Vector2D tick;
	Vector2D velocity;
	Vector2D acceleration;

	
public:
	Rect         canvasSize;
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
	
	virtual void loop(){
		TextureRenderer::loop();
		moveEvent();
	}
	
	virtual void updateVelocity() {
		
		tick.x += (acceleration.x != 0);
		tick.y += (acceleration.y != 0);
		velocity.x = tick.x*acceleration.x;
		if (velocity.x > maxSpeed)		 velocity.x = maxSpeed;
		else if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;
		
		velocity.y = tick.y*acceleration.y;
		if (velocity.y > maxSpeed)		 velocity.y = maxSpeed;
		else if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;
	}
	
	
	virtual void moveEvent(){
		updateVelocity();
		position = position + velocity;
		
		if (position.x < 0)
			position.x = 0;
		else if (position.x + texture->getRect().w > canvasSize.w)
			position.x = canvasSize.w - texture->getRect().w;
		if (position.y < 0)
			position.y = 0;
		else if (position.y + texture->getRect().h > canvasSize.h)
			position.y = canvasSize.h - texture->getRect().h;
	}
	
	static bool collision(PhysicObject *a, PhysicObject *b){
		if (a->_id == b->_id) return false;
		// Rectangles
		Rect A = a->texture->getCollisionRect(a->currentFrame);
		Rect B = b->texture->getCollisionRect(b->currentFrame);
		// Positions
		Vector2D positionA = a->position;
		Vector2D positionB = b->position;
		// Velocities
		Vector2D velocityA = a->velocity;
		Vector2D velocityB = b->velocity;
		
		int leftA   = positionA.x + velocityA.x;
		int topA    = positionA.y + velocityA.y;
		int rightA  = leftA + A.w;
		int bottomA = topA  + A.h;

		int leftB   = positionB.x + velocityB.x;
		int topB    = positionB.y + velocityB.y;
		int rightB  = leftB + B.w;
		int bottomB = topB  + B.h;
		
		bool collision = true;
		
		if( leftA   - velocityA.x > leftB   - velocityB.x and
		    rightA  - velocityA.x < rightB  - velocityB.x and
			bottomA - velocityA.y < bottomB - velocityB.y and
			topA    - velocityA.y > topB    - velocityB.y
		   )
		{
			//printf("Dentro de B\n");
			a->velocity = Vector2D(0, 0);
			a->position.y = topB - A.w;
			
		}
		if(     ( bottomA > topB    and topA   < bottomB and
				 rightA  > leftB   and leftA  < rightB)
				 or ( leftA   > leftB   and rightA < rightB  and
					 bottomA < bottomB and topA   > topB)
		   )
		{
			
			
			leftA   = positionA.x;
			topA    = positionA.y;
			rightA  = leftA + A.w;
			bottomA = topA  + A.h;
			
			
			if(bottomA == topB)
			{
				//					printf("1.1\n");
				a->position.x += velocityA.x;
				a->velocity.x = 0;
				
			}
			else if(leftA == rightB or leftB == rightA)
			{
				//					printf("2.1\n");
				a->position.y += velocityA.y;
				a->velocity.x = 0;
				
			}
			else
			{
				
				float speedX = velocityA.x >= 0 ? velocityA.x : -velocityA.x;
				
				float speedY = velocityA.y >= 0 ? velocityA.y : -velocityA.y;
				//					printf("speed %f %f\n",speedX,speedY);
				float timeUntilCollisionX;
				float timeUntilCollisionY;
				
				if (velocityA.x > 0)
				{
					if (velocityA.y < 0)
					{
						//							printf("3.1.1\n");
						timeUntilCollisionX = (leftB - rightA)/speedX;
						
						timeUntilCollisionY = (topA - bottomB)/speedY;
					}
					else if (velocityA.y > 0)
					{
						//							printf("3.1.2\n");
						timeUntilCollisionX = (leftB - rightA)/speedX;
						
						timeUntilCollisionY = (topB - bottomA)/speedY;
					}
					else
					{
						//							printf("3.1.3\n");
						timeUntilCollisionX = (leftB - rightA)/speedX;
						
						timeUntilCollisionY = HUGE_VALF;
					}
				}
				else if (velocityA.x < 0)
				{
					if (velocityA.y < 0)
					{
						//							printf("3.2.1\n");
						timeUntilCollisionX = (leftA - rightB)/speedX;
						
						timeUntilCollisionY = (topA - bottomB)/speedY;
					}
					else if (velocityA.y > 0)
					{
						//							printf("3.2.2\n");
						timeUntilCollisionX = (leftA - rightB)/speedX;
						
						timeUntilCollisionY = (topB - bottomA)/speedY;
					}
					else
					{
						//							printf("3.2.3\n");
						timeUntilCollisionX = (leftB - rightA)/speedX;
						
						timeUntilCollisionY = HUGE_VALF;
					}
				}
				else
				{
					timeUntilCollisionX = HUGE_VALF;
					if (velocityA.y < 0)
					{
						//							printf("3.3.1\n");
						timeUntilCollisionY = (topA - bottomB)/speedY;
					}
					else if (velocityA.y > 0)
					{
						//							printf("3.3.2\n");
						timeUntilCollisionY = (topB - bottomA)/speedY;
					}
					else
					{
						//							printf("3.3.3\n");
						timeUntilCollisionY = HUGE_VALF;
					}
				}
				
				
				if (timeUntilCollisionX != HUGE_VALF && timeUntilCollisionY != HUGE_VALF)
				{
					if(timeUntilCollisionX > 0 && timeUntilCollisionY > 0)
					{
						
						if (timeUntilCollisionX <= timeUntilCollisionY)
						{
							printf("H.1\n");
							a->position.x += timeUntilCollisionX * velocityA.x;
							
							a->position.y += timeUntilCollisionX * velocityA.y;
							
							a->velocity.x = 0;
						}
						else
						{
//							printf("H.2 (%f,%f) (%f, %f) \n",timeUntilCollisionX, timeUntilCollisionY, velocityA.x, velocityA.y);
//							printf(" %d %d\n", X, Y);
							a->position = positionA + Vector2D(timeUntilCollisionY * velocityA.x,
																   timeUntilCollisionY * velocityA.y);
//							printf(" %d %d\n", X, Y);
							a->velocity.y = 1;
						}
					}
					else if (timeUntilCollisionX < 0 && timeUntilCollisionY >= 0)
					{
						printf("H.3\n");
						a->position = positionA + Vector2D(velocityA.x,timeUntilCollisionY * velocityA.y);
						a->velocity.y = 1;
					}
					else if (timeUntilCollisionY < 0 && timeUntilCollisionX >= 0)
					{
//						printf("H.4 %d %d\n",topB, Y+height);
						a->position.x += timeUntilCollisionX * velocityA.x;
						
//						if (velocityY - GameParameter::_gravtiyAcceleration > 1)
//							Y += velocityY;
						
						a->velocity.x = 0;
					}
				}
				else if (timeUntilCollisionX == HUGE_VALF and timeUntilCollisionY != HUGE_VALF)
				{
					printf("J.1\n");
					if (velocityA.y > 0)
					{
						a->position.y = topB - A.h;
						a->velocity.y = 0;
					}
					else
					{
						a->position.y = bottomB;
						a->velocity.y = 1;
					}
				}
				else if(timeUntilCollisionY == HUGE_VALF and timeUntilCollisionX != HUGE_VALF)
				{
					printf("J.2\n");
					if (velocityA.x > 0)
						a->position.x = leftB - A.w;
					else
						a->position.x = rightB;
					a->velocity.x = 0;
				}

			
			}
		}


		if (not collision)
		{
			a->position = positionA + Vector2D(velocityA.x, velocityA.y);
		}
		//	printf("%d %d")
		return collision;
	}

};
#endif /* PhysicObject_hpp */
