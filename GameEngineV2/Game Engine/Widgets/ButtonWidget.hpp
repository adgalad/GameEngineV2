//
//  ButtonWidget.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/10/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef ButtonWidget_hpp
#define ButtonWidget_hpp

#include "Widget.hpp"
#include "TextTexture.hpp"

class ButtonWidget : public Widget{
	TextTexture *text;
	TextTexture *pressedText;
public:
	ButtonWidget(){
		text = new TextTexture();
		pressedText = new TextTexture();
		
	}
	
	void setFont(string font, int size){
		text->setFont(font, size);
		pressedText->setFont(font, size);
	}
	void setTextColor(Color color){
		text->setColor(color);
	}
	
	void setTextPressedColor(Color color){
		pressedText->setColor(color);
	}
	
	void setMessage(const char *message, ...){
		char buf[1024];
		sprintf(buf, "");
		va_list ap;
		va_start(ap, message);
		vsprintf(buf + strlen(buf), message, ap);
		va_end(ap);
		printf("%d\n",frameRect.w);
		text->setMessage(frameRect.w, buf);
		pressedText->setMessage(frameRect.w, buf);
		
		
	}
	
	void widgetRender(){
		Widget::widgetRender();
		if (currentFrame.y)	pressedText->renderTexture(Point(0, 0).to_float(), NULL, true);
		else				text->renderTexture(Point(0, 0).to_float(), NULL, true);

	}
	
	virtual void pressed(){
		printf("Button Pressed --\n");
		currentFrame.y = 1;
	}
	
	virtual void eventHandler(){
		
	}
	
	virtual void released(bool inside){
		printf("Button Released -- \n");
		currentFrame.y = 0;
		if (inside){
			father->setHide(true);
		}
	}
};

#endif /* ButtonWidget_hpp */
