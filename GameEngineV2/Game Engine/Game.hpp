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
#include "MainWindow.hpp"
//#include "LuaScript.hpp"
#include "XMLTextureLoader.hpp"
#include "XMLSceneLoader.hpp"
#include "ButtonWidget.hpp"
#include "ContainerWidget.hpp"
using namespace std;

class Game
{
private:
	MainWindow mainWindow;
	SDL_Event event;

	
public:
	
	
	Game(){};
	~Game(){
		printf("Renderer deleted\n");

		delete Renderer::camera;
		SDL_DestroyRenderer(Renderer::renderer);
		Renderer::camera   = NULL;
		Renderer::renderer = NULL;
		IMG_Quit();
		SDL_Quit();
	}
	void init(){
		Texture::null();
		
	}
	
	void start(){
		bool running = true;

		
		XMLTextureLoader loader;
		loader.openXMLFile("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/textures.xml");
		loader.load();

		XMLSceneLoader sceneLoader;
		sceneLoader.openXMLFile("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV2/GameEngineV2/scene.xml");
		Scene *currentScene;
		currentScene = new Scene();
		sceneLoader.load(currentScene);
		
		Player *p = (Player*)currentScene->players[0];
		p->key[Up]    = SDLK_w;
		p->key[Down]  = SDLK_s;
		p->key[Left]  = SDLK_a;
		p->key[Right] = SDLK_d;
		p->setPosition(Point<float>(0,0));
		
		ButtonWidget *b = new ButtonWidget();
		b->loadTextureByName("boton");
		b->setPosition(Point<float>(0,0));
		
		ContainerWidget *c = new ContainerWidget(Color(0,00,0,150), 300,700);
		
		c->addSubwidget(b);		
		c->setPosition(Point<float>(180,100));

		mainWindow.addSubwidget(currentScene);
		mainWindow.addSubwidget(c);
		c->name = "container";

		Renderer::camera->setCameraTarget(p->getPosition());
		Renderer::setCanvasSize(currentScene->getTextureSize());

		while(running){
			
			mainWindow.loop();
			Renderer::camera->loop();
			if (!(running = mainWindow.eventHandler())) break;
			mainWindow.render();
			
			Renderer::renderPresent();
			SDL_Delay(50);
		}
	}

};



#endif /* Game_hpp */
