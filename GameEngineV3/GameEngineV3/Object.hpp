//
//  Object.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp


#ifdef __cplusplus
#include "Texture.hpp"
#include "Input.hpp"
#include "Sound.hpp"
#include "Script.hpp"


namespace engine {


template<class Scene, class ObjectModule>
class ObjectT {
  
  SERIALIZE
  
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
    // note, version is always the latest when saving
    
    TAG(ar, id);
    TAG(ar, name);
    TAG(ar, tag);
    if (texture and texture->type != SPRITE) TAG(ar, texture);
    else {
      Texture *texture = NULL;
      TAG(ar,texture);
    }
    TAG(ar, scene);
    
    TAG(ar, _transform.position);
    TAG(ar, _transform.scale);
    TAG(ar, _initial_transform.position);
    TAG(ar, _initial_transform.scale);
    TAG(ar, _movement);
    TAG(ar, _isTarget);
    
    // TAG(ar,static int _id);
    
    TAG(ar, _deleted );
    TAG(ar, __deleted);
    TAG(ar, _hidden  );
    TAG(ar, modules); 
//    TAG(ar, scripts);
  }
  
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
    vector<ObjectModule*> modules;
    TAG(ar, id);
    TAG(ar, name);
    TAG(ar, tag);
    TAG(ar, texture);
    TAG(ar, scene);
    
    TAG(ar, _transform.position);
    TAG(ar, _transform.scale);
    TAG(ar, _initial_transform.position);
    TAG(ar, _initial_transform.scale);
    TAG(ar, _movement);
    TAG(ar, _isTarget);
    
    if (_isTarget) {
     scene->camera.setTarget(this); 
    }
    
    if (id > _id) _id = id;
    
    TAG(ar, _deleted );
    TAG(ar, __deleted);
    TAG(ar, _hidden  );
    TAG(ar, modules);
    for (int i = 0 ; i < modules.size() ; ++i){
      this->addModule(modules[i]);
    }
//    TAG(ar, scripts);
  }
  SPLIT_SERIALIZATION
  
	/**
		Stores the Object's position and scale
	 **/
	struct Transform {
		Vector2D position;
		Vector2D scale;
	};
	
public:
  
	shared_ptr<Texture>	texture = NULL; /**< Object's Texture                  */
	string			          tag = "";       /**< Tags                              */
	string			          name;           /**< Name                              */
	const Transform&    transform;      /**< Read-Only reference to _transform */
	const Vector2D&     movement;       /**< Read-Only reference to _movement  */
	const bool          &deleted, &hidden;
	Scene*              scene;

	/**
	 Public Contructor.
	 **/
	ObjectT();

	/**
		Public Contructor. Set the Object's name.
	 **/
	ObjectT(string name);
	
	/**
		Virtual Destructor. Should be overrided.
	 **/
	virtual ~ObjectT(){
    modules.clear();
    for (int i = 0 ; i < scripts.size(); i++) {
      delete scripts[i];
    }
    scripts.clear();
	}
	
	void Init();
	
	/**
		Returns the Object's Module named `module_name`
	 **/
	ObjectModule *getModule(string module_name);
	
	/**
		Adds a Module to the Object's module vector
	 **/
	void addModule(ObjectModule*);
	
	/**
		Set the position to the Object's Transform
	 **/
	void setPosition(Vector2D);
	
	/**
		Set the scale to the Object's Transform
	 **/
	void setScale(Vector2D);
	
	/**
		Adds an Vector2D to the movement vector
	 **/
	void move(Vector2D);
	
	/**
		Renders the Object's Texture. Called on every iteration of the main
	  loop, after Update().
	 **/
	void Render();
	
	/**
		Private Update function. It's called before every Update().
	  Can't be overrided.
	 **/
	void InternalUpdate();
	
	/**
		Can be used to setup the user's defined attributes. It's called 
	  once before entering the main loop.
	 **/
	virtual void Start();
	
	/**
		Updates the state of the Object. It's called on every iteration
	  of the main loop before Render(). Empty by default.
	 **/
	virtual void Update();

	/**
		Handles a collision with the Object `other`. It's called only 
	  if a collision occurs. Empty by default.
	 **/
	virtual void EnterCollision(ObjectT *other);

	/**
		Handles a collision with the Object `other` when it is a trigger.
	  It's called only if a collision occurs. Empty by default.
	 **/
	virtual void EnterTrigger(ObjectT *other);
	
	/**
	  Function called after Render(). Empty by default.
	 **/
	virtual void AfterRender();
	
	/**
		Retores the initial Transform.
	 **/
	inline void reset(){ _transform = _initial_transform; }

	/**
		Return the Object's id
	 **/
	inline int getId() { return id; }
	
	/**
		Deletes the object from any scene.
	 **/
	inline void remove(){
		__deleted = true;
	}
	
	inline void hide(bool p) {
		_hidden = p;
	}
	
  inline void addLuaScript(LuaScript *newScript) {
    scripts.push_back(newScript);
  }
  
  inline void isTarget(bool b) { _isTarget = b; }
	
private:
	static int _id;
	int id;

	
	Vector2D	    _movement;           /**< How many pixels will move the object */
	Transform	  _transform;          /**< Storage the Object's position and scale */
	Transform	  _initial_transform;  /**< Saves the initial transform */
	bool        _deleted  = false;   /**< If true, the Scene will delete the Object. */
	bool        __deleted = false;
	bool        _hidden   = false;   /**< If true, the scene will ignore the Object. */
  bool        _isTarget = false;
  
	vector<ObjectModule *>	modules; /**< Modules associate to the Object. */
  vector<LuaScript*> scripts;
};
}

namespace engine {
  class Scene;
  template<class T> class ObjectModuleT;
  typedef ObjectT<Scene,ObjectModuleT<Scene>> Object;
}

using namespace engine;
EXPORT_ABSTRACT_KEY(Object);

#endif
#endif /* Object_hpp */
