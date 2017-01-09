//
//  GroundCollision.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 4/29/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef GroundCollision_hpp
#define GroundCollision_hpp

#include "Geometry.hpp"
#include "Collision.hpp"

using namespace engine;

class GroundCollision : public RectangleCollider {
	SERIALIZE
 
  template <class Archive>
  void serialize (Archive & ar, const int version) {
    TAG_BASE(ar, RectangleCollider);
  }
  
public:
	GroundCollision() {}
	
  void Start();
  void Update();
	
};

EXPORT_KEY(GroundCollision)


#endif /* GroundCollision_hpp */
