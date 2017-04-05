//
//  Pacman.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/30/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef Pacman_hpp
#define Pacman_hpp

#include "Game.hpp"
#include "Animator.hpp"
#include "Collision.hpp"
#include "Ghost.hpp"


#define Player



void empowered(Scene*);

class Pacman : public Object {

public:
  direction dir;
  bool canMove;
  Animator *anim;
  RectangleCollider *collider;
  Vector2D auxVector;
  Vector2D scaledPos;
  
  int vel = 4;
  Sound sa, sb;
  
  void Start() {
    collider = new RectangleCollider(Rect(12,12,16,16));
    addModule(collider);
    anim = (Animator*)getModule("Animator");
    sa.loadSound("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/munch A+B.wav");
    sb.loadSound("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/death 1.wav");
    sa.setChannel(1);
    sb.setChannel(2);
    dir = Left;
    anim->setSprite("pmleft");
  }
  void Update() {
    Vector2D movement;
    string sprName;
    
    scaledPos = ((transform.position + Vector2D(6,6))/28);
    auxVector = scaledPos - scaledPos.round_floor();
    
    // if both coordinates are integers, then its exactly above a tile
    // if not, keep moving until its above a tile
    if (auxVector.x != 0 || auxVector.y != 0){
      switch (dir){
        case Up:
          move(Vector2D(0,-vel));
          break;
        case Down:
          move(Vector2D(0,vel));
          break;
        case Right:
          move(Vector2D(vel,0));
          break;
        case Left:
          move(Vector2D(-vel,0));
          break;
      }
    }
    else {
      if (scaledPos == Vector2D(0,14)){
        setPosition(Vector2D(27,14)*28 - Vector2D(6,6));
        scaledPos = Vector2D(27,14);
      } else if (scaledPos == Vector2D(27,14)){
        setPosition(Vector2D(0,14)*28 - Vector2D(6,6));
        scaledPos = Vector2D(0,14);
      }
      direction prevDir = dir;
      if (Input::KeyDown(KEY_UP_ARROW)){
        sprName = "pmup";
        dir = Up;
      } else if (Input::KeyDown(KEY_DOWN_ARROW)){
        sprName = "pmdown";
        dir = Down;
      } else if (Input::KeyDown(KEY_RIGHT_ARROW)){
        sprName = "pmright";
        dir = Right;
      } else if (Input::KeyDown(KEY_LEFT_ARROW)){
        sprName = "pmleft";
        dir = Left;
      }

      Vector2D m = moveForward();
      if (not (m == Vector2D(0,0))){
        move(m);
        if (dir != prevDir) anim->setSprite(sprName);
        
      } else {
        dir = prevDir;
        move(moveForward());
      }
    }
  }
  
  Vector2D moveForward(){
    switch (dir){
      case Up:
        if (table[(int)scaledPos.x][(int)scaledPos.y-1] != wall)
          return Vector2D(0,-vel);
        break;
      case Down:
        if (table[(int)scaledPos.x][(int)scaledPos.y+1] != wall)
          return Vector2D(0,vel);
        break;
      case Right:
        if (table[(int)scaledPos.x+1][(int)scaledPos.y] != wall)
          return Vector2D(vel,0);
        break;
      case Left:
        if (table[(int)scaledPos.x-1][(int)scaledPos.y] != wall)
          return Vector2D(-vel,0);
        break;
    }
    return Vector2D(0,0);
  }
  

  void AI(){
  }
  
  void AfterRender() {
    Texture::renderer->setRenderColor(Color::green);
    Texture::drawRect(collider->absolute_rect);
    Texture::renderer->setRenderColor(Color::black);
  }

  void EnterCollision(Object *other) {
    if (other->tag == "ghost"){
      /* Die */
    }
  }
  
  void EnterTrigger(Object *other){
    if (other->tag == "dot") {
      if (not sa.isPlaying()){
          sa.play(0);
      }
      other->remove();
    }
    else if (other->tag == "bigDot"){
      empowered(this->scene);
      other->remove();
    }
    else if (other->tag == "ghost"){
      anim->setSprite("pmdie");
      sb.play(0);
    }
  }
  
};



class Dot : public Object {
  
  RectangleCollider *col;
  
  void Start(){
    tag = "dot";
    col = (RectangleCollider*)getModule("RectangleCollider");
  }
  
//  void AfterRender() {
//    Texture::renderer->setRenderColor(Color::green);
//    Texture::drawRect(col->absolute_rect);
//    Texture::renderer->setRenderColor(Color::black);
//  }
  
};


class BigDot : public Object {
  
  RectangleCollider *col;
  
  void Start(){
    tag = "bigDot";
    col = (RectangleCollider*)getModule("RectangleCollider");
  }
  
  //  void AfterRender() {
  //    Texture::renderer->setRenderColor(Color::green);
  //    Texture::drawRect(col->absolute_rect);
  //    Texture::renderer->setRenderColor(Color::black);
  //  }
  
};

class PacmanScene : public Scene {
  

  bool readMap(string file);
  
public:
  
  PacmanScene () : Scene("Pacman", Rect(0,0,1024 , 1300)){

  }
  
  Blinky *blinky = new Blinky();
  //    Ghost *g2 = new Ghost(),
  //    *g3 = new Ghost(),
  //    *g4 = new Ghost();
  
