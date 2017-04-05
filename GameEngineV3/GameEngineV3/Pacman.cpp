//
//  Pacman.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/30/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "Pacman.hpp"



kind table[pacmanWidth][pacmanHeight];

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
      case '+':
        table[i][j] = crossDot;
        break;
      case '%':
        table[i][j] = crossEmpty;
        break;
      case 'P':
        table[i][j] = player;
        break;
      case 'i':
        table[i][j] = ghost;
      case 'c':
        table[i][j] = ghost;
      case 'b':
        table[i][j] = ghost;
      case 'p':
        table[i][j] = ghost;
        break;
      case '1':
        table[i][j] = empty; // Portal O
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
  fclose(f);
  return true;
}

void loadPacman(){
  Scene *scene = new PacmanScene();
  
  
  Game::Application->currentScene = shared_ptr<Scene> (scene);
  
  Game::Application->resizeWindow(800,884);
}


void empowered(Scene *s){
  ((PacmanScene*) s)->GivePacmanThePowerToDestroyHisEnemies();
}
