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
const int pacmanHeight = 33;

void copyPosTable();
int farthest(int k, int x, int y);


struct Metric{
  double dir;
  double v;
};

Metric closest(int k, int x, int y);


bool readMap(string file);

typedef enum {
  Scatter    = 0,
  Chase      = 1,
  Frightened = 2,
  Housed     = 3,
  Exit       = 4,
  Encouraged = 5,
  Dead       = 6
} ghostMode;

typedef enum {
  empty  = 0,
  player = 0x1,
  blinkyk = 0x2,
  dot    = 0x4,
  bigDot = 0x8,
  fruit  = 0x10,
  wall   = 0x20,
  crossDot = 0x40,
  crossEmpty = 0x80,
  pinkyk = 0x100,
  inkyk = 0x200,
  clydek = 0x400,
  portal = 0x800,
  ghost = 0x1000,
  visited = 0x2000
  
} kind;

typedef struct {
  int timer;
  int wave;
  ghostMode mode;
  bool alreadySaved;
  Vector2 targetTile;
} ghostStatus;

extern kind table[pacmanWidth][pacmanHeight];
extern unsigned int posTable[pacmanWidth][pacmanHeight];

typedef enum {
  Down  = 1,
  Up    = 2,
  Right = 4,
  Left  = 8
} direction;


class Ghost : public Object {
  
public:
  Sound s;
  ghostStatus saved;
  direction dir;
  direction lastDir;
  bool canMove;
  Animator *anim;
  RectangleCollider *collider;
  Vector2 auxVector;
  Vector2 scaledPos;
  Vector2 targetTile;
  ghostMode mode;
  Timer *timer;
  
  int vel = 4;
  
  bool scaryFace = false;
  bool scary     = false;

  
  virtual void Start(){
    mode = Scatter;
    anim = (Animator*)getModule("Animator");
    

    collider = new RectangleCollider(Rect(6,6,28,28));
    collider->setTrigger(true);
    addModule(collider);
    
    tag = "ghost";
    saved.alreadySaved = false;
    
    s.loadSound("/Users/carlosspaggiari/GameEngineV3/GameEngineV3/Resources/Pacman/ghost eat 2.wav");
    s.setChannel(5);
  }
  
  void Update() {
    if (Input::KeyDown(KEY_M)){
      setFrightened();
    }
    
    string sprName;
    
    scaledPos = ((transform.position + Vector2(6,6))/28);
    auxVector = scaledPos - scaledPos.round_floor();
    
    // if both coordinates are integers, then its exactly above a tile
    // if not, keep moving until its above a tile
    if (auxVector.x != 0 || auxVector.y != 0){
      switch (dir){
        case Up:
          move(Vector2(0,-vel));
          break;
        case Down:
          move(Vector2(0,vel));
          break;
        case Right:
          move(Vector2(vel,0));
          break;
        case Left:
          move(Vector2(-vel,0));
          break;
      }
    }
    else if (mode == Frightened && scaryFace){
      scaryFace = false;
    }
    else {
      if (tag == "dead" && mode != Dead){
        mode = Dead;
        vel = 7;
        targetTile = Vector2(13,14);
      }
      if (scaledPos == Vector2(0,14)){
        setPosition(Vector2(27,14)*28 - Vector2(6,6));
        scaledPos = Vector2(27,14);
      } else if (scaledPos == Vector2(27,14)){
        setPosition(Vector2(0,14)*28 - Vector2(6,6));
        scaledPos = Vector2(0,14);
      } else if (mode == Dead && scaledPos == Vector2(13,14)){
        mode = Exit;
        s.pause();
        tag = "ghost";
        vel = 4;
        targetTile = Vector2(13,11);
        dir = Up;
      } else if (mode == Exit && scaledPos == Vector2(13,11)){
        mode = Chase;
      }
      else if (11 <= scaledPos.x && scaledPos.x <= 15 && 13 <= scaledPos.y && scaledPos.y <= 14 && mode != Frightened && mode != Housed){
        mode = Exit;
        s.pause();
        tag = "ghost";
        vel = 4;
        targetTile = Vector2(13,11);
        dir = Up;
      }

      if (mode == Exit || mode == Dead){
        
        table[13][12] = empty;
        table[11][13] = wall;
        table[11][14] = wall;
        table[15][13] = wall;
        table[15][14] = wall;
      }
      
      
      AI();
      
      if (mode != Frightened && mode != Encouraged && mode != Dead) {
        switch (dir){
          case Up:    anim->setSprite("up");    break;
          case Down:  anim->setSprite("down");  break;
          case Right: anim->setSprite("right"); break;
          case Left:  anim->setSprite("left");  break;
        }
      }
      if (!scary && (mode == Frightened || mode == Encouraged)){
        outFrightened();
      }
      
      Vector2 m = moveForward();
      
      posTable[(int)scaledPos.x][(int)scaledPos.y] &= ~ghost;
      move(m);
      switch (dir){
        case Up:    posTable[(int)scaledPos.x][(int)scaledPos.y-1] |= ghost;    break;
        case Down:  posTable[(int)scaledPos.x][(int)scaledPos.y+1] |= ghost;  break;
        case Right: posTable[(int)scaledPos.x+1][(int)scaledPos.y] |= ghost; break;
        case Left:  posTable[(int)scaledPos.x-1][(int)scaledPos.y] |= ghost;  break;
      }
      
      
      table[13][12] = wall;
      table[11][13] = empty;
      table[11][14] = empty;
      table[15][13] = empty;
      table[15][14] = empty;
    }
  }
  
