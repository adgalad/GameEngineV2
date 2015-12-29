//
//  Texture.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/19/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "ListObject.hpp"
#include "Renderer.hpp"
#include <SDL2_image/SDL_image.h>
#include <string>
#include <iostream>

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

#define NULL_TEXTURE "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/ErrorTexture.jpg"
using namespace std;
/**
 The Texture class offer the neccessary tools to load and render textures using 
 the SDL Framework.
 */
class Texture : public ListObject {
protected:
	static int __id;			 /**< Global id */
	
	string path = "";			 /**< Path to the image on disk. */
	SDL_Texture *texture = NULL; /**< SDL_Texture used to render using the GPU*/
	SDL_Surface *surface = NULL; /**< SDL_Surface used to create a SDL_Texture*/
	Rect srcRect;			 /**< Part of the texture that will be rendered*/
	
	Texture();
	
public:
	static List textures;
	
	static Texture createTexture();
	
	virtual ~Texture();
	
	/**
	 Returns a Texture object that takes the place of a NULL value. This
	 way the Renderer will render a false texture, giving a visual warning
	 of a missing texture and preventing it to access a NULL pointer.\n
	
	 Seeing this texture generally means the code is doing something wrong
	 and should be fixed as soon as possible.
	 */
	static Texture *null();
	
	/**
	 Create a rectangle Texture filled with the given color.
	 */
	static Texture *createRGBTexture(Color color,
									 unsigned int w,
									 unsigned int h
									 );
	
	static Texture *createTargetTexture(Rect r){
		Texture *t = new Texture();
		t->srcRect.w = r.w;
		t->srcRect.h = r.h;
		t->texture = Renderer::createTexture(SDL_PIXELFORMAT_ABGR8888,
										  SDL_TEXTUREACCESS_TARGET,
										  r.w,
										  r.h);
		SDL_SetTextureBlendMode(t->texture, SDL_BLENDMODE_BLEND);
		if (!t->texture){
			fprintf(stderr
					,"ERROR creating Target Texture texture\ntexture: %p\nid: %d\nname: %s\n%s\n"
					,t->texture
					,t->_id
					,t->name.c_str()
					,SDL_GetError()
					);
			exit(EXIT_FAILURE);
		}
		return t;
	}
	
	inline void setBlendMode(bool condition){
		if (condition)	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		else			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE );
	}
	/**
	 Returns the number of rows. if the texture is not a sprite, it's always 1.
	 */
	virtual inline int rows() {return 1;}

	/**
	 Returns the number of columns. if the texture is not a sprite, it's always 1.
	 */
	virtual inline int columns() {return 1;}
	
	/**
	 Get the texture dimensions or frame's dimension if its a sprite.
	 */
	inline Rect getRect(){ return srcRect; }
	
	/**
	 Fill the texture with an image loaded from disk.
	 */
	virtual void loadImage(string file, int rows = 1, int columns = 1);
	
	/**
	 Given the position and the frame that will be rendered,
	 the Texture send the information needed to the Renderer.
	 */
	virtual void renderTexture(Tuple<float> position,
							   Rect			*srcRect,
							   bool			isStatic = false,
							   int			angle    = 0,
							   bool			inverted = false);
	
	inline void setAsRenderTarget() { Renderer::setRendererTarget(texture); }
	
	virtual inline Rect getCollisionRect(Tuple<int> frame){
		return srcRect;
	}
	
};

#endif /* Texture_hpp */
