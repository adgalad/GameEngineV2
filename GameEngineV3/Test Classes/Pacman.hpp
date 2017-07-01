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

#include "Neat.hpp"

#define Player



void empowered(Scene*);


class Pacman : public Object {

public:
  int score;
  direction dir;
  bool canMove;
  Animator *anim;
  RectangleCollider *collider;
  Vector2 auxVector;
  Vector2 scaledPos;
  int points;
  
  Ghost *blinky, *pinky, *inky, *clyde;
  

  NeuralNetwork *nn;
  
  bool energiezed = false;
  int vel = 4;
  Sound sa, sb, sc;
  
  void Start() {

    
    collider = new RectangleCollider(Rect(12,12,16,16));
    addModule(collider);
    anim = (Animator*)getModule("Animator");
    sa.loadSound("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/munch A+B.wav");
    sb.loadSound("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/death 1.wav");
    sc.loadSound("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/ghost eat 7.wav");
    sa.setChannel(1);
    sb.setChannel(2);
    sc.setChannel(4);
    dir = Left;
    anim->setSprite("pmleft");
  }
  void Update() {
    Vector2 movement;
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
    else {
      if (scaledPos == Vector2(0,14)){
        setPosition(Vector2(27,14)*28 - Vector2(6,6));
        scaledPos = Vector2(27,14);
      } else if (scaledPos == Vector2(27,14)){
        setPosition(Vector2(0,14)*28 - Vector2(6,6));
        scaledPos = Vector2(0,14);
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
//      
//      
//      AI();
      switch (dir){
        case Up:
          sprName = "pmup";
          break;
        case Down:
          sprName = "pmdown";
          break;
        case Right:
          sprName = "pmright";
          break;
        case Left:
          sprName = "pmleft";
          break;
      }
      
      Vector2 m = moveForward();
      if (not (m == Vector2(0,0))){
        move(m);
        if (dir != prevDir) anim->setSprite(sprName);
        
      } else {
        dir = prevDir;
        move(moveForward());
      }
    }
  }
  void reset(){
    Object::reset();
    anim->setSprite("pmleft");
    dir = Left;
    scaledPos = ((transform.position + Vector2(6,6))/28);
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
  

  void AI(){
    Metric closestPill = closest(dot|bigDot, scaledPos.x, scaledPos.y);
    Metric closestGhost = closest(ghost, scaledPos.x, scaledPos.y);
    double dBlinky = (scaledPos - blinky->scaledPos).length();
    double dPinky  = (scaledPos - pinky->scaledPos).length();
    double dInky   = (scaledPos - inky->scaledPos).length();
    double dClyde  = (scaledPos - clyde->scaledPos).length();
    double fBlinky = blinky->mode == Frightened || blinky->mode == Encouraged;
    double fPinky  = pinky->mode  == Frightened || pinky->mode  == Encouraged;
    double fInky   = inky->mode   == Frightened || inky->mode   == Encouraged;
    double fClyde  = clyde->mode  == Frightened || clyde->mode  == Encouraged;
    double mvs = 0;
    if (posTable[(int)scaledPos.x][(int)scaledPos.y-1] != wall){
      mvs += Up;
    } else if (posTable[(int)scaledPos.x][(int)scaledPos.y+1] != wall){
      mvs += Down;
    } else if (posTable[(int)scaledPos.x-1][(int)scaledPos.y] != wall){
      mvs += Left;
    } else if (posTable[(int)scaledPos.x+1][(int)scaledPos.y] != wall){
      mvs += Right;
    }
    nn->evaluate({mvs, closestPill.dir, closestPill.v, closestGhost.dir, closestGhost.v, dBlinky, dPinky, dInky, dClyde, fBlinky, fPinky, fInky, fClyde});
    
    double o1 = nn->output[0]->value;
    double o2 = nn->output[1]->value;
    double o3 = nn->output[2]->value;
    double o4 = nn->output[3]->value;
    
    double max = 0;
    
    if (o1 > max){
      dir = Up;
      max = o1;
    }
    if (o2 > max){
      dir = Down;
      max = o2;
    }
    if (o3 > max){
      dir = Left;
      max = o3;
    }
    if (o4 > max){
      dir = Right;
    }
  }
  
  void AfterRender() {
    Application.renderer()->setDrawColor(Color::green);
    Texture::drawRect(collider->absolute_rect);
    Application.renderer()->setDrawColor(Color::black);
  }

//  void EnterCollision(Object *other) {
//    if (other->tag == "ghost"){
//      /* Die */
//    }
//  }
  
  void EnterTrigger(Object *other){
    if (other->tag == "dot") {
      if (not sa.isPlaying()){
          sa.play(0);
      }
      score += 10;
//      cout << "Score: "<< score << "\n";
      other->hide(true);
      posTable[(int)scaledPos.x][(int)scaledPos.y] &= ~dot;
    }
    else if (other->tag == "bigDot"){
      empowered(this->scene);
      score += 100;
//      cout << "Score: "<< score << "\n";
      other->hide(true);
      posTable[(int)scaledPos.x][(int)scaledPos.y] &= ~bigDot;
    }
    else if (other->tag == "ghost"){
      ghostMode m = ((Ghost*)other)->mode;
      if (m == Frightened || m == Encouraged){
        score += 500;
//        cout << "Score: "<< score << "\n";
        sc.play(0);
        SDL_Delay(300);
        ((Ghost*)other)->die();
        
      } else {
//        anim->setSprite("pmdie");
        sb.play(0);
        scene->Reset();
      }
    }
  }
  
};



class Dot : public Object {
  
  RectangleCollider *col;
  
  void Start(){
    tag = "dot";
    col = (RectangleCollider*)getModule("RectangleCollider");
  }
  void reset(){
    Object::reset();
    hide(false);
  }
//  void AfterRender() {
//    Application.renderer()->setDrawColor(Color::green);
//    Texture::drawRect(col->absolute_rect);
//    Application.renderer()->setDrawColor(Color::black);
//  }
  
};


class BigDot : public Object {
  
  RectangleCollider *col;
  
  void Start(){
    tag = "bigDot";
    col = (RectangleCollider*)getModule("RectangleCollider");
  }
  
  void reset(){
    Object::reset();
    hide(false);
  }
  //  void AfterRender() {
  //    Application.renderer()->setDrawColor(Color::green);
  //    Texture::drawRect(col->absolute_rect);
  //    Application.renderer()->setDrawColor(Color::black);
  //  }
  
};

extern Pacman *gPacman;


double pacmanFitness(NeuralNetwork *nn);

class PacmanScene : public Scene {
  

  bool readMap(string file);
  
public:
  
  PacmanScene () : Scene("Pacman", Rect(0,0,1024 , 1300)){

  }
  
  ~PacmanScene(){

    delete p;
  }
  
  Blinky *blinky = new Blinky();
  Pinky  *pinky  = new Pinky();
  Inky   *inky   = new Inky();
  Clyde  *clyde  = new Clyde();
  Pacman *pacman = new Pacman();
  vector<Object*> dots;
  
  Population *p;
  int nni = 0, nnj = 0;
  
  Sound EpicSoundToKillYourEnemies;
  
  
  void Start() {
    Scene::Start();
    
//    p = new Population(100, 13, 4);
//    p->fitness = pacmanFitness;
//    savePopulation("/Users/carlosspaggiari/pacman.ge", p);
    
    p = loadPopulation("/Users/carlosspaggiari/pacman.ge");
    p->setupParameters( 0.3    // Min distance for compatibility
                       , 1     // c1
                       , 1     // c2
                       , 0.4   // c3
                       , 10000 // Max Fitness
                       , 30    // Weight Mutation Probability over 100
                       , 30    // Connection Mutation Probability over 100
                       , 30    // New Neuron Mutation Probability over 100
                       );
    p->fitness = pacmanFitness;    
    
    
    gPacman = pacman;
    
    readMap("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/Original");
    Texture *bg = new Texture("background", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/PacmanBg.jpg");
    Sprite *pmdown = new Sprite("pmdown", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmdown.png", 1, 4);
    Sprite *pmup = new Sprite("pmup", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmup.png", 1, 4);
    Sprite *pmright = new Sprite("pmright", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmright.png", 4, 1);
    Sprite *pmleft = new Sprite("pmleft", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmleft.png", 4, 1);
    Sprite *pmdie  = new Sprite("pmdie", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pmdie.png", 1, 7);
    
    
    Sprite *frightened = new Sprite("frightened", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/frightened.png",2,1);
    Sprite *encouraged = new Sprite("encouraged", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/encouraged.png",4,1);
    Sprite *dieright   = new Sprite("dieright", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/dieright.png",1,1);
    
    Sprite *blinkydown  = new Sprite("down", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkydown.png", 2,1);
    Sprite *blinkyup    = new Sprite("up", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkyup.png", 2,1);
    Sprite *blinkyright = new Sprite("right", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkyright.png", 2,1);
    Sprite *blinkyleft  = new Sprite("left", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/blinkyleft.png", 2,1);
    
    Sprite *pinkydown  = new Sprite("down", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkydown.png", 2,1);
    Sprite *pinkyup    = new Sprite("up", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkyup.png", 2,1);
    Sprite *pinkyright = new Sprite("right", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkyright.png", 2,1);
    Sprite *pinkyleft  = new Sprite("left", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/pinkyleft.png", 2,1);
    
    Sprite *inkydown  = new Sprite("down", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/inkydown.png", 2,1);
    Sprite *inkyup    = new Sprite("up", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/inkyup.png", 2,1);
    Sprite *inkyright = new Sprite("right", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/inkyright.png", 2,1);
    Sprite *inkyleft  = new Sprite("left", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/inkyleft.png", 2,1);
    
    Sprite *clydedown  = new Sprite("down", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/clydedown.png", 2,1);
    Sprite *clydeup    = new Sprite("up", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/clydeup.png", 2,1);
    Sprite *clyderight = new Sprite("right", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/clyderight.png", 2,1);
    Sprite *clydeleft  = new Sprite("left", "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/Pacman/clydeleft.png", 2,1);
    
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
    animBlinky->insertSprite(dieright);
    
    Animator *animPinky = new Animator();
    
    animPinky->insertSprite(pinkydown);
    animPinky->insertSprite(pinkyup);
    animPinky->insertSprite(pinkyright);
    animPinky->insertSprite(pinkyleft);
    animPinky->insertSprite(frightened);
    animPinky->insertSprite(encouraged);
    animPinky->insertSprite(dieright);
    
    Animator *animInky = new Animator();
    
    animInky->insertSprite(inkydown);
    animInky->insertSprite(inkyup);
    animInky->insertSprite(inkyright);
    animInky->insertSprite(inkyleft);
    animInky->insertSprite(frightened);
    animInky->insertSprite(encouraged);
    animInky->insertSprite(dieright);
    
    Animator *animClyde = new Animator();
    
    animClyde->insertSprite(clydedown);
    animClyde->insertSprite(clydeup);
    animClyde->insertSprite(clyderight);
    animClyde->insertSprite(clydeleft);
    animClyde->insertSprite(frightened);
    animClyde->insertSprite(encouraged);
    animClyde->insertSprite(dieright);
    
    
    
    
    pacman->addModule(anim);
    anim->setRenderDelay(2);
        
    blinky->pacman = pacman;
    animBlinky->setRenderDelay(2);
    blinky->addModule(animBlinky);
    
    pinky->pacman = pacman;
    animPinky->setRenderDelay(2);
    pinky->addModule(animPinky);
    
    inky->pacman = pacman;
    inky->blinky = blinky;
    animInky->setRenderDelay(2);
    inky->addModule(animInky);
    
    clyde->pacman = pacman;
    animClyde->setRenderDelay(2);
    clyde->addModule(animClyde);
    
    pacman->blinky = blinky;
    pacman->pinky  = pinky;
    pacman->inky   = inky;
    pacman->clyde  = clyde;
    pacman->nn     = p->species[0][0];
    
    background = bg;
    addObject(pacman);
    addObject(blinky);
    addObject(pinky);
    addObject(inky);
    addObject(clyde);
    shared_ptr<Texture> dotT = shared_ptr<Texture>(new Texture());
    shared_ptr<Texture> bigDotT = shared_ptr<Texture>(new Texture());
    dotT->createTargetTexture("dot", Rect(0,0,28,28));
    dotT->setAsRenderTarget();
    Application.renderer()->clearTarget();
    Texture::drawFilledCircle(Circle(Vector2(14,14), 2), Color::white, Color::white);
    
    bigDotT->createTargetTexture("bigDot", Rect(0,0,28,28));
    bigDotT->setAsRenderTarget();
    Application.renderer()->clearTarget();
    Texture::drawFilledCircle(Circle(Vector2(14,14), 5), Color::white, Color::white);
    
    
    Application.setSceneAsRenderTarget();
    for (int i = 0 ; i < pacmanWidth ; ++i){
      for (int j = 0 ; j < pacmanHeight ; ++j) {
        switch (table[i][j]){
          case player:{
            pacman->setPosition((Vector2(i,j) * 28) - Vector2(6,6) );
            break;
          }
          case blinkyk:
              blinky->setPosition((Vector2(i,j) * 28) - Vector2(6,6));
            break;
          case pinkyk:
            pinky->setPosition((Vector2(i,j) * 28) - Vector2(6,6));
            break;
          case inkyk:
            inky->setPosition((Vector2(i,j) * 28) - Vector2(6,6));
            break;
          case clydek:
            clyde->setPosition((Vector2(i,j) * 28) - Vector2(6,6));
            break;
          case dot:{
            Dot *dotO = new Dot();
            dotO->texture = dotT;
            dotO->setPosition((Vector2(i,j) * 28));
            addObject(dotO);
            RectangleCollider *col = new RectangleCollider(Rect(10,10,8,8));
            col->setTrigger(true);
            dotO->addModule(col);
            dots.push_back(dotO);
            break;
          }
          case bigDot:{
            BigDot *bigDotO = new BigDot();
            bigDotO->texture = bigDotT;
            bigDotO->setPosition((Vector2(i,j) * 28));
            addObject(bigDotO);
            RectangleCollider *col = new RectangleCollider(Rect(10,10,8,8));
            col->setTrigger(true);
            bigDotO->addModule(col);
            dots.push_back(bigDotO);
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
    pinky->setFrightened();
    inky->setFrightened();
    clyde->setFrightened();
    EpicSoundToKillYourEnemies.play(14);
  }
  
  void Reset(){
    Scene::Reset();
    copyPosTable();
    
    nnj++;
    pacman->nn->fitness = pacmanFitness(pacman->nn);
    wm = cm = nm = 0;
    if (nnj == p->species[nni].size()){
      nnj = 0;
      nni++;
    }
    if (nni == p->species.size()){
      nni = 0;
      for (int i = 0 ; i < p->species.size() ; ++i){
        for (int j = 0 ; j < p->species[i].size() ; ++j){
          
          p->species[i][j]->mutate();
        }
      }
      p->_calculateFitness();
      p->crossOver();
      p->generation++;
      savePopulation("/Users/carlosspaggiari/pacman.ge", p);
      printf("Weight: %d,  Connection: %d,  Neuron: %d\n",wm,cm,nm);
      printf("Generation: %d, Pop: %d, Species: %d  Fitness: %f\n----------------------\n",p->generation, p->population, (int)p->species.size(), gBestFitness);
    }
    
    pacman->nn = p->species[nni][nnj];
    if (pacman->nn == NULL){
      cout << "what?\n";
    }
    pacman->score = 0;
    
  }
  
  void Update(){
    Scene::Update();
    if (Input::KeyPressed(KEY_SPACE)){
      Reset();
    }
//    system("clear");
//    for (int i = 0 ; i < pacmanHeight ; ++i){
//      for (int j = 0 ; j < pacmanWidth ; ++j) {
//        if (posTable[j][i] == empty) printf("  ");
//        else if (posTable[j][i] & player) printf("P ");
//        else if (posTable[j][i] & ghost) printf("G ");
//        else if (posTable[j][i] & dot) printf(". ");
//        else if (posTable[j][i] & bigDot) printf("o ");
//        else if (posTable[j][i] & wall) printf("* ");
//        else if (posTable[j][i] & portal) printf("@ ");
//        
//      }
//      printf("\n");
//    }
    
  }
  
//  virtual void Render(){
//    Application.renderer()->setDrawColor(Color::white);
//    for (int i = 0 ; i < pacmanWidth ; ++i){
//      for (int j = 0 ; j < pacmanHeight ; ++j) {
//        
//        if (table[i][j] == dot){
////          Texture::drawRect(Rect(i*28,j*28, 28,28));
//          Texture::drawPoint((Vector2(i,j) * 28)+Vector2(14,14));
//        }
//        else if (table[i][j] == crossEmpty){
//          Application.renderer()->setDrawColor(Color::red);
//          Texture::drawRect(Rect(i*28,j*28, 28,28));
//          Application.renderer()->setDrawColor(Color::white);
//        }
//        else if (table[i][j] == crossDot){
//          Texture::drawPoint((Vector2(i,j) * 28)+Vector2(14,14));
//          Application.renderer()->setDrawColor(Color::yellow);
//          Texture::drawRect(Rect(i*28,j*28, 28,28));
//          Application.renderer()->setDrawColor(Color::white);
//        }
//        else {
////          Texture::drawRect(Rect(i*28,j*28, 28,28));
//        }
//      }
//    }
//    Application.renderer()->setDrawColor(Color::black);
//  }
  
  
  
  
};







void loadPacman();













#endif /* Pacman_hpp */
