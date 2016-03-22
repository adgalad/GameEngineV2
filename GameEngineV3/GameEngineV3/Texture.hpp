//
//  Texture.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef sdl_texturehpp
#define sdl_texturehpp



#include "Renderer.hpp"
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
class Texture {
private:
	
protected:

	SDL_Texture *sdl_texture = NULL; /**< SDL_Texture used to render using the GPU*/
	SDL_Surface *sdl_surface = NULL; /**< SDL_Surface used to create a SDL_Texture*/
				 /**< Part of the texture that will be rendered*/
	
	
	
public:
	
	Rect source_rect = Rect(0,0,0,0);
	string name = "";
	string path_ = "";			 /**< Path to the image on disk. */
	
	static Renderer *_renderer;
	
	Texture();
	
	Texture( string name, string image, Uint32 rows = 1, Uint32 columns = 1);
	
	/**
	 Create a rectangle Texture filled with the given color.
	 */
	Texture(string name, Color color, Uint32 w, Uint32 h);
	
	virtual ~Texture();
	
	/**
	 Returns a Texture object that takes the place of a NULL value. This
	 way the Renderer will render a false texture, giving a visual warning
	 of a missing texture and preventing it to access a NULL pointer.\n
	 
	 Seeing this texture generally means the code is doing something wrong
	 and should be fixed as soon as possible.
	 */
	static Texture *null();
	
	
	
	void createTargetTexture(string name, Rect r){
		source_rect = r;
		sdl_texture = SDL_CreateTexture(_renderer->sdl_renderer,
									 SDL_PIXELFORMAT_ABGR8888,
									 SDL_TEXTUREACCESS_TARGET,
									 r.w,
									 r.h);

		SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
		if (!sdl_texture){
			fprintf(stderr
					,"ERROR creating Target Texture texture\ntexture: %p\nname: %s\n%s\n"
					,sdl_texture
					,name.c_str()
					,SDL_GetError()
					);
			exit(EXIT_FAILURE);
		}
	}
	
	inline void setBlendMode(bool condition){
		if (condition)	SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
		else			SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_NONE );
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
	inline Rect getRect(){ return source_rect; }
	
	inline Vector2D getSize(){ return Vector2D(source_rect.w, source_rect.h); }
	/**
	 Fill the texture with an image loaded from disk.
	 */
	virtual void loadImage(string file, int rows = 1, int columns = 1);
	
	/**
	 Given the position and the frame that will be rendered,
	 the Texture send the information needed to the Renderer.
	 */
	virtual void Render(Vector2D	position,
						int 		angle    = 0,
						bool		inverted = false);
	
	inline void setAsRenderTarget() { _renderer->set_renderer_target(sdl_texture); }
	
	virtual inline Rect getCollisionRect(Vector2D frame){
		return source_rect;
	}
	
};

#endif /* sdl_texturehpp */
