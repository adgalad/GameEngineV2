//
//  TextTexture.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/27/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef TextTexture_hpp
#define TextTexture_hpp

#include <SDL2_ttf/SDL_ttf.h>
#include "Texture.hpp"

class Font : ListObject {
	TTF_Font *font;
public:
	Font(string path = "", int size  = 15){
		this->font = TTF_OpenFont(path.c_str(), size);

		if (!font)
		{
			printf("WARNING TextEntity::setFont(char*, int) Unable to open TTF\n\t%s\n",
				   SDL_GetError()
				   );
			exit(EXIT_FAILURE);
		}
	}
	
	~Font(){
		TTF_CloseFont(font);
	}
	
	inline TTF_Font *getFont(){
		return font;
	}
};



class TextTexture : public Texture {
	Color color;
	string font;
	string text;
	int wrap;
	Uint8 size;
	static List textTextures;

	TextTexture(){
		setFont("/Library/Fonts/Arial.ttf", 15);
		setColor(Color(0,0,0));
		setMessage(0,".");
	}
	
	bool createTexture()
	{
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
		surface = TTF_RenderText_Blended_Wrapped(Font(font,size).getFont(),
												 text.c_str(),
												 color.to_SDL_Color(),
												 wrap
												 );
		if(!surface)
		{
			printf("WARNING Unable to create a surface with the text\n\t%s\n", SDL_GetError());
			return false;
		}
		//Create texture from surface pixels
		texture = Renderer::get()->createTextureFromSurface(surface);
		if( texture == NULL )
		{
			printf("WARNING Unable to create texture from rendered text.\n SDL Error: %s", SDL_GetError());
		}
		else {
			srcRect = Rect(0,0,surface->w,surface->h);
		}
		
		return true;
	}
public:
	
	static TextTexture *createTextTexture(string name = ""){
		TextTexture *texture = new TextTexture();
		if (name == "") texture->name = "text "+to_string(texture->_id);
		else texture->name = name;
		textTextures.pushBack(texture);
		
		return texture;
	}

	virtual ~TextTexture(){
		Texture::~Texture();
	}
	void setColor(Color color){
		this->color = color;
	}
	
	void setFont(string font, int size){
		this->font = font;
		this->size = size;
	}
	
	bool setMessage( int wrap, const char *text, ...){

		char buf[1024];
		sprintf(buf, "");
		va_list ap;
		va_start(ap, text);
		vsprintf(buf + strlen(buf), text, ap);
		this->text = text;
		this->wrap = wrap;
		return createTexture();
	}
	
};
#endif /* TextTexture_hpp */
