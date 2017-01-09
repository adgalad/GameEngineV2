//
//  Geometry.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp


#ifdef __cplusplus
#include "Vector.hpp"

namespace engine {
class Rect {
  SERIALIZE
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar,x);
    TAG(ar,y);
    TAG(ar,w);
    TAG(ar,h);
  }
  
public:
	int x;
	int y;
	int w;
	int h;
	
	Rect();
	
	Rect(int x, int y, int w, int h);
	
	void operator = (Rect other);
	
	inline SDL_Rect to_sdl_rect(){
		return {x,y,w,h};
	}
	
	inline string toStr(){
		return "("+to_string(x)+", "+to_string(y)+"),("+to_string(w)+", "+to_string(h)+")";
	}
};

class Circle {
  SERIALIZE
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar,center);
    TAG(ar,radio);
  }
  
public:
	Vector2D center;
	Vector2D radio;
	
	Circle(Vector2D center, double radio);
	
	Circle(Vector2D center, Vector2D radio);
	
	inline string toStr(){
		return "Center: ("+to_string(center.x)+", "+to_string(center.y)+
					 "),\nRadio: ("+to_string(radio.x)+", "+to_string(radio.y)+")";
	}

};
}
#endif
#endif /* Geometry_hpp */
