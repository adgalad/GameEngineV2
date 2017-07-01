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
	Renderer2D *_renderer  = NULL;
  Framerate framerate = Framerate();
	bool running;
  SDL_GLContext _glContext;
  
	
  
  Game(){};
  
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
    if (main_window == NULL && _renderer == NULL){
      Window   * window   = new Window(this->name, 500, 500);
      Renderer2D * renderer = new Renderer2D(window);
      this->main_window = window;
      this->_renderer		= renderer;
      Sound::Init();
    }
    running = true;
    Scene *scene;
    TAG(ar,scene);
    currentScene = shared_ptr<Scene>(scene);
  }
  SPLIT_SERIALIZATION
  
  
  
public:
  Renderer2D * renderer(){ return _renderer; }
  
  Window *window() { return main_window; }
  
  shared_ptr<Scene> currentScene = NULL;
  string name = "";
	
	Game(Window *window, Renderer2D *_renderer);
	
	~Game();
	
  void SetWindow(Window *window, Renderer2D *renderer);
  
	void setMaxFramesPerSecond(Uint32 n);
	
	void QuitGame();
	
	void Run();

  void resizeWindow(int w, int h){
    SDL_SetWindowSize(main_window->sdl_window, w, h);
  }
	
  inline void setSceneAsRenderTarget(){
    
    if (currentScene && currentScene->_target_texture){
      currentScene->_target_texture->setAsRenderTarget();
    } else {
      _renderer->setRendererTarget(NULL);
    }
  }
  
};
  
}

template <class T> void saveSerialize(std::string filename, const T &obj);
template <class T> void loadSerialize(std::string filename, T &obj);

extern Game Application;


#endif

#endif /* Game_hpp */