  Sound EpicSoundToKillYourEnemies;
  void Start() {
    Scene::Start();
    readMap("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/Original");
    Texture *bg = new Texture("background", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/PacmanBg.jpg");
    Sprite *pmdown = new Sprite("pmdown", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmdown.png", 1, 4);
    Sprite *pmup = new Sprite("pmup", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmup.png", 1, 4);
    Sprite *pmright = new Sprite("pmright", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmright.png", 4, 1);
    Sprite *pmleft = new Sprite("pmleft", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmleft.png", 4, 1);
    Sprite *pmdie  = new Sprite("pmdie", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmdie.png", 1, 7);
    
    
    Sprite *frightened = new Sprite("frightened", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/frightened.png",2,1);
    Sprite *encouraged = new Sprite("encouraged", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/encouraged.png",4,1);
    
    Sprite *blinkydown  = new Sprite("down", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkydown.png", 2,1);
    Sprite *blinkyup    = new Sprite("up", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkyup.png", 2,1);
    Sprite *blinkyright = new Sprite("right", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkyright.png", 2,1);
    Sprite *blinkyleft  = new Sprite("left", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkyleft.png", 2,1);
    
    
    
    Sprite *pinkydown  = new Sprite("down", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkydown.png", 2,1);
    Sprite *pinkyup    = new Sprite("up", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkyup.png", 2,1);
    Sprite *pinkyright = new Sprite("right", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkyright.png", 2,1);
    Sprite *pinkyleft  = new Sprite("left", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkyleft.png", 2,1);
    
    EpicSoundToKillYourEnemies.loadSound("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/large pellet loop.wav");
    EpicSoundToKillYourEnemies.setChannel(3);
    Animator *anim = new Animator();
    
    anim->insertSprite(pmdown);
    anim->insertSprite(pmup);
    anim->insertSprite(pmright);
    anim->insertSprite(pmleft);
    anim->insertSprite(pmdie);
    
    Animator *animBlinky = new Animator();
    
    animBlinky->insertSprite(blinkydown);
    animBlinky->insertSprite(blinkyup);
    animBlinky->insertSprite(blinkyright);
    animBlinky->insertSprite(blinkyleft);
    animBlinky->insertSprite(frightened);
    animBlinky->insertSprite(encouraged);
    
    
    Pacman *pacman = new Pacman();
    pacman->addModule(anim);
    anim->setRenderDelay(2);
    
    

    
    
    blinky->pacman = pacman;
    
    animBlinky->setRenderDelay(2);
    blinky->addModule(animBlinky);
    
    background = bg;
    addObject(pacman);
    addObject(blinky);
//    addObject(g2);
//    addObject(g3);
//    addObject(g4);
    bool ya = true;
    shared_ptr<Texture> dotT = shared_ptr<Texture>(new Texture());
    shared_ptr<Texture> bigDotT = shared_ptr<Texture>(new Texture());
    dotT->createTargetTexture("dot", Rect(0,0,28,28));
    dotT->setAsRenderTarget();
    Texture::renderer->clearTarget();
    Texture::drawFilledCircle(Circle(Vector2D(14,14), 2), Color::white, Color::white);
    
    bigDotT->createTargetTexture("bigDot", Rect(0,0,28,28));
    bigDotT->setAsRenderTarget();
    Texture::renderer->clearTarget();
    Texture::drawFilledCircle(Circle(Vector2D(14,14), 5), Color::white, Color::white);
    
    
    setSceneAsRenderTarget();
    for (int i = 0 ; i < pacmanWidth ; ++i){
      for (int j = 0 ; j < pacmanHeight ; ++j) {
        switch (table[i][j]){
          case player:{
            pacman->setPosition((Vector2D(i,j) * 28) - Vector2D(6,6) );
            break;
          }
          case ghost: {
            if (ya){
              blinky->setPosition((Vector2D(i,j) * 28) - Vector2D(6,6));
              ya = false;
            }
            break;
          }
          case dot:{
            Dot *dotO = new Dot();
            dotO->texture = dotT;
            dotO->setPosition((Vector2D(i,j) * 28));
            addObject(dotO);
            RectangleCollider *col = new RectangleCollider(Rect(10,10,8,8));
            col->setTrigger(true);
            dotO->addModule(col);
            
            break;
          }
          case bigDot:{
            BigDot *bigDotO = new BigDot();
            bigDotO->texture = bigDotT;
            bigDotO->setPosition((Vector2D(i,j) * 28));
            addObject(bigDotO);
            RectangleCollider *col = new RectangleCollider(Rect(10,10,8,8));
            col->setTrigger(true);
            bigDotO->addModule(col);
            
            break;
          }
          default:
            break;
        }
      }
    }
  }
  
  void GivePacmanThePowerToDestroyHisEnemies(){
    blinky->setFrightened();
    EpicSoundToKillYourEnemies.play(14);
  }
  
//  virtual void Render(){
//    Texture::renderer->setRenderColor(Color::white);
//    for (int i = 0 ; i < pacmanWidth ; ++i){
//      for (int j = 0 ; j < pacmanHeight ; ++j) {
//        
//        if (table[i][j] == dot){
////          Texture::drawRect(Rect(i*28,j*28, 28,28));
//          Texture::drawPoint((Vector2D(i,j) * 28)+Vector2D(14,14));
//        }
//        else if (table[i][j] == crossEmpty){
//          Texture::renderer->setRenderColor(Color::red);
//          Texture::drawRect(Rect(i*28,j*28, 28,28));
//          Texture::renderer->setRenderColor(Color::white);
//        }
//        else if (table[i][j] == crossDot){
//          Texture::drawPoint((Vector2D(i,j) * 28)+Vector2D(14,14));
//          Texture::renderer->setRenderColor(Color::yellow);
//          Texture::drawRect(Rect(i*28,j*28, 28,28));
//          Texture::renderer->setRenderColor(Color::white);
//        }
//        else {
////          Texture::drawRect(Rect(i*28,j*28, 28,28));
//        }
//      }
//    }
//    Texture::renderer->setRenderColor(Color::black);
//  }
  
  
  
  
};






void loadPacman();













#endif /* Pacman_hpp */
