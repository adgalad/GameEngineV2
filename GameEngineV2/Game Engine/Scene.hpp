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
#include "Player.hpp"
#include "Widget.hpp"
#include "Camera.hpp"

class Scene : public Widget{
	static int __id;
	Camera *camera;
public:
	int playerTargeted = 0;
	List entities;/**< List with all the Entity objects inside the scene */
	List players; /**< List with all the Widget objects inside the scene */
	
	virtual ~Scene(){
		Widget::~Widget();
		delete camera;
	}
	Scene(){
		_id = __id++;
		isStatic = false;
		camera = new Camera();
	};
	
	virtual bool eventHandler(){
		Uint8 *keyState = EventHandler::get()->keyState;
		if (keyState[SDL_GetScancodeFromKey(SDLK_TAB)])
		{
			playerTargeted = (playerTargeted + 1)%players.size();
			((Player*)players[playerTargeted])->setAsCameraTarget(camera);
			
		}
		return true;
	}
	
	virtual void _eventHandler(){
		eventHandler();

		for (int i = 0; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->_eventHandler();
		}
		for (int i = 0; i < entities.size(); i++) {
			((Entity*)entities[i])->_eventHandler();
		}
		for (int i = 0; i < players.size(); i++) {
			((Player*)players[i])->_eventHandler();
		}
		
	}
	
	virtual void loadTextureById(int id){
		Widget::loadTextureById(id);
		camera->setCanvasSize(texture->getRect());
	}
	
	virtual void loadTextureByName(string name){
		Widget::loadTextureByName(name);
		camera->setCanvasSize(texture->getRect());
	}
	
	virtual void loop(){
		for (int i = 0; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->loop();
		}
		for (int i = 0; i < entities.size(); i++) {
			Entity *e = ((Entity*)entities[i]);
			e->canvasSize = texture->getRect();
			e->loop();
		}
		for (int i = 0; i < players.size(); i++) {
			Player *p = ((Player*)players[i]);
			p->canvasSize = texture->getRect();
			p->loop();
		}
		camera->loop();
	}
	virtual void widgetRender(){
		render();
	}
	virtual void render(){
		widgetTexture->setAsRenderTarget();
		Renderer::get()->clearRender();
		texture->renderTexture(Point<float>(0,0), &frameRect, isStatic, angle, inverted);
		for (int i = 0; i < entities.size(); i++) {
			((Entity*)entities[i])->render();
		}
		for (int i = 0; i < players.size(); i++) {
			((Player*)players[i])->render();
		}
		Renderer::get()->setRendererTarget(NULL);
		Rect cameraRect = frameRect;


		widgetTexture->renderTexture(position, &cameraRect, isStatic, angle, inverted);
	}
	
	void setCamera(Camera *camera){
		if (!camera) {
			printf("ERROR: Trying to assign NULL Camera to Scene\ncamera: %p\n",camera);
			return;
		}
		if (camera != this->camera)
			delete this->camera;
		this->camera = camera;
		if (texture != NULL){
			this->camera->setCanvasSize(texture->getRect());
		}
	}
	
	inline Rect getRect(){
		if (father) return father->getRect();
		else {
			Rect windowRect = Renderer::get()->getWindowSize();
			Rect r = Rect(0,0, windowRect.w - position.x, windowRect.h - position.y);

			return r;
		}
	}
	
	inline void setPlayerAsTarget(int id){
		((Player*)players.getById(id))->setAsCameraTarget(camera);
	}
	inline void setPlayerAsTarget(string name){
		((Player*)players.getByName(name))->setAsCameraTarget(camera);
	}
	inline void setEntityAsTarget(int id){
		((Entity*)entities.getById(id))->setAsCameraTarget(camera);
	}
	inline void setEntityAsTarget(string name){
		((Entity*)entities.getByName(name))->setAsCameraTarget(camera);
	}
};

#endif /* Scene_hpp */
