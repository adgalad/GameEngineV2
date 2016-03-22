//
//  Game.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/19/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "Window.hpp"
//#include "LuaScript.hpp"
#include "XMLTextureLoader.hpp"
#include "XMLSceneLoader.hpp"
#include "ButtonWidget.hpp"
#include "ContainerWidget.hpp"
#include "Thread.hpp"
#include "Renderer.hpp"

using namespace std;

static bool running = true;
static bool finishMainLoop = true;

static int loopFn(void *ptr)
{
//	Window	*Window = (Window*)ptr;
//	Window->loop();
//	
	return 0;
}

class Game
{
private:
	Window		*main_window_;
	Renderer	*renderer_;
	SDL_Event	event_;

	
public:
	
	
	Game(){};
	~Game(){
		printf("Renderer deleted\n");


		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
	void init(){
		TTF_Init();
	}
	
	void Start(){
		main_window_ = new Window(640, 480, SDL_WINDOW_RESIZABLE);
		renderer_ = new Renderer(main_window_);
		
		Scene current_scene;
		Texture *tex = new Texture();
		Object obj;
		obj.set_texture(tex);
		obj.texture_->loadImage("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV2/Resources/yoshi.png");
		
		


		while(running){
			
			
			SDL_Delay(50);

		}
	}
};



#endif /* Game_hpp */
