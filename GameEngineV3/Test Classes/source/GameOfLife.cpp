//
//  GameOfLife.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 7/2/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "GameOfLife.hpp"

GameOfLife::GameOfLife(){
	x    = 0;
	y    = 0;
	dead = 0;
	alive = 0;
	delay = 10;
	pause = false;
};

bool GameOfLife::loadFile(const char* filename){
	FILE* src = fopen(filename, "r");
	if (!src) {
		fprintf(stderr,"File not valid.");
		return false;
	}
	fscanf(src, "%d", &x);
	fscanf(src, "%d", &y);
	char c;
	for (int i = 0 ; i <y ; ++i){
		vector<bool> aux;
		for (int j = 0 ; j <x ; ++j){
			fscanf(src, "%c",&c);
			if (c == '.') {
				aux.push_back(0);
				++alive;
			}
			else if (c == 'O'){
				aux.push_back(1);
				++dead;
			}
			else --j;
		}
		grid.push_back(aux);
		newgrid.push_back(aux);
		seed.push_back(aux);
	}
	fclose(src);
	return true;
}


void GameOfLife::nextGeneration(){
	alive = 0;
	dead = 0;
	Application.renderer()->setDrawColor(Color::yellow);
	for (int i = 0 ; i < y ; ++i){
		for (int j = 0 ; j < x ; ++j){
			int p = 0;
			
			p += grid[(i+1+y)%y][(j+1+x)%x];
			p += grid[( i +y)%y][(j+1+x)%x];
			p += grid[(i+1+y)%y][( j +x)%x];
			p += grid[(i-1+y)%y][(j-1+x)%x];
			p += grid[( i +y)%y][(j-1+x)%x];
			p += grid[(i-1+y)%y][( j +x)%x];
			p += grid[(i+1+y)%y][(j-1+x)%x];
			p += grid[(i-1+y)%y][(j+1+x)%x];
			
			switch (p) {
				case 2:
					if (grid[i][j]){
						++alive;
						newgrid[i][j] = 1;
						Texture::drawPoint(Vector2(j,i));
					} else {
						++dead;
						newgrid[i][j] = 0;
					}
					break;
				case 3:
					++alive;
					newgrid[i][j] = 1;
					Texture::drawPoint(Vector2(j,i));
					break;
					
				default:
					++dead;
					newgrid[i][j] = 0;
					break;
			}
		}
	}

	for (int i = 0 ; i <y ; ++i){
		for (int j = 0 ; j <x ; ++j){
			
			grid[i][j] = newgrid[i][j];
		}
	}
	Application.renderer()->setDrawColor(Color::black);
}




void GameOfLife::showGrid_stdio() {
	printf("Delay: %d ms    Grid: %d x %d    Alive: %d    Dead: %d\n",delay,x,y,alive,dead);
	for (int i = 0 ; i <y ; ++i){
		for (int j = 0 ; j <x ; ++j){
			printf("%c ", grid[i][j]?'@':' ');
		}
		printf("|\n");
	}
}

void GameOfLife::genRandomGrid(int in_x, int in_y) {
	grid.clear();
	newgrid.clear();
	srand ((unsigned int)time(NULL));
	alive = 0;
	dead  = 0;
	
	int r;
	x = in_x;
	y = in_y;
	for (int i = 0 ; i < y ; ++i){
		vector<bool> aux;
		for (int j = 0 ; j < x ; ++j){
			r = rand()%5;
			if (r == 0){
				++alive;
				aux.push_back(1);
			}
			else{
				++dead;
				aux.push_back(0);
			}
		}
		grid.push_back(aux);
		newgrid.push_back(aux);
		seed.push_back(aux);
	}
}

void loadGol(){
	GameOfLife *object = new GameOfLife();
	Scene *scene = new Scene("Game of Life",Rect(0,0,800,600));
	scene->addObject(object);
  Application.currentScene = shared_ptr<Scene>(scene);
}
