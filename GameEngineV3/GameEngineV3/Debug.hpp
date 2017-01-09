//
//  Debug.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/10/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Debug_hpp
#define Debug_hpp

#include <cstdlib>
#include <string>
#include <ctime>

namespace engine {

using namespace std;

class Debug {

public:
    /**
     *  Hola
     */
	Debug (){}
	
	~Debug();
		
	static void Init();
	
    /**
     *  Log
     *
     *  @param msg message
     */
	static void Log(string msg);
	
	inline static void WriteLog(bool value){ _debug->_writeLog = value; }
	
	inline static void ShowLog (bool value){ _debug->_showLog  = value; }
	
	inline static void ClearLog()
	{
		if (_debug->_log) {
            _debug->_log = freopen("rw", _debug->_name.c_str(), _debug->_log);
		}
	}
	
private:
	static unique_ptr<Debug> _debug;
	
	FILE   *_log      = NULL;
	string  _name     = "";
	bool	_showLog  = true;
	bool	_writeLog = true;
};
}

#endif /* Debug_hpp */
