//
//  GameOfLife.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 7/2/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef GameOfLife_hpp
#define GameOfLife_hpp


#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "Game.hpp"


using namespace engine;

#define Grid vector<vector<bool>>

class GameOfLife : public Object
{
public:
	GameOfLife();
	
	bool loadFile(const char* filename);
	
	void nextGeneration();
	
	void showGrid_stdio();
	
	void genRandomGrid(int in_x, int in_y);
	
	void Start() {
		genRandomGrid(800, 600);
//		loadFile("/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/glider6.gl");

	}
	
	inline void Update(){
		if (Input::KeyPressed(KEY_P)) pause = not pause;
		
		if (not pause)
			nextGeneration();
	}
	
private:
	int x,y;
	bool pause = false;
	Uint32 delay;
	Grid grid;
	Grid newgrid;
	Grid seed;
	int dead, alive;
};

void loadGol();



#endif /* GameOfLife_hpp */
