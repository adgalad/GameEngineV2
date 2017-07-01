//
//  Animator.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Animator.hpp"

using namespace engine;

Sprite::Sprite(){

};

Sprite::Sprite(string name,
               string image,
               int rows,
               int columns,
               Vector2 pos,
               Vector2 interSpace)
{
	this->name  = name;
	_image      = image;
  _rows       = rows;
  _columns    = columns;
  _pos        = pos;
  _interSpace = interSpace;
  init();
}


void Sprite::init(){
  SDL_Surface *surface = IMG_Load(_image.c_str());
  if (surface == NULL){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             ("Null Surface: " + _image).c_str(),
                             NULL);
    exit(EXIT_FAILURE);
  }
  SDL_Rect rect = {0, 0,
    surface->w/_rows    - (int)_interSpace.x,
    surface->h/_columns - (int)_interSpace.y };
  
  for (int j = 0 ; j < _columns ; ++j)
  {
    for (int i = 0 ; i < _rows ; ++i)
    {
      SDL_Surface *sprite_surface = SDL_CreateRGBSurface(
                                                         surface->flags,
                                                         rect.w, rect.h,
                                                         surface->format->BitsPerPixel,
                                                         surface->format->Rmask,
                                                         surface->format->Gmask,
                                                         surface->format->Bmask,
                                                         surface->format->Amask
                                                         );
      SDL_BlitSurface(surface, &rect, sprite_surface, 0);
      shared_ptr<Texture> texture =
      shared_ptr<Texture>(new Texture(name+"_Tex_"+to_string(j*_rows+1),
                                      _image,
                                      sprite_surface)
                          );
      if (texture != NULL){
        sheet.push_back(texture);
      } else {
        --i;
        Debug::Log("What?");
      }
      rect.x += rect.w + _interSpace.x;
    }
    rect.y += rect.h + _interSpace.y;
    rect.x = 0;
  }
  SDL_FreeSurface(surface);
}


Sprite::~Sprite(){
	sheet.clear();
}





Animator::Animator(){
	setName("");
}

Animator::~Animator(){
  sprites.clear();
}


void Animator::Init(){
	if (_currentSprite == NULL){
		if (sprites.size() == 0){
			error("Error: No sprite in the animator");
			return;
		}
		_currentSprite = sprites.begin()->second;
	}
  if (_currentSprite->sheet[0]){
    object->texture = _currentSprite->sheet[0];
  }
	Start();
}

void Animator::Start(){
	
}

void Animator::Update()
{
	if (_currentSprite != NULL && _crs == 0)
	{
		if (_currentSprite->loop or
				   (!_currentSprite->loop and
						_current_texture < _currentSprite->sheet.size()-1)
				)
		{
			_current_texture = (_current_texture + 1) % _currentSprite->sheet.size();
		}
		if (_current_texture == -1){
			_current_texture++;
		}
    object->texture = _currentSprite->sheet[_current_texture];
    _crs = _renderDelay;
  } else {
    _crs -= _crs >= 0;
  }
}

void Animator::setName(string name){
	ObjectModule::setName("Animator");
}

void Animator::setRenderDelay(int delay){
  _renderDelay = delay;
  _crs         = delay;
}

void Animator::setSprite(string name){
	if (_currentSprite && _currentSprite->name == name) return;
  Sprites::iterator newSprite = sprites.find(name);
  if (newSprite != sprites.end()){
    _currentSprite = newSprite->second;
    _current_texture = -1;
  } else {
    error("Error: Couldn't find such sprite in the Animator.\n\tname = "+name);
  }
}

EXPORT_IMPLEMENT(Animator);
EXPORT_IMPLEMENT(Sprite);
