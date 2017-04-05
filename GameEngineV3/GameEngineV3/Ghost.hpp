//
//  Ghost.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 4/4/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef Ghost_hpp
#define Ghost_hpp

#include <stdio.h>
#include "Game.hpp"
#include "Animator.hpp"
#include "Collision.hpp"
#include "Timer.hpp"



extern int vel;





const int pacmanWidth  = 28;
const int pacmanHeight = 31;

bool readMap(string file);

typedef enum {
  Scatter    = 0,
  Chase      = 1,
  Frightened = 2,
  Housed     = 3,
  Exit       = 4,
  Encouraged = 5
} ghostMode;

typedef enum {
  empty  = 0,
  player = 1,
  ghost  = 2,
  dot    = 4,
  bigDot = 8,
  fruit  = 16,
  wall   = 32,
  crossDot = 64,
  crossEmpty = 128
  
} kind;

typedef struct {
  int timer;
  int wave;
  ghostMode mode;
  bool alreadySaved;
  Vector2D targetTile;
} ghostStatus;

extern kind table[pacmanWidth][pacmanHeight];

typedef enum {
  Down  = 0,
  Up    = 1,
  Right = 2,
  Left  = 3
} direction;


class Ghost : public Object {

public:
  ghostStatus saved;
  direction dir;
  direction lastDir;
  bool canMove;
  Animator *anim;
  RectangleCollider *collider;
  Vector2D auxVector;
  Vector2D scaledPos;
  Vector2D targetTile;
  ghostMode mode;
  Timer *timer;
  
  int vel = 4;
  
  bool scaryFace = false;
  bool scary     = false;

  
  virtual void Start(){
    mode = Scatter;
    anim = (Animator*)getModule("Animator");
    targetTile = ((transform.position - Vector2D(6,6))/28).round_floor();

    collider = new RectangleCollider(Rect(6,6,28,28));
    collider->setTrigger(true);
    addModule(collider);
    
    tag = "ghost";
    saved.alreadySaved = false;
  }
  
  void Update() {
    if (Input::KeyDown(KEY_M)){
      setFrightened();
    }
    
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
    else if (mode == Frightened && scaryFace){
      scaryFace = false;
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
      
      AI();
      
      if (mode != Frightened && mode != Encouraged) { switch (dir){
          case Up:    anim->setSprite("up");    break;
          case Down:  anim->setSprite("down");  break;
          case Right: anim->setSprite("right"); break;
          case Left:  anim->setSprite("left");  break;
        }
      }
      if (!scary && (mode == Frightened || mode == Encouraged)){
        outFrightened();
      }
      
      Vector2D m = moveForward();
      
      move(m);
//      if (not (m == Vector2D(0,0))){
//        move(m);
//        if (dir != prevDir) anim->setSprite(sprName);
//        
//      } else {
//        dir = prevDir;
//        move(moveForward());
//      }
    }
  }
  
  void AI () {
    if (mode == Frightened || mode == Encouraged){
      dir = escaping();
      return;
    }
    else if (targetTile == scaledPos.round_floor()){
      switch(mode){
        case Scatter:
          scatter();
          break;
        case Chase:
          chase();
          break;
        default:
          break;
      }
    }
    dir = shortestPath();
    
  }
  
  virtual void scatter(){}
  
  virtual void chase(){}
  
  virtual void frightened(){}
  
  direction shortestPath(){
    Vector2D vup, vdown, vleft,vright;
    vup    = Vector2D(scaledPos.x,scaledPos.y-1);
    vleft  = Vector2D(scaledPos.x-1,scaledPos.y);
    vdown  = Vector2D(scaledPos.x,scaledPos.y+1);
    vright = Vector2D(scaledPos.x+1,scaledPos.y);
    
    
    float up, down, left, right;
    up    = (vup    - targetTile).squareLength();
    left  = (vleft  - targetTile).squareLength();
    down  = (vdown  - targetTile).squareLength();
    right = (vright - targetTile).squareLength();
    direction possible;
    
    float dist = 10000;
    
    if (table[(int)vup.x][(int)vup.y] != wall && up < dist && reverse() != Up){
      possible = Up;
      dist = up;
    }
    
    if (table[(int)vleft.x][(int)vleft.y] != wall &&  left < dist && reverse() != Left){
      possible = Left;
      dist = left;
    }
    
    if (table[(int)vdown.x][(int)vdown.y] != wall && down < dist && reverse() != Down){
      possible = Down;
      dist = down;
    }
    
    if (table[(int)vright.x][(int)vright.y] != wall && right < dist && reverse() != Right){
      possible = Right;
      dist = right;
    }
    
    return possible;
    
  }
  
