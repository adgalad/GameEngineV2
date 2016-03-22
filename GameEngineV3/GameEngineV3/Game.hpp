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

class Game {
	Window *main_window;
	Renderer *renderer;
	Input *input;
public:
	
	Scene *current_scene;
	
	Game(Window *window, Renderer *renderer){
		this->main_window = window;
		this->renderer = renderer;
		input = new Input();
		Object::_input = input;
		Texture::_renderer = renderer;
	}
	
	~Game(){
		delete main_window;
		delete renderer;
	}
	
	void Run() {
		while (1) {
			
			// Get new Input events every loop
			input->Update();
			
			// Exit events
			if (input->KeyDown(KEY_ESCAPE) || input->Quit()){
				break;
			}

			// Update and Render the Scene and its objects
			current_scene->Update();
			current_scene->Render();

			// Present the render in the window and then clear its cache
			renderer->render_present();
			renderer->clear_render();
		}

	}
};

#endif /* Game_hpp */
