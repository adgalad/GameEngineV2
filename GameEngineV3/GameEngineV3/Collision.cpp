// ///////////////////////////////////////////////////
//
//  Collision.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/22/16.
//  Copyright © 2016 ARSC. All rights reserved.
//
// ///////////////////////////////////////////////////
//
//  This file contains the implementation of some
//  Colliders like Rectangle Collider
//
// ///////////////////////////////////////////////////

#include "Collision.hpp"

using namespace engine;

vector<RectangleCollider *> RectangleCollider::colliders;


RectangleCollider::RectangleCollider(){
	id = 1;
	setName("");
	_trigger = false;
	rect = Rect(0,0,50,50);
  ObjectModule::setName("RectangleCollider");
}

RectangleCollider::RectangleCollider(Rect r){
	id = 1;
	setName("");
	_trigger = false;
	rect = r;
	ObjectModule::setName("RectangleCollider");
}

RectangleCollider::~RectangleCollider(){
	for (int i = 0 ; i < colliders.size() ; ++i) {
		if (colliders[i]->id == this->id){
			colliders.erase(colliders.begin()+i);
			
		}
	}
}

void RectangleCollider::Init(){
	if (object){
		colliders.push_back(this);
		_phisicController =(PhysicController*) object->getModule("PhysicController");
		absolute_rect = rect;
		absolute_rect.x += object->transform.position.x;
		absolute_rect.y += object->transform.position.y;
		id = object->getId();
		Start();
	}
	else {
		error("Warning: Collider without associated Object\n");
	}
}

void RectangleCollider::Start(){
	
}

void RectangleCollider::Update(){
  
	absolute_rect = rect;
	absolute_rect.x += object->transform.position.x;
	absolute_rect.y += object->transform.position.y;
	absolute_rect.w *= object->transform.scale.x;
	absolute_rect.h *= object->transform.scale.y;
	_collision = false;
	bool col = false;
  
	for (int i = 0 ; i < colliders.size(); ++i)
	{
		if (colliders[i]->id != this->id and !colliders[i]->object->deleted)
		{
			if (!colliders[i]->isTrigger() and !_trigger )
			{
        PhysicController *pc;
        pc = (PhysicController*)colliders[i]->object->getModule("PhysicController");
        double f = pc == NULL ? 0 : pc->friction;
				if ((col = checkCollisionWith(colliders[i], f)))
				{
					object->EnterCollision(colliders[i]->object);
				}
			}
			else if ((col = checkTriggerWith(colliders[i])))
			{
				object->EnterTrigger(colliders[i]->object);
			}
		}
		_collision |= col;
	}

	absolute_rect.x += object->movement.x;
	absolute_rect.y += object->movement.y;
}

bool RectangleCollider::checkTriggerWith(RectangleCollider *collider){
	
		double leftA   = absolute_rect.x + object->movement.x;
		double topA    = absolute_rect.y + object->movement.y;
		double rightA  = absolute_rect.w + leftA;
		double bottomA = absolute_rect.h + topA;
		
		double leftB   = collider->absolute_rect.x;
		double topB    = collider->absolute_rect.y;
		double rightB  = collider->absolute_rect.w + leftB;
		double bottomB = collider->absolute_rect.h + topB;
				
		if(leftA   > rightB  or rightA < leftB or
			 bottomA < topB    or topA   > bottomB)
		{
			return false;
		} else {
			return true;
		}
}

 /*
		Returns true and calculate the next movement if both given
	  rectangles collide and false if not.
 */
bool RectangleCollider::checkCollisionWith(RectangleCollider *collider, double friction){
	if((object->movement.x != 0 or object->movement.y != 0))
	{

		double leftABeforeMove   = absolute_rect.x;
		double topABeforeMove    = absolute_rect.y;
		double rightABeforeMove  = absolute_rect.w + leftABeforeMove;
		double bottomABeforeMove = absolute_rect.h + topABeforeMove;
		
		double leftA   = absolute_rect.x + object->movement.x;
		double topA    = absolute_rect.y + object->movement.y;
		double rightA  = absolute_rect.w + leftA;
		double bottomA = absolute_rect.h + topA;
		
		double leftB   = collider->absolute_rect.x;
		double topB    = collider->absolute_rect.y;
		double rightB  = collider->absolute_rect.w + leftB;
		double bottomB = collider->absolute_rect.h + topB;
		
		
		if(( (leftA   > rightB  and leftABeforeMove   > rightB )  or
				 (rightA  < leftB   and rightABeforeMove  < leftB  )) or
			 ( (bottomA < topB    and bottomABeforeMove < topB   )  or
				 (topA    > bottomB and topABeforeMove    > bottomB)))
		{
			return false;
		}
		
		if (leftABeforeMove < leftB and rightABeforeMove  > rightB and
				topABeforeMove  > topB  and bottomABeforeMove < bottomB)
		{
			object->move(-object->movement+Vector2D(0, bottomB - bottomA));
			return false;
		}
		
		Vector2D new_move = object->movement;
		if ((topB    <= bottomABeforeMove and bottomABeforeMove <= bottomB) or
				(bottomB >= topABeforeMove    and topABeforeMove    >= topB   ) or
				(topB    >= topABeforeMove    and bottomABeforeMove >= bottomB))
		{
			/* Right Collision */
			if (rightA >= leftB and new_move.x > 0 and
					(leftA < leftB or rightABeforeMove <= leftB))
			{
				new_move.x = leftB - rightABeforeMove - 1;
				if (_phisicController)
				{
					_phisicController->velocity.x = 0;
					_phisicController->addFrictionY(1);
				}
			}
			/* Left Collision */
			else if (leftA      <= rightB and
							 new_move.x <  0      and
							 (rightA > rightB or leftABeforeMove >= leftB))
			{
				new_move.x = rightB - leftABeforeMove + 1;
				if (_phisicController)
				{
					_phisicController->velocity.x = 0;
					_phisicController->addFrictionY(1);
				}
			}
		}

		if ((rightABeforeMove >= leftB  and rightABeforeMove <= rightB) or
				(leftABeforeMove  <= rightB and leftABeforeMove  >= leftB ) or
				(leftABeforeMove  <= leftB  and rightABeforeMove >= rightB))
		{
			/* Bottom Collision */
			if (bottomA >= topB and new_move.y > 0 and
					(topA < topB or bottomABeforeMove <= topB))
			{
				
				new_move.y = topB - bottomABeforeMove - 1;
				if (_phisicController)
				{
					if (_phisicController->velocity.y > 0)
						_phisicController->velocity.y = 0;
					_phisicController->addFrictionX(friction);
				}
			}
			/* Top Collision */
			else if (topA       <= bottomB and
							 new_move.y <  0       and
							 (bottomA > bottomB or topABeforeMove >= topB))
			{
				new_move.y = bottomB - topABeforeMove + 1;
				if (_phisicController)
				{
					_phisicController->velocity.y = 0;
					_phisicController->addFrictionX(friction);
				}
			}
		}

		object->move(new_move - object->movement);

		return true;
	}
	return false;
}
EXPORT_IMPLEMENT(RectangleCollider);
