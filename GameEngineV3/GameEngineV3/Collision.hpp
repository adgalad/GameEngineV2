//
//  Collision.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/22/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Collision_hpp
#define Collision_hpp

#ifdef __cplusplus

#include "Scene.hpp"
#include "Geometry.hpp"
#include "Vector.hpp"
#include "PhysicController.hpp"

namespace engine {

	
 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  A RectangleCollider handle the collision between Rectangles
 *  and other supported geometry figures. Multiple collider can be
 *  attached to an object to simulate more complex figures
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class RectangleCollider : public ObjectModule {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, ObjectModule);
    TAG(ar, absolute_rect);
    TAG(ar, rect);
    TAG(ar, _collision);
    TAG(ar, _trigger);
    TAG(ar, _phisicController);
    TAG(ar, colliders);
  }
  
public:
	
	Rect absolute_rect; // Rect with the absolute position within the scene
	Rect rect;          // Rect with the relative position to the associated object
	
	/**
	 * Public constructor
	 */
	RectangleCollider();

	/**
	 * Public constructor. Takes a rectangle as parameter.
	 */
	RectangleCollider(Rect r);
	
	/**
	 * Public destructor
	 */
	~RectangleCollider();

	/**
	 * Set name to the collider
	 */
	inline void setName(string name){
		ObjectModule::setName(name);
	}
	
	/**
	 * Set if its a trigger or not
	 */
	inline void setTrigger(bool value)
	{
		_trigger = value;
	}
	
	/**
	 * Return true if its a trigger
	 */
	inline bool isTrigger()
	{
		return _trigger;
	}
	
	/**
	 *	This function is called when the associated object calls its own Init().
	 *  It will setup the collider before entering the game's main loop.
	 */
	void Init();

	/**
	 * Virtual function that is called inside Init(). Can be used to add custom
	 * setups to the collider. It's empty by default.
	 */
	virtual void Start();
	
	/**
		Checks if there is a collision on every tick of the main loop, 
	  taking the proper actions when triggers are activate.
	 **/
	void Update();
	
protected:
	bool _collision = false;             //True if a collision occurs
	bool _trigger;                       //True if the collider is a trigger
	PhysicController *_phisicController = NULL; //The associated object's physicController
  
  /**
   Returns true if both given rectangles collide and false if not.
	  This function is only reached if one of them is a trigger.
   **/
  bool checkTriggerWith(RectangleCollider *collider);
  
  /**
   Returns true and calculate the next movement if both given
	  rectangles collide and false if not.
   **/
  bool checkCollisionWith(RectangleCollider *collider, double friction);
	
private:
	static vector<RectangleCollider*> colliders; //All Rectangle Colliders inside an scene.
	int id;
	
};




class CircleCollider : public ObjectModule {
	
	static vector<CircleCollider *> colliders;
	static int _id;
	int id;
	
public:
	Rect absolute_rect;
	Rect rect;
	
	CircleCollider(){
	id       = _id;
	_trigger = false;
	rect     = Rect(0,0,50,50);
	++_id;
	setName("");
	}
	~CircleCollider(){
		for (int i = 0 ; i < colliders.size() ; ++i) {
			if (colliders[i]->id == this->id){
				colliders.erase(colliders.begin()+i);
			}
		}
	}
	inline void setName(string name){
		ObjectModule::setName("RectangleCollider");
	}
	
	inline void setTrigger(bool value)
	{
		_trigger = value;
	}
	
	inline bool isTrigger()
	{
		return _trigger;
	}
	
	void Start(){

	}
	
	void Update(){

	}
	
	bool checkTriggerWith(CircleCollider *collider){
		return false;
	}
	
	bool checkCollisionWith(CircleCollider *collider, double friction){
		return false;
	}
	
private:
	bool _trigger;
	PhysicController *_phisicController = NULL;
	
};
}
EXPORT_KEY(engine::RectangleCollider);
#endif

#endif /* Collision_hpp */
