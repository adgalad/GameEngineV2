//
//  Color.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#ifdef __cplusplus
#include "GE_SDL.hpp"


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//RBGA
#define RMASK  0xff000000
#define GMASK  0x00ff0000
#define BMASK  0x0000ff00
#define AMASK  0x000000ff

#else
//ABGR
#define AMASK  0xff000000
#define BMASK  0x00ff0000
#define GMASK  0x0000ff00
#define RMASK  0x000000ff

#endif

namespace engine {

class Color {
  SERIALIZE
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar,r);
    TAG(ar,g);
    TAG(ar,b);
    TAG(ar,a);
  }

  
public:

	/* Common colors */
	static Color red;
	static Color green;
	static Color blue;
  static Color yellow;
	static Color black;
	static Color white;
	
	Uint8 r; /// Red Channel.
	Uint8 g; /// Green Channel.
	Uint8 b; /// Blue Channel.
	Uint8 a; /// Alpha Chanell.

	/**
	 *  Default Contructor.
	 */
	Color();
	
	/**
	 *  Build a Color with the RGBA values.
	 *
	 *	@param r Red Channel.
	 *  @param g Green Channel.
	 *	@param b Blue Channel.
	 *	@param a Alpha Channel.
	 */
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	
	/**
	 *  Build a Color using a hexadecimal value.
   *
   *  @param hexValue Hexadecimal value of the desired color.
	 */
	Color(Uint8 hexValue);
	
	/**
	 *  Transform a Color to a SDL_Color.
	 *
	 *  @return The SDL_Color equivalent.
	 */
	SDL_Color to_SDL_Color();
  
  inline bool operator == (Color other) {
    return r == other.r and b == other.b and g == other.g;
  }
  
  Color operator + (Color c){
    int nr = r + c.r;
    int ng = g + c.g;
    int nb = b + c.b;
    
    return Color(nr <= 255 ? nr : 255, ng <= 255 ? ng : 255, nb <= 255 ? nb : 255);
  }
  
  Color operator - (Color c){
    int nr = r - c.r;
    int ng = g - c.g;
    int nb = b - c.b;
    return Color(nr >= 0  ? nr : 0, ng >= 0 ? ng : 0, nb >= 0 ? nb : 0);
  }
	
};
}

#endif
#endif /* Color_hpp */
