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
#include "EventHandlerObject.hpp"

class Widget : public TextureRenderer, public EventHandlerObject{
	friend class MainWindow;
	static int __id;

	Tuple<float> absolutePosition;
	bool         hide        = false;
	
protected:
	Texture* widgetTexture	= NULL;
	bool     _updated		= false;
	bool     _pressed		= false;
	Widget*  father			= NULL;
	List     subwidgets;

	void updateVisualRect(){
		if (father) {
			absolutePosition = position + father->absolutePosition;
		}
		else {
			absolutePosition = position ;
		}
		for (int i = 0 ; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->updateVisualRect();
		}
	}
	
public:
	virtual void movePosition(Tuple<float> position){
		this->position = this->position + position;
		_updated = false;
	}
	virtual void setPosition(Tuple<float> position){
		this->position = position;
		_updated = false;
	}
	
	Widget(){
		_id = __id++;
		isStatic = true;
	}
	
	~Widget(){
		TextureRenderer::~TextureRenderer();
		widgetTexture = NULL;
		father = NULL;
	}
	
	inline void setHide(bool b){
		hide = b;
	}
	virtual bool eventHandler(){
		return true;
	}
	
	virtual void _eventHandler(){
		if (hide) return;
		eventHandler();
		Rect a = texture->getRect();
		if (not _updated) updateVisualRect();
		switch (EventHandler::get()->event.type) {
			case SDL_MOUSEBUTTONDOWN:{
				Tuple<int> point = Point<int>(EventHandler::get()->event.button.x,
											  EventHandler::get()->event.button.y);
				
				if ((absolutePosition.x       < point.x) and
					(a.w + absolutePosition.x > point.x) and
					(absolutePosition.y       < point.y) and
					(a.h + absolutePosition.y > point.y ))
				{
					
					pressed();
					_pressed = true;
				}
				else return;
				break;
				
			}
			case SDL_MOUSEBUTTONUP:{
				if (!_pressed) return;
				Tuple<int> point = Point<int>(EventHandler::get()->event.button.x,
											  EventHandler::get()->event.button.y);
				bool inside =	((absolutePosition.x       < point.x) and
								 (a.w + absolutePosition.x > point.x) and
								 (absolutePosition.y       < point.y) and
								 (a.h + absolutePosition.y > point.y ));
				if (father)	{
					inside = inside and !father->_pressed;
				}
				
				released(inside);
				_pressed = !inside;
				break;
			}
			default:
				
				break;
		}
		for (int i = 0 ; i < subwidgets.size(); i++){
			((Widget*)subwidgets[i])->_eventHandler();
		}
	}

	virtual inline void loadTextureById(int id){
		TextureRenderer::loadTextureById(id);
		#ifdef GameEngineDebugger
			if (!texture) exit(EXIT_FAILURE);
		#endif
		widgetTexture = Texture::createTargetTexture(texture->getRect());
		
	}
	
	virtual inline void loadTextureByName(string name){
		TextureRenderer::loadTextureByName(name);
		#ifdef GameEngineDebugger
			if (!texture) exit(EXIT_FAILURE);
		#endif
		widgetTexture = Texture::createTargetTexture(texture->getRect());
	}
	
	
	virtual void loop(){
		TextureRenderer::loop();
		for (int i = 0 ; i < subwidgets.size() ; i++){
			((Widget*)subwidgets[i])->loop();
		}
	}
	
	virtual void widgetRender(){
		texture->renderTexture(Point(0, 0).to_float(), &frameRect,isStatic,angle,inverted);
	}
	virtual void render(){
		frameRect.x = frameRect.w*currentFrame.x;
		frameRect.y = frameRect.h*currentFrame.y;
		if (hide) return;
		if (!widgetTexture){
			widgetTexture = Texture::createTargetTexture(texture->getRect());
		}
		widgetTexture->setAsRenderTarget();
		Renderer::get()->clearRender();
		if (animated) {
			currentFrame.y = (currentFrame.y + 1) % texture->rows();
		}
		widgetRender();

		for (int i = 0 ; i < subwidgets.size() ; i++) {
			((Widget*)subwidgets[i])->render();
		}
		Rect r = texture->getRect();
		if (!father){
			Renderer::get()->setRendererTarget(NULL);
			widgetTexture->renderTexture(position,&r,isStatic);
		}
		else{
			father->widgetTexture->setAsRenderTarget();
			widgetTexture->renderTexture(position,&r,true,angle,inverted);
		}
	}
	
	void addSubwidget(Widget *w){
		w->father = this;
		subwidgets.pushBack(w);
		updateVisualRect();
	}
	
	inline Rect getRect(){
		return texture->getRect();
	}
	virtual void pressed(){
		printf("pressed\n");
	}
	
	virtual void released(bool inside){
		printf("Released\n");
	}
};
#endif /* Widget_hpp */
