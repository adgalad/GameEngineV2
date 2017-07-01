//
//  GroundCollision.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 1/8/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "GroundCollision.hpp"



void GroundCollision::Start(){
		RectangleCollider::Start();
  engine::Rect orect = object->texture->getRect();
  rect = engine::Rect(20, orect.h - 4 - 9, orect.w-40 ,4);
}

void GroundCollision::Update(){
		RectangleCollider::Update();
  //		((SP*)object)->onGround = _collision;
}

EXPORT_IMPLEMENT(GroundCollision)
