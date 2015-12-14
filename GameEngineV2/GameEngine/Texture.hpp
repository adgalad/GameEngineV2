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
	int r = 1;					 /**< Number of rows. */
	int c = 1;					 /**< Number of columns. */
	Rect srcRect;				/**< Part of the texture that will be rendered*/
	
public:
	static List textures;


	
	Texture();
	
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
	static Texture *createRGBTexture(SDL_Color color,
									 unsigned int w,
									 unsigned int h
									 );
	
	static Texture *createTargetTexture(Rect r){
		Texture *t = new Texture();
		t->c = 1;
		t->r = 1;
		t->srcRect.w = r.w;
		t->srcRect.h = r.h;
		t->texture = Renderer::createTexture(SDL_PIXELFORMAT_ABGR8888,
										  SDL_TEXTUREACCESS_TARGET,
										  r.w,
										  r.h);
		SDL_SetTextureBlendMode(t->texture, SDL_BLENDMODE_BLEND);
		if (!t->texture){
			fprintf(stderr
					,"ERROR creating Target Texture texture\ntexture: %p\nid: %d\n%s\n"
					,t->texture
					,t->_id
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
	inline int rows() {return r;}

	/**
	 Returns the number of columns. if the texture is not a sprite, it's always 1.
	 */
	inline int columns() {return c;}
	
	/**
	 Get the texture dimensions or frame's dimension if its a sprite.
	 */
	inline Rect getRect(){ return srcRect; }
	
	/**
	 Fill the texture with an image loaded from disk.
	 */
	void loadImage(string file, int rows, int columns);
	
	/**
	 Given the position and the frame that will be rendered,
	 the Texture send the information needed to the Renderer.
	 */
	virtual void renderTexture(Tuple<float> position,Tuple<int> frame,
							   int angle = 0, bool inverted = false,
							   Rect *rect = NULL);
	
	inline void setAsRenderTarget() { Renderer::setRendererTarget(texture); }
	
};

#endif /* Texture_hpp */