  void setFrightened ();
  
  void outFrightened ();
  
  direction escaping() {
    int tries = 0;
    direction ranDir;
    direction rever = reverse();
    while (tries < 10){
      ranDir = (direction)(rand() % 4);
      if (ranDir != rever) switch (ranDir){
        case Up:
          if (table[(int)scaledPos.x][(int)scaledPos.y-1] != wall){
            targetTile = Vector2D(scaledPos.x,scaledPos.y-1);
            return (direction)ranDir;
          }
          break;
        case Down:
          if (table[(int)scaledPos.x][(int)scaledPos.y+1] != wall){
            targetTile = Vector2D(scaledPos.x,scaledPos.y+1);
            return (direction)ranDir;
          }
          break;
        case Right:
          if (table[(int)scaledPos.x+1][(int)scaledPos.y] != wall){
            targetTile = Vector2D(scaledPos.x+1,scaledPos.y);
            return (direction)ranDir;
          }
          break;
        case Left:
          if (table[(int)scaledPos.x-1][(int)scaledPos.y] != wall){
            targetTile = Vector2D(scaledPos.x-1,scaledPos.y);
            return (direction)ranDir;
          }
          break;
      }
    }
    
    if (table[(int)scaledPos.x][(int)scaledPos.y-1] != wall && Up != rever){
      targetTile = Vector2D(scaledPos.x,scaledPos.y-1);
      return Up;
    }
    if (table[(int)scaledPos.x-1][(int)scaledPos.y] != wall && Left != rever){
      targetTile = Vector2D(scaledPos.x-1,scaledPos.y);
      return Left;
    }
    if (table[(int)scaledPos.x][(int)scaledPos.y+1] != wall && Down != rever){
      targetTile = Vector2D(scaledPos.x,scaledPos.y+1);
      return Down;
    }
    if (table[(int)scaledPos.x+1][(int)scaledPos.y] != wall && Right != rever){
      targetTile = Vector2D(scaledPos.x+1,scaledPos.y);
      return Right;
    }
    
    return Up;
  }

  
  direction reverse(){
    switch (dir){
      case Up:    return Down;
      case Down:  return Up;
      case Right: return Left;
      case Left:  return Right;
      default:    return Up;
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
  
  void AfterRender(){
    Vector2D target = targetTile*28;
    Color c = Texture::renderer->getDrawColor();
    Texture::renderer->setRenderColor(Color::red);
    Texture::drawRect(Rect(target.x,target.y,28,28));
    Texture::renderer->setRenderColor(c);
  }
  virtual string changeSprite(){ return "";};
};

typedef struct {
  int timer;
  ghostMode mode;
} wave;


class TimerGhost : public Timer {
  
public:
  
  wave waves[14] = { {5000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {7000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {5000, Chase} };
  int maxWaves;
  
  Ghost * g;
  int nwave = 0;
  
  
  
  TimerGhost(int ms) : Timer(ms){
    
  }
  
  void Start(){
    StartTimer();
    maxWaves = 14;
  }
  

  
  void Finish() {
    if (g->mode == Frightened){
      g->anim->setSprite("encouraged");
      ResetTimer(2000);
      g->mode = Encouraged;
    }
    else if (g->mode == Encouraged){
      g->scary = false;
    }
    else {
      if (nwave < maxWaves-1)
        ++nwave;
      g->mode = waves[nwave].mode;
      if (waves[nwave].mode == Scatter){
        g->scatter();
        ResetTimer(waves[nwave].timer);
      } else if (waves[nwave].mode == Chase){
        g->chase();
        ResetTimer(waves[nwave].timer);
      }
    }
  }

  
};


class Blinky : public Ghost{
public:
  Object *pacman;
  void Start(){
    Ghost::Start();
    TimerGhost *timer = new TimerGhost(5000);
    timer->Start();
    
    timer->g = this;
    this->timer = timer;
    addModule(timer);
  }
  
  virtual void scatter(){
    targetTile = Vector2D(0,0);
  }
  
  virtual void chase(){
    targetTile = ((pacman->transform.position + Vector2D(6,6))/28).round_floor();
  }
  
  virtual void frightened(){
    
  }
};

class Pinky : public Ghost {
  
};


#endif /* Ghost_hpp */
