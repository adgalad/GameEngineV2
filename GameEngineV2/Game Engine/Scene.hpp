//
//  Scene.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Texture.hpp"
#include "Camera.hpp"
#include "Object.hpp"

class Scene : ListObject{
	static int __id;
	
public:
	
	vector<Object*> objects_;/**< List with all the Object objects inside the scene */
	Texture  *background_ = NULL;
	
	virtual ~Scene(){
	
	}
	
	Scene(){
		_id = __id++;
	};
	
	void Start(){
		
	}
	

	virtual void loop(){
		for (int i = 0; i < objects_.size(); i++) {
			Object *object = (Object*)objects_[i];
			object->loop();
		}
	}


	
	void add_object(Object *obj)
	{
		objects_.push_back(obj);
	}
	
	void set_camera(Camera *camera){
//		if (!camera) {
//			printf("ERROR: Trying to assign NULL Camera to Scene\ncamera: %p\n",camera);
//			return;
//		}
//		if (camera != this->camera)
//			delete this->camera;
//		this->camera = camera;
//		if (texture != NULL){
//			this->camera->setCanvasSize(texture->getRect());
//		}
	}
	
	inline Rect get_size(){
		return Rect(0,0,0,0);
	}
	

};

#endif /* Scene_hpp */
