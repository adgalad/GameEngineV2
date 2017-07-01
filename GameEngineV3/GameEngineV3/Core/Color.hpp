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
#include "Vector.hpp"


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
#ifdef ENGINE2D
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
    Uint8 r; /// Red Channel.
    Uint8 g; /// Green Channel.
    Uint8 b; /// Blue Channel.
    Uint8 a; /// Alpha Chanell.
    
    SDL_Color to_SDL_Color(){
      return {r,g,b,a};
    }
    
    inline bool operator == (Color other) {
      return r == other.r and b == other.b and g == other.g;
    }
    

    
#else
  class Color : private Vector4 {
    friend class Game;
  public:

    
#endif /* ENGINE2D */
    
    Color operator + (Color c);
    
    Color operator - (Color c);
    
    /**
     *  Default Contructor.
     */
    Color();
    
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    
    /**
     *  Build a Color using a hexadecimal value.
     *
     *  @param hexValue Hexadecimal value of the desired color.
     */
    Color(Uint8 hexValue);
    
    /* Common colors */
    static Color red;
    static Color green;
    static Color blue;
    static Color yellow;
    static Color black;
    static Color white;
    
  };

  
}
#endif /* __cplusplus */
#endif /* Color_hpp */
