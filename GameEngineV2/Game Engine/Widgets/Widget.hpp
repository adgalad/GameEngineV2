//
//  Widget.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/23/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Widget_hpp
#define Widget_hpp

#include "TextureRenderer.hpp"
#include "ListObject.hpp"

class Widget : public TextureRenderer{
	static int __id;
	
	Texture *widgetTexture = NULL;
	Tuple<float> absolutePosition;
	Rect		 visualRect;
	bool hide = false;
protected:

	bool _pressed;
	Widget *father = NULL;
	List subwidgets;
	

	
public:
	virtual void movePosition(Tuple<float> position){
		this->position = this->position + position;
	}
	virtual void setPosition(Tuple<float> position){
		this->position = position;
	}
	
	Widget(){
		_id = __id++;
	}
	
	~Widget(){
		TextureRenderer::~TextureRenderer();
		widgetTexture = NULL;
		father = NULL;
	}
	
	inline void setHide(bool b){
		hide = b;
	}
	virtual void eventHandler(SDL_Event *event, Uint8 *keyStates){
		int n = 10;
		if (hide) return;
		if (keyStates[SDL_GetScancodeFromKey(SDLK_KP_2)]){
			movePosition(Point<float>(0,n));
			return;
		}
		if (keyStates[SDL_GetScancodeFromKey(SDLK_KP_8)]){
			movePosition(Point<float>(0,-n));
			return;
		}
		if (keyStates[SDL_GetScancodeFromKey(SDLK_KP_6)]){
			movePosition(Point<float>(n,0));
			return;
		}
		if (keyStates[SDL_GetScancodeFromKey(SDLK_KP_4)]){
			movePosition(Point<float>(-n,0));
			return;
		}


		switch (event->type) {
			case SDL_MOUSEBUTTONDOWN:{
				
				Rect rect = texture->getRect();
				
				if (father) {
					Rect frect = father->visualRect;
					absolutePosition = position + father->absolutePosition;
					
					int topA	= absolutePosition.y;
					int bottomA = absolutePosition.y + rect.h;
					int leftA   = absolutePosition.x;
					int rightA  = absolutePosition.x + rect.w;
					
					int topB	= frect.y;
					int bottomB = frect.h;
					int leftB   = frect.x;
					int rightB  = frect.w;

					
					if (leftA < leftB)
						visualRect.x = leftB;
					else
						visualRect.x = leftA;
					
					if (topA < topB)
						visualRect.y = topB;
					else
						visualRect.y = topA;
					
					if (rightA > rightB)
						visualRect.w = rightB;
					else
						visualRect.w = rightA;
						
					if (bottomA > bottomB)
						visualRect.h = bottomB;
					else
						visualRect.h = bottomA;
						
				}
				else {
					
					absolutePosition = position ;
					visualRect = Rect(absolutePosition.x,
									  absolutePosition.y,
									  absolutePosition.x + rect.w,
  									  absolutePosition.y + rect.h);
				}
				
				Tuple<int> point = Point<int>(event->button.x,event->button.y) -
								   Renderer::camera->position.to_int();
				
				if ((visualRect.x < point.x) and
					(visualRect.w > point.x) and
					(visualRect.y < point.y) and
					(visualRect.h > point.y ))
				{
					pressed();
					_pressed = true;
				}
				break;

			}
			case SDL_MOUSEBUTTONUP:{
				if (!_pressed) break;
				Tuple<int> point = Point<int>(event->button.x,event->button.y) -
								   Renderer::camera->position.to_int();
				bool inside =	(visualRect.x < point.x) and
								(visualRect.w > point.x) and
								(visualRect.y < point.y) and
								(visualRect.h > point.y );
				released(inside);
				_pressed = false;
				break;
			}
			default:

				break;
		}
		for (int i = 0 ; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->eventHandler(event, keyStates);
		}
	}

	virtual inline void loadTextureById(int id){
		TextureRenderer::loadTextureById(id);
		#ifdef GameEngineDebugger
			if (!texture) exit(EXIT_FAILURE);
		#endif
		visualRect = texture->getRect();
		widgetTexture = Texture::createTargetTexture(texture->getRect());
		
	}
	
	virtual inline void loadTextureByName(string name){
		TextureRenderer::loadTextureByName(name);
		#ifdef GameEngineDebugger
			if (!texture) exit(EXIT_FAILURE);
		#endif
		visualRect = texture->getRect();
		widgetTexture = Texture::createTargetTexture(texture->getRect());
	}
	
	
	virtual void loop(){
		TextureRenderer::loop();
		for (int i = 0 ; i < subwidgets.size() ; i++){
			((Widget*)subwidgets[i])->loop();
		}
	}
	
	
	virtual void render(){
		if (hide) return;
		if (!widgetTexture){
			widgetTexture = Texture::createTargetTexture(texture->getRect());
		}
		widgetTexture->setAsRenderTarget();
		Renderer::clearRender();
		if (animated) {
			currentFrame.y = (currentFrame.y + 1) % texture->rows();
		}
		texture->renderTexture(Point<float>(0, 0), &frameRect, true,angle,inverted);

		for (int i = 0 ; i < subwidgets.size() ; i++) {
			((Widget*)subwidgets[i])->render();
		}
		Rect r = texture->getRect();
		if (!father){
			Renderer::setRendererTarget(NULL);
			widgetTexture->renderTexture(position,&r);
		}
		else{
			father->widgetTexture->setAsRenderTarget();
			widgetTexture->renderTexture(position,&r,true,angle,inverted);
		}
	}
	
	void addSubwidget(Widget *w){
		w->father = this;
		subwidgets.pushBack(w);
	}
	virtual void pressed(){
		printf("pressed\n");
	}
	
	virtual void released(bool inside){
		printf("Released\n");
	}
};
#endif /* Widget_hpp */
