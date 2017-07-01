//
//  SP_Scene.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/26/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef SP_Scene_hpp
#define SP_Scene_hpp

#ifdef __cplusplus
#include "Game.hpp"
#include "SP.hpp"
#include "GroundCollision.hpp"


void LoadSP(Game *game);

class SPScene;
BOOST_CLASS_IS_WRAPPER(SPScene);

class SPScene : public Scene {
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    
<<<<<<< HEAD
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Scene);
=======
    TAG_BASE(ar,Scene);
>>>>>>> OpenGL

  }
  SPScene(){}
public:
  
  SPScene(string name, engine::Rect r) : Scene(name,r){
	};
	
  virtual ~SPScene() {}
  
	void Start(){
		this->Scene::Start();
		Sound::PlayMusic("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Elwynn Forest.mp3", -1);
	}
};
EXPORT_KEY(SPScene);

#endif
#endif /* SP_Scene_hpp */
