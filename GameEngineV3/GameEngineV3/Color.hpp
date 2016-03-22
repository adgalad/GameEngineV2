//
//  Color.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include "GE_SDL.hpp"

class Color {
	
public:
	static Color red;
	static Color green;
	static Color blue;
	static Color black;
	static Color white;
	
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	
	Color();
	
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	
	SDL_Color to_SDL_Color();
	
};

#endif /* Color_hpp */
