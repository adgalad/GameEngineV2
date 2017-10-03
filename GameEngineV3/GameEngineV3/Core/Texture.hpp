//
//  Texture.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef sdl_texturehpp
#define sdl_texturehpp


#ifdef __cplusplus
#include "Renderer.hpp"


#define NULL_TEXTURE "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/Resources/ErrorTexture.jpg"

namespace engine {

  enum TextureType {
    SOLID_COLOR,
    STANDARD,
    SPRITE
    
  };
  
using namespace std;
/**
 The Texture class offer the neccessary tools to load and render textures using
 the SDL Framework.
 */
class Texture {
  friend class Game;
  SERIALIZE
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
    // note, version is always the latest when saving
    TAG(ar, name);
    TAG(ar, path);
    TAG(ar, type);
    TAG(ar, source_rect);
    TAG(ar, color);
  }
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
    TAG(ar, name);
    TAG(ar, path);
    TAG(ar, type);
    TAG(ar, source_rect);
    TAG(ar, color);
    
    switch (type) {
      case SOLID_COLOR:
        createColorTexture();
        path = "";
        break;
      case STANDARD:
        loadImage(path);
        color = Color::black;
        break;
      case SPRITE:
        Debug::Log("Could not load a Texture from a Sprite. Sprites must do the job.");
        delete this;
        break;
      default:
        break;
    }
  }
  
  SPLIT_SERIALIZATION
  
  static Renderer2D *_renderer;
  
protected:
  Color color = Color(0, 0, 0);
	SDL_Texture *sdl_texture = NULL; /**< SDL_Texture used to render using the GPU*/
	SDL_Surface *sdl_surface = NULL; /**< SDL_Surface used to create a SDL_Texture*/
  	
public:
	
	Rect source_rect = Rect(0,0,0,0); /**< Part of the texture that will be rendered*/

	string path = "";			 /**< Path to the image on disk. */
	string name = "";
  TextureType type;
	
	
	Texture();
	
	Texture(string name, string image, Uint32 rows = 1, Uint32 columns = 1);
	
  Texture(string name, string _path, SDL_Surface *surface);
	/**
	 Create a rectangle Texture filled with the given color.
	 */
	Texture(string name, Color color, Uint32 w, Uint32 h);
	
	virtual ~Texture();
	
	/**
	 Returns a Texture object that takes the place of a NULL value. This
	 way the Renderer2D will render a false texture, giving a visual warning
	 of a missing texture and preventing it to access a NULL pointer.\n
	 
	 Seeing this texture generally means the code is doing something wrong
	 and should be fixed as soon as possible.
	 */
	static Texture *null();
	
  void glBind(){
    SDL_GL_BindTexture(sdl_texture, NULL, NULL);
  }
	
	void createTargetTexture(string name, Rect r){
		source_rect = r;
    if (sdl_texture != NULL){
      SDL_DestroyTexture(sdl_texture);
      sdl_texture = NULL;
    }
    
		sdl_texture = SDL_CreateTexture(_renderer->sdl_renderer,
									 SDL_PIXELFORMAT_ABGR8888,
									 SDL_TEXTUREACCESS_TARGET,
									 r.w,
									 r.h);
		
		if (sdl_texture == NULL){
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                               "Error",
                               ("ERROR: Could not create Target Texture\nname: "+name+"\n "+SDL_GetError()).c_str(),
                               NULL);
			error("ERROR: Could not create Target Texture\nname: "+name+"\n "+SDL_GetError());
			exit(EXIT_FAILURE);
		}
    SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
	}
	
	inline void setBlendMode(bool condition){
		if (condition) SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
		else			     SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_NONE );
	}
	/**
	 Returns the number of rows. if the texture is not a sprite, it's always 1.
	 */
  virtual inline int rows() {return 1;} // Deprecated
	
	/**
   Returns the number of columns. if the texture is not a sprite, it's always 1.
	 */
	virtual inline int columns() {return 1;} // Deprecated
	
	/**
	 Get the texture dimensions or frame's dimension if its a sprite.
	 */
	inline Rect getRect(){ return source_rect; }
	
	inline Vector2 getSize(){ return Vector2(source_rect.w, source_rect.h); }
	
  static inline Renderer2D* renderer() {
    return _renderer;
  }
	/**
	 Draw a line on the current rendering target.
	 */
	static inline void drawLine(Vector2 p1, Vector2 p2){
		SDL_RenderDrawLine(_renderer->sdl_renderer, p1.x, p1.y, p2.x, p2.y);
	}
	
	/**
	 Draw a set of lines on the current rendering target.
	 */
	static inline void drawLines(SDL_Point *points, int n){
		SDL_RenderDrawLines(_renderer->sdl_renderer, points, n);
	}
	
	/**
	 Draw a point on the current rendering target.
	 */
	static inline void drawPoint(Vector2 point){
		SDL_Point p = point.toSDLPoint();
		SDL_RenderDrawPoint(_renderer->sdl_renderer, p.x, p.y);
	}
	/**
	 Draw a point on the current rendering target using a SDL_Point.
	 */
	static inline void drawPoint(SDL_Point point){
		SDL_RenderDrawPoint(_renderer->sdl_renderer, point.x, point.y);
	}
	
	/**
	 Draws a Rect on the current rendering target.
	 */
	static inline void drawRect(Rect rect){
		SDL_Rect r = rect.to_sdl_rect();
		SDL_RenderDrawRect(_renderer->sdl_renderer, &r);
	}
	
	/**
	 Draws a Circle on the current rendering target.
	 */
	static void drawCircle(Circle circle);
  
  /**
   Draws a Filled Circle on the current rendering target.
   */
  static void drawFilledCircle(Circle circle, Color outline, Color filler);
  
	/**
	 Fills the texture with an image loaded from disk.
	 */
	virtual void loadImage(string file, int rows = 1, int columns = 1);
	
	/**
	 Given the position and the frame that will be rendered,
	 the Texture send the information needed to the Renderer2D.
	 */
	virtual void Render(Vector2	position,
											Vector2	scale    = Vector2(1,1),
											Rect		 *srcRect  = NULL,
											int 		  angle    = 0,
											bool		  inverted = false);
	
	inline void setAsRenderTarget() { _renderer->setRendererTarget(sdl_texture); }
	
	virtual inline Rect getCollisionRect(Vector2 frame){
		return source_rect;
	}

private:
  
  void createColorTexture();
  
};
}

using namespace engine;
EXPORT_KEY(Texture)

#endif
#endif /* sdl_texturehpp */