  void reset(){
    Object::reset();
    switch (dir){
      case Up:    anim->setSprite("up");    break;
      case Down:  anim->setSprite("down");  break;
      case Right: anim->setSprite("right"); break;
      case Left:  anim->setSprite("left");  break;
    }
  }
  void AI () {
    if (mode == Frightened || mode == Encouraged){
      dir = escaping();
      return;
    }
    else if (mode == Chase){
      chase();
    }
    else if (targetTile == scaledPos.round_floor()){
      switch(mode){
        case Scatter:
          scatter();
          break;
//        case Chase:
//          chase();
//          break;
        case Housed:
          housed();
          break;
        default:
          break;
      }
    }
    dir = shortestPath();
    
  }
  
  virtual void scatter(){}
  
  virtual void chase(){}
  
  virtual void housed(){
    if (dir == Up){
      targetTile = scaledPos + Vector2(0,1);
      dir = Down;
    } else if (dir == Down){
      targetTile = scaledPos + Vector2(0,-1);
      dir = Up;
    }
  }
  
  virtual void frightened(){}
  
  direction shortestPath(){
    Vector2 vup, vdown, vleft,vright;
    vup    = Vector2(scaledPos.x,scaledPos.y-1);
    vleft  = Vector2(scaledPos.x-1,scaledPos.y);
    vdown  = Vector2(scaledPos.x,scaledPos.y+1);
    vright = Vector2(scaledPos.x+1,scaledPos.y);
    
    
    float up, down, left, right;
    up    = (vup    - targetTile).squareLength();
    left  = (vleft  - targetTile).squareLength();
    down  = (vdown  - targetTile).squareLength();
    right = (vright - targetTile).squareLength();
    direction possible = Up;
    
    float dist = 10000;
    
    
    if (table[(int)vleft.x][(int)vleft.y] != wall &&  left < dist && reverse() != Left){
      possible = Left;
      dist = left;
    }
    
    if (table[(int)vup.x][(int)vup.y] != wall && up < dist && reverse() != Up){
      possible = Up;
      dist = up;
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
    while (tries++ < 10){
      ranDir = (direction)(rand() % 4);
      if (ranDir != rever) switch (ranDir){
        case Up:
          if (table[(int)scaledPos.x][(int)scaledPos.y-1] != wall){
            targetTile = Vector2(scaledPos.x,scaledPos.y-1);
            return (direction)ranDir;
          }
          break;
        case Down:
          if (table[(int)scaledPos.x][(int)scaledPos.y+1] != wall){
            targetTile = Vector2(scaledPos.x,scaledPos.y+1);
            return (direction)ranDir;
          }
          break;
        case Right:
          if (table[(int)scaledPos.x+1][(int)scaledPos.y] != wall){
            targetTile = Vector2(scaledPos.x+1,scaledPos.y);
            return (direction)ranDir;
          }
          break;
        case Left:
          if (table[(int)scaledPos.x-1][(int)scaledPos.y] != wall){
            targetTile = Vector2(scaledPos.x-1,scaledPos.y);
            return (direction)ranDir;
          }
          break;
      }
    }
    
    if (table[(int)scaledPos.x][(int)scaledPos.y-1] != wall && Up != rever){
      targetTile = Vector2(scaledPos.x,scaledPos.y-1);
      return Up;
    }
    if (table[(int)scaledPos.x-1][(int)scaledPos.y] != wall && Left != rever){
      targetTile = Vector2(scaledPos.x-1,scaledPos.y);
      return Left;
    }
    if (table[(int)scaledPos.x][(int)scaledPos.y+1] != wall && Down != rever){
      targetTile = Vector2(scaledPos.x,scaledPos.y+1);
      return Down;
    }
    if (table[(int)scaledPos.x+1][(int)scaledPos.y] != wall && Right != rever){
      targetTile = Vector2(scaledPos.x+1,scaledPos.y);
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
  
  Vector2 moveForward(){
    switch (dir){
      case Up:
        if (table[(int)scaledPos.x][(int)scaledPos.y-1] != wall)
          return Vector2(0,-vel);
        break;
      case Down:
        if (table[(int)scaledPos.x][(int)scaledPos.y+1] != wall)
          return Vector2(0,vel);
        break;
      case Right:
        if (table[(int)scaledPos.x+1][(int)scaledPos.y] != wall)
          return Vector2(vel,0);
        break;
      case Left:
        if (table[(int)scaledPos.x-1][(int)scaledPos.y] != wall)
          return Vector2(-vel,0);
        break;
    }
    return Vector2(0,0);
  }
  

  void die(){
    anim->setSprite("dieright");
    tag = "dead";
    s.play(-1);
  }
};

typedef struct {
  int timer;
  ghostMode mode;
} wave;


class TimerGhost : public Timer {
  
public:
  
  wave *waves;
  int maxWaves;
  
  Ghost * g;
  int nwave = 0;
  
  
  
  TimerGhost() : Timer(0){
    
  }
  
  void Start(){
    ResetTimer(waves[0].timer/5);
    StartTimer();
  }
  

  
  void Finish() {
    if (g->mode == Frightened && g->tag != "dead"){
      g->anim->setSprite("encouraged");
      ResetTimer(2000/5);
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
      } else if (waves[nwave].mode == Chase){
        g->chase();
      } else if (waves[nwave].mode == Exit){
        g->targetTile = Vector2(13,11);
      }
      ResetTimer(waves[nwave].timer/5);
    }
  }

  
};


class Blinky : public Ghost{
public:
  Object *pacman;
  wave waves[14] =
  { {5000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {7000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {5000, Chase} };
  
  
  void reset(){
    dir = Left;
    Ghost::reset();
    TimerGhost* timer = (TimerGhost*)this->timer;
    timer->nwave = 0;
    timer->Start();
    vel = 4;
    targetTile = Vector2(8,14);
    mode = Scatter;
  }
  
  void Start(){
    Ghost::Start();
    TimerGhost *timer = new TimerGhost();
    timer->waves = waves;
    timer->Start();
    timer->maxWaves = 14;
    timer->g = this;
    this->timer = timer;
    targetTile = Vector2(8,14);
    mode = Scatter;
    addModule(timer);
  }
  
  virtual void scatter(){
    targetTile = Vector2(27,0);
  }
  
  virtual void chase(){
    targetTile = ((pacman->transform.position + Vector2(6,6))/28).round_floor();
  }
  
  virtual void frightened(){
    
  }
  
  void AfterRender(){
    Vector2 target = targetTile*28;
    Color c = Application.renderer()->getDrawColor();
    Application.renderer()->setDrawColor(Color::red);
    Texture::drawRect(Rect(target.x,target.y,28,28));
    Application.renderer()->setDrawColor(c);
  }
};

class Pinky : public Ghost {
public:
  Object *pacman;
  wave waves[15] =
  { {1000, Exit}, {4000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {7000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {5000, Chase} };
  
  void reset(){
    dir = Up;
    Ghost::reset();
    TimerGhost* timer = (TimerGhost*)this->timer;
    timer->nwave = 0;
    timer->Start();
    targetTile = Vector2(13,11);
    mode = Exit;
    vel = 4;
  }
  
  void Start(){
    Ghost::Start();
    targetTile = Vector2(13,11);
    TimerGhost *timer = new TimerGhost();
    timer->waves = waves;
    timer->Start();
    timer->maxWaves = 15;
    timer->g = this;
    this->timer = timer;
    mode = Exit;
    addModule(timer);
  }
  
  virtual void scatter(){
    targetTile = Vector2(0,0);
  }
  
  virtual void chase();
  
  virtual void frightened(){
    
  }
  
  void AfterRender(){
    Vector2 target = targetTile*28;
    Color c = Application.renderer()->getDrawColor();
    Application.renderer()->setDrawColor(Color(255,192,203));
    Texture::drawRect(Rect(target.x,target.y,28,28));
    Application.renderer()->setDrawColor(c);
  }
};

class Inky : public Ghost{
public:
  Object *pacman;
  Ghost *blinky;
  wave waves[15] =
  { {4000, Housed}, {2000, Exit},
    {10000, Chase}, {5000, Chase}, {5000, Chase},
    {7000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {5000, Chase} };
  
  
  void reset(){
    dir = Up;
    Ghost::reset();
    TimerGhost* timer = (TimerGhost*)this->timer;
    timer->nwave = 0;
    timer->Start();
    targetTile = Vector2(11,13);
    mode = Housed;
    vel = 4;
    dir = Up;
  }
  
  
  void Start(){
    Ghost::Start();
    TimerGhost *timer = new TimerGhost();
    timer->waves = waves;
    timer->Start();
    timer->maxWaves = 15;
    timer->g = this;
    this->timer = timer;
    targetTile = Vector2(11,13);
    mode = Housed;
    dir = Up;
    addModule(timer);
  }
  
  virtual void scatter(){
    targetTile = Vector2(27,30);
  }
  
  virtual void chase();
  
  virtual void frightened(){
    
  }
  
//  void AfterRender(){
//    Vector2 target = targetTile*28;
//    Color c = Application.renderer()->getDrawColor();
//    Application.renderer()->setDrawColor(Color::blue);
//    Texture::drawRect(Rect(target.x,target.y,28,28));
//    Application.renderer()->setDrawColor(c);
//  }
  
};

class Clyde : public Ghost{
public:
  Object *pacman;
  wave waves[15] =
  { {10000, Housed}, {2000, Exit},
    {5000, Chase}, {5000, Chase},
    {7000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {10000, Chase}, {5000, Chase}, {5000, Chase},
    {5000, Scatter}, {5000, Chase} };
  
  void reset(){
    dir = Up;
    Ghost::reset();
    TimerGhost* timer = (TimerGhost*)this->timer;
    timer->nwave = 0;
    timer->Start();
    targetTile = Vector2(15,13);
    mode = Housed;
    vel = 4;
  }
  
  void Start(){
    Ghost::Start();
    TimerGhost *timer = new TimerGhost();
    timer->waves = waves;
    timer->Start();
    timer->maxWaves = 15;
    timer->g = this;
    this->timer = timer;
    targetTile = Vector2(15,13);
    mode = Housed;
    dir = Up;
    addModule(timer);
  }
  
  virtual void scatter(){
    targetTile = Vector2(0,30);
  }
  
  virtual void chase(){
    Vector2 ppos = pacman->transform.position;
    Vector2 cpos = transform.position;
    if ((ppos - cpos).length() < 8*28){
      scatter();
    } else {
      targetTile = ((pacman->transform.position + Vector2(6,6))/28).round_floor();
    }
  }
  
  virtual void frightened(){
    
  }
  
//  void AfterRender(){
//    
//    Vector2 target = targetTile*28;
//    Color c = Application.renderer()->getDrawColor();
//    Application.renderer()->setDrawColor(Color(255,165,0));
//    Texture::drawCircle(Circle(transform.position, 8*28));
//    Texture::drawRect(Rect(target.x,target.y,28,28));
//    Application.renderer()->setDrawColor(c);
//  }
  
};


#endif /* Ghost_hpp */
