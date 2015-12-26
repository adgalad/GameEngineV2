//
//  Camera.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/27/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp


#include "Utilities.hpp"
class Renderer;

class Camera {
	friend Renderer;
protected:
	Size *displaySize;
	Size *canvas;
public:
	
	Tuple<float> position;
	Tuple<float> *target = NULL;
	
	Camera(){
		position = Point<float>(0, 0);
	}
	virtual ~Camera(){
		displaySize = NULL;
		canvas = NULL;
		target = NULL;
	}
	
	virtual void loop(){
		int halfX  = displaySize->w/2;
		int halfY  = displaySize->h/2;
		int top    = target->y - halfY;
		int	bottom = target->y + halfY;
		int	right  = target->x + halfX;
		int	left   = target->x - halfX;
		
		if (top < 0)				 position.y = 0;
		else if (bottom > canvas->h) position.y = displaySize->h - canvas->h;
		else						 position.y = halfY - target->y;
		if (left < 0)				 position.x = 0;
		else if (right > canvas->w)  position.x = displaySize->w - canvas->w;
		else						 position.x = halfX - target->x;
	}
	
	inline void setCameraTarget(Tuple<float> *target){
		this->target = target;
	}
	
	
};
#endif /* Camera_hpp */
