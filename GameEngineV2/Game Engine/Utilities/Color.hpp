//
//  Color.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <SDL2/SDL.h>

class Color {
	
public:
	static Color red;
	static Color green;
	static Color blue;
	static Color black;
	static Color white;
	
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	
	Color();
	
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	
	SDL_Color to_SDL_Color();
	
};
#endif /* Color_hpp */
