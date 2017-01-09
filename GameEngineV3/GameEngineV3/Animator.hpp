//
//  Animator.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Animator_hpp
#define Animator_hpp

#ifdef __cplusplus

#include <map>
#define Sprites map<string,Sprite*>

/**
 *  @file Animator
 *
 *  Handle the animation of an object manipulating its sprites.
 */
#include "Scene.hpp"

namespace engine {

  

/*! \class Sprite Animator.hpp ""
 *
 *  Docs for Sprite class
 */

class Sprite{
  SERIALIZE
  
  template <class Archive>
  void save(Archive & ar, const unsigned int version)  const{
    TAG(ar, name);
//    TAG(ar, sheet); init() load the sheet
    TAG(ar, loop);
    TAG(ar, _image);
    TAG(ar, _rows);
    TAG(ar, _columns);
    TAG(ar, _pos);
    TAG(ar, _interSpace);
  }
  
  template <class Archive>
  void load(Archive & ar, const unsigned int version) {
    TAG(ar, name);
//    TAG(ar, sheet); init() load the sheet
    TAG(ar, loop);
    TAG(ar, _image);
    TAG(ar, _rows);
    TAG(ar, _columns);
    TAG(ar, _pos);
    TAG(ar, _interSpace);
    init();
  }
  SPLIT_SERIALIZATION
  
  int _rows, _columns;
  Vector2D _pos, _interSpace;
  string _image;
  
  void init();
  
public:

	string name;                       /// Sprite's name
	vector<shared_ptr<Texture>> sheet; /// Std vector with all the textures of the sprite
	bool loop = true;                  /// TODO
	
	/**
	 *  Default Constructor
	 */
	Sprite();
	
	/**
	 *  Sprite Constructor
	 *
	 *  @param name    Sprite's name
	 *  @param image   Path to the source image
	 *  @param rows    Number of rows
	 *  @param columns Number of columns
	 *  @param pos     Initial position in the source image. by default it (0,0)
	 *
	 *  @return Sprite
	 */
	Sprite(string name,
         string image,
         int rows,
         int columns,
         Vector2D pos = Vector2D(0,0),
         Vector2D interSpace = Vector2D(0,0));
  

	
	/**
	 *  Default Destructor
	 */
	~Sprite();



};

/*! \class Animator Animator.hpp ""
 *
 *  Docs for Aniamtor class
 */
class Animator : public ObjectModule{
  SERIALIZE
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){
    TAG_BASE(ar, ObjectModule);
    TAG(ar, sprites);
    TAG(ar, _currentSprite);
    TAG(ar, _currentSprite_id);
    TAG(ar, _current_texture);
    TAG(ar, _renderDelay);
    TAG(ar, _crs);
  }
public:
	Sprites sprites; /**< Std vector with all the Animator's sprites. */
	
	/**
	 *  Defult Constructor
	 */
	Animator();
	
	/**
	 *  Default Destructor
	 */
	~Animator();
	
	/**
	 *  Initialize all private components and modules inside the class just
	 *  before entering the Game's main loop. This method calls Start().
	 */
	void Init();
	
	/**
	 *  Initialize user defined components. It is empty by default and should 
	 *  be override when inherit from this class
	 */
	virtual void Start();
	
	/**
	 *  Updates the class state on every cycle of the Game's main loop
	 */
	virtual void Update();
	
  
  /**
   *  Insert a Sprite in the Animator. Returns false if the Sprite is already
   *  in the Animator.
   *
   *  @param spr Sprite being inserted
   */
  inline bool insertSprite(Sprite* spr){
    return sprites.insert(pair<string, Sprite*>(spr->name,spr)).second;
  }
  
	/**
	 *  Set the name of the Animator
	 *
	 *  @param name Animator's name
	 */
	void setName(string name);

  
  /**
   *  Set a delay between each frame of the animation.
   *  The delay is relative to the FPS and mean how many 
   *  loops before change the current texture
   *
   *  @param delay
   */
  void setRenderDelay(int delay);
  
	/**
	 *  Take the sprite named as the given string and set it 
   *  as the current sprite.
	 *
	 *  @param name Name of the desired sprite
	 */
	void setSprite(string name);

private:
  Sprite *_currentSprite = NULL;
  
  int _currentSprite_id  = 0;
  int _current_texture   = 0;
  int _renderDelay       = 1;
  int _crs               = 1;
};
  
}
using namespace engine;
EXPORT_ABSTRACT_KEY(Animator)
EXPORT_KEY(Sprite);
#endif
#endif /* Animator_hpp */
