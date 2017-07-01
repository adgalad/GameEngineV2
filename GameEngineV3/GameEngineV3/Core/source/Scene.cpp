//
//  Scene.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Game.hpp"
#include "Object.hpp"

using namespace engine;

inline bool hasToBeRemoved(Object *obj) {
	return obj->deleted;
}


template<class T>
Rect Camera<T>::getCameraRect() {
  
	Vector2 v = Application.window()->getSize();
	rect = Rect(  0, 0
							, min((int)v.x,sceneRect.w)
							, min((int)v.y,sceneRect.h));

	Rect cameraRect = rect;

	if (target){
		Vector2 p  = target->transform.position;
		Rect r     = target->texture->getRect();
		Vector2 ss = Application.window()->getSize();
		/*
		 Mueve la camara si el target esta en el centro de la pantalla.
		 CameraRect siempre debe tener campos positivos, de lo contrario
		 distorciona la imagen
			*/
		if (p.x > 0){
			cameraRect.x += p.x - (ss.x - r.w)/2;
			if ( cameraRect.x < 0) cameraRect.x = 0;
		}
		if (p.y > 0){
			cameraRect.y += p.y - (ss.y - r.h)/2;
			if ( cameraRect.y < 0) cameraRect.y = 0;
		}
		
	}
	if (cameraRect.x + rect.w > sceneRect.w)
	{
		cameraRect.x = sceneRect.w - rect.w;
	}
	if (cameraRect.y + rect.h > sceneRect.h)
	{
		cameraRect.y = sceneRect.h - rect.h;
	}
	return cameraRect;
}



Scene::Scene(){
  Vector2 v = Application.window()->getSize();
  camera.setSceneSize(Rect(0,0,v.x,v.y));
  camera.setCameraRect(Rect(0,0,v.x,v.y));

};

Scene::Scene (string name, Rect size){

	this->name = name;
	Rect cameraSize;
	Vector2 v = Application.window()->getSize();
	camera.setSceneSize(size);
  if (size == Rect(0,0,0,0)){
      camera.setCameraRect(Rect(0,0,v.x,v.y));
  } else {
    camera.setCameraRect(size);
  }
	
}

Scene::~Scene(){
	for (int i = 0; i < objs.size(); ++i){
		delete objs[i];
	}
	delete background;
}

void Scene::addObject(Object *object) {
	objs.push_back(object);
	object->scene = this;
}




void Scene::Init(){
  
  _target_texture = new Texture();
  _target_texture->createTargetTexture("Target Texture Scene "+name, camera.sceneRect);
  
	Start();
	for (int i  = 0 ; i < objs.size(); i ++){
		objs[i]->Init();
	}
  
}

void Scene::Reset(){
	for (int i  = 0 ; i < objs.size(); i ++){
		objs[i]->reset();
	}
}



void Scene::Start(){
//	camera.setCameraRect(Rect(30,30,300,300));
	if (not _target_texture) {
		if (objs.size() > 0 and objs[0]->texture) {
			_target_texture = objs[0]->texture.get();
      _target_texture->setAsRenderTarget();
      Application.renderer()->clearRender();
		}
    else {
      error("Could not initialize Scene Target Texture");
    }
  } else {
    _target_texture->setAsRenderTarget();
    Application.renderer()->clearRender();
  }
}

void Scene::Update(){
  
}

void Scene::InternalUpdate(){
  Update();
  for (int i  = 0 ; i < objs.size(); i ++){
    objs[i]->InternalUpdate();
    _hasObjectToRemove |= objs[i]->deleted;
  }
  
  if (_hasObjectToRemove) {
    objs.erase(remove_if(objs.begin(), objs.end(), hasToBeRemoved), objs.end());
  }
  _hasObjectToRemove = false;
}

void Scene::clearTargetAfterRender(bool b){
  _clearRender = b;
}

void Scene::InternalRender(){
  
  if (background){
    background->Render(Vector2(0,0));
  }
  Render();
  for (int i  = 0 ; i < objs.size(); i ++){
    objs[i]->Render();
  }
  
  AfterRender();
  for (int i  = 0 ; i < objs.size(); i ++){
    objs[i]->AfterRender();
  }
  Application.renderer()->setRendererTarget(NULL);
  Rect srcRect = camera.getCameraRect();

  Vector2 pos   = Vector2(0,0)
         , scale = Vector2(1,1);
  _target_texture->Render(pos, scale, &srcRect);
  _target_texture->setAsRenderTarget();
  
  if (_clearRender) Application.renderer()->clearRender();

}
void Scene::Render(){}

void Scene::AfterRender(){}

EXPORT_IMPLEMENT(Scene);
EXPORT_IMPLEMENT(Object);
EXPORT_IMPLEMENT(ObjectModule);

std::ostringstream sceneToStream(const Scene &scene){
  std::ostringstream ostrs (std::ostringstream::binary);
  OUT_ARCHIVE oa(ostrs);
  TAG_OA(oa, scene);
  return ostrs;
}

void streamToScene(std::istringstream *istrs, Scene &scene){
  IN_ARCHIVE ia(*istrs);
  TAG_IA(ia, scene);
}















