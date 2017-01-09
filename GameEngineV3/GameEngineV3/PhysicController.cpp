//
//  PhysicController.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/24/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "PhysicController.hpp"

using namespace engine;

Vector2D PhysicController::_gravity = Vector2D(0,1);

PhysicController::PhysicController() : friction(_friction){ setName(""); }

void PhysicController::setName(string name) {
  ObjectModule::setName("PhysicController");
}

void PhysicController::addForce(Vector2D force) {
  velocity += force;
  // X Axis
  if (velocity.x > maxVelocity.x)
    velocity.x = maxVelocity.x;
  else if (velocity.x < -maxVelocity.x)
    velocity.x = -maxVelocity.x;
  // Y Axis
  if (velocity.y > maxVelocity.y)
    velocity.y = maxVelocity.y;
  else if (velocity.y < -maxVelocity.y)
    velocity.y = -maxVelocity.y;
}

void PhysicController::Init() { Start(); }
void PhysicController::Start() {}
void PhysicController::Update() {
  if (affectedByGravity)
    velocity += _gravity;
  addFrictionX(1);

  object->move(velocity);
}

void PhysicController::addFrictionX(float f) {
  if (velocity.x > 0) {
    velocity.x -= f;
    if (velocity.x < 0)
      velocity.x = 0;
  } else if (velocity.x < 0) {
    velocity.x += f;
    if (velocity.x > 0)
      velocity.x = 0;
  }
}

void PhysicController::addFrictionY(float f) {
  if (velocity.y > 0) {
    velocity.y -= f;
    if (velocity.y < 0)
      velocity.y = 0;
  } else if (velocity.y < 0) {
    velocity.y += f;
    if (velocity.y > 0)
      velocity.y = 0;
  }
}

EXPORT_IMPLEMENT(PhysicController);
