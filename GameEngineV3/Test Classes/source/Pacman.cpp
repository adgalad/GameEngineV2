//
//  Pacman.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/30/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "Pacman.hpp"



kind table[pacmanWidth][pacmanHeight];
unsigned int posTable[pacmanWidth][pacmanHeight];
Pacman *gPacman = NULL;


int farthest(int k, int x, int y){
  if (posTable[x][y] & k){
    return 0;
  }
  posTable[x][y] |= visited;
  int max = 0;
  int current = 0;
  int _k = posTable[x][y+1];
  
  if ((_k & wall & visited) == 0){
    current = farthest(k, x, y+1) + 1;
    if (current > max) max = current;
  }
  
  _k = posTable[x][y-1];
  if ( (_k & wall & visited) == 0){
    current = farthest(k, x, y-1) + 1;
    if (current > max) max = current;
  }
  _k = posTable[x+1][y];
  if ( (_k & wall & visited) == 0){
    current = farthest(k, x+1, y) + 1;
    if (current > max) max = current;
  }
  _k = posTable[x-1][y];
  if ((_k & wall & visited) == 0){
    current = farthest(k, x-1, y) + 1;
    if (current > max) max = current;
  }
  
  return max;
}



int _closest(int k, int x, int y){
  
  if (posTable[x][y] & k){
    return 0;
  }
  posTable[x][y] |= visited;
  int min = 9999;
  int current = 9999;
  int _k = posTable[x][y+1];
  if ((_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x, y+1) + 1;
    if (current < min) min = current;
  }
  _k = posTable[x][y-1];
  if ( (_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x, y-1) + 1;
    if (current < min) min = current;
  }
  _k = posTable[x+1][y];
  if ( x < pacmanWidth-1 && (_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x+1, y) + 1;
    if (current < min) min = current;
  }
  _k = posTable[x-1][y];
  if (x > 0 && (_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x-1, y) + 1;
    if (current < min) min = current;
  }
  return min;
}


Metric closest(int k, int x, int y){
  for (int i = 0 ; i < pacmanWidth ; ++i){
    for (int j = 0 ; j < pacmanHeight ; ++j){
      posTable[i][j] &= ~visited;
    }
  }
  posTable[x][y] |= visited;
  double min = 9999;
  int current = 9999;
  double dir = 0.0;
  int _k = posTable[x][y+1];
  if ((_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x, y+1) + 1;
    if (current < min){
      min = current;
      dir = (double)Down;
    }
  }
  _k = posTable[x][y-1];
  if ((_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x, y-1) + 1;
    if (current < min){
      min = current;
      dir = (double)Up;
    }
  }
  _k = posTable[x+1][y];
  if (x < pacmanWidth-1 && (_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x+1, y) + 1;
    if (current < min){
      min = current;
      dir = (int)Right;
    }
  }
  _k = posTable[x-1][y];
  if (x > 0 && (_k & wall) == 0 && (_k & visited) == 0){
    current = _closest(k, x-1, y) + 1;
    if (current < min){
      min = current;
      dir = (double)Left;
    }
  }
  
  return {dir, min};
}


void copyPosTable(){
  for (int i = 0 ; i < pacmanHeight ; ++i){
    for (int j = 0 ; j < pacmanWidth ; ++j) {
      posTable[j][i] = 0;
      if (table[j][i] == blinkyk || table[j][i] == pinkyk || table[j][i] == inkyk || table[j][i] == clydek )
        posTable[j][i] |= ghost;
      else
        posTable[j][i] |= table[j][i];
    }
  }
}

double pacmanFitness(NeuralNetwork *nn){
  double fitness = (double)gPacman->score;
  printf(" -> %f \n", fitness);
  return fitness;
}

bool PacmanScene::readMap(string file){
  FILE *f = fopen(file.c_str(), "r");
  if (f == NULL) {
    error("Could not open file: " + file);
    return false;
  }
  char buffer;
  int i = 0, j = 0;
  while (fscanf(f,"%c", &buffer) != EOF) {
    
    switch (buffer) {
      case '*':
        table[i][j] = wall;
        break;
      case '.':
        table[i][j] = dot;
        break;
      case 'o':
        table[i][j] = bigDot;
        break;
      case '-':
        table[i][j] = empty;
        break;
      case 'P':
        table[i][j] = player;
        break;
      case 'i':
        table[i][j] = inkyk;
        break;
      case 'c':
        table[i][j] = clydek;
        break;
      case 'b':
        table[i][j] = blinkyk;
        break;
      case 'p':
        table[i][j] = pinkyk;
        break;
      case '1':
        table[i][j] = portal; // Portal O
        break;
      default:
        break;
    }
    
    if (i == pacmanWidth) {
      i = 0;
      ++j;
    } else {
      ++i;
    }
  }
  copyPosTable();
  fclose(f);
  return true;
}

void loadPacman(){
  Scene *scene = new PacmanScene();
  
  
  Application.currentScene = shared_ptr<Scene> (scene);
  
  Application.resizeWindow(800,884);
}


void empowered(Scene *s){
  ((PacmanScene*) s)->GivePacmanThePowerToDestroyHisEnemies();
}

void Pinky::chase(){
  Pacman *p = (Pacman*)pacman;
  
  Vector2 offset = Vector2(0,0);
  
  switch (p->dir){
    case Up:
      offset = Vector2(-4,-4);
      break;
    case Down:
      offset = Vector2(0,4);
      break;
    case Right:
      offset = Vector2(4,0);
      break;
    case Left:
      offset = Vector2(-4,0);
      break;
  }
  targetTile = ((pacman->transform.position + Vector2(6,6))/28).round_floor() + offset;
}

void Inky::chase(){
  Pacman *p = (Pacman*)pacman;
  Vector2 bpos = blinky->scaledPos;
  Vector2 offset = Vector2(0,0);
  
  switch (p->dir){
    case Up:
      offset = Vector2(-2,-2);
      break;
    case Down:
      offset = Vector2(0,2);
      break;
    case Right:
      offset = Vector2(2,0);
      break;
    case Left:
      offset = Vector2(-2,0);
      break;
  }
  Vector2 v = ((pacman->transform.position + Vector2(6,6))/28).round_floor() + offset;
  v = (v - bpos)*2;
  targetTile = bpos + v;
}
