//
//  Scene.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp
#ifdef __cplusplus
#include "ObjectModule.hpp"
#include "source/ObjectModule.cpp"

namespace engine {



template<class Object>
class Camera {
  friend class Scene;  
  SERIALIZE
  
	friend class SceneT;
	Rect rect;
	Rect sceneRect;
	Object *target = NULL;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar, rect);
    TAG(ar, sceneRect);
//    TAG(ar, target);
  }
	
public:

	Camera(){};
	
	/** 
		Returns the Rect's dimensions that the Renderer2D's target
	  Texture will renders.
	 */
	Rect getCameraRect();
	
	/** 
		Tells to Camera the size of the current Scene
	 */
	inline void setSceneSize(Rect rect)  { sceneRect = rect; }
	
	/**
		Set the Camera's size
	 */
	inline void setCameraRect(Rect rect) { this->rect = rect; }
	
	/**
		Set Camera's target
	 */
	inline void setTarget(Object *obj) {
    if (target) target->isTarget(false);
    target = obj;
    target->isTarget(true);
  }
  
  inline Rect getSceneRect() { return sceneRect; }
	
	
};


class Scene {
  friend class Game;
  SERIALIZE
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar, name);
    TAG(ar, background);
    TAG(ar, camera);
    TAG(ar, objs);
    TAG(ar, _target_texture);
    TAG(ar, _hasObjectToRemove);
    TAG(ar, _clearRender);
  }
  
  
  
  
public:
	string name;
	Texture *background = NULL;
	Camera<ObjectT<Scene, ObjectModuleT<Scene>>> camera;
	
  
  
  // Test
  Texture *tex= NULL;
	virtual ~Scene();
	
	void addObject(ObjectT<Scene, ObjectModuleT<Scene>> *object);
	
//	void deleteObjectById(int id);
	
//	void deleteObjectByName(int id);
  Scene();
	
	Scene (string name, Rect size);
	
	virtual void Init();
	
	virtual void Reset();
	
	virtual void Start();
	
	virtual void Update();
  
	virtual void Render();

  virtual void AfterRender();
	
  void clearTargetAfterRender(bool);
  
	inline Vector2 getTargetTextureSize(){
		return _target_texture->getSize();
	}
  
  

  
	
private:
	
  
  void InternalRender();
  
  void InternalUpdate();
  
	vector<ObjectT<Scene, ObjectModuleT<Scene>> *> objs;
	Texture *_target_texture = NULL;
	bool _hasObjectToRemove  = false;
  bool _clearRender        = true;
};

//  typedef ObjectT<Scene,ObjectModuleT<Scene>> Object;
//  typedef ObjectModuleT<Scene> ObjectModule;
  

  
}


using namespace engine;
EXPORT_KEY(Scene);

std::ostringstream sceneToStream(const Scene &scene);

void streamToScene(std::istringstream *sceneBytes, Scene &scene);


#endif
#endif /* Scene_hpp */
