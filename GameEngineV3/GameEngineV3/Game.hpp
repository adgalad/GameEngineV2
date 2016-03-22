//
//  Game.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Input.hpp"
#include "O1.hpp"

class Game {
	Window *main_window;
	Renderer *renderer;
	Input *input;
	
	Uint32 max_fps;
	bool running;
	
public:
	
	Scene *current_scene;
	
	Game(Window *window, Renderer *renderer){
		this->main_window = window;
		this->renderer = renderer;
		input = new Input();
		Object::_input = input;
		Texture::_renderer = renderer;
		max_fps = 1000/30;
		running = true;
	}
	
	~Game(){
		delete main_window;
		delete renderer;
	}
	void setMaxFramesPerSecond(Uint32 n){
		max_fps = 1000/n;
	}
	void QuitGame(){
		running = false;
	}
	void Run() {
		
		current_scene->Init();
		Uint32 oldTicks = SDL_GetTicks();
		Uint32 newTicks = 0;
		while (running) {
			
			// Get new Input events every loop
			input->Update();
			
			// Exit events
			if (input->KeyDown(KEY_ESCAPE) || input->Quit()){
				QuitGame();
			}
			else if (input->KeyPressed(KEY_N)){
				current_scene->reset();
			}

			// Update and Render the Scene and its objects
			current_scene->Update();
			current_scene->Render();
			
			// Present the render in the window and then clear its cache
			renderer->render_present();
			renderer->clear_render();
			
			newTicks = SDL_GetTicks();
			if (newTicks - oldTicks < max_fps){
				SDL_Delay(max_fps - newTicks + oldTicks);
			}
			oldTicks = newTicks;
		}
	}
	
	
};

#endif /* Game_hpp */
