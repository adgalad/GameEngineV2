//
//  PhysicController.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/24/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef PhysicController_hpp
#define PhysicController_hpp

#ifdef __cplusplus

#include "Scene.hpp"
#include "Vector.hpp"

namespace engine {
	
class PhysicController : public ObjectModule {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, ObjectModule);
    TAG(ar, velocity);
    TAG(ar, maxVelocity);
    TAG(ar, affectedByGravity);
    TAG(ar, _friction);
    TAG(ar, _gravity);
  }
  
public:
	Vector2D velocity;
	Vector2D maxVelocity;
  bool     affectedByGravity = true;
  const double& friction;
	
	PhysicController();
	
	void setName(string name);
  
  inline void setFriction(double f){ _friction = f; }
	
	void addForce(Vector2D force);
	
	void Init();
	
	void Start();
	
	void Update();
	
	void addFrictionX(float f);
	
	void addFrictionY(float f);
	
  inline static void setGravity(Vector2D gravity){ _gravity = gravity; }


	
private:
	double _friction = 1;
	static Vector2D _gravity;
};
  
}
EXPORT_KEY(engine::PhysicController);
#endif
#endif /* PhysicController_hpp */
