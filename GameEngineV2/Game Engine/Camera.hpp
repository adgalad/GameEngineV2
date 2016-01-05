//
//  Camera.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/27/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp


#include "Renderer.hpp"
class Renderer;

class Camera {
protected:
	Rect canvas;
	
public:
	
	Rect visualRect;
	Tuple<float> *target = NULL;
	
	Camera(){
		visualRect = Rect(0,0,0,0);
	}
	virtual ~Camera(){
		target = NULL;
	}
	
	virtual Rect getRect(){
		Rect r;
		return r;
	}
	virtual void loop(){
		if (!target) return;

		Rect displayMode = Renderer::get()->getWindowSize();
		
//		printf("%d %d\n",displayMode.w, displayMode.h);
		int halfX  = displayMode.w/2;
		int halfY  = displayMode.h/2;
		int top    = target->y - halfY;
		int	bottom = target->y + halfY;
		int	right  = target->x + halfX;
		int	left   = target->x - halfX;
		
		if (top < 0)				 visualRect.y = 0;
		else if (bottom > canvas.h) visualRect.y = displayMode.h - canvas.h;
		else						 visualRect.y = halfY - target->y;
		if (left < 0)				 visualRect.x = 0;
		else if (right > canvas.w)  visualRect.x = displayMode.w - canvas.w;
		else						 visualRect.x = halfX - target->x;
	}
	
	inline void setCameraTarget(Tuple<float> *target){
		this->target = target;
	}
	
	inline void setCanvasSize(Rect canvasSize){
		this->canvas = canvasSize;
	}
	
};
#endif /* Camera_hpp */
