//
//  Debug.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/10/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Debug.hpp"

using namespace engine;

unique_ptr<Debug> Debug::_debug;


Debug::~Debug(){
	fclose(_log);
}

void Debug::Log(string msg)
{
	if (_debug->_log and _debug->_writeLog){
		fputs((msg+"\n").c_str(),_debug->_log);
		fflush(_debug->_log);
	}
	if (_debug->_showLog) {
		printf("Debug: %s\n",msg.c_str());
	}
}


void Debug::Init() {
	
	_debug = unique_ptr<Debug>(new Debug);
	if (_debug == NULL) {
		fprintf(stderr,"Could not create Debug\n");
		return;
	}
	
	time_t now;
	unique_ptr<struct tm> timeinfo;
	char buffer[80];
	string msg;
	time(&now);
	timeinfo = unique_ptr<struct tm>(localtime(&now));
	
	strftime(buffer,80,"%Y-%m-%d",timeinfo.get());
	
	timeinfo.release();
	
	_debug->_name = string(buffer);
	_debug->_name = "debug_"+_debug->_name+".log";
	
	_debug->_log = fopen(_debug->_name.c_str(), "a+");
	msg = "Log "+_debug->_name+" Initialized";
	Log("=====================================");
	Log(msg);
	msg.clear();
	
}
