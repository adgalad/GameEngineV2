//
//  GameEngineObject.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "GameEngineObject.hpp"


GameEngineObject::GameEngineObject(){
	Start();
}

GameEngineObject::~GameEngineObject(){
	Finish();
}

void GameEngineObject::CallUpdate(){
	Update();
	
}


void GameEngineObject::add_script(Script *script){
	scripts.push_back(script);
}

void GameEngineObject::remove_script(Script *script){
	
}


void GameEngineObject::Start(){
	
}

void GameEngineObject::Update(){
	
}

void GameEngineObject::FixedUpdate(){
	
}

void GameEngineObject::Finish(){
	
}



void GameEngineObject::loop(){
	//Por definir
}

void GameEngineObject::render(){
	//Por definir
}