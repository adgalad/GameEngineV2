//
//  Game.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#ifdef __cplusplus


#include "Window.hpp"
#include "Renderer.hpp"
#include "Framerate.hpp"
#include "Object.hpp"
#include "ObjectModule.hpp"
#include "Scene.hpp"
#include "Input.hpp"




namespace engine {

class Game {
  
  SERIALIZE
  
	Window *main_window = NULL;
	Renderer *renderer  = NULL;
  Framerate framerate = Framerate();
	bool running;
	
  
  Game(){
    
  }
  
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
    // note, version is always the latest when saving
    int fps = this->framerate.getFPS();
    TAG(ar, name);
    TAG(ar, fps);
    Scene *scene = (Scene*)currentScene.get();
    TAG(ar,scene);
  }
  
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
    int fps;
    TAG(ar, name);
    TAG(ar, fps);
    framerate.setFPS(fps);
    if (main_window == NULL && renderer == NULL){
      Window   * window   = new Window(this->name, 500, 500);
      Renderer * renderer = new Renderer(window);
      this->main_window = window;
      this->renderer		= renderer;
      Texture::renderer = renderer;
      Sound::Init();
    }
    running = true;
    Scene *scene;
    TAG(ar,scene);
    currentScene = shared_ptr<Scene>(scene);
  }
  SPLIT_SERIALIZATION
  
  
public:

  
  shared_ptr<Scene> currentScene = NULL;
  string name = "";
	
	Game(Window *window, Renderer *renderer);
	
	~Game();
		
	void setMaxFramesPerSecond(Uint32 n);
	
	void QuitGame();
	
	void Run();

	
};
  
}

void saveGame(std::string filename, const engine::Game &obj);
void loadGame(std::string filename, engine::Game &obj);


#endif

#endif /* Game_hpp */
